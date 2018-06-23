#include "fixedarray.h"

#include <errno.h> /* for errno, EINVAL, ERANGE */
#include <stdlib.h> /* for NULL, malloc(), calloc(), free() */



extern int errno;

struct fixedarray {
	size_t size;
	data *items[];
};


FixedArray *fa_new(const size_t s) {
	if(!s) {
		errno = EINVAL;
		return NULL;
	}
	FixedArray *const fa = malloc(sizeof(FixedArray) + s * sizeof(data*));
	if(!fa) {
		return NULL;
	}
	fa->size = s;
	for(size_t i = 0; i < s; ++i) {
		fa->items[i] = NULL;
	}
	return fa;
}

void fa_free(FixedArray *const fa) {
	free(fa);
}

size_t fa_size(const FixedArray *const fa) {
	return fa->size;
}

data *fa_get(const FixedArray *const fa, const size_t i) {
	if(i < fa->size) {
		errno = 0;
		return fa->items[i];
	}
	errno = ERANGE;
	return NULL;
}

void fa_set(FixedArray *const fa, const size_t i, data *const d) {
	if(i < fa->size) {
		fa->items[i] = d;
		errno = 0;
	} else {
		errno = ERANGE;
	}
}
