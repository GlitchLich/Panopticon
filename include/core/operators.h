/*
    Panopticon - Audio/Graphics/Networking Language
    Copyright (C) 2013 Chad McKinney and Curtis McKinney

    All rights reserved.

    This file is part of Panopticon.

    Panopticon is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Panopticon is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Panopticon.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPERATORS_H
#define OPERATORS_H

#include "types.h"
#include <sstream>
#undef STRING
#undef NUM
#undef BOOL
#undef ARRAY
/*
//Types
    NIL = 0,
    BOOLEAN,
    NUMBER,
    STRING,
    FUNCTION,
    ARRAY,
    MAP
*/

namespace panopticon
{

//==================
//ARRAYS
//==================
inline void print_array(const object &A,int arrayNum=0)
{
    if(arrayNum!=0)
    {
        std::cout << " ";
    }
    std::cout << "[";
    for(int i=0;i<A.data.array->size();++i)
    {
        const panopticon::object& B = A.data.array->at(i);
        switch(B.type)
        {
        case NUMBER:
            std::cout << " " << B.data.number;
            break;
        case STRING:
            std::cout << " " << *(A.data.array->at(i).data.string);
            break;
        case BOOL:
            if(B.data.boolean)
            {
                std::cout << " true";
            }
            else
            {
                std::cout << " false";
            }
            break;
        case ARRAY:
            print_array(B,arrayNum+1);
            break;
        }
    }
    std::cout << " ] ";
    if(arrayNum==0)
    {
        std::cout << std::endl;
    }
}

inline bool add_number_to_array(object& a,const object& array, const object& number)
{
    a.data.array = new std::vector<object>();
    a.data.array->reserve(array.data.array->size());

    for(int i=0;i<array.data.array->size();++i)
    {
        object newObject;
        newObject.type = array.data.array->at(i).type;

        if(array.data.array->at(i).type==NUMBER)
        {
            newObject.data.number = array.data.array->at(i).data.number + number.data.number;
            a.data.array->push_back(newObject);
        }
        else
        {
            add_number_to_array(newObject,array.data.array->at(i),number);
            a.data.array->push_back(newObject);
        }
    }
}

inline bool add_numerical_arrays(object&a, const object& b, const object& c)
{
    a.data.array = new std::vector<object>();
    int size = 1;

    if(b.data.array->size()>=c.data.array->size())
    {
        a.data.array->reserve(b.data.array->size());
        size = b.data.array->size();
    }
    else
    {
        a.data.array->reserve(c.data.array->size());
        size = c.data.array->size();
    }

    for(int i=0;i<size;++i)
    {
        panopticon::object& bb = b.data.array->at(i%(b.data.array->size()));
        panopticon::object& cc = c.data.array->at(i%(c.data.array->size()));
        object newObject;

        if(bb.type==NUMBER&&cc.type==NUMBER)
        {
            newObject.type = NUMBER;
            newObject.data.number = bb.data.number+cc.data.number;
            a.data.array->push_back(newObject);
        }
        else if(bb.type==NUMBER&&cc.type==ARRAY)
        {
            newObject.type = ARRAY;
            add_number_to_array(newObject,cc,bb);
            a.data.array->push_back(newObject);
        }
        else if(bb.type==ARRAY&&cc.type==NUMBER)
        {
            newObject.type = ARRAY;
            add_number_to_array(newObject,bb,cc);
            a.data.array->push_back(newObject);
        }
        else
        {
            newObject.type = ARRAY;
            add_numerical_arrays(newObject,bb,cc);
            a.data.array->push_back(newObject);
        }
    }
}

inline bool is_numerical(const object &a)
{
    bool isNumerical = false;
    for(int i=0;i<a.data.array->size();++i)
    {
        const panopticon::object& b = a.data.array->at(i);
        switch(b.type)
        {
        case NUMBER:
            isNumerical = true;
            break;
        case STRING:
            isNumerical = false;
            goto endd;
            break;
        case BOOL:
            isNumerical = false;
            goto endd;
            break;
        case ARRAY:
            isNumerical = is_numerical(b);
            break;
        }
    }
    endd:
    return isNumerical;
}

inline bool delete_array(object& a)
{
    for(int i=0;i<a.data.array->size();++i)
    {
        panopticon::object& b = a.data.array->at(i);
        switch(b.type)
        {
        case NUMBER:
            break;
        case STRING:
            delete b.data.string;
            break;
        case BOOL:
            break;
        case ARRAY:
            delete_array(b);
            break;
        }
    }
    delete a.data.array;
}


inline bool create_array(object &a)
{
    a.data.array = new std::vector<panopticon::object>();
}

//STRING_STRING
inline bool string_minus_string(object &a,const object b, const object c)
{
    a.data.string = new String(*b.data.string);
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
        delete b.data.string;
        delete c.data.string;
        return false;
    }
    delete b.data.string;
    delete c.data.string;
    return true;
}

