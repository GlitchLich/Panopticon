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
#define YYNSTATE 162
#define YYNRULE 81
#define YYERRORSYMBOL 52
#define YYERRSYMDT yy157
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
#define YY_ACTTAB_COUNT (1275)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    47,   44,  160,   29,   30,   25,   26,   36,   35,   33,
 /*    10 */    31,   34,   32,   28,   27,   42,   41,   40,   39,   38,
 /*    20 */    37,    4,  159,   11,   43,   42,   41,   40,   39,   38,
 /*    30 */    37,  125,   37,   46,   43,  102,   43,   47,   44,   45,
 /*    40 */    29,   30,   25,   26,   36,   35,   33,   31,   34,   32,
 /*    50 */    28,   27,   42,   41,   40,   39,   38,   37,    3,  140,
 /*    60 */    21,   43,   20,   40,   39,   38,   37,   17,   49,   15,
 /*    70 */    43,  105,  120,    5,   47,   44,  104,   29,   30,   25,
 /*    80 */    26,   36,   35,   33,   31,   34,   32,   28,   27,   42,
 /*    90 */    41,   40,   39,   38,   37,  103,  106,  115,   43,  101,
 /*   100 */   244,    1,  127,  133,  126,   48,  123,   55,  100,  119,
 /*   110 */   128,   47,   44,  124,   29,   30,   25,   26,   36,   35,
 /*   120 */    33,   31,   34,   32,   28,   27,   42,   41,   40,   39,
 /*   130 */    38,   37,   13,   16,  116,   43,  127,  146,  121,   55,
 /*   140 */    52,   47,   44,   53,   29,   30,   25,   26,   36,   35,
 /*   150 */    33,   31,   34,   32,   28,   27,   42,   41,   40,   39,
 /*   160 */    38,   37,  106,  118,   55,   43,  129,  145,   54,  133,
 /*   170 */   114,   47,   44,  245,   29,   30,   25,   26,   36,   35,
 /*   180 */    33,   31,   34,   32,   28,   27,   42,   41,   40,   39,
 /*   190 */    38,   37,  245,  245,  245,   43,  245,  141,  245,  245,
 /*   200 */   245,   47,   44,  245,   29,   30,   25,   26,   36,   35,
 /*   210 */    33,   31,   34,   32,   28,   27,   42,   41,   40,   39,
 /*   220 */    38,   37,  245,  245,  245,   43,  245,   47,   44,  139,
 /*   230 */    29,   30,   25,   26,   36,   35,   33,   31,   34,   32,
 /*   240 */    28,   27,   42,   41,   40,   39,   38,   37,  245,  245,
 /*   250 */   245,   43,  245,   47,   44,  137,   29,   30,   25,   26,
 /*   260 */    36,   35,   33,   31,   34,   32,   28,   27,   42,   41,
 /*   270 */    40,   39,   38,   37,  245,   19,  245,   43,  245,   47,
 /*   280 */    44,  134,   29,   30,   25,   26,   36,   35,   33,   31,
 /*   290 */    34,   32,   28,   27,   42,   41,   40,   39,   38,   37,
 /*   300 */   245,   47,   44,   43,   29,   30,   25,   26,   36,   35,
 /*   310 */    33,   31,   34,   32,   28,   27,   42,   41,   40,   39,
 /*   320 */    38,   37,  245,  245,  245,   43,  245,  245,  245,  245,
 /*   330 */   245,  245,  132,  245,  245,  245,  245,  245,   47,   44,
 /*   340 */   245,   29,   30,   25,   26,   36,   35,   33,   31,   34,
 /*   350 */    32,   28,   27,   42,   41,   40,   39,   38,   37,   72,
 /*   360 */   245,  245,   43,  113,  112,  158,  157,  156,  155,   51,
 /*   370 */   111,  245,   97,  122,   90,  117,  245,  131,  152,  245,
 /*   380 */   149,  148,  147,   47,   44,  245,   29,   30,   25,   26,
 /*   390 */    36,   35,   33,   31,   34,   32,   28,   27,   42,   41,
 /*   400 */    40,   39,   38,   37,  245,  245,  245,   43,   28,   27,
 /*   410 */    42,   41,   40,   39,   38,   37,   10,   50,  245,   43,
 /*   420 */   245,  245,  245,   47,   44,  245,   29,   30,   25,   26,
 /*   430 */    36,   35,   33,   31,   34,   32,   28,   27,   42,   41,
 /*   440 */    40,   39,   38,   37,  245,  106,  245,   43,  245,  245,
 /*   450 */   245,  245,  133,  245,  107,  245,  245,  130,  245,   14,
 /*   460 */   245,  245,  245,   47,   44,  245,   29,   30,   25,   26,
 /*   470 */    36,   35,   33,   31,   34,   32,   28,   27,   42,   41,
 /*   480 */    40,   39,   38,   37,  245,   47,   44,   43,   29,   30,
 /*   490 */    25,   26,   36,   35,   33,   31,   34,   32,   28,   27,
 /*   500 */    42,   41,   40,   39,   38,   37,  245,  245,  245,   43,
 /*   510 */    29,   30,   25,   26,   36,   35,   33,   31,   34,   32,
 /*   520 */    28,   27,   42,   41,   40,   39,   38,   37,  245,  245,
 /*   530 */   245,   43,   30,   25,   26,   36,   35,   33,   31,   34,
 /*   540 */    32,   28,   27,   42,   41,   40,   39,   38,   37,  245,
 /*   550 */   245,  245,   43,   25,   26,   36,   35,   33,   31,   34,
 /*   560 */    32,   28,   27,   42,   41,   40,   39,   38,   37,  245,
 /*   570 */   245,  245,   43,   26,   36,   35,   33,   31,   34,   32,
 /*   580 */    28,   27,   42,   41,   40,   39,   38,   37,  245,  245,
 /*   590 */   245,   43,   36,   35,   33,   31,   34,   32,   28,   27,
 /*   600 */    42,   41,   40,   39,   38,   37,  162,  245,  245,   43,
 /*   610 */    33,   31,   34,   32,   28,   27,   42,   41,   40,   39,
 /*   620 */    38,   37,  245,  245,  245,   43,  245,  245,  245,  245,
 /*   630 */   245,  245,   23,   24,  245,  245,   12,  245,    2,  245,
 /*   640 */   245,   22,  161,   87,  245,  245,   23,   24,  245,  245,
 /*   650 */    12,   99,    2,  110,  144,  143,  142,   98,  245,  245,
 /*   660 */   245,  245,  245,  245,  245,  245,  245,  110,  144,  143,
 /*   670 */   142,  245,  245,   23,   24,  245,  245,   12,  245,    2,
 /*   680 */   108,   23,   24,  245,   98,   12,  245,    2,  245,  245,
 /*   690 */   245,  245,   98,  245,  110,  144,  143,  142,   18,  245,
 /*   700 */   245,  245,  110,  144,  143,  142,   23,   24,  245,  245,
 /*   710 */    12,  154,    2,  245,   23,   24,  245,   98,   12,  153,
 /*   720 */     2,  245,  245,  245,  245,   98,  245,  110,  144,  143,
 /*   730 */   142,  245,  245,  245,  245,  110,  144,  143,  142,   23,
 /*   740 */    24,  245,  245,   12,  135,    2,  245,   23,   24,  245,
 /*   750 */    98,   12,  136,    2,  245,  245,  245,  245,   98,  245,
 /*   760 */   110,  144,  143,  142,  245,  245,  245,  245,  110,  144,
 /*   770 */   143,  142,   23,   24,  245,  245,   12,  138,    2,   72,
 /*   780 */   245,  245,  245,   98,  245,  245,  245,  245,  151,  245,
 /*   790 */   111,    9,   97,  110,  144,  143,  142,   72,  152,  109,
 /*   800 */   149,  148,  147,   23,   24,  245,  150,   12,  111,    2,
 /*   810 */    97,  245,  245,  245,   98,  245,  152,   71,  149,  148,
 /*   820 */   147,  245,   72,  245,  110,  144,  143,  142,  111,  245,
 /*   830 */    97,  151,  245,  111,    6,   97,  152,   72,  149,  148,
 /*   840 */   147,  152,   72,  149,  148,  147,  151,  245,  111,    8,
 /*   850 */    97,  151,  245,  111,    7,   97,  152,   67,  149,  148,
 /*   860 */   147,  152,   70,  149,  148,  147,  245,  245,  111,  245,
 /*   870 */    97,  245,  245,  111,  245,   97,  152,  245,  149,  148,
 /*   880 */   147,  152,   73,  149,  148,  147,  245,   74,  245,  245,
 /*   890 */   245,  245,  245,  111,  245,   97,  245,  245,  111,  245,
 /*   900 */    97,  152,   89,  149,  148,  147,  152,   88,  149,  148,
 /*   910 */   147,  245,  245,  111,  245,   97,  245,  245,  111,  245,
 /*   920 */    97,  152,   96,  149,  148,  147,  152,   95,  149,  148,
 /*   930 */   147,  245,  245,  111,  245,   97,  245,  245,  111,  245,
 /*   940 */    97,  152,  245,  149,  148,  147,  152,   94,  149,  148,
 /*   950 */   147,  245,   93,  245,  245,  245,  245,  245,  111,  245,
 /*   960 */    97,  245,  245,  111,  245,   97,  152,   80,  149,  148,
 /*   970 */   147,  152,   79,  149,  148,  147,  245,  245,  111,  245,
 /*   980 */    97,  245,  245,  111,  245,   97,  152,   84,  149,  148,
 /*   990 */   147,  152,   83,  149,  148,  147,  245,  245,  111,  245,
 /*  1000 */    97,  245,  245,  111,  245,   97,  152,  245,  149,  148,
 /*  1010 */   147,  152,   82,  149,  148,  147,  245,   81,  245,  245,
 /*  1020 */   245,  245,  245,  111,  245,   97,  245,  245,  111,  245,
 /*  1030 */    97,  152,   76,  149,  148,  147,  152,   75,  149,  148,
 /*  1040 */   147,  245,  245,  111,  245,   97,  245,  245,  111,  245,
 /*  1050 */    97,  152,   86,  149,  148,  147,  152,   85,  149,  148,
 /*  1060 */   147,  245,  245,  111,  245,   97,  245,  245,  111,  245,
 /*  1070 */    97,  152,  245,  149,  148,  147,  152,   78,  149,  148,
 /*  1080 */   147,  245,   77,  245,  245,  245,  245,  245,  111,  245,
 /*  1090 */    97,  245,  245,  111,  245,   97,  152,   92,  149,  148,
 /*  1100 */   147,  152,   91,  149,  148,  147,  245,  245,  111,  245,
 /*  1110 */    97,  245,  245,  111,  245,   97,  152,   68,  149,  148,
 /*  1120 */   147,  152,   66,  149,  148,  147,  245,  245,  111,  245,
 /*  1130 */    97,  245,  245,  111,  245,   97,  152,  245,  149,  148,
 /*  1140 */   147,  152,   64,  149,  148,  147,  245,   63,  245,  245,
 /*  1150 */   245,  245,  245,  111,  245,   97,  245,  245,  111,  245,
 /*  1160 */    97,  152,   62,  149,  148,  147,  152,   60,  149,  148,
 /*  1170 */   147,  245,  245,  111,  245,   97,  245,  245,  111,  245,
 /*  1180 */    97,  152,   58,  149,  148,  147,  152,   59,  149,  148,
 /*  1190 */   147,  245,  245,  111,  245,   97,  245,  245,  111,  245,
 /*  1200 */    97,  152,  245,  149,  148,  147,  152,   57,  149,  148,
 /*  1210 */   147,  245,   56,  245,  245,  245,  245,  245,  111,  245,
 /*  1220 */    97,  245,  245,  111,  245,   97,  152,   69,  149,  148,
 /*  1230 */   147,  152,   65,  149,  148,  147,  173,  245,  111,  245,
 /*  1240 */    97,  245,  245,  111,  245,   97,  152,   61,  149,  148,
 /*  1250 */   147,  152,  245,  149,  148,  147,  245,  245,  111,  245,
 /*  1260 */    97,  245,  245,  245,  245,    4,  152,   11,  149,  148,
 /*  1270 */   147,  245,  173,  245,  173,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     5,    6,   36,    8,    9,   10,   11,   12,   13,   14,
 /*    10 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*    20 */    25,   30,   36,   32,   29,   20,   21,   22,   23,   24,
 /*    30 */    25,   36,   25,   32,   29,   40,   29,    5,    6,   30,
 /*    40 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*    50 */    18,   19,   20,   21,   22,   23,   24,   25,   30,   33,
 /*    60 */    32,   29,    2,   22,   23,   24,   25,    1,   36,    2,
 /*    70 */    29,   37,   40,   30,    5,    6,   38,    8,    9,   10,
 /*    80 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    90 */    21,   22,   23,   24,   25,   37,   30,   52,   29,   36,
 /*   100 */    55,   56,   37,   37,   39,   36,   70,   71,   41,   40,
 /*   110 */    31,    5,    6,   40,    8,    9,   10,   11,   12,   13,
 /*   120 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   130 */    24,   25,    1,    1,   46,   29,   37,   31,   70,   71,
 /*   140 */    63,    5,    6,   63,    8,    9,   10,   11,   12,   13,
 /*   150 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   160 */    24,   25,   30,   70,   71,   29,   77,   31,   42,   37,
 /*   170 */    51,    5,    6,   78,    8,    9,   10,   11,   12,   13,
 /*   180 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   190 */    24,   25,   78,   78,   78,   29,   78,   31,   78,   78,
 /*   200 */    78,    5,    6,   78,    8,    9,   10,   11,   12,   13,
 /*   210 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   220 */    24,   25,   78,   78,   78,   29,   78,    5,    6,   33,
 /*   230 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   240 */    18,   19,   20,   21,   22,   23,   24,   25,   78,   78,
 /*   250 */    78,   29,   78,    5,    6,   33,    8,    9,   10,   11,
 /*   260 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   270 */    22,   23,   24,   25,   78,    1,   78,   29,   78,    5,
 /*   280 */     6,   33,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   290 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*   300 */    78,    5,    6,   29,    8,    9,   10,   11,   12,   13,
 /*   310 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   320 */    24,   25,   78,   78,   78,   29,   78,   78,   78,   78,
 /*   330 */    78,   78,   36,   78,   78,   78,   78,   78,    5,    6,
 /*   340 */    78,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   350 */    17,   18,   19,   20,   21,   22,   23,   24,   25,   53,
 /*   360 */    78,   78,   29,   57,   58,   59,   60,   61,   62,   63,
 /*   370 */    64,   78,   66,   67,   68,   69,   78,   44,   72,   78,
 /*   380 */    74,   75,   76,    5,    6,   78,    8,    9,   10,   11,
 /*   390 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   400 */    22,   23,   24,   25,   78,   78,   78,   29,   18,   19,
 /*   410 */    20,   21,   22,   23,   24,   25,    1,   39,   78,   29,
 /*   420 */    78,   78,   78,    5,    6,   78,    8,    9,   10,   11,
 /*   430 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   440 */    22,   23,   24,   25,   78,   30,   78,   29,   78,   78,
 /*   450 */    78,   78,   37,   78,   39,   78,   78,   39,   78,    1,
 /*   460 */    78,   78,   78,    5,    6,   78,    8,    9,   10,   11,
 /*   470 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   480 */    22,   23,   24,   25,   78,    5,    6,   29,    8,    9,
 /*   490 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   500 */    20,   21,   22,   23,   24,   25,   78,   78,   78,   29,
 /*   510 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   520 */    18,   19,   20,   21,   22,   23,   24,   25,   78,   78,
 /*   530 */    78,   29,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   540 */    17,   18,   19,   20,   21,   22,   23,   24,   25,   78,
 /*   550 */    78,   78,   29,   10,   11,   12,   13,   14,   15,   16,
 /*   560 */    17,   18,   19,   20,   21,   22,   23,   24,   25,   78,
 /*   570 */    78,   78,   29,   11,   12,   13,   14,   15,   16,   17,
 /*   580 */    18,   19,   20,   21,   22,   23,   24,   25,   78,   78,
 /*   590 */    78,   29,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   600 */    20,   21,   22,   23,   24,   25,    0,   78,   78,   29,
 /*   610 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   620 */    24,   25,   78,   78,   78,   29,   78,   78,   78,   78,
 /*   630 */    78,   78,   26,   27,   78,   78,   30,   78,   32,   78,
 /*   640 */    78,   21,   36,   37,   78,   78,   26,   27,   78,   78,
 /*   650 */    30,   45,   32,   47,   48,   49,   50,   37,   78,   78,
 /*   660 */    78,   78,   78,   78,   78,   78,   78,   47,   48,   49,
 /*   670 */    50,   78,   78,   26,   27,   78,   78,   30,   78,   32,
 /*   680 */    33,   26,   27,   78,   37,   30,   78,   32,   78,   78,
 /*   690 */    78,   78,   37,   78,   47,   48,   49,   50,   43,   78,
 /*   700 */    78,   78,   47,   48,   49,   50,   26,   27,   78,   78,
 /*   710 */    30,   31,   32,   78,   26,   27,   78,   37,   30,   31,
 /*   720 */    32,   78,   78,   78,   78,   37,   78,   47,   48,   49,
 /*   730 */    50,   78,   78,   78,   78,   47,   48,   49,   50,   26,
 /*   740 */    27,   78,   78,   30,   31,   32,   78,   26,   27,   78,
 /*   750 */    37,   30,   31,   32,   78,   78,   78,   78,   37,   78,
 /*   760 */    47,   48,   49,   50,   78,   78,   78,   78,   47,   48,
 /*   770 */    49,   50,   26,   27,   78,   78,   30,   31,   32,   53,
 /*   780 */    78,   78,   78,   37,   78,   78,   78,   78,   62,   78,
 /*   790 */    64,   65,   66,   47,   48,   49,   50,   53,   72,   73,
 /*   800 */    74,   75,   76,   26,   27,   78,   62,   30,   64,   32,
 /*   810 */    66,   78,   78,   78,   37,   78,   72,   53,   74,   75,
 /*   820 */    76,   78,   53,   78,   47,   48,   49,   50,   64,   78,
 /*   830 */    66,   62,   78,   64,   65,   66,   72,   53,   74,   75,
 /*   840 */    76,   72,   53,   74,   75,   76,   62,   78,   64,   65,
 /*   850 */    66,   62,   78,   64,   65,   66,   72,   53,   74,   75,
 /*   860 */    76,   72,   53,   74,   75,   76,   78,   78,   64,   78,
 /*   870 */    66,   78,   78,   64,   78,   66,   72,   78,   74,   75,
 /*   880 */    76,   72,   53,   74,   75,   76,   78,   53,   78,   78,
 /*   890 */    78,   78,   78,   64,   78,   66,   78,   78,   64,   78,
 /*   900 */    66,   72,   53,   74,   75,   76,   72,   53,   74,   75,
 /*   910 */    76,   78,   78,   64,   78,   66,   78,   78,   64,   78,
 /*   920 */    66,   72,   53,   74,   75,   76,   72,   53,   74,   75,
 /*   930 */    76,   78,   78,   64,   78,   66,   78,   78,   64,   78,
 /*   940 */    66,   72,   78,   74,   75,   76,   72,   53,   74,   75,
 /*   950 */    76,   78,   53,   78,   78,   78,   78,   78,   64,   78,
 /*   960 */    66,   78,   78,   64,   78,   66,   72,   53,   74,   75,
 /*   970 */    76,   72,   53,   74,   75,   76,   78,   78,   64,   78,
 /*   980 */    66,   78,   78,   64,   78,   66,   72,   53,   74,   75,
 /*   990 */    76,   72,   53,   74,   75,   76,   78,   78,   64,   78,
 /*  1000 */    66,   78,   78,   64,   78,   66,   72,   78,   74,   75,
 /*  1010 */    76,   72,   53,   74,   75,   76,   78,   53,   78,   78,
 /*  1020 */    78,   78,   78,   64,   78,   66,   78,   78,   64,   78,
 /*  1030 */    66,   72,   53,   74,   75,   76,   72,   53,   74,   75,
 /*  1040 */    76,   78,   78,   64,   78,   66,   78,   78,   64,   78,
 /*  1050 */    66,   72,   53,   74,   75,   76,   72,   53,   74,   75,
 /*  1060 */    76,   78,   78,   64,   78,   66,   78,   78,   64,   78,
 /*  1070 */    66,   72,   78,   74,   75,   76,   72,   53,   74,   75,
 /*  1080 */    76,   78,   53,   78,   78,   78,   78,   78,   64,   78,
 /*  1090 */    66,   78,   78,   64,   78,   66,   72,   53,   74,   75,
 /*  1100 */    76,   72,   53,   74,   75,   76,   78,   78,   64,   78,
 /*  1110 */    66,   78,   78,   64,   78,   66,   72,   53,   74,   75,
 /*  1120 */    76,   72,   53,   74,   75,   76,   78,   78,   64,   78,
 /*  1130 */    66,   78,   78,   64,   78,   66,   72,   78,   74,   75,
 /*  1140 */    76,   72,   53,   74,   75,   76,   78,   53,   78,   78,
 /*  1150 */    78,   78,   78,   64,   78,   66,   78,   78,   64,   78,
 /*  1160 */    66,   72,   53,   74,   75,   76,   72,   53,   74,   75,
 /*  1170 */    76,   78,   78,   64,   78,   66,   78,   78,   64,   78,
 /*  1180 */    66,   72,   53,   74,   75,   76,   72,   53,   74,   75,
 /*  1190 */    76,   78,   78,   64,   78,   66,   78,   78,   64,   78,
 /*  1200 */    66,   72,   78,   74,   75,   76,   72,   53,   74,   75,
 /*  1210 */    76,   78,   53,   78,   78,   78,   78,   78,   64,   78,
 /*  1220 */    66,   78,   78,   64,   78,   66,   72,   53,   74,   75,
 /*  1230 */    76,   72,   53,   74,   75,   76,    1,   78,   64,   78,
 /*  1240 */    66,   78,   78,   64,   78,   66,   72,   53,   74,   75,
 /*  1250 */    76,   72,   78,   74,   75,   76,   78,   78,   64,   78,
 /*  1260 */    66,   78,   78,   78,   78,   30,   72,   32,   74,   75,
 /*  1270 */    76,   78,   37,   78,   39,
};
#define YY_SHIFT_USE_DFLT (-35)
#define YY_SHIFT_COUNT (113)
#define YY_SHIFT_MIN   (-34)
#define YY_SHIFT_MAX   (1235)
static const short yy_shift_ofst[] = {
 /*     0 */   119,  606,  777,  746,  721,  777,  713,  688,  680,  777,
 /*    10 */   655,  647,  620,  777,  777,  777,  777,  777,  777,  777,
 /*    20 */   777,  777,  777,  777,  777,  777,  777,  777,  777,  777,
 /*    30 */   777,  777,  777,  777,  777,  777,  777,  777,  777,  777,
 /*    40 */   777,  777,  777,  777,  777,  777,  777,  777,  126,  126,
 /*    50 */   126,  415,  132,   66,   65,   99,   69,   32,   -5,  458,
 /*    60 */   418,  378,  333,  296,  274,  248,  222,  196,  166,  136,
 /*    70 */   106,  480,  480,  502,  502,  523,  543,  562,  580,  596,
 /*    80 */   596,  390,  390,  390,  390,    5,    5, 1235,   41,   41,
 /*    90 */    67,    7,    7,    7,    7,    7,    7,   28,   -9,   88,
 /*   100 */   131,   73,   63,   79,   58,   38,   34,   60,   43,   26,
 /*   110 */     9,    1,  -14,  -34,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (55)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (1194)
static const short yy_reduce_ofst[] = {
 /*     0 */    45,  306,  726,  789,  784,  769,  744,  744,  744,  744,
 /*    10 */  1194, 1179, 1174, 1159, 1154, 1134, 1129, 1114, 1109, 1094,
 /*    20 */  1089, 1069, 1064, 1049, 1044, 1029, 1024, 1004,  999,  984,
 /*    30 */   979,  964,  959,  939,  934,  919,  914,  899,  894,  874,
 /*    40 */   869,  854,  849,  834,  829,  809,  804,  764,   93,   68,
 /*    50 */    36,   89,   89,   89,   80,   77,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   163,  243,  201,  243,  243,  243,  243,  243,  243,  202,
 /*    10 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    20 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    30 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    40 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  183,
 /*    50 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    60 */   243,  195,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    70 */   243,  213,  171,  214,  215,  229,  228,  236,  235,  223,
 /*    80 */   222,  227,  226,  225,  224,  234,  233,  174,  217,  216,
 /*    90 */   243,  232,  230,  221,  220,  219,  218,  240,  174,  243,
 /*   100 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*   110 */   243,  180,  243,  243,  242,  241,  194,  186,  188,  185,
 /*   120 */   184,  187,  181,  196,  192,  191,  189,  173,  212,  211,
 /*   130 */   190,  193,  182,  172,  238,  176,  178,  239,  179,  237,
 /*   140 */   200,  231,  210,  209,  208,  207,  206,  205,  204,  203,
 /*   150 */   198,  197,  199,  177,  175,  170,  169,  168,  167,  166,
 /*   160 */   165,  164,
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
  "FUNCTION_CALL",  "PREPEND",       "APPEND",        "INDEX",       
  "OR",            "AND",           "BITXOR",        "BITAND",      
  "EQUALTO",       "NOTEQUALTO",    "GREATERTHAN",   "GORE",        
  "LESSTHAN",      "LORE",          "SHIFTL",        "SHIFTR",      
  "PLUS",          "MINUS",         "DIVIDE",        "TIMES",       
  "MODULO",        "POW",           "NOT",           "BITNOT",      
  "UMINUS",        "PLUSPLUS",      "LPAREN",        "RPAREN",      
  "LBRAC",         "RBRAC",         "COMMA",         "COLLECTARRAY",
  "DELIMITER",     "NAME",          "COLON",         "LCURL",       
  "RCURL",         "WILDCARD",      "WHERE",         "CASE",        
  "OF",            "LET",           "IN",            "PRINT",       
  "NUM",           "STRING",        "BOOLEAN",       "OPENQUOTEERROR",
  "error",         "expr",          "id",            "main",        
  "in",            "start",         "test",          "spec",        
  "assignment",    "top_stmt",      "stmt",          "name_chain",  
  "function_call",  "stmt_list",     "array_index",   "case_statement",
  "guard_statement",  "final_guard_statement",  "final_where_statement",  "where_statement",
  "array",         "maybe_empty_stmt_list",  "num",           "string",      
  "bool",          "pattern_argument",
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
 /*  13 */ "function_call ::= NAME LPAREN stmt_list RPAREN",
 /*  14 */ "function_call ::= NAME LBRAC RBRAC LPAREN stmt_list RPAREN",
 /*  15 */ "expr ::= array_index LPAREN stmt_list RPAREN",
 /*  16 */ "function_call ::= NAME LPAREN RPAREN",
 /*  17 */ "function_call ::= array_index LPAREN RPAREN",
 /*  18 */ "expr ::= function_call",
 /*  19 */ "test ::= case_statement",
 /*  20 */ "guard_statement ::= name_chain LCURL BITOR expr ASSIGN expr DELIMITER",
 /*  21 */ "guard_statement ::= guard_statement BITOR expr ASSIGN expr DELIMITER",
 /*  22 */ "final_guard_statement ::= guard_statement BITOR expr ASSIGN expr RCURL",
 /*  23 */ "final_guard_statement ::= guard_statement WILDCARD ASSIGN expr RCURL",
 /*  24 */ "assignment ::= final_guard_statement",
 /*  25 */ "assignment ::= guard_statement BITOR expr ASSIGN expr DELIMITER final_where_statement",
 /*  26 */ "assignment ::= guard_statement WILDCARD ASSIGN expr DELIMITER final_where_statement",
 /*  27 */ "where_statement ::= WHERE LCURL",
 /*  28 */ "where_statement ::= WHERE name_chain ASSIGN expr LCURL",
 /*  29 */ "where_statement ::= where_statement name_chain ASSIGN expr DELIMITER",
 /*  30 */ "final_where_statement ::= where_statement name_chain ASSIGN expr RCURL DELIMITER RCURL",
 /*  31 */ "case_statement ::= name_chain ASSIGN CASE expr OF",
 /*  32 */ "test ::= LET IN",
 /*  33 */ "assignment ::= name_chain ASSIGN expr",
 /*  34 */ "assignment ::= name_chain ASSIGN expr LCURL final_where_statement",
 /*  35 */ "stmt_list ::= stmt",
 /*  36 */ "stmt_list ::= stmt_list stmt",
 /*  37 */ "expr ::= array",
 /*  38 */ "array ::= LBRAC maybe_empty_stmt_list RBRAC",
 /*  39 */ "maybe_empty_stmt_list ::=",
 /*  40 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  41 */ "expr ::= num",
 /*  42 */ "expr ::= string",
 /*  43 */ "expr ::= bool",
 /*  44 */ "expr ::= PRINT LPAREN expr RPAREN",
 /*  45 */ "expr ::= LPAREN expr RPAREN",
 /*  46 */ "num ::= NUM",
 /*  47 */ "string ::= STRING",
 /*  48 */ "bool ::= BOOLEAN",
 /*  49 */ "name_chain ::= name_chain pattern_argument",
 /*  50 */ "pattern_argument ::= LPAREN NAME COLON NAME RPAREN",
 /*  51 */ "expr ::= expr PREPEND expr",
 /*  52 */ "expr ::= expr APPEND expr",
 /*  53 */ "expr ::= expr PLUSPLUS expr",
 /*  54 */ "expr ::= expr PLUS expr",
 /*  55 */ "expr ::= expr MINUS expr",
 /*  56 */ "expr ::= expr DIVIDE expr",
 /*  57 */ "expr ::= expr TIMES expr",
 /*  58 */ "expr ::= expr MODULO expr",
 /*  59 */ "expr ::= expr POW expr",
 /*  60 */ "expr ::= expr EQUALTO expr",
 /*  61 */ "expr ::= expr NOTEQUALTO expr",
 /*  62 */ "expr ::= expr LESSTHAN expr",
 /*  63 */ "expr ::= expr GREATERTHAN expr",
 /*  64 */ "expr ::= expr LORE expr",
 /*  65 */ "expr ::= expr GORE expr",
 /*  66 */ "expr ::= expr AND expr",
 /*  67 */ "expr ::= expr OR expr",
 /*  68 */ "expr ::= BITNOT expr",
 /*  69 */ "expr ::= LPAREN MINUS expr RPAREN",
 /*  70 */ "expr ::= NOT expr",
 /*  71 */ "expr ::= expr SHIFTL expr",
 /*  72 */ "expr ::= expr SHIFTR expr",
 /*  73 */ "expr ::= expr BITAND expr",
 /*  74 */ "expr ::= expr BITXOR expr",
 /*  75 */ "array_index ::= function_call LBRAC expr RBRAC",
 /*  76 */ "array_index ::= NAME LBRAC expr RBRAC",
 /*  77 */ "array_index ::= array_index LBRAC expr RBRAC",
 /*  78 */ "expr ::= array_index",
 /*  79 */ "in ::= error",
 /*  80 */ "error ::= OPENQUOTEERROR",
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
    case 5: /* PREPEND */
    case 6: /* APPEND */
    case 7: /* INDEX */
    case 8: /* OR */
    case 9: /* AND */
    case 10: /* BITXOR */
    case 11: /* BITAND */
    case 12: /* EQUALTO */
    case 13: /* NOTEQUALTO */
    case 14: /* GREATERTHAN */
    case 15: /* GORE */
    case 16: /* LESSTHAN */
    case 17: /* LORE */
    case 18: /* SHIFTL */
    case 19: /* SHIFTR */
    case 20: /* PLUS */
    case 21: /* MINUS */
    case 22: /* DIVIDE */
    case 23: /* TIMES */
    case 24: /* MODULO */
    case 25: /* POW */
    case 26: /* NOT */
    case 27: /* BITNOT */
    case 28: /* UMINUS */
    case 29: /* PLUSPLUS */
    case 30: /* LPAREN */
    case 31: /* RPAREN */
    case 32: /* LBRAC */
    case 33: /* RBRAC */
    case 34: /* COMMA */
    case 35: /* COLLECTARRAY */
    case 36: /* DELIMITER */
    case 37: /* NAME */
    case 38: /* COLON */
    case 39: /* LCURL */
    case 40: /* RCURL */
    case 41: /* WILDCARD */
    case 42: /* WHERE */
    case 43: /* CASE */
    case 44: /* OF */
    case 45: /* LET */
    case 46: /* IN */
    case 47: /* PRINT */
    case 48: /* NUM */
    case 49: /* STRING */
    case 50: /* BOOLEAN */
    case 51: /* OPENQUOTEERROR */
{
#line 43 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 824 "./src/Grammar/grammar.c"
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
  { 64, 4 },
  { 64, 6 },
  { 53, 4 },
  { 64, 3 },
  { 64, 3 },
  { 53, 1 },
  { 58, 1 },
  { 68, 7 },
  { 68, 6 },
  { 69, 6 },
  { 69, 5 },
  { 60, 1 },
  { 60, 7 },
  { 60, 6 },
  { 71, 2 },
  { 71, 5 },
  { 71, 5 },
  { 70, 7 },
  { 67, 5 },
  { 58, 2 },
  { 60, 3 },
  { 60, 5 },
  { 65, 1 },
  { 65, 2 },
  { 53, 1 },
  { 72, 3 },
  { 73, 0 },
  { 73, 1 },
  { 53, 1 },
  { 53, 1 },
  { 53, 1 },
  { 53, 4 },
  { 53, 3 },
  { 74, 1 },
  { 75, 1 },
  { 76, 1 },
  { 63, 2 },
  { 77, 5 },
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
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 2 },
  { 53, 4 },
  { 53, 2 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 66, 4 },
  { 66, 4 },
  { 66, 4 },
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
      case 2: /* in ::= in DELIMITER */
      case 3: /* in ::= in start DELIMITER */ yytestcase(yyruleno==3);
      case 4: /* in ::= in test DELIMITER */ yytestcase(yyruleno==4);
#line 86 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,36,&yymsp[0].minor);
}
#line 1204 "./src/Grammar/grammar.c"
        break;
      case 5: /* start ::= spec */
#line 92 "./src/Grammar/grammar.y"
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
#line 1227 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= assignment */
      case 19: /* test ::= case_statement */ yytestcase(yyruleno==19);
#line 113 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1235 "./src/Grammar/grammar.c"
        break;
      case 7: /* spec ::= top_stmt */
      case 8: /* top_stmt ::= stmt */ yytestcase(yyruleno==8);
#line 118 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1244 "./src/Grammar/grammar.c"
        break;
      case 9: /* stmt ::= expr */
      case 35: /* stmt_list ::= stmt */ yytestcase(yyruleno==35);
#line 130 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1253 "./src/Grammar/grammar.c"
        break;
      case 10: /* name_chain ::= name_chain NAME */
#line 136 "./src/Grammar/grammar.y"
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
#line 1292 "./src/Grammar/grammar.c"
        break;
      case 11: /* name_chain ::= NAME */
#line 173 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1301 "./src/Grammar/grammar.c"
        break;
      case 12: /* expr ::= NAME */
#line 180 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0.data.string = new optic::String(yymsp[0].minor.yy0.data.string->c_str());
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1314 "./src/Grammar/grammar.c"
        break;
      case 13: /* function_call ::= NAME LPAREN stmt_list RPAREN */
#line 196 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,30,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1346 "./src/Grammar/grammar.c"
        break;
      case 14: /* function_call ::= NAME LBRAC RBRAC LPAREN stmt_list RPAREN */
#line 224 "./src/Grammar/grammar.y"
{
/*    std::cout << "yymsp[-5].minor.yy0.type = optic::Array_Map_Value_To_Functions" << std::endl;*/
/*    std::cout << *yymsp[-5].minor.yy0.data.string << std::endl;*/
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
  yy_destructor(yypParser,32,&yymsp[-4].minor);
  yy_destructor(yypParser,33,&yymsp[-3].minor);
  yy_destructor(yypParser,30,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1380 "./src/Grammar/grammar.c"
        break;
      case 15: /* expr ::= array_index LPAREN stmt_list RPAREN */
#line 252 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,30,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1406 "./src/Grammar/grammar.c"
        break;
      case 16: /* function_call ::= NAME LPAREN RPAREN */
#line 275 "./src/Grammar/grammar.y"
{
    yymsp[-2].minor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,30,&yymsp[-1].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1421 "./src/Grammar/grammar.c"
        break;
      case 17: /* function_call ::= array_index LPAREN RPAREN */
#line 286 "./src/Grammar/grammar.y"
{
/*    yymsp[-2].minor.yy0.type = optic::UNDECLARED_VARIABLE;*/
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,30,&yymsp[-1].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1436 "./src/Grammar/grammar.c"
        break;
      case 18: /* expr ::= function_call */
      case 37: /* expr ::= array */ yytestcase(yyruleno==37);
      case 78: /* expr ::= array_index */ yytestcase(yyruleno==78);
#line 297 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1445 "./src/Grammar/grammar.c"
        break;
      case 20: /* guard_statement ::= name_chain LCURL BITOR expr ASSIGN expr DELIMITER */
#line 309 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD1" << std::endl;
    optic::object tree = create_condition_tree(yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0 = create_guard(yymsp[-6].minor.yy0,tree);
    std::cout << "GUARD2" << std::endl;
  yy_destructor(yypParser,39,&yymsp[-5].minor);
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,36,&yymsp[0].minor);
}
#line 1459 "./src/Grammar/grammar.c"
        break;
      case 21: /* guard_statement ::= guard_statement BITOR expr ASSIGN expr DELIMITER */
#line 317 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD3" << std::endl;
    add_branch_to_tree(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-5].minor.yy0;
    std::cout << "GUARD4" << std::endl;
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,36,&yymsp[0].minor);
}
#line 1472 "./src/Grammar/grammar.c"
        break;
      case 22: /* final_guard_statement ::= guard_statement BITOR expr ASSIGN expr RCURL */
#line 325 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD5" << std::endl;
    add_branch_to_tree(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-5].minor.yy0;
    std::cout << "GUARD6" << std::endl;
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,40,&yymsp[0].minor);
}
#line 1485 "./src/Grammar/grammar.c"
        break;
      case 23: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr RCURL */
