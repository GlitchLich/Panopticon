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

#include "../../include/core/operators.h"
#include "../../include/core/heap.h"
#include "../../include/Grammar/plus.h"
#include "../../include/Grammar/minus.h"
#include "../../include/Grammar/divide.h"
#include <math.h>
#include <iostream>

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
    case panopticon::LOCAL_VARIABLE_INDEX:
    case panopticon::OPERATION:
    case panopticon::NUMBER:
    case panopticon::BOOL:
        copy = original;
        break;
    case panopticon::STRING:
        copy.data.string = new String(*copy.data.string);
        break;
    case panopticon::OPERATION_TREE:
    case panopticon::ARRAY:
        copy.data.array = new Array();
        copy.data.array->reserve(original.data.array->size());
        for(int i=0;i<original.data.array->size();++i)
        {
            copy.data.array->push_back(copy_object(original.data.array->at(i)));
        }
        break;
    }
    return copy;
}

bool delete_array(object& a)
{
    for(int i=0;i<a.data.array->size();++i)
    {
        panopticon::object& b = a.data.array->at(i);
        switch(b.type)
        {
        case NUMBER:
            break;
        case STRING:
            delete b.data.string;
            break;
        case BOOL:
            break;
        case ARRAY:
            delete_array(b);
            break;
        }
    }
    delete a.data.array;
}

bool delete_object(object& obj)
{
    switch(obj.type)
    {
    case optic::NUMBER:
    case optic::BOOL:
        break;
    case optic::STRING:
        delete obj.data.string;
        break;
    case optic::ARRAY:
        panopticon::delete_array(obj);
        break;
    }
}

bool print_array(const object &A, int arrayNum)
{
    if(arrayNum!=0)
    {
        out() << " ";
    }
    out() << "[";
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
        case ARRAY:
            print_array(B,arrayNum+1);
            break;
        }
    }
    out() << " ] ";
    if(arrayNum==0)
    {
        out() << std::endl;
    }
}

bool print_object(const object &A)
{
    switch(A.type)
    {
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
    case panopticon::VARIABLE:
        out() << *A.data.string << " = ";
        print_object(A.scope->data.map->at(*A.data.string));
        break;
    case panopticon::UNDECLARED_VARIABLE:
        out() << "Undeclared Variable: " << *A.data.string << std::endl;
        correct_parsing = false;
        break;
    case panopticon::LOCAL_VARIABLE_INDEX:
        out() << "Local Variable Index: " << A.data.number << std::endl;
        break;
    case panopticon::OPERATION_TREE:
        for(int i=0;i<A.data.array->size();++i)
        {
//            if(A.data.array->at(i).type==UNDECLARED_VARIABLE||A.data.array->at(i).type==OPERATION_TREE)
//            {
                print_object(A.data.array->at(i));
//            }
        }
        correct_parsing = false;
        break;
    case panopticon::OPERATION:
        out() << "Operator" << std::endl;
        //        correct_parsing = false;
        break;
    }
}

bool concatenate_arrays(object &a,object b, object c)
{
    a.data.array->reserve(b.data.array->size() + c.data.array->size());
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
    a.data.array = new std::vector<panopticon::object>();
}

//STRING_STRING


bool string_plusplus_string(object &a, object b,  object c)
{
    a.data.string = new String(*b.data.string);
    try
    {
        a.data.string->append(*c.data.string);
    }
    catch(std::exception &e)
    {
        delete b.data.string;
        delete c.data.string;
        return false;
    }
    delete b.data.string;
    delete c.data.string;
    return true;
}

//STRING_NUM
bool string_plusplus_num(object &a, object b,  object c)
{
    a.type = panopticon::STRING;
    a.data.string = new String(*b.data.string);
    std::stringstream ss;
    ss << c.data.number;
    try
    {
        a.data.string->append(ss.str());
    }
    catch(std::exception &e)
    {
        out() << "Error String ++ Number: " << e.what() << std::endl;
        delete b.data.string;
        return false;
    }
    delete b.data.string;
    return true;
}

bool num_plusplus_string(object &a, object b,  object c)
{
    std::stringstream ss;
    ss << b.data.number;
    a.data.string = new String(ss.str());
    try
    {
        a.data.string->append(*c.data.string);
    }
    catch(std::exception &e)
    {
        out() << "Error Number ++ String: " << e.what() << std::endl;
        delete c.data.string;
        return false;
    }
    delete c.data.string;
    return true;
}

bool string_plusplus_bool(object &a, object b,  object c)
{
    a.data.string = new String(*b.data.string);
    try
    {
        if(c.data.boolean)
        {
            a.data.string->append("true");
        }
        else
        {
            a.data.string->append("false");
        }
    }
    catch(std::exception &e)
    {
        out() << "Error String ++ bool: " << e.what() << std::endl;
        delete b.data.string;
        return false;
    }
    delete b.data.string;
    return true;
}



