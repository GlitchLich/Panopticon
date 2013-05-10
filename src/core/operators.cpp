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

#include <math.h>
#include <iostream>

#include "include/core/operators.h"
#include "include/core/heap.h"
#include "include/Grammar/plus.h"
#include "include/Grammar/minus.h"
#include "include/Grammar/divide.h"
#include "include/core/function.h"
#include "include/core/stack.h"

#include <algorithm>

namespace panopticon
{
#undef STRING
#undef NUM
#undef BOOL
#undef ARRAY

//==================
//GENERAL
//==================
object copy_object(const object& original)
{
    object copy;
    copy.type = original.type;
    switch(original.type)
    {
    case panopticon::OPERATION:
    case panopticon::NUMBER:
    case panopticon::BOOL:
        copy = original;
        break;
    case panopticon::STRING:
        copy.data.string = new String(*original.data.string);
        break;
    case panopticon::OPERATION_TREE:
    case panopticon::ARRAY:
        copy.data.array = new Array();
        //        copy.data.array->reserve(original.data.array->size());
        for(int i=0;i<original.data.array->size();++i)
        {
            copy.data.array->push_back(copy_object(original.data.array->at(i)));
        }
        break;

    default:
        copy = original;
        break;
    }

    return copy;
}

object create_void_tree()
{
    object void_tree;
    void_tree.type = OPERATION_TREE;
    object v;
    v.type = VOID;
    void_tree.data.array = new Array();
    void_tree.data.array->push_back(v);
    return void_tree;
}

//object de_tree(object &obj)
//{
//    object new_object;
//    out() << "object de_tree(object &obj): obj.type: " << obj.type << std::endl;
//    if(obj.type==panopticon::OPERATION_TREE)
//    {
//        if(obj.data.array->size()==1)
//        {
//            return obj.data.array->at(0);
//        }
//        else
//        {
//            new_object.type = ARRAY;
//            new_object.data.array = new Array();
//            new_object.data.array->reserve(obj.data.array->size());
//            for(int i=0;i<obj.data.array->size();++i)
//            {
//                new_object.data.array->push_back(de_tree(obj.data.array->at(i)));
//            }
//        }
//    }
//    else if(obj.type==ARRAY||obj.type==STATEMENT_LIST)
//    {
//        new_object.type = ARRAY;
//        new_object.data.array = new Array();
//        new_object.data.array->reserve(obj.data.array->size());
//        for(int i=0;i<obj.data.array->size();++i)
//        {
//            new_object.data.array->push_back(de_tree(obj.data.array->at(i)));
//        }
//    }
//    return new_object;
//}

bool delete_array(object& a)
{
    for(int i=0;i<a.data.array->size();++i)
    {
        panopticon::object& b = a.data.array->at(i);
        switch(b.type)
        {
        case OPERATION:
        case BOOL:
        case NUMBER:
            break;
        case STRING:
            delete b.data.string;
            break;
        case OPERATION_TREE:
        case ARRAY:
            delete_array(b);
            break;
        case DICTIONARY:
            delete_dictionary(b);
            break;
        }
    }
    delete a.data.array;
}

bool delete_object(object& obj)
{
    switch(obj.type)
    {
    case OPERATION:
    case optic::NUMBER:
    case optic::BOOL:
        break;
    case optic::STRING:
        delete obj.data.string;
        break;
    case OPERATION_TREE:
    case optic::ARRAY:
        panopticon::delete_array(obj);
        break;
    }
}

bool print_array(const object &A, int arrayNum,bool isTree)
{
    if(arrayNum!=0)
    {
        out() << " ";
    }
    if(isTree)
    {
        out() << "{";
    }
    else
    {
        out() << "[";
    }
    for(int i=0;i<A.data.array->size();++i)
    {
        panopticon::object& B = A.data.array->at(i);
        switch(B.type)
        {
        case NUMBER:
            out() << " " << B.data.number;
            break;
        case STRING:
            out() << " " << *(A.data.array->at(i).data.string);
            break;
        case BOOL:
            if(B.data.boolean)
            {
                out() << " true";
            }
            else
            {
                out() << " false";
            }
            break;
        case OPERATION_TREE:
            print_array(B,arrayNum+1,true);
            break;
        case ARRAY:
            print_array(B,arrayNum+1);
            break;
        case panopticon::OPERATION:
            out() << " Operator";
            break;
        case UNARY_NO_EXPANSION_OPERATION:
        case panopticon::UNARY_OPERATION:
            out() << " Unary_Operator";
            break;
        case panopticon::NO_EXPANSION_OPERATION:
            out() << " NoExpandOperator";
            break;
        case panopticon::VARIABLE:
            out() << " " << *B.data.string;
            break;
        case panopticon::UNDECLARED_VARIABLE:
            out() << " " << *B.data.string;
            break;
        }
    }
    if(isTree)
    {
        out() << " }";
    }
    else
    {
        out() << " ]";
    }
    if(arrayNum==0)
    {
        out() << std::endl;
    }
}

bool print_object(const object &A)
{
    switch(A.type)
    {
    case panopticon::FUNCTION:
        // -1 arguments because it counts itself as an argument internally
        out() << "Function with " << (A.data.function->num_arguments - 1) << " arguments and " << A.data.function->body.data.array->size() << " body objects" << std::endl;
    case panopticon::NUMBER:
        out() << A.data.number << std::endl;
        break;
    case panopticon::STRING:
        out() << *A.data.string << std::endl;
        break;
    case panopticon::BOOL:
        if(A.data.boolean)
        {
            out() << "true" << std::endl;
        }
        else
        {
            out() << "false" << std::endl;
        }
        break;
    case panopticon::ARRAY:
        panopticon::print_array(A);
        break;
    case panopticon::DICTIONARY:
        print_dictionary(A);
        break;
    case panopticon::VARIABLE:
    case panopticon::UNDECLARED_VARIABLE:

        object result;
        if(get_variable(A.data.string,&result) == OK)
        {
            if(result.type==FUNCTION)
            {
                if(result.data.function->arguments.size() == 1)
                {
                    object arguments; // empty, won't be used by call_function so no need to initialize
                    call_function(result, A, arguments);
                    out() << *A.data.string << ": " << print_object(result);
                }

                else
                {
                    out() << "Function: " << *A.data.string << std::endl;
                    out() << "with arguments: " << result.data.function->arguments.size() << std::endl;
                }
            }
            else
            {
                out() << *A.data.string << ": " << print_object(result);
            }

        }

        else
        {
            out() << "Undeclared Variable: " << *A.data.string << std::endl;
        }

        break;

    case panopticon::OPERATION_TREE:
        panopticon::print_array(A,0,true);
        break;
    case panopticon::OPERATION:
        out() << "Operator" << std::endl;
        break;
    case UNARY_NO_EXPANSION_OPERATION:
    case panopticon::UNARY_OPERATION:
        out() << "Unary_Operator" << std::endl;
        break;
    case panopticon::NO_EXPANSION_OPERATION:
        out() << "NoExpandOperator" << std::endl;
        break;
    }
}

bool unary_print_object(object &A, const object &B)
{
    A = copy_object(B);
    print_object(B);
}

bool create_dictionary(object& dict)
{
    dict.data.dictionary = new Dictionary();
    dict.type = DICTIONARY;
    return true;
}

bool delete_dictionary(object& dict)
{
    Dictionary::iterator iter = dict.data.dictionary->begin();

    while(iter != dict.data.dictionary->end())
    {
        panopticon::object& value = iter->second;

        switch(value.type)
        {
        case STRING:
            delete value.data.string;
            break;

        case OPERATION_TREE:
        case ARRAY:
            delete_array(value);

        case DICTIONARY:
            delete_dictionary(value);
            break;

        default:
            break;
        }

        ++iter;
    }

    dict.data.dictionary->clear();
    delete dict.data.dictionary;
    return true;
}

bool print_dictionary(const object& dict)
{
    Dictionary::iterator iter = dict.data.dictionary->begin();

    out() << "{ ";

    while(iter != dict.data.dictionary->end())
    {
        out() << "\"" << iter->first << "\" : ";

        panopticon::object& value = iter->second;

        switch(value.type)
        {
        case STRING:
            out() << value.data.string;
            break;

        case NUMBER:
            out() << value.data.number;
            break;

        case BOOL:
            out() << value.data.boolean;
            break;

        case OPERATION_TREE:
        case ARRAY:
            print_array(value);

        case DICTIONARY:
            print_dictionary(value);
            break;

        case FUNCTION:
            out() << "Function";
            break;

        case NIL:
            out() << "Nil";
            break;

        default:
            break;
        }

        out() << " ";

        ++iter;
    }

    out() << "}" << std::endl;
    return true;
}

bool dictionary_keys(object& keys, const object& dict)
{
    keys.type = ARRAY;
    Array* key_array = new Array();
    Dictionary::iterator iter = dict.data.dictionary->begin();

    while(iter != dict.data.dictionary->end())
    {
        object key;
        key.type = STRING;
        key.data.string = new String(iter->first);
        key_array->push_back(key);
        ++iter;
    }

    keys.data.array = key_array;
    return true;
}

bool dictionary_values(object& values, const object& dict)
{
    values.type = ARRAY;
    Array* value_array = new Array();
    Dictionary::iterator iter = dict.data.dictionary->begin();

    while(iter != dict.data.dictionary->end())
    {
        value_array->push_back(iter->second);
        ++iter;
    }

    values.data.array = value_array;
    return true;
}

bool dictionary_lookup(object& value, const object& dict, const object& key)
{
    if(key.type != STRING)
    {
        out() << "Error: Dictionary key must be a String." << std::endl;
        correct_parsing = false;
        return false;
    }

    //If the object is a string, attempt to fetch it.
    if(dict.type == STRING||dict.type == UNDECLARED_VARIABLE)
    {
        std::cout << "UV" << std::endl;
        object result;
        if(get_variable(dict.data.string,&result)==OK)
        {
            if(result.type==DICTIONARY)
            {
                return dictionary_lookup(value,result,key);
            }
            else
            {
                value.type = NIL;
                out() << "Error: Cannot call a Dictionary lookup on a non-Dictionary object." << std::endl;
                out() << "Object with Dictionary lookup called on it: " << dict.data.string->c_str() << std::endl;
                correct_parsing = false;
                return false;
            }
        }
        else
        {
            value.type = NIL;
            out() << "Error: the variable \'" << dict.data.string->c_str() << "\'' has not been declared." << std::endl;
            correct_parsing = false;
            return false;
        }

    }

    Dictionary::iterator find = dict.data.dictionary->find(*key.data.string);
    if(find != dict.data.dictionary->end())
    {
        value = copy_object(find->second);
    }
    else
    {
        value.type = NIL;
        out() << "No object found with key \'" << *key.data.string << "\'." << std::endl;
        correct_parsing = false;
        return false;
    }
    return true;
}

bool dictionary_contains(object &boolean, const object &dict, const object &key)
{
    if(key.type != STRING)
    {
        out() << "Dictionary key must be a String." << std::endl;
        correct_parsing = false;
        return false;
    }

    boolean.type = BOOL;
    boolean.data.boolean = dict.data.dictionary->find(*key.data.string) != dict.data.dictionary->end();
    return true;
}

bool concatenate_arrays(object &a,object b, object c)
{
    //    a.data.array->reserve(b.data.array->size() + c.data.array->size());
    for(int i=0;i<b.data.array->size();++i)
    {
        panopticon::object& d = b.data.array->at(i);
        switch(d.type)
        {
        case NUMBER:
            a.data.array->push_back(d);
            break;
        case STRING:
            a.data.array->push_back(copy_object(d));
            break;
        case BOOL:
            a.data.array->push_back(d);
            break;
        case ARRAY:
            a.data.array->push_back(copy_object(d));
            break;
        }
    }

    for(int i=0;i<c.data.array->size();++i)
    {
        panopticon::object& d = b.data.array->at(i);
        switch(d.type)
        {
        case NUMBER:
            a.data.array->push_back(d);
            break;
        case STRING:
            a.data.array->push_back(copy_object(d));
            break;
        case BOOL:
            a.data.array->push_back(d);
            break;
        case ARRAY:
            a.data.array->push_back(copy_object(d));
            break;
        }
    }
}


bool create_array(object &a)
{
    a.data.array = new Array();
}

bool object_operator_array(object& a,const object& obj,const object& array, operator_function func)
{
    a.type = panopticon::ARRAY;
    a.data.array = new Array();
    //    a.data.array->reserve(array.data.array->size());

    for(int i=0;i<array.data.array->size();++i)
    {
        object newObject;
        func(newObject,obj,array.data.array->at(i));
        a.data.array->push_back(newObject);
    }
}

bool array_operator_object(object& a,const object& array,const object& obj, operator_function func)
{
    a.type = panopticon::ARRAY;
    a.data.array = new Array();
    //    a.data.array->reserve(array.data.array->size());

    for(int i=0;i<array.data.array->size();++i)
    {
        object newObject;
        func(newObject,array.data.array->at(i),obj);
        a.data.array->push_back(newObject);
    }
}

bool array_operator_array(object& a,const object& array1,const object& array2, operator_function func)
{
    a.type = panopticon::ARRAY;
    //    a.data.array = new std::vector<object>();
    int size = 0;
    if(array1.data.array->size()>array2.data.array->size())
    {
        size = array1.data.array->size();
    }
    else
    {
        size = array2.data.array->size();
    }
    //    a.data.array->reserve(size);

    for(int i=0;i<size;++i)
    {
        object& array1Object = array1.data.array->at(i%array1.data.array->size());
        object& array2Object = array2.data.array->at(i%array2.data.array->size());
        object newObject;
        func(newObject,array1Object,array2Object);
        a.data.array->push_back(newObject);
    }
}

bool create_tree(object&a,const object& obj)
{
    a.type = OPERATION_TREE;
    a.data.array = new Array();
    if(obj.type==OPERATION_TREE)
    {
        a = obj;
    }
    else
    {
        a.data.array->push_back(obj);
    }

}

bool store_operations(object& a,const object& obj1,unary_operator_function func,bool expand)
{
    a.type = OPERATION_TREE;
    a.data.array = new Array();

    int size = 1;

    if(obj1.type==OPERATION_TREE)
    {
        size+=obj1.data.array->size();
    }
    else
    {
        size++;
    }

    //    a.data.array->reserve(size);
    object op_func;
    if(expand)
    {
        op_func.type = UNARY_OPERATION;
    }
    else
    {
        op_func.type = UNARY_NO_EXPANSION_OPERATION;
    }
    op_func.data.unary_operator_func = func;
    a.data.array->push_back(op_func);

    if(obj1.type==OPERATION_TREE)
    {
        for(int i=0;i<obj1.data.array->size();++i)
        {
            a.data.array->push_back(obj1.data.array->at(i));
        }
    }
    else
    {
        a.data.array->push_back(obj1);
    }
}

bool store_operations(object& a,const object& obj1,const object& obj2,bool expand)
{
    a.type = OPERATION_TREE;
    a.data.array = new Array();

    int size = 0;

    if(obj1.type==OPERATION_TREE)
    {
        size+=obj1.data.array->size();
    }
    else
    {
        size++;
    }

    if(obj2.type==OPERATION_TREE)
    {
        size+=obj2.data.array->size();
    }
    else
    {
        size++;
    }

    object op_func;
    if(expand)
    {
        op_func.type = OPERATION;
    }
    else
    {
        op_func.type = NO_EXPANSION_OPERATION;
    }
    op_func.data.operator_func = &serial;
    a.data.array->push_back(op_func);

    if(obj1.type==OPERATION_TREE)
    {
        for(int i=0;i<obj1.data.array->size();++i)
        {
            a.data.array->push_back(obj1.data.array->at(i));
        }
    }
    else
    {
        a.data.array->push_back(obj1);
    }

    if(obj2.type==OPERATION_TREE)
    {
        for(int i=0;i<obj2.data.array->size();++i)
        {
            a.data.array->push_back(obj2.data.array->at(i));
        }
    }
    else
    {
        a.data.array->push_back(obj2);
    }
}

bool store_operations(object& a,const object& obj1,const object& obj2, operator_function func, bool expand)
{
    a.type = OPERATION_TREE;
    a.data.array = new Array();
    int size = 1;

    if(obj1.type==OPERATION_TREE)
    {
        size+=obj1.data.array->size();
    }
    else
    {
        size++;
    }

    if(obj2.type==OPERATION_TREE)
    {
        size+=obj2.data.array->size();
    }
    else
    {
        size++;
    }

    //    a.data.array->reserve(size);
    object op_func;
    if(expand)
    {
        op_func.type = OPERATION;
    }
    else
    {
        op_func.type = NO_EXPANSION_OPERATION;
    }
    op_func.data.operator_func = func;
    a.data.array->push_back(op_func);

    if(obj1.type==OPERATION_TREE)
    {
        for(int i=0;i<obj1.data.array->size();++i)
        {
            a.data.array->push_back(obj1.data.array->at(i));
        }
    }
    else
    {
        a.data.array->push_back(obj1);
    }

    if(obj2.type==OPERATION_TREE)
    {
        for(int i=0;i<obj2.data.array->size();++i)
        {
            a.data.array->push_back(obj2.data.array->at(i));
        }
    }
    else
    {
        a.data.array->push_back(obj2);
    }
}

bool object_operator_object(object& a, object& b, object& c, operator_function func)
{
    func(a, b, c);
    delete_object(b);
    delete_object(c);
}

bool resolve_stack_from_parser(const object& operation_tree, bool resolve_entire_stack)
{
    if(operation_tree.type == OPERATION_TREE)
    {
        if(operation_tree.data.array->size() > 1)
        {
            std::reverse_copy(operation_tree.data.array->begin(), operation_tree.data.array->end(), std::inserter(optic_stack, optic_stack.end()));
        }

        else if(operation_tree.data.array->size() == 1)
        {
            optic_stack.push_back(operation_tree.data.array->at(0));
        }

        else
        {
            out() << "Error: No operations to put on the stack." << std::endl;
            correct_parsing = false;
        }
    }

    if(resolve_entire_stack)
        evaluate_stack();
    else
        evaluate_top();
}

bool parse_operations(object& a, const object& b, const object& c, operator_function func)
{
    store_operations(a, b, c, func);
}

/**
 * @brief create_function
 * @param A
 * @param B Arguments for the Function. First argument is the function name (unless anonymous)
 * @param C Body of the function, stored as an operation_tree.
 * @return
 */
bool create_function(object &A, const object &B, const object &C)
{
    A.type = FUNCTION;
    Function* function = new Function;

    if(B.type == FUNCTION_ARG_NAMES)
    {
        function->num_arguments = B.data.array->size();
        for(int i = 0; i < function->num_arguments; ++i)
        {
            function->arguments.push_back(copy_object(B.data.array->at(i)));
        }

        function->name = std::string(*B.data.array->at(0).data.string);
    }

    else if(B.type == STRING)
    {
        function->num_arguments = 0;
        function->arguments.push_back(B);
        function->name = std::string(*B.data.string);
    }

    function->body = C;
    function->body.type = OPERATION_TREE;
    A.data.function = function;
}

bool call_function_array(object& A, const object& B, const object& C)
{
    optic_stack.push_back(C);
    optic_stack.push_back(B);
    object call;
    call.type = OPERATION;
    call.data.operator_func = call_function;
    optic_stack.push_back(call);
    evaluate_top();
    A = optic_stack.back();
    optic_stack.pop_back();
}

/**
* @brief call_function
* @param A = Result
* @param B = Function name (STRING)
* @param C = Function Arguments (ARRAY, zero indexed!)
* @return
*/
bool call_function(object& A, const object& B, const object& C)
{
    object function;

    switch(B.type)
    {
    case VARIABLE:
    case UNDECLARED_VARIABLE:
    case STRING:

        if(get_variable(B.data.string, &function) != OK)
        {
            out() << "Unable to find function: " << B.data.string->c_str() << " in current scope" << std::endl;
            correct_parsing = false;
            return false;
        }

        if(function.type == ARRAY)
        {
            return call_function_array(A, function, C);
        }

        else if(function.type != FUNCTION)
        {
            return false;
        }

        break;

    case FUNCTION:
        function = B;
        break;

    default:
        out() << "Object is not a function and is not callable: ";
        out() << "OBJECT TYPE: " << B.type << " ";
        print_object(B);
        return false;
        break;
    }

    std::string function_name = function.data.function->name;
    std::cout << "FUNCTION NAME ";
    std::cout << function_name << std::endl;
    Dictionary context;
    context.insert(std::make_pair(function_name, function));

    if(function.data.function->arguments.size() > 1) // if it has any arguments
    {
        // iterate backwards through the argument list to put them on the stack, this way the resolve in the correct order when we collect them for mapping
        // we use arguments.size() - 2 because we don't want to count the function name which is included in the arguments array
        for(int i = function.data.function->arguments.size() - 2; i >= 0; --i)
        {
            object arg = C.data.array->at(i);
            optic_stack.push_back(arg);
        }

        // Collect the the results and map them to the local scope
        for(int i = 1; i < function.data.function->num_arguments && optic_stack.size() > 0; ++i)
        {
            evaluate_top();
            String arg_name = *function.data.function->arguments.at(i).data.string;
            context.insert(std::make_pair(arg_name, optic_stack.back()));
            optic_stack.pop_back();
        }
    }

    push_scope(&context);
    resolve_stack_from_parser(function.data.function->body, false);

    if(optic_stack.back().type == ARRAY)
    {
        object parse_array;
        parse_array.type = UNARY_OPERATION;
        parse_array.data.unary_operator_func = resolve_function_array;
        optic_stack.push_back(parse_array);
        evaluate_top();
    }

    A = optic_stack.back();
    optic_stack.pop_back();

    pop_scope();
    return true;
}

extern bool resolve_function_array(object& A, const object& B)
{
    if(B.type != FUNCTION)
    {
        optic_stack.push_back(B);
        evaluate_top();
        A = optic_stack.back();
        optic_stack.pop_back();
    }

    else
    {
        A = B;
    }
}

//======================================================================================
//OPERATORS
//======================================================================================

bool serial(object& A,const object& B,const object& C)
{
    A = C;
}

bool u_minus(object&A, const object& B)
{
    switch(B.type)
    {
    case panopticon::NUMBER:
        A=B;
        A.data.number*= -1;
        return true;
    case panopticon::STRING:
        out() << "Error: cannot call a unary minus operator on a String." << std::endl;
        correct_parsing = false;
        return false;
    case panopticon::BOOL:
        out() << "Error: cannot call a unary minus operator on a Boolean." << std::endl;
        correct_parsing = false;
        return false;
    }
}

bool plus(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case panopticon::NUMBER:
        number_plus(A,B,C);
        break;
    case panopticon::STRING:
        string_plus(A,B,C);
        break;
    case panopticon::BOOL:
        bool_plus(A,B,C);
        break;
    case panopticon::ARRAY:
        array_plus(A,B,C);
        break;
    }
}

