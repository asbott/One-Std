
typedef struct string {
    u64 count;
    u8 *data;
} string;

u64 c_style_strlen(const char *s) {
    const char *p = s;
    while (*p++) {}
    return (u64)(p-s-1);
}
#define STR(c) ((string){ c_style_strlen(c), (u8*)c })



/*u64 format_string_to_buffer(char* buffer, u64 count, const char* fmt, va_list args) {
	if (!buffer) count = UINT64_MAX;
    const char* p = fmt;
    char* bufp = buffer;
    while (*p != '\0' && (bufp - buffer) < count - 1) {
        if (*p == '%') {
            p += 1;
            if (*p == 's') {
            	// We replace %s formatting with our fixed length string
                p += 1;
                string s = va_arg(args, string);
                assert(s.count < (1024ULL*1024ULL*1024ULL*256ULL), "Ypu passed something else than a fixed-length 'string' to %%s. Maybe you passed a char* and should do %%cs instead?");
                for (u64 i = 0; i < s.count && (bufp - buffer) < count - 1; i++) {
                	if (buffer) *bufp = s.data[i];
                    bufp += 1;
                }
            } else if (*p == 'c' && *(p+1) == 's') {
            	// We extend the standard formatting and add %cs so we can format c strings if we need to
                p += 2;
                char* s = va_arg(args, char*);
                u64 len = 0;
                while (*s != '\0' && (bufp - buffer) < count - 1) {
                	assert(len < (1024ULL*1024ULL*1024ULL*1ULL), "The argument passed to %%cs is either way too big, missing null-termination or simply not a char*.");
                	if (buffer) {
                		*bufp = *s;
                	}
                	s += 1;
                    bufp += 1;
                    len += 1;
                    assert(len < (1024ULL*1024ULL*1024ULL*1ULL), "The argument passed to %%cs is either way too big, missing null-termination or simply not a char*.");
                }
            } else {
                // Fallback to standard vsnprintf
                char temp_buffer[512];
                char format_specifier[64];
                int specifier_len = 0;
                format_specifier[specifier_len++] = '%';

                while (*p != '\0' && strchr("diuoxXfFeEgGaAcCpn%", *p) == NULL) {
                    format_specifier[specifier_len++] = *p++;
                }
                if (*p != '\0') {
                    format_specifier[specifier_len++] = *p++;
                }
                format_specifier[specifier_len] = '\0';

                int temp_len = vsnprintf(temp_buffer, sizeof(temp_buffer), format_specifier, args);
                switch (format_specifier[specifier_len - 1]) {
                    case 'd': case 'i': va_arg(args, int); break;
                    case 'u': case 'x': case 'X': case 'o': va_arg(args, unsigned int); break;
                    case 'f': case 'F': case 'e': case 'E': case 'g': case 'G': case 'a': case 'A': va_arg(args, double); break;
                    case 'c': va_arg(args, int); break;
                    case 's': va_arg(args, char*); break;
                    case 'p': va_arg(args, void*); break;
                    case 'n': va_arg(args, int*); break;
                    default: break;
                }

                if (temp_len < 0) {
                    return -1; // Error in formatting
                }

                for (int i = 0; i < temp_len && (bufp - buffer) < count - 1; i++) {
                    if (buffer) *bufp = temp_buffer[i];
                    bufp += 1;
                }
            }
        } else {
            if (buffer) {
                *bufp = *p;
            }
            bufp += 1;
            p += 1;
        }
    }
    if (buffer)  *bufp = '\0';
    
    return bufp - buffer;
}
u64 format_string_to_buffer_va(char* buffer, u64 count, const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	u64 r = format_string_to_buffer(buffer, count, fmt, args);
	va_end(args);
	return r;
}*/