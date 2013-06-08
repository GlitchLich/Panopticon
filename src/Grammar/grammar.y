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
#include "include/core/Trie.h"
#include "core/Memory.h"

#undef STRING
#undef NUM
#undef BOOL
#undef panopticon::ARRAY

/*using namespace panopticon;*/

    void token_destructor(Token t)
    {
/*        std::cout << "token_destructor()" << std::endl;*/
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
%left LCBLOCK RCBLOCK.
%left LCURL RCURL.
%left COLON BACKTICK.
%left DICT.
%left WHERE.
%left NAME.
%left COMMA.
%right BITOR.
%left FUNCTION_DEC.
%right RSTREAM.
%left LSTREAM.
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
%left COLONCOLON.
%left LPAREN RPAREN LBRAC RBRAC.
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
/*    std::cout << "Object of type: " << A.type << " hit the stack!" << std::endl;*/
/*    optic::out() << "Object at end of parser: ";*/
/*    print_object(A);*/
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

        B.type = optic::UNDECLARED_VARIABLE;
        C.type = optic::UNDECLARED_VARIABLE;

        A.data.array->push_back(B);
        A.data.array->push_back(C);
    }
    else
    {
        A = B;
        C.type = optic::UNDECLARED_VARIABLE;
        A.data.array->push_back(C);
    }
}

name_chain(A) ::= NAME(B).
{
    A = B;
    A.type = optic::UNDECLARED_VARIABLE;
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

expr(A) ::= expr(B) RSTREAM function_call(C).
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
        C.type = optic::UNDECLARED_VARIABLE;
        optic::store_operations(A,C,function_body,optic::call_function);
    }
}

expr(A) ::= expr(B) RSTREAM NAME(C).
{
    optic::object function_body = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);;
    function_body.data.array->push_back(B);
    optic::store_operations(A,C,function_body,optic::call_function);
}

expr(A) ::= function_call(C) LSTREAM expr(B).
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
        optic::store_operations(A,C,function_body,optic::call_function);
    }
}

expr(A) ::= NAME(C) LSTREAM expr(B).
{
    optic::object function_body = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);;
    function_body.data.array->push_back(B);
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
    optic::store_operations(A,B,C,optic::call_function);
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
guard_statement(A) ::= name_chain(B) LCBLOCK BITOR expr(C) ASSIGN expr(D) DELIMITER. [ASSIGN]
{
    optic::object tree = create_condition_tree(C,D);
    A = create_guard(B,tree);
}