bool minus(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        number_minus(A,B,C);
        break;
    case STRING:
        string_minus(A,B,C);
        break;
    case BOOL:
        bool_minus(A,B,C);
        break;
    case ARRAY:
        array_minus(A,B,C);
        break;
    }
}

bool divide(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = NUMBER;
            A.data.number = B.data.number/C.data.number;
            break;
        case STRING:
            out() << print_error(DivideStringError) << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << print_error(DivideBooolError) << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&divide);
            break;
        }
        break;
    case STRING:
        out() << print_error(DivideStringError) << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        out() << print_error(DivideBooolError) << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&divide);
            break;
        case STRING:
            out() << print_error(DivideStringError) << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << print_error(DivideBooolError) << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&divide);
            break;
        }
        break;
    }
}


bool multiply(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = NUMBER;
            A.data.number = B.data.number * C.data.number;
            break;
        case STRING:
            out() << print_error(MultiplyStringError) << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << print_error(MultiplyBoolError) << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&multiply);
            break;
        }
        break;
    case STRING:
        out() << print_error(MultiplyStringError) << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        out() << print_error(MultiplyBoolError) << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&multiply);
            break;
        case STRING:
            out() << print_error(DivideStringError) << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << print_error(DivideBooolError) << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&multiply);
            break;
        }
        break;
    }
}

