#ifndef CONDITIONALS_H
#define CONDITIONALS_H

#include "../core/types.h"

namespace panopticon
{

//Guards
extern bool resolve_guard(object& A, const object &condition_tree);
extern object create_guard(object &function_call_name_and_args, object &condition_tree);
extern object create_condition_tree(const object& condition, const object& operation);
extern void add_branch_to_tree(object &tree, const object& condition, const object& operation);
extern void add_wildcard_to_tree(object &tree, const object& operation);
bool conditional_function_call(object& result_A,const object& conditional_B,const object& operation_tree_C);
}
#endif // CONDITIONALS_H
