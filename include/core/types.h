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

#ifndef TYPES_H
#define TYPES_H

// llvm
#include <llvm/Analysis/Verifier.h>
#include <llvm/DerivedTypes.h>
#include <llvm/IRBuilder.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

// stl
#include <vector>
#include <unordered_map>
#include <stack>
#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "core/errors.h"

// local
#include <list>

//#define BRAUN_TREE 1
#define TWO_THREE_TREE 1

namespace panopticon
{

// thread status
enum ThreadStatus
{
    OKRUN = 0,
    YIELD,
    ERRRUN,
    ERRSYNTAX,
    ERRMEM,
    ERRGCMM,
    ERRERR
};

enum RESULT
{
    OK,
    ERR,
    VARIABLE_NOT_FOUND,
    VARIABLE_ALREADY_BOUND
};

// functions that read/write blocks when loading/dumping Panopticon chunks
// typedef const char*  (*Reader) (State* P, void* ud, size_t* sz);
// typedef int (*Writer) (State* P, const void* p, size_t sz, void* ud);


// prototype for memory-allocation functions
typedef void*  (*Alloc) (void* ud, void* ptr, size_t osize, size_t nsize);

typedef struct State State;

typedef int (*CFunction) (State* P);


// basic types
enum Type
{
    NIL = 0, // 0
    BOOL,// 1
    NUMBER,// 2
    STRING,// 3
    FUNCTION,// 4
    ARRAY,// 5
    DICTIONARY,// 6
    LIST,// 7
    TRIE, // 8

    //THE FOLLOWING ARE FOR INTERNAL USE ONLY,
    //NOT TO BE USED AS LANGUAGE CONSTRUCTS
    ERROR,// 9
    STATEMENT_LIST,// 10
    VARIABLE,// 11 CHANGING THIS TO TYPE UNSIGNED LONG LONG
    UNDECLARED_VARIABLE,// 12 CHANGING THIS TO TYPE UNSIGNED LONG LONG
    OPERATION_TREE,// 13
    OPERATION,// 14
    UNARY_OPERATION, // 15
    ASSIGNMENT,//16
    GUARD,// 17
    FUNCTION_BODY, // 18 Used to prevent further parsing by the stack, enables lazy evaluation
    FUNCTION_ARG_NAMES, // 19 Used to pass argument names to functions for composition
    FUNCTION_ARG_VALUES, // 20 Used to pass argument values to functions for calling
    VOID, // 21, Use to prevent return on the stack
    CODE_BLOCK, // 22 Denotes several expression in a row
    PRIMITIVE, // 23
    CONDITION_TREE, // 24
    CONDITION_BRANCH, // 25
    NO_EXPANSION_OPERATION, // 26 For those operations that you DON'T want to multichannel expand
    UNARY_NO_EXPANSION_OPERATION, // 27 For those unary operations that you don't want to expand.
    PATTERN, // 28 for pattern matching
    HEAD, // 29 For Arrays/List sorting/construction
    TAIL, // 30 For Arrays/List sorting/construction
    FAILED_CONDITION, // 31 Condition test failed
    EMPTY_LIST, // 32 Signifies empty list.
    FT_SINGLE, // 33 for 23FingerTrees
    FT_DEEP, // 34 for 23FingerTrees
    FT_DIGIT, // 35 for 23FingerTrees
    FT_ELEMENT, // 36 for 23FingerTrees
    FT_NODE2, // 37 for 23 FingerTrees
    FT_NODE3, // 38 for 23 FingerTrees

