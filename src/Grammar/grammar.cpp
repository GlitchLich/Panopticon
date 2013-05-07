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
#define YYNSTATE 146
#define YYNRULE 72
#define YYERRORSYMBOL 50
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
#define YY_ACTTAB_COUNT (1218)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    28,   29,   24,   25,   35,   34,   32,   30,   33,   31,
 /*    10 */    27,   26,   45,   42,   40,   38,   37,   36,   27,   26,
 /*    20 */    45,   42,   40,   38,   37,   36,   10,    4,  113,  105,
 /*    30 */    11,   88,  219,    1,   16,   28,   29,   24,   25,   35,
 /*    40 */    34,   32,   30,   33,   31,   27,   26,   45,   42,   40,
 /*    50 */    38,   37,   36,  144,   45,   42,   40,   38,   37,   36,
 /*    60 */   119,   89,    3,  108,  143,   20,  107,  100,  119,   44,
 /*    70 */    28,   29,   24,   25,   35,   34,   32,   30,   33,   31,
 /*    80 */    27,   26,   45,   42,   40,   38,   37,   36,   28,   29,
 /*    90 */    24,   25,   35,   34,   32,   30,   33,   31,   27,   26,
 /*   100 */    45,   42,   40,   38,   37,   36,   41,   43,  115,  114,
 /*   110 */    36,  130,   28,   29,   24,   25,   35,   34,   32,   30,
 /*   120 */    33,   31,   27,   26,   45,   42,   40,   38,   37,   36,
 /*   130 */   157,  125,   15,   48,  111,  129,   28,   29,   24,   25,
 /*   140 */    35,   34,   32,   30,   33,   31,   27,   26,   45,   42,
 /*   150 */    40,   38,   37,   36,    5,   19,   87,    4,  112,   12,
 /*   160 */    11,   82,  123,   14,  157,  157,  119,  115,   83,   28,
 /*   170 */    29,   24,   25,   35,   34,   32,   30,   33,   31,   27,
 /*   180 */    26,   45,   42,   40,   38,   37,   36,   47,  104,  220,
 /*   190 */    40,   38,   37,   36,  220,  120,  220,   18,  220,   86,
 /*   200 */   220,  220,   28,   29,   24,   25,   35,   34,   32,   30,
 /*   210 */    33,   31,   27,   26,   45,   42,   40,   38,   37,   36,
 /*   220 */    28,   29,   24,   25,   35,   34,   32,   30,   33,   31,
 /*   230 */    27,   26,   45,   42,   40,   38,   37,   36,  220,  220,
 /*   240 */   220,  220,  220,  220,  220,  220,  220,  220,  118,  220,
 /*   250 */   220,  220,  220,  220,  220,   28,   29,   24,   25,   35,
 /*   260 */    34,   32,   30,   33,   31,   27,   26,   45,   42,   40,
 /*   270 */    38,   37,   36,   29,   24,   25,   35,   34,   32,   30,
 /*   280 */    33,   31,   27,   26,   45,   42,   40,   38,   37,   36,
 /*   290 */   117,  220,  220,  220,  220,  220,  220,   28,   29,   24,
 /*   300 */    25,   35,   34,   32,   30,   33,   31,   27,   26,   45,
 /*   310 */    42,   40,   38,   37,   36,   32,   30,   33,   31,   27,
 /*   320 */    26,   45,   42,   40,   38,   37,   36,   46,  220,  220,
 /*   330 */   220,  220,  220,  220,   28,   29,   24,   25,   35,   34,
 /*   340 */    32,   30,   33,   31,   27,   26,   45,   42,   40,   38,
 /*   350 */    37,   36,  220,  220,  220,  220,  220,  220,  220,  220,
 /*   360 */   220,  220,  220,  220,  116,  220,   13,  220,  220,  220,
 /*   370 */   220,   28,   29,   24,   25,   35,   34,   32,   30,   33,
 /*   380 */    31,   27,   26,   45,   42,   40,   38,   37,   36,   28,
 /*   390 */    29,   24,   25,   35,   34,   32,   30,   33,   31,   27,
 /*   400 */    26,   45,   42,   40,   38,   37,   36,  220,  220,  220,
 /*   410 */   220,  220,  220,  220,  220,  220,  220,  220,  220,  220,
 /*   420 */   106,  220,  220,  220,  220,  220,  220,   28,   29,   24,
 /*   430 */    25,   35,   34,   32,   30,   33,   31,   27,   26,   45,
 /*   440 */    42,   40,   38,   37,   36,   24,   25,   35,   34,   32,
 /*   450 */    30,   33,   31,   27,   26,   45,   42,   40,   38,   37,
 /*   460 */    36,   25,   35,   34,   32,   30,   33,   31,   27,   26,
 /*   470 */    45,   42,   40,   38,   37,   36,  220,  220,  220,   64,
 /*   480 */   220,  220,  220,  103,  102,  142,  141,  140,  139,   80,
 /*   490 */   220,   84,  110,  109,   81,  220,  220,  136,  146,  133,
 /*   500 */   132,  131,   35,   34,   32,   30,   33,   31,   27,   26,
 /*   510 */    45,   42,   40,   38,   37,   36,  220,   22,  220,  220,
 /*   520 */   220,  220,   21,   23,  220,   22,   39,  220,  220,  220,
 /*   530 */    21,   23,  145,   77,   39,  220,  220,  220,   90,  220,
 /*   540 */   101,   85,    2,   99,  128,  127,  126,  220,  101,  220,
 /*   550 */     2,   99,  128,  127,  126,  220,  220,  220,   22,  220,
 /*   560 */   220,  220,  220,   21,   23,  220,   22,   39,  220,  220,
 /*   570 */   220,   21,   23,  220,   85,   39,  138,  220,  220,   17,
 /*   580 */   220,  101,   85,    2,   99,  128,  127,  126,  220,  101,
 /*   590 */   220,    2,   99,  128,  127,  126,   22,  220,  220,  220,
 /*   600 */   220,   21,   23,  220,   22,   39,  137,  220,  220,   21,
 /*   610 */    23,  220,   85,   39,  121,  220,  220,  220,  220,  101,
 /*   620 */    85,    2,   99,  128,  127,  126,  220,  101,  220,    2,
 /*   630 */    99,  128,  127,  126,   22,  220,  220,  220,  220,   21,
 /*   640 */    23,  220,   22,   39,  122,  220,  220,   21,   23,  220,
 /*   650 */    85,   39,  124,  220,  220,  220,  220,  101,   85,    2,
 /*   660 */    99,  128,  127,  126,   64,  101,  220,    2,   99,  128,
 /*   670 */   127,  126,   22,  135,  220,    9,   84,   21,   23,  220,
 /*   680 */   220,   39,  136,   91,  133,  132,  131,  220,   85,  220,
 /*   690 */   220,  220,  220,  220,   64,  101,  220,    2,   99,  128,
 /*   700 */   127,  126,  220,  135,  220,    6,   84,  220,  220,   64,
 /*   710 */   220,  220,  136,  220,  133,  132,  131,  220,  135,  220,
 /*   720 */     8,   84,  220,   64,  220,  220,  220,  136,   64,  133,
 /*   730 */   132,  131,  135,  220,    7,   84,  220,  134,  220,  220,
 /*   740 */    84,  136,  220,  133,  132,  131,  136,   78,  133,  132,
 /*   750 */   131,  220,   62,  220,  220,  220,  220,  220,  220,   84,
 /*   760 */   220,  220,  220,  220,   84,  136,   63,  133,  132,  131,
 /*   770 */   136,  220,  133,  132,  131,  220,  220,  220,   84,   79,
 /*   780 */   220,  220,  220,  220,  136,  220,  133,  132,  131,  220,
 /*   790 */   220,   84,   61,  220,  220,  220,  220,  136,  220,  133,
 /*   800 */   132,  131,  220,  220,   84,  220,  220,  220,  220,  220,
 /*   810 */   136,   92,  133,  132,  131,  220,   60,  220,  220,  220,
 /*   820 */   220,  220,  220,   84,  220,  220,  220,  220,   84,  136,
 /*   830 */    98,  133,  132,  131,  136,  220,  133,  132,  131,  220,
 /*   840 */   220,  220,   84,   97,  220,  220,  220,  220,  136,  220,
 /*   850 */   133,  132,  131,  220,  220,   84,   96,  220,  220,  220,
 /*   860 */   220,  136,  220,  133,  132,  131,  220,  220,   84,  220,
 /*   870 */   220,  220,  220,  220,  136,   70,  133,  132,  131,  220,
 /*   880 */    69,  220,  220,  220,  220,  220,  220,   84,  220,  220,
 /*   890 */   220,  220,   84,  136,   74,  133,  132,  131,  136,  220,
 /*   900 */   133,  132,  131,  220,  220,  220,   84,   73,  220,  220,
 /*   910 */   220,  220,  136,  220,  133,  132,  131,  220,  220,   84,
 /*   920 */    72,  220,  220,  220,  220,  136,  220,  133,  132,  131,
 /*   930 */   220,  220,   84,  220,  220,  220,  220,  220,  136,   71,
 /*   940 */   133,  132,  131,  220,   66,  220,  220,  220,  220,  220,
 /*   950 */   220,   84,  220,  220,  220,  220,   84,  136,   65,  133,
 /*   960 */   132,  131,  136,  220,  133,  132,  131,  220,  220,  220,
 /*   970 */    84,   76,  220,  220,  220,  220,  136,  220,  133,  132,
 /*   980 */   131,  220,  220,   84,   75,  220,  220,  220,  220,  136,
 /*   990 */   220,  133,  132,  131,  220,  220,   84,  220,  220,  220,
 /*  1000 */   220,  220,  136,   68,  133,  132,  131,  220,   67,  220,
 /*  1010 */   220,  220,  220,  220,  220,   84,  220,  220,  220,  220,
 /*  1020 */    84,  136,   95,  133,  132,  131,  136,  220,  133,  132,
 /*  1030 */   131,  220,  220,  220,   84,   94,  220,  220,  220,  220,
 /*  1040 */   136,  220,  133,  132,  131,  220,  220,   84,   93,  220,
 /*  1050 */   220,  220,  220,  136,  220,  133,  132,  131,  220,  220,
 /*  1060 */    84,  220,  220,  220,  220,  220,  136,   59,  133,  132,
 /*  1070 */   131,  220,   57,  220,  220,  220,  220,  220,  220,   84,
 /*  1080 */   220,  220,  220,  220,   84,  136,   56,  133,  132,  131,
 /*  1090 */   136,  220,  133,  132,  131,  220,  220,  220,   84,   55,
 /*  1100 */   220,  220,  220,  220,  136,  220,  133,  132,  131,  220,
 /*  1110 */   220,   84,   53,  220,  220,  220,  220,  136,  220,  133,
 /*  1120 */   132,  131,  220,  220,   84,  220,  220,  220,  220,  220,
 /*  1130 */   136,   50,  133,  132,  131,  220,   52,  220,  220,  220,
 /*  1140 */   220,  220,  220,   84,  220,  220,  220,  220,   84,  136,
 /*  1150 */    49,  133,  132,  131,  136,  220,  133,  132,  131,  220,
 /*  1160 */   220,  220,   84,   51,  220,  220,  220,  220,  136,  220,
 /*  1170 */   133,  132,  131,  220,  220,   84,   58,  220,  220,  220,
 /*  1180 */   220,  136,  220,  133,  132,  131,  220,  220,   84,  220,
 /*  1190 */   220,  220,  220,  220,  136,   54,  133,  132,  131,  220,
 /*  1200 */   220,  220,  220,  220,  220,  220,  220,   84,  220,  220,
 /*  1210 */   220,  220,  220,  136,  220,  133,  132,  131,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*    10 */    16,   17,   18,   19,   20,   21,   22,   23,   16,   17,
 /*    20 */    18,   19,   20,   21,   22,   23,    1,   28,   34,   50,
 /*    30 */    31,   37,   53,   54,    1,    6,    7,    8,    9,   10,
 /*    40 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    50 */    21,   22,   23,   34,   18,   19,   20,   21,   22,   23,
 /*    60 */    35,   36,   28,   34,   34,   31,   37,   35,   35,    1,
 /*    70 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*    80 */    16,   17,   18,   19,   20,   21,   22,   23,    6,    7,
 /*    90 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   100 */    18,   19,   20,   21,   22,   23,   28,   43,   35,   36,
 /*   110 */    23,   29,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   120 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   130 */     1,   32,    1,   67,   68,   29,    6,    7,    8,    9,
 /*   140 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   150 */    20,   21,   22,   23,   28,    2,   34,   28,   37,    1,
 /*   160 */    31,   61,   32,    2,   35,   36,   35,   35,   61,    6,
 /*   170 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   180 */    17,   18,   19,   20,   21,   22,   23,   39,   49,   74,
 /*   190 */    20,   21,   22,   23,   74,   32,   74,    1,   74,   38,
 /*   200 */    74,   74,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   210 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   220 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   230 */    16,   17,   18,   19,   20,   21,   22,   23,   74,   74,
 /*   240 */    74,   74,   74,   74,   74,   74,   74,   74,   34,   74,
 /*   250 */    74,   74,   74,   74,   74,    6,    7,    8,    9,   10,
 /*   260 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   270 */    21,   22,   23,    7,    8,    9,   10,   11,   12,   13,
 /*   280 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   290 */    41,   74,   74,   74,   74,   74,   74,    6,    7,    8,
 /*   300 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   310 */    19,   20,   21,   22,   23,   12,   13,   14,   15,   16,
 /*   320 */    17,   18,   19,   20,   21,   22,   23,   36,   74,   74,
 /*   330 */    74,   74,   74,   74,    6,    7,    8,    9,   10,   11,
 /*   340 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   350 */    22,   23,   74,   74,   74,   74,   74,   74,   74,   74,
 /*   360 */    74,   74,   74,   74,   36,   74,    1,   74,   74,   74,
 /*   370 */    74,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   380 */    15,   16,   17,   18,   19,   20,   21,   22,   23,    6,
 /*   390 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   400 */    17,   18,   19,   20,   21,   22,   23,   74,   74,   74,
 /*   410 */    74,   74,   74,   74,   74,   74,   74,   74,   74,   74,
 /*   420 */    37,   74,   74,   74,   74,   74,   74,    6,    7,    8,
 /*   430 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   440 */    19,   20,   21,   22,   23,    8,    9,   10,   11,   12,
 /*   450 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   460 */    23,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   470 */    18,   19,   20,   21,   22,   23,   74,   74,   74,   51,
 /*   480 */    74,   74,   74,   55,   56,   57,   58,   59,   60,   61,
 /*   490 */    74,   63,   64,   65,   66,   74,   74,   69,    0,   71,
 /*   500 */    72,   73,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   510 */    18,   19,   20,   21,   22,   23,   74,   19,   74,   74,
 /*   520 */    74,   74,   24,   25,   74,   19,   28,   74,   74,   74,
 /*   530 */    24,   25,   34,   35,   28,   74,   74,   74,   32,   74,
 /*   540 */    42,   35,   44,   45,   46,   47,   48,   74,   42,   74,
 /*   550 */    44,   45,   46,   47,   48,   74,   74,   74,   19,   74,
 /*   560 */    74,   74,   74,   24,   25,   74,   19,   28,   74,   74,
 /*   570 */    74,   24,   25,   74,   35,   28,   29,   74,   74,   40,
 /*   580 */    74,   42,   35,   44,   45,   46,   47,   48,   74,   42,
 /*   590 */    74,   44,   45,   46,   47,   48,   19,   74,   74,   74,
 /*   600 */    74,   24,   25,   74,   19,   28,   29,   74,   74,   24,
 /*   610 */    25,   74,   35,   28,   29,   74,   74,   74,   74,   42,
 /*   620 */    35,   44,   45,   46,   47,   48,   74,   42,   74,   44,
 /*   630 */    45,   46,   47,   48,   19,   74,   74,   74,   74,   24,
 /*   640 */    25,   74,   19,   28,   29,   74,   74,   24,   25,   74,
 /*   650 */    35,   28,   29,   74,   74,   74,   74,   42,   35,   44,
 /*   660 */    45,   46,   47,   48,   51,   42,   74,   44,   45,   46,
 /*   670 */    47,   48,   19,   60,   74,   62,   63,   24,   25,   74,
 /*   680 */    74,   28,   69,   70,   71,   72,   73,   74,   35,   74,
 /*   690 */    74,   74,   74,   74,   51,   42,   74,   44,   45,   46,
 /*   700 */    47,   48,   74,   60,   74,   62,   63,   74,   74,   51,
 /*   710 */    74,   74,   69,   74,   71,   72,   73,   74,   60,   74,
 /*   720 */    62,   63,   74,   51,   74,   74,   74,   69,   51,   71,
 /*   730 */    72,   73,   60,   74,   62,   63,   74,   60,   74,   74,
 /*   740 */    63,   69,   74,   71,   72,   73,   69,   51,   71,   72,
 /*   750 */    73,   74,   51,   74,   74,   74,   74,   74,   74,   63,
 /*   760 */    74,   74,   74,   74,   63,   69,   51,   71,   72,   73,
 /*   770 */    69,   74,   71,   72,   73,   74,   74,   74,   63,   51,
 /*   780 */    74,   74,   74,   74,   69,   74,   71,   72,   73,   74,
 /*   790 */    74,   63,   51,   74,   74,   74,   74,   69,   74,   71,
 /*   800 */    72,   73,   74,   74,   63,   74,   74,   74,   74,   74,
 /*   810 */    69,   51,   71,   72,   73,   74,   51,   74,   74,   74,
 /*   820 */    74,   74,   74,   63,   74,   74,   74,   74,   63,   69,
 /*   830 */    51,   71,   72,   73,   69,   74,   71,   72,   73,   74,
 /*   840 */    74,   74,   63,   51,   74,   74,   74,   74,   69,   74,
 /*   850 */    71,   72,   73,   74,   74,   63,   51,   74,   74,   74,
 /*   860 */    74,   69,   74,   71,   72,   73,   74,   74,   63,   74,
 /*   870 */    74,   74,   74,   74,   69,   51,   71,   72,   73,   74,
 /*   880 */    51,   74,   74,   74,   74,   74,   74,   63,   74,   74,
 /*   890 */    74,   74,   63,   69,   51,   71,   72,   73,   69,   74,
 /*   900 */    71,   72,   73,   74,   74,   74,   63,   51,   74,   74,
 /*   910 */    74,   74,   69,   74,   71,   72,   73,   74,   74,   63,
 /*   920 */    51,   74,   74,   74,   74,   69,   74,   71,   72,   73,
 /*   930 */    74,   74,   63,   74,   74,   74,   74,   74,   69,   51,
 /*   940 */    71,   72,   73,   74,   51,   74,   74,   74,   74,   74,
 /*   950 */    74,   63,   74,   74,   74,   74,   63,   69,   51,   71,
 /*   960 */    72,   73,   69,   74,   71,   72,   73,   74,   74,   74,
 /*   970 */    63,   51,   74,   74,   74,   74,   69,   74,   71,   72,
 /*   980 */    73,   74,   74,   63,   51,   74,   74,   74,   74,   69,
 /*   990 */    74,   71,   72,   73,   74,   74,   63,   74,   74,   74,
 /*  1000 */    74,   74,   69,   51,   71,   72,   73,   74,   51,   74,
 /*  1010 */    74,   74,   74,   74,   74,   63,   74,   74,   74,   74,
 /*  1020 */    63,   69,   51,   71,   72,   73,   69,   74,   71,   72,
 /*  1030 */    73,   74,   74,   74,   63,   51,   74,   74,   74,   74,
 /*  1040 */    69,   74,   71,   72,   73,   74,   74,   63,   51,   74,
 /*  1050 */    74,   74,   74,   69,   74,   71,   72,   73,   74,   74,
 /*  1060 */    63,   74,   74,   74,   74,   74,   69,   51,   71,   72,
 /*  1070 */    73,   74,   51,   74,   74,   74,   74,   74,   74,   63,
 /*  1080 */    74,   74,   74,   74,   63,   69,   51,   71,   72,   73,
 /*  1090 */    69,   74,   71,   72,   73,   74,   74,   74,   63,   51,
 /*  1100 */    74,   74,   74,   74,   69,   74,   71,   72,   73,   74,
 /*  1110 */    74,   63,   51,   74,   74,   74,   74,   69,   74,   71,
 /*  1120 */    72,   73,   74,   74,   63,   74,   74,   74,   74,   74,
 /*  1130 */    69,   51,   71,   72,   73,   74,   51,   74,   74,   74,
 /*  1140 */    74,   74,   74,   63,   74,   74,   74,   74,   63,   69,
 /*  1150 */    51,   71,   72,   73,   69,   74,   71,   72,   73,   74,
 /*  1160 */    74,   74,   63,   51,   74,   74,   74,   74,   69,   74,
 /*  1170 */    71,   72,   73,   74,   74,   63,   51,   74,   74,   74,
 /*  1180 */    74,   69,   74,   71,   72,   73,   74,   74,   63,   74,
 /*  1190 */    74,   74,   74,   74,   69,   51,   71,   72,   73,   74,
 /*  1200 */    74,   74,   74,   74,   74,   74,   74,   63,   74,   74,
 /*  1210 */    74,   74,   74,   69,   74,   71,   72,   73,
};
#define YY_SHIFT_USE_DFLT (-7)
#define YY_SHIFT_COUNT (103)
#define YY_SHIFT_MIN   (-6)
#define YY_SHIFT_MAX   (653)
static const short yy_shift_ofst[] = {
 /*     0 */   139,  498,  653,  623,  615,  653,  585,  577,  547,  653,
 /*    10 */   539,  506,  653,  653,  653,  653,  653,  653,  653,  653,
 /*    20 */   653,  653,  653,  653,  653,  653,  653,  653,  653,  653,
 /*    30 */   653,  653,  653,  653,  653,  653,  653,  653,  653,  653,
 /*    40 */   653,  653,  653,  653,  653,  653,  148,   73,  132,   29,
 /*    50 */    -6,  383,  365,  328,  291,  249,  214,  196,  163,  130,
 /*    60 */   106,   82,   64,  421,  421,  266,  437,  452,  492,  303,
 /*    70 */   303,    2,    2,    2,    2,   36,   36,  129,  170,  170,
 /*    80 */    25,  161,  131,   33,   34,   -1,  158,  121,  122,  153,
 /*    90 */   126,   99,   87,   87,   87,   87,   87,   87,   87,   78,
 /*   100 */    68,   32,   30,   19,
};
#define YY_REDUCE_USE_DFLT (-22)
#define YY_REDUCE_COUNT (48)
#define YY_REDUCE_MIN   (-21)
#define YY_REDUCE_MAX   (1144)
static const short yy_reduce_ofst[] = {
 /*     0 */   -21,  428,  613,  672,  658,  643,  677,  677,  677,  677,
 /*    10 */  1144, 1125, 1112, 1099, 1085, 1080, 1061, 1048, 1035, 1021,
 /*    20 */  1016,  997,  984,  971,  957,  952,  933,  920,  907,  893,
 /*    30 */   888,  869,  856,  843,  829,  824,  805,  792,  779,  765,
 /*    40 */   760,  741,  728,  715,  701,  696,   66,  107,  100,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   147,  218,  182,  218,  218,  218,  218,  218,  218,  183,
 /*    10 */   218,  218,  218,  218,  218,  218,  218,  218,  218,  218,
 /*    20 */   218,  218,  218,  218,  218,  218,  218,  218,  218,  218,
 /*    30 */   218,  218,  218,  218,  218,  218,  218,  218,  218,  218,
 /*    40 */   218,  218,  218,  218,  218,  218,  218,  218,  218,  218,
 /*    50 */   218,  218,  218,  218,  176,  218,  218,  218,  218,  218,
 /*    60 */   218,  218,  218,  175,  155,  205,  204,  212,  211,  199,
 /*    70 */   198,  203,  202,  201,  200,  210,  209,  158,  192,  193,
 /*    80 */   218,  218,  218,  218,  215,  158,  218,  218,  218,  218,
 /*    90 */   218,  218,  194,  208,  207,  206,  197,  196,  195,  218,
 /*   100 */   218,  218,  218,  218,  217,  216,  169,  168,  167,  165,
 /*   110 */   164,  177,  173,  172,  170,  157,  171,  174,  166,  156,
 /*   120 */   213,  160,  162,  214,  163,  181,  191,  190,  189,  188,
 /*   130 */   187,  186,  185,  184,  179,  178,  180,  161,  159,  154,
 /*   140 */   153,  152,  151,  150,  149,  148,
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
  "case_statement",  "final_guard_statement",  "guard_statement",  "where_statement",
  "final_where_statement",  "array",         "maybe_empty_stmt_list",  "num",         
  "string",        "bool",        
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
 /*  24 */ "where_statement ::= WHERE LCURL",
 /*  25 */ "where_statement ::= WHERE name_chain ASSIGN expr LCURL",
 /*  26 */ "where_statement ::= where_statement name_chain ASSIGN expr DELIMITER",
 /*  27 */ "final_where_statement ::= where_statement name_chain ASSIGN expr RCURL DELIMITER RCURL",
 /*  28 */ "case_statement ::= name_chain ASSIGN CASE expr OF",
 /*  29 */ "expr ::= LET NAME ASSIGN expr IN expr",
 /*  30 */ "assignment ::= name_chain ASSIGN expr",
 /*  31 */ "assignment ::= name_chain ASSIGN expr LCURL final_where_statement",
 /*  32 */ "stmt_list ::= stmt",
 /*  33 */ "stmt_list ::= stmt_list stmt",
 /*  34 */ "expr ::= array",
 /*  35 */ "array ::= OPENBRAC maybe_empty_stmt_list RBRAC",
 /*  36 */ "maybe_empty_stmt_list ::=",
 /*  37 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  38 */ "expr ::= num",
 /*  39 */ "expr ::= string",
 /*  40 */ "expr ::= bool",
 /*  41 */ "expr ::= PRINT LPAREN expr RPAREN",
 /*  42 */ "expr ::= LPAREN expr RPAREN",
 /*  43 */ "num ::= NUM",
 /*  44 */ "string ::= STRING",
 /*  45 */ "bool ::= BOOLEAN",
 /*  46 */ "expr ::= expr PLUS expr",
 /*  47 */ "expr ::= expr MINUS expr",
 /*  48 */ "expr ::= expr DIVIDE expr",
 /*  49 */ "expr ::= expr TIMES expr",
 /*  50 */ "expr ::= expr MODULO expr",
 /*  51 */ "expr ::= expr POW expr",
 /*  52 */ "expr ::= expr EQUALTO expr",
 /*  53 */ "expr ::= expr NOTEQUALTO expr",
 /*  54 */ "expr ::= expr LESSTHAN expr",
 /*  55 */ "expr ::= expr GREATERTHAN expr",
 /*  56 */ "expr ::= expr LORE expr",
 /*  57 */ "expr ::= expr GORE expr",
 /*  58 */ "expr ::= expr AND expr",
 /*  59 */ "expr ::= expr OR expr",
 /*  60 */ "expr ::= BITNOT expr",
 /*  61 */ "expr ::= MINUS expr",
 /*  62 */ "expr ::= NOT expr",
 /*  63 */ "expr ::= expr SHIFTL expr",
 /*  64 */ "expr ::= expr SHIFTR expr",
 /*  65 */ "expr ::= expr BITAND expr",
 /*  66 */ "expr ::= expr BITXOR expr",
 /*  67 */ "array_index ::= NAME LBRAC expr RBRAC",
 /*  68 */ "array_index ::= array_index LBRAC expr RBRAC",
 /*  69 */ "expr ::= array_index",
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
#line 829 "./src/Grammar/grammar.c"
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
  { 67, 2 },
  { 67, 5 },
  { 67, 5 },
  { 68, 7 },
  { 64, 5 },
  { 51, 6 },
  { 58, 3 },
  { 58, 5 },
  { 62, 1 },
  { 62, 2 },
  { 51, 1 },
  { 69, 3 },
  { 70, 0 },
  { 70, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 4 },
  { 51, 3 },
  { 71, 1 },
  { 72, 1 },
  { 73, 1 },
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
#line 1200 "./src/Grammar/grammar.c"
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
#line 1223 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= assignment */
      case 18: /* test ::= case_statement */ yytestcase(yyruleno==18);
#line 111 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1231 "./src/Grammar/grammar.c"
        break;
      case 7: /* spec ::= top_stmt */
      case 8: /* top_stmt ::= stmt */ yytestcase(yyruleno==8);
#line 116 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1240 "./src/Grammar/grammar.c"
        break;
      case 9: /* stmt ::= expr */
      case 32: /* stmt_list ::= stmt */ yytestcase(yyruleno==32);
#line 128 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1249 "./src/Grammar/grammar.c"
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
#line 1288 "./src/Grammar/grammar.c"
        break;
      case 11: /* name_chain ::= NAME */
#line 171 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1297 "./src/Grammar/grammar.c"
        break;
      case 12: /* expr ::= NAME */
#line 178 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = optic::UNDECLARED_VARIABLE;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1310 "./src/Grammar/grammar.c"
        break;
      case 13: /* expr ::= NAME LPAREN stmt_list RPAREN */
#line 194 "./src/Grammar/grammar.y"
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
#line 1342 "./src/Grammar/grammar.c"
        break;
      case 14: /* expr ::= NAME LBRAC RBRAC LPAREN stmt_list RPAREN */
#line 222 "./src/Grammar/grammar.y"
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
        yymsp[-1].minor.yy0.data.array->reserve(1);
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
  yy_destructor(yypParser,31,&yymsp[-4].minor);
  yy_destructor(yypParser,32,&yymsp[-3].minor);
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1376 "./src/Grammar/grammar.c"
        break;
      case 15: /* expr ::= array_index LPAREN stmt_list RPAREN */
#line 250 "./src/Grammar/grammar.y"
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
#line 1402 "./src/Grammar/grammar.c"
        break;
      case 16: /* expr ::= NAME LPAREN RPAREN */
#line 273 "./src/Grammar/grammar.y"
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
#line 1417 "./src/Grammar/grammar.c"
        break;
      case 17: /* expr ::= array_index LPAREN RPAREN */
#line 284 "./src/Grammar/grammar.y"
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
#line 1432 "./src/Grammar/grammar.c"
        break;
      case 19: /* assignment ::= final_guard_statement */
#line 307 "./src/Grammar/grammar.y"
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
#line 1453 "./src/Grammar/grammar.c"
        break;
      case 20: /* guard_statement ::= name_chain LCURL BITOR expr ASSIGN expr DELIMITER */
#line 327 "./src/Grammar/grammar.y"
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
#line 1467 "./src/Grammar/grammar.c"
        break;
      case 21: /* guard_statement ::= guard_statement BITOR expr ASSIGN expr DELIMITER */
#line 335 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD3" << std::endl;
    add_branch_to_tree(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-5].minor.yy0;
    std::cout << "GUARD4" << std::endl;
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1480 "./src/Grammar/grammar.c"
        break;
      case 22: /* final_guard_statement ::= guard_statement BITOR expr ASSIGN expr RCURL */
#line 343 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD5" << std::endl;
    add_branch_to_tree(yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-5].minor.yy0;
    std::cout << "GUARD6" << std::endl;
  yy_destructor(yypParser,2,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,37,&yymsp[0].minor);
}
#line 1493 "./src/Grammar/grammar.c"
        break;
      case 23: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr RCURL */
