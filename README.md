
# One Standard Library

This aims to completely replace the C standard libraries which much better choices, portable lower level API's, and over all: simplicity.

The idea is to target all modern platforms:
    - Windows
    - Linux
    - MacOS
    - Android
    - iOS
    - Web
    - Consoles (When we're licensed. Would be closed-source and only given to licensed entities.)

The C standard library helps us target multiple platforms for some very basic operations. But there is no serious program which doesn't need to mostly do platform-specific code outside of the C std. 

So what if there was a standard library that:
    a) Was built from scratch with no dependencies on C routines or headers, which MUCH better design choices for targetting modern systems and building realtime applications.
    b) Had low-level API's for everything your program needs: System Operations, Audio playback buffer, Vulkan-like graphics.
    c) Was not locked behind a century old committee that has to conform to ancient, outdated and simply poorly designed standards.
    d) Prioritize low code bloat and compilation speed
    e) Self-documents its code with readable code and comments
    f) Included in your codebase with a single header !!!

- You should not need hundreds of lines of code on each target system to get a basic audio playback buffer.

- You should not need to rely on multiple different libraries to do basic things like opening a window or interact with your graphics hardware.


## Getting started

1. Download `ostd_single_header.h`
2. `#include "ostd_single_header.h"`

### Using OGA (One Graphics API)

By default, if `OSTD_IMPL` is defined, the graphics API will be implemented with a software
renderer.
If you want to do hardware accellerated graphics, you need to specify which graphics API implementation to use.

If you don't care which specific graphics API is used, you can do:
`#define OGA_IMPL_AUTO` 
And an appropriate implementation will be selected for the target system.

To choose a specific implementation:
For vulkan: `#define OGA_IMPL_VULKAN`
For D3D12: `#define OGA_IMPL_D3D12`
For Metal: `#define OGA_IMPL_METAL`
For WebGPU: `#define OGA_IMPL_WEBGPU`