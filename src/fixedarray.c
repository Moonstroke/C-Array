#include "fixedarray.h"

#include <stdint.h> /* for uint8_t */
#include <stdlib.h> /* for NULL, malloc(), calloc(), free() */



struct fixedarray {
	data **items;
	unsigned int size;
	uint8_t _padding[4];
};


FixedArray *fa_new(const unsigned int s) {
	if(!s)
		return NULL;
	FixedArray *const fa = malloc(sizeof(FixedArray));
	if(!fa)
		return NULL;
	data **const i = calloc(s, sizeof(data*));
	if(!i) {
		free(fa);
		return NULL;
	}
	fa->size = s;
	fa->items = i;
	return fa;
}

void fa_free(FixedArray *const fa) {
	free(fa->items);
	free(fa);
}


unsigned int fa_size(const FixedArray *const fa) {
	return fa->size;
}

data *fa_get(const FixedArray *const fa, const unsigned int i) {
	return fa->items[i];
}

void fa_set(FixedArray *const fa, const unsigned int i, data *const d) {
	fa->items[i] = d;
}
