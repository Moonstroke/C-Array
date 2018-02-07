#include <log.h>
#include <stdlib.h> /* for EXIT_SUCCESS */

/* Declarations of the tests suites */
extern void test_array(void);
extern void test_fixedarray(void);
extern void test_linkedlist(void);
extern void test_bitarray(void);

int main(void) {
	info("Launching tests for Array...\n");
	test_array();
	info("\nTests for Array ended correctly.\n\n");

	info("Launching tests for FixedArray...\n");
	test_fixedarray();
	info("\nTests for FixedArray ended correctly.\n\n");

	info("Launching tests for LinkedList...\n");
	test_linkedlist();
	info("Tests for LinkedList ended correctly.\n\n");

	info("Launching tests for BitArray...\n");
	test_bitarray();
	info("Tests for BitArray ended correctly.\n\n");

	info("End of tests.");
	return EXIT_SUCCESS;
}
