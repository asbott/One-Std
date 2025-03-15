#if !defined(OGA_GRAPHICS) && !defined(OSTD_HEADLESS)
#define OGA_GRAPHICS


#ifndef _BASE_H
#include "base.h"
#endif // _BASE_H
#ifndef _STRING_H
#include "string.h"
#endif // _STRING_H
#ifndef _MEMORY_H
#include "memory.h"
#endif // _MEMORY_H
#ifndef _SYSTEM_1_H
#include "system1.h"
#endif // _SYSTEM_1_H
#ifndef _MATH_H
#include "math.h"
#endif // _MATH_H
#ifndef _PRINT_H
#include "print.h"
#endif // _PRINT_H

// todo(charlie) make a stack of non-OK results which can be popped
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
    
    OGA_ALLOCATE_MEMORY_ERROR_INVALID_PROPERTIES_AND_USAGE_COMBINATION,
    OGA_ERROR_INVALID_INPUT_RATE_ENUM,
    
    OGA_MEMORY_OFFSET_ERROR_UNDERFLOW,
    OGA_MEMORY_OFFSET_ERROR_OVERFLOW,
    
    OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM,
    OGA_CMD_DRAW_ERROR_VERTEX_LIST_BINDING_COUNT_ZERO,
    OGA_CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING,
    OGA_CMD_DRAW_ERROR_VERTEX_LIST_OFFSET_OUT_OF_RANGE,
    OGA_CMD_DRAW_ERROR_MISSING_INDEX_LIST,
    OGA_CMD_DRAW_ERROR_INVALID_INDEX_TYPE_ENUM,
    
    OGA_INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT,
    OGA_INIT_INDEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT,
    
    OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM,
    OGA_INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED,
    OGA_INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT,
    OGA_INIT_OPTIMAL_COPY_VIEW_ERROR_INVALID_FLAGS,
    
    OGA_INIT_RENDER_PASS_ERROR_INVALID_PROGRAM_BINDING_KIND_ENUM,
    OGA_INIT_BINDING_LIST_LAYOUT_ERROR_MISSING_STAGE_FLAGS,
    
    OGA_PUSH_BINDING_LIST_ERROR_LAYOUT_COUNT_MISMATCH,
    
} Oga_Result;

#define OGA_LOG_VERBOSE (1 << 16)

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
        case OGA_ALLOCATE_MEMORY_ERROR_INVALID_PROPERTIES_AND_USAGE_COMBINATION: return STR("OGA_ALLOCATE_MEMORY_ERROR_INVALID_PROPERTIES_AND_USAGE_COMBINATION");
        case OGA_ERROR_INVALID_INPUT_RATE_ENUM:                         return STR("OGA_ERROR_INVALID_INPUT_RATE_ENUM");
        case OGA_MEMORY_OFFSET_ERROR_UNDERFLOW:                         return STR("OGA_MEMORY_OFFSET_ERROR_UNDERFLOW");
        case OGA_MEMORY_OFFSET_ERROR_OVERFLOW:                          return STR("OGA_MEMORY_OFFSET_ERROR_OVERFLOW");
        case OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM:                 return STR("OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM");
        case OGA_CMD_DRAW_ERROR_VERTEX_LIST_BINDING_COUNT_ZERO:         return STR("OGA_CMD_DRAW_ERROR_VERTEX_LIST_BINDING_COUNT_ZERO");
        case OGA_CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING:            return STR("OGA_CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING");
        case OGA_CMD_DRAW_ERROR_VERTEX_LIST_OFFSET_OUT_OF_RANGE:        return STR("OGA_CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING");
        case OGA_CMD_DRAW_ERROR_MISSING_INDEX_LIST:                     return STR("OGA_CMD_DRAW_ERROR_MISSING_INDEX_LIST");
        case OGA_CMD_DRAW_ERROR_INVALID_INDEX_TYPE_ENUM:                return STR("OGA_CMD_DRAW_ERROR_INVALID_INDEX_TYPE_ENUM");
        case OGA_INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT:      return STR("OGA_INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT");
        case OGA_INIT_INDEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT:       return STR("OGA_INIT_INDEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT");
        case OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM:         return STR("OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM");
        case OGA_INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED:            return STR("OGA_INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED");
        case OGA_INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT:      return STR("OGA_INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT");
        case OGA_INIT_OPTIMAL_COPY_VIEW_ERROR_INVALID_FLAGS:       return STR("OGA_INIT_OPTIMAL_COPY_VIEW_ERROR_INVALID_FLAGS");
        case OGA_INIT_RENDER_PASS_ERROR_INVALID_PROGRAM_BINDING_KIND_ENUM: return STR("OGA_INIT_RENDER_PASS_ERROR_INVALID_PROGRAM_BINDING_KIND_ENUM");
        case OGA_INIT_BINDING_LIST_LAYOUT_ERROR_MISSING_STAGE_FLAGS:    return STR("OGA_INIT_BINDING_LIST_LAYOUT_ERROR_MISSING_STAGE_FLAGS");
        case OGA_PUSH_BINDING_LIST_ERROR_LAYOUT_COUNT_MISMATCH:         return STR("OGA_PUSH_BINDING_LIST_ERROR_LAYOUT_COUNT_MISMATCH");
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
            return STR("Swapchain has no ready imagess yet");
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
            return STR("An allocation with the state_allocator passed in Oga_Context creation returned 0 upon allocation.");
        case OGA_ERROR_OUT_OF_DEVICE_MEMORY:
            return STR("Out of device memory");
        case OGA_ERROR_OUTDATED:
            return STR("A swapchain has become out of date and can no longer present");
        case OGA_ERROR_SURFACE_LOST:
            return STR("A surface was lost; closed or corrupt");
        case OGA_ALLOCATE_MEMORY_ERROR_INVALID_PROPERTIES_AND_USAGE_COMBINATION:
            return STR("The given combination of memory property flags and usage flags did not match to an available heap & memory type. Please see Oga_Device::memory_heaps for heap availability and support.");
        case OGA_ERROR_INVALID_INPUT_RATE_ENUM:
            return STR("The given Oga_Vertex_Attribute_Type enum for Oga_Vertex_List_Attribute_Desc::type was not a valid enum value. It muse be one of: OGA_VERTEX_INPUT_RATE_VERTEX or OGA_VERTEX_INPUT_RATE_INSTANCE.");
        case OGA_MEMORY_OFFSET_ERROR_UNDERFLOW:
            return STR("The resulting pointer from oga_memory_offset() underflows the allocated memory block");
        case OGA_MEMORY_OFFSET_ERROR_OVERFLOW:
            return STR("The resulting pointer from oga_memory_offset() overflows the allocated memory block");
        case OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM:
            return STR("The value in Oga_Draw_Desc::draw_type was of an invalid value. See enum Oga_Draw_Type for valid values.");
        case OGA_CMD_DRAW_ERROR_VERTEX_LIST_BINDING_COUNT_ZERO:
            return STR("A vertex list draw command was submitted but Oga_Draw_Desc::vertex_list_binding_count is 0.");
        case OGA_CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING:
            return STR("A binding slot within the range 0 to Oga_Draw_Desc::vertex_list_binding_count was set to 0 in Oga_Draw_Desc::vertex_list_bindings.");
        case OGA_CMD_DRAW_ERROR_VERTEX_LIST_OFFSET_OUT_OF_RANGE:
            return STR("A vertex list binding offset in Oga_Draw_Desc::vertex_list_offsets was out of range");
        case OGA_CMD_DRAW_ERROR_MISSING_INDEX_LIST:
            return STR("An indexed draw command was submitted but Oga_Draw_Desc::index_list was set to 0.");
        case OGA_CMD_DRAW_ERROR_INVALID_INDEX_TYPE_ENUM:
            return STR("An indexed draw command was submitted Oga_Draw_Desc::index_type was of an invalid enum value. Valid values are: OGA_INDEX_U32 or OGA_INDEX_U16");
        case OGA_INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT:
            return STR("Tried creating a Vertex List View, pointing to memory from a heap which lacks the support flag OGA_MEMORY_USAGE_VERTEX_LIST. Make sure you include the usage flag OGA_MEMORY_USAGE_VERTEX_LIST in oga_allocate_memory() to make sure you get memory from a heap with the required support flags.");
        case OGA_INIT_INDEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT:
            return STR("Tried creating a Vertex List View, pointing to memory from a heap which lacks the support flag OGA_MEMORY_USAGE_INDEX_LIST. Make sure you include the usage flag OGA_MEMORY_USAGE_INDEX_LIST in oga_allocate_memory() to make sure you get memory from a heap with the required support flags.");
        case OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM:
            return STR("Oga_Image_View_Desc::dimensions was an invalid value. It must be one of: OGA_1D, OGA_2D or OGA_3D");
        case OGA_INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED:
            return STR("Oga_Image_View_Desc::memory_pointer offset must be aligned to Oga_Device::limits.image_memory_granularity, but it was not.");
        case OGA_INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT:
            return STR("Oga_Image_View_Desc::memory_pointer allocation size is not enough to meet the memory requirement for the image. To get the memory requirement for an image kind and size, use oga_get_image_memory_requirement()");
        case OGA_INIT_OPTIMAL_COPY_VIEW_ERROR_INVALID_FLAGS:
            return STR("Oga_Optimal_Copy_View_Desc::flags does not convey any intent.");
        case OGA_INIT_RENDER_PASS_ERROR_INVALID_PROGRAM_BINDING_KIND_ENUM:
            return STR("A program binding had an invalid enum value for Oga_Program_Binding_Desc::kind. See Oga_Binding_Kind for valid enum values.");
        case OGA_INIT_BINDING_LIST_LAYOUT_ERROR_MISSING_STAGE_FLAGS:
            return STR("A Oga_Program_Binding_Desc::stage_flags was 0. It needs to contain at least one valid stage flag from Oga_Program_Stage_Flag");
        case OGA_PUSH_BINDING_LIST_ERROR_LAYOUT_COUNT_MISMATCH:
            return STR("Oga_Binding_List_Desc::binding_count is greater than what was passed into oga_init_binding_list_layout Oga_Binding_List_Layout_Desc::binding_count. Cannot allocate a binding list with more bindings than was specified for the layout.");
        default: return STR("<>");
    }
    return STR("<>");
}

