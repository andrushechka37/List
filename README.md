# List
## This is a list created on array of structures.
It is a very useful prorgamm that can help you to store integers in right order. List has a lot of functions to work with it.
* insert after element
* delete element
* swap between elements of list
* linearization


Also list has two variations of dump:
* text dump
* graphyz dump united in slides of presentation

## Usage example 

```C
    FILE * pfile = fopen("log_file.txt", "wb");
    list_struct list = {};

    list_Ctor(&list);

    list_insert_after(&list, 0, 5);
    list_insert_after(&list, 1, 6);
    list_insert_after(&list, 2, 7);
    list_insert_after(&list, 3, 58);
    draw_grapth(&list, "list");

    swap(&list, 6, 2);
    draw_grapth(&list, "swap");
    swap(&list, 6, 2);
    draw_grapth(&list, "delete third position");

    list_Dtor(&list);
```

## How to install
1. Clone this project.
2. Rewrite ``` void create_new_grapth(void)``` to generate images in right folder.

## Find a bug?
If you found an issue or would like to submit an improvement to this project, please submit an issue using the ussues tab above.

## Known isssues(Work in progress)
* ```int swap(list_struct * list, int position1, int position2)``` has a lot of ifs and should be fully rewrited
* ```int verificator(list_struct * list)``` should be apgraded by adding new checks.



# Donation
### :exclamation: :exclamation: send me money om my phone number :exclamation: :exclamation:
