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
#ifndef _ONE_OGA_GRAPHICS_H
#define _ONE_OGA_GRAPHICS_H

#if !defined(OGA_GRAPHICS) && !defined(OSTD_HEADLESS)
#define OGA_GRAPHICS


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

#endif // _STRING_H

/* End include: string.h */
#endif // _STRING_H
#ifndef _MEMORY_H

/* Begin include: memory.h */
#ifndef _MEMORY_H
#define _MEMORY_H

#ifndef _BASE_H
#endif // _BASE_H

#ifndef _STRING_H
#endif //_STRING_H

#ifndef _SYSTEM_1_H

/* Begin include: system1.h */
#ifndef _SYSTEM_1_H
#define _SYSTEM_1_H

#ifndef _BASE_H
#endif // _BASE_H
#ifndef _STRING_H
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

File_Handle sys_get_stdout(void);
File_Handle sys_get_stderr(void);

void sys_set_stdout(File_Handle h);
void sys_set_stderr(File_Handle h);

s64 sys_write(File_Handle h, void *data, u64 size);
s64 sys_write_string(File_Handle h, string s);

s64 sys_read(File_Handle h, void *buffer, u64 buffer_size);

bool sys_make_pipe(File_Handle *read, File_Handle *write);

void sys_close(File_Handle h);

// Returns 0 on failure
File_Handle sys_open_file(string path, File_Open_Flags flags);
u64 sys_get_file_size(File_Handle f);

bool sys_make_directory(string path, bool recursive);
bool sys_remove_directory(string path, bool recursive);
bool sys_is_file(string path);
bool sys_is_directory(string path);

typedef bool (*Walk_Proc)(string); // Return true to continue, false to break
void sys_walk_directory(string path, bool recursive, bool walk_directories, Walk_Proc walk_proc);

typedef struct Easy_Command_Result {
    s64 exit_code;
    bool process_start_success;
} Easy_Command_Result;
Easy_Command_Result sys_run_command_easy(string command_line, File_Handle stdout, File_Handle stderr, string workspace_dir);

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

u32 sys_convert_address_string(string address);

Socket_Result sys_socket_init(Socket *socket, Socket_Domain domain, Socket_Type type, Socket_Protocol protocol);
Socket_Result sys_socket_bind(Socket socket, u32 address, u16 port);
Socket_Result sys_socket_listen(Socket socket, s64 backlog);
Socket_Result sys_socket_accept(Socket socket, Socket *accepted, u64 timeout_ms);
Socket_Result sys_socket_connect(Socket sock, u32 address, u16 port, Socket_Domain domain);
Socket_Result sys_socket_send(Socket socket, void *data, u64 length, u64 *sent);
Socket_Result sys_socket_recv(Socket socket, void *buffer, u64 length, u64 *sent);
Socket_Result sys_socket_close(Socket socket);
Socket_Result sys_socket_set_blocking(Socket *socket, bool blocking);
Socket_Result sys_set_socket_blocking_timeout(Socket socket, u64 ms);


//////
// Thread Primitives
//////

typedef void* Thread_Key;

u64 sys_get_current_thread_id(void);

bool sys_thread_key_init(Thread_Key *key);
bool sys_thread_key_write(Thread_Key key, void* value);
void* sys_thread_key_read(Thread_Key key);

struct Thread;
typedef s64 (*Thread_Proc)(struct Thread*);
typedef struct Thread {
    void *handle;
    u64 id;
    void *userdata;
    Thread_Proc proc;
    bool is_suspended;
} Thread;

bool sys_thread_init(Thread *thread, Thread_Proc proc, void *userdata);
void sys_thread_start(Thread *thread);
void sys_thread_join(Thread *thread);
void sys_thread_close(Thread *thread);

typedef struct Mutex {
    void *handle;
    u8 handle_backing[40]; // This is for windows critical section;
} Mutex;

bool sys_mutex_init(Mutex *mutex);
bool sys_mutex_uninit(Mutex *mutex);
void sys_mutex_acquire(Mutex mutex);
void sys_mutex_release(Mutex mutex);

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

bool surface_get_framebuffer_size(Surface_Handle h, s64 *width, s64 *height);

void* surface_map_pixels(Surface_Handle h);
void surface_blit_pixels(Surface_Handle h);

bool surface_get_monitor(Surface_Handle h, Physical_Monitor *monitor);

#endif // !OSTD_HEADLESS

//////
// Time
//////

float64 sys_get_seconds_monotonic(void);

//////
// Process & Thread
//////

typedef void* Thread_Handle;

Thread_Handle sys_get_current_thread(void);
void sys_set_thread_affinity_mask(Thread_Handle thread, u64 bits);

typedef enum Priority_Level {
    SYS_PRIORITY_LOW,
    SYS_PRIORITY_MEDIUM,
    SYS_PRIORITY_HIGH,
} Priority_Level;

void sys_set_local_process_priority_level(Priority_Level level);
void sys_set_thread_priority_level(Thread_Handle thread, Priority_Level level);

void *sys_load_library(string s);
void sys_close_library(void *lib);
void* sys_get_library_symbol(void *lib, string symbol);

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
    
    return 0;
}

unit_local void _ostd_register_thread_storage(u64 thread_id) {

    if (_ostd_thread_storage) {
        sys_mutex_acquire(_ostd_thread_storage_register_mutex);
    }

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
        sys_mutex_init(&_ostd_thread_storage_register_mutex);
        _ostd_thread_storage = sys_map_pages(SYS_MEMORY_RESERVE, 0, 1024*1024*10, false);
        assert(_ostd_thread_storage);
        void *allocated = sys_map_pages(SYS_MEMORY_ALLOCATE, _ostd_thread_storage, 1, false);
        assert(allocated == _ostd_thread_storage);
        memset(allocated, 0, page_size);
        _ostd_thread_storage_allocated_count = page_size/sizeof(_Ostd_Thread_Storage);
    } else {
        void *next_alloc = (void*)(uintptr)align_next((u64)(_ostd_thread_storage+_ostd_thread_storage_allocated_count), page_size);
        void *allocated = sys_map_pages(SYS_MEMORY_ALLOCATE, next_alloc, 1, false);
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


/* End include: windows_loader.h */
    #endif // _WINDOWS_
    
#endif// OS_FLAGS & OS_FLAG_WINDOWS

#ifndef OSTD_HEADLESS

#if OS_FLAGS & OS_FLAG_LINUX
    #if COMPILER_FLAGS & COMPILER_FLAG_GNU
        #define _GNU_SOURCE
    #endif
    
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/extensions/Xrandr.h>
    // For waiting for vblank. Unfortunately.
    #include <GL/gl.h>
    #include <GL/glx.h>
    struct _XDisplay;
    typedef struct _XDisplay Display;
    struct wl_display;
    typedef struct wl_display wl_display;
#endif // OS_FLAGS & OS_FLAG_LINUX



typedef struct _Surface_State {
    Surface_Handle handle;
#if OS_FLAGS & OS_FLAG_WINDOWS
    BITMAPINFO bmp_info;
    HBITMAP bmp;
#elif OS_FLAGS & OS_FLAG_LINUX
    GC       gc;
    XImage*  ximage;
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
#define _POSIX_C_SOURCE

// todo(charlie) dynamically link & manually  define some stuff to minimize namespace bloat here
#include <unistd.h>
#include <sched.h>
#include <pthread.h>
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

#if (OS_FLAGS & OS_FLAG_LINUX)
#include <execinfo.h>
#endif

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
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))
    
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

double sys_get_seconds_monotonic(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
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
    #pragma comment(lib, "dbghelp")
    #pragma comment(lib, "pdh")
    #pragma comment(lib, "winmm")
    #pragma comment(lib, "ws2_32.lib")
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
    int result = WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)s, -1, (char*)utf8->data, (int)len+1, 0, 0);
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
    
    u16 path_wide[2048];
    u64 path_len = _win_utf8_to_wide(path, path_wide, 2048);
    
    u16 search_pattern[2048];
    u64 pos = 0;
    for (u64 i = 0; i < path_len; i++) {
        search_pattern[pos++] = path_wide[i];
    }
    if (!has_slash) {
        search_pattern[pos++] = '\\';
    }
    search_pattern[pos++] = '*';
    
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
        
        u8 new_path[2048];
        
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

Easy_Command_Result sys_run_command_easy(string command_line, File_Handle stdout, File_Handle stderr, string workspace_dir) {
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
    
    WaitForSingleObject(pi.hProcess, S32_MAX);
    
    DWORD exit_code;
    GetExitCodeProcess(pi.hProcess, &exit_code);
    
    res.exit_code = (s64)exit_code;
    res.process_start_success = true;
    
    return res;
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
void sys_thread_start(Thread *thread) {
    thread->is_suspended = false;
    ResumeThread(thread->handle);
}
void sys_thread_join(Thread *thread) {
    assert(!thread->is_suspended);
    WaitForSingleObject(thread->handle, 0xFFFFFFFF);
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
	return (float64)counter.QuadPart / (float64)freq.QuadPart;
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

#endif // OSTD_IMPL






#endif // _SYSTEM_1_H

/* End include: system1.h */
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

Arena make_arena(u64 reserved_size, u64 initial_allocated_size);
void *arena_push(Arena *arena, u64 size);
void *arena_push_copy(Arena *arena, void *src, u64 size);
void arena_pop(Arena *arena, u64 size);
void arena_reset(Arena *arena);
void free_arena(Arena arena);

void* arena_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags);
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
    return a.proc(ALLOCATOR_ALLOCATE, a.data, 0, 0, n, 0, 0);
}
inline void *reallocate(Allocator a, void *p, u64 old_n, u64 n) {
    return a.proc(ALLOCATOR_REALLOCATE, a.data, p, old_n, n, 0, 0);
}
inline void deallocate(Allocator a, void *p) {
    a.proc(ALLOCATOR_FREE, a.data, p, 0, 0, 0, 0);
}

inline void *allocatef(Allocator a, u64 n, u64 flags) {
    return a.proc(ALLOCATOR_ALLOCATE, a.data, 0, 0, n, flags, 0);
}
inline void *reallocatef(Allocator a, void *p, u64 old_n, u64 n, u64 flags) {
    return a.proc(ALLOCATOR_REALLOCATE, a.data, p, old_n, n, flags, 0);
}
inline void deallocatef(Allocator a, void *p, u64 flags) {
    a.proc(ALLOCATOR_FREE, a.data, p, 0, 0, flags, 0);
}

inline string string_allocate(Allocator a, u64 n) {
    return (string) {n, (u8*)allocate(a, n)};
}
inline void string_deallocate(Allocator a, string s) {
    deallocate(a, s.data);
}

inline string string_copy(Allocator a, string s) {
    string new_s = string_allocate(a, s.count);
    memcpy(new_s.data, s.data, (sys_uint)s.count);
    return new_s;
}

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
    s->temp->arena = make_arena(sys_get_info().page_size*6900, 1024);
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
        void *allocate_result = sys_map_pages(SYS_MEMORY_ALLOCATE, arena.start, initial_allocated_size/info.page_size, true);
        assert(allocate_result == arena.start);
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
    memcpy(dst, src, (sys_uint)size);
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
            return arena_push(a, n);
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

#endif // OSTD_IMPL

#endif // _MEMORY_H

/* End include: memory.h */
#endif // _MEMORY_H
#ifndef _SYSTEM_1_H
#endif // _SYSTEM_1_H
#ifndef _MATH_H

/* Begin include: math.h */
#ifndef _MATH_H
#define _MATH_H

#ifndef _BASE_H
#endif // _BASE_H


/* Begin include: trig_tables.h */
#ifndef _TRIG_TABLES_H
#define _TRIG_TABLES_H

#ifndef _BASE_H
#endif // _BASE_H

unit_local const float64 sine_table[360] = {
    0,    0.017452406437283512,    0.034899496702500969,    0.052335956242943828,    0.069756473744125302,    0.087155742747658166,    0.10452846326765346,    0.12186934340514748,
    0.13917310096006544,    0.15643446504023087,    0.17364817766693033,    0.1908089953765448,    0.20791169081775931,    0.22495105434386498,    0.24192189559966773,    0.25881904510252074,
    0.27563735581699916,    0.29237170472273671,    0.3090169943749474,    0.3255681544571567,    0.34202014332566871,    0.35836794954530027,    0.37460659341591201,    0.39073112848927372,
    0.40673664307580015,    0.42261826174069944,    0.4383711467890774,    0.45399049973954675,    0.46947156278589081,    0.48480962024633706,    0.49999999999999994,    0.51503807491005416,
    0.5299192642332049,    0.54463903501502697,    0.55919290347074679,    0.57357643635104605,    0.58778525229247314,    0.60181502315204827,    0.61566147532565829,    0.6293203910498375,
    0.64278760968653925,    0.65605902899050728,    0.66913060635885824,    0.68199836006249848,    0.69465837045899725,    0.70710678118654757,    0.71933980033865108,    0.73135370161917046,
    0.74314482547739413,    0.7547095802227719,    0.76604444311897801,    0.77714596145697079,    0.7880107536067219,    0.79863551004729283,    0.80901699437494745,    0.8191520442889918,
    0.82903757255504174,    0.83867056794542394,    0.84804809615642607,    0.85716730070211222,    0.8660254037844386,    0.87461970713939574,    0.88294759285892688,    0.89100652418836779,
    0.89879404629916704,    0.90630778703664994,    0.91354545764260087,    0.92050485345244037,    0.92718385456678731,    0.93358042649720174,    0.93969262078590832,    0.94551857559931674,
    0.95105651629515353,    0.95630475596303544,    0.96126169593831889,    0.96592582628906831,    0.97029572627599647,    0.97437006478523525,    0.97814760073380569,    0.98162718344766398,
    0.98480775301220802,    0.98768834059513777,    0.99026806874157036,    0.99254615164132198,    0.99452189536827329,    0.99619469809174555,    0.9975640502598242,    0.99862953475457383,
    0.99939082701909576,    0.99984769515639127,    1,    0.99984769515639127,    0.99939082701909576,    0.99862953475457383,    0.9975640502598242,    0.99619469809174555,
    0.9945218953682734,    0.99254615164132209,    0.99026806874157036,    0.98768834059513766,    0.98480775301220802,    0.98162718344766398,    0.97814760073380569,    0.97437006478523525,
    0.97029572627599647,    0.96592582628906831,    0.96126169593831889,    0.95630475596303555,    0.95105651629515364,    0.94551857559931685,    0.93969262078590843,    0.93358042649720174,
    0.92718385456678742,    0.92050485345244037,    0.91354545764260098,    0.90630778703665005,    0.89879404629916693,    0.8910065241883679,    0.8829475928589271,    0.87461970713939585,
    0.86602540378443871,    0.85716730070211233,    0.84804809615642607,    0.83867056794542405,    0.82903757255504174,    0.81915204428899202,    0.80901699437494745,    0.79863551004729272,
    0.78801075360672201,    0.77714596145697101,    0.76604444311897801,    0.75470958022277213,    0.74314482547739447,    0.73135370161917057,    0.71933980033865108,    0.70710678118654757,
    0.69465837045899748,    0.68199836006249848,    0.66913060635885802,    0.65605902899050728,    0.64278760968653947,    0.62932039104983739,    0.6156614753256584,    0.6018150231520486,
    0.58778525229247325,    0.57357643635104594,    0.5591929034707469,    0.54463903501502731,    0.5299192642332049,    0.51503807491005438,    0.49999999999999994,    0.48480962024633717,
    0.46947156278589069,    0.45399049973954686,    0.43837114678907768,    0.4226182617406995,    0.40673664307580004,    0.39073112848927377,    0.37460659341591224,    0.35836794954530066,
    0.34202014332566888,    0.32556815445715659,    0.30901699437494751,    0.29237170472273705,    0.27563735581699922,    0.25881904510252102,    0.24192189559966773,    0.2249510543438652,
    0.20791169081775931,    0.19080899537654497,    0.17364817766693069,    0.15643446504023098,    0.13917310096006533,    0.12186934340514755,    0.10452846326765373,    0.087155742747658194,
    0.069756473744125524,    0.052335956242944251,    0.034899496702501143,    0.017452406437283439,    1.2246467991473532e-16,    -0.017452406437283192,    -0.0348994967025009,    -0.052335956242943564,
    -0.069756473744124831,    -0.087155742747657944,    -0.1045284632676535,    -0.12186934340514774,    -0.13917310096006552,    -0.15643446504023073,    -0.17364817766693047,    -0.19080899537654472,
    -0.20791169081775907,    -0.22495105434386498,    -0.24192189559966751,    -0.25881904510252035,    -0.27563735581699861,    -0.29237170472273677,    -0.30901699437494773,    -0.32556815445715676,
    -0.34202014332566866,    -0.35836794954530043,    -0.37460659341591201,    -0.39073112848927355,    -0.40673664307579982,    -0.42261826174069927,    -0.43837114678907707,    -0.45399049973954625,
    -0.46947156278589047,    -0.48480962024633734,    -0.50000000000000011,    -0.51503807491005416,    -0.52991926423320479,    -0.54463903501502708,    -0.55919290347074668,    -0.57357643635104583,
    -0.58778525229247303,    -0.60181502315204805,    -0.61566147532565785,    -0.62932039104983728,    -0.64278760968653925,    -0.65605902899050739,    -0.66913060635885824,    -0.68199836006249837,
    -0.69465837045899725,    -0.70710678118654746,    -0.71933980033865086,    -0.73135370161917046,    -0.74314482547739402,    -0.75470958022277168,    -0.7660444431189779,    -0.77714596145697112,
    -0.78801075360672213,    -0.79863551004729283,    -0.80901699437494734,    -0.81915204428899158,    -0.8290375725550414,    -0.83867056794542416,    -0.84804809615642596,    -0.85716730070211211,
    -0.86602540378443849,    -0.87461970713939552,    -0.88294759285892699,    -0.89100652418836779,    -0.89879404629916682,    -0.90630778703665016,    -0.91354545764260098,    -0.92050485345244026,
    -0.92718385456678731,    -0.93358042649720163,    -0.93969262078590821,    -0.94551857559931685,    -0.95105651629515353,    -0.95630475596303532,    -0.96126169593831901,    -0.96592582628906831,
    -0.97029572627599647,    -0.97437006478523513,    -0.97814760073380558,    -0.98162718344766398,    -0.98480775301220802,    -0.98768834059513766,    -0.99026806874157025,    -0.99254615164132198,
    -0.99452189536827329,    -0.99619469809174555,    -0.9975640502598242,    -0.99862953475457394,    -0.99939082701909576,    -0.99984769515639127,    -1,    -0.99984769515639127,
    -0.99939082701909576,    -0.99862953475457394,    -0.99756405025982431,    -0.99619469809174555,    -0.99452189536827329,    -0.99254615164132198,    -0.99026806874157036,    -0.98768834059513777,
    -0.98480775301220813,    -0.98162718344766409,    -0.97814760073380558,    -0.97437006478523525,    -0.97029572627599658,    -0.96592582628906842,    -0.96126169593831901,    -0.95630475596303544,
    -0.95105651629515364,    -0.94551857559931696,    -0.93969262078590832,    -0.93358042649720174,    -0.92718385456678742,    -0.92050485345244049,    -0.91354545764260109,    -0.90630778703665027,
    -0.89879404629916704,    -0.89100652418836801,    -0.8829475928589271,    -0.87461970713939563,    -0.8660254037844386,    -0.85716730070211233,    -0.84804809615642607,    -0.83867056794542427,
    -0.82903757255504162,    -0.8191520442889918,    -0.80901699437494756,    -0.79863551004729305,    -0.78801075360672235,    -0.77714596145697135,    -0.76604444311897812,    -0.75470958022277224,
    -0.74314482547739402,    -0.73135370161917035,    -0.71933980033865108,    -0.70710678118654768,    -0.69465837045899759,    -0.68199836006249892,    -0.66913060635885879,    -0.65605902899050739,
    -0.64278760968653958,    -0.62932039104983717,    -0.61566147532565818,    -0.60181502315204827,    -0.58778525229247336,    -0.57357643635104649,    -0.55919290347074735,    -0.54463903501502697,
    -0.52991926423320501,    -0.51503807491005449,    -0.50000000000000044,    -0.48480962024633767,    -0.46947156278589081,    -0.45399049973954697,    -0.43837114678907779,    -0.42261826174069922,
    -0.40673664307580015,    -0.39073112848927388,    -0.37460659341591235,    -0.35836794954530077,    -0.34202014332566943,    -0.3255681544571567,    -0.30901699437494767,    -0.29237170472273716,
    -0.27563735581699894,    -0.25881904510252068,    -0.24192189559966787,    -0.22495105434386534,    -0.20791169081775987,    -0.19080899537654467,    -0.17364817766693039,    -0.15643446504023109,
    -0.13917310096006588,    -0.12186934340514811,    -0.1045284632676543,    -0.087155742747658319,    -0.069756473744125636,    -0.052335956242943481,    -0.034899496702500823,    -0.01745240643728356
};

unit_local const float64 cosine_table[360] = {
    1,    0.99984769515639127,    0.99939082701909576,    0.99862953475457383,    0.9975640502598242,    0.99619469809174555,    0.99452189536827329,    0.99254615164132198,
    0.99026806874157036,    0.98768834059513777,    0.98480775301220802,    0.98162718344766398,    0.97814760073380569,    0.97437006478523525,    0.97029572627599647,    0.96592582628906831,
    0.96126169593831889,    0.95630475596303555,    0.95105651629515353,    0.94551857559931685,    0.93969262078590843,    0.93358042649720174,    0.92718385456678742,    0.92050485345244037,
    0.91354545764260087,    0.90630778703664994,    0.89879404629916704,    0.8910065241883679,    0.88294759285892699,    0.87461970713939574,    0.86602540378443871,    0.85716730070211233,
    0.84804809615642596,    0.83867056794542405,    0.82903757255504174,    0.8191520442889918,    0.80901699437494745,    0.79863551004729283,    0.7880107536067219,    0.77714596145697079,
    0.76604444311897801,    0.75470958022277201,    0.74314482547739424,    0.73135370161917046,    0.71933980033865119,    0.70710678118654757,    0.69465837045899737,    0.68199836006249848,
    0.66913060635885824,    0.65605902899050739,    0.64278760968653936,    0.6293203910498375,    0.61566147532565829,    0.60181502315204838,    0.58778525229247314,    0.57357643635104605,
    0.55919290347074679,    0.5446390350150272,    0.5299192642332049,    0.51503807491005427,    0.50000000000000011,    0.48480962024633711,    0.46947156278589086,    0.4539904997395468,
    0.43837114678907746,    0.42261826174069944,    0.40673664307580037,    0.39073112848927372,    0.37460659341591218,    0.35836794954530016,    0.34202014332566882,    0.32556815445715676,
    0.30901699437494745,    0.29237170472273677,    0.27563735581699916,    0.25881904510252074,    0.24192189559966767,    0.22495105434386514,    0.20791169081775923,    0.19080899537654492,
    0.17364817766693041,    0.15643446504023092,    0.13917310096006547,    0.12186934340514749,    0.10452846326765346,    0.08715574274765836,    0.069756473744125233,    0.052335956242943966,
    0.03489949670250108,    0.017452406437283598,    6.123233995736766e-17,    -0.017452406437283477,    -0.034899496702500733,    -0.052335956242943842,    -0.06975647374412533,    -0.087155742747658235,
    -0.10452846326765333,    -0.12186934340514737,    -0.13917310096006513,    -0.15643446504023104,    -0.1736481776669303,    -0.1908089953765448,    -0.20791169081775912,    -0.22495105434386481,
    -0.24192189559966756,    -0.25881904510252085,    -0.27563735581699905,    -0.29237170472273666,    -0.30901699437494734,    -0.32556815445715642,    -0.34202014332566871,    -0.35836794954530027,
    -0.37460659341591207,    -0.3907311284892736,    -0.4067366430758001,    -0.42261826174069933,    -0.43837114678907751,    -0.45399049973954675,    -0.46947156278589053,    -0.484809620246337,
    -0.49999999999999978,    -0.51503807491005427,    -0.52991926423320479,    -0.54463903501502708,    -0.55919290347074668,    -0.57357643635104583,    -0.58778525229247303,    -0.60181502315204838,
    -0.61566147532565829,    -0.62932039104983728,    -0.64278760968653936,    -0.65605902899050716,    -0.6691306063588579,    -0.68199836006249837,    -0.69465837045899737,    -0.70710678118654746,
    -0.71933980033865097,    -0.73135370161917046,    -0.74314482547739436,    -0.75470958022277201,    -0.7660444431189779,    -0.7771459614569709,    -0.7880107536067219,    -0.79863551004729261,
    -0.80901699437494734,    -0.81915204428899191,    -0.82903757255504162,    -0.83867056794542394,    -0.84804809615642596,    -0.85716730070211222,    -0.86602540378443871,    -0.87461970713939574,
    -0.88294759285892699,    -0.89100652418836779,    -0.89879404629916682,    -0.90630778703664994,    -0.91354545764260098,    -0.92050485345244037,    -0.92718385456678731,    -0.93358042649720163,
    -0.93969262078590832,    -0.94551857559931685,    -0.95105651629515353,    -0.95630475596303544,    -0.96126169593831889,    -0.9659258262890682,    -0.97029572627599647,    -0.97437006478523513,
    -0.97814760073380569,    -0.98162718344766398,    -0.98480775301220802,    -0.98768834059513766,    -0.99026806874157036,    -0.99254615164132198,    -0.99452189536827329,    -0.99619469809174555,
    -0.9975640502598242,    -0.99862953475457383,    -0.99939082701909576,    -0.99984769515639127,    -1,    -0.99984769515639127,    -0.99939082701909576,    -0.99862953475457383,
    -0.99756405025982431,    -0.99619469809174555,    -0.99452189536827329,    -0.99254615164132198,    -0.99026806874157025,    -0.98768834059513777,    -0.98480775301220802,    -0.98162718344766398,
    -0.97814760073380569,    -0.97437006478523525,    -0.97029572627599647,    -0.96592582628906842,    -0.96126169593831901,    -0.95630475596303544,    -0.95105651629515353,    -0.94551857559931674,
    -0.93969262078590843,    -0.93358042649720174,    -0.92718385456678742,    -0.92050485345244037,    -0.91354545764260109,    -0.90630778703665005,    -0.89879404629916715,    -0.89100652418836812,
    -0.8829475928589271,    -0.87461970713939563,    -0.8660254037844386,    -0.85716730070211233,    -0.84804809615642607,    -0.83867056794542405,    -0.82903757255504174,    -0.81915204428899202,
    -0.80901699437494745,    -0.79863551004729305,    -0.78801075360672224,    -0.77714596145697112,    -0.76604444311897801,    -0.7547095802227719,    -0.74314482547739424,    -0.73135370161917057,
    -0.71933980033865108,    -0.70710678118654768,    -0.69465837045899748,    -0.68199836006249859,    -0.66913060635885846,    -0.65605902899050772,    -0.64278760968653947,    -0.62932039104983706,
    -0.61566147532565807,    -0.60181502315204827,    -0.58778525229247325,    -0.57357643635104638,    -0.55919290347074724,    -0.54463903501502697,    -0.52991926423320501,    -0.51503807491005438,
    -0.50000000000000044,    -0.48480962024633761,    -0.46947156278589075,    -0.45399049973954692,    -0.43837114678907774,    -0.42261826174069916,    -0.4067366430758001,    -0.39073112848927383,
    -0.37460659341591229,    -0.35836794954530071,    -0.34202014332566938,    -0.32556815445715664,    -0.30901699437494756,    -0.2923717047227371,    -0.27563735581699889,    -0.25881904510252063,
    -0.24192189559966779,    -0.22495105434386525,    -0.20791169081775979,    -0.19080899537654461,    -0.17364817766693033,    -0.15643446504023104,    -0.13917310096006583,    -0.12186934340514805,
    -0.10452846326765423,    -0.087155742747658249,    -0.06975647374412558,    -0.052335956242943425,    -0.034899496702500761,    -0.017452406437283498,    -1.8369701987210297e-16,    0.01745240643728313,
    0.034899496702500393,    0.052335956242943057,    0.069756473744125219,    0.087155742747657888,    0.10452846326765387,    0.12186934340514768,    0.13917310096006547,    0.15643446504023067,
    0.17364817766692997,    0.19080899537654425,    0.20791169081775943,    0.22495105434386492,    0.24192189559966742,    0.2588190451025203,    0.2756373558169985,    0.29237170472273671,
    0.30901699437494723,    0.32556815445715631,    0.34202014332566899,    0.35836794954530038,    0.37460659341591196,    0.39073112848927349,    0.40673664307579976,    0.42261826174069883,
    0.4383711467890774,    0.45399049973954664,    0.46947156278589042,    0.48480962024633728,    0.50000000000000011,    0.51503807491005416,    0.52991926423320468,    0.54463903501502664,
    0.55919290347074702,    0.57357643635104605,    0.58778525229247292,    0.60181502315204793,    0.61566147532565785,    0.62932039104983684,    0.64278760968653925,    0.65605902899050705,
    0.66913060635885846,    0.68199836006249859,    0.69465837045899725,    0.70710678118654735,    0.71933980033865086,    0.73135370161917013,    0.74314482547739369,    0.7547095802227719,
    0.76604444311897779,    0.77714596145697112,    0.78801075360672201,    0.79863551004729283,    0.80901699437494734,    0.81915204428899158,    0.8290375725550414,    0.83867056794542405,
    0.84804809615642585,    0.85716730070211211,    0.86602540378443837,    0.87461970713939541,    0.88294759285892699,    0.89100652418836779,    0.89879404629916682,    0.90630778703665005,
    0.91354545764260098,    0.92050485345244026,    0.92718385456678731,    0.93358042649720152,    0.93969262078590809,    0.94551857559931685,    0.95105651629515353,    0.95630475596303532,
    0.96126169593831889,    0.96592582628906831,    0.97029572627599647,    0.97437006478523513,    0.97814760073380558,    0.98162718344766398,    0.98480775301220802,    0.98768834059513766,
    0.99026806874157025,    0.99254615164132198,    0.99452189536827329,    0.99619469809174555,    0.9975640502598242,    0.99862953475457394,    0.99939082701909576,    0.99984769515639127
};

unit_local const float64 tan_table[360] = {
    0,    0.0087268677907587893,    0.017455064928217585,    0.026185921569186928,    0.03492076949174773,    0.043660942908512058,    0.052407779283041196,    0.061162620150484306,
    0.069926811943510414,    0.078701706824618439,    0.087488663525924007,    0.096289048197538613,    0.10510423526567646,    0.11393560830164548,    0.1227845609029046,    0.13165249758739583,
    0.14054083470239145,    0.14945100134912778,    0.15838444032453627,    0.16734260908141957,    0.17632698070846498,    0.18533904493153439,    0.19438030913771848,    0.20345229942369933,
    0.2125565616700221,    0.22169466264293988,    0.23086819112556309,    0.24007875908011603,    0.24932800284318068,    0.25861758435589027,    0.2679491924311227,    0.27732454405983847,
    0.28674538575880792,    0.29621349496208021,    0.30573068145866034,    0.31529878887898349,    0.32491969623290629,    0.33459531950207316,    0.34432761328966527,    0.35411857253069806,
    0.36397023426620234,    0.37388467948480469,    0.38386403503541577,    0.39391047561494241,    0.40402622583515679,    0.41421356237309503,    0.4244748162096047,    0.43481237496093361,
    0.4452286853085361,    0.45572625553258461,    0.46630765815499858,    0.47697553269816012,    0.48773258856586138,    0.49858160805343144,    0.50952544949442879,    0.52056705055174624,
    0.53170943166147877,    0.54295569963843682,    0.55430905145276899,    0.56577277818776994,    0.57735026918962573,    0.58904501642055096,    0.60086061902756038,    0.612800788139932,
    0.62486935190932746,    0.63707026080749318,    0.6494075931975104,    0.66188556119569153,    0.67450851684242652,    0.68728095860161331,    0.70020753820970971,    0.71329306789700531,
    0.72654252800536079,    0.73996107502848762,    0.75355405010279419,    0.76732698797896037,    0.7812856265067174,    0.79543591666782831,    0.80978403319500725,    0.82433638581749569,
    0.83909963117727993,    0.8540806854634666,    0.86928673781622656,    0.8847252645559438,    0.90040404429783993,    0.91633117401742326,    0.93251508613766176,    0.94896456671487961,
    0.96568877480707394,    0.98269726311568995,    0,    1.0176073929721252,    1.0355303137905694,    1.0537801252809622,    1.0723687100246826,    1.0913085010692716,
    1.1106125148291928,    1.1302943863617529,    1.1503684072210092,    1.1708495661125393,    1.19175359259421,    1.2130970040929328,    1.2348971565350511,    1.2571722989189544,
    1.2799416321930785,    1.3032253728412058,    1.3270448216204098,    1.3514224379458082,    1.3763819204711734,    1.4019482944763355,    1.4281480067421144,    1.4550090286724449,
    1.4825609685127403,    1.5108351936149007,    1.5398649638145827,    1.5696855771174902,    1.6003345290410507,    1.6318516871287894,    1.6642794823505174,    1.6976631193260889,
    1.7320508075688767,    1.7674940162428909,    1.8040477552714236,    1.8417708860334581,    1.8807264653463318,    1.9209821269711651,    1.9626105055051504,    2.0056897082590202,
    2.050303841579296,    2.0965435990881738,    2.1445069205095586,    2.1942997311650374,    2.2460367739042151,    2.2998425472362567,    2.3558523658237531,    2.4142135623730949,
    2.4750868534162946,    2.5386478956643073,    2.6050890646938023,    2.674621493926824,    2.7474774194546216,    2.8239128856008011,    2.9042108776758222,    2.9886849627428917,
    3.0776835371752527,    3.1715948023632135,    3.2708526184841404,    3.3759434225912446,    3.4874144438409087,    3.6058835087608729,    3.7320508075688776,    3.8667130948987372,
    4.0107809335358455,    4.1652997700904164,    4.3314758742841528,    4.5107085036620562,    4.7046301094784564,    4.9151570310712049,    5.1445540159703071,    5.3955171743191315,
    5.6712818196177066,    5.9757643644330667,    6.3137515146750411,    6.6911562383174026,    7.115369722384207,    7.5957541127251424,    8.1443464279745932,    8.776887356869949,
    9.5143644542225871,    10.38539708013815,    11.43005230276132,    12.706204736174696,    14.300666256711942,    16.349855476099663,    19.081136687728161,    22.903765548431192,
    28.636253282915515,    38.188459297025304,    57.289961630759144,    114.58865012931011,    0,    -114.58865012931172,    -57.289961630759549,    -38.188459297025808,
    -28.636253282915796,    -22.903765548431256,    -19.081136687728208,    -16.349855476099638,    -14.300666256711921,    -12.706204736174715,    -11.430052302761336,    -10.385397080138164,
    -9.5143644542225978,    -8.7768873568699579,    -8.1443464279746021,    -7.5957541127251629,    -7.1153697223842247,    -6.6911562383174079,    -6.3137515146750367,    -5.9757643644330631,
    -5.6712818196177111,    -5.395517174319135,    -5.1445540159703107,    -4.9151570310712076,    -4.7046301094784591,    -4.5107085036620589,    -4.331475874284159,    -4.1652997700904226,
    -4.0107809335358473,    -3.8667130948987354,    -3.7320508075688763,    -3.6058835087608747,    -3.48741444384091,    -3.3759434225912459,    -3.2708526184841422,    -3.1715948023632148,
    -3.077683537175254,    -2.9886849627428949,    -2.9042108776758253,    -2.823912885600802,    -2.7474774194546225,    -2.6746214939268231,    -2.6050890646938014,    -2.5386478956643082,
    -2.4750868534162955,    -2.4142135623730954,    -2.355852365823754,    -2.2998425472362571,    -2.2460367739042169,    -2.1942997311650396,    -2.1445069205095595,    -2.0965435990881733,
    -2.0503038415792956,    -2.0056897082590197,    -1.962610505505151,    -1.9209821269711667,    -1.8807264653463334,    -1.8417708860334578,    -1.804047755271424,    -1.7674940162428914,
    -1.7320508075688783,    -1.6976631193260903,    -1.6642794823505178,    -1.63185168712879,    -1.6003345290410511,    -1.5696855771174898,    -1.5398649638145827,    -1.5108351936149012,
    -1.4825609685127408,    -1.4550090286724455,    -1.4281480067421155,    -1.401948294476336,    -1.3763819204711738,    -1.3514224379458089,    -1.3270448216204096,    -1.3032253728412055,
    -1.279941632193079,    -1.2571722989189551,    -1.2348971565350519,    -1.2130970040929325,    -1.19175359259421,    -1.1708495661125395,    -1.1503684072210101,    -1.1302943863617536,
    -1.1106125148291937,    -1.0913085010692716,    -1.0723687100246828,    -1.0537801252809618,    -1.0355303137905694,    -1.0176073929721252,    0,    -0.9826972631156905,
    -0.9656887748070746,    -0.9489645667148805,    -0.93251508613766176,    -0.91633117401742359,    -0.9004040442978396,    -0.88472526455594358,    -0.86928673781622667,    -0.85408068546346683,
    -0.83909963117728037,    -0.82433638581749624,    -0.80978403319500702,    -0.79543591666782854,    -0.78128562650671762,    -0.76732698797896071,    -0.75355405010279464,    -0.73996107502848762,
    -0.72654252800536101,    -0.71329306789700564,    -0.70020753820970949,    -0.68728095860161309,    -0.67450851684242674,    -0.66188556119569175,    -0.64940759319751096,    -0.63707026080749363,
    -0.62486935190932746,    -0.61280078813993211,    -0.60086061902756072,    -0.58904501642055085,    -0.57735026918962573,    -0.56577277818777016,    -0.5543090514527691,    -0.54295569963843726,
    -0.53170943166147866,    -0.52056705055174624,    -0.50952544949442891,    -0.49858160805343177,    -0.48773258856586177,    -0.47697553269816068,    -0.46630765815499864,    -0.45572625553258489,
    -0.44522868530853593,    -0.4348123749609335,    -0.42447481620960476,    -0.41421356237309515,    -0.40402622583515707,    -0.39391047561494275,    -0.38386403503541627,    -0.37388467948480475,
    -0.36397023426620256,    -0.35411857253069784,    -0.34432761328966516,    -0.33459531950207316,    -0.32491969623290645,    -0.31529878887898377,    -0.30573068145866067,    -0.29621349496208021,
    -0.28674538575880798,    -0.27732454405983864,    -0.26794919243112297,    -0.25861758435589066,    -0.24932800284318071,    -0.24007875908011617,    -0.23086819112556334,    -0.22169466264293977,
    -0.2125565616700221,    -0.20345229942369944,    -0.19438030913771864,    -0.18533904493153464,    -0.17632698070846534,    -0.16734260908141957,    -0.15838444032453641,    -0.149451001349128,
    -0.14054083470239132,    -0.13165249758739583,    -0.12278456090290465,    -0.11393560830164566,    -0.10510423526567673,    -0.096289048197538543,    -0.087488663525924021,    -0.078701706824618564,
    -0.069926811943510636,    -0.061162620150484626,    -0.052407779283041619,    -0.043660942908512135,    -0.034920769491747904,    -0.026185921569186754,    -0.017455064928217509,    -0.0087268677907588136
};

