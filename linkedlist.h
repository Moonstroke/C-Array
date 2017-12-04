#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>


typedef void data;

typedef struct llist LinkedList;

/**
 * Allocates a new linked list.
 *
 * No parameters are needed because the memory for the elements will be allocated
 * upon adding -- that's the very concept of a linked list.
 */
LinkedList *newlinkedlist(void);

/**
 * Frees a linked list, frees its items with given function, if not NULL.
 * Accessing the list after freeing will result in undefined behaviour.
 */
void lfree(LinkedList *self, void (*freeitem)(data*));

/**
 * Returns the length of the linked list, that is the number of its elements.
 */
size_t llen(const LinkedList *self);


/**
 * Adds an element to the linked list before given index (index start at 0).
 *
 * Returns the index of the element, or -1 in case of error (memory allocation failed)
 */
ssize_t ladd(LinkedList *self, ssize_t index, data *item);

/**
 * Appends an element to the end of the linked list.
 *
 * Returns the index of the element or -1 on error.
 */
inline ssize_t lappend(LinkedList *self, data *item) {
	return ladd(self, llen(self), item);
}


/**
 * Retrieves the index'th element of the linked list (from 0).
 */
data *lget(const LinkedList *self, ssize_t index);

/**
 * Updates the index'th element of the list.
 *
 * Returns the former element.
 */
data *lset(LinkedList *self, ssize_t index, data *item);

/**
 * Removes the index'th element of the list.
 *
 * Returns the removed element, of NULL if no element was removed (invalid index)
 */
data *ldrop(LinkedList *self, ssize_t index);


/**
 * Prints a linked list on stdin, the element separated with a comma and a space and
 * enclosed in round brackets.
 * Each element will be printed by the given function, to which it is passed.
 * If the function is NULL, the elements' addresses will be output in printf's "%p" format
 *
 * For example, if the list contains the real numbers 42.3, 6.0, 19.5, and the function
 * prints a float in printf's "%f" format, the output will be:
 *     (42.3, 6.0, 19.5)
 */
void lprintf(const LinkedList *self, void (*printitem)(data*));

#endif /* LINKEDLIST_H */
