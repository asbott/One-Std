// This file was generated from One-Std/src/path_utils.h
// The following files were included & concatenated:
// - C:\One-Std\src\base.h
// - C:\One-Std\src\path_utils.h
// - C:\One-Std\src\string.h
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
    #define inline __inline__ __attribute__((always_inline))
    #define maybe_inline __inline__
#elif COMPILER_FLAGS & COMPILER_FLAG_MSC
    #define inline __forceinline
    #define maybe_inline __inline
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

void __cpuid(int cpuInfo[4], int function_id);
u64 __cdecl _xgetbv(unsigned int);

#if COMPILER_FLAGS & COMPILER_FLAG_MSC
#define debug_break(...) __debugbreak()
#elif COMPILER_FLAGS & COMPILER_FLAG_GNU
#define debug_break(...) __builtin_trap()
#else
#define debug_break(...) *(volatile int*)0 = 1
#endif

typedef struct string { 
    u64 count;
    u8 *data;
} string;

typedef void(*Assert_Fail_Callback)(string expr, string msg, string file, string function, u64 line);
extern Assert_Fail_Callback assert_fail_callback;
#ifdef OSTD_IMPL
Assert_Fail_Callback assert_fail_callback;
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define assertmsg_always(x, msg) assertmsgs_always(x, (STR(msg)))
#define assertmsgs_always(x, msg)  do { \
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
        if (assert_fail_callback) assert_fail_callback(STR(#x), msg, STR(__FILE__), STR(__func__), __LINE__);\
        debug_break();\
    } \
    } while(0)
#define assert_always(x) assertmsg_always(x, "")

#ifndef DISABLE_ASSERT
    #define assertmsg(x, msg) assertmsgs(x, (STR(msg)))
    #define assertmsgs(x, msg) assertmsgs_always(x, msg)
    #define assert(x) assertmsg(x, "")
#else
    #define assertmsg(x, msg) (void)(x)
    #define assertmsgs(x, msg) (void)(x)
    #define assert(x) (void)(x)
#endif

#ifndef OSTD_LIB
    #define OSTD_LIB
#endif

#ifdef OSTD_SELF_CONTAINED

    #if OS_FLAGS & OS_FLAG_WINDOWS
        #pragma comment(linker, "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
        #pragma comment(linker, "/STACK:0x100000,0x100000")
    #endif

#endif

typedef u64 unaligned_u64 __attribute__((aligned(1), may_alias));
typedef u32 unaligned_u32 __attribute__((aligned(1), may_alias));
typedef u16 unaligned_u16 __attribute__((aligned(1), may_alias));

