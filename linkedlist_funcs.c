#include "linkedlist_funcs.h"

void lfreer(LinkedList l, void (*const f)(void*)) {
	// TODO
	size_t i;
	void *data;
	for(i = 0; data = lget(l, i); ++i) {
		f(data);
	}
}


bool lremove(const LinkedList l, void *const data) {
	size_t i = llen(l);
	while(i--) {
		if(lget(l, i) == data) {
			return ldrop(l, i) != NULL;
		}
	}
}

