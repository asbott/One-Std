

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


typedef struct System_Info {
    u64 page_size;
    u64 granularity;
} System_Info;

inline System_Info sys_get_info(void);

typedef void* File_Handle;

File_Handle sys_get_stdout(void);
File_Handle sys_get_stderr(void);

u32 sys_write(File_Handle f, void *data, u64 size);
u32 sys_write_string(File_Handle f, string s);






#ifdef OSTD_IMPL

#if (OS_FLAGS & OS_FLAG_WINDOWS) == OS_FLAG_WINDOWS

#ifndef _WINDOWS_
// We manually declare windows functions so we don't need to bloat compilation and
// namespace with windows.h

#include "windows_loader.h"

#endif // _WINDOWS_

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

inline System_Info sys_get_info(void) {
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

#endif // (OS_FLAGS & OS_FLAG_WINDOWS) == OS_FLAG_WINDOWS

#endif // OSTD_IMPL