bool modulo(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = NUMBER;
            A.data.number = fmod(B.data.number,C.data.number);
            break;
        case STRING:
            out() << print_error(ModStringError) << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << print_error(ModBoolError) << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&modulo);
            break;
        }
        break;
    case STRING:
        out() << print_error(ModStringError) << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        out() << print_error(ModBoolError) << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&modulo);
            break;
        case STRING:
            out() << print_error(ModStringError) << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << print_error(ModBoolError) << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&modulo);
            break;
        }
        break;
    }
}

bool value_pow(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = NUMBER;
            A.data.number = pow(B.data.number,C.data.number);
            break;
        case STRING:
            out() << print_error(PowStringError) << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << print_error(PowBoolError) << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&value_pow);
            break;
        }
        break;
    case STRING:
        out() << print_error(PowStringError) << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        out() << print_error(PowBoolError) << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&value_pow);
            break;
        case STRING:
            out() << print_error(PowStringError) << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << print_error(PowBoolError) << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&value_pow);
            break;
        }
        break;
    }
}

bool equal_to(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            A.data.boolean = B.data.number == C.data.number;
            break;
        case STRING:
            A.type = BOOL;
            A.data.boolean = false;
            break;
        case BOOL:
            A.type = BOOL;
            A.data.boolean = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&equal_to);
            break;
        }
        break;
    case STRING:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            A.data.boolean = false;
            break;
        case STRING:
            A.type = BOOL;
            A.data.boolean = (B.data.string->compare(*C.data.string)==0);
            break;
        case BOOL:
            A.type = BOOL;
            A.data.boolean = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&equal_to);
            break;
        }
        break;
    case BOOL:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            A.data.boolean = false;
            break;
        case STRING:
            A.type = BOOL;
            A.data.boolean = false;
            break;
        case BOOL:
            A.type = BOOL;
            A.data.boolean = B.data.boolean==C.data.boolean;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&equal_to);
            break;
        }
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            A.data.boolean = false;
            break;
        case STRING:
            A.type = BOOL;
            A.data.boolean = false;
            break;
        case BOOL:
            A.type = BOOL;
            A.data.boolean = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&equal_to);
            break;
        }
        break;
    }
}

