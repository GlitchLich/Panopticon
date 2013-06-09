#include "../../include/core/containers.h"
#include "../../include/Grammar/parse.h"
#include "core/Memory.h"
#include "../../include/core/stack.h"
#include "../../include/Grammar/parsingutilities.h"
#include "../../include/core/operators.h"
#include "../../include/core/heap.h"
#include "include/core/operators.h"
#include "core/Trie.h"
#include <math.h>

namespace panopticon
{

object hash_number(const object& number)
{
    object string;
    cast_to_string(string, number);

    object hash;
    hash.type = VARIABLE;
    hash.data.variable_number = get_string_hash(*string.data.string);
    return hash;
}

// READS a hash entry from the global hash map
object get_hash(const object& obj, bool write = false)
{
    std::cout << "get_hash" << std::endl;
    object result;
    result.type = VARIABLE;

    switch(obj.type)
    {
    case VARIABLE:
        return obj;
        break;

    case STRING:
        if(write)
            result.data.variable_number = get_string_hash(*obj.data.string);
        else
            result.data.variable_number = fnv1a(obj.data.string->c_str());
        break;

    case NUMBER:
        return hash_number(obj);
        break;

    default:
        result.data.variable_number = 0;
        break;
    }

    return result;
}

void print_trie_entry(const unsigned int& key, const object& value)
{
    out() << "\"" << reverse_variable_name_lookup[key] << "\" : ";

    switch(value.type)
    {
    case STRING:
        out() << value.data.string->c_str();
        break;

    case NUMBER:
        out() << value.data.number;
        break;

    case BOOL:
        out() << value.data.boolean;
        break;

    case LIST:
        print_list(value, 1);
        break;

    case OPERATION_TREE:
    case ARRAY:
        print_array(value, 1);
        break;

    case DICTIONARY:
        print_dictionary(value);
        break;

    case TRIE:
        print_trie(value);

    case FUNCTION:
        out() << "Function";
        break;

    case NIL:
        out() << "Nil";
        break;

    case VARIABLE:
        out() << reverse_variable_name_lookup[value.data.variable_number];
        break;

    default:
        break;
    }

    out() << " ";
}

bool print_trie(const object& trie, bool endl)
{
    out() << "{ ";

    trie::map(trie.data.trie, print_trie_entry);

    out() << "} ";

    if(endl)
        out() << std::endl;
}

bool trie_lookup(object& value, const object& trie, const object& key)
{
    object hashed_key = get_hash(key);

    if(hashed_key.type != UNDECLARED_VARIABLE && hashed_key.type != VARIABLE)
    {
        out() << "Error: Trie key must be a String." << std::endl;
        correct_parsing = false;
        return false;
    }

    //If the object is a string, attempt to fetch it.
    if(trie.type == UNDECLARED_VARIABLE || trie.type == VARIABLE)
    {
        object result;

        if(get_variable(trie.data.variable_number, &result) == OK)
        {
            if(result.type == TRIE)
            {
                bool success =  trie_lookup(value, result, hashed_key);
                return success;
            }

            else
            {
                value.type = NIL;
                out() << "Error: Cannot call a Trie lookup on a non-Trie object." << std::endl;
                out() << "Object with Trie lookup called on it: " << trie.data.string->c_str() << std::endl;
                correct_parsing = false;
                return false;
            }
        }

        else
        {
            value.type = NIL;
            out() << "Error: the variable \'" << reverse_variable_name_lookup[hashed_key.data.variable_number] << "\'' has not been declared." << std::endl;
            correct_parsing = false;
            return false;
        }

    }

    value = trie::lookup(trie.data.trie, hashed_key.data.variable_number);
    if(value.type != NIL && value.type == OPERATION_TREE)
    {
        optic_stack.push_back(value);
        evaluate_top();
        value = mem_copy(optic_stack.back());
        value = optic_stack.back();
        optic_stack.pop_back();
    }

    else
    {
        value.type = NIL;
        out() << "No object found with key \'" << reverse_variable_name_lookup[hashed_key.data.variable_number] << "\'." << std::endl;
        correct_parsing = false;
        return false;
    }

    return true;
}

bool trie_contains(object& boolean, const object& trie, const object &key)
{
    object hashed_key = get_hash(key);

    if(hashed_key.type != UNDECLARED_VARIABLE && hashed_key.type != VARIABLE)
    {
        out() << "Trie key must be a String." << std::endl;
        correct_parsing = false;
        return false;
    }

    boolean.type = BOOL;
    boolean.data.boolean = trie::contains(trie.data.trie, hashed_key.data.variable_number);
    return true;
}

bool trie_insert(object& trie_A, const object& string_B, const object& object_C)
{
    object hashed_key = get_hash(string_B, true);
    trie_A.data.trie = trie::insert(trie_A.data.trie, hashed_key.data.variable_number, object_C);
    return true;
}

bool trie_remove(object& trie_A, const object& string_B)
{
    object hashed_key = get_hash(string_B);
    trie_A.data.trie = trie::without(trie_A.data.trie, hashed_key.data.variable_number);
}

bool create_trie(object& result_A, const object& B)
{
    result_A = optic::mem_alloc(optic::TRIE);

    for(int i = 0; i < B.data.array->size() - 1; i += 2)
    {
        if(B.data.array->at(i).type != optic::ARRAY)
        {
            object key = B.data.array->at(i);

            if(key.type == NUMBER || key.type == STRING)
                key = get_hash(key);

            result_A.data.trie = trie::insert(result_A.data.trie, key.data.variable_number, mem_copy(B.data.array->at(i+1)));
        }

        else
        {
            optic::object result;
            object arg_copy = mem_copy(B.data.array->at(i));
            object body_copy = mem_copy(B.data.array->at(i+1));
            insure_ready_for_assignment(arg_copy,body_copy);
            optic::store_operations(result, arg_copy,body_copy, create_function);
            optic_stack.push_back(result);
            evaluate_top();

            result_A.data.trie = trie::insert(result_A.data.trie, B.data.array->at(i).data.array->at(0).data.variable_number, mem_copy(optic_stack.back()));
            optic_stack.pop_back();
        }
    }
}

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

