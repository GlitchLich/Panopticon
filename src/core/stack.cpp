#include <iostream>

#include "core/types.h"
#include "core/operators.h"

namespace panopticon
{

std::deque<object> stack;
object global_state;

void evaluate_object(const object& obj)
{
    if(obj.type == FUNCTION)
        obj.data.stack_func();
}

void evaluate_stack()
{
    std::cout << "evaluate_stack() stack size: " << stack.size() << std::endl;
    while(stack.size())
    {
        std::cout << "evaluate_object() stack size: " << stack.size() << std::endl;
        global_state = stack.back();
        stack.pop_back();

        if(global_state.type == OPERATION)
            global_state.data.stack_func();

        if(stack.size())
        {
            global_state = stack.back();
            std::cout << "globa_state in loop" << std::endl;
            print_object(global_state);
        }

        stack.pop_back();
    }

    std::cout << "globa_state end of loop" << std::endl;
    print_object(global_state);
}

} // panopticon namespace