bool not_equal_to(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            A.data.boolean = B.data.number != C.data.number;
            break;
        case STRING:
            A.type = BOOL;
            A.data.boolean = true;
            break;
        case BOOL:
            A.type = BOOL;
            A.data.boolean = true;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&not_equal_to);
            break;
        }
        break;
    case STRING:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            A.data.boolean = true;
            break;
        case STRING:
            A.type = BOOL;
            A.data.boolean = (B.data.string->compare(*C.data.string)!=0);
            break;
        case BOOL:
            A.type = BOOL;
            A.data.boolean = true;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&not_equal_to);
            break;
        }
        break;
    case BOOL:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            A.data.boolean = true;
            break;
        case STRING:
            A.type = BOOL;
            A.data.boolean = true;
            break;
        case BOOL:
            A.type = BOOL;
            A.data.boolean = B.data.boolean!=C.data.boolean;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&not_equal_to);
            break;
        }
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            A.data.boolean = true;
            break;
        case STRING:
            A.type = BOOL;
            A.data.boolean = true;
            break;
        case BOOL:
            A.type = BOOL;
            A.data.boolean = true;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&not_equal_to);
            break;
        }
        break;
    }
}

bool less_than(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            A.data.boolean = B.data.number < C.data.number;
            break;
        case STRING:
            out() << "Syntax error: A string cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: A bool cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&less_than);
            break;
        }
        break;
    case STRING:
        switch(C.type)
        {
        case STRING:
            A.type = BOOL;
            A.data.boolean =  B.data.string->size() < C.data.string->size();
            break;
        case ARRAY:
            object_operator_array(A,B,C,&less_than);
            break;
        default:
            out() << "Syntax error: A string cannot be greater than or less than a number, or a bool." << std::endl;
            correct_parsing = false;
            break;
        }
        break;
    case BOOL:
        out() << "Syntax error: A bool cannot be greater than or less than a number." << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&less_than);
            break;
        case STRING:
            array_operator_object(A,B,C,&less_than);
            break;
        case BOOL:
            out() << "Syntax error: A bool cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&less_than);
            break;
        }
        break;
    }
}

