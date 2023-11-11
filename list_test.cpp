#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "dump_list.h"


int main(void) {
    FILE * pfile = fopen("log_file.txt", "w");
    doubly_linked_list list = {};

    list_ctor(&list);

    list_insert_after(&list, 0, 5);
    list_insert_after(&list, 1, 6);
    list_insert_after(&list, 2, 7);
    list_insert_after(&list, 3, 58);

    list_swap(&list, 6, 2);
    //list_visualize(&list, "swap");       // bad
    list_swap(&list, 10, 1);


    list_delete_elem(&list, 3);


    list_insert_after(&list, 4, 73);


    // list_delete_elem(&list, 1);


    list_linearization(&list);
    
    dump_list_txt(&list, pfile);
    //verify_list(&list);
    //unite_visualizations();
    html_dump();

    list_dtor(&list);

}
