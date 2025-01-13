
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



// For syntax highligthing
#if 0
#include "ostd.h"
#endif



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

typedef struct _Vk_Image_State {
    VkImage image;
    VkImageView view;
} _Vk_Image_State;

typedef struct _Vk_Swapchain_State {
    VkSwapchainKHR vk_swapchain;
    VkSurfaceKHR vk_surface;
} _Vk_Swapchain_State;

typedef struct _Vk_Pipeline_State {
    VkPipeline pipeline;
    VkPipelineLayout layout;
} _Vk_Pipeline_State;

typedef struct _Vk_Context_Internal {
    u32 vk_version_major;
    u32 vk_version_minor;
    u32 vk_version_patch;
    bool dynamic_rendering;
    bool dynamic_rendering_is_extension;
    
    PFN_vkCmdBeginRenderingKHR vkCmdBeginRenderingKHR;
    PFN_vkCmdEndRenderingKHR vkCmdEndRenderingKHR;
} _Vk_Context_Internal;

typedef struct _Vk_Memory_Block {
    VkDeviceMemory memory;
    VkAccessFlags access_state;
    
    VkBuffer access_buffer;
} _Vk_Memory_Block;

unit_local inline VkFormat _oga_to_vk_format(Oga_Format k) {
    switch (k) {
        case OGA_FORMAT_R8_UNORM:               return VK_FORMAT_R8_UNORM;
        case OGA_FORMAT_R8_SNORM:               return VK_FORMAT_R8_SNORM;
        case OGA_FORMAT_R8_UINT:                return VK_FORMAT_R8_UINT;
        case OGA_FORMAT_R8_SINT:                return VK_FORMAT_R8_SINT;
        case OGA_FORMAT_R8G8_UNORM:             return VK_FORMAT_R8G8_UNORM;
        case OGA_FORMAT_R8G8_SNORM:             return VK_FORMAT_R8G8_SNORM;
        case OGA_FORMAT_R8G8_UINT:              return VK_FORMAT_R8G8_UINT;
        case OGA_FORMAT_R8G8_SINT:              return VK_FORMAT_R8G8_SINT;
        case OGA_FORMAT_R8G8B8A8_UNORM:         return VK_FORMAT_R8G8B8A8_UNORM;
        case OGA_FORMAT_R8G8B8A8_SNORM:         return VK_FORMAT_R8G8B8A8_SNORM;
        case OGA_FORMAT_R8G8B8A8_UINT:          return VK_FORMAT_R8G8B8A8_UINT;
        case OGA_FORMAT_R8G8B8A8_SINT:          return VK_FORMAT_R8G8B8A8_SINT;
        case OGA_FORMAT_R8G8B8A8_SRGB:          return VK_FORMAT_R8G8B8A8_SRGB;
        case OGA_FORMAT_B8G8R8A8_UNORM:         return VK_FORMAT_B8G8R8A8_UNORM;
        case OGA_FORMAT_B8G8R8A8_SNORM:         return VK_FORMAT_B8G8R8A8_SNORM;
        case OGA_FORMAT_B8G8R8A8_UINT:          return VK_FORMAT_B8G8R8A8_UINT;
        case OGA_FORMAT_B8G8R8A8_SINT:          return VK_FORMAT_B8G8R8A8_SINT;
        case OGA_FORMAT_B8G8R8A8_SRGB:          return VK_FORMAT_B8G8R8A8_SRGB;
        case OGA_FORMAT_R16G16B16A16_SFLOAT:    return VK_FORMAT_R16G16B16A16_SFLOAT;
        case OGA_FORMAT_R32G32B32A32_SFLOAT:    return VK_FORMAT_R32G32B32A32_SFLOAT;
        case OGA_FORMAT_DEPTH32_SFLOAT:         return VK_FORMAT_D32_SFLOAT;
        case OGA_FORMAT_DEPTH32_SFLOAT_S8_UINT: return VK_FORMAT_D32_SFLOAT_S8_UINT;
        case OGA_FORMAT_DEPTH24_UNORM_S8_UINT:  return VK_FORMAT_D24_UNORM_S8_UINT;
        case OGA_FORMAT_DEPTH16_UNORM:          return VK_FORMAT_D16_UNORM;

        case OGA_FORMAT_ENUM_MAX:
        default:
        return (VkFormat)0;
    }
    return (VkFormat)0;
}
unit_local inline Oga_Format _vk_to_oga_format(VkFormat k) {
    switch ((s64)k) {
        case VK_FORMAT_R8_UNORM:            return OGA_FORMAT_R8_UNORM;
        case VK_FORMAT_R8_SNORM:            return OGA_FORMAT_R8_SNORM;
        case VK_FORMAT_R8_UINT:             return OGA_FORMAT_R8_UINT;
        case VK_FORMAT_R8_SINT:             return OGA_FORMAT_R8_SINT;
        case VK_FORMAT_R8G8_UNORM:          return OGA_FORMAT_R8G8_UNORM;
        case VK_FORMAT_R8G8_SNORM:          return OGA_FORMAT_R8G8_SNORM;
        case VK_FORMAT_R8G8_UINT:           return OGA_FORMAT_R8G8_UINT;
        case VK_FORMAT_R8G8_SINT:           return OGA_FORMAT_R8G8_SINT;
        case VK_FORMAT_R8G8B8A8_UNORM:      return OGA_FORMAT_R8G8B8A8_UNORM;
        case VK_FORMAT_R8G8B8A8_SNORM:      return OGA_FORMAT_R8G8B8A8_SNORM;
        case VK_FORMAT_R8G8B8A8_UINT:       return OGA_FORMAT_R8G8B8A8_UINT;
        case VK_FORMAT_R8G8B8A8_SINT:       return OGA_FORMAT_R8G8B8A8_SINT;
        case VK_FORMAT_R8G8B8A8_SRGB:       return OGA_FORMAT_R8G8B8A8_SRGB;
        case VK_FORMAT_B8G8R8A8_UNORM:      return OGA_FORMAT_B8G8R8A8_UNORM;
        case VK_FORMAT_B8G8R8A8_SNORM:      return OGA_FORMAT_B8G8R8A8_SNORM;
        case VK_FORMAT_B8G8R8A8_UINT:       return OGA_FORMAT_B8G8R8A8_UINT;
        case VK_FORMAT_B8G8R8A8_SINT:       return OGA_FORMAT_B8G8R8A8_SINT;
        case VK_FORMAT_B8G8R8A8_SRGB:       return OGA_FORMAT_B8G8R8A8_SRGB;
        case VK_FORMAT_R16G16B16A16_SFLOAT: return OGA_FORMAT_R16G16B16A16_SFLOAT;
        case VK_FORMAT_R32G32B32A32_SFLOAT: return OGA_FORMAT_R32G32B32A32_SFLOAT;
        case VK_FORMAT_D32_SFLOAT:          return OGA_FORMAT_DEPTH32_SFLOAT;
        case VK_FORMAT_D32_SFLOAT_S8_UINT:  return OGA_FORMAT_DEPTH32_SFLOAT_S8_UINT;
        case VK_FORMAT_D24_UNORM_S8_UINT:   return OGA_FORMAT_DEPTH24_UNORM_S8_UINT;
        case VK_FORMAT_D16_UNORM:           return OGA_FORMAT_DEPTH16_UNORM;

        case OGA_FORMAT_ENUM_MAX:
        default:
        return (Oga_Format)0;
    }
    return (Oga_Format)0;
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

#define _vk_assert1(expr) do { VkResult _res = expr; string _res_str = _str_vk_result(_res); assertmsgs(_res == VK_SUCCESS, tprint("Vulkan call %s failed: %s. If you see this, you're either doing something very wrong, or there is an internal error in Oga.", STR(#expr), _res_str)); } while(0)
#define _vk_assert2(expr) do { VkResult _res = expr; if (_res == VK_ERROR_OUT_OF_DEVICE_MEMORY) return OGA_ERROR_OUT_OF_DEVICE_MEMORY; if (_res == VK_ERROR_OUT_OF_HOST_MEMORY) return OGA_ERROR_STATE_ALLOCATION_FAILED;  string _res_str = _str_vk_result(_res); assertmsgs(_res == VK_SUCCESS, tprint("Vulkan call %s failed: %s. If you see this, you're either doing something very wrong, or there is an internal error in Oga.", STR(#expr), _res_str)); } while(0)


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

    log(0, "\n-----------------VK VALIDATION MESSAGE-----------------");
    log(0, "Severity: %s", sev);
    if (pCallbackData->pMessageIdName)
        log(0, "- Message ID: %s", STR(pCallbackData->pMessageIdName));
    if (pCallbackData->pMessage)
        log(0, "- Message: %s", STR(pCallbackData->pMessage));

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
    
        log(0, "Supported Vulkan Instance API version: %u.%u\n", version_major, version_minor);

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
        "VK_KHR_get_physical_device_properties2"
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
        "VK_KHR_get_physical_device_properties2"
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

        log(0, "Looking for extensions:");
        for (u64 i = 0; i < num_required_extensions; i += 1) {
            log(0, "\t%s", STR(required_extensions[i]));
        }

        // #Portability dynamic rendering
        u32 num_available_extensions;
        _vk_assert1(vkEnumerateInstanceExtensionProperties(0, &num_available_extensions, 0));
        VkExtensionProperties *available_extensions = NewBuffer(get_temp(), VkExtensionProperties, num_available_extensions);
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
                log(0, "Missing required vulkan extension '%s'", STR(required));
                log(0, "List of available extensions:");
                for (u32 j = 0; j < num_available_extensions; j += 1) {
                    const char *available = available_extensions[j].extensionName;
                    log(0, "\t%s", STR(available));
                }
                    
            } else {
                log(0, "Found '%s'..", STR(required));
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

        VkLayerProperties *available_layers = NewBuffer(get_temp(), VkLayerProperties, num_available_layers);
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
                log(0, "Missing wanted vulkan validation layer '%s'", STR(wanted));
                if (num_available_layers) {
                    log(0, "List of available validation layers:");
                    for (u32 j = 0; j < num_available_layers; j += 1) {
                        const char *available = available_layers[j].layerName;
                        log(0, "\t%s", STR(available));
                    }
                } else {
                    log(0, "No validation layers available");
                }
            } else {
                final_layers[num_final_layers++] = wanted;
                log(0, "Found validation layer %s", STR(wanted));
            }
        }

        create_info.enabledLayerCount = num_final_layers;
        create_info.ppEnabledLayerNames = final_layers;
