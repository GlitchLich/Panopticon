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

#undef STRING
#undef NUM
#undef BOOL
#undef ARRAY

using namespace panopticon;

    void token_destructor(Token t)
    {
/*    out() << "In token_destructor t.value= " << t.value << std::endl;*/
/*    out() << "In token_destructor t.n= " << t.n << std::endl;*/
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
out() << "Syntax error!" << std::endl;
}

main ::= in.
in ::= .
in ::= in NEWLINE.
in ::= in start NEWLINE.

/*state ::= expr(A).   {*/
/*    out() << "Result.value=" << A.value << std::endl;*/
/*    out() << "Result.n=" << A.n << std::endl;*/
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
    if(B.type!=STATEMENT_LIST)
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

access(A) ::= array(B).
{
    A=B;
}

array(A) ::= LBRAC maybe_empty_stmt_list(B) RBRAC.
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
    if(B.type!=STATEMENT_LIST)
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

/*num(A) ::= value(B).
{
    A=B;
}

string(A) ::= value(B).
{
    A=B;

}

bool(A) ::= value(B).
{
    A=B;
}*/

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
    A.data.string = new String(B.data.string->c_str());
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

//=====================================================================
//OPERATORS, STRING_NUMBER / NUMBER_STRING / STRING_BOOL / BOOL_STRING
//=====================================================================

string(A) ::= string(B) PLUS num(C).
{
        A.type = panopticon::STRING;
        panopticon::string_plus_num(A,B,C);
        //A.n = B.n+1  + C.n+1;
}

string(A) ::= string(B) PLUSPLUS num(C).
{
        A.type = panopticon::STRING;
        panopticon::string_plusplus_num(A,B,C);
        //A.n = B.n+1  + C.n+1;
}

string(A) ::= num(B) PLUS string(C).
{
        A.type = panopticon::STRING;
        panopticon::num_plus_string(A,B,C);
        //A.n = B.n+1  + C.n+1;
}

string(A) ::= num(B) PLUSPLUS string(C).
{
        A.type = panopticon::STRING;
        panopticon::num_plusplus_string(A,B,C);
        //A.n = B.n+1  + C.n+1;
}

string(A) ::= string(B) PLUS bool(C).
{
        A.type = panopticon::STRING;
        panopticon::string_plus_bool(A,B,C);
        //A.n = B.n+1  + C.n+1;
}

string(A) ::= string(B) PLUSPLUS bool(C).
{
        A.type = panopticon::STRING;
        panopticon::string_plusplus_bool(A,B,C);
        //A.n = B.n+1  + C.n+1;
}

string(A) ::= bool(B) PLUS string(C).
{
        A.type = panopticon::STRING;
        panopticon::bool_plus_string(A,B,C);
        //A.n = B.n+1  + C.n+1;
}

string(A) ::= bool(B) PLUSPLUS string(C).
{
        A.type = panopticon::STRING;
        panopticon::bool_plusplus_string(A,B,C);
        //A.n = B.n+1  + C.n+1;
}

//===========================
//OPERATORS, BOOLEAN_BOOLEAN
//===========================
bool(A) ::= LPAREN bool(B) RPAREN.
{
    A.type = panopticon::BOOL;
    A.data.boolean = B.data.boolean;
    //A.n = B.n+1;
}

bool(A) ::= bool(B) PLUS bool(C).
{
    A.type = panopticon::BOOL;
    if(B.data.boolean || C.data.boolean)
    {
        A.data.boolean = true;
    }
    else
    {
        A.data.boolean = false;
    }
    //A.n = B.n+1  + C.n+1;
}

bool(A) ::= bool(B) TIMES bool(C).
{
    A.type = panopticon::BOOL;
    if(B.data.boolean && C.data.boolean)
    {
        A.data.boolean = true;
    }
    else
    {
        A.data.boolean = false;
    }
    //A.n = B.n+1  + C.n+1;
}

bool(A) ::= bool(B) EQUALTO bool(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = B.data.boolean == C.data.boolean;
    //A.n = B.n+1+C.n+1;
}