//ERROR VERSION!
guard_statement ::= name_chain ASSIGN LCBLOCK BITOR expr ASSIGN expr DELIMITER. [ASSIGN]
{
    optic::out() << "Syntax Error: Cannot assign a guard statement to a function: get rid of the '='." << std::endl;
    optic::correct_parsing = false;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

guard_statement(A) ::= guard_statement(B) BITOR expr(C) ASSIGN expr(D) DELIMITER. [ASSIGN]
{
    add_branch_to_tree(B,C,D);
    A=B;
}

final_guard_statement(A) ::= guard_statement(B) BITOR expr(C) ASSIGN expr(D) RCBLOCK. [ASSIGN]
{
    add_branch_to_tree(B,C,D);
    A=B;
}

final_guard_statement(A) ::= guard_statement(B) BITOR WILDCARD ASSIGN expr(D) RCBLOCK. [ASSIGN]
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
    panopticon::store_operations(A, b, resolve, &panopticon::assign_variable,false);
    optic::shallow_mem_free_array(B.data.array,optic::GUARD);
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

//========================================================================================
//Anonymous Functions / Partial Application / Operator Sections / Infix binary functions
//========================================================================================

//sectioning

expr(A) ::= LPAREN expr(B) PLUS RPAREN.
{
    optic::left_section(A,B,optic::plus);
}

expr(A) ::= LPAREN PLUS expr(B) RPAREN.
{
    optic::right_section(A,B,optic::plus);
}

expr(A) ::= LPAREN expr(B) MINUS RPAREN.
{
    optic::left_section(A,B,optic::minus);
}

//Not possible with current syntax
/*expr(A) ::= LPAREN MINUS expr(B) RPAREN.*/
/*{*/
/*    optic::right_section(A,B,optic::minus);*/
/*}*/

expr(A) ::= LPAREN expr(B) TIMES RPAREN.
{
    optic::left_section(A,B,optic::multiply);
}

expr(A) ::= LPAREN TIMES expr(B) RPAREN.
{
    optic::right_section(A,B,optic::multiply);
}

expr(A) ::= LPAREN expr(B) DIVIDE RPAREN.
{
    optic::left_section(A,B,optic::divide);
}

expr(A) ::= LPAREN DIVIDE expr(B) RPAREN.
{
    optic::right_section(A,B,optic::divide);
}

expr(A) ::= LPAREN expr(B) MODULO RPAREN.
{
    optic::left_section(A,B,optic::modulo);
}

expr(A) ::= LPAREN MODULO expr(B) RPAREN.
{
    optic::right_section(A,B,optic::modulo);
}

expr(A) ::= LPAREN expr(B) POW RPAREN.
{
    optic::left_section(A,B,optic::value_pow);
}

expr(A) ::= LPAREN POW expr(B) RPAREN.
{
    optic::right_section(A,B,optic::value_pow);
}

expr(A) ::= LPAREN expr(B) EQUALTO RPAREN.
{
    optic::left_section(A,B,optic::equal_to);
}

expr(A) ::= LPAREN EQUALTO expr(B) RPAREN.
{
    optic::right_section(A,B,optic::equal_to);
}

expr(A) ::= LPAREN expr(B) NOTEQUALTO RPAREN.
{
    optic::left_section(A,B,optic::not_equal_to);
}

expr(A) ::= LPAREN NOTEQUALTO expr(B) RPAREN.
{
    optic::right_section(A,B,optic::not_equal_to);
}

expr(A) ::= LPAREN expr(B) LESSTHAN RPAREN.
{
    optic::left_section(A,B,optic::less_than);
}

expr(A) ::= LPAREN LESSTHAN expr(B) RPAREN.
{
    optic::right_section(A,B,optic::less_than);
}

expr(A) ::= LPAREN expr(B) GREATERTHAN RPAREN.
{
    optic::left_section(A,B,optic::greater_than);
}

expr(A) ::= LPAREN GREATERTHAN expr(B) RPAREN.
{
    optic::right_section(A,B,optic::greater_than);
}

expr(A) ::= LPAREN expr(B) LORE RPAREN.
{
    optic::left_section(A,B,optic::lore);
}

expr(A) ::= LPAREN LORE expr(B) RPAREN.
{
    optic::right_section(A,B,optic::lore);
}

expr(A) ::= LPAREN expr(B) GORE RPAREN.
{
    optic::left_section(A,B,optic::gore);
}

expr(A) ::= LPAREN GORE expr(B) RPAREN.
{
    optic::right_section(A,B,optic::gore);
}

expr(A) ::= LPAREN expr(B) AND RPAREN.
{
    optic::left_section(A,B,optic::value_and);
}

expr(A) ::= LPAREN AND expr(B) RPAREN.
{
    optic::right_section(A,B,optic::value_and);
}

expr(A) ::= LPAREN expr(B) OR RPAREN.
{
    optic::left_section(A,B,optic::value_or);
}

expr(A) ::= LPAREN OR expr(B) RPAREN.
{
    optic::right_section(A,B,optic::value_or);
}

expr(A) ::= LPAREN expr(B) SHIFTL RPAREN.
{
    optic::left_section(A,B,optic::shift_left);
}

expr(A) ::= LPAREN SHIFTL expr(B) RPAREN.
{
    optic::right_section(A,B,optic::shift_left);
}

expr(A) ::= LPAREN expr(B) SHIFTR RPAREN.
{
    optic::left_section(A,B,optic::shift_right);
}

expr(A) ::= LPAREN SHIFTR expr(B) RPAREN.
{
    optic::right_section(A,B,optic::shift_right);
}

expr(A) ::= LPAREN expr(B) BITAND RPAREN.
{
    optic::left_section(A,B,optic::bit_and);
}

expr(A) ::= LPAREN BITAND expr(B) RPAREN.
{
    optic::right_section(A,B,optic::bit_and);
}

expr(A) ::= LPAREN expr(B) BITOR RPAREN.
{
    optic::left_section(A,B,optic::bit_or);
}

expr(A) ::= LPAREN BITOR expr(B) RPAREN.
{
    optic::right_section(A,B,optic::bit_or);
}

expr(A) ::= LPAREN expr(B) BITXOR RPAREN.
{
    optic::left_section(A,B,optic::bit_xor);
}

expr(A) ::= LPAREN BITXOR expr(B) RPAREN.
{
    optic::right_section(A,B,optic::bit_xor);
}

expr(A) ::= LPAREN expr(B) PREPEND RPAREN.
{
    optic::left_section(A,B,optic::prepend,false);
}

expr(A) ::= LPAREN PREPEND expr(B) RPAREN.
{
    optic::right_section(A,B,optic::prepend,false);
}

expr(A) ::= LPAREN expr(B) APPEND RPAREN.
{
    optic::left_section(A,B,optic::append,false);
}

expr(A) ::= LPAREN APPEND expr(B) RPAREN.
{
    optic::right_section(A,B,optic::append,false);
}

expr(A) ::= LPAREN expr(B) PLUSPLUS RPAREN.
{
    optic::left_section(A,B,optic::concat,false);
}

expr(A) ::= LPAREN PLUSPLUS expr(B) RPAREN.
{
    optic::right_section(A,B,optic::concat,false);
}

//Infix function calls
expr(A) ::= expr(B) BACKTICK NAME(C) BACKTICK expr(D). [FUNCTION_CALL]
{

    optic::object args = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);
    args.data.array->push_back(B);
    args.data.array->push_back(D);
    optic::store_operations(A,C,args,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

//Infix function partial application
expr(A) ::= LPAREN BACKTICK NAME(C) BACKTICK expr(D) RPAREN. [FUNCTION_CALL]
{

    //Function name/arg
    optic::object name_array = mem_alloc(optic::ARRAY);
    optic::object name = optic::mem_alloc_variable("Anonymous");
    optic::object arg = optic::mem_alloc_variable("x");
    name_array.data.array->push_front(name);
    name_array.data.array->push_back(arg);

    //Store Function call
    optic::object body;
    optic::object args = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);
    optic::object var = optic::mem_alloc_variable("x");
    args.data.array->push_back(var);
    args.data.array->push_back(D);
    optic::store_operations(body,C,args,optic::call_function);

    insure_ready_for_assignment(name_array,body);
    store_operations(A,name_array,body,optic::create_function);

    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

/*assignment(A) ::= LPAREN NAME(B) stmt_list(C) RPAREN. [FUNCTION_CALL]
{
    store_operations(A,B,C,optic::partial_application);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}*/

expr(A) ::= LPAREN expr(B) BACKTICK NAME(C) BACKTICK RPAREN. [FUNCTION_CALL]
{

    //Function name/arg
    optic::object name_array = mem_alloc(optic::ARRAY);
    optic::object name = optic::mem_alloc_variable("Anonymous");
    optic::object arg = optic::mem_alloc_variable("x");
    name_array.data.array->push_front(name);
    name_array.data.array->push_back(arg);

    //Store Function call
    optic::object body;
    optic::object args = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);
    args.data.array->push_back(B);
    optic::object var = optic::mem_alloc_variable("x");
    args.data.array->push_back(var);
    optic::store_operations(body,C,args,optic::call_function);

    insure_ready_for_assignment(name_array,body);
    store_operations(A,name_array,body,optic::create_function);

    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

//Operator Functions
expr(A) ::= LPAREN PLUS RPAREN.
{
    optic::create_operator_function(A,optic::plus);
}

expr(A) ::= LPAREN MINUS RPAREN.
{
    optic::create_operator_function(A,optic::minus);
}

expr(A) ::= LPAREN TIMES RPAREN.
{
    optic::create_operator_function(A,optic::multiply);
}

expr(A) ::= LPAREN DIVIDE RPAREN.
{
    optic::create_operator_function(A,optic::divide);
}

expr(A) ::= LPAREN MODULO RPAREN.
{
    optic::create_operator_function(A,optic::modulo);
}

expr(A) ::= LPAREN POW RPAREN.
{
    optic::create_operator_function(A,optic::value_pow);
}

expr(A) ::= LPAREN EQUALTO RPAREN.
{
    optic::create_operator_function(A,optic::equal_to);
}

expr(A) ::= LPAREN NOTEQUALTO RPAREN.
{
    optic::create_operator_function(A,optic::not_equal_to);
}

expr(A) ::= LPAREN LESSTHAN RPAREN.
{
    optic::create_operator_function(A,optic::less_than);
}

expr(A) ::= LPAREN GREATERTHAN RPAREN.
{
    optic::create_operator_function(A,optic::greater_than);
}

expr(A) ::= LPAREN LORE RPAREN.
{
    optic::create_operator_function(A,optic::lore);
}

expr(A) ::= LPAREN GORE RPAREN.
{
    optic::create_operator_function(A,optic::gore);
}

expr(A) ::= LPAREN AND RPAREN.
{
    optic::create_operator_function(A,optic::value_and);
}

expr(A) ::= LPAREN OR RPAREN.
{
    optic::create_operator_function(A,optic::value_or);
}

expr(A) ::= LPAREN SHIFTL RPAREN.
{
    optic::create_operator_function(A,optic::shift_left);
}

expr(A) ::= LPAREN SHIFTR RPAREN.
{
    optic::create_operator_function(A,optic::shift_right);
}

expr(A) ::= LPAREN BITAND RPAREN.
{
    optic::create_operator_function(A,optic::bit_and);
}

expr(A) ::= LPAREN BITOR RPAREN.
{
    optic::create_operator_function(A,optic::bit_or);
}

expr(A) ::= LPAREN BITXOR RPAREN.
{
    optic::create_operator_function(A,optic::bit_xor);
}

expr(A) ::= LPAREN PREPEND RPAREN.
{
    optic::create_operator_function(A,optic::prepend);
}

expr(A) ::= LPAREN APPEND RPAREN.
{
    optic::create_operator_function(A,optic::append);
}

expr(A) ::= LPAREN PLUSPLUS RPAREN.
{
    optic::create_operator_function(A,optic::concat);
}

//Anonymous Functions
expr(A) ::= BACKSLASH name_chain(B) ASSIGN expr(C).
{
    if(B.type == optic::ARRAY)
    {
        optic::object name = optic::mem_alloc_variable("Anonymous");
        B.data.array->push_front(name);
        insure_ready_for_assignment(B,C);
        store_operations(A,B,C,optic::create_function);
    }
    else
    {
        optic::object name_array = mem_alloc(optic::ARRAY);
        optic::object name = optic::mem_alloc_variable("Anonymous");
        name_array.data.array->push_front(name);
        name_array.data.array->push_back(B);
        insure_ready_for_assignment(name_array,C);
        store_operations(A,name_array,C,optic::create_function);
    }
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

where(A) ::= WHERE LCBLOCK assignment_list(B) RCBLOCK. [DICT]
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
            panopticon::assign_variable
        );
        optic::store_operations(serial_result,previous_result,result);
        previous_result = serial_result;
    }
    optic::shallow_mem_free_array(B.data.array,optic::ARRAY);
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

assignment(A) ::= name_chain(B) ASSIGN expr(C) LCBLOCK where(D) RCBLOCK.
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

assignment(A) ::= guard_statement(B) BITOR expr(C) ASSIGN expr(D) DELIMITER where(E) RCBLOCK. [ASSIGN]
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

assignment(A) ::= guard_statement(B) BITOR WILDCARD ASSIGN expr(D) DELIMITER where(E) RCBLOCK. [ASSIGN]
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

dict(A) ::= LCURL DICT LCBLOCK assignment_list(B) RCBLOCK DELIMITER RCURL.
{
    A = B;
}

dict(A) ::= LCURL DICT LCBLOCK assignment_list(B) RCBLOCK RCURL.
{
    A = B;
}

dict(A) ::= LCURL assignment_list(B) RCURL.
{
    A = B;
}

dict(A) ::= LCURL LCBLOCK assignment_list(B) RCBLOCK DELIMITER RCURL.
{
    A = B;
}

dict(A) ::= LCURL LCBLOCK assignment_list(B) RCBLOCK RCURL.
{
    A = B;
}

expr(A) ::= dict(B).
{
    optic::object dict;
    optic::store_operations(dict,B,&optic::create_trie,false);

    optic::optic_stack.push_back(dict);
    optic::evaluate_top();
/*    A = optic::mem_copy(optic::optic_stack.back());*/
    A = optic::optic_stack.back();
    optic::optic_stack.pop_back();
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

//LOOKUP
expr(A) ::= NAME(B) LCURL NAME(C) RCURL.
{
    std::cout << "Namespace" << std::endl;
    store_operations(A,B,C,&optic::trie_lookup);
    if (!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

expr(A) ::= NAME(B) LCURL string(C) RCURL.
{
    std::cout << "Namespace" << std::endl;
    store_operations(A,B,C,&optic::trie_lookup);
    if (!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

name_space(A) ::= NAME(B) COLONCOLON NAME(C).
{
    std::cout << "Namespace" << std::endl;
    store_operations(A,B,C,&optic::trie_lookup);
    if (!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

name_space(A) ::= function_call(B) COLONCOLON NAME(C).
{
    store_operations(A,B,C,&optic::trie_lookup);
    if (!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

name_space(A) ::= name_space(B) COLONCOLON NAME(C).
{
    store_operations(A,B,C,&optic::trie_lookup);
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
            optic::store_operations(A,B,C,optic::call_function);
    }
    else
    {
        optic::object args = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);
        args.data.array->push_back(C);
        optic::store_operations(A,B,args,optic::call_function);
    }

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
            optic::store_operations(A,B,C,optic::call_function);
    }
    else
    {
        optic::object temp = optic::mem_alloc(optic::FUNCTION_ARG_VALUES);
        temp.data.array->push_back(C);
        optic::store_operations(A,B,temp,optic::call_function);
    }


    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

function_call(A) ::= name_space(B).
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

vertical_array(A) ::= LBRAC LCBLOCK final_vert_stmt_list(B) RCBLOCK RBRAC. [COLLECTARRAY]
{
    optic::object list;
    optic::convert_array_to_list(list,B);
    optic::create_tree(A,list);
}

array(A) ::= vertical_array(B).
{
    A = B;
}

array(A) ::= LBRAC maybe_empty_stmt_list(B) RBRAC. [COLLECTARRAY]
{
    optic::object list;
    optic::convert_array_to_list(list,B);
    optic::create_tree(A,list);
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
    A.data.array->push_back(B);
}
maybe_empty_name_chain(A) ::= pattern(B). [COLON]
{
    A = optic::mem_alloc(optic::ARRAY);
    A.data.array->push_back(B);
}

assignment(A) ::= name_chain(B) maybe_empty_name_chain ASSIGN expr. [COLON]
{
    optic::out() << "Pattern assignment" << std::endl;
    A = B;
}

assignment(A) ::= NAME(B) maybe_empty_name_chain ASSIGN expr. [COLON]
{
    optic::out() << "Pattern assignment" << std::endl;
    A = B;
}

pattern(A) ::= LPAREN NAME(B) PREPEND NAME(C) RPAREN. [COLON]
{
    std::cout << "PATTERN_ARGUMENT" << std::endl;
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
/*    B.type = optic::STRING;*/
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

//===================================================================
//Extended Array Operations
//===================================================================

//Array Slicing
//without step sizes...
//Beginning to ...
array_index(A) ::= NAME(B) LBRAC PREPEND expr(D) RBRAC. [INDEX]
{
    store_operations(A,B,D,optic::slice_beginning_to,false);
}

//... to End
array_index(A) ::= NAME(B) LBRAC expr(C) PREPEND RBRAC. [INDEX]
{
    store_operations(A,B,C,optic::slice_to_end,false);
}

//... to ...
array_index(A) ::= NAME(B) LBRAC expr(C) PREPEND expr(D) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice,false);
}

//WITH step sizes...

//All with steps
array_index(A) ::= NAME(B) LBRAC COLONCOLON expr(D) RBRAC. [INDEX]
{
    store_operations(A,B,D,optic::slice_all_with_step,false);
}

//Beginning to ...
array_index(A) ::= NAME(B) LBRAC expr(C) COLONCOLON expr(D) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_beginning_to_with_step,false);
}

//... to End
array_index(A) ::= NAME(B) LBRAC PREPEND expr(C) PREPEND expr(D) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_to_end_with_step,false);
}

//... to ...
array_index(A) ::= NAME(B) LBRAC expr(C) PREPEND expr(D) PREPEND expr(E) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    range.data.array->push_back(E);
    store_operations(A,B,range,optic::slice_with_step,false);
}

//WITH wrapping...
//Begin to ... with Wrapping
array_index(A) ::= NAME(B) LBRAC expr(C) PREPEND MODULO RBRAC. [INDEX]
{
    store_operations(A,B,C,optic::slice_beginning_to_wrapping,false);
}

// ... to End with Wrapping
array_index(A) ::= NAME(B) LBRAC PREPEND expr(C) PREPEND MODULO RBRAC. [INDEX]
{
    store_operations(A,B,C,optic::slice_to_end_wrapping,false);
}

//... to ... with Wrapping
array_index(A) ::= NAME(B) LBRAC expr(C) PREPEND expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_with_wrapping,false);
}

