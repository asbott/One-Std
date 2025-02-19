#if 0
#include "ostd.h" // For syntax highlighting.
#endif

unit_local inline bool is_alpha(u8 c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
unit_local inline bool is_digit(u8 c) {
	return (c >= '0' && c <= '9');
}
unit_local inline bool is_whitespace(u8 c) {
	return c == '\n' || c == '\r' || c == '\t' || c == ' ';
}


unit_local inline size_t align_next(size_t n, size_t align) {
    return ((n + align - 1) / align) * align;
}

