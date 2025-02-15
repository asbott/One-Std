#ifndef OGA_GRAPHICS
#define OGA_GRAPHICS

#if 0
#include "ostd.h" // For syntax highlighting.
#endif

typedef enum Oga_Result {
    OGA_OK,

    OGA_SUBOPTIMAL,
    OGA_NOT_READY,
    OGA_TIMEOUT,

    // Trying to use device features that were not available.
    // Check Oga_Device::features flags for whether or not a feature is available.
    OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES,
    
    OGA_CONTEXT_INIT_ERROR_BAD_STATE_ALLOCATOR,
    
    // The given family index is not within the range 0 .. Oga_Device::engine_family_count
    OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE,
    // The given engine creation count overflows that of Oga_Logical_Engine_Family_Info::engine_capacity
    OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW,
    
    OGA_INIT_SWAPCHAIN_ERROR_SURFACE_REJECTED,
    OGA_INIT_SWAPCHAIN_ERROR_UNSUPPORTED_PRESENT_MODE,
    
    OGA_INIT_PROGRAM_ERROR_BAD_CODE,
    
    OGA_ERROR_STATE_ALLOCATION_FAILED,
    OGA_ERROR_OUT_OF_DEVICE_MEMORY,
    OGA_ERROR_OUTDATED,
    OGA_ERROR_SURFACE_LOST,
    
} Oga_Result;