#else
        create_info.enabledLayerCount = 0;
#endif

        _vk_assert1(vkCreateInstance(&create_info, 0, &__instance));

#if DEBUG
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
            log(0, "Failed creating vulkan debug messenger");
        }
#endif // DEBUG
    }


    return __instance;
}

void oga_reset(void) {
    void (*untyped)(void) = vkGetInstanceProcAddr(__instance, "vkDestroyDebugUtilsMessengerEXT");
    PFN_vkDestroyDebugUtilsMessengerEXT _vkDestroyDebugUtilsMessengerEXT  = (PFN_vkDestroyDebugUtilsMessengerEXT)*(PFN_vkDestroyDebugUtilsMessengerEXT*)(void**)&untyped;
    _vkDestroyDebugUtilsMessengerEXT(_vk_instance(), _vk_messenger, 0);
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
    log(0, "VK Allocation '%s'  %u bytes, %u alignment %u", scope_str, size, alignment, p);
    //sys_print_stack_trace(sys_get_stdout());
    //log(0, "------------------------------------\n");
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
    log(0, "VK REallocation '%s'  %u bytes, %u alignment ", scope_str, size, alignment);
    //sys_print_stack_trace(sys_get_stdout());
    //log(0, "------------------------------------\n");
#endif
    Allocator *allocator = (Allocator *)ud;
    return allocator->proc(ALLOCATOR_REALLOCATE, allocator->data, old, 0, size, alignment, 0);
}

