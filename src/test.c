#include <assert.h>
#include "log.h"
#include <stdio.h>

#include "linkedlist.h"
#include "linkedlist_funcs.h"



void printint(const void *const data) {
	printf("%d", *((int*)data));
}


/**
 * Tests for the functions for the LinkedList structure
 */
int main(void) {

	LinkedList *l = newlinkedlist();

	const int ints[] = {42, 3, 7, 13};
	const unsigned int N = 4;

	info("tests lappend");
	{
		unsigned int i;
		for(i = 0; i < N; ++i) {
			int v = ints[i];
			int got, expected;

			info("lappend(l, %d)", v);
			expected = i;
			verbose("expected: %ld", expected);
			got = lappend(l, (void*)&ints[i]);
			verbose("got     : %ld", got);
			assert(got == expected);
			info("OK");
		}

		printf("list = ");
		lprintf(l, &printint);
	}

	info("\ntests get");
	{
		unsigned int i;
		for(i = 0; i < N; ++i) {
			int got, expected;
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
		unsigned int i = 3;
		int extra = 8;
		int got, expected = i;
		verbose("expected: %d", expected);
		got = ladd(l, i, &extra);
		verbose("got     : %d", got);
		assert(got == expected);
		info("OK");

		printf("list = ");
		lprintf(l, &printint);
	}

	info("\ntests set");
	{
		unsigned int i = 2;
		int extra = -32;
		int expected, got;
		expected = ints[i];
		verbose("expected: %d", expected);
		got = *((int*)lset(l, i, &extra));
		verbose("got     : %d", got);
		assert(got == expected);
		info("OK");

		printf("list = ");
		lprintf(l, &printint);
	}

	info("\ntests drop");
	{
		unsigned int i = 0;
		int expected, got;
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
