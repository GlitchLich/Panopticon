/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 3 "./src/Grammar/grammar.y"

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
#line 44 "./src/Grammar/grammar.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    ParseTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 70
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy139;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 112
#define YYNRULE 62
#define YYERRORSYMBOL 48
#define YYERRSYMDT yy139
#define YYFALLBACK 1
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
#define YY_ACTTAB_COUNT (706)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    18,  110,    3,   34,   26,   27,   22,   23,   33,   32,
 /*    10 */    30,   28,   31,   29,   25,   24,   40,   38,   37,   36,
 /*    20 */    35,   34,   16,   94,   77,   92,   26,   27,   22,   23,
 /*    30 */    33,   32,   30,   28,   31,   29,   25,   24,   40,   38,
 /*    40 */    37,   36,   35,   34,   26,   27,   22,   23,   33,   32,
 /*    50 */    30,   28,   31,   29,   25,   24,   40,   38,   37,   36,
 /*    60 */    35,   34,   26,   27,   22,   23,   33,   32,   30,   28,
 /*    70 */    31,   29,   25,   24,   40,   38,   37,   36,   35,   34,
 /*    80 */    76,   14,   90,   11,   15,  175,    1,   26,   27,   22,
 /*    90 */    23,   33,   32,   30,   28,   31,   29,   25,   24,   40,
 /*   100 */    38,   37,   36,   35,   34,    9,   13,    8,    7,   26,
 /*   110 */    27,   22,   23,   33,   32,   30,   28,   31,   29,   25,
 /*   120 */    24,   40,   38,   37,   36,   35,   34,   27,   22,   23,
 /*   130 */    33,   32,   30,   28,   31,   29,   25,   24,   40,   38,
 /*   140 */    37,   36,   35,   34,   22,   23,   33,   32,   30,   28,
 /*   150 */    31,   29,   25,   24,   40,   38,   37,   36,   35,   34,
 /*   160 */    23,   33,   32,   30,   28,   31,   29,   25,   24,   40,
 /*   170 */    38,   37,   36,   35,   34,   55,   89,  176,  176,   88,
 /*   180 */   109,  108,  107,  106,   70,  105,  176,   73,   69,   91,
 /*   190 */   102,    6,  100,   99,   98,   33,   32,   30,   28,   31,
 /*   200 */    29,   25,   24,   40,   38,   37,   36,   35,   34,   30,
 /*   210 */    28,   31,   29,   25,   24,   40,   38,   37,   36,   35,
 /*   220 */    34,  112,   21,  176,   93,   19,   17,   20,   39,   25,
 /*   230 */    24,   40,   38,   37,   36,   35,   34,  176,   87,   21,
 /*   240 */   176,  176,  176,   78,   20,   39,   21,    2,   97,   96,
 /*   250 */    95,   20,   39,  176,  111,   68,  104,  176,   37,   36,
 /*   260 */    35,   34,   87,  176,    2,   97,   96,   95,   55,  176,
 /*   270 */   176,    2,   97,   96,   95,   21,  101,  176,  105,    5,
 /*   280 */    20,   39,  176,  102,   79,  100,   99,   98,  176,  176,
 /*   290 */   176,   87,  176,  176,  176,  176,   55,  176,  176,  176,
 /*   300 */     2,   97,   96,   95,  101,  176,  105,    4,  176,  176,
 /*   310 */   176,  102,   55,  100,   99,   98,   12,   10,   75,   74,
 /*   320 */   103,  176,  105,  176,  176,  176,  176,  102,   71,  100,
 /*   330 */    99,   98,   40,   38,   37,   36,   35,   34,  105,  176,
 /*   340 */   176,   86,  176,  102,  176,  100,   99,   98,  176,  176,
 /*   350 */   176,  105,   72,  176,  176,  176,  102,  176,  100,   99,
 /*   360 */    98,  176,  105,   85,  176,  176,  176,  102,  176,  100,
 /*   370 */    99,   98,  176,  105,  176,  176,  176,   84,  102,  176,
 /*   380 */   100,   99,   98,   83,  176,  176,  176,  105,  176,  176,
 /*   390 */   176,  176,  102,  105,  100,   99,   98,   82,  102,  176,
 /*   400 */   100,   99,   98,  176,  176,  176,  176,  105,   61,  176,
 /*   410 */   176,  176,  102,  176,  100,   99,   98,  176,  105,   60,
 /*   420 */   122,  176,  176,  102,  176,  100,   99,   98,  176,  105,
 /*   430 */    65,  176,  176,  176,  102,  176,  100,   99,   98,  176,
 /*   440 */   105,  176,   64,  176,  176,  102,    3,  100,   99,   98,
 /*   450 */   176,  176,  105,  122,  122,  122,  176,  102,   63,  100,
 /*   460 */    99,   98,  176,  176,   62,  176,  176,  176,  105,  176,
 /*   470 */   176,  176,  176,  102,  105,  100,   99,   98,  176,  102,
 /*   480 */    57,  100,   99,   98,  176,  176,   56,  176,  176,  176,
 /*   490 */   105,  176,   67,  176,  176,  102,  105,  100,   99,   98,
 /*   500 */   176,  102,  105,  100,   99,   98,  176,  102,   66,  100,
 /*   510 */    99,   98,  176,  176,   59,  176,  176,  176,  105,  176,
 /*   520 */   176,  176,  176,  102,  105,  100,   99,   98,  176,  102,
 /*   530 */    58,  100,   99,   98,  176,  176,   81,  176,  176,  176,
 /*   540 */   105,  176,   80,  176,  176,  102,  105,  100,   99,   98,
 /*   550 */   176,  102,  105,  100,   99,   98,  176,  102,   45,  100,
 /*   560 */    99,   98,  176,  176,   54,  176,  176,  176,  105,  176,
 /*   570 */   176,  176,  176,  102,  105,  100,   99,   98,  176,  102,
 /*   580 */    44,  100,   99,   98,  176,  176,   53,  176,  176,  176,
 /*   590 */   105,  176,   43,  176,  176,  102,  105,  100,   99,   98,
 /*   600 */   176,  102,  105,  100,   99,   98,  176,  102,   51,  100,
 /*   610 */    99,   98,  176,  176,   50,  176,  176,  176,  105,  176,
 /*   620 */   176,  176,  176,  102,  105,  100,   99,   98,  176,  102,
 /*   630 */    42,  100,   99,   98,  176,  176,   49,  176,  176,  176,
 /*   640 */   105,  176,   41,  176,  176,  102,  105,  100,   99,   98,
 /*   650 */   176,  102,  105,  100,   99,   98,  176,  102,   48,  100,
 /*   660 */    99,   98,  176,  176,   47,  176,  176,  176,  105,  176,
 /*   670 */   176,  176,  176,  102,  105,  100,   99,   98,  176,  102,
 /*   680 */    46,  100,   99,   98,  176,  176,   52,  176,  176,  176,
 /*   690 */   105,  176,  176,  176,  176,  102,  105,  100,   99,   98,
 /*   700 */   176,  102,  176,  100,   99,   98,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,   33,   27,   22,    5,    6,    7,    8,    9,   10,
 /*    10 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    20 */    21,   22,    1,   31,   34,   40,    5,    6,    7,    8,
 /*    30 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*    40 */    19,   20,   21,   22,    5,    6,    7,    8,    9,   10,
 /*    50 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    60 */    21,   22,    5,    6,    7,    8,    9,   10,   11,   12,
 /*    70 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*    80 */    37,   42,   48,    1,   41,   51,   52,    5,    6,    7,
 /*    90 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   100 */    18,   19,   20,   21,   22,    1,   42,    1,    1,    5,
 /*   110 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   120 */    16,   17,   18,   19,   20,   21,   22,    6,    7,    8,
 /*   130 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   140 */    19,   20,   21,   22,    7,    8,    9,   10,   11,   12,
 /*   150 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   160 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   170 */    18,   19,   20,   21,   22,   49,   47,   69,   69,   53,
 /*   180 */    54,   55,   56,   57,   58,   59,   69,   61,   62,   63,
 /*   190 */    64,    1,   66,   67,   68,    9,   10,   11,   12,   13,
 /*   200 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   11,
 /*   210 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   220 */    22,    0,   18,   69,   34,   35,   36,   23,   24,   15,
 /*   230 */    16,   17,   18,   19,   20,   21,   22,   69,   34,   18,
 /*   240 */    69,   69,   69,   39,   23,   24,   18,   43,   44,   45,
 /*   250 */    46,   23,   24,   69,   33,   34,   28,   69,   19,   20,
 /*   260 */    21,   22,   34,   69,   43,   44,   45,   46,   49,   69,
 /*   270 */    69,   43,   44,   45,   46,   18,   57,   69,   59,   60,
 /*   280 */    23,   24,   69,   64,   65,   66,   67,   68,   69,   69,
 /*   290 */    69,   34,   69,   69,   69,   69,   49,   69,   69,   69,
 /*   300 */    43,   44,   45,   46,   57,   69,   59,   60,   69,   69,
 /*   310 */    69,   64,   49,   66,   67,   68,   35,   36,   37,   38,
 /*   320 */    57,   69,   59,   69,   69,   69,   69,   64,   49,   66,
 /*   330 */    67,   68,   17,   18,   19,   20,   21,   22,   59,   69,
 /*   340 */    69,   49,   69,   64,   69,   66,   67,   68,   69,   69,
 /*   350 */    69,   59,   49,   69,   69,   69,   64,   69,   66,   67,
 /*   360 */    68,   69,   59,   49,   69,   69,   69,   64,   69,   66,
 /*   370 */    67,   68,   69,   59,   69,   69,   69,   49,   64,   69,
 /*   380 */    66,   67,   68,   49,   69,   69,   69,   59,   69,   69,
 /*   390 */    69,   69,   64,   59,   66,   67,   68,   49,   64,   69,
 /*   400 */    66,   67,   68,   69,   69,   69,   69,   59,   49,   69,
 /*   410 */    69,   69,   64,   69,   66,   67,   68,   69,   59,   49,
 /*   420 */     1,   69,   69,   64,   69,   66,   67,   68,   69,   59,
 /*   430 */    49,   69,   69,   69,   64,   69,   66,   67,   68,   69,
 /*   440 */    59,   69,   49,   69,   69,   64,   27,   66,   67,   68,
 /*   450 */    69,   69,   59,   34,   35,   36,   69,   64,   49,   66,
 /*   460 */    67,   68,   69,   69,   49,   69,   69,   69,   59,   69,
 /*   470 */    69,   69,   69,   64,   59,   66,   67,   68,   69,   64,
 /*   480 */    49,   66,   67,   68,   69,   69,   49,   69,   69,   69,
 /*   490 */    59,   69,   49,   69,   69,   64,   59,   66,   67,   68,
 /*   500 */    69,   64,   59,   66,   67,   68,   69,   64,   49,   66,
 /*   510 */    67,   68,   69,   69,   49,   69,   69,   69,   59,   69,
 /*   520 */    69,   69,   69,   64,   59,   66,   67,   68,   69,   64,
 /*   530 */    49,   66,   67,   68,   69,   69,   49,   69,   69,   69,
 /*   540 */    59,   69,   49,   69,   69,   64,   59,   66,   67,   68,
 /*   550 */    69,   64,   59,   66,   67,   68,   69,   64,   49,   66,
 /*   560 */    67,   68,   69,   69,   49,   69,   69,   69,   59,   69,
 /*   570 */    69,   69,   69,   64,   59,   66,   67,   68,   69,   64,
 /*   580 */    49,   66,   67,   68,   69,   69,   49,   69,   69,   69,
 /*   590 */    59,   69,   49,   69,   69,   64,   59,   66,   67,   68,
 /*   600 */    69,   64,   59,   66,   67,   68,   69,   64,   49,   66,
 /*   610 */    67,   68,   69,   69,   49,   69,   69,   69,   59,   69,
 /*   620 */    69,   69,   69,   64,   59,   66,   67,   68,   69,   64,
 /*   630 */    49,   66,   67,   68,   69,   69,   49,   69,   69,   69,
 /*   640 */    59,   69,   49,   69,   69,   64,   59,   66,   67,   68,
 /*   650 */    69,   64,   59,   66,   67,   68,   69,   64,   49,   66,
 /*   660 */    67,   68,   69,   69,   49,   69,   69,   69,   59,   69,
 /*   670 */    69,   69,   69,   64,   59,   66,   67,   68,   69,   64,
 /*   680 */    49,   66,   67,   68,   69,   69,   49,   69,   69,   69,
 /*   690 */    59,   69,   69,   69,   69,   64,   59,   66,   67,   68,
 /*   700 */    69,   64,   69,   66,   67,   68,
};
#define YY_SHIFT_USE_DFLT (-33)
#define YY_SHIFT_COUNT (88)
#define YY_SHIFT_MIN   (-32)
#define YY_SHIFT_MAX   (419)
static const short yy_shift_ofst[] = {
 /*     0 */   129,  221,  257,  257,  228,  257,  204,  257,  257,  257,
 /*    10 */   257,  257,  257,  257,  257,  257,  257,  257,  257,  257,
 /*    20 */   257,  257,  257,  257,  257,  257,  257,  257,  257,  257,
 /*    30 */   257,  257,  257,  257,  257,  257,  257,  257,  257,  257,
 /*    40 */   257,  104,   82,   39,   21,   -1,   57,   57,   57,   57,
 /*    50 */    57,   57,   57,   57,   57,   57,  121,  137,  152,  186,
 /*    60 */   198,  198,  214,  214,  214,  214,  315,  315,  419,  281,
 /*    70 */   190,  239,  239,   43,  107,  106,   64,  -15,  -10,   -8,
 /*    80 */   -19,  -19,  -19,  -19,  -19,  -19,  -19,  -25,  -32,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (40)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (637)
static const short yy_reduce_ofst[] = {
 /*     0 */    34,  126,  219,  247,  263,  263,  637,  631,  615,  609,
 /*    10 */   593,  587,  581,  565,  559,  543,  537,  531,  515,  509,
 /*    20 */   493,  487,  481,  465,  459,  443,  437,  431,  415,  409,
 /*    30 */   393,  381,  370,  359,  348,  334,  328,  314,  303,  292,
 /*    40 */   279,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   113,  174,  143,  174,  174,  144,  174,  174,  174,  174,
 /*    10 */   174,  174,  174,  174,  174,  174,  174,  174,  174,  174,
 /*    20 */   174,  174,  174,  174,  174,  174,  174,  174,  174,  174,
 /*    30 */   174,  174,  174,  174,  174,  174,  174,  174,  174,  174,
 /*    40 */   174,  174,  174,  174,  174,  174,  134,  133,  132,  130,
 /*    50 */   137,  136,  138,  131,  129,  120,  164,  163,  171,  170,
 /*    60 */   158,  157,  162,  161,  160,  159,  169,  168,  123,  127,
 /*    70 */   174,  151,  152,  126,  174,  174,  174,  174,  174,  174,
 /*    80 */   167,  166,  156,  155,  154,  153,  165,  123,  174,  173,
 /*    90 */   172,  128,  135,  121,  142,  150,  149,  148,  147,  146,
 /*   100 */   145,  139,  141,  140,  125,  124,  119,  118,  117,  116,
 /*   110 */   115,  114,
};

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
    0,  /*          $ => nothing */
    0,  /*     ASSIGN => nothing */
    0,  /*      BITOR => nothing */
    0,  /* FUNCTION_DEC => nothing */
    0,  /*      INDEX => nothing */
    0,  /*         OR => nothing */
    0,  /*        AND => nothing */
    0,  /*     BITXOR => nothing */
    0,  /*     BITAND => nothing */
    0,  /*    EQUALTO => nothing */
    0,  /* NOTEQUALTO => nothing */
    0,  /* GREATERTHAN => nothing */
    0,  /*       GORE => nothing */
    0,  /*   LESSTHAN => nothing */
    0,  /*       LORE => nothing */
    0,  /*     SHIFTL => nothing */
    0,  /*     SHIFTR => nothing */
    0,  /*       PLUS => nothing */
    0,  /*      MINUS => nothing */
    0,  /*     DIVIDE => nothing */
    0,  /*      TIMES => nothing */
    0,  /*     MODULO => nothing */
    0,  /*        POW => nothing */
    0,  /*        NOT => nothing */
    0,  /*     BITNOT => nothing */
    0,  /*     UMINUS => nothing */
    0,  /*   PLUSPLUS => nothing */
    0,  /*     LPAREN => nothing */
    0,  /*     RPAREN => nothing */
    0,  /*      COMMA => nothing */
   43,  /*      LBRAC => OPENBRAC */
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "ASSIGN",        "BITOR",         "FUNCTION_DEC",
  "INDEX",         "OR",            "AND",           "BITXOR",      
  "BITAND",        "EQUALTO",       "NOTEQUALTO",    "GREATERTHAN", 
  "GORE",          "LESSTHAN",      "LORE",          "SHIFTL",      
  "SHIFTR",        "PLUS",          "MINUS",         "DIVIDE",      
  "TIMES",         "MODULO",        "POW",           "NOT",         
  "BITNOT",        "UMINUS",        "PLUSPLUS",      "LPAREN",      
  "RPAREN",        "COMMA",         "LBRAC",         "RBRAC",       
  "COLLECTARRAY",  "NEWLINE",       "NAME",          "GUARD_N",     
  "GUARD_S",       "WILDCARD_N",    "WILDCARD",      "CASE",        
  "OF",            "N_TAB",         "POINTER",       "OPENBRAC",    
  "NUM",           "STRING",        "BOOLEAN",       "OPENQUOTEERROR",
  "error",         "expr",          "id",            "main",        
  "in",            "start",         "spec",          "assignment",  
  "top_stmt",      "stmt",          "name_chain",    "function_call",
  "stmt_list",     "case_statement",  "guard_statement",  "final_guard_statement",
  "array",         "maybe_empty_stmt_list",  "num",           "string",      
  "bool",        
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "main ::= in",
 /*   1 */ "in ::=",
 /*   2 */ "in ::= in NEWLINE",
 /*   3 */ "in ::= in start NEWLINE",
 /*   4 */ "start ::= spec",
 /*   5 */ "spec ::= assignment",
 /*   6 */ "spec ::= top_stmt",
 /*   7 */ "top_stmt ::= stmt",
 /*   8 */ "stmt ::= expr",
 /*   9 */ "name_chain ::= name_chain NAME",
 /*  10 */ "name_chain ::= NAME",
 /*  11 */ "expr ::= NAME",
 /*  12 */ "expr ::= function_call",
 /*  13 */ "function_call ::= NAME LPAREN stmt_list RPAREN",
 /*  14 */ "spec ::= case_statement",
 /*  15 */ "spec ::= guard_statement",
 /*  16 */ "spec ::= final_guard_statement",
 /*  17 */ "guard_statement ::= name_chain GUARD_N expr ASSIGN expr",
 /*  18 */ "guard_statement ::= guard_statement GUARD_N expr ASSIGN expr",
 /*  19 */ "guard_statement ::= name_chain GUARD_S expr ASSIGN expr",
 /*  20 */ "guard_statement ::= guard_statement GUARD_S expr ASSIGN expr",
 /*  21 */ "final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr",
 /*  22 */ "final_guard_statement ::= guard_statement WILDCARD ASSIGN expr",
 /*  23 */ "case_statement ::= name_chain ASSIGN CASE NAME OF",
 /*  24 */ "case_statement ::= case_statement N_TAB expr POINTER expr",
 /*  25 */ "case_statement ::= case_statement WILDCARD_N POINTER expr",
 /*  26 */ "assignment ::= name_chain ASSIGN expr",
 /*  27 */ "stmt_list ::= stmt",
 /*  28 */ "stmt_list ::= stmt_list stmt",
 /*  29 */ "expr ::= array",
 /*  30 */ "array ::= OPENBRAC maybe_empty_stmt_list RBRAC",
 /*  31 */ "maybe_empty_stmt_list ::=",
 /*  32 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  33 */ "expr ::= num",
 /*  34 */ "expr ::= string",
 /*  35 */ "expr ::= bool",
 /*  36 */ "num ::= NUM",
 /*  37 */ "string ::= STRING",
 /*  38 */ "bool ::= BOOLEAN",
 /*  39 */ "expr ::= expr PLUS expr",
 /*  40 */ "expr ::= expr MINUS expr",
 /*  41 */ "expr ::= expr DIVIDE expr",
 /*  42 */ "expr ::= expr TIMES expr",
 /*  43 */ "expr ::= expr MODULO expr",
 /*  44 */ "expr ::= expr POW expr",
 /*  45 */ "expr ::= expr EQUALTO expr",
 /*  46 */ "expr ::= expr NOTEQUALTO expr",
 /*  47 */ "expr ::= expr LESSTHAN expr",
 /*  48 */ "expr ::= expr GREATERTHAN expr",
 /*  49 */ "expr ::= expr LORE expr",
 /*  50 */ "expr ::= expr GORE expr",
 /*  51 */ "expr ::= expr AND expr",
 /*  52 */ "expr ::= expr OR expr",
 /*  53 */ "expr ::= BITNOT expr",
 /*  54 */ "expr ::= MINUS expr",
 /*  55 */ "expr ::= NOT expr",
 /*  56 */ "expr ::= expr SHIFTL expr",
 /*  57 */ "expr ::= expr SHIFTR expr",
 /*  58 */ "expr ::= expr BITAND expr",
 /*  59 */ "expr ::= expr BITXOR expr",
 /*  60 */ "in ::= error",
 /*  61 */ "error ::= OPENQUOTEERROR",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
      /* TERMINAL Destructor */
    case 1: /* ASSIGN */
    case 2: /* BITOR */
    case 3: /* FUNCTION_DEC */
    case 4: /* INDEX */
    case 5: /* OR */
    case 6: /* AND */
    case 7: /* BITXOR */
    case 8: /* BITAND */
    case 9: /* EQUALTO */
    case 10: /* NOTEQUALTO */
    case 11: /* GREATERTHAN */
    case 12: /* GORE */
    case 13: /* LESSTHAN */
    case 14: /* LORE */
    case 15: /* SHIFTL */
    case 16: /* SHIFTR */
    case 17: /* PLUS */
    case 18: /* MINUS */
    case 19: /* DIVIDE */
    case 20: /* TIMES */
    case 21: /* MODULO */
    case 22: /* POW */
    case 23: /* NOT */
    case 24: /* BITNOT */
    case 25: /* UMINUS */
    case 26: /* PLUSPLUS */
    case 27: /* LPAREN */
    case 28: /* RPAREN */
    case 29: /* COMMA */
    case 30: /* LBRAC */
    case 31: /* RBRAC */
    case 32: /* COLLECTARRAY */
    case 33: /* NEWLINE */
    case 34: /* NAME */
    case 35: /* GUARD_N */
    case 36: /* GUARD_S */
    case 37: /* WILDCARD_N */
    case 38: /* WILDCARD */
    case 39: /* CASE */
    case 40: /* OF */
    case 41: /* N_TAB */
    case 42: /* POINTER */
    case 43: /* OPENBRAC */
    case 44: /* NUM */
    case 45: /* STRING */
    case 46: /* BOOLEAN */
    case 47: /* OPENQUOTEERROR */
{
#line 43 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 708 "./src/Grammar/grammar.c"
}
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParseAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_COUNT
   || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 51, 1 },
  { 52, 0 },
  { 52, 2 },
  { 52, 3 },
  { 53, 1 },
  { 54, 1 },
  { 54, 1 },
  { 56, 1 },
  { 57, 1 },
  { 58, 2 },
  { 58, 1 },
  { 49, 1 },
  { 49, 1 },
  { 59, 4 },
  { 54, 1 },
  { 54, 1 },
  { 54, 1 },
  { 62, 5 },
  { 62, 5 },
  { 62, 5 },
  { 62, 5 },
  { 63, 4 },
  { 63, 4 },
  { 61, 5 },
  { 61, 5 },
  { 61, 4 },
  { 55, 3 },
  { 60, 1 },
  { 60, 2 },
  { 49, 1 },
  { 64, 3 },
  { 65, 0 },
  { 65, 1 },
  { 49, 1 },
  { 49, 1 },
  { 49, 1 },
  { 66, 1 },
  { 67, 1 },
  { 68, 1 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 2 },
  { 49, 2 },
  { 49, 2 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 52, 1 },
  { 48, 1 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 2: /* in ::= in NEWLINE */
      case 3: /* in ::= in start NEWLINE */ yytestcase(yyruleno==3);
#line 83 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,33,&yymsp[0].minor);
}
#line 1068 "./src/Grammar/grammar.c"
        break;
      case 4: /* start ::= spec */
