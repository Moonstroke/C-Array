#include "array.h"

#include "fixedarray.h"
#include "fixedarray_funcs.h" /* for fa_swap() */


#include <log.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h> /* for uint8_t */



#define validate(index, size, include_top_size, return_value) {\
	if(-(signed)size <= index && index < 0) {\
		index +=  size;\
	} else if(index >= ((signed)size + include_top_size) || index < -(signed)size) {\
		return return_value;\
	}\
}


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


data *a_get(const Array *const a, int i) {
	validate(i, a->size, false, NULL);
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
int a_add(Array *const a, int i, data *const e) {
	validate(i, a->size, true, -1);
	const unsigned int index = (unsigned)i,
	                   capa = fa_size(a->items),
	                   size = a->size;
	if(size == capa && !a_resize(a, size + (size / 2 + size % 2) /* capacity * 1.5 */)) {
		return -1;
	}
	for(unsigned int k = size; k > index; --k) {
		fa_set(a->items, k + 1, fa_get(a->items, k));
	}
	fa_set(a->items, index, e);
	++a->size;
	return index;
}
extern int a_append(Array*, data*);


data *a_drop(Array *a, int index) {
	const unsigned int l = a->size;
	validate(index, l, false, NULL);
	data *const it = fa_get(a->items, index);
	fa_set(a->items, index, NULL);

	/* move the elements to shrink the empty slots */
	for(unsigned int i = index; i < l - 1; ++i)
		fa_set(a->items, i, fa_get(a->items, i + 1));
	--a->size;
	return it;
}
