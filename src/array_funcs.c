#include "array_funcs.h"

#include <stdio.h>


void afreer(Array *a, void(*f)(data*)) {
	if(f)
		aeach(a, f);
	afree(a);
}

bool aremove(Array *const a, const data *const item) {
	unsigned int i;
	const unsigned int l = asize(a);
	for(i = 0; i < l; ++i) {
		if(aget(a, i) == item) {
			return adrop(a, i) != NULL;
		}
	}
	return false;
}

void aeach(Array *const a, void (*f)(data*)) {
	unsigned int i;
	const unsigned int l = asize(a);
	for(i = 0; i < l; ++i) {
		f(aget(a, i));
	}
}

data *acond(const Array *a, bool (*f)(const data*)) {
	const unsigned int l = asize(a);
	data *item;
	unsigned int i;
	for(i = 0; i < l; ++i) {
		item = aget(a, i);
		if(f(item))
			return item;
	}
	return NULL;
}

static void printitem_default(const data *item) {
	printf("%p", item);
}

void aprintf(const Array *a, void (*print)(const data*)) {
	const unsigned int n = asize(a);
	printf("[");
	if(!print)
		print = printitem_default;
	if(n > 0) {
		print(aget(a, 0));
	}
	unsigned int i;
	for(i = 1; i < n; ++i) {
		printf(", ");
		print(aget(a, i));
	}
	printf("]\n");
}
