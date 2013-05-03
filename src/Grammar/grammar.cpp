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
#define YYNOCODE 79
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy157;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 139
#define YYNRULE 74
#define YYERRORSYMBOL 53
#define YYERRSYMDT yy157
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
#define YY_ACTTAB_COUNT (802)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    31,   32,   27,   28,   38,   37,   35,   33,   36,   34,
 /*    10 */    30,   29,   47,   44,   42,   41,   40,   39,   31,   32,
 /*    20 */    27,   28,   38,   37,   35,   33,   36,   34,   30,   29,
 /*    30 */    47,   44,   42,   41,   40,   39,   47,   44,   42,   41,
 /*    40 */    40,   39,   45,   30,   29,   47,   44,   42,   41,   40,
 /*    50 */    39,    2,    5,  112,  115,  108,   21,  137,  214,    1,
 /*    60 */    31,   32,   27,   28,   38,   37,   35,   33,   36,   34,
 /*    70 */    30,   29,   47,   44,   42,   41,   40,   39,   19,  111,
 /*    80 */    82,  136,   31,   32,   27,   28,   38,   37,   35,   33,
 /*    90 */    36,   34,   30,   29,   47,   44,   42,   41,   40,   39,
 /*   100 */    17,  102,   46,   39,   31,   32,   27,   28,   38,   37,
 /*   110 */    35,   33,   36,   34,   30,   29,   47,   44,   42,   41,
 /*   120 */    40,   39,   13,  118,   92,   23,   31,   32,   27,   28,
 /*   130 */    38,   37,   35,   33,   36,   34,   30,   29,   47,   44,
 /*   140 */    42,   41,   40,   39,   31,   32,   27,   28,   38,   37,
 /*   150 */    35,   33,   36,   34,   30,   29,   47,   44,   42,   41,
 /*   160 */    40,   39,   31,   32,   27,   28,   38,   37,   35,   33,
 /*   170 */    36,   34,   30,   29,   47,   44,   42,   41,   40,   39,
 /*   180 */    16,   15,  110,   20,   18,   91,   90,  114,  113,   67,
 /*   190 */     9,  215,  107,  106,  105,  135,  134,   87,  131,  130,
 /*   200 */   129,   48,   10,   85,   93,  109,   89,   80,  127,  215,
 /*   210 */   124,  123,  122,   31,   32,   27,   28,   38,   37,   35,
 /*   220 */    33,   36,   34,   30,   29,   47,   44,   42,   41,   40,
 /*   230 */    39,   32,   27,   28,   38,   37,   35,   33,   36,   34,
 /*   240 */    30,   29,   47,   44,   42,   41,   40,   39,   27,   28,
 /*   250 */    38,   37,   35,   33,   36,   34,   30,   29,   47,   44,
 /*   260 */    42,   41,   40,   39,   28,   38,   37,   35,   33,   36,
 /*   270 */    34,   30,   29,   47,   44,   42,   41,   40,   39,  215,
 /*   280 */    67,   42,   41,   40,   39,   24,  133,  134,   87,  131,
 /*   290 */   130,  129,   86,  215,  215,   93,  215,   89,   80,  127,
 /*   300 */    67,  124,  123,  122,  215,  215,  132,  134,   87,  131,
 /*   310 */   130,  129,   86,  215,  154,   93,  215,   89,   80,  127,
 /*   320 */   116,  124,  123,  122,  139,   38,   37,   35,   33,   36,
 /*   330 */    34,   30,   29,   47,   44,   42,   41,   40,   39,  215,
 /*   340 */     5,   88,   26,  215,   67,  215,   11,   25,   43,  154,
 /*   350 */   154,  154,  215,  215,  215,  125,  215,  138,    3,  215,
 /*   360 */    81,   22,   14,  127,  215,  124,  123,  122,    8,  215,
 /*   370 */   103,  215,    4,  121,  120,  119,   20,   18,   91,   90,
 /*   380 */   215,  215,   35,   33,   36,   34,   30,   29,   47,   44,
 /*   390 */    42,   41,   40,   39,   26,  215,  215,  215,  215,   25,
 /*   400 */    43,  215,  215,  116,   22,   14,  215,  215,  215,  215,
 /*   410 */     3,   26,   81,   22,   14,   83,   25,   43,  215,  215,
 /*   420 */   215,  215,  103,  215,    4,  121,  120,  119,  215,  104,
 /*   430 */   215,  215,  215,  215,  127,   12,  124,  123,  122,  103,
 /*   440 */   215,    4,  121,  120,  119,   26,  215,  215,  215,  215,
 /*   450 */    25,   43,  215,  215,   26,  128,  215,  215,  215,   25,
 /*   460 */    43,   26,  215,  104,  117,  215,   25,   43,  215,  215,
 /*   470 */   215,  215,  104,  103,  215,    4,  121,  120,  119,  104,
 /*   480 */    56,  215,  103,  215,    4,  121,  120,  119,  215,  103,
 /*   490 */   215,    4,  121,  120,  119,  215,   67,  215,  215,  127,
 /*   500 */   215,  124,  123,  122,  215,   66,  215,  126,  215,    7,
 /*   510 */    67,  215,  215,  215,  215,  127,   94,  124,  123,  122,
 /*   520 */   215,  126,   84,    6,  127,  215,  124,  123,  122,  127,
 /*   530 */   101,  124,  123,  122,  215,  100,  215,  215,  215,  215,
 /*   540 */    99,  127,  215,  124,  123,  122,   98,  215,  215,  127,
 /*   550 */   215,  124,  123,  122,  127,  215,  124,  123,  122,  127,
 /*   560 */    97,  124,  123,  122,  215,  127,  215,  124,  123,  122,
 /*   570 */    73,  215,  215,  215,  215,  215,   72,  215,  215,  127,
 /*   580 */   215,  124,  123,  122,   77,  215,  215,  215,  215,  127,
 /*   590 */    76,  124,  123,  122,  215,  127,   75,  124,  123,  122,
 /*   600 */   215,   74,  215,  127,  215,  124,  123,  122,   69,  127,
 /*   610 */   215,  124,  123,  122,   68,  127,  215,  124,  123,  122,
 /*   620 */   127,  215,  124,  123,  122,   79,  215,  127,  215,  124,
 /*   630 */   123,  122,  215,  127,   78,  124,  123,  122,  215,   71,
 /*   640 */   215,  215,  215,  215,  127,   70,  124,  123,  122,  215,
 /*   650 */    96,  215,  215,  127,  215,  124,  123,  122,  127,  215,
 /*   660 */   124,  123,  122,   95,  127,  215,  124,  123,  122,  127,
 /*   670 */    55,  124,  123,  122,  215,   65,  215,  215,  215,  215,
 /*   680 */    54,  215,  127,  215,  124,  123,  122,  215,   64,  127,
 /*   690 */   215,  124,  123,  122,  127,  215,  124,  123,  122,  127,
 /*   700 */    53,  124,  123,  122,  215,   63,  215,  127,  215,  124,
 /*   710 */   123,  122,   52,  215,  215,  215,  215,   62,  215,  127,
 /*   720 */   215,  124,  123,  122,  127,   61,  124,  123,  122,  215,
 /*   730 */    60,  127,  215,  124,  123,  122,  127,   51,  124,  123,
 /*   740 */   122,  215,  215,   59,  127,  215,  124,  123,  122,  127,
 /*   750 */   215,  124,  123,  122,   50,  215,  127,  215,  124,  123,
 /*   760 */   122,  215,  127,  215,  124,  123,  122,   49,  215,  215,
 /*   770 */   215,  215,   58,  127,  215,  124,  123,  122,   57,  215,
 /*   780 */   215,  215,  215,  215,  215,  215,  127,  215,  124,  123,
 /*   790 */   122,  127,  215,  124,  123,  122,  215,  127,  215,  124,
 /*   800 */   123,  122,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    10 */    15,   16,   17,   18,   19,   20,   21,   22,    5,    6,
 /*    20 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*    30 */    17,   18,   19,   20,   21,   22,   17,   18,   19,   20,
 /*    40 */    21,   22,   47,   15,   16,   17,   18,   19,   20,   21,
 /*    50 */    22,   33,   27,   35,   41,   53,    1,   33,   56,   57,
 /*    60 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    70 */    15,   16,   17,   18,   19,   20,   21,   22,    1,   71,
 /*    80 */    72,   33,    5,    6,    7,    8,    9,   10,   11,   12,
 /*    90 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   100 */     1,   36,    1,   22,    5,    6,    7,    8,    9,   10,
 /*   110 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   120 */    21,   22,    1,   31,   36,    1,    5,    6,    7,    8,
 /*   130 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   140 */    19,   20,   21,   22,    5,    6,    7,    8,    9,   10,
 /*   150 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   160 */    21,   22,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   170 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   180 */     1,    1,   43,   37,   38,   39,   40,   41,   41,   54,
 /*   190 */    45,   78,   52,   58,   59,   60,   61,   62,   63,   64,
 /*   200 */    65,   66,   45,   68,   69,   70,   71,   72,   73,   78,
 /*   210 */    75,   76,   77,    5,    6,    7,    8,    9,   10,   11,
 /*   220 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   230 */    22,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   240 */    15,   16,   17,   18,   19,   20,   21,   22,    7,    8,
 /*   250 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   260 */    19,   20,   21,   22,    8,    9,   10,   11,   12,   13,
 /*   270 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   78,
 /*   280 */    54,   19,   20,   21,   22,    1,   60,   61,   62,   63,
 /*   290 */    64,   65,   66,   78,   78,   69,   78,   71,   72,   73,
 /*   300 */    54,   75,   76,   77,   78,   78,   60,   61,   62,   63,
 /*   310 */    64,   65,   66,   78,    1,   69,   78,   71,   72,   73,
 /*   320 */    36,   75,   76,   77,    0,    9,   10,   11,   12,   13,
 /*   330 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   78,
 /*   340 */    27,   39,   18,   78,   54,   78,   44,   23,   24,   36,
 /*   350 */    37,   38,   78,   78,   78,   65,   78,   33,   34,   78,
 /*   360 */    36,   37,   38,   73,   78,   75,   76,   77,    1,   78,
 /*   370 */    46,   78,   48,   49,   50,   51,   37,   38,   39,   40,
 /*   380 */    78,   78,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   390 */    19,   20,   21,   22,   18,   78,   78,   78,   78,   23,
 /*   400 */    24,   78,   78,   36,   37,   38,   78,   78,   78,   78,
 /*   410 */    34,   18,   36,   37,   38,   54,   23,   24,   78,   78,
 /*   420 */    78,   78,   46,   78,   48,   49,   50,   51,   78,   36,
 /*   430 */    78,   78,   78,   78,   73,   42,   75,   76,   77,   46,
 /*   440 */    78,   48,   49,   50,   51,   18,   78,   78,   78,   78,
 /*   450 */    23,   24,   78,   78,   18,   28,   78,   78,   78,   23,
 /*   460 */    24,   18,   78,   36,   28,   78,   23,   24,   78,   78,
 /*   470 */    78,   78,   36,   46,   78,   48,   49,   50,   51,   36,
 /*   480 */    54,   78,   46,   78,   48,   49,   50,   51,   78,   46,
 /*   490 */    78,   48,   49,   50,   51,   78,   54,   78,   78,   73,
 /*   500 */    78,   75,   76,   77,   78,   54,   78,   65,   78,   67,
 /*   510 */    54,   78,   78,   78,   78,   73,   74,   75,   76,   77,
 /*   520 */    78,   65,   54,   67,   73,   78,   75,   76,   77,   73,
 /*   530 */    54,   75,   76,   77,   78,   54,   78,   78,   78,   78,
 /*   540 */    54,   73,   78,   75,   76,   77,   54,   78,   78,   73,
 /*   550 */    78,   75,   76,   77,   73,   78,   75,   76,   77,   73,
 /*   560 */    54,   75,   76,   77,   78,   73,   78,   75,   76,   77,
 /*   570 */    54,   78,   78,   78,   78,   78,   54,   78,   78,   73,
 /*   580 */    78,   75,   76,   77,   54,   78,   78,   78,   78,   73,
 /*   590 */    54,   75,   76,   77,   78,   73,   54,   75,   76,   77,
 /*   600 */    78,   54,   78,   73,   78,   75,   76,   77,   54,   73,
 /*   610 */    78,   75,   76,   77,   54,   73,   78,   75,   76,   77,
 /*   620 */    73,   78,   75,   76,   77,   54,   78,   73,   78,   75,
 /*   630 */    76,   77,   78,   73,   54,   75,   76,   77,   78,   54,
 /*   640 */    78,   78,   78,   78,   73,   54,   75,   76,   77,   78,
 /*   650 */    54,   78,   78,   73,   78,   75,   76,   77,   73,   78,
 /*   660 */    75,   76,   77,   54,   73,   78,   75,   76,   77,   73,
 /*   670 */    54,   75,   76,   77,   78,   54,   78,   78,   78,   78,
 /*   680 */    54,   78,   73,   78,   75,   76,   77,   78,   54,   73,
 /*   690 */    78,   75,   76,   77,   73,   78,   75,   76,   77,   73,
 /*   700 */    54,   75,   76,   77,   78,   54,   78,   73,   78,   75,
 /*   710 */    76,   77,   54,   78,   78,   78,   78,   54,   78,   73,
 /*   720 */    78,   75,   76,   77,   73,   54,   75,   76,   77,   78,
 /*   730 */    54,   73,   78,   75,   76,   77,   73,   54,   75,   76,
 /*   740 */    77,   78,   78,   54,   73,   78,   75,   76,   77,   73,
 /*   750 */    78,   75,   76,   77,   54,   78,   73,   78,   75,   76,
 /*   760 */    77,   78,   73,   78,   75,   76,   77,   54,   78,   78,
 /*   770 */    78,   78,   54,   73,   78,   75,   76,   77,   54,   78,
 /*   780 */    78,   78,   78,   78,   78,   78,   73,   78,   75,   76,
 /*   790 */    77,   73,   78,   75,   76,   77,   78,   73,   78,   75,
 /*   800 */    76,   77,
};
#define YY_SHIFT_USE_DFLT (-6)
#define YY_SHIFT_COUNT (106)
#define YY_SHIFT_MIN   (-5)
#define YY_SHIFT_MAX   (443)
static const short yy_shift_ofst[] = {
 /*     0 */   140,  324,  376,  376,  443,  436,  427,  443,  393,  443,
 /*    10 */   443,  443,  443,  443,  443,  443,  443,  443,  443,  443,
 /*    20 */   443,  443,  443,  443,  443,  443,  443,  443,  443,  443,
 /*    30 */   443,  443,  443,  443,  443,  443,  443,  443,  443,  443,
 /*    40 */   443,  443,  443,  443,  443,  443,  443,  443,  367,  157,
 /*    50 */   139,  121,   99,   77,   55,   13,   -5,  208,  208,  208,
 /*    60 */   208,  208,  208,  208,  208,  208,  208,  208,  225,  241,
 /*    70 */   256,  316,  371,  371,   28,   28,   28,   28,   19,   19,
 /*    80 */   146,  313,  339,  262,  262,  302,  284,   18,  145,  147,
 /*    90 */   180,  179,  124,   88,   92,   81,   81,   81,   81,   81,
 /*   100 */    81,   81,  101,   65,   25,   48,   24,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (48)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (724)
static const short yy_reduce_ofst[] = {
 /*     0 */     2,  135,  246,  226,  442,  456,  290,  290,  616,  724,
 /*    10 */   718,  713,  700,  689,  683,  676,  671,  663,  658,  651,
 /*    20 */   646,  634,  626,  621,  616,  609,  596,  591,  585,  580,
 /*    30 */   571,  560,  554,  547,  542,  536,  530,  522,  516,  506,
 /*    40 */   492,  486,  481,  476,  468,  451,  426,  361,    8,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   140,  213,  213,  213,  182,  213,  213,  183,  213,  213,
 /*    10 */   213,  213,  213,  213,  213,  213,  213,  213,  213,  213,
 /*    20 */   213,  213,  213,  213,  213,  213,  213,  213,  213,  213,
 /*    30 */   213,  213,  213,  213,  213,  213,  213,  213,  213,  213,
 /*    40 */   213,  213,  213,  213,  213,  213,  213,  213,  213,  213,
 /*    50 */   213,  213,  213,  213,  213,  177,  213,  175,  174,  165,
 /*    60 */   168,  167,  166,  164,  163,  172,  176,  152,  203,  202,
 /*    70 */   210,  209,  197,  196,  201,  200,  199,  198,  208,  207,
 /*    80 */   213,  155,  162,  190,  191,  158,  213,  213,  213,  213,
 /*    90 */   213,  213,  213,  159,  213,  206,  205,  195,  194,  193,
 /*   100 */   192,  204,  213,  213,  155,  213,  213,  212,  211,  160,
 /*   110 */   173,  161,  148,  170,  169,  171,  153,  157,  181,  189,
 /*   120 */   188,  187,  186,  185,  184,  179,  178,  180,  156,  151,
 /*   130 */   150,  149,  147,  146,  145,  144,  143,  142,  141,
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
   48,  /*      LBRAC => OPENBRAC */
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
  "COLLECTARRAY",  "NEWLINE",       "OPENING_LPAREN",  "CLOSING_RPAREN",
  "NAME",          "GUARD_N",       "GUARD_S",       "WILDCARD_N",  
  "WILDCARD",      "WHERE",         "CASE",          "OF",          
  "N_TAB",         "POINTER",       "LET",           "IN",          
  "OPENBRAC",      "NUM",           "STRING",        "BOOLEAN",     
  "OPENQUOTEERROR",  "error",         "expr",          "id",          
  "main",          "in",            "start",         "test",        
  "spec",          "closed_block",  "open_block",    "assignment",  
  "top_stmt",      "stmt",          "name_chain",    "stmt_list",   
  "case_statement",  "where_statement",  "guard_assignment",  "final_guard_statement",
  "guard_statement",  "array",         "maybe_empty_stmt_list",  "num",         
  "string",        "bool",        
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
 /*   4 */ "in ::= in test NEWLINE",
 /*   5 */ "start ::= spec",
 /*   6 */ "spec ::= closed_block",
 /*   7 */ "open_block ::= OPENING_LPAREN spec",
 /*   8 */ "open_block ::= open_block NEWLINE spec",
 /*   9 */ "closed_block ::= open_block CLOSING_RPAREN",
 /*  10 */ "spec ::= assignment",
 /*  11 */ "spec ::= top_stmt",
 /*  12 */ "top_stmt ::= stmt",
 /*  13 */ "stmt ::= expr",
 /*  14 */ "name_chain ::= name_chain NAME",
 /*  15 */ "name_chain ::= NAME",
 /*  16 */ "expr ::= NAME",
 /*  17 */ "expr ::= NAME LPAREN stmt_list RPAREN",
 /*  18 */ "expr ::= NAME LPAREN RPAREN",
 /*  19 */ "test ::= case_statement",
 /*  20 */ "spec ::= where_statement",
 /*  21 */ "test ::= guard_assignment",
 /*  22 */ "guard_assignment ::= name_chain final_guard_statement",
 /*  23 */ "guard_assignment ::= name_chain guard_statement",
 /*  24 */ "guard_statement ::= GUARD_N expr ASSIGN expr",
 /*  25 */ "guard_statement ::= guard_statement GUARD_N expr ASSIGN expr",
 /*  26 */ "guard_statement ::= GUARD_S expr ASSIGN expr",
 /*  27 */ "guard_statement ::= guard_statement GUARD_S expr ASSIGN expr",
 /*  28 */ "final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr",
 /*  29 */ "final_guard_statement ::= guard_statement WILDCARD ASSIGN expr",
 /*  30 */ "where_statement ::= guard_statement WHERE",
 /*  31 */ "where_statement ::= final_guard_statement WHERE",
 /*  32 */ "where_statement ::= name_chain ASSIGN expr WHERE",
 /*  33 */ "where_statement ::= where_statement NAME ASSIGN expr",
 /*  34 */ "case_statement ::= name_chain ASSIGN CASE expr OF",
 /*  35 */ "case_statement ::= case_statement N_TAB expr POINTER expr",
 /*  36 */ "case_statement ::= case_statement WILDCARD_N POINTER expr",
 /*  37 */ "expr ::= LET NAME ASSIGN expr IN expr",
 /*  38 */ "assignment ::= name_chain ASSIGN expr",
 /*  39 */ "stmt_list ::= stmt",
 /*  40 */ "stmt_list ::= stmt_list stmt",
 /*  41 */ "expr ::= array",
 /*  42 */ "array ::= OPENBRAC maybe_empty_stmt_list RBRAC",
 /*  43 */ "maybe_empty_stmt_list ::=",
 /*  44 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  45 */ "expr ::= num",
 /*  46 */ "expr ::= string",
 /*  47 */ "expr ::= bool",
 /*  48 */ "num ::= NUM",
 /*  49 */ "string ::= STRING",
 /*  50 */ "bool ::= BOOLEAN",
 /*  51 */ "expr ::= expr PLUS expr",
 /*  52 */ "expr ::= expr MINUS expr",
 /*  53 */ "expr ::= expr DIVIDE expr",
 /*  54 */ "expr ::= expr TIMES expr",
 /*  55 */ "expr ::= expr MODULO expr",
 /*  56 */ "expr ::= expr POW expr",
 /*  57 */ "expr ::= expr EQUALTO expr",
 /*  58 */ "expr ::= expr NOTEQUALTO expr",
 /*  59 */ "expr ::= expr LESSTHAN expr",
 /*  60 */ "expr ::= expr GREATERTHAN expr",
 /*  61 */ "expr ::= expr LORE expr",
 /*  62 */ "expr ::= expr GORE expr",
 /*  63 */ "expr ::= expr AND expr",
 /*  64 */ "expr ::= expr OR expr",
 /*  65 */ "expr ::= BITNOT expr",
 /*  66 */ "expr ::= MINUS expr",
 /*  67 */ "expr ::= NOT expr",
 /*  68 */ "expr ::= expr SHIFTL expr",
 /*  69 */ "expr ::= expr SHIFTR expr",
 /*  70 */ "expr ::= expr BITAND expr",
 /*  71 */ "expr ::= expr BITXOR expr",
 /*  72 */ "in ::= error",
 /*  73 */ "error ::= OPENQUOTEERROR",
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
    case 34: /* OPENING_LPAREN */
    case 35: /* CLOSING_RPAREN */
    case 36: /* NAME */
    case 37: /* GUARD_N */
    case 38: /* GUARD_S */
    case 39: /* WILDCARD_N */
    case 40: /* WILDCARD */
    case 41: /* WHERE */
    case 42: /* CASE */
    case 43: /* OF */
    case 44: /* N_TAB */
    case 45: /* POINTER */
    case 46: /* LET */
    case 47: /* IN */
    case 48: /* OPENBRAC */
    case 49: /* NUM */
    case 50: /* STRING */
    case 51: /* BOOLEAN */
    case 52: /* OPENQUOTEERROR */
{
#line 43 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 751 "./src/Grammar/grammar.c"
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
  { 56, 1 },
  { 57, 0 },
  { 57, 2 },
  { 57, 3 },
  { 57, 3 },
  { 58, 1 },
  { 60, 1 },
  { 62, 2 },
  { 62, 3 },
  { 61, 2 },
  { 60, 1 },
  { 60, 1 },
  { 64, 1 },
  { 65, 1 },
  { 66, 2 },
  { 66, 1 },
  { 54, 1 },
  { 54, 4 },
  { 54, 3 },
  { 59, 1 },
  { 60, 1 },
  { 59, 1 },
  { 70, 2 },
  { 70, 2 },
  { 72, 4 },
  { 72, 5 },
  { 72, 4 },
  { 72, 5 },
  { 71, 4 },
  { 71, 4 },
  { 69, 2 },
  { 69, 2 },
  { 69, 4 },
  { 69, 4 },
  { 68, 5 },
  { 68, 5 },
  { 68, 4 },
  { 54, 6 },
  { 63, 3 },
  { 67, 1 },
  { 67, 2 },
  { 54, 1 },
  { 73, 3 },
  { 74, 0 },
  { 74, 1 },
  { 54, 1 },
  { 54, 1 },
  { 54, 1 },
  { 75, 1 },
  { 76, 1 },
  { 77, 1 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 2 },
  { 54, 2 },
  { 54, 2 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 57, 1 },
  { 53, 1 },
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
      case 4: /* in ::= in test NEWLINE */ yytestcase(yyruleno==4);
#line 83 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,33,&yymsp[0].minor);
}
#line 1124 "./src/Grammar/grammar.c"
        break;
      case 5: /* start ::= spec */
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
    if( yymsp[0].minor.yy0.type == optic::CODE_BLOCK )
    {
        optic::out() << "CODE BLOCK!" << std::endl;
    }
    else
    {
        optic::resolve_stack_from_parser(yymsp[0].minor.yy0);
    }
}
#line 1147 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= closed_block */
#line 110 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    optic::out() << "CODE BLOCK!" << std::endl;
}
#line 1155 "./src/Grammar/grammar.c"
        break;
      case 7: /* open_block ::= OPENING_LPAREN spec */
