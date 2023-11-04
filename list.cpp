#include <stdio.h>
#include <stdlib.h>
#include "list.h"

static int free_cell_num (list_struct * list);
static void free_cell(list_struct * list, int position);

void verificator(list_struct * list) {
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

    // if(list->data == NULL) {                               
    //     printf("data zero ptr");
    //     error = 1;        
    // } 

    if(list->free < 0) {// another check                      // make on defines  
        printf("free below zero");
        error = 1;       
    } 

    if(list->head < 0) {                          
        printf("head below zero");
        error = 1;        
    } 

    if(list->tale < 0) {                          
        printf("tale below zero");
        error = 1;        
    } 



    if (error == 1) {
        exit(-1);
    }
}


static void move_borders_of_list(list_struct * list) {
    list->head = list->data[0].next;
    list->tale = list->data[0].prev;
}

void list_elem_put(list_struct * list, int position, int value) {
    int cur = free_cell_num(list);

    list->data[list->data[position].next].prev = cur;      // prev of the next elem is current

    list->data[cur].prev = position; 
    list->data[cur].value = value;
    list->data[cur].next = list->data[position].next;

    list->data[position].next = cur;         // prev elem next is current

    move_borders_of_list(list);
}

void list_elem_del(list_struct * list, int position) {
    list->data[list->data[position].prev].next = list->data[position].next; // next of prev elem = next of cur elem
    list->data[list->data[position].next].prev = list->data[position].prev; // prev of next elem = prev of cur elem

    free_cell(list, position);

    move_borders_of_list(list);
}

void list_Ctor(list_struct * list) {
    for (int i = 1; i < count; i++) {
        list->data[i].prev = free_elem;
        list->data[i].next = i + 1;
    }

    list->head = 0;
    list->tale = 0;
    list->free = 1;
}

void list_Dtor(list_struct * list) {
    for(int i = 0; i < count; i++) {
        list->data[i].prev  = 0; 
        list->data[i].value = 0; 
        list->data[i].next  = 0; 
    }
}

static int free_cell_num(list_struct * list) {
    if (list->data[list->free].next != 0) {
        int pos = list->free;
        list->free = list->data[list->free].next; 
        return pos;
    } else {
        printf("no more free space");
        exit(-1);
    }
}

static void free_cell(list_struct * list, int position) {
    list->data[position].prev = free_elem;
    list->data[position].value = 0;
    list->data[position].next  = list->free;
    list->free = position;
}