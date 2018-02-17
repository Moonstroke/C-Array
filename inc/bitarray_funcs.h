#ifndef BITARRAY_FUNCS_H
#define BITARRAY_FUNCS_H


#include "bitarray.h"



/**
 * \brief Counts the <a href="en.wikipedia.org/wiki/Hamming_weight">Hamming
 *        weight</a> of the array.
 *
 * \param[in] array The bit array
 *
 * \return The number of elements set to \c true in the bit array.
 */
unsigned int ba_count(const BitArray *array);


/**
 * \brief Outputs the bit array on \a stdout.
 *
 * This function prints every element with the exact string \c true or \c false,
 * separated by commas, and enclosed in square brackets.
 *
 * \param[in] array The bit array
 */
void ba_printf(const BitArray *array);


#endif /* BITARRAY_FUNCS_H */
