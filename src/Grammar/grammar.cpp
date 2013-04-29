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
/*    panopticon::out() << "In token_destructor t.expr= " << t.expr << std::endl;*/
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
#define YYNOCODE 54
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy107;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 70
#define YYNRULE 45
#define YYERRORSYMBOL 37
#define YYERRSYMDT yy107
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
#define YY_ACTTAB_COUNT (321)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    11,   12,    6,    7,    8,   18,   17,   15,   13,   16,
 /*    10 */    14,   10,    9,   25,   23,   22,   21,   20,   19,   12,
 /*    20 */     6,    7,    8,   18,   17,   15,   13,   16,   14,   10,
 /*    30 */     9,   25,   23,   22,   21,   20,   19,    6,    7,    8,
 /*    40 */    18,   17,   15,   13,   16,   14,   10,    9,   25,   23,
 /*    50 */    22,   21,   20,   19,    7,    8,   18,   17,   15,   13,
 /*    60 */    16,   14,   10,    9,   25,   23,   22,   21,   20,   19,
 /*    70 */     8,   18,   17,   15,   13,   16,   14,   10,    9,   25,
 /*    80 */    23,   22,   21,   20,   19,   18,   17,   15,   13,   16,
 /*    90 */    14,   10,    9,   25,   23,   22,   21,   20,   19,   15,
 /*   100 */    13,   16,   14,   10,    9,   25,   23,   22,   21,   20,
 /*   110 */    19,   27,   68,   19,   24,   51,   67,   66,   65,   64,
 /*   120 */    50,   27,   70,   62,   61,   60,   54,  117,   56,   64,
 /*   130 */    50,    3,   43,   62,   61,   60,   22,   21,   20,   19,
 /*   140 */    52,  117,    4,    5,   25,   23,   22,   21,   20,   19,
 /*   150 */     2,  117,  117,   69,   63,   59,   58,   57,   53,  117,
 /*   160 */   117,  116,    1,   10,    9,   25,   23,   22,   21,   20,
 /*   170 */    19,   27,  117,  117,    4,    5,  117,  117,   55,   64,
 /*   180 */    50,   41,    2,   62,   61,   60,   63,   59,   58,   57,
 /*   190 */     4,    5,  117,   62,   61,   60,   26,  117,    2,  117,
 /*   200 */   117,  117,   42,   59,   58,   57,   49,  117,   62,   61,
 /*   210 */    60,  117,  117,   48,   62,   61,   60,   47,   62,   61,
 /*   220 */    60,   46,  117,  117,   34,   62,   61,   60,   33,   62,
 /*   230 */    61,   60,   38,   62,   61,   60,   62,   61,   60,  117,
 /*   240 */    62,   61,   60,   37,   62,   61,   60,   36,  117,  117,
 /*   250 */   117,  117,   35,  117,  117,   62,   61,   60,   29,   62,
 /*   260 */    61,   60,  117,   28,   62,   61,   60,   40,  117,  117,
 /*   270 */    62,   61,   60,   39,  117,   62,   61,   60,  117,   62,
 /*   280 */    61,   60,   32,  117,  117,   62,   61,   60,  117,  117,
 /*   290 */   117,   31,  117,  117,   62,   61,   60,   30,  117,  117,
 /*   300 */    45,  117,  117,   62,   61,   60,   44,  117,  117,   62,
 /*   310 */    61,   60,   62,   61,   60,  117,  117,  117,   62,   61,
 /*   320 */    60,
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
 /*    90 */    11,   12,   13,   14,   15,   16,   17,   18,   19,    8,
 /*   100 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   110 */    19,   38,   31,   19,   30,   42,   43,   44,   45,   46,
 /*   120 */    47,   38,    0,   50,   51,   52,   29,   53,   45,   46,
 /*   130 */    47,   48,   49,   50,   51,   52,   16,   17,   18,   19,
 /*   140 */    36,   53,   20,   21,   14,   15,   16,   17,   18,   19,
 /*   150 */    28,   53,   53,   31,   32,   33,   34,   35,   37,   53,
 /*   160 */    53,   40,   41,   12,   13,   14,   15,   16,   17,   18,
 /*   170 */    19,   38,   53,   53,   20,   21,   53,   53,   45,   46,
 /*   180 */    47,   38,   28,   50,   51,   52,   32,   33,   34,   35,
 /*   190 */    20,   21,   53,   50,   51,   52,   38,   53,   28,   53,
 /*   200 */    53,   53,   38,   33,   34,   35,   38,   53,   50,   51,
 /*   210 */    52,   53,   53,   38,   50,   51,   52,   38,   50,   51,
 /*   220 */    52,   38,   53,   53,   38,   50,   51,   52,   38,   50,
 /*   230 */    51,   52,   38,   50,   51,   52,   50,   51,   52,   53,
 /*   240 */    50,   51,   52,   38,   50,   51,   52,   38,   53,   53,
 /*   250 */    53,   53,   38,   53,   53,   50,   51,   52,   38,   50,
 /*   260 */    51,   52,   53,   38,   50,   51,   52,   38,   53,   53,
 /*   270 */    50,   51,   52,   38,   53,   50,   51,   52,   53,   50,
 /*   280 */    51,   52,   38,   53,   53,   50,   51,   52,   53,   53,
 /*   290 */    53,   38,   53,   53,   50,   51,   52,   38,   53,   53,
 /*   300 */    38,   53,   53,   50,   51,   52,   38,   53,   53,   50,
 /*   310 */    51,   52,   50,   51,   52,   53,   53,   53,   50,   51,
 /*   320 */    52,
};
#define YY_SHIFT_USE_DFLT (-2)
#define YY_SHIFT_COUNT (51)
#define YY_SHIFT_MIN   (-1)
#define YY_SHIFT_MAX   (170)
static const short yy_shift_ofst[] = {
 /*     0 */   104,  122,  154,  154,  170,  170,  170,  170,  170,  170,
 /*    10 */   170,  170,  170,  170,  170,  170,  170,  170,  170,  170,
 /*    20 */   170,  170,  170,  170,  170,  170,   -1,   -1,   17,   34,
 /*    30 */    50,   65,   79,   91,   91,  151,  151,  151,  151,  130,
 /*    40 */   130,  120,  120,   97,   94,   94,   94,   94,   94,   94,
 /*    50 */    84,   81,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (25)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (268)
static const short yy_reduce_ofst[] = {
 /*     0 */   121,   73,   83,  133,  268,  262,  259,  253,  244,  235,
 /*    10 */   229,  225,  220,  214,  209,  205,  194,  190,  186,  183,
 /*    20 */   179,  175,  168,  164,  158,  143,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */    71,  115,   84,   85,  115,  115,  115,  115,  115,  115,
 /*    10 */   115,  115,  115,  115,  115,  115,  115,  115,  115,  115,
 /*    20 */   115,  115,  115,  115,  115,  115,   80,   77,  105,  104,
 /*    30 */   112,  111,  110,   99,   98,  103,  102,  101,  100,  109,
 /*    40 */   108,   92,   93,  115,  107,  106,   97,   96,   95,   94,
 /*    50 */   115,  115,  114,  113,   83,   82,   81,   91,   90,   89,
 /*    60 */    88,   87,   86,   79,   78,   76,   75,   74,   73,   72,
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
  "NAME",          "NUM",           "STRING",        "BOOLEAN",     
  "OPENQUOTEERROR",  "error",         "expr",          "id",          
  "main",          "in",            "start",         "spec",        
  "top_stmt",      "stmt",          "assignment",    "identifier",  
  "stmt_list",     "maybe_empty_stmt_list",  "num",           "string",      
  "bool",        
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
 /*   8 */ "stmt ::= assignment",
 /*   9 */ "identifier ::= NAME",
 /*  10 */ "assignment ::= identifier ASSIGN expr",
 /*  11 */ "stmt_list ::= stmt",
 /*  12 */ "stmt_list ::= stmt_list stmt",
 /*  13 */ "expr ::= LBRAC maybe_empty_stmt_list RBRAC",
 /*  14 */ "maybe_empty_stmt_list ::=",
 /*  15 */ "maybe_empty_stmt_list ::= stmt_list",
 /*  16 */ "expr ::= num",
 /*  17 */ "expr ::= string",
 /*  18 */ "expr ::= bool",
 /*  19 */ "num ::= NUM",
 /*  20 */ "string ::= STRING",
 /*  21 */ "bool ::= BOOLEAN",
 /*  22 */ "expr ::= expr PLUS expr",
 /*  23 */ "expr ::= expr MINUS expr",
 /*  24 */ "expr ::= expr DIVIDE expr",
 /*  25 */ "expr ::= expr TIMES expr",
 /*  26 */ "expr ::= expr MODULO expr",
 /*  27 */ "expr ::= expr POW expr",
 /*  28 */ "expr ::= expr EQUALTO expr",
 /*  29 */ "expr ::= expr NOTEQUALTO expr",
 /*  30 */ "expr ::= expr LESSTHAN expr",
 /*  31 */ "expr ::= expr GREATERTHAN expr",
 /*  32 */ "expr ::= expr LORE expr",
 /*  33 */ "expr ::= expr GORE expr",
 /*  34 */ "expr ::= expr AND expr",
 /*  35 */ "expr ::= expr OR expr",
 /*  36 */ "expr ::= BITNOT expr",
 /*  37 */ "expr ::= NOT expr",
 /*  38 */ "expr ::= expr SHIFTL expr",
 /*  39 */ "expr ::= expr SHIFTR expr",
 /*  40 */ "expr ::= expr BITAND expr",
 /*  41 */ "expr ::= expr BITOR expr",
 /*  42 */ "expr ::= expr BITXOR expr",
 /*  43 */ "in ::= error",
 /*  44 */ "error ::= OPENQUOTEERROR",
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
    case 32: /* NAME */
    case 33: /* NUM */
    case 34: /* STRING */
    case 35: /* BOOLEAN */
    case 36: /* OPENQUOTEERROR */
{
#line 41 "./src/Grammar/grammar.y"
 token_destructor((yypminor->yy0)); 
#line 556 "./src/Grammar/grammar.c"
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
  { 40, 1 },
  { 41, 0 },
  { 41, 2 },
  { 41, 3 },
  { 42, 1 },
  { 43, 1 },
  { 44, 1 },
  { 45, 1 },
  { 45, 1 },
  { 47, 1 },
  { 46, 3 },
  { 48, 1 },
  { 48, 2 },
  { 38, 3 },
  { 49, 0 },
  { 49, 1 },
  { 38, 1 },
  { 38, 1 },
  { 38, 1 },
  { 50, 1 },
  { 51, 1 },
  { 52, 1 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 2 },
  { 38, 2 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 41, 1 },
  { 37, 1 },
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
#line 899 "./src/Grammar/grammar.c"
        break;
      case 4: /* start ::= spec */
#line 86 "./src/Grammar/grammar.y"
{
    optic::print_object(yymsp[0].minor.yy0);
    optic::delete_object(yymsp[0].minor.yy0);
}
#line 907 "./src/Grammar/grammar.c"
        break;
      case 5: /* spec ::= top_stmt */
      case 6: /* top_stmt ::= stmt */ yytestcase(yyruleno==6);
      case 17: /* expr ::= string */ yytestcase(yyruleno==17);
#line 93 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;

}
#line 917 "./src/Grammar/grammar.c"
        break;
      case 7: /* stmt ::= expr */
      case 11: /* stmt_list ::= stmt */ yytestcase(yyruleno==11);
#line 104 "./src/Grammar/grammar.y"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;

}
#line 926 "./src/Grammar/grammar.c"
        break;
      case 9: /* identifier ::= NAME */
#line 132 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STRING;
    yygotominor.yy0.data.string = new panopticon::String(*yymsp[0].minor.yy0.data.string);
    delete yymsp[0].minor.yy0.data.string;
}
#line 935 "./src/Grammar/grammar.c"
        break;
      case 10: /* assignment ::= identifier ASSIGN expr */
