#include "fixedarray_funcs.h"

#include <stdio.h> /* for printf() */



void fa_freer(FixedArray *const fa, void (*const f)(data*)) {
	if(f)
		fa_clear(fa, f);
	fa_free(fa);
}


unsigned int fa_count(const FixedArray *const fa) {
	const unsigned int s = fa_size(fa);
	unsigned int n = 0;
	for(unsigned int i = 0; i < s; ++i) {
		if(fa_get(fa, i))
			n++;
	}
	return n;
}

int fa_put(FixedArray *const fa, data *const item) {
	const unsigned int s = fa_size(fa);
	for(unsigned int i = 0; i < s; ++i)
		if(!fa_get(fa, i)) {
			fa_set(fa, i, item);
			return i;
		}
	return -1;
}


data *fa_swap(FixedArray *const fa, const unsigned int i, data *const e) {
	if(i < fa_size(fa)) {
		data *const d = fa_get(fa, i);
		fa_set(fa, i, e);
		return d;
	} else {
		return NULL;
	}
}

extern data *fa_unset(FixedArray*, unsigned int);


void fa_each(FixedArray *const fa, void (*const f)(data*)) {
	if(f) {
		const unsigned int s = fa_size(fa);
		for(unsigned int i = 0; i < s; ++i) {
			data *const item = fa_get(fa, i);
			if(item)
			f(item);
		}
	}
}

void fa_iter(const FixedArray *const fa, void (*const f)(const data*)) {
	const unsigned int s = fa_size(fa);
	for(unsigned int i = 0; i < s; ++i)
		f(fa_get(fa, i));
}


void fa_clear(FixedArray *const fa, void (*const f)(data*)) {
	const unsigned int s = fa_size(fa);
	if(f)
		fa_each(fa, f);
	for(unsigned int i = 0; i < s; ++i)
		fa_unset(fa, i);
}


static void default_print_item(const data *const item) {
	printf("%p", item);
}
void fa_printf(const FixedArray *const fa, void (*p)(const data*)) {
	const unsigned int s = fa_size(fa);
	printf("[");
	if(s) {
		if(!p)
			p = default_print_item;
		p(fa_get(fa, 0));
		for(unsigned int i = 1; i < s; ++i) {
			printf(", ");
			p(fa_get(fa, i));
		}
	}
	printf("]\n");
}
