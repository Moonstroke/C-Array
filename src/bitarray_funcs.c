#include "bitarray_funcs.h"

#include <stdio.h> /* for printf */



unsigned int ba_count(const BitArray *const ba) {
	unsigned int sum = 0;
	const unsigned int s = ba_size(ba);
	for(unsigned int i = 0; i < s; ++i)
		if(ba_get(ba, i))
			++sum;
	return sum;
}

void ba_printf(const BitArray *const ba) {
	const unsigned int s = ba_size(ba);
	printf("[%se", ba_get(ba, 0) ? "tru" : "fals");
	for(unsigned int i = 1; i < s; ++i) {
		printf(", %se", ba_get(ba, i) ? "tru" : "fals");
	}
	printf("]\n");
}