#line 137 "./src/Grammar/grammar.y"
{
  yy_destructor(yypParser,30,&yymsp[-1].minor);
}
#line 942 "./src/Grammar/grammar.c"
        break;
      case 12: /* stmt_list ::= stmt_list stmt */
#line 149 "./src/Grammar/grammar.y"
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
#line 961 "./src/Grammar/grammar.c"
        break;
      case 13: /* expr ::= LBRAC maybe_empty_stmt_list RBRAC */
#line 172 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::ARRAY;
    yygotominor.yy0.data.array = yymsp[-1].minor.yy0.data.array;
  yy_destructor(yypParser,28,&yymsp[-2].minor);
  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 971 "./src/Grammar/grammar.c"
        break;
      case 14: /* maybe_empty_stmt_list ::= */
#line 178 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.type = panopticon::STATEMENT_LIST;
    panopticon::create_array(yygotominor.yy0);
}
#line 979 "./src/Grammar/grammar.c"
        break;
      case 15: /* maybe_empty_stmt_list ::= stmt_list */
#line 184 "./src/Grammar/grammar.y"
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
#line 995 "./src/Grammar/grammar.c"
        break;
      case 16: /* expr ::= num */
      case 18: /* expr ::= bool */ yytestcase(yyruleno==18);
#line 208 "./src/Grammar/grammar.y"
{
    yygotominor.yy0=yymsp[0].minor.yy0;
}
#line 1003 "./src/Grammar/grammar.c"
        break;
      case 19: /* num ::= NUM */
