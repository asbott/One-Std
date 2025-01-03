

typedef enum System_Memory_Action {
    SYS_MEMORY_RESERVE = 1 << 0,
    SYS_MEMORY_ALLOCATE = 1 << 1,
} System_Memory_Action;

void *sys_map_pages(System_Memory_Action action, void *virtual_base, u64 amount_in_bytes);
bool sys_unmap_pages(void *address);
// Deallocates, but keeps pages mapped & reserved
bool sys_deallocate_pages(void *address, u64 number_of_pages);

typedef struct Mapped_Memory_Info {
    void *base;
    u64 page_count;
} Mapped_Memory_Info;
u64 sys_query_mapped_pointers(void *start, void *end, Mapped_Memory_Info *result, u64 result_size);

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

//////
// Debug
//////

void sys_print_stack_trace(File_Handle handle);




#ifdef OSTD_IMPL

#if (OS_FLAGS & OS_FLAG_WINDOWS) == OS_FLAG_WINDOWS

#if COMPILER_FLAGS & COMPILER_FLAG_MSC
    #pragma comment(lib, "kernel32")
    #pragma comment(lib, "user32")
    #pragma comment(lib, "shcore")
    #pragma comment(lib, "dbghelp")
#endif

#if defined(_WINDOWS_) // User included windows.h
    #ifndef WIN32_LEAN_AND_MEAN
        #error For ostd to work with windows.h included, you need to #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef _DBGHELP_
        #include "dbghelp.h"
    #endif
#endif

// If user for some reason wants to include the full standard windows files,
// then he can define OSTD_INCLUDE_WINDOWS
#ifdef OSTD_INCLUDE_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include "windows.h"
    #include "dbghelp.h"
#endif

// We manually declare windows functions so we don't need to bloat compilation and
// namespace with windows.h
#ifndef _WINDOWS_ /* This is defined in windows.h */
#include "windows_loader.h"
#endif // _WINDOWS_

void _win_lazy_enable_dpi_awarness(void) {
    local_persist bool enabled = false;
    if (!enabled) {
        enabled = true;
        BOOL ok = SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
		if (!ok) {
			SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
		}
    }
}

void *sys_map_pages(System_Memory_Action action, void *virtual_base, u64 number_of_pages) {
    
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

u64 sys_query_mapped_pointers(void *start, void *end, Mapped_Memory_Info *result, u64 result_count) {
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

int __wcscmp(const u16 *s1, const u16 *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (int)(*s1) - (int)(*s2);
}
BOOL WINAPI _win_query_monitors_callback(HMONITOR monitor_handle, HDC dc, RECT *rect, LPARAM param) {
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
    while(EnumDisplayDevicesW(0, i, &even_more_info, 0)) {
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

BOOL WINAPI _win_get_total_rect_callback(HMONITOR monitor, HDC dc, RECT *lprcClip, LPARAM param) {
    _win_lazy_enable_dpi_awarness();
    (void)dc; (void)lprcClip;
    TotalRectContext *ctx = (TotalRectContext*)param;
    MONITORINFO info;
    info.cbSize = sizeof(MONITORINFO);
    if(GetMonitorInfoW(monitor, &info)){
        if(info.rcMonitor.left < ctx->rect.left) ctx->rect.left = info.rcMonitor.left;
        if(info.rcMonitor.top < ctx->rect.top) ctx->rect.top = info.rcMonitor.top;
        if(info.rcMonitor.right > ctx->rect.right) ctx->rect.right = info.rcMonitor.right;
        if(info.rcMonitor.bottom > ctx->rect.bottom) ctx->rect.bottom = info.rcMonitor.bottom;
    }
    return true;
}

int32x4 sys_get_rect(void) {
    TotalRectContext ctx;
    ctx.rect.left = 6900000;
    ctx.rect.top = 6900000;
    ctx.rect.right = -6900000;
    ctx.rect.bottom = -6900000;
    EnumDisplayMonitors(0, 0, _win_get_total_rect_callback, (LPARAM)&ctx);
    int32x4 result;
    result.DUMMYSTRUCT.x = ctx.rect.left;
    result.DUMMYSTRUCT.y = ctx.rect.top;
    result.DUMMYSTRUCT.z = ctx.rect.right;
    result.DUMMYSTRUCT.w = ctx.rect.bottom;
    return result;
}

File_Handle sys_get_stdout(void) {
    return (File_Handle)GetStdHandle((u32)-11);
}
File_Handle sys_get_stderr(void) {
    return (File_Handle)GetStdHandle((u32)-12);
}

u32 sys_write(File_Handle f, void *data, u64 size) {
    u32 written;
    WriteFile(f, data, size, (unsigned long*)&written, 0);
    return written;
}

u32 sys_write_string(File_Handle f, string s) {
    return sys_write(f, s.data, s.count);
}
#if (OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)
Surface_Handle sys_make_surface(Surface_Desc desc) {
    (void)desc;
    return 0;
}
void surface_close(Surface_Handle s) {
    (void)s;
}
#else // (OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)

#endif // !(OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM)

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

    const int WIN32_MAX_STACK_FRAMES = 64;
    const int WIN32_MAX_SYMBOL_NAME_LENGTH = 512;

    for (int i = 0; i < WIN32_MAX_STACK_FRAMES; i++) {
        if (!StackWalk64(machineType, process, thread, &stack, &context, 0, SymFunctionTableAccess64, SymGetModuleBase64, 0)) {
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
                u8 buffer[32];
                string line_str = (string){0, buffer};
                line_str.count = format_signed_int(line.LineNumber, 10, buffer, 32);
                sys_write_string(handle, line_str);
                sys_write_string(handle, STR(" "));
                sys_write_string(handle, STR(symbol->Name));
                sys_write_string(handle, STR("\n"));
                
            } else {
                u8 buffer[1024];
                string result = (string) {0, buffer};
                result.count = (u64)(symbol->NameLen + 1);
                memcpy(result.data, symbol->Name, symbol->NameLen + 1);
                sys_write_string(handle, result);
            }
            
        } else {
            sys_write_string(handle, STR("<unavailable>\n"));
        }
    }
}

#endif // (OS_FLAGS & OS_FLAG_WINDOWS) == OS_FLAG_WINDOWS

#endif // OSTD_IMPL