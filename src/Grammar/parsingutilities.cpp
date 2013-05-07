#include "../include/Grammar/parsingutilities.h"
#include "../include/core/types.h"

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
        C.data.array = new panopticon::Array();
        C.data.array->reserve(1);
        C.data.array->push_back(temp);
    }
    C.type = panopticon::FUNCTION_BODY;
    if(B.type!=panopticon::ARRAY)
    {
        panopticon::object temp = B;
        B.type=panopticon::ARRAY;
        B.data.array = new panopticon::Array();
        B.data.array->reserve(1);
        B.data.array->push_back(temp);
    }
}

}