inline bool string_plus_string(object &a,const object b, const object c)
{
    a.data.string = new String(*b.data.string);
    try
    {
        a.data.string->append(" ");
        a.data.string->append(*c.data.string);
    }
    catch(std::exception &e)
    {
        delete b.data.string;
        delete c.data.string;
        return false;
    }
    delete b.data.string;
    delete c.data.string;
    return true;
}

inline bool string_plusplus_string(object &a,const object b, const object c)
{
    a.data.string = new String(*b.data.string);
    try
    {
        a.data.string->append(*c.data.string);
    }
    catch(std::exception &e)
    {
        delete b.data.string;
        delete c.data.string;
        return false;
    }
    delete b.data.string;
    delete c.data.string;
    return true;
}

//STRING_NUM
inline bool string_plus_num(object &a,const object b, const object c)
{
    a.data.string = new String(*b.data.string);
    std::stringstream ss;
    ss << c.data.number;
    try
    {
        a.data.string->append(" ");
        a.data.string->append(ss.str());
    }
    catch(std::exception &e)
    {
        std::cerr << "Error String + Number: " << e.what() << std::endl;
        delete b.data.string;
        return false;
    }
    delete b.data.string;
    return true;
}

inline bool string_plusplus_num(object &a,const object b, const object c)
{
    a.data.string = new String(*b.data.string);
    std::stringstream ss;
    ss << c.data.number;
    try
    {
        a.data.string->append(ss.str());
    }
    catch(std::exception &e)
    {
        std::cerr << "Error String ++ Number: " << e.what() << std::endl;
        delete b.data.string;
        return false;
    }
    delete b.data.string;
    return true;
}

inline bool num_plus_string(object &a,const object b, const object c)
{
    std::stringstream ss;
    ss << b.data.number;
    a.data.string = new String(ss.str());
    try
    {
        a.data.string->append(" ");
        a.data.string->append(*c.data.string);
    }
    catch(std::exception &e)
    {
        std::cerr << "Error Number + String: " << e.what() << std::endl;
        delete c.data.string;
        return false;
    }
    delete c.data.string;
    return true;
}

inline bool num_plusplus_string(object &a,const object b, const object c)
{
    std::stringstream ss;
    ss << b.data.number;
    a.data.string = new String(ss.str());
    try
    {
        a.data.string->append(*c.data.string);
    }
    catch(std::exception &e)
    {
        std::cerr << "Error Number ++ String: " << e.what() << std::endl;
        delete c.data.string;
        return false;
    }
    delete c.data.string;
    return true;
}

//STRING_BOOL
inline bool string_plus_bool(object &a,const object b, const object c)
{
    a.data.string = new String(*b.data.string);
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
        std::cerr << "Error String + bool: " << e.what() << std::endl;
        delete b.data.string;
        return false;
    }
    delete b.data.string;
    return true;
}

inline bool string_plusplus_bool(object &a,const object b, const object c)
{
    a.data.string = new String(*b.data.string);
    try
    {
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
        std::cerr << "Error String ++ bool: " << e.what() << std::endl;
        delete b.data.string;
        return false;
    }
    delete b.data.string;
    return true;
}

inline bool bool_plus_string(object &a,const object b, const object c)
{
    try
    {
        if(b.data.boolean)
        {
            a.data.string = new String("true");
        }
        else
        {
            a.data.string = new String("false");
        }
        a.data.string->append(" ");
        a.data.string->append(*c.data.string);
    }
    catch(std::exception &e)
    {
        std::cerr << "Error Boolean + String: " << e.what() << std::endl;
        delete c.data.string;
        return false;
    }
    delete c.data.string;
    return true;
}

inline bool bool_plusplus_string(object &a,const object b, const object c)
{
    try
    {
        if(b.data.boolean)
        {
            a.data.string = new String("true");
        }
        else
        {
            a.data.string = new String("false");
        }

        a.data.string->append(*c.data.string);
    }
    catch(std::exception &e)
    {
        std::cerr << "Error Boolean ++ String: " << e.what() << std::endl;
        delete c.data.string;
        return false;
    }
    delete c.data.string;
    return true;
}

}
#endif // OPERATORS_H