#line 89 "./src/Grammar/grammar.y"
{
    if(
        yymsp[0].minor.yy0.type == optic::OPERATION_TREE
        )
    {
/*        panopticon::resolve_stack_from_parser(yymsp[0].minor.yy0);*/
    }
    else if(
        yymsp[0].minor.yy0.type == optic::NUMBER ||
        yymsp[0].minor.yy0.type == optic::STRING ||
        yymsp[0].minor.yy0.type == optic::BOOL ||
        yymsp[0].minor.yy0.type == optic::GUARD
        )
    {
        print_object(yymsp[0].minor.yy0);
    }
}
#line 1089 "./src/Grammar/grammar.c"
        break;
      case 5: /* spec ::= assignment */
      case 33: /* expr ::= num */ yytestcase(yyruleno==33);
      case 35: /* expr ::= bool */ yytestcase(yyruleno==35);
#line 109 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1098 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= top_stmt */
      case 7: /* top_stmt ::= stmt */ yytestcase(yyruleno==7);
      case 34: /* expr ::= string */ yytestcase(yyruleno==34);
#line 121 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1108 "./src/Grammar/grammar.c"
        break;
      case 8: /* stmt ::= expr */
      case 27: /* stmt_list ::= stmt */ yytestcase(yyruleno==27);
