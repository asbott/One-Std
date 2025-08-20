#ifndef _SYSTEM_2_H
#define _SYSTEM_2_H

#ifndef _SYSTEM_1_H
#include "system1.h"
#endif // _SYSTEM_1_H
#ifndef _MEMORY_H
#include "memory.h"
#endif // _MEMORY_H
#ifndef _PRINT_H
#include "print.h"
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
    while (attempts--) {
        f = sys_open_file(path, FILE_OPEN_READ);
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
