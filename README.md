
[https://github.com/asbott/One-Std](https://github.com/asbott/One-Std)

# One Standard Library

A C99 standard library to replace the mess which is the C standard library can be included with a single header. Focus on simplicity, speed, self-containedness and reasonableness. Also contains a graphics API that currently has vulkan backend implemented. Can be compiled freestanding, only linking to necessary system libraries. No CRT needed.


The idea is to target all modern platforms:
 - Android
 - iOS
 - Consoles (Once I manage to get licensed. Would be closed-source and only given to licensed entities.)
 - Web
 - Windows
 - MacOS
 - Linux

At the moment I mostly test on Windows, but every now and then I do a round of maintenance for Linux, Android & Web.

OGA currently only targets Vulkan, which means the OSL shader compiler currently targets SPIR-V.

The source code is in src/, but before pushing I generate single-headers in one-headers/ if you only want some of the modules to be compiled. If you want to include the library in its entirety, you would just grab ostd_single_header.h.

To compile the library, you must `#define OSTD_IMPL`. If you don't want graphics or window system to be compiled, do `#define OSTD_HEADLESS`. 
