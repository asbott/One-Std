
#define uint8_t u8
#define int8_t  s8
#define uint16_t u16
#define int16_t  s16
#define uint32_t u32
#define int32_t  s32
#define uint64_t u64
#define int64_t  s64

#define VK_NO_STDDEF_H
#define VK_NO_STDINT_H
// noconcat
#include <vulkan/vulkan.h>


// We manually include the vulkan-specific headers, otherwise vulkan.h will include windows.h
#if OS_FLAGS & OS_FLAG_WINDOWS
// noconcat
#include <vulkan/vulkan_win32.h>
#elif OS_FLAGS & OS_FLAG_LINUX
// noconcat
#include <vulkan/vulkan_xlib.h>
#elif OS_FLAGS & OS_FLAG_MACOS
// noconcat
#include <vulkan/vulkan_macos.h>
#elif OS_FLAGS & OS_FLAG_IOS
// noconcat
#include <vulkan/vulkan_ios.h>
#elif OS_FLAGS & OS_FLAG_ANDROID
// noconcat
#include <vulkan/vulkan_android.h>
#else
#error Vulkan is not supported on target platform
#endif


#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#endif // __clang__

typedef struct _Vk_Memory_State {
    VkDeviceMemory memory;
    u32 memory_type_index;
    VkBuffer raw_view;
    VkImage last_image_optimal_view;
    u64 last_image_optimal_offset;
} _Vk_Memory_State;

typedef struct _Vk_Image_State {
    VkImage image;
    VkImageView view;
} _Vk_Image_State;
typedef struct _Vk_Render_Image_State {
    VkImage image;
    VkImageView view;
} _Vk_Render_Image_State;

typedef struct _Vk_Binding_List_Layout_State {
    VkDescriptorPool pool;
    VkDescriptorSetLayout layout;
} _Vk_Binding_List_Layout_State;

typedef struct _Vk_Swapchain_State {
    VkSwapchainKHR vk_swapchain;
    VkSurfaceKHR vk_surface;
} _Vk_Swapchain_State;

typedef struct _Vk_Render_Pass_State {
    VkPipeline pipeline;
    VkPipelineLayout layout;
    u64 active_image_count;
    VkImage active_images[128];
    VkImage active_resolve_images[128];
} _Vk_Render_Pass_State;

typedef struct _Vk_Context_Internal {
    u32 vk_version_major;
    u32 vk_version_minor;
    u32 vk_version_patch;
    bool dynamic_rendering;
    bool dynamic_rendering_is_extension;
    
    PFN_vkCmdBeginRenderingKHR vkCmdBeginRenderingKHR;
    PFN_vkCmdEndRenderingKHR vkCmdEndRenderingKHR;
    
    VkAllocationCallbacks vk_allocs;
} _Vk_Context_Internal;

typedef struct _Vk_Memory_Block {
    VkDeviceMemory memory;
    VkAccessFlags access_state;
    
    VkBuffer access_buffer;
} _Vk_Memory_Block;

unit_local inline VkFormat _oga_to_vk_format(Oga_Format k) {
    switch (k) {
        case OGA_FORMAT_R4G4_UNORM_PACK8:             return VK_FORMAT_R4G4_UNORM_PACK8;
        case OGA_FORMAT_R4G4B4A4_UNORM_PACK16:         return VK_FORMAT_R4G4B4A4_UNORM_PACK16;
        case OGA_FORMAT_B4G4R4A4_UNORM_PACK16:         return VK_FORMAT_B4G4R4A4_UNORM_PACK16;
        case OGA_FORMAT_R5G6B5_UNORM_PACK16:           return VK_FORMAT_R5G6B5_UNORM_PACK16;
        case OGA_FORMAT_B5G6R5_UNORM_PACK16:           return VK_FORMAT_B5G6R5_UNORM_PACK16;
        case OGA_FORMAT_R5G5B5A1_UNORM_PACK16:         return VK_FORMAT_R5G5B5A1_UNORM_PACK16;
        case OGA_FORMAT_A1R5G5B5_UNORM_PACK16:         return VK_FORMAT_A1R5G5B5_UNORM_PACK16;

        case OGA_FORMAT_R8_UNORM:                      return VK_FORMAT_R8_UNORM;
        case OGA_FORMAT_R8_SNORM:                      return VK_FORMAT_R8_SNORM;
        case OGA_FORMAT_R8_UINT:                       return VK_FORMAT_R8_UINT;
        case OGA_FORMAT_R8_SINT:                       return VK_FORMAT_R8_SINT;
        case OGA_FORMAT_R8_SRGB:                       return VK_FORMAT_R8_SRGB;

        case OGA_FORMAT_R8G8_UNORM:                    return VK_FORMAT_R8G8_UNORM;
        case OGA_FORMAT_R8G8_SNORM:                    return VK_FORMAT_R8G8_SNORM;
        case OGA_FORMAT_R8G8_UINT:                     return VK_FORMAT_R8G8_UINT;
        case OGA_FORMAT_R8G8_SINT:                     return VK_FORMAT_R8G8_SINT;
        case OGA_FORMAT_R8G8_SRGB:                     return VK_FORMAT_R8G8_SRGB;

        case OGA_FORMAT_R8G8B8_UNORM:                  return VK_FORMAT_R8G8B8_UNORM;
        case OGA_FORMAT_R8G8B8_SNORM:                  return VK_FORMAT_R8G8B8_SNORM;
        case OGA_FORMAT_R8G8B8_UINT:                   return VK_FORMAT_R8G8B8_UINT;
        case OGA_FORMAT_R8G8B8_SINT:                   return VK_FORMAT_R8G8B8_SINT;
        case OGA_FORMAT_R8G8B8_SRGB:                   return VK_FORMAT_R8G8B8_SRGB;

        case OGA_FORMAT_R8G8B8A8_UNORM:                return VK_FORMAT_R8G8B8A8_UNORM;
        case OGA_FORMAT_R8G8B8A8_SNORM:                return VK_FORMAT_R8G8B8A8_SNORM;
        case OGA_FORMAT_R8G8B8A8_UINT:                 return VK_FORMAT_R8G8B8A8_UINT;
        case OGA_FORMAT_R8G8B8A8_SINT:                 return VK_FORMAT_R8G8B8A8_SINT;
        case OGA_FORMAT_R8G8B8A8_SRGB:                 return VK_FORMAT_R8G8B8A8_SRGB;

        case OGA_FORMAT_B8G8R8A8_UNORM:                return VK_FORMAT_B8G8R8A8_UNORM;
        case OGA_FORMAT_B8G8R8A8_SNORM:                return VK_FORMAT_B8G8R8A8_SNORM;
        case OGA_FORMAT_B8G8R8A8_UINT:                 return VK_FORMAT_B8G8R8A8_UINT;
        case OGA_FORMAT_B8G8R8A8_SINT:                 return VK_FORMAT_B8G8R8A8_SINT;
        case OGA_FORMAT_B8G8R8A8_SRGB:                 return VK_FORMAT_B8G8R8A8_SRGB;

        case OGA_FORMAT_R16_UNORM:                     return VK_FORMAT_R16_UNORM;
        case OGA_FORMAT_R16_SNORM:                     return VK_FORMAT_R16_SNORM;
        case OGA_FORMAT_R16_UINT:                      return VK_FORMAT_R16_UINT;
        case OGA_FORMAT_R16_SINT:                      return VK_FORMAT_R16_SINT;
        case OGA_FORMAT_R16_SFLOAT:                    return VK_FORMAT_R16_SFLOAT;

        case OGA_FORMAT_R16G16_UNORM:                  return VK_FORMAT_R16G16_UNORM;
        case OGA_FORMAT_R16G16_SNORM:                  return VK_FORMAT_R16G16_SNORM;
        case OGA_FORMAT_R16G16_UINT:                   return VK_FORMAT_R16G16_UINT;
        case OGA_FORMAT_R16G16_SINT:                   return VK_FORMAT_R16G16_SINT;
        case OGA_FORMAT_R16G16_SFLOAT:                 return VK_FORMAT_R16G16_SFLOAT;

        case OGA_FORMAT_R16G16B16A16_UNORM:            return VK_FORMAT_R16G16B16A16_UNORM;
        case OGA_FORMAT_R16G16B16A16_SNORM:            return VK_FORMAT_R16G16B16A16_SNORM;
        case OGA_FORMAT_R16G16B16A16_UINT:             return VK_FORMAT_R16G16B16A16_UINT;
        case OGA_FORMAT_R16G16B16A16_SINT:             return VK_FORMAT_R16G16B16A16_SINT;
        case OGA_FORMAT_R16G16B16A16_SFLOAT:           return VK_FORMAT_R16G16B16A16_SFLOAT;

        case OGA_FORMAT_R32_SFLOAT:                    return VK_FORMAT_R32_SFLOAT;
        case OGA_FORMAT_R32_UINT:                      return VK_FORMAT_R32_UINT;
        case OGA_FORMAT_R32_SINT:                      return VK_FORMAT_R32_SINT;

        case OGA_FORMAT_R32G32_SFLOAT:                 return VK_FORMAT_R32G32_SFLOAT;
        case OGA_FORMAT_R32G32_UINT:                   return VK_FORMAT_R32G32_UINT;
        case OGA_FORMAT_R32G32_SINT:                   return VK_FORMAT_R32G32_SINT;

        case OGA_FORMAT_R32G32B32_SFLOAT:              return VK_FORMAT_R32G32B32_SFLOAT;
        case OGA_FORMAT_R32G32B32_UINT:                return VK_FORMAT_R32G32B32_UINT;
        case OGA_FORMAT_R32G32B32_SINT:                return VK_FORMAT_R32G32B32_SINT;

        case OGA_FORMAT_R32G32B32A32_SFLOAT:           return VK_FORMAT_R32G32B32A32_SFLOAT;
        case OGA_FORMAT_R32G32B32A32_UINT:             return VK_FORMAT_R32G32B32A32_UINT;
        case OGA_FORMAT_R32G32B32A32_SINT:             return VK_FORMAT_R32G32B32A32_SINT;

        case OGA_FORMAT_BC1_RGB_UNORM_BLOCK:           return VK_FORMAT_BC1_RGB_UNORM_BLOCK;
        case OGA_FORMAT_BC1_RGB_SRGB_BLOCK:            return VK_FORMAT_BC1_RGB_SRGB_BLOCK;
        case OGA_FORMAT_BC1_RGBA_UNORM_BLOCK:          return VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
        case OGA_FORMAT_BC1_RGBA_SRGB_BLOCK:           return VK_FORMAT_BC1_RGBA_SRGB_BLOCK;
        case OGA_FORMAT_BC2_UNORM_BLOCK:               return VK_FORMAT_BC2_UNORM_BLOCK;
        case OGA_FORMAT_BC2_SRGB_BLOCK:                return VK_FORMAT_BC2_SRGB_BLOCK;
        case OGA_FORMAT_BC3_UNORM_BLOCK:               return VK_FORMAT_BC3_UNORM_BLOCK;
        case OGA_FORMAT_BC3_SRGB_BLOCK:                return VK_FORMAT_BC3_SRGB_BLOCK;
        case OGA_FORMAT_BC4_UNORM_BLOCK:               return VK_FORMAT_BC4_UNORM_BLOCK;
        case OGA_FORMAT_BC4_SNORM_BLOCK:               return VK_FORMAT_BC4_SNORM_BLOCK;
        case OGA_FORMAT_BC5_UNORM_BLOCK:               return VK_FORMAT_BC5_UNORM_BLOCK;
        case OGA_FORMAT_BC5_SNORM_BLOCK:               return VK_FORMAT_BC5_SNORM_BLOCK;
        case OGA_FORMAT_BC6H_UFLOAT_BLOCK:             return VK_FORMAT_BC6H_UFLOAT_BLOCK;
        case OGA_FORMAT_BC6H_SFLOAT_BLOCK:             return VK_FORMAT_BC6H_SFLOAT_BLOCK;
        case OGA_FORMAT_BC7_UNORM_BLOCK:               return VK_FORMAT_BC7_UNORM_BLOCK;
        case OGA_FORMAT_BC7_SRGB_BLOCK:                return VK_FORMAT_BC7_SRGB_BLOCK;

        case OGA_FORMAT_ENUM_MAX:
        default:
            return (VkFormat)0;
    }
    return (VkFormat)0;
}
unit_local inline Oga_Format _vk_to_oga_format(VkFormat k) {
    switch ((s64)k) {
        case VK_FORMAT_R4G4_UNORM_PACK8:              return OGA_FORMAT_R4G4_UNORM_PACK8;
        case VK_FORMAT_R4G4B4A4_UNORM_PACK16:          return OGA_FORMAT_R4G4B4A4_UNORM_PACK16;
        case VK_FORMAT_B4G4R4A4_UNORM_PACK16:          return OGA_FORMAT_B4G4R4A4_UNORM_PACK16;
        case VK_FORMAT_R5G6B5_UNORM_PACK16:            return OGA_FORMAT_R5G6B5_UNORM_PACK16;
        case VK_FORMAT_B5G6R5_UNORM_PACK16:            return OGA_FORMAT_B5G6R5_UNORM_PACK16;
        case VK_FORMAT_R5G5B5A1_UNORM_PACK16:          return OGA_FORMAT_R5G5B5A1_UNORM_PACK16;
        case VK_FORMAT_A1R5G5B5_UNORM_PACK16:          return OGA_FORMAT_A1R5G5B5_UNORM_PACK16;

        case VK_FORMAT_R8_UNORM:                       return OGA_FORMAT_R8_UNORM;
        case VK_FORMAT_R8_SNORM:                       return OGA_FORMAT_R8_SNORM;
        case VK_FORMAT_R8_UINT:                        return OGA_FORMAT_R8_UINT;
        case VK_FORMAT_R8_SINT:                        return OGA_FORMAT_R8_SINT;
        case VK_FORMAT_R8_SRGB:                        return OGA_FORMAT_R8_SRGB;

        case VK_FORMAT_R8G8_UNORM:                     return OGA_FORMAT_R8G8_UNORM;
        case VK_FORMAT_R8G8_SNORM:                     return OGA_FORMAT_R8G8_SNORM;
        case VK_FORMAT_R8G8_UINT:                      return OGA_FORMAT_R8G8_UINT;
        case VK_FORMAT_R8G8_SINT:                      return OGA_FORMAT_R8G8_SINT;
        case VK_FORMAT_R8G8_SRGB:                      return OGA_FORMAT_R8G8_SRGB;

        case VK_FORMAT_R8G8B8_UNORM:                   return OGA_FORMAT_R8G8B8_UNORM;
        case VK_FORMAT_R8G8B8_SNORM:                   return OGA_FORMAT_R8G8B8_SNORM;
        case VK_FORMAT_R8G8B8_UINT:                    return OGA_FORMAT_R8G8B8_UINT;
        case VK_FORMAT_R8G8B8_SINT:                    return OGA_FORMAT_R8G8B8_SINT;
        case VK_FORMAT_R8G8B8_SRGB:                    return OGA_FORMAT_R8G8B8_SRGB;

        case VK_FORMAT_R8G8B8A8_UNORM:                 return OGA_FORMAT_R8G8B8A8_UNORM;
        case VK_FORMAT_R8G8B8A8_SNORM:                 return OGA_FORMAT_R8G8B8A8_SNORM;
        case VK_FORMAT_R8G8B8A8_UINT:                  return OGA_FORMAT_R8G8B8A8_UINT;
        case VK_FORMAT_R8G8B8A8_SINT:                  return OGA_FORMAT_R8G8B8A8_SINT;
        case VK_FORMAT_R8G8B8A8_SRGB:                  return OGA_FORMAT_R8G8B8A8_SRGB;

        case VK_FORMAT_B8G8R8A8_UNORM:                 return OGA_FORMAT_B8G8R8A8_UNORM;
        case VK_FORMAT_B8G8R8A8_SNORM:                 return OGA_FORMAT_B8G8R8A8_SNORM;
        case VK_FORMAT_B8G8R8A8_UINT:                  return OGA_FORMAT_B8G8R8A8_UINT;
        case VK_FORMAT_B8G8R8A8_SINT:                  return OGA_FORMAT_B8G8R8A8_SINT;
        case VK_FORMAT_B8G8R8A8_SRGB:                  return OGA_FORMAT_B8G8R8A8_SRGB;

        case VK_FORMAT_R16_UNORM:                      return OGA_FORMAT_R16_UNORM;
        case VK_FORMAT_R16_SNORM:                      return OGA_FORMAT_R16_SNORM;
        case VK_FORMAT_R16_UINT:                       return OGA_FORMAT_R16_UINT;
        case VK_FORMAT_R16_SINT:                       return OGA_FORMAT_R16_SINT;
        case VK_FORMAT_R16_SFLOAT:                     return OGA_FORMAT_R16_SFLOAT;

        case VK_FORMAT_R16G16_UNORM:                   return OGA_FORMAT_R16G16_UNORM;
        case VK_FORMAT_R16G16_SNORM:                   return OGA_FORMAT_R16G16_SNORM;
        case VK_FORMAT_R16G16_UINT:                    return OGA_FORMAT_R16G16_UINT;
        case VK_FORMAT_R16G16_SINT:                    return OGA_FORMAT_R16G16_SINT;
        case VK_FORMAT_R16G16_SFLOAT:                  return OGA_FORMAT_R16G16_SFLOAT;

        case VK_FORMAT_R16G16B16A16_UNORM:             return OGA_FORMAT_R16G16B16A16_UNORM;
        case VK_FORMAT_R16G16B16A16_SNORM:             return OGA_FORMAT_R16G16B16A16_SNORM;
        case VK_FORMAT_R16G16B16A16_UINT:              return OGA_FORMAT_R16G16B16A16_UINT;
        case VK_FORMAT_R16G16B16A16_SINT:              return OGA_FORMAT_R16G16B16A16_SINT;
        case VK_FORMAT_R16G16B16A16_SFLOAT:            return OGA_FORMAT_R16G16B16A16_SFLOAT;

        case VK_FORMAT_R32_SFLOAT:                     return OGA_FORMAT_R32_SFLOAT;
        case VK_FORMAT_R32_UINT:                       return OGA_FORMAT_R32_UINT;
        case VK_FORMAT_R32_SINT:                       return OGA_FORMAT_R32_SINT;

        case VK_FORMAT_R32G32_SFLOAT:                  return OGA_FORMAT_R32G32_SFLOAT;
        case VK_FORMAT_R32G32_UINT:                    return OGA_FORMAT_R32G32_UINT;
        case VK_FORMAT_R32G32_SINT:                    return OGA_FORMAT_R32G32_SINT;

        case VK_FORMAT_R32G32B32_SFLOAT:               return OGA_FORMAT_R32G32B32_SFLOAT;
        case VK_FORMAT_R32G32B32_UINT:                 return OGA_FORMAT_R32G32B32_UINT;
        case VK_FORMAT_R32G32B32_SINT:                 return OGA_FORMAT_R32G32B32_SINT;

        case VK_FORMAT_R32G32B32A32_SFLOAT:            return OGA_FORMAT_R32G32B32A32_SFLOAT;
        case VK_FORMAT_R32G32B32A32_UINT:              return OGA_FORMAT_R32G32B32A32_UINT;
        case VK_FORMAT_R32G32B32A32_SINT:              return OGA_FORMAT_R32G32B32A32_SINT;

        case VK_FORMAT_BC1_RGB_UNORM_BLOCK:            return OGA_FORMAT_BC1_RGB_UNORM_BLOCK;
        case VK_FORMAT_BC1_RGB_SRGB_BLOCK:             return OGA_FORMAT_BC1_RGB_SRGB_BLOCK;
        case VK_FORMAT_BC1_RGBA_UNORM_BLOCK:           return OGA_FORMAT_BC1_RGBA_UNORM_BLOCK;
        case VK_FORMAT_BC1_RGBA_SRGB_BLOCK:            return OGA_FORMAT_BC1_RGBA_SRGB_BLOCK;
        case VK_FORMAT_BC2_UNORM_BLOCK:                return OGA_FORMAT_BC2_UNORM_BLOCK;
        case VK_FORMAT_BC2_SRGB_BLOCK:                 return OGA_FORMAT_BC2_SRGB_BLOCK;
        case VK_FORMAT_BC3_UNORM_BLOCK:                return OGA_FORMAT_BC3_UNORM_BLOCK;
        case VK_FORMAT_BC3_SRGB_BLOCK:                 return OGA_FORMAT_BC3_SRGB_BLOCK;
        case VK_FORMAT_BC4_UNORM_BLOCK:                return OGA_FORMAT_BC4_UNORM_BLOCK;
        case VK_FORMAT_BC4_SNORM_BLOCK:                return OGA_FORMAT_BC4_SNORM_BLOCK;
        case VK_FORMAT_BC5_UNORM_BLOCK:                return OGA_FORMAT_BC5_UNORM_BLOCK;
        case VK_FORMAT_BC5_SNORM_BLOCK:                return OGA_FORMAT_BC5_SNORM_BLOCK;
        case VK_FORMAT_BC6H_UFLOAT_BLOCK:              return OGA_FORMAT_BC6H_UFLOAT_BLOCK;
        case VK_FORMAT_BC6H_SFLOAT_BLOCK:              return OGA_FORMAT_BC6H_SFLOAT_BLOCK;
        case VK_FORMAT_BC7_UNORM_BLOCK:                return OGA_FORMAT_BC7_UNORM_BLOCK;
        case VK_FORMAT_BC7_SRGB_BLOCK:                 return OGA_FORMAT_BC7_SRGB_BLOCK;

        //case OGA_FORMAT_ENUM_MAX:
        default:
            return (Oga_Format)0;
    }
    return (Oga_Format)0;
}