#line 133 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1117 "./src/Grammar/grammar.c"
        break;
      case 9: /* name_chain ::= name_chain NAME */
#line 139 "./src/Grammar/grammar.y"
{
    if(yymsp[-1].minor.yy0.type!=optic::ARRAY)
    {
        yygotominor.yy0.type = optic::ARRAY;
        yygotominor.yy0.data.array = new optic::Array();

        optic::object newObject1,newObject2;
        newObject1.type = optic::STRING;
        newObject2.type = optic::STRING;
        newObject1.data.string = new panopticon::String(yymsp[-1].minor.yy0.data.string->c_str());
        newObject2.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
        yygotominor.yy0.data.array->push_back(newObject1);
        yygotominor.yy0.data.array->push_back(newObject2);
    }
    else
    {
        yygotominor.yy0.type = optic::ARRAY;
        yygotominor.yy0.data.array = new optic::Array();
        yygotominor.yy0.data.array->reserve(yymsp[-1].minor.yy0.data.array->size()+1);
        for(int i=0;i<yymsp[-1].minor.yy0.data.array->size();++i)
        {
            optic::object newObject;
            newObject.type = optic::STRING;
            newObject.data.string = new optic::String(*yymsp[-1].minor.yy0.data.array->at(i).data.string);
            yygotominor.yy0.data.array->push_back(newObject);
        }
        optic::object newObject2;
        newObject2.type = optic::STRING;
        newObject2.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
        yygotominor.yy0.data.array->push_back(newObject2);
        //yygotominor.yy0.scope = optic::get_scope();
    }
    delete_object(yymsp[-1].minor.yy0);
    delete_object(yymsp[0].minor.yy0);
}
#line 1156 "./src/Grammar/grammar.c"
        break;
      case 10: /* name_chain ::= NAME */