unit_local inline string oga_get_result_name(Oga_Result r) {
    switch (r) {
        case OGA_OK: return STR("OGA_OK");
        case OGA_SUBOPTIMAL:                                            return STR("OGA_SUBOPTIMAL");
        case OGA_NOT_READY:                                             return STR("OGA_NOT_READY");
        case OGA_TIMEOUT:                                               return STR("OGA_TIMEOUT");
        case OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES:            return STR("OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES");
        case OGA_CONTEXT_INIT_ERROR_BAD_STATE_ALLOCATOR:                return STR("OGA_CONTEXT_INIT_ERROR_BAD_STATE_ALLOCATOR");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE: return STR("OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW:  return STR("OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW");
        case OGA_INIT_SWAPCHAIN_ERROR_SURFACE_REJECTED:                 return STR("OGA_INIT_SWAPCHAIN_ERROR_SURFACE_REJECTED");
        case OGA_INIT_SWAPCHAIN_ERROR_UNSUPPORTED_PRESENT_MODE:         return STR("OGA_INIT_SWAPCHAIN_ERROR_UNSUPPORTED_PRESENT_MODE");
        case OGA_INIT_PROGRAM_ERROR_BAD_CODE:                           return STR("OGA_INIT_PROGRAM_ERROR_BAD_CODE");
        case OGA_ERROR_STATE_ALLOCATION_FAILED:                         return STR("OGA_ERROR_STATE_ALLOCATION_FAILED");
        case OGA_ERROR_OUT_OF_DEVICE_MEMORY:                            return STR("OGA_ERROR_OUT_OF_DEVICE_MEMORY");
        case OGA_ERROR_OUTDATED:                                        return STR("OGA_ERROR_OUTDATED");
        case OGA_ERROR_SURFACE_LOST:                                    return STR("OGA_ERROR_SURFACE_LOST");
        default: return STR("<>");
    }
    return STR("<>");
}
unit_local inline string oga_get_result_message(Oga_Result r) {
    switch (r) {
        case OGA_OK: return STR("No error");
        case OGA_SUBOPTIMAL: 
            return STR("Swapchain is suboptimal and should be recreated, but can still be used.");
        case OGA_NOT_READY: 
            return STR("Swapchain has no ready images yet");
        case OGA_TIMEOUT: 
            return STR("A timeout expired");
        case OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES:
            return STR("Trying to use device features that were not available. Check Oga_Device::features flags for whether or not a feature is available.");
        case OGA_CONTEXT_INIT_ERROR_BAD_STATE_ALLOCATOR:
            return STR("Passed a bad state allocator. allocator.proc is null.");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE:
            return STR("The given family index is not within the range 0 .. Oga_Device::engine_family_count");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW:
            return STR("The given engine creation count overflows that of Oga_Logical_Engine_Family_Info::engine_capacity");
        case OGA_INIT_SWAPCHAIN_ERROR_SURFACE_REJECTED:
            return STR("The provided surface handle was rejected, possibly bad.");
        case OGA_INIT_SWAPCHAIN_ERROR_UNSUPPORTED_PRESENT_MODE:
            return STR("The provided present_mode was either unsupported or just an invalid value.");
        case OGA_INIT_PROGRAM_ERROR_BAD_CODE:
            return STR("The code passed was bad (or code_size) was incorrect.");
        case OGA_ERROR_STATE_ALLOCATION_FAILED:
            return STR("An allocation with the state_allocator passed in Oga_Context creation returned null upon allocation.");
        case OGA_ERROR_OUT_OF_DEVICE_MEMORY:
            return STR("Out of device memory");
        case OGA_ERROR_OUTDATED:
            return STR("A swapchain has become out of date and can no longer present");
        case OGA_ERROR_SURFACE_LOST:
            return STR("A surface was lost; closed or corrupt");
        default: return STR("<>");
    }
    return STR("<>");
}

typedef enum Oga_Format {
    OGA_FORMAT_R8_UNORM,
    OGA_FORMAT_R8_SNORM,
    OGA_FORMAT_R8_UINT,
    OGA_FORMAT_R8_SINT,
    OGA_FORMAT_R8G8_UNORM,
    OGA_FORMAT_R8G8_SNORM,
    OGA_FORMAT_R8G8_UINT,
    OGA_FORMAT_R8G8_SINT,
    OGA_FORMAT_R8G8B8A8_UNORM,
    OGA_FORMAT_R8G8B8A8_SNORM,
    OGA_FORMAT_R8G8B8A8_UINT,
    OGA_FORMAT_R8G8B8A8_SINT,
    OGA_FORMAT_R8G8B8A8_SRGB,
    OGA_FORMAT_B8G8R8A8_UNORM,
    OGA_FORMAT_B8G8R8A8_SNORM,
    OGA_FORMAT_B8G8R8A8_UINT,
    OGA_FORMAT_B8G8R8A8_SINT,
    OGA_FORMAT_B8G8R8A8_SRGB,
    OGA_FORMAT_R16G16B16A16_SFLOAT,
    OGA_FORMAT_R32G32B32A32_SFLOAT,
    OGA_FORMAT_DEPTH32_SFLOAT,
    OGA_FORMAT_DEPTH32_SFLOAT_S8_UINT,
    OGA_FORMAT_DEPTH24_UNORM_S8_UINT,
    OGA_FORMAT_DEPTH16_UNORM,
    
    OGA_FORMAT_ENUM_MAX,
} Oga_Format;

unit_local inline string oga_format_str(Oga_Format f) {
    switch (f) {
        case OGA_FORMAT_R8_UNORM:               return RSTR(R8_UNORM);
        case OGA_FORMAT_R8_SNORM:               return RSTR(R8_SNORM);
        case OGA_FORMAT_R8_UINT:                return RSTR(R8_UINT);
        case OGA_FORMAT_R8_SINT:                return RSTR(R8_SINT);
        case OGA_FORMAT_R8G8_UNORM:             return RSTR(R8G8_UNORM);
        case OGA_FORMAT_R8G8_SNORM:             return RSTR(R8G8_SNORM);
        case OGA_FORMAT_R8G8_UINT:              return RSTR(R8G8_UINT);
        case OGA_FORMAT_R8G8_SINT:              return RSTR(R8G8_SINT);
        case OGA_FORMAT_R8G8B8A8_UNORM:         return RSTR(R8G8B8A8_UNORM);
        case OGA_FORMAT_R8G8B8A8_SNORM:         return RSTR(R8G8B8A8_SNORM);
        case OGA_FORMAT_R8G8B8A8_UINT:          return RSTR(R8G8B8A8_UINT);
        case OGA_FORMAT_R8G8B8A8_SINT:          return RSTR(R8G8B8A8_SINT);
        case OGA_FORMAT_R8G8B8A8_SRGB:          return RSTR(R8G8B8A8_SRGB);
        case OGA_FORMAT_B8G8R8A8_UNORM:         return RSTR(B8G8R8A8_UNORM);
        case OGA_FORMAT_B8G8R8A8_SNORM:         return RSTR(B8G8R8A8_SNORM);
        case OGA_FORMAT_B8G8R8A8_UINT:          return RSTR(B8G8R8A8_UINT);
        case OGA_FORMAT_B8G8R8A8_SINT:          return RSTR(B8G8R8A8_SINT);
        case OGA_FORMAT_B8G8R8A8_SRGB:          return RSTR(B8G8R8A8_SRGB);
        case OGA_FORMAT_R16G16B16A16_SFLOAT:    return RSTR(R16G16B16A16_SFLOAT);
        case OGA_FORMAT_R32G32B32A32_SFLOAT:    return RSTR(R32G32B32A32_SFLOAT);
        case OGA_FORMAT_DEPTH32_SFLOAT:         return RSTR(DEPTH32_SFLOAT);
        case OGA_FORMAT_DEPTH32_SFLOAT_S8_UINT: return RSTR(DEPTH32_SFLOAT_S8_UINT);
        case OGA_FORMAT_DEPTH24_UNORM_S8_UINT:  return RSTR(DEPTH24_UNORM_S8_UINT);
        case OGA_FORMAT_DEPTH16_UNORM:          return RSTR(DEPTH16_UNORM);
        
        case OGA_FORMAT_ENUM_MAX:
        default: return RSTR(<>);
    }
    return RSTR(<>);
}

typedef enum Oga_Memory_Property_Flag {
    // Memory is near GPU and accessed with high performance
    OGA_MEMORY_PROPERTY_GPU_LOCAL  = 0x00000001,
    // Memory can be mapped
    OGA_MEMORY_PROPERTY_GPU_TO_CPU_MAPPABLE  = 0x00000002,
    // Memory is directly reflected on CPU. Mapping is not needed to access memory
    OGA_MEMORY_PROPERTY_GPU_TO_CPU_REFLECTED = 0x00000004,
    // Cached memory is accessed quicker, but does not instantly reflect GPU writes
    OGA_MEMORY_PROPERTY_GPU_TO_CPU_CACHED   = 0x00000008,
} Oga_Memory_Property_Flag;

// Unique identifer/handle for an instance of something.
// For example, if we need to know if two Oga_Device's are the same, we compare
// test them with a,id == b.id.
typedef void* Oga_Id;

typedef enum Oga_Sample_Count_Flag {
    OGA_SAMPLE_COUNT_1 = 1 << 0,
    OGA_SAMPLE_COUNT_2 = 1 << 1,
    OGA_SAMPLE_COUNT_4 = 1 << 2,
    OGA_SAMPLE_COUNT_8 = 1 << 3,
    OGA_SAMPLE_COUNT_16 = 1 << 4,
    OGA_SAMPLE_COUNT_32 = 1 << 5,
    OGA_SAMPLE_COUNT_64 = 1 << 6,
    OGA_SAMPLE_COUNT_128 = 1 << 7
} Oga_Sample_Count_Flag;

//////
// Device

typedef enum Oga_Logical_Engine_Family_Flags {
    OGA_LOGICAL_ENGINE_GRAPHICS = 1 << 0,
    OGA_LOGICAL_ENGINE_COMPUTE = 1 << 1,
    OGA_LOGICAL_ENGINE_TRANSFER = 1 << 2,
    OGA_LOGICAL_ENGINE_PRESENT = 1 << 3,
} Oga_Logical_Engine_Family_Flags;

typedef struct Oga_Logical_Engine_Family_Info {
    Oga_Logical_Engine_Family_Flags flags;
    u32 engine_capacity;
} Oga_Logical_Engine_Family_Info;

typedef struct Oga_Memory_Heap {
    Oga_Memory_Property_Flag properties;
    u64 size;
} Oga_Memory_Heap;

typedef enum Oga_Device_Kind {
    OGA_DEVICE_DISCRETE,
    OGA_DEVICE_INTEGRATED,
    OGA_DEVICE_CPU, // Software implementations
    OGA_DEVICE_OTHER,
} Oga_Device_Kind;

// todo(charlie) populate this with an exhaustive list.
typedef struct Oga_Device_Limits {
    u64 max_program_pointer_sets_per_stage;

    u64 max_fast_data_blocks_per_stage;
    u64 max_large_data_blocks_per_stage;
    u64 max_fast_images_per_stage;
    u64 max_large_images_per_stage;
    u64 max_samplers_per_stage;

    u64 max_fast_data_blocks_per_layout;
    u64 max_large_data_blocks_per_layout;
    u64 max_fast_images_per_layout;
    u64 max_large_images_per_layout;
    u64 max_samplers_per_layout;

    u64 max_memory_allocations;
    u64 max_sampler_allocations;

    u64 max_image_dimension_1d;
    u64 max_image_dimension_2d;
    u64 max_image_dimension_3d;

    u64 max_fast_access_data_block_size;

    u64 max_vertex_layout_attributes;
    u64 max_vertex_layout_bindings;
    u64 max_vertex_layout_attribute_offset;
    u64 max_vertex_layout_binding_stride;

    u64 max_fragment_stage_output_attachments;

    float32 max_sampler_anisotropy;

    u64 max_viewports;
    u64 max_viewport_width;
    u64 max_viewport_height;

    u64 max_framebuffer_width;
    u64 max_framebuffer_height;

    u64 max_render_attachments;

    u64 min_memory_map_alignment;

    Oga_Sample_Count_Flag supported_sample_counts_render_pass;

    Oga_Sample_Count_Flag supported_sample_counts_fast_image_float;
    Oga_Sample_Count_Flag supported_sample_counts_large_image_float;
    Oga_Sample_Count_Flag supported_sample_counts_fast_image_int;
    Oga_Sample_Count_Flag supported_sample_counts_large_image_int;
    
    u64 memory_granularity;

} Oga_Device_Limits;

typedef u64 Oga_Device_Feature_Flag;

#define OGA_DEVICE_FEATURE_GRAPHICS_TIMESTAMP (1 << 0)
#define OGA_DEVICE_FEATURE_COMPUTE_TIMESTAMP  (1 << 1)
#define OGA_DEVICE_FEATURE_PRESENT_MAILBOX    (1 << 2)
#define OGA_DEVICE_FEATURE_DEPTH_CLAMP    (1 << 3)

unit_local inline string oga_device_feature_str(Oga_Device_Feature_Flag f) {
    switch (f) {
        case OGA_DEVICE_FEATURE_GRAPHICS_TIMESTAMP: return STR("Graphics Timestamps");
        case OGA_DEVICE_FEATURE_COMPUTE_TIMESTAMP: return STR("Compute Timestamps");
        case OGA_DEVICE_FEATURE_PRESENT_MAILBOX: return STR("Present mailbox");
        default: return STR("<>");
    }
    return STR("<>");
}

#define OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES 32
#define OGA_MAX_DEVICE_LOGICAL_ENGINES_PER_FAMILY 32
#define OGA_MAX_MEMORY_HEAPS_PER_DEVICE 32
typedef struct Oga_Device {
    void *id;

    Oga_Device_Kind kind;

    // string
    u8 device_name_data[256];
    u64 device_name_length;

    string vendor_name;
    u32 driver_version_raw;

    // string
    u8 driver_version_data[128];
    u64 driver_version_length;
    
    u32 api_version_raw;
    // string
    u8 api_version_data[128];
    u64 api_version_length;
    
    Oga_Device_Limits limits;

    Oga_Logical_Engine_Family_Info engine_family_infos[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES];
    u32 engine_family_count;

    Oga_Format depth_format;

    Oga_Memory_Heap memory_heaps[OGA_MAX_MEMORY_HEAPS_PER_DEVICE];
    u64 memory_heap_count;
    u64 total_gpu_local_memory;

    Oga_Device_Feature_Flag features;
    
    Oga_Format supported_surface_formats[OGA_FORMAT_ENUM_MAX];
    u64 supported_surface_format_count;

} Oga_Device;

typedef enum Oga_Device_Pick_Flag {
    OGA_DEVICE_PICK_NONE = 0,
    OGA_DEVICE_PICK_PREFER_DISCRETE = 1 << 0,
    OGA_DEVICE_PICK_PREFER_INTEGRATED = 1 << 1,
    OGA_DEVICE_PICK_PREFER_CPU = 1 << 2,
    OGA_DEVICE_PICK_REQUIRE_DISCRETE = 1 << 3,
    OGA_DEVICE_PICK_REQUIRE_INTEGRATED = 1 << 4,
    OGA_DEVICE_PICK_REQUIRE_CPU = 1 << 5,
} Oga_Device_Pick_Flag;

u64 oga_query_devices(Oga_Device *buffer, u64 buffer_count);
Oga_Device *oga_get_devices(Allocator a, u64 *count);

typedef struct Oga_Pick_Device_Result {
    bool passed;
    Oga_Device device;
    Oga_Device_Pick_Flag failed_pick_flags;
    Oga_Device_Feature_Flag failed_required_features;
    Oga_Device_Feature_Flag failed_preferred_features;
} Oga_Pick_Device_Result;
Oga_Pick_Device_Result oga_pick_device(Oga_Device_Pick_Flag pick_flags, Oga_Device_Feature_Flag required_features, Oga_Device_Feature_Flag preferred_features);

//////////
/// Oga Context


typedef struct Oga_Logical_Engines_Create_Desc {
    u32 count;
    float32 priorities[OGA_MAX_DEVICE_LOGICAL_ENGINES_PER_FAMILY]; // normalized 0.0-1.0.
} Oga_Logical_Engines_Create_Desc;

// Default allocator of non is specified in Oga_Context_Desc::state_allocator
void* oga_state_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags);


