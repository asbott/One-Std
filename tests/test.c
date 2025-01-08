
//#include <windows.h>

#ifndef TEST_NO_IMPL
#define OSTD_IMPL

#define OGA_IMPL_VULKAN
#endif // TEST_NO_IMPL
#include "../src/ostd.h"
//#include "../ostd_single_header.h"

void test_base(void);
void test_sys1(void);
void test_sys2(void);
void test_memory(void);
void test_print(void);

int main(void) {
    sys_write_string(sys_get_stdout(), STR("Hello, ostd!\n"));

    test_base();
    test_sys1();
    test_memory();
    test_print();
    test_sys2();
    
    u64 device_count = 0;
    Oga_Device *devices = oga_get_devices(get_temp(), &device_count);

    assert(device_count > 0 && device_count < 128);
    
    for (u32 i = 0; i < device_count; i += 1) {
        Oga_Device *device = devices + i;
        
        string depth_str = oga_format_str(device->depth_format);
        print(("Device %u:\n"), i);
        print(("\t%s - %s %s\n"), STRN(device->device_name_length, device->device_name_data), device->vendor_name, STRN(device->driver_version_length, device->driver_version_data));
        print("\tKind: ");
        switch (device->kind) {
            case OGA_DEVICE_DISCRETE: print("Discrete GPU\n"); break;
            case OGA_DEVICE_INTEGRATED: print("Integrated GPU\n"); break;
            case OGA_DEVICE_CPU: print("CPU\n"); break;
            case OGA_DEVICE_OTHER: print("Other\n"); break;
            default: break;
        }
        print(("\tDepth: %s\n"), depth_str);
        
        print(("\t%u Logical Engine families:\n"), device->logical_engine_family_count);
        for (u32 j = 0; j < device->logical_engine_family_count; j += 1) {
            Oga_Logical_Engine_Family_Info family = device->logical_engine_family_infos[j];
            
            print(("\t\t"));
            
            if (family.flags & OGA_LOGICAL_ENGINE_GRAPHICS) print(("GRAPHICS "));
            if (family.flags & OGA_LOGICAL_ENGINE_COMPUTE) print(("COMPUTE "));
            if (family.flags & OGA_LOGICAL_ENGINE_TRANSFER) print(("TRANSFER "));
            if (family.flags & OGA_LOGICAL_ENGINE_PRESENT) print(("PRESENT "));
            
            print(("| %u logical_engines\n"), family.logical_engine_capacity);
            
        }
        u64 mem_gb = device->total_gpu_local_memory/(1024*1024);
        print(("\tLocal memory: %u MB\n"), mem_gb);
        print(("\t%u Heaps:\n"), device->memory_heap_count);
        for (u64 j = 0; j < device->memory_heap_count; j += 1) {
            print(("\t\t"));
            
            Oga_Memory_Heap heap = device->memory_heaps[j];
            if (heap.properties & OGA_MEMORY_PROPERTY_GPU_LOCAL) 
                print(("GPU-LOCAL "));
            if (heap.properties & OGA_MEMORY_PROPERTY_GPU_TO_CPU_MAPPABLE) 
                print(("CPU-MAPPABLE "));
            if (heap.properties & OGA_MEMORY_PROPERTY_GPU_TO_CPU_REFLECTED) 
                print(("CPU-REFLECTED "));
            if (heap.properties & OGA_MEMORY_PROPERTY_GPU_TO_CPU_CACHED) 
                print(("CPU-CACHED "));
                
            mem_gb = heap.size/(1024*1024);
            print(("| %u MB\n"), mem_gb);
        }
    }
    
    Oga_Pick_Device_Result pick0 = oga_pick_device(
        OGA_DEVICE_PICK_PREFER_DISCRETE,
        0,
        0
    );
    Oga_Pick_Device_Result pick1 = oga_pick_device(
        OGA_DEVICE_PICK_PREFER_INTEGRATED,
        0,
        0
    );
    Oga_Pick_Device_Result pick2 = oga_pick_device(
        OGA_DEVICE_PICK_PREFER_CPU,
        0,
        0
    );
    Oga_Pick_Device_Result pick3 = oga_pick_device(
        OGA_DEVICE_PICK_REQUIRE_CPU,
        0,
        0
    );
    Oga_Pick_Device_Result pick4 = oga_pick_device(
        OGA_DEVICE_PICK_REQUIRE_DISCRETE,
        0,
        0
    );
    
    string s0 = (pick0.passed ? (STRN(pick0.device.device_name_length, pick0.device.device_name_data)) : STR("NONE"));
    print("PREFER_DISCRETE: %s\n", s0);
    string s1 = (pick1.passed ? (STRN(pick1.device.device_name_length, pick1.device.device_name_data)) : STR("NONE"));
    print("PREFER_INTEGRATED: %s\n", s1);
    string s2 = (pick2.passed ? (STRN(pick2.device.device_name_length, pick2.device.device_name_data)) : STR("NONE"));
    print("PREFER_CPU: %s\n", s2);
    string s3 = (pick3.passed ? (STRN(pick3.device.device_name_length, pick3.device.device_name_data)) : STR("NONE"));
    print("REQUIRE_CPU: %s\n", s3);
    string s4 = (pick4.passed ? (STRN(pick4.device.device_name_length, pick4.device.device_name_data)) : STR("NONE"));
    print("REQUIRE_DISCRETE: %s\n", s4);

    Oga_Device target_device = pick0.device;

    u64 family_index_graphics = U64_MAX;
    u64 family_index_present = U64_MAX;
    u64 family_index_compute = U64_MAX;

    // Just pick the first logical_engine that has the flag we need.
    for (u32 family_index = 0; family_index < target_device.logical_engine_family_count; family_index += 1) {
        Oga_Logical_Engine_Family_Info family = target_device.logical_engine_family_infos[family_index];
        
        if ((family.flags & OGA_LOGICAL_ENGINE_GRAPHICS) && family_index_graphics == U64_MAX) {
            family_index_graphics = family_index;
        } 
        if ((family.flags & OGA_LOGICAL_ENGINE_PRESENT) && family_index_present == U64_MAX) {
            family_index_present = family_index;
        } 
        if ((family.flags & OGA_LOGICAL_ENGINE_COMPUTE) && family_index_compute == U64_MAX) {
            family_index_compute = family_index;
        } 
    }
    
    if (family_index_graphics == U64_MAX) {
        print("Error: no graphics logical_engines.\n");
        return 1;
    }
    if (family_index_present == U64_MAX) {
        print("Error: no present logical_engines.\n");
        return 1;
    }
    if (family_index_compute == U64_MAX) {
        print("Error: no compute logical_engines.\n");
        return 1;
    }
    

    Oga_Context_Desc context_desc = (Oga_Context_Desc){0};
    
    Oga_Logical_Engines_Create_Desc *graphics_desc = &context_desc.logical_engine_create_descs[family_index_graphics];
    Oga_Logical_Engines_Create_Desc *present_desc = &context_desc.logical_engine_create_descs[family_index_present];
    Oga_Logical_Engines_Create_Desc *compute_desc = &context_desc.logical_engine_create_descs[family_index_compute];
    
    Oga_Logical_Engine_Family_Info graphics_family = target_device.logical_engine_family_infos[family_index_graphics];
    Oga_Logical_Engine_Family_Info present_family = target_device.logical_engine_family_infos[family_index_present];
    Oga_Logical_Engine_Family_Info compute_family = target_device.logical_engine_family_infos[family_index_compute];
    
    // Try creating separate logical_engines if logical_engines belong to same family and capacity allows.
    
    graphics_desc->count = min(graphics_desc->count+1, graphics_family.logical_engine_capacity);
    u64 logical_engine_index_graphics = graphics_desc->count-1; 
    
    present_desc->count = min(present_desc->count+1, present_family.logical_engine_capacity);
    u64 logical_engine_index_present = present_desc->count-1;
    
    compute_desc->count = min(compute_desc->count+1, compute_family.logical_engine_capacity);
    u64 logical_engine_index_compute = compute_desc->count-1;
    
    Oga_Context context;
    Oga_Result context_result = oga_init_context(target_device, context_desc, &context); 
    if (context_result != OGA_OK) {
        string err_name = oga_get_result_name(context_result);
        string err_msg = oga_get_result_message(context_result);
        print("oga_init_failed with error %s: '%s'\n", err_name, err_msg);
        return 1;
    }
    
    Oga_Logical_Engine graphics_logical_engine = context.logical_engines_by_family[family_index_graphics].logical_engines[logical_engine_index_graphics];
    Oga_Logical_Engine present_logical_engine = context.logical_engines_by_family[family_index_present].logical_engines[logical_engine_index_present];
    Oga_Logical_Engine compute_logical_engine = context.logical_engines_by_family[family_index_compute].logical_engines[logical_engine_index_compute];

    print("Graphics logical_engine family %u, index %u\n", family_index_graphics, graphics_logical_engine.index);
    print("Present logical_engine family %u, index %u\n", family_index_present, present_logical_engine.index);
    print("Compute logical_engine family %u, index %u\n", family_index_compute, compute_logical_engine.index);

#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
    Surface_Desc desc = DEFAULT(Surface_Desc);
    Surface_Handle surface = sys_make_surface(desc);
    assertmsg(surface, ("Failed making surface"));
#else
    Surface_Handle surface = sys_get_surface();
#endif
    bool running = true;

    while (running) {
        surface_poll_events(surface);

        if (surface_should_close(surface)) {
            running = false;
            break;
        }
    }

#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
    surface_close(surface);
#endif
}

