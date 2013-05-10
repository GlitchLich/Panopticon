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
%left COLON.
%left NAME.
%right BITOR.
%left FUNCTION_DEC.
%right COMPOSITION.
%left FUNCTION_CALL.
%right PREPEND.
%left APPEND.
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
%left LPAREN RPAREN LBRAC RBRAC.
%left COMMA.
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
in ::= in DELIMITER.
in ::= in start DELIMITER.
in ::= in test DELIMITER.


start ::= spec(A).
{
    optic::resolve_stack_from_parser(A, true);
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
/*        A.data.array->reserve(B.data.array->size()+1);*/
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
    A.type = optic::UNDECLARED_VARIABLE;
    A.data.string = new optic::String(B.data.string->c_str());
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

expr(A) ::= expr(B) COMPOSITION function_call(C).
{
    if(C.type==optic::OPERATION_TREE)
    {
        C.data.array->at(2).data.array->push_front(B);
        A = C;
    }
    else
    {
        optic::object function_body;
        function_body.type = optic::FUNCTION_ARG_VALUES;
        function_body.data.array = new optic::Array();
        function_body.data.array->push_back(B);
        C.type = optic::STRING;
        optic::store_operations(A,C,function_body,optic::call_function);
    }
}

expr(A) ::= expr(B) COMPOSITION NAME(C).
{
    optic::object function_body;
    function_body.type = optic::FUNCTION_ARG_VALUES;
    function_body.data.array = new optic::Array();
    function_body.data.array->push_back(B);
    C.type = optic::STRING;
    optic::store_operations(A,C,function_body,optic::call_function);
}

function_call(A) ::= NAME(B) LPAREN stmt_list(C) RPAREN. [FUNCTION_CALL]
{
    if(C.type==optic::STATEMENT_LIST)
    {
            C.type = optic::FUNCTION_ARG_VALUES;
    }
    else
    {
        optic::object temp = C;
        C.type = optic::FUNCTION_ARG_VALUES;
        C.data.array = new optic::Array();
        C.data.array->push_back(temp);
    }
    optic::object b;
    b.type = optic::STRING;

    b.data.string = new optic::String(B.data.string->c_str());
    optic::store_operations(A,b,C,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

function_call(A) ::= NAME(B) LBRAC RBRAC LPAREN stmt_list(C) RPAREN. [FUNCTION_CALL]
{
    if(C.type==optic::STATEMENT_LIST)
    {
            C.type = optic::FUNCTION_ARG_VALUES;
    }
    else
    {
        optic::object temp = C;
        C.type = optic::FUNCTION_ARG_VALUES;
        C.data.array = new optic::Array();
        C.data.array->push_back(temp);
    }

    B.type = optic::VARIABLE;
    optic::parse_operations(A,B,C,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= array_index(B) LPAREN stmt_list(C) RPAREN. [FUNCTION_CALL]
{
    if(C.type==optic::STATEMENT_LIST)
    {
            C.type = optic::FUNCTION_ARG_VALUES;
    }
    else
    {
        optic::object temp = C;
        C.type = optic::FUNCTION_ARG_VALUES;
        C.data.array = new optic::Array();
        C.data.array->push_back(temp);
    }
    optic::parse_operations(A,B,C,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}


function_call(A) ::= NAME(B) LPAREN RPAREN. [FUNCTION_CALL]
{
    B.type = optic::UNDECLARED_VARIABLE;
    A = B;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

function_call(A) ::= array_index(B) LPAREN RPAREN. [FUNCTION_CALL]
{
    A = B;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= function_call(B).
{
    A = B;
}


test(A) ::= case_statement(B).
{
    A=B;
}

//GUARD STATEMENT BEGINNING
guard_statement(A) ::= name_chain(B) LCURL BITOR expr(C) ASSIGN expr(D) DELIMITER. [ASSIGN]
{
    optic::object tree = create_condition_tree(C,D);
    A = create_guard(B,tree);
}

guard_statement(A) ::= guard_statement(B) BITOR expr(C) ASSIGN expr(D) DELIMITER. [ASSIGN]
{
    add_branch_to_tree(B,C,D);
    A=B;
}

final_guard_statement(A) ::= guard_statement(B) BITOR expr(C) ASSIGN expr(D) RCURL. [ASSIGN]
{
    add_branch_to_tree(B,C,D);
    A=B;
}

final_guard_statement(A) ::= guard_statement(B) WILDCARD ASSIGN expr(D) RCURL. [ASSIGN]
{
    add_wildcard_to_tree(B,D);
    A=B;
}

assignment(A) ::= final_guard_statement(B).
{
    panopticon::object& b = B.data.array->at(0);
    panopticon::object& c = B.data.array->at(1);

    panopticon::object resolve;
    panopticon::store_operations(resolve, c, &panopticon::resolve_guard,false);

    resolve.type = panopticon::FUNCTION_BODY;
/*    insure_ready_for_assignment(b,resolve);*/
    b.type = optic::FUNCTION_ARG_NAMES;
    panopticon::parse_operations(A, b, resolve, &panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

assignment(A) ::= guard_statement(B) BITOR expr(C) ASSIGN expr(D) DELIMITER final_where_statement(E). [ASSIGN]
{
    add_branch_to_tree(B,C,D);
    panopticon::object& b = B.data.array->at(0);
    panopticon::object& func_body = B.data.array->at(1);
    panopticon::object resolve;
    panopticon::store_operations(resolve, func_body, &panopticon::resolve_guard,false);
    optic::object combined;
    panopticon::store_operations(combined,E,resolve,false);
    insure_ready_for_assignment(b,combined);
    panopticon::parse_operations(A, b, combined, &panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

assignment(A) ::= guard_statement(B) WILDCARD ASSIGN expr(D) DELIMITER final_where_statement(E). [ASSIGN]
{
    add_wildcard_to_tree(B,D);
    panopticon::object& b = B.data.array->at(0);
    panopticon::object& func_body = B.data.array->at(1);
    panopticon::object resolve;
    panopticon::store_operations(resolve, func_body, &panopticon::resolve_guard,false);
    optic::object combined;
    panopticon::store_operations(combined,E,resolve,false);
    insure_ready_for_assignment(b,combined);
    panopticon::parse_operations(A, b, combined, &panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

//==================
//Where
//==================

where_statement(A) ::= WHERE LCURL. [ASSIGN]
{
    A.type = optic::NIL;
}

where_statement(A) ::= WHERE name_chain(B) ASSIGN expr(C) LCURL. [ASSIGN]
{
    insure_ready_for_assignment(B,C);
    B.type = optic::FUNCTION_ARG_NAMES;
    panopticon::store_operations(A, B, C, panopticon::assign_variable,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

where_statement(A) ::= where_statement(D) name_chain(B) ASSIGN expr(C) DELIMITER. [ASSIGN]
{
    insure_ready_for_assignment(B,C);
    B.type = optic::FUNCTION_ARG_NAMES;

    if(D.type!=optic::NIL)
    {
        optic::object assign;
        panopticon::store_operations(assign, B, C, panopticon::assign_variable,false);
        optic::store_operations(A,D,assign);
    }
    else
    {
        panopticon::parse_operations(A, B, C, panopticon::assign_variable);
    }
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

final_where_statement(A) ::= where_statement(D) name_chain(B) ASSIGN expr(C) RCURL DELIMITER RCURL. [ASSIGN]
{
    insure_ready_for_assignment(B,C);
    B.type = optic::FUNCTION_ARG_NAMES;
    if(D.type!=optic::NIL)
    {
        optic::object assign;
        panopticon::store_operations(assign, B, C, panopticon::assign_variable,false);
        optic::store_operations(A,D,assign);
    }
    else
    {
        panopticon::store_operations(A, B, C, panopticon::assign_variable,false);
    }
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

case_statement(A) ::= name_chain(B) ASSIGN CASE expr OF. [ASSIGN]
{
    A=B;
    A.type = optic::GUARD;
}

test ::= LET IN.

/*expr(A) ::= LET NAME ASSIGN expr IN expr.
{
    A.type = optic::STRING;
    A.data.string = new optic::String("Let");
}*/

assignment(A) ::= name_chain(B) ASSIGN expr(C). [ASSIGN]
{
    insure_ready_for_assignment(B,C);
    B.type = optic::FUNCTION_ARG_NAMES;
    panopticon::parse_operations(A, B, C, panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

//Assignment with where
assignment(A) ::= name_chain(B) ASSIGN expr(C) LCURL final_where_statement(D). [ASSIGN]
{
    panopticon::object body;
    panopticon::store_operations(body,D,C,false);
    insure_ready_for_assignment(B,body);
    panopticon::parse_operations(A, B, body, panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}


//===========================================
//Statement lists /  Arrays / Dictionaries
//===========================================

dict_argument_list(A) ::= NAME(B) ASSIGN expr(C). [COLLECTARRAY]
{
    A.type = optic::ARRAY;
    A.data.array = new optic::Array();
    A.data.array->push_back(B);
    A.data.array->push_back(C);
}

dict_argument_list(A) ::= dict_argument_list(B) NAME(C) ASSIGN expr(D). [COLLECTARRAY]
{
    A = B;
    A.data.array->push_back(C);
    A.data.array->push_back(D);
}

vertical_dict_list(A) ::= NAME(B) ASSIGN expr(C) DELIMITER. [COLLECTARRAY]
{
    A.type = optic::ARRAY;
    A.data.array = new optic::Array();
    A.data.array->push_back(B);
    A.data.array->push_back(C);
}

vertical_dict_list(A) ::= vertical_dict_list(B) NAME(C) ASSIGN expr(D) DELIMITER. [COLLECTARRAY]
{
    A = B;
    A.data.array->push_back(C);
    A.data.array->push_back(D);
}

final_vertical_dict_list(A) ::= vertical_dict_list(B) NAME(C) ASSIGN expr(D). [COLLECTARRAY]
{
    A = B;
    A.data.array->push_back(C);
    A.data.array->push_back(D);
}


expr(A) ::= dictionary(B).
{
    A.type = optic::DICTIONARY;
    A.data.dictionary = new optic::Dictionary();
    for(int i=0;i<B.data.array->size()-1;i+=2)
    {
        A.data.dictionary->insert(
            std::make_pair(*B.data.array->at(i).data.string,B.data.array->at(i+1))
        );
    }
}

dictionary(A) ::= LCURL LCURL final_vertical_dict_list(B) RCURL DELIMITER RCURL.
{
    A = B;
}

dictionary(A) ::= LCURL final_vertical_dict_list(B) RCURL.
{
    A = B;
}

dictionary(A) ::= LCURL dict_argument_list(B) RCURL.
{
    A = B;
}

expr(A) ::= NAME(B) LCURL STRING(C) RCURL. [INDEX]
{
    B.type = optic::UNDECLARED_VARIABLE;
    C.type = optic::STRING;
    store_operations(A,B,C,&optic::dictionary_lookup);
    if (!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= NAME(B) COLONCOLON NAME(C). [INDEX]
{
    B.type = optic::UNDECLARED_VARIABLE;
    C.type = optic::STRING;
    store_operations(A,B,C,&optic::dictionary_lookup);
    if (!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}


vert_stmt_list(A) ::= stmt(B) DELIMITER.
{
    A = B;
}

vert_stmt_list(A) ::= vert_stmt_list(B) stmt(C) DELIMITER. [COLLECTARRAY]
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
}

final_vert_stmt_list(A) ::= vert_stmt_list(B) stmt(C). [COLLECTARRAY]
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
}



vertical_array(A) ::= LBRAC LCURL final_vert_stmt_list(B) RCURL DELIMITER RBRAC. [COLLECTARRAY]
{
    A = B;
    A.type = optic::ARRAY;
}

array(A) ::= vertical_array(B).
{
    A = B;
}

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
}

expr(A) ::= array(B).
{
    A = B;
}

array(A) ::= LBRAC maybe_empty_stmt_list(B) RBRAC. [COLLECTARRAY]
{
    A = B;
    A.type = optic::ARRAY;
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


//======================
//BASICS
//======================
expr(A) ::= PRINT LPAREN expr(B) RPAREN.
{
    optic::store_operations(A,B,&optic::unary_print_object,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= LPAREN expr(B) RPAREN.
{
    A = B;
}

num(A) ::= NUM(B).
{
    B.type = panopticon::NUMBER;
    create_tree(A,B);
}

string(A) ::= STRING(B).
{
    B.type = panopticon::STRING;
    create_tree(A,B);
}


bool(A) ::= BOOLEAN(B).
{
    B.type = panopticon::BOOL;
    create_tree(A,B);
}

//=======================
//operators
//=======================

/*maybe_empty_name_chain ::= .*/
maybe_empty_name_chain(A) ::= name_chain(B). [COLON]
{
    A.type = optic::ARRAY;
    A.data.array = new optic::Array();
    B.type = optic::STRING;
    A.data.array->push_back(B);
}
maybe_empty_name_chain(A) ::= pattern(B). [COLON]
{
    A.type = optic::ARRAY;
    A.data.array = new optic::Array();
    A.data.array->push_back(B);
}

/*maybe_empty_name_chain(A) ::= maybe_empty_name_chain(B) name_chain(C). [COLON]
{

}

maybe_empty_name_chain(A) ::= maybe_empty_name_chain(B) pattern(C). [COLON]
{

}*/

assignment(A) ::= name_chain(B) maybe_empty_name_chain ASSIGN expr. [COLON]
{
    A = B;
}

assignment(A) ::= NAME(B) maybe_empty_name_chain ASSIGN expr. [COLON]
{
    A = B;
}

pattern(A) ::= LPAREN NAME(B) PREPEND NAME(C) RPAREN. [COLON]
{
/*    std::cout << "PATTERN_ARGUMENT" << std::endl;*/
    B.type = optic::PATTERN;
    C.type = optic::PATTERN;
    A.type = optic::PATTERN;
    A.data.string = new optic::String("PATTERN ARGUMENT!");
}

expr(A) ::= expr(B) PREPEND expr(C).
{
    optic::store_operations(A,B,C,&optic::prepend,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) APPEND expr(C).
{
    optic::store_operations(A,B,C,&optic::append,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) PLUSPLUS expr(C). [APPEND]
{
    optic::store_operations(A,B,C,&optic::concat,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) PLUS expr(C).
{
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
    store_operations(A,B,&optic::bit_not);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= LPAREN MINUS expr(B) RPAREN. [UMINUS]
{
    store_operations(A,B,&panopticon::u_minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= NOT expr(B). [UMINUS]
{
    store_operations(A,B,&panopticon::not_value);
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

expr(A) ::= expr(B) BITXOR expr(C).
{
    parse_operations(A,B,C,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

array_index(A) ::= function_call(B) LBRAC expr(C) RBRAC. [INDEX]
{
    optic::store_operations(A,B,C,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

array_index(A) ::= NAME(B) LBRAC expr(C) RBRAC. [INDEX]
{
    B.type = optic::STRING;
    optic::store_operations(A,B,C,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

array_index(A) ::= array_index(B) LBRAC expr(C) RBRAC. [INDEX]
{
    optic::store_operations(A,B,C,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= array_index(B). [INDEX]
{
    A = B;
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
