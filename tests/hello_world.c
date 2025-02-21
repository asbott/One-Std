// Save compilation time by not compiling the graphics module
#define OSTD_NO_GRAPHICS
#define OSTD_IMPL
#include "../ostd_single_header.h"

int main(void) {
	print("Hello, World!\n");
	return 0;
}

