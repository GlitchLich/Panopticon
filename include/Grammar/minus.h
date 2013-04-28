#ifndef MINUS_H
#define MINUS_H

#include "../core/types.h"
#include <sstream>
#include "../Grammar/parse.h"

namespace panopticon
{

extern bool number_minus(object&A,object& B, object& C);
extern bool bool_minus(object&A, object& B, object& C);
extern bool string_minus(object&A, object& B, object& C);
extern bool array_minus(object&A, object& B, object& C);

extern bool string_minus_string(object &a,const object& b, const object& c);
extern bool number_minus_array(object& a,object& number, object& array);
extern bool string_minus_array(object& a,object& string, object& array);
extern bool array_minus_number(object&A, object& B, object& C);
extern bool array_minus_string(object&A, object& B, object& C);
extern bool array_minus_array(object&A, object& B, object& C);

}

#endif // MINUS_H
