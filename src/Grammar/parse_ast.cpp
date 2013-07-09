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

#include "include/Grammar/parse_ast.h"
#include "core/types.h"
#include "core/Memory.h"
#include "include/core/VM.h"
#include <sstream>
#include "llvm/Intrinsics.h"

#define CHAR_SIZE sizeof(char) * 8

long top_level_counter = 0;

using namespace llvm;


namespace panopticon {

// llvm classes
IRBuilder<> ExprAST::builder = IRBuilder<>(getGlobalContext());
std::unordered_map<std::string, llvm::Value*> ExprAST::namedValues;

FunctionAST* convert_to_top_level_function(ExprAST* expr, llvm::Type* returnType)
{
    std::vector<std::string> args;
    std::vector<llvm::Type*> arg_types;
    std::stringstream ss;
    ss << "top-level";
    ss << top_level_counter++;
    PrototypeAST* proto = new PrototypeAST(ss.str(),args,arg_types,returnType);

    ExprAST* body = expr;

    return new FunctionAST(proto,body);
}

//Numbers
Value* NumberExprAST::codeGen() const
{
    return ConstantFP::get(getGlobalContext(), APFloat(number));
}

llvm::Type* NumberExprAST::type() const
{
    return llvm::Type::getDoubleTy(getGlobalContext());
}

//Booleans
Value* BooleanExprAST::codeGen() const
{
    return ConstantInt::get(llvm::Type::getInt1Ty(llvm::getGlobalContext()),(uint64_t)boolean);
}

llvm::Type* BooleanExprAST::type() const
{
    return llvm::Type::getInt1Ty(getGlobalContext());
}

//Chars
Value* CharExprAST::codeGen() const
{
    return ConstantInt::get(getGlobalContext(), APInt(CHAR_SIZE, character));
}

llvm::Type* CharExprAST::type() const
{
    return llvm::Type::getInt8Ty(getGlobalContext());
}

//Function calls
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
    return llvm::Type::getDoubleTy(getGlobalContext());
}

//Prototypes for Functions
//llvm::FunctionType* PrototypeAST::functionType() const
//{
//    return FunctionType::get(FunctionType::getVoidTy(getGlobalContext()), FunctionType::getVoidTy(getGlobalContext()), true);
//}

llvm::Function* PrototypeAST::codeGen() const
{
    FunctionType *functionType = FunctionType::get(return_arity,argument_arity, false);

    llvm ::Function* func = llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, name, module);

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

