#ifndef OSTD_H_
#define OSTD_H_

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

// I try to compile with -pedantic and -Weverything, but get really dumb warnings like these,
// so I have to ignore them.
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wattributes"
#pragma clang diagnostic ignored "-Wreserved-identifier"
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wcast-align"
#ifdef __EMSCRIPTEN__
#pragma clang diagnostic ignored "-Wpadded"
#endif // __EMSCRIPTEN__
#ifdef _MSC_VER
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif
#endif // __clang__

#include "base.h"

#include "math.h"

#include "utility.h"

#include "string.h"

#include "system.h"

#include "unicode.h"

#include "memory.h"

#include "var_args.h"
#include "print.h"

#include "system2.h"

#ifndef OSTD_NO_GRAPHICS
#include "graphics.h"
#endif // OSTD_NO_GRAPHICS


#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

#endif // OSTD_H_

