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

    draw_grapth(&list, "list");
    //swap(&list, 2, 1);
    draw_grapth(&list, "swap");

    list_elem_del(&list, 3);

    draw_grapth(&list, "delete third position");

    list_insert_after(&list, 4, 73);

    draw_grapth(&list, "add after 4 position");

    list_elem_del(&list, 1);

    draw_grapth(&list, "delete first");
    
    dump_list(&list, pfile);
    verificator(&list);
    //grapth_presentation();

    list_Dtor(&list);

}