unit_local void _vk_deallocate(void *ud, void *old) {
#ifdef LOG_VULKAN_ALLOCATIONS
    log(0, "VK FREE %u", old);
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
            VkExtensionProperties *ext_props = NewBuffer(get_temp(), VkExtensionProperties, ext_count);
            vkEnumerateDeviceExtensionProperties(vk_device, 0, &ext_count, ext_props);

            u32 engine_family_count;
            vkGetPhysicalDeviceQueueFamilyProperties(vk_device, &engine_family_count, 0);
            VkQueueFamilyProperties *engine_family_props = NewBuffer(get_temp(), VkQueueFamilyProperties, engine_family_count);
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
                log(0, ("WARNING: Could not find a supported depth format on this device."));
                vk_depth_format = VK_FORMAT_D32_SFLOAT;
            }

            device->depth_format = _vk_to_oga_format(vk_depth_format);

            /////
            // Memory heaps

            for (u32 j = 0; j < mem_props.memoryHeapCount; j += 1) {
                device->memory_heaps[j].size = (u64)mem_props.memoryHeaps[j].size;
            }
            device->memory_heap_count = mem_props.memoryHeapCount;

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
            }

            for (u32 j = 0; j < device->memory_heap_count; j += 1) {
                if (device->memory_heaps[j].properties & OGA_MEMORY_PROPERTY_GPU_LOCAL)
                    device->total_gpu_local_memory += device->memory_heaps[j].size;
            }


            
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
            
            if (features.depthClamp)
                device->features |= OGA_DEVICE_FEATURE_DEPTH_CLAMP;
                
            /////
            // Limits

            device->limits.max_program_pointer_sets_per_stage = props.limits.maxPerStageResources;
            device->limits.max_fast_data_blocks_per_stage = props.limits.maxPerStageDescriptorUniformBuffers;
            device->limits.max_large_data_blocks_per_stage = props.limits.maxPerStageDescriptorStorageBuffers;
            device->limits.max_fast_images_per_stage = props.limits.maxPerStageDescriptorSampledImages;
            device->limits.max_large_images_per_stage = props.limits.maxPerStageDescriptorStorageImages;
            device->limits.max_samplers_per_stage = props.limits.maxPerStageDescriptorSamplers;
            device->limits.max_fast_data_blocks_per_layout = props.limits.maxDescriptorSetUniformBuffers;
            device->limits.max_large_data_blocks_per_layout = props.limits.maxDescriptorSetStorageBuffers;
            device->limits.max_fast_images_per_layout = props.limits.maxDescriptorSetSampledImages;
            device->limits.max_large_images_per_layout = props.limits.maxDescriptorSetStorageImages;
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
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.framebufferColorSampleCounts & f) device->limits.supported_sample_counts_render_pass |= f;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.sampledImageColorSampleCounts & f) device->limits.supported_sample_counts_fast_image_float |= f;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.storageImageSampleCounts & f) device->limits.supported_sample_counts_large_image_float |= f;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.sampledImageIntegerSampleCounts & f) device->limits.supported_sample_counts_fast_image_int |= f;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.storageImageSampleCounts & f) device->limits.supported_sample_counts_large_image_int |= f;

            device->limits.memory_granularity = (u64)props.limits.bufferImageGranularity;

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

    const char *swapchain_ext = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

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

    VkPhysicalDeviceFeatures enabled_features = (VkPhysicalDeviceFeatures){0};
    // if (desc.enabled_features & OGA_DEVICE_FEATURE_XXXX) enabled_features.xxxx = true;

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
    
    if (target_device.features & OGA_DEVICE_FEATURE_DEPTH_CLAMP) {
        enabled_features.depthClamp = true;
    }
    
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(target_device.id, &props);

    VkDeviceCreateInfo info = (VkDeviceCreateInfo) {0};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    info.pEnabledFeatures = &enabled_features;
    info.queueCreateInfoCount = (u32)engines_desc_count;
    info.pQueueCreateInfos = engine_infos;
    
    
    internal->vk_version_major = VK_VERSION_MAJOR(props.apiVersion);
    internal->vk_version_minor = VK_VERSION_MINOR(props.apiVersion);
    internal->vk_version_patch = VK_VERSION_PATCH(props.apiVersion);
    
    string name = (string){target_device.device_name_length, target_device.device_name_data};
    string api = (string){target_device.api_version_length, target_device.api_version_data};
    log(0, "Making context for device '%s', api version '%s'", name, api);
    
    if (internal->vk_version_major == 1 && internal->vk_version_minor < 3) {
        
        uint32_t existing_count = 0;
        vkEnumerateDeviceExtensionProperties(target_device.id, 0, &existing_count, 0);
        VkExtensionProperties *existing_exts = NewBuffer(get_temp(), VkExtensionProperties, existing_count);
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
        
        char **names = NewBuffer(get_temp(), char*, 8);
        
        
        info.enabledExtensionCount = 0;
        internal->dynamic_rendering = ext_dynamic_rendering;
        names[info.enabledExtensionCount++] = "VK_KHR_dynamic_rendering";
        if (internal->vk_version_minor <= 1) {
            internal->dynamic_rendering &= ext_depth_stencil_resolve;
            names[info.enabledExtensionCount++] = "VK_KHR_depth_stencil_resolve";
            internal->dynamic_rendering &= ext_create_renderpass2;
            names[info.enabledExtensionCount++] = "VK_KHR_create_renderpass2";
        }
            
        
        names[info.enabledExtensionCount++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
        
        info.ppEnabledExtensionNames = (const char*const*)names;
        
        internal->dynamic_rendering_is_extension = true;
    } else {
        internal->dynamic_rendering = true;
        internal->dynamic_rendering_is_extension = false;
        info.enabledExtensionCount = 1;
        info.ppEnabledExtensionNames 
            = &swapchain_ext;
    }
    
    log(0, "Dynamic rendering: %b", internal->dynamic_rendering);
    
    if (internal->dynamic_rendering) {
        if (internal->dynamic_rendering_is_extension) {
            void (*untyped)(void) = vkGetInstanceProcAddr(__instance, "vkCmdBeginRenderingKHR");
            internal->vkCmdBeginRenderingKHR  = (PFN_vkCmdBeginRenderingKHR)*(PFN_vkCmdBeginRenderingKHR*)(void**)&untyped;
            untyped = vkGetInstanceProcAddr(__instance, "vkCmdEndRenderingKHR");
            internal->vkCmdEndRenderingKHR  = (PFN_vkCmdEndRenderingKHR)*(PFN_vkCmdEndRenderingKHR*)(void**)&untyped;
            
            info.pNext = &dynamic_rendering;
            
        } else {
            void (*untyped)(void) = vkGetInstanceProcAddr(__instance, "vkCmdBeginRendering");
            internal->vkCmdBeginRenderingKHR  = (PFN_vkCmdBeginRenderingKHR)*(PFN_vkCmdBeginRenderingKHR*)(void**)&untyped;
            untyped = vkGetInstanceProcAddr(__instance, "vkCmdEndRendering");
            internal->vkCmdEndRenderingKHR  = (PFN_vkCmdEndRenderingKHR)*(PFN_vkCmdEndRenderingKHR*)(void**)&untyped;
            
            info.pNext = &vk13_features;
        }
        
    }

    VkAllocationCallbacks vk_allocs = _vk_allocator(&c->state_allocator);
    _vk_assert2(vkCreateDevice(target_device.id, &info, &vk_allocs, (VkDevice*)&c->id));
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
    
    

    return OGA_OK;
}
void oga_uninit_context(Oga_Context *context) {
    VkAllocationCallbacks vk_allocs = _vk_allocator(&context->state_allocator);
    _vk_assert1(vkDeviceWaitIdle(context->id));
    vkDestroyDevice(context->id, &vk_allocs);
    
    Allocator a = context->state_allocator;
    *context = (Oga_Context){0};
    deallocate(a, context);
}