#line 176 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1165 "./src/Grammar/grammar.c"
        break;
      case 11: /* expr ::= NAME */
#line 183 "./src/Grammar/grammar.y"
{
    panopticon::retrieve_variable(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1177 "./src/Grammar/grammar.c"
        break;
      case 12: /* expr ::= function_call */
      case 29: /* expr ::= array */ yytestcase(yyruleno==29);
#line 193 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1185 "./src/Grammar/grammar.c"
        break;
      case 13: /* function_call ::= NAME LPAREN stmt_list RPAREN */
#line 198 "./src/Grammar/grammar.y"
{
    // yygotominor.yy0.scope = optic::get_scope();
    yygotominor.yy0.type = optic::FUNCTION_CALL;
    optic::parse_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,27,&yymsp[-2].minor);
  yy_destructor(yypParser,28,&yymsp[0].minor);
}
#line 1201 "./src/Grammar/grammar.c"
        break;
      case 14: /* spec ::= case_statement */
#line 210 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Case: " << *yymsp[0].minor.yy0.data.array->at(0).data.string << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1209 "./src/Grammar/grammar.c"
        break;
      case 15: /* spec ::= guard_statement */
      case 16: /* spec ::= final_guard_statement */ yytestcase(yyruleno==16);
#line 217 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Guard: " << *yymsp[0].minor.yy0.data.array->at(0).data.string << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1218 "./src/Grammar/grammar.c"
        break;
      case 17: /* guard_statement ::= name_chain GUARD_N expr ASSIGN expr */
      case 18: /* guard_statement ::= guard_statement GUARD_N expr ASSIGN expr */ yytestcase(yyruleno==18);
#line 229 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,35,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1229 "./src/Grammar/grammar.c"
        break;
      case 19: /* guard_statement ::= name_chain GUARD_S expr ASSIGN expr */
      case 20: /* guard_statement ::= guard_statement GUARD_S expr ASSIGN expr */ yytestcase(yyruleno==20);
#line 241 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1240 "./src/Grammar/grammar.c"
        break;
      case 21: /* final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr */
#line 253 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1250 "./src/Grammar/grammar.c"
        break;
      case 22: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr */
#line 259 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,38,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1260 "./src/Grammar/grammar.c"
        break;
      case 23: /* case_statement ::= name_chain ASSIGN CASE NAME OF */
#line 265 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,39,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[-1].minor);
  yy_destructor(yypParser,40,&yymsp[0].minor);
}
#line 1272 "./src/Grammar/grammar.c"
        break;
      case 24: /* case_statement ::= case_statement N_TAB expr POINTER expr */
