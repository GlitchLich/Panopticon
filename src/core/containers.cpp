#include "../../include/core/containers.h"
#include "../../include/Grammar/parse.h"
#include "core/Memory.h"

namespace panopticon
{

extern bool prepend(object& result_A, const object& B, const object& container_C)
{
    if(container_C.type != ARRAY)
    {
        result_A = mem_alloc(ARRAY);
        result_A.data.array->push_front(mem_copy(container_C));
        result_A.data.array->push_front(mem_copy(B));
        return true;
    }

    // container_C.data.array->push_front(B);
    result_A = mem_copy(container_C);
    result_A.data.array->push_front(mem_copy(B));
    return true;
}

extern bool append(object& result_A, const object& container_B, const object& object_C)
{
    if(container_B.type != ARRAY)
    {
        result_A = mem_alloc(ARRAY);
        result_A.data.array->push_back(mem_copy(container_B));
        result_A.data.array->push_back(mem_copy(object_C));
        return true;
    }

    // container_B.data.array->push_back(object_C);
    result_A = mem_copy(container_B);
    result_A.data.array->push_back(mem_copy(object_C));
    return true;
}

extern bool concat(object& A, const object& B, const object& C)
{
    std::stringstream ss;
    switch(B.type)
    {
    case BOOL:
        switch(C.type)
        {
        case BOOL:
        case NUMBER:
            A = mem_alloc(ARRAY);
            A.data.array->push_back(mem_copy(B));
            A.data.array->push_back(mem_copy(C));
            break;
        case STRING:
            A = mem_alloc(STRING);

            if(B.data.boolean)
            {
                A.data.string->append("true");
            }

            else
            {
                A.data.string->append("false");
            }

            A.data.string->append(*C.data.string);
            break;
        case ARRAY:
            A = mem_copy(C);
            A.data.array->push_front(mem_copy(B));
            break;
        }
        break;
        break;
    case NUMBER:
        switch(C.type)
        {
        case BOOL:
        case NUMBER:
            A = mem_alloc(ARRAY);
            A.data.array->push_back(mem_copy(B));
            A.data.array->push_back(mem_copy(C));
            break;
        case STRING:
            A = mem_alloc(STRING);
            ss << B.data.number;
            A.data.string->append(ss.str());
            A.data.string->append(*C.data.string);
            break;
        case ARRAY:
            A = mem_copy(C);
            A.data.array->push_front(mem_copy(B));
            break;
        }
        break;
    case STRING:
        switch(C.type)
        {
        case BOOL:
            A = mem_copy(B);
            if(B.data.boolean)
            {
                A.data.string->append("true");
            }
            else
            {
                A.data.string->append("false");
            }
            break;
        case NUMBER:
            A = mem_copy(B);
            ss << C.data.number;
            A.data.string->append(ss.str());
            break;
        case STRING:
            A = mem_copy(B);
            A.data.string->append(*C.data.string);
            break;
        case ARRAY:
            A = mem_copy(C);
            A.data.array->push_front(mem_copy(B));
            break;
        }
        break;
    case ARRAY:
        A = mem_copy(B);
        switch(C.type)
        {
        case NUMBER:
            A.data.array->push_back(mem_copy(C));
            break;
        case STRING:
            A.data.array->push_back(mem_copy(C));
            break;
        case BOOL:
            A.data.array->push_back(mem_copy(C));
            break;
        case ARRAY:
            for(int i=0;i<C.data.array->size();++i)
            {
                A.data.array->push_back(mem_copy(C.data.array->at(i)));
            }
            break;
        }
        break;
    }
}


}
