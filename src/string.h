#ifndef _STRING_H
#define _STRING_H

#ifndef _BASE_H
#include "base.h"
#endif // _BASE_H

typedef struct string { 
    u64 count;
    u8 *data;
} string;

OSTD_LIB u64 c_style_strlen(const char *s);
OSTD_LIB u64 c_style_strcmp(const char *a, const char *b);


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

unit_local inline string string_slice(string s, u64 index, u64 count) {
    return (string){ count, s.data+index };
}

unit_local inline bool string_starts_with(string s, string sub) {
    if (sub.count > s.count) return false;
    
    return memcmp(s.data, sub.data, (u32)sub.count) == 0;
}
unit_local inline bool string_ends_with(string s, string sub) {
    if (sub.count > s.count) return false;
    return strings_match(sub, string_slice(s, s.count-sub.count, sub.count));
}

unit_local s64 string_find_index_from_left(string s, string sub) {
    if (sub.count > s.count) return -1;
    
    for (u64 i = 0; i < s.count-sub.count; i += 1) {
        
        if (strings_match((string){sub.count, s.data+i}, sub)) {
            return (s64)i;
        }
    }
    return -1;
}
unit_local s64 string_find_index_from_right(string s, string sub) {
    if (sub.count > s.count) return -1;
    
    for (s64 i = (s64)(s.count-sub.count); i >= 0; i -= 1) {
        
        if (strings_match((string){sub.count, s.data+(u64)i}, sub)) {
            return (s64)i;
        }
    }
    return -1;
}

unit_local string string_trim_left(string s) {

    while (s.count > 0 && !(s.data[0] >= 33 && s.data[0] <= 126)) {
        s.data += 1;
        s.count -= 1;
    }
    return s;
}

unit_local string string_trim_right(string s) {
    while (s.count > 0 && !(s.data[s.count-1] >= 33 && s.data[s.count-1] <= 126)) {
        s.count -= 1;
    }
    return s;
}

unit_local string string_trim(string s) {
    return string_trim_left(string_trim_right(s));
}

unit_local u64 string_count_occurences(string s, string sub) {
    if (sub.count > s.count) return 0;
    u64 n = 0;
    for (u64 i = 0; i < s.count-sub.count; i += 1) {
        if (strings_match(string_slice(s, i, sub.count), sub)) n += 1;
    }
    return n;
}

#ifdef OSTD_IMPL
OSTD_LIB u64 c_style_strlen(const char *s) {
    const char *p = s;
    while (*p) {
        p += 1;
    }
    return (u64)(p - s);
}
OSTD_LIB u64 c_style_strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++;
        b++;
    }
    return (u64)(*a - *b);
}
#endif

#endif // _STRING_H
