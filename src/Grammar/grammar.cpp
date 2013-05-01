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
#line 43 "./src/Grammar/grammar.c"
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
#define YYNOCODE 59
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy117;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 78
#define YYNRULE 50
#define YYERRORSYMBOL 40
#define YYERRSYMDT yy117
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
#define YY_ACTTAB_COUNT (457)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    13,   14,    9,   10,   20,   19,   17,   15,   18,   16,
 /*    10 */    12,   11,   27,   25,   24,   23,   22,   21,   14,    9,
 /*    20 */    10,   20,   19,   17,   15,   18,   16,   12,   11,   27,
 /*    30 */    25,   24,   23,   22,   21,    9,   10,   20,   19,   17,
 /*    40 */    15,   18,   16,   12,   11,   27,   25,   24,   23,   22,
 /*    50 */    21,   10,   20,   19,   17,   15,   18,   16,   12,   11,
 /*    60 */    27,   25,   24,   23,   22,   21,   20,   19,   17,   15,
 /*    70 */    18,   16,   12,   11,   27,   25,   24,   23,   22,   21,
 /*    80 */    17,   15,   18,   16,   12,   11,   27,   25,   24,   23,
 /*    90 */    22,   21,   30,    6,   76,    3,   56,   75,   74,   73,
 /*   100 */    72,   46,   71,   30,   68,   78,   66,   65,   64,    8,
 /*   110 */    26,   67,   21,   71,    5,   68,   48,   66,   65,   64,
 /*   120 */    55,    2,   63,   62,   61,   60,   59,   57,    8,   26,
 /*   130 */    12,   11,   27,   25,   24,   23,   22,   21,   77,   45,
 /*   140 */     2,   63,   62,   61,   24,   23,   22,   21,    7,   88,
 /*   150 */   130,  130,    8,   26,   27,   25,   24,   23,   22,   21,
 /*   160 */   130,  130,   47,   55,    2,   63,   62,   61,  130,  130,
 /*   170 */    58,  130,  130,  129,    1,    3,    8,   26,  130,  130,
 /*   180 */   130,   70,   88,  130,   30,  130,  130,   55,    2,   63,
 /*   190 */    62,   61,   67,  130,   71,    4,   68,  130,   66,   65,
 /*   200 */    64,  130,  130,  130,   30,  130,  130,  130,  130,  130,
 /*   210 */   130,  130,   69,  130,   71,  130,   68,  130,   66,   65,
 /*   220 */    64,  130,  130,   43,  130,  130,  130,  130,  130,  130,
 /*   230 */    54,  130,  130,   71,  130,   68,  130,   66,   65,   64,
 /*   240 */    71,   44,   68,  130,   66,   65,   64,  130,  130,  130,
 /*   250 */   130,   71,  130,   68,   53,   66,   65,   64,  130,  130,
 /*   260 */   130,   52,  130,  130,   71,  130,   68,  130,   66,   65,
 /*   270 */    64,   71,   51,   68,  130,   66,   65,   64,  130,   50,
 /*   280 */   130,  130,   71,  130,   68,  130,   66,   65,   64,   71,
 /*   290 */   130,   68,  130,   66,   65,   64,   36,  130,  130,  130,
 /*   300 */   130,  130,  130,   35,  130,  130,   71,  130,   68,  130,
 /*   310 */    66,   65,   64,   71,   40,   68,  130,   66,   65,   64,
 /*   320 */   130,   39,  130,  130,   71,  130,   68,  130,   66,   65,
 /*   330 */    64,   71,  130,   68,  130,   66,   65,   64,   38,  130,
 /*   340 */   130,  130,  130,  130,  130,   37,  130,  130,   71,  130,
 /*   350 */    68,  130,   66,   65,   64,   71,   32,   68,  130,   66,
 /*   360 */    65,   64,  130,   31,  130,  130,   71,  130,   68,  130,
 /*   370 */    66,   65,   64,   71,  130,   68,  130,   66,   65,   64,
 /*   380 */    42,  130,  130,  130,  130,  130,  130,   41,  130,  130,
 /*   390 */    71,  130,   68,  130,   66,   65,   64,   71,   34,   68,
 /*   400 */   130,   66,   65,   64,  130,   33,  130,  130,   71,  130,
 /*   410 */    68,  130,   66,   65,   64,   71,  130,   68,  130,   66,
 /*   420 */    65,   64,   49,  130,  130,  130,  130,  130,  130,   29,
 /*   430 */   130,  130,   71,  130,   68,  130,   66,   65,   64,   71,
 /*   440 */    28,   68,  130,   66,   65,   64,  130,  130,  130,  130,
 /*   450 */    71,  130,   68,  130,   66,   65,   64,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    10 */    15,   16,   17,   18,   19,   20,   21,   22,    6,    7,
 /*    20 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*    30 */    18,   19,   20,   21,   22,    7,    8,    9,   10,   11,
 /*    40 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*    50 */    22,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*    60 */    17,   18,   19,   20,   21,   22,    9,   10,   11,   12,
 /*    70 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*    80 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    90 */    21,   22,   41,    1,   33,   27,   45,   46,   47,   48,
 /*   100 */    49,   50,   51,   41,   53,    0,   55,   56,   57,   23,
 /*   110 */    24,   49,   22,   51,   52,   53,   54,   55,   56,   57,
 /*   120 */    34,   35,   36,   37,   38,   31,   34,   39,   23,   24,
 /*   130 */    15,   16,   17,   18,   19,   20,   21,   22,   33,   34,
 /*   140 */    35,   36,   37,   38,   19,   20,   21,   22,    2,    1,
 /*   150 */    58,   58,   23,   24,   17,   18,   19,   20,   21,   22,
 /*   160 */    58,   58,   33,   34,   35,   36,   37,   38,   58,   58,
 /*   170 */    40,   58,   58,   43,   44,   27,   23,   24,   58,   58,
 /*   180 */    58,   28,   34,   58,   41,   58,   58,   34,   35,   36,
 /*   190 */    37,   38,   49,   58,   51,   52,   53,   58,   55,   56,
 /*   200 */    57,   58,   58,   58,   41,   58,   58,   58,   58,   58,
 /*   210 */    58,   58,   49,   58,   51,   58,   53,   58,   55,   56,
 /*   220 */    57,   58,   58,   41,   58,   58,   58,   58,   58,   58,
 /*   230 */    41,   58,   58,   51,   58,   53,   58,   55,   56,   57,
 /*   240 */    51,   41,   53,   58,   55,   56,   57,   58,   58,   58,
 /*   250 */    58,   51,   58,   53,   41,   55,   56,   57,   58,   58,
 /*   260 */    58,   41,   58,   58,   51,   58,   53,   58,   55,   56,
 /*   270 */    57,   51,   41,   53,   58,   55,   56,   57,   58,   41,
 /*   280 */    58,   58,   51,   58,   53,   58,   55,   56,   57,   51,
 /*   290 */    58,   53,   58,   55,   56,   57,   41,   58,   58,   58,
 /*   300 */    58,   58,   58,   41,   58,   58,   51,   58,   53,   58,
 /*   310 */    55,   56,   57,   51,   41,   53,   58,   55,   56,   57,
 /*   320 */    58,   41,   58,   58,   51,   58,   53,   58,   55,   56,
 /*   330 */    57,   51,   58,   53,   58,   55,   56,   57,   41,   58,
 /*   340 */    58,   58,   58,   58,   58,   41,   58,   58,   51,   58,
 /*   350 */    53,   58,   55,   56,   57,   51,   41,   53,   58,   55,
 /*   360 */    56,   57,   58,   41,   58,   58,   51,   58,   53,   58,
 /*   370 */    55,   56,   57,   51,   58,   53,   58,   55,   56,   57,
 /*   380 */    41,   58,   58,   58,   58,   58,   58,   41,   58,   58,
 /*   390 */    51,   58,   53,   58,   55,   56,   57,   51,   41,   53,
 /*   400 */    58,   55,   56,   57,   58,   41,   58,   58,   51,   58,
 /*   410 */    53,   58,   55,   56,   57,   51,   58,   53,   58,   55,
 /*   420 */    56,   57,   41,   58,   58,   58,   58,   58,   58,   41,
 /*   430 */    58,   58,   51,   58,   53,   58,   55,   56,   57,   51,
 /*   440 */    41,   53,   58,   55,   56,   57,   58,   58,   58,   58,
 /*   450 */    51,   58,   53,   58,   55,   56,   57,
};
#define YY_SHIFT_USE_DFLT (-6)
#define YY_SHIFT_COUNT (56)
#define YY_SHIFT_MIN   (-5)
#define YY_SHIFT_MAX   (153)
static const short yy_shift_ofst[] = {
 /*     0 */    88,  105,   86,   86,  153,   86,  129,   86,   86,   86,
 /*    10 */    86,   86,   86,   86,   86,   86,   86,   86,   86,   86,
 /*    20 */    86,   86,   86,   86,   86,   86,   86,   86,   -5,   -5,
 /*    30 */    -5,   12,   28,   43,   57,   69,   69,  115,  115,  115,
 /*    40 */   115,  137,  137,  125,  125,  148,   92,  146,   94,   90,
 /*    50 */    90,   90,   90,   90,   90,   68,   61,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (27)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (399)
static const short yy_reduce_ofst[] = {
 /*     0 */   130,   51,   62,  143,  163,  163,  399,  388,  381,  364,
 /*    10 */   357,  346,  339,  322,  315,  304,  297,  280,  273,  262,
 /*    20 */   255,  238,  231,  220,  213,  200,  189,  182,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */    79,  128,   98,  128,  128,   99,  128,  128,  128,  128,
 /*    10 */   128,  128,  128,  128,  128,  128,  128,  128,  128,  128,
 /*    20 */   128,  128,  128,  128,  128,  128,  128,  128,   93,   92,
 /*    30 */    86,  119,  118,  125,  124,  113,  112,  117,  116,  115,
 /*    40 */   114,  123,  122,  106,  107,   89,  128,  128,  128,  121,
 /*    50 */   111,  110,  109,  108,  120,   89,  128,  127,  126,   87,
 /*    60 */    97,  105,  104,  103,  102,  101,  100,   94,   96,   95,
 /*    70 */    91,   90,   85,   84,   83,   82,   81,   80,
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
   35,  /*      LBRAC => OPENBRAC */
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
  "COLLECTARRAY",  "NEWLINE",       "NAME",          "OPENBRAC",    
  "NUM",           "STRING",        "BOOLEAN",       "OPENQUOTEERROR",
  "error",         "expr",          "id",            "main",        
  "in",            "start",         "spec",          "assignment",  
  "top_stmt",      "stmt",          "name_chain",    "function_call",
  "stmt_list",     "array",         "maybe_empty_stmt_list",  "num",         
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
 /*   5 */ "spec ::= assignment",
 /*   6 */ "spec ::= top_stmt",
 /*   7 */ "top_stmt ::= stmt",
 /*   8 */ "stmt ::= expr",
 /*   9 */ "name_chain ::= name_chain NAME",
 /*  10 */ "name_chain ::= NAME",
 /*  11 */ "expr ::= NAME",
 /*  12 */ "expr ::= function_call",
 /*  13 */ "function_call ::= NAME LPAREN stmt_list RPAREN",
 /*  14 */ "assignment ::= name_chain ASSIGN NEWLINE BITOR expr",
 /*  15 */ "assignment ::= name_chain ASSIGN expr",
 /*  16 */ "stmt_list ::= stmt",
 /*  17 */ "stmt_list ::= stmt_list stmt",
 /*  18 */ "expr ::= array",
 /*  19 */ "array ::= OPENBRAC maybe_empty_stmt_list RBRAC",
 /*  20 */ "maybe_empty_stmt_list ::=",
 /*  21 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  22 */ "expr ::= num",
 /*  23 */ "expr ::= string",
 /*  24 */ "expr ::= bool",
 /*  25 */ "num ::= NUM",
 /*  26 */ "string ::= STRING",
 /*  27 */ "bool ::= BOOLEAN",
 /*  28 */ "expr ::= expr PLUS expr",
 /*  29 */ "expr ::= expr MINUS expr",
 /*  30 */ "expr ::= expr DIVIDE expr",
 /*  31 */ "expr ::= expr TIMES expr",
 /*  32 */ "expr ::= expr MODULO expr",
 /*  33 */ "expr ::= expr POW expr",
 /*  34 */ "expr ::= expr EQUALTO expr",
 /*  35 */ "expr ::= expr NOTEQUALTO expr",
 /*  36 */ "expr ::= expr LESSTHAN expr",
 /*  37 */ "expr ::= expr GREATERTHAN expr",
 /*  38 */ "expr ::= expr LORE expr",
 /*  39 */ "expr ::= expr GORE expr",
 /*  40 */ "expr ::= expr AND expr",
 /*  41 */ "expr ::= expr OR expr",
 /*  42 */ "expr ::= BITNOT expr",
 /*  43 */ "expr ::= NOT expr",
 /*  44 */ "expr ::= expr SHIFTL expr",
 /*  45 */ "expr ::= expr SHIFTR expr",
 /*  46 */ "expr ::= expr BITAND expr",
 /*  47 */ "expr ::= expr BITXOR expr",
 /*  48 */ "in ::= error",
 /*  49 */ "error ::= OPENQUOTEERROR",
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
    case 35: /* OPENBRAC */
    case 36: /* NUM */
    case 37: /* STRING */
    case 38: /* BOOLEAN */
    case 39: /* OPENQUOTEERROR */
{
#line 42 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 625 "./src/Grammar/grammar.c"
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
  { 43, 1 },
  { 44, 0 },
  { 44, 2 },
  { 44, 3 },
  { 45, 1 },
  { 46, 1 },
  { 46, 1 },
  { 48, 1 },
  { 49, 1 },
  { 50, 2 },
  { 50, 1 },
  { 41, 1 },
  { 41, 1 },
  { 51, 4 },
  { 47, 5 },
  { 47, 3 },
  { 52, 1 },
  { 52, 2 },
  { 41, 1 },
  { 53, 3 },
  { 54, 0 },
  { 54, 1 },
  { 41, 1 },
  { 41, 1 },
  { 41, 1 },
  { 55, 1 },
  { 56, 1 },
  { 57, 1 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 41, 2 },
  { 41, 2 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 41, 3 },
  { 44, 1 },
  { 40, 1 },
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
#line 82 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,33,&yymsp[0].minor);
}
#line 973 "./src/Grammar/grammar.c"
        break;
      case 4: /* start ::= spec */
#line 94 "./src/Grammar/grammar.y"
{
    if(panopticon::correct_parsing)
    {
        optic::print_object(yymsp[0].minor.yy0);
    }
    optic::delete_object(yymsp[0].minor.yy0);
}
#line 984 "./src/Grammar/grammar.c"
        break;
      case 5: /* spec ::= assignment */
      case 22: /* expr ::= num */ yytestcase(yyruleno==22);
      case 24: /* expr ::= bool */ yytestcase(yyruleno==24);
#line 104 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 993 "./src/Grammar/grammar.c"
        break;
      case 6: /* spec ::= top_stmt */
      case 7: /* top_stmt ::= stmt */ yytestcase(yyruleno==7);
      case 23: /* expr ::= string */ yytestcase(yyruleno==23);
#line 116 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 1003 "./src/Grammar/grammar.c"
        break;
      case 8: /* stmt ::= expr */
      case 16: /* stmt_list ::= stmt */ yytestcase(yyruleno==16);
#line 128 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 1012 "./src/Grammar/grammar.c"
        break;
      case 9: /* name_chain ::= name_chain NAME */
#line 161 "./src/Grammar/grammar.y"
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
        yygotominor.yy0.scope = optic::get_scope();
    }
    delete_object(yymsp[-1].minor.yy0);
    delete_object(yymsp[0].minor.yy0);
}
#line 1051 "./src/Grammar/grammar.c"
        break;
      case 10: /* name_chain ::= NAME */
