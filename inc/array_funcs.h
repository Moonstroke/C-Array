/**
 * \file "array_funcs.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Declaration of extra functions for Array.
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
 * \brief Removes an element from the array, found not by index but by comparing
 *        each element with a provided value.
 *
 * \note The comparison function can be \c NULL, in which case the default
 *       behaviour is to compare the elements' addresses.
 *
 * \note If more than one element matches, only the first in the order of the
 *       array is returned.
 *
 * \note This function sets \a errno to \c EINVAL if the item is not found.
 *
 * \param[in,out] array   The array
 * \param[in]     item    The value to compare
 * \param[in]     eq_func The function to pass each item and the value
 *
 * \return The removed element, or \c NULL if none matched.
 */
data *a_remove(Array *array, const data *item, bool (*eq_func)(const data*, const data*));

/**
 * \brief Applies a function to each element.
 *
 * \note If \a apply is \c NULL, the function is a no-op.
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
 * \brief Constructs an Array and fills it with the elements in the given array.
 *
 * \note The \c static in the declaration of \a elements means that the array
 *       must contain <i>at least</i> \a n elements.
 *
 * \note This function sets \a errno to \c EINVAL if \a n is \c 0, and as it
 *       internally calls \a a_new, it can set \a errno to \c ENOMEM if the
 *       memory can not be allocated.
 *
 * \param[in] n        The number of elements in the array
 * \param[in] elements The elements to fill the Array with
 *
 * \return An \a Array filled with the given items, or \c NULL if an error
 *         occured, or \a n equals \c 0.
 */
Array *a_make(unsigned int n, data *const elements[static n]);


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
 * \param[in,out] array     The array
 * \param[in]     printitem The function to print each element with
 */
void a_printf(const Array *array, void (*printitem)(const data*));


#endif /* ARRAY_FUNCS_H */
