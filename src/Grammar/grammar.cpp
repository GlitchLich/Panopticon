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
#define YYNSTATE 140
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
#define YY_ACTTAB_COUNT (853)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    30,   31,   26,   27,   37,   36,   34,   32,   35,   33,
 /*    10 */    29,   28,   47,   44,   42,   40,   39,   38,   30,   31,
 /*    20 */    26,   27,   37,   36,   34,   32,   35,   33,   29,   28,
 /*    30 */    47,   44,   42,   40,   39,   38,   42,   40,   39,   38,
 /*    40 */    45,  125,   21,   19,   95,   94,   30,   31,   26,   27,
 /*    50 */    37,   36,   34,   32,   35,   33,   29,   28,   47,   44,
 /*    60 */    42,   40,   39,   38,   21,   19,   95,   94,  112,  124,
 /*    70 */   110,  116,   85,  214,    1,   30,   31,   26,   27,   37,
 /*    80 */    36,   34,   32,   35,   33,   29,   28,   47,   44,   42,
 /*    90 */    40,   39,   38,   29,   28,   47,   44,   42,   40,   39,
 /*   100 */    38,  118,    3,   20,  138,   22,  137,   30,   31,   26,
 /*   110 */    27,   37,   36,   34,   32,   35,   33,   29,   28,   47,
 /*   120 */    44,   42,   40,   39,   38,   18,  105,   46,   43,   30,
 /*   130 */    31,   26,   27,   37,   36,   34,   32,   35,   33,   29,
 /*   140 */    28,   47,   44,   42,   40,   39,   38,   14,  120,   38,
 /*   150 */    17,   30,   31,   26,   27,   37,   36,   34,   32,   35,
 /*   160 */    33,   29,   28,   47,   44,   42,   40,   39,   38,   12,
 /*   170 */    16,    8,   91,   30,   31,   26,   27,   37,   36,   34,
 /*   180 */    32,   35,   33,   29,   28,   47,   44,   42,   40,   39,
 /*   190 */    38,   30,   31,   26,   27,   37,   36,   34,   32,   35,
 /*   200 */    33,   29,   28,   47,   44,   42,   40,   39,   38,   26,
 /*   210 */    27,   37,   36,   34,   32,   35,   33,   29,   28,   47,
 /*   220 */    44,   42,   40,   39,   38,  115,    7,  111,  109,  215,
 /*   230 */   215,   30,   31,   26,   27,   37,   36,   34,   32,   35,
 /*   240 */    33,   29,   28,   47,   44,   42,   40,   39,   38,   30,
 /*   250 */    31,   26,   27,   37,   36,   34,   32,   35,   33,   29,
 /*   260 */    28,   47,   44,   42,   40,   39,   38,  114,   30,   31,
 /*   270 */    26,   27,   37,   36,   34,   32,   35,   33,   29,   28,
 /*   280 */    47,   44,   42,   40,   39,   38,  215,    9,   31,   26,
 /*   290 */    27,   37,   36,   34,   32,   35,   33,   29,   28,   47,
 /*   300 */    44,   42,   40,   39,   38,   70,  215,  215,  215,  108,
 /*   310 */   107,  136,  135,  134,  133,   48,  215,   88,   92,  113,
 /*   320 */    90,   84,  131,  215,  128,  127,  126,   27,   37,   36,
 /*   330 */    34,   32,   35,   33,   29,   28,   47,   44,   42,   40,
 /*   340 */    39,   38,  140,   37,   36,   34,   32,   35,   33,   29,
 /*   350 */    28,   47,   44,   42,   40,   39,   38,  215,  215,   93,
 /*   360 */    24,  215,    6,   70,   10,   23,   25,  215,  215,   41,
 /*   370 */   215,  215,  130,  215,    5,  139,   81,   15,   13,  215,
 /*   380 */   131,   96,  128,  127,  126,  215,  106,  215,    2,  104,
 /*   390 */   123,  122,  121,  215,  215,  117,   15,   13,   34,   32,
 /*   400 */    35,   33,   29,   28,   47,   44,   42,   40,   39,   38,
 /*   410 */    24,  215,  215,  215,  215,   23,   25,  215,   24,   41,
 /*   420 */   215,  215,  215,   23,   25,  215,   89,   41,  132,  215,
 /*   430 */   215,  215,   11,  215,   89,  215,  106,  215,    2,  104,
 /*   440 */   123,  122,  121,  215,  106,  215,    2,  104,  123,  122,
 /*   450 */   121,   24,  215,  215,  215,  215,   23,   25,  215,   24,
 /*   460 */    41,  119,  215,  215,   23,   25,  215,   89,   41,   47,
 /*   470 */    44,   42,   40,   39,   38,   89,  215,  106,   86,    2,
 /*   480 */   104,  123,  122,  121,  215,  106,  215,    2,  104,  123,
 /*   490 */   122,  121,   70,  151,  215,  131,  215,  128,  127,  126,
 /*   500 */   215,  130,  215,    4,  215,  215,  215,  215,  215,  131,
 /*   510 */   215,  128,  127,  126,   70,  215,  215,  215,  215,    3,
 /*   520 */   215,   59,   22,  129,  215,  215,  151,  151,  151,   69,
 /*   530 */   215,  131,  215,  128,  127,  126,   87,  215,  131,  215,
 /*   540 */   128,  127,  126,   58,  215,  215,  131,  215,  128,  127,
 /*   550 */   126,   97,  215,  131,  215,  128,  127,  126,  215,  215,
 /*   560 */   131,  215,  128,  127,  126,   57,  215,  215,  131,  215,
 /*   570 */   128,  127,  126,  103,  215,  215,  215,  215,  215,  215,
 /*   580 */   102,  215,  131,  215,  128,  127,  126,  101,  215,  215,
 /*   590 */   131,  215,  128,  127,  126,   76,  215,  131,  215,  128,
 /*   600 */   127,  126,   75,  215,  131,  215,  128,  127,  126,   80,
 /*   610 */   215,  215,  131,  215,  128,  127,  126,   79,  215,  131,
 /*   620 */   215,  128,  127,  126,   78,  215,  131,  215,  128,  127,
 /*   630 */   126,  215,  215,  215,  131,  215,  128,  127,  126,   77,
 /*   640 */   215,  131,  215,  128,  127,  126,   72,  215,  215,  215,
 /*   650 */   215,   71,  215,  215,  215,  215,  131,  215,  128,  127,
 /*   660 */   126,   83,  215,  131,  215,  128,  127,  126,  131,   82,
 /*   670 */   128,  127,  126,  215,  215,   74,  215,  215,  131,  215,
 /*   680 */   128,  127,  126,   73,  215,  215,  131,  215,  128,  127,
 /*   690 */   126,  100,  131,  215,  128,  127,  126,   99,  215,  215,
 /*   700 */   131,  215,  128,  127,  126,   98,  215,  215,  131,  215,
 /*   710 */   128,  127,  126,   56,  131,  215,  128,  127,  126,   55,
 /*   720 */   215,  215,  131,  215,  128,  127,  126,  215,  215,   68,
 /*   730 */   131,  215,  128,  127,  126,   54,  131,  215,  128,  127,
 /*   740 */   126,  215,   67,  215,  215,  215,  131,  215,  128,  127,
 /*   750 */   126,   66,  131,  215,  128,  127,  126,   65,  215,  131,
 /*   760 */   215,  128,  127,  126,   53,  215,  215,  215,  131,  215,
 /*   770 */   128,  127,  126,   64,  131,  215,  128,  127,  126,   52,
 /*   780 */   215,  131,  215,  128,  127,  126,   63,  215,  215,  215,
 /*   790 */   131,  215,  128,  127,  126,  215,  131,  215,  128,  127,
 /*   800 */   126,  215,   50,  131,  215,  128,  127,  126,   49,  215,
 /*   810 */   215,  215,  215,   62,  215,  215,  215,  215,   61,  131,
 /*   820 */   215,  128,  127,  126,   60,  131,  215,  128,  127,  126,
 /*   830 */   131,   51,  128,  127,  126,  131,  215,  128,  127,  126,
 /*   840 */   215,  131,  215,  128,  127,  126,  215,  215,  131,  215,
 /*   850 */   128,  127,  126,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    10 */    15,   16,   17,   18,   19,   20,   21,   22,    5,    6,
 /*    20 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*    30 */    17,   18,   19,   20,   21,   22,   19,   20,   21,   22,
 /*    40 */    45,   28,   35,   36,   37,   38,    5,    6,    7,    8,
 /*    50 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*    60 */    19,   20,   21,   22,   35,   36,   37,   38,   39,   28,
 /*    70 */    52,   68,   69,   55,   56,    5,    6,    7,    8,    9,
 /*    80 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*    90 */    20,   21,   22,   15,   16,   17,   18,   19,   20,   21,
 /*   100 */    22,   31,   27,    1,   33,   30,   33,    5,    6,    7,
 /*   110 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   120 */    18,   19,   20,   21,   22,    1,   34,    1,   27,    5,
 /*   130 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   140 */    16,   17,   18,   19,   20,   21,   22,    1,   31,   22,
 /*   150 */     1,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   160 */    14,   15,   16,   17,   18,   19,   20,   21,   22,    1,
 /*   170 */     1,   43,   34,    5,    6,    7,    8,    9,   10,   11,
 /*   180 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   190 */    22,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   200 */    14,   15,   16,   17,   18,   19,   20,   21,   22,    7,
 /*   210 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   220 */    18,   19,   20,   21,   22,   39,    1,   39,   51,   75,
 /*   230 */    75,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   240 */    14,   15,   16,   17,   18,   19,   20,   21,   22,    5,
 /*   250 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   260 */    16,   17,   18,   19,   20,   21,   22,   41,    5,    6,
 /*   270 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   280 */    17,   18,   19,   20,   21,   22,   75,   43,    6,    7,
 /*   290 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   300 */    18,   19,   20,   21,   22,   53,   75,   75,   75,   57,
 /*   310 */    58,   59,   60,   61,   62,   63,   75,   65,   66,   67,
 /*   320 */    68,   69,   70,   75,   72,   73,   74,    8,    9,   10,
 /*   330 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   340 */    21,   22,    0,    9,   10,   11,   12,   13,   14,   15,
 /*   350 */    16,   17,   18,   19,   20,   21,   22,   75,   75,   37,
 /*   360 */    18,   75,    1,   53,   42,   23,   24,   75,   75,   27,
 /*   370 */    75,   75,   62,   75,   64,   33,   34,   35,   36,   75,
 /*   380 */    70,   71,   72,   73,   74,   75,   44,   75,   46,   47,
 /*   390 */    48,   49,   50,   75,   75,   34,   35,   36,   11,   12,
 /*   400 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   410 */    18,   75,   75,   75,   75,   23,   24,   75,   18,   27,
 /*   420 */    75,   75,   75,   23,   24,   75,   34,   27,   28,   75,
 /*   430 */    75,   75,   40,   75,   34,   75,   44,   75,   46,   47,
 /*   440 */    48,   49,   50,   75,   44,   75,   46,   47,   48,   49,
 /*   450 */    50,   18,   75,   75,   75,   75,   23,   24,   75,   18,
 /*   460 */    27,   28,   75,   75,   23,   24,   75,   34,   27,   17,
 /*   470 */    18,   19,   20,   21,   22,   34,   75,   44,   53,   46,
 /*   480 */    47,   48,   49,   50,   75,   44,   75,   46,   47,   48,
 /*   490 */    49,   50,   53,    1,   75,   70,   75,   72,   73,   74,
 /*   500 */    75,   62,   75,   64,   75,   75,   75,   75,   75,   70,
 /*   510 */    75,   72,   73,   74,   53,   75,   75,   75,   75,   27,
 /*   520 */    75,   53,   30,   62,   75,   75,   34,   35,   36,   53,
 /*   530 */    75,   70,   75,   72,   73,   74,   53,   75,   70,   75,
 /*   540 */    72,   73,   74,   53,   75,   75,   70,   75,   72,   73,
 /*   550 */    74,   53,   75,   70,   75,   72,   73,   74,   75,   75,
 /*   560 */    70,   75,   72,   73,   74,   53,   75,   75,   70,   75,
 /*   570 */    72,   73,   74,   53,   75,   75,   75,   75,   75,   75,
 /*   580 */    53,   75,   70,   75,   72,   73,   74,   53,   75,   75,
 /*   590 */    70,   75,   72,   73,   74,   53,   75,   70,   75,   72,
 /*   600 */    73,   74,   53,   75,   70,   75,   72,   73,   74,   53,
 /*   610 */    75,   75,   70,   75,   72,   73,   74,   53,   75,   70,
 /*   620 */    75,   72,   73,   74,   53,   75,   70,   75,   72,   73,
 /*   630 */    74,   75,   75,   75,   70,   75,   72,   73,   74,   53,
 /*   640 */    75,   70,   75,   72,   73,   74,   53,   75,   75,   75,
 /*   650 */    75,   53,   75,   75,   75,   75,   70,   75,   72,   73,
 /*   660 */    74,   53,   75,   70,   75,   72,   73,   74,   70,   53,
 /*   670 */    72,   73,   74,   75,   75,   53,   75,   75,   70,   75,
 /*   680 */    72,   73,   74,   53,   75,   75,   70,   75,   72,   73,
 /*   690 */    74,   53,   70,   75,   72,   73,   74,   53,   75,   75,
 /*   700 */    70,   75,   72,   73,   74,   53,   75,   75,   70,   75,
 /*   710 */    72,   73,   74,   53,   70,   75,   72,   73,   74,   53,
 /*   720 */    75,   75,   70,   75,   72,   73,   74,   75,   75,   53,
 /*   730 */    70,   75,   72,   73,   74,   53,   70,   75,   72,   73,
 /*   740 */    74,   75,   53,   75,   75,   75,   70,   75,   72,   73,
 /*   750 */    74,   53,   70,   75,   72,   73,   74,   53,   75,   70,
 /*   760 */    75,   72,   73,   74,   53,   75,   75,   75,   70,   75,
 /*   770 */    72,   73,   74,   53,   70,   75,   72,   73,   74,   53,
 /*   780 */    75,   70,   75,   72,   73,   74,   53,   75,   75,   75,
 /*   790 */    70,   75,   72,   73,   74,   75,   70,   75,   72,   73,
 /*   800 */    74,   75,   53,   70,   75,   72,   73,   74,   53,   75,
 /*   810 */    75,   75,   75,   53,   75,   75,   75,   75,   53,   70,
 /*   820 */    75,   72,   73,   74,   53,   70,   75,   72,   73,   74,
 /*   830 */    70,   53,   72,   73,   74,   70,   75,   72,   73,   74,
 /*   840 */    75,   70,   75,   72,   73,   74,   75,   75,   70,   75,
 /*   850 */    72,   73,   74,
};
#define YY_SHIFT_USE_DFLT (-6)
#define YY_SHIFT_COUNT (108)
#define YY_SHIFT_MIN   (-5)
#define YY_SHIFT_MAX   (492)
static const short yy_shift_ofst[] = {
 /*     0 */   177,  342,  441,  433,  400,  441,  392,  441,  441,  441,
 /*    10 */   441,  441,  441,  441,  441,  441,  441,  441,  441,  441,
 /*    20 */   441,  441,  441,  441,  441,  441,  441,  441,  441,  441,
 /*    30 */   441,  441,  441,  441,  441,  441,  441,  441,  441,  441,
 /*    40 */   441,  441,  441,  441,  441,  441,  441,  441,  361,  244,
 /*    50 */   226,  186,  168,  146,  124,  102,   70,   41,   13,   -5,
 /*    60 */   263,  263,  263,  263,  263,  263,  263,  263,  263,  263,
 /*    70 */   263,  282,  202,  319,  334,  387,  387,   78,   78,   78,
 /*    80 */    78,  492,  452,  452,   29,    7,   17,   17,  322,   75,
 /*    90 */   188,  225,  138,  128,  169,  149,  117,  127,  127,  127,
 /*   100 */   127,  127,  127,  127,  101,  126,   92,   73,   71,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (48)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (778)
static const short yy_reduce_ofst[] = {
 /*     0 */    18,  252,  310,  439,  461,  461,  778,  771,  765,  760,
 /*    10 */   755,  749,  733,  726,  720,  711,  704,  698,  689,  682,
 /*    20 */   676,  666,  660,  652,  644,  638,  630,  622,  616,  608,
 /*    30 */   598,  593,  586,  571,  564,  556,  549,  542,  534,  527,
 /*    40 */   520,  512,  498,  490,  483,  476,  468,  425,    3,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   141,  213,  179,  213,  213,  180,  213,  213,  213,  213,
 /*    10 */   213,  213,  213,  213,  213,  213,  213,  213,  213,  213,
 /*    20 */   213,  213,  213,  213,  213,  213,  213,  213,  213,  213,
 /*    30 */   213,  213,  213,  213,  213,  213,  213,  213,  213,  213,
 /*    40 */   213,  213,  213,  213,  213,  213,  213,  213,  213,  213,
 /*    50 */   213,  174,  213,  213,  213,  213,  213,  213,  213,  213,
 /*    60 */   169,  172,  171,  162,  160,  165,  164,  163,  161,  173,
 /*    70 */   149,  202,  201,  209,  208,  196,  195,  200,  199,  198,
 /*    80 */   197,  152,  207,  206,  213,  159,  189,  190,  155,  152,
 /*    90 */   213,  213,  156,  213,  213,  213,  213,  191,  205,  204,
 /*   100 */   203,  194,  193,  192,  213,  213,  213,  213,  213,  212,
 /*   110 */   211,  167,  166,  157,  170,  168,  158,  150,  210,  154,
 /*   120 */   178,  188,  187,  186,  185,  184,  183,  182,  181,  176,
 /*   130 */   175,  177,  153,  148,  147,  146,  145,  144,  143,  142,
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
  "stmt_list",     "case_statement",  "where_statement",  "guard_assignment",
  "final_guard_statement",  "guard_statement",  "array",         "maybe_empty_stmt_list",
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
 /*  14 */ "expr ::= NAME LPAREN RPAREN",
 /*  15 */ "test ::= case_statement",
 /*  16 */ "spec ::= where_statement",
 /*  17 */ "test ::= guard_assignment",
 /*  18 */ "guard_assignment ::= name_chain final_guard_statement",
 /*  19 */ "guard_assignment ::= name_chain guard_statement",
 /*  20 */ "guard_statement ::= GUARD_N expr ASSIGN expr",
 /*  21 */ "guard_statement ::= guard_statement GUARD_N expr ASSIGN expr",
 /*  22 */ "guard_statement ::= GUARD_S expr ASSIGN expr",
 /*  23 */ "guard_statement ::= guard_statement GUARD_S expr ASSIGN expr",
 /*  24 */ "final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr",
 /*  25 */ "final_guard_statement ::= guard_statement WILDCARD ASSIGN expr",
 /*  26 */ "where_statement ::= guard_statement WHERE",
 /*  27 */ "where_statement ::= final_guard_statement WHERE",
 /*  28 */ "where_statement ::= name_chain ASSIGN expr WHERE",
 /*  29 */ "where_statement ::= where_statement NAME ASSIGN expr",
 /*  30 */ "case_statement ::= name_chain ASSIGN CASE expr OF",
 /*  31 */ "case_statement ::= case_statement N_TAB expr POINTER expr",
 /*  32 */ "case_statement ::= case_statement WILDCARD_N POINTER expr",
 /*  33 */ "expr ::= LET NAME ASSIGN expr IN expr",
 /*  34 */ "assignment ::= name_chain ASSIGN expr",
 /*  35 */ "stmt_list ::= stmt",
 /*  36 */ "stmt_list ::= stmt_list stmt",
 /*  37 */ "expr ::= array",
 /*  38 */ "array ::= OPENBRAC maybe_empty_stmt_list RBRAC",
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
 /*  49 */ "expr ::= expr PLUS expr",
 /*  50 */ "expr ::= expr MINUS expr",
 /*  51 */ "expr ::= expr DIVIDE expr",
 /*  52 */ "expr ::= expr TIMES expr",
 /*  53 */ "expr ::= expr MODULO expr",
 /*  54 */ "expr ::= expr POW expr",
 /*  55 */ "expr ::= expr EQUALTO expr",
 /*  56 */ "expr ::= expr NOTEQUALTO expr",
 /*  57 */ "expr ::= expr LESSTHAN expr",
 /*  58 */ "expr ::= expr GREATERTHAN expr",
 /*  59 */ "expr ::= expr LORE expr",
 /*  60 */ "expr ::= expr GORE expr",
 /*  61 */ "expr ::= expr AND expr",
 /*  62 */ "expr ::= expr OR expr",
 /*  63 */ "expr ::= BITNOT expr",
 /*  64 */ "expr ::= MINUS expr",
 /*  65 */ "expr ::= NOT expr",
 /*  66 */ "expr ::= expr SHIFTL expr",
 /*  67 */ "expr ::= expr SHIFTR expr",
 /*  68 */ "expr ::= expr BITAND expr",
 /*  69 */ "expr ::= expr BITXOR expr",
 /*  70 */ "expr ::= NAME LBRAC expr RBRAC",
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
#line 758 "./src/Grammar/grammar.c"
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
  { 58, 1 },
  { 67, 2 },
  { 67, 2 },
  { 69, 4 },
  { 69, 5 },
  { 69, 4 },
  { 69, 5 },
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
#line 1130 "./src/Grammar/grammar.c"
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
#line 1153 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= assignment */
#line 131 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1160 "./src/Grammar/grammar.c"
        break;
      case 7: /* spec ::= top_stmt */
      case 8: /* top_stmt ::= stmt */ yytestcase(yyruleno==8);
#line 136 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1169 "./src/Grammar/grammar.c"
        break;
      case 9: /* stmt ::= expr */
      case 35: /* stmt_list ::= stmt */ yytestcase(yyruleno==35);
#line 148 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1178 "./src/Grammar/grammar.c"
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
#line 1217 "./src/Grammar/grammar.c"
        break;
      case 11: /* name_chain ::= NAME */
#line 191 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1226 "./src/Grammar/grammar.c"
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
#line 1239 "./src/Grammar/grammar.c"
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
#line 1272 "./src/Grammar/grammar.c"
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
#line 1295 "./src/Grammar/grammar.c"
        break;
      case 15: /* test ::= case_statement */
#line 262 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
/*    panopticon::out() << "Case: " << *yymsp[0].minor.yy0.data.array->at(0).data.string << std::endl;*/
}
#line 1303 "./src/Grammar/grammar.c"
        break;
      case 16: /* spec ::= where_statement */
#line 268 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Where: " << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1311 "./src/Grammar/grammar.c"
        break;
      case 17: /* test ::= guard_assignment */
#line 274 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Guard");
}
#line 1320 "./src/Grammar/grammar.c"
        break;
      case 20: /* guard_statement ::= GUARD_N expr ASSIGN expr */
