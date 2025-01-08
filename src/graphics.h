#if 0
#include "ostd.h" // For syntax highlighting.
#endif

typedef enum Oga_Result {
    OGA_OK,

    // Trying to use device features that were not available.
    // Check Oga_Device::features flags for whether or not a feature is available.
    OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES,
    // The given family index is not within the range 0 .. Oga_Device::logical_engine_family_count
    OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE,
    // The given logical_engine creation count overflows that of Oga_Logical_Engine_Family_Info::logical_engine_capacity
    OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW,
} Oga_Result;

unit_local inline string oga_get_result_name(Oga_Result r) {
    switch (r) {
        case OGA_OK: return STR("OGA_OK");
        case OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES:   return STR("OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE: return STR("OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW:  return STR("OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW");
        default: return STR("<>");
    }
    return STR("<>");
}
unit_local inline string oga_get_result_message(Oga_Result r) {
    switch (r) {
        case OGA_OK: return STR("No error");
        case OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES:
            return STR("Trying to use device features that were not available. Check Oga_Device::features flags for whether or not a feature is available.");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE:
            return STR("The given family index is not within the range 0 .. Oga_Device::logical_engine_family_count");
        case OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW:
            return STR("The given logical_engine creation count overflows that of Oga_Logical_Engine_Family_Info::logical_engine_capacity");
        default: return STR("<>");
    }
    return STR("<>");
}

typedef enum Oga_Format_Kind {
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
    OGA_FORMAT_DEPTH16_UNORM
} Oga_Format_Kind;

unit_local inline string oga_format_str(Oga_Format_Kind f) {
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
    u32 logical_engine_capacity;
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
    u64 max_shader_items_sets_per_stage;

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

    u64 max_color_attachments;

    u64 min_memory_map_alignment;

    Oga_Sample_Count_Flag supported_sample_counts_framebuffer;

    Oga_Sample_Count_Flag supported_sample_counts_fast_image_float;
    Oga_Sample_Count_Flag supported_sample_counts_large_image_float;
    Oga_Sample_Count_Flag supported_sample_counts_fast_image_int;
    Oga_Sample_Count_Flag supported_sample_counts_large_image_int;


} Oga_Device_Limits;

typedef u64 Oga_Device_Feature_Flag;

#define OGA_DEVICE_FEATURE_GRAPHICS_TIMESTAMP (1 << 0)
#define OGA_DEVICE_FEATURE_COMPUTE_TIMESTAMP (1 << 1)

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

    Oga_Device_Limits limits;

    Oga_Logical_Engine_Family_Info logical_engine_family_infos[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES];
    u32 logical_engine_family_count;

    Oga_Format_Kind depth_format;

    Oga_Memory_Heap memory_heaps[OGA_MAX_MEMORY_HEAPS_PER_DEVICE];
    u64 memory_heap_count;
    u64 total_gpu_local_memory;

    Oga_Device_Feature_Flag features;

} Oga_Device;