unit_local const float64 asine_table[360] = {
    -1.5707963267948966,    -1.4653382097729968,    -1.4215867531897484,    -1.3879676100508016,    -1.3595854464357182,    -1.3345450208101262,    -1.3118747847886754,    -1.2909978508678623,
    -1.2715385080758619,    -1.2532358975033751,    -1.235900168355518,    -1.2193880569996676,    -1.2035883062370596,    -1.1884124735890216,    -1.1737888775957623,    -1.1596584644725487,
    -1.145971899316008,    -1.1326874657034041,    -1.1197695149986342,    -1.1071872991574336,    -1.0949140771344799,    -1.082926420377921,    -1.0712036657527422,    -1.059727479364178,
    -1.0484815049888481,    -1.0374510778842423,    -1.0266229897075312,    -1.0159852938148251,    -1.0055271427758981,    -0.99523865182134963,    -0.98511078333774571,    -0.97513524857750977,
    -0.96530442354888779,    -0.95561127666385581,    -0.94604930619603278,    -0.93661248597085578,    -0.9272952180016123,    -0.91809229101589507,    -0.90899884400146158,    -0.90001033404868758,
    -0.8911225078866527,    -0.88233137660740224,    -0.87363319315266419,    -0.86502443220288783,    -0.85650177216264967,    -0.848062078981481,    -0.83970239158669147,    -0.83141990873620653,
    -0.8232119771258759,    -0.81507608060804027,    -0.80700983039706498,    -0.79901095615364959,    -0.79107729785345382,    -0.78320679835735574,    -0.77539749661075297,    -0.76764752140803094,
    -0.75995508566584546,    -0.75231848115538602,    -0.74473607364945116,    -0.73720629844510133,    -0.72972765622696645,    -0.7222987092400539,    -0.71491807774421812,    -0.70758443672535565,
    -0.70029651284096583,    -0.69305308157997247,    -0.6858529646187107,    -0.6786950273567649,    -0.67157817661791541,    -0.66450135850286174,    -0.65746355638164378,    -0.65046378901479707,
    -0.64350110879328437,    -0.63657460008814204,    -0.62968337770157945,    -0.62282658541200286,    -0.616003394606079,    -0.60921300299154324,    -0.6024546333849905,    -0.5957275325693614,
    -0.58903097021627393,    -0.58236423786874347,    -0.57572664798018991,    -0.5691175330059558,    -0.56253624454385565,    -0.55598215252054228,    -0.54945464442072622,    -0.54295312455650291,
    -0.53647701337424902,    -0.53002574679673886,    -0.52359877559829893,    -0.51719556481097761,    -0.51081559315985392,    -0.50445835252573556,    -0.49812334743362624,    -0.4918100945654445,
    -0.48551812229559116,    -0.47924697024804724,    -0.4729961888737777,    -0.46676533904729633,    -0.46055399168132238,    -0.45436172735852637,    -0.4481881359794313,    -0.44203281642559072,
    -0.43589537623722258,    -0.42977543130452767,    -0.42367260557197151,    -0.4175865307548477,    -0.41151684606748806,    -0.40546319796251812,    -0.39942523988059464,    -0.3934026320100944,
    -0.38739504105625305,    -0.38140214001928524,    -0.37542360798103941,    -0.36945912989976992,    -0.36350839641262944,    -0.35757110364551026,    -0.35164695302987792,    -0.34573565112626714,
    -0.33983690945412198,    -0.33395044432768162,    -0.32807597669763,    -0.32221323199823859,    -0.31636193999975132,    -0.31052183466576783,    -0.30469265401539758,    -0.29887413998996698,
    -0.29306603832407424,    -0.28726809842079365,    -0.28148007323084495,    -0.27570171913554942,    -0.26993279583340352,    -0.26417306623010933,    -0.25842229633190961,    -0.25268025514207865,
    -0.24694671456043293,    -0.24122144928572564,    -0.23550423672079973,    -0.22979485688037765,    -0.22409309230137084,    -0.21839872795559964,    -0.21271155116481621,    -0.20703135151792887,
    -0.20135792079033074,    -0.19569105286523944,    -0.19003054365695687,    -0.18437619103596498,    -0.17872779475577347,    -0.1730851563814404,    -0.16744807921968929,    -0.1618163682505496,
    -0.15618983006044823,    -0.15056827277668605,    -0.14495150600323164,    -0.13933934075776949,    -0.13373158940994151,    -0.12812806562072102,    -0.12252858428286376,    -0.11693296146237846,
    -0.11134101434096394,    -0.10575256115935965,    -0.10016742116155977,    -0.094585414539839457,    -0.089006362380547238,    -0.083430086610615045,    -0.077856409944740343,    -0.07228515583319646,
    -0.066716148410225246,    -0.061149212442971841,    -0.055584173280917498,    -0.050020856805770057,    -0.044459089381771261,    -0.038898697806381652,    -0.03333950926130208,    -0.027781351263795242,
    -0.022224051618267186,    -0.016667438368071559,    -0.011111339747498734,    -0.0055555841339131364,    0,    0.0055555841339131364,    0.011111339747498734,    0.016667438368071448,
    0.022224051618267071,    0.027781351263795131,    0.033339509261302192,    0.038898697806381763,    0.044459089381771372,    0.050020856805770057,    0.055584173280917498,    0.061149212442971841,
    0.066716148410225246,    0.07228515583319646,    0.077856409944740343,    0.083430086610614934,    0.089006362380547127,    0.094585414539839568,    0.10016742116155988,    0.10575256115935976,
    0.11134101434096394,    0.11693296146237846,    0.12252858428286376,    0.12812806562072102,    0.13373158940994151,    0.13933934075776949,    0.14495150600323153,    0.15056827277668594,
    0.15618983006044812,    0.16181636825054971,    0.16744807921968941,    0.1730851563814404,    0.17872779475577347,    0.18437619103596498,    0.19003054365695687,    0.19569105286523944,
    0.20135792079033074,    0.20703135151792876,    0.2127115511648161,    0.21839872795559953,    0.22409309230137095,    0.22979485688037776,    0.23550423672079984,    0.24122144928572564,
    0.24694671456043293,    0.25268025514207865,    0.25842229633190961,    0.26417306623010933,    0.2699327958334034,    0.27570171913554931,    0.28148007323084484,    0.28726809842079376,
    0.29306603832407435,    0.29887413998996709,    0.30469265401539758,    0.31052183466576783,    0.31636193999975132,    0.32221323199823859,    0.32807597669763,    0.33395044432768162,
    0.33983690945412187,    0.34573565112626703,    0.35164695302987803,    0.35757110364551037,    0.36350839641262955,    0.36945912989976992,    0.37542360798103941,    0.38140214001928524,
    0.38739504105625305,    0.3934026320100944,    0.39942523988059464,    0.40546319796251801,    0.41151684606748795,    0.41758653075484758,    0.42367260557197162,    0.42977543130452778,
    0.43589537623722258,    0.44203281642559072,    0.4481881359794313,    0.45436172735852637,    0.46055399168132238,    0.46676533904729633,    0.47299618887377759,    0.47924697024804713,
    0.48551812229559105,    0.49181009456544461,    0.49812334743362635,    0.50445835252573579,    0.51081559315985392,    0.51719556481097761,    0.52359877559829893,    0.53002574679673886,
    0.53647701337424902,    0.54295312455650291,    0.54945464442072622,    0.55598215252054217,    0.56253624454385576,    0.56911753300595591,    0.57572664798018991,    0.58236423786874347,
    0.58903097021627393,    0.5957275325693614,    0.6024546333849905,    0.60921300299154324,    0.616003394606079,    0.62282658541200286,    0.62968337770157934,    0.63657460008814215,
    0.64350110879328448,    0.65046378901479707,    0.65746355638164378,    0.66450135850286174,    0.67157817661791541,    0.6786950273567649,    0.6858529646187107,    0.69305308157997247,
    0.70029651284096583,    0.70758443672535543,    0.71491807774421789,    0.72229870924005413,    0.72972765622696645,    0.73720629844510133,    0.74473607364945116,    0.75231848115538602,
    0.75995508566584546,    0.76764752140803094,    0.77539749661075297,    0.78320679835735574,    0.7910772978534536,    0.79901095615364937,    0.8070098303970652,    0.81507608060804027,
    0.8232119771258759,    0.83141990873620653,    0.83970239158669147,    0.848062078981481,    0.85650177216264967,    0.86502443220288783,    0.87363319315266419,    0.88233137660740202,
    0.89112250788665259,    0.9000103340486878,    0.9089988440014618,    0.91809229101589507,    0.9272952180016123,    0.93661248597085578,    0.94604930619603278,    0.95561127666385581,
    0.96530442354888779,    0.97513524857750977,    0.98511078333774549,    0.99523865182134941,    1.0055271427758983,    1.0159852938148253,    1.0266229897075312,    1.0374510778842423,
    1.0484815049888481,    1.059727479364178,    1.0712036657527422,    1.082926420377921,    1.0949140771344799,    1.1071872991574334,    1.119769514998634,    1.1326874657034038,
    1.1459718993160082,    1.1596584644725492,    1.1737888775957623,    1.1884124735890216,    1.2035883062370596,    1.2193880569996676,    1.235900168355518,    1.2532358975033751,
    1.2715385080758614,    1.2909978508678619,    1.3118747847886749,    1.3345450208101266,    1.3595854464357187,    1.387967610050802,    1.4215867531897484,    1.4653382097729968
};

unit_local const float64 acosine_table[360] = {
    3.1415926535897931,    3.0361345365678933,    2.9923830799846449,    2.9587639368456982,    2.9303817732306148,    2.9053413476050229,    2.8826711115835719,    2.8617941776627589,
    2.8423348348707584,    2.8240322242982718,    2.8066964951504145,    2.7901843837945641,    2.7743846330319561,    2.7592088003839184,    2.7445852043906589,    2.7304547912674453,
    2.7167682261109043,    2.7034837924983006,    2.6905658417935308,    2.6779836259523302,    2.6657104039293764,    2.6537227471728175,    2.641999992547639,    2.6305238061590748,
    2.6192778317837444,    2.6082474046791386,    2.5974193165024277,    2.5867816206097216,    2.5763234695707946,    2.5660349786162464,    2.555907110132642,    2.5459315753724066,
    2.5361007503437847,    2.5264076034587526,    2.5168456329909294,    2.5074088127657523,    2.4980915447965089,    2.4888886178107916,    2.4797951707963581,    2.4708066608435844,
    2.4619188346815495,    2.4531277034022989,    2.444429519947561,    2.4358207589977843,    2.4272980989575466,    2.4188584057763776,    2.410498718381588,    2.4022162355311032,
    2.3940083039207725,    2.3858724074029367,    2.3778061571919618,    2.3698072829485461,    2.3618736246483505,    2.3540031251522522,    2.3461938234056499,    2.3384438482029273,
    2.3307514124607422,    2.3231148079502826,    2.3155324004443476,    2.3080026252399981,    2.3005239830218631,    2.2930950360349507,    2.2857144045391147,    2.2783807635202522,
    2.2710928396358625,    2.263849408374869,    2.2566492914136074,    2.2494913541516617,    2.2423745034128117,    2.2352976852977582,    2.2282598831765403,    2.2212601158096934,
    2.2142974355881808,    2.2073709268830388,    2.2004797044964759,    2.1936229122068998,    2.1867997214009756,    2.18000932978644,    2.1732509601798871,    2.1665238593642577,
    2.1598272970111703,    2.15316056466364,    2.1465229747750865,    2.1399138598008527,    2.1333325713387525,    2.1267784793154387,    2.120250971215623,    2.1137494513513992,
    2.1072733401691455,    2.1008220735916354,    2.0943951023931957,    2.0879918916058742,    2.0816119199547503,    2.0752546793206323,    2.068919674228523,    2.062606421360341,
    2.0563144490904879,    2.0500432970429436,    2.0437925156686743,    2.0375616658421931,    2.0313503184762189,    2.0251580541534229,    2.0189844627743279,    2.0128291432204874,
    2.0066917030321192,    2.0005717580994244,    1.9944689323668681,    1.9883828575497442,    1.9823131728623846,    1.9762595247574146,    1.9702215666754912,    1.9641989588049911,
    1.9581913678511498,    1.9521984668141819,    1.9462199347759361,    1.9402554566946666,    1.9343047232075261,    1.9283674304404068,    1.9224432798247746,    1.9165319779211638,
    1.9106332362490186,    1.9047467711225783,    1.8988723034925266,    1.8930095587931353,    1.887158266794648,    1.8813181614606644,    1.8754889808102941,    1.8696704667848636,
    1.8638623651189707,    1.8580644252156904,    1.8522764000257417,    1.8464980459304461,    1.8407291226283,    1.8349693930250059,    1.8292186231268062,    1.8234765819369754,
    1.8177430413553295,    1.8120177760806222,    1.8063005635156963,    1.8005911836752744,    1.7948894190962674,    1.7891950547504962,    1.7835078779597129,    1.7778276783128255,
    1.7721542475852274,    1.7664873796601361,    1.7608268704518535,    1.7551725178308617,    1.7495241215506701,    1.743881483176337,    1.7382444060145859,    1.7326126950454461,
    1.7269861568553448,    1.7213645995715827,    1.7157478327981281,    1.7101356675526662,    1.7045279162048381,    1.6989243924156177,    1.6933249110777604,    1.687729288257275,
    1.6821373411358607,    1.6765488879542563,    1.6709637479564563,    1.665381741334736,    1.6598026891754438,    1.6542264134055116,    1.6486527367396371,    1.6430814826280931,
    1.6375124752051218,    1.6319455392378686,    1.626380500075814,    1.6208171836006666,    1.6152554161766679,    1.6096950246012782,    1.6041358360561988,    1.5985776780586918,
    1.5930203784131638,    1.5874637651629682,    1.5819076665423955,    1.5763519109288098,    1.5707963267948966,    1.5652407426609836,    1.5596849870473979,    1.5541288884268252,
    1.5485722751766295,    1.5430149755311016,    1.5374568175335945,    1.5318976289885149,    1.5263372374131252,    1.5207754699891265,    1.5152121535139791,    1.5096471143519248,
    1.5040801783846713,    1.4985111709617001,    1.4929399168501563,    1.4873662401842818,    1.4817899644143495,    1.4762109122550571,    1.4706289056333368,    1.4650437656355368,
    1.4594553124539327,    1.4538633653325181,    1.4482677425120329,    1.4426682611741757,    1.4370647373849552,    1.4314569860371271,    1.425844820791665,    1.4202280540182106,
    1.4146064967344485,    1.408979958544347,    1.4033482475752073,    1.3977111704134562,    1.3920685320391231,    1.3864201357589316,    1.3807657831379396,    1.3751052739296572,
    1.3694384060045659,    1.3637649752769678,    1.3580847756300805,    1.3523975988392971,    1.3467032344935257,    1.3410014699145187,    1.3352920900740968,    1.3295748775091709,
    1.3238496122344636,    1.318116071652818,    1.312374030462987,    1.3066232605647872,    1.3008635309614931,    1.2950946076593473,    1.2893162535640519,    1.2835282283741027,
    1.2777302884708224,    1.2719221868049295,    1.266103672779499,    1.2602744921291289,    1.2544343867951453,    1.2485830947966581,    1.2427203500972666,    1.2368458824672151,
    1.2309594173407747,    1.2250606756686295,    1.2191493737650185,    1.2132252231493863,    1.207287930382267,    1.2013371968951267,    1.1953727188138572,    1.1893941867756115,
    1.1834012857386436,    1.1773936947848023,    1.1713710869143019,    1.1653331288323785,    1.1592794807274087,    1.1532097960400489,    1.1471237212229251,    1.1410208954903689,
    1.1349009505576741,    1.1287635103693059,    1.1226081908154653,    1.1164345994363702,    1.1102423351135742,    1.1040309877476004,    1.0978001379211191,    1.0915493565468495,
    1.0852782044993057,    1.0789862322294521,    1.0726729793612702,    1.0663379742691608,    1.0599807336350429,    1.0536007619839189,    1.0471975511965979,    1.0407705799981577,
    1.0343193134206476,    1.0278432022383936,    1.0213416823741703,    1.0148141742743544,    1.0082600822510408,    1.0016787937889406,    0.99506967881470665,    0.98843208892615309,
    0.98176535657862274,    0.97506879422553527,    0.96834169340990606,    0.96158332380335343,    0.95479293218881767,    0.9479697413828938,    0.94111294909331733,    0.93422172670675441,
    0.92729521800161208,    0.9203325377800996,    0.91333277041325278,    0.90629496829203482,    0.89921815017698126,    0.89210129943813166,    0.88494336217618585,    0.87774324521492408,
    0.87049981395393072,    0.86321189006954113,    0.85587824905067866,    0.84849761755484254,    0.84106867056793011,    0.83359002834979523,    0.82606025314544551,    0.81847784563951054,
    0.8108412411290512,    0.80314880538686562,    0.79539883018414359,    0.78758952843754093,    0.77971902894144296,    0.77178537064124719,    0.76378649639783147,    0.7557202461868564,
    0.74758434966902076,    0.73937641805869003,    0.73109393520820509,    0.72273424781341566,    0.71429455463224689,    0.70577189459200873,    0.69716313364223237,    0.68846495018749454,
    0.67967381890824408,    0.67078599274620887,    0.66179748279343487,    0.6527040357790016,    0.64350110879328426,    0.63418384082404078,    0.62474702059886389,    0.61518505013104074,
    0.60549190324600888,    0.59566107821738679,    0.58568554345715107,    0.57555767497354715,    0.56526918401899839,    0.55481103298007128,    0.54417333708736537,    0.53334524891065438,
    0.5223148218060486,    0.51106884743071856,    0.4995926610421545,    0.48786990641697564,    0.47588224966041665,    0.4636090276374632,    0.45102681179626264,    0.43810886109149277,
    0.42482442747888843,    0.4111378623223475,    0.39700744919913439,    0.38238385320587509,    0.36720802055783708,    0.35140826979522916,    0.33489615843937875,    0.31756042929152151,
    0.29925781871903512,    0.27979847592703461,    0.25892154200622164,    0.23625130598477004,    0.21121088035917793,    0.18282871674409445,    0.14920957360514839,    0.10545811702189975
};

#endif // _TRIG_TABLES_H

/* End include: trig_tables.h */

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wbad-function-cast"
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
#pragma clang diagnostic ignored "-Wbad-function-cast"
#endif // __clang__

#define clamp(x, a, b) (min(max((x), (a)), (b)))

#define abs(x) ((x) < 0 ? -(x) : (x))

#define PI 3.141592653589793
#define TAU (PI*2)

unit_local inline f32 lerp32(f32 a, f32 b, f32 t) {
    return a + (b-a)*t;
}
unit_local inline f64 lerp64(f64 a, f64 b, f64 t) {
    return a + (b-a)*t;
}

unit_local inline f32 floor32(f32 f) {
    return (f32)((f) < 0 ? (s64)(f) - 1 : (s64)(f));
}
unit_local inline f32 ceil32(f32 f) {
    return (f32)((f) == (f32)(s64)(f) ? (s64)(f) : (f) > 0 ? (s64)(f) + 1 : (s64)(f));
}
unit_local inline f64 floor64(f64 f) {
    return (f64)((f) < 0 ? (s64)(f) - 1 : (s64)(f));
}
unit_local inline f64 ceil64(f64 f) {
    return (f64)((f) == (f64)(s64)(f) ? (s64)(f) : (f) > 0 ? (s64)(f) + 1 : (s64)(f));
}

#define trig_lookup(t, f) do { \
    s64 c = sizeof(t) / sizeof(f64); \
    f64 norm_index = (f) * (f64)c; \
    s64 ilo = (s64)floor64(norm_index); \
    s64 ihi = (s64)ceil64(norm_index); \
    if (ihi >= c) return t[0]; \
    f64 t_frac = norm_index - (f64)ilo;\
    return lerp64(t[ilo], t[ihi], t_frac); \
} while (0)


unit_local inline float64 fmod_cycling(float64 x, float64 y) {
    if (y == 0.0) {
        return 0.0;
    }
    float64 n = (int)(x / y);
    return x - n * y;
}

unit_local inline float64 sin(float64 x) {
    if (x == 0.0) return 0.0;
    x = fmod_cycling(x, TAU);
    trig_lookup(sine_table, x/TAU);
}
unit_local inline float64 asin(float64 x) {
    if (x == 0.0) return 0.0;
    x = clamp(x, -1.0, 1.0);
    trig_lookup(asine_table, ((x+1.0)/2.0)/TAU);
}
unit_local inline float64 cos(float64 x) {
    if (x == 0.0) return 1.0;
    x = fmod_cycling(x, TAU);
    trig_lookup(cosine_table, x/TAU);
}
unit_local inline float64 acos(float64 x) {
    if (x == 1.0) return 0.0;
    x = clamp(x, -1.0, 1.0);
    trig_lookup(acosine_table, ((x+1.0)/2.0)/TAU);
}
unit_local inline float64 tan(float64 x) {
    x = fmod_cycling(x, TAU);
    s64 i = (s64)((x/TAU) * (f64)(sizeof(tan_table)/sizeof(float64)));
    if (i >= (s64)(sizeof(tan_table)/sizeof(float64))) return tan_table[0];
    return tan_table[i];
}
unit_local inline float64 atan(float64 x) {
    if (x == 0.0) return 0.0;
    float64 theta = (x < 1.0 && x > -1.0) ? x : (x > 0.0 ? PI / 2 : -PI / 2);
    
    for (int i = 0; i < 5; ++i) { 
        float64 sin_theta = sin(theta);
        float64 cos_theta = cos(theta);
        float64 tan_theta = sin_theta / cos_theta;
        
        theta -= (tan_theta - x) / (1.0 + tan_theta * tan_theta);
    }
    
    return theta;
}

unit_local inline float64 atan2(float64 y, float64 x) {
    return (x > 0) ? atan(y / x) :
           (x < 0 && y >= 0) ? atan(y / x) + PI :
           (x < 0 && y < 0) ? atan(y / x) - PI :
           (y > 0) ? PI / 2 :
           (y < 0) ? -PI / 2 : 0.0;
}

#define f2_expand(v) (v).x, (v).y
#define f3_expand(v) (v).x, (v).y, (v).z
#define f4_expand(v) (v).x, (v).y, (v).z, (v).w

#define f2 f2x32
#define f3 f3x32
#define f4 f4x32

#define f2_scalar f2x32_scalar
#define f3_scalar f3x32_scalar
#define f4_scalar f4x32_scalar

#define f2_one  f2x32_one
#define f3_one  f3x32_one
#define f4_one  f4x32_one

#define f2_zero  f2x32_zero
#define f3_zero  f3x32_zero
#define f4_zero  f4x32_zero

#define f2_add  f2x32_add
#define f3_add  f3x32_add
#define f4_add  f4x32_add

#define f2_sub  f2x32_sub
#define f3_sub  f3x32_sub
#define f4_sub  f4x32_sub

#define f2_mul  f2x32_mul
#define f3_mul  f3x32_mul
#define f4_mul  f4x32_mul

#define f2_mulf  f2x32_mulf32
#define f3_mulf  f3x32_mulf32
#define f4_mulf  f4x32_mulf32

#define f2_div  f2x32_div
#define f3_div  f3x32_div
#define f4_div  f4x32_div

#define f2_divf  f2x32_divf32
#define f3_divf  f3x32_divf32
#define f4_divf  f4x32_divf32

#define f2_len  f2x32_len
#define f3_len  f3x32_len
#define f4_len  f4x32_len

#define f2_lensq  f2x32_lensq
#define f3_lensq  f3x32_lensq
#define f4_lensq  f4x32_lensq

#define f2_average  f2x32_average
#define f3_average  f3x32_average
#define f4_average  f4x32_average

#define f2_normalize  f2x32_normalize
#define f3_normalize  f3x32_normalize
#define f4_normalize  f4x32_normalize

#define f2_dot  f2x32_dot
#define f3_dot  f3x32_dot
#define f4_dot  f4x32_dot

#define f2_perp  f2x32_perp
#define f3_cross  f3x32_cross

typedef struct int32x2 {
    int32 x, y;
} int32x2;

typedef struct int32x4 {
    int32 x, y, z, w;
} int32x4;

typedef int32x2 int2;


typedef struct float2x32 {
    float x, y;
} float2x32;
typedef struct float3x32 {
    float x, y, z;
} float3x32;
typedef struct float4x32 {
    float x, y, z, w;
} float4x32;

typedef float2x32 float2;
typedef float3x32 float3;
typedef float4x32 float4;

unit_local inline float32 ln32(float32 x) {
    u32 bx = * (u32 *) (&x);
    u32 ex = bx >> 23;
    s32 t = (s32)ex-(s32)127;
    bx = 1065353216 | (bx & 8388607);
    x = * (float32 *) (&bx);
    return -1.49278f+(2.11263f+(-0.729104f+0.10969f*x)*x)*x+0.6931471806f*(float32)t;
}
unit_local inline float64 ln64(float64 x) {
    u64 bx = *(u64 *)(&x);
    u64 ex = bx >> 52;
    s32 t = (s32)ex - 1023;
    bx = 4607182418800017408ULL | (bx & 4503599627370495ULL);
    x = *(float64 *)(&bx);
    return -1.49278 + (2.11263 + (-0.729104 + 0.10969 * x) * x) * x + 0.6931471806 * t;
}

unit_local inline u64 powu(u64 x, u64 e) {
    if (e == 0) return 1;
    u64 result = x;
    for (u64 i = 0; i < e-1; i += 1) {
        result *= x;
    }
    return result;
}
unit_local inline f64 powf64(f64 x, f64 e) {
    if (e == 0) return 1;
    f64 result = x;
    for (f64 i = 0; i < e-1; i += 1) {
        result *= x;
    }
    return result;
}

unit_local inline float32 sqrt32(float32 n) {
    if (n < 0.0f) {
        return -1.0f;
    }
    if (n == 0.0f) {
        return 0.0f;
    }

    float32 x = n;
    float32 tolerance = 0.000001f;
    float32 delta;

    do {
        float32 next_x = 0.5f * (x + n / x);
        delta = next_x - x;
        if (delta < 0.0f) {
            delta = -delta;
        }
        x = next_x;
    } while (delta > tolerance);

    return x;
}

unit_local inline float64 sqrt64(float64 n) {
    if (n < 0.0) {
        return -1.0;
    }
    if (n == 0.0) {
        return 0.0;
    }

    float64 x = n;
    float64 tolerance = 0.000001;
    float64 delta;

    do {
        float64 next_x = 0.5 * (x + n / x);
        delta = next_x - x;
        if (delta < 0.0) {
            delta = -delta;
        }
        x = next_x;
    } while (delta > tolerance);

    return x;
}

unit_local inline float2x32 f2x32(float32 x, float32 y)                       { return (float2x32){x, y}; }
unit_local inline float3x32 f3x32(float32 x, float32 y, float32 z)            { return (float3x32){x, y, z}; }
unit_local inline float4x32 f4x32(float32 x, float32 y, float32 z, float32 w) { return (float4x32){x, y, z, w}; }

unit_local inline float2x32 f2x32_scalar(float32 a) { return (float2x32){a, a}; }
unit_local inline float3x32 f3x32_scalar(float32 a) { return (float3x32){a, a, a}; }
unit_local inline float4x32 f4x32_scalar(float32 a) { return (float4x32){a, a, a, a}; }

unit_local const float2x32 f2x32_one = {1, 1};
unit_local const float3x32 f3x32_one = {1, 1, 1};
unit_local const float4x32 f4x32_one = {1, 1, 1, 1};

unit_local const float2x32 f2x32_zero = {0, 0};
unit_local const float3x32 f3x32_zero = {0, 0, 0};
unit_local const float4x32 f4x32_zero = {0, 0, 0, 0};

unit_local inline float2x32 f2x32_add(float2x32 a, float2x32 b)  { return f2x32(a.x+b.x, a.y+b.y); }
unit_local inline float3x32 f3x32_add(float3x32 a, float3x32 b)  { return f3x32(a.x+b.x, a.y+b.y, a.z+b.z); }
unit_local inline float4x32 f4x32_add(float4x32 a, float4x32 b)  { return f4x32(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w); }

unit_local inline float2x32 f2x32_sub(float2x32 a, float2x32 b)  { return f2x32(a.x-b.x, a.y-b.y); }
unit_local inline float3x32 f3x32_sub(float3x32 a, float3x32 b)  { return f3x32(a.x-b.x, a.y-b.y, a.z-b.z); }
unit_local inline float4x32 f4x32_sub(float4x32 a, float4x32 b)  { return f4x32(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w); }

unit_local inline float2x32 f2x32_mul(float2x32 a, float2x32 b)  { return f2x32(a.x*b.x, a.y*b.y); }
unit_local inline float3x32 f3x32_mul(float3x32 a, float3x32 b)  { return f3x32(a.x*b.x, a.y*b.y, a.z*b.z); }
unit_local inline float4x32 f4x32_mul(float4x32 a, float4x32 b)  { return f4x32(a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w); }

unit_local inline float2x32 f2x32_mulf32(float2x32 a, float32 s) { return f2x32_mul(a, f2x32(s, s)); }
unit_local inline float3x32 f3x32_mulf32(float3x32 a, float32 s) { return f3x32_mul(a, f3x32(s, s, s)); }
unit_local inline float4x32 f4x32_mulf32(float4x32 a, float32 s) { return f4x32_mul(a, f4x32(s, s, s, s)); }

unit_local inline float2x32 f2x32_div(float2x32 a, float2x32 b)  { return f2x32(a.x/b.x, a.y/b.y); }
unit_local inline float3x32 f3x32_div(float3x32 a, float3x32 b)  { return f3x32(a.x/b.x, a.y/b.y, a.z/b.z); }
unit_local inline float4x32 f4x32_div(float4x32 a, float4x32 b)  { return f4x32(a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w); }

unit_local inline float2x32 f2x32_divf32(float2x32 a, float32 s) { return f2x32_div(a, f2x32(s, s)); }
unit_local inline float3x32 f3x32_divf32(float3x32 a, float32 s) { return f3x32_div(a, f3x32(s, s, s)); }
unit_local inline float4x32 f4x32_divf32(float4x32 a, float32 s) { return f4x32_div(a, f4x32(s, s, s, s)); }

