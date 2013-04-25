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


int main(int argc,char** argv)
{
    int n;
    int yv;
    char buf[BUFS+1];
    void* pParser = ParseAlloc (malloc);

    struct panopticon::object t0,t1;
    struct panopticon::object mToken;

    t0.n=0;
    t0.data.number=0;

    //    std::cout << "Size of string: " << sizeof(const char*) << std::endl;
    //    std::cout << "Size of double: " << sizeof(double) << std::endl;
    //    std::cout << "Size of data: " << sizeof(panopticon::Data) << std::endl;
    std::cout << "Size of token: " << sizeof(panopticon::object) << std::endl;
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
                break;
//            case OPENQUOTEERROR:
//                yv = NEWLINE;
//                std::cerr << "ERROR p0001: Dangling quotation mark." << std::endl;
//                break;
            }
            Parse(pParser, yv, t0);
        }


    }

    Parse (pParser, 0, t0);
    ParseFree(pParser, free );

}
