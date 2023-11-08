#pragma once

const int count       =  13; // TODO: What is 13? Why is this const here?

const int free_elem   =  -1;

struct elem_list { // TODO: why _list? It's not a list, it's a single element!
    int value; // TODO: can I change list element type? What if I want to?
    int prev;
    int next;
};

struct list_struct { // TODO: list_STRUCT? Why STRUCT? If you want to write struct so much, write it like struct list as language suggests
    elem_list * data;
    int free; // TODO: just free? free_list_head?
};

/// @brief Verificator of list
/// @param list struct 
/// @return 0 if there is no issues in list
int verificator(list_struct * list);  // TODO: verbs? verify? Also, there are no markers that show that it's a list verifier, not for arbitrary data, but specifically for lists

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
int swap(list_struct * list, int position1, int position2); // TODO: list_?

/// @brief leads to correspondence of physical and logical adresses of list elements
/// @param list list struct
void linearization(list_struct * list); // TODO: list_?



int list_Ctor(list_struct * list); // TODO: capital letter here? naming style
int list_Dtor(list_struct * list);





//(optional)

// delete ~time~ temporary files 
// /tmp tmnum how to create time files
// delete time files
// /tmp tmnum how to create time files
// aspell
// list tests

// reallock REALLOC no leviosa-


// commands

// list insert after
// revove exit 
// linearization
// логические и физичиёеские адреса BLAH BLAH BLAH use UTF-8
// pop back pop front swap 
// необязательные дапмы

// git size of list
// clear TODO: where
// resize
// swap(only pointers
// reverse
