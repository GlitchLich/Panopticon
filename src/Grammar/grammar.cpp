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
#define YYNOCODE 78
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy155;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 133
#define YYNRULE 73
#define YYERRORSYMBOL 53
#define YYERRSYMDT yy155
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
#define YY_ACTTAB_COUNT (917)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    30,   31,   26,   27,   37,   36,   34,   32,   35,   33,
 /*    10 */    29,   28,   46,   43,   41,   40,   39,   38,   22,    2,
 /*    20 */   131,  105,   30,   31,   26,   27,   37,   36,   34,   32,
 /*    30 */    35,   33,   29,   28,   46,   43,   41,   40,   39,   38,
 /*    40 */    20,    5,   44,   99,   30,   31,   26,   27,   37,   36,
 /*    50 */    34,   32,   35,   33,   29,   28,   46,   43,   41,   40,
 /*    60 */    39,   38,   30,   31,   26,   27,   37,   36,   34,   32,
 /*    70 */    35,   33,   29,   28,   46,   43,   41,   40,   39,   38,
 /*    80 */    30,   31,   26,   27,   37,   36,   34,   32,   35,   33,
 /*    90 */    29,   28,   46,   43,   41,   40,   39,   38,  109,   30,
 /*   100 */    31,   26,   27,   37,   36,   34,   32,   35,   33,   29,
 /*   110 */    28,   46,   43,   41,   40,   39,   38,   14,  108,   45,
 /*   120 */    38,   30,   31,   26,   27,   37,   36,   34,   32,   35,
 /*   130 */    33,   29,   28,   46,   43,   41,   40,   39,   38,   17,
 /*   140 */    12,  112,   16,   11,   30,   31,   26,   27,   37,   36,
 /*   150 */    34,   32,   35,   33,   29,   28,   46,   43,   41,   40,
 /*   160 */    39,   38,   30,   31,   26,   27,   37,   36,   34,   32,
 /*   170 */    35,   33,   29,   28,   46,   43,   41,   40,   39,   38,
 /*   180 */    65,   10,  106,   85,  102,  130,  129,   84,  126,  125,
 /*   190 */   124,   80,  123,    9,   83,   78,   87,   86,  121,  208,
 /*   200 */   118,  117,  116,   31,   26,   27,   37,   36,   34,   32,
 /*   210 */    35,   33,   29,   28,   46,   43,   41,   40,   39,   38,
 /*   220 */    65,   41,   40,   39,   38,  128,  129,   84,  126,  125,
 /*   230 */   124,   80,  123,  103,   83,   78,   87,   86,  121,   65,
 /*   240 */   118,  117,  116,  208,  127,  129,   84,  126,  125,  124,
 /*   250 */    80,  123,  208,   83,   78,   87,   86,  121,  208,  118,
 /*   260 */   117,  116,   26,   27,   37,   36,   34,   32,   35,   33,
 /*   270 */    29,   28,   46,   43,   41,   40,   39,   38,   27,   37,
 /*   280 */    36,   34,   32,   35,   33,   29,   28,   46,   43,   41,
 /*   290 */    40,   39,   38,   37,   36,   34,   32,   35,   33,   29,
 /*   300 */    28,   46,   43,   41,   40,   39,   38,   34,   32,   35,
 /*   310 */    33,   29,   28,   46,   43,   41,   40,   39,   38,  133,
 /*   320 */    46,   43,   41,   40,   39,   38,   25,   81,  208,  208,
 /*   330 */   104,   24,   42,  207,    1,  208,   90,   25,  208,  123,
 /*   340 */   208,   18,   24,   42,  101,  121,  208,  118,  117,  116,
 /*   350 */    19,  208,  132,    3,  100,   79,    4,  115,  114,  113,
 /*   360 */    15,   13,   89,   88,  107,  100,  208,    4,  115,  114,
 /*   370 */   113,   25,  208,  208,  208,  208,   24,   42,   25,  208,
 /*   380 */   208,  122,  208,   24,   42,  208,  208,   25,  111,  101,
 /*   390 */   208,    8,   24,   42,  208,  208,  101,  208,  208,  100,
 /*   400 */   208,    4,  115,  114,  113,  101,  100,   25,    4,  115,
 /*   410 */   114,  113,   24,   42,  208,  100,  208,    4,  115,  114,
 /*   420 */   113,  208,  208,    3,  208,   79,  110,   23,   21,  208,
 /*   430 */   208,   65,  208,  208,  208,  100,  208,    4,  115,  114,
 /*   440 */   113,  120,  208,  123,    7,  208,  208,  208,  208,  121,
 /*   450 */    91,  118,  117,  116,   29,   28,   46,   43,   41,   40,
 /*   460 */    39,   38,   65,  208,  208,  208,  208,   65,  208,  208,
 /*   470 */   208,  208,  120,  208,  123,    6,  208,  119,   54,  123,
 /*   480 */   121,  208,  118,  117,  116,  121,  208,  118,  117,  116,
 /*   490 */   123,  208,   64,  208,  208,  208,  121,  208,  118,  117,
 /*   500 */   116,  208,  208,  208,  123,   82,  208,  147,  208,  208,
 /*   510 */   121,  208,  118,  117,  116,  208,   98,  123,  208,  208,
 /*   520 */   208,  208,  208,  121,  208,  118,  117,  116,  123,   97,
 /*   530 */   208,  208,  208,    5,  121,  208,  118,  117,  116,  208,
 /*   540 */    96,  123,  147,  147,  147,   95,  208,  121,  208,  118,
 /*   550 */   117,  116,  123,  208,  208,  208,  208,  123,  121,   94,
 /*   560 */   118,  117,  116,  121,  208,  118,  117,  116,  208,  208,
 /*   570 */   208,  123,   71,  208,  208,  208,  208,  121,  208,  118,
 /*   580 */   117,  116,  208,   70,  123,  208,  208,  208,  208,  208,
 /*   590 */   121,  208,  118,  117,  116,  123,   75,  208,  208,  208,
 /*   600 */   208,  121,  208,  118,  117,  116,  208,   74,  123,  208,
 /*   610 */   208,  208,   73,  208,  121,  208,  118,  117,  116,  123,
 /*   620 */   208,  208,  208,  208,  123,  121,   72,  118,  117,  116,
 /*   630 */   121,  208,  118,  117,  116,  208,  208,  208,  123,   67,
 /*   640 */   208,  208,  208,  208,  121,  208,  118,  117,  116,  208,
 /*   650 */    66,  123,  208,  208,  208,  208,  208,  121,  208,  118,
 /*   660 */   117,  116,  123,   77,  208,  208,  208,  208,  121,  208,
 /*   670 */   118,  117,  116,  208,   76,  123,  208,  208,  208,   69,
 /*   680 */   208,  121,  208,  118,  117,  116,  123,  208,  208,  208,
 /*   690 */   208,  123,  121,   68,  118,  117,  116,  121,  208,  118,
 /*   700 */   117,  116,  208,  208,  208,  123,   93,  208,  208,  208,
 /*   710 */   208,  121,  208,  118,  117,  116,  208,   92,  123,  208,
 /*   720 */   208,  208,  208,  208,  121,  208,  118,  117,  116,  123,
 /*   730 */    53,  208,  208,  208,  208,  121,  208,  118,  117,  116,
 /*   740 */   208,   63,  123,  208,  208,  208,   52,  208,  121,  208,
 /*   750 */   118,  117,  116,  123,  208,  208,  208,  208,  123,  121,
 /*   760 */    62,  118,  117,  116,  121,  208,  118,  117,  116,  208,
 /*   770 */   208,  208,  123,   50,  208,  208,  208,  208,  121,  208,
 /*   780 */   118,  117,  116,  208,   49,  123,  208,  208,  208,  208,
 /*   790 */   208,  121,  208,  118,  117,  116,  123,   61,  208,  208,
 /*   800 */   208,  208,  121,  208,  118,  117,  116,  208,   60,  123,
 /*   810 */   208,  208,  208,   48,  208,  121,  208,  118,  117,  116,
 /*   820 */   123,  208,  208,  208,  208,  123,  121,   59,  118,  117,
 /*   830 */   116,  121,  208,  118,  117,  116,  208,  208,  208,  123,
 /*   840 */    47,  208,  208,  208,  208,  121,  208,  118,  117,  116,
 /*   850 */   208,   58,  123,  208,  208,  208,  208,  208,  121,  208,
 /*   860 */   118,  117,  116,  123,   57,  208,  208,  208,  208,  121,
 /*   870 */   208,  118,  117,  116,  208,   56,  123,  208,  208,  208,
 /*   880 */    55,  208,  121,  208,  118,  117,  116,  123,  208,  208,
 /*   890 */   208,  208,  123,  121,   51,  118,  117,  116,  121,  208,
 /*   900 */   118,  117,  116,  208,  208,  208,  123,  208,  208,  208,
 /*   910 */   208,  208,  121,  208,  118,  117,  116,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    10 */    15,   16,   17,   18,   19,   20,   21,   22,    1,   33,
 /*    20 */    33,   35,    5,    6,    7,    8,    9,   10,   11,   12,
 /*    30 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*    40 */     1,   27,   47,   36,    5,    6,    7,    8,    9,   10,
 /*    50 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    60 */    21,   22,    5,    6,    7,    8,    9,   10,   11,   12,
 /*    70 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*    80 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    90 */    15,   16,   17,   18,   19,   20,   21,   22,   41,    5,
 /*   100 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   110 */    16,   17,   18,   19,   20,   21,   22,    1,   43,    1,
 /*   120 */    22,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   130 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   45,
 /*   140 */     1,   31,   45,    1,    5,    6,    7,    8,    9,   10,
 /*   150 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   160 */    21,   22,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   170 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   180 */    54,    1,   41,   36,   58,   59,   60,   61,   62,   63,
 /*   190 */    64,   65,   66,    1,   68,   69,   70,   71,   72,   77,
 /*   200 */    74,   75,   76,    6,    7,    8,    9,   10,   11,   12,
 /*   210 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   220 */    54,   19,   20,   21,   22,   59,   60,   61,   62,   63,
 /*   230 */    64,   65,   66,   52,   68,   69,   70,   71,   72,   54,
 /*   240 */    74,   75,   76,   77,   59,   60,   61,   62,   63,   64,
 /*   250 */    65,   66,   77,   68,   69,   70,   71,   72,   77,   74,
 /*   260 */    75,   76,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   270 */    15,   16,   17,   18,   19,   20,   21,   22,    8,    9,
 /*   280 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   290 */    20,   21,   22,    9,   10,   11,   12,   13,   14,   15,
 /*   300 */    16,   17,   18,   19,   20,   21,   22,   11,   12,   13,
 /*   310 */    14,   15,   16,   17,   18,   19,   20,   21,   22,    0,
 /*   320 */    17,   18,   19,   20,   21,   22,   18,   54,   77,   77,
 /*   330 */    53,   23,   24,   56,   57,   77,   39,   18,   77,   66,
 /*   340 */    77,   44,   23,   24,   36,   72,   77,   74,   75,   76,
 /*   350 */    42,   77,   33,   34,   46,   36,   48,   49,   50,   51,
 /*   360 */    37,   38,   39,   40,   41,   46,   77,   48,   49,   50,
 /*   370 */    51,   18,   77,   77,   77,   77,   23,   24,   18,   77,
 /*   380 */    77,   28,   77,   23,   24,   77,   77,   18,   28,   36,
 /*   390 */    77,    1,   23,   24,   77,   77,   36,   77,   77,   46,
 /*   400 */    77,   48,   49,   50,   51,   36,   46,   18,   48,   49,
 /*   410 */    50,   51,   23,   24,   77,   46,   77,   48,   49,   50,
 /*   420 */    51,   77,   77,   34,   77,   36,   36,   37,   38,   77,
 /*   430 */    77,   54,   77,   77,   77,   46,   77,   48,   49,   50,
 /*   440 */    51,   64,   77,   66,   67,   77,   77,   77,   77,   72,
 /*   450 */    73,   74,   75,   76,   15,   16,   17,   18,   19,   20,
 /*   460 */    21,   22,   54,   77,   77,   77,   77,   54,   77,   77,
 /*   470 */    77,   77,   64,   77,   66,   67,   77,   64,   54,   66,
 /*   480 */    72,   77,   74,   75,   76,   72,   77,   74,   75,   76,
 /*   490 */    66,   77,   54,   77,   77,   77,   72,   77,   74,   75,
 /*   500 */    76,   77,   77,   77,   66,   54,   77,    1,   77,   77,
 /*   510 */    72,   77,   74,   75,   76,   77,   54,   66,   77,   77,
 /*   520 */    77,   77,   77,   72,   77,   74,   75,   76,   66,   54,
 /*   530 */    77,   77,   77,   27,   72,   77,   74,   75,   76,   77,
 /*   540 */    54,   66,   36,   37,   38,   54,   77,   72,   77,   74,
 /*   550 */    75,   76,   66,   77,   77,   77,   77,   66,   72,   54,
 /*   560 */    74,   75,   76,   72,   77,   74,   75,   76,   77,   77,
 /*   570 */    77,   66,   54,   77,   77,   77,   77,   72,   77,   74,
 /*   580 */    75,   76,   77,   54,   66,   77,   77,   77,   77,   77,
 /*   590 */    72,   77,   74,   75,   76,   66,   54,   77,   77,   77,
 /*   600 */    77,   72,   77,   74,   75,   76,   77,   54,   66,   77,
 /*   610 */    77,   77,   54,   77,   72,   77,   74,   75,   76,   66,
 /*   620 */    77,   77,   77,   77,   66,   72,   54,   74,   75,   76,
 /*   630 */    72,   77,   74,   75,   76,   77,   77,   77,   66,   54,
 /*   640 */    77,   77,   77,   77,   72,   77,   74,   75,   76,   77,
 /*   650 */    54,   66,   77,   77,   77,   77,   77,   72,   77,   74,
 /*   660 */    75,   76,   66,   54,   77,   77,   77,   77,   72,   77,
 /*   670 */    74,   75,   76,   77,   54,   66,   77,   77,   77,   54,
 /*   680 */    77,   72,   77,   74,   75,   76,   66,   77,   77,   77,
 /*   690 */    77,   66,   72,   54,   74,   75,   76,   72,   77,   74,
 /*   700 */    75,   76,   77,   77,   77,   66,   54,   77,   77,   77,
 /*   710 */    77,   72,   77,   74,   75,   76,   77,   54,   66,   77,
 /*   720 */    77,   77,   77,   77,   72,   77,   74,   75,   76,   66,
 /*   730 */    54,   77,   77,   77,   77,   72,   77,   74,   75,   76,
 /*   740 */    77,   54,   66,   77,   77,   77,   54,   77,   72,   77,
 /*   750 */    74,   75,   76,   66,   77,   77,   77,   77,   66,   72,
 /*   760 */    54,   74,   75,   76,   72,   77,   74,   75,   76,   77,
 /*   770 */    77,   77,   66,   54,   77,   77,   77,   77,   72,   77,
 /*   780 */    74,   75,   76,   77,   54,   66,   77,   77,   77,   77,
 /*   790 */    77,   72,   77,   74,   75,   76,   66,   54,   77,   77,
 /*   800 */    77,   77,   72,   77,   74,   75,   76,   77,   54,   66,
 /*   810 */    77,   77,   77,   54,   77,   72,   77,   74,   75,   76,
 /*   820 */    66,   77,   77,   77,   77,   66,   72,   54,   74,   75,
 /*   830 */    76,   72,   77,   74,   75,   76,   77,   77,   77,   66,
 /*   840 */    54,   77,   77,   77,   77,   72,   77,   74,   75,   76,
 /*   850 */    77,   54,   66,   77,   77,   77,   77,   77,   72,   77,
 /*   860 */    74,   75,   76,   66,   54,   77,   77,   77,   77,   72,
 /*   870 */    77,   74,   75,   76,   77,   54,   66,   77,   77,   77,
 /*   880 */    54,   77,   72,   77,   74,   75,   76,   66,   77,   77,
 /*   890 */    77,   77,   66,   72,   54,   74,   75,   76,   72,   77,
 /*   900 */    74,   75,   76,   77,   77,   77,   66,   77,   77,   77,
 /*   910 */    77,   77,   72,   77,   74,   75,   76,
};
#define YY_SHIFT_USE_DFLT (-15)
#define YY_SHIFT_COUNT (102)
#define YY_SHIFT_MIN   (-14)
#define YY_SHIFT_MAX   (506)
static const short yy_shift_ofst[] = {
 /*     0 */   181,  319,  389,  389,  369,  360,  353,  369,  308,  369,
 /*    10 */   369,  369,  369,  369,  369,  369,  369,  369,  369,  369,
 /*    20 */   369,  369,  369,  369,  369,  369,  369,  369,  369,  369,
 /*    30 */   369,  369,  369,  369,  369,  369,  369,  369,  369,  369,
 /*    40 */   369,  369,  369,  369,  369,  369,  369,  139,  116,   94,
 /*    50 */    75,   57,   39,   17,   -5,  157,  157,  157,  157,  157,
 /*    60 */   157,  157,  157,  157,  157,  157,  197,  255,  270,  284,
 /*    70 */   296,  296,  439,  439,  439,  439,  303,  303,  323,  506,
 /*    80 */   390,  202,  202,  297,  -14,  192,  147,  141,  180,  142,
 /*    90 */    97,  110,   98,   98,   98,   98,   98,   98,   98,  118,
 /*   100 */     7,   14,  -13,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (46)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (840)
static const short yy_reduce_ofst[] = {
 /*     0 */   277,  126,  185,  166,  377,  408,  413,  413,  840,  826,
 /*    10 */   821,  810,  797,  786,  773,  759,  754,  743,  730,  719,
 /*    20 */   706,  692,  687,  676,  663,  652,  639,  625,  620,  609,
 /*    30 */   596,  585,  572,  558,  553,  542,  529,  518,  505,  491,
 /*    40 */   486,  475,  462,  451,  438,  424,  273,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   134,  206,  206,  206,  175,  206,  206,  176,  206,  206,
 /*    10 */   206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
 /*    20 */   206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
 /*    30 */   206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
 /*    40 */   206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
 /*    50 */   206,  170,  206,  206,  206,  165,  161,  160,  159,  157,
 /*    60 */   168,  167,  158,  156,  169,  145,  196,  195,  203,  202,
 /*    70 */   190,  189,  194,  193,  192,  191,  201,  200,  153,  148,
 /*    80 */   206,  183,  184,  152,  206,  206,  155,  154,  206,  206,
 /*    90 */   206,  206,  199,  198,  188,  187,  186,  185,  197,  206,
 /*   100 */   206,  148,  206,  205,  204,  141,  163,  162,  166,  164,
 /*   110 */   146,  151,  174,  182,  181,  180,  179,  178,  177,  172,
 /*   120 */   171,  173,  150,  149,  144,  143,  142,  140,  139,  138,
 /*   130 */   137,  136,  135,
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
  "main",          "in",            "start",         "spec",        
  "closed_block",  "open_block",    "assignment",    "top_stmt",    
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
 /*   5 */ "spec ::= closed_block",
 /*   6 */ "open_block ::= OPENING_LPAREN spec",
 /*   7 */ "open_block ::= open_block NEWLINE spec",
 /*   8 */ "closed_block ::= open_block CLOSING_RPAREN",
 /*   9 */ "spec ::= assignment",
 /*  10 */ "spec ::= top_stmt",
 /*  11 */ "top_stmt ::= stmt",
 /*  12 */ "stmt ::= expr",
 /*  13 */ "name_chain ::= name_chain NAME",
 /*  14 */ "name_chain ::= NAME",
 /*  15 */ "expr ::= NAME",
 /*  16 */ "expr ::= function_call",
 /*  17 */ "function_call ::= NAME LPAREN stmt_list RPAREN",
 /*  18 */ "function_call ::= NAME LPAREN RPAREN",
 /*  19 */ "spec ::= case_statement",
 /*  20 */ "spec ::= guard_statement",
 /*  21 */ "spec ::= final_guard_statement",
 /*  22 */ "spec ::= where_statement",
 /*  23 */ "guard_statement ::= name_chain GUARD_N expr ASSIGN expr",
 /*  24 */ "guard_statement ::= guard_statement GUARD_N expr ASSIGN expr",
 /*  25 */ "guard_statement ::= name_chain GUARD_S expr ASSIGN expr",
 /*  26 */ "guard_statement ::= guard_statement GUARD_S expr ASSIGN expr",
 /*  27 */ "final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr",
 /*  28 */ "final_guard_statement ::= guard_statement WILDCARD ASSIGN expr",
 /*  29 */ "where_statement ::= guard_statement WHERE",
 /*  30 */ "where_statement ::= final_guard_statement WHERE",
 /*  31 */ "where_statement ::= name_chain ASSIGN expr WHERE",
 /*  32 */ "where_statement ::= where_statement NAME ASSIGN expr",
 /*  33 */ "case_statement ::= name_chain ASSIGN CASE expr OF",
 /*  34 */ "case_statement ::= case_statement N_TAB expr POINTER expr",
 /*  35 */ "case_statement ::= case_statement WILDCARD_N POINTER expr",
 /*  36 */ "expr ::= LET NAME ASSIGN expr IN expr",
 /*  37 */ "assignment ::= name_chain ASSIGN expr",
 /*  38 */ "stmt_list ::= stmt",
 /*  39 */ "stmt_list ::= stmt_list stmt",
 /*  40 */ "expr ::= array",
 /*  41 */ "array ::= OPENBRAC maybe_empty_stmt_list RBRAC",
 /*  42 */ "maybe_empty_stmt_list ::=",
 /*  43 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  44 */ "expr ::= num",
 /*  45 */ "expr ::= string",
 /*  46 */ "expr ::= bool",
 /*  47 */ "num ::= NUM",
 /*  48 */ "string ::= STRING",
 /*  49 */ "bool ::= BOOLEAN",
 /*  50 */ "expr ::= expr PLUS expr",
 /*  51 */ "expr ::= expr MINUS expr",
 /*  52 */ "expr ::= expr DIVIDE expr",
 /*  53 */ "expr ::= expr TIMES expr",
 /*  54 */ "expr ::= expr MODULO expr",
 /*  55 */ "expr ::= expr POW expr",
 /*  56 */ "expr ::= expr EQUALTO expr",
 /*  57 */ "expr ::= expr NOTEQUALTO expr",
 /*  58 */ "expr ::= expr LESSTHAN expr",
 /*  59 */ "expr ::= expr GREATERTHAN expr",
 /*  60 */ "expr ::= expr LORE expr",
 /*  61 */ "expr ::= expr GORE expr",
 /*  62 */ "expr ::= expr AND expr",
 /*  63 */ "expr ::= expr OR expr",
 /*  64 */ "expr ::= BITNOT expr",
 /*  65 */ "expr ::= MINUS expr",
 /*  66 */ "expr ::= NOT expr",
 /*  67 */ "expr ::= expr SHIFTL expr",
 /*  68 */ "expr ::= expr SHIFTR expr",
 /*  69 */ "expr ::= expr BITAND expr",
 /*  70 */ "expr ::= expr BITXOR expr",
 /*  71 */ "in ::= error",
 /*  72 */ "error ::= OPENQUOTEERROR",
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
#line 772 "./src/Grammar/grammar.c"
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
  { 58, 1 },
  { 59, 1 },
  { 61, 2 },
  { 61, 3 },
  { 60, 2 },
  { 59, 1 },
  { 59, 1 },
  { 63, 1 },
  { 64, 1 },
  { 65, 2 },
  { 65, 1 },
  { 54, 1 },
  { 54, 1 },
  { 66, 4 },
  { 66, 3 },
  { 59, 1 },
  { 59, 1 },
  { 59, 1 },
  { 59, 1 },
  { 69, 5 },
  { 69, 5 },
  { 69, 5 },
  { 69, 5 },
  { 70, 4 },
  { 70, 4 },
  { 71, 2 },
  { 71, 2 },
  { 71, 4 },
  { 71, 4 },
  { 68, 5 },
  { 68, 5 },
  { 68, 4 },
  { 54, 6 },
  { 62, 3 },
  { 67, 1 },
  { 67, 2 },
  { 54, 1 },
  { 72, 3 },
  { 73, 0 },
  { 73, 1 },
  { 54, 1 },
  { 54, 1 },
  { 54, 1 },
  { 74, 1 },
  { 75, 1 },
  { 76, 1 },
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
#line 83 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,33,&yymsp[0].minor);
}
#line 1143 "./src/Grammar/grammar.c"
        break;
      case 4: /* start ::= spec */
#line 88 "./src/Grammar/grammar.y"
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
#line 1166 "./src/Grammar/grammar.c"
        break;
      case 5: /* spec ::= closed_block */
#line 109 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    optic::out() << "CODE BLOCK!" << std::endl;
}
#line 1174 "./src/Grammar/grammar.c"
        break;
      case 6: /* open_block ::= OPENING_LPAREN spec */