#line 271 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,41,&yymsp[-3].minor);
  yy_destructor(yypParser,42,&yymsp[-1].minor);
}
#line 1282 "./src/Grammar/grammar.c"
        break;
      case 25: /* case_statement ::= case_statement WILDCARD_N POINTER expr */
#line 277 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,42,&yymsp[-1].minor);
}
#line 1292 "./src/Grammar/grammar.c"
        break;
      case 26: /* assignment ::= name_chain ASSIGN expr */
#line 290 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::ASSIGNMENT;
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1306 "./src/Grammar/grammar.c"
        break;
      case 28: /* stmt_list ::= stmt_list stmt */
#line 311 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    if(yymsp[-1].minor.yy0.type!=panopticon::STATEMENT_LIST)
    {
        panopticon::create_array(yygotominor.yy0);
        yygotominor.yy0.data.array->push_back(yymsp[-1].minor.yy0);
        yygotominor.yy0.data.array->push_back(yymsp[0].minor.yy0);
    }
    else
    {
        yygotominor.yy0.data.array = yymsp[-1].minor.yy0.data.array;
        yygotominor.yy0.data.array->push_back(yymsp[0].minor.yy0);
    }
    //yygotominor.yy0.n = yymsp[-1].minor.yy0.n+1;
}
#line 1325 "./src/Grammar/grammar.c"
        break;
      case 30: /* array ::= OPENBRAC maybe_empty_stmt_list RBRAC */
