#include <cmath>
#include <iostream>

#include "core/Trie.h"
#include "core/panopticon.h"
#include "core/stack.h"
#include "core/operators.h"
#include "core/container_primitives.h"

namespace panopticon
{

namespace trie
{

// Forward declarations
struct Node;
struct ArrayNode;
struct BitmapIndexedNode;
struct HashCollisionNode;
struct NArray;

Node assoc(Node node, uint32_t  shift, uint32_t  hash, Node key, Node val, Node& addedLeaf);
NArray clone(const NArray& array); // Deep Copy
Node find(Node node, uint32_t shift, uint32_t hash, Node key);
Node without(Node node, uint32_t shift, uint32_t hash, Node key);

// Constants

// Array constants
const uint32_t LEVEL_OFFSET = 5;
const unsigned int NODE_ARRAY_SIZE = 32;
const unsigned int NUM_KEYS = 16;
const unsigned int NUM_VALUES = 16;
const unsigned int COLLISION_ARRAY_SIZE = 4;


//////////////////
/// Trie structs
//////////////////

// Stores null or other nodes
struct ArrayNode
{
    uint32_t count;
    NArray array; // Array of nodes

    ArrayNode(uint32_t count, const NArray& array) : count(count), array(array) {}
};

// mixed object array of keys, values, null and nodes with look up hashing via l337 hacks and bit flipping
struct BitmapIndexedNode
{
    uint32_t bitmap; // bitmap used to find indexes and values
    NArray array; // Mixed array of map keys, map values, null, or Nodes

    BitmapIndexedNode(uint32_t bitmap, const NArray& array) : bitmap(bitmap), array(array) {}
};

struct HashCollisionNode
{
    uint32_t hash;
    uint32_t count;
    NArray array;

