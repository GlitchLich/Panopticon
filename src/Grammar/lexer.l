%{
#include "../../include/Grammar/lexglobal.h"
#include "../../include/Grammar/grammar.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

int line = 1, col = 1;


%}

%option noyywrap

%%

        /*^[ ]*\n       {/* Ignore}*/
    /*^[ ]*[^ \n]+  {
        int last = (int) strlen(yytext) - 2;
        calculate_white_space(yytext);
        while( (last >= 0) )
        {
            if(yytext[last] != '\n')
            {
                printf("Unput: %c\n",yytext[last]);
                unput( yytext[last] );
            }
            last-- ;
        }
    }*/
[;]     {return DELIMITER;}
[{]     {return LCURL;}
[}]     {return RCURL;}
[0-9]+|[0-9]*\.[0-9]+    {
    col += (int) strlen(yytext);
    yylval.dval = atof(yytext);
    return NUM;
}
true       { yylval.bval = 1;return BOOLEAN;}
false     { yylval.bval = 0;return BOOLEAN;}
"case"      { return CASE;}
"of"         { return OF;}
"let"         { return LET;}
"in"         { return IN;}
"where"         { return WHERE;}
"print"    {return PRINT;}
[ \t]   {
        col += (int) strlen(yytext);
}               /* ignore but count white space */
[A-Za-z][A-Za-z0-9]* {
    col += (int)strlen(yytext);
    yylval.sval=strndup(yytext,(int)strlen(yytext));
    return NAME;
}
[+]+[+]          {  return PLUSPLUS; }
"::"          {  return COLONCOLON; }
"+"           {  return PLUS; }
"-"           {  return MINUS; }
"*"           {  return TIMES; }
"/"           {  return DIVIDE; }
"("           {  return LPAREN; }
")"           {  return RPAREN; }
"<"           {  return LESSTHAN; }
">"           {  return GREATERTHAN; }
"=="          {  return EQUALTO;  }
">="          {  return GORE;  }
"<="          {  return LORE;  }
"!="          {  return NOTEQUALTO;  }
"<<"          {  return SHIFTL;  }
">>>"          {  return SHIFTR;  }
"&&"          {  return AND;  }
"||"          {  return OR;  }
"!"          {  return NOT;  }
"~"          {  return BITNOT;  }
"&"          {  return BITAND;  }
"|"          {  return BITOR;  }
"^|"          {  return BITXOR;  }
"%"          {  return MODULO;  }
"["          {  return LBRAC;  }
"]"          {  return RBRAC;  }
","          { return COMMA;}
"="          { return ASSIGN;}
"^"          { return POW;}
"_"          { return WILDCARD;}
"<:"          { return APPEND;}
":>"          { return PREPEND;}
":"         {return PREPEND;}
">>"       {return COMPOSITION;}
[\"][^"]*[\"] {
    col += (int)strlen(yytext);
    yylval.sval=strndup(yytext+1,(int)strlen(yytext)-2);
    return STRING;
}
"\""+[__+-={}|:;?/>.<,~`!@#$%^&*()A-Za-z0-9 \t\n\r]* {yyerror(yytext,1);return OPENQUOTEERROR;}

\n      { col = 0; ++line; /*return NEWLINE;*/}
\r      { col = 0; ++line; /*printf("return!\n"); return NEWLINE; */}

.       {
    /*calculate_white_space("");*/
    col += (int) strlen(yytext);
    return yytext[0];
}

    /*<<EOF>>  { calculate_white_space("") ; return 0 ; }*/

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

    /*int yywrap(void)
    {
        return 1;
    }*/
