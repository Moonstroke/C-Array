#include "linkedlist_funcs.h"

#include <errno.h> /* for errno, EINVAL */
#include <stdio.h>
#include <stdlib.h>



extern int errno;


static bool _equals(const data_t *const e1, const data_t* const e2) {
	return e1 == e2;
}

static void _printitem(const data_t *const e) {
	printf("%p", e);
}


void ll_each(LinkedList *const ll, void (*const f)(data_t*)) {
	data_t *item;
	for(size_t i = 0; (item = ll_get(ll, i)); ++i) {
		f(item);
	}
}

data_t *ll_swap(LinkedList *const ll, const size_t i, data_t *const d) {
	data_t *const e = ll_get(ll, i);
	if(errno) {
		return NULL;
	}
	ll_set(ll, i, d);
	return e;
}


data_t *ll_cond(const LinkedList *const ll, const data_t *const e,
              bool (*f)(const data_t*, const data_t*)) {
	const size_t l = ll_len(ll);
	data_t *item;
	if(!f) {
		if(!e) {
			errno = EINVAL;
			return NULL;
		}
		f = _equals;
	}
	for(size_t i = 0; i < l; ++i) {
		item = ll_get(ll, i);
		if(f(item, e))
			return item;
	}
	errno = EINVAL;
	return NULL;
}


data_t *ll_remove(LinkedList *const ll, const data_t *const e,
                bool (*f)(const data_t*, const data_t*)) {
	if(!f) {
		f = _equals;
	}
	const size_t s = ll_len(ll);
	for(size_t i = 0; i < s; ++i) {
		if(f(ll_get(ll, i), e)) {
			errno = 0;
			return ll_drop(ll, i);
		}
	}
	errno = EINVAL;
	return NULL;
}

void ll_printf(const LinkedList *const ll, void (*f)(const data_t*)) {
	printf("(");
	if(!f)
		f = _printitem;
	if(ll_len(ll) > 0)
		f(ll_get(ll, 0));
	data_t *item;
	size_t i;
	for(i = 1; (item = ll_get(ll, i)); ++i) {
			printf(", ");
			f(item);
	}
	printf(")\n");
}
