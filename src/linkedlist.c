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
	LinkedList *const l = malloc(sizeof(LinkedList));
	if(l == NULL)
		return NULL;
	l->len = 0;
	l->head = NULL;
	return l;
}

static inline Node *newnode(data *const d, Node *const next) {
	Node *const node = malloc(sizeof(Node));
	if(node == NULL) {
		return NULL;
	}
	node->value = d;
	node->next = next;
	return node;
}

void ll_free(LinkedList *const l, void (*const f)(data*)) {
	if(l->head) {
		Node *item = l->head, *next;
		if(f != NULL)
			for(next = l->head->next; next != NULL; item = next, next = next->next) {
				f(item->value);
				free(item);
			}
		else
			for(next = l->head->next; next != NULL; item = next, next = next->next)
				free(item);
	}
	free(l);
}


unsigned int ll_len(const LinkedList *const l) {
	return l->len;
}


static inline Node *lgoto(const LinkedList *const l, const unsigned int n) {
	Node *item = l->head;
	unsigned int i;
	for(i = 0; i < n && item != NULL; ++i) {
		item = item->next;
	}
	return item;
}
data *ll_get(const LinkedList *const l, const unsigned int i) {
	if(i >= l->len) {
		return NULL;
	}
	return lgoto(l, i)->value;
}

data *ll_set(LinkedList *const l, const unsigned int i, data *const d) {
	if(i >= l->len) {
		return NULL;
	}
	Node *const item = lgoto(l, i);
	data *const former = item->value;
	item->value = d;
	return former;
}

int ll_add(LinkedList *const l, const unsigned int i, data *const d) {
	Node *item, **plug;
	if(i > l->len || !(item = newnode(d, NULL))) {
		return -1;
	}
	plug = i == 0 ? &l->head : &lgoto(l, i - 1)->next;
	item->next = *plug;
	*plug = item;
	++l->len;
	return i;
}
extern int ll_append(LinkedList*, data*);

data *ll_drop(LinkedList *const l, const unsigned int i) {
	Node *item, **plug;
	data *d;
	if(i >= l->len) {
		return NULL;
	}
	plug = i == 0 ? &l->head : &lgoto(l, i - 1)->next;
	item = *plug;
	d = item->value;
	*plug = item->next;
	--l->len;
	free(item);
	return d;
}
