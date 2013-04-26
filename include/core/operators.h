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

//STRING_STRING
inline bool string_minus_string(object &a,const object b, const object c)
{
    a.type = STRING;
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
    catch(std::exception e)
    {
        return false;
    }
    return true;
}

inline bool string_plus_string(object &a,const object b, const object c)
{
    a.type = STRING;
    a.data.string = new String(*b.data.string);
    try
    {
        a.data.string->append(" ");
        a.data.string->append(*c.data.string);
    }
    catch(std::exception e)
    {
        return false;
    }
    return true;
}

inline bool string_plusplus_string(object &a,const object b, const object c)
{
    a.type = STRING;
    a.data.string = new String(*b.data.string);
    try
    {
        a.data.string->append(*c.data.string);
    }
    catch(std::exception e)
    {
        return false;
    }
    return true;
}

//STRING_NUM
bool string_plus_num(object &a,const object b, const object c)
{
    a.type = STRING;
    a.data.string = new String(*b.data.string);
    std::stringstream ss;
    ss << c.data.number;
    try
    {
        a.data.string->append(" ");
        a.data.string->append(ss.str());
    }
    catch(std::exception e)
    {
        return false;
    }
    return true;
}

inline bool string_plusplus_num(object &a,const object b, const object c)
{
    a.type = STRING;
    a.data.string = new String(*b.data.string);
    std::stringstream ss;
    ss << c.data.number;
    try
    {
        a.data.string->append(ss.str());
    }
    catch(std::exception e)
    {
        return false;
    }
    return true;
}

inline bool num_plus_string(object &a,const object b, const object c)
{
    a.type = STRING;
    std::stringstream ss;
    ss << b.data.number;
    a.data.string = new String(ss.str());
    try
    {
        a.data.string->append(" ");
        a.data.string->append(*c.data.string);
    }
    catch(std::exception e)
    {
        return false;
    }
    return true;
}

inline bool num_plusplus_string(object &a,const object b, const object c)
{
    a.type = STRING;
    std::stringstream ss;
    ss << b.data.number;
    a.data.string = new String(ss.str());
    try
    {
        a.data.string->append(*c.data.string);
    }
    catch(std::exception e)
    {
        return false;
    }
    return true;
}

//STRING_BOOL
bool string_plus_bool(object &a,const object b, const object c)
{
    a.type = STRING;
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
    catch(std::exception e)
    {
        return false;
    }
    return true;
}

bool string_plusplus_bool(object &a,const object b, const object c)
{
    a.type = STRING;
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
    catch(std::exception e)
    {
        return false;
    }
    return true;
}

bool bool_plus_string(object &a,const object b, const object c)
{
    a.type = STRING;
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
    catch(std::exception e)
    {
        return false;
    }
    return true;
}

bool bool_plusplus_string(object &a,const object b, const object c)
{
    a.type = STRING;
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
    catch(std::exception e)
    {
        return false;
    }
    return true;
}

}
#endif // OPERATORS_H
