#pragma once
#include "list.h"

void open(FILE * pfile);
void close(FILE * pfile);
void dump_list (list_struct * list, FILE * pfile);

void create_new_grapth(void);
void draw_grath(list_struct * list, const char * func);
void grapth_presentation(void);

inline char count_gr[] = "1";