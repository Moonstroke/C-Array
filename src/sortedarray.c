#include "sortedarray.h"

#include "array.h"



struct sortedarray {
	Array *array;
	int (*cmp)(const data_t*, const data_t*);
};

SortedArray *sa_new(const size_t size,
                    int (*const cmp)(const data_t *, const data_t*)) {
	SortedArray *const self = malloc(sizeof(SortedArray));
	if(!self)
		return NULL;
	self->array = a_new(size);
	if(!self->array) {
		free(self);
		return NULL;
	}
	self->cmp = cmp;
	return self;
}

void sa_free(SortedArray *const self) {
	a_free(self->array);
	free(self);
}

size_t sa_size(const SortedArray *const self) {
	return a_size(self->array);
}

ssize_t sa_add(SortedArray *const self, data_t *const item) {
	// TODO
	return -1;
}

data_t *sa_get(const SortedArray *const self, const size_t index) {
	return a_get(self->array, index);
}

ssize_t sa_indexof(const SortedArray *const self, const data_t *const value) {
	// TODO
	return -1;
}

extern data_t *sa_geteq(const SortedArray*, const data_t*);