#line 333 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD7" << std::endl;
    add_wildcard_to_tree(yymsp[-4].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-4].minor.yy0;
    std::cout << "GUARD8" << std::endl;
  yy_destructor(yypParser,41,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,40,&yymsp[0].minor);
}
#line 1498 "./src/Grammar/grammar.c"
        break;
      case 24: /* assignment ::= final_guard_statement */
#line 341 "./src/Grammar/grammar.y"
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
#line 1519 "./src/Grammar/grammar.c"
        break;
      case 25: /* assignment ::= guard_statement BITOR expr ASSIGN expr DELIMITER final_where_statement */
#line 360 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,36,&yymsp[-1].minor);
}
#line 1542 "./src/Grammar/grammar.c"
        break;
      case 26: /* assignment ::= guard_statement WILDCARD ASSIGN expr DELIMITER final_where_statement */
#line 378 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,41,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,36,&yymsp[-1].minor);
}
#line 1565 "./src/Grammar/grammar.c"
        break;
      case 27: /* where_statement ::= WHERE LCURL */
#line 400 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::NIL;
    std::cout << "Where 1" << std::endl;
  yy_destructor(yypParser,42,&yymsp[-1].minor);
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1575 "./src/Grammar/grammar.c"
        break;
      case 28: /* where_statement ::= WHERE name_chain ASSIGN expr LCURL */
