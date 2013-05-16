#include <deque>
#include <iostream>

#include "include/core/Memory.h"

namespace panopticon
{
std::deque<object> dealloc_queue;
int num_arrays = 0;
int num_ARRAY = 0;
int num_STATEMENT_LIST = 0;
int num_OPERATION_TREE = 0;
int num_GUARD = 0;
int num_FUNCTION_BODY = 0;
int num_FUNCTION_ARG_NAMES = 0;
int num_FUNCTION_ARG_VALUES = 0;
int num_CONDITION_TREE = 0;
int num_strings = 0;
int num_dictionaries = 0;
int num_functions = 0;
bool collecting = false;
// gc_count accounts for the number of allocated objects
// It is only incremented when the "new" keyword is used on an object
// It is only decremened when the "delete" keyword is used on an object
// If everything works correctly they should mirror
int gc_count = 0;

void gc_report()
{
    std::cout << "==========================================================" << std::endl;
    std::cout << "Leaked Arrays: " << num_arrays << std::endl;
    std::cout << "    Array Types:" << std::endl;
    std::cout << "    Leaked ARRAYS: " << num_ARRAY << std::endl;
    std::cout << "    Leaked STATEMENT_LISTS: " << num_STATEMENT_LIST << std::endl;
    std::cout << "    Leaked OPERATION_TREES: " << num_OPERATION_TREE << std::endl;
    std::cout << "    Leaked GUARDS: " << num_GUARD << std::endl;
    std::cout << "    Leaked FUNCTION_BODYS: " << num_FUNCTION_BODY << std::endl;
    std::cout << "    Leaked FUNCTION_ARG_NAMES: " << num_FUNCTION_ARG_NAMES << std::endl;
    std::cout << "    Leaked FUNCTION_ARG_VALUES: " << num_FUNCTION_ARG_VALUES << std::endl;
    std::cout << "    Leaked CONDITION_TREES: " << num_CONDITION_TREE << std::endl;
    std::cout << "Leaked Strings: " << num_strings << std::endl;
    std::cout << "Leaked Dictionaries: " << num_dictionaries << std::endl;
    std::cout << "Leaked Functions: " << num_functions << std::endl;
    std::cout << "==========================================================" << std::endl;
}

void increment_array(Type type)
{
    ++gc_count;
    ++num_arrays;
    std::cout << "new Array(" << type_string(type) << ")" << std::endl;

    switch(type)
    {
    case ARRAY:
        ++num_ARRAY;
        break;
    case STATEMENT_LIST:
        ++num_STATEMENT_LIST;
        break;
    case OPERATION_TREE:
        ++num_OPERATION_TREE;
        break;
    case GUARD:
        ++num_GUARD;
        break;
    case FUNCTION_BODY:
        ++num_FUNCTION_BODY;
        break;
    case FUNCTION_ARG_NAMES:
        ++num_FUNCTION_ARG_NAMES;
        break;
    case FUNCTION_ARG_VALUES:
        ++num_FUNCTION_ARG_VALUES;
        break;
    case CONDITION_TREE:
        ++num_CONDITION_TREE;
        break;
    }
}

void increment_string()
{
    ++gc_count;
    ++num_strings;
    std::cout << "new String()" << std::endl;
}

void increment_dictionary()
{
    ++gc_count;
    ++num_dictionaries;
    std::cout << "new Dictionary()" << std::endl;
}

void increment_function()
{
    ++gc_count;
    ++num_functions;
    std::cout << "new Function()" << std::endl;
}

void decrement_array(Type type)
{
    --gc_count;
    --num_arrays;
    std::cout << "delete Array(" << type_string(type) << ")" << std::endl;

    switch(type)
    {
    case ARRAY:
        --num_ARRAY;
        break;
    case STATEMENT_LIST:
        --num_STATEMENT_LIST;
        break;
    case OPERATION_TREE:
        --num_OPERATION_TREE;
        break;
    case GUARD:
        --num_GUARD;
        break;
    case FUNCTION_BODY:
        --num_FUNCTION_BODY;
        break;
    case FUNCTION_ARG_NAMES:
        --num_FUNCTION_ARG_NAMES;
        break;
    case FUNCTION_ARG_VALUES:
        --num_FUNCTION_ARG_VALUES;
        break;
    case CONDITION_TREE:
        --num_CONDITION_TREE;
        break;
    }
}

void decrement_string()
{
    --gc_count;
    --num_strings;
    std::cout << "delete String" << std::endl;
}

void decrement_dictionary()
{
    --gc_count;
    --num_dictionaries;
    std::cout << "delete Dictionary" << std::endl;
}

void decrement_function()
{
    --gc_count;
    --num_functions;
    std::cout << "delete Function" << std::endl;
}

void gc_delete(object& obj); // forward declaration

