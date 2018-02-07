#ifndef BITARRAY_H
#define BITARRAY_H


#include <stdbool.h>



typedef struct bitarray BitArray;


BitArray *ba_new(unsigned int size);

void ba_free(BitArray *self);


unsigned int ba_size(const BitArray *self);


bool ba_get(const BitArray *self, unsigned int index);

bool ba_put(BitArray *self, unsigned int index, bool value);

inline bool ba_set(BitArray *const self, const unsigned int index) {
	return ba_put(self, index, true);
}

bool ba_unset(BitArray *const self, const unsigned int index) {
	return ba_put(self, index, false);
}




#endif /* BITARRAY_H */