#line 406 "./src/Grammar/grammar.y"
{
    std::cout << "Where 1.5" << std::endl;
    insure_ready_for_assignment(yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yymsp[-3].minor.yy0.type = optic::FUNCTION_ARG_NAMES;
    panopticon::store_operations(yygotominor.yy0, yymsp[-3].minor.yy0, yymsp[-1].minor.yy0, panopticon::assign_variable,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,42,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1593 "./src/Grammar/grammar.c"
        break;
      case 29: /* where_statement ::= where_statement name_chain ASSIGN expr DELIMITER */
#line 419 "./src/Grammar/grammar.y"
{
    std::cout << "Where 2" << std::endl;
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
  yy_destructor(yypParser,36,&yymsp[0].minor);
}
#line 1620 "./src/Grammar/grammar.c"
        break;
      case 30: /* final_where_statement ::= where_statement name_chain ASSIGN expr RCURL DELIMITER RCURL */
#line 442 "./src/Grammar/grammar.y"
{
    std::cout << "Where 3" << std::endl;
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
  yy_destructor(yypParser,40,&yymsp[-2].minor);
  yy_destructor(yypParser,36,&yymsp[-1].minor);
  yy_destructor(yypParser,40,&yymsp[0].minor);
}
#line 1648 "./src/Grammar/grammar.c"
        break;
      case 31: /* case_statement ::= name_chain ASSIGN CASE expr OF */
#line 464 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,43,&yymsp[-2].minor);
  yy_destructor(yypParser,44,&yymsp[0].minor);
}
#line 1659 "./src/Grammar/grammar.c"
        break;
      case 32: /* test ::= LET IN */
#line 469 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,45,&yymsp[-1].minor);
  yy_destructor(yypParser,46,&yymsp[0].minor);
}
#line 1667 "./src/Grammar/grammar.c"
        break;
      case 33: /* assignment ::= name_chain ASSIGN expr */
#line 478 "./src/Grammar/grammar.y"
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
#line 1682 "./src/Grammar/grammar.c"
        break;
      case 34: /* assignment ::= name_chain ASSIGN expr LCURL final_where_statement */
#line 491 "./src/Grammar/grammar.y"
{
    std::cout << "Where assign" << std::endl;
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
  yy_destructor(yypParser,39,&yymsp[-1].minor);
}
#line 1700 "./src/Grammar/grammar.c"
        break;
      case 36: /* stmt_list ::= stmt_list stmt */
#line 542 "./src/Grammar/grammar.y"
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
#line 1718 "./src/Grammar/grammar.c"
        break;
      case 38: /* array ::= LBRAC maybe_empty_stmt_list RBRAC */
#line 563 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yygotominor.yy0.type = optic::ARRAY;
  yy_destructor(yypParser,32,&yymsp[-2].minor);
  yy_destructor(yypParser,33,&yymsp[0].minor);
}
#line 1728 "./src/Grammar/grammar.c"
        break;
      case 39: /* maybe_empty_stmt_list ::= */
