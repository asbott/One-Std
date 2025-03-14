

# One Standard Library

The only SINGLE-HEADER C99 library you will ever need, with the aim of targetting all modern platforms, and making portable low-level programming sane.

- One Graphics API (OGA)
- One Standard (shader) Language (OSL)
- One System/OS API
- One Base C Library
- One Audio Library (OAL) ((TBD))
- ONE HEADER FILE

Everything is designed to be as simple to use as possible.

See tests/ for example code.

TOC
   - [Licensing/Information](#licensinginformation)
   - [OGA](#oga)
   - [OSL](#osl)
   - [System API](#system-api)
   - [Current State](#current-state)
   - [Quick Guide](#quick-guide)





## Licensing/Information

You're welcome to use One-Standard-Library and any of its modules for personal projects or within small/indie game studios. While attribution isn't required, it is appreciated. For projects involving teams of more than about 10 people, please contact me at charlie.malmqvist1@gmail.com to discuss licensing options. If you’re ever in doubt, just get in touch — I’ll likely give you the green light.

I also run a software business specializing in engine, graphics, and video game programming and consulting. If you're interested in integrating this library or need a custom engine, tool, or software solution, don’t hesitate to drop me an email at charlie.malmqvist1@gmail.com.

## OGA

One Graphics Library

The verbosity of Vulkan/D3D12, but with a well-designed API and completely cross-platform. Also integrates OSL gpu programming language.

Currently targets:
    - Vulkan
    
Upcoming Targets:
 - Console Graphics API's (Need dev kits. Would be closed-source and only given to licensed entities.)
 - D3D12
 - Metal
 - CPU (Software Rendering)

## OSL

One Standard Language

A dead-simple GPU programming language that doesn't pretend that it's anything else than a gpu programming language. Compile OSL code to your target API (or whatever you want to compile to) with a single function call `osl_compile()`.

Currently targets:
    - SPIR-V

Upcoming Targets:
 - HLSL or DXIL not sure yet (maybe both?)
 - Metal
 - Console Shading Languages (Need dev kits. Would be closed-source and only given to licensed entities.)
    
## System API

TBD

## Base C Library

TBD

## Current State

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

## Quick Start Guide

1. Download `ostd_single_header.h`
2. `#include "ostd_single_header.h"`
3. If you want to use OGA with Vulkan backend, make sure <vulkan/vulkan.h> is in the include path.


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