#line 341 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::ARRAY;
    yygotominor.yy0.data.array = yymsp[-1].minor.yy0.data.array;
  yy_destructor(yypParser,43,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1335 "./src/Grammar/grammar.c"
        break;
      case 31: /* maybe_empty_stmt_list ::= */
#line 347 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1343 "./src/Grammar/grammar.c"
        break;
      case 32: /* maybe_empty_stmt_list ::= stmt_list */
#line 353 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    if(yymsp[0].minor.yy0.type!=panopticon::STATEMENT_LIST)
    {
        panopticon::create_array(yygotominor.yy0);
        yygotominor.yy0.data.array->push_back(yymsp[0].minor.yy0);
    }
    else
    {
        yygotominor.yy0.data.array = yymsp[0].minor.yy0.data.array;
    }
}
#line 1359 "./src/Grammar/grammar.c"
        break;
      case 36: /* num ::= NUM */
#line 405 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.type = panopticon::NUMBER;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1368 "./src/Grammar/grammar.c"
        break;
      case 37: /* string ::= STRING */
#line 412 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1378 "./src/Grammar/grammar.c"
        break;
      case 38: /* bool ::= BOOLEAN */
#line 421 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    yygotominor.yy0.type = panopticon::BOOL;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1387 "./src/Grammar/grammar.c"
        break;
      case 39: /* expr ::= expr PLUS expr */
