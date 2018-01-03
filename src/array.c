#include "array.h"

#include "log.h"


struct array {
	size_t capacity;
	size_t size;
	void **items;
};


Array *newarray(const size_t s) {
	Array *const a = malloc(sizeof(Array));
	if(a == NULL)
		return NULL;
	// Using calloc() instead of malloc() here is preferred, as the array might
	// be left only half-full for some time
	data *items = calloc(s, sizeof(data*));
	if(items == NULL)
		return NULL;
	a->items = items;
	a->capacity = s;
	a->size = 0;
	return a;
}

void afree(Array *const a) {
	free(a->items);
	free(a);
}


size_t asize(const Array *const a) {
	return a->size;
}

static inline ssize_t valid(const Array *const a, const ssize_t i) {
	const ssize_t n = a->size;
	if(0 <= i && i < n) {
		return i;
	} else if(-n <= i && i < 0) {
		return n + i;
	} else {
		return -1;
	}
}

data *aget(const Array *const a, const ssize_t index) {
	const ssize_t i = valid(a, index);
	if(i < 0)
		return NULL;
	return a->items[i];
	//return i < 0 ? a->items[a->size + i] : i < a->size ? a->items[i] : NULL;
	/* ungolfed:
	if(i < 0) {
		i = a->size + i;
	}
	// here, necessarily index < a->size
	if(i < 0)
		return NULL;
	return items[i];
	*/
}

data *aset(Array *const a, const ssize_t index, data *const e) {
	const ssize_t i = valid(a, index);
	if(i < 0)
		return NULL;
	void *const former = a->items[i];
	a->items[i] = e;
	return former;
	// TODO
}


ssize_t aadd(Array *const a, const ssize_t index, data *const e) {
	const ssize_t i = (index == (signed)a->size) ? index : valid(a, index);
		// not just `i = valid(index)` because `a->size` is a valid value (=> append)
	if(i < 0)
		return -1;
	const size_t n = a->size,
	             c = a->capacity;
	if(n == c) {
		const size_t capa = c + (c / 2 + c % 2); // capacity * 1.5
		data *const items = realloc(a->items, capa * sizeof(void*));
		if(items == NULL) {
			return -1;
		} else {
			a->capacity = capa;
			a->items = items;
		}
	}
	unsigned int k;
	for(k = n + 1; k > i; --k)
		a->items[k] = a->items[k - 1];
	a->items[i] = e;
	a->size++;
	return i;
}
extern inline ssize_t aappend(Array *a, data *e);

data *adrop(Array *a, const ssize_t index) {
	const size_t l = a->size;
	const ssize_t n = valid(a, index);

	if(n < 0)
		return NULL;
	data *const it = a->items[n];
	a->items[n] = NULL;

	// displace the elements to shrink the space
	size_t i;
	for(i = n; i < l - 1; ++i)
		a->items[i] = a->items[i + 1];
	a->size--;
	return it;
}
