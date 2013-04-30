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
#include "../Grammar/parse.h"

#undef STRING
#undef NUM
#undef BOOL
#undef ARRAY

namespace optic = panopticon;

namespace panopticon
{


//GENERAL operations
extern object copy_object(const object &original);
extern bool delete_object(object& obj);
extern bool print_object(const object& A);
extern object convert_to_string( object& original);

extern bool concatenate_arrays(object &a, object b, object c);
extern bool create_array(object &a);
extern bool print_array(const object &A, int arrayNum=0);
extern bool delete_array(object& a);
extern bool object_operator_array(object &a,const object &obj, const object& array, bool (*func)(object &,const object &,const object &));
extern bool array_operator_object(object &a,const object &array,const object& obj, bool (*func)(object &,const object &,const object &));
extern bool recursive_apply(object &a,const object &obj1,const object& obj2, bool (*func)(object &,const object &,const object &));
extern bool object_operator_object(object& a, object& b, object& c, bool (*func)(object &,const object &,const object &));
extern bool array_operator_array(object& a,const object& array1,const object& array2, bool (*func)(object &,const object &,const object &));
extern bool create_function(object&A, const object& B, const object& C);
extern bool call_function(object&A, const object& B, const object& C);

extern bool handle_stack(object &A, Function* function);

//DONE
extern bool plus(object&A, const object &B, const object &C);
extern bool minus(object&A, const object& B, const object& C);
extern bool divide(object&A, const object& B, const object& C);
extern bool multiply(object&A, const object& B, const object& C);
extern bool modulo(object&A, const object& B, const object& C);
extern bool value_pow(object&A, const object& B, const object& C);
extern bool equal_to(object&A, const object& B, const object& C);
extern bool not_equal_to(object&A, const object& B, const object& C);
extern bool less_than(object&A, const object& B, const object& C);
extern bool greater_than(object&A, const object& B, const object& C);
extern bool lore(object&A, const object& B, const object& C);
extern bool gore(object&A, const object& B, const object& C);
extern bool value_and(object&A, const object& B, const object& C);
extern bool value_or(object&A, const object& B, const object& C);
extern bool not_value(object&A, object& B);
extern bool shift_left(object&A, const object& B, const object& C);
extern bool shift_right(object&A, const object& B, const object& C);
extern bool bit_and(object&A, const object& B, const object& C);
extern bool bit_or(object&A, const object& B, const object& C);
extern bool bit_not(object&A, object& B);
extern bool bit_xor(object&A, const object& B, const object& C);
extern bool assign_variable(object&A, const object& B, const object& C);
extern bool retrieve_variable(object&A, object& B);

//NOT DONE
extern bool plusplus(object&A, const object& B, const object& C);
extern bool index(object&A, const object& B, const object& C);
}
#endif // OPERATORS_H
