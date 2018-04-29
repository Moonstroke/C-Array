#include "array.h"
#include "array_funcs.h"

#include <cute.h>
#include <clog.h>
#include <stdbool.h>
#include <stdlib.h> /* for NULL */



/* The instance of test case */
CUTE_TestCase *case_array;



static Array *array;

static const unsigned int INT_ARRAY_SIZE = 10;
static int VALUES[] = {-1, 42, 666, 13, 28, -54, 0, 7 , 6, 5};

extern bool equal_as_ints(const data*, const data*);
extern const char equal_as_ints_repr[];

extern void print_as_int(const data*);


static void init(void) {
	info("array = a_new(%u)", INT_ARRAY_SIZE);
	array = a_new(INT_ARRAY_SIZE);
	CUTE_assertNotEquals(array, NULL);
	for(unsigned int i = 0; i < INT_ARRAY_SIZE; ++i) {
		a_add(array, i, &VALUES[i]);
	}
	info("OK\n");
}

static void cleanup(void) {
	a_free(array);
}


static void test_a_new__0_null(void) {
	unsigned int index;
	Array *got;
	info("test a_new -- size 0 => NULL array");
	index = 0;
	info("a_new(%u)", index);
	verbose("expected: (nil)");
	got = a_new(index);
	verbose("got     : %p", (void*)got);
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	info("OK\n");
}

static void test_a_size__empty(void) {
	Array *empty_array;
	unsigned int got;
	info("test a_size -- empty array");
	verbose("empty_array = a_new(%u)", INT_ARRAY_SIZE);
	empty_array = a_new(INT_ARRAY_SIZE);
	info("a_size(empty_array)");
	verbose("expected: 0");
	got = a_size(empty_array);
	verbose("got     : %u", got);
	a_free(empty_array);
	CUTE_assertEquals(got, 0);
	info("OK\n");
}

static void test_a_append(void) {
	Array *empty_array;
	data *param;
	int expected, got;
	info("test a_append");
	verbose("empty_array = a_new(%u)", INT_ARRAY_SIZE);
	empty_array = a_new(INT_ARRAY_SIZE);
	verbose("VALUES = [-1, 42, 666, 13, 28, -54, 0, 7, 6, 5]");
	for(unsigned int index = 0; index < INT_ARRAY_SIZE; ++index) {
		param = VALUES + index;
		info("a_append(array, %p)", param);
		expected = index;
		verbose("expected: %d", expected);
		got = a_append(empty_array, param);
		verbose("got     : %d", got);
		CUTE_assertEquals(got, expected);
		CUTE_assertNoError();
	}
	a_free(empty_array);
	info("OK\n");
}

static void test_a_size__full(void) {
	unsigned int expected, got;
	info("test a_size -- array full");
	info("a_size(array)");
	expected = INT_ARRAY_SIZE;
	verbose("expected: %u", expected);
	got = a_size(array);
	verbose("got     : %u", got);
	CUTE_assertEquals(got, expected);
	info("OK\n");
}

static void test_a_get__valid(void) {
	data *expected, *got;
	info("tests a_get -- valid indices");
	for(unsigned int index = 0; index < INT_ARRAY_SIZE; ++index) {
		info("a_get(array, %d)", index);
		expected = VALUES + index;
		verbose("expected: %p", expected);
		got = a_get(array, index);
		verbose("got     : %p", got);
		CUTE_assertEquals(got, expected);
		CUTE_assertNoError();
	}
	info("OK\n");
}

