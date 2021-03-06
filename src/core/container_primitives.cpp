#include "include/core/container_primitives.h"
#include "include/core/heap.h"
#include "include/core/operators.h"
#include "include/core/stack.h"
#include "include/core/Memory.h"
#include <iostream>
#include <algorithm>
#include "include/core/containers.h"
#include "include/core/list.h"
#include "include/core/Trie.h"

namespace panopticon
{

inline void resolve_trie(object& result, trie::Trie* trie)
{
    if(trie)
    {
        result.type = TRIE;
        result.data.trie = trie;
    }

    else
    {
        result.type = NIL;
        result.data.number = 0;
    }
}

//TO DO: Could probably be optimized better.
bool call_func_on_item(object& result, const object& function,const object& item, Dictionary& context)
{
    if(item.type == TRIE)
    {
        return trie::map(item.data.trie, result, function, context);
    }

    else if(item.type == LIST)
    {
        result = mem_alloc(LIST);
        TwoThreeFingerTree* iterative_list = item.data.list;

        while(iterative_list > 0)
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
            Variable arg_name = function.data.function->arguments.at(1).data.variable;
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
    if(item.type == TRIE)
    {
        return trie::filter(item.data.trie, result, function, context);
    }

    else if(item.type == LIST)
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
            Variable arg_name = function.data.function->arguments.at(1).data.variable;
            context[arg_name] = optic_stack.back();
            optic_stack.pop_back();
            resolve_stack_from_parser(function.data.function->body, false);

            if(optic_stack.back().type != BOOL)
            {
                out() << "Error: Non-boolean found in boolean test for filter." << std::endl;
                correct_parsing = false;
                return false;
            }

            if(item.type == LIST)
            {
                if(optic_stack.back().data.boolean)
                {
                    result.data.list = two_three_list_append(result.data.list,item);
                }
            }

            else
            {
                result = optic_stack.back();
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
    Variable arg_name = function.data.function->arguments.at(1).data.variable;
    context[arg_name] = optic_stack.back();
    optic_stack.pop_back();

    optic_stack.push_back(item2);
    evaluate_top();
    arg_name = function.data.function->arguments.at(2).data.variable;
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
        if(get_variable(array.data.variable,&result) !=OK)
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
        if(get_variable(argument.data.variable,&result) !=OK)
        {
            out() << "Error, Unknown variable: " <<reverse_variable_name_lookup[argument.data.variable] << std::endl;
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
            evaluate_top();
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
        if(get_variable(function.data.variable, &function) != OK)
        {
            out() << "Unable to find function: " << reverse_variable_name_lookup[function.data.variable] << " in current scope" << std::endl;
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
    object container = arguments.at(1);
    setup_argument(container);

    setup_func(result,function);
    if(function.data.function->arguments.size()!=2)
    {
        out() << "Error: Mapped function must take exactly 1 argument." << std::endl;
        correct_parsing = false;
        return false;
    }


    if(container.type == ARRAY || container.type == LIST)
        setup_array(container);

    Dictionary context;
    context.insert(std::make_pair(function.data.function->name, function));
    push_scope(&context);

    call_func_on_item(result, function, container, context);

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
    if(arguments.size() != 2)
    {
        out() << "Error: filter received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object function = arguments.at(0);
    object container = arguments.at(1);

    setup_func(result,function);
    setup_argument(container);

    if(function.data.function->arguments.size()!=2)
    {
        out() << "Error: filter function must take exactly 1 argument." << std::endl;
        correct_parsing = false;
        return false;
    }


    if(container.type == LIST)
        setup_array(container);

    Dictionary context;
    context.insert(std::make_pair(function.data.function->name, function));
    push_scope(&context);
    result = mem_alloc(LIST);
    bool success = call_filter_func_on_item(result, function, container, context);
    pop_scope();

    return success;
}

bool array_size(object& result, object& container)
{
    if(setup_array(container))
    {
        result.data.number = two_three_length(container.data.list);
        return true;
    }

    else
    {
        out() << "Error: Attempting to find the size of a non-container." << std::endl;
        correct_parsing = false;
        return false;
    }
}

void size_of_object(object& result, object& obj)
{
    switch(obj.type)
    {
    case panopticon::STRING:
        result.data.number = obj.data.string->length();
        break;

    case panopticon::DICTIONARY:
        result.data.number = obj.data.dictionary->size();
        break;

    case panopticon::TRIE:
        result.data.number = obj.data.trie->count;
        break;

    case NIL:
        result.data.number = 0;
        break;

    case LIST:
        array_size(result, obj);
        break;

    case ARRAY:
        result.data.number = obj.data.array->size();
        break;

    default:
        result.data.number = 1;
        break;
    }
}

bool size(object& result, const Array& arguments)
{
    if(arguments.size() == 0)
    {
        result.type = NIL;
        result.data.number = 0;
        return true;
    }

    else if(arguments.size() == 1)
    {
        result = mem_alloc(NUMBER);
        object argument = arguments.at(0);
        setup_argument(argument);
        size_of_object(result, argument);
        return true;
    }

    else if(arguments.size() > 1)
    {
        result = mem_alloc(LIST);
        for(unsigned int i = 0; i < arguments.size(); ++i)
        {
            object item_size = mem_alloc(NUMBER);
            object argument = arguments.at(i);
            setup_argument(argument);
            size_of_object(item_size, argument);
            result.data.list = two_three_list_append(result.data.list,item_size);
        }

        return true;
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

bool zip3(object& result, const Array& arguments)
{
    if(arguments.size()!=3)
    {
        out() << "Error: zip3 received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object array = arguments.at(0);
    object array2 = arguments.at(1);
    object array3 = arguments.at(2);
    if(setup_array(array) && setup_array(array2) && setup_array(array3) )
    {
        int size = 0;
        int a_size = two_three_length(array.data.list);
        int a2_size = two_three_length(array2.data.list);
        int a3_size = two_three_length(array3.data.list);

        size = a_size;

        if(a2_size > size)
        {
            size = a2_size;
        }
        if(a3_size > size)
        {
            size = a3_size;
        }

        if(size==0)
        {
            out() << "Error: Attempting to zip3 an array with 0 elements." << std::endl;
            correct_parsing = false;
            return false;
        }

        result = mem_alloc(LIST);

        TwoThreeFingerTree* iterative_list = array.data.list;
        TwoThreeFingerTree* iterative_list2 = array2.data.list;
        TwoThreeFingerTree* iterative_list3 = array3.data.list;

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

            if(iterative_list3==0)
            {
                iterative_list3 = array3.data.list;
            }

            tuplet.data.list = two_three_list_append(tuplet.data.list,two_three_list_head(iterative_list));
            tuplet.data.list = two_three_list_append(tuplet.data.list,two_three_list_head(iterative_list2));
            tuplet.data.list = two_three_list_append(tuplet.data.list,two_three_list_head(iterative_list3));
            result.data.list = two_three_list_append(result.data.list,tuplet);

            iterative_list = two_three_tail(iterative_list);
            iterative_list2 = two_three_tail(iterative_list2);
            iterative_list3 = two_three_tail(iterative_list3);
        }
        return true;
    }
    else
    {
        out() << "Error: Attempting to zip3 a non-array." << std::endl;
        correct_parsing = false;
        return false;
    }
}

bool zipWith(object& result, const Array& arguments)
{
    if(arguments.size()!=3)
    {
        out() << "Error: zipWith received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object function = arguments.at(0);
    setup_func(result,function);
    object array = arguments.at(1);
    object array2 = arguments.at(2);
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

        Dictionary context;
        context.insert(std::make_pair(function.data.function->name, function));
        push_scope(&context);

        for(int i=0;i<size;++i)
        {
            if(iterative_list==0)
            {
                iterative_list = array.data.list;
            }

            if(iterative_list2==0)
            {
                iterative_list2 = array2.data.list;
            }

            object with;
            call_func_on_two_items(with,function,two_three_list_head(iterative_list),two_three_list_head(iterative_list2),context);
            result.data.list = two_three_list_append(result.data.list,with);

            iterative_list = two_three_tail(iterative_list);
            iterative_list2 = two_three_tail(iterative_list2);
        }

        pop_scope();
        return true;
    }
    else
    {
        out() << "Error: Attempting to zip of a non-array." << std::endl;
        correct_parsing = false;
        return false;
    }
}

//TODO: Fix this so that it takes 3 argument functions...
bool zipWith3(object& result, const Array& arguments)
{
    if(arguments.size()!=4)
    {
        out() << "Error: zipWith3 received an incorrect number of arguments" << std::endl;
        correct_parsing = false;
        return false;
    }
    object function = arguments.at(0);
    setup_func(result,function);
    object array = arguments.at(1);
    object array2 = arguments.at(2);
    object array3 = arguments.at(3);

    if(setup_array(array) && setup_array(array2) && setup_array(array3))
    {
        int size = 0;
        int a_size = two_three_length(array.data.list);
        int a2_size = two_three_length(array2.data.list);
        int a3_size = two_three_length(array3.data.list);

        size = a_size;

        if(a2_size > size)
        {
            size = a2_size;
        }
        if(a3_size > size)
        {
            size = a3_size;
        }

        if(size==0)
        {
            out() << "Error: Attempting to zipWith3 an array with 0 elements." << std::endl;
            correct_parsing = false;
            return false;
        }
        result = mem_alloc(LIST);
        TwoThreeFingerTree* iterative_list = array.data.list;
        TwoThreeFingerTree* iterative_list2 = array2.data.list;
        TwoThreeFingerTree* iterative_list3 = array3.data.list;

        Dictionary context;
        context.insert(std::make_pair(function.data.function->name, function));
        push_scope(&context);

        for(int i=0;i<size;++i)
        {
            if(iterative_list==0)
            {
                iterative_list = array.data.list;
            }

            if(iterative_list2==0)
            {
                iterative_list2 = array2.data.list;
            }

            if(iterative_list3==0)
            {
                iterative_list3 = array3.data.list;
            }

            object with;
            call_func_on_two_items(with,function,two_three_list_head(iterative_list),two_three_list_head(iterative_list2),context);
            call_func_on_two_items(with,function,with,two_three_list_head(iterative_list3),context);
            result.data.list = two_three_list_append(result.data.list,with);

            iterative_list = two_three_tail(iterative_list);
            iterative_list2 = two_three_tail(iterative_list2);
            iterative_list3 = two_three_tail(iterative_list3);
        }

        pop_scope();

        return true;
    }
    else
    {
        out() << "Error: Attempting to zipWith3 a non-array." << std::endl;
        correct_parsing = false;
        return false;
    }
}
bool lookup(object& result, const Array& arguments)
{
    if(arguments.size() != 2)
    {
        out() << "Error: lookup received an incorrect number of arguments: " << arguments.size() << ". Use lookup(container key)" << std::endl;
        correct_parsing = false;
        return false;
    }

    object map = arguments.at(0);
    setup_argument(map);

    object key = arguments.at(1);
    setup_argument(key);

    if(map.type != TRIE)
    {
        out() << "Error: Received a non-container type the first argument for lookup." << std::endl;
        correct_parsing = false;
        return false;
    }

    if(key.type != STRING)
    {
        out() << "Error: Received a non-String as the 2nd argument for lookup(map key)" << std::endl;
        correct_parsing = false;
        return false;
    }

    result = trie::lookup(map.data.trie, fnv1a(key.data.string->c_str()));
    return true;
}

bool insert(object& result, const Array& arguments)
{
    if(arguments.size() % 2 == 0 || arguments.size() < 3)
    {
        out() << "Error: insert received an incorrect number of arguments: " << arguments.size() << ". Use insert(container key value key2 value2 etc...)" << std::endl;
        correct_parsing = false;
        return false;
    }

    object map = arguments.at(0);
    setup_argument(map);

    if(map.type != TRIE)
    {
        out() << "Error: Received non-container type the first argument for insert." << std::endl;
        correct_parsing = false;
        return false;
    }

    for(unsigned int i = 1; i < arguments.size(); i += 2)
    {
        object key = arguments.at(i);
        setup_argument(key);

        object value = arguments.at(i + 1);
        setup_argument(value);



        if(key.type != STRING && key.type != VARIABLE && key.type != NUMBER)
        {
            out() << "Error: Received a non-String as the 2nd argument for insert(dictionary key value)" << std::endl;
            correct_parsing = false;
            return false;
        }
        trie_insert(map, key, value);
    }

    std::cout << "Trie.insert.type = " << type_string(map.type) << std::endl;

    resolve_trie(result, map.data.trie);
    return true;
}

bool remove(object& result, const Array& arguments)
{
    if(arguments.size() < 2)
    {
        out() << "Error: remove received a wrong number of arguments: " << arguments.size() << ". remove must be used as remove(container key key2 key3 etc...)" << std::endl;
        correct_parsing = false;
        return false;
    }

    object map = arguments.at(0);
    setup_argument(map);

    if(map.type != TRIE)
    {
        out() << "Error: Received a non-container type the first argument for remove." << std::endl;
        correct_parsing = false;
        return false;
    }

    for(unsigned int i = 1; i < arguments.size(); ++i)
    {
        object key = arguments.at(i);
        setup_argument(key);

        if(key.type != STRING && key.type != VARIABLE && key.type != NUMBER)
        {
            out() << "Error: Received a non-String as the 2nd argument for remove(dictionary key)" << std::endl;
            correct_parsing = false;
            return false;
        }
        trie_remove(map, key);
    }

    resolve_trie(result, map.data.trie);
    return true;
}

object type_to_string_object(const object& obj); // Forward declaration

object variable_to_string_object(const object& obj)
{
    optic_stack.push_back(obj);
    evaluate_top();
    object var = optic_stack.back();
    optic_stack.pop_back();
    return type_to_string_object(var);
}

object type_to_string_object(const object& obj)
{
    switch(obj.type)
    {
    case NIL:
        return mem_string_alloc("Nil");
        break;

    case BOOL:
        return mem_string_alloc("Bool");
        break;

    case NUMBER:
        return mem_string_alloc("Number");
        break;

    case STRING:
        return mem_string_alloc("String");
        break;

    case FUNCTION:
        return mem_string_alloc("Function");
        break;

    case ARRAY:
    case LIST:
        return mem_string_alloc("Array");
        break;

    case DICTIONARY:
    case TRIE:
        return mem_string_alloc("Dictionary");
        break;

    case PRIMITIVE:
        return mem_string_alloc("Primitive");
        break;

    case UNDECLARED_VARIABLE:
        return variable_to_string_object(obj);
        break;

    case VARIABLE:
        return mem_string_alloc(reverse_variable_name_lookup[obj.data.variable].c_str());
        break;

    default:
        return mem_string_alloc(type_string(obj.type).c_str());
        break;
    }
}

bool type_of(object& result, const Array& arguments)
{
    if(arguments.size() == 0)
    {
        result.type = NIL;
        result.data.number = 0;
    }

    else if(arguments.size() > 1)
    {
        result = mem_alloc(LIST);
        for(unsigned int i = 0; i < arguments.size(); ++i)
        {
            object argument = arguments.at(i);
            setup_argument(argument);
            result.data.list = two_three_list_append(result.data.list,type_to_string_object(argument));
        }
    }

    else
    {
        object argument = arguments.at(0);
        setup_argument(argument);
        result = type_to_string_object(argument);
    }

    return true;
}

void register_container_primitives()
{
    object psize = mem_alloc(PRIMITIVE);
    int variable = get_string_hash("size");
    psize.data.primitive->name = variable;
    psize.data.primitive->num_arguments = 1;
    psize.data.primitive->p_func = size;
    set_variable(variable, psize);

    object pzip = mem_alloc(PRIMITIVE);
    variable = get_string_hash("zip");
    pzip.data.primitive->name = variable;
    pzip.data.primitive->num_arguments = 3;
    pzip.data.primitive->p_func = zip;
    set_variable(variable,pzip);

    object pzip3 = mem_alloc(PRIMITIVE);
    variable = get_string_hash("zip3");
    pzip3.data.primitive->name = variable;
    pzip3.data.primitive->num_arguments = 4;
    pzip3.data.primitive->p_func = zip3;
    set_variable(variable,pzip3);

    object pzipWith = mem_alloc(PRIMITIVE);
    variable = get_string_hash("zipWith");
    pzipWith.data.primitive->name = variable;
    pzipWith.data.primitive->num_arguments = 4;
    pzipWith.data.primitive->p_func = zipWith;
    set_variable(variable,pzipWith);

    object pzipWith3 = mem_alloc(PRIMITIVE);
    variable = get_string_hash("zipWith3");
    pzipWith3.data.primitive->name = variable;
    pzipWith3.data.primitive->num_arguments = 4;
    pzipWith3.data.primitive->p_func = zipWith3;
    set_variable(variable,pzipWith3);

    object ptake = mem_alloc(PRIMITIVE);
    variable = get_string_hash("take");
    ptake.data.primitive->name = variable;
    ptake.data.primitive->num_arguments = 3;
    ptake.data.primitive->p_func = take;
    set_variable(variable,ptake);

    object preverse = mem_alloc(PRIMITIVE);
    variable = get_string_hash("reverse");
    preverse.data.primitive->name = variable;
    preverse.data.primitive->num_arguments = 2;
    preverse.data.primitive->p_func = reverse;
    set_variable(variable,preverse);

    object pinit = mem_alloc(PRIMITIVE);
    variable = get_string_hash("init");
    pinit.data.primitive->name = variable;
    pinit.data.primitive->num_arguments = 3;
    pinit.data.primitive->p_func = init;
    set_variable(variable,pinit);

    object plast = mem_alloc(PRIMITIVE);
    variable = get_string_hash("last");
    plast.data.primitive->name = variable;
    plast.data.primitive->num_arguments = 2;
    plast.data.primitive->p_func = last;
    set_variable(variable,plast);

    object ptail = mem_alloc(PRIMITIVE);
    variable = get_string_hash("tail");
    ptail.data.primitive->name = variable;
    ptail.data.primitive->num_arguments = 3;
    ptail.data.primitive->p_func = tail;
    set_variable(variable,ptail);

    object phead = mem_alloc(PRIMITIVE);
    variable = get_string_hash("head");
    phead.data.primitive->name = variable;
    phead.data.primitive->num_arguments = 3;
    phead.data.primitive->p_func = head;
    set_variable(variable,phead);

    object pmap = mem_alloc(PRIMITIVE);
    variable = get_string_hash("map");
    pmap.data.primitive->name = variable;
    pmap.data.primitive->num_arguments = 3;
    pmap.data.primitive->p_func = map;
    set_variable(variable,pmap);

    object pfoldl = mem_alloc(PRIMITIVE);
    variable = get_string_hash("foldl");
    pfoldl.data.primitive->name = variable;
    pfoldl.data.primitive->num_arguments = 4;
    pfoldl.data.primitive->p_func = foldl;
    set_variable(variable,pfoldl);

    object pfoldl1 = mem_alloc(PRIMITIVE);
    variable = get_string_hash("foldl1");
    pfoldl1.data.primitive->name = variable;
    pfoldl1.data.primitive->num_arguments = 4;
    pfoldl1.data.primitive->p_func = foldl1;
    set_variable(variable,pfoldl1);

    object pfoldr = mem_alloc(PRIMITIVE);
    variable = get_string_hash("foldr");
    pfoldr.data.primitive->name = variable;
    pfoldr.data.primitive->num_arguments = 4;
    pfoldr.data.primitive->p_func = foldr;
    set_variable(variable,pfoldr);

    object pfoldr1 = mem_alloc(PRIMITIVE);
    variable = get_string_hash("foldr1");
    pfoldr1.data.primitive->name = variable;
    pfoldr1.data.primitive->num_arguments = 4;
    pfoldr1.data.primitive->p_func = foldr1;
    set_variable(variable,pfoldr1);

    object pscanl = mem_alloc(PRIMITIVE);
    variable = get_string_hash("scanl");
    pscanl.data.primitive->name = variable;
    pscanl.data.primitive->num_arguments = 4;
    pscanl.data.primitive->p_func = scanl;
    set_variable(variable,pscanl);

    object pscanl1 = mem_alloc(PRIMITIVE);
    variable = get_string_hash("scanl1");
    pscanl1.data.primitive->name = variable;
    pscanl1.data.primitive->num_arguments = 4;
    pscanl1.data.primitive->p_func = scanl1;
    set_variable(variable,pscanl1);

    object pscanr = mem_alloc(PRIMITIVE);
    variable = get_string_hash("scanr");
    pscanr.data.primitive->name = variable;
    pscanr.data.primitive->num_arguments = 4;
    pscanr.data.primitive->p_func = scanr;
    set_variable(variable,pscanr);

    object pscanr1 = mem_alloc(PRIMITIVE);
    variable = get_string_hash("scanr1");
    pscanr1.data.primitive->name = variable;
    pscanr1.data.primitive->num_arguments = 4;
    pscanr1.data.primitive->p_func = scanr1;
    set_variable(variable,pscanr1);

    object pfilter = mem_alloc(PRIMITIVE);
    variable = get_string_hash("filter");
    pfilter.data.primitive->name = variable;
    pfilter.data.primitive->num_arguments = 3;
    pfilter.data.primitive->p_func = filter;
    set_variable(variable,pfilter);

    object plookup = mem_alloc(PRIMITIVE);
    variable = get_string_hash("lookup");
    plookup.data.primitive->name = variable;
    plookup.data.primitive->num_arguments = 2;
    plookup.data.primitive->p_func = lookup;
    set_variable(variable, plookup);

    object pinsert = mem_alloc(PRIMITIVE);
    variable = get_string_hash("insert");
    pinsert.data.primitive->name = variable;
    pinsert.data.primitive->num_arguments = 3;
    pinsert.data.primitive->p_func = insert;
    set_variable(variable, pinsert);

    object premove = mem_alloc(PRIMITIVE);
    variable = get_string_hash("remove");
    premove.data.primitive->name = variable;
    premove.data.primitive->num_arguments = 2;
    premove.data.primitive->p_func = remove;
    set_variable(variable, premove);

    object ptype = mem_alloc(PRIMITIVE);
    variable = get_string_hash("type");
    ptype.data.primitive->name = variable;
    ptype.data.primitive->num_arguments = 1;
    ptype.data.primitive->p_func = type_of;
    set_variable(variable, ptype);
}

} // panopticon namespace