//Beginning to ... with Step with Wrapping
array_index(A) ::= NAME(B) LBRAC expr(C) COLONCOLON expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_beginning_to_with_step_wrapping,false);
}

// ... to End with Step with Wrapping
array_index(A) ::= NAME(B) LBRAC PREPEND expr(C) PREPEND expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_to_end_with_step_wrapping,false);
}

//... to ... with Step with Wrapping
array_index(A) ::= NAME(B) LBRAC expr(C) PREPEND expr(D) PREPEND expr(E) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    range.data.array->push_back(E);
    store_operations(A,B,range,optic::slice_with_step_wrapping,false);
}

//All with steps with wrapping
array_index(A) ::= NAME(B) LBRAC COLONCOLON expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    store_operations(A,B,D,optic::slice_all_with_step,false);
}

array_index(A) ::= name_space(B) LBRAC expr(C) RBRAC. [INDEX]
{
    optic::store_operations(A,B,C,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}

//=====
//REPEAT WITH ARRAY_INDEX
//=====
//Array Slicing
//without step sizes...
//Beginning to ...
array_index(A) ::= array_index(B) LBRAC PREPEND expr(D) RBRAC. [INDEX]
{
    store_operations(A,B,D,optic::slice_beginning_to,false);
}

//... to End
array_index(A) ::= array_index(B) LBRAC expr(C) PREPEND RBRAC. [INDEX]
{
    store_operations(A,B,C,optic::slice_to_end,false);
}

//... to ...
array_index(A) ::= array_index(B) LBRAC expr(C) PREPEND expr(D) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice,false);
}

