/**
 * \file "cods.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Main header of the project + common features.
 *
 * This file can be used as the main project of the header: including it in user
 * source will include also all the headers in the project. It is less tedious
 * than including all headers, and ensures that any desired feature is made
 * accessible.
 *
 * Besides that, this file is also included by all the headers of the project,
 * as it also declares content shared between the different modules: the generic
 * type alias \c data_t, and macros defining function and expressions attributes
 * based on GNU C attributes.
 */

#ifndef CODS_H
#define CODS_H



/** Generic definition of the type contained in the structures. */
typedef void data_t;


#ifdef __GNUC__

# define CODS_LIKELY(cond)   __builtin_expect((cond), 1)
# define CODS_UNLIKELY(cond) __builtin_expect((cond), 0)


#else /* GNU C */

# warning "ISO C used -- attributes are defined empty"

# define __attribute__(attr) /**< Empty declaration in ISO C */

# define CODS_LIKELY(cond)   (cond)
# define CODS_UNLIKELY(cond) (cond)

#endif

/**
 * \def CODS_LIKELY(cond)
 *
 * \brief The given boolean expression has a high probability of evaluating to
 *        \c true.
 *
 * \note In ISO C, this macro is a no-op.
 *
 * \param[in] cond The condition to evaluate
 */

/**
 * \def CODS_UNLIKELY(cond)
 *
 * \brief The given boolean expression has a high probability of evaluating to
 *        \c false.
 *
 * \note In ISO C, this macro is a no-op.
 *
 * \param[in] cond The condition to evaluate
 */

/**
 * \brief An attribute specifying that the function calls should be replaced by
 *        its code.
 */
#define CODS_INLINE __attribute__((__always_inline__)) inline

/**
 * \brief The arguments of the function whose positions (1-indexed) are given
 *        must not be \c NULL.
 *
 * \note If no argument is given to this attribute, all pointer arguments are
 *       considered affected by this attribute.
 */
#define CODS_NOTNULL(...) __attribute__((__nonnull__(__VA_ARGS__)))

/** Emits a warning if the return value of the function is not used. */
#define CODS_NODISCARD __attribute__((__warn_unused_result__))

/**
 * \brief The value returned is only function of the provided arguments and
 *        global variables.
 *
 * \note A \c PURE function can have pointer arguments, as long as the pointed
 *       data is not modified.
 *
 * \note This attribute implies \a NODISCARD.
 */
#define CODS_PURE __attribute__((__pure__, __warn_unused_result__))

/**
 * \brief The function returns a pointer to a block of memory dynamically
 *        allocated with no other pointer to it.
 *
 * \note This attribute implies \a NODISCARD.
 */
#define CODS_CTOR __attribute__((__malloc__, __warn_unused_result__))

/**
 * The function is a member of the type's methods.
 *
 * This attribute only ensures that the first argument (the type instance) is
 * not \c NULL, however it also carries semantic information: the function is an
 * OO-like method.
 */
#define CODS_MEMBER CODS_NOTNULL(1)


#if !defined(CODS_FIXEDARRAY_H) && !defined(CODS_FIXEDARRAY_FUNCS_H) \
    && !defined(CODS_ARRAY_H) && !defined(CODS_ARRAY_FUNCS_H) \
    && !defined(CODS_ARRAYMAP_H)\
    && !defined(CODS_LINKEDLIST_H) && !defined(CODS_LINKEDLIST_FUNCS_H) \
    && !defined(CODS_BITARRAY_H) && !defined(CODS_BITARRAY_FUNCS_H)\
    && !defined(CODS_SORTEDARRAY_H)
/* The file has been included directly: use it as the project's main interface
*/

#include "array.h"
#include "array_funcs.h"
#include "arraymap.h"
#include "bitarray.h"
#include "bitarray_funcs.h"
#include "fixedarray.h"
#include "fixedarray_funcs.h"
#include "linkedlist.h"
#include "linkedlist_funcs.h"
#include "sortedarray.h"

#endif /* main project file */

#endif /* CODS_H */
