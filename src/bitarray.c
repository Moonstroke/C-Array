#include "bitarray.h"

#include <stdint.h> /* for uint8_t */
#include <stdlib.h> /* for malloc(), free(), and NULL */
#include <string.h> /* for memset() */



struct bitarray {
	unsigned int size;
	uint8_t data[];
};


BitArray *ba_new(const unsigned int s) {
	if(!s) {
		return NULL;
	}
	BitArray *const ba = malloc(sizeof(BitArray) + s * sizeof(uint8_t));
	if(!ba) {
		return NULL;
	}
	ba->size = s;
	memset(ba->data, false, s);
	return ba;
}

void ba_free(BitArray *const ba) {
	free(ba);
}

unsigned int ba_size(const BitArray *const ba) {
	return ba->size;
}

bool ba_get(const BitArray *const ba, const unsigned int i) {
	return (ba->data[i / 8] & 1 << (i % 8)) != 0;
}

bool ba_put(BitArray *const ba, const unsigned int i, const bool v) {
	if(i >= ba->size) {
		return false;
	}
	const bool b = ba_get(ba, i);
	if(v) {
		ba->data[i / 8] |= 1 << i % 8;
	} else {
		ba->data[i / 8] &= ~(1 << i % 8);
	}
	return b;
}
extern bool ba_set(BitArray*, unsigned int);
extern bool ba_unset(BitArray*, unsigned int);
