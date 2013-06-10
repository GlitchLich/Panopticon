#include "include/core/thunk.h"

namespace panopticon
{

struct Lambda
{
    unsigned long long name;
    Dictionary heap;
    Array arguments;
    Thunk thunk_body;
};

struct Function_Call
{
    unsigned long long name;
    Thunk arguments;
};

struct Recursive_call
{

};

struct Case
{

};


}