//WITH step sizes...

//All with steps
array_index(A) ::= array_index(B) LBRAC COLONCOLON expr(D) RBRAC. [INDEX]
{
    store_operations(A,B,D,optic::slice_all_with_step,false);
}

//Beginning to ...
array_index(A) ::= array_index(B) LBRAC expr(C) COLONCOLON expr(D) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_beginning_to_with_step,false);
}

//... to End
array_index(A) ::= array_index(B) LBRAC PREPEND expr(C) PREPEND expr(D) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_to_end_with_step,false);
}

//... to ...
array_index(A) ::= array_index(B) LBRAC expr(C) PREPEND expr(D) PREPEND expr(E) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    range.data.array->push_back(E);
    store_operations(A,B,range,optic::slice_with_step,false);
}

//WITH wrapping...
//Begin to ... with Wrapping
array_index(A) ::= array_index(B) LBRAC expr(C) PREPEND MODULO RBRAC. [INDEX]
{
    store_operations(A,B,C,optic::slice_beginning_to_wrapping,false);
}

// ... to End with Wrapping
array_index(A) ::= array_index(B) LBRAC PREPEND expr(C) PREPEND MODULO RBRAC. [INDEX]
{
    store_operations(A,B,C,optic::slice_to_end_wrapping,false);
}

