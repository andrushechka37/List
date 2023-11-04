#pragma once
const int count       = 13;
const int free_elem   =  -1;

struct elem_list {
    int value;
    int prev;
    int next;
};

struct list_struct {
    elem_list * data;
    int head;
    int tale;
    int free;
};

void verificator(list_struct * list); 

void list_elem_put(list_struct * list, int position, int value);
void list_elem_del(list_struct * list, int position);

void list_Ctor(list_struct * list);
void list_Dtor(list_struct * list);



//(optional)

// delete time files
// /tmp tmnum how to create time files
// delete time files
// /tmp tmnum how to create time files
// aspell
// list tests


// remove tale and header


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