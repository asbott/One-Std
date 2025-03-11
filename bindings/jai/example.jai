
check_oga_result :: (result: ostd.Oga_Result) {
	assert(result == .OK, "Oga err %", result);
}

main :: () {

	////
	// Pick an appropriate device.
	// For more granular control, see implementation of oga_pick_device().

	pick := ostd.oga_pick_device(.PREFER_DISCRETE, 0, 0);
	assert(pick.passed, "Could not find an appropriate device.");
	
	target_device := pick.device;
	
	////
	// Find an approperiate engine for graphics and present
	
	engine_family_index := ostd.U64_MAX;
    
    for family_index: 0..target_device.engine_family_count-1 {
        family := target_device.engine_family_infos[family_index];

        if ((family.flags & .GRAPHICS && family.flags & .PRESENT)) {
            engine_family_index = family_index;
            break;
        }
    }
    
    assert(engine_family_index != ostd.U64_MAX, "Could not find an appropriate engine on device for graphics * presenting.");
    
    engine_family := target_device.engine_family_infos[engine_family_index];
    
    engine_desc: ostd.Oga_Logical_Engines_Create_Desc;
    engine_desc.count = 1;
    engine_desc.priorities[0] = 1.0;
    
    ////
    // Context creation
    context_desc: ostd.Oga_Context_Desc;
    context_desc.engine_create_descs[engine_family_index] = engine_desc;

    oga: *ostd.Oga_Context;
    check_oga_result(ostd.oga_init_context(target_device, context_desc, *oga));
    
    // We created 1 engine, which will be @ index 0
    engine: ostd.Oga_Logical_Engine = oga.engines_by_family[engine_family_index].engines[0]; 
    	
    //////
    // Surface * swap chain
    /////
    
    // To target mobile devices etc, we have a slightly different system surface API
    surface_desc: ostd.Surface_Desc;
    surface_desc.width = 800;
    surface_desc.height = 600;
    surface_desc.title = "Jai OSTD Window";
    surface := ostd.sys_make_surface(surface_desc);
    assert(surface != null, ("Failed making surface"));

	// We need to pick a surface format

	// Any platform should support one of these formats, unless it's a very peculiar platform
	wanted_formats := ostd.Oga_Format.[
        .B8G8R8A8_UNORM,
        .R8G8B8A8_UNORM,
        .B8G8R8A8_SRGB,
        .R8G8B8A8_SRGB
    ];
 
    surface_format: ostd.Oga_Format;
    surface_format_ok := ostd.get_preferred_swapchain_format(
    	oga, 
    	wanted_formats.data, 
    	wanted_formats.count, 
    	*surface_format
	);
	assert(surface_format_ok);
    
    sc_desc: ostd.Oga_Swapchain_Desc;
    sc_desc.surface = surface;
    sc_desc.requested_image_count = 3;
    sc_desc.image_format = surface_format;
    ostd.surface_get_framebuffer_size(surface, cast(*s64)*sc_desc.width, cast(*s64)*sc_desc.height);
    sc_desc.graphics_engine_family_index = xx engine_family_index;
    sc_desc.present_mode = .VSYNC;
    
    swapchain: *ostd.Oga_Swapchain;
    check_oga_result(ostd.oga_init_swapchain(oga, sc_desc, *swapchain));
        
    //////
    // GPU Programs
    /////
    
    vert_src, frag_src: string;
    frag_code, vert_code: *void;
    frag_code_size, vert_code_size: u64;
    
    vert_src_ok := ostd.sys_read_entire_file(ostd.get_temp(), "../../tests/shaders/triangle.vert.osl", *vert_src);
    assert(vert_src_ok);
    
    frag_src_ok := ostd.sys_read_entire_file(ostd.get_temp(), "../../tests/shaders/triangle.frag.osl", *frag_src);
    assert(frag_src_ok);
    
    vert_desc: ostd.Osl_Compile_Desc;
    vert_desc.code_text = vert_src;
    vert_desc.target = .OSL_TARGET_SPIRV_VULKAN;
    vert_desc.program_kind = .VERTEX;
    
    frag_desc: ostd.Osl_Compile_Desc;
    frag_desc.code_text = frag_src;
    frag_desc.target = .OSL_TARGET_SPIRV_VULKAN;
    frag_desc.program_kind = .FRAGMENT;
    
    compile_err: string;
    compile_result: ostd.Osl_Result;
    
    compile_result = ostd.osl_compile(ostd.get_temp(), vert_desc, *vert_code, *vert_code_size, *compile_err);
    assert(compile_result == .OK, compile_err);
    
    compile_result = ostd.osl_compile(ostd.get_temp(), frag_desc, *frag_code, *frag_code_size, *compile_err);
    assert(compile_result == .OK, compile_err);
    
    vert_program, frag_program: *ostd.Oga_Program;
    
    vert_program_desc, frag_program_desc: ostd.Oga_Program_Desc;
    
    vert_program_desc.code = vert_code;
    vert_program_desc.code_size = vert_code_size;
    
    frag_program_desc.code = frag_code;
    frag_program_desc.code_size = frag_code_size;
    
    check_oga_result(ostd.oga_init_program(oga, vert_program_desc, *vert_program));
    check_oga_result(ostd.oga_init_program(oga, frag_program_desc, *frag_program));
    
    //////
    // Render pass
    /////
    
    render_desc: ostd.Oga_Render_Pass_Desc;
    render_desc.vertex_program = vert_program;
    render_desc.vertex_program_entry_point = "main";
    render_desc.fragment_program = frag_program;
    render_desc.fragment_program_entry_point = "main";
    render_desc.attachment_formats = *swapchain.image_format;
    render_desc.attachment_count = 1;
    render_desc.topology = .TRIANGLE_LIST;
    render_desc.cull_mode = .NONE;
    render_desc.line_width = 1.0;
    
    render_pass: *ostd.Oga_Render_Pass;
    check_oga_result(ostd.oga_init_render_pass(oga, render_desc, *render_pass));
    
    //////
    // Command lists & synchronization latches per frame-in-flight (3)
    /////
    
    pool_desc: ostd.Oga_Command_Pool_Desc;
    pool_desc.flags = 0;
    pool_desc.engine_family_index = xx engine_family_index;
    
    pools: [3]*ostd.Oga_Command_Pool;
    check_oga_result(ostd.oga_init_command_pool(oga, pool_desc, *pools[0]));
    check_oga_result(ostd.oga_init_command_pool(oga, pool_desc, *pools[1]));
    check_oga_result(ostd.oga_init_command_pool(oga, pool_desc, *pools[2]));
    
    cmds: [3]ostd.Oga_Command_List;
    check_oga_result(ostd.oga_get_command_lists(pools[0], *cmds[0], 1));
    check_oga_result(ostd.oga_get_command_lists(pools[1], *cmds[1], 1));
    check_oga_result(ostd.oga_get_command_lists(pools[2], *cmds[2], 1));
        
    // todo(charlie) batch create latches
    image_ready_latches: [3]*ostd.Oga_Gpu_Latch;
    check_oga_result(ostd.oga_init_gpu_latch(oga, *image_ready_latches[0]));
    check_oga_result(ostd.oga_init_gpu_latch(oga, *image_ready_latches[1]));
    check_oga_result(ostd.oga_init_gpu_latch(oga, *image_ready_latches[2]));
    commands_done_latches: [3]*ostd.Oga_Gpu_Latch;
    check_oga_result(ostd.oga_init_gpu_latch(oga, *commands_done_latches[0]));
    check_oga_result(ostd.oga_init_gpu_latch(oga, *commands_done_latches[1]));
    check_oga_result(ostd.oga_init_gpu_latch(oga, *commands_done_latches[2]));
    cmd_latches: [3]*ostd.Oga_Cpu_Latch;
    check_oga_result(ostd.oga_init_cpu_latch(oga, *cmd_latches[0], true));
    check_oga_result(ostd.oga_init_cpu_latch(oga, *cmd_latches[1], true));
    check_oga_result(ostd.oga_init_cpu_latch(oga, *cmd_latches[2], true));
    
    running := true;
    
    frame_index := 0;
    
    start_time := ostd.sys_get_seconds_monotonic();
    
    while (running) {
        ostd.reset_temporary_storage();
        
        // Wait for frame to be ready, then reset it
        ostd.oga_wait_latch(cmd_latches[frame_index]);
        ostd.oga_reset_latch(cmd_latches[frame_index]);
        ostd.oga_reset_command_pool(pools[frame_index]);
        
        // Retrieve the next swap chain image index
        image_index: u64;
        image_get_result := ostd.oga_get_next_swapchain_image(swapchain, ostd.U64_MAX, image_ready_latches[frame_index], null, *image_index);
        if (image_get_result == .SUBOPTIMAL) {
            // Here we should probably resize
        } else if (image_get_result != .OK) {
            check_oga_result(image_get_result);
        }
        // We should also check for other errors from the swapchain and handle accordingly
        
        cmd := cmds[frame_index];
        
        // Begin submitting commands to the command list
        ostd.oga_cmd_begin(cmd, 0);
        
        ///
        // Start the render pass
        
        attachment: ostd.Oga_Render_Attachment_Desc;
        attachment.image = swapchain.images[image_index];
        attachment.load_op = .CLEAR;
        attachment.store_op = .STORE;
        attachment.clear_color = .[0.39, 0.58, 0.93, 1.0];
        
        begin_desc: ostd.Oga_Begin_Render_Pass_Desc;
        begin_desc.render_area_width = 800;
        begin_desc.render_area_height = 600;
        begin_desc.attachment_count = 1;
        begin_desc.attachments = *attachment;
        
        ostd.oga_cmd_begin_render_pass(cmd, render_pass, begin_desc);
        
        // The draw call
        draw_desc: ostd.Oga_Draw_Desc;
        draw_desc.draw_type = .INSTANCED;
        draw_desc.instance_count = 1;
        draw_desc.vertex_count = 3;
        ostd.oga_cmd_draw(cmd, draw_desc);
        
        ostd.oga_cmd_end_render_pass(cmd, render_pass);
        
        ostd.oga_cmd_end(cmd);
        
        // Submit commands, waiting for the swapchain image to be ready, and signalling
        // the present latch to notify the present call when it can start presenting
        submit: ostd.Oga_Submit_Command_List_Desc;
        submit.engine = engine;
        submit.signal_cpu_latch = cmd_latches[frame_index];
        submit.wait_gpu_latches = *image_ready_latches[frame_index];
        submit.wait_gpu_latch_count = 1;
        submit.signal_gpu_latches = *commands_done_latches[frame_index];
        submit.signal_gpu_latch_count = 1;
        ostd.oga_submit_command_list(cmd, submit);
        
        // Submit present to the present engine, waiting for the commands to finish
        // before starting the present.
        present_desc: ostd.Oga_Present_Desc;
        present_desc.engine = engine;
        present_desc.wait_gpu_latch_count = 1;
        present_desc.wait_gpu_latches = *commands_done_latches[frame_index];
        present_desc.image_index = image_index;
        ostd. oga_submit_present(swapchain, present_desc);
        
        // Next frame index, 0, 1, 2, 0, 1, ...
        frame_index = (frame_index + 1) % 3;
        
        ostd.surface_poll_events(surface);
        if (ostd.surface_should_close(surface)) {
            running = false;
            break;
        }   
    }
    
    ostd.oga_uninit_command_pool(pools[0]);
    ostd.oga_uninit_command_pool(pools[1]);
    ostd.oga_uninit_command_pool(pools[2]);
    ostd.oga_uninit_cpu_latch(cmd_latches[0]);
    ostd.oga_uninit_cpu_latch(cmd_latches[1]);
    ostd.oga_uninit_cpu_latch(cmd_latches[2]);
    ostd.oga_uninit_gpu_latch(image_ready_latches[0]);
    ostd.oga_uninit_gpu_latch(image_ready_latches[1]);
    ostd.oga_uninit_gpu_latch(image_ready_latches[2]);
    ostd.oga_uninit_gpu_latch(commands_done_latches[0]);
    ostd.oga_uninit_gpu_latch(commands_done_latches[1]);
    ostd.oga_uninit_gpu_latch(commands_done_latches[2]);
    ostd.oga_uninit_render_pass(render_pass);
    ostd.oga_uninit_program(vert_program);
    ostd.oga_uninit_program(frag_program);
    ostd.oga_uninit_swapchain(swapchain);
    ostd.oga_uninit_context(oga);
    ostd.surface_close(surface);

    ostd.oga_reset(); // Only really necessary to get messages about leaked resources
}


ostd :: #import,file "ostd_windows.jai";
#import "Basic";