#line 351 "./src/Grammar/grammar.y"
{
    std::cout << "GUARD7" << std::endl;
    add_wildcard_to_tree(yymsp[-4].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0=yymsp[-4].minor.yy0;
    std::cout << "GUARD8" << std::endl;
  yy_destructor(yypParser,38,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,37,&yymsp[0].minor);
}
#line 1506 "./src/Grammar/grammar.c"
        break;
      case 24: /* where_statement ::= WHERE LCURL */
#line 364 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::NIL;
    std::cout << "Where 1" << std::endl;
  yy_destructor(yypParser,39,&yymsp[-1].minor);
  yy_destructor(yypParser,36,&yymsp[0].minor);
}
#line 1516 "./src/Grammar/grammar.c"
        break;
      case 25: /* where_statement ::= WHERE name_chain ASSIGN expr LCURL */
#line 370 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,39,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,36,&yymsp[0].minor);
}
#line 1534 "./src/Grammar/grammar.c"
        break;
      case 26: /* where_statement ::= where_statement name_chain ASSIGN expr DELIMITER */
#line 383 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1561 "./src/Grammar/grammar.c"
        break;
      case 27: /* final_where_statement ::= where_statement name_chain ASSIGN expr RCURL DELIMITER RCURL */
#line 406 "./src/Grammar/grammar.y"
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
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[-1].minor);
  yy_destructor(yypParser,37,&yymsp[0].minor);
}
#line 1589 "./src/Grammar/grammar.c"
        break;
      case 28: /* case_statement ::= name_chain ASSIGN CASE expr OF */