#define JUMP_TABLE(dst, src, n) \
    case 0: break; \
    case 1: { \
        *(u8 *)((u8 *)(dst) + 0) = *(const u8 *)((const u8 *)(src) + 0); \
        break; \
    } \
    case 2: { \
        *(unaligned_u16 *)((u8 *)(dst) + 0) = *(const unaligned_u16 *)((const u8 *)(src) + 0); \
        break; \
    } \
    case 3: { \
        *(unaligned_u16 *)((u8 *)(dst) + 0) = *(const unaligned_u16 *)((const u8 *)(src) + 0); \
        *(u8 *)((u8 *)(dst) + 2) = *(const u8 *)((const u8 *)(src) + 2); \
        break; \
    } \
    case 4: { \
        *(unaligned_u32 *)((u8 *)(dst) + 0) = *(const unaligned_u32 *)((const u8 *)(src) + 0); \
        break; \
    } \
    case 5: { \
        *(unaligned_u32 *)((u8 *)(dst) + 0) = *(const unaligned_u32 *)((const u8 *)(src) + 0); \
        *(u8 *)((u8 *)(dst) + 4) = *(const u8 *)((const u8 *)(src) + 4); \
        break; \
    } \
    case 6: { \
        *(unaligned_u32 *)((u8 *)(dst) + 0) = *(const unaligned_u32 *)((const u8 *)(src) + 0); \
        *(unaligned_u16 *)((u8 *)(dst) + 4) = *(const unaligned_u16 *)((const u8 *)(src) + 4); \
        break; \
    } \
    case 7: { \
        *(unaligned_u32 *)((u8 *)(dst) + 0) = *(const unaligned_u32 *)((const u8 *)(src) + 0); \
        *(unaligned_u16 *)((u8 *)(dst) + 4) = *(const unaligned_u16 *)((const u8 *)(src) + 4); \
        *(u8 *)((u8 *)(dst) + 6) = *(const u8 *)((const u8 *)(src) + 6); \
        break; \
    } \
    case 8: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        break; \
    } \
    case 9: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(u8 *)((u8 *)(dst) + 8) = *(const u8 *)((const u8 *)(src) + 8); \
        break; \
    } \
    case 10: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u16 *)((u8 *)(dst) + 8) = *(const unaligned_u16 *)((const u8 *)(src) + 8); \
        break; \
    } \
    case 11: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u16 *)((u8 *)(dst) + 8) = *(const unaligned_u16 *)((const u8 *)(src) + 8); \
        *(u8 *)((u8 *)(dst) + 10) = *(const u8 *)((const u8 *)(src) + 10); \
        break; \
    } \
    case 12: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u32 *)((u8 *)(dst) + 8) = *(const unaligned_u32 *)((const u8 *)(src) + 8); \
        break; \
    } \
    case 13: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u32 *)((u8 *)(dst) + 8) = *(const unaligned_u32 *)((const u8 *)(src) + 8); \
        *(u8 *)((u8 *)(dst) + 12) = *(const u8 *)((const u8 *)(src) + 12); \
        break; \
    } \
    case 14: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 6) = *(const unaligned_u64 *)((const u8 *)(src) + 6); \
        break; \
    } \
    case 15: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 7) = *(const unaligned_u64 *)((const u8 *)(src) + 7); \
        break; \
    } \
    case 16: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        break; \
    } \
    case 17: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(u8 *)((u8 *)(dst) + 16) = *(const u8 *)((const u8 *)(src) + 16); \
        break; \
    } \
    case 18: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u16 *)((u8 *)(dst) + 16) = *(const unaligned_u16 *)((const u8 *)(src) + 16); \
        break; \
    } \
    case 19: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u32 *)((u8 *)(dst) + 15) = *(const unaligned_u32 *)((const u8 *)(src) + 15); \
        break; \
    } \
    case 20: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u32 *)((u8 *)(dst) + 16) = *(const unaligned_u32 *)((const u8 *)(src) + 16); \
        break; \
    } \
    case 21: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u32 *)((u8 *)(dst) + 16) = *(const unaligned_u32 *)((const u8 *)(src) + 16); \
        *(u8 *)((u8 *)(dst) + 20) = *(const u8 *)((const u8 *)(src) + 20); \
        break; \
    } \
    case 22: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u32 *)((u8 *)(dst) + 16) = *(const unaligned_u32 *)((const u8 *)(src) + 16); \
        *(unaligned_u16 *)((u8 *)(dst) + 20) = *(const unaligned_u16 *)((const u8 *)(src) + 20); \
        break; \
    } \
    case 23: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 15) = *(const unaligned_u64 *)((const u8 *)(src) + 15); \
        break; \
    } \
    case 24: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        break; \
    } \
    case 25: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(u8 *)((u8 *)(dst) + 24) = *(const u8 *)((const u8 *)(src) + 24); \
        break; \
    } \
    case 26: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u16 *)((u8 *)(dst) + 24) = *(const unaligned_u16 *)((const u8 *)(src) + 24); \
        break; \
    } \
    case 27: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u32 *)((u8 *)(dst) + 23) = *(const unaligned_u32 *)((const u8 *)(src) + 23); \
        break; \
    } \
    case 28: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u32 *)((u8 *)(dst) + 24) = *(const unaligned_u32 *)((const u8 *)(src) + 24); \
        break; \
    } \
    case 29: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 21) = *(const unaligned_u64 *)((const u8 *)(src) + 21); \
        break; \
    } \
    case 30: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 22) = *(const unaligned_u64 *)((const u8 *)(src) + 22); \
        break; \
    } \
    case 31: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 23) = *(const unaligned_u64 *)((const u8 *)(src) + 23); \
        break; \
    } \
    case 32: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        break; \
    } \
    case 33: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 1) = *(const unaligned_u64 *)((const u8 *)(src) + 1); \
        *(unaligned_u64 *)((u8 *)(dst) + 9) = *(const unaligned_u64 *)((const u8 *)(src) + 9); \
        *(unaligned_u64 *)((u8 *)(dst) + 17) = *(const unaligned_u64 *)((const u8 *)(src) + 17); \
        *(unaligned_u64 *)((u8 *)(dst) + 25) = *(const unaligned_u64 *)((const u8 *)(src) + 25); \
        break; \
    } \
    case 34: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 2) = *(const unaligned_u64 *)((const u8 *)(src) + 2); \
        *(unaligned_u64 *)((u8 *)(dst) + 10) = *(const unaligned_u64 *)((const u8 *)(src) + 10); \
        *(unaligned_u64 *)((u8 *)(dst) + 18) = *(const unaligned_u64 *)((const u8 *)(src) + 18); \
        *(unaligned_u64 *)((u8 *)(dst) + 26) = *(const unaligned_u64 *)((const u8 *)(src) + 26); \
        break; \
    } \
    case 35: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 3) = *(const unaligned_u64 *)((const u8 *)(src) + 3); \
        *(unaligned_u64 *)((u8 *)(dst) + 11) = *(const unaligned_u64 *)((const u8 *)(src) + 11); \
        *(unaligned_u64 *)((u8 *)(dst) + 19) = *(const unaligned_u64 *)((const u8 *)(src) + 19); \
        *(unaligned_u64 *)((u8 *)(dst) + 27) = *(const unaligned_u64 *)((const u8 *)(src) + 27); \
        break; \
    } \
    case 36: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 4) = *(const unaligned_u64 *)((const u8 *)(src) + 4); \
        *(unaligned_u64 *)((u8 *)(dst) + 12) = *(const unaligned_u64 *)((const u8 *)(src) + 12); \
        *(unaligned_u64 *)((u8 *)(dst) + 20) = *(const unaligned_u64 *)((const u8 *)(src) + 20); \
        *(unaligned_u64 *)((u8 *)(dst) + 28) = *(const unaligned_u64 *)((const u8 *)(src) + 28); \
        break; \
    } \
    case 37: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 5) = *(const unaligned_u64 *)((const u8 *)(src) + 5); \
        *(unaligned_u64 *)((u8 *)(dst) + 13) = *(const unaligned_u64 *)((const u8 *)(src) + 13); \
        *(unaligned_u64 *)((u8 *)(dst) + 21) = *(const unaligned_u64 *)((const u8 *)(src) + 21); \
        *(unaligned_u64 *)((u8 *)(dst) + 29) = *(const unaligned_u64 *)((const u8 *)(src) + 29); \
        break; \
    } \
    case 38: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 6) = *(const unaligned_u64 *)((const u8 *)(src) + 6); \
        *(unaligned_u64 *)((u8 *)(dst) + 14) = *(const unaligned_u64 *)((const u8 *)(src) + 14); \
        *(unaligned_u64 *)((u8 *)(dst) + 22) = *(const unaligned_u64 *)((const u8 *)(src) + 22); \
        *(unaligned_u64 *)((u8 *)(dst) + 30) = *(const unaligned_u64 *)((const u8 *)(src) + 30); \
        break; \
    } \
    case 39: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 7) = *(const unaligned_u64 *)((const u8 *)(src) + 7); \
        *(unaligned_u64 *)((u8 *)(dst) + 15) = *(const unaligned_u64 *)((const u8 *)(src) + 15); \
        *(unaligned_u64 *)((u8 *)(dst) + 23) = *(const unaligned_u64 *)((const u8 *)(src) + 23); \
        *(unaligned_u64 *)((u8 *)(dst) + 31) = *(const unaligned_u64 *)((const u8 *)(src) + 31); \
        break; \
    } \
    case 40: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        break; \
    } \
    case 41: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 9) = *(const unaligned_u64 *)((const u8 *)(src) + 9); \
        *(unaligned_u64 *)((u8 *)(dst) + 17) = *(const unaligned_u64 *)((const u8 *)(src) + 17); \
        *(unaligned_u64 *)((u8 *)(dst) + 25) = *(const unaligned_u64 *)((const u8 *)(src) + 25); \
        *(unaligned_u64 *)((u8 *)(dst) + 33) = *(const unaligned_u64 *)((const u8 *)(src) + 33); \
        break; \
    } \
    case 42: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 10) = *(const unaligned_u64 *)((const u8 *)(src) + 10); \
        *(unaligned_u64 *)((u8 *)(dst) + 18) = *(const unaligned_u64 *)((const u8 *)(src) + 18); \
        *(unaligned_u64 *)((u8 *)(dst) + 26) = *(const unaligned_u64 *)((const u8 *)(src) + 26); \
        *(unaligned_u64 *)((u8 *)(dst) + 34) = *(const unaligned_u64 *)((const u8 *)(src) + 34); \
        break; \
    } \
    case 43: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 11) = *(const unaligned_u64 *)((const u8 *)(src) + 11); \
        *(unaligned_u64 *)((u8 *)(dst) + 19) = *(const unaligned_u64 *)((const u8 *)(src) + 19); \
        *(unaligned_u64 *)((u8 *)(dst) + 27) = *(const unaligned_u64 *)((const u8 *)(src) + 27); \
        *(unaligned_u64 *)((u8 *)(dst) + 35) = *(const unaligned_u64 *)((const u8 *)(src) + 35); \
        break; \
    } \
    case 44: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 12) = *(const unaligned_u64 *)((const u8 *)(src) + 12); \
        *(unaligned_u64 *)((u8 *)(dst) + 20) = *(const unaligned_u64 *)((const u8 *)(src) + 20); \
        *(unaligned_u64 *)((u8 *)(dst) + 28) = *(const unaligned_u64 *)((const u8 *)(src) + 28); \
        *(unaligned_u64 *)((u8 *)(dst) + 36) = *(const unaligned_u64 *)((const u8 *)(src) + 36); \
        break; \
    } \
    case 45: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 13) = *(const unaligned_u64 *)((const u8 *)(src) + 13); \
        *(unaligned_u64 *)((u8 *)(dst) + 21) = *(const unaligned_u64 *)((const u8 *)(src) + 21); \
        *(unaligned_u64 *)((u8 *)(dst) + 29) = *(const unaligned_u64 *)((const u8 *)(src) + 29); \
        *(unaligned_u64 *)((u8 *)(dst) + 37) = *(const unaligned_u64 *)((const u8 *)(src) + 37); \
        break; \
    } \
    case 46: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 14) = *(const unaligned_u64 *)((const u8 *)(src) + 14); \
        *(unaligned_u64 *)((u8 *)(dst) + 22) = *(const unaligned_u64 *)((const u8 *)(src) + 22); \
        *(unaligned_u64 *)((u8 *)(dst) + 30) = *(const unaligned_u64 *)((const u8 *)(src) + 30); \
        *(unaligned_u64 *)((u8 *)(dst) + 38) = *(const unaligned_u64 *)((const u8 *)(src) + 38); \
        break; \
    } \
    case 47: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 15) = *(const unaligned_u64 *)((const u8 *)(src) + 15); \
        *(unaligned_u64 *)((u8 *)(dst) + 23) = *(const unaligned_u64 *)((const u8 *)(src) + 23); \
        *(unaligned_u64 *)((u8 *)(dst) + 31) = *(const unaligned_u64 *)((const u8 *)(src) + 31); \
        *(unaligned_u64 *)((u8 *)(dst) + 39) = *(const unaligned_u64 *)((const u8 *)(src) + 39); \
        break; \
    } \
    case 48: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        break; \
    } \
    case 49: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 17) = *(const unaligned_u64 *)((const u8 *)(src) + 17); \
        *(unaligned_u64 *)((u8 *)(dst) + 25) = *(const unaligned_u64 *)((const u8 *)(src) + 25); \
        *(unaligned_u64 *)((u8 *)(dst) + 33) = *(const unaligned_u64 *)((const u8 *)(src) + 33); \
        *(unaligned_u64 *)((u8 *)(dst) + 41) = *(const unaligned_u64 *)((const u8 *)(src) + 41); \
        break; \
    } \
    case 50: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 18) = *(const unaligned_u64 *)((const u8 *)(src) + 18); \
        *(unaligned_u64 *)((u8 *)(dst) + 26) = *(const unaligned_u64 *)((const u8 *)(src) + 26); \
        *(unaligned_u64 *)((u8 *)(dst) + 34) = *(const unaligned_u64 *)((const u8 *)(src) + 34); \
        *(unaligned_u64 *)((u8 *)(dst) + 42) = *(const unaligned_u64 *)((const u8 *)(src) + 42); \
        break; \
    } \
    case 51: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 19) = *(const unaligned_u64 *)((const u8 *)(src) + 19); \
        *(unaligned_u64 *)((u8 *)(dst) + 27) = *(const unaligned_u64 *)((const u8 *)(src) + 27); \
        *(unaligned_u64 *)((u8 *)(dst) + 35) = *(const unaligned_u64 *)((const u8 *)(src) + 35); \
        *(unaligned_u64 *)((u8 *)(dst) + 43) = *(const unaligned_u64 *)((const u8 *)(src) + 43); \
        break; \
    } \
    case 52: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 20) = *(const unaligned_u64 *)((const u8 *)(src) + 20); \
        *(unaligned_u64 *)((u8 *)(dst) + 28) = *(const unaligned_u64 *)((const u8 *)(src) + 28); \
        *(unaligned_u64 *)((u8 *)(dst) + 36) = *(const unaligned_u64 *)((const u8 *)(src) + 36); \
        *(unaligned_u64 *)((u8 *)(dst) + 44) = *(const unaligned_u64 *)((const u8 *)(src) + 44); \
        break; \
    } \
    case 53: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 21) = *(const unaligned_u64 *)((const u8 *)(src) + 21); \
        *(unaligned_u64 *)((u8 *)(dst) + 29) = *(const unaligned_u64 *)((const u8 *)(src) + 29); \
        *(unaligned_u64 *)((u8 *)(dst) + 37) = *(const unaligned_u64 *)((const u8 *)(src) + 37); \
        *(unaligned_u64 *)((u8 *)(dst) + 45) = *(const unaligned_u64 *)((const u8 *)(src) + 45); \
        break; \
    } \
    case 54: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 22) = *(const unaligned_u64 *)((const u8 *)(src) + 22); \
        *(unaligned_u64 *)((u8 *)(dst) + 30) = *(const unaligned_u64 *)((const u8 *)(src) + 30); \
        *(unaligned_u64 *)((u8 *)(dst) + 38) = *(const unaligned_u64 *)((const u8 *)(src) + 38); \
        *(unaligned_u64 *)((u8 *)(dst) + 46) = *(const unaligned_u64 *)((const u8 *)(src) + 46); \
        break; \
    } \
    case 55: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 23) = *(const unaligned_u64 *)((const u8 *)(src) + 23); \
        *(unaligned_u64 *)((u8 *)(dst) + 31) = *(const unaligned_u64 *)((const u8 *)(src) + 31); \
        *(unaligned_u64 *)((u8 *)(dst) + 39) = *(const unaligned_u64 *)((const u8 *)(src) + 39); \
        *(unaligned_u64 *)((u8 *)(dst) + 47) = *(const unaligned_u64 *)((const u8 *)(src) + 47); \
        break; \
    } \
    case 56: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        break; \
    } \
    case 57: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 25) = *(const unaligned_u64 *)((const u8 *)(src) + 25); \
        *(unaligned_u64 *)((u8 *)(dst) + 33) = *(const unaligned_u64 *)((const u8 *)(src) + 33); \
        *(unaligned_u64 *)((u8 *)(dst) + 41) = *(const unaligned_u64 *)((const u8 *)(src) + 41); \
        *(unaligned_u64 *)((u8 *)(dst) + 49) = *(const unaligned_u64 *)((const u8 *)(src) + 49); \
        break; \
    } \
    case 58: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 26) = *(const unaligned_u64 *)((const u8 *)(src) + 26); \
        *(unaligned_u64 *)((u8 *)(dst) + 34) = *(const unaligned_u64 *)((const u8 *)(src) + 34); \
        *(unaligned_u64 *)((u8 *)(dst) + 42) = *(const unaligned_u64 *)((const u8 *)(src) + 42); \
        *(unaligned_u64 *)((u8 *)(dst) + 50) = *(const unaligned_u64 *)((const u8 *)(src) + 50); \
        break; \
    } \
    case 59: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 27) = *(const unaligned_u64 *)((const u8 *)(src) + 27); \
        *(unaligned_u64 *)((u8 *)(dst) + 35) = *(const unaligned_u64 *)((const u8 *)(src) + 35); \
        *(unaligned_u64 *)((u8 *)(dst) + 43) = *(const unaligned_u64 *)((const u8 *)(src) + 43); \
        *(unaligned_u64 *)((u8 *)(dst) + 51) = *(const unaligned_u64 *)((const u8 *)(src) + 51); \
        break; \
    } \
    case 60: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 28) = *(const unaligned_u64 *)((const u8 *)(src) + 28); \
        *(unaligned_u64 *)((u8 *)(dst) + 36) = *(const unaligned_u64 *)((const u8 *)(src) + 36); \
        *(unaligned_u64 *)((u8 *)(dst) + 44) = *(const unaligned_u64 *)((const u8 *)(src) + 44); \
        *(unaligned_u64 *)((u8 *)(dst) + 52) = *(const unaligned_u64 *)((const u8 *)(src) + 52); \
        break; \
    } \
    case 61: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 29) = *(const unaligned_u64 *)((const u8 *)(src) + 29); \
        *(unaligned_u64 *)((u8 *)(dst) + 37) = *(const unaligned_u64 *)((const u8 *)(src) + 37); \
        *(unaligned_u64 *)((u8 *)(dst) + 45) = *(const unaligned_u64 *)((const u8 *)(src) + 45); \
        *(unaligned_u64 *)((u8 *)(dst) + 53) = *(const unaligned_u64 *)((const u8 *)(src) + 53); \
        break; \
    } \
    case 62: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 30) = *(const unaligned_u64 *)((const u8 *)(src) + 30); \
        *(unaligned_u64 *)((u8 *)(dst) + 38) = *(const unaligned_u64 *)((const u8 *)(src) + 38); \
        *(unaligned_u64 *)((u8 *)(dst) + 46) = *(const unaligned_u64 *)((const u8 *)(src) + 46); \
        *(unaligned_u64 *)((u8 *)(dst) + 54) = *(const unaligned_u64 *)((const u8 *)(src) + 54); \
        break; \
    } \
    case 63: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 31) = *(const unaligned_u64 *)((const u8 *)(src) + 31); \
        *(unaligned_u64 *)((u8 *)(dst) + 39) = *(const unaligned_u64 *)((const u8 *)(src) + 39); \
        *(unaligned_u64 *)((u8 *)(dst) + 47) = *(const unaligned_u64 *)((const u8 *)(src) + 47); \
        *(unaligned_u64 *)((u8 *)(dst) + 55) = *(const unaligned_u64 *)((const u8 *)(src) + 55); \
        break; \
    } \
    case 64: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        break; \
    } \
    case 65: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 33) = *(const unaligned_u64 *)((const u8 *)(src) + 33); \
        *(unaligned_u64 *)((u8 *)(dst) + 41) = *(const unaligned_u64 *)((const u8 *)(src) + 41); \
        *(unaligned_u64 *)((u8 *)(dst) + 49) = *(const unaligned_u64 *)((const u8 *)(src) + 49); \
        *(unaligned_u64 *)((u8 *)(dst) + 57) = *(const unaligned_u64 *)((const u8 *)(src) + 57); \
        break; \
    } \
    case 66: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 34) = *(const unaligned_u64 *)((const u8 *)(src) + 34); \
        *(unaligned_u64 *)((u8 *)(dst) + 42) = *(const unaligned_u64 *)((const u8 *)(src) + 42); \
        *(unaligned_u64 *)((u8 *)(dst) + 50) = *(const unaligned_u64 *)((const u8 *)(src) + 50); \
        *(unaligned_u64 *)((u8 *)(dst) + 58) = *(const unaligned_u64 *)((const u8 *)(src) + 58); \
        break; \
    } \
    case 67: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 35) = *(const unaligned_u64 *)((const u8 *)(src) + 35); \
        *(unaligned_u64 *)((u8 *)(dst) + 43) = *(const unaligned_u64 *)((const u8 *)(src) + 43); \
        *(unaligned_u64 *)((u8 *)(dst) + 51) = *(const unaligned_u64 *)((const u8 *)(src) + 51); \
        *(unaligned_u64 *)((u8 *)(dst) + 59) = *(const unaligned_u64 *)((const u8 *)(src) + 59); \
        break; \
    } \
    case 68: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 36) = *(const unaligned_u64 *)((const u8 *)(src) + 36); \
        *(unaligned_u64 *)((u8 *)(dst) + 44) = *(const unaligned_u64 *)((const u8 *)(src) + 44); \
        *(unaligned_u64 *)((u8 *)(dst) + 52) = *(const unaligned_u64 *)((const u8 *)(src) + 52); \
        *(unaligned_u64 *)((u8 *)(dst) + 60) = *(const unaligned_u64 *)((const u8 *)(src) + 60); \
        break; \
    } \
    case 69: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 37) = *(const unaligned_u64 *)((const u8 *)(src) + 37); \
        *(unaligned_u64 *)((u8 *)(dst) + 45) = *(const unaligned_u64 *)((const u8 *)(src) + 45); \
        *(unaligned_u64 *)((u8 *)(dst) + 53) = *(const unaligned_u64 *)((const u8 *)(src) + 53); \
        *(unaligned_u64 *)((u8 *)(dst) + 61) = *(const unaligned_u64 *)((const u8 *)(src) + 61); \
        break; \
    } \
    case 70: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 38) = *(const unaligned_u64 *)((const u8 *)(src) + 38); \
        *(unaligned_u64 *)((u8 *)(dst) + 46) = *(const unaligned_u64 *)((const u8 *)(src) + 46); \
        *(unaligned_u64 *)((u8 *)(dst) + 54) = *(const unaligned_u64 *)((const u8 *)(src) + 54); \
        *(unaligned_u64 *)((u8 *)(dst) + 62) = *(const unaligned_u64 *)((const u8 *)(src) + 62); \
        break; \
    } \
    case 71: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 39) = *(const unaligned_u64 *)((const u8 *)(src) + 39); \
        *(unaligned_u64 *)((u8 *)(dst) + 47) = *(const unaligned_u64 *)((const u8 *)(src) + 47); \
        *(unaligned_u64 *)((u8 *)(dst) + 55) = *(const unaligned_u64 *)((const u8 *)(src) + 55); \
        *(unaligned_u64 *)((u8 *)(dst) + 63) = *(const unaligned_u64 *)((const u8 *)(src) + 63); \
        break; \
    } \
    case 72: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        break; \
    } \
    case 73: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 41) = *(const unaligned_u64 *)((const u8 *)(src) + 41); \
        *(unaligned_u64 *)((u8 *)(dst) + 49) = *(const unaligned_u64 *)((const u8 *)(src) + 49); \
        *(unaligned_u64 *)((u8 *)(dst) + 57) = *(const unaligned_u64 *)((const u8 *)(src) + 57); \
        *(unaligned_u64 *)((u8 *)(dst) + 65) = *(const unaligned_u64 *)((const u8 *)(src) + 65); \
        break; \
    } \
    case 74: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 42) = *(const unaligned_u64 *)((const u8 *)(src) + 42); \
        *(unaligned_u64 *)((u8 *)(dst) + 50) = *(const unaligned_u64 *)((const u8 *)(src) + 50); \
        *(unaligned_u64 *)((u8 *)(dst) + 58) = *(const unaligned_u64 *)((const u8 *)(src) + 58); \
        *(unaligned_u64 *)((u8 *)(dst) + 66) = *(const unaligned_u64 *)((const u8 *)(src) + 66); \
        break; \
    } \
    case 75: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 43) = *(const unaligned_u64 *)((const u8 *)(src) + 43); \
        *(unaligned_u64 *)((u8 *)(dst) + 51) = *(const unaligned_u64 *)((const u8 *)(src) + 51); \
        *(unaligned_u64 *)((u8 *)(dst) + 59) = *(const unaligned_u64 *)((const u8 *)(src) + 59); \
        *(unaligned_u64 *)((u8 *)(dst) + 67) = *(const unaligned_u64 *)((const u8 *)(src) + 67); \
        break; \
    } \
    case 76: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 44) = *(const unaligned_u64 *)((const u8 *)(src) + 44); \
        *(unaligned_u64 *)((u8 *)(dst) + 52) = *(const unaligned_u64 *)((const u8 *)(src) + 52); \
        *(unaligned_u64 *)((u8 *)(dst) + 60) = *(const unaligned_u64 *)((const u8 *)(src) + 60); \
        *(unaligned_u64 *)((u8 *)(dst) + 68) = *(const unaligned_u64 *)((const u8 *)(src) + 68); \
        break; \
    } \
    case 77: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 45) = *(const unaligned_u64 *)((const u8 *)(src) + 45); \
        *(unaligned_u64 *)((u8 *)(dst) + 53) = *(const unaligned_u64 *)((const u8 *)(src) + 53); \
        *(unaligned_u64 *)((u8 *)(dst) + 61) = *(const unaligned_u64 *)((const u8 *)(src) + 61); \
        *(unaligned_u64 *)((u8 *)(dst) + 69) = *(const unaligned_u64 *)((const u8 *)(src) + 69); \
        break; \
    } \
    case 78: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 46) = *(const unaligned_u64 *)((const u8 *)(src) + 46); \
        *(unaligned_u64 *)((u8 *)(dst) + 54) = *(const unaligned_u64 *)((const u8 *)(src) + 54); \
        *(unaligned_u64 *)((u8 *)(dst) + 62) = *(const unaligned_u64 *)((const u8 *)(src) + 62); \
        *(unaligned_u64 *)((u8 *)(dst) + 70) = *(const unaligned_u64 *)((const u8 *)(src) + 70); \
        break; \
    } \
    case 79: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 47) = *(const unaligned_u64 *)((const u8 *)(src) + 47); \
        *(unaligned_u64 *)((u8 *)(dst) + 55) = *(const unaligned_u64 *)((const u8 *)(src) + 55); \
        *(unaligned_u64 *)((u8 *)(dst) + 63) = *(const unaligned_u64 *)((const u8 *)(src) + 63); \
        *(unaligned_u64 *)((u8 *)(dst) + 71) = *(const unaligned_u64 *)((const u8 *)(src) + 71); \
        break; \
    } \
    case 80: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        break; \
    } \
    case 81: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 49) = *(const unaligned_u64 *)((const u8 *)(src) + 49); \
        *(unaligned_u64 *)((u8 *)(dst) + 57) = *(const unaligned_u64 *)((const u8 *)(src) + 57); \
        *(unaligned_u64 *)((u8 *)(dst) + 65) = *(const unaligned_u64 *)((const u8 *)(src) + 65); \
        *(unaligned_u64 *)((u8 *)(dst) + 73) = *(const unaligned_u64 *)((const u8 *)(src) + 73); \
        break; \
    } \
    case 82: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 50) = *(const unaligned_u64 *)((const u8 *)(src) + 50); \
        *(unaligned_u64 *)((u8 *)(dst) + 58) = *(const unaligned_u64 *)((const u8 *)(src) + 58); \
        *(unaligned_u64 *)((u8 *)(dst) + 66) = *(const unaligned_u64 *)((const u8 *)(src) + 66); \
        *(unaligned_u64 *)((u8 *)(dst) + 74) = *(const unaligned_u64 *)((const u8 *)(src) + 74); \
        break; \
    } \
    case 83: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 51) = *(const unaligned_u64 *)((const u8 *)(src) + 51); \
        *(unaligned_u64 *)((u8 *)(dst) + 59) = *(const unaligned_u64 *)((const u8 *)(src) + 59); \
        *(unaligned_u64 *)((u8 *)(dst) + 67) = *(const unaligned_u64 *)((const u8 *)(src) + 67); \
        *(unaligned_u64 *)((u8 *)(dst) + 75) = *(const unaligned_u64 *)((const u8 *)(src) + 75); \
        break; \
    } \
    case 84: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 52) = *(const unaligned_u64 *)((const u8 *)(src) + 52); \
        *(unaligned_u64 *)((u8 *)(dst) + 60) = *(const unaligned_u64 *)((const u8 *)(src) + 60); \
        *(unaligned_u64 *)((u8 *)(dst) + 68) = *(const unaligned_u64 *)((const u8 *)(src) + 68); \
        *(unaligned_u64 *)((u8 *)(dst) + 76) = *(const unaligned_u64 *)((const u8 *)(src) + 76); \
        break; \
    } \
    case 85: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 53) = *(const unaligned_u64 *)((const u8 *)(src) + 53); \
        *(unaligned_u64 *)((u8 *)(dst) + 61) = *(const unaligned_u64 *)((const u8 *)(src) + 61); \
        *(unaligned_u64 *)((u8 *)(dst) + 69) = *(const unaligned_u64 *)((const u8 *)(src) + 69); \
        *(unaligned_u64 *)((u8 *)(dst) + 77) = *(const unaligned_u64 *)((const u8 *)(src) + 77); \
        break; \
    } \
    case 86: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 54) = *(const unaligned_u64 *)((const u8 *)(src) + 54); \
        *(unaligned_u64 *)((u8 *)(dst) + 62) = *(const unaligned_u64 *)((const u8 *)(src) + 62); \
        *(unaligned_u64 *)((u8 *)(dst) + 70) = *(const unaligned_u64 *)((const u8 *)(src) + 70); \
        *(unaligned_u64 *)((u8 *)(dst) + 78) = *(const unaligned_u64 *)((const u8 *)(src) + 78); \
        break; \
    } \
    case 87: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 55) = *(const unaligned_u64 *)((const u8 *)(src) + 55); \
        *(unaligned_u64 *)((u8 *)(dst) + 63) = *(const unaligned_u64 *)((const u8 *)(src) + 63); \
        *(unaligned_u64 *)((u8 *)(dst) + 71) = *(const unaligned_u64 *)((const u8 *)(src) + 71); \
        *(unaligned_u64 *)((u8 *)(dst) + 79) = *(const unaligned_u64 *)((const u8 *)(src) + 79); \
        break; \
    } \
    case 88: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        break; \
    } \
    case 89: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 57) = *(const unaligned_u64 *)((const u8 *)(src) + 57); \
        *(unaligned_u64 *)((u8 *)(dst) + 65) = *(const unaligned_u64 *)((const u8 *)(src) + 65); \
        *(unaligned_u64 *)((u8 *)(dst) + 73) = *(const unaligned_u64 *)((const u8 *)(src) + 73); \
        *(unaligned_u64 *)((u8 *)(dst) + 81) = *(const unaligned_u64 *)((const u8 *)(src) + 81); \
        break; \
    } \
    case 90: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 58) = *(const unaligned_u64 *)((const u8 *)(src) + 58); \
        *(unaligned_u64 *)((u8 *)(dst) + 66) = *(const unaligned_u64 *)((const u8 *)(src) + 66); \
        *(unaligned_u64 *)((u8 *)(dst) + 74) = *(const unaligned_u64 *)((const u8 *)(src) + 74); \
        *(unaligned_u64 *)((u8 *)(dst) + 82) = *(const unaligned_u64 *)((const u8 *)(src) + 82); \
        break; \
    } \
    case 91: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 59) = *(const unaligned_u64 *)((const u8 *)(src) + 59); \
        *(unaligned_u64 *)((u8 *)(dst) + 67) = *(const unaligned_u64 *)((const u8 *)(src) + 67); \
        *(unaligned_u64 *)((u8 *)(dst) + 75) = *(const unaligned_u64 *)((const u8 *)(src) + 75); \
        *(unaligned_u64 *)((u8 *)(dst) + 83) = *(const unaligned_u64 *)((const u8 *)(src) + 83); \
        break; \
    } \
    case 92: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 60) = *(const unaligned_u64 *)((const u8 *)(src) + 60); \
        *(unaligned_u64 *)((u8 *)(dst) + 68) = *(const unaligned_u64 *)((const u8 *)(src) + 68); \
        *(unaligned_u64 *)((u8 *)(dst) + 76) = *(const unaligned_u64 *)((const u8 *)(src) + 76); \
        *(unaligned_u64 *)((u8 *)(dst) + 84) = *(const unaligned_u64 *)((const u8 *)(src) + 84); \
        break; \
    } \
    case 93: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 61) = *(const unaligned_u64 *)((const u8 *)(src) + 61); \
        *(unaligned_u64 *)((u8 *)(dst) + 69) = *(const unaligned_u64 *)((const u8 *)(src) + 69); \
        *(unaligned_u64 *)((u8 *)(dst) + 77) = *(const unaligned_u64 *)((const u8 *)(src) + 77); \
        *(unaligned_u64 *)((u8 *)(dst) + 85) = *(const unaligned_u64 *)((const u8 *)(src) + 85); \
        break; \
    } \
    case 94: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 62) = *(const unaligned_u64 *)((const u8 *)(src) + 62); \
        *(unaligned_u64 *)((u8 *)(dst) + 70) = *(const unaligned_u64 *)((const u8 *)(src) + 70); \
        *(unaligned_u64 *)((u8 *)(dst) + 78) = *(const unaligned_u64 *)((const u8 *)(src) + 78); \
        *(unaligned_u64 *)((u8 *)(dst) + 86) = *(const unaligned_u64 *)((const u8 *)(src) + 86); \
        break; \
    } \
    case 95: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 63) = *(const unaligned_u64 *)((const u8 *)(src) + 63); \
        *(unaligned_u64 *)((u8 *)(dst) + 71) = *(const unaligned_u64 *)((const u8 *)(src) + 71); \
        *(unaligned_u64 *)((u8 *)(dst) + 79) = *(const unaligned_u64 *)((const u8 *)(src) + 79); \
        *(unaligned_u64 *)((u8 *)(dst) + 87) = *(const unaligned_u64 *)((const u8 *)(src) + 87); \
        break; \
    } \
    case 96: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        break; \
    } \
    case 97: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 65) = *(const unaligned_u64 *)((const u8 *)(src) + 65); \
        *(unaligned_u64 *)((u8 *)(dst) + 73) = *(const unaligned_u64 *)((const u8 *)(src) + 73); \
        *(unaligned_u64 *)((u8 *)(dst) + 81) = *(const unaligned_u64 *)((const u8 *)(src) + 81); \
        *(unaligned_u64 *)((u8 *)(dst) + 89) = *(const unaligned_u64 *)((const u8 *)(src) + 89); \
        break; \
    } \
    case 98: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 66) = *(const unaligned_u64 *)((const u8 *)(src) + 66); \
        *(unaligned_u64 *)((u8 *)(dst) + 74) = *(const unaligned_u64 *)((const u8 *)(src) + 74); \
        *(unaligned_u64 *)((u8 *)(dst) + 82) = *(const unaligned_u64 *)((const u8 *)(src) + 82); \
        *(unaligned_u64 *)((u8 *)(dst) + 90) = *(const unaligned_u64 *)((const u8 *)(src) + 90); \
        break; \
    } \
    case 99: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 67) = *(const unaligned_u64 *)((const u8 *)(src) + 67); \
        *(unaligned_u64 *)((u8 *)(dst) + 75) = *(const unaligned_u64 *)((const u8 *)(src) + 75); \
        *(unaligned_u64 *)((u8 *)(dst) + 83) = *(const unaligned_u64 *)((const u8 *)(src) + 83); \
        *(unaligned_u64 *)((u8 *)(dst) + 91) = *(const unaligned_u64 *)((const u8 *)(src) + 91); \
        break; \
    } \
    case 100: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 68) = *(const unaligned_u64 *)((const u8 *)(src) + 68); \
        *(unaligned_u64 *)((u8 *)(dst) + 76) = *(const unaligned_u64 *)((const u8 *)(src) + 76); \
        *(unaligned_u64 *)((u8 *)(dst) + 84) = *(const unaligned_u64 *)((const u8 *)(src) + 84); \
        *(unaligned_u64 *)((u8 *)(dst) + 92) = *(const unaligned_u64 *)((const u8 *)(src) + 92); \
        break; \
    } \
    case 101: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 69) = *(const unaligned_u64 *)((const u8 *)(src) + 69); \
        *(unaligned_u64 *)((u8 *)(dst) + 77) = *(const unaligned_u64 *)((const u8 *)(src) + 77); \
        *(unaligned_u64 *)((u8 *)(dst) + 85) = *(const unaligned_u64 *)((const u8 *)(src) + 85); \
        *(unaligned_u64 *)((u8 *)(dst) + 93) = *(const unaligned_u64 *)((const u8 *)(src) + 93); \
        break; \
    } \
    case 102: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 70) = *(const unaligned_u64 *)((const u8 *)(src) + 70); \
        *(unaligned_u64 *)((u8 *)(dst) + 78) = *(const unaligned_u64 *)((const u8 *)(src) + 78); \
        *(unaligned_u64 *)((u8 *)(dst) + 86) = *(const unaligned_u64 *)((const u8 *)(src) + 86); \
        *(unaligned_u64 *)((u8 *)(dst) + 94) = *(const unaligned_u64 *)((const u8 *)(src) + 94); \
        break; \
    } \
    case 103: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 71) = *(const unaligned_u64 *)((const u8 *)(src) + 71); \
        *(unaligned_u64 *)((u8 *)(dst) + 79) = *(const unaligned_u64 *)((const u8 *)(src) + 79); \
        *(unaligned_u64 *)((u8 *)(dst) + 87) = *(const unaligned_u64 *)((const u8 *)(src) + 87); \
        *(unaligned_u64 *)((u8 *)(dst) + 95) = *(const unaligned_u64 *)((const u8 *)(src) + 95); \
        break; \
    } \
    case 104: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 96) = *(const unaligned_u64 *)((const u8 *)(src) + 96); \
        break; \
    } \
    case 105: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 73) = *(const unaligned_u64 *)((const u8 *)(src) + 73); \
        *(unaligned_u64 *)((u8 *)(dst) + 81) = *(const unaligned_u64 *)((const u8 *)(src) + 81); \
        *(unaligned_u64 *)((u8 *)(dst) + 89) = *(const unaligned_u64 *)((const u8 *)(src) + 89); \
        *(unaligned_u64 *)((u8 *)(dst) + 97) = *(const unaligned_u64 *)((const u8 *)(src) + 97); \
        break; \
    } \
    case 106: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 74) = *(const unaligned_u64 *)((const u8 *)(src) + 74); \
        *(unaligned_u64 *)((u8 *)(dst) + 82) = *(const unaligned_u64 *)((const u8 *)(src) + 82); \
        *(unaligned_u64 *)((u8 *)(dst) + 90) = *(const unaligned_u64 *)((const u8 *)(src) + 90); \
        *(unaligned_u64 *)((u8 *)(dst) + 98) = *(const unaligned_u64 *)((const u8 *)(src) + 98); \
        break; \
    } \
    case 107: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 75) = *(const unaligned_u64 *)((const u8 *)(src) + 75); \
        *(unaligned_u64 *)((u8 *)(dst) + 83) = *(const unaligned_u64 *)((const u8 *)(src) + 83); \
        *(unaligned_u64 *)((u8 *)(dst) + 91) = *(const unaligned_u64 *)((const u8 *)(src) + 91); \
        *(unaligned_u64 *)((u8 *)(dst) + 99) = *(const unaligned_u64 *)((const u8 *)(src) + 99); \
        break; \
    } \
    case 108: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 76) = *(const unaligned_u64 *)((const u8 *)(src) + 76); \
        *(unaligned_u64 *)((u8 *)(dst) + 84) = *(const unaligned_u64 *)((const u8 *)(src) + 84); \
        *(unaligned_u64 *)((u8 *)(dst) + 92) = *(const unaligned_u64 *)((const u8 *)(src) + 92); \
        *(unaligned_u64 *)((u8 *)(dst) + 100) = *(const unaligned_u64 *)((const u8 *)(src) + 100); \
        break; \
    } \
    case 109: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 77) = *(const unaligned_u64 *)((const u8 *)(src) + 77); \
        *(unaligned_u64 *)((u8 *)(dst) + 85) = *(const unaligned_u64 *)((const u8 *)(src) + 85); \
        *(unaligned_u64 *)((u8 *)(dst) + 93) = *(const unaligned_u64 *)((const u8 *)(src) + 93); \
        *(unaligned_u64 *)((u8 *)(dst) + 101) = *(const unaligned_u64 *)((const u8 *)(src) + 101); \
        break; \
    } \
    case 110: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 78) = *(const unaligned_u64 *)((const u8 *)(src) + 78); \
        *(unaligned_u64 *)((u8 *)(dst) + 86) = *(const unaligned_u64 *)((const u8 *)(src) + 86); \
        *(unaligned_u64 *)((u8 *)(dst) + 94) = *(const unaligned_u64 *)((const u8 *)(src) + 94); \
        *(unaligned_u64 *)((u8 *)(dst) + 102) = *(const unaligned_u64 *)((const u8 *)(src) + 102); \
        break; \
    } \
    case 111: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 79) = *(const unaligned_u64 *)((const u8 *)(src) + 79); \
        *(unaligned_u64 *)((u8 *)(dst) + 87) = *(const unaligned_u64 *)((const u8 *)(src) + 87); \
        *(unaligned_u64 *)((u8 *)(dst) + 95) = *(const unaligned_u64 *)((const u8 *)(src) + 95); \
        *(unaligned_u64 *)((u8 *)(dst) + 103) = *(const unaligned_u64 *)((const u8 *)(src) + 103); \
        break; \
    } \
    case 112: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 96) = *(const unaligned_u64 *)((const u8 *)(src) + 96); \
        *(unaligned_u64 *)((u8 *)(dst) + 104) = *(const unaligned_u64 *)((const u8 *)(src) + 104); \
        break; \
    } \
    case 113: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 81) = *(const unaligned_u64 *)((const u8 *)(src) + 81); \
        *(unaligned_u64 *)((u8 *)(dst) + 89) = *(const unaligned_u64 *)((const u8 *)(src) + 89); \
        *(unaligned_u64 *)((u8 *)(dst) + 97) = *(const unaligned_u64 *)((const u8 *)(src) + 97); \
        *(unaligned_u64 *)((u8 *)(dst) + 105) = *(const unaligned_u64 *)((const u8 *)(src) + 105); \
        break; \
    } \
    case 114: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 82) = *(const unaligned_u64 *)((const u8 *)(src) + 82); \
        *(unaligned_u64 *)((u8 *)(dst) + 90) = *(const unaligned_u64 *)((const u8 *)(src) + 90); \
        *(unaligned_u64 *)((u8 *)(dst) + 98) = *(const unaligned_u64 *)((const u8 *)(src) + 98); \
        *(unaligned_u64 *)((u8 *)(dst) + 106) = *(const unaligned_u64 *)((const u8 *)(src) + 106); \
        break; \
    } \
    case 115: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 83) = *(const unaligned_u64 *)((const u8 *)(src) + 83); \
        *(unaligned_u64 *)((u8 *)(dst) + 91) = *(const unaligned_u64 *)((const u8 *)(src) + 91); \
        *(unaligned_u64 *)((u8 *)(dst) + 99) = *(const unaligned_u64 *)((const u8 *)(src) + 99); \
        *(unaligned_u64 *)((u8 *)(dst) + 107) = *(const unaligned_u64 *)((const u8 *)(src) + 107); \
        break; \
    } \
    case 116: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 84) = *(const unaligned_u64 *)((const u8 *)(src) + 84); \
        *(unaligned_u64 *)((u8 *)(dst) + 92) = *(const unaligned_u64 *)((const u8 *)(src) + 92); \
        *(unaligned_u64 *)((u8 *)(dst) + 100) = *(const unaligned_u64 *)((const u8 *)(src) + 100); \
        *(unaligned_u64 *)((u8 *)(dst) + 108) = *(const unaligned_u64 *)((const u8 *)(src) + 108); \
        break; \
    } \
    case 117: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 85) = *(const unaligned_u64 *)((const u8 *)(src) + 85); \
        *(unaligned_u64 *)((u8 *)(dst) + 93) = *(const unaligned_u64 *)((const u8 *)(src) + 93); \
        *(unaligned_u64 *)((u8 *)(dst) + 101) = *(const unaligned_u64 *)((const u8 *)(src) + 101); \
        *(unaligned_u64 *)((u8 *)(dst) + 109) = *(const unaligned_u64 *)((const u8 *)(src) + 109); \
        break; \
    } \
    case 118: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 86) = *(const unaligned_u64 *)((const u8 *)(src) + 86); \
        *(unaligned_u64 *)((u8 *)(dst) + 94) = *(const unaligned_u64 *)((const u8 *)(src) + 94); \
        *(unaligned_u64 *)((u8 *)(dst) + 102) = *(const unaligned_u64 *)((const u8 *)(src) + 102); \
        *(unaligned_u64 *)((u8 *)(dst) + 110) = *(const unaligned_u64 *)((const u8 *)(src) + 110); \
        break; \
    } \
    case 119: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 87) = *(const unaligned_u64 *)((const u8 *)(src) + 87); \
        *(unaligned_u64 *)((u8 *)(dst) + 95) = *(const unaligned_u64 *)((const u8 *)(src) + 95); \
        *(unaligned_u64 *)((u8 *)(dst) + 103) = *(const unaligned_u64 *)((const u8 *)(src) + 103); \
        *(unaligned_u64 *)((u8 *)(dst) + 111) = *(const unaligned_u64 *)((const u8 *)(src) + 111); \
        break; \
    } \
    case 120: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 96) = *(const unaligned_u64 *)((const u8 *)(src) + 96); \
        *(unaligned_u64 *)((u8 *)(dst) + 104) = *(const unaligned_u64 *)((const u8 *)(src) + 104); \
        *(unaligned_u64 *)((u8 *)(dst) + 112) = *(const unaligned_u64 *)((const u8 *)(src) + 112); \
        break; \
    } \
    case 121: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 89) = *(const unaligned_u64 *)((const u8 *)(src) + 89); \
        *(unaligned_u64 *)((u8 *)(dst) + 97) = *(const unaligned_u64 *)((const u8 *)(src) + 97); \
        *(unaligned_u64 *)((u8 *)(dst) + 105) = *(const unaligned_u64 *)((const u8 *)(src) + 105); \
        *(unaligned_u64 *)((u8 *)(dst) + 113) = *(const unaligned_u64 *)((const u8 *)(src) + 113); \
        break; \
    } \
    case 122: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 90) = *(const unaligned_u64 *)((const u8 *)(src) + 90); \
        *(unaligned_u64 *)((u8 *)(dst) + 98) = *(const unaligned_u64 *)((const u8 *)(src) + 98); \
        *(unaligned_u64 *)((u8 *)(dst) + 106) = *(const unaligned_u64 *)((const u8 *)(src) + 106); \
        *(unaligned_u64 *)((u8 *)(dst) + 114) = *(const unaligned_u64 *)((const u8 *)(src) + 114); \
        break; \
    } \
    case 123: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 91) = *(const unaligned_u64 *)((const u8 *)(src) + 91); \
        *(unaligned_u64 *)((u8 *)(dst) + 99) = *(const unaligned_u64 *)((const u8 *)(src) + 99); \
        *(unaligned_u64 *)((u8 *)(dst) + 107) = *(const unaligned_u64 *)((const u8 *)(src) + 107); \
        *(unaligned_u64 *)((u8 *)(dst) + 115) = *(const unaligned_u64 *)((const u8 *)(src) + 115); \
        break; \
    } \
    case 124: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 92) = *(const unaligned_u64 *)((const u8 *)(src) + 92); \
        *(unaligned_u64 *)((u8 *)(dst) + 100) = *(const unaligned_u64 *)((const u8 *)(src) + 100); \
        *(unaligned_u64 *)((u8 *)(dst) + 108) = *(const unaligned_u64 *)((const u8 *)(src) + 108); \
        *(unaligned_u64 *)((u8 *)(dst) + 116) = *(const unaligned_u64 *)((const u8 *)(src) + 116); \
        break; \
    } \
    case 125: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 93) = *(const unaligned_u64 *)((const u8 *)(src) + 93); \
        *(unaligned_u64 *)((u8 *)(dst) + 101) = *(const unaligned_u64 *)((const u8 *)(src) + 101); \
        *(unaligned_u64 *)((u8 *)(dst) + 109) = *(const unaligned_u64 *)((const u8 *)(src) + 109); \
        *(unaligned_u64 *)((u8 *)(dst) + 117) = *(const unaligned_u64 *)((const u8 *)(src) + 117); \
        break; \
    } \
    case 126: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 94) = *(const unaligned_u64 *)((const u8 *)(src) + 94); \
        *(unaligned_u64 *)((u8 *)(dst) + 102) = *(const unaligned_u64 *)((const u8 *)(src) + 102); \
        *(unaligned_u64 *)((u8 *)(dst) + 110) = *(const unaligned_u64 *)((const u8 *)(src) + 110); \
        *(unaligned_u64 *)((u8 *)(dst) + 118) = *(const unaligned_u64 *)((const u8 *)(src) + 118); \
        break; \
    } \
    case 127: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 95) = *(const unaligned_u64 *)((const u8 *)(src) + 95); \
        *(unaligned_u64 *)((u8 *)(dst) + 103) = *(const unaligned_u64 *)((const u8 *)(src) + 103); \
        *(unaligned_u64 *)((u8 *)(dst) + 111) = *(const unaligned_u64 *)((const u8 *)(src) + 111); \
        *(unaligned_u64 *)((u8 *)(dst) + 119) = *(const unaligned_u64 *)((const u8 *)(src) + 119); \
        break; \
    } \
    case 128: { \
        *(unaligned_u64 *)((u8 *)(dst) + 0) = *(const unaligned_u64 *)((const u8 *)(src) + 0); \
        *(unaligned_u64 *)((u8 *)(dst) + 8) = *(const unaligned_u64 *)((const u8 *)(src) + 8); \
        *(unaligned_u64 *)((u8 *)(dst) + 16) = *(const unaligned_u64 *)((const u8 *)(src) + 16); \
        *(unaligned_u64 *)((u8 *)(dst) + 24) = *(const unaligned_u64 *)((const u8 *)(src) + 24); \
        *(unaligned_u64 *)((u8 *)(dst) + 32) = *(const unaligned_u64 *)((const u8 *)(src) + 32); \
        *(unaligned_u64 *)((u8 *)(dst) + 40) = *(const unaligned_u64 *)((const u8 *)(src) + 40); \
        *(unaligned_u64 *)((u8 *)(dst) + 48) = *(const unaligned_u64 *)((const u8 *)(src) + 48); \
        *(unaligned_u64 *)((u8 *)(dst) + 56) = *(const unaligned_u64 *)((const u8 *)(src) + 56); \
        *(unaligned_u64 *)((u8 *)(dst) + 64) = *(const unaligned_u64 *)((const u8 *)(src) + 64); \
        *(unaligned_u64 *)((u8 *)(dst) + 72) = *(const unaligned_u64 *)((const u8 *)(src) + 72); \
        *(unaligned_u64 *)((u8 *)(dst) + 80) = *(const unaligned_u64 *)((const u8 *)(src) + 80); \
        *(unaligned_u64 *)((u8 *)(dst) + 88) = *(const unaligned_u64 *)((const u8 *)(src) + 88); \
        *(unaligned_u64 *)((u8 *)(dst) + 96) = *(const unaligned_u64 *)((const u8 *)(src) + 96); \
        *(unaligned_u64 *)((u8 *)(dst) + 104) = *(const unaligned_u64 *)((const u8 *)(src) + 104); \
        *(unaligned_u64 *)((u8 *)(dst) + 112) = *(const unaligned_u64 *)((const u8 *)(src) + 112); \
        *(unaligned_u64 *)((u8 *)(dst) + 120) = *(const unaligned_u64 *)((const u8 *)(src) + 120); \
        break; \
    }



