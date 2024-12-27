
//#include <windows.h>

#define OSTD_IMPL
#include "../ostd.h"

void test_sys();
void test_memory();

int main(int argc, char **argv) {
    test_sys();
    test_memory();
    
    sys_write_string(sys_get_stdout(), STR("Hello, ostd!\n"));
}

void test_sys() {
    System_Info info = sys_get_info();
    {
        void *addr = (void*)((0x0000690000000000ULL + info.granularity-1) & ~(info.granularity-1));
        
        void *mem = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, addr, 4);
        
        assert(mem == addr);
        
        memset(mem, 0xDEADBEEF, info.page_size*4);
        
        sys_unmap_pages(mem);
    }
    {
        u64 page_count = info.granularity / info.page_size;
    
        void *addr0 = (void*)((0x0000690000000000ULL + info.granularity-1) & ~(info.granularity-1));
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
        u64 pointer_count = sys_query_mapped_pointers(addr0, end, pointers, 3);
        
        assert(pointer_count == 3);
        
        assert(pointers[0].base == addr0);
        assert(pointers[1].base == addr1);
        assert(pointers[2].base == addr2);
        
        assert(pointers[0].page_count == 4);
        assert(pointers[1].page_count == 4);
        assert(pointers[2].page_count == 4);
    }
}

void test_memory() {
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
}