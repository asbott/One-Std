
#include <vulkan/vulkan.h>

// For syntax highligthing
#if 0
// noconcat
#include "../vendors/vulkan/vulkan.h"
#include "ostd.h"
#endif



// We manually include the vulkan-specific headers, otherwise vulkan.h will include windows.h
#if OS_FLAGS & OS_FLAG_WINDOWS
#include <vulkan/vulkan_win32.h>
#elif OS_FLAGS & OS_FLAG_LINUX
#include <vulkan/vulkan_xlib.h>
#elif OS_FLAGS & OS_FLAG_MACOS
#include <vulkan/vulkan_macos.h>
#elif OS_FLAGS & OS_FLAG_IOS
#include <vulkan/vulkan_ios.h>
#elif OS_FLAGS & OS_FLAG_ANDROID
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

unit_local inline VkFormat _oga_to_vk_format(Oga_Format_Kind k) {
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

        default:
        return (VkFormat)0;
    }
    return (VkFormat)0;
}
unit_local inline Oga_Format_Kind _vk_to_oga_format(VkFormat k) {
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

        default:
        return (Oga_Format_Kind)0;
    }
    return (Oga_Format_Kind)0;
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

#define _vk_assert(expr) do { VkResult _res = expr; string _res_str = _str_vk_result(_res); assertmsgs(_res == VK_SUCCESS, tprint("Vulkan call %s failed: %s. If you see this, you're either doing something very wrong, or there is an internal error in Oga.", STR(#expr), _res_str)); } while(0)


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

unit_local inline VkInstance _vk_instance(void) {
    local_persist VkInstance instance = 0;

    if (!instance) {

        VkApplicationInfo app_info = (VkApplicationInfo){0};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = "Ostd App";
        app_info.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
        app_info.pEngineName = "Oga";
        app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.apiVersion = VK_API_VERSION_1_1;

        VkInstanceCreateInfo create_info = (VkInstanceCreateInfo){0};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &app_info;

#if OS_FLAGS & OS_FLAG_WINDOWS
        const char *required_extensions[] = {

#ifdef DEBUG
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif // _DEBUG
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_WIN32_SURFACE_EXTENSION_NAME
        };
#elif OS_FLAGS & OS_FLAG_LINUX
    // Depending on your display server, pick one:
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_XLIB_SURFACE_EXTENSION_NAME
    };
#elif OS_FLAGS & OS_FLAG_MACOS
    // MoltenVK-specific extension for macOS
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        "VK_MVK_macos_surface",
        "VK_KHR_portability_enumeration"
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
        "VK_KHR_portability_enumeration"
    };
    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#elif OS_FLAGS & OS_FLAG_ANDROID
    static const char* required_extensions[] = {
#ifdef DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
    };

#else
    #error VK instance extension query not set up for this OS
#endif
        u64 num_required_extensions = sizeof(required_extensions) / sizeof(char*);

        log(0, "Looking for extensions:");
        for (u64 i = 0; i < num_required_extensions; i += 1) {
            log(0, "\t%s", STR(required_extensions[i]));
        }

        u32 num_available_extensions;
        _vk_assert(vkEnumerateInstanceExtensionProperties(0, &num_available_extensions, 0));
        VkExtensionProperties *available_extensions = NewBuffer(get_temp(), VkExtensionProperties, num_available_extensions);
        memset(available_extensions, 0, num_available_extensions*sizeof(VkExtensionProperties));
        _vk_assert(vkEnumerateInstanceExtensionProperties(0, &num_available_extensions, available_extensions));
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
        _vk_assert(vkEnumerateInstanceLayerProperties(&num_available_layers, 0));

        VkLayerProperties *available_layers = NewBuffer(get_temp(), VkLayerProperties, num_available_layers);
        _vk_assert(vkEnumerateInstanceLayerProperties(&num_available_layers, available_layers));

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
                log(0, "Missing wanted vulkan debug layer '%s'", STR(wanted));
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

        _vk_assert(vkCreateInstance(&create_info, 0, &instance));

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

        void (*untyped)(void) = vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        PFN_vkCreateDebugUtilsMessengerEXT _vkCreateDebugUtilsMessengerEXT  = (PFN_vkCreateDebugUtilsMessengerEXT)*(PFN_vkCreateDebugUtilsMessengerEXT*)(void**)&untyped;

        if (_vkCreateDebugUtilsMessengerEXT(instance, &debug_create_info, 0, &_vk_messenger) != VK_SUCCESS) {
            log(0, "Failed creating vulkan debug messenger");
        }
