#ifndef TRIE_H
#define TRIE_H

#include "core/types.h"

/**
 * Trie, a persistant hash map inspired by Clojure's implementation
 *
 */

namespace panopticon
{

namespace trie
{

// Forward declarations
struct Trie; // Persistant Hash Map
struct Entry; // struct { uint32_t key, panopticon::object value }
struct Iterator; // Trie HashMap iterator, use Entry Iterator::next() and bool Iterator::has_next()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Trie Interface Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Trie* new_trie(); // Create a blank Trie
Trie* create(const Array& entry_array); // create from array of panopticon::objects, key/val pairs alternating
Trie* create(const std::deque<Entry>& entry_array); // create from a deque of Entry structs
Trie* create(Entry* entry_array, unsigned int size);
Trie* create(Trie* meta, const Array& entry_array); // create from array of panopticon::objects, key/val pairs alternating with Meta Trie
Trie* create(Trie* meta, const std::deque<Entry>& entry_array); // create from a deque of Entry structs with Meta Trie
bool contains(Trie* trie, uint32_t key);
Entry entry(Trie* trie, uint32_t key);
object lookup(Trie* trie, uint32_t key);
Trie* insert(Trie* trie, uint32_t key, const object& value);
Trie* without(Trie* trie, uint32_t key);
bool map(Trie* trie, object& result, const object& function, Dictionary& context);
bool filter(Trie* trie, object& result, const object& function, Dictionary& context);
Iterator iterator(Trie* trie);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Trie implementation details
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////
/// Trie Types
/////////////////


// Forward declarations
struct Node;
struct ArrayNode;
struct BitmapIndexedNode;
struct HashCollisionNode;

// Trie types, used for type tags
enum Type
{
    NULL_NODE = 0, // 0
    KEY, // 1
    OPTIC_OBJECT, // 2
    ARRAY_NODE, // 3
    BITMAP_INDEXED_NODE, // 4
    HASH_COLLISION_NODE, // 5
    TRIE_MAP, // 6
    NODE // 7
};

//////////////////
/// Trie structs
//////////////////

union NodeData
{
    uint32_t uint;
    object obj; // panopticon object
    ArrayNode* array;
    BitmapIndexedNode* bitmap;
    HashCollisionNode* collision;
    Trie* trie;
    Node* node; // Recursive referencing.
};

// Binds Type tag with NodeData
struct Node
{
    Type type;
    NodeData data;

    Node() // default constructor sets to NULL
    {
        type = NULL_NODE;
        data.uint = 0;
    }

    Node(Type type, NodeData data) : type(type), data(data) {}
    explicit Node(Trie* trie) : type(TRIE_MAP) { data.trie = trie; }
    explicit Node(ArrayNode* array) : type(ARRAY_NODE) { data.array = array; }
    Node(Type type, uint32_t uint) : type(type) { data.uint = uint; }
    explicit Node(const object& obj) : type(OPTIC_OBJECT) { data.obj = obj; }
    explicit Node(BitmapIndexedNode* bitmap) : type(BITMAP_INDEXED_NODE) { data.bitmap = bitmap; }
    explicit Node(HashCollisionNode* collision) : type(HASH_COLLISION_NODE) { data.collision = collision; }
    Node(const Node& node) { type = node.type; data = node.data; } // Shallow copy constructor
};

// Basic array implementation with range checking
struct NArray
{
    NArray();
    NArray(unsigned int size); // Initializes array
    NArray(const NArray& array); // Shallow copy constructor

    void set(unsigned int index, const Node& value);
    Node at(unsigned int index) const;
    unsigned int size() const { return _size; }

    Node* _array; // Don't use this directly without good reason.
    unsigned int _size;  // Don't use this directly without good reason.
};

Node* next_node(Node* node); // Iterator support

struct NodeSeq // Don' use this directly, this is just for Iterator supprt
{
    Trie* meta;
    NArray nodes;
    Type type;
    unsigned int i;
    NodeSeq* s;
    NodeSeq* cs;

    Entry first();
    NodeSeq* next();
    NodeSeq* cons();
    NodeSeq* with_meta(Trie* meta);

    NodeSeq();
    NodeSeq(Type type, const NArray& nodes, unsigned int i);
    NodeSeq(Type type, const NArray& nodes, unsigned int i, NodeSeq* s, NodeSeq* cs = NULL);
    NodeSeq(Trie* meta, Type type, const NArray& nodes, unsigned int i, NodeSeq* s, NodeSeq* cs = NULL);

private:
    void _init(Trie* meta, Type type, const NArray& nodes, unsigned int i, NodeSeq* s, NodeSeq* cs);
};

NodeSeq* node_seq(Type type, const NArray& nodes, unsigned int i, NodeSeq* s, NodeSeq* cs = NULL);
NodeSeq* node_seq(Node node);
NodeSeq* node_seq(Trie* trie);

struct Iterator // Use this for Trie iteration
{
    Trie* trie;
    NodeSeq* ns;
    Entry* entries;
    Entry next();
    bool has_next();
    Entry cons(); // Previous, COMPLETELY UNTESTED. NEEDS THOROUGH TESTING
    bool has_cons(); // Needs testing
    Iterator(Trie* trie);
    void collect_entries(Entry* entries, unsigned int index, Node node); // recursive collect on Node, constructor calls on trie by default
};

object node_to_object(const Node& node);

struct Entry
{
    uint32_t key;
    panopticon::object obj;

    Entry(uint32_t key, const object& obj) : key(key), obj(obj) {}
    Entry(uint32_t key, const Node& node) : key(key), obj(node_to_object(node)) {}
};

// Persistant Trie structure
// Uses Bit partitioning of 32bit integers into "levels" of 5 bits to track indexes and branching
struct Trie
{
    uint32_t count;
    Node root;
    bool has_null;
    Node null_value;
    Trie* _meta;

    Trie(uint32_t count, Node root, bool has_null, Node null_value) : count(count), root(root), has_null(has_null), null_value(null_value) { _meta = NULL; }
    Trie(Trie* meta, uint32_t count, Node root, bool has_null, Node null_value) : _meta(meta), count(count), root(root), has_null(has_null), null_value(null_value) { }
};

} // Trie namespace

} // Panopticon namespace

#endif // TRIE_H
