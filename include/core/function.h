#ifndef FUNCTION_H
#define FUNCTION_H

#include "types.h"

namespace panopticon
{

// extern bool call_function(object& return_value, const object& operator_tree, operator_function func);
//const String __LAMBDA__ = "__LAMBDA__";

bool create_function(object&A, const object& B, const object& C);
bool call_function(object& A, const object& B, const object& C);
bool call_function_array(object& A, const object& B, const object& C);
bool resolve_function_array(object& A, const object& B);

} // panopticon namespace

#endif // FUNCTION_H