//... to ... with Wrapping
array_index(A) ::= array_index(B) LBRAC expr(C) PREPEND expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_with_wrapping,false);
}

//Beginning to ... with Step with Wrapping
array_index(A) ::= array_index(B) LBRAC expr(C) COLONCOLON expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_beginning_to_with_step_wrapping,false);
}

// ... to End with Step with Wrapping
array_index(A) ::= array_index(B) LBRAC PREPEND expr(C) PREPEND expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_to_end_with_step_wrapping,false);
}

//... to ... with Step with Wrapping
array_index(A) ::= array_index(B) LBRAC expr(C) PREPEND expr(D) PREPEND expr(E) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    range.data.array->push_back(E);
    store_operations(A,B,range,optic::slice_with_step_wrapping,false);
}

//All with steps with wrapping
array_index(A) ::= array_index(B) LBRAC COLONCOLON expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    store_operations(A,B,D,optic::slice_all_with_step,false);
}

//=====
//REPEAT WITH function_call
//=====
//Array Slicing
//without step sizes...
//Beginning to ...
array_index(A) ::= function_call(B) LBRAC PREPEND expr(D) RBRAC. [INDEX]
{
    store_operations(A,B,D,optic::slice_beginning_to,false);
}

//... to End
array_index(A) ::= function_call(B) LBRAC expr(C) PREPEND RBRAC. [INDEX]
{
    store_operations(A,B,C,optic::slice_to_end,false);
}

