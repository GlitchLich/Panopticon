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
#define YYACTIONTYPE unsigned short int
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
#define YYNSTATE 168
#define YYNRULE 84
#define YYERRORSYMBOL 50
#define YYERRSYMDT yy155
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
#define YY_ACTTAB_COUNT (1420)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    29,   30,   25,   26,   36,   35,   33,   31,   34,   32,
 /*    10 */    28,   27,   44,   42,   40,   39,   38,   37,   44,   42,
 /*    20 */    40,   39,   38,   37,   54,  116,  112,   46,   14,  130,
 /*    30 */   128,   52,  102,   46,   29,   30,   25,   26,   36,   35,
 /*    40 */    33,   31,   34,   32,   28,   27,   44,   42,   40,   39,
 /*    50 */    38,   37,  132,  131,   40,   39,   38,   37,   10,  125,
 /*    60 */    52,   46,  166,   49,  165,  100,  124,   46,   29,   30,
 /*    70 */    25,   26,   36,   35,   33,   31,   34,   32,   28,   27,
 /*    80 */    44,   42,   40,   39,   38,   37,    3,   45,   20,  107,
 /*    90 */   145,   16,   43,  137,  108,   46,   15,   48,  122,   52,
 /*   100 */   123,   21,   29,   30,   25,   26,   36,   35,   33,   31,
 /*   110 */    34,   32,   28,   27,   44,   42,   40,   39,   38,   37,
 /*   120 */   120,  144,  107,  253,    1,  150,  137,  107,  138,   46,
 /*   130 */     5,  137,   29,   30,   25,   26,   36,   35,   33,   31,
 /*   140 */    34,   32,   28,   27,   44,   42,   40,   39,   38,   37,
 /*   150 */    37,   46,   19,  106,  104,  149,  105,  133,  103,   46,
 /*   160 */    46,  129,   29,   30,   25,   26,   36,   35,   33,   31,
 /*   170 */    34,   32,   28,   27,   44,   42,   40,   39,   38,   37,
 /*   180 */   101,   12,  121,  202,  113,  110,  147,  142,  132,   46,
 /*   190 */   119,  179,   87,   88,   29,   30,   25,   26,   36,   35,
 /*   200 */    33,   31,   34,   32,   28,   27,   44,   42,   40,   39,
 /*   210 */    38,   37,   51,  254,  254,  254,  254,  254,    4,  139,
 /*   220 */    11,   46,  179,   18,  254,  254,  179,  179,   29,   30,
 /*   230 */    25,   26,   36,   35,   33,   31,   34,   32,   28,   27,
 /*   240 */    44,   42,   40,   39,   38,   37,  254,  254,  254,  254,
 /*   250 */   254,  254,  254,  254,  254,   46,  254,  254,  254,  254,
 /*   260 */   254,  254,   29,   30,   25,   26,   36,   35,   33,   31,
 /*   270 */    34,   32,   28,   27,   44,   42,   40,   39,   38,   37,
 /*   280 */   254,  254,  254,  254,  254,  254,  254,  254,  254,   46,
 /*   290 */   254,  136,  254,  254,  254,  254,   29,   30,   25,   26,
 /*   300 */    36,   35,   33,   31,   34,   32,   28,   27,   44,   42,
 /*   310 */    40,   39,   38,   37,   28,   27,   44,   42,   40,   39,
 /*   320 */    38,   37,  254,   46,  254,  254,  254,  254,  254,  254,
 /*   330 */   254,   46,  135,  254,  254,  254,  254,  254,  254,   29,
 /*   340 */    30,   25,   26,   36,   35,   33,   31,   34,   32,   28,
 /*   350 */    27,   44,   42,   40,   39,   38,   37,  254,  254,  254,
 /*   360 */   254,  254,  254,  254,  254,  254,   46,  254,  254,  254,
 /*   370 */    50,  254,  254,   29,   30,   25,   26,   36,   35,   33,
 /*   380 */    31,   34,   32,   28,   27,   44,   42,   40,   39,   38,
 /*   390 */    37,  254,  254,  254,  254,  254,  254,  254,  254,  254,
 /*   400 */    46,  254,   13,  254,  134,  254,  254,   29,   30,   25,
 /*   410 */    26,   36,   35,   33,   31,   34,   32,   28,   27,   44,
 /*   420 */    42,   40,   39,   38,   37,  254,  254,  254,  254,  254,
 /*   430 */   254,  254,  254,  254,   46,  254,  254,  254,  254,  254,
 /*   440 */   254,   29,   30,   25,   26,   36,   35,   33,   31,   34,
 /*   450 */    32,   28,   27,   44,   42,   40,   39,   38,   37,  254,
 /*   460 */   254,  254,   29,   30,   25,   26,   36,   35,   46,   31,
 /*   470 */    34,   32,   28,   27,   44,   42,   40,   39,   38,   37,
 /*   480 */   254,  254,  254,  254,  254,  254,  254,  254,  254,   46,
 /*   490 */   254,  254,  254,  254,  254,  254,  254,   30,   25,   26,
 /*   500 */    36,   35,   33,   31,   34,   32,   28,   27,   44,   42,
 /*   510 */    40,   39,   38,   37,  254,  254,  254,  254,  254,  254,
 /*   520 */   254,  254,  254,   46,  254,  254,  254,  254,  254,  254,
 /*   530 */   254,  254,   25,   26,   36,   35,   33,   31,   34,   32,
 /*   540 */    28,   27,   44,   42,   40,   39,   38,   37,  254,  254,
 /*   550 */   254,  254,  254,  254,   68,  254,  254,   46,  118,  117,
 /*   560 */   164,  163,  162,  161,   86,  254,   97,  127,  126,   89,
 /*   570 */   254,  254,   98,  254,  152,  254,  156,  254,  153,  151,
 /*   580 */   254,  254,   26,   36,   35,   33,   31,   34,   32,   28,
 /*   590 */    27,   44,   42,   40,   39,   38,   37,  254,  254,  254,
 /*   600 */   254,  254,  254,  254,  254,  254,   46,   36,   35,   33,
 /*   610 */    31,   34,   32,   28,   27,   44,   42,   40,   39,   38,
 /*   620 */    37,  168,  254,  254,  254,  254,  254,  254,   47,  254,
 /*   630 */    46,  254,  254,   23,  254,   47,  254,  254,   22,   24,
 /*   640 */    23,  254,   41,  254,    2,   22,   24,  254,  254,   41,
 /*   650 */   160,    2,  254,  254,  254,   17,  167,   83,  254,  115,
 /*   660 */   148,  147,  146,  254,   99,  254,  115,  148,  147,  146,
 /*   670 */    33,   31,   34,   32,   28,   27,   44,   42,   40,   39,
 /*   680 */    38,   37,   47,  254,  254,  254,  254,   23,  254,  254,
 /*   690 */   254,   46,   22,   24,  254,   47,   41,  254,    2,  111,
 /*   700 */    23,  254,  254,  254,  160,   22,   24,  254,  254,   41,
 /*   710 */   159,    2,  254,  115,  148,  147,  146,  160,  254,  254,
 /*   720 */    47,  254,  254,  254,  254,   23,  115,  148,  147,  146,
 /*   730 */    22,   24,  254,  254,   41,  158,    2,  254,  254,  254,
 /*   740 */   254,  254,  160,  254,  254,   47,  254,  254,  254,  254,
 /*   750 */    23,  115,  148,  147,  146,   22,   24,  254,  254,   41,
 /*   760 */   140,    2,  254,  254,  254,  254,  254,  160,  254,  254,
 /*   770 */    47,  254,  254,  254,  254,   23,  115,  148,  147,  146,
 /*   780 */    22,   24,  254,  254,   41,  141,    2,  254,  254,  254,
 /*   790 */   254,  254,  160,  254,  254,   47,  254,  254,  254,  254,
 /*   800 */    23,  115,  148,  147,  146,   22,   24,  254,  254,   41,
 /*   810 */   143,    2,  254,  254,  254,  254,  254,  160,  254,  254,
 /*   820 */    47,  254,  254,  254,  254,   23,  115,  148,  147,  146,
 /*   830 */    22,   24,  254,  254,   41,  254,    2,   68,  254,  254,
 /*   840 */   254,  254,  160,  254,  254,  254,  155,  254,    9,   97,
 /*   850 */   254,  115,  148,  147,  146,  157,   68,  152,  254,  156,
 /*   860 */   114,  153,  151,  254,  254,  155,  254,    6,   97,  254,
 /*   870 */   254,  254,  254,  254,  157,  254,  152,   68,  156,  254,
 /*   880 */   153,  151,  254,  254,  254,  254,  155,  254,    8,   97,
 /*   890 */   254,  254,  254,  254,   68,  157,  254,  152,  254,  156,
 /*   900 */   254,  153,  151,  155,  254,    7,   97,  254,   68,  254,
 /*   910 */   254,  254,  157,  254,  152,  254,  156,  154,  153,  151,
 /*   920 */    97,  254,  254,  254,  254,  254,  157,  254,  152,  109,
 /*   930 */   156,  254,  153,  151,  254,  254,  254,  254,   71,  254,
 /*   940 */   254,   97,  254,  254,  254,  254,  254,  157,  254,  152,
 /*   950 */    97,  156,  254,  153,  151,   84,  157,  254,  152,  254,
 /*   960 */   156,  254,  153,  151,   67,  254,  254,   97,  254,  254,
 /*   970 */   254,  254,  254,  157,  254,  152,   97,  156,   85,  153,
 /*   980 */   151,  254,  157,  254,  152,  254,  156,  254,  153,  151,
 /*   990 */    97,  254,  254,   66,  254,  254,  157,  254,  152,  254,
 /*  1000 */   156,  254,  153,  151,  254,   97,  254,   96,  254,  254,
 /*  1010 */   254,  157,  254,  152,  254,  156,   95,  153,  151,   97,
 /*  1020 */   254,  254,  254,  254,  254,  157,  254,  152,   97,  156,
 /*  1030 */    94,  153,  151,  254,  157,  254,  152,  254,  156,  254,
 /*  1040 */   153,  151,   97,  254,  254,   93,  254,  254,  157,  254,
 /*  1050 */   152,  254,  156,  254,  153,  151,  254,   97,  254,   76,
 /*  1060 */   254,  254,  254,  157,  254,  152,  254,  156,   75,  153,
 /*  1070 */   151,   97,  254,  254,  254,  254,  254,  157,  254,  152,
 /*  1080 */    97,  156,   80,  153,  151,  254,  157,  254,  152,  254,
 /*  1090 */   156,  254,  153,  151,   97,  254,  254,   79,  254,  254,
 /*  1100 */   157,  254,  152,  254,  156,  254,  153,  151,  254,   97,
 /*  1110 */   254,   78,  254,  254,  254,  157,  254,  152,  254,  156,
 /*  1120 */    77,  153,  151,   97,  254,  254,  254,  254,  254,  157,
 /*  1130 */   254,  152,   97,  156,   72,  153,  151,  254,  157,  254,
 /*  1140 */   152,  254,  156,  254,  153,  151,   97,  254,  254,   70,
 /*  1150 */   254,  254,  157,  254,  152,  254,  156,  254,  153,  151,
 /*  1160 */   254,   97,  254,   82,  254,  254,  254,  157,  254,  152,
 /*  1170 */   254,  156,   81,  153,  151,   97,  254,  254,  254,  254,
 /*  1180 */   254,  157,  254,  152,   97,  156,   74,  153,  151,  254,
 /*  1190 */   157,  254,  152,  254,  156,  254,  153,  151,   97,  254,
 /*  1200 */   254,   73,  254,  254,  157,  254,  152,  254,  156,  254,
 /*  1210 */   153,  151,  254,   97,  254,   92,  254,  254,  254,  157,
 /*  1220 */   254,  152,  254,  156,   91,  153,  151,   97,  254,  254,
 /*  1230 */   254,  254,  254,  157,  254,  152,   97,  156,   90,  153,
 /*  1240 */   151,  254,  157,  254,  152,  254,  156,  254,  153,  151,
 /*  1250 */    97,  254,  254,   69,  254,  254,  157,  254,  152,  254,
 /*  1260 */   156,  254,  153,  151,  254,   97,  254,   65,  254,  254,
 /*  1270 */   254,  157,  254,  152,  254,  156,   63,  153,  151,   97,
 /*  1280 */   254,  254,  254,  254,  254,  157,  254,  152,   97,  156,
 /*  1290 */    62,  153,  151,  254,  157,  254,  152,  254,  156,  254,
 /*  1300 */   153,  151,   97,  254,  254,   61,  254,  254,  157,  254,
 /*  1310 */   152,  254,  156,  254,  153,  151,  254,   97,  254,   59,
 /*  1320 */   254,  254,  254,  157,  254,  152,  254,  156,   57,  153,
 /*  1330 */   151,   97,  254,  254,  254,  254,  254,  157,  254,  152,
 /*  1340 */    97,  156,   58,  153,  151,  254,  157,  254,  152,  254,
 /*  1350 */   156,  254,  153,  151,   97,  254,  254,   56,  254,  254,
 /*  1360 */   157,  254,  152,  254,  156,  254,  153,  151,  254,   97,
 /*  1370 */   254,   55,  254,  254,  254,  157,  254,  152,  254,  156,
 /*  1380 */    64,  153,  151,   97,  254,  254,  254,  254,  254,  157,
 /*  1390 */   254,  152,   97,  156,   60,  153,  151,  254,  157,  254,
 /*  1400 */   152,  254,  156,  254,  153,  151,   97,  254,  254,  254,
 /*  1410 */   254,  254,  157,  254,  152,  254,  156,  254,  153,  151,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*    10 */    16,   17,   18,   19,   20,   21,   22,   23,   18,   19,
 /*    20 */    20,   21,   22,   23,   70,   71,   72,   33,    2,   35,
 /*    30 */    67,   68,   38,   33,    6,    7,    8,    9,   10,   11,
 /*    40 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*    50 */    22,   23,   36,   37,   20,   21,   22,   23,    1,   67,
 /*    60 */    68,   33,   35,   35,   35,   39,   38,   33,    6,    7,
 /*    70 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*    80 */    18,   19,   20,   21,   22,   23,   28,    1,   30,   32,
 /*    90 */    31,    1,   28,   36,   37,   33,    1,   35,   67,   68,
 /*   100 */    38,    1,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   110 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   120 */    50,   12,   32,   53,   54,   29,   36,   32,   12,   33,
 /*   130 */    28,   36,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   140 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   150 */    23,   33,    2,   28,   33,   29,   36,   28,   36,   33,
 /*   160 */    33,   38,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   170 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   180 */    35,    1,   44,   35,   71,   71,   47,   31,   36,   33,
 /*   190 */    49,    1,   61,   61,    6,    7,    8,    9,   10,   11,
 /*   200 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   210 */    22,   23,   40,   77,   77,   77,   77,   77,   28,   31,
 /*   220 */    30,   33,   32,    1,   77,   77,   36,   37,    6,    7,
 /*   230 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   240 */    18,   19,   20,   21,   22,   23,   77,   77,   77,   77,
 /*   250 */    77,   77,   77,   77,   77,   33,   77,   77,   77,   77,
 /*   260 */    77,   77,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   270 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   280 */    77,   77,   77,   77,   77,   77,   77,   77,   77,   33,
 /*   290 */    77,   35,   77,   77,   77,   77,    6,    7,    8,    9,
 /*   300 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   310 */    20,   21,   22,   23,   16,   17,   18,   19,   20,   21,
 /*   320 */    22,   23,   77,   33,   77,   77,   77,   77,   77,   77,
 /*   330 */    77,   33,   42,   77,   77,   77,   77,   77,   77,    6,
 /*   340 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   350 */    17,   18,   19,   20,   21,   22,   23,   77,   77,   77,
 /*   360 */    77,   77,   77,   77,   77,   77,   33,   77,   77,   77,
 /*   370 */    37,   77,   77,    6,    7,    8,    9,   10,   11,   12,
 /*   380 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   390 */    23,   77,   77,   77,   77,   77,   77,   77,   77,   77,
 /*   400 */    33,   77,    1,   77,   37,   77,   77,    6,    7,    8,
 /*   410 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   420 */    19,   20,   21,   22,   23,   77,   77,   77,   77,   77,
 /*   430 */    77,   77,   77,   77,   33,   77,   77,   77,   77,   77,
 /*   440 */    77,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   450 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   77,
 /*   460 */    77,   77,    6,    7,    8,    9,   10,   11,   33,   13,
 /*   470 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   480 */    77,   77,   77,   77,   77,   77,   77,   77,   77,   33,
 /*   490 */    77,   77,   77,   77,   77,   77,   77,    7,    8,    9,
 /*   500 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   510 */    20,   21,   22,   23,   77,   77,   77,   77,   77,   77,
 /*   520 */    77,   77,   77,   33,   77,   77,   77,   77,   77,   77,
 /*   530 */    77,   77,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   540 */    16,   17,   18,   19,   20,   21,   22,   23,   77,   77,
 /*   550 */    77,   77,   77,   77,   51,   77,   77,   33,   55,   56,
 /*   560 */    57,   58,   59,   60,   61,   77,   63,   64,   65,   66,
 /*   570 */    77,   77,   69,   77,   71,   77,   73,   77,   75,   76,
 /*   580 */    77,   77,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   590 */    17,   18,   19,   20,   21,   22,   23,   77,   77,   77,
 /*   600 */    77,   77,   77,   77,   77,   77,   33,   10,   11,   12,
 /*   610 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   620 */    23,    0,   77,   77,   77,   77,   77,   77,   14,   77,
 /*   630 */    33,   77,   77,   19,   77,   14,   77,   77,   24,   25,
 /*   640 */    19,   77,   28,   77,   30,   24,   25,   77,   77,   28,
 /*   650 */    36,   30,   77,   77,   77,   41,   35,   36,   77,   45,
 /*   660 */    46,   47,   48,   77,   43,   77,   45,   46,   47,   48,
 /*   670 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   680 */    22,   23,   14,   77,   77,   77,   77,   19,   77,   77,
 /*   690 */    77,   33,   24,   25,   77,   14,   28,   77,   30,   31,
 /*   700 */    19,   77,   77,   77,   36,   24,   25,   77,   77,   28,
 /*   710 */    29,   30,   77,   45,   46,   47,   48,   36,   77,   77,
 /*   720 */    14,   77,   77,   77,   77,   19,   45,   46,   47,   48,
 /*   730 */    24,   25,   77,   77,   28,   29,   30,   77,   77,   77,
 /*   740 */    77,   77,   36,   77,   77,   14,   77,   77,   77,   77,
 /*   750 */    19,   45,   46,   47,   48,   24,   25,   77,   77,   28,
 /*   760 */    29,   30,   77,   77,   77,   77,   77,   36,   77,   77,
 /*   770 */    14,   77,   77,   77,   77,   19,   45,   46,   47,   48,
 /*   780 */    24,   25,   77,   77,   28,   29,   30,   77,   77,   77,
 /*   790 */    77,   77,   36,   77,   77,   14,   77,   77,   77,   77,
 /*   800 */    19,   45,   46,   47,   48,   24,   25,   77,   77,   28,
 /*   810 */    29,   30,   77,   77,   77,   77,   77,   36,   77,   77,
 /*   820 */    14,   77,   77,   77,   77,   19,   45,   46,   47,   48,
 /*   830 */    24,   25,   77,   77,   28,   77,   30,   51,   77,   77,
 /*   840 */    77,   77,   36,   77,   77,   77,   60,   77,   62,   63,
 /*   850 */    77,   45,   46,   47,   48,   69,   51,   71,   77,   73,
 /*   860 */    74,   75,   76,   77,   77,   60,   77,   62,   63,   77,
 /*   870 */    77,   77,   77,   77,   69,   77,   71,   51,   73,   77,
 /*   880 */    75,   76,   77,   77,   77,   77,   60,   77,   62,   63,
 /*   890 */    77,   77,   77,   77,   51,   69,   77,   71,   77,   73,
 /*   900 */    77,   75,   76,   60,   77,   62,   63,   77,   51,   77,
 /*   910 */    77,   77,   69,   77,   71,   77,   73,   60,   75,   76,
 /*   920 */    63,   77,   77,   77,   77,   77,   69,   77,   71,   51,
 /*   930 */    73,   77,   75,   76,   77,   77,   77,   77,   51,   77,
 /*   940 */    77,   63,   77,   77,   77,   77,   77,   69,   77,   71,
 /*   950 */    63,   73,   77,   75,   76,   51,   69,   77,   71,   77,
 /*   960 */    73,   77,   75,   76,   51,   77,   77,   63,   77,   77,
 /*   970 */    77,   77,   77,   69,   77,   71,   63,   73,   51,   75,
 /*   980 */    76,   77,   69,   77,   71,   77,   73,   77,   75,   76,
 /*   990 */    63,   77,   77,   51,   77,   77,   69,   77,   71,   77,
 /*  1000 */    73,   77,   75,   76,   77,   63,   77,   51,   77,   77,
 /*  1010 */    77,   69,   77,   71,   77,   73,   51,   75,   76,   63,
 /*  1020 */    77,   77,   77,   77,   77,   69,   77,   71,   63,   73,
 /*  1030 */    51,   75,   76,   77,   69,   77,   71,   77,   73,   77,
 /*  1040 */    75,   76,   63,   77,   77,   51,   77,   77,   69,   77,
 /*  1050 */    71,   77,   73,   77,   75,   76,   77,   63,   77,   51,
 /*  1060 */    77,   77,   77,   69,   77,   71,   77,   73,   51,   75,
 /*  1070 */    76,   63,   77,   77,   77,   77,   77,   69,   77,   71,
 /*  1080 */    63,   73,   51,   75,   76,   77,   69,   77,   71,   77,
 /*  1090 */    73,   77,   75,   76,   63,   77,   77,   51,   77,   77,
 /*  1100 */    69,   77,   71,   77,   73,   77,   75,   76,   77,   63,
 /*  1110 */    77,   51,   77,   77,   77,   69,   77,   71,   77,   73,
 /*  1120 */    51,   75,   76,   63,   77,   77,   77,   77,   77,   69,
 /*  1130 */    77,   71,   63,   73,   51,   75,   76,   77,   69,   77,
 /*  1140 */    71,   77,   73,   77,   75,   76,   63,   77,   77,   51,
 /*  1150 */    77,   77,   69,   77,   71,   77,   73,   77,   75,   76,
 /*  1160 */    77,   63,   77,   51,   77,   77,   77,   69,   77,   71,
 /*  1170 */    77,   73,   51,   75,   76,   63,   77,   77,   77,   77,
 /*  1180 */    77,   69,   77,   71,   63,   73,   51,   75,   76,   77,
 /*  1190 */    69,   77,   71,   77,   73,   77,   75,   76,   63,   77,
 /*  1200 */    77,   51,   77,   77,   69,   77,   71,   77,   73,   77,
 /*  1210 */    75,   76,   77,   63,   77,   51,   77,   77,   77,   69,
 /*  1220 */    77,   71,   77,   73,   51,   75,   76,   63,   77,   77,
 /*  1230 */    77,   77,   77,   69,   77,   71,   63,   73,   51,   75,
 /*  1240 */    76,   77,   69,   77,   71,   77,   73,   77,   75,   76,
 /*  1250 */    63,   77,   77,   51,   77,   77,   69,   77,   71,   77,
 /*  1260 */    73,   77,   75,   76,   77,   63,   77,   51,   77,   77,
 /*  1270 */    77,   69,   77,   71,   77,   73,   51,   75,   76,   63,
 /*  1280 */    77,   77,   77,   77,   77,   69,   77,   71,   63,   73,
 /*  1290 */    51,   75,   76,   77,   69,   77,   71,   77,   73,   77,
 /*  1300 */    75,   76,   63,   77,   77,   51,   77,   77,   69,   77,
 /*  1310 */    71,   77,   73,   77,   75,   76,   77,   63,   77,   51,
 /*  1320 */    77,   77,   77,   69,   77,   71,   77,   73,   51,   75,
 /*  1330 */    76,   63,   77,   77,   77,   77,   77,   69,   77,   71,
 /*  1340 */    63,   73,   51,   75,   76,   77,   69,   77,   71,   77,
 /*  1350 */    73,   77,   75,   76,   63,   77,   77,   51,   77,   77,
 /*  1360 */    69,   77,   71,   77,   73,   77,   75,   76,   77,   63,
 /*  1370 */    77,   51,   77,   77,   77,   69,   77,   71,   77,   73,
 /*  1380 */    51,   75,   76,   63,   77,   77,   77,   77,   77,   69,
 /*  1390 */    77,   71,   63,   73,   51,   75,   76,   77,   69,   77,
 /*  1400 */    71,   77,   73,   77,   75,   76,   63,   77,   77,   77,
 /*  1410 */    77,   77,   69,   77,   71,   77,   73,   77,   75,   76,
};
#define YY_SHIFT_USE_DFLT (-7)
#define YY_SHIFT_COUNT (118)
#define YY_SHIFT_MIN   (-6)
#define YY_SHIFT_MAX   (806)
static const short yy_shift_ofst[] = {
 /*     0 */   141,  621,  806,  781,  756,  806,  731,  706,  681,  806,
 /*    10 */   614,  668,  806,  806,  806,  806,  806,  806,  806,  806,
 /*    20 */   806,  806,  806,  806,  806,  806,  806,  806,  806,  806,
 /*    30 */   806,  806,  806,  806,  806,  806,  806,  806,  806,  806,
 /*    40 */   806,  806,  806,  806,  806,  806,  806,  139,  172,  172,
 /*    50 */   172,   16,  152,  139,  139,   62,   28,   -6,  401,  367,
 /*    60 */   333,  290,  256,  222,  188,  156,  126,   96,  435,  456,
 /*    70 */   490,  456,  524,  573,  597,  658,  658,  298,  298,  298,
 /*    80 */   298,    0,    0,  190,   34,   34,   57,   95,   90,   26,
 /*    90 */   127,  127,  127,  127,  127,  127,  127,   58,  148,  138,
 /*   100 */   180,  123,  145,  129,  122,  121,  120,  125,  150,  118,
 /*   110 */   116,  102,  109,  100,   59,   64,   86,   29,   27,
};
#define YY_REDUCE_USE_DFLT (-47)
#define YY_REDUCE_COUNT (54)
#define YY_REDUCE_MIN   (-46)
#define YY_REDUCE_MAX   (1343)
static const short yy_reduce_ofst[] = {
 /*     0 */    70,  503,  786,  843,  826,  805,  857,  857,  857,  857,
 /*    10 */  1343, 1329, 1320, 1306, 1291, 1277, 1268, 1254, 1239, 1225,
 /*    20 */  1216, 1202, 1187, 1173, 1164, 1150, 1135, 1121, 1112, 1098,
 /*    30 */  1083, 1069, 1060, 1046, 1031, 1017, 1008,  994,  979,  965,
 /*    40 */   956,  942,  927,  913,  904,  887,  878,  -46,   31,   -8,
 /*    50 */   -37,  132,  131,  114,  113,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   169,  252,  214,  252,  252,  252,  252,  252,  252,  215,
 /*    10 */   252,  252,  252,  252,  252,  252,  252,  252,  252,  252,
 /*    20 */   252,  252,  252,  252,  252,  252,  252,  252,  252,  252,
 /*    30 */   252,  252,  252,  252,  252,  252,  252,  252,  252,  252,
 /*    40 */   252,  252,  252,  252,  252,  252,  252,  205,  252,  189,
 /*    50 */   252,  252,  252,  252,  206,  252,  252,  252,  252,  252,
 /*    60 */   200,  252,  252,  252,  252,  252,  252,  252,  177,  204,
 /*    70 */   239,  203,  238,  246,  245,  233,  232,  237,  236,  235,
 /*    80 */   234,  244,  243,  180,  226,  227,  252,  252,  252,  252,
 /*    90 */   242,  241,  240,  231,  230,  229,  228,  249,  209,  252,
 /*   100 */   252,  252,  252,  252,  252,  252,  252,  252,  252,  225,
 /*   110 */   252,  252,  252,  252,  252,  252,  252,  252,  252,  251,
 /*   120 */   250,  199,  193,  191,  190,  192,  187,  186,  201,  197,
 /*   130 */   196,  194,  179,  224,  195,  198,  188,  178,  207,  247,
 /*   140 */   182,  184,  248,  185,  208,  213,  223,  222,  221,  220,
 /*   150 */   219,  218,  217,  216,  211,  210,  212,  209,  183,  181,
 /*   160 */   180,  176,  175,  174,  173,  172,  171,  170,
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
  "FUNCTION_CALL",  "INDEX",         "OR",            "AND",         
  "BITXOR",        "BITAND",        "EQUALTO",       "NOTEQUALTO",  
  "GREATERTHAN",   "GORE",          "LESSTHAN",      "LORE",        
  "SHIFTL",        "SHIFTR",        "PLUS",          "MINUS",       
  "DIVIDE",        "TIMES",         "MODULO",        "POW",         
  "NOT",           "BITNOT",        "UMINUS",        "PLUSPLUS",    
  "LPAREN",        "RPAREN",        "LBRAC",         "RBRAC",       
  "COMMA",         "COLON",         "COLLECTARRAY",  "DELIMITER",   
  "NAME",          "LCURL",         "RCURL",         "WILDCARD",    
  "WHERE",         "CASE",          "OF",            "LET",         
  "IN",            "PRINT",         "NUM",           "STRING",      
  "BOOLEAN",       "OPENQUOTEERROR",  "error",         "expr",        
  "id",            "main",          "in",            "start",       
  "test",          "spec",          "assignment",    "top_stmt",    
  "stmt",          "name_chain",    "stmt_list",     "array_index", 
  "case_statement",  "final_guard_statement",  "guard_statement",  "final_where_statement",
  "where_statement",  "map",           "map_argument_list",  "string",      
  "maybe_empty_map_argument_list",  "array",         "maybe_empty_stmt_list",  "num",         
  "bool",        
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
 /*  14 */ "expr ::= NAME LBRAC RBRAC LPAREN stmt_list RPAREN",
 /*  15 */ "expr ::= array_index LPAREN stmt_list RPAREN",
 /*  16 */ "expr ::= NAME LPAREN RPAREN",
 /*  17 */ "expr ::= array_index LPAREN RPAREN",
 /*  18 */ "test ::= case_statement",
 /*  19 */ "assignment ::= final_guard_statement",
 /*  20 */ "guard_statement ::= name_chain LCURL BITOR expr ASSIGN expr DELIMITER",
 /*  21 */ "guard_statement ::= guard_statement BITOR expr ASSIGN expr DELIMITER",
 /*  22 */ "final_guard_statement ::= guard_statement BITOR expr ASSIGN expr RCURL",
 /*  23 */ "final_guard_statement ::= guard_statement WILDCARD ASSIGN expr RCURL",
 /*  24 */ "assignment ::= guard_statement BITOR expr ASSIGN expr DELIMITER final_where_statement",
 /*  25 */ "assignment ::= guard_statement WILDCARD ASSIGN expr DELIMITER final_where_statement",
 /*  26 */ "where_statement ::= WHERE LCURL",
 /*  27 */ "where_statement ::= WHERE name_chain ASSIGN expr LCURL",
 /*  28 */ "where_statement ::= where_statement name_chain ASSIGN expr DELIMITER",
 /*  29 */ "final_where_statement ::= where_statement name_chain ASSIGN expr RCURL DELIMITER RCURL",
 /*  30 */ "case_statement ::= name_chain ASSIGN CASE expr OF",
 /*  31 */ "test ::= LET IN",
 /*  32 */ "assignment ::= name_chain ASSIGN expr",
 /*  33 */ "assignment ::= name_chain ASSIGN expr LCURL final_where_statement",
 /*  34 */ "test ::= map",
 /*  35 */ "map_argument_list ::= string ASSIGN expr",
 /*  36 */ "map_argument_list ::= map_argument_list string ASSIGN expr",
 /*  37 */ "maybe_empty_map_argument_list ::=",
 /*  38 */ "maybe_empty_map_argument_list ::= map_argument_list",
 /*  39 */ "expr ::= NAME LESSTHAN string GREATERTHAN",
 /*  40 */ "map ::= LESSTHAN maybe_empty_map_argument_list GREATERTHAN",
 /*  41 */ "expr ::= map",
 /*  42 */ "stmt_list ::= stmt",
 /*  43 */ "stmt_list ::= stmt_list stmt",
 /*  44 */ "expr ::= array",
 /*  45 */ "array ::= LBRAC maybe_empty_stmt_list RBRAC",
 /*  46 */ "maybe_empty_stmt_list ::=",
 /*  47 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  48 */ "expr ::= num",
 /*  49 */ "expr ::= string",
 /*  50 */ "expr ::= bool",
 /*  51 */ "expr ::= PRINT LPAREN expr RPAREN",
 /*  52 */ "expr ::= LPAREN expr RPAREN",
 /*  53 */ "num ::= NUM",
 /*  54 */ "string ::= STRING",
 /*  55 */ "bool ::= BOOLEAN",
 /*  56 */ "name_chain ::= name_chain COMMA LPAREN NAME COLON NAME LPAREN",
 /*  57 */ "expr ::= expr COLON expr",
 /*  58 */ "expr ::= expr PLUS expr",
 /*  59 */ "expr ::= expr MINUS expr",
 /*  60 */ "expr ::= expr DIVIDE expr",
 /*  61 */ "expr ::= expr TIMES expr",
 /*  62 */ "expr ::= expr MODULO expr",
 /*  63 */ "expr ::= expr POW expr",
 /*  64 */ "expr ::= expr EQUALTO expr",
 /*  65 */ "expr ::= expr NOTEQUALTO expr",
 /*  66 */ "expr ::= expr LESSTHAN expr",
 /*  67 */ "expr ::= expr GREATERTHAN expr",
 /*  68 */ "expr ::= expr LORE expr",
 /*  69 */ "expr ::= expr GORE expr",
 /*  70 */ "expr ::= expr AND expr",
 /*  71 */ "expr ::= expr OR expr",
 /*  72 */ "expr ::= BITNOT expr",
 /*  73 */ "expr ::= MINUS expr",
 /*  74 */ "expr ::= NOT expr",
 /*  75 */ "expr ::= expr SHIFTL expr",
 /*  76 */ "expr ::= expr SHIFTR expr",
 /*  77 */ "expr ::= expr BITAND expr",
 /*  78 */ "expr ::= expr BITXOR expr",
 /*  79 */ "array_index ::= NAME LBRAC expr RBRAC",
 /*  80 */ "array_index ::= array_index LBRAC expr RBRAC",
 /*  81 */ "expr ::= array_index",
 /*  82 */ "in ::= error",
 /*  83 */ "error ::= OPENQUOTEERROR",
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
    case 30: /* LBRAC */
    case 31: /* RBRAC */
    case 32: /* COMMA */
    case 33: /* COLON */
    case 34: /* COLLECTARRAY */
    case 35: /* DELIMITER */
    case 36: /* NAME */
    case 37: /* LCURL */
    case 38: /* RCURL */
    case 39: /* WILDCARD */
    case 40: /* WHERE */
    case 41: /* CASE */
    case 42: /* OF */
    case 43: /* LET */
    case 44: /* IN */
    case 45: /* PRINT */
    case 46: /* NUM */
    case 47: /* STRING */
    case 48: /* BOOLEAN */
    case 49: /* OPENQUOTEERROR */
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
  { 51, 6 },
  { 51, 4 },
  { 51, 3 },
  { 51, 3 },
  { 56, 1 },
  { 58, 1 },
  { 66, 7 },
  { 66, 6 },
  { 65, 6 },
  { 65, 5 },
  { 58, 7 },
  { 58, 6 },
  { 68, 2 },
  { 68, 5 },
  { 68, 5 },
  { 67, 7 },
  { 64, 5 },
  { 56, 2 },
  { 58, 3 },
  { 58, 5 },
  { 56, 1 },
  { 70, 3 },
  { 70, 4 },
  { 72, 0 },
  { 72, 1 },
  { 51, 4 },
  { 69, 3 },
  { 51, 1 },
  { 62, 1 },
  { 62, 2 },
  { 51, 1 },
  { 73, 3 },
  { 74, 0 },
  { 74, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 4 },
  { 51, 3 },
  { 75, 1 },
  { 71, 1 },
  { 76, 1 },
  { 61, 7 },
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
#line 85 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,35,&yymsp[0].minor);
}
#line 1236 "./src/Grammar/grammar.c"
        break;
      case 5: /* start ::= spec */
