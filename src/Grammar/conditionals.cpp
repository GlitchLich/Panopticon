#include "../../include/Grammar/conditionals.h"
#include "../../include/Grammar/parse.h"
#include "../../include/core/stack.h"

namespace panopticon
{

bool guard(object& resulting_tree, object& condition_array, object& operation_tree_array)
{
    for(int i=0;i<condition_array.data.array->size();++i)
    {
        optic_stack.push_back(condition_array.data.array->at(i));
        evaluate_top();
        const object& my_result = optic_stack.back();
        optic_stack.pop_back();
        if(my_result.type==BOOL)
        {
            if(my_result.data.boolean)
            {
                resulting_tree = operation_tree_array.data.array->at(i);
                return true;
            }
        }
        else if(my_result.type==BOOL)
        {
            if(my_result.data.number>0)
            {
                resulting_tree = operation_tree_array.data.array->at(i);
                return true;
            }
        }
        else
        {
            out() << "Error: Non-conditional statement used in a guard conditional." << std::endl;
        }
    }
    resulting_tree.type = VOID;
    out() << "Error: No Guard statements conditions met." << std::endl;
    correct_parsing = false;
}

}
