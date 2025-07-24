// This file was generated from One-Std/src/path_utils.h
// The following files were included & concatenated:
// - C:\nowgrep\One-Std\src\string.h
// - C:\nowgrep\One-Std\src\path_utils.h
// - C:\nowgrep\One-Std\src\base.h
// I try to compile with -pedantic and -Weverything, but get really dumb warnings like these,
// so I have to ignore them.
#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-macros"
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wattributes"
#pragma clang diagnostic ignored "-Wreserved-identifier"
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wcast-align"
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Wunused-const-variable"
#if __STDC_VERSION__ == 202311
#pragma clang diagnostic ignored "-Wpre-c23-compat"
#endif
#ifdef __EMSCRIPTEN__
#pragma clang diagnostic ignored "-Wpadded"
#endif // __EMSCRIPTEN__
#if defined(_MSC_VER) || defined(__EMSCRIPTEN__)
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif
#endif // __clang__
#ifndef _ONE_PATH_UTILS_H
#define _ONE_PATH_UTILS_H


#ifndef _STRING_H

/* Begin include: string.h */
#ifndef _STRING_H
#define _STRING_H

#ifndef _BASE_H

/* Begin include: base.h */

#ifndef _BASE_H
#define _BASE_H

/*
            Compiler
*/

#define COMPILER_FLAG_CLANG       (1 << 0)
#define COMPILER_FLAG_GNU         (1 << 1)
#define COMPILER_FLAG_MSC         (1 << 2)
#define COMPILER_FLAG_INTEL       (1 << 3)
#define COMPILER_FLAG_TCC         (1 << 4)
#define COMPILER_FLAG_EMSCRIPTEN  (1 << 5)
#define COMPILER_FLAG_PGI         (1 << 6)
#define COMPILER_FLAG_SUNPRO      (1 << 7)
#define COMPILER_FLAG_CLANG_GNU   (1 << 8)

#ifdef __clang__
    #define CLANG 1
#else
    #define CLANG 0
#endif

#if defined(__GNUC__) || defined(__GNUG__)
    #define GNU 1
#else
    #define GNU 0
#endif

#ifdef _MSC_VER
    #define MSC 1
#else
    #define MSC 0
#endif

#ifdef __INTEL_COMPILER
    #define INTEL 1
#else
    #define INTEL 0
#endif

#ifdef __TINYC__
    #define TCC 1
#else
    #define TCC 0
#endif

#ifdef __EMSCRIPTEN__
    #define EMSCRIPTEN 1
#else
    #define EMSCRIPTEN 0
#endif

#ifdef __PGI
    #define PGI 1
#else
    #define PGI 0
#endif

#ifdef __SUNPRO_C
    #define SUNPRO 1
#else
    #define SUNPRO 0
#endif

#define COMPILER_FLAGS ( \
    (CLANG ? COMPILER_FLAG_CLANG : 0) | \
    (GNU ? COMPILER_FLAG_GNU : 0) | \
    (MSC ? COMPILER_FLAG_MSC : 0) | \
    (INTEL ? COMPILER_FLAG_INTEL : 0) | \
    (TCC ? COMPILER_FLAG_TCC : 0) | \
    (EMSCRIPTEN ? COMPILER_FLAG_EMSCRIPTEN : 0) | \
    (PGI ? COMPILER_FLAG_PGI : 0) | \
    (SUNPRO ? COMPILER_FLAG_SUNPRO : 0) | \
    ((CLANG && GNU) ? COMPILER_FLAG_CLANG_GNU : 0) \
)

// Architexture

#if defined(_M_IX86) || defined(__i386__) || defined(__EMSCRIPTEN__)
    #define ARCH_X86 1
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
    #define ARCH_X64 1
#elif defined(_M_ARM) || defined(__arm__)
    #define ARCH_ARM 1
#elif defined(_M_ARM64) || defined(__aarch64__)
    #define ARCH_ARM64 1
#else
    #error "Unknown architecture"
#endif

#define local_persist static
#define forward_global extern
#define unit_local static