bool bool_plusplus_string(object &a, object b,  object c)
{
    try
    {
        if(b.data.boolean)
        {
            a.data.string = new String("true");
        }
        else
        {
            a.data.string = new String("false");
        }

        a.data.string->append(*c.data.string);
    }
    catch(std::exception &e)
    {
        out() << "Error Boolean ++ String: " << e.what() << std::endl;
        delete c.data.string;
        return false;
    }
    delete c.data.string;
    return true;
}


bool object_operator_array(object& a,const object& obj,const object& array, bool (*func)(object &,const object &,const object &))
{
    a.type = panopticon::ARRAY;
    a.data.array = new std::vector<object>();
    a.data.array->reserve(array.data.array->size());

    for(int i=0;i<array.data.array->size();++i)
    {
        object newObject;
        func(newObject,obj,array.data.array->at(i));
        a.data.array->push_back(newObject);
    }
}

bool array_operator_object(object& a,const object& array,const object& obj, bool (*func)(object &,const object &,const object &))
{
    a.type = panopticon::ARRAY;
    a.data.array = new std::vector<object>();
    a.data.array->reserve(array.data.array->size());

    for(int i=0;i<array.data.array->size();++i)
    {
        object newObject;
        func(newObject,array.data.array->at(i),obj);
        a.data.array->push_back(newObject);
    }
}

bool array_operator_array(object& a,const object& array1,const object& array2, bool (*func)(object &,const object &,const object &))
{
    a.type = panopticon::ARRAY;
    a.data.array = new std::vector<object>();
    int size = 0;
    if(array1.data.array->size()>array2.data.array->size())
    {
        size = array1.data.array->size();
    }
    else
    {
        size = array2.data.array->size();
    }
    a.data.array->reserve(size);

    for(int i=0;i<size;++i)
    {
        object& array1Object = array1.data.array->at(i%array1.data.array->size());
        object& array2Object = array2.data.array->at(i%array2.data.array->size());
        object newObject;
        func(newObject,array1Object,array2Object);
        a.data.array->push_back(newObject);
    }
}

bool store_operations(object& a,const object& obj1,const object& obj2, bool (*func)(object &,const object &,const object &))
{
    a.type = OPERATION_TREE;
    a.data.array = new Array();
//    print_object(obj1);
//    print_object(obj2);

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

    a.data.array->reserve(size);
    object op_func;
    op_func.type = OPERATION;
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

//    std::cout << a.data.array->size() << std::endl;
    print_object(a);
}

bool object_operator_object(object& a, object& b, object& c, bool (*func)(object &,const object &,const object &))
{
    func(a,b,c);
    delete_object(b);
    delete_object(c);
}

bool object_operator_object_old(object& a, object& b, object& c, bool (*func)(object &,const object &,const object &))
{
    if(
            b.type==UNDECLARED_VARIABLE||
            c.type==UNDECLARED_VARIABLE||
            b.type==OPERATION_TREE||
            c.type==OPERATION_TREE
            )
    {
        if(a.type!=ASSIGNMENT)
        {
            store_operations(a,b,c,func);
        }
        else
        {

            create_function(a,b,c);
        }
    }
    else
    {
        func(a,b,c);
        delete_object(b);
        delete_object(c);
    }
}

bool parse_operations(object& a,const object& b,const object& c, bool (*func)(object &,const object &,const object &))
{

    if(a.type==FUNCTION_DEC)
    {
        create_function(a,b,c);
    }
    else if(a.type==ASSIGNMENT)
    {
        assign_variable(a,b,c);
    }
    else if(a.type==COMPUTE)
    {
        a.type = OPERATION_TREE;
        //TO DO:
        //Create system to compute shit outside
//        object_operator_object(a,b,c,func);
    }
    else
    {
        store_operations(a,b,c,func);
    }
}



/**
 * @brief check_variables
 * Check for errors/inconsistencies in the function declaration, assign arguments to indecies.
 * @param arguments Temporary storage for arguments,
 * mainly used to suss out argument order apply that index to all instances of that argument.
 * @param B Arguments for the Function.
 * @param C Body of the function, stored as an operation_tree.
 * @return
 */
