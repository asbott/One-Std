
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
    #define _CLANG 1
    //#error hi1
#else
    #define _CLANG 0
#endif

#if defined(__GNUC__) || defined(__GNUG__)
    #define _GNU 1
#else
    #define _GNU 0
#endif

#ifdef _MSC_VER
    #define _MSC 1
#else
    #define _MSC 0
#endif

#ifdef __INTEL_COMPILER
    #define _INTEL 1
#else
    #define _INTEL 0
#endif

#ifdef __TINYC__
    #define _TCC 1
#else
    #define _TCC 0
#endif

#ifdef __EMSCRIPTEN__
    #define _EMSCRIPTEN 1
#else
    #define _EMSCRIPTEN 0
#endif

#ifdef __PGI
    #define _PGI 1
#else
    #define _PGI 0
#endif

#ifdef __SUNPRO_C
    #define _SUNPRO 1
#else
    #define _SUNPRO 0
#endif

#define COMPILER_FLAGS ( \
    (_CLANG ? COMPILER_FLAG_CLANG : 0) | \
    ((_GNU) ? COMPILER_FLAG_GNU : 0) | \
    (_MSC ? COMPILER_FLAG_MSC : 0) | \
    (_INTEL ? COMPILER_FLAG_INTEL : 0) | \
    (_TCC ? COMPILER_FLAG_TCC : 0) | \
    (_EMSCRIPTEN ? COMPILER_FLAG_EMSCRIPTEN : 0) | \
    (_PGI ? COMPILER_FLAG_PGI : 0) | \
    (_SUNPRO ? COMPILER_FLAG_SUNPRO : 0) | \
    ((_CLANG && _GNU) ? COMPILER_FLAG_CLANG_GNU : 0) \
)




#define local_persist static
#define forward_global extern

// make inline actually inline if supported by compiler

#if COMPILER_FLAGS & COMPILER_FLAG_GNU
    #define inline __attribute__((always_inline))
#elif COMPILER_MSVC
    #define inline __forceinline
#endif

#define CSTD_C90 1
#ifdef __STDC_VERSION__
    #if __STDC_VERSION__ == 199901
        #define CSTD_C99 1
    #endif
    #if __STDC_VERSION__ == 201112
        #define CSTD_C11 1
    #endif
    #if __STDC_VERSION__ == 201710
        #define CSTD_C17 1
    #endif
    #if __STDC_VERSION__ == 202311
        #define CSTD_C23 1
    #endif
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
#define OS_FLAG_MACOS             (1 << 4)
#define OS_FLAG_IOS               (1 << 5)
#define OS_FLAG_ANDROID           (1 << 6)
#define OS_FLAG_STEAMOS           (1 << 7)
#define OS_FLAG_LINUX_BASED       (1 << 8)
#define OS_FLAG_HAS_WINDOW_SYSTEM (1 << 9)

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
    #pragma clang diagnostic pop
    
#elif COMPILER_FLAGS & COMPILER_FLAG_GNU

    // todo(charlie) inspect at a gnu stdint.h
    typedef unsigned char     u8;
    typedef signed char       s8;
    typedef unsigned short    u16;
    typedef signed short      s16;
    typedef unsigned int      u32;
    typedef signed int        s32;
    typedef unsigned long     u64;
    typedef signed long       s64;
    
#else

    #include <stdint.h>
    #error hi
    typedef uint8_t  u8;
    typedef int8_t   s8;
    typedef uint16_t u16;
    typedef int16_t  s16;
    typedef uint32_t u32;
    typedef int32_t  s32;
    typedef uint64_t u64;
    typedef int64_t  s64;

#endif

typedef float float32;
typedef double float64;
#if defined(__SIZEOF_FLOAT128__) && __SIZEOF_FLOAT128__ == 16
    typedef __float128 float128;
    #define HAS_FLOAT128 1
#elif defined(__SIZEOF_LONG_DOUBLE__) && __SIZEOF_LONG_DOUBLE__ == 16
    typedef long double float128;
    #define HAS_FLOAT128 1
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

typedef s8 bool;
#define true 1
#define false 0

typedef union float32x2 {
    struct {float32 x, y;} DUMMYSTRUCT;
} float32x2;

typedef union int32x2 {
    struct {int32 x, y;} DUMMYSTRUCT;
} int32x2;

typedef union int32x4 {
    struct {int32 x, y, z, w;} DUMMYSTRUCT;
} int32x4;

typedef float32x2 float2;
typedef int32x2 int2;

#if COMPILER_FLAGS & COMPILER_FLAG_MSC
#define debug_break(...) __debugbreak()
#elif COMPILER_FLAGS & COMPILER_FLAG_GNU
#define debug_break(...) __builtin_trap()
#else
#define debug_break(...) *(volatile int*)0 = 1
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define assertmsg(x, msg)  do { \
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
#define assert(x) assertmsg(x, (string){0})

inline void *memcpy(void *dst, const void * src, u64 n);
// todo(charlie) inline asm / dynamically load crt's if msvc
inline void *memset(void *dst, s32 c, u64 n) {
    u64 i;
    for (i = 0; i+4 < n; i += 4)  *((s32*)dst + (i/4)) = c;
    if (i < n) memcpy(dst, &c, n-i);
    return dst;
}
inline void *memcpy(void *dst, const void * src, u64 n) {
    for (u64 i = 0; i < n; i += 1)  *((u8*)dst + i) = *((u8*)src + i);
    return dst;
}
inline void *memmove(void *dst, const void *src, u64 n) {
    if (!n) return dst;
    if ((u64)dst > (u64)src)
        for (s64 i = n-1; i >= 0; i -= 1)  *((u8*)dst + i) = *((u8*)src + i);
    else
        for (u64 i = 0; i < n; i += 1)  *((u8*)dst + i) = *((u8*)src + i);
    return dst;
}

inline int memcmp(const void* a, const void* b, size_t n) {
    u8 *p1 = (u8 *)a;
    u8 *p2 = (u8 *)b;

    for (u32 i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    return 0;
}

#define DEFAULT(T) T##_default


// Forward decls
u64 format_signed_int(s64 x, int base, void *buffer, u64 buffer_size);
u64 format_unsigned_int(u64 x, int base, void *buffer, u64 buffer_size);
u64 format_float(float64 x, int decimal_places, void *buffer, u64 buffer_size);