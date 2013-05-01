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
#define YYNOCODE 72
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy143;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 121
#define YYNRULE 66
#define YYERRORSYMBOL 50
#define YYERRSYMDT yy143
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
#define YY_ACTTAB_COUNT (874)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    40,  119,    3,   94,   18,   19,   14,   15,   25,   24,
 /*    10 */    22,   20,   23,   21,   17,   16,   42,   39,   36,   33,
 /*    20 */    30,   27,   37,  111,   92,   29,   18,   19,   14,   15,
 /*    30 */    25,   24,   22,   20,   23,   21,   17,   16,   42,   39,
 /*    40 */    36,   33,   30,   27,   34,   27,  101,   11,   18,   19,
 /*    50 */    14,   15,   25,   24,   22,   20,   23,   21,   17,   16,
 /*    60 */    42,   39,   36,   33,   30,   27,   18,   19,   14,   15,
 /*    70 */    25,   24,   22,   20,   23,   21,   17,   16,   42,   39,
 /*    80 */    36,   33,   30,   27,   18,   19,   14,   15,   25,   24,
 /*    90 */    22,   20,   23,   21,   17,   16,   42,   39,   36,   33,
 /*   100 */    30,   27,    8,   31,   18,   19,   14,   15,   25,   24,
 /*   110 */    22,   20,   23,   21,   17,   16,   42,   39,   36,   33,
 /*   120 */    30,   27,   85,   28,   99,    9,   32,  188,    1,   18,
 /*   130 */    19,   14,   15,   25,   24,   22,   20,   23,   21,   17,
 /*   140 */    16,   42,   39,   36,   33,   30,   27,   19,   14,   15,
 /*   150 */    25,   24,   22,   20,   23,   21,   17,   16,   42,   39,
 /*   160 */    36,   33,   30,   27,   14,   15,   25,   24,   22,   20,
 /*   170 */    23,   21,   17,   16,   42,   39,   36,   33,   30,   27,
 /*   180 */    15,   25,   24,   22,   20,   23,   21,   17,   16,   42,
 /*   190 */    39,   36,   33,   30,   27,   59,  137,    7,   98,   97,
 /*   200 */   118,  117,  116,  115,   78,  114,  189,   76,   72,   80,
 /*   210 */   110,  121,  107,  106,  105,   25,   24,   22,   20,   23,
 /*   220 */    21,   17,   16,   42,   39,   36,   33,   30,   27,   13,
 /*   230 */    38,   10,   82,   81,   12,   26,   17,   16,   42,   39,
 /*   240 */    36,   33,   30,   27,  120,   77,   41,   35,  189,    6,
 /*   250 */    95,  189,  131,  189,   93,  189,    2,  104,  103,  102,
 /*   260 */   189,  189,  136,   13,   38,   10,   82,   81,   12,   26,
 /*   270 */   189,  189,  189,  113,   36,   33,   30,   27,    3,   96,
 /*   280 */    41,   35,  100,  189,   95,  131,  189,  189,   93,  189,
 /*   290 */     2,  104,  103,  102,  189,  189,   22,   20,   23,   21,
 /*   300 */    17,   16,   42,   39,   36,   33,   30,   27,  189,   13,
 /*   310 */   189,  189,  189,  189,   12,   26,   42,   39,   36,   33,
 /*   320 */    30,   27,  189,  189,  189,   96,   41,   35,  189,  189,
 /*   330 */    95,  189,   59,  189,   93,  189,    2,  104,  103,  102,
 /*   340 */   109,  189,  114,    5,   79,   75,  112,  110,   88,  107,
 /*   350 */   106,  105,   59,  135,  189,  189,  189,   85,  189,  189,
 /*   360 */   109,   32,  114,    4,   79,   75,  112,  110,  189,  107,
 /*   370 */   106,  105,  189,  189,  189,  189,  189,   59,  189,  189,
 /*   380 */   189,  189,  189,  189,  189,  108,  189,  114,   73,   79,
 /*   390 */    75,  112,  110,  189,  107,  106,  105,  189,  114,   48,
 /*   400 */    79,   75,  112,  110,  189,  107,  106,  105,  189,  114,
 /*   410 */   189,   79,   75,  112,  110,   58,  107,  106,  105,  189,
 /*   420 */   189,  189,  189,  189,  189,  114,  189,   79,   75,  112,
 /*   430 */   110,  189,  107,  106,  105,  189,  189,   74,  189,  189,
 /*   440 */   189,  189,  189,  189,  189,  189,  189,  114,   47,   79,
 /*   450 */    75,  112,  110,  189,  107,  106,  105,  189,  114,   57,
 /*   460 */    79,   75,  112,  110,  189,  107,  106,  105,  189,  114,
 /*   470 */    83,   79,   75,  112,  110,  189,  107,  106,  105,  189,
 /*   480 */   114,   46,   79,   75,  112,  110,  189,  107,  106,  105,
 /*   490 */   189,  114,  189,   79,   75,  112,  110,  189,  107,  106,
 /*   500 */   105,   56,  189,  189,  189,  189,  189,  189,  189,  189,
 /*   510 */   189,  114,   84,   79,   75,  112,  110,  189,  107,  106,
 /*   520 */   105,  189,  114,   45,   79,   75,  112,  110,  189,  107,
 /*   530 */   106,  105,  189,  114,   55,   79,   75,  112,  110,  189,
 /*   540 */   107,  106,  105,  189,  114,   86,   79,   75,  112,  110,
 /*   550 */   189,  107,  106,  105,  189,  114,  189,   79,   75,  112,
 /*   560 */   110,  189,  107,  106,  105,   44,  189,  189,  189,  189,
 /*   570 */   189,  189,  189,  189,  189,  114,   54,   79,   75,  112,
 /*   580 */   110,  189,  107,  106,  105,  189,  114,   87,   79,   75,
 /*   590 */   112,  110,  189,  107,  106,  105,  189,  114,   91,   79,
 /*   600 */    75,  112,  110,  189,  107,  106,  105,  189,  114,   65,
 /*   610 */    79,   75,  112,  110,  189,  107,  106,  105,  189,  114,
 /*   620 */   189,   79,   75,  112,  110,  189,  107,  106,  105,   64,
 /*   630 */   189,  189,  189,  189,  189,  189,  189,  189,  189,  114,
 /*   640 */    69,   79,   75,  112,  110,  189,  107,  106,  105,  189,
 /*   650 */   114,   68,   79,   75,  112,  110,  189,  107,  106,  105,
 /*   660 */   189,  114,   67,   79,   75,  112,  110,  189,  107,  106,
 /*   670 */   105,  189,  114,   66,   79,   75,  112,  110,  189,  107,
 /*   680 */   106,  105,  189,  114,  189,   79,   75,  112,  110,  189,
 /*   690 */   107,  106,  105,   61,  189,  189,  189,  189,  189,  189,
 /*   700 */   189,  189,  189,  114,   60,   79,   75,  112,  110,  189,
 /*   710 */   107,  106,  105,  189,  114,   71,   79,   75,  112,  110,
 /*   720 */   189,  107,  106,  105,  189,  114,   70,   79,   75,  112,
 /*   730 */   110,  189,  107,  106,  105,  189,  114,   63,   79,   75,
 /*   740 */   112,  110,  189,  107,  106,  105,  189,  114,  189,   79,
 /*   750 */    75,  112,  110,  189,  107,  106,  105,   62,  189,  189,
 /*   760 */   189,  189,  189,  189,  189,  189,  189,  114,   90,   79,
 /*   770 */    75,  112,  110,  189,  107,  106,  105,  189,  114,   89,
 /*   780 */    79,   75,  112,  110,  189,  107,  106,  105,  189,  114,
 /*   790 */    53,   79,   75,  112,  110,  189,  107,  106,  105,  189,
 /*   800 */   114,   43,   79,   75,  112,  110,  189,  107,  106,  105,
 /*   810 */   189,  114,  189,   79,   75,  112,  110,  189,  107,  106,
 /*   820 */   105,   52,  189,  189,  189,  189,  189,  189,  189,  189,
 /*   830 */   189,  114,   51,   79,   75,  112,  110,  189,  107,  106,
 /*   840 */   105,  189,  114,   50,   79,   75,  112,  110,  189,  107,
 /*   850 */   106,  105,  189,  114,   49,   79,   75,  112,  110,  189,
 /*   860 */   107,  106,  105,  189,  114,  189,   79,   75,  112,  110,
 /*   870 */   189,  107,  106,  105,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,   33,   27,   34,    5,    6,    7,    8,    9,   10,
 /*    10 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    20 */    21,   22,    1,   40,   34,    1,    5,    6,    7,    8,
 /*    30 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*    40 */    19,   20,   21,   22,    1,   22,   31,   42,    5,    6,
 /*    50 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*    60 */    17,   18,   19,   20,   21,   22,    5,    6,    7,    8,
 /*    70 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*    80 */    19,   20,   21,   22,    5,    6,    7,    8,    9,   10,
 /*    90 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   100 */    21,   22,    1,   42,    5,    6,    7,    8,    9,   10,
 /*   110 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   120 */    21,   22,   37,   44,   50,    1,   41,   53,   54,    5,
 /*   130 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   140 */    16,   17,   18,   19,   20,   21,   22,    6,    7,    8,
 /*   150 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   160 */    19,   20,   21,   22,    7,    8,    9,   10,   11,   12,
 /*   170 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   180 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   190 */    18,   19,   20,   21,   22,   51,   33,    1,   49,   55,
 /*   200 */    56,   57,   58,   59,   60,   61,   71,   63,   64,   65,
 /*   210 */    66,    0,   68,   69,   70,    9,   10,   11,   12,   13,
 /*   220 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   18,
 /*   230 */    35,   36,   37,   38,   23,   24,   15,   16,   17,   18,
 /*   240 */    19,   20,   21,   22,   33,   34,   35,   36,   71,    1,
 /*   250 */    39,   71,    1,   71,   43,   71,   45,   46,   47,   48,
 /*   260 */    71,   71,   33,   18,   35,   36,   37,   38,   23,   24,
 /*   270 */    71,   71,   71,   28,   19,   20,   21,   22,   27,   34,
 /*   280 */    35,   36,   34,   71,   39,   34,   71,   71,   43,   71,
 /*   290 */    45,   46,   47,   48,   71,   71,   11,   12,   13,   14,
 /*   300 */    15,   16,   17,   18,   19,   20,   21,   22,   71,   18,
 /*   310 */    71,   71,   71,   71,   23,   24,   17,   18,   19,   20,
 /*   320 */    21,   22,   71,   71,   71,   34,   35,   36,   71,   71,
 /*   330 */    39,   71,   51,   71,   43,   71,   45,   46,   47,   48,
 /*   340 */    59,   71,   61,   62,   63,   64,   65,   66,   67,   68,
 /*   350 */    69,   70,   51,   33,   71,   71,   71,   37,   71,   71,
 /*   360 */    59,   41,   61,   62,   63,   64,   65,   66,   71,   68,
 /*   370 */    69,   70,   71,   71,   71,   71,   71,   51,   71,   71,
 /*   380 */    71,   71,   71,   71,   71,   59,   71,   61,   51,   63,
 /*   390 */    64,   65,   66,   71,   68,   69,   70,   71,   61,   51,
 /*   400 */    63,   64,   65,   66,   71,   68,   69,   70,   71,   61,
 /*   410 */    71,   63,   64,   65,   66,   51,   68,   69,   70,   71,
 /*   420 */    71,   71,   71,   71,   71,   61,   71,   63,   64,   65,
 /*   430 */    66,   71,   68,   69,   70,   71,   71,   51,   71,   71,
 /*   440 */    71,   71,   71,   71,   71,   71,   71,   61,   51,   63,
 /*   450 */    64,   65,   66,   71,   68,   69,   70,   71,   61,   51,
 /*   460 */    63,   64,   65,   66,   71,   68,   69,   70,   71,   61,
 /*   470 */    51,   63,   64,   65,   66,   71,   68,   69,   70,   71,
 /*   480 */    61,   51,   63,   64,   65,   66,   71,   68,   69,   70,
 /*   490 */    71,   61,   71,   63,   64,   65,   66,   71,   68,   69,
 /*   500 */    70,   51,   71,   71,   71,   71,   71,   71,   71,   71,
 /*   510 */    71,   61,   51,   63,   64,   65,   66,   71,   68,   69,
 /*   520 */    70,   71,   61,   51,   63,   64,   65,   66,   71,   68,
 /*   530 */    69,   70,   71,   61,   51,   63,   64,   65,   66,   71,
 /*   540 */    68,   69,   70,   71,   61,   51,   63,   64,   65,   66,
 /*   550 */    71,   68,   69,   70,   71,   61,   71,   63,   64,   65,
 /*   560 */    66,   71,   68,   69,   70,   51,   71,   71,   71,   71,
 /*   570 */    71,   71,   71,   71,   71,   61,   51,   63,   64,   65,
 /*   580 */    66,   71,   68,   69,   70,   71,   61,   51,   63,   64,
 /*   590 */    65,   66,   71,   68,   69,   70,   71,   61,   51,   63,
 /*   600 */    64,   65,   66,   71,   68,   69,   70,   71,   61,   51,
 /*   610 */    63,   64,   65,   66,   71,   68,   69,   70,   71,   61,
 /*   620 */    71,   63,   64,   65,   66,   71,   68,   69,   70,   51,
 /*   630 */    71,   71,   71,   71,   71,   71,   71,   71,   71,   61,
 /*   640 */    51,   63,   64,   65,   66,   71,   68,   69,   70,   71,
 /*   650 */    61,   51,   63,   64,   65,   66,   71,   68,   69,   70,
 /*   660 */    71,   61,   51,   63,   64,   65,   66,   71,   68,   69,
 /*   670 */    70,   71,   61,   51,   63,   64,   65,   66,   71,   68,
 /*   680 */    69,   70,   71,   61,   71,   63,   64,   65,   66,   71,
 /*   690 */    68,   69,   70,   51,   71,   71,   71,   71,   71,   71,
 /*   700 */    71,   71,   71,   61,   51,   63,   64,   65,   66,   71,
 /*   710 */    68,   69,   70,   71,   61,   51,   63,   64,   65,   66,
 /*   720 */    71,   68,   69,   70,   71,   61,   51,   63,   64,   65,
 /*   730 */    66,   71,   68,   69,   70,   71,   61,   51,   63,   64,
 /*   740 */    65,   66,   71,   68,   69,   70,   71,   61,   71,   63,
 /*   750 */    64,   65,   66,   71,   68,   69,   70,   51,   71,   71,
 /*   760 */    71,   71,   71,   71,   71,   71,   71,   61,   51,   63,
 /*   770 */    64,   65,   66,   71,   68,   69,   70,   71,   61,   51,
 /*   780 */    63,   64,   65,   66,   71,   68,   69,   70,   71,   61,
 /*   790 */    51,   63,   64,   65,   66,   71,   68,   69,   70,   71,
 /*   800 */    61,   51,   63,   64,   65,   66,   71,   68,   69,   70,
 /*   810 */    71,   61,   71,   63,   64,   65,   66,   71,   68,   69,
 /*   820 */    70,   51,   71,   71,   71,   71,   71,   71,   71,   71,
 /*   830 */    71,   61,   51,   63,   64,   65,   66,   71,   68,   69,
 /*   840 */    70,   71,   61,   51,   63,   64,   65,   66,   71,   68,
 /*   850 */    69,   70,   71,   61,   51,   63,   64,   65,   66,   71,
 /*   860 */    68,   69,   70,   71,   61,   71,   63,   64,   65,   66,
 /*   870 */    71,   68,   69,   70,
};
#define YY_SHIFT_USE_DFLT (-33)
#define YY_SHIFT_COUNT (97)
#define YY_SHIFT_MIN   (-32)
#define YY_SHIFT_MAX   (320)
static const short yy_shift_ofst[] = {
 /*     0 */   149,  211,  291,  291,  245,  291,  291,  291,  291,  291,
 /*    10 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*    20 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*    30 */   291,  291,  291,  291,  291,  291,  291,  291,  291,  291,
 /*    40 */   291,  291,  291,  124,   79,   61,   43,   21,   -1,   99,
 /*    50 */    99,   99,   99,   99,   99,   99,   99,   99,   99,   99,
 /*    60 */   141,  157,  172,  206,  285,  285,  221,  221,  221,  221,
 /*    70 */   299,  299,  229,  255,  255,  195,  320,  251,  248,   85,
 /*    80 */   163,  196,  101,   23,   23,    5,   23,   23,   15,   23,
 /*    90 */    23,   23,   24,  -10,  -17,  -31,  -25,  -32,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (42)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (803)
static const short yy_reduce_ofst[] = {
 /*     0 */    74,  144,  281,  301,  326,  326,  803,  792,  781,  770,
 /*    10 */   750,  739,  728,  717,  706,  686,  675,  664,  653,  642,
 /*    20 */   622,  611,  600,  589,  578,  558,  547,  536,  525,  514,
 /*    30 */   494,  483,  472,  461,  450,  430,  419,  408,  397,  386,
 /*    40 */   364,  348,  337,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   122,  187,  156,  187,  187,  157,  187,  187,  187,  187,
 /*    10 */   187,  187,  187,  187,  187,  187,  187,  187,  187,  187,
 /*    20 */   187,  187,  187,  187,  187,  187,  187,  187,  187,  187,
 /*    30 */   187,  187,  187,  187,  187,  187,  187,  187,  187,  187,
 /*    40 */   187,  187,  187,  187,  187,  187,  187,  187,  187,  151,
 /*    50 */   143,  142,  141,  148,  150,  147,  140,  139,  138,  129,
 /*    60 */   177,  176,  184,  183,  171,  170,  175,  174,  173,  172,
 /*    70 */   182,  181,  144,  164,  165,  144,  149,  132,  187,  149,
 /*    80 */   145,  187,  187,  166,  167,  187,  168,  169,  187,  180,
 /*    90 */   179,  178,  187,  187,  187,  187,  132,  187,  186,  185,
 /*   100 */   130,  155,  163,  162,  161,  160,  159,  158,  153,  152,
 /*   110 */   154,  146,  145,  134,  133,  128,  127,  126,  125,  124,
 /*   120 */   123,
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
   45,  /*      LBRAC => OPENBRAC */
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
  "GUARD_S",       "WILDCARD_N",    "WILDCARD",      "CASE",        
  "OF",            "N_TAB",         "POINTER",       "LET",         
  "IN",            "OPENBRAC",      "NUM",           "STRING",      
  "BOOLEAN",       "OPENQUOTEERROR",  "error",         "expr",        
  "id",            "main",          "in",            "start",       
  "spec",          "assignment",    "top_stmt",      "stmt",        
  "name_chain",    "function_call",  "stmt_list",     "case_statement",
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
 /*   4 */ "start ::= spec",
 /*   5 */ "spec ::= assignment",
 /*   6 */ "spec ::= top_stmt",
 /*   7 */ "top_stmt ::= stmt",
 /*   8 */ "stmt ::= expr",
 /*   9 */ "name_chain ::= name_chain NAME",
 /*  10 */ "name_chain ::= NAME",
 /*  11 */ "expr ::= NAME",
 /*  12 */ "expr ::= function_call",
 /*  13 */ "function_call ::= NAME LPAREN stmt_list RPAREN",
 /*  14 */ "spec ::= case_statement",
 /*  15 */ "spec ::= guard_statement",
 /*  16 */ "spec ::= final_guard_statement",
 /*  17 */ "guard_statement ::= GUARD_N expr ASSIGN expr",
 /*  18 */ "guard_statement ::= guard_statement GUARD_N expr ASSIGN expr",
 /*  19 */ "guard_statement ::= GUARD_S expr ASSIGN expr",
 /*  20 */ "guard_statement ::= guard_statement GUARD_S expr ASSIGN expr",
 /*  21 */ "final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr",
 /*  22 */ "final_guard_statement ::= guard_statement WILDCARD ASSIGN expr",
 /*  23 */ "expr ::= guard_statement",
 /*  24 */ "expr ::= final_guard_statement",
 /*  25 */ "case_statement ::= CASE NAME OF",
 /*  26 */ "case_statement ::= case_statement N_TAB expr POINTER expr",
 /*  27 */ "case_statement ::= case_statement WILDCARD_N POINTER expr",
 /*  28 */ "expr ::= case_statement",
 /*  29 */ "expr ::= LET NAME ASSIGN expr IN expr",
 /*  30 */ "assignment ::= name_chain ASSIGN expr",
 /*  31 */ "stmt_list ::= stmt",
 /*  32 */ "stmt_list ::= stmt_list stmt",
 /*  33 */ "expr ::= array",
 /*  34 */ "array ::= OPENBRAC maybe_empty_stmt_list RBRAC",
 /*  35 */ "maybe_empty_stmt_list ::=",
 /*  36 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  37 */ "expr ::= num",
 /*  38 */ "expr ::= string",
 /*  39 */ "expr ::= bool",
 /*  40 */ "num ::= NUM",
 /*  41 */ "string ::= STRING",
 /*  42 */ "bool ::= BOOLEAN",
 /*  43 */ "expr ::= expr PLUS expr",
 /*  44 */ "expr ::= expr MINUS expr",
 /*  45 */ "expr ::= expr DIVIDE expr",
 /*  46 */ "expr ::= expr TIMES expr",
 /*  47 */ "expr ::= expr MODULO expr",
 /*  48 */ "expr ::= expr POW expr",
 /*  49 */ "expr ::= expr EQUALTO expr",
 /*  50 */ "expr ::= expr NOTEQUALTO expr",
 /*  51 */ "expr ::= expr LESSTHAN expr",
 /*  52 */ "expr ::= expr GREATERTHAN expr",
 /*  53 */ "expr ::= expr LORE expr",
 /*  54 */ "expr ::= expr GORE expr",
 /*  55 */ "expr ::= expr AND expr",
 /*  56 */ "expr ::= expr OR expr",
 /*  57 */ "expr ::= BITNOT expr",
 /*  58 */ "expr ::= MINUS expr",
 /*  59 */ "expr ::= NOT expr",
 /*  60 */ "expr ::= expr SHIFTL expr",
 /*  61 */ "expr ::= expr SHIFTR expr",
 /*  62 */ "expr ::= expr BITAND expr",
 /*  63 */ "expr ::= expr BITXOR expr",
 /*  64 */ "in ::= error",
 /*  65 */ "error ::= OPENQUOTEERROR",
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
    case 39: /* CASE */
    case 40: /* OF */
    case 41: /* N_TAB */
    case 42: /* POINTER */
    case 43: /* LET */
    case 44: /* IN */
    case 45: /* OPENBRAC */
    case 46: /* NUM */
    case 47: /* STRING */
    case 48: /* BOOLEAN */
    case 49: /* OPENQUOTEERROR */
{
#line 43 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 750 "./src/Grammar/grammar.c"
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
  { 55, 1 },
  { 56, 1 },
  { 56, 1 },
  { 58, 1 },
  { 59, 1 },
  { 60, 2 },
  { 60, 1 },
  { 51, 1 },
  { 51, 1 },
  { 61, 4 },
  { 56, 1 },
  { 56, 1 },
  { 56, 1 },
  { 64, 4 },
  { 64, 5 },
  { 64, 4 },
  { 64, 5 },
  { 65, 4 },
  { 65, 4 },
  { 51, 1 },
  { 51, 1 },
  { 63, 3 },
  { 63, 5 },
  { 63, 4 },
  { 51, 1 },
  { 51, 6 },
  { 57, 3 },
  { 62, 1 },
  { 62, 2 },
  { 51, 1 },
  { 66, 3 },
  { 67, 0 },
  { 67, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 68, 1 },
  { 69, 1 },
  { 70, 1 },
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
      case 2: /* in ::= in NEWLINE */
      case 3: /* in ::= in start NEWLINE */ yytestcase(yyruleno==3);
#line 83 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,33,&yymsp[0].minor);
}
#line 1114 "./src/Grammar/grammar.c"
        break;
      case 4: /* start ::= spec */
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
    else
    {
        std::cout << "RESOLVING!" << std::endl;

/*        std::cout << yymsp[0].minor.yy0.type << std::endl;*/
        for(int i=0;i<yymsp[0].minor.yy0.data.array->size();++i)
        {
            std::cout << i << ": " << yymsp[0].minor.yy0.data.array->at(i).type << std::endl;
        }
        optic::resolve_stack_from_parser(yymsp[0].minor.yy0);
    }
}
#line 1140 "./src/Grammar/grammar.c"
        break;
      case 5: /* spec ::= assignment */
      case 37: /* expr ::= num */ yytestcase(yyruleno==37);
      case 39: /* expr ::= bool */ yytestcase(yyruleno==39);
#line 114 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1149 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= top_stmt */
      case 7: /* top_stmt ::= stmt */ yytestcase(yyruleno==7);
      case 38: /* expr ::= string */ yytestcase(yyruleno==38);
#line 126 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1159 "./src/Grammar/grammar.c"
        break;
      case 8: /* stmt ::= expr */
      case 31: /* stmt_list ::= stmt */ yytestcase(yyruleno==31);
#line 138 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1168 "./src/Grammar/grammar.c"
        break;
      case 9: /* name_chain ::= name_chain NAME */
#line 144 "./src/Grammar/grammar.y"
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
#line 1207 "./src/Grammar/grammar.c"
        break;
      case 10: /* name_chain ::= NAME */
#line 181 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1216 "./src/Grammar/grammar.c"
        break;
      case 11: /* expr ::= NAME */
#line 188 "./src/Grammar/grammar.y"
{
/*    panopticon::retrieve_variable(yygotominor.yy0,yymsp[0].minor.yy0);*/
    yymsp[0].minor.yy0.type = optic::UNDECLARED_VARIABLE;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1229 "./src/Grammar/grammar.c"
        break;
      case 12: /* expr ::= function_call */
      case 33: /* expr ::= array */ yytestcase(yyruleno==33);
#line 199 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1237 "./src/Grammar/grammar.c"
        break;
      case 13: /* function_call ::= NAME LPAREN stmt_list RPAREN */
#line 204 "./src/Grammar/grammar.y"
{
    // yygotominor.yy0.scope = optic::get_scope();
    if(yymsp[-1].minor.yy0.type==optic::STATEMENT_LIST)
    {
            yymsp[-1].minor.yy0.type = optic::ARRAY;
            optic::out() << "Received a malformed argument to the function: " << *yymsp[-3].minor.yy0.data.string;
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
    b.type = optic::FUNCTION_CALL;
    b.data.string = new optic::String(*yymsp[-3].minor.yy0.data.string);
    optic::parse_operations(yygotominor.yy0,b,yymsp[-1].minor.yy0,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,27,&yymsp[-2].minor);
  yy_destructor(yypParser,28,&yymsp[0].minor);
}
#line 1268 "./src/Grammar/grammar.c"
        break;
      case 14: /* spec ::= case_statement */
#line 231 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Case: " << *yymsp[0].minor.yy0.data.array->at(0).data.string << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1276 "./src/Grammar/grammar.c"
        break;
      case 15: /* spec ::= guard_statement */
      case 16: /* spec ::= final_guard_statement */ yytestcase(yyruleno==16);
#line 238 "./src/Grammar/grammar.y"
{
    panopticon::out() << "Guard: " << *yymsp[0].minor.yy0.data.array->at(0).data.string << std::endl;
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1285 "./src/Grammar/grammar.c"
        break;
      case 17: /* guard_statement ::= GUARD_N expr ASSIGN expr */
#line 250 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0 = B;*/
/*    yygotominor.yy0.type = optic::GUARD;*/
  yy_destructor(yypParser,35,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1295 "./src/Grammar/grammar.c"
        break;
      case 18: /* guard_statement ::= guard_statement GUARD_N expr ASSIGN expr */
#line 256 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0 = yymsp[-4].minor.yy0;*/
/*    yygotominor.yy0.type = optic::GUARD;*/
  yy_destructor(yypParser,35,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1305 "./src/Grammar/grammar.c"
        break;
      case 19: /* guard_statement ::= GUARD_S expr ASSIGN expr */
#line 262 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0 = B;*/
/*    yygotominor.yy0.type = optic::GUARD;*/
  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1315 "./src/Grammar/grammar.c"
        break;
      case 20: /* guard_statement ::= guard_statement GUARD_S expr ASSIGN expr */
#line 268 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0 = yymsp[-4].minor.yy0;*/
/*    yygotominor.yy0.type = optic::GUARD;*/
  yy_destructor(yypParser,36,&yymsp[-3].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1325 "./src/Grammar/grammar.c"
        break;
      case 21: /* final_guard_statement ::= guard_statement WILDCARD_N ASSIGN expr */
#line 274 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0 = yymsp[-3].minor.yy0;*/
/*    yygotominor.yy0.type = optic::GUARD;*/
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1335 "./src/Grammar/grammar.c"
        break;
      case 22: /* final_guard_statement ::= guard_statement WILDCARD ASSIGN expr */
#line 280 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0 = yymsp[-3].minor.yy0;*/
/*    yygotominor.yy0.type = optic::GUARD;*/
  yy_destructor(yypParser,38,&yymsp[-2].minor);
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1345 "./src/Grammar/grammar.c"
        break;
      case 23: /* expr ::= guard_statement */
      case 24: /* expr ::= final_guard_statement */ yytestcase(yyruleno==24);
#line 286 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Guard");
}
#line 1354 "./src/Grammar/grammar.c"
        break;
      case 25: /* case_statement ::= CASE NAME OF */
#line 297 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0 = B;*/
/*    yygotominor.yy0.type = optic::GUARD;*/
  yy_destructor(yypParser,39,&yymsp[-2].minor);
  yy_destructor(yypParser,34,&yymsp[-1].minor);
  yy_destructor(yypParser,40,&yymsp[0].minor);
}
#line 1365 "./src/Grammar/grammar.c"
        break;
      case 26: /* case_statement ::= case_statement N_TAB expr POINTER expr */
#line 303 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0 = yymsp[-4].minor.yy0;*/
/*    yygotominor.yy0.type = optic::GUARD;*/
  yy_destructor(yypParser,41,&yymsp[-3].minor);
  yy_destructor(yypParser,42,&yymsp[-1].minor);
}
#line 1375 "./src/Grammar/grammar.c"
        break;
      case 27: /* case_statement ::= case_statement WILDCARD_N POINTER expr */
#line 309 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0 = yymsp[-3].minor.yy0;*/
/*    yygotominor.yy0.type = optic::GUARD;*/
  yy_destructor(yypParser,37,&yymsp[-2].minor);
  yy_destructor(yypParser,42,&yymsp[-1].minor);
}
#line 1385 "./src/Grammar/grammar.c"
        break;
      case 28: /* expr ::= case_statement */
#line 315 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Case");
}
#line 1393 "./src/Grammar/grammar.c"
        break;
      case 29: /* expr ::= LET NAME ASSIGN expr IN expr */
#line 321 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("Let");
  yy_destructor(yypParser,43,&yymsp[-5].minor);
  yy_destructor(yypParser,34,&yymsp[-4].minor);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,44,&yymsp[-1].minor);
}
#line 1405 "./src/Grammar/grammar.c"
        break;
      case 30: /* assignment ::= name_chain ASSIGN expr */
