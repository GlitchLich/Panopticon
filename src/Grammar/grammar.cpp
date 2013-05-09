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
#define YYNOCODE 81
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy161;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 177
#define YYNRULE 86
#define YYERRORSYMBOL 53
#define YYERRSYMDT yy161
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
#define YY_ACTTAB_COUNT (1552)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    56,  175,   48,   47,  174,   32,   33,   28,   29,   39,
 /*    10 */    38,   36,   34,   37,   35,   31,   30,   45,   44,   43,
 /*    20 */    42,   41,   40,    5,   50,   12,   46,   45,   44,   43,
 /*    30 */    42,   41,   40,  142,   49,  117,   46,  154,  112,    4,
 /*    40 */    56,   24,   48,   47,  155,   32,   33,   28,   29,   39,
 /*    50 */    38,   36,   34,   37,   35,   31,   30,   45,   44,   43,
 /*    60 */    42,   41,   40,    5,  129,   12,   46,  264,    1,   43,
 /*    70 */    42,   41,   40,   54,   40,  134,   46,  188,   46,  188,
 /*    80 */    56,   16,   48,   47,  144,   32,   33,   28,   29,   39,
 /*    90 */    38,   36,   34,   37,   35,   31,   30,   45,   44,   43,
 /*   100 */    42,   41,   40,  119,    6,  120,   46,   24,   21,    3,
 /*   110 */   148,   12,   20,   53,  148,  133,  188,  115,  138,  109,
 /*   120 */    56,  143,   48,   47,  148,   32,   33,   28,   29,   39,
 /*   130 */    38,   36,   34,   37,   35,   31,   30,   45,   44,   43,
 /*   140 */    42,   41,   40,  125,   23,   98,   46,   56,  161,   48,
 /*   150 */    47,  116,   32,   33,   28,   29,   39,   38,   36,   34,
 /*   160 */    37,   35,   31,   30,   45,   44,   43,   42,   41,   40,
 /*   170 */   140,   58,  141,   46,   56,  160,   48,   47,   18,   32,
 /*   180 */    33,   28,   29,   39,   38,   36,   34,   37,   35,   31,
 /*   190 */    30,   45,   44,   43,   42,   41,   40,  135,   58,  113,
 /*   200 */    46,   56,  156,   48,   47,  112,   32,   33,   28,   29,
 /*   210 */    39,   38,   36,   34,   37,   35,   31,   30,   45,   44,
 /*   220 */    43,   42,   41,   40,  132,   58,  111,   46,  137,   17,
 /*   230 */    56,  153,   48,   47,   14,   32,   33,   28,   29,   39,
 /*   240 */    38,   36,   34,   37,   35,   31,   30,   45,   44,   43,
 /*   250 */    42,   41,   40,  130,   96,  144,   46,   97,   99,   56,
 /*   260 */   151,   48,   47,   57,   32,   33,   28,   29,   39,   38,
 /*   270 */    36,   34,   37,   35,   31,   30,   45,   44,   43,   42,
 /*   280 */    41,   40,  128,   22,  265,   46,  265,  265,   56,  149,
 /*   290 */    48,   47,  265,   32,   33,   28,   29,   39,   38,   36,
 /*   300 */    34,   37,   35,   31,   30,   45,   44,   43,   42,   41,
 /*   310 */    40,  265,  265,   56,   46,   48,   47,  265,   32,   33,
 /*   320 */    28,   29,   39,   38,   36,   34,   37,   35,   31,   30,
 /*   330 */    45,   44,   43,   42,   41,   40,  265,  265,  265,   46,
 /*   340 */   265,  265,   56,  265,   48,   47,  146,   32,   33,   28,
 /*   350 */    29,   39,   38,   36,   34,   37,   35,   31,   30,   45,
 /*   360 */    44,   43,   42,   41,   40,  265,  265,  265,   46,  265,
 /*   370 */   265,  265,  265,  265,  265,   56,   55,   48,   47,  265,
 /*   380 */    32,   33,   28,   29,   39,   38,   36,   34,   37,   35,
 /*   390 */    31,   30,   45,   44,   43,   42,   41,   40,  265,  265,
 /*   400 */   265,   46,  265,  265,  265,  265,  265,  265,   56,  145,
 /*   410 */    48,   47,  265,   32,   33,   28,   29,   39,   38,   36,
 /*   420 */    34,   37,   35,   31,   30,   45,   44,   43,   42,   41,
 /*   430 */    40,  265,  265,  265,   46,   36,   34,   37,   35,   31,
 /*   440 */    30,   45,   44,   43,   42,   41,   40,  139,  265,   15,
 /*   450 */    46,  265,  265,  265,   56,  265,   48,   47,  265,   32,
 /*   460 */    33,   28,   29,   39,   38,   36,   34,   37,   35,   31,
 /*   470 */    30,   45,   44,   43,   42,   41,   40,  265,  265,   56,
 /*   480 */    46,   48,   47,  265,   32,   33,   28,   29,   39,   38,
 /*   490 */    36,   34,   37,   35,   31,   30,   45,   44,   43,   42,
 /*   500 */    41,   40,  265,   48,   47,   46,   32,   33,   28,   29,
 /*   510 */    39,   38,   36,   34,   37,   35,   31,   30,   45,   44,
 /*   520 */    43,   42,   41,   40,  265,  265,  265,   46,   32,   33,
 /*   530 */    28,   29,   39,   38,   36,   34,   37,   35,   31,   30,
 /*   540 */    45,   44,   43,   42,   41,   40,  265,  265,  265,   46,
 /*   550 */    33,   28,   29,   39,   38,   36,   34,   37,   35,   31,
 /*   560 */    30,   45,   44,   43,   42,   41,   40,  265,  265,  265,
 /*   570 */    46,   28,   29,   39,   38,   36,   34,   37,   35,   31,
 /*   580 */    30,   45,   44,   43,   42,   41,   40,   76,  265,  265,
 /*   590 */    46,  127,  126,  173,  172,  171,  170,   52,  124,  265,
 /*   600 */   106,  136,   95,  131,  265,  265,  166,  265,  164,  163,
 /*   610 */   162,   29,   39,   38,   36,   34,   37,   35,   31,   30,
 /*   620 */    45,   44,   43,   42,   41,   40,  265,  265,  107,   46,
 /*   630 */    39,   38,   36,   34,   37,   35,   31,   30,   45,   44,
 /*   640 */    43,   42,   41,   40,  265,  265,  265,   46,  177,   25,
 /*   650 */   265,   51,  265,  265,   26,   27,  119,  265,   13,  107,
 /*   660 */     2,   31,   30,   45,   44,   43,   42,   41,   40,  265,
 /*   670 */   110,  138,   46,  123,  159,  158,  157,   26,   27,  265,
 /*   680 */   265,   13,  107,    2,  265,   26,   27,  176,  265,   13,
 /*   690 */   107,    2,  121,   11,  108,  147,  123,  159,  158,  157,
 /*   700 */   265,  265,  265,  265,  123,  159,  158,  157,   26,   27,
 /*   710 */   265,  265,   13,  107,    2,  265,   26,   27,  265,  265,
 /*   720 */    13,  169,    2,   19,  107,  114,  265,  123,  159,  158,
 /*   730 */   157,  265,  118,  265,  265,  123,  159,  158,  157,   26,
 /*   740 */    27,  265,  265,   13,  168,    2,  265,  107,  265,  265,
 /*   750 */    26,   27,  265,  265,   13,  150,    2,  265,  123,  159,
 /*   760 */   158,  157,  265,  265,  265,  265,  265,  265,  265,  123,
 /*   770 */   159,  158,  157,   26,   27,  107,  265,   13,  152,    2,
 /*   780 */   265,  265,   94,  265,  265,  265,  265,  265,  265,  265,
 /*   790 */   265,  265,  123,  159,  158,  157,  265,  265,  265,  265,
 /*   800 */   265,   26,   27,  265,  265,   13,  154,    2,   26,   27,
 /*   810 */   265,  265,   13,  152,    2,  265,  265,  265,  265,  265,
 /*   820 */   123,  159,  158,  157,   76,  107,  265,  123,  159,  158,
 /*   830 */   157,  265,  265,  165,  265,  124,   10,  106,  265,  265,
 /*   840 */   265,  265,  265,  166,  122,  164,  163,  162,  265,  265,
 /*   850 */   265,   26,   27,  265,  265,   13,   76,    2,  265,  265,
 /*   860 */   265,  265,  265,  265,  265,  165,  265,  124,    7,  106,
 /*   870 */   123,  159,  158,  157,  265,  166,  265,  164,  163,  162,
 /*   880 */    76,  265,  265,  265,  265,   76,  265,  265,  265,  165,
 /*   890 */   265,  124,    9,  106,  165,  265,  124,    8,  106,  166,
 /*   900 */    76,  164,  163,  162,  166,  265,  164,  163,  162,  167,
 /*   910 */   265,  124,  265,  106,  265,  265,  265,  265,  265,  166,
 /*   920 */    68,  164,  163,  162,  265,   73,  265,  265,  265,  265,
 /*   930 */   265,  124,  265,  106,  265,  265,  124,  265,  106,  166,
 /*   940 */    77,  164,  163,  162,  166,  265,  164,  163,  162,  265,
 /*   950 */   265,  124,  265,  106,   79,  265,  265,  265,  265,  166,
 /*   960 */   265,  164,  163,  162,  265,  124,  265,  106,   78,  265,
 /*   970 */   265,  265,  265,  166,  265,  164,  163,  162,  265,  124,
 /*   980 */   265,  106,  265,  265,  265,  265,   93,  166,  265,  164,
 /*   990 */   163,  162,  265,   92,  265,  265,  265,  124,  265,  106,
 /*  1000 */   265,  265,  265,  265,  124,  166,  106,  164,  163,  162,
 /*  1010 */   265,  265,  166,  265,  164,  163,  162,  105,  265,  265,
 /*  1020 */   265,  265,  104,  265,  265,  265,  265,  265,  124,  265,
 /*  1030 */   106,  265,  265,  124,  265,  106,  166,  265,  164,  163,
 /*  1040 */   162,  166,  103,  164,  163,  162,  265,  265,  265,  265,
 /*  1050 */   265,  265,  265,  124,  265,  106,  265,  265,  265,  102,
 /*  1060 */   265,  166,  265,  164,  163,  162,  265,  265,  265,  265,
 /*  1070 */   124,  265,  106,  265,  265,  265,  265,   85,  166,  265,
 /*  1080 */   164,  163,  162,  265,  265,  265,  265,  265,  124,  265,
 /*  1090 */   106,   84,  265,  265,  265,  265,  166,  265,  164,  163,
 /*  1100 */   162,  265,  124,  265,  106,  265,  265,  265,   89,  265,
 /*  1110 */   166,  265,  164,  163,  162,  265,  265,  265,  265,  124,
 /*  1120 */   265,  106,  265,  265,  265,   88,  265,  166,  265,  164,
 /*  1130 */   163,  162,   87,  265,  265,  265,  124,  265,  106,  265,
 /*  1140 */   265,  265,  265,  124,  166,  106,  164,  163,  162,  265,
 /*  1150 */   265,  166,  265,  164,  163,  162,  265,   86,  265,  265,
 /*  1160 */   265,  265,  265,  265,  265,  265,  265,  265,  124,  265,
 /*  1170 */   106,  265,  265,  265,   81,  265,  166,  265,  164,  163,
 /*  1180 */   162,  265,  265,  265,  265,  124,  265,  106,  265,  265,
 /*  1190 */   265,   80,  265,  166,  265,  164,  163,  162,   91,  265,
 /*  1200 */   265,  265,  124,  265,  106,  265,  265,  265,  265,  124,
 /*  1210 */   166,  106,  164,  163,  162,  265,  265,  166,  265,  164,
 /*  1220 */   163,  162,  265,   90,  265,  265,  265,  265,  265,  265,
 /*  1230 */   265,  265,  265,  265,  124,  265,  106,  265,  265,  265,
 /*  1240 */    83,  265,  166,  265,  164,  163,  162,  265,  265,  265,
 /*  1250 */   265,  124,  265,  106,  265,  265,  265,   82,  265,  166,
 /*  1260 */   265,  164,  163,  162,  101,  265,  265,  265,  124,  265,
 /*  1270 */   106,  265,  265,  265,  265,  124,  166,  106,  164,  163,
 /*  1280 */   162,  265,  265,  166,  265,  164,  163,  162,  265,  100,
 /*  1290 */   265,  265,  265,  265,  265,  265,  265,  265,  265,  265,
 /*  1300 */   124,  265,  106,  265,  265,  265,   71,  265,  166,  265,
 /*  1310 */   164,  163,  162,  265,  265,  265,  265,  124,  265,  106,
 /*  1320 */   265,  265,  265,   70,  265,  166,  265,  164,  163,  162,
 /*  1330 */    67,  265,  265,  265,  124,  265,  106,  265,  265,  265,
 /*  1340 */   265,  124,  166,  106,  164,  163,  162,  265,  265,  166,
 /*  1350 */   265,  164,  163,  162,  265,   66,  265,  265,  265,  265,
 /*  1360 */   265,  265,  265,  265,  265,  265,  124,  265,  106,  265,
 /*  1370 */   265,  265,   64,  265,  166,  265,  164,  163,  162,  265,
 /*  1380 */   265,  265,  265,  124,  265,  106,  265,  265,  265,   61,
 /*  1390 */   265,  166,  265,  164,  163,  162,   63,  265,  265,  265,
 /*  1400 */   124,  265,  106,  265,  265,  265,  265,  124,  166,  106,
 /*  1410 */   164,  163,  162,  265,  265,  166,  265,  164,  163,  162,
 /*  1420 */   265,   75,  265,  265,  265,  265,  265,  265,  265,  265,
 /*  1430 */   265,  265,  124,  265,  106,  265,  265,  265,   74,  265,
 /*  1440 */   166,  265,  164,  163,  162,  265,  265,  265,  265,  124,
 /*  1450 */   265,  106,  265,  265,  265,   62,  265,  166,  265,  164,
 /*  1460 */   163,  162,   60,  265,  265,  265,  124,  265,  106,  265,
 /*  1470 */   265,  265,  265,  124,  166,  106,  164,  163,  162,  265,
 /*  1480 */   265,  166,  265,  164,  163,  162,  265,   59,  265,  265,
 /*  1490 */   265,  265,  265,  265,  265,  265,  265,  265,  124,  265,
 /*  1500 */   106,  265,  265,  265,   72,  265,  166,  265,  164,  163,
 /*  1510 */   162,  265,  265,  265,  265,  124,  265,  106,  265,  265,
 /*  1520 */   265,   69,  265,  166,  265,  164,  163,  162,   65,  265,
 /*  1530 */   265,  265,  124,  265,  106,  265,  265,  265,  265,  124,
 /*  1540 */   166,  106,  164,  163,  162,  265,  265,  166,  265,  164,
 /*  1550 */   163,  162,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     6,   39,    8,    9,   39,   11,   12,   13,   14,   15,
 /*    10 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*    20 */    26,   27,   28,   33,   35,   35,   32,   23,   24,   25,
 /*    30 */    26,   27,   28,   39,   33,   41,   32,   34,    8,   33,
 /*    40 */     6,   35,    8,    9,   36,   11,   12,   13,   14,   15,
 /*    50 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*    60 */    26,   27,   28,   33,   53,   35,   32,   56,   57,   25,
 /*    70 */    26,   27,   28,   39,   28,   41,   32,    1,   32,    3,
 /*    80 */     6,    4,    8,    9,    3,   11,   12,   13,   14,   15,
 /*    90 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*   100 */    26,   27,   28,   64,   33,   33,   32,   35,    1,   33,
 /*   110 */     3,   35,    1,   39,    3,   41,   40,   78,   79,   42,
 /*   120 */     6,   40,    8,    9,    3,   11,   12,   13,   14,   15,
 /*   130 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*   140 */    26,   27,   28,   65,    4,   67,   32,    6,   34,    8,
 /*   150 */     9,   39,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   160 */    19,   20,   21,   22,   23,   24,   25,   26,   27,   28,
 /*   170 */    71,   72,   41,   32,    6,   34,    8,    9,    1,   11,
 /*   180 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   190 */    22,   23,   24,   25,   26,   27,   28,   71,   72,    3,
 /*   200 */    32,    6,   34,    8,    9,    8,   11,   12,   13,   14,
 /*   210 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*   220 */    25,   26,   27,   28,   71,   72,    3,   32,   34,    1,
 /*   230 */     6,   36,    8,    9,    1,   11,   12,   13,   14,   15,
 /*   240 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*   250 */    26,   27,   28,   47,   64,    3,   32,   64,    3,    6,
 /*   260 */    36,    8,    9,   43,   11,   12,   13,   14,   15,   16,
 /*   270 */    17,   18,   19,   20,   21,   22,   23,   24,   25,   26,
 /*   280 */    27,   28,   52,    1,   80,   32,   80,   80,    6,   36,
 /*   290 */     8,    9,   80,   11,   12,   13,   14,   15,   16,   17,
 /*   300 */    18,   19,   20,   21,   22,   23,   24,   25,   26,   27,
 /*   310 */    28,   80,   80,    6,   32,    8,    9,   80,   11,   12,
 /*   320 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   330 */    23,   24,   25,   26,   27,   28,   80,   80,   80,   32,
 /*   340 */    80,   80,    6,   80,    8,    9,   39,   11,   12,   13,
 /*   350 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   360 */    24,   25,   26,   27,   28,   80,   80,   80,   32,   80,
 /*   370 */    80,   80,   80,   80,   80,    6,   40,    8,    9,   80,
 /*   380 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   390 */    21,   22,   23,   24,   25,   26,   27,   28,   80,   80,
 /*   400 */    80,   32,   80,   80,   80,   80,   80,   80,    6,   40,
 /*   410 */     8,    9,   80,   11,   12,   13,   14,   15,   16,   17,
 /*   420 */    18,   19,   20,   21,   22,   23,   24,   25,   26,   27,
 /*   430 */    28,   80,   80,   80,   32,   17,   18,   19,   20,   21,
 /*   440 */    22,   23,   24,   25,   26,   27,   28,   45,   80,    1,
 /*   450 */    32,   80,   80,   80,    6,   80,    8,    9,   80,   11,
 /*   460 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   470 */    22,   23,   24,   25,   26,   27,   28,   80,   80,    6,
 /*   480 */    32,    8,    9,   80,   11,   12,   13,   14,   15,   16,
 /*   490 */    17,   18,   19,   20,   21,   22,   23,   24,   25,   26,
 /*   500 */    27,   28,   80,    8,    9,   32,   11,   12,   13,   14,
 /*   510 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*   520 */    25,   26,   27,   28,   80,   80,   80,   32,   11,   12,
 /*   530 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   540 */    23,   24,   25,   26,   27,   28,   80,   80,   80,   32,
 /*   550 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   560 */    22,   23,   24,   25,   26,   27,   28,   80,   80,   80,
 /*   570 */    32,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   580 */    22,   23,   24,   25,   26,   27,   28,   54,   80,   80,
 /*   590 */    32,   58,   59,   60,   61,   62,   63,   64,   65,   80,
 /*   600 */    67,   68,   69,   70,   80,   80,   73,   80,   75,   76,
 /*   610 */    77,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   620 */    23,   24,   25,   26,   27,   28,   80,   80,    3,   32,
 /*   630 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*   640 */    25,   26,   27,   28,   80,   80,   80,   32,    0,   24,
 /*   650 */    80,    3,   80,   80,   29,   30,   64,   80,   33,    3,
 /*   660 */    35,   21,   22,   23,   24,   25,   26,   27,   28,   80,
 /*   670 */    78,   79,   32,   48,   49,   50,   51,   29,   30,   80,
 /*   680 */    80,   33,    3,   35,   80,   29,   30,   39,   80,   33,
 /*   690 */     3,   35,   36,    1,   46,    3,   48,   49,   50,   51,
 /*   700 */    80,   80,   80,   80,   48,   49,   50,   51,   29,   30,
 /*   710 */    80,   80,   33,    3,   35,   80,   29,   30,   80,   80,
 /*   720 */    33,   34,   35,   44,    3,   33,   80,   48,   49,   50,
 /*   730 */    51,   80,   40,   80,   80,   48,   49,   50,   51,   29,
 /*   740 */    30,   80,   80,   33,   34,   35,   80,    3,   80,   80,
 /*   750 */    29,   30,   80,   80,   33,   34,   35,   80,   48,   49,
 /*   760 */    50,   51,   80,   80,   80,   80,   80,   80,   80,   48,
 /*   770 */    49,   50,   51,   29,   30,    3,   80,   33,   34,   35,
 /*   780 */    80,   80,    3,   80,   80,   80,   80,   80,   80,   80,
 /*   790 */    80,   80,   48,   49,   50,   51,   80,   80,   80,   80,
 /*   800 */    80,   29,   30,   80,   80,   33,   34,   35,   29,   30,
 /*   810 */    80,   80,   33,   34,   35,   80,   80,   80,   80,   80,
 /*   820 */    48,   49,   50,   51,   54,    3,   80,   48,   49,   50,
 /*   830 */    51,   80,   80,   63,   80,   65,   66,   67,   80,   80,
 /*   840 */    80,   80,   80,   73,   74,   75,   76,   77,   80,   80,
 /*   850 */    80,   29,   30,   80,   80,   33,   54,   35,   80,   80,
 /*   860 */    80,   80,   80,   80,   80,   63,   80,   65,   66,   67,
 /*   870 */    48,   49,   50,   51,   80,   73,   80,   75,   76,   77,
 /*   880 */    54,   80,   80,   80,   80,   54,   80,   80,   80,   63,
 /*   890 */    80,   65,   66,   67,   63,   80,   65,   66,   67,   73,
 /*   900 */    54,   75,   76,   77,   73,   80,   75,   76,   77,   63,
 /*   910 */    80,   65,   80,   67,   80,   80,   80,   80,   80,   73,
 /*   920 */    54,   75,   76,   77,   80,   54,   80,   80,   80,   80,
 /*   930 */    80,   65,   80,   67,   80,   80,   65,   80,   67,   73,
 /*   940 */    54,   75,   76,   77,   73,   80,   75,   76,   77,   80,
 /*   950 */    80,   65,   80,   67,   54,   80,   80,   80,   80,   73,
 /*   960 */    80,   75,   76,   77,   80,   65,   80,   67,   54,   80,
 /*   970 */    80,   80,   80,   73,   80,   75,   76,   77,   80,   65,
 /*   980 */    80,   67,   80,   80,   80,   80,   54,   73,   80,   75,
 /*   990 */    76,   77,   80,   54,   80,   80,   80,   65,   80,   67,
 /*  1000 */    80,   80,   80,   80,   65,   73,   67,   75,   76,   77,
 /*  1010 */    80,   80,   73,   80,   75,   76,   77,   54,   80,   80,
 /*  1020 */    80,   80,   54,   80,   80,   80,   80,   80,   65,   80,
 /*  1030 */    67,   80,   80,   65,   80,   67,   73,   80,   75,   76,
 /*  1040 */    77,   73,   54,   75,   76,   77,   80,   80,   80,   80,
 /*  1050 */    80,   80,   80,   65,   80,   67,   80,   80,   80,   54,
 /*  1060 */    80,   73,   80,   75,   76,   77,   80,   80,   80,   80,
 /*  1070 */    65,   80,   67,   80,   80,   80,   80,   54,   73,   80,
 /*  1080 */    75,   76,   77,   80,   80,   80,   80,   80,   65,   80,
 /*  1090 */    67,   54,   80,   80,   80,   80,   73,   80,   75,   76,
 /*  1100 */    77,   80,   65,   80,   67,   80,   80,   80,   54,   80,
 /*  1110 */    73,   80,   75,   76,   77,   80,   80,   80,   80,   65,
 /*  1120 */    80,   67,   80,   80,   80,   54,   80,   73,   80,   75,
 /*  1130 */    76,   77,   54,   80,   80,   80,   65,   80,   67,   80,
 /*  1140 */    80,   80,   80,   65,   73,   67,   75,   76,   77,   80,
 /*  1150 */    80,   73,   80,   75,   76,   77,   80,   54,   80,   80,
 /*  1160 */    80,   80,   80,   80,   80,   80,   80,   80,   65,   80,
 /*  1170 */    67,   80,   80,   80,   54,   80,   73,   80,   75,   76,
 /*  1180 */    77,   80,   80,   80,   80,   65,   80,   67,   80,   80,
 /*  1190 */    80,   54,   80,   73,   80,   75,   76,   77,   54,   80,
 /*  1200 */    80,   80,   65,   80,   67,   80,   80,   80,   80,   65,
 /*  1210 */    73,   67,   75,   76,   77,   80,   80,   73,   80,   75,
 /*  1220 */    76,   77,   80,   54,   80,   80,   80,   80,   80,   80,
 /*  1230 */    80,   80,   80,   80,   65,   80,   67,   80,   80,   80,
 /*  1240 */    54,   80,   73,   80,   75,   76,   77,   80,   80,   80,
 /*  1250 */    80,   65,   80,   67,   80,   80,   80,   54,   80,   73,
 /*  1260 */    80,   75,   76,   77,   54,   80,   80,   80,   65,   80,
 /*  1270 */    67,   80,   80,   80,   80,   65,   73,   67,   75,   76,
 /*  1280 */    77,   80,   80,   73,   80,   75,   76,   77,   80,   54,
 /*  1290 */    80,   80,   80,   80,   80,   80,   80,   80,   80,   80,
 /*  1300 */    65,   80,   67,   80,   80,   80,   54,   80,   73,   80,
 /*  1310 */    75,   76,   77,   80,   80,   80,   80,   65,   80,   67,
 /*  1320 */    80,   80,   80,   54,   80,   73,   80,   75,   76,   77,
 /*  1330 */    54,   80,   80,   80,   65,   80,   67,   80,   80,   80,
 /*  1340 */    80,   65,   73,   67,   75,   76,   77,   80,   80,   73,
 /*  1350 */    80,   75,   76,   77,   80,   54,   80,   80,   80,   80,
 /*  1360 */    80,   80,   80,   80,   80,   80,   65,   80,   67,   80,
 /*  1370 */    80,   80,   54,   80,   73,   80,   75,   76,   77,   80,
 /*  1380 */    80,   80,   80,   65,   80,   67,   80,   80,   80,   54,
 /*  1390 */    80,   73,   80,   75,   76,   77,   54,   80,   80,   80,
 /*  1400 */    65,   80,   67,   80,   80,   80,   80,   65,   73,   67,
 /*  1410 */    75,   76,   77,   80,   80,   73,   80,   75,   76,   77,
 /*  1420 */    80,   54,   80,   80,   80,   80,   80,   80,   80,   80,
 /*  1430 */    80,   80,   65,   80,   67,   80,   80,   80,   54,   80,
 /*  1440 */    73,   80,   75,   76,   77,   80,   80,   80,   80,   65,
 /*  1450 */    80,   67,   80,   80,   80,   54,   80,   73,   80,   75,
 /*  1460 */    76,   77,   54,   80,   80,   80,   65,   80,   67,   80,
 /*  1470 */    80,   80,   80,   65,   73,   67,   75,   76,   77,   80,
 /*  1480 */    80,   73,   80,   75,   76,   77,   80,   54,   80,   80,
 /*  1490 */    80,   80,   80,   80,   80,   80,   80,   80,   65,   80,
 /*  1500 */    67,   80,   80,   80,   54,   80,   73,   80,   75,   76,
 /*  1510 */    77,   80,   80,   80,   80,   65,   80,   67,   80,   80,
 /*  1520 */    80,   54,   80,   73,   80,   75,   76,   77,   54,   80,
 /*  1530 */    80,   80,   65,   80,   67,   80,   80,   80,   80,   65,
 /*  1540 */    73,   67,   75,   76,   77,   80,   80,   73,   80,   75,
 /*  1550 */    76,   77,
};
#define YY_SHIFT_USE_DFLT (-39)
#define YY_SHIFT_COUNT (127)
#define YY_SHIFT_MIN   (-38)
#define YY_SHIFT_MAX   (822)
static const short yy_shift_ofst[] = {
 /*     0 */   230,  648,  822,  779,  772,  744,  822,  721,  710,  687,
 /*    10 */   822,  679,  656,  625,  822,  822,  822,  822,  822,  822,
 /*    20 */   822,  822,  822,  822,  822,  822,  822,  822,  822,  822,
 /*    30 */   822,  822,  822,  822,  822,  822,  822,  822,  822,  822,
 /*    40 */   822,  822,  822,  822,  822,  822,  822,  822,  822,  822,
 /*    50 */   822,   76,  692,  220,  220,  220,  255,   81,  252,   74,
 /*    60 */    34,   -6,  448,  402,  369,  336,  307,  282,  253,  224,
 /*    70 */   195,  168,  141,  114,  473,  473,  473,  495,  517,  517,
 /*    80 */   538,  558,  597,  615,  418,  418,  640,  640,  640,  640,
 /*    90 */     4,    4,   44,   44,   30,   77,  111,  107,   72,  -10,
 /*   100 */    46,   46,   46,   46,   46,   46,    6,  -10,  206,  233,
 /*   110 */   228,  194,  223,  197,  196,  177,  131,  112,  140,  121,
 /*   120 */     3,   71,    8,    1,  -11,  -11,  -35,  -38,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (58)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (1474)
static const short yy_reduce_ofst[] = {
 /*     0 */    11,  533,  770,  826,  831,  826,  802,  846,  846,  846,
 /*    10 */   846, 1474, 1467, 1450, 1433, 1408, 1401, 1384, 1367, 1342,
 /*    20 */  1335, 1318, 1301, 1276, 1269, 1252, 1235, 1210, 1203, 1186,
 /*    30 */  1169, 1144, 1137, 1120, 1103, 1078, 1071, 1054, 1037, 1023,
 /*    40 */  1005,  988,  968,  963,  939,  932,  914,  900,  886,  871,
 /*    50 */   866,  592,   39,  153,  126,   99,   78,  193,  190,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   178,  263,  218,  263,  263,  263,  263,  263,  263,  263,
 /*    10 */   219,  263,  263,  263,  263,  263,  263,  263,  263,  263,
 /*    20 */   263,  263,  263,  263,  263,  263,  263,  263,  263,  263,
 /*    30 */   263,  263,  263,  263,  263,  263,  263,  263,  263,  263,
 /*    40 */   263,  263,  263,  263,  263,  263,  263,  263,  263,  263,
 /*    50 */   263,  189,  263,  263,  200,  263,  263,  263,  263,  263,
 /*    60 */   263,  263,  263,  263,  263,  212,  263,  263,  263,  263,
 /*    70 */   263,  263,  263,  263,  231,  230,  186,  233,  235,  234,
 /*    80 */   249,  248,  256,  255,  243,  242,  247,  246,  245,  244,
 /*    90 */   254,  253,  237,  236,  189,  263,  263,  263,  263,  191,
 /*   100 */   252,  250,  241,  240,  239,  238,  260,  189,  263,  263,
 /*   110 */   263,  263,  263,  263,  263,  263,  263,  263,  263,  228,
 /*   120 */   263,  263,  263,  263,  197,  190,  263,  263,  262,  261,
 /*   130 */   211,  203,  205,  202,  201,  204,  198,  232,  229,  210,
 /*   140 */   213,  209,  208,  206,  188,  207,  199,  187,  187,  257,
 /*   150 */   193,  258,  195,  259,  196,  217,  251,  227,  226,  225,
 /*   160 */   224,  223,  222,  221,  220,  214,  216,  215,  194,  192,
 /*   170 */   185,  184,  183,  182,  181,  180,  179,
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
  "$",             "ASSIGN",        "COLON",         "NAME",        
  "BITOR",         "FUNCTION_DEC",  "COMPOSITION",   "FUNCTION_CALL",
  "PREPEND",       "APPEND",        "INDEX",         "OR",          
  "AND",           "BITXOR",        "BITAND",        "EQUALTO",     
  "NOTEQUALTO",    "GREATERTHAN",   "GORE",          "LESSTHAN",    
  "LORE",          "SHIFTL",        "SHIFTR",        "PLUS",        
  "MINUS",         "DIVIDE",        "TIMES",         "MODULO",      
  "POW",           "NOT",           "BITNOT",        "UMINUS",      
  "PLUSPLUS",      "LPAREN",        "RPAREN",        "LBRAC",       
  "RBRAC",         "COMMA",         "COLLECTARRAY",  "DELIMITER",   
  "LCURL",         "RCURL",         "WILDCARD",      "WHERE",       
  "CASE",          "OF",            "LET",           "IN",          
  "PRINT",         "NUM",           "STRING",        "BOOLEAN",     
  "OPENQUOTEERROR",  "error",         "expr",          "id",          
  "main",          "in",            "start",         "test",        
  "spec",          "assignment",    "top_stmt",      "stmt",        
  "name_chain",    "function_call",  "stmt_list",     "array_index", 
  "case_statement",  "guard_statement",  "final_guard_statement",  "final_where_statement",
  "where_statement",  "array",         "maybe_empty_stmt_list",  "num",         
  "string",        "bool",          "maybe_empty_name_chain",  "pattern",     
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
 /*  51 */ "maybe_empty_name_chain ::= name_chain",
 /*  52 */ "maybe_empty_name_chain ::= pattern",
 /*  53 */ "assignment ::= name_chain maybe_empty_name_chain ASSIGN expr",
 /*  54 */ "assignment ::= NAME maybe_empty_name_chain ASSIGN expr",
 /*  55 */ "pattern ::= LPAREN NAME PREPEND NAME RPAREN",
 /*  56 */ "expr ::= expr PREPEND expr",
 /*  57 */ "expr ::= expr APPEND expr",
 /*  58 */ "expr ::= expr PLUSPLUS expr",
 /*  59 */ "expr ::= expr PLUS expr",
 /*  60 */ "expr ::= expr MINUS expr",
 /*  61 */ "expr ::= expr DIVIDE expr",
 /*  62 */ "expr ::= expr TIMES expr",
 /*  63 */ "expr ::= expr MODULO expr",
 /*  64 */ "expr ::= expr POW expr",
 /*  65 */ "expr ::= expr EQUALTO expr",
 /*  66 */ "expr ::= expr NOTEQUALTO expr",
 /*  67 */ "expr ::= expr LESSTHAN expr",
 /*  68 */ "expr ::= expr GREATERTHAN expr",
 /*  69 */ "expr ::= expr LORE expr",
 /*  70 */ "expr ::= expr GORE expr",
 /*  71 */ "expr ::= expr AND expr",
 /*  72 */ "expr ::= expr OR expr",
 /*  73 */ "expr ::= BITNOT expr",
 /*  74 */ "expr ::= LPAREN MINUS expr RPAREN",
 /*  75 */ "expr ::= NOT expr",
 /*  76 */ "expr ::= expr SHIFTL expr",
 /*  77 */ "expr ::= expr SHIFTR expr",
 /*  78 */ "expr ::= expr BITAND expr",
 /*  79 */ "expr ::= expr BITXOR expr",
 /*  80 */ "array_index ::= function_call LBRAC expr RBRAC",
 /*  81 */ "array_index ::= NAME LBRAC expr RBRAC",
 /*  82 */ "array_index ::= array_index LBRAC expr RBRAC",
 /*  83 */ "expr ::= array_index",
 /*  84 */ "in ::= error",
 /*  85 */ "error ::= OPENQUOTEERROR",
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
    case 2: /* COLON */
    case 3: /* NAME */
    case 4: /* BITOR */
    case 5: /* FUNCTION_DEC */
    case 6: /* COMPOSITION */
    case 7: /* FUNCTION_CALL */
    case 8: /* PREPEND */
    case 9: /* APPEND */
    case 10: /* INDEX */
    case 11: /* OR */
    case 12: /* AND */
    case 13: /* BITXOR */
    case 14: /* BITAND */
    case 15: /* EQUALTO */
    case 16: /* NOTEQUALTO */
    case 17: /* GREATERTHAN */
    case 18: /* GORE */
    case 19: /* LESSTHAN */
    case 20: /* LORE */
    case 21: /* SHIFTL */
    case 22: /* SHIFTR */
    case 23: /* PLUS */
    case 24: /* MINUS */
    case 25: /* DIVIDE */
    case 26: /* TIMES */
    case 27: /* MODULO */
    case 28: /* POW */
    case 29: /* NOT */
    case 30: /* BITNOT */
    case 31: /* UMINUS */
    case 32: /* PLUSPLUS */
    case 33: /* LPAREN */
    case 34: /* RPAREN */
    case 35: /* LBRAC */
    case 36: /* RBRAC */
    case 37: /* COMMA */
    case 38: /* COLLECTARRAY */
    case 39: /* DELIMITER */
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
#line 888 "./src/Grammar/grammar.c"
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
  { 78, 1 },
  { 78, 1 },
  { 61, 4 },
  { 61, 4 },
  { 79, 5 },
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
#line 89 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1273 "./src/Grammar/grammar.c"
        break;
      case 5: /* start ::= spec */
#line 95 "./src/Grammar/grammar.y"
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
#line 1291 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= assignment */
      case 21: /* test ::= case_statement */ yytestcase(yyruleno==21);
#line 111 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1299 "./src/Grammar/grammar.c"
        break;
      case 7: /* spec ::= top_stmt */
      case 8: /* top_stmt ::= stmt */ yytestcase(yyruleno==8);
#line 116 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1308 "./src/Grammar/grammar.c"
        break;
      case 9: /* stmt ::= expr */
      case 37: /* stmt_list ::= stmt */ yytestcase(yyruleno==37);
#line 128 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1317 "./src/Grammar/grammar.c"
        break;
      case 10: /* name_chain ::= name_chain NAME */
#line 134 "./src/Grammar/grammar.y"
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
#line 1356 "./src/Grammar/grammar.c"
        break;
      case 11: /* name_chain ::= NAME */
#line 171 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1365 "./src/Grammar/grammar.c"
        break;
      case 12: /* expr ::= NAME */
#line 178 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0.data.string = new optic::String(yymsp[0].minor.yy0.data.string->c_str());
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1378 "./src/Grammar/grammar.c"
        break;
      case 13: /* expr ::= expr COMPOSITION function_call */
#line 194 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1399 "./src/Grammar/grammar.c"
        break;
      case 14: /* expr ::= expr COMPOSITION NAME */
#line 212 "./src/Grammar/grammar.y"
{
    optic::object function_body;
    function_body.type = optic::FUNCTION_ARG_VALUES;
    function_body.data.array = new optic::Array();
    function_body.data.array->push_back(yymsp[-2].minor.yy0);
    yymsp[0].minor.yy0.type = optic::STRING;
    optic::store_operations(yygotominor.yy0,yymsp[0].minor.yy0,function_body,optic::call_function);
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1412 "./src/Grammar/grammar.c"
        break;
      case 15: /* function_call ::= NAME LPAREN stmt_list RPAREN */
#line 222 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,33,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1441 "./src/Grammar/grammar.c"
        break;
      case 16: /* function_call ::= NAME LBRAC RBRAC LPAREN stmt_list RPAREN */
#line 247 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,35,&yymsp[-4].minor);
  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,33,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1473 "./src/Grammar/grammar.c"
        break;
      case 17: /* expr ::= array_index LPAREN stmt_list RPAREN */
#line 273 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,33,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1499 "./src/Grammar/grammar.c"
        break;
      case 18: /* function_call ::= NAME LPAREN RPAREN */
#line 296 "./src/Grammar/grammar.y"
{
    yymsp[-2].minor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,33,&yymsp[-1].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1514 "./src/Grammar/grammar.c"
        break;
      case 19: /* function_call ::= array_index LPAREN RPAREN */
#line 307 "./src/Grammar/grammar.y"
{
/*    yymsp[-2].minor.yy0.type = optic::UNDECLARED_VARIABLE;*/
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,33,&yymsp[-1].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1529 "./src/Grammar/grammar.c"
        break;
      case 20: /* expr ::= function_call */
      case 39: /* expr ::= array */ yytestcase(yyruleno==39);
      case 83: /* expr ::= array_index */ yytestcase(yyruleno==83);
#line 318 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1538 "./src/Grammar/grammar.c"
        break;
      case 22: /* guard_statement ::= name_chain LCURL BITOR expr ASSIGN expr DELIMITER */
#line 330 "./src/Grammar/grammar.y"
{
    optic::object tree = create_condition_tree(yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0 = create_guard(yymsp[-6].minor.yy0,tree);
  yy_destructor(yypParser,40,&yymsp[-5].minor);
  yy_destructor(yypParser,4,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1550 "./src/Grammar/grammar.c"
        break;
      case 23: /* guard_statement ::= guard_statement BITOR expr ASSIGN expr DELIMITER */
#line 336 "./src/Grammar/grammar.y"
{
    add_branch_to_tree(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-5].minor.yy0;
  yy_destructor(yypParser,4,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1561 "./src/Grammar/grammar.c"
        break;
      case 24: /* final_guard_statement ::= guard_statement BITOR expr ASSIGN expr RCURL */
#line 342 "./src/Grammar/grammar.y"
{
    add_branch_to_tree(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-5].minor.yy0;
  yy_destructor(yypParser,4,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1572 "./src/Grammar/grammar.c"
        break;
      case 25: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr RCURL */
#line 348 "./src/Grammar/grammar.y"
{
    add_wildcard_to_tree(yymsp[-4].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-4].minor.yy0;
  yy_destructor(yypParser,42,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1583 "./src/Grammar/grammar.c"
        break;
      case 26: /* assignment ::= final_guard_statement */
#line 354 "./src/Grammar/grammar.y"
{
    panopticon::object& b = yymsp[0].minor.yy0.data.array->at(0);
    panopticon::object& c = yymsp[0].minor.yy0.data.array->at(1);

    panopticon::object resolve;
    panopticon::store_operations(resolve, c, &panopticon::resolve_guard,false);

    resolve.type = panopticon::FUNCTION_BODY;
/*    insure_ready_for_assignment(b,resolve);*/
    b.type = optic::FUNCTION_ARG_NAMES;
    panopticon::parse_operations(yygotominor.yy0, b, resolve, &panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1604 "./src/Grammar/grammar.c"
        break;
      case 27: /* assignment ::= guard_statement BITOR expr ASSIGN expr DELIMITER final_where_statement */
#line 373 "./src/Grammar/grammar.y"
{
    add_branch_to_tree(yymsp[-6].minor.yy0,yymsp[-4].minor.yy0,yymsp[-2].minor.yy0);
    panopticon::object& b = yymsp[-6].minor.yy0.data.array->at(0);
    panopticon::object& func_body = yymsp[-6].minor.yy0.data.array->at(1);
    panopticon::object resolve;
    panopticon::store_operations(resolve, func_body, &panopticon::resolve_guard,false);
    optic::object combined;
    panopticon::store_operations(combined,yymsp[0].minor.yy0,resolve,false);
    insure_ready_for_assignment(b,combined);
    panopticon::parse_operations(yygotominor.yy0, b, combined, &panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,4,&yymsp[-5].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,39,&yymsp[-1].minor);
}
#line 1627 "./src/Grammar/grammar.c"
        break;
      case 28: /* assignment ::= guard_statement WILDCARD ASSIGN expr DELIMITER final_where_statement */
#line 391 "./src/Grammar/grammar.y"
{
    add_wildcard_to_tree(yymsp[-5].minor.yy0,yymsp[-2].minor.yy0);
    panopticon::object& b = yymsp[-5].minor.yy0.data.array->at(0);
    panopticon::object& func_body = yymsp[-5].minor.yy0.data.array->at(1);
    panopticon::object resolve;
    panopticon::store_operations(resolve, func_body, &panopticon::resolve_guard,false);
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
  yy_destructor(yypParser,39,&yymsp[-1].minor);
}
#line 1650 "./src/Grammar/grammar.c"
        break;
      case 29: /* where_statement ::= WHERE LCURL */
#line 413 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::NIL;
  yy_destructor(yypParser,43,&yymsp[-1].minor);
  yy_destructor(yypParser,40,&yymsp[0].minor);
}
#line 1659 "./src/Grammar/grammar.c"
        break;
      case 30: /* where_statement ::= WHERE name_chain ASSIGN expr LCURL */
#line 418 "./src/Grammar/grammar.y"
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
#line 1676 "./src/Grammar/grammar.c"
        break;
      case 31: /* where_statement ::= where_statement name_chain ASSIGN expr DELIMITER */
#line 430 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1702 "./src/Grammar/grammar.c"
        break;
      case 32: /* final_where_statement ::= where_statement name_chain ASSIGN expr RCURL DELIMITER RCURL */
#line 452 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,39,&yymsp[-1].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1729 "./src/Grammar/grammar.c"
        break;
      case 33: /* case_statement ::= name_chain ASSIGN CASE expr OF */
#line 473 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,44,&yymsp[-2].minor);
  yy_destructor(yypParser,45,&yymsp[0].minor);
}
#line 1740 "./src/Grammar/grammar.c"
        break;
      case 34: /* test ::= LET IN */
#line 478 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,46,&yymsp[-1].minor);
  yy_destructor(yypParser,47,&yymsp[0].minor);
}
#line 1748 "./src/Grammar/grammar.c"
        break;
      case 35: /* assignment ::= name_chain ASSIGN expr */
#line 487 "./src/Grammar/grammar.y"
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
#line 1763 "./src/Grammar/grammar.c"
        break;
      case 36: /* assignment ::= name_chain ASSIGN expr LCURL final_where_statement */
#line 500 "./src/Grammar/grammar.y"
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
#line 1780 "./src/Grammar/grammar.c"
        break;
      case 38: /* stmt_list ::= stmt_list stmt */
#line 550 "./src/Grammar/grammar.y"
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
#line 1798 "./src/Grammar/grammar.c"
        break;
      case 40: /* array ::= LBRAC maybe_empty_stmt_list RBRAC */
#line 571 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yygotominor.yy0.type = optic::ARRAY;
  yy_destructor(yypParser,35,&yymsp[-2].minor);
  yy_destructor(yypParser,36,&yymsp[0].minor);
}
#line 1808 "./src/Grammar/grammar.c"
        break;
      case 41: /* maybe_empty_stmt_list ::= */
#line 577 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1816 "./src/Grammar/grammar.c"
        break;
      case 42: /* maybe_empty_stmt_list ::= stmt_list */
#line 583 "./src/Grammar/grammar.y"
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
#line 1832 "./src/Grammar/grammar.c"
        break;
      case 43: /* expr ::= num */
      case 45: /* expr ::= bool */ yytestcase(yyruleno==45);
#line 601 "./src/Grammar/grammar.y"
{
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1840 "./src/Grammar/grammar.c"
        break;
      case 44: /* expr ::= string */
#line 606 "./src/Grammar/grammar.y"
{
   create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1847 "./src/Grammar/grammar.c"
        break;
      case 46: /* expr ::= PRINT LPAREN expr RPAREN */
#line 620 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-1].minor.yy0,&optic::unary_print_object,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,48,&yymsp[-3].minor);
  yy_destructor(yypParser,33,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1862 "./src/Grammar/grammar.c"
        break;
      case 47: /* expr ::= LPAREN expr RPAREN */
#line 630 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
  yy_destructor(yypParser,33,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1871 "./src/Grammar/grammar.c"
        break;
      case 48: /* num ::= NUM */
#line 635 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1879 "./src/Grammar/grammar.c"
        break;
      case 49: /* string ::= STRING */
#line 641 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::STRING;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1887 "./src/Grammar/grammar.c"
        break;
      case 50: /* bool ::= BOOLEAN */
#line 648 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::BOOL;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1895 "./src/Grammar/grammar.c"
        break;
      case 51: /* maybe_empty_name_chain ::= name_chain */
#line 659 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::ARRAY;
    yygotominor.yy0.data.array = new optic::Array();
    yymsp[0].minor.yy0.type = optic::STRING;
    yygotominor.yy0.data.array->push_back(yymsp[0].minor.yy0);
}
#line 1905 "./src/Grammar/grammar.c"
        break;
      case 52: /* maybe_empty_name_chain ::= pattern */
#line 666 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::ARRAY;
    yygotominor.yy0.data.array = new optic::Array();
    yygotominor.yy0.data.array->push_back(yymsp[0].minor.yy0);
}
#line 1914 "./src/Grammar/grammar.c"
        break;
      case 53: /* assignment ::= name_chain maybe_empty_name_chain ASSIGN expr */
      case 54: /* assignment ::= NAME maybe_empty_name_chain ASSIGN expr */ yytestcase(yyruleno==54);
#line 683 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1923 "./src/Grammar/grammar.c"
        break;
      case 55: /* pattern ::= LPAREN NAME PREPEND NAME RPAREN */
#line 693 "./src/Grammar/grammar.y"
{
/*    std::cout << "PATTERN_ARGUMENT" << std::endl;*/
    yymsp[-3].minor.yy0.type = optic::PATTERN;
    yymsp[-1].minor.yy0.type = optic::PATTERN;
    yygotominor.yy0.type = optic::PATTERN;
    yygotominor.yy0.data.string = new optic::String("PATTERN ARGUMENT!");
  yy_destructor(yypParser,33,&yymsp[-4].minor);
  yy_destructor(yypParser,8,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1937 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr PREPEND expr */
#line 702 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&optic::prepend,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1950 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr APPEND expr */
#line 712 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&optic::append,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1963 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= expr PLUSPLUS expr */
#line 722 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&optic::concat,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,32,&yymsp[-1].minor);
}
#line 1976 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= expr PLUS expr */
#line 732 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::plus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1989 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= expr MINUS expr */
#line 742 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 2002 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= expr DIVIDE expr */
#line 752 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,25,&yymsp[-1].minor);
}
#line 2015 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= expr TIMES expr */
#line 762 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,26,&yymsp[-1].minor);
}
#line 2028 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= expr MODULO expr */
#line 772 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,27,&yymsp[-1].minor);
}
#line 2041 "./src/Grammar/grammar.c"
        break;
      case 64: /* expr ::= expr POW expr */
#line 782 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,28,&yymsp[-1].minor);
}
#line 2054 "./src/Grammar/grammar.c"
        break;
      case 65: /* expr ::= expr EQUALTO expr */
#line 792 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 2067 "./src/Grammar/grammar.c"
        break;
      case 66: /* expr ::= expr NOTEQUALTO expr */
#line 802 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 2080 "./src/Grammar/grammar.c"
        break;
      case 67: /* expr ::= expr LESSTHAN expr */
#line 812 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 2093 "./src/Grammar/grammar.c"
        break;
      case 68: /* expr ::= expr GREATERTHAN expr */
#line 822 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 2106 "./src/Grammar/grammar.c"
        break;
      case 69: /* expr ::= expr LORE expr */
#line 832 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 2119 "./src/Grammar/grammar.c"
        break;
      case 70: /* expr ::= expr GORE expr */
#line 842 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 2132 "./src/Grammar/grammar.c"
        break;
      case 71: /* expr ::= expr AND expr */
#line 852 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 2145 "./src/Grammar/grammar.c"
        break;
      case 72: /* expr ::= expr OR expr */
#line 862 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 2158 "./src/Grammar/grammar.c"
        break;
      case 73: /* expr ::= BITNOT expr */
#line 872 "./src/Grammar/grammar.y"
{
    store_operations(yygotominor.yy0,yymsp[0].minor.yy0,&optic::bit_not);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,30,&yymsp[-1].minor);
}
#line 2171 "./src/Grammar/grammar.c"
        break;
      case 74: /* expr ::= LPAREN MINUS expr RPAREN */
#line 882 "./src/Grammar/grammar.y"
{
    store_operations(yygotominor.yy0,yymsp[-1].minor.yy0,&panopticon::u_minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,33,&yymsp[-3].minor);
  yy_destructor(yypParser,24,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 2186 "./src/Grammar/grammar.c"
        break;
      case 75: /* expr ::= NOT expr */
#line 892 "./src/Grammar/grammar.y"
{
    store_operations(yygotominor.yy0,yymsp[0].minor.yy0,&panopticon::not_value);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,29,&yymsp[-1].minor);
}
#line 2199 "./src/Grammar/grammar.c"
        break;
      case 76: /* expr ::= expr SHIFTL expr */
#line 902 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 2212 "./src/Grammar/grammar.c"
        break;
      case 77: /* expr ::= expr SHIFTR expr */
#line 912 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 2225 "./src/Grammar/grammar.c"
        break;
      case 78: /* expr ::= expr BITAND expr */
#line 922 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 2238 "./src/Grammar/grammar.c"
        break;
      case 79: /* expr ::= expr BITXOR expr */
#line 932 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 2251 "./src/Grammar/grammar.c"
        break;
      case 80: /* array_index ::= function_call LBRAC expr RBRAC */
      case 82: /* array_index ::= array_index LBRAC expr RBRAC */ yytestcase(yyruleno==82);
#line 942 "./src/Grammar/grammar.y"
{
    optic::store_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,35,&yymsp[-2].minor);
  yy_destructor(yypParser,36,&yymsp[0].minor);
}
#line 2266 "./src/Grammar/grammar.c"
        break;
      case 81: /* array_index ::= NAME LBRAC expr RBRAC */
#line 952 "./src/Grammar/grammar.y"
{
    yymsp[-3].minor.yy0.type = optic::STRING;
    optic::store_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,&optic::index,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,35,&yymsp[-2].minor);
  yy_destructor(yypParser,36,&yymsp[0].minor);
}
#line 2281 "./src/Grammar/grammar.c"
        break;
      case 84: /* in ::= error */
#line 982 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy161)
    {
    case panopticon::OpenQuoteError:
/*        panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        panopticon::out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 2296 "./src/Grammar/grammar.c"
        break;
      case 85: /* error ::= OPENQUOTEERROR */
#line 995 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy161 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 2305 "./src/Grammar/grammar.c"
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
#line 83 "./src/Grammar/grammar.y"

panopticon::out() << "Syntax error!" << std::endl;
#line 2372 "./src/Grammar/grammar.c"
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
#line 78 "./src/Grammar/grammar.y"

printf("parsing complete!\n\n\n");
#line 2394 "./src/Grammar/grammar.c"
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
