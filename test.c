#include "array.c"
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


int main(const int argc, const char *argv[]) {
	// 10 integers array
	Array *a = newarray(INT_ARRAY_SIZE);

	int ints[] = {-1, 42, 666, 13, 28, -54, 0, 7 , 6, 5};
	unsigned int i;

	info("\ntest append");
	verbose("values = [-1, 42, 666, 13, 28, -54, 0, 7 , 6, 5]\n");
	for(i = 0; i < INT_ARRAY_SIZE; ++i) {
		ssize_t expected, got;
		expected = i;
		verbose("expected: %ld", expected);
		got = aappend(a, &ints[i]);
		verbose("got     : %ld", got);
		assert(expected == got);
		info("OK");
		aprintf(a, *printint);
	}

	info("\ntests get\n");
	for(i = 0; i < INT_ARRAY_SIZE; ++i) {
		int expected, got;
		expected = ints[i];
		verbose("expected: %d", expected);
		got = *((int*)aget(a, i));
		verbose("got     : %d", got);
		assert(got == expected);
		info("OK");
	}
	aprintf(a, *printint);

	info("\ntest append - overflow size (=> realloc)\n");
	{
		int extra = 73;
		ssize_t expected, got;
		expected = INT_ARRAY_SIZE;
		verbose("expected: %ld", expected);
		got = aappend(a, &extra);
		verbose("got     : %ld", got);
		assert(expected == got);
		info("OK");
	}
	aprintf(a, *printint);

	info("\ntest set");
	{
		int extra = 777;
		int expected, got;
		i = 2;
		expected = ints[i];
		verbose("expected: %ld", expected);
		got = *(int*)aset(a, i, &extra);
		verbose("got     : %ld", got);
		assert(expected == got);
		info("OK");
	}

	info("\ntest free");
	afree(a);
	info("OK");

	return 0;
}
