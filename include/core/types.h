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

#include <vector>
#include <unordered_map>
#include <stack>
#include <string>
#include <cstring>
#include "core/errors.h"

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
    NIL = 0,
    BOOL,//1
    NUMBER,//2
    STRING,//3
    FUNCTION,//4
    ARRAY,//5
    DICTIONARY,//6

    //THE FOLLOWING ARE FOR INTERNAL USE ONLY,
    //NOT TO BE USED AS LANGUAGE CONSTRUCTS
    ERROR,//7
    STATEMENT_LIST,//8
    VARIABLE,//9 CHANGING THIS TO TYPE UNSIGNED LONG LONG
    UNDECLARED_VARIABLE,//10 CHANGING THIS TO TYPE UNSIGNED LONG LONG
    OPERATION_TREE,//11
    OPERATION,//12
    UNARY_OPERATION, // 13
    ASSIGNMENT,//14
    GUARD,//15
    FUNCTION_BODY, //16 Used to prevent further parsing by the stack, enables lazy evaluation
    FUNCTION_ARG_NAMES, // 17 Used to pass argument names to functions for composition
    FUNCTION_ARG_VALUES, // 18 Used to pass argument values to functions for calling
    VOID, // 19, Use to prevent return on the stack
    CODE_BLOCK, //20 Denotes several expression in a row
    PRIMITIVE, // 21
    CONDITION_TREE, //22
    CONDITION_BRANCH, //23
    NO_EXPANSION_OPERATION, //24 For those operations that you DON'T want to multichannel expand
    UNARY_NO_EXPANSION_OPERATION, //25 For those unary operations that you don't want to expand.
    PATTERN, //26 for pattern matching
    HEAD, //27 For Arrays/List sorting/construction
    TAIL, //28 For Arrays/List sorting/construction
    FAILED_CONDITION //29 Condition test failed
};

std::string type_string(Type type);

// Forward declarations
struct Function;
struct Primitive;
struct object;
struct Nil { };

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
//typedef unsigned long long Variable;
typedef unsigned int Variable;

// Data type union
union Data
{
    Number number;
    String* string;
    bool boolean;
    Function* function;
    Array* array;
    Dictionary* dictionary;
    operator_function operator_func;
    unary_operator_function unary_operator_func;
    Primitive* primitive;

    //Only to be used for variable indentification!
    Variable variable_number;
};

// const bool ALIVE = true;
// const bool DEAD = false;

#define ALIVE true
#define DEAD false

struct object
{
    Type type;
    Data data;
    bool* alive; // Handle to alive value, needs to be pointer because the object itself is pass by value. Used for Garbage Collection.
};

struct Function
{
//    String name;
    Variable name;
    Dictionary heap;
    int num_arguments;
    Array arguments;
    object body;
};

struct Primitive
{
    Variable name;
    Dictionary heap;
    int num_arguments;
    Array arguments;
    primitive_function p_func;
};

} // panopticon namespace

#endif // TYPES_H