unit_local VkFormat _oga_vertex_attribute_type_to_vk_format(Oga_Vertex_Attribute_Type t) {
    switch(t) {
        case OGA_VERTEX_ATTRIBUTE_TYPE_F32:             return VK_FORMAT_R32_SFLOAT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_F32V2:           return VK_FORMAT_R32G32_SFLOAT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_F32V3:           return VK_FORMAT_R32G32B32_SFLOAT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_F32V4:           return VK_FORMAT_R32G32B32A32_SFLOAT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S32:             return VK_FORMAT_R32_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S32V2:           return VK_FORMAT_R32G32_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S32V3:           return VK_FORMAT_R32G32B32_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S32V4:           return VK_FORMAT_R32G32B32A32_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S16:             return VK_FORMAT_R16_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S16V2:           return VK_FORMAT_R16G16_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S16V3:           return VK_FORMAT_R16G16B16_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S16V4:           return VK_FORMAT_R16G16B16A16_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S8:              return VK_FORMAT_R8_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S8V2:            return VK_FORMAT_R8G8_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S8V3:            return VK_FORMAT_R8G8B8_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_S8V4:            return VK_FORMAT_R8G8B8A8_SINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U32:             return VK_FORMAT_R32_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U32V2:           return VK_FORMAT_R32G32_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U32V3:           return VK_FORMAT_R32G32B32_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U32V4:           return VK_FORMAT_R32G32B32A32_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U16:             return VK_FORMAT_R16_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U16V2:           return VK_FORMAT_R16G16_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U16V3:           return VK_FORMAT_R16G16B16_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U16V4:           return VK_FORMAT_R16G16B16A16_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8:              return VK_FORMAT_R8_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8V2:            return VK_FORMAT_R8G8_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8V3:            return VK_FORMAT_R8G8B8_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8V4:            return VK_FORMAT_R8G8B8A8_UINT;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8_NORMALIZED:   return VK_FORMAT_R8_UNORM;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8V2_NORMALIZED: return VK_FORMAT_R8G8_UNORM;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8V3_NORMALIZED: return VK_FORMAT_R8G8B8_UNORM;
        case OGA_VERTEX_ATTRIBUTE_TYPE_U8V4_NORMALIZED: return VK_FORMAT_R8G8B8A8_UNORM;
        default: assert(false); break;
    }
    assert(false);
    return VK_FORMAT_R8G8B8A8_UNORM;
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


unit_local inline string _str_vk_result(VkResult result) {
    switch ((s64)result) {
        case VK_SUCCESS:                                            return RSTR(VK_SUCCESS);
        case VK_NOT_READY:                                          return RSTR(VK_NOT_READY);
        case VK_TIMEOUT:                                            return RSTR(VK_TIMEOUT);
        case VK_EVENT_SET:                                          return RSTR(VK_EVENT_SET);
        case VK_EVENT_RESET:                                        return RSTR(VK_EVENT_RESET);
        case VK_INCOMPLETE:                                         return RSTR(VK_INCOMPLETE);
        case VK_ERROR_OUT_OF_HOST_MEMORY:                           return RSTR(VK_ERROR_OUT_OF_HOST_MEMORY);
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:                         return RSTR(VK_ERROR_OUT_OF_DEVICE_MEMORY);
        case VK_ERROR_INITIALIZATION_FAILED:                        return RSTR(VK_ERROR_INITIALIZATION_FAILED);
        case VK_ERROR_DEVICE_LOST:                                  return RSTR(VK_ERROR_DEVICE_LOST);
        case VK_ERROR_MEMORY_MAP_FAILED:                            return RSTR(VK_ERROR_MEMORY_MAP_FAILED);
        case VK_ERROR_LAYER_NOT_PRESENT:                            return RSTR(VK_ERROR_LAYER_NOT_PRESENT);
        case VK_ERROR_EXTENSION_NOT_PRESENT:                        return RSTR(VK_ERROR_EXTENSION_NOT_PRESENT);
        case VK_ERROR_FEATURE_NOT_PRESENT:                          return RSTR(VK_ERROR_FEATURE_NOT_PRESENT);
        case VK_ERROR_INCOMPATIBLE_DRIVER:                          return RSTR(VK_ERROR_INCOMPATIBLE_DRIVER);
        case VK_ERROR_TOO_MANY_OBJECTS:                             return RSTR(VK_ERROR_TOO_MANY_OBJECTS);
        case VK_ERROR_FORMAT_NOT_SUPPORTED:                         return RSTR(VK_ERROR_FORMAT_NOT_SUPPORTED);
        case VK_ERROR_FRAGMENTED_POOL:                              return RSTR(VK_ERROR_FRAGMENTED_POOL);
        case VK_ERROR_UNKNOWN:                                      return RSTR(VK_ERROR_UNKNOWN);
        case VK_ERROR_OUT_OF_POOL_MEMORY:                           return RSTR(VK_ERROR_OUT_OF_POOL_MEMORY);
        case VK_ERROR_INVALID_EXTERNAL_HANDLE:                      return RSTR(VK_ERROR_INVALID_EXTERNAL_HANDLE);
        case VK_ERROR_FRAGMENTATION:                                return RSTR(VK_ERROR_FRAGMENTATION);
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:               return RSTR(VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS);
        case VK_PIPELINE_COMPILE_REQUIRED:                          return RSTR(VK_PIPELINE_COMPILE_REQUIRED);
        case VK_ERROR_SURFACE_LOST_KHR:                             return RSTR(VK_ERROR_SURFACE_LOST_KHR);
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:                     return RSTR(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR);
        case VK_SUBOPTIMAL_KHR:                                     return RSTR(VK_SUBOPTIMAL_KHR);
        case VK_ERROR_OUT_OF_DATE_KHR:                              return RSTR(VK_ERROR_OUT_OF_DATE_KHR);
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:                     return RSTR(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
        case VK_ERROR_VALIDATION_FAILED_EXT:                        return RSTR(VK_ERROR_VALIDATION_FAILED_EXT);
        case VK_ERROR_INVALID_SHADER_NV:                            return RSTR(VK_ERROR_INVALID_SHADER_NV);
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: return RSTR(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:          return RSTR(VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT);
        case VK_THREAD_IDLE_KHR:                                    return RSTR(VK_THREAD_IDLE_KHR);
        case VK_THREAD_DONE_KHR:                                    return RSTR(VK_THREAD_DONE_KHR);
        case VK_OPERATION_DEFERRED_KHR:                             return RSTR(VK_OPERATION_DEFERRED_KHR);
        case VK_OPERATION_NOT_DEFERRED_KHR:                         return RSTR(VK_OPERATION_NOT_DEFERRED_KHR);

        case VK_RESULT_MAX_ENUM:
        default: return STR("<>");
    }
    return STR("<>");
}

#define _vk_assert1(expr) do { VkResult _res = expr; string _res_str = _str_vk_result(_res); assertmsgs(_res == VK_SUCCESS, tprint("Vulkan call '%s' failed: %s. If you see this, you're either doing something very wrong, or there is an internal error in Oga.", STR(#expr), _res_str)); } while(0)
#define _vk_assert2(expr) do { VkResult _res = expr; if (_res == VK_ERROR_OUT_OF_DEVICE_MEMORY) return OGA_ERROR_OUT_OF_DEVICE_MEMORY; if (_res == VK_ERROR_OUT_OF_HOST_MEMORY) return OGA_ERROR_STATE_ALLOCATION_FAILED;  string _res_str = _str_vk_result(_res); assertmsgs(_res == VK_SUCCESS, tprint("Vulkan call '%s' failed: %s. If you see this, you're either doing something very wrong, or there is an internal error in Oga.", STR(#expr), _res_str)); } while(0)


unit_local VkDebugUtilsMessengerEXT _vk_messenger;

#ifdef DEBUG
unit_local VkBool32 _vk_debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT           messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT                  messageTypes,
    const VkDebugUtilsMessengerCallbackDataEXT*      pCallbackData,
    void*                                            pUserData) {

    (void)messageTypes; (void)pUserData;
    string sev;

    if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
        sev = RSTR("WARNING");
    else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
        sev = RSTR("ERROR");
    else
        sev = RSTR("INFO");

    log(OGA_LOG_VERBOSE, "\n-----------------VK VALIDATION MESSAGE-----------------");
    log(OGA_LOG_VERBOSE, "Severity: %s", sev);
    if (pCallbackData->pMessageIdName)
        log(OGA_LOG_VERBOSE, "- Message ID: %s", STR(pCallbackData->pMessageIdName));
    if (pCallbackData->pMessage)
        log(OGA_LOG_VERBOSE, "- Message: %s", STR(pCallbackData->pMessage));

    return 0;
}
#endif

unit_local inline bool _vk_select_format(VkFormat *formats, u32 num_formats, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice vk_device, VkFormat *result) {
    for (u32 i = 0; i < num_formats; i += 1) {
        VkFormat format = formats[i];

        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(vk_device, format, &props);

        if (tiling == VK_IMAGE_TILING_LINEAR && (features & props.linearTilingFeatures) == features) {
            *result = format;
            return true;
        }
        if (tiling == VK_IMAGE_TILING_OPTIMAL && (features & props.optimalTilingFeatures) == features) {
            *result = format;
            return true;
        }
    }

    return false;
}

unit_local u8 _context_mem[(sizeof(Oga_Context)+sizeof(_Vk_Context_Internal))*1024];
unit_local u64 _allocated_contexts;
unit_local bool _has_dynamic_rendering = false;
unit_local VkInstance __instance = 0;
unit_local inline VkInstance _vk_instance(void) {

    if (!__instance) {
        
        u32 version_major = 0;
        u32 version_minor = 0;
        u32 version_patch = 0;
        {
            VkApplicationInfo query_app_info = (VkApplicationInfo){0};
            query_app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            query_app_info.pApplicationName = "Vulkan Version Check";
            query_app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            query_app_info.pEngineName = "No Engine";
            query_app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            query_app_info.apiVersion = VK_API_VERSION_1_0; 
        
            VkInstanceCreateInfo create_info = (VkInstanceCreateInfo){0};
            create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            create_info.pApplicationInfo = &query_app_info;
        
            VkInstance query_instance;
            VkResult result = vkCreateInstance(&create_info, 0, &query_instance);
            if (result != VK_SUCCESS) {
                print("Failed to create Vulkan query_instance.\n");
                return 0;
            }
        
            uint32_t device_count = 0;
            vkEnumeratePhysicalDevices(query_instance, &device_count, 0);
            if (device_count == 0) {
                print("No Vulkan-compatible devices found.\n");
                return 0;
            }
        
            VkPhysicalDevice devices[256];
            vkEnumeratePhysicalDevices(query_instance, &device_count, devices);
        
            for (uint32_t i = 0; i < device_count; i++) {
                VkPhysicalDeviceProperties properties;
                vkGetPhysicalDeviceProperties(devices[i], &properties);
        
                version_major = max(VK_VERSION_MAJOR(properties.apiVersion), version_major);
                version_minor = max(VK_VERSION_MINOR(properties.apiVersion), version_minor);
                version_patch = max(VK_VERSION_PATCH(properties.apiVersion), version_patch);
            }

            vkDestroyInstance(query_instance, 0);
        }
    
        log(OGA_LOG_VERBOSE, "Supported Vulkan Instance API version: %u.%u\n", version_major, version_minor);

        if (version_major >= 1 && version_minor >= 3) {
            _has_dynamic_rendering = true;
            
        }

        VkApplicationInfo app_info = (VkApplicationInfo){0};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = "Ostd App";
        app_info.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
        app_info.pEngineName = "Oga";
        app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        
        if (version_minor >= 3) {
            app_info.apiVersion = VK_API_VERSION_1_3;
        } else if (version_minor >= 2) {
            app_info.apiVersion = VK_API_VERSION_1_2;
        } else if (version_minor >= 1) {
            app_info.apiVersion = VK_API_VERSION_1_1;
        } else {
            app_info.apiVersion = VK_API_VERSION_1_0;
        }

        VkInstanceCreateInfo create_info = (VkInstanceCreateInfo){0};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &app_info;

#if OS_FLAGS & OS_FLAG_WINDOWS
        const char *required_extensions[] = {

#ifdef DEBUG
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif // _DEBUG
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
            "VK_KHR_get_physical_device_properties2"
        };
#elif OS_FLAGS & OS_FLAG_LINUX
    // Depending on your display server, pick one:
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        "VK_KHR_get_physical_device_properties2"
    };
#elif OS_FLAGS & OS_FLAG_MACOS
    // MoltenVK-specific extension for macOS
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        "VK_MVK_macos_surface",
        "VK_KHR_portability_enumeration",
        "VK_KHR_get_physical_device_properties2",
    };
    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#elif OS_FLAGS & OS_FLAG_IOS
    // MoltenVK-specific extension for iOS
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        "VK_MVK_ios_surface",
        "VK_KHR_portability_enumeration",
        "VK_KHR_get_physical_device_properties2",
    };
    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#elif OS_FLAGS & OS_FLAG_ANDROID
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
        "VK_KHR_get_physical_device_properties2"
    };

#else
    #error VK __instance extension query not set up for this OS
#endif
        
        u64 num_required_extensions = sizeof(required_extensions) / sizeof(char*) ;
        
        for (u64 i = 0; i < sizeof(required_extensions) / sizeof(char*); i += 1) {
            required_extensions[i] = required_extensions[i];
        }

        log(OGA_LOG_VERBOSE, "Looking for VkInstance extensions:");
        for (u64 i = 0; i < num_required_extensions; i += 1) {
            log(OGA_LOG_VERBOSE, "\t%s", STR(required_extensions[i]));
        }

        // #Portability dynamic rendering
        u32 num_available_extensions;
        _vk_assert1(vkEnumerateInstanceExtensionProperties(0, &num_available_extensions, 0));
        VkExtensionProperties *available_extensions = PushTempBuffer(VkExtensionProperties, num_available_extensions);
        memset(available_extensions, 0, num_available_extensions*sizeof(VkExtensionProperties));
        _vk_assert1(vkEnumerateInstanceExtensionProperties(0, &num_available_extensions, available_extensions));
        bool any_missing = false;
        for (u64 i = 0; i < num_required_extensions; i += 1) {
            const char *required = required_extensions[i];

            bool match = false;
            for (u64 j = 0; j < num_available_extensions; j += 1) {
                const char *available = available_extensions[j].extensionName;
                if (strings_match(STR(required), STR(available))) {
                    match = true;
                    break;
                }
            }

            if (match == false) {
                any_missing = true;
                log(OGA_LOG_VERBOSE, "Missing required vulkan extension '%s'", STR(required));
                log(OGA_LOG_VERBOSE, "List of available extensions:");
                for (u32 j = 0; j < num_available_extensions; j += 1) {
                    const char *available = available_extensions[j].extensionName;
                    log(OGA_LOG_VERBOSE, "\t%s", STR(available));
                }
                    
            } else {
                log(OGA_LOG_VERBOSE, "Found '%s'..", STR(required));
            }
        }

        assertmsg(!any_missing, "Basic vulkan extensions were missing, cannot proceed. Make sure you have a proper vulkan SDK installed.");

        create_info.ppEnabledExtensionNames = required_extensions;
        create_info.enabledExtensionCount = (u32)num_required_extensions;

#ifdef DEBUG
        const char *wanted_layers[] = {"VK_LAYER_KHRONOS_validation"};
        u32 num_wanted_layers = (u64)(sizeof(wanted_layers)/sizeof(char*));

        u32 num_available_layers;
        _vk_assert1(vkEnumerateInstanceLayerProperties(&num_available_layers, 0));

        VkLayerProperties *available_layers = PushTempBuffer(VkLayerProperties, num_available_layers);
        _vk_assert1(vkEnumerateInstanceLayerProperties(&num_available_layers, available_layers));

        const char *final_layers[32];
        u32 num_final_layers = 0;

        any_missing = false;
        for (u64 i = 0; i < num_wanted_layers; i += 1) {
            const char *wanted = wanted_layers[i];

            bool match = false;
            for (u64 j = 0; j < num_available_layers; j += 1) {
                const char *available = available_layers[j].layerName;
                if (strings_match(STR(wanted), STR(available))) {
                    match = true;
                    break;
                }
            }

            if (match == false) {
                any_missing = true;
                log(OGA_LOG_VERBOSE, "Missing wanted vulkan validation layer '%s'", STR(wanted));
                if (num_available_layers) {
                    log(OGA_LOG_VERBOSE, "List of available validation layers:");
                    for (u32 j = 0; j < num_available_layers; j += 1) {
                        const char *available = available_layers[j].layerName;
                        log(OGA_LOG_VERBOSE, "\t%s", STR(available));
                    }
                } else {
                    log(OGA_LOG_VERBOSE, "No validation layers available");
                }
            } else {
                final_layers[num_final_layers++] = wanted;
                log(OGA_LOG_VERBOSE, "Found validation layer %s", STR(wanted));
            }
        }

        create_info.enabledLayerCount = num_final_layers;
        create_info.ppEnabledLayerNames = final_layers;
#else
        create_info.enabledLayerCount = 0;
#endif

        _vk_assert1(vkCreateInstance(&create_info, 0, &__instance));
        log(OGA_LOG_VERBOSE, "Created a vulkan instance");

#ifdef DEBUG
        VkDebugUtilsMessengerCreateInfoEXT debug_create_info = (VkDebugUtilsMessengerCreateInfoEXT){0};
        debug_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

        debug_create_info.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

        debug_create_info.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

        debug_create_info.pfnUserCallback = _vk_debug_callback;

        void (*untyped)(void) = vkGetInstanceProcAddr(__instance, "vkCreateDebugUtilsMessengerEXT");
        PFN_vkCreateDebugUtilsMessengerEXT _vkCreateDebugUtilsMessengerEXT  = (PFN_vkCreateDebugUtilsMessengerEXT)*(PFN_vkCreateDebugUtilsMessengerEXT*)(void**)&untyped;

        if (_vkCreateDebugUtilsMessengerEXT(__instance, &debug_create_info, 0, &_vk_messenger) != VK_SUCCESS) {
            log(OGA_LOG_VERBOSE, "Failed creating vulkan debug messenger");
        } else {
            log(OGA_LOG_VERBOSE, "Created a vulkan debug messenger");
        }
#endif // DEBUG
    }


    return __instance;
}

void oga_reset(void) {
    void (*untyped)(void) = vkGetInstanceProcAddr(__instance, "vkDestroyDebugUtilsMessengerEXT");
    PFN_vkDestroyDebugUtilsMessengerEXT _vkDestroyDebugUtilsMessengerEXT  = (PFN_vkDestroyDebugUtilsMessengerEXT)*(PFN_vkDestroyDebugUtilsMessengerEXT*)(void**)&untyped;
    if (_vkDestroyDebugUtilsMessengerEXT) {
        _vkDestroyDebugUtilsMessengerEXT(_vk_instance(), _vk_messenger, 0);
    }
    vkDestroyInstance(_vk_instance(), 0);
    __instance = 0;
}

unit_local void *_vk_allocate(void *ud, size_t size, size_t alignment, VkSystemAllocationScope scope) {
    (void)scope;
    Allocator *allocator = (Allocator *)ud;
    void *p = allocator->proc(ALLOCATOR_ALLOCATE, allocator->data, 0, 0, size, alignment, 0);
#ifdef LOG_VULKAN_ALLOCATIONS
    string scope_str;
    if (scope == VK_SYSTEM_ALLOCATION_SCOPE_COMMAND) {
        scope_str = STR("Command");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_OBJECT) {
        scope_str = STR("Scope");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_CACHE) {
        scope_str = STR("Cache");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_DEVICE) {
        scope_str = STR("Device");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE) {
        scope_str = STR("Instance");
    }
    log(OGA_LOG_VERBOSE, "VK Allocation '%s'  %u bytes, %u alignment %u", scope_str, size, alignment, p);
    //sys_print_stack_trace(sys_get_stdout());
    //log(OGA_LOG_VERBOSE, "------------------------------------\n");
#endif
    return p;
}

unit_local void *_vk_reallocate(void *ud, void *old, size_t size, size_t alignment, VkSystemAllocationScope scope) {
    (void)scope;
#ifdef LOG_VULKAN_ALLOCATIONS
    string scope_str;
    if (scope == VK_SYSTEM_ALLOCATION_SCOPE_COMMAND) {
        scope_str = STR("Command");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_OBJECT) {
        scope_str = STR("Scope");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_CACHE) {
        scope_str = STR("Cache");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_DEVICE) {
        scope_str = STR("Device");
    } else if (scope == VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE) {
        scope_str = STR("Instance");
    }
    log(OGA_LOG_VERBOSE, "VK REallocation '%s'  %u bytes, %u alignment ", scope_str, size, alignment);
    //sys_print_stack_trace(sys_get_stdout());
    //log(OGA_LOG_VERBOSE, "------------------------------------\n");
#endif
    Allocator *allocator = (Allocator *)ud;
    return allocator->proc(ALLOCATOR_REALLOCATE, allocator->data, old, 0, size, alignment, 0);
}

unit_local void _vk_deallocate(void *ud, void *old) {
#ifdef LOG_VULKAN_ALLOCATIONS
    log(OGA_LOG_VERBOSE, "VK FREE %u", old);
#endif
    Allocator *allocator = (Allocator *)ud;
    allocator->proc(ALLOCATOR_FREE, allocator->data, old, 0, 0, 0, 0);
}

