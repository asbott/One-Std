#ifndef OSTD_H_
#define OSTD_H_

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-library-redeclaration"
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#pragma clang diagnostic ignored "-Wnewline-eof"
#pragma clang diagnostic ignored "-Wkeyword-macro"
#pragma clang diagnostic ignored "-Wreserved-identifier"
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wcast-align"
#pragma clang diagnostic ignored "-Wunused-function"
#ifdef _MSC_VER
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif
#ifdef __EMSCRIPTEN__
#pragma clang diagnostic ignored "-Wpadded"
#endif
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

#include "graphics.h"

#ifdef OSTD_NO_IGNORE_WARNINGS
#pragma clang diagnostic pop
#endif // OSTD_NO_IGNORE_WARNINGS

#endif // OSTD_H_