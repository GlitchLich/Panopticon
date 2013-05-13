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
#include "core/Memory.h"

#undef STRING
#undef NUM
#undef BOOL
#undef panopticon::ARRAY

/*using namespace panopticon;*/

    void token_destructor(Token t)
    {
        std::cout << "token_destructor()" << std::endl;
        //TO DO: Do we need to free the tokens or not? I don't think so...
/*        mem_free(t);*/
    }
}


%token_type {Token}
%default_type {Token}
%token_destructor { token_destructor($$); }

%type expr {Token}
%type id {Token}

//Precedence: Top is lowest, bottom is highest

%left ASSIGN.
%left LCURL RCURL.
%left COLON.
%left DICT.
%left WHERE.
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
    std::cout << "Object of type: " << A.type << " hit the stack!" << std::endl;
    if(A.type!=optic::OPERATION_TREE)
    {
        optic::object a = mem_alloc(optic::OPERATION_TREE);
        a.data.array->push_back(A);
        optic::resolve_stack_from_parser(a, true);
    }
    else
    {
        optic::resolve_stack_from_parser(A, true);
/*        optic::resolve_stack_from_parser(flatten_tree(A), true);*/
    }
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

stmt(A) ::= expr(B).
{
    A = B;

}

name_chain(A) ::= name_chain(B) NAME(C).
{
    if(B.type!=optic::ARRAY)
    {
        A = optic::mem_alloc(optic::ARRAY);

        B.type = optic::STRING;
        C.type = optic::STRING;

        A.data.array->push_back(B);
        A.data.array->push_back(C);
    }
    else
    {
        /*A = optic::mem_alloc(optic::ARRAY);
        for(int i=0;i<B.data.array->size();++i)
        {
            optic::object newObject;
            newObject.type = optic::mem_alloc(optic::STRING);
            newObject.data.string = B.data.array->at(i).data.string;
            A.data.array->push_back(newObject);
        }*/

        A = B;
        C.type = optic::STRING;
        A.data.array->push_back(C);
    }

    // delete_object(B);
    // delete_object(C);
}

name_chain(A) ::= NAME(B).
{
    A = B;
    A.type = optic::STRING;
}

expr(A) ::= NAME(B).
{
    A = B;
    A.type = optic::UNDECLARED_VARIABLE;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) COMPOSITION function_call(C).
{
    if(C.type==optic::OPERATION_TREE)
    {
        C.data.array->at(2).data.array->push_front(B);
        A = C;
    }
    else
    {
        optic::object function_body = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);
        function_body.data.array->push_back(B);
        C.type = optic::STRING;
        optic::store_operations(A,C,function_body,optic::call_function);
    }
}

