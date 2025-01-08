#ifndef OSTD_H_
#define OSTD_H_

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-library-redeclaration"
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#pragma clang diagnostic ignored "-Wnewline-eof"
#pragma clang diagnostic ignored "-Wkeyword-macro"
#pragma clang diagnostic ignored "-Wreserved-identifier"
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wcast-align"
#pragma clang diagnostic ignored "-Wunused-function"
#ifdef _MSC_VER
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif
#ifdef __EMSCRIPTEN__
#pragma clang diagnostic ignored "-Wpadded"
#endif
#endif


/* Begin include: base.h */

#if 0
#endif

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
    //#error hi1
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

#if COMPILER_FLAGS & COMPILER_FLAG_GNU
    #define inline __attribute__((always_inline))
#elif COMPILER_FLAGS & COMPILER_FLAG_MSC
    #define inline __forceinline
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

#if defined(ARCH_X64) || defined (ARCH_ARM64)
typedef s64 sys_int;
typedef u64 sys_uint;
#define SYS_INT_MAX SYS_S64_MAX
#define SYS_UINT_MAX SYS_U64_MAX
#else
typedef s32 sys_int;
typedef u32 sys_uint;
#define SYS_INT_MAX S32_MAX
#define SYS_UINT_MAX U32_MAX
#endif

#if !CSTD_C23
    #pragma clang diagnostic push
#if (COMPILER_FLAGS & COMPILER_FLAG_CLANG) && ((COMPILER_FLAGS & COMPILER_FLAG_MSC) || COMPILER_FLAGS & COMPILER_FLAG_EMSCRIPTEN)
    #pragma clang diagnostic ignored "-Wc23-compat"
#endif
    typedef s8 bool;
    #define true 1
    #define false 0
    #pragma clang diagnostic pop
#endif

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

inline void *memcpy(void *dst, const void * src, sys_uint n);
// todo(charlie) inline asm / dynamically load crt's if msvc
inline void *memset(void *dst, s32 c, sys_uint n) {
    sys_uint i;
    for (i = 0; i+4 < n; i += 4)  *((s32*)dst + (i/4)) = c;
    if (i < n) memcpy(dst, &c, n-i);
    return dst;
}
inline void *memcpy(void *dst, const void * src, sys_uint n) {
    for (sys_uint i = 0; i < n; i += 1)  *((u8*)dst + i) = *((const u8*)src + i);
    return dst;
}
inline void *memmove(void *dst, const void *src, sys_uint n) {
    if (!n) return dst;
    if ((sys_uint)dst > (sys_uint)src)
        for (s64 i = (s64)n-1; i >= 0; i -= 1)  *((u8*)dst + i) = *((const u8*)src + i);
    else
        for (sys_uint i = 0; i < n; i += 1)  *((u8*)dst + i) = *((const u8*)src + i);
    return dst;
}

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



#define PP_FIRST_ARG_HELPER(x, ...) x
#define PP_FIRST_ARG(...) PP_FIRST_ARG_HELPER(__VA_ARGS__)

#define PP_EXCLUDE_FIRST_ARG_HELPER(x, ...) __VA_ARGS__
#define PP_EXCLUDE_FIRST_ARG(...) PP_EXCLUDE_FIRST_ARG_HELPER(__VA_ARGS__)


/* End include: base.h */


/* Begin include: math.h */
#if 0
#endif

// Natural logarithm
float32 ln32(float32 x);
float64 ln64(float64 x);

#ifdef OSTD_IMPL

float32 ln32(float32 x) {
    u32 bx = * (u32 *) (&x);
    u32 ex = bx >> 23;
    s32 t = (s32)ex-(s32)127;
    bx = 1065353216 | (bx & 8388607);
    x = * (float32 *) (&bx);
    return -1.49278f+(2.11263f+(-0.729104f+0.10969f*x)*x)*x+0.6931471806f*(float32)t;
}

float64 ln64(float64 x) {
    u64 bx = *(u64 *)(&x); // Read float64 bits
    u64 ex = bx >> 52; // Extract exponent (11 bits)
    s32 t = (s32)ex - 1023; // Adjust for float64 bias
    bx = 4607182418800017408ULL | (bx & 4503599627370495ULL); // Normalize mantissa
    x = *(float64 *)(&bx);
    return -1.49278 + (2.11263 + (-0.729104 + 0.10969 * x) * x) * x + 0.6931471806 * t;
}

#endif // OSTD_IMPL
/* End include: math.h */


/* Begin include: utility.h */
#if 0
#endif

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))


/* End include: utility.h */


/* Begin include: string.h */
#if 0
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

#define STR(c) ((string){ c_style_strlen((const char*)c), (u8*)(uintptr)(const void*)(c) })
#define STRN(n, c) ((string){ n, (u8*)(uintptr)(const void*)(c) })
#define RSTR(...) STR(#__VA_ARGS__)

unit_local inline bool strings_match(string a, string b) {
    if (a.count != b.count) return false;

    if (a.data == b.data) return true; // Pointers and counts match

    if (a.count == 0 || b.count == 0) return false;
    if (a.data  == 0 || b.data  == 0) return false;

    return memcmp(a.data, b.data, (sys_uint)a.count) == 0;
}
/* End include: string.h */


/* Begin include: system.h */
#if 0
#endif

#define SYS_MEMORY_RESERVE (1 << 0)
#define SYS_MEMORY_ALLOCATE (1 << 1)

void *sys_map_pages(u64 action, void *virtual_base, u64 amount_in_bytes);
bool sys_unmap_pages(void *address);
// Deallocates, but keeps pages mapped & reserved
bool sys_deallocate_pages(void *address, u64 number_of_pages);

typedef struct Mapped_Memory_Info {
    void *base;
    u64 page_count;
} Mapped_Memory_Info;
u64 sys_query_mapped_regions(void *start, void *end, Mapped_Memory_Info *result, u64 result_size);

//////
// System info
//////

typedef struct System_Info {
    u64 page_size;
    u64 granularity;
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

//////
// IO
//////

typedef void* File_Handle;

File_Handle sys_get_stdout(void);
File_Handle sys_get_stderr(void);

void sys_set_stdout(File_Handle h);
void sys_set_stderr(File_Handle h);

s64 sys_write(File_Handle h, void *data, u64 size);
s64 sys_write_string(File_Handle h, string s);

s64 sys_read(File_Handle h, void *buffer, u64 buffer_size);

bool sys_make_pipe(File_Handle *read, File_Handle *write);

void sys_close(File_Handle h);

//////
// Surfaces (Window)
//////

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
Surface_Handle sys_make_surface(Surface_Desc desc);
void surface_close(Surface_Handle s);


#else // !(OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)

Surface_Handle sys_get_surface(void);

#endif // !(OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)

void surface_poll_events(Surface_Handle surface);
bool surface_should_close(Surface_Handle s);

// Will return false on systems where the flag isn't implemented
bool surface_set_flags(Surface_Handle h, Surface_Flags flags);
bool surface_unset_flags(Surface_Handle h, Surface_Flags flags);

//////
// Debug
//////

void sys_print_stack_trace(File_Handle handle);

//////
// System Constants
/////

#define MAX_SURFACES 64
#define MAX_PATH_LENGTH 260


//////
// Implementations
//////

#ifdef OSTD_IMPL

#if (OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)

typedef struct _Surface_State {
    Surface_Handle handle;
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

#endif // (OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)


#if (OS_FLAGS & OS_FLAG_UNIX)

/////////////////////////////////////////////////////
//////
// :Unix
//////
/////////////////////////////////////////////////////

// todo(charlie) dynamically link & manually  define some stuff to minimize namespace bloat here
#include <unistd.h>
#include <sched.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
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
    buffer->regions[0].page_count = (u32)page_count;
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
        // On Unix, allocation granularity is typically the same as page size
        info.granularity = info.page_size;
    }

    return info;
}

void *sys_map_pages(u64 action, void *virtual_base, u64 number_of_pages) {
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
        flags |= MAP_FIXED;
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

s64 sys_write(File_Handle f, void *data, u64 size) {
    return (s64)write((int)(u64)f, data, (sys_uint)size);
}

s64 sys_write_string(File_Handle f, string s) {
    return sys_write(f, s.data, s.count);
}

s64 sys_read(File_Handle h, void *buffer, u64 buffer_size) {
    return (s64)read((int)(u64)h, buffer, (sys_uint)buffer_size);
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
    #pragma comment(lib, "dbghelp")
#endif // COMPILER_FLAGS & COMPILER_FLAG_MSC

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

#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00


#define DECLSPEC_ALIGN(x) __declspec(align(x))
#define DECLSPEC_NOINITALL

//#include "basetsd.h"

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
#define WINDOWS_IMPORT __attribute__((dllimport))
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

#define GWL_STYLE -16
#define GWL_EXSTYLE -20

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


/* End include: windows_loader.h */
#endif // _WINDOWS_

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

unit_local u64 _win_utf8_to_wide(string utf8, u16 *result, u64 result_max) {
    return (u64)MultiByteToWideChar(CP_UTF8, 0, (LPCCH)utf8.data, (int)utf8.count, (LPWSTR)result, (int)result_max);
}

unit_local LRESULT window_proc ( HWND hwnd,  u32 message,  WPARAM wparam,  LPARAM lparam) {

    _Surface_State *state = _get_surface_state(hwnd);
    if (!state) return DefWindowProcW(hwnd, message, wparam, lparam);

    switch (message) {
        case WM_QUIT:
        case WM_CLOSE:
            state->should_close = true;
            break;

        default: {
            return DefWindowProcW(hwnd, message, wparam, lparam);
        }
    }

    return 0;
}


void *sys_map_pages(u64 action, void *virtual_base, u64 number_of_pages) {

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

System_Info sys_get_info(void) {
    local_persist System_Info info;
    local_persist bool has_retrieved_info = false;

    if (!has_retrieved_info) {
        has_retrieved_info = true;

        SYSTEM_INFO win32_info;
        GetSystemInfo(&win32_info);

        info.page_size = (u64)win32_info.dwPageSize;
        info.granularity = win32_info.dwAllocationGranularity;
    }

    return info;
}

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

typedef struct TotalRectContext {
    RECT rect;
} TotalRectContext;


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
    u32 written;
    WriteFile(f, data, (DWORD)size, (unsigned long*)&written, 0);
    if (written == 0 && size != 0) return -1;
    return (s64)written;
}

s64 sys_write_string(File_Handle f, string s) {
    return sys_write(f, s.data, s.count);
}

s64 sys_read(File_Handle h, void *buffer, u64 buffer_size) {
    DWORD read = 0;
    BOOL ok = ReadFile(h, (LPVOID)buffer, (DWORD)buffer_size, &read, 0);
    if (!ok) return -1;

    return (s64)read;
}

void sys_close(File_Handle h) {
    CloseHandle((HANDLE)h);
}

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
            _android_refresh_rate = 1.0 / (f64)(delta_time_nanos*1000000000);
        }
    }

    _android_previous_vsync_time = frame_time_nanos;
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