typedef enum Oga_Device_Pick_Flag {
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


typedef struct Oga_Context_Desc {
    // Indices match to that of Oga_Device::logical_engine_family_infos.
    // So the create logical_engines of family 0, you set the desc in logical_engine_create_descs[0].
    // Leave descs uninitialized to make no logical_engines in that family.
    Oga_Logical_Engines_Create_Desc logical_engine_create_descs[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES];
    Oga_Device_Feature_Flag enabled_features;
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
    Oga_Logical_Engine logical_engines[OGA_MAX_DEVICE_LOGICAL_ENGINES_PER_FAMILY];
    u64 logical_engine_count;
} Oga_Logical_Engine_Group;

typedef struct Oga_Context {
    void *id;
    Oga_Device device;
    Oga_Logical_Engine_Group logical_engines_by_family[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES];
} Oga_Context;

Oga_Result oga_init_context(Oga_Device target_device, Oga_Context_Desc desc, Oga_Context *context);
void oga_uninit_context(Oga_Context *context);

//////////
/// Memory

typedef void* Oga_Memory_Handle;

typedef enum Oga_Allocator_Message {
    OGA_ALLOCATOR_ALLOCATE,
    OGA_ALLOCATOR_DEALLOCATE
} Oga_Allocator_Message;

typedef Oga_Memory_Handle (*Oga_Allocator_Proc_)(
        Oga_Allocator_Message msg,
        Oga_Memory_Handle mem,
        u64 size,
        Oga_Memory_Property_Flag props,
        u64 flags
    );
typedef Oga_Allocator_Proc_ Oga_Allocator_Proc;

// Allocator for video memory
typedef struct Oga_Allocator {
    void *data;
    Oga_Allocator_Proc proc;
} Oga_Allocator;

Oga_Memory_Handle oga_allocate(Oga_Allocator a, u64 size, Oga_Memory_Property_Flag props, u64 flags);
void oga_deallocate(Oga_Allocator a, Oga_Memory_Handle mem);

Oga_Memory_Handle oga_default_allocator(Oga_Allocator_Message msg, Oga_Memory_Handle mem, u64 size, Oga_Memory_Property_Flag props, u64 flags);

typedef enum Oga_Memory_View_Kind {
    OGA_MEMORY_VIEW_KIND_SHADER_ITEM_DESCRIPTOR,
    OGA_MEMORY_VIEW_KIND_VERTEX_LIST,
    OGA_MEMORY_VIEW_KIND_INDEX_LIST,
    OGA_MEMORY_VIEW_KIND_COPY_TASK,
} Oga_Memory_View_Kind;

typedef enum Oga_Memory_View_Flag {
    OGA_MEMORY_VIEW_FLAG_COPY_DST = 1 << 0,
    OGA_MEMORY_VIEW_FLAG_COPY_SRC = 1 << 1,
} Oga_Memory_View_Flag;

typedef enum Oga_Shader_Item_Descriptor_Kind {
    OGA_SHADER_ITEM_DESCRIPTOR_KIND_DATA_BLOCK,
    OGA_SHADER_ITEM_DESCRIPTOR_KIND_IMAGE1D,
    OGA_SHADER_ITEM_DESCRIPTOR_KIND_IMAGE2D,
    OGA_SHADER_ITEM_DESCRIPTOR_KIND_IMAGE3D,
} Oga_Shader_Item_Descriptor_Kind;

typedef enum Oga_Shader_Item_Descriptor_Flag {
    OGA_SHADER_ITEM_DESCRIPTOR_FLAG_READ,
    OGA_SHADER_ITEM_DESCRIPTOR_FLAG_WRITE,

    // When a shader item descriptor is flagged with large or write, it can have larger
    // storage (or be written to) at the cost of memory access performance.
    // see limits max_fast_access_xxxxx_size
    OGA_SHADER_ITEM_DESCRIPTOR_FLAG_LARGE,
} Oga_Shader_Item_Descriptor_Flag;

typedef struct Oga_Shader_Item_Descriptor_Desc {
    Oga_Shader_Item_Descriptor_Kind kind;
    Oga_Shader_Item_Descriptor_Flag flags;

} Oga_Shader_Item_Descriptor_Desc;

typedef struct Oga_Vertex_List_Desc  {
    int _;
} Oga_Vertex_List_Desc;

typedef struct Oga_Index_List_Desc  {
    int _;

} Oga_Index_List_Desc;

typedef struct Oga_Copy_Task_Desc  {
    int _;

} Oga_Copy_Task_Desc;

typedef struct Oga_Memory_View_Desc {
    Oga_Memory_View_Kind kind;
    Oga_Memory_View_Flag flags;

    Oga_Memory_Handle memory;

    union {
        Oga_Shader_Item_Descriptor_Desc shader_item_descriptor;
        Oga_Vertex_List_Desc vertex_list;
        Oga_Index_List_Desc index_list;
        Oga_Copy_Task_Desc copy_task;
    } UNION;
} Oga_Memory_View_Desc;

//Oga_Result oga_make_memory_view(Oga_Context c, Oga_Memory_View_Desc desc);


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

inline string oga_format_str(Oga_Format_Kind f);

#ifdef OGA_IMPL_VULKAN

/////////////////////////////////////////////////////
//////
// :Vulkan
//////
/////////////////////////////////////////////////////

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

#endif

#endif // OSTD_IMPL

