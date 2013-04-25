#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <unordered_map>
#include <stack>
#include <string>

namespace panopticon
{

// thread status
enum ThreadStatus
{
    OK = 0,
    YIELD,
    ERRRUN,
    ERRSYNTAX,
    ERRMEM,
    ERRGCMM,
    ERRERR
};

// functions that read/write blocks when loading/dumping Panopticon chunks
// typedef const char*  (*Reader) (State* P, void* ud, size_t* sz);
// typedef int (*Writer) (State* P, const void* p, size_t sz, void* ud);


// prototype for memory-allocation functions
typedef void*  (*Alloc) (void* ud, void* ptr, size_t osize, size_t nsize);

typedef struct State State;

typedef int (*CFunction) (State* P);

// basic types
enum Type
{
    NIL = 0,
    BOOLEAN,
    NUMBER,
    STRING,
    FUNCTION,
    ARRAY,
    MAP
};

// Forward declarations
struct Function;
struct object;

/* typedefs for types in Panopticon */
typedef double Number;
typedef std::vector<object> Array;
typedef std::unordered_map<std::string, object> Map;
typedef std::string String;

// Data type union
typedef union
{
    Number number;
    String* string;
    bool boolean;
    Function* function;
    Array* array;
    Map* map;
} Data;

struct object
{
    Data data;
    Type type;
    unsigned n;
};

struct Function
{
    std::stack<object> stack;
};

} // panopticon namespace

#endif // TYPES_H
