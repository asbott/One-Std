

#define OSTD_IMPL
#define OGA_IMPL_VULKAN

#include "../ostd_single_header.h"
#include "minimal_triangle.spv.h"

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

        if ((family.flags & OGA_LOGICAL_ENGINE_COMPUTE && family.flags & OGA_LOGICAL_ENGINE_PRESENT)) {
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
        OGA_FORMAT_B8G8R8A8_SRGB,
        OGA_FORMAT_R8G8B8A8_SRGB,
        OGA_FORMAT_B8G8R8A8_UNORM,
        OGA_FORMAT_R8G8B8A8_UNORM
    };
 
 	// Another helper. Again, if you want more granular control, see the implementation.   
    Oga_Format surface_format;
    bool surface_format_ok = get_preferred_swapchain_format(
    	context, 
    	wanted_formats, 
    	sizeof(wanted_formats)/sizeof(Oga_Format), 
    	&surface_format
	);
    
    Oga_Swapchain_Desc sc_desc = (Oga_Swapchain_Desc){0};
    sc_desc.surface = surface;
    sc_desc.requested_image_count = 3;
    sc_desc.image_format = surface_format;
    // todo(charlie) sys_get_surface_framebuffer_size
    sc_desc.width = 800;
    sc_desc.height = 600;
    sc_desc.engine_families_with_access = &engine_family_index;
    sc_desc.engine_families_with_access_count = 1;
    sc_desc.present_mode = OGA_PRESENT_MODE_VSYNC;
    
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
    if (!check_oga_result(oga_get_command_lists(pools[0], cmds, 3)))
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
    Oga_Cpu_Latch *present_latches[3];
    if (!check_oga_result(oga_init_cpu_latch(context, &present_latches[0], true)))
        return 1;
    if (!check_oga_result(oga_init_cpu_latch(context, &present_latches[1], true)))
        return 1;
    if (!check_oga_result(oga_init_cpu_latch(context, &present_latches[2], true)))
        return 1;
    
    bool running = true;
    
    u64 frame_index = 0;
    
    bool image_virgin_flags[3] = {1,1,1};
    
    while (running) {
        reset_temporary_storage();
        
        // Wait for frame to be ready, then reset it
        oga_wait_latch(present_latches[frame_index]);
        oga_reset_latch(present_latches[frame_index]);
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
        
        // The first time we use an image, it's in the undefined layout.
        // Otherwise it will be in the present layout
        Oga_Image_Optimization src_opt = OGA_IMAGE_OPTIMIZATION_PRESENT;
        if (image_virgin_flags[image_index]) src_opt = OGA_IMAGE_OPTIMIZATION_UNDEFINED;
        image_virgin_flags[image_index] = false; 
        oga_cmd_transition_image_optimization(cmd, swapchain->images[image_index], src_opt, OGA_IMAGE_OPTIMIZATION_RENDER_ATTACHMENT);
        
        ///
        // Start the render pass
        
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
        
        // The draw call
        oga_cmd_draw(cmd, 3, 0, 1, 0);
        
        oga_cmd_end_render_pass(cmd);
        
        // Transition to present layout after commands are done
        oga_cmd_transition_image_optimization(cmd, swapchain->images[image_index], OGA_IMAGE_OPTIMIZATION_RENDER_ATTACHMENT, OGA_IMAGE_OPTIMIZATION_PRESENT);
        
        oga_cmd_end(cmd);
        
        // Submit commands, waiting for the swapchain image to be ready, and signalling
        // the present latch to notify the present call when it can start presenting
        Oga_Submit_Command_List_Desc submit = (Oga_Submit_Command_List_Desc){0};
        submit.engine = engine;
        submit.signal_cpu_latch = present_latches[frame_index];
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
}