expr(A) ::= expr(B) COMPOSITION NAME(C).
{
    optic::object function_body = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);;
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
        C = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);
        C.data.array->push_back(temp);
    }
    optic::object b;
    b.type = optic::STRING;
    b.data.string = B.data.string;
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
        C = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);
        C.data.array->push_back(temp);
    }

    B.type = optic::VARIABLE;
    optic::store_operations(A,B,C,optic::call_function);
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
        C = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);
        C.data.array->push_back(temp);
    }
    optic::store_operations(A,B,C,optic::call_function);
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
    b.type = optic::FUNCTION_ARG_NAMES;
    panopticon::store_operations(A, b, resolve, &panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

assignment(A) ::= name_chain(B) ASSIGN expr(C). [ASSIGN]
{
    insure_ready_for_assignment(B,C);
    panopticon::store_operations(A, B, C, panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}


//==================
//Where
//==================
horizontal_assignment_list(A) ::= name_chain(B) ASSIGN expr(C).
{
    A = optic::mem_alloc(optic::ARRAY);
    A.data.array->push_back(B);
    A.data.array->push_back(C);
}

horizontal_assignment_list(A) ::= assignment_list(B) name_chain(C) ASSIGN expr(D).
{
    A = B;
    A.data.array->push_back(C);
    A.data.array->push_back(D);
}

vertical_assignment_list(A) ::= name_chain(B) ASSIGN expr(C) DELIMITER.
{
    A = optic::mem_alloc(optic::ARRAY);
    A.data.array->push_back(B);
    A.data.array->push_back(C);
}

vertical_assignment_list(A) ::= vertical_assignment_list(B) name_chain(C) ASSIGN expr(D) DELIMITER.
{
    A = B;
    A.data.array->push_back(C);
    A.data.array->push_back(D);
}

final_vertical_assignment_list(A) ::= vertical_assignment_list(B) name_chain(C) ASSIGN expr(D).
{
    A = B;
    A.data.array->push_back(C);
    A.data.array->push_back(D);
}

assignment_list(A) ::= vertical_assignment_list(B).
{
    A = B;
}

assignment_list(A) ::= final_vertical_assignment_list(B).
{
    A = B;
}

assignment_list(A) ::=  horizontal_assignment_list(B).
{
    A = B;
}

where(A) ::= WHERE LCURL assignment_list(B) RCURL. [DICT]
{
    A = B;
    optic::object serial_result;
    optic::object result;
    optic::object previous_result;
    for(int i=0;i<B.data.array->size(); i+=2)
    {
        insure_ready_for_assignment(
            B.data.array->at(i),
            B.data.array->at(i+1)
        );
        panopticon::store_operations(
            result,
            B.data.array->at(i),
            B.data.array->at(i+1),
            panopticon::assign_variable,
            false
        );
        optic::store_operations(serial_result,previous_result,result);
        previous_result = serial_result;
    }
    A = serial_result;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

assignment ::= name_chain ASSIGN expr expr.
{
    optic::out() << "Error: Cannot declare two statements in a single assignment." << std::endl;
    optic::correct_parsing = false;
    while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
    ParseARG_STORE;
}

assignment(A) ::= name_chain(B) ASSIGN expr(C) LCURL where(D) RCURL.
{
    panopticon::object body;
    panopticon::store_operations(body,D,C,false);
    insure_ready_for_assignment(B,body);
    panopticon::store_operations(A, B, body, panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

assignment(A) ::= guard_statement(B) BITOR expr(C) ASSIGN expr(D) DELIMITER where(E) RCURL. [ASSIGN]
{
    add_branch_to_tree(B,C,D);
    panopticon::object& b = B.data.array->at(0);
    panopticon::object& func_body = B.data.array->at(1);
    panopticon::object resolve;
    panopticon::store_operations(resolve, func_body, &panopticon::resolve_guard,false);

    panopticon::object combined;
    panopticon::store_operations(combined,E,resolve,false);
    insure_ready_for_assignment(B,combined);
    panopticon::store_operations(A, B, combined, panopticon::assign_variable);

    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

assignment(A) ::= guard_statement(B) WILDCARD ASSIGN expr(D) DELIMITER where(E) RCURL. [ASSIGN]
{
    add_wildcard_to_tree(B,D);
    panopticon::object& b = B.data.array->at(0);
    panopticon::object& func_body = B.data.array->at(1);
    panopticon::object resolve;
    panopticon::store_operations(resolve, func_body, &panopticon::resolve_guard,false);

    optic::object combined;
    panopticon::store_operations(combined,E,resolve,false);
    insure_ready_for_assignment(b,combined);
    panopticon::store_operations(A, b, combined, &panopticon::assign_variable);

    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

//====================================================================
//Case / Let / In
//====================================================================

case_statement(A) ::= CASE expr OF. [ASSIGN]
{
/*    A=B;*/
    A.type = optic::GUARD;
}

test ::= LET IN.

/*expr(A) ::= LET NAME ASSIGN expr IN expr.
{
    A.type = optic::STRING;
}*/

//===========================================
//Dictionaries
//===========================================

dict(A) ::= DICT LCURL assignment_list(B) RCURL.
{
    A = B;
}

dict(A) ::= LCURL DICT LCURL assignment_list(B) RCURL DELIMITER RCURL.
{
    A = B;
}

dict(A) ::= LCURL DICT LCURL assignment_list(B) RCURL RCURL.
{
    A = B;
}

dict(A) ::= LCURL assignment_list(B) RCURL.
{
    A = B;
}

dict(A) ::= LCURL LCURL assignment_list(B) RCURL DELIMITER RCURL.
{
    A = B;
}

dict(A) ::= LCURL LCURL assignment_list(B) RCURL RCURL.
{
    A = B;
}

expr(A) ::= dict(B).
{
    A = optic::mem_alloc(optic::DICTIONARY);
    for(int i=0;i<B.data.array->size()-1;i+=2)
    {
        if(
            B.data.array->at(i).type != optic::ARRAY
        )
        {
            A.data.dictionary->insert(
                std::make_pair(
                    *B.data.array->at(i).data.string,
                    B.data.array->at(i+1)
                    )
            );
        }
        else
        {
            insure_ready_for_assignment(B.data.array->at(i),B.data.array->at(i+1));
            //Leak???
            optic::object result;
            optic::create_function(result,B.data.array->at(i),B.data.array->at(i+1));
            A.data.dictionary->insert(
                std::make_pair(
                    *B.data.array->at(i).data.array->at(0).data.string,
                    result
                    )
            );
/*            optic::mem_free(B.data.array->at(i+1));*/
        }
/*        optic::mem_free(B.data.array->at(i));*/
    }

    optic::shallow_mem_free_array(B.data.array,"ARRAY");

    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

//LOOKUP
expr(A) ::= NAME(B) LCURL NAME(C) RCURL.
{
    store_operations(A,B,C,&optic::dictionary_lookup);
    if (!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= NAME(B) LCURL string(C) RCURL.
{
    store_operations(A,B,C,&optic::dictionary_lookup);
    if (!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

name_space(A) ::= NAME(B) COLONCOLON NAME(C). [INDEX]
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

name_space(A) ::= name_space(B) COLONCOLON NAME(C). [INDEX]
{
    C.type = optic::STRING;
    store_operations(A,B,C,&optic::dictionary_lookup);
    if (!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

function_call(A) ::= name_space(B) LPAREN stmt_list(C) RPAREN. [FUNCTION_CALL]
{
    if(C.type==optic::STATEMENT_LIST)
    {
            C.type = optic::FUNCTION_ARG_VALUES;
    }
    else
    {
        optic::object temp = C;
        C = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);
        C.data.array->push_back(temp);
    }
    optic::store_operations(A,B,C,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

//Call Array Functor []()
function_call(A) ::= name_space(B) LBRAC RBRAC LPAREN stmt_list(C) RPAREN. [FUNCTION_CALL]
{
    if(C.type==optic::STATEMENT_LIST)
    {
            C.type = optic::FUNCTION_ARG_VALUES;
    }
    else
    {
        optic::object temp = C;
        C = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);
        C.data.array->push_back(temp);
    }

    optic::store_operations(A,B,C,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= name_space(B).
{
    A = B;
}

//===========================================
//Statement lists /  Arrays
//===========================================
vert_stmt_list(A) ::= stmt(B) DELIMITER.
{
    A = B;
}

vert_stmt_list(A) ::= vert_stmt_list(B) stmt(C) DELIMITER. [COLLECTARRAY]
{
    A.type = panopticon::STATEMENT_LIST;
    if(B.type!=panopticon::STATEMENT_LIST)
    {
        A = optic::mem_alloc(optic::ARRAY);
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
        A = optic::mem_alloc(optic::STATEMENT_LIST);
        A.data.array->push_back(B);
        A.data.array->push_back(C);
    }
    else
    {
        A.data.array = B.data.array;
        A.data.array->push_back(C);
    }
}

vertical_array(A) ::= LBRAC LCURL final_vert_stmt_list(B) RCURL RBRAC. [COLLECTARRAY]
{
    A = B;
    A.type = optic::ARRAY;
}

array(A) ::= vertical_array(B).
{
    create_tree(A,B);
}

array(A) ::= LBRAC maybe_empty_stmt_list(B) RBRAC. [COLLECTARRAY]
{
    B.type = optic::ARRAY;
    create_tree(A,B);
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
        A = optic::mem_alloc(optic::STATEMENT_LIST);
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

maybe_empty_stmt_list(A) ::= .
{
    A = optic::mem_alloc(optic::STATEMENT_LIST);
}

maybe_empty_stmt_list(A) ::= stmt_list(B).
{
    A.type = panopticon::STATEMENT_LIST;
    if(B.type!=panopticon::STATEMENT_LIST)
    {
        A = optic::mem_alloc(optic::STATEMENT_LIST);
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
    A = B;
/*    create_tree(A,B);*/
}

expr(A) ::= string(B).
{
    A = B;
/*   create_tree(A,B);*/
}

expr(A) ::= bool(B).
{
    A = B;
/*    create_tree(A,B);*/
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
    A = optic::mem_alloc(optic::ARRAY);
    B.type = optic::STRING;
    A.data.array->push_back(B);
}
maybe_empty_name_chain(A) ::= pattern(B). [COLON]
{
    A = optic::mem_alloc(optic::ARRAY);
    A.data.array->push_back(B);
}

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
    store_operations(A,B,C,&panopticon::plus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) MINUS expr(C).
{
    store_operations(A,B,C,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) DIVIDE expr(C).
{
    store_operations(A,B,C,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) TIMES expr(C).
{
    store_operations(A,B,C,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) MODULO expr(C).
{
    store_operations(A,B,C,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) POW expr(C).
{
    store_operations(A,B,C,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) EQUALTO expr(C).
{
    store_operations(A,B,C,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) NOTEQUALTO expr(C).
{
    store_operations(A,B,C,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) LESSTHAN expr(C).
{
    store_operations(A,B,C,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) GREATERTHAN expr(C).
{
    store_operations(A,B,C,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) LORE expr(C).
{
    store_operations(A,B,C,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) GORE expr(C).
{
    store_operations(A,B,C,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) AND expr(C).
{
    store_operations(A,B,C,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) OR expr(C).
{
    store_operations(A,B,C,&panopticon::value_or);
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
    store_operations(A,B,C,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) SHIFTR expr(C).
{
    store_operations(A,B,C,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) BITAND expr(C).
{
    store_operations(A,B,C,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= expr(B) BITXOR expr(C).
{
    store_operations(A,B,C,&panopticon::bit_xor);
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