#line 284 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Guard");
  yy_destructor(yypParser,35,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1330 "./src/Grammar/grammar.c"
        break;
      case 21: /* guard_statement ::= guard_statement GUARD_N expr ASSIGN expr */
#line 290 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
  yy_destructor(yypParser,35,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1339 "./src/Grammar/grammar.c"
        break;
      case 22: /* guard_statement ::= GUARD_S expr ASSIGN expr */
#line 295 "./src/Grammar/grammar.y"
{

  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1348 "./src/Grammar/grammar.c"
        break;
      case 23: /* guard_statement ::= guard_statement GUARD_S expr ASSIGN expr */
#line 300 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1357 "./src/Grammar/grammar.c"
        break;
      case 24: /* final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr */
#line 305 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1367 "./src/Grammar/grammar.c"
        break;
      case 25: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr */
#line 311 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,38,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1377 "./src/Grammar/grammar.c"
        break;
      case 26: /* where_statement ::= guard_statement WHERE */
      case 27: /* where_statement ::= final_guard_statement WHERE */ yytestcase(yyruleno==27);
#line 316 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1385 "./src/Grammar/grammar.c"
        break;
      case 28: /* where_statement ::= name_chain ASSIGN expr WHERE */
#line 318 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1393 "./src/Grammar/grammar.c"
        break;
      case 29: /* where_statement ::= where_statement NAME ASSIGN expr */
#line 320 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,34,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1401 "./src/Grammar/grammar.c"
        break;
      case 30: /* case_statement ::= name_chain ASSIGN CASE expr OF */
#line 323 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,40,&yymsp[-2].minor);
  yy_destructor(yypParser,41,&yymsp[0].minor);
}
#line 1412 "./src/Grammar/grammar.c"
        break;
      case 31: /* case_statement ::= case_statement N_TAB expr POINTER expr */
#line 329 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-4].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,42,&yymsp[-3].minor);
  yy_destructor(yypParser,43,&yymsp[-1].minor);
}
#line 1422 "./src/Grammar/grammar.c"
        break;
      case 32: /* case_statement ::= case_statement WILDCARD_N POINTER expr */
#line 335 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0.type = optic::GUARD;
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,43,&yymsp[-1].minor);
}
#line 1432 "./src/Grammar/grammar.c"
        break;
      case 33: /* expr ::= LET NAME ASSIGN expr IN expr */
