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
 *
 * The functions \a a_new, \a a_get, \a a_set, \a a_add, \a aappend and
 * \a a_drop can be in an error state (generally if an argument given is
 * invalid), and to indicate their status set the variable \a errno (defined in
 * the standard header \c errno.h, and to be declared as \c extern in the
 * source).
 * In these functions, the variable \a errno is assured to be set to \c 0 in the
 * state of the function is nominal, and a non-zero value otherwise:
 * - \c ENOMEM, in case of a memory allocation failure (in \a a_new),
 * - \c EINVAL, in case of an invalid value for an argument (a size of \c 0
 *   given to \a a_new),
 * - \c ERANGE, in case of a function argument describing an index to access and
 *   whose value is out of range (ie. greater than, or equal to the size of the
 *   array).
 */

#ifndef ARRAY_H
#define ARRAY_H


#include "cods.h" /* for function attrs, data */



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
 * \note This function sets \a errno to \c ENOMEM if the memory allocation fails
 *       or \c EINVAL if the given size is invalid (ie. is \c 0).
 *
 * \param[in] size The number of elements to allocate
 *
 * \return A new instance of \a Array, with \a size elements slots, or \c NULL
 *         if an error occurred.
 */
CTOR Array *a_new(unsigned int size);


/**
 * \brief Deallocates an array.
 *
 * \param[in,out] self The array to free
 */
MEMBER void a_free(Array *self);


/**
 * \brief Gives the size of an array.
 *
 * \param[in] self The array
 *
 * \return The number of elements in the array.
 */
MEMBER unsigned int a_size(const Array *self) PURE;


/**
 * \brief Retrieves an element of an array from its position (ie. \a index), or
 *        \c NULL if the \a index is invalid.
 *
 * \note An index is valid if an only if it is strictly less than the size of
 *       the array. If the index is greater than this value, \a errno is set to
 *       \c ERANGE and \c NULL is returned.
 *
 * \param[in] self  The array
 * \param[in] index The index at which to look for an element
 *
 * \return The \a index 'th element in the array, or \c NULL.
 */
MEMBER data *a_get(const Array *self, unsigned int index) PURE;


/**
 *\brief Replaces an element of the array.
 *
 * \note Sets \a errno to \c ERANGE if \a index is invalid.
 *
 * \param[in,out] self    The array
 * \param[in]     index   The index at which to update the element
 * \param[in]     newitem The new element to set
 */
MEMBER void a_set(Array *self, unsigned int index, data *newitem) NOTNULL(3);


/**
 * \brief Inserts an element at \a index'th position.
 *
 * \note This function sets \a errno to \c ENOMEM if the memory allocation fails
 *       or \c ERANGE if the \a index is strictly greater than the size of the
 *       array. In these cases, \c -1 i returned.
 *
 * \param[in,out] self    The array
 * \param[in]     index   The index at which to insert an element
 * \param[in]     newitem The element to add
 * \return The new size of the array or \c -1.
 */
MEMBER int a_add(Array *self, unsigned int index, data *newitem) NOTNULL(3);

/**
 * \brief Adds an item to the end of the array.
 *
 * \note Sets \a errno to \c ENOMEM if the memory allocation for the new element
 *       fails.
 *
 * \param[in,out] self The array
 * \param[in]     item The element to append
 *
 * \return The index of the array, or \c -1 if an error occurred.
 *
 * \sa a_add
 */
MEMBER INLINE NOTNULL(2) int a_append(Array *self, data *item) {
	return a_add(self, a_size(self), item);
}


/**
 * \brief Removes an element from the array.
 *
 * \note Sets \a errno to \c ERANGE and returns \c NULL if \a index is invalid.
 *
 * \param[in,out] self  The array
 * \param[in]     index The index of the element to remove
 *
 * \return The element just removed, or \c NULL if an error occurred (\a index
 *         is invalid).
 */
MEMBER data *a_drop(Array *self, unsigned int index);

#endif /* ARRAY_H */