#line 197 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
}
#line 1060 "./src/Grammar/grammar.c"
        break;
      case 11: /* expr ::= NAME */
#line 204 "./src/Grammar/grammar.y"
{
    panopticon::retrieve_variable(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1072 "./src/Grammar/grammar.c"
        break;
      case 12: /* expr ::= function_call */
      case 18: /* expr ::= array */ yytestcase(yyruleno==18);
#line 214 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1080 "./src/Grammar/grammar.c"
        break;
      case 13: /* function_call ::= NAME LPAREN stmt_list RPAREN */
#line 219 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.scope = optic::get_scope();
    yygotominor.yy0.type = FUNCTION_DEC;
    optic::parse_operations(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,optic::call_function);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,27,&yymsp[-2].minor);
  yy_destructor(yypParser,28,&yymsp[0].minor);
}
#line 1096 "./src/Grammar/grammar.c"
        break;
      case 14: /* assignment ::= name_chain ASSIGN NEWLINE BITOR expr */
#line 241 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::STRING;
    yygotominor.yy0.data.string = new optic::String("GUARD!");
    optic::out() << "GUARD!" << std::endl;
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,33,&yymsp[-2].minor);
  yy_destructor(yypParser,2,&yymsp[-1].minor);
}
#line 1108 "./src/Grammar/grammar.c"
        break;
      case 15: /* assignment ::= name_chain ASSIGN expr */
