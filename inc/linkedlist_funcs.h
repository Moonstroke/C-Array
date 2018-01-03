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
 *
 * \relates LinkedList
 */
void lfreer(LinkedList *list, void (*freeitems)(data*));


/**
 * \brief Removes an element of the linked list.
 *
 * \param[in,out] list The linked list
 * \param[in]     item The item to find and remove
 *
 * \return \c true if the element could be found, and was removed.
 *
 * \relates LinkedList
 */
bool lremove(LinkedList *list, const data *item);


#endif /* LINKEDLIST_FUNCS_H */
