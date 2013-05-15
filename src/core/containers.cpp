#include "../../include/core/containers.h"
#include "../../include/Grammar/parse.h"
#include "core/Memory.h"
#include "../../include/core/stack.h"
#include "../../include/Grammar/parsingutilities.h"
#include "../../include/core/operators.h"
#include "../../include/core/heap.h"

namespace panopticon
{

bool print_dictionary(const object& dict)
{
    Dictionary::iterator iter = dict.data.dictionary->begin();

    out() << "{ " << std::endl;

    while(iter != dict.data.dictionary->end())
    {
        out() << "\"" << iter->first << "\" : ";

        panopticon::object& value = iter->second;

        switch(value.type)
        {
        case STRING:
            out() << value.data.string;
            break;

        case NUMBER:
            out() << value.data.number;
            break;

        case BOOL:
            out() << value.data.boolean;
            break;

        case OPERATION_TREE:
        case ARRAY:
            print_array(value);
            break;

        case DICTIONARY:
            print_dictionary(value);
            break;

        case FUNCTION:
            out() << "Function";
            break;

        case NIL:
            out() << "Nil";
            break;

        default:
            break;
        }

        out() << " ";

        ++iter;
    }

    out() << "}" << std::endl;
    return true;
}

bool dictionary_lookup(object& value, const object& dict, const object& key)
{
    if(key.type != STRING)
    {
        out() << "Error: Dictionary key must be a String." << std::endl;
        correct_parsing = false;
        return false;
    }

    //If the object is a string, attempt to fetch it.
    if(dict.type == STRING || dict.type == UNDECLARED_VARIABLE)
    {
        object result;

        if(get_variable(dict.data.string, &result) == OK)
        {
            if(result.type == DICTIONARY)
            {
                bool success =  dictionary_lookup(value, result, key);
                mem_free(result);
                return success;
            }

            else
            {
                value.type = NIL;
                out() << "Error: Cannot call a Dictionary lookup on a non-Dictionary object." << std::endl;
                out() << "Object with Dictionary lookup called on it: " << dict.data.string->c_str() << std::endl;
                correct_parsing = false;
                return false;
            }
        }

        else
        {
            value.type = NIL;
            out() << "Error: the variable \'" << dict.data.string->c_str() << "\'' has not been declared." << std::endl;
            correct_parsing = false;
            return false;
        }

    }

    Dictionary::iterator find = dict.data.dictionary->find(*key.data.string);
    if(find != dict.data.dictionary->end())
    {
        value = mem_copy(find->second);
    }

    else
    {
        value.type = NIL;
        out() << "No object found with key \'" << *key.data.string << "\'." << std::endl;
        correct_parsing = false;
        return false;
    }

    return true;
}

bool dictionary_contains(object &boolean, const object &dict, const object &key)
{
    if(key.type != STRING)
    {
        out() << "Dictionary key must be a String." << std::endl;
        correct_parsing = false;
        return false;
    }

    boolean.type = BOOL;
    boolean.data.boolean = dict.data.dictionary->find(*key.data.string) != dict.data.dictionary->end();
    return true;
}

bool dictionary_insert(object& dictionary_A,const object& string_B, const object& object_C)
{
    object boolean;
    dictionary_contains(boolean,dictionary_A,string_B);
    if(!boolean.data.boolean)
    {
        dictionary_A.data.dictionary->insert(
                    std::make_pair(
                        *string_B.data.string,
                        object_C
                        )
                    );
    }
    else
    {
        out() << "Error:  Cannot insert key: " << *string_B.data.string << "into dictionary because this key already exists." << std::endl;
        correct_parsing = false;
        return false;
    }
}


bool create_dictionary(object& result_A, const object& B)
{
//    std::cout << "CREATING A DICTIONARY!!!!!!!!!!!!!!!!!!!" << std::endl;
    result_A = optic::mem_alloc(optic::DICTIONARY);
    for(int i=0;i<B.data.array->size()-1;i+=2)
    {
        if(
                B.data.array->at(i).type != optic::ARRAY
                )
        {
            result_A.data.dictionary->insert(
                        std::make_pair(
                            std::string(*B.data.array->at(i).data.string),
                            mem_copy(B.data.array->at(i+1))
                            )
                        );
//            optic::mem_free(B.data.array->at(i));
        }
        else
        {
            optic::object result;
            object arg_copy = mem_copy(B.data.array->at(i));
            object body_copy = mem_copy(B.data.array->at(i+1));
            insure_ready_for_assignment(arg_copy,body_copy);
            optic::store_operations(result,arg_copy,body_copy,create_function);
            optic_stack.push_back(result);
            evaluate_top();
            result_A.data.dictionary->insert(
                        std::make_pair(
                            std::string(*B.data.array->at(i).data.array->at(0).data.string),
                            mem_copy(optic_stack.back())
                            )
                        );
//            optic_stack.pop_back();
//            mem_free(arg_copy);
        }
    }
    optic_stack.push_back(result_A);
    //    optic::shallow_mem_free_array(B.data.array,"ARRAY");
}

bool prepend(object& result_A, const object& B, const object& container_C)
{
    if(container_C.type != ARRAY)
    {
        result_A = mem_alloc(ARRAY);
        result_A.data.array->push_front(mem_copy(container_C));
        result_A.data.array->push_front(mem_copy(B));
        return true;
    }

    // container_C.data.array->push_front(B);
    result_A = mem_copy(container_C);
    result_A.data.array->push_front(mem_copy(B));
    return true;
}

bool append(object& result_A, const object& container_B, const object& object_C)
{
    if(container_B.type != ARRAY)
    {
        result_A = mem_alloc(ARRAY);
        result_A.data.array->push_back(mem_copy(container_B));
        result_A.data.array->push_back(mem_copy(object_C));
        return true;
    }

    // container_B.data.array->push_back(object_C);
    result_A = mem_copy(container_B);
    result_A.data.array->push_back(mem_copy(object_C));
    return true;
}

bool concat(object& A, const object& B, const object& C)
{
    std::stringstream ss;
    switch(B.type)
    {
    case BOOL:
        switch(C.type)
        {
        case BOOL:
        case NUMBER:
            A = mem_alloc(ARRAY);
            A.data.array->push_back(mem_copy(B));
            A.data.array->push_back(mem_copy(C));
            break;
        case STRING:
            A = mem_alloc(STRING);

            if(B.data.boolean)
            {
                A.data.string->append("true");
            }

            else
            {
                A.data.string->append("false");
            }

            A.data.string->append(*C.data.string);
            break;
        case ARRAY:
            A = mem_copy(C);
            A.data.array->push_front(mem_copy(B));
            break;
        }
        break;
        break;
    case NUMBER:
        switch(C.type)
        {
        case BOOL:
        case NUMBER:
            A = mem_alloc(ARRAY);
            A.data.array->push_back(mem_copy(B));
            A.data.array->push_back(mem_copy(C));
            break;
        case STRING:
            A = mem_alloc(STRING);
            ss << B.data.number;
            A.data.string->append(ss.str());
            A.data.string->append(*C.data.string);
            break;
        case ARRAY:
            A = mem_copy(C);
            A.data.array->push_front(mem_copy(B));
            break;
        }
        break;
    case STRING:
        switch(C.type)
        {
        case BOOL:
            A = mem_copy(B);
            if(B.data.boolean)
            {
                A.data.string->append("true");
            }
            else
            {
                A.data.string->append("false");
            }
            break;
        case NUMBER:
            A = mem_copy(B);
            ss << C.data.number;
            A.data.string->append(ss.str());
            break;
        case STRING:
            A = mem_copy(B);
            A.data.string->append(*C.data.string);
            break;
        case ARRAY:
            A = mem_copy(C);
            A.data.array->push_front(mem_copy(B));
            break;
        }
        break;
    case ARRAY:
        A = mem_copy(B);
        switch(C.type)
        {
        case NUMBER:
            A.data.array->push_back(mem_copy(C));
            break;
        case STRING:
            A.data.array->push_back(mem_copy(C));
            break;
        case BOOL:
            A.data.array->push_back(mem_copy(C));
            break;
        case ARRAY:
            for(int i=0;i<C.data.array->size();++i)
            {
                A.data.array->push_back(mem_copy(C.data.array->at(i)));
            }
            break;
        }
        break;
    }
}

bool index(object& A, const object& B, const object& C)
{
    object result;
    switch(B.type)
    {
    case ARRAY:
        switch(C.type)
        {
        case NUMBER:
            if(C.data.number<B.data.array->size())
            {
                A = mem_copy(B.data.array->at(C.data.number));
                optic_stack.push_back(A);
                evaluate_top();
                A = optic_stack.back();
                optic_stack.pop_back();
            }
            else
            {
                out() << "Error: Index out of range." << std::endl;
                correct_parsing = false;
            }
            break;
        case STRING:
            out() << "Syntax error: A string cannot be an array index." << std::endl;
            correct_parsing = false;
            break;
        case BOOL:
            out() << "Syntax error: A bool cannot be an array index." << std::endl;
            correct_parsing = false;
            break;
        case ARRAY:
            if(C.data.array->size() > 0)
            {
                index(A,B,C.data.array->at(0));
            }
            else
            {
                out() << "Error: Attempting to index with an array of size zero." << std::endl;
                correct_parsing = false;
            }
            break;
        case UNDECLARED_VARIABLE:
            get_variable(C.data.string,&result);
            index(A,B,mem_copy(result));
            break;
        case OPERATION_TREE:
            optic_stack.push_back(C);
            evaluate_top();
            result = mem_copy(optic_stack.back());
            optic_stack.pop_back();
            index(A,B,result);
            break;
        default:
            out() << "Syntax error: cannot use a non-numeral for an array index." << std::endl;
            out() << "Object used as index: ";
            print_object(C);
            correct_parsing = false;
            break;
        }
        break;
    case STRING:
        if(get_variable(B.data.string, &result) == OK)
        {
            if(result.type != FUNCTION)
            {
                index(A,result,C);
            }

            else
            {
                call_function(result,B,create_void_tree());
                index(A,result,C);
            }

            break;
        }
        out() << "Syntax error: Attempting to index an undeclared variable." << std::endl;
        out() << "Variable with index called on it: ";
        print_object(B);
        correct_parsing = false;
        break;
    default:
        out() << "Syntax error: cannot retrieve an index from a non-array data type." << std::endl;
        out() << "Object with index called on it: ";
        print_object(B);
        correct_parsing = false;
        break;
    }
}

}