typedef enum Oga_Format {
    OGA_FORMAT_R4G4_UNORM_PACK8,
    OGA_FORMAT_R4G4B4A4_UNORM_PACK16,
    OGA_FORMAT_B4G4R4A4_UNORM_PACK16,
    OGA_FORMAT_R5G6B5_UNORM_PACK16,
    OGA_FORMAT_B5G6R5_UNORM_PACK16,
    OGA_FORMAT_R5G5B5A1_UNORM_PACK16,
    OGA_FORMAT_A1R5G5B5_UNORM_PACK16,

    OGA_FORMAT_R8_UNORM,
    OGA_FORMAT_R8_SNORM,
    OGA_FORMAT_R8_UINT,
    OGA_FORMAT_R8_SINT,
    OGA_FORMAT_R8_SRGB,

    OGA_FORMAT_R8G8_UNORM,
    OGA_FORMAT_R8G8_SNORM,
    OGA_FORMAT_R8G8_UINT,
    OGA_FORMAT_R8G8_SINT,
    OGA_FORMAT_R8G8_SRGB,

    OGA_FORMAT_R8G8B8_UNORM,
    OGA_FORMAT_R8G8B8_SNORM,
    OGA_FORMAT_R8G8B8_UINT,
    OGA_FORMAT_R8G8B8_SINT,
    OGA_FORMAT_R8G8B8_SRGB,

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

    OGA_FORMAT_R16_UNORM,
    OGA_FORMAT_R16_SNORM,
    OGA_FORMAT_R16_UINT,
    OGA_FORMAT_R16_SINT,
    OGA_FORMAT_R16_SFLOAT,

    OGA_FORMAT_R16G16_UNORM,
    OGA_FORMAT_R16G16_SNORM,
    OGA_FORMAT_R16G16_UINT,
    OGA_FORMAT_R16G16_SINT,
    OGA_FORMAT_R16G16_SFLOAT,

    OGA_FORMAT_R16G16B16A16_UNORM,
    OGA_FORMAT_R16G16B16A16_SNORM,
    OGA_FORMAT_R16G16B16A16_UINT,
    OGA_FORMAT_R16G16B16A16_SINT,
    OGA_FORMAT_R16G16B16A16_SFLOAT,

    OGA_FORMAT_R32_SFLOAT,
    OGA_FORMAT_R32_UINT,
    OGA_FORMAT_R32_SINT,

    OGA_FORMAT_R32G32_SFLOAT,
    OGA_FORMAT_R32G32_UINT,
    OGA_FORMAT_R32G32_SINT,

    OGA_FORMAT_R32G32B32_SFLOAT,
    OGA_FORMAT_R32G32B32_UINT,
    OGA_FORMAT_R32G32B32_SINT,

    OGA_FORMAT_R32G32B32A32_SFLOAT,
    OGA_FORMAT_R32G32B32A32_UINT,
    OGA_FORMAT_R32G32B32A32_SINT,
    
    OGA_FORMAT_BC1_RGB_UNORM_BLOCK,
    OGA_FORMAT_BC1_RGB_SRGB_BLOCK,
    OGA_FORMAT_BC1_RGBA_UNORM_BLOCK,
    OGA_FORMAT_BC1_RGBA_SRGB_BLOCK,
    OGA_FORMAT_BC2_UNORM_BLOCK,
    OGA_FORMAT_BC2_SRGB_BLOCK,
    OGA_FORMAT_BC3_UNORM_BLOCK,
    OGA_FORMAT_BC3_SRGB_BLOCK,
    OGA_FORMAT_BC4_UNORM_BLOCK,
    OGA_FORMAT_BC4_SNORM_BLOCK,
    OGA_FORMAT_BC5_UNORM_BLOCK,
    OGA_FORMAT_BC5_SNORM_BLOCK,
    OGA_FORMAT_BC6H_UFLOAT_BLOCK,
    OGA_FORMAT_BC6H_SFLOAT_BLOCK,
    OGA_FORMAT_BC7_UNORM_BLOCK,
    OGA_FORMAT_BC7_SRGB_BLOCK,

    OGA_FORMAT_ENUM_MAX,
} Oga_Format;