// make inline actually inline if supported by compiler

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wkeyword-macro"
#endif
#if COMPILER_FLAGS & COMPILER_FLAG_GNU
    #define inline __attribute__((always_inline))
#elif COMPILER_FLAGS & COMPILER_FLAG_MSC
    #define inline __forceinline
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#define CSTD_C90 1
#ifdef __STDC_VERSION__
    #if __STDC_VERSION__ == 199901
        #define CSTD_C99 1
    #else
        #define CSTD_C99 0
    #endif // CSTD_C99
    #if __STDC_VERSION__ == 201112
        #define CSTD_C11 1
    #else
        #define CSTD_C11 0
    #endif // CSTD_C11
    #if __STDC_VERSION__ == 201710
        #define CSTD_C17 1
    #else
        #define CSTD_C17 0
    #endif // CSTD_C17
    #if __STDC_VERSION__ == 202311
        #define CSTD_C23 1
    #else
        #define CSTD_C23 0
    #endif // CSTD_C23
#endif

#if CSTD_C23
    #define CSTD "C23"
#elif CSTD_C17
    #define CSTD "C17"
#elif CSTD_C11
    #define CSTD "C11"
#elif CSTD_C99
    #define CSTD "C99"
#elif CSTD_C90
    #define CSTD "C90"
#else
    #warning "Unknown C standard."
    #define CSTD "CUnknown"
#endif




/*
            Target system
*/

#define OS_FLAG_WINDOWS           (1 << 0)
#define OS_FLAG_UNIX              (1 << 1)
#define OS_FLAG_LINUX             (1 << 2)
#define OS_FLAG_APPLE             (1 << 3)
#define OS_FLAG_DARWIN            OS_FLAG_APPLE
#define OS_FLAG_MACOS             (1 << 4)
#define OS_FLAG_IOS               (1 << 5)
#define OS_FLAG_ANDROID           (1 << 6)
#define OS_FLAG_STEAMOS           (1 << 7)
#define OS_FLAG_LINUX_BASED       (1 << 8)
#define OS_FLAG_HAS_WINDOW_SYSTEM (1 << 9)
#define OS_FLAG_EMSCRIPTEN        (1 << 10)

#define OS_FLAG_WEB OS_FLAG_EMSCRIPTEN

#ifdef _WIN32
    #define OS_FLAGS (OS_FLAG_WINDOWS | OS_FLAG_HAS_WINDOW_SYSTEM)
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        #define OS_FLAGS (OS_FLAG_UNIX | OS_FLAG_APPLE | OS_FLAG_IOS)
    #elif TARGET_OS_MAC
        #define OS_FLAGS (OS_FLAG_UNIX | OS_FLAG_APPLE | OS_FLAG_MACOS | OS_FLAG_HAS_WINDOW_SYSTEM)
    #else
        #define OS_FLAGS (OS_FLAG_UNIX | OS_FLAG_APPLE)
    #endif
#elif defined(__ANDROID__)
    #define OS_FLAGS (OS_FLAG_UNIX | OS_FLAG_LINUX_BASED | OS_FLAG_ANDROID)
#elif defined(__STEAMOS__) /* You need to define this yourself when targetting steam */
    #define OS_FLAGS (OS_FLAG_UNIX | OS_FLAG_LINUX_BASED | OS_FLAG_LINUX | OS_FLAG_STEAMOS)
#elif defined(__linux__)
    #define OS_FLAGS (OS_FLAG_UNIX | OS_FLAG_LINUX_BASED | OS_FLAG_LINUX | OS_FLAG_HAS_WINDOW_SYSTEM)
#elif defined(__EMSCRIPTEN__)
    #define OS_FLAGS (OS_FLAG_UNIX | OS_FLAG_EMSCRIPTEN)
#elif defined(__unix__) || defined(__unix)
    #define OS_FLAGS (OS_FLAG_UNIX)
#else
    #define OS_FLAGS (0)
#endif

