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

inline bool call_func_on_item(object& result, const object& function,const object& item, Dictionary& context)
{
    if(item.type==ARRAY)
    {
        result = mem_alloc(ARRAY);
        for(Array::iterator it = item.data.array->begin();it!=item.data.array->end();++it)
        {
            object res;
            call_func_on_item(res,function,*it,context);
            result.data.array->push_back(res);
        }
    }
    else
    {
        optic_stack.push_back(item);
        evaluate_top();
        Variable arg_name = function.data.function->arguments.at(1).data.variable_number;
        context[arg_name] = optic_stack.back();
        optic_stack.pop_back();

        resolve_stack_from_parser(function.data.function->body, false);

        if(optic_stack.back().type == ARRAY)
        {
            object parse_array = mem_alloc(UNARY_OPERATION);
            parse_array.data.unary_operator_func = resolve_function_array;
            optic_stack.push_back(parse_array);
            evaluate_top();
        }

        result = optic_stack.back();
        optic_stack.pop_back();
    }
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
        else if(result.type != ARRAY)
        {
            out() << "Error: Attempting to use a non-Array of type: " << type_string(array.type) << std::endl;
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

inline bool setup_func(object& result, object& function)
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
        //        if(function.type == ARRAY)
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

inline bool call_func_on_two_items(object& result, object& function, object& item1, object& item2,Dictionary& context)
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

    if(optic_stack.back().type == ARRAY)
    {
        object parse_array = mem_alloc(UNARY_OPERATION);
        parse_array.data.unary_operator_func = resolve_function_array;
        optic_stack.push_back(parse_array);
        evaluate_top();
    }

    result = optic_stack.back();
    optic_stack.pop_back();

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

    call_func_on_two_items(result,function,starting_value,array.data.array->at(0),context);
    for(Array::iterator it = array.data.array->begin()+1; it != array.data.array->end(); ++ it)
    {
        call_func_on_two_items(result,function,result,*it,context);
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

    call_func_on_two_items(result,function,array.data.array->at(0),array.data.array->at(1),context);
    for(Array::iterator it = array.data.array->begin()+2; it != array.data.array->end(); ++ it)
    {
        call_func_on_two_items(result,function,result,*it,context);
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
    for(Array::reverse_iterator it = array.data.array->rbegin(); it != array.data.array->rend(); it++)
    {
        call_func_on_two_items(result,function,*it,result,context);
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

    result =  *(array.data.array->rbegin());
    for(Array::reverse_iterator it = array.data.array->rbegin()+1; it != array.data.array->rend(); it++)
    {
        call_func_on_two_items(result,function,*it,result,context);
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
    result = mem_alloc(ARRAY);
    result.data.array->push_back(starting_value);
    call_func_on_two_items(temp,function,starting_value,array.data.array->at(0),context);
    result.data.array->push_back(temp);

    for(Array::iterator it = array.data.array->begin()+1; it != array.data.array->end(); ++ it)
    {
        call_func_on_two_items(temp,function,temp,*it,context);
        result.data.array->push_back(temp);
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
    result = mem_alloc(ARRAY);
    //    result.data.array->push_back(starting_value);
    call_func_on_two_items(temp,function,array.data.array->at(0),array.data.array->at(1),context);
    result.data.array->push_back(temp);

    for(Array::iterator it = array.data.array->begin()+2; it != array.data.array->end(); ++ it)
    {
        call_func_on_two_items(temp,function,temp,*it,context);
        result.data.array->push_back(temp);
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
    result = mem_alloc(ARRAY);
    result.data.array->push_back(starting_value);
    //    call_func_on_two_items(temp,function,starting_value,array.data.array->at(0),context);
    //    result.data.array->push_back(temp);

    for(Array::reverse_iterator it = array.data.array->rbegin(); it != array.data.array->rend(); it++)
    {
        call_func_on_two_items(temp,function,*it,temp,context);
        result.data.array->push_front(temp);
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

    object temp = *array.data.array->rbegin();
    result = mem_alloc(ARRAY);
    result.data.array->push_back(temp);
    for(Array::reverse_iterator it = array.data.array->rbegin()+1; it != array.data.array->rend(); it++)
    {
        call_func_on_two_items(temp,function,*it,temp,context);
        result.data.array->push_front(temp);
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

    //    call_func_on_item(result,function,array,context);
    result = mem_alloc(ARRAY);

    std::function<bool (object& obj)> filt = [&function,&context,&filt](object& obj)->bool {
        object return_value;
        call_func_on_item(return_value,function,obj,context);
        if(return_value.type==BOOL)
        {
            if(return_value.data.boolean)
            {
                if(obj.type==STRING)
                {
                    obj.data.string = mem_copy(obj).data.string;
                }
                return true;
            }
        }
        else if(return_value.type==ARRAY)
        {
            object new_array = mem_alloc(ARRAY);
            std::copy_if(
                        obj.data.array->begin(),
                        obj.data.array->end(),
                        std::back_inserter(*new_array.data.array),
                        filt
                        );
            if(new_array.data.array->size()>0)
            {
                obj.data.array = new_array.data.array;
                return true;
            }
            return false;
        }
        return false;
    };

    std::copy_if(
                array.data.array->begin(),
                array.data.array->end(),
                std::back_inserter(*result.data.array),
                filt
                );
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
        result.data.number = two_three_element_count(array.data.list);
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
        if(array.data.array->size()>1)
        {
            result = mem_alloc(ARRAY);
            std::reverse_copy(array.data.array->begin(),array.data.array->end(),std::back_inserter(*result.data.array));
        }
        else
        {
            result = array;
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
    object arg = arguments.at(1);
    if(arg.type == ARRAY)
    {
        setup_array(arg);
    }
    else
    {
        result = arg;
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
        int a_size = array.data.array->size();
        int a2_size = array2.data.array->size();
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

        result = mem_alloc(ARRAY);
        for(int i=0;i<size;++i)
        {
            object tuplet = mem_alloc(ARRAY);
            tuplet.data.array->push_back(mem_copy(array.data.array->at(i%a_size)));
            tuplet.data.array->push_back(mem_copy(array2.data.array->at(i%a2_size)));
            result.data.array->push_back(tuplet);
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