        case TRIE:
            print_trie(value);
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
    if(key.type != UNDECLARED_VARIABLE && key.type != VARIABLE)
    {
        out() << "Error: Dictionary key must be a String." << std::endl;
        correct_parsing = false;
        return false;
    }

    //If the object is a string, attempt to fetch it.
    if(dict.type == UNDECLARED_VARIABLE || dict.type == VARIABLE)
    {
        object result;

        if(get_variable(dict.data.variable_number, &result) == OK)
        {
            if(result.type == DICTIONARY)
            {
                bool success =  dictionary_lookup(value, result, key);
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
            out() << "Error: the variable \'" << reverse_variable_name_lookup[key.data.variable_number] << "\'' has not been declared." << std::endl;
            correct_parsing = false;
            return false;
        }

    }

    Dictionary::iterator find = dict.data.dictionary->find(key.data.variable_number);
    if(find != dict.data.dictionary->end())
    {
        //        value = mem_copy(find->second);
        value = find->second;
        if(value.type == OPERATION_TREE)
        {
            optic_stack.push_back(value);
            evaluate_top();
            value = mem_copy(optic_stack.back());
            value = optic_stack.back();
            optic_stack.pop_back();
        }
    }

    else
    {
        value.type = NIL;
        out() << "No object found with key \'" << reverse_variable_name_lookup[key.data.variable_number] << "\'." << std::endl;
        correct_parsing = false;
        return false;
    }

    return true;
}

bool dictionary_contains(object &boolean, const object &dict, const object &key)
{
    if(key.type != UNDECLARED_VARIABLE || key.type != VARIABLE)
    {
        out() << "Dictionary key must be a String." << std::endl;
        correct_parsing = false;
        return false;
    }

    boolean.type = BOOL;
    boolean.data.boolean = dict.data.dictionary->find(key.data.variable_number) != dict.data.dictionary->end();
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
                        string_B.data.variable_number,
                        object_C
                        )
                    );
    }
    else
    {
        out() << "Error:  Cannot insert key: " << reverse_variable_name_lookup[string_B.data.variable_number] << "into dictionary because this key already exists." << std::endl;
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
        if(B.data.array->at(i).type != optic::ARRAY)
        {
            result_A.data.dictionary->insert(
                        std::make_pair(
                            B.data.array->at(i).data.variable_number,
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
                            B.data.array->at(i).data.array->at(0).data.variable_number,
                            mem_copy(optic_stack.back())
                            )
                        );
            optic_stack.pop_back();
            //            mem_free(arg_copy);
        }
    }
    //    optic_stack.push_back(result_A);
    //    optic::shallow_mem_free_array(B.data.array,"ARRAY");
}