#line 91 "./src/Grammar/grammar.y"
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
#line 1259 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= assignment */
      case 18: /* test ::= case_statement */ yytestcase(yyruleno==18);
#line 112 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1267 "./src/Grammar/grammar.c"
        break;
      case 7: /* spec ::= top_stmt */
      case 8: /* top_stmt ::= stmt */ yytestcase(yyruleno==8);
#line 117 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1276 "./src/Grammar/grammar.c"
        break;
      case 9: /* stmt ::= expr */
      case 42: /* stmt_list ::= stmt */ yytestcase(yyruleno==42);
#line 129 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1285 "./src/Grammar/grammar.c"
        break;
      case 10: /* name_chain ::= name_chain NAME */
#line 135 "./src/Grammar/grammar.y"
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
#line 1324 "./src/Grammar/grammar.c"
        break;
      case 11: /* name_chain ::= NAME */
#line 172 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1333 "./src/Grammar/grammar.c"
        break;
      case 12: /* expr ::= NAME */
#line 179 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1346 "./src/Grammar/grammar.c"
        break;
      case 13: /* expr ::= NAME LPAREN stmt_list RPAREN */
#line 195 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1378 "./src/Grammar/grammar.c"
        break;
      case 14: /* expr ::= NAME LBRAC RBRAC LPAREN stmt_list RPAREN */
