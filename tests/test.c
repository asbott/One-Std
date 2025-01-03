
//#include <windows.h>

#ifndef TEST_NO_IMPL
#define OSTD_IMPL
#endif // TEST_NO_IMPL
#include "../ostd.h"

void test_base(void);
void test_sys1(void);
void test_sys2(void);
void test_memory(void);
void test_print(void);

int main(void) {
    sys_write_string(sys_get_stdout(), STR("Hello, ostd!\n"));
    
    test_base();
    test_sys1();
    test_memory();
    test_print();
    test_sys2();
    
#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
    Surface_Desc desc = DEFAULT(Surface_Desc);
    Surface_Handle surface = sys_make_surface(desc);
    assertmsg(surface, STR("Failed making surface"));
#else
    Surface_Handle surface = sys_get_surface();
#endif
    bool running = true;
    
    while (running) {
        surface_poll_events(surface);
    }
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
    System_Info info = sys_get_info();
    {
        void *mem = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, 4);
        
        memset(mem, (int)0xDEADBEEF, info.page_size*4);
        
        sys_unmap_pages(mem);
    }
    {
        // todo(charlie) portable safe virtual base address
        void* addr = (void*)((0x0000007cccc00000ULL + info.granularity - 1) & ~(info.granularity - 1));
        
        void *mem = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr, 4);
        memset(mem, (int)0xDEADBEEF, info.page_size*4);
        
        sys_unmap_pages(mem);
    }
    {
        u64 page_count = info.granularity / info.page_size;
    
        // todo(charlie) portable safe virtual base address
        void* addr0 = (void*)((0x0000007cccc00000ULL + info.granularity - 1) & ~(info.granularity - 1));
        void *addr1 = (u8*)addr0 + page_count*info.page_size;
        void *addr2 = (u8*)addr1 + page_count*info.page_size;
        void *end = (u8*)addr2 + page_count*info.page_size;
        
        void *mem0 = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr0, 4);
        void *mem1 = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr1, 4);
        void *mem2 = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr2, 4);
        
        assert(mem0 == addr0);
        assert(mem1 == addr1);
        assert(mem2 == addr2);
        
        Mapped_Memory_Info pointers[3];
        u64 pointer_count = sys_query_mapped_regions(addr0, end, pointers, 3);
        
        assert(pointer_count == 3);
        
        assert(pointers[0].base == addr0);
        assert(pointers[1].base == addr1);
        assert(pointers[2].base == addr2);
        
        assert(pointers[0].page_count == 4);
        assert(pointers[1].page_count == 4);
        assert(pointers[2].page_count == 4);
    }
    
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
            i += 1;
            print(STR("Monitor %i:\n\t%s\n\thz: %i\n\t%ix%i\n\tscale: %f\n\tX: %i, Y: %i"),
                (i), name, m.refresh_rate, m.resolution_x, m.resolution_y, m.scale, m.pos_x, m.pos_y);
        }
    }
}

void test_memory(void) {
    System_Info info = sys_get_info();

    {
        Arena arena = make_arena(1024*100, 1024*10);
    
        assert(arena.allocated_size == ((1024*10 + info.page_size-1) & ~(info.page_size-1)));
        assert(arena.reserved_size  == ((1024*100 + info.page_size-1) & ~(info.page_size-1)));
        
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
        
        void *mem0 = talloc(69);
        memset(mem0, 0, 69);
        
        reset_temporary_storage();
        
        void *mem1 = talloc(69);
        assert(mem0 == mem1);
        memset(mem1, 0, 69);
        
        void *mem2 = talloc(69);
        assert((u64)mem2 > (u64)mem1 + 69);
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

    string result = sprint(get_temp(), STR("Hello, %s!"), STR("World"));
    assert(result.count == 13);
    assert(strings_match(result, STR("Hello, World!")));

    s16 val1 = 42;
    s32 val2 = -812736812;
    result = tprint(STR("Value1: %i, Value2: %i"), val1, val2);
    assert(strings_match(result, STR("Value1: 42, Value2: -812736812")));

    float32 flt = 3.14159f;
    print(STR("Testing print: %f\n"), flt);
    
    s = STR("TEST");
    float32 a = -123.456f;
    s16 b = -255;
    bool c = false;
    result = tprint(STR("%s, %f, %i, %b %a"), s, a, b, c, s);
    
    assert(strings_match(result, STR("TEST, -123.45600, -255, false <Unknown format specifier '%a'>")));
    
    print(STR("Print tests passed\n"));
}