unit_local void _vk_internal_allocate(void *ud, size_t sz, VkInternalAllocationType t, VkSystemAllocationScope s) {
    (void)ud; (void)sz; (void)t; (void)s;
}
unit_local void _vk_internal_deallocate(void *ud, size_t sz, VkInternalAllocationType t, VkSystemAllocationScope s) {
    (void)ud; (void)sz; (void)t; (void)s;
}
unit_local inline VkAllocationCallbacks _vk_allocator(Allocator *a) {
    VkAllocationCallbacks c = (VkAllocationCallbacks){0};
    c.pUserData = a;
    c.pfnAllocation = _vk_allocate;
    c.pfnReallocation = _vk_reallocate;
    c.pfnFree = _vk_deallocate;
    c.pfnInternalAllocation = _vk_internal_allocate;
    c.pfnInternalFree = _vk_internal_deallocate;
    return c;
}


unit_local VkResult vkCreateSurfaceKHR(Surface_Handle h, VkSurfaceKHR *result) {
#if OS_FLAGS & OS_FLAG_WINDOWS
    VkWin32SurfaceCreateInfoKHR create_info = (VkWin32SurfaceCreateInfoKHR){0};
    create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    create_info.hwnd = (HWND)h;
    create_info.hinstance = GetModuleHandleW(0);
    return vkCreateWin32SurfaceKHR(_vk_instance(), &create_info, 0, result);
#elif OS_FLAGS & OS_FLAG_LINUX
    VkXlibSurfaceCreateInfoKHR create_info = (VkXlibSurfaceCreateInfoKHR){0};
    create_info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    create_info.window = (Window)_get_surface_state(h)->handle;
    create_info.dpy = _get_surface_state(h)->xlib_display;
    return vkCreateXlibSurfaceKHR(_vk_instance(), &create_info, 0, result);
#elif OS_FLAGS & OS_FLAG_MACOS
    VkMacOSSurfaceCreateInfoMVK create_info = (VkMacOSSurfaceCreateInfoMVK){0};
    create_info.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    create_info.pView = h;
    return vkCreateMacOSSurfaceMVK(_vk_instance(), &create_info, 0, result);
#elif OS_FLAGS & OS_FLAG_IOS
    VkIOSSurfaceCreateInfoMVK create_info = (VkIOSSurfaceCreateInfoMVK){0};
    create_info.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
    create_info.pView = h;
    return vkCreateIOSSurfaceMVK(_vk_instance(), &create_info, 0, result);
#elif OS_FLAGS & OS_FLAG_ANDROID
    VkAndroidSurfaceCreateInfoKHR create_info = (VkAndroidSurfaceCreateInfoKHR){0};
    create_info.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    create_info.window = (ANativeWindow*)h;
    return vkCreateAndroidSurfaceKHR(_vk_instance(), &create_info, 0, result);
#else
    #error VK surface creation not implemented for this os
#endif
}

