#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif

#define OSTD_IMPL
#define OGA_IMPL_VULKAN

//#include "../ostd_single_header.h"
#include "../src/ostd.h"

#include "third_party/stb_image_modified.h"

unit_local void my_logger(string message, u64 flags, Source_Location location) {
    print("%s:%i | ", location.file, location.line);
    if (flags & OGA_LOG_VERBOSE) {
        print("[OGA VERBOSE]: %s", message);
    } else {
        prints(message);
    }
    
    if (message.count > 0 && message.data[message.count-1] != '\n') {
        print("\n");
    }
}

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

typedef struct Data {
    float4 tints[3];
    float4 offsets[3];
} Data;

int main(void) {

    stb_arena = make_arena(1024*1024*1024*69, 1024*1024*20);
    
    // Set the global logger, which all log() calls will go through
    logger = my_logger;

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
	// Find an appropriate engine for graphics and present
	
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
    sc_desc.present_mode = OGA_PRESENT_MODE_VSYNC;
    sc_desc.graphics_engine_family_index = engine_family_index;
    
    Oga_Swapchain *swapchain;
    if (!check_oga_result(oga_init_swapchain(context, sc_desc, &swapchain)))
        return 1;
        
    //////
    // GPU Programs
    /////
    
    string vert_src, frag_src;
    void *frag_code, *vert_code;
    u64 frag_code_size, vert_code_size;
    
    bool vert_src_ok = sys_read_entire_file(get_temp(), STR("tests/shaders/simple_blending.vert.osl"), &vert_src);
    assert(vert_src_ok);
    
    bool frag_src_ok = sys_read_entire_file(get_temp(), STR("tests/shaders/simple_blending.frag.osl"), &frag_src);
    assert(frag_src_ok);
    
    Osl_Compile_Desc vert_desc = (Osl_Compile_Desc){0};
    vert_desc.code_text = vert_src;
    vert_desc.target = OGA_OSL_TARGET;
    vert_desc.program_kind = OSL_PROGRAM_GPU_VERTEX;
    
    Osl_Compile_Desc frag_desc = (Osl_Compile_Desc){0};
    frag_desc.code_text = frag_src;
    frag_desc.target = OGA_OSL_TARGET;
    frag_desc.program_kind = OSL_PROGRAM_GPU_FRAGMENT;
    frag_desc.enabled_features = OSL_FEATURE_INVOCATION_PIXEL_INTERLOCK;
    
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
        
    sys_write_entire_file(STR("test.vert.spv"), (string){vert_code_size, (u8*)vert_code});
    sys_write_entire_file(STR("test.frag.spv"), (string){frag_code_size, (u8*)frag_code});
    
    //////
    // Vertex & Index List & Data Block
    /////
    
    struct { float4 pos; float3 col; float2 uv; } verts[] = {
    	{ f4(-0.5f, -0.5f, 0.0f, 1.0f), f3(1.0f, 1.0f, 1.0f), f2(0.0f, 0.0f) },
    	{ f4( 0.5f, -0.5f, 0.0f, 1.0f), f3(1.0f, 1.0f, 1.0f), f2(1.0f, 0.0f) },
    	{ f4( 0.5f,  0.5f, 0.0f, 1.0f), f3(1.0f, 1.0f, 1.0f), f2(1.0f, 1.0f) },
    	{ f4(-0.5f,  0.5f, 0.0f, 1.0f), f3(1.0f, 1.0f, 1.0f), f2(0.0f, 1.0f) }
    };
    
    u32 indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    
    Oga_Image_View_Desc blend_buffer_desc = (Oga_Image_View_Desc){0};
    blend_buffer_desc.format = OGA_FORMAT_R8G8B8A8_UNORM;
    blend_buffer_desc.dimensions = OGA_2D;
    blend_buffer_desc.width = (u64)sc_desc.width;
    blend_buffer_desc.height = (u64)sc_desc.height;
    blend_buffer_desc.graphics_engine_family_index = engine_family_index;
    
    Oga_Memory_Pointer static_mem = (Oga_Memory_Pointer){0};
    
    Oga_Memory_Pointer reflected_mem = (Oga_Memory_Pointer){0};
    
    // Memory views needs to start at memory_granularity to guarantee all alignment requirements are met
    // and no aliasing occurs.
    u64 granularity = context->device.limits.memory_granularity;
    u64 fbuffer_granularity = context->device.limits.fbuffer_memory_granularity;
    
    u64 vertex_alloc_size = sizeof(verts);
    u64 vertex_offset = 0;
     
    u64 index_alloc_size  = sizeof(indices);
    u64 index_offset = align_next(vertex_alloc_size, granularity);
    
    u64 blend_buffer_alloc_size  = oga_get_image_memory_requirement(context, blend_buffer_desc);
    u64 blend_buffer_offset = align_next(index_offset+index_alloc_size, fbuffer_granularity);
    
    u64 alloc_size = blend_buffer_offset + blend_buffer_alloc_size;
    
    // Allocate the memory
    
    Oga_Memory_Property_Flag mem_props = OGA_MEMORY_PROPERTY_GPU_LOCAL | OGA_MEMORY_PROPERTY_GPU_TO_CPU_MAPPABLE;
    Oga_Memory_Usage mem_usage = 
        OGA_MEMORY_USAGE_VERTEX_LIST 
      | OGA_MEMORY_USAGE_INDEX_LIST 
      | OGA_MEMORY_USAGE_IMAGE_2D; 
    if (!check_oga_result(oga_allocate_memory(context, alloc_size, mem_props, mem_usage, &static_mem)))
        return 1;
        
    
    u64 block_alloc_size  = sizeof(Data);
    u64 block_offset = 0;
    mem_props = OGA_MEMORY_PROPERTY_GPU_LOCAL | OGA_MEMORY_PROPERTY_GPU_TO_CPU_MAPPABLE | OGA_MEMORY_PROPERTY_GPU_TO_CPU_REFLECTED;
    mem_usage = OGA_MEMORY_USAGE_FAST_READONLY_DATA_BLOCK;
    if (!check_oga_result(oga_allocate_memory(context, block_alloc_size, mem_props, mem_usage, &reflected_mem)))
        return 1;
        
    // Offset pointers
    
    Oga_Memory_Pointer vertex_ptr, index_ptr, block_ptr, blend_buffer_ptr;
    
    oga_memory_offset(static_mem, (s64)vertex_offset, &vertex_ptr);
    oga_memory_offset(static_mem, (s64)index_offset, &index_ptr);
    oga_memory_offset(static_mem, (s64)blend_buffer_offset, &blend_buffer_ptr);
    
    oga_memory_offset(reflected_mem, (s64)block_offset, &block_ptr);
    
    void *mapped_memory = 0;
    if (!check_oga_result(oga_map_memory(static_mem, alloc_size, &mapped_memory)))
        return 1;
    memcpy((u8*)mapped_memory+0, verts, sizeof(verts));
    memcpy((u8*)mapped_memory+index_offset, indices, sizeof(indices));
    oga_unmap_memory(static_mem);
    
    // Map the gpu data block to our Data*, which we can write directly to and it will
    // get written to the GPU memory.
    Data *gpu_data;
    if (!check_oga_result(oga_map_memory(reflected_mem, sizeof(Data), (void**)&gpu_data)))
        return 1;
    
    // Create the memory views
    
    Oga_Vertex_List_View *vlist = 0;
    Oga_Index_List_View *ilist = 0;
    Oga_Block_View *block = 0;
    Oga_FBuffer_View *blend_buffer;
    
    Oga_Memory_View_Desc vlist_desc = (Oga_Memory_View_Desc){0};
    vlist_desc.memory_pointer = vertex_ptr;
    vlist_desc.size = sizeof(verts);
    if (!check_oga_result(oga_init_vertex_list_view(context, vlist_desc, &vlist)))
        return 1;
    
    Oga_Memory_View_Desc ilist_desc = (Oga_Memory_View_Desc){0};
    ilist_desc.memory_pointer = index_ptr;
    ilist_desc.size = sizeof(indices);
    if (!check_oga_result(oga_init_index_list_view(context, ilist_desc, &ilist)))
        return 1;
    
    Oga_Memory_View_Desc block_desc = (Oga_Memory_View_Desc){0};
    block_desc.memory_pointer = block_ptr;
    block_desc.size = sizeof(Data);
    if (!check_oga_result(oga_init_block_view(context, block_desc, &block)))
        return 1;
        
    blend_buffer_desc.memory_pointer = blend_buffer_ptr;
    if (!check_oga_result(oga_init_fbuffer_view(context, blend_buffer_desc, &blend_buffer)))
        return 1;
        
    Oga_Optimal_Copy_View *blend_buffer_copy_dst = 0;
    Oga_Optimal_Copy_View_Desc blend_buffer_copy_dst_desc = (Oga_Optimal_Copy_View_Desc){0};
    blend_buffer_copy_dst_desc.memory_pointer = blend_buffer_desc.memory_pointer;
    blend_buffer_copy_dst_desc.format = blend_buffer_desc.format;
    blend_buffer_copy_dst_desc.dimensions = blend_buffer_desc.dimensions;
    blend_buffer_copy_dst_desc.width = blend_buffer_desc.width;
    blend_buffer_copy_dst_desc.height = blend_buffer_desc.height;
    blend_buffer_copy_dst_desc.depth = blend_buffer_desc.depth;
    blend_buffer_copy_dst_desc.linear_tiling = blend_buffer_desc.linear_tiling;
    blend_buffer_copy_dst_desc.graphics_engine_family_index = blend_buffer_desc.graphics_engine_family_index;
    blend_buffer_copy_dst_desc.flags = OGA_OPTIMAL_COPY_DST;
    if (!check_oga_result(oga_init_optimal_copy_view(context, blend_buffer_copy_dst_desc, &blend_buffer_copy_dst)))
        return 1;
        
    //////
    // Render pass
    /////
    
    // Vertex layout
    Oga_Vertex_List_Layout_Desc vertex_layout_desc = (Oga_Vertex_List_Layout_Desc) {0};
    vertex_layout_desc.bindings[0].stride = sizeof(float4)+sizeof(float3)+sizeof(float2);
    vertex_layout_desc.bindings[0].input_rate = OGA_VERTEX_INPUT_RATE_VERTEX;
    vertex_layout_desc.binding_count = 1;
    
    vertex_layout_desc.attributes[vertex_layout_desc.attribute_count].binding = 0;
    vertex_layout_desc.attributes[vertex_layout_desc.attribute_count].location = 0;
    vertex_layout_desc.attributes[vertex_layout_desc.attribute_count].offset = 0;
    vertex_layout_desc.attributes[vertex_layout_desc.attribute_count].type = OGA_VERTEX_ATTRIBUTE_TYPE_F32V4;
    vertex_layout_desc.attribute_count += 1;
    
    vertex_layout_desc.attributes[vertex_layout_desc.attribute_count].binding = 0;
    vertex_layout_desc.attributes[vertex_layout_desc.attribute_count].location = 1;
    vertex_layout_desc.attributes[vertex_layout_desc.attribute_count].offset = sizeof(float4);
    vertex_layout_desc.attributes[vertex_layout_desc.attribute_count].type = OGA_VERTEX_ATTRIBUTE_TYPE_F32V3;
    vertex_layout_desc.attribute_count += 1;
    
    vertex_layout_desc.attributes[vertex_layout_desc.attribute_count].binding = 0;
    vertex_layout_desc.attributes[vertex_layout_desc.attribute_count].location = 2;
    vertex_layout_desc.attributes[vertex_layout_desc.attribute_count].offset = sizeof(float4)+sizeof(float3);
    vertex_layout_desc.attributes[vertex_layout_desc.attribute_count].type = OGA_VERTEX_ATTRIBUTE_TYPE_F32V2;
    vertex_layout_desc.attribute_count += 1;
    
    Oga_Binding_Layout_Entry_Desc layout_bindings[3];
    layout_bindings[0].kind = OGA_BINDING_SAMPLE_MODE;
    layout_bindings[0].binding_slot = 0;
    layout_bindings[0].binding_count = 1;
    layout_bindings[0].stage_flags = OGA_PROGRAM_STAGE_FRAGMENT;
    
    layout_bindings[1].kind = OGA_BINDING_BLOCK;
    layout_bindings[1].binding_slot = 1;
    layout_bindings[1].binding_count = 1;
    layout_bindings[1].stage_flags = OGA_PROGRAM_STAGE_FRAGMENT | OGA_PROGRAM_STAGE_VERTEX;
    
    layout_bindings[2].kind = OGA_BINDING_FBUFFER;
    layout_bindings[2].binding_slot = 2;
    layout_bindings[2].binding_count = 1;
    layout_bindings[2].stage_flags = OGA_PROGRAM_STAGE_FRAGMENT;
    
    Oga_Binding_List_Layout *binding_layout = 0;
    Oga_Binding_List_Layout_Desc binding_layout_desc = (Oga_Binding_List_Layout_Desc){0};
    binding_layout_desc.bindings = layout_bindings;
    binding_layout_desc.binding_count = sizeof(layout_bindings)/sizeof(layout_bindings[0]);
    binding_layout_desc.binding_list_count = 3; // Frames in flight. 
    if (!check_oga_result(oga_init_binding_list_layout(context, binding_layout_desc, &binding_layout)))
        return 1;
    
    Oga_Binding_List *binding_list = 0;
    
    Oga_Sample_Mode_Desc sample_mode = (Oga_Sample_Mode_Desc){0};
    sample_mode.magnification_filter = OGA_SAMPLE_FILTER_NEAREST;
    sample_mode.minification_filter = OGA_SAMPLE_FILTER_NEAREST;
    sample_mode.address_mode_u = OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_EDGE;
    sample_mode.address_mode_v = OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_EDGE;
    
    Oga_Binding_Desc bindings[3] = {0};
    bindings[0].kind = OGA_BINDING_SAMPLE_MODE;
    bindings[0].count = 1;
    bindings[0].binding_slot = 0;
    bindings[0].array_index = 0;
    bindings[0].sample_modes = &sample_mode;
    
    bindings[1].kind = OGA_BINDING_BLOCK;
    bindings[1].count = 1;
    bindings[1].binding_slot = 1;
    bindings[1].array_index = 0;
    bindings[1].blocks = &block;
    
    bindings[2].kind = OGA_BINDING_FBUFFER;
    bindings[2].count = 1;
    bindings[2].binding_slot = 2;
    bindings[2].array_index = 0;
    bindings[2].fbuffers = &blend_buffer;
    
    Oga_Binding_List_Desc binding_list_desc = (Oga_Binding_List_Desc){0};
    binding_list_desc.bindings = bindings;
    binding_list_desc.binding_count = sizeof(bindings)/sizeof(bindings[0]);
    
    if (!check_oga_result(oga_push_binding_list(binding_layout, binding_list_desc, &binding_list)))
        return 1;
    
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
    render_desc.vertex_input_layout = vertex_layout_desc;
    render_desc.binding_list_layout = binding_layout;
    
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
        
    // GPU-waited latches that will be signalled when the next swapchain image is ready
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
    
    Oga_Gpu_Timestamp_Pool *timestamp_pool;
    if (!check_oga_result(oga_init_gpu_timestamp_pool(context, 2, &timestamp_pool)))
        return 1;
    
    
    
    while (running) {
        reset_temporary_storage();
        
#ifdef RUNNING_TESTS
        if (sys_get_seconds_monotonic()-start_time > TESTING_DURATION) {
            running = false;
        }
#endif // RUNNING_TESTS
        
        ///
        // Update the gpu data through the mapped memory
        // Make the color shift between red and normal
        gpu_data->tints[0] = f4(1.0f, 0.0f, 0.0f, 0.6f);
        gpu_data->tints[1] = f4(0.0f, 1.0f, 0.0f, 0.6f);
        gpu_data->tints[2] = f4(0.0f, 0.0f, 1.0f, 0.6f);
        
        // Should appear in order, according to Z:
        //  Nearest:  [1]
        //  Middle:   [0]
        //  Furthest: [3]
        gpu_data->offsets[0] = f4(-0.5f,  0.25f, 0.5f, 0.0f);
        gpu_data->offsets[1] = f4( 0.5f,  0.25f, 0.0f, 0.0f);
        gpu_data->offsets[2] = f4( 0.0f, -0.25f, 1.0f, 0.0f);
        
        float64 now = sys_get_seconds_monotonic();
        float32 scale = 0.1f;
        float64 speed = 3.0;
        gpu_data->offsets[0] = f4_add(gpu_data->offsets[0], f4((f32)sin(speed*now+PI*1)*scale, (f32)-sin(speed*now+PI*3)*scale, 0.0, 0.0));
        gpu_data->offsets[1] = f4_add(gpu_data->offsets[1], f4((f32)sin(speed*now+PI*2)*scale, (f32)-sin(speed*now+PI*2)*scale, 0.0, 0.0));
        gpu_data->offsets[2] = f4_add(gpu_data->offsets[2], f4((f32)sin(speed*now+PI*3)*scale, (f32)-sin(speed*now+PI*1)*scale, 0.0, 0.0));
        
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
        oga_cmd_reset_timestamp_pool(cmd, timestamp_pool);
        
        ///
        // Start the render pass
        
        Oga_Render_Attachment_Desc attachment = (Oga_Render_Attachment_Desc){0};
        attachment.image = swapchain->images[image_index];
        attachment.load_op = OGA_ATTACHMENT_LOAD_OP_CLEAR;
        attachment.store_op = OGA_ATTACHMENT_STORE_OP_STORE;
        memcpy(attachment.clear_color, &(float32[4]){0.39f, 0.58f, 0.93f, 1.0f}, 16);
        
        oga_cmd_fill_image(cmd, blend_buffer_copy_dst, f4(0.39f, 0.58f, 0.93f, 1.0f));
        
        Oga_Begin_Render_Pass_Desc begin_desc = (Oga_Begin_Render_Pass_Desc){0};
        begin_desc.render_area_width = 800;
        begin_desc.render_area_height = 600;
        begin_desc.attachment_count = 1;
        begin_desc.attachments = &attachment;
        
        oga_cmd_write_timestamp(cmd, timestamp_pool);
        oga_cmd_begin_render_pass(cmd, render_pass, begin_desc);
        
        oga_cmd_bind_render_pass_binding_list(cmd, render_pass, binding_list);
        
        // The draw call
        Oga_Draw_Desc draw_desc = (Oga_Draw_Desc){0};
        draw_desc.draw_type = OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED;
        draw_desc.vertex_count = sizeof(verts)/sizeof(verts[0]);
        draw_desc.vertex_list_bindings[0] = vlist;
        draw_desc.vertex_list_binding_count = 1;
        draw_desc.index_count = 6;
        draw_desc.index_list = ilist;
        draw_desc.index_type = OGA_INDEX_U32;
        draw_desc.instance_count = 3;
        check_oga_result(oga_cmd_draw(cmd, draw_desc));
        
        oga_cmd_end_render_pass(cmd, render_pass);
        oga_cmd_write_timestamp(cmd, timestamp_pool);
        
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
        
        float64 timestamps[2];
        if (!check_oga_result(oga_read_timestamps(timestamp_pool, timestamps, true)))
            return 1;
        float64 t = timestamps[1]-timestamps[0];
        float64 tmcs = (timestamps[1]-timestamps[0])/1000.0;
        print("Draw took %f ns / %f mcs on GPU\n", t, tmcs);
        
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
    oga_uninit_gpu_timestamp_pool(timestamp_pool);
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
    oga_uninit_fbuffer_view(blend_buffer);
    oga_uninit_optimal_copy_view(blend_buffer_copy_dst);
    oga_uninit_block_view(block);
    oga_uninit_index_list_view(ilist);
    oga_uninit_vertex_list_view(vlist);
    oga_unmap_memory(reflected_mem);
    oga_deallocate_memory(static_mem);
    oga_deallocate_memory(reflected_mem);
    oga_uninit_render_pass(render_pass);
    oga_uninit_binding_list_layout(binding_layout);
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
