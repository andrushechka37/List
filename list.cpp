#include <stdio.h>
#include <stdlib.h>
#include "list.h"
const int count  = 10;

struct elem_list {
    int value;
    int prev;
    int next;
};

struct list_struct {
    elem_list data[count];
    int head;
    int tale;
    int free;
};
void partion(FILE * pfile) {
    fprintf(pfile, "\n           ");
    for (int i = 0; i < count - 1; i++) {
        fprintf(pfile, "|_____");
    }
    return;
}
void dump_list (list_struct * list, FILE * pfile) {
    fprintf(pfile, "index: ");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, "%.3d_|_", i);
    }


    partion(pfile);


    fprintf(pfile, "\ndata: ");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, " %.3d |", (list->data[i]).value);
    }

    partion(pfile);

    fprintf(pfile, "\nnext: ");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, " %.3d |", (list->data[i]).next);
    }

    partion(pfile);

    fprintf(pfile, "\n rev: ");
    for (int i = 0; i < count; i++) {
        fprintf(pfile, " %.3d |", (list->data[i]).prev);
    }
    partion(pfile);


    fprintf(pfile, "\n\nhead: [%.3d]\n", list->head);
    fprintf(pfile, "tale: [%.3d]\n", list->tale);
    fprintf(pfile, "free: [%.3d]\n", list->free);

}

int main(void) {
    FILE * pfile = fopen("log_file.txt", "wb");
    list_struct list = {};
    list.data[0].value = 999;
    for (int i = 1; i < 10; i++) {
        list.data[i].value = i;
        list.data[i].next = i + 1;
        list.data[i].prev = i - 1;
    }
    list.head = 5;
    list.tale = 98;
    list.free = 78;
    dump_list(&list, pfile);

}