#ifndef HEAP_H
#define HEAP_H

#include <deque>

#include "types.h"

namespace panopticon
{

typedef std::deque<Dictionary*> heap_t;
typedef std::deque<Dictionary*>::iterator scope_iter_t;
typedef Dictionary::iterator dict_iter_t;
extern heap_t global_scope;
extern void init_heap();
extern void clear_heap(); // ONLY CALL THIS ON CLOSE OR FATAL ERROR
extern void push_scope(Dictionary* scope);
extern void pop_scope(); // This frees all the objects INSIDE the dictionary, but not the dictionary itself
//extern RESULT get_variable(std::string* variable_name, object* result); // returns a mem_copy of the result
//extern RESULT set_variable(std::string* variable_name, const object& value); // sets a mem_copy of the value
extern RESULT get_variable(Variable variable_name, object* result); // returns a mem_copy of the result
extern RESULT set_variable(Variable variable_name, const object& value); // sets a mem_copy of the value

}

#endif // HEAP_H