 void gc_delete_array(Array* array, Type type)
{
    if(array)
    {
        Array::iterator iter = array->begin();

        while(iter != array->end())
        {
            mem_free(*iter);
            ++iter;
        }

        array->clear();
        decrement_array(type);
        delete array;
        array = 0;
    }

    else
    {
        std::cerr << "Attempted to gc_delete_array on a null pointer." << std::endl;
    }
}

void gc_delete_array(Array& array)
{
    Array::iterator iter = array.begin();

    while(iter != array.end())
    {
        mem_free(*iter);
        ++iter;
    }

    array.clear();
}

void mem_free_array(Array& array)
{
    Array::iterator iter = array.begin();

    while(iter != array.end())
    {
        mem_free(*iter);
        ++iter;
    }

    array.clear();
}

void shallow_mem_free_array(Array* array, Type type)
{
    if(array)
    {
        decrement_array(type);
        delete array;
        array = 0;
    }

    else
    {
        std::cerr << "Attempted to shallo_mem_free_array on a null pointer." << std::endl;
    }
}

void gc_delete_dictionary(Dictionary* dictionary)
{
    if(dictionary)
    {
        Dictionary::iterator iter = dictionary->begin();

        while(iter != dictionary->end())
        {

            mem_free(iter->second);
            ++iter;
        }

        dictionary->clear();
        decrement_dictionary();
        delete dictionary;
        dictionary = 0;
    }

    else
    {
        std::cerr << "Attempted to gc_delete_dictionary on a null pointer." << std::endl;
    }
}

void gc_delete_dictionary(Dictionary& dictionary)
{
    Dictionary::iterator iter = dictionary.begin();

    while(iter != dictionary.end())
    {
        mem_free(iter->second);
        ++iter;
    }

    dictionary.clear();
}

void mem_free_dictionary(Dictionary& dictionary)
{
    Dictionary::iterator iter = dictionary.begin();

    while(iter != dictionary.end())
    {
        mem_free(iter->second);
        ++iter;
    }

    dictionary.clear();
}

void gc_delete_function(Function* function)
{
    if(function)
    {
        if(function->name.size()>0&&function->name.size()<25)
        {
            std::cout  << "deleting function: " << function->name << std::endl;
        }
        else
        {
            std::cout  << "deleting function with no name" << std::endl;

        }

        gc_delete_array(function->arguments);
        mem_free(function->body);
        gc_delete_dictionary(function->heap);

        decrement_function();
        delete function;
        function = 0;
    }

    else
    {
        std::cerr << "Attempted to gc_delete_function on a null pointer." << std::endl;
    }
}

void gc_delete_string(String* string)
{
    if(string)
    {
        decrement_string();
        delete string;
        string = 0;
    }

    else
    {
        std::cerr << "Attempted to gc_delete_string on a null pointer." << std::endl;
    }
}

void gc_delete(object& obj)
{
    std::cout << "gc_delete obj.type = " << panopticon::type_string(obj.type) << std::endl;
    switch(obj.type)
    {
    case NIL:
        break;
    case BOOL:
        break;
    case NUMBER:
        break;
    case STRING:
        gc_delete_string(obj.data.string);
        break;
    case FUNCTION:
        gc_delete_function(obj.data.function);
        break;
    case ARRAY:
        gc_delete_array(obj.data.array, ARRAY);
        break;
    case DICTIONARY:
        gc_delete_dictionary(obj.data.dictionary);
        break;
    case ERROR:
        break;
    case STATEMENT_LIST:
        gc_delete_array(obj.data.array, STATEMENT_LIST);
        break;
    case VARIABLE:
        gc_delete_string(obj.data.string);
        break;
    case UNDECLARED_VARIABLE:
        gc_delete_string(obj.data.string);
        break;
    case OPERATION_TREE:
        gc_delete_array(obj.data.array, OPERATION_TREE);
        break;
    case OPERATION:
        break;
    case UNARY_OPERATION:
        break;
    case ASSIGNMENT:
        break;
    case GUARD:
       gc_delete_array(obj.data.array, GUARD);
        break;
    case FUNCTION_BODY:
        gc_delete_array(obj.data.array, FUNCTION_BODY);
        break;
    case FUNCTION_ARG_NAMES:
        gc_delete_array(obj.data.array, FUNCTION_ARG_NAMES);
        break;
    case FUNCTION_ARG_VALUES:
        gc_delete_array(obj.data.array, FUNCTION_ARG_VALUES);
        break;
    case VOID:
        break;
    case CODE_BLOCK:
        break;
    case PRIMITIVE:
        break;
    case CONDITION_TREE:
        gc_delete_array(obj.data.array, CONDITION_TREE);
        break;
    case CONDITION_BRANCH:
        break;
    case NO_EXPANSION_OPERATION:
        break;
    case UNARY_NO_EXPANSION_OPERATION:
        break;
    case PATTERN:
        break;
    case HEAD:
        break;
    case TAIL:
        break;
    case FAILED_CONDITION:
        break;
    }
}

void gc_free_all()
{
    int i = 0;
    collecting = true;

    while(dealloc_queue.size())
    {
//        std::cout << "dealloc_queue.size: " << dealloc_queue.size() << std::endl;
        gc_delete(dealloc_queue.front());
        dealloc_queue.pop_front();
        ++i;
    }

    if(gc_count != 0)
    {
        std::cerr << "Warning: some memory may not be collectable by the garbage collector, there may be possible memory leaks." << std::endl;
        std::cout << "gc_count: " << gc_count << std::endl;
        // gc_count = 0; // If dealloc_queue.size == 0 then gc_count should be 0 as well. If it is not, then likely we've missed something
    }

    std::cout << "Garbage Collector freed: " << i << " objects." << std::endl;
    collecting = false;
}

void gc_sweep()
{
    if((dealloc_queue.size() > MAX_GC_OBJECTS) && !collecting)
    {
        gc_free_all();
    }
}

object mem_string_alloc(const char* string)
{
    object obj;
    obj.type = STRING;
    obj.data.string = new String(string);
    increment_string();
    return obj;
}

object mem_string_alloc(Type type, const char* string)
{
    object obj;
    obj.type = type;
    obj.data.string = new String(string);
    increment_string();
    return obj;
}

object mem_alloc(Type type)
{
    object obj;
    obj.type = type;

