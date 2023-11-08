#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "dump_list.h"
// count gr
// grapth



int main(void) {
    FILE * pfile = fopen("log_file.txt", "wb");
    doubly_linked_list list = {};

    list_ctor(&list);

    list_insert_after(&list, 0, 5);
    list_insert_after(&list, 1, 6);
    list_insert_after(&list, 2, 7);
    list_insert_after(&list, 3, 58);
    draw_grapth(&list, "list");

    list_swap(&list, 6, 2);
    draw_grapth(&list, "swap");
    list_swap(&list, 10, 1);
    draw_grapth(&list, "funny swap");


    list_elem_del(&list, 3);


    list_insert_after(&list, 4, 73);


    // list_elem_del(&list, 1);

    draw_grapth(&list, "delete first");

    list_linearization(&list);
    draw_grapth(&list, "linearization");
    
    dump_list(&list, pfile);
    //verify_list(&list);
    grapth_presentation();

    list_dtor(&list);

}

