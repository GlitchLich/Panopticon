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
#ifndef PARSINGUTILITIES_H
#define PARSINGUTILITIES_H

#include <iostream>
#include <sstream>
#include <algorithm>
#include "../../include/core/types.h"

bool is_number(const std::string& s)
{
    bool isNumber = false;
    std::string::const_iterator it = s.begin();
    if(std::count(s.begin(), s.end(), '.')<2)
    {
        while (
               it != s.end() && (
                   std::isdigit(*it) ||
                   ((*it)=='.')
                    )
               ) ++it;
        isNumber = !s.empty() && it == s.end();
    }
    return isNumber;
}

double string_to_double( const std::string& s )
{
    std::istringstream i(s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}

bool insure_ready_for_assignment(panopticon::object& B, panopticon::object& C)
{
//    std::cout << "insure_ready_for_assignment: C.type: " << C.type << std::endl;
    if(
        C.type == panopticon::OPERATION ||
        C.type == panopticon::NUMBER ||
        C.type == panopticon::STRING ||
        C.type == panopticon::BOOL   ||
        C.type == panopticon::ARRAY ||
        C.type != panopticon::OPERATION_TREE
    )
    {
        panopticon::object temp = C;
        C.data.array = new panopticon::Array();
        C.data.array->reserve(1);
        C.data.array->push_back(temp);
    }
    C.type = panopticon::FUNCTION_BODY;
    if(B.type!=optic::ARRAY)
    {
        panopticon::object temp = B;
        B.type=optic::ARRAY;
        B.data.array = new optic::Array();
        B.data.array->reserve(1);
        B.data.array->push_back(temp);
    }
}

#endif // PARSINGUTILITIES_H
