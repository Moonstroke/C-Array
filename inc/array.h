/**
 * \file "array.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Declaration of the dynamic array type.
 *
 * The Array type is a dynamic container for any type of elements. It is
 * allocated an initial size, but in the contrary of FixedArray, its size can
 * dynamically increase over time when further elements are added to it.
 */

#ifndef ARRAY_H
#define ARRAY_H



typedef void data; /**< A more eloquent name for the type of the elements */


/**
 * \brief A structure able to contain a dynamic number of elements.
 *
 * This structure is defined remotely from this file for data encapsulation.
 *
 * An instance of this structure will increase its capacity whenever needed,
 * without explicit user management. The type of the elements is not checked --
 * this means it is user's responsibility to manipulate their \a Arrays with
 * care to avoid undefined behavior!
 *
 * \note This structure is only able to contain pointed types, not primitive
 *       types (unless you try to interpret the addresses as integers).
 */
typedef struct array Array;


/**
 * \brief Constructs an array with initial capacity of \a size elements.
 *
 * \param[in] size The number of elements to allocate
 *
 * \return A new instance of \a Array, with \a size elements slots.
 */
Array *a_new(unsigned int size);

/**
 * \brief Deallocates an array.
 *
 * \param[in,out] self The array to free
 */
void a_free(Array *self);


/**
 * \brief Gives the size of an array.
 *
 * \param[in] self The array
 *
 * \return The number of elements in the array
 */
unsigned int a_size(const Array *self);


/**
 * \brief Retrieves an element of an array from its position (ie. \a index), or
 *        \c NULL if the \a index is invalid.
 *
 * \note An index is valid if an only if it is strictly less than the size of
 *       the array.
 *
 * \param[in] self  The array
 * \param[in] index The index at which to look for an element
 *
 * \return The \a index 'th element in the array, or \c NULL if the index is
 *         invalid
 */
data *a_get(const Array *self, unsigned int index);

/**
 *\brief Replaces an element of the array.
 *
 * \param[in,out] self    The array
 * \param[in]     index   The index at which to update the element
 * \param[in]     newitem The new element to set
 *
 * \return The former element found at index \a index, or \c NULL if the index
 *         is invalid.
 */
data *a_set(Array *self, unsigned int index, data *newitem);


/**
 * \brief Inserts an element at \a index'th position.
 *
 * \param[in,out] self    The array
 * \param[in]     index   The index at which to insert an element
 * \param[in]     newitem The element to add
 * \return The new size of the array or \c -1 if an error occurred (\a index is
 *         invalid, memory allocation failed)
 */
int a_add(Array *self, unsigned int index, data *newitem);

/**
 * \brief Adds an item to the end of the array.
 *
 * \param[in,out] self The array
 * \param[in]     item The element to append
 *
 * \return The index of the array, or \c -1 if an error occurred.
 *
 * \sa a_add
 */
inline int a_append(Array *const self, data *const item) {
	return a_add(self, a_size(self), item);
}


/**
 * \brief Removes an element from the array.
 *
 * \param[in,out] self  The array
 * \param[in]     index The index of the element to remove
 *
 * \return The element just removed, or \c NULL if an error occurred (\a index
 *         is invalid).
 */
data *a_drop(Array *self, unsigned int index);

#endif /* ARRAY_H */