typedef struct Oga_Allocator_Row {
    void *start;
    void *end;
    u64 first_free_index;
    u64 highest_allocated_index;
} Oga_Allocator_Row;
typedef struct Oga_State_Allocator_Data {
    // 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8196, 16384
    Oga_Allocator_Row rows[11];
} Oga_State_Allocator_Data;

typedef struct Oga_Context_Desc {
    // Indices match to that of Oga_Device::engine_family_infos.
    // So the create engines of family 0, you set the desc in engine_create_descs[0].
    // Leave descs uninitialized to make no engines in that family.
    Oga_Logical_Engines_Create_Desc engine_create_descs[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES];
    Oga_Device_Feature_Flag enabled_features;
    Allocator state_allocator; // The allocator used to allocate state & handles in this context. Will only be used when creating/destroying things.
} Oga_Context_Desc;

// Some hardware expose their engines, some don't.
// So we deal with Logical Engines, which may or may not map directly to
// hardware engines.
// Equivalent to a vulkan Queue
typedef struct Oga_Logical_Engine {
    void *id;
    u32 index;
} Oga_Logical_Engine;

typedef struct Oga_Logical_Engine_Group {
    Oga_Logical_Engine engines[OGA_MAX_DEVICE_LOGICAL_ENGINES_PER_FAMILY];
    u64 engine_count;
} Oga_Logical_Engine_Group;

