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

        }
        else
        {
            out() << "Error: Non-boolean condition found in a guard statement." << std::endl;
        }
    }
}

}