    HashCollisionNode(uint32_t hash, uint32_t count, const NArray& array) : hash(hash), count(count), array(array) {}
};

// Struct constants
const Node EMPTY_NODE = Node();
Node EMPTY_NODE_NC = Node(); // non-const
const Trie EMPTY = { 0, Node(), false, Node() };



////////////////////
/// Trie functions
////////////////////

NArray::NArray()
{
    _array = NULL;
    _size = 0;
}

NArray::NArray(unsigned int size)
{
    _array = (Node*) malloc(size * sizeof(Node));
    _size = size;

    for(unsigned int i = 0; i < size; ++i)
    {
        _array[i] = EMPTY_NODE;
    }
}

NArray::NArray(const NArray& array) // Shallow copy
{
    _array = array._array;
    _size = array._size;
}

void NArray::set(unsigned int index, const Node& value)
{
    if(index < _size)
        _array[index] = value;
    else
        std::cerr << "Attempting to set value outside of trie::NArray range" << std::endl;
}

Node NArray::at(unsigned int index) const
{
    if(index < _size)
        return _array[index];
    else
        return EMPTY_NODE;
}

Entry NodeSeq::first()
{
    if(s)
        return s->first();
    else
        return Entry(nodes.at(i).data.uint, nodes.at(i + 1).data.obj);
}

NodeSeq* NodeSeq::next()
{
    if(s)
    {
        return node_seq(type, nodes, i, s->next());
    }

    else
    {
        return node_seq(type, nodes, i + 2, NULL);
    }
}

NodeSeq* NodeSeq::cons()
{
    if(s && i > 0)
    {
        return node_seq(type, nodes, i - 1, s->cons(), this);
    }

    else
    {
        if(i >= 2)
            return node_seq(type, nodes, i - 2, NULL, this);
        else
            return cs;
    }
}

NodeSeq* NodeSeq::with_meta(Trie* meta)
{
    return new NodeSeq(meta, type, nodes, i, s, cs);
}

NodeSeq::NodeSeq()
{
    _init(NULL, NULL_NODE, NArray(), 0, NULL, NULL);
}

NodeSeq::NodeSeq(Type type, const NArray& nodes, unsigned int i)
{
    _init(NULL, type, nodes, i, NULL, NULL);
}

NodeSeq::NodeSeq(Type type, const NArray &nodes, unsigned int i, NodeSeq* s, NodeSeq* cs)
{
    _init(NULL, type, nodes, i, s, cs);
}

NodeSeq::NodeSeq(Trie* meta, Type type, const NArray& nodes, unsigned int i, NodeSeq* s, NodeSeq* cs)
{
    _init(meta, type, nodes, i, s, cs);
}

void NodeSeq::_init(Trie* meta, Type type, const NArray& nodes, unsigned int i, NodeSeq* s, NodeSeq* cs)
{
    this->meta = meta;
    this->type = type;
    this->nodes = nodes;
    this->i = i;
    this->s = s;
    this->cs = cs;
}

void print_node(Node node)
{
    switch(node.type)
    {
    case NULL_NODE:
        std::cout << "NULL_NODE ";
        break;

    case KEY:
        std::cout << "KEY ";
        break;

    case OPTIC_OBJECT:
        std::cout << "OPTIC_OBJECT ";
        break;

    case ARRAY_NODE:
        std::cout << "ARRAY_NODE ";
        break;

    case BITMAP_INDEXED_NODE:
        std::cout << "BITMAP_INDEXED_NODE ";
        break;

    case HASH_COLLISION_NODE:
        std::cout << "HASH_COLLISION_NODE ";
        break;

    case TRIE_MAP:
        std::cout << "TRIE_MAP ";
        break;

    case NODE: // Recursive identity check
        std::cout << "NODE ";
        break;

    default:
        std::cout << "UnknownType: " << node.type;
        break;
    }
}

void print_node_array(const NArray& nodes)
{
    for(unsigned int i = 0; i < nodes.size(); ++i)
    {
        print_node(nodes.at(i));
    }
}

NodeSeq* node_seq(Node node)
{
    switch(node.type)
    {
    case NULL_NODE:
        return NULL;
        break;

    case KEY:
        return NULL;
        break;

    case OPTIC_OBJECT:
        return NULL;
        break;

    case ARRAY_NODE:
        return node_seq(node.type, node.data.array->array, 0, NULL);
        break;

    case BITMAP_INDEXED_NODE:
        return node_seq(node.type, node.data.bitmap->array, 0, NULL);
        break;

    case HASH_COLLISION_NODE:
        return node_seq(node.type, node.data.collision->array, 0, NULL);
        break;

    case TRIE_MAP:
        return node_seq(node.data.trie->root);
        break;

    case NODE: // Recursive identity check
        return node_seq(*node.data.node);
        break;

    default:
        std::cerr << "Unknown Node Type in node::node_seq" << std::endl;
        return NULL;
        break;
    }
}

NodeSeq* node_seq(Type type, const NArray& nodes, unsigned int i, NodeSeq* s, NodeSeq *cs)
{
    // std::cout << "node_seq(Type: " << type << ", NArray.size: " << nodes.size() << ", i: " << i << ", s: " << s << ")" << std::endl;

    if(s)
    {

        return new NodeSeq(NULL, s->type, nodes, i, s, cs);
    }

    else
    {
        if(type == BITMAP_INDEXED_NODE || type == HASH_COLLISION_NODE)
        {
            for(unsigned int j = i; j < nodes.size(); j += 2)
            {
                Node val = nodes.at(j);
                if(val.type != NULL_NODE)
                {
                    return new NodeSeq(NULL, type, nodes, j, NULL, cs);
                }

                val = nodes.at(j + 1);
                if(val.type != NULL_NODE)
                {
                    NodeSeq* ns = node_seq(val);

                    if(ns)
                    {
                        return new NodeSeq(type, nodes, j + 2, ns, cs);
                    }
                }

                break;
            }
        }

        else if(type == ARRAY_NODE)
        {
            for(unsigned int j = i; j < nodes.size(); j++)
            {
                Node val = nodes.at(j);
                if(val.type != NULL_NODE)
                {
                    NodeSeq* ns = node_seq(val);

                    if(ns)
                    {
                        return new NodeSeq(type, nodes, j + 1, ns, cs);
                    }

                    break;
                }
            }
        }

        return NULL;
    }
}

NodeSeq* node_seq(Trie* trie)
{
    return trie->root.type != NULL_NODE ? node_seq(trie->root) : NULL;
}

Iterator::Iterator(Trie *trie) :
    ns(node_seq(trie)),
    trie(trie)
{

}

Entry Iterator::next()
{
    if(ns)
    {
        Entry entry = ns->first();
        ns = ns->next();
        return entry;
    }

    return Entry(0, EMPTY_OBJECT);
}

bool Iterator::has_next()
{
    return ns != NULL;
}

Entry Iterator::cons()
{
    if(ns)
    {
        Entry entry = ns->first();
        ns = ns->cons();
        return entry;
    }

    return Entry(0, EMPTY_OBJECT);
}

bool Iterator::has_cons()
{
    if(ns)
     {
        if(ns->i > 0)
            return true;
        else if(ns->cs != NULL)
            return true;
        else return false;
    }

    else
    {
        return false;
    }
}

object node_to_object(const Node& node)
{
    object obj;

    if(node.type != OPTIC_OBJECT)
    {
        return EMPTY_OBJECT;
    }

