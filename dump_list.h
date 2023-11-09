#pragma once
#include "list.h"

void list_cell_open(FILE * pfile);
void list_cell_close(FILE * pfile);

void dump_list(doubly_linked_list * list, FILE * pfile);

void create_new_graph(void);
void draw_graph(doubly_linked_list * list, const char * func);

void graph_presentation(void);

inline char count_gr[] = "1";
const int command_len = 1000;