#line 116 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
  yy_destructor(yypParser,34,&yymsp[-1].minor);
}
#line 1163 "./src/Grammar/grammar.c"
        break;
      case 8: /* open_block ::= open_block NEWLINE spec */
#line 121 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::CODE_BLOCK;
  yy_destructor(yypParser,33,&yymsp[-1].minor);
}
#line 1171 "./src/Grammar/grammar.c"
        break;
      case 9: /* closed_block ::= open_block CLOSING_RPAREN */
#line 126 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::CODE_BLOCK;
  yy_destructor(yypParser,35,&yymsp[0].minor);
}
#line 1179 "./src/Grammar/grammar.c"
        break;
      case 10: /* spec ::= assignment */
#line 131 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1186 "./src/Grammar/grammar.c"
        break;
      case 11: /* spec ::= top_stmt */
      case 12: /* top_stmt ::= stmt */ yytestcase(yyruleno==12);
#line 136 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1195 "./src/Grammar/grammar.c"
        break;
      case 13: /* stmt ::= expr */
      case 39: /* stmt_list ::= stmt */ yytestcase(yyruleno==39);
#line 148 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1204 "./src/Grammar/grammar.c"
        break;
      case 14: /* name_chain ::= name_chain NAME */
#line 154 "./src/Grammar/grammar.y"
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
#line 1243 "./src/Grammar/grammar.c"
        break;
      case 15: /* name_chain ::= NAME */
