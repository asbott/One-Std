
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