#include "linkedlist_funcs.h"

#include <stdlib.h>



void lfreer(LinkedList *const l, void (*const f)(data*)) {
	// TODO
	unsigned int i;
	void *data;
	for(i = 0; (data = lget(l, i)); ++i) {
		f(data);
	}
}


bool lremove(LinkedList *const l, const data *const d) {
	unsigned int i = llen(l);
	while(i--) {
		if(lget(l, i) == d) {
			return ldrop(l, i) != NULL;
		}
	}
	return false;
}


void leach(LinkedList *const l, void (*const f)(data*)) {
	data *item;
	for(unsigned int i = 0; item = lget(l, i); ++i) {
		f(item);
	}
}


data *lcond(const LinkedList *const l, bool (*const f)(const data*)) {
	const data *item;
	for(unsigned int i = 0; (item = lget(l, i)) && f(item); ++i);
	return item;
}


void lprintf(const LinkedList *const l, void (*const f)(const data*)) {
	printf("(");
	if(llen(l) > 0) {
		if(f)
			f(lget(l, 0));
		else
			printf("%p", lget(l, 0));
	}
	data *item;
	unsigned int i;
	for(i = 0; item = lget(l, i); ++i) {
		if(f) {
			printf(", ");
			f(item);
		} else
			printf(", %p", item);
	}
	printf(")\n");
}
