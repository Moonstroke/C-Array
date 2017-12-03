#ifndef ARRAY_FUNCS_H
#define ARRAY_FUNCS_H

#include "array.h"


/**
 * \brief Frees an array and its items using given function.
 *
 * If one makes an array of user-defined type, providing a destructor function,
 * this is the place to use it. Cast to \c void(*)(void*) might be necessary to
 * shut up some compilers warnings.
 *
 * \note Function pointers casts usually cause undefined behavior, but if one
 *       knows what he's doing, a cast to \c void* will not cause undefined
 *       behaviour.
 */
void afreer(Array *array, void (*freeitem)(data*));

/**
 * \brief Removes an element from the array, found not by index but by the
 *        element directly.
 *
 * \param[in,out] array The array
 * \param[in]     item  The item to remove
 *
 * Returns \c true iff the element was found and removed.
 */
bool aremove(Array *array, const data *item);

/**
 * \brief Applies a function to each element.
 *
 * \param[in,out] array The array to iterate over
 * \param[in]     apply The function to apply to each element
 */
void aeach(Array *array, void (*apply)(data*));


#endif /* ARRAY_FUNCS_H */
