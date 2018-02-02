#include "fixedarray.h"

#include <stdint.h> /* for uint8_t */
#include <stdlib.h> /* for NULL, malloc(), calloc(), free() */
#include <string.h> /* for memset() */



struct fixedarray {
	unsigned int size;
	uint8_t _padding[4];
	data *items[];
};


FixedArray *fa_new(const unsigned int s) {
	if(!s)
		return NULL;
	FixedArray *const fa = malloc(sizeof(FixedArray) + s * sizeof(data*));
	if(!fa)
		return NULL;
	fa->size = s;
	memset(fa->items, 0, s);
	return fa;
}

void fa_free(FixedArray *const fa) {
	free(fa);
}


unsigned int fa_size(const FixedArray *const fa) {
	return fa->size;
}

data *fa_get(const FixedArray *const fa, const unsigned int i) {
	return i < fa->size ? fa->items[i] : NULL;
}

void fa_set(FixedArray *const fa, const unsigned int i, data *const d) {
	if(i < fa->size) {
		fa->items[i] = d;
	}
}
