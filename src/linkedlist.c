#include "linkedlist.h"


#include <stdlib.h>
#include <stdio.h>

typedef struct node Node;
struct node {
	void *data;
	Node *next;
};

struct llist {
	Node *head;
	unsigned int len;
	char _padding[4];
};

LinkedList *newlinkedlist(void) {
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
	node->data = d;
	node->next = next;
	return node;
}

void lfree(LinkedList *const l, void (*const f)(data*)) {
	if(l->head) {
		Node *item = l->head, *next;
		if(f != NULL)
			for(next = l->head->next; next != NULL; item = next, next = next->next) {
				f(item->data);
				free(item);
			}
		else
			for(next = l->head->next; next != NULL; item = next, next = next->next)
				free(item);
	}
	free(l);
}


unsigned int llen(const LinkedList *const l) {
	return l->len;
}


static inline int valid(const LinkedList *const l, const int i) {
	const unsigned int n = l->len;
	if(0 <= i && i < (signed)n) {
		return i;
	} else if(-(signed)n <= i && i < 0) {
		return n + i;
	} else {
		return -1;
	}
}

static inline Node *lgoto(const LinkedList *const l, const unsigned int n) {
	Node *item = l->head;
	unsigned int i;
	for(i = 0; i < n && item != NULL; ++i) {
		item = item->next;
	}
	return item;
}


data *lget(const LinkedList *const l, const int index) {
	int i = valid(l, index);
	if(i < 0) {
		return NULL;
	}
	return lgoto(l, i)->data;
}

data *lset(LinkedList *const l, const int index, data *const d) {
	int i = valid(l, index);
	if(i < 0) {
		return NULL;
	}
	Node *const item = lgoto(l, i);
	data *const former = item->data;
	item->data = d;
	return former;
}

int ladd(LinkedList *const l, const int index, void *const d) {
	Node *item = newnode(d, NULL);
	if(item == NULL) {
		return -1;
	}
	// here `l->len` is a valid index ( <=> append)
	const int i = (index == (signed)l->len) ? index : valid(l, index);
	if(i == 0) {
		l->head = item;
	} else {
		Node *const prev = lgoto(l, i - 1);
		item->next = prev->next;
		prev->next = item;
	}
	l->len++;
	return i;
}
extern inline int lappend(LinkedList *l, data *data);

data *ldrop(LinkedList *const l, const int index) {
	const int i = valid(l, index);
	if(i < 0) {
		return NULL;
	}
	else if(i == 0) {
		data *const d = l->head->data;
		l->head = l->head->next;
		return d;
	}
	Node *prev = lgoto(l, i - 1), *item;
	if(prev == NULL || (item = prev->next) == NULL)
		return NULL;
	data *const d = item->data;
	prev->next = item->next;
	free(item);
	return d;
}
