#include <stdio.h>
#include <assert.h>

#include "linkedlist.h"
#include "linkedlist_funcs.h"
#include "log.h"

void printint(void *const data) {
	printf("%d", *((int*)data));
}


/**
 * Tests for the functions for the LinkedList structure
 */
int main(const int argc, char *const argv[]) {

	LinkedList l = newlinkedlist();

	int ints[] = {42, 3, 7, 13};
	const unsigned int N = 4;
	unsigned int i;

	info("tests lappend");
	for(i = 0; i < N; ++i) {
		int v = ints[i];
		ssize_t got, expected;

		info("lappend(l, %d)", v);
		expected = i;
		verbose("expected: %ld", expected);
		got = lappend(l, (void*)&ints[i]);
		verbose("got     : %ld", got);
		assert(got == expected);
		info("OK");
		printf("list = ");
		lprintf(l, &printint);
	}

	info("\ntests get");
	for(i = 0; i < N; ++i) {
		int got, expected;
		expected = ints[i];
		verbose("expected: %d", expected);
		got = *((int*)lget(l, i));
		verbose("got     : %d", got);
		assert(got == expected);
		info("OK");
	}

	info("\ntests add");
	i = 3;
	int add_extra = 8;
	int got, expected = i;
	verbose("expected: %d", expected);
	got = ladd(l, i, &add_extra);
	verbose("got     : %d", got);
	assert(got == expected);
	info("OK");
	printf("list = ");
	lprintf(l, &printint);

	info("\ntests set");
	i = 2;
	int set_extra = -32;
	expected = ints[i];
	verbose("expected: %d\n", expected);
	got = *((int*)lset(l, i, &set_extra));
	verbose("got     : %d", got);
	assert(got == expected);
	info("OK");
	printf("list = ");
	lprintf(l, &printint);

	info("\ntests drop");
	i = 0;
	expected = ints[0];
	verbose("expected: %d", expected);
	got = *((int*)ldrop(l, i));
	verbose("got     : %d", got);
	assert(got == expected);
	info("OK");
	printf("list = ");
	lprintf(l, &printint);

	info("\n test free");
	lfree(l, NULL);
	info("OK");

	info("\nend tests");
	return 0;
}
