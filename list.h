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

/// @brief Verificator of list 
/// @param list struct 
/// @return 0 if there is no issues in list
int verificator(list_struct * list); 

/// @brief inserts after the element of list
/// @param list list struct
/// @param position after that position insertion
/// @param value value has been inserted
int list_insert_after(list_struct * list, int position, int value);

/// @brief delete element of list
/// @param list list struct
/// @param position position of deleted element
int list_elem_del(list_struct * list, int position);


/// @brief swaps two argument in given posotions
/// @param list list struct
/// @param position1 first position
/// @param position2 second position
/// @note there are a lot of ifs, should be rewrited
int swap(list_struct * list, int position1, int position2);

/// @brief leads to correspondence of physical and logical adresses of list elements
/// @param list list struct
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