bool(A) ::= bool(B) NOTEQUALTO bool(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = B.data.number != C.data.number;
    //A.n = B.n+1+C.n+1;
}

bool(A) ::= bool(B) AND bool(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = (int)B.data.boolean && (int)C.data.boolean;
    //A.n = B.n+1+C.n+1;
}

bool(A) ::= bool(B) OR bool(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = (int)B.data.boolean || (int)C.data.boolean;
    //A.n = B.n+1+C.n+1;
}

bool(A) ::= NOT bool(B).
{
    A.type = panopticon::BOOL;
    A.data.boolean = !((int)B.data.boolean);
    //A.n = B.n+1;
}
/*
bool(A) ::= bool(B) MINUS bool(C).
{
    A.type = panopticon::BOOL;
    if(B.data.boolean || C.data.boolean)
    {
        A.data.boolean = true;
    }
    else
    {
        A.data.boolean = false;
    }
    //A.n = B.n+1  + C.n+1;
}

error(A) ::= bool(B) LESSTHAN bool(C).
{
    B.type = panopticon::BOOL;
    C.type = panopticon::BOOL;
    A = IncorrectBooleanComparisonLesser;
    out() << "Error p0005: Cannot ask if one boolean is lesser than another." << std::endl;
}

error(A) ::= bool(B) GREATERTHAN bool(C).
{
    B.type = panopticon::BOOL;
    C.type = panopticon::BOOL;
    A = IncorrectBooleanComparisonGreater;
    out() << "Error p0004: Cannot ask if one boolean is greater than another." << std::endl;
}

error(A) ::= bool(B) GORE bool(C).
{
    B.type = panopticon::BOOL;
    C.type = panopticon::BOOL;
    A = IncorrectBooleanComparisonGORE;
    out() << "Error p0006: Cannot ask if one boolean is greater than or equal to another boolean. " << std::endl;
}

error(A) ::= bool(B) LORE bool(C).
{
    B.type = panopticon::BOOL;
    C.type = panopticon::BOOL;
    A = IncorrectBooleanComparisonLORE;
    out() << "Error p0007: Cannot ask if one boolean is less than or greater to another boolean." << std::endl;
}
*/

//FIX POINTERS!

/*expr(A) ::= LPAREN expr(B) RPAREN.*/
/*{*/
/*    A.type = panopticon::B.type;*/
/*    A.data.number = B.data.number;*/
/*    //A.n = B.n+1;*/
/*}*/

//=====================================
//OPERATORS, STRING_STRING
//=====================================
string(A) ::= LPAREN string(B) RPAREN.
{
    A.data.string = B.data.string;
    A.type = panopticon::STRING;
    //A.n = B.n+1;
}

string(A) ::= string(B) MINUS string(C).
{
    panopticon::string_minus_string(A,B,C);
    A.type = panopticon::STRING;
    //A.n = B.n+1  + C.n+1;
}

string(A) ::= string(B) PLUS string(C).
{
    panopticon::string_plus_string(A,B,C);
    A.type = panopticon::STRING;
    //A.n = B.n+1  + C.n+1;
}

string(A) ::= string(B) PLUSPLUS string(C).
{
    panopticon::string_plusplus_string(A,B,C);
    A.type = panopticon::STRING;
    //A.n = B.n+1  + C.n+1;
}

num(A) ::= string(B) TIMES string(C).
{
    if(is_number(*B.data.string) && is_number(*C.data.string))
    {
        A.type = panopticon::NUMBER;
        A.data.number = string_to_double(*B.data.string) * string_to_double(*C.data.string);
    }
    else
    {
/*        A = panopticon::MulStringError;*/
        out() << "Error p0002: Attempted to Multiply a string by a string, and at least one is non-numerical: " << std::endl;
        out() << "String 1: " << *B.data.string << std::endl;
        out() << "String 2: " << *C.data.string << std::endl;
    }
}