unit_local inline float32 f2x32_lensq(float2x32 a) { return a.x*a.x + a.y*a.y; }
unit_local inline float32 f3x32_lensq(float3x32 a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
unit_local inline float32 f4x32_lensq(float4x32 a) { return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w; }

unit_local inline float32 f2x32_len(float2x32 a) { return sqrt32(a.x*a.x + a.y*a.y); }
unit_local inline float32 f3x32_len(float3x32 a) { return sqrt32(a.x * a.x + a.y * a.y + a.z * a.z); }
unit_local inline float32 f4x32_len(float4x32 a) { return sqrt32(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w); }

unit_local inline float32 f2x32_average(float2x32 a) { return (a.x+a.y)/2.0f; }
unit_local inline float32 f3x32_average(float3x32 a) { return (a.x + a.y + a.z) / 3.0f; }
unit_local inline float32 f4x32_average(float4x32 a) { return (a.x + a.y + a.z + a.w) / 4.0f; }

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
#endif // __clang__

unit_local inline float2x32 f2x32_normalize(float2x32 a) { return f2x32_lensq(a) == 0 ? f2x32_scalar(0) : f2x32_divf32(a, f2x32_len(a)); }
unit_local inline float3x32 f3x32_normalize(float3x32 a) { return f3x32_lensq(a) == 0 ? f3x32_scalar(0) : f3x32_divf32(a, f3x32_len(a)); }
unit_local inline float4x32 f4x32_normalize(float4x32 a) { return f4x32_lensq(a) == 0 ? f4x32_scalar(0) : f4x32_divf32(a, f4x32_len(a)); }

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

unit_local inline float32 f2x32_dot(float2x32 a, float2x32 b) { return a.x * b.x + a.y * b.y; }
unit_local inline float32 f3x32_dot(float3x32 a, float3x32 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
unit_local inline float32 f4x32_dot(float4x32 a, float4x32 b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

unit_local inline float32 f2x32_perp(float2x32 a, float2x32 b) { return (a.x * b.y) - (a.y * b.x); }
unit_local inline float3x32 f3x32_cross(float3x32 a, float3x32 b) { return f3x32((a.y*b.z)-(a.z*b.y), (a.z*b.x)-(a.x*b.z), (a.x*b.y)-(a.y*b.x)); }


// Column major
typedef struct Matrix4 {
    float32 data[4][4];
} Matrix4;

unit_local inline Matrix4 m4_scalar(float32 scalar) {
    Matrix4 m = (Matrix4){0};
    m.data[0][0] = scalar; 
    m.data[1][1] = scalar; 
    m.data[2][2] = scalar; 
    m.data[3][3] = scalar; 
    return m;
}

unit_local inline Matrix4 m4_identity(void) { return m4_scalar(1.0); }

unit_local inline Matrix4 m4_make_translation(float3 translation) {
    Matrix4 m = m4_identity();    
    *(float3*)m.data[3] = translation;
    
    return m;
}

unit_local inline Matrix4 m4_translate(Matrix4 m, float3 translation) {
    m.data[3][0] = translation.x;
    m.data[3][1] = translation.y;
    m.data[3][2] = translation.z;
    return m;
}

unit_local inline float m4_trace(Matrix4 m) {
    float a = m.data[0][0];
    a += m.data[1][1];
    a += m.data[2][2];
    a += m.data[3][3];
    
    return a;
}

unit_local inline Matrix4 m4_add(Matrix4 m0, Matrix4 m1) {
    *(float4*)m0.data[0] = f4_add(*(float4*)m0.data[0], *(float4*)m1.data[0]);
    *(float4*)m0.data[1] = f4_add(*(float4*)m0.data[1], *(float4*)m1.data[1]);
    *(float4*)m0.data[2] = f4_add(*(float4*)m0.data[2], *(float4*)m1.data[2]);
    *(float4*)m0.data[3] = f4_add(*(float4*)m0.data[3], *(float4*)m1.data[3]);
    
    return m0;
}

unit_local inline Matrix4 m4_make_scale(float3 scalars) {
    Matrix4 m = m4_identity();
    *(float4*)m.data[0] = f4_mulf(*(float4*)m.data[0], scalars.x);
    *(float4*)m.data[1] = f4_mulf(*(float4*)m.data[1], scalars.y);
    *(float4*)m.data[2] = f4_mulf(*(float4*)m.data[2], scalars.z);
    
    return m;
}

unit_local inline Matrix4 m4_scalef(Matrix4 m, float32 scalar) {
    *(float4*)m.data[0] = f4_mulf(*(float4*)m.data[0], scalar);
    *(float4*)m.data[1] = f4_mulf(*(float4*)m.data[1], scalar);
    *(float4*)m.data[2] = f4_mulf(*(float4*)m.data[2], scalar);
    *(float4*)m.data[3] = f4_mulf(*(float4*)m.data[3], scalar);
    
    return m;
}
unit_local inline Matrix4 m4_scale(Matrix4 m, float3 scalars) {
    *(float4*)m.data[0] = f4_mulf(*(float4*)m.data[0], scalars.x);
    *(float4*)m.data[1] = f4_mulf(*(float4*)m.data[1], scalars.y);
    *(float4*)m.data[2] = f4_mulf(*(float4*)m.data[2], scalars.z);
    
    return m;
}
unit_local inline Matrix4 m4_scale_f4(Matrix4 m, float4 scalars) {
    *(float4*)m.data[0] = f4_mulf(*(float4*)m.data[0], scalars.x);
    *(float4*)m.data[1] = f4_mulf(*(float4*)m.data[1], scalars.y);
    *(float4*)m.data[2] = f4_mulf(*(float4*)m.data[2], scalars.z);
    *(float4*)m.data[3] = f4_mulf(*(float4*)m.data[3], scalars.w);
    
    return m;
}

unit_local inline Matrix4 m4_make_rotation_x(float rad) {
    float c = (f32)cos((f64)rad);
    float s = (f32)sin((f64)rad);
    return (Matrix4){{
        {  c,  0, -s,  0 },
        {  0,  1,  0,  0 },
        {  0,  0,  c,  0 },
        {  s,  0,  0,  1 },
    }};
}
unit_local inline Matrix4 m4_make_rotation_y(float rad) {
    float c = (f32)cos((f64)rad);
    float s = (f32)sin((f64)rad);
    return (Matrix4){{
        {  1,  0,  0,  0 },
        {  0,  c,  s,  0 },
        {  0, -s,  c,  0 },
        {  0,  0,  0,  1 },
    }};
}
unit_local inline Matrix4 m4_make_rotation_z(float rad) {
    float c = (f32)cos((f64)rad);
    float s = (f32)sin((f64)rad);
    return (Matrix4){{
        {  c,  s,  0,  0 },
        { -s,  c,  0,  0 },
        {  0,  0,  1,  0 },
        {  0,  0,  0,  1 },
    }};
}

unit_local inline Matrix4 m4_transpose(Matrix4 m) {
    Matrix4 tm = m;
    
    // Diagonal is copied over, but swap each side of it
    
    tm.data[0][1] = m.data[1][0];
    tm.data[0][2] = m.data[2][0];
    tm.data[0][3] = m.data[3][0];
    
    tm.data[1][0] = m.data[0][1];
    tm.data[1][2] = m.data[2][1];
    tm.data[1][3] = m.data[3][1];
    
    tm.data[2][0] = m.data[0][2];
    tm.data[2][1] = m.data[1][2];
    tm.data[2][3] = m.data[3][2];
    
    tm.data[3][0] = m.data[0][3];
    tm.data[3][1] = m.data[1][3];
    tm.data[3][2] = m.data[2][3];
    
    return tm;
} 

unit_local inline Matrix4 m4_mulm4(Matrix4 m0, Matrix4 m1) {
/*
        m = m0 * m1
        
        each ij in m should be dot(m0[row:i], m1[col:j])
        
        We transpose m0 so we can read rows trivially (since our matrices are column-major)
*/

    // todo(charlie) very easily vectorized


    Matrix4 tm0 = m4_transpose(m0);
    Matrix4 m;
    
    *(float*)&m.data[0][0] = f4_dot(*(float4*)tm0.data[0], *(float4*)m1.data[0]);
    *(float*)&m.data[0][1] = f4_dot(*(float4*)tm0.data[1], *(float4*)m1.data[0]);
    *(float*)&m.data[0][2] = f4_dot(*(float4*)tm0.data[2], *(float4*)m1.data[0]);
    *(float*)&m.data[0][3] = f4_dot(*(float4*)tm0.data[3], *(float4*)m1.data[0]);
    
    *(float*)&m.data[1][0] = f4_dot(*(float4*)tm0.data[0], *(float4*)m1.data[1]);
    *(float*)&m.data[1][1] = f4_dot(*(float4*)tm0.data[1], *(float4*)m1.data[1]);
    *(float*)&m.data[1][2] = f4_dot(*(float4*)tm0.data[2], *(float4*)m1.data[1]);
    *(float*)&m.data[1][3] = f4_dot(*(float4*)tm0.data[3], *(float4*)m1.data[1]);
    
    *(float*)&m.data[2][0] = f4_dot(*(float4*)tm0.data[0], *(float4*)m1.data[2]);
    *(float*)&m.data[2][1] = f4_dot(*(float4*)tm0.data[1], *(float4*)m1.data[2]);
    *(float*)&m.data[2][2] = f4_dot(*(float4*)tm0.data[2], *(float4*)m1.data[2]);
    *(float*)&m.data[2][3] = f4_dot(*(float4*)tm0.data[3], *(float4*)m1.data[2]);
    
    *(float*)&m.data[3][0] = f4_dot(*(float4*)tm0.data[0], *(float4*)m1.data[3]);
    *(float*)&m.data[3][1] = f4_dot(*(float4*)tm0.data[1], *(float4*)m1.data[3]);
    *(float*)&m.data[3][2] = f4_dot(*(float4*)tm0.data[2], *(float4*)m1.data[3]);
    *(float*)&m.data[3][3] = f4_dot(*(float4*)tm0.data[3], *(float4*)m1.data[3]);
    
    return m;
}

unit_local inline float4 m4_mulf4(Matrix4 m0, float4 m1) {
    Matrix4 tm0 = m4_transpose(m0);
    
    float4 f;
    f.x = f4_dot(*(float4*)tm0.data[0], m1);
    f.y = f4_dot(*(float4*)tm0.data[1], m1);
    f.z = f4_dot(*(float4*)tm0.data[2], m1);
    f.w = f4_dot(*(float4*)tm0.data[3], m1);
    
    return f;
}

// This aren't actually real well-defined mathmatical operations,
// but nevertheless useful and makes sense to a game developer.
// It just fills in the z w components to 0 1 if missing.
// This only makes sense in games.
unit_local inline float3 m4_mulf3_trunc(Matrix4 m0, float3 m1) {
    Matrix4 tm0 = m4_transpose(m0);
    
    float3 f;
    f.x = f4_dot(*(float4*)tm0.data[0], f4(m1.x, m1.y, m1.z, 1.0f));
    f.y = f4_dot(*(float4*)tm0.data[1], f4(m1.x, m1.y, m1.z, 1.0f));
    f.z = f4_dot(*(float4*)tm0.data[2], f4(m1.x, m1.y, m1.z, 1.0f));
    
    return f;
} 
unit_local inline float2 m4_mulf2_trunc(Matrix4 m0, float2 m1) {
    Matrix4 tm0 = m4_transpose(m0);
    
    float2 f;
    f.x = f4_dot(*(float4*)tm0.data[0], f4(m1.x, m1.y, 0.0f, 1.0f));
    f.y = f4_dot(*(float4*)tm0.data[1], f4(m1.x, m1.y, 0.0f, 1.0f));
    
    return f;
} 

unit_local inline f64 get_power_of_two_f64(f64 x, u64 exp) {
    return x * (f64)(1ULL << exp);
}

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

#endif //_MATH_H

/* End include: math.h */
#endif // _MATH_H
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
#ifndef _MATH_H
#endif // _MATH_H

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

    u64 n = format_string_args(0, 0, fmt, arg_count, args, 0);

    u8 buffer[4096];
    u64 written = 0;

    while (written < n) {
        u64 to_write = min(n, 4096);
        u64 consumed_args;
        format_string_args(buffer, to_write, fmt, arg_count, args, &consumed_args);
        args += consumed_args;
        arg_count -= consumed_args;

        sys_write(f, buffer, to_write);

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

u64 string_to_unsigned_int(string str, int base, bool *success)
{
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

// todo(charlie) make a stack of non-OK results which can be popped
typedef enum Oga_Result {
    OGA_OK,

    OGA_SUBOPTIMAL,
    OGA_NOT_READY,
    OGA_TIMEOUT,

    // Trying to use device features that were not available.
    // Check Oga_Device::features flags for whether or not a feature is available.
    OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES,
    
    OGA_CONTEXT_INIT_ERROR_BAD_STATE_ALLOCATOR,
    
    // The given family index is not within the range 0 .. Oga_Device::engine_family_count
    OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE,
    // The given engine creation count overflows that of Oga_Logical_Engine_Family_Info::engine_capacity
    OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW,
    
    OGA_INIT_SWAPCHAIN_ERROR_SURFACE_REJECTED,
    OGA_INIT_SWAPCHAIN_ERROR_UNSUPPORTED_PRESENT_MODE,
    
    OGA_INIT_PROGRAM_ERROR_BAD_CODE,
    
    OGA_ERROR_STATE_ALLOCATION_FAILED,
    OGA_ERROR_OUT_OF_DEVICE_MEMORY,
    OGA_ERROR_OUTDATED,
    OGA_ERROR_SURFACE_LOST,
    
    OGA_ALLOCATE_MEMORY_ERROR_INVALID_PROPERTIES_AND_USAGE_COMBINATION,
    OGA_ERROR_INVALID_INPUT_RATE_ENUM,
    
    OGA_MEMORY_OFFSET_ERROR_UNDERFLOW,
    OGA_MEMORY_OFFSET_ERROR_OVERFLOW,
    
    OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM,
    OGA_CMD_DRAW_ERROR_VERTEX_LIST_BINDING_COUNT_ZERO,
    OGA_CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING,
    OGA_CMD_DRAW_ERROR_VERTEX_LIST_OFFSET_OUT_OF_RANGE,
    OGA_CMD_DRAW_ERROR_MISSING_INDEX_LIST,
    OGA_CMD_DRAW_ERROR_INVALID_INDEX_TYPE_ENUM,
    
    OGA_INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT,
    OGA_INIT_INDEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT,
    
    OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM,
    OGA_INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED,
    OGA_INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT,
    OGA_INIT_OPTIMAL_COPY_VIEW_ERROR_INVALID_FLAGS,
    
    OGA_INIT_RENDER_PASS_ERROR_INVALID_PROGRAM_BINDING_KIND_ENUM,
    OGA_INIT_BINDING_LIST_LAYOUT_ERROR_MISSING_STAGE_FLAGS,
    
    OGA_PUSH_BINDING_LIST_ERROR_LAYOUT_COUNT_MISMATCH,
    
} Oga_Result;

#define OGA_LOG_VERBOSE (1 << 16)

unit_local inline string oga_get_result_name(Oga_Result r) {
    switch (r) {
        case OGA_OK: return STR("OGA_OK");
        case OGA_SUBOPTIMAL:                                            return STR("OGA_SUBOPTIMAL");
        case OGA_NOT_READY:                                             return STR("OGA_NOT_READY");
        case OGA_TIMEOUT:                                               return STR("OGA_TIMEOUT");
        case OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES:            return STR("OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES");
        case OGA_CONTEXT_INIT_ERROR_BAD_STATE_ALLOCATOR:                return STR("OGA_CONTEXT_INIT_ERROR_BAD_STATE_ALLOCATOR");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE: return STR("OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW:  return STR("OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW");
        case OGA_INIT_SWAPCHAIN_ERROR_SURFACE_REJECTED:                 return STR("OGA_INIT_SWAPCHAIN_ERROR_SURFACE_REJECTED");
        case OGA_INIT_SWAPCHAIN_ERROR_UNSUPPORTED_PRESENT_MODE:         return STR("OGA_INIT_SWAPCHAIN_ERROR_UNSUPPORTED_PRESENT_MODE");
        case OGA_INIT_PROGRAM_ERROR_BAD_CODE:                           return STR("OGA_INIT_PROGRAM_ERROR_BAD_CODE");
        case OGA_ERROR_STATE_ALLOCATION_FAILED:                         return STR("OGA_ERROR_STATE_ALLOCATION_FAILED");
        case OGA_ERROR_OUT_OF_DEVICE_MEMORY:                            return STR("OGA_ERROR_OUT_OF_DEVICE_MEMORY");
        case OGA_ERROR_OUTDATED:                                        return STR("OGA_ERROR_OUTDATED");
        case OGA_ERROR_SURFACE_LOST:                                    return STR("OGA_ERROR_SURFACE_LOST");
        case OGA_ALLOCATE_MEMORY_ERROR_INVALID_PROPERTIES_AND_USAGE_COMBINATION: return STR("OGA_ALLOCATE_MEMORY_ERROR_INVALID_PROPERTIES_AND_USAGE_COMBINATION");
        case OGA_ERROR_INVALID_INPUT_RATE_ENUM:                         return STR("OGA_ERROR_INVALID_INPUT_RATE_ENUM");
        case OGA_MEMORY_OFFSET_ERROR_UNDERFLOW:                         return STR("OGA_MEMORY_OFFSET_ERROR_UNDERFLOW");
        case OGA_MEMORY_OFFSET_ERROR_OVERFLOW:                          return STR("OGA_MEMORY_OFFSET_ERROR_OVERFLOW");
        case OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM:                 return STR("OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM");
        case OGA_CMD_DRAW_ERROR_VERTEX_LIST_BINDING_COUNT_ZERO:         return STR("OGA_CMD_DRAW_ERROR_VERTEX_LIST_BINDING_COUNT_ZERO");
        case OGA_CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING:            return STR("OGA_CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING");
        case OGA_CMD_DRAW_ERROR_VERTEX_LIST_OFFSET_OUT_OF_RANGE:        return STR("OGA_CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING");
        case OGA_CMD_DRAW_ERROR_MISSING_INDEX_LIST:                     return STR("OGA_CMD_DRAW_ERROR_MISSING_INDEX_LIST");
        case OGA_CMD_DRAW_ERROR_INVALID_INDEX_TYPE_ENUM:                return STR("OGA_CMD_DRAW_ERROR_INVALID_INDEX_TYPE_ENUM");
        case OGA_INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT:      return STR("OGA_INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT");
        case OGA_INIT_INDEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT:       return STR("OGA_INIT_INDEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT");
        case OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM:         return STR("OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM");
        case OGA_INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED:            return STR("OGA_INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED");
        case OGA_INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT:      return STR("OGA_INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT");
        case OGA_INIT_OPTIMAL_COPY_VIEW_ERROR_INVALID_FLAGS:       return STR("OGA_INIT_OPTIMAL_COPY_VIEW_ERROR_INVALID_FLAGS");
        case OGA_INIT_RENDER_PASS_ERROR_INVALID_PROGRAM_BINDING_KIND_ENUM: return STR("OGA_INIT_RENDER_PASS_ERROR_INVALID_PROGRAM_BINDING_KIND_ENUM");
        case OGA_INIT_BINDING_LIST_LAYOUT_ERROR_MISSING_STAGE_FLAGS:    return STR("OGA_INIT_BINDING_LIST_LAYOUT_ERROR_MISSING_STAGE_FLAGS");
        case OGA_PUSH_BINDING_LIST_ERROR_LAYOUT_COUNT_MISMATCH:         return STR("OGA_PUSH_BINDING_LIST_ERROR_LAYOUT_COUNT_MISMATCH");
        default: return STR("<>");
    }
    return STR("<>");
}
unit_local inline string oga_get_result_message(Oga_Result r) {
    switch (r) {
        case OGA_OK: return STR("No error");
        case OGA_SUBOPTIMAL: 
            return STR("Swapchain is suboptimal and should be recreated, but can still be used.");
        case OGA_NOT_READY: 
            return STR("Swapchain has no ready imagess yet");
        case OGA_TIMEOUT: 
            return STR("A timeout expired");
        case OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES:
            return STR("Trying to use device features that were not available. Check Oga_Device::features flags for whether or not a feature is available.");
        case OGA_CONTEXT_INIT_ERROR_BAD_STATE_ALLOCATOR:
            return STR("Passed a bad state allocator. allocator.proc is null.");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE:
            return STR("The given family index is not within the range 0 .. Oga_Device::engine_family_count");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW:
            return STR("The given engine creation count overflows that of Oga_Logical_Engine_Family_Info::engine_capacity");
        case OGA_INIT_SWAPCHAIN_ERROR_SURFACE_REJECTED:
            return STR("The provided surface handle was rejected, possibly bad.");
        case OGA_INIT_SWAPCHAIN_ERROR_UNSUPPORTED_PRESENT_MODE:
            return STR("The provided present_mode was either unsupported or just an invalid value.");
        case OGA_INIT_PROGRAM_ERROR_BAD_CODE:
            return STR("The code passed was bad (or code_size) was incorrect.");
        case OGA_ERROR_STATE_ALLOCATION_FAILED:
            return STR("An allocation with the state_allocator passed in Oga_Context creation returned 0 upon allocation.");
        case OGA_ERROR_OUT_OF_DEVICE_MEMORY:
            return STR("Out of device memory");
        case OGA_ERROR_OUTDATED:
            return STR("A swapchain has become out of date and can no longer present");
        case OGA_ERROR_SURFACE_LOST:
            return STR("A surface was lost; closed or corrupt");
        case OGA_ALLOCATE_MEMORY_ERROR_INVALID_PROPERTIES_AND_USAGE_COMBINATION:
            return STR("The given combination of memory property flags and usage flags did not match to an available heap & memory type. Please see Oga_Device::memory_heaps for heap availability and support.");
        case OGA_ERROR_INVALID_INPUT_RATE_ENUM:
            return STR("The given Oga_Vertex_Attribute_Type enum for Oga_Vertex_List_Attribute_Desc::type was not a valid enum value. It muse be one of: OGA_VERTEX_INPUT_RATE_VERTEX or OGA_VERTEX_INPUT_RATE_INSTANCE.");
        case OGA_MEMORY_OFFSET_ERROR_UNDERFLOW:
            return STR("The resulting pointer from oga_memory_offset() underflows the allocated memory block");
        case OGA_MEMORY_OFFSET_ERROR_OVERFLOW:
            return STR("The resulting pointer from oga_memory_offset() overflows the allocated memory block");
        case OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM:
            return STR("The value in Oga_Draw_Desc::draw_type was of an invalid value. See enum Oga_Draw_Type for valid values.");
        case OGA_CMD_DRAW_ERROR_VERTEX_LIST_BINDING_COUNT_ZERO:
            return STR("A vertex list draw command was submitted but Oga_Draw_Desc::vertex_list_binding_count is 0.");
        case OGA_CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING:
            return STR("A binding slot within the range 0 to Oga_Draw_Desc::vertex_list_binding_count was set to 0 in Oga_Draw_Desc::vertex_list_bindings.");
        case OGA_CMD_DRAW_ERROR_VERTEX_LIST_OFFSET_OUT_OF_RANGE:
            return STR("A vertex list binding offset in Oga_Draw_Desc::vertex_list_offsets was out of range");
        case OGA_CMD_DRAW_ERROR_MISSING_INDEX_LIST:
            return STR("An indexed draw command was submitted but Oga_Draw_Desc::index_list was set to 0.");
        case OGA_CMD_DRAW_ERROR_INVALID_INDEX_TYPE_ENUM:
            return STR("An indexed draw command was submitted Oga_Draw_Desc::index_type was of an invalid enum value. Valid values are: OGA_INDEX_U32 or OGA_INDEX_U16");
        case OGA_INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT:
            return STR("Tried creating a Vertex List View, pointing to memory from a heap which lacks the support flag OGA_MEMORY_USAGE_VERTEX_LIST. Make sure you include the usage flag OGA_MEMORY_USAGE_VERTEX_LIST in oga_allocate_memory() to make sure you get memory from a heap with the required support flags.");
        case OGA_INIT_INDEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT:
            return STR("Tried creating a Vertex List View, pointing to memory from a heap which lacks the support flag OGA_MEMORY_USAGE_INDEX_LIST. Make sure you include the usage flag OGA_MEMORY_USAGE_INDEX_LIST in oga_allocate_memory() to make sure you get memory from a heap with the required support flags.");
        case OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM:
            return STR("Oga_Image_View_Desc::dimensions was an invalid value. It must be one of: OGA_1D, OGA_2D or OGA_3D");
        case OGA_INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED:
            return STR("Oga_Image_View_Desc::memory_pointer offset must be aligned to Oga_Device::limits.image_memory_granularity, but it was not.");
        case OGA_INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT:
            return STR("Oga_Image_View_Desc::memory_pointer allocation size is not enough to meet the memory requirement for the image. To get the memory requirement for an image kind and size, use oga_get_image_memory_requirement()");
        case OGA_INIT_OPTIMAL_COPY_VIEW_ERROR_INVALID_FLAGS:
            return STR("Oga_Optimal_Copy_View_Desc::flags does not convey any intent.");
        case OGA_INIT_RENDER_PASS_ERROR_INVALID_PROGRAM_BINDING_KIND_ENUM:
            return STR("A program binding had an invalid enum value for Oga_Program_Binding_Desc::kind. See Oga_Binding_Kind for valid enum values.");
        case OGA_INIT_BINDING_LIST_LAYOUT_ERROR_MISSING_STAGE_FLAGS:
            return STR("A Oga_Program_Binding_Desc::stage_flags was 0. It needs to contain at least one valid stage flag from Oga_Program_Stage_Flag");
        case OGA_PUSH_BINDING_LIST_ERROR_LAYOUT_COUNT_MISMATCH:
            return STR("Oga_Binding_List_Desc::binding_count is greater than what was passed into oga_init_binding_list_layout Oga_Binding_List_Layout_Desc::binding_count. Cannot allocate a binding list with more bindings than was specified for the layout.");
        default: return STR("<>");
    }
    return STR("<>");
}

typedef enum Oga_Format {
    OGA_FORMAT_R4G4_UNORM_PACK8,
    OGA_FORMAT_R4G4B4A4_UNORM_PACK16,
    OGA_FORMAT_B4G4R4A4_UNORM_PACK16,
    OGA_FORMAT_R5G6B5_UNORM_PACK16,
    OGA_FORMAT_B5G6R5_UNORM_PACK16,
    OGA_FORMAT_R5G5B5A1_UNORM_PACK16,
    OGA_FORMAT_A1R5G5B5_UNORM_PACK16,

    OGA_FORMAT_R8_UNORM,
    OGA_FORMAT_R8_SNORM,
    OGA_FORMAT_R8_UINT,
    OGA_FORMAT_R8_SINT,
    OGA_FORMAT_R8_SRGB,

    OGA_FORMAT_R8G8_UNORM,
    OGA_FORMAT_R8G8_SNORM,
    OGA_FORMAT_R8G8_UINT,
    OGA_FORMAT_R8G8_SINT,
    OGA_FORMAT_R8G8_SRGB,

    OGA_FORMAT_R8G8B8_UNORM,
    OGA_FORMAT_R8G8B8_SNORM,
    OGA_FORMAT_R8G8B8_UINT,
    OGA_FORMAT_R8G8B8_SINT,
    OGA_FORMAT_R8G8B8_SRGB,

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

    OGA_FORMAT_R16_UNORM,
    OGA_FORMAT_R16_SNORM,
    OGA_FORMAT_R16_UINT,
    OGA_FORMAT_R16_SINT,
    OGA_FORMAT_R16_SFLOAT,

    OGA_FORMAT_R16G16_UNORM,
    OGA_FORMAT_R16G16_SNORM,
    OGA_FORMAT_R16G16_UINT,
    OGA_FORMAT_R16G16_SINT,
    OGA_FORMAT_R16G16_SFLOAT,

    OGA_FORMAT_R16G16B16A16_UNORM,
    OGA_FORMAT_R16G16B16A16_SNORM,
    OGA_FORMAT_R16G16B16A16_UINT,
    OGA_FORMAT_R16G16B16A16_SINT,
    OGA_FORMAT_R16G16B16A16_SFLOAT,

    OGA_FORMAT_R32_SFLOAT,
    OGA_FORMAT_R32_UINT,
    OGA_FORMAT_R32_SINT,

    OGA_FORMAT_R32G32_SFLOAT,
    OGA_FORMAT_R32G32_UINT,
    OGA_FORMAT_R32G32_SINT,

    OGA_FORMAT_R32G32B32_SFLOAT,
    OGA_FORMAT_R32G32B32_UINT,
    OGA_FORMAT_R32G32B32_SINT,

    OGA_FORMAT_R32G32B32A32_SFLOAT,
    OGA_FORMAT_R32G32B32A32_UINT,
    OGA_FORMAT_R32G32B32A32_SINT,
    
    OGA_FORMAT_DEPTH16_UNORM,
    OGA_FORMAT_DEPTH24_UNORM_S8_UINT,
    OGA_FORMAT_DEPTH32_SFLOAT,
    OGA_FORMAT_DEPTH32_SFLOAT_S8_UINT,

    OGA_FORMAT_BC1_RGB_UNORM_BLOCK,
    OGA_FORMAT_BC1_RGB_SRGB_BLOCK,
    OGA_FORMAT_BC1_RGBA_UNORM_BLOCK,
    OGA_FORMAT_BC1_RGBA_SRGB_BLOCK,
    OGA_FORMAT_BC2_UNORM_BLOCK,
    OGA_FORMAT_BC2_SRGB_BLOCK,
    OGA_FORMAT_BC3_UNORM_BLOCK,
    OGA_FORMAT_BC3_SRGB_BLOCK,
    OGA_FORMAT_BC4_UNORM_BLOCK,
    OGA_FORMAT_BC4_SNORM_BLOCK,
    OGA_FORMAT_BC5_UNORM_BLOCK,
    OGA_FORMAT_BC5_SNORM_BLOCK,
    OGA_FORMAT_BC6H_UFLOAT_BLOCK,
    OGA_FORMAT_BC6H_SFLOAT_BLOCK,
    OGA_FORMAT_BC7_UNORM_BLOCK,
    OGA_FORMAT_BC7_SRGB_BLOCK,

    OGA_FORMAT_ENUM_MAX,
} Oga_Format;

unit_local inline string oga_format_str(Oga_Format f) {
    switch (f) {
        case OGA_FORMAT_R4G4_UNORM_PACK8:              return RSTR(R4G4_UNORM_PACK8);
        case OGA_FORMAT_R4G4B4A4_UNORM_PACK16:          return RSTR(R4G4B4A4_UNORM_PACK16);
        case OGA_FORMAT_B4G4R4A4_UNORM_PACK16:          return RSTR(B4G4R4A4_UNORM_PACK16);
        case OGA_FORMAT_R5G6B5_UNORM_PACK16:            return RSTR(R5G6B5_UNORM_PACK16);
        case OGA_FORMAT_B5G6R5_UNORM_PACK16:            return RSTR(B5G6R5_UNORM_PACK16);
        case OGA_FORMAT_R5G5B5A1_UNORM_PACK16:          return RSTR(R5G5B5A1_UNORM_PACK16);
        case OGA_FORMAT_A1R5G5B5_UNORM_PACK16:          return RSTR(A1R5G5B5_UNORM_PACK16);

        case OGA_FORMAT_R8_UNORM:                       return RSTR(R8_UNORM);
        case OGA_FORMAT_R8_SNORM:                       return RSTR(R8_SNORM);
        case OGA_FORMAT_R8_UINT:                        return RSTR(R8_UINT);
        case OGA_FORMAT_R8_SINT:                        return RSTR(R8_SINT);
        case OGA_FORMAT_R8_SRGB:                        return RSTR(R8_SRGB);

        case OGA_FORMAT_R8G8_UNORM:                     return RSTR(R8G8_UNORM);
        case OGA_FORMAT_R8G8_SNORM:                     return RSTR(R8G8_SNORM);
        case OGA_FORMAT_R8G8_UINT:                      return RSTR(R8G8_UINT);
        case OGA_FORMAT_R8G8_SINT:                      return RSTR(R8G8_SINT);
        case OGA_FORMAT_R8G8_SRGB:                      return RSTR(R8G8_SRGB);

        case OGA_FORMAT_R8G8B8_UNORM:                   return RSTR(R8G8B8_UNORM);
        case OGA_FORMAT_R8G8B8_SNORM:                   return RSTR(R8G8B8_SNORM);
        case OGA_FORMAT_R8G8B8_UINT:                    return RSTR(R8G8B8_UINT);
        case OGA_FORMAT_R8G8B8_SINT:                    return RSTR(R8G8B8_SINT);
        case OGA_FORMAT_R8G8B8_SRGB:                    return RSTR(R8G8B8_SRGB);

        case OGA_FORMAT_R8G8B8A8_UNORM:                 return RSTR(R8G8B8A8_UNORM);
        case OGA_FORMAT_R8G8B8A8_SNORM:                 return RSTR(R8G8B8A8_SNORM);
        case OGA_FORMAT_R8G8B8A8_UINT:                  return RSTR(R8G8B8A8_UINT);
        case OGA_FORMAT_R8G8B8A8_SINT:                  return RSTR(R8G8B8A8_SINT);
        case OGA_FORMAT_R8G8B8A8_SRGB:                  return RSTR(R8G8B8A8_SRGB);

        case OGA_FORMAT_B8G8R8A8_UNORM:                 return RSTR(B8G8R8A8_UNORM);
        case OGA_FORMAT_B8G8R8A8_SNORM:                 return RSTR(B8G8R8A8_SNORM);
        case OGA_FORMAT_B8G8R8A8_UINT:                  return RSTR(B8G8R8A8_UINT);
        case OGA_FORMAT_B8G8R8A8_SINT:                  return RSTR(B8G8R8A8_SINT);
        case OGA_FORMAT_B8G8R8A8_SRGB:                  return RSTR(B8G8R8A8_SRGB);

        case OGA_FORMAT_R16_UNORM:                      return RSTR(R16_UNORM);
        case OGA_FORMAT_R16_SNORM:                      return RSTR(R16_SNORM);
        case OGA_FORMAT_R16_UINT:                       return RSTR(R16_UINT);
        case OGA_FORMAT_R16_SINT:                       return RSTR(R16_SINT);
        case OGA_FORMAT_R16_SFLOAT:                     return RSTR(R16_SFLOAT);

        case OGA_FORMAT_R16G16_UNORM:                   return RSTR(R16G16_UNORM);
        case OGA_FORMAT_R16G16_SNORM:                   return RSTR(R16G16_SNORM);
        case OGA_FORMAT_R16G16_UINT:                    return RSTR(R16G16_UINT);
        case OGA_FORMAT_R16G16_SINT:                    return RSTR(R16G16_SINT);
        case OGA_FORMAT_R16G16_SFLOAT:                  return RSTR(R16G16_SFLOAT);

        case OGA_FORMAT_R16G16B16A16_UNORM:             return RSTR(R16G16B16A16_UNORM);
        case OGA_FORMAT_R16G16B16A16_SNORM:             return RSTR(R16G16B16A16_SNORM);
        case OGA_FORMAT_R16G16B16A16_UINT:              return RSTR(R16G16B16A16_UINT);
        case OGA_FORMAT_R16G16B16A16_SINT:              return RSTR(R16G16B16A16_SINT);
        case OGA_FORMAT_R16G16B16A16_SFLOAT:            return RSTR(R16G16B16A16_SFLOAT);

        case OGA_FORMAT_R32_SFLOAT:                     return RSTR(R32_SFLOAT);
        case OGA_FORMAT_R32_UINT:                       return RSTR(R32_UINT);
        case OGA_FORMAT_R32_SINT:                       return RSTR(R32_SINT);

        case OGA_FORMAT_R32G32_SFLOAT:                  return RSTR(R32G32_SFLOAT);
        case OGA_FORMAT_R32G32_UINT:                    return RSTR(R32G32_UINT);
        case OGA_FORMAT_R32G32_SINT:                    return RSTR(R32G32_SINT);

        case OGA_FORMAT_R32G32B32_SFLOAT:               return RSTR(R32G32B32_SFLOAT);
        case OGA_FORMAT_R32G32B32_UINT:                 return RSTR(R32G32B32_UINT);
        case OGA_FORMAT_R32G32B32_SINT:                 return RSTR(R32G32B32_SINT);

        case OGA_FORMAT_R32G32B32A32_SFLOAT:            return RSTR(R32G32B32A32_SFLOAT);
        case OGA_FORMAT_R32G32B32A32_UINT:              return RSTR(R32G32B32A32_UINT);
        case OGA_FORMAT_R32G32B32A32_SINT:              return RSTR(R32G32B32A32_SINT);

        case OGA_FORMAT_DEPTH16_UNORM:                  return RSTR(DEPTH16_UNORM);
        case OGA_FORMAT_DEPTH24_UNORM_S8_UINT:          return RSTR(DEPTH24_UNORM_S8_UINT);
        case OGA_FORMAT_DEPTH32_SFLOAT:                 return RSTR(DEPTH32_SFLOAT);
        case OGA_FORMAT_DEPTH32_SFLOAT_S8_UINT:         return RSTR(DEPTH32_SFLOAT_S8_UINT);

        case OGA_FORMAT_BC1_RGB_UNORM_BLOCK:            return RSTR(BC1_RGB_UNORM_BLOCK);
        case OGA_FORMAT_BC1_RGB_SRGB_BLOCK:             return RSTR(BC1_RGB_SRGB_BLOCK);
        case OGA_FORMAT_BC1_RGBA_UNORM_BLOCK:           return RSTR(BC1_RGBA_UNORM_BLOCK);
        case OGA_FORMAT_BC1_RGBA_SRGB_BLOCK:            return RSTR(BC1_RGBA_SRGB_BLOCK);
        case OGA_FORMAT_BC2_UNORM_BLOCK:                return RSTR(BC2_UNORM_BLOCK);
        case OGA_FORMAT_BC2_SRGB_BLOCK:                 return RSTR(BC2_SRGB_BLOCK);
        case OGA_FORMAT_BC3_UNORM_BLOCK:                return RSTR(BC3_UNORM_BLOCK);
        case OGA_FORMAT_BC3_SRGB_BLOCK:                 return RSTR(BC3_SRGB_BLOCK);
        case OGA_FORMAT_BC4_UNORM_BLOCK:                return RSTR(BC4_UNORM_BLOCK);
        case OGA_FORMAT_BC4_SNORM_BLOCK:                return RSTR(BC4_SNORM_BLOCK);
        case OGA_FORMAT_BC5_UNORM_BLOCK:                return RSTR(BC5_UNORM_BLOCK);
        case OGA_FORMAT_BC5_SNORM_BLOCK:                return RSTR(BC5_SNORM_BLOCK);
        case OGA_FORMAT_BC6H_UFLOAT_BLOCK:              return RSTR(BC6H_UFLOAT_BLOCK);
        case OGA_FORMAT_BC6H_SFLOAT_BLOCK:              return RSTR(BC6H_SFLOAT_BLOCK);
        case OGA_FORMAT_BC7_UNORM_BLOCK:                return RSTR(BC7_UNORM_BLOCK);
        case OGA_FORMAT_BC7_SRGB_BLOCK:                 return RSTR(BC7_SRGB_BLOCK);

        case OGA_FORMAT_ENUM_MAX:
        default:
            return RSTR(<>);
    }
    return RSTR(<>);
}

typedef enum Oga_Memory_Property_Flag_ {
    // Memory is near GPU and accessed with high performance
    OGA_MEMORY_PROPERTY_GPU_LOCAL  = 0x00000001,
    // Memory can be mapped
    OGA_MEMORY_PROPERTY_GPU_TO_CPU_MAPPABLE  = 0x00000002,
    // Memory is directly reflected on CPU. Mapping is not needed to access memory
    OGA_MEMORY_PROPERTY_GPU_TO_CPU_REFLECTED = 0x00000004,
    // Cached memory is accessed quicker, but does not instantly reflect GPU writes
    OGA_MEMORY_PROPERTY_GPU_TO_CPU_CACHED   = 0x00000008,
} Oga_Memory_Property_Flag_;
typedef u64 Oga_Memory_Property_Flag;

typedef enum Oga_Memory_Usage_ {
    OGA_MEMORY_USAGE_NONE = 0,
    OGA_MEMORY_USAGE_VERTEX_LIST = 1 << 2,
    OGA_MEMORY_USAGE_INDEX_LIST = 1 << 3,
    // todo(charlie) rename
    OGA_MEMORY_USAGE_FAST_READONLY_DATA_BLOCK = 1 << 4,
    OGA_MEMORY_USAGE_LARGE_READWRITE_DATA_BLOCK = 1 << 5,
    OGA_MEMORY_USAGE_COPY_DST = 1 << 6,
    OGA_MEMORY_USAGE_COPY_SRC = 1 << 7,
    OGA_MEMORY_USAGE_IMAGE_1D = 1 << 8,
    OGA_MEMORY_USAGE_IMAGE_2D = 1 << 9,
    OGA_MEMORY_USAGE_IMAGE_3D = 1 << 10,
    OGA_MEMORY_USAGE_FBUFFER_1D = 1 << 8,
    OGA_MEMORY_USAGE_FBUFFER_2D = 1 << 9,
    OGA_MEMORY_USAGE_FBUFFER_3D = 1 << 10,
} Oga_Memory_Usage_;
typedef u64 Oga_Memory_Usage;

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
    u32 engine_capacity;
} Oga_Logical_Engine_Family_Info;

typedef struct Oga_Memory_Heap {
    Oga_Memory_Property_Flag properties;
    u64 size;
    Oga_Memory_Usage supported_usage_flags;
} Oga_Memory_Heap;

typedef enum Oga_Device_Kind {
    OGA_DEVICE_DISCRETE,
    OGA_DEVICE_INTEGRATED,
    OGA_DEVICE_CPU, // Software implementations
    OGA_DEVICE_OTHER,
} Oga_Device_Kind;

// todo(charlie) populate this with an exhaustive list.
typedef struct Oga_Device_Limits {
    u64 max_program_view_sets_per_stage;

    u64 max_fast_data_blocks_per_stage;
    u64 max_large_data_blocks_per_stage;
    u64 max_images_per_stage;
    u64 max_fbuffers_per_stage;
    u64 max_samplers_per_stage;

    u64 max_fast_data_blocks_per_layout;
    u64 max_large_data_blocks_per_layout;
    u64 max_images_per_layout;
    u64 max_fbuffers_per_layout;
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

    u64 max_render_attachments;

    u64 min_memory_map_alignment;

    Oga_Sample_Count_Flag supported_sample_counts_render_pass;

    Oga_Sample_Count_Flag supported_sample_counts_image_float;
    Oga_Sample_Count_Flag supported_sample_counts_fbuffer_float;
    Oga_Sample_Count_Flag supported_sample_counts_image_int;
    Oga_Sample_Count_Flag supported_sample_counts_fbuffer_int;
    
    u64 memory_granularity;
    u64 image_memory_granularity;
    u64 fbuffer_memory_granularity;

} Oga_Device_Limits;

typedef u64 Oga_Device_Feature_Flag;

#define OGA_DEVICE_FEATURE_GRAPHICS_TIMESTAMP (1 << 0)
#define OGA_DEVICE_FEATURE_COMPUTE_TIMESTAMP  (1 << 1)
#define OGA_DEVICE_FEATURE_PRESENT_MAILBOX    (1 << 2)
#define OGA_DEVICE_FEATURE_DEPTH_CLAMP    (1 << 3)

unit_local inline string oga_device_feature_str(Oga_Device_Feature_Flag f) {
    switch (f) {
        case OGA_DEVICE_FEATURE_GRAPHICS_TIMESTAMP: return STR("Graphics Timestamps");
        case OGA_DEVICE_FEATURE_COMPUTE_TIMESTAMP: return STR("Compute Timestamps");
        case OGA_DEVICE_FEATURE_PRESENT_MAILBOX: return STR("Present mailbox");
        default: return STR("<>");
    }
    return STR("<>");
}

#define OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES 32
#define OGA_MAX_DEVICE_LOGICAL_ENGINES_PER_FAMILY 32
#define OGA_MAX_MEMORY_HEAPS_PER_DEVICE 32
typedef struct Oga_Device {
    void *id;

    Oga_Device_Kind kind;

    // string
    u8 device_name_data[256];
    u64 device_name_length;

    u64 vendor_id;
    string vendor_name;
    u32 driver_version_raw;

    // string
    u8 driver_version_data[128];
    u64 driver_version_length;
    
    u32 api_version_raw;
    // string
    u8 api_version_data[128];
    u64 api_version_length;
    
    Oga_Device_Limits limits;

    Oga_Logical_Engine_Family_Info engine_family_infos[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES];
    u32 engine_family_count;

    Oga_Format depth_format;

    Oga_Memory_Heap memory_heaps[OGA_MAX_MEMORY_HEAPS_PER_DEVICE];
    u64 memory_heap_count;
    u64 total_gpu_local_memory;

    Oga_Device_Feature_Flag features;
    
    Oga_Format supported_surface_formats[OGA_FORMAT_ENUM_MAX];
    u64 supported_surface_format_count;

} Oga_Device;

typedef enum Oga_Device_Pick_Flag {
    OGA_DEVICE_PICK_NONE = 0,
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
// todo(charlie) add consideration for heap properties and usage flags
Oga_Pick_Device_Result oga_pick_device(Oga_Device_Pick_Flag pick_flags, Oga_Device_Feature_Flag required_features, Oga_Device_Feature_Flag preferred_features);

//////////
/// Oga Context


typedef struct Oga_Logical_Engines_Create_Desc {
    u32 count;
    float32 priorities[OGA_MAX_DEVICE_LOGICAL_ENGINES_PER_FAMILY]; // normalized 0.0-1.0.
} Oga_Logical_Engines_Create_Desc;

// Default allocator of non is specified in Oga_Context_Desc::state_allocator
void* oga_state_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags);


typedef struct Oga_Allocator_Row {
    void *start;
    void *end;
    u64 first_free_index;
    u64 highest_allocated_index;
} Oga_Allocator_Row;
typedef struct Oga_State_Allocator_Data {
    // 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8196, 16384
    Oga_Allocator_Row rows[11];
} Oga_State_Allocator_Data;

typedef struct Oga_Context_Desc {
    // Indices match to that of Oga_Device::engine_family_infos.
    // So the create engines of family 0, you set the desc in engine_create_descs[0].
    // Leave descs uninitialized to make no engines in that family.
    Oga_Logical_Engines_Create_Desc engine_create_descs[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES];
    Oga_Device_Feature_Flag enabled_features;
    Allocator state_allocator; // The allocator used to allocate state & handles in this context. Will only be used when creating/destroying things.
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
    Oga_Logical_Engine engines[OGA_MAX_DEVICE_LOGICAL_ENGINES_PER_FAMILY];
    u64 engine_count;
} Oga_Logical_Engine_Group;

typedef struct Oga_Context {
    void *id;
    void *internal;
    Oga_Device device;
    Oga_Logical_Engine_Group engines_by_family[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES];
    Allocator state_allocator;
    
    Oga_State_Allocator_Data default_allocator_data; // Backing for Allocator::data
} Oga_Context;

Oga_Result oga_init_context(Oga_Device target_device, Oga_Context_Desc desc, Oga_Context **context);
void oga_uninit_context(Oga_Context *context);

void oga_wait_engine_idle(Oga_Logical_Engine engine);
void oga_wait_context_idle(Oga_Context *context);

//////////
/// Swap chain

typedef enum Oga_Present_Mode {
    // Present() will halt the thread until at least 1 image is ready to be queued,
    // and then each image in the queue is presented and popped each vertical blank.
    OGA_PRESENT_MODE_VSYNC,
    // Present() Will submit the image to the queue, and if the queue is full, it will
    //  abort the image currently being presented, which will very likely cause visual tearing.
    // There may techically be devices that only support OGA_PRESENT_MODE_VSYNC, and in such
    // rare cases this will fallback to that.
    OGA_PRESENT_MODE_IMMEDIATE,
    // Present() will submit the image to the queue, resetting the oldest pending image
    //  if queue is full, and will NOT halt the thread. This won't cause tearing, but will
    //  discard some submitted frames if submitted at a higher rate than vertical blank rate.
    // Check device feature flag OGA_DEVICE_FEATURE_PRESENT_MAILBOX
    OGA_PRESENT_MODE_VSYNC_MAILBOX 
} Oga_Present_Mode;

typedef struct Oga_Swapchain_Desc {
    Surface_Handle surface;
    u64 requested_image_count;
    Oga_Format image_format;
    u64 width;
    u64 height;
    Oga_Present_Mode present_mode;
    u64 graphics_engine_family_index; // Swapchain needs a graphics engine
    
} Oga_Swapchain_Desc;



#define MAX_SWAPCHAIN_IMAGES 16

struct Oga_Render_Image_View;
typedef struct Oga_Swapchain {
    void *id;
    Oga_Context *context;
    struct Oga_Render_Image_View *images[MAX_SWAPCHAIN_IMAGES];
    u64 current_image_index;
    u64 image_count;
    Oga_Format image_format;
} Oga_Swapchain;

bool get_preferred_swapchain_format(Oga_Context *context, Oga_Format *wanted_formats, u64 count, Oga_Format *format);

Oga_Result oga_init_swapchain(Oga_Context *context, Oga_Swapchain_Desc desc, Oga_Swapchain **swapchain);
void oga_uninit_swapchain(Oga_Swapchain *swapchain);

struct Oga_Gpu_Latch;
struct Oga_Cpu_Latch;
Oga_Result oga_get_next_swapchain_image(Oga_Swapchain *swapchain, u64 timeout, struct Oga_Gpu_Latch *signal_gpu_latch, struct Oga_Cpu_Latch *signal_cpu_latch, u64 *image_index); 

typedef struct Oga_Present_Desc {
    Oga_Logical_Engine engine;
    u64 wait_gpu_latch_count;
    struct Oga_Gpu_Latch **wait_gpu_latches;
    u64 image_index;
} Oga_Present_Desc;
Oga_Result oga_submit_present(Oga_Swapchain *swapchain, Oga_Present_Desc desc);

//////////
/// GPU Programs

typedef enum Oga_Program_Kind {
    OGA_PROGRAM_VERTEX,
    OGA_PROGRAM_FRAGMENT,
    OGA_PROGRAM_COMPUTE,
} Oga_Program_Kind;

typedef struct Oga_Program_Desc {
    const void *code; // Compiled code ready to send to drivers
    u64 code_size;
    Oga_Program_Kind kind;
} Oga_Program_Desc;

typedef struct Oga_Program {
    void *id;
    Oga_Context *context;
    Oga_Program_Kind kind;
} Oga_Program;

// Goes through OSL to compile osl lang to target drivers
// Oga_Result oga_compile_program_for_target

Oga_Result oga_init_program(Oga_Context *context, Oga_Program_Desc desc, Oga_Program **program);
void oga_uninit_program(Oga_Program *program);

//////////
/// Render Passes

typedef enum Oga_Program_Stage_Flag_ {
    OGA_PROGRAM_STAGE_VERTEX = 1 << 1,
    OGA_PROGRAM_STAGE_FRAGMENT = 1 << 2,
    OGA_PROGRAM_STAGE_COMPUTE = 1 << 3,
} Oga_Program_Stage_Flag_;
typedef u64 Oga_Program_Stage_Flag;

typedef enum Oga_Sampling_Filter {
    OGA_SAMPLE_FILTER_LINEAR,
    OGA_SAMPLE_FILTER_NEAREST,
} Oga_Sampling_Filter;
typedef enum Oga_Sampling_Address_Mode {
    OGA_SAMPLE_ADDRESS_MODE_REPEAT,
    OGA_SAMPLE_ADDRESS_MODE_MIRRORED_REPEAT,
    OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_EDGE,
    OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_BORDER,
} Oga_Sampling_Address_Mode;
typedef struct Oga_Sample_Mode_Desc {
    Oga_Sampling_Filter magnification_filter;
    Oga_Sampling_Filter minification_filter;
    Oga_Sampling_Address_Mode address_mode_u;
    Oga_Sampling_Address_Mode address_mode_v;
    Oga_Sampling_Address_Mode address_mode_w;
    float max_anisotropy;
} Oga_Sample_Mode_Desc;

typedef enum Oga_Binding_Kind {
    OGA_BINDING_IMAGE,
    OGA_BINDING_SAMPLE_MODE,
    OGA_BINDING_BLOCK,
    OGA_BINDING_FBUFFER,
    
    OGA_BINDING_ENUM_MAX
} Oga_Binding_Kind;
typedef struct Oga_Binding_Layout_Entry_Desc {
    Oga_Binding_Kind kind;
    u64 binding_slot;
    u64 binding_count; // Number of elements in this binding. If > 1, the program declaration should be an array
    Oga_Program_Stage_Flag stage_flags;
} Oga_Binding_Layout_Entry_Desc;
typedef struct Oga_Binding_List_Layout_Desc {
    Oga_Binding_Layout_Entry_Desc *bindings;
    u64 binding_count;
    u64 binding_list_count;
} Oga_Binding_List_Layout_Desc;

typedef struct Oga_Binding_List_Layout {
    void *id;
    Oga_Context *context;
    Oga_Binding_Layout_Entry_Desc *bindings;
    u64 binding_count;
    u64 binding_list_count;
    u64 allocated_lists_count;
} Oga_Binding_List_Layout;

Oga_Result oga_init_binding_list_layout(Oga_Context *context, Oga_Binding_List_Layout_Desc desc, Oga_Binding_List_Layout **layout);
void oga_uninit_binding_list_layout(Oga_Binding_List_Layout *layout);

struct Oga_Image_View;
struct Oga_Block_View;
typedef struct Oga_Binding_Desc {
    Oga_Binding_Kind kind;
    u64 binding_slot;
    u64 array_index;
    u64 count;
    
    // OGA_BINDING_IMAGE
    struct Oga_Image_View **images;
    
    // OGA_BINDING_SAMPLE_MODE
    Oga_Sample_Mode_Desc *sample_modes;
    
    // OGA_BINDING_BLOCK
    struct Oga_Block_View **blocks;
    
    // OGA_BINDING_FBUFFER
    struct Oga_FBuffer_View **fbuffers;
    
} Oga_Binding_Desc;
typedef struct Oga_Binding_List_Desc {
    Oga_Binding_Desc *bindings;
    u64 binding_count;
} Oga_Binding_List_Desc;

typedef struct Oga_Binding_List {
    void *id;
    Oga_Context *context;
    Oga_Binding_List_Layout *layout;
} Oga_Binding_List;

Oga_Result oga_push_binding_list(Oga_Binding_List_Layout *layout, Oga_Binding_List_Desc desc, Oga_Binding_List **list);

// I looked through various devices and they all report these numbers
// Including RTX 5090 as well as GT 710 (vulkan)
#define OGA_MAX_VERTEX_BINDING_COUNT 32
#define OGA_MAX_VERTEX_ATTRIBUTE_COUNT 32
#define MAX_VERTEX_ATTRIBUTE_OFFSET 2047
#define MAX_VERTEX_BINDING_OFFSET 2048

typedef enum Oga_Vertex_List_Input_Rate {
    OGA_VERTEX_INPUT_RATE_VERTEX,
    OGA_VERTEX_INPUT_RATE_INSTANCE,
} Oga_Vertex_List_Input_Rate;

typedef enum Oga_Vertex_Attribute_Type {
    OGA_VERTEX_ATTRIBUTE_TYPE_F32,
    OGA_VERTEX_ATTRIBUTE_TYPE_F32V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_F32V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_F32V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_S32,
    OGA_VERTEX_ATTRIBUTE_TYPE_S32V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_S32V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_S32V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_S16,
    OGA_VERTEX_ATTRIBUTE_TYPE_S16V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_S16V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_S16V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_S8,
    OGA_VERTEX_ATTRIBUTE_TYPE_S8V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_S8V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_S8V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_U32,
    OGA_VERTEX_ATTRIBUTE_TYPE_U32V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_U32V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_U32V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_U16,
    OGA_VERTEX_ATTRIBUTE_TYPE_U16V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_U16V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_U16V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8_NORMALIZED,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V2_NORMALIZED,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V3_NORMALIZED,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V4_NORMALIZED,
} Oga_Vertex_Attribute_Type;

/*
    We often only need one vertex list in one binding slot:
    
    Oga_Vertex_List_Layout_Desc desc = (Oga_Vertex_List_Layout_Desc) {0};
    desc.bindings[0].stride = sizeof(float4)+sizeof(float3);
    desc.bindings[0].input_rate = OGA_VERTEX_INPUT_RATE_VERTEX;
    desc.binding_count = 1;
    
    desc.attributes[desc.attribute_count].binding = 0;
    desc.attributes[desc.attribute_count].location = 0;
    desc.attributes[desc.attribute_count].offset = 0;
    desc.attributes[desc.attribute_count].type = OGA_VERTEX_ATTRIBUTE_TYPE_F32V4;
    desc.attribute_count += 1;
    
    desc.attributes[desc.attribute_count].binding = 0;
    desc.attributes[desc.attribute_count].location = 1;
    desc.attributes[desc.attribute_count].offset = sizeof(float4);
    desc.attributes[desc.attribute_count].type = OGA_VERTEX_ATTRIBUTE_TYPE_F32V3;
    desc.attribute_count += 1;
*/
typedef struct Oga_Vertex_List_Binding_Desc {
    
    u64 stride; // The stride between the start of each vertex in the vertex list in this binding slot
    Oga_Vertex_List_Input_Rate input_rate; // Input is per vertex or per instance
    
} Oga_Vertex_List_Binding_Desc;
typedef struct Oga_Vertex_List_Attribute_Desc {
    
    u64 binding; // The attribute points to the vertex list in this binding slot
    u64 location; // The attribute is bound to this location in the program input
    u64 offset; 
    Oga_Vertex_Attribute_Type type;
    
} Oga_Vertex_List_Attribute_Desc;
typedef struct Oga_Vertex_List_Layout_Desc {
    
    Oga_Vertex_List_Binding_Desc bindings[OGA_MAX_VERTEX_BINDING_COUNT]; // Vertex list binding slots
    u64 binding_count;
    Oga_Vertex_List_Attribute_Desc attributes[OGA_MAX_VERTEX_ATTRIBUTE_COUNT];
    u64 attribute_count;
    
} Oga_Vertex_List_Layout_Desc;

typedef u64 Oga_Render_Pass_Flag;
unit_local const Oga_Render_Pass_Flag OGA_RENDER_PASS_INHERITANCE_PARENT = 1 << 0;
unit_local const Oga_Render_Pass_Flag OGA_RENDER_PASS_INHERITANCE_CHILD = 1 << 1;
unit_local const Oga_Render_Pass_Flag OGA_RENDER_PASS_DISABLE_DEPTH_CLAMP = 1 << 2;

// #Volatile values must map to same as vulkan equivalents
typedef enum Oga_Primitive_Topology {
    OGA_PRIMITIVE_TOPOLOGY_POINT_LIST = 0,
    OGA_PRIMITIVE_TOPOLOGY_LINE_LIST = 1,
    OGA_PRIMITIVE_TOPOLOGY_LINE_STRIP = 2,
    OGA_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 3,
    OGA_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = 4
} Oga_Primitive_Topology;

typedef enum Oga_Cull_Mode {
    OGA_CULL_NONE,
    OGA_CULL_CLOCKWISE,
    OGA_CULL_COUNTER_CLOCKWISE,
} Oga_Cull_Mode;

struct Oga_Render_Pass;
typedef struct Oga_Render_Pass_Desc {
    
    Oga_Render_Pass_Flag flags;
    struct Oga_Render_Pass *base;
    u64 base_index; // Index into buffer of descs passed. Only used if base is null.
    
    Oga_Program *vertex_program;
    string vertex_program_entry_point;
    Oga_Program *fragment_program;
    string fragment_program_entry_point;
    
    Oga_Format *attachment_formats;
    u64 attachment_count;
    
    Oga_Primitive_Topology topology;
    
    Oga_Cull_Mode cull_mode;
    
    float32 line_width;
    
    // See Oga_Device::limits.supported_sample_counts_render_pass
    Oga_Sample_Count_Flag rasterization_samples;
    
    Oga_Vertex_List_Layout_Desc vertex_input_layout;
    
    Oga_Binding_List_Layout *binding_list_layout;
    
} Oga_Render_Pass_Desc;

typedef struct Oga_Render_Pass {
    void *id;
    Oga_Context *context;
    Oga_Vertex_List_Layout_Desc vertex_input_layout;
} Oga_Render_Pass;

Oga_Result oga_init_render_passes(Oga_Context *context, Oga_Render_Pass_Desc* descs, Oga_Render_Pass **render_passes, u64 render_pass_count);

Oga_Result oga_init_render_pass(Oga_Context *context, Oga_Render_Pass_Desc desc, Oga_Render_Pass **render_pass);
void oga_uninit_render_pass(Oga_Render_Pass *render_pass);

//////////
/// Synchronization

// Gpu latch; for synchronizing on gpu. Signalled on gpu, waited on gpu.
typedef struct Oga_Gpu_Latch {
    void *id;
    Oga_Context *context;
} Oga_Gpu_Latch;

Oga_Result oga_init_gpu_latch(Oga_Context *context, Oga_Gpu_Latch **gpu_latch);
void oga_uninit_gpu_latch(Oga_Gpu_Latch *gpu_latch);

// Cpu latch; for synchronizing cpu with gpu. Signalled on gpu, waited on cpu.
typedef struct Oga_Cpu_Latch {
    void *id;
    Oga_Context *context;
} Oga_Cpu_Latch;
Oga_Result oga_init_cpu_latch(Oga_Context *context, Oga_Cpu_Latch **cpu_latch, bool start_signaled);
void oga_uninit_cpu_latch(Oga_Cpu_Latch *cpu_latch);
Oga_Result oga_wait_latch(Oga_Cpu_Latch *cpu_latch);
Oga_Result oga_reset_latch(Oga_Cpu_Latch *cpu_latch);

//////////
/// Memory & Views

#define OGA_INTERNALLY_MANAGED_MEMORY_HANDLE ((Oga_Memory_Pointer) { (void*)U64_MAX, (Oga_Context*) U64_MAX, U64_MAX, U64_MAX, U64_MAX, U64_MAX, U64_MAX })
typedef struct Oga_Memory_Pointer {
    void *id;
    Oga_Context *context;
    u64 offset;
    u64 size;
    u64 heap_index;
    Oga_Memory_Property_Flag properties;
    Oga_Memory_Usage usage;
    
#ifdef OGA_DEBUG
    // todo(charlie) #validation Track view regions
#endif 
} Oga_Memory_Pointer;

Oga_Result oga_allocate_memory(Oga_Context *context, u64 size, Oga_Memory_Property_Flag properties, Oga_Memory_Usage usage, Oga_Memory_Pointer *ptr);
void oga_deallocate_memory(Oga_Memory_Pointer ptr);
Oga_Result oga_map_memory(Oga_Memory_Pointer ptr, u64 size, void **mapped_mem);
void oga_unmap_memory(Oga_Memory_Pointer ptr);
Oga_Result oga_memory_offset(Oga_Memory_Pointer ptr, s64 offset, Oga_Memory_Pointer *result_ptr);


typedef struct Oga_Memory_View_Desc  {
    Oga_Memory_Pointer memory_pointer;
    u64 size;
} Oga_Memory_View_Desc;

// These are the same (as of now) but we have a compiler and a statically typechecked programming language,
// which we should use.
typedef struct Oga_Vertex_List_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 size;
} Oga_Vertex_List_View;
typedef struct Oga_Index_List_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 size;
} Oga_Index_List_View;

Oga_Result oga_init_vertex_list_view(Oga_Context *context, Oga_Memory_View_Desc desc, Oga_Vertex_List_View **vlist);
void oga_uninit_vertex_list_view(Oga_Vertex_List_View *vlist);

Oga_Result oga_init_index_list_view(Oga_Context *context, Oga_Memory_View_Desc desc, Oga_Index_List_View **ilist);
void oga_uninit_index_list_view(Oga_Index_List_View *ilist);

/// Image view

typedef enum Oga_Dimensions {
    OGA_1D,
    OGA_2D,
    OGA_3D,
} Oga_Dimensions;

typedef struct Oga_Image_View_Desc {
    Oga_Memory_Pointer memory_pointer;
    Oga_Format format;
    Oga_Dimensions dimensions;
    u64 width, height, depth;
    bool linear_tiling;
    u64 graphics_engine_family_index;
    
} Oga_Image_View_Desc;

typedef struct Oga_Image_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 width, height, depth;
    Oga_Dimensions dimensions;
    bool linear_tiling;
} Oga_Image_View;

Oga_Result oga_init_image_view(Oga_Context *context, Oga_Image_View_Desc desc, Oga_Image_View **image);
void oga_uninit_image_view(Oga_Image_View *image);

u64 oga_get_image_memory_requirement(Oga_Context *context, Oga_Image_View_Desc desc);

typedef struct Oga_FBuffer_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 width, height, depth;
    Oga_Dimensions dimensions;
    bool linear_tiling;
} Oga_FBuffer_View;

Oga_Result oga_init_fbuffer_view(Oga_Context *context, Oga_Image_View_Desc desc, Oga_FBuffer_View **fbuffer);
void oga_uninit_fbuffer_view(Oga_FBuffer_View *fbuffer);

/// Image copy target view

typedef enum Oga_Optimal_Copy_Flag_ {
    OGA_OPTIMAL_COPY_DST = 1 << 1,
    OGA_OPTIMAL_COPY_SRC = 1 << 2,
} Oga_Optimal_Copy_Flag_;
typedef u64 Oga_Optimal_Copy_Flag;

typedef struct Oga_Optimal_Copy_View_Desc {
    Oga_Memory_Pointer memory_pointer;
    Oga_Format format;
    Oga_Dimensions dimensions;
    u64 width, height, depth;
    bool linear_tiling;
    u64 graphics_engine_family_index;
    Oga_Optimal_Copy_Flag flags;
} Oga_Optimal_Copy_View_Desc;

typedef struct Oga_Optimal_Copy_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 width, height, depth;
    Oga_Dimensions dimensions;
    bool linear_tiling;
    Oga_Optimal_Copy_Flag flags;
} Oga_Optimal_Copy_View;

