

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

u32 sys_write(File_Handle f, void *data, u64 size);
u32 sys_write_string(File_Handle f, string s);


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


#if (OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)

typedef struct Surface_Desc {
    // These don't do anything for main surface on phone/console systems
    u32 width;
    u32 height;
    u32 x_pos;
    u32 y_pos;
    string title;
    bool fullscreen;
} Surface_Desc;
inline Surface_Desc Surface_Desc_default(void) {
    Surface_Desc desc = (Surface_Desc) {0};
    desc.width = 800;
    desc.height = 600;
    desc.x_pos = 0;
    desc.y_pos = 0;
    desc.title = STR("ostd window");
    return desc;
}
Surface_Handle sys_make_surface(Surface_Desc desc);
void surface_close(Surface_Handle s);


#else // !(OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)

Surface_Handle sys_get_surface(void);

#endif // !(OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)

void surface_poll_events(Surface_Handle surface);
bool surface_should_close(Surface_Handle s);

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
    Surface_Handle *handle;
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
_Mapped_Region_Desc_Buffer *_unix_mapped_region_buffers = 0;
u64 _unix_mapped_region_buffers_allocated_count = 0;
u64 _unix_mapped_region_buffers_count = 0;

// todo(charlie): mutex
void _unix_add_mapped_region(void *start, u64 page_count) {
    System_Info info = sys_get_info();
    if (!_unix_mapped_region_buffers) {
        _unix_mapped_region_buffers = (_Mapped_Region_Desc_Buffer *)mmap(0, info.page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        assert(_unix_mapped_region_buffers); // todo(charlie) revise
        memset(_unix_mapped_region_buffers, 0, info.page_size);
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
                region->page_count = page_count;
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
        
        _Mapped_Region_Desc_Buffer *new_buffers = (_Mapped_Region_Desc_Buffer *)mmap(0, info.page_size*new_count, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        assert(new_buffers); // todo(charlie) revise
        
        memcpy(new_buffers, _unix_mapped_region_buffers, old_count*info.page_size);
        
        munmap(_unix_mapped_region_buffers, info.page_size*old_count);
        _unix_mapped_region_buffers = new_buffers;
        
        memset((u8*)_unix_mapped_region_buffers + info.page_size*old_count, 0, info.page_size);
        
        _unix_mapped_region_buffers_allocated_count = new_count;
    }
    
    assert(_unix_mapped_region_buffers_count < _unix_mapped_region_buffers_allocated_count);
    
    // Grab & initialize next buffer
    _Mapped_Region_Desc_Buffer *buffer = &_unix_mapped_region_buffers[_unix_mapped_region_buffers_count++];
    buffer->count = info.page_size/sizeof(_Mapped_Region_Desc);
    buffer->regions = mmap(0, info.page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memset(buffer->regions, 0, info.page_size);
    assert(buffer->regions); // todo(charlie) revise
    
    buffer->regions[0].taken = true;
    buffer->regions[0].start = start;
    buffer->regions[0].page_count = page_count;
}

_Mapped_Region_Desc *_unix_find_mapped_region(void *start) {
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

    void *result = mmap(virtual_base, amount_in_bytes, prot, flags, -1, 0);
    if (result == MAP_FAILED) {
        return NULL;
    }
    
    _unix_add_mapped_region(result, number_of_pages);

    return result;
}

bool sys_unmap_pages(void *address) {
    System_Info info = sys_get_info();
    
    _Mapped_Region_Desc *region = _unix_find_mapped_region(address);
    if (region) {
        munmap(region->start, info.page_size * region->page_count);
        region->taken = false;
    }
    
    return region != 0;
}

bool sys_deallocate_pages(void *address, u64 number_of_pages) {
    System_Info info = sys_get_info();
    u64 amount_in_bytes = info.page_size * number_of_pages;

    if (madvise(address, amount_in_bytes, MADV_DONTNEED) != 0) {
        return false;
    }
    return true;
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



#if defined(_WINDOWS_) // User included windows.h
    #ifndef  // WIN32_LEAN_AND_MEAN
        #error For ostd to work with windows.h included, you need to #define WIN32_LEAN_AND_MEAN
    #endif // WIN32_LEAN_AND_MEAN
    #ifndef _DBGHELP_
        #include "dbghelp.h"
    #endif // _DBGHELP_
#endif // defined(_WINDOWS_)

// If user for some reason wants to include the full standard windows files,
// then he can define OSTD_INCLUDE_WINDOWS
#ifdef OSTD_INCLUDE_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include "windows.h"
    #include "dbghelp.h"
#endif // OSTD_INCLUDE_WINDOWS

// We manually declare windows functions so we don't need to bloat compilation and
// namespace with windows.h
#ifndef _WINDOWS_ /* This is defined in windows.h */
#include "windows_loader.h"
#endif // _WINDOWS_



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

u32 sys_write(File_Handle f, void *data, u64 size) {
    u32 written;
    WriteFile(f, data, (DWORD)size, (unsigned long*)&written, 0);
    return written;
}

u32 sys_write_string(File_Handle f, string s) {
    return sys_write(f, s.data, s.count);
}

Surface_Handle sys_make_surface(Surface_Desc desc) {
    _Surface_State *s = _alloc_surface_state();
    if (!s) {
        // todo(charlie) sys_error
        return 0;
    }
    
    HINSTANCE instance = GetModuleHandleW(0);
    
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
    UpdateWindow(hwnd);
    
    ShowWindow(hwnd, SW_SHOW);
    
    s->handle = hwnd;
    
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
int _android_stdout_pipe[2];
// Must be provided by android project
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
    return NULL;
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

int _android_main(void) {
    pipe(_android_stdout_pipe);
    
    pthread_attr_t attr;
    struct sched_param param;
    
    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
    
    param.sched_priority = 0;
    pthread_attr_setschedparam(&attr, &param);
#if CSTD11
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
#endif

    pthread_mutex_init(&_android_stdout_pending_mutex, NULL);
    pthread_create(&_android_stdout_thread, &attr, _android_stdout_thread_proc, 0);

    extern int main(void);
    int code = main();
    
    _android_running = false;
    
    pthread_mutex_lock(&_android_stdout_pending_mutex);
    close(_android_stdout_pipe[0]);
    close(_android_stdout_pipe[1]);
    pthread_mutex_unlock(&_android_stdout_pending_mutex);
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
    buffer[0].handle = NULL;

    return 1;
}


File_Handle sys_get_stdout(void) {
    return (File_Handle)(u64)_android_stdout_pipe[1];
}
File_Handle sys_get_stderr(void) {
    return (File_Handle)(u64)_android_stdout_pipe[1];
}

u32 sys_write(File_Handle f, void *data, u64 size) {
    return (u32)write((int)(u64)f, data, size);
}

u32 sys_write_string(File_Handle f, string s) {
    return sys_write(f, s.data, s.count);
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

void sys_print_stack_trace(File_Handle handle) {
    sys_write_string(handle, STR("<Stack trace unimplemented>"));
}

#endif // OS_FLAGS & XXXXX

#endif // OSTD_IMPL