u64 oga_query_devices(Oga_Device *buffer, u64 buffer_count) {

    u32 device_count;
    _vk_assert1(vkEnumeratePhysicalDevices(_vk_instance(), &device_count,  0));

    if (buffer) {
        memset(buffer, 0, buffer_count*sizeof(Oga_Device));
        VkPhysicalDevice vk_devices[256];
        _vk_assert1(vkEnumeratePhysicalDevices(_vk_instance(), &device_count,  vk_devices));

        // note(charlie) annoyingly, we need an existing surface to look for
        // surface support in engines. So, we just make a temporary invisible
        // surface and then delete it when done.
#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
        Surface_Desc desc = DEFAULT(Surface_Desc);
        desc.width = 1;
        desc.height = 1;
        desc.flags = SURFACE_FLAG_HIDDEN;
        Surface_Handle temp_sys_surface = sys_make_surface(desc);
#else
        Surface_Handle temp_sys_surface = sys_get_surface();
#endif

        VkSurfaceKHR temp_vk_surface;
        _vk_assert1(vkCreateSurfaceKHR(temp_sys_surface, &temp_vk_surface));
        for (u32 i = 0; i < min(device_count, (u32)buffer_count); i += 1) {
            Oga_Device *device = buffer + i;
            VkPhysicalDevice vk_device = vk_devices[i];
            
            VkDevice dummy_device;
            VkDeviceCreateInfo dummy_info = (VkDeviceCreateInfo){0};
            
            VkDeviceQueueCreateInfo dummy_queue = (VkDeviceQueueCreateInfo){0};
            dummy_queue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            dummy_queue.queueFamilyIndex = 0;
            dummy_queue.queueCount = 1;
            float one = 1;
            dummy_queue.pQueuePriorities = &one;
            
            dummy_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            dummy_info.queueCreateInfoCount = 1;
            dummy_info.pQueueCreateInfos = &dummy_queue;
            
            _vk_assert2(vkCreateDevice(vk_device, &dummy_info, 0, &dummy_device));

            ////
            // Yoink info

            VkPhysicalDeviceProperties props;
            VkPhysicalDeviceMemoryProperties mem_props;
            VkPhysicalDeviceFeatures features;

            vkGetPhysicalDeviceProperties(vk_device, &props);
            vkGetPhysicalDeviceMemoryProperties(vk_device, &mem_props);
            vkGetPhysicalDeviceFeatures(vk_device, &features);

            u32 ext_count;
            vkEnumerateDeviceExtensionProperties(vk_device, 0, &ext_count, 0);
            VkExtensionProperties *ext_props = PushTempBuffer(VkExtensionProperties, ext_count);
            vkEnumerateDeviceExtensionProperties(vk_device, 0, &ext_count, ext_props);

            u32 engine_family_count;
            vkGetPhysicalDeviceQueueFamilyProperties(vk_device, &engine_family_count, 0);
            VkQueueFamilyProperties *engine_family_props = PushTempBuffer(VkQueueFamilyProperties, engine_family_count);
            vkGetPhysicalDeviceQueueFamilyProperties(vk_device, &engine_family_count, engine_family_props);


            /////
            // Copy over info into our API

            ///
            // Kind
            if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
                device->kind = OGA_DEVICE_INTEGRATED;
            else if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                device->kind = OGA_DEVICE_DISCRETE;
            else if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU)
                device->kind = OGA_DEVICE_CPU;
            ///
            // Stuff
            memcpy(device->device_name_data, props.deviceName, min(sizeof(device->device_name_data), sizeof(props.deviceName)));
            device->device_name_length = c_style_strlen((const char*)device->device_name_data);
            device->vendor_id = (u64)props.vendorID;
            device->vendor_name = _str_vendor_id(props.vendorID);
            device->driver_version_raw = props.driverVersion;
            device->driver_version_length = _format_driver_version(props.vendorID, props.driverVersion, device->driver_version_data, sizeof(device->driver_version_data));
            
            device->api_version_raw = props.apiVersion;
            u32 major = VK_VERSION_MAJOR(device->api_version_raw);
            u32 minor = VK_VERSION_MINOR(device->api_version_raw);
            u32 patch = VK_VERSION_PATCH(device->api_version_raw);
            device->api_version_length = format_string(device->api_version_data, sizeof(device->api_version_data), "Vulkan %u.%u.%u", major, minor, patch);

            ///
            // Logical Engine flags


            device->engine_family_count = engine_family_count;
            for (u32 j = 0; j < engine_family_count; j += 1) {
                Oga_Logical_Engine_Family_Info *info = &device->engine_family_infos[j];
                VkQueueFamilyProperties family_props = engine_family_props[j];

                VkBool32 val;
                _vk_assert1(vkGetPhysicalDeviceSurfaceSupportKHR(vk_device, j, temp_vk_surface, &val));
                if (val) info->flags |= OGA_LOGICAL_ENGINE_PRESENT;

                info->engine_capacity = family_props.queueCount;

                if (family_props.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                    info->flags |= OGA_LOGICAL_ENGINE_GRAPHICS;
                if (family_props.queueFlags & VK_QUEUE_COMPUTE_BIT)
                    info->flags |= OGA_LOGICAL_ENGINE_COMPUTE;
                if (family_props.queueFlags & VK_QUEUE_TRANSFER_BIT)
                    info->flags |= OGA_LOGICAL_ENGINE_TRANSFER;
            }

            ///
            // Depth format

            VkFormat depth_formats[] =  {
                VK_FORMAT_D32_SFLOAT,
                VK_FORMAT_D32_SFLOAT_S8_UINT,
                VK_FORMAT_D24_UNORM_S8_UINT,
                VK_FORMAT_D16_UNORM
            };

            VkFormat vk_depth_format;
            bool ok = _vk_select_format(depth_formats, sizeof(depth_formats)/sizeof(VkFormat), VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT, vk_device, &vk_depth_format);

            if (!ok) {
                log(OGA_LOG_VERBOSE, ("WARNING: Could not find a supported depth format on this device."));
                vk_depth_format = VK_FORMAT_D32_SFLOAT;
            }

            (void)vk_depth_format;
            //device->depth_format = _vk_to_oga_format(vk_depth_format);

            /////
            // Memory heaps

            for (u32 j = 0; j < mem_props.memoryHeapCount; j += 1) {
                device->memory_heaps[j].size = (u64)mem_props.memoryHeaps[j].size;
            }
            device->memory_heap_count = mem_props.memoryHeapCount;
            
            VkBuffer dummy_vlist, dummy_ilist, dummy_ubuffer, dummy_sbuffer, dummy_dst, dummy_src;
            VkBufferCreateInfo dummy_buffer_info = (VkBufferCreateInfo){0};
            dummy_buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            dummy_buffer_info.size = 569;
            dummy_buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            dummy_buffer_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
            _vk_assert2(vkCreateBuffer(dummy_device, &dummy_buffer_info, 0, &dummy_vlist));
            dummy_buffer_info.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
            _vk_assert2(vkCreateBuffer(dummy_device, &dummy_buffer_info, 0, &dummy_ilist));
            dummy_buffer_info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
            _vk_assert2(vkCreateBuffer(dummy_device, &dummy_buffer_info, 0, &dummy_ubuffer));
            dummy_buffer_info.usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
            _vk_assert2(vkCreateBuffer(dummy_device, &dummy_buffer_info, 0, &dummy_sbuffer));
            dummy_buffer_info.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
            _vk_assert2(vkCreateBuffer(dummy_device, &dummy_buffer_info, 0, &dummy_dst));
            dummy_buffer_info.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
            _vk_assert2(vkCreateBuffer(dummy_device, &dummy_buffer_info, 0, &dummy_src));
            
            VkImage dummy_image_1d, dummy_image_2d, dummy_image_3d;
            VkImage dummy_fbuffer_1d, dummy_fbuffer_2d, dummy_fbuffer_3d;
            VkImageCreateInfo dummy_image_info = (VkImageCreateInfo){0};
            dummy_image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            dummy_image_info.extent.width = props.limits.maxImageDimension1D;
            dummy_image_info.extent.height = 1;
            dummy_image_info.extent.depth = 1;
            dummy_image_info.mipLevels = 1;
            dummy_image_info.arrayLayers = 1;
            dummy_image_info.format = VK_FORMAT_R8G8B8A8_UNORM;
            dummy_image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
            dummy_image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            dummy_image_info.samples = VK_SAMPLE_COUNT_1_BIT;
            dummy_image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            
            dummy_image_info.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
            dummy_image_info.imageType = VK_IMAGE_TYPE_1D;
            _vk_assert2(vkCreateImage(dummy_device, &dummy_image_info, 0, &dummy_image_1d));
            dummy_image_info.usage = VK_IMAGE_USAGE_STORAGE_BIT;
            dummy_image_info.imageType = VK_IMAGE_TYPE_1D;
            _vk_assert2(vkCreateImage(dummy_device, &dummy_image_info, 0, &dummy_fbuffer_1d));
            dummy_image_info.extent.width = props.limits.maxImageDimension2D;
            dummy_image_info.extent.height = props.limits.maxImageDimension2D;
            dummy_image_info.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
            dummy_image_info.imageType = VK_IMAGE_TYPE_2D;
            _vk_assert2(vkCreateImage(dummy_device, &dummy_image_info, 0, &dummy_image_2d));
            dummy_image_info.usage = VK_IMAGE_USAGE_STORAGE_BIT;
            dummy_image_info.imageType = VK_IMAGE_TYPE_2D;
            _vk_assert2(vkCreateImage(dummy_device, &dummy_image_info, 0, &dummy_fbuffer_2d));
            dummy_image_info.extent.width = props.limits.maxImageDimension3D;
            dummy_image_info.extent.height = props.limits.maxImageDimension3D;
            dummy_image_info.extent.depth = 4;
            dummy_image_info.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
            dummy_image_info.imageType = VK_IMAGE_TYPE_3D;
            _vk_assert2(vkCreateImage(dummy_device, &dummy_image_info, 0, &dummy_image_3d));
            dummy_image_info.usage = VK_IMAGE_USAGE_STORAGE_BIT;
            dummy_image_info.imageType = VK_IMAGE_TYPE_3D;
            _vk_assert2(vkCreateImage(dummy_device, &dummy_image_info, 0, &dummy_fbuffer_3d));
            
            for (u32 j = 0; j < mem_props.memoryTypeCount; j += 1) {
                VkMemoryType type = mem_props.memoryTypes[j];
                Oga_Memory_Heap *heap = &device->memory_heaps[type.heapIndex];
                if (type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
                    heap->properties |= OGA_MEMORY_PROPERTY_GPU_LOCAL;
                if (type.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
                    heap->properties |= OGA_MEMORY_PROPERTY_GPU_TO_CPU_MAPPABLE;
                if (type.propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
                    heap->properties |= OGA_MEMORY_PROPERTY_GPU_TO_CPU_REFLECTED;
                if (type.propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
                    heap->properties |= OGA_MEMORY_PROPERTY_GPU_TO_CPU_CACHED;
                VkMemoryRequirements req = (VkMemoryRequirements){0};
                vkGetBufferMemoryRequirements(dummy_device, dummy_vlist, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_VERTEX_LIST;
                vkGetBufferMemoryRequirements(dummy_device, dummy_ilist, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_INDEX_LIST;
                vkGetBufferMemoryRequirements(dummy_device, dummy_ubuffer, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_FAST_READONLY_DATA_BLOCK;
                vkGetBufferMemoryRequirements(dummy_device, dummy_sbuffer, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_LARGE_READWRITE_DATA_BLOCK;
                vkGetBufferMemoryRequirements(dummy_device, dummy_src, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_COPY_DST;
                vkGetBufferMemoryRequirements(dummy_device, dummy_dst, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_COPY_SRC;
                vkGetImageMemoryRequirements(dummy_device, dummy_image_1d, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_IMAGE_1D;
                vkGetImageMemoryRequirements(dummy_device, dummy_image_2d, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_IMAGE_2D;
                vkGetImageMemoryRequirements(dummy_device, dummy_image_3d, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_IMAGE_3D;
                vkGetImageMemoryRequirements(dummy_device, dummy_fbuffer_1d, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_FBUFFER_1D;
                vkGetImageMemoryRequirements(dummy_device, dummy_fbuffer_2d, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_FBUFFER_2D;
                vkGetImageMemoryRequirements(dummy_device, dummy_fbuffer_3d, &req);
                if (j & req.memoryTypeBits)
                    heap->supported_usage_flags |= OGA_MEMORY_USAGE_FBUFFER_3D;
                    
                device->limits.image_memory_granularity = max(device->limits.image_memory_granularity, (u64)req.alignment);
                
            }
            
            for (u32 j = 0; j < device->memory_heap_count; j += 1) {
                if (device->memory_heaps[j].properties & OGA_MEMORY_PROPERTY_GPU_LOCAL)
                    device->total_gpu_local_memory += device->memory_heaps[j].size;
            }
            
            vkDestroyBuffer(dummy_device, dummy_vlist, 0);
            vkDestroyBuffer(dummy_device, dummy_ilist, 0);
            vkDestroyBuffer(dummy_device, dummy_ubuffer, 0);
            vkDestroyBuffer(dummy_device, dummy_sbuffer, 0);
            vkDestroyBuffer(dummy_device, dummy_src, 0);
            vkDestroyBuffer(dummy_device, dummy_dst, 0);
            vkDestroyImage(dummy_device, dummy_image_1d, 0);
            vkDestroyImage(dummy_device, dummy_image_2d, 0);
            vkDestroyImage(dummy_device, dummy_image_3d, 0);
            vkDestroyImage(dummy_device, dummy_fbuffer_1d, 0);
            vkDestroyImage(dummy_device, dummy_fbuffer_2d, 0);
            vkDestroyImage(dummy_device, dummy_fbuffer_3d, 0);
            
            /////
            // Feature flags
            if (props.limits.timestampComputeAndGraphics) {
                device->features |= (OGA_DEVICE_FEATURE_GRAPHICS_TIMESTAMP |
                                     OGA_DEVICE_FEATURE_COMPUTE_TIMESTAMP);
            }
            
            VkPresentModeKHR present_modes[32];
            u32 present_mode_count = 32;
            _vk_assert1(vkGetPhysicalDeviceSurfacePresentModesKHR(vk_device, temp_vk_surface, &present_mode_count, present_modes));
            for (u32 j = 0; j < present_mode_count; j += 1) {
                if (present_modes[j] == VK_PRESENT_MODE_MAILBOX_KHR)
                    device->features |= OGA_DEVICE_FEATURE_PRESENT_MAILBOX;
            }
            
            //if (features.depthClamp)
            //    device->features |= OGA_DEVICE_FEATURE_DEPTH_CLAMP;
                
            /////
            // Limits

            device->limits.max_program_view_sets_per_stage = props.limits.maxPerStageResources;
            device->limits.max_fast_data_blocks_per_stage = props.limits.maxPerStageDescriptorUniformBuffers;
            device->limits.max_large_data_blocks_per_stage = props.limits.maxPerStageDescriptorStorageBuffers;
            device->limits.max_images_per_stage = props.limits.maxPerStageDescriptorSampledImages;
            device->limits.max_fbuffers_per_stage = props.limits.maxPerStageDescriptorStorageImages;
            device->limits.max_samplers_per_stage = props.limits.maxPerStageDescriptorSamplers;
            device->limits.max_fast_data_blocks_per_layout = props.limits.maxDescriptorSetUniformBuffers;
            device->limits.max_large_data_blocks_per_layout = props.limits.maxDescriptorSetStorageBuffers;
            device->limits.max_images_per_layout = props.limits.maxDescriptorSetSampledImages;
            device->limits.max_fbuffers_per_layout = props.limits.maxDescriptorSetStorageImages;
            device->limits.max_samplers_per_layout = props.limits.maxDescriptorSetSamplers;
            device->limits.max_memory_allocations = props.limits.maxMemoryAllocationCount;
            device->limits.max_sampler_allocations = props.limits.maxSamplerAllocationCount;
            device->limits.max_image_dimension_1d = props.limits.maxImageDimension1D;
            device->limits.max_image_dimension_2d = props.limits.maxImageDimension2D;
            device->limits.max_image_dimension_3d = props.limits.maxImageDimension3D;
            device->limits.max_fast_access_data_block_size = props.limits.maxUniformBufferRange;
            device->limits.max_vertex_layout_attributes = props.limits.maxVertexInputAttributes;
            device->limits.max_vertex_layout_bindings = props.limits.maxVertexInputBindings;
            device->limits.max_vertex_layout_attribute_offset = props.limits.maxVertexInputAttributeOffset;
            device->limits.max_vertex_layout_binding_stride = props.limits.maxVertexInputBindingStride;
            device->limits.max_fragment_stage_output_attachments = props.limits.maxFragmentOutputAttachments;
            device->limits.max_sampler_anisotropy = props.limits.maxSamplerAnisotropy;
            device->limits.max_viewports = props.limits.maxViewports;
            device->limits.max_viewport_width = props.limits.maxViewportDimensions[0];
            device->limits.max_viewport_height = props.limits.maxViewportDimensions[1];
            device->limits.max_framebuffer_width = props.limits.maxFramebufferWidth;
            device->limits.max_framebuffer_height = props.limits.maxFramebufferHeight;
            device->limits.max_render_attachments = props.limits.maxColorAttachments;
            device->limits.min_memory_map_alignment = props.limits.minMemoryMapAlignment;
            for (u64 f = 1; f < 64; f = f << 1)
                if (props.limits.framebufferColorSampleCounts & f) device->limits.supported_sample_counts_render_pass |= f;
            for (u64 f = 1; f < 64; f = f << 1)
                if (props.limits.sampledImageColorSampleCounts & f) device->limits.supported_sample_counts_image_float |= f;
            for (u64 f = 1; f < 64; f = f << 1)
                if (props.limits.storageImageSampleCounts & f) device->limits.supported_sample_counts_fbuffer_float |= f;
            for (u64 f = 1; f < 64; f = f << 1)
                if (props.limits.sampledImageIntegerSampleCounts & f) device->limits.supported_sample_counts_image_int |= f;
            for (u64 f = 1; f < 64; f = f << 1)
                if (props.limits.storageImageSampleCounts & f) device->limits.supported_sample_counts_fbuffer_int |= f;

            device->limits.memory_granularity = max(device->limits.memory_granularity, (u64)props.limits.bufferImageGranularity);
            device->limits.memory_granularity = max(device->limits.memory_granularity, (u64)props.limits.minMemoryMapAlignment);
            device->limits.memory_granularity = max(device->limits.memory_granularity, (u64)props.limits.minTexelBufferOffsetAlignment);
            device->limits.memory_granularity = max(device->limits.memory_granularity, (u64)props.limits.minUniformBufferOffsetAlignment);
            device->limits.memory_granularity = max(device->limits.memory_granularity, (u64)props.limits.optimalBufferCopyOffsetAlignment);
            device->limits.memory_granularity = max(device->limits.memory_granularity, (u64)props.limits.optimalBufferCopyRowPitchAlignment);
            
            device->limits.image_memory_granularity = max(device->limits.image_memory_granularity, device->limits.memory_granularity);
            device->limits.fbuffer_memory_granularity = device->limits.image_memory_granularity;

            /////
            // Surface formats
            
            u32 vk_formats_count = 512;
            _vk_assert1(vkGetPhysicalDeviceSurfaceFormatsKHR(vk_device, temp_vk_surface, &vk_formats_count, 0));
            VkSurfaceFormatKHR vk_formats[512];
            _vk_assert1(vkGetPhysicalDeviceSurfaceFormatsKHR(vk_device, temp_vk_surface, &vk_formats_count, vk_formats));
            
            for (u32 j = 0; j < vk_formats_count; j += 1) {
                if (vk_formats[j].colorSpace != VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) continue;
                Oga_Format oga_format = _vk_to_oga_format(vk_formats[j].format);
                if (oga_format != 0) {
                    device->supported_surface_formats[device->supported_surface_format_count++] = oga_format;
                }
            }
            
            
            
            
            
            vkDestroyDevice(dummy_device, 0);
        
            device->id = vk_device;
        }
        vkDestroySurfaceKHR(_vk_instance(), temp_vk_surface, 0);

#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
        surface_close(temp_sys_surface);
#endif
    }

    return device_count;
}

Oga_Device *oga_get_devices(Allocator a, u64 *count) {
    *count = oga_query_devices(0, 0);

    Oga_Device *devices = NewBuffer(a, Oga_Device, *count);
    oga_query_devices(devices, *count);

    return devices;
}


Oga_Result oga_init_context(Oga_Device target_device, Oga_Context_Desc desc, Oga_Context **context) {

    if ((desc.enabled_features & target_device.features) != desc.enabled_features) {
        return OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES;
    }

    *context = (Oga_Context*)&_context_mem[(sizeof(Oga_Context)+sizeof(_Vk_Context_Internal))*_allocated_contexts++];
    if (!*context) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }
    Oga_Context *c = *context;
    *c = (Oga_Context){0};
    c->state_allocator = desc.state_allocator;
    c->internal = c+1;
    if (!c->state_allocator.proc) {
        Allocator a;
        a.proc = oga_state_allocator_proc;
        c->default_allocator_data = (Oga_State_Allocator_Data) {0};
        a.data = &c->default_allocator_data;
        c->state_allocator = a;
    }
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)c->internal;
    
    internal->vk_allocs = _vk_allocator(&c->state_allocator);

    VkPhysicalDeviceFeatures enabled_features = (VkPhysicalDeviceFeatures){0};
    // if (desc.enabled_features & OGA_DEVICE_FEATURE_XXXX) enabled_features.xxxx = true;
    
    // if (target_device.features & OGA_DEVICE_FEATURE_DEPTH_CLAMP) {
    //     enabled_features.depthClamp = true;
    // }
    
    enabled_features.samplerAnisotropy = VK_TRUE;
    // todo(charlie) device feature flag
    enabled_features.fragmentStoresAndAtomics = VK_TRUE;
    
    // We need to do this because driver people simply hate programmers
    VkPhysicalDeviceCoherentMemoryFeaturesAMD device_coherent_memory_features_amd
        = (VkPhysicalDeviceCoherentMemoryFeaturesAMD) {0};
        device_coherent_memory_features_amd.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD;
    
    VkPhysicalDeviceFeatures2 enabled_features2 = (VkPhysicalDeviceFeatures2){0};
    enabled_features2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR;
    enabled_features2.pNext = &device_coherent_memory_features_amd;
    
    {
        void (*untyped)(void) = vkGetInstanceProcAddr(__instance, "vkGetPhysicalDeviceFeatures2KHR");
        if (!untyped) {
            untyped = vkGetInstanceProcAddr(__instance, "vkGetPhysicalDeviceFeatures2");
        }
        assert(untyped);
        
        PFN_vkGetPhysicalDeviceFeatures2KHR vkGetPhysicalDeviceFeatures2KHR_ 
            = (PFN_vkGetPhysicalDeviceFeatures2KHR)*(PFN_vkGetPhysicalDeviceFeatures2KHR*)(void**)&untyped;
        
        vkGetPhysicalDeviceFeatures2KHR_(target_device.id, &enabled_features2);
    }
    
    
    enabled_features2.features = enabled_features;
    
    // todo(charlie) oga context feature flags
    VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT fragment_shader_interlock
        = (VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT) {0};
    fragment_shader_interlock.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT;
    fragment_shader_interlock.fragmentShaderSampleInterlock = VK_FALSE;
    fragment_shader_interlock.fragmentShaderPixelInterlock = VK_TRUE;
    fragment_shader_interlock.fragmentShaderShadingRateInterlock = VK_FALSE;
    
    device_coherent_memory_features_amd.pNext = &fragment_shader_interlock;

    VkDeviceQueueCreateInfo engine_infos[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES] = {0};

    u64 engines_desc_count = 0;
    for (u64 family_index = 0; family_index < OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES; family_index += 1) {
        Oga_Logical_Engines_Create_Desc engines_desc = desc.engine_create_descs[family_index];
        if (engines_desc.count > 0) {

            if (family_index >= target_device.engine_family_count) {
                return OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE;
            }

            Oga_Logical_Engine_Family_Info family = target_device.engine_family_infos[family_index];
            if (engines_desc.count > family.engine_capacity) {
                return OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW;
            }

            VkDeviceQueueCreateInfo *info = &engine_infos[engines_desc_count];
            info->sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            info->queueFamilyIndex = (u32)family_index;
            info->queueCount = (u32)engines_desc.count;
            info->pQueuePriorities = engines_desc.priorities;

            engines_desc_count += 1;
        }
    }

    // #Portability dynamic rendering
    VkPhysicalDeviceDynamicRenderingFeatures dynamic_rendering = (VkPhysicalDeviceDynamicRenderingFeatures){0};
    dynamic_rendering.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES;
    dynamic_rendering.dynamicRendering = true;
    
    VkPhysicalDeviceVulkan13Features vk13_features = (VkPhysicalDeviceVulkan13Features){0};
    vk13_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
    vk13_features.dynamicRendering = true;
    
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(target_device.id, &props);

    VkDeviceCreateInfo info = (VkDeviceCreateInfo) {0};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    info.pEnabledFeatures = 0;
    info.pNext = &enabled_features2;
    info.queueCreateInfoCount = (u32)engines_desc_count;
    info.pQueueCreateInfos = engine_infos;
    
    void **pp_next = &fragment_shader_interlock.pNext;
    
    
    internal->vk_version_major = VK_VERSION_MAJOR(props.apiVersion);
    internal->vk_version_minor = VK_VERSION_MINOR(props.apiVersion);
    internal->vk_version_patch = VK_VERSION_PATCH(props.apiVersion);
    
    string name = (string){target_device.device_name_length, target_device.device_name_data};
    string api = (string){target_device.api_version_length, target_device.api_version_data};
    
    
    char **names = PushTempBuffer(char*, 32);
    if (internal->vk_version_major == 1 && internal->vk_version_minor < 3) {
        
        uint32_t existing_count = 0;
        vkEnumerateDeviceExtensionProperties(target_device.id, 0, &existing_count, 0);
        VkExtensionProperties *existing_exts = PushTempBuffer(VkExtensionProperties, existing_count);
        vkEnumerateDeviceExtensionProperties(target_device.id, 0, &existing_count, existing_exts);
        
        bool ext_depth_stencil_resolve = false;
        bool ext_create_renderpass2 = false;
        bool ext_dynamic_rendering = false;
        
        for (u64 i = 0; i < existing_count; i += 1) {
            string existing = STR(existing_exts[i].extensionName);
            
            if (strings_match(existing, STR("VK_KHR_depth_stencil_resolve")))
                ext_depth_stencil_resolve = true;
            if (strings_match(existing, STR("VK_KHR_create_renderpass2")))
                ext_create_renderpass2 = true;
            if (strings_match(existing, STR("VK_KHR_dynamic_rendering")))
                ext_dynamic_rendering = true;
        }
        
        
        
        info.enabledExtensionCount = 0;
        internal->dynamic_rendering = ext_dynamic_rendering;
        names[info.enabledExtensionCount++] = "VK_KHR_dynamic_rendering";
        if (internal->vk_version_minor <= 1) {
            internal->dynamic_rendering &= ext_depth_stencil_resolve;
            names[info.enabledExtensionCount++] = "VK_KHR_depth_stencil_resolve";
            internal->dynamic_rendering &= ext_create_renderpass2;
            names[info.enabledExtensionCount++] = "VK_KHR_create_renderpass2";
        }
            
        
        names[info.enabledExtensionCount++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME
        ;
        
        info.ppEnabledExtensionNames = (const char*const*)names;
        
        // todo(charlie) feature flags
        if (target_device.vendor_id == VENDOR_ID_AMD) {
            names[info.enabledExtensionCount++] = "VK_AMD_device_coherent_memory";
        }
        names[info.enabledExtensionCount++] = "VK_EXT_fragment_shader_interlock";
        internal->dynamic_rendering_is_extension = true;
    } else {
        internal->dynamic_rendering = true;
        internal->dynamic_rendering_is_extension = false;
        
        // todo(charlie) feature flags
        if (target_device.vendor_id == VENDOR_ID_AMD) {
            names[info.enabledExtensionCount++] = "VK_AMD_device_coherent_memory";
        }
        names[info.enabledExtensionCount++] = "VK_EXT_fragment_shader_interlock";
        names[info.enabledExtensionCount++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
        info.ppEnabledExtensionNames = (const char*const*)names;
    }
    
    
    log(OGA_LOG_VERBOSE, "Enabling %i VkDevice extensions:", info.enabledExtensionCount);
    for (u32 i = 0; i < info.enabledExtensionCount; i += 1) {
        log(OGA_LOG_VERBOSE, "\t%s", STR(names[i]));
    }
    
    log(OGA_LOG_VERBOSE, "Dynamic rendering enabled: %b", internal->dynamic_rendering);
    
    if (internal->dynamic_rendering) {
        if (internal->dynamic_rendering_is_extension) {
            void (*untyped)(void) = vkGetInstanceProcAddr(__instance, "vkCmdBeginRenderingKHR");
            internal->vkCmdBeginRenderingKHR  = (PFN_vkCmdBeginRenderingKHR)*(PFN_vkCmdBeginRenderingKHR*)(void**)&untyped;
            untyped = vkGetInstanceProcAddr(__instance, "vkCmdEndRenderingKHR");
            internal->vkCmdEndRenderingKHR  = (PFN_vkCmdEndRenderingKHR)*(PFN_vkCmdEndRenderingKHR*)(void**)&untyped;
            
            *pp_next = &dynamic_rendering;
            
        } else {
            void (*untyped)(void) = vkGetInstanceProcAddr(__instance, "vkCmdBeginRendering");
            internal->vkCmdBeginRenderingKHR  = (PFN_vkCmdBeginRenderingKHR)*(PFN_vkCmdBeginRenderingKHR*)(void**)&untyped;
            untyped = vkGetInstanceProcAddr(__instance, "vkCmdEndRendering");
            internal->vkCmdEndRenderingKHR  = (PFN_vkCmdEndRenderingKHR)*(PFN_vkCmdEndRenderingKHR*)(void**)&untyped;
            
            *pp_next = &vk13_features;
        }
        
    }

    _vk_assert2(vkCreateDevice(target_device.id, &info, &internal->vk_allocs, (VkDevice*)&c->id));
    c->device = target_device;
    
    for (u64 family_index = 0; family_index < OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES; family_index += 1) {
        Oga_Logical_Engines_Create_Desc engines_desc = desc.engine_create_descs[family_index];
        Oga_Logical_Engine_Group *group = &c->engines_by_family[family_index];
        for (u64 engine_index = 0; engine_index < engines_desc.count; engine_index += 1) {
            Oga_Logical_Engine *engine = &group->engines[engine_index];
            vkGetDeviceQueue(
                c->id,
                (u32)family_index,
                (u32)engine_index,
                (VkQueue*)&engine->id
            );
            engine->index = (u32)engine_index;
        }
    }
    
    log(OGA_LOG_VERBOSE, "Initted a Oga_Context for device '%s', api version '%s'", name, api);
    
    return OGA_OK;
}
void oga_uninit_context(Oga_Context *context) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    _vk_assert1(vkDeviceWaitIdle(context->id));
    vkDestroyDevice(context->id, &internal->vk_allocs);
    
    Allocator a = context->state_allocator;
    *context = (Oga_Context){0};
    deallocate(a, context);
}

void oga_wait_engine_idle(Oga_Logical_Engine engine) {
    _vk_assert1(vkQueueWaitIdle(engine.id));
}
void oga_wait_context_idle(Oga_Context *context) {
    _vk_assert1(vkDeviceWaitIdle(context->id));
}

unit_local void _vk_decide_stage_and_access_mask(VkImageLayout layout, VkPipelineStageFlags *stage, VkAccessFlags *access) {
    if (layout == VK_IMAGE_LAYOUT_UNDEFINED) {
        *access = 0;
        *stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    } else if (layout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR) {
        *access = VK_ACCESS_MEMORY_READ_BIT;
        *stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    } else if (layout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL) {
        *access = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        *stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    } else if (layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        *access = VK_ACCESS_SHADER_READ_BIT;
        *stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    } else if (layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        *access = VK_ACCESS_TRANSFER_WRITE_BIT;
        *stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    } else if (layout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) {
        *access = VK_ACCESS_TRANSFER_READ_BIT;
        *stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    } else if (layout == VK_IMAGE_LAYOUT_GENERAL) {
        *access = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
        *stage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
    } else {
        assertmsgs(false, tprint("Unhandled image layout '%u' for transitioning (internal error)\n", layout));
    }
}

unit_local void _vk_image_barrier_helper(VkCommandBuffer cmd, VkImage image, VkImageLayout old_layout, VkImageLayout new_layout) {
    VkPipelineStageFlags src_stage, dst_stage;
    VkAccessFlags src_access, dst_access;
    
    _vk_decide_stage_and_access_mask(old_layout, &src_stage, &src_access);
    _vk_decide_stage_and_access_mask(new_layout, &dst_stage, &dst_access);
    
    VkImageMemoryBarrier barrier = (VkImageMemoryBarrier){0};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = old_layout;
    barrier.newLayout = new_layout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;
    barrier.pNext = 0;
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;

    vkCmdPipelineBarrier(cmd, src_stage, dst_stage, 0, 0, 0, 0, 0, 1, &barrier);
}

Oga_Result oga_init_swapchain(Oga_Context *context, Oga_Swapchain_Desc desc, Oga_Swapchain **swapchain) {
    *swapchain = allocate(context->state_allocator, sizeof(Oga_Swapchain) + sizeof(_Vk_Swapchain_State));
    if (!*swapchain) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }
    **swapchain = (Oga_Swapchain){0};
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    _Vk_Swapchain_State *state = (_Vk_Swapchain_State*)(*swapchain+1);
    
    if (vkCreateSurfaceKHR(desc.surface, &state->vk_surface) != VK_SUCCESS) {
        deallocate((*swapchain)->context->state_allocator, swapchain);
        return OGA_INIT_SWAPCHAIN_ERROR_SURFACE_REJECTED;
    }
    
    (*swapchain)->id = state;
    
    VkSurfaceCapabilitiesKHR cap;
    _vk_assert2(vkGetPhysicalDeviceSurfaceCapabilitiesKHR((VkPhysicalDevice)context->device.id, state->vk_surface, &cap));
    
    u32 image_count = clamp((u32)desc.requested_image_count, cap.minImageCount, min(cap.maxImageCount, MAX_SWAPCHAIN_IMAGES));
    (*swapchain)->image_count = (u64)image_count;
    
    
    VkPresentModeKHR vk_present_mode = VK_PRESENT_MODE_FIFO_KHR;
    if (desc.present_mode == OGA_PRESENT_MODE_IMMEDIATE) {
        VkPresentModeKHR present_modes[32];
        u32 present_mode_count = 32;
        _vk_assert2(vkGetPhysicalDeviceSurfacePresentModesKHR((VkPhysicalDevice)context->device.id, state->vk_surface, &present_mode_count, present_modes));
        for (u32 i = 0; i < present_mode_count; i += 1) {
            if (present_modes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                vk_present_mode = VK_PRESENT_MODE_IMMEDIATE_KHR;
                break;
            }
        }
    } else if (desc.present_mode == OGA_PRESENT_MODE_VSYNC) {
        vk_present_mode = VK_PRESENT_MODE_FIFO_KHR;
        
    } else if (desc.present_mode == OGA_PRESENT_MODE_VSYNC_MAILBOX && context->device.features & OGA_DEVICE_FEATURE_PRESENT_MAILBOX) {
        vk_present_mode = VK_PRESENT_MODE_MAILBOX_KHR;
    } else {
        deallocate((*swapchain)->context->state_allocator, swapchain);
        return OGA_INIT_SWAPCHAIN_ERROR_UNSUPPORTED_PRESENT_MODE;
    }
    
    VkCompositeAlphaFlagBitsKHR composite_alpha = (VkCompositeAlphaFlagBitsKHR)0;
    if (cap.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)
        composite_alpha |= VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    else if (cap.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR )
        composite_alpha |= VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR ;
    else if (cap.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR )
        composite_alpha |= VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR ;
    else if (cap.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR )
        composite_alpha |= VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR ;
    
    VkSwapchainCreateInfoKHR info = (VkSwapchainCreateInfoKHR){0};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    info.flags = 0;
    info.surface = state->vk_surface;
    info.minImageCount = image_count;
    info.imageFormat = _oga_to_vk_format(desc.image_format);
    info.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    info.imageExtent.width = (u32)desc.width;
    info.imageExtent.height = (u32)desc.height;
    info.imageArrayLayers = 0;
    info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    info.preTransform = cap.currentTransform;
    info.compositeAlpha = composite_alpha;
    info.presentMode = vk_present_mode;
    info.clipped = VK_TRUE;
    info.oldSwapchain = 0;
    info.imageArrayLayers = 1;
    
    _vk_assert2(vkCreateSwapchainKHR((VkDevice)context->id, &info, &internal->vk_allocs, &state->vk_swapchain));
    
    VkImage vk_images[MAX_SWAPCHAIN_IMAGES];
    
    vkGetSwapchainImagesKHR((VkDevice)context->id, state->vk_swapchain, (u32*)&(*swapchain)->image_count, vk_images);
    
    (*swapchain)->image_format = desc.image_format;
    
    VkCommandPool transition_pool = 0;
    VkCommandPoolCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    create_info.flags = 0;
    create_info.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    create_info.queueFamilyIndex = (u32)desc.graphics_engine_family_index;

    _vk_assert2(vkCreateCommandPool((VkDevice)context->id, &create_info, &internal->vk_allocs, &transition_pool));
    
    VkCommandBufferAllocateInfo allocate_info = {0};
    allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocate_info.commandPool = transition_pool;
    allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocate_info.commandBufferCount = 1;

    VkCommandBuffer transition_cmd = 0;
    _vk_assert2(vkAllocateCommandBuffers(context->id, &allocate_info, &transition_cmd));
    
    VkCommandBufferBeginInfo begin_info = (VkCommandBufferBeginInfo){0};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    
    _vk_assert2(vkBeginCommandBuffer(transition_cmd, &begin_info));
    
    u64 stride = sizeof(_Vk_Render_Image_State)+sizeof(Oga_Render_Image_View);
    void *image_states_data = allocate(context->state_allocator, stride * (*swapchain)->image_count);
    for (u64 i = 0; i < (*swapchain)->image_count; i += 1) {
    
        _vk_image_barrier_helper(transition_cmd, vk_images[i], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
    
        Oga_Render_Image_View *image = (Oga_Render_Image_View*)((u8*)image_states_data + i*stride);
        *image = (Oga_Render_Image_View){0};
        _Vk_Render_Image_State *image_state = (_Vk_Render_Image_State*)(image+1);
        *image_state = (_Vk_Render_Image_State){0};
        
        image->id = image_state;
        image->memory_pointer = OGA_INTERNALLY_MANAGED_MEMORY_HANDLE;
        image->width = desc.width;
        image->height = desc.height;
        
        image_state->image = vk_images[i];
        
        VkImageViewCreateInfo image_view_info = (VkImageViewCreateInfo){0};
        image_view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        image_view_info.image = image_state->image;
        image_view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        image_view_info.format = _oga_to_vk_format((*swapchain)->image_format);
        image_view_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        image_view_info.subresourceRange.baseMipLevel = 0;
        image_view_info.subresourceRange.levelCount = 1;
        image_view_info.subresourceRange.baseArrayLayer = 0;
        image_view_info.subresourceRange.layerCount = 1;
        
        _vk_assert2(vkCreateImageView((VkDevice)context->id, &image_view_info, &internal->vk_allocs, &image_state->view));
        
        (*swapchain)->images[i] = image;
    }
    
    _vk_assert2(vkEndCommandBuffer(transition_cmd));
    
    VkSubmitInfo submit_info = (VkSubmitInfo){0};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &transition_cmd;
    
    _vk_assert2(vkQueueSubmit(context->engines_by_family[desc.graphics_engine_family_index].engines[0].id, 1, &submit_info, 0));
    
    vkQueueWaitIdle(context->engines_by_family[desc.graphics_engine_family_index].engines[0].id);
    
    vkDestroyCommandPool(context->id, transition_pool, &internal->vk_allocs);
    
    (*swapchain)->context = context;
    
    log(OGA_LOG_VERBOSE, "Initted a swapchain %ix%i", desc.width, desc.height);
    
    return OGA_OK;
}
void oga_uninit_swapchain(Oga_Swapchain *swapchain) {
    _Vk_Swapchain_State *state = (_Vk_Swapchain_State*)(swapchain->id);
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)swapchain->context->internal;
    
    _vk_assert1(vkDeviceWaitIdle(swapchain->context->id));
    
    for (u64 i = 0; i < swapchain->image_count; i += 1) {
        _Vk_Image_State *image_state = (_Vk_Image_State*)(swapchain->images[i]->id);
        vkDestroyImageView((VkDevice)swapchain->context->id, image_state->view, &internal->vk_allocs);
    }
    
    vkDestroySwapchainKHR((VkDevice)swapchain->context->id, state->vk_swapchain, &internal->vk_allocs);
    
    
    VkSurfaceKHR sur = state->vk_surface;
    // Musnt use the vulkan allocation callbacks
    
    vkDestroySurfaceKHR(_vk_instance(), sur, 0);

    Allocator a = swapchain->context->state_allocator;
    
    deallocate(a, swapchain->images[0]);
    
    *swapchain = (Oga_Swapchain){0};
    deallocate(a, swapchain);
}

Oga_Result oga_get_next_swapchain_image(Oga_Swapchain *swapchain, u64 timeout, struct Oga_Gpu_Latch *signal_gpu_latch, struct Oga_Cpu_Latch *signal_cpu_latch, u64 *image_index) {

    _Vk_Swapchain_State *state = (_Vk_Swapchain_State*)swapchain->id;

    u32 index;
    VkResult result = vkAcquireNextImageKHR(swapchain->context->id, state->vk_swapchain, timeout, signal_gpu_latch ? signal_gpu_latch->id : 0, signal_cpu_latch ? signal_cpu_latch->id : 0, &index);
    
    *image_index = (u64)index;
    
    if (result == VK_SUBOPTIMAL_KHR)  return OGA_SUBOPTIMAL;
    else if (result == VK_NOT_READY) return OGA_NOT_READY;
    else if (result == VK_TIMEOUT) return OGA_TIMEOUT;
    else if (result == VK_ERROR_OUT_OF_DATE_KHR) return OGA_ERROR_OUTDATED;
    else if (result == VK_ERROR_SURFACE_LOST_KHR) return OGA_ERROR_SURFACE_LOST;
    
    _vk_assert2(result);
    
    return OGA_OK;
}

Oga_Result oga_submit_present(Oga_Swapchain *swapchain, Oga_Present_Desc desc) {
    
    _Vk_Swapchain_State *state = (_Vk_Swapchain_State*)swapchain->id;
    
    VkSemaphore vk_semaphores[256];
    
    for (u64 i = 0; i < desc.wait_gpu_latch_count; i += 1) {
        vk_semaphores[i] = desc.wait_gpu_latches[i]->id;
    }
    
    VkPresentInfoKHR info = (VkPresentInfoKHR){0};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    info.waitSemaphoreCount = (u32)desc.wait_gpu_latch_count;
    info.pWaitSemaphores = vk_semaphores;
    info.swapchainCount = 1;
    info.pSwapchains = &state->vk_swapchain;
    info.pImageIndices = (u32*)&desc.image_index;
    
    VkResult result = vkQueuePresentKHR(desc.engine.id, &info);
    
    if (result == VK_SUBOPTIMAL_KHR)  return OGA_SUBOPTIMAL;
    else if (result == VK_NOT_READY) return OGA_NOT_READY;
    else if (result == VK_TIMEOUT) return OGA_TIMEOUT;
    else if (result == VK_ERROR_OUT_OF_DATE_KHR) return OGA_ERROR_OUTDATED;
    else if (result == VK_ERROR_SURFACE_LOST_KHR) return OGA_ERROR_SURFACE_LOST;
    
    _vk_assert2(result);
    
    return OGA_OK;
}

Oga_Result oga_init_program(Oga_Context *context, Oga_Program_Desc desc, Oga_Program **program) {
    *program = allocate(context->state_allocator, sizeof(Oga_Program));
    if (!*program) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }
    **program = (Oga_Program){0};
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkShaderModuleCreateInfo info = (VkShaderModuleCreateInfo){0};
    
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.codeSize = (size_t)desc.code_size;
    info.pCode = desc.code;
    
    VkResult result = vkCreateShaderModule((VkDevice)context->id, &info, &internal->vk_allocs, (VkShaderModule*)&(*program)->id);
    
    if (result != VK_SUCCESS) {
        if (result == VK_ERROR_INVALID_SHADER_NV || result == VK_ERROR_INITIALIZATION_FAILED) {
            deallocate(context->state_allocator, *program);
            return OGA_INIT_PROGRAM_ERROR_BAD_CODE;
        }
        _vk_assert2(result);
    }
    
    (*program)->context = context;
    
    return OGA_OK;
}
void oga_uninit_program(Oga_Program *program) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)program->context->internal;
    
    _vk_assert1(vkDeviceWaitIdle(program->context->id));
    vkDestroyShaderModule((VkDevice)program->context->id, (VkShaderModule)program->id, &internal->vk_allocs);
    
    Allocator a = program->context->state_allocator;
    *program = (Oga_Program){0};
    deallocate(a, program);
}

Oga_Result oga_init_binding_list_layout(Oga_Context *context, Oga_Binding_List_Layout_Desc desc, Oga_Binding_List_Layout **layout) {
    *layout = allocate(context->state_allocator, sizeof(Oga_Binding_List_Layout)+sizeof(_Vk_Binding_List_Layout_State)+desc.binding_list_count*sizeof(Oga_Binding_Layout_Entry_Desc));
    if (!*layout) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }
    **layout = (Oga_Binding_List_Layout){0};
    
    (*layout)->context = context;
    
    (*layout)->id = (*layout)+1;
    _Vk_Binding_List_Layout_State *state = (_Vk_Binding_List_Layout_State*)((*layout)->id);
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkDescriptorSetLayoutCreateInfo set_layout_info = (VkDescriptorSetLayoutCreateInfo) {0};
    set_layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    set_layout_info.bindingCount = (u32)desc.binding_count;
    
    VkDescriptorPoolSize pool_sizes[OGA_BINDING_ENUM_MAX];
    pool_sizes[OGA_BINDING_IMAGE].type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
    pool_sizes[OGA_BINDING_SAMPLE_MODE].type = VK_DESCRIPTOR_TYPE_SAMPLER;
    pool_sizes[OGA_BINDING_BLOCK].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    pool_sizes[OGA_BINDING_FBUFFER].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    
    // todo(charlie) #validation
    // - Overlapped binding slots ?
    // - Does the layout match the shader reflection data?
    // - Check shader reflection if a binding is used in a stage which was not specified in stage_flags
    
    VkDescriptorSetLayoutBinding *vk_bindings = PushTempBuffer(VkDescriptorSetLayoutBinding, desc.binding_count);
    for (u64 j = 0; j < desc.binding_count; j += 1) {
        switch (desc.bindings[j].kind) {
        case OGA_BINDING_IMAGE: 
            vk_bindings[j].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE; 
            pool_sizes[OGA_BINDING_IMAGE].descriptorCount += (u32)desc.binding_list_count;
            break;
        case OGA_BINDING_FBUFFER: 
            vk_bindings[j].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE; 
            pool_sizes[OGA_BINDING_FBUFFER].descriptorCount += (u32)desc.binding_list_count;
            break;
        case OGA_BINDING_SAMPLE_MODE: 
            vk_bindings[j].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER; 
            pool_sizes[OGA_BINDING_SAMPLE_MODE].descriptorCount += (u32)desc.binding_list_count;
            break;
        case OGA_BINDING_BLOCK: 
            vk_bindings[j].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; 
            pool_sizes[OGA_BINDING_BLOCK].descriptorCount += (u32)desc.binding_list_count;
            break;
        case OGA_BINDING_ENUM_MAX: // fallthrough
        default:
            return OGA_INIT_RENDER_PASS_ERROR_INVALID_PROGRAM_BINDING_KIND_ENUM;
        }
        vk_bindings[j].binding = (u32)desc.bindings[j].binding_slot;
        vk_bindings[j].descriptorCount = (u32)desc.bindings[j].binding_count;
        
        vk_bindings[j].stageFlags = 0;
        if (desc.bindings[j].stage_flags & OGA_PROGRAM_STAGE_VERTEX)
            vk_bindings[j].stageFlags |= VK_SHADER_STAGE_VERTEX_BIT;
        if (desc.bindings[j].stage_flags & OGA_PROGRAM_STAGE_FRAGMENT)
            vk_bindings[j].stageFlags |= VK_SHADER_STAGE_FRAGMENT_BIT;
        if (desc.bindings[j].stage_flags & OGA_PROGRAM_STAGE_COMPUTE)
            vk_bindings[j].stageFlags |= VK_SHADER_STAGE_COMPUTE_BIT;
            
        if (vk_bindings[j].stageFlags == 0) {
            return OGA_INIT_BINDING_LIST_LAYOUT_ERROR_MISSING_STAGE_FLAGS;
        }
        
        vk_bindings[j].pImmutableSamplers = 0;
    }
    
    VkDescriptorPoolSize actual_pool_sizes[OGA_BINDING_ENUM_MAX];
    u64 actual_pool_sizes_next = 0;
    for (u64 i = 0; i < OGA_BINDING_ENUM_MAX; i += 1) {
        if (pool_sizes[i].descriptorCount > 0) {
            actual_pool_sizes[actual_pool_sizes_next++] = pool_sizes[i];
        }
    }
    
    
    set_layout_info.pBindings = vk_bindings;
    
    _vk_assert2(vkCreateDescriptorSetLayout(context->id, &set_layout_info, &internal->vk_allocs, &state->layout));
    
    VkDescriptorPoolCreateInfo pool_info = (VkDescriptorPoolCreateInfo){0};
    pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.maxSets = (u32)desc.binding_list_count;
    pool_info.poolSizeCount = (u32)actual_pool_sizes_next;
    pool_info.pPoolSizes = actual_pool_sizes;
    _vk_assert2(vkCreateDescriptorPool(context->id, &pool_info, &internal->vk_allocs, &state->pool));
    
    (*layout)->bindings = (Oga_Binding_Layout_Entry_Desc*)((state)+1);
    memcpy((*layout)->bindings, desc.bindings, desc.binding_list_count*sizeof(Oga_Binding_Layout_Entry_Desc));
    (*layout)->binding_count = desc.binding_count;
    (*layout)->binding_list_count = desc.binding_list_count;
    
    return OGA_OK;
}
void oga_uninit_binding_list_layout(Oga_Binding_List_Layout *layout) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)layout->context->internal;
    
    _Vk_Binding_List_Layout_State *state = (_Vk_Binding_List_Layout_State*)((layout)->id);
    
    _vk_assert1(vkDeviceWaitIdle(layout->context->id));
    vkDestroyDescriptorPool(layout->context->id, state->pool, &internal->vk_allocs);
    vkDestroyDescriptorSetLayout((VkDevice)layout->context->id, state->layout, &internal->vk_allocs);
    
    Allocator a = layout->context->state_allocator;
    *layout = (Oga_Binding_List_Layout){0};
    deallocate(a, layout);
}

Oga_Result oga_push_binding_list(Oga_Binding_List_Layout *layout, Oga_Binding_List_Desc desc, Oga_Binding_List **list) {
    *list = allocate(layout->context->state_allocator, sizeof(Oga_Binding_List)); // todo(charlie #leak this isn't freed
    if (!*list) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }
    **list = (Oga_Binding_List){0};
    
    (*list)->context = layout->context;
    
    _Vk_Binding_List_Layout_State *layout_state = (_Vk_Binding_List_Layout_State*)((layout)->id);
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)layout->context->internal;
    
    if (desc.binding_count > layout->binding_count) {
        return OGA_PUSH_BINDING_LIST_ERROR_LAYOUT_COUNT_MISMATCH;
    }
    // todo(charlie) #validation 
    // - check that binding list is compliant with layout
    // - check allocated_lists_count was not overflown
    // - Notify if any item is null where a binding is expected
    
    
    VkDescriptorSetAllocateInfo info = (VkDescriptorSetAllocateInfo){0};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    info.descriptorPool = layout_state->pool;
    info.descriptorSetCount = 1;
    info.pSetLayouts = &layout_state->layout;
    _vk_assert2(vkAllocateDescriptorSets(layout->context->id, &info, (VkDescriptorSet*)&(*list)->id));
    
    layout->allocated_lists_count += 1;
    
    VkWriteDescriptorSet *writes = PushTempBuffer(VkWriteDescriptorSet, desc.binding_count);
    
    // todo(charlie) #validation
    
    for (u64 i = 0; i < desc.binding_count; i += 1) {
        writes[i] = (VkWriteDescriptorSet){0};
        writes[i].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[i].dstSet = (*list)->id;
        writes[i].dstBinding = (u32)desc.bindings[i].binding_slot;
        writes[i].dstArrayElement = (u32)desc.bindings[i].array_index;
        writes[i].descriptorCount = (u32)desc.bindings[i].count;
        switch (desc.bindings[i].kind) {
            case OGA_BINDING_IMAGE: {
                writes[i].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
                assert(desc.bindings[i].count);
                VkDescriptorImageInfo *image_infos = PushTempBuffer(VkDescriptorImageInfo, desc.bindings[i].count);
                for (u64 j = 0; j < desc.bindings[i].count; j += 1) {
                    _Vk_Image_State* image_state = (_Vk_Image_State*)desc.bindings[i].images[j]->id;                    
                    image_infos[j] = (VkDescriptorImageInfo){0};
                    image_infos[j].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
                    image_infos[j].imageView = image_state->view;
                }
                writes[i].pImageInfo = image_infos;
                break;
            }
            case OGA_BINDING_FBUFFER: {
                writes[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
                assert(desc.bindings[i].count);
                VkDescriptorImageInfo *image_infos = PushTempBuffer(VkDescriptorImageInfo, desc.bindings[i].count);
                for (u64 j = 0; j < desc.bindings[i].count; j += 1) {
                    _Vk_Image_State* image_state = (_Vk_Image_State*)desc.bindings[i].fbuffers[j]->id;                    
                    image_infos[j] = (VkDescriptorImageInfo){0};
                    image_infos[j].imageLayout = VK_IMAGE_LAYOUT_GENERAL;
                    image_infos[j].imageView = image_state->view;
                }
                writes[i].pImageInfo = image_infos;
                break;
            }
            case OGA_BINDING_BLOCK: {
                writes[i].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                assert(desc.bindings[i].count);
                
                VkDescriptorBufferInfo *buffer_infos = PushTempBuffer(VkDescriptorBufferInfo, desc.bindings[i].count);
                for (u64 j = 0; j < desc.bindings[i].count; j += 1) {
                    buffer_infos[j].buffer = desc.bindings[i].blocks[j]->id;
                    buffer_infos[j].offset = 0;
                    buffer_infos[j].range = desc.bindings[i].blocks[j]->size;
                }
                writes[i].pBufferInfo = buffer_infos;
                break;
            }
            case OGA_BINDING_SAMPLE_MODE: {
                writes[i].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
                assert(desc.bindings[i].count);
                
                // todo(charlie) table of samplers (we are currently just leakign sampelrs)
                
                VkDescriptorImageInfo *image_infos = PushTempBuffer(VkDescriptorImageInfo, desc.bindings[i].count);
                for (u64 j = 0; j < desc.bindings[i].count; j += 1) {
                    Oga_Sample_Mode_Desc mode = desc.bindings[i].sample_modes[j];
                    VkSampler sampler = 0;
                    VkSamplerCreateInfo sampler_info = (VkSamplerCreateInfo){0};
                    sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
                    
                    switch (mode.magnification_filter) {
                    case OGA_SAMPLE_FILTER_LINEAR: sampler_info.magFilter = VK_FILTER_LINEAR; break;
                    case OGA_SAMPLE_FILTER_NEAREST: sampler_info.magFilter = VK_FILTER_NEAREST; break;
                    default:
                        assert(false); break; // todo(charlie) #validation #error
                    }
                    switch (mode.minification_filter) {
                    case OGA_SAMPLE_FILTER_LINEAR: sampler_info.minFilter = VK_FILTER_LINEAR; break;
                    case OGA_SAMPLE_FILTER_NEAREST: sampler_info.minFilter = VK_FILTER_NEAREST; break;
                    default:
                        assert(false); break; // todo(charlie) #validation #error
                    }
                    
                    switch (mode.address_mode_u) {
                    case OGA_SAMPLE_ADDRESS_MODE_REPEAT:          sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT; break;
                    case OGA_SAMPLE_ADDRESS_MODE_MIRRORED_REPEAT: sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT; break;
                    case OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_EDGE:   sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE; break;
                    case OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_BORDER: sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER; break;
                    default:
                        assert(false); break; // todo(charlie) #validation #error
                    }
                    switch (mode.address_mode_v) {
                    case OGA_SAMPLE_ADDRESS_MODE_REPEAT:          sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT; break;
                    case OGA_SAMPLE_ADDRESS_MODE_MIRRORED_REPEAT: sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT; break;
                    case OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_EDGE:   sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE; break;
                    case OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_BORDER: sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER; break;
                    default:
                        assert(false); break; // todo(charlie) #validation #error
                    }
                    switch (mode.address_mode_w) {
                    case OGA_SAMPLE_ADDRESS_MODE_REPEAT:          sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT; break;
                    case OGA_SAMPLE_ADDRESS_MODE_MIRRORED_REPEAT: sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT; break;
                    case OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_EDGE:   sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE; break;
                    case OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_BORDER: sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER; break;
                    default:
                        assert(false); break; // todo(charlie) #validation #error
                    }
                    
                    sampler_info.anisotropyEnable = mode.max_anisotropy > 0.0f ? VK_TRUE : VK_FALSE;
                    sampler_info.maxAnisotropy = mode.max_anisotropy;
                    
                    _vk_assert2(vkCreateSampler(layout->context->id, &sampler_info, &internal->vk_allocs, &sampler));
                    
                    image_infos[j] = (VkDescriptorImageInfo){0};
                    image_infos[j].sampler = sampler;
                }
                writes[i].pImageInfo = image_infos;
                break;
            }
            case OGA_BINDING_ENUM_MAX: // fallthrough
            default:
                assert(false); // todo(charlie) #validation #error
        }
    }
    
    vkUpdateDescriptorSets(layout->context->id, (u32)desc.binding_count, writes, 0, 0);
    
    return OGA_OK;
}

Oga_Result oga_init_render_passes(Oga_Context *context, Oga_Render_Pass_Desc* descs, Oga_Render_Pass **render_passes, u64 render_pass_count) {

    for (u64 i = 0; i < render_pass_count; i += 1) {
        render_passes[i] = (Oga_Render_Pass*)allocate(context->state_allocator, sizeof(Oga_Render_Pass)+sizeof(_Vk_Render_Pass_State));
    }

    VkGraphicsPipelineCreateInfo *infos = PushTempBuffer(VkGraphicsPipelineCreateInfo, render_pass_count);
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    // todo(charlie)
    // We use a lot of temporary storage here, so we would probably want to reset it back to where it was before,
    // once that's implemented ..
    for (u64 i = 0; i < render_pass_count; i += 1) {
    
        Oga_Render_Pass_Desc desc = descs[i];
        
        VkFormat *vk_formats = PushTempBuffer(VkFormat, desc.attachment_count);
        for (u64 j = 0; j < desc.attachment_count; j += 1) {
            vk_formats[j] = _oga_to_vk_format(desc.attachment_formats[j]);
        }
        
        VkPipelineRenderingCreateInfoKHR *rendering = PushTemp(VkPipelineRenderingCreateInfoKHR);
        *rendering = (VkPipelineRenderingCreateInfoKHR){0};
        rendering->sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
        rendering->pNext = 0;
        rendering->viewMask = 0;
        rendering->colorAttachmentCount = (u32)desc.attachment_count;
        rendering->pColorAttachmentFormats = vk_formats;
        
        VkPipelineCreateFlags pipeline_flags = (VkPipelineCreateFlags)(int)0;
        if (desc.flags & OGA_RENDER_PASS_INHERITANCE_PARENT) pipeline_flags |= VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT;
        if (desc.flags & OGA_RENDER_PASS_INHERITANCE_CHILD)  pipeline_flags |= VK_PIPELINE_CREATE_DERIVATIVE_BIT;
        
        char *vert_entry = PushTempBuffer(char, desc.vertex_program_entry_point.count+1);
        char *frag_entry = PushTempBuffer(char, desc.fragment_program_entry_point.count+1);
        memcpy(vert_entry, desc.vertex_program_entry_point.data, desc.vertex_program_entry_point.count+1);
        memcpy(frag_entry, desc.fragment_program_entry_point.data, desc.fragment_program_entry_point.count+1);
        vert_entry[desc.vertex_program_entry_point.count] = 0;
        frag_entry[desc.fragment_program_entry_point.count] = 0;
        
        VkPipelineShaderStageCreateInfo *stages = PushTempBuffer(VkPipelineShaderStageCreateInfo, 2);
        stages[0] = (VkPipelineShaderStageCreateInfo){0};
        stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
        stages[0].module = (VkShaderModule)desc.vertex_program->id;
        stages[0].pName = vert_entry;
        
        stages[1] = (VkPipelineShaderStageCreateInfo){0};
        stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        stages[1].module = (VkShaderModule)desc.fragment_program->id;
        stages[1].pName = frag_entry;
        
        VkPipelineInputAssemblyStateCreateInfo *ia = PushTemp(VkPipelineInputAssemblyStateCreateInfo);
        *ia = (VkPipelineInputAssemblyStateCreateInfo){0};
        ia->sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        ia->topology = (VkPrimitiveTopology)desc.topology; // #Volatile values must map to same as vulkan equivalents
        
        VkPipelineTessellationStateCreateInfo *tessellation = PushTemp(VkPipelineTessellationStateCreateInfo);
        *tessellation = (VkPipelineTessellationStateCreateInfo){0};
        tessellation->sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
        tessellation->patchControlPoints = 0;
        
        VkPipelineViewportStateCreateInfo *viewport = PushTemp(VkPipelineViewportStateCreateInfo);
        *viewport = (VkPipelineViewportStateCreateInfo){0};
        viewport->sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewport->viewportCount = 1;
        viewport->scissorCount = 1; 
        viewport->pViewports = 0;
        viewport->pScissors = 0; 
        
        VkFrontFace front_face = VK_FRONT_FACE_CLOCKWISE;
        VkCullModeFlags cull_mode = VK_CULL_MODE_BACK_BIT;
        
        switch(desc.cull_mode) {
            case OGA_CULL_NONE:
                cull_mode = VK_CULL_MODE_NONE;
                break;
            case OGA_CULL_CLOCKWISE:
                front_face = VK_FRONT_FACE_CLOCKWISE;
                break;
            case OGA_CULL_COUNTER_CLOCKWISE:
                front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE;
                break;
            
            default: assert(false);
        }
        
        //VkBool32 depth_clamp_enable = (desc.flags & OGA_RENDER_PASS_DISABLE_DEPTH_CLAMP) == 0;

        /*if (depth_clamp_enable && !(context->device.features & OGA_DEVICE_FEATURE_DEPTH_CLAMP)) {
            depth_clamp_enable = false;
            log(OGA_LOG_VERBOSE, "Depth clamp was flagged as enabled, but device is missing feature flag OGA_RENDER_PASS_DISABLE_DEPTH_CLAMP");
        }*/
        VkBool32 depth_clamp_enable = VK_FALSE;
        
        VkPipelineRasterizationStateCreateInfo *rasterization = PushTemp(VkPipelineRasterizationStateCreateInfo);
        *rasterization = (VkPipelineRasterizationStateCreateInfo){0};
        rasterization->sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterization->depthClampEnable = depth_clamp_enable;
        rasterization->rasterizerDiscardEnable = VK_FALSE;
        rasterization->polygonMode = VK_POLYGON_MODE_FILL;
        rasterization->cullMode = cull_mode;
        rasterization->frontFace = front_face;
        rasterization->depthBiasEnable = VK_FALSE;
        rasterization->lineWidth = desc.line_width;
        
        VkSampleCountFlagBits samples = (VkSampleCountFlagBits)OGA_SAMPLE_COUNT_1;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_1)  samples |= VK_SAMPLE_COUNT_1_BIT;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_2)  samples |= VK_SAMPLE_COUNT_2_BIT;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_4)  samples |= VK_SAMPLE_COUNT_4_BIT;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_8)  samples |= VK_SAMPLE_COUNT_8_BIT;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_16) samples |= VK_SAMPLE_COUNT_16_BIT;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_32) samples |= VK_SAMPLE_COUNT_32_BIT;
        if (desc.rasterization_samples & OGA_SAMPLE_COUNT_64) samples |= VK_SAMPLE_COUNT_64_BIT;
        
        
        VkPipelineMultisampleStateCreateInfo *multisample = PushTemp(VkPipelineMultisampleStateCreateInfo);
        *multisample = (VkPipelineMultisampleStateCreateInfo){0};
        multisample->sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisample->rasterizationSamples = samples;
        
        VkPipelineDepthStencilStateCreateInfo *depth_stencil = PushTemp(VkPipelineDepthStencilStateCreateInfo);
        *depth_stencil = (VkPipelineDepthStencilStateCreateInfo){0};
        depth_stencil->sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        
        // todo(charlie) allow enabling driver blending
        VkPipelineColorBlendAttachmentState *blend_attachment = PushTemp(VkPipelineColorBlendAttachmentState);
        *blend_attachment = (VkPipelineColorBlendAttachmentState){0};
        //blend_attachment->blendEnable = true;
        blend_attachment->srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        blend_attachment->dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        blend_attachment->colorBlendOp = VK_BLEND_OP_ADD;
        blend_attachment->srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        blend_attachment->dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        blend_attachment->alphaBlendOp = VK_BLEND_OP_ADD;
        blend_attachment->colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        
        VkPipelineColorBlendStateCreateInfo *blend = PushTemp(VkPipelineColorBlendStateCreateInfo);
        *blend = (VkPipelineColorBlendStateCreateInfo){0};
        blend->sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        blend->attachmentCount = 1;
        blend->pAttachments = blend_attachment;
        blend->blendConstants[0] = 0.0f;
        blend->blendConstants[1] = 0.0f;
        blend->blendConstants[2] = 0.0f;
        blend->blendConstants[3] = 0.0f;
        
        VkDynamicState dynamic_states[] = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
        };
        VkPipelineDynamicStateCreateInfo *dynamic = PushTemp(VkPipelineDynamicStateCreateInfo);
        *dynamic = (VkPipelineDynamicStateCreateInfo){0};
        dynamic->sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamic->dynamicStateCount = sizeof(dynamic_states)/sizeof(VkDynamicState);
        dynamic->pDynamicStates = dynamic_states;
                 
        VkPipelineLayout layout;
        VkPipelineLayoutCreateInfo *layout_info = PushTemp(VkPipelineLayoutCreateInfo);
        *layout_info = (VkPipelineLayoutCreateInfo){0};
        layout_info->sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        layout_info->pSetLayouts 
            = desc.binding_list_layout ? &((_Vk_Binding_List_Layout_State*)desc.binding_list_layout->id)->layout : 0;
        layout_info->setLayoutCount = desc.binding_list_layout ? 1 : 0;
        
        _vk_assert2(vkCreatePipelineLayout((VkDevice)context->id, layout_info, &internal->vk_allocs, &layout));
        
        VkPipeline base_pipeline = 0;
        if (desc.base) {
            _Vk_Render_Pass_State *state = (_Vk_Render_Pass_State*)desc.base->id;
            base_pipeline = state->pipeline;
        }
        
        s32 base_index = (s32)desc.base_index;
         
        VkVertexInputBindingDescription bindings[OGA_MAX_VERTEX_BINDING_COUNT];
        VkVertexInputAttributeDescription attributes[OGA_MAX_VERTEX_ATTRIBUTE_COUNT];
        
        for (u64 j = 0; j < desc.vertex_input_layout.binding_count; j += 1) {
            bindings[j].binding = (u32)i;
            bindings[j].stride = (u32)desc.vertex_input_layout.bindings[j].stride;
            switch (desc.vertex_input_layout.bindings[j].input_rate) {
            case OGA_VERTEX_INPUT_RATE_VERTEX: bindings[j].inputRate = VK_VERTEX_INPUT_RATE_VERTEX; break;
            case OGA_VERTEX_INPUT_RATE_INSTANCE: bindings[j].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE; break;
            default:
                return OGA_ERROR_INVALID_INPUT_RATE_ENUM;
            }
        }
        for (u64 j = 0; j < desc.vertex_input_layout.attribute_count; j += 1) {
            attributes[j].binding = (u32)desc.vertex_input_layout.attributes[j].binding;
            attributes[j].location = (u32)desc.vertex_input_layout.attributes[j].location;
            attributes[j].offset = (u32)desc.vertex_input_layout.attributes[j].offset;
            attributes[j].format = _oga_vertex_attribute_type_to_vk_format(desc.vertex_input_layout.attributes[j].type);
        }
        
        // todo(charlie) #validation generate a detailed error for mismatch between vertex program input layout
        // and this input layout.
        VkPipelineVertexInputStateCreateInfo *vertex_input = PushTemp(VkPipelineVertexInputStateCreateInfo);
        *vertex_input = (VkPipelineVertexInputStateCreateInfo) {0};
        vertex_input->sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertex_input->vertexBindingDescriptionCount = (u32)desc.vertex_input_layout.binding_count;
        vertex_input->vertexAttributeDescriptionCount = (u32)desc.vertex_input_layout.attribute_count;
        vertex_input->pVertexBindingDescriptions = bindings;
        vertex_input->pVertexAttributeDescriptions = attributes;
    
        VkGraphicsPipelineCreateInfo info = (VkGraphicsPipelineCreateInfo) {0};
        info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        info.pNext = rendering;
        info.flags = pipeline_flags;
        info.stageCount = 2;
        info.pStages = stages;
        info.pVertexInputState = vertex_input;
        info.pInputAssemblyState = ia;
        info.pTessellationState = tessellation;
        info.pViewportState = viewport;
        info.pRasterizationState = rasterization;
        info.pMultisampleState = multisample;
        info.pDepthStencilState = depth_stencil;
        info.pColorBlendState = blend;
        info.pDynamicState = dynamic;
        info.layout = layout;
        info.renderPass = 0; // #Portability dynamic rendering
        info.subpass = 0;
        info.basePipelineHandle = base_pipeline;
        info.basePipelineIndex = base_index;
        
        infos[i] = info;
    }
    
    VkPipeline *vk_pipelines = PushTempBuffer(VkPipeline, render_pass_count);
    assert(vk_pipelines);
    _vk_assert2(vkCreateGraphicsPipelines((VkDevice)context->id, 0, (u32)render_pass_count, infos, &internal->vk_allocs, vk_pipelines));
    
    // These need to be allocated one by one because render passes needs to be able to be freed one by one
    for (u64 i = 0; i < render_pass_count; i += 1) {
        render_passes[i]->context = context;
        _Vk_Render_Pass_State *state = (_Vk_Render_Pass_State*)(render_passes[i]+1);
        render_passes[i]->id = state;
        
        state->pipeline = vk_pipelines[i];
        state->layout = infos[i].layout;
        
        render_passes[i]->vertex_input_layout = descs[i].vertex_input_layout;
    }
    
    return OGA_OK;
}