bool check_variables(Map& arguments,const object& B,const object& C)
{
    if(B.type==ARRAY)
    {
        for(int i=1;i<B.data.array->size();++i)
        {
            object variableObject;
            variableObject.type = LOCAL_VARIABLE_INDEX;
            variableObject.data.number = i-1;
            arguments[*B.data.array->at(i).data.string] = variableObject;
        }
    }
    else
    {
        object newObject;
        arguments[*B.data.string] = newObject;
    }

    if(C.type==OPERATION_TREE)
    {
        for(int i=0;i<C.data.array->size();++i)
        {
            if(C.data.array->at(i).type==OPERATION_TREE)
            {
                return false;
            }
            if(C.data.array->at(i).type!=OPERATION&&C.data.array->at(i).type!=NUMBER)
            {
                if(arguments.find(*C.data.array->at(i).data.string)==arguments.end())
                {
                    return false;
                }
                else
                {
                    C.data.array->at(i).data.number = arguments[*C.data.array->at(i).data.string].data.number;
                    C.data.array->at(i).type = LOCAL_VARIABLE_INDEX;
                }
            }
        }
    }
    else
    {
        if(C.type==OPERATION)
        {
            return false;
        }
        if(arguments.find(*C.data.string)==arguments.end())
        {
            return false;
        }
        else
        {
            //TO DO FIX THIS
            //            C.data.number = arguments[*C.data.string].data.number;
            //            C.type = LOCAL_VARIABLE_INDEX;
        }
    }

    return true;
}

/**
 * @brief create_function
 * @param A
 * @param B Arguments for the Function. First argument is the function name (unless anonymous)
 * @param C Body of the function, stored as an operation_tree.
 * @return
 */
bool create_function(object &A,const object &B,const object &C)
{
    A.type = FUNCTION;
    std::string function_name;
    if(B.type == ARRAY)
    {
        function_name = *B.data.array->at(0).data.string;
    }
    else
    {
        function_name = *B.data.string;
    }
    Map arguments;
    if(!check_variables(arguments,B,C))
    {
        out() << "Error: Function contains variables that are not in the arguments field." << std::endl;
        correct_parsing = false;
    }
    else
    {
        if(B.scope->data.map->find(function_name)!=B.scope->data.map->end())
        {
            //TO DO, SHOULD THIS DELETE THE FUNCTION?
            //HOW CAN WE KEEP THINGS IMMUTABLE AND THREAD SAFE?
            B.scope->data.map->erase(function_name);
        }
        out() << "Creating function "<< function_name << std::endl;

        if(B.type == ARRAY)
        {
            out() << "with arguments: ";
            for(int i=1;i<B.data.array->size();++i)
            {
                out() << *B.data.array->at(i).data.string << " ";
            }
            out() << std::endl;
        }
        Function* function = new Function;
        function->num_arguments = arguments.size();
        function->body = copy_object(C);

        A.data.function = function;
        A.scope = B.scope;
        std::pair<std::string,object> func(function_name,A);
        B.scope->data.map->insert(func);
    }
}

bool handle_stack(object &A, Function *function)
{
    for(int i=function->body.data.array->size()-1;i>=0;i-=1)
    {
        //        out() << function->body.data.array->at(i).type << std::endl;
        print_object(function->body.data.array->at(i));
        function->stack.push(function->body.data.array->at(i));
    }
    while(function->stack.size()>1)
    {
        out() << "Stack size: " << function->stack.size() << std::endl;
        const object& object1 = function->stack.top();
        int arg1 = -1;
        int arg2 = -1;
        object result;
        function->stack.pop();
        switch(object1.type)
        {
        case LOCAL_VARIABLE_INDEX:
            arg1 = object1.data.number;
            //            out() << "ARG1: " << arg1 << std::endl;
        case NUMBER:
        case STRING:
        case BOOL:
        case ARRAY:
            const object& object2 = function->stack.top();
            function->stack.pop();
            switch(object2.type)
            {
            case NUMBER:
            case STRING:
            case BOOL:
            case ARRAY:
                out() << "Error: two concurrent expressions without an infix operator." << std::endl;
                break;
            case OPERATION:
                const object& object3 = function->stack.top();
                function->stack.pop();
                switch(object3.type)
                {
                case LOCAL_VARIABLE_INDEX:
                    arg2 = object3.data.number;
                case NUMBER:
                case STRING:
                case BOOL:
                case ARRAY:
                    if(arg1>-1&&arg2>-1)
                    {
                        object2.data.operator_func(result,function->arguments.at(arg1),function->arguments.at(arg2));
                    }
                    else if(arg1>-1)
                    {
                        object2.data.operator_func(result,function->arguments.at(arg1),object3);
                    }
                    else if(arg2>-1)
                    {
                        object2.data.operator_func(result,object1,function->arguments.at(arg2));
                    }
                    else
                    {
                        object2.data.operator_func(result,object1,object3);
                    }
                    break;
                case OPERATION:
                    out() << "Error: two concurrent operators on the stack." << std::endl;
                    break;
                }
            }
            break;
        }
        function->stack.push(result);
    }
    A = copy_object(function->stack.top());
    function->stack.pop();
}

