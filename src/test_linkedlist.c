#include "linkedlist.h"
#include "linkedlist_funcs.h"

#include <assert.h>
#include <log.h> /* for info(), verbose() */
#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for NULL */



static LinkedList *llist;


static int values[] = {42, 3, 7, 13};
static const unsigned int N = 4;


static void init(void) {
	info("llist = newlinkedlist(%u)", N);
	llist = newlinkedlist();
	assert(llist != NULL);
	info("OK\n");
}

static void cleanup(void) {
	info("lfree(llist)");
	lfree(llist, NULL);
	info("OK\n");
}


static void test_lappend(void) {
	int expected, got;
	data *param;
	info("tests lappend");
	for(unsigned int n = 0; n < N; ++n) {
		param = values + n;
		info("lappend(llist, %p)", param);
		expected = n;
		verbose("expected: %d", expected);
		got = lappend(llist, param);
		verbose("got     : %d", got);
		assert(got == expected);
	}
	info("OK\n");
}

static void test_lget__valid(void) {
	data *expected, *got;
	info("test lget -- valid indices");
	for(unsigned int index = 0; index < N; ++index) {
		info("lget(llist, %u)", index);
		expected = values + index;
		verbose("expected: %d", expected);
		got = lget(llist, index);
		verbose("got     : %d", got);
		assert(got == expected);
		info("OK\n");
	}
}

static void test_lset__valid(void) {
	static int extra = -32;
	data *const param = &extra;
	const unsigned int index = 2;
	data *expected, *got;
	info("test lset -- valid index");
	info("lset(llist, %u, %p)", index, param);
	expected = values + index;
	verbose("expected: %d", expected);
	got = lset(llist, index, param);
	verbose("got     : %d", got);
	assert(got == expected);
	info("OK\n");
}

static void test_ladd__valid(void) {
	static int extra = 8;
	data *const param = &extra;
	int expected, got;
	const unsigned int index = 3;
	info("test ladd -- valid index");
	info("ladd(llist, %u, %p)", index, param);
	expected = (signed)index;
	verbose("expected: %d", expected);
	got = ladd(llist, index, param);
	verbose("got     : %d", got);
	assert(got == expected);
	info("OK\n");
}

static void test_ldrop__valid(void) {
	data *expected, *got;
	const unsigned int index = 0;
	info("test ldrop -- valid index");
	info("ldrop(llist, %u)", index);
	expected = values + index;
	verbose("expected: %p", expected);
	got = ldrop(llist, index);
	verbose("got     : %p", got);
	assert(got == expected);
	info("OK\n");
}


static void print_as_int(const data *const e) {
	if(e)
		printf("%d", *(int*)e);
	else
		printf("(null)");
}
void test_linkedlist(void) {

	init();

	test_lappend();
	lprintf(llist, print_as_int);

	test_lget__valid();

	test_ladd__valid();
	lprintf(llist, print_as_int);

	test_lset__valid();
	lprintf(llist, print_as_int);

	test_ldrop__valid();
	lprintf(llist, print_as_int);

	cleanup();
}
