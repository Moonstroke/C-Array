#include "linkedlist.h"
#include "linkedlist_funcs.h"

#include <assert.h>
#include <log.h> /* for info(), verbose() */
#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for NULL */



void printint(const void *const data) {
	printf("%d", *((int*)data));
}


int test_linkedlist(void) {

	LinkedList *l = newlinkedlist();

	const int ints[] = {42, 3, 7, 13};
	const unsigned int N = 4;

	/* Variables used in tests */
	unsigned int i;
	int got, expected;
	int extra_add, extra_set;

	info("tests lappend");
	{
		for(i = 0; i < N; ++i) {
			int v = ints[i];
			info("lappend(l, %d)", v);
			expected = i;
			verbose("expected: %d", expected);
			got = lappend(l, (void*)&ints[i]);
			verbose("got     : %d", got);
			assert(got == expected);
			info("OK");
		}

		printf("list = ");
		lprintf(l, &printint);
	}

	info("\ntests get");
	{
		for(i = 0; i < N; ++i) {
			expected = ints[i];
			verbose("expected: %d", expected);
			got = *((int*)lget(l, i));
			verbose("got     : %d", got);
			assert(got == expected);
			info("OK");
		}
	}

	info("\ntests add");
	{
		i = 3;
		expected = i;
		extra_add = 8;
		verbose("expected: %d", expected);
		got = ladd(l, i, &extra_add);
		verbose("got     : %d", got);
		assert(got == expected);
		info("OK");
		printf("list = ");
		lprintf(l, &printint);
	}

	info("\ntests set");
	{
		i = 2;
		extra_set = -32;
		expected = ints[i];
		verbose("expected: %d", expected);
		got = *((int*)lset(l, i, &extra_set));
		verbose("got     : %d", got);
		assert(got == expected);
		info("OK");

		printf("list = ");
		lprintf(l, &printint);
	}

	info("\ntests drop");
	{
		i = 0;
		expected = ints[i];
		verbose("expected: %d", expected);
		got = *((int*)ldrop(l, i));
		verbose("got     : %d", got);
		assert(got == expected);
		info("OK");

		printf("list = ");
		lprintf(l, &printint);
	}

	info("\n test free");
	lfree(l, NULL);
	info("OK");

	info("\nend tests");
	return 0;
}
