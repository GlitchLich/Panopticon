#include "../../include/Grammar/minus.h"
#include "../../include/core/operators.h"
#include "core/Memory.h"

namespace panopticon
{

//================================
//Switches
//================================

bool number_minus(object&A,const object& B,const object& C)
{
    switch(C.type)
    {
    case NUMBER:
        A.type = NUMBER;
        A.data.number = B.data.number - C.data.number;
        break;
    case STRING:
        out() << print_error(SubtractStringFromNum) << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        out() << print_error(SubtractBoolFromNum) << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
        object_operator_array(A,B,C,&number_minus);
        break;
    }
}

bool bool_minus(object&A, const object& B, const object& C)
{
    out() << print_error(SubtractBoolFromNum) << std::endl;
    correct_parsing = false;
}


bool string_minus(object&A, const object& B, const object& C)
{
    switch(C.type)
    {
    case NUMBER:
//        string_minus_string(A,B,convert_to_string(C));
        out() << print_error(SubtractNumFromString) << std::endl;
        correct_parsing = false;
        break;
    case STRING:
        string_minus_string(A,B,C);
        break;
    case BOOL:
        out() << print_error(SubtractBoolFromString) << std::endl;
        correct_parsing = false;
//        string_minus_string(A,B,convert_to_string(C));
        break;
    case ARRAY:
        object_operator_array(A,B,C,&string_minus);
//        string_minus_array(A,C,B);
        break;
    }
}

bool array_minus(object&A, const object& B, const object& C)
{
    switch(C.type)
    {
    case NUMBER:
        array_operator_object(A,B,C,&minus);
//        array_minus_number(A,B,C);
        break;
    case STRING:
         array_operator_object(A,B,C,&minus);
//        array_minus_string(A,B,C);
        break;
    case BOOL:
        out() << print_error(SubtractBoolFromNum) << std::endl;
        correct_parsing = false;
        break;
    case ARRAY:
//        array_minus_array(A,B,C);
//        array_operator_object(A,B,C,&minus);
        array_operator_array(A,B,C,&minus);
        break;
    }
}

//================================
//Combinations
//================================

bool string_minus_string(object &a, const object &b, const object &c)
{
    a = mem_string_alloc(b.data.string->c_str());

    try
    {
        while(true)
        {
            int found = a.data.string->find(*c.data.string);
            if(found !=std::string::npos){
                a.data.string->erase(found,c.data.string->size());
            }
            else
            {
                break;
            }
        }
    }
    catch(std::exception &e)
    {
//        delete b.data.string;
//        delete c.data.string;
        return false;
    }
//    delete b.data.string;
//    delete c.data.string;
    return true;
}

bool number_minus_array(object& a, const object &number, const object &array)
{
    a = mem_alloc(ARRAY);
//    a.data.array->reserve(array.data.array->size());

    for(int i=0;i<array.data.array->size();++i)
    {
        object newObject;
        number_minus(newObject,number,array.data.array->at(i));
        a.data.array->push_back(newObject);
    }

//    delete array.data.array;
}

bool array_minus_number(object& a,object& array, object& number)
{
    a = mem_alloc(ARRAY);
//    a.data.array->reserve(array.data.array->size());

    for(int i=0;i<array.data.array->size();++i)
    {
        object newObject;
        minus(newObject,number,array.data.array->at(i));
        a.data.array->push_back(newObject);
    }

//    delete array.data.array;
}

bool array_minus_string(object& a,object& array, object& string)
{
    a = mem_alloc(ARRAY);
//    a.data.array->reserve(array.data.array->size());

    for(int i=0;i<array.data.array->size();++i)
    {
        object newObject;
        string_minus(newObject,string,array.data.array->at(i));
    }

//    delete array.data.array;
}

bool string_minus_array(object& a, const object &string, const object &array)
{
    a = mem_alloc(ARRAY);
//    a.data.array->reserve(array.data.array->size());

    for(int i=0;i<array.data.array->size();++i)
    {
        object newObject;
        string_minus(newObject,string,array.data.array->at(i));
        a.data.array->push_back(newObject);
    }

//    delete array.data.array;
}

bool array_minus_array(object& a,object& array1, object& array2)
{
    a = mem_alloc(ARRAY);
    int size = 1;

    if(array1.data.array->size()>=array2.data.array->size())
    {
//        a.data.array->reserve(array1.data.array->size());
        size = array1.data.array->size();
    }
    else
    {
//        a.data.array->reserve(array2.data.array->size());
        size = array2.data.array->size();
    }

    for(int i=0;i<size;++i)
    {
        panopticon::object& bb = array1.data.array->at(i%(array1.data.array->size()));
        panopticon::object& cc = array2.data.array->at(i%(array2.data.array->size()));
        object newObject;
        minus(newObject,bb,cc);
        a.data.array->push_back(newObject);
    }

//    delete array1.data.array;
//    delete array2.data.array;
}

}