//typedef u64 unaligned_u64 __attribute__((aligned(1), may_alias));

#ifndef OSTD_NO_MEMCPY

#define memcpy memcpy_ostd

__attribute__((no_builtin("memcpy")))
void *memcpy_ostd(void *restrict dst, const void *restrict src, sys_uint n) {
    
    switch (n) {
    JUMP_TABLE(dst, src, n);
    
    default: {

        //u64 allow_align = (n > 256) & 1;
        //u64 need_align = ((u64)dst % 32 != 0) & 1;
        //u64 do_align = (allow_align & need_align);
        //
        //u8 *aligned_dst = (u8*)(((~do_align & 1) * (u64)dst) + (do_align * (((u64)dst+31ull) & ~(31ull))));
        //
        //u64 align_diff = do_align * ((u64)aligned_dst - (u64)dst);
        //n -= align_diff;
        //switch (align_diff) {
        //    JUMP_TABLE(dst, src, align_diff)
        //}
        //src = (u8*)src + align_diff;
        
        u8 *aligned_dst = dst;
        //if (n > 256) {
        //    aligned_dst = (u8*)(((u64)dst+31) & ~(31));
        //    u64 align_diff = (u64)aligned_dst - (u64)dst;
        //    n -= align_diff;
        //    
        //    switch (align_diff) {
        //        JUMP_TABLE(dst, src, align_diff)
        //    }
        //    
        //    src = (u8*)src + align_diff;
        //}
        
        u64 rem = n;
        
        #pragma clang loop vectorize(enable)
        while (rem >= 32) {
            u64 i = n - rem;
            *(unaligned_u64*)((u8*)aligned_dst + i) = *(unaligned_u64*)((u8*)src + i);
            *(unaligned_u64*)((u8*)aligned_dst + i +  8) = *(unaligned_u64*)((u8*)src + i +  8);
            *(unaligned_u64*)((u8*)aligned_dst + i + 16) = *(unaligned_u64*)((u8*)src + i + 16);
            *(unaligned_u64*)((u8*)aligned_dst + i + 24) = *(unaligned_u64*)((u8*)src + i + 24);
            //*(unaligned_u64*)((u8*)aligned_dst + i + 32) = *(unaligned_u64*)((u8*)src + i + 32);
            //*(unaligned_u64*)((u8*)aligned_dst + i + 40) = *(unaligned_u64*)((u8*)src + i + 40);
            //*(unaligned_u64*)((u8*)aligned_dst + i + 48) = *(unaligned_u64*)((u8*)src + i + 48);
            //*(unaligned_u64*)((u8*)aligned_dst + i + 56) = *(unaligned_u64*)((u8*)src + i + 56);
            //*(unaligned_u64*)((u8*)aligned_dst + i + 64) = *(unaligned_u64*)((u8*)src + i + 64);
            //*(unaligned_u64*)((u8*)aligned_dst + i + 72) = *(unaligned_u64*)((u8*)src + i + 72);
            //*(unaligned_u64*)((u8*)aligned_dst + i + 80) = *(unaligned_u64*)((u8*)src + i + 80);
            //*(unaligned_u64*)((u8*)aligned_dst + i + 88) = *(unaligned_u64*)((u8*)src + i + 88);
            //*(unaligned_u64*)((u8*)aligned_dst + i + 96) = *(unaligned_u64*)((u8*)src + i + 96);
            //*(unaligned_u64*)((u8*)aligned_dst + i + 104) = *(unaligned_u64*)((u8*)src + i + 104);
            //*(unaligned_u64*)((u8*)aligned_dst + i + 112) = *(unaligned_u64*)((u8*)src + i + 112);
            //*(unaligned_u64*)((u8*)aligned_dst + i + 120) = *(unaligned_u64*)((u8*)src + i + 120);
            
            rem -= 32;
        }
        
        __builtin_assume(rem < 32);
        
        u64 i = n - rem;
        u8 *tail_dst = (u8*)aligned_dst + i;
        u8 *tail_src = (u8*)src + i;
        
        
        switch (rem) {
    
        JUMP_TABLE(tail_dst, tail_src, rem)
        
        default: return dst;
        }
        
        return dst;
    }
    }
    
    return dst;
}

