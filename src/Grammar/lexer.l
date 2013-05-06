%{
#include "../../include/Grammar/lexglobal.h"
#include "../../include/Grammar/grammar.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "../../include/Grammar/lexer.h"
//#include "../../include/core/panerrors.h"

int line = 1, col = 0;


%}

%%


[0-9]+|[0-9]*\.[0-9]+    {
                                                int len = (int) strlen(yytext);
                                                col += len;
                                                w_count = col - len;
                                                yylval.dval = atof(yytext);
                                                return NUM; }
true       { yylval.bval = 1;return BOOLEAN;}
false     { yylval.bval = 0;return BOOLEAN;}
\n+[\t " "]*+"case"         { return CASE;}
"of"         { return OF;}
\n+[\t " "]*+"let"         { return LET;}
"let"         { return LET;}
\n+[\t " "]*+"in"         { return IN;}
"in"         { return IN;}
\n+[\t " "]*+"where"         { return WHERE;}
"where"         { return WHERE;}
\n+[\t " "]+[\t " "]*          { return N_TAB;}
    /*"("+\n           {  return OPENING_LPAREN; }
    \n+")"           {  return CLOSING_RPAREN; }*/
 "print"    {return PRINT;}
[ \t]   {
     int len = (int) strlen(yytext);
     col += len;
     w_count = col - len;
    }               /* ignore but count white space */
[A-Za-z][A-Za-z0-9]* {
    int len = (int) strlen(yytext);
    col += len;
    w_count = col - len;
    yylval.sval=strndup(yytext,(int)strlen(yytext));
    return NAME;
}
[+]+[+]           {  return PLUSPLUS; }
"+"           {  col++;w_count++; return PLUS; }
"-"           {  col++;w_count++; return MINUS; }
"*"           {  col++;w_count++; return TIMES; }
"/"           {  col++;w_count++; return DIVIDE; }
"("           {  col++;w_count++; return LPAREN; }
")"           {  col++;w_count++; return RPAREN; }
"<"           {  col++;w_count++; return LESSTHAN; }
">"           {  col++;w_count++; return GREATERTHAN; }
"=="          {  col++;w_count++; return EQUALTO;  }
">="          {  col++;w_count++; return GORE;  }
"<="          {  col++;w_count++; return LORE;  }
"!="          {  col++;w_count++; return NOTEQUALTO;  }
"<<"          {  col++;w_count++; return SHIFTL;  }
">>"          {  col++;w_count++; return SHIFTR;  }
"&&"          {  col++;w_count++; return AND;  }
"||"          {  col++;w_count++; return OR;  }
"!"          {  col++;w_count++; return NOT;  }
"~"          {  col++;w_count++; return BITNOT;  }
"&"          {  col++;w_count++; return BITAND;  }
"|"          {  col++;w_count++; return BITOR;  }
"^|"          {  col++;w_count++; return BITXOR;  }
"%"          {  col++;w_count++; return MODULO;  }
"["          {  col++;w_count++; return LBRAC;  }
"]"          {  col++;w_count++; return RBRAC;  }
","          { col++;w_count++; return COMMA;}
"="          { col++;w_count++; return ASSIGN;}
"^"          { col++;w_count++; return POW;}
"->"          { col++;w_count++; return POINTER;}
[\t " "]+"|"          { return GUARD_S;}
\n+[\t " "]*+"|"          { return GUARD_N;}
[\t " "]+"_"          { return WILDCARD;}
\n+[\t " "]*+"_"          { return WILDCARD_N;}
[\"][^"]*[\"] {
    int len = (int) strlen(yytext);
    col += len;
    w_count = col - len;
    yylval.sval=strndup(yytext+1,(int)strlen(yytext)-2);
    return STRING;}
"\""+[__+-={}|:;?/>.<,~`!@#$%^&*()A-Za-z0-9 \t\n\r]* {yyerror(yytext,1);return OPENQUOTEERROR;}

\n      { col = 0; ++line; w_count = col; calculate_tabs(); return NEWLINE; }
\r      { col = 0; ++line;  w_count = col; calculate_tabs(); printf("return!\n"); return NEWLINE; }

.       {
        int len = (int) strlen(yytext);
        col += len;
        w_count = col - len; return yytext[0];
    }
%%
/**
 * reset the line and column count
 *  []
 *
 */
void reset_lexer(void)
{

  line = 1;
  col  = 1;

}

/**
 * yyerror() is invoked when the lexer or the parser encounter
 * an error. The error message is passed via *s
 *
 *
 */
void yyerror(char *s, int errorCode)
{
    switch(errorCode)
    {
    //panopticon::OpenQuoteError
    case 1:
        printf("Syntax Error p0001, dangling quotation mark: %s at line: %d col: %d\n",s,line,col);
        break;
    //panopticon::UnknownError
    case 0:
    default:
        printf("Syntax Error p0000: %s at line: %d col: %d\n",s,line,col);
        break;
    }
}

int yywrap(void)
{
  return 1;
}
