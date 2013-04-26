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
#undef STRING
#undef NUM

using namespace panopticon;

    void token_destructor(Token t)
    {
/*    std::cout << "In token_destructor t.value= " << t.value << std::endl;*/
/*    std::cout << "In token_destructor t.n= " << t.n << std::endl;*/
    }
#line 36 "./src/Grammar/grammar.c"
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
#define YYNOCODE 51
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy101;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 117
#define YYNRULE 69
#define YYERRORSYMBOL 35
#define YYERRSYMDT yy101
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
#define YY_ACTTAB_COUNT (431)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    16,   17,   40,   12,   13,   21,   20,   22,   19,   23,
 /*    10 */    18,   15,   14,   42,   26,   24,   25,   11,   10,   67,
 /*    20 */    80,   65,   30,  115,  103,   28,   16,   17,  100,   12,
 /*    30 */    13,   21,   20,   22,   19,   23,   18,   15,   14,   42,
 /*    40 */    26,   24,   25,   11,   10,  188,  188,   17,   30,   12,
 /*    50 */    13,   21,   20,   22,   19,   23,   18,   15,   14,   42,
 /*    60 */    26,   24,   25,   11,   10,   68,   79,   81,   30,   12,
 /*    70 */    13,   21,   20,   22,   19,   23,   18,   15,   14,   42,
 /*    80 */    26,   24,   25,   11,   10,   82,   98,   91,   30,   13,
 /*    90 */    21,   20,   22,   19,   23,   18,   15,   14,   42,   26,
 /*   100 */    24,   25,   11,   10,   44,   78,   65,   30,   21,   20,
 /*   110 */    22,   19,   23,   18,   15,   14,   42,   26,   24,   25,
 /*   120 */    11,   10,   44,   97,   65,   30,   22,   19,   23,   18,
 /*   130 */    15,   14,   42,   26,   24,   25,   11,   10,   44,   60,
 /*   140 */    65,   30,   37,   33,   34,   32,   35,   31,   36,   38,
 /*   150 */    41,   39,   36,   38,    8,   40,   44,   96,   65,   40,
 /*   160 */    28,  104,   44,   74,   65,  188,   37,   33,   34,   32,
 /*   170 */    35,   31,  188,  188,   41,   39,   36,   38,  101,  188,
 /*   180 */   111,  187,    1,   40,   99,  114,  113,  112,  110,  109,
 /*   190 */   108,   45,   53,   62,   34,   32,   35,   31,  188,  188,
 /*   200 */    41,   39,   36,   38,  117,   44,   73,   65,  188,   40,
 /*   210 */    15,   14,   42,   26,   24,   25,   11,   10,  188,    2,
 /*   220 */   188,   30,  188,  188,    9,    3,    4,    5,   27,   10,
 /*   230 */   188,    7,    6,   30,  116,  107,  106,  105,  188,   29,
 /*   240 */    29,  188,    8,    8,   24,   25,   11,   10,   28,   28,
 /*   250 */   102,   30,    4,    5,  188,    2,  188,    7,    6,  188,
 /*   260 */     9,    3,  188,  188,   27,   29,  188,  188,    8,  188,
 /*   270 */   188,  107,  106,  105,   28,  188,   44,   59,   65,  188,
 /*   280 */    42,   26,   24,   25,   11,   10,    5,  188,  188,   30,
 /*   290 */     7,    6,    7,    6,   44,   72,   65,  188,   29,  188,
 /*   300 */    29,    8,  188,    8,  188,  188,  188,   28,  188,   28,
 /*   310 */   188,  188,  188,   41,   39,   36,   38,  188,  188,   44,
 /*   320 */    71,   65,   40,  188,   44,   95,   65,  188,   44,   77,
 /*   330 */    90,  188,   44,   94,   65,  188,  188,   43,   52,   61,
 /*   340 */    70,   54,   65,   89,   54,   65,  188,  188,   88,   54,
 /*   350 */    65,   58,   54,   65,  188,   57,   54,   65,  188,  188,
 /*   360 */   188,   51,   54,   65,   50,   54,   65,   56,   54,   65,
 /*   370 */    55,   54,   65,   47,   54,   65,   46,   54,   65,  188,
 /*   380 */    64,   54,   65,  188,  188,   63,   54,   65,   49,   54,
 /*   390 */    65,   48,   54,   65,  188,  188,   87,   54,   65,   86,
 /*   400 */    54,   65,  188,   85,   54,   93,  188,  188,  188,   44,
 /*   410 */    54,   92,   44,   54,   76,   44,   54,   75,   44,   54,
 /*   420 */    69,   44,   54,   66,   84,   54,   65,  188,   83,   54,
 /*   430 */    65,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    2,   23,    4,    5,    6,    7,    8,    9,   10,
 /*    10 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   47,
 /*    20 */    48,   49,   23,   30,   25,   23,    1,    2,   34,    4,
 /*    30 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    40 */    15,   16,   17,   18,   19,   50,   50,    2,   23,    4,
 /*    50 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    60 */    15,   16,   17,   18,   19,   47,   48,   49,   23,    4,
 /*    70 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    80 */    15,   16,   17,   18,   19,   47,   48,   49,   23,    5,
 /*    90 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   100 */    16,   17,   18,   19,   47,   48,   49,   23,    6,    7,
 /*   110 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   120 */    18,   19,   47,   48,   49,   23,    8,    9,   10,   11,
 /*   130 */    12,   13,   14,   15,   16,   17,   18,   19,   47,   48,
 /*   140 */    49,   23,    6,    7,    8,    9,   10,   11,   16,   17,
 /*   150 */    14,   15,   16,   17,   17,   23,   47,   48,   49,   23,
 /*   160 */    23,   25,   47,   48,   49,   50,    6,    7,    8,    9,
 /*   170 */    10,   11,   50,   50,   14,   15,   16,   17,   35,   50,
 /*   180 */    36,   38,   39,   23,   40,   41,   42,   43,   44,   45,
 /*   190 */    46,   47,   48,   49,    8,    9,   10,   11,   50,   50,
 /*   200 */    14,   15,   16,   17,    0,   47,   48,   49,   50,   23,
 /*   210 */    12,   13,   14,   15,   16,   17,   18,   19,   50,   15,
 /*   220 */    50,   23,   50,   50,   20,   21,    1,    2,   24,   19,
 /*   230 */    50,    6,    7,   23,   30,   31,   32,   33,   50,   14,
 /*   240 */    14,   50,   17,   17,   16,   17,   18,   19,   23,   23,
 /*   250 */    25,   23,    1,    2,   50,   15,   50,    6,    7,   50,
 /*   260 */    20,   21,   50,   50,   24,   14,   50,   50,   17,   50,
 /*   270 */    50,   31,   32,   33,   23,   50,   47,   48,   49,   50,
 /*   280 */    14,   15,   16,   17,   18,   19,    2,   50,   50,   23,
 /*   290 */     6,    7,    6,    7,   47,   48,   49,   50,   14,   50,
 /*   300 */    14,   17,   50,   17,   50,   50,   50,   23,   50,   23,
 /*   310 */    50,   50,   50,   14,   15,   16,   17,   50,   50,   47,
 /*   320 */    48,   49,   23,   50,   47,   48,   49,   50,   47,   48,
 /*   330 */    49,   50,   47,   48,   49,   50,   50,   47,   48,   49,
 /*   340 */    47,   48,   49,   47,   48,   49,   50,   50,   47,   48,
 /*   350 */    49,   47,   48,   49,   50,   47,   48,   49,   50,   50,
 /*   360 */    50,   47,   48,   49,   47,   48,   49,   47,   48,   49,
 /*   370 */    47,   48,   49,   47,   48,   49,   47,   48,   49,   50,
 /*   380 */    47,   48,   49,   50,   50,   47,   48,   49,   47,   48,
 /*   390 */    49,   47,   48,   49,   50,   50,   47,   48,   49,   47,
 /*   400 */    48,   49,   50,   47,   48,   49,   50,   50,   50,   47,
 /*   410 */    48,   49,   47,   48,   49,   47,   48,   49,   47,   48,
 /*   420 */    49,   47,   48,   49,   47,   48,   49,   50,   47,   48,
 /*   430 */    49,
};
#define YY_SHIFT_USE_DFLT (-22)
#define YY_SHIFT_COUNT (99)
#define YY_SHIFT_MIN   (-21)
#define YY_SHIFT_MAX   (299)
static const short yy_shift_ofst[] = {
 /*     0 */    -6,  204,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    10 */   240,  240,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    20 */   240,  240,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    30 */   240,  240,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    40 */   240,  240,  240,   -1,   25,   25,   45,   65,   84,  102,
 /*    50 */   118,  118,  136,  160,  160,  198,  198,  198,  198,  186,
 /*    60 */   186,  225,  251,  266,  266,  251,  284,  228,  228,  286,
 /*    70 */   228,  299,  299,  299,  299,  226,  226,  132,  132,  132,
 /*    80 */   132,  137,  210,  210,  210,  210,  210,  210,  210,  210,
 /*    90 */   137,    2,    2,    2,  -21,  -21,  -21,  -21,  -21,   -7,
};
#define YY_REDUCE_USE_DFLT (-29)
#define YY_REDUCE_COUNT (42)
#define YY_REDUCE_MIN   (-28)
#define YY_REDUCE_MAX   (381)
static const short yy_reduce_ofst[] = {
 /*     0 */   143,  144,  381,  377,  374,  371,  368,  365,  362,  356,
 /*    10 */   352,  349,  344,  341,  338,  333,  329,  326,  323,  320,
 /*    20 */   317,  314,  308,  304,  301,  296,  293,  290,  285,  281,
 /*    30 */   277,  272,  247,  229,  158,  115,  109,   91,   75,   57,
 /*    40 */    38,   18,  -28,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   118,  186,  186,  186,  186,  186,  186,  186,  186,  186,
 /*    10 */   186,  186,  186,  186,  186,  186,  186,  186,  186,  186,
 /*    20 */   186,  186,  186,  186,  186,  186,  186,  186,  186,  186,
 /*    30 */   186,  186,  186,  186,  186,  186,  186,  186,  186,  186,
 /*    40 */   186,  186,  186,  186,  186,  128,  174,  173,  179,  178,
 /*    50 */   170,  169,  186,  129,  186,  172,  171,  168,  167,  159,
 /*    60 */   155,  186,  130,  177,  176,  186,  148,  164,  134,  147,
 /*    70 */   163,  161,  160,  158,  157,  146,  145,  140,  151,  152,
 /*    80 */   136,  138,  135,  181,  180,  175,  183,  182,  166,  165,
 /*    90 */   143,  139,  144,  149,  141,  137,  156,  154,  153,  186,
 /*   100 */   185,  184,  142,  162,  150,  133,  132,  131,  127,  126,
 /*   110 */   125,  124,  123,  122,  121,  120,  119,
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
  "LPAREN",        "RPAREN",        "COMMA",         "LBRAC",       
  "RBRAC",         "ASSIGN",        "NEWLINE",       "NUM",         
  "STRING",        "BOOLEAN",       "OPENQUOTEERROR",  "error",       
  "expr",          "id",            "main",          "in",          
  "start",         "spec",          "top_stmt",      "stmt",        
  "retval",        "invoke",        "value",         "num",         
  "string",        "bool",        
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
 /*   9 */ "retval ::= invoke",
 /*  10 */ "invoke ::= value",
 /*  11 */ "value ::= num",
 /*  12 */ "value ::= string",
 /*  13 */ "value ::= bool",
 /*  14 */ "num ::= NUM",
 /*  15 */ "string ::= STRING",
 /*  16 */ "bool ::= BOOLEAN",
 /*  17 */ "string ::= string PLUS num",
 /*  18 */ "string ::= string PLUSPLUS num",
 /*  19 */ "string ::= num PLUS string",
 /*  20 */ "string ::= num PLUSPLUS string",
 /*  21 */ "string ::= string PLUS bool",
 /*  22 */ "string ::= string PLUSPLUS bool",
 /*  23 */ "string ::= bool PLUS string",
 /*  24 */ "string ::= bool PLUSPLUS string",
 /*  25 */ "bool ::= LPAREN bool RPAREN",
 /*  26 */ "bool ::= bool PLUS bool",
 /*  27 */ "bool ::= bool TIMES bool",
 /*  28 */ "bool ::= bool EQUALTO bool",
 /*  29 */ "bool ::= bool NOTEQUALTO bool",
 /*  30 */ "bool ::= bool AND bool",
 /*  31 */ "bool ::= bool OR bool",
 /*  32 */ "bool ::= NOT bool",
 /*  33 */ "string ::= LPAREN string RPAREN",
 /*  34 */ "string ::= string MINUS string",
 /*  35 */ "string ::= string PLUS string",
 /*  36 */ "string ::= string PLUSPLUS string",
 /*  37 */ "num ::= string TIMES string",
 /*  38 */ "bool ::= string EQUALTO string",
 /*  39 */ "num ::= string DIVIDE string",
 /*  40 */ "bool ::= string LESSTHAN string",
 /*  41 */ "bool ::= string GREATERTHAN string",
 /*  42 */ "bool ::= string NOTEQUALTO string",
 /*  43 */ "bool ::= string GORE string",
 /*  44 */ "bool ::= string LORE string",
 /*  45 */ "num ::= LPAREN num RPAREN",
 /*  46 */ "num ::= num MINUS num",
 /*  47 */ "num ::= num PLUS num",
 /*  48 */ "num ::= num TIMES num",
 /*  49 */ "num ::= num DIVIDE num",
 /*  50 */ "bool ::= num LESSTHAN num",
 /*  51 */ "bool ::= num GREATERTHAN num",
 /*  52 */ "bool ::= num EQUALTO num",
 /*  53 */ "bool ::= num NOTEQUALTO num",
 /*  54 */ "bool ::= num GORE num",
 /*  55 */ "bool ::= num LORE num",
 /*  56 */ "bool ::= num AND num",
 /*  57 */ "bool ::= num OR num",
 /*  58 */ "bool ::= NOT num",
 /*  59 */ "num ::= num SHIFTL num",
 /*  60 */ "num ::= num SHIFTR num",
 /*  61 */ "num ::= num BITAND num",
 /*  62 */ "num ::= num BITOR num",
 /*  63 */ "num ::= BITNOT num",
 /*  64 */ "num ::= MINUS num",
 /*  65 */ "num ::= num MODULO num",
 /*  66 */ "num ::= num POW num",
 /*  67 */ "in ::= error",
 /*  68 */ "error ::= OPENQUOTEERROR",
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
    case 24: /* LPAREN */
    case 25: /* RPAREN */
    case 26: /* COMMA */
    case 27: /* LBRAC */
    case 28: /* RBRAC */
    case 29: /* ASSIGN */
    case 30: /* NEWLINE */
    case 31: /* NUM */
    case 32: /* STRING */
    case 33: /* BOOLEAN */
    case 34: /* OPENQUOTEERROR */
{
#line 35 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 604 "./src/Grammar/grammar.c"
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
  { 38, 1 },
  { 39, 0 },
  { 39, 2 },
  { 39, 3 },
  { 40, 1 },
  { 41, 1 },
  { 42, 1 },
  { 43, 1 },
  { 36, 1 },
  { 44, 1 },
  { 45, 1 },
  { 46, 1 },
  { 46, 1 },
  { 46, 1 },
  { 47, 1 },
  { 48, 1 },
  { 49, 1 },
  { 48, 3 },
  { 48, 3 },
  { 48, 3 },
  { 48, 3 },
  { 48, 3 },
  { 48, 3 },
  { 48, 3 },
  { 48, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 2 },
  { 48, 3 },
  { 48, 3 },
  { 48, 3 },
  { 48, 3 },
  { 47, 3 },
  { 49, 3 },
  { 47, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 47, 3 },
  { 47, 3 },
  { 47, 3 },
  { 47, 3 },
  { 47, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 3 },
  { 49, 2 },
  { 47, 3 },
  { 47, 3 },
  { 47, 3 },
  { 47, 3 },
  { 47, 2 },
  { 47, 2 },
  { 47, 3 },
  { 47, 3 },
  { 39, 1 },
  { 35, 1 },
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
#line 70 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,30,&yymsp[0].minor);
}
#line 971 "./src/Grammar/grammar.c"
        break;
      case 4: /* start ::= spec */
#line 81 "./src/Grammar/grammar.y"
{
/*    std::cout << "Result.type="<< yymsp[0].minor.yy0.type << std::endl;*/
    switch(yymsp[0].minor.yy0.type)
    {
    case NUMBER:
        std::cout << "Number=" << yymsp[0].minor.yy0.data.number << std::endl;
        break;
    case STRING:
        std::cout << "String=" << *yymsp[0].minor.yy0.data.string << std::endl;
        break;
    case BOOLEAN:
        if(yymsp[0].minor.yy0.data.boolean)
        {
            std::cout << "Boolean=true" << std::endl;
        }
        else
        {
            std::cout << "Boolean=false" << std::endl;
        }
    }
}
#line 996 "./src/Grammar/grammar.c"
        break;
      case 5: /* spec ::= top_stmt */
      case 6: /* top_stmt ::= stmt */ yytestcase(yyruleno==6);
      case 7: /* stmt ::= expr */ yytestcase(yyruleno==7);
      case 8: /* expr ::= retval */ yytestcase(yyruleno==8);
      case 9: /* retval ::= invoke */ yytestcase(yyruleno==9);
      case 10: /* invoke ::= value */ yytestcase(yyruleno==10);
#line 105 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = yymsp[0].minor.yy0.type;
    switch(yymsp[0].minor.yy0.type)
    {
    case NUMBER:
        yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
        break;
    case STRING:
        yygotominor.yy0.data.string = new String(yymsp[0].minor.yy0.data.string->c_str());
        break;
    case BOOLEAN:
        yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    }
    yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1020 "./src/Grammar/grammar.c"
        break;
      case 11: /* value ::= num */
      case 14: /* num ::= NUM */ yytestcase(yyruleno==14);
#line 219 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.type = NUMBER;
    yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1030 "./src/Grammar/grammar.c"
        break;
      case 12: /* value ::= string */
      case 15: /* string ::= STRING */ yytestcase(yyruleno==15);
#line 226 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new String(yymsp[0].minor.yy0.data.string->c_str());
    yygotominor.yy0.type = STRING;
    yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1040 "./src/Grammar/grammar.c"
        break;
      case 13: /* value ::= bool */
      case 16: /* bool ::= BOOLEAN */ yytestcase(yyruleno==16);
#line 233 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1050 "./src/Grammar/grammar.c"
        break;
      case 17: /* string ::= string PLUS num */
#line 269 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = STRING;
        panopticon::string_plus_num(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1060 "./src/Grammar/grammar.c"
        break;
      case 18: /* string ::= string PLUSPLUS num */
#line 276 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = STRING;
        panopticon::string_plusplus_num(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1070 "./src/Grammar/grammar.c"
        break;
      case 19: /* string ::= num PLUS string */
#line 283 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = STRING;
        panopticon::num_plus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1080 "./src/Grammar/grammar.c"
        break;
      case 20: /* string ::= num PLUSPLUS string */
#line 290 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = STRING;
        panopticon::num_plusplus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1090 "./src/Grammar/grammar.c"
        break;
      case 21: /* string ::= string PLUS bool */
#line 297 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = STRING;
        panopticon::string_plus_bool(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1100 "./src/Grammar/grammar.c"
        break;
      case 22: /* string ::= string PLUSPLUS bool */
#line 304 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = STRING;
        panopticon::string_plusplus_bool(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1110 "./src/Grammar/grammar.c"
        break;
      case 23: /* string ::= bool PLUS string */
#line 311 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = STRING;
        panopticon::bool_plus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1120 "./src/Grammar/grammar.c"
        break;
      case 24: /* string ::= bool PLUSPLUS string */
#line 318 "./src/Grammar/grammar.y"
{
        yygotominor.yy0.type = STRING;
        panopticon::bool_plusplus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1130 "./src/Grammar/grammar.c"
        break;
      case 25: /* bool ::= LPAREN bool RPAREN */
#line 328 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = yymsp[-1].minor.yy0.data.boolean;
    yygotominor.yy0.n = yymsp[-1].minor.yy0.n+1;
  yy_destructor(yypParser,24,&yymsp[-2].minor);
  yy_destructor(yypParser,25,&yymsp[0].minor);
}
#line 1141 "./src/Grammar/grammar.c"
        break;
      case 26: /* bool ::= bool PLUS bool */
#line 335 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    if(yymsp[-2].minor.yy0.data.boolean || yymsp[0].minor.yy0.data.boolean)
    {
        yygotominor.yy0.data.boolean = true;
    }
    else
    {
        yygotominor.yy0.data.boolean = false;
    }
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1158 "./src/Grammar/grammar.c"
        break;
      case 27: /* bool ::= bool TIMES bool */
#line 349 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    if(yymsp[-2].minor.yy0.data.boolean && yymsp[0].minor.yy0.data.boolean)
    {
        yygotominor.yy0.data.boolean = true;
    }
    else
    {
        yygotominor.yy0.data.boolean = false;
    }
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1175 "./src/Grammar/grammar.c"
        break;
      case 28: /* bool ::= bool EQUALTO bool */
#line 363 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.boolean == yymsp[0].minor.yy0.data.boolean;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1185 "./src/Grammar/grammar.c"
        break;
      case 29: /* bool ::= bool NOTEQUALTO bool */
      case 53: /* bool ::= num NOTEQUALTO num */ yytestcase(yyruleno==53);
#line 370 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number != yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1196 "./src/Grammar/grammar.c"
        break;
      case 30: /* bool ::= bool AND bool */
#line 377 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = (int)yymsp[-2].minor.yy0.data.boolean && (int)yymsp[0].minor.yy0.data.boolean;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,2,&yymsp[-1].minor);
}
#line 1206 "./src/Grammar/grammar.c"
        break;
      case 31: /* bool ::= bool OR bool */
#line 384 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = (int)yymsp[-2].minor.yy0.data.boolean || (int)yymsp[0].minor.yy0.data.boolean;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1216 "./src/Grammar/grammar.c"
        break;
      case 32: /* bool ::= NOT bool */
#line 391 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = !((int)yymsp[0].minor.yy0.data.boolean);
    yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1226 "./src/Grammar/grammar.c"
        break;
      case 33: /* string ::= LPAREN string RPAREN */
#line 457 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = STRING;
    yygotominor.yy0.data.string = yymsp[-1].minor.yy0.data.string;
    yygotominor.yy0.n = yymsp[-1].minor.yy0.n+1;
  yy_destructor(yypParser,24,&yymsp[-2].minor);
  yy_destructor(yypParser,25,&yymsp[0].minor);
}
#line 1237 "./src/Grammar/grammar.c"
        break;
      case 34: /* string ::= string MINUS string */
#line 464 "./src/Grammar/grammar.y"
{
    panopticon::string_minus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1246 "./src/Grammar/grammar.c"
        break;
      case 35: /* string ::= string PLUS string */
#line 470 "./src/Grammar/grammar.y"
{
    panopticon::string_plus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1255 "./src/Grammar/grammar.c"
        break;
      case 36: /* string ::= string PLUSPLUS string */
#line 476 "./src/Grammar/grammar.y"
{
    panopticon::string_plusplus_string(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1264 "./src/Grammar/grammar.c"
        break;
      case 37: /* num ::= string TIMES string */
#line 482 "./src/Grammar/grammar.y"
{
    if(is_number(*yymsp[-2].minor.yy0.data.string) && is_number(*yymsp[0].minor.yy0.data.string))
    {
        yygotominor.yy0.type = NUMBER;
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
#line 1283 "./src/Grammar/grammar.c"
        break;
      case 38: /* bool ::= string EQUALTO string */
#line 498 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->compare(*yymsp[0].minor.yy0.data.string)==0;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1293 "./src/Grammar/grammar.c"
        break;
      case 39: /* num ::= string DIVIDE string */
#line 505 "./src/Grammar/grammar.y"
{
    if(is_number(*yymsp[-2].minor.yy0.data.string) && is_number(*yymsp[0].minor.yy0.data.string))
    {
        yygotominor.yy0.type = NUMBER;
        yygotominor.yy0.data.number = string_to_double(*yymsp[-2].minor.yy0.data.string) / string_to_double(*yymsp[0].minor.yy0.data.string);
    }
    else
    {
        yygotominor.yy0.type = ERROR;
        yygotominor.yy0.data.number = 0;
/*        yygotominor.yy0 = panopticon::MulStringError;*/
        std::cerr << "Error p0002: Attempted to Multiply a string by a string, and at least one is non-numerical: " << std::endl;
        std::cerr << "String 1: " << *yymsp[-2].minor.yy0.data.string << std::endl;
        std::cerr << "String 2: " << *yymsp[0].minor.yy0.data.string << std::endl;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1314 "./src/Grammar/grammar.c"
        break;
      case 40: /* bool ::= string LESSTHAN string */
#line 523 "./src/Grammar/grammar.y"
{
    if(is_number(*yymsp[-2].minor.yy0.data.string) && is_number(*yymsp[0].minor.yy0.data.string))
    {
        yygotominor.yy0.type = BOOLEAN;
        yygotominor.yy0.data.boolean = string_to_double(*yymsp[-2].minor.yy0.data.string) < string_to_double(*yymsp[0].minor.yy0.data.string);
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
    else
    {
        yygotominor.yy0.type = BOOLEAN;
        yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->size() < yymsp[0].minor.yy0.data.string->size();
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1333 "./src/Grammar/grammar.c"
        break;
      case 41: /* bool ::= string GREATERTHAN string */
#line 539 "./src/Grammar/grammar.y"
{
    if(is_number(*yymsp[-2].minor.yy0.data.string) && is_number(*yymsp[0].minor.yy0.data.string))
    {
        yygotominor.yy0.type = BOOLEAN;
        yygotominor.yy0.data.boolean = string_to_double(*yymsp[-2].minor.yy0.data.string) > string_to_double(*yymsp[0].minor.yy0.data.string);
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
    else
    {
        yygotominor.yy0.type = BOOLEAN;
        yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->size() > yymsp[0].minor.yy0.data.string->size();
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1352 "./src/Grammar/grammar.c"
        break;
      case 42: /* bool ::= string NOTEQUALTO string */
#line 555 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->compare(*yymsp[0].minor.yy0.data.string)!=0;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1362 "./src/Grammar/grammar.c"
        break;
      case 43: /* bool ::= string GORE string */
#line 563 "./src/Grammar/grammar.y"
{
    if(is_number(*yymsp[-2].minor.yy0.data.string) && is_number(*yymsp[0].minor.yy0.data.string))
    {
        yygotominor.yy0.type = BOOLEAN;
        yygotominor.yy0.data.boolean = string_to_double(*yymsp[-2].minor.yy0.data.string) >= string_to_double(*yymsp[0].minor.yy0.data.string);
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
    else
    {
        yygotominor.yy0.type = BOOLEAN;
        yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->size() > yymsp[0].minor.yy0.data.string->size();
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1381 "./src/Grammar/grammar.c"
        break;
      case 44: /* bool ::= string LORE string */
#line 579 "./src/Grammar/grammar.y"
{
    if(is_number(*yymsp[-2].minor.yy0.data.string) && is_number(*yymsp[0].minor.yy0.data.string))
    {
        yygotominor.yy0.type = BOOLEAN;
        yygotominor.yy0.data.boolean = string_to_double(*yymsp[-2].minor.yy0.data.string) <= string_to_double(*yymsp[0].minor.yy0.data.string);
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
    else
    {
        yygotominor.yy0.type = BOOLEAN;
        yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.string->size() > yymsp[0].minor.yy0.data.string->size();
        yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1400 "./src/Grammar/grammar.c"
        break;
      case 45: /* num ::= LPAREN num RPAREN */
#line 598 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = NUMBER;
    yygotominor.yy0.data.number = yymsp[-1].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-1].minor.yy0.n+1;
  yy_destructor(yypParser,24,&yymsp[-2].minor);
  yy_destructor(yypParser,25,&yymsp[0].minor);
}
#line 1411 "./src/Grammar/grammar.c"
        break;
      case 46: /* num ::= num MINUS num */
#line 605 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = NUMBER;
    yygotominor.yy0.data.number = yymsp[-2].minor.yy0.data.number - yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1421 "./src/Grammar/grammar.c"
        break;
      case 47: /* num ::= num PLUS num */
#line 612 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = NUMBER;
    yygotominor.yy0.data.number = yymsp[-2].minor.yy0.data.number + yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1431 "./src/Grammar/grammar.c"
        break;
      case 48: /* num ::= num TIMES num */
#line 619 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = NUMBER;
    yygotominor.yy0.data.number = yymsp[-2].minor.yy0.data.number * yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1  + yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1441 "./src/Grammar/grammar.c"
        break;
      case 49: /* num ::= num DIVIDE num */
#line 626 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = NUMBER;
    if(yymsp[0].minor.yy0.data.number != 0)
    {
         yygotominor.yy0.data.number = yymsp[-2].minor.yy0.data.number / yymsp[0].minor.yy0.data.number;
         yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1 + yymsp[0].minor.yy0.n+1;
    }
    else
    {
         std::cout << "divide by zero" << std::endl;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1458 "./src/Grammar/grammar.c"
        break;
      case 50: /* bool ::= num LESSTHAN num */
#line 640 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number < yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1468 "./src/Grammar/grammar.c"
        break;
      case 51: /* bool ::= num GREATERTHAN num */
#line 647 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number > yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1478 "./src/Grammar/grammar.c"
        break;
      case 52: /* bool ::= num EQUALTO num */
#line 654 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number == yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1488 "./src/Grammar/grammar.c"
        break;
      case 54: /* bool ::= num GORE num */
#line 668 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number >= yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1498 "./src/Grammar/grammar.c"
        break;
      case 55: /* bool ::= num LORE num */
#line 675 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = yymsp[-2].minor.yy0.data.number <= yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1508 "./src/Grammar/grammar.c"
        break;
      case 56: /* bool ::= num AND num */
#line 682 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = (int)yymsp[-2].minor.yy0.data.number && (int)yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,2,&yymsp[-1].minor);
}
#line 1518 "./src/Grammar/grammar.c"
        break;
      case 57: /* bool ::= num OR num */
#line 689 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = (int)yymsp[-2].minor.yy0.data.number || (int)yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1528 "./src/Grammar/grammar.c"
        break;
      case 58: /* bool ::= NOT num */
#line 696 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = BOOLEAN;
    yygotominor.yy0.data.boolean = !((int)yymsp[0].minor.yy0.data.number);
    yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1538 "./src/Grammar/grammar.c"
        break;
      case 59: /* num ::= num SHIFTL num */
#line 703 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = NUMBER;
    yygotominor.yy0.data.number = (int)yymsp[-2].minor.yy0.data.number << (int)yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1548 "./src/Grammar/grammar.c"
        break;
      case 60: /* num ::= num SHIFTR num */
#line 710 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = NUMBER;
    yygotominor.yy0.data.number = (int)yymsp[-2].minor.yy0.data.number >> (int)yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1558 "./src/Grammar/grammar.c"
        break;
      case 61: /* num ::= num BITAND num */
#line 717 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = NUMBER;
    yygotominor.yy0.data.number = (int)yymsp[-2].minor.yy0.data.number & (int)yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1568 "./src/Grammar/grammar.c"
        break;
      case 62: /* num ::= num BITOR num */
#line 724 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = NUMBER;
    yygotominor.yy0.data.number = (int)yymsp[-2].minor.yy0.data.number | (int)yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,4,&yymsp[-1].minor);
}
#line 1578 "./src/Grammar/grammar.c"
        break;
      case 63: /* num ::= BITNOT num */
#line 731 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = NUMBER;
    yygotominor.yy0.data.number = ~((int)yymsp[0].minor.yy0.data.number);
    yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1588 "./src/Grammar/grammar.c"
        break;
      case 64: /* num ::= MINUS num */
#line 738 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = NUMBER;
    yygotominor.yy0.data.number = -1 * yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1598 "./src/Grammar/grammar.c"
        break;
      case 65: /* num ::= num MODULO num */
#line 745 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = NUMBER;
    yygotominor.yy0.data.number = fmod(yymsp[-2].minor.yy0.data.number,yymsp[0].minor.yy0.data.number);
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1608 "./src/Grammar/grammar.c"
        break;
      case 66: /* num ::= num POW num */
#line 752 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = NUMBER;
    yygotominor.yy0.data.number = pow(yymsp[-2].minor.yy0.data.number,yymsp[0].minor.yy0.data.number);
    yygotominor.yy0.n = yymsp[-2].minor.yy0.n+1+yymsp[0].minor.yy0.n+1;
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1618 "./src/Grammar/grammar.c"
        break;
      case 67: /* in ::= error */
#line 763 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy101)
    {
    case OpenQuoteError:
/*        std::cerr << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        std::cerr << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 1633 "./src/Grammar/grammar.c"
        break;
      case 68: /* error ::= OPENQUOTEERROR */
#line 776 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = NUMBER;
    yygotominor.yy101 = OpenQuoteError;
    std::cerr << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1642 "./src/Grammar/grammar.c"
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
#line 64 "./src/Grammar/grammar.y"

std::cout << "Syntax error!" << std::endl;
#line 1709 "./src/Grammar/grammar.c"
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
#line 59 "./src/Grammar/grammar.y"

printf("parsing complete!\n\n\n");
#line 1731 "./src/Grammar/grammar.c"
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
