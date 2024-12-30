
/*
            Compiler
*/


#ifdef __clang__
    #define COMPILER_CLANG 1
    #define COMPILER_GNU 1
#elif defined(__GNUC__) || defined(__GNUG__)
    #define COMPILER_GCC 1
    #define COMPILER_GNU 1
#elif defined(_MSC_VER)
    #define COMPILER_MSVC 1
#else
    #define COMPILER_UNKNOWN 1
#endif

#define local_persist static
#define forward_global extern

// make inline actually inline if supported by compiler

#if COMPILER_GNU
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

typedef enum OS_Flags { 
    OS_FLAG_WINDOWS     = 1 << 0,
    OS_FLAG_UNIX        = 1 << 1,
    OS_FLAG_LINUX       = 1 << 2,
    OS_FLAG_APPLE       = 1 << 3,
    OS_FLAG_MACOS       = 1 << 4,
    OS_FLAG_IOS         = 1 << 5,
    OS_FLAG_ANDROID     = 1 << 6,
    OS_FLAG_STEAMOS     = 1 << 7,
    OS_FLAG_LINUX_BASED = 1 << 8,
} OS_Flags;

#ifdef _WIN32
    #define OS_FLAGS (OS_FLAG_WINDOWS)
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        #define OS_FLAGS (OS_FLAG_UNIX | OS_FLAG_APPLE | OS_FLAG_IOS)
    #elif TARGET_OS_MAC
        #define OS_FLAGS (OS_FLAG_UNIX | OS_FLAG_APPLE | OS_FLAG_MACOS)
    #else
        #define OS_FLAGS (OS_FLAG_UNIX | OS_FLAG_APPLE)
    #endif
#elif defined(__ANDROID__)
    #define OS_FLAGS (OS_FLAG_UNIX | OS_FLAG_LINUX_BASED | OS_FLAG_ANDROID)
#elif defined(__STEAMOS__) /* You need to define this yourself when targetting steam */
    #define OS_FLAGS (OS_FLAG_UNIX | OS_FLAG_LINUX_BASED | OS_FLAG_LINUX | OS_FLAG_STEAMOS)
#elif defined(__linux__)
    #define OS_FLAGS (OS_FLAG_UNIX | OS_FLAG_LINUX_BASED | OS_FLAG_LINUX)
#elif defined(__unix__) || defined(__unix)
    #define OS_FLAGS (OS_FLAG_UNIX)
#else
    #define OS_FLAGS (0)
#endif

#include <stdint.h>

typedef uint8_t  u8;
typedef int8_t   s8;
typedef uint16_t u16;
typedef int16_t  s16;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint64_t u64;
typedef int64_t  s64;

typedef float float32;
typedef double float64;

typedef s8 bool;
#define true 1
#define false 0

#define assert(x, ...)  if (!(x)) *(volatile int*)0 = 1

void *memcpy(void *dst, const void * src, u64 n);

// todo(charlie) inline asm / dynamically load crt's if msvc
void *memset(void *dst, s32 c, u64 n) {
    u64 i;
    for (i = 0; i+4 < n; i += 4)  *((s32*)dst + (i/4)) = c;
    if (i < n) memcpy(dst, &c, n-i);
    return dst;
}
void *memcpy(void *dst, const void * src, u64 n) {
    for (u64 i = 0; i < n; i += 1)  *((u8*)dst + i) = *((u8*)src + i);
    return dst;
}
void *memmove(void *dst, const void *src, u64 n) {
    if (!n) return dst;
    if ((u64)dst > (u64)src)
        for (s64 i = n-1; i >= 0; i -= 1)  *((u8*)dst + i) = *((u8*)src + i);
    else
        for (u64 i = 0; i < n; i += 1)  *((u8*)dst + i) = *((u8*)src + i);
    return dst;
}

int memcmp(void *a, void *b, u64 n) {
    u8 *p1 = (u8 *)a;
    u8 *p2 = (u8 *)b;

    for (u64 i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    return 0;
}