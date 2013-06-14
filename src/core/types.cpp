/*
    Panopticon - Audio/Graphics/Networking Language
    Copyright (C) 2013 Chad McKinney and Curtis McKinney

    All rights reserved.

    This file is part of Panopticon.

    Panopticon is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Panopticon is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Panopticon.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "core/types.h"
#include "core/Memory.h"
#include "include/core/VM.h"

#define CHAR_SIZE sizeof(char) * 8

using namespace llvm;

namespace panopticon
{

const Data EMPTY_DATA = { 0 };
const object EMPTY_OBJECT = { 0, 0, NIL };

std::string type_string(Type type)
{
    switch(type)
    {
    case NIL:
        return "NIL";
        break;
    case BOOL:
        return "BOOL";
        break;
    case NUMBER:
        return "NUMBER";
        break;
    case STRING:
        return "STRING";
        break;
    case FUNCTION:
        return "FUNCTION";
        break;
    case ARRAY:
        return "ARRAY";
        break;
    case DICTIONARY:
        return "DICTIONARY";
        break;
    case TRIE:
        return "TRIE";
        break;
    case ERROR:
        return "ERROR";
        break;
    case STATEMENT_LIST:
        return "STATEMENT_LIST";
        break;
    case VARIABLE:
        return "VARIABLE";
        break;
    case UNDECLARED_VARIABLE:
        return "UNDECLARED_VARIABLE";
        break;
    case OPERATION_TREE:
        return "OPERATION_TREE";
        break;
    case OPERATION:
        return "OPERATION";
        break;
    case UNARY_OPERATION:
        return "UNARY_OPERATION";
        break;
    case ASSIGNMENT:
        return "ASSIGNMENT";
        break;
    case GUARD:
        return "GUARD";
        break;
    case FUNCTION_BODY:
        return "FUNCTION_BODY";
        break;
    case FUNCTION_ARG_NAMES:
        return "FUNCTION_ARG_NAMES";
        break;
    case FUNCTION_ARG_VALUES:
        return "FUNCTION_ARG_VALUES";
        break;
    case VOID:
        return "VOID";
        break;
    case CODE_BLOCK:
        return "CODE_BLOCK";
        break;
    case PRIMITIVE:
        return "PRIMITIVE";
        break;
    case CONDITION_TREE:
        return "CONDITION_TREE";
        break;
    case CONDITION_BRANCH:
        return "CONDITION_BRANCH";
        break;
    case NO_EXPANSION_OPERATION:
        return "NO_EXPANSION_OPERATION";
        break;
    case UNARY_NO_EXPANSION_OPERATION:
        return "UNARY_NO_EXPANSION_OPERATION";
        break;
    case PATTERN:
        return "PATTERN";
        break;
    case HEAD:
        return "HEAD";
        break;
    case TAIL:
        return "TAIL";
        break;
    case FAILED_CONDITION:
        return "FAILED_CONDITION";
        break;
    default:
        return "Unknown Type";
        break;
    }
}

// llvm classes
IRBuilder<> ExprAST::builder = IRBuilder<>(getGlobalContext());
std::unordered_map<std::string, llvm::Value*> ExprAST::namedValues;

Value* NumberExprAST::codeGen() const
{
    return ConstantFP::get(getGlobalContext(), APFloat(number));
}

llvm::Type* NumberExprAST::type() const
{
    return llvm::Type::getDoubleTy(getGlobalContext());
}

Value* CharExprAST::codeGen() const
{
    return ConstantInt::get(getGlobalContext(), APInt(CHAR_SIZE, character));
}

llvm::Type* CharExprAST::type() const
{
    return llvm::Type::getInt8Ty(getGlobalContext());
}

llvm::Value* CallExprAST::codeGen() const
{
    // Look up the name in the global module table
    llvm::Function* calleeFunc = module->getFunction(callee);

    if(!calleeFunc)
        return errorV("Unkown function referenced");

    // If argument mismatch error.
    if(calleeFunc->arg_size() != args.size())
        return errorV("Incorrect number of arguments passed.");

    std::vector<Value*> argsVector;

    for(size_t i = 0; i < args.size(); ++i)
    {
        argsVector.push_back(args.at(i)->codeGen());
        if(!argsVector.back()) return NULL;
    }

    return ExprAST::builder.CreateCall(calleeFunc, argsVector, "calltmp");
}

llvm::Type* CallExprAST::type() const
{
    return llvm::Type::getVoidTy(getGlobalContext());
}

llvm::FunctionType* PrototypeAST::functionType() const
{
    return FunctionType::get(FunctionType::getVoidTy(getGlobalContext()), FunctionType::getVoidTy(getGlobalContext()), true);
}

llvm::Function* PrototypeAST::codeGen() const
{
    llvm ::Function* func = llvm::Function::Create(functionType(), llvm::Function::ExternalLinkage, name, module);

    if(func->getName() != name)
    {
        func->eraseFromParent();
        func = module->getFunction(name);

        if(!func->empty())
        {
            ExprAST::errorV("redefinition of function");
            return NULL;
        }

        if(func->arg_size() != args.size())
        {
            ExprAST::errorV("redefinition of function with different number of arguments");
            return NULL;
        }
    }

    size_t index = 0;
    llvm::Function::arg_iterator arg_iter = func->arg_begin();

    // Set names for all arguments
    while(arg_iter != func->arg_end())
    {
        arg_iter->setName(args.at(index));

        // Add  arguments to variable symbol table
        ExprAST::namedValues[args.at(index)] = arg_iter;

        ++index;
        ++arg_iter;
    }

    return func;
}

llvm::Function* FunctionAST::codeGen() const
{
    namedValues.clear();

    llvm::Function* func = proto->codeGen();

    if(!func)
        return NULL;

    // Create a new basic block to start insertion into.
    BasicBlock* bb = BasicBlock::Create(getGlobalContext(), "entry", func);
    ExprAST::builder.SetInsertPoint(bb);

    Value* returnVal = body->codeGen();

    if(returnVal)
    {
        // Finish off the function
        ExprAST::builder.CreateRet(returnVal);

        // Validate the generated code, checking for consistency.
        verifyFunction(*func);

        // optimize the function
        passManager->run(*func);

        return func;
    }

    // Error reading Body, remove function
    func->eraseFromParent();
    return NULL;
}

llvm::Type* FunctionAST::type() const
{
    return proto->functionType();
}

} // panopticon namespace