#line 453 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::plus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1400 "./src/Grammar/grammar.c"
        break;
      case 40: /* expr ::= expr MINUS expr */
#line 463 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1413 "./src/Grammar/grammar.c"
        break;
      case 41: /* expr ::= expr DIVIDE expr */
#line 473 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1426 "./src/Grammar/grammar.c"
        break;
      case 42: /* expr ::= expr TIMES expr */
#line 483 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1439 "./src/Grammar/grammar.c"
        break;
      case 43: /* expr ::= expr MODULO expr */
#line 493 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1452 "./src/Grammar/grammar.c"
        break;
      case 44: /* expr ::= expr POW expr */
#line 503 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1465 "./src/Grammar/grammar.c"
        break;
      case 45: /* expr ::= expr EQUALTO expr */
#line 513 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1478 "./src/Grammar/grammar.c"
        break;
      case 46: /* expr ::= expr NOTEQUALTO expr */
#line 523 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1491 "./src/Grammar/grammar.c"
        break;
      case 47: /* expr ::= expr LESSTHAN expr */
#line 533 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1504 "./src/Grammar/grammar.c"
        break;
      case 48: /* expr ::= expr GREATERTHAN expr */
#line 543 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1517 "./src/Grammar/grammar.c"
        break;
      case 49: /* expr ::= expr LORE expr */