#line 428 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,40,&yymsp[-2].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1600 "./src/Grammar/grammar.c"
        break;
      case 29: /* expr ::= LET NAME ASSIGN expr IN expr */
#line 434 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Let");
  yy_destructor(yypParser,42,&yymsp[-5].minor);
  yy_destructor(yypParser,35,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,43,&yymsp[-1].minor);
}
#line 1612 "./src/Grammar/grammar.c"
        break;
      case 30: /* assignment ::= name_chain ASSIGN expr */
#line 440 "./src/Grammar/grammar.y"
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
#line 1627 "./src/Grammar/grammar.c"
        break;
      case 31: /* assignment ::= name_chain ASSIGN expr LCURL final_where_statement */
#line 453 "./src/Grammar/grammar.y"
{
    std::cout << "Where assign" << std::endl;
    yymsp[-4].minor.yy0.type = optic::FUNCTION_ARG_NAMES;
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
  yy_destructor(yypParser,36,&yymsp[-1].minor);
}
#line 1646 "./src/Grammar/grammar.c"
        break;
      case 33: /* stmt_list ::= stmt_list stmt */
#line 478 "./src/Grammar/grammar.y"
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
#line 1664 "./src/Grammar/grammar.c"
        break;
      case 34: /* expr ::= array */
      case 69: /* expr ::= array_index */ yytestcase(yyruleno==69);
