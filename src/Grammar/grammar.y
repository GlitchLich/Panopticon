/* Copyright (GPL) 2013 Curtis McKinney, casiosk1@gmail.com*/

%include {
#include <iostream>
#include "../../include/Grammar/tokens.h"
#include "../../include/Grammar/grammar.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
/*#include "lexglobal.h"*/
#include <assert.h>
#include <math.h>
#define BUFS 1024
#include <stdio.h>
#include <string.h>
#include "core/operators.h"

#undef STRING
#undef NUM

using namespace panopticon;

    void token_destructor(Token t)
    {
/*    std::cout << "In token_destructor t.value= " << t.value << std::endl;*/
/*    std::cout << "In token_destructor t.n= " << t.n << std::endl;*/
    }
}


%token_type {Token}
%default_type {Token}
%token_destructor { token_destructor($$); }

%type expr {Token}
%type id {Token}

//Precedence: Top is lowest, bottom is highest



%left OR.
%left AND.
%left BITXOR.
%left BITOR.
%left BITAND.
%left EQUALTO NOTEQUALTO.
%left GREATERTHAN GORE LESSTHAN LORE.
%left SHIFTL SHIFTR.
%left PLUS MINUS.
%left DIVIDE TIMES MODULO.
%right POW NOT BITNOT UMINUS PLUSPLUS.
%left LPAREN RPAREN COMMA LBRAC RBRAC.
%left ASSIGN.


%parse_accept {
printf("parsing complete!\n\n\n");
}


%syntax_error {
std::cout << "Syntax error!" << std::endl;
}

main ::= in.
in ::= .
in ::= in NEWLINE.
in ::= in start NEWLINE.

/*error ::= OPENQUOTE.*/

/*state ::= expr(A).   {*/
/*    std::cout << "Result.value=" << A.value << std::endl;*/
/*    std::cout << "Result.n=" << A.n << std::endl;*/
/*}*/

start ::= spec(A).
{
/*    std::cout << "Result.type="<< A.type << std::endl;*/
    switch(A.type)
    {
    case NUMBER:
        std::cout << "Number=" << A.data.number << std::endl;
        break;
    case STRING:
        std::cout << "String=" << *A.data.string << std::endl;
        break;
    }
/*    std::cout << "Result.n=" << A.n << std::endl;*/
}
/*spec ::= MOD STRING top_stmt.*/
spec(A) ::= top_stmt(B).
{
    A.type = B.type;
    switch(B.type)
    {
    case NUMBER:
        A.data.number = B.data.number;
        break;
    case STRING:
        A.data.string = new String(B.data.string->c_str());
        break;
    }
    A.n = B.n+1;
}
top_stmt(A) ::= stmt(B).
{
    A.type = B.type;
    switch(B.type)
    {
    case NUMBER:
        A.data.number = B.data.number;
        break;
    case STRING:
        A.data.string = new String(B.data.string->c_str());
        break;
    }
    A.n = B.n+1;
}
/*top_stmt ::= conditional.*/
stmt(A) ::= expr(B).
{
    A.type = B.type;
    switch(B.type)
    {
    case NUMBER:
        A.data.number = B.data.number;
        break;
    case STRING:
        A.data.string = new String(B.data.string->c_str());
        break;
    }
    A.n = B.n+1;
}
/*stmt ::= assignment.*/
/*conditional ::= IF stmt_list.*/
expr(A) ::= retval(B).
{
    A.type = B.type;
    switch(B.type)
    {
    case NUMBER:
        A.data.number = B.data.number;
        break;
    case STRING:
        A.data.string = new String(B.data.string->c_str());
        break;
    }
    A.n = B.n+1;
}
/*expr ::= NOT retval.*/
/*retval ::= access.*/
retval(A) ::= invoke(B).
{
    A.type = B.type;
    switch(B.type)
    {
    case NUMBER:
        A.data.number = B.data.number;
        break;
    case STRING:
        A.data.string = new String(B.data.string->c_str());
        break;
    }
    A.n = B.n+1;
}
/*access ::= identifier OBJECT_OPERATOR property_chain.*/
/*access ::= identifier.*/
/*property_chain ::= property_chain OBJECT_OPERATOR identifier.*/
/*property_chain ::= identifier.*/
/*identifier ::= value.*/
/*identifier ::= STRING.*/
/*assignment ::= access ASSIGN expr. [ASSIGN]*/
/*stmt_list ::= stmt.*/
/*stmt_list ::= stmt_list COMMA stmt. [COMMA]*/
/*invoke ::= access LPAREN maybe_empty_stmt_list RPAREN.*/
/*maybe_empty_stmt_list ::= .*/
/*maybe_empty_stmt_list ::= stmt_list.*/
invoke(A) ::= value(B).
{
    A.type = B.type;
    switch(B.type)
    {
    case NUMBER:
        A.data.number = B.data.number;
        break;
    case STRING:
        A.data.string = new String(B.data.string->c_str());
        break;
    }
    A.n = B.n+1;
}

