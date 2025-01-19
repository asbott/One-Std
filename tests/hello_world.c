#define OSTD_IMPL
#define OSTD_NO_GRAPHICS
#include "../src/ostd.h"

int main(void) {
	int a = 5;
	int b = 2;
	print("a-b: %i\n", a-b);
	return 0;
}

