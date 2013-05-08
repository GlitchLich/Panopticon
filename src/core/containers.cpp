#include "../../include/core/containers.h"
#include "../../include/Grammar/parse.h"

namespace panopticon
{

extern bool prepend(object& result_A, const object& B, const object& container_C)
{
    out() << "Prepend C.type: " << container_C.type;
    if(container_C.type != ARRAY)
    {
        out() << "Error: Cannot prepend a non-Array type." << std::endl;
        result_A.type = VOID;
        correct_parsing = false;
        return false;
    }

    container_C.data.array->push_front(B);
    result_A = container_C;
    return true;
}

}
