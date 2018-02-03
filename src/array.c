#include "array.h"

#include "fixedarray.h"
#include "fixedarray_funcs.h" /* for fa_swap() */


#include <log.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h> /* for uint8_t */



struct array {
	unsigned int size;
	uint8_t _padding[4];
	FixedArray *items;
};


Array *a_new(const unsigned int s) {
	Array *const a = malloc(sizeof(Array));
	if(a == NULL)
		return NULL;
	a->items = fa_new(s);
	if(a->items == NULL) {
		free(a);
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


static inline int valid(const int s, const int i) {
	if(-s <= i && i < 0) {
		return s + i;
	} else if(i < s) {
		return i;
	} else {
		return -1;
	}
}
data *a_get(const Array *const a, const int index) {
	const int i = valid(a->size, index);
	if(i < 0)
		return NULL;
	return fa_get(a->items, i);
}

data *a_set(Array *const a, const int i, data *const e) {
	return fa_swap(a->items, i, e);
}


static bool a_resize(Array *const a, const unsigned int c) {
	const unsigned int s = fa_size(a->items);
	FixedArray *const items = fa_new(c);
	if(!items) {
		return false;
	}
	for(unsigned int i = 0; i < s; ++i) {
		fa_set(items, i, fa_get(a->items, i));
	}
	fa_free(a->items);
	a->items = items;
	return true;
}
int a_add(Array *const a, int index, data *const e) {
	if(index < (signed)a->size)
		index = valid(a->size, index);
	/* not just i = valid(index) because a->size is a valid value (=> append) */
	if(index < 0)
		return -1;
	const unsigned int i = (unsigned)index,
	                   n = fa_size(a->items),
	                   c = a->size;
	if(n == c) {
		if(!a_resize(a, c + (c / 2 + c % 2) /* capacity * 1.5 */)) {
			return -1;
		}
	}
	for(unsigned int k = n + 1; k > i; --k)
		fa_set(a->items, k, fa_get(a->items, k - 1));
	fa_set(a->items, i, e);
	a->size++;
	return i;
}
extern int a_append(Array*, data*);


data *a_drop(Array *a, const int index) {
	const unsigned int l = a->size;
	const int n = valid(l, index);

	if(n < 0)
		return NULL;
	data *const it = fa_get(a->items, n);
	fa_set(a->items, n, NULL);

	/* displace the elements to shrink the space */
	unsigned int i;
	for(i = n; i < l - 1; ++i)
		fa_set(a->items, i, fa_get(a->items, i + 1));
	a->size--;
	return it;
}
