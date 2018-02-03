#include "linkedlist_funcs.h"

#include <stdio.h>
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
	for(unsigned int i = 0; (item = lget(l, i)); ++i) {
		f(item);
	}
}


data *lcond(const LinkedList *const l, bool (*const f)(const data*)) {
	data *item;
	for(unsigned int i = 0; (item = lget(l, i)) && f(item); ++i);
	return item;
}


static void printitem_default(const data *item) {
	printf("%p", item);
}

void lprintf(const LinkedList *const l, void (*f)(const data*)) {
	printf("(");
	if(!f)
		f = printitem_default;
	if(llen(l) > 0)
		f(lget(l, 0));
	data *item;
	unsigned int i;
	for(i = 1; (item = lget(l, i)); ++i) {
			printf(", ");
			f(item);
	}
	printf(")\n");
}
