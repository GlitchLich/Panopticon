#ifndef LEXER_H
#define LEXER_H

extern unsigned int indent_stack[];
extern unsigned int level;
extern unsigned int first;
extern int nesting;
extern void calculate_white_space(char* line);
extern unsigned int w_count(char* line);

#endif // LEXER_H
