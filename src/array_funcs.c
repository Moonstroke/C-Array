#include "array_funcs.h"

#include <stdio.h>


void a_freer(Array *a, void(*f)(data*)) {
	if(f)
		a_each(a, f);
	a_free(a);
}

bool a_remove(Array *const a, const data *const item) {
	unsigned int i;
	const unsigned int l = a_size(a);
	for(i = 0; i < l; ++i) {
		if(a_get(a, i) == item) {
			return a_drop(a, i) != NULL;
		}
	}
	return false;
}

void a_each(Array *const a, void (*f)(data*)) {
	unsigned int i;
	const unsigned int l = a_size(a);
	for(i = 0; i < l; ++i) {
		f(a_get(a, i));
	}
}

data *a_cond(const Array *a, bool (*f)(const data*)) {
	const unsigned int l = a_size(a);
	data *item;
	unsigned int i;
	for(i = 0; i < l; ++i) {
		item = a_get(a, i);
		if(f(item))
			return item;
	}
	return NULL;
}

static void printitem_default(const data *item) {
	printf("%p", item);
}

Array *a_make(const unsigned int n, data *const elements[static n]) {
	Array *arr = a_new(n);
	if(!arr) {
		return NULL;
	}
	for(unsigned int i = 0; i < n; ++i) {
		a_append(arr, elements[i]);
	}
	return arr;
}

void a_printf(const Array *a, void (*print)(const data*)) {
	const unsigned int n = a_size(a);
	printf("[");
	if(!print)
		print = printitem_default;
	if(n > 0) {
		print(a_get(a, 0));
	}
	unsigned int i;
	for(i = 1; i < n; ++i) {
		printf(", ");
		print(a_get(a, i));
	}
	printf("]\n");
}