#endif // DEBUG
    }


    return instance;
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
    _vk_assert(vkEnumeratePhysicalDevices(_vk_instance(), &device_count,  0));

    if (buffer) {
        memset(buffer, 0, buffer_count*sizeof(Oga_Device));
        VkPhysicalDevice vk_devices[256];
        _vk_assert(vkEnumeratePhysicalDevices(_vk_instance(), &device_count,  vk_devices));

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

            u32 logical_engine_family_count;
            vkGetPhysicalDeviceQueueFamilyProperties(vk_device, &logical_engine_family_count, 0);
            VkQueueFamilyProperties *logical_engine_family_props = NewBuffer(get_temp(), VkQueueFamilyProperties, logical_engine_family_count);
            vkGetPhysicalDeviceQueueFamilyProperties(vk_device, &logical_engine_family_count, logical_engine_family_props);


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


            ///
            // Logical Engine flags

            // note(charlie) annoyingly, we need an existing surface to look for
            // surface support in logical_engines. So, we just make a temporary invisible
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
            _vk_assert(vkCreateSurfaceKHR(temp_sys_surface, &temp_vk_surface));

            device->logical_engine_family_count = logical_engine_family_count;
            for (u32 j = 0; j < logical_engine_family_count; j += 1) {
                Oga_Logical_Engine_Family_Info *info = &device->logical_engine_family_infos[j];
                VkQueueFamilyProperties family_props = logical_engine_family_props[j];

                VkBool32 val;
                _vk_assert(vkGetPhysicalDeviceSurfaceSupportKHR(vk_device, j, temp_vk_surface, &val));
                if (val) info->flags |= OGA_LOGICAL_ENGINE_PRESENT;

                info->logical_engine_capacity = family_props.queueCount;

                if (family_props.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                    info->flags |= OGA_LOGICAL_ENGINE_GRAPHICS;
                if (family_props.queueFlags & VK_QUEUE_COMPUTE_BIT)
                    info->flags |= OGA_LOGICAL_ENGINE_COMPUTE;
                if (family_props.queueFlags & VK_QUEUE_TRANSFER_BIT)
                    info->flags |= OGA_LOGICAL_ENGINE_TRANSFER;
            }

            vkDestroySurfaceKHR(_vk_instance(), temp_vk_surface, 0);

#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
            surface_close(temp_sys_surface);
#endif

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


            if (props.limits.timestampComputeAndGraphics) {
                device->features |= (OGA_DEVICE_FEATURE_GRAPHICS_TIMESTAMP |
                                     OGA_DEVICE_FEATURE_COMPUTE_TIMESTAMP);
            }

            device->limits.max_shader_items_sets_per_stage = props.limits.maxPerStageResources;
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
            device->limits.max_color_attachments = props.limits.maxColorAttachments;
            device->limits.min_memory_map_alignment = props.limits.minMemoryMapAlignment;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.framebufferColorSampleCounts & f) device->limits.supported_sample_counts_framebuffer |= f;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.sampledImageColorSampleCounts & f) device->limits.supported_sample_counts_fast_image_float |= f;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.storageImageSampleCounts & f) device->limits.supported_sample_counts_large_image_float |= f;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.sampledImageIntegerSampleCounts & f) device->limits.supported_sample_counts_fast_image_int |= f;
            for (u64 f = 1; f < VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM; f = f << 1)
                if (props.limits.storageImageSampleCounts & f) device->limits.supported_sample_counts_large_image_int |= f;

            device->id = vk_device;
        }
    }

    return device_count;
}

Oga_Device *oga_get_devices(Allocator a, u64 *count) {
    *count = oga_query_devices(0, 0);

    Oga_Device *devices = NewBuffer(a, Oga_Device, *count);
    oga_query_devices(devices, *count);

    return devices;
}


Oga_Result oga_init_context(Oga_Device target_device, Oga_Context_Desc desc, Oga_Context *context) {

    const char *required_extensions[] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    if ((desc.enabled_features & target_device.features) != desc.enabled_features) {
        return OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES;
    }

    VkPhysicalDeviceFeatures enabled_features = (VkPhysicalDeviceFeatures){0};
    // if (desc.enabled_features & OGA_DEVICE_FEATURE_XXXX) enabled_features.xxxx = true;

    VkDeviceQueueCreateInfo logical_engine_infos[OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES] = {0};

    u64 logical_engines_desc_count = 0;
    for (u64 family_index = 0; family_index < OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES; family_index += 1) {
        Oga_Logical_Engines_Create_Desc logical_engines_desc = desc.logical_engine_create_descs[family_index];
        if (logical_engines_desc.count > 0) {

            if (family_index >= target_device.logical_engine_family_count) {
                return OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE;
            }

            Oga_Logical_Engine_Family_Info family = target_device.logical_engine_family_infos[family_index];
            if (logical_engines_desc.count > family.logical_engine_capacity) {
                return OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW;
            }

            VkDeviceQueueCreateInfo *info = &logical_engine_infos[logical_engines_desc_count];
            info->sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            info->queueFamilyIndex = (u32)family_index;
            info->queueCount = (u32)logical_engines_desc.count;
            info->pQueuePriorities = logical_engines_desc.priorities;

            logical_engines_desc_count += 1;
        }
    }


    VkDeviceCreateInfo info = (VkDeviceCreateInfo) {0};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    info.enabledExtensionCount = (u32)(sizeof(required_extensions)/sizeof(char*));
    info.ppEnabledExtensionNames = required_extensions;
    info.pEnabledFeatures = &enabled_features;
    info.queueCreateInfoCount = (u32)logical_engines_desc_count;
    info.pQueueCreateInfos = logical_engine_infos;

    *context = (Oga_Context){0};
    _vk_assert(vkCreateDevice(target_device.id, &info, 0, (VkDevice*)&context->id));
    context->device = target_device;

    for (u64 family_index = 0; family_index < OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES; family_index += 1) {
        Oga_Logical_Engines_Create_Desc logical_engines_desc = desc.logical_engine_create_descs[family_index];
        Oga_Logical_Engine_Group *group = &context->logical_engines_by_family[family_index];
        for (u64 logical_engine_index = 0; logical_engine_index < logical_engines_desc.count; logical_engine_index += 1) {
            Oga_Logical_Engine *logical_engine = &group->logical_engines[logical_engine_index];
            vkGetDeviceQueue(
                context->id,
                (u32)family_index,
                (u32)logical_engine_index,
                (VkQueue*)&logical_engine->id
            );
            logical_engine->index = (u32)logical_engine_index;
        }
    }

    return OGA_OK;
}
void oga_uninit_context(Oga_Context *context) {
    vkDeviceWaitIdle(context->id);

    vkDestroyDevice(context->id, 0);
    *context = (Oga_Context){0};
}

