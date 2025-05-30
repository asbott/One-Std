#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#pragma clang diagnostic ignored "-Wpre-c23-compat"
#endif

#define OSTD_IMPL
#define OGA_IMPL_VULKAN

//#include "../ostd_single_header.h"
#include "../src/ostd.h"

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

	////
	// Pick an appropriate device.
	// For more granular control, see implementation of oga_pick_device().

	Oga_Pick_Device_Result pick0 = oga_pick_device(OGA_DEVICE_PICK_PREFER_DISCRETE, 0, 0);
	if (!pick0.passed) {
		print("Could not find an appropriate device.\n");
		return 1;
	}
	Oga_Device target_device = pick0.device;
	
	////
	// Find an approperiate engine for graphics and present
	
	u64 engine_family_index = U64_MAX;
    
    for (u32 family_index = 0; family_index < target_device.engine_family_count; family_index += 1) {
        Oga_Logical_Engine_Family_Info family = target_device.engine_family_infos[family_index];

        if ((family.flags & OGA_LOGICAL_ENGINE_GRAPHICS && family.flags & OGA_LOGICAL_ENGINE_PRESENT)) {
            engine_family_index = family_index;
            break;
        }
    }
    
    if (engine_family_index == U64_MAX) {
    	print("Could not find an appropriate engine on device for graphics & presenting.\n");
    	return 1;
    }
    
    Oga_Logical_Engine_Family_Info engine_family 
    	= target_device.engine_family_infos[engine_family_index];
    (void)engine_family;
    
    Oga_Logical_Engines_Create_Desc engine_desc = (Oga_Logical_Engines_Create_Desc){0};
    engine_desc.count = 1;
    engine_desc.priorities[0] = 1.0f;
    
    ////
    // Context creation
    Oga_Context_Desc context_desc = (Oga_Context_Desc){0};
    context_desc.state_allocator = (Allocator){0}; // Use default state allocator, should be very good for many drivers
    context_desc.engine_create_descs[engine_family_index] = engine_desc;

    Oga_Context *context = 0;
    if (!check_oga_result(oga_init_context(target_device, context_desc, &context)))
        return 1;
    
    // We created 1 engine, which will be @ index 0
    Oga_Logical_Engine engine 
    	= context->engines_by_family[engine_family_index].engines[0]; 
    	
    //////
    // Surface & swap chain
    /////
    
    // To target mobile devices etc, we have a slightly different system surface API
#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
    Surface_Desc surface_desc = DEFAULT(Surface_Desc);
    Surface_Handle surface = sys_make_surface(surface_desc);
    assertmsg(surface, ("Failed making surface"));
#else
    Surface_Handle surface = sys_get_surface();
