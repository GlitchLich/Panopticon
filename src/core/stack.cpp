#include <iostream>

#include "core/types.h"
#include "core/operators.h"
#include "include/core/panopticon.h"
#include "include/core/heap.h"
#include "include/Grammar/parse.h"

namespace panopticon
{

std::deque<object> optic_stack;
object global_state;

bool evaluate_top();

void clear_stack()
{
    optic_stack.clear();
    global_state.type = NIL;
    correct_parsing = false;
}

bool evaluate_binary_operator(const object& operator_object, bool expand = true)
{
    object result, arg1, arg2;
    bool eval = true;

    if(optic_stack.size())
    {
        eval = evaluate_top();

        if(eval)
        {
            arg1 = optic_stack.back();
            optic_stack.pop_back();
        }
    }

    else
    {
        eval = false;
    }

    if(optic_stack.size())
    {
        eval = evaluate_top();

        if(eval)
        {
            arg2 = optic_stack.back();
            optic_stack.pop_back();
        }
    }

    else
    {
        eval = false;
    }

    if(eval)
    {
        if(expand)
        {
            if(arg1.type == ARRAY && arg2.type == ARRAY)
            {
                object new_array;
                new_array.data.array = new Array();
                new_array.type = ARRAY;
                unsigned int num_iterations = arg1.data.array->size() > arg2.data.array->size() ? arg1.data.array->size() : arg2.data.array->size();

                for(unsigned int i = 0; i < num_iterations; ++i)
                {
                    optic_stack.push_back(copy_object(arg2.data.array->at(i % arg2.data.array->size())));
                    optic_stack.push_back(copy_object(arg1.data.array->at(i % arg1.data.array->size())));
                    optic_stack.push_back(operator_object);

                    if(evaluate_top())
                    {
                        new_array.data.array->push_back(optic_stack.back());
                        optic_stack.pop_back();
                    }

                    else
                    {
                        clear_stack();
                        return false;
                    }
                }

                result = new_array;
            }

            else if(arg1.type == ARRAY)
            {
                object new_array;
                new_array.data.array = new Array();
                new_array.type = ARRAY;

                for(int i = 0; i < arg1.data.array->size(); ++i)
                {
                    optic_stack.push_back(copy_object(arg2));
                    optic_stack.push_back(copy_object(arg1.data.array->at(i)));
                    optic_stack.push_back(operator_object);

                    if(evaluate_top())
                    {
                        new_array.data.array->push_back(optic_stack.back());
                        optic_stack.pop_back();
                    }

                    else
                    {
                        clear_stack();
                        return false;
                    }

                }

                result = new_array;
            }

            else if(arg2.type == ARRAY)
            {
                object new_array;
                new_array.data.array = new Array();
                new_array.type = ARRAY;

                for(int i = 0; i < arg2.data.array->size(); ++i)
                {
                    optic_stack.push_back(copy_object(arg2.data.array->at(i)));
                    optic_stack.push_back(copy_object(arg1));
                    optic_stack.push_back(operator_object);

                    if(evaluate_top())
                    {
                        new_array.data.array->push_back(optic_stack.back());
                        optic_stack.pop_back();
                    }

                    else
                    {
                        clear_stack();
                        return false;
                    }
                }

                result = new_array;
            }

            else
            {
                operator_object.data.operator_func(result, arg1, arg2);
            }
        }

        else
        {
            operator_object.data.operator_func(result, arg1, arg2);
        }

        optic_stack.push_back(result);
        return true;
    }

    else
    {
        out() << "Missing arguments for binary operator" << std::endl;
        clear_stack();
        return false;
    }
}


bool evaluate_unary_operator(const object& operator_object,bool expand = true)
{
    object result, arg;
    bool eval = true;

    if(optic_stack.size())
    {
        eval = evaluate_top();

        if(eval)
        {
            arg = optic_stack.back();
            optic_stack.pop_back();


            if(arg.type == ARRAY && expand)
            {
                object new_array;
                new_array.data.array = new Array();
                new_array.type = ARRAY;

                for(int i = 0; i < arg.data.array->size(); ++i)
                {
                    optic_stack.push_back(copy_object(arg.data.array->at(i)));
                    optic_stack.push_back(operator_object);

                    if(evaluate_top())
                    {
                        new_array.data.array->push_back(optic_stack.back());
                        optic_stack.pop_back();
                    }

                }

                result = new_array;
            }

            else
            {
                operator_object.data.unary_operator_func(result, arg);
            }

            optic_stack.push_back(result);
            return true;
        }
    }

    else
    {
        eval = false;
    }

    if(!eval)
    {
        out() << "Missing argument for unary operator" << std::endl;
        clear_stack();
        return false;
    }
}

bool evaluate_function_dec()
{
    object arguments = optic_stack.back();
    optic_stack.pop_back();
    object body = optic_stack.back();
    body.type = OPERATION_TREE;
    optic_stack.pop_back();
    object function;
    create_function(function, arguments, body);
    optic_stack.push_back(function);
    return true;
}

bool evaluate_function_call()
{
    /* DOESN'T WORK
    if(optic_stack.back().type == FUNCTION)
    {
        object function = optic_stack.back();
        optic_stack.pop_back();
        call_function(function, __LAMBDA__);
        optic_stack.push_back(global_state);
    }

    else */

    if(optic_stack.back().type == STRING)
    {
        object name = optic_stack.back();
        optic_stack.pop_back();
        object arguments = optic_stack.back();
        optic_stack.pop_back();
        return call_function(name, name, arguments);
    }

    clear_stack();
    return false;
}

bool evaluate_variable(const object& variable_name)
{
    object result;

    if(get_variable(variable_name.data.string, &result) == OK)
    {
        //=============
        //Curtis: Added this to auto call zero argument functions when they are found.
        //=============
        if(result.type == FUNCTION)
        {
            if(result.data.function->arguments.size() == 1)
            {
                object arguments; // empty, won't be used by call_function so no need to initialize
                call_function(result, variable_name, arguments);
            }
        }

        optic_stack.push_back(result);
        return true;
    }

    else
    {
        out() << "Variable " << variable_name.data.string->c_str() << " not found." << std::endl;
        clear_stack();
        return false;
    }
}

bool evaluate_assignment()
{
    object result;

    if(!evaluate_top())
    {
        clear_stack();
        return false;
    }

    if(set_variable(result.data.string, optic_stack.back()) == OK)
    {
        optic_stack.pop_back();
        return true;
    }

    else
    {
        out() << "Unable to bind variable " << result.data.string << std::endl;
        clear_stack();
        return false;
    }
}

bool evaluate_top()
{
    if(!optic_stack.size())
    {
        out() << "Instruction stack is empty, cannot evaluate expression." << std::endl;
        clear_stack();
        return false;
    }

    object obj = optic_stack.back();
    optic_stack.pop_back();

    switch(obj.type)
    {
    case OPERATION:
        return evaluate_binary_operator(obj);
        break;

    case NO_EXPANSION_OPERATION:
        return evaluate_binary_operator(obj, false);
        break;

    case UNARY_OPERATION:
        return evaluate_unary_operator(obj);
        break;

    case UNARY_NO_EXPANSION_OPERATION:
        return evaluate_unary_operator(obj, false);
        break;

    case OPERATION_TREE:
        return resolve_stack_from_parser(obj, false);
        break;

    case VARIABLE:
    case UNDECLARED_VARIABLE:
        return evaluate_variable(obj);
        break;

    case ASSIGNMENT:
        return evaluate_assignment();
        break;

    case FUNCTION_DEC:
        return evaluate_function_dec();
        break;

    case FUNCTION_CALL:
        return evaluate_function_call();
        break;

    case VOID: // don't return
        break;

    default:
        optic_stack.push_back(obj);
        break;
    }

    return true;
}

void evaluate_stack()
{
    global_state.type = NIL;
    while(optic_stack.size())
    {
        evaluate_top();

        if(optic_stack.size())
        {
            global_state = optic_stack.back();
            optic_stack.pop_back();
        }
    }

    if(global_state.type != NIL)
    {
        out() << "optic: ";
        print_object(global_state);
    }
}

void print_stack()
{
    out() << "Contents of the stack: ( " << std::endl;
    int i=0;
    for(std::deque<object>::iterator it = optic_stack.begin();it!=optic_stack.end();++it)
    {
        out() << "  ["<< i << "] ";
        print_object(*(it));
        i++;
    }
    out() << ")" << std::endl;
}

} // panopticon namespace
