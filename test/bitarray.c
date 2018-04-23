#include "bitarray.h"
#include "bitarray_funcs.h"

#include <cute.h>
#include <errno.h> /* for errno, EINVAL, ERANGE */
#include <clog.h>
#include <stdbool.h>
#include <stdlib.h>



extern int errno;


/* The instance of test case */
CUTE_TestCase *case_bitarray;



static BitArray *barray;

static const unsigned int BIT_ARRAY_SIZE = 10;
static bool VALUES[] = {true, false, false, true, false, true, true, false, true, false};
static unsigned int COUNT = 5;


static void init(void) {
	info("barray = ba_new(%u)", BIT_ARRAY_SIZE);
	barray = ba_new(BIT_ARRAY_SIZE);
	CUTE_runTimeAssert(barray != NULL);
	for(unsigned int i = 0; i < BIT_ARRAY_SIZE; ++i) {
		ba_put(barray, i, VALUES[i]);
	}
	info("OK\n");
}

static void cleanup(void) {
	info("ba_free(barray)");
	ba_free(barray);
	info("Bye\n");
}

static void test_ba_new__0_null(void) {
	BitArray *got;
	info("test ba_new -- size of 0 => NULL bit array");
	info("ba_new(0)");
	verbose("expected: (nil)");
	got = ba_new(0);
	verbose("got     : %p", (void*)got);
	CUTE_assertEquals(got, NULL);
	CUTE_assertEquals(errno, EINVAL);
	info("OK\n");
}

static void test_ba_size(void) {
	unsigned int got;
	info("test ba_size");
	info("ba_size(barray)");
	verbose("expected: %u", BIT_ARRAY_SIZE);
	got = ba_size(barray);
	verbose("got     : %u", got);
	CUTE_assertEquals(got, BIT_ARRAY_SIZE);
	info("OK\n");
}

static void test_ba_put__valid(void) {
	bool got;
	bool param;
	info("test ba_put -- valid indices");
	for(unsigned int index = 0; index < BIT_ARRAY_SIZE; ++index) {
		param = VALUES[index];
		info("ba_put(barray, %u, %s)", index, param ? "true" : "false");
		verbose("expected: false");
		got = ba_put(barray, index, param);
		verbose("got     : %s", got ? "true" : "false");
		CUTE_assertEquals(got, false);
		CUTE_assertEquals(errno, 0);
	}
	info("OK\n");
}

static void test_ba_put__invalid(void) {
	const unsigned int invalid_indices[3] = {
		BIT_ARRAY_SIZE,
		BIT_ARRAY_SIZE + 1,
		42
	};
	bool got;
	unsigned int index;
	info("test ba_put -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		info("ba_put(barray, %u, false)", index);
		verbose("expected: false");
		got = ba_put(barray, index, false);
		verbose("got     : %s", got ? "true" : "false");
		CUTE_assertEquals(got, false);
		CUTE_assertEquals(errno, ERANGE);
	}
	info("OK\n");
}

static void test_ba_get__valid(void) {
	bool expected, got;
	info("test ba_get -- valid indices");
	for(unsigned int index = 0; index < BIT_ARRAY_SIZE; ++index) {
		info("ba_get(barray, %u)", index);
		expected = VALUES[index];
		verbose("expected: %s", expected ? "true" : "false");
		got = ba_get(barray, index);
		verbose("got     : %s", got ? "true" : "false");
		CUTE_assertEquals(got, expected);
		CUTE_assertEquals(errno, 0);
	}
	info("OK\n");
}

static void test_ba_get__invalid(void) {
	const unsigned int invalid_indices[3] = {
		BIT_ARRAY_SIZE,
		BIT_ARRAY_SIZE + 1,
		8 * BIT_ARRAY_SIZE
	};
	unsigned int index;
	bool got;
	info("test ba_get -- invalid indices");
	for(unsigned int i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		info("ba_get(barray, %u)", index);
		verbose("expected = false");
		got = ba_get(barray, index);
		CUTE_assertEquals(got, false);
		CUTE_assertEquals(errno, ERANGE);
	}
	info("OK\n");
}


static void test_ba_count(void) {
	unsigned int expected, got;
	info("test ba_count");
	info("ba_count(barray)");
	expected = COUNT;
	verbose("expected: %u", expected);
	got = ba_count(barray);
	verbose("got     : %u", got);
	CUTE_assertEquals(got, expected);
	info("OK\n");
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
