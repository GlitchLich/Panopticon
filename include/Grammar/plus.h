#ifndef PLUS_H
#define PLUS_H

#include "../core/types.h"
#include <sstream>
#include "../Grammar/parse.h"

namespace panopticon
{
extern void number_plus(object&A,object& B, object& C);
extern void bool_plus(object&A, object& B, object& C);
extern void string_plus(object&A, object& B, object& C);
extern void array_plus(object&A, object& B, object& C);

extern void number_plus_bool(object&A,object& number, object& boolean);

//Strings
extern bool bool_plus_string(object &a,const object b, const object c);
extern bool string_plus_bool(object &a,const object b, const object c);
extern bool num_plus_string(object &a,const object b, const object c);
extern bool string_plus_num(object &a,const object b, const object c);
extern bool string_plus_string(object &a,const object b, const object c);

//arrays
extern bool array_plus_bool(object& a,object& array, object& boolean);
extern bool array_plus_number(object& a,object& array, object& number);
extern void array_plus_string(object&A,object& array, object& string);
extern bool array_plus_array(object& a,object& array1, object& array2);

}
#endif // PLUS_H
