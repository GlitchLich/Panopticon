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
#define YYNOCODE 80
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy159;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 167
#define YYNRULE 83
#define YYERRORSYMBOL 53
#define YYERRSYMDT yy159
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
#define YY_ACTTAB_COUNT (1407)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    51,  165,   45,   44,  164,   29,   30,   25,   26,   36,
 /*    10 */    35,   33,   31,   34,   32,   28,   27,   42,   41,   40,
 /*    20 */    39,   38,   37,    4,   47,   11,   43,   42,   41,   40,
 /*    30 */    39,   38,   37,  131,   46,   37,   43,  105,   51,   43,
 /*    40 */    45,   44,  145,   29,   30,   25,   26,   36,   35,   33,
 /*    50 */    31,   34,   32,   28,   27,   42,   41,   40,   39,   38,
 /*    60 */    37,    3,    5,   21,   43,   40,   39,   38,   37,  178,
 /*    70 */    18,   49,   43,  144,   17,  125,   51,   20,   45,   44,
 /*    80 */   134,   29,   30,   25,   26,   36,   35,   33,   31,   34,
 /*    90 */    32,   28,   27,   42,   41,   40,   39,   38,   37,    4,
 /*   100 */   109,   11,   43,  108,  109,   15,  178,  138,  178,   48,
 /*   110 */   111,  138,   21,  124,   51,  107,   45,   44,  106,   29,
 /*   120 */    30,   25,   26,   36,   35,   33,   31,   34,   32,   28,
 /*   130 */    27,   42,   41,   40,   39,   38,   37,  133,  104,  132,
 /*   140 */    43,   51,  151,   45,   44,  103,   29,   30,   25,   26,
 /*   150 */    36,   35,   33,   31,   34,   32,   28,   27,   42,   41,
 /*   160 */    40,   39,   38,   37,  129,   56,  130,   43,   51,  150,
 /*   170 */    45,   44,   13,   29,   30,   25,   26,   36,   35,   33,
 /*   180 */    31,   34,   32,   28,   27,   42,   41,   40,   39,   38,
 /*   190 */    37,  116,  121,   92,   43,   51,  146,   45,   44,   53,
 /*   200 */    29,   30,   25,   26,   36,   35,   33,   31,   34,   32,
 /*   210 */    28,   27,   42,   41,   40,   39,   38,   37,  126,   56,
 /*   220 */   133,   43,  123,   56,   54,  143,   51,  135,   45,   44,
 /*   230 */    93,   29,   30,   25,   26,   36,   35,   33,   31,   34,
 /*   240 */    32,   28,   27,   42,   41,   40,   39,   38,   37,   55,
 /*   250 */   120,  119,   43,  251,    1,  252,  141,   51,  252,   45,
 /*   260 */    44,  252,   29,   30,   25,   26,   36,   35,   33,   31,
 /*   270 */    34,   32,   28,   27,   42,   41,   40,   39,   38,   37,
 /*   280 */   252,  252,  252,   43,  252,   19,  252,  139,   51,  252,
 /*   290 */    45,   44,  252,   29,   30,   25,   26,   36,   35,   33,
 /*   300 */    31,   34,   32,   28,   27,   42,   41,   40,   39,   38,
 /*   310 */    37,   10,  252,   51,   43,   45,   44,  252,   29,   30,
 /*   320 */    25,   26,   36,   35,   33,   31,   34,   32,   28,   27,
 /*   330 */    42,   41,   40,   39,   38,   37,  252,  252,  252,   43,
 /*   340 */   252,  109,  252,  252,  252,  252,  137,  252,  138,  252,
 /*   350 */   110,   51,  252,   45,   44,  252,   29,   30,   25,   26,
 /*   360 */    36,   35,   33,   31,   34,   32,   28,   27,   42,   41,
 /*   370 */    40,   39,   38,   37,  252,  252,  252,   43,   28,   27,
 /*   380 */    42,   41,   40,   39,   38,   37,  252,   50,  252,   43,
 /*   390 */   252,  252,   51,  252,   45,   44,  252,   29,   30,   25,
 /*   400 */    26,   36,   35,   33,   31,   34,   32,   28,   27,   42,
 /*   410 */    41,   40,   39,   38,   37,  252,  252,  252,   43,  252,
 /*   420 */   252,  252,  252,  252,  252,  252,  252,  252,  136,  252,
 /*   430 */   252,  252,  252,   51,  252,   45,   44,  252,   29,   30,
 /*   440 */    25,   26,   36,   35,   33,   31,   34,   32,   28,   27,
 /*   450 */    42,   41,   40,   39,   38,   37,  252,  252,  252,   43,
 /*   460 */    36,   35,   33,   31,   34,   32,   28,   27,   42,   41,
 /*   470 */    40,   39,   38,   37,  128,  252,   14,   43,  252,   51,
 /*   480 */   252,   45,   44,  252,   29,   30,   25,   26,   36,   35,
 /*   490 */    33,   31,   34,   32,   28,   27,   42,   41,   40,   39,
 /*   500 */    38,   37,  252,  252,   51,   43,   45,   44,  252,   29,
 /*   510 */    30,   25,   26,   36,   35,   33,   31,   34,   32,   28,
 /*   520 */    27,   42,   41,   40,   39,   38,   37,  252,   45,   44,
 /*   530 */    43,   29,   30,   25,   26,   36,   35,   33,   31,   34,
 /*   540 */    32,   28,   27,   42,   41,   40,   39,   38,   37,  252,
 /*   550 */   252,  252,   43,   29,   30,   25,   26,   36,   35,   33,
 /*   560 */    31,   34,   32,   28,   27,   42,   41,   40,   39,   38,
 /*   570 */    37,  252,  252,  252,   43,   30,   25,   26,   36,   35,
 /*   580 */    33,   31,   34,   32,   28,   27,   42,   41,   40,   39,
 /*   590 */    38,   37,  252,  252,  252,   43,   25,   26,   36,   35,
 /*   600 */    33,   31,   34,   32,   28,   27,   42,   41,   40,   39,
 /*   610 */    38,   37,   72,  252,  252,   43,  118,  117,  163,  162,
 /*   620 */   161,  160,   52,  115,  252,  100,  127,   91,  122,  252,
 /*   630 */   252,  156,  252,  154,  153,  152,   26,   36,   35,   33,
 /*   640 */    31,   34,   32,   28,   27,   42,   41,   40,   39,   38,
 /*   650 */    37,  167,  252,  252,   43,   33,   31,   34,   32,   28,
 /*   660 */    27,   42,   41,   40,   39,   38,   37,  252,  252,  252,
 /*   670 */    43,  252,  252,  252,  252,  252,  252,  252,   23,   24,
 /*   680 */   252,  252,   12,  252,    2,  252,  252,   22,  166,   88,
 /*   690 */   252,  252,   23,   24,  252,  252,   12,  102,    2,  114,
 /*   700 */   149,  148,  147,  101,  252,  252,  252,  252,  252,  252,
 /*   710 */   252,  252,  252,  114,  149,  148,  147,   23,   24,  252,
 /*   720 */   252,   12,  252,    2,  112,   23,   24,  252,  101,   12,
 /*   730 */   252,    2,  252,  252,  252,  252,  101,  252,  114,  149,
 /*   740 */   148,  147,   16,  252,  252,  252,  114,  149,  148,  147,
 /*   750 */   252,   23,   24,  252,  252,   12,  159,    2,  252,   23,
 /*   760 */    24,  252,  101,   12,  158,    2,  252,  252,  252,  252,
 /*   770 */   101,  252,  114,  149,  148,  147,  252,  252,  252,  252,
 /*   780 */   114,  149,  148,  147,   23,   24,  252,  252,   12,  140,
 /*   790 */     2,  252,   23,   24,  252,  101,   12,  142,    2,  252,
 /*   800 */   252,  252,  252,  101,  252,  114,  149,  148,  147,  252,
 /*   810 */   252,  252,  252,  114,  149,  148,  147,   23,   24,  252,
 /*   820 */   252,   12,  144,    2,  252,  252,  252,  252,  101,  252,
 /*   830 */   252,  252,  252,  252,  252,   72,  252,  252,  114,  149,
 /*   840 */   148,  147,  252,  252,  155,  252,  115,    9,  100,  252,
 /*   850 */   252,  252,  252,  252,  156,  113,  154,  153,  152,  252,
 /*   860 */   252,  252,  252,   23,   24,  252,  252,   12,  252,    2,
 /*   870 */    72,  252,  252,  252,  101,  252,  252,  252,  252,  155,
 /*   880 */   252,  115,    6,  100,  114,  149,  148,  147,  252,  156,
 /*   890 */   252,  154,  153,  152,   72,  252,  252,  252,  252,   72,
 /*   900 */   252,  252,  252,  155,  252,  115,    8,  100,  155,  252,
 /*   910 */   115,    7,  100,  156,  252,  154,  153,  152,  156,   72,
 /*   920 */   154,  153,  152,  252,   66,  252,  252,  252,  157,  252,
 /*   930 */   115,  252,  100,  252,  252,  115,  252,  100,  156,   71,
 /*   940 */   154,  153,  152,  156,   73,  154,  153,  152,  252,  252,
 /*   950 */   115,  252,  100,  252,  252,  115,  252,  100,  156,  252,
 /*   960 */   154,  153,  152,  156,  252,  154,  153,  152,   75,  252,
 /*   970 */   252,  252,  252,   74,  252,  252,  252,  252,  252,  115,
 /*   980 */   252,  100,  252,  252,  115,  252,  100,  156,  252,  154,
 /*   990 */   153,  152,  156,   90,  154,  153,  152,  252,   89,  252,
 /*  1000 */   252,  252,  252,  252,  115,  252,  100,  252,  252,  115,
 /*  1010 */   252,  100,  156,   99,  154,  153,  152,  156,   98,  154,
 /*  1020 */   153,  152,  252,  252,  115,  252,  100,  252,  252,  115,
 /*  1030 */   252,  100,  156,  252,  154,  153,  152,  156,  252,  154,
 /*  1040 */   153,  152,   97,  252,  252,  252,  252,   96,  252,  252,
 /*  1050 */   252,  252,  252,  115,  252,  100,  252,  252,  115,  252,
 /*  1060 */   100,  156,  252,  154,  153,  152,  156,   81,  154,  153,
 /*  1070 */   152,  252,   80,  252,  252,  252,  252,  252,  115,  252,
 /*  1080 */   100,  252,  252,  115,  252,  100,  156,   85,  154,  153,
 /*  1090 */   152,  156,   84,  154,  153,  152,  252,  252,  115,  252,
 /*  1100 */   100,  252,  252,  115,  252,  100,  156,  252,  154,  153,
 /*  1110 */   152,  156,  252,  154,  153,  152,   83,  252,  252,  252,
 /*  1120 */   252,   82,  252,  252,  252,  252,  252,  115,  252,  100,
 /*  1130 */   252,  252,  115,  252,  100,  156,  252,  154,  153,  152,
 /*  1140 */   156,   77,  154,  153,  152,  252,   76,  252,  252,  252,
 /*  1150 */   252,  252,  115,  252,  100,  252,  252,  115,  252,  100,
 /*  1160 */   156,   87,  154,  153,  152,  156,   86,  154,  153,  152,
 /*  1170 */   252,  252,  115,  252,  100,  252,  252,  115,  252,  100,
 /*  1180 */   156,  252,  154,  153,  152,  156,  252,  154,  153,  152,
 /*  1190 */    79,  252,  252,  252,  252,   78,  252,  252,  252,  252,
 /*  1200 */   252,  115,  252,  100,  252,  252,  115,  252,  100,  156,
 /*  1210 */   252,  154,  153,  152,  156,   95,  154,  153,  152,  252,
 /*  1220 */    94,  252,  252,  252,  252,  252,  115,  252,  100,  252,
 /*  1230 */   252,  115,  252,  100,  156,   69,  154,  153,  152,  156,
 /*  1240 */    68,  154,  153,  152,  252,  252,  115,  252,  100,  252,
 /*  1250 */   252,  115,  252,  100,  156,  252,  154,  153,  152,  156,
 /*  1260 */   252,  154,  153,  152,   65,  252,  252,  252,  252,   64,
 /*  1270 */   252,  252,  252,  252,  252,  115,  252,  100,  252,  252,
 /*  1280 */   115,  252,  100,  156,  252,  154,  153,  152,  156,   62,
 /*  1290 */   154,  153,  152,  252,   59,  252,  252,  252,  252,  252,
 /*  1300 */   115,  252,  100,  252,  252,  115,  252,  100,  156,   61,
 /*  1310 */   154,  153,  152,  156,   60,  154,  153,  152,  252,  252,
 /*  1320 */   115,  252,  100,  252,  252,  115,  252,  100,  156,  252,
 /*  1330 */   154,  153,  152,  156,  252,  154,  153,  152,   58,  252,
 /*  1340 */   252,  252,  252,   57,  252,  252,  252,  252,  252,  115,
 /*  1350 */   252,  100,  252,  252,  115,  252,  100,  156,  252,  154,
 /*  1360 */   153,  152,  156,   70,  154,  153,  152,  252,   67,  252,
 /*  1370 */   252,  252,  252,  252,  115,  252,  100,  252,  252,  115,
 /*  1380 */   252,  100,  156,   63,  154,  153,  152,  156,  252,  154,
 /*  1390 */   153,  152,  252,  252,  115,  252,  100,  252,  252,  252,
 /*  1400 */   252,  252,  156,  252,  154,  153,  152,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     4,   37,    6,    7,   37,    9,   10,   11,   12,   13,
 /*    10 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*    20 */    24,   25,   26,   31,   33,   33,   30,   21,   22,   23,
 /*    30 */    24,   25,   26,   37,   31,   26,   30,   41,    4,   30,
 /*    40 */     6,    7,   34,    9,   10,   11,   12,   13,   14,   15,
 /*    50 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*    60 */    26,   31,   31,   33,   30,   23,   24,   25,   26,    1,
 /*    70 */     1,   37,   30,   32,    1,   41,    4,    2,    6,    7,
 /*    80 */    32,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*    90 */    18,   19,   20,   21,   22,   23,   24,   25,   26,   31,
 /*   100 */    31,   33,   30,   38,   31,    2,   38,   38,   40,   37,
 /*   110 */    31,   38,   33,   41,    4,   39,    6,    7,   38,    9,
 /*   120 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   130 */    20,   21,   22,   23,   24,   25,   26,   38,   37,   40,
 /*   140 */    30,    4,   32,    6,    7,   42,    9,   10,   11,   12,
 /*   150 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   160 */    23,   24,   25,   26,   71,   72,   41,   30,    4,   32,
 /*   170 */     6,    7,    1,    9,   10,   11,   12,   13,   14,   15,
 /*   180 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*   190 */    26,   65,   47,   67,   30,    4,   32,    6,    7,   64,
 /*   200 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   210 */    19,   20,   21,   22,   23,   24,   25,   26,   71,   72,
 /*   220 */    38,   30,   71,   72,   64,   34,    4,   78,    6,    7,
 /*   230 */    38,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   240 */    18,   19,   20,   21,   22,   23,   24,   25,   26,   43,
 /*   250 */    53,   52,   30,   56,   57,   79,   34,    4,   79,    6,
 /*   260 */     7,   79,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   270 */    17,   18,   19,   20,   21,   22,   23,   24,   25,   26,
 /*   280 */    79,   79,   79,   30,   79,    1,   79,   34,    4,   79,
 /*   290 */     6,    7,   79,    9,   10,   11,   12,   13,   14,   15,
 /*   300 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*   310 */    26,    1,   79,    4,   30,    6,    7,   79,    9,   10,
 /*   320 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   330 */    21,   22,   23,   24,   25,   26,   79,   79,   79,   30,
 /*   340 */    79,   31,   79,   79,   79,   79,   37,   79,   38,   79,
 /*   350 */    40,    4,   79,    6,    7,   79,    9,   10,   11,   12,
 /*   360 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   370 */    23,   24,   25,   26,   79,   79,   79,   30,   19,   20,
 /*   380 */    21,   22,   23,   24,   25,   26,   79,   40,   79,   30,
 /*   390 */    79,   79,    4,   79,    6,    7,   79,    9,   10,   11,
 /*   400 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   410 */    22,   23,   24,   25,   26,   79,   79,   79,   30,   79,
 /*   420 */    79,   79,   79,   79,   79,   79,   79,   79,   40,   79,
 /*   430 */    79,   79,   79,    4,   79,    6,    7,   79,    9,   10,
 /*   440 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   450 */    21,   22,   23,   24,   25,   26,   79,   79,   79,   30,
 /*   460 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   470 */    23,   24,   25,   26,   45,   79,    1,   30,   79,    4,
 /*   480 */    79,    6,    7,   79,    9,   10,   11,   12,   13,   14,
 /*   490 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*   500 */    25,   26,   79,   79,    4,   30,    6,    7,   79,    9,
 /*   510 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   520 */    20,   21,   22,   23,   24,   25,   26,   79,    6,    7,
 /*   530 */    30,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   540 */    18,   19,   20,   21,   22,   23,   24,   25,   26,   79,
 /*   550 */    79,   79,   30,    9,   10,   11,   12,   13,   14,   15,
 /*   560 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*   570 */    26,   79,   79,   79,   30,   10,   11,   12,   13,   14,
 /*   580 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*   590 */    25,   26,   79,   79,   79,   30,   11,   12,   13,   14,
 /*   600 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*   610 */    25,   26,   54,   79,   79,   30,   58,   59,   60,   61,
 /*   620 */    62,   63,   64,   65,   79,   67,   68,   69,   70,   79,
 /*   630 */    79,   73,   79,   75,   76,   77,   12,   13,   14,   15,
 /*   640 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*   650 */    26,    0,   79,   79,   30,   15,   16,   17,   18,   19,
 /*   660 */    20,   21,   22,   23,   24,   25,   26,   79,   79,   79,
 /*   670 */    30,   79,   79,   79,   79,   79,   79,   79,   27,   28,
 /*   680 */    79,   79,   31,   79,   33,   79,   79,   22,   37,   38,
 /*   690 */    79,   79,   27,   28,   79,   79,   31,   46,   33,   48,
 /*   700 */    49,   50,   51,   38,   79,   79,   79,   79,   79,   79,
 /*   710 */    79,   79,   79,   48,   49,   50,   51,   27,   28,   79,
 /*   720 */    79,   31,   79,   33,   34,   27,   28,   79,   38,   31,
 /*   730 */    79,   33,   79,   79,   79,   79,   38,   79,   48,   49,
 /*   740 */    50,   51,   44,   79,   79,   79,   48,   49,   50,   51,
 /*   750 */    79,   27,   28,   79,   79,   31,   32,   33,   79,   27,
 /*   760 */    28,   79,   38,   31,   32,   33,   79,   79,   79,   79,
 /*   770 */    38,   79,   48,   49,   50,   51,   79,   79,   79,   79,
 /*   780 */    48,   49,   50,   51,   27,   28,   79,   79,   31,   32,
 /*   790 */    33,   79,   27,   28,   79,   38,   31,   32,   33,   79,
 /*   800 */    79,   79,   79,   38,   79,   48,   49,   50,   51,   79,
 /*   810 */    79,   79,   79,   48,   49,   50,   51,   27,   28,   79,
 /*   820 */    79,   31,   32,   33,   79,   79,   79,   79,   38,   79,
 /*   830 */    79,   79,   79,   79,   79,   54,   79,   79,   48,   49,
 /*   840 */    50,   51,   79,   79,   63,   79,   65,   66,   67,   79,
 /*   850 */    79,   79,   79,   79,   73,   74,   75,   76,   77,   79,
 /*   860 */    79,   79,   79,   27,   28,   79,   79,   31,   79,   33,
 /*   870 */    54,   79,   79,   79,   38,   79,   79,   79,   79,   63,
 /*   880 */    79,   65,   66,   67,   48,   49,   50,   51,   79,   73,
 /*   890 */    79,   75,   76,   77,   54,   79,   79,   79,   79,   54,
 /*   900 */    79,   79,   79,   63,   79,   65,   66,   67,   63,   79,
 /*   910 */    65,   66,   67,   73,   79,   75,   76,   77,   73,   54,
 /*   920 */    75,   76,   77,   79,   54,   79,   79,   79,   63,   79,
 /*   930 */    65,   79,   67,   79,   79,   65,   79,   67,   73,   54,
 /*   940 */    75,   76,   77,   73,   54,   75,   76,   77,   79,   79,
 /*   950 */    65,   79,   67,   79,   79,   65,   79,   67,   73,   79,
 /*   960 */    75,   76,   77,   73,   79,   75,   76,   77,   54,   79,
 /*   970 */    79,   79,   79,   54,   79,   79,   79,   79,   79,   65,
 /*   980 */    79,   67,   79,   79,   65,   79,   67,   73,   79,   75,
 /*   990 */    76,   77,   73,   54,   75,   76,   77,   79,   54,   79,
 /*  1000 */    79,   79,   79,   79,   65,   79,   67,   79,   79,   65,
 /*  1010 */    79,   67,   73,   54,   75,   76,   77,   73,   54,   75,
 /*  1020 */    76,   77,   79,   79,   65,   79,   67,   79,   79,   65,
 /*  1030 */    79,   67,   73,   79,   75,   76,   77,   73,   79,   75,
 /*  1040 */    76,   77,   54,   79,   79,   79,   79,   54,   79,   79,
 /*  1050 */    79,   79,   79,   65,   79,   67,   79,   79,   65,   79,
 /*  1060 */    67,   73,   79,   75,   76,   77,   73,   54,   75,   76,
 /*  1070 */    77,   79,   54,   79,   79,   79,   79,   79,   65,   79,
 /*  1080 */    67,   79,   79,   65,   79,   67,   73,   54,   75,   76,
 /*  1090 */    77,   73,   54,   75,   76,   77,   79,   79,   65,   79,
 /*  1100 */    67,   79,   79,   65,   79,   67,   73,   79,   75,   76,
 /*  1110 */    77,   73,   79,   75,   76,   77,   54,   79,   79,   79,
 /*  1120 */    79,   54,   79,   79,   79,   79,   79,   65,   79,   67,
 /*  1130 */    79,   79,   65,   79,   67,   73,   79,   75,   76,   77,
 /*  1140 */    73,   54,   75,   76,   77,   79,   54,   79,   79,   79,
 /*  1150 */    79,   79,   65,   79,   67,   79,   79,   65,   79,   67,
 /*  1160 */    73,   54,   75,   76,   77,   73,   54,   75,   76,   77,
 /*  1170 */    79,   79,   65,   79,   67,   79,   79,   65,   79,   67,
 /*  1180 */    73,   79,   75,   76,   77,   73,   79,   75,   76,   77,
 /*  1190 */    54,   79,   79,   79,   79,   54,   79,   79,   79,   79,
 /*  1200 */    79,   65,   79,   67,   79,   79,   65,   79,   67,   73,
 /*  1210 */    79,   75,   76,   77,   73,   54,   75,   76,   77,   79,
 /*  1220 */    54,   79,   79,   79,   79,   79,   65,   79,   67,   79,
 /*  1230 */    79,   65,   79,   67,   73,   54,   75,   76,   77,   73,
 /*  1240 */    54,   75,   76,   77,   79,   79,   65,   79,   67,   79,
 /*  1250 */    79,   65,   79,   67,   73,   79,   75,   76,   77,   73,
 /*  1260 */    79,   75,   76,   77,   54,   79,   79,   79,   79,   54,
 /*  1270 */    79,   79,   79,   79,   79,   65,   79,   67,   79,   79,
 /*  1280 */    65,   79,   67,   73,   79,   75,   76,   77,   73,   54,
 /*  1290 */    75,   76,   77,   79,   54,   79,   79,   79,   79,   79,
 /*  1300 */    65,   79,   67,   79,   79,   65,   79,   67,   73,   54,
 /*  1310 */    75,   76,   77,   73,   54,   75,   76,   77,   79,   79,
 /*  1320 */    65,   79,   67,   79,   79,   65,   79,   67,   73,   79,
 /*  1330 */    75,   76,   77,   73,   79,   75,   76,   77,   54,   79,
 /*  1340 */    79,   79,   79,   54,   79,   79,   79,   79,   79,   65,
 /*  1350 */    79,   67,   79,   79,   65,   79,   67,   73,   79,   75,
 /*  1360 */    76,   77,   73,   54,   75,   76,   77,   79,   54,   79,
 /*  1370 */    79,   79,   79,   79,   65,   79,   67,   79,   79,   65,
 /*  1380 */    79,   67,   73,   54,   75,   76,   77,   73,   79,   75,
 /*  1390 */    76,   77,   79,   79,   65,   79,   67,   79,   79,   79,
 /*  1400 */    79,   79,   73,   79,   75,   76,   77,
};
#define YY_SHIFT_USE_DFLT (-37)
#define YY_SHIFT_COUNT (118)
#define YY_SHIFT_MIN   (-36)
#define YY_SHIFT_MAX   (836)
static const short yy_shift_ofst[] = {
 /*     0 */   199,  651,  836,  790,  765,  836,  757,  732,  724,  836,
 /*    10 */   698,  690,  665,  836,  836,  836,  836,  836,  836,  836,
 /*    20 */   836,  836,  836,  836,  836,  836,  836,  836,  836,  836,
 /*    30 */   836,  836,  836,  836,  836,  836,  836,  836,  836,  836,
 /*    40 */   836,  836,  836,  836,  836,  836,  836,  836,  206,  206,
 /*    50 */   206,  192,  310,   73,   69,   99,  182,   72,   34,   -4,
 /*    60 */   475,  429,  388,  347,  309,  284,  253,  222,  191,  164,
 /*    70 */   137,  110,  500,  522,  544,  544,  565,  585,  624,  447,
 /*    80 */   640,  640,  359,  359,  359,  359,    6,    6,   68,   42,
 /*    90 */    42,  103,   79,   -8,    9,    9,    9,    9,    9,    9,
 /*   100 */    30,   -8,  145,  171,  125,  101,   48,   80,   76,   65,
 /*   110 */    75,   41,   31,    8,    3,   -9,   -9,  -33,  -36,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (56)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (1329)
static const short yy_reduce_ofst[] = {
 /*     0 */   197,  558,  781,  845,  840,  816,  865,  865,  865,  865,
 /*    10 */  1329, 1314, 1309, 1289, 1284, 1260, 1255, 1240, 1235, 1215,
 /*    20 */  1210, 1186, 1181, 1166, 1161, 1141, 1136, 1112, 1107, 1092,
 /*    30 */  1087, 1067, 1062, 1038, 1033, 1018, 1013,  993,  988,  964,
 /*    40 */   959,  944,  939,  919,  914,  890,  885,  870,  151,  147,
 /*    50 */    93,  126,  149,  149,  149,  160,  135,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   168,  250,  208,  250,  250,  250,  250,  250,  250,  209,
 /*    10 */   250,  250,  250,  250,  250,  250,  250,  250,  250,  250,
 /*    20 */   250,  250,  250,  250,  250,  250,  250,  250,  250,  250,
 /*    30 */   250,  250,  250,  250,  250,  250,  250,  250,  250,  250,
 /*    40 */   250,  250,  250,  250,  250,  250,  250,  250,  250,  190,
 /*    50 */   250,  250,  250,  250,  250,  250,  250,  250,  250,  250,
 /*    60 */   250,  250,  250,  202,  250,  250,  250,  250,  250,  250,
 /*    70 */   250,  250,  176,  220,  222,  221,  236,  235,  243,  242,
 /*    80 */   230,  229,  234,  233,  232,  231,  241,  240,  179,  224,
 /*    90 */   223,  250,  250,  181,  239,  237,  228,  227,  226,  225,
 /*   100 */   247,  179,  250,  250,  250,  250,  250,  250,  250,  250,
 /*   110 */   250,  250,  250,  250,  250,  187,  180,  250,  250,  249,
 /*   120 */   248,  201,  193,  195,  192,  191,  194,  188,  200,  203,
 /*   130 */   199,  198,  196,  178,  219,  218,  197,  189,  177,  244,
 /*   140 */   183,  245,  185,  246,  186,  207,  238,  217,  216,  215,
 /*   150 */   214,  213,  212,  211,  210,  204,  206,  205,  184,  182,
 /*   160 */   175,  174,  173,  172,  171,  170,  169,
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
  "COMPOSITION",   "FUNCTION_CALL",  "PREPEND",       "APPEND",      
  "INDEX",         "OR",            "AND",           "BITXOR",      
  "BITAND",        "EQUALTO",       "NOTEQUALTO",    "GREATERTHAN", 
  "GORE",          "LESSTHAN",      "LORE",          "SHIFTL",      
  "SHIFTR",        "PLUS",          "MINUS",         "DIVIDE",      
  "TIMES",         "MODULO",        "POW",           "NOT",         
  "BITNOT",        "UMINUS",        "PLUSPLUS",      "LPAREN",      
  "RPAREN",        "LBRAC",         "RBRAC",         "COMMA",       
  "COLLECTARRAY",  "DELIMITER",     "NAME",          "COLON",       
  "LCURL",         "RCURL",         "WILDCARD",      "WHERE",       
  "CASE",          "OF",            "LET",           "IN",          
  "PRINT",         "NUM",           "STRING",        "BOOLEAN",     
  "OPENQUOTEERROR",  "error",         "expr",          "id",          
  "main",          "in",            "start",         "test",        
  "spec",          "assignment",    "top_stmt",      "stmt",        
  "name_chain",    "function_call",  "stmt_list",     "array_index", 
  "case_statement",  "guard_statement",  "final_guard_statement",  "final_where_statement",
  "where_statement",  "array",         "maybe_empty_stmt_list",  "num",         
  "string",        "bool",          "pattern_argument",
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
 /*  13 */ "expr ::= expr COMPOSITION function_call",
 /*  14 */ "expr ::= expr COMPOSITION NAME",
 /*  15 */ "function_call ::= NAME LPAREN stmt_list RPAREN",
 /*  16 */ "function_call ::= NAME LBRAC RBRAC LPAREN stmt_list RPAREN",
 /*  17 */ "expr ::= array_index LPAREN stmt_list RPAREN",
 /*  18 */ "function_call ::= NAME LPAREN RPAREN",
 /*  19 */ "function_call ::= array_index LPAREN RPAREN",
 /*  20 */ "expr ::= function_call",
 /*  21 */ "test ::= case_statement",
 /*  22 */ "guard_statement ::= name_chain LCURL BITOR expr ASSIGN expr DELIMITER",
 /*  23 */ "guard_statement ::= guard_statement BITOR expr ASSIGN expr DELIMITER",
 /*  24 */ "final_guard_statement ::= guard_statement BITOR expr ASSIGN expr RCURL",
 /*  25 */ "final_guard_statement ::= guard_statement WILDCARD ASSIGN expr RCURL",
 /*  26 */ "assignment ::= final_guard_statement",
 /*  27 */ "assignment ::= guard_statement BITOR expr ASSIGN expr DELIMITER final_where_statement",
 /*  28 */ "assignment ::= guard_statement WILDCARD ASSIGN expr DELIMITER final_where_statement",
 /*  29 */ "where_statement ::= WHERE LCURL",
 /*  30 */ "where_statement ::= WHERE name_chain ASSIGN expr LCURL",
 /*  31 */ "where_statement ::= where_statement name_chain ASSIGN expr DELIMITER",
 /*  32 */ "final_where_statement ::= where_statement name_chain ASSIGN expr RCURL DELIMITER RCURL",
 /*  33 */ "case_statement ::= name_chain ASSIGN CASE expr OF",
 /*  34 */ "test ::= LET IN",
 /*  35 */ "assignment ::= name_chain ASSIGN expr",
 /*  36 */ "assignment ::= name_chain ASSIGN expr LCURL final_where_statement",
 /*  37 */ "stmt_list ::= stmt",
 /*  38 */ "stmt_list ::= stmt_list stmt",
 /*  39 */ "expr ::= array",
 /*  40 */ "array ::= LBRAC maybe_empty_stmt_list RBRAC",
 /*  41 */ "maybe_empty_stmt_list ::=",
 /*  42 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  43 */ "expr ::= num",
 /*  44 */ "expr ::= string",
 /*  45 */ "expr ::= bool",
 /*  46 */ "expr ::= PRINT LPAREN expr RPAREN",
 /*  47 */ "expr ::= LPAREN expr RPAREN",
 /*  48 */ "num ::= NUM",
 /*  49 */ "string ::= STRING",
 /*  50 */ "bool ::= BOOLEAN",
 /*  51 */ "name_chain ::= name_chain pattern_argument",
 /*  52 */ "pattern_argument ::= LPAREN NAME COLON NAME RPAREN",
 /*  53 */ "expr ::= expr PREPEND expr",
 /*  54 */ "expr ::= expr APPEND expr",
 /*  55 */ "expr ::= expr PLUSPLUS expr",
 /*  56 */ "expr ::= expr PLUS expr",
 /*  57 */ "expr ::= expr MINUS expr",
 /*  58 */ "expr ::= expr DIVIDE expr",
 /*  59 */ "expr ::= expr TIMES expr",
 /*  60 */ "expr ::= expr MODULO expr",
 /*  61 */ "expr ::= expr POW expr",
 /*  62 */ "expr ::= expr EQUALTO expr",
 /*  63 */ "expr ::= expr NOTEQUALTO expr",
 /*  64 */ "expr ::= expr LESSTHAN expr",
 /*  65 */ "expr ::= expr GREATERTHAN expr",
 /*  66 */ "expr ::= expr LORE expr",
 /*  67 */ "expr ::= expr GORE expr",
 /*  68 */ "expr ::= expr AND expr",
 /*  69 */ "expr ::= expr OR expr",
 /*  70 */ "expr ::= BITNOT expr",
 /*  71 */ "expr ::= LPAREN MINUS expr RPAREN",
 /*  72 */ "expr ::= NOT expr",
 /*  73 */ "expr ::= expr SHIFTL expr",
 /*  74 */ "expr ::= expr SHIFTR expr",
 /*  75 */ "expr ::= expr BITAND expr",
 /*  76 */ "expr ::= expr BITXOR expr",
 /*  77 */ "array_index ::= function_call LBRAC expr RBRAC",
 /*  78 */ "array_index ::= NAME LBRAC expr RBRAC",
 /*  79 */ "array_index ::= array_index LBRAC expr RBRAC",
 /*  80 */ "expr ::= array_index",
 /*  81 */ "in ::= error",
 /*  82 */ "error ::= OPENQUOTEERROR",
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
    case 4: /* COMPOSITION */
    case 5: /* FUNCTION_CALL */
    case 6: /* PREPEND */
    case 7: /* APPEND */
    case 8: /* INDEX */
    case 9: /* OR */
    case 10: /* AND */
    case 11: /* BITXOR */
    case 12: /* BITAND */
    case 13: /* EQUALTO */
    case 14: /* NOTEQUALTO */
    case 15: /* GREATERTHAN */
    case 16: /* GORE */
    case 17: /* LESSTHAN */
    case 18: /* LORE */
    case 19: /* SHIFTL */
    case 20: /* SHIFTR */
    case 21: /* PLUS */
    case 22: /* MINUS */
    case 23: /* DIVIDE */
    case 24: /* TIMES */
    case 25: /* MODULO */
    case 26: /* POW */
    case 27: /* NOT */
    case 28: /* BITNOT */
    case 29: /* UMINUS */
    case 30: /* PLUSPLUS */
    case 31: /* LPAREN */
    case 32: /* RPAREN */
    case 33: /* LBRAC */
    case 34: /* RBRAC */
    case 35: /* COMMA */
    case 36: /* COLLECTARRAY */
    case 37: /* DELIMITER */
    case 38: /* NAME */
    case 39: /* COLON */
    case 40: /* LCURL */
    case 41: /* RCURL */
    case 42: /* WILDCARD */
    case 43: /* WHERE */
    case 44: /* CASE */
    case 45: /* OF */
    case 46: /* LET */
    case 47: /* IN */
    case 48: /* PRINT */
    case 49: /* NUM */
    case 50: /* STRING */
    case 51: /* BOOLEAN */
    case 52: /* OPENQUOTEERROR */
{
#line 43 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 853 "./src/Grammar/grammar.c"
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
  { 60, 1 },
  { 62, 1 },
  { 63, 1 },
  { 64, 2 },
  { 64, 1 },
  { 54, 1 },
  { 54, 3 },
  { 54, 3 },
  { 65, 4 },
  { 65, 6 },
  { 54, 4 },
  { 65, 3 },
  { 65, 3 },
  { 54, 1 },
  { 59, 1 },
  { 69, 7 },
  { 69, 6 },
  { 70, 6 },
  { 70, 5 },
  { 61, 1 },
  { 61, 7 },
  { 61, 6 },
  { 72, 2 },
  { 72, 5 },
  { 72, 5 },
  { 71, 7 },
  { 68, 5 },
  { 59, 2 },
  { 61, 3 },
  { 61, 5 },
  { 66, 1 },
  { 66, 2 },
  { 54, 1 },
  { 73, 3 },
  { 74, 0 },
  { 74, 1 },
  { 54, 1 },
  { 54, 1 },
  { 54, 1 },
  { 54, 4 },
  { 54, 3 },
  { 75, 1 },
  { 76, 1 },
  { 77, 1 },
  { 64, 2 },
  { 78, 5 },
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
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 2 },
  { 54, 4 },
  { 54, 2 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 67, 4 },
  { 67, 4 },
  { 67, 4 },
  { 54, 1 },
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
      case 2: /* in ::= in DELIMITER */
      case 3: /* in ::= in start DELIMITER */ yytestcase(yyruleno==3);
      case 4: /* in ::= in test DELIMITER */ yytestcase(yyruleno==4);
#line 87 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,37,&yymsp[0].minor);
}
#line 1235 "./src/Grammar/grammar.c"
        break;
      case 5: /* start ::= spec */
#line 93 "./src/Grammar/grammar.y"
{
    if(
        yymsp[0].minor.yy0.type == optic::NUMBER ||
        yymsp[0].minor.yy0.type == optic::STRING ||
        yymsp[0].minor.yy0.type == optic::BOOL
        )
    {
        print_object(yymsp[0].minor.yy0);
    }
    else
    {
        optic::resolve_stack_from_parser(yymsp[0].minor.yy0, true);
    }
}
#line 1253 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= assignment */
      case 21: /* test ::= case_statement */ yytestcase(yyruleno==21);
#line 109 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1261 "./src/Grammar/grammar.c"
        break;
      case 7: /* spec ::= top_stmt */
      case 8: /* top_stmt ::= stmt */ yytestcase(yyruleno==8);
#line 114 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1270 "./src/Grammar/grammar.c"
        break;
      case 9: /* stmt ::= expr */
      case 37: /* stmt_list ::= stmt */ yytestcase(yyruleno==37);
#line 126 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1279 "./src/Grammar/grammar.c"
        break;
      case 10: /* name_chain ::= name_chain NAME */
#line 132 "./src/Grammar/grammar.y"
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
/*        yygotominor.yy0.data.array->reserve(yymsp[-1].minor.yy0.data.array->size()+1);*/
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
#line 1318 "./src/Grammar/grammar.c"
        break;
      case 11: /* name_chain ::= NAME */
#line 169 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1327 "./src/Grammar/grammar.c"
        break;
      case 12: /* expr ::= NAME */
#line 176 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0.data.string = new optic::String(yymsp[0].minor.yy0.data.string->c_str());
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1340 "./src/Grammar/grammar.c"
        break;
      case 13: /* expr ::= expr COMPOSITION function_call */
#line 192 "./src/Grammar/grammar.y"
{
    if(yymsp[0].minor.yy0.type==optic::OPERATION_TREE)
    {
        yymsp[0].minor.yy0.data.array->at(2).data.array->push_front(yymsp[-2].minor.yy0);
        yygotominor.yy0 = yymsp[0].minor.yy0;
    }
    else
    {
        optic::object function_body;
        function_body.type = optic::FUNCTION_ARG_VALUES;
        function_body.data.array = new optic::Array();
        function_body.data.array->push_back(yymsp[-2].minor.yy0);
        yymsp[0].minor.yy0.type = optic::STRING;
        optic::store_operations(yygotominor.yy0,yymsp[0].minor.yy0,function_body,optic::call_function);
    }
  yy_destructor(yypParser,4,&yymsp[-1].minor);
}
#line 1361 "./src/Grammar/grammar.c"
        break;
      case 14: /* expr ::= expr COMPOSITION NAME */
#line 210 "./src/Grammar/grammar.y"
{
    optic::object function_body;
    function_body.type = optic::FUNCTION_ARG_VALUES;
    function_body.data.array = new optic::Array();
    function_body.data.array->push_back(yymsp[-2].minor.yy0);
    yymsp[0].minor.yy0.type = optic::STRING;
    optic::store_operations(yygotominor.yy0,yymsp[0].minor.yy0,function_body,optic::call_function);
  yy_destructor(yypParser,4,&yymsp[-1].minor);
}
#line 1374 "./src/Grammar/grammar.c"
        break;
      case 15: /* function_call ::= NAME LPAREN stmt_list RPAREN */
#line 220 "./src/Grammar/grammar.y"
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
        yymsp[-1].minor.yy0.data.array->push_back(temp);
    }
    optic::object b;
    b.type = optic::STRING;

    b.data.string = new optic::String(yymsp[-3].minor.yy0.data.string->c_str());
    optic::store_operations(yygotominor.yy0,b,yymsp[-1].minor.yy0,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,31,&yymsp[-2].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1403 "./src/Grammar/grammar.c"
        break;
      case 16: /* function_call ::= NAME LBRAC RBRAC LPAREN stmt_list RPAREN */
#line 245 "./src/Grammar/grammar.y"
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
/*        yymsp[-1].minor.yy0.data.array->reserve(1);*/
        yymsp[-1].minor.yy0.data.array->push_back(temp);
    }

