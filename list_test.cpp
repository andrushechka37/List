#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "dump_list.h"


int main(void) {
    FILE * pfile = fopen("log_file.txt", "wb");
    list_struct list = {};
    list_Ctor(&list);
    list_elem_put(&list, 0, 5);
    list_elem_put(&list, 1, 6);
    list_elem_put(&list, 2, 7);
    list_elem_put(&list, 3, 58);
    draw_grath(&list, "list");
    list_elem_del(&list, 3);
    draw_grath(&list, "delete third position");
    list_elem_put(&list, 4, 73);
    draw_grath(&list, "add after 4 position");
    list_elem_del(&list, 1);
    draw_grath(&list, "delete first");
    
    dump_list(&list, pfile);
    dump_list(&list, pfile);
    verificator(&list);
    //grapth_presentation();

    list_Dtor(&list);

}









