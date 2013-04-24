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
%right POW NOT BITNOT UMINUS.
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
in ::= in start NEWLINE.

/*state ::= expr(A).   {*/
/*    std::cout << "Result.value=" << A.value << std::endl;*/
/*    std::cout << "Result.n=" << A.n << std::endl;*/
/*}*/

start ::= spec(A).
{
    switch(A.type)
    {
    case INT:
        std::cout << "Result.data.number=" << A.data.number << std::endl;
        break;
    case STRING:
        std::cout << "Result.data.string=" << A.data.string << std::endl;
        break;
    }
    std::cout << "Result.n=" << A.n << std::endl;
}
/*spec ::= MOD STRING top_stmt.*/
spec(A) ::= top_stmt(B).
{
    A.type = B.type;
    switch(B.type)
    {
    case INT:
        A.data.number = B.data.number;
        break;
    case STRING:
        A.data.string = strdup(B.data.string);
        A.stringLength = B.stringLength;
        break;
    }
    A.n = B.n+1;
}
top_stmt(A) ::= stmt(B).
{
    A.type = B.type;
    switch(B.type)
    {
    case INT:
        A.data.number = B.data.number;
        break;
    case STRING:
        A.data.string = strdup(B.data.string);
        A.stringLength = B.stringLength;
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
    case INT:
        A.data.number = B.data.number;
        break;
    case STRING:
        A.data.string = strdup(B.data.string);
        A.stringLength = B.stringLength;
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
    case INT:
        A.data.number = B.data.number;
        break;
    case STRING:
        A.data.string = strdup(B.data.string);
        A.stringLength = B.stringLength;
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
    case INT:
        A.data.number = B.data.number;
        break;
    case STRING:
        A.data.string = strdup(B.data.string);
        A.stringLength = B.stringLength;
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
    case INT:
        A.data.number = B.data.number;
        break;
    case STRING:
        A.data.string = strdup(B.data.string);
        A.stringLength = B.stringLength;
        break;
    }
    A.n = B.n+1;
}

//BASICS
value(A) ::= NUM(B).
{
    A.data.number = B.data.number;
    A.type = INT;
    A.n = B.n+1;
}

value(A) ::= STRING(B).
{
    A.data.string = strdup(B.data.string);
    A.stringLength = (int)strlen(B.data.string);
    A.type = STRING;
    A.n = B.n+1;
}

//OPERATORS
expr(A) ::= expr(B) MINUS expr(C).
{
    A.data.number = B.data.number - C.data.number;
    A.n = B.n+1  + C.n+1;
}

expr(A) ::= expr(B) PLUS  expr(C).
{
    A.data.number = B.data.number + C.data.number;
    A.n = B.n+1  + C.n+1;
}

expr(A) ::= expr(B) TIMES  expr(C).
{
    A.data.number = B.data.number * C.data.number;
    A.n = B.n+1  + C.n+1;
}

expr(A) ::= expr(B) DIVIDE expr(C).
{
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

expr(A) ::= expr(B) LESSTHAN expr(C).
{
    A.data.number = B.data.number < C.data.number;
    A.n = B.n+1+C.n+1;
}

expr(A) ::= expr(B) GREATERTHAN expr(C).
{
    A.data.number = B.data.number > C.data.number;
    A.n = B.n+1+C.n+1;
}

expr(A) ::= expr(B) EQUALTO expr(C).
{
    A.data.number = B.data.number == C.data.number;
    A.n = B.n+1+C.n+1;
}

expr(A) ::= expr(B) NOTEQUALTO expr(C).
{
    A.data.number = B.data.number != C.data.number;
    A.n = B.n+1+C.n+1;
}

expr(A) ::= expr(B) GORE expr(C).
{
    A.data.number = B.data.number >= C.data.number;
    A.n = B.n+1+C.n+1;
}

expr(A) ::= expr(B) LORE expr(C).
{
    A.data.number = B.data.number <= C.data.number;
    A.n = B.n+1+C.n+1;
}

expr(A) ::= LPAREN expr(B) RPAREN.
{
    A.data.number = B.data.number;
    A.n = B.n+1;
}

expr(A) ::= expr(B) SHIFTL expr(C).
{
    A.data.number = (int)B.data.number << (int)C.data.number;
    A.n = B.n+1+C.n+1;
}

expr(A) ::= expr(B) SHIFTR expr(C).
{
    A.data.number = (int)B.data.number >> (int)C.data.number;
    A.n = B.n+1+C.n+1;
}

expr(A) ::= expr(B) AND expr(C).
{
    A.data.number = (int)B.data.number && (int)C.data.number;
    A.n = B.n+1+C.n+1;
}

expr(A) ::= expr(B) OR expr(C).
{
    A.data.number = (int)B.data.number || (int)C.data.number;
    A.n = B.n+1+C.n+1;
}

expr(A) ::= NOT expr(B).
{
    A.data.number = !((int)B.data.number);
    A.n = B.n+1;
}

expr(A) ::= expr(B) BITAND expr(C).
{
    A.data.number = (int)B.data.number & (int)C.data.number;
    A.n = B.n+1+C.n+1;
}

expr(A) ::= expr(B) BITOR expr(C).
{
    A.data.number = (int)B.data.number | (int)C.data.number;
    A.n = B.n+1+C.n+1;
}

expr(A) ::= BITNOT expr(B).
{
    A.data.number = ~((int)B.data.number);
    A.n = B.n+1;
}

expr(A) ::= MINUS expr(B). [UMINUS]
{
    A.data.number = -1 * B.data.number;
    A.n = B.n+1;
}

expr(A) ::= expr(B) MODULO expr(C).
{
    A.data.number = fmod(B.data.number,C.data.number);
    A.n = B.n+1+C.n+1;
}

/*numberSeq(A) ::= LBRAC expr(B) expr(B) RBRAC.*/
/*{*/

/*}*/

/*expr(A) ::= TRUE.*/
/*{*/
/*    A.value = true;*/
/*    A.n = B.n+1;*/
/*}*/

/*expr(A) ::= FALSE.*/
/*{*/
/*    A.value = false;*/
/*    A.n = B.n+1;*/
/*}*/
/*function(FUNCTION) ::= returnType(TYPE) parameterList(PARAMS) EQUALS methodBody(BODY).*/
/*{*/
/*    FUNCTION = new FunctionNode(TYPE, PARAMS, BODY);*/
/*}*/

