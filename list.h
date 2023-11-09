#pragma once


// i am thinking of a better name for this macros, but now it is "verify"  :(
#define verify(list)               \
if (verify_list(&list) != 0) {     \
    return -1;                     \
}


const int list_capacity = 13; // I was thinking about removing this constant from this header, but now
                              // it is using in all cpps so i am not sure, if it is should be removed or not
                              // this question is in work!


const int free_elem_marker =  -1; // i am thinking of better name, but current is not as terrible as previous

struct list_element {
    int value; // TODO: can I change list element type? What if I want to? - NO :(
    int prev;
    int next;
};

struct doubly_linked_list {
    list_element * data;
    int free_element_head;
};

// DO NOT READ DOCUMENTATION, IT IS AWFUL, I KNOW, IT IS IN PROGRESS

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
int list_delete_elem(doubly_linked_list * list, int position);


/// @brief swaps two argument in given positions
/// @param list list struct
/// @param position1 first position
/// @param position2 second position
/// @note there are a lot of ifs, should be rewritten
int list_swap(doubly_linked_list * list, int position1, int position2);

/// @brief leads to correspondence of physical and logical addresses of list elements
/// @param list list struct
void list_linearization(doubly_linked_list * list); 



int list_ctor(doubly_linked_list * list);
int list_dtor(doubly_linked_list * list);




// list of TODOs:
//(optional)

// delete ~time~ temporary files 
// /tmp tmnum how to create time files
// delete time files
// /tmp tmnum how to create time files
// aspell
// list tests

// realloc REALLOC no leviosa-


// commands

// list insert after
// remove exit 
// linearization
// logical and physical addresses
// pop back pop front swap 
// optional dumps

// git size of list
// clear TODO: where
// resize
// swap(only pointers)
// reverse
