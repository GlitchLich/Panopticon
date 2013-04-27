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
#undef STRING
#undef NUM
#undef BOOL
#undef ARRAY

using namespace panopticon;

    void token_destructor(Token t)
    {
/*    std::cout << "In token_destructor t.value= " << t.value << std::endl;*/
/*    std::cout << "In token_destructor t.n= " << t.n << std::endl;*/
    }
#line 39 "./src/Grammar/grammar.c"
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
#define YYNSTATE 143
#define YYNRULE 84
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
#define YY_ACTTAB_COUNT (555)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    24,   25,  141,   20,   21,   29,   28,   30,   27,   31,
 /*    10 */    26,   23,   22,   50,   34,   32,   33,   19,   18,    8,
 /*    20 */    37,   48,   38,   16,   36,  127,    7,   24,   25,   36,
 /*    30 */    20,   21,   29,   28,   30,   27,   31,   26,   23,   22,
 /*    40 */    50,   34,   32,   33,   19,   18,  124,   44,   46,   38,
 /*    50 */    49,   47,   44,   46,   48,  123,  121,   24,   25,   48,
 /*    60 */    20,   21,   29,   28,   30,   27,   31,   26,   23,   22,
 /*    70 */    50,   34,   32,   33,   19,   18,  229,   24,   25,   38,
 /*    80 */    20,   21,   29,   28,   30,   27,   31,   26,   23,   22,
 /*    90 */     6,   34,   32,   33,   19,   18,  229,  229,   25,    5,
 /*   100 */    20,   21,   29,   28,   30,   27,   31,   26,   23,   22,
 /*   110 */    50,   34,   32,   33,   19,   18,   81,   94,   78,   38,
 /*   120 */    20,   21,   29,   28,   30,   27,   31,   26,   23,   22,
 /*   130 */    50,   34,   32,   33,   19,   18,  229,   24,   25,   38,
 /*   140 */    20,   21,   29,   28,   30,   27,   31,   26,   23,   22,
 /*   150 */   229,  229,   32,   33,   19,   18,   82,   93,   96,    5,
 /*   160 */    21,   29,   28,   30,   27,   31,   26,   23,   22,   50,
 /*   170 */    34,   32,   33,   19,   18,   97,  118,  111,   38,   29,
 /*   180 */    28,   30,   27,   31,   26,   23,   22,   50,   34,   32,
 /*   190 */    33,   19,   18,   55,   92,   78,   38,   30,   27,   31,
 /*   200 */    26,   23,   22,   50,   34,   32,   33,   19,   18,  137,
 /*   210 */   229,  229,   38,  120,  140,  139,  138,  136,  135,  134,
 /*   220 */   229,   95,  229,  119,   54,   66,   75,  229,   45,   41,
 /*   230 */    42,   40,   43,   39,  229,   16,   49,   47,   44,   46,
 /*   240 */   122,   36,  137,  228,    1,   48,  229,  229,  128,  133,
 /*   250 */   136,  135,  134,    3,   95,  107,  119,   54,   66,   75,
 /*   260 */    45,   41,   42,   40,   43,   39,  137,  229,   49,   47,
 /*   270 */    44,   46,  143,  132,  136,  135,  134,   48,   95,  229,
 /*   280 */   119,   54,   66,   75,   18,   12,   13,   10,   38,  229,
 /*   290 */    15,   14,   17,   11,  229,  229,  229,   35,   37,  229,
 /*   300 */     2,   16,  229,  142,  131,  130,  129,   36,  229,   42,
 /*   310 */    40,   43,   39,  229,  229,   49,   47,   44,   46,  229,
 /*   320 */   125,   56,   66,   75,   48,   23,   22,   50,   34,   32,
 /*   330 */    33,   19,   18,   12,   13,  229,   38,  229,   15,   14,
 /*   340 */   229,   32,   33,   19,   18,  229,   37,    4,   38,   16,
 /*   350 */    32,   33,   19,   18,   10,   36,    7,    5,  126,   17,
 /*   360 */    11,    9,  229,  229,   35,  106,  229,    2,   58,   67,
 /*   370 */    78,  131,  130,  129,   50,   34,   32,   33,   19,   18,
 /*   380 */    10,  229,  229,   38,  229,   17,   11,  229,   13,  229,
 /*   390 */    35,  108,   15,   14,   80,   94,   78,  131,  130,  129,
 /*   400 */    37,  229,  229,   16,   15,   14,   55,  117,   78,   36,
 /*   410 */   229,  229,   37,  229,  229,   16,  229,  229,  229,  110,
 /*   420 */   229,   36,   53,  115,   78,  109,  229,  229,   59,   67,
 /*   430 */    78,   55,   73,   78,  229,  229,   55,  116,   78,   55,
 /*   440 */    88,   78,  229,   55,   87,   78,   55,   72,   78,   55,
 /*   450 */    86,   78,   55,   85,   78,  229,   55,  115,   78,   55,
 /*   460 */    91,  105,   55,  114,   78,   52,   65,   74,   84,   67,
 /*   470 */    78,  229,  104,   67,   78,  103,   67,   78,   71,   67,
 /*   480 */    78,   70,   67,   78,   64,   67,   78,  229,  229,   63,
 /*   490 */    67,   78,   69,   67,   78,  229,   68,   67,   78,   60,
 /*   500 */    67,   78,   57,   67,   78,   77,   67,   78,  229,   76,
 /*   510 */    67,   78,   62,   67,   78,   61,   67,   78,  102,   67,
 /*   520 */    78,  101,   67,   78,  229,  100,   67,  113,   55,   67,
 /*   530 */   112,   55,   67,   90,   55,   67,   89,   55,   67,   83,
 /*   540 */   229,  229,   55,   67,   79,   99,   67,   78,  229,   98,
 /*   550 */    67,   78,   51,   67,   78,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    2,   31,    4,    5,    6,    7,    8,    9,   10,
 /*    10 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   14,
 /*    20 */    14,   23,   23,   17,   23,   26,   23,    1,    2,   23,
 /*    30 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*    40 */    14,   15,   16,   17,   18,   19,   29,   16,   17,   23,
 /*    50 */    14,   15,   16,   17,   23,   29,   35,    1,    2,   23,
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
 /*   310 */     9,   10,   11,   55,   55,   14,   15,   16,   17,   55,
 /*   320 */    51,   52,   53,   54,   23,   12,   13,   14,   15,   16,
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
 /*   550 */    53,   54,   52,   53,   54,
};
#define YY_SHIFT_USE_DFLT (-30)
#define YY_SHIFT_COUNT (120)
#define YY_SHIFT_MIN   (-29)
#define YY_SHIFT_MAX   (398)
static const short yy_shift_ofst[] = {
 /*     0 */    21,  272,  339,  339,  339,  339,  339,  339,  365,  365,
 /*    10 */   365,  365,  365,  365,  365,  365,  365,  365,  365,  365,
 /*    20 */   365,  365,  365,  365,  365,  365,  365,  365,  365,  365,
 /*    30 */   365,  365,  365,  365,  365,  365,  365,  365,  365,  365,
 /*    40 */   365,  365,  365,  365,  365,  365,  365,  365,  365,  365,
 /*    50 */   365,   26,   -1,   76,   76,   56,   56,   96,  136,  136,
 /*    60 */   116,  155,  173,  189,  189,  222,  254,  254,  313,  313,
 /*    70 */   313,  313,  301,  301,  332,  284,  360,  360,  284,  386,
 /*    80 */   334,  325,  325,  398,  325,   36,   36,   36,   36,    6,
 /*    90 */     6,   31,   31,   31,   31,  333,  218,  265,  265,  265,
 /*   100 */   265,  265,  265,  265,  265,  218,    3,   17,    3,    3,
 /*   110 */     3,    1,    1,    1,   -2,   -2,   -2,   -2,   -2,    5,
 /*   120 */   -29,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (50)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (500)
static const short yy_reduce_ofst[] = {
 /*     0 */   204,  172,  205,  229,  376,  370,  342,  316,  269,  500,
 /*    10 */   497,  493,  490,  485,  482,  479,  476,  473,  469,  466,
 /*    20 */   463,  460,  457,  453,  450,  447,  444,  440,  437,  432,
 /*    30 */   429,  426,  423,  420,  416,  413,  410,  407,  404,  400,
 /*    40 */   397,  394,  391,  387,  384,  379,  354,  141,  123,  104,
 /*    50 */    64,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   144,  227,  158,  159,  227,  227,  227,  227,  227,  227,
 /*    10 */   227,  227,  227,  227,  227,  227,  227,  227,  227,  227,
 /*    20 */   227,  227,  227,  227,  227,  227,  227,  227,  227,  227,
 /*    30 */   227,  227,  227,  227,  227,  227,  227,  227,  227,  227,
 /*    40 */   227,  227,  227,  227,  227,  227,  227,  227,  227,  227,
 /*    50 */   227,  227,  227,  227,  161,  227,  161,  207,  222,  220,
 /*    60 */   206,  212,  211,  203,  202,  227,  162,  227,  205,  204,
 /*    70 */   201,  200,  192,  188,  227,  163,  210,  209,  227,  181,
 /*    80 */   197,  197,  167,  180,  196,  194,  193,  191,  190,  179,
 /*    90 */   178,  173,  184,  185,  169,  156,  171,  168,  214,  213,
 /*   100 */   208,  216,  215,  199,  198,  176,  217,  227,  219,  218,
 /*   110 */   221,  172,  177,  182,  174,  170,  189,  187,  186,  160,
 /*   120 */   227,  226,  225,  223,  157,  224,  175,  195,  183,  166,
 /*   130 */   165,  164,  155,  154,  153,  152,  151,  150,  149,  148,
 /*   140 */   147,  146,  145,
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
 /*  80 */ "stmt ::= array LBRAC num RBRAC",
 /*  81 */ "value ::= value PLUS value",
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
#line 38 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 655 "./src/Grammar/grammar.c"
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
  { 44, 4 },
  { 51, 3 },
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
#line 74 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1037 "./src/Grammar/grammar.c"
        break;
      case 4: /* start ::= spec */
#line 85 "./src/Grammar/grammar.y"
{
/*    std::cout << "Result.type="<< yymsp[0].minor.yy0.type << std::endl;*/
    switch(yymsp[0].minor.yy0.type)
    {
    case panopticon::NUMBER:
        std::cout << yymsp[0].minor.yy0.data.number << std::endl;
        break;
    case panopticon::STRING:
        std::cout << *yymsp[0].minor.yy0.data.string << std::endl;
        delete yymsp[0].minor.yy0.data.string;
        break;
    case panopticon::BOOL:
        if(yymsp[0].minor.yy0.data.boolean)
        {
            std::cout << "true" << std::endl;
        }
        else
        {
            std::cout << "false" << std::endl;
        }
        break;
    case panopticon::ARRAY:
/*        std::cout << "printing array" << std::endl;*/
        panopticon::print_array(yymsp[0].minor.yy0);
        panopticon::delete_array(yymsp[0].minor.yy0);
        break;
    }

}
#line 1070 "./src/Grammar/grammar.c"
        break;
      case 5: /* spec ::= top_stmt */
      case 6: /* top_stmt ::= stmt */ yytestcase(yyruleno==6);
      case 8: /* expr ::= retval */ yytestcase(yyruleno==8);
#line 117 "./src/Grammar/grammar.y"
{
    /*yygotominor.yy0.type = yymsp[0].minor.yy0.type;
    switch(yymsp[0].minor.yy0.type)
    {
    case NUMBER:
        yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
        break;
    case STRING:
        std::cout << "copying" << std::endl;
        yygotominor.yy0.data.string = new String(yymsp[0].minor.yy0.data.string->c_str());
        break;
    case BOOLEAN:
        yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    case ARRAY:
        yygotominor.yy0.data.array = yymsp[0].minor.yy0.data.array;
        break;
    }
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;*/
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1097 "./src/Grammar/grammar.c"
        break;
      case 7: /* stmt ::= expr */
#line 162 "./src/Grammar/grammar.y"
{
    /*yygotominor.yy0.type = yymsp[0].minor.yy0.type;
    switch(yymsp[0].minor.yy0.type)
    {
    case NUMBER:
        yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
        break;
    case STRING:
        std::cout << "copying" << std::endl;
        yygotominor.yy0.data.string = new String(yymsp[0].minor.yy0.data.string->c_str());
        break;
    case BOOLEAN:
        yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    case ARRAY:
        yygotominor.yy0.data.array = yymsp[0].minor.yy0.data.array;
        break;
    }
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;*/
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1122 "./src/Grammar/grammar.c"
        break;
      case 9: /* retval ::= access */
      case 10: /* access ::= identifier */ yytestcase(yyruleno==10);
#line 209 "./src/Grammar/grammar.y"
{
    /*yygotominor.yy0.type = yymsp[0].minor.yy0.type;
    switch(yymsp[0].minor.yy0.type)
    {
    case NUMBER:
        yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
        break;
    case STRING:
        std::cout << "copying" << std::endl;
        yygotominor.yy0.data.string = new String(yymsp[0].minor.yy0.data.string->c_str());
        break;
    case BOOLEAN:
        yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
        break;
    case ARRAY:
        yygotominor.yy0.data.array = yymsp[0].minor.yy0.data.array;
        break;
    }
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;*/
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1149 "./src/Grammar/grammar.c"
        break;
      case 11: /* stmt_list ::= stmt */
#line 266 "./src/Grammar/grammar.y"
{
/*
    yygotominor.yy0.type = yymsp[0].minor.yy0.type;
    switch(yymsp[0].minor.yy0.type)
    {
    case NUMBER:
        yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
        break;
    case STRING:
        std::cout << "copying" << std::endl;
        yygotominor.yy0.data.string = new String(yymsp[0].minor.yy0.data.string->c_str());
        break;
    case BOOLEAN:
        yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    case ARRAY:
        yygotominor.yy0 = yymsp[0].minor.yy0;
    }
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;*/
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1174 "./src/Grammar/grammar.c"
        break;
      case 12: /* stmt_list ::= stmt_list stmt */
#line 289 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    if(yymsp[-1].minor.yy0.type!=STATEMENT_LIST)
    {
/*        yygotominor.yy0.data.array = new std::vector<panopticon::object>();*/
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
#line 1194 "./src/Grammar/grammar.c"
        break;
      case 13: /* access ::= array */
#line 308 "./src/Grammar/grammar.y"
{
/*    yygotominor.yy0.type = panopticon::ARRAY;*/
/*    yygotominor.yy0.data.array = yymsp[0].minor.yy0.data.array;*/
/*    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;*/
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1204 "./src/Grammar/grammar.c"
        break;
      case 14: /* array ::= LBRAC maybe_empty_stmt_list RBRAC */
#line 316 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::ARRAY;
    yygotominor.yy0.data.array = yymsp[-1].minor.yy0.data.array;
    //yygotominor.yy0.n = yymsp[-1].minor.yy0.n+1;
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1215 "./src/Grammar/grammar.c"
        break;
      case 15: /* maybe_empty_stmt_list ::= */
#line 323 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
/*    yygotominor.yy0.data.array = new std::vector<panopticon::object>();*/
    panopticon::create_array(yygotominor.yy0);
/*    yygotominor.yy0.n = 0;*/
}
#line 1225 "./src/Grammar/grammar.c"
        break;
      case 16: /* maybe_empty_stmt_list ::= stmt_list */
#line 331 "./src/Grammar/grammar.y"
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
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1242 "./src/Grammar/grammar.c"
        break;
      case 17: /* identifier ::= value */
#line 346 "./src/Grammar/grammar.y"
{
    /*
    yygotominor.yy0.type = panopticon::yymsp[0].minor.yy0.type;
    switch(yymsp[0].minor.yy0.type)
    {
    case NUMBER:
        yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
        break;
    case STRING:
        std::cout << "copying" << std::endl;
        yygotominor.yy0.data.string = new String(yymsp[0].minor.yy0.data.string->c_str());
        break;
    case BOOLEAN:
        yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    }
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
    */
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1266 "./src/Grammar/grammar.c"
        break;
      case 18: /* value ::= num */
      case 20: /* value ::= bool */ yytestcase(yyruleno==20);
#line 372 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1274 "./src/Grammar/grammar.c"
        break;
      case 19: /* value ::= string */
#line 377 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1282 "./src/Grammar/grammar.c"
        break;
      case 21: /* num ::= NUM */
#line 407 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.type = panopticon::NUMBER;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1291 "./src/Grammar/grammar.c"
        break;
      case 22: /* string ::= STRING */
#line 414 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1301 "./src/Grammar/grammar.c"
        break;
      case 23: /* bool ::= BOOLEAN */
#line 423 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    yygotominor.yy0.type = panopticon::BOOL;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1310 "./src/Grammar/grammar.c"
        break;
      case 24: /* string ::= string PLUS num */
#line 434 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::string_plus_num(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1320 "./src/Grammar/grammar.c"
        break;
      case 25: /* string ::= string PLUSPLUS num */
#line 441 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::string_plusplus_num(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1330 "./src/Grammar/grammar.c"
        break;
      case 26: /* string ::= num PLUS string */
#line 448 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::num_plus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1340 "./src/Grammar/grammar.c"
        break;
      case 27: /* string ::= num PLUSPLUS string */
#line 455 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::num_plusplus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1350 "./src/Grammar/grammar.c"
        break;
      case 28: /* string ::= string PLUS bool */
#line 462 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::string_plus_bool(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1360 "./src/Grammar/grammar.c"
        break;
      case 29: /* string ::= string PLUSPLUS bool */
#line 469 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::string_plusplus_bool(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1370 "./src/Grammar/grammar.c"
        break;
      case 30: /* string ::= bool PLUS string */
#line 476 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::bool_plus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1380 "./src/Grammar/grammar.c"
        break;
      case 31: /* string ::= bool PLUSPLUS string */
#line 483 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = panopticon::STRING;
        panopticon::bool_plusplus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1390 "./src/Grammar/grammar.c"
        break;
      case 32: /* bool ::= LPAREN bool RPAREN */
#line 493 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-1].minor.yy0.data.boolean;
    //yygotominor.yy0.n = yymsp[-1].minor.yy0.n+1;
  yy_destructor(yypParser,25,&yymsp[-2].minor);
  yy_destructor(yypParser,26,&yymsp[0].minor);
}
#line 1401 "./src/Grammar/grammar.c"
        break;
      case 33: /* bool ::= bool PLUS bool */
#line 500 "./src/Grammar/grammar.y"
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
#line 1418 "./src/Grammar/grammar.c"
        break;
      case 34: /* bool ::= bool TIMES bool */
#line 514 "./src/Grammar/grammar.y"
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
#line 1435 "./src/Grammar/grammar.c"
        break;
      case 35: /* bool ::= bool EQUALTO bool */
#line 528 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.boolean == yymsp[0].minor.yy0.data.boolean;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1445 "./src/Grammar/grammar.c"
        break;
      case 36: /* bool ::= bool NOTEQUALTO bool */
      case 60: /* bool ::= num NOTEQUALTO num */ yytestcase(yyruleno==60);
#line 535 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number != yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1456 "./src/Grammar/grammar.c"
        break;
      case 37: /* bool ::= bool AND bool */
#line 542 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = (int)yymsp[-2].minor.yy0.data.boolean && (int)yymsp[0].minor.yy0.data.boolean;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,2,&yymsp[-1].minor);
}
#line 1466 "./src/Grammar/grammar.c"
        break;
      case 38: /* bool ::= bool OR bool */
#line 549 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = (int)yymsp[-2].minor.yy0.data.boolean || (int)yymsp[0].minor.yy0.data.boolean;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1476 "./src/Grammar/grammar.c"
        break;
      case 39: /* bool ::= NOT bool */
#line 556 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = !((int)yymsp[0].minor.yy0.data.boolean);
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1486 "./src/Grammar/grammar.c"
        break;
      case 40: /* string ::= LPAREN string RPAREN */
#line 622 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = yymsp[-1].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[-1].minor.yy0.n+1;
  yy_destructor(yypParser,25,&yymsp[-2].minor);
  yy_destructor(yypParser,26,&yymsp[0].minor);
}
#line 1497 "./src/Grammar/grammar.c"
        break;
      case 41: /* string ::= string MINUS string */
#line 629 "./src/Grammar/grammar.y"
{
    panopticon::string_minus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1507 "./src/Grammar/grammar.c"
        break;
      case 42: /* string ::= string PLUS string */
#line 636 "./src/Grammar/grammar.y"
{
    panopticon::string_plus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1517 "./src/Grammar/grammar.c"
        break;
      case 43: /* string ::= string PLUSPLUS string */
#line 643 "./src/Grammar/grammar.y"
{
    panopticon::string_plusplus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1527 "./src/Grammar/grammar.c"
        break;
      case 44: /* num ::= string TIMES string */
#line 650 "./src/Grammar/grammar.y"
{
    if(is_number(*yymsp[-2].minor.yy0.data.string) && is_number(*yymsp[0].minor.yy0.data.string))
    {
        yygotominor.yy0.type = panopticon::NUMBER;
        yygotominor.yy0.data.number = string_to_double(*yymsp[-2].minor.yy0.data.string) * string_to_double(*yymsp[0].minor.yy0.data.string);
    }
    else
    {
/*        yygotominor.yy0 = panopticon::MulStringError;*/
        std::cerr << "Error p0002: Attempted to Multiply a string by a string, and at least one is non-numerical: " << std::endl;
        std::cerr << "String 1: " << *yymsp[-2].minor.yy0.data.string << std::endl;
        std::cerr << "String 2: " << *yymsp[0].minor.yy0.data.string << std::endl;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1546 "./src/Grammar/grammar.c"
        break;
      case 45: /* bool ::= string EQUALTO string */
#line 666 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->compare(*yymsp[0].minor.yy0.data.string)==0;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1556 "./src/Grammar/grammar.c"
        break;
      case 46: /* num ::= string DIVIDE string */
#line 673 "./src/Grammar/grammar.y"
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
        std::cerr << "Error p0002: Attempted to Multiply a string by a string, and at least one is non-numerical: " << std::endl;
        std::cerr << "String 1: " << *yymsp[-2].minor.yy0.data.string << std::endl;
        std::cerr << "String 2: " << *yymsp[0].minor.yy0.data.string << std::endl;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1577 "./src/Grammar/grammar.c"
        break;
      case 47: /* bool ::= string LESSTHAN string */
#line 691 "./src/Grammar/grammar.y"
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
#line 1596 "./src/Grammar/grammar.c"
        break;
      case 48: /* bool ::= string GREATERTHAN string */
#line 707 "./src/Grammar/grammar.y"
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
#line 1615 "./src/Grammar/grammar.c"
        break;
      case 49: /* bool ::= string NOTEQUALTO string */
#line 723 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->compare(*yymsp[0].minor.yy0.data.string)!=0;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1625 "./src/Grammar/grammar.c"
        break;
      case 50: /* bool ::= string GORE string */
#line 731 "./src/Grammar/grammar.y"
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
#line 1644 "./src/Grammar/grammar.c"
        break;
      case 51: /* bool ::= string LORE string */
#line 747 "./src/Grammar/grammar.y"
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
#line 1663 "./src/Grammar/grammar.c"
        break;
      case 52: /* num ::= LPAREN num RPAREN */
#line 766 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = yymsp[-1].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-1].minor.yy0.n+1;
  yy_destructor(yypParser,25,&yymsp[-2].minor);
  yy_destructor(yypParser,26,&yymsp[0].minor);
}
#line 1674 "./src/Grammar/grammar.c"
        break;
      case 53: /* num ::= num MINUS num */
#line 773 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = yymsp[-2].minor.yy0.data.number - yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1684 "./src/Grammar/grammar.c"
        break;
      case 54: /* num ::= num PLUS num */
#line 780 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = yymsp[-2].minor.yy0.data.number + yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1694 "./src/Grammar/grammar.c"
        break;
      case 55: /* num ::= num TIMES num */
#line 787 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = yymsp[-2].minor.yy0.data.number * yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1704 "./src/Grammar/grammar.c"
        break;
      case 56: /* num ::= num DIVIDE num */
#line 794 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    if(yymsp[0].minor.yy0.data.number != 0)
    {
         yygotominor.yy0.data.number = yymsp[-2].minor.yy0.data.number / yymsp[0].minor.yy0.data.number;
/*         yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1 + yymsp[0].minor.yy0.n+1;*/
    }
    else
    {
         std::cout << "divide by zero" << std::endl;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1721 "./src/Grammar/grammar.c"
        break;
      case 57: /* bool ::= num LESSTHAN num */
#line 808 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number < yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1731 "./src/Grammar/grammar.c"
        break;
      case 58: /* bool ::= num GREATERTHAN num */
#line 815 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number > yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1741 "./src/Grammar/grammar.c"
        break;
      case 59: /* bool ::= num EQUALTO num */
#line 822 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number == yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1751 "./src/Grammar/grammar.c"
        break;
      case 61: /* bool ::= num GORE num */
#line 836 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number >= yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1761 "./src/Grammar/grammar.c"
        break;
      case 62: /* bool ::= num LORE num */
#line 843 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number <= yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1771 "./src/Grammar/grammar.c"
        break;
      case 63: /* bool ::= num AND num */
#line 850 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = (int)yymsp[-2].minor.yy0.data.number && (int)yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,2,&yymsp[-1].minor);
}
#line 1781 "./src/Grammar/grammar.c"
        break;
      case 64: /* bool ::= num OR num */
#line 857 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = (int)yymsp[-2].minor.yy0.data.number || (int)yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1791 "./src/Grammar/grammar.c"
        break;
      case 65: /* bool ::= NOT num */
#line 864 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::BOOL;
    yygotominor.yy0.data.boolean = !((int)yymsp[0].minor.yy0.data.number);
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1801 "./src/Grammar/grammar.c"
        break;
      case 66: /* num ::= num SHIFTL num */
#line 871 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = (int)yymsp[-2].minor.yy0.data.number << (int)yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1811 "./src/Grammar/grammar.c"
        break;
      case 67: /* num ::= num SHIFTR num */
#line 878 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = (int)yymsp[-2].minor.yy0.data.number >> (int)yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1821 "./src/Grammar/grammar.c"
        break;
      case 68: /* num ::= num BITAND num */
#line 885 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = (int)yymsp[-2].minor.yy0.data.number & (int)yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1831 "./src/Grammar/grammar.c"
        break;
      case 69: /* num ::= num BITOR num */
#line 892 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = (int)yymsp[-2].minor.yy0.data.number | (int)yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,4,&yymsp[-1].minor);
}
#line 1841 "./src/Grammar/grammar.c"
        break;
      case 70: /* num ::= BITNOT num */
#line 899 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = ~((int)yymsp[0].minor.yy0.data.number);
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1851 "./src/Grammar/grammar.c"
        break;
      case 71: /* num ::= MINUS num */
#line 906 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = -1 * yymsp[0].minor.yy0.data.number;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1861 "./src/Grammar/grammar.c"
        break;
      case 72: /* num ::= num MODULO num */
#line 913 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = fmod(yymsp[-2].minor.yy0.data.number,yymsp[0].minor.yy0.data.number);
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1871 "./src/Grammar/grammar.c"
        break;
      case 73: /* num ::= num POW num */
#line 920 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::NUMBER;
    yygotominor.yy0.data.number = pow(yymsp[-2].minor.yy0.data.number,yymsp[0].minor.yy0.data.number);
    //yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1881 "./src/Grammar/grammar.c"
        break;
      case 74: /* array ::= array PLUSPLUS array */
#line 930 "./src/Grammar/grammar.y"
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
#line 1901 "./src/Grammar/grammar.c"
        break;
      case 75: /* array ::= array PLUS array */
#line 947 "./src/Grammar/grammar.y"
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
#line 1929 "./src/Grammar/grammar.c"
        break;
      case 76: /* array ::= num PLUS array */
#line 976 "./src/Grammar/grammar.y"
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
#line 1953 "./src/Grammar/grammar.c"
        break;
      case 77: /* array ::= array PLUS num */
#line 997 "./src/Grammar/grammar.y"
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
#line 1977 "./src/Grammar/grammar.c"
        break;
      case 78: /* array ::= num PLUSPLUS array */
#line 1018 "./src/Grammar/grammar.y"
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
#line 1993 "./src/Grammar/grammar.c"
        break;
      case 79: /* array ::= array PLUSPLUS num */
#line 1031 "./src/Grammar/grammar.y"
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
#line 2009 "./src/Grammar/grammar.c"
        break;
      case 80: /* stmt ::= array LBRAC num RBRAC */
#line 1044 "./src/Grammar/grammar.y"
{
    if(yymsp[-1].minor.yy0.data.number<yymsp[-3].minor.yy0.data.array->size())
    {
        yygotominor.yy0 = yymsp[-3].minor.yy0.data.array->at(yymsp[-1].minor.yy0.data.number);
    }
    else
    {
        std::cerr << "Error p0008: Index out of bounds." << std::endl;
        yygotominor.yy0 = yymsp[-3].minor.yy0;
    }
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 2026 "./src/Grammar/grammar.c"
        break;
      case 81: /* value ::= value PLUS value */
#line 1056 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 2033 "./src/Grammar/grammar.c"
        break;
      case 82: /* in ::= error */
#line 1065 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy111)
    {
    case OpenQuoteError:
/*        std::cerr << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        std::cerr << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 2048 "./src/Grammar/grammar.c"
        break;
      case 83: /* error ::= OPENQUOTEERROR */
#line 1078 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy111 = OpenQuoteError;
    std::cerr << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 2057 "./src/Grammar/grammar.c"
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
#line 68 "./src/Grammar/grammar.y"

std::cout << "Syntax error!" << std::endl;
#line 2124 "./src/Grammar/grammar.c"
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
#line 63 "./src/Grammar/grammar.y"

printf("parsing complete!\n\n\n");
#line 2146 "./src/Grammar/grammar.c"
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