Oga_Result oga_init_render_pass(Oga_Context *context, Oga_Render_Pass_Desc desc, Oga_Render_Pass **render_pass) {
    return oga_init_render_passes(context, &desc, render_pass, 1);
} 
void oga_uninit_render_pass(Oga_Render_Pass *render_pass) {
    _Vk_Render_Pass_State *state = (_Vk_Render_Pass_State*)render_pass->id;
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)render_pass->context->internal;
    
    _vk_assert1(vkDeviceWaitIdle(render_pass->context->id));
    vkDestroyPipeline((VkDevice)render_pass->context->id, state->pipeline, &internal->vk_allocs);
    vkDestroyPipelineLayout((VkDevice)render_pass->context->id, state->layout, &internal->vk_allocs);
    
    Allocator a = render_pass->context->state_allocator;
    *render_pass = (Oga_Render_Pass){0};
    deallocate(a, render_pass);
} 

Oga_Result oga_init_gpu_latch(Oga_Context *context, Oga_Gpu_Latch **gpu_latch) {
    *gpu_latch = allocate(context->state_allocator, sizeof(Oga_Gpu_Latch) + sizeof(VkSemaphore));
    if (!*gpu_latch) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **gpu_latch = (Oga_Gpu_Latch){0};
    (*gpu_latch)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;

    VkSemaphoreCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    _vk_assert2(vkCreateSemaphore((VkDevice)context->id, &create_info, &internal->vk_allocs, (VkSemaphore*)&(*gpu_latch)->id));
    
    return OGA_OK;
}

