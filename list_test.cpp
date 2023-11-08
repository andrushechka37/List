#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "dump_list.h"


int main(void) {
    FILE * pfile = fopen("log_file.txt", "wb");
    list_struct list = {};

    list_Ctor(&list);

    list_insert_after(&list, 0, 5);
    list_insert_after(&list, 1, 6);
    list_insert_after(&list, 2, 7);
    list_insert_after(&list, 3, 58);
    draw_grapth(&list, "list");

    swap(&list, 6, 2);
    draw_grapth(&list, "swap");
    swap(&list, 6, 2);
    draw_grapth(&list, "delete third position");


    list_elem_del(&list, 3);


    list_insert_after(&list, 4, 73);


    list_elem_del(&list, 1);

    draw_grapth(&list, "delete first");

    linearization(&list);
    draw_grapth(&list, "linearization");
    
    dump_list(&list, pfile);
    //verificator(&list);
    grapth_presentation();

    list_Dtor(&list);

}


///////////




static int get_vacant_cell (list_struct * list);
static void add_vacant_cell(list_struct * list, int position);

int verificator(list_struct * list) {
    bool error = 0;
    for (int i = 0; i < count; i++) {
        if (list->data[list->data[i].prev].next != i && list->data[i].prev != free_elem) {
            printf("%d %d", list->data[list->data[i].prev].next, i);
            printf("next of previous elem is %d element is %d", list->data[list->data[i].prev].next, i);
            error = 1;
        }
        if (list->data[list->data[i].next].prev != i && list->data[i].prev != free_elem) {
            printf("previous of next element is %d element is %d", list->data[list->data[i].next].prev, i);
            error = 1;
        }
    }

    if(list->data == NULL) {                               
        printf("data zero ptr");
        error = 1;        
    } 

    if(list->free < 0) { 
        printf("free below zero");
        error = 1;       
    } 

    if(list->free > count) { 
        printf("free is out of range    %d    \n", list->free);
        error = 1;       
    } 

    if (error == 1) {
        draw_grapth(list, "error, check console output");
        exit(-1);
    }

    return 0;
}



int list_insert_after(list_struct * list, int position, int value) {
    int cur = get_vacant_cell(list);

    list->data[list->data[position].next].prev = cur;      // prev of the next elem is current

    list->data[cur].prev = position; 
    list->data[cur].value = value;
    list->data[cur].next = list->data[position].next;

    list->data[position].next = cur;
    return 0;         // prev elem next is current

}

int list_elem_del(list_struct * list, int position) {
    list->data[list->data[position].prev].next = list->data[position].next; // next of prev elem = next of cur elem
    list->data[list->data[position].next].prev = list->data[position].prev; // prev of next elem = prev of cur elem

    add_vacant_cell(list, position);
    return 0;

}

int list_Ctor(list_struct * list) {
    list->data = (elem_list *) calloc(count, sizeof(elem_list));
    for (int i = 1; i < count; i++) {
        list->data[i].prev = free_elem;
        list->data[i].next = i + 1;
    }

    list->free = 1;
    return 0;
}

int list_Dtor(list_struct * list) {
    for(int i = 0; i < count; i++) {
        list->data[i].prev  = 0; 
        list->data[i].value = 0; 
        list->data[i].next  = 0; 
    }
    free(list->data);
    return 0;
}

static int get_vacant_cell(list_struct * list) {
    if (list->data[list->free].next != 0) {
        int pos = list->free;
        list->free = list->data[list->free].next; 
        return pos;
    } else {
        printf("no more free space");
        exit(-1);
    }
}

static void add_vacant_cell(list_struct * list, int position) {
    list->data[position].prev = free_elem;
    list->data[position].value = 0;
    list->data[position].next  = list->free;
    list->free = position;
}