Oga_Result oga_init_optimal_copy_view(Oga_Context *context, Oga_Optimal_Copy_View_Desc desc, Oga_Optimal_Copy_View **image);
void oga_uninit_optimal_copy_view(Oga_Optimal_Copy_View *image);

typedef struct Oga_Render_Image_View_Desc {
    Oga_Memory_Pointer memory_pointer;
    Oga_Format format;
    u64 width, height;    
} Oga_Render_Image_View_Desc;

typedef struct Oga_Render_Image_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 width, height;
} Oga_Render_Image_View;

// todo(charlie)
// Oga_Result oga_init_render_image_view(Oga_Context *context, Oga_Render_Image_View_Desc desc, Oga_Render_Image_View **view);
// void oga_uninit_render_image_view(Oga_Render_Image_View *view);
//
// u64 oga_get_render_image_memory_requirement(Oga_Context *context, Oga_Render_Image_View_Desc desc);



/// Read buffer view

typedef struct Oga_Block_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 size;
} Oga_Block_View;
Oga_Result oga_init_block_view(Oga_Context *context, Oga_Memory_View_Desc desc, Oga_Block_View **buffer);
void oga_uninit_block_view(Oga_Block_View *buffer);

// todo(charlie) #validation
// Keep track of all init()'s and report them here if they were not uninitted
// This is really only here to get validation/debug layer messages for leaked resources
void oga_reset(void);


//////////
/// Commands

typedef u64 Oga_Command_Pool_Flag;
#define  OGA_COMMAND_POOL_NONE 0
#define  OGA_COMMAND_POOL_SHORT_LIVED_ALLOCATIONS (1 << 0)

typedef struct Oga_Command_Pool_Desc {
    Oga_Command_Pool_Flag flags;
    u64 engine_family_index; // Pinky promise which queue family this will be submitted to
} Oga_Command_Pool_Desc;

typedef struct Oga_Command_Pool {
    void *id;
    Oga_Context *context;
} Oga_Command_Pool;

typedef struct Oga_Command_List {
    void *id;
    Oga_Command_Pool *pool;
    
#ifdef OGA_DEBUG
    // todo(charlie) #validation track all submitted commands and validate
    //  - Vertex lists bound when cmd_draw in a render pass which specified vertex list bindings
    //  - Index list is bound when cmd_draw indexed
    //  - Formatted blocks are in the correct layout state for the operations they will be used in
#endif
} Oga_Command_List;

Oga_Result oga_init_command_pool(Oga_Context *context, Oga_Command_Pool_Desc desc, Oga_Command_Pool **pool);
 // This will free all command lists, so you do not need to explicitly free each command list.
void oga_uninit_command_pool(Oga_Command_Pool *pool);
void oga_reset_command_pool(Oga_Command_Pool *pool);

Oga_Result oga_get_command_lists(Oga_Command_Pool *pool, Oga_Command_List *lists, u64 list_count);
void oga_release_command_lists(Oga_Command_List *lists, u64 list_count);



typedef u64 Oga_Command_List_Usage_Flag;
#define OGA_COMMAND_LIST_USAGE_ONE_TIME_SUBMIT (1 << 0)

Oga_Result oga_cmd_begin(Oga_Command_List cmd, Oga_Command_List_Usage_Flag flags);
Oga_Result oga_cmd_end(Oga_Command_List cmd);

typedef struct Oga_Submit_Command_List_Desc {
    Oga_Logical_Engine engine; 
    Oga_Gpu_Latch **wait_gpu_latches; 
    u64 wait_gpu_latch_count; 
    Oga_Gpu_Latch **signal_gpu_latches; 
    u64 signal_gpu_latch_count; 
    Oga_Cpu_Latch *signal_cpu_latch;
} Oga_Submit_Command_List_Desc;
Oga_Result oga_submit_command_list(Oga_Command_List cmd, Oga_Submit_Command_List_Desc desc);

typedef struct Oga_Gpu_Timestamp_Pool {
    void *id;
    Oga_Context *context;
    u64 timestamp_count;
    u64 written_timestamp_count;
} Oga_Gpu_Timestamp_Pool;

Oga_Result oga_init_gpu_timestamp_pool(Oga_Context *context, u64 timestamp_count, Oga_Gpu_Timestamp_Pool **pool);
void oga_uninit_gpu_timestamp_pool(Oga_Gpu_Timestamp_Pool *pool);

void oga_cmd_reset_timestamp_pool(Oga_Command_List cmd, Oga_Gpu_Timestamp_Pool *pool);
void oga_cmd_write_timestamp(Oga_Command_List cmd, Oga_Gpu_Timestamp_Pool *pool);

Oga_Result oga_read_timestamps(Oga_Gpu_Timestamp_Pool *pool, f64 *nanosecond_timestamps, bool wait);

typedef u64 Oga_Msaa_Resolve_Mode_Flag;
#define OGA_MSAA_RESOLVE_MODE_NONE    0
#define OGA_MSAA_RESOLVE_MODE_ZERO    (1 << 0)
#define OGA_MSAA_RESOLVE_MODE_AVERAGE (1 << 1)
#define OGA_MSAA_RESOLVE_MODE_MIN     (1 << 2)
#define OGA_MSAA_RESOLVE_MODE_MAX     (1 << 3)

typedef enum Oga_Attachment_Load_Op {
    OGA_ATTACHMENT_LOAD_OP_LOAD,
    OGA_ATTACHMENT_LOAD_OP_CLEAR,
    OGA_ATTACHMENT_LOAD_OP_NOTHING
} Oga_Attachment_Load_Op;
typedef enum Oga_Attachment_Store_Op {
    OGA_ATTACHMENT_STORE_OP_STORE,
    OGA_ATTACHMENT_STORE_OP_NOTHING
} Oga_Attachment_Store_Op;

typedef struct Oga_Render_Attachment_Desc {
    Oga_Render_Image_View *image;
    
    // If rendering with multisampling, we can resolve the multiple samples into single samples
    // on another image.
    Oga_Msaa_Resolve_Mode_Flag resolve_mode;
    const Oga_Image_View *resolve_image;
    
    Oga_Attachment_Load_Op load_op;
    Oga_Attachment_Store_Op store_op;
    
    float32 clear_color[4]; // In case of load_op CLEAR
    
} Oga_Render_Attachment_Desc;

typedef struct Oga_Begin_Render_Pass_Desc {
    s64 render_area_offset_x;
    s64 render_area_offset_y;
    u64 render_area_width;
    u64 render_area_height;
    u64 attachment_count;
    Oga_Render_Attachment_Desc *attachments;
} Oga_Begin_Render_Pass_Desc;

void oga_cmd_begin_render_pass(Oga_Command_List cmd, Oga_Render_Pass *render_pass, Oga_Begin_Render_Pass_Desc desc);
void oga_cmd_end_render_pass(Oga_Command_List cmd, Oga_Render_Pass *render_pass);

void oga_cmd_bind_render_pass_binding_list(Oga_Command_List cmd, Oga_Render_Pass *pass, Oga_Binding_List *list);

typedef enum Oga_Draw_Type {
    OGA_DRAW_INSTANCED,
    OGA_DRAW_VERTEX_LIST,
    OGA_DRAW_VERTEX_LIST_INSTANCED,
    OGA_DRAW_VERTEX_LIST_INDEXED,
    OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED,
    
    OGA_DRAW_INSTANCED_INDIRECT,
    OGA_DRAW_VERTEX_LIST_INDIRECT,
    OGA_DRAW_VERTEX_LIST_INSTANCED_INDIRECT,
    OGA_DRAW_VERTEX_LIST_INDEXED_INDIRECT,
    OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED_INDIRECT,
} Oga_Draw_Type;
typedef enum Oga_Index_Type {
    OGA_INDEX_U32,
    OGA_INDEX_U16,
} Oga_Index_Type;
typedef struct Oga_Draw_Desc {
    
    Oga_Draw_Type draw_type;
    
    // All
    u64 vertex_start; // The first vertex to draw. For vertex lists, this is an offset from the BASE vertex at the binding point
    u64 vertex_count;
    
    // Vertex list
    Oga_Vertex_List_View *vertex_list_bindings[OGA_MAX_VERTEX_BINDING_COUNT];
    u64 vertex_list_offsets[OGA_MAX_VERTEX_BINDING_COUNT]; // Offset to the BASE vertex to be bound
    u64 vertex_list_binding_count;
    
    // Instanced
    u64 instance_start;
    u64 instance_count;
    
    // Indexed
    u64 index_start;
    u64 index_count;
    Oga_Index_List_View *index_list;
    u64 index_list_offset;
    Oga_Index_Type index_type;
    
    // Indirect
    // Indirect_Block *indirect_block;
    
} Oga_Draw_Desc;

Oga_Result oga_cmd_draw(Oga_Command_List cmd, Oga_Draw_Desc desc);

void oga_cmd_copy_linear(Oga_Command_List cmd, Oga_Memory_Pointer dst, Oga_Memory_Pointer src, u64 size);

typedef struct Oga_Optimal_Copy_Desc {
    s64 offset_x, offset_y, offset_z;
    u64 width, height, depth;
} Oga_Optimal_Copy_Desc;
void oga_cmd_copy_linear_to_image(Oga_Command_List cmd, Oga_Optimal_Copy_View *dst_view, Oga_Optimal_Copy_Desc dst_desc, Oga_Memory_Pointer src);
void oga_cmd_copy_image_to_linear(Oga_Command_List cmd, Oga_Memory_Pointer dst, Oga_Optimal_Copy_View *src_view, Oga_Optimal_Copy_Desc src_desc);
void oga_cmd_copy_image(Oga_Command_List cmd, Oga_Optimal_Copy_View *dst_view, Oga_Optimal_Copy_Desc dst_desc, Oga_Optimal_Copy_View *src_view, Oga_Optimal_Copy_Desc src_desc);

void oga_cmd_fill_image(Oga_Command_List cmd, Oga_Optimal_Copy_View *dst_view, float4 color);

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
#endif // OGA_IMPL_AUTO

#if !defined(OGA_IMPL_WEBGPU) && !defined(OGA_IMPL_D3D12) && !defined(OGA_IMPL_METAL) && !defined(OGA_IMPL_VULKAN)

    #define OGA_NO_IMPL

#endif

#if defined(OSTD_IMPL)

void* oga_state_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags) {
    (void)flags;
    (void)old_n;
    Oga_State_Allocator_Data *a = (Oga_State_Allocator_Data*)data;

    if (alignment == 0)
        alignment = 8;
    
    System_Info info = sys_get_info();
    
    switch (msg) {
        case ALLOCATOR_ALLOCATE:
        {
            if (n > 4096) {
                // Just directly map pages for big allocations. This should be rare, or probably never happen.
                void *p = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, (n+info.page_size)/info.page_size, false);
                assert(p);
                assert((u64)p % info.page_size == 0);
                assertmsgs((u64)p % alignment == 0, tprint("Expected alignment of %i, view is %u", alignment, p));
                return p;
            }
            Oga_Allocator_Row *row = 0;
            u64 stride = 0;
            for (u64 i = 0; i < 11; i += 1) {
                u64 row_stride = powu(2, i+4);
                if (n <= row_stride) {
                    stride = row_stride;
                    row = &a->rows[i];
                    break;
                }
            }
            
            assert(row);
            
            if (!row->start) {
                // todo(charlie) #Portability
                // Need to find a portable free address space, or provide a way to query for such.

                void *reserved = sys_map_pages(SYS_MEMORY_RESERVE, 0, (1024*1024*1024)/info.page_size, false);
                assert(reserved);
                
                u64 initial_row_size = max(info.granularity, 1024*32);
                row->start = sys_map_pages(SYS_MEMORY_ALLOCATE, reserved, initial_row_size/info.page_size, true);
                
                if (!row->start) return 0;
                
                // Round to page size (actual allocated size)
                row->end = (u8*)row->start + (initial_row_size/info.page_size)*info.page_size;
                
                row->first_free_index = 0;
                row->highest_allocated_index = 0;
            }
            
            
            void *next = (u8*)row->start + row->first_free_index*stride;
            u64 allocated_index = ((u64)next-(u64)row->start)/stride;
            
            assert(row->first_free_index <= ((u64)row->end-(u64)row->start)/stride);
            
            if ((u8*)next == (u8*)row->end) {
                u64 old_size = (u64)row->end - (u64)row->start;
                u64 new_size = (((old_size*2)+info.page_size)/info.page_size)*info.page_size;
                
                void *expansion = sys_map_pages(SYS_MEMORY_ALLOCATE, row->end, new_size/info.page_size, true);
#if OS_FLAGS & OS_FLAG_WINDOWS
                assert(expansion);
#endif
                if (!expansion) {  
                    // todo(charlie) #Portability #Memory #Speed
                    // If target system has poor mapping features, we might hit this often, which is kind of crazy.
                    void *p = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, (n+info.page_size)/info.page_size, false);
                    assert((u64)p % alignment == 0);
                    return p;
                }
                
                assert(expansion == row->end);
                row->end = (u8*)row->start + new_size;
            } else {
                assertmsgs((u64)next < (u64)row->end, tprint("%u, %u", next, row->end));
            }
            
            if (allocated_index >= row->highest_allocated_index) {
                row->first_free_index = allocated_index+1;
            } else {
                // When we free a block, we store the index to the next free block
                row->first_free_index = *(u64*)next;
            }
            
            assert(row->first_free_index <= ((u64)row->end-(u64)row->start)/stride);            assertmsgs((u64)((u8*)row->start + row->first_free_index*stride) <= (u64)row->end, tprint("%u, %u", next, row->end));
            
            row->highest_allocated_index = max(row->highest_allocated_index, allocated_index);
            
            assert(row->first_free_index <= row->highest_allocated_index+1);
            
            assert((u64)next % alignment == 0);
            
            return next;
        }
        case ALLOCATOR_REALLOCATE:
        {
            if (n == 0) {
                oga_state_allocator_proc(ALLOCATOR_FREE, 0, old, 0, 0, alignment, flags);
                return 0;
            }
            void * pnew = oga_state_allocator_proc(ALLOCATOR_ALLOCATE, data, 0, 0, n, alignment, flags);
            if (old) {
                memcpy(pnew, old, min(n, old_n));
                oga_state_allocator_proc(ALLOCATOR_FREE, 0, old, 0, 0, alignment, flags);
            }
            return pnew;
        }
        case ALLOCATOR_FREE:
        {
            if (!old) return 0;
            
            Oga_Allocator_Row *row = 0;
            u64 stride = 16;
            for (u64 i = 0; i < 11; i += 1) {
                if ((u64)old >= (u64)a->rows[i].start && (u64)old < (u64)a->rows[i].end) {
                    row = &a->rows[i];
                    u64 exp = powu(2, i+4);
                    assertmsgs(stride == exp, tprint("%u, %u", stride, exp));
                    break;
                }
                stride *= 2;
            }
            
            
            if (!row) {
                sys_unmap_pages(old);
                return 0;
            }
            
            u64 offset = (u64)old - (u64)row->start;
            assert(offset % stride == 0);
            u64 index = offset/stride;
            
            // Use old memory to store index to the next free block
            *(u64*)old = row->first_free_index;
            row->first_free_index = index;
            
            assert(row->first_free_index <= ((u64)row->end-(u64)row->start)/stride);
            assert((u64)((u8*)row->start + row->first_free_index*stride) <= (u64)row->end);
            assert(row->first_free_index <= row->highest_allocated_index+1);
            
            break;
        }

        default:
        {
            break;
        }
    }

    return 0;
}

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
            
        *pscore += device.engine_family_count*10;
        
        // Whatever these drivers are, they cause a LOT of trouble.
        string device_name = (string) {device.device_name_length, device.device_name_data};
        if (string_contains(device_name, STR("Microsoft")) || string_contains(device_name, STR("Direct3D12"))) {
            *pscore -= 500;
        }
          
        u64 preferred_features_count = 0;

#ifdef __clang__
        // clang loop vectorization shits its pants here when -mavx -mavx2, so just disable it.
        // It completely messes up the branches, basically always doing continue here for some reason.
        // todo(charlie) try gcc and see if same thing happens
        #pragma clang loop vectorize(disable)
#endif // __clang__
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

