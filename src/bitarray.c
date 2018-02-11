#include "bitarray.h"

#include <errno.h> /* for errno, EINVAL, ENOMEM, ERANGE */
#include <stdint.h> /* for uint8_t */
#include <stdlib.h> /* for malloc(), free(), and NULL */
#include <string.h> /* for memset() */



extern int errno;



struct bitarray {
	unsigned int size;
	uint8_t data[];
};


BitArray *ba_new(const unsigned int s) {
	if(!s) {
		errno = EINVAL;
		return NULL;
	}
	BitArray *const ba = malloc(sizeof(BitArray) + s * sizeof(uint8_t));
	if(!ba) {
		errno = ENOMEM;
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
	if(i < ba->size) {
		errno = 0;
		return (ba->data[i / 8] & 1 << (i % 8)) != 0;
	}
	errno = ERANGE;
	return false;
}

bool ba_put(BitArray *const ba, const unsigned int i, const bool v) {
	const bool b = ba_get(ba, i);
	if(!errno) {
		if(v) {
			ba->data[i / 8] |= 1 << i % 8;
		} else {
			ba->data[i / 8] &= ~(1 << i % 8);
		}
	}
	return b;
}
extern bool ba_set(BitArray*, unsigned int);
extern bool ba_unset(BitArray*, unsigned int);