#line 249 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = optic::ASSIGNMENT;
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::assign_variable);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1122 "./src/Grammar/grammar.c"
        break;
      case 17: /* stmt_list ::= stmt_list stmt */
#line 270 "./src/Grammar/grammar.y"
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
#line 1141 "./src/Grammar/grammar.c"
        break;
      case 19: /* array ::= OPENBRAC maybe_empty_stmt_list RBRAC */
#line 300 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::ARRAY;
    yygotominor.yy0.data.array = yymsp[-1].minor.yy0.data.array;
  yy_destructor(yypParser,35,&yymsp[-2].minor);
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1151 "./src/Grammar/grammar.c"
        break;
      case 20: /* maybe_empty_stmt_list ::= */
#line 306 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 1159 "./src/Grammar/grammar.c"
        break;
      case 21: /* maybe_empty_stmt_list ::= stmt_list */
#line 312 "./src/Grammar/grammar.y"
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
#line 1175 "./src/Grammar/grammar.c"
        break;
      case 25: /* num ::= NUM */
#line 364 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.type = panopticon::NUMBER;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1184 "./src/Grammar/grammar.c"
        break;
      case 26: /* string ::= STRING */
#line 371 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1194 "./src/Grammar/grammar.c"
        break;
      case 27: /* bool ::= BOOLEAN */