Surface_Handle sys_get_surface() {
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

void sys_print_stack_trace(File_Handle handle) {
    sys_write_string(handle, STR("<Stack trace unimplemented>"));
}

#elif (OS_FLAGS & OS_FLAG_EMSCRIPTEN)

/////////////////////////////////////////////////////
//////
// :Emscripten
//////
/////////////////////////////////////////////////////

#include <emscripten.h>
#include <emscripten/html5.h>
#undef bool

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

void sys_print_stack_trace(File_Handle handle) {
    char buffer[16384];
    int len = emscripten_get_callstack(EM_LOG_C_STACK, buffer, 16384);
    sys_write(handle, buffer, (u64)len);
}

#endif // OS_FLAGS & XXXXX

#endif // OSTD_IMPL
/* End include: system.h */


/* Begin include: unicode.h */
#if 0
#endif

#define UTF16_SURROGATE_HIGH_START  0xD800
#define UTF16_SURROGATE_HIGH_END    0xDBFF
#define UTF16_SURROGATE_LOW_START   0xDC00
#define UTF16_SURROGATE_LOW_END     0xDFFF
#define UTF16_SURROGATE_OFFSET      0x10000
#define UTF16_SURROGATE_MASK        0x3FF


#define UNI_REPLACEMENT_CHAR 0x0000FFFD
#define UNI_MAX_UTF32        0x7FFFFFFF
#define UNI_MAX_UTF16        0x0010FFFF
#define SURROGATES_START     0xD800
#define SURROGATES_END       0xDFFF

typedef struct {
	u32 utf32;
	s64 continuation_bytes;
	bool reached_end;
	bool error;
} Utf8_To_Utf32_Result;
typedef struct {
    u32 utf32;
    s64 continuation_bytes;
    bool reached_end;
    bool error;
} Utf8_To_Utf16_Result;

Utf8_To_Utf32_Result one_utf8_to_utf32(u8 *s, s64 source_length, bool strict);
Utf8_To_Utf16_Result one_utf8_to_utf16(u8 *s, s64 source_length, bool strict);

#ifdef OSTD_IMPL

unit_local const u8 trailing_bytes_for_utf8[] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};
unit_local const u8 utf8_inital_byte_mask[] = { 0x7F, 0x1F, 0x0F, 0x07, 0x03, 0x01 };

// Convert single utf8 character to a single utf32 codepoint
Utf8_To_Utf32_Result one_utf8_to_utf32(u8 *s, s64 source_length, bool strict) {
    s64 continuation_bytes = trailing_bytes_for_utf8[s[0]];

    if (continuation_bytes + 1 > source_length) {
        return (Utf8_To_Utf32_Result){UNI_REPLACEMENT_CHAR, source_length, true, true};
    }

    u32 ch = s[0] & utf8_inital_byte_mask[continuation_bytes];

    for (s64 i = 1; i <= continuation_bytes; i++) {  // Do nothing if it is 0.
        ch = ch << 6;
        if (strict) if ((s[i] & 0xC0) != 0x80)  return (Utf8_To_Utf32_Result){UNI_REPLACEMENT_CHAR, i - 1, true, true};
    	ch |= s[i] & 0x3F;
    }

    if (strict) {
        if (ch > UNI_MAX_UTF16 ||
          (SURROGATES_START <= ch && ch <= SURROGATES_END) ||
          (ch <= 0x0000007F && continuation_bytes != 0) ||
          (ch <= 0x000007FF && continuation_bytes != 1) ||
          (ch <= 0x0000FFFF && continuation_bytes != 2) ||
          continuation_bytes > 3) {
            return (Utf8_To_Utf32_Result){UNI_REPLACEMENT_CHAR, continuation_bytes+1, true, true};
        }
    }

    if (ch > UNI_MAX_UTF32) {
        ch = UNI_REPLACEMENT_CHAR;
    }

	return (Utf8_To_Utf32_Result){ ch, continuation_bytes+1, false, false };
}

// Convert single utf8 character to utf16 code units
Utf8_To_Utf16_Result one_utf8_to_utf16(u8 *s, s64 source_length, bool strict) {
    Utf8_To_Utf32_Result utf32_res = one_utf8_to_utf32(s, source_length, strict);
    Utf8_To_Utf16_Result res = {0};
    res.utf32 = utf32_res.utf32;
    res.continuation_bytes = utf32_res.continuation_bytes;
    res.reached_end = utf32_res.reached_end;
    res.error = utf32_res.error;

    if (res.error) {
        res.utf32 = UNI_REPLACEMENT_CHAR;
    }

    if (res.utf32 <= 0xFFFF) {
        res.utf32 = res.utf32;
    }
    else if (res.utf32 <= UNI_MAX_UTF16) {
        res.utf32 -= UTF16_SURROGATE_OFFSET;
        res.utf32 = UTF16_SURROGATE_HIGH_START + ((res.utf32 >> 10) & UTF16_SURROGATE_MASK);
        res.utf32 = (UTF16_SURROGATE_LOW_START) | (res.utf32 & UTF16_SURROGATE_MASK);
    }
    else {
        res.utf32 = UNI_REPLACEMENT_CHAR;
    }

    return res;
}

#endif //OSTD_IMPL
/* End include: unicode.h */


/* Begin include: memory.h */
#if 0
#endif

/////
// Allocator
/////

typedef enum Allocator_Message {
    ALLOCATOR_ALLOCATE,
    ALLOCATOR_REALLOCATE,
    ALLOCATOR_FREE
} Allocator_Message;
typedef void*(*Allocator_Proc)(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 flags);

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

inline string string_allocate(Allocator a, u64 n);
inline void string_deallocate(Allocator a, string s);

/////
// Arena
/////

typedef struct Arena {
    void *start;
    void *position;
    u64 reserved_size;
    u64 allocated_size;
} Arena;

Arena make_arena(u64 reserved_size, u64 initial_allocated_size);
void *arena_push(Arena *arena, u64 size);
void arena_pop(Arena *arena, u64 size);
void arena_reset(Arena *arena);
void free_arena(Arena arena);

void* arena_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64);
unit_local inline Allocator arena_allocator(Arena *a) { return (Allocator) { a, arena_allocator_proc }; }

/////
// Temporary storage
/////

// todo(charlie) temporary storage might get bloated with large temporary allocations,
// so we should provide a way to shrink temporary storage.

Allocator get_temp(void);
void reset_temporary_storage(void);
void *tallocate(size_t n);




inline void *allocate(Allocator a, u64 n) {
    return a.proc(ALLOCATOR_ALLOCATE, a.data, 0, 0, n, 0);
}
inline void *reallocate(Allocator a, void *p, u64 old_n, u64 n) {
    return a.proc(ALLOCATOR_REALLOCATE, a.data, p, old_n, n, 0);
}
inline void deallocate(Allocator a, void *p) {
    a.proc(ALLOCATOR_FREE, a.data, p, 0, 0, 0);
}

inline void *allocatef(Allocator a, u64 n, u64 flags) {
    return a.proc(ALLOCATOR_ALLOCATE, a.data, 0, 0, n, flags);
}
inline void *reallocatef(Allocator a, void *p, u64 old_n, u64 n, u64 flags) {
    return a.proc(ALLOCATOR_REALLOCATE, a.data, p, old_n, n, flags);
}
inline void deallocatef(Allocator a, void *p, u64 flags) {
    a.proc(ALLOCATOR_FREE, a.data, p, 0, 0, flags);
}

inline string string_allocate(Allocator a, u64 n) {
    return (string) {n, (u8*)allocate(a, n)};
}
inline void string_deallocate(Allocator a, string s) {
    deallocate(a, s.data);
}

inline string string_copy(Allocator a, string s) {
    string new_s = string_allocate(a, s.count);
    memcpy(new_s.data, s.data, s.count);
    return new_s;
}

#ifdef OSTD_IMPL

unit_local Arena _temp_arena;
unit_local Allocator _temp;
unit_local bool _temp_initted = false;

unit_local inline void _lazy_init_temporary_storage(void) {
    if (_temp_initted) return;

#if OS_FLAGS & OS_FLAG_EMSCRIPTEN
    _temp_arena = make_arena(1024*1024, 1024*1024);
#else
    _temp_arena = make_arena(sys_get_info().page_size*6900, 1024);
#endif
    _temp = (Allocator) { &_temp_arena, arena_allocator_proc };

    _temp_initted = true;
}
Allocator get_temp(void) {
    _lazy_init_temporary_storage();
    return _temp;
}
void reset_temporary_storage(void) {
    _lazy_init_temporary_storage();
    arena_reset(&_temp_arena);
}
void *tallocate(size_t n) {
    _lazy_init_temporary_storage();

    return allocate(_temp, n);
}

Arena make_arena(u64 reserved_size, u64 initial_allocated_size) {
    assert(reserved_size >= initial_allocated_size);

#if OS_FLAGS & OS_FLAG_EMSCRIPTEN
    assertmsg(reserved_size == initial_allocated_size, STR("Emscripten does not support reserved-only memory allocations. Arena initial allocation size must match reserved_size"));
#endif // OS_FLAGS & OS_FLAG_EMSCRIPTEN

    System_Info info = sys_get_info();

    // Align to page size
    reserved_size = (reserved_size + info.page_size - 1) & ~(info.page_size - 1);
    initial_allocated_size = (initial_allocated_size + info.page_size - 1) & ~(info.page_size - 1);

    assert(initial_allocated_size <= reserved_size);

    Arena arena;

    if (reserved_size > initial_allocated_size) {
        arena.start = sys_map_pages(SYS_MEMORY_RESERVE, 0, reserved_size/info.page_size);
        assert(arena.start);
        void *allocate_result = sys_map_pages(SYS_MEMORY_ALLOCATE, arena.start, initial_allocated_size/info.page_size);
        assert(allocate_result == arena.start);
    } else {
        arena.start = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, reserved_size/info.page_size);
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

    // todo(charlie)  use a temp scratch memory here
    Mapped_Memory_Info pointers[4096];
    sys_query_mapped_regions(start, end, pointers, pointer_count);

    u32 i;
    for (i = 0; i < pointer_count; i += 1) {
        sys_unmap_pages(pointers[i].base);
    }
}

void *arena_push(Arena *arena, u64 size) {

    System_Info info = sys_get_info();

    // Align to 8
    size = (size + 7u) & ~(7u);

    void *allocated_tail = (u8*)arena->start + arena->allocated_size;
    void *reserved_tail = (u8*)arena->start + arena->reserved_size;

    if ((u64)arena->position + size > (u64)reserved_tail) {
        return 0;
    }

    if ((u64)arena->position + size > (u64)allocated_tail) {

        u64 amount_to_allocate = ((u64)arena->position + size) - (u64)allocated_tail;

        amount_to_allocate = (amount_to_allocate + info.page_size-1) & ~(info.page_size-1);

        u64 pages_to_allocate = amount_to_allocate / info.page_size;

        void *allocate_result = sys_map_pages(SYS_MEMORY_ALLOCATE, allocated_tail, pages_to_allocate);
        assertmsg(allocate_result == allocated_tail, "Failed allocating pages in arena");

        arena->allocated_size += amount_to_allocate;
    }

    void *p = arena->position;
    arena->position = (u8*)arena->position + size;

    return p;
}

void arena_pop(Arena *arena, u64 size) {
    arena->position = (u8*)arena->position - size;
    if ((u64)arena->position < (u64)arena->start)  arena->position = arena->start;
}

