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

bool sys_read_entire_file(Allocator a, string path, string *result);
bool sys_write_entire_file(string path, string data);

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
    assert(size > 0);
    
    *result = string_allocate(a, size);
    s64 readeded =  sys_read(f, result->data, result->count);
    
    if (readeded != (s64)size) {
        deallocate(a, result->data);
        return false;
    }
    
    return true;
}
bool sys_write_entire_file(string path, string data) {
    File_Handle f = sys_open_file(path, FILE_OPEN_WRITE | FILE_OPEN_CREATE | FILE_OPEN_RESET);
    if (!f) return false;
    
    s64 written = sys_write_string(f, data);
    
    return written == (s64)data.count;
}

#endif // OSTD_IMPL

#endif // _SYSTEM_2_H