bool index(object& A, const object& B, const object& C)
{
    object result;
    switch(B.type)
    {
    case LIST:
        switch(C.type)
        {
        case NUMBER:
            if(C.data.number<B.data.array->size())
            {
                //                A = mem_copy(B.data.array->at(C.data.number));
//                A = B.data.array->at(C.data.number);
//                optic_stack.push_back(A);
//                evaluate_top();
//                A = optic_stack.back();
//                optic_stack.pop_back();
                A = two_three_lookup(B.data.list,C.data.number);
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
            get_variable(C.data.variable_number,&result);
            //            index(A,B,mem_copy(result));
            index(A,B,result);
            break;
        case OPERATION_TREE:
            optic_stack.push_back(C);
            evaluate_top();
            //            result = mem_copy(optic_stack.back());
            result = optic_stack.back();
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
        if(get_variable(B.data.variable_number, &result) == OK)
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

bool slice(object&A, const object& B, const object& C)
{
    //Error Guards
    if(B.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(B.data.variable_number,&result)==OK)
        {
            return slice(result,B,C);
        }
        else
        {
            out() << "Error: Could not find array with name: " << *B.data.string << std::endl;
            correct_parsing = false;
            return false;
        }
    }
    if(B.type!=ARRAY)
    {
        out() << "Error: Cannot slice a non-Array." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=ARRAY)
    {
        out() << "Error: Malformed Array slicing." << std::endl;
        correct_parsing = false;
        return false;
    }
    int begin,end;
    const object& index1 = C.data.array->at(0);
    const object& index2 = C.data.array->at(1);
    if(index1.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index1));
        optic_stack.push_back(index1);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            begin = optic_stack.back().data.number;

            optic_stack.pop_back();
        }
    }
    else if(index1.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index1.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                begin = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index1.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(0).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        begin = index1.data.number;
    }

    //Slice Index 2
    if(index2.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index2));
        optic_stack.push_back(index2);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number two is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            end = optic_stack.back().data.number;
            optic_stack.pop_back();
        }
    }
    else if(index2.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index2.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                end = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index2.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(1).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        end = index2.data.number;
    }
    if(begin>end)
    {
        out() << "Error: Number on left-hand side of Array slice is larger than the number on the right-hand side, which is illegal with out specifying a negative slice step-size." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(begin<0)
    {
        begin = 0;
    }
    if(end<0)
    {
        end = 0;
    }
    if(begin>B.data.array->size())
    {
        begin = B.data.array->size();
    }
    if(end>B.data.array->size())
    {
        end = B.data.array->size();
    }
    A = mem_alloc(ARRAY);
    A.data.array->resize(end - begin);
    std::copy(B.data.array->begin()+begin,B.data.array->begin()+end,A.data.array->begin());
}

bool slice_beginning_to(object&A, const object& B, const object& C)
{
    if(B.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(B.data.variable_number,&result)==OK)
        {
            return slice_beginning_to(result,B,C);
        }
        else
        {
            out() << "Error: Could not find array with name: " << *B.data.string << std::endl;
            correct_parsing = false;
            return false;
        }
    }
    //Error Guards
    if(B.type!=ARRAY)
    {
        out() << "Error: Cannot slice a non-Array." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number." << std::endl;
        correct_parsing = false;
        return false;
    }
    int num = C.data.number;
    if(num<0)
    {
        num = 0;
    }
    if(num>B.data.array->size())
    {
        num = B.data.array->size();
    }
    A = mem_alloc(ARRAY);
    A.data.array->resize(num);
    std::copy(B.data.array->begin(),B.data.array->begin()+num,A.data.array->begin());
}

bool slice_to_end(object&A, const object& B, const object& C)
{
    if(B.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(B.data.variable_number,&result)==OK)
        {
            return slice_to_end(result,B,C);
        }
        else
        {
            out() << "Error: Could not find array with name: " << *B.data.string << std::endl;
            correct_parsing = false;
            return false;
        }
    }
    if(B.type!=ARRAY)
    {
        out() << "Error: Cannot slice a non-Array." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number." << std::endl;
        correct_parsing = false;
        return false;
    }
    int num = C.data.number;
    if(num<0)
    {
        num = 0;
    }
    if(num>B.data.array->size())
    {
        num = B.data.array->size();
    }

    A = mem_alloc(ARRAY);
    A.data.array->resize(B.data.array->size()-num);
    std::copy(B.data.array->begin()+num,B.data.array->end(),A.data.array->begin());
}

