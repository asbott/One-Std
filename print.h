
#include <stdarg.h>



// This shouldn't be called directly, see macro 'format_string'
typedef struct Format_String_Desc {
    void *buffer;
    u64 buffer_size;
    string fmt;
} Format_String_Desc;
u64 format_string_impl(Format_String_Desc desc, u64 arg_count, ...);

inline Format_String_Desc make_format_string_desc(void *buffer, u64 buffer_size, string fmt) {
    Format_String_Desc desc;
    desc.buffer = buffer;
    desc.buffer_size = buffer_size;
    desc.fmt = fmt;
    return desc;
}
    
#define format_string(buffer, buffer_size, fmt, ...) MAKE_WRAPPED_CALL(format_string_impl, make_format_string_desc(buffer, buffer_size, fmt), __VA_ARGS__)


u64 format_signed_int(s64 x, int base, void *buffer, u64 buffer_size);
u64 format_unsigned_int(u64 x, int base, void *buffer, u64 buffer_size);
u64 format_float(float64 x, int decimal_places, void *buffer, u64 buffer_size);


#ifdef OSTD_IMPL

u64 format_string_impl(Format_String_Desc desc, u64 arg_count, ...) {
    va_list va_args;
    va_start(va_args, arg_count);
    
    string fmt = desc.fmt;
    void *buffer = desc.buffer;
    u64 buffer_size = desc.buffer_size;
    
    Var_Arg args[1024];
    
    u64 i;
    for (i = 0; i < arg_count; i += 1)
        args[i] = va_arg(va_args, Var_Arg);
    
    va_end(va_args);
    
    u64 next_arg_index = 0;
    
    u64 written = 0;
    
    for (i = 0; i < fmt.count-1; i += 1) {
        if (fmt.data[i] == '%' && next_arg_index < arg_count) {
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
                
                if (buffer && to_write) {
                    memcpy((u8*)buffer + written, str.data, to_write);
                }
                
                written += str.count;
            }
            
            next_arg_index += 1;
        } else {
            if (buffer && written + 1 <= buffer_size)
                *((u8*)buffer + written) = fmt.data[i];
            written += 1;
        }
    }
    
    return written;
}

// todo(charlie) make a less naive and slow version of this !
u64 format_int(void *px, int base, bool _signed, void *buffer, u64 buffer_size) {
    assert(base >= 2 && base <= 36); // 0-z
    
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
        abs_val = neg ? (signed_val*-1) : signed_val;
    }
    else {
        abs_val = *(u64*)px;
    }
    
    while (abs_val != 0) {
        u8 digit = digits[abs_val%base];
        
        if (buffer && written < buffer_size)
            *((u8*)tail - written) = digit;
        
        written += 1;
        
        abs_val /= base;
    }
    
    // Write the '-' if negative number
    if (neg) {
        if (buffer && written < buffer_size)
            *((u8*)tail - written) = '-';
        
        written += 1;
    }
    
    // Since we wrote right-to-left, shift down to overwrite the bytes we did not touch
    if (buffer && written <= buffer_size) {
        memmove(buffer, (u8*)tail - written + 1, written);
    }
    
    return written;
}
u64 format_signed_int(s64 x, int base, void *buffer, u64 buffer_size) {
    return format_int(&x, base, true, buffer, buffer_size);
}
u64 format_unsigned_int(u64 x, int base, void *buffer, u64 buffer_size) {
    return format_int(&x, base, false, buffer, buffer_size);
}

u64 format_float(float64 x, int decimal_places, void *buffer, u64 buffer_size) {
    assert(decimal_places >= 0);

    u64 written = 0;

    
    bool neg = x < 0.0;
    if (neg) x = -x;

    s64 integral_part = (s64)x;
    float64 fractional_part = x - integral_part;

    written += format_signed_int(integral_part, 10, buffer, buffer_size);

    if (decimal_places > 0 && written < buffer_size) {
        *((u8*)buffer + written) = '.';
        written += 1;
    }

    for (int i = 0; i < decimal_places && written < buffer_size; i++) {
        fractional_part *= 10.0;
        u8 digit = (u8) fractional_part; 
        fractional_part -= digit;

        *((u8*)buffer + written) = '0' + digit;
        written += 1;
    }

    if (neg && written < buffer_size) {
        memmove((u8*)buffer + 1, buffer, written);
        *((u8*)buffer) = '-';
        written += 1;
    }

    return written;
}

#endif // OSTD_IMPL