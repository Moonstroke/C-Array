/**
 * \file "linkedlist_funcs.h"
 * \author joH1
 * \version 0.1
 *
 *\brief This module contains additional functions for the LinkedList structure.
 *
 */

#ifndef LINKEDLIST_FUNCS_H
#define LINKEDLIST_FUNCS_H


#include <stdbool.h>

#include "arrays.h" /* for function attrs */
#include "linkedlist.h"



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
* \param[in] list The linked list
* \param[in] value The value to check against
* \param[in] equals The comparator function
*
* \return The first element to satisfy the condition, or \c NULL.
 */
MEMBER data *ll_cond(const LinkedList *list, const data *value, bool (*equals)(const data*, const data*)) PURE;


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
 * \param[in,out] list    The linked list
 * \param[in]     item    The item to find and remove
 * \param[in]     eq_func The comparison function
 *
 * \return The removed element, or \c NULL if none matched.
 */
MEMBER data *ll_remove(LinkedList *list, const data *item, bool (*eq_func)(const data*, const data*));


/**
 * \brief Applies a function to each element of the structure.
 *
 * \param[in,out] list  The linked list
 * \param[in]     apply The function to apply
 */
MEMBER void ll_each(LinkedList *list, void (*apply)(data*)) NOTNULL(2);


/**
 * \brief Prints a linked list on \a stdin, each element separated with a comma
 * and a space, enclosed in round brackets.
 *
 * \param[in] list      The linked list
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
MEMBER void ll_printf(const LinkedList *list, void (*printitem)(const data*));


#endif /* LINKEDLIST_FUNCS_H */
