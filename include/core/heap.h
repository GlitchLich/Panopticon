#ifndef HEAP_H
#define HEAP_H

#include "types.h"

namespace panopticon
{

extern void init_heap();
extern object* get_scope();
extern void push_scope(object* scope);
extern void pop_scope(object* scope);

}
#endif // HEAP_H