    switch(type)
    {
    case NIL:
        obj.data.number = 0;
        break;
    case BOOL:
        obj.data.boolean = false;
        break;
    case NUMBER:
        obj.data.number = 0;
        break;
    case STRING:
        increment_string();
        obj.data.string = new String();
        break;
    case FUNCTION:
        increment_function();
        obj.data.function = new Function();
        break;
    case ARRAY:
        increment_array(ARRAY);
        obj.data.array = new Array();
        break;
    case DICTIONARY:
        increment_dictionary();
        obj.data.dictionary = new Dictionary();
        break;
    case ERROR:
        break;
    case STATEMENT_LIST:
        increment_array(STATEMENT_LIST);
        obj.data.array = new Array();
        break;
    case VARIABLE:
        increment_string();
        obj.data.string = new String();
        break;
    case UNDECLARED_VARIABLE:
        increment_string();
        obj.data.string = new String();
        break;
    case OPERATION_TREE:
        increment_array(OPERATION_TREE);
        obj.data.array = new Array();
        break;
    case OPERATION:
        break;
    case UNARY_OPERATION:
        break;
    case ASSIGNMENT:
        break;
    case GUARD:
        increment_array(GUARD);
        obj.data.array = new Array();
        break;
    case FUNCTION_BODY:
        increment_array(FUNCTION_BODY);
        obj.data.array = new Array();
        break;
    case FUNCTION_ARG_NAMES:
        increment_array(FUNCTION_ARG_NAMES);
        obj.data.array = new Array();
        break;
    case FUNCTION_ARG_VALUES:
        increment_array(FUNCTION_ARG_VALUES);
        obj.data.array = new Array();
        break;
    case VOID:
        break;
    case CODE_BLOCK:
        break;
    case PRIMITIVE:
        break;
    case CONDITION_TREE:
        increment_array(CONDITION_TREE);
        obj.data.array = new Array();
        break;
    case CONDITION_BRANCH:
        break;
    case NO_EXPANSION_OPERATION:
        break;
    case UNARY_NO_EXPANSION_OPERATION:
        break;
    case PATTERN:
        break;
    case HEAD:
        break;
    case TAIL:
        break;
    case FAILED_CONDITION:
        break;
    }

