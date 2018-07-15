/**
 * \file "sortedarray.h"
 * \author joH1
 * \version 0.1
 *
 * \brief An array storing ts elements sorted.
 *
 * This module declares a type of array where the elements are sorted with a
 * comparison function, specified at creation. This allows for any element to be
 * retrieved faster (logarithmic time, achieved using a binary search algorithm)
 * than in a regular array.
 *
 * The comparison function takes two values and returns a signed integer value.
 * Its specifications are as follows: if the first element is inferior to the
 * second, the returned value must be negative (<= -1), if the first element is
 * superior to the second, the value must be positive (>= 1), and only when the
 * two values are equivalent the function must return exactly zero.
 *
 * Throughout the header is used the term \e equivalent to designate two
 * elements whose comparison returns \c 0 with the function used by the involved
 * sorted array.
 */

#ifndef CODS_SORTEDARRAY_H
#define CODS_SORTEDARRAY_H


#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for NULL */
#include <unistd.h> /* for ssize_t */

#include "cods.h" /* for func attrs, data_t */



/** The sorted array structure. */
typedef struct sortedarray SortedArray;

/**
 * \brief Creates a new sorted array of given capacity.
 *
 * \param[in] size The initial size of the sorted array
 * \param[in] cmp  The comparison function
 *
 * \return A newly allocated instance of SortedArray.
 */
CODS_CTOR
SortedArray *sa_new(size_t size, int (*cmp)(const data_t*, const data_t*))
CODS_NOTNULL(2);

/**
 * \brief Deallocates a sorted array.
 *
 * \param[in,out] self The sorted array
 */
CODS_MEMBER void sa_free(SortedArray *self);

/**
 * \brief Retrieves the size of the sorted array.
 *
 * \param[in] self The sorted array
 *
 * \return The number of elements actually contained in the sorted array.
 */
CODS_MEMBER size_t sa_size(const SortedArray *self) CODS_PURE;

/**
 * \brief Adds an element in the sorted array.
 *
 * \note If the array already contains an element equivalent to the given value,
 *       the function does not add the element and returns \c -1.
 *
 * \param[in] self The sorted array
 * \param[in] item The element, may be \c NULL
 *
 * \return The index of the element in the array, or \c -1 on error.
 */
CODS_MEMBER ssize_t sa_add(SortedArray *self, data_t *item);

/**
 * \brief Retrieves an element in the array by its index.
 *
 * \note Since an element in the array may be \c NULL, the user is advised to
 *       check the value of \e errno on \c NULL returned to ensure that the
 *       value truly indicates an error.
 *
 * \param[in] self  The sorted array
 * \param[in] index The index
 *
 * \return The element at given index in the array, or \c NULL if the index is
 *         invalid.
 */
CODS_MEMBER data_t *sa_get(const SortedArray *self, size_t index) CODS_PURE;

/**
 * \brief Retrieves the index of an equivalent element in the sorted array.
 *
 * \param[in] self  The sorted array
 * \param[in] value The element value
 *
 * \return The index of the element equivalent
 */
CODS_MEMBER ssize_t sa_indexof(const SortedArray *self, const data_t *value)
CODS_PURE;

/**
 * \brief Retrieves in the sorted array an element equivalent to the given one.
 *
 * \param[in] self  The sorted array
 * \param[in] other The equivalent element
 *
 * \return The element equivalent to the given one, or \c NULL if none matches.
 */
CODS_MEMBER CODS_INLINE CODS_NOTNULL(2) CODS_PURE
data_t *sa_geteq(const SortedArray *const self, const data_t *const other) {
	const ssize_t index = sa_indexof(self, other);
	return index == -1 ? NULL : sa_get(self, index);
}

/**
 * \brief Removes an element from the sorted array.
 *
 * \param[in] self The sorted array
 * \param[in] index
 *
 * \return The value just removed, or \c NULL on error.
 */
CODS_MEMBER data_t *sa_drop(SortedArray *self, size_t index);

#endif /* CODS_SORTEDARRAY_H */