#line 380 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    yygotominor.yy0.type = panopticon::BOOL;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1203 "./src/Grammar/grammar.c"
        break;
      case 28: /* expr ::= expr PLUS expr */
#line 412 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::plus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1216 "./src/Grammar/grammar.c"
        break;
      case 29: /* expr ::= expr MINUS expr */
#line 422 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1229 "./src/Grammar/grammar.c"
        break;
      case 30: /* expr ::= expr DIVIDE expr */
#line 432 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1242 "./src/Grammar/grammar.c"
        break;
      case 31: /* expr ::= expr TIMES expr */
#line 442 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1255 "./src/Grammar/grammar.c"
        break;
      case 32: /* expr ::= expr MODULO expr */
#line 452 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1268 "./src/Grammar/grammar.c"
        break;
      case 33: /* expr ::= expr POW expr */
#line 462 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,22,&yymsp[-1].minor);
}
#line 1281 "./src/Grammar/grammar.c"
        break;
      case 34: /* expr ::= expr EQUALTO expr */
#line 472 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1294 "./src/Grammar/grammar.c"
        break;
      case 35: /* expr ::= expr NOTEQUALTO expr */
#line 482 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1307 "./src/Grammar/grammar.c"
        break;
      case 36: /* expr ::= expr LESSTHAN expr */