bool(A) ::= string(B) EQUALTO string(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = B.data.string->compare(*C.data.string)==0;
    //A.n = B.n+1+C.n+1;
}

num(A) ::= string(B) DIVIDE string(C).
{
    if(is_number(*B.data.string) && is_number(*C.data.string))
    {
        A.type = panopticon::NUMBER;
        A.data.number = string_to_double(*B.data.string) / string_to_double(*C.data.string);
    }
    else
    {
        A.type = panopticon::ERROR;
        A.data.number = 0;
/*        A = panopticon::MulStringError;*/
        out() << "Error p0002: Attempted to Multiply a string by a string, and at least one is non-numerical: " << std::endl;
        out() << "String 1: " << *B.data.string << std::endl;
        out() << "String 2: " << *C.data.string << std::endl;
    }
}

bool(A) ::= string(B) LESSTHAN string(C).
{
    if(is_number(*B.data.string) && is_number(*C.data.string))
    {
        A.type = panopticon::BOOL;
        A.data.boolean = string_to_double(*B.data.string) < string_to_double(*C.data.string);
        //A.n = B.n+1+C.n+1;
    }
    else
    {
        A.type = panopticon::BOOL;
        A.data.boolean = B.data.string->size() < C.data.string->size();
        //A.n = B.n+1+C.n+1;
    }
}

bool(A) ::= string(B) GREATERTHAN string(C).
{
    if(is_number(*B.data.string) && is_number(*C.data.string))
    {
        A.type = panopticon::BOOL;
        A.data.boolean = string_to_double(*B.data.string) > string_to_double(*C.data.string);
        //A.n = B.n+1+C.n+1;
    }
    else
    {
        A.type = panopticon::BOOL;
        A.data.boolean = B.data.string->size() > C.data.string->size();
        //A.n = B.n+1+C.n+1;
    }
}

bool(A) ::= string(B) NOTEQUALTO string(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = B.data.string->compare(*C.data.string)!=0;
    //A.n = B.n+1+C.n+1;
}


bool(A) ::= string(B) GORE string(C).
{
    if(is_number(*B.data.string) && is_number(*C.data.string))
    {
        A.type = panopticon::BOOL;
        A.data.boolean = string_to_double(*B.data.string) >= string_to_double(*C.data.string);
        //A.n = B.n+1+C.n+1;
    }
    else
    {
        A.type = panopticon::BOOL;
        A.data.boolean = B.data.string->size() > C.data.string->size();
        //A.n = B.n+1+C.n+1;
    }
}

bool(A) ::= string(B) LORE string(C).
{
    if(is_number(*B.data.string) && is_number(*C.data.string))
    {
        A.type = panopticon::BOOL;
        A.data.boolean = string_to_double(*B.data.string) <= string_to_double(*C.data.string);
        //A.n = B.n+1+C.n+1;
    }
    else
    {
        A.type = panopticon::BOOL;
        A.data.boolean = B.data.string->size() > C.data.string->size();
        //A.n = B.n+1+C.n+1;
    }
}

//======================
//OPERATORS, NUMBER_NUMBER
//======================
num(A) ::= LPAREN num(B) RPAREN.
{
    A.type = panopticon::NUMBER;
    A.data.number = B.data.number;
    //A.n = B.n+1;
}

num(A) ::= num(B) MINUS num(C).
{
    A.type = panopticon::NUMBER;
    A.data.number = B.data.number - C.data.number;
    //A.n = B.n+1  + C.n+1;
}

num(A) ::= num(B) PLUS  num(C).
{
    A.type = panopticon::NUMBER;
    A.data.number = B.data.number + C.data.number;
    //A.n = B.n+1  + C.n+1;
}

num(A) ::= num(B) TIMES num(C).
{
    A.type = panopticon::NUMBER;
    A.data.number = B.data.number * C.data.number;
    //A.n = B.n+1  + C.n+1;
}

