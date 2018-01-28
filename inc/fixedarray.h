#ifndef FIXEDARRAY_H
#define FIXEDARRAY_H


typedef struct fixedarray FixedArray;


typedef void data;


FixedArray *fa_new(unsigned int size);

void fa_free(FixedArray *self);


unsigned int fa_size(const FixedArray *self);


data *fa_get(const FixedArray *self, unsigned int index);

data *fa_set(FixedArray *self, unsigned int index, data *element);


# endif /* FIXEDARRAY_H */