bool greater_than(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            A.data.boolean = B.data.number > C.data.number;
            break;
        case STRING:
            out() << "Syntax error: A string cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: A bool cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&greater_than);
            break;
        }
        break;
    case STRING:
        switch(C.type)
        {
        case STRING:
            A.type = BOOL;
            A.data.boolean =  B.data.string->size() > C.data.string->size();
            break;
        case ARRAY:
            object_operator_array(A,B,C,&greater_than);
            break;
        default:
            out() << "Syntax error: A string cannot be greater than or less than a number, or a bool." << std::endl;
            correct_parsing = false;
            break;
        }
        break;
    case BOOL:
        out() << "Syntax error: A bool cannot be greater than or less than a number." << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&greater_than);
            break;
        case STRING:
            array_operator_object(A,B,C,&less_than);
            break;
        case BOOL:
            out() << "Syntax error: A bool cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&greater_than);
            break;
        }
        break;
    }
}

bool lore(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            A.data.boolean = B.data.number <= C.data.number;
            break;
        case STRING:
            out() << "Syntax error: A string cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: A bool cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&lore);
            break;
        }
        break;
    case STRING:
        switch(C.type)
        {
        case STRING:
            A.type = BOOL;
            A.data.boolean =  B.data.string->size() <= C.data.string->size();
            break;
        case ARRAY:
            object_operator_array(A,B,C,&lore);
            break;
        default:
            out() << "Syntax error: A string cannot be greater than or less than a number, or a bool." << std::endl;
            correct_parsing = false;
            break;
        }
        break;
    case BOOL:
        out() << "Syntax error: A bool cannot be greater than or less than a number." << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&lore);
            break;
        case STRING:
            array_operator_object(A,B,C,&less_than);
            break;
        case BOOL:
            out() << "Syntax error: A bool cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&lore);
            break;
        }
        break;
    }
}

