#ifndef CONTAINERS_H
#define CONTAINERS_H

#include "../core/types.h"
#include "include/core/list.h"

namespace panopticon
{

// Dictionaries
bool print_dictionary(const object& dict);
bool dictionary_lookup(object& value, const object& dict, const object& key);
bool dictionary_contains(object &boolean, const object &dict, const object &key);
bool dictionary_insert(object& dictionary_A,const object& string_B, const object& object_C);
bool create_dictionary(object& result_A, const object& B);

//Slice notation:
//[ <first element to include> : <first element to exclude> : <step> ]

//Arrays
bool index(object&A, const object& B, const object& C);

//No Wrapping
bool slice(object&A, const object& B, const object& C);
bool slice_beginning_to(object&A, const object& B, const object& C);
bool slice_to_end(object&A, const object& B, const object& C);
bool slice_all_with_step(object&A, const object& B, const object& C);
bool slice_with_step(object&A, const object& B, const object& C);
bool slice_beginning_to_with_step(object&A, const object& B, const object& C);
bool slice_to_end_with_step(object&A, const object& B, const object& C);

//Wrapping
bool slice_with_wrapping(object&A, const object& B, const object& C);
bool slice_beginning_to_wrapping(object&A, const object& B, const object& C);
bool slice_to_end_wrapping(object&A, const object& B, const object& C);
bool slice_with_step_wrapping(object&A, const object& B, const object& C);
bool slice_beginning_to_with_step_wrapping(object&A, const object& B, const object& C);
bool slice_to_end_with_step_wrapping(object&A, const object& B, const object& C);

//Array Range Syntax
bool range_from_to(object&A, const object& B, const object& C);
bool range_from_step_to(object&A, const object& B, const object& C);




}

#endif // CONTAINERS_H