    gc_sweep();
    return obj;
}

void mem_free(object obj)
{
    std::cout << "mem_free" << std::endl;
    // dealloc_queue.push_back(obj);
    gc_delete(obj);
}

Array* copy_array(Array* array)
{
    Array* new_array =  new Array();
    Array::iterator iter = array->begin();

    while(iter != array->end())
    {
        new_array->push_back(mem_copy(*iter));
        ++iter;
    }

    return new_array;
}

Array copy_array(const Array& array)
{
    Array new_array;
    Array::const_iterator iter = array.begin();

    while(iter != array.end())
    {
        new_array.push_back(mem_copy(*iter));
        ++iter;
    }

    return new_array;
}

Dictionary copy_dictionary(const Dictionary& dictionary)
{
    Dictionary new_dictionary;
    Dictionary::const_iterator iter = dictionary.begin();

    while(iter != dictionary.end())
    {
        new_dictionary.insert(
            std::make_pair(
                iter->first,
                mem_copy(iter->second)
            )
        );

        ++iter;
    }

    return new_dictionary;
}

Dictionary* copy_dictionary(Dictionary* dictionary)
{
    increment_dictionary();
    Dictionary* new_dictionary =  new Dictionary();
    Dictionary::iterator iter = dictionary->begin();

    while(iter != dictionary->end())
    {
        new_dictionary->insert(
            std::make_pair(
                iter->first,
                mem_copy(iter->second)
            )
        );

        ++iter;
    }

    return new_dictionary;
}


Function* copy_function(const Function* function)
{
    increment_function();
    Function* new_function = new Function();
    new_function->arguments = copy_array(function->arguments);
    new_function->body = mem_copy(function->body);
    new_function->heap = copy_dictionary(function->heap);
    new_function->name = function->name;
    new_function->num_arguments = function->num_arguments;

    return new_function;
}

object mem_copy(const object &obj)
{
    object new_object;
    new_object.type = obj.type;

    switch(obj.type)
    {
    case NIL:
        new_object.data.number = 0;
        break;
    case BOOL:
        new_object.data.boolean = obj.data.boolean;
        break;
    case NUMBER:
        new_object.data.number = obj.data.number;
        break;
    case STRING:
        increment_string();
        new_object.data.string = new String(*obj.data.string);
        break;
    case FUNCTION:
        new_object.data.function = copy_function(obj.data.function);
        break;
    case ARRAY:
        increment_array(ARRAY);
        new_object.data.array = copy_array(obj.data.array);
        break;
    case DICTIONARY:
        new_object.data.dictionary = copy_dictionary(obj.data.dictionary);
        break;
    case ERROR:
        new_object.data.number = obj.data.number;
        break;
    case STATEMENT_LIST:
        increment_array(STATEMENT_LIST);
        new_object.data.array = copy_array(obj.data.array);
        break;
    case VARIABLE:
        increment_string();
        new_object.data.string = new String(*obj.data.string);
        break;
    case UNDECLARED_VARIABLE:
        increment_string();
        new_object.data.string = new String(*obj.data.string);
        break;
    case OPERATION_TREE:
        increment_array(OPERATION_TREE);
        new_object.data.array = copy_array(obj.data.array);
        break;
    case OPERATION:
        new_object.data.operator_func = obj.data.operator_func;
        break;
    case UNARY_OPERATION:
        new_object.data.unary_operator_func = obj.data.unary_operator_func;
        break;
    case ASSIGNMENT:
        new_object.data.operator_func = obj.data.operator_func;
        break;
    case GUARD:
        increment_array(GUARD);
        new_object.data.array = copy_array(obj.data.array);
        break;
    case FUNCTION_BODY:
        increment_array(FUNCTION_BODY);
        new_object.data.array = copy_array(obj.data.array);
        break;
    case FUNCTION_ARG_NAMES:
        increment_array(FUNCTION_ARG_NAMES);
        new_object.data.array = copy_array(obj.data.array);
        break;
    case FUNCTION_ARG_VALUES:
        increment_array(FUNCTION_ARG_VALUES);
        new_object.data.array = copy_array(obj.data.array);
        break;
    case VOID: // don't copy
        break;
    case CODE_BLOCK:
        break;
    case PRIMITIVE: // Not implemented yet
        break;
    case CONDITION_TREE:
        increment_array(CONDITION_TREE);
        new_object.data.array = copy_array(obj.data.array);
        break;
    case CONDITION_BRANCH:
        break;
    case NO_EXPANSION_OPERATION:
        new_object.data.operator_func = obj.data.operator_func;
        break;
    case UNARY_NO_EXPANSION_OPERATION:
        new_object.data.unary_operator_func = obj.data.unary_operator_func;
        break;
    case PATTERN:
        break;
    case HEAD:
        break;
    case TAIL:
        break;
    case FAILED_CONDITION:
        break;
    default: // unknown
        break;
    }

    gc_sweep();
    return new_object;
}

} // panopticon namespace