bool slice_all_with_step(object&A, const object& B, const object& C)
{
    if(B.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(B.data.variable_number,&result)==OK)
        {
            return slice_all_with_step(result,B,C);
        }
        else
        {
            out() << "Error: Could not find array with name: " << *B.data.string << std::endl;
            correct_parsing = false;
            return false;
        }
    }
    //Error Guards
    if(B.type!=ARRAY)
    {
        out() << "Error: Cannot slice a non-Array." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number for a step-size." << std::endl;
        correct_parsing = false;
        return false;
    }
    int num = C.data.number;
    if(num<0)
    {
        num = 0;
    }
    if(num>B.data.array->size())
    {
        num = B.data.array->size();
    }
    A = mem_alloc(ARRAY);
    for(int i=0;i<B.data.array->size();i+=num)
    {
        A.data.array->push_back(mem_copy(B.data.array->at(i)));
    }
}

bool slice_beginning_to_with_step(object&A, const object& B, const object& C)
{
    //Error Guards
    if(B.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(B.data.variable_number,&result)==OK)
        {
            return slice_beginning_to_with_step(result,B,C);
        }
        else
        {
            out() << "Error: Could not find array with name: " << *B.data.string << std::endl;
            correct_parsing = false;
            return false;
        }
    }
    if(B.type!=ARRAY)
    {
        out() << "Error: Cannot slice a non-Array." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=ARRAY)
    {
        out() << "Error: Malformed Array slicing." << std::endl;
        correct_parsing = false;
        return false;
    }
    int begin,end;
    const object& index1 = C.data.array->at(0);
    const object& index2 = C.data.array->at(1);
    if(index1.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index1));
        optic_stack.push_back(index1);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            begin = optic_stack.back().data.number;

            optic_stack.pop_back();
        }
    }
    else if(index1.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index1.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                begin = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index1.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(0).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        begin = index1.data.number;
    }

    //Slice Index 2
    if(index2.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index2));
        optic_stack.push_back(index2);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number two is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            end = optic_stack.back().data.number;
            optic_stack.pop_back();
        }
    }
    else if(index2.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index2.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                end = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index2.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(1).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        end = index2.data.number;
    }
    if(begin<0)
    {
        begin = 0;
    }
    if(end == 0)
    {
        out() << "Error: Cannot have a step-size of zero." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(begin>B.data.array->size())
    {
        begin = B.data.array->size();
    }
    A = mem_alloc(ARRAY);

    for(int i=begin;i<B.data.array->size();i+=end)
    {
        A.data.array->push_back(mem_copy(B.data.array->at(i)));
    }
}

bool slice_to_end_with_step(object&A, const object& B, const object& C)
{
    //Error Guards
    if(B.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(B.data.variable_number,&result)==OK)
        {
            return slice_to_end_with_step(result,B,C);
        }
        else
        {
            out() << "Error: Could not find array with name: " << *B.data.string << std::endl;
            correct_parsing = false;
            return false;
        }
    }
    if(B.type!=ARRAY)
    {
        out() << "Error: Cannot slice a non-Array." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=ARRAY)
    {
        out() << "Error: Malformed Array slicing." << std::endl;
        correct_parsing = false;
        return false;
    }
    int begin,end;
    const object& index1 = C.data.array->at(0);
    const object& index2 = C.data.array->at(1);
    if(index1.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index1));
        optic_stack.push_back(index1);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            begin = optic_stack.back().data.number;

            optic_stack.pop_back();
        }
    }
    else if(index1.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index1.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                begin = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index1.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(0).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        begin = index1.data.number;
    }

    //Slice Index 2
    if(index2.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index2));
        optic_stack.push_back(index2);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number two is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            end = optic_stack.back().data.number;
            optic_stack.pop_back();
        }
    }
    else if(index2.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index2.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                end = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index2.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(1).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        end = index2.data.number;
    }
    if(begin<0)
    {
        begin = 0;
    }
    if(end == 0)
    {
        out() << "Error: Cannot have a step-size of zero." << std::endl;
        correct_parsing = false;
        return false;
    }
    else if(end < 0 )
    {
        out() << "Error: Cannot have a negative slice step-size that goes below the zero index unless you allow wrapping. (i.e. myArray[:2:(-4):%] )" << std::endl;
        correct_parsing = false;
        return false;
    }
    if(begin>B.data.array->size())
    {
        begin = B.data.array->size();
    }
    A = mem_alloc(ARRAY);

    for(int i=0;i<begin;i+=end)
    {
        A.data.array->push_back(mem_copy(B.data.array->at(i)));
    }
}

