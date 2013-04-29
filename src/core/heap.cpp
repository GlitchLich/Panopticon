#include "../../include/core/heap.h"

namespace panopticon
{

object* global;
object* current_scope;

object* get_scope()
{
    return current_scope;
}

void init_heap()
{
    global = new object;
    global->data.map = new std::unordered_map<std::string,object>();
    current_scope = global;
}

void push_scope(object* scope)
{
    current_scope = scope;
}

void pop_scope(object* scope)
{

}

}