#line 233 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.number = yymsp[0].minor.yy0.data.number;
    yygotominor.yy0.type = panopticon::NUMBER;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1012 "./src/Grammar/grammar.c"
        break;
      case 20: /* string ::= STRING */
#line 240 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.string = new panopticon::String(yymsp[0].minor.yy0.data.string->c_str());
    delete yymsp[0].minor.yy0.data.string;
    yygotominor.yy0.type = panopticon::STRING;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1022 "./src/Grammar/grammar.c"
        break;
      case 21: /* bool ::= BOOLEAN */
#line 249 "./src/Grammar/grammar.y"
{
    yygotominor.yy0.data.boolean = yymsp[0].minor.yy0.data.boolean;
    yygotominor.yy0.type = panopticon::BOOL;
    //yygotominor.yy0.n = yymsp[0].minor.yy0.n+1;
}
#line 1031 "./src/Grammar/grammar.c"
        break;
      case 22: /* expr ::= expr PLUS expr */
#line 259 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::plus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,14,&yymsp[-1].minor);
}
#line 1044 "./src/Grammar/grammar.c"
        break;
      case 23: /* expr ::= expr MINUS expr */
#line 269 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::minus);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,15,&yymsp[-1].minor);
}
#line 1057 "./src/Grammar/grammar.c"
        break;
      case 24: /* expr ::= expr DIVIDE expr */
