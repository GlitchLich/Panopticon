#include "../../include/Grammar/plus.h"
#include "../../include/core/operators.h"
#include "core/Memory.h"
#include <iostream>

namespace panopticon
{

//================================
//Switches
//================================

bool number_plus(object&A,const object& B,const object& C)
{
    switch(C.type)
    {
    case NUMBER:
        A.type = NUMBER;
        A.data.number = B.data.number + C.data.number;
        break;
    case STRING:
        num_plus_string(A,B,C);
        break;
    case BOOL:
        number_plus_bool(A,B,C);
        break;
    }
}

bool bool_plus(object&A,const object& B,const object& C)
{
    switch(C.type)
    {
    case NUMBER:
        number_plus_bool(A,C,B);
        break;
    case STRING:
        bool_plus_string(A,B,C);
        break;
    case BOOL:
        A.type = BOOL;
        if(B.data.boolean&&C.data.boolean)
        {
            A.data.boolean = true;
        }
        else
        {
            A.data.boolean = false;
        }
        break;
    }
}


bool string_plus(object&A,const object& B,const object& C)
{
    switch(C.type)
    {
    case NUMBER:
        string_plus_num(A,B,C);
        break;
    case STRING:
        string_plus_string(A,B,C);
        break;
    case BOOL:
        string_plus_bool(A,B,C);
        break;
    }
}

//================================
//Combinations
//================================

bool number_plus_bool(object&A,const object& number,const object& boolean)
{
    A.type = BOOL;
    if(boolean.data.boolean&&number.data.number>1)
    {
        A .data.boolean = true;
    }
    else
    {
        A.data.boolean = false;
    }
}

//Strings
bool bool_plus_string(object &a,const object b, const object c)
{
    try
    {
        a.type = STRING;

        if(b.data.boolean)
        {
            a = mem_string_alloc("true");
        }
        else
        {
            a = mem_string_alloc("false");
        }

        a.data.string->append(" ");
        a.data.string->append(*c.data.string);
    }
    catch(std::exception &e)
    {
        out() << "Error Boolean + String: " << e.what() << std::endl;
//        delete c.data.string;
        return false;
    }
//    delete c.data.string;
    return true;
}

bool string_plus_bool(object &a,const object b, const object c)
{
    a = mem_string_alloc(b.data.string->c_str());
    try
    {
        a.data.string->append(" ");
        if(c.data.boolean)
        {
            a.data.string->append("true");
        }
        else
        {
            a.data.string->append("false");
        }
    }
    catch(std::exception &e)
    {
        out() << "Error String + bool: " << e.what() << std::endl;
//        delete b.data.string;
        return false;
    }
    return true;
}

bool num_plus_string(object &a,const object b, const object c)
{
    std::stringstream ss;
    ss << b.data.number;
    a = mem_string_alloc(ss.str().c_str());
    try
    {
        a.data.string->append(" ");
        a.data.string->append(*c.data.string);
    }
    catch(std::exception &e)
    {
        out() << "Error Number + String: " << e.what() << std::endl;
//        delete c.data.string;
        return false;
    }
//    delete c.data.string;
    return true;
}

bool string_plus_num(object &a,const object b, const object c)
{
    a = mem_string_alloc(b.data.string->c_str());
    std::stringstream ss;
    ss << c.data.number;
    try
    {
        a.data.string->append(" ");
        a.data.string->append(ss.str());
    }
    catch(std::exception &e)
    {
        out() << "Error String + Number: " << e.what() << std::endl;
//        delete b.data.string;
        return false;
    }
    return true;
}

bool string_plus_string(object &a,const object b, const object c)
{
    a = mem_string_alloc(b.data.string->c_str());
    try
    {
        a.data.string->append(" ");
        a.data.string->append(*c.data.string);
    }
    catch(std::exception &e)
    {
//        delete b.data.string;
//        delete c.data.string;
        return false;
    }
//    delete c.data.string;
    return true;
}


}
