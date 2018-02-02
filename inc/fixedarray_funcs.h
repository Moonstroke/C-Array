/**
 * \file fixedarray_funcs.h
 * \author joH1
 * \version 0.1
 *
 * \brief Supplementary functions for the FixedArray type.
 *
 * This file declares several additional functions to manipulate instances of
 * FixedArray.
 */

#ifndef FIXEDARRAY_FUNCS_H
#define FIXEDARRAY_FUNCS_H


#include "fixedarray.h"

#include <stdlib.h> /* for NULL */



/**
 * \brief Frees the elements of the fixed array wth the provided function.
 *
 * \note if \a free_item is \c NULL, the elements are not freed.
 *
 * \param[in,out] farray    The fixed array
 * \param[in]     free_item The function to free each item with
 */
void fa_freer(FixedArray *farray, void (*free_item)(data*));

/**
 * \brief Clears the elements of the array (unset all), optionally freeing the
 *        elements.
 *
 * \note If \a free_item is \c NULL, the elements are not freed.
 *
 * \param[in,out] farray    The fixed array
 * \param[in]     free_item The function to free the items
 */
void fa_clear(FixedArray *farray, void (*free_item)(data*));


/**
 * \brief Caluclates the number of non-\c NULL elements.
 *
 * \param[in,out] farray The fixed array
 *
 * \return The number of elements that are not \c NULL.
 */
unsigned int fa_count(const FixedArray *farray);


/**
 * \brief Places an item into the array in the first available slot (ie. the
 *        first non-\c NULL element).
 *
 * \param[in,out] farray The fixed array
 * \param[in]     item   The item to place
 *
 * \return The index where the element was put, or \c -1 i the element could not
 *         be placed.
 */
int fa_put(FixedArray *farray, data *item);


/**
 * \brief Replaces an element in the array and returns it.
 *
 * \param[in,out] farray The fixed array
 * \param[in]     index  The index where to change the values
 * \param[in]     item   The new value to put
 *
 * \return The former element of the array at given index.
 */
data *fa_swap(FixedArray *farray, unsigned int index, data *item);

/**
 * \brief Unsets an element of the array (ie. set it to \c NULL) and returns it.
 *
 * \param[in,out] farray The fixed array
 * \param[in]     index  The index of the element
 *
 * \return The element just unset.
 */
inline data *fa_unset(FixedArray *const farray, const unsigned int index) {
	return fa_swap(farray, index, NULL);
}


/**
 * \brief Applies a function to each element of the array, possibly changing it.
 *
 * \param[in,out] farray The array
 * \param[in]     func   The function to apply
 */
void fa_each(FixedArray *farray, void (*func)(data*));

/**
 * \brief Iterates over the fixed array, without modifying the elements.
 *
 * \param[in] farray The array
 * \param[in] func   The function to apply
 */
void fa_iter(const FixedArray *farray, void (*func)(const data*));


/**
 * \brief Outputs the array on \c stdin.
 *
 * The array is printed between square brackets, each two items separated by a
 * comma and a space.
 *
 * \note The printing of the brackets, comma and space is already handled, the
 *       function \a print_item does not have to do it.
 *
 * \note If \a print_item is \c NULL, the items are printed by default with
 *       their addresses in haxadecimal format, as for the format \c "%p" of
 *       \a printf.
 *
 * \param[in] farray     The array
 * \param[in] print_item The function used to print each element
 */
void fa_printf(const FixedArray *farray, void (*print_item)(const data*));


#endif /* FIXEDARRAY_FUNCS_H */
