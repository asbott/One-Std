#ifndef _SYSTEM_1_H
#define _SYSTEM_1_H

#ifndef _BASE_H
#include "base.h"
#endif // _BASE_H
#ifndef _STRING_H
#include "string.h"
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
OSTD_LIB Easy_Command_Result sys_run_command_easy(string command_line, File_Handle stdout, File_Handle stderr, string workspace_dir);

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
    void *handle;
    u64 id;
    void *userdata;
    Thread_Proc proc;
    bool is_suspended;
} Thread;

OSTD_LIB bool sys_thread_init(Thread *thread, Thread_Proc proc, void *userdata);
OSTD_LIB void sys_thread_start(Thread *thread);
OSTD_LIB s64 sys_thread_join(Thread *thread);
OSTD_LIB void sys_thread_close(Thread *thread);

typedef struct Mutex {
    void *handle;
    u8 handle_backing[40]; // This is for windows critical section;
} Mutex;

OSTD_LIB bool sys_mutex_init(Mutex *mutex);
OSTD_LIB bool sys_mutex_uninit(Mutex *mutex);
OSTD_LIB void sys_mutex_acquire(Mutex mutex);
OSTD_LIB void sys_mutex_release(Mutex mutex);

typedef void *Semaphore;
OSTD_LIB bool sys_semaphore_init(Semaphore *sem);
OSTD_LIB void sys_semaphore_signal(Semaphore *sem);
OSTD_LIB void sys_semaphore_wait(Semaphore sem);
OSTD_LIB void sys_semaphore_release(Semaphore sem);

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
    #include "windows_loader.h"
    #endif // _WINDOWS_

#endif// OS_FLAGS & OS_FLAG_WINDOWS

#ifndef OSTD_HEADLESS

#if OS_FLAGS & OS_FLAG_LINUX
    #if COMPILER_FLAGS & COMPILER_FLAG_GNU
    #endif

    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/extensions/Xrandr.h>
    #undef NULL

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

#undef NULL

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
void sys_thread_start(Thread *thread) {
    thread->is_suspended = false;
    ResumeThread(thread->handle);
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
    if (!sem) return false;
    HANDLE handle = CreateSemaphoreA(0, 0, S32_MAX, 0);
    if (!handle) return false;
    *sem = handle;
    return true;
}

OSTD_LIB void sys_semaphore_signal(Semaphore *sem) {
    if (!sem || !*sem) return;
    ReleaseSemaphore((HANDLE)*sem, 1, 0);
}

OSTD_LIB void sys_semaphore_wait(Semaphore sem) {
    if (!sem) return;
    WaitForSingleObject((HANDLE)sem, 0xFFFFFFFF);
}

OSTD_LIB void sys_semaphore_release(Semaphore sem) {
    if (!sem) return;
    CloseHandle((HANDLE)sem);
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
