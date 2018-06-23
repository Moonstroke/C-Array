#ifndef CODS_SORTEDARRAY_H
#define CODS_SORTEDARRAY_H


#include <stddef.h> /* for size_t */
#include <unistd.h> /* for ssize_t */

#include "cods.h" /* for func attrs, data_t */



typedef struct sortedarray SortedArray;

CODS_CTOR
SortedArray *sa_new(size_t size, int (*cmp)(const data_t *, const data_t*));

CODS_MEMBER void sa_free(SortedArray *self);

CODS_MEMBER size_t sa_size(const SortedArray *self) CODS_PURE;

CODS_MEMBER ssize_t sa_add(SortedArray *self, data_t *item);

CODS_MEMBER data_t *sa_get(const SortedArray *self, size_t index) CODS_PURE;

CODS_MEMBER ssize_t sa_indexof(const SortedArray *self, const data_t *value);


#endif /* CODS_SORTEDARRAY_H */
