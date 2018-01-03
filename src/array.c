#include "array.h"

#include "log.h"


struct array {
	unsigned int capacity;
	unsigned int size;
	void **items;
};


Array *newarray(const unsigned int s) {
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


unsigned int asize(const Array *const a) {
	return a->size;
}

static inline int valid(const Array *const a, const int i) {
	const int n = a->size;
	if(0 <= i && i < n) {
		return i;
	} else if(-n <= i && i < 0) {
		return n + i;
	} else {
		return -1;
	}
}

data *aget(const Array *const a, const int index) {
	const int i = valid(a, index);
	if(i < 0)
		return NULL;
	return a->items[i];
}

data *aset(Array *const a, const int index, data *const e) {
	const int i = valid(a, index);
	if(i < 0)
		return NULL;
	void *const former = a->items[i];
	a->items[i] = e;
	return former;
}


int aadd(Array *const a, const int index, data *const e) {
	const int i = (index == (signed)a->size) ? index : valid(a, index);
	/* not just `i = valid(index)` because `a->size` is a valid value (=> append) */
	if(i < 0)
		return -1;
	const unsigned int n = a->size,
	             c = a->capacity;
	if(n == c) {
		const unsigned int capa = c + (c / 2 + c % 2); /* capacity * 1.5 */
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
extern inline int aappend(Array *a, data *e);

data *adrop(Array *a, const int index) {
	const unsigned int l = a->size;
	const int n = valid(a, index);

	if(n < 0)
		return NULL;
	data *const it = a->items[n];
	a->items[n] = NULL;

	/* displace the elements to shrink the space */
	unsigned int i;
	for(i = n; i < l - 1; ++i)
		a->items[i] = a->items[i + 1];
	a->size--;
	return it;
}
