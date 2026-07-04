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

OSTD_LIB void sys_logs_enable_print(File_Handle pipe, System_Log_Kind enabled_kinds, System_Log_Category enabled_categories);
OSTD_LIB void sys_logs_disable_print(void);

OSTD_LIB bool sys_read_entire_file(Allocator a, string path, string *result);
OSTD_LIB bool sys_write_entire_file(string path, string data);

OSTD_LIB bool sys_get_absolute_path(Allocator a, string path, string *result);

#ifdef OSTD_IMPL

unit_local File_Handle _ostd_log_print_pipe = 0;
unit_local System_Log_Kind _ostd_enabled_log_kinds = 0;
unit_local System_Log_Category _ostd_enabled_log_categories = 0;
unit_local Mutex _ostd_log_mutex;
unit_local bool _ostd_log_mutex_initted = false;

void _ostd_print_log(System_Log l) {
    if (!_ostd_log_print_pipe) return;
    
    if (!(_ostd_enabled_log_kinds & l.kind) || !(_ostd_enabled_log_categories & l.category)) {
        return;
    }
    
    string function = (string) { l.function_length, l.function };
    string message = (string) { l.message_length, l.message };
    string os_name = (string) { l.os_name_length, l.os_name };
    
    sys_mutex_acquire(_ostd_log_mutex);
    
    switch (l.kind) {
        case SYSTEM_LOG_OK: {
            fprint(_ostd_log_print_pipe, "Function: %s\nID: %u\nOK\nMessage: %s\n", function, l.id, message);
            break;
        }
        case SYSTEM_LOG_OS_CALL: {
            fprint(_ostd_log_print_pipe, "Function: %s\nID: %u\nOS CALL: %s\nResult: %u\nHandle: %x\nMessage: %s\n", function, l.id, os_name, l.os_number, l.os_handle, message);
            break;
        }
        case SYSTEM_LOG_ERROR: {
            fprint(_ostd_log_print_pipe, "Function: %s\nID: %u\nERROR: %u\nMessage: %s\n", function, l.id, l.error, message);
            break;
        }
        case SYSTEM_LOG_ENTER_SYS_FUNCTION: {
            fprint(_ostd_log_print_pipe, "====== SYSTEM FUNCTION: %s\nID: %u\n", function, l.id);
            break;
        }
        case SYSTEM_LOG_ALL: break;
    }
    
    sys_print_stack_trace(_ostd_log_print_pipe);
    
    fprint(_ostd_log_print_pipe, "\n\n");
    
    sys_mutex_release(_ostd_log_mutex);
}

void sys_logs_enable_print(File_Handle pipe, System_Log_Kind enabled_kinds, System_Log_Category enabled_categories) {
    if (!_ostd_log_mutex_initted) {
        sys_mutex_init(&_ostd_log_mutex);
    }
    
    _ostd_log_print_pipe = pipe;
    _ostd_print_log_fn = _ostd_print_log;
    _ostd_enabled_log_kinds = enabled_kinds;
    _ostd_enabled_log_categories = enabled_categories;
    
}

void sys_logs_disable_print(void) {
    _ostd_log_print_pipe = 0;
    _ostd_print_log_fn = 0;
}

bool sys_read_entire_file(Allocator a, string path, string *result) {
    const int MAX_ATTEMPTS = 100;
    int attempts = MAX_ATTEMPTS;
    File_Handle f = 0;
    while (f == 0 && attempts > 0) {
        f = sys_open_file(path, FILE_OPEN_READ);
        attempts -= 1;
    }
    if (!f) return false;
    
    u64 size = sys_get_file_size(f);
    
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
