#if 0
#include "ostd.h" // For syntax highlighting.
#endif

typedef struct string {
    u64 count;
    u8 *data;

} string;

unit_local inline u64 c_style_strlen(const char *s) {
    const char *p = s;
    while (*p++) {}
    return (u64)(p-s-1);
}
unit_local inline u64 c_style_strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++;
        b++;
    }
    return (u64)(*a - *b);
}


#define STR(c) ((string){ c_style_strlen((const char*)c), (u8*)(uintptr)(const void*)(c) })
#define STRN(n, c) ((string){ n, (u8*)(uintptr)(const void*)(c) })
#define RSTR(...) STR(#__VA_ARGS__)

inline int memcmp(const void* a, const void* b, sys_uint n);
unit_local inline bool strings_match(string a, string b) {
    if (a.count != b.count) return false;

    if (a.data == b.data) return true; // Pointers and counts match

    if (a.count == 0 || b.count == 0) return false;
    if (a.data  == 0 || b.data  == 0) return false;

    return memcmp(a.data, b.data, (sys_uint)a.count) == 0;
}

unit_local inline bool string_contains(string s, string sub) {
    if (sub.count > s.count) return false;
    for (u64 i = 0; i < s.count-sub.count; i += 1) {
        string ssub = s;
        ssub.data += i;
        ssub.count = sub.count;
        if (strings_match(ssub, sub)) return true;
    }
    return false;
}

unit_local inline bool string_starts_with(string s, string sub) {
    if (sub.count > s.count) return false;
    
    return memcmp(s.data, sub.data, sub.count) == 0;
}

unit_local s64 string_find_index_from_left(string s, string sub) {
    
    for (u64 i = 0; i < s.count-sub.count; i += 1) {
        
        if (strings_match((string){sub.count, s.data+i}, sub)) {
            return (s64)i;
        }
    }
    return -1;
}
