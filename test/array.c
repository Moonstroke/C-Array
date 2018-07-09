#include "array.h"
#include "array_funcs.h"

#include <CUTE/cute.h>
#include <clog.h> /* for logging macros */
#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for NULL */



/* The instance of test case */
CUTE_TestCase *case_array;



static Array *array;

static const size_t INT_ARRAY_SIZE = 10;
static int VALUES[] = {-1, 42, 666, 13, 28, -54, 0, 7 , 6, 5};


extern _Bool equal_as_ints(const data_t*, const data_t*);
extern const char equal_as_ints_repr[];

extern void print_as_int(const data_t*);


static void init(void) {
	verbose("array = a_new(%zu)", INT_ARRAY_SIZE);
	array = a_new(INT_ARRAY_SIZE);
	CUTE_assertNotEquals(array, NULL);
	for(size_t i = 0; i < INT_ARRAY_SIZE; ++i) {
		a_add(array, i, &VALUES[i]);
	}
}

static void cleanup(void) {
	verbose("a_free(array)");
	a_free(array);
}


static void test_a_new__0_null(void) {
	size_t index;
	Array *got;
	notice("test a_new -- size 0 => NULL array");
	index = 0;
	verbose("a_new(%zu)", index);
	info("expected: (nil)");
	got = a_new(index);
	info("got     : %p", (void*)got); /* necessary cast because of GCC warning */
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	verbose("OK");
}

static void test_a_size__empty(void) {
	Array *empty_array;
	size_t got;
	notice("test a_size -- empty array");
	verbose("empty_array = a_new(%zu)", INT_ARRAY_SIZE);
	empty_array = a_new(INT_ARRAY_SIZE);
	verbose("a_size(empty_array)");
	info("expected: 0");
	got = a_size(empty_array);
	info("got     : %zu", got);
	a_free(empty_array);
	CUTE_assertEquals(got, 0);
	verbose("OK");
}

static void test_a_append(void) {
	Array *empty_array;
	ssize_t expected, got;
	notice("test a_append");
	verbose("empty_array = a_new(%zu)", INT_ARRAY_SIZE);
	empty_array = a_new(INT_ARRAY_SIZE);
	verbose("VALUES = [-1, 42, 666, 13, 28, -54, 0, 7, 6, 5]");
	for(size_t index = 0; index < INT_ARRAY_SIZE; ++index) {
		int value = VALUES[index];
		verbose("a_append(array, &<%d>)", value);
		expected = index;
		info("expected: %zd", expected);
		got = a_append(empty_array, &value);
		info("got     : %zd", got);
		CUTE_assertEquals(got, expected);
		CUTE_assertNoError();
	}
	a_free(empty_array);
	verbose("OK");
}

static void test_a_size__full(void) {
	size_t expected, got;
	notice("test a_size -- array full");
	verbose("a_size(array)");
	expected = INT_ARRAY_SIZE;
	info("expected: %zu", expected);
	got = a_size(array);
	info("got     : %zu", got);
	CUTE_assertEquals(got, expected);
	verbose("OK");
}

static void test_a_get__valid(void) {
	data_t *expected, *got;
	notice("tests a_get -- valid indices");
	for(size_t index = 0; index < INT_ARRAY_SIZE; ++index) {
		verbose("a_get(array, %zu)", index);
		expected = &(VALUES[index]);
		info("expected: %p", expected);
		got = a_get(array, index);
		info("got     : %p", got);
		CUTE_assertEquals(got, expected);
		CUTE_assertNoError();
	}
	verbose("OK");
}