#endif

	// We need to pick a surface format

	// Any platform should support one of these formats, unless it's a very peculiar platform
	Oga_Format wanted_formats[] = {
        OGA_FORMAT_B8G8R8A8_UNORM,
        OGA_FORMAT_R8G8B8A8_UNORM,
        OGA_FORMAT_B8G8R8A8_SRGB,
        OGA_FORMAT_R8G8B8A8_SRGB
    };
 
 	// Another helper. Again, if you want more granular control, see the implementation.   
    Oga_Format surface_format;
    bool surface_format_ok = get_preferred_swapchain_format(
    	context, 
    	wanted_formats, 
    	sizeof(wanted_formats)/sizeof(Oga_Format), 
    	&surface_format
	);
	assert(surface_format_ok);
    
    Oga_Swapchain_Desc sc_desc = (Oga_Swapchain_Desc){0};
    sc_desc.surface = surface;
    sc_desc.requested_image_count = 3;
    sc_desc.image_format = surface_format;
    surface_get_framebuffer_size(surface, (s64*)&sc_desc.width, (s64*)&sc_desc.height);
    sc_desc.graphics_engine_family_index = engine_family_index;
    sc_desc.present_mode = OGA_PRESENT_MODE_VSYNC;
    
    Oga_Swapchain *swapchain;
    if (!check_oga_result(oga_init_swapchain(context, sc_desc, &swapchain)))
        return 1;
        
    //////
    // GPU Programs
    /////
    
    string vert_src, frag_src;
    void *frag_code, *vert_code;
    u64 frag_code_size, vert_code_size;
    
    bool vert_src_ok = sys_read_entire_file(get_temp(), STR("tests/shaders/triangle.vert.osl"), &vert_src);
    assert(vert_src_ok);
    
    bool frag_src_ok = sys_read_entire_file(get_temp(), STR("tests/shaders/triangle.frag.osl"), &frag_src);
    assert(frag_src_ok);
    
    Osl_Compile_Desc vert_desc = (Osl_Compile_Desc){0};
    vert_desc.code_text = vert_src;
    vert_desc.target = OGA_OSL_TARGET;
    vert_desc.program_kind = OSL_PROGRAM_GPU_VERTEX;
    
    Osl_Compile_Desc frag_desc = (Osl_Compile_Desc){0};
    frag_desc.code_text = frag_src;
    frag_desc.target = OGA_OSL_TARGET;
    frag_desc.program_kind = OSL_PROGRAM_GPU_FRAGMENT;
    
    string compile_err;
    Osl_Result compile_result;
    
    compile_result = osl_compile(get_temp(), vert_desc, &vert_code, &vert_code_size, &compile_err);
    assertmsgs(compile_result == OSL_OK, compile_err);
    
    compile_result = osl_compile(get_temp(), frag_desc, &frag_code, &frag_code_size, &compile_err);
    assertmsgs(compile_result == OSL_OK, compile_err);
    
    Oga_Program *vert_program, *frag_program;
    
    Oga_Program_Desc vert_program_desc, frag_program_desc;
    
    vert_program_desc.code = vert_code;
    vert_program_desc.code_size = vert_code_size;
    
    frag_program_desc.code = frag_code;
    frag_program_desc.code_size = frag_code_size;
    
    if (!check_oga_result(oga_init_program(context, vert_program_desc, &vert_program)))
        return 1;
    if (!check_oga_result(oga_init_program(context, frag_program_desc, &frag_program)))
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
    
    //////
    // Command lists & synchronization latches per frame-in-flight (3)
    /////
    
    Oga_Command_Pool_Desc pool_desc = (Oga_Command_Pool_Desc){0};
    pool_desc.flags = 0;
    pool_desc.engine_family_index = engine_family_index;
    
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
        
    // todo(charlie) batch create latches
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
    Oga_Cpu_Latch *cmd_latches[3];
    if (!check_oga_result(oga_init_cpu_latch(context, &cmd_latches[0], true)))
        return 1;
    if (!check_oga_result(oga_init_cpu_latch(context, &cmd_latches[1], true)))
        return 1;
    if (!check_oga_result(oga_init_cpu_latch(context, &cmd_latches[2], true)))
        return 1;
    
    bool running = true;
    
    u64 frame_index = 0;
    
    f64 start_time = sys_get_seconds_monotonic();
    (void)start_time;
    
    while (running) {
        reset_temporary_storage();
        
#ifdef RUNNING_TESTS
        if (sys_get_seconds_monotonic()-start_time > TESTING_DURATION) {
            running = false;
        }
#endif // RUNNING_TESTS
        
        // Wait for frame to be ready, then reset it
        oga_wait_latch(cmd_latches[frame_index]);
        oga_reset_latch(cmd_latches[frame_index]);
        oga_reset_command_pool(pools[frame_index]);
        
        // Retrieve the next swap chain image index
        u64 image_index;
        Oga_Result image_get_result = oga_get_next_swapchain_image(swapchain, U64_MAX, image_ready_latches[frame_index], 0, &image_index);
        if (image_get_result == OGA_SUBOPTIMAL) {
            // Here we should probably resize
        } else if (image_get_result != OGA_OK) {
            if (!check_oga_result(image_get_result))
                return 1;
        }
        // We should also check for other errors from the swapchain and handle accordingly
        
        Oga_Command_List cmd = cmds[frame_index];
        
        // Begin submitting commands to the command list
        oga_cmd_begin(cmd, 0);
        
        ///
        // Start the render pass
        
        Oga_Render_Attachment_Desc attachment = (Oga_Render_Attachment_Desc){0};
        attachment.image = swapchain->images[image_index];
        attachment.load_op = OGA_ATTACHMENT_LOAD_OP_CLEAR;
        attachment.store_op = OGA_ATTACHMENT_STORE_OP_STORE;
        memcpy(attachment.clear_color, &(float32[4]){0.39f, 0.58f, 0.93f, 1.0f}, 16);
        
        Oga_Begin_Render_Pass_Desc begin_desc = (Oga_Begin_Render_Pass_Desc){0};
        begin_desc.render_area_width = 800;
        begin_desc.render_area_height = 600;
        begin_desc.attachment_count = 1;
        begin_desc.attachments = &attachment;
        
        oga_cmd_begin_render_pass(cmd, render_pass, begin_desc);
        
        // The draw call
        Oga_Draw_Desc draw_desc = (Oga_Draw_Desc){0};
        draw_desc.draw_type = OGA_DRAW_INSTANCED;
        draw_desc.instance_count = 1;
        draw_desc.vertex_count = 3;
        oga_cmd_draw(cmd, draw_desc);
        
        oga_cmd_end_render_pass(cmd, render_pass);
        
        oga_cmd_end(cmd);
        
        // Submit commands, waiting for the swapchain image to be ready, and signalling
        // the present latch to notify the present call when it can start presenting
        Oga_Submit_Command_List_Desc submit = (Oga_Submit_Command_List_Desc){0};
        submit.engine = engine;
        submit.signal_cpu_latch = cmd_latches[frame_index];
        submit.wait_gpu_latches = &image_ready_latches[frame_index];
        submit.wait_gpu_latch_count = 1;
        submit.signal_gpu_latches = &commands_done_latches[frame_index];
        submit.signal_gpu_latch_count = 1;
        oga_submit_command_list(cmd, submit);
        
        // Submit present to the present engine, waiting for the commands to finish
        // before starting the present.
        Oga_Present_Desc present_desc = (Oga_Present_Desc){0};
        present_desc.engine = engine;
        present_desc.wait_gpu_latch_count = 1;
        present_desc.wait_gpu_latches = &commands_done_latches[frame_index];
        present_desc.image_index = image_index;
        oga_submit_present(swapchain, present_desc);
        
        // Next frame index, 0, 1, 2, 0, 1, ...
        frame_index = (frame_index + 1) % 3;
        
        surface_poll_events(surface);
        if (surface_should_close(surface)) {
            running = false;
            break;
        }   
    }
    
    // System will free any resources when our program exits, this is to get sanity validation errors to make sure
    // we have everything under control.
#ifdef DEBUG
    oga_uninit_command_pool(pools[0]);
    oga_uninit_command_pool(pools[1]);
    oga_uninit_command_pool(pools[2]);
    oga_uninit_cpu_latch(cmd_latches[0]);
    oga_uninit_cpu_latch(cmd_latches[1]);
    oga_uninit_cpu_latch(cmd_latches[2]);
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