unit_local inline string oga_format_str(Oga_Format f) {
    switch (f) {
        case OGA_FORMAT_R4G4_UNORM_PACK8:              return RSTR(R4G4_UNORM_PACK8);
        case OGA_FORMAT_R4G4B4A4_UNORM_PACK16:          return RSTR(R4G4B4A4_UNORM_PACK16);
        case OGA_FORMAT_B4G4R4A4_UNORM_PACK16:          return RSTR(B4G4R4A4_UNORM_PACK16);
        case OGA_FORMAT_R5G6B5_UNORM_PACK16:            return RSTR(R5G6B5_UNORM_PACK16);
        case OGA_FORMAT_B5G6R5_UNORM_PACK16:            return RSTR(B5G6R5_UNORM_PACK16);
        case OGA_FORMAT_R5G5B5A1_UNORM_PACK16:          return RSTR(R5G5B5A1_UNORM_PACK16);
        case OGA_FORMAT_A1R5G5B5_UNORM_PACK16:          return RSTR(A1R5G5B5_UNORM_PACK16);

        case OGA_FORMAT_R8_UNORM:                       return RSTR(R8_UNORM);
        case OGA_FORMAT_R8_SNORM:                       return RSTR(R8_SNORM);
        case OGA_FORMAT_R8_UINT:                        return RSTR(R8_UINT);
        case OGA_FORMAT_R8_SINT:                        return RSTR(R8_SINT);
        case OGA_FORMAT_R8_SRGB:                        return RSTR(R8_SRGB);

        case OGA_FORMAT_R8G8_UNORM:                     return RSTR(R8G8_UNORM);
        case OGA_FORMAT_R8G8_SNORM:                     return RSTR(R8G8_SNORM);
        case OGA_FORMAT_R8G8_UINT:                      return RSTR(R8G8_UINT);
        case OGA_FORMAT_R8G8_SINT:                      return RSTR(R8G8_SINT);
        case OGA_FORMAT_R8G8_SRGB:                      return RSTR(R8G8_SRGB);

        case OGA_FORMAT_R8G8B8_UNORM:                   return RSTR(R8G8B8_UNORM);
        case OGA_FORMAT_R8G8B8_SNORM:                   return RSTR(R8G8B8_SNORM);
        case OGA_FORMAT_R8G8B8_UINT:                    return RSTR(R8G8B8_UINT);
        case OGA_FORMAT_R8G8B8_SINT:                    return RSTR(R8G8B8_SINT);
        case OGA_FORMAT_R8G8B8_SRGB:                    return RSTR(R8G8B8_SRGB);

        case OGA_FORMAT_R8G8B8A8_UNORM:                 return RSTR(R8G8B8A8_UNORM);
        case OGA_FORMAT_R8G8B8A8_SNORM:                 return RSTR(R8G8B8A8_SNORM);
        case OGA_FORMAT_R8G8B8A8_UINT:                  return RSTR(R8G8B8A8_UINT);
        case OGA_FORMAT_R8G8B8A8_SINT:                  return RSTR(R8G8B8A8_SINT);
        case OGA_FORMAT_R8G8B8A8_SRGB:                  return RSTR(R8G8B8A8_SRGB);

        case OGA_FORMAT_B8G8R8A8_UNORM:                 return RSTR(B8G8R8A8_UNORM);
        case OGA_FORMAT_B8G8R8A8_SNORM:                 return RSTR(B8G8R8A8_SNORM);
        case OGA_FORMAT_B8G8R8A8_UINT:                  return RSTR(B8G8R8A8_UINT);
        case OGA_FORMAT_B8G8R8A8_SINT:                  return RSTR(B8G8R8A8_SINT);
        case OGA_FORMAT_B8G8R8A8_SRGB:                  return RSTR(B8G8R8A8_SRGB);

        case OGA_FORMAT_R16_UNORM:                      return RSTR(R16_UNORM);
        case OGA_FORMAT_R16_SNORM:                      return RSTR(R16_SNORM);
        case OGA_FORMAT_R16_UINT:                       return RSTR(R16_UINT);
        case OGA_FORMAT_R16_SINT:                       return RSTR(R16_SINT);
        case OGA_FORMAT_R16_SFLOAT:                     return RSTR(R16_SFLOAT);

        case OGA_FORMAT_R16G16_UNORM:                   return RSTR(R16G16_UNORM);
        case OGA_FORMAT_R16G16_SNORM:                   return RSTR(R16G16_SNORM);
        case OGA_FORMAT_R16G16_UINT:                    return RSTR(R16G16_UINT);
        case OGA_FORMAT_R16G16_SINT:                    return RSTR(R16G16_SINT);
        case OGA_FORMAT_R16G16_SFLOAT:                  return RSTR(R16G16_SFLOAT);

        case OGA_FORMAT_R16G16B16A16_UNORM:             return RSTR(R16G16B16A16_UNORM);
        case OGA_FORMAT_R16G16B16A16_SNORM:             return RSTR(R16G16B16A16_SNORM);
        case OGA_FORMAT_R16G16B16A16_UINT:              return RSTR(R16G16B16A16_UINT);
        case OGA_FORMAT_R16G16B16A16_SINT:              return RSTR(R16G16B16A16_SINT);
        case OGA_FORMAT_R16G16B16A16_SFLOAT:            return RSTR(R16G16B16A16_SFLOAT);

        case OGA_FORMAT_R32_SFLOAT:                     return RSTR(R32_SFLOAT);
        case OGA_FORMAT_R32_UINT:                       return RSTR(R32_UINT);
        case OGA_FORMAT_R32_SINT:                       return RSTR(R32_SINT);

        case OGA_FORMAT_R32G32_SFLOAT:                  return RSTR(R32G32_SFLOAT);
        case OGA_FORMAT_R32G32_UINT:                    return RSTR(R32G32_UINT);
        case OGA_FORMAT_R32G32_SINT:                    return RSTR(R32G32_SINT);

        case OGA_FORMAT_R32G32B32_SFLOAT:               return RSTR(R32G32B32_SFLOAT);
        case OGA_FORMAT_R32G32B32_UINT:                 return RSTR(R32G32B32_UINT);
        case OGA_FORMAT_R32G32B32_SINT:                 return RSTR(R32G32B32_SINT);

        case OGA_FORMAT_R32G32B32A32_SFLOAT:            return RSTR(R32G32B32A32_SFLOAT);
        case OGA_FORMAT_R32G32B32A32_UINT:              return RSTR(R32G32B32A32_UINT);
        case OGA_FORMAT_R32G32B32A32_SINT:              return RSTR(R32G32B32A32_SINT);

        case OGA_FORMAT_BC1_RGB_UNORM_BLOCK:            return RSTR(BC1_RGB_UNORM_BLOCK);
        case OGA_FORMAT_BC1_RGB_SRGB_BLOCK:             return RSTR(BC1_RGB_SRGB_BLOCK);
        case OGA_FORMAT_BC1_RGBA_UNORM_BLOCK:           return RSTR(BC1_RGBA_UNORM_BLOCK);
        case OGA_FORMAT_BC1_RGBA_SRGB_BLOCK:            return RSTR(BC1_RGBA_SRGB_BLOCK);
        case OGA_FORMAT_BC2_UNORM_BLOCK:                return RSTR(BC2_UNORM_BLOCK);
        case OGA_FORMAT_BC2_SRGB_BLOCK:                 return RSTR(BC2_SRGB_BLOCK);
        case OGA_FORMAT_BC3_UNORM_BLOCK:                return RSTR(BC3_UNORM_BLOCK);
        case OGA_FORMAT_BC3_SRGB_BLOCK:                 return RSTR(BC3_SRGB_BLOCK);
        case OGA_FORMAT_BC4_UNORM_BLOCK:                return RSTR(BC4_UNORM_BLOCK);
        case OGA_FORMAT_BC4_SNORM_BLOCK:                return RSTR(BC4_SNORM_BLOCK);
        case OGA_FORMAT_BC5_UNORM_BLOCK:                return RSTR(BC5_UNORM_BLOCK);
        case OGA_FORMAT_BC5_SNORM_BLOCK:                return RSTR(BC5_SNORM_BLOCK);
        case OGA_FORMAT_BC6H_UFLOAT_BLOCK:              return RSTR(BC6H_UFLOAT_BLOCK);
        case OGA_FORMAT_BC6H_SFLOAT_BLOCK:              return RSTR(BC6H_SFLOAT_BLOCK);
        case OGA_FORMAT_BC7_UNORM_BLOCK:                return RSTR(BC7_UNORM_BLOCK);
        case OGA_FORMAT_BC7_SRGB_BLOCK:                 return RSTR(BC7_SRGB_BLOCK);

        case OGA_FORMAT_ENUM_MAX:
        default:
            return RSTR(<>);
    }
    return RSTR(<>);
}

