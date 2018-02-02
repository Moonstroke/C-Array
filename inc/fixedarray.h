/**
 * \file fixedarray.h
* \author joH1
* \version 0.1
*
* \brief This file contains the declaration of a type of array of fixed size.
*
* The type FixedArray is to be instantiated with a certain size that is not
* modified for the lifetime of the object. Elements can be added at any index
* of the array, unset values are set to \c NULL -- which is then  a valid value
* for an element.
*/

#ifndef FIXEDARRAY_H
#define FIXEDARRAY_H


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
FixedArray *fa_new(unsigned int size);

/**
 * \brief Deallocates a fixed array.
*
* \param[in,out] self The fixed array to free
*/
void fa_free(FixedArray *self);


/**
 * \brief Gets the size of the fixed array.
 *
 * \param[in] self self The fixed array
 *
 * \return The size of the fixed array
 */
unsigned int fa_size(const FixedArray *self);


/**
 * \brief Retrieve an element of the fixed array.
 *
 * \note The function returns \c NULL if the index is invalid, but it can also
 *       be a valid value (ie. the element is unset).
 *
 * \param[in] self  The fixed array
 * \param[in] index The index at which to get the element
 *
 * \return The element at given index, or \c NULL if the index is invalid
 */
data *fa_get(const FixedArray *self, unsigned int index);

/**
 * \brief Overwrites an element of the fixed array.
 *
 * \param[in,out] self    The fixed array
 * \param[in]     index   The index at which to set the element
 * \param[in]     element The value to set
 */
void fa_set(FixedArray *self, unsigned int index, data *element);


# endif /* FIXEDARRAY_H */