#line 492 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1320 "./src/Grammar/grammar.c"
        break;
      case 37: /* expr ::= expr GREATERTHAN expr */
#line 502 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1333 "./src/Grammar/grammar.c"
        break;
      case 38: /* expr ::= expr LORE expr */
#line 512 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1346 "./src/Grammar/grammar.c"
        break;
      case 39: /* expr ::= expr GORE expr */
#line 522 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1359 "./src/Grammar/grammar.c"
        break;
      case 40: /* expr ::= expr AND expr */
#line 532 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1372 "./src/Grammar/grammar.c"
        break;
      case 41: /* expr ::= expr OR expr */
#line 542 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1385 "./src/Grammar/grammar.c"
        break;
      case 42: /* expr ::= BITNOT expr */
#line 552 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,24,&yymsp[-1].minor);
}
#line 1398 "./src/Grammar/grammar.c"
        break;
      case 43: /* expr ::= NOT expr */
#line 562 "./src/Grammar/grammar.y"
{
    not_value(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1411 "./src/Grammar/grammar.c"
        break;
      case 44: /* expr ::= expr SHIFTL expr */
#line 572 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1424 "./src/Grammar/grammar.c"
        break;
      case 45: /* expr ::= expr SHIFTR expr */
#line 582 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1437 "./src/Grammar/grammar.c"
        break;
      case 46: /* expr ::= expr BITAND expr */
#line 592 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1450 "./src/Grammar/grammar.c"
        break;
      case 47: /* expr ::= expr BITXOR expr */
#line 612 "./src/Grammar/grammar.y"
{
    parse_operations(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1463 "./src/Grammar/grammar.c"
        break;
      case 48: /* in ::= error */
#line 663 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy117)
    {
    case panopticon::OpenQuoteError:
/*        panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        panopticon::out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 1478 "./src/Grammar/grammar.c"
        break;
      case 49: /* error ::= OPENQUOTEERROR */
#line 676 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy117 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1487 "./src/Grammar/grammar.c"
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
#line 76 "./src/Grammar/grammar.y"

panopticon::out() << "Syntax error!" << std::endl;
#line 1554 "./src/Grammar/grammar.c"
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
#line 71 "./src/Grammar/grammar.y"

printf("parsing complete!\n\n\n");
#line 1576 "./src/Grammar/grammar.c"
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
