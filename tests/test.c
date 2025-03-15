
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



void test_base(void);
void test_sys1(void);
void test_sys2(void);
void test_memory(void);
void test_print(void);
void test_math(void);

int main(void) {
    sys_write_string(sys_get_stdout(), STR("Hello, ostd!\n"));

    test_base();
    test_sys1();
    test_memory();
    test_print();
    test_sys2();
    test_math();

    

}

void test_base(void) {
    assert(sizeof(u8) == 1 && (u8)-1 == (u8)0xffu);
    assert(sizeof(s8) == 1 && (s8)-1 == (s8)-0x01);
    assert(sizeof(u16) == 2 && (u16)-1 == (u16)0xffffu);
    assert(sizeof(s16) == 2 && (s16)-1 == (s16)-0x0001);
    assert(sizeof(u32) == 4 && (u32)-1 == (u32)0xffffffffu);
    assert(sizeof(s32) == 4 && (s32)-1 == (s32)-0x00000001);
    assert(sizeof(u64) == 8 && (u64)-1 == (u64)0xffffffffffffffffu);
    assert(sizeof(s64) == 8 && (s64)-1 == (s64)-0x0000000000000001);

    assert(sizeof(float32) == 4);
    assert(sizeof(float64) == 8);
#if HAS_FLOAT128
    assert(sizeof(float128) == 16);
#endif
}
void test_sys1(void) {
    assert(MAX_SURFACES > 0);

    System_Info info = sys_get_info();
    {
        void *mem = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, 4, false);
        assert(mem);

        memset(mem, (int)0xDEADBEEF, (sys_uint)info.page_size*4);

        sys_unmap_pages(mem);
    }
    // Address hints isnt supported with emscripten mmap
#if !(OS_FLAGS & OS_FLAG_EMSCRIPTEN)
    {
        // todo(charlie) portable safe virtual base address
        // win64, android arm64  0x0000007cccc00000ULL
        void* addr = (void*)((0x0000007cccc00000ULL + info.granularity - 1) & ~(info.granularity - 1));

        void *mem = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr, 4, true);
        assert(mem);
        assert(mem == addr);

        memset(mem, (int)0xDEADBEEF, (sys_uint)info.page_size*4);

        sys_unmap_pages(mem);
    }
    {
        u64 page_count = info.granularity / info.page_size;

        // todo(charlie) portable safe virtual base address
        void* addr0 = (void*)((0x40000000 + info.granularity - 1) & ~(info.granularity - 1));
        void *addr1 = (u8*)addr0 + page_count*info.page_size;
        void *addr2 = (u8*)addr1 + page_count*info.page_size;
        void *end = (u8*)addr2 + page_count*info.page_size;

        void *mem0 = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr0, page_count, true);
        void *mem1 = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr1, page_count, true);
        void *mem2 = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr2, page_count, true);

        assert(mem0);
        assert(mem1);
        assert(mem2);

        assert(mem0 == addr0);
        assert(mem1 == addr1);
        assert(mem2 == addr2);

        Mapped_Memory_Info pointers[3];
        u64 pointer_count = sys_query_mapped_regions(addr0, end, pointers, 3);

        assert(pointer_count == 3);

        assert(pointers[0].base == addr0);
        assert(pointers[1].base == addr1);
        assert(pointers[2].base == addr2);

        assert(pointers[0].page_count == page_count);
        assert(pointers[1].page_count == page_count);
        assert(pointers[2].page_count == page_count);
    }
#endif // !(OS_FLAGS & OS_FLAG_EMSCRIPTEN)

    {
        File_Handle hread, hwrite;

        bool ok = sys_make_pipe(&hread, &hwrite);
        assert(ok);

        string a = STR("Hey");

        s64 written = sys_write_string(hwrite, a);
        assert(written == (s64)a.count);

        u8 buf[128];
        string b = (string) { (u64)sys_read(hread, buf, 128), buf };

        assert(b.count == a.count);
        assert(strings_match(a, b));

        sys_close(hread);
        sys_close(hwrite);

        written = sys_write_string(hwrite, a);
        assert(written == 0);

        s64 read = sys_read(hread, buf, 128);
        assert(read == 0);
    }

    // todo(charlie) test rerouting stdout & stderr to a file
}
void test_sys2(void) {
    {
        Physical_Monitor monitors[128];
        u64 num_monitors = sys_query_monitors(0, 0);
        assert(num_monitors != 0);
        sys_query_monitors(monitors, num_monitors);

        for (u64 i = 0; i < num_monitors; i += 1) {
            Physical_Monitor m = monitors[i];
            string name = (string) {m.name_count, m.name};
            print(("Monitor %i:\n\t%s\n\thz: %i\n\t%ix%i\n\tscale: %f\n\tX: %i, Y: %i\n"),
                (i), name, m.refresh_rate, m.resolution_x, m.resolution_y, m.scale, m.pos_x, m.pos_y);
        }
    }
}

