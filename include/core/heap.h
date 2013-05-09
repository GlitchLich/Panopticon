#ifndef HEAP_H
#define HEAP_H

#include <deque>

#include "types.h"

namespace panopticon
{

typedef std::deque<Dictionary*> heap_t;
extern heap_t global_scope;
extern void init_heap();
extern void push_scope(Dictionary* scope);
extern void pop_scope();
extern RESULT get_variable(std::string* variable_name, object* result);
extern RESULT set_variable(std::string* variable_name, const object& value);

}

#endif // HEAP_H
