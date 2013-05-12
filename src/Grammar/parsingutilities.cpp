#include "../include/Grammar/parsingutilities.h"
#include "../include/core/types.h"
#include "../include/core/Memory.h"

namespace panopticon {

extern bool insure_ready_for_assignment(panopticon::object& B, panopticon::object& C)
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
