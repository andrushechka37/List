#pragma once
#include "list.h"

void list_cell_open(FILE * pfile);
void list_cell_close(FILE * pfile);

void dump_list (doubly_linked_list * list, FILE * pfile);

void create_new_grapth(void);
void draw_grapth(doubly_linked_list * list, const char * func);

void grapth_presentation(void);

inline char count_gr[] = "1";
const int command_len = 1000;