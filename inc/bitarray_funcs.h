/**
 * \file "bitarray_funcs.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Supplementary functions for the BitArray type.
 *
 * This file declares more convenience functions to manipulate instances of
 * \a BitArray.
 */

#ifndef CODS_BITARRAY_FUNCS_H
#define CODS_BITARRAY_FUNCS_H


#include "bitarray.h"



/**
 * \brief Counts the <a href="en.wikipedia.org/wiki/Hamming_weight">Hamming
 *        weight</a> of the array.
 *
 * \param[in] array The bit array
 *
 * \return The number of elements set to \c true in the bit array.
 */
CODS_MEMBER size_t ba_count(const BitArray *array) CODS_PURE;


/**
 * \brief Outputs the bit array on \a stdout.
 *
 * This function prints every element with the exact string \c true or \c false,
 * separated by commas, and enclosed in square brackets.
 *
 * \param[in] array The bit array
 */
CODS_MEMBER void ba_printf(const BitArray *array);

/**
 * \brief Convenient macro to translate a boolean to a string.
 *
 * \param[in] b The boolean
 *
 * \return The string representation of the given boolean
 */
#define BOOL_REPR(b) ((b) ? "true" : "false")


#endif /* CODS_BITARRAY_FUNCS_H */
