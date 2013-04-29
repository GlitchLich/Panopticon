#ifndef DIVIDE_H
#define DIVIDE_H

#include "../core/types.h"
#include <sstream>
#include "../Grammar/parse.h"

namespace panopticon
{

extern void number_divide(object&A,object& B, object& C);
extern void bool_divide(object&A, object& B, object& C);
extern void string_divide(object&A, object& B, object& C);
extern void array_divide(object&A, object& B, object& C);

}

#endif // DIVIDE_H