//... to ...
array_index(A) ::= function_call(B) LBRAC expr(C) PREPEND expr(D) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice,false);
}

//WITH step sizes...

//All with steps
array_index(A) ::= function_call(B) LBRAC COLONCOLON expr(D) RBRAC. [INDEX]
{
    store_operations(A,B,D,optic::slice_all_with_step,false);
}

//Beginning to ...
array_index(A) ::= function_call(B) LBRAC expr(C) COLONCOLON expr(D) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_beginning_to_with_step,false);
}

//... to End
array_index(A) ::= function_call(B) LBRAC PREPEND expr(C) PREPEND expr(D) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_to_end_with_step,false);
}

//... to ...
array_index(A) ::= function_call(B) LBRAC expr(C) PREPEND expr(D) PREPEND expr(E) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    range.data.array->push_back(E);
    store_operations(A,B,range,optic::slice_with_step,false);
}

//WITH wrapping...
//Begin to ... with Wrapping
array_index(A) ::= function_call(B) LBRAC expr(C) PREPEND MODULO RBRAC. [INDEX]
{
    store_operations(A,B,C,optic::slice_beginning_to_wrapping,false);
}

// ... to End with Wrapping
array_index(A) ::= function_call(B) LBRAC PREPEND expr(C) PREPEND MODULO RBRAC. [INDEX]
{
    store_operations(A,B,C,optic::slice_to_end_wrapping,false);
}

