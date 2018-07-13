/**
 * \file "arraymap.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Definition of a structure mapping keys to values in parallel arrays.
 *
 * The ArrayMap structure binds a \e key element type to a \e value one, in a
 * one-to-one relationship: each key binds to a value, and a key is unique.
 * Each instance is given a comparator function, which is used to compare the
 * keys, and ensure their unicity. However values need not be unique: several
 * keys can map to the same value, in that case the pointers will be considered
 * to be different elements.
 *
 * This structure is implemented with two arrays: one that contains the keys,
 * and the other, the values. The arrays are parallel in that a key has the same
 * index in the array of keys as its value in the array of values. The keys are
 * sorted, to allow optimized resolution (\c O(log n) complexity using the
 * binary search algorithm).
 */

#ifndef CODS_ARRAYMAP_H
#define CODS_ARRAYMAP_H


#include <stdbool.h>
#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for NULL */

#include "cods.h" /* for func attrs, data_t */



/** A structure binding values to unique keys. */
typedef struct arraymap ArrayMap;

/** Alias for the key type. */
typedef data_t key_t;
/** Alias for the value type. */
typedef data_t value_t;


/**
 * \brief Creates a new array map.
 *
 * \param[in] size The initial number of key-value elements
 * \param[in] cmp  The comparison function
 *
 * \return A newly-allocated ArrayMap, or \c NULL on error.
 */
CODS_CTOR ArrayMap *am_new(size_t size, int (*cmp)(const key_t*, const key_t*))
CODS_NOTNULL(2);

/**
 * \brief Releases memory of an array map.
 *
 * \param[in,out] self The array map
 */
CODS_MEMBER void am_free(ArrayMap *self);


/**
 * \brief Places a key and its value in the array map.
 *
 * \note If the key is already present in the map, the mapped value is
 *       overriden.
 *
 * \param[in] self  The array map
 * \param[in] key   The key
 * \param[in] value The value
 *
 * \return \c true if the key and the value could be placed, or \c false if any
 *         error occurred.
 */
CODS_MEMBER bool am_put(ArrayMap *self, key_t *key, value_t *value)
CODS_NOTNULL(2, 3);

/**
 * \brief Retrieves the value mapped to a key in the array map.
 *
 * \param[in] self The array map
 * \param[in] key  The key
 *
 * \return The value bound to the given key, or \c NULL if the key is not
 *         present.
 */
CODS_MEMBER value_t *am_get(const ArrayMap *self, const key_t *key)
CODS_NOTNULL(2);
/**
 * \brief Convenience function to get a value from the array map or a default
 *        one if not present.
 *
 * \param[in] self  The array map
 * \param[in] key   The key
 * \param[in] d_val The default value
 *
 * \return The value bound to the given key, or the default value.
 */
CODS_MEMBER CODS_INLINE CODS_NOTNULL(2, 3)
value_t *am_getd(const ArrayMap *const self, const key_t *const key,
                 value_t *const d_val) {
	value_t *const value = am_get(self, key);
	return value == NULL ? d_val : value;
}

/**
 * \brief Checks whether a key is present in the array map.
 *
 * \param[in] self The array map
 * \param[in] key  The key
 *
 * \return \c true if the key has a mapping in the instance.
 */
CODS_MEMBER bool am_contains(const ArrayMap *self, const key_t *key);

/**
 * \brief Removes a key and its value from the array map.
 *
 * \note If the key is not rpesent, \c NULL is returned and no action is
 *       performed on the array map.
 *
 * \param[in] self The array map
 * \param[in] key  The key
 *
 * \return The former value, or \c NULL.
 */
CODS_MEMBER value_t *am_remove(ArrayMap *self, key_t *key);


#endif /* CODS_ARRAYMAP_H */