typedef struct Oga_Context {
    void *id;
    void *internal;
    Oga_Device device;
    Oga_Logical_Engine_Group engines_by_family[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES];
    Allocator state_allocator;
    
    Oga_State_Allocator_Data default_allocator_data; // Backing for Allocator::data
} Oga_Context;

Oga_Result oga_init_context(Oga_Device target_device, Oga_Context_Desc desc, Oga_Context **context);
void oga_uninit_context(Oga_Context *context);


//////////
/// Swap chain

typedef enum Oga_Present_Mode {
    // Present() will halt the thread until at least 1 image is ready to be queued,
    // and then each image in the queue is presented and popped each vertical blank.
    OGA_PRESENT_MODE_VSYNC,
    // Present() Will submit the image to the queue, and if the queue is full, it will
    //  abort the image currently being presented, which will very likely cause visual tearing.
    // There may techically be devices that only support OGA_PRESENT_MODE_VSYNC, and in such
    // rare cases this will fallback to that.
    OGA_PRESENT_MODE_IMMEDIATE,
    // Present() will submit the image to the queue, resetting the oldest pending image
    //  if queue is full, and will NOT halt the thread. This won't cause tearing, but will
    //  discard some submitted frames if submitted at a higher rate than vertical blank rate.
    // Check device feature flag OGA_DEVICE_FEATURE_PRESENT_MAILBOX
    OGA_PRESENT_MODE_VSYNC_MAILBOX 
} Oga_Present_Mode;

typedef struct Oga_Swapchain_Desc {
    Surface_Handle surface;
    u64 requested_image_count;
    Oga_Format image_format;
    u64 width;
    u64 height;
    u64 *engine_families_with_access; // The indices of the queue families that will be allowed to access the images
    u64 engine_families_with_access_count;
    Oga_Present_Mode present_mode;
    
} Oga_Swapchain_Desc;



#define MAX_SWAPCHAIN_IMAGES 16

typedef struct Oga_Swapchain {
    void *id;
    Oga_Context *context;
    struct Oga_Image *images[MAX_SWAPCHAIN_IMAGES];
    u64 current_image_index;
    u64 image_count;
    Oga_Format image_format;
} Oga_Swapchain;

bool get_preferred_swapchain_format(Oga_Context *context, Oga_Format *wanted_formats, u64 count, Oga_Format *format);

Oga_Result oga_init_swapchain(Oga_Context *context, Oga_Swapchain_Desc desc, Oga_Swapchain **swapchain);
void oga_uninit_swapchain(Oga_Swapchain *swapchain);

struct Oga_Gpu_Latch;
struct Oga_Cpu_Latch;
Oga_Result oga_get_next_swapchain_image(Oga_Swapchain *swapchain, u64 timeout, struct Oga_Gpu_Latch *signal_gpu_latch, struct Oga_Cpu_Latch *signal_cpu_latch, u64 *image_index); 

typedef struct Oga_Present_Desc {
    Oga_Logical_Engine engine;
    u64 wait_gpu_latch_count;
    struct Oga_Gpu_Latch **wait_gpu_latches;
    u64 image_index;
} Oga_Present_Desc;
Oga_Result oga_submit_present(Oga_Swapchain *swapchain, Oga_Present_Desc desc);

