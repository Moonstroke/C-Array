#include <clog.h> /* for clog_init */
#include <CUTE/cute.h>
#include <stdbool.h>
#include <stdio.h> /* for printf */
#include <stdlib.h> /* for EXIT_SUCCESS */

#include "cods.h"



/* Helper functions */
int cmp_as_ints(const data_t *const e1, const data_t *const e2) {
	CUTE_runTimeAssert(e1 != NULL && e2 != NULL);
	const int i1 = *(int*)e1, i2 = *(int*)e2;
	return (i1 > i2) - (i1 < i2);
}
const char cmp_as_ints_repr[] = "(int *i, int *j) -> (*i > *j) - (*i < *j)";

bool equal_as_ints(const data_t *const e1, const data_t *const e2) {
	return cmp_as_ints(e1, e2) == 0;
}
const char equal_as_ints_repr[] = "(int *i, int *j) -> *i == *j";

void print_as_int(const data_t *const e) {
	if(e)
		printf("%d", *(int*)e);
	else
		printf("(null)");
}


/* Declarations of the tests cases */
extern CUTE_TestCase *case_fixedarray;
extern void build_case_fixedarray(void);

extern CUTE_TestCase *case_array;
extern void build_case_array(void);

extern CUTE_TestCase *case_bitarray;
extern void build_case_bitarray(void);

extern CUTE_TestCase *case_linkedlist;
extern void build_case_linkedlist(void);

extern CUTE_TestCase *case_sortedarray;
extern void build_case_sortedarray(void);


int main(void) {

	const CUTE_RunResults **results;

	clog_init(CLOG_FORMAT_TEXT, CLOG_ATTR_FUNC | CLOG_ATTR_COLORED);
	build_case_fixedarray();
	build_case_array();
	build_case_bitarray();
	build_case_linkedlist();
	build_case_sortedarray();

	CUTE_prepareTestSuite(5, case_fixedarray, case_array, case_bitarray,
	                      case_linkedlist, case_sortedarray);

	results = CUTE_runTestSuite();

	CUTE_printResults(5, results);


	return EXIT_SUCCESS;
}
