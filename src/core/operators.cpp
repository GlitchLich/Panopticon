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
    case panopticon::LOCAL_VARIABLE_INDEX:
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
        copy.data.array->reserve(original.data.array->size());
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
    case panopticon::VARIABLE:
        out() << "print_object: VARIABLE"<< std::endl;
        out() << *A.data.string << " = ";
        break;
    case panopticon::UNDECLARED_VARIABLE:
        out() << "Undeclared Variable: " << *A.data.string << std::endl;
        break;
    case panopticon::LOCAL_VARIABLE_INDEX:
        out() << "Local Variable Index: " << A.data.number << std::endl;
        break;
    case panopticon::OPERATION_TREE:
        panopticon::print_array(A,0,true);
        break;
    case panopticon::OPERATION:
        out() << "Operator" << std::endl;
        break;
    }
}

bool unary_print_object(object &A, const object &B)
{
    A = copy_object(B);
    out() << "PRINTING FROM LANGUAGE: ";
    print_object(B);
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

bool object_operator_array(object& a,const object& obj,const object& array, operator_function func)
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

bool array_operator_object(object& a,const object& array,const object& obj, operator_function func)
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

bool array_operator_array(object& a,const object& array1,const object& array2, operator_function func)
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

bool store_operations(object& a,const object& obj1,unary_operator_function func)
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

    a.data.array->reserve(size);
    object op_func;
    op_func.type = UNARY_OPERATION;
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

bool store_operations(object& a,const object& obj1,const object& obj2, operator_function func)
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
    // op_func.data.stack_func = func;
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

bool resolve_stack_from_parser(object& operation_tree, bool resolve_entire_stack)
{
    std::cout << "About to copy. operation_tree.size = " << operation_tree.data.array->size() << std::endl;
    if(operation_tree.type == OPERATION_TREE)
    {
        if(operation_tree.data.array->size() > 1)
        {
            out() << "operation_tree.type == OPERATION_TREE operation_tree.size = " << operation_tree.data.array->size() << std::endl;
            print_object(operation_tree);
            std::reverse_copy(operation_tree.data.array->begin(), operation_tree.data.array->end(), std::inserter(optic_stack, optic_stack.end()));
        }

        else if(operation_tree.data.array->size() == 1)
        {
            optic_stack.push_back(operation_tree.data.array->at(0));
            std::cout << "test" << std::endl;
        }

        else
        {
            out() << "Error: No operations to put on the stack." << std::endl;
            correct_parsing = false;
        }
    }



    out() << "About to evaluate: ";
    print_object(operation_tree);

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
bool create_function(object &A, const object &B, const object &C)
{
    A.type = FUNCTION;
    out() << "Creating function " << std::endl;
    Function* function = new Function;

    if(B.type == ARRAY)
    {
        out() << "with arguments: ";

        for(int i = 1; i < B.data.array->size(); ++i)
        {
            out() << *B.data.array->at(i).data.string << " ";
        }

        out() << std::endl;

        function->num_arguments = B.data.array->size();
        for(int i = 0; i < function->num_arguments; ++i)
        {
            function->arguments.push_back(copy_object(B.data.array->at(i)));
            std::cout << "create_function function->arguments->at(i): " << function->arguments.at(i).data.string->c_str() << std::endl;
        }

        /*
        function->arguments.resize(B.data.array->size());
        std::copy(B.data.array->begin(), B.data.array->end(), function->arguments.begin());*/
    }

    else if(B.type == STRING)
    {
        std::cout << "create_function B.type == STRING" << std::endl;
        function->num_arguments = 0;
        function->arguments.push_back(B);
    }

    function->body = C;
    function->body.type = OPERATION_TREE;
    std::cout << "FUNCTION BODY.TYPE: " << function->body.type << std::endl;
    A.data.function = function;

    /*
    // std::string function_name;
    if(B.type == ARRAY)
    {
        function_name = *B.data.array->at(0).data.string;
    }
    else
    {
        function_name = *B.data.string;
    }

    Map arguments;
    if(!check_variables(arguments, B, C))
    {
        out() << "Error: Function contains variables that are not in the arguments field." << std::endl;
        correct_parsing = false;
    }
    */
    // else
    // {
    /*
        if(B.scope->data.map->find(function_name)!=B.scope->data.map->end())
        {
            //TO DO, SHOULD THIS DELETE THE FUNCTION?
            //HOW CAN WE KEEP THINGS IMMUTABLE AND THREAD SAFE?
            B.scope->data.map->erase(function_name);
        }*/


    // A.scope = B.scope;
    // std::pair<std::string, object> func(function_name,A);
    // B.scope->data.map->insert(func);
    // }
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

/**
* @brief call_function
* @param A = Result
* @param B = Function name (STRING)
* @param C = Function Arguments (ARRAY, zero indexed!)
* @return
*/
bool call_function(object& A, const object& B, const object& C)
{
    std::cout << "CALL FUNCTION!!!!!!!!!!!" << std::endl;

    object function;

    if(get_variable(B.data.string, &function) == OK)
    {
        std::string function_name = *B.data.string;
        std::cout << "Function name: " << function_name << std::endl;
        std::cout << "Function type: " << function.type << std::endl;
        std::cout << "Function number of arguments: " << function.data.function->arguments.size() << std::endl;
        out() << "function.type: " << function.type << std::endl;

        Map context;
        context.insert(std::make_pair(function_name, function));

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
            std::cout << "function_arg: " << arg_name << std::endl;
            context.insert(std::make_pair(arg_name, optic_stack.back()));
            optic_stack.pop_back();
        }

        push_scope(&context);
        resolve_stack_from_parser(function.data.function->body, false);
        A = optic_stack.back();
        optic_stack.pop_back();
        pop_scope();

        out() << "FUNCTION RESULT" << std::endl;
        print_object(optic_stack.back());
    }

    else
    {
        out() << "Unable to find function: " << B.data.string->c_str() << " in current scope" << std::endl;
        std::cout << "Unable to find function: " << B.data.string->c_str() << " in current scope" << std::endl;
        correct_parsing = false;
    }

}

bool call_function(const object &function, const String& name)
{
    out() << "function.type: " << function.type << std::endl;

    Map context;
    context.insert(std::make_pair(name, function));

    std::cout << "function name: " << name << std::endl;
    for(int i = 1; i < function.data.function->arguments.size(); ++i)
    {
        String function_arg = *function.data.function->arguments.at(i).data.string;
        std::cout << "function_arg: " << function_arg << std::endl;
        evaluate_top(); // evaluate the top of the stack for our arguments;
        context.insert(std::make_pair(function_arg, optic_stack.back()));
        optic_stack.pop_back();
    }


    push_scope(&context);
    resolve_stack_from_parser(function.data.function->body);
    pop_scope();
}

//======================================================================================
//======================================================================================
//======================================================================================

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
        out() << "ARRAY_PLUS(A,B,C): A = ";
        print_object(A);
        out() << std::endl;
        out() << "B = ";
        print_object(B);
        out() << std::endl;
        out() << "C = ";
        print_object(C);
        out() << std::endl;
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

bool not_value(object& A, object& B)
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

bool bit_not(object& A, object& B)
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
    switch(B.type)
    {
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            if(C.data.number<B.data.array->size())
            {
                A = copy_object(B.data.array->at(C.data.number));
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
        }
        break;
    case STRING:
        out() << "Evaluating a string as a Function call for an index lookup." << std::endl;
        object func_object;
        call_function(func_object,B,create_void_tree());
//        out() << "Function produced: ";
//        print_object(func_object);
        index(A,func_object,C);
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
    out() << "ASSIGN ASSIGN ASSIGN ASSIGN ASSIGN ASSIGN" << std::endl;


    if(B.type == ARRAY)
    {
        std::cout << "ASSIGN B.data.array->size(): " << B.data.array->size() << std::endl;

        create_function(A,B,C);
        std::cout << "ASSIGN_VARIABLE A.type = " << A.type << std::endl;
        // out() << "ARRAY!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "A.data.function->num_arguments: " << A.data.function->num_arguments << std::endl;
        std::cout << "B.data.string: " << B.data.array->at(0).data.string->c_str() << std::endl;
        // A.type = panopticon::VARIABLE;
        //A.data.string = new String(*B.data.string);
        if(set_variable(B.data.array->at(0).data.string, A) == OK)
        {
            out() << "FUNCTION ASSIGNMENT RIGHT NOW: ";
            out() << "Bound variable_name " << B.data.array->at(0).data.string->c_str() << " to: ";
            print_object(A);
        }

        else
        {
            out() << "Error. Unable to bind variable " << B.data.array->at(0).data.string << std::endl;
        }

        // std::cout << "ASSIGN_VARIABLE A.type = " << A.data.function->arguments.at(0).type << std::endl;
    }

    else if(B.type == STRING)
    {
        std::cout << "ASSGN_VARIABLE: B.type == STRING";
        if(set_variable(B.data.string, A) == OK)
        {
            out() << "Bound variable_name " << B.data.string->c_str() << " to: ";
            print_object(A);
        }

        else
        {
            out() << "Error. Unable to bind variable " << B.data.string << std::endl;
            correct_parsing = false;
        }
    }

    else
    {
        std::cout << "assign_variable unable to determine type" << std::endl;
    }

    A.type = VOID; // prevent return to stack

    // A.scope = get_scope();
    // std::pair<std::string, object> value(*B.data.string, copy_object(C));
    // A.scope->data.map->insert(value);
}

bool retrieve_variable(object &A, object &B)
{
    /*
    B.scope = get_scope();

    if(B.scope->data.map->find(*B.data.string)!=B.scope->data.map->end())
    {
        A = B.scope->data.map->at(*B.data.string);
    }*/

    if(get_variable(B.data.string, &A) != OK)
    {
        A = B;
        A.type = UNDECLARED_VARIABLE;
    }
}

bool print(object& A, const object& B)
{

}

/*
void plus()
{
    std::cout << "plus()" << std::endl;
    object A;
    A.type = NUMBER;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void minus()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void divide()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}


void multiply()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void modulo()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void value_pow()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void equal_to()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void not_equal_to()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void less_than()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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
            out() << "Syntax error: A void cannot be greater than or less than a number." << std::endl;
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
        out() << "Syntax error: A void cannot be greater than or less than a number." << std::endl;
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
            out() << "Syntax error: A void cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&less_than);
            break;
        }
        break;
    }

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void greater_than()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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
            out() << "Syntax error: A void cannot be greater than or less than a number." << std::endl;
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
        out() << "Syntax error: A void cannot be greater than or less than a number." << std::endl;
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
            out() << "Syntax error: A void cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&greater_than);
            break;
        }
        break;
    }

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void lore()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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
            out() << "Syntax error: A bool _cannot be greater than or less than a number." << std::endl;
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
        out() << "Syntax error: A bool _cannot be greater than or less than a number." << std::endl;
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
            out() << "Syntax error: A bool _cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&lore);
            break;
        }
        break;
    }

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void gore()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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
            out() << "Syntax error: A bool _cannot be greater than or less than a number." << std::endl;
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
        out() << "Syntax error: A bool _cannot be greater than or less than a number." << std::endl;
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
            out() << "Syntax error: A bool _cannot be greater than or less than a number." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            array_operator_array(A,B,C,&gore);
            break;
        }
        break;
    }

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void value_and()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void value_or()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void not_value()
{
    object A;
    const object& B = optic_stack.back();

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

    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void shift_left()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void shift_right()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void bit_not()
{
    object A;
    const object& B = optic_stack.back();

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

    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void bit_and()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void bit_or()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void bit_xor()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}


void index()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

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
            out() << "Syntax error: A bool _cannot be an array index." << std::endl;
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

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void assign_variable()
{
    object A;
    const object& B = optic_stack.back();
    const object& C = optic_stack.at(optic_stack.size() - 2);

    if(B.type == ARRAY)
    {

(A,B,C);
        return;
    }

    A.type = panopticon::VARIABLE;
    A.data.string = new String(*B.data.string);
    A.scope = get_scope();
    std::pair<std::string,object> value(*B.data.string,copy_object(C));
    A.scope->data.map->insert(value);

    optic_stack.pop_back();
    optic_stack.pop_back();
    optic_stack.push_back(A);
}

void retrieve_variable()
{
    object A;
    object B = optic_stack.back();
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

    optic_stack.pop_back();
    optic_stack.push_back(A);
}

object object_plus = { OPERATION, { _plus }, (object*) 0 };
object object_minus = { OPERATION, { _minus }, (object*) 0 };
object object_divide = { OPERATION, { _divide }, (object*) 0 };
object object_multiply = { OPERATION, { _multiply }, (object*) 0 };
object object_modulo = { OPERATION, { _modulo }, (object*) 0 };
object object_value_pow = { OPERATION, { _value_pow }, (object*) 0 };
object object_equal_to = { OPERATION, { _equal_to }, (object*) 0 };
object object_not_equal_to = { OPERATION, { _not_equal_to }, (object*) 0 };
object object_less_than = { OPERATION, { _less_than }, (object*) 0 };
object object_greater_than = { OPERATION, { _greater_than }, (object*) 0 };
object object_lore = { OPERATION, { _lore }, (object*) 0 };
object object_gore = { OPERATION, { _gore }, (object*) 0 };
object object_value_and = { OPERATION, { _value_and }, (object*) 0 };
object object_value_or = { OPERATION, { _value_or }, (object*) 0 };
object object_not_value = { OPERATION, { _not_value }, (object*) 0 };
object object_shift_left = { OPERATION, { _shift_left }, (object*) 0 };
object object_shift_right = { OPERATION, { _shift_right }, (object*) 0 };
object object_bit_and = { OPERATION, { _bit_and }, (object*) 0 };
object object_bit_or = { OPERATION, { _bit_or }, (object*) 0 };
object object_bit_not = { OPERATION, { _bit_not }, (object*) 0 };
object object_bit_xor = { OPERATION, { _bit_xor }, (object*) 0 };
object object_assign_variable = { OPERATION, { _assign_variable }, (object*) 0 };
object object_retrieve_variable = { OPERATION, { _retrieve_variable }, (object*) 0 };


bool plus(object& A, const object &B, const object &C)
{
    std::cout << "bool plus" << std::endl;
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_plus);
    return true;
}

bool minus(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_minus);
    return true;
}

bool divide(object& A, const object& B, const object& C)
{
    std::cout << "divide" << std::endl;
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_divide);
    return true;
}

bool multiply(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_multiply);
    return true;
}

bool modulo(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_modulo);
    return true;
}

bool value_pow(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_value_pow);
    return true;
}

bool equal_to(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_equal_to);
    return true;
}

bool not_equal_to(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_not_equal_to);
    return true;
}

bool less_than(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_less_than);
    return true;
}

bool greater_than(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_greater_than);
    return true;
}

bool lore(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_lore);
    return true;
}

bool gore(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_gore);
    return true;
}

bool value_and(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_value_and);
    return true;
}

bool value_or(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_value_or);
    return true;
}

bool not_value(object& A, object& B)
{
    stack.push_back(B);
    stack.push_back(object_not_value);
    return true;
}

bool shift_left(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_shift_left);
    return true;
}

bool shift_right(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_shift_right);
    return true;
}

bool bit_and(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_bit_and);
    return true;
}

bool bit_or(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_bit_or);
    return true;
}

bool bit_not(object& A, object& B)
{
    stack.push_back(B);
    stack.push_back(object_bit_not);
    return true;
}

bool bit_xor(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_bit_xor);
    return true;
}

bool assign_variable(object& A, const object& B, const object& C)
{
    stack.push_back(C);
    stack.push_back(B);
    stack.push_back(object_assign_variable);
    return true;
}

bool retrieve_variable(object& A, object& B)
{
    stack.push_back(B);
    stack.push_back(object_retrieve_variable);
    return true;
}*/


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
