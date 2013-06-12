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
llvm::IRBuilder<> ExprAST::Builder = llvm::IRBuilder<>(llvm::getGlobalContext());

} // panopticon namespace
