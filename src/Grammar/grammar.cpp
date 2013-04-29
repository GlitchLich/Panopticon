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

#undef STRING
#undef NUM
#undef BOOL
#undef panopticon::ARRAY

/*using namespace panopticon;*/

    void token_destructor(Token t)
    {
/*    panopticon::out() << "In token_destructor t.value= " << t.value << std::endl;*/
/*    panopticon::out() << "In token_destructor t.n= " << t.n << std::endl;*/
    }
#line 42 "./src/Grammar/grammar.c"
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
#define YYNOCODE 58
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy115;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 77
#define YYNRULE 49
#define YYERRORSYMBOL 38
#define YYERRSYMDT yy115
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
#define YY_ACTTAB_COUNT (338)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    12,   13,    7,    8,    9,   19,   18,   16,   14,   17,
 /*    10 */    15,   11,   10,   25,   24,   23,   22,   21,   20,   13,
 /*    20 */     7,    8,    9,   19,   18,   16,   14,   17,   15,   11,
 /*    30 */    10,   25,   24,   23,   22,   21,   20,    7,    8,    9,
 /*    40 */    19,   18,   16,   14,   17,   15,   11,   10,   25,   24,
 /*    50 */    23,   22,   21,   20,    8,    9,   19,   18,   16,   14,
 /*    60 */    17,   15,   11,   10,   25,   24,   23,   22,   21,   20,
 /*    70 */     9,   19,   18,   16,   14,   17,   15,   11,   10,   25,
 /*    80 */    24,   23,   22,   21,   20,   19,   18,   16,   14,   17,
 /*    90 */    15,   11,   10,   25,   24,   23,   22,   21,   20,   71,
 /*   100 */    75,   20,   26,   55,   74,   73,   72,   70,   69,   68,
 /*   110 */    59,   28,   58,   65,   64,   63,   45,   16,   14,   17,
 /*   120 */    15,   11,   10,   25,   24,   23,   22,   21,   20,   71,
 /*   130 */    25,   24,   23,   22,   21,   20,   67,   70,   69,   68,
 /*   140 */     3,   28,   44,   65,   64,   63,   45,   71,   77,   23,
 /*   150 */    22,   21,   20,    4,   66,   70,   69,   68,   47,   28,
 /*   160 */    46,   65,   64,   63,   45,   56,  128,  128,    5,    6,
 /*   170 */    43,  128,   65,   64,   63,   48,    2,  128,  128,   76,
 /*   180 */    62,   61,   60,   42,   46,   65,   64,   63,   48,   11,
 /*   190 */    10,   25,   24,   23,   22,   21,   20,  128,  128,  128,
 /*   200 */     5,    6,  128,   57,  128,  128,  127,    1,    2,  128,
 /*   210 */   128,  128,   62,   61,   60,   54,   46,   65,   64,   63,
 /*   220 */    48,   53,  128,   65,   64,   63,   48,   52,  128,   65,
 /*   230 */    64,   63,   48,   51,  128,   65,   64,   63,   48,   35,
 /*   240 */   128,   65,   64,   63,   48,   34,  128,   65,   64,   63,
 /*   250 */    48,  128,   39,  128,   65,   64,   63,   48,  128,  128,
 /*   260 */    38,  128,   65,   64,   63,   48,   37,  128,   65,   64,
 /*   270 */    63,   48,   36,  128,   65,   64,   63,   48,   30,  128,
 /*   280 */    65,   64,   63,   48,   29,  128,   65,   64,   63,   48,
 /*   290 */    41,  128,   65,   64,   63,   48,   40,  128,   65,   64,
 /*   300 */    63,   48,   33,  128,   65,   64,   63,   48,   32,  128,
 /*   310 */    65,   64,   63,   48,   31,  128,   65,   64,   63,   48,
 /*   320 */    50,  128,   65,   64,   63,   48,   49,  128,   65,   64,
 /*   330 */    63,   48,   27,  128,   65,   64,   63,   48,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
 /*    10 */    11,   12,   13,   14,   15,   16,   17,   18,   19,    2,
 /*    20 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*    30 */    13,   14,   15,   16,   17,   18,   19,    3,    4,    5,
 /*    40 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*    50 */    16,   17,   18,   19,    4,    5,    6,    7,    8,    9,
 /*    60 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*    70 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    80 */    15,   16,   17,   18,   19,    6,    7,    8,    9,   10,
 /*    90 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   39,
 /*   100 */    31,   19,   35,   43,   44,   45,   46,   47,   48,   49,
 /*   110 */    29,   51,   29,   53,   54,   55,   56,    8,    9,   10,
 /*   120 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   39,
 /*   130 */    14,   15,   16,   17,   18,   19,   46,   47,   48,   49,
 /*   140 */    50,   51,   52,   53,   54,   55,   56,   39,    0,   16,
 /*   150 */    17,   18,   19,   30,   46,   47,   48,   49,   56,   51,
 /*   160 */    36,   53,   54,   55,   56,   37,   57,   57,   20,   21,
 /*   170 */    51,   57,   53,   54,   55,   56,   28,   57,   57,   31,
 /*   180 */    32,   33,   34,   51,   36,   53,   54,   55,   56,   12,
 /*   190 */    13,   14,   15,   16,   17,   18,   19,   57,   57,   57,
 /*   200 */    20,   21,   57,   38,   57,   57,   41,   42,   28,   57,
 /*   210 */    57,   57,   32,   33,   34,   51,   36,   53,   54,   55,
 /*   220 */    56,   51,   57,   53,   54,   55,   56,   51,   57,   53,
 /*   230 */    54,   55,   56,   51,   57,   53,   54,   55,   56,   51,
 /*   240 */    57,   53,   54,   55,   56,   51,   57,   53,   54,   55,
 /*   250 */    56,   57,   51,   57,   53,   54,   55,   56,   57,   57,
 /*   260 */    51,   57,   53,   54,   55,   56,   51,   57,   53,   54,
 /*   270 */    55,   56,   51,   57,   53,   54,   55,   56,   51,   57,
 /*   280 */    53,   54,   55,   56,   51,   57,   53,   54,   55,   56,
 /*   290 */    51,   57,   53,   54,   55,   56,   51,   57,   53,   54,
 /*   300 */    55,   56,   51,   57,   53,   54,   55,   56,   51,   57,
 /*   310 */    53,   54,   55,   56,   51,   57,   53,   54,   55,   56,
 /*   320 */    51,   57,   53,   54,   55,   56,   51,   57,   53,   54,
 /*   330 */    55,   56,   51,   57,   53,   54,   55,   56,
};
#define YY_SHIFT_USE_DFLT (-2)
#define YY_SHIFT_COUNT (55)
#define YY_SHIFT_MIN   (-1)
#define YY_SHIFT_MAX   (180)
static const short yy_shift_ofst[] = {
 /*     0 */   128,  148,  180,  180,  180,  180,  180,  180,  180,  180,
 /*    10 */   180,  180,  180,  180,  180,  180,  180,  180,  180,  180,
 /*    20 */   180,  180,  180,  180,  180,  180,  124,   -1,   -1,   17,
 /*    30 */    34,   50,   65,   79,  109,  109,  177,  177,  177,  177,
 /*    40 */   116,  116,  133,  133,   83,   67,  123,   81,   67,   82,
 /*    50 */    82,   82,   82,   82,   82,   69,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (26)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (281)
static const short yy_reduce_ofst[] = {
 /*     0 */   165,   60,   90,  108,  281,  275,  269,  263,  257,  251,
 /*    10 */   245,  239,  233,  227,  221,  215,  209,  201,  194,  188,
 /*    20 */   182,  176,  170,  164,  132,  119,  102,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */    78,  126,   91,   92,  126,  126,  126,  126,  126,  126,
 /*    10 */   126,  126,  126,  126,  126,  126,  126,  126,  126,  126,
 /*    20 */   126,  126,  126,  126,  126,  126,  126,  123,   93,  113,
 /*    30 */   112,  120,  119,  118,  107,  106,  111,  110,  109,  108,
 /*    40 */   117,  116,  101,  100,  126,  122,  126,  126,  126,  115,
 /*    50 */   114,  105,  104,  103,  102,  126,  125,  124,   90,  121,
 /*    60 */    99,   98,   97,   96,   95,   94,   89,   88,   87,   86,
 /*    70 */    85,   84,   83,   82,   81,   80,   79,
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
  "NUM",           "STRING",        "BOOLEAN",       "OPENBRAC",    
  "NAME",          "OPENQUOTEERROR",  "error",         "expr",        
  "id",            "main",          "in",            "start",       
  "spec",          "top_stmt",      "stmt",          "retval",      
  "access",        "identifier",    "stmt_list",     "value",       
  "maybe_empty_stmt_list",  "num",           "string",        "bool",        
  "variable",    
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
 /*  13 */ "value ::= LBRAC maybe_empty_stmt_list RBRAC",
 /*  14 */ "maybe_empty_stmt_list ::=",
 /*  15 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  16 */ "identifier ::= value",
 /*  17 */ "value ::= num",
 /*  18 */ "value ::= string",
 /*  19 */ "value ::= bool",
 /*  20 */ "num ::= NUM",
 /*  21 */ "string ::= STRING",
 /*  22 */ "bool ::= BOOLEAN",
 /*  23 */ "value ::= value PLUS value",
 /*  24 */ "value ::= value MINUS value",
 /*  25 */ "value ::= value DIVIDE value",
 /*  26 */ "value ::= value TIMES value",
 /*  27 */ "value ::= value MODULO value",
 /*  28 */ "value ::= value POW value",
 /*  29 */ "value ::= value EQUALTO value",
 /*  30 */ "value ::= value NOTEQUALTO value",
 /*  31 */ "value ::= value LESSTHAN value",
 /*  32 */ "value ::= value GREATERTHAN value",
 /*  33 */ "value ::= value LORE value",
 /*  34 */ "value ::= value GORE value",
 /*  35 */ "value ::= value AND value",
 /*  36 */ "value ::= value OR value",
 /*  37 */ "value ::= BITNOT value",
 /*  38 */ "value ::= NOT value",
 /*  39 */ "value ::= value SHIFTL value",
 /*  40 */ "value ::= value SHIFTR value",
 /*  41 */ "value ::= value BITAND value",
 /*  42 */ "value ::= value BITOR value",
 /*  43 */ "value ::= value BITXOR value",
 /*  44 */ "value ::= variable OPENBRAC variable RBRAC",
 /*  45 */ "stmt ::= variable",
 /*  46 */ "variable ::= NAME ASSIGN value",
 /*  47 */ "in ::= error",
 /*  48 */ "error ::= OPENQUOTEERROR",
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
    case 35: /* OPENBRAC */
    case 36: /* NAME */
    case 37: /* OPENQUOTEERROR */
{
#line 41 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 565 "./src/Grammar/grammar.c"
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
  { 41, 1 },
  { 42, 0 },
  { 42, 2 },
  { 42, 3 },
  { 43, 1 },
  { 44, 1 },
  { 45, 1 },
  { 46, 1 },
  { 39, 1 },
  { 47, 1 },
  { 48, 1 },
  { 50, 1 },
  { 50, 2 },
  { 51, 3 },
  { 52, 0 },
  { 52, 1 },
  { 49, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 53, 1 },
  { 54, 1 },
  { 55, 1 },
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
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 4 },
  { 46, 1 },
  { 56, 3 },
  { 42, 1 },
  { 38, 1 },
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
#line 77 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 912 "./src/Grammar/grammar.c"
        break;
      case 4: /* start ::= spec */
#line 86 "./src/Grammar/grammar.y"
{
    optic::print_object(yymsp[0].minor.yy0);
    optic::delete_object(yymsp[0].minor.yy0);
}
#line 920 "./src/Grammar/grammar.c"
        break;
      case 5: /* spec ::= top_stmt */
      case 6: /* top_stmt ::= stmt */ yytestcase(yyruleno==6);
      case 8: /* expr ::= retval */ yytestcase(yyruleno==8);
      case 16: /* identifier ::= value */ yytestcase(yyruleno==16);
      case 18: /* value ::= string */ yytestcase(yyruleno==18);
#line 93 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 932 "./src/Grammar/grammar.c"
        break;
      case 7: /* stmt ::= expr */
      case 9: /* retval ::= access */ yytestcase(yyruleno==9);
      case 10: /* access ::= identifier */ yytestcase(yyruleno==10);
      case 11: /* stmt_list ::= stmt */ yytestcase(yyruleno==11);
#line 104 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 943 "./src/Grammar/grammar.c"
        break;
      case 12: /* stmt_list ::= stmt_list stmt */
#line 144 "./src/Grammar/grammar.y"
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
#line 962 "./src/Grammar/grammar.c"
        break;
      case 13: /* value ::= LBRAC maybe_empty_stmt_list RBRAC */
#line 167 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::ARRAY;
    yygotominor.yy0.data.array = yymsp[-1].minor.yy0.data.array;
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 972 "./src/Grammar/grammar.c"
        break;
      case 14: /* maybe_empty_stmt_list ::= */
#line 173 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 980 "./src/Grammar/grammar.c"
        break;
      case 15: /* maybe_empty_stmt_list ::= stmt_list */
#line 179 "./src/Grammar/grammar.y"
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
#line 996 "./src/Grammar/grammar.c"
        break;
      case 17: /* value ::= num */
      case 19: /* value ::= bool */ yytestcase(yyruleno==19);
#line 203 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1004 "./src/Grammar/grammar.c"
        break;
      case 20: /* num ::= NUM */
#line 228 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.type = panopticon::NUMBER;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1013 "./src/Grammar/grammar.c"
        break;
      case 21: /* string ::= STRING */
#line 235 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1023 "./src/Grammar/grammar.c"
        break;
      case 22: /* bool ::= BOOLEAN */
#line 244 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    yygotominor.yy0.type = panopticon::BOOL;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1032 "./src/Grammar/grammar.c"
        break;
      case 23: /* value ::= value PLUS value */
#line 254 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::plus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1045 "./src/Grammar/grammar.c"
        break;
      case 24: /* value ::= value MINUS value */
#line 264 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1058 "./src/Grammar/grammar.c"
        break;
      case 25: /* value ::= value DIVIDE value */
#line 274 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1071 "./src/Grammar/grammar.c"
        break;
      case 26: /* value ::= value TIMES value */
#line 284 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1084 "./src/Grammar/grammar.c"
        break;
      case 27: /* value ::= value MODULO value */
#line 294 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1097 "./src/Grammar/grammar.c"
        break;
      case 28: /* value ::= value POW value */
#line 304 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1110 "./src/Grammar/grammar.c"
        break;
      case 29: /* value ::= value EQUALTO value */
#line 314 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1123 "./src/Grammar/grammar.c"
        break;
      case 30: /* value ::= value NOTEQUALTO value */
#line 324 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1136 "./src/Grammar/grammar.c"
        break;
      case 31: /* value ::= value LESSTHAN value */
#line 334 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1149 "./src/Grammar/grammar.c"
        break;
      case 32: /* value ::= value GREATERTHAN value */
#line 344 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1162 "./src/Grammar/grammar.c"
        break;
      case 33: /* value ::= value LORE value */
#line 354 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1175 "./src/Grammar/grammar.c"
        break;
      case 34: /* value ::= value GORE value */
#line 364 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1188 "./src/Grammar/grammar.c"
        break;
      case 35: /* value ::= value AND value */
#line 374 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,2,&yymsp[-1].minor);
}
#line 1201 "./src/Grammar/grammar.c"
        break;
      case 36: /* value ::= value OR value */
#line 384 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1214 "./src/Grammar/grammar.c"
        break;
      case 37: /* value ::= BITNOT value */
#line 394 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1227 "./src/Grammar/grammar.c"
        break;
      case 38: /* value ::= NOT value */
#line 404 "./src/Grammar/grammar.y"
{
    not_value(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1240 "./src/Grammar/grammar.c"
        break;
      case 39: /* value ::= value SHIFTL value */
#line 414 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1253 "./src/Grammar/grammar.c"
        break;
      case 40: /* value ::= value SHIFTR value */
#line 424 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1266 "./src/Grammar/grammar.c"
        break;
      case 41: /* value ::= value BITAND value */
#line 434 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1279 "./src/Grammar/grammar.c"
        break;
      case 42: /* value ::= value BITOR value */
#line 444 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,4,&yymsp[-1].minor);
}
#line 1292 "./src/Grammar/grammar.c"
        break;
      case 43: /* value ::= value BITXOR value */
#line 454 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,3,&yymsp[-1].minor);
}
#line 1305 "./src/Grammar/grammar.c"
        break;
      case 44: /* value ::= variable OPENBRAC variable RBRAC */
#line 466 "./src/Grammar/grammar.y"
{
    index(yygotominor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,35,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1319 "./src/Grammar/grammar.c"
        break;
      case 45: /* stmt ::= variable */
#line 476 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
}
#line 1331 "./src/Grammar/grammar.c"
        break;
      case 46: /* variable ::= NAME ASSIGN value */
#line 486 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
    yygotominor.yy0.type = panopticon::VARIABLE;
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,36,&yymsp[-2].minor);
  yy_destructor(yypParser,30,&yymsp[-1].minor);
}
#line 1346 "./src/Grammar/grammar.c"
        break;
      case 47: /* in ::= error */
#line 502 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy115)
    {
    case panopticon::OpenQuoteError:
/*        panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        panopticon::out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 1361 "./src/Grammar/grammar.c"
        break;
      case 48: /* error ::= OPENQUOTEERROR */
#line 515 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy115 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1370 "./src/Grammar/grammar.c"
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
#line 71 "./src/Grammar/grammar.y"

panopticon::out() << "Syntax error!" << std::endl;
#line 1437 "./src/Grammar/grammar.c"
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
#line 66 "./src/Grammar/grammar.y"

printf("parsing complete!\n\n\n");
#line 1459 "./src/Grammar/grammar.c"
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