bool slice_with_step(object&A, const object& B, const object& C)
{
    //Error Guards
    if(B.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(B.data.variable_number,&result)==OK)
        {
            return slice_with_step(result,B,C);
        }
        else
        {
            out() << "Error: Could not find array with name: " << *B.data.string << std::endl;
            correct_parsing = false;
            return false;
        }
    }
    if(B.type!=ARRAY)
    {
        out() << "Error: Cannot slice a non-Array." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=ARRAY)
    {
        out() << "Error: Malformed Array slicing." << std::endl;
        correct_parsing = false;
        return false;
    }
    int begin,end,step;
    const object& index1 = C.data.array->at(0);
    const object& index2 = C.data.array->at(1);
    const object& index3 = C.data.array->at(2);
    if(index1.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index1));
        optic_stack.push_back(index1);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            begin = optic_stack.back().data.number;

            optic_stack.pop_back();
        }
    }
    else if(index1.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index1.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                begin = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index1.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(0).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        begin = index1.data.number;
    }

    //Slice Index 2
    if(index2.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index2));
        optic_stack.push_back(index2);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number two is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            end = optic_stack.back().data.number;
            optic_stack.pop_back();
        }
    }
    else if(index2.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index2.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                end = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index2.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(1).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        end = index2.data.number;
    }

    //Slice Index 2
    if(index3.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index3));
        optic_stack.push_back(index3);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number two is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            step = optic_stack.back().data.number;
            optic_stack.pop_back();
        }
    }
    else if(index3.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index3.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                step = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index3.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(2).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        step = index3.data.number;
    }
    if(step == 0)
    {
        out() << "Error: Cannot have a step-size of zero." << std::endl;
        correct_parsing = false;
        return false;
    }
    else if(step>0)
    {
        if(begin>end)
        {
            out() << "Error: Number on left-hand side of Array slice is larger than the number on the right-hand side, which is illegal with out specifying a negative slice step-size." << std::endl;
            correct_parsing = false;
            return false;
        }
    }
    else
    {
        if(end>begin)
        {
            out() << "Error: Number on Right-hand side of Array slice is larger than the number on the left-hand side, which is illegal while specifying a negative slice step-size." << std::endl;
            correct_parsing = false;
            return false;
        }
    }

    if(begin<0)
    {
        begin = 0;
    }
    if(end<0)
    {
        end = 0;
    }
    if(begin>B.data.array->size())
    {
        begin = B.data.array->size();
    }
    if(end>B.data.array->size())
    {
        end = B.data.array->size();
    }
    A = mem_alloc(ARRAY);
    if(step>0)
    {
        for(int i=begin;i<end;i+=step)
        {
            A.data.array->push_back(mem_copy(B.data.array->at(i)));
        }
    }
    else if(step < 0)
    {
        for(int i=begin;i>end;i+=step)
        {
            A.data.array->push_back(mem_copy(B.data.array->at(i)));
        }
    }
}

//WRAPPING
bool slice_beginning_to_wrapping(object&A, const object& B, const object& C)
{
    if(B.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(B.data.variable_number,&result)==OK)
        {
            return slice_beginning_to(result,B,C);
        }
        else
        {
            out() << "Error: Could not find array with name: " << *B.data.string << std::endl;
            correct_parsing = false;
            return false;
        }
    }

    //Error Guards
    if(B.type!=ARRAY)
    {
        out() << "Error: Cannot slice a non-Array." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number." << std::endl;
        correct_parsing = false;
        return false;
    }

    int num = C.data.number;
    A = mem_alloc(ARRAY);
    int size = B.data.array->size();
    int end  = size - num;

    for(int i=num;i<num + size;i++)
    {
        if(i>=0)
        {
            A.data.array->push_back(mem_copy(B.data.array->at(i%size)));
        }
        else
        {
            int index = i%size;
            index = size + index;
            A.data.array->push_back(mem_copy(B.data.array->at(index%size)));
        }
    }
}

bool slice_to_end_wrapping(object&A, const object& B, const object& C)
{
    if(B.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(B.data.variable_number,&result)==OK)
        {
            return slice_to_end(result,B,C);
        }
        else
        {
            out() << "Error: Could not find array with name: " << *B.data.string << std::endl;
            correct_parsing = false;
            return false;
        }
    }

    if(B.type!=ARRAY)
    {
        out() << "Error: Cannot slice a non-Array." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number." << std::endl;
        correct_parsing = false;
        return false;
    }

    int num = C.data.number;
    A = mem_alloc(ARRAY);
    int size = B.data.array->size();
    int end  = size - num;

    for(int i=0;i<num;i++)
    {
        if(i>=0)
        {
            A.data.array->push_back(mem_copy(B.data.array->at(i%size)));
        }
        else
        {
            int index = i%size;
            index = size + index;
            A.data.array->push_back(mem_copy(B.data.array->at(index%size)));
        }
    }
}

