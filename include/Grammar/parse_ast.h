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

#ifndef PARSE_AST_H
#define PARSE_AST_H

#include "include/core/types.h"
#include "include/core/VM.h"
#include "llvm/Support/Casting.h"


//Type Deviations! Functions that return different types based on different case statements?
//Would it confuse the type checker too much?

namespace panopticon {

ExprAST* transform_to_lambda_calculus(ExprAST *expr);
FunctionAST* convert_to_top_level_function(ExprAST* expr, llvm::Type *returnType);

// Expresions for numeric literals such as 0.3, 1.0, and 666
class NumberExprAST : public ExprAST
{
public:

    NumberExprAST(double number) : number(number) {}
    virtual llvm::Value* codeGen() const;
    virtual llvm::Type* type() const;
    virtual AST_Type getAST_Type() const;
    void print() const;

protected:
    double number;
};

class BooleanExprAST : public ExprAST
{
public:
    BooleanExprAST(bool boolean) : boolean(boolean) {}
    virtual llvm::Value* codeGen() const;
    virtual llvm::Type* type() const;
    virtual AST_Type getAST_Type() const;
    void print() const;

protected:
    bool boolean;
};

// Expressions for a  single character such as 'l', '6', and '.'
class CharExprAST : public ExprAST
{
public:
    CharExprAST(const char& character) : character(character) {}
    virtual llvm::Value* codeGen() const;
    virtual llvm::Type* type() const;
    virtual AST_Type getAST_Type() const;
    void print() const;

protected:
    char character;
};

// Function call, such as print(1), parsed via the parentheses ()
class CallExprAST : public ExprAST
{
public:
    CallExprAST(const std::string& callee, std::vector<ExprAST*>& args) :
        callee(callee), args(args) {}

    virtual llvm::Value* codeGen() const;
    virtual llvm::Type* type() const;
    virtual AST_Type getAST_Type() const;
    void print() const;

    std::string callee;
    std::vector<ExprAST*> args;
};

// Represents a prototype for a function
class PrototypeAST : public ExprAST
{
public:
    PrototypeAST(const std::string& name, const std::vector<std::string>& args)
        : name(name), args(args){}

    llvm::Function* codeGen() const;
    llvm::Type* type() const;
    AST_Type getAST_Type() const;

    std::string name;
    std::vector<llvm::Type*> argument_arity;
    llvm::Type* return_arity;
    llvm::FunctionType* arity;
    std::vector<std::string> args;
    void print() const;
protected:

};

// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {

public:
  VariableExprAST(const std::string &name) : Name(name) {}
  virtual llvm::Value* codeGen() const;
  virtual llvm::Type* type() const;
  virtual AST_Type getAST_Type() const;
  void print() const;
  std::string Name;

  llvm::Type* arity;
};

ExprAST* ParseNumberExpr(double number);
ExprAST* parseVariable(std::string name);

// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
public:
  enum Op{
      Add,
      Subtract,
      Multiply,
      Divide,
      Modulus,
      Power,
      GreaterThan,
      LessThan,
      EqualTo,
      NotEqualTo,
      GreaterThanEq,
      LessThanEq,
      And,
      Or,
      ShiftLeft,
      ShiftRight,
      BitAnd,
      BitOr,
      BitXOr
  };
  BinaryExprAST(int op, ExprAST *lhs, ExprAST *rhs)
    : op(op), lhs(lhs), rhs(rhs) {}
  virtual llvm::Value* codeGen() const;
  virtual llvm::Type* type() const;
  virtual AST_Type getAST_Type() const;
  void print() const;

  ExprAST *lhs, *rhs;
  int op;
};




//================================================
// Lambda-Calculus ASTs
//================================================
class LambdaAST : public ExprAST
{
public:
    LambdaAST(PrototypeAST* proto, ExprAST* body)
        : proto(proto), body(body) {}

    virtual llvm::Function* codeGen() const;
    virtual llvm::Type* type() const;
    virtual AST_Type getAST_Type() const;
    void print() const;

    PrototypeAST* proto;
    ExprAST* body;

    llvm::Type* arity;
};

//Apply, can be used on LetAST's or LambdaAST's
class ApplyAST : public ExprAST
{
public:
    ApplyAST(ExprAST* lambda, ExprAST* arg) :
        lambda(lambda), arg(arg)
    {

    }

    virtual llvm::Value* codeGen() const;
    virtual llvm::Type* type() const;
    virtual AST_Type getAST_Type() const;
    void print() const;

    ExprAST* lambda;
    ExprAST* arg;
    llvm::Type* arity;
};


// Let Expression, without in
class LetAST : public ExprAST
{
public:
    LetAST(std::string name, ExprAST* body)
        : name(name), body(body) {}

    llvm::Function* codeGen() const;
    llvm::Type* type() const;
    AST_Type getAST_Type() const;
    void print() const;

    std::string name;
    ExprAST* body;
    llvm::Type* arity;
};


}

#endif // PARSE_AST_H