#line 223 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,30,&yymsp[-4].minor);
  yy_destructor(yypParser,31,&yymsp[-3].minor);
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1412 "./src/Grammar/grammar.c"
        break;
      case 15: /* expr ::= array_index LPAREN stmt_list RPAREN */
#line 251 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1438 "./src/Grammar/grammar.c"
        break;
      case 16: /* expr ::= NAME LPAREN RPAREN */
#line 274 "./src/Grammar/grammar.y"
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
#line 1453 "./src/Grammar/grammar.c"
        break;
      case 17: /* expr ::= array_index LPAREN RPAREN */
#line 285 "./src/Grammar/grammar.y"
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
#line 1468 "./src/Grammar/grammar.c"
        break;
      case 19: /* assignment ::= final_guard_statement */
#line 302 "./src/Grammar/grammar.y"
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
#line 1489 "./src/Grammar/grammar.c"
        break;
      case 20: /* guard_statement ::= name_chain LCURL BITOR expr ASSIGN expr DELIMITER */
#line 322 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD1" << std::endl;
    optic::object tree = create_condition_tree(yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0 = create_guard(yymsp[-6].minor.yy0,tree);
    std::cout << "GUARD2" << std::endl;
  yy_destructor(yypParser,37,&yymsp[-5].minor);
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,35,&yymsp[0].minor);
}
#line 1503 "./src/Grammar/grammar.c"
        break;
      case 21: /* guard_statement ::= guard_statement BITOR expr ASSIGN expr DELIMITER */
