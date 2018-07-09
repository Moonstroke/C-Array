#include "bitarray.h"
#include "bitarray_funcs.h"

#include <CUTE/cute.h>
#include <clog.h> /* for logging macros */
#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for NULL */



/* The instance of test case */
CUTE_TestCase *case_bitarray;



static BitArray *barray;

static const size_t BIT_ARRAY_SIZE = 10;
static bool VALUES[] = {true, false, false, true, false, true, true, false, true, false};
static size_t COUNT = 5;


static void init(void) {
	verbose("barray = ba_new(%zu)", BIT_ARRAY_SIZE);
	barray = ba_new(BIT_ARRAY_SIZE);
	CUTE_assertNotEquals(barray, NULL);
	for(size_t i = 0; i < BIT_ARRAY_SIZE; ++i) {
		ba_put(barray, i, VALUES[i]);
	}
}

static void cleanup(void) {
	verbose("ba_free(barray)");
	ba_free(barray);
}

static void test_ba_new__0_null(void) {
	BitArray *got;
	notice("test ba_new -- size of 0 => NULL bit array");
	verbose("ba_new(0)");
	info("expected: (nil)");
	got = ba_new(0);
	info("got     : %p", (void*)got); /* necessary cast because of GCC warning */
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	verbose("OK");
}

static void test_ba_size(void) {
	size_t got;
	notice("test ba_size");
	verbose("ba_size(barray)");
	info("expected: %zu", BIT_ARRAY_SIZE);
	got = ba_size(barray);
	info("got     : %zu", got);
	CUTE_assertEquals(got, BIT_ARRAY_SIZE);
	verbose("OK");
}

static void test_ba_put__valid(void) {
	bool expected, got;
	bool param;
	notice("test ba_put -- valid indices");
	for(size_t index = 0; index < BIT_ARRAY_SIZE; ++index) {
		param = VALUES[index];
		verbose("ba_put(barray, %zu, %s)", index, BOOL_REPR(param));
		expected = VALUES[index];
		info("expected: %s", BOOL_REPR(expected));
		got = ba_put(barray, index, param);
		info("got     : %s", BOOL_REPR(got));
		CUTE_assertEquals(got, expected);
		CUTE_assertNoError();
	}
	verbose("OK");
}

static void test_ba_put__invalid(void) {
	const size_t invalid_indices[3] = {
		BIT_ARRAY_SIZE,
		BIT_ARRAY_SIZE + 1,
		42
	};
	bool got;
	size_t index;
	notice("test ba_put -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("ba_put(barray, %zu, false)", index);
		info("expected: false");
		got = ba_put(barray, index, false);
		info("got     : %s", BOOL_REPR(got));
		CUTE_assertEquals(got, false);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_ba_get__valid(void) {
	bool expected, got;
	notice("test ba_get -- valid indices");
	for(size_t index = 0; index < BIT_ARRAY_SIZE; ++index) {
		verbose("ba_get(barray, %zu)", index);
		expected = VALUES[index];
		info("expected: %s", BOOL_REPR(expected));
		got = ba_get(barray, index);
		info("got     : %s", BOOL_REPR(got));
		CUTE_assertEquals(got, expected);
		CUTE_assertNoError();
	}
	verbose("OK");
}

static void test_ba_get__invalid(void) {
	const size_t invalid_indices[3] = {
		BIT_ARRAY_SIZE,
		BIT_ARRAY_SIZE + 1,
		8 * BIT_ARRAY_SIZE
	};
	size_t index;
	bool got;
	notice("test ba_get -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("ba_get(barray, %zu)", index);
		info("expected: false");
		got = ba_get(barray, index);
		info("got     : %s", BOOL_REPR(got));
		CUTE_assertEquals(got, false);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}


static void test_ba_count(void) {
	size_t expected, got;
	notice("test ba_count");
	verbose("ba_count(barray)");
	expected = COUNT;
	info("expected: %zu", expected);
	got = ba_count(barray);
	info("got     : %zu", got);
	CUTE_assertEquals(got, expected);
	verbose("OK");
}


void build_case_bitarray(void) {
	case_bitarray = CUTE_newTestCase("Tests for BitArray", 7);
	CUTE_setCaseBefore(case_bitarray, init);
	CUTE_setCaseAfter(case_bitarray, cleanup);
	CUTE_addCaseTest(case_bitarray, CUTE_makeTest(test_ba_new__0_null));
	CUTE_addCaseTest(case_bitarray, CUTE_makeTest(test_ba_size));
	CUTE_addCaseTest(case_bitarray, CUTE_makeTest(test_ba_put__valid));
	CUTE_addCaseTest(case_bitarray, CUTE_makeTest(test_ba_put__invalid));
	CUTE_addCaseTest(case_bitarray, CUTE_makeTest(test_ba_get__valid));
	CUTE_addCaseTest(case_bitarray, CUTE_makeTest(test_ba_get__invalid));
	CUTE_addCaseTest(case_bitarray, CUTE_makeTest(test_ba_count));
}
