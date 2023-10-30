#include <stdio.h>
#include <stdlib.h>
#include "list.h"


int give_free_cell (list_struct * list) {
    if (list->data[list->free].next != poizon) {
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

void full_poison(list_struct * list, int position) {
    list->data[position].prev  = poizon;
    list->data[position].value = poizon;
    list->data[position].next  = poizon;
}
void list_elem_put(list_struct * list, int position, int value) {   // may be copipast, think more
    if (position == list->tale && position != 0) {
        list->tale = give_free_cell(list);                          // move tale  
        list->data[position].next = list->tale;                     // prev elem next is current

        list->data[list->tale].prev  = position; 
        list->data[list->tale].value = value;
        list->data[list->tale].next  = poizon;
    } else if (position != 0) {
        int cur = list->data[position].next = give_free_cell(list);  // current is first free     
        list->data[cur].prev = position;                
        list->data[cur].value = value;
        list->data[cur].next = list->data[position].next;
        list->data[position].next = cur;
    } else {
        int cur = give_free_cell(list);
        list->data[cur].prev = 0;                
        list->data[cur].value = value;
        list->data[cur].next = poizon;
    }
}
void list_elem_del(list_struct * list, int position) { // add adding a free cell
    if (position == list->tale) {
        list->tale = list->data[position].prev;
        list->data[list->tale].next = poizon;
        free_cell(list, position);
    } else if (position == list->head) {
        list->head = list->data[position].next;
        list->data[list->head].prev = poizon;
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
    list->data[count - 1].next = poizon;
    full_poison(list, 0);
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
        if ((list->data[i]).value == poizon) {
            fprintf(pfile, " pzn |");
        } else {
            fprintf(pfile, " %.3d |", (list->data[i]).value);
        }
    }

    close(pfile);

    fprintf(pfile, "\nnext:|");
    for (int i = 0; i < count; i++) {
        if ((list->data[i]).next == poizon) {
            fprintf(pfile, " pzn |");
        } else {
            fprintf(pfile, " %.3d |", (list->data[i]).next);
        }
    }

    close(pfile);

    fprintf(pfile, "\nprev:|");
    for (int i = 0; i < count; i++) {
        if ((list->data[i]).prev == poizon) {
            fprintf(pfile, " pzn |");
        } else if((list->data[i]).prev == free_elem) {
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