#line 330 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD3" << std::endl;
    add_branch_to_tree(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-5].minor.yy0;
    std::cout << "GUARD4" << std::endl;
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,35,&yymsp[0].minor);
}
#line 1516 "./src/Grammar/grammar.c"
        break;
      case 22: /* final_guard_statement ::= guard_statement BITOR expr ASSIGN expr RCURL */
#line 338 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD5" << std::endl;
    add_branch_to_tree(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-5].minor.yy0;
    std::cout << "GUARD6" << std::endl;
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,38,&yymsp[0].minor);
}
#line 1529 "./src/Grammar/grammar.c"
        break;
      case 23: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr RCURL */
#line 346 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD7" << std::endl;
    add_wildcard_to_tree(yymsp[-4].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-4].minor.yy0;
    std::cout << "GUARD8" << std::endl;
  yy_destructor(yypParser,39,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,38,&yymsp[0].minor);
}
#line 1542 "./src/Grammar/grammar.c"
        break;
      case 24: /* assignment ::= guard_statement BITOR expr ASSIGN expr DELIMITER final_where_statement */
#line 354 "./src/Grammar/grammar.y"
{
    add_branch_to_tree(yymsp[-6].minor.yy0,yymsp[-4].minor.yy0,yymsp[-2].minor.yy0);
    panopticon::object& b = yymsp[-6].minor.yy0.data.array->at(0);
    panopticon::object& func_body = yymsp[-6].minor.yy0.data.array->at(1);
    panopticon::object resolve;
    panopticon::store_operations(resolve, func_body, &panopticon::resolve_guard);
    optic::object combined;
    panopticon::store_operations(combined,yymsp[0].minor.yy0,func_body);
    insure_ready_for_assignment(b,combined);
    panopticon::parse_operations(yygotominor.yy0, b, combined, &panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,2,&yymsp[-5].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,35,&yymsp[-1].minor);
}
#line 1565 "./src/Grammar/grammar.c"
        break;
      case 25: /* assignment ::= guard_statement WILDCARD ASSIGN expr DELIMITER final_where_statement */
