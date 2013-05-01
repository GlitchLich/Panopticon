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
#include "../include/core/heap.h"
#include <algorithm>

/**
 * We have to declare these here - they're not  in any header files
 * we can inclde.  yyparse() is declared with an empty argument list
 * so that it is compatible with the generated C code from bison.
 *
 */

extern FILE *yyin;
typedef size_t yy_size_t;
struct yy_buffer_state
    {
    FILE *yy_input_file;

    char *yy_ch_buf;		/* input buffer */
    char *yy_buf_pos;		/* current position in input buffer */

    /* Size of input buffer in bytes, not including room for EOB
     * characters.
     */
    yy_size_t yy_buf_size;

    /* Number of characters read into yy_ch_buf, not including EOB
     * characters.
     */
    int yy_n_chars;

    /* Whether we "own" the buffer - i.e., we know we created it,
     * and can realloc() it to grow it, and should free() it to
     * delete it.
     */
    int yy_is_our_buffer;

    /* Whether this is an "interactive" input source; if so, and
     * if we're using stdio for input, then we want to use getc()
     * instead of fread(), to make sure we stop fetching input after
     * each newline.
     */
    int yy_is_interactive;

    /* Whether we're considered to be at the beginning of a line.
     * If so, '^' rules will be active on the next match, otherwise
     * not.
     */
    int yy_at_bol;

    int yy_bs_lineno; /**< The line count. */
    int yy_bs_column; /**< The column count. */

    /* Whether to try to fill the input buffer when we reach the
     * end of it.
     */
    int yy_fill_buffer;

    int yy_buffer_status;

#define YY_BUFFER_NEW 0
#define YY_BUFFER_NORMAL 1
    /* When an EOF's been seen but there's still some text to process
     * then we mark the buffer as YY_EOF_PENDING, to indicate that we
     * shouldn't try reading from the input source any more.  We might
     * still have a bunch of tokens to match, though, because of
     * possible backing-up.
     *
     * When we actually see the EOF, we change the status to "new"
     * (via yyrestart()), so that the user can continue scanning by
     * just pointing yyin at a new input file.
     */
#define YY_BUFFER_EOF_PENDING 2

    };
typedef struct yy_buffer_state *YY_BUFFER_STATE;

extern "C" {
int             yylex( void );
YY_BUFFER_STATE yy_scan_string( const char * );
void            yy_delete_buffer( YY_BUFFER_STATE );
}

int n;
int yv;
char buf[BUFS+1];
void* pParser = ParseAlloc (malloc);

struct panopticon::object t0,t1;
struct panopticon::object mToken;

namespace panopticon
{

bool cli = true;
std::stringstream stream_out;

std::ostream& out() {
    if (!cli)
        return stream_out;
    else
        return std::cout;
}

void init()
{

    t0.data.number=0;
    std::cout << "Size of token: " << sizeof(t0) << std::endl;
    std::cout << "Enter an expression like 3+5 <return>" << std::endl;
    std::cout << "  Terminate with ^D" << std::endl;
    init_heap();
}

void mutate_text_for_parsing(std::string& string)
{
    int whitespacecount=0;
    int string_length = string.size();
    for(int i=0;i<string_length-1;++i)
    {
//        if(string.at(i)=='\n' && string.at(i+1)=='\t')
//        {
//            std::cout << "TAB!" << std::endl;
//            whitespacecount++;
//            if(whitespacecount==3)
//            {
//                stringSize-=3;
//                string.replace(i-2,3,"_TAB");
//                whitespacecount = 0;
//            }
//        }

    }
}

bool exec(std::string string, std::string& output)
{
    correct_parsing = true;
    cli = false;
    output.clear();
    stream_out.str(std::string());
    YY_BUFFER_STATE bufferstate;
    try
    {
        int stringSize = string.size();
        for(int i=0;i<stringSize;++i)
        {
            if(((int)string.at(i))<0)
            {
                string.replace(i,3,"\n");
                stringSize-=2;
            }
        }
//        mutate_text_for_parsing(string);
        string = string.append("\n");
        std::cout << "Parsing: " << string << std::endl;
        bufferstate = yy_scan_string(string.c_str());
//        yy_scan_string(string.c_str());
        while( (yv=yylex()) != 0)
        {
            //            std::cout << " yylex() " << yv << " yylval.dval " << yylval.dval << std::endl;
            switch(yv)
            {
            case NUM:
                t0.data.number = yylval.dval;
                break;
            case NAME:
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

        //Error Handling
        if(correct_parsing)
        {
            output.clear();
            output.append(stream_out.str());
            return true;
        }
        else
        {
            out() << "at line: " << bufferstate->yy_bs_lineno << ", column: " << bufferstate->yy_bs_lineno << std::endl;
            output.clear();
            output.append(stream_out.str());
            return false;
        }
    }
    catch(std::exception &e)
    {
        out() << "Error reading a string into parser" << e.what() << std::endl;
        output.clear();
        output.append(stream_out.str());
        return false;
    }
    catch(Error e)
    {
        return true;
    }
    catch(...)
    {
        return false;
    }
}

void command_line_loop()
{
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

}
