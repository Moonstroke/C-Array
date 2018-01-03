#include "array.h"
#include "array_funcs.h"

#include <stdio.h>
#include <assert.h>

#include "log.h"


#define INT_ARRAY_SIZE 10

void printint(const void *i) {
	if(i == NULL)
		printf("(nil)");
	else
		printf("%d", *(int*)i);
}

bool equals42(const void *const e) {
	return *((int*)e) == 42;
}

bool equals1024(const void *const e) {
	return *((int*)e) == 1024;
}


int main(void) {
	// 10 integers array
	Array *a = newarray(INT_ARRAY_SIZE);

	int ints[] = {-1, 42, 666, 13, 28, -54, 0, 7 , 6, 5};
	verbose("values = [-1, 42, 666, 13, 28, -54, 0, 7 , 6, 5]");

	info("test append");
	{
		unsigned int i;
		for(i = 0; i < INT_ARRAY_SIZE; ++i) {
			ssize_t expected, got;
			expected = i;
			verbose("aappend(a, %d)", ints[i]);
			verbose("expected: %ld", expected);
			got = aappend(a, &ints[i]);
			verbose("got     : %ld", got);
			assert(expected == got);
		}
	}
	aprintf(a, *printint);
	info("OK\n");

	info("tests get");
	{
		unsigned int i;
		for(i = 0; i < INT_ARRAY_SIZE; ++i) {
			int expected, got;
			expected = ints[i];
			verbose("aget(a, %d)", i);
			verbose("expected: %d", expected);
			got = *((int*)aget(a, i));
			verbose("got     : %d", got);
			assert(got == expected);
		}
	}
	aprintf(a, *printint);
	info("OK\n");

	info("test append - overflow size (=> realloc)");
	{
		int extra = 73;
		ssize_t expected, got;
		expected = INT_ARRAY_SIZE;
		verbose("aappend(a, %d)", extra);
		verbose("expected: %ld", expected);
		got = aappend(a, &extra);
		verbose("got     : %ld", got);
		assert(expected == got);
	}
	aprintf(a, *printint);
	info("OK\n");

	info("test set");
	{
		int extra = 777;
		int expected, got;
		unsigned int i = 2;
		expected = ints[i];
		verbose("aset(a, %u, %d)", i, extra);
		verbose("expected: %ld", expected);
		got = *(int*)aset(a, i, &extra);
		verbose("got     : %ld", got);
		assert(expected == got);
	}
	aprintf(a, *printint);
	info("OK\n");

	info("test acond");
	{
		int expected, got;
		expected = 42;
		verbose("acond(a, %s)", "(int i) -> (i == 42)"); // string repr of the equals42() func
		verbose("expected = %d", expected);
		got = *(int*)acond(a, equals42);
		verbose("got      = %d", got);
		assert(expected == got);
	}
	info("OK\n");

	info("test acond - not found");
	{
		int *expected, *got;
		expected = NULL;
		verbose("acond(a, %s)", "(int i) -> (i == 1024)");
		verbose("expected = %p", expected);
		got = (int*)acond(a, equals1024);
		verbose("got      = %p", got);
		assert(expected == got);
	}
	info("OK\n");

	info("test afree");
	verbose("afree(a)");
	afree(a);
	info("OK\n");

	return 0;
}