#line 115 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
  yy_destructor(yypParser,34,&yymsp[-1].minor);
}
#line 1182 "./src/Grammar/grammar.c"
        break;
      case 7: /* open_block ::= open_block NEWLINE spec */
#line 120 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::CODE_BLOCK;
  yy_destructor(yypParser,33,&yymsp[-1].minor);
}
#line 1190 "./src/Grammar/grammar.c"
        break;
      case 8: /* closed_block ::= open_block CLOSING_RPAREN */
#line 125 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::CODE_BLOCK;
  yy_destructor(yypParser,35,&yymsp[0].minor);
}
#line 1198 "./src/Grammar/grammar.c"
        break;
      case 9: /* spec ::= assignment */
      case 44: /* expr ::= num */ yytestcase(yyruleno==44);
      case 46: /* expr ::= bool */ yytestcase(yyruleno==46);
#line 130 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1207 "./src/Grammar/grammar.c"
        break;
      case 10: /* spec ::= top_stmt */
      case 11: /* top_stmt ::= stmt */ yytestcase(yyruleno==11);
      case 45: /* expr ::= string */ yytestcase(yyruleno==45);
#line 135 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1217 "./src/Grammar/grammar.c"
        break;
      case 12: /* stmt ::= expr */
      case 38: /* stmt_list ::= stmt */ yytestcase(yyruleno==38);
#line 147 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1226 "./src/Grammar/grammar.c"
        break;
      case 13: /* name_chain ::= name_chain NAME */
#line 153 "./src/Grammar/grammar.y"
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
#line 1265 "./src/Grammar/grammar.c"
        break;
      case 14: /* name_chain ::= NAME */
#line 190 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1274 "./src/Grammar/grammar.c"
        break;
      case 15: /* expr ::= NAME */
#line 197 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1287 "./src/Grammar/grammar.c"
        break;
      case 16: /* expr ::= function_call */
      case 40: /* expr ::= array */ yytestcase(yyruleno==40);
#line 208 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1295 "./src/Grammar/grammar.c"
        break;
      case 17: /* function_call ::= NAME LPAREN stmt_list RPAREN */
#line 213 "./src/Grammar/grammar.y"
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
#line 1325 "./src/Grammar/grammar.c"
        break;
      case 18: /* function_call ::= NAME LPAREN RPAREN */
#line 239 "./src/Grammar/grammar.y"
{
    optic::object C;
    C.type = optic::OPERATION_TREE;
    C.data.array = new optic::Array();
    optic::object b;
    b.type = optic::FUNCTION_CALL;
    b.data.string = new optic::String(*yymsp[-2].minor.yy0.data.string);
    optic::parse_operations(yygotominor.yy0,b,C,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,27,&yymsp[-1].minor);
  yy_destructor(yypParser,28,&yymsp[0].minor);
}
#line 1345 "./src/Grammar/grammar.c"
        break;
      case 19: /* spec ::= case_statement */