typedef enum Oga_Memory_Property_Flag_ {
    // Memory is near GPU and accessed with high performance
    OGA_MEMORY_PROPERTY_GPU_LOCAL  = 0x00000001,
    // Memory can be mapped
    OGA_MEMORY_PROPERTY_GPU_TO_CPU_MAPPABLE  = 0x00000002,
    // Memory is directly reflected on CPU. Mapping is not needed to access memory
    OGA_MEMORY_PROPERTY_GPU_TO_CPU_REFLECTED = 0x00000004,
    // Cached memory is accessed quicker, but does not instantly reflect GPU writes
    OGA_MEMORY_PROPERTY_GPU_TO_CPU_CACHED   = 0x00000008,
} Oga_Memory_Property_Flag_;
typedef u64 Oga_Memory_Property_Flag;

typedef enum Oga_Memory_Usage_ {
    OGA_MEMORY_USAGE_NONE = 0,
    OGA_MEMORY_USAGE_VERTEX_LIST = 1 << 2,
    OGA_MEMORY_USAGE_INDEX_LIST = 1 << 3,
    // todo(charlie) rename
    OGA_MEMORY_USAGE_FAST_READONLY_DATA_BLOCK = 1 << 4,
    OGA_MEMORY_USAGE_LARGE_READWRITE_DATA_BLOCK = 1 << 5,
    OGA_MEMORY_USAGE_COPY_DST = 1 << 6,
    OGA_MEMORY_USAGE_COPY_SRC = 1 << 7,
    OGA_MEMORY_USAGE_IMAGE_1D = 1 << 8,
    OGA_MEMORY_USAGE_IMAGE_2D = 1 << 9,
    OGA_MEMORY_USAGE_IMAGE_3D = 1 << 10,
    OGA_MEMORY_USAGE_FBUFFER_1D = 1 << 8,
    OGA_MEMORY_USAGE_FBUFFER_2D = 1 << 9,
    OGA_MEMORY_USAGE_FBUFFER_3D = 1 << 10,
} Oga_Memory_Usage_;
typedef u64 Oga_Memory_Usage;

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
    Oga_Memory_Usage supported_usage_flags;
} Oga_Memory_Heap;

typedef enum Oga_Device_Kind {
    OGA_DEVICE_DISCRETE,
    OGA_DEVICE_INTEGRATED,
    OGA_DEVICE_CPU, // Software implementations
    OGA_DEVICE_OTHER,
} Oga_Device_Kind;

// todo(charlie) populate this with an exhaustive list.
typedef struct Oga_Device_Limits {
    u64 max_program_view_sets_per_stage;

    u64 max_fast_data_blocks_per_stage;
    u64 max_large_data_blocks_per_stage;
    u64 max_images_per_stage;
    u64 max_fbuffers_per_stage;
    u64 max_samplers_per_stage;

    u64 max_fast_data_blocks_per_layout;
    u64 max_large_data_blocks_per_layout;
    u64 max_images_per_layout;
    u64 max_fbuffers_per_layout;
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

    Oga_Sample_Count_Flag supported_sample_counts_image_float;
    Oga_Sample_Count_Flag supported_sample_counts_fbuffer_float;
    Oga_Sample_Count_Flag supported_sample_counts_image_int;
    Oga_Sample_Count_Flag supported_sample_counts_fbuffer_int;
    
    u64 memory_granularity;
    u64 image_memory_granularity;
    u64 fbuffer_memory_granularity;

} Oga_Device_Limits;

typedef u64 Oga_Device_Feature_Flag;

#define OGA_DEVICE_FEATURE_GRAPHICS_TIMESTAMP (1 << 0)
#define OGA_DEVICE_FEATURE_COMPUTE_TIMESTAMP  (1 << 1)
#define OGA_DEVICE_FEATURE_PRESENT_MAILBOX    (1 << 2)
//#define OGA_DEVICE_FEATURE_DEPTH_CLAMP    (1 << 3)

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

    u64 vendor_id;
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

OSTD_LIB u64 oga_query_devices(Oga_Device *buffer, u64 buffer_count);
OSTD_LIB Oga_Device *oga_get_devices(Allocator a, u64 *count);

typedef struct Oga_Pick_Device_Result {
    bool passed;
    Oga_Device device;
    Oga_Device_Pick_Flag failed_pick_flags;
    Oga_Device_Feature_Flag failed_required_features;
    Oga_Device_Feature_Flag failed_preferred_features;
} Oga_Pick_Device_Result;
// todo(charlie) add consideration for heap properties and usage flags
OSTD_LIB Oga_Pick_Device_Result oga_pick_device(Oga_Device_Pick_Flag pick_flags, Oga_Device_Feature_Flag required_features, Oga_Device_Feature_Flag preferred_features);

//////////
/// Oga Context


typedef struct Oga_Logical_Engines_Create_Desc {
    u32 count;
    float32 priorities[OGA_MAX_DEVICE_LOGICAL_ENGINES_PER_FAMILY]; // normalized 0.0-1.0.
} Oga_Logical_Engines_Create_Desc;

// Default allocator of non is specified in Oga_Context_Desc::state_allocator
OSTD_LIB void* oga_state_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags);


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

OSTD_LIB Oga_Result oga_init_context(Oga_Device target_device, Oga_Context_Desc desc, Oga_Context **context);
OSTD_LIB void oga_uninit_context(Oga_Context *context);

OSTD_LIB void oga_wait_engine_idle(Oga_Logical_Engine engine);
OSTD_LIB void oga_wait_context_idle(Oga_Context *context);

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
    Oga_Present_Mode present_mode;
    u64 graphics_engine_family_index; // Swapchain needs a graphics engine
    
} Oga_Swapchain_Desc;



#define MAX_SWAPCHAIN_IMAGES 16

struct Oga_Render_Image_View;
typedef struct Oga_Swapchain {
    void *id;
    Oga_Context *context;
    struct Oga_Render_Image_View *images[MAX_SWAPCHAIN_IMAGES];
    u64 current_image_index;
    u64 image_count;
    Oga_Format image_format;
} Oga_Swapchain;

OSTD_LIB bool get_preferred_swapchain_format(Oga_Context *context, Oga_Format *wanted_formats, u64 count, Oga_Format *format);

OSTD_LIB Oga_Result oga_init_swapchain(Oga_Context *context, Oga_Swapchain_Desc desc, Oga_Swapchain **swapchain);
OSTD_LIB void oga_uninit_swapchain(Oga_Swapchain *swapchain);

struct Oga_Gpu_Latch;
struct Oga_Cpu_Latch;
OSTD_LIB Oga_Result oga_get_next_swapchain_image(Oga_Swapchain *swapchain, u64 timeout, struct Oga_Gpu_Latch *signal_gpu_latch, struct Oga_Cpu_Latch *signal_cpu_latch, u64 *image_index); 

typedef struct Oga_Present_Desc {
    Oga_Logical_Engine engine;
    u64 wait_gpu_latch_count;
    struct Oga_Gpu_Latch **wait_gpu_latches;
    u64 image_index;
} Oga_Present_Desc;
OSTD_LIB Oga_Result oga_submit_present(Oga_Swapchain *swapchain, Oga_Present_Desc desc);

//////////
/// GPU Programs

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

OSTD_LIB Oga_Result oga_init_program(Oga_Context *context, Oga_Program_Desc desc, Oga_Program **program);
OSTD_LIB void oga_uninit_program(Oga_Program *program);

