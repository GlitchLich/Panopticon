#ifndef OPERATORS_H
#define OPERATORS_H

#include "types.h"

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
bool string_minus_string(object &a,const object b, const object c)
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

bool string_plus_string(object &a,const object b, const object c)
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

bool string_plusplus_string(object &a,const object b, const object c)
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


}
#endif // OPERATORS_H
