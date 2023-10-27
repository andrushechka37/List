
const int count  = 13;

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