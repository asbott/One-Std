#ifndef _VAR_ARGS_H
#define _VAR_ARGS_H

#ifndef _BASE_H
#include "base.h"
#endif // _BASE_H
#ifndef _STRING_H
#include "string.h"
#endif // _STRING_H

// This is C90 so we need to do some macro nonsense to be able to do any form of variadic stuff.
// It's to get slightly better var args than the standard C va_list.
/*
    To make a variadic arguments procedure:
    note the comma-swallowing "##"
    // note(charlie) comma-swallowing is a hit on #Portability

    #define do_thing(arg1, ...)\
        MAKE_WRAPPED_CALL(do_thing_impl, arg1, ##__VA_ARGS__)

    void do_thing_impl(int arg1, u64 arg_count, ...) {
        Var_Arg args[MAX_VAR_ARGS];
        get_var_args(arg_count, args);


    }
*/

#define _VA_LIST_DEFINED
#ifndef va_start
    #if (COMPILER_FLAGS & COMPILER_FLAG_MSC)
        #define va_list  char*

        #define _SLOTSIZEOF(t)  (sizeof(t))
        #define _APALIGN(t,ap)  (__alignof(t))

        #define __crt_va_start(ap, x)  ((void)(__va_start(&ap, x)))
        #define __crt_va_arg(ap, t)                                               \
        ((sizeof(t) > sizeof(uintptr) || (sizeof(t) & (sizeof(t) - 1)) != 0) \
            ? **(t**)(uintptr)((ap += sizeof(uintptr)) - sizeof(uintptr))             \
            :  *(t* )(uintptr)((ap += sizeof(uintptr)) - sizeof(uintptr)))
        #define __crt_va_end(ap)        ((void)(ap = (va_list)0))

        #define va_start __crt_va_start
        #define va_arg   __crt_va_arg
        #define va_end   __crt_va_end
        #define va_copy(destination, source) ((destination) = (source))
    #elif COMPILER_FLAGS & COMPILER_FLAG_GNU
        #define va_start __builtin_va_start
        #define va_list  __builtin_va_list
        #define va_arg   __builtin_va_arg
        #define va_end   __builtin_va_end
        #define va_copy(destination, source) __builtin_va_copy((destination), (source))
    #else
        #include <stdarg.h>
    #endif
#endif // va_start

#define get_var_args(count, pargs) do {\
    va_list va_args;\
    va_start(va_args, count);\
    \
    for (u64 i = 0; i < count; i += 1)\
        pargs[i] = *(va_arg(va_args, Var_Arg*));\
    \
    va_end(va_args);\
} while(0)

typedef struct Var_Arg {
    u64 int_val;
    float64 flt_val;
    string str_val;

    u64 size;
} Var_Arg;

#define _WRAP_VAR(x) &(Var_Arg) {sizeof((x)) >= 8 ? *(u64*)(uintptr)&(x) : sizeof((x)) >= 4 ? *(u32*)(uintptr)&(x) : sizeof((x)) >= 2 ? *(u16*)(uintptr)&(x) : *(u8*)(uintptr)&(x), sizeof((x)) >= 8 ? *(float64*)(uintptr)&(x) : sizeof((x)) >= 4 ? (float64)*(float32*)(uintptr)&(x) : 0, sizeof((x)) >= sizeof(string) ? *(string*)(uintptr)&(x) : (string){0}, sizeof((x))}

#include "var_args_macros.h"

#endif // _VAR_ARGS_H
