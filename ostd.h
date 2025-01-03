
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-library-redeclaration"
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#pragma clang diagnostic ignored "-Wnewline-eof"
#pragma clang diagnostic ignored "-Wkeyword-macro"
#endif

#include "base.h"

#include "math.h"

#include "utility.h"

#include "string.h"

#include "system.h"

#include "unicode.h"

#include "memory.h"

#include "var_args.h"
#include "print.h"

#ifdef OSTD_NO_IGNORE_WARNINGS
#pragma clang diagnostic pop
#endif // OSTD_NO_IGNORE_WARNINGS