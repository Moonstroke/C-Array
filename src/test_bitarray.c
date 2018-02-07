#include "bitarray.h"

#include <assert.h>
#include <log.h>
#include <stdlib.h>



static BitArray *barray;

static const unsigned int size = 10;


static void init(void) {
	info("barray = ba_new(%u)", size);
	barray = ba_new(size);
	assert(barray != NULL);
	info("OK\n");
}

static void cleanup(void) {
	info("ba_free(barray)");
	ba_free(barray);
	info("Bye\n");
}

static void test_ba_new__0_null(void) {
	BitArray *expected, *got;
	info("test ba_new -- size of 0 => NULL bit array");
	info("ba_new(0)");
	expected = NULL;
	verbose("expected: %p", expected);
	got = ba_new(0);
	verbose("got     : %p", got);
	assert(got == expected);
	info("OK\n");
}

void test_bitarray(void) {

	init();

	test_ba_new__0_null();


	cleanup();
}
