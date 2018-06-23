#include "array_funcs.h"

#include <errno.h> /* for errno, EINVAL */
#include <stdio.h>



extern int errno;


static bool _equals(const data_t *const e1, const data_t *const e2) {
	return e1 == e2;
}

static void _printitem(const data_t *item) {
	printf("%p", item);
}


void a_freer(Array *a, void (*const f)(data_t*)) {
	a_each(a, f);
	a_free(a);
}

data_t *a_swap(Array *const a, const size_t i, data_t *const e) {
	data_t *const former = a_get(a, i);
	if(errno) {
		return NULL;
	} else {
		a_set(a, i, e);
		return former;
	}
}

void a_each(Array *const a, void (*f)(data_t*)) {
	const size_t s = a_size(a);
	for(size_t i = 0; i < s; ++i) {
		f(a_get(a, i));
	}
}

data_t *a_cond(const Array *a, const data_t *const e, bool (*f)(const data_t*, const data_t*)) {
	const size_t s = a_size(a);
	data_t *item;
	if(!f) {
		if(!e) {
			errno = EINVAL;
			return NULL;
		}
		f = _equals;
	}
	for(size_t i = 0; i < s; ++i) {
		item = a_get(a, i);
		if(f(item, e))
			return item;
	}
	errno = EINVAL;
	return NULL;
}

data_t *a_remove(Array *const a, const data_t *const e, bool (*f)(const data_t*, const data_t*)) {
	if(!f) {
		if(!e) {
			errno = EINVAL;
			return NULL;
		}
		f = _equals;
	}
	const size_t s = a_size(a);
	for(size_t i = 0; i < s; ++i) {
		if(f(a_get(a, i), e)) {
			errno = 0;
			return a_drop(a, i);
		}
	}
	errno = EINVAL;
	return NULL;
}

Array *a_make(const size_t n, data_t *const elements[static n]) {
	Array *const arr = a_new(n);
	if(!arr) {
		return NULL;
	}
	for(size_t i = 0; i < n; ++i) {
		a_append(arr, elements[i]);
	}
	return arr;
}

void a_printf(const Array *a, void (*print)(const data_t*)) {
	const size_t n = a_size(a);
	printf("[");
	if(n) {
		if(!print)
			print = _printitem;
		print(a_get(a, 0));
		for(size_t i = 1; i < n; ++i) {
			printf(", ");
			print(a_get(a, i));
		}
	}
	printf("]\n");
}