Oga_Result oga_init_swapchain(Oga_Context *context, Oga_Swapchain_Desc desc, Oga_Swapchain **swapchain) {
    *swapchain = allocate(context->state_allocator, sizeof(Oga_Swapchain) + sizeof(_Vk_Swapchain_State));
    if (!*swapchain) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }
    **swapchain = (Oga_Swapchain){0};
    
    _Vk_Swapchain_State *state = (_Vk_Swapchain_State*)(*swapchain+1);
    
    VkAllocationCallbacks vk_allocs = _vk_allocator(&context->state_allocator);
    
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
    
    u32 *engine_families = 0;
    u32 engine_families_count = 0;
    if (desc.engine_families_with_access_count) {
        engine_families = NewBuffer(get_temp(), u32, desc.engine_families_with_access_count);
        for (u64 i = 0; i < desc.engine_families_with_access_count; i += 1) {
            bool contains = false;
            for (u64 j = 0; j < engine_families_count; j += 1) {
                if (engine_families[j] == desc.engine_families_with_access[i]) {
                    contains = true;
                    break;
                }
            }
            if (!contains) engine_families[engine_families_count++] = (u32)desc.engine_families_with_access[i];
        }
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
    info.imageSharingMode = engine_families_count > 1 ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
    info.queueFamilyIndexCount = engine_families_count;
    info.pQueueFamilyIndices = engine_families;
    info.preTransform = cap.currentTransform;
    info.compositeAlpha = composite_alpha;
    info.presentMode = vk_present_mode;
    info.clipped = VK_TRUE;
    info.oldSwapchain = 0;
    info.imageArrayLayers = 1;
    
    _vk_assert2(vkCreateSwapchainKHR((VkDevice)context->id, &info, &vk_allocs, &state->vk_swapchain));
    
    VkImage vk_images[MAX_SWAPCHAIN_IMAGES];
    
    vkGetSwapchainImagesKHR((VkDevice)context->id, state->vk_swapchain, (u32*)&(*swapchain)->image_count, vk_images);
    
    (*swapchain)->image_format = desc.image_format;
    
    u64 stride = sizeof(_Vk_Image_State)+sizeof(Oga_Image);
    void *image_states_data = allocate(context->state_allocator, stride * (*swapchain)->image_count);
    for (u64 i = 0; i < (*swapchain)->image_count; i += 1) {
        Oga_Image *image = (Oga_Image*)((u8*)image_states_data + i*stride);
        _Vk_Image_State *image_state = (_Vk_Image_State*)(image+1);
        
        
        image->image_kind = OGA_IMAGE_2D;
        image->id = image_state;
        image->pointer_kind = OGA_POINTER_KIND_PROGRAM_POINTER;
        image->memory = OGA_INTERNALLY_MANAGED_MEMORY_HANDLE;
        image->program_pointer_kind = OGA_PROGRAM_POINTER_KIND_IMAGE2D;
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
        
        _vk_assert2(vkCreateImageView((VkDevice)context->id, &image_view_info, &vk_allocs, &image_state->view));
        
        
        
        (*swapchain)->images[i] = image;
    }
    
    (*swapchain)->context = context;
    
    return OGA_OK;
}
void oga_uninit_swapchain(Oga_Swapchain *swapchain) {
    _Vk_Swapchain_State *state = (_Vk_Swapchain_State*)(swapchain->id);
    VkAllocationCallbacks vk_allocs = _vk_allocator(&swapchain->context->state_allocator);
    
    _vk_assert1(vkDeviceWaitIdle(swapchain->context->id));
    
    for (u64 i = 0; i < swapchain->image_count; i += 1) {
        _Vk_Image_State *image_state = (_Vk_Image_State*)(swapchain->images[i]->id);
        vkDestroyImageView((VkDevice)swapchain->context->id, image_state->view, &vk_allocs);
    }
    
    vkDestroySwapchainKHR((VkDevice)swapchain->context->id, state->vk_swapchain, &vk_allocs);
    
    
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
    
    VkShaderModuleCreateInfo info = (VkShaderModuleCreateInfo){0};
    
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.codeSize = (size_t)desc.code_size;
    info.pCode = desc.code;
    
    VkAllocationCallbacks vk_allocs = _vk_allocator(&context->state_allocator);
    VkResult result = vkCreateShaderModule((VkDevice)context->id, &info, &vk_allocs, (VkShaderModule*)&(*program)->id);
    
    if (result != VK_SUCCESS) {
        if (result == VK_ERROR_INVALID_SHADER_NV) {
            deallocate(context->state_allocator, *program);
            return OGA_INIT_PROGRAM_ERROR_BAD_CODE;
        }
        _vk_assert2(result);
    }
    
    (*program)->context = context;
    
    return OGA_OK;
}
void oga_uninit_program(Oga_Program *program) {
    VkAllocationCallbacks vk_allocs = _vk_allocator(&program->context->state_allocator);
    
    _vk_assert1(vkDeviceWaitIdle(program->context->id));
    vkDestroyShaderModule((VkDevice)program->context->id, (VkShaderModule)program->id, &vk_allocs);
    
    Allocator a = program->context->state_allocator;
    *program = (Oga_Program){0};
    deallocate(a, program);
}

