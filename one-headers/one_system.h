// This file was generated from One-Std/src/system.h
// The following files were included & concatenated:
// - C:\One-Std\src\system1.h
// - C:\One-Std\src\memory.h
// - C:\One-Std\src\system2.h
// - C:\One-Std\src\windows_loader.h
// - C:\One-Std\src\var_args_macros.h
// - C:\One-Std\src\system.h
// - C:\One-Std\src\print.h
// - C:\One-Std\src\var_args.h
// - C:\One-Std\src\string.h
// - C:\One-Std\src\base.h
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
#ifndef _ONE_SYSTEM_H
#define _ONE_SYSTEM_H



/* Begin include: system1.h */
#ifndef _SYSTEM_1_H
#define _SYSTEM_1_H

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
    #define assertmsg(x, msg) assertmsgs(x, (STR(msg)))
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
#ifndef _STRING_H

/* Begin include: string.h */
#ifndef _STRING_H
#define _STRING_H

#ifndef _BASE_H
#endif // _BASE_H

typedef struct string { 
    u64 count;
    u8 *data;
} string;

OSTD_LIB u64 c_style_strlen(const char *s);
OSTD_LIB u64 c_style_strcmp(const char *a, const char *b);


#define STR(c) ((string){ c_style_strlen((const char*)(c)), (u8*)(uintptr)(const void*)(c) })
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
    
    for (u64 i = 0; i <= s.count-sub.count; i += 1) {
        
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

#define SYS_MEMORY_RESERVE (1 << 0)
#define SYS_MEMORY_ALLOCATE (1 << 1)

void *sys_map_pages(u64 action, void *virtual_base, u64 number_of_pages, bool strict_base_address);
bool sys_unmap_pages(void *address);
// Deallocates, but keeps pages mapped & reserved
bool sys_deallocate_pages(void *address, u64 number_of_pages);

typedef struct Mapped_Memory_Info {
    void *base;
    u64 page_count;
} Mapped_Memory_Info;
u64 sys_query_mapped_regions(void *start, void *end, Mapped_Memory_Info *result, u64 result_size);

void *sys_find_mappable_range(u64 page_count);

//////
// System info
//////

typedef struct System_Info {
    u64 page_size;
    u64 granularity;
    u64 logical_cpu_count;
} System_Info;

System_Info sys_get_info(void);

typedef struct Physical_Monitor {
    //  Do (string) {monitor.name_count, monitor.name}
    u8 name[256];
    u64 name_count;
	int64 refresh_rate;
	int64 resolution_x;
	int64 resolution_y;
	float64 scale;
	int64 pos_x;
	int64 pos_y;

	void *handle;
} Physical_Monitor;

u64 sys_query_monitors(Physical_Monitor *buffer, u64 max_count);

bool sys_wait_vertical_blank(Physical_Monitor monitor);



//////
// IO
//////

typedef void* File_Handle;
typedef u64 File_Open_Flags;
#define FILE_OPEN_WRITE  (1 << 0)
#define FILE_OPEN_READ   (1 << 1)
#define FILE_OPEN_RESET  (1 << 2)
#define FILE_OPEN_CREATE (1 << 3)

OSTD_LIB File_Handle sys_get_stdout(void);
OSTD_LIB File_Handle sys_get_stderr(void);

OSTD_LIB void sys_set_stdout(File_Handle h);
OSTD_LIB void sys_set_stderr(File_Handle h);

OSTD_LIB s64 sys_write(File_Handle h, void *data, u64 size);
OSTD_LIB s64 sys_write_string(File_Handle h, string s);

OSTD_LIB s64 sys_read(File_Handle h, void *buffer, u64 buffer_size);

OSTD_LIB bool sys_make_pipe(File_Handle *read, File_Handle *write);

OSTD_LIB void sys_close(File_Handle h);

// Returns 0 on failure
OSTD_LIB File_Handle sys_open_file(string path, File_Open_Flags flags);
OSTD_LIB u64 sys_get_file_size(File_Handle f);

OSTD_LIB bool sys_set_file_position(File_Handle f, u64 position);

OSTD_LIB bool sys_make_directory(string path, bool recursive);
OSTD_LIB bool sys_remove_directory(string path, bool recursive);
OSTD_LIB bool sys_is_file(string path);
OSTD_LIB bool sys_is_directory(string path);

typedef bool (*Walk_Proc)(string); // Return true to continue, false to break
OSTD_LIB void sys_walk_directory(string path, bool recursive, bool walk_directories, Walk_Proc walk_proc);

typedef struct Easy_Command_Result {
    s64 exit_code;
    bool process_start_success;
} Easy_Command_Result;
OSTD_LIB Easy_Command_Result sys_run_command_easy(string command_line, File_Handle stdout, File_Handle stderr, string workspace_dir, bool wait_for_exit);

OSTD_LIB void sys_exit(s64 code);
OSTD_LIB void sys_exit_current_thread(s64 code);

//////
// Sockets
//////

typedef u64 Socket;

typedef enum Socket_Result {
    SOCKET_OK = 0,

    SOCKET_DISCONNECTED,
    SOCKET_NOT_INITIALIZED,
    SOCKET_NOACCESS,
    SOCKET_IN_PROGRESS,
    SOCKET_NOT_A_SOCKET,

    SOCKET_INVALID_ADDRESS,
    SOCKET_TIMED_OUT,
    SOCKET_CONNECTION_REFUSED,
    SOCKET_CONNECTION_RESET,
    SOCKET_ALREADY_CONNECTED,
    SOCKET_ADDRESS_IN_USE,
    SOCKET_NETWORK_UNREACHABLE,
    SOCKET_HOST_UNREACHABLE,
    SOCKET_PROTOCOL_ERROR,
} Socket_Result;


typedef enum Socket_Domain {
    SOCKET_DOMAIN_IPV4,
    SOCKET_DOMAIN_BLUETOOTH,
    SOCKET_DOMAIN_APPLETALK,
#if OS_FLAGS & OS_FLAG_UNIX
    SOCKET_DOMAIN_UNIX,
#endif

} Socket_Domain;

typedef enum Socket_Type {
    SOCKET_TYPE_STREAM,
    SOCKET_TYPE_DGRAM,
    SOCKET_TYPE_RAW,
    SOCKET_TYPE_RDM,
    SOCKET_TYPE_SEQPACKET,
} Socket_Type;

typedef enum Socket_Protocol {
    SOCKET_PROTOCOL_TCP,
    SOCKET_PROTOCOL_UDP,
} Socket_Protocol;

OSTD_LIB u32 sys_convert_address_string(string address);

OSTD_LIB Socket_Result sys_socket_init(Socket *socket, Socket_Domain domain, Socket_Type type, Socket_Protocol protocol);
OSTD_LIB Socket_Result sys_socket_bind(Socket socket, u32 address, u16 port);
OSTD_LIB Socket_Result sys_socket_listen(Socket socket, s64 backlog);
OSTD_LIB Socket_Result sys_socket_accept(Socket socket, Socket *accepted, u64 timeout_ms);
OSTD_LIB Socket_Result sys_socket_connect(Socket sock, u32 address, u16 port, Socket_Domain domain);
OSTD_LIB Socket_Result sys_socket_send(Socket socket, void *data, u64 length, u64 *sent);
OSTD_LIB Socket_Result sys_socket_recv(Socket socket, void *buffer, u64 length, u64 *sent);
OSTD_LIB Socket_Result sys_socket_close(Socket socket);
OSTD_LIB Socket_Result sys_socket_set_blocking(Socket *socket, bool blocking);
OSTD_LIB Socket_Result sys_set_socket_blocking_timeout(Socket socket, u64 ms);


//////
// Thread Primitives
//////

typedef void* Thread_Key;

OSTD_LIB u64 sys_get_current_thread_id(void);

OSTD_LIB bool sys_thread_key_init(Thread_Key *key);
OSTD_LIB bool sys_thread_key_write(Thread_Key key, void* value);
OSTD_LIB void* sys_thread_key_read(Thread_Key key);

struct Thread;
typedef s64 (*Thread_Proc)(struct Thread*);
typedef struct Thread {
    u8 handle_backing[64];
    void *handle;
    u64 id;
    void *userdata;
    Thread_Proc proc;
    bool is_suspended;
} Thread;

OSTD_LIB bool sys_thread_init(Thread *thread, Thread_Proc proc, void *userdata);
OSTD_LIB bool sys_thread_start(Thread *thread);
OSTD_LIB s64 sys_thread_join(Thread *thread);
OSTD_LIB void sys_thread_close(Thread *thread);

typedef struct Mutex {
    u8 handle_backing[64];
    void *handle;
} Mutex;

OSTD_LIB bool sys_mutex_init(Mutex *mutex);
OSTD_LIB bool sys_mutex_uninit(Mutex *mutex);
OSTD_LIB void sys_mutex_acquire(Mutex mutex);
OSTD_LIB void sys_mutex_release(Mutex mutex);

typedef struct Semaphore {
    u8 handle_backing[64];
    void *handle;
} Semaphore;
OSTD_LIB bool sys_semaphore_init(Semaphore *sem);
OSTD_LIB void sys_semaphore_signal(Semaphore *sem);
OSTD_LIB void sys_semaphore_wait(Semaphore *sem);
OSTD_LIB void sys_semaphore_uninit(Semaphore *sem);

////////
// Atomics

inline unit_local u32 sys_atomic_add_32(volatile u32 *addend, u32 value);
inline unit_local u64 sys_atomic_add_64(volatile u64 *addend, u64 value);

//////
// Surfaces (Window)
//////

#ifndef OSTD_HEADLESS

typedef void* Surface_Handle;

// note(charlie)
// Some systems have window systems, like win32, where you can create/destroy/manage
// multiple windows, while other platforms, like android, only has a single surface
// for your program to draw to.
// Making a thin abstraction layer that works with both types of system doesn't really
// make sense, unless we only allow a single full-screen surface on all platforms.
// However, since this library aims to be useful on all systems, we can't really do that.
// Instead, we disable the concept of creating/destroying surfaces on systems without
// windowing systems, and leave that up to the programmer. To keep it simple, we only
// compile different functions for creating/destroying/getting surfaces depending on
// target system. This means, for example, on windows you need to create/destroy but
// on mobiles you only ever get the surface.
// Any setting functions will still be compiled to no-ops on systems where they don't
// make sense. You also won't be able to get multiple surface handles on single-surface
// systems.
// Suggestions for "initialization" of a surface if your program needs to deploy on both
// mobiles/consoles and desktops:
//
// // In init:
// #if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
//     Surface_Desc desc = ...;
//     my_surface = sys_make_surface(desc);
// #else
//     my_surface = sys_get_surface();
// #endif
//
// And after that, you can use surface functions in a completely portable way.

// todo(charlie) more flags
typedef u64 Surface_Flags;
#define SURFACE_FLAG_HIDDEN (1 << 0)
#define SURFACE_FLAG_TOPMOST (1 << 1)

#if (OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)

typedef struct Surface_Desc {
    // These don't do anything for main surface on phone/console systems
    u32 width;
    u32 height;
    u32 x_pos;
    u32 y_pos;
    string title;
    bool fullscreen;
    Surface_Flags flags;
} Surface_Desc;
unit_local inline Surface_Desc Surface_Desc_default(void) {
    Surface_Desc desc = (Surface_Desc) {0};
    desc.width = 800;
    desc.height = 600;
    desc.x_pos = 0;
    desc.y_pos = 0;
    desc.title = RSTR(ostd window);
    desc.flags = 0;
    return desc;
}
OSTD_LIB Surface_Handle sys_make_surface(Surface_Desc desc);
OSTD_LIB void surface_close(Surface_Handle s);


#else // !(OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)

OSTD_LIB Surface_Handle sys_get_surface(void);

#endif // !(OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)

OSTD_LIB void surface_poll_events(Surface_Handle surface);
OSTD_LIB bool surface_should_close(Surface_Handle s);

// Will return false on systems where the flag isn't implemented
OSTD_LIB bool surface_set_flags(Surface_Handle h, Surface_Flags flags);
OSTD_LIB bool surface_unset_flags(Surface_Handle h, Surface_Flags flags);

OSTD_LIB bool surface_get_framebuffer_size(Surface_Handle h, s64 *width, s64 *height);

OSTD_LIB void* surface_map_pixels(Surface_Handle h);
OSTD_LIB void surface_blit_pixels(Surface_Handle h);

OSTD_LIB bool surface_get_monitor(Surface_Handle h, Physical_Monitor *monitor);

#endif // !OSTD_HEADLESS

//////
// Time
//////

OSTD_LIB float64 sys_get_seconds_monotonic(void);

//////
// Process & Thread
//////

typedef void* Thread_Handle;

OSTD_LIB Thread_Handle sys_get_current_thread(void);
OSTD_LIB void sys_set_thread_affinity_mask(Thread_Handle thread, u64 bits);

typedef enum Priority_Level {
    SYS_PRIORITY_LOW,
    SYS_PRIORITY_MEDIUM,
    SYS_PRIORITY_HIGH,
} Priority_Level;

OSTD_LIB void sys_set_local_process_priority_level(Priority_Level level);
OSTD_LIB void sys_set_thread_priority_level(Thread_Handle thread, Priority_Level level);

OSTD_LIB void *sys_load_library(string s);
OSTD_LIB void sys_close_library(void *lib);
OSTD_LIB void* sys_get_library_symbol(void *lib, string symbol);

//////
// Debug
//////

OSTD_LIB void sys_print_stack_trace(File_Handle handle);

//////
// System Constants
/////

#define MAX_SURFACES 64
#define MAX_PATH_LENGTH 260


//////
// Implementations
//////


struct _Per_Thread_Temporary_Storage;
typedef struct _Ostd_Thread_Storage {
    u64 thread_id;
    u8 temporary_storage_struct_backing[128];
    struct _Per_Thread_Temporary_Storage *temp;
    bool taken;
} _Ostd_Thread_Storage;

_Ostd_Thread_Storage *_ostd_get_thread_storage(void);

#ifdef OSTD_IMPL

unit_local _Ostd_Thread_Storage *_ostd_thread_storage = 0;
unit_local u64 _ostd_thread_storage_allocated_count = 0;
unit_local Mutex _ostd_thread_storage_register_mutex;
unit_local bool _ostd_thread_storage_register_mutex_initted;
unit_local u64 _ostd_main_thread_id;
unit_local bool _ostd_main_thread_is_unknown = true;
unit_local _Ostd_Thread_Storage _ostd_main_thread_storage;

_Ostd_Thread_Storage *_ostd_get_thread_storage(void) {
    u64 thread_id = sys_get_current_thread_id();

    if (!_ostd_main_thread_is_unknown && _ostd_main_thread_id == thread_id) {
        return &_ostd_main_thread_storage;
    }

    for (u64 i = 0; i < _ostd_thread_storage_allocated_count; i += 1) {
        _Ostd_Thread_Storage *s = &_ostd_thread_storage[i];
        if (s->thread_id == thread_id) return s;
    }

    if (_ostd_main_thread_is_unknown) {
        _ostd_main_thread_id = thread_id;
        _ostd_main_thread_is_unknown = false;
        _ostd_main_thread_storage = (_Ostd_Thread_Storage){0};
        _ostd_main_thread_storage.taken = true;
        _ostd_main_thread_storage.thread_id = thread_id;
        _ostd_main_thread_storage.temp
            = (struct _Per_Thread_Temporary_Storage*)_ostd_main_thread_storage.temporary_storage_struct_backing;
        return &_ostd_main_thread_storage;
    }
    
    assert(false);
    
    return 0;
}

unit_local void _ostd_register_thread_storage(u64 thread_id) {

    static u64 crazy_counter = 0;
    u64 me = sys_atomic_add_64(&crazy_counter, 1);
    
    while (!_ostd_thread_storage_register_mutex_initted && me > 0) {}
    
    if (!_ostd_thread_storage_register_mutex_initted) {
        sys_mutex_init(&_ostd_thread_storage_register_mutex);
        _ostd_thread_storage_register_mutex_initted = true;
    }
    
    sys_mutex_acquire(_ostd_thread_storage_register_mutex);

    for (u64 i = 0; i < _ostd_thread_storage_allocated_count; i += 1) {
        _Ostd_Thread_Storage *s = &_ostd_thread_storage[i];
        if (!s->taken) {
            *s = (_Ostd_Thread_Storage) {0};
            s->taken = true;
            s->thread_id = thread_id;
            s->temp = (struct _Per_Thread_Temporary_Storage*)s->temporary_storage_struct_backing;
            sys_mutex_release(_ostd_thread_storage_register_mutex);
            return;
        }
    }

    u64 page_size = sys_get_info().page_size;

    assertmsg(sizeof(_Ostd_Thread_Storage) < page_size, "refactor time");

    if (!_ostd_thread_storage) {
        _ostd_thread_storage = sys_map_pages(SYS_MEMORY_RESERVE, 0, 100000, false);
        assert(_ostd_thread_storage);
        void *allocated = sys_map_pages(SYS_MEMORY_ALLOCATE, _ostd_thread_storage, 1, true);
        assert(allocated == _ostd_thread_storage);
        memset(allocated, 0, page_size);
        _ostd_thread_storage_allocated_count = page_size/sizeof(_Ostd_Thread_Storage);
    } else {
        void *next_alloc = (void*)(uintptr)align_next((u64)(_ostd_thread_storage+_ostd_thread_storage_allocated_count), page_size);
        void *allocated = sys_map_pages(SYS_MEMORY_ALLOCATE, next_alloc, 1, true);
        assert(allocated == next_alloc);
        memset(allocated, 0, page_size);

        _ostd_thread_storage_allocated_count += (page_size / sizeof(_Ostd_Thread_Storage));
    }

    sys_mutex_release(_ostd_thread_storage_register_mutex);

    // scary
    _ostd_register_thread_storage(thread_id);
}

#if (OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)

#if OS_FLAGS & OS_FLAG_WINDOWS
    //#define WIN32_LEAN_AND_MEAN
    //#include <Windows.h>

    #if defined(_WINDOWS_) // User included windows.h
        #ifndef  WIN32_LEAN_AND_MEAN
            #error For ostd to work with windows.h included, you need to #define WIN32_LEAN_AND_MEAN
        #endif // WIN32_LEAN_AND_MEAN
        #ifndef _DBGHELP_
            #include <DbgHelp.h>
        #endif // _DBGHELP_
    #endif // defined(_WINDOWS_)

    // If user for some reason wants to include the full standard windows files,
    // then he can define OSTD_INCLUDE_WINDOWS
    #ifdef OSTD_INCLUDE_WINDOWS
        #define WIN32_LEAN_AND_MEAN
        #include <Windows.h>
        #include <DbgHelp.h>
    #endif // OSTD_INCLUDE_WINDOWS
    // We manually declare windows functions so we don't need to bloat compilation and
    // namespace with windows.h
    #ifndef _WINDOWS_ /* This is defined in windows.h */

/* Begin include: windows_loader.h */

#ifndef _WINDOWS_LOADER_H
#define _WINDOWS_LOADER_H

#ifndef _BASE_H
#endif // _BASE_H

#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00


#define DECLSPEC_ALIGN(x) __declspec(align(x))
#define DECLSPEC_NOINITALL

typedef void *HANDLE;
typedef void* HWND;
typedef unsigned long* PDWORD;
typedef void* HMONITOR;
typedef u32 HRESULT;
typedef void* HDC;
typedef HANDLE HINSTANCE;
typedef HANDLE HICON;
typedef HANDLE HBRUSH;
typedef HANDLE HCURSOR;
typedef HANDLE HMODULE;
typedef HANDLE HMENU;
typedef HANDLE HBITMAP;
typedef HANDLE HGDIOBJ;
typedef HANDLE HFONT;
typedef HANDLE HPEN;
typedef HANDLE HGLOBAL;
typedef HANDLE HRGN;

typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL                *PBOOL;
typedef BOOL                *LPBOOL;
typedef BYTE                *PBYTE;
typedef BYTE                *LPBYTE;
typedef int                 *PINT;
typedef int                 *LPINT;
typedef WORD                *PWORD;
typedef WORD                *LPWORD;
typedef long                *LPLONG;
typedef DWORD               *PDWORD;
typedef DWORD               *LPDWORD;
typedef void                *LPVOID;
typedef const void          *LPCVOID;
typedef void                *PVOID;

typedef u64 DWORDLONG;


#if !defined(_M_IX86)
 typedef s64 LONGLONG; 
#else
 typedef double LONGLONG;
#endif

#if !defined(_M_IX86)
 typedef u64 ULONGLONG;
#else
 typedef double ULONGLONG;
#endif
typedef LONGLONG USN;

typedef WORD ATOM;

typedef s64 INT_PTR, *PINT_PTR;
typedef u64 UINT_PTR, *PUINT_PTR;

typedef s64 LONG_PTR, *PLONG_PTR;
typedef u64 ULONG_PTR, *PULONG_PTR;


typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

typedef signed char         INT8, *PINT8;
typedef signed short        INT16, *PINT16;
typedef signed int          INT32, *PINT32;
typedef s64      INT64, *PINT64;
typedef unsigned char       UINT8, *PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;
typedef s64    UINT64, *PUINT64;

typedef signed int LONG32, *PLONG32;

typedef unsigned int ULONG32, *PULONG32;
typedef unsigned int DWORD32, *PDWORD32;

typedef LONG32 LONG;

typedef s64 ULONG64, *PULONG64;
typedef s64 DWORD64, *PDWORD64;

typedef u64 LONG64;

typedef char CHAR;
typedef CHAR *PCHAR, *LPCH, *PCH;
typedef const CHAR *LPCCH, *PCCH;

typedef DWORD *DWORD_PTR;

typedef CHAR *NPSTR, *LPSTR, *PSTR;
typedef PSTR *PZPSTR;
typedef const PSTR *PCZPSTR;
typedef const CHAR *LPCSTR, *PCSTR;
typedef PCSTR *PZPCSTR;
typedef const PCSTR *PCZPCSTR;

typedef CHAR *PZZSTR;
typedef const CHAR *PCZZSTR;

typedef  CHAR *PNZCH;
typedef  const CHAR *PCNZCH;

typedef unsigned short WCHAR;

typedef WCHAR *NWPSTR, *LPWSTR, *PWSTR;
typedef PWSTR *PZPWSTR;
typedef const PWSTR *PCZPWSTR;
typedef WCHAR *LPUWSTR, *PUWSTR;
typedef const WCHAR *LPCWSTR, *PCWSTR;
typedef PCWSTR *PZPCWSTR;
typedef const PCWSTR *PCZPCWSTR;
typedef const WCHAR *LPCUWSTR, *PCUWSTR;

// what the fuck

// who thought this was a good idea

typedef WCHAR *PZZWSTR;
typedef const WCHAR *PCZZWSTR;
typedef WCHAR *PUZZWSTR;
typedef const WCHAR *PCUZZWSTR;

typedef  WCHAR *PNZWCH;
typedef  const WCHAR *PCNZWCH;
typedef  WCHAR *PUNZWCH;
typedef  const WCHAR *PCUNZWCH;

typedef const WCHAR *LPCWCH;

typedef long long LONGLONG;

typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } DUMMYSTRUCTNAME;
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef LARGE_INTEGER LARGE_INTEGER;

typedef LRESULT (*WNDPROC)( HWND unnamedParam1, UINT unnamedParam2, WPARAM unnamedParam3, LPARAM unnamedParam4);


// #Portability x64
#define CONTEXT_AMD64   0x00100000L

#define CONTEXT_CONTROL         (CONTEXT_AMD64 | 0x00000001L)
#define CONTEXT_INTEGER         (CONTEXT_AMD64 | 0x00000002L)
#define CONTEXT_SEGMENTS        (CONTEXT_AMD64 | 0x00000004L)
#define CONTEXT_FLOATING_POINT  (CONTEXT_AMD64 | 0x00000008L)
#define CONTEXT_DEBUG_REGISTERS (CONTEXT_AMD64 | 0x00000010L)

#define CONTEXT_FULL            (CONTEXT_CONTROL | CONTEXT_INTEGER | \
    CONTEXT_FLOATING_POINT)

#define CONTEXT_ALL             (CONTEXT_CONTROL | CONTEXT_INTEGER | \
    CONTEXT_SEGMENTS | CONTEXT_FLOATING_POINT | \
    CONTEXT_DEBUG_REGISTERS)

#define CONTEXT_XSTATE          (CONTEXT_AMD64 | 0x00000040L)




#define WINAPI __stdcall

#if COMPILER_FLAGS & COMPILER_FLAG_GNU
#define WINDOWS_IMPORT extern __attribute__((dllimport))
#elif COMPILER_FLAGS & COMPILER_FLAG_MSC

#define WINDOWS_IMPORT __declspec(dllimport)
#else
#define WINDOWS_IMPORT
#endif

typedef struct tagRECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT, *PRECT, *NPRECT, *LPRECT;
typedef const RECT* LPCRECT;

// ?!?!?!?!?!?!??!?!?!?!?!??!?!?!?!?!?!?!?!??!?!!??!?!?!?!?
typedef struct _POINTL {
  LONG x;
  LONG y;
} POINTL, *PPOINTL;
typedef struct tagPOINT {
  LONG x;
  LONG y;
} POINT, *PPOINT, *NPPOINT, *LPPOINT;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmicrosoft-anon-tag"
#endif // __clang__
typedef struct _SYSTEM_INFO {
    union _SYSTEM_INFO_DUMMYUNION {
        DWORD dwOemId;
        struct _SYSTEM_INFO_DUMMYSTRUCT {
            WORD wProcessorArchitecture;
            WORD wReserved;
        } ;
    } ;
    DWORD dwPageSize;
    LPVOID lpMinimumApplicationAddress;
    LPVOID lpMaximumApplicationAddress;
    DWORD_PTR dwActiveProcessorMask;
    DWORD dwNumberOfProcessors;
    DWORD dwProcessorType;
    DWORD dwAllocationGranularity;
    WORD wProcessorLevel;
    WORD wProcessorRevision;
} SYSTEM_INFO, *LPSYSTEM_INFO;
#ifdef __clang__
#pragma clang diagnostic pop
#endif //__clang__

typedef struct _MEMORY_BASIC_INFORMATION {
    void*  BaseAddress;
    void*  AllocationBase;
    u32  AllocationProtect;
    u16   PartitionId;
    size_t RegionSize;
    u32  State;
    u32  Protect;
    u32  Type;
} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;

typedef struct DECLSPEC_ALIGN(16) _M128A {
    unsigned long long Low;
    long long High;
} M128A, *PM128A;

typedef struct DECLSPEC_ALIGN(16) _XMM_SAVE_AREA32
{
    WORD   ControlWord;
    WORD   StatusWord;
    BYTE  TagWord;
    BYTE  Reserved1;
    WORD   ErrorOpcode;
    DWORD ErrorOffset;
    WORD   ErrorSelector;
    WORD   Reserved2;
    DWORD DataOffset;
    WORD   DataSelector;
    WORD   Reserved3;
    DWORD MxCsr;
    DWORD MxCsr_Mask;
    M128A FloatRegisters[8];

    #if defined(_WIN64)

    M128A XmmRegisters[16];
    BYTE  Reserved4[96];

    #else

    M128A XmmRegisters[8];
    BYTE  Reserved4[224];

    #endif

} XMM_SAVE_AREA32;
typedef struct DECLSPEC_ALIGN(16) _CONTEXT {

    //
    // Register parameter home addresses.
    //
    // N.B. These fields are for convience - they could be used to extend the
    //      context record in the future.
    //

    DWORD64 P1Home;
    DWORD64 P2Home;
    DWORD64 P3Home;
    DWORD64 P4Home;
    DWORD64 P5Home;
    DWORD64 P6Home;

    //
    // Control flags.
    //

    DWORD ContextFlags;
    DWORD MxCsr;

    //
    // Segment Registers and processor flags.
    //

    WORD   SegCs;
    WORD   SegDs;
    WORD   SegEs;
    WORD   SegFs;
    WORD   SegGs;
    WORD   SegSs;
    DWORD EFlags;

    //
    // Debug registers
    //

    DWORD64 Dr0;
    DWORD64 Dr1;
    DWORD64 Dr2;
    DWORD64 Dr3;
    DWORD64 Dr6;
    DWORD64 Dr7;

    //
    // Integer registers.
    //

    DWORD64 Rax;
    DWORD64 Rcx;
    DWORD64 Rdx;
    DWORD64 Rbx;
    DWORD64 Rsp;
    DWORD64 Rbp;
    DWORD64 Rsi;
    DWORD64 Rdi;
    DWORD64 R8;
    DWORD64 R9;
    DWORD64 R10;
    DWORD64 R11;
    DWORD64 R12;
    DWORD64 R13;
    DWORD64 R14;
    DWORD64 R15;

    //
    // Program counter.
    //

    DWORD64 Rip;

    //
    // Floating point state.
    //

    union {
        XMM_SAVE_AREA32 FltSave;
        struct {
            M128A Header[2];
            M128A Legacy[8];
            M128A Xmm0;
            M128A Xmm1;
            M128A Xmm2;
            M128A Xmm3;
            M128A Xmm4;
            M128A Xmm5;
            M128A Xmm6;
            M128A Xmm7;
            M128A Xmm8;
            M128A Xmm9;
            M128A Xmm10;
            M128A Xmm11;
            M128A Xmm12;
            M128A Xmm13;
            M128A Xmm14;
            M128A Xmm15;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    //
    // Vector registers.
    //

    M128A VectorRegister[26];
    DWORD64 VectorControl;

    //
    // Special debug control registers.
    //

    DWORD64 DebugControl;
    DWORD64 LastBranchToRip;
    DWORD64 LastBranchFromRip;
    DWORD64 LastExceptionToRip;
    DWORD64 LastExceptionFromRip;
} CONTEXT, *PCONTEXT;

typedef enum {
    AddrMode1616,
    AddrMode1632,
    AddrModeReal,
    AddrModeFlat
} ADDRESS_MODE;
typedef struct _tagADDRESS64 {
    DWORD64       Offset;
    WORD          Segment;
    ADDRESS_MODE  Mode;
} ADDRESS64, *LPADDRESS64;

typedef struct _KDHELP64 {

    DWORD64   Thread;
    DWORD   ThCallbackStack;
    DWORD   ThCallbackBStore;
    DWORD   NextCallback;
    DWORD   FramePointer;
    DWORD64   KiCallUserMode;
    DWORD64   KeUserCallbackDispatcher;
    DWORD64   SystemRangeStart;
    DWORD64   KiUserExceptionDispatcher;
    DWORD64   StackBase;
    DWORD64   StackLimit;
    DWORD     BuildVersion;
    DWORD     RetpolineStubFunctionTableSize;
    DWORD64   RetpolineStubFunctionTable;
    DWORD     RetpolineStubOffset;
    DWORD     RetpolineStubSize;
    DWORD64   Reserved0[2];

} KDHELP64, *PKDHELP64;

typedef struct _tagSTACKFRAME64 {
    ADDRESS64   AddrPC;               // program counter
    ADDRESS64   AddrReturn;           // return address
    ADDRESS64   AddrFrame;            // frame pointer
    ADDRESS64   AddrStack;            // stack pointer
    ADDRESS64   AddrBStore;           // backing store pointer
    PVOID       FuncTableEntry;       // pointer to pdata/fpo or NULL
    DWORD64     Params[4];            // possible arguments to the function
    BOOL        Far;                  // WOW far call
    BOOL        Virtual;              // is this a virtual frame?
    DWORD64     Reserved[3];
    KDHELP64    KdHelp;
} STACKFRAME64, *LPSTACKFRAME64;

typedef struct _SYMBOL_INFO {
    ULONG       SizeOfStruct;
    ULONG       TypeIndex;        // Type Index of symbol
    ULONG64     Reserved[2];
    ULONG       Index;
    ULONG       Size;
    ULONG64     ModBase;          // Base Address of module comtaining this symbol
    ULONG       Flags;
    ULONG64     Value;            // Value of symbol, ValuePresent should be 1
    ULONG64     Address;          // Address of symbol including base address of module
    ULONG       Register;         // register holding value or pointer to value
    ULONG       Scope;            // scope of the symbol
    ULONG       Tag;              // pdb classification
    ULONG       NameLen;          // Actual length of name
    ULONG       MaxNameLen;
    CHAR        Name[1];          // Name of symbol
} SYMBOL_INFO, *PSYMBOL_INFO;

typedef struct _IMAGEHLP_LINE64 {
    DWORD    SizeOfStruct;           // set to sizeof(IMAGEHLP_LINE64)
    PVOID    Key;                    // internal
    DWORD    LineNumber;             // line number in file
    PCHAR    FileName;               // full filename
    DWORD64  Address;                // first instruction of line
} IMAGEHLP_LINE64, *PIMAGEHLP_LINE64;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmicrosoft-anon-tag"
#endif // __clang__
typedef struct _OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    union _OVERLAPPED_DUMMYUNION {
        struct _OVERLAPPED_DUMMYSTRUCT {
            DWORD Offset;
            DWORD OffsetHigh;
        } ;
        PVOID Pointer;
    } ;

    HANDLE hEvent;
} OVERLAPPED, *LPOVERLAPPED;
#ifdef __clang__
#pragma clang diagnostic pop
#endif //__clang__

typedef struct tagMSG {
  HWND   hwnd;
  UINT   message;
  WPARAM wParam;
  LPARAM lParam;
  DWORD  time;
  POINT  pt;
  DWORD  lPrivate;
} MSG, *PMSG, *NPMSG, *LPMSG;

#define CCHDEVICENAME 32
#define CCHFORMNAME 32

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmicrosoft-anon-tag"
#endif // __clang__
typedef struct _devicemodeW {
  WCHAR dmDeviceName[CCHDEVICENAME];
  WORD  dmSpecVersion;
  WORD  dmDriverVersion;
  WORD  dmSize;
  WORD  dmDriverExtra;
  DWORD dmFields;
  union {
    struct {
      short dmOrientation;
      short dmPaperSize;
      short dmPaperLength;
      short dmPaperWidth;
      short dmScale;
      short dmCopies;
      short dmDefaultSource;
      short dmPrintQuality;
    } DUMMYSTRUCTNAME;
    POINTL dmPosition;
    struct {
      POINTL dmPosition;
      DWORD  dmDisplayOrientation;
      DWORD  dmDisplayFixedOutput;
    } DUMMYSTRUCTNAME2;
  } DUMMYUNIONNAME;
  short dmColor;
  short dmDuplex;
  short dmYResolution;
  short dmTTOption;
  short dmCollate;
  WCHAR dmFormName[CCHFORMNAME];
  WORD  dmLogPixels;
  DWORD dmBitsPerPel;
  DWORD dmPelsWidth;
  DWORD dmPelsHeight;
  union {
    DWORD dmDisplayFlags;
    DWORD dmNup;
  } DUMMYUNIONNAME2;
  DWORD dmDisplayFrequency;
  DWORD dmICMMethod;
  DWORD dmICMIntent;
  DWORD dmMediaType;
  DWORD dmDitherType;
  DWORD dmReserved1;
  DWORD dmReserved2;
  DWORD dmPanningWidth;
  DWORD dmPanningHeight;
} DEVMODEW, *PDEVMODEW, *NPDEVMODEW, *LPDEVMODEW;
#ifdef __clang__
#pragma clang diagnostic pop
#endif //__clang__

typedef struct tagMONITORINFO {
    DWORD cbSize;
    RECT  rcMonitor;
    RECT  rcWork;
    DWORD dwFlags;
} MONITORINFO, *LPMONITORINFO;

typedef struct tagMONITORINFOEXW {
    DWORD cbSize;
    RECT  rcMonitor;
    RECT  rcWork;
    DWORD dwFlags;
    WCHAR szDevice[CCHDEVICENAME];
} MONITORINFOEXW, *LPMONITORINFOEXW;

typedef struct _DISPLAY_DEVICEW {
  DWORD cb;
  WCHAR DeviceName[32];
  WCHAR DeviceString[128];
  DWORD StateFlags;
  WCHAR DeviceID[128];
  WCHAR DeviceKey[128];
} DISPLAY_DEVICEW, *PDISPLAY_DEVICEW, *LPDISPLAY_DEVICEW;

typedef struct tagWNDCLASSEXW {
  UINT      cbSize;
  UINT      style;
  WNDPROC   lpfnWndProc;
  int       cbClsExtra;
  int       cbWndExtra;
  HINSTANCE hInstance;
  HICON     hIcon;
  HCURSOR   hCursor;
  HBRUSH    hbrBackground;
  LPCWSTR   lpszMenuName;
  LPCWSTR   lpszClassName;
  HICON     hIconSm;
} WNDCLASSEXW, *PWNDCLASSEXW, *NPWNDCLASSEXW, *LPWNDCLASSEXW;

typedef struct _SECURITY_ATTRIBUTES {
  DWORD  nLength;
  LPVOID lpSecurityDescriptor;
  BOOL   bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct _GUID {
  unsigned long  Data1;
  unsigned short Data2;
  unsigned short Data3;
  unsigned char  Data4[8];
} GUID;
typedef struct tagRGBQUAD {
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
} RGBQUAD;
typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;
typedef struct tagBITMAPINFO {
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD          bmiColors[1];
} BITMAPINFO, *LPBITMAPINFO, *PBITMAPINFO;

typedef struct _STARTUPINFOA {
  DWORD  cb;
  LPSTR  lpReserved;
  LPSTR  lpDesktop;
  LPSTR  lpTitle;
  DWORD  dwX;
  DWORD  dwY;
  DWORD  dwXSize;
  DWORD  dwYSize;
  DWORD  dwXCountChars;
  DWORD  dwYCountChars;
  DWORD  dwFillAttribute;
  DWORD  dwFlags;
  WORD   wShowWindow;
  WORD   cbReserved2;
  LPBYTE lpReserved2;
  HANDLE hStdInput;
  HANDLE hStdOutput;
  HANDLE hStdError;
} STARTUPINFOA, *LPSTARTUPINFOA;

typedef struct _PROCESS_INFORMATION {
  HANDLE hProcess;
  HANDLE hThread;
  DWORD  dwProcessId;
  DWORD  dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;

#define MEM_COMMIT 0x00001000
#define MEM_RESERVE 0x00002000
#define MEM_DECOMMIT 0x00004000
#define MEM_RELEASE 0x00008000

#define PAGE_NOACCESS  0x01
#define PAGE_READWRITE 0x04

#define IMAGE_FILE_MACHINE_UNKNOWN           0
#define IMAGE_FILE_MACHINE_TARGET_HOST       0x0001  // Useful for indicating we want to interact with the host and not a WoW guest.
#define IMAGE_FILE_MACHINE_I386              0x014c  // Intel 386.
#define IMAGE_FILE_MACHINE_R3000             0x0162  // MIPS little-endian, 0x160 big-endian
#define IMAGE_FILE_MACHINE_R4000             0x0166  // MIPS little-endian
#define IMAGE_FILE_MACHINE_R10000            0x0168  // MIPS little-endian
#define IMAGE_FILE_MACHINE_WCEMIPSV2         0x0169  // MIPS little-endian WCE v2
#define IMAGE_FILE_MACHINE_ALPHA             0x0184  // Alpha_AXP
#define IMAGE_FILE_MACHINE_SH3               0x01a2  // SH3 little-endian
#define IMAGE_FILE_MACHINE_SH3DSP            0x01a3
#define IMAGE_FILE_MACHINE_SH3E              0x01a4  // SH3E little-endian
#define IMAGE_FILE_MACHINE_SH4               0x01a6  // SH4 little-endian
#define IMAGE_FILE_MACHINE_SH5               0x01a8  // SH5
#define IMAGE_FILE_MACHINE_ARM               0x01c0  // ARM Little-Endian
#define IMAGE_FILE_MACHINE_THUMB             0x01c2  // ARM Thumb/Thumb-2 Little-Endian
#define IMAGE_FILE_MACHINE_ARMNT             0x01c4  // ARM Thumb-2 Little-Endian
#define IMAGE_FILE_MACHINE_AM33              0x01d3
#define IMAGE_FILE_MACHINE_POWERPC           0x01F0  // IBM PowerPC Little-Endian
#define IMAGE_FILE_MACHINE_POWERPCFP         0x01f1
#define IMAGE_FILE_MACHINE_IA64              0x0200  // Intel 64
#define IMAGE_FILE_MACHINE_MIPS16            0x0266  // MIPS
#define IMAGE_FILE_MACHINE_ALPHA64           0x0284  // ALPHA64
#define IMAGE_FILE_MACHINE_MIPSFPU           0x0366  // MIPS
#define IMAGE_FILE_MACHINE_MIPSFPU16         0x0466  // MIPS
#define IMAGE_FILE_MACHINE_AXP64             IMAGE_FILE_MACHINE_ALPHA64
#define IMAGE_FILE_MACHINE_TRICORE           0x0520  // Infineon
#define IMAGE_FILE_MACHINE_CEF               0x0CEF
#define IMAGE_FILE_MACHINE_EBC               0x0EBC  // EFI Byte Code
#define IMAGE_FILE_MACHINE_AMD64             0x8664  // AMD64 (K8)
#define IMAGE_FILE_MACHINE_M32R              0x9041  // M32R little-endian
#define IMAGE_FILE_MACHINE_ARM64             0xAA64  // ARM64 Little-Endian
#define IMAGE_FILE_MACHINE_CEE               0xC0EE

#define ENUM_CURRENT_SETTINGS       ((DWORD)-1)
#define ENUM_REGISTRY_SETTINGS      ((DWORD)-2)

#define MONITOR_DEFAULTTONULL       0x00000000
#define MONITOR_DEFAULTTOPRIMARY    0x00000001
#define MONITOR_DEFAULTTONEAREST    0x00000002

#define MONITORINFOF_PRIMARY        0x00000001

#define CP_ACP                    0           // default to ANSI code page
#define CP_OEMCP                  1           // default to OEM  code page
#define CP_MACCP                  2           // default to MAC  code page
#define CP_THREAD_ACP             3           // current thread's ANSI code page
#define CP_SYMBOL                 42          // SYMBOL translations

#define CP_UTF7                   65000       // UTF-7 translation
#define CP_UTF8                   65001       // UTF-8 translation

typedef void* DPI_AWARENESS_CONTEXT;
#define DPI_AWARENESS_CONTEXT_UNAWARE              ((DPI_AWARENESS_CONTEXT)-1)
#define DPI_AWARENESS_CONTEXT_SYSTEM_AWARE         ((DPI_AWARENESS_CONTEXT)-2)
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE    ((DPI_AWARENESS_CONTEXT)-3)
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#define DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED    ((DPI_AWARENESS_CONTEXT)-5)

/*
 * Window Styles
 */
#define WS_OVERLAPPED       0x00000000L
#define WS_POPUP            0x80000000L
#define WS_CHILD            0x40000000L
#define WS_MINIMIZE         0x20000000L
#define WS_VISIBLE          0x10000000L
#define WS_DISABLED         0x08000000L
#define WS_CLIPSIBLINGS     0x04000000L
#define WS_CLIPCHILDREN     0x02000000L
#define WS_MAXIMIZE         0x01000000L
#define WS_CAPTION          0x00C00000L     /* WS_BORDER | WS_DLGFRAME  */
#define WS_BORDER           0x00800000L
#define WS_DLGFRAME         0x00400000L
#define WS_VSCROLL          0x00200000L
#define WS_HSCROLL          0x00100000L
#define WS_SYSMENU          0x00080000L
#define WS_THICKFRAME       0x00040000L
#define WS_GROUP            0x00020000L
#define WS_TABSTOP          0x00010000L

#define WS_MINIMIZEBOX      0x00020000L
#define WS_MAXIMIZEBOX      0x00010000L


#define WS_TILED            WS_OVERLAPPED
#define WS_ICONIC           WS_MINIMIZE
#define WS_SIZEBOX          WS_THICKFRAME
#define WS_TILEDWINDOW      WS_OVERLAPPEDWINDOW

/*
 * Common Window Styles
 */
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED     | \
                             WS_CAPTION        | \
                             WS_SYSMENU        | \
                             WS_THICKFRAME     | \
                             WS_MINIMIZEBOX    | \
                             WS_MAXIMIZEBOX)

#define WS_POPUPWINDOW      (WS_POPUP          | \
                             WS_BORDER         | \
                             WS_SYSMENU)

#define WS_CHILDWINDOW      (WS_CHILD)

/*
 * Extended Window Styles
 */
#define WS_EX_DLGMODALFRAME     0x00000001L
#define WS_EX_NOPARENTNOTIFY    0x00000004L
#define WS_EX_TOPMOST           0x00000008L
#define WS_EX_ACCEPTFILES       0x00000010L
#define WS_EX_TRANSPARENT       0x00000020L
#if(WINVER >= 0x0400)
#define WS_EX_MDICHILD          0x00000040L
#define WS_EX_TOOLWINDOW        0x00000080L
#define WS_EX_WINDOWEDGE        0x00000100L
#define WS_EX_CLIENTEDGE        0x00000200L
#define WS_EX_CONTEXTHELP       0x00000400L

#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0400)

#define WS_EX_RIGHT             0x00001000L
#define WS_EX_LEFT              0x00000000L
#define WS_EX_RTLREADING        0x00002000L
#define WS_EX_LTRREADING        0x00000000L
#define WS_EX_LEFTSCROLLBAR     0x00004000L
#define WS_EX_RIGHTSCROLLBAR    0x00000000L

#define WS_EX_CONTROLPARENT     0x00010000L
#define WS_EX_STATICEDGE        0x00020000L
#define WS_EX_APPWINDOW         0x00040000L


#define WS_EX_OVERLAPPEDWINDOW  (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
#define WS_EX_PALETTEWINDOW     (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)

#endif /* WINVER >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
#define WS_EX_LAYERED           0x00080000

#endif /* _WIN32_WINNT >= 0x0500 */


#if(WINVER >= 0x0500)
#define WS_EX_NOINHERITLAYOUT   0x00100000L // Disable inheritence of mirroring by children
#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0602)
#define WS_EX_NOREDIRECTIONBITMAP 0x00200000L
#endif /* WINVER >= 0x0602 */

#if(WINVER >= 0x0500)
#define WS_EX_LAYOUTRTL         0x00400000L // Right to left mirroring
#endif /* WINVER >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
#define WS_EX_COMPOSITED        0x02000000L
#endif /* _WIN32_WINNT >= 0x0501 */
#if(_WIN32_WINNT >= 0x0500)
#define WS_EX_NOACTIVATE        0x08000000L
#endif /* _WIN32_WINNT >= 0x0500 */


/*
 * Class styles
 */
#define CS_VREDRAW          0x0001
#define CS_HREDRAW          0x0002
#define CS_DBLCLKS          0x0008
#define CS_OWNDC            0x0020
#define CS_CLASSDC          0x0040
#define CS_PARENTDC         0x0080
#define CS_NOCLOSE          0x0200
#define CS_SAVEBITS         0x0800
#define CS_BYTEALIGNCLIENT  0x1000
#define CS_BYTEALIGNWINDOW  0x2000
#define CS_GLOBALCLASS      0x4000

#define CS_IME              0x00010000
#if(_WIN32_WINNT >= 0x0501)
#define CS_DROPSHADOW       0x00020000
#endif /* _WIN32_WINNT >= 0x0501 */

#define SW_HIDE             0
#define SW_SHOWNORMAL       1
#define SW_NORMAL           1
#define SW_SHOWMINIMIZED    2
#define SW_SHOWMAXIMIZED    3
#define SW_MAXIMIZE         3
#define SW_SHOWNOACTIVATE   4
#define SW_SHOW             5
#define SW_MINIMIZE         6
#define SW_SHOWMINNOACTIVE  7
#define SW_SHOWNA           8
#define SW_RESTORE          9
#define SW_SHOWDEFAULT      10
#define SW_FORCEMINIMIZE    11
#define SW_MAX              11

#define CW_USEDEFAULT       ((int)0x80000000)

/*
 * Window Messages
 */

#define WM_NULL                         0x0000
#define WM_CREATE                       0x0001
#define WM_DESTROY                      0x0002
#define WM_MOVE                         0x0003
#define WM_SIZE                         0x0005

#define WM_ACTIVATE                     0x0006
/*
 * WM_ACTIVATE state values
 */
#define     WA_INACTIVE     0
#define     WA_ACTIVE       1
#define     WA_CLICKACTIVE  2

#define WM_SETFOCUS                     0x0007
#define WM_KILLFOCUS                    0x0008
#define WM_ENABLE                       0x000A
#define WM_SETREDRAW                    0x000B
#define WM_SETTEXT                      0x000C
#define WM_GETTEXT                      0x000D
#define WM_GETTEXTLENGTH                0x000E
#define WM_PAINT                        0x000F
#define WM_CLOSE                        0x0010
#ifndef _WIN32_WCE
#define WM_QUERYENDSESSION              0x0011
#define WM_QUERYOPEN                    0x0013
#define WM_ENDSESSION                   0x0016
#endif
#define WM_QUIT                         0x0012
#define WM_ERASEBKGND                   0x0014
#define WM_SYSCOLORCHANGE               0x0015
#define WM_SHOWWINDOW                   0x0018
#define WM_WININICHANGE                 0x001A
#if(WINVER >= 0x0400)
#define WM_SETTINGCHANGE                WM_WININICHANGE
#endif /* WINVER >= 0x0400 */


#define WM_DEVMODECHANGE                0x001B
#define WM_ACTIVATEAPP                  0x001C
#define WM_FONTCHANGE                   0x001D
#define WM_TIMECHANGE                   0x001E
#define WM_CANCELMODE                   0x001F
#define WM_SETCURSOR                    0x0020
#define WM_MOUSEACTIVATE                0x0021
#define WM_CHILDACTIVATE                0x0022
#define WM_QUEUESYNC                    0x0023

#define WM_GETMINMAXINFO                0x0024

/*
 * Struct pointed to by WM_GETMINMAXINFO lParam
 */
typedef struct tagMINMAXINFO {
    POINT ptReserved;
    POINT ptMaxSize;
    POINT ptMaxPosition;
    POINT ptMinTrackSize;
    POINT ptMaxTrackSize;
} MINMAXINFO, *PMINMAXINFO, *LPMINMAXINFO;


#define WM_PAINTICON                    0x0026
#define WM_ICONERASEBKGND               0x0027
#define WM_NEXTDLGCTL                   0x0028
#define WM_SPOOLERSTATUS                0x002A
#define WM_DRAWITEM                     0x002B
#define WM_MEASUREITEM                  0x002C
#define WM_DELETEITEM                   0x002D
#define WM_VKEYTOITEM                   0x002E
#define WM_CHARTOITEM                   0x002F
#define WM_SETFONT                      0x0030
#define WM_GETFONT                      0x0031
#define WM_SETHOTKEY                    0x0032
#define WM_GETHOTKEY                    0x0033
#define WM_QUERYDRAGICON                0x0037
#define WM_COMPAREITEM                  0x0039
#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
#define WM_GETOBJECT                    0x003D
#endif
#endif /* WINVER >= 0x0500 */
#define WM_COMPACTING                   0x0041
#define WM_COMMNOTIFY                   0x0044  /* no longer suported */
#define WM_WINDOWPOSCHANGING            0x0046
#define WM_WINDOWPOSCHANGED             0x0047

#define WM_POWER                        0x0048
/*
 * wParam for WM_POWER window message and DRV_POWER driver notification
 */
#define PWR_OK              1
#define PWR_FAIL            (-1)
#define PWR_SUSPENDREQUEST  1
#define PWR_SUSPENDRESUME   2
#define PWR_CRITICALRESUME  3

#define WM_COPYDATA                     0x004A
#define WM_CANCELJOURNAL                0x004B



/*
 * lParam of WM_COPYDATA message points to...
 */
typedef struct tagCOPYDATASTRUCT {
    ULONG_PTR dwData;
    DWORD cbData;
    PVOID lpData;
} COPYDATASTRUCT, *PCOPYDATASTRUCT;

#if(WINVER >= 0x0400)
typedef struct tagMDINEXTMENU
{
    HMENU   hmenuIn;
    HMENU   hmenuNext;
    HWND    hwndNext;
} MDINEXTMENU, * PMDINEXTMENU, * LPMDINEXTMENU;
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)
#define WM_NOTIFY                       0x004E
#define WM_INPUTLANGCHANGEREQUEST       0x0050
#define WM_INPUTLANGCHANGE              0x0051
#define WM_TCARD                        0x0052
#define WM_HELP                         0x0053
#define WM_USERCHANGED                  0x0054
#define WM_NOTIFYFORMAT                 0x0055

#define NFR_ANSI                             1
#define NFR_UNICODE                          2
#define NF_QUERY                             3
#define NF_REQUERY                           4

#define WM_CONTEXTMENU                  0x007B
#define WM_STYLECHANGING                0x007C
#define WM_STYLECHANGED                 0x007D
#define WM_DISPLAYCHANGE                0x007E
#define WM_GETICON                      0x007F
#define WM_SETICON                      0x0080
#endif /* WINVER >= 0x0400 */

#define WM_NCCREATE                     0x0081
#define WM_NCDESTROY                    0x0082
#define WM_NCCALCSIZE                   0x0083
#define WM_NCHITTEST                    0x0084
#define WM_NCPAINT                      0x0085
#define WM_NCACTIVATE                   0x0086
#define WM_GETDLGCODE                   0x0087
#ifndef _WIN32_WCE
#define WM_SYNCPAINT                    0x0088
#endif
#define WM_NCMOUSEMOVE                  0x00A0
#define WM_NCLBUTTONDOWN                0x00A1
#define WM_NCLBUTTONUP                  0x00A2
#define WM_NCLBUTTONDBLCLK              0x00A3
#define WM_NCRBUTTONDOWN                0x00A4
#define WM_NCRBUTTONUP                  0x00A5
#define WM_NCRBUTTONDBLCLK              0x00A6
#define WM_NCMBUTTONDOWN                0x00A7
#define WM_NCMBUTTONUP                  0x00A8
#define WM_NCMBUTTONDBLCLK              0x00A9



#if(_WIN32_WINNT >= 0x0500)
#define WM_NCXBUTTONDOWN                0x00AB
#define WM_NCXBUTTONUP                  0x00AC
#define WM_NCXBUTTONDBLCLK              0x00AD
#endif /* _WIN32_WINNT >= 0x0500 */


#if(_WIN32_WINNT >= 0x0501)
#define WM_INPUT_DEVICE_CHANGE          0x00FE
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0501)
#define WM_INPUT                        0x00FF
#endif /* _WIN32_WINNT >= 0x0501 */

#define WM_KEYFIRST                     0x0100
#define WM_KEYDOWN                      0x0100
#define WM_KEYUP                        0x0101
#define WM_CHAR                         0x0102
#define WM_DEADCHAR                     0x0103
#define WM_SYSKEYDOWN                   0x0104
#define WM_SYSKEYUP                     0x0105
#define WM_SYSCHAR                      0x0106
#define WM_SYSDEADCHAR                  0x0107
#if(_WIN32_WINNT >= 0x0501)
#define WM_UNICHAR                      0x0109
#define WM_KEYLAST                      0x0109
#define UNICODE_NOCHAR                  0xFFFF
#else
#define WM_KEYLAST                      0x0108
#endif /* _WIN32_WINNT >= 0x0501 */

#if(WINVER >= 0x0400)
#define WM_IME_STARTCOMPOSITION         0x010D
#define WM_IME_ENDCOMPOSITION           0x010E
#define WM_IME_COMPOSITION              0x010F
#define WM_IME_KEYLAST                  0x010F
#endif /* WINVER >= 0x0400 */

#define WM_INITDIALOG                   0x0110
#define WM_COMMAND                      0x0111
#define WM_SYSCOMMAND                   0x0112
#define WM_TIMER                        0x0113
#define WM_HSCROLL                      0x0114
#define WM_VSCROLL                      0x0115
#define WM_INITMENU                     0x0116
#define WM_INITMENUPOPUP                0x0117
#if(WINVER >= 0x0601)
#define WM_GESTURE                      0x0119
#define WM_GESTURENOTIFY                0x011A
#endif /* WINVER >= 0x0601 */
#define WM_MENUSELECT                   0x011F
#define WM_MENUCHAR                     0x0120
#define WM_ENTERIDLE                    0x0121
#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
#define WM_MENURBUTTONUP                0x0122
#define WM_MENUDRAG                     0x0123
#define WM_MENUGETOBJECT                0x0124
#define WM_UNINITMENUPOPUP              0x0125
#define WM_MENUCOMMAND                  0x0126

#ifndef _WIN32_WCE
#if(_WIN32_WINNT >= 0x0500)
#define WM_CHANGEUISTATE                0x0127
#define WM_UPDATEUISTATE                0x0128
#define WM_QUERYUISTATE                 0x0129

/*
 * LOWORD(wParam) values in WM_*UISTATE*
 */
#define UIS_SET                         1
#define UIS_CLEAR                       2
#define UIS_INITIALIZE                  3

/*
 * HIWORD(wParam) values in WM_*UISTATE*
 */
#define UISF_HIDEFOCUS                  0x1
#define UISF_HIDEACCEL                  0x2
#if(_WIN32_WINNT >= 0x0501)
#define UISF_ACTIVE                     0x4
#endif /* _WIN32_WINNT >= 0x0501 */
#endif /* _WIN32_WINNT >= 0x0500 */
#endif

#endif
#endif /* WINVER >= 0x0500 */

#define WM_CTLCOLORMSGBOX               0x0132
#define WM_CTLCOLOREDIT                 0x0133
#define WM_CTLCOLORLISTBOX              0x0134
#define WM_CTLCOLORBTN                  0x0135
#define WM_CTLCOLORDLG                  0x0136
#define WM_CTLCOLORSCROLLBAR            0x0137
#define WM_CTLCOLORSTATIC               0x0138
#define MN_GETHMENU                     0x01E1

#define WM_MOUSEFIRST                   0x0200
#define WM_MOUSEMOVE                    0x0200
#define WM_LBUTTONDOWN                  0x0201
#define WM_LBUTTONUP                    0x0202
#define WM_LBUTTONDBLCLK                0x0203
#define WM_RBUTTONDOWN                  0x0204
#define WM_RBUTTONUP                    0x0205
#define WM_RBUTTONDBLCLK                0x0206
#define WM_MBUTTONDOWN                  0x0207
#define WM_MBUTTONUP                    0x0208
#define WM_MBUTTONDBLCLK                0x0209
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#define WM_MOUSEWHEEL                   0x020A
#endif
#if (_WIN32_WINNT >= 0x0500)
#define WM_XBUTTONDOWN                  0x020B
#define WM_XBUTTONUP                    0x020C
#define WM_XBUTTONDBLCLK                0x020D
#endif
#if (_WIN32_WINNT >= 0x0600)
#define WM_MOUSEHWHEEL                  0x020E
#endif

#if (_WIN32_WINNT >= 0x0600)
#define WM_MOUSELAST                    0x020E
#elif (_WIN32_WINNT >= 0x0500)
#define WM_MOUSELAST                    0x020D
#elif (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#define WM_MOUSELAST                    0x020A
#else
#define WM_MOUSELAST                    0x0209
#endif /* (_WIN32_WINNT >= 0x0600) */


#if(_WIN32_WINNT >= 0x0400)
/* Value for rolling one detent */
#define WHEEL_DELTA                     120
#define GET_WHEEL_DELTA_WPARAM(wParam)  ((short)HIWORD(wParam))

/* Setting to scroll one page for SPI_GET/SETWHEELSCROLLLINES */
#define WHEEL_PAGESCROLL                (UINT_MAX)
#endif /* _WIN32_WINNT >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
#define GET_KEYSTATE_WPARAM(wParam)     (LOWORD(wParam))
#define GET_NCHITTEST_WPARAM(wParam)    ((short)LOWORD(wParam))
#define GET_XBUTTON_WPARAM(wParam)      (HIWORD(wParam))

/* XButton values are WORD flags */
#define XBUTTON1      0x0001
#define XBUTTON2      0x0002
/* Were there to be an XBUTTON3, its value would be 0x0004 */
#endif /* _WIN32_WINNT >= 0x0500 */

#define WM_PARENTNOTIFY                 0x0210
#define WM_ENTERMENULOOP                0x0211
#define WM_EXITMENULOOP                 0x0212

#if(WINVER >= 0x0400)
#define WM_NEXTMENU                     0x0213
#define WM_SIZING                       0x0214
#define WM_CAPTURECHANGED               0x0215
#define WM_MOVING                       0x0216
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)


#define WM_POWERBROADCAST               0x0218

#ifndef _WIN32_WCE
#define PBT_APMQUERYSUSPEND             0x0000
#define PBT_APMQUERYSTANDBY             0x0001

#define PBT_APMQUERYSUSPENDFAILED       0x0002
#define PBT_APMQUERYSTANDBYFAILED       0x0003

#define PBT_APMSUSPEND                  0x0004
#define PBT_APMSTANDBY                  0x0005

#define PBT_APMRESUMECRITICAL           0x0006
#define PBT_APMRESUMESUSPEND            0x0007
#define PBT_APMRESUMESTANDBY            0x0008

#define PBTF_APMRESUMEFROMFAILURE       0x00000001

#define PBT_APMBATTERYLOW               0x0009
#define PBT_APMPOWERSTATUSCHANGE        0x000A

#define PBT_APMOEMEVENT                 0x000B


#define PBT_APMRESUMEAUTOMATIC          0x0012
#if (_WIN32_WINNT >= 0x0502)
#ifndef PBT_POWERSETTINGCHANGE
#define PBT_POWERSETTINGCHANGE          0x8013

typedef struct {
    GUID PowerSetting;
    DWORD DataLength;
    UCHAR Data[1];
} POWERBROADCAST_SETTING, *PPOWERBROADCAST_SETTING;


#endif // PBT_POWERSETTINGCHANGE

#endif // (_WIN32_WINNT >= 0x0502)
#endif

#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)
#define WM_DEVICECHANGE                 0x0219
#endif /* WINVER >= 0x0400 */

#define WM_MDICREATE                    0x0220
#define WM_MDIDESTROY                   0x0221
#define WM_MDIACTIVATE                  0x0222
#define WM_MDIRESTORE                   0x0223
#define WM_MDINEXT                      0x0224
#define WM_MDIMAXIMIZE                  0x0225
#define WM_MDITILE                      0x0226
#define WM_MDICASCADE                   0x0227
#define WM_MDIICONARRANGE               0x0228
#define WM_MDIGETACTIVE                 0x0229


#define WM_MDISETMENU                   0x0230
#define WM_ENTERSIZEMOVE                0x0231
#define WM_EXITSIZEMOVE                 0x0232
#define WM_DROPFILES                    0x0233
#define WM_MDIREFRESHMENU               0x0234

#if(WINVER >= 0x0602)
#define WM_POINTERDEVICECHANGE          0x238
#define WM_POINTERDEVICEINRANGE         0x239
#define WM_POINTERDEVICEOUTOFRANGE      0x23A
#endif /* WINVER >= 0x0602 */


#if(WINVER >= 0x0601)
#define WM_TOUCH                        0x0240
#endif /* WINVER >= 0x0601 */

#if(WINVER >= 0x0602)
#define WM_NCPOINTERUPDATE              0x0241
#define WM_NCPOINTERDOWN                0x0242
#define WM_NCPOINTERUP                  0x0243
#define WM_POINTERUPDATE                0x0245
#define WM_POINTERDOWN                  0x0246
#define WM_POINTERUP                    0x0247
#define WM_POINTERENTER                 0x0249
#define WM_POINTERLEAVE                 0x024A
#define WM_POINTERACTIVATE              0x024B
#define WM_POINTERCAPTURECHANGED        0x024C
#define WM_TOUCHHITTESTING              0x024D
#define WM_POINTERWHEEL                 0x024E
#define WM_POINTERHWHEEL                0x024F
#define DM_POINTERHITTEST               0x0250
#define WM_POINTERROUTEDTO              0x0251
#define WM_POINTERROUTEDAWAY            0x0252
#define WM_POINTERROUTEDRELEASED        0x0253
#endif /* WINVER >= 0x0602 */


#if(WINVER >= 0x0400)
#define WM_IME_SETCONTEXT               0x0281
#define WM_IME_NOTIFY                   0x0282
#define WM_IME_CONTROL                  0x0283
#define WM_IME_COMPOSITIONFULL          0x0284
#define WM_IME_SELECT                   0x0285
#define WM_IME_CHAR                     0x0286
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0500)
#define WM_IME_REQUEST                  0x0288
#endif /* WINVER >= 0x0500 */
#if(WINVER >= 0x0400)
#define WM_IME_KEYDOWN                  0x0290
#define WM_IME_KEYUP                    0x0291
#endif /* WINVER >= 0x0400 */

#if((_WIN32_WINNT >= 0x0400) || (WINVER >= 0x0500))
#define WM_MOUSEHOVER                   0x02A1
#define WM_MOUSELEAVE                   0x02A3
#endif
#if(WINVER >= 0x0500)
#define WM_NCMOUSEHOVER                 0x02A0
#define WM_NCMOUSELEAVE                 0x02A2
#endif /* WINVER >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
#define WM_WTSSESSION_CHANGE            0x02B1

#define WM_TABLET_FIRST                 0x02c0
#define WM_TABLET_LAST                  0x02df
#endif /* _WIN32_WINNT >= 0x0501 */

#if(WINVER >= 0x0601)
#define WM_DPICHANGED                   0x02E0
#endif /* WINVER >= 0x0601 */
#if(WINVER >= 0x0605)
#define WM_DPICHANGED_BEFOREPARENT      0x02E2
#define WM_DPICHANGED_AFTERPARENT       0x02E3
#define WM_GETDPISCALEDSIZE             0x02E4
#endif /* WINVER >= 0x0605 */

#define WM_CUT                          0x0300
#define WM_COPY                         0x0301
#define WM_PASTE                        0x0302
#define WM_CLEAR                        0x0303
#define WM_UNDO                         0x0304
#define WM_RENDERFORMAT                 0x0305
#define WM_RENDERALLFORMATS             0x0306
#define WM_DESTROYCLIPBOARD             0x0307
#define WM_DRAWCLIPBOARD                0x0308
#define WM_PAINTCLIPBOARD               0x0309
#define WM_VSCROLLCLIPBOARD             0x030A
#define WM_SIZECLIPBOARD                0x030B
#define WM_ASKCBFORMATNAME              0x030C
#define WM_CHANGECBCHAIN                0x030D
#define WM_HSCROLLCLIPBOARD             0x030E
#define WM_QUERYNEWPALETTE              0x030F
#define WM_PALETTEISCHANGING            0x0310
#define WM_PALETTECHANGED               0x0311
#define WM_HOTKEY                       0x0312

#if(WINVER >= 0x0400)
#define WM_PRINT                        0x0317
#define WM_PRINTCLIENT                  0x0318
#endif /* WINVER >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
#define WM_APPCOMMAND                   0x0319
#endif /* _WIN32_WINNT >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
#define WM_THEMECHANGED                 0x031A
#endif /* _WIN32_WINNT >= 0x0501 */


#if(_WIN32_WINNT >= 0x0501)
#define WM_CLIPBOARDUPDATE              0x031D
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0600)
#define WM_DWMCOMPOSITIONCHANGED        0x031E
#define WM_DWMNCRENDERINGCHANGED        0x031F
#define WM_DWMCOLORIZATIONCOLORCHANGED  0x0320
#define WM_DWMWINDOWMAXIMIZEDCHANGE     0x0321
#endif /* _WIN32_WINNT >= 0x0600 */

#if(_WIN32_WINNT >= 0x0601)
#define WM_DWMSENDICONICTHUMBNAIL           0x0323
#define WM_DWMSENDICONICLIVEPREVIEWBITMAP   0x0326
#endif /* _WIN32_WINNT >= 0x0601 */


#if(WINVER >= 0x0600)
#define WM_GETTITLEBARINFOEX            0x033F
#endif /* WINVER >= 0x0600 */

#if(WINVER >= 0x0400)
#endif /* WINVER >= 0x0400 */


#if(WINVER >= 0x0400)
#define WM_HANDHELDFIRST                0x0358
#define WM_HANDHELDLAST                 0x035F

#define WM_AFXFIRST                     0x0360
#define WM_AFXLAST                      0x037F
#endif /* WINVER >= 0x0400 */

#define WM_PENWINFIRST                  0x0380
#define WM_PENWINLAST                   0x038F


#if(WINVER >= 0x0400)
#define WM_APP                          0x8000
#endif /* WINVER >= 0x0400 */


/*
 * NOTE: All Message Numbers below 0x0400 are RESERVED.
 *
 * Private Window Messages Start Here:
 */
#define WM_USER                         0x0400

#if(WINVER >= 0x0400)

/*  wParam for WM_SIZING message  */
#define WMSZ_LEFT           1
#define WMSZ_RIGHT          2
#define WMSZ_TOP            3
#define WMSZ_TOPLEFT        4
#define WMSZ_TOPRIGHT       5
#define WMSZ_BOTTOM         6
#define WMSZ_BOTTOMLEFT     7
#define WMSZ_BOTTOMRIGHT    8
#endif /* WINVER >= 0x0400 */

#ifndef NONCMESSAGES

/*
 * WM_NCHITTEST and MOUSEHOOKSTRUCT Mouse Position Codes
 */
#define HTERROR             (-2)
#define HTTRANSPARENT       (-1)
#define HTNOWHERE           0
#define HTCLIENT            1
#define HTCAPTION           2
#define HTSYSMENU           3
#define HTGROWBOX           4
#define HTSIZE              HTGROWBOX
#define HTMENU              5
#define HTHSCROLL           6
#define HTVSCROLL           7
#define HTMINBUTTON         8
#define HTMAXBUTTON         9
#define HTLEFT              10
#define HTRIGHT             11
#define HTTOP               12
#define HTTOPLEFT           13
#define HTTOPRIGHT          14
#define HTBOTTOM            15
#define HTBOTTOMLEFT        16
#define HTBOTTOMRIGHT       17
#define HTBORDER            18
#define HTREDUCE            HTMINBUTTON
#define HTZOOM              HTMAXBUTTON
#define HTSIZEFIRST         HTLEFT
#define HTSIZELAST          HTBOTTOMRIGHT
#if(WINVER >= 0x0400)
#define HTOBJECT            19
#define HTCLOSE             20
#define HTHELP              21
#endif /* WINVER >= 0x0400 */


/*
 * SendMessageTimeout values
 */
#define SMTO_NORMAL         0x0000
#define SMTO_BLOCK          0x0001
#define SMTO_ABORTIFHUNG    0x0002
#if(WINVER >= 0x0500)
#define SMTO_NOTIMEOUTIFNOTHUNG 0x0008
#endif /* WINVER >= 0x0500 */
#if(WINVER >= 0x0600)
#define SMTO_ERRORONEXIT    0x0020
#endif /* WINVER >= 0x0600 */
#if(WINVER >= 0x0602)
#endif /* WINVER >= 0x0602 */

#endif /* !NONCMESSAGES */

/*
 * WM_MOUSEACTIVATE Return Codes
 */
#define MA_ACTIVATE         1
#define MA_ACTIVATEANDEAT   2
#define MA_NOACTIVATE       3
#define MA_NOACTIVATEANDEAT 4

/*
 * WM_SETICON / WM_GETICON Type Codes
 */
#define ICON_SMALL          0
#define ICON_BIG            1
#if(_WIN32_WINNT >= 0x0501)
#define ICON_SMALL2         2
#endif /* _WIN32_WINNT >= 0x0501 */



/*
 * WM_SIZE message wParam values
 */
#define SIZE_RESTORED       0
#define SIZE_MINIMIZED      1
#define SIZE_MAXIMIZED      2
#define SIZE_MAXSHOW        3
#define SIZE_MAXHIDE        4

/*
 * Obsolete constant names
 */
#define SIZENORMAL          SIZE_RESTORED
#define SIZEICONIC          SIZE_MINIMIZED
#define SIZEFULLSCREEN      SIZE_MAXIMIZED
#define SIZEZOOMSHOW        SIZE_MAXSHOW
#define SIZEZOOMHIDE        SIZE_MAXHIDE


/*
 * WM_WINDOWPOSCHANGING/CHANGED struct pointed to by lParam
 */
typedef struct tagWINDOWPOS {
    HWND    hwnd;
    HWND    hwndInsertAfter;
    int     x;
    int     y;
    int     cx;
    int     cy;
    UINT    flags;
} WINDOWPOS, *LPWINDOWPOS, *PWINDOWPOS;

/*
 * WM_NCCALCSIZE parameter structure
 */
typedef struct tagNCCALCSIZE_PARAMS {
    RECT       rgrc[3];
    PWINDOWPOS lppos;
} NCCALCSIZE_PARAMS, *LPNCCALCSIZE_PARAMS;

/*
 * WM_NCCALCSIZE "window valid rect" return values
 */
#define WVR_ALIGNTOP        0x0010
#define WVR_ALIGNLEFT       0x0020
#define WVR_ALIGNBOTTOM     0x0040
#define WVR_ALIGNRIGHT      0x0080
#define WVR_HREDRAW         0x0100
#define WVR_VREDRAW         0x0200
#define WVR_REDRAW         (WVR_HREDRAW | \
                            WVR_VREDRAW)
#define WVR_VALIDRECTS      0x0400


#ifndef NOKEYSTATES

/*
 * Key State Masks for Mouse Messages
 */
#define MK_LBUTTON          0x0001
#define MK_RBUTTON          0x0002
#define MK_SHIFT            0x0004
#define MK_CONTROL          0x0008
#define MK_MBUTTON          0x0010
#if(_WIN32_WINNT >= 0x0500)
#define MK_XBUTTON1         0x0020
#define MK_XBUTTON2         0x0040
#endif /* _WIN32_WINNT >= 0x0500 */

#endif /* !NOKEYSTATES */


#if(_WIN32_WINNT >= 0x0400)
#ifndef NOTRACKMOUSEEVENT

#define TME_HOVER       0x00000001
#define TME_LEAVE       0x00000002
#if(WINVER >= 0x0500)
#define TME_NONCLIENT   0x00000010
#endif /* WINVER >= 0x0500 */
#define TME_QUERY       0x40000000
#define TME_CANCEL      0x80000000


#define HOVER_DEFAULT   0xFFFFFFFF
#endif /* _WIN32_WINNT >= 0x0400 */

#if(_WIN32_WINNT >= 0x0400)

typedef struct tagTRACKMOUSEEVENT {
    DWORD cbSize;
    DWORD dwFlags;
    HWND  hwndTrack;
    DWORD dwHoverTime;
} TRACKMOUSEEVENT, *LPTRACKMOUSEEVENT;


#endif /* _WIN32_WINNT >= 0x0400 */

#if(_WIN32_WINNT >= 0x0400)

#endif /* !NOTRACKMOUSEEVENT */
#endif /* _WIN32_WINNT >= 0x0400 */

#define PM_NOREMOVE         0x0000
#define PM_REMOVE           0x0001
#define PM_NOYIELD          0x0002

#define HWND_BOTTOM ((HWND)1)
#define HWND_NOTOPMOST ((HWND)-2)
#define HWND_TOP ((HWND)0)
#define HWND_TOPMOST ((HWND)-1)

/*
 * SetWindowPos Flags
 */
#define SWP_NOSIZE          0x0001
#define SWP_NOMOVE          0x0002
#define SWP_NOZORDER        0x0004
#define SWP_NOREDRAW        0x0008
#define SWP_NOACTIVATE      0x0010
#define SWP_FRAMECHANGED    0x0020  /* The frame changed: send WM_NCCALCSIZE */
#define SWP_SHOWWINDOW      0x0040
#define SWP_HIDEWINDOW      0x0080
#define SWP_NOCOPYBITS      0x0100
#define SWP_NOOWNERZORDER   0x0200  /* Don't do owner Z ordering */
#define SWP_NOSENDCHANGING  0x0400  /* Don't send WM_WINDOWPOSCHANGING */

#define SWP_DRAWFRAME       SWP_FRAMECHANGED
#define SWP_NOREPOSITION    SWP_NOOWNERZORDER

#if(WINVER >= 0x0400)
#define SWP_DEFERERASE      0x2000 // same as SWP_DEFERDRAWING
#define SWP_ASYNCWINDOWPOS  0x4000 // same as SWP_CREATESPB
#endif /* WINVER >= 0x0400 */

#define FILE_READ_DATA            ( 0x0001 )    // file & pipe
#define FILE_LIST_DIRECTORY       ( 0x0001 )    // directory

#define FILE_WRITE_DATA           ( 0x0002 )    // file & pipe
#define FILE_ADD_FILE             ( 0x0002 )    // directory

#define FILE_APPEND_DATA          ( 0x0004 )    // file
#define FILE_ADD_SUBDIRECTORY     ( 0x0004 )    // directory
#define FILE_CREATE_PIPE_INSTANCE ( 0x0004 )    // named pipe


#define FILE_READ_EA              ( 0x0008 )    // file & directory

#define FILE_WRITE_EA             ( 0x0010 )    // file & directory

#define FILE_EXECUTE              ( 0x0020 )    // file
#define FILE_TRAVERSE             ( 0x0020 )    // directory

#define FILE_DELETE_CHILD         ( 0x0040 )    // directory

#define FILE_READ_ATTRIBUTES      ( 0x0080 )    // all

#define FILE_WRITE_ATTRIBUTES     ( 0x0100 )    // all

#define FILE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1FF)

#define FILE_GENERIC_READ         (STANDARD_RIGHTS_READ     |\
                                   FILE_READ_DATA           |\
                                   FILE_READ_ATTRIBUTES     |\
                                   FILE_READ_EA             |\
                                   SYNCHRONIZE)


#define FILE_GENERIC_WRITE        (STANDARD_RIGHTS_WRITE    |\
                                   FILE_WRITE_DATA          |\
                                   FILE_WRITE_ATTRIBUTES    |\
                                   FILE_WRITE_EA            |\
                                   FILE_APPEND_DATA         |\
                                   SYNCHRONIZE)


#define FILE_GENERIC_EXECUTE      (STANDARD_RIGHTS_EXECUTE  |\
                                   FILE_READ_ATTRIBUTES     |\
                                   FILE_EXECUTE             |\
                                   SYNCHRONIZE)

// end_access
#define FILE_SHARE_READ                 0x00000001  
#define FILE_SHARE_WRITE                0x00000002  
#define FILE_SHARE_DELETE               0x00000004  
#define FILE_ATTRIBUTE_READONLY             0x00000001  
#define FILE_ATTRIBUTE_HIDDEN               0x00000002  
#define FILE_ATTRIBUTE_SYSTEM               0x00000004  
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020  
#define FILE_ATTRIBUTE_DEVICE               0x00000040  
#define FILE_ATTRIBUTE_NORMAL               0x00000080  
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100  
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200  
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400  
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800  
#define FILE_ATTRIBUTE_OFFLINE              0x00001000  
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000  
#define FILE_ATTRIBUTE_ENCRYPTED            0x00004000  
#define FILE_ATTRIBUTE_INTEGRITY_STREAM     0x00008000  
#define FILE_ATTRIBUTE_VIRTUAL              0x00010000  
#define FILE_ATTRIBUTE_NO_SCRUB_DATA        0x00020000  
#define FILE_ATTRIBUTE_EA                   0x00040000  
#define FILE_ATTRIBUTE_PINNED               0x00080000  
#define FILE_ATTRIBUTE_UNPINNED             0x00100000  
#define FILE_ATTRIBUTE_RECALL_ON_OPEN       0x00040000  
#define FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS 0x00400000 
#define TREE_CONNECT_ATTRIBUTE_PRIVACY      0x00004000  
#define TREE_CONNECT_ATTRIBUTE_INTEGRITY    0x00008000  
#define TREE_CONNECT_ATTRIBUTE_GLOBAL       0x00000004  
#define TREE_CONNECT_ATTRIBUTE_PINNED       0x00000002  
#define FILE_ATTRIBUTE_STRICTLY_SEQUENTIAL  0x20000000  
#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001   
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002   
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004   
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008   
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010   
#define FILE_NOTIFY_CHANGE_LAST_ACCESS  0x00000020   
#define FILE_NOTIFY_CHANGE_CREATION     0x00000040   
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100   
#define FILE_ACTION_ADDED                   0x00000001   
#define FILE_ACTION_REMOVED                 0x00000002   
#define FILE_ACTION_MODIFIED                0x00000003   
#define FILE_ACTION_RENAMED_OLD_NAME        0x00000004   
#define FILE_ACTION_RENAMED_NEW_NAME        0x00000005   
#define MAILSLOT_NO_MESSAGE             ((DWORD)-1) 
#define MAILSLOT_WAIT_FOREVER           ((DWORD)-1) 
#define FILE_CASE_SENSITIVE_SEARCH          0x00000001  
#define FILE_CASE_PRESERVED_NAMES           0x00000002  
#define FILE_UNICODE_ON_DISK                0x00000004  
#define FILE_PERSISTENT_ACLS                0x00000008  
#define FILE_FILE_COMPRESSION               0x00000010  
#define FILE_VOLUME_QUOTAS                  0x00000020  
#define FILE_SUPPORTS_SPARSE_FILES          0x00000040  
#define FILE_SUPPORTS_REPARSE_POINTS        0x00000080  
#define FILE_SUPPORTS_REMOTE_STORAGE        0x00000100  
#define FILE_RETURNS_CLEANUP_RESULT_INFO    0x00000200  
#define FILE_SUPPORTS_POSIX_UNLINK_RENAME   0x00000400  




#define FILE_VOLUME_IS_COMPRESSED           0x00008000  
#define FILE_SUPPORTS_OBJECT_IDS            0x00010000  
#define FILE_SUPPORTS_ENCRYPTION            0x00020000  
#define FILE_NAMED_STREAMS                  0x00040000  
#define FILE_READ_ONLY_VOLUME               0x00080000  
#define FILE_SEQUENTIAL_WRITE_ONCE          0x00100000  
#define FILE_SUPPORTS_TRANSACTIONS          0x00200000  
#define FILE_SUPPORTS_HARD_LINKS            0x00400000  
#define FILE_SUPPORTS_EXTENDED_ATTRIBUTES   0x00800000  
#define FILE_SUPPORTS_OPEN_BY_FILE_ID       0x01000000  
#define FILE_SUPPORTS_USN_JOURNAL           0x02000000  
#define FILE_SUPPORTS_INTEGRITY_STREAMS     0x04000000  
#define FILE_SUPPORTS_BLOCK_REFCOUNTING     0x08000000  
#define FILE_SUPPORTS_SPARSE_VDL            0x10000000  
#define FILE_DAX_VOLUME                     0x20000000  
#define FILE_SUPPORTS_GHOSTING              0x40000000  

#define FILE_INVALID_FILE_ID               ((LONGLONG)-1LL) 

#define DELETE                           (0x00010000L)
#define READ_CONTROL                     (0x00020000L)
#define WRITE_DAC                        (0x00040000L)
#define WRITE_OWNER                      (0x00080000L)
#define SYNCHRONIZE                      (0x00100000L)

#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)

#define STANDARD_RIGHTS_READ             (READ_CONTROL)
#define STANDARD_RIGHTS_WRITE            (READ_CONTROL)
#define STANDARD_RIGHTS_EXECUTE          (READ_CONTROL)

#define STANDARD_RIGHTS_ALL              (0x001F0000L)

#define SPECIFIC_RIGHTS_ALL              (0x0000FFFFL)

#define CREATE_ALWAYS 2
#define CREATE_NEW 1
#define OPEN_ALWAYS 4
#define OPEN_EXISTING 3
#define TRUNCATE_EXISTING 5

#define INVALID_HANDLE_VALUE ((HANDLE)-1)

#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L
#define BI_JPEG       4L
#define BI_PNG        5L

#define DIB_RGB_COLORS      0 /* color table in RGBs */
#define DIB_PAL_COLORS      1 /* color table in palette indices */

#define SRCCOPY             (DWORD)0x00CC0020 /* dest = source                   */
#define SRCPAINT            (DWORD)0x00EE0086 /* dest = source OR dest           */
#define SRCAND              (DWORD)0x008800C6 /* dest = source AND dest          */
#define SRCINVERT           (DWORD)0x00660046 /* dest = source XOR dest          */
#define SRCERASE            (DWORD)0x00440328 /* dest = source AND (NOT dest )   */
#define NOTSRCCOPY          (DWORD)0x00330008 /* dest = (NOT source)             */
#define NOTSRCERASE         (DWORD)0x001100A6 /* dest = (NOT src) AND (NOT dest) */
#define MERGECOPY           (DWORD)0x00C000CA /* dest = (source AND pattern)     */
#define MERGEPAINT          (DWORD)0x00BB0226 /* dest = (NOT source) OR dest     */
#define PATCOPY             (DWORD)0x00F00021 /* dest = pattern                  */
#define PATPAINT            (DWORD)0x00FB0A09 /* dest = DPSnoo                   */
#define PATINVERT           (DWORD)0x005A0049 /* dest = pattern XOR dest         */
#define DSTINVERT           (DWORD)0x00550009 /* dest = (NOT dest)               */
#define BLACKNESS           (DWORD)0x00000042 /* dest = BLACK                    */
#define WHITENESS           (DWORD)0x00FF0062 /* dest = WHITE                    */

#define MONITOR_DEFAULTTONULL       0x00000000
#define MONITOR_DEFAULTTOPRIMARY    0x00000001
#define MONITOR_DEFAULTTONEAREST    0x00000002

WINDOWS_IMPORT void WINAPI GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);

WINDOWS_IMPORT void* WINAPI VirtualAlloc(void *lpAddress, size_t dwSize, u32 flAllocationType, u32 flProtect);
WINDOWS_IMPORT s32 WINAPI VirtualFree(void *lpAddress, size_t dwSize, u32 dwFreeType);

WINDOWS_IMPORT size_t WINAPI VirtualQuery(void* lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, u32 dwLength);

WINDOWS_IMPORT void* WINAPI GetStdHandle(u32 nStdHandle);
WINDOWS_IMPORT BOOL WINAPI SetStdHandle( DWORD nStdHandle, HANDLE hHandle);

WINDOWS_IMPORT s32 WINAPI WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
WINDOWS_IMPORT BOOL WINAPI ReadFile( HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);

WINDOWS_IMPORT void* WINAPI GetCurrentProcess(void);
WINDOWS_IMPORT void* WINAPI GetCurrentThread(void);
WINDOWS_IMPORT BOOL WINAPI SymInitialize(HANDLE hProcess, PCSTR UserSearchPath, BOOL fInvadeProcess);
WINDOWS_IMPORT int WINAPI SymCleanup(HANDLE hProcess);
WINDOWS_IMPORT BOOL WINAPI SymFromAddr(HANDLE hProcess, DWORD64 Address, PDWORD64 Displacement, PSYMBOL_INFO Symbol);
WINDOWS_IMPORT int WINAPI SymGetLineFromAddr64(HANDLE hProcess, DWORD64 dwAddr, PDWORD pdwDisplacement, PIMAGEHLP_LINE64 Line);
WINDOWS_IMPORT HANDLE WINAPI SymFunctionTableAccess64(HANDLE hProcess, DWORD64 AddrBase);
WINDOWS_IMPORT DWORD64 WINAPI SymGetModuleBase64(HANDLE hProcess, DWORD64 Address);
typedef BOOL (__stdcall *PREAD_PROCESS_MEMORY_ROUTINE64)( HANDLE hProcess, DWORD64 qwBaseAddress,  PVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead);
typedef PVOID (__stdcall *PFUNCTION_TABLE_ACCESS_ROUTINE64)( HANDLE ahProcess, DWORD64 AddrBase);
typedef DWORD64 (__stdcall *PGET_MODULE_BASE_ROUTINE64)( HANDLE hProcess, DWORD64 Address);
typedef DWORD64 (__stdcall *PTRANSLATE_ADDRESS_ROUTINE64)( HANDLE hProcess, HANDLE hThread, LPADDRESS64 lpaddr);
WINDOWS_IMPORT BOOL WINAPI StackWalk64( DWORD MachineType, HANDLE hProcess, HANDLE hThread, LPSTACKFRAME64 StackFrame, PVOID ContextRecord, PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine, PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine, PGET_MODULE_BASE_ROUTINE64 GetModuleBaseRoutine, PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress);
WINDOWS_IMPORT void WINAPI RtlCaptureContext(PCONTEXT ContextRecord);

WINDOWS_IMPORT BOOL WINAPI GetMonitorInfoW( HMONITOR hMonitor, LPMONITORINFO lpmi);
WINDOWS_IMPORT BOOL WINAPI EnumDisplaySettingsW( LPCWSTR lpszDeviceName, DWORD iModeNum, DEVMODEW *lpDevMode);

WINDOWS_IMPORT BOOL WINAPI EnumDisplayDevicesW( LPCWSTR lpDevice, DWORD iDevNum, PDISPLAY_DEVICEW lpDisplayDevice, DWORD dwFlags);



WINDOWS_IMPORT HMONITOR WINAPI MonitorFromWindow( HWND hwnd, DWORD dwFlags);

WINDOWS_IMPORT int WINAPI WideCharToMultiByte( UINT CodePage, DWORD dwFlags, LPCWCH lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar);

typedef BOOL (*MONITORENUMPROC)( HMONITOR unnamedParam1, HDC unnamedParam2, LPRECT unnamedParam3, LPARAM unnamedParam4);
WINDOWS_IMPORT BOOL WINAPI EnumDisplayMonitors( HDC hdc, LPCRECT lprcClip, MONITORENUMPROC lpfnEnum, LPARAM dwData);

WINDOWS_IMPORT HMODULE WINAPI GetModuleHandleA(LPCSTR lpModuleName);
WINDOWS_IMPORT HMODULE WINAPI GetModuleHandleW(LPCWSTR lpModuleName);

WINDOWS_IMPORT ATOM WINAPI RegisterClassExW(const WNDCLASSEXW *unnamedParam1);

WINDOWS_IMPORT BOOL WINAPI AdjustWindowRectEx( LPRECT lpRect, DWORD  dwStyle, BOOL   bMenu, DWORD  dwExStyle);

WINDOWS_IMPORT DWORD WINAPI GetLastError(void);
WINDOWS_IMPORT void WINAPI SetLastError(DWORD);

WINDOWS_IMPORT HWND WINAPI CreateWindowExW(
    DWORD     dwExStyle,
    LPCWSTR   lpClassName,
    LPCWSTR   lpWindowName,
    DWORD     dwStyle,
    int       X,
    int       Y,
    int       nWidth,
    int       nHeight,
    HWND      hWndParent,
    HMENU     hMenu,
    HINSTANCE hInstance,
    LPVOID    lpParam
);
WINDOWS_IMPORT BOOL WINAPI UpdateWindow(HWND hWnd);
WINDOWS_IMPORT BOOL WINAPI ShowWindow( HWND hWnd, int  nCmdShow);

WINDOWS_IMPORT int WINAPI MultiByteToWideChar( UINT CodePage, DWORD dwFlags, LPCCH lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);

WINDOWS_IMPORT BOOL WINAPI PeekMessageW( LPMSG lpMsg, HWND  hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax, UINT  wRemoveMsg);

WINDOWS_IMPORT BOOL WINAPI TranslateMessage(const MSG *lpMsg);

WINDOWS_IMPORT LRESULT WINAPI DispatchMessageW(const MSG *lpMsg);

WINDOWS_IMPORT LRESULT WINAPI DefWindowProcW(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);

WINDOWS_IMPORT BOOL WINAPI DestroyWindow(HWND hWnd);

WINDOWS_IMPORT LONG WINAPI GetWindowLongW( HWND hWnd, int nIndex);
WINDOWS_IMPORT LONG WINAPI SetWindowLongW(HWND hWnd, int nIndex, LONG dwNewLong);
WINDOWS_IMPORT BOOL WINAPI SetWindowPos( HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);

WINDOWS_IMPORT BOOL WINAPI CreatePipe( HANDLE* hReadPipe, HANDLE* hWritePipe, LPSECURITY_ATTRIBUTES lpPipeAttributes, DWORD nSize);

WINDOWS_IMPORT BOOL WINAPI CloseHandle(HANDLE hObject);

WINDOWS_IMPORT HANDLE WINAPI CreateFileW( LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

WINDOWS_IMPORT BOOL WINAPI GetFileSizeEx( HANDLE hFile, PLARGE_INTEGER lpFileSize);

WINDOWS_IMPORT BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
WINDOWS_IMPORT BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);

WINDOWS_IMPORT DWORD_PTR WINAPI SetThreadAffinityMask( HANDLE hThread, DWORD_PTR dwThreadAffinityMask);

WINDOWS_IMPORT BOOL WINAPI GetClientRect( HWND hWnd, LPRECT lpRect);

WINDOWS_IMPORT HBITMAP WINAPI CreateDIBSection( HDC hdc, BITMAPINFO  *pbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset);

WINDOWS_IMPORT HDC WINAPI GetDC(HWND hWnd);

WINDOWS_IMPORT int WINAPI StretchDIBits( HDC hdc, int xDest, int yDest, int DestWidth, int DestHeight, int xSrc, int ySrc, int SrcWidth, int SrcHeight, PVOID lpBits, PBITMAPINFO lpbmi, UINT iUsage, DWORD rop);

WINDOWS_IMPORT BOOL WINAPI DeleteObject(HGDIOBJ ho);

WINDOWS_IMPORT HMONITOR WINAPI MonitorFromWindow(HWND hwnd,DWORD dwFlags);

WINDOWS_IMPORT HMODULE WINAPI LoadLibraryA(LPCSTR lpLibFileName);
WINDOWS_IMPORT void* WINAPI GetProcAddress(HMODULE hModule,LPCSTR  lpProcName);

WINDOWS_IMPORT u32 WINAPI timeBeginPeriod(UINT uPeriod);

WINDOWS_IMPORT BOOL WINAPI SetPriorityClass(HANDLE hProcess,DWORD  dwPriorityClass);

WINDOWS_IMPORT BOOL WINAPI SetThreadPriority(HANDLE hThread,int    nPriority);

WINDOWS_IMPORT HMODULE WINAPI LoadLibraryA(LPCSTR lpLibFileName);

WINDOWS_IMPORT BOOL WINAPI CreateProcessA( LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);

WINDOWS_IMPORT DWORD WINAPI WaitForSingleObject(HANDLE hHandle,DWORD  dwMilliseconds);

WINDOWS_IMPORT BOOL WINAPI GetExitCodeProcess(HANDLE  hProcess,LPDWORD lpExitCode);

typedef enum DXGI_FORMAT {
  DXGI_FORMAT_UNKNOWN = 0,
  DXGI_FORMAT_R32G32B32A32_TYPELESS = 1,
  DXGI_FORMAT_R32G32B32A32_FLOAT = 2,
  DXGI_FORMAT_R32G32B32A32_UINT = 3,
  DXGI_FORMAT_R32G32B32A32_SINT = 4,
  DXGI_FORMAT_R32G32B32_TYPELESS = 5,
  DXGI_FORMAT_R32G32B32_FLOAT = 6,
  DXGI_FORMAT_R32G32B32_UINT = 7,
  DXGI_FORMAT_R32G32B32_SINT = 8,
  DXGI_FORMAT_R16G16B16A16_TYPELESS = 9,
  DXGI_FORMAT_R16G16B16A16_FLOAT = 10,
  DXGI_FORMAT_R16G16B16A16_UNORM = 11,
  DXGI_FORMAT_R16G16B16A16_UINT = 12,
  DXGI_FORMAT_R16G16B16A16_SNORM = 13,
  DXGI_FORMAT_R16G16B16A16_SINT = 14,
  DXGI_FORMAT_R32G32_TYPELESS = 15,
  DXGI_FORMAT_R32G32_FLOAT = 16,
  DXGI_FORMAT_R32G32_UINT = 17,
  DXGI_FORMAT_R32G32_SINT = 18,
  DXGI_FORMAT_R32G8X24_TYPELESS = 19,
  DXGI_FORMAT_D32_FLOAT_S8X24_UINT = 20,
  DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
  DXGI_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
  DXGI_FORMAT_R10G10B10A2_TYPELESS = 23,
  DXGI_FORMAT_R10G10B10A2_UNORM = 24,
  DXGI_FORMAT_R10G10B10A2_UINT = 25,
  DXGI_FORMAT_R11G11B10_FLOAT = 26,
  DXGI_FORMAT_R8G8B8A8_TYPELESS = 27,
  DXGI_FORMAT_R8G8B8A8_UNORM = 28,
  DXGI_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
  DXGI_FORMAT_R8G8B8A8_UINT = 30,
  DXGI_FORMAT_R8G8B8A8_SNORM = 31,
  DXGI_FORMAT_R8G8B8A8_SINT = 32,
  DXGI_FORMAT_R16G16_TYPELESS = 33,
  DXGI_FORMAT_R16G16_FLOAT = 34,
  DXGI_FORMAT_R16G16_UNORM = 35,
  DXGI_FORMAT_R16G16_UINT = 36,
  DXGI_FORMAT_R16G16_SNORM = 37,
  DXGI_FORMAT_R16G16_SINT = 38,
  DXGI_FORMAT_R32_TYPELESS = 39,
  DXGI_FORMAT_D32_FLOAT = 40,
  DXGI_FORMAT_R32_FLOAT = 41,
  DXGI_FORMAT_R32_UINT = 42,
  DXGI_FORMAT_R32_SINT = 43,
  DXGI_FORMAT_R24G8_TYPELESS = 44,
  DXGI_FORMAT_D24_UNORM_S8_UINT = 45,
  DXGI_FORMAT_R24_UNORM_X8_TYPELESS = 46,
  DXGI_FORMAT_X24_TYPELESS_G8_UINT = 47,
  DXGI_FORMAT_R8G8_TYPELESS = 48,
  DXGI_FORMAT_R8G8_UNORM = 49,
  DXGI_FORMAT_R8G8_UINT = 50,
  DXGI_FORMAT_R8G8_SNORM = 51,
  DXGI_FORMAT_R8G8_SINT = 52,
  DXGI_FORMAT_R16_TYPELESS = 53,
  DXGI_FORMAT_R16_FLOAT = 54,
  DXGI_FORMAT_D16_UNORM = 55,
  DXGI_FORMAT_R16_UNORM = 56,
  DXGI_FORMAT_R16_UINT = 57,
  DXGI_FORMAT_R16_SNORM = 58,
  DXGI_FORMAT_R16_SINT = 59,
  DXGI_FORMAT_R8_TYPELESS = 60,
  DXGI_FORMAT_R8_UNORM = 61,
  DXGI_FORMAT_R8_UINT = 62,
  DXGI_FORMAT_R8_SNORM = 63,
  DXGI_FORMAT_R8_SINT = 64,
  DXGI_FORMAT_A8_UNORM = 65,
  DXGI_FORMAT_R1_UNORM = 66,
  DXGI_FORMAT_R9G9B9E5_SHAREDEXP = 67,
  DXGI_FORMAT_R8G8_B8G8_UNORM = 68,
  DXGI_FORMAT_G8R8_G8B8_UNORM = 69,
  DXGI_FORMAT_BC1_TYPELESS = 70,
  DXGI_FORMAT_BC1_UNORM = 71,
  DXGI_FORMAT_BC1_UNORM_SRGB = 72,
  DXGI_FORMAT_BC2_TYPELESS = 73,
  DXGI_FORMAT_BC2_UNORM = 74,
  DXGI_FORMAT_BC2_UNORM_SRGB = 75,
  DXGI_FORMAT_BC3_TYPELESS = 76,
  DXGI_FORMAT_BC3_UNORM = 77,
  DXGI_FORMAT_BC3_UNORM_SRGB = 78,
  DXGI_FORMAT_BC4_TYPELESS = 79,
  DXGI_FORMAT_BC4_UNORM = 80,
  DXGI_FORMAT_BC4_SNORM = 81,
  DXGI_FORMAT_BC5_TYPELESS = 82,
  DXGI_FORMAT_BC5_UNORM = 83,
  DXGI_FORMAT_BC5_SNORM = 84,
  DXGI_FORMAT_B5G6R5_UNORM = 85,
  DXGI_FORMAT_B5G5R5A1_UNORM = 86,
  DXGI_FORMAT_B8G8R8A8_UNORM = 87,
  DXGI_FORMAT_B8G8R8X8_UNORM = 88,
  DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
  DXGI_FORMAT_B8G8R8A8_TYPELESS = 90,
  DXGI_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
  DXGI_FORMAT_B8G8R8X8_TYPELESS = 92,
  DXGI_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
  DXGI_FORMAT_BC6H_TYPELESS = 94,
  DXGI_FORMAT_BC6H_UF16 = 95,
  DXGI_FORMAT_BC6H_SF16 = 96,
  DXGI_FORMAT_BC7_TYPELESS = 97,
  DXGI_FORMAT_BC7_UNORM = 98,
  DXGI_FORMAT_BC7_UNORM_SRGB = 99,
  DXGI_FORMAT_AYUV = 100,
  DXGI_FORMAT_Y410 = 101,
  DXGI_FORMAT_Y416 = 102,
  DXGI_FORMAT_NV12 = 103,
  DXGI_FORMAT_P010 = 104,
  DXGI_FORMAT_P016 = 105,
  DXGI_FORMAT_420_OPAQUE = 106,
  DXGI_FORMAT_YUY2 = 107,
  DXGI_FORMAT_Y210 = 108,
  DXGI_FORMAT_Y216 = 109,
  DXGI_FORMAT_NV11 = 110,
  DXGI_FORMAT_AI44 = 111,
  DXGI_FORMAT_IA44 = 112,
  DXGI_FORMAT_P8 = 113,
  DXGI_FORMAT_A8P8 = 114,
  DXGI_FORMAT_B4G4R4A4_UNORM = 115,
  DXGI_FORMAT_P208 = 130,
  DXGI_FORMAT_V208 = 131,
  DXGI_FORMAT_V408 = 132,
  DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE,
  DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE,
 
} DXGI_FORMAT ;
#define  DXGI_FORMAT_FORCE_UINT 0xffffffff

typedef enum DXGI_MODE_ROTATION { 
  DXGI_MODE_ROTATION_UNSPECIFIED  = 0,
  DXGI_MODE_ROTATION_IDENTITY     = 1,
  DXGI_MODE_ROTATION_ROTATE90     = 2,
  DXGI_MODE_ROTATION_ROTATE180    = 3,
  DXGI_MODE_ROTATION_ROTATE270    = 4
} DXGI_MODE_ROTATION;

typedef struct DXGI_OUTPUT_DESC
    {
    WCHAR DeviceName[ 32 ];
    RECT DesktopCoordinates;
    BOOL AttachedToDesktop;
    DXGI_MODE_ROTATION Rotation;
    HMONITOR Monitor;
    } 	DXGI_OUTPUT_DESC;

typedef struct DXGI_RATIONAL
{
    UINT Numerator;
    UINT Denominator;
} DXGI_RATIONAL;

typedef enum DXGI_MODE_SCANLINE_ORDER { 
  DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED        = 0,
  DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE        = 1,
  DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST  = 2,
  DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST  = 3
} DXGI_MODE_SCANLINE_ORDER;

typedef enum DXGI_MODE_SCALING { 
  DXGI_MODE_SCALING_UNSPECIFIED  = 0,
  DXGI_MODE_SCALING_CENTERED     = 1,
  DXGI_MODE_SCALING_STRETCHED    = 2
} DXGI_MODE_SCALING;
typedef struct DXGI_MODE_DESC
{
    UINT Width;
    UINT Height;
    DXGI_RATIONAL RefreshRate;
    DXGI_FORMAT Format;
    DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
    DXGI_MODE_SCALING Scaling;
} DXGI_MODE_DESC;


typedef struct DXGI_GAMMA_CONTROL_CAPABILITIES
{
    BOOL ScaleAndOffsetSupported;
    float MaxConvertedValue;
    float MinConvertedValue;
    UINT NumGammaControlPoints;
    float ControlPointPositions[1025];
} DXGI_GAMMA_CONTROL_CAPABILITIES;


typedef struct DXGI_RGB {
    float Red;
    float Green;
    float Blue;
} DXGI_RGB;
typedef struct DXGI_GAMMA_CONTROL
{
    DXGI_RGB Scale;
    DXGI_RGB Offset;
    DXGI_RGB GammaCurve[ 1025 ];
} DXGI_GAMMA_CONTROL;

typedef struct DXGI_FRAME_STATISTICS
    {
    UINT PresentCount;
    UINT PresentRefreshCount;
    UINT SyncRefreshCount;
    LARGE_INTEGER SyncQPCTime;
    LARGE_INTEGER SyncGPUTime;
    } 	DXGI_FRAME_STATISTICS;

typedef struct LUID {
    DWORD LowPart;
    LONG HighPart;
} LUID;
typedef struct DXGI_ADAPTER_DESC
    {
    WCHAR Description[ 128 ];
    UINT VendorId;
    UINT DeviceId;
    UINT SubSysId;
    UINT Revision;
    size_t DedicatedVideoMemory;
    size_t DedicatedSystemMemory;
    size_t SharedSystemMemory;
    LUID AdapterLuid;
    } 	DXGI_ADAPTER_DESC;

typedef struct DXGI_SAMPLE_DESC {
  UINT Count;
  UINT Quality;
} DXGI_SAMPLE_DESC;
typedef enum DXGI_SWAP_EFFECT {
  DXGI_SWAP_EFFECT_DISCARD = 0,
  DXGI_SWAP_EFFECT_SEQUENTIAL = 1,
  DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL = 3,
  DXGI_SWAP_EFFECT_FLIP_DISCARD = 4
} DXGI_SWAP_EFFECT;
#define DXGI_CPU_ACCESS_NONE    ( 0 )
#define DXGI_CPU_ACCESS_DYNAMIC    ( 1 )
#define DXGI_CPU_ACCESS_READ_WRITE    ( 2 )
#define DXGI_CPU_ACCESS_SCRATCH    ( 3 )
#define DXGI_CPU_ACCESS_FIELD        15
#define DXGI_USAGE_SHADER_INPUT             ( 1L << (0 + 4) )
#define DXGI_USAGE_RENDER_TARGET_OUTPUT     ( 1L << (1 + 4) )
#define DXGI_USAGE_BACK_BUFFER              ( 1L << (2 + 4) )
#define DXGI_USAGE_SHARED                   ( 1L << (3 + 4) )
#define DXGI_USAGE_READ_ONLY                ( 1L << (4 + 4) )
#define DXGI_USAGE_DISCARD_ON_PRESENT       ( 1L << (5 + 4) )
#define DXGI_USAGE_UNORDERED_ACCESS         ( 1L << (6 + 4) )
typedef UINT DXGI_USAGE;
typedef struct DXGI_SWAP_CHAIN_DESC {
  DXGI_MODE_DESC   BufferDesc;
  DXGI_SAMPLE_DESC SampleDesc;
  DXGI_USAGE       BufferUsage;
  UINT             BufferCount;
  HWND             OutputWindow;
  BOOL             Windowed;
  DXGI_SWAP_EFFECT SwapEffect;
  UINT             Flags;
} DXGI_SWAP_CHAIN_DESC;

typedef struct IUnknownVtbl {
    HRESULT (*QueryInterface)(void *This, const GUID *riid, void **ppvObject);
    ULONG (*AddRef)(void *This);
    ULONG (*Release)(void *This);
} IUnknownVtbl;
typedef struct IDXGIObjectVtbl {
    IUnknownVtbl parent; // Inherits from IUnknown

    HRESULT (*SetPrivateData)(void *This, const GUID *Name, UINT DataSize, const void *pData);
    HRESULT (*SetPrivateDataInterface)(void *This, const GUID *Name, const void *pUnknown);
    HRESULT (*GetPrivateData)(void *This, const GUID *Name, UINT *pDataSize, void *pData);
    HRESULT (*GetParent)(void *This, const GUID *riid, void **ppParent);
} IDXGIObjectVtbl;

typedef struct IDXGIObject {
    const IDXGIObjectVtbl *lpVtbl;
} IDXGIObject;


typedef struct IDXGIOutputVtbl {
    IUnknownVtbl parent; // Inherits from IUnknown

    HRESULT (*SetPrivateData)(void *This, const GUID *Name, UINT DataSize, const void *pData);
    HRESULT (*SetPrivateDataInterface)(void *This, const GUID *Name, const void *pUnknown);
    HRESULT (*GetPrivateData)(void *This, const GUID *Name, UINT *pDataSize, void *pData);
    HRESULT (*GetParent)(void *This, const GUID *riid, void **ppParent);

    HRESULT (*GetDesc)(void *This, DXGI_OUTPUT_DESC *pDesc);
    HRESULT (*GetDisplayModeList)(void *This, DXGI_FORMAT EnumFormat, UINT Flags, UINT *pNumModes, DXGI_MODE_DESC *pDesc);
    HRESULT (*FindClosestMatchingMode)(void *This, const DXGI_MODE_DESC *pModeToMatch, DXGI_MODE_DESC *pClosestMatch, void *pConcernedDevice);
    HRESULT (*WaitForVBlank)(void *This);
    HRESULT (*TakeOwnership)(void *This, void *pDevice, BOOL Exclusive);
    void (*ReleaseOwnership)(void *This);
    HRESULT (*GetGammaControlCapabilities)(void *This, DXGI_GAMMA_CONTROL_CAPABILITIES *pGammaCaps);
    HRESULT (*SetGammaControl)(void *This, const DXGI_GAMMA_CONTROL *pArray);
    HRESULT (*GetGammaControl)(void *This, DXGI_GAMMA_CONTROL *pArray);
    HRESULT (*SetDisplaySurface)(void *This, void *pScanoutSurface);
    HRESULT (*GetDisplaySurfaceData)(void *This, void *pDestination);
    HRESULT (*GetFrameStatistics)(void *This, DXGI_FRAME_STATISTICS *pStats);
} IDXGIOutputVtbl;

typedef struct IDXGIOutput {
    const IDXGIOutputVtbl *lpVtbl;
} IDXGIOutput;

typedef struct IDXGIAdapterVtbl {
    IUnknownVtbl parent; // Inherits from IUnknown

    HRESULT (*SetPrivateData)(void *This, const GUID *Name, UINT DataSize, const void *pData);
    HRESULT (*SetPrivateDataInterface)(void *This, const GUID *Name, const void *pUnknown);
    HRESULT (*GetPrivateData)(void *This, const GUID *Name, UINT *pDataSize, void *pData);
    HRESULT (*GetParent)(void *This, const GUID *riid, void **ppParent);

    HRESULT (*EnumOutputs)(void *This, UINT Output, IDXGIOutput **ppOutput);
    HRESULT (*GetDesc)(void *This, DXGI_ADAPTER_DESC *pDesc);
    HRESULT (*CheckInterfaceSupport)(void *This, const GUID *InterfaceName, LARGE_INTEGER *pUMDVersion);
} IDXGIAdapterVtbl;

typedef struct IDXGIAdapter {
    const IDXGIAdapterVtbl *lpVtbl;
} IDXGIAdapter;

struct IDXGISwapChain;
typedef struct IDXGIFactoryVtbl {
    IUnknownVtbl parent; // Inherits from IUnknown

    HRESULT (*SetPrivateData)(void *This, const GUID *Name, UINT DataSize, const void *pData);
    HRESULT (*SetPrivateDataInterface)(void *This, const GUID *Name, const void *pUnknown);
    HRESULT (*GetPrivateData)(void *This, const GUID *Name, UINT *pDataSize, void *pData);
    HRESULT (*GetParent)(void *This, const GUID *riid, void **ppParent);

    HRESULT (*EnumAdapters)(void *This, UINT Adapter, IDXGIAdapter **ppAdapter);
    HRESULT (*MakeWindowAssociation)(void *This, HWND WindowHandle, UINT Flags);
    HRESULT (*GetWindowAssociation)(void *This, HWND *pWindowHandle);
    HRESULT (*CreateSwapChain)(void *This, void *pDevice, const DXGI_SWAP_CHAIN_DESC *pDesc, struct IDXGISwapChain **ppSwapChain);
    HRESULT (*CreateSoftwareAdapter)(void *This, HMODULE Module, IDXGIAdapter **ppAdapter);
} IDXGIFactoryVtbl;

typedef struct IDXGIFactory {
    const IDXGIFactoryVtbl *lpVtbl;
} IDXGIFactory;

typedef GUID IID;
extern const IID IID_IDXGIFactory;
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    const GUID name = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }
DEFINE_GUID(IID_IDXGIFactory,0x7b7166ec,0x21c7,0x44ae,0xb2,0x1a,0xc9,0xae,0x32,0x1a,0xe3,0x69);
unit_local const HRESULT DXGI_ERROR_NOT_FOUND = 0x887A0002;


WINDOWS_IMPORT HRESULT WINAPI CreateDXGIFactory(const GUID *riid, void **ppFactory);







#define WSABASEERR 10000
#define WSAEINTR                         10004L
#define WSAEBADF                         10009L
#define WSAEACCES                        10013L
#define WSAEFAULT                        10014L
#define WSAEINVAL                        10022L
#define WSAEMFILE                        10024L
#define WSAEWOULDBLOCK                   10035L
#define WSAEINPROGRESS                   10036L
#define WSAEALREADY                      10037L
#define WSAENOTSOCK                      10038L
#define WSAEDESTADDRREQ                  10039L
#define WSAEMSGSIZE                      10040L
#define WSAEPROTOTYPE                    10041L
#define WSAENOPROTOOPT                   10042L
#define WSAEPROTONOSUPPORT               10043L
#define WSAESOCKTNOSUPPORT               10044L
#define WSAEOPNOTSUPP                    10045L
#define WSAEPFNOSUPPORT                  10046L
#define WSAEAFNOSUPPORT                  10047L
#define WSAEADDRINUSE                    10048L
#define WSAEADDRNOTAVAIL                 10049L
#define WSAENETDOWN                      10050L
#define WSAENETUNREACH                   10051L
#define WSAENETRESET                     10052L
#define WSAECONNABORTED                  10053L
#define WSAECONNRESET                    10054L
#define WSAENOBUFS                       10055L
#define WSAEISCONN                       10056L
#define WSAENOTCONN                      10057L
#define WSAESHUTDOWN                     10058L
#define WSAETOOMANYREFS                  10059L
#define WSAETIMEDOUT                     10060L
#define WSAECONNREFUSED                  10061L
#define WSAELOOP                         10062L
#define WSAENAMETOOLONG                  10063L
#define WSAEHOSTDOWN                     10064L
#define WSAEHOSTUNREACH                  10065L
#define WSAENOTEMPTY                     10066L
#define WSAEPROCLIM                      10067L
#define WSAEUSERS                        10068L
#define WSAEDQUOT                        10069L
#define WSAESTALE                        10070L
#define WSAEREMOTE                       10071L
#define WSASYSNOTREADY                   10091L
#define WSAVERNOTSUPPORTED               10092L
#define WSANOTINITIALISED                10093L
#define WSAEDISCON                       10101L
#define WSAENOMORE                       10102L
#define WSAECANCELLED                    10103L
#define WSAEINVALIDPROCTABLE             10104L
#define WSAEINVALIDPROVIDER              10105L
#define WSAEPROVIDERFAILEDINIT           10106L
#define WSASYSCALLFAILURE                10107L
#define WSASERVICE_NOT_FOUND             10108L
#define WSATYPE_NOT_FOUND                10109L
#define WSA_E_NO_MORE                    10110L
#define WSA_E_CANCELLED                  10111L
#define WSAEREFUSED                      10112L
#define WSAHOST_NOT_FOUND                11001L
#define WSATRY_AGAIN                     11002L
#define WSANO_RECOVERY                   11003L
#define WSANO_DATA                       11004L
#define WSA_QOS_RECEIVERS                11005L
#define WSA_QOS_SENDERS                  11006L
#define WSA_QOS_NO_SENDERS               11007L
#define WSA_QOS_NO_RECEIVERS             11008L
#define WSA_QOS_REQUEST_CONFIRMED        11009L
#define WSA_QOS_ADMISSION_FAILURE        11010L
#define WSA_QOS_POLICY_FAILURE           11011L
#define WSA_QOS_BAD_STYLE                11012L
#define WSA_QOS_BAD_OBJECT               11013L
#define WSA_QOS_TRAFFIC_CTRL_ERROR       11014L
#define WSA_QOS_GENERIC_ERROR            11015L
#define WSA_QOS_ESERVICETYPE             11016L
#define WSA_QOS_EFLOWSPEC                11017L
#define WSA_QOS_EPROVSPECBUF             11018L
#define WSA_QOS_EFILTERSTYLE             11019L
#define WSA_QOS_EFILTERTYPE              11020L
#define WSA_QOS_EFILTERCOUNT             11021L
#define WSA_QOS_EOBJLENGTH               11022L
#define WSA_QOS_EFLOWCOUNT               11023L
#define WSA_QOS_EUNKOWNPSOBJ             11024L
#define WSA_QOS_EPOLICYOBJ               11025L
#define WSA_QOS_EFLOWDESC                11026L
#define WSA_QOS_EPSFLOWSPEC              11027L
#define WSA_QOS_EPSFILTERSPEC            11028L
#define WSA_QOS_ESDMODEOBJ               11029L
#define WSA_QOS_ESHAPERATEOBJ            11030L
#define WSA_QOS_RESERVED_PETYPE          11031L
#define WSA_SECURE_HOST_NOT_FOUND        11032L
#define WSA_IPSEC_NAME_POLICY_ERROR      11033L

#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128

typedef UINT_PTR        SOCKET;

typedef struct WSAData {
        WORD                    wVersion;
        WORD                    wHighVersion;
#ifdef _WIN64
        unsigned short          iMaxSockets;
        unsigned short          iMaxUdpDg;
        char *              lpVendorInfo;
        char                    szDescription[WSADESCRIPTION_LEN+1];
        char                    szSystemStatus[WSASYS_STATUS_LEN+1];
#else
        char                    szDescription[WSADESCRIPTION_LEN+1];
        char                    szSystemStatus[WSASYS_STATUS_LEN+1];
        unsigned short          iMaxSockets;
        unsigned short          iMaxUdpDg;
        char *              lpVendorInfo;
#endif
} WSADATA;

typedef WSADATA *LPWSADATA;

WINDOWS_IMPORT int WINAPI WSAStartup( WORD      wVersionRequired, LPWSADATA lpWSAData);

/*
 * Address families.
 */
#define AF_UNSPEC       0               /* unspecified */
#define AF_UNIX         1               /* local to host (pipes, portals) */
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#define AF_IMPLINK      3               /* arpanet imp addresses */
#define AF_PUP          4               /* pup protocols: e.g. BSP */
#define AF_CHAOS        5               /* mit CHAOS protocols */
#define AF_IPX          6               /* IPX and SPX */
#define AF_NS           6               /* XEROX NS protocols */
#define AF_ISO          7               /* ISO protocols */
#define AF_OSI          AF_ISO          /* OSI is ISO */
#define AF_ECMA         8               /* european computer manufacturers */
#define AF_DATAKIT      9               /* datakit protocols */
#define AF_CCITT        10              /* CCITT protocols, X.25 etc */
#define AF_SNA          11              /* IBM SNA */
#define AF_DECnet       12              /* DECnet */
#define AF_DLI          13              /* Direct data link interface */
#define AF_LAT          14              /* LAT */
#define AF_HYLINK       15              /* NSC Hyperchannel */
#define AF_APPLETALK    16              /* AppleTalk */
#define AF_NETBIOS      17              /* NetBios-style addresses */
#define AF_VOICEVIEW    18              /* VoiceView */
#define AF_FIREFOX      19              /* FireFox */
#define AF_UNKNOWN1     20              /* Somebody is using this! */
#define AF_BAN          21              /* Banyan */

#define AF_MAX          22

/*
 * Types
 */
#define SOCK_STREAM     1               /* stream socket */
#define SOCK_DGRAM      2               /* datagram socket */
#define SOCK_RAW        3               /* raw-protocol interface */
#define SOCK_RDM        4               /* reliably-delivered message */
#define SOCK_SEQPACKET  5               /* sequenced packet stream */


#define IPPROTO_IP              0               /* dummy for IP */
#define IPPROTO_ICMP            1               /* control message protocol */
#define IPPROTO_IGMP            2               /* group management protocol */
#define IPPROTO_GGP             3               /* gateway^2 (deprecated) */
#define IPPROTO_TCP             6               /* tcp */
#define IPPROTO_PUP             12              /* pup */
#define IPPROTO_UDP             17              /* user datagram protocol */
#define IPPROTO_IDP             22              /* xns idp */
#define IPPROTO_ND              77              /* UNOFFICIAL net disk proto */

#define IPPROTO_RAW             255             /* raw IP packet */
#define IPPROTO_MAX             256





           
typedef struct in_addr {
        union {
                struct { UCHAR s_b1,s_b2,s_b3,s_b4; } S_un_b;
                struct { USHORT s_w1,s_w2; } S_un_w;
                ULONG S_addr;
        } S_un;
#define s_addr  S_un.S_addr /* can be used for most tcp & ip code */
#define s_host  S_un.S_un_b.s_b2    // host on imp
#define s_net   S_un.S_un_b.s_b1    // network
#define s_imp   S_un.S_un_w.s_w2    // imp
#define s_impno S_un.S_un_b.s_b4    // imp #
#define s_lh    S_un.S_un_b.s_b3    // logical host
} IN_ADDR, *PIN_ADDR,  *LPIN_ADDR;

    
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)
    
  typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in *PSOCKADDR_IN;
typedef struct sockaddr_in *LPSOCKADDR_IN;

typedef USHORT ADDRESS_FAMILY;

typedef struct sockaddr_in {

#if(_WIN32_WINNT < 0x0600)
    short   sin_family;
#else //(_WIN32_WINNT < 0x0600)
    ADDRESS_FAMILY sin_family;
#endif //(_WIN32_WINNT < 0x0600)

    USHORT sin_port;
    IN_ADDR sin_addr;
    CHAR sin_zero[8];
} SOCKADDR_IN, *PSOCKADDR_IN;

struct sockaddr {
        USHORT sa_family;              /* address family */
        char    sa_data[14];            /* up to 14 bytes of direct address */
};


WINDOWS_IMPORT
SOCKET
WINAPI
socket(
    int af,
    int type,
    int protocol
    );
    
WINDOWS_IMPORT
USHORT
WINAPI
htons(
    USHORT hostshort
    );
WINDOWS_IMPORT
USHORT
WINAPI
htonl(
   USHORT hostlong
    );
        
WINDOWS_IMPORT
int
WINAPI
bind(
     SOCKET s,
    const struct sockaddr * name,
     int namelen
    );
    
WINDOWS_IMPORT
int
WINAPI
WSAGetLastError(
    void
    );    

WINDOWS_IMPORT
int
WINAPI
listen(
     SOCKET s,
     int backlog
    );

WINDOWS_IMPORT
SOCKET
WINAPI
accept(
    SOCKET s,
    struct sockaddr * addr,
    int * addrlen
    );
    

WINDOWS_IMPORT
unsigned long
WINAPI
inet_addr(
     const char * cp
    );
    
#define INADDR_NONE             0xffffffff


WINDOWS_IMPORT
int
WINAPI
connect(
    SOCKET s,
    const struct sockaddr * name,
    int namelen
    );


WINDOWS_IMPORT
int
WINAPI
send(
    SOCKET s,
    const char * buf,
    int len,
    int flags
    );
    
WINDOWS_IMPORT
int
WINAPI
recv(
    SOCKET s,
    char * buf,
    int len,
    int flags
    );



WINDOWS_IMPORT
int
WINAPI
closesocket(
    SOCKET s
    );

WINDOWS_IMPORT
int
WINAPI
ioctlsocket(
     SOCKET s,
     long cmd,
    unsigned long * argp
    );
    

#define IOCPARM_MASK    0x7f            /* parameters must be < 128 bytes */
#define IOC_VOID        0x20000000      /* no parameters */
#define IOC_OUT         0x40000000      /* copy out parameters */
#define IOC_IN          0x80000000      /* copy in parameters */
#define IOC_INOUT       (IOC_IN|IOC_OUT)
#define _IO(x,y)        (IOC_VOID|((x)<<8)|(y))

#define _IOR(x,y,t)     (IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define _IOW(x,y,t)     (IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))
#define FIONREAD    _IOR('f', 127, unsigned long) /* get # bytes to read */
#define FIONBIO     _IOW('f', 126, unsigned long) /* set/clear non-blocking i/o */
#define FIOASYNC    _IOW('f', 125, unsigned long) /* set/clear async i/o */

#define NO_ERROR 0L                                                 // dderror

int setsockopt (
                           SOCKET s,
                           int level,
                           int optname,
                           const char * optval,
                           int optlen);
                           
#define SOL_SOCKET      0xffff          /* options for socket level */

#define SO_SNDBUF       0x1001          /* send buffer size */
#define SO_RCVBUF       0x1002          /* receive buffer size */
#define SO_SNDLOWAT     0x1003          /* send low-water mark */
#define SO_RCVLOWAT     0x1004          /* receive low-water mark */
#define SO_SNDTIMEO     0x1005          /* send timeout */
#define SO_RCVTIMEO     0x1006          /* receive timeout */
#define SO_ERROR        0x1007          /* get error status and clear */
#define SO_TYPE         0x1008          /* get socket type */

#define FD_SETSIZE      64

#define FD_CLR(fd, set) do { \
    u_int __i; \
    for (__i = 0; __i < ((fd_set *)(set))->fd_count ; __i++) { \
        if (((fd_set *)(set))->fd_array[__i] == fd) { \
            while (__i < ((fd_set *)(set))->fd_count-1) { \
                ((fd_set *)(set))->fd_array[__i] = \
                    ((fd_set *)(set))->fd_array[__i+1]; \
                __i++; \
            } \
            ((fd_set *)(set))->fd_count--; \
            break; \
        } \
    } \
} while(0)

#define FD_SET(fd, set) do { \
    if (((fd_set *)(set))->fd_count < FD_SETSIZE) \
        ((fd_set *)(set))->fd_array[((fd_set *)(set))->fd_count++]=(fd);\
} while(0)

#define FD_ZERO(set) (((fd_set *)(set))->fd_count=0)

#define FD_ISSET(fd, set) __WSAFDIsSet((SOCKET)(fd), (fd_set *)(set))

/*
 * Structure used in select() call, taken from the BSD file sys/time.h.
 */
struct timeval {
        long    tv_sec;         /* seconds */
        long    tv_usec;        /* and microseconds */
};

/*
 * Operations on timevals.
 *
 * NB: timercmp does not work for >= or <=.
 */
#define timerisset(tvp)         ((tvp)->tv_sec || (tvp)->tv_usec)
#define timercmp(tvp, uvp, cmp) \
        ((tvp)->tv_sec cmp (uvp)->tv_sec || \
         (tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp (uvp)->tv_usec)
#define timerclear(tvp)         (tvp)->tv_sec = (tvp)->tv_usec = 0

typedef struct fd_set {
        unsigned int   fd_count;               /* how many are SET? */
        SOCKET  fd_array[FD_SETSIZE];   /* an array of SOCKETs */
} fd_set;

WINDOWS_IMPORT
int
WINAPI
select(
    int nfds,
    fd_set * readfds,
    fd_set * writefds,
    fd_set * exceptfds,
    const struct timeval * timeout
    );
    
#endif // _WINDOWS_LOADER_H

typedef struct _FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

WINDOWS_IMPORT BOOL WINAPI FindClose(
  HANDLE hFindFile
);

typedef struct _WIN32_FIND_DATAW {
  DWORD    dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD    nFileSizeHigh;
  DWORD    nFileSizeLow;
  DWORD    dwReserved0;
  DWORD    dwReserved1;
  WCHAR    cFileName[260];
  WCHAR    cAlternateFileName[14];
  DWORD    dwFileType; // Obsolete. Do not use.
  DWORD    dwCreatorType; // Obsolete. Do not use
  WORD     wFinderFlags; // Obsolete. Do not use
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;

WINDOWS_IMPORT HANDLE WINAPI FindFirstFileW(
  LPCWSTR            lpFileName,
  LPWIN32_FIND_DATAW lpFindFileData
);

WINDOWS_IMPORT BOOL WINAPI FindNextFileW(
  HANDLE             hFindFile,
  LPWIN32_FIND_DATAW lpFindFileData
);

WINDOWS_IMPORT DWORD WINAPI GetFileAttributesW(
  LPCWSTR lpFileName
);

WINDOWS_IMPORT BOOL WINAPI RemoveDirectoryW(
  LPCWSTR lpPathName
);

WINDOWS_IMPORT BOOL WINAPI DeleteFileW(
  LPCWSTR lpFileName
);

// end_access
#define FILE_SHARE_READ                 0x00000001  
#define FILE_SHARE_WRITE                0x00000002  
#define FILE_SHARE_DELETE               0x00000004  
#define FILE_ATTRIBUTE_READONLY             0x00000001  
#define FILE_ATTRIBUTE_HIDDEN               0x00000002  
#define FILE_ATTRIBUTE_SYSTEM               0x00000004  
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020  
#define FILE_ATTRIBUTE_DEVICE               0x00000040  
#define FILE_ATTRIBUTE_NORMAL               0x00000080  
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100  
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200  
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400  
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800  
#define FILE_ATTRIBUTE_OFFLINE              0x00001000  
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000  
#define FILE_ATTRIBUTE_ENCRYPTED            0x00004000  
#define FILE_ATTRIBUTE_INTEGRITY_STREAM     0x00008000  
#define FILE_ATTRIBUTE_VIRTUAL              0x00010000  
#define FILE_ATTRIBUTE_NO_SCRUB_DATA        0x00020000  
#define FILE_ATTRIBUTE_EA                   0x00040000  
#define FILE_ATTRIBUTE_PINNED               0x00080000  
#define FILE_ATTRIBUTE_UNPINNED             0x00100000  
#define FILE_ATTRIBUTE_RECALL_ON_OPEN       0x00040000  
#define FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS 0x00400000 
#define TREE_CONNECT_ATTRIBUTE_PRIVACY      0x00004000  
#define TREE_CONNECT_ATTRIBUTE_INTEGRITY    0x00008000  
#define TREE_CONNECT_ATTRIBUTE_GLOBAL       0x00000004  
#define TREE_CONNECT_ATTRIBUTE_PINNED       0x00000002  
#define FILE_ATTRIBUTE_STRICTLY_SEQUENTIAL  0x20000000  
#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001   
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002   
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004   
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008   
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010   
#define FILE_NOTIFY_CHANGE_LAST_ACCESS  0x00000020   
#define FILE_NOTIFY_CHANGE_CREATION     0x00000040   
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100   
#define FILE_ACTION_ADDED                   0x00000001   
#define FILE_ACTION_REMOVED                 0x00000002   
#define FILE_ACTION_MODIFIED                0x00000003   
#define FILE_ACTION_RENAMED_OLD_NAME        0x00000004   
#define FILE_ACTION_RENAMED_NEW_NAME        0x00000005   
#define MAILSLOT_NO_MESSAGE             ((DWORD)-1) 
#define MAILSLOT_WAIT_FOREVER           ((DWORD)-1) 
#define FILE_CASE_SENSITIVE_SEARCH          0x00000001  
#define FILE_CASE_PRESERVED_NAMES           0x00000002  
#define FILE_UNICODE_ON_DISK                0x00000004  
#define FILE_PERSISTENT_ACLS                0x00000008  
#define FILE_FILE_COMPRESSION               0x00000010  
#define FILE_VOLUME_QUOTAS                  0x00000020  
#define FILE_SUPPORTS_SPARSE_FILES          0x00000040  
#define FILE_SUPPORTS_REPARSE_POINTS        0x00000080  
#define FILE_SUPPORTS_REMOTE_STORAGE        0x00000100  
#define FILE_RETURNS_CLEANUP_RESULT_INFO    0x00000200  
#define FILE_SUPPORTS_POSIX_UNLINK_RENAME   0x00000400  




#define FILE_VOLUME_IS_COMPRESSED           0x00008000  
#define FILE_SUPPORTS_OBJECT_IDS            0x00010000  
#define FILE_SUPPORTS_ENCRYPTION            0x00020000  
#define FILE_NAMED_STREAMS                  0x00040000  
#define FILE_READ_ONLY_VOLUME               0x00080000  
#define FILE_SEQUENTIAL_WRITE_ONCE          0x00100000  
#define FILE_SUPPORTS_TRANSACTIONS          0x00200000  
#define FILE_SUPPORTS_HARD_LINKS            0x00400000  
#define FILE_SUPPORTS_EXTENDED_ATTRIBUTES   0x00800000  
#define FILE_SUPPORTS_OPEN_BY_FILE_ID       0x01000000  
#define FILE_SUPPORTS_USN_JOURNAL           0x02000000  
#define FILE_SUPPORTS_INTEGRITY_STREAMS     0x04000000  
#define FILE_SUPPORTS_BLOCK_REFCOUNTING     0x08000000  
#define FILE_SUPPORTS_SPARSE_VDL            0x10000000  
#define FILE_DAX_VOLUME                     0x20000000  
#define FILE_SUPPORTS_GHOSTING              0x40000000  


WINDOWS_IMPORT DWORD WINAPI TlsAlloc(void);
WINDOWS_IMPORT LPVOID WINAPI TlsGetValue(
  DWORD dwTlsIndex
);
WINDOWS_IMPORT BOOL WINAPI TlsSetValue(
  DWORD  dwTlsIndex,
  LPVOID lpTlsValue
);

WINDOWS_IMPORT DWORD WINAPI GetCurrentThreadId(void);

typedef DWORD (__stdcall *LPTHREAD_START_ROUTINE) (LPVOID lpThreadParameter);  

WINDOWS_IMPORT HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, size_t dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);

WINDOWS_IMPORT DWORD WINAPI ResumeThread(HANDLE hThread);

typedef struct CRITICAL_SECTION {
  u8 _[40]; // todo(charlie) #portability 32-bit
} CRITICAL_SECTION, *LPCRITICAL_SECTION, *PCRITICAL_SECTION;

WINDOWS_IMPORT void WINAPI InitializeCriticalSection(
  LPCRITICAL_SECTION lpCriticalSection
);

WINDOWS_IMPORT void WINAPI EnterCriticalSection(
  LPCRITICAL_SECTION lpCriticalSection
);

WINDOWS_IMPORT void WINAPI LeaveCriticalSection(
  LPCRITICAL_SECTION lpCriticalSection
);

WINDOWS_IMPORT void WINAPI DeleteCriticalSection(
  LPCRITICAL_SECTION lpCriticalSection
);

WINDOWS_IMPORT BOOL WINAPI CreateDirectoryW(
  LPCWSTR               lpPathName,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes
);


#define SO_DEBUG        0x0001          /* turn on debugging info recording */
#define SO_ACCEPTCONN   0x0002          /* socket has had listen() */
#define SO_REUSEADDR    0x0004          /* allow local address reuse */
#define SO_KEEPALIVE    0x0008          /* keep connections alive */
#define SO_DONTROUTE    0x0010          /* just use interface addresses */
#define SO_BROADCAST    0x0020          /* permit sending of broadcast msgs */
#define SO_USELOOPBACK  0x0040          /* bypass hardware when possible */
#define SO_LINGER       0x0080          /* linger on close if data present */
#define SO_OOBINLINE    0x0100          /* leave received OOB data in line */

WINDOWS_IMPORT void WINAPI ExitProcess(UINT uExitCode);

WINDOWS_IMPORT void WINAPI ExitThread(DWORD dwExitCode);

WINDOWS_IMPORT BOOL WINAPI GetExitCodeThread(HANDLE hThread, LPDWORD lpExitCode);

WINDOWS_IMPORT DWORD WINAPI GetFullPathNameA( LPCSTR lpFileName, DWORD  nBufferLength, LPSTR  lpBuffer, LPSTR  *lpFilePart);

WINDOWS_IMPORT LPWSTR  WINAPI GetCommandLineW(void);
WINDOWS_IMPORT LPCSTR  WINAPI GetCommandLineA(void);
WINDOWS_IMPORT LPWSTR* WINAPI CommandLineToArgvW(LPCWSTR, int*);

WINDOWS_IMPORT HANDLE WINAPI CreateSemaphoreA( LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCSTR lpName);

WINDOWS_IMPORT BOOL WINAPI ReleaseSemaphore( HANDLE hSemaphore, LONG   lReleaseCount, LPLONG lpPreviousCount);

typedef struct {
  LARGE_INTEGER VolumeSerialNumber;
  LARGE_INTEGER NumberSectors;
  LARGE_INTEGER TotalClusters;
  LARGE_INTEGER FreeClusters;
  LARGE_INTEGER TotalReserved;
  ULONG         BytesPerSector;
  ULONG         BytesPerCluster;
  ULONG         BytesPerFileRecordSegment;
  ULONG         ClustersPerFileRecordSegment;
  LARGE_INTEGER MftValidDataLength;
  LARGE_INTEGER MftStartLcn;
  LARGE_INTEGER Mft2StartLcn;
  LARGE_INTEGER MftZoneStart;
  LARGE_INTEGER MftZoneEnd;
} NTFS_VOLUME_DATA_BUFFER, *PNTFS_VOLUME_DATA_BUFFER;

WINDOWS_IMPORT BOOL WINAPI DeviceIoControl( HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);

typedef struct {
  DWORDLONG StartFileReferenceNumber;
  USN       LowUsn;
  USN       HighUsn;
} MFT_ENUM_DATA_V0, *PMFT_ENUM_DATA_V0;

#define DEVICE_TYPE DWORD

#define FILE_DEVICE_BEEP                0x00000001
#define FILE_DEVICE_CD_ROM              0x00000002
#define FILE_DEVICE_CD_ROM_FILE_SYSTEM  0x00000003
#define FILE_DEVICE_CONTROLLER          0x00000004
#define FILE_DEVICE_DATALINK            0x00000005
#define FILE_DEVICE_DFS                 0x00000006
#define FILE_DEVICE_DISK                0x00000007
#define FILE_DEVICE_DISK_FILE_SYSTEM    0x00000008
#define FILE_DEVICE_FILE_SYSTEM         0x00000009
#define FILE_DEVICE_INPORT_PORT         0x0000000a
#define FILE_DEVICE_KEYBOARD            0x0000000b
#define FILE_DEVICE_MAILSLOT            0x0000000c
#define FILE_DEVICE_MIDI_IN             0x0000000d
#define FILE_DEVICE_MIDI_OUT            0x0000000e
#define FILE_DEVICE_MOUSE               0x0000000f
#define FILE_DEVICE_MULTI_UNC_PROVIDER  0x00000010
#define FILE_DEVICE_NAMED_PIPE          0x00000011
#define FILE_DEVICE_NETWORK             0x00000012
#define FILE_DEVICE_NETWORK_BROWSER     0x00000013
#define FILE_DEVICE_NETWORK_FILE_SYSTEM 0x00000014
#define FILE_DEVICE_NULL                0x00000015
#define FILE_DEVICE_PARALLEL_PORT       0x00000016
#define FILE_DEVICE_PHYSICAL_NETCARD    0x00000017
#define FILE_DEVICE_PRINTER             0x00000018
#define FILE_DEVICE_SCANNER             0x00000019
#define FILE_DEVICE_SERIAL_MOUSE_PORT   0x0000001a
#define FILE_DEVICE_SERIAL_PORT         0x0000001b
#define FILE_DEVICE_SCREEN              0x0000001c
#define FILE_DEVICE_SOUND               0x0000001d
#define FILE_DEVICE_STREAMS             0x0000001e
#define FILE_DEVICE_TAPE                0x0000001f
#define FILE_DEVICE_TAPE_FILE_SYSTEM    0x00000020
#define FILE_DEVICE_TRANSPORT           0x00000021
#define FILE_DEVICE_UNKNOWN             0x00000022
#define FILE_DEVICE_VIDEO               0x00000023
#define FILE_DEVICE_VIRTUAL_DISK        0x00000024
#define FILE_DEVICE_WAVE_IN             0x00000025
#define FILE_DEVICE_WAVE_OUT            0x00000026
#define FILE_DEVICE_8042_PORT           0x00000027
#define FILE_DEVICE_NETWORK_REDIRECTOR  0x00000028
#define FILE_DEVICE_BATTERY             0x00000029
#define FILE_DEVICE_BUS_EXTENDER        0x0000002a
#define FILE_DEVICE_MODEM               0x0000002b
#define FILE_DEVICE_VDM                 0x0000002c
#define FILE_DEVICE_MASS_STORAGE        0x0000002d
#define FILE_DEVICE_SMB                 0x0000002e
#define FILE_DEVICE_KS                  0x0000002f
#define FILE_DEVICE_CHANGER             0x00000030
#define FILE_DEVICE_SMARTCARD           0x00000031
#define FILE_DEVICE_ACPI                0x00000032
#define FILE_DEVICE_DVD                 0x00000033
#define FILE_DEVICE_FULLSCREEN_VIDEO    0x00000034
#define FILE_DEVICE_DFS_FILE_SYSTEM     0x00000035
#define FILE_DEVICE_DFS_VOLUME          0x00000036
#define FILE_DEVICE_SERENUM             0x00000037
#define FILE_DEVICE_TERMSRV             0x00000038
#define FILE_DEVICE_KSEC                0x00000039
#define FILE_DEVICE_FIPS                0x0000003A
#define FILE_DEVICE_INFINIBAND          0x0000003B
#define FILE_DEVICE_VMBUS               0x0000003E
#define FILE_DEVICE_CRYPT_PROVIDER      0x0000003F
#define FILE_DEVICE_WPD                 0x00000040
#define FILE_DEVICE_BLUETOOTH           0x00000041
#define FILE_DEVICE_MT_COMPOSITE        0x00000042
#define FILE_DEVICE_MT_TRANSPORT        0x00000043
#define FILE_DEVICE_BIOMETRIC           0x00000044
#define FILE_DEVICE_PMI                 0x00000045
#define FILE_DEVICE_EHSTOR              0x00000046
#define FILE_DEVICE_DEVAPI              0x00000047
#define FILE_DEVICE_GPIO                0x00000048
#define FILE_DEVICE_USBEX               0x00000049
#define FILE_DEVICE_CONSOLE             0x00000050
#define FILE_DEVICE_NFP                 0x00000051
#define FILE_DEVICE_SYSENV              0x00000052
#define FILE_DEVICE_VIRTUAL_BLOCK       0x00000053
#define FILE_DEVICE_POINT_OF_SERVICE    0x00000054
#define FILE_DEVICE_STORAGE_REPLICATION 0x00000055
#define FILE_DEVICE_TRUST_ENV           0x00000056
#define FILE_DEVICE_UCM                 0x00000057
#define FILE_DEVICE_UCMTCPCI            0x00000058
#define FILE_DEVICE_PERSISTENT_MEMORY   0x00000059
#define FILE_DEVICE_NVDIMM              0x0000005a
#define FILE_DEVICE_HOLOGRAPHIC         0x0000005b
#define FILE_DEVICE_SDFXHCI             0x0000005c
#define FILE_DEVICE_UCMUCSI             0x0000005d

#define DEVICE_TYPE_FROM_CTL_CODE(ctrlCode)     (((DWORD)(ctrlCode & 0xffff0000)) >> 16)

//
// Macro to extract buffering method out of the device io control code
//
#define METHOD_FROM_CTL_CODE(ctrlCode)          ((DWORD)(ctrlCode & 3))

//
// Define the method codes for how buffers are passed for I/O and FS controls
//

#define METHOD_BUFFERED                 0
#define METHOD_IN_DIRECT                1
#define METHOD_OUT_DIRECT               2
#define METHOD_NEITHER                  3

//
// Define some easier to comprehend aliases:
//   METHOD_DIRECT_TO_HARDWARE (writes, aka METHOD_IN_DIRECT)
//   METHOD_DIRECT_FROM_HARDWARE (reads, aka METHOD_OUT_DIRECT)
//

#define METHOD_DIRECT_TO_HARDWARE       METHOD_IN_DIRECT
#define METHOD_DIRECT_FROM_HARDWARE     METHOD_OUT_DIRECT

#define FILE_ANY_ACCESS                 0
#define FILE_SPECIAL_ACCESS    (FILE_ANY_ACCESS)
#define FILE_READ_ACCESS          ( 0x0001 )    // file & pipe
#define FILE_WRITE_ACCESS         ( 0x0002 )    // file & pipe

//
// _WIN32_WINNT version constants
//
#define _WIN32_WINNT_NT4                    0x0400
#define _WIN32_WINNT_WIN2K                  0x0500
#define _WIN32_WINNT_WINXP                  0x0501
#define _WIN32_WINNT_WS03                   0x0502
#define _WIN32_WINNT_WIN6                   0x0600
#define _WIN32_WINNT_VISTA                  0x0600
#define _WIN32_WINNT_WS08                   0x0600
#define _WIN32_WINNT_LONGHORN               0x0600
#define _WIN32_WINNT_WIN7                   0x0601
#define _WIN32_WINNT_WIN8                   0x0602
#define _WIN32_WINNT_WINBLUE                0x0603
#define _WIN32_WINNT_WINTHRESHOLD           0x0A00 /* ABRACADABRA_THRESHOLD*/
#define _WIN32_WINNT_WIN10                  0x0A00 /* ABRACADABRA_THRESHOLD*/

//
// _WIN32_IE_ version constants
//
#define _WIN32_IE_IE20                      0x0200
#define _WIN32_IE_IE30                      0x0300
#define _WIN32_IE_IE302                     0x0302
#define _WIN32_IE_IE40                      0x0400
#define _WIN32_IE_IE401                     0x0401
#define _WIN32_IE_IE50                      0x0500
#define _WIN32_IE_IE501                     0x0501
#define _WIN32_IE_IE55                      0x0550
#define _WIN32_IE_IE60                      0x0600
#define _WIN32_IE_IE60SP1                   0x0601
#define _WIN32_IE_IE60SP2                   0x0603
#define _WIN32_IE_IE70                      0x0700
#define _WIN32_IE_IE80                      0x0800
#define _WIN32_IE_IE90                      0x0900
#define _WIN32_IE_IE100                     0x0A00
#define _WIN32_IE_IE110                     0x0A00  /* ABRACADABRA_THRESHOLD */

//
// IE <-> OS version mapping
//
// NT4 supports IE versions 2.0 -> 6.0 SP1
#define _WIN32_IE_NT4                       _WIN32_IE_IE20
#define _WIN32_IE_NT4SP1                    _WIN32_IE_IE20
#define _WIN32_IE_NT4SP2                    _WIN32_IE_IE20
#define _WIN32_IE_NT4SP3                    _WIN32_IE_IE302
#define _WIN32_IE_NT4SP4                    _WIN32_IE_IE401
#define _WIN32_IE_NT4SP5                    _WIN32_IE_IE401
#define _WIN32_IE_NT4SP6                    _WIN32_IE_IE50
// Win98 supports IE versions 4.01 -> 6.0 SP1
#define _WIN32_IE_WIN98                     _WIN32_IE_IE401
// Win98SE supports IE versions 5.0 -> 6.0 SP1
#define _WIN32_IE_WIN98SE                   _WIN32_IE_IE50
// WinME supports IE versions 5.5 -> 6.0 SP1
#define _WIN32_IE_WINME                     _WIN32_IE_IE55
// Win2k supports IE versions 5.01 -> 6.0 SP1
#define _WIN32_IE_WIN2K                     _WIN32_IE_IE501
#define _WIN32_IE_WIN2KSP1                  _WIN32_IE_IE501
#define _WIN32_IE_WIN2KSP2                  _WIN32_IE_IE501
#define _WIN32_IE_WIN2KSP3                  _WIN32_IE_IE501
#define _WIN32_IE_WIN2KSP4                  _WIN32_IE_IE501
#define _WIN32_IE_XP                        _WIN32_IE_IE60
#define _WIN32_IE_XPSP1                     _WIN32_IE_IE60SP1
#define _WIN32_IE_XPSP2                     _WIN32_IE_IE60SP2
#define _WIN32_IE_WS03                      0x0602
#define _WIN32_IE_WS03SP1                   _WIN32_IE_IE60SP2
#define _WIN32_IE_WIN6                      _WIN32_IE_IE70
#define _WIN32_IE_LONGHORN                  _WIN32_IE_IE70
#define _WIN32_IE_WIN7                      _WIN32_IE_IE80
#define _WIN32_IE_WIN8                      _WIN32_IE_IE100
#define _WIN32_IE_WINBLUE                   _WIN32_IE_IE100
#define _WIN32_IE_WINTHRESHOLD              _WIN32_IE_IE110  /* ABRACADABRA_THRESHOLD */
#define _WIN32_IE_WIN10                     _WIN32_IE_IE110  /* ABRACADABRA_THRESHOLD */


//
// NTDDI version constants
//
#define NTDDI_WIN2K                         0x05000000
#define NTDDI_WIN2KSP1                      0x05000100
#define NTDDI_WIN2KSP2                      0x05000200
#define NTDDI_WIN2KSP3                      0x05000300
#define NTDDI_WIN2KSP4                      0x05000400

#define NTDDI_WINXP                         0x05010000
#define NTDDI_WINXPSP1                      0x05010100
#define NTDDI_WINXPSP2                      0x05010200
#define NTDDI_WINXPSP3                      0x05010300
#define NTDDI_WINXPSP4                      0x05010400

#define NTDDI_WS03                          0x05020000
#define NTDDI_WS03SP1                       0x05020100
#define NTDDI_WS03SP2                       0x05020200
#define NTDDI_WS03SP3                       0x05020300
#define NTDDI_WS03SP4                       0x05020400

#define NTDDI_WIN6                          0x06000000
#define NTDDI_WIN6SP1                       0x06000100
#define NTDDI_WIN6SP2                       0x06000200
#define NTDDI_WIN6SP3                       0x06000300
#define NTDDI_WIN6SP4                       0x06000400

#define NTDDI_VISTA                         NTDDI_WIN6
#define NTDDI_VISTASP1                      NTDDI_WIN6SP1
#define NTDDI_VISTASP2                      NTDDI_WIN6SP2
#define NTDDI_VISTASP3                      NTDDI_WIN6SP3
#define NTDDI_VISTASP4                      NTDDI_WIN6SP4

#define NTDDI_LONGHORN  NTDDI_VISTA

#define NTDDI_WS08                          NTDDI_WIN6SP1
#define NTDDI_WS08SP2                       NTDDI_WIN6SP2
#define NTDDI_WS08SP3                       NTDDI_WIN6SP3
#define NTDDI_WS08SP4                       NTDDI_WIN6SP4

#define NTDDI_WIN7                          0x06010000
#define NTDDI_WIN8                          0x06020000
#define NTDDI_WINBLUE                       0x06030000
#define NTDDI_WINTHRESHOLD                  0x0A000000  /* ABRACADABRA_THRESHOLD */
#define NTDDI_WIN10                         0x0A000000  /* ABRACADABRA_THRESHOLD */
#define NTDDI_WIN10_TH2                     0x0A000001  /* ABRACADABRA_WIN10_TH2 */
#define NTDDI_WIN10_RS1                     0x0A000002  /* ABRACADABRA_WIN10_RS1 */
#define NTDDI_WIN10_RS2                     0x0A000003  /* ABRACADABRA_WIN10_RS2 */
#define NTDDI_WIN10_RS3                     0x0A000004  /* ABRACADABRA_WIN10_RS3 */
#define NTDDI_WIN10_RS4                     0x0A000005  /* ABRACADABRA_WIN10_RS4 */
#define NTDDI_WIN10_RS5                     0x0A000006  /* ABRACADABRA_WIN10_RS5 */
#define NTDDI_WIN10_19H1                    0x0A000007  /* ABRACADABRA_WIN10_19H1*/
#define NTDDI_WIN10_VB                      0x0A000008  /* ABRACADABRA_WIN10_VB */

#define WDK_NTDDI_VERSION                   NTDDI_WIN10_VB /* ABRACADABRA_WIN10_VB */


//
// masks for version macros
//
#define OSVERSION_MASK      0xFFFF0000
#define SPVERSION_MASK      0x0000FF00
#define SUBVERSION_MASK     0x000000FF


//
// macros to extract various version fields from the NTDDI version
//
#define OSVER(Version)  ((Version) & OSVERSION_MASK)
#define SPVER(Version)  (((Version) & SPVERSION_MASK) >> 8)
#define SUBVER(Version) (((Version) & SUBVERSION_MASK) )

#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
)
#define FSCTL_REQUEST_OPLOCK_LEVEL_1    CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  0, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_REQUEST_OPLOCK_LEVEL_2    CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_REQUEST_BATCH_OPLOCK      CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  2, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_OPLOCK_BREAK_ACKNOWLEDGE  CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  3, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_OPBATCH_ACK_CLOSE_PENDING CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  4, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_OPLOCK_BREAK_NOTIFY       CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  5, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_LOCK_VOLUME               CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  6, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_UNLOCK_VOLUME             CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  7, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_DISMOUNT_VOLUME           CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  8, METHOD_BUFFERED, FILE_ANY_ACCESS)
// decommissioned fsctl value                                              9
#define FSCTL_IS_VOLUME_MOUNTED         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 10, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_IS_PATHNAME_VALID         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 11, METHOD_BUFFERED, FILE_ANY_ACCESS) // PATHNAME_BUFFER,
#define FSCTL_MARK_VOLUME_DIRTY         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 12, METHOD_BUFFERED, FILE_ANY_ACCESS)
// decommissioned fsctl value                                             13
#define FSCTL_QUERY_RETRIEVAL_POINTERS  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 14,  METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_GET_COMPRESSION           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 15, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SET_COMPRESSION           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 16, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA)
// decommissioned fsctl value                                             17
// decommissioned fsctl value                                             18
#define FSCTL_SET_BOOTLOADER_ACCESSED   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 19,  METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_MARK_AS_SYSTEM_HIVE       FSCTL_SET_BOOTLOADER_ACCESSED
#define FSCTL_OPLOCK_BREAK_ACK_NO_2     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 20, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_INVALIDATE_VOLUMES        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 21, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_QUERY_FAT_BPB             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 22, METHOD_BUFFERED, FILE_ANY_ACCESS) // FSCTL_QUERY_FAT_BPB_BUFFER
#define FSCTL_REQUEST_FILTER_OPLOCK     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 23, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_FILESYSTEM_GET_STATISTICS CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 24, METHOD_BUFFERED, FILE_ANY_ACCESS) // FILESYSTEM_STATISTICS

#if (_WIN32_WINNT >= _WIN32_WINNT_NT4)
#define FSCTL_GET_NTFS_VOLUME_DATA      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 25, METHOD_BUFFERED, FILE_ANY_ACCESS) // NTFS_VOLUME_DATA_BUFFER
#define FSCTL_GET_NTFS_FILE_RECORD      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 26, METHOD_BUFFERED, FILE_ANY_ACCESS) // NTFS_FILE_RECORD_INPUT_BUFFER, NTFS_FILE_RECORD_OUTPUT_BUFFER
#define FSCTL_GET_VOLUME_BITMAP         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 27,  METHOD_NEITHER, FILE_ANY_ACCESS) // STARTING_LCN_INPUT_BUFFER, VOLUME_BITMAP_BUFFER
#define FSCTL_GET_RETRIEVAL_POINTERS    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 28,  METHOD_NEITHER, FILE_ANY_ACCESS) // STARTING_VCN_INPUT_BUFFER, RETRIEVAL_POINTERS_BUFFER
#define FSCTL_MOVE_FILE                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 29, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // MOVE_FILE_DATA,
#define FSCTL_IS_VOLUME_DIRTY           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 30, METHOD_BUFFERED, FILE_ANY_ACCESS)
// decommissioned fsctl value                                             31
#define FSCTL_ALLOW_EXTENDED_DASD_IO    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 32, METHOD_NEITHER,  FILE_ANY_ACCESS)
#endif /* _WIN32_WINNT >= _WIN32_WINNT_NT4 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
// decommissioned fsctl value                                             33
// decommissioned fsctl value                                             34
#define FSCTL_FIND_FILES_BY_SID         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 35, METHOD_NEITHER, FILE_ANY_ACCESS)
// decommissioned fsctl value                                             36
// decommissioned fsctl value                                             37
#define FSCTL_SET_OBJECT_ID             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 38, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // FILE_OBJECTID_BUFFER
#define FSCTL_GET_OBJECT_ID             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 39, METHOD_BUFFERED, FILE_ANY_ACCESS) // FILE_OBJECTID_BUFFER
#define FSCTL_DELETE_OBJECT_ID          CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 40, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_SET_REPARSE_POINT         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 41, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // REPARSE_DATA_BUFFER,
#define FSCTL_GET_REPARSE_POINT         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 42, METHOD_BUFFERED, FILE_ANY_ACCESS) // REPARSE_DATA_BUFFER
#define FSCTL_DELETE_REPARSE_POINT      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 43, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // REPARSE_DATA_BUFFER,
#define FSCTL_ENUM_USN_DATA             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 44,  METHOD_NEITHER, FILE_ANY_ACCESS) // MFT_ENUM_DATA,
#define FSCTL_SECURITY_ID_CHECK         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 45,  METHOD_NEITHER, FILE_READ_DATA)  // BULK_SECURITY_TEST_DATA,
#define FSCTL_READ_USN_JOURNAL          CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 46,  METHOD_NEITHER, FILE_ANY_ACCESS) // READ_USN_JOURNAL_DATA, USN
#define FSCTL_SET_OBJECT_ID_EXTENDED    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 47, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_CREATE_OR_GET_OBJECT_ID   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 48, METHOD_BUFFERED, FILE_ANY_ACCESS) // FILE_OBJECTID_BUFFER
#define FSCTL_SET_SPARSE                CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 49, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_SET_ZERO_DATA             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 50, METHOD_BUFFERED, FILE_WRITE_DATA) // FILE_ZERO_DATA_INFORMATION,
#define FSCTL_QUERY_ALLOCATED_RANGES    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 51,  METHOD_NEITHER, FILE_READ_DATA)  // FILE_ALLOCATED_RANGE_BUFFER, FILE_ALLOCATED_RANGE_BUFFER
#define FSCTL_ENABLE_UPGRADE            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 52, METHOD_BUFFERED, FILE_WRITE_DATA)
#define FSCTL_SET_ENCRYPTION            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 53,  METHOD_NEITHER, FILE_ANY_ACCESS) // ENCRYPTION_BUFFER, DECRYPTION_STATUS_BUFFER
#define FSCTL_ENCRYPTION_FSCTL_IO       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 54,  METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_WRITE_RAW_ENCRYPTED       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 55,  METHOD_NEITHER, FILE_SPECIAL_ACCESS) // ENCRYPTED_DATA_INFO, EXTENDED_ENCRYPTED_DATA_INFO
#define FSCTL_READ_RAW_ENCRYPTED        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 56,  METHOD_NEITHER, FILE_SPECIAL_ACCESS) // REQUEST_RAW_ENCRYPTED_DATA, ENCRYPTED_DATA_INFO, EXTENDED_ENCRYPTED_DATA_INFO
#define FSCTL_CREATE_USN_JOURNAL        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 57,  METHOD_NEITHER, FILE_ANY_ACCESS) // CREATE_USN_JOURNAL_DATA,
#define FSCTL_READ_FILE_USN_DATA        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 58,  METHOD_NEITHER, FILE_ANY_ACCESS) // Read the Usn Record for a file
#define FSCTL_WRITE_USN_CLOSE_RECORD    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 59,  METHOD_NEITHER, FILE_ANY_ACCESS) // Generate Close Usn Record
#define FSCTL_EXTEND_VOLUME             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 60, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_QUERY_USN_JOURNAL         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 61, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_DELETE_USN_JOURNAL        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 62, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_MARK_HANDLE               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 63, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SIS_COPYFILE              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 64, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SIS_LINK_FILES            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 65, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA)
// decommissional fsctl value                                             66
// decommissioned fsctl value                                             67
// decommissioned fsctl value                                             68
#define FSCTL_RECALL_FILE               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 69, METHOD_NEITHER, FILE_ANY_ACCESS)
// decommissioned fsctl value                                             70
#define FSCTL_READ_FROM_PLEX            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 71, METHOD_OUT_DIRECT, FILE_READ_DATA)
#define FSCTL_FILE_PREFETCH             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 72, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // FILE_PREFETCH
#endif /* _WIN32_WINNT >= _WIN32_WINNT_WIN2K */

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
#define FSCTL_MAKE_MEDIA_COMPATIBLE         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 76, METHOD_BUFFERED, FILE_WRITE_DATA) // UDFS R/W
#define FSCTL_SET_DEFECT_MANAGEMENT         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 77, METHOD_BUFFERED, FILE_WRITE_DATA) // UDFS R/W
#define FSCTL_QUERY_SPARING_INFO            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 78, METHOD_BUFFERED, FILE_ANY_ACCESS) // UDFS R/W
#define FSCTL_QUERY_ON_DISK_VOLUME_INFO     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 79, METHOD_BUFFERED, FILE_ANY_ACCESS) // C/UDFS
#define FSCTL_SET_VOLUME_COMPRESSION_STATE  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 80, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // VOLUME_COMPRESSION_STATE
// decommissioned fsctl value                                                 80
#define FSCTL_TXFS_MODIFY_RM                CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 81, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_QUERY_RM_INFORMATION     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 82, METHOD_BUFFERED, FILE_READ_DATA)  // TxF
// decommissioned fsctl value                                                 83
#define FSCTL_TXFS_ROLLFORWARD_REDO         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 84, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_ROLLFORWARD_UNDO         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 85, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_START_RM                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 86, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_SHUTDOWN_RM              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 87, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_READ_BACKUP_INFORMATION  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 88, METHOD_BUFFERED, FILE_READ_DATA)  // TxF
#define FSCTL_TXFS_WRITE_BACKUP_INFORMATION CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 89, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_CREATE_SECONDARY_RM      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 90, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_GET_METADATA_INFO        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 91, METHOD_BUFFERED, FILE_READ_DATA)  // TxF
#define FSCTL_TXFS_GET_TRANSACTED_VERSION   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 92, METHOD_BUFFERED, FILE_READ_DATA)  // TxF
// decommissioned fsctl value                                                 93
#define FSCTL_TXFS_SAVEPOINT_INFORMATION    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 94, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_CREATE_MINIVERSION       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 95, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
// decommissioned fsctl value                                                 96
// decommissioned fsctl value                                                 97
// decommissioned fsctl value                                                 98
#define FSCTL_TXFS_TRANSACTION_ACTIVE       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 99, METHOD_BUFFERED, FILE_READ_DATA)  // TxF
#define FSCTL_SET_ZERO_ON_DEALLOCATION      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 101, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_SET_REPAIR                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 102, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_GET_REPAIR                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 103, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_WAIT_FOR_REPAIR               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 104, METHOD_BUFFERED, FILE_ANY_ACCESS)
// decommissioned fsctl value                                                 105
#define FSCTL_INITIATE_REPAIR               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 106, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSC_INTERNAL                  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 107, METHOD_NEITHER, FILE_ANY_ACCESS) // CSC internal implementation
#define FSCTL_SHRINK_VOLUME                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 108, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // SHRINK_VOLUME_INFORMATION
#define FSCTL_SET_SHORT_NAME_BEHAVIOR       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 109, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_DFSR_SET_GHOST_HANDLE_STATE   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 110, METHOD_BUFFERED, FILE_ANY_ACCESS)

//
//  Values 111 - 119 are reserved for FSRM.
//

#define FSCTL_TXFS_LIST_TRANSACTION_LOCKED_FILES \
                                            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 120, METHOD_BUFFERED, FILE_READ_DATA) // TxF
#define FSCTL_TXFS_LIST_TRANSACTIONS        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 121, METHOD_BUFFERED, FILE_READ_DATA) // TxF
#define FSCTL_QUERY_PAGEFILE_ENCRYPTION     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 122, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* _WIN32_WINNT >= _WIN32_WINNT_VISTA */

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
#define FSCTL_RESET_VOLUME_ALLOCATION_HINTS CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 123, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* _WIN32_WINNT >= _WIN32_WINNT_VISTA */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_QUERY_DEPENDENT_VOLUME        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 124, METHOD_BUFFERED, FILE_ANY_ACCESS)    // Dependency File System Filter
#define FSCTL_SD_GLOBAL_CHANGE              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 125, METHOD_BUFFERED, FILE_ANY_ACCESS) // Query/Change NTFS Security Descriptors
#endif /* _WIN32_WINNT >= _WIN32_WINNT_WIN7 */

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
#define FSCTL_TXFS_READ_BACKUP_INFORMATION2 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 126, METHOD_BUFFERED, FILE_ANY_ACCESS) // TxF
#endif /* _WIN32_WINNT >= _WIN32_WINNT_VISTA */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_LOOKUP_STREAM_FROM_CLUSTER    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 127, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_TXFS_WRITE_BACKUP_INFORMATION2 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 128, METHOD_BUFFERED, FILE_ANY_ACCESS) // TxF
#define FSCTL_FILE_TYPE_NOTIFICATION        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 129, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
#define FSCTL_FILE_LEVEL_TRIM               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 130, METHOD_BUFFERED, FILE_WRITE_DATA)
#endif /*_WIN32_WINNT >= _WIN32_WINNT_WIN8 */

//
//  Values 131 - 139 are reserved for FSRM.
//

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_GET_BOOT_AREA_INFO            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 140, METHOD_BUFFERED, FILE_ANY_ACCESS) // BOOT_AREA_INFO
#define FSCTL_GET_RETRIEVAL_POINTER_BASE    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 141, METHOD_BUFFERED, FILE_ANY_ACCESS) // RETRIEVAL_POINTER_BASE
#define FSCTL_SET_PERSISTENT_VOLUME_STATE   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 142, METHOD_BUFFERED, FILE_ANY_ACCESS)  // FILE_FS_PERSISTENT_VOLUME_INFORMATION
#define FSCTL_QUERY_PERSISTENT_VOLUME_STATE CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 143, METHOD_BUFFERED, FILE_ANY_ACCESS)  // FILE_FS_PERSISTENT_VOLUME_INFORMATION

#define FSCTL_REQUEST_OPLOCK                CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 144, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define FSCTL_CSV_TUNNEL_REQUEST            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 145, METHOD_BUFFERED, FILE_ANY_ACCESS) // CSV_TUNNEL_REQUEST
#define FSCTL_IS_CSV_FILE                   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 146, METHOD_BUFFERED, FILE_ANY_ACCESS) // IS_CSV_FILE

#define FSCTL_QUERY_FILE_SYSTEM_RECOGNITION CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 147, METHOD_BUFFERED, FILE_ANY_ACCESS) //
#define FSCTL_CSV_GET_VOLUME_PATH_NAME      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 148, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_GET_VOLUME_NAME_FOR_VOLUME_MOUNT_POINT CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 149, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_GET_VOLUME_PATH_NAMES_FOR_VOLUME_NAME CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 150,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_IS_FILE_ON_CSV_VOLUME         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 151,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* _WIN32_WINNT >= _WIN32_WINNT_WIN7 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
#define FSCTL_CORRUPTION_HANDLING           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 152, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_OFFLOAD_READ                  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 153, METHOD_BUFFERED, FILE_READ_ACCESS)
#define FSCTL_OFFLOAD_WRITE                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 154, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#endif /*_WIN32_WINNT >= _WIN32_WINNT_WIN8 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_CSV_INTERNAL                  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 155,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* _WIN32_WINNT >= _WIN32_WINNT_WIN7 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
#define FSCTL_SET_PURGE_FAILURE_MODE        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 156, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_QUERY_FILE_LAYOUT             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 157, METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_IS_VOLUME_OWNED_BYCSVFS       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 158,  METHOD_BUFFERED, FILE_ANY_ACCESS)

#define FSCTL_GET_INTEGRITY_INFORMATION     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 159, METHOD_BUFFERED, FILE_ANY_ACCESS)                  // FSCTL_GET_INTEGRITY_INFORMATION_BUFFER
#define FSCTL_SET_INTEGRITY_INFORMATION     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 160, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA) // FSCTL_SET_INTEGRITY_INFORMATION_BUFFER

#define FSCTL_QUERY_FILE_REGIONS            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 161, METHOD_BUFFERED, FILE_ANY_ACCESS)

#endif /*_WIN32_WINNT >= _WIN32_WINNT_WIN8 */


#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
#define FSCTL_RKF_INTERNAL                  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 171, METHOD_NEITHER, FILE_ANY_ACCESS) // Resume Key Filter

#define FSCTL_SCRUB_DATA                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 172, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_REPAIR_COPIES                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 173, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA)
#define FSCTL_DISABLE_LOCAL_BUFFERING       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 174, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_MGMT_LOCK                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 175, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_QUERY_DOWN_LEVEL_FILE_SYSTEM_CHARACTERISTICS CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 176, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_ADVANCE_FILE_ID               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 177, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_SYNC_TUNNEL_REQUEST       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 178, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_QUERY_VETO_FILE_DIRECT_IO CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 179, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_WRITE_USN_REASON              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 180, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_CONTROL                   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 181, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_GET_REFS_VOLUME_DATA          CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 182, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_H_BREAKING_SYNC_TUNNEL_REQUEST CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 185, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /*_WIN32_WINNT >= _WIN32_WINNT_WIN8 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
#define FSCTL_QUERY_STORAGE_CLASSES         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 187, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_QUERY_REGION_INFO             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 188, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_USN_TRACK_MODIFIED_RANGES     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 189, METHOD_BUFFERED, FILE_ANY_ACCESS) // USN_TRACK_MODIFIED_RANGES
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
#define FSCTL_QUERY_SHARED_VIRTUAL_DISK_SUPPORT CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 192, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SVHDX_SYNC_TUNNEL_REQUEST         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 193, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SVHDX_SET_INITIATOR_INFORMATION   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 194, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_SET_EXTERNAL_BACKING              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 195, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_GET_EXTERNAL_BACKING              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 196, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_DELETE_EXTERNAL_BACKING           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 197, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_ENUM_EXTERNAL_BACKING             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 198, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_ENUM_OVERLAY                      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 199, METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_ADD_OVERLAY                       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 204, METHOD_BUFFERED, FILE_WRITE_DATA)
#define FSCTL_REMOVE_OVERLAY                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 205, METHOD_BUFFERED, FILE_WRITE_DATA)
#define FSCTL_UPDATE_OVERLAY                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 206, METHOD_BUFFERED, FILE_WRITE_DATA)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN7) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
#define FSCTL_SHUFFLE_FILE                      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 208, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS) // SHUFFLE_FILE_DATA
#endif /*_WIN32_WINNT >= _WIN32_WINNT_WIN8 */
#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
#define FSCTL_DUPLICATE_EXTENTS_TO_FILE         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 209, METHOD_BUFFERED, FILE_WRITE_DATA )
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
#define FSCTL_SPARSE_OVERALLOCATE               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 211, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_STORAGE_QOS_CONTROL               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 212, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WINTHRESHOLD)
#define FSCTL_INITIATE_FILE_METADATA_OPTIMIZATION       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 215, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_QUERY_FILE_METADATA_OPTIMIZATION          CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 216, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINTHRESHOLD) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
#define FSCTL_SVHDX_ASYNC_TUNNEL_REQUEST         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 217, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_GET_WOF_VERSION                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 218, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WINTHRESHOLD)
#define FSCTL_HCS_SYNC_TUNNEL_REQUEST            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 219, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_HCS_ASYNC_TUNNEL_REQUEST           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 220, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_QUERY_EXTENT_READ_CACHE_INFO       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 221, METHOD_NEITHER, FILE_ANY_ACCESS)  // VCN_RANGE_INPUT_BUFFER, EXTENT_READ_CACHE_INFO_BUFFER
#define FSCTL_QUERY_REFS_VOLUME_COUNTER_INFO     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 222, METHOD_NEITHER, FILE_ANY_ACCESS)  // REFS_VOLUME_COUNTER_INFO_INPUT_BUFFER, VOLUME_REFS_INFO_BUFFER
#define FSCTL_CLEAN_VOLUME_METADATA              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 223, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SET_INTEGRITY_INFORMATION_EX       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 224, METHOD_BUFFERED, FILE_ANY_ACCESS) // FSCTL_SET_INTEGRITY_INFORMATION_BUFFER_EX
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINTHRESHOLD) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_SUSPEND_OVERLAY                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 225, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif
#if (_WIN32_WINNT >= _WIN32_WINNT_WINTHRESHOLD)
#define FSCTL_VIRTUAL_STORAGE_QUERY_PROPERTY     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 226, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_FILESYSTEM_GET_STATISTICS_EX       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 227, METHOD_BUFFERED, FILE_ANY_ACCESS) // FILESYSTEM_STATISTICS_EX
#define FSCTL_QUERY_VOLUME_CONTAINER_STATE       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 228, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SET_LAYER_ROOT                     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 229, METHOD_BUFFERED, FILE_ANY_ACCESS) // CONTAINER_ROOT_INFO_INPUT CONTAINER_ROOT_INFO_OUTPUT
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundef"
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_TH2)
#define FSCTL_QUERY_DIRECT_ACCESS_EXTENTS        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 230, METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_NOTIFY_STORAGE_SPACE_ALLOCATION    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 231, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SSDI_STORAGE_REQUEST               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 232, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS1)
#define FSCTL_QUERY_DIRECT_IMAGE_ORIGINAL_BASE   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 233, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_READ_UNPRIVILEGED_USN_JOURNAL      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 234,  METHOD_NEITHER, FILE_ANY_ACCESS) // READ_USN_JOURNAL_DATA, USN
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_TH2)
#define FSCTL_GHOST_FILE_EXTENTS                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 235, METHOD_BUFFERED, FILE_WRITE_ACCESS) // FSCTL_GHOST_FILE_EXTENTS_INPUT_BUFFER
#define FSCTL_QUERY_GHOSTED_FILE_EXTENTS         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 236, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_TH2)
#define FSCTL_UNMAP_SPACE                        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 237, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif
#if (_WIN32_WINNT >= _WIN32_WINNT_WINTHRESHOLD)
#define FSCTL_HCS_SYNC_NO_WRITE_TUNNEL_REQUEST   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 238, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS2)
#define FSCTL_STREAMS_QUERY_PARAMETERS          CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 241, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_STREAMS_ASSOCIATE_ID              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 242, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_STREAMS_QUERY_ID                  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 243, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define FSCTL_GET_RETRIEVAL_POINTERS_AND_REFCOUNT CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 244, METHOD_NEITHER,  FILE_ANY_ACCESS) // STARTING_VCN_INPUT_BUFFER, RETRIEVAL_POINTERS_AND_REFCOUNT_BUFFER

#define FSCTL_QUERY_VOLUME_NUMA_INFO            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 245, METHOD_BUFFERED, FILE_ANY_ACCESS)

#endif
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS2)

#define FSCTL_REFS_DEALLOCATE_RANGES            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 246, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_TH2)
#define FSCTL_QUERY_REFS_SMR_VOLUME_INFO         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 247, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SET_REFS_SMR_VOLUME_GC_PARAMETERS  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 248, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SET_REFS_FILE_STRICTLY_SEQUENTIAL  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 249, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS3)
#define FSCTL_DUPLICATE_EXTENTS_TO_FILE_EX      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 250, METHOD_BUFFERED, FILE_WRITE_DATA)
#define FSCTL_QUERY_BAD_RANGES                  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 251, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SET_DAX_ALLOC_ALIGNMENT_HINT      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 252, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_DELETE_CORRUPTED_REFS_CONTAINER   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 253, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SCRUB_UNDISCOVERABLE_ID           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 254, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS3) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS4)
#define FSCTL_NOTIFY_DATA_CHANGE                CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 255, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS4) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS1)
#define FSCTL_START_VIRTUALIZATION_INSTANCE_EX  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 256, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS1) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS4)
#define FSCTL_ENCRYPTION_KEY_CONTROL            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 257, METHOD_BUFFERED, FILE_ANY_ACCESS)  // protect/unprotect under DPL
#define FSCTL_VIRTUAL_STORAGE_SET_BEHAVIOR      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 258, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS4) */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS1)
#define FSCTL_SET_REPARSE_POINT_EX              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 259, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // REPARSE_DATA_BUFFER_EX
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS1) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS5)
#define FSCTL_REARRANGE_FILE                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 264, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS) // REARRANGE_FILE_DATA
#define FSCTL_VIRTUAL_STORAGE_PASSTHROUGH       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 265, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_GET_RETRIEVAL_POINTER_COUNT       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 266, METHOD_NEITHER,  FILE_ANY_ACCESS) // STARTING_VCN_INPUT_BUFFER, RETRIEVAL_POINTER_COUNT
#if defined(_WIN64)
#define FSCTL_ENABLE_PER_IO_FLAGS               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 267, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* _WIN64 */
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS5) */
//
// AVIO IOCTLS.
//

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#define IOCTL_AVIO_ALLOCATE_STREAM      CTL_CODE(FILE_DEVICE_AVIO, 1, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_AVIO_FREE_STREAM          CTL_CODE(FILE_DEVICE_AVIO, 2, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_AVIO_MODIFY_STREAM        CTL_CODE(FILE_DEVICE_AVIO, 3, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef struct {

    DWORD RecordLength;
    WORD   MajorVersion;
    WORD   MinorVersion;
    DWORDLONG FileReferenceNumber;
    DWORDLONG ParentFileReferenceNumber;
    USN Usn;
    LARGE_INTEGER TimeStamp;
    DWORD Reason;
    DWORD SourceInfo;
    DWORD SecurityId;
    DWORD FileAttributes;
    WORD   FileNameLength;
    WORD   FileNameOffset;
    WCHAR FileName[1];

} USN_RECORD_V2, *PUSN_RECORD_V2;


//
//  These are the generic rights.
//

#define GENERIC_READ                     (0x80000000L)
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL                      (0x10000000L)
typedef HANDLE HKEY;

typedef struct _SHELLEXECUTEINFOA {
  DWORD     cbSize;
  ULONG     fMask;
  HWND      hwnd;
  LPCSTR    lpVerb;
  LPCSTR    lpFile;
  LPCSTR    lpParameters;
  LPCSTR    lpDirectory;
  int       nShow;
  HINSTANCE hInstApp;
  void      *lpIDList;
  LPCSTR    lpClass;
  HKEY      hkeyClass;
  DWORD     dwHotKey;
  union {
    HANDLE hIcon;
    HANDLE hMonitor;
  } DUMMYUNIONNAME;
  HANDLE    hProcess;
} SHELLEXECUTEINFOA, *LPSHELLEXECUTEINFOA;

WINDOWS_IMPORT BOOL WINAPI ShellExecuteExA(SHELLEXECUTEINFOA *pExecInfo);

WINDOWS_IMPORT BOOL WINAPI OpenProcessToken( HANDLE ProcessHandle, DWORD DesiredAccess, HANDLE* TokenHandle);

typedef enum _TOKEN_INFORMATION_CLASS {
  TokenUser = 1,
  TokenGroups,
  TokenPrivileges,
  TokenOwner,
  TokenPrimaryGroup,
  TokenDefaultDacl,
  TokenSource,
  TokenType,
  TokenImpersonationLevel,
  TokenStatistics,
  TokenRestrictedSids,
  TokenSessionId,
  TokenGroupsAndPrivileges,
  TokenSessionReference,
  TokenSandBoxInert,
  TokenAuditPolicy,
  TokenOrigin,
  TokenElevationType,
  TokenLinkedToken,
  TokenElevation,
  TokenHasRestrictions,
  TokenAccessInformation,
  TokenVirtualizationAllowed,
  TokenVirtualizationEnabled,
  TokenIntegrityLevel,
  TokenUIAccess,
  TokenMandatoryPolicy,
  TokenLogonSid,
  TokenIsAppContainer,
  TokenCapabilities,
  TokenAppContainerSid,
  TokenAppContainerNumber,
  TokenUserClaimAttributes,
  TokenDeviceClaimAttributes,
  TokenRestrictedUserClaimAttributes,
  TokenRestrictedDeviceClaimAttributes,
  TokenDeviceGroups,
  TokenRestrictedDeviceGroups,
  TokenSecurityAttributes,
  TokenIsRestricted,
  TokenProcessTrustLevel,
  TokenPrivateNameSpace,
  TokenSingletonAttributes,
  TokenBnoIsolation,
  TokenChildProcessFlags,
  TokenIsLessPrivilegedAppContainer,
  TokenIsSandboxed,
  TokenIsAppSilo,
  TokenLoggingInformation,
  TokenLearningMode,
  MaxTokenInfoClass
} TOKEN_INFORMATION_CLASS, *PTOKEN_INFORMATION_CLASS;

typedef struct _TOKEN_ELEVATION {
    DWORD TokenIsElevated;
} TOKEN_ELEVATION, *PTOKEN_ELEVATION;

#define TOKEN_ASSIGN_PRIMARY    (0x0001)
#define TOKEN_DUPLICATE         (0x0002)
#define TOKEN_IMPERSONATE       (0x0004)
#define TOKEN_QUERY             (0x0008)
#define TOKEN_QUERY_SOURCE      (0x0010)
#define TOKEN_ADJUST_PRIVILEGES (0x0020)
#define TOKEN_ADJUST_GROUPS     (0x0040)
#define TOKEN_ADJUST_DEFAULT    (0x0080)
#define TOKEN_ADJUST_SESSIONID  (0x0100)

#define TOKEN_ALL_ACCESS_P (STANDARD_RIGHTS_REQUIRED  |\
                          TOKEN_ASSIGN_PRIMARY      |\
                          TOKEN_DUPLICATE           |\
                          TOKEN_IMPERSONATE         |\
                          TOKEN_QUERY               |\
                          TOKEN_QUERY_SOURCE        |\
                          TOKEN_ADJUST_PRIVILEGES   |\
                          TOKEN_ADJUST_GROUPS       |\
                          TOKEN_ADJUST_DEFAULT )

#if ((defined(_WIN32_WINNT) && (_WIN32_WINNT > 0x0400)) || (!defined(_WIN32_WINNT)))
#define TOKEN_ALL_ACCESS  (TOKEN_ALL_ACCESS_P |\
                          TOKEN_ADJUST_SESSIONID )
#else
#define TOKEN_ALL_ACCESS  (TOKEN_ALL_ACCESS_P)
#endif

#define TOKEN_READ       (STANDARD_RIGHTS_READ      |\
                          TOKEN_QUERY)


#define TOKEN_WRITE      (STANDARD_RIGHTS_WRITE     |\
                          TOKEN_ADJUST_PRIVILEGES   |\
                          TOKEN_ADJUST_GROUPS       |\
                          TOKEN_ADJUST_DEFAULT)

#define TOKEN_EXECUTE    (STANDARD_RIGHTS_EXECUTE)

#define TOKEN_TRUST_CONSTRAINT_MASK    (STANDARD_RIGHTS_READ  | \
                                       TOKEN_QUERY  |\
                                       TOKEN_QUERY_SOURCE )

WINDOWS_IMPORT BOOL WINAPI GetTokenInformation( HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, LPVOID TokenInformation, DWORD TokenInformationLength, PDWORD ReturnLength);

#define SEE_MASK_DEFAULT           0x00000000
#define SEE_MASK_CLASSNAME         0x00000001   // SHELLEXECUTEINFO.lpClass is valid
#define SEE_MASK_CLASSKEY          0x00000003   // SHELLEXECUTEINFO.hkeyClass is valid
// Note SEE_MASK_INVOKEIDLIST(0xC) implies SEE_MASK_IDLIST(0x04)
#define SEE_MASK_IDLIST            0x00000004   // SHELLEXECUTEINFO.lpIDList is valid
#define SEE_MASK_INVOKEIDLIST      0x0000000c   // enable IContextMenu based verbs
#define SEE_MASK_HOTKEY            0x00000020   // SHELLEXECUTEINFO.dwHotKey is valid
#define SEE_MASK_NOCLOSEPROCESS    0x00000040   // SHELLEXECUTEINFO.hProcess
#define SEE_MASK_CONNECTNETDRV     0x00000080   // enables re-connecting disconnected network drives
#define SEE_MASK_NOASYNC           0x00000100   // block on the call until the invoke has completed, use for callers that exit after calling ShellExecuteEx()
#define SEE_MASK_FLAG_DDEWAIT      SEE_MASK_NOASYNC // Use SEE_MASK_NOASYNC instead of SEE_MASK_FLAG_DDEWAIT as it more accuratly describes the behavior
#define SEE_MASK_DOENVSUBST        0x00000200   // indicates that SHELLEXECUTEINFO.lpFile contains env vars that should be expanded
#define SEE_MASK_FLAG_NO_UI        0x00000400   // disable UI including error messages
#define SEE_MASK_UNICODE           0x00004000
#define SEE_MASK_NO_CONSOLE        0x00008000
#define SEE_MASK_ASYNCOK           0x00100000

#define FILE_FLAG_WRITE_THROUGH         0x80000000
#define FILE_FLAG_OVERLAPPED            0x40000000
#define FILE_FLAG_NO_BUFFERING          0x20000000
#define FILE_FLAG_RANDOM_ACCESS         0x10000000
#define FILE_FLAG_SEQUENTIAL_SCAN       0x08000000
#define FILE_FLAG_DELETE_ON_CLOSE       0x04000000
#define FILE_FLAG_BACKUP_SEMANTICS      0x02000000
#define FILE_FLAG_POSIX_SEMANTICS       0x01000000
#define FILE_FLAG_SESSION_AWARE         0x00800000
#define FILE_FLAG_OPEN_REPARSE_POINT    0x00200000
#define FILE_FLAG_OPEN_NO_RECALL        0x00100000
#define FILE_FLAG_FIRST_PIPE_INSTANCE   0x00080000

#define PAGE_NOACCESS           0x01    
#define PAGE_READONLY           0x02    
#define PAGE_READWRITE          0x04    
#define PAGE_WRITECOPY          0x08    
#define PAGE_EXECUTE            0x10    
#define PAGE_EXECUTE_READ       0x20    
#define PAGE_EXECUTE_READWRITE  0x40    
#define PAGE_EXECUTE_WRITECOPY  0x80    
#define PAGE_GUARD             0x100    
#define PAGE_NOCACHE           0x200    
#define PAGE_WRITECOMBINE      0x400    
#define PAGE_ENCLAVE_THREAD_CONTROL 0x80000000  
#define PAGE_REVERT_TO_FILE_MAP     0x80000000  
#define PAGE_TARGETS_NO_UPDATE      0x40000000  
#define PAGE_TARGETS_INVALID        0x40000000  
#define PAGE_ENCLAVE_UNVALIDATED    0x20000000  
#define PAGE_ENCLAVE_DECOMMIT       0x10000000  
#define MEM_COMMIT                      0x00001000  
#define MEM_RESERVE                     0x00002000  
#define MEM_REPLACE_PLACEHOLDER         0x00004000  
#define MEM_RESERVE_PLACEHOLDER         0x00040000  
#define MEM_RESET                       0x00080000  
#define MEM_TOP_DOWN                    0x00100000  
#define MEM_WRITE_WATCH                 0x00200000  
#define MEM_PHYSICAL                    0x00400000  
#define MEM_ROTATE                      0x00800000  
#define MEM_DIFFERENT_IMAGE_BASE_OK     0x00800000  
#define MEM_RESET_UNDO                  0x01000000  
#define MEM_LARGE_PAGES                 0x20000000  
#define MEM_4MB_PAGES                   0x80000000  
#define MEM_64K_PAGES                   (MEM_LARGE_PAGES | MEM_PHYSICAL)  
#define MEM_UNMAP_WITH_TRANSIENT_BOOST  0x00000001  
#define MEM_COALESCE_PLACEHOLDERS       0x00000001  
#define MEM_PRESERVE_PLACEHOLDER        0x00000002  
#define MEM_DECOMMIT                    0x00004000  
#define MEM_RELEASE                     0x00008000  
#define MEM_FREE                        0x00010000  

#define SECTION_QUERY                0x0001
#define SECTION_MAP_WRITE            0x0002
#define SECTION_MAP_READ             0x0004
#define SECTION_MAP_EXECUTE          0x0008
#define SECTION_EXTEND_SIZE          0x0010
#define SECTION_MAP_EXECUTE_EXPLICIT 0x0020 // not included in SECTION_ALL_ACCESS

#define SECTION_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SECTION_QUERY|\
                            SECTION_MAP_WRITE |      \
                            SECTION_MAP_READ |       \
                            SECTION_MAP_EXECUTE |    \
                            SECTION_EXTEND_SIZE)

#define FILE_MAP_WRITE            SECTION_MAP_WRITE
#define FILE_MAP_READ             SECTION_MAP_READ
#define FILE_MAP_ALL_ACCESS       SECTION_ALL_ACCESS
#define FILE_MAP_EXECUTE          SECTION_MAP_EXECUTE_EXPLICIT  // not included in FILE_MAP_ALL_ACCESS
#define FILE_MAP_COPY             0x00000001
#define FILE_MAP_RESERVE          0x80000000
#define FILE_MAP_TARGETS_INVALID  0x40000000
#define FILE_MAP_LARGE_PAGES      0x20000000

#define SE_CREATE_TOKEN_NAME                         (L"SeCreateTokenPrivilege")
#define SE_ASSIGNPRIMARYTOKEN_NAME                   (L"SeAssignPrimaryTokenPrivilege")
#define SE_LOCK_MEMORY_NAME                          (L"SeLockMemoryPrivilege")
#define SE_INCREASE_QUOTA_NAME                       (L"SeIncreaseQuotaPrivilege")
#define SE_UNSOLICITED_INPUT_NAME                    (L"SeUnsolicitedInputPrivilege")
#define SE_MACHINE_ACCOUNT_NAME                      (L"SeMachineAccountPrivilege")
#define SE_TCB_NAME                                  (L"SeTcbPrivilege")
#define SE_SECURITY_NAME                             (L"SeSecurityPrivilege")
#define SE_TAKE_OWNERSHIP_NAME                       (L"SeTakeOwnershipPrivilege")
#define SE_LOAD_DRIVER_NAME                          (L"SeLoadDriverPrivilege")
#define SE_SYSTEM_PROFILE_NAME                       (L"SeSystemProfilePrivilege")
#define SE_SYSTEMTIME_NAME                           (L"SeSystemtimePrivilege")
#define SE_PROF_SINGLE_PROCESS_NAME                  (L"SeProfileSingleProcessPrivilege")
#define SE_INC_BASE_PRIORITY_NAME                    (L"SeIncreaseBasePriorityPrivilege")
#define SE_CREATE_PAGEFILE_NAME                      (L"SeCreatePagefilePrivilege")
#define SE_CREATE_PERMANENT_NAME                     (L"SeCreatePermanentPrivilege")
#define SE_BACKUP_NAME                               (L"SeBackupPrivilege")
#define SE_RESTORE_NAME                              (L"SeRestorePrivilege")
#define SE_SHUTDOWN_NAME                             (L"SeShutdownPrivilege")
#define SE_DEBUG_NAME                                (L"SeDebugPrivilege")
#define SE_AUDIT_NAME                                (L"SeAuditPrivilege")
#define SE_SYSTEM_ENVIRONMENT_NAME                   (L"SeSystemEnvironmentPrivilege")
#define SE_CHANGE_NOTIFY_NAME                        (L"SeChangeNotifyPrivilege")
#define SE_REMOTE_SHUTDOWN_NAME                      (L"SeRemoteShutdownPrivilege")
#define SE_UNDOCK_NAME                               (L"SeUndockPrivilege")
#define SE_SYNC_AGENT_NAME                           (L"SeSyncAgentPrivilege")
#define SE_ENABLE_DELEGATION_NAME                    (L"SeEnableDelegationPrivilege")
#define SE_MANAGE_VOLUME_NAME                        (L"SeManageVolumePrivilege")
#define SE_IMPERSONATE_NAME                          (L"SeImpersonatePrivilege")
#define SE_CREATE_GLOBAL_NAME                        (L"SeCreateGlobalPrivilege")
#define SE_TRUSTED_CREDMAN_ACCESS_NAME               (L"SeTrustedCredManAccessPrivilege")
#define SE_RELABEL_NAME                              (L"SeRelabelPrivilege")
#define SE_INC_WORKING_SET_NAME                      (L"SeIncreaseWorkingSetPrivilege")
#define SE_TIME_ZONE_NAME                            (L"SeTimeZonePrivilege")
#define SE_CREATE_SYMBOLIC_LINK_NAME                 (L"SeCreateSymbolicLinkPrivilege")
#define SE_DELEGATE_SESSION_USER_IMPERSONATE_NAME    (L"SeDelegateSessionUserImpersonatePrivilege")

#define SE_PRIVILEGE_ENABLED_BY_DEFAULT (0x00000001L)
#define SE_PRIVILEGE_ENABLED            (0x00000002L)
#define SE_PRIVILEGE_REMOVED            (0X00000004L)
#define SE_PRIVILEGE_USED_FOR_ACCESS    (0x80000000L)

#define SE_PRIVILEGE_VALID_ATTRIBUTES   (SE_PRIVILEGE_ENABLED_BY_DEFAULT | \
                                         SE_PRIVILEGE_ENABLED            | \
                                         SE_PRIVILEGE_REMOVED            | \
                                         SE_PRIVILEGE_USED_FOR_ACCESS)


#define ANYSIZE_ARRAY 1 

typedef struct {
    LUID Luid;
    DWORD Attributes;
    } LUID_AND_ATTRIBUTES, * PLUID_AND_ATTRIBUTES;
typedef LUID_AND_ATTRIBUTES LUID_AND_ATTRIBUTES_ARRAY[ANYSIZE_ARRAY];
typedef LUID_AND_ATTRIBUTES_ARRAY *PLUID_AND_ATTRIBUTES_ARRAY;

typedef struct  {
    DWORD PrivilegeCount;
    LUID_AND_ATTRIBUTES Privileges[ANYSIZE_ARRAY];
} TOKEN_PRIVILEGES, *PTOKEN_PRIVILEGES;

WINDOWS_IMPORT BOOL WINAPI SetFilePointerEx( HANDLE hFile, LARGE_INTEGER liDistanceToMove, LARGE_INTEGER* lpNewFilePointer, DWORD dwMoveMethod);

WINDOWS_IMPORT HANDLE WINAPI CreateFileMappingW(HANDLE hFile,LPSECURITY_ATTRIBUTES lpFileMappingAttributes,DWORD flProtect,DWORD dwMaximumSizeHigh,DWORD dwMaximumSizeLow,LPCWSTR lpName);

WINDOWS_IMPORT PVOID WINAPI MapViewOfFile(HANDLE hFileMappingObject,DWORD dwDesiredAccess,DWORD dwFileOffsetHigh,DWORD dwFileOffsetLow,size_t dwNumberOfBytesToMap);

WINDOWS_IMPORT BOOL WINAPI LookupPrivilegeValueW(LPCWSTR lpSystemName,LPCWSTR lpName,LUID *lpLuid);

WINDOWS_IMPORT BOOL WINAPI AdjustTokenPrivileges(HANDLE TokenHandle,BOOL DisableAllPrivileges,TOKEN_PRIVILEGES *NewState,DWORD BufferLength,PTOKEN_PRIVILEGES PreviousState,PDWORD ReturnLength);

WINDOWS_IMPORT BOOL WINAPI GetVolumePathNameW( LPCWSTR lpszFileName, LPWSTR lpszVolumePathName, DWORD cchBufferLength);

WINDOWS_IMPORT BOOL WINAPI GetVolumeNameForVolumeMountPointW( LPCWSTR lpszVolumeMountPoint, LPWSTR  lpszVolumeName, DWORD   cchBufferLength
);

typedef struct _DISK_PERFORMANCE {
  LARGE_INTEGER BytesRead;
  LARGE_INTEGER BytesWritten;
  LARGE_INTEGER ReadTime;
  LARGE_INTEGER WriteTime;
  LARGE_INTEGER IdleTime;
  DWORD         ReadCount;
  DWORD         WriteCount;
  DWORD         QueueDepth;
  DWORD         SplitCount;
  LARGE_INTEGER QueryTime;
  DWORD         StorageDeviceNumber;
  WCHAR         StorageManagerName[8];
} DISK_PERFORMANCE, *PDISK_PERFORMANCE;


#define IOCTL_DISK_BASE                 FILE_DEVICE_DISK
#define IOCTL_DISK_GET_DRIVE_GEOMETRY   CTL_CODE(IOCTL_DISK_BASE, 0x0000, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_GET_PARTITION_INFO   CTL_CODE(IOCTL_DISK_BASE, 0x0001, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_DISK_SET_PARTITION_INFO   CTL_CODE(IOCTL_DISK_BASE, 0x0002, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_DISK_GET_DRIVE_LAYOUT     CTL_CODE(IOCTL_DISK_BASE, 0x0003, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_DISK_SET_DRIVE_LAYOUT     CTL_CODE(IOCTL_DISK_BASE, 0x0004, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_DISK_VERIFY               CTL_CODE(IOCTL_DISK_BASE, 0x0005, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_FORMAT_TRACKS        CTL_CODE(IOCTL_DISK_BASE, 0x0006, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_DISK_REASSIGN_BLOCKS      CTL_CODE(IOCTL_DISK_BASE, 0x0007, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_DISK_PERFORMANCE          CTL_CODE(IOCTL_DISK_BASE, 0x0008, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_IS_WRITABLE          CTL_CODE(IOCTL_DISK_BASE, 0x0009, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_LOGGING              CTL_CODE(IOCTL_DISK_BASE, 0x000a, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_FORMAT_TRACKS_EX     CTL_CODE(IOCTL_DISK_BASE, 0x000b, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_DISK_HISTOGRAM_STRUCTURE  CTL_CODE(IOCTL_DISK_BASE, 0x000c, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_HISTOGRAM_DATA       CTL_CODE(IOCTL_DISK_BASE, 0x000d, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_HISTOGRAM_RESET      CTL_CODE(IOCTL_DISK_BASE, 0x000e, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_REQUEST_STRUCTURE    CTL_CODE(IOCTL_DISK_BASE, 0x000f, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_REQUEST_DATA         CTL_CODE(IOCTL_DISK_BASE, 0x0010, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_PERFORMANCE_OFF      CTL_CODE(IOCTL_DISK_BASE, 0x0018, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct _GLYPHMETRICS {
    UINT    gmBlackBoxX;
    UINT    gmBlackBoxY;
    POINT   gmptGlyphOrigin;
    short   gmCellIncX;
    short   gmCellIncY;
} GLYPHMETRICS, *LPGLYPHMETRICS;

typedef struct _FIXED {
#ifndef _MAC
    WORD    fract;
    short   value;
#else
    short   value;
    WORD    fract;
#endif
} FIXED;

typedef struct _MAT2 {
  FIXED eM11;
  FIXED eM12;
  FIXED eM21;
  FIXED eM22;
} MAT2, *LPMAT2;

#define FW_DONTCARE         0
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900

#define FW_ULTRALIGHT       FW_EXTRALIGHT
#define FW_REGULAR          FW_NORMAL
#define FW_DEMIBOLD         FW_SEMIBOLD
#define FW_ULTRABOLD        FW_EXTRABOLD
#define FW_BLACK            FW_HEAVY

#define ANSI_CHARSET            0
#define DEFAULT_CHARSET         1
#define SYMBOL_CHARSET          2
#define SHIFTJIS_CHARSET        128
#define HANGEUL_CHARSET         129
#define HANGUL_CHARSET          129
#define GB2312_CHARSET          134
#define CHINESEBIG5_CHARSET     136
#define OEM_CHARSET             255

#define JOHAB_CHARSET           130
#define HEBREW_CHARSET          177
#define ARABIC_CHARSET          178
#define GREEK_CHARSET           161
#define TURKISH_CHARSET         162
#define VIETNAMESE_CHARSET      163
#define THAI_CHARSET            222
#define EASTEUROPE_CHARSET      238
#define RUSSIAN_CHARSET         204

#define OUT_DEFAULT_PRECIS          0
#define OUT_STRING_PRECIS           1
#define OUT_CHARACTER_PRECIS        2
#define OUT_STROKE_PRECIS           3
#define OUT_TT_PRECIS               4
#define OUT_DEVICE_PRECIS           5
#define OUT_RASTER_PRECIS           6
#define OUT_TT_ONLY_PRECIS          7
#define OUT_OUTLINE_PRECIS          8
#define OUT_SCREEN_OUTLINE_PRECIS   9
#define OUT_PS_ONLY_PRECIS          10

#define CLIP_DEFAULT_PRECIS     0
#define CLIP_CHARACTER_PRECIS   1
#define CLIP_STROKE_PRECIS      2
#define CLIP_MASK               0xf
#define CLIP_LH_ANGLES          (1<<4)
#define CLIP_TT_ALWAYS          (2<<4)
#if (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
#define CLIP_DFA_DISABLE        (4<<4)
#endif // (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
#define CLIP_EMBEDDED           (8<<4)

#define DEFAULT_QUALITY         0
#define DRAFT_QUALITY           1
#define PROOF_QUALITY           2
#if(WINVER >= 0x0400)
#define NONANTIALIASED_QUALITY  3
#define ANTIALIASED_QUALITY     4
#endif /* WINVER >= 0x0400 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WINXP)
#define CLEARTYPE_QUALITY       5
#define CLEARTYPE_NATURAL_QUALITY       6
#endif

#define DEFAULT_PITCH           0
#define FIXED_PITCH             1
#define VARIABLE_PITCH          2
#if(WINVER >= 0x0400)
#define MONO_FONT               8
#endif /* WINVER >= 0x0400 */

#define ANSI_CHARSET            0
#define DEFAULT_CHARSET         1
#define SYMBOL_CHARSET          2
#define SHIFTJIS_CHARSET        128
#define HANGEUL_CHARSET         129
#define HANGUL_CHARSET          129
#define GB2312_CHARSET          134
#define CHINESEBIG5_CHARSET     136
#define OEM_CHARSET             255
#if(WINVER >= 0x0400)
#define JOHAB_CHARSET           130
#define HEBREW_CHARSET          177
#define ARABIC_CHARSET          178
#define GREEK_CHARSET           161
#define TURKISH_CHARSET         162
#define VIETNAMESE_CHARSET      163
#define THAI_CHARSET            222
#define EASTEUROPE_CHARSET      238
#define RUSSIAN_CHARSET         204

#define MAC_CHARSET             77
#define BALTIC_CHARSET          186

#define FS_LATIN1               0x00000001L
#define FS_LATIN2               0x00000002L
#define FS_CYRILLIC             0x00000004L
#define FS_GREEK                0x00000008L
#define FS_TURKISH              0x00000010L
#define FS_HEBREW               0x00000020L
#define FS_ARABIC               0x00000040L
#define FS_BALTIC               0x00000080L
#define FS_VIETNAMESE           0x00000100L
#define FS_THAI                 0x00010000L
#define FS_JISJAPAN             0x00020000L
#define FS_CHINESESIMP          0x00040000L
#define FS_WANSUNG              0x00080000L
#define FS_CHINESETRAD          0x00100000L
#define FS_JOHAB                0x00200000L
#define FS_SYMBOL               0x80000000L
#endif /* WINVER >= 0x0400 */

/* Font Families */
#define FF_DONTCARE         (0<<4)  /* Don't care or don't know. */
#define FF_ROMAN            (1<<4)  /* Variable stroke width, serifed. */
                                    /* Times Roman, Century Schoolbook, etc. */
#define FF_SWISS            (2<<4)  /* Variable stroke width, sans-serifed. */
                                    /* Helvetica, Swiss, etc. */
#define FF_MODERN           (3<<4)  /* Constant stroke width, serifed or sans-serifed. */
                                    /* Pica, Elite, Courier, etc. */
#define FF_SCRIPT           (4<<4)  /* Cursive, etc. */
#define FF_DECORATIVE       (5<<4)  /* Old English, etc. */

#define GGO_METRICS        0
#define GGO_BITMAP         1
#define GGO_NATIVE         2
#define GGO_BEZIER         3

#if(WINVER >= 0x0400)
#define  GGO_GRAY2_BITMAP   4
#define  GGO_GRAY4_BITMAP   5
#define  GGO_GRAY8_BITMAP   6
#define  GGO_GLYPH_INDEX    0x0080
#endif /* WINVER >= 0x0400 */

typedef struct tagBITMAP {
  LONG   bmType;
  LONG   bmWidth;
  LONG   bmHeight;
  LONG   bmWidthBytes;
  WORD   bmPlanes;
  WORD   bmBitsPixel;
  LPVOID bmBits;
} BITMAP, *PBITMAP, *NPBITMAP, *LPBITMAP;

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
#define  GGO_UNHINTED       0x0100
#endif // (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)

#define TT_POLYGON_TYPE   24

#define TT_PRIM_LINE       1
#define TT_PRIM_QSPLINE    2
#define TT_PRIM_CSPLINE    3

WINDOWS_IMPORT HFONT WINAPI CreateFontA( int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet, DWORD iOutPrecision, DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily, LPCSTR pszFaceName);

WINDOWS_IMPORT DWORD WINAPI GetGlyphOutlineA( HDC hdc, UINT uChar, UINT fuFormat, LPGLYPHMETRICS lpgm, DWORD cjBuffer, LPVOID pvBuffer, const MAT2 *lpmat2);

WINDOWS_IMPORT HGDIOBJ WINAPI SelectObject(HDC hdc,HGDIOBJ h);

WINDOWS_IMPORT void WINAPI Sleep(DWORD dwMilliseconds);
typedef DWORD COLORREF;
typedef DWORD* LPCOLORREF;
typedef struct tagLOGFONTA {
  LONG lfHeight;
  LONG lfWidth;
  LONG lfEscapement;
  LONG lfOrientation;
  LONG lfWeight;
  BYTE lfItalic;
  BYTE lfUnderline;
  BYTE lfStrikeOut;
  BYTE lfCharSet;
  BYTE lfOutPrecision;
  BYTE lfClipPrecision;
  BYTE lfQuality;
  BYTE lfPitchAndFamily;
  CHAR lfFaceName[32];
} LOGFONTA, *PLOGFONTA, *NPLOGFONTA, *LPLOGFONTA;

WINDOWS_IMPORT int WINAPI GetObjectA( HANDLE h, int c, LPVOID pv);

WINDOWS_IMPORT COLORREF WINAPI SetTextColor( HDC hdc, COLORREF color);

WINDOWS_IMPORT int WINAPI SetBkMode( HDC hdc, int mode);
WINDOWS_IMPORT UINT WINAPI SetTextAlign( HDC hdc, UINT align);



/* EnumFonts Masks */
#define RASTER_FONTTYPE     0x0001
#define DEVICE_FONTTYPE     0x0002
#define TRUETYPE_FONTTYPE   0x0004

#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define PALETTERGB(r,g,b)   (0x02000000 | RGB(r,g,b))
#define PALETTEINDEX(i)     ((COLORREF)(0x01000000 | (DWORD)(WORD)(i)))

/* palette entry flags */

#define PC_RESERVED     0x01    /* palette index used for animation */
#define PC_EXPLICIT     0x02    /* palette index is explicit to device */
#define PC_NOCOLLAPSE   0x04    /* do not match color to system palette */

#define GetRValue(rgb)      (LOBYTE(rgb))
#define GetGValue(rgb)      (LOBYTE(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)      (LOBYTE((rgb)>>16))

/* Background Modes */
#define TRANSPARENT         1
#define OPAQUE              2
#define BKMODE_LAST         2

/* Text Alignment Options */
#define TA_NOUPDATECP                0
#define TA_UPDATECP                  1

#define TA_LEFT                      0
#define TA_RIGHT                     2
#define TA_CENTER                    6

#define TA_TOP                       0
#define TA_BOTTOM                    8
#define TA_BASELINE                  24
#if (WINVER >= 0x0400)
#define TA_RTLREADING                256
#define TA_MASK       (TA_BASELINE+TA_CENTER+TA_UPDATECP+TA_RTLREADING)
#else
#define TA_MASK       (TA_BASELINE+TA_CENTER+TA_UPDATECP)
#endif

#define VTA_BASELINE TA_BASELINE
#define VTA_LEFT     TA_BOTTOM
#define VTA_RIGHT    TA_TOP
#define VTA_CENTER   TA_CENTER
#define VTA_BOTTOM   TA_RIGHT
#define VTA_TOP      TA_LEFT

WINDOWS_IMPORT BOOL WINAPI ExtTextOutW( HDC hdc, int x, int y, UINT options , RECT *lprect, LPCWSTR lpString, UINT c, INT  *lpDx);
WINDOWS_IMPORT BOOL WINAPI TextOutW( HDC hdc, int x, int y, LPCWSTR lpString, int c);

#define GCP_DBCS           0x0001
#define GCP_REORDER        0x0002
#define GCP_USEKERNING     0x0008
#define GCP_GLYPHSHAPE     0x0010
#define GCP_LIGATE         0x0020
////#define GCP_GLYPHINDEXING  0x0080
#define GCP_DIACRITIC      0x0100
#define GCP_KASHIDA        0x0400
#define GCP_ERROR          0x8000
#define FLI_MASK           0x103B

#define GCP_JUSTIFY        0x00010000L
////#define GCP_NODIACRITICS   0x00020000L
#define FLI_GLYPHS         0x00040000L
#define GCP_CLASSIN        0x00080000L
#define GCP_MAXEXTENT      0x00100000L
#define GCP_JUSTIFYIN      0x00200000L
#define GCP_DISPLAYZWG      0x00400000L
#define GCP_SYMSWAPOFF      0x00800000L
#define GCP_NUMERICOVERRIDE 0x01000000L
#define GCP_NEUTRALOVERRIDE 0x02000000L
#define GCP_NUMERICSLATIN   0x04000000L
#define GCP_NUMERICSLOCAL   0x08000000L

#define GCPCLASS_LATIN                  1
#define GCPCLASS_HEBREW                 2
#define GCPCLASS_ARABIC                 2
#define GCPCLASS_NEUTRAL                3
#define GCPCLASS_LOCALNUMBER            4
#define GCPCLASS_LATINNUMBER            5
#define GCPCLASS_LATINNUMERICTERMINATOR 6
#define GCPCLASS_LATINNUMERICSEPARATOR  7
#define GCPCLASS_NUMERICSEPARATOR       8
#define GCPCLASS_PREBOUNDLTR         0x80
#define GCPCLASS_PREBOUNDRTL         0x40
#define GCPCLASS_POSTBOUNDLTR        0x20
#define GCPCLASS_POSTBOUNDRTL        0x10

#define GCPGLYPH_LINKBEFORE          0x8000
#define GCPGLYPH_LINKAFTER           0x4000

typedef struct tagGCP_RESULTSA
{
    DWORD   lStructSize;
    LPSTR     lpOutString;
    UINT *lpOrder;
    int  *lpDx;
    int  *lpCaretPos;
    LPSTR   lpClass;
    LPWSTR  lpGlyphs;
    UINT    nGlyphs;
    int     nMaxFit;
} GCP_RESULTSA, *LPGCP_RESULTSA;
typedef struct tagGCP_RESULTSW
{
    DWORD   lStructSize;
    LPWSTR    lpOutString;
    UINT *lpOrder;
    int  *lpDx;
    int  *lpCaretPos;
    LPSTR   lpClass;
    LPWSTR  lpGlyphs;
    UINT    nGlyphs;
    int     nMaxFit;
} GCP_RESULTSW, *LPGCP_RESULTSW;

WINDOWS_IMPORT DWORD WINAPI GetCharacterPlacementW( HDC hdc, LPCWSTR lpString, int nCount, int nMexExtent, LPGCP_RESULTSW lpResults, DWORD dwFlags);

WINDOWS_IMPORT DWORD WINAPI GetGlyphIndicesW( HDC hdc, LPCWSTR lpstr, int c, LPWORD pgi, DWORD fl);

typedef struct tagKERNINGPAIR {
  WORD wFirst;
  WORD wSecond;
  int  iKernAmount;
} KERNINGPAIR, *LPKERNINGPAIR;

WINDOWS_IMPORT DWORD WINAPI GetKerningPairsW( HDC hdc, DWORD nPairs, LPKERNINGPAIR lpKernPair);

/* flAccel flags for the GLYPHSET structure above */

#define GS_8BIT_INDICES     0x00000001

/* flags for GetGlyphIndices */

#define GGI_MARK_NONEXISTING_GLYPHS  0X0001

WINDOWS_IMPORT BOOL WINAPI GetOverlappedResult( HANDLE hFile, LPOVERLAPPED lpOverlapped, LPDWORD lpNumberOfBytesTransferred, BOOL bWait);

WINDOWS_IMPORT HANDLE WINAPI CreateEventA( LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCSTR lpName
);

WINDOWS_IMPORT BOOL WINAPI ResetEvent(HANDLE hEvent);


WINDOWS_IMPORT LPVOID WINAPI HeapAlloc(HANDLE hHeap,DWORD  dwFlags,u64 dwBytes);

WINDOWS_IMPORT HANDLE WINAPI GetProcessHeap(void);


WINDOWS_IMPORT BOOL WINAPI HeapFree(HANDLE hHeap,DWORD dwFlags,LPVOID lpMem);

WINDOWS_IMPORT HPEN WINAPI CreatePen( int iStyle, int cWidth, COLORREF color);

/* Pen Styles */
#define PS_SOLID            0
#define PS_DASH             1       /* -------  */
#define PS_DOT              2       /* .......  */
#define PS_DASHDOT          3       /* _._._._  */
#define PS_DASHDOTDOT       4       /* _.._.._  */
#define PS_NULL             5
#define PS_INSIDEFRAME      6
#define PS_USERSTYLE        7
#define PS_ALTERNATE        8
#define PS_STYLE_MASK       0x0000000F

#define DC_BRUSH            18
#define DC_PEN              19

#define NULL_BRUSH          5
#define ETO_OPAQUE                   0x0002
#define ETO_CLIPPED                  0x0004
#if(WINVER >= 0x0400)
#define ETO_GLYPH_INDEX              0x0010
#define ETO_RTLREADING               0x0080
#define ETO_NUMERICSLOCAL            0x0400
#define ETO_NUMERICSLATIN            0x0800
#define ETO_IGNORELANGUAGE           0x1000
#endif /* WINVER >= 0x0400 */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
#define ETO_PDY                      0x2000
#endif // (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
#if (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
#define ETO_REVERSE_INDEX_MAP        0x10000
#endif

typedef USHORT COLOR16;

typedef struct _TRIVERTEX
{
    LONG    x;
    LONG    y;
    COLOR16 Red;
    COLOR16 Green;
    COLOR16 Blue;
    COLOR16 Alpha;
}TRIVERTEX,*PTRIVERTEX,*LPTRIVERTEX;

typedef struct _BLENDFUNCTION
{
    BYTE   BlendOp;
    BYTE   BlendFlags;
    BYTE   SourceConstantAlpha;
    BYTE   AlphaFormat;
}BLENDFUNCTION,*PBLENDFUNCTION;

typedef struct _GRADIENT_TRIANGLE
{
    ULONG Vertex1;
    ULONG Vertex2;
    ULONG Vertex3;
} GRADIENT_TRIANGLE,*PGRADIENT_TRIANGLE,*LPGRADIENT_TRIANGLE;


#define AC_SRC_OVER                 0x00

//
// alpha format flags
//

#define AC_SRC_ALPHA                0x01

#define GRADIENT_FILL_RECT_H    0x00000000
#define GRADIENT_FILL_RECT_V    0x00000001
#define GRADIENT_FILL_TRIANGLE  0x00000002
#define GRADIENT_FILL_OP_FLAG   0x000000ff

#define TRUE 1
#define FALSE 0

typedef struct tagTEXTMETRICW
{
    LONG        tmHeight;
    LONG        tmAscent;
    LONG        tmDescent;
    LONG        tmInternalLeading;
    LONG        tmExternalLeading;
    LONG        tmAveCharWidth;
    LONG        tmMaxCharWidth;
    LONG        tmWeight;
    LONG        tmOverhang;
    LONG        tmDigitizedAspectX;
    LONG        tmDigitizedAspectY;
    WCHAR       tmFirstChar;
    WCHAR       tmLastChar;
    WCHAR       tmDefaultChar;
    WCHAR       tmBreakChar;
    BYTE        tmItalic;
    BYTE        tmUnderlined;
    BYTE        tmStruckOut;
    BYTE        tmPitchAndFamily;
    BYTE        tmCharSet;
} TEXTMETRICW, *PTEXTMETRICW, *NPTEXTMETRICW, *LPTEXTMETRICW;

#define CF_TEXT               1
#define CF_BITMAP             2
#define CF_METAFILEPICT       3
#define CF_SYLK               4
#define CF_DIF                5
#define CF_TIFF               6
#define CF_OEMTEXT            7
#define CF_DIB                8
#define CF_PALETTE            9
#define CF_PENDATA            10
#define CF_RIFF               11
#define CF_WAVE               12
#define CF_UNICODETEXT        13
#define CF_ENHMETAFILE        14
#define CF_HDROP              15
#define CF_LOCALE             16
#define CF_DIBV5              17

#define CF_OWNERDISPLAY       0x0080
#define CF_DSPTEXT            0x0081
#define CF_DSPBITMAP          0x0082
#define CF_DSPMETAFILEPICT    0x0083
#define CF_DSPENHMETAFILE     0x008E

#define CF_PRIVATEFIRST       0x0200
#define CF_PRIVATELAST        0x02FF

#define CF_GDIOBJFIRST        0x0300
#define CF_GDIOBJLAST         0x03FF

#define VK_LBUTTON             0x01
#define VK_RBUTTON             0x02
#define VK_CANCEL              0x03
#define VK_MBUTTON             0x04
#define VK_XBUTTON1            0x05
#define VK_XBUTTON2            0x06
#define VK_BACK                0x08
#define VK_TAB                 0x09
#define VK_CLEAR               0x0C
#define VK_RETURN              0x0D
#define VK_SHIFT               0x10
#define VK_CONTROL             0x11
#define VK_MENU                0x12
#define VK_PAUSE               0x13
#define VK_CAPITAL             0x14
#define VK_KANA                0x15
#define VK_HANGUL              0x15
#define VK_IME_ON              0x16
#define VK_JUNJA               0x17
#define VK_FINAL               0x18
#define VK_HANJA               0x19
#define VK_KANJI               0x19
#define VK_IME_OFF             0x1A
#define VK_ESCAPE              0x1B
#define VK_CONVERT             0x1C
#define VK_NONCONVERT          0x1D
#define VK_ACCEPT              0x1E
#define VK_MODECHANGE          0x1F
#define VK_SPACE               0x20
#define VK_PRIOR               0x21
#define VK_NEXT                0x22
#define VK_END                 0x23
#define VK_HOME                0x24
#define VK_LEFT                0x25
#define VK_UP                  0x26
#define VK_RIGHT               0x27
#define VK_DOWN                0x28
#define VK_SELECT              0x29
#define VK_PRINT               0x2A
#define VK_EXECUTE             0x2B
#define VK_SNAPSHOT            0x2C
#define VK_INSERT              0x2D
#define VK_DELETE              0x2E
#define VK_HELP                0x2F

#define VK_0                   0x30
#define VK_1                   0x31
#define VK_2                   0x32
#define VK_3                   0x33
#define VK_4                   0x34
#define VK_5                   0x35
#define VK_6                   0x36
#define VK_7                   0x37
#define VK_8                   0x38
#define VK_9                   0x39

#define VK_A                   0x41
#define VK_B                   0x42
#define VK_C                   0x43
#define VK_D                   0x44
#define VK_E                   0x45
#define VK_F                   0x46
#define VK_G                   0x47
#define VK_H                   0x48
#define VK_I                   0x49
#define VK_J                   0x4A
#define VK_K                   0x4B
#define VK_L                   0x4C
#define VK_M                   0x4D
#define VK_N                   0x4E
#define VK_O                   0x4F
#define VK_P                   0x50
#define VK_Q                   0x51
#define VK_R                   0x52
#define VK_S                   0x53
#define VK_T                   0x54
#define VK_U                   0x55
#define VK_V                   0x56
#define VK_W                   0x57
#define VK_X                   0x58
#define VK_Y                   0x59
#define VK_Z                   0x5A

#define VK_LWIN                0x5B
#define VK_RWIN                0x5C
#define VK_APPS                0x5D
#define VK_SLEEP               0x5F

#define VK_NUMPAD0             0x60
#define VK_NUMPAD1             0x61
#define VK_NUMPAD2             0x62
#define VK_NUMPAD3             0x63
#define VK_NUMPAD4             0x64
#define VK_NUMPAD5             0x65
#define VK_NUMPAD6             0x66
#define VK_NUMPAD7             0x67
#define VK_NUMPAD8             0x68
#define VK_NUMPAD9             0x69
#define VK_MULTIPLY            0x6A
#define VK_ADD                 0x6B
#define VK_SEPARATOR           0x6C
#define VK_SUBTRACT            0x6D
#define VK_DECIMAL             0x6E
#define VK_DIVIDE              0x6F

#define VK_F1                  0x70
#define VK_F2                  0x71
#define VK_F3                  0x72
#define VK_F4                  0x73
#define VK_F5                  0x74
#define VK_F6                  0x75
#define VK_F7                  0x76
#define VK_F8                  0x77
#define VK_F9                  0x78
#define VK_F10                 0x79
#define VK_F11                 0x7A
#define VK_F12                 0x7B
#define VK_F13                 0x7C
#define VK_F14                 0x7D
#define VK_F15                 0x7E
#define VK_F16                 0x7F
#define VK_F17                 0x80
#define VK_F18                 0x81
#define VK_F19                 0x82
#define VK_F20                 0x83
#define VK_F21                 0x84
#define VK_F22                 0x85
#define VK_F23                 0x86
#define VK_F24                 0x87

#define VK_NUMLOCK             0x90
#define VK_SCROLL              0x91

#define VK_LSHIFT              0xA0
#define VK_RSHIFT              0xA1
#define VK_LCONTROL            0xA2
#define VK_RCONTROL            0xA3
#define VK_LMENU               0xA4
#define VK_RMENU               0xA5

#define VK_BROWSER_BACK        0xA6
#define VK_BROWSER_FORWARD     0xA7
#define VK_BROWSER_REFRESH     0xA8
#define VK_BROWSER_STOP        0xA9
#define VK_BROWSER_SEARCH      0xAA
#define VK_BROWSER_FAVORITES   0xAB
#define VK_BROWSER_HOME        0xAC

#define VK_VOLUME_MUTE         0xAD
#define VK_VOLUME_DOWN         0xAE
#define VK_VOLUME_UP           0xAF

#define VK_MEDIA_NEXT_TRACK    0xB0
#define VK_MEDIA_PREV_TRACK    0xB1
#define VK_MEDIA_STOP          0xB2
#define VK_MEDIA_PLAY_PAUSE    0xB3

#define VK_LAUNCH_MAIL         0xB4
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define VK_LAUNCH_APP1         0xB6
#define VK_LAUNCH_APP2         0xB7

#define VK_OEM_1               0xBA
#define VK_OEM_PLUS            0xBB
#define VK_OEM_COMMA           0xBC
#define VK_OEM_MINUS           0xBD
#define VK_OEM_PERIOD          0xBE
#define VK_OEM_2               0xBF
#define VK_OEM_3               0xC0
#define VK_OEM_4               0xDB
#define VK_OEM_5               0xDC
#define VK_OEM_6               0xDD
#define VK_OEM_7               0xDE
#define VK_OEM_8               0xDF
#define VK_OEM_102             0xE2

#define VK_PROCESSKEY          0xE5
#define VK_PACKET              0xE7

#define VK_ATTN                0xF6
#define VK_CRSEL               0xF7
#define VK_EXSEL               0xF8
#define VK_EREOF               0xF9
#define VK_PLAY                0xFA
#define VK_ZOOM                0xFB
#define VK_NONAME              0xFC
#define VK_PA1                 0xFD
#define VK_OEM_CLEAR           0xFE

typedef struct tagSIZE {
  LONG cx;
  LONG cy;
} SIZE, *PSIZE, *LPSIZE;

typedef struct tagPAINTSTRUCT {
  HDC  hdc;
  BOOL fErase;
  RECT rcPaint;
  BOOL fRestore;
  BOOL fIncUpdate;
  BYTE rgbReserved[32];
} PAINTSTRUCT, *PPAINTSTRUCT, *NPPAINTSTRUCT, *LPPAINTSTRUCT;

#define GMEM_FIXED          0x0000
#define GMEM_MOVEABLE       0x0002
#define GMEM_NOCOMPACT      0x0010
#define GMEM_NODISCARD      0x0020
#define GMEM_ZEROINIT       0x0040
#define GMEM_MODIFY         0x0080
#define GMEM_DISCARDABLE    0x0100
#define GMEM_NOT_BANKED     0x1000
#define GMEM_SHARE          0x2000
#define GMEM_DDESHARE       0x2000
#define GMEM_NOTIFY         0x4000
#define GMEM_LOWER          GMEM_NOT_BANKED
#define GMEM_VALID_FLAGS    0x7F72
#define GMEM_INVALID_HANDLE 0x8000

WINDOWS_IMPORT int WINAPI GetDIBits(HDC hdc, HBITMAP hbm, UINT start, UINT cLines, LPVOID lpvBits, LPBITMAPINFO lpbmi, UINT usage);

WINDOWS_IMPORT int WINAPI SetDIBits(HDC hdc, HBITMAP hbm, UINT start, UINT cLines, const LPVOID lpBits, const BITMAPINFO *lpbmi, UINT ColorUse);

WINDOWS_IMPORT HDC WINAPI CreateCompatibleDC(HDC hdc);

#define GetObject GetObjectA

#ifndef LOWORD
#define LOWORD(l) ((WORD)((l) & 0xFFFF))
#endif

#ifndef HIWORD
#define HIWORD(l) ((WORD)(((l) >> 16) & 0xFFFF))
#endif


WINDOWS_IMPORT BOOL WINAPI StretchBlt(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop);

WINDOWS_IMPORT BOOL WINAPI DeleteDC(HDC hdc);

WINDOWS_IMPORT int WINAPI SelectClipRgn(HDC hdc, HRGN hrgn);

WINDOWS_IMPORT int WINAPI IntersectClipRect(HDC hdc, int left, int top, int right, int bottom);

WINDOWS_IMPORT COLORREF WINAPI SetDCPenColor(HDC hdc, COLORREF color);

WINDOWS_IMPORT BOOL WINAPI MoveToEx(HDC hdc, int x, int y, LPPOINT lppt);

WINDOWS_IMPORT BOOL WINAPI LineTo(HDC hdc, int x, int y);

WINDOWS_IMPORT HGDIOBJ WINAPI GetStockObject(int i);

WINDOWS_IMPORT BOOL WINAPI Rectangle(HDC hdc, int left, int top, int right, int bottom);

WINDOWS_IMPORT BOOL WINAPI RoundRect(HDC hdc, int left, int top, int right, int bottom, int width, int height);

WINDOWS_IMPORT BOOL WINAPI SetRect(LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom);

WINDOWS_IMPORT COLORREF WINAPI SetBkColor(HDC hdc, COLORREF color);

WINDOWS_IMPORT COLORREF WINAPI SetDCBrushColor(HDC hdc, COLORREF color);

WINDOWS_IMPORT BOOL WINAPI GdiGradientFill(HDC hdc, PTRIVERTEX pVertex, ULONG nVertex, PVOID pMesh, ULONG nMesh, ULONG dwMode);

WINDOWS_IMPORT BOOL WINAPI AlphaBlend(HDC hdcDest, int xDest, int yDest, int wDest, int hDest,
                                      HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, BLENDFUNCTION blend);

WINDOWS_IMPORT BOOL WINAPI Polygon(HDC hdc, const POINT *apt, int cpt);

WINDOWS_IMPORT BOOL WINAPI Polyline(HDC hdc, const POINT *apt, int cpt);

WINDOWS_IMPORT BOOL WINAPI Ellipse(HDC hdc, int left, int top, int right, int bottom);

WINDOWS_IMPORT BOOL WINAPI PolyBezier(HDC hdc, const POINT *apt, DWORD cpt);

WINDOWS_IMPORT BOOL WINAPI BitBlt(HDC hdcDest, int xDest, int yDest, int w, int h,
                                   HDC hdcSrc, int xSrc, int ySrc, DWORD rop);

WINDOWS_IMPORT BOOL WINAPI GetTextMetricsW(HDC hdc, LPTEXTMETRICW lptm);

WINDOWS_IMPORT BOOL WINAPI GetTextExtentPoint32W(HDC hdc, LPCWSTR lpStr, int c, LPSIZE lpSize);

WINDOWS_IMPORT BOOL WINAPI IsClipboardFormatAvailable(UINT format);

WINDOWS_IMPORT BOOL WINAPI OpenClipboard(HWND hWndNewOwner);

WINDOWS_IMPORT HANDLE WINAPI GetClipboardData(UINT uFormat);

WINDOWS_IMPORT u64 WINAPI GlobalSize(HGLOBAL hMem);

WINDOWS_IMPORT LPVOID WINAPI GlobalLock(HGLOBAL hMem);

WINDOWS_IMPORT BOOL WINAPI GlobalUnlock(HGLOBAL hMem);

WINDOWS_IMPORT BOOL WINAPI CloseClipboard(void);

WINDOWS_IMPORT HGLOBAL WINAPI GlobalAlloc(UINT uFlags, u64 dwBytes);

WINDOWS_IMPORT HANDLE WINAPI SetClipboardData(UINT uFormat, HANDLE hMem);

WINDOWS_IMPORT HBITMAP WINAPI CreateCompatibleBitmap(HDC hdc, int cx, int cy);

WINDOWS_IMPORT HDC WINAPI BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint);

WINDOWS_IMPORT BOOL WINAPI EndPaint(HWND hWnd, const PAINTSTRUCT *lpPaint);

WINDOWS_IMPORT short WINAPI GetKeyState(int nVirtKey);

WINDOWS_IMPORT HWND WINAPI SetCapture(HWND hWnd);

WINDOWS_IMPORT BOOL WINAPI ReleaseCapture(void);

WINDOWS_IMPORT HMODULE WINAPI GetModuleHandleA(LPCSTR lpModuleName);
#define GetModuleHandle GetModuleHandleA

WINDOWS_IMPORT HICON WINAPI LoadIconA(HINSTANCE hInstance, LPCSTR lpIconName);

#define IDI_APPLICATION 32512

#define LoadIcon LoadIconW

WINDOWS_IMPORT HCURSOR WINAPI LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName);

#define IDC_ARROW 32512

#define LoadCursor LoadCursorW

WINDOWS_IMPORT BOOL WINAPI UnregisterClassW(LPCWSTR lpClassName, HINSTANCE hInstance);

WINDOWS_IMPORT BOOL WINAPI SetWindowTextA(HWND hWnd, LPCSTR lpString);

WINDOWS_IMPORT HDC WINAPI GetWindowDC(HWND hWnd);

WINDOWS_IMPORT int WINAPI ReleaseDC(HWND hWnd, HDC hDC);

WINDOWS_IMPORT BOOL WINAPI CloseWindow(HWND hWnd);

WINDOWS_IMPORT BOOL WINAPI PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
#define PeekMessage PeekMessageW

WINDOWS_IMPORT int WINAPI GetWindowTextA(HWND hWnd, LPSTR lpString, int nMaxCount);

WINDOWS_IMPORT LONG_PTR WINAPI SetWindowLongPtrA(HWND hWnd,int nIndex,LONG_PTR dwNewLong);

WINDOWS_IMPORT LONG_PTR WINAPI SetWindowLongPtrW(HWND hWnd, int nIndex, LONG_PTR dwNewLong);

#define SetWindowLongPtr SetWindowLongPtrW

typedef struct tagCREATESTRUCTA {
  LPVOID    lpCreateParams;
  HINSTANCE hInstance;
  HMENU     hMenu;
  HWND      hwndParent;
  int       cy;
  int       cx;
  int       y;
  int       x;
  LONG      style;
  LPCSTR    lpszName;
  LPCSTR    lpszClass;
  DWORD     dwExStyle;
} CREATESTRUCTA, *LPCREATESTRUCTA;
#define CREATESTRUCT CREATESTRUCTA

#define GWL_WNDPROC         (-4)
#define GWL_HINSTANCE       (-6)
#define GWL_HWNDPARENT      (-8)
#define GWL_STYLE           (-16)
#define GWL_EXSTYLE         (-20)
#define GWL_USERDATA        (-21)
#define GWL_ID              (-12)


#define DefWindowProc DefWindowProcW

WINDOWS_IMPORT HICON WINAPI LoadIconW(HINSTANCE hInstance, LPCWSTR lpIconName);

WINDOWS_IMPORT HCURSOR WINAPI LoadCursorW(HINSTANCE hInstance, LPCWSTR lpCursorName);

WINDOWS_IMPORT BOOL WINAPI PeekMessageW(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

WINDOWS_IMPORT LONG_PTR WINAPI SetWindowLongPtrW(HWND hWnd, int nIndex, LONG_PTR dwNewLong);

WINDOWS_IMPORT LONG_PTR WINAPI GetWindowLongPtrW(HWND hWnd, int nIndex);

WINDOWS_IMPORT BOOL WINAPI GetCursorPos(LPPOINT lpPoint);


#define GWLP_WNDPROC        (-4)
#define GWLP_HINSTANCE      (-6)
#define GWLP_HWNDPARENT     (-8)
#define GWLP_USERDATA       (-21)
#define GWLP_ID             (-12)

WINDOWS_IMPORT DWORD WINAPI GetLogicalDriveStringsA(DWORD nBufferLength,LPSTR lpBuffer);

WINDOWS_IMPORT DWORD WINAPI SearchPathA(LPCSTR lpPath,LPCSTR lpFileName,LPCSTR lpExtension,DWORD  nBufferLength,LPSTR  lpBuffer,LPSTR  *lpFilePart);

/* End include: windows_loader.h */
    #endif // _WINDOWS_

#endif// OS_FLAGS & OS_FLAG_WINDOWS

#ifndef OSTD_HEADLESS

#if OS_FLAGS & OS_FLAG_LINUX
    #if COMPILER_FLAGS & COMPILER_FLAG_GNU
    #endif

    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/extensions/Xrandr.h>
    #undef 0

    struct _XDisplay;
    typedef struct _XDisplay Display;
    struct _XImage;
    typedef struct _XImage XImage;
    struct wl_display;
    typedef struct wl_display wl_display;
    struct _XGC;
    typedef struct _XGC* GC;
#endif // OS_FLAGS & OS_FLAG_LINUX



typedef struct _Surface_State {
    Surface_Handle handle;
#if OS_FLAGS & OS_FLAG_WINDOWS
    BITMAPINFO bmp_info;
    HBITMAP bmp;
#elif OS_FLAGS & OS_FLAG_LINUX
    GC       gc;
    XImage*  ximage;
    Display *xlib_display;
#endif
    void *pixels;
    bool allocated;
    bool should_close;
} _Surface_State;
unit_local _Surface_State _surface_states[MAX_SURFACES] = {0};

unit_local _Surface_State *_alloc_surface_state(void) {
    for (u64 i = 0; i < MAX_SURFACES; i += 1) {
        if (!_surface_states[i].allocated) {
            memset(&_surface_states[i], 0, sizeof(_Surface_State));
            _surface_states[i].allocated = true;
            return &_surface_states[i];
        }
    }
    return 0;
}

unit_local _Surface_State *_get_surface_state(Surface_Handle h) {
    for (u64 i = 0; i < MAX_SURFACES; i += 1) {
        if (_surface_states[i].allocated && _surface_states[i].handle == h) {
            return &_surface_states[i];
        }
    }
    return 0;
}

#endif // !OSTD_HEADLESS
#endif // (OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)


#if (OS_FLAGS & OS_FLAG_UNIX)

/////////////////////////////////////////////////////
//////
// :Unix
//////
/////////////////////////////////////////////////////

#define _GNU_SOURCE

// todo(charlie) dynamically link & manually  define some stuff to minimize namespace bloat here
#include <stdint.h>
#include <unistd.h>
#include <sched.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
//#include <execinfo.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#if (OS_FLAGS & OS_FLAG_LINUX)

#include <execinfo.h>
#include <time.h>
// For waiting for vblank. Unfortunately.
#include <GL/gl.h>
#include <GL/glx.h>

/* Stupid unix headers isnt giving me everything >?!>!>!>?!>? */

#define CPU_ZERO(cpusetp)	 __CPU_ZERO_S (sizeof (cpu_set_t), cpusetp)
#define CPU_ZERO_S(setsize, cpusetp)	    __CPU_ZERO_S (setsize, cpusetp)
#define CPU_SETSIZE __CPU_SETSIZE
#define CPU_SET(cpu, cpusetp)	 __CPU_SET_S (cpu, sizeof (cpu_set_t), cpusetp)
#define CPU_SET_S(cpu, setsize, cpusetp)   __CPU_SET_S (cpu, setsize, cpusetp)

extern int pthread_setaffinity_np (pthread_t __th, size_t __cpusetsize,
                                   const cpu_set_t *__cpuset);


#endif

#undef 0

#undef bool

typedef struct _Mapped_Region_Desc {
    void *start;
    u32 page_count;
    u32 taken;
} _Mapped_Region_Desc;

typedef struct _Mapped_Region_Desc_Buffer {
    _Mapped_Region_Desc *regions;
    u32 count;
} _Mapped_Region_Desc_Buffer;

// Buffers of mapped regions, each the size of a page
// (with a count of sizeof(_Mapped_Region_Desc) / page_size
unit_local _Mapped_Region_Desc_Buffer *_unix_mapped_region_buffers = 0;
unit_local u64 _unix_mapped_region_buffers_allocated_count = 0;
unit_local u64 _unix_mapped_region_buffers_count = 0;

// todo(charlie): mutex
unit_local void _unix_add_mapped_region(void *start, u64 page_count) {
    System_Info info = sys_get_info();
    if (!_unix_mapped_region_buffers) {
        _unix_mapped_region_buffers = (_Mapped_Region_Desc_Buffer *)mmap(0, (sys_uint)info.page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        assert(_unix_mapped_region_buffers); // todo(charlie) revise
        memset(_unix_mapped_region_buffers, 0, (sys_uint)info.page_size);
        _unix_mapped_region_buffers_allocated_count = info.page_size/sizeof(_Mapped_Region_Desc_Buffer);
        _unix_mapped_region_buffers_count = 0;
    }

    // First, see if this is already mapped (we might be allocating reserved memory)
    for (u64 i = 0; i < _unix_mapped_region_buffers_count; i += 1) {
        _Mapped_Region_Desc_Buffer buffer = _unix_mapped_region_buffers[i];
        assert(buffer.regions);
        assert(buffer.count);

        for (u32 j = 0; j < buffer.count; j += 1) {
            _Mapped_Region_Desc *region = buffer.regions + j;

            void *end = (u8*)region->start + region->page_count*info.page_size;

            if ((u64)start >= (u64)region->start && (u64)start < (u64)end) {
                return;
            }
        }
    }

    for (u64 i = 0; i < _unix_mapped_region_buffers_count; i += 1) {
        _Mapped_Region_Desc_Buffer buffer = _unix_mapped_region_buffers[i];
        assert(buffer.regions);
        assert(buffer.count);

        for (u32 j = 0; j < buffer.count; j += 1) {
            _Mapped_Region_Desc *region = buffer.regions + j;

            if (!region->taken) {
                region->taken = true;
                region->start = start;
                region->page_count = (sys_uint)page_count;
                return;
            }
        }
    }

    ///
    // We did not find free memory for a region descriptor,
    // so allocate a new one


    // Grow buffer of buffers one page at a time
    if (_unix_mapped_region_buffers_count == _unix_mapped_region_buffers_allocated_count) {
        u64 old_count = _unix_mapped_region_buffers_allocated_count/info.page_size;
        u64 new_count = old_count + 1;

        _Mapped_Region_Desc_Buffer *new_buffers = (_Mapped_Region_Desc_Buffer *)mmap(0, (sys_uint)(info.page_size*new_count), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        assert(new_buffers); // todo(charlie) revise

        memcpy(new_buffers, _unix_mapped_region_buffers, (sys_uint)(old_count*info.page_size));

        munmap(_unix_mapped_region_buffers, (sys_uint)(info.page_size*old_count));
        _unix_mapped_region_buffers = new_buffers;

        memset((u8*)_unix_mapped_region_buffers + info.page_size*old_count, 0, (sys_uint)info.page_size);

        _unix_mapped_region_buffers_allocated_count = new_count;
    }

    assert(_unix_mapped_region_buffers_count < _unix_mapped_region_buffers_allocated_count);

    // Grab & initialize next buffer
    _Mapped_Region_Desc_Buffer *buffer = &_unix_mapped_region_buffers[_unix_mapped_region_buffers_count++];
    buffer->count = (sys_uint)(info.page_size/sizeof(_Mapped_Region_Desc));
    buffer->regions = mmap(0, (sys_uint)info.page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memset(buffer->regions, 0, (sys_uint)info.page_size);
    assert(buffer->regions); // todo(charlie) revise

    buffer->regions[0].taken = true;
    buffer->regions[0].start = start;
    buffer->regions[0].page_count = (sys_uint)page_count;
}

unit_local _Mapped_Region_Desc *_unix_find_mapped_region(void *start) {
    for (u64 i = 0; i < _unix_mapped_region_buffers_count; i += 1) {
        _Mapped_Region_Desc_Buffer buffer = _unix_mapped_region_buffers[i];
        assert(buffer.regions);
        assert(buffer.count);

        for (u32 j = 0; j < buffer.count; j += 1) {
            _Mapped_Region_Desc *region = buffer.regions + j;
            if (!region->taken) continue;

            if (region->start == start) {
                return region;
            }
        }
    }
    return 0;
}


System_Info sys_get_info(void) {
    static System_Info info;
    static bool has_retrieved_info = false;

    if (!has_retrieved_info) {
        has_retrieved_info = true;
        long page_size = sysconf(_SC_PAGESIZE);
        if (page_size == -1) {
            info.page_size = 4096;
        } else {
            info.page_size = (u64)page_size;
        }
        info.logical_cpu_count = (u64)sysconf(_SC_NPROCESSORS_ONLN);

        // On Unix, allocation granularity is typically the same as page size
        info.granularity = info.page_size;
    }

    return info;
}

void *sys_map_pages(u64 action, void *virtual_base, u64 number_of_pages, bool strict_base_address) {
    System_Info info = sys_get_info();
    u64 amount_in_bytes = info.page_size * number_of_pages;

    int flags = MAP_ANONYMOUS | MAP_PRIVATE;
    int prot = 0;

    if (action & SYS_MEMORY_RESERVE) {
        prot |= PROT_NONE;
    }
    if (action & SYS_MEMORY_ALLOCATE) {
        prot |= PROT_READ | PROT_WRITE;
    }

    if (virtual_base) {
        if (strict_base_address) flags |= MAP_FIXED;
    }

    void *result = mmap(virtual_base, (sys_uint)amount_in_bytes, prot, flags, -1, 0);
    if (result == MAP_FAILED) {
        return 0;
    }

    _unix_add_mapped_region(result, number_of_pages);

    return result;
}

bool sys_unmap_pages(void *address) {
    System_Info info = sys_get_info();

    _Mapped_Region_Desc *region = _unix_find_mapped_region(address);
    if (region) {
        munmap(region->start, (sys_uint)(info.page_size * region->page_count));
        region->taken = false;
    }

    return region != 0;
}

bool sys_deallocate_pages(void *address, u64 number_of_pages) {
#if !(COMPILER_FLAGS & COMPILER_FLAG_EMSCRIPTEN)
    System_Info info = sys_get_info();
    u64 amount_in_bytes = info.page_size * number_of_pages;

    if (madvise(address, amount_in_bytes, MADV_DONTNEED) != 0) {
        return false;
    }
    return true;
#else
    (void)address; (void)number_of_pages;
    return true;
#endif
}

u64 sys_query_mapped_regions(void *start, void *end, Mapped_Memory_Info *result, u64 result_count) {
    u64 counter = 0;
    if (!result) result_count = U64_MAX;

    System_Info info = sys_get_info();

    start = (void*)(((u64)start + info.page_size-1) & ~(info.page_size-1));

    for (u64 i = 0; i < _unix_mapped_region_buffers_count; i += 1) {
        _Mapped_Region_Desc_Buffer buffer = _unix_mapped_region_buffers[i];
        assert(buffer.regions);
        assert(buffer.count);

        for (u32 j = 0; j < buffer.count; j += 1) {
            _Mapped_Region_Desc *region = buffer.regions + j;
            if (!region->taken) continue;

            if ((u64)region->start >= (u64)start && (u64)region->start < (u64)end) {
                if (result && result_count > counter) {
                    Mapped_Memory_Info m = (Mapped_Memory_Info){ 0 };
                    m.base = region->start;
                    m.page_count = region->page_count;
                    result[counter] = m;
                }
                counter += 1;
            }
        }
    }

    return counter;
}

void *sys_find_mappable_range(u64 page_count) {
    (void)page_count;
    assertmsg(false, "sys_find_mappable_range unimplemented on linux"); // todo(charlie)
    return 0;
}

s64 sys_write(File_Handle f, void *data, u64 size) {
    s64 written = (s64)write((int)(u64)f, data, (sys_uint)size);
    if (written < 0) written = 0;
    return written;
}

s64 sys_write_string(File_Handle f, string s) {
    return sys_write(f, s.data, s.count);
}

s64 sys_read(File_Handle h, void *buffer, u64 buffer_size) {
    s64 readeded = (s64)read((int)(u64)h, buffer, (sys_uint)buffer_size);
    return readeded < 0 ? 0 : readeded;
}

bool sys_make_pipe(File_Handle *read, File_Handle *write) {
    int pipe_fds[2];
    if (pipe(pipe_fds) == -1) return false;
    *read = (File_Handle)(u64)pipe_fds[0];
    *write = (File_Handle)(u64)pipe_fds[1];
    return true;
}

void sys_close(File_Handle h) {
    close((int)(u64)h);
}

File_Handle sys_open_file(string path, File_Open_Flags flags) {
    char cpath[MAX_PATH_LENGTH];
    u64 path_len = min(path.count, MAX_PATH_LENGTH - 1);
    memcpy(cpath, path.data, (sys_uint)path_len);
    cpath[path_len] = 0;

    int unix_flags = 0;

    if (flags & FILE_OPEN_WRITE) {
        unix_flags |= (flags & FILE_OPEN_READ) ? O_RDWR : O_WRONLY;
    } else if (flags & FILE_OPEN_READ) {
        unix_flags |= O_RDONLY;
    }

    if (flags & FILE_OPEN_CREATE) {
        unix_flags |= O_CREAT;
    }
    if (flags & FILE_OPEN_RESET) {
        unix_flags |= O_TRUNC;
    } else {
        unix_flags |= O_APPEND;
    }

    int fd = open(cpath, unix_flags, 0644);
    if (fd < 0) return 0;

    return (File_Handle)(u64)fd;
}

u64 sys_get_file_size(File_Handle f) {
    struct stat file_stat;
    if (fstat((int)(u64)f, &file_stat) == -1) {
        return 0;
    }
    return (u64)file_stat.st_size;
}

bool sys_set_file_position(File_Handle f, u64 position) {
    return lseek((int)(u64)f, (off_t)position, SEEK_SET) != (off_t)-1;
}

bool sys_make_directory(string path, bool recursive) {
    if (path.count == 0) return false;

    char cpath[2048];
    size_t n = (path.count < sizeof(cpath) - 1) ? (size_t)path.count : (sizeof(cpath) - 1);
    memcpy(cpath, path.data, n);
    cpath[n] = 0;

    if (!recursive) {
        if (mkdir(cpath, 0777) == 0) return true;
        if (errno == EEXIST) {
            struct stat st;
            if (stat(cpath, &st) == 0 && S_ISDIR(st.st_mode)) return true;
        }
        return false;
    }

    char buffer[2048];
    size_t len = strlen(cpath);
    if (len >= sizeof(buffer)) return false;
    memcpy(buffer, cpath, len + 1);

    for (size_t i = 0; i < len; ++i) {
        if (buffer[i] == '/' || buffer[i] == '\\') {
            if (i == 0) continue; 
            char saved = buffer[i];
            buffer[i] = 0;
            if (mkdir(buffer, 0777) != 0) {
                if (errno != EEXIST) return false;
            }
            buffer[i] = saved;
        }
    }

    if (mkdir(buffer, 0777) != 0) {
        if (errno != EEXIST) return false;
    }
    return true;
}

bool sys_remove_directory(string path, bool recursive) {
    if (path.count == 0) return false;

    char cpath[2048];
    size_t n = (path.count < sizeof(cpath) - 1) ? (size_t)path.count : (sizeof(cpath) - 1);
    memcpy(cpath, path.data, n);
    cpath[n] = 0;

    if (!recursive) {
        return rmdir(cpath) == 0;
    }

    DIR *dir = opendir(cpath);
    if (!dir) return false;

    size_t base_len = strlen(cpath);
    int has_slash = (base_len > 0 && (cpath[base_len - 1] == '/' || cpath[base_len - 1] == '\\'));

    struct dirent *ent;
    while ((ent = readdir(dir)) != 0) {
        if (ent->d_name[0] == '.' && (ent->d_name[1] == 0 ||
                                      (ent->d_name[1] == '.' && ent->d_name[2] == 0))) {
            continue; // skip "." and ".."
        }

        char entry_path[2048];
        if (has_slash) {
            if (snprintf(entry_path, sizeof(entry_path), "%s%s", cpath, ent->d_name) >= (int)sizeof(entry_path)) {
                closedir(dir);
                return false;
            }
        } else {
            if (snprintf(entry_path, sizeof(entry_path), "%s/%s", cpath, ent->d_name) >= (int)sizeof(entry_path)) {
                closedir(dir);
                return false;
            }
        }

        struct stat st;
        if (lstat(entry_path, &st) != 0) {
            closedir(dir);
            return false;
        }

        if (S_ISDIR(st.st_mode)) {
            string child;
            child.data  = (u8*)entry_path;
            child.count = (u64)strlen(entry_path);
            if (!sys_remove_directory(child, true)) {
                closedir(dir);
                return false;
            }
        } else {
            if (unlink(entry_path) != 0) {
                closedir(dir);
                return false;
            }
        }
    }

    closedir(dir);

    return rmdir(cpath) == 0;
}

bool sys_is_file(string path) {
    if (path.count == 0) return false;

    char cpath[2048];
    size_t n = (path.count < sizeof(cpath) - 1) ? (size_t)path.count : (sizeof(cpath) - 1);
    memcpy(cpath, path.data, n);
    cpath[n] = 0;

    struct stat st;
    if (stat(cpath, &st) != 0) return false;
    return S_ISREG(st.st_mode);
}

bool sys_is_directory(string path) {
    if (path.count == 0) return false;

    char cpath[2048];
    size_t n = (path.count < sizeof(cpath) - 1) ? (size_t)path.count : (sizeof(cpath) - 1);
    memcpy(cpath, path.data, n);
    cpath[n] = 0;

    struct stat st;
    if (stat(cpath, &st) != 0) return false;
    return S_ISDIR(st.st_mode);
}


unit_local int _to_win_sock_err(Socket_Result r) {
    switch(r) {
        case SOCKET_OK:                  return 0;
        case SOCKET_DISCONNECTED:        return ECONNRESET;
        case SOCKET_NOT_INITIALIZED:     return EINVAL;
        case SOCKET_NOACCESS:            return EACCES;
        case SOCKET_IN_PROGRESS:         return EWOULDBLOCK;
        case SOCKET_NOT_A_SOCKET:        return ENOTSOCK;
        case SOCKET_INVALID_ADDRESS:     return EFAULT;
        case SOCKET_TIMED_OUT:           return ETIMEDOUT;
        case SOCKET_CONNECTION_REFUSED:  return ECONNREFUSED;
        case SOCKET_CONNECTION_RESET:    return ECONNRESET;
        case SOCKET_ALREADY_CONNECTED:   return EISCONN;
        case SOCKET_ADDRESS_IN_USE:      return EADDRINUSE;
        case SOCKET_NETWORK_UNREACHABLE: return ENETUNREACH;
        case SOCKET_HOST_UNREACHABLE:    return EHOSTUNREACH;
        case SOCKET_PROTOCOL_ERROR:      return EPROTONOSUPPORT;
        default:                         return -1;
    }
}

u32 sys_convert_address_string(string address) {
    assert(address.count < 1024);
    char addr_str[1024] = {0};
    memcpy(addr_str, address.data, (sys_uint)address.count);
    addr_str[address.count] = '\0';
    return inet_addr(addr_str);
}

Socket_Result sys_socket_init(Socket *s, Socket_Domain domain, Socket_Type type, Socket_Protocol protocol) {
    int af = 0;
    switch(domain) {
        case SOCKET_DOMAIN_IPV4:
            af = AF_INET;
            break;
        case SOCKET_DOMAIN_BLUETOOTH:
            return SOCKET_INVALID_ADDRESS;
        case SOCKET_DOMAIN_APPLETALK:
            return SOCKET_INVALID_ADDRESS;
#if OS_FLAGS & OS_FLAG_UNIX
        case SOCKET_DOMAIN_UNIX:
            return SOCKET_INVALID_ADDRESS;
#endif
        default:
            return SOCKET_PROTOCOL_ERROR;
    }

    int sock_type = 0;
    switch(type) {
        case SOCKET_TYPE_STREAM:
            sock_type = SOCK_STREAM;
            break;
        case SOCKET_TYPE_DGRAM:
            sock_type = SOCK_DGRAM;
            break;
        case SOCKET_TYPE_RAW:
            sock_type = SOCK_RAW;
            break;
        case SOCKET_TYPE_RDM:
            sock_type = SOCK_RDM;
            break;
        case SOCKET_TYPE_SEQPACKET:
            sock_type = SOCK_SEQPACKET;
            break;
        default:
            return SOCKET_PROTOCOL_ERROR;
    }

    int proto = 0;
    switch(protocol) {
        case SOCKET_PROTOCOL_TCP:
            proto = IPPROTO_TCP;
            break;
        case SOCKET_PROTOCOL_UDP:
            proto = IPPROTO_UDP;
            break;
        default:
            return SOCKET_PROTOCOL_ERROR;
    }

    int sock = socket(af, sock_type, proto);
    if (sock < 0) {
        return SOCKET_PROTOCOL_ERROR;
    }

    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    *s = (Socket)sock;
    return SOCKET_OK;
}

Socket_Result sys_socket_bind(Socket sock, u32 address, u16 port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl((u16)address);
    int result = bind((int)sock, (struct sockaddr*)&addr, sizeof(addr));
    if (result < 0) {
        int err = errno;
        switch(err) {
            case EADDRINUSE: return SOCKET_ADDRESS_IN_USE;
            case EACCES:     return SOCKET_NOACCESS;
            default:         return SOCKET_PROTOCOL_ERROR;
        }
    }
    return SOCKET_OK;
}

Socket_Result sys_socket_listen(Socket sock, s64 backlog) {
    int result = listen((int)sock, (int)backlog);
    if (result < 0) {
        return SOCKET_PROTOCOL_ERROR;
    }
    return SOCKET_OK;
}

Socket_Result sys_socket_accept(Socket sock, Socket *accepted, u64 timeout_ms) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);

    struct timeval tv;
    tv.tv_sec  = (long)(timeout_ms / 1000);
    tv.tv_usec = (long)((timeout_ms % 1000) * 1000);

    int select_result = select((int)sock + 1, &readfds, 0, 0, &tv);
    if (select_result == 0) {
        return SOCKET_TIMED_OUT;
    }
    if (select_result < 0) {
        return SOCKET_PROTOCOL_ERROR;
    }

    // Socket is ready for reading (an incoming connection)
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    int client = accept((int)sock, (struct sockaddr*)&addr, &addr_len);
    if (client < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN)
            return SOCKET_IN_PROGRESS;
        return SOCKET_PROTOCOL_ERROR;
    }
    *accepted = (Socket)client;
    return SOCKET_OK;
}

Socket_Result sys_socket_connect(Socket sock, u32 address, u16 port, Socket_Domain domain) {
    if (domain != SOCKET_DOMAIN_IPV4)
        return SOCKET_INVALID_ADDRESS;

    struct sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(port);
    addr_in.sin_addr.s_addr = address;
    if (addr_in.sin_addr.s_addr == INADDR_NONE)
        return SOCKET_INVALID_ADDRESS;

    int result = connect((int)sock, (struct sockaddr*)&addr_in, sizeof(addr_in));
    if (result < 0) {
        int err = errno;
        if (err == EINPROGRESS || err == EWOULDBLOCK)
            return SOCKET_IN_PROGRESS;
        if (err == ETIMEDOUT)
            return SOCKET_TIMED_OUT;
        if (err == ECONNREFUSED)
            return SOCKET_CONNECTION_REFUSED;
        if (err == EALREADY)
            return SOCKET_ALREADY_CONNECTED;
        return SOCKET_PROTOCOL_ERROR;
    }
    return SOCKET_OK;
}

Socket_Result sys_socket_send(Socket sock, void *data, u64 length, u64 *sent) {
    ssize_t result = send((int)sock, data, (sys_uint)length, 0);
    if (result < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            if (sent)
                *sent = 0;
            return SOCKET_IN_PROGRESS;
        }
        return SOCKET_PROTOCOL_ERROR;
    }
    if (sent)
        *sent = result > 0 ? (u64)result : 0;
    return SOCKET_OK;
}

Socket_Result sys_socket_recv(Socket sock, void *buffer, u64 length, u64 *received) {
    ssize_t result = recv((int)sock, buffer, (sys_uint)length, 0);
    if (result < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            if (received)
                *received = 0;
            return SOCKET_IN_PROGRESS;
        }
        return SOCKET_PROTOCOL_ERROR;
    } else if (result == 0) {
        if (received)
            *received = 0;
        return SOCKET_DISCONNECTED;
    }
    if (received)
        *received = result > 0 ? (u64)result : 0;
    return SOCKET_OK;
}

Socket_Result sys_socket_close(Socket sock) {
    int result = close((int)sock);
    if (result < 0)
        return SOCKET_PROTOCOL_ERROR;
    return SOCKET_OK;
}

Socket_Result sys_socket_set_blocking(Socket *sock, bool blocking) {
    int fd = (int)(*sock);
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0)
        return SOCKET_PROTOCOL_ERROR;
    if (!blocking)
        flags |= O_NONBLOCK;
    else
        flags &= ~O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0)
        return SOCKET_PROTOCOL_ERROR;
    return SOCKET_OK;
}

Socket_Result sys_set_socket_blocking_timeout(Socket socket, u64 ms) {
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = (sys_int)ms*1000;
    setsockopt((int)socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
    return SOCKET_OK;
}

u64 sys_get_current_thread_id(void) {
    return (u64)pthread_self();
}

bool sys_thread_key_init(Thread_Key *key) {
    pthread_key_t tmp;
    if (pthread_key_create(&tmp, 0) != 0) return false;
    *key = (void*)(uintptr_t)tmp;  // store key value in pointer-sized slot
    return true;
}

bool sys_thread_key_write(Thread_Key key, void* value) {
    return pthread_setspecific((pthread_key_t)(uintptr_t)key, value) == 0;
}

void* sys_thread_key_read(Thread_Key key) {
    return pthread_getspecific((pthread_key_t)(uintptr_t)key);
}

unit_local void* _unix_thread_proc(void *arg) {
    Thread *t = (Thread*)arg;
    
    t->id = (u64)(uintptr_t)pthread_self();
    
    _ostd_register_thread_storage(t->id);
    
    s64 ret = t->proc(t);
    
    _ostd_get_thread_storage()->taken = false;
    
    return (void*)(u64)ret;
}

bool sys_thread_init(Thread *thread, Thread_Proc proc, void *userdata) {
    thread->handle = thread->handle_backing;
    thread->userdata = userdata;
    thread->id = 0;
    thread->is_suspended = true;
    thread->proc = proc;
    return true;
}
bool sys_thread_start(Thread *thread) {
    thread->is_suspended = false;
    return pthread_create((pthread_t*)thread->handle, 0, _unix_thread_proc, thread) == 0;
}
s64 sys_thread_join(Thread *thread) {
    void *ret = 0;
    pthread_join(*(pthread_t*)thread->handle, &ret);
    return (s64)(u64)ret;
}
void sys_thread_close(Thread *thread) {
    (void)thread;
}

bool sys_mutex_init(Mutex *mutex) {
    if (!mutex) return false;
    mutex->handle = mutex->handle_backing;

    pthread_mutexattr_t attr;
    if (pthread_mutexattr_init(&attr) != 0) return false;
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    int rc = pthread_mutex_init((pthread_mutex_t*)mutex->handle, &attr);
    pthread_mutexattr_destroy(&attr);
    return rc == 0;
}

bool sys_mutex_uninit(Mutex *mutex) {
    if (!mutex || !mutex->handle) return false;
    int rc = pthread_mutex_destroy((pthread_mutex_t*)mutex->handle);
    mutex->handle = 0;
    return rc == 0;
}

void sys_mutex_acquire(Mutex mutex) {
    pthread_mutex_lock((pthread_mutex_t*)mutex.handle);
}

void sys_mutex_release(Mutex mutex) {
    pthread_mutex_unlock((pthread_mutex_t*)mutex.handle);
}

OSTD_LIB bool sys_semaphore_init(Semaphore *sem) {
    sem->handle = sem->handle_backing;
    return sem_init((sem_t*)sem->handle, 0, 0) == 0;
}

OSTD_LIB void sys_semaphore_signal(Semaphore *sem) {
    sem_post((sem_t*)sem->handle);
}

OSTD_LIB void sys_semaphore_wait(Semaphore* sem) {
    while (sem_wait((sem_t*)sem->handle) == -1 && errno == EINTR) { }
}

OSTD_LIB void sys_semaphore_uninit(Semaphore *sem) {
    sem_destroy((sem_t*)sem->handle);
}

inline unit_local u32 sys_atomic_add_32(volatile u32 *addend, u32 value) {
    return __atomic_fetch_add(addend, value, __ATOMIC_SEQ_CST);
}

inline unit_local u64 sys_atomic_add_64(volatile u64 *addend, u64 value) {
    return __atomic_fetch_add(addend, value, __ATOMIC_SEQ_CST);
}

float64 sys_get_seconds_monotonic(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    float64 t = (float64)ts.tv_sec + (float64)ts.tv_nsec / 1e9;

    local_persist float64 start_time = 0.0;
	if (start_time == 0.0) {
	   start_time = t;
	}

	return t - start_time;
}



void sys_set_thread_affinity_mask(Thread_Handle thread, u64 bits) {
#if (OS_FLAGS & OS_FLAG_ANDROID) || (OS_FLAGS & OS_FLAG_EMSCRIPTEN)
    (void)thread; (void)bits;
    return;
#else
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);

    for (int i = 0; i < 64; i++) {
        if (bits & (1ULL << i)) {
            CPU_SET(i, &cpuset);
        }
    }

    pthread_setaffinity_np((pthread_t)thread, sizeof(cpu_set_t), &cpuset);
#endif
}

Thread_Handle sys_get_current_thread(void) {
    return (Thread_Handle)pthread_self();
}

#endif // OS_FLAGS & OS_FLAG_UNIX

#if (OS_FLAGS & OS_FLAG_WINDOWS)

/////////////////////////////////////////////////////
//////
// :Windows
//////
/////////////////////////////////////////////////////

#if COMPILER_FLAGS & COMPILER_FLAG_MSC
    #pragma comment(lib, "kernel32")
    #pragma comment(lib, "user32")
    #pragma comment(lib, "shcore")
    #pragma comment(lib, "advapi32")
    #pragma comment(lib, "dbghelp")
    #pragma comment(lib, "pdh")
    #pragma comment(lib, "winmm")
    #pragma comment(lib, "ws2_32.lib")
    #pragma comment(lib, "shell32")
    #pragma comment(lib, "Msimg32.lib")
#ifndef OSTD_HEADLESS
    #pragma comment(lib, "gdi32")
    #pragma comment(lib, "dxgi")
#endif // !OSTD_HEADLESS

#endif // COMPILER_FLAGS & COMPILER_FLAG_MSC


unit_local u64 _win_utf8_to_wide(string utf8, u16 *result, u64 result_max) {
    u64 n = (u64)MultiByteToWideChar(CP_UTF8, 0, (LPCCH)utf8.data, (int)utf8.count, (LPWSTR)result, (int)result_max);
    if (n < result_max) result[n] = 0;
    return n;
}


unit_local u64 _wide_strlen(u16 *str) {
    u64 len = 0;
    while (str[len] != 0) {
        len++;
    }
    return len;
}

unit_local s64 _wide_strcmp(u16 *s1, u16 *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (s64)*s1 - (s64)*s2;
}

unit_local void _win_wide_to_utf8(u16 *s, string *utf8) {
    u64 len = _wide_strlen(s);
    int result = WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)s, -1, (char*)utf8->data, (int)len*4+1, 0, 0);
    assert(result);

    utf8->count = (u64)(len);
}

#ifndef OSTD_HEADLESS

typedef enum MONITOR_DPI_TYPE {
  MDT_EFFECTIVE_DPI = 0,
  MDT_ANGULAR_DPI = 1,
  MDT_RAW_DPI = 2,
  MDT_DEFAULT
} MONITOR_DPI_TYPE;

typedef enum PROCESS_DPI_AWARENESS {
  PROCESS_DPI_UNAWARE = 0,
  PROCESS_SYSTEM_DPI_AWARE = 1,
  PROCESS_PER_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;
__declspec(dllimport) HRESULT __stdcall SetProcessDpiAwareness(PROCESS_DPI_AWARENESS value);

__declspec(dllimport) BOOL __stdcall SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT value);

__declspec(dllimport) HRESULT __stdcall GetDpiForMonitor( HMONITOR hmonitor, MONITOR_DPI_TYPE dpiType, UINT *dpiX, UINT *dpiY);


unit_local void _win_lazy_enable_dpi_awarness(void) {
    local_persist bool enabled = false;
    if (!enabled) {
        enabled = true;
        BOOL ok = SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
		if (!ok) {
			SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
		}
    }
}


unit_local LRESULT window_proc ( HWND hwnd,  u32 message,  WPARAM wparam,  LPARAM lparam) {

    _Surface_State *state = _get_surface_state(hwnd);
    if (!state) return DefWindowProcW(hwnd, message, wparam, lparam);

    switch (message) {
        case WM_QUIT:
        case WM_CLOSE:
            state->should_close = true;
            break;
        case WM_SIZE:
            state->pixels = 0;
            if (state->bmp) DeleteObject(state->bmp);
            break;
        default: {
            return DefWindowProcW(hwnd, message, wparam, lparam);
        }
    }

    return 0;
}

#endif // !OSTD_HEADLESS


void *sys_map_pages(u64 action, void *virtual_base, u64 number_of_pages, bool strict_base_address) {
    (void)strict_base_address;
    // todo(charlie) attempt multiple times in case of failure.

    System_Info info = sys_get_info();

    u64 amount_in_bytes = info.page_size * number_of_pages;

    u32 flags = 0;
    u32 protection = 0;

    if (action & SYS_MEMORY_RESERVE)  {
        flags |= MEM_RESERVE;
        protection = PAGE_NOACCESS;
    }
    if (action & SYS_MEMORY_ALLOCATE) {
        flags |= MEM_COMMIT;
        protection = PAGE_READWRITE;
    }

    void *result = VirtualAlloc(virtual_base, amount_in_bytes, flags, protection);
    // todo(charlie)
    // Some error reporting so user can see what went wrong if !result

    return result;
}



bool sys_unmap_pages(void *address) {
    // todo(charlie) attempt multiple times in case of failure.
    return VirtualFree(address, 0, MEM_RELEASE) != 0;
}

bool sys_deallocate_pages(void *address, u64 number_of_pages) {
    System_Info info = sys_get_info();

    u64 amount_in_bytes = info.page_size*number_of_pages;

    return VirtualFree(address, amount_in_bytes, MEM_DECOMMIT) != 0;
}

u64 sys_query_mapped_regions(void *start, void *end, Mapped_Memory_Info *result, u64 result_count) {
    System_Info info = sys_get_info();

    start = (void*)(((u64)start + info.page_size-1) & ~(info.page_size-1));

    void *p = start;
    u64 counter = 0;

    void *current_base = 0;

    MEMORY_BASIC_INFORMATION last_info;
    bool trailing_pointer = false;
    while ((u64)p < (u64)end) {

        MEMORY_BASIC_INFORMATION mem_info = (MEMORY_BASIC_INFORMATION){0};

        size_t r = VirtualQuery(p, &mem_info, sizeof(MEMORY_BASIC_INFORMATION));
        // todo(charlie)  VirtualQuery might fail for random reasons
        if (r != 0 && mem_info.AllocationBase) {
            if (current_base && (u64)current_base < (u64)mem_info.AllocationBase) {

                if (result && result_count > counter) {
                    Mapped_Memory_Info m = (Mapped_Memory_Info){0};
                    m.base = current_base;
                    m.page_count = (u64)last_info.RegionSize / info.page_size;
                    result[counter] = m;
                    trailing_pointer = false;
                }

                counter += 1;

            }
            current_base = mem_info.AllocationBase;
        }

        if (r != 0) {
            p = (u8*)p + mem_info.RegionSize;
            if (mem_info.AllocationBase) {
                last_info = mem_info;
                trailing_pointer = true;
            }
        }
    }

    if (trailing_pointer) {
        // todo(charlie) multiple attempts
        if (result_count > counter) {
            Mapped_Memory_Info m = (Mapped_Memory_Info){0};
            m.base = current_base;
            m.page_count = (u64)last_info.RegionSize / info.page_size;
            result[counter] = m;
        }
        counter += 1;
    }

    return counter;
}

void *sys_find_mappable_range(u64 page_count) {

    System_Info info = sys_get_info();

    u64 amount_in_bytes = page_count*info.page_size;

    MEMORY_BASIC_INFORMATION mbi;
    void *address = (void *)0x0000100000000000; // Start at a high user-space address
    while (address) {
        size_t query_size = VirtualQuery(address, &mbi, sizeof(mbi));
        if (query_size == 0) {
            return 0;
        }

        if (mbi.State == 0x10000 /*MEM_FREE*/ && mbi.RegionSize >= amount_in_bytes) {
            // Align the base address to the granularity
            u64 aligned_base = ((u64)mbi.BaseAddress + info.granularity - 1) & ~(info.granularity - 1);
            if (aligned_base + amount_in_bytes <= (u64)mbi.BaseAddress + mbi.RegionSize) {
                return (void *)aligned_base;
            }
        }

        address = (void *)((u64)mbi.BaseAddress + mbi.RegionSize);
    }

    return 0;
}

System_Info sys_get_info(void) {
    local_persist System_Info info;
    local_persist bool has_retrieved_info = false;

    if (!has_retrieved_info) {
        has_retrieved_info = true;

        SYSTEM_INFO win32_info;
        GetSystemInfo(&win32_info);

        info.page_size = (u64)win32_info.dwPageSize;
        info.granularity = win32_info.dwAllocationGranularity;
        info.logical_cpu_count = (u64)win32_info.dwNumberOfProcessors;
    }

    return info;
}

#ifndef OSTD_HEADLESS

typedef struct MonitorContext {
    Physical_Monitor *buffer;
    u64 max_count;
    u64 count;
} MonitorContext;

unit_local int __wcscmp(const u16 *s1, const u16 *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (int)(*s1) - (int)(*s2);
}
unit_local BOOL WINAPI _win_query_monitors_callback(HMONITOR monitor_handle, HDC dc, RECT *rect, LPARAM param) {
    (void)dc; (void)rect;
    MonitorContext *ctx = (MonitorContext*)param;
    if(ctx->buffer && ctx->count >= ctx->max_count) return false;
    MONITORINFOEXW info;
    info.cbSize = sizeof(MONITORINFOEXW);
    if(!GetMonitorInfoW(monitor_handle, (LPMONITORINFO)&info)) return true;
    DEVMODEW more_info;
    more_info.dmSize = sizeof(DEVMODEW);
    if(!EnumDisplaySettingsW(info.szDevice, ENUM_CURRENT_SETTINGS, &more_info)) return true;
    DISPLAY_DEVICEW even_more_info;
    even_more_info.cb = sizeof(DISPLAY_DEVICEW);
    int i = 0;
    BOOL found = false;
    while(EnumDisplayDevicesW(0, (DWORD)i, &even_more_info, 0)) {
        if(__wcscmp(even_more_info.DeviceName, info.szDevice) == 0){
            found = true;
            break;
        }
        i++;
    }
    if(!found) return true;
    if(ctx->buffer){
        Physical_Monitor *monitor = &ctx->buffer[ctx->count];
        monitor->name_count = (u64)WideCharToMultiByte(CP_UTF8, 0, even_more_info.DeviceString, -1, (LPSTR)monitor->name, 256, 0, 0);
        monitor->refresh_rate = more_info.dmDisplayFrequency;
        monitor->resolution_x = info.rcMonitor.right - info.rcMonitor.left;
        monitor->resolution_y = info.rcMonitor.bottom - info.rcMonitor.top;
        monitor->pos_x = info.rcMonitor.left;
        monitor->pos_y = info.rcMonitor.top;
        UINT dpix, dpiy;
        GetDpiForMonitor(monitor_handle, MDT_EFFECTIVE_DPI, &dpix, &dpiy);
        monitor->scale = (float64)dpix/96.0;
        monitor->handle = monitor_handle;
    }
    ctx->count++;
    return true;
}

u64 sys_query_monitors(Physical_Monitor *buffer, u64 max_count) {
    _win_lazy_enable_dpi_awarness();
    MonitorContext ctx;
    ctx.buffer = buffer;
    ctx.max_count = max_count;
    ctx.count = 0;
    EnumDisplayMonitors(0, 0, _win_query_monitors_callback, (LPARAM)&ctx);
    return ctx.count;
}

unit_local IDXGIOutput* _win_get_output_for_monitor(HMONITOR hMonitor)
{
    IDXGIFactory* factory = 0;
    if (CreateDXGIFactory(&IID_IDXGIFactory, (void**)&factory) != 0)
    {
        return 0;
    }

    IDXGIAdapter* adapter = 0;
    IDXGIOutput* output = 0;

    for (UINT i = 0; factory->lpVtbl->EnumAdapters(factory, i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
    {
        for (UINT j = 0; adapter->lpVtbl->EnumOutputs(adapter, j, &output) != DXGI_ERROR_NOT_FOUND; ++j)
        {
            DXGI_OUTPUT_DESC desc;
            output->lpVtbl->GetDesc(output, &desc);

            if (desc.Monitor == hMonitor)
            {
                adapter->lpVtbl->parent.Release(adapter);
                factory->lpVtbl->parent.Release(factory);
                return output;
            }

            output->lpVtbl->parent.Release(output);
        }
        adapter->lpVtbl->parent.Release(adapter);
    }

    factory->lpVtbl->parent.Release(factory);
    return 0;
}
bool sys_wait_vertical_blank(Physical_Monitor monitor) {
    IDXGIOutput *output = _win_get_output_for_monitor(monitor.handle);

    if (output) {
        output->lpVtbl->WaitForVBlank(output);
        return true;
    }
    return false;
}

#endif // !OSTD_HEADLESS

File_Handle sys_get_stdout(void) {
    return (File_Handle)GetStdHandle((u32)-11);
}
File_Handle sys_get_stderr(void) {
    return (File_Handle)GetStdHandle((u32)-12);
}

bool sys_make_pipe(File_Handle *read, File_Handle *write) {
    HANDLE read_handle, write_handle;
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), 0, true};
    if (!CreatePipe(&read_handle, &write_handle, &sa, 0)) return false;
    *read = (File_Handle)read_handle;
    *write = (File_Handle)write_handle;
    return true;
}

s64 sys_write(File_Handle f, void *data, u64 size) {
    u32 written = 0;
    WriteFile(f, data, (DWORD)size, (unsigned long*)&written, 0);
    return (s64)written;
}

s64 sys_write_string(File_Handle f, string s) {
    return sys_write(f, s.data, s.count);
}

s64 sys_read(File_Handle h, void *buffer, u64 buffer_size) {
    DWORD read = 0;
    ReadFile(h, (LPVOID)buffer, (DWORD)buffer_size, &read, 0);

    return (s64)read;
}

void sys_close(File_Handle h) {
    CloseHandle((HANDLE)h);
}

File_Handle sys_open_file(string path, File_Open_Flags flags) {
    u16 cpath[MAX_PATH_LENGTH*2];
    _win_utf8_to_wide(path, cpath, MAX_PATH_LENGTH*2);

    DWORD access_mode = 0;
    DWORD creation_flags = 0;

    if (flags & FILE_OPEN_WRITE) {
        access_mode |= FILE_GENERIC_WRITE;
    }
    
    if (flags & FILE_OPEN_READ) {
        access_mode |= FILE_GENERIC_READ;
    }

    if (flags & FILE_OPEN_RESET) {
        creation_flags = CREATE_ALWAYS;
    } else if (flags & FILE_OPEN_CREATE) {
        creation_flags = OPEN_ALWAYS;
    } else {
        creation_flags = OPEN_EXISTING;
    }

    SECURITY_ATTRIBUTES attr = (SECURITY_ATTRIBUTES){0};
    attr.nLength = sizeof(SECURITY_ATTRIBUTES);
    attr.bInheritHandle = 1;

    HANDLE handle = CreateFileW(
        cpath,
        access_mode,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        &attr,
        creation_flags,
        FILE_ATTRIBUTE_NORMAL,
        0
    );

    if (handle == INVALID_HANDLE_VALUE) {
        return 0;
    }

    return handle;
}

u64 sys_get_file_size(File_Handle f) {
    LARGE_INTEGER size;
    if (!GetFileSizeEx(f, &size)) {
        return 0; // Indicate failure
    }
    return (u64)size.QuadPart;
}

bool sys_set_file_position(File_Handle f, u64 position) {
    LARGE_INTEGER li;
    li.QuadPart = (LONGLONG)position;
    return SetFilePointerEx((HANDLE)f, li, 0, 0) != 0;
}

bool sys_make_directory(string path, bool recursive) {
    u16 path_wide[2048];
    u64 path_len = _win_utf8_to_wide(path, path_wide, 2048);
    if (path_len == 0) {
        return false;
    }

    if (!recursive) {
        if (CreateDirectoryW(path_wide, 0) || GetLastError() == 0xB7 /* ERROR_ALREADY_EXISTS */) {
            return true;
        }
        return false;
    }

    u16 buffer[1024];
    if (path.count >= sizeof(buffer))
        return false;

    memcpy(buffer, path_wide, path.count*sizeof(u16));
    buffer[path.count] = '\0';

    for (size_t i = 0; i < path.count; i++) {
        if (buffer[i] == '\\' || buffer[i] == '/') {
            if (i == 0 || (i == 2 && buffer[1] == ':'))
                continue;

            u16 saved = buffer[i];
            buffer[i] = '\0';
            if (!CreateDirectoryW(buffer, 0) && GetLastError() != 0xB7 /* ERROR_ALREADY_EXISTS */) {
                return false;
            }
            buffer[i] = saved;
        }
    }

    if (!CreateDirectoryW(buffer, 0) && GetLastError() != 0xB7 /* ERROR_ALREADY_EXISTS */) {
        return false;
    }
    return true;
}

bool sys_remove_directory(string path, bool recursive) {
    u16 path_wide[2048];
    u64 path_len = _win_utf8_to_wide(path, path_wide, 2048);
    if (path_len == 0) {
        return false;
    }

    if (!recursive) {
        return (RemoveDirectoryW((LPCWSTR)path_wide) != 0);
    }

    bool has_slash = false;
    if (path.count > 0) {
        char last = ((char*)path.data)[path.count - 1];
        if (last == '\\' || last == '/') {
            has_slash = true;
        }
    }
    u16 search_pattern[2048];
    u64 pos = 0;
    for (u64 i = 0; i < path_len; i++) {
        search_pattern[pos++] = path_wide[i];
    }
    if (!has_slash) {
        search_pattern[pos++] = '\\';
    }
    search_pattern[pos++] = '*';
    search_pattern[pos] = 0;

    WIN32_FIND_DATAW findData;
    HANDLE hFind = FindFirstFileW((LPCWSTR)search_pattern, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return false;
    }

    do {
        if (_wide_strcmp(findData.cFileName, L".") == 0 ||
            _wide_strcmp(findData.cFileName, L"..") == 0) {
            continue;
        }

        u16 entry_path[2048];
        u64 new_pos = 0;
        for (u64 i = 0; i < path_len; i++) {
            entry_path[new_pos++] = path_wide[i];
        }
        if (!has_slash) {
            entry_path[new_pos++] = '\\';
        }
        u64 entry_name_len = _wide_strlen(findData.cFileName);
        for (u64 i = 0; i < entry_name_len; i++) {
            entry_path[new_pos++] = findData.cFileName[i];
        }
        entry_path[new_pos] = 0;

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            u8 entry_utf8[2048];
            string entry_str;
            entry_str.data = entry_utf8;
            entry_str.count = _wide_strlen(entry_path);
            _win_wide_to_utf8(entry_path, &entry_str);
            if (!sys_remove_directory(entry_str, true)) {
                FindClose(hFind);
                return false;
            }
        } else {
            if (!DeleteFileW((LPCWSTR)entry_path)) {
                FindClose(hFind);
                return false;
            }
        }
    } while (FindNextFileW(hFind, &findData));

    FindClose(hFind);

    return (RemoveDirectoryW((LPCWSTR)path_wide) != 0);
}

bool sys_is_file(string path) {
    u16 path_wide[2048];
    u64 path_len = _win_utf8_to_wide(path, path_wide, 2048);
    if (path_len == 0) {
        return false;
    }
    DWORD attr = GetFileAttributesW((LPCWSTR)path_wide);
    if (attr == 0xFFFFFFFF)
        return false;
    return ((attr & FILE_ATTRIBUTE_DIRECTORY) == 0);
}

bool sys_is_directory(string path) {
    u16 path_wide[2048];
    u64 path_len = _win_utf8_to_wide(path, path_wide, 2048);
    if (path_len == 0) {
        return false;
    }
    DWORD attr = GetFileAttributesW((LPCWSTR)path_wide);
    if (attr == 0xFFFFFFFF)
        return false;
    return ((attr & FILE_ATTRIBUTE_DIRECTORY) != 0);
}



void sys_walk_directory(string path, bool recursive, bool walk_directories, Walk_Proc walk_proc) {
    bool has_slash = false;
    if (path.count > 0) {
        char last = ((char*)path.data)[path.count - 1];
        if (last == '\\' || last == '/') {
            has_slash = true;
        }
    }

    static u16 path_wide[2048];
    u64 path_len = _win_utf8_to_wide(path, path_wide, 2048);

    static u16 search_pattern[2048];
    u64 pos = 0;
    for (u64 i = 0; i < path_len; i++) {
        search_pattern[pos++] = path_wide[i];
    }
    if (!has_slash) {
        search_pattern[pos++] = '\\';
    }
    search_pattern[pos++] = '*';
    search_pattern[pos] = 0;

    WIN32_FIND_DATAW findData;
    HANDLE hFind = FindFirstFileW((LPCWSTR)search_pattern, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        if (_wide_strcmp(findData.cFileName, L".") == 0 ||
            _wide_strcmp(findData.cFileName, L"..") == 0) {
            continue;
        }

        u64 entry_name_len = _wide_strlen(findData.cFileName);
        u64 new_path_len = path.count + (has_slash ? 0 : 1) + entry_name_len;
        u16 new_path_wide[2048];
        u64 new_pos = 0;
        for (u64 i = 0; i < path.count; i++) {
            new_path_wide[new_pos++] = path_wide[i];
        }
        if (!has_slash) {
            new_path_wide[new_pos++] = '\\';
        }
        for (u64 i = 0; i < entry_name_len; i++) {
            new_path_wide[new_pos++] = findData.cFileName[i];
            //sys_write_string(sys_get_stdout(), (string){1, (u8*)&findData.cFileName[i]});
        }
        new_path_wide[new_pos++] = 0;

        static u8 new_path[2048];

        string entry_str;
        entry_str.count = new_path_len;
        entry_str.data = new_path;

        _win_wide_to_utf8(new_path_wide, &entry_str);


        bool is_dir = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

        if (is_dir) {
            if (walk_directories) {
                if (!walk_proc(entry_str)) {
                    FindClose(hFind);
                    return;
                }
            }
            if (recursive) {
                sys_walk_directory(entry_str, recursive, walk_directories, walk_proc);
            }
        } else {
            if (!walk_proc(entry_str)) {
                FindClose(hFind);
                return;
            }
        }

    } while (FindNextFileW(hFind, &findData));

    FindClose(hFind);
}

Easy_Command_Result sys_run_command_easy(string command_line, File_Handle stdout, File_Handle stderr, string workspace_dir, bool wait_for_exit) {
    Easy_Command_Result res = (Easy_Command_Result){0};

    STARTUPINFOA si = {0};
    si.cb = sizeof(STARTUPINFOA);
    si.dwFlags |= 0x00000100; /*STARTF_USESTDHANDLES */
    si.hStdOutput = stdout;
    si.hStdError = stderr;

    PROCESS_INFORMATION pi = (PROCESS_INFORMATION){ 0 };

    char cmd[1024];

    memcpy(cmd, command_line.data, command_line.count);
    cmd[command_line.count] = 0;

    char wks[1024];
    memcpy(wks, workspace_dir.data, workspace_dir.count);
    wks[workspace_dir.count] = 0;

    bool ok = (bool)(int)CreateProcessA(0, cmd, 0, 0, true, 0, 0, wks, &si, &pi);

    if (!ok) {
        res.process_start_success = false;
        return res;
    }
    
    if (wait_for_exit) {
        WaitForSingleObject(pi.hProcess, S32_MAX);
    
        DWORD exit_code;
        GetExitCodeProcess(pi.hProcess, &exit_code);
    
        res.exit_code = (s64)exit_code;
        res.process_start_success = true;
    }

    return res;
}

OSTD_LIB void sys_exit(s64 code) {
    ExitProcess((UINT)code);
}

OSTD_LIB void sys_exit_current_thread(s64 code) {
    ExitThread((DWORD)code);
}

inline unit_local int _to_winsock_err(Socket_Result r) {
    switch(r) {
        case SOCKET_OK: return 0;
        case SOCKET_DISCONNECTED: return WSAECONNRESET;
        case SOCKET_NOT_INITIALIZED: return WSANOTINITIALISED;
        case SOCKET_NOACCESS: return WSAEACCES;
        case SOCKET_IN_PROGRESS: return WSAEWOULDBLOCK;
        case SOCKET_NOT_A_SOCKET: return WSAENOTSOCK;
        case SOCKET_INVALID_ADDRESS: return WSAEFAULT;
        case SOCKET_TIMED_OUT: return WSAETIMEDOUT;
        case SOCKET_CONNECTION_REFUSED: return WSAECONNREFUSED;
        case SOCKET_CONNECTION_RESET: return WSAECONNRESET;
        case SOCKET_ALREADY_CONNECTED: return WSAEISCONN;
        case SOCKET_ADDRESS_IN_USE: return WSAEADDRINUSE;
        case SOCKET_NETWORK_UNREACHABLE: return WSAENETUNREACH;
        case SOCKET_HOST_UNREACHABLE: return WSAEHOSTUNREACH;
        case SOCKET_PROTOCOL_ERROR: return WSAEPROTONOSUPPORT;
        default: return -1;
    }
}


static Socket_Result _ensure_winsock_initialized(void) {
    static bool winsock_initialized = false;
    if (!winsock_initialized) {
        WSADATA wsaData;
        int result = WSAStartup(2 | (2 << 8), &wsaData);
        if (result != 0) {
            return SOCKET_NOT_INITIALIZED;
        }
        winsock_initialized = true;
    }
    return SOCKET_OK;
}

unit_local int _to_win_sock_err(Socket_Result r) {
    switch(r) {
        case SOCKET_OK: return 0;
        case SOCKET_DISCONNECTED: return WSAECONNRESET;
        case SOCKET_NOT_INITIALIZED: return WSANOTINITIALISED;
        case SOCKET_NOACCESS: return WSAEACCES;
        case SOCKET_IN_PROGRESS: return WSAEWOULDBLOCK;
        case SOCKET_NOT_A_SOCKET: return WSAENOTSOCK;
        case SOCKET_INVALID_ADDRESS: return WSAEFAULT;
        case SOCKET_TIMED_OUT: return WSAETIMEDOUT;
        case SOCKET_CONNECTION_REFUSED: return WSAECONNREFUSED;
        case SOCKET_CONNECTION_RESET: return WSAECONNRESET;
        case SOCKET_ALREADY_CONNECTED: return WSAEISCONN;
        case SOCKET_ADDRESS_IN_USE: return WSAEADDRINUSE;
        case SOCKET_NETWORK_UNREACHABLE: return WSAENETUNREACH;
        case SOCKET_HOST_UNREACHABLE: return WSAEHOSTUNREACH;
        case SOCKET_PROTOCOL_ERROR: return WSAEPROTONOSUPPORT;
        default: return -1;
    }
}

u32 sys_convert_address_string(string address) {
    assert(address.count < 1024);
    char addr_str[1024] = {0};
    memcpy(addr_str, address.data, address.count);
    addr_str[address.count] = '\0';
    return inet_addr(addr_str);
}

Socket_Result sys_socket_init(Socket *s, Socket_Domain domain, Socket_Type type, Socket_Protocol protocol) {
    Socket_Result init_res = _ensure_winsock_initialized();
    if (init_res != SOCKET_OK)
        return init_res;

    int af = 0;
    switch (domain) {
        case SOCKET_DOMAIN_IPV4:
            af = AF_INET;
            break;
        case SOCKET_DOMAIN_BLUETOOTH:
            // todo(charlie)
            return SOCKET_INVALID_ADDRESS;
        case SOCKET_DOMAIN_APPLETALK:
            return SOCKET_INVALID_ADDRESS;
#if OS_FLAGS & OS_FLAG_UNIX
        case SOCKET_DOMAIN_UNIX:
            return SOCKET_INVALID_ADDRESS;
#endif
        default:
            return SOCKET_PROTOCOL_ERROR;
    }

    int sock_type = 0;
    switch (type) {
        case SOCKET_TYPE_STREAM:
            sock_type = SOCK_STREAM;
            break;
        case SOCKET_TYPE_DGRAM:
            sock_type = SOCK_DGRAM;
            break;
        case SOCKET_TYPE_RAW:
            sock_type = SOCK_RAW;
            break;
        case SOCKET_TYPE_RDM:
            sock_type = SOCK_RDM;
            break;
        case SOCKET_TYPE_SEQPACKET:
            sock_type = SOCK_SEQPACKET;
            break;
        default:
            return SOCKET_PROTOCOL_ERROR;
    }

    int proto = 0;
    switch (protocol) {
        case SOCKET_PROTOCOL_TCP:
            proto = IPPROTO_TCP;
            break;
        case SOCKET_PROTOCOL_UDP:
            proto = IPPROTO_UDP;
            break;
        default:
            return SOCKET_PROTOCOL_ERROR;
    }

    SOCKET win_sock = socket(af, sock_type, proto);
    if (win_sock == INVALID_SOCKET) {
        return SOCKET_PROTOCOL_ERROR;
    }

    int optval = 1;
    setsockopt(win_sock, SOL_SOCKET, SO_REUSEADDR,  (const char *)&optval, sizeof(optval));

    *s = (Socket)win_sock;
    return SOCKET_OK;
}

Socket_Result sys_socket_bind(Socket sock, u32 address, u16 port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl((u16)address);
    int result = bind((SOCKET)sock, (struct sockaddr*)&addr, sizeof(addr));
    if (result == SOCKET_ERROR) {
        int err = WSAGetLastError();
        switch(err) {
            case WSAEADDRINUSE: return SOCKET_ADDRESS_IN_USE;
            case WSAEACCES:   return SOCKET_NOACCESS;
            default:         return SOCKET_PROTOCOL_ERROR;
        }
    }
    return SOCKET_OK;
}

Socket_Result sys_socket_listen(Socket sock, s64 backlog) {
    int result = listen((SOCKET)sock, (int)backlog);
    if (result == SOCKET_ERROR) {
        return SOCKET_PROTOCOL_ERROR;
    }
    return SOCKET_OK;
}

Socket_Result sys_socket_accept(Socket sock, Socket *accepted, u64 timeout_ms) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);

    struct timeval tv;
    tv.tv_sec  = (long)(timeout_ms / 1000);
    tv.tv_usec = (long)((timeout_ms % 1000) * 1000);

    int select_result = select(0, &readfds, 0, 0, &tv);
    if (select_result == 0) {
        return SOCKET_TIMED_OUT;
    }
    if (select_result == SOCKET_ERROR) {
        return SOCKET_PROTOCOL_ERROR;
    }

    struct sockaddr_in addr;
    int addr_len = sizeof(addr);
    SOCKET client = accept((SOCKET)sock, (struct sockaddr*)&addr, &addr_len);
    if (client == INVALID_SOCKET) {
        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK)
            return SOCKET_IN_PROGRESS;
        return SOCKET_PROTOCOL_ERROR;
    }
    *accepted = (Socket)client;
    return SOCKET_OK;
}

Socket_Result sys_socket_send(Socket sock, void *data, u64 length, u64 *sent) {
    int result = send((SOCKET)sock, (const char*)data, (int)length, 0);
    if (result == SOCKET_ERROR) {
        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK) {
            if (sent)
                *sent = 0;
            return SOCKET_IN_PROGRESS;
        }
        if (err == WSAETIMEDOUT)
            return SOCKET_TIMED_OUT;
        return SOCKET_PROTOCOL_ERROR;
    }
    if (sent)
        *sent = result > 0 ? (u64)result : 0;
    return SOCKET_OK;
}

Socket_Result sys_socket_recv(Socket sock, void *buffer, u64 length, u64 *received) {
    int result = recv((SOCKET)sock, (char*)buffer, (int)length, 0);
    if (result == SOCKET_ERROR) {
        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK) {
            if (received)
                *received = 0;
            return SOCKET_IN_PROGRESS;
        }
        if (err == WSAETIMEDOUT)
            return SOCKET_TIMED_OUT;
        return SOCKET_PROTOCOL_ERROR;
    } else if (result == 0) {
        if (received)
            *received = 0;
        return SOCKET_DISCONNECTED;
    }
    if (received)
        *received = result > 0 ? (u64)result : 0;
    return SOCKET_OK;
}

Socket_Result sys_socket_close(Socket sock) {
    int result = closesocket((SOCKET)sock);
    if (result == SOCKET_ERROR)
        return SOCKET_PROTOCOL_ERROR;
    return SOCKET_OK;
}

Socket_Result sys_socket_set_blocking(Socket *sock, bool blocking) {
    unsigned long mode = blocking ? 0 : 1;
    int result = ioctlsocket((SOCKET)(*sock), (long)FIONBIO, &mode);
    if (result != NO_ERROR)
        return SOCKET_PROTOCOL_ERROR;
    return SOCKET_OK;
}
Socket_Result sys_set_socket_blocking_timeout(Socket socket, u64 ms) {
    setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&ms, sizeof(ms));
    setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&ms, sizeof(ms));
    return SOCKET_OK;
}

u64 sys_get_current_thread_id(void) {
    return (u64)GetCurrentThreadId();
}

bool sys_thread_key_init(Thread_Key *key) {
    *key = (Thread_Key)(u64)TlsAlloc();
    return (u64)*key != 0xFFFFFFFF;
}
bool sys_thread_key_write(Thread_Key key, void* value) {
    return (bool)(int)TlsSetValue((DWORD)(u64)key, value);
}
void* sys_thread_key_read(Thread_Key key) {
    return TlsGetValue((DWORD)(u64)key);
}

unit_local DWORD WINAPI _windows_thread_proc(LPVOID lpParameter) {
    Thread *t = (Thread*)lpParameter;

    _ostd_register_thread_storage(t->id);

    DWORD ret = (DWORD)t->proc(t);

    _ostd_get_thread_storage()->taken = false;

    return ret;
}

bool sys_thread_init(Thread *thread, Thread_Proc proc, void *userdata) {
    thread->userdata = userdata;
    thread->id = 0;
    thread->handle = CreateThread(0, 0, _windows_thread_proc, thread, 0x00000004, (LPDWORD)&thread->id);
    thread->is_suspended = true;
    thread->proc = proc;
    return thread->handle != 0;
}
bool sys_thread_start(Thread *thread) {
    (void)_ostd_get_thread_storage();
    thread->is_suspended = false;
    return ResumeThread(thread->handle) != (DWORD)-1;
}
s64 sys_thread_join(Thread *thread) {
    assert(!thread->is_suspended);
    WaitForSingleObject(thread->handle, 0xFFFFFFFF);
    
    DWORD exit_code = 0;
    GetExitCodeThread(thread->handle, &exit_code);
    return (s64)exit_code;
}
void sys_thread_close(Thread *thread) {
    CloseHandle(thread->handle);
}

bool sys_mutex_init(Mutex *mutex) {
    if (!mutex) return false;
    mutex->handle = mutex->handle_backing;
    InitializeCriticalSection(mutex->handle);
    return true;
}

bool sys_mutex_uninit(Mutex *mutex) {
    if (!mutex || !mutex->handle) return false;
    DeleteCriticalSection(mutex->handle);
    mutex->handle = 0;
    return true;
}

void sys_mutex_acquire(Mutex mutex) {
    EnterCriticalSection(mutex.handle);
}

void sys_mutex_release(Mutex mutex) {
    LeaveCriticalSection(mutex.handle);
}

OSTD_LIB bool sys_semaphore_init(Semaphore *sem) {
    sem->handle = CreateSemaphoreA(0, 0, S32_MAX, 0);
    return sem->handle != 0;
}

OSTD_LIB void sys_semaphore_signal(Semaphore *sem) {
    ReleaseSemaphore(sem->handle, 1, 0);
}

OSTD_LIB void sys_semaphore_wait(Semaphore *sem) {
    WaitForSingleObject((HANDLE)sem->handle, 0xFFFFFFFF);
}

OSTD_LIB void sys_semaphore_uninit(Semaphore *sem) {
    CloseHandle((HANDLE)sem->handle);
}

inline unit_local u32 sys_atomic_add_32(volatile u32 *addend, u32 value) {
    return (u32)_InterlockedExchangeAdd((volatile long*)addend, (long)value);
}
inline unit_local u64 sys_atomic_add_64(volatile u64 *addend, u64 value) {
    long long old;

    do {
        old = (long long)*addend;
    } while (_InterlockedCompareExchange64((volatile long long*)addend, old + (long long)value, (long long)old) != (long long)old);

    return (u64)old;
}

#ifndef OSTD_HEADLESS

Surface_Handle sys_make_surface(Surface_Desc desc) {
    _Surface_State *s = _alloc_surface_state();
    if (!s) {
        // todo(charlie) sys_error
        return 0;
    }

    HINSTANCE instance = GetModuleHandleW(0);

    local_persist bool class_initted = false;
    if (!class_initted) {
        class_initted = true;
        WNDCLASSEXW wc = (WNDCLASSEXW){0};
        wc.cbSize = sizeof(WNDCLASSEXW);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = window_proc;
        wc.hInstance = instance;
        wc.lpszClassName = L"abc123";
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hCursor = 0;
        wc.hIcon = 0;
        wc.lpszMenuName = 0;
        wc.hbrBackground = 0;

    	ATOM res = RegisterClassExW(&wc);
    	assert(res);
    }

	RECT rect = (RECT){0, 0, (LONG)desc.width, (LONG)desc.height};


	DWORD style = WS_OVERLAPPEDWINDOW;
	DWORD style_ex = WS_EX_CLIENTEDGE;

	AdjustWindowRectEx(&rect, style, 0, style_ex);

	u16 title[256];
	u64 title_length = _win_utf8_to_wide(desc.title, title, 256);
	title[title_length] = 0;

    // Create the window
    HWND hwnd = CreateWindowExW(
        style_ex,
        L"abc123",
        title,
        style,
        CW_USEDEFAULT, CW_USEDEFAULT, rect.right-rect.left, rect.bottom-rect.top,
        0, 0, instance, 0
    );

    if (!hwnd) return 0;

    s->handle = hwnd;

    UpdateWindow(hwnd);

    surface_unset_flags(hwnd, ~desc.flags);
    surface_set_flags(hwnd, desc.flags);



    return hwnd;
}
void surface_close(Surface_Handle s) {
    _Surface_State *state = _get_surface_state(s);
    if (!state) return; // todo(charlie) sys_error

    DestroyWindow((HWND)s);
    state->allocated = false;
    state->handle = 0;
}


void surface_poll_events(Surface_Handle surface) {
    MSG msg;
    BOOL result = PeekMessageW(&msg, (HWND)surface, 0, 0, PM_REMOVE);
	while (result) {
    	TranslateMessage(&msg);
    	DispatchMessageW(&msg);
    	result = PeekMessageW(&msg, (HWND)surface, 0, 0, PM_REMOVE);
    }
}

bool surface_should_close(Surface_Handle s) {
    _Surface_State *state = _get_surface_state(s);
    if (!state) return true;
    return state->should_close;
}

bool surface_set_flags(Surface_Handle h, Surface_Flags flags) {
    int ex_style = GetWindowLongW((HWND)h, GWL_EXSTYLE);
    int style = GetWindowLongW((HWND)h, GWL_STYLE);

    if (flags & SURFACE_FLAG_HIDDEN) {
        ex_style |= WS_EX_TOOLWINDOW;
    }

    if (flags & SURFACE_FLAG_TOPMOST) {
        ex_style |= WS_EX_TOPMOST;
    }

    SetWindowLongW((HWND)h, GWL_EXSTYLE, ex_style);
    SetWindowLongW((HWND)h, GWL_STYLE, style);

    if (flags & SURFACE_FLAG_HIDDEN) {
        ShowWindow((HWND)h, SW_HIDE);
    }

    if (flags & SURFACE_FLAG_TOPMOST) {
        SetWindowPos((HWND)h, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOREPOSITION | SWP_NOSIZE | SWP_NOMOVE);
    }

    return true;
}
bool surface_unset_flags(Surface_Handle h, Surface_Flags flags) {
    int ex_style = GetWindowLongW((HWND)h, GWL_EXSTYLE);
    int style = GetWindowLongW((HWND)h, GWL_STYLE);

    if (flags & SURFACE_FLAG_HIDDEN) {
        ex_style &= ~(WS_EX_TOOLWINDOW);
    }

    if (flags & SURFACE_FLAG_TOPMOST) {
        ex_style &= ~(WS_EX_TOPMOST);
    }

    SetWindowLongW((HWND)h, GWL_EXSTYLE, ex_style);
    SetWindowLongW((HWND)h, GWL_STYLE, style);

    if (flags & SURFACE_FLAG_HIDDEN) {
        ShowWindow((HWND)h, SW_SHOW);
    }
    if (flags & SURFACE_FLAG_TOPMOST) {
        SetWindowPos((HWND)h, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOREPOSITION | SWP_NOSIZE | SWP_NOMOVE);
    }
    return true;
}

bool surface_get_framebuffer_size(Surface_Handle h, s64 *width, s64 *height) {
    RECT r;
    if (GetClientRect((HWND)h, &r)) {
        *width = r.right - r.left;
        *height = r.bottom - r.top;
        return true;
    } else {
        return false;
    }
}

void* surface_map_pixels(Surface_Handle h) {
    _Surface_State *state = _get_surface_state(h);
    if (!state) return 0;

    s64 width, height;
    if (!surface_get_framebuffer_size(h, &width, &height)) {
        return 0;
    }

    if (!state->pixels) {
        state->bmp_info.bmiHeader.biSize        = sizeof(state->bmp_info.bmiHeader);
        state->bmp_info.bmiHeader.biWidth       = (LONG)width;
        state->bmp_info.bmiHeader.biHeight      = (LONG)-height;
        state->bmp_info.bmiHeader.biPlanes      = 1;
        state->bmp_info.bmiHeader.biBitCount    = 32;
        state->bmp_info.bmiHeader.biCompression = BI_RGB;
        state->bmp_info.bmiHeader.biSizeImage   = 0;

        state->bmp = CreateDIBSection(GetDC((HWND)h), &state->bmp_info, DIB_RGB_COLORS, &state->pixels, 0, 0);
    }

    return state->pixels;
}
void surface_blit_pixels(Surface_Handle h) {
    _Surface_State *state = _get_surface_state(h);
    if (!state) return;

    s64 width, height;
    if (!surface_get_framebuffer_size(h, &width, &height)) return;

    HDC hdc = GetDC((HWND)h);

    StretchDIBits(
        hdc,
        0, 0, (LONG)width, (LONG)height,
        0, 0, (LONG)width, (LONG)height,
        state->pixels,
        &state->bmp_info,
        DIB_RGB_COLORS,
        SRCCOPY
    );
}

bool surface_get_monitor(Surface_Handle h, Physical_Monitor *monitor) {
    HMONITOR hmon = MonitorFromWindow((HWND)h, MONITOR_DEFAULTTONEAREST);
    if (!hmon) return false;

    Physical_Monitor mons[256];


    u64 count = sys_query_monitors(mons, 256);

    for (u64 i = 0; i < count; i += 1) {
        if (mons[i].handle == hmon) {
            *monitor = mons[i];
            return true;
        }
    }

    return false;
}

#endif // !OSTD_HEADLESS

float64 sys_get_seconds_monotonic(void) {
    LARGE_INTEGER freq, counter = (LARGE_INTEGER){0};
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&counter);
	float64 t = (float64)counter.QuadPart / (float64)freq.QuadPart;

	local_persist float64 start_time = 0.0;
	if (start_time == 0.0) {
	   start_time = t;
	}

	return t - start_time;
}

void sys_set_thread_affinity_mask(Thread_Handle thread, u64 bits) {
    SetThreadAffinityMask((HANDLE)thread, (DWORD_PTR)bits);
}

void sys_set_local_process_priority_level(Priority_Level level) {
    switch(level) {
        case SYS_PRIORITY_LOW:
            SetPriorityClass(GetCurrentProcess(), 0x00000040 /*IDLE_PRIORITY_CLASS*/);
            break;
        case SYS_PRIORITY_MEDIUM:
            SetPriorityClass(GetCurrentProcess(), 0x00000020 /*NORMAL_PRIORITY_CLASS*/);
            break;
        case SYS_PRIORITY_HIGH:
            SetPriorityClass(GetCurrentProcess(), 0x00000080 /*HIGH_PRIORITY_CLASS*/);
            break;

        default: break;
    }
}
void sys_set_thread_priority_level(Thread_Handle thread, Priority_Level level) {
    switch(level) {
        case SYS_PRIORITY_LOW:
            SetThreadPriority(thread, -2 /*THREAD_PRIORITY_LOWEST*/);
            break;
        case SYS_PRIORITY_MEDIUM:
            SetThreadPriority(thread, 0 /*THREAD_PRIORITY_NORMAL*/);
            break;
        case SYS_PRIORITY_HIGH:
            SetThreadPriority(thread, 15 /*THREAD_PRIORITY_TIME_CRITICAL*/);
            break;

        default: break;
    }
}

void *sys_load_library(string s) {
    char cs[1024];
    memcpy(cs, s.data, s.count);
    cs[s.count] = 0;
    return LoadLibraryA(cs);
}
void sys_close_library(void *lib) {
    (void)lib;
}
void* sys_get_library_symbol(void *lib, string symbol) {
    char cs[1024];
    memcpy(cs, symbol.data, symbol.count);
    cs[symbol.count] = 0;

    return GetProcAddress(lib, cs);
}

Thread_Handle sys_get_current_thread(void) {
    return (Thread_Handle)GetCurrentThread();
}

void sys_print_stack_trace(File_Handle handle) {

    void* process = GetCurrentProcess();
    void* thread = GetCurrentThread();

    SymInitialize(process, 0, 1);

    CONTEXT context;
    STACKFRAME64 stack = (STACKFRAME64) {0};

    context.ContextFlags = CONTEXT_FULL;
    RtlCaptureContext(&context);

    // #Portability cpu arch
    int machineType = IMAGE_FILE_MACHINE_AMD64;
    stack.AddrPC.Offset = context.Rip;
    stack.AddrPC.Mode = AddrModeFlat;
    stack.AddrFrame.Offset = context.Rsp;
    stack.AddrFrame.Mode = AddrModeFlat;
    stack.AddrStack.Offset = context.Rsp;
    stack.AddrStack.Mode = AddrModeFlat;

    #define WIN32_MAX_STACK_FRAMES 64
    #define WIN32_MAX_SYMBOL_NAME_LENGTH 512

    for (int i = 0; i < WIN32_MAX_STACK_FRAMES; i++) {
        if (!StackWalk64((DWORD)machineType, process, thread, &stack, &context, 0, SymFunctionTableAccess64, SymGetModuleBase64, 0)) {
            break;
        }

        DWORD64 displacement = 0;
        char buffer[sizeof(SYMBOL_INFO) + WIN32_MAX_SYMBOL_NAME_LENGTH];
        PSYMBOL_INFO symbol = (PSYMBOL_INFO)buffer;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = WIN32_MAX_SYMBOL_NAME_LENGTH;

        if (SymFromAddr(process, stack.AddrPC.Offset, &displacement, symbol)) {
            IMAGEHLP_LINE64 line;
            u32 displacement_line;
            line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);


            if (SymGetLineFromAddr64(process, stack.AddrPC.Offset, (PDWORD)&displacement_line, &line)) {
                sys_write_string(handle, STR(line.FileName));
                sys_write_string(handle, STR(" Line "));
                u8 sym_buffer[32];
                string line_str = (string){0, sym_buffer};
                line_str.count = format_signed_int(line.LineNumber, 10, sym_buffer, 32);
                sys_write_string(handle, line_str);
                sys_write_string(handle, STR(" "));
                sys_write_string(handle, STR(symbol->Name));
                sys_write_string(handle, STR("\n"));

            } else {
                u8 sym_buffer[1024];
                string result = (string) {0, sym_buffer};
                result.count = (u64)(symbol->NameLen + 1);
                memcpy(result.data, symbol->Name, symbol->NameLen + 1);
                sys_write_string(handle, result);
            }

        } else {
            sys_write_string(handle, STR("<unavailable>\n"));
        }
    }
}
#elif (OS_FLAGS & OS_FLAG_ANDROID)

/////////////////////////////////////////////////////
//////
// :Android
//////
/////////////////////////////////////////////////////

#include <android/log.h>
#include <android/configuration.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/native_activity.h>
#include <android/choreographer.h>
#undef bool

pthread_t _android_stdout_thread;
pthread_t _android_stderr_thread;
int _android_stdout_pipe[2];
int _android_user_stdout_handle = -1;
int _android_stderr_pipe[2];
int _android_user_stderr_handle = -1;

ANativeActivity *_android_activity = 0;
ANativeWindow *_android_window = 0;
jobject _android_context;
bool _android_running = true;
pthread_t _android_main_thread;
s64 _android_previous_vsync_time = 0;
f64 _android_refresh_rate = 0.0f;

pthread_cond_t _android_vsync_cond;
pthread_mutex_t _android_vsync_mut;

unit_local void *_android_mapped_pixels = 0;

static void _android_onDestroy(ANativeActivity* activity) {

}

static void _android_onStart(ANativeActivity* activity) {

}

static void _android_onResume(ANativeActivity* activity) {

}

static void* _android_onSaveInstanceState(ANativeActivity* activity, size_t* outLen) {
    return 0;
}

static void _android_onPause(ANativeActivity* activity) {

}

static void _android_onStop(ANativeActivity* activity) {

}

static void _android_onConfigurationChanged(ANativeActivity* activity) {

}

static void _android_onLowMemory(ANativeActivity* activity) {

}

static void _android_onWindowFocusChanged(ANativeActivity* activity, int focused) {

}

static void _android_onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {
    _android_window = window;
    __android_log_print(ANDROID_LOG_INFO, "android", "Set _android_window to %p", window);
}

static void _android_onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {

}

static void _android_onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {

}

static void _android_onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {

}

void _android_vsync_callback(s64 frame_time_nanos, void* data) {
    if (_android_previous_vsync_time != 0) {
        s64 delta_time_nanos = frame_time_nanos - _android_previous_vsync_time;

        if (delta_time_nanos > 0) {
            _android_refresh_rate = 1.0 / ((f64)delta_time_nanos / 1000000000.0);
        }
    }

    _android_previous_vsync_time = frame_time_nanos;

    pthread_cond_broadcast(&_android_vsync_cond);
    AChoreographer* choreographer = AChoreographer_getInstance();
    assert(choreographer);
    AChoreographer_postFrameCallback(choreographer, _android_vsync_callback, 0);
}

void* _android_main_thread_proc(void* arg) {

    // todo(charlie) timeout
    // wait for window to be created
    while (!_android_window) {}

    extern int _android_main(void);
    int code = _android_main();

    __android_log_print(ANDROID_LOG_INFO, "android thread", "Exit android thread");
    ANativeActivity_finish(_android_activity);

    return (void*)(u64)code;
}

JNIEXPORT __attribute__((visibility("default")))
void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState,
    size_t savedStateSize) {
    activity->callbacks->onDestroy = _android_onDestroy;
    activity->callbacks->onStart = _android_onStart;
    activity->callbacks->onResume = _android_onResume;
    activity->callbacks->onSaveInstanceState = _android_onSaveInstanceState;
    activity->callbacks->onPause = _android_onPause;
    activity->callbacks->onStop = _android_onStop;
    activity->callbacks->onConfigurationChanged = _android_onConfigurationChanged;
    activity->callbacks->onLowMemory = _android_onLowMemory;
    activity->callbacks->onWindowFocusChanged = _android_onWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated = _android_onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = _android_onNativeWindowDestroyed;
    activity->callbacks->onInputQueueCreated = _android_onInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = _android_onInputQueueDestroyed;

    activity->instance = 0;

    _android_activity = activity;

    AChoreographer* choreographer = AChoreographer_getInstance();
    assert(choreographer);
    AChoreographer_postFrameCallback(choreographer, _android_vsync_callback, 0);

    pthread_create(&_android_main_thread, 0, _android_main_thread_proc, 0);
    pthread_cond_init(&_android_vsync_cond, 0);
    pthread_mutex_init(&_android_vsync_mut, 0);
}


pthread_mutex_t _android_stdout_pending_mutex;
pthread_mutex_t _android_stderr_pending_mutex;

void* _android_stdout_thread_proc(void* arg) {
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(_android_stdout_pipe[0], buffer, sizeof(buffer) - 1)) > 0) {
        pthread_mutex_lock(&_android_stdout_pending_mutex);
        usleep(50000);
        buffer[bytesRead] = '\0';
        __android_log_print(ANDROID_LOG_INFO, "stdout", "%s", buffer);
        pthread_mutex_unlock(&_android_stdout_pending_mutex);
    }

    __android_log_print(ANDROID_LOG_INFO, "stdout", "Stdout closed");

    return 0;
}

void* _android_stderr_thread_proc(void* arg) {
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(_android_stderr_pipe[0], buffer, sizeof(buffer) - 1)) > 0) {
        pthread_mutex_lock(&_android_stderr_pending_mutex);
        usleep(50000);
        buffer[bytesRead] = '\0';
        __android_log_print(ANDROID_LOG_INFO, "stderr", "%s", buffer);
        pthread_mutex_unlock(&_android_stderr_pending_mutex);
    }

    __android_log_print(ANDROID_LOG_INFO, "stderr", "Stderr closed");

    return 0;
}

int _android_main(void) {
    pipe(_android_stdout_pipe);
    pipe(_android_stderr_pipe);

    pthread_attr_t attr;
    struct sched_param param;

    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, SCHED_OTHER);

    param.sched_priority = 0;
    pthread_attr_setschedparam(&attr, &param);
#if CSTD11
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
#endif

    pthread_mutex_init(&_android_stdout_pending_mutex, 0);
    pthread_create(&_android_stdout_thread, &attr, _android_stdout_thread_proc, 0);

    pthread_mutex_init(&_android_stderr_pending_mutex, 0);
    pthread_create(&_android_stderr_thread, &attr, _android_stderr_thread_proc, 0);

    extern int main(void);
    int code = main();

    _android_running = false;

    pthread_mutex_lock(&_android_stdout_pending_mutex);
    close(_android_stdout_pipe[0]);
    close(_android_stdout_pipe[1]);
    pthread_mutex_unlock(&_android_stdout_pending_mutex);

    pthread_mutex_lock(&_android_stderr_pending_mutex);
    close(_android_stderr_pipe[0]);
    close(_android_stderr_pipe[1]);
    pthread_mutex_unlock(&_android_stderr_pending_mutex);

    return code;
}

u64 sys_query_monitors(Physical_Monitor *buffer, u64 max_count) {

    if (!buffer) return 1;
    if (max_count == 0) return 0;



    // Retrieve display resolution using ANativeWindow
    ANativeWindow* window = _android_window;
    assert(window);

    int width = ANativeWindow_getWidth(window);
    int height = ANativeWindow_getHeight(window);

    // Retrieve display density using AConfiguration
    AConfiguration* config = AConfiguration_new();
    assert(config);

    AConfiguration_fromAssetManager(config, _android_activity->assetManager);

    int density_dpi = AConfiguration_getDensity(config);
    float64 scale = density_dpi <= 0 ? 1.0 : (float64)density_dpi / 160.0;

    AConfiguration_delete(config);

    memcpy(buffer[0].name, "Android display", sizeof("Android display")-1);
    buffer[0].name_count = sizeof("Android display")-1;

    buffer[0].refresh_rate = (s64)_android_refresh_rate;
    buffer[0].resolution_x = width;
    buffer[0].resolution_y = height;
    buffer[0].pos_x = 0;
    buffer[0].pos_y = 0;
    buffer[0].scale = scale;
    buffer[0].handle = 0;

    return 1;
}

bool sys_wait_vertical_blank(Physical_Monitor monitor) {
    return pthread_cond_wait(&_android_vsync_cond, &_android_vsync_mut) == 0;
}

File_Handle sys_get_stdout(void) {
    if (_android_user_stdout_handle == -1) return (File_Handle)(u64)_android_stdout_pipe[1];
    else return (File_Handle)(u64)_android_user_stdout_handle;
}
File_Handle sys_get_stderr(void) {
    if (_android_user_stderr_handle == -1) return (File_Handle)(u64)_android_stderr_pipe[1];
    else return (File_Handle)(u64)_android_user_stderr_handle;
}

void sys_set_stdout(File_Handle h) {
    _android_user_stdout_handle = (int)(u64)h;
}
void sys_set_stderr(File_Handle h) {
    _android_user_stderr_handle = (int)(u64)h;
}

#ifndef OSTD_HEADLESS

Surface_Handle sys_get_surface(void) {
    return (Surface_Handle)_android_window;
}

void surface_poll_events(Surface_Handle surface) {
    (void)surface;
}
bool surface_should_close(Surface_Handle s) {
    return false;
}

bool surface_set_flags(Surface_Handle h, Surface_Flags flags) {
    return false;
}
bool surface_unset_flags(Surface_Handle h, Surface_Flags flags) {
    return false;
}

bool surface_get_framebuffer_size(Surface_Handle h, s64 *width, s64 *height) {
    *width = (s64)ANativeWindow_getWidth((ANativeWindow*)h);
    *height = (s64)ANativeWindow_getHeight((ANativeWindow*)h);

    return true;
}

void* surface_map_pixels(Surface_Handle h) {
    if (!_android_mapped_pixels) {
        s64 width, height;
        surface_get_framebuffer_size(h, &width, &height);

        _android_mapped_pixels = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, (width * height * 4) / 4096, false);
    }
    return _android_mapped_pixels;
}
void surface_blit_pixels(Surface_Handle h) {
    assertmsg(_android_mapped_pixels, "You must call surface_map_pixels() before blitting them. Otherwise there might not be any pixels to blit.");
    s64 width, height;
    surface_get_framebuffer_size(h, &width, &height);

    if (ANativeWindow_setBuffersGeometry((ANativeWindow*)h, width, height, WINDOW_FORMAT_RGBA_8888) != 0) {
        return;
    }

    ANativeWindow_Buffer buffer;
    if (ANativeWindow_lock((ANativeWindow*)h, &buffer, 0) != 0) {
        return;
    }

    assert(width == buffer.width);
    assert(height == buffer.height);

    memcpy(buffer.bits, _android_mapped_pixels, width*height*4);

    ANativeWindow_unlockAndPost((ANativeWindow*)h);
}

bool surface_get_monitor(Surface_Handle h, Physical_Monitor *monitor) {
    sys_query_monitors(monitor, 1);
    return true;
}

#endif // !OSTD_HEADLESS

void sys_print_stack_trace(File_Handle handle) {
    sys_write_string(handle, STR("<Stack trace unimplemented>"));
}

#elif (OS_FLAGS & OS_FLAG_LINUX)

/////////////////////////////////////////////////////
//////
// :Linux
//////
/////////////////////////////////////////////////////

#ifndef OSTD_HEADLESS

Display *xdisplay = 0;

u64 sys_query_monitors(Physical_Monitor *buffer, u64 max_count)
{
    Display *dpy = XOpenDisplay(0);
    if (!dpy) {
        // Could not open X display
        return 0;
    }

    Window root = RootWindow(dpy, DefaultScreen(dpy));

    XRRScreenResources *res = XRRGetScreenResources(dpy, root);
    if (!res) {
        XCloseDisplay(dpy);
        return 0;
    }

    u64 total_found = 0;

    for (int i = 0; i < res->noutput; i++) {
        XRROutputInfo *output_info = XRRGetOutputInfo(dpy, res, res->outputs[i]);
        if (!output_info) {
            continue;
        }

        // Only count if it's connected and has an active CRTC
        if (output_info->connection == RR_Connected && output_info->crtc) {
            XRRCrtcInfo *crtc_info = XRRGetCrtcInfo(dpy, res, output_info->crtc);
            if (crtc_info) {
                if (buffer && total_found < max_count) {
                    Physical_Monitor *pm = &buffer[total_found];
                    memset(pm, 0, sizeof(*pm));

                    memcpy(pm->name, output_info->name, sizeof(pm->name) - 1);
                    pm->name[sizeof(pm->name) - 1] = '\0';
                    pm->name_count = (u64)(c_style_strlen((char*)pm->name) + 1);

                    pm->pos_x       = crtc_info->x;
                    pm->pos_y       = crtc_info->y;
                    pm->resolution_x = crtc_info->width;
                    pm->resolution_y = crtc_info->height;

                    // todo(charlie) this is a hacky approximation that might not work very well so
                    // I will need to revisit it.
                    double refresh = 0.0;
                    for (int m = 0; m < res->nmode; m++) {
                        if (res->modes[m].id == crtc_info->mode) {
                            XRRModeInfo *mode_info = &res->modes[m];
                            if (mode_info->hTotal && mode_info->vTotal) {
                                refresh = (double)mode_info->dotClock /
                                          (double)(mode_info->hTotal * mode_info->vTotal);
                            }
                            break;
                        }
                    }
                    pm->refresh_rate = (u64)(refresh + 0.5);

                    pm->scale = 1.0;

                    pm->handle = dpy;
                }
                total_found++;
                XRRFreeCrtcInfo(crtc_info);
            }
        }
        XRRFreeOutputInfo(output_info);
    }

    XRRFreeScreenResources(res);
    XCloseDisplay(dpy);

    return total_found;
}

bool sys_wait_vertical_blank(Physical_Monitor monitor) {
    // Linux sucks for this. All I can really do is open an invisible window, make
    // a dummy glx context, and swap buffers.
    (void)monitor;
    local_persist GLXContext glx = 0;
    local_persist Window wnd = 0;
    local_persist Display *dsp = 0;

    if (!glx) {
        dsp = XOpenDisplay(0);
        assert(dsp);
        if (!dsp) {
            return false;
        }

        int screen = DefaultScreen(dsp);

        // Define the visual attributes
        int attribs[] = {
            GLX_RGBA,
            GLX_DEPTH_SIZE, 24,
            GLX_DOUBLEBUFFER,
            None
        };

        XVisualInfo *visual_info = glXChooseVisual(dsp, screen, attribs);
        if (!visual_info) {
            XCloseDisplay(dsp);
            dsp = 0;
            return false;
        }

        // Create a simple window
        wnd = XCreateSimpleWindow(
            dsp,
            DefaultRootWindow(dsp),
            -10000, -10000,  /* x, y: move window off-screen */
            1, 1,           /* width, height: 1x1 so it's tiny */
            0,
            BlackPixel(dsp, screen),
            BlackPixel(dsp, screen)
        );

        assert(wnd);

        // Make the window invisible
        XSetWindowAttributes attrs;
        attrs.override_redirect = True;
        XChangeWindowAttributes(dsp, wnd, CWOverrideRedirect, &attrs);

        // Map the window to make it a valid drawable
        XMapWindow(dsp, wnd);

        // Wait window mapped.
        XEvent event;
        for (;;) {
            if (XCheckTypedWindowEvent(dsp, wnd, MapNotify, &event)) {
                break;
            }
        }

        // Create a GLX context
        glx = glXCreateContext(dsp, visual_info, 0, GL_TRUE);
        XFree(visual_info);

        assert(glx);

        assert(glXMakeCurrent(dsp, wnd, glx));

        // Enable v-sync
        typedef int (*glXSwapIntervalProc)(int);
        glXSwapIntervalProc glXSwapIntervalSGI = (glXSwapIntervalProc)glXGetProcAddressARB((const GLubyte *)"glXSwapIntervalSGI");
        if (glXSwapIntervalSGI) {
            glXSwapIntervalSGI(1);
        }
    }

    if (dsp && glx && wnd) {
        glXMakeCurrent(dsp, wnd, glx);
        glXSwapBuffers(dsp, wnd);
        return true;
    }

    return false;
}

bool surface_get_monitor(Surface_Handle h, Physical_Monitor *monitor) {
    _Surface_State *state = _get_surface_state(h);

    Physical_Monitor monitors[128];
    u64 monitor_count = sys_query_monitors(monitors, 128);

    if (monitor_count == 0) {
        return false;
    }

    if (!xdisplay) xdisplay = XOpenDisplay(0);

    XWindowAttributes win_attr;
    if (!XGetWindowAttributes(xdisplay, (Window)state->handle, &win_attr)) {
        return false;
    }

    int win_x = win_attr.x;
    int win_y = win_attr.y;
    int win_width = win_attr.width;
    int win_height = win_attr.height;

    int max_intersection_area = 0;

    Physical_Monitor *max_monitor = 0;

    for (u64 i = 0; i < monitor_count; i++) {
        Physical_Monitor *m = &monitors[i];

        int mon_x = m->pos_x;
        int mon_y = m->pos_y;
        int mon_width = m->resolution_x;
        int mon_height = m->resolution_y;

        int inter_x = max(win_x, mon_x);
        int inter_y = max(win_y, mon_y);
        int inter_width = min(win_x + win_width, mon_x + mon_width) - inter_x;
        int inter_height = min(win_y + win_height, mon_y + mon_height) - inter_y;

        if (inter_width > 0 && inter_height > 0) {
            int intersection_area = inter_width * inter_height;
            if (intersection_area > max_intersection_area) {
                max_intersection_area = intersection_area;
                max_monitor = m;
            }
        }
    }

    if (max_monitor) {
        *monitor = *max_monitor;
        return true;
    }
    return false;
}

#endif // OSTD_HEADLESS

File_Handle sys_get_stdout(void) {
    return (File_Handle)(u64)STDOUT_FILENO;
}

File_Handle sys_get_stderr(void) {
    return (File_Handle)(u64)STDERR_FILENO;
}

void sys_set_stdout(File_Handle h) {
    dup2((int)(u64)h, STDOUT_FILENO);
}

void sys_set_stderr(File_Handle h) {
    dup2((int)(u64)h, STDERR_FILENO);
}

unit_local bool _x11_initted = false;

#ifndef OSTD_HEADLESS

Surface_Handle sys_make_surface(Surface_Desc desc) {
        if (!_x11_initted) {
            XInitThreads();
            _x11_initted = true;
        }

        if (!xdisplay) xdisplay = XOpenDisplay(0);
        if (!xdisplay) {
            sys_write_string(sys_get_stdout(), STR("Failed to open X xdisplay\n"));
            return 0;
        }

        int screen = DefaultScreen(xdisplay);
        unsigned long white = WhitePixel(xdisplay, screen);

        Window window = XCreateSimpleWindow(
            xdisplay,
            DefaultRootWindow(xdisplay),
            0, 0,
            desc.width, desc.height,
            0,
            0,
            white
        );


        char ctitle[256];
        memcpy(ctitle, desc.title.data, min(desc.title.count, 255));
        ctitle[min(desc.title.count, 255)] = 0;
        XStoreName(xdisplay, window, ctitle);

        XSelectInput(xdisplay, window, ExposureMask | KeyPressMask | StructureNotifyMask);

        if (!(desc.flags & SURFACE_FLAG_HIDDEN)) {
            XMapWindow(xdisplay, window);
        }

        _Surface_State *surface = (_Surface_State *)_alloc_surface_state();
        surface->handle = (Surface_Handle)window;
        surface->should_close = false;
        return (Surface_Handle)window;
}

void surface_close(Surface_Handle s) {
    if (!s) return;
    _Surface_State *state = _get_surface_state(s);

    XDestroyWindow(xdisplay, (Window)state->handle);
    XCloseDisplay(xdisplay);

    state->allocated = false;
}

void surface_poll_events(Surface_Handle surface) {
    if (!surface) return;
    _Surface_State *state = _get_surface_state(surface);

    while (XPending(xdisplay)) {
        XEvent evt;
        XNextEvent(xdisplay, &evt);
        switch (evt.type) {
            case ClientMessage:
            case DestroyNotify:
                state->should_close = true;
                break;
            default:
                break;
        }
    }
}

bool surface_should_close(Surface_Handle s) {
    if (!s) return true;
    _Surface_State *state = _get_surface_state(s);
    return state->should_close;
}

bool surface_set_flags(Surface_Handle h, Surface_Flags flags) {
    if (!h) return false;
    _Surface_State *state = _get_surface_state(h);

    if (flags & SURFACE_FLAG_HIDDEN) {
        XUnmapWindow(xdisplay, (Window)state->handle);
    }
    if (flags & SURFACE_FLAG_TOPMOST) {

    }
    return true;
}

bool surface_unset_flags(Surface_Handle h, Surface_Flags flags) {
    if (!h) return false;
    _Surface_State *state = _get_surface_state(h);

    if (flags & SURFACE_FLAG_HIDDEN) {
        XMapWindow(xdisplay, (Window)state->handle);
    }

    if (flags & SURFACE_FLAG_TOPMOST) {
    }
    return true;
}

bool surface_get_framebuffer_size(Surface_Handle h, s64 *width, s64 *height) {
    _Surface_State *state = _get_surface_state(h);
    if (!state) return false;

    XWindowAttributes attrs;
    if (!XGetWindowAttributes(xdisplay, (Window)h, &attrs)) {
        return false;
    }
    *width  = (s64)attrs.width;
    *height = (s64)attrs.height;
    return true;
}

void* surface_map_pixels(Surface_Handle h) {
    _Surface_State *state = _get_surface_state(h);
    if (!state) return 0;

    if (state->pixels) {
        return state->pixels;
    }

    s64 width, height;
    if (!surface_get_framebuffer_size(h, &width, &height)) return 0;

    s64 bytes_needed = width * height * 4;
    s64 pages        = (bytes_needed + 4095) / 4096;

    state->pixels = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, pages, false);
    if (!state->pixels) {
        return 0;
    }

    int screen = DefaultScreen(xdisplay);
    int depth  = DefaultDepth(xdisplay, screen);

    state->ximage = XCreateImage(
        xdisplay,
        DefaultVisual(xdisplay, screen),
        (unsigned int)depth,
        ZPixmap,
        0,
        (char*)state->pixels,
        (unsigned int)width,
        (unsigned int)height,
        32,
        (int)(width * 4)
    );

    state->gc = XCreateGC(xdisplay, (Drawable)h, 0, 0);

    return state->pixels;
}

void surface_blit_pixels(Surface_Handle h) {
    _Surface_State *state = _get_surface_state(h);
    if (!state) return;

    if (!state->pixels || !state->ximage) {
        return;
    }

    s64 width, height;
    if (!surface_get_framebuffer_size(h, &width, &height)) {
        return;
    }

    Window window = (Window)state->handle;
    glXMakeCurrent(0, 0, 0);
    XPutImage(
        xdisplay,
        (Drawable)window,
        state->gc,
        state->ximage,
        0, 0,
        0, 0,
        (unsigned int)width,
        (unsigned int)height
    );

    XFlush(xdisplay);
}

#endif // !OSTD_HEADLESS

void sys_print_stack_trace(File_Handle handle) {
    void *stack[64];
    int frames = backtrace(stack, 64);
    char **symbols = backtrace_symbols(stack, frames);

    if (symbols) {
        for (int i = 0; i < frames; i++) {
            sys_write_string(handle, STR(symbols[i]));
            sys_write_string(handle, STR("\n"));
        }
        //free(symbols);
        // #Leak
    } else {
        sys_write_string(handle, STR("<Stack trace unavailable>\n"));
    }
}

#elif (OS_FLAGS & OS_FLAG_EMSCRIPTEN)

/////////////////////////////////////////////////////
//////
// :Emscripten
//////
/////////////////////////////////////////////////////

#undef abs
#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/threading_legacy.h>
#define abs(x) ((x) < 0 ? -(x) : (x))
#undef bool

unit_local u64 __rdtsc(void) {
    return (u64)(emscripten_get_now()*1000.0);
}

#ifndef OSTD_HEADLESS

u64 sys_query_monitors(Physical_Monitor *buffer, u64 max_count)
{
    if (!buffer) {
        return 1;
    }
    if (max_count == 0) {
        return 0;
    }
    double scale = emscripten_get_device_pixel_ratio();

    int width = 0;
    int height = 0;
    emscripten_get_canvas_element_size("#canvas", &width, &height);

    {
        memcpy(buffer[0].name, "Web Display", sizeof("Web Display")-1);
        buffer[0].name_count = sizeof("Web Display")-1;

        buffer[0].refresh_rate = 60;

        buffer[0].resolution_x = width;
        buffer[0].resolution_y = height;

        buffer[0].pos_x = 0;
        buffer[0].pos_y = 0;

        buffer[0].scale = scale;

        buffer[0].handle = 0;
    }

    return 1;
}
bool surface_get_monitor(Surface_Handle h, Physical_Monitor *monitor) {
    (void)h;
    sys_query_monitors(monitor, 1);
    return true;
}

#endif // !OSTD_HEADLESS

File_Handle sys_get_stdout(void) {
    return (File_Handle)1;
}

File_Handle sys_get_stderr(void) {
    return (File_Handle)2;
}

void sys_set_stdout(File_Handle h) {
    (void)h;
}
void sys_set_stderr(File_Handle h) {
    (void)h;
}

#ifndef OSTD_HEADLESS
Surface_Handle sys_get_surface(void) {
    return (Surface_Handle)69; // todo(charlie) revisit
}

void surface_poll_events(Surface_Handle surface) {
    (void)surface;
}
bool surface_should_close(Surface_Handle s) {
    (void)s;
    return false;
}

typedef struct _Em_Canvas_Size_Result {
    int success;
    int w;
    int h;
} _Em_Canvas_Size_Result;

unit_local void _em_get_canvas_size_main_thread(void *arg) {
    _Em_Canvas_Size_Result *result = (_Em_Canvas_Size_Result *)arg;
    int w, h_int;
    if (emscripten_get_canvas_element_size("#canvas", &w, &h_int) == EMSCRIPTEN_RESULT_SUCCESS) {
        result->w = w;
        result->h = h_int;
        result->success = 1;
    } else {
        result->success = 0;
    }
}

bool surface_get_framebuffer_size(Surface_Handle h, s64 *width, s64 *height) {
    (void)h;
    _Em_Canvas_Size_Result result = {0};

    emscripten_sync_run_in_main_runtime_thread(EM_FUNC_SIG_VI, _em_get_canvas_size_main_thread, &result);
    if (!result.success)
        return false;

    *width = result.w;
    *height = result.h;
    return true;
}

static uint32_t *_em_pixel_buffer = 0;
static size_t _em_pixel_buffer_size = 0;
// Allocate (or reallocate) a static pixel buffer to match the canvas size.
void* surface_map_pixels(Surface_Handle h) {
    (void)h;
    s64 width, height;
    if (!surface_get_framebuffer_size(h, &width, &height))
        return 0;
    size_t required = (size_t)width * (size_t)height;
    if (required > _em_pixel_buffer_size) {
        if (_em_pixel_buffer) {
            sys_unmap_pages(_em_pixel_buffer);
        }

        u64 size = required * 4;
        u64 pages = (size+4096)/4096;
        _em_pixel_buffer = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, pages, false);
        _em_pixel_buffer_size = required;
    }
    return _em_pixel_buffer;
}

unit_local char _em_surface_blit_pixels_script[8196] = {0};
    #pragma clang diagnostic ignored "-Wmissing-noreturn"
unit_local void main_thread_surface_blit_pixels(void) {
    char *script = _em_surface_blit_pixels_script;
    emscripten_run_script(script);
}

void surface_blit_pixels(Surface_Handle h) {
    (void)h;
    s64 width, height;
    if (!surface_get_framebuffer_size(h, &width, &height))
        return;

    const char *format =
        "var canvas = document.getElementById('canvas');"
        "if (canvas) {"
            "var ctx = canvas.getContext('2d');"
            "var imageData = ctx.createImageData(%i, %i);"
            "var numBytes = %i * %i * 4;"
            "var ptr = %i;"
            "var pixels = HEAPU8.subarray(ptr, ptr + numBytes);"
            "imageData.data.set(pixels);"
            "ctx.putImageData(imageData, 0, 0);"
        "}";

    int w = (int)width;
    int h_int = (int)height;

    #pragma clang diagnostic ignored "-Wformat-nonliteral"
    extern int snprintf(char*restrict, unsigned long, const char*restrict, ...);
    int script_len = snprintf(0, 0, format, w, h_int, w, h_int, (int)_em_pixel_buffer) + 1;
    assert(script_len < (int)sizeof(_em_surface_blit_pixels_script));
    snprintf(_em_surface_blit_pixels_script, (unsigned long)script_len, format, w, h_int, w, h_int, (int)_em_pixel_buffer);

    emscripten_sync_run_in_main_runtime_thread(EM_FUNC_SIG_V, main_thread_surface_blit_pixels, _em_surface_blit_pixels_script);
}

unit_local volatile s32 _em_frame_ready = 0;
unit_local EM_BOOL animation_frame_callback(double time, void *userData) {
    (void)time;
    (void)userData;
    _em_frame_ready = 1;
    return EM_TRUE;
}
unit_local void _em_main_thread_wait_animation_frame(void) {
    _em_frame_ready = 0;
    emscripten_request_animation_frame(animation_frame_callback, 0);

    while (!_em_frame_ready) {
        // whatevs web is dumb
         _em_frame_ready = true;
    }
}
bool sys_wait_vertical_blank(Physical_Monitor monitor) {
    (void)monitor;
    emscripten_sync_run_in_main_runtime_thread(EM_FUNC_SIG_V, _em_main_thread_wait_animation_frame);
    return true;
}

#endif // !OSTD_HEADLESS


void sys_print_stack_trace(File_Handle handle) {
    char buffer[16384];
    int len = emscripten_get_callstack(EM_LOG_C_STACK, buffer, 16384);
    sys_write(handle, buffer, (u64)len);
}

#endif // OS_FLAGS & XXXXX


#if defined(OSTD_SELF_CONTAINED)

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-identifier"
#pragma clang diagnostic ignored "-Wmissing-variable-declarations"
#endif

unit_local int ___argc;
unit_local string *___argv;

unit_local u64 sys_get_argc(void) { return (u64)___argc; }
unit_local string *sys_get_argv(void) { return ___argv; }

#if defined(_WIN32)
int _fltused = 0;

#ifndef _WIN64
#error Only x86_64 windows supported
#endif

__attribute__((naked))
void __chkstk(void) {
    __asm__ volatile(
        "movq %rcx, %rax\n"
        "ret\n"
    );
}

int ostd_main(void);
int __premain(void) {
    LPWSTR cmd = GetCommandLineW();
    int argc = 0;
    LPWSTR *wargv = CommandLineToArgvW(cmd, &argc);
    
    u64 argv_arr_size = (u64)argc*sizeof(string);
    u64 argv_size = 0;
    for (int i = 0; i < argc; ++i) {
        int len = WideCharToMultiByte(CP_UTF8, 0, wargv[i], -1, 0, 0, 0, 0);
        argv_size += (u64)len;
    }
    
    u64 total_size = argv_size + argv_arr_size;
    u64 ps = sys_get_info().page_size;
    u64 page_count = (total_size + ps - 1) / ps;
    
    void *mem = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, page_count, false);
    
    string *argv = (string*)mem;
    char *pnext = (char*)mem + argv_arr_size;
    
    for (int i = 0; i < argc; ++i) {
        int len = WideCharToMultiByte(CP_UTF8, 0, wargv[i], -1, 0, 0, 0, 0);
        WideCharToMultiByte(CP_UTF8, 0, wargv[i], -1, pnext, len, 0, 0);
        argv[i] = (string) { (u64)(len-1), (u8*)pnext };
        pnext += len-1;
    }
    
    ___argc = argc;
    ___argv = argv;
    
    return ostd_main();
}

__attribute__((naked))
void mainCRTStartup(void) { 
    __asm__ volatile(
        // reserve the 32-byte shadow space
        "subq $32, %rsp\n"
        // call your C main()
        "call __premain\n"
        // restore RSP
        "addq $32, %rsp\n"
        // move return value into RCX and tail-jump to sys_exit
        "movq %rax, %rcx\n"
        "jmp sys_exit\n"
    );
}


#elif defined(__linux__)
void __start(void) {
    int main(void);
    __asm__ (
        "mov %%rsp, %%rdi\n"
        "call init_linux_args\n"
        "call main\n"
        "mov %eax, %edi\n"
        "call sys_exit\n"
        :
        :
        : "rdi", "rax"
    );
}
#else
#error os missing startup implementation
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif // OSTD_SELF_CONTAINED

#endif // OSTD_IMPL

#endif // _SYSTEM_1_H

/* End include: system1.h */

/* Begin include: system2.h */
#ifndef _SYSTEM_2_H
#define _SYSTEM_2_H

#ifndef _SYSTEM_1_H
#endif // _SYSTEM_1_H
#ifndef _MEMORY_H

/* Begin include: memory.h */
#ifndef _MEMORY_H
#define _MEMORY_H

#ifndef _BASE_H
#endif // _BASE_H

#ifndef _STRING_H
#endif //_STRING_H

#ifndef _SYSTEM_1_H
#endif //_SYSTEM_1_H

/////
// Allocator
/////

typedef enum Allocator_Message {
    ALLOCATOR_ALLOCATE,
    ALLOCATOR_REALLOCATE,
    ALLOCATOR_FREE
} Allocator_Message;
typedef void*(*Allocator_Proc)(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags);

typedef struct Allocator {
    void *data;
    Allocator_Proc proc;
} Allocator;

inline void *allocate(Allocator a, u64 n);
inline void *reallocate(Allocator a, void *p, u64 old_n, u64 n);
inline void deallocate(Allocator a, void *p);

inline void *allocatef(Allocator a, u64 n, u64 flags);
inline void *reallocatef(Allocator a, void *p, u64 old_n, u64 n, u64 flags);
inline void deallocatef(Allocator a, void *p, u64 flags);

#define New(a, T) ((T*)allocate(a, sizeof(T)))
#define NewBuffer(a, T, n) ((T*)allocate(a, sizeof(T)*n))

#define PushTemp(T) New(get_temp(), T)
#define PushTempBuffer(T, n) NewBuffer(get_temp(), T, n)

inline string string_allocate(Allocator a, u64 n);
inline void string_deallocate(Allocator a, string s);
inline string string_copy(Allocator a, string s);

/////
// Arena
/////

typedef struct Arena {
    void *start;
    void *position;
    u64 reserved_size;
    u64 allocated_size;
} Arena;

OSTD_LIB Arena make_arena(u64 reserved_size, u64 initial_allocated_size);
OSTD_LIB void *arena_push(Arena *arena, u64 size);
OSTD_LIB void *arena_push_copy(Arena *arena, void *src, u64 size);
OSTD_LIB void *arena_push_string(Arena *arena, string data);
OSTD_LIB void arena_pop(Arena *arena, u64 size);
OSTD_LIB void arena_reset(Arena *arena);
OSTD_LIB void free_arena(Arena arena);

unit_local void* arena_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags);
unit_local inline Allocator arena_allocator(Arena *a) { return (Allocator) { a, arena_allocator_proc }; }

/////
// Temporary storage
/////

// todo(charlie) temporary storage might get bloated with large temporary allocations,
// so we should provide a way to shrink temporary storage.

OSTD_LIB Allocator get_temp(void);
OSTD_LIB void reset_temporary_storage(void);
OSTD_LIB void *tallocate(size_t n);


/////
// Allocation interface
/////

OSTD_LIB void *allocate(Allocator a, u64 n);
OSTD_LIB void *reallocate(Allocator a, void *p, u64 old_n, u64 n);
OSTD_LIB void deallocate(Allocator a, void *p);

OSTD_LIB void *allocatef(Allocator a, u64 n, u64 flags);
OSTD_LIB void *reallocatef(Allocator a, void *p, u64 old_n, u64 n, u64 flags);
OSTD_LIB void deallocatef(Allocator a, void *p, u64 flags);

OSTD_LIB string string_allocate(Allocator a, u64 n);
OSTD_LIB void string_deallocate(Allocator a, string s);

OSTD_LIB string string_copy(Allocator a, string s);


/////
// Arena-backed Persistent Growing Array
/////

/*
    Usage:
    
        Data *my_array;
        persistent_array_init(allocator, (void**)&my_array, sizeof(Data));
        
        persistent_array_reserve(my_array, 7); // Optional, reserve memory for fewer grows
        
        Data elem = ...;
        persistent_array_push_copy(my_array, &elem);
        
        Data *elem = persistent_array_push_empty(my_array);
        
        persistent_array_uninit(my_array);
*/

OSTD_LIB void persistent_array_init(void **pparray, u64 element_size);
OSTD_LIB void persistent_array_uninit(void *parray);
OSTD_LIB void *persistent_array_push_copy(void *parray, void *item);
OSTD_LIB void *persistent_array_push_empty(void *parray);
OSTD_LIB void persistent_array_reserve(void *parray, u64 reserve_count);
OSTD_LIB void persistent_array_shift_left(void *parray, u64 start_index, u64 shift_amount);
OSTD_LIB void *persistent_array_shift_right(void *parray, u64 start_index, u64 shift_amount);
OSTD_LIB void persistent_array_pop(void *parray);
OSTD_LIB void persistent_array_swap_and_pop(void *parray, u64 index);
OSTD_LIB s64 persistent_array_find_from_left(void *parray, void *pcompare_mem);
OSTD_LIB s64 persistent_array_find_from_right(void *parray, void *pcompare_mem);
OSTD_LIB void persistent_array_set_count(void *parray, u64 count);
OSTD_LIB u64 persistent_array_count(void *parray);

typedef struct Arena_Backed_Array_Header {
    Arena arena;
    u64 capacity;
    u64 count;
    u64 elem_size;
    u64 signature;
} Arena_Backed_Array_Header;

#ifdef OSTD_IMPL

typedef struct _Per_Thread_Temporary_Storage {
    Arena arena;
    Allocator a;
    bool initted;
} _Per_Thread_Temporary_Storage;

unit_local inline _Per_Thread_Temporary_Storage* _lazy_init_temporary_storage(void) {
    _Ostd_Thread_Storage *s = _ostd_get_thread_storage();
    assert(s->temp);
    assertmsg(sizeof(_Per_Thread_Temporary_Storage) < sizeof(s->temporary_storage_struct_backing), "refactor time");
    if (s->temp->initted) {
        return s->temp;
    }

#if OS_FLAGS & OS_FLAG_EMSCRIPTEN
    s->temp->arena = make_arena(1024*1024, 1024*1024);
#else
    s->temp->arena = make_arena(sys_get_info().page_size*100000, 1024*32);
#endif
    s->temp->a = (Allocator) { &s->temp->arena, arena_allocator_proc };
    
    s->temp->initted = true;
    
    return s->temp;
}
Allocator get_temp(void) {
    return _lazy_init_temporary_storage()->a;
}
void reset_temporary_storage(void) {
    arena_reset(&_lazy_init_temporary_storage()->arena);
}
void *tallocate(size_t n) {
    return allocate(_lazy_init_temporary_storage()->a, n);
}

Arena make_arena(u64 reserved_size, u64 initial_allocated_size) {
    assert(reserved_size >= initial_allocated_size);

#if OS_FLAGS & OS_FLAG_EMSCRIPTEN
    assertmsg(reserved_size == initial_allocated_size, "Emscripten does not support reserved-only memory allocations. Arena initial allocation size must match reserved_size");
#endif // OS_FLAGS & OS_FLAG_EMSCRIPTEN

    System_Info info = sys_get_info();

    // Align to page size
    reserved_size = (reserved_size + info.page_size - 1) & ~(info.page_size - 1);
    initial_allocated_size = (initial_allocated_size + info.page_size - 1) & ~(info.page_size - 1);

    assert(initial_allocated_size <= reserved_size);

    Arena arena;

    if (reserved_size > initial_allocated_size) {
        arena.start = sys_map_pages(SYS_MEMORY_RESERVE, 0, reserved_size/info.page_size, false);
        assert(arena.start);
        if (initial_allocated_size) {
            void *allocate_result = sys_map_pages(SYS_MEMORY_ALLOCATE, arena.start, initial_allocated_size/info.page_size, true);
            assert(allocate_result == arena.start);
        }
    } else {
        arena.start = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, reserved_size/info.page_size, false);
    }

    arena.position = arena.start;


    arena.reserved_size = reserved_size;
    arena.allocated_size = initial_allocated_size;

    return arena;
}
void arena_reset(Arena *arena) {
    arena->position = arena->start;
}
void free_arena(Arena arena) {
    void *start = arena.start;
    void *end = (u8*)arena.start + arena.reserved_size;

    u64 pointer_count = sys_query_mapped_regions(start, end, 0, 0);

    Mapped_Memory_Info *pointers = (Mapped_Memory_Info *)arena.start;
    sys_query_mapped_regions(start, end, pointers, pointer_count);

    u32 i;
    for (i = 0; i < pointer_count; i += 1) {
        sys_unmap_pages(pointers[i].base);
    }
}

void *arena_push(Arena *arena, u64 size) {

    System_Info info = sys_get_info();

    void *allocated_tail = (u8*)arena->start + arena->allocated_size;
    void *reserved_tail = (u8*)arena->start + arena->reserved_size;

    if ((u64)arena->position + size > (u64)reserved_tail) {
        return 0;
    }

    if ((u64)arena->position + size > (u64)allocated_tail) {

        u64 amount_to_allocate = ((u64)arena->position + size) - (u64)allocated_tail;

        amount_to_allocate = (amount_to_allocate + info.page_size-1) & ~(info.page_size-1);

        u64 pages_to_allocate = amount_to_allocate / info.page_size;

        void *allocate_result = sys_map_pages(SYS_MEMORY_ALLOCATE, allocated_tail, pages_to_allocate, true);
        assertmsg(allocate_result == allocated_tail, "Failed allocating pages in arena");

        arena->allocated_size += amount_to_allocate;
    }

    void *p = arena->position;
    arena->position = (u8*)arena->position + size;

    return p;
}

void *arena_push_copy(Arena *arena, void *src, u64 size) {
    void *dst = arena_push(arena, size);
    if (!dst) return dst;
    memcpy(dst, src, (sys_uint)size);
    return dst;
}

void *arena_push_string(Arena *arena, string data) {
    void *dst = arena_push(arena, data.count);
    if (!dst) return dst;
    memcpy(dst, data.data, (sys_uint)data.count);
    return dst;
}

void arena_pop(Arena *arena, u64 size) {
    arena->position = (u8*)arena->position - size;
    if ((u64)arena->position < (u64)arena->start)  arena->position = arena->start;
}

void* arena_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags) {
    (void)flags;
    Arena *a = (Arena*)data;
    switch (msg) {
        case ALLOCATOR_ALLOCATE:
        {
            void *p = arena_push(a, n);
            return p;
        }
        case ALLOCATOR_REALLOCATE:
        {
            u64 pad = (u64)a->start - ((u64)a->start+alignment-1) & ~(alignment-1);
            void* p = (u8*)arena_push(a, n+pad) + pad;
            assert((u64)p % alignment == 0);
            if (old && old_n) {
                memcpy(p, old, (sys_uint)min(old_n, n));
            }
            return p;

        }
        case ALLOCATOR_FREE:
        {
            break;
        }

        default:
        {
            break;
        }
    }

    return 0;
}

void *allocate(Allocator a, u64 n) {
    return a.proc(ALLOCATOR_ALLOCATE, a.data, 0, 0, n, 0, 0);
}
void *reallocate(Allocator a, void *p, u64 old_n, u64 n) {
    return a.proc(ALLOCATOR_REALLOCATE, a.data, p, old_n, n, 0, 0);
}
void deallocate(Allocator a, void *p) {
    a.proc(ALLOCATOR_FREE, a.data, p, 0, 0, 0, 0);
}

void *allocatef(Allocator a, u64 n, u64 flags) {
    return a.proc(ALLOCATOR_ALLOCATE, a.data, 0, 0, n, flags, 0);
}
void *reallocatef(Allocator a, void *p, u64 old_n, u64 n, u64 flags) {
    return a.proc(ALLOCATOR_REALLOCATE, a.data, p, old_n, n, flags, 0);
}
void deallocatef(Allocator a, void *p, u64 flags) {
    a.proc(ALLOCATOR_FREE, a.data, p, 0, 0, flags, 0);
}

string string_allocate(Allocator a, u64 n) {
    u8 *p = (u8*)allocate(a, n);
    assertmsg(p, "Ran out of memory.");
    return (string) {n, p};
}
void string_deallocate(Allocator a, string s) {
    deallocate(a, s.data);
}

string string_copy(Allocator a, string s) {
    string new_s = string_allocate(a, s.count);
    memcpy(new_s.data, s.data, (sys_uint)s.count);
    return new_s;
}

unit_local Arena_Backed_Array_Header *_persistent_header(void *parray) {
    Arena_Backed_Array_Header *h = (Arena_Backed_Array_Header*)parray - 1;
    assertmsg(h->signature == 0xfeedfacedeadbeef, "Pointer used as persistent array but it was not initialized with persistent_array_init()");
    return h;
}

void persistent_array_init(void **pparray, u64 element_size) {
    // todo(charlie) configurable
    Arena arena = make_arena(1024ULL*1024ULL*1024ULL*4ULL, 0);
    
    Arena_Backed_Array_Header *header = (Arena_Backed_Array_Header*)arena_push(&arena, sizeof(Arena_Backed_Array_Header));
    *header = (Arena_Backed_Array_Header){0};
    header->arena = arena;
    header->signature = 0xfeedfacedeadbeef;
    header->elem_size = element_size;
    
    *pparray = header->arena.position;
}
void persistent_array_uninit(void *parray) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    free_arena(h->arena);
}
void *persistent_array_push_copy(void *parray, void *src) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    void *p = persistent_array_push_empty(parray);
    memcpy(p, src, h->elem_size);
    return p;
}
void *persistent_array_push_empty(void *parray) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    
    void *p;
    if (h->count == h->capacity) {
        p = arena_push(&h->arena, h->elem_size);
        h->capacity += 1;
    } else {
        assert(h->count < h->capacity);
        p = (u8*)parray + h->count*h->elem_size;
    }
    
    h->count += 1;
    
    return p;
}
void persistent_array_reserve(void *parray, u64 reserve_count) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    if (reserve_count <= h->capacity) return;
    
    u64 diff = reserve_count - h->capacity;
    
    arena_push(&h->arena, diff*h->elem_size);
    h->capacity += diff;
}
void persistent_array_shift_left(void *parray, u64 start_index, u64 shift_amount) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    assertmsg(start_index < h->count, "Index out of range");
    u64 left_count = h->count-start_index-1;
    assert(shift_amount <= left_count);
    
    memcpy(
        (u8*)parray+(start_index-shift_amount)*h->elem_size, 
        (u8*)parray+(h->count-start_index)*h->elem_size, 
        shift_amount*h->elem_size
    );
}
void *persistent_array_shift_right(void *parray, u64 start_index, u64 shift_amount) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    assertmsg(start_index < h->count, "Index out of range");
    
    persistent_array_reserve(parray, h->count+shift_amount);
    
    memcpy(
        (u8*)parray+(start_index+shift_amount)*h->elem_size, 
        (u8*)parray+start_index*h->elem_size, 
        shift_amount*h->elem_size
    );
    
    return (u8*)parray+start_index*h->elem_size;
}
void persistent_array_pop(void *parray) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    assert(h->count > 0);
    h->count -= 1;
}
void persistent_array_swap_and_pop(void *parray, u64 index) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    persistent_array_pop(parray);
    memcpy((u8*)parray+index*h->elem_size, (u8*)parray+h->count*h->elem_size, h->elem_size);
}
s64 persistent_array_find_from_left(void *parray, void *pcompare_mem) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    for (u64 i = 0; i < h->count; i += 1) {
        if (memcmp(pcompare_mem, (u8*)parray + i*h->elem_size, h->elem_size) == 0)
            return (s64)i;
    }
    return -1;
}
s64 persistent_array_find_from_right(void *parray, void *pcompare_mem) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    for (s64 i = (s64)h->count-1; i >= 0; i -= 1) {
        if (memcmp(pcompare_mem, (u8*)parray + (u64)i*h->elem_size, h->elem_size) == 0)
            return i;
    }
    return -1;
}

void persistent_array_set_count(void *parray, u64 count) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    persistent_array_reserve(parray, count);
    h->count = count;
}

u64 persistent_array_count(void *parray) {
    return _persistent_header(parray)->count;
}

#endif // OSTD_IMPL

#endif // _MEMORY_H

/* End include: memory.h */
#endif // _MEMORY_H
#ifndef _PRINT_H

/* Begin include: print.h */
#ifndef _PRINT_H
#define _PRINT_H

#ifndef _BASE_H
#endif // _BASE_H
#ifndef _STRING_H
#endif // _STRING_H
#ifndef _MEMORY_H
#endif // _MEMORY_H
#ifndef _VAR_ARGS_H

/* Begin include: var_args.h */
#ifndef _VAR_ARGS_H
#define _VAR_ARGS_H

#ifndef _BASE_H
#endif // _BASE_H
#ifndef _STRING_H
#endif // _STRING_H

// This is C90 so we need to do some macro nonsense to be able to do any form of variadic stuff.
// It's to get slightly better var args than the standard C va_list.
/*
    To make a variadic arguments procedure:
    note the comma-swallowing "##"
    // note(charlie) comma-swallowing is a hit on #Portability

    #define do_thing(arg1, ...)\
        MAKE_WRAPPED_CALL(do_thing_impl, arg1, ##__VA_ARGS__)

    void do_thing_impl(int arg1, u64 arg_count, ...) {
        Var_Arg args[MAX_VAR_ARGS];
        get_var_args(arg_count, args);


    }
*/

#define _VA_LIST_DEFINED
#ifndef va_start
    #if (COMPILER_FLAGS & COMPILER_FLAG_MSC)
        #define va_list  char*

        #define _SLOTSIZEOF(t)  (sizeof(t))
        #define _APALIGN(t,ap)  (__alignof(t))

        #define __crt_va_start(ap, x)  ((void)(__va_start(&ap, x)))
        #define __crt_va_arg(ap, t)                                               \
        ((sizeof(t) > sizeof(uintptr) || (sizeof(t) & (sizeof(t) - 1)) != 0) \
            ? **(t**)(uintptr)((ap += sizeof(uintptr)) - sizeof(uintptr))             \
            :  *(t* )(uintptr)((ap += sizeof(uintptr)) - sizeof(uintptr)))
        #define __crt_va_end(ap)        ((void)(ap = (va_list)0))

        #define va_start __crt_va_start
        #define va_arg   __crt_va_arg
        #define va_end   __crt_va_end
        #define va_copy(destination, source) ((destination) = (source))
    #elif COMPILER_FLAGS & COMPILER_FLAG_GNU
        #define va_start __builtin_va_start
        #define va_list  __builtin_va_list
        #define va_arg   __builtin_va_arg
        #define va_end   __builtin_va_end
        #define va_copy(destination, source) __builtin_va_copy((destination), (source))
    #else
        #include <stdarg.h>
    #endif
#endif // va_start

#define get_var_args(count, pargs) do {\
    va_list va_args;\
    va_start(va_args, count);\
    \
    for (u64 i = 0; i < count; i += 1)\
        pargs[i] = *(va_arg(va_args, Var_Arg*));\
    \
    va_end(va_args);\
} while(0)

typedef struct Var_Arg {
    u64 int_val;
    float64 flt_val;
    string str_val;

    u64 size;
} Var_Arg;

#define _WRAP_VAR(x) &(Var_Arg) {sizeof((x)) >= 8 ? *(u64*)(uintptr)&(x) : sizeof((x)) >= 4 ? *(u32*)(uintptr)&(x) : sizeof((x)) >= 2 ? *(u16*)(uintptr)&(x) : *(u8*)(uintptr)&(x), sizeof((x)) >= 8 ? *(float64*)(uintptr)&(x) : sizeof((x)) >= 4 ? (float64)*(float32*)(uintptr)&(x) : 0, sizeof((x)) >= sizeof(string) ? *(string*)(uintptr)&(x) : (string){0}, sizeof((x))}


/* Begin include: var_args_macros.h */
#ifndef _VAR_ARGS_MACROS_H
#define _VAR_ARGS_MACROS_H

#define MAX_VAR_ARGS 70

#define PP_NARG(...) PP_ARG_N(__VA_ARGS__, PP_RSEQ_N())

#define PP_ARG_N(...) PP_ARG_N_(__VA_ARGS__)

#define PP_RSEQ_N() 140,139,138,137,136,135,134,133,132,131,130,129,128,127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,104,103,102,101,100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0

#define PP_ARG_N_(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127, _128, _129, _130, _131, _132, _133, _134, _135, _136, _137, _138, _139, _140, N, ...) N

#define PP_CONCATENATE(a, b) PP_CONCATENATE_(a, b)
#define PP_CONCATENATE_(a, b) a##b

#define _WRAP_ARGS_0(TARGET, FIRST) \
    TARGET(FIRST, 0)

#define _WRAP_ARGS_1(TARGET, FIRST, _0) \
	TARGET(FIRST, 1, _WRAP_VAR(_0))

#define _WRAP_ARGS_2(TARGET, FIRST, _0, _1) \
	TARGET(FIRST, 2, _WRAP_VAR(_0), _WRAP_VAR(_1))

#define _WRAP_ARGS_3(TARGET, FIRST, _0, _1, _2) \
	TARGET(FIRST, 3, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2))

#define _WRAP_ARGS_4(TARGET, FIRST, _0, _1, _2, _3) \
	TARGET(FIRST, 4, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3))

#define _WRAP_ARGS_5(TARGET, FIRST, _0, _1, _2, _3, _4) \
	TARGET(FIRST, 5, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4))

#define _WRAP_ARGS_6(TARGET, FIRST, _0, _1, _2, _3, _4, _5) \
	TARGET(FIRST, 6, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5))

#define _WRAP_ARGS_7(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6) \
	TARGET(FIRST, 7, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6))

#define _WRAP_ARGS_8(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7) \
	TARGET(FIRST, 8, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7))

#define _WRAP_ARGS_9(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
	TARGET(FIRST, 9, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8))

#define _WRAP_ARGS_10(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
	TARGET(FIRST, 10, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9))

#define _WRAP_ARGS_11(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
	TARGET(FIRST, 11, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10))

#define _WRAP_ARGS_12(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
	TARGET(FIRST, 12, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11))

#define _WRAP_ARGS_13(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
	TARGET(FIRST, 13, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12))

#define _WRAP_ARGS_14(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
	TARGET(FIRST, 14, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13))

#define _WRAP_ARGS_15(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
	TARGET(FIRST, 15, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14))

#define _WRAP_ARGS_16(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
	TARGET(FIRST, 16, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15))

#define _WRAP_ARGS_17(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
	TARGET(FIRST, 17, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16))

#define _WRAP_ARGS_18(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
	TARGET(FIRST, 18, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17))

#define _WRAP_ARGS_19(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
	TARGET(FIRST, 19, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18))

#define _WRAP_ARGS_20(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
	TARGET(FIRST, 20, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19))

#define _WRAP_ARGS_21(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) \
	TARGET(FIRST, 21, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20))

#define _WRAP_ARGS_22(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) \
	TARGET(FIRST, 22, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21))

#define _WRAP_ARGS_23(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) \
	TARGET(FIRST, 23, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22))

#define _WRAP_ARGS_24(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) \
	TARGET(FIRST, 24, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23))

#define _WRAP_ARGS_25(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) \
	TARGET(FIRST, 25, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24))

#define _WRAP_ARGS_26(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) \
	TARGET(FIRST, 26, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25))

#define _WRAP_ARGS_27(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) \
	TARGET(FIRST, 27, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26))

#define _WRAP_ARGS_28(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) \
	TARGET(FIRST, 28, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27))

#define _WRAP_ARGS_29(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) \
	TARGET(FIRST, 29, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28))

#define _WRAP_ARGS_30(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) \
	TARGET(FIRST, 30, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29))

#define _WRAP_ARGS_31(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) \
	TARGET(FIRST, 31, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30))

#define _WRAP_ARGS_32(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) \
	TARGET(FIRST, 32, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31))

#define _WRAP_ARGS_33(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) \
	TARGET(FIRST, 33, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32))

#define _WRAP_ARGS_34(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) \
	TARGET(FIRST, 34, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33))

#define _WRAP_ARGS_35(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) \
	TARGET(FIRST, 35, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34))

#define _WRAP_ARGS_36(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) \
	TARGET(FIRST, 36, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35))

#define _WRAP_ARGS_37(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) \
	TARGET(FIRST, 37, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36))

#define _WRAP_ARGS_38(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) \
	TARGET(FIRST, 38, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37))

#define _WRAP_ARGS_39(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) \
	TARGET(FIRST, 39, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38))

#define _WRAP_ARGS_40(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39) \
	TARGET(FIRST, 40, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39))

#define _WRAP_ARGS_41(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40) \
	TARGET(FIRST, 41, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40))

#define _WRAP_ARGS_42(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41) \
	TARGET(FIRST, 42, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41))

#define _WRAP_ARGS_43(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42) \
	TARGET(FIRST, 43, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42))

#define _WRAP_ARGS_44(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43) \
	TARGET(FIRST, 44, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43))

#define _WRAP_ARGS_45(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44) \
	TARGET(FIRST, 45, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44))

#define _WRAP_ARGS_46(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45) \
	TARGET(FIRST, 46, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45))

#define _WRAP_ARGS_47(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46) \
	TARGET(FIRST, 47, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46))

#define _WRAP_ARGS_48(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47) \
	TARGET(FIRST, 48, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47))

#define _WRAP_ARGS_49(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48) \
	TARGET(FIRST, 49, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48))

#define _WRAP_ARGS_50(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49) \
	TARGET(FIRST, 50, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49))

#define _WRAP_ARGS_51(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50) \
	TARGET(FIRST, 51, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50))

#define _WRAP_ARGS_52(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51) \
	TARGET(FIRST, 52, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51))

#define _WRAP_ARGS_53(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52) \
	TARGET(FIRST, 53, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52))

#define _WRAP_ARGS_54(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53) \
	TARGET(FIRST, 54, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53))

#define _WRAP_ARGS_55(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54) \
	TARGET(FIRST, 55, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54))

#define _WRAP_ARGS_56(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55) \
	TARGET(FIRST, 56, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55))

#define _WRAP_ARGS_57(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56) \
	TARGET(FIRST, 57, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56))

#define _WRAP_ARGS_58(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57) \
	TARGET(FIRST, 58, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56), _WRAP_VAR(_57))

#define _WRAP_ARGS_59(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58) \
	TARGET(FIRST, 59, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56), _WRAP_VAR(_57), _WRAP_VAR(_58))

#define _WRAP_ARGS_60(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59) \
	TARGET(FIRST, 60, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56), _WRAP_VAR(_57), _WRAP_VAR(_58), _WRAP_VAR(_59))

#define _WRAP_ARGS_61(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60) \
	TARGET(FIRST, 61, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56), _WRAP_VAR(_57), _WRAP_VAR(_58), _WRAP_VAR(_59), _WRAP_VAR(_60))

#define _WRAP_ARGS_62(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61) \
	TARGET(FIRST, 62, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56), _WRAP_VAR(_57), _WRAP_VAR(_58), _WRAP_VAR(_59), _WRAP_VAR(_60), _WRAP_VAR(_61))

#define _WRAP_ARGS_63(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62) \
	TARGET(FIRST, 63, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56), _WRAP_VAR(_57), _WRAP_VAR(_58), _WRAP_VAR(_59), _WRAP_VAR(_60), _WRAP_VAR(_61), _WRAP_VAR(_62))

#define _WRAP_ARGS_64(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63) \
	TARGET(FIRST, 64, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56), _WRAP_VAR(_57), _WRAP_VAR(_58), _WRAP_VAR(_59), _WRAP_VAR(_60), _WRAP_VAR(_61), _WRAP_VAR(_62), _WRAP_VAR(_63))

#define _WRAP_ARGS_65(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64) \
	TARGET(FIRST, 65, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56), _WRAP_VAR(_57), _WRAP_VAR(_58), _WRAP_VAR(_59), _WRAP_VAR(_60), _WRAP_VAR(_61), _WRAP_VAR(_62), _WRAP_VAR(_63), _WRAP_VAR(_64))

#define _WRAP_ARGS_66(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65) \
	TARGET(FIRST, 66, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56), _WRAP_VAR(_57), _WRAP_VAR(_58), _WRAP_VAR(_59), _WRAP_VAR(_60), _WRAP_VAR(_61), _WRAP_VAR(_62), _WRAP_VAR(_63), _WRAP_VAR(_64), _WRAP_VAR(_65))

#define _WRAP_ARGS_67(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66) \
	TARGET(FIRST, 67, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56), _WRAP_VAR(_57), _WRAP_VAR(_58), _WRAP_VAR(_59), _WRAP_VAR(_60), _WRAP_VAR(_61), _WRAP_VAR(_62), _WRAP_VAR(_63), _WRAP_VAR(_64), _WRAP_VAR(_65), _WRAP_VAR(_66))

#define _WRAP_ARGS_68(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67) \
	TARGET(FIRST, 68, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56), _WRAP_VAR(_57), _WRAP_VAR(_58), _WRAP_VAR(_59), _WRAP_VAR(_60), _WRAP_VAR(_61), _WRAP_VAR(_62), _WRAP_VAR(_63), _WRAP_VAR(_64), _WRAP_VAR(_65), _WRAP_VAR(_66), _WRAP_VAR(_67))

#define _WRAP_ARGS_69(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68) \
	TARGET(FIRST, 69, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56), _WRAP_VAR(_57), _WRAP_VAR(_58), _WRAP_VAR(_59), _WRAP_VAR(_60), _WRAP_VAR(_61), _WRAP_VAR(_62), _WRAP_VAR(_63), _WRAP_VAR(_64), _WRAP_VAR(_65), _WRAP_VAR(_66), _WRAP_VAR(_67), _WRAP_VAR(_68))

#define _WRAP_ARGS_70(TARGET, FIRST, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69) \
	TARGET(FIRST, 70, _WRAP_VAR(_0), _WRAP_VAR(_1), _WRAP_VAR(_2), _WRAP_VAR(_3), _WRAP_VAR(_4), _WRAP_VAR(_5), _WRAP_VAR(_6), _WRAP_VAR(_7), _WRAP_VAR(_8), _WRAP_VAR(_9), _WRAP_VAR(_10), _WRAP_VAR(_11), _WRAP_VAR(_12), _WRAP_VAR(_13), _WRAP_VAR(_14), _WRAP_VAR(_15), _WRAP_VAR(_16), _WRAP_VAR(_17), _WRAP_VAR(_18), _WRAP_VAR(_19), _WRAP_VAR(_20), _WRAP_VAR(_21), _WRAP_VAR(_22), _WRAP_VAR(_23), _WRAP_VAR(_24), _WRAP_VAR(_25), _WRAP_VAR(_26), _WRAP_VAR(_27), _WRAP_VAR(_28), _WRAP_VAR(_29), _WRAP_VAR(_30), _WRAP_VAR(_31), _WRAP_VAR(_32), _WRAP_VAR(_33), _WRAP_VAR(_34), _WRAP_VAR(_35), _WRAP_VAR(_36), _WRAP_VAR(_37), _WRAP_VAR(_38), _WRAP_VAR(_39), _WRAP_VAR(_40), _WRAP_VAR(_41), _WRAP_VAR(_42), _WRAP_VAR(_43), _WRAP_VAR(_44), _WRAP_VAR(_45), _WRAP_VAR(_46), _WRAP_VAR(_47), _WRAP_VAR(_48), _WRAP_VAR(_49), _WRAP_VAR(_50), _WRAP_VAR(_51), _WRAP_VAR(_52), _WRAP_VAR(_53), _WRAP_VAR(_54), _WRAP_VAR(_55), _WRAP_VAR(_56), _WRAP_VAR(_57), _WRAP_VAR(_58), _WRAP_VAR(_59), _WRAP_VAR(_60), _WRAP_VAR(_61), _WRAP_VAR(_62), _WRAP_VAR(_63), _WRAP_VAR(_64), _WRAP_VAR(_65), _WRAP_VAR(_66), _WRAP_VAR(_67), _WRAP_VAR(_68), _WRAP_VAR(_69))

#define _WRAP_ARGS_DISPATCH(N, TARGET, ...) \
    PP_CONCATENATE(_WRAP_ARGS_, N)(TARGET, __VA_ARGS__)

#define MAKE_WRAPPED_CALL(TARGET, ...) \
    _WRAP_ARGS_DISPATCH(PP_NARG(__VA_ARGS__), TARGET, __VA_ARGS__)

#endif // _VAR_ARGS_MACROS_H

/* End include: var_args_macros.h */

#endif // _VAR_ARGS_H

/* End include: var_args.h */
#endif // _VAR_ARGS_H
#ifndef _SYSTEM_1_H
#endif // _SYSTEM_1_H


/*

    TODO:

        - Specify int base
            %i16  - base 16
        - Padding, 0 padding
            %4-i   "   5"
                   "  81"
            %i-4   "5   "
                   "81  "
            %i04   "0005"
                   "0081"
        - Decimal places
            %f.3   "1.123"
            %f.5   "1.12340"

            %f04.3 "0001.123""

        - Null terminated string is %s0

        - Stack-backed buffered print() (instead of temporary allocation)


*/

//////
// Formatting
//////

#define format_string(buffer, buffer_size, /*fmt, */...)  _format_string_ugly(buffer, buffer_size, __VA_ARGS__)
#define format_strings(buffer, buffer_size, fmt, /*fmt, */...)  _format_strings_ugly(buffer, buffer_size, __VA_ARGS__)

u64 format_string_args(void *buffer, u64 buffer_size, string fmt, u64 arg_count, Var_Arg *args, u64 *consumed_args);

u64 format_signed_int(s64 x, int base, void *buffer, u64 buffer_size);
u64 format_unsigned_int(u64 x, int base, void *buffer, u64 buffer_size);
u64 format_float(float64 x, int decimal_places, void *buffer, u64 buffer_size);

u64 string_to_unsigned_int(string str, int base, bool *success);
s64 string_to_signed_int(string str, int base, bool *success);
float64 string_to_float(string str, bool *success);

//////
// Printing
//////

typedef struct Source_Location {
    u64 line;
    string file;
    string function;
} Source_Location;
#define HERE(...) (Source_Location) {__LINE__, STR(__FILE__), STR(__func__)}

#define sprint(allocator, /*fmt, */...)  _sprint_ugly(allocator, __VA_ARGS__)
#define sprints(allocator, /*fmt, */...) _sprints_ugly(allocator, __VA_ARGS__)
#define tprint(/*fmt, */...)             _tprint_ugly(__VA_ARGS__)
#define tprints(/*fmt, */...)            _tprints_ugly(__VA_ARGS__)
#define print(/*fmt, */...)              _print_ugly(__VA_ARGS__)
#define prints(/*fmt, */...)             _prints_ugly(__VA_ARGS__)
#define fprint(file, /*fmt, */...)       _fprint_ugly(file, __VA_ARGS__)
#define fprints(file, /*fmt, */...)      _fprints_ugly(file, __VA_ARGS__)

string sprint_args(Allocator a, string fmt, u64 arg_count, Var_Arg *args);
string tprint_args(string fmt, u64 arg_count, Var_Arg *args);
void   print_args(string fmt, u64 arg_count, Var_Arg *args);
void   fprint_args(File_Handle f, string fmt, u64 arg_count, Var_Arg *args);
void   log_args(u64 flags, Source_Location location, string fmt, u64 arg_count, Var_Arg *args);

typedef void (*Logger_Proc)(string message, u64 flags, Source_Location location);
extern Logger_Proc logger;

void default_logger(string message, u64 flags, Source_Location location);

#define log(flags, /*fmt, */...)              _log_ugly(flags, __VA_ARGS__)
#define logs(flags, /*fmt, */ ...)             _logs_ugly(flags, __VA_ARGS__)

//////
// Internal
//////

// note(charlie): These bloat the code and makes it less good at self-documenting,
// so I made a prettier indirection for the readable part of the file.

#define _format_string_ugly(buffer, buffer_size, ...)\
    MAKE_WRAPPED_CALL(format_string_impl, _make_format_string_desc(buffer, buffer_size, STR(PP_FIRST_ARG(__VA_ARGS__))), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _format_strings_ugly(buffer, buffer_size, ...)\
    MAKE_WRAPPED_CALL(format_string_impl, _make_format_string_desc(buffer, buffer_size, PP_FIRST_ARG(__VA_ARGS__)), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))


#define _sprint_ugly(allocator, ...)\
    MAKE_WRAPPED_CALL(sprint_impl, _make_print_desc(allocator, STR(PP_FIRST_ARG(__VA_ARGS__)), 0), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _sprints_ugly(allocator, ...)\
    MAKE_WRAPPED_CALL(sprint_impl, _make_print_desc(allocator, PP_FIRST_ARG(__VA_ARGS__), 0), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _tprint_ugly(...)\
    MAKE_WRAPPED_CALL(tprint_impl, _make_print_desc((Allocator){0}, STR(PP_FIRST_ARG(__VA_ARGS__)), 0), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _tprints_ugly(...)\
    MAKE_WRAPPED_CALL(tprint_impl, _make_print_desc((Allocator){0}, PP_FIRST_ARG(__VA_ARGS__), 0), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _print_ugly(...)\
    MAKE_WRAPPED_CALL(print_impl, _make_print_desc((Allocator){0}, STR(PP_FIRST_ARG(__VA_ARGS__)), 0), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _prints_ugly(...)\
    MAKE_WRAPPED_CALL(print_impl, _make_print_desc((Allocator){0}, PP_FIRST_ARG(__VA_ARGS__), 0), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _fprint_ugly(file, ...)\
    MAKE_WRAPPED_CALL(fprint_impl, _make_print_desc((Allocator){0}, STR(PP_FIRST_ARG(__VA_ARGS__)), file), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _fprints_ugly(file, ...)\
    MAKE_WRAPPED_CALL(fprint_impl, _make_print_desc((Allocator){0}, PP_FIRST_ARG(__VA_ARGS__), file), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))

#define _log_ugly(flags, ...)\
    MAKE_WRAPPED_CALL(log_impl, _make_log_desc((Allocator){0}, STR(PP_FIRST_ARG(__VA_ARGS__)), flags, HERE()), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _logs_ugly(flags, ...)\
    MAKE_WRAPPED_CALL(log_impl, _make_log_desc((Allocator){0}, PP_FIRST_ARG(__VA_ARGS__), flags, HERE()), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__,  (string){0}))

typedef struct _Format_String_Desc {
    void *buffer;
    u64 buffer_size;
    string fmt;
} _Format_String_Desc;
unit_local inline _Format_String_Desc _make_format_string_desc(void *buffer, u64 buffer_size, string fmt) {
    return (_Format_String_Desc) {buffer, buffer_size, fmt};
}

typedef struct _Print_Desc {
    Allocator a;
    string fmt;
    File_Handle file;
} _Print_Desc;
unit_local inline _Print_Desc _make_print_desc(Allocator a, string fmt, File_Handle f) {
    return (_Print_Desc) {a, fmt, f};
}

typedef struct _Log_Desc {
    Allocator a;
    string fmt;
    u64 flags;
    Source_Location location;
} _Log_Desc;
unit_local inline _Log_Desc _make_log_desc(Allocator a, string fmt, u64 flags, Source_Location location) {
    return (_Log_Desc) {a, fmt, flags, location};
}

u64 format_string_impl(_Format_String_Desc desc, u64 arg_count, ...);
string sprint_impl(_Print_Desc desc, u64 arg_count, ...);
string tprint_impl(_Print_Desc desc, u64 arg_count, ...);
void print_impl(_Print_Desc desc, u64 arg_count, ...);
void fprint_impl(_Print_Desc desc, u64 arg_count, ...);
void log_impl(_Log_Desc desc, u64 arg_count, ...);


// todo(charlie) move to appropriate file
string string_replace(Allocator a, string s, string sub, string new);


#ifdef OSTD_IMPL

u64 format_string_impl(_Format_String_Desc desc, u64 arg_count, ...) {
    Var_Arg args[MAX_VAR_ARGS];

    get_var_args(arg_count, args);

    return format_string_args(desc.buffer, desc.buffer_size, desc.fmt, arg_count, args, 0);
}

u64 format_string_args(void *buffer, u64 buffer_size, string fmt, u64 arg_count, Var_Arg *args, u64 *consumed_args) {

    if (!buffer) buffer_size = U64_MAX;

    u64 next_arg_index = 0;

    u64 written = 0;

    for (u64 i = 0; i < fmt.count; i += 1) {
        if (fmt.data[i] == '%' && next_arg_index < arg_count && i < fmt.count-1) {
            Var_Arg arg = args[next_arg_index];

            //u32 left_padding = 0;
            //u32 right_padding = 0;
            //u32 left_0_padding = 0;
            //u32 right_0_padding = 0;

            int base = 10;
            int decimal_places = 5;

            u8 small_str[64];
            string str = (string) { 0, small_str };

            if (fmt.data[i+1] == 'u') {
                str.count = format_unsigned_int(arg.int_val, base, str.data, 32);
                i += 1;
            } else if (fmt.data[i+1] == 'i') {
                s64 signed_val;
                if (arg.size == 1) {
                    signed_val = (s64)(*(s8*)&arg.int_val);
                } else if (arg.size == 2) {
                    signed_val = (s64)(*(s16*)&arg.int_val);
                } else if (arg.size == 4) {
                    signed_val = (s64)(*(s32*)&arg.int_val);
                } else {
                    signed_val = *(s64*)&arg.int_val;
                }
                str.count = format_signed_int(signed_val, base, str.data, 32);
                i += 1;
            } else if (fmt.data[i+1] == 'x') {
                str.count = format_unsigned_int(arg.int_val, 16, str.data, 32);
                i += 1;
            } else if (fmt.data[i+1] == 'f') {
                // todo(charlie)
                str.count = format_float(arg.flt_val, decimal_places, str.data, 32);
                i += 1;
            } else if (fmt.data[i+1] == 'b') {
                str = arg.int_val ? STR("true") : STR("false");
                i += 1;
            } else if (fmt.data[i+1] == 's') {
                str = arg.str_val;
                i += 1;
            } else {

                char msg[] = "<Unknown format specifier '  '>";
                memcpy(str.data, msg, sizeof(msg)-1);
                str.count = sizeof(msg)-1;
                str.data[str.count-4] = '%';
                str.data[str.count-3] = fmt.data[i+1];
                i += 1;
            }

            if (str.count) {
                u64 to_write = str.count;

                if (written + to_write > buffer_size) {
                    to_write -= (written + to_write) - buffer_size;
                }

                if (to_write) {
                    if (buffer) memcpy((u8*)buffer + written, str.data, (sys_uint)to_write);
                    written += str.count;
                }
            }

            if (consumed_args) (*consumed_args) += 1;

            next_arg_index += 1;
        } else {
            if (written + 1 <= buffer_size) {
                if (buffer) *((u8*)buffer + written) = fmt.data[i];
                written += 1;
            }
        }
    }

    return written;
}

string sprint_impl(_Print_Desc desc, u64 arg_count, ...) {
    Var_Arg args[MAX_VAR_ARGS];
    get_var_args(arg_count, args);
    return sprint_args(desc.a, desc.fmt, arg_count, args);
}
string tprint_impl(_Print_Desc desc, u64 arg_count, ...) {
    Var_Arg args[MAX_VAR_ARGS];
    get_var_args(arg_count, args);
    return tprint_args(desc.fmt, arg_count, args);
}
void print_impl(_Print_Desc desc, u64 arg_count, ...) {
    Var_Arg args[MAX_VAR_ARGS];
    get_var_args(arg_count, args);
    print_args(desc.fmt, arg_count, args);
}
void log_impl(_Log_Desc desc, u64 arg_count, ...) {
    Var_Arg args[MAX_VAR_ARGS];
    get_var_args(arg_count, args);
    log_args(desc.flags, desc.location, desc.fmt, arg_count, args);
}
void fprint_impl(_Print_Desc desc, u64 arg_count, ...) {
    Var_Arg args[MAX_VAR_ARGS];
    get_var_args(arg_count, args);
    fprint_args(desc.file, desc.fmt, arg_count, args);
}

string sprint_args(Allocator a, string fmt, u64 arg_count, Var_Arg *args) {
    u64 n = format_string_args(0, 0, fmt, arg_count, args, 0);

    void *buffer = allocate(a, n);

    format_string_args(buffer, n, fmt, arg_count, args, 0);

    return (string) { n, (u8*)buffer };
}
string tprint_args(string fmt, u64 arg_count, Var_Arg *args) {
    return sprint_args(get_temp(), fmt, arg_count, args);
}
void print_args(string fmt, u64 arg_count, Var_Arg *args) {
    fprint_args(sys_get_stdout(), fmt, arg_count, args);
}
void fprint_args(File_Handle f, string fmt, u64 arg_count, Var_Arg *args) {

    u64 full_size = format_string_args(0, 0, fmt, arg_count, args, 0);
    
    u8 small_buffer[KiB(16)];
    
    u8 *buffer = small_buffer;
    if (full_size > KiB(16))
        buffer = PushTempBuffer(u8, full_size);
    
    u64 written = format_string_args(buffer, full_size, fmt, arg_count, args, 0);
    
    sys_write(f, buffer, written);
}
void log_args(u64 flags, Source_Location location, string fmt, u64 arg_count, Var_Arg *args) {

    string s = tprint_args(fmt, arg_count, args);

    if (!logger) {
        default_logger(s, flags, location);
    } else {
        logger(s, flags, location);
    }
}

void default_logger(string message, u64 flags, Source_Location location) {
    (void)flags;
    print("%s:%u: %s\n", location.file, location.line, message);
}

// Keeping this here so we dont need to include entire math module for this
unit_local inline float64 ___ln64(float64 x) {
    u64 bx = *(u64 *)(&x);
    u64 ex = bx >> 52;
    s32 t = (s32)ex - 1023;
    bx = 4607182418800017408ULL | (bx & 4503599627370495ULL);
    x = *(float64 *)(&bx);
    return -1.49278 + (2.11263 + (-0.729104 + 0.10969 * x) * x) * x + 0.6931471806 * t;
}

// todo(charlie) make a less naive and slow version of this !
unit_local u64 _format_int(void *px, int base, bool _signed, void *buffer, u64 buffer_size) {
    assert(base >= 2 && base <= 36); // 0-z

    if (!buffer) buffer_size = U64_MAX;

    u8 digits[36];
    memcpy(digits, "0123456789abcdefghijklmnopqrstuvxyz", 36);

    void *tail = (u8*)buffer + buffer_size - 1;

    u64 written = 0;

    bool neg = false;

    u64 abs_val;
    if (_signed) {
        s64 signed_val = *(s64*)px;
        neg = signed_val < 0;
        // todo(charlie), this shouldnt actually generate a mul but we may want to check
        abs_val = (u64)(neg ? (signed_val*-1) : signed_val);
    }
    else {
        abs_val = *(u64*)px;
    }

    if (abs_val == 0 && written < buffer_size) {
        if (buffer) *(u8*)buffer = '0';
        return 1;
    }

    u64 digit_count = (u64)(___ln64((float64)abs_val)/___ln64((float64)base));

    u64 skip = 0;
    if (digit_count > buffer_size) {
        skip = digit_count-buffer_size+1;
    }

    while (abs_val != 0) {
        u8 digit = digits[abs_val%(u64)base];

        if (skip == 0 && written < buffer_size) {
            if (buffer) *((u8*)tail - written) = digit;
            written += 1;
        }

        abs_val /= (u64)base;
        if (skip > 0) skip -= 1;
    }

    // Write the '-' if negative number
    if (neg && written < buffer_size) {
        if (buffer) *((u8*)tail - written) = '-';
        written += 1;
    }

    // Since we wrote right-to-left, shift down to overwrite the bytes we did not touch
    if (buffer) {
        memmove(buffer, (u8*)tail - written + 1, (sys_uint)written);
    }

    return written;
}
u64 format_signed_int(s64 x, int base, void *buffer, u64 buffer_size) {
    return _format_int(&x, base, true, buffer, buffer_size);
}
u64 format_unsigned_int(u64 x, int base, void *buffer, u64 buffer_size) {
    return _format_int(&x, base, false, buffer, buffer_size);
}

u64 format_float(float64 x, int decimal_places, void *buffer, u64 buffer_size) {
    assert(decimal_places >= 0);

    if (!buffer) buffer_size = U64_MAX;

    u64 written = 0;

    bool neg = x < 0.0;
    if (neg) x = -x;

    s64 integral_part = (s64)x;
    float64 fractional_part = x - (float64)integral_part;

    written += format_signed_int(integral_part, 10, buffer, buffer_size);

    if (decimal_places > 0 && written < buffer_size) {
        if (buffer) *((u8*)buffer + written) = '.';
        written += 1;
    }

    for (int i = 0; i < decimal_places && written < buffer_size; i++) {
        fractional_part *= 10.0;
        u8 digit = (u8) fractional_part;
        fractional_part -= digit;

        *((u8*)buffer + written) = '0' + digit;
        if (buffer) written += 1;
    }

    if (neg && written < buffer_size) {
        memmove((u8*)buffer + 1, buffer, (sys_uint)written);
        *((u8*)buffer) = '-';
        if (buffer) written += 1;
    }

    return written;
}

u64 string_to_unsigned_int(string str, int base, bool *success)
{
    if (!str.data || !str.count) {
        *success = false;
        return 0;
    }
    
    u64 value = 0;
    if (base < 2 || base > 36) {
        if (success) *success = false;
        return 0;
    }
    
    u8 *p = str.data;

    while (*p == ' ' || *p == '\t' || *p == '\n' ||
           *p == '\r' || *p == '\f' || *p == '\v') {
        p++;
    }

    while (p) {
        if (p == str.data+str.count) {
            break;
        }
        u8 c = *p;

        s64 digit = -1;

        if (c >= '0' && c <= '9') {
            digit = (s64)(c - '0');
        } else if (c >= 'a' && c <= 'z') {
            digit = 10 + (s64)(c - 'a');
        } else if (c >= 'A' && c <= 'Z') {
            digit = 10 + (s64)(c - 'A');
        } else {
            if (success) *success = false;
            return 0;
        }

        if (digit < 0 || digit >= base) {
            if (success) *success = false;
            return 0;
        }

        value = (value * (u64)base) + (u64)digit;
        
        p += 1;
    }

    if (success) *success = true;
    return value;
}

s64 string_to_signed_int(string str, int base, bool *success)
{
    if (!str.data || !str.count) {
        *success = false;
        return 0;
    }
    u8 *p = str.data;

    while (*p == ' ' || *p == '\t' || *p == '\n' ||
           *p == '\r' || *p == '\f' || *p == '\v') {
        p++;
    }

    int sign = 1;
    if (*p == '-') {
        sign = -1;
        p++;
        str.data++;
        str.count--;
    } else if (*p == '+') {
        p++;
    }

    u64 unsigned_val = string_to_unsigned_int(str, base, success);

    s64 signed_val = (s64)unsigned_val;
    if (sign < 0) {
        signed_val = -signed_val;
    }

    return signed_val;
}

float64 string_to_float(string str, bool *success)
{
    u8 *p = str.data;

    while (*p == ' ' || *p == '\t' || *p == '\n' ||
           *p == '\r' || *p == '\f' || *p == '\v') {
        p++;
    }

    int sign = 1;
    if (*p == '-') {
        sign = -1;
        p++;
    } else if (*p == '+') {
        p++;
    }

    float64 value = 0.0;
    float64 fraction = 0.0;
    float64 divisor = 1.0;

    while (*p >= '0' && *p <= '9') {
        value = (value * 10.0) + (float64)(*p - '0');
        p++;
    }

    if (*p == '.') {
        p++;
        while (*p >= '0' && *p <= '9') {
            fraction = (fraction * 10.0) + (float64)(*p - '0');
            divisor *= 10.0;
            p++;
        }
    }
    
    if (p != str.data+str.count) {
        if (success) *success = false;
        return 0;
    }

    value = value + (fraction / divisor);

    if (sign < 0) {
        value = -value;
    }

    if (success) *success = true;
    return value;
}

Logger_Proc logger = 0;

// todo(charlie) move to appropriate file
// There probably needs to be a string_utilities file or something because this function needs
// the memory module, but the string module must come before the memory module because the system
// module must come before the memory module because it uses strings. 
string string_replace(Allocator a, string s, string sub, string replacement) {
    if (s.count < sub.count) return (string){0};

    string temp_string = string_allocate(get_temp(), s.count * 2);

    u64 out_index = 0;
    for (u64 i = 0; i < s.count; ) {
        if (i <= s.count - sub.count &&
            strings_match((string){.count = sub.count, .data = s.data + i}, sub)) {
            
            while (out_index + replacement.count >= temp_string.count) {
                string new_temp_string = string_allocate(get_temp(), temp_string.count * 2);
                memcpy(new_temp_string.data, temp_string.data, (sys_uint)temp_string.count);
                temp_string = new_temp_string;
            }

            if (replacement.count > 0) {
                memcpy(temp_string.data + out_index, replacement.data, (sys_uint)replacement.count);
            }
            out_index += replacement.count;
            i += sub.count;
        } else {
            while (out_index >= temp_string.count) {
                string new_temp_string = string_allocate(get_temp(), temp_string.count * 2);
                memcpy(new_temp_string.data, temp_string.data, (sys_uint)temp_string.count);
                temp_string = new_temp_string;
            }
            temp_string.data[out_index++] = s.data[i++];
        }
    }

    string final_string = string_allocate(a, out_index);
    memcpy(final_string.data, temp_string.data, (sys_uint)out_index);

    return final_string;
}


#endif // OSTD_IMPL


#endif // _PRINT_H

/* End include: print.h */
#endif // _PRINT_H

OSTD_LIB bool sys_read_entire_file(Allocator a, string path, string *result);
OSTD_LIB bool sys_write_entire_file(string path, string data);

OSTD_LIB bool sys_get_absolute_path(Allocator a, string path, string *result);

//typedef struct Disk_Entry {
//    u64 parent_index;
//    string name;
//    bool is_directory;
//} Disk_Entry;
//OSTD_LIB bool sys_scrape_disk(Allocator a, string disk_id, Disk_Entry *result, u64 *count);

#ifdef OSTD_IMPL

bool sys_read_entire_file(Allocator a, string path, string *result) {
    const int MAX_ATTEMPTS = 100;
    int attempts = MAX_ATTEMPTS;
    File_Handle f = 0;
    while (f == 0 && attempts > 0) {
        f = sys_open_file(path, FILE_OPEN_READ);
        attempts -= 1;
    }
    if (!f) return false;
    
    u64 size = sys_get_file_size(f);
    if (size == 0) {
        sys_close(f);
        return false;
    }
    
    *result = string_allocate(a, size);
    s64 readeded =  sys_read(f, result->data, result->count);
    
    if (readeded != (s64)size) {
        deallocate(a, result->data);
        sys_close(f);
        return false;
    }
    
    sys_close(f);
    
    return true;
}
bool sys_write_entire_file(string path, string data) {
    File_Handle f = sys_open_file(path, FILE_OPEN_WRITE | FILE_OPEN_CREATE | FILE_OPEN_RESET);
    if (!f) {
        sys_close(f);
        return false;
    }
    
    s64 written = sys_write_string(f, data);
    
    sys_close(f);
    return written == (s64)data.count;
}

#if OS_FLAGS & OS_FLAG_WINDOWS

bool sys_get_absolute_path(Allocator a, string path, string *result) {
    
    char *cpath = (char*)allocate(a, path.count+1);
    memcpy(cpath, path.data, path.count);
    cpath[path.count] = 0;

    DWORD count = GetFullPathNameA(cpath, 0, 0, 0);

    *result = string_allocate(a, (u64)count);
    result->count -= 1; // Null terminator

    DWORD result_count = GetFullPathNameA(cpath, count, (LPSTR)result->data, 0);
    
    return result_count == count-1;
}



#endif // WINDOWS

#if OS_FLAGS & OS_FLAG_UNIX
#endif // UNIX

#if OS_FLAGS & OS_FLAG_LINUX
#endif // LINUX

#if OS_FLAGS & OS_FLAG_ANDROID
#endif // ANDROID

#if OS_FLAGS & OS_FLAG_EMSCRIPTEN
#endif // EMSCRIPTEN

#endif // OSTD_IMPL

#endif // _SYSTEM_2_H

/* End include: system2.h */
#endif // _ONE_SYSTEM_H
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