//////////
/// Render Passes

typedef enum Oga_Program_Stage_Flag_ {
    OGA_PROGRAM_STAGE_VERTEX = 1 << 1,
    OGA_PROGRAM_STAGE_FRAGMENT = 1 << 2,
    OGA_PROGRAM_STAGE_COMPUTE = 1 << 3,
} Oga_Program_Stage_Flag_;
typedef u64 Oga_Program_Stage_Flag;

typedef enum Oga_Sampling_Filter {
    OGA_SAMPLE_FILTER_LINEAR,
    OGA_SAMPLE_FILTER_NEAREST,
} Oga_Sampling_Filter;
typedef enum Oga_Sampling_Address_Mode {
    OGA_SAMPLE_ADDRESS_MODE_REPEAT,
    OGA_SAMPLE_ADDRESS_MODE_MIRRORED_REPEAT,
    OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_EDGE,
    OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_BORDER,
} Oga_Sampling_Address_Mode;
typedef struct Oga_Sample_Mode_Desc {
    Oga_Sampling_Filter magnification_filter;
    Oga_Sampling_Filter minification_filter;
    Oga_Sampling_Address_Mode address_mode_u;
    Oga_Sampling_Address_Mode address_mode_v;
    Oga_Sampling_Address_Mode address_mode_w;
    float max_anisotropy;
} Oga_Sample_Mode_Desc;

typedef enum Oga_Binding_Kind {
    OGA_BINDING_IMAGE,
    OGA_BINDING_SAMPLE_MODE,
    OGA_BINDING_BLOCK,
    OGA_BINDING_FBUFFER,
    
    OGA_BINDING_ENUM_MAX
} Oga_Binding_Kind;
typedef struct Oga_Binding_Layout_Entry_Desc {
    Oga_Binding_Kind kind;
    u64 binding_slot;
    u64 binding_count; // Number of elements in this binding. If > 1, the program declaration should be an array
    Oga_Program_Stage_Flag stage_flags;
} Oga_Binding_Layout_Entry_Desc;
typedef struct Oga_Binding_List_Layout_Desc {
    Oga_Binding_Layout_Entry_Desc *bindings;
    u64 binding_count;
    u64 binding_list_count;
} Oga_Binding_List_Layout_Desc;

typedef struct Oga_Binding_List_Layout {
    void *id;
    Oga_Context *context;
    Oga_Binding_Layout_Entry_Desc *bindings;
    u64 binding_count;
    u64 binding_list_count;
    u64 allocated_lists_count;
} Oga_Binding_List_Layout;

OSTD_LIB Oga_Result oga_init_binding_list_layout(Oga_Context *context, Oga_Binding_List_Layout_Desc desc, Oga_Binding_List_Layout **layout);
OSTD_LIB void oga_uninit_binding_list_layout(Oga_Binding_List_Layout *layout);

struct Oga_Image_View;
struct Oga_Block_View;
typedef struct Oga_Binding_Desc {
    Oga_Binding_Kind kind;
    u64 binding_slot;
    u64 array_index;
    u64 count;
    
    // OGA_BINDING_IMAGE
    struct Oga_Image_View **images;
    
    // OGA_BINDING_SAMPLE_MODE
    Oga_Sample_Mode_Desc *sample_modes;
    
    // OGA_BINDING_BLOCK
    struct Oga_Block_View **blocks;
    
    // OGA_BINDING_FBUFFER
    struct Oga_FBuffer_View **fbuffers;
    
} Oga_Binding_Desc;
typedef struct Oga_Binding_List_Desc {
    Oga_Binding_Desc *bindings;
    u64 binding_count;
} Oga_Binding_List_Desc;

typedef struct Oga_Binding_List {
    void *id;
    Oga_Context *context;
    Oga_Binding_List_Layout *layout;
} Oga_Binding_List;

OSTD_LIB Oga_Result oga_push_binding_list(Oga_Binding_List_Layout *layout, Oga_Binding_List_Desc desc, Oga_Binding_List **list);

// I looked through various devices and they all report these numbers
// Including RTX 5090 as well as GT 710 (vulkan)
#define OGA_MAX_VERTEX_BINDING_COUNT 32
#define OGA_MAX_VERTEX_ATTRIBUTE_COUNT 32
#define MAX_VERTEX_ATTRIBUTE_OFFSET 2047
#define MAX_VERTEX_BINDING_OFFSET 2048

typedef enum Oga_Vertex_List_Input_Rate {
    OGA_VERTEX_INPUT_RATE_VERTEX,
    OGA_VERTEX_INPUT_RATE_INSTANCE,
} Oga_Vertex_List_Input_Rate;

typedef enum Oga_Vertex_Attribute_Type {
    OGA_VERTEX_ATTRIBUTE_TYPE_F32,
    OGA_VERTEX_ATTRIBUTE_TYPE_F32V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_F32V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_F32V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_S32,
    OGA_VERTEX_ATTRIBUTE_TYPE_S32V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_S32V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_S32V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_S16,
    OGA_VERTEX_ATTRIBUTE_TYPE_S16V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_S16V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_S16V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_S8,
    OGA_VERTEX_ATTRIBUTE_TYPE_S8V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_S8V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_S8V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_U32,
    OGA_VERTEX_ATTRIBUTE_TYPE_U32V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_U32V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_U32V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_U16,
    OGA_VERTEX_ATTRIBUTE_TYPE_U16V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_U16V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_U16V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V2,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V3,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V4,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8_NORMALIZED,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V2_NORMALIZED,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V3_NORMALIZED,
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V4_NORMALIZED,
} Oga_Vertex_Attribute_Type;

/*
    We often only need one vertex list in one binding slot:
    
    Oga_Vertex_List_Layout_Desc desc = (Oga_Vertex_List_Layout_Desc) {0};
    desc.bindings[0].stride = sizeof(f32v4)+sizeof(float3);
    desc.bindings[0].input_rate = OGA_VERTEX_INPUT_RATE_VERTEX;
    desc.binding_count = 1;
    
    desc.attributes[desc.attribute_count].binding = 0;
    desc.attributes[desc.attribute_count].location = 0;
    desc.attributes[desc.attribute_count].offset = 0;
    desc.attributes[desc.attribute_count].type = OGA_VERTEX_ATTRIBUTE_TYPE_F32V4;
    desc.attribute_count += 1;
    
    desc.attributes[desc.attribute_count].binding = 0;
    desc.attributes[desc.attribute_count].location = 1;
    desc.attributes[desc.attribute_count].offset = sizeof(f32v4);
    desc.attributes[desc.attribute_count].type = OGA_VERTEX_ATTRIBUTE_TYPE_F32V3;
    desc.attribute_count += 1;
*/
typedef struct Oga_Vertex_List_Binding_Desc {
    
    u64 stride; // The stride between the start of each vertex in the vertex list in this binding slot
    Oga_Vertex_List_Input_Rate input_rate; // Input is per vertex or per instance
    
} Oga_Vertex_List_Binding_Desc;
typedef struct Oga_Vertex_List_Attribute_Desc {
    
    u64 binding; // The attribute points to the vertex list in this binding slot
    u64 location; // The attribute is bound to this location in the program input
    u64 offset; 
    Oga_Vertex_Attribute_Type type;
    
} Oga_Vertex_List_Attribute_Desc;
typedef struct Oga_Vertex_List_Layout_Desc {
    
    Oga_Vertex_List_Binding_Desc bindings[OGA_MAX_VERTEX_BINDING_COUNT]; // Vertex list binding slots
    u64 binding_count;
    Oga_Vertex_List_Attribute_Desc attributes[OGA_MAX_VERTEX_ATTRIBUTE_COUNT];
    u64 attribute_count;
    
} Oga_Vertex_List_Layout_Desc;

