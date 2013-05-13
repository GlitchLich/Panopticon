#include "../include/Grammar/parsingutilities.h"
#include "../include/core/types.h"
#include "../include/core/Memory.h"
#include "../include/core/operators.h"

namespace panopticon {

void flatten_from_tree(Array& new_tree,const object& tree)
{
//    std::cout << "void flatten_from_tree(Array& new_tree,const object& tree)" << std::endl;
    for(int i=0;i<tree.data.array->size();++i)
    {
        if(tree.data.array->at(i).type == OPERATION_TREE)
        {
            flatten_from_tree(new_tree,tree.data.array->at(i));
        }
        else
        {
            new_tree.push_back(tree.data.array->at(i));
        }
    }
}

panopticon::object flatten_tree(panopticon::object& tree)
{
    object new_tree;
    new_tree.data.array = new Array();
    new_tree.type = OPERATION_TREE;
    out() << "Before Flatten: ";
    print_object(tree);
    if(tree.type==OPERATION_TREE)
    {
        flatten_from_tree(*new_tree.data.array,tree);
    }
    else
    {
        new_tree.data.array->push_back(tree);
    }
    mem_free_array(*tree.data.array);
    out() << "After Flatten: ";
    print_object(new_tree);

    return new_tree;
}

bool insure_ready_for_assignment(panopticon::object& B, panopticon::object& C)
{
    if(
        C.type == panopticon::OPERATION     ||
        C.type == panopticon::NUMBER        ||
        C.type == panopticon::STRING        ||
        C.type == panopticon::BOOL          ||
        C.type == panopticon::ARRAY         ||
        C.type != panopticon::OPERATION_TREE
    )
    {
        panopticon::object temp = C;
        C = mem_alloc(panopticon::FUNCTION_BODY);
        C.data.array->push_back(temp);
    }
    C.type = FUNCTION_BODY;

    if(B.type!=panopticon::ARRAY)
    {
        panopticon::object temp = B;
        B = mem_alloc(panopticon::FUNCTION_ARG_NAMES);
        B.data.array->push_back(temp);
    }
    B.type = FUNCTION_ARG_NAMES;
}

}