#line 341 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Let");
  yy_destructor(yypParser,44,&yymsp[-5].minor);
  yy_destructor(yypParser,34,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,45,&yymsp[-1].minor);
}
#line 1444 "./src/Grammar/grammar.c"
        break;
      case 34: /* assignment ::= name_chain ASSIGN expr */
#line 347 "./src/Grammar/grammar.y"
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
#line 1459 "./src/Grammar/grammar.c"
        break;
      case 36: /* stmt_list ::= stmt_list stmt */
#line 369 "./src/Grammar/grammar.y"
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
#line 1478 "./src/Grammar/grammar.c"
        break;
      case 37: /* expr ::= array */
#line 394 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1485 "./src/Grammar/grammar.c"
        break;
      case 38: /* array ::= OPENBRAC maybe_empty_stmt_list RBRAC */
#line 399 "./src/Grammar/grammar.y"
{
    create_tree(yygotominor.yy0,de_tree(yymsp[-1].minor.yy0));
  yy_destructor(yypParser,46,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1494 "./src/Grammar/grammar.c"
        break;
      case 39: /* maybe_empty_stmt_list ::= */
#line 404 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1502 "./src/Grammar/grammar.c"
        break;
      case 40: /* maybe_empty_stmt_list ::= stmt_list */
#line 410 "./src/Grammar/grammar.y"
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
#line 1518 "./src/Grammar/grammar.c"
        break;
      case 41: /* expr ::= num */
      case 43: /* expr ::= bool */ yytestcase(yyruleno==43);
#line 434 "./src/Grammar/grammar.y"
{
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1526 "./src/Grammar/grammar.c"
        break;
      case 42: /* expr ::= string */
#line 439 "./src/Grammar/grammar.y"
{
   create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1533 "./src/Grammar/grammar.c"
        break;
      case 44: /* expr ::= PRINT LPAREN expr RPAREN */
#line 453 "./src/Grammar/grammar.y"
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
#line 1548 "./src/Grammar/grammar.c"
        break;
      case 45: /* expr ::= LPAREN expr RPAREN */
#line 463 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
  yy_destructor(yypParser,27,&yymsp[-2].minor);
  yy_destructor(yypParser,28,&yymsp[0].minor);
}
#line 1557 "./src/Grammar/grammar.c"
        break;
      case 46: /* num ::= NUM */
#line 468 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;*/
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1566 "./src/Grammar/grammar.c"
        break;
      case 47: /* string ::= STRING */
#line 475 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());*/
/*    delete yymsp[0].minor.yy0.data.string;*/
    yymsp[0].minor.yy0.type = panopticon::STRING;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1576 "./src/Grammar/grammar.c"
        break;
      case 48: /* bool ::= BOOLEAN */
#line 484 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;*/
    yymsp[0].minor.yy0.type = panopticon::BOOL;
    create_tree(yygotominor.yy0,yymsp[0].minor.yy0);
}
#line 1585 "./src/Grammar/grammar.c"
        break;
      case 49: /* expr ::= expr PLUS expr */
#line 516 "./src/Grammar/grammar.y"
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
#line 1600 "./src/Grammar/grammar.c"
        break;
      case 50: /* expr ::= expr MINUS expr */
#line 528 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1613 "./src/Grammar/grammar.c"
        break;
      case 51: /* expr ::= expr DIVIDE expr */
#line 538 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1626 "./src/Grammar/grammar.c"
        break;
      case 52: /* expr ::= expr TIMES expr */
#line 548 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1639 "./src/Grammar/grammar.c"
        break;
      case 53: /* expr ::= expr MODULO expr */
#line 558 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1652 "./src/Grammar/grammar.c"
        break;
      case 54: /* expr ::= expr POW expr */
#line 568 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1665 "./src/Grammar/grammar.c"
        break;
      case 55: /* expr ::= expr EQUALTO expr */
#line 578 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1678 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr NOTEQUALTO expr */
#line 588 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1691 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= expr LESSTHAN expr */
#line 598 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1704 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= expr GREATERTHAN expr */
#line 608 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1717 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= expr LORE expr */
#line 618 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1730 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= expr GORE expr */
#line 628 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1743 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= expr AND expr */
#line 638 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1756 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= expr OR expr */
#line 648 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1769 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= BITNOT expr */
#line 658 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1782 "./src/Grammar/grammar.c"
        break;
      case 64: /* expr ::= MINUS expr */
#line 668 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1795 "./src/Grammar/grammar.c"
        break;
      case 65: /* expr ::= NOT expr */
#line 678 "./src/Grammar/grammar.y"
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
#line 1809 "./src/Grammar/grammar.c"
        break;
      case 66: /* expr ::= expr SHIFTL expr */
#line 689 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1822 "./src/Grammar/grammar.c"
        break;
      case 67: /* expr ::= expr SHIFTR expr */
#line 699 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1835 "./src/Grammar/grammar.c"
        break;
      case 68: /* expr ::= expr BITAND expr */
#line 709 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1848 "./src/Grammar/grammar.c"
        break;
      case 69: /* expr ::= expr BITXOR expr */
#line 729 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1861 "./src/Grammar/grammar.c"
        break;
      case 70: /* expr ::= NAME LBRAC expr RBRAC */
#line 739 "./src/Grammar/grammar.y"
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
#line 1876 "./src/Grammar/grammar.c"
        break;
      case 71: /* in ::= error */
#line 780 "./src/Grammar/grammar.y"
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
#line 1891 "./src/Grammar/grammar.c"
        break;
      case 72: /* error ::= OPENQUOTEERROR */
#line 793 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy151 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1900 "./src/Grammar/grammar.c"
        break;
      default:
      /* (0) main ::= in */ yytestcase(yyruleno==0);
      /* (1) in ::= */ yytestcase(yyruleno==1);
      /* (18) guard_assignment ::= name_chain final_guard_statement */ yytestcase(yyruleno==18);
      /* (19) guard_assignment ::= name_chain guard_statement */ yytestcase(yyruleno==19);
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
#line 1969 "./src/Grammar/grammar.c"
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
#line 1991 "./src/Grammar/grammar.c"
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