typedef u64 Oga_Render_Pass_Flag;
unit_local const Oga_Render_Pass_Flag OGA_RENDER_PASS_INHERITANCE_PARENT = 1 << 0;
unit_local const Oga_Render_Pass_Flag OGA_RENDER_PASS_INHERITANCE_CHILD = 1 << 1;
//unit_local const Oga_Render_Pass_Flag OGA_RENDER_PASS_DISABLE_DEPTH_CLAMP = 1 << 2;

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
    
    Oga_Vertex_List_Layout_Desc vertex_input_layout;
    
    Oga_Binding_List_Layout *binding_list_layout;
    
} Oga_Render_Pass_Desc;

typedef struct Oga_Render_Pass {
    void *id;
    Oga_Context *context;
    Oga_Vertex_List_Layout_Desc vertex_input_layout;
} Oga_Render_Pass;

OSTD_LIB Oga_Result oga_init_render_passes(Oga_Context *context, Oga_Render_Pass_Desc* descs, Oga_Render_Pass **render_passes, u64 render_pass_count);

OSTD_LIB Oga_Result oga_init_render_pass(Oga_Context *context, Oga_Render_Pass_Desc desc, Oga_Render_Pass **render_pass);
OSTD_LIB void oga_uninit_render_pass(Oga_Render_Pass *render_pass);

//////////
/// Synchronization

// Gpu latch; for synchronizing on gpu. Signalled on gpu, waited on gpu.
typedef struct Oga_Gpu_Latch {
    void *id;
    Oga_Context *context;
} Oga_Gpu_Latch;

OSTD_LIB Oga_Result oga_init_gpu_latch(Oga_Context *context, Oga_Gpu_Latch **gpu_latch);
OSTD_LIB void oga_uninit_gpu_latch(Oga_Gpu_Latch *gpu_latch);

// Cpu latch; for synchronizing cpu with gpu. Signalled on gpu, waited on cpu.
typedef struct Oga_Cpu_Latch {
    void *id;
    Oga_Context *context;
} Oga_Cpu_Latch;
OSTD_LIB Oga_Result oga_init_cpu_latch(Oga_Context *context, Oga_Cpu_Latch **cpu_latch, bool start_signaled);
OSTD_LIB void oga_uninit_cpu_latch(Oga_Cpu_Latch *cpu_latch);
OSTD_LIB Oga_Result oga_wait_latch(Oga_Cpu_Latch *cpu_latch);
OSTD_LIB Oga_Result oga_reset_latch(Oga_Cpu_Latch *cpu_latch);

//////////
/// Memory & Views

#define OGA_INTERNALLY_MANAGED_MEMORY_HANDLE ((Oga_Memory_Pointer) { (void*)U64_MAX, (Oga_Context*) U64_MAX, U64_MAX, U64_MAX, U64_MAX, U64_MAX, U64_MAX })
typedef struct Oga_Memory_Pointer {
    void *id;
    Oga_Context *context;
    u64 offset;
    u64 size;
    u64 heap_index;
    Oga_Memory_Property_Flag properties;
    Oga_Memory_Usage usage;
    
#ifdef OGA_DEBUG
    // todo(charlie) #validation Track view regions
#endif 
} Oga_Memory_Pointer;

OSTD_LIB Oga_Result oga_allocate_memory(Oga_Context *context, u64 size, Oga_Memory_Property_Flag properties, Oga_Memory_Usage usage, Oga_Memory_Pointer *ptr);
OSTD_LIB void oga_deallocate_memory(Oga_Memory_Pointer ptr);
OSTD_LIB Oga_Result oga_map_memory(Oga_Memory_Pointer ptr, u64 size, void **mapped_mem);
OSTD_LIB void oga_unmap_memory(Oga_Memory_Pointer ptr);
OSTD_LIB Oga_Result oga_memory_offset(Oga_Memory_Pointer ptr, s64 offset, Oga_Memory_Pointer *result_ptr);


typedef struct Oga_Memory_View_Desc  {
    Oga_Memory_Pointer memory_pointer;
    u64 size;
} Oga_Memory_View_Desc;

// These are the same (as of now) but we have a compiler and a statically typechecked programming language,
// which we should use.
typedef struct Oga_Vertex_List_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 size;
} Oga_Vertex_List_View;
typedef struct Oga_Index_List_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 size;
} Oga_Index_List_View;

OSTD_LIB Oga_Result oga_init_vertex_list_view(Oga_Context *context, Oga_Memory_View_Desc desc, Oga_Vertex_List_View **vlist);
OSTD_LIB void oga_uninit_vertex_list_view(Oga_Vertex_List_View *vlist);

OSTD_LIB Oga_Result oga_init_index_list_view(Oga_Context *context, Oga_Memory_View_Desc desc, Oga_Index_List_View **ilist);
OSTD_LIB void oga_uninit_index_list_view(Oga_Index_List_View *ilist);

/// Image view

typedef enum Oga_Dimensions {
    OGA_1D,
    OGA_2D,
    OGA_3D,
} Oga_Dimensions;

typedef struct Oga_Image_View_Desc {
    Oga_Memory_Pointer memory_pointer;
    Oga_Format format;
    Oga_Dimensions dimensions;
    u64 width, height, depth;
    bool linear_tiling;
    u64 graphics_engine_family_index;
    
} Oga_Image_View_Desc;

typedef struct Oga_Image_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 width, height, depth;
    Oga_Dimensions dimensions;
    bool linear_tiling;
} Oga_Image_View;

OSTD_LIB Oga_Result oga_init_image_view(Oga_Context *context, Oga_Image_View_Desc desc, Oga_Image_View **image);
OSTD_LIB void oga_uninit_image_view(Oga_Image_View *image);

OSTD_LIB u64 oga_get_image_memory_requirement(Oga_Context *context, Oga_Image_View_Desc desc);

typedef struct Oga_FBuffer_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 width, height, depth;
    Oga_Dimensions dimensions;
    bool linear_tiling;
} Oga_FBuffer_View;

OSTD_LIB Oga_Result oga_init_fbuffer_view(Oga_Context *context, Oga_Image_View_Desc desc, Oga_FBuffer_View **fbuffer);
OSTD_LIB void oga_uninit_fbuffer_view(Oga_FBuffer_View *fbuffer);

/// Image copy target view

typedef enum Oga_Optimal_Copy_Flag_ {
    OGA_OPTIMAL_COPY_DST = 1 << 1,
    OGA_OPTIMAL_COPY_SRC = 1 << 2,
} Oga_Optimal_Copy_Flag_;
typedef u64 Oga_Optimal_Copy_Flag;

typedef struct Oga_Optimal_Copy_View_Desc {
    Oga_Memory_Pointer memory_pointer;
    Oga_Format format;
    Oga_Dimensions dimensions;
    u64 width, height, depth;
    bool linear_tiling;
    u64 graphics_engine_family_index;
    Oga_Optimal_Copy_Flag flags;
} Oga_Optimal_Copy_View_Desc;

typedef struct Oga_Optimal_Copy_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 width, height, depth;
    Oga_Dimensions dimensions;
    bool linear_tiling;
    Oga_Optimal_Copy_Flag flags;
} Oga_Optimal_Copy_View;

OSTD_LIB Oga_Result oga_init_optimal_copy_view(Oga_Context *context, Oga_Optimal_Copy_View_Desc desc, Oga_Optimal_Copy_View **image);
OSTD_LIB void oga_uninit_optimal_copy_view(Oga_Optimal_Copy_View *image);

