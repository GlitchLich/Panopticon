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

void evaluate_top();

void clear_stack()
{
    optic_stack.clear();
    global_state.type = NIL;
}

void evaluate_binary_operator(const object& operator_object, bool expand = true)
{
    object result, arg1, arg2;
    bool eval = true;

    if(optic_stack.size())
    {
        evaluate_top();
        arg1 = optic_stack.back();
        optic_stack.pop_back();
    }

    else
    {
        eval = false;
    }

    if(optic_stack.size())
    {
        evaluate_top();
        arg2 = optic_stack.back();
        optic_stack.pop_back();
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
                std::cout << "evaluate_array_array_binary_operator" << std::endl;
                object new_array;
                new_array.data.array = new Array();
                new_array.type = ARRAY;
                unsigned int num_iterations = arg1.data.array->size() > arg2.data.array->size() ? arg1.data.array->size() : arg2.data.array->size();

                for(unsigned int i = 0; i < num_iterations; ++i)
                {
                    optic_stack.push_back(copy_object(arg2.data.array->at(i % arg2.data.array->size())));
                    optic_stack.push_back(copy_object(arg1.data.array->at(i % arg1.data.array->size())));
                    optic_stack.push_back(operator_object);
                    evaluate_top();
                    // delete_object(larger_array->data.array->at(i));
                    // (*new_array.data.array)[i] = optic_stack.back();
                    new_array.data.array->push_back(optic_stack.back());
                    optic_stack.pop_back();
                    std::cout << "evaluate_array_array_binary_operator iteration: " << i << std::endl;
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
                    evaluate_top();
                    // delete_object(arg1.data.array->at(i));
                    // (*arg1.data.array)[i] = optic_stack.back();
                    new_array.data.array->push_back(optic_stack.back());
                    optic_stack.pop_back();
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
                    evaluate_top();
                    // delete_object(arg2.data.array->at(i));
                    // (*arg2.data.array)[i] = optic_stack.back();
                    new_array.data.array->push_back(optic_stack.back());
                    optic_stack.pop_back();
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

        std::cout << "BINARY OP RESULT TYPE: " << result.type << std::endl;
        optic_stack.push_back(result);
    }

    else
    {
        out() << "Missing arguments for binary operator" << std::endl;
        correct_parsing = false;
    }
}


void evaluate_unary_operator(const object& operator_object)
{
    object result, arg;

    if(optic_stack.size())
    {
        evaluate_top();
        arg = optic_stack.back();
        optic_stack.pop_back();


        if(arg.type == ARRAY)
        {
            object new_array;
            new_array.data.array = new Array();
            new_array.type = ARRAY;

            for(int i = 0; i < arg.data.array->size(); ++i)
            {
                optic_stack.push_back(copy_object(arg.data.array->at(i)));
                optic_stack.push_back(operator_object);
                evaluate_top();
                // delete_object(arg.data.array->at(i));
                // (*arg.data.array)[i] = optic_stack.back();
                new_array.data.array->push_back(optic_stack.back());
                optic_stack.pop_back();
            }

            result = new_array;
        }

        else
        {
            operator_object.data.unary_operator_func(result, arg);
        }

        optic_stack.push_back(result);
    }

    else
    {
        out() << "Missing argument for unary operator" << std::endl;
        correct_parsing = false;
    }
}

void evaluate_function_dec()
{
    std::cout << "!!!!!!!!!!!!!!FUNCTION_DEC!!!!!!!!!!!!!!!" << std::endl;
    object arguments = optic_stack.back();
    optic_stack.pop_back();
    object body = optic_stack.back();
    body.type = OPERATION_TREE;
    optic_stack.pop_back();
    object function;
    create_function(function, arguments, body);
    optic_stack.push_back(function);
}

void evaluate_function_call()
{
    std::cout << "evaluate_function_call()" << std::endl;
    if(optic_stack.back().type == FUNCTION)
    {
        object function = optic_stack.back();
        optic_stack.pop_back();
        call_function(function, __LAMBDA__);
        optic_stack.push_back(global_state);
    }

    else if(optic_stack.back().type == STRING)
    {
        object name = optic_stack.back();
        optic_stack.pop_back();
        object arguments = optic_stack.back();
        optic_stack.pop_back();
        call_function(name, name, arguments);
    }
}

void evaluate_variable(std::string* variable_name)
{
    std::cout << "EVALUATE VARIABLE" << std::endl;
    object result;

    if(get_variable(variable_name, &result) == OK)
    {
        std::cout << "VARIABLE " << variable_name << " FOUND FOUND FOUND FOUND " << std::endl;
        optic_stack.push_back(result);
    }

    else
    {
        out() << "Variable " << variable_name << " not found." << std::endl;
        correct_parsing = false;
        clear_stack();
    }
}

void evaluate_assignment()
{
    object result;
    std::cout << "EVALUATE ASSIGNMENT" << std::endl;
    evaluate_top();

    if(set_variable(result.data.string, optic_stack.back()) == OK)
    {
        std::cout << "VARIABLE " << result.data.string << " bound." << std::endl;
        optic_stack.pop_back();
    }

    else
    {
        out() << "Unable to bind variable " << result.data.string << std::endl;
        correct_parsing = false;
        clear_stack();
    }
}

void evaluate_top()
{
    object obj = optic_stack.back();
    optic_stack.pop_back();

    switch(obj.type)
    {
    case OPERATION:
        std::cout << "EVALUATE OPERATION" << std::endl;
        evaluate_binary_operator(obj);
        break;

    case NO_EXPANSION_OPERATION:
        std::cout << "EVALUATE NO_EXPANSION_OPERATION" << std::endl;
        evaluate_binary_operator(obj,false);
        break;

    case UNARY_OPERATION:
        evaluate_unary_operator(obj);
        break;

    case OPERATION_TREE:
        std::cout << "EVALUATE OPERATION_TREE" << std::endl;
        resolve_stack_from_parser(obj, false);
        break;

    case VARIABLE:
    case UNDECLARED_VARIABLE:
        evaluate_variable(obj.data.string);
        break;

    case ASSIGNMENT:
        evaluate_assignment();
        break;

    case FUNCTION_DEC:
        std::cout << "EVALUATE FUNCTION_DEC" << std::endl;
        evaluate_function_dec();
        break;

    case FUNCTION_CALL:
        std::cout << "EVALUATE FUNCTION_CALL" << std::endl;
        evaluate_function_call();
        break;

    case VOID: // don't return
        std::cout << "EVALUATE VOID" << std::endl;
        break;

        // case FUNCTION:
        //    std::cout << "EVALUATE FUNCTION ON THE STACK. (In reality nothing much happens, just returned as an object back to the top)" << std::endl;
    case ARRAY:
        std::cout << "ARRAY ON THE STACK ARRAY ON THE STACK ARRAY ON THE STACK ARRAY ON THE STACK ARRAY ON THE STACK ARRAY ON THE STACK ." << std::endl;
    default:
        optic_stack.push_back(obj);
        break;
    }

    std::cout << "evaluate_top() obj.type: " << obj.type << std::endl;
    print_object(obj);
}

void evaluate_stack()
{
    std::cout << std::cout << "evaluate_stack() optic_stack size: " << optic_stack.size() << std::endl;
    global_state.type = NIL;
    while(optic_stack.size())
    {
        out() << "evaluate_object() optic_stack size: " << optic_stack.size() << std::endl;
        evaluate_top();

        if(optic_stack.size())
        {
            global_state = optic_stack.back();
            out() << "global_state in loop" << std::endl;
            print_object(global_state);
            optic_stack.pop_back();
        }
    }

    if(global_state.type != NIL)
    {
        out() << "RESULT OF THE FUCKING STACK: ";
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