int swap(list_struct * list, int position1, int position2) {  // in work

    if((list->data[position1].prev == free_elem && list->data[position2].prev == free_elem) || position1 == 0 || position2 == 0) {
        return 0;
    }
    if (list->data[position1].prev == free_elem) {
        list->data[list->data[position2].prev].next = position1;
        list->data[list->data[position2].next].prev = position1;

        list->data[position1].prev = list->data[position2].prev;
        list->data[position1].value = list->data[position2].value;

        int k = list->data[position1].next;

        list->data[position1].next = list->data[position2].next;

        list->data[position2].prev = free_elem;
        list->data[position2].value = 0;
        list->data[position2].next = k;

        if(list->free == position1) {
            list->free = position2;
        }
        return 0;
    }

    if (list->data[position2].prev == free_elem) {
        list->data[list->data[position1].prev].next = position2;
        list->data[list->data[position1].next].prev = position2;

        list->data[position2].prev = list->data[position1].prev;
        list->data[position2].value = list->data[position1].value;

        int k = list->data[position2].next;

        list->data[position2].next = list->data[position1].next;

        list->data[position1].prev = free_elem;
        list->data[position1].value = 0;
        list->data[position1].next = k;

        if(list->free == position2) {
            list->free = position1;
        }
        return 0;
    }
    int next = list->data[position1].next;
    int prev = list->data[position1].prev;
    int prev_elem1 = list->data[position1].prev;
    int prev_elem2 = list->data[position2].prev;

    int next_elem1 = list->data[position1].next;
    int next_elem2 = list->data[position2].next;
    list->data[prev_elem1].next = position2;
    list->data[prev_elem2].next = position1;
    list->data[next_elem1].prev = position2;
    list->data[next_elem2].prev = position1;





    if (abs((position1 - position2)) == 1) {  // 1 2
        if (next_elem1 == position2) {
            list->data[position1].next = next_elem2;
            list->data[position2].prev = prev_elem1;
            list->data[position1].prev = position2;
            list->data[position2].next = position1;
        } else {
            list->data[position1].next = position2;  // 2 1
            list->data[position1].prev = prev_elem2;
            printf("fjn");
            list->data[position2].prev = position1;
            list->data[position2].next = next_elem1;
        }
    } else {
        list->data[position1].next = list->data[position2].next;
        list->data[position1].prev = list->data[position2].prev;
        list->data[position2].next = next;
        list->data[position2].prev = prev;
    }


    return 0;

}

void linearization(list_struct * list) {
    int count = 1;
    for (int i = 0; i < 10; i++) { 
        if (list->data[i].next != count) {
            //draw_grapth(list, "list");
            printf("%d\n\n\n\n", count);
            swap(list, count, list->data[i].next);
        }
        count++;
    }
}



void grapth_presentation(void) {
    char command[command_len] = "open /opt/local/bin/sxiv ";
    char file[] = " /Users/anzhiday/Documents/list/grapths/grath";
    int counter = atoi(count_gr);
    for (int i = 1; i < counter; i++) {
        char number[6] = "";
        snprintf(number, 6,  "%d.png", i);
        strcat(command, file);
        strcat(command, number);
    }
    printf("%s", command);
    system(command);
}

void list_cell_open(FILE * pfile) {
    fprintf(pfile, "\n     ");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, "______");
    }
    fprintf(pfile, "\n");
    return;
}

void list_cell_close(FILE * pfile) {
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
    list_cell_open(pfile);
    fprintf(pfile, "  ip:| ");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, "%.3d | ", i);
    }
    list_cell_close(pfile);



    fprintf(pfile, "\ndata:|");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, " %.3d |", (list->data[i]).value);
    }

    list_cell_close(pfile);

    fprintf(pfile, "\nnext:|");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, " %.3d |", (list->data[i]).next);
    }

    list_cell_close(pfile);

    fprintf(pfile, "\nprev:|");
    for (int i = 0; i < count; i++) {
        if((list->data[i]).prev == free_elem) {
            fprintf(pfile, " fre |");
        } else {
            fprintf(pfile, " %.3d |", (list->data[i]).prev);
        }
    }
    list_cell_close(pfile);


    fprintf(pfile, "\n\nhead: [%.3d]\n", list->data[0].next);
    fprintf(pfile, "tale: [%.3d]\n", list->data[0].prev);
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


void draw_grapth(list_struct * list, const char * func) {
    FILE * pfile = fopen("grath.dot", "wb");
    fprintf(pfile, "digraph structs {\n");
    fprintf(pfile, "\trankdir=LR;\n");
    fprintf(pfile, "\tgraph [bgcolor=\"#31353b\"]\n");
    fprintf(pfile, "\tnode[color=\"black\",fontsize=14];\n");
    fprintf(pfile, "\tedge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n\n\n");

    fprintf(pfile, "\t50 [shape=note,style=filled, fillcolor=\"#fdf39b\", label=\"%s\", fontcolor = \"black\", fontsize = 20];\n", func);

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
    fprintf(pfile, "%d[weight = 100, color = \"invis\"];\n", count - 1);


    for(int i = 0; i < count - 1; i++) {
        if (list->data[i].prev == free_elem) {     // draw next line
            fprintf(pfile, "\t%d->%d[color = \"#22f230\", constraint=false];\n", i, list->data[i].next);
        } else if (list->data[i].next == 0) {
            fprintf(pfile, "\t%d->%d[color = \"#8139bd\", constraint=false];\n", i, list->data[i].next);
        } else {
            fprintf(pfile, "\t%d->%d[color = \"#0ae7ff\", constraint=false];\n", i, list->data[i].next);
        }
    }
    for (int i = 0; i < count; i++) {
        if (list->data[i].prev != free_elem && list->data[i].prev != list->data[0].prev) {   // draw prev line
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
    fprintf(pfile, "\tf->%d[color = \"orange\", constraint=false];\n", list->free);
    fprintf(pfile, "\n}");
    fclose(pfile);


    create_new_grapth();   
}

