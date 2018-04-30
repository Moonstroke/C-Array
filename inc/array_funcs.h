/**
 * \file "array_funcs.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Declaration of extra functions for Array.
 *
 * This file contains additional functions related to the \a Array structure.
 */

#ifndef CODS_ARRAY_FUNCS_H
#define CODS_ARRAY_FUNCS_H


#include <stdbool.h>

#include "array.h"



/**
 * \brief Frees an array and its items using given function.
 *
 * If one makes an array of user-defined type, providing a destructor function,
 * this is the place to use it.
 *
 * \note You might want to cast your function to \c void(*)(void*) to shut up
 * some compilers warnings.
 *
 * \param[in,out] array    The array to free recursively
 * \param[in]     freeitem The function to use to free each item
 */
CODS_MEMBER void a_freer(Array *array, void (*freeitem)(data*)) CODS_NOTNULL(2);


/**
 * \brief Replaces an element of the array.
 *
 * \note Sets \a errno to \c ERANGE if \a index is invalid.
 *
 * \param[in,out] self    The array
 * \param[in]     index   The index at which to update the element
 * \param[in]     newitem The new element to set
 *
 * \return The former element found at index \a index, or \c NULL if the index
 *         is invalid.
 */
CODS_MEMBER data *a_swap(Array *self, unsigned int index, data *newitem)
CODS_NODISCARD CODS_NOTNULL(3);


/**
 * \brief Applies a function to each element.
 *
 * \param[in,out] array The array to iterate over
 * \param[in]     apply The function to apply to each element
 */
CODS_MEMBER void a_each(Array *array, void (*apply)(data*)) CODS_NOTNULL(2);


/**
 * \brief Retrieves an element of the array that compares equal to a value
 *        through given comparison function.
 *
 * Each element of the array is passed to the comparator function along with the
 * value, the first element that returns \c true is then returned.
 *
 * \note If \a equals is \c NULL, the elements' addresses are compared.
 *
 * \note It is safe to pass \a value as \c NULL, as long as \a equals is not
 *       \c NULL in the same time; in that case, \a errno is set to \c EINVAL
 *       and the function returns \c NULL immediately.
 *
 * \param[in] array The array
 * \param[in] value The value to check against
 * \param[in] equals The comparator function
 *
 * \return The first element to satisfy the condition, or \c NULL.
 */
CODS_MEMBER data *a_cond(const Array *array, const data *value,
                    bool (*equals)(const data*, const data*));


/**
 * \brief Removes an element from the array, found not by index but by comparing
 *        each element with a provided value.
 *
 * The function compares each element of the array with the given value through
 * the provided function. The first element, in the order of the array, to match
 * (the function call returns \c true) is returned, even if there are more
 * matches after this element.
 *
 * \note The comparison function can be \c NULL, in which case the default
 *       behaviour is to compare the elements' addresses.
 *
 * \note This function sets \a errno to \c EINVAL if the element is not found,
 *       or if both \a value and \a equals are \c NULL, in which case the
 *       function returns \c NULL immediately.
 *
 * \param[in,out] array  The array
 * \param[in]     value  The value to compare
 * \param[in] equals The comparator function
 *
 * \return The removed element, or \c NULL.
 */
CODS_MEMBER data *a_remove(Array *array, const data *value,
                      bool (*equals)(const data*, const data*));


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
CODS_CTOR Array *a_make(unsigned int n, data *const elements[static n]);


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
CODS_MEMBER void a_printf(const Array *array, void (*printitem)(const data*));


#endif /* CODS_ARRAY_FUNCS_H */
