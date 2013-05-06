#include "../../include/Grammar/lexer.h"

int w_count = 0;
int previous_w_count = 0;
int tab_count = 0;
int previous_tab_level = 0;
int current_tab_level = 0;

void calculate_tabs()
{
    if(w_count > previous_w_count+3)
    {
        previous_tab_level = current_tab_level;
        current_tab_level++;
        printf("Tab!");
    }
}

