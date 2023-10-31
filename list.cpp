#include <stdio.h>
#include <stdlib.h>
#include "list.h"
 // letters to grath commit
 // different comours for free
 // shapes
void draw_grath(list_struct * list) {
    FILE * pfile = fopen("grath.dot", "wb");
    fprintf(pfile, "digraph structs {\n");
    fprintf(pfile, "\trankdir=LR;\n");
    fprintf(pfile, "\tgraph [bgcolor=\"#31353b\"]\n");
    fprintf(pfile, "\tnode[color=\"black\",fontsize=14];\n");
    fprintf(pfile, "\tedge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n\n\n");

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


    for(int i = 0; i < count - 1; i++) {
        if (list->data[i].prev == free_elem) {
            fprintf(pfile, "\t%d->%d[color = \"#22f230\"];\n", i, list->data[i].next);
        } else {
            fprintf(pfile, "\t%d->%d[color = \"#0ae7ff\"];\n", i, list->data[i].next);
        }
    }
    for (int i = 0; i < count; i++) {
        if (list->data[i].prev != free_elem) {
            fprintf(pfile, "\t %d -> %d[color = \"#ff0a0a\"];\n", i, list->data[i].prev);
        }
    }

    fprintf(pfile, "\th [shape=tripleoctagon,label=\"HEAD\", color = \"yellow\", fillcolor=\"#7293ba\",style=filled  ];\n");
    fprintf(pfile, "\tt [shape=tripleoctagon,label=\"TALE\", color = \"yellow\", fillcolor=\"#7293ba\",style=filled ];\n");
    fprintf(pfile, "\tf [shape=tripleoctagon,label=\"FREE\", color = \"yellow\", fillcolor=\"#7293ba\",style=filled ];\n");
    fprintf(pfile, "\th->%d[color = \"orange\"];\n", list->head);
    fprintf(pfile, "\tt->%d[color = \"orange\"];\n", list->tale);
    fprintf(pfile, "\tf->%d[color = \"orange\"];\n", list->free);
    fprintf(pfile, "\n}");


    //system(" dot -Tpng /Users/anzhiday/Documents/list/grath.dot  -o /Users/anzhiday/Documents/list/grath/file.png");

    
    
}
int get_free_cell (list_struct * list) {
    if (list->data[list->free].next != 0) {
        int pos = list->free;
        list->free = list->data[list->free].next; 
        return pos;
    } else {
        printf("no more free space");
        exit(-1);
    }
}
void free_cell(list_struct * list, int position) {
    list->data[position].prev  = free_elem;
    list->data[position].value = 0;
    list->data[position].next  = list->free;
    list->free = position;
}

// void full_poison(list_struct * list, int position) {
//     list->data[position].prev  = poizon;
//     list->data[position].value = poizon;
//     list->data[position].next  = poizon;
// }
void list_elem_put(list_struct * list, int position, int value) {   // may be copipast, think more
    if (position == list->tale && position != 0) {
        list->tale = get_free_cell(list);                          // move tale  
        list->data[position].next = list->tale;                     // prev elem next is current

        list->data[list->tale].prev  = position; 
        list->data[list->tale].value = value;
        //list->data[list->tale].next  = poizon;
    } else if (position != 0) {
        int cur = list->data[position].next = get_free_cell(list);  // current is first free     
        list->data[cur].prev = position;                
        list->data[cur].value = value;
        list->data[cur].next = list->data[position].next;
        list->data[position].next = cur;
    } else {
        int cur = get_free_cell(list);
        list->data[cur].prev = 0;                
        list->data[cur].value = value;
        //list->data[cur].next = poizon;
    }
}
void list_elem_del(list_struct * list, int position) { // add adding a free cell
    if (position == list->tale) {
        list->tale = list->data[position].prev;
        //list->data[list->tale].next = poizon;
        free_cell(list, position);
    } else if (position == list->head) {
        list->head = list->data[position].next;
        //list->data[list->head].prev = poizon;
        free_cell(list, position);
    } else {
        list->data[list->data[position].prev].next = list->data[position].next; // next of prev elem = next of cur elem
        list->data[list->data[position].next].prev = list->data[position].prev; // prev of next elem = prev of cur elem
    
        free_cell(list, position);
    }
    


}

void list_Ctor(list_struct * list) {
    list->head = 1;
    for (int i = 1; i < count; i++) {
        list->data[i].prev = free_elem;
        list->data[i].next = i + 1;
    }
    // list->data[count - 1].next = poizon;
    // full_poison(list, 0);
    list->head = 0;
    list->tale = 0;
    list->free = 1;
}
int main(void) {
    FILE * pfile = fopen("log_file.txt", "wb");
    list_struct list = {};
    list_Ctor(&list);
    list_elem_put(&list, 0, 5);
    list_elem_put(&list, 1, 6);
    list_elem_put(&list, 2, 7);
    list_elem_put(&list, 3, 58);
    list.head = 2;
    list_elem_del(&list, 3);
    draw_grath(&list);
    
    dump_list(&list, pfile);
    list_elem_del(&list, 3);
    dump_list(&list, pfile);

}










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