//SLICE WITH WRAPPING
bool slice_with_wrapping(object&A, const object& B, const object& C)
{
    //Error Guards
    if(B.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(B.data.variable_number,&result)==OK)
        {
            return slice(result,B,C);
        }
        else
        {
            out() << "Error: Could not find array with name: " << *B.data.string << std::endl;
            correct_parsing = false;
            return false;
        }
    }
    if(B.type!=ARRAY)
    {
        out() << "Error: Cannot slice a non-Array." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=ARRAY)
    {
        out() << "Error: Malformed Array slicing." << std::endl;
        correct_parsing = false;
        return false;
    }
    int begin,end;
    const object& index1 = C.data.array->at(0);
    const object& index2 = C.data.array->at(1);
    if(index1.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index1));
        optic_stack.push_back(index1);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            begin = optic_stack.back().data.number;

            optic_stack.pop_back();
        }
    }
    else if(index1.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index1.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                begin = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index1.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(0).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        begin = index1.data.number;
    }

    //Slice Index 2
    if(index2.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index2));
        optic_stack.push_back(index2);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number two is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            end = optic_stack.back().data.number;
            optic_stack.pop_back();
        }
    }
    else if(index2.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index2.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                end = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index2.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(1).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        end = index2.data.number;
    }
    if(begin>end)
    {
        out() << "Error: Number on left-hand side of Array slice is larger than the number on the right-hand side, which is illegal with out specifying a negative slice step-size." << std::endl;
        correct_parsing = false;
        return false;
    }

    A = mem_alloc(ARRAY);

    int size = B.data.array->size();

    for(int i=begin;i<end;i++)
    {
        if(i>=0)
        {
            A.data.array->push_back(mem_copy(B.data.array->at(i%size)));
        }
        else
        {
            int index = i%size;
            index = size + index;
            A.data.array->push_back(mem_copy(B.data.array->at(index%size)));
        }
    }
}

bool slice_beginning_to_with_step_wrapping(object&A, const object& B, const object& C)
{
    //Error Guards
    if(B.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(B.data.variable_number,&result)==OK)
        {
            return slice_beginning_to_with_step(result,B,C);
        }
        else
        {
            out() << "Error: Could not find array with name: " << *B.data.string << std::endl;
            correct_parsing = false;
            return false;
        }
    }
    if(B.type!=ARRAY)
    {
        out() << "Error: Cannot slice a non-Array." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=ARRAY)
    {
        out() << "Error: Malformed Array slicing." << std::endl;
        correct_parsing = false;
        return false;
    }
    int begin,end;
    const object& index1 = C.data.array->at(0);
    const object& index2 = C.data.array->at(1);
    if(index1.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index1));
        optic_stack.push_back(index1);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            begin = optic_stack.back().data.number;

            optic_stack.pop_back();
        }
    }
    else if(index1.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index1.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                begin = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index1.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(0).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        begin = index1.data.number;
    }

    //Slice Index 2
    if(index2.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index2));
        optic_stack.push_back(index2);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number two is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            end = optic_stack.back().data.number;
            optic_stack.pop_back();
        }
    }
    else if(index2.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index2.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                end = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index2.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(1).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        end = index2.data.number;
    }

    A = mem_alloc(ARRAY);

    int size = B.data.array->size();

    if(end>0)
    {

        for(int i=begin;i<begin+size;i+=end)
        {
            if(i>=0)
            {
                A.data.array->push_back(mem_copy(B.data.array->at(i%size)));
            }
            else
            {
                int index = i%size;
                index = size + index;
                A.data.array->push_back(mem_copy(B.data.array->at(index%size)));
            }
        }
    }
    else
    {
        for(int i=begin;i>begin+(-1 * size);i+=end)
        {
            //            std::cout << i << std::endl;
            if(i>=0)
            {
                A.data.array->push_back(mem_copy(B.data.array->at(i%size)));
            }
            else
            {
                int index = i%size;
                index = size + index;
                A.data.array->push_back(mem_copy(B.data.array->at(index%size)));
            }
        }
    }
}

