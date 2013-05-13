#include <iostream>

#include "core/types.h"
#include "core/operators.h"
#include "include/core/panopticon.h"
#include "include/core/heap.h"
#include "include/Grammar/parse.h"
#include "core/Memory.h"

namespace panopticon
{

std::deque<object> optic_stack;
object global_state;

bool evaluate_top();

void clear_stack()
{
    while(optic_stack.size())
    {
        mem_free(optic_stack.back());
        optic_stack.pop_back();
    }

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
                object new_array = mem_alloc(ARRAY);
                unsigned int num_iterations = arg1.data.array->size() > arg2.data.array->size() ? arg1.data.array->size() : arg2.data.array->size();

                for(unsigned int i = 0; i < num_iterations; ++i)
                {
                    optic_stack.push_back(mem_copy(arg2.data.array->at(i % arg2.data.array->size())));
                    optic_stack.push_back(mem_copy(arg1.data.array->at(i % arg1.data.array->size())));
                    optic_stack.push_back(operator_object);

                    if(evaluate_top())
                    {
                        new_array.data.array->push_back(optic_stack.back());
                        optic_stack.pop_back();
                    }

                    else
                    {
                        mem_free(arg1);
                        mem_free(arg2);
                        clear_stack();
                        return false;
                    }
                }

                result = new_array;
            }

            else if(arg1.type == ARRAY)
            {
                object new_array = mem_alloc(ARRAY);

                for(int i = 0; i < arg1.data.array->size(); ++i)
                {
                    optic_stack.push_back(mem_copy(arg2));
                    optic_stack.push_back(mem_copy(arg1.data.array->at(i)));
                    optic_stack.push_back(operator_object);

                    if(evaluate_top())
                    {
                        new_array.data.array->push_back(optic_stack.back());
                        optic_stack.pop_back();
                    }

                    else
                    {
                        mem_free(arg1);
                        mem_free(arg2);
                        clear_stack();
                        return false;
                    }

                }

                result = new_array;
            }

            else if(arg2.type == ARRAY)
            {
                object new_array = mem_alloc(ARRAY);

                for(int i = 0; i < arg2.data.array->size(); ++i)
                {
                    optic_stack.push_back(mem_copy(arg2.data.array->at(i)));
                    optic_stack.push_back(mem_copy(arg1));
                    optic_stack.push_back(operator_object);

                    if(evaluate_top())
                    {
                        new_array.data.array->push_back(optic_stack.back());
                        optic_stack.pop_back();
                    }

                    else
                    {
                        mem_free(arg1);
                        mem_free(arg2);
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

        mem_free(arg1);
        mem_free(arg2);
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
                object new_array = mem_alloc(ARRAY);

                for(int i = 0; i < arg.data.array->size(); ++i)
                {
                    optic_stack.push_back(mem_copy(arg.data.array->at(i)));
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

            mem_free(arg);
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
        mem_free(arg);
        out() << "Missing argument for unary operator" << std::endl;
        clear_stack();
        return false;
    }
}

bool evaluate_variable(const object& variable_name)
{
    object result;

    std::cout << "GET VARIABLE" << std::endl;
    if(get_variable(variable_name.data.string, &result) == OK)
    {
        std::cout << "GET VARIABLE" << std::endl;

        // Auto call zero argument functions when they are found.
        if(result.type == FUNCTION)
        {
            if(result.data.function->arguments.size() == 1)
            {
                object arguments; // empty, won't be used by call_function so no need to initialize
                call_function(result, result, arguments);
            }
        }

        optic_stack.push_back(result); // result is already a copy, no need to copy again
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

    if(set_variable(result.data.string, optic_stack.back()) == OK) // set_variable uses mem_copy, we need to remember to free the top of the stack
    {
        mem_free(optic_stack.back()); // make sure to free memory!
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

    std::cout << "evaluate_top()" << std::endl;
    object obj = optic_stack.back();
    optic_stack.pop_back();
    bool result = true;
    bool free_obj = true;

    switch(obj.type)
    {
    case OPERATION:
        result = evaluate_binary_operator(obj);
        break;

    case NO_EXPANSION_OPERATION:
        result = evaluate_binary_operator(obj, false);
        break;

    case UNARY_OPERATION:
        result = evaluate_unary_operator(obj);
        break;

    case UNARY_NO_EXPANSION_OPERATION:
        result = evaluate_unary_operator(obj, false);
        break;

    case OPERATION_TREE:
        result = resolve_stack_from_parser(obj, false);
        break;

    case VARIABLE:
    case UNDECLARED_VARIABLE:
        result = evaluate_variable(obj);
        break;

    case ASSIGNMENT:
        result = evaluate_assignment();
        break;

    case VOID: // don't return
        break;

    default:
        optic_stack.push_back(obj);
        free_obj = false;
        break;
    }

    if(free_obj)
        mem_free(obj);

    return result;
}

void evaluate_stack()
{
    std::cout << "EVALUATE_STACK: optic_stack.size: " << optic_stack.size() << std::endl;

    global_state.type = VOID;
    while(optic_stack.size())
    {
        evaluate_top();

        if(optic_stack.size())
        {
            mem_free(global_state); // queue for deallocation
            global_state = optic_stack.back();
            optic_stack.pop_back();
        }
    }

    if(global_state.type != VOID)
    {
        out() << "optic: ";
        print_object(global_state);
        mem_free(global_state);
    }

    gc_free_all(); // Now's a good time to collect the garbage because the stack is empty and nothing is happening
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