/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/********************************* SPIRV HEADER START *********************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
#include "./../vendors/spirv/spirv.h"
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/********************************* SPIRV HEADER END ***********************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/

//////////
/// Render passes & Programs

typedef enum Oga_Program_Kind {
    OGA_PROGRAM_VERTEX,
    OGA_PROGRAM_FRAGMENT,
    OGA_PROGRAM_COMPUTE,
} Oga_Program_Kind;

typedef struct Oga_Program_Desc {
    const void *code; // Compiled code ready to send to drivers
    u64 code_size;
    Oga_Program_Kind kind;
} Oga_Program_Desc;

typedef struct Oga_Program {
    void *id;
    Oga_Context *context;
    Oga_Program_Kind kind;
} Oga_Program;

// Goes through OSL to compile osl lang to target drivers
// Oga_Result oga_compile_program_for_target

Oga_Result oga_init_program(Oga_Context *context, Oga_Program_Desc desc, Oga_Program **program);
void oga_uninit_program(Oga_Program *program);

typedef u64 Oga_Render_Pass_Flag;
unit_local Oga_Render_Pass_Flag OGA_RENDER_PASS_INHERITANCE_PARENT = 1 << 0;
unit_local Oga_Render_Pass_Flag OGA_RENDER_PASS_INHERITANCE_CHILD = 1 << 1;
unit_local Oga_Render_Pass_Flag OGA_RENDER_PASS_DISABLE_DEPTH_CLAMP = 1 << 2;

// #Volatile values must map to same as vulkan equivalents
typedef enum Oga_Primitive_Topology {
    OGA_PRIMITIVE_TOPOLOGY_POINT_LIST = 0,
    OGA_PRIMITIVE_TOPOLOGY_LINE_LIST = 1,
    OGA_PRIMITIVE_TOPOLOGY_LINE_STRIP = 2,
    OGA_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 3,
    OGA_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = 4
} Oga_Primitive_Topology;

typedef enum Oga_Cull_Mode {
    OGA_CULL_NONE,
    OGA_CULL_CLOCKWISE,
    OGA_CULL_COUNTER_CLOCKWISE,
} Oga_Cull_Mode;

struct Oga_Render_Pass;
typedef struct Oga_Render_Pass_Desc {
    
    Oga_Render_Pass_Flag flags;
    struct Oga_Render_Pass *base;
    u64 base_index; // Index into buffer of descs passed. Only used if base is null.
    
    Oga_Program *vertex_program;
    string vertex_program_entry_point;
    Oga_Program *fragment_program;
    string fragment_program_entry_point;
    
    Oga_Format *attachment_formats;
    u64 attachment_count;
    
    Oga_Primitive_Topology topology;
    
    Oga_Cull_Mode cull_mode;
    
    float32 line_width;
    
    // See Oga_Device::limits.supported_sample_counts_render_pass
    Oga_Sample_Count_Flag rasterization_samples;
    
} Oga_Render_Pass_Desc;

typedef struct Oga_Render_Pass {
    void *id;
    Oga_Context *context;
} Oga_Render_Pass;

Oga_Result oga_init_render_passes(Oga_Context *context, Oga_Render_Pass_Desc* descs, Oga_Render_Pass **render_passes, u64 render_pass_count);

Oga_Result oga_init_render_pass(Oga_Context *context, Oga_Render_Pass_Desc desc, Oga_Render_Pass **render_pass);
void oga_uninit_render_pass(Oga_Render_Pass *render_pass);

//////////
/// Synchronization

// Gpu latch; for synchronizing on gpu. Signalled on gpu, waited on gpu.
typedef struct Oga_Gpu_Latch {
    void *id;
    Oga_Context *context;
} Oga_Gpu_Latch;

Oga_Result oga_init_gpu_latch(Oga_Context *context, Oga_Gpu_Latch **gpu_latch);
void oga_uninit_gpu_latch(Oga_Gpu_Latch *gpu_latch);

// Cpu latch; for synchronizing cpu with gpu. Signalled on gpu, waited on cpu.
typedef struct Oga_Cpu_Latch {
    void *id;
    Oga_Context *context;
} Oga_Cpu_Latch;
Oga_Result oga_init_cpu_latch(Oga_Context *context, Oga_Cpu_Latch **cpu_latch, bool start_signaled);
void oga_uninit_cpu_latch(Oga_Cpu_Latch *cpu_latch);
Oga_Result oga_wait_latch(Oga_Cpu_Latch *cpu_latch);
Oga_Result oga_reset_latch(Oga_Cpu_Latch *cpu_latch);

//////////
/// Memory & Pointers

typedef struct Oga_Memory {
    u64 size;
    Oga_Memory_Property_Flag usage;
} Oga_Memory;
#define OGA_INTERNALLY_MANAGED_MEMORY_HANDLE ((void*)0xFFFFFFFFFFFFFFFF)

Oga_Result oga_allocate_memory(Oga_Context *context, u64 size, Oga_Memory_Property_Flag usage_flags);
void oga_deallocate_memory(Oga_Memory *mem);
Oga_Result oga_map_memory(Oga_Memory *mem, u64 offset, u64 size, void *mapped_mem);
Oga_Result oga_unmap_memory(Oga_Memory *mem);

typedef u64 Oga_Image_Optimization;
#define OGA_IMAGE_OPTIMIZATION_UNDEFINED 0
#define OGA_IMAGE_OPTIMIZATION_GENERAL 1
#define OGA_IMAGE_OPTIMIZATION_RENDER_ATTACHMENT 2
#define OGA_IMAGE_OPTIMIZATION_SHADER_READONLY 3
#define OGA_IMAGE_OPTIMIZATION_TRANSFER_DST 4
#define OGA_IMAGE_OPTIMIZATION_TRANSFER_SRC 5
#define OGA_IMAGE_OPTIMIZATION_PRESENT 6

typedef enum Oga_Pointer_Kind {
    OGA_POINTER_KIND_PROGRAM_POINTER,
    OGA_POINTER_KIND_VERTEX_LIST,
    OGA_POINTER_KIND_INDEX_LIST,
    OGA_POINTER_KIND_COPY_TASK,
} Oga_Pointer_Kind;

typedef enum Oga_Pointer_Flag {
    OGA_POINTER_FLAG_COPY_DST = 1 << 0,
    OGA_POINTER_FLAG_COPY_SRC = 1 << 1,
} Oga_Pointer_Flag;

typedef enum Oga_Program_Pointer_Kind {
    OGA_PROGRAM_POINTER_KIND_DATA_BLOCK,
    OGA_PROGRAM_POINTER_KIND_IMAGE1D,
    OGA_PROGRAM_POINTER_KIND_IMAGE2D,
    OGA_PROGRAM_POINTER_KIND_IMAGE3D,
} Oga_Program_Pointer_Kind;

typedef enum Oga_Program_Pointer_Flag {
    OGA_PROGRAM_POINTER_FLAG_READ,
    OGA_PROGRAM_POINTER_FLAG_WRITE,

    // When a program pointer is flagged with large or write, it can have larger
    // storage (or be written to) at the cost of memory access performance.
    // see limits max_fast_access_xxxxx_size
    OGA_PROGRAM_POINTER_FLAG_LARGE,
} Oga_Program_Pointer_Flag;

typedef struct Oga_Program_Pointer_Desc {
    Oga_Program_Pointer_Kind kind;
    Oga_Program_Pointer_Flag flags;

} Oga_Program_Pointer_Desc;

typedef struct Oga_Vertex_List_Desc  {
    int _;
} Oga_Vertex_List_Desc;

typedef struct Oga_Index_List_Desc  {
    int _;

} Oga_Index_List_Desc;

typedef struct Oga_Copy_Task_Desc  {
    int _;

} Oga_Copy_Task_Desc;

typedef struct Oga_Pointer_Desc {
    Oga_Pointer_Kind kind;
    Oga_Pointer_Flag flags;

    Oga_Memory *memory;
    u64 memory_offset;
    
    union {
        Oga_Program_Pointer_Desc program_pointer;
        Oga_Vertex_List_Desc vertex_list;
        Oga_Index_List_Desc index_list;
        Oga_Copy_Task_Desc copy_task;
    } UNION;
} Oga_Pointer_Desc;

//Oga_Result oga_make_pointer(Oga_Context c, Oga_Pointer_Desc desc);

// Program Pointers can be trivially casted
// Oga_Image2D *my_image = ...;
// Oga_Pointer *some_pointer = (Oga_Pointer *)my_image;
// ...
// if (some_pointer->kind == OGA_PROGRAM_POINTER_KIND_IMAGE2D) {
//     Oga_Image2D *as_image = (Oga_Image2D*)some_pointer;
// }


typedef struct Oga_Pointer {
#define OGA_POINTER_MEMBERS\
    void *id;\
    Oga_Memory *memory; /* This will be set to 0xFFFFFFFFFFFFFFFF if memory is internally managed in drivers */ \
    Oga_Pointer_Kind pointer_kind;
    
    OGA_POINTER_MEMBERS
} Oga_Pointer;

typedef struct Oga_Program_Pointer {
#define OGA_PROGRAM_POINTER_MEMBERS OGA_POINTER_MEMBERS\
    Oga_Program_Pointer_Kind program_pointer_kind;
    
    OGA_PROGRAM_POINTER_MEMBERS
} Oga_Program_Pointer;