#line 372 "./src/Grammar/grammar.y"
{
    add_wildcard_to_tree(yymsp[-5].minor.yy0,yymsp[-2].minor.yy0);
    panopticon::object& b = yymsp[-5].minor.yy0.data.array->at(0);
    panopticon::object& func_body = yymsp[-5].minor.yy0.data.array->at(1);
    panopticon::object resolve;
    panopticon::store_operations(resolve, func_body, &panopticon::resolve_guard);
    optic::object combined;
    panopticon::store_operations(combined,yymsp[0].minor.yy0,func_body);
    insure_ready_for_assignment(b,combined);
    panopticon::parse_operations(yygotominor.yy0, b, combined, &panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,39,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,35,&yymsp[-1].minor);
}
#line 1588 "./src/Grammar/grammar.c"
        break;
      case 26: /* where_statement ::= WHERE LCURL */
#line 394 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::NIL;
    std::cout << "Where 1" << std::endl;
  yy_destructor(yypParser,40,&yymsp[-1].minor);
  yy_destructor(yypParser,37,&yymsp[0].minor);
}
#line 1598 "./src/Grammar/grammar.c"
        break;
      case 27: /* where_statement ::= WHERE name_chain ASSIGN expr LCURL */
#line 400 "./src/Grammar/grammar.y"
{
    std::cout << "Where 1.5" << std::endl;
    insure_ready_for_assignment(yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yymsp[-3].minor.yy0.type = optic::FUNCTION_ARG_NAMES;
    panopticon::parse_operations(yygotominor.yy0, yymsp[-3].minor.yy0, yymsp[-1].minor.yy0, panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,40,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,37,&yymsp[0].minor);
}
#line 1616 "./src/Grammar/grammar.c"
        break;
      case 28: /* where_statement ::= where_statement name_chain ASSIGN expr DELIMITER */
#line 413 "./src/Grammar/grammar.y"
{
    std::cout << "Where 2" << std::endl;
    insure_ready_for_assignment(yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yymsp[-3].minor.yy0.type = optic::FUNCTION_ARG_NAMES;

    if(yymsp[-4].minor.yy0.type!=optic::NIL)
    {
        optic::object assign;
        panopticon::parse_operations(assign, yymsp[-3].minor.yy0, yymsp[-1].minor.yy0, panopticon::assign_variable);
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
  yy_destructor(yypParser,35,&yymsp[0].minor);
}
#line 1643 "./src/Grammar/grammar.c"
        break;
      case 29: /* final_where_statement ::= where_statement name_chain ASSIGN expr RCURL DELIMITER RCURL */
#line 436 "./src/Grammar/grammar.y"
{
    std::cout << "Where 3" << std::endl;
    insure_ready_for_assignment(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0);
    yymsp[-5].minor.yy0.type = optic::FUNCTION_ARG_NAMES;
    if(yymsp[-6].minor.yy0.type!=optic::NIL)
    {
        optic::object assign;
        panopticon::parse_operations(assign, yymsp[-5].minor.yy0, yymsp[-3].minor.yy0, panopticon::assign_variable);
        optic::store_operations(yygotominor.yy0,yymsp[-6].minor.yy0,assign);
    }
    else
    {
        panopticon::parse_operations(yygotominor.yy0, yymsp[-5].minor.yy0, yymsp[-3].minor.yy0, panopticon::assign_variable);
    }
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-4].minor);
  yy_destructor(yypParser,38,&yymsp[-2].minor);
  yy_destructor(yypParser,35,&yymsp[-1].minor);
  yy_destructor(yypParser,38,&yymsp[0].minor);
}
#line 1671 "./src/Grammar/grammar.c"
        break;
      case 30: /* case_statement ::= name_chain ASSIGN CASE expr OF */
#line 458 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,41,&yymsp[-2].minor);
  yy_destructor(yypParser,42,&yymsp[0].minor);
}
#line 1682 "./src/Grammar/grammar.c"
        break;
      case 31: /* test ::= LET IN */