void oga_uninit_gpu_latch(Oga_Gpu_Latch *gpu_latch) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)gpu_latch->context->internal;
    _vk_assert1(vkDeviceWaitIdle(gpu_latch->context->id));
    vkDestroySemaphore((VkDevice)gpu_latch->context->id, (VkSemaphore)gpu_latch->id, &internal->vk_allocs);

    Allocator a = gpu_latch->context->state_allocator;
    *gpu_latch = (Oga_Gpu_Latch){0};
    deallocate(a, gpu_latch);
}

// Cpu latch; for synchronizing CPU with GPU. Signalled on GPU, waited on CPU.
Oga_Result oga_init_cpu_latch(Oga_Context *context, Oga_Cpu_Latch **cpu_latch, bool start_signaled) {
    *cpu_latch = allocate(context->state_allocator, sizeof(Oga_Cpu_Latch) + sizeof(VkFence));
    if (!*cpu_latch) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **cpu_latch = (Oga_Cpu_Latch){0};
    (*cpu_latch)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;

    VkFenceCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    create_info.flags = start_signaled ? VK_FENCE_CREATE_SIGNALED_BIT : 0;

    _vk_assert2(vkCreateFence((VkDevice)context->id, &create_info, &internal->vk_allocs, (VkFence*)&(*cpu_latch)->id));

    return OGA_OK;
}

void oga_uninit_cpu_latch(Oga_Cpu_Latch *cpu_latch) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)cpu_latch->context->internal;
    _vk_assert1(vkDeviceWaitIdle(cpu_latch->context->id));
    vkDestroyFence((VkDevice)cpu_latch->context->id, (VkFence)cpu_latch->id, &internal->vk_allocs);

    Allocator a = cpu_latch->context->state_allocator;
    *cpu_latch = (Oga_Cpu_Latch){0};
    deallocate(a, cpu_latch);
}

Oga_Result oga_wait_latch(Oga_Cpu_Latch *cpu_latch) {
    _vk_assert2(vkWaitForFences((VkDevice)cpu_latch->context->id, 1, (VkFence*)&cpu_latch->id, VK_TRUE, UINT64_MAX));
    
    return OGA_OK;
}

Oga_Result oga_reset_latch(Oga_Cpu_Latch *cpu_latch) {
    _vk_assert2(vkResetFences((VkDevice)cpu_latch->context->id, 1, (VkFence*)&cpu_latch->id));

    return OGA_OK;
}

Oga_Result oga_allocate_memory(Oga_Context *context, u64 size, Oga_Memory_Property_Flag properties, Oga_Memory_Usage usage, Oga_Memory_Pointer *result) {
    *result = (Oga_Memory_Pointer){0};
    (result)->context = context;
    
    result->id = New(context->state_allocator, _Vk_Memory_State);
    _Vk_Memory_State *state = (_Vk_Memory_State*)result->id;
    *state = (_Vk_Memory_State){0};
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkPhysicalDeviceMemoryProperties props;
    vkGetPhysicalDeviceMemoryProperties(context->device.id, &props);
    
    u32 index = U32_MAX;
    u64 heap_index = 0;
    for (u32 i = 0; i < props.memoryTypeCount; i += 1) {
        VkMemoryType type = props.memoryTypes[i];
        
        if ((properties & OGA_MEMORY_PROPERTY_GPU_LOCAL) && !(type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT))
            continue;
        if ((properties & OGA_MEMORY_PROPERTY_GPU_TO_CPU_MAPPABLE) && !(type.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT))
            continue;
        if ((properties & OGA_MEMORY_PROPERTY_GPU_TO_CPU_REFLECTED) && !(type.propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
            continue;
        if ((properties & OGA_MEMORY_PROPERTY_GPU_TO_CPU_CACHED) && !(type.propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT))
            continue;
        
        
        
        if (usage != (context->device.memory_heaps[type.heapIndex].supported_usage_flags & usage))
            continue;
        
        // todo(charlie)
        // Find memory type that is the closest match.
        // We might want to use a memory type that has only the GPU_LOCAL flag, as some
        // drivers may use this to optimize.
        index = i;
        heap_index = (u64)type.heapIndex;
        break;
    }
    
    if (index == U32_MAX) 
        return OGA_ALLOCATE_MEMORY_ERROR_INVALID_PROPERTIES_AND_USAGE_COMBINATION;
    
    VkMemoryAllocateInfo info = (VkMemoryAllocateInfo){0};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    info.allocationSize = (VkDeviceSize)size;
    info.memoryTypeIndex = index;
    _vk_assert2(vkAllocateMemory(context->id, &info, &internal->vk_allocs, &(state)->memory));
    
    state->memory_type_index = index;
    
    result->properties = properties;
    result->offset = 0;
    result->size = size;
    result->usage = usage;
    result->heap_index = heap_index;
    
    VkBufferCreateInfo copy_buffer_info = (VkBufferCreateInfo){0};
    copy_buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    copy_buffer_info.size = (VkDeviceSize)size;
    copy_buffer_info.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    copy_buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    _vk_assert2(vkCreateBuffer(context->id, &copy_buffer_info, &internal->vk_allocs, &state->raw_view));
    
    _vk_assert2(vkBindBufferMemory(context->id, state->raw_view, state->memory, 0));
    
    return OGA_OK;
}
void oga_deallocate_memory(Oga_Memory_Pointer ptr) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)ptr.context->internal;
    _Vk_Memory_State *state = (_Vk_Memory_State*)ptr.id;
    _vk_assert1(vkDeviceWaitIdle(ptr.context->id));
    
    vkDestroyBuffer(ptr.context->id, state->raw_view, &internal->vk_allocs);
    if (state->last_image_optimal_view)
        vkDestroyImage(ptr.context->id, state->last_image_optimal_view, &internal->vk_allocs);
    vkFreeMemory(ptr.context->id, state->memory, &internal->vk_allocs);
}
Oga_Result oga_map_memory(Oga_Memory_Pointer ptr, u64 size, void **mapped_mem) {
    _Vk_Memory_State *state = (_Vk_Memory_State*)ptr.id;
    _vk_assert2(vkMapMemory(ptr.context->id, state->memory, (VkDeviceSize)ptr.offset, (VkDeviceSize)size, 0, mapped_mem));
    return OGA_OK;
}
void oga_unmap_memory(Oga_Memory_Pointer ptr) {
    _Vk_Memory_State *state = (_Vk_Memory_State*)ptr.id;
    vkUnmapMemory(ptr.context->id, state->memory);
}
Oga_Result oga_memory_offset(Oga_Memory_Pointer ptr, s64 offset, Oga_Memory_Pointer *result_ptr) {
    *result_ptr = ptr;
    
    s64 new_offset = (s64)result_ptr->offset + offset;
    
    if (new_offset < 0) {
        return OGA_MEMORY_OFFSET_ERROR_UNDERFLOW;
    }
    if (new_offset >= (s64)result_ptr->size) {
        return OGA_MEMORY_OFFSET_ERROR_UNDERFLOW;
    }
    
    result_ptr->offset = (u64)new_offset;
    
    return OGA_OK;
}

Oga_Result oga_init_vertex_list_view(Oga_Context *context, Oga_Memory_View_Desc desc, Oga_Vertex_List_View **vlist) {
    *vlist = allocate(context->state_allocator, sizeof(Oga_Vertex_List_View));
    if (!*vlist) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **vlist = (Oga_Vertex_List_View){0};
    (*vlist)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkBufferCreateInfo info = (VkBufferCreateInfo){0};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    info.size = (VkDeviceSize)desc.size;
    info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    _vk_assert2(vkCreateBuffer(context->id, &info, &internal->vk_allocs, (VkBuffer*)&(*vlist)->id));
    
    (*vlist)->size = desc.size;
    (*vlist)->memory_pointer = desc.memory_pointer;
    
    _Vk_Memory_State *mem_state = (_Vk_Memory_State*)desc.memory_pointer.id;
    
    if (!(context->device.memory_heaps[desc.memory_pointer.heap_index].supported_usage_flags & OGA_MEMORY_USAGE_VERTEX_LIST)) {
        return OGA_INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT;
    }
    
    _vk_assert2(vkBindBufferMemory(context->id, (*vlist)->id, mem_state->memory, desc.memory_pointer.offset));
    
    return OGA_OK;
}
void oga_uninit_vertex_list_view(Oga_Vertex_List_View *vlist) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)vlist->context->internal;
    _vk_assert1(vkDeviceWaitIdle(vlist->context->id));
    
    vkDestroyBuffer(vlist->context->id, vlist->id, &internal->vk_allocs);
    
    Allocator a = vlist->context->state_allocator;
    *vlist = (Oga_Vertex_List_View){0};
    deallocate(a, vlist);
}

Oga_Result oga_init_index_list_view(Oga_Context *context, Oga_Memory_View_Desc desc, Oga_Index_List_View **ilist) {
    *ilist = allocate(context->state_allocator, sizeof(Oga_Index_List_View));
    if (!*ilist) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **ilist = (Oga_Index_List_View){0};
    (*ilist)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkBufferCreateInfo info = (VkBufferCreateInfo){0};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    info.size = (VkDeviceSize)desc.size;
    info.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    _vk_assert2(vkCreateBuffer(context->id, &info, &internal->vk_allocs, (VkBuffer*)&(*ilist)->id));
    
    (*ilist)->size = desc.size;
    (*ilist)->memory_pointer = desc.memory_pointer;
    
    _Vk_Memory_State *mem_state = (_Vk_Memory_State*)desc.memory_pointer.id;
    
    if (!(context->device.memory_heaps[desc.memory_pointer.heap_index].supported_usage_flags & OGA_MEMORY_USAGE_INDEX_LIST)) {
        return OGA_INIT_INDEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT;
    }
    
    _vk_assert2(vkBindBufferMemory(context->id, (*ilist)->id, mem_state->memory, desc.memory_pointer.offset));
    
    return OGA_OK;
}
void oga_uninit_index_list_view(Oga_Index_List_View *ilist) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)ilist->context->internal;
    _vk_assert1(vkDeviceWaitIdle(ilist->context->id));
    
    vkDestroyBuffer(ilist->context->id, ilist->id, &internal->vk_allocs);
    
    Allocator a = ilist->context->state_allocator;
    *ilist = (Oga_Index_List_View){0};
    deallocate(a, ilist);
}