#line 279 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::divide);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,16,&yymsp[-1].minor);
}
#line 1070 "./src/Grammar/grammar.c"
        break;
      case 25: /* expr ::= expr TIMES expr */
#line 289 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::multiply);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,17,&yymsp[-1].minor);
}
#line 1083 "./src/Grammar/grammar.c"
        break;
      case 26: /* expr ::= expr MODULO expr */
#line 299 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::modulo);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 1096 "./src/Grammar/grammar.c"
        break;
      case 27: /* expr ::= expr POW expr */
#line 309 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_pow);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,19,&yymsp[-1].minor);
}
#line 1109 "./src/Grammar/grammar.c"
        break;
      case 28: /* expr ::= expr EQUALTO expr */
#line 319 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,6,&yymsp[-1].minor);
}
#line 1122 "./src/Grammar/grammar.c"
        break;
      case 29: /* expr ::= expr NOTEQUALTO expr */
#line 329 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::not_equal_to);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1135 "./src/Grammar/grammar.c"
        break;
      case 30: /* expr ::= expr LESSTHAN expr */
#line 339 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::less_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1148 "./src/Grammar/grammar.c"
        break;
      case 31: /* expr ::= expr GREATERTHAN expr */
#line 349 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::greater_than);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,8,&yymsp[-1].minor);
}
#line 1161 "./src/Grammar/grammar.c"
        break;
      case 32: /* expr ::= expr LORE expr */
