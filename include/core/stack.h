#ifndef STACK_H
#define STACK_H

#include <deque>
#include "types.h"

namespace panopticon
{

extern std::deque<object> optic_stack;
extern object global_state;
void clear_stack();
bool evaluate_top();
void evaluate_stack();
typedef std::deque<object>::iterator stack_iter;
void print_stack();

bool resolve_stack_from_parser(const object &operation_tree, bool resolve_entire_stack = false);

} // panopticon namespace

#endif // STACK_H
