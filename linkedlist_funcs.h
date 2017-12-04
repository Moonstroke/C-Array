#ifndef LINKEDLIST_FUNCS_H
#define LINKEDLIST_FUNCS_H

#include "linkedlist.h"

#include <stdbool.h>

/**
 * Frees a linked list and frees its elements with given function.
 */
void lfreer(LinkedList *llist, void (*freeitems)(data*));


/*
 * Removes an element of the linked list
 *
 * Returns TRUE if the element was found -- and removed.
 */
bool lremove(LinkedList *a, const data *item);


#endif /* LINKEDLIST_FUNCS_H */
