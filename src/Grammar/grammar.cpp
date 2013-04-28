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

#undef STRING
#undef NUM
#undef BOOL
#undef ARRAY

using namespace panopticon;

    void token_destructor(Token t)
    {
/*    out() << "In token_destructor t.value= " << t.value << std::endl;*/
/*    out() << "In token_destructor t.n= " << t.n << std::endl;*/
    }
#line 41 "./src/Grammar/grammar.c"
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
#define YYNOCODE 56
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy111;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 140
#define YYNRULE 83
#define YYERRORSYMBOL 36
#define YYERRSYMDT yy111
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
#define YY_ACTTAB_COUNT (552)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    23,   24,  138,   19,   20,   28,   27,   29,   26,   30,
 /*    10 */    25,   22,   21,   38,   33,   31,   32,   18,   17,   48,
 /*    20 */    36,   35,   37,   15,    7,  123,  121,   23,   24,   35,
 /*    30 */    19,   20,   28,   27,   29,   26,   30,   25,   22,   21,
 /*    40 */    38,   33,   31,   32,   18,   17,  118,   44,   46,   37,
 /*    50 */    49,   47,   44,   46,   48,  120,  225,   23,   24,   48,
 /*    60 */    19,   20,   28,   27,   29,   26,   30,   25,   22,   21,
 /*    70 */     6,   33,   31,   32,   18,   17,  225,   23,   24,    5,
 /*    80 */    19,   20,   28,   27,   29,   26,   30,   25,   22,   21,
 /*    90 */    38,   33,   31,   32,   18,   17,  225,  225,   24,   37,
 /*   100 */    19,   20,   28,   27,   29,   26,   30,   25,   22,   21,
 /*   110 */    38,   33,   31,   32,   18,   17,   79,   91,   94,   37,
 /*   120 */    19,   20,   28,   27,   29,   26,   30,   25,   22,   21,
 /*   130 */    38,   33,   31,   32,   18,   17,  225,   23,   24,   37,
 /*   140 */    19,   20,   28,   27,   29,   26,   30,   25,   22,   21,
 /*   150 */   225,  225,   31,   32,   18,   17,   95,  116,  109,    5,
 /*   160 */    20,   28,   27,   29,   26,   30,   25,   22,   21,   38,
 /*   170 */    33,   31,   32,   18,   17,   53,   90,   76,   37,   28,
 /*   180 */    27,   29,   26,   30,   25,   22,   21,   38,   33,   31,
 /*   190 */    32,   18,   17,   53,  115,   76,   37,   29,   26,   30,
 /*   200 */    25,   22,   21,   38,   33,   31,   32,   18,   17,  134,
 /*   210 */   225,  225,   37,  117,  137,  136,  135,  133,  132,  131,
 /*   220 */   225,   93,  225,  128,   54,   64,   73,  225,   45,   41,
 /*   230 */    42,   40,   43,   39,  225,   15,   49,   47,   44,   46,
 /*   240 */   119,   35,  134,  224,    1,   48,  225,  225,  124,  130,
 /*   250 */   133,  132,  131,    3,   93,  105,  128,   54,   64,   73,
 /*   260 */    45,   41,   42,   40,   43,   39,  134,  225,   49,   47,
 /*   270 */    44,   46,  140,  129,  133,  132,  131,   48,   93,  225,
 /*   280 */   128,   54,   64,   73,   17,   11,   12,    9,   37,  225,
 /*   290 */    14,   13,   16,   10,  225,  225,  225,   34,   36,  225,
 /*   300 */     2,   15,  225,  139,  127,  126,  125,   35,  225,   42,
 /*   310 */    40,   43,   39,  225,  225,   49,   47,   44,   46,   53,
 /*   320 */    71,   76,  225,  225,   48,   22,   21,   38,   33,   31,
 /*   330 */    32,   18,   17,   11,   12,  225,   37,  225,   14,   13,
 /*   340 */   225,   31,   32,   18,   17,  225,   36,    4,   37,   15,
 /*   350 */    31,   32,   18,   17,    9,   35,    7,    5,  122,   16,
 /*   360 */    10,    8,  225,  225,   34,  104,  225,    2,   56,   65,
 /*   370 */    76,  127,  126,  125,   38,   33,   31,   32,   18,   17,
 /*   380 */     9,  225,  225,   37,  225,   16,   10,  225,   12,  225,
 /*   390 */    34,  106,   14,   13,   78,   92,   76,  127,  126,  125,
 /*   400 */    36,  225,  225,   15,   14,   13,   53,  114,   76,   35,
 /*   410 */   225,  225,   36,  225,  225,   15,  225,  225,  225,  108,
 /*   420 */   225,   35,   52,  113,   76,  107,  225,  225,   57,   65,
 /*   430 */    76,   53,   86,   76,  225,  225,   53,   85,   76,   53,
 /*   440 */    70,   76,  225,   53,   84,   76,   53,   83,   76,   82,
 /*   450 */    92,   76,   53,  113,   76,  225,   53,   89,  103,   53,
 /*   460 */   112,   76,   51,   63,   72,   81,   65,   76,  102,   65,
 /*   470 */    76,  225,  101,   65,   76,   69,   65,   76,   68,   65,
 /*   480 */    76,   62,   65,   76,   61,   65,   76,  225,  225,   67,
 /*   490 */    65,   76,   66,   65,   76,  225,   58,   65,   76,   55,
 /*   500 */    65,   76,   75,   65,   76,   74,   65,   76,  225,   60,
 /*   510 */    65,   76,   59,   65,   76,  100,   65,   76,   99,   65,
 /*   520 */    76,   98,   65,  111,  225,   53,   65,  110,   53,   65,
 /*   530 */    88,   53,   65,   87,   53,   65,   80,   53,   65,   77,
 /*   540 */   225,  225,   97,   65,   76,   96,   65,   76,  225,   50,
 /*   550 */    65,   76,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    2,   31,    4,    5,    6,    7,    8,    9,   10,
 /*    10 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   23,
 /*    20 */    14,   23,   23,   17,   23,   26,   29,    1,    2,   23,
 /*    30 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*    40 */    14,   15,   16,   17,   18,   19,   35,   16,   17,   23,
 /*    50 */    14,   15,   16,   17,   23,   29,   55,    1,    2,   23,
 /*    60 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*    70 */    14,   15,   16,   17,   18,   19,   55,    1,    2,   23,
 /*    80 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*    90 */    14,   15,   16,   17,   18,   19,   55,   55,    2,   23,
 /*   100 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   110 */    14,   15,   16,   17,   18,   19,   52,   53,   54,   23,
 /*   120 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   130 */    14,   15,   16,   17,   18,   19,   55,    1,    2,   23,
 /*   140 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   150 */    55,   55,   16,   17,   18,   19,   52,   53,   54,   23,
 /*   160 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   170 */    15,   16,   17,   18,   19,   52,   53,   54,   23,    6,
 /*   180 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   190 */    17,   18,   19,   52,   53,   54,   23,    8,    9,   10,
 /*   200 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   37,
 /*   210 */    55,   55,   23,   41,   42,   43,   44,   45,   46,   47,
 /*   220 */    55,   49,   55,   51,   52,   53,   54,   55,    6,    7,
 /*   230 */     8,    9,   10,   11,   55,   17,   14,   15,   16,   17,
 /*   240 */    36,   23,   37,   39,   40,   23,   55,   55,   26,   44,
 /*   250 */    45,   46,   47,   48,   49,   50,   51,   52,   53,   54,
 /*   260 */     6,    7,    8,    9,   10,   11,   37,   55,   14,   15,
 /*   270 */    16,   17,    0,   44,   45,   46,   47,   23,   49,   55,
 /*   280 */    51,   52,   53,   54,   19,    1,    2,   15,   23,   55,
 /*   290 */     6,    7,   20,   21,   55,   55,   55,   25,   14,   55,
 /*   300 */    28,   17,   55,   31,   32,   33,   34,   23,   55,    8,
 /*   310 */     9,   10,   11,   55,   55,   14,   15,   16,   17,   52,
 /*   320 */    53,   54,   55,   55,   23,   12,   13,   14,   15,   16,
 /*   330 */    17,   18,   19,    1,    2,   55,   23,   55,    6,    7,
 /*   340 */    55,   16,   17,   18,   19,   55,   14,   14,   23,   17,
 /*   350 */    16,   17,   18,   19,   15,   23,   23,   23,   26,   20,
 /*   360 */    21,   28,   55,   55,   25,   49,   55,   28,   52,   53,
 /*   370 */    54,   32,   33,   34,   14,   15,   16,   17,   18,   19,
 /*   380 */    15,   55,   55,   23,   55,   20,   21,   55,    2,   55,
 /*   390 */    25,   49,    6,    7,   52,   53,   54,   32,   33,   34,
 /*   400 */    14,   55,   55,   17,    6,    7,   52,   53,   54,   23,
 /*   410 */    55,   55,   14,   55,   55,   17,   55,   55,   55,   49,
 /*   420 */    55,   23,   52,   53,   54,   49,   55,   55,   52,   53,
 /*   430 */    54,   52,   53,   54,   55,   55,   52,   53,   54,   52,
 /*   440 */    53,   54,   55,   52,   53,   54,   52,   53,   54,   52,
 /*   450 */    53,   54,   52,   53,   54,   55,   52,   53,   54,   52,
 /*   460 */    53,   54,   52,   53,   54,   52,   53,   54,   52,   53,
 /*   470 */    54,   55,   52,   53,   54,   52,   53,   54,   52,   53,
 /*   480 */    54,   52,   53,   54,   52,   53,   54,   55,   55,   52,
 /*   490 */    53,   54,   52,   53,   54,   55,   52,   53,   54,   52,
 /*   500 */    53,   54,   52,   53,   54,   52,   53,   54,   55,   52,
 /*   510 */    53,   54,   52,   53,   54,   52,   53,   54,   52,   53,
 /*   520 */    54,   52,   53,   54,   55,   52,   53,   54,   52,   53,
 /*   530 */    54,   52,   53,   54,   52,   53,   54,   52,   53,   54,
 /*   540 */    55,   55,   52,   53,   54,   52,   53,   54,   55,   52,
 /*   550 */    53,   54,
};
#define YY_SHIFT_USE_DFLT (-30)
#define YY_SHIFT_COUNT (117)
#define YY_SHIFT_MIN   (-29)
#define YY_SHIFT_MAX   (398)
static const short yy_shift_ofst[] = {
 /*     0 */    11,  272,  339,  339,  339,  339,  339,  339,  365,  365,
 /*    10 */   365,  365,  365,  365,  365,  365,  365,  365,  365,  365,
 /*    20 */   365,  365,  365,  365,  365,  365,  365,  365,  365,  365,
 /*    30 */   365,  365,  365,  365,  365,  365,  365,  365,  365,  365,
 /*    40 */   365,  365,  365,  365,  365,  365,  365,  365,  365,  365,
 /*    50 */    26,   -1,   56,   76,   56,   96,  136,  136,  116,  155,
 /*    60 */   173,  189,  189,  222,  254,  254,  313,  313,  313,  313,
 /*    70 */   301,  301,  332,  284,  360,  360,  284,  386,  334,  325,
 /*    80 */   398,  325,  325,   36,   36,   36,   36,    6,    6,   31,
 /*    90 */    31,   31,   31,  333,  218,  265,  265,  265,  265,  265,
 /*   100 */   265,  265,  265,  218,    1,   -3,    1,    1,    1,   -2,
 /*   110 */    -2,   -2,   -4,   -4,   -4,   -4,   -4,  -29,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (49)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (497)
static const short yy_reduce_ofst[] = {
 /*     0 */   204,  172,  205,  229,  376,  370,  342,  316,  497,  493,
 /*    10 */   490,  485,  482,  479,  476,  473,  469,  466,  463,  460,
 /*    20 */   457,  453,  450,  447,  444,  440,  437,  432,  429,  426,
 /*    30 */   423,  420,  416,  413,  410,  407,  404,  400,  397,  394,
 /*    40 */   391,  387,  384,  379,  354,  267,  141,  123,  104,   64,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   141,  223,  155,  156,  223,  223,  223,  223,  223,  223,
 /*    10 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*    20 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*    30 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*    40 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*    50 */   223,  223,  223,  223,  158,  204,  219,  217,  203,  209,
 /*    60 */   208,  200,  199,  223,  159,  223,  202,  201,  198,  197,
 /*    70 */   189,  185,  223,  160,  207,  206,  223,  178,  194,  164,
 /*    80 */   177,  193,  194,  191,  190,  188,  187,  176,  175,  170,
 /*    90 */   181,  182,  166,  153,  168,  165,  211,  210,  205,  213,
 /*   100 */   212,  196,  195,  173,  214,  223,  216,  215,  218,  169,
 /*   110 */   174,  179,  171,  167,  186,  184,  183,  223,  222,  221,
 /*   120 */   220,  154,  172,  192,  180,  163,  162,  161,  157,  152,
 /*   130 */   151,  150,  149,  148,  147,  146,  145,  144,  143,  142,
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
  "$",             "OR",            "AND",           "BITXOR",      
  "BITOR",         "BITAND",        "EQUALTO",       "NOTEQUALTO",  
  "GREATERTHAN",   "GORE",          "LESSTHAN",      "LORE",        
  "SHIFTL",        "SHIFTR",        "PLUS",          "MINUS",       
  "DIVIDE",        "TIMES",         "MODULO",        "POW",         
  "NOT",           "BITNOT",        "UMINUS",        "PLUSPLUS",    
  "INDEX",         "LPAREN",        "RPAREN",        "COMMA",       
  "LBRAC",         "RBRAC",         "ASSIGN",        "NEWLINE",     
  "NUM",           "STRING",        "BOOLEAN",       "OPENQUOTEERROR",
  "error",         "expr",          "id",            "main",        
  "in",            "start",         "spec",          "top_stmt",    
  "stmt",          "retval",        "access",        "identifier",  
  "stmt_list",     "array",         "maybe_empty_stmt_list",  "value",       
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
 /*   5 */ "spec ::= top_stmt",
 /*   6 */ "top_stmt ::= stmt",
 /*   7 */ "stmt ::= expr",
 /*   8 */ "expr ::= retval",
 /*   9 */ "retval ::= access",
 /*  10 */ "access ::= identifier",
 /*  11 */ "stmt_list ::= stmt",
 /*  12 */ "stmt_list ::= stmt_list stmt",
 /*  13 */ "access ::= array",
 /*  14 */ "array ::= LBRAC maybe_empty_stmt_list RBRAC",
 /*  15 */ "maybe_empty_stmt_list ::=",
 /*  16 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  17 */ "identifier ::= value",
 /*  18 */ "value ::= num",
 /*  19 */ "value ::= string",
 /*  20 */ "value ::= bool",
 /*  21 */ "num ::= NUM",
 /*  22 */ "string ::= STRING",
 /*  23 */ "bool ::= BOOLEAN",
 /*  24 */ "string ::= string PLUS num",
 /*  25 */ "string ::= string PLUSPLUS num",
 /*  26 */ "string ::= num PLUS string",
 /*  27 */ "string ::= num PLUSPLUS string",
 /*  28 */ "string ::= string PLUS bool",
 /*  29 */ "string ::= string PLUSPLUS bool",
 /*  30 */ "string ::= bool PLUS string",
 /*  31 */ "string ::= bool PLUSPLUS string",
 /*  32 */ "bool ::= LPAREN bool RPAREN",
 /*  33 */ "bool ::= bool PLUS bool",
 /*  34 */ "bool ::= bool TIMES bool",
 /*  35 */ "bool ::= bool EQUALTO bool",
 /*  36 */ "bool ::= bool NOTEQUALTO bool",
 /*  37 */ "bool ::= bool AND bool",
 /*  38 */ "bool ::= bool OR bool",
 /*  39 */ "bool ::= NOT bool",
 /*  40 */ "string ::= LPAREN string RPAREN",
 /*  41 */ "string ::= string MINUS string",
 /*  42 */ "string ::= string PLUS string",
 /*  43 */ "string ::= string PLUSPLUS string",
 /*  44 */ "num ::= string TIMES string",
 /*  45 */ "bool ::= string EQUALTO string",
 /*  46 */ "num ::= string DIVIDE string",
 /*  47 */ "bool ::= string LESSTHAN string",
 /*  48 */ "bool ::= string GREATERTHAN string",
 /*  49 */ "bool ::= string NOTEQUALTO string",
 /*  50 */ "bool ::= string GORE string",
 /*  51 */ "bool ::= string LORE string",
 /*  52 */ "num ::= LPAREN num RPAREN",
 /*  53 */ "num ::= num MINUS num",
 /*  54 */ "num ::= num PLUS num",
 /*  55 */ "num ::= num TIMES num",
 /*  56 */ "num ::= num DIVIDE num",
 /*  57 */ "bool ::= num LESSTHAN num",
 /*  58 */ "bool ::= num GREATERTHAN num",
 /*  59 */ "bool ::= num EQUALTO num",
 /*  60 */ "bool ::= num NOTEQUALTO num",
 /*  61 */ "bool ::= num GORE num",
 /*  62 */ "bool ::= num LORE num",
 /*  63 */ "bool ::= num AND num",
 /*  64 */ "bool ::= num OR num",
 /*  65 */ "bool ::= NOT num",
 /*  66 */ "num ::= num SHIFTL num",
 /*  67 */ "num ::= num SHIFTR num",
 /*  68 */ "num ::= num BITAND num",
 /*  69 */ "num ::= num BITOR num",
 /*  70 */ "num ::= BITNOT num",
 /*  71 */ "num ::= MINUS num",
 /*  72 */ "num ::= num MODULO num",
 /*  73 */ "num ::= num POW num",
 /*  74 */ "array ::= array PLUSPLUS array",
 /*  75 */ "array ::= array PLUS array",
 /*  76 */ "array ::= num PLUS array",
 /*  77 */ "array ::= array PLUS num",
 /*  78 */ "array ::= num PLUSPLUS array",
 /*  79 */ "array ::= array PLUSPLUS num",
 /*  80 */ "value ::= array LBRAC num RBRAC",
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
    case 1: /* OR */
    case 2: /* AND */
    case 3: /* BITXOR */
    case 4: /* BITOR */
    case 5: /* BITAND */
    case 6: /* EQUALTO */
    case 7: /* NOTEQUALTO */
    case 8: /* GREATERTHAN */
    case 9: /* GORE */
    case 10: /* LESSTHAN */
    case 11: /* LORE */
    case 12: /* SHIFTL */
    case 13: /* SHIFTR */
    case 14: /* PLUS */
    case 15: /* MINUS */
    case 16: /* DIVIDE */
    case 17: /* TIMES */
    case 18: /* MODULO */
    case 19: /* POW */
    case 20: /* NOT */
    case 21: /* BITNOT */
    case 22: /* UMINUS */
    case 23: /* PLUSPLUS */
    case 24: /* INDEX */
    case 25: /* LPAREN */
    case 26: /* RPAREN */
    case 27: /* COMMA */
    case 28: /* LBRAC */
    case 29: /* RBRAC */
    case 30: /* ASSIGN */
    case 31: /* NEWLINE */
    case 32: /* NUM */
    case 33: /* STRING */
    case 34: /* BOOLEAN */
    case 35: /* OPENQUOTEERROR */
{
#line 40 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 653 "./src/Grammar/grammar.c"
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
  { 39, 1 },
  { 40, 0 },
  { 40, 2 },
  { 40, 3 },
  { 41, 1 },
  { 42, 1 },
  { 43, 1 },
  { 44, 1 },
  { 37, 1 },
  { 45, 1 },
  { 46, 1 },
  { 48, 1 },
  { 48, 2 },
  { 46, 1 },
  { 49, 3 },
  { 50, 0 },
  { 50, 1 },
  { 47, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 52, 1 },
  { 53, 1 },
  { 54, 1 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 2 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 52, 3 },
  { 54, 3 },
  { 52, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 3 },
  { 54, 2 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 3 },
  { 52, 2 },
  { 52, 2 },
  { 52, 3 },
  { 52, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 51, 4 },
  { 40, 1 },
  { 36, 1 },
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
#line 76 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1034 "./src/Grammar/grammar.c"
        break;
      case 4: /* start ::= spec */
#line 85 "./src/Grammar/grammar.y"
{
    optic::print_object(yymsp[0].minor.yy0);
    optic::delete_object(yymsp[0].minor.yy0);
}
#line 1042 "./src/Grammar/grammar.c"
        break;
      case 5: /* spec ::= top_stmt */
      case 6: /* top_stmt ::= stmt */ yytestcase(yyruleno==6);
      case 8: /* expr ::= retval */ yytestcase(yyruleno==8);
      case 17: /* identifier ::= value */ yytestcase(yyruleno==17);
      case 19: /* value ::= string */ yytestcase(yyruleno==19);
#line 92 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1054 "./src/Grammar/grammar.c"
        break;
      case 7: /* stmt ::= expr */
      case 9: /* retval ::= access */ yytestcase(yyruleno==9);
      case 10: /* access ::= identifier */ yytestcase(yyruleno==10);
      case 11: /* stmt_list ::= stmt */ yytestcase(yyruleno==11);
#line 103 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1065 "./src/Grammar/grammar.c"
        break;
      case 12: /* stmt_list ::= stmt_list stmt */
#line 143 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    if(yymsp[-1].minor.yy0.type!=STATEMENT_LIST)
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
#line 1084 "./src/Grammar/grammar.c"
        break;
      case 13: /* access ::= array */
      case 18: /* value ::= num */ yytestcase(yyruleno==18);
      case 20: /* value ::= bool */ yytestcase(yyruleno==20);
#line 161 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1093 "./src/Grammar/grammar.c"
        break;
      case 14: /* array ::= LBRAC maybe_empty_stmt_list RBRAC */
#line 166 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::ARRAY;
    yygotominor.yy0.data.array = yymsp[-1].minor.yy0.data.array;
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1103 "./src/Grammar/grammar.c"
        break;
      case 15: /* maybe_empty_stmt_list ::= */
#line 172 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1111 "./src/Grammar/grammar.c"
        break;
      case 16: /* maybe_empty_stmt_list ::= stmt_list */
#line 178 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    if(yymsp[0].minor.yy0.type!=STATEMENT_LIST)
    {
        panopticon::create_array(yygotominor.yy0);
        yygotominor.yy0.data.array->push_back(yymsp[0].minor.yy0);
    }
    else
    {
        yygotominor.yy0.data.array = yymsp[0].minor.yy0.data.array;
    }
}
#line 1127 "./src/Grammar/grammar.c"
        break;
      case 21: /* num ::= NUM */
#line 237 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.type = panopticon::NUMBER;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1136 "./src/Grammar/grammar.c"
        break;
      case 22: /* string ::= STRING */
#line 244 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1146 "./src/Grammar/grammar.c"
        break;
      case 23: /* bool ::= BOOLEAN */
#line 253 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    yygotominor.yy0.type = panopticon::BOOL;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1155 "./src/Grammar/grammar.c"
        break;
      case 24: /* string ::= string PLUS num */
#line 264 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::string_plus_num(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1165 "./src/Grammar/grammar.c"
        break;
      case 25: /* string ::= string PLUSPLUS num */
#line 271 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::string_plusplus_num(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1175 "./src/Grammar/grammar.c"
        break;
      case 26: /* string ::= num PLUS string */
#line 278 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::num_plus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1185 "./src/Grammar/grammar.c"
        break;
      case 27: /* string ::= num PLUSPLUS string */
#line 285 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::num_plusplus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1195 "./src/Grammar/grammar.c"
        break;
      case 28: /* string ::= string PLUS bool */
#line 292 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::string_plus_bool(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1205 "./src/Grammar/grammar.c"
        break;
      case 29: /* string ::= string PLUSPLUS bool */
#line 299 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::string_plusplus_bool(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1215 "./src/Grammar/grammar.c"
        break;
      case 30: /* string ::= bool PLUS string */
#line 306 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::bool_plus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1225 "./src/Grammar/grammar.c"
        break;
      case 31: /* string ::= bool PLUSPLUS string */
#line 313 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::bool_plusplus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1235 "./src/Grammar/grammar.c"
        break;
      case 32: /* bool ::= LPAREN bool RPAREN */
#line 323 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-1].minor.yy0.data.boolean;
    //yygotominor.yy0.n = yymsp[-1].minor.yy0.n+1;
  yy_destructor(yypParser,25,&yymsp[-2].minor);
  yy_destructor(yypParser,26,&yymsp[0].minor);
}
#line 1246 "./src/Grammar/grammar.c"
        break;
      case 33: /* bool ::= bool PLUS bool */
#line 330 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    if(yymsp[-2].minor.yy0.data.boolean || yymsp[0].minor.yy0.data.boolean)
    {
        yygotominor.yy0.data.boolean = true;
    }
    else
    {
        yygotominor.yy0.data.boolean = false;
    }
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1263 "./src/Grammar/grammar.c"
        break;
      case 34: /* bool ::= bool TIMES bool */
#line 344 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    if(yymsp[-2].minor.yy0.data.boolean && yymsp[0].minor.yy0.data.boolean)
    {
        yygotominor.yy0.data.boolean = true;
    }
    else
    {
        yygotominor.yy0.data.boolean = false;
    }
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1280 "./src/Grammar/grammar.c"
        break;
      case 35: /* bool ::= bool EQUALTO bool */
#line 358 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.boolean == yymsp[0].minor.yy0.data.boolean;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1290 "./src/Grammar/grammar.c"
        break;
      case 36: /* bool ::= bool NOTEQUALTO bool */
      case 60: /* bool ::= num NOTEQUALTO num */ yytestcase(yyruleno==60);
#line 365 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number != yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1301 "./src/Grammar/grammar.c"
        break;
      case 37: /* bool ::= bool AND bool */
#line 372 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = (int)yymsp[-2].minor.yy0.data.boolean && (int)yymsp[0].minor.yy0.data.boolean;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,2,&yymsp[-1].minor);
}
#line 1311 "./src/Grammar/grammar.c"
        break;
      case 38: /* bool ::= bool OR bool */