Oga_Result oga_init_render_passes(Oga_Context *context, Oga_Render_Pass_Desc* descs, Oga_Render_Pass **render_passes, u64 render_pass_count) {
    VkGraphicsPipelineCreateInfo *infos = NewBuffer(get_temp(), VkGraphicsPipelineCreateInfo, render_pass_count);
    
    // todo(charlie)
    // We use a lot of temporary storage here, so we would probably want to reset it back to where it was before,
    // once that's implemented ..
    for (u64 i = 0; i < render_pass_count; i += 1) {
    
        Oga_Render_Pass_Desc desc = descs[i];
        
        VkFormat *vk_formats = NewBuffer(get_temp(), VkFormat, desc.attachment_count);
        for (u64 j = 0; j < desc.attachment_count; j += 1) {
            vk_formats[j] = _oga_to_vk_format(desc.attachment_formats[j]);
        }
        
        VkPipelineRenderingCreateInfoKHR *rendering = New(get_temp(), VkPipelineRenderingCreateInfoKHR);
        *rendering = (VkPipelineRenderingCreateInfoKHR){0};
        rendering->sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
        rendering->pNext = 0;
        rendering->viewMask = 0;
        rendering->colorAttachmentCount = (u32)desc.attachment_count;
        rendering->pColorAttachmentFormats = vk_formats;
        
        VkPipelineCreateFlags pipeline_flags = (VkPipelineCreateFlags)(int)0;
        if (desc.flags & OGA_RENDER_PASS_INHERITANCE_PARENT) pipeline_flags |= VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT;
        if (desc.flags & OGA_RENDER_PASS_INHERITANCE_CHILD)  pipeline_flags |= VK_PIPELINE_CREATE_DERIVATIVE_BIT;
        
        char *vert_entry = NewBuffer(get_temp(), char, desc.vertex_program_entry_point.count);
        char *frag_entry = NewBuffer(get_temp(), char, desc.fragment_program_entry_point.count);
        memcpy(vert_entry, desc.vertex_program_entry_point.data, desc.vertex_program_entry_point.count);
        memcpy(frag_entry, desc.fragment_program_entry_point.data, desc.fragment_program_entry_point.count);
        vert_entry[desc.vertex_program_entry_point.count] = 0;
        frag_entry[desc.fragment_program_entry_point.count] = 0;
        
        VkPipelineShaderStageCreateInfo *stages = NewBuffer(get_temp(), VkPipelineShaderStageCreateInfo, 2);
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
        
        VkPipelineVertexInputStateCreateInfo *vertex_input = New(get_temp(), VkPipelineVertexInputStateCreateInfo);
        *vertex_input = (VkPipelineVertexInputStateCreateInfo){0};
        vertex_input->sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertex_input->vertexBindingDescriptionCount = 0;
        vertex_input->vertexAttributeDescriptionCount = 0;
        
        VkPipelineInputAssemblyStateCreateInfo *ia = New(get_temp(), VkPipelineInputAssemblyStateCreateInfo);
        *ia = (VkPipelineInputAssemblyStateCreateInfo){0};
        ia->sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        ia->topology = (VkPrimitiveTopology)desc.topology; // #Volatile values must map to same as vulkan equivalents
        
        VkPipelineTessellationStateCreateInfo *tessellation = New(get_temp(), VkPipelineTessellationStateCreateInfo);
        *tessellation = (VkPipelineTessellationStateCreateInfo){0};
        tessellation->sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
        tessellation->patchControlPoints = 0;
        
        VkPipelineViewportStateCreateInfo *viewport = New(get_temp(), VkPipelineViewportStateCreateInfo);
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
        
        VkBool32 depth_clamp_enable = (desc.flags & OGA_RENDER_PASS_DISABLE_DEPTH_CLAMP) == 0;

        if (depth_clamp_enable && !(context->device.features & OGA_DEVICE_FEATURE_DEPTH_CLAMP)) {
            depth_clamp_enable = false;
            log(0, "Depth clamp was flagged as enabled, but device is missing feature flag OGA_RENDER_PASS_DISABLE_DEPTH_CLAMP");
        }
        
        VkPipelineRasterizationStateCreateInfo *rasterization = New(get_temp(), VkPipelineRasterizationStateCreateInfo);
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
        
        
        VkPipelineMultisampleStateCreateInfo *multisample = New(get_temp(), VkPipelineMultisampleStateCreateInfo);
        *multisample = (VkPipelineMultisampleStateCreateInfo){0};
        multisample->sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisample->rasterizationSamples = samples;
        
        VkPipelineDepthStencilStateCreateInfo *depth_stencil = New(get_temp(), VkPipelineDepthStencilStateCreateInfo);
        *depth_stencil = (VkPipelineDepthStencilStateCreateInfo){0};
        depth_stencil->sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        
        VkPipelineColorBlendAttachmentState *blend_attachment = New(get_temp(), VkPipelineColorBlendAttachmentState);
        *blend_attachment = (VkPipelineColorBlendAttachmentState){0};
        blend_attachment->blendEnable = false;
        blend_attachment->colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        
        VkPipelineColorBlendStateCreateInfo *blend = New(get_temp(), VkPipelineColorBlendStateCreateInfo);
        *blend = (VkPipelineColorBlendStateCreateInfo){0};
        blend->sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        blend->attachmentCount = 1;
        blend->pAttachments = blend_attachment;
        
        VkDynamicState dynamic_states[] = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
        };
        VkPipelineDynamicStateCreateInfo *dynamic = New(get_temp(), VkPipelineDynamicStateCreateInfo);
        *dynamic = (VkPipelineDynamicStateCreateInfo){0};
        dynamic->sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamic->dynamicStateCount = sizeof(dynamic_states)/sizeof(VkDynamicState);
        dynamic->pDynamicStates = dynamic_states;
        
        VkPipelineLayout layout;
        VkPipelineLayoutCreateInfo *layout_info = New(get_temp(), VkPipelineLayoutCreateInfo);
        *layout_info = (VkPipelineLayoutCreateInfo){0};
        layout_info->sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        
        VkAllocationCallbacks vk_allocs = _vk_allocator(&context->state_allocator);
        _vk_assert2(vkCreatePipelineLayout((VkDevice)context->id, layout_info, &vk_allocs, &layout));
        
        VkPipeline base_pipeline = 0;
        if (desc.base) {
            _Vk_Pipeline_State *state = (_Vk_Pipeline_State*)desc.base->id;
            base_pipeline = state->pipeline;
        }
        
        s32 base_index = (s32)desc.base_index;
    
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
    
    VkPipeline *vk_pipelines = NewBuffer(get_temp(), VkPipeline, render_pass_count);
    assert(vk_pipelines);
    VkAllocationCallbacks vk_allocs = _vk_allocator(&context->state_allocator);
    _vk_assert2(vkCreateGraphicsPipelines((VkDevice)context->id, 0, (u32)render_pass_count, infos, &vk_allocs, vk_pipelines));
    
    // These need to be allocated one by one because render passes needs to be able to be freed one by one
    for (u64 i = 0; i < render_pass_count; i += 1) {
        render_passes[i] = (Oga_Render_Pass*)allocate(context->state_allocator, sizeof(Oga_Render_Pass)+sizeof(_Vk_Pipeline_State));
        render_passes[i]->context = context;
        _Vk_Pipeline_State *state = (_Vk_Pipeline_State*)(render_passes[i]+1);
        render_passes[i]->id = state;
        
        state->pipeline = vk_pipelines[i];
        state->layout = infos[i].layout;
    }
    
    return OGA_OK;
}

