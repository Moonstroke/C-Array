#include "linkedlist.h"


#include <stdlib.h>
#include <stdio.h>

typedef struct node Node;
struct node {
	void *data;
	Node *next;
};

struct llist {
	size_t len;
	Node *head;
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


size_t llen(const LinkedList *const l) {
	return l->len;
}


static inline ssize_t valid(const LinkedList *const l, const ssize_t i) {
	const size_t n = l->len;
	if(0 <= i && i < (signed)n) {
		return i;
	} else if(-(signed)n <= i && i < 0) {
		return n + i;
	} else {
		return -1;
	}
}

static inline Node *lgoto(const LinkedList *const l, const size_t n) {
	Node *item = l->head;
	size_t i;
	for(i = 0; i < n && item != NULL; ++i) {
		item = item->next;
	}
	return item;
}


data *lget(const LinkedList *const l, const ssize_t index) {
	ssize_t i = valid(l, index);
	if(i < 0) {
		return NULL;
	}
	return lgoto(l, i)->data;
}

data *lset(LinkedList *const l, const ssize_t index, data *const d) {
	ssize_t i = valid(l, index);
	if(i < 0) {
		return NULL;
	}
	Node *const item = lgoto(l, i);
	data *const former = item->data;
	item->data = d;
	return former;
}

ssize_t ladd(LinkedList *const l, const ssize_t index, void *const d) {
	Node *item = newnode(d, NULL);
	if(item == NULL) {
		return -1;
	}
	// here `l->len` is a valid index ( <=> append)
	const ssize_t i = (index == (signed)l->len) ? index : valid(l, index);
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
extern inline ssize_t lappend(LinkedList *l, data *data);

void *ldrop(LinkedList *const l, const ssize_t index) {
	const ssize_t i = valid(l, index);
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

void lprintf(const LinkedList *const l, void (*f)(void*)) {
	const size_t n = l->len;
	printf("(");
	if(n > 0) {
		if(f)
			f(l->head->data);
		else
			printf("%p", l->head->data);
	}
	Node *item;
	for(item = l->head->next; item; item = item->next) {
		if(f) {
			printf(", ");
			f(item->data);
		} else
			printf(", %p", item->data);
	}
	printf(")\n");
}
