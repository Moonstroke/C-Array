#include "array.h"
#include "array_funcs.h"

#include <CUTE/cute.h>
#include <clog.h> /* for logging macros */
#include <stdlib.h> /* for NULL */



/* The instance of test case */
CUTE_TestCase *case_array;



static Array *array;

static const unsigned int INT_ARRAY_SIZE = 10;
static int VALUES[] = {-1, 42, 666, 13, 28, -54, 0, 7 , 6, 5};


extern _Bool equal_as_ints(const data_t*, const data_t*);
extern const char equal_as_ints_repr[];

extern void print_as_int(const data_t*);


static void init(void) {
	verbose("array = a_new(%u)", INT_ARRAY_SIZE);
	array = a_new(INT_ARRAY_SIZE);
	CUTE_assertNotEquals(array, NULL);
	for(unsigned int i = 0; i < INT_ARRAY_SIZE; ++i) {
		a_add(array, i, &VALUES[i]);
	}
}

static void cleanup(void) {
	verbose("a_free(array)");
	a_free(array);
}


static void test_a_new__0_null(void) {
	unsigned int index;
	Array *got;
	notice("test a_new -- size 0 => NULL array");
	index = 0;
	verbose("a_new(%u)", index);
	info("expected: (nil)");
	got = a_new(index);
	info("got     : %p", (void*)got); /* necessary cast because of GCC warning */
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	verbose("OK");
}

static void test_a_size__empty(void) {
	Array *empty_array;
	unsigned int got;
	notice("test a_size -- empty array");
	verbose("empty_array = a_new(%u)", INT_ARRAY_SIZE);
	empty_array = a_new(INT_ARRAY_SIZE);
	verbose("a_size(empty_array)");
	info("expected: 0");
	got = a_size(empty_array);
	info("got     : %u", got);
	a_free(empty_array);
	CUTE_assertEquals(got, 0);
	verbose("OK");
}

static void test_a_append(void) {
	Array *empty_array;
	data_t *param;
	int expected, got;
	notice("test a_append");
	verbose("empty_array = a_new(%u)", INT_ARRAY_SIZE);
	empty_array = a_new(INT_ARRAY_SIZE);
	verbose("VALUES = [-1, 42, 666, 13, 28, -54, 0, 7, 6, 5]");
	for(unsigned int index = 0; index < INT_ARRAY_SIZE; ++index) {
		param = VALUES + index;
		verbose("a_append(array, %p)", param);
		expected = index;
		info("expected: %d", expected);
		got = a_append(empty_array, param);
		info("got     : %d", got);
		CUTE_assertEquals(got, expected);
		CUTE_assertNoError();
	}
	a_free(empty_array);
	verbose("OK");
}

static void test_a_size__full(void) {
	unsigned int expected, got;
	notice("test a_size -- array full");
	verbose("a_size(array)");
	expected = INT_ARRAY_SIZE;
	info("expected: %u", expected);
	got = a_size(array);
	info("got     : %u", got);
	CUTE_assertEquals(got, expected);
	verbose("OK");
}

static void test_a_get__valid(void) {
	data_t *expected, *got;
	notice("tests a_get -- valid indices");
	for(unsigned int index = 0; index < INT_ARRAY_SIZE; ++index) {
		verbose("a_get(array, %d)", index);
		expected = VALUES + index;
		info("expected: %p", expected);
		got = a_get(array, index);
		info("got     : %p", got);
		CUTE_assertEquals(got, expected);
		CUTE_assertNoError();
	}
	verbose("OK");
}

