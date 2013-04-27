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

#ifndef PARSE_H
#define PARSE_H

#include "tokens.h"
#include <sstream>

#define ParseTOKENTYPE Token
#define ParseARG_PDECL

extern void *ParseAlloc(void *(*mallocProc)(size_t));
extern void Parse(
        void* yyp,                   /* The parser */
        int yymajor,                 /* The major token code number */
        ParseTOKENTYPE yyminor       /* The value for the token */
        ParseARG_PDECL               /* Optional %extra_argument parameter */
        );
extern void ParseFree(
        void *p,                    /* The parser to be deleted */
        void (*freeProc)(void*)     /* Function used to reclaim memory */
        );

namespace panopticon
{

extern bool cli;
extern std::stringstream output_stream;
extern std::ostream& out();

extern void init();
extern void command_line_loop();
extern bool exec(std::string input, std::string &output);

}

namespace optic = panopticon;
#endif // PARSE_H
