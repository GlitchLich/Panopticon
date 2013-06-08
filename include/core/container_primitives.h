#ifndef CONTAINER_PRIMITIVES_H
#define CONTAINER_PRIMITIVES_H

#include "include/Grammar/parse.h"
#include "include/core/types.h"

namespace panopticon
{

void register_container_primitives();
bool call_func_on_item(object& result, const object& function,const object& item, Dictionary& context);
bool call_filter_func_on_item(object& result, const object& function,const object& item, Dictionary& context);

} // panopticon namespace


#endif // CONTAINER_PRIMITIVES_H