unit_local Oga_Result _oga_make_vk_image(Oga_Context *context, _Vk_Image_State *state, Oga_Image_View_Desc desc, VkImageUsageFlags usage, VkImageLayout initial_layout) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;

    VkImageType image_type = 0;
    switch (desc.dimensions) {
        case OGA_1D: image_type = VK_IMAGE_TYPE_1D; break;
        case OGA_2D: image_type = VK_IMAGE_TYPE_2D; break;
        case OGA_3D: image_type = VK_IMAGE_TYPE_3D; break;
        default: return OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM;
    }
    
    VkImageCreateInfo info = (VkImageCreateInfo) {0};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.imageType = image_type;
    info.format = _oga_to_vk_format(desc.format);
    info.extent.width = (u32)desc.width;
    info.extent.height = desc.dimensions <= OGA_1D ? 1 : (u32)desc.height;
    info.extent.depth = desc.dimensions <= OGA_2D ? 1 : (u32)desc.depth;
    info.mipLevels = 1;
    info.arrayLayers = 1;
    info.samples = VK_SAMPLE_COUNT_1_BIT;
    info.tiling = desc.linear_tiling ? VK_IMAGE_TILING_LINEAR : VK_IMAGE_TILING_OPTIMAL;
    info.usage = usage;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    
    _vk_assert2(vkCreateImage(context->id, &info, &internal->vk_allocs, &state->image));
    
    if (desc.memory_pointer.offset % context->device.limits.image_memory_granularity != 0) {
        // todo(charlie) #validation
        // What is the offset, what should it be aligned to ?
        return OGA_INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED;
    }
    
    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(context->id, state->image, &mem_req);
    if (mem_req.size > desc.memory_pointer.size-desc.memory_pointer.offset) {
        // todo(charlie) #validation
        // How much is required, how much was allocated ?
        return OGA_INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT;
    }
    
    _vk_assert2(vkBindImageMemory(context->id, state->image, ((_Vk_Memory_State*)desc.memory_pointer.id)->memory, desc.memory_pointer.offset));
    
    VkCommandPool transition_pool = 0;
    VkCommandPoolCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    create_info.flags = 0;
    create_info.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    create_info.queueFamilyIndex = (u32)desc.graphics_engine_family_index;

    _vk_assert2(vkCreateCommandPool((VkDevice)context->id, &create_info, &internal->vk_allocs, &transition_pool));
    
    VkCommandBufferAllocateInfo allocate_info = {0};
    allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocate_info.commandPool = transition_pool;
    allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocate_info.commandBufferCount = 1;

    VkCommandBuffer transition_cmd = 0;
    _vk_assert2(vkAllocateCommandBuffers(context->id, &allocate_info, &transition_cmd));
    
    VkCommandBufferBeginInfo begin_info = (VkCommandBufferBeginInfo){0};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    
    _vk_assert2(vkBeginCommandBuffer(transition_cmd, &begin_info));
     _vk_image_barrier_helper(transition_cmd, state->image, VK_IMAGE_LAYOUT_UNDEFINED, initial_layout);
    _vk_assert2(vkEndCommandBuffer(transition_cmd));
    
    VkSubmitInfo submit_info = (VkSubmitInfo){0};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &transition_cmd;
    
    _vk_assert2(vkQueueSubmit(context->engines_by_family[desc.graphics_engine_family_index].engines[0].id, 1, &submit_info, 0));
    vkQueueWaitIdle(context->engines_by_family[desc.graphics_engine_family_index].engines[0].id);
    vkDestroyCommandPool(context->id, transition_pool, &internal->vk_allocs);
    
    VkImageViewType view_type = 0;
    switch (desc.dimensions) {
        case OGA_1D: view_type = VK_IMAGE_VIEW_TYPE_1D; break;
        case OGA_2D: view_type = VK_IMAGE_VIEW_TYPE_2D; break;
        case OGA_3D: view_type = VK_IMAGE_VIEW_TYPE_3D; break;
        default: return OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM;
    }
    
    VkImageViewCreateInfo view_info = (VkImageViewCreateInfo){0};
    view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    view_info.viewType = view_type;
    view_info.format = _oga_to_vk_format(desc.format);
    view_info.components.r = VK_COMPONENT_SWIZZLE_R;
    view_info.components.g = VK_COMPONENT_SWIZZLE_G;
    view_info.components.b = VK_COMPONENT_SWIZZLE_B;
    view_info.components.a = VK_COMPONENT_SWIZZLE_A;
    view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    view_info.subresourceRange.baseMipLevel = 0;
    view_info.subresourceRange.levelCount = 1;
    view_info.subresourceRange.baseArrayLayer = 0;
    view_info.subresourceRange.layerCount = 1;
    view_info.image = state->image;
     
    _vk_assert2(vkCreateImageView(context->id, &view_info, &internal->vk_allocs, &state->view));
    
    return OGA_OK;
}

Oga_Result oga_init_image_view(Oga_Context *context, Oga_Image_View_Desc desc, Oga_Image_View **image) {
    *image = allocate(context->state_allocator, sizeof(Oga_Image_View) + sizeof(_Vk_Image_State));
    if (!*image) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **image = (Oga_Image_View){0};
    (*image)->context = context;
    (*image)->id = (*image)+1;
    
    _Vk_Image_State *state = (_Vk_Image_State*)(*image)->id;
    
    Oga_Result res = _oga_make_vk_image(context, state, desc, VK_IMAGE_USAGE_SAMPLED_BIT, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    if (res != OGA_OK) return res;
    
    (*image)->memory_pointer = desc.memory_pointer;
    (*image)->width = desc.width;
    (*image)->height = desc.height;
    (*image)->depth = desc.depth;
    (*image)->dimensions = desc.dimensions;
    (*image)->linear_tiling = desc.linear_tiling;
    
    
    return OGA_OK;
}
void oga_uninit_image_view(Oga_Image_View *image) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)image->context->internal;
    _vk_assert1(vkDeviceWaitIdle(image->context->id));
    
    _Vk_Image_State *state = (_Vk_Image_State*)image->id;
    
    vkDestroyImageView(image->context->id, state->view, &internal->vk_allocs);
    vkDestroyImage(image->context->id, state->image, &internal->vk_allocs);
    
    Allocator a = image->context->state_allocator;
    *image = (Oga_Image_View){0};
    deallocate(a, image);
}

Oga_Result oga_init_fbuffer_view(Oga_Context *context, Oga_Image_View_Desc desc, Oga_FBuffer_View **fbuffer) {
    *fbuffer = allocate(context->state_allocator, sizeof(Oga_FBuffer_View) + sizeof(_Vk_Image_State));
    if (!*fbuffer) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **fbuffer = (Oga_FBuffer_View){0};
    (*fbuffer)->context = context;
    (*fbuffer)->id = (*fbuffer)+1;
    
    _Vk_Image_State *state = (_Vk_Image_State*)(*fbuffer)->id;
    
    Oga_Result res = _oga_make_vk_image(context, state, desc, VK_IMAGE_USAGE_STORAGE_BIT, VK_IMAGE_LAYOUT_GENERAL);
    if (res != OGA_OK) return res;
    
    (*fbuffer)->memory_pointer = desc.memory_pointer;
    (*fbuffer)->width = desc.width;
    (*fbuffer)->height = desc.height;
    (*fbuffer)->depth = desc.depth;
    (*fbuffer)->dimensions = desc.dimensions;
    (*fbuffer)->linear_tiling = desc.linear_tiling;
    
    
    return OGA_OK;
}
void oga_uninit_fbuffer_view(Oga_FBuffer_View *fbuffer) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)fbuffer->context->internal;
    _vk_assert1(vkDeviceWaitIdle(fbuffer->context->id));
    
    _Vk_Image_State *state = (_Vk_Image_State*)fbuffer->id;
    
    vkDestroyImageView(fbuffer->context->id, state->view, &internal->vk_allocs);
    vkDestroyImage(fbuffer->context->id, state->image, &internal->vk_allocs);
    
    Allocator a = fbuffer->context->state_allocator;
    *fbuffer = (Oga_FBuffer_View){0};
    deallocate(a, fbuffer);
}

u64 oga_get_image_memory_requirement(Oga_Context *context, Oga_Image_View_Desc desc) {
    VkImage dummy_image;

    VkImageType image_type = 0;
    switch (desc.dimensions) {
        case OGA_1D: image_type = VK_IMAGE_TYPE_1D; break;
        case OGA_2D: image_type = VK_IMAGE_TYPE_2D; break;
        case OGA_3D: image_type = VK_IMAGE_TYPE_3D; break;
        default: return OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM;
    }
    
    VkImageCreateInfo info = (VkImageCreateInfo) {0};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.imageType = image_type;
    info.format = _oga_to_vk_format(desc.format);
    info.extent.width = (u32)desc.width;
    info.extent.height = desc.dimensions <= OGA_1D ? 1 : (u32)desc.height;
    info.extent.depth = desc.dimensions <= OGA_2D ? 1 : (u32)desc.depth;
    info.mipLevels = 1;
    info.arrayLayers = 1;
    info.samples = VK_SAMPLE_COUNT_1_BIT;
    info.tiling = desc.linear_tiling ? VK_IMAGE_TILING_LINEAR : VK_IMAGE_TILING_OPTIMAL;
    info.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    _vk_assert1(vkCreateImage(context->id, &info, &internal->vk_allocs, &dummy_image));
    
    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(context->id, dummy_image, &mem_req);
    
    vkDestroyImage(context->id, dummy_image, &internal->vk_allocs);
    
    return (u64)mem_req.size;
}

Oga_Result oga_init_optimal_copy_view(Oga_Context *context, Oga_Optimal_Copy_View_Desc desc, Oga_Optimal_Copy_View **image) {
    *image = allocate(context->state_allocator, sizeof(Oga_Optimal_Copy_View) + sizeof(_Vk_Image_State));
    if (!*image) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **image = (Oga_Optimal_Copy_View){0};
    (*image)->context = context;
    (*image)->id = (*image)+1;
    
    _Vk_Image_State *state = (_Vk_Image_State*)(*image)->id;
    
    VkImageType image_type = 0;
    switch (desc.dimensions) {
        case OGA_1D: image_type = VK_IMAGE_TYPE_1D; break;
        case OGA_2D: image_type = VK_IMAGE_TYPE_2D; break;
        case OGA_3D: image_type = VK_IMAGE_TYPE_3D; break;
        default: return OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM;
    }
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    VkImageCreateInfo info = (VkImageCreateInfo) {0};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.imageType = image_type;
    info.format = _oga_to_vk_format(desc.format);
    info.extent.width = (u32)desc.width;
    info.extent.height = desc.dimensions <= OGA_1D ? 1 : (u32)desc.height;
    info.extent.depth = desc.dimensions <= OGA_2D ? 1 : (u32)desc.depth;
    info.mipLevels = 1;
    info.arrayLayers = 1;
    info.samples = VK_SAMPLE_COUNT_1_BIT;
    info.tiling = desc.linear_tiling ? VK_IMAGE_TILING_LINEAR : VK_IMAGE_TILING_OPTIMAL;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    info.usage = 0;
    if (desc.flags & OGA_OPTIMAL_COPY_DST) info.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    if (desc.flags & OGA_OPTIMAL_COPY_SRC) info.usage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    
    if (info.usage == 0) {
        return OGA_INIT_OPTIMAL_COPY_VIEW_ERROR_INVALID_FLAGS;
    }
    
    _vk_assert2(vkCreateImage(context->id, &info, &internal->vk_allocs, &state->image));
    
    if (desc.memory_pointer.offset % context->device.limits.image_memory_granularity != 0) {
        // todo(charlie) #validation
        // What is the offset, what should it be aligned to ?
        return OGA_INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED;
    }
    
    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(context->id, state->image, &mem_req);
    if (mem_req.size > desc.memory_pointer.size-desc.memory_pointer.offset) {
        // todo(charlie) #validation
        // How much is required, how much was allocated ?
        return OGA_INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT;
    }
    
    _vk_assert2(vkBindImageMemory(context->id, state->image, ((_Vk_Memory_State*)desc.memory_pointer.id)->memory, desc.memory_pointer.offset));
    
    VkCommandPool transition_pool = 0;
    VkCommandPoolCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    create_info.flags = 0;
    create_info.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    create_info.queueFamilyIndex = (u32)desc.graphics_engine_family_index;

    _vk_assert2(vkCreateCommandPool((VkDevice)context->id, &create_info, &internal->vk_allocs, &transition_pool));
    
    VkCommandBufferAllocateInfo allocate_info = {0};
    allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocate_info.commandPool = transition_pool;
    allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocate_info.commandBufferCount = 1;

    VkCommandBuffer transition_cmd = 0;
    _vk_assert2(vkAllocateCommandBuffers(context->id, &allocate_info, &transition_cmd));
    
    VkCommandBufferBeginInfo begin_info = (VkCommandBufferBeginInfo){0};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    
    _vk_assert2(vkBeginCommandBuffer(transition_cmd, &begin_info));
     _vk_image_barrier_helper(transition_cmd, state->image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL);
    _vk_assert2(vkEndCommandBuffer(transition_cmd));
    
    VkSubmitInfo submit_info = (VkSubmitInfo){0};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &transition_cmd;
    
    _vk_assert2(vkQueueSubmit(context->engines_by_family[desc.graphics_engine_family_index].engines[0].id, 1, &submit_info, 0));
    vkQueueWaitIdle(context->engines_by_family[desc.graphics_engine_family_index].engines[0].id);
    vkDestroyCommandPool(context->id, transition_pool, &internal->vk_allocs);
    
    
    (*image)->memory_pointer = desc.memory_pointer;
    (*image)->width = desc.width;
    (*image)->height = desc.height;
    (*image)->depth = desc.depth;
    (*image)->dimensions = desc.dimensions;
    (*image)->linear_tiling = desc.linear_tiling;
    (*image)->flags = desc.flags;
    
    return OGA_OK;
}
void oga_uninit_optimal_copy_view(Oga_Optimal_Copy_View *image) {
     _Vk_Context_Internal *internal = (_Vk_Context_Internal*)image->context->internal;
    _vk_assert1(vkDeviceWaitIdle(image->context->id));
    
    _Vk_Image_State *state = (_Vk_Image_State*)image->id;
    
    vkDestroyImageView(image->context->id, state->view, &internal->vk_allocs);
    vkDestroyImage(image->context->id, state->image, &internal->vk_allocs);
    
    Allocator a = image->context->state_allocator;
    *image = (Oga_Optimal_Copy_View){0};
    deallocate(a, image);
}

Oga_Result oga_init_block_view(Oga_Context *context, Oga_Memory_View_Desc desc, Oga_Block_View **block) {
    *block = allocate(context->state_allocator, sizeof(Oga_Block_View));
    if (!*block) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **block = (Oga_Block_View){0};
    (*block)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkBufferCreateInfo info = (VkBufferCreateInfo){0};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    info.size = (VkDeviceSize)desc.size;
    info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    _vk_assert2(vkCreateBuffer(context->id, &info, &internal->vk_allocs, (VkBuffer*)&(*block)->id));
    
    (*block)->size = desc.size;
    (*block)->memory_pointer = desc.memory_pointer;
    
    _Vk_Memory_State *mem_state = (_Vk_Memory_State*)desc.memory_pointer.id;
    
    if (!(context->device.memory_heaps[desc.memory_pointer.heap_index].supported_usage_flags & OGA_MEMORY_USAGE_VERTEX_LIST)) {
        return OGA_INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT;
    }
    
    _vk_assert2(vkBindBufferMemory(context->id, (*block)->id, mem_state->memory, desc.memory_pointer.offset));
    
    return OGA_OK;
}
void oga_uninit_block_view(Oga_Block_View *block) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)block->context->internal;
    _vk_assert1(vkDeviceWaitIdle(block->context->id));
    
    vkDestroyBuffer(block->context->id, block->id, &internal->vk_allocs);
    
    Allocator a = block->context->state_allocator;
    *block = (Oga_Block_View){0};
    deallocate(a, block);
}

Oga_Result oga_init_command_pool(Oga_Context *context, Oga_Command_Pool_Desc desc, Oga_Command_Pool **pool) {
    *pool = allocate(context->state_allocator, sizeof(Oga_Command_Pool));
    if (!*pool) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **pool = (Oga_Command_Pool){0};
    (*pool)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;

    VkCommandPoolCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    create_info.flags = 0;

    if (desc.flags & OGA_COMMAND_POOL_SHORT_LIVED_ALLOCATIONS) {
        create_info.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    }

    create_info.queueFamilyIndex = (u32)desc.engine_family_index;

    _vk_assert2(vkCreateCommandPool((VkDevice)context->id, &create_info, &internal->vk_allocs, (VkCommandPool *)&(*pool)->id));

    return OGA_OK;
}

void oga_uninit_command_pool(Oga_Command_Pool *pool) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)pool->context->internal;

    _vk_assert1(vkDeviceWaitIdle(pool->context->id));
    vkResetCommandPool(pool->context->id, pool->id, 0);
    _vk_assert1(vkDeviceWaitIdle(pool->context->id));
    vkDestroyCommandPool(pool->context->id, pool->id, &internal->vk_allocs);

    Allocator a = pool->context->state_allocator;
    *pool = (Oga_Command_Pool){0};
    deallocate(a, pool);
}
void oga_reset_command_pool(Oga_Command_Pool *pool) {
    _vk_assert1(vkResetCommandPool(pool->context->id, pool->id, 0));
}

Oga_Result oga_get_command_lists(Oga_Command_Pool *pool, Oga_Command_List *lists, u64 list_count) {
    VkCommandBufferAllocateInfo allocate_info = {0};
    allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocate_info.commandPool = (VkCommandPool)pool->id;
    allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocate_info.commandBufferCount = (u32)list_count;

    VkCommandBuffer *vk_buffers = PushTempBuffer(VkCommandBuffer, list_count);
    _vk_assert2(vkAllocateCommandBuffers((VkDevice)pool->context->id, &allocate_info, vk_buffers));


    for (u64 i = 0; i < list_count; i += 1) {
        lists[i] = (Oga_Command_List){0};
        lists[i].id = vk_buffers[i];
        lists[i].pool = pool;
    }

    return OGA_OK;
}

void oga_release_command_lists(Oga_Command_List *lists, u64 list_count) {
    VkCommandBuffer *vk_buffers = PushTempBuffer(VkCommandBuffer, list_count);

    Oga_Command_Pool *last_pool = 0;
    
    for (u64 i = 0; i < list_count; i += 1) {
        if (last_pool) {
            assertmsg(last_pool != lists[i].pool, "Command lists from different pools were passed to oga_release_command_lists. All command lists must be from the same pool to do a batched release.");
        }
        last_pool = lists[i].pool;
    
        vk_buffers[i] = (VkCommandBuffer)lists[i].id;
        lists[i] = (Oga_Command_List){0};
    }
    
    _vk_assert1(vkDeviceWaitIdle(last_pool->context->id));
    vkFreeCommandBuffers((VkDevice)last_pool->context->id, (VkCommandPool)last_pool->id, (u32)list_count, vk_buffers);
}


Oga_Result oga_cmd_begin(Oga_Command_List cmd, Oga_Command_List_Usage_Flag flags) {
    VkCommandBufferBeginInfo info = (VkCommandBufferBeginInfo){0};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    if (flags & OGA_COMMAND_LIST_USAGE_ONE_TIME_SUBMIT) 
        info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    _vk_assert2(vkBeginCommandBuffer(cmd.id, &info));
    return OGA_OK;
}
Oga_Result oga_cmd_end(Oga_Command_List cmd) {
    _vk_assert2(vkEndCommandBuffer(cmd.id));
    return OGA_OK;
}
Oga_Result oga_submit_command_list(Oga_Command_List cmd, Oga_Submit_Command_List_Desc desc) {
    
    VkSemaphore *wait_semaphores = PushTempBuffer(VkSemaphore, desc.wait_gpu_latch_count);
    VkPipelineStageFlags *wait_stages = PushTempBuffer(VkPipelineStageFlags, desc.wait_gpu_latch_count);
    VkSemaphore *signal_semaphores = PushTempBuffer(VkSemaphore, desc.signal_gpu_latch_count);
    
    for (u64 i = 0; i < desc.wait_gpu_latch_count; i += 1) {
        wait_semaphores[i] = desc.wait_gpu_latches[i]->id;
        // note(charlie): it's a bit unfortunate to abstract this away from the programmer,
        // because it's a pretty neat opportunity for layout. Maybe we add this to the
        // api but make it sure it only has an effect when targetting vulkan?
        wait_stages[i] = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    }
    for (u64 i = 0; i < desc.signal_gpu_latch_count; i += 1) {
        signal_semaphores[i] = desc.signal_gpu_latches[i]->id;
    }

    VkSubmitInfo info = (VkSubmitInfo){0};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info.waitSemaphoreCount = (u32)desc.wait_gpu_latch_count;
    info.pWaitSemaphores = wait_semaphores;
    info.pWaitDstStageMask = wait_stages;
    info.commandBufferCount = 1; // todo(charlie) api to submit multiple command buffers at a time?
    info.pCommandBuffers = (VkCommandBuffer*)&cmd.id;
    info.signalSemaphoreCount = (u32)desc.signal_gpu_latch_count;
    info.pSignalSemaphores = signal_semaphores;
    
    _vk_assert2(vkQueueSubmit(desc.engine.id, 1, &info, desc.signal_cpu_latch ? desc.signal_cpu_latch->id : 0));
    
    return OGA_OK;    
}