#line 379 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = (int)yymsp[-2].minor.yy0.data.boolean || (int)yymsp[0].minor.yy0.data.boolean;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1321 "./src/Grammar/grammar.c"
        break;
      case 39: /* bool ::= NOT bool */
#line 386 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = !((int)yymsp[0].minor.yy0.data.boolean);
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1331 "./src/Grammar/grammar.c"
        break;
      case 40: /* string ::= LPAREN string RPAREN */
#line 452 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = yymsp[-1].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[-1].minor.yy0.n+1;
  yy_destructor(yypParser,25,&yymsp[-2].minor);
  yy_destructor(yypParser,26,&yymsp[0].minor);
}
#line 1342 "./src/Grammar/grammar.c"
        break;
      case 41: /* string ::= string MINUS string */
#line 459 "./src/Grammar/grammar.y"
{
    panopticon::string_minus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1352 "./src/Grammar/grammar.c"
        break;
      case 42: /* string ::= string PLUS string */
#line 466 "./src/Grammar/grammar.y"
{
    panopticon::string_plus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1362 "./src/Grammar/grammar.c"
        break;
      case 43: /* string ::= string PLUSPLUS string */
#line 473 "./src/Grammar/grammar.y"
{
    panopticon::string_plusplus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1372 "./src/Grammar/grammar.c"
        break;
      case 44: /* num ::= string TIMES string */
#line 480 "./src/Grammar/grammar.y"
{
    if(is_number(*yymsp[-2].minor.yy0.data.string) && is_number(*yymsp[0].minor.yy0.data.string))
    {
        yygotominor.yy0.type = panopticon::NUMBER;
        yygotominor.yy0.data.number = string_to_double(*yymsp[-2].minor.yy0.data.string) * string_to_double(*yymsp[0].minor.yy0.data.string);
    }
    else
    {
/*        yygotominor.yy0 = panopticon::MulStringError;*/
        out() << "Error p0002: Attempted to Multiply a string by a string, and at least one is non-numerical: " << std::endl;
        out() << "String 1: " << *yymsp[-2].minor.yy0.data.string << std::endl;
        out() << "String 2: " << *yymsp[0].minor.yy0.data.string << std::endl;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1391 "./src/Grammar/grammar.c"
        break;
      case 45: /* bool ::= string EQUALTO string */
#line 496 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->compare(*yymsp[0].minor.yy0.data.string)==0;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1401 "./src/Grammar/grammar.c"
        break;
      case 46: /* num ::= string DIVIDE string */
#line 503 "./src/Grammar/grammar.y"
{
    if(is_number(*yymsp[-2].minor.yy0.data.string) && is_number(*yymsp[0].minor.yy0.data.string))
    {
        yygotominor.yy0.type = panopticon::NUMBER;
        yygotominor.yy0.data.number = string_to_double(*yymsp[-2].minor.yy0.data.string) / string_to_double(*yymsp[0].minor.yy0.data.string);
    }
    else
    {
        yygotominor.yy0.type = panopticon::ERROR;
        yygotominor.yy0.data.number = 0;
/*        yygotominor.yy0 = panopticon::MulStringError;*/
        out() << "Error p0002: Attempted to Multiply a string by a string, and at least one is non-numerical: " << std::endl;
        out() << "String 1: " << *yymsp[-2].minor.yy0.data.string << std::endl;
        out() << "String 2: " << *yymsp[0].minor.yy0.data.string << std::endl;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1422 "./src/Grammar/grammar.c"
        break;
      case 47: /* bool ::= string LESSTHAN string */
#line 521 "./src/Grammar/grammar.y"
{
    if(is_number(*yymsp[-2].minor.yy0.data.string) && is_number(*yymsp[0].minor.yy0.data.string))
    {
        yygotominor.yy0.type = panopticon::BOOL;
        yygotominor.yy0.data.boolean = string_to_double(*yymsp[-2].minor.yy0.data.string) < string_to_double(*yymsp[0].minor.yy0.data.string);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
    else
    {
        yygotominor.yy0.type = panopticon::BOOL;
        yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->size() < yymsp[0].minor.yy0.data.string->size();
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1441 "./src/Grammar/grammar.c"
        break;
      case 48: /* bool ::= string GREATERTHAN string */
#line 537 "./src/Grammar/grammar.y"
{
    if(is_number(*yymsp[-2].minor.yy0.data.string) && is_number(*yymsp[0].minor.yy0.data.string))
    {
        yygotominor.yy0.type = panopticon::BOOL;
        yygotominor.yy0.data.boolean = string_to_double(*yymsp[-2].minor.yy0.data.string) > string_to_double(*yymsp[0].minor.yy0.data.string);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
    else
    {
        yygotominor.yy0.type = panopticon::BOOL;
        yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->size() > yymsp[0].minor.yy0.data.string->size();
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1460 "./src/Grammar/grammar.c"
        break;
      case 49: /* bool ::= string NOTEQUALTO string */
#line 553 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->compare(*yymsp[0].minor.yy0.data.string)!=0;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1470 "./src/Grammar/grammar.c"
        break;
      case 50: /* bool ::= string GORE string */
#line 561 "./src/Grammar/grammar.y"
{
    if(is_number(*yymsp[-2].minor.yy0.data.string) && is_number(*yymsp[0].minor.yy0.data.string))
    {
        yygotominor.yy0.type = panopticon::BOOL;
        yygotominor.yy0.data.boolean = string_to_double(*yymsp[-2].minor.yy0.data.string) >= string_to_double(*yymsp[0].minor.yy0.data.string);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
    else
    {
        yygotominor.yy0.type = panopticon::BOOL;
        yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->size() > yymsp[0].minor.yy0.data.string->size();
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1489 "./src/Grammar/grammar.c"
        break;
      case 51: /* bool ::= string LORE string */
#line 577 "./src/Grammar/grammar.y"
{
    if(is_number(*yymsp[-2].minor.yy0.data.string) && is_number(*yymsp[0].minor.yy0.data.string))
    {
        yygotominor.yy0.type = panopticon::BOOL;
        yygotominor.yy0.data.boolean = string_to_double(*yymsp[-2].minor.yy0.data.string) <= string_to_double(*yymsp[0].minor.yy0.data.string);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
    else
    {
        yygotominor.yy0.type = panopticon::BOOL;
        yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->size() > yymsp[0].minor.yy0.data.string->size();
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1508 "./src/Grammar/grammar.c"
        break;
      case 52: /* num ::= LPAREN num RPAREN */
#line 596 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = yymsp[-1].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-1].minor.yy0.n+1;
  yy_destructor(yypParser,25,&yymsp[-2].minor);
  yy_destructor(yypParser,26,&yymsp[0].minor);
}
#line 1519 "./src/Grammar/grammar.c"
        break;
      case 53: /* num ::= num MINUS num */
#line 603 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = yymsp[-2].minor.yy0.data.number - yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1529 "./src/Grammar/grammar.c"
        break;
      case 54: /* num ::= num PLUS num */
#line 610 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = yymsp[-2].minor.yy0.data.number + yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1539 "./src/Grammar/grammar.c"
        break;
      case 55: /* num ::= num TIMES num */
#line 617 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = yymsp[-2].minor.yy0.data.number * yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1549 "./src/Grammar/grammar.c"
        break;
      case 56: /* num ::= num DIVIDE num */
#line 624 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    if(yymsp[0].minor.yy0.data.number != 0)
    {
         yygotominor.yy0.data.number = yymsp[-2].minor.yy0.data.number / yymsp[0].minor.yy0.data.number;
/*         yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1 + yymsp[0].minor.yy0.n+1;*/
    }
    else
    {
         out() << "divide by zero" << std::endl;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1566 "./src/Grammar/grammar.c"
        break;
      case 57: /* bool ::= num LESSTHAN num */
#line 638 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number < yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1576 "./src/Grammar/grammar.c"
        break;
      case 58: /* bool ::= num GREATERTHAN num */
#line 645 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number > yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1586 "./src/Grammar/grammar.c"
        break;
      case 59: /* bool ::= num EQUALTO num */
#line 652 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number == yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1596 "./src/Grammar/grammar.c"
        break;
      case 61: /* bool ::= num GORE num */
#line 666 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number >= yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1606 "./src/Grammar/grammar.c"
        break;
      case 62: /* bool ::= num LORE num */
#line 673 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number <= yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1616 "./src/Grammar/grammar.c"
        break;
      case 63: /* bool ::= num AND num */
#line 680 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = (int)yymsp[-2].minor.yy0.data.number && (int)yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,2,&yymsp[-1].minor);
}
#line 1626 "./src/Grammar/grammar.c"
        break;
      case 64: /* bool ::= num OR num */
#line 687 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = (int)yymsp[-2].minor.yy0.data.number || (int)yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1636 "./src/Grammar/grammar.c"
        break;
      case 65: /* bool ::= NOT num */
#line 694 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = !((int)yymsp[0].minor.yy0.data.number);
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1646 "./src/Grammar/grammar.c"
        break;
      case 66: /* num ::= num SHIFTL num */
#line 701 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = (int)yymsp[-2].minor.yy0.data.number << (int)yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1656 "./src/Grammar/grammar.c"
        break;
      case 67: /* num ::= num SHIFTR num */
#line 708 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = (int)yymsp[-2].minor.yy0.data.number >> (int)yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1666 "./src/Grammar/grammar.c"
        break;
      case 68: /* num ::= num BITAND num */
#line 715 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = (int)yymsp[-2].minor.yy0.data.number & (int)yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1676 "./src/Grammar/grammar.c"
        break;
      case 69: /* num ::= num BITOR num */
#line 722 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = (int)yymsp[-2].minor.yy0.data.number | (int)yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,4,&yymsp[-1].minor);
}
#line 1686 "./src/Grammar/grammar.c"
        break;
      case 70: /* num ::= BITNOT num */
#line 729 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = ~((int)yymsp[0].minor.yy0.data.number);
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1696 "./src/Grammar/grammar.c"
        break;
      case 71: /* num ::= MINUS num */
#line 736 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = -1 * yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1706 "./src/Grammar/grammar.c"
        break;
      case 72: /* num ::= num MODULO num */
#line 743 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = fmod(yymsp[-2].minor.yy0.data.number,yymsp[0].minor.yy0.data.number);
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1716 "./src/Grammar/grammar.c"
        break;
      case 73: /* num ::= num POW num */
#line 750 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = pow(yymsp[-2].minor.yy0.data.number,yymsp[0].minor.yy0.data.number);
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1726 "./src/Grammar/grammar.c"
        break;
      case 74: /* array ::= array PLUSPLUS array */
#line 760 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = ARRAY;
    yygotominor.yy0.data.array = new std::vector<panopticon::object>();
    yygotominor.yy0.data.array->reserve(yymsp[-2].minor.yy0.data.array->size()+yymsp[0].minor.yy0.data.array->size());
    for(int i=0;i<yymsp[-2].minor.yy0.data.array->size();++i)
    {
        yygotominor.yy0.data.array->push_back(yymsp[-2].minor.yy0.data.array->at(i));
    }
    for(int i=0;i<yymsp[0].minor.yy0.data.array->size();++i)
    {
        yygotominor.yy0.data.array->push_back(yymsp[0].minor.yy0.data.array->at(i));
    }
    delete yymsp[-2].minor.yy0.data.array;
    delete yymsp[0].minor.yy0.data.array;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1746 "./src/Grammar/grammar.c"
        break;
      case 75: /* array ::= array PLUS array */
#line 777 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = ARRAY;
    if(panopticon::is_numerical(yymsp[-2].minor.yy0)&&is_numerical(yymsp[0].minor.yy0))
    {
        panopticon::add_numerical_arrays(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);

    }
    else
    {
        yygotominor.yy0.data.array = new std::vector<panopticon::object>();
        yygotominor.yy0.data.array->reserve(yymsp[-2].minor.yy0.data.array->size()+yymsp[0].minor.yy0.data.array->size());
        for(int i=0;i<yymsp[-2].minor.yy0.data.array->size();++i)
        {
            yygotominor.yy0.data.array->push_back(yymsp[-2].minor.yy0.data.array->at(i));
        }
        for(int i=0;i<yymsp[0].minor.yy0.data.array->size();++i)
        {
            yygotominor.yy0.data.array->push_back(yymsp[0].minor.yy0.data.array->at(i));
        }
    }
    delete yymsp[-2].minor.yy0.data.array;
    delete yymsp[0].minor.yy0.data.array;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1774 "./src/Grammar/grammar.c"
        break;
      case 76: /* array ::= num PLUS array */
#line 806 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = ARRAY;
    if(panopticon::is_numerical(yymsp[0].minor.yy0))
    {
        panopticon::add_number_to_array(yygotominor.yy0,yymsp[0].minor.yy0,yymsp[-2].minor.yy0);
    }
    else
    {
        yygotominor.yy0.data.array = new std::vector<panopticon::object>();
        yygotominor.yy0.data.array->reserve(yymsp[0].minor.yy0.data.array->size() + 1);
        yygotominor.yy0.data.array->push_back(yymsp[-2].minor.yy0);
        for(int i=0;i<yymsp[0].minor.yy0.data.array->size();++i)
        {
            yygotominor.yy0.data.array->push_back(yymsp[0].minor.yy0.data.array->at(i));
        }

    }
    delete yymsp[0].minor.yy0.data.array;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1798 "./src/Grammar/grammar.c"
        break;
      case 77: /* array ::= array PLUS num */
#line 827 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = ARRAY;
    if(panopticon::is_numerical(yymsp[-2].minor.yy0))
    {
        panopticon::add_number_to_array(yygotominor.yy0,yymsp[0].minor.yy0,yymsp[-2].minor.yy0);
    }
    else
    {
        yygotominor.yy0.data.array = new std::vector<panopticon::object>();
        yygotominor.yy0.data.array->reserve(yymsp[-2].minor.yy0.data.array->size() + 1);
        for(int i=0;i<yymsp[-2].minor.yy0.data.array->size();++i)
        {
            yygotominor.yy0.data.array->push_back(yymsp[-2].minor.yy0.data.array->at(i));
        }
        yygotominor.yy0.data.array->push_back(yymsp[0].minor.yy0);
    }

    delete yymsp[-2].minor.yy0.data.array;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1822 "./src/Grammar/grammar.c"
        break;
      case 78: /* array ::= num PLUSPLUS array */
#line 848 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = ARRAY;
        yygotominor.yy0.data.array = new std::vector<panopticon::object>();
        yygotominor.yy0.data.array->reserve(yymsp[0].minor.yy0.data.array->size() + 1);
        yygotominor.yy0.data.array->push_back(yymsp[-2].minor.yy0);
        for(int i=0;i<yymsp[0].minor.yy0.data.array->size();++i)
        {
            yygotominor.yy0.data.array->push_back(yymsp[0].minor.yy0.data.array->at(i));
        }
    delete yymsp[0].minor.yy0.data.array;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1838 "./src/Grammar/grammar.c"
        break;
      case 79: /* array ::= array PLUSPLUS num */
#line 861 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = ARRAY;
        yygotominor.yy0.data.array = new std::vector<panopticon::object>();
        yygotominor.yy0.data.array->reserve(yymsp[-2].minor.yy0.data.array->size() + 1);
        for(int i=0;i<yymsp[-2].minor.yy0.data.array->size();++i)
        {
            yygotominor.yy0.data.array->push_back(yymsp[-2].minor.yy0.data.array->at(i));
        }
        yygotominor.yy0.data.array->push_back(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0.data.array;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1854 "./src/Grammar/grammar.c"
        break;
      case 80: /* value ::= array LBRAC num RBRAC */
#line 874 "./src/Grammar/grammar.y"
{
    if(yymsp[-1].minor.yy0.data.number<yymsp[-3].minor.yy0.data.array->size())
    {
        yygotominor.yy0 = panopticon::copy_object(yymsp[-3].minor.yy0.data.array->at(yymsp[-1].minor.yy0.data.number));
/*        yygotominor.yy0.data.number = yymsp[-1].minor.yy0.data.number;*/
    }
    else
    {
        out() << "Error p0008: Index out of bounds." << std::endl;
    }
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1871 "./src/Grammar/grammar.c"
        break;
      case 81: /* in ::= error */
#line 929 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy111)
    {
    case OpenQuoteError:
/*        out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 1886 "./src/Grammar/grammar.c"
        break;
      case 82: /* error ::= OPENQUOTEERROR */
#line 942 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy111 = OpenQuoteError;
    out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1895 "./src/Grammar/grammar.c"
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
#line 70 "./src/Grammar/grammar.y"

out() << "Syntax error!" << std::endl;
#line 1962 "./src/Grammar/grammar.c"
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
#line 65 "./src/Grammar/grammar.y"

printf("parsing complete!\n\n\n");
#line 1984 "./src/Grammar/grammar.c"
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
