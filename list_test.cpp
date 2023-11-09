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
    draw_graph(&list, "list");

    list_swap(&list, 6, 2);
    draw_graph(&list, "swap");
    list_swap(&list, 10, 1);
    draw_graph(&list, "funny swap");


    list_elem_del(&list, 3);


    list_insert_after(&list, 4, 73);


    // list_elem_del(&list, 1);

    draw_graph(&list, "delete first");

    list_linearization(&list);
    draw_graph(&list, "linearization");
    
    dump_list(&list, pfile);
    //verify_list(&list);
    //graph_presentation();

    list_dtor(&list);

}