//... to ... with Wrapping
array_index(A) ::= function_call(B) LBRAC expr(C) PREPEND expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_with_wrapping,false);
}

//Beginning to ... with Step with Wrapping
array_index(A) ::= function_call(B) LBRAC expr(C) COLONCOLON expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_beginning_to_with_step_wrapping,false);
}

// ... to End with Step with Wrapping
array_index(A) ::= function_call(B) LBRAC PREPEND expr(C) PREPEND expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_to_end_with_step_wrapping,false);
}

//... to ... with Step with Wrapping
array_index(A) ::= function_call(B) LBRAC expr(C) PREPEND expr(D) PREPEND expr(E) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    range.data.array->push_back(E);
    store_operations(A,B,range,optic::slice_with_step_wrapping,false);
}

//All with steps with wrapping
array_index(A) ::= function_call(B) LBRAC COLONCOLON expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    store_operations(A,B,D,optic::slice_all_with_step,false);
}

//=====
//REPEAT WITH name_space
//=====
//Array Slicing
//without step sizes...
//Beginning to ...
array_index(A) ::= name_space(B) LBRAC PREPEND expr(D) RBRAC. [INDEX]
{
    store_operations(A,B,D,optic::slice_beginning_to,false);
}

//... to End
array_index(A) ::= name_space(B) LBRAC expr(C) PREPEND RBRAC. [INDEX]
{
    store_operations(A,B,C,optic::slice_to_end,false);
}

