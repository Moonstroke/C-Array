#include "fixedarray.h"
#include "fixedarray_funcs.h"

#include <cute.h>
#include <clog.h>
#include <stdbool.h>
#include <stdlib.h> /* for NULL */



/* The instance of test case */
CUTE_TestCase *case_fixedarray;



static FixedArray *farray;

static const unsigned int INT_FIXED_ARRAY_SIZE = 8;
static int VALUES[] = {1, 42, 6, 3, 27, 9, 55, 700};


extern bool equal_as_ints(const data*, const data*);
extern const char equal_as_ints_repr[];

extern void print_as_int(const data*);


static void init(void) {
	info("farray = fa_new(%u)", INT_FIXED_ARRAY_SIZE);
	farray = fa_new(INT_FIXED_ARRAY_SIZE);
	CUTE_assertNotEquals(farray, NULL);
	for(unsigned int i = 0; i < INT_FIXED_ARRAY_SIZE; ++i) {
		fa_set(farray, i, &VALUES[i]);
	}
	info("OK\n");
}

static void cleanup(void) {
	fa_free(farray);
}


static void test_fa_new__0_null(void) {
	FixedArray *got;
	info("test fa_new -- size of 0 => NULL");
	info("test fa_new(0)");
	verbose("expected: (nil)");
	got = fa_new(0);
	verbose("got     : %p", (void*)got);
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	info("OK\n");
}

static void test_fa_size(void) {
	unsigned int got;
	info("test fa_size");
	info("fa_size(farray)");
	verbose("expected: %u", INT_FIXED_ARRAY_SIZE);
	got = fa_size(farray);
	verbose("got     : %u", got);
	CUTE_assertEquals(got, INT_FIXED_ARRAY_SIZE);
	info("OK\n");
}

static void test_fa_set__valid(void) {
	data *param;
	info("test fa_set -- valid indices");
	for(unsigned int index = 0; index < INT_FIXED_ARRAY_SIZE; ++index) {
		param = VALUES + index;
		info("fa_set(farray, %u, %p)", index, param);
		fa_set(farray, index, param);
		CUTE_assertNoError();
	}
	info("OK\n");
}

static void test_fa_set__invalid(void) {
	static int extra_value = 7;
	data *const param = &extra_value;
	const unsigned int invalid_indices[3] = {
		INT_FIXED_ARRAY_SIZE,
		INT_FIXED_ARRAY_SIZE + 1,
		3 * INT_FIXED_ARRAY_SIZE
	};
	unsigned int index;
	info("test fa_set -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		info("fa_set(farray, %u, %p)", index, param);
		verbose("expected errno: %d", ERANGE);
		fa_set(farray, index, param);
		verbose("got      errno: %d", errno);
		CUTE_assertErrnoEquals(ERANGE);
	}
	info("OK\n");
}

static void test_fa_get__valid(void) {
	data *expected, *got;
	info("test fa_get -- valid indices");
	for(unsigned int index = 0; index < INT_FIXED_ARRAY_SIZE; ++index) {
		info("fa_get(farray, %u)", index);
		expected = VALUES + index;
		verbose("expected: %p", expected);
		got = fa_get(farray, index);
		verbose("got     : %p", got);
		CUTE_assertEquals(got, expected);
		CUTE_assertNoError();
	}
	info("OK\n");
}

