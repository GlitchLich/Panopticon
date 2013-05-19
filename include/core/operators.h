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

#include <sstream>

#include "types.h"
#include "include/Grammar/parse.h"
#include "include/core/function.h"
#include "include/Grammar/conditionals.h"
#include "containers.h"
#include "function.h"

#undef STRING
#undef NUM
#undef BOOL
#undef ARRAY

namespace optic = panopticon;

namespace panopticon
{
//General Operations
bool print_object(const object& A);
bool print_array(const object &A, int arrayNum=0, bool isTree=false);
bool unary_print_object(object &A, const object &B);

bool store_operations(object& a,const object& obj1,unary_operator_function func,bool expand = true);
bool store_operations(object& a, const object& obj1, const object& obj2, operator_function func, bool expand = true);
bool store_operations(object& a, const object& obj1, const object& obj2, bool expand = true);

bool left_section(object& A, object &B, operator_function func, bool expand = true);
bool right_section(object& A, object &B, operator_function func, bool expand = true);


// Operators
bool serial(object& A, const object &B, const object &C);
bool plus(object&A, const object& B, const object& C);
bool minus(object&A, const object& B, const object& C);
bool divide(object&A, const object& B, const object& C);
bool multiply(object&A, const object& B, const object& C);
bool modulo(object&A, const object& B, const object& C);
bool value_pow(object&A, const object& B, const object& C);
bool equal_to(object&A, const object& B, const object& C);
bool not_equal_to(object&A, const object& B, const object& C);
bool less_than(object&A, const object& B, const object& C);
bool greater_than(object&A, const object& B, const object& C);
bool lore(object&A, const object& B, const object& C);
bool gore(object&A, const object& B, const object& C);
bool value_and(object&A, const object& B, const object& C);
bool value_or(object&A, const object& B, const object& C);
bool not_value(object&A, const object& B);
bool shift_left(object&A, const object& B, const object& C);
bool shift_right(object&A, const object& B, const object& C);
bool bit_and(object&A, const object& B, const object& C);
bool bit_or(object&A, const object& B, const object& C);
bool bit_not(object&A,const  object& B);
bool bit_xor(object&A, const object& B, const object& C);
bool assign_variable(object&A, const object& B, const object& C);
bool u_minus(object&A, const object& B);

}
#endif // OPERATORS_H
