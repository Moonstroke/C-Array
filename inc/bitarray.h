#ifndef BITARRAY_H
#define BITARRAY_H


#include <stdbool.h>



typedef struct bitarray BitArray;


Bitarray *ba_new(unsigned int size);

void ba_free(BitArray *self);


unsigned int ba_size(const BitArray *self);


bool ba_get(const BitArray *self);

bool ba_set(BitArray *self, unsigned int value);

bool ba_unset(BitArray *self, unsigned int index);




#endif /* BITARRAY_H */
