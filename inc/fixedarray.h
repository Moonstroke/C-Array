/**
 * \file fixedarray.h
 * \author joH1
 * \version 0.1
 *
 * \brief Declaration of an array type of fixed size.
 *
 * The type FixedArray is to be instantiated with a certain size that is not
 * modified for the lifetime of the object. Elements can be added at any index
 * of the array, unset values are set to \c NULL -- which is then a valid value
 * for an element.
 *
 * The functions that can be in an error state set the variable \a errno
 * (defined in the standard header \c errno.h, and to be declared as \c extern
 * in the source) to a value that indicates their status.
 * The functions are \a fa_new, \a fa_get, \a fa_set, and every function that
 * uses one --or more-- of these.
 * In these functions, the variable \a errno is assured to be set to \c 0 in the
 * state of the function is valid, and a non-zero value otherwise:
 * - \c ENOMEM, in case of a memory allocation failure (in \a fa_new),
 * - \c EINVAL, in case of an invalid value for an argument (a size of \c 0
 *   given to \a fa_new),
 * - \c ERANGE, in case of a function argument describing an index to access and
 *   whose value is out of range (ie. greater than, or equal to the size of the
 *   array).
 */

#ifndef FIXEDARRAY_H
#define FIXEDARRAY_H


#include "arrays.h" /* for function attrs */



/**
 * \brief An explicit redefinition of the type contained in the array.
*/
typedef void data;


/**
 * \brief The fixed-size array type.
*/
typedef struct fixedarray FixedArray;


/**
  * \brief Constructs a new fixed array.
 *
 * \param[in] size The size to set to the array
 *
 * \return A new instance of FixedArray of given size
 */
CTOR FixedArray *fa_new(unsigned int size);

/**
 * \brief Deallocates a fixed array.
*
* \param[in,out] self The fixed array to free
*/
MEMBER void fa_free(FixedArray *self);


/**
 * \brief Gets the size of the fixed array.
 *
 * \param[in] self self The fixed array
 *
 * \return The size of the fixed array
 */
MEMBER unsigned int fa_size(const FixedArray *self) PURE;


/**
 * \brief Retrieve an element of the fixed array.
 *
 * \note The function returns \c NULL if the index is invalid, but it can also
 *       be a valid value (ie. the element is unset). Test the value of \a errno
 *       to distinguish those cases (this serves to indicate the state of the
 *       function, see the description of the type for more).
 *
 * \param[in] self  The fixed array
 * \param[in] index The index at which to get the element
 *
 * \return The element at given index, or \c NULL if the index is invalid
 */
MEMBER data *fa_get(const FixedArray *self, unsigned int index) PURE;

/**
 * \brief Overwrites an element of the fixed array.
 *
 * \param[in,out] self    The fixed array
 * \param[in]     index   The index at which to set the element
 * \param[in]     element The value to set
 */
MEMBER void fa_set(FixedArray *self, unsigned int index, data *element);


# endif /* FIXEDARRAY_H */
