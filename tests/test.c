
#ifndef TEST_NO_IMPL
#define OSTD_IMPL

#define OGA_IMPL_VULKAN
#endif // TEST_NO_IMPL
#include "../src/ostd.h"
//#include "../ostd_single_header.h"

// Pre compiled spv for a single instanced triangle at the center of the view
#include "minimal_triangle.spv.h"

// Clang warns if there is a default case in switch covering full enum, but also warns if there
// is not default switch. ?!?!??!?!?!?!?!?!?
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-default"
// And it gives warnings about code not being compliant with pre-C99... Even though I've specified
// std=c99 ....
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
// MSC clang also complains every time I do pointer arithmetic... in C .....
#ifdef _MSC_VER
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif



void test_base(void);
void test_sys1(void);
void test_sys2(void);
void test_memory(void);
void test_print(void);

unit_local bool inline check_oga_result(Oga_Result result) {
    if (result != OGA_OK) {
        string err_name = oga_get_result_name(result);
        string err_msg = oga_get_result_message(result);
        print("oga call failed with error %s: '%s'\n", err_name, err_msg);
        sys_print_stack_trace(sys_get_stdout());
        return false;
    }
    return true;
}

int main(void) {
    sys_write_string(sys_get_stdout(), STR("Hello, ostd!\n"));

    test_base();
    test_sys1();
    test_memory();
    test_print();
    test_sys2();

    Oga_Device devices[128];
    u64 device_count = oga_query_devices(devices, 128);

    assert(device_count > 0 && device_count < 128);

    print("%u devices:\n", device_count);
    for (u32 i = 0; i < device_count; i += 1) {
        Oga_Device *device = devices + i;

        string depth_str = oga_format_str(device->depth_format);
        print(("Device %u:\n"), i);
        print(("\t%s - %s %s - %s\n"), STRN(device->device_name_length, device->device_name_data), device->vendor_name, STRN(device->driver_version_length, device->driver_version_data), STRN(device->api_version_length, device->api_version_data));
        print("\tKind: ");
        switch (device->kind) {
            case OGA_DEVICE_DISCRETE: print("Discrete GPU\n"); break;
            case OGA_DEVICE_INTEGRATED: print("Integrated GPU\n"); break;
            case OGA_DEVICE_CPU: print("CPU\n"); break;
            case OGA_DEVICE_OTHER: print("Other\n"); break;
        }
        print(("\tDepth: %s\n"), depth_str);

        print(("\t%u Logical Engine families:\n"), device->engine_family_count);
        for (u32 j = 0; j < device->engine_family_count; j += 1) {
            Oga_Logical_Engine_Family_Info family = device->engine_family_infos[j];

            print(("\t\t"));

            if (family.flags & OGA_LOGICAL_ENGINE_GRAPHICS) print(("GRAPHICS "));
            if (family.flags & OGA_LOGICAL_ENGINE_COMPUTE) print(("COMPUTE "));
            if (family.flags & OGA_LOGICAL_ENGINE_TRANSFER) print(("TRANSFER "));
            if (family.flags & OGA_LOGICAL_ENGINE_PRESENT) print(("PRESENT "));

            print(("| %u engines\n"), family.engine_capacity);

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
        print("\t%u supported surface formats:\n", device->supported_surface_format_count);
        for (u64 j = 0; j < device->supported_surface_format_count; j += 1) {
            Oga_Format f = device->supported_surface_formats[j];
            string fstr = oga_format_str(f);
            print("\t\t%s\n", fstr);
        }
        
        print("\tFeatures:\n\t\t");
        for (u64 f = 0; f < 64; f += 1) {
            if (device->features & (1ULL << f)) {
                string feature_str = oga_device_feature_str(1ULL << f);
                print("%s | ", feature_str);
            }
        }
        print("\n");
    }
    print("\n");
    
    //////
    // Test device picking helper
    /////
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
    Oga_Pick_Device_Result pick5 = oga_pick_device(
        0,
        OGA_DEVICE_FEATURE_PRESENT_MAILBOX,
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
    string s5 = (pick5.passed ? (STRN(pick5.device.device_name_length, pick5.device.device_name_data)) : STR("NONE"));
    print("REQUIRE FEATURE PRESENT_MAILBOX: %s\n", s5);

    print("\n");

    Oga_Device target_device = pick0.device;

    //////
    // Init context
    /////

    ///
    // Select queues
    // note(charlie) In a real-world scenario you would probably want to spread out queues across families.
    // You'd especially want to make sure, if possible, that compute is on another family, or at least 
    // a separate queue index from graphics.
    u64 family_index_graphics = U64_MAX;
    u64 family_index_present = U64_MAX;
    u64 family_index_compute = U64_MAX;

    for (u32 family_index = 0; family_index < target_device.engine_family_count; family_index += 1) {
        Oga_Logical_Engine_Family_Info family = target_device.engine_family_infos[family_index];

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
        print("Error: no graphics engines.\n");
        return 1;
    }
    if (family_index_present == U64_MAX) {
        print("Error: no present engines.\n");
        return 1;
    }
    if (family_index_compute == U64_MAX) {
        print("Error: no compute engines.\n");
        return 1;
    }
    
    
    ///
    // Context desc
    Oga_Context_Desc context_desc = (Oga_Context_Desc){0};
    context_desc.state_allocator = (Allocator){0}; // Use default state allocator, should be very good for many drivers

    Oga_Logical_Engines_Create_Desc *graphics_engine_desc = &context_desc.engine_create_descs[family_index_graphics];
    Oga_Logical_Engines_Create_Desc *present_engine_desc = &context_desc.engine_create_descs[family_index_present];
    Oga_Logical_Engines_Create_Desc *compute_engine_desc = &context_desc.engine_create_descs[family_index_compute];

    Oga_Logical_Engine_Family_Info graphics_family = target_device.engine_family_infos[family_index_graphics];
    Oga_Logical_Engine_Family_Info present_family = target_device.engine_family_infos[family_index_present];
    Oga_Logical_Engine_Family_Info compute_family = target_device.engine_family_infos[family_index_compute];

    // Try creating separate engines if engines belong to same family and capacity allows.

    graphics_engine_desc->count = min(graphics_engine_desc->count+1, graphics_family.engine_capacity);
    for (u32 i = 0; i < graphics_engine_desc->count; i += 1)
        graphics_engine_desc->priorities[i] = 1;
    u64 engine_index_graphics = graphics_engine_desc->count-1;

    present_engine_desc->count = min(present_engine_desc->count+1, present_family.engine_capacity);
    for (u32 i = 0; i < present_engine_desc->count; i += 1)
        present_engine_desc->priorities[i] = 1;
    u64 engine_index_present = present_engine_desc->count-1;

    compute_engine_desc->count = min(compute_engine_desc->count+1, compute_family.engine_capacity);
    for (u32 i = 0; i < compute_engine_desc->count; i += 1)
        compute_engine_desc->priorities[i] = 1;
    u64 engine_index_compute = compute_engine_desc->count-1;

    Oga_Context *context = 0;
    if (!check_oga_result(oga_init_context(target_device, context_desc, &context)))
        return 1;

    ///
    // Retrieve logical engines
    Oga_Logical_Engine graphics_engine = context->engines_by_family[family_index_graphics].engines[engine_index_graphics];
    Oga_Logical_Engine present_engine = context->engines_by_family[family_index_present].engines[engine_index_present];
    Oga_Logical_Engine compute_engine = context->engines_by_family[family_index_compute].engines[engine_index_compute];

    print("Graphics engine family %u, index %u\n", family_index_graphics, graphics_engine.index);
    print("Present engine family %u, index %u\n", family_index_present, present_engine.index);
    print("Compute engine family %u, index %u\n", family_index_compute, compute_engine.index);
    
    //////
    // Surface & swap chain
    /////
#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
    Surface_Desc surface_desc = DEFAULT(Surface_Desc);
    Surface_Handle surface = sys_make_surface(surface_desc);
    assertmsg(surface, ("Failed making surface"));
#else
    Surface_Handle surface = sys_get_surface();
#endif


    
    Oga_Format wanted_formats[] = {
        OGA_FORMAT_B8G8R8A8_SRGB,
        OGA_FORMAT_R8G8B8A8_SRGB,
        OGA_FORMAT_B8G8R8A8_UNORM,
        OGA_FORMAT_R8G8B8A8_UNORM
    };
    bool found_flags[sizeof(wanted_formats)/sizeof(Oga_Format)] = {0};
    
    for (u64 i = 0; i < sizeof(wanted_formats)/sizeof(Oga_Format); i += 1) {
        for (u64 j = 0; j < context->device.supported_surface_format_count; j += 1) {
            Oga_Format f = context->device.supported_surface_formats[j];
            if (f == wanted_formats[i]) {
                found_flags[i] = true;
                break;
            }
        }
    }
    
    Oga_Format surface_format = context->device.supported_surface_formats[0];
    for (u64 i = 0; i < sizeof(wanted_formats)/sizeof(Oga_Format); i += 1) {
        if (found_flags[i]) {
            surface_format = wanted_formats[i];
        }
    }
    
    
    
    u64 engine_families_with_access[] = { family_index_graphics, family_index_present };
    
    Oga_Present_Mode present_mode = OGA_PRESENT_MODE_VSYNC;
    if (context->device.features & OGA_DEVICE_FEATURE_PRESENT_MAILBOX) {
        // It just breaks on android for some reason todo(charlie) fix
#if !(OS_FLAGS & OS_FLAG_ANDROID)
        present_mode = OGA_PRESENT_MODE_VSYNC_MAILBOX;
#endif
    }
    Oga_Swapchain_Desc sc_desc = (Oga_Swapchain_Desc){0};
    sc_desc.surface = surface;
    sc_desc.requested_image_count = 3;
    sc_desc.image_format = surface_format;
    sc_desc.width = 800;
    sc_desc.height = 600;
    sc_desc.engine_families_with_access = engine_families_with_access;
    sc_desc.engine_families_with_access_count = sizeof(engine_families_with_access)/sizeof(u64);
    sc_desc.present_mode = present_mode;
    
    Oga_Swapchain *swapchain;
    if (!check_oga_result(oga_init_swapchain(context, sc_desc, &swapchain)))
        return 1;
    
    //////
    // GPU Programs
    /////
    
    Oga_Program *vert_program, *frag_program;
    
    Oga_Program_Desc vert_desc, frag_desc;
    
    vert_desc.code = triangle_vert_code;
    vert_desc.code_size = sizeof(triangle_vert_code);
    
    frag_desc.code = triangle_frag_code;
    frag_desc.code_size = sizeof(triangle_frag_code);
    
    if (!check_oga_result(oga_init_program(context, vert_desc, &vert_program)))
        return 1;
    if (!check_oga_result(oga_init_program(context, frag_desc, &frag_program)))
        return 1;
    
    //////
    // Render pass
    /////
    
    Oga_Render_Pass_Desc render_desc = (Oga_Render_Pass_Desc){0};
    render_desc.vertex_program = vert_program;
    render_desc.vertex_program_entry_point = STR("main");
    render_desc.fragment_program = frag_program;
    render_desc.fragment_program_entry_point = STR("main");
    render_desc.attachment_formats = &swapchain->image_format;
    render_desc.attachment_count = 1;
    render_desc.topology = OGA_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    render_desc.cull_mode = OGA_CULL_NONE;
    render_desc.line_width = 1.0;
    
    Oga_Render_Pass *render_pass;
    if (!check_oga_result(oga_init_render_pass(context, render_desc, &render_pass)))
        return 1;
    
    Oga_Command_Pool_Desc pool_desc = (Oga_Command_Pool_Desc){0};
    pool_desc.flags = 0;
    pool_desc.engine_family_index = family_index_graphics;
    
    Oga_Command_Pool *pools[3];
    if (!check_oga_result(oga_init_command_pool(context, pool_desc, &pools[0])))
        return 1;
    if (!check_oga_result(oga_init_command_pool(context, pool_desc, &pools[1])))
        return 1;
    if (!check_oga_result(oga_init_command_pool(context, pool_desc, &pools[2])))
        return 1;
    
    Oga_Command_List cmds[3];
    if (!check_oga_result(oga_get_command_lists(pools[0], &cmds[0], 1)))
        return 1;
    if (!check_oga_result(oga_get_command_lists(pools[1], &cmds[1], 1)))
        return 1;
    if (!check_oga_result(oga_get_command_lists(pools[2], &cmds[2], 1)))
        return 1;
        
    Oga_Gpu_Latch *image_ready_latches[3];
    if (!check_oga_result(oga_init_gpu_latch(context, &image_ready_latches[0])))
        return 1;
    if (!check_oga_result(oga_init_gpu_latch(context, &image_ready_latches[1])))
        return 1;
    if (!check_oga_result(oga_init_gpu_latch(context, &image_ready_latches[2])))
        return 1;
    Oga_Gpu_Latch *commands_done_latches[3];
    if (!check_oga_result(oga_init_gpu_latch(context, &commands_done_latches[0])))
        return 1;
    if (!check_oga_result(oga_init_gpu_latch(context, &commands_done_latches[1])))
        return 1;
    if (!check_oga_result(oga_init_gpu_latch(context, &commands_done_latches[2])))
        return 1;
    Oga_Cpu_Latch *present_latches[3];
    if (!check_oga_result(oga_init_cpu_latch(context, &present_latches[0], true)))
        return 1;
    if (!check_oga_result(oga_init_cpu_latch(context, &present_latches[1], true)))
        return 1;
    if (!check_oga_result(oga_init_cpu_latch(context, &present_latches[2], true)))
        return 1;
    
    bool running = true;
    
    u64 frame_count = 3;
    u64 frame_index = 0;
    
    bool image_virgin_flags[3] = {1,1,1};
    float64 last_time = 0.0;
    while (running) {
        reset_temporary_storage();
        float64 now = sys_get_seconds_monotonic();
        float64 delta = now-last_time;
        if ((u64)now > (u64)last_time) {
            float64 ms = delta*1000.0;
            float64 fps = 1.0/delta;
            print("%fms, %ffps\n", ms, fps);
        }
        last_time = now;
        
        
        surface_poll_events(surface);

        if (surface_should_close(surface)) {
            running = false;
            break;
        }
        
        oga_wait_latch(present_latches[frame_index]);
        oga_reset_latch(present_latches[frame_index]);
        oga_reset_command_pool(pools[frame_index]);
        
        u64 image_index;
        Oga_Result image_get_result = oga_get_next_swapchain_image(swapchain, U64_MAX, image_ready_latches[frame_index], 0, &image_index);
        if (image_get_result == OGA_SUBOPTIMAL) {
            
        } else if (image_get_result != OGA_OK) {
            if (!check_oga_result(image_get_result))
                return 1;
        }
        
        Oga_Command_List cmd = cmds[frame_index];
        
        oga_cmd_begin(cmd, 0);
        
        Oga_Image_Optimization src_opt = OGA_IMAGE_OPTIMIZATION_PRESENT;
        if (image_virgin_flags[image_index]) src_opt = OGA_IMAGE_OPTIMIZATION_UNDEFINED;
        image_virgin_flags[image_index] = false; 
        oga_cmd_transition_image_optimization(cmd, swapchain->images[image_index], src_opt, OGA_IMAGE_OPTIMIZATION_RENDER_ATTACHMENT);
        
        Oga_Render_Attachment_Desc attachment = (Oga_Render_Attachment_Desc){0};
        attachment.image = swapchain->images[image_index];
        attachment.load_op = OGA_ATTACHMENT_LOAD_OP_CLEAR;
        attachment.store_op = OGA_ATTACHMENT_STORE_OP_STORE;
        attachment.image_optimization = OGA_IMAGE_OPTIMIZATION_RENDER_ATTACHMENT;
        memcpy(attachment.clear_color, &(float32[4]){1.f, 0.f, 0.f, 1.f}, 16);
        
        Oga_Begin_Render_Pass_Desc begin_desc = (Oga_Begin_Render_Pass_Desc){0};
        begin_desc.render_pass = render_pass;
        begin_desc.render_area_width = 800;
        begin_desc.render_area_height = 600;
        begin_desc.attachment_count = 1;
        begin_desc.attachments = &attachment;
        
        oga_cmd_begin_render_pass(cmd, begin_desc);
        
        oga_cmd_draw(cmd, 3, 0, 1, 0);
        
        oga_cmd_end_render_pass(cmd);
        
        oga_cmd_transition_image_optimization(cmd, swapchain->images[image_index], OGA_IMAGE_OPTIMIZATION_RENDER_ATTACHMENT, OGA_IMAGE_OPTIMIZATION_PRESENT);
        
        oga_cmd_end(cmd);
        
        
        Oga_Submit_Command_List_Desc submit = (Oga_Submit_Command_List_Desc){0};
        submit.engine = graphics_engine;
        submit.signal_cpu_latch = present_latches[frame_index];
        submit.wait_gpu_latches = &image_ready_latches[frame_index];
        submit.wait_gpu_latch_count = 1;
        submit.signal_gpu_latches = &commands_done_latches[frame_index];
        submit.signal_gpu_latch_count = 1;
        oga_submit_command_list(cmd, submit);
        
        Oga_Present_Desc present_desc = (Oga_Present_Desc){0};
        present_desc.engine = present_engine;
        present_desc.wait_gpu_latch_count = 1;
        present_desc.wait_gpu_latches = &commands_done_latches[frame_index];
        present_desc.image_index = image_index;
        
        oga_submit_present(swapchain, present_desc);
        
        frame_index = (frame_index + 1) % frame_count;        
    }

    // System will free any resources when our program exits, this is to get sanity validation errors to make sure
    // we have everything under control.
#if DEBUG
    oga_uninit_command_pool(pools[0]);
    oga_uninit_command_pool(pools[1]);
    oga_uninit_command_pool(pools[2]);
    oga_uninit_cpu_latch(present_latches[0]);
    oga_uninit_cpu_latch(present_latches[1]);
    oga_uninit_cpu_latch(present_latches[2]);
    oga_uninit_gpu_latch(image_ready_latches[0]);
    oga_uninit_gpu_latch(image_ready_latches[1]);
    oga_uninit_gpu_latch(image_ready_latches[2]);
    oga_uninit_gpu_latch(commands_done_latches[0]);
    oga_uninit_gpu_latch(commands_done_latches[1]);
    oga_uninit_gpu_latch(commands_done_latches[2]);
    oga_uninit_render_pass(render_pass);
    oga_uninit_program(vert_program);
    oga_uninit_program(frag_program);
    oga_uninit_swapchain(swapchain);
    oga_uninit_context(context);
#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
    surface_close(surface);
#endif

    oga_reset(); // Only really necessary to get messages about leaked resources
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
        void *mem = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, 4, false);
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

        void *mem = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr, 4, true);
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

        void *mem0 = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr0, 4, true);
        void *mem1 = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr1, 4, true);
        void *mem2 = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr2, 4, true);

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
        assert(written == 0);

        s64 read = sys_read(hread, buf, 128);
        assert(read == 0);
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

