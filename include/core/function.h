#ifndef FUNCTION_H
#define FUNCTION_H

#include "types.h"

namespace panopticon
{

void register_primitive_functions();

// extern bool call_function(object& return_value, const object& operator_tree, operator_function func);
//const String __LAMBDA__ = "__LAMBDA__";

bool create_function(object&A, const object& B, const object& C);
bool call_function(object& A, const object& B, const object& C);
bool call_function_array(object& A, const object& B, const object& C);
bool resolve_function_array(object& A, const object& B);

bool partial_application(object& result_A, const object &func_B, const object &arguments_C);
bool left_section(object& A, object &B, operator_function func, bool expand = true);
bool right_section(object& A, object &B, operator_function func, bool expand = true);
bool create_operator_function(object& A, operator_function func, bool expand = true);

} // panopticon namespace

#endif // FUNCTION_H
