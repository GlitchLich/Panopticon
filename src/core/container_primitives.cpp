#include "include/core/container_primitives.h"
#include "include/core/heap.h"
#include "include/core/operators.h"
#include "include/core/stack.h"
#include "include/core/Memory.h"
#include <iostream>
#include <algorithm>
#include "include/core/containers.h"
#include "include/core/list.h"

namespace panopticon
{

//TO DO: Could probably be optimized better.
bool call_func_on_item(object& result, const object& function,const object& item, Dictionary& context)
{
    if(item.type==LIST)
    {
        result = mem_alloc(LIST);
        TwoThreeFingerTree* iterative_list = item.data.list;

        while(iterative_list>0)
        {
            object res;
            call_func_on_item(res,function,two_three_list_head(iterative_list),context);
            result.data.list = two_three_list_append(result.data.list,res);
            iterative_list = two_three_tail(iterative_list);
        }
    }
    else
    {
        optic_stack.push_back(item);
        evaluate_top();

        if(optic_stack.back().type == LIST)
        {
            TwoThreeFingerTree* iterative_list = optic_stack.back().data.list;
            object list_result = mem_alloc(LIST);
            while(iterative_list>0)
            {
                object res;
                call_func_on_item(res,function,two_three_list_head(iterative_list),context);
                list_result.data.list = two_three_list_append(list_result.data.list,res);
                iterative_list = two_three_tail(iterative_list);
            }
            result = list_result;
            optic_stack.pop_back();
        }
        else if(optic_stack.back().type == NIL || optic_stack.back().type == VOID)
        {
            out() << "Error: Attempted to map a Null value." << std::endl;
            correct_parsing = false;
            return false;
        }
        else
        {
            Variable arg_name = function.data.function->arguments.at(1).data.variable_number;
            context[arg_name] = optic_stack.back();
            optic_stack.pop_back();
            resolve_stack_from_parser(function.data.function->body, false);

            result = optic_stack.back();
            optic_stack.pop_back();
        }
    }
    return true;
}

bool call_filter_func_on_item(object& result, const object& function,const object& item, Dictionary& context)
{
    if(item.type==LIST)
    {
        result = mem_alloc(LIST);
        TwoThreeFingerTree* iterative_list = item.data.list;

        while(iterative_list>0)
        {
            call_filter_func_on_item(result,function,two_three_list_head(iterative_list),context);
            iterative_list = two_three_tail(iterative_list);
        }
    }
    else
    {
        optic_stack.push_back(item);
        evaluate_top();

        if(optic_stack.back().type == LIST)
        {
            object list_result = mem_alloc(LIST);

            call_filter_func_on_item(list_result,function,optic_stack.back(),context);

            if(two_three_length(list_result.data.list))
            {
                result.data.list = two_three_list_append(result.data.list,list_result);
            }
            optic_stack.pop_back();
        }
        else if(optic_stack.back().type == NIL || optic_stack.back().type == VOID)
        {
            out() << "Error: Attempted to map a Null value." << std::endl;
            correct_parsing = false;
            return false;
        }
        else
        {
            Variable arg_name = function.data.function->arguments.at(1).data.variable_number;
            context[arg_name] = optic_stack.back();
            optic_stack.pop_back();
            resolve_stack_from_parser(function.data.function->body, false);

            if(optic_stack.back().type != BOOL)
            {
                out() << "Error: Non-boolean found in boolean test for filter." << std::endl;
                correct_parsing = false;
                return false;
            }

            if(optic_stack.back().data.boolean)
            {
                result.data.list = two_three_list_append(result.data.list,item);
            }
            optic_stack.pop_back();
        }
    }
    return true;
}

inline bool call_func_on_two_items(object& result, object& function,const object& item1,const object& item2,Dictionary& context)
{
    optic_stack.push_back(item1);
    evaluate_top();
    Variable arg_name = function.data.function->arguments.at(1).data.variable_number;
    context[arg_name] = optic_stack.back();
    optic_stack.pop_back();

    optic_stack.push_back(item2);
    evaluate_top();
    arg_name = function.data.function->arguments.at(2).data.variable_number;
    context[arg_name] = optic_stack.back();
    optic_stack.pop_back();

    resolve_stack_from_parser(function.data.function->body, false);

    result = optic_stack.back();
    optic_stack.pop_back();

    return true;
}

inline bool setup_array(object& array)
{
    if(array.type == OPERATION_TREE)
    {
        optic_stack.push_back(array);
        evaluate_top();
        array = optic_stack.back();
        optic_stack.pop_back();
    }
    else if(array.type == UNDECLARED_VARIABLE||array.type == VARIABLE)
    {
        object result;
        if(get_variable(array.data.variable_number,&result) !=OK)
        {
            out() << "Error: Attempting to map a non-Array of type: " << type_string(result.type) << std::endl;
            correct_parsing = false;
            return false;
        }
        else if(result.type == FUNCTION)
        {
            object arguments;
            call_function(array, result, arguments);
        }
        else if(result.type == OPERATION_TREE)
        {
            optic_stack.push_back(array);
            evaluate_top;
            array = optic_stack.back();
            optic_stack.pop_back();
        }
        else if(result.type != LIST)
        {
            out() << "Error: Attempting to use a non-List of type: " << type_string(array.type) << std::endl;
            print_object(result);
            correct_parsing = false;
            return false;
        }
        else
        {
            array = result;
        }
    }
    else if(array.type == FUNCTION)
    {
        object arguments;
        call_function(array, array, arguments);
    }
    if(array.type != LIST)
    {
        out() << "Error: Attempting to use a non-List of type: " << type_string(array.type) << std::endl;
        print_object(array);
        correct_parsing = false;
        return false;
    }
}

inline bool setup_argument(object& argument)
{
    if(argument.type == OPERATION_TREE)
    {
        optic_stack.push_back(argument);
        evaluate_top();
        argument = optic_stack.back();
        optic_stack.pop_back();
    }
    else if(argument.type == UNDECLARED_VARIABLE||argument.type == VARIABLE)
    {
        object result;
        if(get_variable(argument.data.variable_number,&result) !=OK)
        {
            out() << "Error, Unknown variable: " <<reverse_variable_name_lookup[argument.data.variable_number] << std::endl;
            correct_parsing = false;
            return false;
        }
        else if(result.type == FUNCTION)
        {
            object arguments;
            call_function(argument, result, arguments);
        }
        else if(result.type == OPERATION_TREE)
        {
            optic_stack.push_back(argument);
            evaluate_top;
            argument = optic_stack.back();
            optic_stack.pop_back();
        }
        else
        {
            argument = result;
        }
    }
    else if(argument.type == FUNCTION)
    {
        object arguments;
        call_function(argument, argument, arguments);
    }
}

bool setup_func(object& result, object& function)
{
    optic_stack.push_back(function);
    evaluate_top();
    function = optic_stack.back();
    optic_stack.pop_back();

    //============================
    // SETUP FUNCTION AND CONTEXT
    //============================

    switch(function.type)
    {
    case VARIABLE:
    case UNDECLARED_VARIABLE:
        if(get_variable(function.data.variable_number, &function) != OK)
        {
            out() << "Unable to find function: " << reverse_variable_name_lookup[function.data.variable_number] << " in current scope" << std::endl;
            correct_parsing = false;
            return false;
        }

        //Array Functors...Sort this out
        //        if(function.type == LIST)
        //        {
        //            return call_function_array(result, function, array);
        //        }

        else if(function.type != FUNCTION)
        {
            out() << "Error: Attempted to call a non-function of type: " << type_string(function.type) << std::endl;
            correct_parsing = false;
            return false;
        }

        break;
    case STRING:
        out() << "Error: Malformed Function call." << std::endl;
        correct_parsing = false;
        return false;
        break;
    case FUNCTION:
        // function = mem_copy(B);
        //        function = function; // Will this cause a mem_free crash later? Not sure, something to test for.
        break;

    default:
        out() << "Error: Object is not a function and is not callable: ";
        out() << "OBJECT TYPE: " << type_string(function.type) << " ";
        print_object(function);
        correct_parsing = false;
        return false;
    }
}

bool map(object& result, const Array& arguments)
{
    if(arguments.size()!=2)
    {
        out() << "Error: map received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object function = arguments.at(0);
    object array = arguments.at(1);

    setup_func(result,function);
    if(function.data.function->arguments.size()!=2)
    {
        out() << "Error: Mapped function must take exactly 1 argument." << std::endl;
        correct_parsing = false;
        return false;
    }


    setup_array(array);

    Dictionary context;
    context.insert(std::make_pair(function.data.function->name, function));
    push_scope(&context);

    call_func_on_item(result,function,array,context);

    pop_scope();

    return true;
}

bool foldl(object& result, const Array& arguments)
{
    if(arguments.size()!=3)
    {
        out() << "Error: foldl received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object function = arguments.at(0);
    object starting_value = arguments.at(1);
    object array = arguments.at(2);

    setup_func(result,function);
    if(function.data.function->arguments.size()!=3)
    {
        out() << "Error: function passed to foldl must take exactly 2 arguments." << std::endl;
        correct_parsing = false;
        return false;
    }
    setup_argument(starting_value);
    setup_array(array);

    Dictionary context;
    context.insert(std::make_pair(function.data.function->name, function));
    push_scope(&context);

    call_func_on_two_items(result,function,starting_value,two_three_list_head(array.data.list),context);

    TwoThreeFingerTree* iterative_list = two_three_tail(array.data.list);
    while(iterative_list>0)
    {
        call_func_on_two_items(result,function,result,two_three_list_head(iterative_list),context);
        iterative_list = two_three_tail(iterative_list);
    }

    pop_scope();

    return true;
}

bool foldl1(object& result, const Array& arguments)
{
    if(arguments.size()!=2)
    {
        out() << "Error: foldl received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object function = arguments.at(0);
    object array = arguments.at(1);

    setup_func(result,function);
    if(function.data.function->arguments.size()!=3)
    {
        out() << "Error: function passed to foldl1 must take exactly 2 arguments." << std::endl;
        correct_parsing = false;
        return false;
    }
    setup_array(array);

    Dictionary context;
    context.insert(std::make_pair(function.data.function->name, function));
    push_scope(&context);

    TwoThreeFingerTree* iterative_list = two_three_tail(array.data.list);
    call_func_on_two_items(result,function,two_three_list_head(array.data.list),two_three_list_head(iterative_list),context);
    iterative_list = two_three_tail(iterative_list);
    while(iterative_list)
    {
        call_func_on_two_items(result,function,result,two_three_list_head(iterative_list),context);
        iterative_list = two_three_tail(iterative_list);
    }

    pop_scope();

    return true;
}

bool foldr(object& result, const Array& arguments)
{
    if(arguments.size()!=3)
    {
        out() << "Error: foldl received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object function = arguments.at(0);
    object starting_value = arguments.at(1);
    object array = arguments.at(2);

    setup_func(result,function);
    if(function.data.function->arguments.size()!=3)
    {
        out() << "Error: function passed to foldr must take exactly 2 arguments." << std::endl;
        correct_parsing = false;
        return false;
    }
    setup_argument(starting_value);
    setup_array(array);

    Dictionary context;
    context.insert(std::make_pair(function.data.function->name, function));
    push_scope(&context);

    result = starting_value;
    TwoThreeFingerTree* iterative_list = array.data.list;
    while(iterative_list)
    {
        call_func_on_two_items(result,function,two_three_list_last(iterative_list),result,context);
        iterative_list = two_three_init(iterative_list);
    }

    pop_scope();

    return true;
}

bool foldr1(object& result, const Array& arguments)
{
    if(arguments.size()!=2)
    {
        out() << "Error: foldl received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object function = arguments.at(0);
    object array = arguments.at(1);

    setup_func(result,function);
    if(function.data.function->arguments.size()!=3)
    {
        out() << "Error: function passed to foldr must take exactly 2 arguments." << std::endl;
        correct_parsing = false;
        return false;
    }
    setup_array(array);

    Dictionary context;
    context.insert(std::make_pair(function.data.function->name, function));
    push_scope(&context);

    result =  two_three_list_last(array.data.list);

    TwoThreeFingerTree* iterative_list = two_three_init(array.data.list);
    while(iterative_list)
    {
        call_func_on_two_items(result,function,two_three_list_last(iterative_list),result,context);
        iterative_list = two_three_init(iterative_list);
    }

    pop_scope();

    return true;
}

bool scanl(object& result, const Array& arguments)
{
    if(arguments.size()!=3)
    {
        out() << "Error: scanl received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object function = arguments.at(0);
    object starting_value = arguments.at(1);
    object array = arguments.at(2);

    setup_func(result,function);
    if(function.data.function->arguments.size()!=3)
    {
        out() << "Error: function passed to scanl must take exactly 2 arguments." << std::endl;
        correct_parsing = false;
        return false;
    }
    setup_argument(starting_value);
    setup_array(array);

    Dictionary context;
    context.insert(std::make_pair(function.data.function->name, function));
    push_scope(&context);

    object temp;

    result = mem_alloc(LIST);

    result.data.list = two_three_list_append(result.data.list,starting_value);
    call_func_on_two_items(temp,function,starting_value,two_three_list_head(array.data.list),context);
    result.data.list = two_three_list_append(result.data.list,temp);

    TwoThreeFingerTree* iterative_list = two_three_tail(array.data.list);
    while(iterative_list>0)
    {
        call_func_on_two_items(temp,function,temp,two_three_list_head(iterative_list),context);
        iterative_list = two_three_tail(iterative_list);
        result.data.list = two_three_list_append(result.data.list,temp);
    }

    pop_scope();

    return true;
}

bool scanl1(object& result, const Array& arguments)
{
    if(arguments.size()!=2)
    {
        out() << "Error: scanl received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object function = arguments.at(0);
    object array = arguments.at(1);

    setup_func(result,function);
    if(function.data.function->arguments.size()!=3)
    {
        out() << "Error: function passed to scanl1 must take exactly 2 arguments." << std::endl;
        correct_parsing = false;
        return false;
    }
    setup_array(array);

    Dictionary context;
    context.insert(std::make_pair(function.data.function->name, function));
    push_scope(&context);

    object temp;

    result = mem_alloc(LIST);

    TwoThreeFingerTree* iterative_list = two_three_tail(array.data.list);
    call_func_on_two_items(temp,function,two_three_list_head(array.data.list),two_three_list_head(iterative_list),context);
    result.data.list = two_three_list_append(result.data.list,temp);
    iterative_list = two_three_tail(iterative_list);

    while(iterative_list>0)
    {
        call_func_on_two_items(temp,function,temp,two_three_list_head(iterative_list),context);
        iterative_list = two_three_tail(iterative_list);
        result.data.list = two_three_list_append(result.data.list,temp);
    }

    pop_scope();

    return true;
}

bool scanr(object& result, const Array& arguments)
{
    if(arguments.size()!=3)
    {
        out() << "Error: scanl received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object function = arguments.at(0);
    object starting_value = arguments.at(1);
    object array = arguments.at(2);

    setup_func(result,function);
    if(function.data.function->arguments.size()!=3)
    {
        out() << "Error: function passed to scanl must take exactly 2 arguments." << std::endl;
        correct_parsing = false;
        return false;
    }
    setup_argument(starting_value);
    setup_array(array);

    Dictionary context;
    context.insert(std::make_pair(function.data.function->name, function));
    push_scope(&context);

    object temp = starting_value;

    result = mem_alloc(LIST);

    result.data.list = two_three_list_append(result.data.list,starting_value);

    TwoThreeFingerTree* iterative_list = array.data.list;
    while(iterative_list>0)
    {
        call_func_on_two_items(temp,function,two_three_list_last(iterative_list),temp,context);
        iterative_list = two_three_init(iterative_list);
        result.data.list = two_three_list_append(result.data.list,temp);
    }

    pop_scope();

    return true;
}

bool scanr1(object& result, const Array& arguments)
{
    if(arguments.size()!=2)
    {
        out() << "Error: scanl received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object function = arguments.at(0);
    object array = arguments.at(1);

    setup_func(result,function);
    if(function.data.function->arguments.size()!=3)
    {
        out() << "Error: function passed to scanl must take exactly 2 arguments." << std::endl;
        correct_parsing = false;
        return false;
    }
    setup_array(array);

    Dictionary context;
    context.insert(std::make_pair(function.data.function->name, function));
    push_scope(&context);

    result = mem_alloc(LIST);
    TwoThreeFingerTree* iterative_list = array.data.list;
    object temp = two_three_list_last(iterative_list);
    result.data.list = two_three_list_append(result.data.list,temp);
    iterative_list = two_three_init(iterative_list);

    while(iterative_list>0)
    {
        call_func_on_two_items(temp,function,two_three_list_last(iterative_list),temp,context);
        iterative_list = two_three_init(iterative_list);
        result.data.list = two_three_list_append(result.data.list,temp);
    }

    pop_scope();

    return true;
}

bool filter(object& result, const Array& arguments)
{
    if(arguments.size()!=2)
    {
        out() << "Error: filter received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object function = arguments.at(0);
    object array = arguments.at(1);

    setup_func(result,function);
    if(function.data.function->arguments.size()!=2)
    {
        out() << "Error: filter function must take exactly 1 argument." << std::endl;
        correct_parsing = false;
        return false;
    }

    setup_array(array);

    Dictionary context;
    context.insert(std::make_pair(function.data.function->name, function));
    push_scope(&context);

    result = mem_alloc(LIST);

    result = mem_alloc(LIST);

    call_filter_func_on_item(result,function,array,context);

    pop_scope();

    return true;
}

bool length(object& result, const Array& arguments)
{
    if(arguments.size()!=1)
    {
        out() << "Error: length received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object array = arguments.at(0);
    if(setup_array(array))
    {
        result = mem_alloc(NUMBER);
        result.data.number = two_three_length(array.data.list);
        return true;
    }
    else
    {
        out() << "Error: Attempting to find the length of a non-array." << std::endl;
        correct_parsing = false;
        return false;
    }
}

bool last(object& result, const Array& arguments)
{
    if(arguments.size()!=1)
    {
        out() << "Error: last received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object array = arguments.at(0);
    if(setup_array(array))
    {
        result = two_three_list_last(array.data.list);
        return true;
    }
    else
    {
        out() << "Error: Attempting to retrieve the last of a non-array." << std::endl;
        correct_parsing = false;
        return false;
    }
}

#ifdef BRAUN_TREE
bool tail(object& result, const Array& arguments)
{
    if(arguments.size()!=1)
    {
        out() << "Error: tail received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object array = arguments.at(0);
    if(setup_array(array))
    {
        List* list = braun_tail(array.data.list);
        result = mem_alloc(LIST);
        result.data.list = list;
        complexity_test();
        return true;
    }
    else
    {
        out() << "Error: Attempting to find the tail of a non-array." << std::endl;
        correct_parsing = false;
        return false;
    }
}

bool head(object& result, const Array& arguments)
{
    if(arguments.size()!=1)
    {
        out() << "Error: head received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object array = arguments.at(0);
    if(setup_array(array))
    {
        if(array.data.array->size()>1)
        {
            result = array.data.array->at(0);
        }
        else
        {
            result = array;
        }
        return true;
    }
    else
    {
        out() << "Error: Attempting to retrieve the head of a non-array." << std::endl;
        correct_parsing = false;
        return false;
    }
}
#elif TWO_THREE_TREE
bool tail(object& result, const Array& arguments)
{
    if(arguments.size()!=1)
    {
        out() << "Error: tail received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object array = arguments.at(0);
    if(setup_array(array))
    {
        result = mem_alloc(LIST);
        result.data.list = two_three_tail(array.data.list);
        return true;
    }
    else
    {
        out() << "Error: Attempting to find the tail of a non-array." << std::endl;
        correct_parsing = false;
        return false;
    }
}

bool head(object& result, const Array& arguments)
{
    if(arguments.size()!=1)
    {
        out() << "Error: head received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object array = arguments.at(0);
    if(setup_array(array))
    {
        result = two_three_list_head(array.data.list);
        return true;
    }
    else
    {
        out() << "Error: Attempting to retrieve the head of a non-array." << std::endl;
        correct_parsing = false;
        return false;
    }
}
#endif

bool init(object& result, const Array& arguments)
{
    if(arguments.size()!=1)
    {
        out() << "Error: init received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object array = arguments.at(0);
    if(setup_array(array))
    {
        result = mem_alloc(LIST);
        result.data.list = two_three_init(array.data.list);
        return true;
    }
    else
    {
        out() << "Error: Attempting to find the init of a non-array." << std::endl;
        correct_parsing = false;
        return false;
    }
}

bool reverse(object& result, const Array& arguments)
{
    if(arguments.size()!=1)
    {
        out() << "Error: reverse received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object array = arguments.at(0);
    if(setup_array(array))
    {
        result = mem_alloc(LIST);
        TwoThreeFingerTree* iterative_list = array.data.list;
        while(iterative_list>0)
        {
            result.data.list = two_three_list_append(result.data.list,two_three_list_last(iterative_list));
            iterative_list = two_three_init(iterative_list);
        }
        return true;
    }
    else
    {
        out() << "Error: Attempting to reverse of a non-array." << std::endl;
        correct_parsing = false;
        return false;
    }
}

bool take(object& result, const Array& arguments)
{
    //    std::cout << "take" << std::endl;
    if(arguments.size()!=2)
    {
        out() << "Error: take received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object num_items = arguments.at(0);
    setup_argument(num_items);
    object array = arguments.at(1);
    if(setup_array(array))
    {
        //        setup_array(arg);
        result = mem_alloc(LIST);
        TwoThreeFingerTree* iterative_list = array.data.list;
        int num = num_items.data.number;
        while(iterative_list && num)
        {
            result.data.list = two_three_list_append(result.data.list,two_three_list_head(iterative_list));
            iterative_list = two_three_tail(iterative_list);
            num-=1;
        }
    }
    else
    {
        out() << "Error: Received a non-List as an argument of take." << std::endl;
        correct_parsing = false;
        return false;
    }
    return true;
}

bool zip(object& result, const Array& arguments)
{
    if(arguments.size()!=2)
    {
        out() << "Error: zip received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object array = arguments.at(0);
    object array2 = arguments.at(1);
    if(setup_array(array) && setup_array(array2))
    {
        int size = 0;
        int a_size = two_three_length(array.data.list);
        int a2_size = two_three_length(array2.data.list);
        if(a_size > a2_size)
        {
            size = a_size;
        }
        else
        {
            size = a2_size;
        }

        if(size==0)
        {
            out() << "Error: Attempting to zip an array with 0 elements." << std::endl;
            correct_parsing = false;
            return false;
        }

        result = mem_alloc(LIST);
        TwoThreeFingerTree* iterative_list = array.data.list;
        TwoThreeFingerTree* iterative_list2 = array2.data.list;
        for(int i=0;i<size;++i)
        {
            object tuplet = mem_alloc(LIST);

            if(iterative_list==0)
            {
                iterative_list = array.data.list;
            }

            if(iterative_list2==0)
            {
                iterative_list2 = array2.data.list;
            }

            tuplet.data.list = two_three_list_append(tuplet.data.list,two_three_list_head(iterative_list));
            tuplet.data.list = two_three_list_append(tuplet.data.list,two_three_list_head(iterative_list2));
            result.data.list = two_three_list_append(result.data.list,tuplet);

            iterative_list = two_three_tail(iterative_list);
            iterative_list2 = two_three_tail(iterative_list2);
        }
        return true;
    }
    else
    {
        out() << "Error: Attempting to zip of a non-array." << std::endl;
        correct_parsing = false;
        return false;
    }
}


void register_container_primitives()
{
    object plength = mem_alloc(PRIMITIVE);
    int variable_number = get_string_hash("length");
    plength.data.primitive->name = variable_number;
    plength.data.primitive->num_arguments = 1;
    plength.data.primitive->p_func = length;
    set_variable(variable_number,plength);

    object pzip = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("zip");
    pzip.data.primitive->name = variable_number;
    pzip.data.primitive->num_arguments = 3;
    pzip.data.primitive->p_func = zip;
    set_variable(variable_number,pzip);

    object ptake = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("take");
    ptake.data.primitive->name = variable_number;
    ptake.data.primitive->num_arguments = 3;
    ptake.data.primitive->p_func = take;
    set_variable(variable_number,ptake);

    object preverse = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("reverse");
    preverse.data.primitive->name = variable_number;
    preverse.data.primitive->num_arguments = 2;
    preverse.data.primitive->p_func = reverse;
    set_variable(variable_number,preverse);

    object pinit = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("init");
    pinit.data.primitive->name = variable_number;
    pinit.data.primitive->num_arguments = 3;
    pinit.data.primitive->p_func = init;
    set_variable(variable_number,pinit);

    object plast = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("last");
    plast.data.primitive->name = variable_number;
    plast.data.primitive->num_arguments = 2;
    plast.data.primitive->p_func = last;
    set_variable(variable_number,plast);

    object ptail = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("tail");
    ptail.data.primitive->name = variable_number;
    ptail.data.primitive->num_arguments = 3;
    ptail.data.primitive->p_func = tail;
    set_variable(variable_number,ptail);

    object phead = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("head");
    phead.data.primitive->name = variable_number;
    phead.data.primitive->num_arguments = 3;
    phead.data.primitive->p_func = head;
    set_variable(variable_number,phead);

    object pmap = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("map");
    pmap.data.primitive->name = variable_number;
    pmap.data.primitive->num_arguments = 3;
    pmap.data.primitive->p_func = map;
    set_variable(variable_number,pmap);

    object pfoldl = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("foldl");
    pfoldl.data.primitive->name = variable_number;
    pfoldl.data.primitive->num_arguments = 4;
    pfoldl.data.primitive->p_func = foldl;
    set_variable(variable_number,pfoldl);

    object pfoldl1 = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("foldl1");
    pfoldl1.data.primitive->name = variable_number;
    pfoldl1.data.primitive->num_arguments = 4;
    pfoldl1.data.primitive->p_func = foldl1;
    set_variable(variable_number,pfoldl1);

    object pfoldr = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("foldr");
    pfoldr.data.primitive->name = variable_number;
    pfoldr.data.primitive->num_arguments = 4;
    pfoldr.data.primitive->p_func = foldr;
    set_variable(variable_number,pfoldr);

    object pfoldr1 = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("foldr1");
    pfoldr1.data.primitive->name = variable_number;
    pfoldr1.data.primitive->num_arguments = 4;
    pfoldr1.data.primitive->p_func = foldr1;
    set_variable(variable_number,pfoldr1);

    object pscanl = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("scanl");
    pscanl.data.primitive->name = variable_number;
    pscanl.data.primitive->num_arguments = 4;
    pscanl.data.primitive->p_func = scanl;
    set_variable(variable_number,pscanl);

    object pscanl1 = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("scanl1");
    pscanl1.data.primitive->name = variable_number;
    pscanl1.data.primitive->num_arguments = 4;
    pscanl1.data.primitive->p_func = scanl1;
    set_variable(variable_number,pscanl1);

    object pscanr = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("scanr");
    pscanr.data.primitive->name = variable_number;
    pscanr.data.primitive->num_arguments = 4;
    pscanr.data.primitive->p_func = scanr;
    set_variable(variable_number,pscanr);

    object pscanr1 = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("scanr1");
    pscanr1.data.primitive->name = variable_number;
    pscanr1.data.primitive->num_arguments = 4;
    pscanr1.data.primitive->p_func = scanr1;
    set_variable(variable_number,pscanr1);

    object pfilter = mem_alloc(PRIMITIVE);
    variable_number = get_string_hash("filter");
    pfilter.data.primitive->name = variable_number;
    pfilter.data.primitive->num_arguments = 3;
    pfilter.data.primitive->p_func = filter;
    set_variable(variable_number,pfilter);
}


}
