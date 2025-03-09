// I try to compile with -pedantic and -Weverything, but get really dumb warnings like these,
// so I have to ignore them.
#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-macros"
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wattributes"
#pragma clang diagnostic ignored "-Wreserved-identifier"
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wcast-align"
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Wunused-const-variable"
#if __STDC_VERSION__ == 202311
#pragma clang diagnostic ignored "-Wpre-c23-compat"
#endif
#ifdef __EMSCRIPTEN__
#pragma clang diagnostic ignored "-Wpadded"
#endif // __EMSCRIPTEN__
#if defined(_MSC_VER) || defined(__EMSCRIPTEN__)
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif
#endif // __clang__
