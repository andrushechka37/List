
const int count       = 13;
const int free_elem   =  -1;
struct elem_list {
    int value;
    int prev;
    int next;
};

struct list_struct {
    elem_list data[count];
    int head;
    int tale;
    int free;
};


void open(FILE * pfile);
void close(FILE * pfile);
void dump_list (list_struct * list, FILE * pfile);

void create_new_grapth(void);
void draw_grath(list_struct * list, const char * func);

int free_cell_num (list_struct * list);
void free_cell(list_struct * list, int position);

void list_elem_put(list_struct * list, int position, int value);
void list_elem_del(list_struct * list, int position);

void list_Ctor(list_struct * list);
void list_Dtor(list_struct * list);