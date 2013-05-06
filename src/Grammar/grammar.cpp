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
#define YYNOCODE 76
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy151;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 141
#define YYNRULE 74
#define YYERRORSYMBOL 52
#define YYERRSYMDT yy151
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
#define YY_ACTTAB_COUNT (952)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    31,   32,   27,   28,   38,   37,   35,   33,   36,   34,
 /*    10 */    30,   29,   48,   45,   43,   41,   40,   39,   31,   32,
 /*    20 */    27,   28,   38,   37,   35,   33,   36,   34,   30,   29,
 /*    30 */    48,   45,   43,   41,   40,   39,   43,   41,   40,   39,
 /*    40 */    46,  126,    3,  139,  138,   22,   31,   32,   27,   28,
 /*    50 */    38,   37,   35,   33,   36,   34,   30,   29,   48,   45,
 /*    60 */    43,   41,   40,   39,   12,   10,   93,   92,  114,  125,
 /*    70 */     6,  107,   47,   44,   39,   31,   32,   27,   28,   38,
 /*    80 */    37,   35,   33,   36,   34,   30,   29,   48,   45,   43,
 /*    90 */    41,   40,   39,   30,   29,   48,   45,   43,   41,   40,
 /*   100 */    39,  121,   23,  117,   21,   19,  120,   31,   32,   27,
 /*   110 */    28,   38,   37,   35,   33,   36,   34,   30,   29,   48,
 /*   120 */    45,   43,   41,   40,   39,   48,   45,   43,   41,   40,
 /*   130 */    39,   96,   14,  118,  112,   20,   16,  216,    1,   31,
 /*   140 */    32,   27,   28,   38,   37,   35,   33,   36,   34,   30,
 /*   150 */    29,   48,   45,   43,   41,   40,   39,   18,   94,   13,
 /*   160 */     8,   31,   32,   27,   28,   38,   37,   35,   33,   36,
 /*   170 */    34,   30,   29,   48,   45,   43,   41,   40,   39,   31,
 /*   180 */    32,   27,   28,   38,   37,   35,   33,   36,   34,   30,
 /*   190 */    29,   48,   45,   43,   41,   40,   39,   27,   28,   38,
 /*   200 */    37,   35,   33,   36,   34,   30,   29,   48,   45,   43,
 /*   210 */    41,   40,   39,  116,    7,  113,  111,  217,  217,   31,
 /*   220 */    32,   27,   28,   38,   37,   35,   33,   36,   34,   30,
 /*   230 */    29,   48,   45,   43,   41,   40,   39,   31,   32,   27,
 /*   240 */    28,   38,   37,   35,   33,   36,   34,   30,   29,   48,
 /*   250 */    45,   43,   41,   40,   39,  115,   31,   32,   27,   28,
 /*   260 */    38,   37,   35,   33,   36,   34,   30,   29,   48,   45,
 /*   270 */    43,   41,   40,   39,  217,   15,  217,   11,  217,  217,
 /*   280 */   217,   31,   32,   27,   28,   38,   37,   35,   33,   36,
 /*   290 */    34,   30,   29,   48,   45,   43,   41,   40,   39,    9,
 /*   300 */   217,  217,  217,   31,   32,   27,   28,   38,   37,   35,
 /*   310 */    33,   36,   34,   30,   29,   48,   45,   43,   41,   40,
 /*   320 */    39,   32,   27,   28,   38,   37,   35,   33,   36,   34,
 /*   330 */    30,   29,   48,   45,   43,   41,   40,   39,   71,  217,
 /*   340 */   217,  217,  110,  109,  137,  136,  135,  134,   86,  217,
 /*   350 */    89,   95,   85,   91,  132,  217,  129,  128,  127,   99,
 /*   360 */    28,   38,   37,   35,   33,   36,   34,   30,   29,   48,
 /*   370 */    45,   43,   41,   40,   39,   38,   37,   35,   33,   36,
 /*   380 */    34,   30,   29,   48,   45,   43,   41,   40,   39,  141,
 /*   390 */    35,   33,   36,   34,   30,   29,   48,   45,   43,   41,
 /*   400 */    40,   39,  217,  217,  217,  217,  217,   25,   71,  217,
 /*   410 */   217,  217,   24,   26,  217,  217,   42,  131,  217,    5,
 /*   420 */   217,  217,  140,   82,  132,   97,  129,  128,  127,   99,
 /*   430 */   217,  217,  217,  108,  217,    2,  106,  124,  123,  122,
 /*   440 */    71,   25,  217,  217,  217,  217,   24,   26,  217,  131,
 /*   450 */    42,    4,  217,  217,  217,  217,  132,   90,  129,  128,
 /*   460 */   127,   99,  217,   17,  217,  217,  217,  108,  217,    2,
 /*   470 */   106,  124,  123,  122,  217,  217,   25,  217,   71,  217,
 /*   480 */   217,   24,   26,  217,  217,   42,  133,  130,  217,  152,
 /*   490 */   217,  217,   90,  217,  132,  217,  129,  128,  127,   99,
 /*   500 */   217,  217,  108,  217,    2,  106,  124,  123,  122,  217,
 /*   510 */    87,   25,  217,  217,  217,    3,   24,   26,   22,  217,
 /*   520 */    42,  119,  152,  152,  152,  217,  132,   90,  129,  128,
 /*   530 */   127,   99,  217,  217,  217,  217,  217,  108,  217,    2,
 /*   540 */   106,  124,  123,  122,  217,  217,   25,  217,   60,  217,
 /*   550 */   217,   24,   26,  217,  217,   42,  217,  217,  217,  217,
 /*   560 */   217,  217,   90,  217,  132,   70,  129,  128,  127,   99,
 /*   570 */   217,   88,  108,  217,    2,  106,  124,  123,  122,  217,
 /*   580 */    59,  132,  217,  129,  128,  127,   99,  132,  217,  129,
 /*   590 */   128,  127,   99,   98,  217,  217,  132,  217,  129,  128,
 /*   600 */   127,   99,   58,  217,  217,  217,  217,  217,  217,  132,
 /*   610 */   217,  129,  128,  127,   99,  217,  105,  217,  132,  217,
 /*   620 */   129,  128,  127,   99,  217,  104,  217,  217,  217,  217,
 /*   630 */   217,  103,  132,  217,  129,  128,  127,   99,   77,  217,
 /*   640 */   217,  132,  217,  129,  128,  127,   99,  132,  217,  129,
 /*   650 */   128,  127,   99,   76,  132,  217,  129,  128,  127,   99,
 /*   660 */   217,  217,  217,   81,  217,  217,  217,  217,  217,  132,
 /*   670 */    80,  129,  128,  127,   99,  217,   79,  217,  217,  132,
 /*   680 */   217,  129,  128,  127,   99,   78,  132,  217,  129,  128,
 /*   690 */   127,   99,  132,  217,  129,  128,  127,   99,   73,  217,
 /*   700 */   217,  132,  217,  129,  128,  127,   99,   72,  217,  217,
 /*   710 */   217,  217,  217,   84,  132,  217,  129,  128,  127,   99,
 /*   720 */   217,  217,  217,  132,   83,  129,  128,  127,   99,  132,
 /*   730 */    75,  129,  128,  127,   99,  217,   74,  217,  217,  217,
 /*   740 */   132,  217,  129,  128,  127,   99,  132,  217,  129,  128,
 /*   750 */   127,   99,  132,  217,  129,  128,  127,   99,  102,  217,
 /*   760 */   217,  217,  217,  217,  217,  217,  217,  101,  217,  217,
 /*   770 */   217,  217,  217,  100,  132,  217,  129,  128,  127,   99,
 /*   780 */    57,  217,  217,  132,  217,  129,  128,  127,   99,  132,
 /*   790 */    56,  129,  128,  127,   99,  217,  132,   55,  129,  128,
 /*   800 */   127,   99,  217,   69,  217,  217,  132,  217,  129,  128,
 /*   810 */   127,   99,   54,  132,  217,  129,  128,  127,   99,  132,
 /*   820 */   217,  129,  128,  127,   99,  217,  217,   68,  132,  217,
 /*   830 */   129,  128,  127,   99,   52,  217,  217,  217,  217,  217,
 /*   840 */    51,  217,  217,  132,  217,  129,  128,  127,   99,  217,
 /*   850 */   132,   67,  129,  128,  127,   99,  132,   66,  129,  128,
 /*   860 */   127,   99,  217,   65,  217,  217,  217,  132,  217,  129,
 /*   870 */   128,  127,   99,  132,  217,  129,  128,  127,   99,  132,
 /*   880 */   217,  129,  128,  127,   99,   50,  217,  217,  217,  217,
 /*   890 */   217,  217,  217,  217,   64,  217,  217,  217,  217,  217,
 /*   900 */    49,  132,  217,  129,  128,  127,   99,   63,  217,  217,
 /*   910 */   132,  217,  129,  128,  127,   99,  132,   62,  129,  128,
 /*   920 */   127,   99,  217,  132,   61,  129,  128,  127,   99,  217,
 /*   930 */    53,  217,  217,  132,  217,  129,  128,  127,   99,  217,
 /*   940 */   132,  217,  129,  128,  127,   99,  132,  217,  129,  128,
 /*   950 */   127,   99,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    10 */    15,   16,   17,   18,   19,   20,   21,   22,    5,    6,
 /*    20 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*    30 */    17,   18,   19,   20,   21,   22,   19,   20,   21,   22,
 /*    40 */    45,   28,   27,   33,   33,   30,    5,    6,    7,    8,
 /*    50 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*    60 */    19,   20,   21,   22,   35,   36,   37,   38,   39,   28,
 /*    70 */     1,   34,    1,   27,   22,    5,    6,    7,    8,    9,
 /*    80 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*    90 */    20,   21,   22,   15,   16,   17,   18,   19,   20,   21,
 /*   100 */    22,   31,   30,   34,   35,   36,   31,    5,    6,    7,
 /*   110 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   120 */    18,   19,   20,   21,   22,   17,   18,   19,   20,   21,
 /*   130 */    22,   37,   43,   31,   52,    1,   42,   55,   56,    5,
 /*   140 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   150 */    16,   17,   18,   19,   20,   21,   22,    1,   34,    1,
 /*   160 */     1,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   170 */    14,   15,   16,   17,   18,   19,   20,   21,   22,    5,
 /*   180 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   190 */    16,   17,   18,   19,   20,   21,   22,    7,    8,    9,
 /*   200 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   210 */    20,   21,   22,   39,    1,   39,   51,   75,   75,    5,
 /*   220 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   230 */    16,   17,   18,   19,   20,   21,   22,    5,    6,    7,
 /*   240 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   250 */    18,   19,   20,   21,   22,   41,    5,    6,    7,    8,
 /*   260 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   270 */    19,   20,   21,   22,   75,   43,   75,    1,   75,   75,
 /*   280 */    75,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   290 */    14,   15,   16,   17,   18,   19,   20,   21,   22,    1,
 /*   300 */    75,   75,   75,    5,    6,    7,    8,    9,   10,   11,
 /*   310 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   320 */    22,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   330 */    15,   16,   17,   18,   19,   20,   21,   22,   53,   75,
 /*   340 */    75,   75,   57,   58,   59,   60,   61,   62,   63,   75,
 /*   350 */    65,   66,   67,   68,   69,   75,   71,   72,   73,   74,
 /*   360 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   370 */    18,   19,   20,   21,   22,    9,   10,   11,   12,   13,
 /*   380 */    14,   15,   16,   17,   18,   19,   20,   21,   22,    0,
 /*   390 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   400 */    21,   22,   75,   75,   75,   75,   75,   18,   53,   75,
 /*   410 */    75,   75,   23,   24,   75,   75,   27,   62,   75,   64,
 /*   420 */    75,   75,   33,   34,   69,   70,   71,   72,   73,   74,
 /*   430 */    75,   75,   75,   44,   75,   46,   47,   48,   49,   50,
 /*   440 */    53,   18,   75,   75,   75,   75,   23,   24,   75,   62,
 /*   450 */    27,   64,   75,   75,   75,   75,   69,   34,   71,   72,
 /*   460 */    73,   74,   75,   40,   75,   75,   75,   44,   75,   46,
 /*   470 */    47,   48,   49,   50,   75,   75,   18,   75,   53,   75,
 /*   480 */    75,   23,   24,   75,   75,   27,   28,   62,   75,    1,
 /*   490 */    75,   75,   34,   75,   69,   75,   71,   72,   73,   74,
 /*   500 */    75,   75,   44,   75,   46,   47,   48,   49,   50,   75,
 /*   510 */    53,   18,   75,   75,   75,   27,   23,   24,   30,   75,
 /*   520 */    27,   28,   34,   35,   36,   75,   69,   34,   71,   72,
 /*   530 */    73,   74,   75,   75,   75,   75,   75,   44,   75,   46,
 /*   540 */    47,   48,   49,   50,   75,   75,   18,   75,   53,   75,
 /*   550 */    75,   23,   24,   75,   75,   27,   75,   75,   75,   75,
 /*   560 */    75,   75,   34,   75,   69,   53,   71,   72,   73,   74,
 /*   570 */    75,   53,   44,   75,   46,   47,   48,   49,   50,   75,
 /*   580 */    53,   69,   75,   71,   72,   73,   74,   69,   75,   71,
 /*   590 */    72,   73,   74,   53,   75,   75,   69,   75,   71,   72,
 /*   600 */    73,   74,   53,   75,   75,   75,   75,   75,   75,   69,
 /*   610 */    75,   71,   72,   73,   74,   75,   53,   75,   69,   75,
 /*   620 */    71,   72,   73,   74,   75,   53,   75,   75,   75,   75,
 /*   630 */    75,   53,   69,   75,   71,   72,   73,   74,   53,   75,
 /*   640 */    75,   69,   75,   71,   72,   73,   74,   69,   75,   71,
 /*   650 */    72,   73,   74,   53,   69,   75,   71,   72,   73,   74,
 /*   660 */    75,   75,   75,   53,   75,   75,   75,   75,   75,   69,
 /*   670 */    53,   71,   72,   73,   74,   75,   53,   75,   75,   69,
 /*   680 */    75,   71,   72,   73,   74,   53,   69,   75,   71,   72,
 /*   690 */    73,   74,   69,   75,   71,   72,   73,   74,   53,   75,
 /*   700 */    75,   69,   75,   71,   72,   73,   74,   53,   75,   75,
 /*   710 */    75,   75,   75,   53,   69,   75,   71,   72,   73,   74,
 /*   720 */    75,   75,   75,   69,   53,   71,   72,   73,   74,   69,
 /*   730 */    53,   71,   72,   73,   74,   75,   53,   75,   75,   75,
 /*   740 */    69,   75,   71,   72,   73,   74,   69,   75,   71,   72,
 /*   750 */    73,   74,   69,   75,   71,   72,   73,   74,   53,   75,
 /*   760 */    75,   75,   75,   75,   75,   75,   75,   53,   75,   75,
 /*   770 */    75,   75,   75,   53,   69,   75,   71,   72,   73,   74,
 /*   780 */    53,   75,   75,   69,   75,   71,   72,   73,   74,   69,
 /*   790 */    53,   71,   72,   73,   74,   75,   69,   53,   71,   72,
 /*   800 */    73,   74,   75,   53,   75,   75,   69,   75,   71,   72,
 /*   810 */    73,   74,   53,   69,   75,   71,   72,   73,   74,   69,
 /*   820 */    75,   71,   72,   73,   74,   75,   75,   53,   69,   75,
 /*   830 */    71,   72,   73,   74,   53,   75,   75,   75,   75,   75,
 /*   840 */    53,   75,   75,   69,   75,   71,   72,   73,   74,   75,
 /*   850 */    69,   53,   71,   72,   73,   74,   69,   53,   71,   72,
 /*   860 */    73,   74,   75,   53,   75,   75,   75,   69,   75,   71,
 /*   870 */    72,   73,   74,   69,   75,   71,   72,   73,   74,   69,
 /*   880 */    75,   71,   72,   73,   74,   53,   75,   75,   75,   75,
 /*   890 */    75,   75,   75,   75,   53,   75,   75,   75,   75,   75,
 /*   900 */    53,   69,   75,   71,   72,   73,   74,   53,   75,   75,
 /*   910 */    69,   75,   71,   72,   73,   74,   69,   53,   71,   72,
 /*   920 */    73,   74,   75,   69,   53,   71,   72,   73,   74,   75,
 /*   930 */    53,   75,   75,   69,   75,   71,   72,   73,   74,   75,
 /*   940 */    69,   75,   71,   72,   73,   74,   69,   75,   71,   72,
 /*   950 */    73,   74,
};
#define YY_SHIFT_USE_DFLT (-6)
#define YY_SHIFT_COUNT (110)
#define YY_SHIFT_MIN   (-5)
#define YY_SHIFT_MAX   (528)
static const short yy_shift_ofst[] = {
 /*     0 */   165,  389,  528,  493,  458,  528,  423,  528,  528,  528,
 /*    10 */   528,  528,  528,  528,  528,  528,  528,  528,  528,  528,
 /*    20 */   528,  528,  528,  528,  528,  528,  528,  528,  528,  528,
 /*    30 */   528,  528,  528,  528,  528,  528,  528,  528,  528,  528,
 /*    40 */   528,  528,  528,  528,  528,  528,  528,  528,  528,  298,
 /*    50 */   276,  232,  214,  174,  156,  134,  102,   70,   41,   13,
 /*    60 */    -5,  251,  251,  251,  251,  251,  251,  251,  251,  251,
 /*    70 */   251,  251,  315,  190,  352,  366,  379,  379,   78,   78,
 /*    80 */    78,   78,  488,  108,  108,   29,   69,   17,   17,   94,
 /*    90 */    15,  176,  213,  159,  158,  124,   89,   75,   52,   72,
 /*   100 */    52,   52,   52,   52,   52,   52,   46,   71,   37,   11,
 /*   110 */    10,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (48)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (877)
static const short yy_reduce_ofst[] = {
 /*     0 */    82,  285,  355,  387,  425,  425,  877,  871,  864,  854,
 /*    10 */   847,  841,  832,  810,  804,  798,  787,  781,  774,  759,
 /*    20 */   750,  744,  737,  727,  720,  714,  705,  683,  677,  671,
 /*    30 */   660,  654,  645,  632,  623,  617,  610,  600,  585,  578,
 /*    40 */   572,  563,  549,  540,  527,  518,  512,  495,  457,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   142,  215,  179,  215,  215,  180,  215,  215,  215,  215,
 /*    10 */   215,  215,  215,  215,  215,  215,  215,  215,  215,  215,
 /*    20 */   215,  215,  215,  215,  215,  215,  215,  215,  215,  215,
 /*    30 */   215,  215,  215,  215,  215,  215,  215,  215,  215,  215,
 /*    40 */   215,  215,  215,  215,  215,  215,  215,  215,  215,  215,
 /*    50 */   215,  215,  215,  174,  215,  215,  215,  215,  215,  215,
 /*    60 */   215,  165,  164,  163,  162,  169,  172,  171,  161,  160,
 /*    70 */   173,  150,  202,  201,  209,  208,  196,  195,  200,  199,
 /*    80 */   198,  197,  153,  207,  206,  158,  215,  189,  190,  156,
 /*    90 */   153,  159,  215,  215,  215,  157,  215,  215,  191,  212,
 /*   100 */   205,  204,  203,  194,  193,  192,  215,  215,  215,  215,
 /*   110 */   215,  214,  213,  167,  166,  170,  168,  151,  210,  155,
 /*   120 */   178,  211,  188,  187,  186,  185,  184,  183,  182,  181,
 /*   130 */   176,  175,  177,  154,  149,  148,  147,  146,  145,  144,
 /*   140 */   143,
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
  "LET",           "IN",            "OPENBRAC",      "PRINT",       
  "NUM",           "STRING",        "BOOLEAN",       "OPENQUOTEERROR",
  "error",         "expr",          "id",            "main",        
  "in",            "start",         "test",          "spec",        
  "assignment",    "top_stmt",      "stmt",          "name_chain",  
  "stmt_list",     "case_statement",  "where_statement",  "guard_statement",
  "final_guard_statement",  "array",         "maybe_empty_stmt_list",  "num",         
  "string",        "bool",          "array_index", 
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
 /*   6 */ "spec ::= assignment",
 /*   7 */ "spec ::= top_stmt",
 /*   8 */ "top_stmt ::= stmt",
 /*   9 */ "stmt ::= expr",
 /*  10 */ "name_chain ::= name_chain NAME",
 /*  11 */ "name_chain ::= NAME",
 /*  12 */ "expr ::= NAME",
 /*  13 */ "expr ::= NAME LPAREN stmt_list RPAREN",
 /*  14 */ "expr ::= NAME LPAREN RPAREN",
 /*  15 */ "test ::= case_statement",
 /*  16 */ "spec ::= where_statement",
 /*  17 */ "assignment ::= guard_statement",
 /*  18 */ "assignment ::= final_guard_statement",
 /*  19 */ "guard_statement ::= name_chain GUARD_N expr ASSIGN expr",
 /*  20 */ "guard_statement ::= name_chain GUARD_S expr ASSIGN expr",
 /*  21 */ "guard_statement ::= guard_statement GUARD_N expr ASSIGN expr",
 /*  22 */ "guard_statement ::= guard_statement GUARD_S expr ASSIGN expr",
 /*  23 */ "final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr",
 /*  24 */ "final_guard_statement ::= guard_statement WILDCARD ASSIGN expr",
 /*  25 */ "where_statement ::= guard_statement WHERE",
 /*  26 */ "where_statement ::= final_guard_statement WHERE",
 /*  27 */ "where_statement ::= name_chain ASSIGN expr WHERE",
 /*  28 */ "where_statement ::= where_statement NAME ASSIGN expr",
 /*  29 */ "case_statement ::= name_chain ASSIGN CASE expr OF",
 /*  30 */ "case_statement ::= case_statement N_TAB expr POINTER expr",
 /*  31 */ "case_statement ::= case_statement WILDCARD_N POINTER expr",
 /*  32 */ "expr ::= LET NAME ASSIGN expr IN expr",
 /*  33 */ "assignment ::= name_chain ASSIGN expr",
 /*  34 */ "stmt_list ::= stmt",
 /*  35 */ "stmt_list ::= stmt_list stmt",
 /*  36 */ "expr ::= array",
 /*  37 */ "array ::= OPENBRAC maybe_empty_stmt_list RBRAC",
 /*  38 */ "maybe_empty_stmt_list ::=",
 /*  39 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  40 */ "expr ::= num",
 /*  41 */ "expr ::= string",
 /*  42 */ "expr ::= bool",
 /*  43 */ "expr ::= PRINT LPAREN expr RPAREN",
 /*  44 */ "expr ::= LPAREN expr RPAREN",
 /*  45 */ "num ::= NUM",
 /*  46 */ "string ::= STRING",
 /*  47 */ "bool ::= BOOLEAN",
 /*  48 */ "expr ::= expr PLUS expr",
 /*  49 */ "expr ::= expr MINUS expr",
 /*  50 */ "expr ::= expr DIVIDE expr",
 /*  51 */ "expr ::= expr TIMES expr",
 /*  52 */ "expr ::= expr MODULO expr",
 /*  53 */ "expr ::= expr POW expr",
 /*  54 */ "expr ::= expr EQUALTO expr",
 /*  55 */ "expr ::= expr NOTEQUALTO expr",
 /*  56 */ "expr ::= expr LESSTHAN expr",
 /*  57 */ "expr ::= expr GREATERTHAN expr",
 /*  58 */ "expr ::= expr LORE expr",
 /*  59 */ "expr ::= expr GORE expr",
 /*  60 */ "expr ::= expr AND expr",
 /*  61 */ "expr ::= expr OR expr",
 /*  62 */ "expr ::= BITNOT expr",
 /*  63 */ "expr ::= MINUS expr",
 /*  64 */ "expr ::= NOT expr",
 /*  65 */ "expr ::= expr SHIFTL expr",
 /*  66 */ "expr ::= expr SHIFTR expr",
 /*  67 */ "expr ::= expr BITAND expr",
 /*  68 */ "expr ::= expr BITXOR expr",
 /*  69 */ "array_index ::= NAME LBRAC expr RBRAC",
 /*  70 */ "array_index ::= array_index LBRAC expr RBRAC",
 /*  71 */ "expr ::= array_index",
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
    case 47: /* PRINT */
    case 48: /* NUM */
    case 49: /* STRING */
    case 50: /* BOOLEAN */
    case 51: /* OPENQUOTEERROR */
{
#line 43 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 781 "./src/Grammar/grammar.c"
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
  { 55, 1 },
  { 56, 0 },
  { 56, 2 },
  { 56, 3 },
  { 56, 3 },
  { 57, 1 },
  { 59, 1 },
  { 59, 1 },
  { 61, 1 },
  { 62, 1 },
  { 63, 2 },
  { 63, 1 },
  { 53, 1 },
  { 53, 4 },
  { 53, 3 },
  { 58, 1 },
  { 59, 1 },
  { 60, 1 },
  { 60, 1 },
  { 67, 5 },
  { 67, 5 },
  { 67, 5 },
  { 67, 5 },
  { 68, 4 },
  { 68, 4 },
  { 66, 2 },
  { 66, 2 },
  { 66, 4 },
  { 66, 4 },
  { 65, 5 },
  { 65, 5 },
  { 65, 4 },
  { 53, 6 },
  { 60, 3 },
  { 64, 1 },
  { 64, 2 },
  { 53, 1 },
  { 69, 3 },
  { 70, 0 },
  { 70, 1 },
  { 53, 1 },
  { 53, 1 },
  { 53, 1 },
  { 53, 4 },
  { 53, 3 },
  { 71, 1 },
  { 72, 1 },
  { 73, 1 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 2 },
  { 53, 2 },
  { 53, 2 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 74, 4 },
  { 74, 4 },
  { 53, 1 },
  { 56, 1 },
  { 52, 1 },
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
#line 1154 "./src/Grammar/grammar.c"
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
        optic::resolve_stack_from_parser(yymsp[0].minor.yy0, true);
    }
}
#line 1177 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= assignment */
#line 131 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1184 "./src/Grammar/grammar.c"
        break;
      case 7: /* spec ::= top_stmt */
      case 8: /* top_stmt ::= stmt */ yytestcase(yyruleno==8);
#line 136 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1193 "./src/Grammar/grammar.c"
        break;
      case 9: /* stmt ::= expr */
      case 34: /* stmt_list ::= stmt */ yytestcase(yyruleno==34);
#line 148 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1202 "./src/Grammar/grammar.c"
        break;
      case 10: /* name_chain ::= name_chain NAME */
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
#line 1241 "./src/Grammar/grammar.c"
        break;
      case 11: /* name_chain ::= NAME */
#line 191 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1250 "./src/Grammar/grammar.c"
        break;
      case 12: /* expr ::= NAME */
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
#line 1263 "./src/Grammar/grammar.c"
        break;
      case 13: /* expr ::= NAME LPAREN stmt_list RPAREN */
#line 214 "./src/Grammar/grammar.y"
{
    if(yymsp[-1].minor.yy0.type==optic::STATEMENT_LIST)
    {
/*            yymsp[-1].minor.yy0 = de_tree(yymsp[-1].minor.yy0);*/
            yymsp[-1].minor.yy0.type = optic::FUNCTION_ARG_VALUES;
    }
    else
    {
        optic::object temp = yymsp[-1].minor.yy0;
        yymsp[-1].minor.yy0.type = optic::FUNCTION_ARG_VALUES;
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
#line 1296 "./src/Grammar/grammar.c"
        break;
      case 14: /* expr ::= NAME LPAREN RPAREN */
#line 243 "./src/Grammar/grammar.y"
{
    optic::object C;
    C.type = optic::FUNCTION_ARG_VALUES;
    C.data.array = new optic::Array();
/*    optic::object v;*/
/*    v.type = optic::VOID;*/
/*    C.data.array->push_back(v);*/
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
#line 1319 "./src/Grammar/grammar.c"
        break;
      case 15: /* test ::= case_statement */
#line 262 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
/*    panopticon::out() << "Case: " << *yymsp[0].minor.yy0.data.array->at(0).data.string << std::endl;*/
}
#line 1327 "./src/Grammar/grammar.c"
        break;
      case 16: /* spec ::= where_statement */
#line 268 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Where: " << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1335 "./src/Grammar/grammar.c"
        break;
      case 17: /* assignment ::= guard_statement */
      case 18: /* assignment ::= final_guard_statement */ yytestcase(yyruleno==18);
#line 274 "./src/Grammar/grammar.y"
{
    panopticon::object& b = yymsp[0].minor.yy0.data.array->at(0);
    panopticon::object& c = yymsp[0].minor.yy0.data.array->at(1);

    panopticon::object resolve;
    panopticon::store_operations(resolve, c, &panopticon::resolve_guard);

    insure_ready_for_assignment(b,resolve);
    b.type = optic::FUNCTION_ARG_NAMES;
    panopticon::parse_operations(yygotominor.yy0, b, resolve, &panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1356 "./src/Grammar/grammar.c"
        break;
      case 19: /* guard_statement ::= name_chain GUARD_N expr ASSIGN expr */
#line 315 "./src/Grammar/grammar.y"
{
    optic::object tree = create_condition_tree(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0 = create_guard(yymsp[-4].minor.yy0,tree);
  yy_destructor(yypParser,35,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1366 "./src/Grammar/grammar.c"
        break;
      case 20: /* guard_statement ::= name_chain GUARD_S expr ASSIGN expr */
#line 321 "./src/Grammar/grammar.y"
{
    optic::object tree = create_condition_tree(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0 = create_guard(yymsp[-4].minor.yy0,tree);
  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1376 "./src/Grammar/grammar.c"
        break;
      case 21: /* guard_statement ::= guard_statement GUARD_N expr ASSIGN expr */
#line 327 "./src/Grammar/grammar.y"
{
    add_branch_to_tree(yymsp[-4].minor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0=yymsp[-4].minor.yy0;
  yy_destructor(yypParser,35,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1386 "./src/Grammar/grammar.c"
        break;
      case 22: /* guard_statement ::= guard_statement GUARD_S expr ASSIGN expr */
#line 333 "./src/Grammar/grammar.y"
{
    add_branch_to_tree(yymsp[-4].minor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0=yymsp[-4].minor.yy0;
  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1396 "./src/Grammar/grammar.c"
        break;
      case 23: /* final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr */
#line 339 "./src/Grammar/grammar.y"
{
    add_wildcard_to_tree(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0=yymsp[-3].minor.yy0;
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1406 "./src/Grammar/grammar.c"
        break;
      case 24: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr */
#line 345 "./src/Grammar/grammar.y"
{
    add_wildcard_to_tree(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0=yymsp[-3].minor.yy0;
  yy_destructor(yypParser,38,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1416 "./src/Grammar/grammar.c"
        break;
      case 25: /* where_statement ::= guard_statement WHERE */
      case 26: /* where_statement ::= final_guard_statement WHERE */ yytestcase(yyruleno==26);
#line 350 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1424 "./src/Grammar/grammar.c"
        break;
      case 27: /* where_statement ::= name_chain ASSIGN expr WHERE */
#line 352 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1432 "./src/Grammar/grammar.c"
        break;
      case 28: /* where_statement ::= where_statement NAME ASSIGN expr */
#line 354 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,34,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1440 "./src/Grammar/grammar.c"
        break;
      case 29: /* case_statement ::= name_chain ASSIGN CASE expr OF */
#line 357 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,40,&yymsp[-2].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1451 "./src/Grammar/grammar.c"
        break;
      case 30: /* case_statement ::= case_statement N_TAB expr POINTER expr */
#line 363 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,42,&yymsp[-3].minor);
  yy_destructor(yypParser,43,&yymsp[-1].minor);
}
#line 1461 "./src/Grammar/grammar.c"
        break;
      case 31: /* case_statement ::= case_statement WILDCARD_N POINTER expr */
#line 369 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,43,&yymsp[-1].minor);
}
#line 1471 "./src/Grammar/grammar.c"
        break;
      case 32: /* expr ::= LET NAME ASSIGN expr IN expr */
#line 375 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Let");
  yy_destructor(yypParser,44,&yymsp[-5].minor);
  yy_destructor(yypParser,34,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,45,&yymsp[-1].minor);
}
#line 1483 "./src/Grammar/grammar.c"
        break;
      case 33: /* assignment ::= name_chain ASSIGN expr */
#line 381 "./src/Grammar/grammar.y"
{
    insure_ready_for_assignment(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yymsp[-2].minor.yy0.type = optic::FUNCTION_ARG_NAMES;
    panopticon::parse_operations(yygotominor.yy0, yymsp[-2].minor.yy0, yymsp[0].minor.yy0, panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1498 "./src/Grammar/grammar.c"
        break;
      case 35: /* stmt_list ::= stmt_list stmt */
#line 403 "./src/Grammar/grammar.y"
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
#line 1517 "./src/Grammar/grammar.c"
        break;
      case 36: /* expr ::= array */
      case 71: /* expr ::= array_index */ yytestcase(yyruleno==71);
#line 428 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1525 "./src/Grammar/grammar.c"
        break;
      case 37: /* array ::= OPENBRAC maybe_empty_stmt_list RBRAC */
#line 433 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yygotominor.yy0.type = optic::ARRAY;
/*    create_tree(yygotominor.yy0,de_tree(yymsp[-1].minor.yy0));*/
  yy_destructor(yypParser,46,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1536 "./src/Grammar/grammar.c"
        break;
      case 38: /* maybe_empty_stmt_list ::= */
#line 440 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1544 "./src/Grammar/grammar.c"
        break;
      case 39: /* maybe_empty_stmt_list ::= stmt_list */
#line 446 "./src/Grammar/grammar.y"
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
#line 1560 "./src/Grammar/grammar.c"
        break;
      case 40: /* expr ::= num */
      case 42: /* expr ::= bool */ yytestcase(yyruleno==42);
#line 470 "./src/Grammar/grammar.y"
{
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1568 "./src/Grammar/grammar.c"
        break;
      case 41: /* expr ::= string */
#line 475 "./src/Grammar/grammar.y"
{
   create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1575 "./src/Grammar/grammar.c"
        break;
      case 43: /* expr ::= PRINT LPAREN expr RPAREN */
#line 489 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-1].minor.yy0,&optic::unary_print_object);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,47,&yymsp[-3].minor);
  yy_destructor(yypParser,27,&yymsp[-2].minor);
  yy_destructor(yypParser,28,&yymsp[0].minor);
}
#line 1590 "./src/Grammar/grammar.c"
        break;
      case 44: /* expr ::= LPAREN expr RPAREN */
#line 499 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
  yy_destructor(yypParser,27,&yymsp[-2].minor);
  yy_destructor(yypParser,28,&yymsp[0].minor);
}
#line 1599 "./src/Grammar/grammar.c"
        break;
      case 45: /* num ::= NUM */
#line 504 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;*/
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1608 "./src/Grammar/grammar.c"
        break;
      case 46: /* string ::= STRING */
#line 511 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());*/
/*    delete yymsp[0].minor.yy0.data.string;*/
    yymsp[0].minor.yy0.type = panopticon::STRING;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1618 "./src/Grammar/grammar.c"
        break;
      case 47: /* bool ::= BOOLEAN */
#line 520 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;*/
    yymsp[0].minor.yy0.type = panopticon::BOOL;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1627 "./src/Grammar/grammar.c"
        break;
      case 48: /* expr ::= expr PLUS expr */
#line 552 "./src/Grammar/grammar.y"
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
#line 1642 "./src/Grammar/grammar.c"
        break;
      case 49: /* expr ::= expr MINUS expr */
#line 564 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1655 "./src/Grammar/grammar.c"
        break;
      case 50: /* expr ::= expr DIVIDE expr */
#line 574 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1668 "./src/Grammar/grammar.c"
        break;
      case 51: /* expr ::= expr TIMES expr */
#line 584 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1681 "./src/Grammar/grammar.c"
        break;
      case 52: /* expr ::= expr MODULO expr */
#line 594 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1694 "./src/Grammar/grammar.c"
        break;
      case 53: /* expr ::= expr POW expr */
#line 604 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1707 "./src/Grammar/grammar.c"
        break;
      case 54: /* expr ::= expr EQUALTO expr */
#line 614 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1720 "./src/Grammar/grammar.c"
        break;
      case 55: /* expr ::= expr NOTEQUALTO expr */
#line 624 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1733 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr LESSTHAN expr */
#line 634 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1746 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr GREATERTHAN expr */
#line 644 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1759 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= expr LORE expr */
#line 654 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1772 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= expr GORE expr */
#line 664 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1785 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= expr AND expr */
#line 674 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1798 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= expr OR expr */
#line 684 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1811 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= BITNOT expr */
#line 694 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1824 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= MINUS expr */
#line 704 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1837 "./src/Grammar/grammar.c"
        break;
      case 64: /* expr ::= NOT expr */
#line 714 "./src/Grammar/grammar.y"
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
#line 1851 "./src/Grammar/grammar.c"
        break;
      case 65: /* expr ::= expr SHIFTL expr */
#line 725 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1864 "./src/Grammar/grammar.c"
        break;
      case 66: /* expr ::= expr SHIFTR expr */
#line 735 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1877 "./src/Grammar/grammar.c"
        break;
      case 67: /* expr ::= expr BITAND expr */
#line 745 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1890 "./src/Grammar/grammar.c"
        break;
      case 68: /* expr ::= expr BITXOR expr */
#line 765 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1903 "./src/Grammar/grammar.c"
        break;
      case 69: /* array_index ::= NAME LBRAC expr RBRAC */
#line 775 "./src/Grammar/grammar.y"
{
    yymsp[-3].minor.yy0.type = optic::STRING;
    optic::store_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,30,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1918 "./src/Grammar/grammar.c"
        break;
      case 70: /* array_index ::= array_index LBRAC expr RBRAC */
#line 786 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,30,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1932 "./src/Grammar/grammar.c"
        break;
      case 72: /* in ::= error */
#line 830 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy151)
    {
    case panopticon::OpenQuoteError:
/*        panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        panopticon::out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 1947 "./src/Grammar/grammar.c"
        break;
      case 73: /* error ::= OPENQUOTEERROR */
#line 843 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy151 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1956 "./src/Grammar/grammar.c"
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
#line 2023 "./src/Grammar/grammar.c"
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
#line 2045 "./src/Grammar/grammar.c"
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
