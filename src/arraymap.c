#include "arraymap.h"

#include "array.h"
#include "sortedarray.h"

struct arraymap {
	SortedArray *keys;
	Array *values;
};

ArrayMap *am_new(const size_t size,
                 int (*const cmp)(const key_t*, const key_t*)) {
	ArrayMap *const self = malloc(sizeof(ArrayMap));
	if(!self)
		return NULL;
	self->keys = sa_new(size, cmp);
	if(!self->keys) {
		free(self);
		return NULL;
	}
	self->values = a_new(size);
	if(!self->values) {
		sa_free(self->keys);
		free(self);
		return NULL;
	}
	return self;
}

void am_free(ArrayMap *const self) {
	a_free(self->values);
	sa_free(self->keys);
	free(self);
}

bool am_put(ArrayMap *const self, key_t *const key, value_t *const value) {
	const ssize_t index = sa_add(self->keys, key);
	if(index < 0)
		return false;
	return a_add(self->values, (size_t)index, value) == index;
}

value_t *am_get(const ArrayMap *const self, const key_t *const key) {
	const ssize_t index = sa_indexof(self->keys, key);
	if(index < 0)
		return NULL;
	return a_get(self->values, index);
}
extern value_t *am_getd(const ArrayMap*, const key_t*, value_t*);

bool am_contains(const ArrayMap *const self, const key_t *const key) {
	return sa_indexof(self->keys, key) >= 0;
}

value_t *am_remove(ArrayMap *self, key_t *key) {
	const ssize_t index = sa_indexof(self->keys, key);
	if(index < 0)
		return NULL;
	sa_drop(self->keys, index);
	return a_drop(self->values, index);
}
