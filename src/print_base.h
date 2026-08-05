#ifndef _PRINT1_H
#define _PRINT1_H

#ifndef _BASE_H
#include "base.h"
#endif // _BASE_H
#ifndef _STRING_H
#include "string.h"
#endif // _STRING_H
#ifndef _VAR_ARGS_H
#include "var_args.h"
#endif // _VAR_ARGS_H
#ifndef _SYSTEM_1_H
#include "system_base.h"
#endif // _SYSTEM_1_H


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

//////
// Printing
//////

typedef struct Source_Location {
    u64 line;
    string file;
    string function;
} Source_Location;
#define HERE(...) (Source_Location) {__LINE__, STR(__FILE__), STR(__func__)}


#define print(/*fmt, */...)              _print_ugly(__VA_ARGS__)
#define prints(/*fmt, */...)             _prints_ugly(__VA_ARGS__)
#define fprint(file, /*fmt, */...)       _fprint_ugly(file, __VA_ARGS__)
#define fprints(file, /*fmt, */...)      _fprints_ugly(file, __VA_ARGS__)

OSTD_LIB void   print_args(string fmt, u64 arg_count, Var_Arg *args);
OSTD_LIB void   fprint_args(File_Handle f, string fmt, u64 arg_count, Var_Arg *args);
OSTD_LIB void   log_args(u64 flags, Source_Location location, string fmt, u64 arg_count, Var_Arg *args);

typedef void (*Logger_Proc)(string message, u64 flags, Source_Location location, void *ud);

void default_logger(string message, u64 flags, Source_Location location, void *ud);

OSTD_LIB void set_logger(Logger_Proc proc, void *ud);

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

#define _print_ugly(...)\
    MAKE_WRAPPED_CALL(print_impl, _make_print_desc(STR(PP_FIRST_ARG(__VA_ARGS__)), 0), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _prints_ugly(...)\
    MAKE_WRAPPED_CALL(print_impl, _make_print_desc(PP_FIRST_ARG(__VA_ARGS__), 0), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _fprint_ugly(file, ...)\
    MAKE_WRAPPED_CALL(fprint_impl, _make_print_desc(STR(PP_FIRST_ARG(__VA_ARGS__)), file), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _fprints_ugly(file, ...)\
    MAKE_WRAPPED_CALL(fprint_impl, _make_print_desc(PP_FIRST_ARG(__VA_ARGS__), file), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))

#define _log_ugly(flags, ...)\
    MAKE_WRAPPED_CALL(log_impl, _make_log_desc(STR(PP_FIRST_ARG(__VA_ARGS__)), flags, HERE()), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__, (string){0}))
#define _logs_ugly(flags, ...)\
    MAKE_WRAPPED_CALL(log_impl, _make_log_desc(PP_FIRST_ARG(__VA_ARGS__), flags, HERE()), PP_EXCLUDE_FIRST_ARG(__VA_ARGS__,  (string){0}))

typedef struct _Format_String_Desc {
    void *buffer;
    u64 buffer_size;
    string fmt;
} _Format_String_Desc;
unit_local inline _Format_String_Desc _make_format_string_desc(void *buffer, u64 buffer_size, string fmt) {
    return (_Format_String_Desc) {buffer, buffer_size, fmt};
}

typedef struct _Print_Desc {
    string fmt;
    File_Handle file;
} _Print_Desc;

unit_local inline _Print_Desc _make_print_desc(string fmt, File_Handle f) {
    return (_Print_Desc) {fmt, f};
}

typedef struct _Log_Desc {
    string fmt;
    u64 flags;
    Source_Location location;
} _Log_Desc;
unit_local inline _Log_Desc _make_log_desc(string fmt, u64 flags, Source_Location location) {
    return (_Log_Desc) {fmt, flags, location};
}

u64 format_string_impl(_Format_String_Desc desc, u64 arg_count, ...);

void print_impl(_Print_Desc desc, u64 arg_count, ...);
void fprint_impl(_Print_Desc desc, u64 arg_count, ...);
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
            
            bool ok = true;
            if (i + 2 < fmt.count && fmt.data[i+1] == '.') {
                u64 n = 0;
                string num_slice = STR("");
                
                while (i + 2 + n < fmt.count && (fmt.data[i + 2 + n] >= '0' && fmt.data[i + 2 + n] <= '9')) {
                    n += 1;
                    num_slice = string_slice(fmt, i + 2, n);
                }
                
                u64 new_decimal_places = string_to_unsigned_int(num_slice, 10, &ok);
                
                if (ok) {
                    i += n + 1;
                    decimal_places = new_decimal_places;
                }
            }
            
            if (!ok) {
                char msg[] = "<Could not parse decimal places>";
                memcpy(str.data, msg, sizeof(msg)-1);
                i += 1;
            }
            
            if (ok) {
                if (fmt.data[i+1] == '%') {
                    str = STR("%");
                    i += 1;
                } else if (fmt.data[i+1] == 'u') {
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
                } else if (fmt.data[i+1] == 'x') {
                    str.count = format_unsigned_int(arg.int_val, 16, str.data, 32);
                    i += 1;
                } else if (fmt.data[i+1] == 'f') {
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
            }

            if (str.count) {
                u64 to_write = str.count;

                if (written + to_write > buffer_size) {
                    to_write -= (written + to_write) - buffer_size;
                }

                if (to_write) {
                    if (buffer) memcpy((u8*)buffer + written, str.data, (sys_uint)to_write);
                    written += str.count;
                }
            }

            if (fmt.data[i] != '%' && consumed_args) (*consumed_args) += 1;

            if (fmt.data[i] != '%') next_arg_index += 1;
        } else {
            if (written + 1 <= buffer_size) {
                if (buffer) *((u8*)buffer + written) = fmt.data[i];
                written += 1;
            }
        }
    }

    return written;
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

