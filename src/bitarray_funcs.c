#include "bitarray_funcs.h"

#include <stdio.h> /* for printf */



size_t ba_count(const BitArray *const ba) {
	size_t sum = 0;
	const size_t s = ba_size(ba);
	for(size_t i = 0; i < s; ++i)
		if(ba_get(ba, i))
			++sum;
	return sum;
}

void ba_printf(const BitArray *const ba) {
	const size_t s = ba_size(ba);
	printf("[%s", BOOL_REPR(ba_get(ba, 0)));
	for(size_t i = 1; i < s; ++i) {
		printf(", %s", BOOL_REPR(ba_get(ba, i)));
	}
	printf("]\n");
}
