#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"      // question: i want make header for each cpp but i have const that needed in two cpps

char count_gr[] = "1";

void open(FILE * pfile) {
    fprintf(pfile, "\n     ");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, "______");
    }
    fprintf(pfile, "\n");
    return;
}
void close(FILE * pfile) {
    fprintf(pfile, "\n     ");

    for (int i = 0; i < count; i++) {
        fprintf(pfile, "|     ");
    }
    fprintf(pfile, "|");
    fprintf(pfile, "\n     ");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, "|     ");
    }
    fprintf(pfile, "|");
    fprintf(pfile, "\n     ");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, "|_____");
    }
    fprintf(pfile, "|");
    return;
}
void dump_list (list_struct * list, FILE * pfile) {
    fprintf(pfile, "\n\n     --------------------------next dump--------------------------\n\n");
    open(pfile);
    fprintf(pfile, "  ip:| ");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, "%.3d | ", i);
    }
    close(pfile);



    fprintf(pfile, "\ndata:|");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, " %.3d |", (list->data[i]).value);
    }

    close(pfile);

    fprintf(pfile, "\nnext:|");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, " %.3d |", (list->data[i]).next);
    }

    close(pfile);

    fprintf(pfile, "\nprev:|");
    for (int i = 0; i < count; i++) {
        if((list->data[i]).prev == free_elem) {
            fprintf(pfile, " fre |");
        } else {
            fprintf(pfile, " %.3d |", (list->data[i]).prev);
        }
    }
    close(pfile);


    fprintf(pfile, "\n\nhead: [%.3d]\n", list->head);
    fprintf(pfile, "tale: [%.3d]\n", list->tale);
    fprintf(pfile, "free: [%.3d]\n", list->free);

}

void create_new_grapth(void) {
    char command1[1000] = "dot -Tpng /Users/anzhiday/Documents/list/grath.dot  -o /Users/anzhiday/Documents/list/grapths/grath";
    char command2[] = ".png";
    strcat(command1, count_gr);
    strcat(command1, command2);
    system(command1);
    snprintf(count_gr, 2,  "%d", (1 + atoi(count_gr)));
}


void draw_grath(list_struct * list, const char * func) {
    FILE * pfile = fopen("grath.dot", "wb");
    fprintf(pfile, "digraph structs {\n");
    fprintf(pfile, "\trankdir=LR;\n");
    fprintf(pfile, "\tgraph [bgcolor=\"#31353b\"]\n");
    fprintf(pfile, "\tnode[color=\"black\",fontsize=14];\n");
    fprintf(pfile, "\tedge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n\n\n");

    fprintf(pfile, "\t50 [shape=note,style=filled, fillcolor=\"#fdf39b\", label=\" was called from %s\", fontcolor = \"black\", fontsize = 20];\n", func);

    for (int i = 0; i < count; i++) {
        fprintf(pfile, "\t%d [shape=Mrecord,style=filled, fillcolor=\"#7293ba\", label=\" ip: %d ", i, i);
        fprintf(pfile, "| data: %d", list->data[i].value);
        fprintf(pfile, "| next: %d", list->data[i].next);
        if (list->data[i].prev == free_elem) {
            fprintf(pfile, "| prev: fre\" ");
        } else {
            fprintf(pfile, "| prev: %d\" ", list->data[i].prev);
        }
        if (list->data[i].prev == free_elem) {
             fprintf(pfile, ", color = lightgreen];\n");
        } else {
            fprintf(pfile, "];\n");
        }
    }
    fprintf(pfile, "\n\t");
    for (int i = 0; i < count - 1; i++) {
        fprintf(pfile, "%d->", i);
    }
    fprintf(pfile, "%d[weight = 10000, color = \"#31353b\"];\n", count - 1);

////////////////////////////
    for(int i = 0; i < count - 1; i++) {
        if (list->data[i].prev == free_elem) {     // draw next line
            fprintf(pfile, "\t%d->%d[color = \"#22f230\"];\n", i, list->data[i].next);
        } else if (list->data[i].next == 0) {
            fprintf(pfile, "\t%d->%d[color = \"#8139bd\"];\n", i, list->data[i].next);
        } else {
            fprintf(pfile, "\t%d->%d[color = \"#0ae7ff\"];\n", i, list->data[i].next);
        }
    }
    for (int i = 0; i < count; i++) {
        if (list->data[i].prev != free_elem && list->data[i].prev != list->tale) {   // draw prev line
            fprintf(pfile, "\t%d -> %d[color = \"#ff0a0a\"];\n", i, list->data[i].prev);
        } else if (list->data[i].prev == list->tale) {
            fprintf(pfile, "\t%d -> %d[color = \"#8139bd\"];\n", i, list->data[i].prev);
        }
    }

    fprintf(pfile, "\th [shape=tripleoctagon,label=\"HEAD\", color = \"yellow\", fillcolor=\"#7293ba\",style=filled  ];\n");
    fprintf(pfile, "\tt [shape=tripleoctagon,label=\"TALE\", color = \"yellow\", fillcolor=\"#7293ba\",style=filled ];\n");
    fprintf(pfile, "\tf [shape=tripleoctagon,label=\"FREE\", color = \"yellow\", fillcolor=\"#7293ba\",style=filled ];\n");
    fprintf(pfile, "\th->t->f[weight = 10000, color = \"#31353b\"];\n");
    fprintf(pfile, "\th->%d[color = \"orange\"];\n", list->head);
    fprintf(pfile, "\tt->%d[color = \"orange\"];\n", list->tale);
    fprintf(pfile, "\tf->%d[color = \"orange\"];\n", list->free);
    fprintf(pfile, "\n}");
    fclose(pfile);


    create_new_grapth();   
}