in ::= error(B).
{
    switch(B)
    {
    case OpenQuoteError:
/*        std::cerr << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        std::cerr << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}

error(A) ::= OPENQUOTEERROR(B).
{
    B.type = NUMBER;
    A = OpenQuoteError;
}


value(A) ::= num(B).
{
    A.data.number = B.data.number;
    A.type = NUMBER;
    A.n = B.n+1;
}

value(A) ::= string(B).
{
    A.data.string = new String(B.data.string->c_str());
    A.type = STRING;
    A.n = B.n+1;
}

//BASICS
num(A) ::= NUM(B).
{
    A.data.number = B.data.number;
    A.type = NUMBER;
    A.n = B.n+1;
}

string(A) ::= STRING(B).
{
    A.data.string = new String(B.data.string->c_str());
    A.type = STRING;
    A.n = B.n+1;
}

//FIX POINTERS!

/*expr(A) ::= LPAREN expr(B) RPAREN.*/
/*{*/
/*    A.type = B.type;*/
/*    A.data.number = B.data.number;*/
/*    A.n = B.n+1;*/
/*}*/

//OPERATORS, STRING_STRING
string(A) ::= LPAREN string(B) RPAREN.
{
    A.type = STRING;
    A.data.string = B.data.string;
    A.n = B.n+1;
}

string(A) ::= string(B) MINUS string(C).
{
    panopticon::string_minus_string(A,B,C);
    A.n = B.n+1  + C.n+1;
}

string(A) ::= string(B) PLUS string(C).
{
    panopticon::string_plus_string(A,B,C);
    A.n = B.n+1  + C.n+1;
}

string(A) ::= string(B) PLUSPLUS string(C).
{
    panopticon::string_plusplus_string(A,B,C);
    A.n = B.n+1  + C.n+1;
}

string(A) ::= string(B) EQUALTO string(C).
{
    A.type = STRING;
    A.data.number = B.data.number == C.data.number;
    A.n = B.n+1+C.n+1;
}

//OPERATORS, NUMBER_NUMBER
num(A) ::= LPAREN num(B) RPAREN.
{
    A.type = NUMBER;
    A.data.number = B.data.number;
    A.n = B.n+1;
}

num(A) ::= num(B) MINUS num(C).
{
    A.type = NUMBER;
    A.data.number = B.data.number - C.data.number;
    A.n = B.n+1  + C.n+1;
}

num(A) ::= num(B) PLUS  num(C).
{
    A.type = NUMBER;
    A.data.number = B.data.number + C.data.number;
    A.n = B.n+1  + C.n+1;
}

num(A) ::= num(B) TIMES  num(C).
{
    A.type = NUMBER;
    A.data.number = B.data.number * C.data.number;
    A.n = B.n+1  + C.n+1;
}

num(A) ::= num(B) DIVIDE num(C).
{
    A.type = NUMBER;
    if(C.data.number != 0)
    {
         A.data.number = B.data.number / C.data.number;
         A.n = B.n+1 + C.n+1;
    }
    else
    {
         std::cout << "divide by zero" << std::endl;
    }
}

num(A) ::= num(B) LESSTHAN num(C).
{
    A.type = NUMBER;
    A.data.number = B.data.number < C.data.number;
    A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) GREATERTHAN num(C).
{
    A.type = NUMBER;
    A.data.number = B.data.number > C.data.number;
    A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) EQUALTO num(C).
{
    A.type = NUMBER;
    A.data.number = B.data.number == C.data.number;
    A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) NOTEQUALTO num(C).
{
    A.type = NUMBER;
    A.data.number = B.data.number != C.data.number;
    A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) GORE num(C).
{
    A.type = NUMBER;
    A.data.number = B.data.number >= C.data.number;
    A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) LORE num(C).
{
    A.type = NUMBER;
    A.data.number = B.data.number <= C.data.number;
    A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) SHIFTL num(C).
{
    A.type = NUMBER;
    A.data.number = (int)B.data.number << (int)C.data.number;
    A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) SHIFTR num(C).
{
    A.type = NUMBER;
    A.data.number = (int)B.data.number >> (int)C.data.number;
    A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) AND num(C).
{
    A.type = NUMBER;
    A.data.number = (int)B.data.number && (int)C.data.number;
    A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) OR num(C).
{
    A.type = NUMBER;
    A.data.number = (int)B.data.number || (int)C.data.number;
    A.n = B.n+1+C.n+1;
}

num(A) ::= NOT num(B).
{
    A.type = NUMBER;
    A.data.number = !((int)B.data.number);
    A.n = B.n+1;
}

num(A) ::= num(B) BITAND num(C).
{
    A.type = NUMBER;
    A.data.number = (int)B.data.number & (int)C.data.number;
    A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) BITOR num(C).
{
    A.type = NUMBER;
    A.data.number = (int)B.data.number | (int)C.data.number;
    A.n = B.n+1+C.n+1;
}

num(A) ::= BITNOT num(B).
{
    A.type = NUMBER;
    A.data.number = ~((int)B.data.number);
    A.n = B.n+1;
}

num(A) ::= MINUS num(B). [UMINUS]
{
    A.type = NUMBER;
    A.data.number = -1 * B.data.number;
    A.n = B.n+1;
}

num(A) ::= num(B) MODULO num(C).
{
    A.type = NUMBER;
    A.data.number = fmod(B.data.number,C.data.number);
    A.n = B.n+1+C.n+1;
}