#if defined(OSTD_SELF_CONTAINED)

// Compilers are annoying.
void *memcpy_no_inline(void *restrict dst, const void *restrict src, sys_uint n) __asm__("memcpy");

void *memcpy_no_inline(void *restrict dst, const void *restrict src, sys_uint n) {
    return memcpy_ostd(dst, src, n);
}
#endif // OSTD_SELF_CONTAINED

#endif

#ifndef OSTD_NO_MEMSET

#define memset memset_inline

__attribute__((no_builtin("memset")))
inline void *memset_inline(void *dst, s32 c, sys_uint n) {
    u8 *p = (u8*)dst;
    while (n--) *p++ = (u8)c;
    return dst;
}

#if defined(OSTD_SELF_CONTAINED)

// Compilers are annoying.
void *memset_no_inline(void *dst, s32 c, sys_uint n) __asm__("memset");

void *memset_no_inline(void *dst, s32 c, sys_uint n) {
    u8 *p = (u8*)dst;
    while (n--) *p++ = (u8)c;
    return dst;
}
#endif // OSTD_SELF_CONTAINED

#endif

#ifndef OSTD_NO_MEMMOVE
inline void *memmove(void *dst, const void *src, sys_uint n) {
    if (!n) return dst;
    if ((sys_uint)dst > (sys_uint)src)
        for (s64 i = (s64)n-1; i >= 0; i -= 1)  *((u8*)dst + i) = *((const u8*)src + i);
    else
        for (sys_uint i = 0; i < n; i += 1)  *((u8*)dst + i) = *((const u8*)src + i);
    return dst;
}
#endif


inline int memcmp(const void* a, const void* b, sys_uint n) {
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

OSTD_LIB u64 c_style_strlen(const char *s);
OSTD_LIB u64 c_style_strcmp(const char *a, const char *b);


#define STR(c) ((string){ c_style_strlen((const char*)(c)), (u8*)(uintptr)(const void*)(c) })
#define STR_LIT(c) ((string){ sizeof(c)-1, (u8*)(uintptr)(const void*)(c) })
#define STRN(n, c) ((string){ n, (u8*)(uintptr)(const void*)(c) })
#define RSTR(...) STR(#__VA_ARGS__)

inline int memcmp(const void* a, const void* b, sys_uint n);
unit_local inline bool strings_match(string a, string b) {
    if (a.count != b.count) return false;
    
    if (a.count == 0) return true;

    if (a.data == b.data) return true; // Pointers and counts match

    if (a.count == 0 || b.count == 0) return false;
    if (a.data  == 0 || b.data  == 0) return false;
    
    for (u64 i = 0; i < a.count; i += 1) {
        if (a.data[i] != b.data[i])
            return false;
    }
    return true;
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

