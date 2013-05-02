#include "../../include/Grammar/conditionals.h"
#include "../../include/Grammar/parse.h"
namespace panopticon
{

bool guard(object& resulting_tree, object& condition_array, object& operation_tree_array)
{
    for(int i=0;i<condition_array.data.array->size();++i)
    {
        if(condition_array.data.array->at(i).type==BOOL)
        {
            if(condition_array.data.array->at(i).data.boolean)
            {
                resulting_tree = operation_tree_array.data.array->at(i);
                return true;
            }
        }
        else
        {
            out() << "Error: Non-boolean condition found in a guard statement." << std::endl;
            correct_parsing = false;
        }
    }
    resulting_tree.type = VOID;
    out() << "Error: No Guard statements conditions met." << std::endl;
    correct_parsing = false;
}

}