void test_memory(void) {
    System_Info info = sys_get_info();

    {
#if OS_FLAGS & OS_FLAG_EMSCRIPTEN
        Arena arena = make_arena(1024*100, 1024*100);
        assert(arena.allocated_size == ((1024*100 + info.page_size-1) & ~(info.page_size-1)));
        assert(arena.reserved_size  == ((1024*100 + info.page_size-1) & ~(info.page_size-1)));
#else
        Arena arena = make_arena(1024*100, 1024*10);
        assert(arena.allocated_size == ((1024*10 + info.page_size-1) & ~(info.page_size-1)));
        assert(arena.reserved_size  == ((1024*100 + info.page_size-1) & ~(info.page_size-1)));
#endif


        void *mem0 = arena_push(&arena, 1024*10);
        assert(mem0);
        memset(mem0, 0, 1024*10);

        void *mem1 = arena_push(&arena, 1024);
        assert(mem1);
        memset(mem1, 0, 1024);

        free_arena(arena);
    }

    {
        reset_temporary_storage();

        void *mem0 = tallocate(69);
        memset(mem0, 0, 69);

        reset_temporary_storage();

        void *mem1 = tallocate(69);
        assertmsgs(mem0 == mem1, tprint("%u, %u", mem0, mem1));
        memset(mem1, 0, 69);
    }
}

void test_print(void) {
    char buffer[256];

    string s;
    s.data = (u8*)buffer;
    s.count = 0;

    s.count = format_unsigned_int(12345, 10, s.data, sizeof(buffer));
    assert(strings_match(s, STR("12345")));

    s.count = format_signed_int(-6789, 10, s.data, sizeof(buffer));
    assert(strings_match(s, STR("-6789")));

    s.count = format_signed_int(6789, 10, s.data, sizeof(buffer));
    assert(strings_match(s, STR("6789")));

    s.count = format_float(123.456, 2, s.data, sizeof(buffer));
    assert(strings_match(s, STR("123.45")));

    s.count = format_float(-123.456, 2, s.data, sizeof(buffer));
    assert(strings_match(s, STR("-123.45")));

    s.count = format_unsigned_int(123456789, 10, buffer, 5);
    assert(strings_match(s, STR("12345"))); // Truncated to buffer size

    string result = sprints(get_temp(), STR("Hello, %s!"), STR("World"));
    assert(result.count == 13);
    assert(strings_match(result, STR("Hello, World!")));


    s16 val1 = 42;
    s32 val2 = -812736812;
    result = tprint(("Value1: %i, Value2: %i"), val1, val2);
    assert(strings_match(result, STR("Value1: 42, Value2: -812736812")));

    float32 flt = 3.14159f;
    print(("Testing print: %f\n"), flt);

    s = STR("TEST");
    float32 a = -123.456f;
    s16 b = -255;
    bool c = false;
    result = tprint(("%s, %f, %i, %b %a"), s, a, b, c, s);

    assert(strings_match(result, STR("TEST, -123.45600, -255, false <Unknown format specifier '%a'>")));

    print(("Print tests passed\n"));

    arena_allocator((Arena*)0);
}