Oga_Result oga_init_gpu_timestamp_pool(Oga_Context *context, u64 timestamp_count, Oga_Gpu_Timestamp_Pool **pool) {
    *pool = allocate(context->state_allocator, sizeof(Oga_Gpu_Timestamp_Pool));
    if (!*pool) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **pool = (Oga_Gpu_Timestamp_Pool){0};
    (*pool)->context = context;
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)context->internal;
    
    VkQueryPoolCreateInfo pool_info = {0};
    pool_info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    pool_info.queryType = VK_QUERY_TYPE_TIMESTAMP;
    pool_info.queryCount = (u32)timestamp_count;
    
    _vk_assert2(vkCreateQueryPool(context->id, &pool_info, &internal->vk_allocs, (VkQueryPool*)&(*pool)->id));
    
    (*pool)->timestamp_count = timestamp_count;
    
    return OGA_OK;
}
void oga_uninit_gpu_timestamp_pool(Oga_Gpu_Timestamp_Pool *pool) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)pool->context->internal;
    _vk_assert1(vkDeviceWaitIdle(pool->context->id));
    
    vkDestroyQueryPool(pool->context->id, pool->id, &internal->vk_allocs);
    
    Allocator a = pool->context->state_allocator;
    *pool = (Oga_Gpu_Timestamp_Pool){0};
    deallocate(a, pool);
}

void oga_cmd_reset_timestamp_pool(Oga_Command_List cmd, Oga_Gpu_Timestamp_Pool *pool) {
    vkCmdResetQueryPool(cmd.id, pool->id, 0, (u32)pool->timestamp_count);
    pool->written_timestamp_count = 0;
}
void oga_cmd_write_timestamp(Oga_Command_List cmd, Oga_Gpu_Timestamp_Pool *pool) {
    if (pool->written_timestamp_count >= pool->timestamp_count) return; // todo(charlie) #validation
    
    vkCmdWriteTimestamp(cmd.id, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, pool->id, (u32)pool->written_timestamp_count);
    pool->written_timestamp_count += 1;
}

Oga_Result oga_read_timestamps(Oga_Gpu_Timestamp_Pool *pool, f64 *nanosecond_timestamps, bool wait) {
    u64 *periods_buffer = PushTempBuffer(u64, pool->written_timestamp_count);
    _vk_assert2(vkGetQueryPoolResults(pool->context->id, pool->id, 0, (u32)pool->written_timestamp_count, pool->written_timestamp_count*sizeof(u64), periods_buffer, sizeof(u64), VK_QUERY_RESULT_64_BIT | (wait ? VK_QUERY_RESULT_WAIT_BIT : 0)));
    
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(pool->context->device.id, &props);
    f64 nanoseconds_per_period = (f64)props.limits.timestampPeriod;
    
    for (u64 i = 0; i < pool->written_timestamp_count; i += 1) {
        nanosecond_timestamps[i] = nanoseconds_per_period * (f64)periods_buffer[i];
    }
    
    return OGA_OK;
}

void oga_cmd_begin_render_pass(Oga_Command_List cmd, Oga_Render_Pass *render_pass, Oga_Begin_Render_Pass_Desc desc) {
    // todo(charlie) #validation
    // Make sure a render target is only active in one render pass at a time
    
    VkRenderingAttachmentInfoKHR vk_attachments[128] = {0};

    for (u64 i = 0; i < desc.attachment_count; i += 1) {
        
        Oga_Render_Attachment_Desc attach_desc = desc.attachments[i];
        
        _Vk_Render_Image_State *state = (_Vk_Render_Image_State*)attach_desc.image->id;
        
        _vk_image_barrier_helper(cmd.id, state->image, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
    
        vk_attachments[i].sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
        vk_attachments[i].imageView = state->view;
        vk_attachments[i].imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        
        if (attach_desc.resolve_mode & OGA_MSAA_RESOLVE_MODE_ZERO)
            vk_attachments[i].resolveMode |= VK_RESOLVE_MODE_SAMPLE_ZERO_BIT_KHR;
        if (attach_desc.resolve_mode & OGA_MSAA_RESOLVE_MODE_AVERAGE)
            vk_attachments[i].resolveMode |= VK_RESOLVE_MODE_AVERAGE_BIT_KHR;
        if (attach_desc.resolve_mode & OGA_MSAA_RESOLVE_MODE_MIN)
            vk_attachments[i].resolveMode |= VK_RESOLVE_MODE_MIN_BIT_KHR;
        if (attach_desc.resolve_mode & OGA_MSAA_RESOLVE_MODE_MAX)
            vk_attachments[i].resolveMode |= VK_RESOLVE_MODE_MAX_BIT_KHR;
            
        if (attach_desc.resolve_image) {
            _Vk_Render_Image_State *resolve_state = (_Vk_Render_Image_State*)attach_desc.resolve_image->id;
            _vk_image_barrier_helper(cmd.id, resolve_state->image, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
    
            vk_attachments[i].resolveImageView = resolve_state->view;
            vk_attachments[i].resolveImageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        }
        
        switch (attach_desc.load_op) {
            case OGA_ATTACHMENT_LOAD_OP_LOAD:
                vk_attachments[i].loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
                break;
            case OGA_ATTACHMENT_LOAD_OP_CLEAR:
                vk_attachments[i].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
                break;
            case OGA_ATTACHMENT_LOAD_OP_NOTHING:
                vk_attachments[i].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
                break;
            default:break;
        }
        switch (attach_desc.store_op) {
            case OGA_ATTACHMENT_STORE_OP_STORE:
                vk_attachments[i].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
                break;
            case OGA_ATTACHMENT_STORE_OP_NOTHING:
                vk_attachments[i].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
                break;
            default:break;
        }
        
        memcpy(vk_attachments[i].clearValue.color.float32, attach_desc.clear_color, sizeof(float32)*4);
    }
    
    VkRenderingAttachmentInfo dummy_attachment = (VkRenderingAttachmentInfo){0};
    dummy_attachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;

    VkRenderingInfoKHR info = (VkRenderingInfoKHR){0};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;
    info.renderArea.offset.x = (s32)desc.render_area_offset_x;
    info.renderArea.offset.y = (s32)desc.render_area_offset_y;
    info.renderArea.extent.width = (u32)desc.render_area_width;
    info.renderArea.extent.height = (u32)desc.render_area_height;
    info.layerCount = 1;
    info.colorAttachmentCount = (u32)desc.attachment_count;
    info.pColorAttachments = vk_attachments;
    info.pDepthAttachment = &dummy_attachment;
    info.pStencilAttachment = &dummy_attachment;
    
    
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)cmd.pool->context->internal;
    internal->vkCmdBeginRenderingKHR(cmd.id, &info);
    
    _Vk_Render_Pass_State *state = (_Vk_Render_Pass_State*)render_pass->id;
    
    state->active_image_count = desc.attachment_count;
    for (u64 i = 0; i < desc.attachment_count; i += 1) {
        _Vk_Render_Image_State *image_state = (_Vk_Render_Image_State*)desc.attachments[i].image->id;
        state->active_images[i] = image_state->image;
        if (desc.attachments[i].resolve_image) {
            _Vk_Render_Image_State *resolve_state = (_Vk_Render_Image_State*)desc.attachments[i].resolve_image->id;
            state->active_resolve_images[i] = resolve_state->image;
        }
    }
    
    vkCmdBindPipeline(cmd.id, VK_PIPELINE_BIND_POINT_GRAPHICS, state->pipeline); 
    
    VkViewport vp = (VkViewport){0};
    vp.x = 0;
    vp.y = 0;
    vp.width = (float)desc.render_area_width;
    vp.height = (float)desc.render_area_height;
    vp.minDepth = 0.0;
    vp.maxDepth = 1.0;
    
    vkCmdSetViewport(cmd.id, 0, 1, &vp);
    
    VkRect2D scissor;
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent.width = info.renderArea.extent.width;
    scissor.extent.height = info.renderArea.extent.height;
    
    vkCmdSetScissor(cmd.id, 0, 1, &scissor);
}
void oga_cmd_end_render_pass(Oga_Command_List cmd, Oga_Render_Pass *render_pass) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)cmd.pool->context->internal;
    
    internal->vkCmdEndRenderingKHR(cmd.id);
    
    _Vk_Render_Pass_State *state = (_Vk_Render_Pass_State*)render_pass->id;
    
    for (u64 i = 0; i < state->active_image_count; i += 1) {
        
        _vk_image_barrier_helper(cmd.id, state->active_images[i], VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
            
        if (state->active_resolve_images[i]) {
            _vk_image_barrier_helper(cmd.id, state->active_resolve_images[i], VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
        }
        
        state->active_images[i] = 0;
        state->active_resolve_images[i] = 0;
    }
    state->active_image_count = 0;
    
}

void oga_cmd_bind_render_pass_binding_list(Oga_Command_List cmd, Oga_Render_Pass *pass, Oga_Binding_List *list) {
    _Vk_Render_Pass_State *pass_state = (_Vk_Render_Pass_State*)pass->id;
    vkCmdBindDescriptorSets(cmd.id, VK_PIPELINE_BIND_POINT_GRAPHICS, pass_state->layout, 0, 1, (VkDescriptorSet*)&list->id, 0, 0);
}

Oga_Result oga_cmd_draw(Oga_Command_List cmd, Oga_Draw_Desc desc) {

    // Potentially bind vertex lists
    switch (desc.draw_type) {
    case OGA_DRAW_VERTEX_LIST:                             // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED:                   // fallthrough
    case OGA_DRAW_VERTEX_LIST_INDEXED:                     // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED:           // fallthrough
    case OGA_DRAW_VERTEX_LIST_INDIRECT:                    // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDIRECT:          // fallthrough
    case OGA_DRAW_VERTEX_LIST_INDEXED_INDIRECT:            // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED_INDIRECT:
        
        if (desc.vertex_list_binding_count == 0) {
            return OGA_CMD_DRAW_ERROR_VERTEX_LIST_BINDING_COUNT_ZERO; 
        }
        
        VkDeviceSize offsets[OGA_MAX_VERTEX_BINDING_COUNT];
        VkBuffer vbuffers[OGA_MAX_VERTEX_BINDING_COUNT];
        
        for (u32 i = 0; i < desc.vertex_list_binding_count; i += 1) {
            Oga_Vertex_List_View *vlist = desc.vertex_list_bindings[i];
            u64 offset = desc.vertex_list_offsets[i];
            if (!vlist) 
                return OGA_CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING; // todo(charlie) #validation user should get a descriptive error conveying exactly which bind point was missing 
            if (desc.vertex_list_offsets[i] >= vlist->size)
                return OGA_CMD_DRAW_ERROR_VERTEX_LIST_OFFSET_OUT_OF_RANGE; // todo(charlie) #validation same as above
            
            offsets[i] = (VkDeviceSize)offset;
            vbuffers[i] = (VkBuffer)vlist->id; 
        }
        
        vkCmdBindVertexBuffers(cmd.id, 0, (u32)desc.vertex_list_binding_count, vbuffers, offsets);
        
        break;
    case OGA_DRAW_INSTANCED: // fallthrough
    case OGA_DRAW_INSTANCED_INDIRECT:                     
        break;
    default:
        return OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM;
    }
    
    // Potentially bind index lists
    switch (desc.draw_type) {
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED:           // fallthrough
    case OGA_DRAW_VERTEX_LIST_INDEXED:                     // fallthrough
    case OGA_DRAW_VERTEX_LIST_INDEXED_INDIRECT:            // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED_INDIRECT:
        
        if (!desc.index_list) {
            return OGA_CMD_DRAW_ERROR_MISSING_INDEX_LIST;
        }
        
        VkIndexType index_type = 0;
        u64 index_size = 0;
        switch (desc.index_type) {
        case OGA_INDEX_U32: 
            index_type = VK_INDEX_TYPE_UINT32; 
            index_size = 4;
            break;
        case OGA_INDEX_U16: 
            index_type = VK_INDEX_TYPE_UINT16; 
            index_size = 2;
            break;
        default:
            return OGA_CMD_DRAW_ERROR_INVALID_INDEX_TYPE_ENUM;
        }
        
        vkCmdBindIndexBuffer(cmd.id, (VkBuffer)desc.index_list->id, (VkDeviceSize)(index_size*desc.index_list_offset), index_type);
        
        break;
    case OGA_DRAW_VERTEX_LIST:                             // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED:                   // fallthrough
    case OGA_DRAW_VERTEX_LIST_INDIRECT:                    // fallthrough
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDIRECT:          // fallthrough
    case OGA_DRAW_INSTANCED: // fallthrough
    case OGA_DRAW_INSTANCED_INDIRECT:                     
        break;
    default:
        return OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM;
    }

    switch (desc.draw_type) {
    case OGA_DRAW_INSTANCED:                              
        vkCmdDraw(cmd.id, (u32)desc.vertex_count, (u32)desc.instance_count, (u32)desc.vertex_start, (u32)desc.instance_start);
        break;
    case OGA_DRAW_VERTEX_LIST:
        vkCmdDraw(cmd.id, (u32)desc.vertex_count, 1, (u32)desc.vertex_start, 0);
        break;
    case OGA_DRAW_VERTEX_LIST_INSTANCED:                  
        vkCmdDraw(cmd.id, (u32)desc.vertex_count, (u32)desc.instance_count, (u32)desc.vertex_start, (u32)desc.instance_start);
        break;
    case OGA_DRAW_VERTEX_LIST_INDEXED:
        vkCmdDrawIndexed(cmd.id, (u32)desc.index_count, 1, (u32)desc.index_start, (s32)desc.vertex_start, 0);
        break;
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED:          
        vkCmdDrawIndexed(cmd.id, (u32)desc.index_count, (u32)desc.instance_count, (u32)desc.index_start, (s32)desc.vertex_start, (u32)desc.instance_start);
        break;
    case OGA_DRAW_INSTANCED_INDIRECT:      
        assertmsg(false, "unimplemented");               
        break;
    case OGA_DRAW_VERTEX_LIST_INDIRECT:                   
        assertmsg(false, "unimplemented");               
        break;
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDIRECT:         
        assertmsg(false, "unimplemented");               
        break;
    case OGA_DRAW_VERTEX_LIST_INDEXED_INDIRECT:           
        assertmsg(false, "unimplemented");               
        break;
    case OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED_INDIRECT: 
        assertmsg(false, "unimplemented");               
        break;
    default:
        return OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM;
    }
    
    return OGA_OK;
}

void oga_cmd_copy_linear(Oga_Command_List cmd, Oga_Memory_Pointer dst, Oga_Memory_Pointer src, u64 size) {
    VkBufferCopy info = (VkBufferCopy){0};
    info.srcOffset = (VkDeviceSize)src.offset;
    info.dstOffset = (VkDeviceSize)dst.offset;
    info.size = (VkDeviceSize)size;
    
    _Vk_Memory_State *src_state = (_Vk_Memory_State*)(src.id);
    _Vk_Memory_State *dst_state = (_Vk_Memory_State*)(dst.id);
    
    vkCmdCopyBuffer(cmd.id, src_state->raw_view, dst_state->raw_view, 1, &info);
}

void oga_cmd_copy_linear_to_image(Oga_Command_List cmd, Oga_Optimal_Copy_View *dst_view, Oga_Optimal_Copy_Desc dst_desc, Oga_Memory_Pointer src) {

    VkBufferImageCopy info = (VkBufferImageCopy){0};
    info.bufferOffset = (VkDeviceSize)src.offset;
    info.imageOffset.x = (s32)dst_desc.offset_x;
    info.imageOffset.y = (s32)dst_desc.offset_y;
    info.imageOffset.z = (s32)dst_desc.offset_z;
    info.imageExtent.width = (u32)dst_desc.width;
    info.imageExtent.height = dst_view->dimensions <= OGA_1D ? 1 : (u32)dst_desc.height;
    info.imageExtent.depth = dst_view->dimensions <= OGA_2D ? 1 : (u32)dst_desc.depth;
    info.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    info.imageSubresource.mipLevel = 0;
    info.imageSubresource.baseArrayLayer = 0;
    info.imageSubresource.layerCount = 1;
    
    _Vk_Image_State *dst_state = (_Vk_Image_State*)(dst_view->id);
    _Vk_Memory_State *src_state = (_Vk_Memory_State*)(src.id);
    
    _vk_image_barrier_helper(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    vkCmdCopyBufferToImage(cmd.id, src_state->raw_view, dst_state->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &info);
    _vk_image_barrier_helper(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
}
void oga_cmd_copy_image_to_linear(Oga_Command_List cmd, Oga_Memory_Pointer dst, Oga_Optimal_Copy_View *src_view, Oga_Optimal_Copy_Desc src_desc) {

    VkBufferImageCopy info = (VkBufferImageCopy){0};
    info.bufferOffset = (VkDeviceSize)dst.offset;
    info.imageOffset.x = (s32)src_desc.offset_x;
    info.imageOffset.y = (s32)src_desc.offset_y;
    info.imageOffset.z = (s32)src_desc.offset_z;
    info.imageExtent.width = (u32)src_desc.width;
    info.imageExtent.height = src_view->dimensions <= OGA_1D ? 1 : (u32)src_desc.height;
    info.imageExtent.depth = src_view->dimensions <= OGA_2D ? 1 : (u32)src_desc.depth;
    info.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    info.imageSubresource.mipLevel = 0;
    info.imageSubresource.baseArrayLayer = 0;
    info.imageSubresource.layerCount = 1;
    
    _Vk_Image_State *src_state = (_Vk_Image_State*)(src_view->id);
    _Vk_Memory_State *dst_state = (_Vk_Memory_State*)(dst.id);
    
    _vk_image_barrier_helper(cmd.id, src_state->image, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
    vkCmdCopyImageToBuffer(cmd.id, src_state->image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dst_state->raw_view, 1, &info);
    _vk_image_barrier_helper(cmd.id, src_state->image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
}

void oga_cmd_copy_image(Oga_Command_List cmd, Oga_Optimal_Copy_View *dst_view, Oga_Optimal_Copy_Desc dst_desc, Oga_Optimal_Copy_View *src_view, Oga_Optimal_Copy_Desc src_desc) {
    VkImageCopy info = (VkImageCopy){0};
    
    info.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    info.srcSubresource.mipLevel = 0;
    info.srcSubresource.baseArrayLayer = 0;
    info.srcSubresource.layerCount = 1;
    info.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    info.dstSubresource.mipLevel = 0;
    info.dstSubresource.baseArrayLayer = 0;
    info.dstSubresource.layerCount = 1;
    info.srcOffset.x = (s32)src_desc.offset_x;
    info.srcOffset.y = (s32)src_desc.offset_y;
    info.srcOffset.z = (s32)src_desc.offset_z;
    info.dstOffset.x = (s32)dst_desc.offset_x;
    info.dstOffset.y = (s32)dst_desc.offset_y;
    info.dstOffset.z = (s32)dst_desc.offset_z;
    info.extent.width = (u32)dst_desc.width;
    info.extent.height = dst_view->dimensions <= OGA_1D ? 1 : (u32)dst_desc.height;
    info.extent.depth = dst_view->dimensions <= OGA_2D ? 1 : (u32)dst_desc.depth;
    
    _Vk_Image_State *src_state = (_Vk_Image_State*)(src_view->id);
    _Vk_Image_State *dst_state = (_Vk_Image_State*)(dst_view->id);
    
    _vk_image_barrier_helper(cmd.id, src_state->image, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
    _vk_image_barrier_helper(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    vkCmdCopyImage(cmd.id, src_state->image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dst_state->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &info);
    _vk_image_barrier_helper(cmd.id, src_state->image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
    _vk_image_barrier_helper(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
}

void oga_cmd_fill_image(Oga_Command_List cmd, Oga_Optimal_Copy_View *dst_view, f32v4 color) {
    _Vk_Image_State *dst_state = (_Vk_Image_State*)(dst_view->id);
    
    VkClearColorValue vk_color;
    vk_color.float32[0] = color.x;
    vk_color.float32[1] = color.y;
    vk_color.float32[2] = color.z;
    vk_color.float32[3] = color.w;
    
    VkImageSubresourceRange sub = (VkImageSubresourceRange){0};
    sub.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    sub.baseMipLevel = 0;
    sub.levelCount = 1;
    sub.baseArrayLayer = 0;
    sub.layerCount = 1;
    
    _vk_image_barrier_helper(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    vkCmdClearColorImage(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &vk_color, 1, &sub);
    _vk_image_barrier_helper(cmd.id, dst_state->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
}

#undef uint8_t
#undef int8_t
#undef uint16_t
#undef int16_t
#undef uint32_t
#undef int32_t
#undef uint64_t
#undef int64_t
