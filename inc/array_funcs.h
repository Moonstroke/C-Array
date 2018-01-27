/**
 * \file "array_funcs.h"
 * \author joH1
 * \version 0.1
 *
 * This file contains additional functions related to the \a Array structure.
 */

#ifndef ARRAY_FUNCS_H
#define ARRAY_FUNCS_H


#include <stdbool.h>

#include "array.h"



/**
 * \brief Frees an array and its items using given function.
 *
 * If one makes an array of user-defined type, providing a destructor function,
 * this is the place to use it. Cast to \c void(*)(void*) might be necessary to
 * shut up some compilers warnings.
 *
 * \note Function pointers casts usually cause undefined behavior, but if one
 *       knows what he's doing, a cast to \c void* will not cause undefined
 *       behaviour.
 *
 * \param[in,out] array    The array to free recursively
 * \param[in]     freeitem The function to use to free each item
 */
void a_freer(Array *array, void (*freeitem)(data*));

/**
 * \brief Removes an element from the array, found not by index but by the
 *        element directly.
 *
 * \param[in,out] array The array
 * \param[in]     item  The item to remove
 *
 * \return \c true \a iff the element was found and removed.
 */
bool a_remove(Array *array, const data *item);

/**
 * \brief Applies a function to each element.
 *
 * \param[in,out] array The array to iterate over
 * \param[in]     apply The function to apply to each element
 */
void a_each(Array *array, void (*apply)(data*));

/**
 * \brief Retrieves an element of the array according to the condition.
 *
 * Each element of the array is passed to the \a predicate, and the first
 * element to return \c true is returned.
 *
 * \param[in] array     The array
 * \param[in] predicate The condition function to use
 *
 * \return The first element to satisfy the condition, or \c NULL if none is found
 */
data *a_cond(const Array *array, bool (*predicate)(const data*));

/**
 * \brief Prints an array on \a stdin, with each element printed with provided
 *        function.
 *
 * \note The function must only output the element, no whitespace or separating
 *       characters are needed (commas, brackets).
 * \note The function should check the pointer element's value before
 *       dereferencing it, it is not guaranteed that the value will not be
 *       \c NULL.
 *
 * If the item function is \c NULL, the function will output the pointer
 * addresses of the elements in \c printf's "%p" format.
 *
 * \param[in,out] self      The array
 * \param[in]     printitem The function to print each element with
 */
void a_printf(const Array *self, void (*printitem)(const data*));


Array *a_make(unsigned int n, data *const elements[static n]);


#endif /* ARRAY_FUNCS_H */