#line 255 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Case: " << *yymsp[0].minor.yy0.data.array->at(0).data.string << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1353 "./src/Grammar/grammar.c"
        break;
      case 20: /* spec ::= guard_statement */
      case 21: /* spec ::= final_guard_statement */ yytestcase(yyruleno==21);
#line 262 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Guard: " << *yymsp[0].minor.yy0.data.array->at(0).data.string << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1362 "./src/Grammar/grammar.c"
        break;
      case 22: /* spec ::= where_statement */
#line 274 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Where: " << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1370 "./src/Grammar/grammar.c"
        break;
      case 23: /* guard_statement ::= name_chain GUARD_N expr ASSIGN expr */
      case 24: /* guard_statement ::= guard_statement GUARD_N expr ASSIGN expr */ yytestcase(yyruleno==24);
#line 280 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,37,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1381 "./src/Grammar/grammar.c"
        break;
      case 25: /* guard_statement ::= name_chain GUARD_S expr ASSIGN expr */
      case 26: /* guard_statement ::= guard_statement GUARD_S expr ASSIGN expr */ yytestcase(yyruleno==26);
#line 292 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,38,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1392 "./src/Grammar/grammar.c"
        break;
      case 27: /* final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr */
#line 304 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,39,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1402 "./src/Grammar/grammar.c"
        break;
      case 28: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr */
