#include "array.h"

#include "fixedarray.h"


#include <errno.h> /* for errno, EINVAL, ERANGE */
#include <stdbool.h>
#include <stdlib.h>



extern int errno;

struct array {
	size_t size;
	FixedArray *items;
};


static bool a_grow(Array *const a) {
	const size_t s = fa_size(a->items),
	             c = s + (s / 2 + s % 2) /* capacity * 1.5 */;
	FixedArray *const items = fa_new(c);
	if(!items) {
		/* errno already set in fa_new() */
		return false;
	}
	for(size_t i = 0; i < s; ++i) {
		fa_set(items, i, fa_get(a->items, i));
	}
	fa_free(a->items);
	a->items = items;
	return true;
}


Array *a_new(const size_t s) {
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

size_t a_size(const Array *const a) {
	return a->size;
}

data_t *a_get(const Array *const a, const size_t i) {
	if(i < a->size) {
		errno = 0;
		return fa_get(a->items, i);
	} else {
		errno = ERANGE;
		return NULL;
	}
}

void a_set(Array *const a, const size_t i, data_t *const e) {
	if(i < a->size) {
		fa_set(a->items, i, e);
		errno = 0;
	} else {
		errno = ERANGE;
	}
}

ssize_t a_add(Array *const a, const size_t i, data_t *const e) {
	const size_t s = a->size;
	if(i > s) {
		errno = ERANGE;
		return -1;
	}
	if(s == fa_size(a->items) && !a_grow(a)) {
		/* errno set in a_grow */
		return -1;
	}
	for(size_t k = s; k > i; --k) {
		fa_set(a->items, k + 1, fa_get(a->items, k));
	}
	fa_set(a->items, i, e);
	++a->size;
	return i;
}
extern ssize_t a_append(Array*, data_t*);

data_t *a_drop(Array *a, const size_t i) {
	const size_t s = a->size;
	if(i >= s) {
		errno = ERANGE;
		return NULL;
	}
	errno = 0;
	data_t *const e = a_get(a, i);
	/* move the elements to shrink the empty slots */
	for(size_t k = i; k < s - 1; ++k) {
		fa_set(a->items, k, fa_get(a->items, k + 1));
	}
	--a->size;
	return e;
}
