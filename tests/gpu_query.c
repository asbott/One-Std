
#ifndef TEST_NO_IMPL
#define OSTD_IMPL

#define OGA_IMPL_VULKAN
#endif // TEST_NO_IMPL
#include "../src/ostd.h"
//#include "../ostd_single_header.h"

// Clang warns if there is a default case in switch covering full enum, but also warns if there
// is not default switch. ?!?!??!?!?!?!?!?!?
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-default"
// And it gives warnings about code not being compliant with pre-C99... Even though I've specified
// std=c99 ....
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
// MSC clang also complains every time I do pointer arithmetic... in C .....
#pragma clang diagnostic ignored "-Wpre-c23-compat"
#ifdef _MSC_VER
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif

int main(void) {
    Oga_Device devices[128];
    u64 device_count = oga_query_devices(devices, 128);

    assert(device_count > 0 && device_count < 128);

    print("%u devices:\n", device_count);
    for (u32 i = 0; i < device_count; i += 1) {
        Oga_Device *device = devices + i;

        print(("Device %u:\n"), i);
        print(("\t%s - %s %s - %s\n"), STRN(device->device_name_length, device->device_name_data), device->vendor_name, STRN(device->driver_version_length, device->driver_version_data), STRN(device->api_version_length, device->api_version_data));
        print("\tKind: ");
        switch (device->kind) {
            case OGA_DEVICE_DISCRETE: print("Discrete GPU\n"); break;
            case OGA_DEVICE_INTEGRATED: print("Integrated GPU\n"); break;
            case OGA_DEVICE_CPU: print("CPU\n"); break;
            case OGA_DEVICE_OTHER: print("Other\n"); break;
        }

        print(("\t%u Logical Engine families:\n"), device->engine_family_count);
        for (u32 j = 0; j < device->engine_family_count; j += 1) {
            Oga_Logical_Engine_Family_Info family = device->engine_family_infos[j];

            print(("\t\t"));

            if (family.flags & OGA_LOGICAL_ENGINE_GRAPHICS) print(("GRAPHICS "));
            if (family.flags & OGA_LOGICAL_ENGINE_COMPUTE) print(("COMPUTE "));
            if (family.flags & OGA_LOGICAL_ENGINE_TRANSFER) print(("TRANSFER "));
            if (family.flags & OGA_LOGICAL_ENGINE_PRESENT) print(("PRESENT "));

            print(("| %u engines\n"), family.engine_capacity);

        }
        u64 mem_gb = device->total_gpu_local_memory/(1024*1024);
        print(("\tLocal memory: %u MB\n"), mem_gb);
        print(("\t%u Heaps:\n"), device->memory_heap_count);
        for (u64 j = 0; j < device->memory_heap_count; j += 1) {
            print(("\t\t"));

            Oga_Memory_Heap heap = device->memory_heaps[j];
            if (heap.properties & OGA_MEMORY_PROPERTY_GPU_LOCAL)
                print(("GPU-LOCAL "));
            if (heap.properties & OGA_MEMORY_PROPERTY_GPU_TO_CPU_MAPPABLE)
                print(("CPU-MAPPABLE "));
            if (heap.properties & OGA_MEMORY_PROPERTY_GPU_TO_CPU_REFLECTED)
                print(("CPU-REFLECTED "));
            if (heap.properties & OGA_MEMORY_PROPERTY_GPU_TO_CPU_CACHED)
                print(("CPU-CACHED "));

            mem_gb = heap.size/(1024*1024);
            print(("| %u MB\n"), mem_gb);
            print("\t\tSupported usage flags: ");
            if (heap.supported_usage_flags & OGA_MEMORY_USAGE_IMAGE_1D)
                print("IMAGE_1D ");
            if (heap.supported_usage_flags & OGA_MEMORY_USAGE_IMAGE_2D)
                print("IMAGE_2D ");
            if (heap.supported_usage_flags & OGA_MEMORY_USAGE_IMAGE_3D)
                print("IMAGE_3D ");
            if (heap.supported_usage_flags & OGA_MEMORY_USAGE_IMAGE_1D)
                print("IMAGE_1D ");
            if (heap.supported_usage_flags & OGA_MEMORY_USAGE_IMAGE_2D)
                print("IMAGE_2D ");
            if (heap.supported_usage_flags & OGA_MEMORY_USAGE_IMAGE_3D)
                print("IMAGE_3D ");
            if (heap.supported_usage_flags & OGA_MEMORY_USAGE_VERTEX_LIST)
                print("VERTEX_LIST ");
            if (heap.supported_usage_flags & OGA_MEMORY_USAGE_INDEX_LIST)
                print("INDEX_LIST ");
            if (heap.supported_usage_flags & OGA_MEMORY_USAGE_FAST_READONLY_DATA_BLOCK)
                print("FAST_READONLY_DATABLOCK ");
            if (heap.supported_usage_flags & OGA_MEMORY_USAGE_LARGE_READWRITE_DATA_BLOCK)
                print("LARGE_READWRITE_DATABLOCK ");
            if (heap.supported_usage_flags & OGA_MEMORY_USAGE_COPY_DST)
                print("COPY_DST ");
            if (heap.supported_usage_flags & OGA_MEMORY_USAGE_COPY_SRC)
                print("COPY_SRC ");
            print("\n");
        }
        print("\t%u supported surface formats:\n", device->supported_surface_format_count);
        for (u64 j = 0; j < device->supported_surface_format_count; j += 1) {
            Oga_Format f = device->supported_surface_formats[j];
            string fstr = oga_format_str(f);
            print("\t\t%s\n", fstr);
        }

        print("\tFeatures:\n\t\t");
        for (u64 f = 0; f < 64; f += 1) {
            if (device->features & (1ULL << f)) {
                string feature_str = oga_device_feature_str(1ULL << f);
                print("%s | ", feature_str);
            }
        }
        print("\n");
    }
    print("\n");

    //////
    // Test device picking helper
    /////
    Oga_Pick_Device_Result pick0 = oga_pick_device(
        OGA_DEVICE_PICK_PREFER_DISCRETE,
        0,
        0
    );
    Oga_Pick_Device_Result pick1 = oga_pick_device(
        OGA_DEVICE_PICK_PREFER_INTEGRATED,
        0,
        0
    );
    Oga_Pick_Device_Result pick2 = oga_pick_device(
        OGA_DEVICE_PICK_PREFER_CPU,
        0,
        0
    );
    Oga_Pick_Device_Result pick3 = oga_pick_device(
        OGA_DEVICE_PICK_REQUIRE_CPU,
        0,
        0
    );
    Oga_Pick_Device_Result pick4 = oga_pick_device(
        OGA_DEVICE_PICK_REQUIRE_DISCRETE,
        0,
        0
    );
    Oga_Pick_Device_Result pick5 = oga_pick_device(
        0,
        OGA_DEVICE_FEATURE_PRESENT_MAILBOX,
        0
    );

    string s0 = (pick0.passed ? (STRN(pick0.device.device_name_length, pick0.device.device_name_data)) : STR("NONE"));
    print("PREFER_DISCRETE: %s\n", s0);
    string s1 = (pick1.passed ? (STRN(pick1.device.device_name_length, pick1.device.device_name_data)) : STR("NONE"));
    print("PREFER_INTEGRATED: %s\n", s1);
    string s2 = (pick2.passed ? (STRN(pick2.device.device_name_length, pick2.device.device_name_data)) : STR("NONE"));
    print("PREFER_CPU: %s\n", s2);
    string s3 = (pick3.passed ? (STRN(pick3.device.device_name_length, pick3.device.device_name_data)) : STR("NONE"));
    print("REQUIRE_CPU: %s\n", s3);
    string s4 = (pick4.passed ? (STRN(pick4.device.device_name_length, pick4.device.device_name_data)) : STR("NONE"));
    print("REQUIRE_DISCRETE: %s\n", s4);
    string s5 = (pick5.passed ? (STRN(pick5.device.device_name_length, pick5.device.device_name_data)) : STR("NONE"));
    print("REQUIRE FEATURE PRESENT_MAILBOX: %s\n", s5);

    print("\n");

    Oga_Device target_device = pick0.device;

    //////
    // Init context
    /////

    ///
    // Select queues
    // note(charlie) In a real-world scenario you would probably want to spread out queues across families.
    // You'd especially want to make sure, if possible, that compute is on another family, or at least
    // a separate queue index from graphics.
    u64 family_index_graphics = U64_MAX;
    u64 family_index_present = U64_MAX;
    u64 family_index_compute = U64_MAX;

    for (u32 family_index = 0; family_index < target_device.engine_family_count; family_index += 1) {
        Oga_Logical_Engine_Family_Info family = target_device.engine_family_infos[family_index];

        if ((family.flags & OGA_LOGICAL_ENGINE_GRAPHICS) && family_index_graphics == U64_MAX) {
            family_index_graphics = family_index;
        }
        if ((family.flags & OGA_LOGICAL_ENGINE_PRESENT) && family_index_present == U64_MAX) {
            family_index_present = family_index;
        }
        if ((family.flags & OGA_LOGICAL_ENGINE_COMPUTE) && family_index_compute == U64_MAX) {
            family_index_compute = family_index;
        }
    }

    if (family_index_graphics == U64_MAX) {
        print("Error: no graphics engines.\n");
        return 1;
    }
    if (family_index_present == U64_MAX) {
        print("Error: no present engines.\n");
        return 1;
    }
    if (family_index_compute == U64_MAX) {
        print("Error: no compute engines.\n");
        return 1;
    }

}

