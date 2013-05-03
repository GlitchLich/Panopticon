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
#include "../../include/core/heap.h"
#include "include/core/stack.h"

#undef STRING
#undef NUM
#undef BOOL
#undef panopticon::ARRAY

/*using namespace panopticon;*/

    void token_destructor(Token t)
    {
/*    panopticon::out() << "In token_destructor t.expr= " << t.expr << std::endl;*/
/*    panopticon::out() << "In token_destructor t.n= " << t.n << std::endl;*/
    }
}


%token_type {Token}
%default_type {Token}
%token_destructor { token_destructor($$); }

%type expr {Token}
%type id {Token}

//Precedence: Top is lowest, bottom is highest

%left ASSIGN.
%right BITOR.
%left FUNCTION_DEC.
%left INDEX.
%left OR.
%left AND.
%left BITXOR.
%left BITAND.
%left EQUALTO NOTEQUALTO.
%left GREATERTHAN GORE LESSTHAN LORE.
%left SHIFTL SHIFTR.
%left PLUS MINUS.
%left DIVIDE TIMES MODULO.
%right POW NOT BITNOT UMINUS PLUSPLUS.
%left LPAREN RPAREN COMMA LBRAC RBRAC.
%left COLLECTARRAY.



/*%left ASSIGN.*/


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
in ::= in test NEWLINE.


start ::= spec(A).
{
    if(
        A.type == optic::NUMBER ||
        A.type == optic::STRING ||
        A.type == optic::BOOL ||
        A.type == optic::GUARD
        )
    {
        print_object(A);
    }
    if( A.type == optic::CODE_BLOCK )
    {
        optic::out() << "CODE BLOCK!" << std::endl;
    }
    else
    {
        optic::resolve_stack_from_parser(A);
    }
}

spec(A) ::= closed_block(B).
{
    A = B;
    optic::out() << "CODE BLOCK!" << std::endl;
}

open_block(A) ::= OPENING_LPAREN spec(B).
{
    A = B;
}

open_block(A) ::= open_block NEWLINE spec.
{
    A.type = optic::CODE_BLOCK;
}

closed_block(A) ::= open_block CLOSING_RPAREN.
{
    A.type = optic::CODE_BLOCK;
}

spec(A) ::= assignment(B).
{
    A=B;
}

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

name_chain(A) ::= name_chain(B) NAME(C).
{
    if(B.type!=optic::ARRAY)
    {
        A.type = optic::ARRAY;
        A.data.array = new optic::Array();

        optic::object newObject1,newObject2;
        newObject1.type = optic::STRING;
        newObject2.type = optic::STRING;
        newObject1.data.string = new panopticon::String(B.data.string->c_str());
        newObject2.data.string = new panopticon::String(C.data.string->c_str());
        A.data.array->push_back(newObject1);
        A.data.array->push_back(newObject2);
    }
    else
    {
        A.type = optic::ARRAY;
        A.data.array = new optic::Array();
        A.data.array->reserve(B.data.array->size()+1);
        for(int i=0;i<B.data.array->size();++i)
        {
            optic::object newObject;
            newObject.type = optic::STRING;
            newObject.data.string = new optic::String(*B.data.array->at(i).data.string);
            A.data.array->push_back(newObject);
        }
        optic::object newObject2;
        newObject2.type = optic::STRING;
        newObject2.data.string = new panopticon::String(C.data.string->c_str());
        A.data.array->push_back(newObject2);
        //A.scope = optic::get_scope();
    }
    delete_object(B);
    delete_object(C);
}

name_chain(A) ::= NAME(B).
{
    A.data.string = new panopticon::String(B.data.string->c_str());
    delete B.data.string;
    A.type = panopticon::STRING;
}

