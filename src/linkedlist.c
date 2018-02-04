#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>



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
	node->data = d;
	node->next = next;
	return node;
}

void ll_free(LinkedList *const l, void (*const f)(data*)) {
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


unsigned int ll_len(const LinkedList *const l) {
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


data *ll_get(const LinkedList *const l, const int index) {
	int i = valid(l, index);
	if(i < 0) {
		return NULL;
	}
	return lgoto(l, i)->data;
}

data *ll_set(LinkedList *const l, const int index, data *const d) {
	int i = valid(l, index);
	if(i < 0) {
		return NULL;
	}
	Node *const item = lgoto(l, i);
	data *const former = item->data;
	item->data = d;
	return former;
}

int ll_add(LinkedList *const l, const int index, void *const d) {
	const int i = (index == (signed)l->len) ? index : valid(l, index);
	if(i < 0) {
		return -1;
	}
	Node *const item = newnode(d, NULL);
	if(!item) {
		return -1;
	}
	if(!i) {
		item->next = l->head;
		l->head = item;
	} else {
		Node *const prev = lgoto(l, i - 1);
		item->next = prev->next;
		prev->next = item;
	}
	++l->len;
	return i;
}
extern int ll_append(LinkedList*, data*);

data *ll_drop(LinkedList *const l, const int index) {
	const int i = valid(l, index);
	if(i < 0) {
		return NULL;
	}
	data *d = NULL;
	Node *item, **plug = NULL;
	if(i == 0) {
		plug = &l->head;
	} else {
		item = lgoto(l, i - 1);
		if(item == NULL || item->next == NULL) {
			return NULL;
		}
		plug = &item->next;
	}
	item = *plug;
	d = item->data;
	*plug = item->next;
	--l->len;
	free(item);
	return d;
}
