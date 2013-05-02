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
#define YYNOCODE 74
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy147;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 122
#define YYNRULE 67
#define YYERRORSYMBOL 51
#define YYERRSYMDT yy147
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
#define YY_ACTTAB_COUNT (810)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    27,   28,   23,   24,   34,   33,   31,   29,   32,   30,
 /*    10 */    26,   25,   43,   40,   38,   37,   36,   35,   19,  120,
 /*    20 */     3,   92,   27,   28,   23,   24,   34,   33,   31,   29,
 /*    30 */    32,   30,   26,   25,   43,   40,   38,   37,   36,   35,
 /*    40 */    41,   17,   42,   35,  104,   27,   28,   23,   24,   34,
 /*    50 */    33,   31,   29,   32,   30,   26,   25,   43,   40,   38,
 /*    60 */    37,   36,   35,   27,   28,   23,   24,   34,   33,   31,
 /*    70 */    29,   32,   30,   26,   25,   43,   40,   38,   37,   36,
 /*    80 */    35,   23,   24,   34,   33,   31,   29,   32,   30,   26,
 /*    90 */    25,   43,   40,   38,   37,   36,   35,  102,   12,   10,
 /*   100 */    82,   81,  100,   27,   28,   23,   24,   34,   33,   31,
 /*   110 */    29,   32,   30,   26,   25,   43,   40,   38,   37,   36,
 /*   120 */    35,   27,   28,   23,   24,   34,   33,   31,   29,   32,
 /*   130 */    30,   26,   25,   43,   40,   38,   37,   36,   35,  101,
 /*   140 */    27,   28,   23,   24,   34,   33,   31,   29,   32,   30,
 /*   150 */    26,   25,   43,   40,   38,   37,   36,   35,   13,   14,
 /*   160 */    97,   11,    8,  190,    1,   27,   28,   23,   24,   34,
 /*   170 */    33,   31,   29,   32,   30,   26,   25,   43,   40,   38,
 /*   180 */    37,   36,   35,    9,    7,   99,   96,   27,   28,   23,
 /*   190 */    24,   34,   33,   31,   29,   32,   30,   26,   25,   43,
 /*   200 */    40,   38,   37,   36,   35,   28,   23,   24,   34,   33,
 /*   210 */    31,   29,   32,   30,   26,   25,   43,   40,   38,   37,
 /*   220 */    36,   35,   61,  191,  191,  191,   95,  119,  118,  117,
 /*   230 */   116,   76,  115,  191,   79,   74,   80,   98,  113,  191,
 /*   240 */   110,  109,  108,   24,   34,   33,   31,   29,   32,   30,
 /*   250 */    26,   25,   43,   40,   38,   37,   36,   35,   34,   33,
 /*   260 */    31,   29,   32,   30,   26,   25,   43,   40,   38,   37,
 /*   270 */    36,   35,   31,   29,   32,   30,   26,   25,   43,   40,
 /*   280 */    38,   37,   36,   35,  122,   26,   25,   43,   40,   38,
 /*   290 */    37,   36,   35,   22,   77,   83,  191,  191,   21,   39,
 /*   300 */    15,  191,   22,  191,  115,  191,  191,   21,   39,   94,
 /*   310 */   113,  191,  110,  109,  108,   16,  191,  121,   75,   93,
 /*   320 */   191,    2,  107,  106,  105,  191,  191,  191,   93,  191,
 /*   330 */     2,  107,  106,  105,   22,   61,  191,  191,  191,   21,
 /*   340 */    39,   22,  191,  111,  114,  115,   21,   39,  191,  191,
 /*   350 */    94,  113,  191,  110,  109,  108,  191,   94,  191,  191,
 /*   360 */    93,  191,    2,  107,  106,  105,  191,   93,  191,    2,
 /*   370 */   107,  106,  105,  191,   61,   43,   40,   38,   37,   36,
 /*   380 */    35,  191,  112,  191,  115,    5,  191,   61,  191,  191,
 /*   390 */   113,   84,  110,  109,  108,  112,    6,  115,    4,   51,
 /*   400 */   191,  191,  191,  113,   60,  110,  109,  108,  191,  115,
 /*   410 */    38,   37,   36,   35,  115,  113,   78,  110,  109,  108,
 /*   420 */   113,  191,  110,  109,  108,  191,  115,   91,  191,  103,
 /*   430 */    20,   18,  113,  191,  110,  109,  108,  115,   90,  191,
 /*   440 */   191,  191,  191,  113,  191,  110,  109,  108,  115,  191,
 /*   450 */    89,  191,  191,  191,  113,  191,  110,  109,  108,  191,
 /*   460 */   115,  191,   88,  191,  191,  191,  113,   87,  110,  109,
 /*   470 */   108,  191,  115,  191,  191,  191,  191,  115,  113,   67,
 /*   480 */   110,  109,  108,  113,  191,  110,  109,  108,  191,  115,
 /*   490 */    66,  191,  191,  191,  191,  113,  191,  110,  109,  108,
 /*   500 */   115,   71,  191,  191,  191,  191,  113,  191,  110,  109,
 /*   510 */   108,  115,  191,   70,  191,  191,  191,  113,  191,  110,
 /*   520 */   109,  108,  191,  115,  191,   69,  191,  191,  191,  113,
 /*   530 */    68,  110,  109,  108,  191,  115,  191,  191,  191,  191,
 /*   540 */   115,  113,   63,  110,  109,  108,  113,  191,  110,  109,
 /*   550 */   108,  191,  115,   62,  191,  191,  191,  191,  113,  191,
 /*   560 */   110,  109,  108,  115,   73,  191,  191,  191,  191,  113,
 /*   570 */   191,  110,  109,  108,  115,  191,   72,  191,  191,  191,
 /*   580 */   113,  191,  110,  109,  108,  191,  115,  191,   65,  191,
 /*   590 */   191,  191,  113,   64,  110,  109,  108,  191,  115,  191,
 /*   600 */   191,  191,  191,  115,  113,   86,  110,  109,  108,  113,
 /*   610 */   191,  110,  109,  108,  191,  115,   85,  191,  191,  191,
 /*   620 */   191,  113,  191,  110,  109,  108,  115,   50,  191,  191,
 /*   630 */   191,  191,  113,  191,  110,  109,  108,  115,  191,   59,
 /*   640 */   191,  191,  191,  113,  191,  110,  109,  108,  191,  115,
 /*   650 */   191,   49,  191,  191,  191,  113,   58,  110,  109,  108,
 /*   660 */   191,  115,  191,  191,  191,  191,  115,  113,   47,  110,
 /*   670 */   109,  108,  113,  191,  110,  109,  108,  191,  115,   46,
 /*   680 */   191,  191,  191,  191,  113,  191,  110,  109,  108,  115,
 /*   690 */    57,  191,  191,  191,  191,  113,  191,  110,  109,  108,
 /*   700 */   115,  191,   56,  191,  191,  191,  113,  191,  110,  109,
 /*   710 */   108,  191,  115,  191,   45,  191,  191,  191,  113,   55,
 /*   720 */   110,  109,  108,  191,  115,  191,  191,  191,  191,  115,
 /*   730 */   113,   44,  110,  109,  108,  113,  191,  110,  109,  108,
 /*   740 */   191,  115,   54,  191,  191,  191,  191,  113,  191,  110,
 /*   750 */   109,  108,  115,   53,  191,  191,  191,  191,  113,  191,
 /*   760 */   110,  109,  108,  115,  191,   52,  191,  191,  191,  113,
 /*   770 */   191,  110,  109,  108,  132,  115,  191,   48,  191,  191,
 /*   780 */   191,  113,  191,  110,  109,  108,  191,  115,  191,  191,
 /*   790 */   191,  191,  191,  113,  191,  110,  109,  108,  191,  191,
 /*   800 */     3,  191,  191,  191,  191,  191,  191,  132,  132,  132,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    10 */    15,   16,   17,   18,   19,   20,   21,   22,    1,   33,
 /*    20 */    27,   34,    5,    6,    7,    8,    9,   10,   11,   12,
 /*    30 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*    40 */    45,    1,    1,   22,   31,    5,    6,    7,    8,    9,
 /*    50 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*    60 */    20,   21,   22,    5,    6,    7,    8,    9,   10,   11,
 /*    70 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*    80 */    22,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*    90 */    16,   17,   18,   19,   20,   21,   22,   39,   35,   36,
 /*   100 */    37,   38,   39,    5,    6,    7,    8,    9,   10,   11,
 /*   110 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   120 */    22,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   130 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   41,
 /*   140 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   150 */    15,   16,   17,   18,   19,   20,   21,   22,   43,   43,
 /*   160 */    51,    1,    1,   54,   55,    5,    6,    7,    8,    9,
 /*   170 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   180 */    20,   21,   22,    1,    1,   39,   50,    5,    6,    7,
 /*   190 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   200 */    18,   19,   20,   21,   22,    6,    7,    8,    9,   10,
 /*   210 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   220 */    21,   22,   52,   73,   73,   73,   56,   57,   58,   59,
 /*   230 */    60,   61,   62,   73,   64,   65,   66,   67,   68,   73,
 /*   240 */    70,   71,   72,    8,    9,   10,   11,   12,   13,   14,
 /*   250 */    15,   16,   17,   18,   19,   20,   21,   22,    9,   10,
 /*   260 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   270 */    21,   22,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   280 */    19,   20,   21,   22,    0,   15,   16,   17,   18,   19,
 /*   290 */    20,   21,   22,   18,   52,   37,   73,   73,   23,   24,
 /*   300 */    42,   73,   18,   73,   62,   73,   73,   23,   24,   34,
 /*   310 */    68,   73,   70,   71,   72,   40,   73,   33,   34,   44,
 /*   320 */    73,   46,   47,   48,   49,   73,   73,   73,   44,   73,
 /*   330 */    46,   47,   48,   49,   18,   52,   73,   73,   73,   23,
 /*   340 */    24,   18,   73,   60,   28,   62,   23,   24,   73,   73,
 /*   350 */    34,   68,   73,   70,   71,   72,   73,   34,   73,   73,
 /*   360 */    44,   73,   46,   47,   48,   49,   73,   44,   73,   46,
 /*   370 */    47,   48,   49,   73,   52,   17,   18,   19,   20,   21,
 /*   380 */    22,   73,   60,   73,   62,   63,   73,   52,   73,   73,
 /*   390 */    68,   69,   70,   71,   72,   60,    1,   62,   63,   52,
 /*   400 */    73,   73,   73,   68,   52,   70,   71,   72,   73,   62,
 /*   410 */    19,   20,   21,   22,   62,   68,   52,   70,   71,   72,
 /*   420 */    68,   73,   70,   71,   72,   73,   62,   52,   73,   34,
 /*   430 */    35,   36,   68,   73,   70,   71,   72,   62,   52,   73,
 /*   440 */    73,   73,   73,   68,   73,   70,   71,   72,   62,   73,
 /*   450 */    52,   73,   73,   73,   68,   73,   70,   71,   72,   73,
 /*   460 */    62,   73,   52,   73,   73,   73,   68,   52,   70,   71,
 /*   470 */    72,   73,   62,   73,   73,   73,   73,   62,   68,   52,
 /*   480 */    70,   71,   72,   68,   73,   70,   71,   72,   73,   62,
 /*   490 */    52,   73,   73,   73,   73,   68,   73,   70,   71,   72,
 /*   500 */    62,   52,   73,   73,   73,   73,   68,   73,   70,   71,
 /*   510 */    72,   62,   73,   52,   73,   73,   73,   68,   73,   70,
 /*   520 */    71,   72,   73,   62,   73,   52,   73,   73,   73,   68,
 /*   530 */    52,   70,   71,   72,   73,   62,   73,   73,   73,   73,
 /*   540 */    62,   68,   52,   70,   71,   72,   68,   73,   70,   71,
 /*   550 */    72,   73,   62,   52,   73,   73,   73,   73,   68,   73,
 /*   560 */    70,   71,   72,   62,   52,   73,   73,   73,   73,   68,
 /*   570 */    73,   70,   71,   72,   62,   73,   52,   73,   73,   73,
 /*   580 */    68,   73,   70,   71,   72,   73,   62,   73,   52,   73,
 /*   590 */    73,   73,   68,   52,   70,   71,   72,   73,   62,   73,
 /*   600 */    73,   73,   73,   62,   68,   52,   70,   71,   72,   68,
 /*   610 */    73,   70,   71,   72,   73,   62,   52,   73,   73,   73,
 /*   620 */    73,   68,   73,   70,   71,   72,   62,   52,   73,   73,
 /*   630 */    73,   73,   68,   73,   70,   71,   72,   62,   73,   52,
 /*   640 */    73,   73,   73,   68,   73,   70,   71,   72,   73,   62,
 /*   650 */    73,   52,   73,   73,   73,   68,   52,   70,   71,   72,
 /*   660 */    73,   62,   73,   73,   73,   73,   62,   68,   52,   70,
 /*   670 */    71,   72,   68,   73,   70,   71,   72,   73,   62,   52,
 /*   680 */    73,   73,   73,   73,   68,   73,   70,   71,   72,   62,
 /*   690 */    52,   73,   73,   73,   73,   68,   73,   70,   71,   72,
 /*   700 */    62,   73,   52,   73,   73,   73,   68,   73,   70,   71,
 /*   710 */    72,   73,   62,   73,   52,   73,   73,   73,   68,   52,
 /*   720 */    70,   71,   72,   73,   62,   73,   73,   73,   73,   62,
 /*   730 */    68,   52,   70,   71,   72,   68,   73,   70,   71,   72,
 /*   740 */    73,   62,   52,   73,   73,   73,   73,   68,   73,   70,
 /*   750 */    71,   72,   62,   52,   73,   73,   73,   73,   68,   73,
 /*   760 */    70,   71,   72,   62,   73,   52,   73,   73,   73,   68,
 /*   770 */    73,   70,   71,   72,    1,   62,   73,   52,   73,   73,
 /*   780 */    73,   68,   73,   70,   71,   72,   73,   62,   73,   73,
 /*   790 */    73,   73,   73,   68,   73,   70,   71,   72,   73,   73,
 /*   800 */    27,   73,   73,   73,   73,   73,   73,   34,   35,   36,
};
#define YY_SHIFT_USE_DFLT (-15)
#define YY_SHIFT_COUNT (95)
#define YY_SHIFT_MIN   (-14)
#define YY_SHIFT_MAX   (773)
static const short yy_shift_ofst[] = {
 /*     0 */   136,  284,  323,  323,  316,  323,  275,  323,  323,  323,
 /*    10 */   323,  323,  323,  323,  323,  323,  323,  323,  323,  323,
 /*    20 */   323,  323,  323,  323,  323,  323,  323,  323,  323,  323,
 /*    30 */   323,  323,  323,  323,  323,  323,  323,  323,  323,  323,
 /*    40 */   323,  323,  323,  323,  182,  160,  116,   98,   58,   40,
 /*    50 */    17,   -5,  135,  135,  135,  135,  135,  135,  135,  135,
 /*    60 */   135,  135,  199,   74,  235,  249,  261,  261,  270,  270,
 /*    70 */   270,  270,  358,  358,   63,  773,  395,  391,  391,  258,
 /*    80 */   146,  183,  161,  115,   13,   21,   21,   21,   21,   21,
 /*    90 */    21,   21,   41,  -13,   -7,  -14,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (43)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (725)
static const short yy_reduce_ofst[] = {
 /*     0 */   109,  170,  322,  335,  283,  283,  725,  713,  701,  690,
 /*    10 */   679,  667,  662,  650,  638,  627,  616,  604,  599,  587,
 /*    20 */   575,  564,  553,  541,  536,  524,  512,  501,  490,  478,
 /*    30 */   473,  461,  449,  438,  427,  415,  410,  398,  386,  375,
 /*    40 */   364,  352,  347,  242,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   123,  189,  158,  189,  189,  159,  189,  189,  189,  189,
 /*    10 */   189,  189,  189,  189,  189,  189,  189,  189,  189,  189,
 /*    20 */   189,  189,  189,  189,  189,  189,  189,  189,  189,  189,
 /*    30 */   189,  189,  189,  189,  189,  189,  189,  189,  189,  189,
 /*    40 */   189,  189,  189,  189,  189,  189,  189,  189,  153,  189,
 /*    50 */   189,  189,  145,  144,  143,  141,  151,  150,  142,  140,
 /*    60 */   152,  130,  179,  178,  186,  185,  173,  172,  177,  176,
 /*    70 */   175,  174,  184,  183,  137,  133,  189,  166,  167,  136,
 /*    80 */   138,  189,  189,  189,  189,  182,  181,  171,  170,  169,
 /*    90 */   168,  180,  189,  189,  133,  189,  188,  187,  139,  147,
 /*   100 */   146,  149,  148,  131,  157,  165,  164,  163,  162,  161,
 /*   110 */   160,  155,  154,  156,  135,  134,  129,  128,  127,  126,
 /*   120 */   125,  124,
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
   46,  /*      LBRAC => OPENBRAC */
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
  "GUARD_S",       "WILDCARD_N",    "WILDCARD",      "WHERE",       
  "CASE",          "OF",            "N_TAB",         "POINTER",     
  "LET",           "IN",            "OPENBRAC",      "NUM",         
  "STRING",        "BOOLEAN",       "OPENQUOTEERROR",  "error",       
  "expr",          "id",            "main",          "in",          
  "start",         "spec",          "assignment",    "top_stmt",    
  "stmt",          "name_chain",    "function_call",  "stmt_list",   
  "case_statement",  "guard_statement",  "final_guard_statement",  "where_statement",
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
 /*  17 */ "spec ::= where_statement",
 /*  18 */ "guard_statement ::= name_chain GUARD_N expr ASSIGN expr",
 /*  19 */ "guard_statement ::= guard_statement GUARD_N expr ASSIGN expr",
 /*  20 */ "guard_statement ::= name_chain GUARD_S expr ASSIGN expr",
 /*  21 */ "guard_statement ::= guard_statement GUARD_S expr ASSIGN expr",
 /*  22 */ "final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr",
 /*  23 */ "final_guard_statement ::= guard_statement WILDCARD ASSIGN expr",
 /*  24 */ "where_statement ::= guard_statement WHERE",
 /*  25 */ "where_statement ::= final_guard_statement WHERE",
 /*  26 */ "where_statement ::= name_chain ASSIGN expr WHERE",
 /*  27 */ "case_statement ::= name_chain ASSIGN CASE expr OF",
 /*  28 */ "case_statement ::= case_statement N_TAB expr POINTER expr",
 /*  29 */ "case_statement ::= case_statement WILDCARD_N POINTER expr",
 /*  30 */ "expr ::= LET NAME ASSIGN expr IN expr",
 /*  31 */ "assignment ::= name_chain ASSIGN expr",
 /*  32 */ "stmt_list ::= stmt",
 /*  33 */ "stmt_list ::= stmt_list stmt",
 /*  34 */ "expr ::= array",
 /*  35 */ "array ::= OPENBRAC maybe_empty_stmt_list RBRAC",
 /*  36 */ "maybe_empty_stmt_list ::=",
 /*  37 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  38 */ "expr ::= num",
 /*  39 */ "expr ::= string",
 /*  40 */ "expr ::= bool",
 /*  41 */ "num ::= NUM",
 /*  42 */ "string ::= STRING",
 /*  43 */ "bool ::= BOOLEAN",
 /*  44 */ "expr ::= expr PLUS expr",
 /*  45 */ "expr ::= expr MINUS expr",
 /*  46 */ "expr ::= expr DIVIDE expr",
 /*  47 */ "expr ::= expr TIMES expr",
 /*  48 */ "expr ::= expr MODULO expr",
 /*  49 */ "expr ::= expr POW expr",
 /*  50 */ "expr ::= expr EQUALTO expr",
 /*  51 */ "expr ::= expr NOTEQUALTO expr",
 /*  52 */ "expr ::= expr LESSTHAN expr",
 /*  53 */ "expr ::= expr GREATERTHAN expr",
 /*  54 */ "expr ::= expr LORE expr",
 /*  55 */ "expr ::= expr GORE expr",
 /*  56 */ "expr ::= expr AND expr",
 /*  57 */ "expr ::= expr OR expr",
 /*  58 */ "expr ::= BITNOT expr",
 /*  59 */ "expr ::= MINUS expr",
 /*  60 */ "expr ::= NOT expr",
 /*  61 */ "expr ::= expr SHIFTL expr",
 /*  62 */ "expr ::= expr SHIFTR expr",
 /*  63 */ "expr ::= expr BITAND expr",
 /*  64 */ "expr ::= expr BITXOR expr",
 /*  65 */ "in ::= error",
 /*  66 */ "error ::= OPENQUOTEERROR",
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
    case 39: /* WHERE */
    case 40: /* CASE */
    case 41: /* OF */
    case 42: /* N_TAB */
    case 43: /* POINTER */
    case 44: /* LET */
    case 45: /* IN */
    case 46: /* OPENBRAC */
    case 47: /* NUM */
    case 48: /* STRING */
    case 49: /* BOOLEAN */
    case 50: /* OPENQUOTEERROR */
{
#line 43 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 739 "./src/Grammar/grammar.c"
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
  { 54, 1 },
  { 55, 0 },
  { 55, 2 },
  { 55, 3 },
  { 56, 1 },
  { 57, 1 },
  { 57, 1 },
  { 59, 1 },
  { 60, 1 },
  { 61, 2 },
  { 61, 1 },
  { 52, 1 },
  { 52, 1 },
  { 62, 4 },
  { 57, 1 },
  { 57, 1 },
  { 57, 1 },
  { 57, 1 },
  { 65, 5 },
  { 65, 5 },
  { 65, 5 },
  { 65, 5 },
  { 66, 4 },
  { 66, 4 },
  { 67, 2 },
  { 67, 2 },
  { 67, 4 },
  { 64, 5 },
  { 64, 5 },
  { 64, 4 },
  { 52, 6 },
  { 58, 3 },
  { 63, 1 },
  { 63, 2 },
  { 52, 1 },
  { 68, 3 },
  { 69, 0 },
  { 69, 1 },
  { 52, 1 },
  { 52, 1 },
  { 52, 1 },
  { 70, 1 },
  { 71, 1 },
  { 72, 1 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 2 },
  { 52, 2 },
  { 52, 2 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 55, 1 },
  { 51, 1 },
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
#line 1104 "./src/Grammar/grammar.c"
        break;
      case 4: /* start ::= spec */
#line 89 "./src/Grammar/grammar.y"
{
    if(
        yymsp[0].minor.yy0.type == optic::NUMBER ||
        yymsp[0].minor.yy0.type == optic::STRING ||
        yymsp[0].minor.yy0.type == optic::BOOL ||
        yymsp[0].minor.yy0.type == optic::GUARD
        )
    {
        print_object(yymsp[0].minor.yy0);
    }
    else
    {
        optic::resolve_stack_from_parser(yymsp[0].minor.yy0);
    }
}
#line 1123 "./src/Grammar/grammar.c"
        break;
      case 5: /* spec ::= assignment */
      case 38: /* expr ::= num */ yytestcase(yyruleno==38);
      case 40: /* expr ::= bool */ yytestcase(yyruleno==40);
#line 107 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1132 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= top_stmt */
      case 7: /* top_stmt ::= stmt */ yytestcase(yyruleno==7);
      case 39: /* expr ::= string */ yytestcase(yyruleno==39);
#line 119 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1142 "./src/Grammar/grammar.c"
        break;
      case 8: /* stmt ::= expr */
      case 32: /* stmt_list ::= stmt */ yytestcase(yyruleno==32);
#line 131 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1151 "./src/Grammar/grammar.c"
        break;
      case 9: /* name_chain ::= name_chain NAME */
#line 137 "./src/Grammar/grammar.y"
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
#line 1190 "./src/Grammar/grammar.c"
        break;
      case 10: /* name_chain ::= NAME */
#line 174 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1199 "./src/Grammar/grammar.c"
        break;
      case 11: /* expr ::= NAME */
#line 181 "./src/Grammar/grammar.y"
{
/*    panopticon::retrieve_variable(yygotominor.yy0,yymsp[0].minor.yy0);*/
    yymsp[0].minor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1213 "./src/Grammar/grammar.c"
        break;
      case 12: /* expr ::= function_call */
      case 34: /* expr ::= array */ yytestcase(yyruleno==34);
#line 193 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1221 "./src/Grammar/grammar.c"
        break;
      case 13: /* function_call ::= NAME LPAREN stmt_list RPAREN */
#line 198 "./src/Grammar/grammar.y"
{
    // yygotominor.yy0.scope = optic::get_scope();
    if(yymsp[-1].minor.yy0.type==optic::STATEMENT_LIST)
    {
            yymsp[-1].minor.yy0.type = optic::ARRAY;
            optic::out() << "Received a malformed argument to the function: " << *yymsp[-3].minor.yy0.data.string;
    }
    else
    {
        optic::object temp = yymsp[-1].minor.yy0;
        yymsp[-1].minor.yy0.type = optic::ARRAY;
        yymsp[-1].minor.yy0.data.array = new optic::Array();
        yymsp[-1].minor.yy0.data.array->reserve(1);
        yymsp[-1].minor.yy0.data.array->push_back(temp);
    }
    optic::object b;
    b.type = optic::STRING;
    std::cout << "FUNCTION_CALL yymsp[-3].minor.yy0.data.string " << *yymsp[-3].minor.yy0.data.string << std::endl;
    b.data.string = new optic::String(yymsp[-3].minor.yy0.data.string->c_str());
    optic::parse_operations(yygotominor.yy0,b,yymsp[-1].minor.yy0,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,27,&yymsp[-2].minor);
  yy_destructor(yypParser,28,&yymsp[0].minor);
}
#line 1253 "./src/Grammar/grammar.c"
        break;
      case 14: /* spec ::= case_statement */
#line 226 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Case: " << *yymsp[0].minor.yy0.data.array->at(0).data.string << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1261 "./src/Grammar/grammar.c"
        break;
      case 15: /* spec ::= guard_statement */
      case 16: /* spec ::= final_guard_statement */ yytestcase(yyruleno==16);
#line 233 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Guard: " << *yymsp[0].minor.yy0.data.array->at(0).data.string << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1270 "./src/Grammar/grammar.c"
        break;
      case 17: /* spec ::= where_statement */
#line 245 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Where: " << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1278 "./src/Grammar/grammar.c"
        break;
      case 18: /* guard_statement ::= name_chain GUARD_N expr ASSIGN expr */
      case 19: /* guard_statement ::= guard_statement GUARD_N expr ASSIGN expr */ yytestcase(yyruleno==19);
#line 251 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,35,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1289 "./src/Grammar/grammar.c"
        break;
      case 20: /* guard_statement ::= name_chain GUARD_S expr ASSIGN expr */
      case 21: /* guard_statement ::= guard_statement GUARD_S expr ASSIGN expr */ yytestcase(yyruleno==21);
#line 263 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1300 "./src/Grammar/grammar.c"
        break;
      case 22: /* final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr */
#line 275 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1310 "./src/Grammar/grammar.c"
        break;
      case 23: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr */
#line 281 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,38,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1320 "./src/Grammar/grammar.c"
        break;
      case 24: /* where_statement ::= guard_statement WHERE */
      case 25: /* where_statement ::= final_guard_statement WHERE */ yytestcase(yyruleno==25);
#line 286 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1328 "./src/Grammar/grammar.c"
        break;
      case 26: /* where_statement ::= name_chain ASSIGN expr WHERE */
#line 288 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1336 "./src/Grammar/grammar.c"
        break;
      case 27: /* case_statement ::= name_chain ASSIGN CASE expr OF */
#line 291 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,40,&yymsp[-2].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1347 "./src/Grammar/grammar.c"
        break;
      case 28: /* case_statement ::= case_statement N_TAB expr POINTER expr */
#line 297 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,42,&yymsp[-3].minor);
  yy_destructor(yypParser,43,&yymsp[-1].minor);
}
#line 1357 "./src/Grammar/grammar.c"
        break;
      case 29: /* case_statement ::= case_statement WILDCARD_N POINTER expr */
#line 303 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,43,&yymsp[-1].minor);
}
#line 1367 "./src/Grammar/grammar.c"
        break;
      case 30: /* expr ::= LET NAME ASSIGN expr IN expr */
#line 309 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Let");
  yy_destructor(yypParser,44,&yymsp[-5].minor);
  yy_destructor(yypParser,34,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,45,&yymsp[-1].minor);
}
#line 1379 "./src/Grammar/grammar.c"
        break;
      case 31: /* assignment ::= name_chain ASSIGN expr */
#line 322 "./src/Grammar/grammar.y"
{
    // yymsp[-2].minor.yy0.type = panopticon::ARRAY;
    // yymsp[0].minor.yy0.type = panopticon::OPERATION_TREE;
    // yymsp[-2].minor.yy0.type = FUNCTION_DEC;
    // std::cout << "Function_Dec yymsp[0].minor.yy0: " << yymsp[0].minor.yy0.type << std::endl;
    // panopticon::parse_operations(yygotominor.yy0, yymsp[-2].minor.yy0, yymsp[0].minor.yy0, panopticon::create_function);
    yymsp[0].minor.yy0.type = panopticon::FUNCTION_BODY;
    panopticon::parse_operations(yygotominor.yy0, yymsp[-2].minor.yy0, yymsp[0].minor.yy0, panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1398 "./src/Grammar/grammar.c"
        break;
      case 33: /* stmt_list ::= stmt_list stmt */
#line 348 "./src/Grammar/grammar.y"
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
#line 1417 "./src/Grammar/grammar.c"
        break;
      case 35: /* array ::= OPENBRAC maybe_empty_stmt_list RBRAC */
#line 378 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::ARRAY;
    yygotominor.yy0.data.array = yymsp[-1].minor.yy0.data.array;
  yy_destructor(yypParser,46,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1427 "./src/Grammar/grammar.c"
        break;
      case 36: /* maybe_empty_stmt_list ::= */
#line 384 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1435 "./src/Grammar/grammar.c"
        break;
      case 37: /* maybe_empty_stmt_list ::= stmt_list */
#line 390 "./src/Grammar/grammar.y"
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
#line 1451 "./src/Grammar/grammar.c"
        break;
      case 41: /* num ::= NUM */
#line 442 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.type = panopticon::NUMBER;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1460 "./src/Grammar/grammar.c"
        break;
      case 42: /* string ::= STRING */
#line 449 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1470 "./src/Grammar/grammar.c"
        break;
      case 43: /* bool ::= BOOLEAN */
#line 458 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    yygotominor.yy0.type = panopticon::BOOL;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1479 "./src/Grammar/grammar.c"
        break;
      case 44: /* expr ::= expr PLUS expr */
#line 490 "./src/Grammar/grammar.y"
{
    std::cout << "Plus yymsp[-2].minor.yy0: " << yymsp[-2].minor.yy0.type << std::endl;
    std::cout << "Plus yymsp[0].minor.yy0: " << yymsp[0].minor.yy0.type << std::endl;
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::plus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1494 "./src/Grammar/grammar.c"
        break;
      case 45: /* expr ::= expr MINUS expr */
#line 502 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1507 "./src/Grammar/grammar.c"
        break;
      case 46: /* expr ::= expr DIVIDE expr */
#line 512 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1520 "./src/Grammar/grammar.c"
        break;
      case 47: /* expr ::= expr TIMES expr */
#line 522 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1533 "./src/Grammar/grammar.c"
        break;
      case 48: /* expr ::= expr MODULO expr */
#line 532 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1546 "./src/Grammar/grammar.c"
        break;
      case 49: /* expr ::= expr POW expr */
#line 542 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1559 "./src/Grammar/grammar.c"
        break;
      case 50: /* expr ::= expr EQUALTO expr */
#line 552 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1572 "./src/Grammar/grammar.c"
        break;
      case 51: /* expr ::= expr NOTEQUALTO expr */
#line 562 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1585 "./src/Grammar/grammar.c"
        break;
      case 52: /* expr ::= expr LESSTHAN expr */
#line 572 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1598 "./src/Grammar/grammar.c"
        break;
      case 53: /* expr ::= expr GREATERTHAN expr */
#line 582 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1611 "./src/Grammar/grammar.c"
        break;
      case 54: /* expr ::= expr LORE expr */
#line 592 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1624 "./src/Grammar/grammar.c"
        break;
      case 55: /* expr ::= expr GORE expr */
#line 602 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1637 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr AND expr */
#line 612 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1650 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr OR expr */
#line 622 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1663 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= BITNOT expr */
#line 632 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1676 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= MINUS expr */
#line 642 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1689 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= NOT expr */
#line 652 "./src/Grammar/grammar.y"
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
#line 1703 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= expr SHIFTL expr */
#line 663 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1716 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= expr SHIFTR expr */
#line 673 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1729 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= expr BITAND expr */
#line 683 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1742 "./src/Grammar/grammar.c"
        break;
      case 64: /* expr ::= expr BITXOR expr */
#line 703 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1755 "./src/Grammar/grammar.c"
        break;
      case 65: /* in ::= error */
#line 754 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy147)
    {
    case panopticon::OpenQuoteError:
/*        panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        panopticon::out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 1770 "./src/Grammar/grammar.c"
        break;
      case 66: /* error ::= OPENQUOTEERROR */
#line 767 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy147 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1779 "./src/Grammar/grammar.c"
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
#line 1846 "./src/Grammar/grammar.c"
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
#line 1868 "./src/Grammar/grammar.c"
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