Oga_Result oga_init_render_pass(Oga_Context *context, Oga_Render_Pass_Desc desc, Oga_Render_Pass **render_pass) {
    return oga_init_render_passes(context, &desc, render_pass, 1);
} 
void oga_uninit_render_pass(Oga_Render_Pass *render_pass) {
    _Vk_Pipeline_State *state = (_Vk_Pipeline_State*)render_pass->id;
    VkAllocationCallbacks vk_allocs = _vk_allocator(&render_pass->context->state_allocator);
    
    _vk_assert1(vkDeviceWaitIdle(render_pass->context->id));
    vkDestroyPipeline((VkDevice)render_pass->context->id, state->pipeline, &vk_allocs);
    vkDestroyPipelineLayout((VkDevice)render_pass->context->id, state->layout, &vk_allocs);
    
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

    VkSemaphoreCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkAllocationCallbacks vk_allocs = _vk_allocator(&context->state_allocator);
    _vk_assert2(vkCreateSemaphore((VkDevice)context->id, &create_info, &vk_allocs, (VkSemaphore*)&(*gpu_latch)->id));
    
    return OGA_OK;
}

void oga_uninit_gpu_latch(Oga_Gpu_Latch *gpu_latch) {
    VkAllocationCallbacks vk_allocs = _vk_allocator(&gpu_latch->context->state_allocator);
    _vk_assert1(vkDeviceWaitIdle(gpu_latch->context->id));
    vkDestroySemaphore((VkDevice)gpu_latch->context->id, (VkSemaphore)gpu_latch->id, &vk_allocs);

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

    VkFenceCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    create_info.flags = start_signaled ? VK_FENCE_CREATE_SIGNALED_BIT : 0;

    VkAllocationCallbacks vk_allocs = _vk_allocator(&context->state_allocator);
    _vk_assert2(vkCreateFence((VkDevice)context->id, &create_info, &vk_allocs, (VkFence*)&(*cpu_latch)->id));

    return OGA_OK;
}

