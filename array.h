#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdbool.h>


typedef void data; /**< A more talkative type name */


/**
 * Opaque type definition
 */
typedef struct array Array;


/**
 * \brief Initializer method.
 *
 * Constructs an array of `size` slots, with `size` times `itemsize` allocated
 * bytes
 *
 * \param[in] size
 */
Array *newarray(size_t size);

/**
 * \brief Deallocates an array.
 *
 * \param[in,out] self The array to free
 */
void afree(Array *self);


/**
 * \brief Gives the size of an array.
 *
 * \param[in] self The array
 *
 * \return The number of elements in the array
 */
size_t asize(const Array *self);


/**
 * \brief Retrieves an element of an array from its index or NULL if index is
 *        invalid.
 *
 * An index is valid if an only if:
 * \code
 * -arraysize(array) <= index < -1 || 0 <= index < arraysize(array)
 * \endcode
 * Negative indexes will get \c |index|'th item from the end
 *
 * \param[in] self  The array
 * \param[in] index The index at which to look for an element
 *
 * \return The \a index'th element in the array, or \c NULL if the index is
 *         invalid
 */
data *aget(const Array *self, ssize_t index);

/**
 *\brief Replaces an element of the array.
 *
 * \param[in,out] self    The array
 * \param[in]     index   The index at which to update the element
 * \param[in]     newitem The new element to set
 *
 * \return The former element found at index \c index, or \c NULL if the index
 *         is invalid
 */
data *aset(Array *self, ssize_t index, data *newitem);


/**
 * \brief Inserts an element at \c index'th position.
 *
 * \param[in,out] self    The array
 * \param[in]     index   The index at which to insert an element
 * \param[in]     newitem The element to add
 * \return The new size of the array or \c -1 if an error occurred (index is
 *         invalid or memory allocation failed)
 */
ssize_t aadd(Array *self, ssize_t index, data *newitem);

/**
 * \brief Adds an item to the end of the array.
 *
 * \param[in,out] self The array
 * \param[in]     item The element to append
 *
 * \return The index of the array, or \c -1 if an error occurred.
 *
 * \sa aadd
 */
inline ssize_t aappend(Array *self, data *item) {
	aadd(self, asize(self), item);
}


/**
 * \brief Removes an element from the array.
 *
 * \param[in,out] self  The array
 * \param[in]     index The index of the element to remove
 *
 * \return The element just removed, or NULL if an error occurred (invalid index)
 */
data *adrop(Array *self, ssize_t index);


/**
 * \brief Prints an array on stdin, with each element printed with provided
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
 * \param[in,out] self      The array
 * \param[in]     printitem The function to print each element with
 */
void aprintf(const Array *self, void (*printitem)(const data*));
#endif /* ARRAY_H */
