#include "../../include/core/containers.h"
#include "../../include/Grammar/parse.h"

namespace panopticon
{

extern bool prepend(object& result_A, const object& B, const object& container_C)
{
    out() << "Prepend C.type: " << container_C.type;
    if(container_C.type != ARRAY)
    {
        result_A.type = ARRAY;
        result_A.data.array = new Array();
        result_A.data.array->push_front(container_C);
        result_A.data.array->push_front(B);
        return true;
    }

    container_C.data.array->push_front(B);
    result_A = container_C;
    return true;
}

extern bool append(object& result_A, const object& container_B, const object& object_C)
{
    out() << "Prepend C.type: " << container_B.type;
    if(container_B.type != ARRAY)
    {
        result_A.type = ARRAY;
        result_A.data.array = new Array();
        result_A.data.array->push_back(container_B);
        result_A.data.array->push_back(object_C);
        return true;
    }

    container_B.data.array->push_back(object_C);
    result_A = container_B;
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
            A.type = ARRAY;
            A.data.array = new Array();
            A.data.array->push_back(B);
            A.data.array->push_back(C);
            break;
        case STRING:
            A.type = STRING;
            if(B.data.boolean)
            {
                A.data.string = new String("true");
            }
            else
            {
                A.data.string = new String("false");
            }
            A.data.string->append(*C.data.string);
            break;
        case ARRAY:
            A = C;
            A.data.array->push_front(B);
            break;
        }
        break;
        break;
    case NUMBER:
        switch(C.type)
        {
        case BOOL:
        case NUMBER:
            A.type = ARRAY;
            A.data.array = new Array();
            A.data.array->push_back(B);
            A.data.array->push_back(C);
            break;
        case STRING:
            A.type = STRING;
            ss << B.data.number;
            A.data.string = new String(ss.str());
            A.data.string->append(*C.data.string);
            break;
        case ARRAY:
            A = C;
            A.data.array->push_front(B);
            break;
        }
        break;
    case STRING:
        switch(C.type)
        {
        case BOOL:
            A = B;
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
            A = B;
            ss << C.data.number;
            A.data.string->append(ss.str());
            break;
        case STRING:
            A = B;
            A.data.string->append(*C.data.string);
            break;
        case ARRAY:
            A = C;
            A.data.array->push_front(B);
            break;
        }
        break;
    case ARRAY:
        A = B;
        switch(C.type)
        {
        case NUMBER:
            A.data.array->push_back(C);
            break;
        case STRING:
            A.data.array->push_back(C);
            break;
        case BOOL:
            A.data.array->push_back(C);
            break;
        case ARRAY:
            for(int i=0;i<C.data.array->size();++i)
            {
                A.data.array->push_back(C.data.array->at(i));
            }
            break;
        }
        break;
    }
}


}