#line 310 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,40,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1412 "./src/Grammar/grammar.c"
        break;
      case 29: /* where_statement ::= guard_statement WHERE */
      case 30: /* where_statement ::= final_guard_statement WHERE */ yytestcase(yyruleno==30);
#line 315 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1420 "./src/Grammar/grammar.c"
        break;
      case 31: /* where_statement ::= name_chain ASSIGN expr WHERE */
#line 317 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1428 "./src/Grammar/grammar.c"
        break;
      case 32: /* where_statement ::= where_statement NAME ASSIGN expr */
#line 319 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,36,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1436 "./src/Grammar/grammar.c"
        break;
      case 33: /* case_statement ::= name_chain ASSIGN CASE expr OF */
#line 322 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,42,&yymsp[-2].minor);
  yy_destructor(yypParser,43,&yymsp[0].minor);
}
#line 1447 "./src/Grammar/grammar.c"
        break;
      case 34: /* case_statement ::= case_statement N_TAB expr POINTER expr */
#line 328 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,44,&yymsp[-3].minor);
  yy_destructor(yypParser,45,&yymsp[-1].minor);
}
#line 1457 "./src/Grammar/grammar.c"
        break;
      case 35: /* case_statement ::= case_statement WILDCARD_N POINTER expr */
#line 334 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,39,&yymsp[-2].minor);
  yy_destructor(yypParser,45,&yymsp[-1].minor);
}
#line 1467 "./src/Grammar/grammar.c"
        break;
      case 36: /* expr ::= LET NAME ASSIGN expr IN expr */