#line 463 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,43,&yymsp[-1].minor);
  yy_destructor(yypParser,44,&yymsp[0].minor);
}
#line 1690 "./src/Grammar/grammar.c"
        break;
      case 32: /* assignment ::= name_chain ASSIGN expr */
#line 472 "./src/Grammar/grammar.y"
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
#line 1705 "./src/Grammar/grammar.c"
        break;
      case 33: /* assignment ::= name_chain ASSIGN expr LCURL final_where_statement */
#line 485 "./src/Grammar/grammar.y"
{
    std::cout << "Where assign" << std::endl;
    panopticon::object body;
    panopticon::store_operations(body,yymsp[0].minor.yy0,yymsp[-2].minor.yy0);
    insure_ready_for_assignment(yymsp[-4].minor.yy0,body);
    panopticon::parse_operations(yygotominor.yy0, yymsp[-4].minor.yy0, body, panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,37,&yymsp[-1].minor);
}
#line 1723 "./src/Grammar/grammar.c"
        break;
      case 35: /* map_argument_list ::= string ASSIGN expr */
      case 36: /* map_argument_list ::= map_argument_list string ASSIGN expr */ yytestcase(yyruleno==36);
#line 506 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1731 "./src/Grammar/grammar.c"
        break;
      case 39: /* expr ::= NAME LESSTHAN string GREATERTHAN */
