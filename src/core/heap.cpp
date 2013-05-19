#include <iostream>
#include <string>

#include "../../include/core/heap.h"
#include "include/core/operators.h"
#include "core/Memory.h"

namespace panopticon
{

heap_t global_scope;
heap_t::iterator dynamic_scope_pointer;
Dictionary initial_scope;
Dictionary::iterator scope_pointer;
Dictionary* current_scope;

void init_heap()
{
    global_scope.push_back(&initial_scope);
    current_scope = &initial_scope;
    scope_pointer = current_scope->end();
    dynamic_scope_pointer = global_scope.begin();
}

void clear_heap()
{
    while(global_scope.size())
    {
        mem_free_dictionary(*global_scope.back());
        global_scope.pop_back();
    }
}

void push_scope(Dictionary* scope)
{
    global_scope.push_back(scope);
    current_scope = scope;
    scope_pointer = current_scope->begin();
}

void pop_scope()
{
    global_scope.pop_back();
    current_scope = global_scope.back();
    scope_pointer = current_scope->begin();
}

RESULT get_variable(std::string* variable_name, object* result)
{
    dynamic_scope_pointer = global_scope.end();

    // Iterate backwards through each scope
    while(--dynamic_scope_pointer >= global_scope.begin())
    {
        // Check to see if that scope contains the variable we want
        scope_pointer = (*dynamic_scope_pointer)->find(*variable_name);

        // If it does assign the results and return OK
        if(scope_pointer != (*dynamic_scope_pointer)->end())
        {
            // *result = mem_copy(scope_pointer->second);
            *result = scope_pointer->second;
            return OK;
        }
    }

    // If we get to the end we never found it. Return = NULL, return VARIABLE_NOT_FOUND
    result = 0;
    return VARIABLE_NOT_FOUND;
}

RESULT set_variable(std::string* variable_name, const object& value)
{
    scope_pointer = current_scope->find(*variable_name);
    if(scope_pointer == current_scope->end())
    {
        // current_scope->insert(std::make_pair(String(*variable_name), mem_copy(value)));
        current_scope->insert(std::make_pair(String(*variable_name), value));
        return OK;
    }

    else
    {
        return VARIABLE_ALREADY_BOUND;
    }
}

} // panopticon namespace
