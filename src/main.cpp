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

#include <stdio.h>

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#define BUFS 1024
#include <stdio.h>
#include <string.h>
#include "../include/Grammar/parse.h"
#include "../include/Grammar/tokens.h"
#include "../include/Grammar/lexglobal.h"
#include "../include/Grammar/grammar.h"

/**
 * We have to declare these here - they're not  in any header files
 * we can inclde.  yyparse() is declared with an empty argument list
 * so that it is compatible with the generated C code from bison.
 *
 */

extern FILE *yyin;
typedef struct yy_buffer_state *YY_BUFFER_STATE;

extern "C" {
int             yylex( void );
YY_BUFFER_STATE yy_scan_string( const char * );
void            yy_delete_buffer( YY_BUFFER_STATE );
}


#ifndef PN_IDE
int main(int argc,char** argv)
{
    int n;
    int yv;
    char buf[BUFS+1];
    void* pParser = ParseAlloc (malloc);

    struct panopticon::object t0,t1;
    struct panopticon::object mToken;

//    t0.n=0;
    t0.data.number=0;

    //    std::cout << "Size of string: " << sizeof(const char*) << std::endl;
    //    std::cout << "Size of double: " << sizeof(double) << std::endl;
    //    std::cout << "Size of data: " << sizeof(panopticon::Data) << std::endl;
    std::cout << "Size of token: " << sizeof(t0) << std::endl;
    //    std::cout << "Size of void*: " << sizeof(void*) << std::endl;
    std::cout << "Enter an expression like 3+5 <return>" << std::endl;
    std::cout << "  Terminate with ^D" << std::endl;

    while ( ( n=read(fileno(stdin), buf, BUFS )) >  0)
    {
        buf[n]='\0';
        yy_scan_string(buf);
        // on EOF yylex will return 0
        while( (yv=yylex()) != 0)
        {
            //            std::cout << " yylex() " << yv << " yylval.dval " << yylval.dval << std::endl;
            switch(yv)
            {
            case NUM:
                t0.data.number = yylval.dval;
                break;
            case STRING:
                t0.data.string = new std::string(yylval.sval);
                if(yylval.sval!=0)
                {
                    delete yylval.sval;
                }
                break;
            case BOOLEAN:
                t0.data.boolean = yylval.bval;
            }
            Parse(pParser, yv, t0);
        }


    }

    Parse (pParser, 0, t0);
    ParseFree(pParser, free );
}

#endif
