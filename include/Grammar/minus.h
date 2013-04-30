#ifndef MINUS_H
#define MINUS_H

#include "../core/types.h"
#include <sstream>
#include "../Grammar/parse.h"

namespace panopticon
{

extern bool number_minus(object&A,const object& B,const object& C);
extern bool bool_minus(object&A, const object& B, const object& C);
extern bool string_minus(object&A, const object& B, const object& C);
extern bool array_minus(object&A, const object& B, const object& C);

extern bool string_minus_string(object &a,const object& b, const object& c);
extern bool number_minus_array(object& a,const object& number,const object& array);
extern bool string_minus_array(object& a,const object& string,const object& array);
extern bool array_minus_number(object&A, const object& B, const object& C);
extern bool array_minus_string(object&A, const object& B, const object& C);
extern bool array_minus_array(object&A, const object& B, const object& C);

}

#endif // MINUS_H