#line 340 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Let");
  yy_destructor(yypParser,46,&yymsp[-5].minor);
  yy_destructor(yypParser,36,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,47,&yymsp[-1].minor);
}
#line 1479 "./src/Grammar/grammar.c"
        break;
      case 37: /* assignment ::= name_chain ASSIGN expr */
#line 353 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::FUNCTION_BODY;
    if(
        yymsp[0].minor.yy0.type == optic::OPERATION ||
        yymsp[0].minor.yy0.type == optic::OPERATION ||
        yymsp[0].minor.yy0.type == optic::NUMBER ||
        yymsp[0].minor.yy0.type == optic::STRING ||
        yymsp[0].minor.yy0.type == optic::BOOL   ||
        yymsp[0].minor.yy0.type == optic::ARRAY
    )
    {
        optic::object temp = yymsp[0].minor.yy0;
        yymsp[0].minor.yy0.data.array = new optic::Array();
        yymsp[0].minor.yy0.data.array->reserve(1);
        yymsp[0].minor.yy0.data.array->push_back(temp);
    }

    if(yymsp[-2].minor.yy0.type!=optic::ARRAY)
    {
        optic::object temp = yymsp[-2].minor.yy0;
        yymsp[-2].minor.yy0.type=optic::ARRAY;
        yymsp[-2].minor.yy0.data.array = new optic::Array();
        yymsp[-2].minor.yy0.data.array->reserve(1);
        yymsp[-2].minor.yy0.data.array->push_back(temp);
    }

    panopticon::parse_operations(yygotominor.yy0, yymsp[-2].minor.yy0, yymsp[0].minor.yy0, panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1517 "./src/Grammar/grammar.c"
        break;
      case 39: /* stmt_list ::= stmt_list stmt */
#line 398 "./src/Grammar/grammar.y"
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
#line 1536 "./src/Grammar/grammar.c"
        break;
      case 41: /* array ::= OPENBRAC maybe_empty_stmt_list RBRAC */
#line 428 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::ARRAY;
    yygotominor.yy0.data.array = yymsp[-1].minor.yy0.data.array;
  yy_destructor(yypParser,48,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1546 "./src/Grammar/grammar.c"
        break;
      case 42: /* maybe_empty_stmt_list ::= */
#line 434 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1554 "./src/Grammar/grammar.c"
        break;
      case 43: /* maybe_empty_stmt_list ::= stmt_list */
#line 440 "./src/Grammar/grammar.y"
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
#line 1570 "./src/Grammar/grammar.c"
        break;
      case 47: /* num ::= NUM */
#line 492 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.type = panopticon::NUMBER;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1579 "./src/Grammar/grammar.c"
        break;
      case 48: /* string ::= STRING */
#line 499 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1589 "./src/Grammar/grammar.c"
        break;
      case 49: /* bool ::= BOOLEAN */
#line 508 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    yygotominor.yy0.type = panopticon::BOOL;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1598 "./src/Grammar/grammar.c"
        break;
      case 50: /* expr ::= expr PLUS expr */
#line 540 "./src/Grammar/grammar.y"
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
#line 1613 "./src/Grammar/grammar.c"
        break;
      case 51: /* expr ::= expr MINUS expr */
#line 552 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1626 "./src/Grammar/grammar.c"
        break;
      case 52: /* expr ::= expr DIVIDE expr */
#line 562 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1639 "./src/Grammar/grammar.c"
        break;
      case 53: /* expr ::= expr TIMES expr */
#line 572 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1652 "./src/Grammar/grammar.c"
        break;
      case 54: /* expr ::= expr MODULO expr */
#line 582 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1665 "./src/Grammar/grammar.c"
        break;
      case 55: /* expr ::= expr POW expr */
#line 592 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1678 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr EQUALTO expr */
#line 602 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1691 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr NOTEQUALTO expr */
#line 612 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1704 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= expr LESSTHAN expr */
#line 622 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1717 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= expr GREATERTHAN expr */
#line 632 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1730 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= expr LORE expr */
#line 642 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1743 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= expr GORE expr */
#line 652 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1756 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= expr AND expr */
#line 662 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1769 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= expr OR expr */
#line 672 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1782 "./src/Grammar/grammar.c"
        break;
      case 64: /* expr ::= BITNOT expr */
#line 682 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1795 "./src/Grammar/grammar.c"
        break;
      case 65: /* expr ::= MINUS expr */
#line 692 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1808 "./src/Grammar/grammar.c"
        break;
      case 66: /* expr ::= NOT expr */
#line 702 "./src/Grammar/grammar.y"
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
#line 1822 "./src/Grammar/grammar.c"
        break;
      case 67: /* expr ::= expr SHIFTL expr */
#line 713 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1835 "./src/Grammar/grammar.c"
        break;
      case 68: /* expr ::= expr SHIFTR expr */
#line 723 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1848 "./src/Grammar/grammar.c"
        break;
      case 69: /* expr ::= expr BITAND expr */
#line 733 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1861 "./src/Grammar/grammar.c"
        break;
      case 70: /* expr ::= expr BITXOR expr */
#line 753 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1874 "./src/Grammar/grammar.c"
        break;
      case 71: /* in ::= error */
#line 804 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy155)
    {
    case panopticon::OpenQuoteError:
/*        panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        panopticon::out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 1889 "./src/Grammar/grammar.c"
        break;
      case 72: /* error ::= OPENQUOTEERROR */
#line 817 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy155 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1898 "./src/Grammar/grammar.c"
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
#line 1965 "./src/Grammar/grammar.c"
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
#line 1987 "./src/Grammar/grammar.c"
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
