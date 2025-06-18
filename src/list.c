#include <stdlib.h>
#include <stdio.h>
#include "list.h"

#define INITIAL_SIZE 50
#define GROWTH_FACTOR 2

void init_list(List *list)
{
    list->length = 0;
    list->size = INITIAL_SIZE;
    list->values = malloc(list->size * sizeof(*list->values));

    if (!list->values)
    {
        perror("Could not allocate memory for a dynamic list");
        exit(EXIT_FAILURE);
    }
}

void free_list(List *list) {
    free(list->values);
    list->values = NULL;
    list->length = 0;
    list->size = 0;
}

void add_item(List *list, int item)
{
    if (list->length == list->size) {
        int new_size = list->size * GROWTH_FACTOR;
        int *new_values = realloc(list->values, new_size * sizeof(*list->values));
        if (!new_values)
        {
            perror("Could not reallocate memory for dynamic list");
            exit(EXIT_FAILURE);
        }
        list->values = new_values;
        list->size = new_size;
    }

    list->values[list->length++] = item;
}
