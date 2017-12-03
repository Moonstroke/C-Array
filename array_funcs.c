#include "array_funcs.h"


void afreer(Array *a, void(*f)(data*)) {
	if(f)
		aeach(a, f);
	afree(a);
}

bool aremove(Array *const a, const data *const item) {
	size_t i;
	const size_t l = asize(a);
	for(i = 0; i < l; ++i) {
		if(aget(a, i) == item) {
			return adrop(a, i) != NULL;
		}
	}
}

void aeach(Array *const a, void (*f)(data*)) {
	size_t i;
	const size_t l = asize(a);
	for(i = 0; i < l; ++i) {
		f(aget(a, i));
	}
}
