#include "linkedlist_funcs.h"

#include <stdio.h>
#include <stdlib.h>



static bool eq_func__default(const data *const e1, const data* const e2) {
	return e1 == e2;
}
data *ll_remove(LinkedList *const l, const data *const e, bool (*f)(const data*, const data*)) {
	if(!f) {
		f = eq_func__default;
	}
	const unsigned int s = ll_len(l);
	for(unsigned int i = 0; i < s; ++i) {
		if(f(ll_get(l, i), e)) {
			return ll_drop(l, i);
		}
	}
	return NULL;
}


void ll_each(LinkedList *const l, void (*const f)(data*)) {
	if(f) {
		data *item;
		for(unsigned int i = 0; (item = ll_get(l, i)); ++i) {
			f(item);
		}
	}
}


data *ll_cond(const LinkedList *const l, bool (*const f)(const data*)) {
	data *item;
	for(unsigned int i = 0; (item = ll_get(l, i)) && f(item); ++i);
	return item;
}


static void printitem_default(const data *item) {
	printf("%p", item);
}

void ll_printf(const LinkedList *const l, void (*f)(const data*)) {
	printf("(");
	if(!f)
		f = printitem_default;
	if(ll_len(l) > 0)
		f(ll_get(l, 0));
	data *item;
	unsigned int i;
	for(i = 1; (item = ll_get(l, i)); ++i) {
			printf(", ");
			f(item);
	}
	printf(")\n");
}
