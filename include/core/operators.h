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
extern object create_void_tree();

//extern object de_tree(object& obj);
extern bool concatenate_arrays(object &a, object b, object c);
extern bool create_array(object &a);
extern bool print_array(const object &A, int arrayNum=0, bool isTree=false);
extern bool delete_array(object& a);
extern bool unary_print_object(object &A, const object &B);

extern bool object_operator_array(object &a,const object &obj, const object& array, operator_function func);
extern bool array_operator_object(object &a,const object &array,const object& obj, operator_function func);
extern bool recursive_apply(object &a,const object &obj1,const object& obj2, operator_function func);
extern bool object_operator_object(object& a, object& b, object& c, operator_function func);
extern bool array_operator_array(object& a,const object& array1,const object& array2, operator_function func);
extern bool parse_operations(object& a, const object& b, const object& c, operator_function func);
extern bool resolve_stack_from_parser(object& operation_tree, bool resolve_entire_stack = false);
extern bool create_tree(object&a,const object& obj);
extern bool store_operations(object& a,const object& obj1,unary_operator_function func);
extern bool store_operations(object& a, const object& obj1, const object& obj2, operator_function func, bool expand = true);

extern bool create_function(object&A, const object& B, const object& C);
extern bool call_function(object& A, const object& B, const object& C);
// extern bool call_function(const object& function, const String &name, bool resolve = true); DON'T USE THIS, IT's BROKEN
extern bool handle_stack(object &A, Function* function);

/*
extern void plus();
extern void minus();
extern void divide();
extern void multiply();
extern void modulo();
extern void value_pow();
extern void equal_to();
extern void not_equal_to();
extern void less_than();
extern void greater_than();
extern void lore();
extern void gore();
extern void value_and();
extern void value_or();
extern void not_value();
extern void shift_left();
extern void shift_right();
extern void bit_and();
extern void bit_or();
extern void bit_not();
extern void bit_xor();
extern void assign_variable();
extern void retrieve_variable();*/

// Called by parser

extern bool plus(object&A, const object& B, const object& C);
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
