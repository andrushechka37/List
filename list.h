#pragma once

const int count = 13; // this const uses not only in tests think more!!!!!!!!!!!!!
const int free_elem   =  -1;

struct list_element {
    int value; // TODO: can I change list element type? What if I want to? - NO :(
    int prev;
    int next;
};

struct doubly_linked_list {
    list_element * data;
    int free_element_head;
};

/// @brief Verificator of list
/// @param list struct 
/// @return 0 if there is no issues in list
bool verify_list(doubly_linked_list * list);

/// @brief inserts after the element of list
/// @param list list struct
/// @param position after that position insertion
/// @param value value has been inserted
int list_insert_after(doubly_linked_list * list, int position, int value);

/// @brief delete element of list
/// @param list list struct
/// @param position position of deleted element
int list_elem_del(doubly_linked_list * list, int position);


/// @brief swaps two argument in given posotions
/// @param list list struct
/// @param position1 first position
/// @param position2 second position
/// @note there are a lot of ifs, should be rewrited
int list_swap(doubly_linked_list * list, int position1, int position2);

/// @brief leads to correspondence of physical and logical adresses of list elements
/// @param list list struct
void list_linearization(doubly_linked_list * list); 



int list_ctor(doubly_linked_list * list);
int list_dtor(doubly_linked_list * list);





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