//Functions
llvm::Function* FunctionAST::codeGen() const
{
    namedValues.clear();

    llvm::Function* func = proto->codeGen();

    if(!func)
        return NULL;

    // Create a new basic block to start insertion into.
    BasicBlock* entry = BasicBlock::Create(getGlobalContext(), "entry", func);

    ExprAST::builder.SetInsertPoint(entry);

    Value* returnVal = body->codeGen();

    if(returnVal)
    {
        // Finish off the function
        ExprAST::builder.CreateRet(returnVal);

        // Validate the generated code, checking for consistency.
        verifyFunction(*func);
        //        std::cout << "module: " << module << std::endl;
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
    return proto->return_arity;
}

//Variables
Value* VariableExprAST::codeGen() const
{
    //     Look this variable up in the function.
    Value *v = namedValues[Name];
    return v ? v : errorV("Unknown variable name");
}

llvm::Type* VariableExprAST::type() const
{
    return llvm::Type::getDoubleTy(getGlobalContext());
}

//Binary operators
Value* BinaryExprAST::codeGen() const
{
    Value *L = lhs->codeGen();
    Value *R = rhs->codeGen();
    if (L == 0 || R == 0) return 0;

    Value* int_left;
    Value* int_right;
    Value* int_result;
    std::vector<Value*> argsVector;
    std::vector<llvm::Type*> arg_type;

    switch (op) {
    case Add: return builder.CreateFAdd(L, R, "addtmp");
    case Subtract: return builder.CreateFSub(L, R, "subtmp");
    case Multiply: return builder.CreateFMul(L, R, "multmp");
    case Divide: return builder.CreateFDiv(L, R, "divtmp");
    case Modulus: return builder.CreateFRem(L, R, "modtmp");
    case LessThan: return builder.CreateFCmpULT(L, R, "lt_tmp");
    case GreaterThan: return builder.CreateFCmpUGT(L, R, "gt_tmp");
    case EqualTo: return builder.CreateFCmpUEQ(L, R, "eq_tmp");
    case NotEqualTo: return builder.CreateFCmpUNE(L, R, "neq_tmp");
    case GreaterThanEq: return builder.CreateFCmpUGE(L, R, "gte_tmp");
    case LessThanEq: return builder.CreateFCmpULE(L, R, "lte_tmp");
    case And: return builder.CreateAnd(L, R, "and_tmp");
    case Or: return builder.CreateOr(L, R, "or_tmp");
    case ShiftLeft:
        int_left = builder.CreateFPToUI(L,llvm::Type::getInt32Ty(llvm::getGlobalContext()),"castL_tmp");
        int_right = builder.CreateFPToUI(R,llvm::Type::getInt32Ty(llvm::getGlobalContext()),"castR_tmp");
        int_result = builder.CreateShl(int_left,int_right,"shiftL_tmp");
        return builder.CreateSIToFP(int_result,llvm::Type::getDoubleTy(llvm::getGlobalContext()),"castDouble_tmp");
    case ShiftRight:
        int_left = builder.CreateFPToUI(L,llvm::Type::getInt32Ty(llvm::getGlobalContext()),"castL_tmp");
        int_right = builder.CreateFPToUI(R,llvm::Type::getInt32Ty(llvm::getGlobalContext()),"castR_tmp");
        int_result = builder.CreateAShr(int_left,int_right,"shiftR_tmp");
        return builder.CreateSIToFP(int_result,llvm::Type::getDoubleTy(llvm::getGlobalContext()),"castDouble_tmp");
    case BitAnd:
        int_left = builder.CreateFPToUI(L,llvm::Type::getInt32Ty(llvm::getGlobalContext()),"castL_tmp");
        int_right = builder.CreateFPToUI(R,llvm::Type::getInt32Ty(llvm::getGlobalContext()),"castR_tmp");
        int_result = builder.CreateAnd(int_left,int_right,"band_tmp");
        return builder.CreateSIToFP(int_result,llvm::Type::getDoubleTy(llvm::getGlobalContext()),"castDouble_tmp");
    case BitOr:
        int_left = builder.CreateFPToUI(L,llvm::Type::getInt32Ty(llvm::getGlobalContext()),"castL_tmp");
        int_right = builder.CreateFPToUI(R,llvm::Type::getInt32Ty(llvm::getGlobalContext()),"castR_tmp");
        int_result = builder.CreateOr(int_left,int_right,"bor_tmp");
        return builder.CreateSIToFP(int_result,llvm::Type::getDoubleTy(llvm::getGlobalContext()),"castDouble_tmp");
    case BitXOr:
        int_left = builder.CreateFPToUI(L,llvm::Type::getInt32Ty(llvm::getGlobalContext()),"castL_tmp");
        int_right = builder.CreateFPToUI(R,llvm::Type::getInt32Ty(llvm::getGlobalContext()),"castR_tmp");
        int_result = builder.CreateXor(int_left,int_right,"bxor_tmp");
        return builder.CreateSIToFP(int_result,llvm::Type::getDoubleTy(llvm::getGlobalContext()),"castDouble_tmp");
    case Power:
        argsVector.push_back(L);
        argsVector.push_back(R);
        arg_type.push_back(argsVector.at(0)->getType());
        Value* powFunc = llvm::Intrinsic::getDeclaration(module,llvm::Intrinsic::pow,arg_type);
        return builder.CreateCall(powFunc,argsVector,"power_tmp");

        //Error of some kind
//    default:
//        return errorV("invalid binary operator");
    }
}

llvm::Type* BinaryExprAST::type() const
{
    switch (op) {
    case Add:
    case Subtract:
    case Multiply:
    case Divide:
    case Modulus:
    case ShiftLeft:
    case ShiftRight:
    case BitAnd:
    case BitOr:
    case BitXOr:
    case Power:
        return llvm::Type::getDoubleTy(llvm::getGlobalContext());

    case LessThan:
    case GreaterThan:
    case EqualTo:
    case NotEqualTo:
    case GreaterThanEq:
    case LessThanEq:
    case And:
    case Or:
        return llvm::Type::getInt1Ty(llvm::getGlobalContext());

        //Error of some kind
    default:
        return llvm::Type::getVoidTy(llvm::getGlobalContext());
    }
}

ExprAST* parseNumberExpr(double number)
{
    ExprAST *Result = new NumberExprAST(number);
    return Result;
}

ExprAST* parseVariable(std::string name)
{
    ExprAST *Result = new VariableExprAST(name);
    return Result;
}

}
