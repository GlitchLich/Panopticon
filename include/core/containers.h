#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <cassert>
#include <sstream>

#include "../core/types.h"
#include "include/core/list.h"

namespace panopticon
{

// Hashing, thanks to Stephan Brumme: http://create.stephan-brumme.com/fnv-hash/
const uint32_t Prime = 0x01000193; // 16777619
const uint32_t Seed = 0x811C9DC5; // 2166136261

// hash a single byte
inline uint32_t fnv1a(unsigned char oneByte, uint32_t hash = Seed)
{
    return (oneByte ^ hash) * Prime;
}

// hash a block of memory
inline uint32_t fnv1a(const void* data, size_t numBytes, uint32_t hash = Seed)
{
    assert(data);
    const unsigned char* ptr = (const unsigned char*)data;
    while (numBytes--)
        hash = fnv1a(*ptr++, hash);

    return hash;
}

// hash a short (two bytes)
inline uint32_t fnv1a(unsigned short twoBytes, uint32_t hash = Seed)
{
    const unsigned char* ptr = (const unsigned char*) &twoBytes;
    hash = fnv1a(*ptr++, hash);
    return fnv1a(*ptr , hash);
}

// hash a 32 bit integer (four bytes)
inline uint32_t fnv1a(uint32_t fourBytes, uint32_t hash = Seed)
{
    const unsigned char* ptr = (const unsigned char*) &fourBytes;
    hash = fnv1a(*ptr++, hash);
    hash = fnv1a(*ptr++, hash);
    hash = fnv1a(*ptr++, hash);
    return fnv1a(*ptr , hash);
}

// hash a float
inline uint32_t fnv1a(float number, uint32_t hash = Seed)
{
    return fnv1a(&number, sizeof(number), hash);
}

// hash a double
inline uint32_t fnv1a(double number, uint32_t hash = Seed)
{
    return fnv1a(&number, sizeof(number), hash);
}

// hash a C-style string
inline uint32_t fnv1a(const char* text, uint32_t hash = Seed)
{
    assert(text);
    while(*text)
        hash = fnv1a((unsigned char)*text++, hash);

    return hash;
}

// Tries
bool print_trie(const object& trie, bool endl = false);
bool trie_lookup(object& value, const object& trie, const object &key);
bool trie_contains(object& boolean, const object& trie, object& key);
bool trie_insert(object& trie_A, object& string_B, object& object_C);
bool trie_remove(object& trie_A, object& string_B);
bool create_trie(object& result_A, const object& B);

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