#line 496 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1672 "./src/Grammar/grammar.c"
        break;
      case 35: /* array ::= OPENBRAC maybe_empty_stmt_list RBRAC */
#line 501 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yygotominor.yy0.type = optic::ARRAY;
  yy_destructor(yypParser,44,&yymsp[-2].minor);
  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1682 "./src/Grammar/grammar.c"
        break;
      case 36: /* maybe_empty_stmt_list ::= */
#line 507 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1690 "./src/Grammar/grammar.c"
        break;
      case 37: /* maybe_empty_stmt_list ::= stmt_list */
#line 513 "./src/Grammar/grammar.y"
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
#line 1706 "./src/Grammar/grammar.c"
        break;
      case 38: /* expr ::= num */
      case 40: /* expr ::= bool */ yytestcase(yyruleno==40);
#line 531 "./src/Grammar/grammar.y"
{
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1714 "./src/Grammar/grammar.c"
        break;
      case 39: /* expr ::= string */
#line 536 "./src/Grammar/grammar.y"
{
   create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1721 "./src/Grammar/grammar.c"
        break;
      case 41: /* expr ::= PRINT LPAREN expr RPAREN */
#line 550 "./src/Grammar/grammar.y"
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
#line 1736 "./src/Grammar/grammar.c"
        break;
      case 42: /* expr ::= LPAREN expr RPAREN */
#line 560 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1745 "./src/Grammar/grammar.c"
        break;
      case 43: /* num ::= NUM */
#line 565 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1753 "./src/Grammar/grammar.c"
        break;
      case 44: /* string ::= STRING */
#line 571 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::STRING;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1761 "./src/Grammar/grammar.c"
        break;
      case 45: /* bool ::= BOOLEAN */
#line 578 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::BOOL;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1769 "./src/Grammar/grammar.c"
        break;
      case 46: /* expr ::= expr PLUS expr */
#line 588 "./src/Grammar/grammar.y"
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
#line 1784 "./src/Grammar/grammar.c"
        break;
      case 47: /* expr ::= expr MINUS expr */
#line 600 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1797 "./src/Grammar/grammar.c"
        break;
      case 48: /* expr ::= expr DIVIDE expr */
#line 610 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1810 "./src/Grammar/grammar.c"
        break;
      case 49: /* expr ::= expr TIMES expr */
#line 620 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1823 "./src/Grammar/grammar.c"
        break;
      case 50: /* expr ::= expr MODULO expr */
#line 630 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1836 "./src/Grammar/grammar.c"
        break;
      case 51: /* expr ::= expr POW expr */
#line 640 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1849 "./src/Grammar/grammar.c"
        break;
      case 52: /* expr ::= expr EQUALTO expr */
#line 650 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1862 "./src/Grammar/grammar.c"
        break;
      case 53: /* expr ::= expr NOTEQUALTO expr */
#line 660 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1875 "./src/Grammar/grammar.c"
        break;
      case 54: /* expr ::= expr LESSTHAN expr */
#line 670 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1888 "./src/Grammar/grammar.c"
        break;
      case 55: /* expr ::= expr GREATERTHAN expr */
#line 680 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1901 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr LORE expr */
#line 690 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1914 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr GORE expr */
#line 700 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1927 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= expr AND expr */
#line 710 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1940 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= expr OR expr */
#line 720 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1953 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= BITNOT expr */
#line 730 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,25,&yymsp[-1].minor);
}
#line 1966 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= MINUS expr */
#line 740 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1979 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= NOT expr */
#line 750 "./src/Grammar/grammar.y"
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
#line 1993 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= expr SHIFTL expr */
#line 761 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 2006 "./src/Grammar/grammar.c"
        break;
      case 64: /* expr ::= expr SHIFTR expr */
#line 771 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 2019 "./src/Grammar/grammar.c"
        break;
      case 65: /* expr ::= expr BITAND expr */
#line 781 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 2032 "./src/Grammar/grammar.c"
        break;
      case 66: /* expr ::= expr BITXOR expr */
#line 791 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 2045 "./src/Grammar/grammar.c"
        break;
      case 67: /* array_index ::= NAME LBRAC expr RBRAC */
#line 801 "./src/Grammar/grammar.y"
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
#line 2060 "./src/Grammar/grammar.c"
        break;
      case 68: /* array_index ::= array_index LBRAC expr RBRAC */
#line 812 "./src/Grammar/grammar.y"
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
#line 2074 "./src/Grammar/grammar.c"
        break;
      case 70: /* in ::= error */
#line 831 "./src/Grammar/grammar.y"
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
#line 2089 "./src/Grammar/grammar.c"
        break;
      case 71: /* error ::= OPENQUOTEERROR */
#line 844 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy149 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 2098 "./src/Grammar/grammar.c"
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
#line 2165 "./src/Grammar/grammar.c"
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
#line 2187 "./src/Grammar/grammar.c"
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
