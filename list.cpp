#include <stdio.h>
#include <stdlib.h>
#include "list.h"
int list_push(list_struct * list, int value) {
    list->data[list->tale].prev = list->tale - 1;
    list->data[list->tale - 1].next = list->tale;
    list->data[list->tale].value = value;
    list->data[list->tale].next = 998;
    list->tale++;
}
int main(void) {
    FILE * pfile = fopen("log_file.txt", "wb");
    list_struct list = {};
    list.data[0].value = 999;
    // for (int i = 1; i < 10; i++) {
    //     list.data[i].value = i;
    //     list.data[i].next = i + 1;
    //     list.data[i].prev = i - 1;
    // }
    // list.head = 5;
    list.tale = 1;
    // list.free = 78;
    list_push(&list, 7);
    list_push(&list, 90);
    

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
        fprintf(pfile, "|_____");
    }
    fprintf(pfile, "|");
    return;
}
void dump_list (list_struct * list, FILE * pfile) {
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
        fprintf(pfile, " %.3d |", (list->data[i]).prev);
    }
    close(pfile);


    fprintf(pfile, "\n\nhead: [%.3d]\n", list->head);
    fprintf(pfile, "tale: [%.3d]\n", list->tale);
    fprintf(pfile, "free: [%.3d]\n", list->free);

}