typedef enum Oga_Image_Kind {
    OGA_IMAGE_1D,
    OGA_IMAGE_2D,
    OGA_IMAGE_3D,
} Oga_Image_Kind;

typedef struct Oga_Image {
    OGA_PROGRAM_POINTER_MEMBERS
        
    u64 width, height, depth;
    Oga_Image_Kind image_kind;
} Oga_Image;


// This is really only here to get validation/debug layer messages for leaked resources
void oga_reset(void);


//////////
/// Commands

// note(charlie)
// If it was up to me, I would let you manage your own memory.
// Unfortunately, graphics API designers decided that we can't be trusted.
// So we need to use this really weird, intrusive, generalized mystical abstraction,
// praying to the driver gods that it's good enough.

typedef u64 Oga_Command_Pool_Flag;
#define  OGA_COMMAND_POOL_NONE 0
#define  OGA_COMMAND_POOL_SHORT_LIVED (1 << 0)

typedef struct Oga_Command_Pool_Desc {
    Oga_Command_Pool_Flag flags;
    u64 engine_family_index; // Pinky promise which queue family this will be submitted to
} Oga_Command_Pool_Desc;

typedef struct Oga_Command_Pool {
    void *id;
    Oga_Context *context;
} Oga_Command_Pool;

typedef struct Oga_Command_List {
    void *id;
    Oga_Command_Pool *pool;
} Oga_Command_List;

Oga_Result oga_init_command_pool(Oga_Context *context, Oga_Command_Pool_Desc desc, Oga_Command_Pool **pool);
 // This will free all command lists, so you do not need to explicitly free each command list.
void oga_uninit_command_pool(Oga_Command_Pool *pool);
void oga_reset_command_pool(Oga_Command_Pool *pool);

Oga_Result oga_get_command_lists(Oga_Command_Pool *pool, Oga_Command_List *lists, u64 list_count);
void oga_release_command_lists(Oga_Command_List *lists, u64 list_count);



typedef u64 Oga_Command_List_Usage_Flag;
#define OGA_COMMAND_LIST_USAGE_ONE_TIME_SUBMIT (1 << 0)

Oga_Result oga_cmd_begin(Oga_Command_List cmd, Oga_Command_List_Usage_Flag flags);
Oga_Result oga_cmd_end(Oga_Command_List cmd);

typedef struct Oga_Submit_Command_List_Desc {
    Oga_Logical_Engine engine; 
    Oga_Gpu_Latch **wait_gpu_latches; 
    u64 wait_gpu_latch_count; 
    Oga_Gpu_Latch **signal_gpu_latches; 
    u64 signal_gpu_latch_count; 
    Oga_Cpu_Latch *signal_cpu_latch;
} Oga_Submit_Command_List_Desc;
Oga_Result oga_submit_command_list(Oga_Command_List cmd, Oga_Submit_Command_List_Desc desc);

void oga_cmd_transition_image_optimization(Oga_Command_List cmd, Oga_Image *image, Oga_Image_Optimization src_optimization, Oga_Image_Optimization optimization);

typedef u64 Oga_Msaa_Resolve_Mode_Flag;
#define OGA_MSAA_RESOLVE_MODE_NONE    0
#define OGA_MSAA_RESOLVE_MODE_ZERO    (1 << 0)
#define OGA_MSAA_RESOLVE_MODE_AVERAGE (1 << 1)
#define OGA_MSAA_RESOLVE_MODE_MIN     (1 << 2)
#define OGA_MSAA_RESOLVE_MODE_MAX     (1 << 3)

typedef enum Oga_Attachment_Load_Op {
    OGA_ATTACHMENT_LOAD_OP_LOAD,
    OGA_ATTACHMENT_LOAD_OP_CLEAR,
    OGA_ATTACHMENT_LOAD_OP_NOTHING
} Oga_Attachment_Load_Op;
typedef enum Oga_Attachment_Store_Op {
    OGA_ATTACHMENT_STORE_OP_STORE,
    OGA_ATTACHMENT_STORE_OP_NOTHING
} Oga_Attachment_Store_Op;

typedef struct Oga_Render_Attachment_Desc {
    Oga_Image *image;
    Oga_Image_Optimization image_optimization;
    
    // If rendering with multisampling, we can resolve the multiple samples into single samples
    // on another image.
    Oga_Msaa_Resolve_Mode_Flag resolve_mode;
    const Oga_Image *resolve_image;
    Oga_Image_Optimization resolve_image_optimization;
    
    Oga_Attachment_Load_Op load_op;
    Oga_Attachment_Store_Op store_op;
    
    float32 clear_color[4]; // In case of load_op CLEAR
    
} Oga_Render_Attachment_Desc;

typedef struct Oga_Begin_Render_Pass_Desc {
    Oga_Render_Pass *render_pass;
    s64 render_area_offset_x;
    s64 render_area_offset_y;
    u64 render_area_width;
    u64 render_area_height;
    u64 attachment_count;
    Oga_Render_Attachment_Desc *attachments;
} Oga_Begin_Render_Pass_Desc;

void oga_cmd_begin_render_pass(Oga_Command_List cmd, Oga_Begin_Render_Pass_Desc desc);
void oga_cmd_end_render_pass(Oga_Command_List cmd);

void oga_cmd_draw(Oga_Command_List cmd, u64 vertex_count, u64 vertex_start, u64 instance_count, u64 instance_start);

Oga_Result oga_cmd_copy_memory(Oga_Pointer *dst, Oga_Pointer *src, u64 offset, u64 size);

#ifdef OGA_IMPL_AUTO
    #if (OS_FLAGS & OS_FLAG_WEB)
        #define OGA_IMPL_WEBGPU
    #elif (OS_FLAGS & OS_FLAG_WINDOWS)
        #define OGA_IMPL_D3D12
    #elif (OS_FLAGS & OS_FLAG_APPLE)
        #define OGA_IMPL_METAL
    #elif OS_FLAGS != 0
        // If recognized OS, fallback to vulkan, because it's probably supported.
        // todo(charlie) consoles
        #define OGA_IMPL_VULKAN
    #endif
#endif // OGA_IMPL_HARDWARE_AUTO

#ifdef OSTD_IMPL

