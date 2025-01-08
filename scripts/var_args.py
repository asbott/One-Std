
# Helper to generate a lot of macros for var args in var_args.py
# This script is not actually necessary, it's just a helper if you want
# to change the amount of max var args.



def generate_macros(N):
    macros = []

    macros.append(f'#define MAX_VAR_ARGS {N}\n')

    # PP_NARG and related macros
    macros.append('''#define PP_NARG(...) PP_ARG_N(__VA_ARGS__, PP_RSEQ_N())\n''')
    macros.append('''#define PP_ARG_N(...) PP_ARG_N_(__VA_ARGS__)\n''')
    
    # PP_RSEQ_N
    rseq = ','.join(map(str, range(N*2, -1, -1)))
    macros.append(f'#define PP_RSEQ_N() {rseq}\n')
    
    u = ", ".join([f"_{it}" for it in range(N*2+1)])
    
    macros.append(f"#define PP_ARG_N_({u}, N, ...) N\n")
    
    # PP_CONCATENATE macros
    macros.append('''#define PP_CONCATENATE(a, b) PP_CONCATENATE_(a, b)
#define PP_CONCATENATE_(a, b) a##b\n''')
    
    # _WRAP_ARGS_ macros
    for i in range(0, N + 1):
        if i == 0:
            macro = f'''#define _WRAP_ARGS_{i}(TARGET, FIRST) \\
    TARGET(FIRST, {i})\n'''
        else:
            args = ', '.join([f'_WRAP_VAR(_{j})' for j in range(i)])
            params = ', '.join([f'_{{{j}}}' for j in range(i)])
            u = ", ".join([f"_{it}" for it in range(i)])
            macro = f"#define _WRAP_ARGS_{i}(TARGET, FIRST, {u}) \\\n\tTARGET(FIRST, {i}, {args})\n"
        macros.append(macro)
    
    # _WRAP_ARGS_DISPATCH macro
    macros.append(f'''#define _WRAP_ARGS_DISPATCH(N, TARGET, ...) \\
    PP_CONCATENATE(_WRAP_ARGS_, N)(TARGET, __VA_ARGS__)\n''')
    
    # MAKE_WRAPPED_CALL macro
    macros.append('''#define MAKE_WRAPPED_CALL(TARGET, ...) \\
    _WRAP_ARGS_DISPATCH(PP_NARG(__VA_ARGS__), TARGET, __VA_ARGS__)\n''')
    
    return '\n'.join(macros)


with open("src/var_args_macros.h", 'w') as file:
    file.write(str(generate_macros(70)))