#line 359 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::lore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,11,&yymsp[-1].minor);
}
#line 1174 "./src/Grammar/grammar.c"
        break;
      case 33: /* expr ::= expr GORE expr */
#line 369 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::gore);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 1187 "./src/Grammar/grammar.c"
        break;
      case 34: /* expr ::= expr AND expr */
#line 379 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,2,&yymsp[-1].minor);
}
#line 1200 "./src/Grammar/grammar.c"
        break;
      case 35: /* expr ::= expr OR expr */
#line 389 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::value_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 1213 "./src/Grammar/grammar.c"
        break;
      case 36: /* expr ::= BITNOT expr */
#line 399 "./src/Grammar/grammar.y"
{
    bit_not(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,21,&yymsp[-1].minor);
}
#line 1226 "./src/Grammar/grammar.c"
        break;
      case 37: /* expr ::= NOT expr */
#line 409 "./src/Grammar/grammar.y"
{
    not_value(yygotominor.yy0,yymsp[0].minor.yy0);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,20,&yymsp[-1].minor);
}
#line 1239 "./src/Grammar/grammar.c"
        break;
      case 38: /* expr ::= expr SHIFTL expr */
#line 419 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_left);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,12,&yymsp[-1].minor);
}
#line 1252 "./src/Grammar/grammar.c"
        break;
      case 39: /* expr ::= expr SHIFTR expr */
#line 429 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::shift_right);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,13,&yymsp[-1].minor);
}
#line 1265 "./src/Grammar/grammar.c"
        break;
      case 40: /* expr ::= expr BITAND expr */
#line 439 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_and);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 1278 "./src/Grammar/grammar.c"
        break;
      case 41: /* expr ::= expr BITOR expr */
#line 449 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_or);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,4,&yymsp[-1].minor);
}
#line 1291 "./src/Grammar/grammar.c"
        break;
      case 42: /* expr ::= expr BITXOR expr */
#line 459 "./src/Grammar/grammar.y"
{
    object_operator_object(yygotominor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0,&panopticon::bit_xor);
    if(!panopticon::correct_parsing)
    {
        while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
        ParseARG_STORE;
    }
  yy_destructor(yypParser,3,&yymsp[-1].minor);
}
#line 1304 "./src/Grammar/grammar.c"
        break;
      case 43: /* in ::= error */
#line 509 "./src/Grammar/grammar.y"
{
    switch(yymsp[0].minor.yy107)
    {
    case panopticon::OpenQuoteError:
/*        panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;*/
        break;
    default:
/*        panopticon::out() << "ERROR p0000: UnknownError" << std::endl;*/
        break;
    }
}
#line 1319 "./src/Grammar/grammar.c"
        break;
      case 44: /* error ::= OPENQUOTEERROR */
#line 522 "./src/Grammar/grammar.y"
{
    yymsp[0].minor.yy0.type = panopticon::NUMBER;
    yygotominor.yy107 = panopticon::OpenQuoteError;
    panopticon::out() << "ERROR p0001: Dangling quotation mark." << std::endl;
}
#line 1328 "./src/Grammar/grammar.c"
        break;
      default:
      /* (0) main ::= in */ yytestcase(yyruleno==0);
      /* (1) in ::= */ yytestcase(yyruleno==1);
      /* (8) stmt ::= assignment */ yytestcase(yyruleno==8);
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
#line 1396 "./src/Grammar/grammar.c"
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
#line 1418 "./src/Grammar/grammar.c"
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
