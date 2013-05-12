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

#undef STRING
#undef NUM
#undef BOOL
#undef ARRAY

namespace optic = panopticon;

namespace panopticon
{


//GENERAL operations
// object copy_object(const object &original);
// bool delete_object(object& obj);
bool print_object(const object& A);
object convert_to_string( object& original);
object create_void_tree();

// Dictionaries
// bool create_dictionary(object& dict);
// bool delete_dictionary(object& dict);
bool print_dictionary(const object& dict);
bool dictionary_lookup(object& value, const object& dict, const object& key);
bool dictionary_contains(object &boolean, const object &dict, const object &key);
bool dictionary_insert(object& dictionary_A,const object& string_B, const object& object_C);

//object de_tree(object& obj);
// bool concatenate_arrays(object &a, object b, object c);
// bool create_array(object &a);
bool print_array(const object &A, int arrayNum=0, bool isTree=false);
// bool delete_array(object& a);
bool unary_print_object(object &A, const object &B);

bool object_operator_array(object &a,const object &obj, const object& array, operator_function func);
bool array_operator_object(object &a,const object &array,const object& obj, operator_function func);
bool recursive_apply(object &a,const object &obj1,const object& obj2, operator_function func);
// bool object_operator_object(object& a, object& b, object& c, operator_function func);
bool array_operator_array(object& a,const object& array1,const object& array2, operator_function func);
bool parse_operations(object& a, const object& b, const object& c, operator_function func);
bool resolve_stack_from_parser(const object &operation_tree, bool resolve_entire_stack = false);
bool create_tree(object&a,const object& obj);
bool store_operations(object& a,const object& obj1,unary_operator_function func,bool expand = true);
bool store_operations(object& a, const object& obj1, const object& obj2, operator_function func, bool expand = true);
bool store_operations(object& a, const object& obj1, const object& obj2, bool expand = true);

bool create_function(object&A, const object& B, const object& C);
bool call_function(object& A, const object& B, const object& C);
bool call_function_array(object& A, const object& B, const object& C);
bool resolve_function_array(object& A, const object& B);
bool handle_stack(object &A, Function* function);

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
bool retrieve_variable(object&A, object& B);
bool u_minus(object&A, const object& B);

//NOT DONE
bool plusplus(object&A, const object& B, const object& C);
bool index(object&A, const object& B, const object& C);
}
#endif // OPERATORS_H