#line 512 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
  yy_destructor(yypParser,14,&yymsp[-2].minor);
  yy_destructor(yypParser,12,&yymsp[0].minor);
}
#line 1740 "./src/Grammar/grammar.c"
        break;
      case 40: /* map ::= LESSTHAN maybe_empty_map_argument_list GREATERTHAN */
#line 517 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    optic::out() << "Map" << std::endl;
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Map");
/*    yygotominor.yy0.type = optic::MAP;*/
  yy_destructor(yypParser,14,&yymsp[-2].minor);
  yy_destructor(yypParser,12,&yymsp[0].minor);
}
#line 1753 "./src/Grammar/grammar.c"
        break;
      case 41: /* expr ::= map */
      case 44: /* expr ::= array */ yytestcase(yyruleno==44);
      case 81: /* expr ::= array_index */ yytestcase(yyruleno==81);
#line 526 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1762 "./src/Grammar/grammar.c"
        break;
      case 43: /* stmt_list ::= stmt_list stmt */
#line 537 "./src/Grammar/grammar.y"
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
#line 1780 "./src/Grammar/grammar.c"
        break;
      case 45: /* array ::= LBRAC maybe_empty_stmt_list RBRAC */
#line 558 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yygotominor.yy0.type = optic::ARRAY;
  yy_destructor(yypParser,30,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1790 "./src/Grammar/grammar.c"
        break;
      case 46: /* maybe_empty_stmt_list ::= */
#line 564 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1798 "./src/Grammar/grammar.c"
        break;
      case 47: /* maybe_empty_stmt_list ::= stmt_list */
#line 570 "./src/Grammar/grammar.y"
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
#line 1814 "./src/Grammar/grammar.c"
        break;
      case 48: /* expr ::= num */
      case 50: /* expr ::= bool */ yytestcase(yyruleno==50);
#line 588 "./src/Grammar/grammar.y"
{
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1822 "./src/Grammar/grammar.c"
        break;
      case 49: /* expr ::= string */
#line 593 "./src/Grammar/grammar.y"
{
   create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1829 "./src/Grammar/grammar.c"
        break;
      case 51: /* expr ::= PRINT LPAREN expr RPAREN */
#line 607 "./src/Grammar/grammar.y"
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
#line 1844 "./src/Grammar/grammar.c"
        break;
      case 52: /* expr ::= LPAREN expr RPAREN */
#line 617 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1853 "./src/Grammar/grammar.c"
        break;
      case 53: /* num ::= NUM */
#line 622 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1861 "./src/Grammar/grammar.c"
        break;
      case 54: /* string ::= STRING */
#line 628 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::STRING;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1869 "./src/Grammar/grammar.c"
        break;
      case 55: /* bool ::= BOOLEAN */
#line 635 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::BOOL;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1877 "./src/Grammar/grammar.c"
        break;
      case 56: /* name_chain ::= name_chain COMMA LPAREN NAME COLON NAME LPAREN */
#line 654 "./src/Grammar/grammar.y"
{
    std::cout << "PATTERN_ARGUMENT" << std::endl;
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = yymsp[-3].minor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yygotominor.yy0 = yymsp[-6].minor.yy0;
  yy_destructor(yypParser,32,&yymsp[-5].minor);
  yy_destructor(yypParser,28,&yymsp[-4].minor);
  yy_destructor(yypParser,33,&yymsp[-2].minor);
  yy_destructor(yypParser,28,&yymsp[0].minor);
}
#line 1892 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr COLON expr */
#line 668 "./src/Grammar/grammar.y"
{
    std::cout << "PREPEND" << std::endl;
    optic::store_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&optic::prepend,false);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,33,&yymsp[-1].minor);
}
#line 1906 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= expr PLUS expr */
#line 679 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::plus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1919 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= expr MINUS expr */
#line 689 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1932 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= expr DIVIDE expr */
#line 699 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1945 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= expr TIMES expr */
#line 709 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1958 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= expr MODULO expr */
#line 719 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1971 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= expr POW expr */
#line 729 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1984 "./src/Grammar/grammar.c"
        break;
      case 64: /* expr ::= expr EQUALTO expr */
#line 739 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1997 "./src/Grammar/grammar.c"
        break;
      case 65: /* expr ::= expr NOTEQUALTO expr */
#line 749 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 2010 "./src/Grammar/grammar.c"
        break;
      case 66: /* expr ::= expr LESSTHAN expr */
#line 759 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 2023 "./src/Grammar/grammar.c"
        break;
      case 67: /* expr ::= expr GREATERTHAN expr */
#line 769 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 2036 "./src/Grammar/grammar.c"
        break;
      case 68: /* expr ::= expr LORE expr */
#line 779 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 2049 "./src/Grammar/grammar.c"
        break;
      case 69: /* expr ::= expr GORE expr */
#line 789 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 2062 "./src/Grammar/grammar.c"
        break;
      case 70: /* expr ::= expr AND expr */
#line 799 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 2075 "./src/Grammar/grammar.c"
        break;
      case 71: /* expr ::= expr OR expr */
#line 809 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 2088 "./src/Grammar/grammar.c"
        break;
      case 72: /* expr ::= BITNOT expr */
#line 819 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,25,&yymsp[-1].minor);
}
#line 2101 "./src/Grammar/grammar.c"
        break;
      case 73: /* expr ::= MINUS expr */