bool get_preferred_swapchain_format(Oga_Context *context, Oga_Format *wanted_formats, u64 count, Oga_Format *format) {
    for (u64 i = 0; i < count; i += 1) {
        for (u64 j = 0; j < context->device.supported_surface_format_count; j += 1) {
            Oga_Format f = context->device.supported_surface_formats[j];
            if (f == wanted_formats[i]) {
                *format = f;
                return true;
            }
        }
    }
    
    return false;
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

inline string oga_format_str(Oga_Format f);

#ifdef OGA_IMPL_VULKAN

/////////////////////////////////////////////////////
//////
// :Vulkan
//////
/////////////////////////////////////////////////////

#define OGA_OSL_TARGET OSL_TARGET_SPIRV_VULKAN

#if COMPILER_FLAGS & COMPILER_FLAG_MSC
    #pragma comment(lib, "vendors/vulkan-1.lib")
#endif // COMPILER_FLAGS & COMPILER_FLAG_MSC

#if (OS_FLAGS & (OS_FLAG_WINDOWS | OS_FLAG_LINUX | OS_FLAG_MACOS | OS_FLAG_IOS | OS_FLAG_ANDROID)) == 0
    #error Vulkan is not supported on target platform
#else

/* Begin include: graphics_vulkan.h */

#define uint8_t u8
#define int8_t  s8
#define uint16_t u16
#define int16_t  s16
#define uint32_t u32
#define int32_t  s32
#define uint64_t u64
#define int64_t  s64

#define VK_NO_STDDEF_H
#define VK_NO_STDINT_H
// noconcat
#include <vulkan/vulkan.h>


// We manually include the vulkan-specific headers, otherwise vulkan.h will include windows.h
#if OS_FLAGS & OS_FLAG_WINDOWS
// noconcat
#include <vulkan/vulkan_win32.h>
#elif OS_FLAGS & OS_FLAG_LINUX
// noconcat
#include <vulkan/vulkan_xlib.h>
#elif OS_FLAGS & OS_FLAG_MACOS
// noconcat
#include <vulkan/vulkan_macos.h>
#elif OS_FLAGS & OS_FLAG_IOS
// noconcat
#include <vulkan/vulkan_ios.h>
#elif OS_FLAGS & OS_FLAG_ANDROID
// noconcat
#include <vulkan/vulkan_android.h>
#else
#error Vulkan is not supported on target platform
#endif


#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#endif // __clang__

typedef struct _Vk_Memory_State {
    VkDeviceMemory memory;
    u32 memory_type_index;
    VkBuffer raw_view;
    VkImage last_image_optimal_view;
    u64 last_image_optimal_offset;
} _Vk_Memory_State;

typedef struct _Vk_Image_State {
    VkImage image;
    VkImageView view;
} _Vk_Image_State;
typedef struct _Vk_Render_Image_State {
    VkImage image;
    VkImageView view;
} _Vk_Render_Image_State;

typedef struct _Vk_Binding_List_Layout_State {
    VkDescriptorPool pool;
    VkDescriptorSetLayout layout;
} _Vk_Binding_List_Layout_State;

typedef struct _Vk_Swapchain_State {
    VkSwapchainKHR vk_swapchain;
    VkSurfaceKHR vk_surface;
} _Vk_Swapchain_State;

typedef struct _Vk_Render_Pass_State {
    VkPipeline pipeline;
    VkPipelineLayout layout;
    u64 active_image_count;
    VkImage active_images[128];
    VkImage active_resolve_images[128];
} _Vk_Render_Pass_State;

typedef struct _Vk_Context_Internal {
    u32 vk_version_major;
    u32 vk_version_minor;
    u32 vk_version_patch;
    bool dynamic_rendering;
    bool dynamic_rendering_is_extension;
    
    PFN_vkCmdBeginRenderingKHR vkCmdBeginRenderingKHR;
    PFN_vkCmdEndRenderingKHR vkCmdEndRenderingKHR;
    
    VkAllocationCallbacks vk_allocs;
} _Vk_Context_Internal;

typedef struct _Vk_Memory_Block {
    VkDeviceMemory memory;
    VkAccessFlags access_state;
    
    VkBuffer access_buffer;
} _Vk_Memory_Block;

unit_local inline VkFormat _oga_to_vk_format(Oga_Format k) {
    switch (k) {
        case OGA_FORMAT_R4G4_UNORM_PACK8:             return VK_FORMAT_R4G4_UNORM_PACK8;
        case OGA_FORMAT_R4G4B4A4_UNORM_PACK16:         return VK_FORMAT_R4G4B4A4_UNORM_PACK16;
        case OGA_FORMAT_B4G4R4A4_UNORM_PACK16:         return VK_FORMAT_B4G4R4A4_UNORM_PACK16;
        case OGA_FORMAT_R5G6B5_UNORM_PACK16:           return VK_FORMAT_R5G6B5_UNORM_PACK16;
        case OGA_FORMAT_B5G6R5_UNORM_PACK16:           return VK_FORMAT_B5G6R5_UNORM_PACK16;
        case OGA_FORMAT_R5G5B5A1_UNORM_PACK16:         return VK_FORMAT_R5G5B5A1_UNORM_PACK16;
        case OGA_FORMAT_A1R5G5B5_UNORM_PACK16:         return VK_FORMAT_A1R5G5B5_UNORM_PACK16;

        case OGA_FORMAT_R8_UNORM:                      return VK_FORMAT_R8_UNORM;
        case OGA_FORMAT_R8_SNORM:                      return VK_FORMAT_R8_SNORM;
        case OGA_FORMAT_R8_UINT:                       return VK_FORMAT_R8_UINT;
        case OGA_FORMAT_R8_SINT:                       return VK_FORMAT_R8_SINT;
        case OGA_FORMAT_R8_SRGB:                       return VK_FORMAT_R8_SRGB;

        case OGA_FORMAT_R8G8_UNORM:                    return VK_FORMAT_R8G8_UNORM;
        case OGA_FORMAT_R8G8_SNORM:                    return VK_FORMAT_R8G8_SNORM;
        case OGA_FORMAT_R8G8_UINT:                     return VK_FORMAT_R8G8_UINT;
        case OGA_FORMAT_R8G8_SINT:                     return VK_FORMAT_R8G8_SINT;
        case OGA_FORMAT_R8G8_SRGB:                     return VK_FORMAT_R8G8_SRGB;

        case OGA_FORMAT_R8G8B8_UNORM:                  return VK_FORMAT_R8G8B8_UNORM;
        case OGA_FORMAT_R8G8B8_SNORM:                  return VK_FORMAT_R8G8B8_SNORM;
        case OGA_FORMAT_R8G8B8_UINT:                   return VK_FORMAT_R8G8B8_UINT;
        case OGA_FORMAT_R8G8B8_SINT:                   return VK_FORMAT_R8G8B8_SINT;
        case OGA_FORMAT_R8G8B8_SRGB:                   return VK_FORMAT_R8G8B8_SRGB;

        case OGA_FORMAT_R8G8B8A8_UNORM:                return VK_FORMAT_R8G8B8A8_UNORM;
        case OGA_FORMAT_R8G8B8A8_SNORM:                return VK_FORMAT_R8G8B8A8_SNORM;
        case OGA_FORMAT_R8G8B8A8_UINT:                 return VK_FORMAT_R8G8B8A8_UINT;
        case OGA_FORMAT_R8G8B8A8_SINT:                 return VK_FORMAT_R8G8B8A8_SINT;
        case OGA_FORMAT_R8G8B8A8_SRGB:                 return VK_FORMAT_R8G8B8A8_SRGB;

        case OGA_FORMAT_B8G8R8A8_UNORM:                return VK_FORMAT_B8G8R8A8_UNORM;
        case OGA_FORMAT_B8G8R8A8_SNORM:                return VK_FORMAT_B8G8R8A8_SNORM;
        case OGA_FORMAT_B8G8R8A8_UINT:                 return VK_FORMAT_B8G8R8A8_UINT;
        case OGA_FORMAT_B8G8R8A8_SINT:                 return VK_FORMAT_B8G8R8A8_SINT;
        case OGA_FORMAT_B8G8R8A8_SRGB:                 return VK_FORMAT_B8G8R8A8_SRGB;

        case OGA_FORMAT_R16_UNORM:                     return VK_FORMAT_R16_UNORM;
        case OGA_FORMAT_R16_SNORM:                     return VK_FORMAT_R16_SNORM;
        case OGA_FORMAT_R16_UINT:                      return VK_FORMAT_R16_UINT;
        case OGA_FORMAT_R16_SINT:                      return VK_FORMAT_R16_SINT;
        case OGA_FORMAT_R16_SFLOAT:                    return VK_FORMAT_R16_SFLOAT;

        case OGA_FORMAT_R16G16_UNORM:                  return VK_FORMAT_R16G16_UNORM;
        case OGA_FORMAT_R16G16_SNORM:                  return VK_FORMAT_R16G16_SNORM;
        case OGA_FORMAT_R16G16_UINT:                   return VK_FORMAT_R16G16_UINT;
        case OGA_FORMAT_R16G16_SINT:                   return VK_FORMAT_R16G16_SINT;
        case OGA_FORMAT_R16G16_SFLOAT:                 return VK_FORMAT_R16G16_SFLOAT;

        case OGA_FORMAT_R16G16B16A16_UNORM:            return VK_FORMAT_R16G16B16A16_UNORM;
        case OGA_FORMAT_R16G16B16A16_SNORM:            return VK_FORMAT_R16G16B16A16_SNORM;
        case OGA_FORMAT_R16G16B16A16_UINT:             return VK_FORMAT_R16G16B16A16_UINT;
        case OGA_FORMAT_R16G16B16A16_SINT:             return VK_FORMAT_R16G16B16A16_SINT;
        case OGA_FORMAT_R16G16B16A16_SFLOAT:           return VK_FORMAT_R16G16B16A16_SFLOAT;

        case OGA_FORMAT_R32_SFLOAT:                    return VK_FORMAT_R32_SFLOAT;
        case OGA_FORMAT_R32_UINT:                      return VK_FORMAT_R32_UINT;
        case OGA_FORMAT_R32_SINT:                      return VK_FORMAT_R32_SINT;

        case OGA_FORMAT_R32G32_SFLOAT:                 return VK_FORMAT_R32G32_SFLOAT;
        case OGA_FORMAT_R32G32_UINT:                   return VK_FORMAT_R32G32_UINT;
        case OGA_FORMAT_R32G32_SINT:                   return VK_FORMAT_R32G32_SINT;

        case OGA_FORMAT_R32G32B32_SFLOAT:              return VK_FORMAT_R32G32B32_SFLOAT;
        case OGA_FORMAT_R32G32B32_UINT:                return VK_FORMAT_R32G32B32_UINT;
        case OGA_FORMAT_R32G32B32_SINT:                return VK_FORMAT_R32G32B32_SINT;

        case OGA_FORMAT_R32G32B32A32_SFLOAT:           return VK_FORMAT_R32G32B32A32_SFLOAT;
        case OGA_FORMAT_R32G32B32A32_UINT:             return VK_FORMAT_R32G32B32A32_UINT;
        case OGA_FORMAT_R32G32B32A32_SINT:             return VK_FORMAT_R32G32B32A32_SINT;

        case OGA_FORMAT_DEPTH16_UNORM:                 return VK_FORMAT_D16_UNORM;
        case OGA_FORMAT_DEPTH24_UNORM_S8_UINT:         return VK_FORMAT_D24_UNORM_S8_UINT;
        case OGA_FORMAT_DEPTH32_SFLOAT:                return VK_FORMAT_D32_SFLOAT;
        case OGA_FORMAT_DEPTH32_SFLOAT_S8_UINT:        return VK_FORMAT_D32_SFLOAT_S8_UINT;

        case OGA_FORMAT_BC1_RGB_UNORM_BLOCK:           return VK_FORMAT_BC1_RGB_UNORM_BLOCK;
        case OGA_FORMAT_BC1_RGB_SRGB_BLOCK:            return VK_FORMAT_BC1_RGB_SRGB_BLOCK;
        case OGA_FORMAT_BC1_RGBA_UNORM_BLOCK:          return VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
        case OGA_FORMAT_BC1_RGBA_SRGB_BLOCK:           return VK_FORMAT_BC1_RGBA_SRGB_BLOCK;
        case OGA_FORMAT_BC2_UNORM_BLOCK:               return VK_FORMAT_BC2_UNORM_BLOCK;
        case OGA_FORMAT_BC2_SRGB_BLOCK:                return VK_FORMAT_BC2_SRGB_BLOCK;
        case OGA_FORMAT_BC3_UNORM_BLOCK:               return VK_FORMAT_BC3_UNORM_BLOCK;
        case OGA_FORMAT_BC3_SRGB_BLOCK:                return VK_FORMAT_BC3_SRGB_BLOCK;
        case OGA_FORMAT_BC4_UNORM_BLOCK:               return VK_FORMAT_BC4_UNORM_BLOCK;
        case OGA_FORMAT_BC4_SNORM_BLOCK:               return VK_FORMAT_BC4_SNORM_BLOCK;
        case OGA_FORMAT_BC5_UNORM_BLOCK:               return VK_FORMAT_BC5_UNORM_BLOCK;
        case OGA_FORMAT_BC5_SNORM_BLOCK:               return VK_FORMAT_BC5_SNORM_BLOCK;
        case OGA_FORMAT_BC6H_UFLOAT_BLOCK:             return VK_FORMAT_BC6H_UFLOAT_BLOCK;
        case OGA_FORMAT_BC6H_SFLOAT_BLOCK:             return VK_FORMAT_BC6H_SFLOAT_BLOCK;
        case OGA_FORMAT_BC7_UNORM_BLOCK:               return VK_FORMAT_BC7_UNORM_BLOCK;
        case OGA_FORMAT_BC7_SRGB_BLOCK:                return VK_FORMAT_BC7_SRGB_BLOCK;

        case OGA_FORMAT_ENUM_MAX:
        default:
            return (VkFormat)0;
    }
    return (VkFormat)0;
}
unit_local inline Oga_Format _vk_to_oga_format(VkFormat k) {
    switch ((s64)k) {
        case VK_FORMAT_R4G4_UNORM_PACK8:              return OGA_FORMAT_R4G4_UNORM_PACK8;
        case VK_FORMAT_R4G4B4A4_UNORM_PACK16:          return OGA_FORMAT_R4G4B4A4_UNORM_PACK16;
        case VK_FORMAT_B4G4R4A4_UNORM_PACK16:          return OGA_FORMAT_B4G4R4A4_UNORM_PACK16;
        case VK_FORMAT_R5G6B5_UNORM_PACK16:            return OGA_FORMAT_R5G6B5_UNORM_PACK16;
        case VK_FORMAT_B5G6R5_UNORM_PACK16:            return OGA_FORMAT_B5G6R5_UNORM_PACK16;
        case VK_FORMAT_R5G5B5A1_UNORM_PACK16:          return OGA_FORMAT_R5G5B5A1_UNORM_PACK16;
        case VK_FORMAT_A1R5G5B5_UNORM_PACK16:          return OGA_FORMAT_A1R5G5B5_UNORM_PACK16;

        case VK_FORMAT_R8_UNORM:                       return OGA_FORMAT_R8_UNORM;
        case VK_FORMAT_R8_SNORM:                       return OGA_FORMAT_R8_SNORM;
        case VK_FORMAT_R8_UINT:                        return OGA_FORMAT_R8_UINT;
        case VK_FORMAT_R8_SINT:                        return OGA_FORMAT_R8_SINT;
        case VK_FORMAT_R8_SRGB:                        return OGA_FORMAT_R8_SRGB;

        case VK_FORMAT_R8G8_UNORM:                     return OGA_FORMAT_R8G8_UNORM;
        case VK_FORMAT_R8G8_SNORM:                     return OGA_FORMAT_R8G8_SNORM;
        case VK_FORMAT_R8G8_UINT:                      return OGA_FORMAT_R8G8_UINT;
        case VK_FORMAT_R8G8_SINT:                      return OGA_FORMAT_R8G8_SINT;
        case VK_FORMAT_R8G8_SRGB:                      return OGA_FORMAT_R8G8_SRGB;

        case VK_FORMAT_R8G8B8_UNORM:                   return OGA_FORMAT_R8G8B8_UNORM;
        case VK_FORMAT_R8G8B8_SNORM:                   return OGA_FORMAT_R8G8B8_SNORM;
        case VK_FORMAT_R8G8B8_UINT:                    return OGA_FORMAT_R8G8B8_UINT;
        case VK_FORMAT_R8G8B8_SINT:                    return OGA_FORMAT_R8G8B8_SINT;
        case VK_FORMAT_R8G8B8_SRGB:                    return OGA_FORMAT_R8G8B8_SRGB;

        case VK_FORMAT_R8G8B8A8_UNORM:                 return OGA_FORMAT_R8G8B8A8_UNORM;
        case VK_FORMAT_R8G8B8A8_SNORM:                 return OGA_FORMAT_R8G8B8A8_SNORM;
        case VK_FORMAT_R8G8B8A8_UINT:                  return OGA_FORMAT_R8G8B8A8_UINT;
        case VK_FORMAT_R8G8B8A8_SINT:                  return OGA_FORMAT_R8G8B8A8_SINT;
        case VK_FORMAT_R8G8B8A8_SRGB:                  return OGA_FORMAT_R8G8B8A8_SRGB;

        case VK_FORMAT_B8G8R8A8_UNORM:                 return OGA_FORMAT_B8G8R8A8_UNORM;
        case VK_FORMAT_B8G8R8A8_SNORM:                 return OGA_FORMAT_B8G8R8A8_SNORM;
        case VK_FORMAT_B8G8R8A8_UINT:                  return OGA_FORMAT_B8G8R8A8_UINT;
        case VK_FORMAT_B8G8R8A8_SINT:                  return OGA_FORMAT_B8G8R8A8_SINT;
        case VK_FORMAT_B8G8R8A8_SRGB:                  return OGA_FORMAT_B8G8R8A8_SRGB;

        case VK_FORMAT_R16_UNORM:                      return OGA_FORMAT_R16_UNORM;
        case VK_FORMAT_R16_SNORM:                      return OGA_FORMAT_R16_SNORM;
        case VK_FORMAT_R16_UINT:                       return OGA_FORMAT_R16_UINT;
        case VK_FORMAT_R16_SINT:                       return OGA_FORMAT_R16_SINT;
        case VK_FORMAT_R16_SFLOAT:                     return OGA_FORMAT_R16_SFLOAT;

        case VK_FORMAT_R16G16_UNORM:                   return OGA_FORMAT_R16G16_UNORM;
        case VK_FORMAT_R16G16_SNORM:                   return OGA_FORMAT_R16G16_SNORM;
        case VK_FORMAT_R16G16_UINT:                    return OGA_FORMAT_R16G16_UINT;
        case VK_FORMAT_R16G16_SINT:                    return OGA_FORMAT_R16G16_SINT;
        case VK_FORMAT_R16G16_SFLOAT:                  return OGA_FORMAT_R16G16_SFLOAT;

        case VK_FORMAT_R16G16B16A16_UNORM:             return OGA_FORMAT_R16G16B16A16_UNORM;
        case VK_FORMAT_R16G16B16A16_SNORM:             return OGA_FORMAT_R16G16B16A16_SNORM;
        case VK_FORMAT_R16G16B16A16_UINT:              return OGA_FORMAT_R16G16B16A16_UINT;
        case VK_FORMAT_R16G16B16A16_SINT:              return OGA_FORMAT_R16G16B16A16_SINT;
        case VK_FORMAT_R16G16B16A16_SFLOAT:            return OGA_FORMAT_R16G16B16A16_SFLOAT;

        case VK_FORMAT_R32_SFLOAT:                     return OGA_FORMAT_R32_SFLOAT;
        case VK_FORMAT_R32_UINT:                       return OGA_FORMAT_R32_UINT;
        case VK_FORMAT_R32_SINT:                       return OGA_FORMAT_R32_SINT;

        case VK_FORMAT_R32G32_SFLOAT:                  return OGA_FORMAT_R32G32_SFLOAT;
        case VK_FORMAT_R32G32_UINT:                    return OGA_FORMAT_R32G32_UINT;
        case VK_FORMAT_R32G32_SINT:                    return OGA_FORMAT_R32G32_SINT;

        case VK_FORMAT_R32G32B32_SFLOAT:               return OGA_FORMAT_R32G32B32_SFLOAT;
        case VK_FORMAT_R32G32B32_UINT:                 return OGA_FORMAT_R32G32B32_UINT;
        case VK_FORMAT_R32G32B32_SINT:                 return OGA_FORMAT_R32G32B32_SINT;

        case VK_FORMAT_R32G32B32A32_SFLOAT:            return OGA_FORMAT_R32G32B32A32_SFLOAT;
        case VK_FORMAT_R32G32B32A32_UINT:              return OGA_FORMAT_R32G32B32A32_UINT;
        case VK_FORMAT_R32G32B32A32_SINT:              return OGA_FORMAT_R32G32B32A32_SINT;

        // Depth and Stencil formats
        case VK_FORMAT_D16_UNORM:                      return OGA_FORMAT_DEPTH16_UNORM;
        case VK_FORMAT_D24_UNORM_S8_UINT:              return OGA_FORMAT_DEPTH24_UNORM_S8_UINT;
        case VK_FORMAT_D32_SFLOAT:                     return OGA_FORMAT_DEPTH32_SFLOAT;
        case VK_FORMAT_D32_SFLOAT_S8_UINT:             return OGA_FORMAT_DEPTH32_SFLOAT_S8_UINT;

        case VK_FORMAT_BC1_RGB_UNORM_BLOCK:            return OGA_FORMAT_BC1_RGB_UNORM_BLOCK;
        case VK_FORMAT_BC1_RGB_SRGB_BLOCK:             return OGA_FORMAT_BC1_RGB_SRGB_BLOCK;
        case VK_FORMAT_BC1_RGBA_UNORM_BLOCK:           return OGA_FORMAT_BC1_RGBA_UNORM_BLOCK;
        case VK_FORMAT_BC1_RGBA_SRGB_BLOCK:            return OGA_FORMAT_BC1_RGBA_SRGB_BLOCK;
        case VK_FORMAT_BC2_UNORM_BLOCK:                return OGA_FORMAT_BC2_UNORM_BLOCK;
        case VK_FORMAT_BC2_SRGB_BLOCK:                 return OGA_FORMAT_BC2_SRGB_BLOCK;
        case VK_FORMAT_BC3_UNORM_BLOCK:                return OGA_FORMAT_BC3_UNORM_BLOCK;
        case VK_FORMAT_BC3_SRGB_BLOCK:                 return OGA_FORMAT_BC3_SRGB_BLOCK;
        case VK_FORMAT_BC4_UNORM_BLOCK:                return OGA_FORMAT_BC4_UNORM_BLOCK;
        case VK_FORMAT_BC4_SNORM_BLOCK:                return OGA_FORMAT_BC4_SNORM_BLOCK;
        case VK_FORMAT_BC5_UNORM_BLOCK:                return OGA_FORMAT_BC5_UNORM_BLOCK;
        case VK_FORMAT_BC5_SNORM_BLOCK:                return OGA_FORMAT_BC5_SNORM_BLOCK;
        case VK_FORMAT_BC6H_UFLOAT_BLOCK:              return OGA_FORMAT_BC6H_UFLOAT_BLOCK;
        case VK_FORMAT_BC6H_SFLOAT_BLOCK:              return OGA_FORMAT_BC6H_SFLOAT_BLOCK;
        case VK_FORMAT_BC7_UNORM_BLOCK:                return OGA_FORMAT_BC7_UNORM_BLOCK;
        case VK_FORMAT_BC7_SRGB_BLOCK:                 return OGA_FORMAT_BC7_SRGB_BLOCK;

        case OGA_FORMAT_ENUM_MAX:
        default:
            return (Oga_Format)0;
    }
    return (Oga_Format)0;
}

unit_local VkFormat _oga_vertex_attribute_type_to_vk_format(Oga_Vertex_Attribute_Type t) {
    switch(t) {
        case OGA_VERTEX_ATTRIBUTE_TYPE_F32:             return VK_FORMAT_R32_SFLOAT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_F32V2:           return VK_FORMAT_R32G32_SFLOAT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_F32V3:           return VK_FORMAT_R32G32B32_SFLOAT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_F32V4:           return VK_FORMAT_R32G32B32A32_SFLOAT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S32:             return VK_FORMAT_R32_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S32V2:           return VK_FORMAT_R32G32_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S32V3:           return VK_FORMAT_R32G32B32_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S32V4:           return VK_FORMAT_R32G32B32A32_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S16:             return VK_FORMAT_R16_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S16V2:           return VK_FORMAT_R16G16_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S16V3:           return VK_FORMAT_R16G16B16_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S16V4:           return VK_FORMAT_R16G16B16A16_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S8:              return VK_FORMAT_R8_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S8V2:            return VK_FORMAT_R8G8_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S8V3:            return VK_FORMAT_R8G8B8_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S8V4:            return VK_FORMAT_R8G8B8A8_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U32:             return VK_FORMAT_R32_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U32V2:           return VK_FORMAT_R32G32_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U32V3:           return VK_FORMAT_R32G32B32_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U32V4:           return VK_FORMAT_R32G32B32A32_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U16:             return VK_FORMAT_R16_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U16V2:           return VK_FORMAT_R16G16_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U16V3:           return VK_FORMAT_R16G16B16_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U16V4:           return VK_FORMAT_R16G16B16A16_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8:              return VK_FORMAT_R8_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8V2:            return VK_FORMAT_R8G8_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8V3:            return VK_FORMAT_R8G8B8_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8V4:            return VK_FORMAT_R8G8B8A8_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8_NORMALIZED:   return VK_FORMAT_R8_UNORM;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8V2_NORMALIZED: return VK_FORMAT_R8G8_UNORM;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8V3_NORMALIZED: return VK_FORMAT_R8G8B8_UNORM;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8V4_NORMALIZED: return VK_FORMAT_R8G8B8A8_UNORM;
        default: assert(false); break;
    }
    assert(false);
    return VK_FORMAT_R8G8B8A8_UNORM;
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


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

#define _vk_assert1(expr) do { VkResult _res = expr; string _res_str = _str_vk_result(_res); assertmsgs(_res == VK_SUCCESS, tprint("Vulkan call '%s' failed: %s. If you see this, you're either doing something very wrong, or there is an internal error in Oga.", STR(#expr), _res_str)); } while(0)
#define _vk_assert2(expr) do { VkResult _res = expr; if (_res == VK_ERROR_OUT_OF_DEVICE_MEMORY) return OGA_ERROR_OUT_OF_DEVICE_MEMORY; if (_res == VK_ERROR_OUT_OF_HOST_MEMORY) return OGA_ERROR_STATE_ALLOCATION_FAILED;  string _res_str = _str_vk_result(_res); assertmsgs(_res == VK_SUCCESS, tprint("Vulkan call '%s' failed: %s. If you see this, you're either doing something very wrong, or there is an internal error in Oga.", STR(#expr), _res_str)); } while(0)


unit_local VkDebugUtilsMessengerEXT _vk_messenger;

#ifdef DEBUG
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

    log(OGA_LOG_VERBOSE, "\n-----------------VK VALIDATION MESSAGE-----------------");
    log(OGA_LOG_VERBOSE, "Severity: %s", sev);
    if (pCallbackData->pMessageIdName)
        log(OGA_LOG_VERBOSE, "- Message ID: %s", STR(pCallbackData->pMessageIdName));
    if (pCallbackData->pMessage)
        log(OGA_LOG_VERBOSE, "- Message: %s", STR(pCallbackData->pMessage));

    return 0;
}
#endif

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

unit_local u8 _context_mem[(sizeof(Oga_Context)+sizeof(_Vk_Context_Internal))*1024];
unit_local u64 _allocated_contexts;
unit_local bool _has_dynamic_rendering = false;
unit_local VkInstance __instance = 0;
unit_local inline VkInstance _vk_instance(void) {

    if (!__instance) {
        
        u32 version_major = 0;
        u32 version_minor = 0;
        u32 version_patch = 0;
        {
            VkApplicationInfo query_app_info = (VkApplicationInfo){0};
            query_app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            query_app_info.pApplicationName = "Vulkan Version Check";
            query_app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            query_app_info.pEngineName = "No Engine";
            query_app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            query_app_info.apiVersion = VK_API_VERSION_1_0; 
        
            VkInstanceCreateInfo create_info = (VkInstanceCreateInfo){0};
            create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            create_info.pApplicationInfo = &query_app_info;
        
            VkInstance query_instance;
            VkResult result = vkCreateInstance(&create_info, 0, &query_instance);
            if (result != VK_SUCCESS) {
                print("Failed to create Vulkan query_instance.\n");
                return 0;
            }
        
            uint32_t device_count = 0;
            vkEnumeratePhysicalDevices(query_instance, &device_count, 0);
            if (device_count == 0) {
                print("No Vulkan-compatible devices found.\n");
                return 0;
            }
        
            VkPhysicalDevice devices[256];
            vkEnumeratePhysicalDevices(query_instance, &device_count, devices);
        
            for (uint32_t i = 0; i < device_count; i++) {
                VkPhysicalDeviceProperties properties;
                vkGetPhysicalDeviceProperties(devices[i], &properties);
        
                version_major = max(VK_VERSION_MAJOR(properties.apiVersion), version_major);
                version_minor = max(VK_VERSION_MINOR(properties.apiVersion), version_minor);
                version_patch = max(VK_VERSION_PATCH(properties.apiVersion), version_patch);
            }

            vkDestroyInstance(query_instance, 0);
        }
    
        log(OGA_LOG_VERBOSE, "Supported Vulkan Instance API version: %u.%u\n", version_major, version_minor);

        if (version_major >= 1 && version_minor >= 3) {
            _has_dynamic_rendering = true;
            
        }

        VkApplicationInfo app_info = (VkApplicationInfo){0};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = "Ostd App";
        app_info.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
        app_info.pEngineName = "Oga";
        app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        
        if (version_minor >= 3) {
            app_info.apiVersion = VK_API_VERSION_1_3;
        } else if (version_minor >= 2) {
            app_info.apiVersion = VK_API_VERSION_1_2;
        } else if (version_minor >= 1) {
            app_info.apiVersion = VK_API_VERSION_1_1;
        } else {
            app_info.apiVersion = VK_API_VERSION_1_0;
        }

        VkInstanceCreateInfo create_info = (VkInstanceCreateInfo){0};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &app_info;

#if OS_FLAGS & OS_FLAG_WINDOWS
        const char *required_extensions[] = {

#ifdef DEBUG
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif // _DEBUG
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
            "VK_KHR_get_physical_device_properties2"
        };
#elif OS_FLAGS & OS_FLAG_LINUX
    // Depending on your display server, pick one:
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        "VK_KHR_get_physical_device_properties2"
    };
#elif OS_FLAGS & OS_FLAG_MACOS
    // MoltenVK-specific extension for macOS
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        "VK_MVK_macos_surface",
        "VK_KHR_portability_enumeration",
        "VK_KHR_get_physical_device_properties2",
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
        "VK_KHR_portability_enumeration",
        "VK_KHR_get_physical_device_properties2",
    };
    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#elif OS_FLAGS & OS_FLAG_ANDROID
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
        "VK_KHR_get_physical_device_properties2"
    };

#else
    #error VK __instance extension query not set up for this OS
#endif
        
        u64 num_required_extensions = sizeof(required_extensions) / sizeof(char*) ;
        
        for (u64 i = 0; i < sizeof(required_extensions) / sizeof(char*); i += 1) {
            required_extensions[i] = required_extensions[i];
        }

        log(OGA_LOG_VERBOSE, "Looking for VkInstance extensions:");
        for (u64 i = 0; i < num_required_extensions; i += 1) {
            log(OGA_LOG_VERBOSE, "\t%s", STR(required_extensions[i]));
        }

        // #Portability dynamic rendering
        u32 num_available_extensions;
        _vk_assert1(vkEnumerateInstanceExtensionProperties(0, &num_available_extensions, 0));
        VkExtensionProperties *available_extensions = PushTempBuffer(VkExtensionProperties, num_available_extensions);
        memset(available_extensions, 0, num_available_extensions*sizeof(VkExtensionProperties));
        _vk_assert1(vkEnumerateInstanceExtensionProperties(0, &num_available_extensions, available_extensions));
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
                log(OGA_LOG_VERBOSE, "Missing required vulkan extension '%s'", STR(required));
                log(OGA_LOG_VERBOSE, "List of available extensions:");
                for (u32 j = 0; j < num_available_extensions; j += 1) {
                    const char *available = available_extensions[j].extensionName;
                    log(OGA_LOG_VERBOSE, "\t%s", STR(available));
                }
                    
            } else {
                log(OGA_LOG_VERBOSE, "Found '%s'..", STR(required));
            }
        }

        assertmsg(!any_missing, "Basic vulkan extensions were missing, cannot proceed. Make sure you have a proper vulkan SDK installed.");

        create_info.ppEnabledExtensionNames = required_extensions;
        create_info.enabledExtensionCount = (u32)num_required_extensions;

#ifdef DEBUG
        const char *wanted_layers[] = {"VK_LAYER_KHRONOS_validation"};
        u32 num_wanted_layers = (u64)(sizeof(wanted_layers)/sizeof(char*));

        u32 num_available_layers;
        _vk_assert1(vkEnumerateInstanceLayerProperties(&num_available_layers, 0));

        VkLayerProperties *available_layers = PushTempBuffer(VkLayerProperties, num_available_layers);
        _vk_assert1(vkEnumerateInstanceLayerProperties(&num_available_layers, available_layers));

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
                log(OGA_LOG_VERBOSE, "Missing wanted vulkan validation layer '%s'", STR(wanted));
                if (num_available_layers) {
                    log(OGA_LOG_VERBOSE, "List of available validation layers:");
                    for (u32 j = 0; j < num_available_layers; j += 1) {
                        const char *available = available_layers[j].layerName;
                        log(OGA_LOG_VERBOSE, "\t%s", STR(available));
                    }
                } else {
                    log(OGA_LOG_VERBOSE, "No validation layers available");
                }
            } else {
                final_layers[num_final_layers++] = wanted;
                log(OGA_LOG_VERBOSE, "Found validation layer %s", STR(wanted));
            }
        }

        create_info.enabledLayerCount = num_final_layers;
        create_info.ppEnabledLayerNames = final_layers;
#else
        create_info.enabledLayerCount = 0;
#endif

        _vk_assert1(vkCreateInstance(&create_info, 0, &__instance));
        log(OGA_LOG_VERBOSE, "Created a vulkan instance");

#ifdef DEBUG
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

        void (*untyped)(void) = vkGetInstanceProcAddr(__instance, "vkCreateDebugUtilsMessengerEXT");
        PFN_vkCreateDebugUtilsMessengerEXT _vkCreateDebugUtilsMessengerEXT  = (PFN_vkCreateDebugUtilsMessengerEXT)*(PFN_vkCreateDebugUtilsMessengerEXT*)(void**)&untyped;

        if (_vkCreateDebugUtilsMessengerEXT(__instance, &debug_create_info, 0, &_vk_messenger) != VK_SUCCESS) {
            log(OGA_LOG_VERBOSE, "Failed creating vulkan debug messenger");
        } else {
            log(OGA_LOG_VERBOSE, "Created a vulkan debug messenger");
        }
#endif // DEBUG
    }


    return __instance;
}

void oga_reset(void) {
    void (*untyped)(void) = vkGetInstanceProcAddr(__instance, "vkDestroyDebugUtilsMessengerEXT");
    PFN_vkDestroyDebugUtilsMessengerEXT _vkDestroyDebugUtilsMessengerEXT  = (PFN_vkDestroyDebugUtilsMessengerEXT)*(PFN_vkDestroyDebugUtilsMessengerEXT*)(void**)&untyped;
    _vkDestroyDebugUtilsMessengerEXT(_vk_instance(), _vk_messenger, 0);
    vkDestroyInstance(_vk_instance(), 0);
    __instance = 0;
}

unit_local void *_vk_allocate(void *ud, size_t size, size_t alignment, VkSystemAllocationScope scope) {
    (void)scope;
    Allocator *allocator = (Allocator *)ud;
    void *p = allocator->proc(ALLOCATOR_ALLOCATE, allocator->data, 0, 0, size, alignment, 0);
#ifdef LOG_VULKAN_ALLOCATIONS
    string scope_str;
    if (scope == VK_SYSTEM_ALLOCATION_SCOPE_COMMAND) {
        scope_str = STR("Command");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_OBJECT) {
        scope_str = STR("Scope");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_CACHE) {
        scope_str = STR("Cache");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_DEVICE) {
        scope_str = STR("Device");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE) {
        scope_str = STR("Instance");
    }
    log(OGA_LOG_VERBOSE, "VK Allocation '%s'  %u bytes, %u alignment %u", scope_str, size, alignment, p);
    //sys_print_stack_trace(sys_get_stdout());
    //log(OGA_LOG_VERBOSE, "------------------------------------\n");
#endif
    return p;
}

unit_local void *_vk_reallocate(void *ud, void *old, size_t size, size_t alignment, VkSystemAllocationScope scope) {
    (void)scope;
#ifdef LOG_VULKAN_ALLOCATIONS
    string scope_str;
    if (scope == VK_SYSTEM_ALLOCATION_SCOPE_COMMAND) {
        scope_str = STR("Command");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_OBJECT) {
        scope_str = STR("Scope");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_CACHE) {
        scope_str = STR("Cache");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_DEVICE) {
        scope_str = STR("Device");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE) {
        scope_str = STR("Instance");
    }
    log(OGA_LOG_VERBOSE, "VK REallocation '%s'  %u bytes, %u alignment ", scope_str, size, alignment);
    //sys_print_stack_trace(sys_get_stdout());
    //log(OGA_LOG_VERBOSE, "------------------------------------\n");
#endif
    Allocator *allocator = (Allocator *)ud;
    return allocator->proc(ALLOCATOR_REALLOCATE, allocator->data, old, 0, size, alignment, 0);
}

unit_local void _vk_deallocate(void *ud, void *old) {
#ifdef LOG_VULKAN_ALLOCATIONS
    log(OGA_LOG_VERBOSE, "VK FREE %u", old);
#endif
    Allocator *allocator = (Allocator *)ud;
    allocator->proc(ALLOCATOR_FREE, allocator->data, old, 0, 0, 0, 0);
}

unit_local void _vk_internal_allocate(void *ud, size_t sz, VkInternalAllocationType t, VkSystemAllocationScope s) {
    (void)ud; (void)sz; (void)t; (void)s;
}
unit_local void _vk_internal_deallocate(void *ud, size_t sz, VkInternalAllocationType t, VkSystemAllocationScope s) {
    (void)ud; (void)sz; (void)t; (void)s;
}
unit_local inline VkAllocationCallbacks _vk_allocator(Allocator *a) {
    VkAllocationCallbacks c = (VkAllocationCallbacks){0};
    c.pUserData = a;
    c.pfnAllocation = _vk_allocate;
    c.pfnReallocation = _vk_reallocate;
    c.pfnFree = _vk_deallocate;
    c.pfnInternalAllocation = _vk_internal_allocate;
    c.pfnInternalFree = _vk_internal_deallocate;
    return c;
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
    create_info.window = (Window)_get_surface_state(h)->handle;
    create_info.dpy = _get_surface_state(h)->xlib_display;
    return vkCreateXlibSurfaceKHR(_vk_instance(), &create_info, 0, result);
#elif OS_FLAGS & OS_FLAG_MACOS
    VkMacOSSurfaceCreateInfoMVK create_info = (VkMacOSSurfaceCreateInfoMVK){0};
    create_info.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    create_info.pView = h;
    return vkCreateMacOSSurfaceMVK(_vk_instance(), &create_info, 0, result);
#elif OS_FLAGS & OS_FLAG_IOS
    VkIOSSurfaceCreateInfoMVK create_info = (VkIOSSurfaceCreateInfoMVK){0};
    create_info.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
    create_info.pView = h;
    return vkCreateIOSSurfaceMVK(_vk_instance(), &create_info, 0, result);
#elif OS_FLAGS & OS_FLAG_ANDROID
    VkAndroidSurfaceCreateInfoKHR create_info = (VkAndroidSurfaceCreateInfoKHR){0};
    create_info.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    create_info.window = (ANativeWindow*)h;
    return vkCreateAndroidSurfaceKHR(_vk_instance(), &create_info, 0, result);
#else
    #error VK surface creation not implemented for this os
#endif
}