void* oga_state_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags) {
    (void)flags;
    (void)old_n;
    (void)alignment; // Since fitting into blocks, they will already be aligned
    Oga_State_Allocator_Data *a = (Oga_State_Allocator_Data*)data;
    
    System_Info info = sys_get_info();
    
    switch (msg) {
        case ALLOCATOR_ALLOCATE:
        {
            if (n > 16384) {
                // Just directly map pages for big allocations. This should be rare, or probably never happen.
                void *p = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, (n+info.page_size)/info.page_size, false);
                return p;
            }
        
            Oga_Allocator_Row *row = 0;
            u64 stride = 0;
            for (u64 i = 0; i < 11; i += 1) {
                u64 row_stride = powu(2, i+3);
                if (n <= row_stride) {
                    stride = row_stride;
                    row = &a->rows[i];
                    break;
                }
            }
            
            assert(row);
            
            if (!row->start) {
                // todo(charlie) #Portability
                // Need to find a portable free address space, or provide a way to query for such.

                void *reserved = sys_map_pages(SYS_MEMORY_RESERVE, 0, (1024*1024*1024)/info.page_size, false);
                assert(reserved);
                
                row->start = sys_map_pages(SYS_MEMORY_ALLOCATE, reserved, max(info.granularity, 1024*32)/info.page_size, true);
                
                if (!row->start) return 0;
                
                row->end = (u8*)row->start + (max(info.granularity, 1024*32)/info.page_size)*info.page_size;
                
                row->first_free_index = 0;
            }
            
            
            void *next = (u8*)row->start + row->first_free_index*stride;
            u64 allocated_index = ((u64)next-(u64)row->start)/stride;
            
            assert(row->first_free_index <= ((u64)row->end-(u64)row->start)/stride);
            
            if ((u8*)next == (u8*)row->end) {
                u64 old_size = (u64)row->end - (u64)row->start;
                u64 new_size = old_size*2;
                
                void *expansion = sys_map_pages(SYS_MEMORY_ALLOCATE, row->end, new_size/info.page_size, true);
#if OS_FLAGS & OS_FLAG_WINDOWS
                assert(expansion);
#endif
                if (!expansion) {  
                    // todo(charlie) #Portability #Memory #Speed
                    // If target system has poor mapping features, we might hit this often, which is kind of crazy.
                    void *p = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, (n+info.page_size)/info.page_size, false);
                    return p;
                }
                
                assert(expansion == row->end);
                row->end = (u8*)row->start + new_size;
            } else {
                assertmsgs((u64)next < (u64)row->end, tprint("%u, %u", next, row->end));
            }
            
            if (allocated_index >= row->highest_allocated_index) {
                row->first_free_index = allocated_index+1;
            } else {
                row->first_free_index = *(u64*)next;
            }
            
            assert(row->first_free_index <= ((u64)row->end-(u64)row->start)/stride);            assertmsgs((u64)((u8*)row->start + row->first_free_index*stride) <= (u64)row->end, tprint("%u, %u", next, row->end));
            
            row->highest_allocated_index = max(row->highest_allocated_index, allocated_index);
            
            assert(row->first_free_index <= row->highest_allocated_index+1);
            
            return next;
        }
        case ALLOCATOR_REALLOCATE:
        {
            void * pnew = oga_state_allocator_proc(ALLOCATOR_ALLOCATE, data, 0, 0, n, alignment, flags);
            memcpy(pnew, old, min(n, old_n));
            oga_state_allocator_proc(ALLOCATOR_FREE, data, old, 0, 0, alignment, flags);
            return pnew;
        }
        case ALLOCATOR_FREE:
        {
            Oga_Allocator_Row *row = 0;
            u64 stride = 16;
            for (u64 i = 0; i < 11; i += 1) {
                if ((u64)old >= (u64)a->rows[i].start && (u64)old < (u64)a->rows[i].end) {
                    row = &a->rows[i];
                    u64 exp = powu(2, i+3);
                    assertmsgs(stride == exp, tprint("%u, %u", stride, exp));
                    break;
                }
                stride *= 2;
            }
            
            
            if (!row) {
                sys_unmap_pages(old);
                return 0;
            }
            
            u64 offset = (u64)old - (u64)row->start;
            assert(offset % stride == 0);
            u64 index = offset/stride;
            
            *(u64*)old = row->first_free_index;
            row->first_free_index = index;
            
            assert(row->first_free_index <= ((u64)row->end-(u64)row->start)/stride);
            assert((u64)((u8*)row->start + row->first_free_index*stride) <= (u64)row->end);
            assert(row->first_free_index <= row->highest_allocated_index+1);
            
            break;
        }

        default:
        {
            break;
        }
    }

    return 0;
}

Oga_Pick_Device_Result oga_pick_device(Oga_Device_Pick_Flag pick_flags, Oga_Device_Feature_Flag required_features, Oga_Device_Feature_Flag preferred_features) {

    Oga_Device devices[32];
    u64 device_count = oga_query_devices(devices, 32);

    s64 device_scores[32] = {0};

    Oga_Pick_Device_Result results[32] = {0};

    for (u64 i = 0; i < device_count; i += 1) {
        Oga_Device device = devices[i];
        s64 *pscore = &device_scores[i];

        results[i].device = device;

        if ((pick_flags & OGA_DEVICE_PICK_REQUIRE_DISCRETE) && device.kind != OGA_DEVICE_DISCRETE)  {
            results[i].passed = false;
            results[i].failed_pick_flags |= OGA_DEVICE_PICK_REQUIRE_DISCRETE;
            continue;
        }
        if ((pick_flags & OGA_DEVICE_PICK_REQUIRE_INTEGRATED) && device.kind != OGA_DEVICE_INTEGRATED)  {
            results[i].passed = false;
            results[i].failed_pick_flags |= OGA_DEVICE_PICK_REQUIRE_INTEGRATED;
            continue;
        }
        if ((pick_flags & OGA_DEVICE_PICK_REQUIRE_CPU) && device.kind != OGA_DEVICE_CPU)  {
            results[i].passed = false;
            results[i].failed_pick_flags |= OGA_DEVICE_PICK_REQUIRE_CPU;
            continue;
        }

        if ((required_features & device.features) != required_features) {
            results[i].passed = false;
            results[i].failed_required_features |= ((required_features & device.features) & required_features);
            continue;
        }

        if ((pick_flags & OGA_DEVICE_PICK_PREFER_DISCRETE) && device.kind == OGA_DEVICE_DISCRETE)
            *pscore += 1000;
        if ((pick_flags & OGA_DEVICE_PICK_PREFER_INTEGRATED) && device.kind == OGA_DEVICE_INTEGRATED)
            *pscore += 1000;
        if ((pick_flags & OGA_DEVICE_PICK_PREFER_CPU) && device.kind == OGA_DEVICE_CPU)
            *pscore += 1000;
            
        *pscore += device.engine_family_count*10;
        
        // Whatever these drivers are, they cause a LOT of trouble.
        string device_name = (string) {device.device_name_length, device.device_name_data};
        if (string_contains(device_name, STR("Microsoft")) || string_contains(device_name, STR("Direct3D12"))) {
            *pscore -= 500;
        }
          
        u64 preferred_features_count = 0;
        for (u64 f = 0; f < 64; f += 1) {
            // Feature flag is preferred ?
            if (preferred_features & (1 << f)) {
                preferred_features_count += 1;
            }
        }

        if (preferred_features_count) {
            s64 score_per_feature = 1000/preferred_features_count;

            for (u64 f = 0; f < 64; f += 1) {
                // Feature flag is preferred ?
                if (preferred_features & (1 << f)) {
                    // Preferred feature flag is set on device ?
                    if (device.features & (1 << f)) {
                        *pscore += score_per_feature;
                    } else {
                        results[i].failed_preferred_features |= (1 << f);
                    }
                }
            }
        } else {
            *pscore += 1;
        }

        results[i].passed = *pscore > 0;
    }

    s64 max_score = 0;
    u64 winner_index = 0;
    for (u64 i = 0; i < device_count; i += 1) {
        if (device_scores[i] > max_score) {
            max_score = device_scores[i];
            winner_index = i;
        }
    }
    return results[winner_index];
}