/*    optic::object b;*/
    yymsp[-5].minor.yy0.type = optic::VARIABLE;
/*    b.data.string = new optic::String(yymsp[-5].minor.yy0.data.string->c_str());*/
    optic::parse_operations(yygotominor.yy0,yymsp[-5].minor.yy0,yymsp[-1].minor.yy0,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,33,&yymsp[-4].minor);
  yy_destructor(yypParser,34,&yymsp[-3].minor);
  yy_destructor(yypParser,31,&yymsp[-2].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1435 "./src/Grammar/grammar.c"
        break;
      case 17: /* expr ::= array_index LPAREN stmt_list RPAREN */
#line 271 "./src/Grammar/grammar.y"
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
/*        yymsp[-1].minor.yy0.data.array->reserve(1);*/
        yymsp[-1].minor.yy0.data.array->push_back(temp);
    }
    optic::parse_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,31,&yymsp[-2].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1461 "./src/Grammar/grammar.c"
        break;
      case 18: /* function_call ::= NAME LPAREN RPAREN */
#line 294 "./src/Grammar/grammar.y"
{
    yymsp[-2].minor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,31,&yymsp[-1].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1476 "./src/Grammar/grammar.c"
        break;
      case 19: /* function_call ::= array_index LPAREN RPAREN */
#line 305 "./src/Grammar/grammar.y"
{
/*    yymsp[-2].minor.yy0.type = optic::UNDECLARED_VARIABLE;*/
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,31,&yymsp[-1].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1491 "./src/Grammar/grammar.c"
        break;
      case 20: /* expr ::= function_call */
      case 39: /* expr ::= array */ yytestcase(yyruleno==39);
      case 80: /* expr ::= array_index */ yytestcase(yyruleno==80);
#line 316 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1500 "./src/Grammar/grammar.c"
        break;
      case 22: /* guard_statement ::= name_chain LCURL BITOR expr ASSIGN expr DELIMITER */
#line 328 "./src/Grammar/grammar.y"
{
    optic::object tree = create_condition_tree(yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0 = create_guard(yymsp[-6].minor.yy0,tree);
  yy_destructor(yypParser,40,&yymsp[-5].minor);
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,37,&yymsp[0].minor);
}
#line 1512 "./src/Grammar/grammar.c"
        break;
      case 23: /* guard_statement ::= guard_statement BITOR expr ASSIGN expr DELIMITER */
#line 334 "./src/Grammar/grammar.y"
{
    add_branch_to_tree(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-5].minor.yy0;
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,37,&yymsp[0].minor);
}
#line 1523 "./src/Grammar/grammar.c"
        break;
      case 24: /* final_guard_statement ::= guard_statement BITOR expr ASSIGN expr RCURL */
#line 340 "./src/Grammar/grammar.y"
{
    add_branch_to_tree(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-5].minor.yy0;
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1534 "./src/Grammar/grammar.c"
        break;
      case 25: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr RCURL */
#line 346 "./src/Grammar/grammar.y"
{
    add_wildcard_to_tree(yymsp[-4].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-4].minor.yy0;
  yy_destructor(yypParser,42,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1545 "./src/Grammar/grammar.c"
        break;
      case 26: /* assignment ::= final_guard_statement */
#line 352 "./src/Grammar/grammar.y"
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
#line 1565 "./src/Grammar/grammar.c"
        break;
      case 27: /* assignment ::= guard_statement BITOR expr ASSIGN expr DELIMITER final_where_statement */
#line 370 "./src/Grammar/grammar.y"
{
    add_branch_to_tree(yymsp[-6].minor.yy0,yymsp[-4].minor.yy0,yymsp[-2].minor.yy0);
    panopticon::object& b = yymsp[-6].minor.yy0.data.array->at(0);
    panopticon::object& func_body = yymsp[-6].minor.yy0.data.array->at(1);
    panopticon::object resolve;
    panopticon::store_operations(resolve, func_body, &panopticon::resolve_guard);
    optic::object combined;
    panopticon::store_operations(combined,yymsp[0].minor.yy0,resolve,false);
    insure_ready_for_assignment(b,combined);
    panopticon::parse_operations(yygotominor.yy0, b, combined, &panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,2,&yymsp[-5].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,37,&yymsp[-1].minor);
}
#line 1588 "./src/Grammar/grammar.c"
        break;
      case 28: /* assignment ::= guard_statement WILDCARD ASSIGN expr DELIMITER final_where_statement */
#line 388 "./src/Grammar/grammar.y"
{
    add_wildcard_to_tree(yymsp[-5].minor.yy0,yymsp[-2].minor.yy0);
    panopticon::object& b = yymsp[-5].minor.yy0.data.array->at(0);
    panopticon::object& func_body = yymsp[-5].minor.yy0.data.array->at(1);
    panopticon::object resolve;
    panopticon::store_operations(resolve, func_body, &panopticon::resolve_guard);
    optic::object combined;
    panopticon::store_operations(combined,yymsp[0].minor.yy0,resolve,false);
    insure_ready_for_assignment(b,combined);
    panopticon::parse_operations(yygotominor.yy0, b, combined, &panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,42,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,37,&yymsp[-1].minor);
}
#line 1611 "./src/Grammar/grammar.c"
        break;
      case 29: /* where_statement ::= WHERE LCURL */
#line 410 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::NIL;
  yy_destructor(yypParser,43,&yymsp[-1].minor);
  yy_destructor(yypParser,40,&yymsp[0].minor);
}
#line 1620 "./src/Grammar/grammar.c"
        break;
      case 30: /* where_statement ::= WHERE name_chain ASSIGN expr LCURL */
#line 415 "./src/Grammar/grammar.y"
{
    insure_ready_for_assignment(yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yymsp[-3].minor.yy0.type = optic::FUNCTION_ARG_NAMES;
    panopticon::store_operations(yygotominor.yy0, yymsp[-3].minor.yy0, yymsp[-1].minor.yy0, panopticon::assign_variable,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,43,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,40,&yymsp[0].minor);
}
#line 1637 "./src/Grammar/grammar.c"
        break;
      case 31: /* where_statement ::= where_statement name_chain ASSIGN expr DELIMITER */
#line 427 "./src/Grammar/grammar.y"
{
    insure_ready_for_assignment(yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yymsp[-3].minor.yy0.type = optic::FUNCTION_ARG_NAMES;

    if(yymsp[-4].minor.yy0.type!=optic::NIL)
    {
        optic::object assign;
        panopticon::store_operations(assign, yymsp[-3].minor.yy0, yymsp[-1].minor.yy0, panopticon::assign_variable,false);
        optic::store_operations(yygotominor.yy0,yymsp[-4].minor.yy0,assign);
    }
    else
    {
        panopticon::parse_operations(yygotominor.yy0, yymsp[-3].minor.yy0, yymsp[-1].minor.yy0, panopticon::assign_variable);
    }
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,37,&yymsp[0].minor);
}
#line 1663 "./src/Grammar/grammar.c"
        break;
      case 32: /* final_where_statement ::= where_statement name_chain ASSIGN expr RCURL DELIMITER RCURL */
#line 449 "./src/Grammar/grammar.y"
{
    insure_ready_for_assignment(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0);
    yymsp[-5].minor.yy0.type = optic::FUNCTION_ARG_NAMES;
    if(yymsp[-6].minor.yy0.type!=optic::NIL)
    {
        optic::object assign;
        panopticon::store_operations(assign, yymsp[-5].minor.yy0, yymsp[-3].minor.yy0, panopticon::assign_variable,false);
        optic::store_operations(yygotominor.yy0,yymsp[-6].minor.yy0,assign);
    }
    else
    {
        panopticon::store_operations(yygotominor.yy0, yymsp[-5].minor.yy0, yymsp[-3].minor.yy0, panopticon::assign_variable,false);
    }
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-4].minor);
  yy_destructor(yypParser,41,&yymsp[-2].minor);
  yy_destructor(yypParser,37,&yymsp[-1].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1690 "./src/Grammar/grammar.c"
        break;
      case 33: /* case_statement ::= name_chain ASSIGN CASE expr OF */
#line 470 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,44,&yymsp[-2].minor);
  yy_destructor(yypParser,45,&yymsp[0].minor);
}
#line 1701 "./src/Grammar/grammar.c"
        break;
      case 34: /* test ::= LET IN */
#line 475 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,46,&yymsp[-1].minor);
  yy_destructor(yypParser,47,&yymsp[0].minor);
}
#line 1709 "./src/Grammar/grammar.c"
        break;
      case 35: /* assignment ::= name_chain ASSIGN expr */
#line 484 "./src/Grammar/grammar.y"
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
#line 1724 "./src/Grammar/grammar.c"
        break;
      case 36: /* assignment ::= name_chain ASSIGN expr LCURL final_where_statement */
#line 497 "./src/Grammar/grammar.y"
{
    panopticon::object body;
    panopticon::store_operations(body,yymsp[0].minor.yy0,yymsp[-2].minor.yy0,false);
    insure_ready_for_assignment(yymsp[-4].minor.yy0,body);
    panopticon::parse_operations(yygotominor.yy0, yymsp[-4].minor.yy0, body, panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,40,&yymsp[-1].minor);
}
#line 1741 "./src/Grammar/grammar.c"
        break;
      case 38: /* stmt_list ::= stmt_list stmt */
#line 547 "./src/Grammar/grammar.y"
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
#line 1759 "./src/Grammar/grammar.c"
        break;
      case 40: /* array ::= LBRAC maybe_empty_stmt_list RBRAC */
#line 568 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yygotominor.yy0.type = optic::ARRAY;
  yy_destructor(yypParser,33,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1769 "./src/Grammar/grammar.c"
        break;
      case 41: /* maybe_empty_stmt_list ::= */
#line 574 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1777 "./src/Grammar/grammar.c"
        break;
      case 42: /* maybe_empty_stmt_list ::= stmt_list */
#line 580 "./src/Grammar/grammar.y"
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
#line 1793 "./src/Grammar/grammar.c"
        break;
      case 43: /* expr ::= num */
      case 45: /* expr ::= bool */ yytestcase(yyruleno==45);
#line 598 "./src/Grammar/grammar.y"
{
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1801 "./src/Grammar/grammar.c"
        break;
      case 44: /* expr ::= string */
#line 603 "./src/Grammar/grammar.y"
{
   create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1808 "./src/Grammar/grammar.c"
        break;
      case 46: /* expr ::= PRINT LPAREN expr RPAREN */
#line 617 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-1].minor.yy0,&optic::unary_print_object,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,48,&yymsp[-3].minor);
  yy_destructor(yypParser,31,&yymsp[-2].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1823 "./src/Grammar/grammar.c"
        break;
      case 47: /* expr ::= LPAREN expr RPAREN */
#line 627 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
  yy_destructor(yypParser,31,&yymsp[-2].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1832 "./src/Grammar/grammar.c"
        break;
      case 48: /* num ::= NUM */
#line 632 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1840 "./src/Grammar/grammar.c"
        break;
      case 49: /* string ::= STRING */
#line 638 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::STRING;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1848 "./src/Grammar/grammar.c"
        break;
      case 50: /* bool ::= BOOLEAN */
#line 645 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::BOOL;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1856 "./src/Grammar/grammar.c"
        break;
      case 51: /* name_chain ::= name_chain pattern_argument */
#line 663 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
}
#line 1863 "./src/Grammar/grammar.c"
        break;
      case 52: /* pattern_argument ::= LPAREN NAME COLON NAME RPAREN */
#line 668 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0 = yymsp[-1].minor.yy0;
/*    yygotominor.yy0 = B;*/
  yy_destructor(yypParser,31,&yymsp[-4].minor);
  yy_destructor(yypParser,39,&yymsp[-2].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1875 "./src/Grammar/grammar.c"
        break;
      case 53: /* expr ::= expr PREPEND expr */
#line 680 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&optic::prepend,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1888 "./src/Grammar/grammar.c"
        break;
      case 54: /* expr ::= expr APPEND expr */
#line 690 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&optic::append,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1901 "./src/Grammar/grammar.c"
        break;
      case 55: /* expr ::= expr PLUSPLUS expr */
#line 700 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&optic::concat,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,30,&yymsp[-1].minor);
}
#line 1914 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr PLUS expr */
#line 710 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::plus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1927 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr MINUS expr */
#line 720 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1940 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= expr DIVIDE expr */
#line 730 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1953 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= expr TIMES expr */
#line 740 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1966 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= expr MODULO expr */
#line 750 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,25,&yymsp[-1].minor);
}
#line 1979 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= expr POW expr */
#line 760 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,26,&yymsp[-1].minor);
}
#line 1992 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= expr EQUALTO expr */
#line 770 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 2005 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= expr NOTEQUALTO expr */
#line 780 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 2018 "./src/Grammar/grammar.c"
        break;
      case 64: /* expr ::= expr LESSTHAN expr */
#line 790 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 2031 "./src/Grammar/grammar.c"
        break;
      case 65: /* expr ::= expr GREATERTHAN expr */
#line 800 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 2044 "./src/Grammar/grammar.c"
        break;
      case 66: /* expr ::= expr LORE expr */
#line 810 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 2057 "./src/Grammar/grammar.c"
        break;
      case 67: /* expr ::= expr GORE expr */
#line 820 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 2070 "./src/Grammar/grammar.c"
        break;
      case 68: /* expr ::= expr AND expr */
#line 830 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 2083 "./src/Grammar/grammar.c"
        break;
      case 69: /* expr ::= expr OR expr */
#line 840 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 2096 "./src/Grammar/grammar.c"
        break;
      case 70: /* expr ::= BITNOT expr */
#line 850 "./src/Grammar/grammar.y"
{
    store_operations(yygotominor.yy0,yymsp[0].minor.yy0,&optic::bit_not);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,28,&yymsp[-1].minor);
}
#line 2109 "./src/Grammar/grammar.c"
        break;
      case 71: /* expr ::= LPAREN MINUS expr RPAREN */
#line 860 "./src/Grammar/grammar.y"
{
    store_operations(yygotominor.yy0,yymsp[-1].minor.yy0,&panopticon::u_minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,31,&yymsp[-3].minor);
  yy_destructor(yypParser,22,&yymsp[-2].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 2124 "./src/Grammar/grammar.c"
        break;
      case 72: /* expr ::= NOT expr */
#line 870 "./src/Grammar/grammar.y"
{
    store_operations(yygotominor.yy0,yymsp[0].minor.yy0,&panopticon::not_value);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,27,&yymsp[-1].minor);
}
#line 2137 "./src/Grammar/grammar.c"
        break;
      case 73: /* expr ::= expr SHIFTL expr */
#line 880 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 2150 "./src/Grammar/grammar.c"
        break;
      case 74: /* expr ::= expr SHIFTR expr */
#line 890 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 2163 "./src/Grammar/grammar.c"
        break;
      case 75: /* expr ::= expr BITAND expr */
#line 900 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 2176 "./src/Grammar/grammar.c"
        break;
      case 76: /* expr ::= expr BITXOR expr */
#line 910 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 2189 "./src/Grammar/grammar.c"
        break;
      case 77: /* array_index ::= function_call LBRAC expr RBRAC */
      case 79: /* array_index ::= array_index LBRAC expr RBRAC */ yytestcase(yyruleno==79);
#line 920 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,33,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 2204 "./src/Grammar/grammar.c"
        break;
      case 78: /* array_index ::= NAME LBRAC expr RBRAC */
#line 930 "./src/Grammar/grammar.y"
{
    yymsp[-3].minor.yy0.type = optic::STRING;
    optic::store_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,33,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 2219 "./src/Grammar/grammar.c"
        break;
      case 81: /* in ::= error */
#line 960 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy159)
    {
    case panopticon::OpenQuoteError:
/*        panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        panopticon::out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 2234 "./src/Grammar/grammar.c"
        break;
      case 82: /* error ::= OPENQUOTEERROR */
#line 973 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy159 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 2243 "./src/Grammar/grammar.c"
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
#line 81 "./src/Grammar/grammar.y"

panopticon::out() << "Syntax error!" << std::endl;
#line 2310 "./src/Grammar/grammar.c"
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
#line 76 "./src/Grammar/grammar.y"

printf("parsing complete!\n\n\n");
#line 2332 "./src/Grammar/grammar.c"
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