u64 oga_query_devices(Oga_Device *buffer, u64 buffer_count) {

    u32 device_count;
    _vk_assert1(vkEnumeratePhysicalDevices(_vk_instance(), &device_count,  0));

    if (buffer) {
        memset(buffer, 0, buffer_count*sizeof(Oga_Device));
        VkPhysicalDevice vk_devices[256];
        _vk_assert1(vkEnumeratePhysicalDevices(_vk_instance(), &device_count,  vk_devices));

        // note(charlie) annoyingly, we need an existing surface to look for
        // surface support in engines. So, we just make a temporary invisible
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
        _vk_assert1(vkCreateSurfaceKHR(temp_sys_surface, &temp_vk_surface));
        for (u32 i = 0; i < min(device_count, (u32)buffer_count); i += 1) {
            Oga_Device *device = buffer + i;
            VkPhysicalDevice vk_device = vk_devices[i];
            
            VkDevice dummy_device;
            VkDeviceCreateInfo dummy_info = (VkDeviceCreateInfo){0};
            
            VkDeviceQueueCreateInfo dummy_queue = (VkDeviceQueueCreateInfo){0};
            dummy_queue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            dummy_queue.queueFamilyIndex = 0;
            dummy_queue.queueCount = 1;
            float one = 1;
            dummy_queue.pQueuePriorities = &one;
            
            dummy_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            dummy_info.queueCreateInfoCount = 1;
            dummy_info.pQueueCreateInfos = &dummy_queue;
            
            _vk_assert2(vkCreateDevice(vk_device, &dummy_info, 0, &dummy_device));

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
            VkExtensionProperties *ext_props = PushTempBuffer(VkExtensionProperties, ext_count);
            vkEnumerateDeviceExtensionProperties(vk_device, 0, &ext_count, ext_props);

            u32 engine_family_count;
            vkGetPhysicalDeviceQueueFamilyProperties(vk_device, &engine_family_count, 0);
            VkQueueFamilyProperties *engine_family_props = PushTempBuffer(VkQueueFamilyProperties, engine_family_count);
            vkGetPhysicalDeviceQueueFamilyProperties(vk_device, &engine_family_count, engine_family_props);


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
            device->vendor_id = (u64)props.vendorID;
            device->vendor_name = _str_vendor_id(props.vendorID);
            device->driver_version_raw = props.driverVersion;
            device->driver_version_length = _format_driver_version(props.vendorID, props.driverVersion, device->driver_version_data, sizeof(device->driver_version_data));
            
            device->api_version_raw = props.apiVersion;
            u32 major = VK_VERSION_MAJOR(device->api_version_raw);
            u32 minor = VK_VERSION_MINOR(device->api_version_raw);
            u32 patch = VK_VERSION_PATCH(device->api_version_raw);
            device->api_version_length = format_string(device->api_version_data, sizeof(device->api_version_data), "Vulkan %u.%u.%u", major, minor, patch);

            ///
            // Logical Engine flags


            device->engine_family_count = engine_family_count;
            for (u32 j = 0; j < engine_family_count; j += 1) {
                Oga_Logical_Engine_Family_Info *info = &device->engine_family_infos[j];
                VkQueueFamilyProperties family_props = engine_family_props[j];

                VkBool32 val;
                _vk_assert1(vkGetPhysicalDeviceSurfaceSupportKHR(vk_device, j, temp_vk_surface, &val));
                if (val) info->flags |= OGA_LOGICAL_ENGINE_PRESENT;

                info->engine_capacity = family_props.queueCount;

                if (family_props.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                    info->flags |= OGA_LOGICAL_ENGINE_GRAPHICS;
                if (family_props.queueFlags & VK_QUEUE_COMPUTE_BIT)
                    info->flags |= OGA_LOGICAL_ENGINE_COMPUTE;
                if (family_props.queueFlags & VK_QUEUE_TRANSFER_BIT)
                    info->flags |= OGA_LOGICAL_ENGINE_TRANSFER;
            }

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
                log(OGA_LOG_VERBOSE, ("WARNING: Could not find a supported depth format on this device."));
                vk_depth_format = VK_FORMAT_D32_SFLOAT;
            }

            device->depth_format = _vk_to_oga_format(vk_depth_format);

            /////
            // Memory heaps

            for (u32 j = 0; j < mem_props.memoryHeapCount; j += 1) {
                device->memory_heaps[j].size = (u64)mem_props.memoryHeaps[j].size;
            }
            device->memory_heap_count = mem_props.memoryHeapCount;
            
            VkBuffer dummy_vlist, dummy_ilist, dummy_ubuffer, dummy_sbuffer, dummy_dst, dummy_src;
            VkBufferCreateInfo dummy_buffer_info = (VkBufferCreateInfo){0};
            dummy_buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            dummy_buffer_info.size = 569;
            dummy_buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            dummy_buffer_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
            _vk_assert2(vkCreateBuffer(dummy_device, &dummy_buffer_info, 0, &dummy_vlist));
            dummy_buffer_info.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
            _vk_assert2(vkCreateBuffer(dummy_device, &dummy_buffer_info, 0, &dummy_ilist));
            dummy_buffer_info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
            _vk_assert2(vkCreateBuffer(dummy_device, &dummy_buffer_info, 0, &dummy_ubuffer));
            dummy_buffer_info.usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
            _vk_assert2(vkCreateBuffer(dummy_device, &dummy_buffer_info, 0, &dummy_sbuffer));
            dummy_buffer_info.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
            _vk_assert2(vkCreateBuffer(dummy_device, &dummy_buffer_info, 0, &dummy_dst));
            dummy_buffer_info.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
            _vk_assert2(vkCreateBuffer(dummy_device, &dummy_buffer_info, 0, &dummy_src));
            
            VkImage dummy_image_1d, dummy_image_2d, dummy_image_3d;
            VkImage dummy_fbuffer_1d, dummy_fbuffer_2d, dummy_fbuffer_3d;
            VkImageCreateInfo dummy_image_info = (VkImageCreateInfo){0};
            dummy_image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            dummy_image_info.extent.width = props.limits.maxImageDimension1D;
            dummy_image_info.extent.height = 1;
            dummy_image_info.extent.depth = 1;
            dummy_image_info.mipLevels = 1;
            dummy_image_info.arrayLayers = 1;
            dummy_image_info.format = VK_FORMAT_R8G8B8A8_UNORM;
            dummy_image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
            dummy_image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            dummy_image_info.samples = VK_SAMPLE_COUNT_1_BIT;
            dummy_image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            
            dummy_image_info.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
            dummy_image_info.imageType = VK_IMAGE_TYPE_1D;
            _vk_assert2(vkCreateImage(dummy_device, &dummy_image_info, 0, &dummy_image_1d));
            dummy_image_info.usage = VK_IMAGE_USAGE_STORAGE_BIT;
            dummy_image_info.imageType = VK_IMAGE_TYPE_1D;
            _vk_assert2(vkCreateImage(dummy_device, &dummy_image_info, 0, &dummy_fbuffer_1d));
            dummy_image_info.extent.width = props.limits.maxImageDimension2D;
            dummy_image_info.extent.height = props.limits.maxImageDimension2D;
            dummy_image_info.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
            dummy_image_info.imageType = VK_IMAGE_TYPE_2D;
            _vk_assert2(vkCreateImage(dummy_device, &dummy_image_info, 0, &dummy_image_2d));
            dummy_image_info.usage = VK_IMAGE_USAGE_STORAGE_BIT;
            dummy_image_info.imageType = VK_IMAGE_TYPE_2D;
            _vk_assert2(vkCreateImage(dummy_device, &dummy_image_info, 0, &dummy_fbuffer_2d));
            dummy_image_info.extent.width = props.limits.maxImageDimension3D;
            dummy_image_info.extent.height = props.limits.maxImageDimension3D;
            dummy_image_info.extent.depth = 4;
            dummy_image_info.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
            dummy_image_info.imageType = VK_IMAGE_TYPE_3D;
            _vk_assert2(vkCreateImage(dummy_device, &dummy_image_info, 0, &dummy_image_3d));
            dummy_image_info.usage = VK_IMAGE_USAGE_STORAGE_BIT;
            dummy_image_info.imageType = VK_IMAGE_TYPE_3D;
            _vk_assert2(vkCreateImage(dummy_device, &dummy_image_info, 0, &dummy_fbuffer_3d));
            
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
                VkMemoryRequirements req = (VkMemoryRequirements){0};
                vkGetBufferMemoryRequirements(dummy_device, dummy_vlist, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_VERTEX_LIST;
                vkGetBufferMemoryRequirements(dummy_device, dummy_ilist, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_INDEX_LIST;
                vkGetBufferMemoryRequirements(dummy_device, dummy_ubuffer, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_FAST_READONLY_DATA_BLOCK;
                vkGetBufferMemoryRequirements(dummy_device, dummy_sbuffer, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_LARGE_READWRITE_DATA_BLOCK;
                vkGetBufferMemoryRequirements(dummy_device, dummy_src, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_COPY_DST;
                vkGetBufferMemoryRequirements(dummy_device, dummy_dst, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_COPY_SRC;
                vkGetImageMemoryRequirements(dummy_device, dummy_image_1d, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_IMAGE_1D;
                vkGetImageMemoryRequirements(dummy_device, dummy_image_2d, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_IMAGE_2D;
                vkGetImageMemoryRequirements(dummy_device, dummy_image_3d, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_IMAGE_3D;
                vkGetImageMemoryRequirements(dummy_device, dummy_fbuffer_1d, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_FBUFFER_1D;
                vkGetImageMemoryRequirements(dummy_device, dummy_fbuffer_2d, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_FBUFFER_2D;
                vkGetImageMemoryRequirements(dummy_device, dummy_fbuffer_3d, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_FBUFFER_3D;
                    
                device->limits.image_memory_granularity = max(device->limits.image_memory_granularity, (u64)req.alignment);
                
            }
            
            for (u32 j = 0; j < device->memory_heap_count; j += 1) {
                if (device->memory_heaps[j].properties & OGA_MEMORY_PROPERTY_GPU_LOCAL)
                    device->total_gpu_local_memory += device->memory_heaps[j].size;
            }
            
            vkDestroyBuffer(dummy_device, dummy_vlist, 0);
            vkDestroyBuffer(dummy_device, dummy_ilist, 0);
            vkDestroyBuffer(dummy_device, dummy_ubuffer, 0);
            vkDestroyBuffer(dummy_device, dummy_sbuffer, 0);
            vkDestroyBuffer(dummy_device, dummy_src, 0);
            vkDestroyBuffer(dummy_device, dummy_dst, 0);
            vkDestroyImage(dummy_device, dummy_image_1d, 0);
            vkDestroyImage(dummy_device, dummy_image_2d, 0);
            vkDestroyImage(dummy_device, dummy_image_3d, 0);
            vkDestroyImage(dummy_device, dummy_fbuffer_1d, 0);
            vkDestroyImage(dummy_device, dummy_fbuffer_2d, 0);
            vkDestroyImage(dummy_device, dummy_fbuffer_3d, 0);
            
            /////
            // Feature flags
            if (props.limits.timestampComputeAndGraphics) {
                device->features |= (OGA_DEVICE_FEATURE_GRAPHICS_TIMESTAMP |
                                     OGA_DEVICE_FEATURE_COMPUTE_TIMESTAMP);
            }
            
            VkPresentModeKHR present_modes[32];
            u32 present_mode_count = 32;
            _vk_assert1(vkGetPhysicalDeviceSurfacePresentModesKHR(vk_device, temp_vk_surface, &present_mode_count, present_modes));
            for (u32 j = 0; j < present_mode_count; j += 1) {
                if (present_modes[j] == VK_PRESENT_MODE_MAILBOX_KHR)
                    device->features |= OGA_DEVICE_FEATURE_PRESENT_MAILBOX;
            }
            
            if (features.depthClamp)
                device->features |= OGA_DEVICE_FEATURE_DEPTH_CLAMP;
                
            /////
            // Limits

            device->limits.max_program_view_sets_per_stage = props.limits.maxPerStageResources;
            device->limits.max_fast_data_blocks_per_stage = props.limits.maxPerStageDescriptorUniformBuffers;
            device->limits.max_large_data_blocks_per_stage = props.limits.maxPerStageDescriptorStorageBuffers;
            device->limits.max_images_per_stage = props.limits.maxPerStageDescriptorSampledImages;
            device->limits.max_fbuffers_per_stage = props.limits.maxPerStageDescriptorStorageImages;
            device->limits.max_samplers_per_stage = props.limits.maxPerStageDescriptorSamplers;
            device->limits.max_fast_data_blocks_per_layout = props.limits.maxDescriptorSetUniformBuffers;
            device->limits.max_large_data_blocks_per_layout = props.limits.maxDescriptorSetStorageBuffers;
            device->limits.max_images_per_layout = props.limits.maxDescriptorSetSampledImages;
            device->limits.max_fbuffers_per_layout = props.limits.maxDescriptorSetStorageImages;
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
            device->limits.max_render_attachments = props.limits.maxColorAttachments;
            device->limits.min_memory_map_alignment = props.limits.minMemoryMapAlignment;
            for (u64 f = 1; f < 64; f = f << 1)
                if (props.limits.framebufferColorSampleCounts & f) device->limits.supported_sample_counts_render_pass |= f;
            for (u64 f = 1; f < 64; f = f << 1)
                if (props.limits.sampledImageColorSampleCounts & f) device->limits.supported_sample_counts_image_float |= f;
            for (u64 f = 1; f < 64; f = f << 1)
                if (props.limits.storageImageSampleCounts & f) device->limits.supported_sample_counts_fbuffer_float |= f;
            for (u64 f = 1; f < 64; f = f << 1)
                if (props.limits.sampledImageIntegerSampleCounts & f) device->limits.supported_sample_counts_image_int |= f;
            for (u64 f = 1; f < 64; f = f << 1)
                if (props.limits.storageImageSampleCounts & f) device->limits.supported_sample_counts_fbuffer_int |= f;

            device->limits.memory_granularity = max(device->limits.memory_granularity, (u64)props.limits.bufferImageGranularity);
            device->limits.memory_granularity = max(device->limits.memory_granularity, (u64)props.limits.minMemoryMapAlignment);
            device->limits.memory_granularity = max(device->limits.memory_granularity, (u64)props.limits.minTexelBufferOffsetAlignment);
            device->limits.memory_granularity = max(device->limits.memory_granularity, (u64)props.limits.minUniformBufferOffsetAlignment);
            device->limits.memory_granularity = max(device->limits.memory_granularity, (u64)props.limits.optimalBufferCopyOffsetAlignment);
            device->limits.memory_granularity = max(device->limits.memory_granularity, (u64)props.limits.optimalBufferCopyRowPitchAlignment);
            
            device->limits.image_memory_granularity = max(device->limits.image_memory_granularity, device->limits.memory_granularity);
            device->limits.fbuffer_memory_granularity = device->limits.image_memory_granularity;

            /////
            // Surface formats
            
            u32 vk_formats_count = 512;
            _vk_assert1(vkGetPhysicalDeviceSurfaceFormatsKHR(vk_device, temp_vk_surface, &vk_formats_count, 0));
            VkSurfaceFormatKHR vk_formats[512];
            _vk_assert1(vkGetPhysicalDeviceSurfaceFormatsKHR(vk_device, temp_vk_surface, &vk_formats_count, vk_formats));
            
            for (u32 j = 0; j < vk_formats_count; j += 1) {
                if (vk_formats[j].colorSpace != VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) continue;
                Oga_Format oga_format = _vk_to_oga_format(vk_formats[j].format);
                if (oga_format != 0) {
                    device->supported_surface_formats[device->supported_surface_format_count++] = oga_format;
                }
            }
            
            
            
            
            
            vkDestroyDevice(dummy_device, 0);
        
            device->id = vk_device;
        }
        vkDestroySurfaceKHR(_vk_instance(), temp_vk_surface, 0);

#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
        surface_close(temp_sys_surface);
#endif
    }

    return device_count;
}

Oga_Device *oga_get_devices(Allocator a, u64 *count) {
    *count = oga_query_devices(0, 0);

    Oga_Device *devices = NewBuffer(a, Oga_Device, *count);
    oga_query_devices(devices, *count);

    return devices;
}


Oga_Result oga_init_context(Oga_Device target_device, Oga_Context_Desc desc, Oga_Context **context) {

    if ((desc.enabled_features & target_device.features) != desc.enabled_features) {
        return OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES;
    }

    *context = (Oga_Context*)&_context_mem[(sizeof(Oga_Context)+sizeof(_Vk_Context_Internal))*_allocated_contexts++];
    if (!*context) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }
    Oga_Context *c = *context;
    *c = (Oga_Context){0};
    c->state_allocator = desc.state_allocator;
    c->internal = c+1;
    if (!c->state_allocator.proc) {
        Allocator a;
        a.proc = oga_state_allocator_proc;
        c->default_allocator_data = (Oga_State_Allocator_Data) {0};
        a.data = &c->default_allocator_data;
        c->state_allocator = a;
    }
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)c->internal;
    
    internal->vk_allocs = _vk_allocator(&c->state_allocator);

    VkPhysicalDeviceFeatures enabled_features = (VkPhysicalDeviceFeatures){0};
    // if (desc.enabled_features & OGA_DEVICE_FEATURE_XXXX) enabled_features.xxxx = true;
    
    if (target_device.features & OGA_DEVICE_FEATURE_DEPTH_CLAMP) {
        enabled_features.depthClamp = true;
    }
    
    enabled_features.samplerAnisotropy = VK_TRUE;
    // todo(charlie) device feature flag
    enabled_features.fragmentStoresAndAtomics = VK_TRUE;
    
    // We need to do this because driver people simply hate programmers
    VkPhysicalDeviceCoherentMemoryFeaturesAMD device_coherent_memory_features_amd
        = (VkPhysicalDeviceCoherentMemoryFeaturesAMD) {0};
        device_coherent_memory_features_amd.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD;
    
    VkPhysicalDeviceFeatures2 enabled_features2 = (VkPhysicalDeviceFeatures2){0};
    enabled_features2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR;
    enabled_features2.pNext = &device_coherent_memory_features_amd;
    
    {
        void (*untyped)(void) = vkGetInstanceProcAddr(__instance, "vkGetPhysicalDeviceFeatures2KHR");
        if (!untyped) {
            untyped = vkGetInstanceProcAddr(__instance, "vkGetPhysicalDeviceFeatures2");
        }
        assert(untyped);
        
        PFN_vkGetPhysicalDeviceFeatures2KHR vkGetPhysicalDeviceFeatures2KHR_ 
            = (PFN_vkGetPhysicalDeviceFeatures2KHR)*(PFN_vkGetPhysicalDeviceFeatures2KHR*)(void**)&untyped;
        
        vkGetPhysicalDeviceFeatures2KHR_(target_device.id, &enabled_features2);
    }
    
    
    enabled_features2.features = enabled_features;
    
    // todo(charlie) oga context feature flags
    VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT fragment_shader_interlock
        = (VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT) {0};
    fragment_shader_interlock.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT;
    fragment_shader_interlock.fragmentShaderSampleInterlock = VK_FALSE;
    fragment_shader_interlock.fragmentShaderPixelInterlock = VK_TRUE;
    fragment_shader_interlock.fragmentShaderShadingRateInterlock = VK_FALSE;
    
    device_coherent_memory_features_amd.pNext = &fragment_shader_interlock;

    VkDeviceQueueCreateInfo engine_infos[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES] = {0};

    u64 engines_desc_count = 0;
    for (u64 family_index = 0; family_index < OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES; family_index += 1) {
        Oga_Logical_Engines_Create_Desc engines_desc = desc.engine_create_descs[family_index];
        if (engines_desc.count > 0) {

            if (family_index >= target_device.engine_family_count) {
                return OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE;
            }

            Oga_Logical_Engine_Family_Info family = target_device.engine_family_infos[family_index];
            if (engines_desc.count > family.engine_capacity) {
                return OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW;
            }

            VkDeviceQueueCreateInfo *info = &engine_infos[engines_desc_count];
            info->sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            info->queueFamilyIndex = (u32)family_index;
            info->queueCount = (u32)engines_desc.count;
            info->pQueuePriorities = engines_desc.priorities;

            engines_desc_count += 1;
        }
    }

    // #Portability dynamic rendering
    VkPhysicalDeviceDynamicRenderingFeatures dynamic_rendering = (VkPhysicalDeviceDynamicRenderingFeatures){0};
    dynamic_rendering.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES;
    dynamic_rendering.dynamicRendering = true;
    
    VkPhysicalDeviceVulkan13Features vk13_features = (VkPhysicalDeviceVulkan13Features){0};
    vk13_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
    vk13_features.dynamicRendering = true;
    
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(target_device.id, &props);

    VkDeviceCreateInfo info = (VkDeviceCreateInfo) {0};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    info.pEnabledFeatures = 0;
    info.pNext = &enabled_features2;
    info.queueCreateInfoCount = (u32)engines_desc_count;
    info.pQueueCreateInfos = engine_infos;
    
    void **pp_next = &fragment_shader_interlock.pNext;
    
    
    internal->vk_version_major = VK_VERSION_MAJOR(props.apiVersion);
    internal->vk_version_minor = VK_VERSION_MINOR(props.apiVersion);
    internal->vk_version_patch = VK_VERSION_PATCH(props.apiVersion);
    
    string name = (string){target_device.device_name_length, target_device.device_name_data};
    string api = (string){target_device.api_version_length, target_device.api_version_data};
    
    
    char **names = PushTempBuffer(char*, 32);
    if (internal->vk_version_major == 1 && internal->vk_version_minor < 3) {
        
        uint32_t existing_count = 0;
        vkEnumerateDeviceExtensionProperties(target_device.id, 0, &existing_count, 0);
        VkExtensionProperties *existing_exts = PushTempBuffer(VkExtensionProperties, existing_count);
        vkEnumerateDeviceExtensionProperties(target_device.id, 0, &existing_count, existing_exts);
        
        bool ext_depth_stencil_resolve = false;
        bool ext_create_renderpass2 = false;
        bool ext_dynamic_rendering = false;
        
        for (u64 i = 0; i < existing_count; i += 1) {
            string existing = STR(existing_exts[i].extensionName);
            
            if (strings_match(existing, STR("VK_KHR_depth_stencil_resolve")))
                ext_depth_stencil_resolve = true;
            if (strings_match(existing, STR("VK_KHR_create_renderpass2")))
                ext_create_renderpass2 = true;
            if (strings_match(existing, STR("VK_KHR_dynamic_rendering")))
                ext_dynamic_rendering = true;
        }
        
        
        
        info.enabledExtensionCount = 0;
        internal->dynamic_rendering = ext_dynamic_rendering;
        names[info.enabledExtensionCount++] = "VK_KHR_dynamic_rendering";
        if (internal->vk_version_minor <= 1) {
            internal->dynamic_rendering &= ext_depth_stencil_resolve;
            names[info.enabledExtensionCount++] = "VK_KHR_depth_stencil_resolve";
            internal->dynamic_rendering &= ext_create_renderpass2;
            names[info.enabledExtensionCount++] = "VK_KHR_create_renderpass2";
        }
            
        
        names[info.enabledExtensionCount++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME
        ;
        
        info.ppEnabledExtensionNames = (const char*const*)names;
        
        // todo(charlie) feature flags
        if (target_device.vendor_id == VENDOR_ID_AMD) {
            names[info.enabledExtensionCount++] = "VK_AMD_device_coherent_memory";
        }
        names[info.enabledExtensionCount++] = "VK_EXT_fragment_shader_interlock";
        internal->dynamic_rendering_is_extension = true;
    } else {
        internal->dynamic_rendering = true;
        internal->dynamic_rendering_is_extension = false;
        
        // todo(charlie) feature flags
        if (target_device.vendor_id == VENDOR_ID_AMD) {
            names[info.enabledExtensionCount++] = "VK_AMD_device_coherent_memory";
        }
        names[info.enabledExtensionCount++] = "VK_EXT_fragment_shader_interlock";
        names[info.enabledExtensionCount++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
        info.ppEnabledExtensionNames = (const char*const*)names;
    }
    
    
    log(OGA_LOG_VERBOSE, "Enabling %i VkDevice extensions:", info.enabledExtensionCount);
    for (u32 i = 0; i < info.enabledExtensionCount; i += 1) {
        log(OGA_LOG_VERBOSE, "\t%s", STR(names[i]));
    }
    
    log(OGA_LOG_VERBOSE, "Dynamic rendering enabled: %b", internal->dynamic_rendering);
    
    if (internal->dynamic_rendering) {
        if (internal->dynamic_rendering_is_extension) {
            void (*untyped)(void) = vkGetInstanceProcAddr(__instance, "vkCmdBeginRenderingKHR");
            internal->vkCmdBeginRenderingKHR  = (PFN_vkCmdBeginRenderingKHR)*(PFN_vkCmdBeginRenderingKHR*)(void**)&untyped;
            untyped = vkGetInstanceProcAddr(__instance, "vkCmdEndRenderingKHR");
            internal->vkCmdEndRenderingKHR  = (PFN_vkCmdEndRenderingKHR)*(PFN_vkCmdEndRenderingKHR*)(void**)&untyped;
            
            *pp_next = &dynamic_rendering;
            
        } else {
            void (*untyped)(void) = vkGetInstanceProcAddr(__instance, "vkCmdBeginRendering");
            internal->vkCmdBeginRenderingKHR  = (PFN_vkCmdBeginRenderingKHR)*(PFN_vkCmdBeginRenderingKHR*)(void**)&untyped;
            untyped = vkGetInstanceProcAddr(__instance, "vkCmdEndRendering");
            internal->vkCmdEndRenderingKHR  = (PFN_vkCmdEndRenderingKHR)*(PFN_vkCmdEndRenderingKHR*)(void**)&untyped;
            
            *pp_next = &vk13_features;
        }
        
    }

    _vk_assert2(vkCreateDevice(target_device.id, &info, &internal->vk_allocs, (VkDevice*)&c->id));
    c->device = target_device;
    
    for (u64 family_index = 0; family_index < OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES; family_index += 1) {
        Oga_Logical_Engines_Create_Desc engines_desc = desc.engine_create_descs[family_index];
        Oga_Logical_Engine_Group *group = &c->engines_by_family[family_index];
        for (u64 engine_index = 0; engine_index < engines_desc.count; engine_index += 1) {
            Oga_Logical_Engine *engine = &group->engines[engine_index];
            vkGetDeviceQueue(
                c->id,
                (u32)family_index,
                (u32)engine_index,
                (VkQueue*)&engine->id
            );
            engine->index = (u32)engine_index;
        }
    }
    
    log(OGA_LOG_VERBOSE, "Initted a Oga_Context for device '%s', api version '%s'", name, api);
    
    return OGA_OK;
}
void oga_uninit_context(Oga_Context *context) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    _vk_assert1(vkDeviceWaitIdle(context->id));
    vkDestroyDevice(context->id, &internal->vk_allocs);
    
    Allocator a = context->state_allocator;
    *context = (Oga_Context){0};
    deallocate(a, context);
}

void oga_wait_engine_idle(Oga_Logical_Engine engine) {
    _vk_assert1(vkQueueWaitIdle(engine.id));
}
void oga_wait_context_idle(Oga_Context *context) {
    _vk_assert1(vkDeviceWaitIdle(context->id));
}

unit_local void _vk_decide_stage_and_access_mask(VkImageLayout layout, VkPipelineStageFlags *stage, VkAccessFlags *access) {
    if (layout == VK_IMAGE_LAYOUT_UNDEFINED) {
        *access = 0;
        *stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    } else if (layout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR) {
        *access = VK_ACCESS_MEMORY_READ_BIT;
        *stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    } else if (layout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL) {
        *access = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        *stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    } else if (layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        *access = VK_ACCESS_SHADER_READ_BIT;
        *stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    } else if (layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        *access = VK_ACCESS_TRANSFER_WRITE_BIT;
        *stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    } else if (layout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) {
        *access = VK_ACCESS_TRANSFER_READ_BIT;
        *stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    } else if (layout == VK_IMAGE_LAYOUT_GENERAL) {
        *access = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
        *stage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
    } else {
        assertmsgs(false, tprint("Unhandled image layout '%u' for transitioning (internal error)\n", layout));
    }
}

unit_local void _vk_image_barrier_helper(VkCommandBuffer cmd, VkImage image, VkImageLayout old_layout, VkImageLayout new_layout) {
    VkPipelineStageFlags src_stage, dst_stage;
    VkAccessFlags src_access, dst_access;
    
    _vk_decide_stage_and_access_mask(old_layout, &src_stage, &src_access);
    _vk_decide_stage_and_access_mask(new_layout, &dst_stage, &dst_access);
    
    VkImageMemoryBarrier barrier = (VkImageMemoryBarrier){0};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = old_layout;
    barrier.newLayout = new_layout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;
    barrier.pNext = 0;
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;

    vkCmdPipelineBarrier(cmd, src_stage, dst_stage, 0, 0, 0, 0, 0, 1, &barrier);
}

Oga_Result oga_init_swapchain(Oga_Context *context, Oga_Swapchain_Desc desc, Oga_Swapchain **swapchain) {
    *swapchain = allocate(context->state_allocator, sizeof(Oga_Swapchain) + sizeof(_Vk_Swapchain_State));
    if (!*swapchain) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }
    **swapchain = (Oga_Swapchain){0};
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    _Vk_Swapchain_State *state = (_Vk_Swapchain_State*)(*swapchain+1);
    
    if (vkCreateSurfaceKHR(desc.surface, &state->vk_surface) != VK_SUCCESS) {
        deallocate((*swapchain)->context->state_allocator, swapchain);
        return OGA_INIT_SWAPCHAIN_ERROR_SURFACE_REJECTED;
    }
    
    (*swapchain)->id = state;
    
    VkSurfaceCapabilitiesKHR cap;
    _vk_assert2(vkGetPhysicalDeviceSurfaceCapabilitiesKHR((VkPhysicalDevice)context->device.id, state->vk_surface, &cap));
    
    u32 image_count = clamp((u32)desc.requested_image_count, cap.minImageCount, min(cap.maxImageCount, MAX_SWAPCHAIN_IMAGES));
    (*swapchain)->image_count = (u64)image_count;
    
    
    VkPresentModeKHR vk_present_mode = VK_PRESENT_MODE_FIFO_KHR;
    if (desc.present_mode == OGA_PRESENT_MODE_IMMEDIATE) {
        VkPresentModeKHR present_modes[32];
        u32 present_mode_count = 32;
        _vk_assert2(vkGetPhysicalDeviceSurfacePresentModesKHR((VkPhysicalDevice)context->device.id, state->vk_surface, &present_mode_count, present_modes));
        for (u32 i = 0; i < present_mode_count; i += 1) {
            if (present_modes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                vk_present_mode = VK_PRESENT_MODE_IMMEDIATE_KHR;
                break;
            }
        }
    } else if (desc.present_mode == OGA_PRESENT_MODE_VSYNC) {
        vk_present_mode = VK_PRESENT_MODE_FIFO_KHR;
        
    } else if (desc.present_mode == OGA_PRESENT_MODE_VSYNC_MAILBOX && context->device.features & OGA_DEVICE_FEATURE_PRESENT_MAILBOX) {
        vk_present_mode = VK_PRESENT_MODE_MAILBOX_KHR;
    } else {
        deallocate((*swapchain)->context->state_allocator, swapchain);
        return OGA_INIT_SWAPCHAIN_ERROR_UNSUPPORTED_PRESENT_MODE;
    }
    
    VkCompositeAlphaFlagBitsKHR composite_alpha = (VkCompositeAlphaFlagBitsKHR)0;
    if (cap.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)
        composite_alpha |= VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    else if (cap.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR )
        composite_alpha |= VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR ;
    else if (cap.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR )
        composite_alpha |= VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR ;
    else if (cap.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR )
        composite_alpha |= VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR ;
    
    VkSwapchainCreateInfoKHR info = (VkSwapchainCreateInfoKHR){0};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    info.flags = 0;
    info.surface = state->vk_surface;
    info.minImageCount = image_count;
    info.imageFormat = _oga_to_vk_format(desc.image_format);
    info.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    info.imageExtent.width = (u32)desc.width;
    info.imageExtent.height = (u32)desc.height;
    info.imageArrayLayers = 0;
    info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    info.preTransform = cap.currentTransform;
    info.compositeAlpha = composite_alpha;
    info.presentMode = vk_present_mode;
    info.clipped = VK_TRUE;
    info.oldSwapchain = 0;
    info.imageArrayLayers = 1;
    
    _vk_assert2(vkCreateSwapchainKHR((VkDevice)context->id, &info, &internal->vk_allocs, &state->vk_swapchain));
    
    VkImage vk_images[MAX_SWAPCHAIN_IMAGES];
    
    vkGetSwapchainImagesKHR((VkDevice)context->id, state->vk_swapchain, (u32*)&(*swapchain)->image_count, vk_images);
    
    (*swapchain)->image_format = desc.image_format;
    
    VkCommandPool transition_pool = 0;
    VkCommandPoolCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    create_info.flags = 0;
    create_info.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    create_info.queueFamilyIndex = (u32)desc.graphics_engine_family_index;

    _vk_assert2(vkCreateCommandPool((VkDevice)context->id, &create_info, &internal->vk_allocs, &transition_pool));
    
    VkCommandBufferAllocateInfo allocate_info = {0};
    allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocate_info.commandPool = transition_pool;
    allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocate_info.commandBufferCount = 1;

    VkCommandBuffer transition_cmd = 0;
    _vk_assert2(vkAllocateCommandBuffers(context->id, &allocate_info, &transition_cmd));
    
    VkCommandBufferBeginInfo begin_info = (VkCommandBufferBeginInfo){0};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    
    _vk_assert2(vkBeginCommandBuffer(transition_cmd, &begin_info));
    
    u64 stride = sizeof(_Vk_Render_Image_State)+sizeof(Oga_Render_Image_View);
    void *image_states_data = allocate(context->state_allocator, stride * (*swapchain)->image_count);
    for (u64 i = 0; i < (*swapchain)->image_count; i += 1) {
    
        _vk_image_barrier_helper(transition_cmd, vk_images[i], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
    
        Oga_Render_Image_View *image = (Oga_Render_Image_View*)((u8*)image_states_data + i*stride);
        *image = (Oga_Render_Image_View){0};
        _Vk_Render_Image_State *image_state = (_Vk_Render_Image_State*)(image+1);
        *image_state = (_Vk_Render_Image_State){0};
        
        image->id = image_state;
        image->memory_pointer = OGA_INTERNALLY_MANAGED_MEMORY_HANDLE;
        image->width = desc.width;
        image->height = desc.height;
        
        image_state->image = vk_images[i];
        
        VkImageViewCreateInfo image_view_info = (VkImageViewCreateInfo){0};
        image_view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        image_view_info.image = image_state->image;
        image_view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        image_view_info.format = _oga_to_vk_format((*swapchain)->image_format);
        image_view_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        image_view_info.subresourceRange.baseMipLevel = 0;
        image_view_info.subresourceRange.levelCount = 1;
        image_view_info.subresourceRange.baseArrayLayer = 0;
        image_view_info.subresourceRange.layerCount = 1;
        
        _vk_assert2(vkCreateImageView((VkDevice)context->id, &image_view_info, &internal->vk_allocs, &image_state->view));
        
        (*swapchain)->images[i] = image;
    }
    
    _vk_assert2(vkEndCommandBuffer(transition_cmd));
    
    VkSubmitInfo submit_info = (VkSubmitInfo){0};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &transition_cmd;
    
    _vk_assert2(vkQueueSubmit(context->engines_by_family[desc.graphics_engine_family_index].engines[0].id, 1, &submit_info, 0));
    
    vkQueueWaitIdle(context->engines_by_family[desc.graphics_engine_family_index].engines[0].id);
    
    vkDestroyCommandPool(context->id, transition_pool, &internal->vk_allocs);
    
    (*swapchain)->context = context;
    
    log(OGA_LOG_VERBOSE, "Initted a swapchain %ix%i", desc.width, desc.height);
    
    return OGA_OK;
}
void oga_uninit_swapchain(Oga_Swapchain *swapchain) {
    _Vk_Swapchain_State *state = (_Vk_Swapchain_State*)(swapchain->id);
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)swapchain->context->internal;
    
    _vk_assert1(vkDeviceWaitIdle(swapchain->context->id));
    
    for (u64 i = 0; i < swapchain->image_count; i += 1) {
        _Vk_Image_State *image_state = (_Vk_Image_State*)(swapchain->images[i]->id);
        vkDestroyImageView((VkDevice)swapchain->context->id, image_state->view, &internal->vk_allocs);
    }
    
    vkDestroySwapchainKHR((VkDevice)swapchain->context->id, state->vk_swapchain, &internal->vk_allocs);
    
    
    VkSurfaceKHR sur = state->vk_surface;
    // Musnt use the vulkan allocation callbacks
    
    vkDestroySurfaceKHR(_vk_instance(), sur, 0);

    Allocator a = swapchain->context->state_allocator;
    
    deallocate(a, swapchain->images[0]);
    
    *swapchain = (Oga_Swapchain){0};
    deallocate(a, swapchain);
}

Oga_Result oga_get_next_swapchain_image(Oga_Swapchain *swapchain, u64 timeout, struct Oga_Gpu_Latch *signal_gpu_latch, struct Oga_Cpu_Latch *signal_cpu_latch, u64 *image_index) {

    _Vk_Swapchain_State *state = (_Vk_Swapchain_State*)swapchain->id;

    u32 index;
    VkResult result = vkAcquireNextImageKHR(swapchain->context->id, state->vk_swapchain, timeout, signal_gpu_latch ? signal_gpu_latch->id : 0, signal_cpu_latch ? signal_cpu_latch->id : 0, &index);
    
    *image_index = (u64)index;
    
    if (result == VK_SUBOPTIMAL_KHR)  return OGA_SUBOPTIMAL;
    else if (result == VK_NOT_READY) return OGA_NOT_READY;
    else if (result == VK_TIMEOUT) return OGA_TIMEOUT;
    else if (result == VK_ERROR_OUT_OF_DATE_KHR) return OGA_ERROR_OUTDATED;
    else if (result == VK_ERROR_SURFACE_LOST_KHR) return OGA_ERROR_SURFACE_LOST;
    
    _vk_assert2(result);
    
    return OGA_OK;
}

Oga_Result oga_submit_present(Oga_Swapchain *swapchain, Oga_Present_Desc desc) {
    
    _Vk_Swapchain_State *state = (_Vk_Swapchain_State*)swapchain->id;
    
    VkSemaphore vk_semaphores[256];
    
    for (u64 i = 0; i < desc.wait_gpu_latch_count; i += 1) {
        vk_semaphores[i] = desc.wait_gpu_latches[i]->id;
    }
    
    VkPresentInfoKHR info = (VkPresentInfoKHR){0};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    info.waitSemaphoreCount = (u32)desc.wait_gpu_latch_count;
    info.pWaitSemaphores = vk_semaphores;
    info.swapchainCount = 1;
    info.pSwapchains = &state->vk_swapchain;
    info.pImageIndices = (u32*)&desc.image_index;
    
    VkResult result = vkQueuePresentKHR(desc.engine.id, &info);
    
    if (result == VK_SUBOPTIMAL_KHR)  return OGA_SUBOPTIMAL;
    else if (result == VK_NOT_READY) return OGA_NOT_READY;
    else if (result == VK_TIMEOUT) return OGA_TIMEOUT;
    else if (result == VK_ERROR_OUT_OF_DATE_KHR) return OGA_ERROR_OUTDATED;
    else if (result == VK_ERROR_SURFACE_LOST_KHR) return OGA_ERROR_SURFACE_LOST;
    
    _vk_assert2(result);
    
    return OGA_OK;
}

Oga_Result oga_init_program(Oga_Context *context, Oga_Program_Desc desc, Oga_Program **program) {
    *program = allocate(context->state_allocator, sizeof(Oga_Program));
    if (!*program) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }
    **program = (Oga_Program){0};
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkShaderModuleCreateInfo info = (VkShaderModuleCreateInfo){0};
    
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.codeSize = (size_t)desc.code_size;
    info.pCode = desc.code;
    
    VkResult result = vkCreateShaderModule((VkDevice)context->id, &info, &internal->vk_allocs, (VkShaderModule*)&(*program)->id);
    
    if (result != VK_SUCCESS) {
        if (result == VK_ERROR_INVALID_SHADER_NV || result == VK_ERROR_INITIALIZATION_FAILED) {
            deallocate(context->state_allocator, *program);
            return OGA_INIT_PROGRAM_ERROR_BAD_CODE;
        }
        _vk_assert2(result);
    }
    
    (*program)->context = context;
    
    return OGA_OK;
}
void oga_uninit_program(Oga_Program *program) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)program->context->internal;
    
    _vk_assert1(vkDeviceWaitIdle(program->context->id));
    vkDestroyShaderModule((VkDevice)program->context->id, (VkShaderModule)program->id, &internal->vk_allocs);
    
    Allocator a = program->context->state_allocator;
    *program = (Oga_Program){0};
    deallocate(a, program);
}

Oga_Result oga_init_binding_list_layout(Oga_Context *context, Oga_Binding_List_Layout_Desc desc, Oga_Binding_List_Layout **layout) {
    *layout = allocate(context->state_allocator, sizeof(Oga_Binding_List_Layout)+sizeof(_Vk_Binding_List_Layout_State)+desc.binding_list_count*sizeof(Oga_Binding_Layout_Entry_Desc));
    if (!*layout) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }
    **layout = (Oga_Binding_List_Layout){0};
    
    (*layout)->context = context;
    
    (*layout)->id = (*layout)+1;
    _Vk_Binding_List_Layout_State *state = (_Vk_Binding_List_Layout_State*)((*layout)->id);
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkDescriptorSetLayoutCreateInfo set_layout_info = (VkDescriptorSetLayoutCreateInfo) {0};
    set_layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    set_layout_info.bindingCount = (u32)desc.binding_count;
    
    VkDescriptorPoolSize pool_sizes[OGA_BINDING_ENUM_MAX];
    pool_sizes[OGA_BINDING_IMAGE].type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
    pool_sizes[OGA_BINDING_SAMPLE_MODE].type = VK_DESCRIPTOR_TYPE_SAMPLER;
    pool_sizes[OGA_BINDING_BLOCK].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    pool_sizes[OGA_BINDING_FBUFFER].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    
    // todo(charlie) #validation
    // - Overlapped binding slots ?
    // - Does the layout match the shader reflection data?
    // - Check shader reflection if a binding is used in a stage which was not specified in stage_flags
    
    VkDescriptorSetLayoutBinding *vk_bindings = PushTempBuffer(VkDescriptorSetLayoutBinding, desc.binding_count);
    for (u64 j = 0; j < desc.binding_count; j += 1) {
        switch (desc.bindings[j].kind) {
        case OGA_BINDING_IMAGE: 
            vk_bindings[j].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE; 
            pool_sizes[OGA_BINDING_IMAGE].descriptorCount += (u32)desc.binding_list_count;
            break;
        case OGA_BINDING_FBUFFER: 
            vk_bindings[j].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE; 
            pool_sizes[OGA_BINDING_FBUFFER].descriptorCount += (u32)desc.binding_list_count;
            break;
        case OGA_BINDING_SAMPLE_MODE: 
            vk_bindings[j].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER; 
            pool_sizes[OGA_BINDING_SAMPLE_MODE].descriptorCount += (u32)desc.binding_list_count;
            break;
        case OGA_BINDING_BLOCK: 
            vk_bindings[j].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; 
            pool_sizes[OGA_BINDING_BLOCK].descriptorCount += (u32)desc.binding_list_count;
            break;
        case OGA_BINDING_ENUM_MAX: // fallthrough
        default:
            return OGA_INIT_RENDER_PASS_ERROR_INVALID_PROGRAM_BINDING_KIND_ENUM;
        }
        vk_bindings[j].binding = (u32)desc.bindings[j].binding_slot;
        vk_bindings[j].descriptorCount = (u32)desc.bindings[j].binding_count;
        
        vk_bindings[j].stageFlags = 0;
        if (desc.bindings[j].stage_flags & OGA_PROGRAM_STAGE_VERTEX)
            vk_bindings[j].stageFlags |= VK_SHADER_STAGE_VERTEX_BIT;
        if (desc.bindings[j].stage_flags & OGA_PROGRAM_STAGE_FRAGMENT)
            vk_bindings[j].stageFlags |= VK_SHADER_STAGE_FRAGMENT_BIT;
        if (desc.bindings[j].stage_flags & OGA_PROGRAM_STAGE_COMPUTE)
            vk_bindings[j].stageFlags |= VK_SHADER_STAGE_COMPUTE_BIT;
            
        if (vk_bindings[j].stageFlags == 0) {
            return OGA_INIT_BINDING_LIST_LAYOUT_ERROR_MISSING_STAGE_FLAGS;
        }
        
        vk_bindings[j].pImmutableSamplers = 0;
    }
    
    VkDescriptorPoolSize actual_pool_sizes[OGA_BINDING_ENUM_MAX];
    u64 actual_pool_sizes_next = 0;
    for (u64 i = 0; i < OGA_BINDING_ENUM_MAX; i += 1) {
        if (pool_sizes[i].descriptorCount > 0) {
            actual_pool_sizes[actual_pool_sizes_next++] = pool_sizes[i];
        }
    }
    
    
    set_layout_info.pBindings = vk_bindings;
    
    _vk_assert2(vkCreateDescriptorSetLayout(context->id, &set_layout_info, &internal->vk_allocs, &state->layout));
    
    VkDescriptorPoolCreateInfo pool_info = (VkDescriptorPoolCreateInfo){0};
    pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.maxSets = (u32)desc.binding_list_count;
    pool_info.poolSizeCount = (u32)actual_pool_sizes_next;
    pool_info.pPoolSizes = actual_pool_sizes;
    _vk_assert2(vkCreateDescriptorPool(context->id, &pool_info, &internal->vk_allocs, &state->pool));
    
    (*layout)->bindings = (Oga_Binding_Layout_Entry_Desc*)((state)+1);
    memcpy((*layout)->bindings, desc.bindings, desc.binding_list_count*sizeof(Oga_Binding_Layout_Entry_Desc));
    (*layout)->binding_count = desc.binding_count;
    (*layout)->binding_list_count = desc.binding_list_count;
    
    return OGA_OK;
}
void oga_uninit_binding_list_layout(Oga_Binding_List_Layout *layout) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)layout->context->internal;
    
    _Vk_Binding_List_Layout_State *state = (_Vk_Binding_List_Layout_State*)((layout)->id);
    
    _vk_assert1(vkDeviceWaitIdle(layout->context->id));
    vkDestroyDescriptorPool(layout->context->id, state->pool, &internal->vk_allocs);
    vkDestroyDescriptorSetLayout((VkDevice)layout->context->id, state->layout, &internal->vk_allocs);
    
    Allocator a = layout->context->state_allocator;
    *layout = (Oga_Binding_List_Layout){0};
    deallocate(a, layout);
}

Oga_Result oga_push_binding_list(Oga_Binding_List_Layout *layout, Oga_Binding_List_Desc desc, Oga_Binding_List **list) {
    *list = allocate(layout->context->state_allocator, sizeof(Oga_Binding_List)); // todo(charlie #leak this isn't freed
    if (!*list) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }
    **list = (Oga_Binding_List){0};
    
    (*list)->context = layout->context;
    
    _Vk_Binding_List_Layout_State *layout_state = (_Vk_Binding_List_Layout_State*)((layout)->id);
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)layout->context->internal;
    
    if (desc.binding_count > layout->binding_count) {
        return OGA_PUSH_BINDING_LIST_ERROR_LAYOUT_COUNT_MISMATCH;
    }
    // todo(charlie) #validation 
    // - check that binding list is compliant with layout
    // - check allocated_lists_count was not overflown
    // - Notify if any item is null where a binding is expected
    
    
    VkDescriptorSetAllocateInfo info = (VkDescriptorSetAllocateInfo){0};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    info.descriptorPool = layout_state->pool;
    info.descriptorSetCount = 1;
    info.pSetLayouts = &layout_state->layout;
    _vk_assert2(vkAllocateDescriptorSets(layout->context->id, &info, (VkDescriptorSet*)&(*list)->id));
    
    layout->allocated_lists_count += 1;
    
    VkWriteDescriptorSet *writes = PushTempBuffer(VkWriteDescriptorSet, desc.binding_count);
    
    // todo(charlie) #validation
    
    for (u64 i = 0; i < desc.binding_count; i += 1) {
        writes[i] = (VkWriteDescriptorSet){0};
        writes[i].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[i].dstSet = (*list)->id;
        writes[i].dstBinding = (u32)desc.bindings[i].binding_slot;
        writes[i].dstArrayElement = (u32)desc.bindings[i].array_index;
        writes[i].descriptorCount = (u32)desc.bindings[i].count;
        switch (desc.bindings[i].kind) {
            case OGA_BINDING_IMAGE: {
                writes[i].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
                assert(desc.bindings[i].count);
                VkDescriptorImageInfo *image_infos = PushTempBuffer(VkDescriptorImageInfo, desc.bindings[i].count);
                for (u64 j = 0; j < desc.bindings[i].count; j += 1) {
                    _Vk_Image_State* image_state = (_Vk_Image_State*)desc.bindings[i].images[j]->id;                    
                    image_infos[j] = (VkDescriptorImageInfo){0};
                    image_infos[j].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
                    image_infos[j].imageView = image_state->view;
                }
                writes[i].pImageInfo = image_infos;
                break;
            }
            case OGA_BINDING_FBUFFER: {
                writes[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
                assert(desc.bindings[i].count);
                VkDescriptorImageInfo *image_infos = PushTempBuffer(VkDescriptorImageInfo, desc.bindings[i].count);
                for (u64 j = 0; j < desc.bindings[i].count; j += 1) {
                    _Vk_Image_State* image_state = (_Vk_Image_State*)desc.bindings[i].fbuffers[j]->id;                    
                    image_infos[j] = (VkDescriptorImageInfo){0};
                    image_infos[j].imageLayout = VK_IMAGE_LAYOUT_GENERAL;
                    image_infos[j].imageView = image_state->view;
                }
                writes[i].pImageInfo = image_infos;
                break;
            }
            case OGA_BINDING_BLOCK: {
                writes[i].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                assert(desc.bindings[i].count);
                
                VkDescriptorBufferInfo *buffer_infos = PushTempBuffer(VkDescriptorBufferInfo, desc.bindings[i].count);
                for (u64 j = 0; j < desc.bindings[i].count; j += 1) {
                    buffer_infos[j].buffer = desc.bindings[i].blocks[j]->id;
                    buffer_infos[j].offset = 0;
                    buffer_infos[j].range = desc.bindings[i].blocks[j]->size;
                }
                writes[i].pBufferInfo = buffer_infos;
                break;
            }
            case OGA_BINDING_SAMPLE_MODE: {
                writes[i].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
                assert(desc.bindings[i].count);
                
                // todo(charlie) table of samplers (we are currently just leakign sampelrs)
                
                VkDescriptorImageInfo *image_infos = PushTempBuffer(VkDescriptorImageInfo, desc.bindings[i].count);
                for (u64 j = 0; j < desc.bindings[i].count; j += 1) {
                    Oga_Sample_Mode_Desc mode = desc.bindings[i].sample_modes[j];
                    VkSampler sampler = 0;
                    VkSamplerCreateInfo sampler_info = (VkSamplerCreateInfo){0};
                    sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
                    
                    switch (mode.magnification_filter) {
                    case OGA_SAMPLE_FILTER_LINEAR: sampler_info.magFilter = VK_FILTER_LINEAR; break;
                    case OGA_SAMPLE_FILTER_NEAREST: sampler_info.magFilter = VK_FILTER_NEAREST; break;
                    default:
                        assert(false); break; // todo(charlie) #validation #error
                    }
                    switch (mode.minification_filter) {
                    case OGA_SAMPLE_FILTER_LINEAR: sampler_info.minFilter = VK_FILTER_LINEAR; break;
                    case OGA_SAMPLE_FILTER_NEAREST: sampler_info.minFilter = VK_FILTER_NEAREST; break;
                    default:
                        assert(false); break; // todo(charlie) #validation #error
                    }
                    
                    switch (mode.address_mode_u) {
                    case OGA_SAMPLE_ADDRESS_MODE_REPEAT:          sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT; break;
                    case OGA_SAMPLE_ADDRESS_MODE_MIRRORED_REPEAT: sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT; break;
                    case OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_EDGE:   sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE; break;
                    case OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_BORDER: sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER; break;
                    default:
                        assert(false); break; // todo(charlie) #validation #error
                    }
                    switch (mode.address_mode_v) {
                    case OGA_SAMPLE_ADDRESS_MODE_REPEAT:          sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT; break;
                    case OGA_SAMPLE_ADDRESS_MODE_MIRRORED_REPEAT: sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT; break;
                    case OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_EDGE:   sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE; break;
                    case OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_BORDER: sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER; break;
                    default:
                        assert(false); break; // todo(charlie) #validation #error
                    }
                    switch (mode.address_mode_w) {
                    case OGA_SAMPLE_ADDRESS_MODE_REPEAT:          sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT; break;
                    case OGA_SAMPLE_ADDRESS_MODE_MIRRORED_REPEAT: sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT; break;
                    case OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_EDGE:   sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE; break;
                    case OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_BORDER: sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER; break;
                    default:
                        assert(false); break; // todo(charlie) #validation #error
                    }
                    
                    sampler_info.anisotropyEnable = mode.max_anisotropy > 0.0f ? VK_TRUE : VK_FALSE;
                    sampler_info.maxAnisotropy = mode.max_anisotropy;
                    
                    _vk_assert2(vkCreateSampler(layout->context->id, &sampler_info, &internal->vk_allocs, &sampler));
                    
                    image_infos[j] = (VkDescriptorImageInfo){0};
                    image_infos[j].sampler = sampler;
                }
                writes[i].pImageInfo = image_infos;
                break;
            }
            case OGA_BINDING_ENUM_MAX: // fallthrough
            default:
                assert(false); // todo(charlie) #validation #error
        }
    }
    
    vkUpdateDescriptorSets(layout->context->id, (u32)desc.binding_count, writes, 0, 0);
    
    return OGA_OK;
}

Oga_Result oga_init_render_passes(Oga_Context *context, Oga_Render_Pass_Desc* descs, Oga_Render_Pass **render_passes, u64 render_pass_count) {

    for (u64 i = 0; i < render_pass_count; i += 1) {
        render_passes[i] = (Oga_Render_Pass*)allocate(context->state_allocator, sizeof(Oga_Render_Pass)+sizeof(_Vk_Render_Pass_State));
    }

    VkGraphicsPipelineCreateInfo *infos = PushTempBuffer(VkGraphicsPipelineCreateInfo, render_pass_count);
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    // todo(charlie)
    // We use a lot of temporary storage here, so we would probably want to reset it back to where it was before,
    // once that's implemented ..
    for (u64 i = 0; i < render_pass_count; i += 1) {
    
        Oga_Render_Pass_Desc desc = descs[i];
        
        VkFormat *vk_formats = PushTempBuffer(VkFormat, desc.attachment_count);
        for (u64 j = 0; j < desc.attachment_count; j += 1) {
            vk_formats[j] = _oga_to_vk_format(desc.attachment_formats[j]);
        }
        
        VkPipelineRenderingCreateInfoKHR *rendering = PushTemp(VkPipelineRenderingCreateInfoKHR);
        *rendering = (VkPipelineRenderingCreateInfoKHR){0};
        rendering->sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
        rendering->pNext = 0;
        rendering->viewMask = 0;
        rendering->colorAttachmentCount = (u32)desc.attachment_count;
        rendering->pColorAttachmentFormats = vk_formats;
        
        VkPipelineCreateFlags pipeline_flags = (VkPipelineCreateFlags)(int)0;
        if (desc.flags & OGA_RENDER_PASS_INHERITANCE_PARENT) pipeline_flags |= VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT;
        if (desc.flags & OGA_RENDER_PASS_INHERITANCE_CHILD)  pipeline_flags |= VK_PIPELINE_CREATE_DERIVATIVE_BIT;
        
        char *vert_entry = PushTempBuffer(char, desc.vertex_program_entry_point.count+1);
        char *frag_entry = PushTempBuffer(char, desc.fragment_program_entry_point.count+1);
        memcpy(vert_entry, desc.vertex_program_entry_point.data, desc.vertex_program_entry_point.count+1);
        memcpy(frag_entry, desc.fragment_program_entry_point.data, desc.fragment_program_entry_point.count+1);
        vert_entry[desc.vertex_program_entry_point.count] = 0;
        frag_entry[desc.fragment_program_entry_point.count] = 0;
        
        VkPipelineShaderStageCreateInfo *stages = PushTempBuffer(VkPipelineShaderStageCreateInfo, 2);
        stages[0] = (VkPipelineShaderStageCreateInfo){0};
        stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
        stages[0].module = (VkShaderModule)desc.vertex_program->id;
        stages[0].pName = vert_entry;
        
        stages[1] = (VkPipelineShaderStageCreateInfo){0};
        stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        stages[1].module = (VkShaderModule)desc.fragment_program->id;
        stages[1].pName = frag_entry;
        
        VkPipelineInputAssemblyStateCreateInfo *ia = PushTemp(VkPipelineInputAssemblyStateCreateInfo);
        *ia = (VkPipelineInputAssemblyStateCreateInfo){0};
        ia->sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        ia->topology = (VkPrimitiveTopology)desc.topology; // #Volatile values must map to same as vulkan equivalents
        
        VkPipelineTessellationStateCreateInfo *tessellation = PushTemp(VkPipelineTessellationStateCreateInfo);
        *tessellation = (VkPipelineTessellationStateCreateInfo){0};
        tessellation->sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
        tessellation->patchControlPoints = 0;
        
        VkPipelineViewportStateCreateInfo *viewport = PushTemp(VkPipelineViewportStateCreateInfo);
        *viewport = (VkPipelineViewportStateCreateInfo){0};
        viewport->sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewport->viewportCount = 1;
        viewport->scissorCount = 1; 
        viewport->pViewports = 0;
        viewport->pScissors = 0; 
        
        VkFrontFace front_face = VK_FRONT_FACE_CLOCKWISE;
        VkCullModeFlags cull_mode = VK_CULL_MODE_BACK_BIT;
        
        switch(desc.cull_mode) {
            case OGA_CULL_NONE:
                cull_mode = VK_CULL_MODE_NONE;
                break;
            case OGA_CULL_CLOCKWISE:
                front_face = VK_FRONT_FACE_CLOCKWISE;
                break;
            case OGA_CULL_COUNTER_CLOCKWISE:
                front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE;
                break;
            
            default: assert(false);
        }
        
        VkBool32 depth_clamp_enable = (desc.flags & OGA_RENDER_PASS_DISABLE_DEPTH_CLAMP) == 0;

        if (depth_clamp_enable && !(context->device.features & OGA_DEVICE_FEATURE_DEPTH_CLAMP)) {
            depth_clamp_enable = false;
            log(OGA_LOG_VERBOSE, "Depth clamp was flagged as enabled, but device is missing feature flag OGA_RENDER_PASS_DISABLE_DEPTH_CLAMP");
        }
        
        VkPipelineRasterizationStateCreateInfo *rasterization = PushTemp(VkPipelineRasterizationStateCreateInfo);
        *rasterization = (VkPipelineRasterizationStateCreateInfo){0};
        rasterization->sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterization->depthClampEnable = depth_clamp_enable;
        rasterization->rasterizerDiscardEnable = VK_FALSE;
        rasterization->polygonMode = VK_POLYGON_MODE_FILL;
        rasterization->cullMode = cull_mode;
        rasterization->frontFace = front_face;
        rasterization->depthBiasEnable = VK_FALSE;
        rasterization->lineWidth = desc.line_width;
        
        VkSampleCountFlagBits samples = (VkSampleCountFlagBits)OGA_SAMPLE_COUNT_1;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_1)  samples |= VK_SAMPLE_COUNT_1_BIT;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_2)  samples |= VK_SAMPLE_COUNT_2_BIT;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_4)  samples |= VK_SAMPLE_COUNT_4_BIT;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_8)  samples |= VK_SAMPLE_COUNT_8_BIT;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_16) samples |= VK_SAMPLE_COUNT_16_BIT;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_32) samples |= VK_SAMPLE_COUNT_32_BIT;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_64) samples |= VK_SAMPLE_COUNT_64_BIT;
        
        
        VkPipelineMultisampleStateCreateInfo *multisample = PushTemp(VkPipelineMultisampleStateCreateInfo);
        *multisample = (VkPipelineMultisampleStateCreateInfo){0};
        multisample->sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisample->rasterizationSamples = samples;
        
        VkPipelineDepthStencilStateCreateInfo *depth_stencil = PushTemp(VkPipelineDepthStencilStateCreateInfo);
        *depth_stencil = (VkPipelineDepthStencilStateCreateInfo){0};
        depth_stencil->sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        
        // todo(charlie) allow enabling driver blending
        VkPipelineColorBlendAttachmentState *blend_attachment = PushTemp(VkPipelineColorBlendAttachmentState);
        *blend_attachment = (VkPipelineColorBlendAttachmentState){0};
        //blend_attachment->blendEnable = true;
        blend_attachment->srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        blend_attachment->dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        blend_attachment->colorBlendOp = VK_BLEND_OP_ADD;
        blend_attachment->srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        blend_attachment->dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        blend_attachment->alphaBlendOp = VK_BLEND_OP_ADD;
        blend_attachment->colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        
        VkPipelineColorBlendStateCreateInfo *blend = PushTemp(VkPipelineColorBlendStateCreateInfo);
        *blend = (VkPipelineColorBlendStateCreateInfo){0};
        blend->sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        blend->attachmentCount = 1;
        blend->pAttachments = blend_attachment;
        blend->blendConstants[0] = 0.0f;
        blend->blendConstants[1] = 0.0f;
        blend->blendConstants[2] = 0.0f;
        blend->blendConstants[3] = 0.0f;
        
        VkDynamicState dynamic_states[] = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
        };
        VkPipelineDynamicStateCreateInfo *dynamic = PushTemp(VkPipelineDynamicStateCreateInfo);
        *dynamic = (VkPipelineDynamicStateCreateInfo){0};
        dynamic->sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamic->dynamicStateCount = sizeof(dynamic_states)/sizeof(VkDynamicState);
        dynamic->pDynamicStates = dynamic_states;
                 
        VkPipelineLayout layout;
        VkPipelineLayoutCreateInfo *layout_info = PushTemp(VkPipelineLayoutCreateInfo);
        *layout_info = (VkPipelineLayoutCreateInfo){0};
        layout_info->sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        layout_info->pSetLayouts 
            = desc.binding_list_layout ? &((_Vk_Binding_List_Layout_State*)desc.binding_list_layout->id)->layout : 0;
        layout_info->setLayoutCount = desc.binding_list_layout ? 1 : 0;
        
        _vk_assert2(vkCreatePipelineLayout((VkDevice)context->id, layout_info, &internal->vk_allocs, &layout));
        
        VkPipeline base_pipeline = 0;
        if (desc.base) {
            _Vk_Render_Pass_State *state = (_Vk_Render_Pass_State*)desc.base->id;
            base_pipeline = state->pipeline;
        }
        
        s32 base_index = (s32)desc.base_index;
         
        VkVertexInputBindingDescription bindings[OGA_MAX_VERTEX_BINDING_COUNT];
        VkVertexInputAttributeDescription attributes[OGA_MAX_VERTEX_ATTRIBUTE_COUNT];
        
        for (u64 j = 0; j < desc.vertex_input_layout.binding_count; j += 1) {
            bindings[j].binding = (u32)i;
            bindings[j].stride = (u32)desc.vertex_input_layout.bindings[j].stride;
            switch (desc.vertex_input_layout.bindings[j].input_rate) {
            case OGA_VERTEX_INPUT_RATE_VERTEX: bindings[j].inputRate = VK_VERTEX_INPUT_RATE_VERTEX; break;
            case OGA_VERTEX_INPUT_RATE_INSTANCE: bindings[j].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE; break;
            default:
                return OGA_ERROR_INVALID_INPUT_RATE_ENUM;
            }
        }
        for (u64 j = 0; j < desc.vertex_input_layout.attribute_count; j += 1) {
            attributes[j].binding = (u32)desc.vertex_input_layout.attributes[j].binding;
            attributes[j].location = (u32)desc.vertex_input_layout.attributes[j].location;
            attributes[j].offset = (u32)desc.vertex_input_layout.attributes[j].offset;
            attributes[j].format = _oga_vertex_attribute_type_to_vk_format(desc.vertex_input_layout.attributes[j].type);
        }
        
        // todo(charlie) #validation generate a detailed error for mismatch between vertex program input layout
        // and this input layout.
        VkPipelineVertexInputStateCreateInfo *vertex_input = PushTemp(VkPipelineVertexInputStateCreateInfo);
        *vertex_input = (VkPipelineVertexInputStateCreateInfo) {0};
        vertex_input->sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertex_input->vertexBindingDescriptionCount = (u32)desc.vertex_input_layout.binding_count;
        vertex_input->vertexAttributeDescriptionCount = (u32)desc.vertex_input_layout.attribute_count;
        vertex_input->pVertexBindingDescriptions = bindings;
        vertex_input->pVertexAttributeDescriptions = attributes;
    
        VkGraphicsPipelineCreateInfo info = (VkGraphicsPipelineCreateInfo) {0};
        info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        info.pNext = rendering;
        info.flags = pipeline_flags;
        info.stageCount = 2;
        info.pStages = stages;
        info.pVertexInputState = vertex_input;
        info.pInputAssemblyState = ia;
        info.pTessellationState = tessellation;
        info.pViewportState = viewport;
        info.pRasterizationState = rasterization;
        info.pMultisampleState = multisample;
        info.pDepthStencilState = depth_stencil;
        info.pColorBlendState = blend;
        info.pDynamicState = dynamic;
        info.layout = layout;
        info.renderPass = 0; // #Portability dynamic rendering
        info.subpass = 0;
        info.basePipelineHandle = base_pipeline;
        info.basePipelineIndex = base_index;
        
        infos[i] = info;
    }
    
    VkPipeline *vk_pipelines = PushTempBuffer(VkPipeline, render_pass_count);
    assert(vk_pipelines);
    _vk_assert2(vkCreateGraphicsPipelines((VkDevice)context->id, 0, (u32)render_pass_count, infos, &internal->vk_allocs, vk_pipelines));
    
    // These need to be allocated one by one because render passes needs to be able to be freed one by one
    for (u64 i = 0; i < render_pass_count; i += 1) {
        render_passes[i]->context = context;
        _Vk_Render_Pass_State *state = (_Vk_Render_Pass_State*)(render_passes[i]+1);
        render_passes[i]->id = state;
        
        state->pipeline = vk_pipelines[i];
        state->layout = infos[i].layout;
        
        render_passes[i]->vertex_input_layout = descs[i].vertex_input_layout;
    }
    
    return OGA_OK;
}