void test_base(void) {
    assert(sizeof(u8) == 1 && (u8)-1 == (u8)0xffu);
    assert(sizeof(s8) == 1 && (s8)-1 == (s8)-0x01);
    assert(sizeof(u16) == 2 && (u16)-1 == (u16)0xffffu);
    assert(sizeof(s16) == 2 && (s16)-1 == (s16)-0x0001);
    assert(sizeof(u32) == 4 && (u32)-1 == (u32)0xffffffffu);
    assert(sizeof(s32) == 4 && (s32)-1 == (s32)-0x00000001);
    assert(sizeof(u64) == 8 && (u64)-1 == (u64)0xffffffffffffffffu);
    assert(sizeof(s64) == 8 && (s64)-1 == (s64)-0x0000000000000001);

    assert(sizeof(float32) == 4);
    assert(sizeof(float64) == 8);
#if HAS_FLOAT128
    assert(sizeof(float128) == 16);
#endif
}
void test_sys1(void) {
    assert(MAX_SURFACES > 0);

    System_Info info = sys_get_info();
    {
        void *mem = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, 4);
        assert(mem);

        memset(mem, (int)0xDEADBEEF, (sys_uint)info.page_size*4);

        sys_unmap_pages(mem);
    }
    // Address hints isnt supported with emscripten mmap
