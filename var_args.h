
// This is C90 so we need to do some macro nonsense to be able to do any form of variadic stuff.
// It's to get slightly better var args than the standard C va_list.
/*
    To make a variadic arguments procedure:
    
    #define do_thing(arg1, ...)\
        MAKE_WRAPPED_CALL(do_thing_impl, arg1, __VA_ARGS__)
    
    void do_thing_impl(int arg1, u64 arg_count, ...) {
        Var_Arg args[MAX_VAR_ARGS];
        get_var_args(arg_count, args);
    
        
    }
*/

#define get_var_args(count, pargs) {\
    va_list va_args;\
    va_start(va_args, count);\
    \
    for (u64 i = 0; i < count; i += 1)\
        pargs[i] = va_arg(va_args, Var_Arg);\
    \
    va_end(va_args);\
}

typedef struct Var_Arg {
    u64 int_val;
    float64 flt_val;
    string str_val;
    
    u64 size;
} Var_Arg;

// todo(charlie) this is a crazy amount of branching being concealed by a macro. Should 
// probably revisit this.
#define _WRAP_VAR(x) (Var_Arg) {sizeof(x) >= 8 ? *(u64*)&x : sizeof(x) >= 4 ? *(u32*)&x : sizeof(x) >= 2 ? *(u16*)&x : *(u8*)&x, sizeof(x) >= 8 ? *(float64*)&x : sizeof(x) >= 4 ? *(float32*)&x : 0, sizeof(x) >= sizeof(string) ? *(string*)&(x) : (string){0}, sizeof(x)}

#include "var_args_macros.h"