expr(A) ::= NAME(B).
{
    B.type = optic::UNDECLARED_VARIABLE;
    A = B;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

/*expr(A) ::= function_call(B).
{
    A = B;
}*/

expr(A) ::= NAME(B) LPAREN stmt_list(C) RPAREN.
{
    if(C.type==optic::STATEMENT_LIST)
    {
            C.type = optic::ARRAY;
    }
    else
    {
        optic::object temp = C;
        C.type = optic::ARRAY;
        C.data.array = new optic::Array();
        C.data.array->reserve(1);
        C.data.array->push_back(temp);
    }
    optic::object b;
    b.type = optic::STRING;
    optic::out() << "FUNCTION_CALL B.data.string " << *B.data.string << "arguments: " << std::endl;
    print_object(C);

    b.data.string = new optic::String(B.data.string->c_str());
    optic::parse_operations(A,b,C,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= NAME(B) LPAREN RPAREN.
{
    optic::object C;
    C.type = optic::OPERATION_TREE;
    C.data.array = new optic::Array();
    optic::object b;
    b.type = optic::STRING;
    b.data.string = new optic::String(B.data.string->c_str());
    optic::parse_operations(A,b,C,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

test(A) ::= case_statement(B).
{
    A=B;
/*    panopticon::out() << "Case: " << *B.data.array->at(0).data.string << std::endl;*/
}

spec(A) ::= where_statement(B).
{
    panopticon::out() << "Where: " << std::endl;
    A=B;
}

test(A) ::= guard_assignment(B).
{
    A=B;
    A.type = optic::STRING;
    A.data.string = new optic::String("Guard");
}

guard_assignment ::= name_chain final_guard_statement.
guard_assignment ::= name_chain guard_statement.

guard_statement(A) ::= GUARD_N expr ASSIGN expr. [ASSIGN]
{
    A.type = optic::STRING;
    A.data.string = new optic::String("Guard");
}

guard_statement(A) ::= guard_statement(B) GUARD_N expr ASSIGN expr. [ASSIGN]
{
    A = B;
}

guard_statement ::= GUARD_S expr ASSIGN expr. [ASSIGN]
{

}

guard_statement(A) ::= guard_statement(B) GUARD_S expr ASSIGN expr. [ASSIGN]
{
    A = B;
}

final_guard_statement(A) ::= guard_statement(B) WILDCARD_N ASSIGN expr. [ASSIGN]
{
    A = B;
    A.type = optic::GUARD;
}

final_guard_statement(A) ::= guard_statement(B) WILDCARD ASSIGN expr. [ASSIGN]
{
    A = B;
    A.type = optic::GUARD;
}

where_statement ::= guard_statement WHERE.
where_statement ::= final_guard_statement WHERE.
where_statement ::= name_chain ASSIGN expr WHERE.

where_statement ::= where_statement NAME ASSIGN expr.

case_statement(A) ::= name_chain(B) ASSIGN CASE expr OF. [ASSIGN]
{
    A=B;
    A.type = optic::GUARD;
}

case_statement(A) ::= case_statement(B) N_TAB expr POINTER expr. [ASSIGN]
{
    A = B;
    A.type = optic::GUARD;
}

case_statement(A) ::= case_statement(B) WILDCARD_N POINTER expr. [ASSIGN]
{
    A = B;
    A.type = optic::GUARD;
}

expr(A) ::= LET NAME ASSIGN expr IN expr.
{
    A.type = optic::STRING;
    A.data.string = new optic::String("Let");
}

assignment(A) ::= name_chain(B) ASSIGN expr(C). [ASSIGN]
{
    insure_ready_for_assignment(B,C);

    panopticon::parse_operations(A, B, C, panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}


//=================================
//Statement lists /  Arrays
//=================================
stmt_list(A) ::= stmt(B).
{
    A = B;

}

stmt_list(A) ::= stmt_list(B) stmt(C). [COLLECTARRAY]
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

%fallback OPENBRAC LBRAC.

expr(A) ::= array(B).
{
    A = B;
}

array(A) ::= OPENBRAC maybe_empty_stmt_list(B) RBRAC. [COLLECTARRAY]
{
    create_tree(A,de_tree(B));
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

/*identifier(A) ::= expr(B).*/
/*{*/
/*    A=B;*/

/*}*/

//=================================
//Convert to Dynamic exprs
//=================================

expr(A) ::= num(B).
{
    create_tree(A,B);
}

expr(A) ::= string(B).
{
   create_tree(A,B);
}

expr(A) ::= bool(B).
{
    create_tree(A,B);
}

/*expr(A) ::= array(B).*/
/*{*/
/*    A=B;*/
/*}*/


//======================
//BASICS
//======================
expr(A) ::= PRINT LPAREN expr(B) RPAREN.
{
    optic::store_operations(A,B,&optic::unary_print_object);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

num(A) ::= NUM(B).
{
/*    A.data.number = B.data.number;*/
    B.type = panopticon::NUMBER;
    create_tree(A,B);
}

string(A) ::= STRING(B).
{
/*    A.data.string = new panopticon::String(B.data.string->c_str());*/
/*    delete B.data.string;*/
    B.type = panopticon::STRING;
    create_tree(A,B);
}


bool(A) ::= BOOLEAN(B).
{
/*    A.data.boolean = B.data.boolean;*/
    B.type = panopticon::BOOL;
    create_tree(A,B);
}

//=======================
//operators
//=======================
/*operator ::= PLUS.
operator ::= MINUS.
operator ::= DIVIDE.
operator ::= TIMES.
operator ::= MODULO.
operator ::= POW.
operator ::= EQUALTO.
operator ::= NOTEQUALTO.
operator ::= LESSTHAN.
operator ::= GREATERTHAN.
operator ::= LORE.
operator ::= GORE.
operator ::= AND.
operator ::= OR.
operator ::= NOT.
operator ::= BITNOT.
operator ::= BITAND.
operator ::= BITOR.
operator ::= SHIFTL.
operator ::= SHIFTR.
operator ::= BITXOR.*/

expr(A) ::= expr(B) PLUS expr(C).
{
    std::cout << "Plus B: " << B.type << std::endl;
    std::cout << "Plus C: " << C.type << std::endl;
    parse_operations(A,B,C,&panopticon::plus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) MINUS expr(C).
{
    parse_operations(A,B,C,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) DIVIDE expr(C).
{
    parse_operations(A,B,C,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) TIMES expr(C).
{
    parse_operations(A,B,C,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) MODULO expr(C).
{
    parse_operations(A,B,C,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) POW expr(C).
{
    parse_operations(A,B,C,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) EQUALTO expr(C).
{
    parse_operations(A,B,C,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) NOTEQUALTO expr(C).
{
    parse_operations(A,B,C,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) LESSTHAN expr(C).
{
    parse_operations(A,B,C,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) GREATERTHAN expr(C).
{
    parse_operations(A,B,C,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) LORE expr(C).
{
    parse_operations(A,B,C,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) GORE expr(C).
{
    parse_operations(A,B,C,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) AND expr(C).
{
    parse_operations(A,B,C,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) OR expr(C).
{
    parse_operations(A,B,C,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= BITNOT expr(B).
{
    bit_not(A,B);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= MINUS expr(B). [UMINUS]
{
    A = B;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= NOT expr(B). [UMINUS]
{
    A = B;
    not_value(A,B);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) SHIFTL expr(C).
{
    parse_operations(A,B,C,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) SHIFTR expr(C).
{
    parse_operations(A,B,C,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) BITAND expr(C).
{
    parse_operations(A,B,C,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

/*expr(A) ::= expr(B) BITOR expr(C).
{
    parse_operations(A,B,C,&panopticon::bit_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}*/

expr(A) ::= expr(B) BITXOR expr(C).
{
    parse_operations(A,B,C,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

/*
expr(A) ::= expr(B) array(C). [INDEX]
{
    index(A,B,C);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
*/

/*
stmt(A) ::= variable(B).
{
    A = B;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}*/

/*
variable(A) ::= NAME ASSIGN expr(B).
{
    A = B;
    A.type = panopticon::VARIABLE;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
*/


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
