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
//#include "../include/Grammar/lexer.h"
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


#define MAX_DEPTH 72
unsigned int indent_stack[MAX_DEPTH];
unsigned int level = 0;
int nesting = 0;
unsigned int first = 1;

void clear_lexer()
{
    //clear lexer
    for(int i=0;i<72;++i)
    {
        indent_stack[i] = 0;
    }
    level = 0;
    nesting = 0;
    first = 1;
}

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
    init_heap();
}

bool exec(std::string string, std::string& output)
{
    correct_parsing = true;
    cli = false;
    output.clear();
    stream_out.str(std::string());
    YY_BUFFER_STATE bufferstate;

    clear_lexer();

    try
    {
        int stringSize = string.size();
        int white_count = 0;
        for(int i=0;i<stringSize;++i)
        {
            if(((int)string.at(i))<0)
            {
                string.replace(i,3,"\n");
                stringSize-=2;
            }
            if(((int)string.at(i))=='\n')
            {
                white_count=0;
            }
            if(((int)string.at(i))==' ')
            {
                white_count = (white_count + 1)%4;
            }
            else if(((int)string.at(i))=='\t')
            {
                if(white_count==0)
                {
                    string.replace(i,1,"    ");
                    stringSize+=3;
                }
                else if(white_count==1)
                {
                    string.replace(i,1,"   ");
                    stringSize+=2;
                }
                else if(white_count==2)
                {
                    string.replace(i,1,"  ");
                    stringSize+=1;
                }
                else if(white_count==3)
                {
                    string.replace(i,1," ");
                }
            }
        }
        string = string.append("\n\n");
        calculate_white_space(string);
        std::cout << string << std::endl;
        bufferstate = yy_scan_string(string.c_str());
        while( (yv=yylex()) != 0)
        {
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
            switch(yv)
            {
            case NUM:
                t0.data.number = yylval.dval;
                break;
            case NAME:
                t0.data.string = new std::string(yylval.sval);
                if(yylval.sval!=0)
                {
                    delete yylval.sval;
                }
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

//Significant whitespace

unsigned int white_count(std::string& line,int start,int stop) {
    unsigned int count = 0;
    bool firstChar = false;
    for(int i=start;i<stop;++i)
    {
        if(line.at(i) == ' ' && !firstChar)
        {
            count++;
        }

        else if(line.at(i) != '\n')
        {
            firstChar = true;
        }
    }
    return count ;
}


bool should_replace(const std::string& string,int insert,int indent)
{
    if(string.size()<insert+indent)
    {
        return false;
    }
    std::cout << "REPLACEMENT TEST: " << string.substr(insert,insert+indent+1) << std::endl;

    if(string.at(insert)!='\n')
    {
        return false;
    }
    for(int i=1;i<=indent;++i)
    {
        if(string.at(insert+indent)!=' ')
        {
            return false;
        }
    }

    if(string.at(insert+indent+1)!='}')
    {
        return false;
    }

    return true;
}

void strip_whitespace_before_breaks(std::string& string)
{
    int size = string.size();
    int last_character = 0;
    for(int i=0;i<size;++i)
    {
        if(string.at(i)!=' ')
        {
            if(string.at(i)=='\n')
            {
                if(i==string.size()-1)
                {
                    return;
                }
                int num_erased = (i)-(last_character+1);
                if(num_erased>0)
                {
                    string.erase(string.begin()+last_character+1,string.begin()+i);
                    i-=num_erased;
                    size-=num_erased;
                    last_character-=num_erased;
                }
            }
            else
            {
                last_character = i;
            }
        }
    }
}

void collapse_braces_after_linebreaks(std::string& string)
{
    int size = string.size();
    int last_linebreak = 0;
    int last_character = 0;
    for(int i=0;i<size;++i)
    {
        if(string.at(i)!=' '||string.at(i)!='\n')
        {
            last_character = i;
        }
        if(string.at(i)=='\n')
        {
            last_linebreak = i;
        }
        else if(string.at(i)=='}')
        {
            if(last_linebreak>last_character)
            {
                int num_erased = (i+1)-(last_linebreak+1);
                std::cout << "num_erased: " << num_erased << std::endl;
                std::cout << "i: " << i << std::endl;
                if(num_erased>0)
                {
                    //                string.insert(i,";");
                    string.erase(string.begin()+last_linebreak+1,string.begin()+i+1);
                    i-=(num_erased);
                    size-=(num_erased);
                    last_linebreak-=(num_erased);
                }
            }
        }
    }
}

void stip_final_whitespace(std::string& line)
{
    int num_erase = 0;
    for(int i=line.size()-1;i>0;i-=1)
    {
        if(line.at(i)==' ')
        {
            num_erase++;
        }
        else
        {
            break;
        }
    }
    if(num_erase>0)
    {
        num_erase-=1;
        line.erase(line.end() - num_erase,line.end());
    }
}

//FIX THIS SHIT
void calculate_white_space(std::string& line) {
    //    stip_final_whitespace(line);
    //    strip_whitespace_before_breaks(line);
    //    collapse_braces_after_linebreaks(line);
    int previous_break = 0;
    int size = line.size();
    std::string string;
    string.reserve(line.size()*1.15);
    int insert = -1;
    int insert_add = 0;
    nesting = 0;
    bool blanked = false;
    for(int i=0;i<size;++i)
    {
        insert_add++;
        string.push_back(line.at(i));
        if(line.at(i)=='(')
        {
            nesting-=1;
        }
        else if(line.at(i)==')')
        {
            nesting+=1;
        }
        else if(line.at(i)=='\n'||line.at(i)=='\r'||line.at(i)=='\0')
        {
            if(blanked)
            {
                blanked = false;
                previous_break = i;
                insert+=insert_add;
                insert_add = 0;
                assert(level >= 0);
                continue;
            }
            if (nesting==0)
            {

                unsigned int indent = white_count(line,previous_break,i);

                if (indent == indent_stack[level]) {
                    if (!first)
                    {
                        string.replace(insert,1,";");
//                        string.insert(insert,";");
//                        insert++;
                        //                        size++;
                    }
                    first = 0;
                }
                else if (indent > indent_stack[level]) {
                    //                    if(string.at(insert-1)!='{')
                    //                    {
                    string.replace(insert,1," {");
                    insert++;
//                                            string.insert(insert,"{");
//                                            insert++;
                    //                        size++;
                    //                    }
                    assert(level+1 < MAX_DEPTH);
                    indent_stack[++level] = indent;
                }
                else
                {
                    while (indent < indent_stack[level]) {
                        --level ;

                        //                        std::cout << "INDENT LEVEL!: " << indent << std::endl;
                        //                        if(!should_replace(string,insert,indent))
                        //                        {
                        string.replace(insert,1," }  ");
//                        string.insert(insert-1," ");
                        insert++;
                        insert++;
                        insert++;
//                        insert++;
//                        string.insert(insert," }; ");
//                        insert++;
//                        insert++;
//                        insert++;
//                        insert++;

                        //                            size++;
                        //                            size++;
                        //                        }
                        //                        else
                        //                        {
                        //                            std::cout << "REPLACE!" << std::endl;
                        //                            std::string replacement("};");
                        //                            for(int i=0;i<indent+1;++i)
                        //                            {
                        //                                replacement.append(" ");
                        //                            }
                        //                            string.replace(string.begin()+insert,string.begin()+insert+2+indent,replacement);
                        //                            string.insert(insert,";");
                        //                            insert++;
                        //                            size++;
                        //                            blanked = true;
                        //                        }
                    }
                }
            }
            previous_break = i;
            insert+=insert_add;
            insert_add = 0;
            assert(level >= 0);
        }
    }
    for(int i = string.size()-1;i>0;i-=1)
    {
        if(string.at(i)==';')
        {
            break;
        }
        else if(string.at(i)==' '||string.at(i)=='\n')
        {
            //next
        }
        else
        {
            if(i>=string.size()-1)
            {
                string.append(";");
            }
            else
            {
                string.insert(i+1,";");
            }
            break;
        }
    }
    string.swap(line);
}

}
