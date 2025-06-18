#ifndef LIST_H
#define LIST_H

typedef struct List {
    int *values;
    int size;
    int length;
} List;

void init_list(List *list);

void free_list(List *list);

void add_item(List *list, int item);

#endif
