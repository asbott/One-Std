#if 0
#include "ostd.h" // For syntax highlighting.
#endif

/*

    TODO:

        - Specify int base
            %ib16 - base 16
        - Padding, 0 padding
            %i-4   "   5"
                   "  81"
            %i4    "5   "
                   "81  "
            %i04   "0005"
                   "0081"
        - Decimal places
            %f.3   "1.123"
            %f.5   "1.12340"

            %f04.3 "0001.123""

        - Null terminated string %s0 or %cs or %ns

        - Stack-backed buffered print() (instead of temporary allocation)


*/

//////
// Formatting
//////

// note(charlie) comma-swallowing is a hit on #Portability
#define format_string(buffer, buffer_size, fmt, ...)  _format_string_ugly(buffer, buffer_size, STR(fmt), ##__VA_ARGS__)
#define format_strings(buffer, buffer_size, fmt, ...)  _format_string_ugly(buffer, buffer_size, fmt, ##__VA_ARGS__)

u64 format_string_args(void *buffer, u64 buffer_size, string fmt, u64 arg_count, Var_Arg *args, u64 *consumed_args);

u64 format_signed_int(s64 x, int base, void *buffer, u64 buffer_size);
u64 format_unsigned_int(u64 x, int base, void *buffer, u64 buffer_size);
u64 format_float(float64 x, int decimal_places, void *buffer, u64 buffer_size);

//////
// Printing
//////

typedef struct Source_Location {
    u64 line;
    string file;
    string function;
} Source_Location;
#define HERE(...) (Source_Location) {__LINE__, STR(__FILE__), STR(__func__)}

// note(charlie) comma-swallowing is a hit on #Portability
#define sprint(allocator, fmt, ...)  _sprint_ugly(allocator,  STR(fmt), ##__VA_ARGS__)
#define sprints(allocator, fmt, ...) _sprint_ugly(allocator,  fmt, ##__VA_ARGS__)
#define tprint(fmt, ...)             _tprint_ugly(STR(fmt), ##__VA_ARGS__)
#define tprints(fmt, ...)            _tprint_ugly(fmt, ##__VA_ARGS__)
#define print(fmt, ...)              _print_ugly(STR(fmt), ##__VA_ARGS__)
#define prints(fmt, ...)             _print_ugly(fmt, ##__VA_ARGS__)

string sprint_args(Allocator a, string fmt, u64 arg_count, Var_Arg *args);
string tprint_args(string fmt, u64 arg_count, Var_Arg *args);
void   print_args(string fmt, u64 arg_count, Var_Arg *args);
void   log_args(u64 flags, Source_Location location, string fmt, u64 arg_count, Var_Arg *args);

typedef void (*Logger_Proc)(string message, u64 flags, Source_Location location);
extern Logger_Proc logger;

void default_logger(string message, u64 flags, Source_Location location);
#define log(flags, fmt, ...)              _log_ugly(flags, STR(fmt), ##__VA_ARGS__)
#define logs(flags, fmt, ...)             _log_ugly(flags, fmt, ##__VA_ARGS__)

//////
// Internal
//////

// note(charlie): These bloat the code and makes it less good at self-documenting,
// so I made a prettier indirection for the readable part of the file.

#define _format_string_ugly(buffer, buffer_size, fmt, ...)\
    MAKE_WRAPPED_CALL(format_string_impl, _make_format_string_desc(buffer, buffer_size, fmt), ##__VA_ARGS__)
#define _sprint_ugly(allocator, fmt, ...)\
    MAKE_WRAPPED_CALL(sprint_impl, _make_print_desc(allocator, fmt), ##__VA_ARGS__)
#define _tprint_ugly(fmt, ...)\
    MAKE_WRAPPED_CALL(tprint_impl, _make_print_desc((Allocator){0}, fmt), ##__VA_ARGS__)
#define _print_ugly(fmt, ...)\
    MAKE_WRAPPED_CALL(print_impl, _make_print_desc((Allocator){0}, fmt), ##__VA_ARGS__)

#define _log_ugly(flags, fmt, ...)\
    MAKE_WRAPPED_CALL(log_impl, _make_log_desc((Allocator){0}, fmt, flags, HERE()), ##__VA_ARGS__)

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
} _Print_Desc;
unit_local inline _Print_Desc _make_print_desc(Allocator a, string fmt) {
    return (_Print_Desc) {a, fmt};
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

    u64 n = format_string_args(0, 0, fmt, arg_count, args, 0);

    u8 buffer[4096];
    u64 written = 0;

    while (written < n) {
        u64 to_write = min(n, 4096);
        u64 consumed_args;
        format_string_args(buffer, to_write, fmt, arg_count, args, &consumed_args);
        args += consumed_args;
        arg_count -= consumed_args;

        sys_write(sys_get_stdout(), buffer, to_write);

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

Logger_Proc logger = 0;

#endif // OSTD_IMPL
