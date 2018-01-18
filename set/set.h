typedef struct elem {
  struct elem *prev;
  struct elem *next;
  int data;
} elem;

typedef struct set {
  int size;
  elem *head;
} set;

set *init_set();

elem *init_elem();

void set_remove(set *s, int data);

int is_in_set(set *s, int data);

void set_add(set *s, int data);