#line 829 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 2114 "./src/Grammar/grammar.c"
        break;
      case 74: /* expr ::= NOT expr */
#line 839 "./src/Grammar/grammar.y"
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
#line 2128 "./src/Grammar/grammar.c"
        break;
      case 75: /* expr ::= expr SHIFTL expr */
#line 850 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 2141 "./src/Grammar/grammar.c"
        break;
      case 76: /* expr ::= expr SHIFTR expr */
#line 860 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 2154 "./src/Grammar/grammar.c"
        break;
      case 77: /* expr ::= expr BITAND expr */
#line 870 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 2167 "./src/Grammar/grammar.c"
        break;
      case 78: /* expr ::= expr BITXOR expr */
#line 880 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 2180 "./src/Grammar/grammar.c"
        break;
      case 79: /* array_index ::= NAME LBRAC expr RBRAC */
#line 890 "./src/Grammar/grammar.y"
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
#line 2195 "./src/Grammar/grammar.c"
        break;
      case 80: /* array_index ::= array_index LBRAC expr RBRAC */
#line 901 "./src/Grammar/grammar.y"
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
#line 2209 "./src/Grammar/grammar.c"
        break;
      case 82: /* in ::= error */
#line 920 "./src/Grammar/grammar.y"
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
#line 2224 "./src/Grammar/grammar.c"
        break;
      case 83: /* error ::= OPENQUOTEERROR */
#line 933 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy155 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 2233 "./src/Grammar/grammar.c"
        break;
      default:
      /* (0) main ::= in */ yytestcase(yyruleno==0);
      /* (1) in ::= */ yytestcase(yyruleno==1);
      /* (34) test ::= map */ yytestcase(yyruleno==34);
      /* (37) maybe_empty_map_argument_list ::= */ yytestcase(yyruleno==37);
      /* (38) maybe_empty_map_argument_list ::= map_argument_list */ yytestcase(yyruleno==38);
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
#line 79 "./src/Grammar/grammar.y"

panopticon::out() << "Syntax error!" << std::endl;
#line 2303 "./src/Grammar/grammar.c"
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
#line 74 "./src/Grammar/grammar.y"

printf("parsing complete!\n\n\n");
#line 2325 "./src/Grammar/grammar.c"
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