Oga_Result oga_init_render_pass(Oga_Context *context, Oga_Render_Pass_Desc desc, Oga_Render_Pass **render_pass) {
    return oga_init_render_passes(context, &desc, render_pass, 1);
} 
void oga_uninit_render_pass(Oga_Render_Pass *render_pass) {
    _Vk_Render_Pass_State *state = (_Vk_Render_Pass_State*)render_pass->id;
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)render_pass->context->internal;
    
    _vk_assert1(vkDeviceWaitIdle(render_pass->context->id));
    vkDestroyPipeline((VkDevice)render_pass->context->id, state->pipeline, &internal->vk_allocs);
    vkDestroyPipelineLayout((VkDevice)render_pass->context->id, state->layout, &internal->vk_allocs);
    
    Allocator a = render_pass->context->state_allocator;
    *render_pass = (Oga_Render_Pass){0};
    deallocate(a, render_pass);
} 

Oga_Result oga_init_gpu_latch(Oga_Context *context, Oga_Gpu_Latch **gpu_latch) {
    *gpu_latch = allocate(context->state_allocator, sizeof(Oga_Gpu_Latch) + sizeof(VkSemaphore));
    if (!*gpu_latch) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **gpu_latch = (Oga_Gpu_Latch){0};
    (*gpu_latch)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;

    VkSemaphoreCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    _vk_assert2(vkCreateSemaphore((VkDevice)context->id, &create_info, &internal->vk_allocs, (VkSemaphore*)&(*gpu_latch)->id));
    
    return OGA_OK;
}

void oga_uninit_gpu_latch(Oga_Gpu_Latch *gpu_latch) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)gpu_latch->context->internal;
    _vk_assert1(vkDeviceWaitIdle(gpu_latch->context->id));
    vkDestroySemaphore((VkDevice)gpu_latch->context->id, (VkSemaphore)gpu_latch->id, &internal->vk_allocs);

    Allocator a = gpu_latch->context->state_allocator;
    *gpu_latch = (Oga_Gpu_Latch){0};
    deallocate(a, gpu_latch);
}

// Cpu latch; for synchronizing CPU with GPU. Signalled on GPU, waited on CPU.
Oga_Result oga_init_cpu_latch(Oga_Context *context, Oga_Cpu_Latch **cpu_latch, bool start_signaled) {
    *cpu_latch = allocate(context->state_allocator, sizeof(Oga_Cpu_Latch) + sizeof(VkFence));
    if (!*cpu_latch) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **cpu_latch = (Oga_Cpu_Latch){0};
    (*cpu_latch)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;

    VkFenceCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    create_info.flags = start_signaled ? VK_FENCE_CREATE_SIGNALED_BIT : 0;

    _vk_assert2(vkCreateFence((VkDevice)context->id, &create_info, &internal->vk_allocs, (VkFence*)&(*cpu_latch)->id));

    return OGA_OK;
}

void oga_uninit_cpu_latch(Oga_Cpu_Latch *cpu_latch) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)cpu_latch->context->internal;
    _vk_assert1(vkDeviceWaitIdle(cpu_latch->context->id));
    vkDestroyFence((VkDevice)cpu_latch->context->id, (VkFence)cpu_latch->id, &internal->vk_allocs);

    Allocator a = cpu_latch->context->state_allocator;
    *cpu_latch = (Oga_Cpu_Latch){0};
    deallocate(a, cpu_latch);
}

Oga_Result oga_wait_latch(Oga_Cpu_Latch *cpu_latch) {
    _vk_assert2(vkWaitForFences((VkDevice)cpu_latch->context->id, 1, (VkFence*)&cpu_latch->id, VK_TRUE, UINT64_MAX));
    
    return OGA_OK;
}

Oga_Result oga_reset_latch(Oga_Cpu_Latch *cpu_latch) {
    _vk_assert2(vkResetFences((VkDevice)cpu_latch->context->id, 1, (VkFence*)&cpu_latch->id));

    return OGA_OK;
}

Oga_Result oga_allocate_memory(Oga_Context *context, u64 size, Oga_Memory_Property_Flag properties, Oga_Memory_Usage usage, Oga_Memory_Pointer *result) {
    *result = (Oga_Memory_Pointer){0};
    (result)->context = context;
    
    result->id = New(context->state_allocator, _Vk_Memory_State);
    _Vk_Memory_State *state = (_Vk_Memory_State*)result->id;
    *state = (_Vk_Memory_State){0};
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkPhysicalDeviceMemoryProperties props;
    vkGetPhysicalDeviceMemoryProperties(context->device.id, &props);
    
    u32 index = U32_MAX;
    u64 heap_index = 0;
    for (u32 i = 0; i < props.memoryTypeCount; i += 1) {
        VkMemoryType type = props.memoryTypes[i];
        
        if ((properties & OGA_MEMORY_PROPERTY_GPU_LOCAL) && !(type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT))
            continue;
        if ((properties & OGA_MEMORY_PROPERTY_GPU_TO_CPU_MAPPABLE) && !(type.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT))
            continue;
        if ((properties & OGA_MEMORY_PROPERTY_GPU_TO_CPU_REFLECTED) && !(type.propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
            continue;
        if ((properties & OGA_MEMORY_PROPERTY_GPU_TO_CPU_CACHED) && !(type.propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT))
            continue;
        
        
        
        if (usage != (context->device.memory_heaps[type.heapIndex].supported_usage_flags & usage))
            continue;
        
        // todo(charlie)
        // Find memory type that is the closest match.
        // We might want to use a memory type that has only the GPU_LOCAL flag, as some
        // drivers may use this to optimize.
        index = i;
        heap_index = (u64)type.heapIndex;
        break;
    }
    
    if (index == U32_MAX) 
        return OGA_ALLOCATE_MEMORY_ERROR_INVALID_PROPERTIES_AND_USAGE_COMBINATION;
    
    VkMemoryAllocateInfo info = (VkMemoryAllocateInfo){0};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    info.allocationSize = (VkDeviceSize)size;
    info.memoryTypeIndex = index;
    _vk_assert2(vkAllocateMemory(context->id, &info, &internal->vk_allocs, &(state)->memory));
    
    state->memory_type_index = index;
    
    result->properties = properties;
    result->offset = 0;
    result->size = size;
    result->usage = usage;
    result->heap_index = heap_index;
    
    VkBufferCreateInfo copy_buffer_info = (VkBufferCreateInfo){0};
    copy_buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    copy_buffer_info.size = (VkDeviceSize)size;
    copy_buffer_info.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    copy_buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    _vk_assert2(vkCreateBuffer(context->id, &copy_buffer_info, &internal->vk_allocs, &state->raw_view));
    
    _vk_assert2(vkBindBufferMemory(context->id, state->raw_view, state->memory, 0));
    
    return OGA_OK;
}
void oga_deallocate_memory(Oga_Memory_Pointer ptr) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)ptr.context->internal;
    _Vk_Memory_State *state = (_Vk_Memory_State*)ptr.id;
    _vk_assert1(vkDeviceWaitIdle(ptr.context->id));
    
    vkDestroyBuffer(ptr.context->id, state->raw_view, &internal->vk_allocs);
    if (state->last_image_optimal_view)
        vkDestroyImage(ptr.context->id, state->last_image_optimal_view, &internal->vk_allocs);
    vkFreeMemory(ptr.context->id, state->memory, &internal->vk_allocs);
}
Oga_Result oga_map_memory(Oga_Memory_Pointer ptr, u64 size, void **mapped_mem) {
    _Vk_Memory_State *state = (_Vk_Memory_State*)ptr.id;
    _vk_assert2(vkMapMemory(ptr.context->id, state->memory, (VkDeviceSize)ptr.offset, (VkDeviceSize)size, 0, mapped_mem));
    return OGA_OK;
}
void oga_unmap_memory(Oga_Memory_Pointer ptr) {
    _Vk_Memory_State *state = (_Vk_Memory_State*)ptr.id;
    vkUnmapMemory(ptr.context->id, state->memory);
}
Oga_Result oga_memory_offset(Oga_Memory_Pointer ptr, s64 offset, Oga_Memory_Pointer *result_ptr) {
    *result_ptr = ptr;
    
    s64 new_offset = (s64)result_ptr->offset + offset;
    
    if (new_offset < 0) {
        return OGA_MEMORY_OFFSET_ERROR_UNDERFLOW;
    }
    if (new_offset >= (s64)result_ptr->size) {
        return OGA_MEMORY_OFFSET_ERROR_UNDERFLOW;
    }
    
    result_ptr->offset = (u64)new_offset;
    
    return OGA_OK;
}

Oga_Result oga_init_vertex_list_view(Oga_Context *context, Oga_Memory_View_Desc desc, Oga_Vertex_List_View **vlist) {
    *vlist = allocate(context->state_allocator, sizeof(Oga_Vertex_List_View));
    if (!*vlist) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **vlist = (Oga_Vertex_List_View){0};
    (*vlist)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkBufferCreateInfo info = (VkBufferCreateInfo){0};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    info.size = (VkDeviceSize)desc.size;
    info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    _vk_assert2(vkCreateBuffer(context->id, &info, &internal->vk_allocs, (VkBuffer*)&(*vlist)->id));
    
    (*vlist)->size = desc.size;
    (*vlist)->memory_pointer = desc.memory_pointer;
    
    _Vk_Memory_State *mem_state = (_Vk_Memory_State*)desc.memory_pointer.id;
    
    if (!(context->device.memory_heaps[desc.memory_pointer.heap_index].supported_usage_flags & OGA_MEMORY_USAGE_VERTEX_LIST)) {
        return OGA_INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT;
    }
    
    _vk_assert2(vkBindBufferMemory(context->id, (*vlist)->id, mem_state->memory, desc.memory_pointer.offset));
    
    return OGA_OK;
}
void oga_uninit_vertex_list_view(Oga_Vertex_List_View *vlist) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)vlist->context->internal;
    _vk_assert1(vkDeviceWaitIdle(vlist->context->id));
    
    vkDestroyBuffer(vlist->context->id, vlist->id, &internal->vk_allocs);
    
    Allocator a = vlist->context->state_allocator;
    *vlist = (Oga_Vertex_List_View){0};
    deallocate(a, vlist);
}

Oga_Result oga_init_index_list_view(Oga_Context *context, Oga_Memory_View_Desc desc, Oga_Index_List_View **ilist) {
    *ilist = allocate(context->state_allocator, sizeof(Oga_Index_List_View));
    if (!*ilist) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **ilist = (Oga_Index_List_View){0};
    (*ilist)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkBufferCreateInfo info = (VkBufferCreateInfo){0};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    info.size = (VkDeviceSize)desc.size;
    info.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    _vk_assert2(vkCreateBuffer(context->id, &info, &internal->vk_allocs, (VkBuffer*)&(*ilist)->id));
    
    (*ilist)->size = desc.size;
    (*ilist)->memory_pointer = desc.memory_pointer;
    
    _Vk_Memory_State *mem_state = (_Vk_Memory_State*)desc.memory_pointer.id;
    
    if (!(context->device.memory_heaps[desc.memory_pointer.heap_index].supported_usage_flags & OGA_MEMORY_USAGE_INDEX_LIST)) {
        return OGA_INIT_INDEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT;
    }
    
    _vk_assert2(vkBindBufferMemory(context->id, (*ilist)->id, mem_state->memory, desc.memory_pointer.offset));
    
    return OGA_OK;
}
void oga_uninit_index_list_view(Oga_Index_List_View *ilist) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)ilist->context->internal;
    _vk_assert1(vkDeviceWaitIdle(ilist->context->id));
    
    vkDestroyBuffer(ilist->context->id, ilist->id, &internal->vk_allocs);
    
    Allocator a = ilist->context->state_allocator;
    *ilist = (Oga_Index_List_View){0};
    deallocate(a, ilist);
}

unit_local Oga_Result _oga_make_vk_image(Oga_Context *context, _Vk_Image_State *state, Oga_Image_View_Desc desc, VkImageUsageFlags usage, VkImageLayout initial_layout) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;

    VkImageType image_type = 0;
    switch (desc.dimensions) {
        case OGA_1D: image_type = VK_IMAGE_TYPE_1D; break;
        case OGA_2D: image_type = VK_IMAGE_TYPE_2D; break;
        case OGA_3D: image_type = VK_IMAGE_TYPE_3D; break;
        default: return OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM;
    }
    
    VkImageCreateInfo info = (VkImageCreateInfo) {0};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.imageType = image_type;
    info.format = _oga_to_vk_format(desc.format);
    info.extent.width = (u32)desc.width;
    info.extent.height = desc.dimensions <= OGA_1D ? 1 : (u32)desc.height;
    info.extent.depth = desc.dimensions <= OGA_2D ? 1 : (u32)desc.depth;
    info.mipLevels = 1;
    info.arrayLayers = 1;
    info.samples = VK_SAMPLE_COUNT_1_BIT;
    info.tiling = desc.linear_tiling ? VK_IMAGE_TILING_LINEAR : VK_IMAGE_TILING_OPTIMAL;
    info.usage = usage;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    
    _vk_assert2(vkCreateImage(context->id, &info, &internal->vk_allocs, &state->image));
    
    if (desc.memory_pointer.offset % context->device.limits.image_memory_granularity != 0) {
        // todo(charlie) #validation
        // What is the offset, what should it be aligned to ?
        return OGA_INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED;
    }
    
    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(context->id, state->image, &mem_req);
    if (mem_req.size > desc.memory_pointer.size-desc.memory_pointer.offset) {
        // todo(charlie) #validation
        // How much is required, how much was allocated ?
        return OGA_INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT;
    }
    
    _vk_assert2(vkBindImageMemory(context->id, state->image, ((_Vk_Memory_State*)desc.memory_pointer.id)->memory, desc.memory_pointer.offset));
    
    VkCommandPool transition_pool = 0;
    VkCommandPoolCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    create_info.flags = 0;
    create_info.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    create_info.queueFamilyIndex = (u32)desc.graphics_engine_family_index;

    _vk_assert2(vkCreateCommandPool((VkDevice)context->id, &create_info, &internal->vk_allocs, &transition_pool));
    
    VkCommandBufferAllocateInfo allocate_info = {0};
    allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocate_info.commandPool = transition_pool;
    allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocate_info.commandBufferCount = 1;

    VkCommandBuffer transition_cmd = 0;
    _vk_assert2(vkAllocateCommandBuffers(context->id, &allocate_info, &transition_cmd));
    
    VkCommandBufferBeginInfo begin_info = (VkCommandBufferBeginInfo){0};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    
    _vk_assert2(vkBeginCommandBuffer(transition_cmd, &begin_info));
     _vk_image_barrier_helper(transition_cmd, state->image, VK_IMAGE_LAYOUT_UNDEFINED, initial_layout);
    _vk_assert2(vkEndCommandBuffer(transition_cmd));
    
    VkSubmitInfo submit_info = (VkSubmitInfo){0};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &transition_cmd;
    
    _vk_assert2(vkQueueSubmit(context->engines_by_family[desc.graphics_engine_family_index].engines[0].id, 1, &submit_info, 0));
    vkQueueWaitIdle(context->engines_by_family[desc.graphics_engine_family_index].engines[0].id);
    vkDestroyCommandPool(context->id, transition_pool, &internal->vk_allocs);
    
    VkImageViewType view_type = 0;
    switch (desc.dimensions) {
        case OGA_1D: view_type = VK_IMAGE_VIEW_TYPE_1D; break;
        case OGA_2D: view_type = VK_IMAGE_VIEW_TYPE_2D; break;
        case OGA_3D: view_type = VK_IMAGE_VIEW_TYPE_3D; break;
        default: return OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM;
    }
    
    VkImageViewCreateInfo view_info = (VkImageViewCreateInfo){0};
    view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    view_info.viewType = view_type;
    view_info.format = _oga_to_vk_format(desc.format);
    view_info.components.r = VK_COMPONENT_SWIZZLE_R;
    view_info.components.g = VK_COMPONENT_SWIZZLE_G;
    view_info.components.b = VK_COMPONENT_SWIZZLE_B;
    view_info.components.a = VK_COMPONENT_SWIZZLE_A;
    view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    view_info.subresourceRange.baseMipLevel = 0;
    view_info.subresourceRange.levelCount = 1;
    view_info.subresourceRange.baseArrayLayer = 0;
    view_info.subresourceRange.layerCount = 1;
    view_info.image = state->image;
     
    _vk_assert2(vkCreateImageView(context->id, &view_info, &internal->vk_allocs, &state->view));
    
    return OGA_OK;
}

