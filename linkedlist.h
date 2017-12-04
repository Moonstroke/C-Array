/**
 * \file "linkedlist.h"
 * \author joH1
 * \version 0.1
 *
 * \brief This files contains the definition of the LinkedList structure, which
 *        store elements dynamically.
 *
 * Each element is added on the fly, there is no guarantee that the element will
 * be stored in contiguous space in the memory -- actually, they certainly will
 * not.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>


typedef void data; /**< A more eloquent name for the type of the elements */

/**
 * \brief The linked list data structure.
 *
 * Defined opaquely for data encapsulation.
 */
typedef struct llist LinkedList;


/**
 * \brief Allocates a new linked list.
 *
 * \note No parameters are needed because the memory for the elements will be
 * allocated on the fly upon adding -- that's the very concept of a linked list.
 */
LinkedList *newlinkedlist(void);

/**
 * \brief Frees a linked list, frees its items with given function, if not
 *        \c NULL.
 *
 * \param[in,out] self     The linked list to free
 * \param[in]     freeitem The function to apply to each element
 *
 * \note Accessing the list after freeing will result in undefined behaviour.
 */
void lfree(LinkedList *self, void (*freeitem)(data*));


/**
 * \brief Returns the length of the linked list.
 *
 * \param[in] self The linked list
 *
 * \return The number of elements in the list.
 */
size_t llen(const LinkedList *self);


/**
 * \brief Retrieves an element of the linked list by its position.
 *
 * \param[in,out] self  The linked list
 * \param[in]     index The index
 *
 * \return The \a index 'th element in the list.
 */
data *lget(const LinkedList *self, ssize_t index);

/**
 * \brief Updates an element of the list.
 *
 * \param[in,out] self  The linked list
 * \param[in]     index The index where to update the element
 * \param[in]     item  The element to set
 *
 * \return The former element at \a index 'th position.
 */
data *lset(LinkedList *self, ssize_t index, data *item);


/**
 * \brief Inserts an element to the linked list before given \a index (index
 *        starts at \c 0).
 *
 * \param[in,out] self  The linked list
 * \param[in]     index The index where to add the element
 * \param[in]     item  The item to insert
 * \return The index of the element, or \c -1 in case of error: memory
 *         allocation failed, or the \a index is invalid
 */
ssize_t ladd(LinkedList *self, ssize_t index, data *item);

/**
 * \brief Appends an element to the end of the linked list.
 *
 * \param[in,out] self The linked list
 * \param[in]     item The element to add
 *
 * \return The index of the element, or \c -1 on error.
 */
inline ssize_t lappend(LinkedList *self, data *item) {
	return ladd(self, llen(self), item);
}


/**
 * \brief Removes an element of the list.
 *
 * \param[in,out] self  The linked list
 * \param[in]     index The index where to delete the element
 *
 * \return The removed element, of NULL if no element was removed (\a i.e.
 *         \a index has an invalid value)
 */
data *ldrop(LinkedList *self, ssize_t index);


/**
 * \brief Prints a linked list on \a stdin, each element separated with a comma
 * and a space, enclosed in round brackets.
 *
 * \param[in,out] self      The linked list
 * \param[in]     printitem The function to print each element with
 *
 * \note If \a printitem is \c NULL, the elements' addresses will be output in
 *       \a printf 's \c "%p" format.
 *
 * If the list contains the real numbers \c 42.3, \c 6.0, \c 19.5, and
 * \a printitem prints a \c float in \a printf 's \c "%f" format, the
 * output will be:
 * \verbatim (42.3, 6.0, 19.5) \endverbatim
 */
void lprintf(const LinkedList *self, void (*printitem)(data*));

#endif /* LINKEDLIST_H */
