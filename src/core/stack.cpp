#include <iostream>

#include "core/types.h"
#include "core/operators.h"
#include "include/core/panopticon.h"

namespace panopticon
{

std::deque<object> optic_stack;
object global_state;

namespace detail
{
void evaluate_binary_operator(const object& operator_object);

void evaluate_top()
{
    object obj = optic_stack.back();
    optic_stack.pop_back();

    switch(obj.type)
    {
    case OPERATION:
        evaluate_binary_operator(obj);
        break;

    default:
        optic_stack.push_back(obj);
        break;
    }
}

void evaluate_binary_operator(const object& operator_object)
{
    object result, arg1, arg2;

    if(optic_stack.size())
    {
        evaluate_top();
        arg1 = optic_stack.back();
        optic_stack.pop_back();
    }

    if(optic_stack.size())
    {
        evaluate_top();
        arg2 = optic_stack.back();
        optic_stack.pop_back();
    }

    operator_object.data.operator_func(result, arg1, arg2);
    optic_stack.push_back(result);
}

} // detail namespace

void evaluate_stack()
{
    std::cout << std::cout << "evaluate_stack() optic_stack size: " << optic_stack.size() << std::endl;
    global_state.type = NIL;
    while(optic_stack.size())
    {
        out() << "evaluate_object() optic_stack size: " << optic_stack.size() << std::endl;
        detail::evaluate_top();

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
        out() << "globa_state end of loop" << std::endl;
        print_object(global_state);
    }
}

} // panopticon namespace
