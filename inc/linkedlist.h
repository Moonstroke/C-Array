/**
 * \file "linkedlist.h"
 * \author joH1
 * \version 0.1
 *
 * \brief This files contains the definition of the LinkedList structure, which
 *        store elements dynamically.
 *
 * Each element is added on the fly, there is no guarantee that the element will
 * be stored in contiguous space in the memory -- they most certainly will
 * not be, actually.
 *
 * The functions \a ll_new, \a ll_get, \a ll_set, \a ll_add, \a ll_append and
 * \a ll_drop set the variable \a errno to describe their state:
 * - \c 0 if the execution proceeded nominally,
 * - \c ENOMEM if a memory allocation process failed (no more memory available),
 * - \c EINVAL if the value of an argument is invalid for the function,
 * - \c ERANGE if the argument describing an acces index is invalid.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <stdlib.h> /* for NULL */

#include "arrays.h" /* for function attrs, data */



/**
 * \brief The linked list data structure.
 *
 * Defined opaquely for data encapsulation.
 */
typedef struct llist LinkedList;


/**
 * \brief Allocates a new linked list.
 *
 * \note The functions sets \a errno to \c ENOMEM if memory for the list could
 *       not be allocated, in that case the function returns \c NULL.
 *
 * \note No parameters are needed because the memory for the elements will be
 *       allocated on the fly upon adding -- that's the very concept of a linked
 *       list.
 *
 * \return A newly allocated linked list, or \c NULL.
 */
CTOR LinkedList *ll_new(void);


/**
 * \brief Frees a linked list, frees its items with given function, if not
 *        \c NULL.
 *
 * \param[in,out] self     The linked list to free
 * \param[in]     freeitem The function to apply to each element
 *
 * \note Accessing the list after freeing will result in undefined behaviour.
 */
MEMBER void ll_freer(LinkedList *self, void (*freeitem)(data*));

/**
 * \brief Frees a linkedlist, without attempting to deallocate the elements.
 *
 * \param[in,out] self The linked list
 *
 * \sa ll_freer
 */
MEMBER INLINE void ll_free(LinkedList *const self) {
	ll_freer(self, NULL);
}


/**
 * \brief Returns the length of the linked list.
 *
 * \param[in] self The linked list
 *
 * \return The number of elements in the list.
 */
MEMBER unsigned int ll_len(const LinkedList *self) PURE;


/**
 * \brief Retrieves an element of the linked list by its position.
 *
 * \note Sets \a errno to \c ERANGE if \a index is greater than, or equal to the
 *       size of the list, in that case returns \c NULL.
 *
 * \param[in,out] self  The linked list
 * \param[in]     index The index
 *
 * \return The \a index 'th element in the list, or \c NULL if the index is
 *         invalid.
 */
MEMBER data *ll_get(const LinkedList *self, unsigned int index) PURE;

/**
 * \brief Updates an element of the list.
 *
 * \note Sets \a errno to \c ERANGE if \a index is invalid; in that case
 *       returns \c NULL.
 *
 * \param[in,out] self  The linked list
 * \param[in]     index The index where to update the element
 * \param[in]     item  The element to set
 */
MEMBER void ll_set(LinkedList *self, unsigned int index, data *item) NOTNULL(3);


/**
 * \brief Inserts an element to the linked list before given \a index (indices
 *        start at \c 0).
 *
 * \note Sets \a errno to \c ENOMEM if no memory could be allocated for the
 *       element, or \c ERANGE if \a index is invalid. In these cases, returns
 *       \c NULL.
 *
 * \param[in,out] self  The linked list
 * \param[in]     index The index where to add the element
 * \param[in]     item  The item to insert
 * \return The index of the element, or \c -1 in case of error: memory
 *         allocation failed, or the \a index is invalid.
 */
MEMBER int ll_add(LinkedList *self, unsigned int index, data *item) NOTNULL(3);

/**
 * \brief Appends an element to the end of the linked list.
 *
 * \note Sets \a errno to \c ENOMEM if no memory for the element could be
 *       allocated.
 *
 * \param[in,out] self The linked list
 * \param[in]     item The element to add
 *
 * \return The index of the element, or \c -1 on error.
 */
MEMBER INLINE NOTNULL(2) int ll_append(LinkedList *self, data *item) {
	return ll_add(self, ll_len(self), item);
}


/**
 * \brief Removes an element of the list.
 *
 * \note Sets \a errno to \c ERANGE and returns \c NULL if \a index is invalid.
 *
 * \param[in,out] self  The linked list
 * \param[in]     index The index where to delete the element
 *
 * \return The removed element, of NULL if no element was removed (\a i.e.
 *         \a index has an invalid value).
 */
MEMBER data *ll_drop(LinkedList *self, unsigned int index);


#endif /* LINKEDLIST_H */
