#ifndef CODS_SORTEDARRAY_H
#define CODS_SORTEDARRAY_H


#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for NULL */
#include <unistd.h> /* for ssize_t */

#include "cods.h" /* for func attrs, data_t */



typedef struct sortedarray SortedArray;

CODS_CTOR
SortedArray *sa_new(size_t size, int (*cmp)(const data_t*, const data_t*))
CODS_NOTNULL(2);

CODS_MEMBER void sa_free(SortedArray *self);

CODS_MEMBER size_t sa_size(const SortedArray *self) CODS_PURE;

CODS_MEMBER ssize_t sa_add(SortedArray *self, data_t *item);

CODS_MEMBER data_t *sa_get(const SortedArray *self, size_t index) CODS_PURE;

CODS_MEMBER ssize_t sa_indexof(const SortedArray *self, const data_t *value)
CODS_PURE;

CODS_MEMBER CODS_INLINE CODS_NOTNULL(2) CODS_PURE
data_t *sa_geteq(const SortedArray *const self, const data_t *const other) {
	const ssize_t index = sa_indexof(self, other);
	return index == -1 ? NULL : sa_get(self, index);
}

CODS_MEMBER data_t *sa_drop(SortedArray *self, size_t index);

#endif /* CODS_SORTEDARRAY_H */
