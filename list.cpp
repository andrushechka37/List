#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "dump_list.h"
#include <math.h>

static int get_free_cell (list_struct * list);
static void add_free_cell(list_struct * list, int position);

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
    int cur = get_free_cell(list);

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

    add_free_cell(list, position);
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

static int get_free_cell(list_struct * list) {
    if (list->data[list->free].next != 0) {
        int pos = list->free;
        list->free = list->data[list->free].next; 
        return pos;
    } else {
        printf("no more free space");
        exit(-1);
    }
}

static void add_free_cell(list_struct * list, int position) {
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