static void test_fa_get__invalid(void) {
	const unsigned int invalid_indices[3] = {
		INT_FIXED_ARRAY_SIZE,
		INT_FIXED_ARRAY_SIZE + 1,
		100
	};
	data *got;
	unsigned int index;
	info("test fa_get -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		info("fa_get(farray, %u)", index);
		verbose("expected : (nil)");
		got = fa_get(farray, index);
		verbose("got      : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	info("OK\n");
}

static void test_fa_unset__valid(void) {
	const unsigned int index = 5;
	data *expected, *got;
	info("test fa_unset -- valid index");
	info("fa_unset(farray, %u)", index);
	expected = VALUES + index;
	verbose("expected: %p", expected);
	got = fa_unset(farray, index);
	verbose("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	info("OK\n");
}

static void test_fa_unset__invalid(void) {
	const unsigned int invalid_indices[3] = {
		INT_FIXED_ARRAY_SIZE,
		INT_FIXED_ARRAY_SIZE + 1,
		43
	};
	data *got;
	unsigned int index;
	info("test fa_unset -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		info("fa_unset(farray, %u)", index);
		verbose("expected : (nil)");
		got = fa_unset(farray, index);
		verbose("got      : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	info("OK\n");
}

static void test_fa_count(void) {
	const unsigned int index = 3;
	unsigned int expected, got;
	info("test fa_count");
	verbose("fa_unset(farray, %u)", index);
	fa_unset(farray, index);
	info("fa_count(farray)");
	expected = INT_FIXED_ARRAY_SIZE - 1;
	verbose("expected: %u", expected);
	got = fa_count(farray);
	verbose("got     : %u", got);
	CUTE_assertEquals(got, expected);
	info("OK\n");
}

static void test_fa_put__valid(void) {
	static int extra = 33;
	const unsigned int index = 4;
	data *const param = &extra;
	int expected, got;
	verbose("fa_unset(farray, %u)", index);
	fa_unset(farray, index);
	info("test fa_put(farray, %p)", param);
	expected = index;
	verbose("expected: %d", expected);
	got = fa_put(farray, param);
	verbose("got     : %d", got);
	CUTE_assertEquals(got, expected);
	info("OK\n");
}

static void test_fa_put__invalid(void) {
	int extra = 7;
	data *const param = &extra;
	int got;
	info("test fa_put -- invalid (array is full)");
	info("fa_put(farray, %p)", param);
	verbose("expected: -1");
	got = fa_put(farray, param);
	verbose("got     : %d", got);
	CUTE_assertEquals(got, -1);
	info("OK\n");
}

static void test_fa_cond__valid(void) {
	static int test_val = 55;
	data *const param = &test_val;
	data *expected, *got;
	info("test fa_cond -- valid element value: %d", test_val);
	info("fa_cond(farray, %s, %p)", equal_as_ints_repr, param);
	expected = VALUES + 6;
	verbose("expected: %p", expected);
	got = fa_cond(farray, equal_as_ints, param);
	verbose("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	info("OK\n");
}

static void test_fa_cond__null(void) {
	const unsigned int index = 5;
	data *const param = VALUES + index;
	data *expected, *got;
	info("test fa_cond -- NULL as function (compare addresses)");
	info("fa_cond(farray, (nil), %p)", param);
	expected = VALUES + index;
	verbose("expected: %p", expected);
	got = fa_cond(farray, NULL, param);
	verbose("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	info("OK\n");
}

static void test_fa_cond__invalid(void) {
	static int test_val = 83;
	data *const param = &test_val;
	data *got;
	info("test fa_cond -- invalid value: %d", test_val);
	info("fa_cond(farray, %s, %p)", equal_as_ints_repr, param);
	verbose("expected: (nil)");
	got = fa_cond(farray, equal_as_ints, param);
	verbose("got     : %p", got);
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	info("OK\n");
}

static void test_fa_remove__valid(void) {
	static int test_val = 6;
	data *const param = &test_val;
	data *expected, *got;
	info("test fa_remove -- valid element value: %d", test_val);
	info("fa_remove(farray, %s, %p)", equal_as_ints_repr, param);
	expected = VALUES + 2;
	verbose("expected: %p", expected);
	got = fa_cond(farray, equal_as_ints, param);
	verbose("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	info("OK\n");
}

static void test_fa_remove__null(void) {
	const unsigned int index = 5;
	data *const param = VALUES + index;
	data *expected, *got;
	info("test fa_remove -- NULL as function (compare addresses)");
	info("fa_remove(farray, (nil), %p)", param);
	expected = VALUES + index;
	verbose("expected: %p", expected);
	got = fa_cond(farray, NULL, param);
	verbose("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	info("OK\n");
}

static void test_fa_remove__invalid(void) {
	static int test_val = 37;
	data *const param = &test_val;
	data *got;
	info("test fa_remove -- invalid element value: %d", test_val);
	info("fa_remove(farray, %s, %p)", equal_as_ints_repr, param);
	verbose("expected: (nil)");
	got = fa_cond(farray, equal_as_ints, param);
	verbose("got     : %p", got);
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	info("OK\n");
}

static void inc(data *const v) {
	++*(int*)v;
}
static const char inc_repr[] = "(int i) {++i;}";
static void test_fa_each(void) {
	info("test fa_each");
	info("fa_each(farray, %s)", inc_repr);
	fa_each(farray, inc);
	verbose("Checking array elements...");
	for(unsigned int i = 0; i < INT_FIXED_ARRAY_SIZE; ++i) {
		CUTE_assertEquals(*(int*)fa_get(farray, i), VALUES[i]);
		verbose("OK for %u", i);
	}
	info("OK\n");
}


void build_case_fixedarray(void) {
	case_fixedarray = CUTE_newTestCase("Tests for FixedArray", 18);
	CUTE_setCaseBefore(case_fixedarray, init);
	CUTE_setCaseAfter(case_fixedarray, cleanup);
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_new__0_null));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_size));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_set__valid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_set__invalid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_get__valid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_get__invalid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_unset__valid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_unset__invalid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_count));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_put__valid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_put__invalid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_cond__valid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_cond__null));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_cond__invalid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_remove__valid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_remove__null));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_remove__invalid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_each));
}