typedef struct Oga_Render_Image_View_Desc {
    Oga_Memory_Pointer memory_pointer;
    Oga_Format format;
    u64 width, height;    
} Oga_Render_Image_View_Desc;

typedef struct Oga_Render_Image_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 width, height;
} Oga_Render_Image_View;

// todo(charlie)
// Oga_Result oga_init_render_image_view(Oga_Context *context, Oga_Render_Image_View_Desc desc, Oga_Render_Image_View **view);
// void oga_uninit_render_image_view(Oga_Render_Image_View *view);
//
// u64 oga_get_render_image_memory_requirement(Oga_Context *context, Oga_Render_Image_View_Desc desc);



/// Read buffer view

typedef struct Oga_Block_View {
    void *id;
    Oga_Context *context;
    Oga_Memory_Pointer memory_pointer;
    u64 size;
} Oga_Block_View;
OSTD_LIB Oga_Result oga_init_block_view(Oga_Context *context, Oga_Memory_View_Desc desc, Oga_Block_View **buffer);
OSTD_LIB void oga_uninit_block_view(Oga_Block_View *buffer);

// todo(charlie) #validation
// Keep track of all init()'s and report them here if they were not uninitted
// This is really only here to get validation/debug layer messages for leaked resources
OSTD_LIB void oga_reset(void);


//////////
/// Commands

typedef u64 Oga_Command_Pool_Flag;
#define  OGA_COMMAND_POOL_NONE 0
#define  OGA_COMMAND_POOL_SHORT_LIVED_ALLOCATIONS (1 << 0)

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
    
#ifdef OGA_DEBUG
    // todo(charlie) #validation track all submitted commands and validate
    //  - Vertex lists bound when cmd_draw in a render pass which specified vertex list bindings
    //  - Index list is bound when cmd_draw indexed
    //  - Formatted blocks are in the correct layout state for the operations they will be used in
#endif
} Oga_Command_List;

OSTD_LIB Oga_Result oga_init_command_pool(Oga_Context *context, Oga_Command_Pool_Desc desc, Oga_Command_Pool **pool);
 // This will free all command lists, so you do not need to explicitly free each command list.
OSTD_LIB void oga_uninit_command_pool(Oga_Command_Pool *pool);
OSTD_LIB void oga_reset_command_pool(Oga_Command_Pool *pool);

OSTD_LIB Oga_Result oga_get_command_lists(Oga_Command_Pool *pool, Oga_Command_List *lists, u64 list_count);
OSTD_LIB void oga_release_command_lists(Oga_Command_List *lists, u64 list_count);



typedef u64 Oga_Command_List_Usage_Flag;
#define OGA_COMMAND_LIST_USAGE_ONE_TIME_SUBMIT (1 << 0)

OSTD_LIB Oga_Result oga_cmd_begin(Oga_Command_List cmd, Oga_Command_List_Usage_Flag flags);
OSTD_LIB Oga_Result oga_cmd_end(Oga_Command_List cmd);

typedef struct Oga_Submit_Command_List_Desc {
    Oga_Logical_Engine engine; 
    Oga_Gpu_Latch **wait_gpu_latches; 
    u64 wait_gpu_latch_count; 
    Oga_Gpu_Latch **signal_gpu_latches; 
    u64 signal_gpu_latch_count; 
    Oga_Cpu_Latch *signal_cpu_latch;
} Oga_Submit_Command_List_Desc;
OSTD_LIB Oga_Result oga_submit_command_list(Oga_Command_List cmd, Oga_Submit_Command_List_Desc desc);

typedef struct Oga_Gpu_Timestamp_Pool {
    void *id;
    Oga_Context *context;
    u64 timestamp_count;
    u64 written_timestamp_count;
} Oga_Gpu_Timestamp_Pool;

OSTD_LIB Oga_Result oga_init_gpu_timestamp_pool(Oga_Context *context, u64 timestamp_count, Oga_Gpu_Timestamp_Pool **pool);
OSTD_LIB void oga_uninit_gpu_timestamp_pool(Oga_Gpu_Timestamp_Pool *pool);

OSTD_LIB void oga_cmd_reset_timestamp_pool(Oga_Command_List cmd, Oga_Gpu_Timestamp_Pool *pool);
OSTD_LIB void oga_cmd_write_timestamp(Oga_Command_List cmd, Oga_Gpu_Timestamp_Pool *pool);

OSTD_LIB Oga_Result oga_read_timestamps(Oga_Gpu_Timestamp_Pool *pool, f64 *nanosecond_timestamps, bool wait);

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
    Oga_Render_Image_View *image;
    
    // If rendering with multisampling, we can resolve the multiple samples into single samples
    // on another image.
    Oga_Msaa_Resolve_Mode_Flag resolve_mode;
    const Oga_Image_View *resolve_image;
    
    Oga_Attachment_Load_Op load_op;
    Oga_Attachment_Store_Op store_op;
    
    float32 clear_color[4]; // In case of load_op CLEAR
    
} Oga_Render_Attachment_Desc;

typedef struct Oga_Begin_Render_Pass_Desc {
    s64 render_area_offset_x;
    s64 render_area_offset_y;
    u64 render_area_width;
    u64 render_area_height;
    u64 attachment_count;
    Oga_Render_Attachment_Desc *attachments;
} Oga_Begin_Render_Pass_Desc;

OSTD_LIB void oga_cmd_begin_render_pass(Oga_Command_List cmd, Oga_Render_Pass *render_pass, Oga_Begin_Render_Pass_Desc desc);
OSTD_LIB void oga_cmd_end_render_pass(Oga_Command_List cmd, Oga_Render_Pass *render_pass);

OSTD_LIB void oga_cmd_bind_render_pass_binding_list(Oga_Command_List cmd, Oga_Render_Pass *pass, Oga_Binding_List *list);

typedef enum Oga_Draw_Type {
    OGA_DRAW_INSTANCED,
    OGA_DRAW_VERTEX_LIST,
    OGA_DRAW_VERTEX_LIST_INSTANCED,
    OGA_DRAW_VERTEX_LIST_INDEXED,
    OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED,
    
    OGA_DRAW_INSTANCED_INDIRECT,
    OGA_DRAW_VERTEX_LIST_INDIRECT,
    OGA_DRAW_VERTEX_LIST_INSTANCED_INDIRECT,
    OGA_DRAW_VERTEX_LIST_INDEXED_INDIRECT,
    OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED_INDIRECT,
} Oga_Draw_Type;
typedef enum Oga_Index_Type {
    OGA_INDEX_U32,
    OGA_INDEX_U16,
} Oga_Index_Type;
typedef struct Oga_Draw_Desc {
    
    Oga_Draw_Type draw_type;
    
    // All
    u64 vertex_start; // The first vertex to draw. For vertex lists, this is an offset from the BASE vertex at the binding point
    u64 vertex_count;
    
    // Vertex list
    Oga_Vertex_List_View *vertex_list_bindings[OGA_MAX_VERTEX_BINDING_COUNT];
    u64 vertex_list_offsets[OGA_MAX_VERTEX_BINDING_COUNT]; // Offset to the BASE vertex to be bound
    u64 vertex_list_binding_count;
    
    // Instanced
    u64 instance_start;
    u64 instance_count;
    
    // Indexed
    u64 index_start;
    u64 index_count;
    Oga_Index_List_View *index_list;
    u64 index_list_offset;
    Oga_Index_Type index_type;
    
    // Indirect
    // Indirect_Block *indirect_block;
    
} Oga_Draw_Desc;

OSTD_LIB Oga_Result oga_cmd_draw(Oga_Command_List cmd, Oga_Draw_Desc desc);

OSTD_LIB void oga_cmd_copy_linear(Oga_Command_List cmd, Oga_Memory_Pointer dst, Oga_Memory_Pointer src, u64 size);