#if COMPILER_FLAGS & COMPILER_FLAG_MSC

    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wlanguage-extension-token"
    typedef unsigned __int8   u8;
    typedef signed __int8     s8;
    typedef unsigned __int16  u16;
    typedef signed __int16    s16;
    typedef unsigned __int32  u32;
    typedef signed __int32    s32;
    typedef unsigned __int64  u64;
    typedef signed __int64    s64;
    typedef unsigned __int64 uintptr;
    #pragma clang diagnostic pop

#elif COMPILER_FLAGS & COMPILER_FLAG_GNU

    typedef __UINT64_TYPE__ u64;
    typedef __INT64_TYPE__  s64;
    typedef __UINT32_TYPE__ u32;
    typedef __INT32_TYPE__  s32;
    typedef __UINT16_TYPE__ u16;
    typedef __INT16_TYPE__  s16;
    typedef __UINT8_TYPE__  u8;
    typedef __INT8_TYPE__   s8;

    typedef __UINTPTR_TYPE__  uintptr;

#else

    #include <stdint.h>
    typedef uint8_t  u8;
    typedef int8_t   s8;
    typedef uint16_t u16;
    typedef int16_t  s16;
    typedef uint32_t u32;
    typedef int32_t  s32;
    typedef uint64_t u64;
    typedef int64_t  s64;

     typedef uintptr_t uintptr;

#endif

typedef float float32;
typedef double float64;
#if defined(__SIZEOF_FLOAT128__) && __SIZEOF_FLOAT128__ == 16
    typedef __float128 float128;
    #define HAS_FLOAT128 1
#elif defined(__SIZEOF_LONG_DOUBLE__) && __SIZEOF_LONG_DOUBLE__ == 16
    typedef long double float128;
    #define HAS_FLOAT128 1
#else
    #define HAS_FLOAT128 0
#endif

typedef u8 uint8;
typedef s8 int8;
typedef u16 uint16;
typedef s16 int16;
typedef u32 uint32;
typedef s32 int32;
typedef u64 uint64;
typedef s64 int64;

typedef float32 f32;
typedef float64 f64;
#if HAS_FLOAT128
typedef float128 f128;
#endif // HAS_FLOAT128

#define U8_MIN 0
#define U8_MAX 255U
#define S8_MIN (-128)
#define S8_MAX 127
#define U16_MIN 0
#define U16_MAX 65535U
#define S16_MIN (-32768)
#define S16_MAX 32767
#define U32_MIN 0U
#define U32_MAX 4294967295UL
#define S32_MIN (-2147483648L)
#define S32_MAX 2147483647L
#define U64_MIN 0ULL
#define U64_MAX 18446744073709551615ULL
#define S64_MIN (-9223372036854775807LL - 1)
#define S64_MAX 9223372036854775807LL

#define UINT8_MIN 0
#define UINT8_MAX 255U
#define INT8_MIN (-128)
#define INT8_MAX 127
#define UINT16_MIN 0
#define UINT16_MAX 65535U
#define INT16_MIN (-32768)
#define INT16_MAX 32767
#define UINT32_MIN 0U
#define UINT32_MAX 4294967295UL
#define INT32_MIN (-2147483648L)
#define INT32_MAX 2147483647L
#define UINT64_MIN 0ULL
#define UINT64_MAX 18446744073709551615ULL
#define INT64_MIN (-9223372036854775807LL - 1)
#define INT64_MAX 9223372036854775807LL

#if defined(ARCH_X64) || defined (ARCH_ARM64)
typedef s64 sys_int;
typedef u64 sys_uint;
#define SYS_INT_MAX SYS_S64_MAX
#define SYS_UINT_MAX SYS_U64_MAX
#else
#if OS_FLAGS & OS_FLAG_EMSCRIPTEN
typedef signed long sys_int;
typedef unsigned long sys_uint;
#else
typedef s32 sys_int;
typedef u32 sys_uint;
#endif
#define SYS_INT_MAX S32_MAX
#define SYS_UINT_MAX U32_MAX
#endif

#if !CSTD_C23

