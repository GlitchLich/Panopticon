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
#define YYNSTATE 149
#define YYNRULE 74
#define YYERRORSYMBOL 50
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
#define YY_ACTTAB_COUNT (1067)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    27,   28,   23,   24,   34,   33,   31,   29,   32,   30,
 /*    10 */    26,   25,   44,   41,   39,   37,   36,   35,   26,   25,
 /*    20 */    44,   41,   39,   37,   36,   35,  106,  147,  117,  224,
 /*    30 */     1,  116,  146,    8,  101,   27,   28,   23,   24,   34,
 /*    40 */    33,   31,   29,   32,   30,   26,   25,   44,   41,   39,
 /*    50 */    37,   36,   35,   14,   44,   41,   39,   37,   36,   35,
 /*    60 */    43,  160,    4,  114,   35,   18,  115,  123,   91,   11,
 /*    70 */    27,   28,   23,   24,   34,   33,   31,   29,   32,   30,
 /*    80 */    26,   25,   44,   41,   39,   37,   36,   35,    4,   90,
 /*    90 */    46,   18,  112,  111,    3,  160,  160,   19,  108,   40,
 /*   100 */    17,   88,  128,  123,   12,   27,   28,   23,   24,   34,
 /*   110 */    33,   31,   29,   32,   30,   26,   25,   44,   41,   39,
 /*   120 */    37,   36,   35,   27,   28,   23,   24,   34,   33,   31,
 /*   130 */    29,   32,   30,   26,   25,   44,   41,   39,   37,   36,
 /*   140 */    35,   45,   42,  112,  109,   87,  133,   27,   28,   23,
 /*   150 */    24,   34,   33,   31,   29,   32,   30,   26,   25,   44,
 /*   160 */    41,   39,   37,   36,   35,   10,  107,    9,   82,  112,
 /*   170 */   132,   27,   28,   23,   24,   34,   33,   31,   29,   32,
 /*   180 */    30,   26,   25,   44,   41,   39,   37,   36,   35,   84,
 /*   190 */   225,   39,   37,   36,   35,  105,   83,  126,  225,  123,
 /*   200 */   225,  123,  225,  225,   27,   28,   23,   24,   34,   33,
 /*   210 */    31,   29,   32,   30,   26,   25,   44,   41,   39,   37,
 /*   220 */    36,   35,  225,  225,  225,  225,  225,  225,  225,  225,
 /*   230 */   124,  225,   16,  225,  225,  225,  225,   27,   28,   23,
 /*   240 */    24,   34,   33,   31,   29,   32,   30,   26,   25,   44,
 /*   250 */    41,   39,   37,   36,   35,   27,   28,   23,   24,   34,
 /*   260 */    33,   31,   29,   32,   30,   26,   25,   44,   41,   39,
 /*   270 */    37,   36,   35,  225,  225,  225,  225,  225,  225,  225,
 /*   280 */   225,  225,  225,  122,  225,  225,  225,  225,  225,  225,
 /*   290 */    27,   28,   23,   24,   34,   33,   31,   29,   32,   30,
 /*   300 */    26,   25,   44,   41,   39,   37,   36,   35,   28,   23,
 /*   310 */    24,   34,   33,   31,   29,   32,   30,   26,   25,   44,
 /*   320 */    41,   39,   37,   36,   35,  121,  225,   13,  225,  225,
 /*   330 */   225,  225,   27,   28,   23,   24,   34,   33,   31,   29,
 /*   340 */    32,   30,   26,   25,   44,   41,   39,   37,   36,   35,
 /*   350 */    27,   28,   23,   24,   34,   33,   31,   29,   32,   30,
 /*   360 */    26,   25,   44,   41,   39,   37,   36,   35,   31,   29,
 /*   370 */    32,   30,   26,   25,   44,   41,   39,   37,   36,   35,
 /*   380 */   113,  225,  225,  225,  225,  225,  225,   27,   28,   23,
 /*   390 */    24,   34,   33,   31,   29,   32,   30,   26,   25,   44,
 /*   400 */    41,   39,   37,   36,   35,  225,   64,  225,  225,  225,
 /*   410 */   104,  103,  145,  144,  143,  142,   81,  110,   85,  120,
 /*   420 */   119,  118,   80,   89,   47,  139,  225,  136,  135,  134,
 /*   430 */    27,   28,   23,   24,   34,   33,   31,   29,   32,   30,
 /*   440 */    26,   25,   44,   41,   39,   37,   36,   35,   23,   24,
 /*   450 */    34,   33,   31,   29,   32,   30,   26,   25,   44,   41,
 /*   460 */    39,   37,   36,   35,   24,   34,   33,   31,   29,   32,
 /*   470 */    30,   26,   25,   44,   41,   39,   37,   36,   35,   34,
 /*   480 */    33,   31,   29,   32,   30,   26,   25,   44,   41,   39,
 /*   490 */    37,   36,   35,  149,  225,  225,  225,   21,  225,  225,
 /*   500 */   225,  225,   20,   22,  225,  225,   38,  141,  225,  225,
 /*   510 */   225,  225,   21,   86,  225,  225,  225,   20,   22,  225,
 /*   520 */   102,   38,    2,  100,  131,  130,  129,  148,   77,  225,
 /*   530 */   225,  225,  225,  225,  225,  102,  225,    2,  100,  131,
 /*   540 */   130,  129,  225,  225,  225,  225,  225,   21,  225,  225,
 /*   550 */   225,  225,   20,   22,  225,   21,   38,  225,  225,  225,
 /*   560 */    20,   22,  225,   86,   38,  140,  225,  225,   15,  225,
 /*   570 */   102,   86,    2,  100,  131,  130,  129,  225,  102,  225,
 /*   580 */     2,  100,  131,  130,  129,   21,  225,  225,  225,  225,
 /*   590 */    20,   22,  225,   21,   38,  125,  225,  225,   20,   22,
 /*   600 */   225,   86,   38,  127,  225,  225,  225,  225,  102,   86,
 /*   610 */     2,  100,  131,  130,  129,   64,  102,  225,    2,  100,
 /*   620 */   131,  130,  129,   21,  138,  225,    7,   85,   20,   22,
 /*   630 */   225,  225,   38,  225,  139,   92,  136,  135,  134,   86,
 /*   640 */   225,  225,  225,  225,  225,   64,  102,  225,    2,  100,
 /*   650 */   131,  130,  129,  225,  138,  225,    6,   85,  225,  225,
 /*   660 */    64,  225,  225,  225,  139,   64,  136,  135,  134,  138,
 /*   670 */   225,    5,   85,   78,  137,  225,  225,   85,   61,  139,
 /*   680 */   225,  136,  135,  134,  139,   85,  136,  135,  134,  225,
 /*   690 */    85,   63,  139,  225,  136,  135,  134,  139,  225,  136,
 /*   700 */   135,  134,  225,   85,   79,  225,  225,  225,  225,   60,
 /*   710 */   139,  225,  136,  135,  134,  225,   85,   93,  225,  225,
 /*   720 */   225,   85,  225,  139,  225,  136,  135,  134,  139,   85,
 /*   730 */   136,  135,  134,   59,  225,  225,  139,  225,  136,  135,
 /*   740 */   134,  225,  225,  225,  225,   85,   99,  225,  225,  225,
 /*   750 */   225,   98,  139,  225,  136,  135,  134,  225,   85,  225,
 /*   760 */   225,  225,  225,   85,   97,  139,  225,  136,  135,  134,
 /*   770 */   139,  225,  136,  135,  134,  225,   85,   70,  225,  225,
 /*   780 */   225,  225,   69,  139,  225,  136,  135,  134,  225,   85,
 /*   790 */    74,  225,  225,  225,   85,  225,  139,  225,  136,  135,
 /*   800 */   134,  139,   85,  136,  135,  134,   73,  225,  225,  139,
 /*   810 */   225,  136,  135,  134,  225,  225,  225,  225,   85,   72,
 /*   820 */   225,  225,  225,  225,   71,  139,  225,  136,  135,  134,
 /*   830 */   225,   85,  225,  225,  225,  225,   85,   66,  139,  225,
 /*   840 */   136,  135,  134,  139,  225,  136,  135,  134,  225,   85,
 /*   850 */    65,  225,  225,  225,  225,   76,  139,  225,  136,  135,
 /*   860 */   134,  225,   85,   75,  225,  225,  225,   85,  225,  139,
 /*   870 */   225,  136,  135,  134,  139,   85,  136,  135,  134,   68,
 /*   880 */   225,  225,  139,  225,  136,  135,  134,  225,  225,  225,
 /*   890 */   225,   85,   67,  225,  225,  225,  225,   96,  139,  225,
 /*   900 */   136,  135,  134,  225,   85,  225,  225,  225,  225,   85,
 /*   910 */    95,  139,  225,  136,  135,  134,  139,  225,  136,  135,
 /*   920 */   134,  225,   85,   94,  225,  225,  225,  225,   58,  139,
 /*   930 */   225,  136,  135,  134,  225,   85,   57,  225,  225,  225,
 /*   940 */    85,  225,  139,  225,  136,  135,  134,  139,   85,  136,
 /*   950 */   135,  134,   56,  225,  225,  139,  225,  136,  135,  134,
 /*   960 */   225,  225,  225,  225,   85,   55,  225,  225,  225,  225,
 /*   970 */    54,  139,  225,  136,  135,  134,  225,   85,  225,  225,
 /*   980 */   225,  225,   85,   53,  139,  225,  136,  135,  134,  139,
 /*   990 */   225,  136,  135,  134,  225,   85,   50,  225,  225,  225,
 /*  1000 */   225,   49,  139,  225,  136,  135,  134,  225,   85,   52,
 /*  1010 */   225,  225,  225,   85,  225,  139,  225,  136,  135,  134,
 /*  1020 */   139,   85,  136,  135,  134,   51,  225,  225,  139,  225,
 /*  1030 */   136,  135,  134,  225,  225,  225,  225,   85,   48,  225,
 /*  1040 */   225,  225,  225,   62,  139,  225,  136,  135,  134,  225,
 /*  1050 */    85,  225,  225,  225,  225,   85,  225,  139,  225,  136,
 /*  1060 */   135,  134,  139,  225,  136,  135,  134,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*    10 */    16,   17,   18,   19,   20,   21,   22,   23,   16,   17,
 /*    20 */    18,   19,   20,   21,   22,   23,   50,   34,   34,   53,
 /*    30 */    54,   37,   34,    1,   35,    6,    7,    8,    9,   10,
 /*    40 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    50 */    21,   22,   23,    2,   18,   19,   20,   21,   22,   23,
 /*    60 */     1,    1,   28,   34,   23,   31,   37,   35,   36,    1,
 /*    70 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*    80 */    16,   17,   18,   19,   20,   21,   22,   23,   28,   38,
 /*    90 */    39,   31,   35,   36,   28,   35,   36,   31,   34,   28,
 /*   100 */     2,   37,   32,   35,    1,    6,    7,    8,    9,   10,
 /*   110 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   120 */    21,   22,   23,    6,    7,    8,    9,   10,   11,   12,
 /*   130 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   140 */    23,   39,   43,   35,   36,   34,   29,    6,    7,    8,
 /*   150 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   160 */    19,   20,   21,   22,   23,    1,   37,    1,   61,   35,
 /*   170 */    29,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   180 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   61,
 /*   190 */    75,   20,   21,   22,   23,   49,   61,   32,   75,   35,
 /*   200 */    75,   35,   75,   75,    6,    7,    8,    9,   10,   11,
 /*   210 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   220 */    22,   23,   75,   75,   75,   75,   75,   75,   75,   75,
 /*   230 */    32,   75,    1,   75,   75,   75,   75,    6,    7,    8,
 /*   240 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   250 */    19,   20,   21,   22,   23,    6,    7,    8,    9,   10,
 /*   260 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   270 */    21,   22,   23,   75,   75,   75,   75,   75,   75,   75,
 /*   280 */    75,   75,   75,   34,   75,   75,   75,   75,   75,   75,
 /*   290 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   300 */    16,   17,   18,   19,   20,   21,   22,   23,    7,    8,
 /*   310 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   320 */    19,   20,   21,   22,   23,   41,   75,    1,   75,   75,
 /*   330 */    75,   75,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   340 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   350 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   360 */    16,   17,   18,   19,   20,   21,   22,   23,   12,   13,
 /*   370 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   380 */    36,   75,   75,   75,   75,   75,   75,    6,    7,    8,
 /*   390 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   400 */    19,   20,   21,   22,   23,   75,   51,   75,   75,   75,
 /*   410 */    55,   56,   57,   58,   59,   60,   61,   36,   63,   64,
 /*   420 */    65,   66,   67,   68,   69,   70,   75,   72,   73,   74,
 /*   430 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   440 */    16,   17,   18,   19,   20,   21,   22,   23,    8,    9,
 /*   450 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   460 */    20,   21,   22,   23,    9,   10,   11,   12,   13,   14,
 /*   470 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   10,
 /*   480 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   490 */    21,   22,   23,    0,   75,   75,   75,   19,   75,   75,
 /*   500 */    75,   75,   24,   25,   75,   75,   28,   29,   75,   75,
 /*   510 */    75,   75,   19,   35,   75,   75,   75,   24,   25,   75,
 /*   520 */    42,   28,   44,   45,   46,   47,   48,   34,   35,   75,
 /*   530 */    75,   75,   75,   75,   75,   42,   75,   44,   45,   46,
 /*   540 */    47,   48,   75,   75,   75,   75,   75,   19,   75,   75,
 /*   550 */    75,   75,   24,   25,   75,   19,   28,   75,   75,   75,
 /*   560 */    24,   25,   75,   35,   28,   29,   75,   75,   40,   75,
 /*   570 */    42,   35,   44,   45,   46,   47,   48,   75,   42,   75,
 /*   580 */    44,   45,   46,   47,   48,   19,   75,   75,   75,   75,
 /*   590 */    24,   25,   75,   19,   28,   29,   75,   75,   24,   25,
 /*   600 */    75,   35,   28,   29,   75,   75,   75,   75,   42,   35,
 /*   610 */    44,   45,   46,   47,   48,   51,   42,   75,   44,   45,
 /*   620 */    46,   47,   48,   19,   60,   75,   62,   63,   24,   25,
 /*   630 */    75,   75,   28,   75,   70,   71,   72,   73,   74,   35,
 /*   640 */    75,   75,   75,   75,   75,   51,   42,   75,   44,   45,
 /*   650 */    46,   47,   48,   75,   60,   75,   62,   63,   75,   75,
 /*   660 */    51,   75,   75,   75,   70,   51,   72,   73,   74,   60,
 /*   670 */    75,   62,   63,   51,   60,   75,   75,   63,   51,   70,
 /*   680 */    75,   72,   73,   74,   70,   63,   72,   73,   74,   75,
 /*   690 */    63,   51,   70,   75,   72,   73,   74,   70,   75,   72,
 /*   700 */    73,   74,   75,   63,   51,   75,   75,   75,   75,   51,
 /*   710 */    70,   75,   72,   73,   74,   75,   63,   51,   75,   75,
 /*   720 */    75,   63,   75,   70,   75,   72,   73,   74,   70,   63,
 /*   730 */    72,   73,   74,   51,   75,   75,   70,   75,   72,   73,
 /*   740 */    74,   75,   75,   75,   75,   63,   51,   75,   75,   75,
 /*   750 */    75,   51,   70,   75,   72,   73,   74,   75,   63,   75,
 /*   760 */    75,   75,   75,   63,   51,   70,   75,   72,   73,   74,
 /*   770 */    70,   75,   72,   73,   74,   75,   63,   51,   75,   75,
 /*   780 */    75,   75,   51,   70,   75,   72,   73,   74,   75,   63,
 /*   790 */    51,   75,   75,   75,   63,   75,   70,   75,   72,   73,
 /*   800 */    74,   70,   63,   72,   73,   74,   51,   75,   75,   70,
 /*   810 */    75,   72,   73,   74,   75,   75,   75,   75,   63,   51,
 /*   820 */    75,   75,   75,   75,   51,   70,   75,   72,   73,   74,
 /*   830 */    75,   63,   75,   75,   75,   75,   63,   51,   70,   75,
 /*   840 */    72,   73,   74,   70,   75,   72,   73,   74,   75,   63,
 /*   850 */    51,   75,   75,   75,   75,   51,   70,   75,   72,   73,
 /*   860 */    74,   75,   63,   51,   75,   75,   75,   63,   75,   70,
 /*   870 */    75,   72,   73,   74,   70,   63,   72,   73,   74,   51,
 /*   880 */    75,   75,   70,   75,   72,   73,   74,   75,   75,   75,
 /*   890 */    75,   63,   51,   75,   75,   75,   75,   51,   70,   75,
 /*   900 */    72,   73,   74,   75,   63,   75,   75,   75,   75,   63,
 /*   910 */    51,   70,   75,   72,   73,   74,   70,   75,   72,   73,
 /*   920 */    74,   75,   63,   51,   75,   75,   75,   75,   51,   70,
 /*   930 */    75,   72,   73,   74,   75,   63,   51,   75,   75,   75,
 /*   940 */    63,   75,   70,   75,   72,   73,   74,   70,   63,   72,
 /*   950 */    73,   74,   51,   75,   75,   70,   75,   72,   73,   74,
 /*   960 */    75,   75,   75,   75,   63,   51,   75,   75,   75,   75,
 /*   970 */    51,   70,   75,   72,   73,   74,   75,   63,   75,   75,
 /*   980 */    75,   75,   63,   51,   70,   75,   72,   73,   74,   70,
 /*   990 */    75,   72,   73,   74,   75,   63,   51,   75,   75,   75,
 /*  1000 */    75,   51,   70,   75,   72,   73,   74,   75,   63,   51,
 /*  1010 */    75,   75,   75,   63,   75,   70,   75,   72,   73,   74,
 /*  1020 */    70,   63,   72,   73,   74,   51,   75,   75,   70,   75,
 /*  1030 */    72,   73,   74,   75,   75,   75,   75,   63,   51,   75,
 /*  1040 */    75,   75,   75,   51,   70,   75,   72,   73,   74,   75,
 /*  1050 */    63,   75,   75,   75,   75,   63,   75,   70,   75,   72,
 /*  1060 */    73,   74,   70,   75,   72,   73,   74,
};
#define YY_SHIFT_USE_DFLT (-8)
#define YY_SHIFT_COUNT (104)
#define YY_SHIFT_MIN   (-7)
#define YY_SHIFT_MAX   (604)
static const short yy_shift_ofst[] = {
 /*     0 */   146,  493,  604,  574,  566,  536,  478,  604,  528,  604,
 /*    10 */   604,  604,  604,  604,  604,  604,  604,  604,  604,  604,
 /*    20 */   604,  604,  604,  604,  604,  604,  604,  604,  604,  604,
 /*    30 */   604,  604,  604,  604,  604,  604,  604,  604,  604,  604,
 /*    40 */   604,  604,  604,  604,  604,  108,   57,  134,   64,   29,
 /*    50 */    -6,  381,  344,  326,  284,  249,  231,  198,  165,  141,
 /*    60 */   117,   99,  424,  424,  424,  301,  440,  455,  469,  356,
 /*    70 */   356,    2,    2,    2,    2,   36,   36,   60,  171,  171,
 /*    80 */    51,   32,  166,  164,   68,   66,   34,  129,  111,  102,
 /*    90 */   103,   98,   70,   41,   41,   41,   41,   41,   41,   41,
 /*   100 */    71,   59,   -1,   -2,   -7,
};
#define YY_REDUCE_USE_DFLT (-25)
#define YY_REDUCE_COUNT (47)
#define YY_REDUCE_MIN   (-24)
#define YY_REDUCE_MAX   (992)
static const short yy_reduce_ofst[] = {
 /*     0 */   -24,  355,  564,  609,  594,  614,  614,  614,  992,  987,
 /*    10 */   974,  958,  950,  945,  932,  919,  914,  901,  885,  877,
 /*    20 */   872,  859,  846,  841,  828,  812,  804,  799,  786,  773,
 /*    30 */   768,  755,  739,  731,  726,  713,  700,  695,  682,  666,
 /*    40 */   658,  653,  640,  627,  622,  135,  128,  107,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   150,  223,  187,  223,  223,  223,  223,  188,  223,  223,
 /*    10 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*    20 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*    30 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*    40 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*    50 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*    60 */   223,  223,  182,  181,  158,  210,  209,  217,  216,  204,
 /*    70 */   203,  208,  207,  206,  205,  215,  214,  161,  197,  198,
 /*    80 */   223,  223,  223,  223,  223,  220,  161,  223,  223,  223,
 /*    90 */   223,  223,  223,  199,  213,  212,  211,  202,  201,  200,
 /*   100 */   223,  223,  223,  223,  223,  222,  221,  179,  178,  175,
 /*   110 */   177,  174,  160,  176,  173,  172,  171,  170,  168,  167,
 /*   120 */   166,  180,  169,  159,  218,  164,  219,  165,  186,  196,
 /*   130 */   195,  194,  193,  192,  191,  190,  189,  184,  183,  185,
 /*   140 */   163,  162,  157,  156,  155,  154,  153,  152,  151,
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
    0,  /* FUNCTION_CALL => nothing */
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
   44,  /*      LBRAC => OPENBRAC */
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
  "FUNCTION_CALL",  "INDEX",         "OR",            "AND",         
  "BITXOR",        "BITAND",        "EQUALTO",       "NOTEQUALTO",  
  "GREATERTHAN",   "GORE",          "LESSTHAN",      "LORE",        
  "SHIFTL",        "SHIFTR",        "PLUS",          "MINUS",       
  "DIVIDE",        "TIMES",         "MODULO",        "POW",         
  "NOT",           "BITNOT",        "UMINUS",        "PLUSPLUS",    
  "LPAREN",        "RPAREN",        "COMMA",         "LBRAC",       
  "RBRAC",         "COLLECTARRAY",  "DELIMITER",     "NAME",        
  "LCURL",         "RCURL",         "WILDCARD",      "WHERE",       
  "CASE",          "OF",            "LET",           "IN",          
  "OPENBRAC",      "PRINT",         "NUM",           "STRING",      
  "BOOLEAN",       "OPENQUOTEERROR",  "error",         "expr",        
  "id",            "main",          "in",            "start",       
  "test",          "spec",          "assignment",    "top_stmt",    
  "stmt",          "name_chain",    "stmt_list",     "array_index", 
  "case_statement",  "final_where_statement",  "final_guard_statement",  "guard_statement",
  "where_guard_statement",  "where_statement",  "array",         "maybe_empty_stmt_list",
  "num",           "string",        "bool",        
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "main ::= in",
 /*   1 */ "in ::=",
 /*   2 */ "in ::= in DELIMITER",
 /*   3 */ "in ::= in start DELIMITER",
 /*   4 */ "in ::= in test DELIMITER",
 /*   5 */ "start ::= spec",
 /*   6 */ "spec ::= assignment",
 /*   7 */ "spec ::= top_stmt",
 /*   8 */ "top_stmt ::= stmt",
 /*   9 */ "stmt ::= expr",
 /*  10 */ "name_chain ::= name_chain NAME",
 /*  11 */ "name_chain ::= NAME",
 /*  12 */ "expr ::= NAME",
 /*  13 */ "expr ::= NAME LPAREN stmt_list RPAREN",
 /*  14 */ "expr ::= array_index LPAREN stmt_list RPAREN",
 /*  15 */ "expr ::= NAME LPAREN RPAREN",
 /*  16 */ "expr ::= array_index LPAREN RPAREN",
 /*  17 */ "test ::= case_statement",
 /*  18 */ "spec ::= final_where_statement",
 /*  19 */ "assignment ::= final_guard_statement",
 /*  20 */ "guard_statement ::= name_chain LCURL BITOR expr ASSIGN expr DELIMITER",
 /*  21 */ "guard_statement ::= guard_statement BITOR expr ASSIGN expr DELIMITER",
 /*  22 */ "final_guard_statement ::= guard_statement BITOR expr ASSIGN expr RCURL",
 /*  23 */ "final_guard_statement ::= guard_statement WILDCARD ASSIGN expr RCURL",
 /*  24 */ "where_guard_statement ::= guard_statement WILDCARD ASSIGN expr DELIMITER",
 /*  25 */ "where_statement ::= guard_statement WHERE LCURL",
 /*  26 */ "where_statement ::= where_guard_statement WHERE LCURL",
 /*  27 */ "where_statement ::= guard_statement WHERE name_chain ASSIGN expr LCURL",
 /*  28 */ "where_statement ::= where_guard_statement WHERE name_chain ASSIGN expr LCURL",
 /*  29 */ "where_statement ::= where_statement name_chain ASSIGN expr DELIMITER",
 /*  30 */ "final_where_statement ::= where_statement name_chain ASSIGN expr RCURL DELIMITER RCURL",
 /*  31 */ "case_statement ::= name_chain ASSIGN CASE expr OF",
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
    case 4: /* FUNCTION_CALL */
    case 5: /* INDEX */
    case 6: /* OR */
    case 7: /* AND */
    case 8: /* BITXOR */
    case 9: /* BITAND */
    case 10: /* EQUALTO */
    case 11: /* NOTEQUALTO */
    case 12: /* GREATERTHAN */
    case 13: /* GORE */
    case 14: /* LESSTHAN */
    case 15: /* LORE */
    case 16: /* SHIFTL */
    case 17: /* SHIFTR */
    case 18: /* PLUS */
    case 19: /* MINUS */
    case 20: /* DIVIDE */
    case 21: /* TIMES */
    case 22: /* MODULO */
    case 23: /* POW */
    case 24: /* NOT */
    case 25: /* BITNOT */
    case 26: /* UMINUS */
    case 27: /* PLUSPLUS */
    case 28: /* LPAREN */
    case 29: /* RPAREN */
    case 30: /* COMMA */
    case 31: /* LBRAC */
    case 32: /* RBRAC */
    case 33: /* COLLECTARRAY */
    case 34: /* DELIMITER */
    case 35: /* NAME */
    case 36: /* LCURL */
    case 37: /* RCURL */
    case 38: /* WILDCARD */
    case 39: /* WHERE */
    case 40: /* CASE */
    case 41: /* OF */
    case 42: /* LET */
    case 43: /* IN */
    case 44: /* OPENBRAC */
    case 45: /* PRINT */
    case 46: /* NUM */
    case 47: /* STRING */
    case 48: /* BOOLEAN */
    case 49: /* OPENQUOTEERROR */
{
#line 43 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 801 "./src/Grammar/grammar.c"
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
  { 53, 1 },
  { 54, 0 },
  { 54, 2 },
  { 54, 3 },
  { 54, 3 },
  { 55, 1 },
  { 57, 1 },
  { 57, 1 },
  { 59, 1 },
  { 60, 1 },
  { 61, 2 },
  { 61, 1 },
  { 51, 1 },
  { 51, 4 },
  { 51, 4 },
  { 51, 3 },
  { 51, 3 },
  { 56, 1 },
  { 57, 1 },
  { 58, 1 },
  { 67, 7 },
  { 67, 6 },
  { 66, 6 },
  { 66, 5 },
  { 68, 5 },
  { 69, 3 },
  { 69, 3 },
  { 69, 6 },
  { 69, 6 },
  { 69, 5 },
  { 65, 7 },
  { 64, 5 },
  { 51, 6 },
  { 58, 3 },
  { 62, 1 },
  { 62, 2 },
  { 51, 1 },
  { 70, 3 },
  { 71, 0 },
  { 71, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 4 },
  { 51, 3 },
  { 72, 1 },
  { 73, 1 },
  { 74, 1 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 2 },
  { 51, 2 },
  { 51, 2 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 63, 4 },
  { 63, 4 },
  { 51, 1 },
  { 54, 1 },
  { 50, 1 },
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
      case 2: /* in ::= in DELIMITER */
      case 3: /* in ::= in start DELIMITER */ yytestcase(yyruleno==3);
      case 4: /* in ::= in test DELIMITER */ yytestcase(yyruleno==4);
#line 84 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1174 "./src/Grammar/grammar.c"
        break;
      case 5: /* start ::= spec */
#line 90 "./src/Grammar/grammar.y"
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
#line 1197 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= assignment */
      case 17: /* test ::= case_statement */ yytestcase(yyruleno==17);
#line 132 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1205 "./src/Grammar/grammar.c"
        break;
      case 7: /* spec ::= top_stmt */
      case 8: /* top_stmt ::= stmt */ yytestcase(yyruleno==8);
#line 137 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1214 "./src/Grammar/grammar.c"
        break;
      case 9: /* stmt ::= expr */
      case 34: /* stmt_list ::= stmt */ yytestcase(yyruleno==34);
#line 149 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1223 "./src/Grammar/grammar.c"
        break;
      case 10: /* name_chain ::= name_chain NAME */
#line 155 "./src/Grammar/grammar.y"
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
#line 1262 "./src/Grammar/grammar.c"
        break;
      case 11: /* name_chain ::= NAME */
#line 192 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1271 "./src/Grammar/grammar.c"
        break;
      case 12: /* expr ::= NAME */
#line 199 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1284 "./src/Grammar/grammar.c"
        break;
      case 13: /* expr ::= NAME LPAREN stmt_list RPAREN */
#line 215 "./src/Grammar/grammar.y"
{
    if(yymsp[-1].minor.yy0.type==optic::STATEMENT_LIST)
    {
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
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1316 "./src/Grammar/grammar.c"
        break;
      case 14: /* expr ::= array_index LPAREN stmt_list RPAREN */
#line 243 "./src/Grammar/grammar.y"
{
    if(yymsp[-1].minor.yy0.type==optic::STATEMENT_LIST)
    {
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
    optic::parse_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1342 "./src/Grammar/grammar.c"
        break;
      case 15: /* expr ::= NAME LPAREN RPAREN */
#line 266 "./src/Grammar/grammar.y"
{
    yymsp[-2].minor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,28,&yymsp[-1].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1357 "./src/Grammar/grammar.c"
        break;
      case 16: /* expr ::= array_index LPAREN RPAREN */
#line 277 "./src/Grammar/grammar.y"
{
/*    yymsp[-2].minor.yy0.type = optic::UNDECLARED_VARIABLE;*/
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,28,&yymsp[-1].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1372 "./src/Grammar/grammar.c"
        break;
      case 18: /* spec ::= final_where_statement */
#line 294 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Where: " << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1380 "./src/Grammar/grammar.c"
        break;
      case 19: /* assignment ::= final_guard_statement */
#line 300 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD11" << std::endl;
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
#line 1401 "./src/Grammar/grammar.c"
        break;
      case 20: /* guard_statement ::= name_chain LCURL BITOR expr ASSIGN expr DELIMITER */
#line 320 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD1" << std::endl;
    optic::object tree = create_condition_tree(yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0 = create_guard(yymsp[-6].minor.yy0,tree);
    std::cout << "GUARD2" << std::endl;
  yy_destructor(yypParser,36,&yymsp[-5].minor);
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1415 "./src/Grammar/grammar.c"
        break;
      case 21: /* guard_statement ::= guard_statement BITOR expr ASSIGN expr DELIMITER */
#line 328 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD3" << std::endl;
    add_branch_to_tree(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-5].minor.yy0;
    std::cout << "GUARD4" << std::endl;
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1428 "./src/Grammar/grammar.c"
        break;
      case 22: /* final_guard_statement ::= guard_statement BITOR expr ASSIGN expr RCURL */
#line 336 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD5" << std::endl;
    add_branch_to_tree(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-5].minor.yy0;
    std::cout << "GUARD6" << std::endl;
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,37,&yymsp[0].minor);
}
#line 1441 "./src/Grammar/grammar.c"
        break;
      case 23: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr RCURL */
#line 344 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD7" << std::endl;
    add_wildcard_to_tree(yymsp[-4].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-4].minor.yy0;
    std::cout << "GUARD8" << std::endl;
  yy_destructor(yypParser,38,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,37,&yymsp[0].minor);
}
#line 1454 "./src/Grammar/grammar.c"
        break;
      case 24: /* where_guard_statement ::= guard_statement WILDCARD ASSIGN expr DELIMITER */
#line 352 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD9" << std::endl;
    add_wildcard_to_tree(yymsp[-4].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-4].minor.yy0;
    std::cout << "GUARD10" << std::endl;
  yy_destructor(yypParser,38,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1467 "./src/Grammar/grammar.c"
        break;
      case 25: /* where_statement ::= guard_statement WHERE LCURL */
      case 26: /* where_statement ::= where_guard_statement WHERE LCURL */ yytestcase(yyruleno==26);
#line 364 "./src/Grammar/grammar.y"
{
     std::cout << "WHERE!!!!!!!!!!!!!" << std::endl;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
  yy_destructor(yypParser,39,&yymsp[-1].minor);
  yy_destructor(yypParser,36,&yymsp[0].minor);
}
#line 1478 "./src/Grammar/grammar.c"
        break;
      case 27: /* where_statement ::= guard_statement WHERE name_chain ASSIGN expr LCURL */
      case 28: /* where_statement ::= where_guard_statement WHERE name_chain ASSIGN expr LCURL */ yytestcase(yyruleno==28);
#line 376 "./src/Grammar/grammar.y"
{
     std::cout << "WHERE!!!!!!!!!!!!!" << std::endl;
    yygotominor.yy0 = yymsp[-5].minor.yy0;
  yy_destructor(yypParser,39,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,36,&yymsp[0].minor);
}
#line 1490 "./src/Grammar/grammar.c"
        break;
      case 29: /* where_statement ::= where_statement name_chain ASSIGN expr DELIMITER */
#line 388 "./src/Grammar/grammar.y"
{
     std::cout << "WHERE!!!!!!!!!!!!!" << std::endl;
    yygotominor.yy0 = yymsp[-4].minor.yy0;
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1500 "./src/Grammar/grammar.c"
        break;
      case 30: /* final_where_statement ::= where_statement name_chain ASSIGN expr RCURL DELIMITER RCURL */
#line 394 "./src/Grammar/grammar.y"
{
    std::cout << "WHERE!!!!!!!!!!!!!" << std::endl;
    yygotominor.yy0 = yymsp[-6].minor.yy0;
  yy_destructor(yypParser,1,&yymsp[-4].minor);
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[-1].minor);
  yy_destructor(yypParser,37,&yymsp[0].minor);
}
#line 1512 "./src/Grammar/grammar.c"
        break;
      case 31: /* case_statement ::= name_chain ASSIGN CASE expr OF */
#line 400 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,40,&yymsp[-2].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1523 "./src/Grammar/grammar.c"
        break;
      case 32: /* expr ::= LET NAME ASSIGN expr IN expr */
#line 406 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Let");
  yy_destructor(yypParser,42,&yymsp[-5].minor);
  yy_destructor(yypParser,35,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,43,&yymsp[-1].minor);
}
#line 1535 "./src/Grammar/grammar.c"
        break;
      case 33: /* assignment ::= name_chain ASSIGN expr */
#line 412 "./src/Grammar/grammar.y"
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
#line 1550 "./src/Grammar/grammar.c"
        break;
      case 35: /* stmt_list ::= stmt_list stmt */
#line 434 "./src/Grammar/grammar.y"
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
}
#line 1568 "./src/Grammar/grammar.c"
        break;
      case 36: /* expr ::= array */
      case 71: /* expr ::= array_index */ yytestcase(yyruleno==71);
#line 452 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1576 "./src/Grammar/grammar.c"
        break;
      case 37: /* array ::= OPENBRAC maybe_empty_stmt_list RBRAC */
#line 457 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yygotominor.yy0.type = optic::ARRAY;
  yy_destructor(yypParser,44,&yymsp[-2].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1586 "./src/Grammar/grammar.c"
        break;
      case 38: /* maybe_empty_stmt_list ::= */
#line 463 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1594 "./src/Grammar/grammar.c"
        break;
      case 39: /* maybe_empty_stmt_list ::= stmt_list */
#line 469 "./src/Grammar/grammar.y"
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
#line 1610 "./src/Grammar/grammar.c"
        break;
      case 40: /* expr ::= num */
      case 42: /* expr ::= bool */ yytestcase(yyruleno==42);
#line 487 "./src/Grammar/grammar.y"
{
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1618 "./src/Grammar/grammar.c"
        break;
      case 41: /* expr ::= string */
#line 492 "./src/Grammar/grammar.y"
{
   create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1625 "./src/Grammar/grammar.c"
        break;
      case 43: /* expr ::= PRINT LPAREN expr RPAREN */
#line 506 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-1].minor.yy0,&optic::unary_print_object);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,45,&yymsp[-3].minor);
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1640 "./src/Grammar/grammar.c"
        break;
      case 44: /* expr ::= LPAREN expr RPAREN */
#line 516 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1649 "./src/Grammar/grammar.c"
        break;
      case 45: /* num ::= NUM */
#line 521 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1657 "./src/Grammar/grammar.c"
        break;
      case 46: /* string ::= STRING */
#line 527 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::STRING;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1665 "./src/Grammar/grammar.c"
        break;
      case 47: /* bool ::= BOOLEAN */
#line 534 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::BOOL;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1673 "./src/Grammar/grammar.c"
        break;
      case 48: /* expr ::= expr PLUS expr */
#line 544 "./src/Grammar/grammar.y"
{
    std::cout << "Plus yymsp[-2].minor.yy0: " << yymsp[-2].minor.yy0.type << std::endl;
    std::cout << "Plus yymsp[0].minor.yy0: " << yymsp[0].minor.yy0.type << std::endl;
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::plus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1688 "./src/Grammar/grammar.c"
        break;
      case 49: /* expr ::= expr MINUS expr */
#line 556 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1701 "./src/Grammar/grammar.c"
        break;
      case 50: /* expr ::= expr DIVIDE expr */
#line 566 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1714 "./src/Grammar/grammar.c"
        break;
      case 51: /* expr ::= expr TIMES expr */
#line 576 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1727 "./src/Grammar/grammar.c"
        break;
      case 52: /* expr ::= expr MODULO expr */
#line 586 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1740 "./src/Grammar/grammar.c"
        break;
      case 53: /* expr ::= expr POW expr */
#line 596 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1753 "./src/Grammar/grammar.c"
        break;
      case 54: /* expr ::= expr EQUALTO expr */
#line 606 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1766 "./src/Grammar/grammar.c"
        break;
      case 55: /* expr ::= expr NOTEQUALTO expr */
#line 616 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1779 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr LESSTHAN expr */
#line 626 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1792 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr GREATERTHAN expr */
#line 636 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1805 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= expr LORE expr */
#line 646 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1818 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= expr GORE expr */
#line 656 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1831 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= expr AND expr */
#line 666 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1844 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= expr OR expr */
#line 676 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1857 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= BITNOT expr */
#line 686 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,25,&yymsp[-1].minor);
}
#line 1870 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= MINUS expr */
#line 696 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1883 "./src/Grammar/grammar.c"
        break;
      case 64: /* expr ::= NOT expr */
#line 706 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    not_value(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1897 "./src/Grammar/grammar.c"
        break;
      case 65: /* expr ::= expr SHIFTL expr */
#line 717 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1910 "./src/Grammar/grammar.c"
        break;
      case 66: /* expr ::= expr SHIFTR expr */
#line 727 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1923 "./src/Grammar/grammar.c"
        break;
      case 67: /* expr ::= expr BITAND expr */
#line 737 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1936 "./src/Grammar/grammar.c"
        break;
      case 68: /* expr ::= expr BITXOR expr */
#line 747 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1949 "./src/Grammar/grammar.c"
        break;
      case 69: /* array_index ::= NAME LBRAC expr RBRAC */
#line 757 "./src/Grammar/grammar.y"
{
    yymsp[-3].minor.yy0.type = optic::STRING;
    optic::store_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,31,&yymsp[-2].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1964 "./src/Grammar/grammar.c"
        break;
      case 70: /* array_index ::= array_index LBRAC expr RBRAC */
#line 768 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,31,&yymsp[-2].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1978 "./src/Grammar/grammar.c"
        break;
      case 72: /* in ::= error */
#line 787 "./src/Grammar/grammar.y"
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
#line 1993 "./src/Grammar/grammar.c"
        break;
      case 73: /* error ::= OPENQUOTEERROR */
#line 800 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy151 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 2002 "./src/Grammar/grammar.c"
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
#line 78 "./src/Grammar/grammar.y"

panopticon::out() << "Syntax error!" << std::endl;
#line 2069 "./src/Grammar/grammar.c"
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
#line 73 "./src/Grammar/grammar.y"

printf("parsing complete!\n\n\n");
#line 2091 "./src/Grammar/grammar.c"
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
