#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

// Interface for managing memory allocation and deallocation in Panopticon

// Max object allocations before sweep
#define MAX_GC_OBJECTS 1000

namespace panopticon
{

void gc_free_all(); // collects all free memory, used on stack completion, program end, or assert
void gc_sweep(); // request sweep, will only deallocate if MAX_GC_OBJECTS reached/surpassed
void mem_free_array(Array& array); // DON'T USE THIS DIRECTLY UNLESS YOU HAVE A GOOD REASON. Prefer mem_free where possible.
void mem_free_dictionary(Dictionary& dictionary); // DON'T USE THIS DIRECTLY UNLESS YOU HAVE A GOOD REASON. Prefer mem_free where possible.
object mem_alloc(Type type);
void mem_free(object obj); // not immediate, just scheduled
object mem_copy(const object& obj); // Deep copy an object

} // panopticon namespace

#endif // MEMORY_H