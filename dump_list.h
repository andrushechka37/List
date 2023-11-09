#pragma once
#include "list.h"

void list_cell_open(FILE * pfile);
void list_cell_close(FILE * pfile);

void dump_list_txt(doubly_linked_list * list, FILE * pfile); // func doesn't refer directly to the list
                                                             // so list is on the second position. Am i right?
void create_new_graph(void);
void list_visualize(doubly_linked_list * list, const char * comment);

void unite_visualizations(void);

inline int graph_number = 1;
const int command_len = 1000;