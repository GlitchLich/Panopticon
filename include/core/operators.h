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
extern object copy_object(object &original);
extern bool delete_object(object& obj);
extern bool print_object( object& A);
extern object convert_to_string( object& original);

extern bool concatenate_arrays(object &a, object b, object c);
extern bool create_array(object &a);
extern bool print_array( object &A,int arrayNum=0);
extern bool delete_array(object& a);
extern bool object_operator_array(object &a, object &obj, object& array, bool (*func)(object &, object &, object &));
extern bool array_operator_object(object &a, object &array, object& obj, bool (*func)(object &, object &, object &));
extern bool recursive_apply(object &a, object &obj1, object& obj2, bool (*func)(object &, object &, object &));
extern bool object_operator_object(object& a, object& b, object& c, bool (*func)(object &, object &, object &));
extern bool array_operator_array(object& a, object& array1, object& array2, bool (*func)(object &, object &, object &));

//DONE
extern bool plus(object&A, object& B, object& C);
extern bool minus(object&A, object& B, object& C);
extern bool divide(object&A, object& B, object& C);
extern bool multiply(object&A, object& B, object& C);
extern bool modulo(object&A, object& B, object& C);
extern bool value_pow(object&A, object& B, object& C);
extern bool equal_to(object&A, object& B, object& C);
extern bool not_equal_to(object&A, object& B, object& C);
extern bool less_than(object&A, object& B, object& C);
extern bool greater_than(object&A, object& B, object& C);
extern bool lore(object&A, object& B, object& C);
extern bool gore(object&A, object& B, object& C);
extern bool value_and(object&A, object& B, object& C);
extern bool value_or(object&A, object& B, object& C);
extern bool not_value(object&A, object& B);
extern bool shift_left(object&A, object& B, object& C);
extern bool shift_right(object&A, object& B, object& C);
extern bool bit_and(object&A, object& B, object& C);
extern bool bit_or(object&A, object& B, object& C);


//NOT DONE
//PLUSPLUS
extern bool bit_not(object&A, object& B);
extern bool bit_xor(object&A, object& B, object& C);
extern bool plusplus(object&A, object& B, object& C);
extern bool index(object&A, object& B, object& C);
}
#endif // OPERATORS_H
