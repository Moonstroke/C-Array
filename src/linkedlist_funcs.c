#include "linkedlist_funcs.h"

#include <errno.h> /* for errno, EINVAL */
#include <stdio.h>
#include <stdlib.h>



extern int errno;


static bool _equals(const data *const e1, const data* const e2) {
	return e1 == e2;
}

static void _printitem(const data *const e) {
	printf("%p", e);
}



data *ll_cond(const LinkedList *const ll, const data *const e, bool (*f)(const data*, const data*)) {
	const unsigned int l = ll_len(ll);
	data *item;
	if(!f) {
		if(!e) {
			errno = EINVAL;
			return NULL;
		}
		f = _equals;
	}
	for(unsigned int i = 0; i < l; ++i) {
		item = ll_get(ll, i);
		if(f(item, e))
			return item;
	}
	errno = EINVAL;
	return NULL;
}


data *ll_remove(LinkedList *const ll, const data *const e, bool (*f)(const data*, const data*)) {
	if(!f) {
		f = _equals;
	}
	const unsigned int s = ll_len(ll);
	for(unsigned int i = 0; i < s; ++i) {
		if(f(ll_get(ll, i), e)) {
			errno = 0;
			return ll_drop(ll, i);
		}
	}
	errno = EINVAL;
	return NULL;
}


void ll_each(LinkedList *const ll, void (*const f)(data*)) {
	if(f) {
		errno = 0;
		data *item;
		for(unsigned int i = 0; (item = ll_get(ll, i)); ++i) {
			f(item);
		}
	} else {
		errno = EINVAL;
	}
}


void ll_printf(const LinkedList *const ll, void (*f)(const data*)) {
	printf("(");
	if(!f)
		f = _printitem;
	if(ll_len(ll) > 0)
		f(ll_get(ll, 0));
	data *item;
	unsigned int i;
	for(i = 1; (item = ll_get(ll, i)); ++i) {
			printf(", ");
			f(item);
	}
	printf(")\n");
}