static void test_a_get__invalid(void) {
	const size_t invalid_indices[3] = {
		a_size(array),
		a_size(array) + 1,
		73 /* big "arbitrary" value */
	};
	size_t index;
	data_t *got;
	notice("tests a_get -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("a_get(array, %zu)", index);
		info("expected: (nil)");
		got = a_get(array, index);
		info("got     : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_a_set__valid(void) {
	static int value = 64;
	const size_t index = 7;
	notice("test a_set -- valid index");
	verbose("a_set(array, %zu, &<%d>)", index, value);
	info("expected errno: 0");
	a_set(array, index, &value);
	info("actual errno  : %d", errno);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_a_set__invalid(void) {
	static int value = 23;
	const size_t invalid_indices[3] = {
		a_size(array),
		a_size(array) + 1,
		73 /* big "arbitrary" value */
	};
	size_t index;
	notice("tests a_set -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("a_set(array, %zu, &<%d>)", index, value);
		info("expected errno: %d", ERANGE);
		a_set(array, index, &value);
		info("actual errno  : %d", errno);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_a_add__middle(void) {
	static int value = 33;
	const size_t index = INT_ARRAY_SIZE - 3;
	ssize_t r;
	notice("test a_add() in middle of array");
	verbose("a_add(array, %zu, &<%d>)", index, value);
	r = a_add(array, index, &value);
	CUTE_assertEquals(r, index);
	CUTE_assertNoError();
	for(size_t i = 0; i < index; ++i) {
		const int expected = VALUES[i], got = *(int*)a_get(array, i);
		CUTE_assertEquals(got, expected);
		verbose("%d == %d", got, expected);
	}
	for(size_t i = index; i < INT_ARRAY_SIZE; ++i) {
		const int expected = VALUES[i], got = *(int*)a_get(array, i + 1);
		CUTE_assertEquals(got, expected);
		verbose("%d == %d", got, expected);
	}
	verbose("OK");
}

static void test_a_add__invalid(void) {
	static int value = 42;
	const size_t invalid_indices[3] = {
		a_size(array) + 1,
		a_size(array) + 2,
		73
	};
	int got;
	size_t index;
	notice("tests a_add -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("a_add(array, %zu, &<%d>)", index, value);
		info("expected: -1");
		got = a_add(array, index, &value);
		info("got     : %d", got);
		CUTE_assertEquals(got, -1);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_a_append__overflow(void) {
	static int value = 73;
	int expected, got;
	notice("test a_append -- overflow size (=> realloc)");
	verbose("a_append(array, &<%d>)", value);
	expected = INT_ARRAY_SIZE;
	info("expected: %d", expected);
	got = a_append(array, &value);
	info("got     : %d", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_a_drop__valid(void) {
	const size_t index = 4;
	data_t *expected, *got;
	notice("test a_drop -- valid index");
	verbose("a_drop(array, %zu)", index);
	expected = &(VALUES[index]);
	info("expected: %p", expected);
	got = a_drop(array, index);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_a_drop__invalid(void) {
	const size_t invalid_indices[3] = {
		a_size(array),
		a_size(array) + 1,
		73
	};
	data_t *got;
	size_t index;
	notice("tests a_drop -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("a_drop(array, %zu)", index);
		info("expected: (nil)");
		got = a_drop(array, index);
		info("got     : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

void test_a_swap__valid(void) {
	static int value = 777;
	int expected, got;
	size_t index;
	notice("test a_swap -- valid indices");
	index = 2;
	verbose("a_swap(array, %zu, &<%d>)", index, value);
	expected = VALUES[index];
	info("expected: %d", expected);
	got = *(int*)a_swap(array, index, &value);
	info("got     : %d", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_a_swap__invalid(void) {
	static int value = 42;
	const size_t invalid_indices[3] = {
		a_size(array),
		a_size(array) + 1,
		73
	};
	size_t index;
	data_t *got;
	notice("tests a_swap -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("a_swap(array, %zu, &<%d>)", index, value);
		info("expected: (nil)");
		got = a_swap(array, index, &value);
		info("got     : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_a_remove__found(void) {
	static const int value = 13; /* VALUES[3] */
	data_t *expected, *got;
	notice("test a_remove -- item found");
	verbose("a_remove(array, &<%d>, %s)", value, equal_as_ints_repr);
	expected = &(VALUES[3]);
	info("expected: %p", expected);
	got = a_remove(array, &value, equal_as_ints);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_a_remove__not_found(void) {
	static const int value = -42;
	data_t *got;
	notice("test a_remove -- item not found");
	verbose("a_remove(array, &<%d>, %s)", value, equal_as_ints_repr);
	info("expected: (nil)");
	got = a_remove(array, &value, equal_as_ints);
	info("got     : %p", got);
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	verbose("OK");
}

static void test_a_cond__found(void) {
	static const int value = 42; /* VALUES[1] */
	data_t *expected, *got;
	notice("test a_cond -- found");
	expected = VALUES + 1;
	verbose("a_cond(array, &<%d>, %s)", value, equal_as_ints_repr);
	info("expected: %p", expected);
	got = a_cond(array, &value, equal_as_ints);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_a_cond__not_found(void) {
	static const int value = 1024;
	data_t *got;
	notice("test a_cond -- not found");
	verbose("a_cond(array, &<%d>, %s)", value, equal_as_ints_repr);
	info("expected: (nil)");
	got = a_cond(array, &value, equal_as_ints);
	info("got     : %p", got);
	CUTE_assertEquals(got, NULL);
	verbose("OK");
}


void build_case_array(void) {
	case_array = CUTE_newTestCase("Tests for Array", 18);
	CUTE_setCaseBefore(case_array, init);
	CUTE_setCaseAfter(case_array, cleanup);
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_new__0_null));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_size__empty));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_append));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_size__full));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_get__valid));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_get__invalid));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_set__valid));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_set__invalid));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_add__middle));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_add__invalid));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_append__overflow));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_drop__valid));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_drop__invalid));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_swap__valid));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_swap__invalid));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_remove__found));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_remove__not_found));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_cond__found));
	CUTE_addCaseTest(case_array, CUTE_makeTest(test_a_cond__not_found));
}