bool slice_to_end_with_step_wrapping(object&A, const object& B, const object& C)
{
    //Error Guards
    if(B.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(B.data.variable_number,&result)==OK)
        {
            return slice_to_end_with_step(result,B,C);
        }
        else
        {
            out() << "Error: Could not find array with name: " << *B.data.string << std::endl;
            correct_parsing = false;
            return false;
        }
    }
    if(B.type!=ARRAY)
    {
        out() << "Error: Cannot slice a non-Array." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=ARRAY)
    {
        out() << "Error: Malformed Array slicing." << std::endl;
        correct_parsing = false;
        return false;
    }
    int begin,end;
    const object& index1 = C.data.array->at(0);
    const object& index2 = C.data.array->at(1);
    if(index1.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index1));
        optic_stack.push_back(index1);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            begin = optic_stack.back().data.number;

            optic_stack.pop_back();
        }
    }
    else if(index1.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index1.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                begin = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index1.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(0).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        begin = index1.data.number;
    }

    //Slice Index 2
    if(index2.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index2));
        optic_stack.push_back(index2);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number two is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            end = optic_stack.back().data.number;
            optic_stack.pop_back();
        }
    }
    else if(index2.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index2.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                end = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index2.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(1).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        end = index2.data.number;
    }
    if(begin<0)
    {
        begin = 0;
    }
    if(end == 0)
    {
        out() << "Error: Cannot have a step-size of zero." << std::endl;
        correct_parsing = false;
        return false;
    }
    else if(end < 0 )
    {
        out() << "Error: Cannot have a negative slice step-size that goes below the zero index unless you allow wrapping. (i.e. myArray[:2:(-4):%] )" << std::endl;
        correct_parsing = false;
        return false;
    }

    A = mem_alloc(ARRAY);

    int size = B.data.array->size();

    for(int i=0;i<begin;i+=end)
    {

        A.data.array->push_back(mem_copy(B.data.array->at(i%size)));
    }
}

bool slice_with_step_wrapping(object&A, const object& B, const object& C)
{
    //Error Guards
    if(B.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(B.data.variable_number,&result)==OK)
        {
            return slice_with_step(result,B,C);
        }
        else
        {
            out() << "Error: Could not find array with name: " << *B.data.string << std::endl;
            correct_parsing = false;
            return false;
        }
    }
    if(B.type!=ARRAY)
    {
        out() << "Error: Cannot slice a non-Array." << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=ARRAY)
    {
        out() << "Error: Malformed Array slicing." << std::endl;
        correct_parsing = false;
        return false;
    }
    int begin,end,step;
    const object& index1 = C.data.array->at(0);
    const object& index2 = C.data.array->at(1);
    const object& index3 = C.data.array->at(2);
    if(index1.type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(index1));
        optic_stack.push_back(index1);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            begin = optic_stack.back().data.number;

            optic_stack.pop_back();
        }
    }
    else if(index1.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index1.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                begin = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index1.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(0).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        begin = index1.data.number;
    }

    //Slice Index 2
    if(index2.type==OPERATION_TREE)
    {
        optic_stack.push_back(index2);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number two is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            end = optic_stack.back().data.number;
            optic_stack.pop_back();
        }
    }
    else if(index2.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index2.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                end = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index2.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(1).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        end = index2.data.number;
    }

    //Slice Index 2
    if(index3.type==OPERATION_TREE)
    {
        optic_stack.push_back(index3);
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot slice an array with a non-Number. Object in slice index number two is of type: "<< type_string(optic_stack.back().type) << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            step = optic_stack.back().data.number;
            optic_stack.pop_back();
        }
    }
    else if(index3.type == UNDECLARED_VARIABLE)
    {
        object result;
        if(get_variable(index3.data.variable_number,&result)==OK)
        {
            if(result.type!=NUMBER)
            {
                out() << "Error: Cannot slice an array with a non-Number. Object in slice index number one is of type: "<< type_string(result.type) << std::endl;
                correct_parsing = false;
                optic_stack.pop_back();
                return false;
            }
            else
            {
                step = result.data.number;
            }
        }
        else
        {
            correct_parsing = false;
            return false;
        }
    }
    else if(index3.type!=NUMBER)
    {
        out() << "Error: Cannot slice an array with a non-Number. Slice type: "<< type_string(C.data.array->at(2).type) << std::endl;
        correct_parsing = false;
        return false;
    }
    else
    {
        step = index3.data.number;
    }
    if(step == 0)
    {
        out() << "Error: Cannot have a step-size of zero." << std::endl;
        correct_parsing = false;
        return false;
    }
    else if(step>0)
    {
        if(begin>end)
        {
            out() << "Error: Number on left-hand side of Array slice is larger than the number on the right-hand side, which is illegal with out specifying a negative slice step-size." << std::endl;
            correct_parsing = false;
            return false;
        }
    }
    else
    {
        if(end>begin)
        {
            out() << "Error: Number on Right-hand side of Array slice is larger than the number on the left-hand side, which is illegal while specifying a negative slice step-size." << std::endl;
            correct_parsing = false;
            return false;
        }
    }

    int size = B.data.array->size();

    A = mem_alloc(ARRAY);
    if(step>0)
    {
        for(int i=begin;i<end;i+=step)
        {
            if(i>=0)
            {
                A.data.array->push_back(mem_copy(B.data.array->at(i%size)));
            }
            else
            {
                int index = i%size;
                index = size + index;
                A.data.array->push_back(mem_copy(B.data.array->at(index%size)));
            }
        }
    }
    else if(step < 0)
    {
        for(int i=begin;i>end;i+=step)
        {
            if(i>=0)
            {
                A.data.array->push_back(mem_copy(B.data.array->at(i%size)));
            }
            else
            {
                int index = i%size;
                index = size + index;
                A.data.array->push_back(mem_copy(B.data.array->at(index%size)));
            }
        }
    }
}

