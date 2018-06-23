/**
 * \file "bitarray.h"
 * \author joH1
 * \version 0.1
 *
 * \brief A type of array optimized to contain boolean values.
 *
 * The type BitArray is a specific type of array whose elements are boolean
 * values.
 * It is of fixed size, so it will not operate on memory otherwise than to
 * instantiate and free the array; it also does not have the ability to add or
 * remove elements. Indeed this type is designed to express a set of parameters
 * in a larger architecture, adding or removing any of these parameters has no
 * actual meaning.
 *
 * The functions \a ba_new, \a ba_get, \a ba_put (and hence \a ba_set and
 * \a ba_unset) set the error variable \a errno, defined in the standard header
 * \c errno.h to describe the error state of the function.
 * The variable is assured to be set to \c 0 if the function is in its nominal
 * state, \c ENOMEM if a memory allocation fails (only for \a ba_new),
 * \c EINVAL if a given argument has an invalid value (only for \a ba_new as
 * well, if the size is \c 0) or \c ERANGE if an indexpassed to the function is
 * invalid (ie. greater or equal to the size of the array).
 */

#ifndef CODS_BITARRAY_H
#define CODS_BITARRAY_H


#include <stdbool.h>
#include <stddef.h> /* for size_t */

#include "cods.h" /* for function attrs */



/** A structure that contains a fixed number of binary values. */
typedef struct bitarray BitArray;


/**
 * \brief Allocates a bit array of given size.
 *
 * \note If the allocation fails, the function sets \a errno to \c ENOMEM, or
 * \c EINVAL if \a size is \c 0.
 *
 * \param[in] size The size of the array
 *
 * \return A pointer to a bit array of \a size elements, or \c NULL.
 */
CODS_CTOR BitArray *ba_new(size_t size);


/**
 * \brief Releases memory used by the bit array.
 *
 * \param[in] self The bit array to free
 */
CODS_MEMBER void ba_free(BitArray *self);


/**
 * \brief Gives the number of values held in the array.
 *
 * \param[in] self The bit array
 *
 * \return The size of the bit array.
 */
CODS_MEMBER size_t ba_size(const BitArray *self) CODS_PURE;


/**
 * \brief Retrieves a value from the array at given index.
 *
 * \note If the index is invalid, this function sets \a errno to \c ERANGE and
 *       returns \c false.
 *
 * \param[in] self The bit array
 * \param[in] index The index
 *
 * \return The value in the array, at index \a index.
 */
CODS_MEMBER bool ba_get(const BitArray *self, size_t index) CODS_PURE;


/**
 * \brief Sets the element at position \a index in the bit array to \c true.
 *
 * \note If the index is invalid, this function sets \a errno to \c ERANGE and
 *       returns \c false.
 *
 * \param[in] self The bit array
 * \param[in] index The index
 *
 * \return The former value of the element, or \c false.
 */
CODS_MEMBER bool ba_set(BitArray *const self, const size_t index);

/**
 * \brief Sets the element at position \a index in the bit array to \c false.
 *
 * \note If the index is invalid, this function sets \a errno to \c ERANGE and
 *       returns \c false.
 *
 * \param[in] self The bit array
 * \param[in] index The index
 *
 * \return The former value of the element, or \c false.
 */
CODS_MEMBER bool ba_unset(BitArray *const self, const size_t index);

/**
 * \brief Gives an element of the bit array the given value.
 *
 * \note If the index is invalid, this function sets \a errno to \c ERANGE and
 *       returns \c false.
 *
 * \param[in] self  The bit array
 * \param[in] i     The index
 * \param[in] val   The value to give
 *
 * \return The former value of the element, or \c false.
 */
CODS_MEMBER CODS_INLINE
bool ba_put(BitArray *const self, const size_t i, const bool val) {
	return val ? ba_set(self, i) : ba_unset(self, i);
}


#endif /* CODS_BITARRAY_H */
