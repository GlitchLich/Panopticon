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
#include "../../include/Grammar/parsingutilities.h"
#include "../../include/core/types.h"
#include "../../include/Grammar/parse.h"
#include "../../include/core/errors.h"

#undef STRING
#undef NUM
#undef BOOL
#undef panopticon::ARRAY

/*using namespace panopticon;*/

    void token_destructor(Token t)
    {
/*    panopticon::out() << "In token_destructor t.value= " << t.value << std::endl;*/
/*    panopticon::out() << "In token_destructor t.n= " << t.n << std::endl;*/
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
%left INDEX.
%left LPAREN RPAREN COMMA LBRAC RBRAC.
%left ASSIGN.


%parse_accept {
printf("parsing complete!\n\n\n");
}


%syntax_error {
panopticon::out() << "Syntax error!" << std::endl;
}

main ::= in.
in ::= .
in ::= in NEWLINE.
in ::= in start NEWLINE.

/*state ::= expr(A).   {*/
/*    panopticon::out() << "Result.value=" << A.value << std::endl;*/
/*    panopticon::out() << "Result.n=" << A.n << std::endl;*/
/*}*/

start ::= spec(A).
{
    optic::print_object(A);
    optic::delete_object(A);
}

/*spec ::= MOD STRING top_stmt.*/
spec(A) ::= top_stmt(B).
{
    A=B;

}
top_stmt(A) ::= stmt(B).
{
    A=B;

}
/*top_stmt ::= conditional.*/
stmt(A) ::= expr(B).
{
    A = B;

}
/*stmt ::= assignment.*/
/*conditional ::= IF stmt_list.*/
expr(A) ::= retval(B).
{
    A=B;

}
/*expr ::= NOT retval.*/
retval(A) ::= access(B).
{
    A = B;

}

/*access ::= identifier OBJECT_OPERATOR property_chain.*/
access(A) ::= identifier(B).
{
    A = B;

}
/*property_chain ::= property_chain OBJECT_OPERATOR identifier.*/
/*property_chain ::= identifier.*/
/*identifier ::= value.*/
/*identifier ::= STRING.*/
/*assignment ::= access ASSIGN expr. [ASSIGN]*/

//=================================
//Statement lists /  Arrays
//=================================
stmt_list(A) ::= stmt(B).
{
    A = B;

}

stmt_list(A) ::= stmt_list(B) stmt(C). [COMMA]
{
    A.type = panopticon::STATEMENT_LIST;
    if(B.type!=panopticon::STATEMENT_LIST)
    {
        panopticon::create_array(A);
        A.data.array->push_back(B);
        A.data.array->push_back(C);
    }
    else
    {
        A.data.array = B.data.array;
        A.data.array->push_back(C);
    }
    //A.n = B.n+1;
}
/*invoke ::= access LBRAC maybe_empty_stmt_list RBRAC.*/

/*access(A) ::= array(B).*/
/*{*/
/*    A=B;*/
/*}*/

value(A) ::= LBRAC maybe_empty_stmt_list(B) RBRAC.
{
    A.type = panopticon::ARRAY;
    A.data.array = B.data.array;
}

maybe_empty_stmt_list(A) ::= .
{
    A.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(A);
}

maybe_empty_stmt_list(A) ::= stmt_list(B).
{
    A.type = panopticon::STATEMENT_LIST;
    if(B.type!=panopticon::STATEMENT_LIST)
    {
        panopticon::create_array(A);
        A.data.array->push_back(B);
    }
    else
    {
        A.data.array = B.data.array;
    }
}

identifier(A) ::= value(B).
{
    A=B;

}

//=================================
//Convert to Dynamic Values
//=================================

value(A) ::= num(B).
{
    A=B;
}

value(A) ::= string(B).
{
    A=B;

}

value(A) ::= bool(B).
{
    A=B;
}


//======================
//BASICS
//======================
num(A) ::= NUM(B).
{
    A.data.number = B.data.number;
    A.type = panopticon::NUMBER;
    //A.n = B.n+1;
}

string(A) ::= STRING(B).
{
    A.data.string = new panopticon::String(B.data.string->c_str());
    delete B.data.string;
    A.type = panopticon::STRING;
    //A.n = B.n+1;
}


bool(A) ::= BOOLEAN(B).
{
    A.data.boolean = B.data.boolean;
    A.type = panopticon::BOOL;
    //A.n = B.n+1;
}

//=======================
//operators
//=======================
value(A) ::= value(B) PLUS value(C).
{
    plus(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) MINUS value(C).
{
    minus(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) DIVIDE value(C).
{
    divide(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) TIMES value(C).
{
    multiply(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) MODULO value(C).
{
    modulo(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) POW value(C).
{
    value_pow(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) EQUALTO value(C).
{
    equal_to(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) NOTEQUALTO value(C).
{
    not_equal_to(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) LESSTHAN value(C).
{
    less_than(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) GREATERTHAN value(C).
{
    greater_than(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) LORE value(C).
{
    lore(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) GORE value(C).
{
    gore(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) AND value(C).
{
    value_and(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) OR value(C).
{
    value_or(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= NOT value(B).
{
    not_value(A,B);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) SHIFTL value(C).
{
    shift_left(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) SHIFTR value(C).
{
    shift_right(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) BITAND value(C).
{
    bit_and(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

value(A) ::= value(B) BITOR value(C).
{
    bit_or(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

/*%fallback OPENBRAC LBRAC.*/

value(A) ::= variable(B) OPENBRAC num(C) RBRAC. [INDEX]
{
    index(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

stmt(A) ::= variable(B).
{
    A = B;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

variable(A) ::= NAME ASSIGN value(B).
{
    A = B;
    A.type = panopticon::VARIABLE;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}


//======================
//Syntax ERROR HANDLING
//=====================

in ::= error(B).
{
    switch(B)
    {
    case panopticon::OpenQuoteError:
/*        panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        panopticon::out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}

error(A) ::= OPENQUOTEERROR(B).
{
    B.type = panopticon::NUMBER;
    A = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