bool call_function(object &A,const object &B,const object &C)
{
    if(A.scope->data.map->find(*B.data.string)!=A.scope->data.map->end())
    {
        if(C.data.array->size()==(*A.scope->data.map)[*B.data.string].data.function->num_arguments)
        {
            out() << "Calling function: " << *B.data.string << std::endl;
            out() << "with arguments: " << std::endl;
            for(int i=0;i<C.data.array->size();++i)
            {
                print_object(C.data.array->at(i));
            }
            //        A = (*A.scope->data.map)[*B.data.string];
            (*A.scope->data.map)[*B.data.string].data.function->arguments.swap(*C.data.array);
            handle_stack(A,(*A.scope->data.map)[*B.data.string].data.function);
            //        out() << "Function Result: " << std::endl;
            //        out() << A.type << std::endl;
        }
        else
        {
            out() << "Error: Incorrect number of supplied arguments for this function: " << *B.data.string << std::endl;
            correct_parsing = false;
        }
    }
    else
    {
        out() << "Error: This function has not been declared: " << *B.data.string << std::endl;
        correct_parsing = false;
    }
}



bool recursive_apply(object& a,const object& obj1,const object& obj2, bool (*func)(object &,const object &,const object &))
{
    if(obj1.type==ARRAY)
    {
        array_operator_object(a,obj1,obj2,func);
    }
    else
    {
        object_operator_array(a,obj1,obj2,func);
    }
}

//======================================================================================
//======================================================================================
//======================================================================================

bool plus(object&A, const object& B, const object& C)
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

bool minus(object&A, const object& B, const object& C)
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

bool divide(object&A, const object& B, const object& C)
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


bool multiply(object&A, const object& B, const object& C)
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
            recursive_apply(A,B,C,&multiply);
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

bool modulo(object&A, const object& B, const object& C)
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

bool value_pow(object&A, const object& B, const object& C)
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

bool equal_to(object&A, const object& B, const object& C)
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

bool not_equal_to(object&A, const object& B, const object& C)
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

bool less_than(object&A, const object& B, const object& C)
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
        out() << "Syntax error: A string cannot be greater than or less than a number." << std::endl;
        correct_parsing = false;
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
            out() << "Syntax error: A string cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
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

bool greater_than(object&A, const object& B, const object& C)
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
        out() << "Syntax error: A string cannot be greater than or less than a number." << std::endl;
        correct_parsing = false;
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
            out() << "Syntax error: A string cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
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

bool lore(object&A, const object& B, const object& C)
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
        out() << "Syntax error: A string cannot be greater than or less than a number." << std::endl;
        correct_parsing = false;
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
            out() << "Syntax error: A string cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
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

bool gore(object&A, const object& B, const object& C)
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
        out() << "Syntax error: A string cannot be greater than or less than a number." << std::endl;
        correct_parsing = false;
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
            out() << "Syntax error: A string cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
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

bool value_and(object&A, const object& B, const object& C)
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

bool value_or(object&A, const object& B, const object& C)
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

bool not_value(object&A, object& B)
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

bool shift_left(object&A, const object& B, const object& C)
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

bool shift_right(object&A, const object& B, const object& C)
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

bool bit_not(object&A, object& B)
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

bool bit_and(object&A, const object& B, const object& C)
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

bool bit_or(object&A, const object& B, const object& C)
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

bool bit_xor(object&A, const object& B, const object& C)
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


bool index(object&A, const object& B, const object& C)
{
    switch(B.type)
    {
    case NUMBER:
    case STRING:
    case BOOL:
        out() << "Syntax error: cannot retrieve an index from a non-array data type." << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
        case STRING:
            out() << "Syntax error: A string cannot be an array index." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: A bool cannot be an array index." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            if(C.data.array->at(0).type==NUMBER)
            {
                if(C.data.array->at(0).data.number<B.data.array->size())
                {
                    A = copy_object(B.data.array->at(C.data.array->at(0).data.number));
                }
                else
                {
                    out() << "Error: Index out of range." << std::endl;
                    correct_parsing = false;
                }
                break;
            }
            else
            {
                out() << "Error Indexing Array." << std::endl;
                correct_parsing = false;
            }
            break;
        }
        break;
    }
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

bool assign_variable(object&A, const object& B, const object& C)
{
    if(B.type == ARRAY)
    {
        create_function(A,B,C);
        return true;
    }
    A.type = panopticon::VARIABLE;
    A.data.string = new String(*B.data.string);
    A.scope = get_scope();
    std::pair<std::string,object> value(*B.data.string,copy_object(C));
    A.scope->data.map->insert(value);
}

bool retrieve_variable(object &A, object &B)
{
    B.scope = get_scope();
    if(B.scope->data.map->find(*B.data.string)!=B.scope->data.map->end())
    {
        A = B.scope->data.map->at(*B.data.string);
    }
    else
    {
        A = B;
        A.type = UNDECLARED_VARIABLE;
    }
}


}