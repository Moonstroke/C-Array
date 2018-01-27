#include "array.h"
#include "array_funcs.h"

#include <assert.h>
#include <log.h>
#include <stdio.h>


#define INT_ARRAY_SIZE 10

static void printint(const void *i) {
	if(i == NULL)
		printf("(nil)");
	else
		printf("%d", *(int*)i);
}

static bool equals42(const void *const e) {
	assert(e != NULL);
	return *((int*)e) == 42;
}

static bool equals1024(const void *const e) {
	assert(e != NULL);
	return *((int*)e) == 1024;
}


void test_array(void) {
	// 10 integers array
	Array *a = a_new(INT_ARRAY_SIZE);

	int ints[] = {-1, 42, 666, 13, 28, -54, 0, 7 , 6, 5};
	verbose("values = [-1, 42, 666, 13, 28, -54, 0, 7, 6, 5]");

	info("test append");
	{
		unsigned int i;
		for(i = 0; i < INT_ARRAY_SIZE; ++i) {
			int expected, got;
			expected = i;
			verbose("a_append(a, %d)", ints[i]);
			verbose("expected: %ld", expected);
			got = a_append(a, &ints[i]);
			verbose("got     : %ld", got);
			assert(expected == got);
		}
	}
	a_printf(a, *printint);
	info("OK\n");

	info("tests get");
	{
		unsigned int i;
		for(i = 0; i < INT_ARRAY_SIZE; ++i) {
			int expected, got;
			expected = ints[i];
			verbose("a_get(a, %d)", i);
			verbose("expected: %d", expected);
			got = *((int*)a_get(a, i));
			verbose("got     : %d", got);
			assert(got == expected);
		}
	}
	a_printf(a, *printint);
	info("OK\n");

	info("test append - overflow size (=> realloc)");
	{
		int extra = 73;
		int expected, got;
		expected = INT_ARRAY_SIZE;
		verbose("a_append(a, %d)", extra);
		verbose("expected: %ld", expected);
		got = a_append(a, &extra);
		verbose("got     : %ld", got);
		assert(expected == got);
	}
	a_printf(a, *printint);
	info("OK\n");

	info("test set");
	{
		int extra = 777;
		int expected, got;
		unsigned int i = 2;
		expected = ints[i];
		verbose("a_set(a, %u, %d)", i, extra);
		verbose("expected: %ld", expected);
		got = *(int*)a_set(a, i, &extra);
		verbose("got     : %ld", got);
		assert(expected == got);
	}
	a_printf(a, *printint);
	info("OK\n");

	info("test a_cond");
	{
		int expected, got;
		expected = 42;
		verbose("acond(a, %s)", "(int i) -> (i == 42)"); // string repr of the equals42() func
		verbose("expected = %d", expected);
		got = *(int*)a_cond(a, equals42);
		verbose("got      = %d", got);
		assert(expected == got);
	}
	info("OK\n");

	info("test a_cond - not found");
	{
		int *expected, *got;
		expected = NULL;
		verbose("a_cond(a, %s)", "(int i) -> (i == 1024)");
		verbose("expected = %p", expected);
		got = (int*)a_cond(a, equals1024);
		verbose("got      = %p", got);
		assert(expected == got);
	}
	info("OK\n");

	info("test a_free");
	verbose("a_free(a)");
	a_free(a);
	info("OK\n");
}
