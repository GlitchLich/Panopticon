#include <iostream>

#include "core/types.h"
#include "core/operators.h"
#include "include/core/panopticon.h"

namespace panopticon
{

std::deque<object> optic_stack;
object global_state;

void evaluate_object(const object& obj)
{
    if(obj.type == FUNCTION)
        obj.data.stack_func();
}

void evaluate_stack()
{
//    std::cout << "evaluate_stack() optic_stack size: " << optic_stack.size() << std::endl;
    while(optic_stack.size())
    {
        out() << "evaluate_object() optic_stack size: " << optic_stack.size() << std::endl;
        global_state = optic_stack.back();
        print_object(global_state);
        optic_stack.pop_back();

        if(global_state.type == OPERATION)
            global_state.data.stack_func();

        if(optic_stack.size())
        {
            global_state = optic_stack.back();
            out() << "global_state in loop" << std::endl;
            print_object(global_state);
//            std::cout << global_state.type << std::endl;
        }

        optic_stack.pop_back();
    }

    out() << "globa_state end of loop" << std::endl;
    print_object(global_state);
}

} // panopticon namespace