#if !(OS_FLAGS & OS_FLAG_EMSCRIPTEN)
    {
        // todo(charlie) portable safe virtual base address
        // win64, android arm64  0x0000007cccc00000ULL
        void* addr = (void*)((0x0000007cccc00000ULL + info.granularity - 1) & ~(info.granularity - 1));

        void *mem = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr, 4);
        assert(mem);
        assert(mem == addr);

        memset(mem, (int)0xDEADBEEF, (sys_uint)info.page_size*4);

        sys_unmap_pages(mem);
    }
    {
        u64 page_count = info.granularity / info.page_size;

        // todo(charlie) portable safe virtual base address
        void* addr0 = (void*)((0x40000000 + info.granularity - 1) & ~(info.granularity - 1));
        void *addr1 = (u8*)addr0 + page_count*info.page_size;
        void *addr2 = (u8*)addr1 + page_count*info.page_size;
        void *end = (u8*)addr2 + page_count*info.page_size;

        void *mem0 = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr0, 4);
        void *mem1 = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr1, 4);
        void *mem2 = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr2, 4);

        assert(mem0);
        assert(mem1);
        assert(mem2);

        assert(mem0 == addr0);
        assert(mem1 == addr1);
        assert(mem2 == addr2);

        Mapped_Memory_Info pointers[3];
        u64 pointer_count = sys_query_mapped_regions(addr0, end, pointers, 3);

        assert(pointer_count == 3);

        assert(pointers[0].base == addr0);
        assert(pointers[1].base == addr1);
        assert(pointers[2].base == addr2);

        assert(pointers[0].page_count == 4);
        assert(pointers[1].page_count == 4);
        assert(pointers[2].page_count == 4);
    }