#line 191 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1252 "./src/Grammar/grammar.c"
        break;
      case 16: /* expr ::= NAME */
#line 198 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1265 "./src/Grammar/grammar.c"
        break;
      case 17: /* expr ::= NAME LPAREN stmt_list RPAREN */
#line 214 "./src/Grammar/grammar.y"
{
    if(yymsp[-1].minor.yy0.type==optic::STATEMENT_LIST)
    {
            yymsp[-1].minor.yy0.type = optic::ARRAY;
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
    optic::out() << "FUNCTION_CALL yymsp[-3].minor.yy0.data.string " << *yymsp[-3].minor.yy0.data.string << "arguments: " << std::endl;
    print_object(yymsp[-1].minor.yy0);

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
#line 1297 "./src/Grammar/grammar.c"
        break;
      case 18: /* expr ::= NAME LPAREN RPAREN */
#line 242 "./src/Grammar/grammar.y"
{
    optic::object C;
    C.type = optic::OPERATION_TREE;
    C.data.array = new optic::Array();
    optic::object b;
    b.type = optic::STRING;
    b.data.string = new optic::String(yymsp[-2].minor.yy0.data.string->c_str());
    optic::parse_operations(yygotominor.yy0,b,C,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,27,&yymsp[-1].minor);
  yy_destructor(yypParser,28,&yymsp[0].minor);
}
#line 1317 "./src/Grammar/grammar.c"
        break;
      case 19: /* test ::= case_statement */
#line 258 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
/*    panopticon::out() << "Case: " << *yymsp[0].minor.yy0.data.array->at(0).data.string << std::endl;*/
}
#line 1325 "./src/Grammar/grammar.c"
        break;
      case 20: /* spec ::= where_statement */
#line 264 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Where: " << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1333 "./src/Grammar/grammar.c"
        break;
      case 21: /* test ::= guard_assignment */
#line 270 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Guard");
}
#line 1342 "./src/Grammar/grammar.c"
        break;
      case 24: /* guard_statement ::= GUARD_N expr ASSIGN expr */
