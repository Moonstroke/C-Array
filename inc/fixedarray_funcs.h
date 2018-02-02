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
 * \param[in,out] farray    The array
 * \param[in]     free_item The function to free each item with
 */
void fa_freer(FixedArray *farray, void (*free_item)(data*));

/**
 * \brief Clears the elements of the array (unset all), optionally freeing the
 *        elements.
 *
 * \note If \a free_item is \c NULL, the elements are not freed.
 *
 * \param[in,out] farray    The array
 * \param[in]     free_item The function to free the items
 */
void fa_clear(FixedArray *farray, void (*free_item)(data*));


/**
 * \brief Caluclates the number of non-\c NULL elements.
 *
 * \param[in,out] farray The array
 *
 * \return The number of elements that are not \c NULL
 */
unsigned int fa_count(const FixedArray *farray);


/**
 * \brief 
 *
 * \param[in,out] farray The array
 * \param[in]     
 *
 * \return 
 */
int fa_put(FixedArray *farray, data *item);


/**
 * \brief 
 *
 * \param[in,out] farray The array
 * \param[in]     
 *
 * \return 
 */
data *fa_swap(FixedArray *farray, unsigned int index, data *item);

/**
 * \brief 
 *
 * \param[in,out] farray The array
 * \param[in]     
 *
 * \return 
 */
inline data *fa_unset(FixedArray *const farray, const unsigned int index) {
	return fa_swap(farray, index, NULL);
}


/**
 * \brief 
 *
 * \param[in,out] farray The array
 * \param[in]     
 *
 * \return 
 */
void fa_each(FixedArray *farray, void (*func)(data*));

/**
 * \brief 
 *
 * \param[in,out] farray The array
 * \param[in]     
 *
 * \return 
 */
void fa_iter(const FixedArray *farray, void (*func)(const data*));


/**
 * \brief 
 *
 * \param[in,out] farray The array
 * \param[in]     
 *
 * \return 
 */
void fa_printf(const FixedArray *farray, void (*print_item)(const data*));


#endif /* FIXEDARRAY_FUNCS_H */