    else
    {
        obj = node.data.obj;
        return obj;
    }
}

void recurse_leaf(Node* leaf)
{
    leaf->type = NODE;
    leaf->data.node = leaf;
}

// Create hash value for key
uint32_t hash_key(uint32_t key)
{
    // return key; // May not need this function at all since all our keys are hashed to begin with
    return ((uint64_t) key) ^ ((uint64_t) key >> 32);
    // return fnv1a(key);
}

// Extract 5-bit level
uint32_t mask(uint32_t hash, uint32_t shift)
{
    return (hash >> shift) & 0x01f;
}

// Return the bit position by finding the level via mask
uint32_t bitpos(uint32_t hash, uint32_t shift)
{
    return 1 << mask(hash, shift);
}

uint32_t population_count(uint32_t x)
{
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0f0f0f0f;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x3f;
}

// Count number of 1s to find the index
uint32_t bitmap_index(uint32_t bitmap, uint32_t bit)
{
    return population_count(bitmap & (bit - 1));
}

bool obj_equivalent(object a, object b)
{
    object equal_function;
    equal_function.type = OPERATION;
    equal_function.data.operator_func = equal_to;

    optic_stack.push_back(b);
    optic_stack.push_back(a);
    optic_stack.push_back(equal_function);
    evaluate_top();

    object result = optic_stack.back();
    optic_stack.pop_back();

    if(result.type == BOOL)
        return result.data.boolean;
    else
        return false;
}

// Compare identity of two nodes. Identical pointer values will return true.
bool identical(Node a, Node b)
{
    if(a.type != b.type)
    {
        return false;
    }

    else
    {
        switch(a.type)
        {
        case NULL_NODE:
            return true;
            break;

        case KEY:
            return a.data.uint == b.data.uint;
            break;

        case OPTIC_OBJECT:
            return obj_equivalent(a.data.obj, b.data.obj);
            break;

        case ARRAY_NODE:
            return a.data.array == b.data.array; // We're looking for identity equivalence, ie, ===
            break;

        case BITMAP_INDEXED_NODE:
            return a.data.bitmap == b.data.bitmap; // We're looking for identity equivalence, ie, ===
            break;

        case HASH_COLLISION_NODE:
            return a.data.collision == b.data.collision; // We're looking for identity equivalence, ie, ===
            break;

        case TRIE_MAP:
            return a.data.trie == b.data.trie; // We're looking for identity equivalence, ie, ===
            break;

        case NODE: // Recursive identity check
            return identical(*a.data.node, *b.data.node);
            break;

        default:
            std::cerr << "Unknown Node Type in trie::node_equivalent" << std::endl;
            return false;
            break;
        }
    }
}

NArray empty_node_array()
{
    return NArray(NODE_ARRAY_SIZE);
}

NArray empty_collision_array()
{
    return NArray(COLLISION_ARRAY_SIZE);
}

Node empty_node(Type type)
{
    Node node;
    node.type = type;

    switch(type)
    {
    case NULL_NODE:
        return EMPTY_NODE;
        break;

    case KEY:
        node.data.uint = 0;
        break;

    case OPTIC_OBJECT:
        node.data.obj = EMPTY_OBJECT;
        break;

    case BITMAP_INDEXED_NODE:
        node.data.bitmap = new BitmapIndexedNode(0, NArray(0));
        break;

    case HASH_COLLISION_NODE:
        node.data.collision = new HashCollisionNode(0, 0, empty_collision_array());
        break;

    case TRIE_MAP:
        node.data.trie = new Trie(NULL, 0, Node(), false, Node());
        break;

    case NODE:
        return EMPTY_NODE;
        break;

    default:
        std::cerr << "Unknown Node Type in trie::empty_node" << std::endl;
        return EMPTY_NODE;
        break;
    }

    return node;
}

Node object_node(object obj)
{
    return Node(obj);
}

Node key_node(uint32_t key)
{
    return Node(KEY, key);
}

Node create_node(uint32_t shift, Node key1, Node val1, uint32_t key2hash, Node key2, Node val2)
{
    uint32_t key1hash = hash_key(key1.data.uint);

    if(key1hash == key2hash)
    {
        // std::cout << "create_node: Hash Collision!!" << std::endl;
        NArray array(COLLISION_ARRAY_SIZE);
        array.set(0, key1);
        array.set(1, val1);
        array.set(2, key2);
        array.set(3, val2);

        return Node(new HashCollisionNode(key1hash, 2, array));
    }

    else
    {
        // std::cout << "create_node: Node bitmap" << std::endl;
        Node leaf;
        Node bitmap = empty_node(BITMAP_INDEXED_NODE);
        bitmap = assoc(bitmap, shift, key1hash, key1, val1, leaf);
        bitmap = assoc(bitmap, shift, key2hash, key2, val2, leaf);
        return bitmap;
    }
}

Node clone(const Node& node)
{
    Node new_node;
    new_node.type = node.type;

    switch(node.type)
    {
    case NULL_NODE:
        return EMPTY_NODE;
        break;

    case KEY:
        new_node.data.uint = node.data.uint;
        break;

    case OPTIC_OBJECT:
        new_node.data.obj = mem_copy(node.data.obj);
        break;

    case ARRAY_NODE:
        new_node.data.array = new ArrayNode(node.data.array->count, clone(node.data.array->array));
        break;

    case BITMAP_INDEXED_NODE:
        new_node.data.bitmap = new BitmapIndexedNode(node.data.bitmap->bitmap, clone(node.data.bitmap->array));
        break;

    case HASH_COLLISION_NODE:
        new_node.data.collision = new HashCollisionNode(node.data.collision->hash, node.data.collision->count, clone(node.data.collision->array));
        break;

    case TRIE_MAP:
        new_node.data.trie = new Trie(node.data.trie->_meta, node.data.trie->count, clone(node.data.trie->root), node.data.trie->has_null, clone(node.data.trie->null_value));
        /* // Too deep of a copy?
         new_node.data.trie->_meta = new Trie(
                    node.data.trie->_meta->count,
                    clone(node.data.trie->_meta->root),
                    node.data.trie->_meta->has_null,
                    clone(node.data.trie->_meta->null_value)
        );*/
        break;

    case NODE:
        return EMPTY_NODE;
        break;

    default:
        std::cerr << "Unknown Node Type in trie::clone(const Node& node): " << node.type << std::endl;
        return EMPTY_NODE;
        break;
    }

    return new_node;
}

void clone_range(const NArray& source, unsigned int source_begin, NArray& destination, unsigned int destination_begin, unsigned int range)
{
    for(unsigned int i = 0; i < range; ++i)
    {
        destination.set(destination_begin + i, clone(source.at(source_begin + i)));
    }
}

NArray clone(const NArray& array)
{
    NArray new_array(array.size());

    for(unsigned int i = 0; i < new_array.size(); ++i)
    {
        new_array.set(i, clone(array.at(i)));
    }

    return new_array;
}

NArray clone_and_set(const NArray& array, uint32_t i, Node a)
{
    NArray new_array = clone(array);
    new_array.set(i, a);
    return new_array;
}

NArray clone_and_set(const NArray& array, uint32_t i, Node a, uint32_t j, Node b)
{
    NArray new_array = clone(array);
    new_array.set(i, a);
    new_array.set(j, b);
    return new_array;
}

NArray remove_pair(const NArray& array, unsigned int index)
{
    NArray new_array(array.size() - 2);
    clone_range(array, 0, new_array, 0, 2 * index);
    clone_range(array, 2 * (index + 1), new_array, 2 * index, new_array.size() - (2 * index));
    return new_array;
}


Node array_assoc(Node node, uint32_t shift, uint32_t hash, Node key, Node val, Node& addedLeaf)
{
    uint32_t index = mask(hash, shift);
    Node indexed_node = node.data.array->array.at(index);
    Node new_node;

    if(indexed_node.type == NULL_NODE)
    {
        new_node.type = ARRAY_NODE;
        Node bitmap = empty_node(BITMAP_INDEXED_NODE);
        bitmap = assoc(bitmap, shift + LEVEL_OFFSET, hash, key, val, addedLeaf);
        NArray new_array =  clone_and_set(node.data.array->array, index, bitmap);
        new_node.data.array = new ArrayNode(node.data.array->count + 1, new_array);

        return new_node;
    }

    new_node = assoc(indexed_node, shift + LEVEL_OFFSET, hash, key, val, addedLeaf);

    if(identical(new_node, indexed_node))
    {
        return node;
    }

    else
    {
        return Node(new ArrayNode(node.data.array->count, clone_and_set(node.data.array->array, index, new_node)));
    }
}

Node bitmap_assoc(Node node, uint32_t  shift, uint32_t  hash, Node key, Node val, Node& addedLeaf)
{
    // std::cout << "bitmap_assoc begin" << std::endl;
    // std::cout << "node.data.bitmap->bitmap: " << node.data.bitmap->bitmap << std::endl;
    uint32_t bit = bitpos(hash, shift);
    int index = bitmap_index(node.data.bitmap->bitmap, bit);

    // std::cout << "bitpos(hash, shift) = " << bit << " bitmap_index(bitmap, bit) = " << index << std::endl;
    // std::cout << "node.data.bitmap->bitmap & bit = " << (node.data.bitmap->bitmap & bit) << std::endl;

    // If the index is in the bitmap
    if((node.data.bitmap->bitmap & bit) != 0)
    {
        // std::cout << "(bitmap & bit) != 0" << std::endl;
        Node keyOrNull = node.data.bitmap->array.at(index * 2);
        Node valOrNode = node.data.bitmap->array.at(index * 2 + 1);

        if(keyOrNull.type == NULL_NODE)
        {
            // std::cout << "keyOrNull.type == NULL_NODE" << std::endl;
            Node n = assoc(valOrNode, shift + LEVEL_OFFSET, hash, key, val, addedLeaf);

            if(identical(n, valOrNode))
            {
                // std::cout << "identical(n, valOrNode)" << std::endl;
                return node;
            }

            else
            {
                // std::cout << "Not identical" << std::endl;
                return Node(new BitmapIndexedNode(node.data.bitmap->bitmap, clone_and_set(node.data.bitmap->array, (2 * index) + 1, n)));
            }
        }

        if(key.data.uint == keyOrNull.data.uint)
        {
            // std::cout << "key.data.uint == keyOrNull.data.uint" << std::endl;
            if(identical(valOrNode, val))
            {
                // std::cout << "identical(valOrNode, val)" << std::endl;
                return node;
            }

            // std::cout << "Not identical" << std::endl;
            return Node(new BitmapIndexedNode(node.data.bitmap->bitmap, clone_and_set(node.data.bitmap->array, (2 * index) + 1, val)));
        }

        // std::cout << "create_node" << std::endl;
        // std::cout << "keyOrNull.type = " << keyOrNull.type << std::endl;
        // std::cout << "bitmap_assoc index: " << (2 * index) << std::endl;

        recurse_leaf(&addedLeaf); // self reference
        return Node(
            new BitmapIndexedNode(
                node.data.bitmap->bitmap,
                clone_and_set(
                    node.data.bitmap->array,
                    2 * index,
                    EMPTY_NODE,
                    2 * index + 1,
                    create_node(shift + LEVEL_OFFSET, keyOrNull, valOrNode, hash, key, val)
                )
            )
        );
    }

    else // try adding to the current bitmap
    {
        int num_bits = population_count(node.data.bitmap->bitmap);
        // std::cout << "NUM_BITS: " << num_bits << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

        if(num_bits >= 16) // if we've run out of room create a new ArrayNode
        {
            // std::cout << "num_bits >= 16" << std::endl;
            NArray nodes(NODE_ARRAY_SIZE);
            uint32_t jindex = mask(hash, shift);
            nodes.set(jindex, assoc(EMPTY_NODE, shift + LEVEL_OFFSET, hash, key, val, addedLeaf));
            unsigned int j = 0;

            for(unsigned int i = 0; i < NODE_ARRAY_SIZE; ++i)
            {
                // For each index that is found
                if(((node.data.bitmap->bitmap >> i) & 1) != 0)
                {
                    if(node.data.bitmap->array.at(j).type == NULL_NODE) // if null, copy Node object
                        nodes.set(i, node.data.bitmap->array.at(j + 1));

                    else // otherwise call assoc on the value
                        nodes.set(
                                i,
                                assoc(
                                    EMPTY_NODE,
                                    shift + LEVEL_OFFSET,
                                    hash_key(node.data.bitmap->array.at(j).data.uint),
                                    node.data.bitmap->array.at(j),
                                    node.data.bitmap->array.at(j + 1),
                                    addedLeaf
                                )
                        );

                    j += 2;
                }
            }

            return Node(new ArrayNode(num_bits + 1, nodes));
        }

        else // otherwise, insert into the current bitmap
        {
            // std::cout << "bitmap_assoc: otherwise, insert into the current bitmap" << std::endl;
            // std::cout << "bitmap_assoc: index " << (2 * index) << std::endl;
            NArray new_array(2 * (num_bits + 1));
            clone_range(node.data.bitmap->array, 0, new_array, 0, 2 * index);
            new_array.set(2 * index, key);
            recurse_leaf(&addedLeaf);
            new_array.set(2 * index + 1, val);
            clone_range(node.data.bitmap->array, 2 * index, new_array, 2 * (index + 1), 2 * (num_bits - index));
            // std::cout << "new_array.size(): " << new_array.size() << std::endl;
            // print_node_array(new_array);
            return Node(new BitmapIndexedNode(node.data.bitmap->bitmap | bit, new_array));
        }
    }
}

int find_index(HashCollisionNode* node, Node key)
{
    if(key.type != KEY)
        return -1;

    uint key_val = key.data.uint;

    for(unsigned int i = 0; i < (2 * node->count); i += 2)
    {
        if(node->array.at(i).type == KEY)
            if(key_val == node->array.at(i).data.uint)
                return i;
    }

    return -1;
}


Node collision_assoc(Node node, uint32_t  shift, uint32_t  hash, Node key, Node val, Node& addedLeaf)
{
    if(hash == node.data.collision->hash)
    {
        int index = find_index(node.data.collision, key);

        if(index != -1)
        {
            if(identical(node.data.collision->array.at(index + 1), val))
                return node;
            else
                return Node(new HashCollisionNode(hash, node.data.collision->count, clone_and_set(node.data.collision->array, index + 1, val)));
        }

        NArray new_array(node.data.collision->array.size() + 2);
        clone_range(node.data.collision->array, 0, new_array, 0, node.data.collision->array.size());

        new_array.set(node.data.collision->array.size(), key);
        new_array.set(node.data.collision->array.size() + 1, val);
        recurse_leaf(&addedLeaf);

        return Node(new HashCollisionNode(hash, node.data.collision->count + 1, new_array));
    }

    // nest in a bitmap node
    NArray bitmap_array(2);
    bitmap_array.set(0, EMPTY_NODE);
    bitmap_array.set(1, node);

    Node bitmap_node(new BitmapIndexedNode(bitpos(node.data.collision->hash, shift), bitmap_array));
    return assoc(bitmap_node, shift, hash, key, val, addedLeaf);
}

Node trie_assoc(Node node, Node key, Node val)
{
    if(key.type == NULL_NODE)
    {
        // std::cout << "trie::trie_assoc key.type == NULL_NODE" << std::endl;
        if(node.data.trie->has_null && identical(val, node.data.trie->null_value))
        {
            return node;
        }

        else
        {
            // We need to figure out how to get the GC to track this so it doesn't end up leaking!
            return Node(
                new Trie(
                    node.data.trie->_meta,
                    node.data.trie->has_null ? node.data.trie->count : node.data.trie->count + 1,
                    node.data.trie->root,
                    true,
                    val
                )
            );
        }
    }

    Node addedLeaf;
    Node new_root;

    if(node.data.trie->root.type == NULL_NODE)
        new_root = empty_node(BITMAP_INDEXED_NODE);
    else
        new_root = node.data.trie->root;

    // std::cout << "key.data.uint: " << key.data.uint << std::endl;
    // std::cout << "hash_key(key.data.uint) = " << hash_key(key.data.uint) << std::endl;
    new_root = assoc(new_root, 0, hash_key(key.data.uint), key, val, addedLeaf);

    if(identical(new_root, node.data.trie->root))
    {
        // std::cout << "trie_assoc identical(new_root, node.data.trie->root) == true" << std::endl;
        return node;
    }

    // std::cout << "trie_assoc: New Trie!" << std::endl;
    return Node(
        new Trie(
            node.data.trie->_meta,
            addedLeaf.type == NULL_NODE ? node.data.trie->count : node.data.trie->count + 1,
            new_root,
            node.data.trie->has_null,
            node.data.trie->null_value
        )
    );
}

Node assoc(Node node, uint32_t  shift, uint32_t  hash, Node key, Node val, Node& addedLeaf)
{
    switch(node.type)
    {
    case NULL_NODE: // Nothing
        return node;
        break;

    case KEY:
        return node; // Not sure what to do do here. This probably shouldn'tever happen
        break;

    case OPTIC_OBJECT:
        return node; // just return the node? This probably shouldn't ever happen
        break;

    case ARRAY_NODE:
        return array_assoc(node, shift, hash, key, val, addedLeaf);
        break;

    case BITMAP_INDEXED_NODE:
        return bitmap_assoc(node, shift, hash, key, val, addedLeaf);
        break;

    case HASH_COLLISION_NODE:
        return collision_assoc(node, shift, hash, key, val, addedLeaf);
        break;

    case TRIE_MAP:
        return trie_assoc(node, key, val);
        std::cerr << "trie_assoc called from assoc, not sure this should happen????" << std::endl;
        break;

    case NODE: // Recursive apply?
        return assoc(*node.data.node, shift, hash, key, val, addedLeaf);
        break;

    default:
        std::cerr << "Unknown Node Type in trie::assoc" << std::endl;
        return EMPTY_NODE;
        break;
    }
}

Node array_find(Node node, uint32_t shift, uint32_t hash, Node key)
{
    uint32_t index = mask(hash, shift);
    Node indexed_node = node.data.array->array.at(index);

    if(indexed_node.type == NULL_NODE)
        return indexed_node;
    else
        return find(indexed_node, shift + LEVEL_OFFSET, hash, key);
}

Node bitmap_find(Node node, uint32_t shift, uint32_t hash, Node key)
{
    uint32_t bit = bitpos(hash, shift);

    if((node.data.bitmap->bitmap & bit) == 0)
    {
        return EMPTY_NODE;
    }

    else
    {
        uint32_t index = bitmap_index(node.data.bitmap->bitmap, bit);
        Node keyOrNull = node.data.bitmap->array.at(2 * index);
        Node valOrNode = node.data.bitmap->array.at(2 * index + 1);

        if(keyOrNull.type == NULL_NODE)
        {
            return find(valOrNode, shift + LEVEL_OFFSET, hash, key);
        }

        else
        {
            if(identical(key, keyOrNull))
                return valOrNode;

            return EMPTY_NODE;
        }
    }
}

Node collision_find(Node node, uint32_t shift, uint32_t hash, Node key)
{
    int index = find_index(node.data.collision, key);

    if(index < 0)
        return EMPTY_NODE;

    if(identical(key, node.data.collision->array.at(index)))
        return node.data.collision->array.at(index + 1);

    return EMPTY_NODE;
}

Node find(Node node, uint32_t shift, uint32_t hash, Node key)
{
    if(key.type == NULL_NODE)
        return EMPTY_NODE;

    switch(node.type)
    {
    case NULL_NODE: // Nothing
        return node;
        break;

    case KEY:
        return EMPTY_NODE; // Can't find anything inside a key itself!
        break;

    case OPTIC_OBJECT:
        return node; // We found the object?
        break;

    case ARRAY_NODE:
        return array_find(node, shift, hash, key);
        break;

    case BITMAP_INDEXED_NODE:
        return bitmap_find(node, shift, hash, key);
        break;

    case HASH_COLLISION_NODE:
        return collision_find(node, shift, hash, key);
        break;

    case TRIE_MAP:
        return find(node.data.trie->root, shift, hash, key);
        break;

    case NODE: // Recursive apply?
        return find(*node.data.node, shift, hash, key);
        break;

    default:
        std::cerr << "Unknown Node Type in trie::assoc" << std::endl;
        return EMPTY_NODE;
        break;
    }
}

Node pack(Node node, uint32_t index)
{
    NArray new_array(2 * (node.data.array->count - 1));
    uint32_t j = 1;
    uint32_t bitmap = 0;

    for(uint32_t i = 0; i < index; ++i)
    {
        Node val = node.data.array->array.at(i);
        if(val.type != NULL_NODE)
        {
            new_array.set(j, val);
            bitmap |= 1 << i;
            j += 2;
        }
    }

    for(uint32_t i = index; i < node.data.array->array.size(); ++i)
    {
        Node val = node.data.array->array.at(i);
        if(val.type != NULL_NODE)
        {
            new_array.set(j, val);
            bitmap |= 1 << i;
            j += 2;
        }
    }

    return Node(new BitmapIndexedNode(bitmap, new_array));
}

Node array_without(Node node, uint32_t shift, uint32_t hash, Node key)
{
    uint32_t index = mask(hash, shift);
    Node indexed_node = node.data.array->array.at(index);

    if(indexed_node.type == NULL_NODE)
        return node;

    Node n = without(indexed_node, shift + LEVEL_OFFSET, hash, key);
    if(n.type == NULL_NODE)
    {
        if(node.data.array->count <= 8) // shrink
            return pack(node, index);

        return Node(new ArrayNode(node.data.array->count - 1, clone_and_set(node.data.array->array, index, n)));
    }

    else
    {
        return Node(new ArrayNode(node.data.array->count, clone_and_set(node.data.array->array, index, n)));
    }
}

Node bitmap_without(Node node, uint32_t shift, uint32_t hash, Node key)
{
    uint32_t bit = bitpos(hash, shift);

    if((node.data.bitmap->bitmap & bit) == 0) // index not found
        return node;

    uint32_t index = bitmap_index(node.data.bitmap->bitmap, bit);
    Node keyOrNull = node.data.bitmap->array.at(2 * index);
    Node valOrNode = node.data.bitmap->array.at(2 * index + 1);

    if(keyOrNull.type == NULL_NODE) // value is node because key is null
    {
        Node n = without(valOrNode, shift + LEVEL_OFFSET, hash, key);
        if(identical(n, valOrNode))
            return node;

        if(n.type != NULL_NODE)
            return Node(new BitmapIndexedNode(node.data.bitmap->bitmap, clone_and_set(node.data.bitmap->array, 2 * index + 1, n)));

        if(node.data.bitmap->bitmap == bit)
            return EMPTY_NODE;

        return Node(new BitmapIndexedNode(node.data.bitmap->bitmap ^ bit, remove_pair(node.data.bitmap->array, index)));
    }

    if(identical(key, keyOrNull)) // Found
        return Node(new BitmapIndexedNode(node.data.bitmap->bitmap ^ bit, remove_pair(node.data.bitmap->array, index)));

    return node;
}

Node collision_without(Node node, uint32_t shift, uint32_t hash, Node key)
{
    int index = find_index(node.data.collision, key);
    if(index == -1)
        return node;

    if(node.data.collision->count == 1)
        return EMPTY_NODE;

    return Node(new HashCollisionNode(node.data.collision->hash, node.data.collision->count - 1, remove_pair(node.data.collision->array, index / 2)));
}

Node without(Node node, uint32_t shift, uint32_t hash, Node key)
{
    if(key.type == NULL_NODE)
        return node;

    switch(node.type)
    {
    case NULL_NODE: // Nothing
        return node;
        break;

    case KEY: // This should probably never be reached
        if(identical(node, key))
            return EMPTY_NODE;
        else
            return node;
        break;

    case OPTIC_OBJECT:
        return node; // Should probably never be reached
        break;

    case ARRAY_NODE:
        return array_without(node, shift, hash, key);
        break;

    case BITMAP_INDEXED_NODE:
        return bitmap_without(node, shift, hash, key);
        break;

    case HASH_COLLISION_NODE:
        return collision_without(node, shift, hash, key);
        break;

    case TRIE_MAP:
        return Node(without(node.data.trie, key.data.uint));
        break;

    case NODE: // Recursive apply?
        return without(*node.data.node, shift, hash, key);
        break;

    default:
        std::cerr << "Unknown Node Type in trie::assoc" << std::endl;
        return EMPTY_NODE;
        break;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Trie Interface Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Trie* new_trie()
{
    return new Trie(NULL, 0, Node(), false, Node());
}

Trie* create(Entry* entry_array, unsigned int size)
{
    Node trie_node = empty_node(TRIE_MAP);

    for(unsigned int i = 0; i < size; ++i)
    {
        trie_node = trie_assoc(
            trie_node,
            key_node(entry_array[i].key),
            object_node(entry_array[i].obj)
        );
    }

    return trie_node.data.trie;
}

bool contains(Trie* trie, uint32_t key)
{
    return trie->root.type != NULL_NODE
            ? find(trie->root, 0, hash_key(key), key_node(key)).type != NULL_NODE
            : false;
}

Entry entry(Trie* trie, uint32_t key)
{
    return trie->root.type != NULL_NODE
            ? Entry(key, find(trie->root, 0, hash_key(key), key_node(key)))
            : Entry(key, EMPTY_NODE);
}

object lookup(Trie* trie, uint32_t key)
{
    return trie->root.type != NULL_NODE
            ? node_to_object(find(trie->root, 0, hash_key(key), key_node(key)))
            : EMPTY_OBJECT;
}

bool contains(Trie* trie, Node key)
{
    if(key.type == KEY)
        return contains(trie, key.data.uint);
    else
        return trie->has_null;
}

Entry entry(Trie* trie, Node key)
{
    if(key.type == NULL_NODE)
        return Entry(key.data.uint, EMPTY_NODE);
    else
        return entry(trie, key.data.uint);
}

object lookup(Trie* trie, Node key)
{
    if(key.type == NULL_NODE)
        return EMPTY_OBJECT;
    else
        return lookup(trie, key.data.uint);
}

Trie* insert(Trie* trie, uint32_t key, const object &value)
{
    Node new_trie = trie_assoc(Node(trie), key_node(key), Node(value));

    if(new_trie.type == TRIE_MAP)
        return new_trie.data.trie;
    else
        return NULL; // Something went wrong!
}

Trie* without(Trie* trie, uint32_t key)
{
    if(trie->root.type == NULL_NODE)
    {
        return trie;
    }

    else
    {
        Node new_root = without(trie->root, 0, hash_key(key), key_node(key));
        if(identical(new_root, trie->root))
            return trie;

        return new Trie(trie->_meta, trie->count - 1, new_root, trie->has_null, trie->null_value);
    }
}

Trie* without(Trie* trie, Node key)
{
    if(key.type == NULL_NODE)
        return trie->has_null
                ? new Trie(trie->_meta, trie->count - 1, trie->root, false, EMPTY_NODE)
                : trie;
    else
        return without(trie, key.data.uint);
}

Iterator iterator(Trie* trie)
{
    return Iterator(trie);
}

// Calls func on each element of the Trie. Performs no mutation and does not return a new trie
void map(Node& node, trie_map_function func, Node& previous_node)
{
    Node next_node = EMPTY_NODE_NC;

    switch(node.type)
    {
    case NULL_NODE:
        return;
        break;

    case KEY:
        break;

    case OPTIC_OBJECT:
        func(previous_node.data.uint, node.data.obj);
        break;

    case ARRAY_NODE:

        previous_node = node;
        for(unsigned int i = 0; i < node.data.array->array.size(); ++i)
        {
            next_node = node.data.array->array.at(i);
            map(next_node, func, previous_node);
            previous_node = next_node;
        }

        return;
        break;

    case BITMAP_INDEXED_NODE:

        previous_node = node;
        for(unsigned int i = 0; i < node.data.bitmap->array.size(); ++i)
        {
            next_node = node.data.bitmap->array.at(i);
            map(next_node, func, previous_node);
            previous_node = next_node;
        }

        return;
        break;

    case HASH_COLLISION_NODE:

        previous_node = node;
        for(unsigned int i = 0; i < node.data.collision->array.size(); ++i)
        {
            next_node = node.data.collision->array.at(i);
            map(next_node, func, previous_node);
            previous_node = next_node;
        }

        return;
        break;

    case TRIE_MAP:
        next_node = node.data.trie->root;
        break;

    case NODE: // Recursive identity check
        next_node = *node.data.node;
        break;

    default:
        std::cerr << "Unknown Node Type in trie::map_trie" << std::endl;
        return;
        break;
    }

    if(next_node.type == NULL_NODE)
        return;

    return map(next_node, func, node);
}

void map(Trie *trie, trie_map_function func)
{
    Node trie_node(trie);
    return map(trie_node, func, EMPTY_NODE_NC);
}

void map_func_to_trie(Node* new_trie, const object& function, Dictionary& context, const unsigned int& key, const object& value)
{
    object res;
    call_func_on_item(res, function, value, context);
    new_trie->data.trie = trie_assoc(Node(new_trie->data.trie), key_node(key), Node(res)).data.trie;
}

// Returns a new trie (via Node* trie) that has had the object_function called on each element. Trie is persistent so no mutation occurs
void map(Node* trie, Node& node, new_trie_map_function map_function, const object& object_function, Dictionary& context, Node& previous_node)
{
    Node next_node = EMPTY_NODE_NC;

    switch(node.type)
    {
    case NULL_NODE:
        return;
        break;

    case KEY:
        break;

    case OPTIC_OBJECT:
        map_function(trie, object_function, context, previous_node.data.uint, node.data.obj);
        break;

    case ARRAY_NODE:

        previous_node = node;
        for(unsigned int i = 0; i < node.data.array->array.size(); ++i)
        {
            next_node = node.data.array->array.at(i);
            map(trie, next_node, map_function, object_function, context, previous_node);
            previous_node = next_node;
        }

        return;
        break;

    case BITMAP_INDEXED_NODE:

        previous_node = node;
        for(unsigned int i = 0; i < node.data.bitmap->array.size(); ++i)
        {
            next_node = node.data.bitmap->array.at(i);
            map(trie, next_node, map_function, object_function, context, previous_node);
            previous_node = next_node;
        }

        return;
        break;

    case HASH_COLLISION_NODE:

        previous_node = node;
        for(unsigned int i = 0; i < node.data.collision->array.size(); ++i)
        {
            next_node = node.data.collision->array.at(i);
            map(trie, next_node, map_function, object_function, context, previous_node);
            previous_node = next_node;
        }

        return;
        break;

    case TRIE_MAP:
        next_node = node.data.trie->root;
        break;

    case NODE: // Recursive identity check
        next_node = *node.data.node;
        break;

    default:
        std::cerr << "Unknown Node Type in trie::map_trie" << std::endl;
        return;
        break;
    }

    if(next_node.type == NULL_NODE)
        return;

    return map(trie, next_node, map_function, object_function, context, node);
}

bool map(Trie* trie, object& result, new_trie_map_function map_function, const object& object_function, Dictionary& context)
{
    if(!trie)
    {
        result.type = NIL;
        result.data.number = 0;
        return false;
    }

    Node new_trie_node(trie);
    Node begin_node(trie);
    map(&new_trie_node, begin_node, map_function, object_function, context, EMPTY_NODE_NC);
    result.type = TRIE;
    result.data.trie = new_trie_node.data.trie;
    return true;
}

bool map(Trie* trie, object& result, const object& function, Dictionary& context)
{
    return map(trie, result, map_func_to_trie, function, context);
}

void filter_func_to_trie(Node* new_trie, const object& function, Dictionary& context, const unsigned int& key, const object& value)
{
    object res;
    call_func_on_item(res, function, value, context);

    if(!res.data.boolean)
        new_trie->data.trie = without(new_trie->data.trie, key_node(key));
}

bool filter(Trie* trie, object& result, const object& function, Dictionary& context)
{
    return map(trie, result, filter_func_to_trie, function, context);
}

} // trie namespace

} // Panopticon namespace