Oga_Result oga_init_image_view(Oga_Context *context, Oga_Image_View_Desc desc, Oga_Image_View **image) {
    *image = allocate(context->state_allocator, sizeof(Oga_Image_View) + sizeof(_Vk_Image_State));
    if (!*image) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **image = (Oga_Image_View){0};
    (*image)->context = context;
    (*image)->id = (*image)+1;
    
    _Vk_Image_State *state = (_Vk_Image_State*)(*image)->id;
    
    Oga_Result res = _oga_make_vk_image(context, state, desc, VK_IMAGE_USAGE_SAMPLED_BIT, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    if (res != OGA_OK) return res;
    
    (*image)->memory_pointer = desc.memory_pointer;
    (*image)->width = desc.width;
    (*image)->height = desc.height;
    (*image)->depth = desc.depth;
    (*image)->dimensions = desc.dimensions;
    (*image)->linear_tiling = desc.linear_tiling;
    
    
    return OGA_OK;
}
void oga_uninit_image_view(Oga_Image_View *image) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)image->context->internal;
    _vk_assert1(vkDeviceWaitIdle(image->context->id));
    
    _Vk_Image_State *state = (_Vk_Image_State*)image->id;
    
    vkDestroyImageView(image->context->id, state->view, &internal->vk_allocs);
    vkDestroyImage(image->context->id, state->image, &internal->vk_allocs);
    
    Allocator a = image->context->state_allocator;
    *image = (Oga_Image_View){0};
    deallocate(a, image);
}

Oga_Result oga_init_fbuffer_view(Oga_Context *context, Oga_Image_View_Desc desc, Oga_FBuffer_View **fbuffer) {
    *fbuffer = allocate(context->state_allocator, sizeof(Oga_FBuffer_View) + sizeof(_Vk_Image_State));
    if (!*fbuffer) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **fbuffer = (Oga_FBuffer_View){0};
    (*fbuffer)->context = context;
    (*fbuffer)->id = (*fbuffer)+1;
    
    _Vk_Image_State *state = (_Vk_Image_State*)(*fbuffer)->id;
    
    Oga_Result res = _oga_make_vk_image(context, state, desc, VK_IMAGE_USAGE_STORAGE_BIT, VK_IMAGE_LAYOUT_GENERAL);
    if (res != OGA_OK) return res;
    
    (*fbuffer)->memory_pointer = desc.memory_pointer;
    (*fbuffer)->width = desc.width;
    (*fbuffer)->height = desc.height;
    (*fbuffer)->depth = desc.depth;
    (*fbuffer)->dimensions = desc.dimensions;
    (*fbuffer)->linear_tiling = desc.linear_tiling;
    
    
    return OGA_OK;
}
void oga_uninit_fbuffer_view(Oga_FBuffer_View *fbuffer) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)fbuffer->context->internal;
    _vk_assert1(vkDeviceWaitIdle(fbuffer->context->id));
    
    _Vk_Image_State *state = (_Vk_Image_State*)fbuffer->id;
    
    vkDestroyImageView(fbuffer->context->id, state->view, &internal->vk_allocs);
    vkDestroyImage(fbuffer->context->id, state->image, &internal->vk_allocs);
    
    Allocator a = fbuffer->context->state_allocator;
    *fbuffer = (Oga_FBuffer_View){0};
    deallocate(a, fbuffer);
}

u64 oga_get_image_memory_requirement(Oga_Context *context, Oga_Image_View_Desc desc) {
    VkImage dummy_image;

    VkImageType image_type = 0;
    switch (desc.dimensions) {
        case OGA_1D: image_type = VK_IMAGE_TYPE_1D; break;
        case OGA_2D: image_type = VK_IMAGE_TYPE_2D; break;
        case OGA_3D: image_type = VK_IMAGE_TYPE_3D; break;
        default: return OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM;
    }
    
    VkImageCreateInfo info = (VkImageCreateInfo) {0};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.imageType = image_type;
    info.format = _oga_to_vk_format(desc.format);
    info.extent.width = (u32)desc.width;
    info.extent.height = desc.dimensions <= OGA_1D ? 1 : (u32)desc.height;
    info.extent.depth = desc.dimensions <= OGA_2D ? 1 : (u32)desc.depth;
    info.mipLevels = 1;
    info.arrayLayers = 1;
    info.samples = VK_SAMPLE_COUNT_1_BIT;
    info.tiling = desc.linear_tiling ? VK_IMAGE_TILING_LINEAR : VK_IMAGE_TILING_OPTIMAL;
    info.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    _vk_assert1(vkCreateImage(context->id, &info, &internal->vk_allocs, &dummy_image));
    
    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(context->id, dummy_image, &mem_req);
    
    vkDestroyImage(context->id, dummy_image, &internal->vk_allocs);
    
    return (u64)mem_req.size;
}

Oga_Result oga_init_optimal_copy_view(Oga_Context *context, Oga_Optimal_Copy_View_Desc desc, Oga_Optimal_Copy_View **image) {
    *image = allocate(context->state_allocator, sizeof(Oga_Optimal_Copy_View) + sizeof(_Vk_Image_State));
    if (!*image) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **image = (Oga_Optimal_Copy_View){0};
    (*image)->context = context;
    (*image)->id = (*image)+1;
    
    _Vk_Image_State *state = (_Vk_Image_State*)(*image)->id;
    
    VkImageType image_type = 0;
    switch (desc.dimensions) {
        case OGA_1D: image_type = VK_IMAGE_TYPE_1D; break;
        case OGA_2D: image_type = VK_IMAGE_TYPE_2D; break;
        case OGA_3D: image_type = VK_IMAGE_TYPE_3D; break;
        default: return OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM;
    }
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    VkImageCreateInfo info = (VkImageCreateInfo) {0};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.imageType = image_type;
    info.format = _oga_to_vk_format(desc.format);
    info.extent.width = (u32)desc.width;
    info.extent.height = desc.dimensions <= OGA_1D ? 1 : (u32)desc.height;
    info.extent.depth = desc.dimensions <= OGA_2D ? 1 : (u32)desc.depth;
    info.mipLevels = 1;
    info.arrayLayers = 1;
    info.samples = VK_SAMPLE_COUNT_1_BIT;
    info.tiling = desc.linear_tiling ? VK_IMAGE_TILING_LINEAR : VK_IMAGE_TILING_OPTIMAL;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    info.usage = 0;
    if (desc.flags & OGA_OPTIMAL_COPY_DST) info.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    if (desc.flags & OGA_OPTIMAL_COPY_SRC) info.usage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    
    if (info.usage == 0) {
        return OGA_INIT_OPTIMAL_COPY_VIEW_ERROR_INVALID_FLAGS;
    }
    
    _vk_assert2(vkCreateImage(context->id, &info, &internal->vk_allocs, &state->image));
    
    if (desc.memory_pointer.offset % context->device.limits.image_memory_granularity != 0) {
        // todo(charlie) #validation
        // What is the offset, what should it be aligned to ?
        return OGA_INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED;
    }
    
    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(context->id, state->image, &mem_req);
    if (mem_req.size > desc.memory_pointer.size-desc.memory_pointer.offset) {
        // todo(charlie) #validation
        // How much is required, how much was allocated ?
        return OGA_INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT;
    }
    
    _vk_assert2(vkBindImageMemory(context->id, state->image, ((_Vk_Memory_State*)desc.memory_pointer.id)->memory, desc.memory_pointer.offset));
    
    VkCommandPool transition_pool = 0;
    VkCommandPoolCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    create_info.flags = 0;
    create_info.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    create_info.queueFamilyIndex = (u32)desc.graphics_engine_family_index;

    _vk_assert2(vkCreateCommandPool((VkDevice)context->id, &create_info, &internal->vk_allocs, &transition_pool));
    
    VkCommandBufferAllocateInfo allocate_info = {0};
    allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocate_info.commandPool = transition_pool;
    allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocate_info.commandBufferCount = 1;

    VkCommandBuffer transition_cmd = 0;
    _vk_assert2(vkAllocateCommandBuffers(context->id, &allocate_info, &transition_cmd));
    
    VkCommandBufferBeginInfo begin_info = (VkCommandBufferBeginInfo){0};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    
    _vk_assert2(vkBeginCommandBuffer(transition_cmd, &begin_info));
     _vk_image_barrier_helper(transition_cmd, state->image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL);
    _vk_assert2(vkEndCommandBuffer(transition_cmd));
    
    VkSubmitInfo submit_info = (VkSubmitInfo){0};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &transition_cmd;
    
    _vk_assert2(vkQueueSubmit(context->engines_by_family[desc.graphics_engine_family_index].engines[0].id, 1, &submit_info, 0));
    vkQueueWaitIdle(context->engines_by_family[desc.graphics_engine_family_index].engines[0].id);
    vkDestroyCommandPool(context->id, transition_pool, &internal->vk_allocs);
    
    
    (*image)->memory_pointer = desc.memory_pointer;
    (*image)->width = desc.width;
    (*image)->height = desc.height;
    (*image)->depth = desc.depth;
    (*image)->dimensions = desc.dimensions;
    (*image)->linear_tiling = desc.linear_tiling;
    (*image)->flags = desc.flags;
    
    return OGA_OK;
}
void oga_uninit_optimal_copy_view(Oga_Optimal_Copy_View *image) {
     _Vk_Context_Internal *internal = (_Vk_Context_Internal*)image->context->internal;
    _vk_assert1(vkDeviceWaitIdle(image->context->id));
    
    _Vk_Image_State *state = (_Vk_Image_State*)image->id;
    
    vkDestroyImageView(image->context->id, state->view, &internal->vk_allocs);
    vkDestroyImage(image->context->id, state->image, &internal->vk_allocs);
    
    Allocator a = image->context->state_allocator;
    *image = (Oga_Optimal_Copy_View){0};
    deallocate(a, image);
}

Oga_Result oga_init_block_view(Oga_Context *context, Oga_Memory_View_Desc desc, Oga_Block_View **block) {
    *block = allocate(context->state_allocator, sizeof(Oga_Block_View));
    if (!*block) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **block = (Oga_Block_View){0};
    (*block)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkBufferCreateInfo info = (VkBufferCreateInfo){0};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    info.size = (VkDeviceSize)desc.size;
    info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    _vk_assert2(vkCreateBuffer(context->id, &info, &internal->vk_allocs, (VkBuffer*)&(*block)->id));
    
    (*block)->size = desc.size;
    (*block)->memory_pointer = desc.memory_pointer;
    
    _Vk_Memory_State *mem_state = (_Vk_Memory_State*)desc.memory_pointer.id;
    
    if (!(context->device.memory_heaps[desc.memory_pointer.heap_index].supported_usage_flags & OGA_MEMORY_USAGE_VERTEX_LIST)) {
        return OGA_INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT;
    }
    
    _vk_assert2(vkBindBufferMemory(context->id, (*block)->id, mem_state->memory, desc.memory_pointer.offset));
    
    return OGA_OK;
}
void oga_uninit_block_view(Oga_Block_View *block) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)block->context->internal;
    _vk_assert1(vkDeviceWaitIdle(block->context->id));
    
    vkDestroyBuffer(block->context->id, block->id, &internal->vk_allocs);
    
    Allocator a = block->context->state_allocator;
    *block = (Oga_Block_View){0};
    deallocate(a, block);
}

Oga_Result oga_init_command_pool(Oga_Context *context, Oga_Command_Pool_Desc desc, Oga_Command_Pool **pool) {
    *pool = allocate(context->state_allocator, sizeof(Oga_Command_Pool));
    if (!*pool) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **pool = (Oga_Command_Pool){0};
    (*pool)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;

    VkCommandPoolCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    create_info.flags = 0;

    if (desc.flags & OGA_COMMAND_POOL_SHORT_LIVED_ALLOCATIONS) {
        create_info.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    }

    create_info.queueFamilyIndex = (u32)desc.engine_family_index;

    _vk_assert2(vkCreateCommandPool((VkDevice)context->id, &create_info, &internal->vk_allocs, (VkCommandPool *)&(*pool)->id));

    return OGA_OK;
}

void oga_uninit_command_pool(Oga_Command_Pool *pool) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)pool->context->internal;

    _vk_assert1(vkDeviceWaitIdle(pool->context->id));
    vkResetCommandPool(pool->context->id, pool->id, 0);
    _vk_assert1(vkDeviceWaitIdle(pool->context->id));
    vkDestroyCommandPool(pool->context->id, pool->id, &internal->vk_allocs);

    Allocator a = pool->context->state_allocator;
    *pool = (Oga_Command_Pool){0};
    deallocate(a, pool);
}
void oga_reset_command_pool(Oga_Command_Pool *pool) {
    _vk_assert1(vkResetCommandPool(pool->context->id, pool->id, 0));
}

Oga_Result oga_get_command_lists(Oga_Command_Pool *pool, Oga_Command_List *lists, u64 list_count) {
    VkCommandBufferAllocateInfo allocate_info = {0};
    allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocate_info.commandPool = (VkCommandPool)pool->id;
    allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocate_info.commandBufferCount = (u32)list_count;

    VkCommandBuffer *vk_buffers = PushTempBuffer(VkCommandBuffer, list_count);
    _vk_assert2(vkAllocateCommandBuffers((VkDevice)pool->context->id, &allocate_info, vk_buffers));


    for (u64 i = 0; i < list_count; i += 1) {
        lists[i] = (Oga_Command_List){0};
        lists[i].id = vk_buffers[i];
        lists[i].pool = pool;
    }

    return OGA_OK;
}

void oga_release_command_lists(Oga_Command_List *lists, u64 list_count) {
    VkCommandBuffer *vk_buffers = PushTempBuffer(VkCommandBuffer, list_count);

    Oga_Command_Pool *last_pool = 0;
    
    for (u64 i = 0; i < list_count; i += 1) {
        if (last_pool) {
            assertmsg(last_pool != lists[i].pool, "Command lists from different pools were passed to oga_release_command_lists. All command lists must be from the same pool to do a batched release.");
        }
        last_pool = lists[i].pool;
    
        vk_buffers[i] = (VkCommandBuffer)lists[i].id;
        lists[i] = (Oga_Command_List){0};
    }
    
    _vk_assert1(vkDeviceWaitIdle(last_pool->context->id));
    vkFreeCommandBuffers((VkDevice)last_pool->context->id, (VkCommandPool)last_pool->id, (u32)list_count, vk_buffers);
}


Oga_Result oga_cmd_begin(Oga_Command_List cmd, Oga_Command_List_Usage_Flag flags) {
    VkCommandBufferBeginInfo info = (VkCommandBufferBeginInfo){0};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    if (flags & OGA_COMMAND_LIST_USAGE_ONE_TIME_SUBMIT) 
        info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    _vk_assert2(vkBeginCommandBuffer(cmd.id, &info));
    return OGA_OK;
}
Oga_Result oga_cmd_end(Oga_Command_List cmd) {
    _vk_assert2(vkEndCommandBuffer(cmd.id));
    return OGA_OK;
}
Oga_Result oga_submit_command_list(Oga_Command_List cmd, Oga_Submit_Command_List_Desc desc) {
    
    VkSemaphore *wait_semaphores = PushTempBuffer(VkSemaphore, desc.wait_gpu_latch_count);
    VkPipelineStageFlags *wait_stages = PushTempBuffer(VkPipelineStageFlags, desc.wait_gpu_latch_count);
    VkSemaphore *signal_semaphores = PushTempBuffer(VkSemaphore, desc.signal_gpu_latch_count);
    
    for (u64 i = 0; i < desc.wait_gpu_latch_count; i += 1) {
        wait_semaphores[i] = desc.wait_gpu_latches[i]->id;
        // note(charlie): it's a bit unfortunate to abstract this away from the programmer,
        // because it's a pretty neat opportunity for layout. Maybe we add this to the
        // api but make it sure it only has an effect when targetting vulkan?
        wait_stages[i] = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    }
    for (u64 i = 0; i < desc.signal_gpu_latch_count; i += 1) {
        signal_semaphores[i] = desc.signal_gpu_latches[i]->id;
    }

    VkSubmitInfo info = (VkSubmitInfo){0};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info.waitSemaphoreCount = (u32)desc.wait_gpu_latch_count;
    info.pWaitSemaphores = wait_semaphores;
    info.pWaitDstStageMask = wait_stages;
    info.commandBufferCount = 1; // todo(charlie) api to submit multiple command buffers at a time?
    info.pCommandBuffers = (VkCommandBuffer*)&cmd.id;
    info.signalSemaphoreCount = (u32)desc.signal_gpu_latch_count;
    info.pSignalSemaphores = signal_semaphores;
    
    _vk_assert2(vkQueueSubmit(desc.engine.id, 1, &info, desc.signal_cpu_latch ? desc.signal_cpu_latch->id : 0));
    
    return OGA_OK;    
}

Oga_Result oga_init_gpu_timestamp_pool(Oga_Context *context, u64 timestamp_count, Oga_Gpu_Timestamp_Pool **pool) {
    *pool = allocate(context->state_allocator, sizeof(Oga_Gpu_Timestamp_Pool));
    if (!*pool) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **pool = (Oga_Gpu_Timestamp_Pool){0};
    (*pool)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkQueryPoolCreateInfo pool_info = {0};
    pool_info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    pool_info.queryType = VK_QUERY_TYPE_TIMESTAMP;
    pool_info.queryCount = (u32)timestamp_count;
    
    _vk_assert2(vkCreateQueryPool(context->id, &pool_info, &internal->vk_allocs, (VkQueryPool*)&(*pool)->id));
    
    (*pool)->timestamp_count = timestamp_count;
    
    return OGA_OK;
}
void oga_uninit_gpu_timestamp_pool(Oga_Gpu_Timestamp_Pool *pool) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)pool->context->internal;
    _vk_assert1(vkDeviceWaitIdle(pool->context->id));
    
    vkDestroyQueryPool(pool->context->id, pool->id, &internal->vk_allocs);
    
    Allocator a = pool->context->state_allocator;
    *pool = (Oga_Gpu_Timestamp_Pool){0};
    deallocate(a, pool);
}

void oga_cmd_reset_timestamp_pool(Oga_Command_List cmd, Oga_Gpu_Timestamp_Pool *pool) {
    vkCmdResetQueryPool(cmd.id, pool->id, 0, (u32)pool->timestamp_count);
    pool->written_timestamp_count = 0;
}
void oga_cmd_write_timestamp(Oga_Command_List cmd, Oga_Gpu_Timestamp_Pool *pool) {
    if (pool->written_timestamp_count >= pool->timestamp_count) return; // todo(charlie) #validation
    
    vkCmdWriteTimestamp(cmd.id, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, pool->id, (u32)pool->written_timestamp_count);
    pool->written_timestamp_count += 1;
}

Oga_Result oga_read_timestamps(Oga_Gpu_Timestamp_Pool *pool, f64 *nanosecond_timestamps, bool wait) {
    u64 *periods_buffer = PushTempBuffer(u64, pool->written_timestamp_count);
    _vk_assert2(vkGetQueryPoolResults(pool->context->id, pool->id, 0, (u32)pool->written_timestamp_count, pool->written_timestamp_count*sizeof(u64), periods_buffer, sizeof(u64), VK_QUERY_RESULT_64_BIT | (wait ? VK_QUERY_RESULT_WAIT_BIT : 0)));
    
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(pool->context->device.id, &props);
    f64 nanoseconds_per_period = (f64)props.limits.timestampPeriod;
    
    for (u64 i = 0; i < pool->written_timestamp_count; i += 1) {
        nanosecond_timestamps[i] = nanoseconds_per_period * (f64)periods_buffer[i];
    }
    
    return OGA_OK;
}

void oga_cmd_begin_render_pass(Oga_Command_List cmd, Oga_Render_Pass *render_pass, Oga_Begin_Render_Pass_Desc desc) {
    // todo(charlie) #validation
    // Make sure a render target is only active in one render pass at a time
    
    VkRenderingAttachmentInfoKHR vk_attachments[128] = {0};

    for (u64 i = 0; i < desc.attachment_count; i += 1) {
        
        Oga_Render_Attachment_Desc attach_desc = desc.attachments[i];
        
        _Vk_Render_Image_State *state = (_Vk_Render_Image_State*)attach_desc.image->id;
        
        _vk_image_barrier_helper(cmd.id, state->image, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
    
        vk_attachments[i].sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
        vk_attachments[i].imageView = state->view;
        vk_attachments[i].imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        
        if (attach_desc.resolve_mode & OGA_MSAA_RESOLVE_MODE_ZERO)
            vk_attachments[i].resolveMode |= VK_RESOLVE_MODE_SAMPLE_ZERO_BIT_KHR;
        if (attach_desc.resolve_mode & OGA_MSAA_RESOLVE_MODE_AVERAGE)
            vk_attachments[i].resolveMode |= VK_RESOLVE_MODE_AVERAGE_BIT_KHR;
        if (attach_desc.resolve_mode & OGA_MSAA_RESOLVE_MODE_MIN)
            vk_attachments[i].resolveMode |= VK_RESOLVE_MODE_MIN_BIT_KHR;
        if (attach_desc.resolve_mode & OGA_MSAA_RESOLVE_MODE_MAX)
            vk_attachments[i].resolveMode |= VK_RESOLVE_MODE_MAX_BIT_KHR;
            
        if (attach_desc.resolve_image) {
            _Vk_Render_Image_State *resolve_state = (_Vk_Render_Image_State*)attach_desc.resolve_image->id;
            _vk_image_barrier_helper(cmd.id, resolve_state->image, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
    
            vk_attachments[i].resolveImageView = resolve_state->view;
            vk_attachments[i].resolveImageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        }
        
        switch (attach_desc.load_op) {
            case OGA_ATTACHMENT_LOAD_OP_LOAD:
                vk_attachments[i].loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
                break;
            case OGA_ATTACHMENT_LOAD_OP_CLEAR:
                vk_attachments[i].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
                break;
            case OGA_ATTACHMENT_LOAD_OP_NOTHING:
                vk_attachments[i].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
                break;
            default:break;
        }
        switch (attach_desc.store_op) {
            case OGA_ATTACHMENT_STORE_OP_STORE:
                vk_attachments[i].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
                break;
            case OGA_ATTACHMENT_STORE_OP_NOTHING:
                vk_attachments[i].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
                break;
            default:break;
        }
        
        memcpy(vk_attachments[i].clearValue.color.float32, attach_desc.clear_color, sizeof(float32)*4);
    }
    
    VkRenderingAttachmentInfo dummy_attachment = (VkRenderingAttachmentInfo){0};
    dummy_attachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;

    VkRenderingInfoKHR info = (VkRenderingInfoKHR){0};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;
    info.renderArea.offset.x = (s32)desc.render_area_offset_x;
    info.renderArea.offset.y = (s32)desc.render_area_offset_y;
    info.renderArea.extent.width = (u32)desc.render_area_width;
    info.renderArea.extent.height = (u32)desc.render_area_height;
    info.layerCount = 1;
    info.colorAttachmentCount = (u32)desc.attachment_count;
    info.pColorAttachments = vk_attachments;
    info.pDepthAttachment = &dummy_attachment;
    info.pStencilAttachment = &dummy_attachment;
    
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)cmd.pool->context->internal;
    internal->vkCmdBeginRenderingKHR(cmd.id, &info);
    
    _Vk_Render_Pass_State *state = (_Vk_Render_Pass_State*)render_pass->id;
    
    state->active_image_count = desc.attachment_count;
    for (u64 i = 0; i < desc.attachment_count; i += 1) {
        _Vk_Render_Image_State *image_state = (_Vk_Render_Image_State*)desc.attachments[i].image->id;
        state->active_images[i] = image_state->image;
        if (desc.attachments[i].resolve_image) {
            _Vk_Render_Image_State *resolve_state = (_Vk_Render_Image_State*)desc.attachments[i].resolve_image->id;
            state->active_resolve_images[i] = resolve_state->image;
        }
    }
    
    vkCmdBindPipeline(cmd.id, VK_PIPELINE_BIND_POINT_GRAPHICS, state->pipeline); 
    
    VkViewport vp = (VkViewport){0};
    vp.x = 0;
    vp.y = 0;
    vp.width = (float)desc.render_area_width;
    vp.height = (float)desc.render_area_height;
    vp.minDepth = 0.0;
    vp.maxDepth = 1.0;
    
    vkCmdSetViewport(cmd.id, 0, 1, &vp);
    
    VkRect2D scissor;
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent.width = info.renderArea.extent.width;
    scissor.extent.height = info.renderArea.extent.height;
    
    vkCmdSetScissor(cmd.id, 0, 1, &scissor);
}
void oga_cmd_end_render_pass(Oga_Command_List cmd, Oga_Render_Pass *render_pass) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)cmd.pool->context->internal;
    
    internal->vkCmdEndRenderingKHR(cmd.id);
    
    _Vk_Render_Pass_State *state = (_Vk_Render_Pass_State*)render_pass->id;
    
    for (u64 i = 0; i < state->active_image_count; i += 1) {
        
        _vk_image_barrier_helper(cmd.id, state->active_images[i], VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
            
        if (state->active_resolve_images[i]) {
            _vk_image_barrier_helper(cmd.id, state->active_resolve_images[i], VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
        }
        
        state->active_images[i] = 0;
        state->active_resolve_images[i] = 0;
    }
    state->active_image_count = 0;
    
}

void oga_cmd_bind_render_pass_binding_list(Oga_Command_List cmd, Oga_Render_Pass *pass, Oga_Binding_List *list) {
    _Vk_Render_Pass_State *pass_state = (_Vk_Render_Pass_State*)pass->id;
    vkCmdBindDescriptorSets(cmd.id, VK_PIPELINE_BIND_POINT_GRAPHICS, pass_state->layout, 0, 1, (VkDescriptorSet*)&list->id, 0, 0);
}

Oga_Result oga_cmd_draw(Oga_Command_List cmd, Oga_Draw_Desc desc) {

    // Potentially bind vertex lists
    switch (desc.draw_type) {
    case OGA_DRAW_VERTEX_LIST:                             // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED:                   // fallthrough
    case OGA_DRAW_VERTEX_LIST_INDEXED:                     // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED:           // fallthrough
    case OGA_DRAW_VERTEX_LIST_INDIRECT:                    // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDIRECT:          // fallthrough
    case OGA_DRAW_VERTEX_LIST_INDEXED_INDIRECT:            // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED_INDIRECT:
        
        if (desc.vertex_list_binding_count == 0) {
            return OGA_CMD_DRAW_ERROR_VERTEX_LIST_BINDING_COUNT_ZERO; 
        }
        
        VkDeviceSize offsets[OGA_MAX_VERTEX_BINDING_COUNT];
        VkBuffer vbuffers[OGA_MAX_VERTEX_BINDING_COUNT];
        
        for (u32 i = 0; i < desc.vertex_list_binding_count; i += 1) {
            Oga_Vertex_List_View *vlist = desc.vertex_list_bindings[i];
            u64 offset = desc.vertex_list_offsets[i];
            if (!vlist) 
                return OGA_CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING; // todo(charlie) #validation user should get a descriptive error conveying exactly which bind point was missing 
            if (desc.vertex_list_offsets[i] >= vlist->size)
                return OGA_CMD_DRAW_ERROR_VERTEX_LIST_OFFSET_OUT_OF_RANGE; // todo(charlie) #validation same as above
            
            offsets[i] = (VkDeviceSize)offset;
            vbuffers[i] = (VkBuffer)vlist->id; 
        }
        
        vkCmdBindVertexBuffers(cmd.id, 0, (u32)desc.vertex_list_binding_count, vbuffers, offsets);
        
        break;
    case OGA_DRAW_INSTANCED: // fallthrough
    case OGA_DRAW_INSTANCED_INDIRECT:                     
        break;
    default:
        return OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM;
    }
    
    // Potentially bind index lists
    switch (desc.draw_type) {
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED:           // fallthrough
    case OGA_DRAW_VERTEX_LIST_INDEXED:                     // fallthrough
    case OGA_DRAW_VERTEX_LIST_INDEXED_INDIRECT:            // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED_INDIRECT:
        
        if (!desc.index_list) {
            return OGA_CMD_DRAW_ERROR_MISSING_INDEX_LIST;
        }
        
        VkIndexType index_type = 0;
        u64 index_size = 0;
        switch (desc.index_type) {
        case OGA_INDEX_U32: 
            index_type = VK_INDEX_TYPE_UINT32; 
            index_size = 4;
            break;
        case OGA_INDEX_U16: 
            index_type = VK_INDEX_TYPE_UINT16; 
            index_size = 2;
            break;
        default:
            return OGA_CMD_DRAW_ERROR_INVALID_INDEX_TYPE_ENUM;
        }
        
        vkCmdBindIndexBuffer(cmd.id, (VkBuffer)desc.index_list->id, (VkDeviceSize)(index_size*desc.index_list_offset), index_type);
        
        break;
    case OGA_DRAW_VERTEX_LIST:                             // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED:                   // fallthrough
    case OGA_DRAW_VERTEX_LIST_INDIRECT:                    // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDIRECT:          // fallthrough
    case OGA_DRAW_INSTANCED: // fallthrough
    case OGA_DRAW_INSTANCED_INDIRECT:                     
        break;
    default:
        return OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM;
    }

    switch (desc.draw_type) {
    case OGA_DRAW_INSTANCED:                              
        vkCmdDraw(cmd.id, (u32)desc.vertex_count, (u32)desc.instance_count, (u32)desc.vertex_start, (u32)desc.instance_start);
        break;
    case OGA_DRAW_VERTEX_LIST:
        vkCmdDraw(cmd.id, (u32)desc.vertex_count, 1, (u32)desc.vertex_start, 0);
        break;
    case OGA_DRAW_VERTEX_LIST_INSTANCED:                  
        vkCmdDraw(cmd.id, (u32)desc.vertex_count, (u32)desc.instance_count, (u32)desc.vertex_start, (u32)desc.instance_start);
        break;
    case OGA_DRAW_VERTEX_LIST_INDEXED:
        vkCmdDrawIndexed(cmd.id, (u32)desc.index_count, 1, (u32)desc.index_start, (s32)desc.vertex_start, 0);
        break;
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED:          
        vkCmdDrawIndexed(cmd.id, (u32)desc.index_count, (u32)desc.instance_count, (u32)desc.index_start, (s32)desc.vertex_start, (u32)desc.instance_start);
        break;
    case OGA_DRAW_INSTANCED_INDIRECT:      
        assertmsg(false, "unimplemented");               
        break;
    case OGA_DRAW_VERTEX_LIST_INDIRECT:                   
        assertmsg(false, "unimplemented");               
        break;
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDIRECT:         
        assertmsg(false, "unimplemented");               
        break;
    case OGA_DRAW_VERTEX_LIST_INDEXED_INDIRECT:           
        assertmsg(false, "unimplemented");               
        break;
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED_INDIRECT: 
        assertmsg(false, "unimplemented");               
        break;
    default:
        return OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM;
    }
    
    return OGA_OK;
}

void oga_cmd_copy_linear(Oga_Command_List cmd, Oga_Memory_Pointer dst, Oga_Memory_Pointer src, u64 size) {
    VkBufferCopy info = (VkBufferCopy){0};
    info.srcOffset = (VkDeviceSize)src.offset;
    info.dstOffset = (VkDeviceSize)dst.offset;
    info.size = (VkDeviceSize)size;
    
    _Vk_Memory_State *src_state = (_Vk_Memory_State*)(src.id);
    _Vk_Memory_State *dst_state = (_Vk_Memory_State*)(dst.id);
    
    vkCmdCopyBuffer(cmd.id, src_state->raw_view, dst_state->raw_view, 1, &info);
}

void oga_cmd_copy_linear_to_image(Oga_Command_List cmd, Oga_Optimal_Copy_View *dst_view, Oga_Optimal_Copy_Desc dst_desc, Oga_Memory_Pointer src) {

    VkBufferImageCopy info = (VkBufferImageCopy){0};
    info.bufferOffset = (VkDeviceSize)src.offset;
    info.imageOffset.x = (s32)dst_desc.offset_x;
    info.imageOffset.y = (s32)dst_desc.offset_y;
    info.imageOffset.z = (s32)dst_desc.offset_z;
    info.imageExtent.width = (u32)dst_desc.width;
    info.imageExtent.height = dst_view->dimensions <= OGA_1D ? 1 : (u32)dst_desc.height;
    info.imageExtent.depth = dst_view->dimensions <= OGA_2D ? 1 : (u32)dst_desc.depth;
    info.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    info.imageSubresource.mipLevel = 0;
    info.imageSubresource.baseArrayLayer = 0;
    info.imageSubresource.layerCount = 1;
    
    _Vk_Image_State *dst_state = (_Vk_Image_State*)(dst_view->id);
    _Vk_Memory_State *src_state = (_Vk_Memory_State*)(src.id);
    
    _vk_image_barrier_helper(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    vkCmdCopyBufferToImage(cmd.id, src_state->raw_view, dst_state->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &info);
    _vk_image_barrier_helper(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
}
void oga_cmd_copy_image_to_linear(Oga_Command_List cmd, Oga_Memory_Pointer dst, Oga_Optimal_Copy_View *src_view, Oga_Optimal_Copy_Desc src_desc) {

    VkBufferImageCopy info = (VkBufferImageCopy){0};
    info.bufferOffset = (VkDeviceSize)dst.offset;
    info.imageOffset.x = (s32)src_desc.offset_x;
    info.imageOffset.y = (s32)src_desc.offset_y;
    info.imageOffset.z = (s32)src_desc.offset_z;
    info.imageExtent.width = (u32)src_desc.width;
    info.imageExtent.height = src_view->dimensions <= OGA_1D ? 1 : (u32)src_desc.height;
    info.imageExtent.depth = src_view->dimensions <= OGA_2D ? 1 : (u32)src_desc.depth;
    info.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    info.imageSubresource.mipLevel = 0;
    info.imageSubresource.baseArrayLayer = 0;
    info.imageSubresource.layerCount = 1;
    
    _Vk_Image_State *src_state = (_Vk_Image_State*)(src_view->id);
    _Vk_Memory_State *dst_state = (_Vk_Memory_State*)(dst.id);
    
    _vk_image_barrier_helper(cmd.id, src_state->image, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
    vkCmdCopyImageToBuffer(cmd.id, src_state->image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dst_state->raw_view, 1, &info);
    _vk_image_barrier_helper(cmd.id, src_state->image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
}

void oga_cmd_copy_image(Oga_Command_List cmd, Oga_Optimal_Copy_View *dst_view, Oga_Optimal_Copy_Desc dst_desc, Oga_Optimal_Copy_View *src_view, Oga_Optimal_Copy_Desc src_desc) {
    VkImageCopy info = (VkImageCopy){0};
    
    info.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    info.srcSubresource.mipLevel = 0;
    info.srcSubresource.baseArrayLayer = 0;
    info.srcSubresource.layerCount = 1;
    info.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    info.dstSubresource.mipLevel = 0;
    info.dstSubresource.baseArrayLayer = 0;
    info.dstSubresource.layerCount = 1;
    info.srcOffset.x = (s32)src_desc.offset_x;
    info.srcOffset.y = (s32)src_desc.offset_y;
    info.srcOffset.z = (s32)src_desc.offset_z;
    info.dstOffset.x = (s32)dst_desc.offset_x;
    info.dstOffset.y = (s32)dst_desc.offset_y;
    info.dstOffset.z = (s32)dst_desc.offset_z;
    info.extent.width = (u32)dst_desc.width;
    info.extent.height = dst_view->dimensions <= OGA_1D ? 1 : (u32)dst_desc.height;
    info.extent.depth = dst_view->dimensions <= OGA_2D ? 1 : (u32)dst_desc.depth;
    
    _Vk_Image_State *src_state = (_Vk_Image_State*)(src_view->id);
    _Vk_Image_State *dst_state = (_Vk_Image_State*)(dst_view->id);
    
    _vk_image_barrier_helper(cmd.id, src_state->image, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
    _vk_image_barrier_helper(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    vkCmdCopyImage(cmd.id, src_state->image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dst_state->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &info);
    _vk_image_barrier_helper(cmd.id, src_state->image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
    _vk_image_barrier_helper(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
}

void oga_cmd_fill_image(Oga_Command_List cmd, Oga_Optimal_Copy_View *dst_view, float4 color) {
    _Vk_Image_State *dst_state = (_Vk_Image_State*)(dst_view->id);
    
    VkClearColorValue vk_color;
    vk_color.float32[0] = color.x;
    vk_color.float32[1] = color.y;
    vk_color.float32[2] = color.z;
    vk_color.float32[3] = color.w;
    
    VkImageSubresourceRange sub = (VkImageSubresourceRange){0};
    sub.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    sub.baseMipLevel = 0;
    sub.levelCount = 1;
    sub.baseArrayLayer = 0;
    sub.layerCount = 1;
    
    _vk_image_barrier_helper(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    vkCmdClearColorImage(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &vk_color, 1, &sub);
    _vk_image_barrier_helper(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
}

#undef uint8_t
#undef int8_t
#undef uint16_t
#undef int16_t
#undef uint32_t
#undef int32_t
#undef uint64_t
#undef int64_t

/* End include: graphics_vulkan.h */
#endif // (OS_FLAGS & (OS_FLAG_WINDOWS | OS_FLAG_LINUX | OS_FLAG_MACOS | OS_FLAG_IOS | OS_FLAG_ANDROID))

// OGA_IMPL_VULKAN
#elif defined(OGA_IMPL_WEBGPU)

/////////////////////////////////////////////////////
//////
// :WebGPU
//////
/////////////////////////////////////////////////////

#define OGA_OSL_TARGET OSL_TARGET_WGPU

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

#define OGA_OSL_TARGET OSL_TARGET_DXIL

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

#define OGA_OSL_TARGET OSL_TARGET_MSL

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

#define OGA_OSL_TARGET OSL_TARGET_AVX

u64 oga_query_devices(Oga_Device *buffer, u64 buffer_count) {
    (void)buffer;(void)buffer_count;
    return 0;
}

#endif

#endif // OSTD_IMPL

#endif // OGA_GRAPHICS && !OSTD_HEADLESS

#endif // _ONE_OGA_GRAPHICS_H
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

