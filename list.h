#pragma once

const int count       =  13;
const int free_elem   =  -1;

struct elem_list {
    int value;
    int prev;
    int next;
};

struct list_struct {
    elem_list * data;
    int free;
};

int verificator(list_struct * list); 

int list_insert_after(list_struct * list, int position, int value);
int list_elem_del(list_struct * list, int position);

int swap(list_struct * list, int position1, int position2);

void linearization(list_struct * list);

int list_Ctor(list_struct * list);
int list_Dtor(list_struct * list);





//(optional)

// delete time files
// /tmp tmnum how to create time files
// delete time files
// /tmp tmnum how to create time files
// aspell
// list tests

// reallock


// commands

// list insert after
// revove exit 
// linearization
// логические и физичиёеские адреса
// pop back pop front swap 
// необязательные дапмы

// git sixe of list
// clear
// resize
// swap(only pointers
// reverse