/**
 * \file "arrays.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Function attributes the GNU way.
 *
 * This file declares macros defining function and expressions attributes
 * based on GNU C attributes.
 */

#ifndef ARRAYS_H
#define ARRAYS_H



/** Generic definition of the type contained in the structures. */
typedef void data;


#ifdef __GNUC__

# define LIKELY(cond)   __builtin_expect((cond), 1)
# define UNLIKELY(cond) __builtin_expect((cond), 0)


#else /* GNU C */

# warning "ISO C used -- attributes are defined empty"

# define __attribute__(attr) /**< Empty declaration in ISO C */

# define LIKELY(cond)   (cond)
# define UNLIKELY(cond) (cond)

#endif

/**
 * \def LIKELY(cond)
 *
 * \brief The given boolean expression has a high probability of evaluating to
 *        \c true.
 *
 * \note In ISO C, this macro is a no-op.
 *
 * \param[in] cond The condition to evaluate
 */

/**
 * \def UNLIKELY(cond)
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
#define INLINE __attribute__((__always_inline__)) inline

/**
 * \brief The arguments of the function whose positions (1-indexed) are given
 *        must not be \c NULL.
 *
 * \note If no argument is given to this attribute, all pointer arguments are
 *       considered affected by this attribute.
 */
#define NOTNULL(...) __attribute__((__nonnull__(__VA_ARGS__)))

/** Emits a warning if the return value of the function is not used. */
#define NODISCARD __attribute__((__warn_unused_result__))

/**
 * \brief The value returned is only function of the provided arguments and
 *        global variables.
 *
 * \note A \c PURE function can have pointer arguments, as long as the pointed
 *       data is not modified.
 *
 * \note This attribute implies \a NODISCARD.
 */
#define PURE __attribute__((__pure__, __warn_unused_result__))

/**
 * \brief The function does not affect external data; the return value is only
 *        function of its arguments.
 *
 * \note This attribute semantically implies \a PURE, and is more stricter:
 *       global data must not be affected, (pointer arguments must not even be
 *       dereferenced).
 *
 * \note This attribute implies \a NODISCARD.
 */
#define CONSTEXPR __attribute__((__const__, __warn_unused_result__))

/**
 * \brief The function returns a pointer to a block of memory dynamically
 *        allocated with no other pointer to it.
 *
 * \note This attribute implies \a NODISCARD.
 */
#define CTOR __attribute__((__malloc__, __warn_unused_result__))

/** The function is a type method. */
#define MEMBER NOTNULL(1)


#if !defined(FIXEDARRAY_H) && !defined(FIXEDARRAY_FUNCS_H) \
    && !defined(ARRAY_H) && !defined(ARRAY_FUNCS_H) \
    && !defined(LINKEDLIST_H) && !defined(LINKEDLIST_FUNCS_H) \
    && !defined(BITARRAY_H) && !defined(BITARRAY_FUNCS_H)
/* The file has been included directly: use it as the project's main interface
*/

#include "array.h"
#include "array_funcs.h"
#include "bitarray.h"
#include "bitarray_funcs.h"
#include "fixedarray.h"
#include "fixedarray_funcs.h"
#include "linkedlist.h"
#include "linkedlist_funcs.h"

#endif /* main project file */

#endif /* ARRAYS_H */
