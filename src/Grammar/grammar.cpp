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
#define YYNSTATE 137
#define YYNRULE 73
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
#define YY_ACTTAB_COUNT (1130)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    30,   31,   26,   27,   37,   36,   34,   32,   35,   33,
 /*    10 */    29,   28,   47,   44,   42,   40,   39,   38,   30,   31,
 /*    20 */    26,   27,   37,   36,   34,   32,   35,   33,   29,   28,
 /*    30 */    47,   44,   42,   40,   39,   38,  135,    4,  134,   45,
 /*    40 */    21,  121,   30,   31,   26,   27,   37,   36,   34,   32,
 /*    50 */    35,   33,   29,   28,   47,   44,   42,   40,   39,   38,
 /*    60 */    14,   12,   89,   88,  108,  120,   30,   31,   26,   27,
 /*    70 */    37,   36,   34,   32,   35,   33,   29,   28,   47,   44,
 /*    80 */    42,   40,   39,   38,   29,   28,   47,   44,   42,   40,
 /*    90 */    39,   38,  114,   47,   44,   42,   40,   39,   38,   30,
 /*   100 */    31,   26,   27,   37,   36,   34,   32,   35,   33,   29,
 /*   110 */    28,   47,   44,   42,   40,   39,   38,   42,   40,   39,
 /*   120 */    38,  101,   46,   43,   38,  112,  106,   19,    3,  211,
 /*   130 */     1,   22,   30,   31,   26,   27,   37,   36,   34,   32,
 /*   140 */    35,   33,   29,   28,   47,   44,   42,   40,   39,   38,
 /*   150 */    17,  116,   90,   15,   10,   30,   31,   26,   27,   37,
 /*   160 */    36,   34,   32,   35,   33,   29,   28,   47,   44,   42,
 /*   170 */    40,   39,   38,   30,   31,   26,   27,   37,   36,   34,
 /*   180 */    32,   35,   33,   29,   28,   47,   44,   42,   40,   39,
 /*   190 */    38,   30,   31,   26,   27,   37,   36,   34,   32,   35,
 /*   200 */    33,   29,   28,   47,   44,   42,   40,   39,   38,  110,
 /*   210 */     9,   13,  107,  105,  212,  212,   30,   31,   26,   27,
 /*   220 */    37,   36,   34,   32,   35,   33,   29,   28,   47,   44,
 /*   230 */    42,   40,   39,   38,   11,  212,  212,  212,  212,   30,
 /*   240 */    31,   26,   27,   37,   36,   34,   32,   35,   33,   29,
 /*   250 */    28,   47,   44,   42,   40,   39,   38,   31,   26,   27,
 /*   260 */    37,   36,   34,   32,   35,   33,   29,   28,   47,   44,
 /*   270 */    42,   40,   39,   38,   67,  212,  212,  212,  104,  103,
 /*   280 */   133,  132,  131,  130,   82,  212,   85,   91,  109,   81,
 /*   290 */    87,  127,  212,  124,  123,  122,   26,   27,   37,   36,
 /*   300 */    34,   32,   35,   33,   29,   28,   47,   44,   42,   40,
 /*   310 */    39,   38,   27,   37,   36,   34,   32,   35,   33,   29,
 /*   320 */    28,   47,   44,   42,   40,   39,   38,   37,   36,   34,
 /*   330 */    32,   35,   33,   29,   28,   47,   44,   42,   40,   39,
 /*   340 */    38,  137,   34,   32,   35,   33,   29,   28,   47,   44,
 /*   350 */    42,   40,   39,   38,  212,  212,  212,  212,  212,  212,
 /*   360 */    24,   67,    8,  212,  212,   23,   25,  212,  212,   41,
 /*   370 */   126,  212,    7,   85,  212,  136,   78,  212,  127,   92,
 /*   380 */   124,  123,  122,  212,  212,  102,  212,    2,  100,  119,
 /*   390 */   118,  117,  212,   67,  212,   24,  111,   20,   18,  212,
 /*   400 */    23,   25,  125,  212,   41,   85,  212,  212,  212,  212,
 /*   410 */   127,   86,  124,  123,  122,  212,  212,   16,  212,  212,
 /*   420 */   102,  212,    2,  100,  119,  118,  117,  212,  212,  212,
 /*   430 */   212,   24,  212,   67,  212,  212,   23,   25,  212,  212,
 /*   440 */    41,  129,  126,  212,    6,   85,  212,   86,  212,  212,
 /*   450 */   127,  212,  124,  123,  122,  148,  102,  212,    2,  100,
 /*   460 */   119,  118,  117,  212,  212,  212,  212,   24,  212,  212,
 /*   470 */   212,  212,   23,   25,  212,  212,   41,  128,  212,  212,
 /*   480 */   212,  212,    4,   86,  212,   21,  212,  212,  212,  148,
 /*   490 */   148,  148,  102,  212,    2,  100,  119,  118,  117,  212,
 /*   500 */   212,  212,  212,   24,  212,  212,   67,  212,   23,   25,
 /*   510 */   212,  212,   41,  113,  212,  126,  212,    5,   85,   86,
 /*   520 */   212,  212,  212,  127,  212,  124,  123,  122,  102,  212,
 /*   530 */     2,  100,  119,  118,  117,  212,  212,  212,  212,   24,
 /*   540 */   212,  212,  212,  212,   23,   25,  212,  212,   41,  115,
 /*   550 */   212,  212,  212,  212,  212,   86,  212,  212,  212,  212,
 /*   560 */   212,  212,  212,  212,  102,  212,    2,  100,  119,  118,
 /*   570 */   117,  212,  212,  212,  212,   24,  212,   83,  212,  212,
 /*   580 */    23,   25,  212,  212,   41,  212,  212,  212,  212,   85,
 /*   590 */   212,   86,  212,  212,  127,  212,  124,  123,  122,   57,
 /*   600 */   102,  212,    2,  100,  119,  118,  117,  212,  212,  212,
 /*   610 */   212,   85,  212,  212,  212,  212,  127,  212,  124,  123,
 /*   620 */   122,   66,  212,  212,  212,  212,  212,  212,  212,  212,
 /*   630 */   212,   84,  212,   85,  212,  212,  212,  212,  127,  212,
 /*   640 */   124,  123,  122,   85,  212,   56,  212,  212,  127,  212,
 /*   650 */   124,  123,  122,  212,  212,  212,   93,   85,  212,  212,
 /*   660 */   212,  212,  127,  212,  124,  123,  122,  212,   85,  212,
 /*   670 */    55,  212,  212,  127,  212,  124,  123,  122,  212,  212,
 /*   680 */   212,  212,   85,  212,  212,   99,  212,  127,  212,  124,
 /*   690 */   123,  122,  212,  212,  212,   98,  212,   85,  212,  212,
 /*   700 */   212,  212,  127,  212,  124,  123,  122,   85,  212,  212,
 /*   710 */    97,  212,  127,  212,  124,  123,  122,  212,  212,  212,
 /*   720 */    73,  212,   85,  212,  212,  212,  212,  127,  212,  124,
 /*   730 */   123,  122,   85,  212,  212,  212,   72,  127,  212,  124,
 /*   740 */   123,  122,  212,  212,  212,  212,  212,  212,   85,   77,
 /*   750 */   212,  212,  212,  127,  212,  124,  123,  122,  212,   76,
 /*   760 */   212,   85,  212,  212,  212,  212,  127,  212,  124,  123,
 /*   770 */   122,   85,  212,  212,   75,  212,  127,  212,  124,  123,
 /*   780 */   122,  212,  212,  212,   74,  212,   85,  212,  212,  212,
 /*   790 */    69,  127,  212,  124,  123,  122,   85,  212,  212,  212,
 /*   800 */   212,  127,   85,  124,  123,  122,  212,  127,  212,  124,
 /*   810 */   123,  122,  212,   68,  212,  212,  212,  212,  212,  212,
 /*   820 */   212,  212,  212,   80,  212,   85,  212,  212,  212,  212,
 /*   830 */   127,  212,  124,  123,  122,   85,  212,  212,   79,  212,
 /*   840 */   127,  212,  124,  123,  122,  212,  212,  212,   71,  212,
 /*   850 */    85,  212,  212,  212,  212,  127,  212,  124,  123,  122,
 /*   860 */    85,   70,  212,  212,  212,  127,  212,  124,  123,  122,
 /*   870 */   212,  212,  212,   85,  212,  212,  212,   96,  127,  212,
 /*   880 */   124,  123,  122,  212,  212,  212,  212,   95,  212,   85,
 /*   890 */   212,  212,  212,  212,  127,  212,  124,  123,  122,   85,
 /*   900 */   212,  212,   94,  212,  127,  212,  124,  123,  122,  212,
 /*   910 */   212,  212,   54,  212,   85,  212,  212,  212,  212,  127,
 /*   920 */   212,  124,  123,  122,   85,  212,  212,   53,  212,  127,
 /*   930 */   212,  124,  123,  122,  212,  212,  212,  212,  212,   85,
 /*   940 */   212,   52,  212,  212,  127,  212,  124,  123,  122,  212,
 /*   950 */   212,   65,  212,   85,  212,  212,  212,  212,  127,  212,
 /*   960 */   124,  123,  122,   85,  212,  212,   51,  212,  127,  212,
 /*   970 */   124,  123,  122,  212,  212,  212,   64,  212,   85,  212,
 /*   980 */   212,  212,  212,  127,  212,  124,  123,  122,   85,  212,
 /*   990 */   212,  212,  212,  127,  212,  124,  123,  122,   50,  212,
 /*  1000 */   212,  212,  212,  212,  212,  212,  212,  212,  212,  212,
 /*  1010 */    85,  212,   62,  212,  212,  127,  212,  124,  123,  122,
 /*  1020 */   212,  212,   49,  212,   85,  212,  212,  212,  212,  127,
 /*  1030 */   212,  124,  123,  122,   85,  212,  212,   61,  212,  127,
 /*  1040 */   212,  124,  123,  122,  212,  212,  212,   48,  212,   85,
 /*  1050 */   212,  212,  212,  212,  127,  212,  124,  123,  122,   85,
 /*  1060 */   212,  212,  212,  212,  127,  212,  124,  123,  122,   60,
 /*  1070 */   212,  212,  212,  212,  212,  212,  212,  212,  212,  212,
 /*  1080 */   212,   85,  212,   59,  212,  212,  127,  212,  124,  123,
 /*  1090 */   122,  212,  212,   58,  212,   85,  212,  212,  212,  212,
 /*  1100 */   127,  212,  124,  123,  122,   85,  212,  212,   63,  212,
 /*  1110 */   127,  212,  124,  123,  122,  212,  212,  212,  212,  212,
 /*  1120 */    85,  212,  212,  212,  212,  127,  212,  124,  123,  122,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*    10 */    16,   17,   18,   19,   20,   21,   22,   23,    6,    7,
 /*    20 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*    30 */    18,   19,   20,   21,   22,   23,   34,   28,   34,   45,
 /*    40 */    31,   29,    6,    7,    8,    9,   10,   11,   12,   13,
 /*    50 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*    60 */    36,   37,   38,   39,   40,   29,    6,    7,    8,    9,
 /*    70 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*    80 */    20,   21,   22,   23,   16,   17,   18,   19,   20,   21,
 /*    90 */    22,   23,   32,   18,   19,   20,   21,   22,   23,    6,
 /*   100 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   110 */    17,   18,   19,   20,   21,   22,   23,   20,   21,   22,
 /*   120 */    23,   35,    1,   28,   23,   32,   52,    1,   28,   55,
 /*   130 */    56,   31,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   140 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   150 */     1,   32,   38,   43,    1,    6,    7,    8,    9,   10,
 /*   160 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   170 */    21,   22,   23,    6,    7,    8,    9,   10,   11,   12,
 /*   180 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   190 */    23,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   200 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   42,
 /*   210 */     1,    1,   40,   51,   75,   75,    6,    7,    8,    9,
 /*   220 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   230 */    20,   21,   22,   23,    1,   75,   75,   75,   75,    6,
 /*   240 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   250 */    17,   18,   19,   20,   21,   22,   23,    7,    8,    9,
 /*   260 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   270 */    20,   21,   22,   23,   53,   75,   75,   75,   57,   58,
 /*   280 */    59,   60,   61,   62,   63,   75,   65,   66,   67,   68,
 /*   290 */    69,   70,   75,   72,   73,   74,    8,    9,   10,   11,
 /*   300 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   310 */    22,   23,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   320 */    17,   18,   19,   20,   21,   22,   23,   10,   11,   12,
 /*   330 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   340 */    23,    0,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   350 */    20,   21,   22,   23,   75,   75,   75,   75,   75,   75,
 /*   360 */    19,   53,    1,   75,   75,   24,   25,   75,   75,   28,
 /*   370 */    62,   75,   64,   65,   75,   34,   35,   75,   70,   71,
 /*   380 */    72,   73,   74,   75,   75,   44,   75,   46,   47,   48,
 /*   390 */    49,   50,   75,   53,   75,   19,   35,   36,   37,   75,
 /*   400 */    24,   25,   62,   75,   28,   65,   75,   75,   75,   75,
 /*   410 */    70,   35,   72,   73,   74,   75,   75,   41,   75,   75,
 /*   420 */    44,   75,   46,   47,   48,   49,   50,   75,   75,   75,
 /*   430 */    75,   19,   75,   53,   75,   75,   24,   25,   75,   75,
 /*   440 */    28,   29,   62,   75,   64,   65,   75,   35,   75,   75,
 /*   450 */    70,   75,   72,   73,   74,    1,   44,   75,   46,   47,
 /*   460 */    48,   49,   50,   75,   75,   75,   75,   19,   75,   75,
 /*   470 */    75,   75,   24,   25,   75,   75,   28,   29,   75,   75,
 /*   480 */    75,   75,   28,   35,   75,   31,   75,   75,   75,   35,
 /*   490 */    36,   37,   44,   75,   46,   47,   48,   49,   50,   75,
 /*   500 */    75,   75,   75,   19,   75,   75,   53,   75,   24,   25,
 /*   510 */    75,   75,   28,   29,   75,   62,   75,   64,   65,   35,
 /*   520 */    75,   75,   75,   70,   75,   72,   73,   74,   44,   75,
 /*   530 */    46,   47,   48,   49,   50,   75,   75,   75,   75,   19,
 /*   540 */    75,   75,   75,   75,   24,   25,   75,   75,   28,   29,
 /*   550 */    75,   75,   75,   75,   75,   35,   75,   75,   75,   75,
 /*   560 */    75,   75,   75,   75,   44,   75,   46,   47,   48,   49,
 /*   570 */    50,   75,   75,   75,   75,   19,   75,   53,   75,   75,
 /*   580 */    24,   25,   75,   75,   28,   75,   75,   75,   75,   65,
 /*   590 */    75,   35,   75,   75,   70,   75,   72,   73,   74,   53,
 /*   600 */    44,   75,   46,   47,   48,   49,   50,   75,   75,   75,
 /*   610 */    75,   65,   75,   75,   75,   75,   70,   75,   72,   73,
 /*   620 */    74,   53,   75,   75,   75,   75,   75,   75,   75,   75,
 /*   630 */    75,   53,   75,   65,   75,   75,   75,   75,   70,   75,
 /*   640 */    72,   73,   74,   65,   75,   53,   75,   75,   70,   75,
 /*   650 */    72,   73,   74,   75,   75,   75,   53,   65,   75,   75,
 /*   660 */    75,   75,   70,   75,   72,   73,   74,   75,   65,   75,
 /*   670 */    53,   75,   75,   70,   75,   72,   73,   74,   75,   75,
 /*   680 */    75,   75,   65,   75,   75,   53,   75,   70,   75,   72,
 /*   690 */    73,   74,   75,   75,   75,   53,   75,   65,   75,   75,
 /*   700 */    75,   75,   70,   75,   72,   73,   74,   65,   75,   75,
 /*   710 */    53,   75,   70,   75,   72,   73,   74,   75,   75,   75,
 /*   720 */    53,   75,   65,   75,   75,   75,   75,   70,   75,   72,
 /*   730 */    73,   74,   65,   75,   75,   75,   53,   70,   75,   72,
 /*   740 */    73,   74,   75,   75,   75,   75,   75,   75,   65,   53,
 /*   750 */    75,   75,   75,   70,   75,   72,   73,   74,   75,   53,
 /*   760 */    75,   65,   75,   75,   75,   75,   70,   75,   72,   73,
 /*   770 */    74,   65,   75,   75,   53,   75,   70,   75,   72,   73,
 /*   780 */    74,   75,   75,   75,   53,   75,   65,   75,   75,   75,
 /*   790 */    53,   70,   75,   72,   73,   74,   65,   75,   75,   75,
 /*   800 */    75,   70,   65,   72,   73,   74,   75,   70,   75,   72,
 /*   810 */    73,   74,   75,   53,   75,   75,   75,   75,   75,   75,
 /*   820 */    75,   75,   75,   53,   75,   65,   75,   75,   75,   75,
 /*   830 */    70,   75,   72,   73,   74,   65,   75,   75,   53,   75,
 /*   840 */    70,   75,   72,   73,   74,   75,   75,   75,   53,   75,
 /*   850 */    65,   75,   75,   75,   75,   70,   75,   72,   73,   74,
 /*   860 */    65,   53,   75,   75,   75,   70,   75,   72,   73,   74,
 /*   870 */    75,   75,   75,   65,   75,   75,   75,   53,   70,   75,
 /*   880 */    72,   73,   74,   75,   75,   75,   75,   53,   75,   65,
 /*   890 */    75,   75,   75,   75,   70,   75,   72,   73,   74,   65,
 /*   900 */    75,   75,   53,   75,   70,   75,   72,   73,   74,   75,
 /*   910 */    75,   75,   53,   75,   65,   75,   75,   75,   75,   70,
 /*   920 */    75,   72,   73,   74,   65,   75,   75,   53,   75,   70,
 /*   930 */    75,   72,   73,   74,   75,   75,   75,   75,   75,   65,
 /*   940 */    75,   53,   75,   75,   70,   75,   72,   73,   74,   75,
 /*   950 */    75,   53,   75,   65,   75,   75,   75,   75,   70,   75,
 /*   960 */    72,   73,   74,   65,   75,   75,   53,   75,   70,   75,
 /*   970 */    72,   73,   74,   75,   75,   75,   53,   75,   65,   75,
 /*   980 */    75,   75,   75,   70,   75,   72,   73,   74,   65,   75,
 /*   990 */    75,   75,   75,   70,   75,   72,   73,   74,   53,   75,
 /*  1000 */    75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
 /*  1010 */    65,   75,   53,   75,   75,   70,   75,   72,   73,   74,
 /*  1020 */    75,   75,   53,   75,   65,   75,   75,   75,   75,   70,
 /*  1030 */    75,   72,   73,   74,   65,   75,   75,   53,   75,   70,
 /*  1040 */    75,   72,   73,   74,   75,   75,   75,   53,   75,   65,
 /*  1050 */    75,   75,   75,   75,   70,   75,   72,   73,   74,   65,
 /*  1060 */    75,   75,   75,   75,   70,   75,   72,   73,   74,   53,
 /*  1070 */    75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
 /*  1080 */    75,   65,   75,   53,   75,   75,   70,   75,   72,   73,
 /*  1090 */    74,   75,   75,   53,   75,   65,   75,   75,   75,   75,
 /*  1100 */    70,   75,   72,   73,   74,   65,   75,   75,   53,   75,
 /*  1110 */    70,   75,   72,   73,   74,   75,   75,   75,   75,   75,
 /*  1120 */    65,   75,   75,   75,   75,   70,   75,   72,   73,   74,
};
#define YY_SHIFT_USE_DFLT (-7)
#define YY_SHIFT_COUNT (104)
#define YY_SHIFT_MIN   (-6)
#define YY_SHIFT_MAX   (556)
static const short yy_shift_ofst[] = {
 /*     0 */   162,  341,  556,  520,  484,  448,  412,  556,  376,  556,
 /*    10 */   556,  556,  556,  556,  556,  556,  556,  556,  556,  556,
 /*    20 */   556,  556,  556,  556,  556,  556,  556,  556,  556,  556,
 /*    30 */   556,  556,  556,  556,  556,  556,  556,  556,  556,  556,
 /*    40 */   556,  556,  556,  556,  556,  556,  556,  556,  233,  210,
 /*    50 */   167,  149,  126,   93,   60,   36,   12,   -6,  185,  185,
 /*    60 */   185,  185,  185,  185,  185,  185,  185,  185,  250,  288,
 /*    70 */   303,  317,  330,  330,   68,   68,   68,   68,  454,   75,
 /*    80 */    75,   24,  361,   97,   97,  100,    9,  172,  209,  153,
 /*    90 */   110,  114,  119,  101,  101,  101,  101,  101,  101,  101,
 /*   100 */    95,  121,   86,    4,    2,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (47)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (1055)
static const short yy_reduce_ofst[] = {
 /*     0 */    74,  221,  308,  453,  380,  340,  340,  340, 1055, 1040,
 /*    10 */  1030, 1016,  994,  984,  969,  959,  945,  923,  913,  898,
 /*    20 */   888,  874,  859,  849,  834,  824,  808,  795,  785,  770,
 /*    30 */   760,  737,  731,  721,  706,  696,  683,  667,  657,  642,
 /*    40 */   632,  617,  603,  592,  578,  568,  546,  524,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   138,  210,  174,  210,  210,  210,  210,  175,  210,  210,
 /*    10 */   210,  210,  210,  210,  210,  210,  210,  210,  210,  210,
 /*    20 */   210,  210,  210,  210,  210,  210,  210,  210,  210,  210,
 /*    30 */   210,  210,  210,  210,  210,  210,  210,  210,  210,  210,
 /*    40 */   210,  210,  210,  210,  210,  210,  210,  210,  210,  210,
 /*    50 */   210,  210,  210,  210,  210,  210,  210,  210,  163,  162,
 /*    60 */   161,  160,  167,  169,  159,  158,  168,  146,  197,  196,
 /*    70 */   204,  203,  191,  190,  195,  194,  193,  192,  149,  202,
 /*    80 */   201,  156,  210,  184,  185,  207,  149,  157,  210,  210,
 /*    90 */   210,  154,  210,  186,  200,  199,  198,  189,  188,  187,
 /*   100 */   210,  210,  210,  210,  210,  209,  208,  165,  164,  155,
 /*   110 */   166,  147,  205,  152,  206,  153,  173,  183,  182,  181,
 /*   120 */   180,  179,  178,  177,  176,  171,  170,  172,  151,  150,
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
  "FUNCTION_CALL",  "INDEX",         "OR",            "AND",         
  "BITXOR",        "BITAND",        "EQUALTO",       "NOTEQUALTO",  
  "GREATERTHAN",   "GORE",          "LESSTHAN",      "LORE",        
  "SHIFTL",        "SHIFTR",        "PLUS",          "MINUS",       
  "DIVIDE",        "TIMES",         "MODULO",        "POW",         
  "NOT",           "BITNOT",        "UMINUS",        "PLUSPLUS",    
  "LPAREN",        "RPAREN",        "COMMA",         "LBRAC",       
  "RBRAC",         "COLLECTARRAY",  "NEWLINE",       "NAME",        
  "GUARD_N",       "GUARD_S",       "WILDCARD_N",    "WILDCARD",    
  "WHERE",         "CASE",          "OF",            "POINTER",     
  "LET",           "IN",            "OPENBRAC",      "PRINT",       
  "NUM",           "STRING",        "BOOLEAN",       "OPENQUOTEERROR",
  "error",         "expr",          "id",            "main",        
  "in",            "start",         "test",          "spec",        
  "assignment",    "top_stmt",      "stmt",          "name_chain",  
  "stmt_list",     "array_index",   "case_statement",  "where_statement",
  "guard_statement",  "final_guard_statement",  "array",         "maybe_empty_stmt_list",
  "num",           "string",        "bool",        
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
 /*  14 */ "expr ::= array_index LPAREN stmt_list RPAREN",
 /*  15 */ "expr ::= NAME LPAREN RPAREN",
 /*  16 */ "expr ::= array_index LPAREN RPAREN",
 /*  17 */ "test ::= case_statement",
 /*  18 */ "spec ::= where_statement",
 /*  19 */ "assignment ::= guard_statement",
 /*  20 */ "assignment ::= final_guard_statement",
 /*  21 */ "guard_statement ::= name_chain GUARD_N expr ASSIGN expr",
 /*  22 */ "guard_statement ::= name_chain GUARD_S expr ASSIGN expr",
 /*  23 */ "guard_statement ::= guard_statement GUARD_N expr ASSIGN expr",
 /*  24 */ "guard_statement ::= guard_statement GUARD_S expr ASSIGN expr",
 /*  25 */ "final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr",
 /*  26 */ "final_guard_statement ::= guard_statement WILDCARD ASSIGN expr",
 /*  27 */ "where_statement ::= guard_statement WHERE",
 /*  28 */ "where_statement ::= final_guard_statement WHERE",
 /*  29 */ "case_statement ::= name_chain ASSIGN CASE expr OF",
 /*  30 */ "case_statement ::= case_statement WILDCARD_N POINTER expr",
 /*  31 */ "expr ::= LET NAME ASSIGN expr IN expr",
 /*  32 */ "assignment ::= name_chain ASSIGN expr",
 /*  33 */ "stmt_list ::= stmt",
 /*  34 */ "stmt_list ::= stmt_list stmt",
 /*  35 */ "expr ::= array",
 /*  36 */ "array ::= OPENBRAC maybe_empty_stmt_list RBRAC",
 /*  37 */ "maybe_empty_stmt_list ::=",
 /*  38 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  39 */ "expr ::= num",
 /*  40 */ "expr ::= string",
 /*  41 */ "expr ::= bool",
 /*  42 */ "expr ::= PRINT LPAREN expr RPAREN",
 /*  43 */ "expr ::= LPAREN expr RPAREN",
 /*  44 */ "num ::= NUM",
 /*  45 */ "string ::= STRING",
 /*  46 */ "bool ::= BOOLEAN",
 /*  47 */ "expr ::= expr PLUS expr",
 /*  48 */ "expr ::= expr MINUS expr",
 /*  49 */ "expr ::= expr DIVIDE expr",
 /*  50 */ "expr ::= expr TIMES expr",
 /*  51 */ "expr ::= expr MODULO expr",
 /*  52 */ "expr ::= expr POW expr",
 /*  53 */ "expr ::= expr EQUALTO expr",
 /*  54 */ "expr ::= expr NOTEQUALTO expr",
 /*  55 */ "expr ::= expr LESSTHAN expr",
 /*  56 */ "expr ::= expr GREATERTHAN expr",
 /*  57 */ "expr ::= expr LORE expr",
 /*  58 */ "expr ::= expr GORE expr",
 /*  59 */ "expr ::= expr AND expr",
 /*  60 */ "expr ::= expr OR expr",
 /*  61 */ "expr ::= BITNOT expr",
 /*  62 */ "expr ::= MINUS expr",
 /*  63 */ "expr ::= NOT expr",
 /*  64 */ "expr ::= expr SHIFTL expr",
 /*  65 */ "expr ::= expr SHIFTR expr",
 /*  66 */ "expr ::= expr BITAND expr",
 /*  67 */ "expr ::= expr BITXOR expr",
 /*  68 */ "array_index ::= NAME LBRAC expr RBRAC",
 /*  69 */ "array_index ::= array_index LBRAC expr RBRAC",
 /*  70 */ "expr ::= array_index",
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
    case 34: /* NEWLINE */
    case 35: /* NAME */
    case 36: /* GUARD_N */
    case 37: /* GUARD_S */
    case 38: /* WILDCARD_N */
    case 39: /* WILDCARD */
    case 40: /* WHERE */
    case 41: /* CASE */
    case 42: /* OF */
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
#line 813 "./src/Grammar/grammar.c"
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
  { 53, 4 },
  { 53, 3 },
  { 53, 3 },
  { 58, 1 },
  { 59, 1 },
  { 60, 1 },
  { 60, 1 },
  { 68, 5 },
  { 68, 5 },
  { 68, 5 },
  { 68, 5 },
  { 69, 4 },
  { 69, 4 },
  { 67, 2 },
  { 67, 2 },
  { 66, 5 },
  { 66, 4 },
  { 53, 6 },
  { 60, 3 },
  { 64, 1 },
  { 64, 2 },
  { 53, 1 },
  { 70, 3 },
  { 71, 0 },
  { 71, 1 },
  { 53, 1 },
  { 53, 1 },
  { 53, 1 },
  { 53, 4 },
  { 53, 3 },
  { 72, 1 },
  { 73, 1 },
  { 74, 1 },
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
  { 65, 4 },
  { 65, 4 },
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
#line 84 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1185 "./src/Grammar/grammar.c"
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
#line 1208 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= assignment */
      case 17: /* test ::= case_statement */ yytestcase(yyruleno==17);
#line 132 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1216 "./src/Grammar/grammar.c"
        break;
      case 7: /* spec ::= top_stmt */
      case 8: /* top_stmt ::= stmt */ yytestcase(yyruleno==8);
#line 137 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1225 "./src/Grammar/grammar.c"
        break;
      case 9: /* stmt ::= expr */
      case 33: /* stmt_list ::= stmt */ yytestcase(yyruleno==33);
#line 149 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1234 "./src/Grammar/grammar.c"
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
#line 1273 "./src/Grammar/grammar.c"
        break;
      case 11: /* name_chain ::= NAME */
#line 192 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1282 "./src/Grammar/grammar.c"
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
#line 1295 "./src/Grammar/grammar.c"
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
#line 1327 "./src/Grammar/grammar.c"
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
#line 1353 "./src/Grammar/grammar.c"
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
#line 1368 "./src/Grammar/grammar.c"
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
#line 1383 "./src/Grammar/grammar.c"
        break;
      case 18: /* spec ::= where_statement */
#line 294 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Where: " << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1391 "./src/Grammar/grammar.c"
        break;
      case 19: /* assignment ::= guard_statement */
      case 20: /* assignment ::= final_guard_statement */ yytestcase(yyruleno==20);
#line 300 "./src/Grammar/grammar.y"
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
#line 1412 "./src/Grammar/grammar.c"
        break;
      case 21: /* guard_statement ::= name_chain GUARD_N expr ASSIGN expr */
#line 341 "./src/Grammar/grammar.y"
{
    optic::object tree = create_condition_tree(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0 = create_guard(yymsp[-4].minor.yy0,tree);
  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1422 "./src/Grammar/grammar.c"
        break;
      case 22: /* guard_statement ::= name_chain GUARD_S expr ASSIGN expr */
#line 347 "./src/Grammar/grammar.y"
{
    optic::object tree = create_condition_tree(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0 = create_guard(yymsp[-4].minor.yy0,tree);
  yy_destructor(yypParser,37,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1432 "./src/Grammar/grammar.c"
        break;
      case 23: /* guard_statement ::= guard_statement GUARD_N expr ASSIGN expr */
#line 353 "./src/Grammar/grammar.y"
{
    add_branch_to_tree(yymsp[-4].minor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0=yymsp[-4].minor.yy0;
  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1442 "./src/Grammar/grammar.c"
        break;
      case 24: /* guard_statement ::= guard_statement GUARD_S expr ASSIGN expr */
#line 359 "./src/Grammar/grammar.y"
{
    add_branch_to_tree(yymsp[-4].minor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0=yymsp[-4].minor.yy0;
  yy_destructor(yypParser,37,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1452 "./src/Grammar/grammar.c"
        break;
      case 25: /* final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr */
#line 365 "./src/Grammar/grammar.y"
{
    add_wildcard_to_tree(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0=yymsp[-3].minor.yy0;
  yy_destructor(yypParser,38,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1462 "./src/Grammar/grammar.c"
        break;
      case 26: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr */
#line 371 "./src/Grammar/grammar.y"
{
    add_wildcard_to_tree(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0=yymsp[-3].minor.yy0;
  yy_destructor(yypParser,39,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1472 "./src/Grammar/grammar.c"
        break;
      case 27: /* where_statement ::= guard_statement WHERE */
      case 28: /* where_statement ::= final_guard_statement WHERE */ yytestcase(yyruleno==28);
#line 377 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
  yy_destructor(yypParser,40,&yymsp[0].minor);
}
#line 1481 "./src/Grammar/grammar.c"
        break;
      case 29: /* case_statement ::= name_chain ASSIGN CASE expr OF */
#line 394 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,41,&yymsp[-2].minor);
  yy_destructor(yypParser,42,&yymsp[0].minor);
}
#line 1492 "./src/Grammar/grammar.c"
        break;
      case 30: /* case_statement ::= case_statement WILDCARD_N POINTER expr */
#line 406 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,38,&yymsp[-2].minor);
  yy_destructor(yypParser,43,&yymsp[-1].minor);
}
#line 1502 "./src/Grammar/grammar.c"
        break;
      case 31: /* expr ::= LET NAME ASSIGN expr IN expr */
#line 412 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Let");
  yy_destructor(yypParser,44,&yymsp[-5].minor);
  yy_destructor(yypParser,35,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,45,&yymsp[-1].minor);
}
#line 1514 "./src/Grammar/grammar.c"
        break;
      case 32: /* assignment ::= name_chain ASSIGN expr */
#line 418 "./src/Grammar/grammar.y"
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
#line 1529 "./src/Grammar/grammar.c"
        break;
      case 34: /* stmt_list ::= stmt_list stmt */
#line 440 "./src/Grammar/grammar.y"
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
#line 1548 "./src/Grammar/grammar.c"
        break;
      case 35: /* expr ::= array */
      case 70: /* expr ::= array_index */ yytestcase(yyruleno==70);
#line 465 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1556 "./src/Grammar/grammar.c"
        break;
      case 36: /* array ::= OPENBRAC maybe_empty_stmt_list RBRAC */
#line 470 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yygotominor.yy0.type = optic::ARRAY;
/*    create_tree(yygotominor.yy0,de_tree(yymsp[-1].minor.yy0));*/
  yy_destructor(yypParser,46,&yymsp[-2].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1567 "./src/Grammar/grammar.c"
        break;
      case 37: /* maybe_empty_stmt_list ::= */
#line 477 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1575 "./src/Grammar/grammar.c"
        break;
      case 38: /* maybe_empty_stmt_list ::= stmt_list */
#line 483 "./src/Grammar/grammar.y"
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
#line 1591 "./src/Grammar/grammar.c"
        break;
      case 39: /* expr ::= num */
      case 41: /* expr ::= bool */ yytestcase(yyruleno==41);
#line 507 "./src/Grammar/grammar.y"
{
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1599 "./src/Grammar/grammar.c"
        break;
      case 40: /* expr ::= string */
#line 512 "./src/Grammar/grammar.y"
{
   create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1606 "./src/Grammar/grammar.c"
        break;
      case 42: /* expr ::= PRINT LPAREN expr RPAREN */
#line 526 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-1].minor.yy0,&optic::unary_print_object);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,47,&yymsp[-3].minor);
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1621 "./src/Grammar/grammar.c"
        break;
      case 43: /* expr ::= LPAREN expr RPAREN */
#line 536 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1630 "./src/Grammar/grammar.c"
        break;
      case 44: /* num ::= NUM */
#line 541 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;*/
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1639 "./src/Grammar/grammar.c"
        break;
      case 45: /* string ::= STRING */
#line 548 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());*/
/*    delete yymsp[0].minor.yy0.data.string;*/
    yymsp[0].minor.yy0.type = panopticon::STRING;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1649 "./src/Grammar/grammar.c"
        break;
      case 46: /* bool ::= BOOLEAN */
#line 557 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;*/
    yymsp[0].minor.yy0.type = panopticon::BOOL;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1658 "./src/Grammar/grammar.c"
        break;
      case 47: /* expr ::= expr PLUS expr */
#line 589 "./src/Grammar/grammar.y"
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
#line 1673 "./src/Grammar/grammar.c"
        break;
      case 48: /* expr ::= expr MINUS expr */
#line 601 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1686 "./src/Grammar/grammar.c"
        break;
      case 49: /* expr ::= expr DIVIDE expr */
#line 611 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1699 "./src/Grammar/grammar.c"
        break;
      case 50: /* expr ::= expr TIMES expr */
#line 621 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1712 "./src/Grammar/grammar.c"
        break;
      case 51: /* expr ::= expr MODULO expr */
#line 631 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1725 "./src/Grammar/grammar.c"
        break;
      case 52: /* expr ::= expr POW expr */
#line 641 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1738 "./src/Grammar/grammar.c"
        break;
      case 53: /* expr ::= expr EQUALTO expr */
#line 651 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1751 "./src/Grammar/grammar.c"
        break;
      case 54: /* expr ::= expr NOTEQUALTO expr */
#line 661 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1764 "./src/Grammar/grammar.c"
        break;
      case 55: /* expr ::= expr LESSTHAN expr */
#line 671 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1777 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr GREATERTHAN expr */
#line 681 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1790 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr LORE expr */
#line 691 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1803 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= expr GORE expr */
#line 701 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1816 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= expr AND expr */
#line 711 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1829 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= expr OR expr */
#line 721 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1842 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= BITNOT expr */
#line 731 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,25,&yymsp[-1].minor);
}
#line 1855 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= MINUS expr */
#line 741 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1868 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= NOT expr */
#line 751 "./src/Grammar/grammar.y"
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
#line 1882 "./src/Grammar/grammar.c"
        break;
      case 64: /* expr ::= expr SHIFTL expr */
#line 762 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1895 "./src/Grammar/grammar.c"
        break;
      case 65: /* expr ::= expr SHIFTR expr */
#line 772 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1908 "./src/Grammar/grammar.c"
        break;
      case 66: /* expr ::= expr BITAND expr */
#line 782 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1921 "./src/Grammar/grammar.c"
        break;
      case 67: /* expr ::= expr BITXOR expr */
#line 802 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1934 "./src/Grammar/grammar.c"
        break;
      case 68: /* array_index ::= NAME LBRAC expr RBRAC */
#line 812 "./src/Grammar/grammar.y"
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
#line 1949 "./src/Grammar/grammar.c"
        break;
      case 69: /* array_index ::= array_index LBRAC expr RBRAC */
#line 823 "./src/Grammar/grammar.y"
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
#line 1963 "./src/Grammar/grammar.c"
        break;
      case 71: /* in ::= error */
#line 867 "./src/Grammar/grammar.y"
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
#line 1978 "./src/Grammar/grammar.c"
        break;
      case 72: /* error ::= OPENQUOTEERROR */
#line 880 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy151 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1987 "./src/Grammar/grammar.c"
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
#line 2054 "./src/Grammar/grammar.c"
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
#line 2076 "./src/Grammar/grammar.c"
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
