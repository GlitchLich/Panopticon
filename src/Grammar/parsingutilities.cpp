#include "../include/Grammar/parsingutilities.h"
#include "../include/core/types.h"
#include "../include/core/Memory.h"
#include "../include/core/operators.h"

namespace panopticon {

object create_void_tree()
{
    object void_tree = mem_alloc(OPERATION_TREE);
    object v;
    v.type = VOID;
    void_tree.data.array->push_back(v);
    return void_tree;
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

bool create_tree(object&a, const object& obj)
{
    if(obj.type == OPERATION_TREE)
    {
//        a = mem_copy(obj);
        a = obj;
    }

    else
    {
        a = mem_alloc(OPERATION_TREE);
//        a.data.array->push_back(mem_copy(obj));
        a.data.array->push_back(obj);
    }
}


}