//... to ...
array_index(A) ::= name_space(B) LBRAC expr(C) PREPEND expr(D) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice,false);
}

//WITH step sizes...

//All with steps
array_index(A) ::= name_space(B) LBRAC COLONCOLON expr(D) RBRAC. [INDEX]
{
    store_operations(A,B,D,optic::slice_all_with_step,false);
}

//Beginning to ...
array_index(A) ::= name_space(B) LBRAC expr(C) COLONCOLON expr(D) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_beginning_to_with_step,false);
}

//... to End
array_index(A) ::= name_space(B) LBRAC PREPEND expr(C) PREPEND expr(D) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_to_end_with_step,false);
}

//... to ...
array_index(A) ::= name_space(B) LBRAC expr(C) PREPEND expr(D) PREPEND expr(E) RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    range.data.array->push_back(E);
    store_operations(A,B,range,optic::slice_with_step,false);
}

//WITH wrapping...
//Begin to ... with Wrapping
array_index(A) ::= name_space(B) LBRAC expr(C) PREPEND MODULO RBRAC. [INDEX]
{
    store_operations(A,B,C,optic::slice_beginning_to_wrapping,false);
}

// ... to End with Wrapping
array_index(A) ::= name_space(B) LBRAC PREPEND expr(C) PREPEND MODULO RBRAC. [INDEX]
{
    store_operations(A,B,C,optic::slice_to_end_wrapping,false);
}

//... to ... with Wrapping
array_index(A) ::= name_space(B) LBRAC expr(C) PREPEND expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_with_wrapping,false);
}

//Beginning to ... with Step with Wrapping
array_index(A) ::= name_space(B) LBRAC expr(C) COLONCOLON expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_beginning_to_with_step_wrapping,false);
}

// ... to End with Step with Wrapping
array_index(A) ::= name_space(B) LBRAC PREPEND expr(C) PREPEND expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    store_operations(A,B,range,optic::slice_to_end_with_step_wrapping,false);
}

//... to ... with Step with Wrapping
array_index(A) ::= name_space(B) LBRAC expr(C) PREPEND expr(D) PREPEND expr(E) PREPEND MODULO RBRAC. [INDEX]
{
    optic::object range = optic::mem_alloc(optic::ARRAY);
    range.data.array->push_back(C);
    range.data.array->push_back(D);
    range.data.array->push_back(E);
    store_operations(A,B,range,optic::slice_with_step_wrapping,false);
}

//All with steps with wrapping
array_index(A) ::= name_space(B) LBRAC COLONCOLON expr(D) PREPEND MODULO RBRAC. [INDEX]
{
    store_operations(A,B,D,optic::slice_all_with_step,false);
}

expr(A) ::= LBRAC expr(B) RANGE expr(C) RBRAC.
{
    store_operations(A,B,C,optic::range_from_to);
}

expr(A) ::= LBRAC expr(B) COMMA expr(C) RANGE expr(D) RBRAC.
{
    optic::object start_step = optic::mem_alloc(optic::ARRAY);
    start_step.data.array->push_back(B);
    start_step.data.array->push_back(C);
    store_operations(A,start_step,D,optic::range_from_step_to,false);
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
