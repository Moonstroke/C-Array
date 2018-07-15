#include "sortedarray.h"

#include <clog.h>

#include "array.h"



struct sortedarray {
	Array *array;
	int (*cmp)(const data_t*, const data_t*);
};

static ssize_t _sa_binsearch(const SortedArray *const self,
                             const data_t *const item, size_t *const end) {
	size_t s = 0, e = a_size(self->array);
	ssize_t i = -1;
	while (i < 0 && s < e) {
		const size_t m = (s + e) / 2;
		const int d = self->cmp(item, a_get(self->array, m));
		if(d < 0) {
			e = m;
		} else if(d > 0) {
			s = m + 1;
		} else {
			i = m;
		}
	}
	if(end)
		*end = e;
	return i;
}

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
	size_t end;
	if(!a_size(self->array)) {
		return a_add(self->array, 0, item);
	} else if(a_size(self->array) == 1) {
		const int d = self->cmp(item, a_get(self->array, 0));
		if(d < 0) {
			return a_add(self->array, 0, item);
		} else if(d > 0) {
			return a_add(self->array, 1, item);
		} else {
			return -1;
		}
	}
	if(_sa_binsearch(self, item, &end) < 0)
		return a_add(self->array, end, item) < 0 ? -1 : (ssize_t)end;
	return -1;
}

data_t *sa_get(const SortedArray *const self, const size_t index) {
	return a_get(self->array, index);
}

ssize_t sa_indexof(const SortedArray *const self, const data_t *const value) {
	return _sa_binsearch(self, value, NULL);
}

extern data_t *sa_geteq(const SortedArray*, const data_t*);

data_t *sa_drop(SortedArray *const self, const size_t index) {
	return a_drop(self->array, index);
}

extern data_t *sa_remove(SortedArray*, const data_t*);