#line 553 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1530 "./src/Grammar/grammar.c"
        break;
      case 50: /* expr ::= expr GORE expr */
#line 563 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1543 "./src/Grammar/grammar.c"
        break;
      case 51: /* expr ::= expr AND expr */
#line 573 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1556 "./src/Grammar/grammar.c"
        break;
      case 52: /* expr ::= expr OR expr */
#line 583 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1569 "./src/Grammar/grammar.c"
        break;
      case 53: /* expr ::= BITNOT expr */
#line 593 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1582 "./src/Grammar/grammar.c"
        break;
      case 54: /* expr ::= MINUS expr */
#line 603 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1595 "./src/Grammar/grammar.c"
        break;
      case 55: /* expr ::= NOT expr */
#line 613 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    not_value(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1609 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr SHIFTL expr */
#line 624 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1622 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr SHIFTR expr */
#line 634 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1635 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= expr BITAND expr */
#line 644 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1648 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= expr BITXOR expr */
#line 664 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1661 "./src/Grammar/grammar.c"
        break;
      case 60: /* in ::= error */
#line 715 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy139)
    {
    case panopticon::OpenQuoteError:
/*        panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        panopticon::out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 1676 "./src/Grammar/grammar.c"
        break;
      case 61: /* error ::= OPENQUOTEERROR */
#line 728 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy139 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1685 "./src/Grammar/grammar.c"
        break;
      default:
      /* (0) main ::= in */ yytestcase(yyruleno==0);
      /* (1) in ::= */ yytestcase(yyruleno==1);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 77 "./src/Grammar/grammar.y"

panopticon::out() << "Syntax error!" << std::endl;
#line 1752 "./src/Grammar/grammar.c"
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
#line 72 "./src/Grammar/grammar.y"

printf("parsing complete!\n\n\n");
#line 1774 "./src/Grammar/grammar.c"
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