num(A) ::= num(B) DIVIDE num(C).
{
    A.type = panopticon::NUMBER;
    if(C.data.number != 0)
    {
         A.data.number = B.data.number / C.data.number;
/*         A.n = B.n+1 + C.n+1;*/
    }
    else
    {
         out() << "divide by zero" << std::endl;
    }
}

bool(A) ::= num(B) LESSTHAN num(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = B.data.number < C.data.number;
    //A.n = B.n+1+C.n+1;
}

bool(A) ::= num(B) GREATERTHAN num(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = B.data.number > C.data.number;
    //A.n = B.n+1+C.n+1;
}

bool(A) ::= num(B) EQUALTO num(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = B.data.number == C.data.number;
    //A.n = B.n+1+C.n+1;
}

bool(A) ::= num(B) NOTEQUALTO num(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = B.data.number != C.data.number;
    //A.n = B.n+1+C.n+1;
}

bool(A) ::= num(B) GORE num(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = B.data.number >= C.data.number;
    //A.n = B.n+1+C.n+1;
}

bool(A) ::= num(B) LORE num(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = B.data.number <= C.data.number;
    //A.n = B.n+1+C.n+1;
}

bool(A) ::= num(B) AND num(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = (int)B.data.number && (int)C.data.number;
    //A.n = B.n+1+C.n+1;
}

bool(A) ::= num(B) OR num(C).
{
    A.type = panopticon::BOOL;
    A.data.boolean = (int)B.data.number || (int)C.data.number;
    //A.n = B.n+1+C.n+1;
}

bool(A) ::= NOT num(B).
{
    A.type = panopticon::BOOL;
    A.data.boolean = !((int)B.data.number);
    //A.n = B.n+1;
}

