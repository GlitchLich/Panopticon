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

#include "Grammar/parse.h"
#include <iostream>

#ifndef PN_IDE
int main(int argc,char** argv)
{
    panopticon::init();

    //This starts the command line interface
//    panopticon::command_line_loop();

    //This is how you read a string into the parser manually
    std::string output;

    panopticon::exec("3*5",output);
    std::cout << output;

    optic::exec("5.1/10^2",output);
    std::cout << output;
}

#endif
