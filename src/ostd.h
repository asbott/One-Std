#ifndef OSTD_H_
#define OSTD_H_

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wattributes"
#ifdef __EMSCRIPTEN__
#pragma clang diagnostic ignored "-Wpadded"
#endif // __EMSCRIPTEN__
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

#include "graphics.h"

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

#endif // OSTD_H_

