#include "array.h"
#include "array_funcs.h"

#include <assert.h>
#include <log.h>
#include <stdio.h>



static Array *array;

static const unsigned int INT_ARRAY_SIZE = 10;
static int values[] = {-1, 42, 666, 13, 28, -54, 0, 7 , 6, 5};


static void init(void) {
	info("Initialization of array of %u items", INT_ARRAY_SIZE);
	array = a_new(INT_ARRAY_SIZE);
}

static void cleanup(void) {
	a_free(array);
}


static void test_a_append(void) {
	unsigned int i;
	info("test a_append");
	verbose("values = [-1, 42, 666, 13, 28, -54, 0, 7, 6, 5]");
	for(i = 0; i < INT_ARRAY_SIZE; ++i) {
		int expected, got;
		expected = i;
		verbose("a_append(array, %d)", values[i]);
		verbose("expected: %ld", expected);
		got = a_append(array, &values[i]);
		verbose("got     : %ld", got);
		assert(got == expected);
	}
	info("OK\n");
}

static void test_a_get(void) {
	info("tests a_get");
	for(unsigned int i = 0; i < INT_ARRAY_SIZE; ++i) {
		int expected, got;
		expected = values[i];
		verbose("a_get(array, %d)", i);
		verbose("expected: %d", expected);
		got = *((int*)a_get(array, i));
		verbose("got     : %d", got);
		assert(got == expected);
	}
	info("OK\n");
}

static void test_a_append__overflow(void) {
	static int extra = 73;
	int expected, got;
	info("test a_append - overflow size (=> realloc)");
	expected = INT_ARRAY_SIZE;
	verbose("a_append(array, %d)", extra);
	verbose("expected: %ld", expected);
	got = a_append(array, &extra);
	verbose("got     : %ld", got);
	assert(got == expected);
	info("OK\n");
}

void test_a_set(void) {
	static int extra = 777;
	int expected, got;
	unsigned int i = 2;
	info("test a_set");
	expected = values[i];
	verbose("a_set(array, %u, %d)", i, extra);
	verbose("expected: %ld", expected);
	got = *(int*)a_set(array, i, &extra);
	verbose("got     : %ld", got);
	assert(got == expected);
	info("OK\n");
}

static bool equals42(const void *const e) {
	assert(e != NULL);
	return *((int*)e) == 42;
}
static void test_a_cond(void) {
	int expected, got;
	info("test a_cond");
	expected = 42;
	verbose("acond(array, %s)", "(int i) -> (i == 42)"); // string repr of the equals42() func
	verbose("expected = %d", expected);
	got = *(int*)a_cond(array, equals42);
	verbose("got      = %d", got);
	assert(got == expected);
	info("OK\n");
}

static bool equals1024(const void *const e) {
	assert(e != NULL);
	return *((int*)e) == 1024;
}
static void test_a_cond__not_found(void) {
	int *expected, *got;
	info("test a_cond - not found");
	expected = NULL;
	verbose("a_cond(array, %s)", "(int i) -> (i == 1024)");
	verbose("expected = %p", expected);
	got = (int*)a_cond(array, equals1024);
	verbose("got      = %p", got);
	assert(got == expected);
	info("OK\n");
}


static void print_as_int(const void *const i) {
	if(i == NULL)
		printf("(nil)");
	else
		printf("%d", *(int*)i);
}
void test_array(void) {

	init();

	test_a_append();
	a_printf(array, *print_as_int);

	test_a_get();

	test_a_append__overflow();
	a_printf(array, *print_as_int);

	test_a_set();
	a_printf(array, *print_as_int);

	test_a_cond();

	test_a_cond__not_found();

	cleanup();
}
