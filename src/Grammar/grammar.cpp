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
#define YYNOCODE 75
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy149;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 137
#define YYNRULE 72
#define YYERRORSYMBOL 52
#define YYERRSYMDT yy149
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
#define YY_ACTTAB_COUNT (897)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    30,   31,   26,   27,   37,   36,   34,   32,   35,   33,
 /*    10 */    29,   28,   47,   44,   42,   40,   39,   38,   30,   31,
 /*    20 */    26,   27,   37,   36,   34,   32,   35,   33,   29,   28,
 /*    30 */    47,   44,   42,   40,   39,   38,   42,   40,   39,   38,
 /*    40 */    45,  122,    3,  135,  134,   22,   30,   31,   26,   27,
 /*    50 */    37,   36,   34,   32,   35,   33,   29,   28,   47,   44,
 /*    60 */    42,   40,   39,   38,   12,   10,   91,   90,  111,  121,
 /*    70 */   109,  104,   46,  210,    1,   30,   31,   26,   27,   37,
 /*    80 */    36,   34,   32,   35,   33,   29,   28,   47,   44,   42,
 /*    90 */    40,   39,   38,   29,   28,   47,   44,   42,   40,   39,
 /*   100 */    38,  115,   43,   20,   38,  117,   14,   30,   31,   26,
 /*   110 */    27,   37,   36,   34,   32,   35,   33,   29,   28,   47,
 /*   120 */    44,   42,   40,   39,   38,   18,   92,   13,    8,   30,
 /*   130 */    31,   26,   27,   37,   36,   34,   32,   35,   33,   29,
 /*   140 */    28,   47,   44,   42,   40,   39,   38,   30,   31,   26,
 /*   150 */    27,   37,   36,   34,   32,   35,   33,   29,   28,   47,
 /*   160 */    44,   42,   40,   39,   38,   26,   27,   37,   36,   34,
 /*   170 */    32,   35,   33,   29,   28,   47,   44,   42,   40,   39,
 /*   180 */    38,  113,    7,  110,  108,  211,  211,   30,   31,   26,
 /*   190 */    27,   37,   36,   34,   32,   35,   33,   29,   28,   47,
 /*   200 */    44,   42,   40,   39,   38,   30,   31,   26,   27,   37,
 /*   210 */    36,   34,   32,   35,   33,   29,   28,   47,   44,   42,
 /*   220 */    40,   39,   38,  112,   30,   31,   26,   27,   37,   36,
 /*   230 */    34,   32,   35,   33,   29,   28,   47,   44,   42,   40,
 /*   240 */    39,   38,   94,   15,  211,   11,  211,   16,  211,   30,
 /*   250 */    31,   26,   27,   37,   36,   34,   32,   35,   33,   29,
 /*   260 */    28,   47,   44,   42,   40,   39,   38,    9,  211,  211,
 /*   270 */   211,   30,   31,   26,   27,   37,   36,   34,   32,   35,
 /*   280 */    33,   29,   28,   47,   44,   42,   40,   39,   38,   31,
 /*   290 */    26,   27,   37,   36,   34,   32,   35,   33,   29,   28,
 /*   300 */    47,   44,   42,   40,   39,   38,   69,  211,  211,  211,
 /*   310 */   107,  106,  133,  132,  131,  130,   84,  211,   87,   93,
 /*   320 */    83,   89,  128,  211,  125,  124,  123,   27,   37,   36,
 /*   330 */    34,   32,   35,   33,   29,   28,   47,   44,   42,   40,
 /*   340 */    39,   38,   37,   36,   34,   32,   35,   33,   29,   28,
 /*   350 */    47,   44,   42,   40,   39,   38,  137,   34,   32,   35,
 /*   360 */    33,   29,   28,   47,   44,   42,   40,   39,   38,  211,
 /*   370 */   211,  211,  211,  211,   24,   69,    6,  211,  211,   23,
 /*   380 */    25,  211,  211,   41,  127,  211,    5,  211,  211,  136,
 /*   390 */    80,  128,   95,  125,  124,  123,  211,  211,  211,  211,
 /*   400 */   105,  211,    2,  103,  120,  119,  118,   69,   24,  114,
 /*   410 */    21,   19,  211,   23,   25,  211,  127,   41,    4,  211,
 /*   420 */   211,  211,  211,  128,   88,  125,  124,  123,  211,  211,
 /*   430 */    17,  211,  211,  211,  105,  211,    2,  103,  120,  119,
 /*   440 */   118,  211,  211,   24,  211,  211,  211,  211,   23,   25,
 /*   450 */   211,  211,   41,  129,  211,  211,  211,  211,  211,   88,
 /*   460 */   211,   47,   44,   42,   40,   39,   38,  148,  211,  105,
 /*   470 */   211,    2,  103,  120,  119,  118,  211,  211,   24,   85,
 /*   480 */   211,  211,  211,   23,   25,  211,  211,   41,  116,  211,
 /*   490 */   211,  211,  211,    3,   88,  128,   22,  125,  124,  123,
 /*   500 */   148,  148,  148,  211,  105,  211,    2,  103,  120,  119,
 /*   510 */   118,  211,  211,   24,  211,   69,  211,  211,   23,   25,
 /*   520 */   211,  211,   41,  211,  126,  211,  211,  211,  211,   88,
 /*   530 */   211,  128,   58,  125,  124,  123,  211,   68,  211,  105,
 /*   540 */   211,    2,  103,  120,  119,  118,  211,   86,  128,  211,
 /*   550 */   125,  124,  123,  128,   57,  125,  124,  123,  211,  211,
 /*   560 */    96,  211,  211,  128,  211,  125,  124,  123,  211,   56,
 /*   570 */   128,  211,  125,  124,  123,  211,  128,  211,  125,  124,
 /*   580 */   123,  211,  211,  102,  211,  128,  211,  125,  124,  123,
 /*   590 */   211,  101,  211,  211,  211,  211,  100,  211,  211,  128,
 /*   600 */   211,  125,  124,  123,   75,  211,  211,  128,  211,  125,
 /*   610 */   124,  123,  128,  211,  125,  124,  123,   74,  211,  211,
 /*   620 */   128,  211,  125,  124,  123,  211,   79,  211,  211,  211,
 /*   630 */   211,  211,   78,  128,  211,  125,  124,  123,  211,   77,
 /*   640 */   211,  211,  128,  211,  125,  124,  123,  211,  128,  211,
 /*   650 */   125,  124,  123,   76,  211,  128,  211,  125,  124,  123,
 /*   660 */   211,   71,  211,  211,  211,  211,   70,  211,  211,  128,
 /*   670 */   211,  125,  124,  123,   82,  211,  211,  128,  211,  125,
 /*   680 */   124,  123,  128,  211,  125,  124,  123,   81,  211,  211,
 /*   690 */   128,  211,  125,  124,  123,  211,   73,  211,  211,  211,
 /*   700 */   211,  211,   72,  128,  211,  125,  124,  123,  211,   99,
 /*   710 */   211,  211,  128,  211,  125,  124,  123,  211,  128,  211,
 /*   720 */   125,  124,  123,   98,  211,  128,  211,  125,  124,  123,
 /*   730 */   211,   97,  211,  211,  211,  211,   55,  211,  211,  128,
 /*   740 */   211,  125,  124,  123,   54,  211,  211,  128,  211,  125,
 /*   750 */   124,  123,  128,  211,  125,  124,  123,   67,  211,  211,
 /*   760 */   128,  211,  125,  124,  123,  211,   53,  211,  211,  211,
 /*   770 */   211,  211,   66,  128,  211,  125,  124,  123,  211,   51,
 /*   780 */   211,  211,  128,  211,  125,  124,  123,  211,  128,  211,
 /*   790 */   125,  124,  123,   50,  211,  128,  211,  125,  124,  123,
 /*   800 */   211,   65,  211,  211,  211,  211,   64,  211,  211,  128,
 /*   810 */   211,  125,  124,  123,   63,  211,  211,  128,  211,  125,
 /*   820 */   124,  123,  128,  211,  125,  124,  123,   49,  211,  211,
 /*   830 */   128,  211,  125,  124,  123,  211,   62,  211,  211,  211,
 /*   840 */   211,  211,   48,  128,  211,  125,  124,  123,  211,   61,
 /*   850 */   211,  211,  128,  211,  125,  124,  123,  211,  128,  211,
 /*   860 */   125,  124,  123,   60,  211,  128,  211,  125,  124,  123,
 /*   870 */   211,   59,  211,  211,  211,  211,   52,  211,  211,  128,
 /*   880 */   211,  125,  124,  123,  211,  211,  211,  128,  211,  125,
 /*   890 */   124,  123,  128,  211,  125,  124,  123,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    10 */    15,   16,   17,   18,   19,   20,   21,   22,    5,    6,
 /*    20 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*    30 */    17,   18,   19,   20,   21,   22,   19,   20,   21,   22,
 /*    40 */    45,   28,   27,   33,   33,   30,    5,    6,    7,    8,
 /*    50 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*    60 */    19,   20,   21,   22,   35,   36,   37,   38,   39,   28,
 /*    70 */    52,   34,    1,   55,   56,    5,    6,    7,    8,    9,
 /*    80 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*    90 */    20,   21,   22,   15,   16,   17,   18,   19,   20,   21,
 /*   100 */    22,   31,   27,    1,   22,   31,   43,    5,    6,    7,
 /*   110 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   120 */    18,   19,   20,   21,   22,    1,   34,    1,    1,    5,
 /*   130 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   140 */    16,   17,   18,   19,   20,   21,   22,    5,    6,    7,
 /*   150 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   160 */    18,   19,   20,   21,   22,    7,    8,    9,   10,   11,
 /*   170 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   180 */    22,   39,    1,   39,   51,   74,   74,    5,    6,    7,
 /*   190 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   200 */    18,   19,   20,   21,   22,    5,    6,    7,    8,    9,
 /*   210 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   220 */    20,   21,   22,   41,    5,    6,    7,    8,    9,   10,
 /*   230 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   240 */    21,   22,   37,   43,   74,    1,   74,   42,   74,    5,
 /*   250 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   260 */    16,   17,   18,   19,   20,   21,   22,    1,   74,   74,
 /*   270 */    74,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   280 */    14,   15,   16,   17,   18,   19,   20,   21,   22,    6,
 /*   290 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   300 */    17,   18,   19,   20,   21,   22,   53,   74,   74,   74,
 /*   310 */    57,   58,   59,   60,   61,   62,   63,   74,   65,   66,
 /*   320 */    67,   68,   69,   74,   71,   72,   73,    8,    9,   10,
 /*   330 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   340 */    21,   22,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   350 */    17,   18,   19,   20,   21,   22,    0,   11,   12,   13,
 /*   360 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   74,
 /*   370 */    74,   74,   74,   74,   18,   53,    1,   74,   74,   23,
 /*   380 */    24,   74,   74,   27,   62,   74,   64,   74,   74,   33,
 /*   390 */    34,   69,   70,   71,   72,   73,   74,   74,   74,   74,
 /*   400 */    44,   74,   46,   47,   48,   49,   50,   53,   18,   34,
 /*   410 */    35,   36,   74,   23,   24,   74,   62,   27,   64,   74,
 /*   420 */    74,   74,   74,   69,   34,   71,   72,   73,   74,   74,
 /*   430 */    40,   74,   74,   74,   44,   74,   46,   47,   48,   49,
 /*   440 */    50,   74,   74,   18,   74,   74,   74,   74,   23,   24,
 /*   450 */    74,   74,   27,   28,   74,   74,   74,   74,   74,   34,
 /*   460 */    74,   17,   18,   19,   20,   21,   22,    1,   74,   44,
 /*   470 */    74,   46,   47,   48,   49,   50,   74,   74,   18,   53,
 /*   480 */    74,   74,   74,   23,   24,   74,   74,   27,   28,   74,
 /*   490 */    74,   74,   74,   27,   34,   69,   30,   71,   72,   73,
 /*   500 */    34,   35,   36,   74,   44,   74,   46,   47,   48,   49,
 /*   510 */    50,   74,   74,   18,   74,   53,   74,   74,   23,   24,
 /*   520 */    74,   74,   27,   74,   62,   74,   74,   74,   74,   34,
 /*   530 */    74,   69,   53,   71,   72,   73,   74,   53,   74,   44,
 /*   540 */    74,   46,   47,   48,   49,   50,   74,   53,   69,   74,
 /*   550 */    71,   72,   73,   69,   53,   71,   72,   73,   74,   74,
 /*   560 */    53,   74,   74,   69,   74,   71,   72,   73,   74,   53,
 /*   570 */    69,   74,   71,   72,   73,   74,   69,   74,   71,   72,
 /*   580 */    73,   74,   74,   53,   74,   69,   74,   71,   72,   73,
 /*   590 */    74,   53,   74,   74,   74,   74,   53,   74,   74,   69,
 /*   600 */    74,   71,   72,   73,   53,   74,   74,   69,   74,   71,
 /*   610 */    72,   73,   69,   74,   71,   72,   73,   53,   74,   74,
 /*   620 */    69,   74,   71,   72,   73,   74,   53,   74,   74,   74,
 /*   630 */    74,   74,   53,   69,   74,   71,   72,   73,   74,   53,
 /*   640 */    74,   74,   69,   74,   71,   72,   73,   74,   69,   74,
 /*   650 */    71,   72,   73,   53,   74,   69,   74,   71,   72,   73,
 /*   660 */    74,   53,   74,   74,   74,   74,   53,   74,   74,   69,
 /*   670 */    74,   71,   72,   73,   53,   74,   74,   69,   74,   71,
 /*   680 */    72,   73,   69,   74,   71,   72,   73,   53,   74,   74,
 /*   690 */    69,   74,   71,   72,   73,   74,   53,   74,   74,   74,
 /*   700 */    74,   74,   53,   69,   74,   71,   72,   73,   74,   53,
 /*   710 */    74,   74,   69,   74,   71,   72,   73,   74,   69,   74,
 /*   720 */    71,   72,   73,   53,   74,   69,   74,   71,   72,   73,
 /*   730 */    74,   53,   74,   74,   74,   74,   53,   74,   74,   69,
 /*   740 */    74,   71,   72,   73,   53,   74,   74,   69,   74,   71,
 /*   750 */    72,   73,   69,   74,   71,   72,   73,   53,   74,   74,
 /*   760 */    69,   74,   71,   72,   73,   74,   53,   74,   74,   74,
 /*   770 */    74,   74,   53,   69,   74,   71,   72,   73,   74,   53,
 /*   780 */    74,   74,   69,   74,   71,   72,   73,   74,   69,   74,
 /*   790 */    71,   72,   73,   53,   74,   69,   74,   71,   72,   73,
 /*   800 */    74,   53,   74,   74,   74,   74,   53,   74,   74,   69,
 /*   810 */    74,   71,   72,   73,   53,   74,   74,   69,   74,   71,
 /*   820 */    72,   73,   69,   74,   71,   72,   73,   53,   74,   74,
 /*   830 */    69,   74,   71,   72,   73,   74,   53,   74,   74,   74,
 /*   840 */    74,   74,   53,   69,   74,   71,   72,   73,   74,   53,
 /*   850 */    74,   74,   69,   74,   71,   72,   73,   74,   69,   74,
 /*   860 */    71,   72,   73,   53,   74,   69,   74,   71,   72,   73,
 /*   870 */    74,   53,   74,   74,   74,   74,   53,   74,   74,   69,
 /*   880 */    74,   71,   72,   73,   74,   74,   74,   69,   74,   71,
 /*   890 */    72,   73,   69,   74,   71,   72,   73,
};
#define YY_SHIFT_USE_DFLT (-6)
#define YY_SHIFT_COUNT (107)
#define YY_SHIFT_MIN   (-5)
#define YY_SHIFT_MAX   (495)
static const short yy_shift_ofst[] = {
 /*     0 */   133,  356,  495,  460,  425,  495,  390,  495,  495,  495,
 /*    10 */   495,  495,  495,  495,  495,  495,  495,  495,  495,  495,
 /*    20 */   495,  495,  495,  495,  495,  495,  495,  495,  495,  495,
 /*    30 */   495,  495,  495,  495,  495,  495,  495,  495,  495,  495,
 /*    40 */   495,  495,  495,  495,  495,  495,  495,  495,  266,  244,
 /*    50 */   200,  182,  142,  124,  102,   70,   41,   13,   -5,  219,
 /*    60 */   219,  219,  219,  219,  219,  219,  219,  219,  219,  219,
 /*    70 */   283,  158,  319,  333,  346,  346,   78,   78,   78,   78,
 /*    80 */   466,  444,  444,   29,  375,   17,   17,  205,   15,  144,
 /*    90 */   181,  127,  126,   92,   63,   74,   82,   82,   82,   82,
 /*   100 */    82,   82,   82,   75,   71,   37,   11,   10,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (47)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (823)
static const short yy_reduce_ofst[] = {
 /*     0 */    18,  253,  322,  354,  462,  462,  823,  818,  810,  796,
 /*    10 */   789,  783,  774,  761,  753,  748,  740,  726,  719,  713,
 /*    20 */   704,  691,  683,  678,  670,  656,  649,  643,  634,  621,
 /*    30 */   613,  608,  600,  586,  579,  573,  564,  551,  543,  538,
 /*    40 */   530,  516,  507,  501,  494,  484,  479,  426,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   138,  209,  175,  209,  209,  176,  209,  209,  209,  209,
 /*    10 */   209,  209,  209,  209,  209,  209,  209,  209,  209,  209,
 /*    20 */   209,  209,  209,  209,  209,  209,  209,  209,  209,  209,
 /*    30 */   209,  209,  209,  209,  209,  209,  209,  209,  209,  209,
 /*    40 */   209,  209,  209,  209,  209,  209,  209,  209,  209,  209,
 /*    50 */   209,  209,  170,  209,  209,  209,  209,  209,  209,  161,
 /*    60 */   160,  159,  158,  165,  168,  167,  157,  156,  169,  146,
 /*    70 */   198,  197,  205,  204,  192,  191,  196,  195,  194,  193,
 /*    80 */   149,  203,  202,  154,  209,  185,  186,  152,  149,  155,
 /*    90 */   209,  209,  209,  153,  209,  209,  187,  201,  200,  199,
 /*   100 */   190,  189,  188,  209,  209,  209,  209,  209,  208,  207,
 /*   110 */   163,  162,  166,  164,  147,  206,  151,  174,  184,  183,
 /*   120 */   182,  181,  180,  179,  178,  177,  172,  171,  173,  150,
 /*   130 */   145,  144,  143,  142,  141,  140,  139,
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
 /*  69 */ "expr ::= NAME LBRAC expr RBRAC",
 /*  70 */ "in ::= error",
 /*  71 */ "error ::= OPENQUOTEERROR",
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
#line 765 "./src/Grammar/grammar.c"
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
  { 53, 4 },
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
#line 1136 "./src/Grammar/grammar.c"
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
#line 1159 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= assignment */
#line 131 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1166 "./src/Grammar/grammar.c"
        break;
      case 7: /* spec ::= top_stmt */
      case 8: /* top_stmt ::= stmt */ yytestcase(yyruleno==8);
#line 136 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1175 "./src/Grammar/grammar.c"
        break;
      case 9: /* stmt ::= expr */
      case 34: /* stmt_list ::= stmt */ yytestcase(yyruleno==34);
#line 148 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1184 "./src/Grammar/grammar.c"
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
#line 1223 "./src/Grammar/grammar.c"
        break;
      case 11: /* name_chain ::= NAME */
#line 191 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1232 "./src/Grammar/grammar.c"
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
#line 1245 "./src/Grammar/grammar.c"
        break;
      case 13: /* expr ::= NAME LPAREN stmt_list RPAREN */
#line 214 "./src/Grammar/grammar.y"
{
    if(yymsp[-1].minor.yy0.type==optic::STATEMENT_LIST)
    {
/*            yymsp[-1].minor.yy0 = de_tree(yymsp[-1].minor.yy0);*/
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
#line 1278 "./src/Grammar/grammar.c"
        break;
      case 14: /* expr ::= NAME LPAREN RPAREN */
#line 243 "./src/Grammar/grammar.y"
{
    optic::object C;
    C.type = optic::ARRAY;
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
#line 1301 "./src/Grammar/grammar.c"
        break;
      case 15: /* test ::= case_statement */
#line 262 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
/*    panopticon::out() << "Case: " << *yymsp[0].minor.yy0.data.array->at(0).data.string << std::endl;*/
}
#line 1309 "./src/Grammar/grammar.c"
        break;
      case 16: /* spec ::= where_statement */
#line 268 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Where: " << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1317 "./src/Grammar/grammar.c"
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
    panopticon::parse_operations(yygotominor.yy0, b, resolve, &panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1337 "./src/Grammar/grammar.c"
        break;
      case 19: /* guard_statement ::= name_chain GUARD_N expr ASSIGN expr */
#line 313 "./src/Grammar/grammar.y"
{
    optic::object tree = create_condition_tree(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0 = create_guard(yymsp[-4].minor.yy0,tree);
  yy_destructor(yypParser,35,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1347 "./src/Grammar/grammar.c"
        break;
      case 20: /* guard_statement ::= name_chain GUARD_S expr ASSIGN expr */
#line 319 "./src/Grammar/grammar.y"
{
    optic::object tree = create_condition_tree(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0 = create_guard(yymsp[-4].minor.yy0,tree);
  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1357 "./src/Grammar/grammar.c"
        break;
      case 21: /* guard_statement ::= guard_statement GUARD_N expr ASSIGN expr */
#line 325 "./src/Grammar/grammar.y"
{
    add_branch_to_tree(yymsp[-4].minor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0=yymsp[-4].minor.yy0;
  yy_destructor(yypParser,35,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1367 "./src/Grammar/grammar.c"
        break;
      case 22: /* guard_statement ::= guard_statement GUARD_S expr ASSIGN expr */
#line 331 "./src/Grammar/grammar.y"
{
    add_branch_to_tree(yymsp[-4].minor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0=yymsp[-4].minor.yy0;
  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1377 "./src/Grammar/grammar.c"
        break;
      case 23: /* final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr */
#line 337 "./src/Grammar/grammar.y"
{
    add_wildcard_to_tree(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0=yymsp[-3].minor.yy0;
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1387 "./src/Grammar/grammar.c"
        break;
      case 24: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr */
#line 343 "./src/Grammar/grammar.y"
{
    add_wildcard_to_tree(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0=yymsp[-3].minor.yy0;
  yy_destructor(yypParser,38,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1397 "./src/Grammar/grammar.c"
        break;
      case 25: /* where_statement ::= guard_statement WHERE */
      case 26: /* where_statement ::= final_guard_statement WHERE */ yytestcase(yyruleno==26);
#line 348 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1405 "./src/Grammar/grammar.c"
        break;
      case 27: /* where_statement ::= name_chain ASSIGN expr WHERE */
#line 350 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1413 "./src/Grammar/grammar.c"
        break;
      case 28: /* where_statement ::= where_statement NAME ASSIGN expr */
#line 352 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,34,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1421 "./src/Grammar/grammar.c"
        break;
      case 29: /* case_statement ::= name_chain ASSIGN CASE expr OF */
#line 355 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,40,&yymsp[-2].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1432 "./src/Grammar/grammar.c"
        break;
      case 30: /* case_statement ::= case_statement N_TAB expr POINTER expr */
#line 361 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,42,&yymsp[-3].minor);
  yy_destructor(yypParser,43,&yymsp[-1].minor);
}
#line 1442 "./src/Grammar/grammar.c"
        break;
      case 31: /* case_statement ::= case_statement WILDCARD_N POINTER expr */
#line 367 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,43,&yymsp[-1].minor);
}
#line 1452 "./src/Grammar/grammar.c"
        break;
      case 32: /* expr ::= LET NAME ASSIGN expr IN expr */
#line 373 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Let");
  yy_destructor(yypParser,44,&yymsp[-5].minor);
  yy_destructor(yypParser,34,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,45,&yymsp[-1].minor);
}
#line 1464 "./src/Grammar/grammar.c"
        break;
      case 33: /* assignment ::= name_chain ASSIGN expr */
#line 379 "./src/Grammar/grammar.y"
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
#line 1479 "./src/Grammar/grammar.c"
        break;
      case 35: /* stmt_list ::= stmt_list stmt */
#line 401 "./src/Grammar/grammar.y"
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
#line 1498 "./src/Grammar/grammar.c"
        break;
      case 36: /* expr ::= array */
#line 426 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1505 "./src/Grammar/grammar.c"
        break;
      case 37: /* array ::= OPENBRAC maybe_empty_stmt_list RBRAC */
#line 431 "./src/Grammar/grammar.y"
{
    create_tree(yygotominor.yy0,de_tree(yymsp[-1].minor.yy0));
  yy_destructor(yypParser,46,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1514 "./src/Grammar/grammar.c"
        break;
      case 38: /* maybe_empty_stmt_list ::= */
#line 436 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1522 "./src/Grammar/grammar.c"
        break;
      case 39: /* maybe_empty_stmt_list ::= stmt_list */
#line 442 "./src/Grammar/grammar.y"
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
#line 1538 "./src/Grammar/grammar.c"
        break;
      case 40: /* expr ::= num */
      case 42: /* expr ::= bool */ yytestcase(yyruleno==42);
#line 466 "./src/Grammar/grammar.y"
{
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1546 "./src/Grammar/grammar.c"
        break;
      case 41: /* expr ::= string */
#line 471 "./src/Grammar/grammar.y"
{
   create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1553 "./src/Grammar/grammar.c"
        break;
      case 43: /* expr ::= PRINT LPAREN expr RPAREN */
#line 485 "./src/Grammar/grammar.y"
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
#line 1568 "./src/Grammar/grammar.c"
        break;
      case 44: /* expr ::= LPAREN expr RPAREN */
#line 495 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
  yy_destructor(yypParser,27,&yymsp[-2].minor);
  yy_destructor(yypParser,28,&yymsp[0].minor);
}
#line 1577 "./src/Grammar/grammar.c"
        break;
      case 45: /* num ::= NUM */
#line 500 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;*/
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1586 "./src/Grammar/grammar.c"
        break;
      case 46: /* string ::= STRING */
#line 507 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());*/
/*    delete yymsp[0].minor.yy0.data.string;*/
    yymsp[0].minor.yy0.type = panopticon::STRING;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1596 "./src/Grammar/grammar.c"
        break;
      case 47: /* bool ::= BOOLEAN */
#line 516 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;*/
    yymsp[0].minor.yy0.type = panopticon::BOOL;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1605 "./src/Grammar/grammar.c"
        break;
      case 48: /* expr ::= expr PLUS expr */
#line 548 "./src/Grammar/grammar.y"
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
#line 1620 "./src/Grammar/grammar.c"
        break;
      case 49: /* expr ::= expr MINUS expr */
#line 560 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1633 "./src/Grammar/grammar.c"
        break;
      case 50: /* expr ::= expr DIVIDE expr */
#line 570 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1646 "./src/Grammar/grammar.c"
        break;
      case 51: /* expr ::= expr TIMES expr */
#line 580 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1659 "./src/Grammar/grammar.c"
        break;
      case 52: /* expr ::= expr MODULO expr */
#line 590 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1672 "./src/Grammar/grammar.c"
        break;
      case 53: /* expr ::= expr POW expr */
#line 600 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1685 "./src/Grammar/grammar.c"
        break;
      case 54: /* expr ::= expr EQUALTO expr */
#line 610 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1698 "./src/Grammar/grammar.c"
        break;
      case 55: /* expr ::= expr NOTEQUALTO expr */
#line 620 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1711 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr LESSTHAN expr */
#line 630 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1724 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr GREATERTHAN expr */
#line 640 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1737 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= expr LORE expr */
#line 650 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1750 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= expr GORE expr */
#line 660 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1763 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= expr AND expr */
#line 670 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1776 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= expr OR expr */
#line 680 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1789 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= BITNOT expr */
#line 690 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1802 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= MINUS expr */
#line 700 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1815 "./src/Grammar/grammar.c"
        break;
      case 64: /* expr ::= NOT expr */
#line 710 "./src/Grammar/grammar.y"
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
#line 1829 "./src/Grammar/grammar.c"
        break;
      case 65: /* expr ::= expr SHIFTL expr */
#line 721 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1842 "./src/Grammar/grammar.c"
        break;
      case 66: /* expr ::= expr SHIFTR expr */
#line 731 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1855 "./src/Grammar/grammar.c"
        break;
      case 67: /* expr ::= expr BITAND expr */
#line 741 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1868 "./src/Grammar/grammar.c"
        break;
      case 68: /* expr ::= expr BITXOR expr */
#line 761 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1881 "./src/Grammar/grammar.c"
        break;
      case 69: /* expr ::= NAME LBRAC expr RBRAC */
#line 771 "./src/Grammar/grammar.y"
{
    yymsp[-3].minor.yy0.type = optic::STRING;
    optic::store_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,&optic::index);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,30,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1896 "./src/Grammar/grammar.c"
        break;
      case 70: /* in ::= error */
#line 812 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy149)
    {
    case panopticon::OpenQuoteError:
/*        panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        panopticon::out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 1911 "./src/Grammar/grammar.c"
        break;
      case 71: /* error ::= OPENQUOTEERROR */
#line 825 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy149 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1920 "./src/Grammar/grammar.c"
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
#line 1987 "./src/Grammar/grammar.c"
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
#line 2009 "./src/Grammar/grammar.c"
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
