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

namespace panopticon {

FunctionAST* convert_to_top_level_function(ExprAST* expr, llvm::Type *returnType);

// Expresions for numeric literals such as 0.3, 1.0, and 666
class NumberExprAST : public ExprAST
{
public:
    NumberExprAST(double number) : number(number) {}
    virtual llvm::Value* codeGen() const;
    virtual llvm::Type* type() const;

protected:
    double number;
};

class BooleanExprAST : public ExprAST
{
public:
    BooleanExprAST(bool boolean) : boolean(boolean) {}
    virtual llvm::Value* codeGen() const;
    virtual llvm::Type* type() const;

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

private:
    std::string callee;
    std::vector<ExprAST*> args;
};

// Represents a prototype for a function
class PrototypeAST
{
public:
    PrototypeAST(const std::string& name, const std::vector<std::string>& args,std::vector<llvm::Type*> argument_arity,llvm::Type* return_arity)
        : name(name), args(args),argument_arity(argument_arity),return_arity(return_arity) {}

    llvm::Function* codeGen() const;

    std::string name;
    std::vector<llvm::Type*> argument_arity;
    llvm::Type* return_arity;

protected:
    std::vector<std::string> args;
};

// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
  std::string Name;
public:
  VariableExprAST(const std::string &name) : Name(name) {}
  virtual llvm::Value* codeGen() const;
  virtual llvm::Type* type() const;
};

ExprAST* ParseNumberExpr(double number);
ExprAST* parseVariable(std::string name);

// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
  ExprAST *lhs, *rhs;
  int op;
public:
  enum Op{
      Add,
      Subtract,
      Multiply,
      Divide,
      Modulus,
      GreaterThan,
      LessThan,
      EqualTo,
      NotEqualTo,
      GreatherThanEq,
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
};

}

#endif // PARSE_AST_H