// trig math is broken
void test_math(void) {

    double epsilon = 0.01;

    // Test sin function using known angles.
    struct { double angle; double expected; const char* msg; } sin_tests[] = {
        { 0.0, 0.0, "sin(0) failed" },
        { PI/6, 0.5, "sin(PI/6) failed" },
        { PI/4, 0.7071067811865476, "sin(PI/4) failed" },
        { PI/3, 0.8660254037844386, "sin(PI/3) failed" },
        { PI/2, 1.0, "sin(PI/2) failed" },
        { PI, 0.0, "sin(PI) failed" },
        { 3*PI/2, -1.0, "sin(3PI/2) failed" },
        { TAU, 0.0, "sin(TAU) failed" }
    };
    for (size_t i = 0; i < sizeof(sin_tests)/sizeof(sin_tests[0]); i++) {
        double actual = sin(sin_tests[i].angle);
        assertmsgs(abs(actual - sin_tests[i].expected) <= epsilon, tprint("Expected %f, got %f, %i", sin_tests[i].expected, actual, i));
    }

    // Test cos function using known angles.
    struct { double angle; double expected; const char* msg; } cos_tests[] = {
        { 0.0, 1.0, "cos(0) failed" },
        { PI/6, 0.8660254037844386, "cos(PI/6) failed" },
        { PI/4, 0.7071067811865476, "cos(PI/4) failed" },
        { PI/3, 0.5, "cos(PI/3) failed" },
        { PI/2, 0.0, "cos(PI/2) failed" },
        { PI, -1.0, "cos(PI) failed" },
        { 3*PI/2, 0.0, "cos(3PI/2) failed" },
        { TAU, 1.0, "cos(TAU) failed" }
    };
    for (size_t i = 0; i < sizeof(cos_tests)/sizeof(cos_tests[0]); i++) {
        double actual = cos(cos_tests[i].angle);
        assertmsg(abs(actual - cos_tests[i].expected) <= epsilon, cos_tests[i].msg);
    }

    // Test tan function by comparing against sin/cos (avoiding points where cos(x) is near zero).
    struct { double angle; double expected; const char* msg; } tan_tests[] = {
        { 0.0, 0.0, "tan(0) failed" },
        { PI/6, 0.5773502691896257, "tan(PI/6) failed" },
        { PI/4, 1.0, "tan(PI/4) failed" },
        { PI/3, 1.7320508075688772, "tan(PI/3) failed" }
    };
    for (size_t i = 0; i < sizeof(tan_tests)/sizeof(tan_tests[0]); i++) {
        double actual = tan(tan_tests[i].angle);
        assertmsgs(abs(actual - tan_tests[i].expected) <= epsilon, tprint("Expected %f, got %f, %i", tan_tests[i].expected, actual, i));
    }

    // Test asin function using known values.
    // The expected values here are the angles whose sine is the given value.
    struct { double value; double expected; const char* msg; } asin_tests[] = {
        { 0.0, 0.0, "asin(0) failed" },
        { 0.5, PI/6, "asin(0.5) failed" },
        { 0.70710678119, PI/4, "asin(0.7071) failed" },
        { 1.0, PI/2, "asin(1) failed" },
        { -0.5, -PI/6, "asin(-0.5) failed" },
        { -0.70710678119, -PI/4, "asin(-0.7071) failed" },
        { -1.0, -PI/2, "asin(-1) failed" }
    };
    for (size_t i = 0; i < sizeof(asin_tests)/sizeof(asin_tests[0]); i++) {
        double actual = asin(asin_tests[i].value);
        assertmsgs(abs(actual - asin_tests[i].expected) <= epsilon, tprint("%f Expected %f, got %f, %i", asin_tests[i].value, asin_tests[i].expected, actual, i));
    }

    // Test acos function using known values.
    struct { double value; double expected; const char* msg; } acos_tests[] = {
        { 1.0, 0.0, "acos(1) failed" },
        { 0.8660254037844386, PI/6, "acos(0.8660) failed" },
        { 0.7071067811865476, PI/4, "acos(0.7071) failed" },
        { 0.5, PI/3, "acos(0.5) failed" },
        { 0.0, PI/2, "acos(0) failed" },
        { -0.5, 2*PI/3, "acos(-0.5) failed" },
        { -0.7071067811865476, 3*PI/4, "acos(-0.7071) failed" },
        { -0.8660254037844386, 5*PI/6, "acos(-0.8660) failed" },
        { -1.0, PI, "acos(-1) failed" }
    };
    for (size_t i = 0; i < sizeof(acos_tests)/sizeof(acos_tests[0]); i++) {
        double actual = acos(acos_tests[i].value);
        assertmsg(abs(actual - acos_tests[i].expected) <= epsilon, acos_tests[i].msg);
    }

    // Test atan function using known values.
    struct { double value; double expected; const char* msg; } atan_tests[] = {
        { 0.0, 0.0, "atan(0) failed" },
        { 1.0, PI/4, "atan(1) failed" },
        { -1.0, -PI/4, "atan(-1) failed" },
        { 0.5773502691896257, PI/6, "atan(0.57735) failed" },
        { -0.5773502691896257, -PI/6, "atan(-0.57735) failed" }
    };
    for (size_t i = 0; i < sizeof(atan_tests)/sizeof(atan_tests[0]); i++) {
        double actual = atan(atan_tests[i].value);
        assertmsgs(abs(actual - atan_tests[i].expected) <= epsilon,
                   tprint("atan function failed for input %f. Expected %f, got %f", 
                          atan_tests[i].value, atan_tests[i].expected, actual));
    }

    // Test atan2 function using known values for various quadrants.
    struct { double y; double x; double expected; const char* msg; } atan2_tests[] = {
        { 0.0, 1.0, 0.0, "atan2(0,1) failed" },
        { 1.0, 0.0, PI/2, "atan2(1,0) failed" },
        { 0.0, -1.0, PI, "atan2(0,-1) failed" },
        { -1.0, 0.0, -PI/2, "atan2(-1,0) failed" },
        { 1.0, 1.0, PI/4, "atan2(1,1) failed" },
        { -1.0, -1.0, -3*PI/4, "atan2(-1,-1) failed" }
    };
    for (size_t i = 0; i < sizeof(atan2_tests)/sizeof(atan2_tests[0]); i++) {
        double actual = atan2(atan2_tests[i].y, atan2_tests[i].x);
        assertmsg(abs(actual - atan2_tests[i].expected) <= epsilon, atan2_tests[i].msg);
    }
}