#line 280 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Guard");
  yy_destructor(yypParser,37,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1352 "./src/Grammar/grammar.c"
        break;
      case 25: /* guard_statement ::= guard_statement GUARD_N expr ASSIGN expr */
#line 286 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
  yy_destructor(yypParser,37,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1361 "./src/Grammar/grammar.c"
        break;
      case 26: /* guard_statement ::= GUARD_S expr ASSIGN expr */
#line 291 "./src/Grammar/grammar.y"
{

  yy_destructor(yypParser,38,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1370 "./src/Grammar/grammar.c"
        break;
      case 27: /* guard_statement ::= guard_statement GUARD_S expr ASSIGN expr */
#line 296 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
  yy_destructor(yypParser,38,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1379 "./src/Grammar/grammar.c"
        break;
      case 28: /* final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr */
#line 301 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,39,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1389 "./src/Grammar/grammar.c"
        break;
      case 29: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr */
#line 307 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,40,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1399 "./src/Grammar/grammar.c"
        break;
      case 30: /* where_statement ::= guard_statement WHERE */
      case 31: /* where_statement ::= final_guard_statement WHERE */ yytestcase(yyruleno==31);
#line 312 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1407 "./src/Grammar/grammar.c"
        break;
      case 32: /* where_statement ::= name_chain ASSIGN expr WHERE */
#line 314 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1415 "./src/Grammar/grammar.c"
        break;
      case 33: /* where_statement ::= where_statement NAME ASSIGN expr */
#line 316 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,36,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1423 "./src/Grammar/grammar.c"
        break;
      case 34: /* case_statement ::= name_chain ASSIGN CASE expr OF */
#line 319 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,42,&yymsp[-2].minor);
  yy_destructor(yypParser,43,&yymsp[0].minor);
}
#line 1434 "./src/Grammar/grammar.c"
        break;
      case 35: /* case_statement ::= case_statement N_TAB expr POINTER expr */
#line 325 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,44,&yymsp[-3].minor);
  yy_destructor(yypParser,45,&yymsp[-1].minor);
}
#line 1444 "./src/Grammar/grammar.c"
        break;
      case 36: /* case_statement ::= case_statement WILDCARD_N POINTER expr */
#line 331 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,39,&yymsp[-2].minor);
  yy_destructor(yypParser,45,&yymsp[-1].minor);
}
#line 1454 "./src/Grammar/grammar.c"
        break;
      case 37: /* expr ::= LET NAME ASSIGN expr IN expr */
#line 337 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Let");
  yy_destructor(yypParser,46,&yymsp[-5].minor);
  yy_destructor(yypParser,36,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,47,&yymsp[-1].minor);
}
#line 1466 "./src/Grammar/grammar.c"
        break;
      case 38: /* assignment ::= name_chain ASSIGN expr */
#line 343 "./src/Grammar/grammar.y"
{
    insure_ready_for_assignment(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);

    panopticon::parse_operations(yygotominor.yy0, yymsp[-2].minor.yy0, yymsp[0].minor.yy0, panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1481 "./src/Grammar/grammar.c"
        break;
      case 40: /* stmt_list ::= stmt_list stmt */
#line 365 "./src/Grammar/grammar.y"
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
#line 1500 "./src/Grammar/grammar.c"
        break;
      case 41: /* expr ::= array */
#line 390 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1507 "./src/Grammar/grammar.c"
        break;
      case 42: /* array ::= OPENBRAC maybe_empty_stmt_list RBRAC */
#line 395 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::ARRAY;
    yygotominor.yy0.data.array = yymsp[-1].minor.yy0.data.array;
  yy_destructor(yypParser,48,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1517 "./src/Grammar/grammar.c"
        break;
      case 43: /* maybe_empty_stmt_list ::= */
#line 401 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1525 "./src/Grammar/grammar.c"
        break;
      case 44: /* maybe_empty_stmt_list ::= stmt_list */
#line 407 "./src/Grammar/grammar.y"
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
#line 1541 "./src/Grammar/grammar.c"
        break;
      case 45: /* expr ::= num */
      case 47: /* expr ::= bool */ yytestcase(yyruleno==47);
#line 431 "./src/Grammar/grammar.y"
{
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1549 "./src/Grammar/grammar.c"
        break;
      case 46: /* expr ::= string */
#line 436 "./src/Grammar/grammar.y"
{
   create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1556 "./src/Grammar/grammar.c"
        break;
      case 48: /* num ::= NUM */
#line 458 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;*/
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1565 "./src/Grammar/grammar.c"
        break;
      case 49: /* string ::= STRING */
#line 465 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());*/
/*    delete yymsp[0].minor.yy0.data.string;*/
    yymsp[0].minor.yy0.type = panopticon::STRING;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1575 "./src/Grammar/grammar.c"
        break;
      case 50: /* bool ::= BOOLEAN */
#line 474 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;*/
    yymsp[0].minor.yy0.type = panopticon::BOOL;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1584 "./src/Grammar/grammar.c"
        break;
      case 51: /* expr ::= expr PLUS expr */
#line 506 "./src/Grammar/grammar.y"
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
#line 1599 "./src/Grammar/grammar.c"
        break;
      case 52: /* expr ::= expr MINUS expr */
#line 518 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1612 "./src/Grammar/grammar.c"
        break;
      case 53: /* expr ::= expr DIVIDE expr */
#line 528 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1625 "./src/Grammar/grammar.c"
        break;
      case 54: /* expr ::= expr TIMES expr */
#line 538 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1638 "./src/Grammar/grammar.c"
        break;
      case 55: /* expr ::= expr MODULO expr */
#line 548 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1651 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr POW expr */
#line 558 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1664 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr EQUALTO expr */
#line 568 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1677 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= expr NOTEQUALTO expr */
#line 578 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1690 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= expr LESSTHAN expr */
#line 588 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1703 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= expr GREATERTHAN expr */
#line 598 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1716 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= expr LORE expr */
#line 608 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1729 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= expr GORE expr */
#line 618 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1742 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= expr AND expr */
#line 628 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1755 "./src/Grammar/grammar.c"
        break;
      case 64: /* expr ::= expr OR expr */
#line 638 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1768 "./src/Grammar/grammar.c"
        break;
      case 65: /* expr ::= BITNOT expr */
#line 648 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1781 "./src/Grammar/grammar.c"
        break;
      case 66: /* expr ::= MINUS expr */
#line 658 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1794 "./src/Grammar/grammar.c"
        break;
      case 67: /* expr ::= NOT expr */
#line 668 "./src/Grammar/grammar.y"
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
#line 1808 "./src/Grammar/grammar.c"
        break;
      case 68: /* expr ::= expr SHIFTL expr */
#line 679 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1821 "./src/Grammar/grammar.c"
        break;
      case 69: /* expr ::= expr SHIFTR expr */
#line 689 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1834 "./src/Grammar/grammar.c"
        break;
      case 70: /* expr ::= expr BITAND expr */
#line 699 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1847 "./src/Grammar/grammar.c"
        break;
      case 71: /* expr ::= expr BITXOR expr */
#line 719 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1860 "./src/Grammar/grammar.c"
        break;
      case 72: /* in ::= error */
#line 770 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy157)
    {
    case panopticon::OpenQuoteError:
/*        panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        panopticon::out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 1875 "./src/Grammar/grammar.c"
        break;
      case 73: /* error ::= OPENQUOTEERROR */
#line 783 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy157 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1884 "./src/Grammar/grammar.c"
        break;
      default:
      /* (0) main ::= in */ yytestcase(yyruleno==0);
      /* (1) in ::= */ yytestcase(yyruleno==1);
      /* (22) guard_assignment ::= name_chain final_guard_statement */ yytestcase(yyruleno==22);
      /* (23) guard_assignment ::= name_chain guard_statement */ yytestcase(yyruleno==23);
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
#line 1953 "./src/Grammar/grammar.c"
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
#line 1975 "./src/Grammar/grammar.c"
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
