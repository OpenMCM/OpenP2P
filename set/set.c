#include <stdlib.h>
#include <stdio.h>

#include "set.h"

set *init_set() {
  set *s = malloc(sizeof(set));
  if(s == NULL) {
    printf("malloc() returned NULL\n");
    exit(1);
  }
  s->size = 0;
  s->head = NULL;
  return s;
}

elem *init_elem(int data) {
  elem *l = malloc(sizeof(elem));
  if(l == NULL) {
    printf("malloc() returned NULL\n");
    exit(1);
  }
  l->prev = NULL;
  l->prev = NULL;
  l->data = data;
  return l;
}

void set_remove_helper(elem *l) {
  if(l->prev != NULL) {
    l->prev->next = l->next;
  }

  if(l->next != NULL) {
    l->next->prev = l->prev;
  }
}

void set_remove(set *s, int data) {
  if(!is_in_set(s, data)) {
    return;
  }

  elem *curr_elem = s->head;
  while(curr_elem != NULL) {
    if(curr_elem->data == data) {
      if(curr_elem == s->head) {
        s->head = curr_elem->next;
      }
      set_remove_helper(curr_elem);

      free(curr_elem);
      s->size -= 1;
      return;
    }

    curr_elem = curr_elem->next;
  }

  return;
}

// A handy debbugging function to make sure no pointers have been corrupted
int iterate(set *s) {
  printf("Begin Iterate\n");
  elem *curr_elem = s->head;

  while(curr_elem != NULL) {
    printf("%lx, data: %d,", (unsigned long)curr_elem, curr_elem->data);
    printf("prev: %lx, next: %lx\n", (unsigned long)curr_elem->prev, (unsigned long)curr_elem->next);
    curr_elem = curr_elem->next;
  }
  printf("End Iterate\n");
  return 0;
}

int is_in_set(set *s, int data) {
  elem *curr_elem = s->head;

  while(curr_elem != NULL) {
    if(curr_elem->data == data) {
      return 1;
    }
    curr_elem = curr_elem->next;
  }
  
  return 0;
}

void set_add_helper(set *s, elem *l) {
  if(s->head == NULL) {
    s->head = l;
    // This line shouldn't be needed, but apparently l->next gets corrupted
    // somewhere. No idea where.
    l->next = NULL;
    return;
  }
  s->head->prev = l;
  l->next = s->head;
  s->head = l;
}

void set_add(set *s, int data) {
  elem *l = init_elem(data);
  set_add_helper(s, l);
  s->size += 1;
}
