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
#include "include/Grammar/parsingutilities.h"
#include "include/core/function.h"
#include "include/core/stack.h"
#include "core/Memory.h"

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

bool left_section(object& A, object &B, operator_function func, bool expand)
{
    //Function name/arg
    optic::object name_array = mem_alloc(optic::ARRAY);
    optic::object name = optic::mem_string_alloc("\\");
    optic::object arg = optic::mem_string_alloc("x");
    name_array.data.array->push_front(name);
    name_array.data.array->push_back(arg);

    //Function body
    optic::object var = optic::mem_string_alloc(UNDECLARED_VARIABLE,"x");
    object body;
    store_operations(body,B,var,func);

    insure_ready_for_assignment(name_array,body);
    store_operations(A,name_array,body,optic::create_function);
}

bool right_section(object& A, object &B, operator_function func, bool expand)
{
    //Function name/arg
    optic::object name_array = mem_alloc(optic::ARRAY);
    optic::object name = optic::mem_string_alloc("\\");
    optic::object arg = optic::mem_string_alloc("x");
    name_array.data.array->push_front(name);
    name_array.data.array->push_back(arg);

    //Function body
    optic::object var = optic::mem_string_alloc(UNDECLARED_VARIABLE,"x");
    object body;
    store_operations(body,var,B,func);

    insure_ready_for_assignment(name_array,body);
    store_operations(A,name_array,body,optic::create_function);
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

bool print_variable(const object& A)
{
    object result = mem_alloc(NIL);
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

    mem_free(result);
}

bool print_object(const object &A)
{
//    std::cout << "print_object.type: " << A.type << std::endl;
    switch(A.type)
    {
    case panopticon::FUNCTION:
        // -1 arguments because it counts itself as an argument internally
        out() << "A Function" << std::endl;
        break;
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

        print_variable(A);
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

    case NIL:
        out() << "Nil" << std::endl;
        break;
    }
}

bool unary_print_object(object &A, const object &B)
{
    print_object(B);
    A = B;
}

//Unary
bool store_operations(object& a, const object& obj1, unary_operator_function func, bool expand)
{
    a = mem_alloc(OPERATION_TREE);

    int size = 1;

    if(obj1.type == OPERATION_TREE)
    {
        size += obj1.data.array->size();
    }

    else
    {
        size++;
    }

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

    if(obj1.type == OPERATION_TREE)
    {
        for(int i = 0; i < obj1.data.array->size(); ++i)
        {
            a.data.array->push_back(obj1.data.array->at(i));
        }
        shallow_mem_free_array(obj1.data.array, obj1.type);
    }

    else
    {
        a.data.array->push_back(obj1);
    }
}

//Serial
bool store_operations(object& a, const object& obj1, const object& obj2, bool expand)
{
    a = mem_alloc(OPERATION_TREE);

    int size = 0;

    if(obj1.type == OPERATION_TREE)
    {
        size += obj1.data.array->size();
    }

    else
    {
        size++;
    }

    if(obj2.type == OPERATION_TREE)
    {
        size += obj2.data.array->size();
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

    if(obj1.type == OPERATION_TREE)
    {
        //TO DO: std::copy instead?
        for(int i = 0; i < obj1.data.array->size(); ++i)
        {
            a.data.array->push_back(obj1.data.array->at(i));
        }
        shallow_mem_free_array(obj1.data.array, obj1.type);
    }

    else
    {
        a.data.array->push_back(obj1);
    }

    if(obj2.type == OPERATION_TREE)
    {
        for(int i = 0; i < obj2.data.array->size(); ++i)
        {
            a.data.array->push_back(obj2.data.array->at(i));
        }
        shallow_mem_free_array(obj2.data.array, obj2.type);
    }

    else
    {
        a.data.array->push_back(obj2);
    }
}

//Binary
bool store_operations(object& a, const object& obj1, const object& obj2, operator_function func, bool expand)
{
    a = mem_alloc(OPERATION_TREE);

    int size = 1;

    if(obj1.type == OPERATION_TREE)
    {
        size += obj1.data.array->size();
    }

    else
    {
        size++;
    }

    if(obj2.type == OPERATION_TREE)
    {
        size += obj2.data.array->size();
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

    op_func.data.operator_func = func;
    a.data.array->push_back(op_func);

    if(obj1.type == OPERATION_TREE)
    {
        for(int i = 0; i < obj1.data.array->size(); ++i)
        {
            a.data.array->push_back(obj1.data.array->at(i));
        }
        shallow_mem_free_array(obj1.data.array, obj1.type);
    }

    else
    {
        a.data.array->push_back(obj1);
    }

    if(obj2.type == OPERATION_TREE)
    {
        for(int i = 0; i < obj2.data.array->size(); ++i)
        {
            a.data.array->push_back(obj2.data.array->at(i));
        }
        shallow_mem_free_array(obj2.data.array, obj2.type);
    }

    else
    {
        a.data.array->push_back(obj2);
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
        }
        break;
    case STRING:
        switch(C.type)
        {
        case STRING:
            A.type = BOOL;
            A.data.boolean =  B.data.string->size() < C.data.string->size();
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
        }
        break;
    case STRING:
        switch(C.type)
        {
        case STRING:
            A.type = BOOL;
            A.data.boolean =  B.data.string->size() > C.data.string->size();
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
        }
        break;
    case STRING:
        switch(C.type)
        {
        case STRING:
            A.type = BOOL;
            A.data.boolean =  B.data.string->size() <= C.data.string->size();
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
        }
        break;
    case STRING:
        switch(C.type)
        {
        case STRING:
            A.type = BOOL;
            A.data.boolean =  B.data.string->size() >= C.data.string->size();
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
}

}
