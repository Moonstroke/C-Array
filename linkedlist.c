#include "linkedlist.h"


#include <stdlib.h>
#include <stdio.h>


struct node {
	void *data;
	struct node *next;
};

struct llist {
	size_t len;
	struct node *head;
};

struct llist *newlinkedlist(void) {
	struct llist *const l = malloc(sizeof(struct llist));
	if(l == NULL)
		return NULL;
	l->len = 0;
	l->head = NULL;
	return l;
}

static inline struct node *newnode(void *const data, struct node *const next) {
	struct node *const item = malloc(sizeof(struct node));
	if(item == NULL) {
		return NULL;
	}
	item->data = data;
	item->next = next;
	return item;
}

void lfree(struct llist *const l, void (*f)(void*)) {
	if(l->head) {
		struct node *item = l->head, *next;
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


size_t llen(const struct llist *const l) {
	return l->len;
}


static inline ssize_t valid(const struct llist *const l, const ssize_t i) {
	const size_t n = l->len;
	if(0 <= i && i < n) {
		return i;
	} else if(-n <= i && i < 0) {
		return n + i;
	} else {
		return -1;
	}
}

static inline struct node *lgoto(const struct llist *const l, const size_t n) {
	struct node *item = l->head;
	size_t i;
	for(i = 0; i < n && item != NULL; ++i) {
		item = item->next;
	}
	return item;
}


void *lget(const struct llist *const l, const ssize_t index) {
	ssize_t i = valid(l, index);
	if(i < 0) {
		return NULL;
	}
	return lgoto(l, i)->data;
}

void *lset(struct llist *const l, const ssize_t index, void *const data) {
	ssize_t i = valid(l, index);
	if(i < 0) {
		return NULL;
	}
	struct node *const item = lgoto(l, i);
	void *const former = item->data;
	item->data = data;
	return former;
}

ssize_t ladd(struct llist *const l, const ssize_t index, void *const data) {
	struct node *item = newnode(data, NULL);
	if(item == NULL) {
		return -1;
	}
	// here `l->len` is a valid index ( <=> append)
	ssize_t i = (index == l->len) ? index : valid(l, index);
	if(i == 0) {
		l->head = item;
	} else {
		struct node *prev = lgoto(l, i - 1);/*l->head;
		while(i-- && prev->next != NULL) {
			prev = prev->next;
		}*/
		item->next = prev->next;
		prev->next = item;
	}
	l->len++;
	return index;
}
extern inline ssize_t lappend(struct llist *l, void *data);

void *ldrop(struct llist *const l, const ssize_t index) { // TODO refactor
	const ssize_t i = valid(l, index);
	if(i < 0) {
		return NULL;
	}
	else if(i == 0) {
		void *const data = l->head->data;
		l->head = l->head->next;
		return data;
	}
	struct node *prev = lgoto(l, i - 1), *item;
	if(prev == NULL || (item = prev->next) == NULL)
		return NULL;
	void *const data = item->data;
	prev->next = item->next;
	free(item);
	return data;
}

void lprintf(const struct llist *const l, void (*f)(void*)) {
	const size_t n = l->len;
	printf("(");
	if(n > 0) {
		if(f)
			f(l->head->data);
		else
			printf("%p", l->head->data);
	}
	struct node *item;
	for(item = l->head->next; item; item = item->next) {
		if(f) {
			printf(", ");
			f(item->data);
		} else
			printf(", %p", item->data);
	}
	printf(")\n");
}

// debugging function
static void ldump(const struct llist *l) {
	printf("LinkedList {\n");
	printf("    len = %ld,\n", l->len);
	printf("    items = ");
	struct node *item = l->head;
	while(item != NULL) {
		printf("%p, ", item);
		item = item->next;
	}
	printf("\n}\n");
}