void* arena_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 flags) {
    (void)flags;
    Arena *a = (Arena*)data;
    switch (msg) {
        case ALLOCATOR_ALLOCATE:
        {
            return arena_push(a, n);
        }
        case ALLOCATOR_REALLOCATE:
        {
            void* p = arena_push(a, n);
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

#endif // OSTD_IMPL
/* End include: memory.h */


/* Begin include: var_args.h */
#if 0
#endif

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
            ? **(t**)((ap += sizeof(uintptr)) - sizeof(uintptr))             \
            :  *(t* )((ap += sizeof(uintptr)) - sizeof(uintptr)))
        #define __crt_va_end(ap)        ((void)(ap = (va_list)0))

        #define va_start __crt_va_start
        #define va_arg   __crt_va_arg
        #define va_end   __crt_va_end
        #define va_copy(destination, source) ((destination) = (source))
    #elif COMPILER_FLAGS & COMPILER_FLAG_CLANG_GNU
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

#define _WRAP_VAR(x) &(Var_Arg) {sizeof(x) >= 8 ? *(u64*)&x : sizeof(x) >= 4 ? *(u32*)&x : sizeof(x) >= 2 ? *(u16*)&x : *(u8*)&x, sizeof(x) >= 8 ? *(float64*)&x : sizeof(x) >= 4 ? (float64)*(float32*)&x : 0, sizeof(x) >= sizeof(string) ? *(string*)&(x) : (string){0}, sizeof(x)}


/* Begin include: var_args_macros.h */
#define MAX_VAR_ARGS 70

#define PP_NARG(...) PP_ARG_N(__VA_ARGS__, PP_RSEQ_N())

#define PP_ARG_N(...) PP_ARG_N_(__VA_ARGS__, DUMMY)

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

/* End include: var_args_macros.h */

/* End include: var_args.h */

/* Begin include: print.h */
#if 0
#endif

/*

    TODO:

        - Specify int base
            %ib16 - base 16
        - Padding, 0 padding
            %i-4   "   5"
                   "  81"
            %i4    "5   "
                   "81  "
            %i04   "0005"
                   "0081"
        - Decimal places
            %f.3   "1.123"
            %f.5   "1.12340"

            %f04.3 "0001.123""

        - Null terminated string %s0 or %cs or %ns

        - Stack-backed buffered print() (instead of temporary allocation)


*/

//////
// Formatting
//////

// note(charlie) comma-swallowing is a hit on #Portability
#define format_string(buffer, buffer_size, fmt, ...)  _format_string_ugly(buffer, buffer_size, STR(fmt), ##__VA_ARGS__)
#define format_strings(buffer, buffer_size, fmt, ...)  _format_string_ugly(buffer, buffer_size, fmt, ##__VA_ARGS__)

u64 format_string_args(void *buffer, u64 buffer_size, string fmt, u64 arg_count, Var_Arg *args, u64 *consumed_args);

u64 format_signed_int(s64 x, int base, void *buffer, u64 buffer_size);
u64 format_unsigned_int(u64 x, int base, void *buffer, u64 buffer_size);
u64 format_float(float64 x, int decimal_places, void *buffer, u64 buffer_size);

//////
// Printing
//////

typedef struct Source_Location {
    u64 line;
    string file;
    string function;
} Source_Location;
#define HERE(...) (Source_Location) {__LINE__, STR(__FILE__), STR(__func__)}

// note(charlie) comma-swallowing is a hit on #Portability
#define sprint(allocator, fmt, ...)  _sprint_ugly(allocator,  STR(fmt), ##__VA_ARGS__)
#define sprints(allocator, fmt, ...) _sprint_ugly(allocator,  fmt, ##__VA_ARGS__)
#define tprint(fmt, ...)             _tprint_ugly(STR(fmt), ##__VA_ARGS__)
#define tprints(fmt, ...)            _tprint_ugly(fmt, ##__VA_ARGS__)
#define print(fmt, ...)              _print_ugly(STR(fmt), ##__VA_ARGS__)
#define prints(fmt, ...)             _print_ugly(fmt, ##__VA_ARGS__)

string sprint_args(Allocator a, string fmt, u64 arg_count, Var_Arg *args);
string tprint_args(string fmt, u64 arg_count, Var_Arg *args);
void   print_args(string fmt, u64 arg_count, Var_Arg *args);
void   log_args(u64 flags, Source_Location location, string fmt, u64 arg_count, Var_Arg *args);

typedef void (*Logger_Proc)(string message, u64 flags, Source_Location location);
extern Logger_Proc logger;

void default_logger(string message, u64 flags, Source_Location location);
#define log(flags, fmt, ...)              _log_ugly(flags, STR(fmt), ##__VA_ARGS__)
#define logs(flags, fmt, ...)             _log_ugly(flags, fmt, ##__VA_ARGS__)

//////
// Internal
//////

// note(charlie): These bloat the code and makes it less good at self-documenting,
// so I made a prettier indirection for the readable part of the file.

#define _format_string_ugly(buffer, buffer_size, fmt, ...)\
    MAKE_WRAPPED_CALL(format_string_impl, _make_format_string_desc(buffer, buffer_size, fmt), ##__VA_ARGS__)
#define _sprint_ugly(allocator, fmt, ...)\
    MAKE_WRAPPED_CALL(sprint_impl, _make_print_desc(allocator, fmt), ##__VA_ARGS__)
#define _tprint_ugly(fmt, ...)\
    MAKE_WRAPPED_CALL(tprint_impl, _make_print_desc((Allocator){0}, fmt), ##__VA_ARGS__)
#define _print_ugly(fmt, ...)\
    MAKE_WRAPPED_CALL(print_impl, _make_print_desc((Allocator){0}, fmt), ##__VA_ARGS__)

#define _log_ugly(flags, fmt, ...)\
    MAKE_WRAPPED_CALL(log_impl, _make_log_desc((Allocator){0}, fmt, flags, HERE()), ##__VA_ARGS__)

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
} _Print_Desc;
unit_local inline _Print_Desc _make_print_desc(Allocator a, string fmt) {
    return (_Print_Desc) {a, fmt};
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
void log_impl(_Log_Desc desc, u64 arg_count, ...);

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
                    to_write -= buffer_size - (written + to_write);
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

    u64 n = format_string_args(0, 0, fmt, arg_count, args, 0);

    u8 buffer[4096];
    u64 written = 0;

    while (written < n) {
        u64 to_write = min(n, 4096);
        u64 consumed_args;
        format_string_args(buffer, to_write, fmt, arg_count, args, &consumed_args);
        args += consumed_args;
        arg_count -= consumed_args;

        sys_write(sys_get_stdout(), buffer, to_write);

        written += to_write;
    }
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

    u64 digit_count = (u64)(ln64((float64)abs_val)/ln64((float64)base));

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

Logger_Proc logger = 0;

#endif // OSTD_IMPL

/* End include: print.h */


/* Begin include: graphics.h */
#if 0
#endif

typedef enum Oga_Result {
    OGA_OK,
    
    // Trying to use device features that were not available.
    // Check Oga_Device::features flags for whether or not a feature is available.
    OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES,
    // The given family index is not within the range 0 .. Oga_Device::logical_engine_family_count
    OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE,
    // The given logical_engine creation count overflows that of Oga_Logical_Engine_Family_Info::logical_engine_capacity
    OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW,
} Oga_Result;

unit_local inline string oga_get_result_name(Oga_Result r) {
    switch (r) {
        case OGA_OK: return STR("OGA_OK");
        case OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES:   return STR("OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE: return STR("OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW:  return STR("OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW");
        default: return STR("<>");
    }
    return STR("<>");
}
unit_local inline string oga_get_result_message(Oga_Result r) {
    switch (r) {
        case OGA_OK: return STR("No error");
        case OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES:
            return STR("Trying to use device features that were not available. Check Oga_Device::features flags for whether or not a feature is available.");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE:
            return STR("The given family index is not within the range 0 .. Oga_Device::logical_engine_family_count");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW:
            return STR("The given logical_engine creation count overflows that of Oga_Logical_Engine_Family_Info::logical_engine_capacity");
        default: return STR("<>");
    }
    return STR("<>");
}

typedef enum Oga_Format_Kind {
    OGA_FORMAT_R8_UNORM,
    OGA_FORMAT_R8_SNORM,
    OGA_FORMAT_R8_UINT,
    OGA_FORMAT_R8_SINT,
    OGA_FORMAT_R8G8_UNORM,
    OGA_FORMAT_R8G8_SNORM,
    OGA_FORMAT_R8G8_UINT,
    OGA_FORMAT_R8G8_SINT,
    OGA_FORMAT_R8G8B8A8_UNORM,
    OGA_FORMAT_R8G8B8A8_SNORM,
    OGA_FORMAT_R8G8B8A8_UINT,
    OGA_FORMAT_R8G8B8A8_SINT,
    OGA_FORMAT_R8G8B8A8_SRGB,
    OGA_FORMAT_B8G8R8A8_UNORM,
    OGA_FORMAT_B8G8R8A8_SNORM,
    OGA_FORMAT_B8G8R8A8_UINT,
    OGA_FORMAT_B8G8R8A8_SINT,
    OGA_FORMAT_B8G8R8A8_SRGB,
    OGA_FORMAT_R16G16B16A16_SFLOAT,
    OGA_FORMAT_R32G32B32A32_SFLOAT,
    OGA_FORMAT_DEPTH32_SFLOAT,
    OGA_FORMAT_DEPTH32_SFLOAT_S8_UINT,
    OGA_FORMAT_DEPTH24_UNORM_S8_UINT,
    OGA_FORMAT_DEPTH16_UNORM
} Oga_Format_Kind;

unit_local inline string oga_format_str(Oga_Format_Kind f) {
    switch (f) {
        case OGA_FORMAT_R8_UNORM:               return RSTR(R8_UNORM);
        case OGA_FORMAT_R8_SNORM:               return RSTR(R8_SNORM);
        case OGA_FORMAT_R8_UINT:                return RSTR(R8_UINT);
        case OGA_FORMAT_R8_SINT:                return RSTR(R8_SINT);
        case OGA_FORMAT_R8G8_UNORM:             return RSTR(R8G8_UNORM);
        case OGA_FORMAT_R8G8_SNORM:             return RSTR(R8G8_SNORM);
        case OGA_FORMAT_R8G8_UINT:              return RSTR(R8G8_UINT);
        case OGA_FORMAT_R8G8_SINT:              return RSTR(R8G8_SINT);
        case OGA_FORMAT_R8G8B8A8_UNORM:         return RSTR(R8G8B8A8_UNORM);
        case OGA_FORMAT_R8G8B8A8_SNORM:         return RSTR(R8G8B8A8_SNORM);
        case OGA_FORMAT_R8G8B8A8_UINT:          return RSTR(R8G8B8A8_UINT);
        case OGA_FORMAT_R8G8B8A8_SINT:          return RSTR(R8G8B8A8_SINT);
        case OGA_FORMAT_R8G8B8A8_SRGB:          return RSTR(R8G8B8A8_SRGB);
        case OGA_FORMAT_B8G8R8A8_UNORM:         return RSTR(B8G8R8A8_UNORM);
        case OGA_FORMAT_B8G8R8A8_SNORM:         return RSTR(B8G8R8A8_SNORM);
        case OGA_FORMAT_B8G8R8A8_UINT:          return RSTR(B8G8R8A8_UINT);
        case OGA_FORMAT_B8G8R8A8_SINT:          return RSTR(B8G8R8A8_SINT);
        case OGA_FORMAT_B8G8R8A8_SRGB:          return RSTR(B8G8R8A8_SRGB);
        case OGA_FORMAT_R16G16B16A16_SFLOAT:    return RSTR(R16G16B16A16_SFLOAT);
        case OGA_FORMAT_R32G32B32A32_SFLOAT:    return RSTR(R32G32B32A32_SFLOAT);
        case OGA_FORMAT_DEPTH32_SFLOAT:         return RSTR(DEPTH32_SFLOAT);
        case OGA_FORMAT_DEPTH32_SFLOAT_S8_UINT: return RSTR(DEPTH32_SFLOAT_S8_UINT);
        case OGA_FORMAT_DEPTH24_UNORM_S8_UINT:  return RSTR(DEPTH24_UNORM_S8_UINT);
        case OGA_FORMAT_DEPTH16_UNORM:          return RSTR(DEPTH16_UNORM);
        default: return RSTR(<>);
    }
    return RSTR(<>);
}

typedef enum Oga_Memory_Property_Flag {
    // Memory is near GPU and accessed with high performance
    OGA_MEMORY_PROPERTY_GPU_LOCAL  = 0x00000001,
    // Memory can be mapped
    OGA_MEMORY_PROPERTY_GPU_TO_CPU_MAPPABLE  = 0x00000002,
    // Memory is directly reflected on CPU. Mapping is not needed to access memory
    OGA_MEMORY_PROPERTY_GPU_TO_CPU_REFLECTED = 0x00000004,
    // Cached memory is accessed quicker, but does not instantly reflect GPU writes
    OGA_MEMORY_PROPERTY_GPU_TO_CPU_CACHED   = 0x00000008,
} Oga_Memory_Property_Flag;

// Unique identifer/handle for an instance of something.
// For example, if we need to know if two Oga_Device's are the same, we compare
// test them with a,id == b.id.
typedef void* Oga_Id;

typedef enum Oga_Sample_Count_Flag {
    OGA_SAMPLE_COUNT_1 = 1 << 0,
    OGA_SAMPLE_COUNT_2 = 1 << 1,
    OGA_SAMPLE_COUNT_4 = 1 << 2,
    OGA_SAMPLE_COUNT_8 = 1 << 3,
    OGA_SAMPLE_COUNT_16 = 1 << 4,
    OGA_SAMPLE_COUNT_32 = 1 << 5,
    OGA_SAMPLE_COUNT_64 = 1 << 6,
    OGA_SAMPLE_COUNT_128 = 1 << 7
} Oga_Sample_Count_Flag;

//////
// Device

typedef enum Oga_Logical_Engine_Family_Flags {
    OGA_LOGICAL_ENGINE_GRAPHICS = 1 << 0,
    OGA_LOGICAL_ENGINE_COMPUTE = 1 << 1,
    OGA_LOGICAL_ENGINE_TRANSFER = 1 << 2,
    OGA_LOGICAL_ENGINE_PRESENT = 1 << 3,
} Oga_Logical_Engine_Family_Flags;

typedef struct Oga_Logical_Engine_Family_Info {
    Oga_Logical_Engine_Family_Flags flags;
    u32 logical_engine_capacity;
} Oga_Logical_Engine_Family_Info;

typedef struct Oga_Memory_Heap {
    Oga_Memory_Property_Flag properties;
    u64 size;
} Oga_Memory_Heap;

typedef enum Oga_Device_Kind {
    OGA_DEVICE_DISCRETE,
    OGA_DEVICE_INTEGRATED,
    OGA_DEVICE_CPU, // Software implementations
    OGA_DEVICE_OTHER,
} Oga_Device_Kind;

// todo(charlie) populate this with an exhaustive list. 
typedef struct Oga_Device_Limits {
    u64 max_shader_items_sets_per_stage;
    
    u64 max_fast_data_blocks_per_stage;
    u64 max_large_data_blocks_per_stage;
    u64 max_fast_images_per_stage;
    u64 max_large_images_per_stage;
    u64 max_samplers_per_stage;
    
    u64 max_fast_data_blocks_per_layout;
    u64 max_large_data_blocks_per_layout;
    u64 max_fast_images_per_layout;
    u64 max_large_images_per_layout;
    u64 max_samplers_per_layout;
    
    u64 max_memory_allocations;
    u64 max_sampler_allocations;
    
    u64 max_image_dimension_1d;
    u64 max_image_dimension_2d;
    u64 max_image_dimension_3d;
    
    u64 max_fast_access_data_block_size;
    
    u64 max_vertex_layout_attributes;
    u64 max_vertex_layout_bindings;
    u64 max_vertex_layout_attribute_offset;
    u64 max_vertex_layout_binding_stride;
    
    u64 max_fragment_stage_output_attachments;
    
    float32 max_sampler_anisotropy;
    
    u64 max_viewports;
    u64 max_viewport_width;
    u64 max_viewport_height;
    
    u64 max_framebuffer_width;
    u64 max_framebuffer_height;
    
    u64 max_color_attachments;
    
    u64 min_memory_map_alignment;
    
    Oga_Sample_Count_Flag supported_sample_counts_framebuffer;
    
    Oga_Sample_Count_Flag supported_sample_counts_fast_image_float;
    Oga_Sample_Count_Flag supported_sample_counts_large_image_float;
    Oga_Sample_Count_Flag supported_sample_counts_fast_image_int;
    Oga_Sample_Count_Flag supported_sample_counts_large_image_int;
    
    
} Oga_Device_Limits;

typedef u64 Oga_Device_Feature_Flag;

#define OGA_DEVICE_FEATURE_GRAPHICS_TIMESTAMP (1 << 0)
#define OGA_DEVICE_FEATURE_COMPUTE_TIMESTAMP (1 << 1)

#define OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES 32
#define OGA_MAX_DEVICE_LOGICAL_ENGINES_PER_FAMILY 32
#define OGA_MAX_MEMORY_HEAPS_PER_DEVICE 32
typedef struct Oga_Device {
    void *id;
    
    Oga_Device_Kind kind;

    // string
    u8 device_name_data[256];
    u64 device_name_length;
    
    string vendor_name;
    u32 driver_version_raw;
    
    // string
    u8 driver_version_data[128];
    u64 driver_version_length;
    
    Oga_Device_Limits limits;

    Oga_Logical_Engine_Family_Info logical_engine_family_infos[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES];
    u32 logical_engine_family_count;
    
    Oga_Format_Kind depth_format;
    
    Oga_Memory_Heap memory_heaps[OGA_MAX_MEMORY_HEAPS_PER_DEVICE];
    u64 memory_heap_count;
    u64 total_gpu_local_memory;
    
    Oga_Device_Feature_Flag features;

} Oga_Device;

typedef enum Oga_Device_Pick_Flag {
    OGA_DEVICE_PICK_PREFER_DISCRETE = 1 << 0,
    OGA_DEVICE_PICK_PREFER_INTEGRATED = 1 << 1,
    OGA_DEVICE_PICK_PREFER_CPU = 1 << 2,
    OGA_DEVICE_PICK_REQUIRE_DISCRETE = 1 << 3,
    OGA_DEVICE_PICK_REQUIRE_INTEGRATED = 1 << 4,
    OGA_DEVICE_PICK_REQUIRE_CPU = 1 << 5,
} Oga_Device_Pick_Flag;

u64 oga_query_devices(Oga_Device *buffer, u64 buffer_count);
Oga_Device *oga_get_devices(Allocator a, u64 *count);

typedef struct Oga_Pick_Device_Result {
    bool passed;
    Oga_Device device;
    Oga_Device_Pick_Flag failed_pick_flags;
    Oga_Device_Feature_Flag failed_required_features;
    Oga_Device_Feature_Flag failed_preferred_features;
} Oga_Pick_Device_Result;
Oga_Pick_Device_Result oga_pick_device(Oga_Device_Pick_Flag pick_flags, Oga_Device_Feature_Flag required_features, Oga_Device_Feature_Flag preferred_features);

//////////
/// Oga Context


typedef struct Oga_Logical_Engines_Create_Desc {
    u32 count;
    float32 priorities[OGA_MAX_DEVICE_LOGICAL_ENGINES_PER_FAMILY]; // normalized 0.0-1.0.
} Oga_Logical_Engines_Create_Desc;


typedef struct Oga_Context_Desc {
    // Indices match to that of Oga_Device::logical_engine_family_infos.
    // So the create logical_engines of family 0, you set the desc in logical_engine_create_descs[0].
    // Leave descs uninitialized to make no logical_engines in that family.
    Oga_Logical_Engines_Create_Desc logical_engine_create_descs[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES];    
    Oga_Device_Feature_Flag enabled_features;
} Oga_Context_Desc;

// Some hardware expose their engines, some don't.
// So we deal with Logical Engines, which may or may not map directly to
// hardware engines.
// Equivalent to a vulkan Queue
typedef struct Oga_Logical_Engine {
    void *id;
    u32 index;
} Oga_Logical_Engine;

typedef struct Oga_Logical_Engine_Group {
    Oga_Logical_Engine logical_engines[OGA_MAX_DEVICE_LOGICAL_ENGINES_PER_FAMILY];
    u64 logical_engine_count;
} Oga_Logical_Engine_Group;

typedef struct Oga_Context {
    void *id;
    Oga_Device device;
    Oga_Logical_Engine_Group logical_engines_by_family[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES];
} Oga_Context;

Oga_Result oga_init_context(Oga_Device target_device, Oga_Context_Desc desc, Oga_Context *context);
void oga_uninit_context(Oga_Context *context);

//////////
/// Memory

typedef void* Oga_Memory_Handle;

typedef enum Oga_Allocator_Message {
    OGA_ALLOCATOR_ALLOCATE,
    OGA_ALLOCATOR_DEALLOCATE
} Oga_Allocator_Message;

typedef Oga_Memory_Handle (*Oga_Allocator_Proc_)(
        Oga_Allocator_Message msg,
        Oga_Memory_Handle mem,
        u64 size,
        Oga_Memory_Property_Flag props,
        u64 flags
    );
typedef Oga_Allocator_Proc_ Oga_Allocator_Proc;

// Allocator for video memory
typedef struct Oga_Allocator {
    void *data;
    Oga_Allocator_Proc proc;
} Oga_Allocator;

Oga_Memory_Handle oga_allocate(Oga_Allocator a, u64 size, Oga_Memory_Property_Flag props, u64 flags);
void oga_deallocate(Oga_Allocator a, Oga_Memory_Handle mem);

Oga_Memory_Handle oga_default_allocator(Oga_Allocator_Message msg, Oga_Memory_Handle mem, u64 size, Oga_Memory_Property_Flag props, u64 flags);

typedef enum Oga_Memory_View_Kind {
    OGA_MEMORY_VIEW_KIND_SHADER_ITEM_DESCRIPTOR,
    OGA_MEMORY_VIEW_KIND_VERTEX_LIST,
    OGA_MEMORY_VIEW_KIND_INDEX_LIST,
    OGA_MEMORY_VIEW_KIND_COPY_TASK,
} Oga_Memory_View_Kind;

typedef enum Oga_Memory_View_Flag {
    OGA_MEMORY_VIEW_FLAG_COPY_DST = 1 << 0,
    OGA_MEMORY_VIEW_FLAG_COPY_SRC = 1 << 1,
} Oga_Memory_View_Flag;

typedef enum Oga_Shader_Item_Descriptor_Kind {
    OGA_SHADER_ITEM_DESCRIPTOR_KIND_DATA_BLOCK,
    OGA_SHADER_ITEM_DESCRIPTOR_KIND_IMAGE1D,
    OGA_SHADER_ITEM_DESCRIPTOR_KIND_IMAGE2D,
    OGA_SHADER_ITEM_DESCRIPTOR_KIND_IMAGE3D,
} Oga_Shader_Item_Descriptor_Kind;

typedef enum Oga_Shader_Item_Descriptor_Flag {
    OGA_SHADER_ITEM_DESCRIPTOR_FLAG_READ,
    OGA_SHADER_ITEM_DESCRIPTOR_FLAG_WRITE,
    
    // When a shader item descriptor is flagged with large or write, it can have larger
    // storage (or be written to) at the cost of memory access performance.
    // see limits max_fast_access_xxxxx_size
    OGA_SHADER_ITEM_DESCRIPTOR_FLAG_LARGE,
} Oga_Shader_Item_Descriptor_Flag;

typedef struct Oga_Shader_Item_Descriptor_Desc {
    Oga_Shader_Item_Descriptor_Kind kind;
    Oga_Shader_Item_Descriptor_Flag flags;
    
} Oga_Shader_Item_Descriptor_Desc;

typedef struct Oga_Vertex_List_Desc  {
    int _;  
} Oga_Vertex_List_Desc;

typedef struct Oga_Index_List_Desc  {
    int _;  
    
} Oga_Index_List_Desc;

typedef struct Oga_Copy_Task_Desc  {
    int _;  
    
} Oga_Copy_Task_Desc;

typedef struct Oga_Memory_View_Desc {
    Oga_Memory_View_Kind kind;
    Oga_Memory_View_Flag flags;
    
    Oga_Memory_Handle memory;
    
    union {
        Oga_Shader_Item_Descriptor_Desc shader_item_descriptor;
        Oga_Vertex_List_Desc vertex_list;
        Oga_Index_List_Desc index_list;
        Oga_Copy_Task_Desc copy_task;
    } UNION;
} Oga_Memory_View_Desc;

//Oga_Result oga_make_memory_view(Oga_Context c, Oga_Memory_View_Desc desc);


#ifdef OGA_IMPL_AUTO
    #if (OS_FLAGS & OS_FLAG_WEB)
        #define OGA_IMPL_WEBGPU
    #elif (OS_FLAGS & OS_FLAG_WINDOWS)
        #define OGA_IMPL_D3D12
    #elif (OS_FLAGS & OS_FLAG_APPLE)
        #define OGA_IMPL_METAL
    #elif OS_FLAGS != 0
        // If recognized OS, fallback to vulkan, because it's probably supported.
        // todo(charlie) consoles
        #define OGA_IMPL_VULKAN
    #endif
#endif // OGA_IMPL_HARDWARE_AUTO

#ifdef OSTD_IMPL

Oga_Pick_Device_Result oga_pick_device(Oga_Device_Pick_Flag pick_flags, Oga_Device_Feature_Flag required_features, Oga_Device_Feature_Flag preferred_features) {
    
    Oga_Device devices[32];
    u64 device_count = oga_query_devices(devices, 32);
    
    s64 device_scores[32] = {0};
    
    Oga_Pick_Device_Result results[32] = {0};
    
    for (u64 i = 0; i < device_count; i += 1) {
        Oga_Device device = devices[i];
        s64 *pscore = &device_scores[i];
        
        results[i].device = device;
        
        if ((pick_flags & OGA_DEVICE_PICK_REQUIRE_DISCRETE) && device.kind != OGA_DEVICE_DISCRETE)  {
            results[i].passed = false;
            results[i].failed_pick_flags |= OGA_DEVICE_PICK_REQUIRE_DISCRETE;
            continue;
        }
        if ((pick_flags & OGA_DEVICE_PICK_REQUIRE_INTEGRATED) && device.kind != OGA_DEVICE_INTEGRATED)  {
            results[i].passed = false;
            results[i].failed_pick_flags |= OGA_DEVICE_PICK_REQUIRE_INTEGRATED;
            continue;
        }
        if ((pick_flags & OGA_DEVICE_PICK_REQUIRE_CPU) && device.kind != OGA_DEVICE_CPU)  {
            results[i].passed = false;
            results[i].failed_pick_flags |= OGA_DEVICE_PICK_REQUIRE_CPU;
            continue;
        }
        
        if ((required_features & device.features) != required_features) {
            results[i].passed = false;
            results[i].failed_required_features |= ((required_features & device.features) & required_features); 
            continue;
        }
            
        if ((pick_flags & OGA_DEVICE_PICK_PREFER_DISCRETE) && device.kind == OGA_DEVICE_DISCRETE) 
            *pscore += 1000;
        if ((pick_flags & OGA_DEVICE_PICK_PREFER_INTEGRATED) && device.kind == OGA_DEVICE_INTEGRATED) 
            *pscore += 1000;
        if ((pick_flags & OGA_DEVICE_PICK_PREFER_CPU) && device.kind == OGA_DEVICE_CPU) 
            *pscore += 1000;
        
        u64 preferred_features_count = 0;
        for (u64 f = 0; f < 64; f += 1) {
            // Feature flag is preferred ?
            if (preferred_features & (1 << f)) {
                preferred_features_count += 1;
            }
        }
        
        if (preferred_features_count) {
            s64 score_per_feature = 1000/preferred_features_count;
            
            for (u64 f = 0; f < 64; f += 1) {
                // Feature flag is preferred ?
                if (preferred_features & (1 << f)) {
                    // Preferred feature flag is set on device ?
                    if (device.features & (1 << f)) {
                        *pscore += score_per_feature;
                    } else {
                        results[i].failed_preferred_features |= (1 << f);
                    }
                } 
            }
        } else {
            *pscore += 1;
        }
        
        results[i].passed = *pscore > 0;
    }
    
    s64 max_score = 0;
    u64 winner_index = 0;
    for (u64 i = 0; i < device_count; i += 1) {
        if (device_scores[i] > max_score) {
            max_score = device_scores[i];
            winner_index = i;
        }
    }
    return results[winner_index];
}

#define VENDOR_ID_NVIDIA   0x10DE
#define VENDOR_ID_AMD      0x1002
#define VENDOR_ID_INTEL    0x8086
#define VENDOR_ID_ARM      0x13B5
#define VENDOR_ID_IMGTEC   0x1010
#define VENDOR_ID_QUALCOMM 0x5143

unit_local inline string _str_vendor_id(u32 id) {
    switch (id) {
        case VENDOR_ID_NVIDIA:   return RSTR(Nvidia);
        case VENDOR_ID_AMD:      return RSTR(Amd);
        case VENDOR_ID_INTEL:    return RSTR(Intel);
        case VENDOR_ID_ARM:      return RSTR(Arm);
        case VENDOR_ID_IMGTEC:   return RSTR(ImgTec);
        case VENDOR_ID_QUALCOMM: return RSTR(Qualcomm);
        default: return RSTR(<Unknown Vendor ID>);
    }

}

unit_local u64 _format_driver_version(u32 vendor_id, u32 driver_version, u8 *buffer, u64 buffer_size) {
    if (vendor_id == VENDOR_ID_NVIDIA) {
        u32 major = (driver_version >> 22) & 0x3FF;
        u32 minor = (driver_version >> 14) & 0xFF;
        u32 patch = (driver_version >> 6) & 0xFF;
        u32 build = driver_version & 0x3F;
        return format_string(buffer, buffer_size, "%u.%u.%u build %u", major, minor, patch, build);
    } else if (vendor_id == VENDOR_ID_NVIDIA) {
        u32 major = (driver_version >> 14);
        u32 minor = driver_version & 0x3FFF;
        return format_string(buffer, buffer_size, "%u.%u", major, minor);
    } else {
        return format_string(buffer, buffer_size, "%u", driver_version);
    }
}

inline string oga_format_str(Oga_Format_Kind f);

#ifdef OGA_IMPL_VULKAN

/////////////////////////////////////////////////////
//////
// :Vulkan
//////
/////////////////////////////////////////////////////

#if COMPILER_FLAGS & COMPILER_FLAG_MSC
    #pragma comment(lib, "vendors/vulkan-1.lib")
#endif // COMPILER_FLAGS & COMPILER_FLAG_MSC

#if (OS_FLAGS & (OS_FLAG_WINDOWS | OS_FLAG_LINUX | OS_FLAG_MACOS | OS_FLAG_IOS | OS_FLAG_ANDROID)) == 0
    #error Vulkan is not supported on target platform
#else

/* Begin include: graphics_vulkan.h */

#include <vulkan/vulkan.h>

// For syntax highligthing
#if 0
// noconcat
#include "../vendors/vulkan/vulkan.h"
#endif



// We manually include the vulkan-specific headers, otherwise vulkan.h will include windows.h
#if OS_FLAGS & OS_FLAG_WINDOWS
#include <vulkan/vulkan_win32.h>
#elif OS_FLAGS & OS_FLAG_LINUX
#include <vulkan/vulkan_xlib.h>
#elif OS_FLAGS & OS_FLAG_MACOS
#include <vulkan/vulkan_macos.h>
#elif OS_FLAGS & OS_FLAG_IOS
#include <vulkan/vulkan_ios.h>
#elif OS_FLAGS & OS_FLAG_ANDROID
#include <vulkan/vulkan_android.h>
#else
#error Vulkan is not supported on target platform
#endif

unit_local inline VkFormat _oga_to_vk_format(Oga_Format_Kind k) {
    switch (k) {
        case OGA_FORMAT_R8_UNORM:               return VK_FORMAT_R8_UNORM;
        case OGA_FORMAT_R8_SNORM:               return VK_FORMAT_R8_SNORM;
        case OGA_FORMAT_R8_UINT:                return VK_FORMAT_R8_UINT;
        case OGA_FORMAT_R8_SINT:                return VK_FORMAT_R8_SINT;
        case OGA_FORMAT_R8G8_UNORM:             return VK_FORMAT_R8G8_UNORM;
        case OGA_FORMAT_R8G8_SNORM:             return VK_FORMAT_R8G8_SNORM;
        case OGA_FORMAT_R8G8_UINT:              return VK_FORMAT_R8G8_UINT;
        case OGA_FORMAT_R8G8_SINT:              return VK_FORMAT_R8G8_SINT;
        case OGA_FORMAT_R8G8B8A8_UNORM:         return VK_FORMAT_R8G8B8A8_UNORM;
        case OGA_FORMAT_R8G8B8A8_SNORM:         return VK_FORMAT_R8G8B8A8_SNORM;
        case OGA_FORMAT_R8G8B8A8_UINT:          return VK_FORMAT_R8G8B8A8_UINT;
        case OGA_FORMAT_R8G8B8A8_SINT:          return VK_FORMAT_R8G8B8A8_SINT;
        case OGA_FORMAT_R8G8B8A8_SRGB:          return VK_FORMAT_R8G8B8A8_SRGB;
        case OGA_FORMAT_B8G8R8A8_UNORM:         return VK_FORMAT_B8G8R8A8_UNORM;
        case OGA_FORMAT_B8G8R8A8_SNORM:         return VK_FORMAT_B8G8R8A8_SNORM;
        case OGA_FORMAT_B8G8R8A8_UINT:          return VK_FORMAT_B8G8R8A8_UINT;
        case OGA_FORMAT_B8G8R8A8_SINT:          return VK_FORMAT_B8G8R8A8_SINT;
        case OGA_FORMAT_B8G8R8A8_SRGB:          return VK_FORMAT_B8G8R8A8_SRGB;
        case OGA_FORMAT_R16G16B16A16_SFLOAT:    return VK_FORMAT_R16G16B16A16_SFLOAT;
        case OGA_FORMAT_R32G32B32A32_SFLOAT:    return VK_FORMAT_R32G32B32A32_SFLOAT;
        case OGA_FORMAT_DEPTH32_SFLOAT:         return VK_FORMAT_D32_SFLOAT;
        case OGA_FORMAT_DEPTH32_SFLOAT_S8_UINT: return VK_FORMAT_D32_SFLOAT_S8_UINT;
        case OGA_FORMAT_DEPTH24_UNORM_S8_UINT:  return VK_FORMAT_D24_UNORM_S8_UINT;
        case OGA_FORMAT_DEPTH16_UNORM:          return VK_FORMAT_D16_UNORM;
        
        default:
        return (VkFormat)0;
    }
    return (VkFormat)0;
}
unit_local inline Oga_Format_Kind _vk_to_oga_format(VkFormat k) {
    switch ((s64)k) {
        case VK_FORMAT_R8_UNORM:            return OGA_FORMAT_R8_UNORM;
        case VK_FORMAT_R8_SNORM:            return OGA_FORMAT_R8_SNORM;
        case VK_FORMAT_R8_UINT:             return OGA_FORMAT_R8_UINT;
        case VK_FORMAT_R8_SINT:             return OGA_FORMAT_R8_SINT;
        case VK_FORMAT_R8G8_UNORM:          return OGA_FORMAT_R8G8_UNORM;
        case VK_FORMAT_R8G8_SNORM:          return OGA_FORMAT_R8G8_SNORM;
        case VK_FORMAT_R8G8_UINT:           return OGA_FORMAT_R8G8_UINT;
        case VK_FORMAT_R8G8_SINT:           return OGA_FORMAT_R8G8_SINT;
        case VK_FORMAT_R8G8B8A8_UNORM:      return OGA_FORMAT_R8G8B8A8_UNORM;
        case VK_FORMAT_R8G8B8A8_SNORM:      return OGA_FORMAT_R8G8B8A8_SNORM;
        case VK_FORMAT_R8G8B8A8_UINT:       return OGA_FORMAT_R8G8B8A8_UINT;
        case VK_FORMAT_R8G8B8A8_SINT:       return OGA_FORMAT_R8G8B8A8_SINT;
        case VK_FORMAT_R8G8B8A8_SRGB:       return OGA_FORMAT_R8G8B8A8_SRGB;
        case VK_FORMAT_B8G8R8A8_UNORM:      return OGA_FORMAT_B8G8R8A8_UNORM;
        case VK_FORMAT_B8G8R8A8_SNORM:      return OGA_FORMAT_B8G8R8A8_SNORM;
        case VK_FORMAT_B8G8R8A8_UINT:       return OGA_FORMAT_B8G8R8A8_UINT;
        case VK_FORMAT_B8G8R8A8_SINT:       return OGA_FORMAT_B8G8R8A8_SINT;
        case VK_FORMAT_B8G8R8A8_SRGB:       return OGA_FORMAT_B8G8R8A8_SRGB;
        case VK_FORMAT_R16G16B16A16_SFLOAT: return OGA_FORMAT_R16G16B16A16_SFLOAT;
        case VK_FORMAT_R32G32B32A32_SFLOAT: return OGA_FORMAT_R32G32B32A32_SFLOAT;
        case VK_FORMAT_D32_SFLOAT:          return OGA_FORMAT_DEPTH32_SFLOAT;
        case VK_FORMAT_D32_SFLOAT_S8_UINT:  return OGA_FORMAT_DEPTH32_SFLOAT_S8_UINT;
        case VK_FORMAT_D24_UNORM_S8_UINT:   return OGA_FORMAT_DEPTH24_UNORM_S8_UINT;
        case VK_FORMAT_D16_UNORM:           return OGA_FORMAT_DEPTH16_UNORM;
        
        default:
        return (Oga_Format_Kind)0;
    }
    return (Oga_Format_Kind)0;
}


unit_local inline string _str_vk_result(VkResult result) {
    switch ((s64)result) {
        case VK_SUCCESS:                                            return RSTR(VK_SUCCESS);
        case VK_NOT_READY:                                          return RSTR(VK_NOT_READY);
        case VK_TIMEOUT:                                            return RSTR(VK_TIMEOUT);
        case VK_EVENT_SET:                                          return RSTR(VK_EVENT_SET);
        case VK_EVENT_RESET:                                        return RSTR(VK_EVENT_RESET);
        case VK_INCOMPLETE:                                         return RSTR(VK_INCOMPLETE);
        case VK_ERROR_OUT_OF_HOST_MEMORY:                           return RSTR(VK_ERROR_OUT_OF_HOST_MEMORY);
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:                         return RSTR(VK_ERROR_OUT_OF_DEVICE_MEMORY);
        case VK_ERROR_INITIALIZATION_FAILED:                        return RSTR(VK_ERROR_INITIALIZATION_FAILED);
        case VK_ERROR_DEVICE_LOST:                                  return RSTR(VK_ERROR_DEVICE_LOST);
        case VK_ERROR_MEMORY_MAP_FAILED:                            return RSTR(VK_ERROR_MEMORY_MAP_FAILED);
        case VK_ERROR_LAYER_NOT_PRESENT:                            return RSTR(VK_ERROR_LAYER_NOT_PRESENT);
        case VK_ERROR_EXTENSION_NOT_PRESENT:                        return RSTR(VK_ERROR_EXTENSION_NOT_PRESENT);
        case VK_ERROR_FEATURE_NOT_PRESENT:                          return RSTR(VK_ERROR_FEATURE_NOT_PRESENT);
        case VK_ERROR_INCOMPATIBLE_DRIVER:                          return RSTR(VK_ERROR_INCOMPATIBLE_DRIVER);
        case VK_ERROR_TOO_MANY_OBJECTS:                             return RSTR(VK_ERROR_TOO_MANY_OBJECTS);
        case VK_ERROR_FORMAT_NOT_SUPPORTED:                         return RSTR(VK_ERROR_FORMAT_NOT_SUPPORTED);
        case VK_ERROR_FRAGMENTED_POOL:                              return RSTR(VK_ERROR_FRAGMENTED_POOL);
        case VK_ERROR_UNKNOWN:                                      return RSTR(VK_ERROR_UNKNOWN);
        case VK_ERROR_OUT_OF_POOL_MEMORY:                           return RSTR(VK_ERROR_OUT_OF_POOL_MEMORY);
        case VK_ERROR_INVALID_EXTERNAL_HANDLE:                      return RSTR(VK_ERROR_INVALID_EXTERNAL_HANDLE);
        case VK_ERROR_FRAGMENTATION:                                return RSTR(VK_ERROR_FRAGMENTATION);
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:               return RSTR(VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS);
        case VK_PIPELINE_COMPILE_REQUIRED:                          return RSTR(VK_PIPELINE_COMPILE_REQUIRED);
        case VK_ERROR_SURFACE_LOST_KHR:                             return RSTR(VK_ERROR_SURFACE_LOST_KHR);
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:                     return RSTR(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR);
        case VK_SUBOPTIMAL_KHR:                                     return RSTR(VK_SUBOPTIMAL_KHR);
        case VK_ERROR_OUT_OF_DATE_KHR:                              return RSTR(VK_ERROR_OUT_OF_DATE_KHR);
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:                     return RSTR(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
        case VK_ERROR_VALIDATION_FAILED_EXT:                        return RSTR(VK_ERROR_VALIDATION_FAILED_EXT);
        case VK_ERROR_INVALID_SHADER_NV:                            return RSTR(VK_ERROR_INVALID_SHADER_NV);
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: return RSTR(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:          return RSTR(VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT);
        case VK_THREAD_IDLE_KHR:                                    return RSTR(VK_THREAD_IDLE_KHR);
        case VK_THREAD_DONE_KHR:                                    return RSTR(VK_THREAD_DONE_KHR);
        case VK_OPERATION_DEFERRED_KHR:                             return RSTR(VK_OPERATION_DEFERRED_KHR);
        case VK_OPERATION_NOT_DEFERRED_KHR:                         return RSTR(VK_OPERATION_NOT_DEFERRED_KHR);
        
        case VK_RESULT_MAX_ENUM:
        default: return STR("<>");
    }
    return STR("<>");
}

#define _vk_assert(expr) do { VkResult _res = expr; string _res_str = _str_vk_result(_res); assertmsgs(expr == VK_SUCCESS, tprint("Vulkan call %s failed: %s. If you see this, you're either doing something very wrong, or there is an internal error in Oga.", STR(#expr), _res_str)); } while(0)


unit_local VkDebugUtilsMessengerEXT _vk_messenger;

unit_local VkBool32 _vk_debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT           messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT                  messageTypes,
    const VkDebugUtilsMessengerCallbackDataEXT*      pCallbackData,
    void*                                            pUserData) {
    
    (void)messageTypes; (void)pUserData;
    string sev;
    
    if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
        sev = RSTR("WARNING");
    else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
        sev = RSTR("ERROR");
    else
        sev = RSTR("INFO");
    
    log(0, "\n-----------------VK VALIDATION MESSAGE-----------------");
    log(0, "Severity: %s", sev);
    if (pCallbackData->pMessageIdName)
        log(0, "- Message ID: %s", STR(pCallbackData->pMessageIdName));
    if (pCallbackData->pMessage)
        log(0, "- Message: %s", STR(pCallbackData->pMessage));
        
    return 0;
}

unit_local inline bool _vk_select_format(VkFormat *formats, u32 num_formats, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice vk_device, VkFormat *result) {
    for (u32 i = 0; i < num_formats; i += 1) {
        VkFormat format = formats[i];
        
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(vk_device, format, &props);
        
        if (tiling == VK_IMAGE_TILING_LINEAR && (features & props.linearTilingFeatures) == features) {
            *result = format;
            return true;
        }
        if (tiling == VK_IMAGE_TILING_OPTIMAL && (features & props.optimalTilingFeatures) == features) {
            *result = format;
            return true;
        }
    }
    
    return false;
}

unit_local inline VkInstance _vk_instance(void) {
    local_persist VkInstance instance = 0;
    
    if (!instance) {
        
        VkApplicationInfo app_info = (VkApplicationInfo){0};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = "Ostd App";
        app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.pEngineName = "Oga";
        app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.apiVersion = VK_API_VERSION_1_0;
    
        VkInstanceCreateInfo create_info = (VkInstanceCreateInfo){0};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &app_info;
        
#if OS_FLAGS & OS_FLAG_WINDOWS
        const char *required_extensions[] = {
            
#ifdef DEBUG
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif // _DEBUG
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_WIN32_SURFACE_EXTENSION_NAME
        };
#elif OS_FLAGS & OS_FLAG_LINUX
    // Depending on your display server, pick one:
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_XLIB_SURFACE_EXTENSION_NAME
    };
#elif OS_FLAGS & OS_FLAG_MACOS
    // MoltenVK-specific extension for macOS
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        "VK_MVK_macos_surface",
        "VK_KHR_portability_enumeration"
    };
    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#elif OS_FLAGS & OS_FLAG_IOS
    // MoltenVK-specific extension for iOS
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        "VK_MVK_ios_surface",
        "VK_KHR_portability_enumeration"
    };
    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#elif OS_FLAGS & OS_FLAG_ANDROID
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
    };

#else
    #error VK instance extension query not set up for this OS
#endif
        u64 num_required_extensions = sizeof(required_extensions) / sizeof(char*);
        
        log(0, "Looking for extensions:");
        for (u64 i = 0; i < num_required_extensions; i += 1) {
            log(0, "\t%s", STR(required_extensions[i]));
        }
        
        u32 num_available_extensions;
        _vk_assert(vkEnumerateInstanceExtensionProperties(0, &num_available_extensions, 0));
        VkExtensionProperties *available_extensions = NewBuffer(get_temp(), VkExtensionProperties, num_available_extensions);
        memset(available_extensions, 0, num_available_extensions*sizeof(VkExtensionProperties));
        _vk_assert(vkEnumerateInstanceExtensionProperties(0, &num_available_extensions, available_extensions));
        bool any_missing = false;
        for (u64 i = 0; i < num_required_extensions; i += 1) {
            const char *required = required_extensions[i];
            
            bool match = false;
            for (u64 j = 0; j < num_available_extensions; j += 1) {
                const char *available = available_extensions[j].extensionName;
                if (strings_match(STR(required), STR(available))) {
                    match = true;
                    break;
                }
            }
            
            if (match == false) {
                any_missing = true;
                log(0, "Missing required vulkan extension '%s'", STR(required));
            } else {
                log(0, "Found '%s'..", STR(required));
            }
        }
        
        assertmsg(!any_missing, "Basic vulkan extensions were missing, cannot proceed. Make sure you have a proper vulkan SDK installed.");
        
        create_info.ppEnabledExtensionNames = required_extensions;
        create_info.enabledExtensionCount = (u32)num_required_extensions;
        
#ifdef DEBUG
        const char *wanted_layers[] = {"VK_LAYER_KHRONOS_validation"};
        u32 num_wanted_layers = (u64)(sizeof(wanted_layers)/sizeof(char*));
        
        u32 num_available_layers;
        _vk_assert(vkEnumerateInstanceLayerProperties(&num_available_layers, 0));
        
        VkLayerProperties *available_layers = NewBuffer(get_temp(), VkLayerProperties, num_available_layers);
        _vk_assert(vkEnumerateInstanceLayerProperties(&num_available_layers, available_layers));
        
        const char *final_layers[32];
        u32 num_final_layers = 0;
        
        any_missing = false;
        for (u64 i = 0; i < num_wanted_layers; i += 1) {
            const char *wanted = wanted_layers[i];
            
            bool match = false;
            for (u64 j = 0; j < num_available_layers; j += 1) {
                const char *available = available_layers[j].layerName;
                if (strings_match(STR(wanted), STR(available))) {
                    match = true;
                    break;
                }
            }
            
            if (match == false) {
                any_missing = true;
                log(0, "Missing wanted vulkan debug layer '%s'", STR(wanted));
            } else {
                final_layers[num_final_layers++] = wanted;
                log(0, "Found validation layer %s", STR(wanted));
            }
        }
    
        create_info.enabledLayerCount = num_final_layers;
        create_info.ppEnabledLayerNames = final_layers;
#else
        create_info.enabledLayerCount = 0;
#endif
        
        _vk_assert(vkCreateInstance(&create_info, 0, &instance));
        
#if DEBUG
        VkDebugUtilsMessengerCreateInfoEXT debug_create_info = (VkDebugUtilsMessengerCreateInfoEXT){0};
        debug_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        
        debug_create_info.messageSeverity = 
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        
        debug_create_info.messageType = 
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | 
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            
        debug_create_info.pfnUserCallback = _vk_debug_callback;
        
        PFN_vkCreateDebugUtilsMessengerEXT _vkCreateDebugUtilsMessengerEXT  = (PFN_vkCreateDebugUtilsMessengerEXT)(void*)vkGetInstanceProcAddr(_vk_instance(), "vkCreateDebugUtilsMessengerEXT");
        
        if (_vkCreateDebugUtilsMessengerEXT(_vk_instance(), &debug_create_info, 0, &_vk_messenger) != VK_SUCCESS) {
            log(0, "Failed creating vulkan debug messenger");
        }
#endif // DEBUG
    }
    
    
    return instance;
}



unit_local VkResult vkCreateSurfaceKHR(Surface_Handle h, VkSurfaceKHR *result) {
#if OS_FLAGS & OS_FLAG_WINDOWS            
    VkWin32SurfaceCreateInfoKHR create_info = (VkWin32SurfaceCreateInfoKHR){0};
    create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    create_info.hwnd = (HWND)h;
    create_info.hinstance = GetModuleHandleW(0);
    return vkCreateWin32SurfaceKHR(_vk_instance(), &create_info, 0, result);
#elif OS_FLAGS & OS_FLAG_LINUX
    VkXlibSurfaceCreateInfoKHR create_info = (VkXlibSurfaceCreateInfoKHR){0};
    create_info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    create_info.window = (Window)h;
    create_info.dpy = ???;
    return vkCreateXlibSurfaceKHR(_vk_instance(), &create_info, 0, result);
#elif OS_FLAGS & OS_FLAG_MACOS
    VkMacOSSurfaceCreateInfoMVK create_info = (VkMacOSSurfaceCreateInfoMVK){0};
    create_info.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    create_info.pView = h;
    return vkCreateMacOSSurfaceMVK(_vk_instance(), &create_info, 0, result);
#elif OS_FLAGS & OS_FLAG_IOS
    VkIOSSurfaceCreateInfoMVK create_info = (VkIOSSurfaceCreateInfoMVK){0};
    create_info.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    create_info.pView = h;
    return vkCreateIOSSurfaceMVK(_vk_instance(), &create_info, 0, result);
#elif OS_FLAGS & OS_FLAG_ANDROID
    VkAndroidSurfaceCreateInfoKHR create_info = (VkAndroidSurfaceCreateInfoKHR){0};
    create_info.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    create_info.window = (ANativeWindow*)h;
    return vkCreateAndroidSurfaceKHR(_vk_instance(), &create_info, 0, result);
#else
    #error VK surface creation not implemented for this os
#endif
}

u64 oga_query_devices(Oga_Device *buffer, u64 buffer_count) {
    u32 device_count;
    _vk_assert(vkEnumeratePhysicalDevices(_vk_instance(), &device_count,  0));
    
    if (buffer) {
        memset(buffer, 0, buffer_count*sizeof(Oga_Device));
        VkPhysicalDevice vk_devices[256];
        _vk_assert(vkEnumeratePhysicalDevices(_vk_instance(), &device_count,  vk_devices));
        
        for (u32 i = 0; i < min(device_count, (u32)buffer_count); i += 1) {
            Oga_Device *device = buffer + i;
            VkPhysicalDevice vk_device = vk_devices[i];
        
        
            ////
            // Yoink info
            
            VkPhysicalDeviceProperties props;
            VkPhysicalDeviceMemoryProperties mem_props;
            VkPhysicalDeviceFeatures features;
        
            vkGetPhysicalDeviceProperties(vk_device, &props);
            vkGetPhysicalDeviceMemoryProperties(vk_device, &mem_props);
            vkGetPhysicalDeviceFeatures(vk_device, &features);
            
            u32 ext_count;
            vkEnumerateDeviceExtensionProperties(vk_device, 0, &ext_count, 0);
            VkExtensionProperties *ext_props = NewBuffer(get_temp(), VkExtensionProperties, ext_count);
            vkEnumerateDeviceExtensionProperties(vk_device, 0, &ext_count, ext_props);
            
            u32 logical_engine_family_count;
            vkGetPhysicalDeviceQueueFamilyProperties(vk_device, &logical_engine_family_count, 0);
            VkQueueFamilyProperties *logical_engine_family_props = NewBuffer(get_temp(), VkQueueFamilyProperties, logical_engine_family_count);
            vkGetPhysicalDeviceQueueFamilyProperties(vk_device, &logical_engine_family_count, logical_engine_family_props);
            
            
            /////
            // Copy over info into our API
            
            ///
            // Kind
            if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
                device->kind = OGA_DEVICE_INTEGRATED;
            else if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                device->kind = OGA_DEVICE_DISCRETE;
            else if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU)
                device->kind = OGA_DEVICE_CPU;
            ///
            // Stuff
            memcpy(device->device_name_data, props.deviceName, min(sizeof(device->device_name_data), sizeof(props.deviceName)));
            device->device_name_length = c_style_strlen((const char*)device->device_name_data);
            device->vendor_name = _str_vendor_id(props.vendorID);
            device->driver_version_raw = props.driverVersion;
            device->driver_version_length = _format_driver_version(props.vendorID, props.driverVersion, device->driver_version_data, sizeof(device->driver_version_data));
           
            
            ///
            // Logical Engine flags
            
            // note(charlie) annoyingly, we need an existing surface to look for
            // surface support in logical_engines. So, we just make a temporary invisible
            // surface and then delete it when done.
#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
            Surface_Desc desc = DEFAULT(Surface_Desc);
            desc.width = 1;
            desc.height = 1;
            desc.flags = SURFACE_FLAG_HIDDEN;
            Surface_Handle temp_sys_surface = sys_make_surface(desc);
#else
            Surface_Handle temp_sys_surface = sys_get_surface();
#endif
            
            VkSurfaceKHR temp_vk_surface;
            _vk_assert(vkCreateSurfaceKHR(temp_sys_surface, &temp_vk_surface));
            
            device->logical_engine_family_count = logical_engine_family_count;
            for (u32 j = 0; j < logical_engine_family_count; j += 1) {
                Oga_Logical_Engine_Family_Info *info = &device->logical_engine_family_infos[j];
                VkQueueFamilyProperties family_props = logical_engine_family_props[j];
            
                VkBool32 val;
                _vk_assert(vkGetPhysicalDeviceSurfaceSupportKHR(vk_device, j, temp_vk_surface, &val));
                if (val) info->flags |= OGA_LOGICAL_ENGINE_PRESENT;
                
                info->logical_engine_capacity = family_props.queueCount;
                
                if (family_props.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                    info->flags |= OGA_LOGICAL_ENGINE_GRAPHICS;
                if (family_props.queueFlags & VK_QUEUE_COMPUTE_BIT)
                    info->flags |= OGA_LOGICAL_ENGINE_COMPUTE;
                if (family_props.queueFlags & VK_QUEUE_TRANSFER_BIT)
                    info->flags |= OGA_LOGICAL_ENGINE_TRANSFER;
            }
            
            vkDestroySurfaceKHR(_vk_instance(), temp_vk_surface, 0);

#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
            surface_close(temp_sys_surface);
#endif

            ///
            // Depth format
        
            VkFormat depth_formats[] =  {
                VK_FORMAT_D32_SFLOAT,
                VK_FORMAT_D32_SFLOAT_S8_UINT,
                VK_FORMAT_D24_UNORM_S8_UINT,
                VK_FORMAT_D16_UNORM
            };
            
            VkFormat vk_depth_format;
            bool ok = _vk_select_format(depth_formats, sizeof(depth_formats)/sizeof(VkFormat), VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT, vk_device, &vk_depth_format);
            
            if (!ok) {
                log(0, ("WARNING: Could not find a supported depth format on this device."));
                vk_depth_format = VK_FORMAT_D32_SFLOAT;
            }
            
            device->depth_format = _vk_to_oga_format(vk_depth_format);
            
            /////
            // Memory heaps
            
            for (u32 j = 0; j < mem_props.memoryHeapCount; j += 1) {
                device->memory_heaps[j].size = (u64)mem_props.memoryHeaps[j].size;
            }
            device->memory_heap_count = mem_props.memoryHeapCount;
            
            for (u32 j = 0; j < mem_props.memoryTypeCount; j += 1) {
                VkMemoryType type = mem_props.memoryTypes[j];
                Oga_Memory_Heap *heap = &device->memory_heaps[type.heapIndex];
                
                
                
                if (type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
                    heap->properties |= OGA_MEMORY_PROPERTY_GPU_LOCAL;
                if (type.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
                    heap->properties |= OGA_MEMORY_PROPERTY_GPU_TO_CPU_MAPPABLE;
                if (type.propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
                    heap->properties |= OGA_MEMORY_PROPERTY_GPU_TO_CPU_REFLECTED;
                if (type.propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
                    heap->properties |= OGA_MEMORY_PROPERTY_GPU_TO_CPU_CACHED;
            }
            
            for (u32 j = 0; j < device->memory_heap_count; j += 1) {
                if (device->memory_heaps[j].properties & OGA_MEMORY_PROPERTY_GPU_LOCAL)
                    device->total_gpu_local_memory += device->memory_heaps[j].size;
            }
            
            
            if (props.limits.timestampComputeAndGraphics) {
                device->features |= (OGA_DEVICE_FEATURE_GRAPHICS_TIMESTAMP |
                                     OGA_DEVICE_FEATURE_COMPUTE_TIMESTAMP);
            }
            
            device->limits.max_shader_items_sets_per_stage = props.limits.maxPerStageResources;
            device->limits.max_fast_data_blocks_per_stage = props.limits.maxPerStageDescriptorUniformBuffers;
            device->limits.max_large_data_blocks_per_stage = props.limits.maxPerStageDescriptorStorageBuffers;
            device->limits.max_fast_images_per_stage = props.limits.maxPerStageDescriptorSampledImages;
            device->limits.max_large_images_per_stage = props.limits.maxPerStageDescriptorStorageImages;
            device->limits.max_samplers_per_stage = props.limits.maxPerStageDescriptorSamplers;
            device->limits.max_fast_data_blocks_per_layout = props.limits.maxDescriptorSetUniformBuffers;
            device->limits.max_large_data_blocks_per_layout = props.limits.maxDescriptorSetStorageBuffers;
            device->limits.max_fast_images_per_layout = props.limits.maxDescriptorSetSampledImages;
            device->limits.max_large_images_per_layout = props.limits.maxDescriptorSetStorageImages;
            device->limits.max_samplers_per_layout = props.limits.maxDescriptorSetSamplers;
            device->limits.max_memory_allocations = props.limits.maxMemoryAllocationCount;
            device->limits.max_sampler_allocations = props.limits.maxSamplerAllocationCount;
            device->limits.max_image_dimension_1d = props.limits.maxImageDimension1D;
            device->limits.max_image_dimension_2d = props.limits.maxImageDimension2D;
            device->limits.max_image_dimension_3d = props.limits.maxImageDimension3D;
            device->limits.max_fast_access_data_block_size = props.limits.maxUniformBufferRange;
            device->limits.max_vertex_layout_attributes = props.limits.maxVertexInputAttributes;
            device->limits.max_vertex_layout_bindings = props.limits.maxVertexInputBindings;
            device->limits.max_vertex_layout_attribute_offset = props.limits.maxVertexInputAttributeOffset;
            device->limits.max_vertex_layout_binding_stride = props.limits.maxVertexInputBindingStride;
            device->limits.max_fragment_stage_output_attachments = props.limits.maxFragmentOutputAttachments;
            device->limits.max_sampler_anisotropy = props.limits.maxSamplerAnisotropy;
            device->limits.max_viewports = props.limits.maxViewports;
            device->limits.max_viewport_width = props.limits.maxViewportDimensions[0];
            device->limits.max_viewport_height = props.limits.maxViewportDimensions[1];
            device->limits.max_framebuffer_width = props.limits.maxFramebufferWidth;
            device->limits.max_framebuffer_height = props.limits.maxFramebufferHeight;
            device->limits.max_color_attachments = props.limits.maxColorAttachments;
            device->limits.min_memory_map_alignment = props.limits.minMemoryMapAlignment;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.framebufferColorSampleCounts & f) device->limits.supported_sample_counts_framebuffer |= f;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.sampledImageColorSampleCounts & f) device->limits.supported_sample_counts_fast_image_float |= f;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.storageImageSampleCounts & f) device->limits.supported_sample_counts_large_image_float |= f;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.sampledImageIntegerSampleCounts & f) device->limits.supported_sample_counts_fast_image_int |= f;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.storageImageSampleCounts & f) device->limits.supported_sample_counts_large_image_int |= f;
            
            device->id = vk_device;
        }
    }
    
    return device_count;
}

Oga_Device *oga_get_devices(Allocator a, u64 *count) {
    *count = oga_query_devices(0, 0);
    
    Oga_Device *devices = NewBuffer(a, Oga_Device, *count);
    oga_query_devices(devices, *count);
    
    return devices;
}


Oga_Result oga_init_context(Oga_Device target_device, Oga_Context_Desc desc, Oga_Context *context) {
    
    const char *required_extensions[] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    
    if ((desc.enabled_features & target_device.features) != desc.enabled_features) {
        return OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES;
    }
    
    VkPhysicalDeviceFeatures enabled_features = (VkPhysicalDeviceFeatures){0};
    // if (desc.enabled_features & OGA_DEVICE_FEATURE_XXXX) enabled_features.xxxx = true;
    
    VkDeviceQueueCreateInfo logical_engine_infos[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES] = {0};
    
    u64 logical_engines_desc_count = 0;
    for (u64 family_index = 0; family_index < OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES; family_index += 1) {
        Oga_Logical_Engines_Create_Desc logical_engines_desc = desc.logical_engine_create_descs[family_index];
        if (logical_engines_desc.count > 0) {
            
            if (family_index >= target_device.logical_engine_family_count) {
                return OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE;
            }
            
            Oga_Logical_Engine_Family_Info family = target_device.logical_engine_family_infos[family_index];
            if (logical_engines_desc.count >= family.logical_engine_capacity) {
                return OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW;
            }
            
            VkDeviceQueueCreateInfo *info = &logical_engine_infos[logical_engines_desc_count];
            info->sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            info->queueFamilyIndex = (u32)family_index;
            info->queueCount = (u32)logical_engines_desc.count;
            info->pQueuePriorities = logical_engines_desc.priorities;
            
            logical_engines_desc_count += 1;
        }
    }
    
    
    VkDeviceCreateInfo info = (VkDeviceCreateInfo) {0};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    info.enabledExtensionCount = (u32)(sizeof(required_extensions)/sizeof(char*));
    info.ppEnabledExtensionNames = required_extensions;
    info.pEnabledFeatures = &enabled_features;
    info.queueCreateInfoCount = (u32)logical_engines_desc_count;
    info.pQueueCreateInfos = logical_engine_infos;
    
    *context = (Oga_Context){0};
    _vk_assert(vkCreateDevice(target_device.id, &info, 0, (VkDevice*)&context->id));
    context->device = target_device;
    
    for (u64 family_index = 0; family_index < OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES; family_index += 1) {
        Oga_Logical_Engines_Create_Desc logical_engines_desc = desc.logical_engine_create_descs[family_index];
        Oga_Logical_Engine_Group *group = &context->logical_engines_by_family[family_index];
        for (u64 logical_engine_index = 0; logical_engine_index < logical_engines_desc.count; logical_engine_index += 1) {
            Oga_Logical_Engine *logical_engine = &group->logical_engines[logical_engine_index];
            vkGetDeviceQueue(
                context->id, 
                (u32)family_index, 
                (u32)logical_engine_index, 
                (VkQueue*)&logical_engine->id
            );
            logical_engine->index = (u32)logical_engine_index;
        }
    }
    
    return OGA_OK;
}
void oga_uninit_context(Oga_Context *context) {
    vkDeviceWaitIdle(context->id);
    
    vkDestroyDevice(context->id, 0);
}
/* End include: graphics_vulkan.h */
#endif // (OS_FLAGS & (OS_FLAG_WINDOWS | OS_FLAG_LINUX | OS_FLAG_MACOS | OS_FLAG_IOS | OS_FLAG_ANDROID))

// OGA_IMPL_VULKAN
#elif defined(OGA_IMPL_WEBGPU)

/////////////////////////////////////////////////////
//////
// :WebGPU
//////
/////////////////////////////////////////////////////

#if !(OS_FLAGS & OS_FLAG_WEB)
    #error WebGPU can only be implemented when targetting web (Emscripten)
#else

/* Begin include: graphics_webgpu.h */


#error WebGPU graphics is not implemented
/* End include: graphics_webgpu.h */
#endif

// OGA_IMPL_WEBGPU
#elif defined(OGA_IMPL_D3D12)

/////////////////////////////////////////////////////
//////
// :D3D12
//////
/////////////////////////////////////////////////////

#if !(OS_FLAGS & OS_FLAG_WINDOWS)
    #error D3D12 can only be implemented when targetting Windows
#else

/* Begin include: graphics_d3d12.h */


#error D3D12 graphics is not implemented
/* End include: graphics_d3d12.h */
#endif

//OGA_IMPL_D3D12
#elif defined(OGA_IMPL_METAL)

/////////////////////////////////////////////////////
//////
// :Metal
//////
/////////////////////////////////////////////////////

#if !(OS_FLAGS & OS_FLAG_APPLE)
    #error Metal can only be implemented when targetting Apple
#else

/* Begin include: graphics_metal.h */


#error Metal graphics is not implemented
/* End include: graphics_metal.h */
#endif

//OGA_IMPL_METAL
#else

/////////////////////////////////////////////////////
//////
// :Software
//////
/////////////////////////////////////////////////////

#endif

#endif // OSTD_IMPL


/* End include: graphics.h */

#ifdef OSTD_NO_IGNORE_WARNINGS
#pragma clang diagnostic pop
#endif // OSTD_NO_IGNORE_WARNINGS

#endif // OSTD_H_