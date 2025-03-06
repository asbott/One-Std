
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif

// Save compilation time by not compiling the graphics module
#define OSTD_HEADLESS
#define OSTD_IMPL
#include "../ostd_single_header.h"

int main(void) {
	print("Hello, World!\n");
	return 0;
}

