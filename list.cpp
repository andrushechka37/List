#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "dump_list.h"
#include <math.h>




static int  get_vacant_cell(doubly_linked_list * list);
static void add_vacant_cell(doubly_linked_list * list, int position);

bool verify_list(doubly_linked_list * list) {
    bool error = 0;

    if (list->data == NULL) {  
        printf("data zero ptr");
        error = 1;
        return 1;     
    } 

    for (int i = 0; i < list_capacity; i++) {
        if (list->data[list->data[i].prev].next != i && list->data[i].prev != free_elem_marker) {
            printf("%d %d", list->data[list->data[i].prev].next, i);
            printf("next of previous elem is %d element is %d", list->data[list->data[i].prev].next, i);
            return 1; 
        }
        if (list->data[list->data[i].next].prev != i && list->data[i].prev != free_elem_marker) {
            printf("previous of next element is %d element is %d", list->data[list->data[i].next].prev, i);
            return 1; 
        }
    }


    if(list->free_element_head < 0) { 
        printf("free below zero");
        error = 1;       
    } 

    if(list->free_element_head > list_capacity) { 
        printf("free is out of range    %d    \n", list->free_element_head);
        error = 1;       
    } 

    if (list->data[list->free_element_head].next == 0) {
        printf("no more free space");
        error = 1;
    }

    if (error == 1) {
        list_visualize(list, "error, check console output");
        return 1;
    }

    return 0;
}



int list_insert_after(doubly_linked_list * list, int position, int value) {

    int cur = get_vacant_cell(list);

    list->data[list->data[position].next].prev = cur;      // prev of the next elem is current

    list->data[cur].prev = position; 
    list->data[cur].value = value;
    list->data[cur].next = list->data[position].next;

    list->data[position].next = cur;

    char comment[comment_len] = "";
    snprintf(comment, comment_len,  "insert after %d position, inserted value is %d", position, value);
    list_visualize(list, comment);
    return 0;         // prev elem next is current

}

int list_delete_elem(doubly_linked_list * list, int position) {  // i was thinking of naming style like list_insert_after
    // TODO: check if element is free - done in verificator      // list_delete_chosen sounds bad? or list_delete_current?
                                                                 // but current bad i think.             
    list->data[list->data[position].prev].next = list->data[position].next; // next of prev elem = next of cur elem
    list->data[list->data[position].next].prev = list->data[position].prev; // prev of next elem = prev of cur elem

    add_vacant_cell(list, position);
    return 0;

}
int get_head(doubly_linked_list * list) {
    return list->data[0].next;
}

int list_ctor(doubly_linked_list * list) {
    list->data = (list_element *) calloc(list_capacity, sizeof(list_element));
    for (int i = 1; i < list_capacity; i++) {
        list->data[i].prev = free_elem_marker;
        list->data[i].next = i + 1;
    }

    list->free_element_head = 1;
    return 0;
}

int list_dtor(doubly_linked_list * list) {
    for(int i = 0; i < list_capacity; i++) {
        list->data[i].prev  = 0; 
        list->data[i].value = 0; 
        list->data[i].next  = 0; 
    }
    free(list->data);
    return 0;
}

static int get_vacant_cell(doubly_linked_list * list) {
    int position = list->free_element_head;
    list->free_element_head = list->data[list->free_element_head].next; 
    return position;
}

static void add_vacant_cell(doubly_linked_list * list, int position) {
    list->data[position].prev = free_elem_marker;
    list->data[position].value = 0;
    list->data[position].next  = list->free_element_head;
    list->free_element_head = position;
}

// TODO: I'm gonna pretend I didn't see this - thank you
int list_swap(doubly_linked_list * list, int position1, int position2) {  // in work

    if((list->data[position1].prev == free_elem_marker && list->data[position2].prev == free_elem_marker) || position1 == 0 || position2 == 0) {
        return 0;
    }
    if (list->data[position1].prev == free_elem_marker) {
        list->data[list->data[position2].prev].next = position1;
        list->data[list->data[position2].next].prev = position1;

        list->data[position1].prev = list->data[position2].prev;
        list->data[position1].value = list->data[position2].value;

        int k = list->data[position1].next;

        list->data[position1].next = list->data[position2].next;

        list->data[position2].prev = free_elem_marker;
        list->data[position2].value = 0;
        list->data[position2].next = k;

        if(list->free_element_head == position1) {
            list->free_element_head = position2;
        }
        return 0;
    }

    if (list->data[position2].prev == free_elem_marker) {
        list->data[list->data[position1].prev].next = position2;
        list->data[list->data[position1].next].prev = position2;

        list->data[position2].prev = list->data[position1].prev;
        list->data[position2].value = list->data[position1].value;

        int k = list->data[position2].next;

        list->data[position2].next = list->data[position1].next;

        list->data[position1].prev = free_elem_marker;
        list->data[position1].value = 0;
        list->data[position1].next = k;

        if(list->free_element_head == position2) {
            list->free_element_head = position1;
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

void list_linearization(doubly_linked_list * list) {
    int physical_address = 1;
    for (int i = 0; i < list_capacity; i++) {          // TODO: 10????????????????---fixed, it was temporary test
        if (list->data[i].next != physical_address) {   // also "count" renamed and now it is physical_address
            list_swap(list, physical_address, list->data[i].next);
        }
        physical_address++;
    }
}