static void test_a_get__invalid(void) {
	const unsigned int invalid_indices[3] = {
		a_size(array),
		a_size(array) + 1,
		73 /* big "arbitrary" value */
	};
	unsigned int index;
	data *got;
	info("tests a_get -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		info("a_get(array, %u)", index);
		verbose("expected: (nil)");
		got = a_get(array, index);
		verbose("got     : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	info("OK\n");
}

static void test_a_set__valid(void) {
	static int extra = 64;
	data *const param = &extra;
	const unsigned int index = 7;
	info("test a_set -- valid index");
	info("a_set(array, %u, %p)", index, param);
	verbose("expected errno: 0");
	a_set(array, index, param);
	verbose("actual errno  : %d", errno);
	CUTE_assertNoError();
	info("OK\n");
}

static void test_a_set__invalid(void) {
	static int extra = 23;
	data *const param = &extra;
	const unsigned int invalid_indices[3] = {
		a_size(array),
		a_size(array) + 1,
		73 /* big "arbitrary" value */
	};
	unsigned int index;
	info("tests a_set -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		info("a_set(array, %u, %p)", index, param);
		verbose("expected errno: %d", ERANGE);
		a_set(array, index, param);
		verbose("actual errno  : %d", errno);
		CUTE_assertErrnoEquals(ERANGE);
	}
	info("OK\n");
}

static void test_a_add__invalid(void) {
	int value = 42;
	const unsigned int invalid_indices[3] = {
		a_size(array) + 1,
		a_size(array) + 2,
		73
	};
	int got;
	data *const param = &value;
	unsigned int index;
	info("tests a_add -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		info("a_add(array, %u, %p)", index, param);
		verbose("expected: -1");
		got = a_add(array, index, param);
		verbose("got     : %d", got);
		CUTE_assertEquals(got, -1);
		CUTE_assertErrnoEquals(ERANGE);
	}
	info("OK\n");
}

static void test_a_append__overflow(void) {
	static int extra = 73;
	int expected, got;
	data *const param = &extra;
	info("test a_append -- overflow size (=> realloc)");
	info("a_append(array, %p)", param);
	expected = INT_ARRAY_SIZE;
	verbose("expected: %d", expected);
	got = a_append(array, param);
	verbose("got     : %d", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	info("OK\n");
}

static void test_a_drop__valid(void) {
	const unsigned int index = 4;
	data *expected, *got;
	info("test a_drop -- valid index");
	info("a_drop(array, %u)", index);
	expected = VALUES + index;
	verbose("expected: %p", expected);
	got = a_drop(array, index);
	verbose("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	info("OK\n");
}

static void test_a_drop__invalid(void) {
	const unsigned int invalid_indices[3] = {
		a_size(array),
		a_size(array) + 1,
		73
	};
	data *got;
	unsigned int index;
	info("test a_drop -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		info("a_drop(array, %u)", index);
		verbose("expected: (nil)");
		got = a_drop(array, index);
		verbose("got     : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	info("OK\n");
}

void test_a_swap__valid(void) {
	static int extra = 777;
	data *const param = &extra;
	int expected, got;
	unsigned int index;
	info("test a_swap -- valid indices");
	index = 2;
	info("a_swap(array, %u, %p)", index, param);
	expected = VALUES[index];
	verbose("expected: %d", expected);
	got = *(int*)a_swap(array, index, param);
	verbose("got     : %d", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	info("OK\n");
}

static void test_a_swap__invalid(void) {
	int value = 42;
	const unsigned int invalid_indices[3] = {
		a_size(array),
		a_size(array) + 1,
		73
	};
	data *const param = &value;
	unsigned int index;
	data *got;
	info("tests a_swap -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		info("a_swap(array, %u, %p)", index, param);
		verbose("expected: (nil)");
		got = a_swap(array, index, param);
		verbose("got     : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	info("OK\n");
}

static void test_a_remove__found(void) {
	const int value = VALUES[3];
	const data *const param = &value;
	data *expected, *got;
	info("test a_remove -- item found");
	info("a_remove(array, *%d, %s)", value, equal_as_ints_repr);
	expected = VALUES + 3;
	verbose("expected: %p", expected);
	got = a_remove(array, param, equal_as_ints);
	verbose("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	info("OK\n");
}

static void test_a_remove__not_found(void) {
	const int value = -42;
	const data *const param = &value;
	data *got;
	info("test a_remove -- item not found");
	info("a_remove(array, *%d, %s)", value, equal_as_ints_repr);
	verbose("expected: (nil)");
	got = a_remove(array, param, equal_as_ints);
	verbose("got     : %p", got);
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	info("OK\n");
}

static void test_a_cond__found(void) {
	const int value = VALUES[1];
	const data *const param = &value;
	data *expected, *got;
	info("test a_cond -- found");
	expected = VALUES + 1;
	info("a_cond(array, *%d, %s)", *(int*)param, equal_as_ints_repr);
	verbose("expected: %p", expected);
	got = a_cond(array, param, equal_as_ints);
	verbose("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	info("OK\n");
}

static void test_a_cond__not_found(void) {
	static int value = 1024;
	data *const param = &value;
	data *got;
	info("test a_cond -- not found");
	info("a_cond(array, *%d, %s)", value, equal_as_ints_repr);
	verbose("expected: (nil)");
	got = a_cond(array, param, equal_as_ints);
	verbose("got     : %p", got);
	CUTE_assertEquals(got, NULL);
	info("OK\n");
}


void build_case_array(void) {
	case_array = CUTE_newTestCase("Tests for Array", 17);
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
