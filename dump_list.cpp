#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dump_list.h"  



void unite_visualizations(void) {
    char command[command_len] = "open /opt/local/bin/sxiv ";
    char file[] = " /Users/anzhiday/Documents/list/graphs/graph";
    for (int i = 1; i < graph_number; i++) {
        char number[6] = "";   // magic number? YES
        snprintf(number, 6,  "%d.png", i);
        strcat(command, file);
        strcat(command, number);
    }
    printf("%s", command);
    system(command);
}

void list_cell_open(FILE * pfile) {
    fprintf(pfile, "\n     ");
    for (int i = 0; i < list_capacity; i++) {
        fprintf(pfile, "______");
    }
    fprintf(pfile, "\n");
    return;
}

void list_cell_close(FILE * pfile) {
    fprintf(pfile, "\n     ");

    for (int i = 0; i < list_capacity; i++) {
        fprintf(pfile, "|     ");
    }
    fprintf(pfile, "|");
    fprintf(pfile, "\n     ");
    for (int i = 0; i < list_capacity; i++) {
        fprintf(pfile, "|     ");
    }
    fprintf(pfile, "|");
    fprintf(pfile, "\n     ");
    for (int i = 0; i < list_capacity; i++) {
        fprintf(pfile, "|_____");
    }
    fprintf(pfile, "|");
    return;
}

void dump_list_txt(doubly_linked_list * list, FILE * pfile) {
    fprintf(pfile, "\n\n     --------------------------next dump--------------------------\n\n");
    list_cell_open(pfile);
    fprintf(pfile, "  ip:| ");
    for (int i = 0; i < list_capacity; i++) {
        fprintf(pfile, "%.3d | ", i);
    }
    list_cell_close(pfile);



    fprintf(pfile, "\ndata:|");
    for (int i = 0; i < list_capacity; i++) {
        fprintf(pfile, " %.3d |", (list->data[i]).value);
    }

    list_cell_close(pfile);

    fprintf(pfile, "\nnext:|");
    for (int i = 0; i < list_capacity; i++) {
        fprintf(pfile, " %.3d |", (list->data[i]).next);
    }

    list_cell_close(pfile);

    fprintf(pfile, "\nprev:|");
    for (int i = 0; i < list_capacity; i++) {
        if((list->data[i]).prev == free_elem_marker) {
            fprintf(pfile, " fre |");
        } else {
            fprintf(pfile, " %.3d |", (list->data[i]).prev);
        }
    }
    list_cell_close(pfile);


    fprintf(pfile, "\n\nhead: [%.3d]\n", list->data[0].next);
    fprintf(pfile, "tale: [%.3d]\n", list->data[0].prev);
    fprintf(pfile, "free: [%.3d]\n", list->free_element_head);

}

void create_new_graph(void) {  // TODO: temporary files
    char command1[command_len] = "dot -Tpng /Users/anzhiday/Documents/list/grath.dot  -o /Users/anzhiday/Documents/list/graphs/graph";
    char command2[] = ".png";
    char graph_number_str[2] = {};

    snprintf(graph_number_str, 2,  "%d", graph_number);
    strcat(command1, graph_number_str);
    strcat(command1, command2);
    system(command1);
    graph_number++;
}


void list_visualize(doubly_linked_list * list, const char * comment) {
    FILE * pfile = fopen("grath.dot", "wb");
    fprintf(pfile, "digraph structs {\n");
    fprintf(pfile, "\trankdir=LR;\n");
    fprintf(pfile, "\tgraph [bgcolor=\"#31353b\"]\n");
    fprintf(pfile, "\tnode[color=\"black\",fontsize=14];\n");
    fprintf(pfile, "\tedge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n\n\n");

    fprintf(pfile, "\t50 [shape=note,style=filled, fillcolor=\"#fdf39b\", label=\"%s\", fontcolor = \"black\", fontsize = 20];\n", comment);

    for (int i = 0; i < list_capacity; i++) {
        fprintf(pfile, "\t%d [shape=Mrecord,style=filled, fillcolor=\"#7293ba\", label=\" ip: %d ", i, i);
        fprintf(pfile, "| data: %d", list->data[i].value);
        fprintf(pfile, "| next: %d", list->data[i].next);
        if (list->data[i].prev == free_elem_marker) {
            fprintf(pfile, "| prev: fre\" ");
        } else {
            fprintf(pfile, "| prev: %d\" ", list->data[i].prev);
        }
        if (list->data[i].prev == free_elem_marker) {
             fprintf(pfile, ", color = lightgreen];\n");
        } else {
            fprintf(pfile, "];\n");
        }
    }
    fprintf(pfile, "\n\t");
    for (int i = 0; i < list_capacity - 1; i++) {
        fprintf(pfile, "%d->", i);
    }
    fprintf(pfile, "%d[weight = 100, color = \"invis\"];\n", list_capacity - 1);


    for(int i = 0; i < list_capacity - 1; i++) {
        if (list->data[i].prev == free_elem_marker) {     // draw next line
            fprintf(pfile, "\t%d->%d[color = \"#22f230\", constraint=false];\n", i, list->data[i].next);
        } else if (list->data[i].next == 0) {
            fprintf(pfile, "\t%d->%d[color = \"#8139bd\", constraint=false];\n", i, list->data[i].next);
        } else {
            fprintf(pfile, "\t%d->%d[color = \"#0ae7ff\", constraint=false];\n", i, list->data[i].next);
        }
    }
    for (int i = 0; i < list_capacity; i++) {
        if (list->data[i].prev != free_elem_marker && list->data[i].prev != list->data[0].prev) {   // draw prev line
            fprintf(pfile, "\t%d -> %d[color = \"#ff0a0a\", constraint=false];\n", i, list->data[i].prev);
        } else if (list->data[i].prev == list->data[0].prev) {
            fprintf(pfile, "\t%d -> %d[color = \"#8139bd\", constraint=false];\n", i, list->data[i].prev);
        }
    }

    fprintf(pfile, "\th [shape=tripleoctagon,label=\"HEAD\", color = \"yellow\", fillcolor=\"#7293ba\",style=filled  ];\n");
    fprintf(pfile, "\tt [shape=tripleoctagon,label=\"TALE\", color = \"yellow\", fillcolor=\"#7293ba\",style=filled ];\n");
    fprintf(pfile, "\tf [shape=tripleoctagon,label=\"FREE\", color = \"yellow\", fillcolor=\"#7293ba\",style=filled ];\n");
    fprintf(pfile, "\th->t->f[weight = 100, color = \"invis\"];\n");
    fprintf(pfile, "\th->%d[color = \"orange\", constraint=false];\n", list->data[0].next);
    fprintf(pfile, "\tt->%d[color = \"orange\", constraint=false];\n", list->data[0].prev);
    fprintf(pfile, "\tf->%d[color = \"orange\", constraint=false];\n", list->free_element_head);
    fprintf(pfile, "\n}");
    fclose(pfile);


    create_new_graph();   
}

