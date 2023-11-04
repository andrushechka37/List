#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "dump_list.h"


int main(void) {
    FILE * pfile = fopen("log_file.txt", "wb");
    list_struct list = {};

    list_Ctor(&list);

    list_insert_after(&list, 0, 5);
    list_insert_after(&list, 1, 6);
    list_insert_after(&list, 2, 7);
    list_insert_after(&list, 3, 58);

    swap(&list, 6, 2);
    draw_grapth(&list, "swap");
    swap(&list, 6, 2);
    draw_grapth(&list, "delete third position");


    list_elem_del(&list, 3);


    list_insert_after(&list, 4, 73);


    list_elem_del(&list, 1);

    draw_grapth(&list, "delete first");

    linearization(&list);
    draw_grapth(&list, "linearization");
    
    dump_list(&list, pfile);
    //verificator(&list);
    grapth_presentation();

    list_Dtor(&list);

}
