#include "linkedlist.h"

#include <errno.h> /* errno, ERANGE */



extern int errno;

typedef struct node Node;
struct node {
	data_t *value;
	Node *next;
};

struct llist {
	Node *head;
	size_t len;
};


static CODS_INLINE Node *newnode(data_t *const d) {
	Node *const node = malloc(sizeof(Node));
	if(!node) {
		return NULL;
	}
	node->value = d;
	node->next = NULL;
	return node;
}

static CODS_INLINE Node *ll_goto(const LinkedList *const ll, const size_t n) {
	Node *item = ll->head;
	for(size_t i = 0; i < n && item; ++i)
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

void ll_freer(LinkedList *const ll, void (*const f)(data_t*)) {
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

size_t ll_len(const LinkedList *const ll) {
	return ll->len;
}

data_t *ll_get(const LinkedList *const ll, const size_t i) {
	if(i < ll->len) {
		errno = 0;
		return ll_goto(ll, i)->value;
	}
	errno = ERANGE;
	return NULL;
}

void ll_set(LinkedList *const ll, const size_t i, data_t *const d) {
	if(i >= ll->len) {
		errno = ERANGE;
	} else {
		ll_goto(ll, i)->value = d;
		errno = 0;
	}
}

int ll_add(LinkedList *const ll, const size_t i, data_t *const d) {
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
extern int ll_append(LinkedList*, data_t*);

data_t *ll_drop(LinkedList *const ll, const size_t i) {
	if(i >= ll->len) {
		errno = ERANGE;
		return NULL;
	}
	Node *item, **plug;
	data_t *d;
	plug = i == 0 ? &ll->head : &ll_goto(ll, i - 1)->next;
	item = *plug;
	d = item->value;
	*plug = item->next;
	--ll->len;
	free(item);
	errno = 0;
	return d;
}