//=======================
//Array ranges
//=======================

//Default step-size of 1
bool range_from_to(object&A, const object& B, const object& C)
{
    A = mem_alloc(ARRAY);

    if(B.type!=NUMBER)
    {
        out() << "Error: Cannot have a non-Number type in an Array-range specifier" << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=NUMBER)
    {
        out() << "Error: Cannot have a non-Number type in an Array-range specifier" << std::endl;
        correct_parsing = false;
        return false;
    }

    int start = B.data.number;
    int end = C.data.number;

    if(start>end)
    {
        out() << "Error: This range is impossible: Start is larger than end, and you have a positive step-size of 1" << std::endl;
        correct_parsing = false;
        return false;
    }

    while(start<=end)
    {
        object num = mem_alloc(NUMBER);
        num.data.number = start;
        A.data.array->push_back(num);
        start++;
    }
}

bool range_from_step_to(object&A, const object& B, const object& C)
{
    A = mem_alloc(ARRAY);
    out() << type_string(B.data.array->at(0).type) << std::endl;
    if(B.type!=ARRAY)
    {
        out() << "Error: Malformed Array specificer." << std::endl;
        correct_parsing = false;
        return false;
    }
    double start,step,end;

    //start
    if(B.data.array->at(0).type==OPERATION_TREE)
    {
        //        optic_stack.push_back(mem_copy(B.data.array->at(0)));
        optic_stack.push_back(B.data.array->at(0));
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot have a non-Number type in an Array-range specifier" << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            start = optic_stack.back().data.number;
            optic_stack.pop_back();
        }
    }
    else if(B.data.array->at(0).type!=NUMBER)
    {
        out() << "Error: Cannot have a non-Number type in an Array-range specifier" << std::endl;
        correct_parsing = false;
        return false;
    }

    //step
    if(B.data.array->at(1).type==OPERATION_TREE)
    {
        optic_stack.push_back(B.data.array->at(1));
        evaluate_top();

        if(optic_stack.back().type!=NUMBER)
        {
            out() << "Error: Cannot have a non-Number type in an Array-range specifier" << std::endl;
            correct_parsing = false;
            optic_stack.pop_back();
            return false;
        }
        else
        {
            step = optic_stack.back().data.number;
            optic_stack.pop_back();
        }
    }
    else if(B.data.array->at(1).type!=NUMBER)
    {
        out() << "Error: Cannot have a non-Number type in an Array-range specifier" << std::endl;
        correct_parsing = false;
        return false;
    }
    if(C.type!=NUMBER)
    {
        out() << "Error: Cannot have a non-Number type in an Array-range specifier" << std::endl;
        correct_parsing = false;
        return false;
    }
    end = C.data.number;

    step = step - start;

    if(step == 0)
    {
        out() << "Error: Cannot have an Array-range step size of zero." << std::endl;
        correct_parsing = false;
        return false;
    }
    else if(start>end && step > 0)
    {
        out() << "Error: This range is impossible: Start is larger than end, and you have a positive step-size of: " <<step << "." << std::endl;
        correct_parsing = false;
        return false;
    }
    else if(end>start && step < 0)
    {
        out() << "Error: This range is impossible: End is larger than start, and you have a negative step-size of: " <<step << "." << std::endl;
        correct_parsing = false;
        return false;
    }

    if(step>0)
    {
        while(start<=end)
        {
            object num = mem_alloc(NUMBER);
            num.data.number = start;
            A.data.array->push_back(num);
            start+=step;
        }
    }
    else
    {
        while(start>=end)
        {
            object num = mem_alloc(NUMBER);
            num.data.number = start;
            A.data.array->push_back(num);
            start+=step;
        }
    }
}

}