    //New Thunk Stuff?
    FUNCTION_DECLARATION,
    FUNCTION_CALL,
    IDENTIFIER,
    LAMBDA,
    RECURSIVE_CALL,
    CASE,
    THUNK
};

std::string type_string(Type type);

// Forward declarations
struct Function;
struct Primitive;
struct object;
struct Nil { };

#ifdef TWO_THREE_TREE
struct TwoThreeFingerTree;
typedef TwoThreeFingerTree List;
#else
struct List;
#endif

namespace trie
{
    struct Trie; // Forward declaration
}

/* typedefs for types in Panopticon */
//typedef double Number;
typedef double Number;
//typedef std::vector<object> Array;
typedef std::deque<object> Array;
typedef std::unordered_map<unsigned long long, object> Dictionary;
typedef std::string String;
typedef bool Boolean;
typedef bool (*operator_function) (object &, const object &, const object &);
typedef bool (*unary_operator_function) (object &, const object &);
typedef bool (*primitive_function) (object&, const Array& arguments);

//Thunks
typedef std::deque<object> Thunk;
struct Function_Declaration;
struct Function_Call;
struct Identifier;
struct Lambda;
struct Recursive_call;
struct Case;


//typedef unsigned long long Variable;
typedef uint32_t Variable;

// Data type union
union Data
{
    Number number;
    String* string;
    bool boolean;
    Function* function;
    Array* array;
    List* list;
    trie::Trie* trie;
    Dictionary* dictionary;
    operator_function operator_func;
    unary_operator_function unary_operator_func;
    Primitive* primitive;
    Thunk* thunk;
    //Only to be used for variable indentification!
    Variable variable_number;
};

// Constants
#define ALIVE true
#define DEAD false
extern const Data EMPTY_DATA;
extern const object EMPTY_OBJECT;

struct object
{
    Data data;
    bool* alive; // Handle to alive value, needs to be pointer because the object itself is pass by value. Used for Garbage Collection.
    Type type;
};

namespace typing
{

//Type Inference
struct TypeVariable;
struct PolymorphicOperator;

struct ParseError
{
    unsigned long long name;
};

struct TypeError
{
    unsigned long long name;
};

enum OperatorTypes{TYPE_VARIABLE,Null,MONO,POLY,FUNC,PARSE_ERROR,TYPE_ERROR,NONE,TYPE_OPERATOR};

union OpType
{
    PolymorphicOperator* type_op;
    TypeVariable* type_var;
    ParseError parse_error;
    TypeError type_error;
};

struct TypeOperator
{
    int type;
    OpType data;
};

}

//Functions and Primitives
struct Function
{
    Variable name;
    Dictionary heap;
    int num_arguments;
    Array arguments;
    object body;
    bool evaluated;
    Thunk thunk_body;
    typing::TypeOperator arity;
};

struct Primitive
{
    Variable name;
    Dictionary heap;
    int num_arguments;
    Array arguments;
    primitive_function p_func;
    typing::TypeOperator arity;
};

/////////////////////////////////////////
/// llvm compilation classes and types
/////////////////////////////////////////

// Base class for expression nodes
class ExprAST
{
public:
    virtual ~ExprAST() {}
    virtual llvm::Value* codeGen() = 0;

    // Error handling
    llvm::Value* errorV(const char* str)
    {
        std::cerr << str << std::endl;
        return 0;
    }

    static llvm::Module* module;
    static llvm::IRBuilder<> Builder;
    static std::unordered_map<std::string, llvm::Value*> namedValues;
};

// Expresions for numeric literals such as 0.3, 1.0, and 666
class NumberExprAST : public ExprAST
{
public:
    NumberExprAST(double number) : number(number) {}
    virtual llvm::Value* codeGen();

protected:
    double number;
};

// Expressions for a  single character such as 'l', '6', and '.'
class CharExprAST : public ExprAST
{
public:
    CharExprAST(const char& character) : character(character) {}
    virtual llvm::Value* codeGen();

protected:
    char character;
};

// Represents a prototype for a function
class PrototypeAST
{
public:
    PrototypeAST(const std::string& name, std::vector<ExprAST*>& args)
        : name(name), args(args) {}

protected:
    std::string name;
    std::vector<ExprAST*> args;
};

// Expression class for functions themselves
class FunctionAST : public ExprAST
{
public:
    FunctionAST(PrototypeAST* proto, ExprAST* body)
        : proto(proto), body(body) {}

    virtual llvm::Value* codeGen();

protected:
    PrototypeAST* proto;
    ExprAST* body;
};

} // panopticon namespace

#endif // TYPES_H