typedef struct Oga_Optimal_Copy_Desc {
    s64 offset_x, offset_y, offset_z;
    u64 width, height, depth;
} Oga_Optimal_Copy_Desc;
OSTD_LIB void oga_cmd_copy_linear_to_image(Oga_Command_List cmd, Oga_Optimal_Copy_View *dst_view, Oga_Optimal_Copy_Desc dst_desc, Oga_Memory_Pointer src);
OSTD_LIB void oga_cmd_copy_image_to_linear(Oga_Command_List cmd, Oga_Memory_Pointer dst, Oga_Optimal_Copy_View *src_view, Oga_Optimal_Copy_Desc src_desc);
OSTD_LIB void oga_cmd_copy_image(Oga_Command_List cmd, Oga_Optimal_Copy_View *dst_view, Oga_Optimal_Copy_Desc dst_desc, Oga_Optimal_Copy_View *src_view, Oga_Optimal_Copy_Desc src_desc);

OSTD_LIB void oga_cmd_fill_image(Oga_Command_List cmd, Oga_Optimal_Copy_View *dst_view, f32v4 color);

#ifdef OGA_IMPL_AUTO
    #if (OS_FLAGS & OS_FLAG_WEB)
        // webgl and webgpu are awful so we will only support software rendering for web.
    #elif (OS_FLAGS & OS_FLAG_WINDOWS)
        #define OGA_IMPL_D3D12
    #elif (OS_FLAGS & OS_FLAG_APPLE)
        #define OGA_IMPL_METAL
    #elif OS_FLAGS != 0
        // If recognized OS, fallback to vulkan, because it's probably supported.
        // todo(charlie) consoles
        #define OGA_IMPL_VULKAN
    #endif
#endif // OGA_IMPL_AUTO

#if !defined(OGA_IMPL_D3D12) && !defined(OGA_IMPL_METAL) && !defined(OGA_IMPL_VULKAN)

    #define OGA_NO_IMPL

#endif

#if defined(OSTD_IMPL)

void* oga_state_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags) {
    (void)flags;
    (void)old_n;
    Oga_State_Allocator_Data *a = (Oga_State_Allocator_Data*)data;

    if (alignment == 0)
        alignment = 8;
    
    System_Info info = sys_get_info();
    
    switch (msg) {
        case ALLOCATOR_ALLOCATE:
        {
            if (n > 4096) {
                // Just directly map pages for big allocations. This should be rare, or probably never happen.
                void *p = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, (n+info.page_size)/info.page_size, false);
                assert(p);
                assert((u64)p % info.page_size == 0);
                assertmsgs((u64)p % alignment == 0, tprint("Expected alignment of %i, view is %u", alignment, p));
                return p;
            }
            Oga_Allocator_Row *row = 0;
            u64 stride = 0;
            for (u64 i = 0; i < 11; i += 1) {
                u64 row_stride = powu(2, i+4);
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
                
                u64 initial_row_size = max(info.granularity, 1024*32);
                row->start = sys_map_pages(SYS_MEMORY_ALLOCATE, reserved, initial_row_size/info.page_size, true);
                
                if (!row->start) return 0;
                
                // Round to page size (actual allocated size)
                row->end = (u8*)row->start + (initial_row_size/info.page_size)*info.page_size;
                
                row->first_free_index = 0;
                row->highest_allocated_index = 0;
            }
            
            
            void *next = (u8*)row->start + row->first_free_index*stride;
            u64 allocated_index = ((u64)next-(u64)row->start)/stride;
            
            assert(row->first_free_index <= ((u64)row->end-(u64)row->start)/stride);
            
            if ((u8*)next == (u8*)row->end) {
                u64 old_size = (u64)row->end - (u64)row->start;
                u64 new_size = (((old_size*2)+info.page_size)/info.page_size)*info.page_size;
                
                void *expansion = sys_map_pages(SYS_MEMORY_ALLOCATE, row->end, new_size/info.page_size, true);
#if OS_FLAGS & OS_FLAG_WINDOWS
                assert(expansion);
#endif
                if (!expansion) {  
                    // todo(charlie) #Portability #Memory #Speed
                    // If target system has poor mapping features, we might hit this often, which is kind of crazy.
                    void *p = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, (n+info.page_size)/info.page_size, false);
                    assert((u64)p % alignment == 0);
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
                // When we free a block, we store the index to the next free block
                row->first_free_index = *(u64*)next;
            }
            
            assert(row->first_free_index <= ((u64)row->end-(u64)row->start)/stride);            assertmsgs((u64)((u8*)row->start + row->first_free_index*stride) <= (u64)row->end, tprint("%u, %u", next, row->end));
            
            row->highest_allocated_index = max(row->highest_allocated_index, allocated_index);
            
            assert(row->first_free_index <= row->highest_allocated_index+1);
            
            assert((u64)next % alignment == 0);
            
            return next;
        }
        case ALLOCATOR_REALLOCATE:
        {
            if (n == 0) {
                oga_state_allocator_proc(ALLOCATOR_FREE, 0, old, 0, 0, alignment, flags);
                return 0;
            }
            void * pnew = oga_state_allocator_proc(ALLOCATOR_ALLOCATE, data, 0, 0, n, alignment, flags);
            if (old) {
                memcpy(pnew, old, min(n, old_n));
                oga_state_allocator_proc(ALLOCATOR_FREE, 0, old, 0, 0, alignment, flags);
            }
            return pnew;
        }
        case ALLOCATOR_FREE:
        {
            if (!old) return 0;
            
            Oga_Allocator_Row *row = 0;
            u64 stride = 16;
            for (u64 i = 0; i < 11; i += 1) {
                if ((u64)old >= (u64)a->rows[i].start && (u64)old < (u64)a->rows[i].end) {
                    row = &a->rows[i];
                    u64 exp = powu(2, i+4);
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
            
            // Use old memory to store index to the next free block
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

#ifdef __clang__
        // clang loop vectorization shits its pants here when -mavx -mavx2, so just disable it.
        // It completely messes up the branches, basically always doing continue here for some reason.
        // todo(charlie) try gcc and see if same thing happens
        #pragma clang loop vectorize(disable)
#endif // __clang__
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

#define OGA_OSL_TARGET OSL_TARGET_SPIRV_VULKAN

#if COMPILER_FLAGS & COMPILER_FLAG_MSC
    #pragma comment(lib, "vendors/vulkan-1.lib")
#endif // COMPILER_FLAGS & COMPILER_FLAG_MSC

#if (OS_FLAGS & (OS_FLAG_WINDOWS | OS_FLAG_LINUX | OS_FLAG_MACOS | OS_FLAG_IOS | OS_FLAG_ANDROID)) == 0
    #error Vulkan is not supported on target platform
#else
    #include "graphics_vulkan.h"
#endif // (OS_FLAGS & (OS_FLAG_WINDOWS | OS_FLAG_LINUX | OS_FLAG_MACOS | OS_FLAG_IOS | OS_FLAG_ANDROID))

// OGA_IMPL_VULKAN
#elif defined(OGA_IMPL_D3D12)

/////////////////////////////////////////////////////
//////
// :D3D12
//////
/////////////////////////////////////////////////////

#define OGA_OSL_TARGET OSL_TARGET_DXIL

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

#define OGA_OSL_TARGET OSL_TARGET_MSL

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

#define OGA_OSL_TARGET OSL_TARGET_AVX

u64 oga_query_devices(Oga_Device *buffer, u64 buffer_count) {
    (void)buffer;(void)buffer_count;
    return 0;
}

#endif

#endif // OSTD_IMPL

#endif // OGA_GRAPHICS && !OSTD_HEADLESS