#line 569 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1736 "./src/Grammar/grammar.c"
        break;
      case 40: /* maybe_empty_stmt_list ::= stmt_list */
#line 575 "./src/Grammar/grammar.y"
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
#line 1752 "./src/Grammar/grammar.c"
        break;
      case 41: /* expr ::= num */
      case 43: /* expr ::= bool */ yytestcase(yyruleno==43);
#line 593 "./src/Grammar/grammar.y"
{
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1760 "./src/Grammar/grammar.c"
        break;
      case 42: /* expr ::= string */
#line 598 "./src/Grammar/grammar.y"
{
   create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1767 "./src/Grammar/grammar.c"
        break;
      case 44: /* expr ::= PRINT LPAREN expr RPAREN */
#line 612 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-1].minor.yy0,&optic::unary_print_object);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,47,&yymsp[-3].minor);
  yy_destructor(yypParser,30,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1782 "./src/Grammar/grammar.c"
        break;
      case 45: /* expr ::= LPAREN expr RPAREN */
#line 622 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
  yy_destructor(yypParser,30,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1791 "./src/Grammar/grammar.c"
        break;
      case 46: /* num ::= NUM */
#line 627 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1799 "./src/Grammar/grammar.c"
        break;
      case 47: /* string ::= STRING */
#line 633 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::STRING;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1807 "./src/Grammar/grammar.c"
        break;
      case 48: /* bool ::= BOOLEAN */
#line 640 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::BOOL;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1815 "./src/Grammar/grammar.c"
        break;
      case 49: /* name_chain ::= name_chain pattern_argument */
#line 658 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
}
#line 1822 "./src/Grammar/grammar.c"
        break;
      case 50: /* pattern_argument ::= LPAREN NAME COLON NAME RPAREN */
#line 663 "./src/Grammar/grammar.y"
{
    std::cout << "PATTERN_ARGUMENT" << std::endl;
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0 = yymsp[-1].minor.yy0;
/*    yygotominor.yy0 = B;*/
  yy_destructor(yypParser,30,&yymsp[-4].minor);
  yy_destructor(yypParser,38,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1835 "./src/Grammar/grammar.c"
        break;
      case 51: /* expr ::= expr PREPEND expr */
#line 676 "./src/Grammar/grammar.y"
{
    std::cout << "PREPEND" << std::endl;
    optic::store_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&optic::prepend,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1849 "./src/Grammar/grammar.c"
        break;
      case 52: /* expr ::= expr APPEND expr */
#line 687 "./src/Grammar/grammar.y"
{
    std::cout << "APPEND" << std::endl;
    optic::store_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&optic::append,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1863 "./src/Grammar/grammar.c"
        break;
      case 53: /* expr ::= expr PLUSPLUS expr */
#line 698 "./src/Grammar/grammar.y"
{
    std::cout << "CONCAT" << std::endl;
    optic::store_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&optic::concat,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,29,&yymsp[-1].minor);
}
#line 1877 "./src/Grammar/grammar.c"
        break;
      case 54: /* expr ::= expr PLUS expr */
#line 709 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::plus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1890 "./src/Grammar/grammar.c"
        break;
      case 55: /* expr ::= expr MINUS expr */
#line 719 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1903 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr DIVIDE expr */
#line 729 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1916 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr TIMES expr */
#line 739 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1929 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= expr MODULO expr */
#line 749 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1942 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= expr POW expr */
#line 759 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,25,&yymsp[-1].minor);
}
#line 1955 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= expr EQUALTO expr */
#line 769 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1968 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= expr NOTEQUALTO expr */
#line 779 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1981 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= expr LESSTHAN expr */
#line 789 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1994 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= expr GREATERTHAN expr */
#line 799 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 2007 "./src/Grammar/grammar.c"
        break;
      case 64: /* expr ::= expr LORE expr */
#line 809 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 2020 "./src/Grammar/grammar.c"
        break;
      case 65: /* expr ::= expr GORE expr */
#line 819 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 2033 "./src/Grammar/grammar.c"
        break;
      case 66: /* expr ::= expr AND expr */
#line 829 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 2046 "./src/Grammar/grammar.c"
        break;
      case 67: /* expr ::= expr OR expr */
#line 839 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 2059 "./src/Grammar/grammar.c"
        break;
      case 68: /* expr ::= BITNOT expr */
#line 849 "./src/Grammar/grammar.y"
{
    store_operations(yygotominor.yy0,yymsp[0].minor.yy0,&optic::bit_not);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,27,&yymsp[-1].minor);
}
#line 2072 "./src/Grammar/grammar.c"
        break;
      case 69: /* expr ::= LPAREN MINUS expr RPAREN */
#line 859 "./src/Grammar/grammar.y"
{
    store_operations(yygotominor.yy0,yymsp[-1].minor.yy0,&panopticon::u_minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,30,&yymsp[-3].minor);
  yy_destructor(yypParser,21,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 2087 "./src/Grammar/grammar.c"
        break;
      case 70: /* expr ::= NOT expr */
#line 869 "./src/Grammar/grammar.y"
{
    store_operations(yygotominor.yy0,yymsp[0].minor.yy0,&panopticon::not_value);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,26,&yymsp[-1].minor);
}
#line 2100 "./src/Grammar/grammar.c"
        break;
      case 71: /* expr ::= expr SHIFTL expr */
#line 879 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 2113 "./src/Grammar/grammar.c"
        break;
      case 72: /* expr ::= expr SHIFTR expr */
#line 889 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 2126 "./src/Grammar/grammar.c"
        break;
      case 73: /* expr ::= expr BITAND expr */
#line 899 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 2139 "./src/Grammar/grammar.c"
        break;
      case 74: /* expr ::= expr BITXOR expr */
#line 909 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 2152 "./src/Grammar/grammar.c"
        break;
      case 75: /* array_index ::= function_call LBRAC expr RBRAC */
      case 77: /* array_index ::= array_index LBRAC expr RBRAC */ yytestcase(yyruleno==77);
#line 919 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,32,&yymsp[-2].minor);
  yy_destructor(yypParser,33,&yymsp[0].minor);
}
#line 2167 "./src/Grammar/grammar.c"
        break;
      case 76: /* array_index ::= NAME LBRAC expr RBRAC */
#line 929 "./src/Grammar/grammar.y"
{
    yymsp[-3].minor.yy0.type = optic::STRING;
    optic::store_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,32,&yymsp[-2].minor);
  yy_destructor(yypParser,33,&yymsp[0].minor);
}
#line 2182 "./src/Grammar/grammar.c"
        break;
      case 79: /* in ::= error */
#line 959 "./src/Grammar/grammar.y"
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
#line 2197 "./src/Grammar/grammar.c"
        break;
      case 80: /* error ::= OPENQUOTEERROR */
#line 972 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy157 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 2206 "./src/Grammar/grammar.c"
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
#line 80 "./src/Grammar/grammar.y"

panopticon::out() << "Syntax error!" << std::endl;
#line 2273 "./src/Grammar/grammar.c"
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
#line 75 "./src/Grammar/grammar.y"

printf("parsing complete!\n\n\n");
#line 2295 "./src/Grammar/grammar.c"
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
