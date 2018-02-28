#include "fixedarray_funcs.h"

#include <errno.h> /* for errno */
#include <stdio.h> /* for printf() */



extern int errno;


static bool default_equals(const data *const e1, const data *const e2) {
	return e1 == e2;
}

static void default_print_item(const data *const item) {
	printf("%p", item);
}


void fa_freer(FixedArray *const fa, void (*const f)(data*)) {
	fa_clear(fa, f);
	fa_free(fa);
}

void fa_clear(FixedArray *const fa, void (*const f)(data*)) {
	const unsigned int s = fa_size(fa);
	if(f) {
		fa_each(fa, f);
	}
	for(unsigned int i = 0; i < s; ++i) {
		fa_unset(fa, i);
	}
}

unsigned int fa_count(const FixedArray *const fa) {
	const unsigned int s = fa_size(fa);
	unsigned int n = 0;
	for(unsigned int i = 0; i < s; ++i) {
		if(fa_get(fa, i))
			++n;
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
	data *const d = fa_get(fa, i); /* this sets errno */
	if(errno) {
		return NULL;
	} else {
		fa_set(fa, i, e);
		return d;
	}
}
extern data *fa_unset(FixedArray*, unsigned int);


data *fa_cond(const FixedArray *fa, bool (*f)(const data*, const data*), const data *v) {
	const unsigned int s = fa_size(fa);
	data *e;
	if(!f) {
		f = default_equals;
	}
	for(unsigned int i = 0; i < s; ++i) {
		e = fa_get(fa, i);
		if(f(e, v)) {
			errno = 0;
			return e;
		}
	}
	errno = EINVAL;
	return NULL;
}

data *fa_remove(FixedArray *fa, bool (*f)(const data*, const data*), const data *const v) {
	const unsigned int s = fa_size(fa);
	if(!f) {
		f = default_equals;
	}
	for(unsigned int i = 0; i < s; ++i) {
		if(f(fa_get(fa, i), v)) {
			errno = 0;
			return fa_unset(fa, i);
		}
	}
	errno = EINVAL;
	return NULL;
}

void fa_each(FixedArray *const fa, void (*const f)(data*)) {
	const unsigned int s = fa_size(fa);
	for(unsigned int i = 0; i < s; ++i) {
		data *const item = fa_get(fa, i);
		if(item)
			f(item);
	}
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
