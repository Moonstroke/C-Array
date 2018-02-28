#include "array.h"

#include "fixedarray.h"
#include "fixedarray_funcs.h" /* for fa_swap() */


#include <errno.h> /* for errno, EINVAL, ERANGE */
#include <log.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h> /* for uint8_t */



extern int errno;

struct array {
	unsigned int size;
	uint8_t _padding[4];
	FixedArray *items;
};


static bool a_grow(Array *const a) {
	const unsigned int s = fa_size(a->items),
	                   c = s + (s / 2 + s % 2) /* capacity * 1.5 */;
	FixedArray *const items = fa_new(c);
	if(!items) {
		/* errno already set in fa_new() */
		return false;
	}
	for(unsigned int i = 0; i < s; ++i) {
		fa_set(items, i, fa_get(a->items, i));
	}
	fa_free(a->items);
	a->items = items;
	return true;
}


Array *a_new(const unsigned int s) {
	Array *const a = malloc(sizeof(Array));
	if(!a) {
		return NULL;
	}
	a->items = fa_new(s);
	if(!a->items) {
		free(a);
		/* errno already set in fa_new() */
		return NULL;
	}
	a->size = 0;
	return a;
}

void a_free(Array *const a) {
	fa_free(a->items);
	free(a);
}

unsigned int a_size(const Array *const a) {
	return a->size;
}

data *a_get(const Array *const a, const unsigned int i) {
	return fa_get(a->items, i);
}

data *a_set(Array *const a, const unsigned int i, data *const e) {
	return fa_swap(a->items, i, e);
}

int a_add(Array *const a, const unsigned int i, data *const e) {
	const unsigned int s = a->size;
	if(i > s) {
		errno = ERANGE;
		return -1;
	}
	if(s == fa_size(a->items) && !a_grow(a)) {
		/* errno set in a_grow */
		return -1;
	}
	for(unsigned int k = s; k > i; --k) {
		fa_set(a->items, k + 1, fa_get(a->items, k));
	}
	fa_set(a->items, i, e);
	++a->size;
	return i;
}
extern int a_append(Array*, data*);

data *a_drop(Array *a, const unsigned int i) {
	const unsigned int s = a->size;
	if(i >= s) {
		errno = ERANGE;
		return NULL;
	}
	errno = 0;
	data *const e = a_set(a, i, NULL);
	/* move the elements to shrink the empty slots */
	for(unsigned int k = i; k < s - 1; ++k) {
		fa_set(a->items, k, fa_get(a->items, k + 1));
	}
	--a->size;
	return e;
}