bool get_preferred_swapchain_format(Oga_Context *context, Oga_Format *wanted_formats, u64 count, Oga_Format *format) {
    for (u64 i = 0; i < count; i += 1) {
        for (u64 j = 0; j < context->device.supported_surface_format_count; j += 1) {
            Oga_Format f = context->device.supported_surface_formats[j];
            if (f == wanted_formats[i]) {
                *format = f;
                return true;
            }
        }
    }
    
    return false;
}

#define VENDOR_ID_NVIDIA   0x10DE
#define VENDOR_ID_AMD      0x1002
#define VENDOR_ID_INTEL    0x8086
#define VENDOR_ID_ARM      0x13B5
#define VENDOR_ID_IMGTEC   0x1010
#define VENDOR_ID_QUALCOMM 0x5143

unit_local inline string _str_vendor_id(u32 id) {
    switch (id) {
        case VENDOR_ID_NVIDIA:   return RSTR(Nvidia);
        case VENDOR_ID_AMD:      return RSTR(Amd);
        case VENDOR_ID_INTEL:    return RSTR(Intel);
        case VENDOR_ID_ARM:      return RSTR(Arm);
        case VENDOR_ID_IMGTEC:   return RSTR(ImgTec);
        case VENDOR_ID_QUALCOMM: return RSTR(Qualcomm);
        default: return RSTR(<Unknown Vendor ID>);
    }

}

unit_local u64 _format_driver_version(u32 vendor_id, u32 driver_version, u8 *buffer, u64 buffer_size) {
    if (vendor_id == VENDOR_ID_NVIDIA) {
        u32 major = (driver_version >> 22) & 0x3FF;
        u32 minor = (driver_version >> 14) & 0xFF;
        u32 patch = (driver_version >> 6) & 0xFF;
        u32 build = driver_version & 0x3F;
        return format_string(buffer, buffer_size, "%u.%u.%u build %u", major, minor, patch, build);
    } else if (vendor_id == VENDOR_ID_NVIDIA) {
        u32 major = (driver_version >> 14);
        u32 minor = driver_version & 0x3FFF;
        return format_string(buffer, buffer_size, "%u.%u", major, minor);
    } else {
        return format_string(buffer, buffer_size, "%u", driver_version);
    }
}

inline string oga_format_str(Oga_Format f);

#ifdef OGA_IMPL_VULKAN

/////////////////////////////////////////////////////
//////
// :Vulkan
//////
/////////////////////////////////////////////////////

#define OGA_OL_TARGET OL_TARGET_SPIRV

#if COMPILER_FLAGS & COMPILER_FLAG_MSC
    #pragma comment(lib, "vendors/vulkan-1.lib")
#endif // COMPILER_FLAGS & COMPILER_FLAG_MSC

#if (OS_FLAGS & (OS_FLAG_WINDOWS | OS_FLAG_LINUX | OS_FLAG_MACOS | OS_FLAG_IOS | OS_FLAG_ANDROID)) == 0
    #error Vulkan is not supported on target platform
#else
    #include "graphics_vulkan.h"
#endif // (OS_FLAGS & (OS_FLAG_WINDOWS | OS_FLAG_LINUX | OS_FLAG_MACOS | OS_FLAG_IOS | OS_FLAG_ANDROID))

// OGA_IMPL_VULKAN
#elif defined(OGA_IMPL_WEBGPU)

/////////////////////////////////////////////////////
//////
// :WebGPU
//////
/////////////////////////////////////////////////////

#define OGA_OL_TARGET OL_TARGET_WGPU

#if !(OS_FLAGS & OS_FLAG_WEB)
    #error WebGPU can only be implemented when targetting web (Emscripten)
#else
    #include "graphics_webgpu.h"
#endif

// OGA_IMPL_WEBGPU
#elif defined(OGA_IMPL_D3D12)

/////////////////////////////////////////////////////
//////
// :D3D12
//////
/////////////////////////////////////////////////////

#define OGA_OL_TARGET OL_TARGET_DXIL

#if !(OS_FLAGS & OS_FLAG_WINDOWS)
    #error D3D12 can only be implemented when targetting Windows
#else
    #include "graphics_d3d12.h"
#endif

//OGA_IMPL_D3D12
#elif defined(OGA_IMPL_METAL)

/////////////////////////////////////////////////////
//////
// :Metal
//////
/////////////////////////////////////////////////////

#define OGA_OL_TARGET OL_TARGET_MSL

#if !(OS_FLAGS & OS_FLAG_APPLE)
    #error Metal can only be implemented when targetting Apple
#else
    #include "graphics_metal.h"
#endif

//OGA_IMPL_METAL
#else

/////////////////////////////////////////////////////
//////
// :Software
//////
/////////////////////////////////////////////////////

#define OGA_OL_TARGET OL_TARGET_AVX

#endif

#endif // OSTD_IMPL

#endif // OGA_GRAPHICS

