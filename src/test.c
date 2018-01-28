#include <log.h>
#include <stdlib.h> /* for EXIT_SUCCESS */

/* Declarations of the tests suites */
extern void test_array(void);

int main(void) {
	info("Launching tests for Array...\n");
	test_array();
	info("\nTests for Array ended correctly.\n\n");

	info("End of tests.");
	return EXIT_SUCCESS;
}
