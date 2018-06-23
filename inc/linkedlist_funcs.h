/**
 * \file "linkedlist_funcs.h"
 * \author joH1
 * \version 0.1
 *
 *\brief This module contains additional functions for the LinkedList structure.
 *
 */

#ifndef CODS_LINKEDLIST_FUNCS_H
#define CODS_LINKEDLIST_FUNCS_H


#include <stdbool.h>

#include "linkedlist.h"



/**
 * \brief Applies a function to each element of the structure.
 *
 * \param[in,out] llist  The linked list
 * \param[in]     apply The function to apply
 */
CODS_MEMBER void ll_each(LinkedList *llist, void (*apply)(data_t*))
CODS_NOTNULL(2);


/**
 * \brief Replaces an element of the list.
 *
 * \note Sets \a errno to \c ERANGE if \a index is invalid.
 *
 * \param[in,out] llist    The linked list
 * \param[in]     index   The index at which to update the element
 * \param[in]     newitem The new element to set
 *
 * \return The former element found at index \a index, or \c NULL if the index
 *         is invalid.
 */
CODS_MEMBER data_t *ll_swap(LinkedList *llist, size_t index, data_t *newitem)
CODS_NODISCARD CODS_NOTNULL(3);


/**
 * \brief Retrieves an element of the linked list that compares equal to a value
 *        through given comparison function.
 *
 * Each element of the list is passed to the comparator function along with the
 * value, the first element that returns \c true is then returned.
 *
 * \note If \a equals is \c NULL, the elements' addresses are compared.
 *
 * \note It is safe to pass \a value as \c NULL, as long as \a equals is not
 *       \c NULL in the same time; in that case, \a errno is set to \c EINVAL
 *       and the function returns \c NULL immediately.
 *
 * \param[in] llist The linked list
 * \param[in] value The value to check against
 * \param[in] equals The comparator function
 *
 * \return The first element to satisfy the condition, or \c NULL.
 */
CODS_MEMBER
data_t *ll_cond(const LinkedList *llist, const data_t *value,
                bool (*equals)(const data_t*, const data_t*)) CODS_PURE;


/**
 * \brief Removes an element of the linked list, found by comparing each element
 *        with a given value and a specified comparision function.
 *
 * \note If \a eq_func is \c NULL, the default behaviour is to compare the
 *       addresses of the elements.
 *
 * \note If more than one element matches, only the first in the order of the
 *       list is returned.
 *
 * \note This function sets \a errno to \c EINVAL if the item is not found.
 *
 * \param[in,out] llist    The linked list
 * \param[in]     item    The item to find and remove
 * \param[in]     eq_func The comparison function
 *
 * \return The removed element, or \c NULL if none matched.
 */
CODS_MEMBER data_t *ll_remove(LinkedList *llist, const data_t *item,
                              bool (*eq_func)(const data_t*, const data_t*));


/**
 * \brief Prints a linked list on \a stdin, each element separated with a comma
 * and a space, enclosed in round brackets.
 *
 * \param[in] llist      The linked list
 * \param[in] printitem The function to print each element with
 *
 * \note If \a printitem is \c NULL, the elements' addresses will be output in
 *       \a printf 's \c "%p" format.
 *
 * If the list contains the real numbers \c 42.3, \c 6.0, \c 19.5, and
 * \a printitem prints a \c float in \a printf 's \c "%f" format, the
 * output will be:
 * \verbatim (42.3, 6.0, 19.5) \endverbatim
 */
CODS_MEMBER void ll_printf(const LinkedList *llist,
                           void (*printitem)(const data_t*));


#endif /* LINKEDLIST_FUNCS_H */
