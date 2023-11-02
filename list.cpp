#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"



int main(void) {
    FILE * pfile = fopen("log_file.txt", "wb");
    list_struct list = {};
    list_Ctor(&list);
    list_elem_put(&list, 0, 5);
    list_elem_put(&list, 1, 6);
    list_elem_put(&list, 2, 7);
    list_elem_put(&list, 3, 58);
    draw_grath(&list, __func__);
    list_elem_del(&list, 3);
    draw_grath(&list, __func__);
    draw_grath(&list, __func__);
    
    dump_list(&list, pfile);
    dump_list(&list, pfile);
    
    list_Dtor(&list);

}









