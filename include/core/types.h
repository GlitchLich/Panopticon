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
    OK = 0,
    YIELD,
    ERRRUN,
    ERRSYNTAX,
    ERRMEM,
    ERRGCMM,
    ERRERR
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
    BOOL,
    NUMBER,
    STRING,
    FUNCTION,
    ARRAY,
    MAP,


    //THE FOLLOWING ARE FOR PARSING ONLY,
    //NOT TO BE USED AS LANGUAGE CONSTRUCTS
    ERROR,
    STATEMENT_LIST,
    VARIABLE,
    UNDECLARED_VARIABLE,
    OPERATION_TREE,
    OPERATION,
    ASSIGNMENT,
    LOCAL_VARIABLE_INDEX
};

// Forward declarations
struct Function;
struct object;
struct Nil { };

/* typedefs for types in Panopticon */
typedef double Number;
typedef std::vector<object> Array;
typedef std::unordered_map<std::string, object> Map;
typedef std::string String;
typedef bool Boolean;

// Data type union
union Data
{
    Number number;
    String* string;
    bool boolean;
    Function* function;
    Array* array;
    Map* map;
    bool (*operator_func)(object &,const object &,const object &);
};

struct object
{
    int type;
    Data data;
    object* scope;
};

struct Function
{
    std::stack<object> stack;
    std::unordered_map<std::string,object> heap;
    int num_arguments;
    std::vector<object> arguments;
    object body;
};

} // panopticon namespace

#endif // TYPES_H
