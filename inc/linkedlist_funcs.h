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

#include "linkedlist.h"

#include <stdbool.h>



/**
 * \brief Frees a linked list and frees its elements with given function.
 *
 * \param[in,out] list      The linked list
 * \param[in]     freeitems The function to pass each item to free
 */
void lfreer(LinkedList *list, void (*freeitems)(data*));


/**
 * \brief Removes an element of the linked list.
 *
 * \param[in,out] list The linked list
 * \param[in]     item The item to find and remove
 *
 * \return \c true if the element could be found, and was removed.
 */
bool lremove(LinkedList *list, const data *item);


/**
 * \brief Applies a function to each element of the structure.
 *
 * \param[in,out] list  The linked list
 * \param[in]     apply The function to apply
 */
void leach(LinkedList *list, void (*apply)(data*));


/**
 * \brief Retrieve the first item in the linked list to match a given
 *        predicate.
 *
 * \param[in] list The linked list
 * \param[in] pred The predicate function to apply
 *
 * \return The first matching element, or \c NULL if none was found.
 */
data *lcond(const LinkedList *list, bool (*pred)(const data*));


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
void lprintf(const LinkedList *list, void (*printitem)(const data*));


#endif /* LINKEDLIST_FUNCS_H */
