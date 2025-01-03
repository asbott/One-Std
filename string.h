
typedef struct string {
    u64 count;
    u8 *data;
} string;

inline u64 c_style_strlen(const char *s) {
    const char *p = s;
    while (*p++) {}
    return (u64)(p-s-1);
}

#define STR(c) ((string){ c_style_strlen(c), (u8*)c })

inline bool strings_match(string a, string b) {
    if (a.count != b.count) return false;
    
    if (a.data == b.data) return true; // Pointers and counts match
    
    if (a.count == 0 || b.count == 0) return false;
    if (a.data  == 0 || b.data  == 0) return false;
    
    return memcmp(a.data, b.data, a.count) == 0;
}