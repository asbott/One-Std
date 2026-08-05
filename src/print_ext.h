#ifndef _PRINT2_H
#define _PRINT2_H

#ifndef _PRINT1_H
#include "print_base.h"
#endif // _PRINT1_H
#ifndef _MEMORY_H
#include "memory.h"
#endif // _MEMORY_H

#define sprint(allocator, /*fmt, */...)  _sprint_ugly(allocator, __VA_ARGS__)
#define sprints(allocator, /*fmt, */...) _sprints_ugly(allocator, __VA_ARGS__)
#define tprint(/*fmt, */...)             _tprint_ugly(__VA_ARGS__)
#define tprints(/*fmt, */...)            _tprints_ugly(__VA_ARGS__)

OSTD_LIB string sprint_args(Allocator a, string fmt, u64 arg_count, Var_Arg *args);
OSTD_LIB string tprint_args(string fmt, u64 arg_count, Var_Arg *args);

#define _sprint_ugly(allocator, ...)\
    MAKE_WRAPPED_CALL(sprint_impl, _make_print_desc_allocator(allocator, STR(PP_FIRST_ARG(__VA_ARGS__)), 0), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _sprints_ugly(allocator, ...)\
    MAKE_WRAPPED_CALL(sprint_impl, _make_print_desc_allocator(allocator, PP_FIRST_ARG(__VA_ARGS__), 0), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _tprint_ugly(...)\
    MAKE_WRAPPED_CALL(tprint_impl, _make_print_desc_allocator((Allocator){0}, STR(PP_FIRST_ARG(__VA_ARGS__)), 0), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _tprints_ugly(...)\
    MAKE_WRAPPED_CALL(tprint_impl, _make_print_desc_allocator((Allocator){0}, PP_FIRST_ARG(__VA_ARGS__), 0), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
    
typedef struct _Print_With_Mem_Desc {
    Allocator a;
    string fmt;
    File_Handle file;
} _Print_With_Mem_Desc;

unit_local inline _Print_With_Mem_Desc _make_print_desc_allocator(Allocator a, string fmt, File_Handle f) {
    return (_Print_With_Mem_Desc) {a, fmt, f};
}
    
string sprint_impl(_Print_With_Mem_Desc desc, u64 arg_count, ...);
string tprint_impl(_Print_With_Mem_Desc desc, u64 arg_count, ...);

#ifdef OSTD_IMPL

string sprint_impl(_Print_With_Mem_Desc desc, u64 arg_count, ...) {
    Var_Arg args[MAX_VAR_ARGS];
    get_var_args(arg_count, args);
    return sprint_args(desc.a, desc.fmt, arg_count, args);
}
string tprint_impl(_Print_With_Mem_Desc desc, u64 arg_count, ...) {
    Var_Arg args[MAX_VAR_ARGS];
    get_var_args(arg_count, args);
    return tprint_args(desc.fmt, arg_count, args);
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

#endif

#endif // _PRINT2_H