static void test_a_get__invalid(void) {
	const unsigned int invalid_indices[3] = {
		a_size(array),
		a_size(array) + 1,
		73 /* big "arbitrary" value */
	};
	unsigned int index;
	data_t *got;
	notice("tests a_get -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("a_get(array, %u)", index);
		info("expected: (nil)");
		got = a_get(array, index);
		info("got     : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_a_set__valid(void) {
	static int extra = 64;
	data_t *const param = &extra;
	const unsigned int index = 7;
	notice("test a_set -- valid index");
	verbose("a_set(array, %u, %p)", index, param);
	info("expected errno: 0");
	a_set(array, index, param);
	info("actual errno  : %d", errno);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_a_set__invalid(void) {
	static int extra = 23;
	data_t *const param = &extra;
	const unsigned int invalid_indices[3] = {
		a_size(array),
		a_size(array) + 1,
		73 /* big "arbitrary" value */
	};
	unsigned int index;
	notice("tests a_set -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("a_set(array, %u, %p)", index, param);
		info("expected errno: %d", ERANGE);
		a_set(array, index, param);
		info("actual errno  : %d", errno);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_a_add__invalid(void) {
	int value = 42;
	const unsigned int invalid_indices[3] = {
		a_size(array) + 1,
		a_size(array) + 2,
		73
	};
	int got;
	data_t *const param = &value;
	unsigned int index;
	notice("tests a_add -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("a_add(array, %u, %p)", index, param);
		info("expected: -1");
		got = a_add(array, index, param);
		info("got     : %d", got);
		CUTE_assertEquals(got, -1);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_a_append__overflow(void) {
	static int extra = 73;
	int expected, got;
	data_t *const param = &extra;
	notice("test a_append -- overflow size (=> realloc)");
	verbose("a_append(array, %p)", param);
	expected = INT_ARRAY_SIZE;
	info("expected: %d", expected);
	got = a_append(array, param);
	info("got     : %d", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_a_drop__valid(void) {
	const unsigned int index = 4;
	data_t *expected, *got;
	notice("test a_drop -- valid index");
	verbose("a_drop(array, %u)", index);
	expected = VALUES + index;
	info("expected: %p", expected);
	got = a_drop(array, index);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_a_drop__invalid(void) {
	const unsigned int invalid_indices[3] = {
		a_size(array),
		a_size(array) + 1,
		73
	};
	data_t *got;
	unsigned int index;
	notice("tests a_drop -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("a_drop(array, %u)", index);
		info("expected: (nil)");
		got = a_drop(array, index);
		info("got     : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

void test_a_swap__valid(void) {
	static int extra = 777;
	data_t *const param = &extra;
	int expected, got;
	unsigned int index;
	notice("test a_swap -- valid indices");
	index = 2;
	verbose("a_swap(array, %u, %p)", index, param);
	expected = VALUES[index];
	info("expected: %d", expected);
	got = *(int*)a_swap(array, index, param);
	info("got     : %d", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_a_swap__invalid(void) {
	int value = 42;
	const unsigned int invalid_indices[3] = {
		a_size(array),
		a_size(array) + 1,
		73
	};
	data_t *const param = &value;
	unsigned int index;
	data_t *got;
	notice("tests a_swap -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("a_swap(array, %u, %p)", index, param);
		info("expected: (nil)");
		got = a_swap(array, index, param);
		info("got     : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_a_remove__found(void) {
	const int value = VALUES[3];
	const data_t *const param = &value;
	data_t *expected, *got;
	notice("test a_remove -- item found");
	verbose("a_remove(array, *%d, %s)", value, equal_as_ints_repr);
	expected = VALUES + 3;
	info("expected: %p", expected);
	got = a_remove(array, param, equal_as_ints);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_a_remove__not_found(void) {
	const int value = -42;
	const data_t *const param = &value;
	data_t *got;
	notice("test a_remove -- item not found");
	verbose("a_remove(array, *%d, %s)", value, equal_as_ints_repr);
	info("expected: (nil)");
	got = a_remove(array, param, equal_as_ints);
	info("got     : %p", got);
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	verbose("OK");
}

static void test_a_cond__found(void) {
	const int value = VALUES[1];
	const data_t *const param = &value;
	data_t *expected, *got;
	notice("test a_cond -- found");
	expected = VALUES + 1;
	verbose("a_cond(array, *%d, %s)", *(int*)param, equal_as_ints_repr);
	info("expected: %p", expected);
	got = a_cond(array, param, equal_as_ints);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_a_cond__not_found(void) {
	static int value = 1024;
	data_t *const param = &value;
	data_t *got;
	notice("test a_cond -- not found");
	verbose("a_cond(array, *%d, %s)", value, equal_as_ints_repr);
	info("expected: (nil)");
	got = a_cond(array, param, equal_as_ints);
	info("got     : %p", got);
	CUTE_assertEquals(got, NULL);
	verbose("OK");
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