#line 334 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.type = optic::FUNCTION_DEC;*/
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1419 "./src/Grammar/grammar.c"
        break;
      case 32: /* stmt_list ::= stmt_list stmt */
#line 355 "./src/Grammar/grammar.y"
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
#line 1438 "./src/Grammar/grammar.c"
        break;
      case 34: /* array ::= OPENBRAC maybe_empty_stmt_list RBRAC */
#line 385 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::ARRAY;
    yygotominor.yy0.data.array = yymsp[-1].minor.yy0.data.array;
  yy_destructor(yypParser,45,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1448 "./src/Grammar/grammar.c"
        break;
      case 35: /* maybe_empty_stmt_list ::= */
#line 391 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1456 "./src/Grammar/grammar.c"
        break;
      case 36: /* maybe_empty_stmt_list ::= stmt_list */
#line 397 "./src/Grammar/grammar.y"
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
#line 1472 "./src/Grammar/grammar.c"
        break;
      case 40: /* num ::= NUM */
#line 449 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.type = panopticon::NUMBER;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1481 "./src/Grammar/grammar.c"
        break;
      case 41: /* string ::= STRING */
#line 456 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1491 "./src/Grammar/grammar.c"
        break;
      case 42: /* bool ::= BOOLEAN */
#line 465 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    yygotominor.yy0.type = panopticon::BOOL;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1500 "./src/Grammar/grammar.c"
        break;
      case 43: /* expr ::= expr PLUS expr */
#line 497 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::plus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1513 "./src/Grammar/grammar.c"
        break;
      case 44: /* expr ::= expr MINUS expr */
#line 507 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1526 "./src/Grammar/grammar.c"
        break;
      case 45: /* expr ::= expr DIVIDE expr */
#line 517 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1539 "./src/Grammar/grammar.c"
        break;
      case 46: /* expr ::= expr TIMES expr */
#line 527 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1552 "./src/Grammar/grammar.c"
        break;
      case 47: /* expr ::= expr MODULO expr */
#line 537 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1565 "./src/Grammar/grammar.c"
        break;
      case 48: /* expr ::= expr POW expr */
#line 547 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1578 "./src/Grammar/grammar.c"
        break;
      case 49: /* expr ::= expr EQUALTO expr */
#line 557 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1591 "./src/Grammar/grammar.c"
        break;
      case 50: /* expr ::= expr NOTEQUALTO expr */
#line 567 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1604 "./src/Grammar/grammar.c"
        break;
      case 51: /* expr ::= expr LESSTHAN expr */
#line 577 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1617 "./src/Grammar/grammar.c"
        break;
      case 52: /* expr ::= expr GREATERTHAN expr */
#line 587 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1630 "./src/Grammar/grammar.c"
        break;
      case 53: /* expr ::= expr LORE expr */
#line 597 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1643 "./src/Grammar/grammar.c"
        break;
      case 54: /* expr ::= expr GORE expr */
#line 607 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1656 "./src/Grammar/grammar.c"
        break;
      case 55: /* expr ::= expr AND expr */
#line 617 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1669 "./src/Grammar/grammar.c"
        break;
      case 56: /* expr ::= expr OR expr */
#line 627 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1682 "./src/Grammar/grammar.c"
        break;
      case 57: /* expr ::= BITNOT expr */
#line 637 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1695 "./src/Grammar/grammar.c"
        break;
      case 58: /* expr ::= MINUS expr */
#line 647 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1708 "./src/Grammar/grammar.c"
        break;
      case 59: /* expr ::= NOT expr */
#line 657 "./src/Grammar/grammar.y"
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
#line 1722 "./src/Grammar/grammar.c"
        break;
      case 60: /* expr ::= expr SHIFTL expr */
#line 668 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1735 "./src/Grammar/grammar.c"
        break;
      case 61: /* expr ::= expr SHIFTR expr */
#line 678 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1748 "./src/Grammar/grammar.c"
        break;
      case 62: /* expr ::= expr BITAND expr */
#line 688 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1761 "./src/Grammar/grammar.c"
        break;
      case 63: /* expr ::= expr BITXOR expr */
#line 708 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1774 "./src/Grammar/grammar.c"
        break;
      case 64: /* in ::= error */
#line 759 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy143)
    {
    case panopticon::OpenQuoteError:
/*        panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        panopticon::out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 1789 "./src/Grammar/grammar.c"
        break;
      case 65: /* error ::= OPENQUOTEERROR */
#line 772 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy143 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1798 "./src/Grammar/grammar.c"
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
#line 1865 "./src/Grammar/grammar.c"
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
#line 1887 "./src/Grammar/grammar.c"
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
