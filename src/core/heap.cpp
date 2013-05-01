#include "../../include/core/heap.h"
#include "include/core/operators.h"

namespace panopticon
{

heap_t global_scope;
Map initial_scope;
Map::iterator scope_pointer;
Map* current_scope;

void init_heap()
{
    global_scope.push_back(&initial_scope);
    current_scope = &initial_scope;
    scope_pointer = current_scope->end();
}

void push_scope(Map* scope)
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
    scope_pointer = current_scope->find(*variable_name);
    if(scope_pointer == current_scope->end())
    {
        result = 0;
        return VARIABLE_NOT_FOUND;
    }

    else
    {
        *result = scope_pointer->second;
        return OK;
    }
}

RESULT set_variable(std::string* variable_name, const object& value)
{
    scope_pointer = current_scope->find(*variable_name);
    if(scope_pointer == current_scope->end())
    {
        current_scope->insert(std::make_pair(*variable_name, value));
        return OK;
    }

    else
    {
        return VARIABLE_ALREADY_BOUND;
    }
}

}