bool gore(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            A.data.boolean = B.data.number >= C.data.number;
            break;
        case STRING:
            out() << "Syntax error: A string cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: A bool cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&gore);
            break;
        }
        break;
    case STRING:
        switch(C.type)
        {
        case STRING:
            A.type = BOOL;
            A.data.boolean =  B.data.string->size() >= C.data.string->size();
            break;
        case ARRAY:
            object_operator_array(A,B,C,&gore);
            break;
        default:
            out() << "Syntax error: A string cannot be greater than or less than a number, or a bool." << std::endl;
            correct_parsing = false;
            break;
        }
        break;
    case BOOL:
        out() << "Syntax error: A bool cannot be greater than or less than a number." << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&gore);
            break;
        case STRING:
            array_operator_object(A,B,C,&gore);
            break;
        case BOOL:
            out() << "Syntax error: A bool cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&gore);
            break;
        }
        break;
    }
}

bool value_and(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            if(B.data.number>0&&C.data.number>0)
            {
                A.data.boolean = true;
            }
            else
            {
                A.data.boolean = false;
            }
            break;
        case STRING:
            out() << "Syntax error: A string is not a bool." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            A.type = BOOL;
            if(B.data.number>0&&C.data.boolean)
            {
                A.data.boolean = true;
            }
            else
            {
                A.data.boolean = false;
            }
            break;
        case ARRAY:
            object_operator_array(A,B,C,&value_and);
            break;
        }
        break;
    case STRING:
        out() << "Syntax error: A string is not a bool." << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            if(B.data.boolean&&C.data.number>0)
            {
                A.data.boolean = true;
            }
            else
            {
                A.data.boolean = false;
            }
            break;
        case STRING:
            out() << "Syntax error: A string is not a bool." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            A.type = BOOL;
            if(B.data.boolean&&C.data.boolean)
            {
                A.data.boolean = true;
            }
            else
            {
                A.data.boolean = false;
            }
            break;
        case ARRAY:
            object_operator_array(A,B,C,&value_and);
            break;
        }
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&value_and);
            break;
        case STRING:
            out() << "Syntax error: A string is not a bool." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            array_operator_object(A,B,C,&value_and);
            break;
        case ARRAY:
            array_operator_array(A,B,C,&value_and);
            break;
        }
        break;
    }
}

