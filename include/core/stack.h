#ifndef STACK_H
#define STACK_H

#include <deque>
#include "types.h"

namespace panopticon
{

extern std::deque<object> optic_stack;
extern object global_state;
extern void evaluate_stack();
typedef std::deque<object>::iterator stack_iter;

} // panopticon namespace

#endif // STACK_H