#if (COMPILER_FLAGS & COMPILER_FLAG_CLANG) && ((COMPILER_FLAGS & COMPILER_FLAG_MSC) || COMPILER_FLAGS & COMPILER_FLAG_EMSCRIPTEN)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wc23-compat"
#endif // (COMPILER_FLAGS & COMPILER_FLAG_CLANG) && ((COMPILER_FLAGS & COMPILER_FLAG_MSC) || COMPILER_FLAGS & COMPILER_FLAG_EMSCRIPTEN)

    typedef s8 bool;
    #define true 1
    #define false 0
#if (COMPILER_FLAGS & COMPILER_FLAG_CLANG) && ((COMPILER_FLAGS & COMPILER_FLAG_MSC) || COMPILER_FLAGS & COMPILER_FLAG_EMSCRIPTEN)
    #pragma clang diagnostic pop
#endif // (COMPILER_FLAGS & COMPILER_FLAG_CLANG) && ((COMPILER_FLAGS & COMPILER_FLAG_MSC) || COMPILER_FLAGS & COMPILER_FLAG_EMSCRIPTEN)

#else // !CSTD_C23

#endif // CSTD_C23

#if COMPILER_FLAGS & COMPILER_FLAG_MSC
#define debug_break(...) __debugbreak()
#elif COMPILER_FLAGS & COMPILER_FLAG_GNU
#define debug_break(...) __builtin_trap()
#else
#define debug_break(...) *(volatile int*)0 = 1
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#ifndef DISABLE_ASSERT
    #define assertmsg(x, msg) assertmsgs(x, STR(msg))
    #define assertmsgs(x, msg)  do { \
            if (!(x)) {\
                sys_write_string(sys_get_stderr(), STR("\n========================================================\n"));\
                sys_write_string(sys_get_stderr(), STR("==========!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!==========\n"));\
                sys_write_string(sys_get_stderr(), STR("========================================================\n"));\
                sys_write_string(sys_get_stderr(), STR("\nAssertion failed for expression: '"));\
                sys_write_string(sys_get_stderr(), STR(#x));\
                sys_write_string(sys_get_stderr(), STR("'.\n"));\
                if (msg.data && msg.count) {\
                    sys_write_string(sys_get_stderr(), STR("\n\""));\
                    sys_write_string(sys_get_stderr(), msg);\
                    sys_write_string(sys_get_stderr(), STR("\"\n"));\
                }\
                sys_write_string(sys_get_stderr(), STR("\nIn File '"));\
                sys_write_string(sys_get_stderr(), STR(__FILE__));\
                sys_write_string(sys_get_stderr(), STR("' on line "));\
                sys_write_string(sys_get_stderr(), STR(TOSTRING(__LINE__)));\
                sys_write_string(sys_get_stderr(), STR("\n\nPrinting stack trace:\n"));\
                sys_print_stack_trace(sys_get_stderr());\
                sys_write_string(sys_get_stderr(), STR("\n\n========================================================\n"));\
                sys_write_string(sys_get_stderr(), STR("==========!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!==========\n"));\
                sys_write_string(sys_get_stderr(), STR("========================================================\n"));\
                debug_break();\
            } \
        } while(0)
    #define assert(x) assertmsg(x, "")
#else
    #define assertmsg(x, msg) (void)(x)
    #define assertmsgs(x, msg) (void)(x)
    #define assert(x) (void)(x)
#endif

#ifndef OSTD_LIB
    #define OSTD_LIB
#endif

#ifndef BUILTIN_ATTRIB
    #ifdef OSTD_SELF_CONTAINED
        #define BUILTIN_ATTRIB __attribute__((used))
    #else
        #define BUILTIN_ATTRIB
    #endif
#endif

// todo(charlie) inline asm / dynamically load crt's if msvc

void *memcpy(void *dst, const void * src, sys_uint n) {
    for (sys_uint i = 0; i < n; i += 1)  *((u8*)dst + i) = *((const u8*)src + i);
    return dst;
}

void *memset(void *dst, s32 c, sys_uint n) {
    u8 *p = (u8*)dst;
    while (n--) *p++ = (u8)c;
    return dst;
}

void *memmove(void *dst, const void *src, sys_uint n) {
    if (!n) return dst;
    if ((sys_uint)dst > (sys_uint)src)
        for (s64 i = (s64)n-1; i >= 0; i -= 1)  *((u8*)dst + i) = *((const u8*)src + i);
    else
        for (sys_uint i = 0; i < n; i += 1)  *((u8*)dst + i) = *((const u8*)src + i);
    return dst;
}


int memcmp(const void* a, const void* b, sys_uint n) {
    const u8 *p1 = (const u8 *)a;
    const u8 *p2 = (const u8 *)b;

    for (u32 i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    return 0;
}

#define DEFAULT(T) T##_default()


// Forward decls
u64 format_signed_int(s64 x, int base, void *buffer, u64 buffer_size);
u64 format_unsigned_int(u64 x, int base, void *buffer, u64 buffer_size);
u64 format_float(float64 x, int decimal_places, void *buffer, u64 buffer_size);



#define PP_FIRST_ARG_HELPER(first, ...) first
#define PP_FIRST_ARG(...) PP_FIRST_ARG_HELPER(__VA_ARGS__, 0)

#define PP_EXCLUDE_FIRST_ARG_HELPER(first, ...) __VA_ARGS__
#define PP_EXCLUDE_FIRST_ARG(...) PP_EXCLUDE_FIRST_ARG_HELPER(__VA_ARGS__)

#define Swap(a, b) do {  u8 tmp__[sizeof(a)]; memcpy(tmp__, &a, sizeof(a)); a = b; memcpy(&b, tmp__, sizeof(b)); } while (0)

#ifndef offsetof
#define offsetof(t, d) ((sys_uint)&(((t *)0)->d))
#endif


void __cpuid(int cpuInfo[4], int function_id);

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

unit_local inline bool is_alpha(u8 c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
unit_local inline bool is_digit(u8 c) {
	return (c >= '0' && c <= '9');
}
unit_local inline bool is_whitespace(u8 c) {
	return c == '\n' || c == '\r' || c == '\t' || c == ' ';
}

unit_local inline u64 align_next(u64 n, u64 align) {
    return (n+align-1) & ~(align-1);
}

#define KiB(N) (1024ULL*N)
#define MiB(N) (1024ULL*1024ULL*N)
#define GiB(N) (1024ULL*1024ULL*1024ULL*N)
#define TiB(N) (1024ULL*1024ULL*1024ULL*1024ULL*N)

#endif // _BASE_H




/* End include: base.h */
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

/* End include: string.h */
#endif // _STRING_H

OSTD_LIB string path_get_filename(string path);
OSTD_LIB string path_strip_one_extension(string path);
OSTD_LIB string path_strip_all_extensions(string path);
OSTD_LIB string path_get_directory(string path);

#ifdef OSTD_IMPL

string path_get_filename(string path) {
	for (s64 i = (s64)(path.count-1); i >= 0; i -= 1) {
		if (path.data[i] == '\\' || path.data[i] == '/') {
			return string_slice(path, (u64)i+1, path.count-(u64)i-1);
		}
    }
    return path;
}

string path_strip_one_extension(string path) {
	for (s64 i = (s64)(path.count-1); i >= 0; i -= 1) {
		if (path.data[i] == '\\' || path.data[i] == '/') {
			return path;
		}
		if (path.data[i] == '.') {
			return string_slice(path, 0, (u64)i);
		}
    }
    return path;
}

string path_strip_all_extensions(string path) {
	s64 lowest_index = -1;
	for (s64 i = (s64)(path.count-1); i >= 0; i -= 1) {
		if (path.data[i] == '\\' || path.data[i] == '/') {
			break;
		}
		if (path.data[i] == '.') {
			if (lowest_index == -1 || i < lowest_index) {
				lowest_index = i;
			}
		}
    }
    if (lowest_index == -1) return path;
    
	return string_slice(path, 0, (u64)lowest_index);
}

string path_get_directory(string path) {
    for (s64 i = (s64)(path.count - 1); i >= 0; i -= 1) {
        if (path.data[i] == '\\' || path.data[i] == '/') {
            return string_slice(path, 0, (u64)i);
        }
    }
    return (string){0};
}

#endif // OSTD_IMPL
#endif // _ONE_PATH_UTILS_H
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

