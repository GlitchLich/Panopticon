#include "../../include/Grammar/lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAX_DEPTH 72
unsigned int indent_stack[MAX_DEPTH];
unsigned int level = 0;
int nesting = 0;
unsigned int first = 1;

void clear_lexer()
{

}

unsigned int white_count(char* line) {
    unsigned int count = 0 ;
    while (*line == ' ')
        count++, line++ ;
    return count ;
}

void calculate_white_space(char* line) {
    if (nesting)
        /* Ignore indents while nested. */
        return ;

    printf("              \n");
    unsigned int indent = white_count(line) ;

    if (indent == indent_stack[level]) {
        if (!first) printf(" ;\n") ;
        first = 0 ;
        return ;
    }

    if (indent > indent_stack[level]) {
        printf(" {\n") ;
        assert(level+1 < MAX_DEPTH) ;
        indent_stack[++level] = indent ;
        return ;
    }

    while (indent < indent_stack[level]) {
        --level ;
        printf(" }\n") ;
    }
    printf("              \n");
    assert(level >= 0) ;
}
