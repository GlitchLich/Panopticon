#ifndef PARSE_H
#define PARSE_H

struct Token;

#define ParseTOKENTYPE Token
#define ParseARG_PDECL

extern void *ParseAlloc(void *(*mallocProc)(size_t));
extern void Parse(
        void* yyp,                   /* The parser */
        int yymajor,                 /* The major token code number */
        ParseTOKENTYPE yyminor       /* The value for the token */
        ParseARG_PDECL               /* Optional %extra_argument parameter */
      );
extern void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
);
#endif // PARSE_H
