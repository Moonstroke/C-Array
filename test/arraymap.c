#include "arraymap.h"

#include <CUTE/cute.h>
#include <clog.h>
#include <stdlib.h> /* for NULL */



CUTE_TestCase *case_arraymap;


static ArrayMap *arraymap;

extern int cmp_as_ints(const key_t*, const key_t*);
extern const char cmp_as_ints_repr[];

static const unsigned int ARRAY_MAP_SIZE = 10;
static int KEYS[] = {1, 73, 42, 28, 34, 13, -20, 592, 8, 30};
static float VALUES[] = {3.1, 8.27, -55.9, 56.34, 7.6, 0.9, 7.1, 54.23, 21.5,
                         0.48};


static void init(void) {
	verbose("arraymap = am_new(%u, %s)", ARRAY_MAP_SIZE, cmp_as_ints_repr);
	arraymap = am_new(ARRAY_MAP_SIZE, cmp_as_ints);
	CUTE_assertNotEquals(arraymap, NULL);
	for(unsigned int i = 0; i < ARRAY_MAP_SIZE; ++i) {
		am_put(arraymap, &KEYS[i], &VALUES[i]);
	}
}

static void cleanup(void) {
	verbose("am_free(arraymap)");
	am_free(arraymap);
}


static void test_am_new__0_null(void) {
	ArrayMap *got;
	notice("test am_new -- size 0 => NULL arraymap");
	verbose("am_new(0, NULL)");
	info("expected: (nil)");
	got = am_new(0, cmp_as_ints);
	info("got     : %p", (void*)got); /* necessary cast because of GCC warning */
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	verbose("OK");
}

// TODO


void build_case_arraymap(void) {
	case_arraymap = CUTE_newTestCase("Tests for ArrayMap", 1);
	CUTE_setCaseBefore(case_arraymap, init);
	CUTE_setCaseAfter(case_arraymap, cleanup);
	CUTE_addCaseTest(case_arraymap ,CUTE_makeTest(test_am_new__0_null));
	// TODO
}
