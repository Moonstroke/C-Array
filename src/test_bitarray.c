#include "bitarray.h"

#include <assert.h>
#include <log.h>
#include <stdbool.h>
#include <stdlib.h>



static BitArray *barray;

static const unsigned int BIT_ARRAY_SIZE = 10;
static bool values[] = {true, false, false, true, false, true, true, false, true, false};


static void init(void) {
	info("barray = ba_new(%u)", BIT_ARRAY_SIZE);
	barray = ba_new(BIT_ARRAY_SIZE);
	assert(barray != NULL);
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
	verbose("got     : %p", got);
	assert(got == NULL);
	info("OK\n");
}

static void test_ba_size(void) {
	unsigned int expected, got;
	info("test ba_size");
	info("ba_size(barray)");
	expected = BIT_ARRAY_SIZE;
	verbose("expected: ", expected);
	got = ba_size(barray);
	verbose("got     : ", got);
	assert(got == expected);
	info("OK\n");
}

static void test_ba_put__valid(void) {
	bool got;
	bool param;
	info("test ba_put -- valid indices");
	for(unsigned int index = 0; index < BIT_ARRAY_SIZE; ++index) {
		param = values[index];
		info("ba_put(barray, %u, %s)", index, param ? "true" : "false");
		verbose("expected: false");
		got = ba_put(barray, index, param);
		verbose("got     : %s", got ? "true" : "false");
		assert(got == false);
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
		assert(got == false);
	}
	info("OK\n");
}

static void test_ba_get__valid(void) {
	bool expected, got;
	info("test ba_get -- valid indices");
	for(unsigned int index = 0; index < BIT_ARRAY_SIZE; ++index) {
		info("ba_get(barray, %u)", index);
		expected = values[index];
		verbose("expected: %s", expected ? "true" : "false");
		got = ba_get(barray, index);
		verbose("got     : %s", got ? "true" : "false");
		assert(got == expected);
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
		assert(got == false);
	}
	info("OK\n");
}


void test_bitarray(void) {

	init();

	test_ba_new__0_null();

	test_ba_size();

	test_ba_put__valid();

	test_ba_put__invalid();

	test_ba_get__valid();

	test_ba_get__invalid();


	cleanup();
}
