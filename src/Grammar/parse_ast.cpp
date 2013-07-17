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
#include "include/Grammar/parse.h"

#define CHAR_SIZE sizeof(char) * 8

long top_level_counter = 0;

using namespace llvm;


namespace panopticon {

// llvm classes
IRBuilder<> ExprAST::builder = IRBuilder<>(getGlobalContext());
std::unordered_map<std::string, llvm::Value*> ExprAST::namedValues;

ExprAST* transform_to_lambda_calculus(ExprAST* expr)
{
    switch(expr->getAST_Type())
    {
    //Non-Lambda
    case ExprAST::Function:
    {
        FunctionAST* func = (FunctionAST*)expr;

        std::cout << "Before Lambda-Calculus Conversion: " << std::endl;
        func->print();

        LambdaAST* lambda;
        std::vector<PrototypeAST*> protos;

        if(func->proto->args.size()>0)
        {
            for(int i=0;i<func->proto->args.size();++i)
            {
                std::vector<std::string> args;
                args.push_back(func->proto->args.at(i));
                PrototypeAST* proto = new PrototypeAST("",args);
                proto = new PrototypeAST("",args);
                protos.push_back(proto);
            }

            for(int i=protos.size()-1;i>=0;i-=1)
            {
                if(i<protos.size()-1)
                {
                    lambda = new LambdaAST(protos.at(i),lambda);
                }
                else
                {
                    ExprAST* lambda_body = transform_to_lambda_calculus(func->body);
                    lambda = new LambdaAST(protos.at(i),lambda_body);
                }
            }
        }
        else
        {
            std::vector<std::string> args;
            PrototypeAST* proto = new PrototypeAST("",args);
            ExprAST* lambda_body = transform_to_lambda_calculus(func->body);
            lambda = new LambdaAST(proto,lambda_body);
        }

        LetAST* let = new LetAST(func->proto->name,lambda);
        std::cout << "After Lambda-Calculus Conversion: " << std::endl;
        let->print();

        return let;
    }
        break;
    case ExprAST::FunctionCall:
    {
        CallExprAST* func_call = (CallExprAST*)expr;

        std::cout << "Before Lambda-Calculus Conversion: " << std::endl;
        func_call->print();
        std::cout << std::endl;

        ExprAST* apply = new VariableExprAST(func_call->callee);

        for(int i=0;i<func_call->args.size();++i)
        {
            ExprAST* transformed_arg = transform_to_lambda_calculus(func_call->args.at(i));
            apply = new ApplyAST(apply,transformed_arg);
        }

        std::cout << "After Lambda-Calculus Conversion: " << std::endl;
        apply->print();
        std::cout << std::endl;

        return apply;
    }
        break;
    case ExprAST::BinaryOp:
    {
        BinaryExprAST* bin_op = (BinaryExprAST*)expr;
        ExprAST* lhs = transform_to_lambda_calculus(bin_op->lhs);
        ExprAST* rhs = transform_to_lambda_calculus(bin_op->rhs);
        return new BinaryExprAST(bin_op->op,lhs,rhs);
    }
    case ExprAST::Number:
    case ExprAST::Char:
    case ExprAST::True:
    case ExprAST::False:
    case ExprAST::Variable:
        //Lambda
    case ExprAST::Lambda:
    case ExprAST::Let:
    case ExprAST::LetRec:
    case ExprAST::Apply:
        return expr;
    case ExprAST::Prototype:
        out() << "Error Parsing AST, received PrototypeExprAST in lambda calculus conversion." << std::endl;
        correct_parsing = false;
        return expr;


    }
}

FunctionAST* convert_to_top_level_function(ExprAST* expr, llvm::Type* returnType)
{
    std::vector<std::string> args;
    std::vector<llvm::Type*> arg_types;
    std::stringstream ss;
    ss << "top-level";
    ss << top_level_counter++;
    //    PrototypeAST* proto = new PrototypeAST(ss.str(),args,arg_types,returnType);
    PrototypeAST* proto = new PrototypeAST(ss.str(),args);
    proto->argument_arity = arg_types;
    proto->return_arity = returnType;

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

ExprAST::AST_Type NumberExprAST::getAST_Type() const
{
    return ExprAST::Number;
}

void NumberExprAST::print() const
{
    std::cout << number << " ";
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

ExprAST::AST_Type BooleanExprAST::getAST_Type() const
{
    if(boolean)
    {
        return ExprAST::True;
    }
    else
    {
        return ExprAST::False;
    }
}

void BooleanExprAST::print() const
{
    std::cout << boolean << " ";
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

ExprAST::AST_Type CharExprAST::getAST_Type() const
{
    return ExprAST::Char;
}

void CharExprAST::print() const
{
    std::cout << character << " ";
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
    llvm::Function* calleeFunc = module->getFunction(callee);
    return calleeFunc->getReturnType();
}

ExprAST::AST_Type CallExprAST::getAST_Type() const
{
    return ExprAST::FunctionCall;
}

void CallExprAST::print() const
{
    std::cout << callee << "( ";
    for(int i=0;i<args.size();++i)
    {
        args.at(i)->print();
    }
    std::cout << ")";
}

//Prototypes for Functions
//llvm::FunctionType* PrototypeAST::functionType() const
//{
//    return FunctionType::get(FunctionType::getVoidTy(getGlobalContext()), FunctionType::getVoidTy(getGlobalContext()), true);
//}

llvm::Function* PrototypeAST::codeGen() const
{
//    FunctionType *functionType = FunctionType::get(return_arity,argument_arity, false);

    llvm ::Function* func = llvm::Function::Create(arity, llvm::Function::ExternalLinkage, name, module);

    std::cout << "proto param type: " << arity->getParamType(0)->getTypeID() << std::endl;

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

ExprAST::AST_Type PrototypeAST::getAST_Type() const
{
    return ExprAST::Prototype;
}

llvm::Type* PrototypeAST::type() const
{
    return return_arity;
}

void PrototypeAST::print() const
{

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

ExprAST::AST_Type FunctionAST::getAST_Type() const
{
    return ExprAST::Function;
}

void FunctionAST::print() const
{
    std::cout << proto->name;
    for(int i=0;i<proto->args.size();++i)
    {
        std::cout << "  " << proto->args.at(i);
    }
    std::cout << " = ";
    body->print();
    std::cout << std::endl;
}

//Variables
Value* VariableExprAST::codeGen() const
{
    //     Look this variable up in the function.
    Value *v = ExprAST::namedValues[Name];
    std::cout << "VariableExprAST: " << Name << " with type: " <<  v->getType()->getTypeID() << std::endl;
    return v ? v : errorV(std::string("Unknown variable name: ").append(Name).c_str());
}

llvm::Type* VariableExprAST::type() const
{
//    return arity;
    return llvm::Type::getDoubleTy(llvm::getGlobalContext());
}

ExprAST::AST_Type VariableExprAST::getAST_Type() const
{
    return ExprAST::Variable;
}

void VariableExprAST::print() const
{
    std::cout << Name << " ";
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

void BinaryExprAST::print() const
{
    lhs->print();
    switch (op) {
    case Add:
        std::cout << "+"; break;
    case Subtract:
        std::cout << "-"; break;
    case Multiply:
        std::cout << "*"; break;
    case Divide:
        std::cout << "/"; break;
    case Modulus:
        std::cout << "%"; break;
    case ShiftLeft:
        std::cout << "<<<"; break;
    case ShiftRight:
        std::cout << ">>>"; break;
    case BitAnd:
        std::cout << "&"; break;
    case BitOr:
        std::cout << "|"; break;
    case BitXOr:
        std::cout << "^|"; break;
    case Power:
        std::cout << "^"; break;
    case LessThan:
        std::cout << "<"; break;
    case GreaterThan:
        std::cout << ">"; break;
    case EqualTo:
        std::cout << "=="; break;
    case NotEqualTo:
        std::cout << "!="; break;
    case GreaterThanEq:
        std::cout << ">="; break;
    case LessThanEq:
        std::cout << "<="; break;
    case And:
        std::cout << "&&"; break;
    case Or:
        std::cout << "||"; break;
        //Error of some kind
    default:
        std::cout << "???";
    }

    std::cout << " ";

    rhs->print();
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

ExprAST::AST_Type BinaryExprAST::getAST_Type() const
{
    return ExprAST::BinaryOp;
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

//================================================
// Lambda-Calculus ASTs
//================================================
//Lambda
llvm::Function* LambdaAST::codeGen() const
{
//    namedValues.clear();
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

llvm::Type* LambdaAST::type() const
{
    return arity;
}

ExprAST::AST_Type LambdaAST::getAST_Type() const
{
    return ExprAST::Lambda;
}

void LambdaAST::print() const
{
    std::cout << "\\";
    for(int i=0;i<proto->args.size();++i)
    {
        std::cout << proto->args.at(i) << "  ";
    }
    std::cout << "-> ";
    body->print();
    std::cout << std::endl;
}

//Apply
llvm::Value* ApplyAST::codeGen() const
{
    llvm::Function* calleeFunc;
    std::vector<Value*> argsVector;

    calleeFunc = (llvm::Function*)lambda->codeGen();
    argsVector.push_back(arg->codeGen());
    if(!argsVector.back()) return NULL;

    return ExprAST::builder.CreateCall(calleeFunc, argsVector, "applytmp");
}

llvm::Type* ApplyAST::type() const
{
    return arity;
}

ExprAST::AST_Type ApplyAST::getAST_Type() const
{
    return ExprAST::Apply;
}

void ApplyAST::print() const
{
    std::cout << "apply( ";
    lambda->print();
    arg->print();
    std::cout << ") ";

}

//Let
llvm::Function* LetAST::codeGen() const
{
    namedValues.clear();

    std::vector<llvm::Type*> argument_arity;
//    argument_arity.push_back(llvm::Type::getVoidTy(llvm::getGlobalContext()));
    FunctionType *functionType = FunctionType::get(arity,argument_arity, false);
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
    }

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

llvm::Type* LetAST::type() const
{
    return arity;
}

ExprAST::AST_Type LetAST::getAST_Type() const
{
    return ExprAST::Let;
}

void LetAST::print() const
{
    std::cout << "let " << name << " = ";
    body->print();
}

}
