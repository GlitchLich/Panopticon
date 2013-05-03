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

void evaluate_binary_operator(const object& operator_object)
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
        operator_object.data.operator_func(result, arg1, arg2);
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

        operator_object.data.unary_operator_func(result, arg);
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

    case FUNCTION:
        std::cout << "EVALUATE FUNCTION ON THE STACK. (In reality nothing much happens, just returned as an object back to the top)" << std::endl;
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

} // panopticon namespace
