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

#ifndef ERRORS_H
#define ERRORS_H
#include <string>

namespace panopticon
{

enum Error
{
    UnknownError,
    OpenQuoteError,//p0001
    MulStringError,//p0002
    DivideStringError, //p0003
    IncorrectBooleanComparisonGreater, //p0004
    IncorrectBooleanComparisonLesser, //p0005
    IndexOutOfBounds,//p0006
    SubtractStringFromNum,//p0007
    SubtractBoolFromNum,//p0008
    DivideBooolError,//p0009
    MultiplyBoolError,//p0010
    MultiplyStringError,//p0011
    SubtractNumFromString,//p0012
    SubtractBoolFromString,//p0013
    ModBoolError,//p0014
    ModStringError,//p0015
    PowBoolError,//p0016
    PowStringError//p0016
};
extern bool correct_parsing;
extern std::string print_error(Error error_code);

}
#endif // ERRORS_H
