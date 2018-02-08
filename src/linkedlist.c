#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>



typedef struct node Node;
struct node {
	data *value;
	Node *next;
};

struct llist {
	Node *head;
	unsigned int len;
	char _padding[4];
};

LinkedList *ll_new(void) {
	LinkedList *const ll = malloc(sizeof(LinkedList));
	if(!ll)
		return NULL;
	ll->len = 0;
	ll->head = NULL;
	return ll;
}

static inline Node *newnode(data *const d, Node *const next) {
	Node *const node = malloc(sizeof(Node));
	if(!node) {
		return NULL;
	}
	node->value = d;
	node->next = next;
	return node;
}

void ll_free(LinkedList *const ll, void (*const f)(data*)) {
	if(ll->head) {
		Node *item = ll->head, *next;
		if(f != NULL)
			for(next = ll->head->next; next != NULL; item = next, next = next->next) {
				f(item->value);
				free(item);
			}
		else
			for(next = ll->head->next; next != NULL; item = next, next = next->next)
				free(item);
	}
	free(ll);
}


unsigned int ll_len(const LinkedList *const ll) {
	return ll->len;
}


static inline Node *lgoto(const LinkedList *const ll, const unsigned int n) {
	Node *item = ll->head;
	unsigned int i;
	for(i = 0; i < n && item != NULL; ++i) {
		item = item->next;
	}
	return item;
}
data *ll_get(const LinkedList *const ll, const unsigned int i) {
	if(i >= ll->len) {
		return NULL;
	}
	return lgoto(ll, i)->value;
}

data *ll_set(LinkedList *const ll, const unsigned int i, data *const d) {
	if(i >= ll->len) {
		return NULL;
	}
	Node *const item = lgoto(ll, i);
	data *const former = item->value;
	item->value = d;
	return former;
}

int ll_add(LinkedList *const ll, const unsigned int i, data *const d) {
	Node *item, **plug;
	if(i > ll->len || !(item = newnode(d, NULL))) {
		return -1;
	}
	plug = i == 0 ? &ll->head : &lgoto(ll, i - 1)->next;
	item->next = *plug;
	*plug = item;
	++ll->len;
	return i;
}
extern int ll_append(LinkedList*, data*);

data *ll_drop(LinkedList *const ll, const unsigned int i) {
	Node *item, **plug;
	data *d;
	if(i >= ll->len) {
		return NULL;
	}
	plug = i == 0 ? &ll->head : &lgoto(ll, i - 1)->next;
	item = *plug;
	d = item->value;
	*plug = item->next;
	--ll->len;
	free(item);
	return d;
}