void print_args(string fmt, u64 arg_count, Var_Arg *args) {
    fprint_args(sys_get_stdout(), fmt, arg_count, args);
}
void fprint_args(File_Handle f, string fmt, u64 arg_count, Var_Arg *args) {
    u64 full_size = format_string_args(0, 0, fmt, arg_count, args, 0);
    u64 buffer_size = KiB(64);
    
    u8 small_buffer[KiB(64)];
    u8 *buffer = small_buffer;
    
    u64 total_written = 0;
    while (total_written < full_size) {
        u64 written = format_string_args(buffer, buffer_size, fmt, arg_count, args, 0);
        
        sys_write(f, buffer, written);
        total_written += written;
    }
}

void log_args(u64 flags, Source_Location location, string fmt, u64 arg_count, Var_Arg *args) {

    u64 full_size = format_string_args(0, 0, fmt, arg_count, args, 0);
    u64 buffer_size = KiB(64);
    
    u8 small_buffer[KiB(64)];
    u8 *buffer = small_buffer;
    
    Logger_Proc logger = (Logger_Proc)_ostd_get_thread_storage()->logger;
    void *ud = _ostd_get_thread_storage()->logger_ud;
    u64 total_written = 0;
    while (total_written < full_size) {
        u64 written = format_string_args(buffer, buffer_size, fmt, arg_count, args, 0);
        
        string s = (string) {written, buffer};
        if (!logger) {
            default_logger(s, flags, location, ud);
        } else {
            logger(s, flags, location, ud);
        }
        
        total_written += written;
    }
}

void default_logger(string message, u64 flags, Source_Location location, void *ud) {
    (void)flags; (void)ud;
    print("%s:%u: %s\n", location.file, location.line, message);
}

OSTD_LIB void set_logger(Logger_Proc proc, void *ud) {
    _ostd_get_thread_storage()->logger = (void*)proc;
    _ostd_get_thread_storage()->logger_ud = ud;
}




#endif // OSTD_IMPL


#endif // _PRINT1_H