#endif // !(OS_FLAGS & OS_FLAG_EMSCRIPTEN)

    {
        File_Handle hread, hwrite;

        bool ok = sys_make_pipe(&hread, &hwrite);
        assert(ok);

        string a = STR("Hey");

        s64 written = sys_write_string(hwrite, a);
        assert(written == (s64)a.count);

        u8 buf[128];
        string b = (string) { (u64)sys_read(hread, buf, 128), buf };

        assert(b.count == a.count);
        assert(strings_match(a, b));

        sys_close(hread);
        sys_close(hwrite);

        written = sys_write_string(hwrite, a);
        assert(written == -1);

        s64 read = sys_read(hread, buf, 128);
        assert(read == -1);
    }

    // todo(charlie) test rerouting stdout & stderr to a file
}
void test_sys2(void) {
    {
        Physical_Monitor monitors[128];
        u64 num_monitors = sys_query_monitors(0, 0);
        assert(num_monitors != 0);
        sys_query_monitors(monitors, num_monitors);

        for (u64 i = 0; i < num_monitors; i += 1) {
            Physical_Monitor m = monitors[i];
            string name = (string) {m.name_count, m.name};
            i += 1;
            print(("Monitor %i:\n\t%s\n\thz: %i\n\t%ix%i\n\tscale: %f\n\tX: %i, Y: %i\n"),
                (i), name, m.refresh_rate, m.resolution_x, m.resolution_y, m.scale, m.pos_x, m.pos_y);
        }
    }
}

void test_memory(void) {
    System_Info info = sys_get_info();

    {
#if OS_FLAGS & OS_FLAG_EMSCRIPTEN
        Arena arena = make_arena(1024*100, 1024*100);
        assert(arena.allocated_size == ((1024*100 + info.page_size-1) & ~(info.page_size-1)));
        assert(arena.reserved_size  == ((1024*100 + info.page_size-1) & ~(info.page_size-1)));
#else
        Arena arena = make_arena(1024*100, 1024*10);
        assert(arena.allocated_size == ((1024*10 + info.page_size-1) & ~(info.page_size-1)));
        assert(arena.reserved_size  == ((1024*100 + info.page_size-1) & ~(info.page_size-1)));
#endif


        void *mem0 = arena_push(&arena, 1024*10);
        assert(mem0);
        memset(mem0, 0, 1024*10);

        void *mem1 = arena_push(&arena, 1024);
        assert(mem1);
        memset(mem1, 0, 1024);

        free_arena(arena);
    }

    {
        reset_temporary_storage();

        void *mem0 = tallocate(69);
        memset(mem0, 0, 69);

        reset_temporary_storage();

        void *mem1 = tallocate(69);
        assert(mem0 == mem1);
        memset(mem1, 0, 69);

        void *mem2 = tallocate(69);
        assert((u64)mem2 > (u64)mem1 + 69);
    }
}

void test_print(void) {
    char buffer[256];

    string s;
    s.data = (u8*)buffer;
    s.count = 0;

    s.count = format_unsigned_int(12345, 10, s.data, sizeof(buffer));
    assert(strings_match(s, STR("12345")));

    s.count = format_signed_int(-6789, 10, s.data, sizeof(buffer));
    assert(strings_match(s, STR("-6789")));

    s.count = format_signed_int(6789, 10, s.data, sizeof(buffer));
    assert(strings_match(s, STR("6789")));

    s.count = format_float(123.456, 2, s.data, sizeof(buffer));
    assert(strings_match(s, STR("123.45")));

    s.count = format_float(-123.456, 2, s.data, sizeof(buffer));
    assert(strings_match(s, STR("-123.45")));

    s.count = format_unsigned_int(123456789, 10, buffer, 5);
    assert(strings_match(s, STR("12345"))); // Truncated to buffer size

    string result = sprints(get_temp(), STR("Hello, %s!"), STR("World"));
    assert(result.count == 13);
    assert(strings_match(result, STR("Hello, World!")));


    s16 val1 = 42;
    s32 val2 = -812736812;
    result = tprint(("Value1: %i, Value2: %i"), val1, val2);
    assert(strings_match(result, STR("Value1: 42, Value2: -812736812")));

    float32 flt = 3.14159f;
    print(("Testing print: %f\n"), flt);

    s = STR("TEST");
    float32 a = -123.456f;
    s16 b = -255;
    bool c = false;
    result = tprint(("%s, %f, %i, %b %a"), s, a, b, c, s);

    assert(strings_match(result, STR("TEST, -123.45600, -255, false <Unknown format specifier '%a'>")));

    print(("Print tests passed\n"));

    arena_allocator((Arena*)0);
}