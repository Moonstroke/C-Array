#include "linkedlist_funcs.h"

void lfreer(LinkedList *const l, void (*const f)(data*)) {
	// TODO
	size_t i;
	void *data;
	for(i = 0; (data = lget(l, i)); ++i) {
		f(data);
	}
}


bool lremove(LinkedList *const l, const data *const d) {
	size_t i = llen(l);
	while(i--) {
		if(lget(l, i) == d) {
			return ldrop(l, i) != NULL;
		}
	}
	return false;
}