bool value_or(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            if(B.data.number>0||C.data.number>0)
            {
                A.data.boolean = true;
            }
            else
            {
                A.data.boolean = false;
            }
            break;
        case STRING:
            out() << "Syntax error: A string is not a bool." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            A.type = BOOL;
            if(B.data.number>0||C.data.boolean)
            {
                A.data.boolean = true;
            }
            else
            {
                A.data.boolean = false;
            }
            break;
        case ARRAY:
            object_operator_array(A,B,C,&value_or);
            break;
        }
        break;
    case STRING:
        out() << "Syntax error: A string is not a bool." << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        switch(C.type)
        {
        case NUMBER:
            A.type = BOOL;
            if(B.data.boolean||C.data.number>0)
            {
                A.data.boolean = true;
            }
            else
            {
                A.data.boolean = false;
            }
            break;
        case STRING:
            out() << "Syntax error: A string is not a bool." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            A.type = BOOL;
            if(B.data.boolean||C.data.boolean)
            {
                A.data.boolean = true;
            }
            else
            {
                A.data.boolean = false;
            }
            break;
        case ARRAY:
            object_operator_array(A,B,C,&value_or);
            break;
        }
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&value_or);
            break;
        case STRING:
            out() << "Syntax error: A string is not a bool." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            array_operator_object(A,B,C,&value_or);
            break;
        case ARRAY:
            array_operator_array(A,B,C,&value_or);
            break;
        }
        break;
    }
}

bool not_value(object& A, const object& B)
{
    switch(B.type)
    {
    case NUMBER:
        A.type = BOOL;
        if(B.data.number>0)
        {
            A.data.boolean = false;
        }
        else
        {
            A.data.boolean = true;
        }
        break;
    case STRING:
        out() << "Syntax error: cannot call ! on a string." << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        A = B;
        A.data.boolean = !A.data.boolean;
        break;
    case ARRAY:
        out() << "Syntax error: cannot call ! on an array." << std::endl;
        correct_parsing = false;
        break;
    }
}

bool shift_left(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(B.type)
        {
        case NUMBER:
            A.type = NUMBER;
            A.data.number = (((int)B.data.number) << ((int)C.data.number));
            break;
        case STRING:
            out() << "Syntax error: cannot call << on a string." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: cannot call << on a boolean." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&shift_left);
            break;
        }
        break;
    case STRING:
        out() << "Syntax error: cannot call << on a string." << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        out() << "Syntax error: cannot call << on a boolean." << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&shift_left);
            break;
        case STRING:
            out() << "Syntax error: cannot call << on a string." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: cannot call << on a boolean." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&shift_left);
            break;
        }
        break;
    }
}

bool shift_right(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(B.type)
        {
        case NUMBER:
            A.type = NUMBER;
            A.data.number = (((int)B.data.number) >> ((int)C.data.number));
            break;
        case STRING:
            out() << "Syntax error: cannot call >> on a string." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: cannot call >> on a boolean." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&shift_right);
            break;
        }
        break;
    case STRING:
        out() << "Syntax error: cannot call >> on a string." << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        out() << "Syntax error: cannot call >> on a boolean." << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&shift_right);
            break;
        case STRING:
            out() << "Syntax error: cannot call >> on a string." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: cannot call >> on a boolean." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&shift_right);
            break;
        }
        break;
    }
}

bool bit_not(object& A, const object &B)
{
    switch(B.type)
    {
    case NUMBER:
        A.type = NUMBER;
        A.data.number = ~(int)B.data.number;
        break;
    case STRING:
        out() << "Syntax error: cannot call ~ on a string." << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        out() << "Syntax error: cannot call ~ on a string." << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        out() << "Syntax error: cannot call ~ on an array." << std::endl;
        correct_parsing = false;
        break;
    }
}