num(A) ::= num(B) SHIFTL num(C).
{
    A.type = panopticon::NUMBER;
    A.data.number = (int)B.data.number << (int)C.data.number;
    //A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) SHIFTR num(C).
{
    A.type = panopticon::NUMBER;
    A.data.number = (int)B.data.number >> (int)C.data.number;
    //A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) BITAND num(C).
{
    A.type = panopticon::NUMBER;
    A.data.number = (int)B.data.number & (int)C.data.number;
    //A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) BITOR num(C).
{
    A.type = panopticon::NUMBER;
    A.data.number = (int)B.data.number | (int)C.data.number;
    //A.n = B.n+1+C.n+1;
}

num(A) ::= BITNOT num(B).
{
    A.type = panopticon::NUMBER;
    A.data.number = ~((int)B.data.number);
    //A.n = B.n+1;
}

num(A) ::= MINUS num(B). [UMINUS]
{
    A.type = panopticon::NUMBER;
    A.data.number = -1 * B.data.number;
    //A.n = B.n+1;
}

num(A) ::= num(B) MODULO num(C).
{
    A.type = panopticon::NUMBER;
    A.data.number = fmod(B.data.number,C.data.number);
    //A.n = B.n+1+C.n+1;
}

num(A) ::= num(B) POW num(C).
{
    A.type = panopticon::NUMBER;
    A.data.number = pow(B.data.number,C.data.number);
    //A.n = B.n+1+C.n+1;
}

//=====================================================================
//OPERATORS, ARRAY_ARRAY
//=====================================================================
array(A) ::= array(B) PLUSPLUS array(C).
{
    A.type = ARRAY;
    A.data.array = new std::vector<panopticon::object>();
    A.data.array->reserve(B.data.array->size()+C.data.array->size());
    for(int i=0;i<B.data.array->size();++i)
    {
        A.data.array->push_back(B.data.array->at(i));
    }
    for(int i=0;i<C.data.array->size();++i)
    {
        A.data.array->push_back(C.data.array->at(i));
    }
    delete B.data.array;
    delete C.data.array;
}

array(A) ::= array(B) PLUS array(C).
{
    A.type = ARRAY;
    if(panopticon::is_numerical(B)&&is_numerical(C))
    {
        panopticon::add_numerical_arrays(A,B,C);

    }
    else
    {
        A.data.array = new std::vector<panopticon::object>();
        A.data.array->reserve(B.data.array->size()+C.data.array->size());
        for(int i=0;i<B.data.array->size();++i)
        {
            A.data.array->push_back(B.data.array->at(i));
        }
        for(int i=0;i<C.data.array->size();++i)
        {
            A.data.array->push_back(C.data.array->at(i));
        }
    }
    delete B.data.array;
    delete C.data.array;
}

//=====================================================================
//OPERATORS, ARRAY_NUMBER
//=====================================================================

array(A) ::= num(B) PLUS array(C).
{
    A.type = ARRAY;
    if(panopticon::is_numerical(C))
    {
        panopticon::add_number_to_array(A,C,B);
    }
    else
    {
        A.data.array = new std::vector<panopticon::object>();
        A.data.array->reserve(C.data.array->size() + 1);
        A.data.array->push_back(B);
        for(int i=0;i<C.data.array->size();++i)
        {
            A.data.array->push_back(C.data.array->at(i));
        }

    }
    delete C.data.array;
}

array(A) ::= array(B) PLUS num(C).
{
    A.type = ARRAY;
    if(panopticon::is_numerical(B))
    {
        panopticon::add_number_to_array(A,C,B);
    }
    else
    {
        A.data.array = new std::vector<panopticon::object>();
        A.data.array->reserve(B.data.array->size() + 1);
        for(int i=0;i<B.data.array->size();++i)
        {
            A.data.array->push_back(B.data.array->at(i));
        }
        A.data.array->push_back(C);
    }

    delete B.data.array;
}

array(A) ::= num(B) PLUSPLUS array(C).
{
    A.type = ARRAY;
        A.data.array = new std::vector<panopticon::object>();
        A.data.array->reserve(C.data.array->size() + 1);
        A.data.array->push_back(B);
        for(int i=0;i<C.data.array->size();++i)
        {
            A.data.array->push_back(C.data.array->at(i));
        }
    delete C.data.array;
}

array(A) ::= array(B) PLUSPLUS num(C).
{
    A.type = ARRAY;
        A.data.array = new std::vector<panopticon::object>();
        A.data.array->reserve(B.data.array->size() + 1);
        for(int i=0;i<B.data.array->size();++i)
        {
            A.data.array->push_back(B.data.array->at(i));
        }
        A.data.array->push_back(C);
    delete B.data.array;
}

value(A) ::= array(B) LBRAC num(C) RBRAC. [INDEX]
{
    if(C.data.number<B.data.array->size())
    {
        A = panopticon::copy_object(B.data.array->at(C.data.number));
/*        A.data.number = C.data.number;*/
    }
    else
    {
        out() << "Error p0008: Index out of bounds." << std::endl;
    }
}

/*
multi_index(A) ::= index(B) LBRAC num(C) RBRAC. [INDEX]
{
    A.type = ARRAY;
    A.data.array = new std::vector<panopticon::object>();
    A.data.array->reserve(2);
    A.data.array->push_back(B.data.number);
    A.data.array->push_back(C.data.number);
}

multi_index(A) ::= multi_index(B) LBRAC num(C) RBRAC. [INDEX]
{
    A.type = ARRAY;
    A.data.array = new std::vector<panopticon::object>();
    A.data.array->reserve(2);
    A.data.array->push_back(B.data.number);
    A.data.array->push_back(C.data.number);
}
*/
/*
value(A) ::= array(B) index(C). [INDEX]
{

    if(C.data.number<B.data.array->size())
    {
        A = optic::copy_object(B.data.array->at(C.data.number));
    }
    else
    {
        out() << "Error p0008: Index out of bounds." << std::endl;
    }
}
*/
/*value::= value PLUS value.*/

/*value(A) ::= value(A).*/

//======================
//Syntax ERROR HANDLING
//=====================

in ::= error(B).
{
    switch(B)
    {
    case OpenQuoteError:
/*        out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}

error(A) ::= OPENQUOTEERROR(B).
{
    B.type = panopticon::NUMBER;
    A = OpenQuoteError;
    out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
