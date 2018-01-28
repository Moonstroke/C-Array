#ifndef FIXEDARRAY_FUNCS_H
#define FIXEDARRAY_FUNCS_H


#include "fixedarray.h"

#include <stdlib.h> /* for NULL */



void fa_freer(FixedArray *farray, void (*free_item)(data*));

void fa_clear(FixedArray *farray, void (*free_item)(data*));


unsigned int fa_count(const FixedArray *farray);


int fa_put(FixedArray *farray, data *item);


data *fa_swap(FixedArray *farray, unsigned int index, data *item);

inline data *fa_unset(FixedArray *const farray, const unsigned int index) {
	return fa_swap(farray, index, NULL);
}


void fa_each(FixedArray *farray, void (*func)(data*));

void fa_iter(const FixedArray *farray, void (*func)(const data*));


void fa_printf(const FixedArray *farray, void (*print_item)(const data*));


#endif /* FIXEDARRAY_FUNCS_H */
