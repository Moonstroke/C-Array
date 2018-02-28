#include "linkedlist.h"

#include <errno.h> /** errno, ERANGE */



extern int errno;

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


static INLINE Node *newnode(data *const d) {
	Node *const node = malloc(sizeof(Node));
	if(!node) {
		return NULL;
	}
	node->value = d;
	node->next = NULL;
	return node;
}

static INLINE Node *ll_goto(const LinkedList *const ll, const unsigned int n) {
	Node *item = ll->head;
	for(unsigned int i = 0; i < n && item; ++i)
		item = item->next;
	return item;
}


LinkedList *ll_new(void) {
	LinkedList *const ll = malloc(sizeof(LinkedList));
	if(!ll) {
		return NULL;
	}
	ll->len = 0;
	ll->head = NULL;
	return ll;
}

void ll_freer(LinkedList *const ll, void (*const f)(data*)) {
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
extern void ll_free(LinkedList*);

unsigned int ll_len(const LinkedList *const ll) {
	return ll->len;
}

data *ll_get(const LinkedList *const ll, const unsigned int i) {
	if(i < ll->len) {
		errno = 0;
		return ll_goto(ll, i)->value;
	}
	errno = ERANGE;
	return NULL;
}

data *ll_set(LinkedList *const ll, const unsigned int i, data *const d) {
	if(i < ll->len) {
		Node *const item = ll_goto(ll, i);
		data *const former = item->value;
		item->value = d;
		errno = 0;
		return former;
	}
	errno = ERANGE;
	return NULL;
}

int ll_add(LinkedList *const ll, const unsigned int i, data *const d) {
	Node *item;
	if(i > ll->len) {
		errno = ERANGE;
		return -1;
	} else if(!(item = newnode(d))) {
		/* errno set in newnode */
		return -1;
	} else {
		Node **plug;
		plug = i == 0 ? &ll->head : &ll_goto(ll, i - 1)->next;
		item->next = *plug;
		*plug = item;
		++ll->len;
		errno = 0;
		return i;
	}
}
extern int ll_append(LinkedList*, data*);

data *ll_drop(LinkedList *const ll, const unsigned int i) {
	if(i >= ll->len) {
		errno = ERANGE;
		return NULL;
	}
	Node *item, **plug;
	data *d;
	plug = i == 0 ? &ll->head : &ll_goto(ll, i - 1)->next;
	item = *plug;
	d = item->value;
	*plug = item->next;
	--ll->len;
	free(item);
	errno = 0;
	return d;
}