void oga_uninit_cpu_latch(Oga_Cpu_Latch *cpu_latch) {
    VkAllocationCallbacks vk_allocs = _vk_allocator(&cpu_latch->context->state_allocator);
    _vk_assert1(vkDeviceWaitIdle(cpu_latch->context->id));
    vkDestroyFence((VkDevice)cpu_latch->context->id, (VkFence)cpu_latch->id, &vk_allocs);

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

Oga_Result oga_init_command_pool(Oga_Context *context, Oga_Command_Pool_Desc desc, Oga_Command_Pool **pool) {
    *pool = allocate(context->state_allocator, sizeof(Oga_Command_Pool) + sizeof(VkCommandPool));
    if (!*pool) {
        return OGA_ERROR_STATE_ALLOCATION_FAILED;
    }

    **pool = (Oga_Command_Pool){0};
    (*pool)->context = context;

    VkCommandPoolCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    create_info.flags = 0;

    if (desc.flags & OGA_COMMAND_POOL_SHORT_LIVED) {
        create_info.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    }

    create_info.queueFamilyIndex = (u32)desc.engine_family_index;

    VkAllocationCallbacks vk_allocs = _vk_allocator(&context->state_allocator);
    _vk_assert2(vkCreateCommandPool((VkDevice)context->id, &create_info, &vk_allocs, (VkCommandPool *)&(*pool)->id));

    return OGA_OK;
}

void oga_uninit_command_pool(Oga_Command_Pool *pool) {
    VkAllocationCallbacks vk_allocs = _vk_allocator(&pool->context->state_allocator);

    _vk_assert1(vkDeviceWaitIdle(pool->context->id));
    vkResetCommandPool(pool->context->id, pool->id, 0);
    _vk_assert1(vkDeviceWaitIdle(pool->context->id));
    vkDestroyCommandPool(pool->context->id, pool->id, &vk_allocs);

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

    VkCommandBuffer *vk_buffers = NewBuffer(get_temp(), VkCommandBuffer, list_count);
    _vk_assert2(vkAllocateCommandBuffers((VkDevice)pool->context->id, &allocate_info, vk_buffers));


    for (u64 i = 0; i < list_count; i += 1) {
        lists[i] = (Oga_Command_List){0};
        lists[i].id = vk_buffers[i];
        lists[i].pool = pool;
    }

    return OGA_OK;
}

void oga_release_command_lists(Oga_Command_List *lists, u64 list_count) {
    VkCommandBuffer *vk_buffers = NewBuffer(get_temp(), VkCommandBuffer, list_count);

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
    
    VkSemaphore *wait_semaphores = NewBuffer(get_temp(), VkSemaphore, desc.wait_gpu_latch_count);
    VkPipelineStageFlags *wait_stages = NewBuffer(get_temp(), VkPipelineStageFlags, desc.wait_gpu_latch_count);
    VkSemaphore *signal_semaphores = NewBuffer(get_temp(), VkSemaphore, desc.signal_gpu_latch_count);
    
    for (u64 i = 0; i < desc.wait_gpu_latch_count; i += 1) {
        wait_semaphores[i] = desc.wait_gpu_latches[i]->id;
        // note(charlie): it's a bit unfortunate to abstract this away from the programmer,
        // because it's a pretty neat opportunity for optimization. Maybe we add this to the
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
    
    _vk_assert2(vkQueueSubmit(desc.engine.id, 1, &info, desc.signal_cpu_latch->id));
    
    return OGA_OK;    
}
unit_local VkImageLayout _oga_to_vk_image_layout(Oga_Image_Optimization o) {
    switch(o) {
        case OGA_IMAGE_OPTIMIZATION_UNDEFINED:         return VK_IMAGE_LAYOUT_UNDEFINED;
        case OGA_IMAGE_OPTIMIZATION_GENERAL:           return VK_IMAGE_LAYOUT_GENERAL;
        case OGA_IMAGE_OPTIMIZATION_RENDER_ATTACHMENT: return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        case OGA_IMAGE_OPTIMIZATION_SHADER_READONLY:   return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        case OGA_IMAGE_OPTIMIZATION_TRANSFER_DST:      return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        case OGA_IMAGE_OPTIMIZATION_TRANSFER_SRC:      return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        case OGA_IMAGE_OPTIMIZATION_PRESENT:           return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        default: return 0;
    }
    return 0;
}
unit_local void _vk_decide_stage_and_access_mask(VkImageLayout layout, VkPipelineStageFlags *stage, VkAccessFlags *access)  {
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
        } else {
            assertmsgs(false, tprint("Unhandled image layout '%u' for transitioning (internal error)\n", layout));
        }
    }
void oga_cmd_transition_image_optimization(Oga_Command_List cmd, Oga_Image *image, Oga_Image_Optimization src_optimization, Oga_Image_Optimization dst_optimization) {
    VkPipelineStageFlags src_stage, dst_stage;
    VkAccessFlags src_access, dst_access;
    
    _vk_decide_stage_and_access_mask(_oga_to_vk_image_layout(src_optimization), &src_stage, &src_access);
    _vk_decide_stage_and_access_mask(_oga_to_vk_image_layout(dst_optimization), &dst_stage, &dst_access);
    
    _Vk_Image_State *state = (_Vk_Image_State*)image->id;
    
    VkImageMemoryBarrier barrier = (VkImageMemoryBarrier){0};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = _oga_to_vk_image_layout(src_optimization);
    barrier.newLayout = _oga_to_vk_image_layout(dst_optimization);
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = state->image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;
    barrier.pNext = 0;
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    

    vkCmdPipelineBarrier(cmd.id, src_stage, dst_stage, 0, 0, 0, 0, 0, 1, &barrier);
}

void oga_cmd_begin_render_pass(Oga_Command_List cmd, Oga_Begin_Render_Pass_Desc desc) {

    VkRenderingAttachmentInfoKHR vk_attachments[128] = {0};

    for (u64 i = 0; i < desc.attachment_count; i += 1) {
        
        Oga_Render_Attachment_Desc attach_desc = desc.attachments[i];
        
        _Vk_Image_State *state = (_Vk_Image_State*)attach_desc.image->id;
    
        vk_attachments[i].sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
        vk_attachments[i].imageView = state->view;
        vk_attachments[i].imageLayout = _oga_to_vk_image_layout(attach_desc.image_optimization);
        
        if (attach_desc.resolve_mode & OGA_MSAA_RESOLVE_MODE_ZERO)
            vk_attachments[i].resolveMode |= VK_RESOLVE_MODE_SAMPLE_ZERO_BIT_KHR;
        if (attach_desc.resolve_mode & OGA_MSAA_RESOLVE_MODE_AVERAGE)
            vk_attachments[i].resolveMode |= VK_RESOLVE_MODE_AVERAGE_BIT_KHR;
        if (attach_desc.resolve_mode & OGA_MSAA_RESOLVE_MODE_MIN)
            vk_attachments[i].resolveMode |= VK_RESOLVE_MODE_MIN_BIT_KHR;
        if (attach_desc.resolve_mode & OGA_MSAA_RESOLVE_MODE_MAX)
            vk_attachments[i].resolveMode |= VK_RESOLVE_MODE_MAX_BIT_KHR;
            
        if (attach_desc.resolve_image) {
            state = (_Vk_Image_State*)attach_desc.resolve_image->id;
    
            vk_attachments[i].resolveImageView = state->view;
            vk_attachments[i].resolveImageLayout = _oga_to_vk_image_layout(attach_desc.resolve_image_optimization);
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
    
    _Vk_Pipeline_State *state = (_Vk_Pipeline_State*)desc.render_pass->id;
    
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
void oga_cmd_end_render_pass(Oga_Command_List cmd) {
    _Vk_Context_Internal *internal = (_Vk_Context_Internal*)cmd.pool->context->internal;
    internal->vkCmdEndRenderingKHR(cmd.id);
}

void oga_cmd_draw(Oga_Command_List cmd, u64 vertex_count, u64 vertex_start, u64 instance_count, u64 instance_start) {
    vkCmdDraw(cmd.id, (u32)vertex_count, (u32)instance_count, (u32)vertex_start, (u32)instance_start);
}









#undef uint8_t
#undef int8_t
#undef uint16_t
#undef int16_t
#undef uint32_t
#undef int32_t
#undef uint64_t
#undef int64_t
