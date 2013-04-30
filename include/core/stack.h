#ifndef STACK_H
#define STACK_H

#include <deque>

#include "include/core/panopticon.h"

namespace panopticon
{

extern std::deque<object> stack;
extern object globa_state;
extern void evaluate_stack();
typedef std::deque<object>::iterator stack_iter;

} // panopticon namespace

#endif // STACK_H