bool bit_and(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = NUMBER;
            A.data.number = (int)B.data.number & (int)C.data.number;
            break;
        case STRING:
            out() << "Syntax error: cannot call & on a string." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: cannot call & on a boolean." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&bit_and);
            break;
        }
        break;
    case STRING:
        out() << "Syntax error: cannot call & on a string." << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        out() << "Syntax error: cannot call & on a boolean." << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&bit_and);
            break;
        case STRING:
            out() << "Syntax error: cannot call & on a string." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: cannot call & on a boolean." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&bit_and);
            break;
        }
        break;
    }
}

bool bit_or(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = NUMBER;
            A.data.number = (int)B.data.number | (int)C.data.number;
            break;
        case STRING:
            out() << "Syntax error: cannot call & on a string." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: cannot call & on a boolean." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&bit_or);
            break;
        }
        break;
    case STRING:
        out() << "Syntax error: cannot call & on a string." << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        out() << "Syntax error: cannot call & on a boolean." << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&bit_or);
            break;
        case STRING:
            out() << "Syntax error: cannot call & on a string." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: cannot call & on a boolean." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&bit_or);
            break;
        }
        break;
    }
}

bool bit_xor(object& A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
        switch(C.type)
        {
        case NUMBER:
            A.type = NUMBER;
            A.data.number = (int)B.data.number ^ (int)C.data.number;
            break;
        case STRING:
            out() << "Syntax error: cannot call |^ on a string." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: cannot call |^ on a boolean." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            object_operator_array(A,B,C,&bit_xor);
            break;
        }
        break;
    case STRING:
        out() << "Syntax error: cannot call |^ on a string." << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        out() << "Syntax error: cannot call |^ on a boolean." << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            array_operator_object(A,B,C,&bit_xor);
            break;
        case STRING:
            out() << "Syntax error: cannot call |^ on a string." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: cannot call |^ on a boolean." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&bit_xor);
            break;
        }
        break;
    }
}


bool index(object& A, const object& B, const object& C)
{
    object result;
    switch(B.type)
    {
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            if(C.data.number<B.data.array->size())
            {
                A = copy_object(B.data.array->at(C.data.number));
                optic_stack.push_back(A);
                evaluate_top();
                A = optic_stack.back();
                optic_stack.pop_back();
            }
            else
            {
                out() << "Error: Index out of range." << std::endl;
                correct_parsing = false;
            }
            break;
        case STRING:
            out() << "Syntax error: A string cannot be an array index." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: A bool cannot be an array index." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            if(C.data.array->size() > 0)
            {
                index(A,B,C.data.array->at(0));
            }
            else
            {
                out() << "Error: Attempting to index with an array of size zero." << std::endl;
                correct_parsing = false;
            }
            break;
        case UNDECLARED_VARIABLE:
            get_variable(C.data.string,&result);
            index(A,B,copy_object(result));
            break;
        case OPERATION_TREE:
            optic_stack.push_back(C);
            evaluate_top();
            result = copy_object(optic_stack.back());
            optic_stack.pop_back();
            index(A,B,result);
            break;
        default:
            out() << "Syntax error: cannot use a non-numeral for an array index." << std::endl;
            out() << "Object used as index: ";
            print_object(C);
            correct_parsing = false;
            break;
        }
        break;
    case STRING:
        if(get_variable(B.data.string, &result) == OK)
        {
            if(result.type != FUNCTION)
            {
                index(A,result,C);
            }

            else
            {
                call_function(result,B,create_void_tree());
                index(A,result,C);
            }

            break;
        }
        out() << "Syntax error: Attempting to index an undeclared variable." << std::endl;
        out() << "Variable with index called on it: ";
        print_object(B);
        correct_parsing = false;
        break;
    default:
        out() << "Syntax error: cannot retrieve an index from a non-array data type." << std::endl;
        out() << "Object with index called on it: ";
        print_object(B);
        correct_parsing = false;
        break;
    }
}

bool assign_variable(object& A, const object& B, const object& C)
{
    if(B.type == FUNCTION_ARG_NAMES)
    {
        create_function(A,B,C);

        if(set_variable(B.data.array->at(0).data.string, A) != OK)
        {
            out() << "Error. Unable to bind variable " << B.data.array->at(0).data.string << std::endl;
        }
    }

    else if(B.type == STRING)
    {
        if(set_variable(B.data.string, A) != OK)
        {
            out() << "Error. Unable to bind variable " << B.data.string << std::endl;
            correct_parsing = false;
        }
    }

    else
    {
        out() << "assign_variable unable to determine type" << std::endl;
        correct_parsing = false;
    }

    A.type = VOID; // prevent return to stack
}

bool retrieve_variable(object &A, object &B)
{

    if(get_variable(B.data.string, &A) != OK)
    {
        A = B;
        A.type = UNDECLARED_VARIABLE;
        return true;
    }

    else
    {
        return false;
    }
}

bool print(object& A, const object& B)
{

}

object convert_to_string( object& original)
{
    object newObject;
    newObject.type = STRING;
    std::stringstream ss;
    ss << original.data.number;
    newObject.data.string = new String(ss.str());
    return newObject;
}


}
