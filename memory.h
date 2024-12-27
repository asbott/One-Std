typedef struct Arena {
    void *start;
    void *position;
    u64 reserved_size;
    u64 allocated_size;
} Arena;

Arena make_arena(u64 reserved_size, u64 initial_allocated_size);
void *arena_push(Arena *arena, u64 size);
void arena_pop(Arena *arena, u64 size);
void free_arena(Arena arena);

#ifdef OSTD_IMPL

Arena make_arena(u64 reserved_size, u64 initial_allocated_size) {
    System_Info info = sys_get_info();
    
    // Align to page size
    reserved_size = (reserved_size + info.page_size - 1) & ~(info.page_size - 1);
    initial_allocated_size = (initial_allocated_size + info.page_size - 1) & ~(info.page_size - 1);
    
    assert(initial_allocated_size <= reserved_size);
    
    Arena arena;
    
    arena.start = sys_map_pages(SYS_MEMORY_RESERVE, 0, reserved_size/info.page_size);
    assert(arena.start);
    
    arena.position = arena.start;
    
    void *allocate_result = sys_map_pages(SYS_MEMORY_ALLOCATE, arena.start, initial_allocated_size/info.page_size);
    assert(allocate_result == arena.start);
    
    arena.reserved_size = reserved_size;
    arena.allocated_size = initial_allocated_size;
    
    return arena;
}
void free_arena(Arena arena) {
    void *start = arena.start;
    void *end = (u8*)arena.start + arena.reserved_size;
    
    u64 pointer_count = sys_query_mapped_pointers(start, end, 0, 0);
    
    // todo(charlie)  use a temp scratch memory here
    Mapped_Memory_Info pointers[4096];
    sys_query_mapped_pointers(start, end, pointers, pointer_count);
    
    u32 i;
    for (i = 0; i < pointer_count; i += 1) {
        sys_unmap_pages(pointers[i].base);
    }
}

void *arena_push(Arena *arena, u64 size) {

    System_Info info = sys_get_info();

    // Align to 8
    size = (size + 7) & ~(7);

    void *allocated_tail = (u8*)arena->start + arena->allocated_size;
    void *reserved_tail = (u8*)arena->start + arena->reserved_size;

    if ((u64)arena->position + size > (u64)reserved_tail) {
        return 0;
    }
    
    if ((u64)arena->position + size > (u64)allocated_tail) {
        
        u64 amount_to_allocate = ((u64)arena->position + size) - (u64)allocated_tail;
        
        amount_to_allocate = (amount_to_allocate + info.page_size-1) & ~(info.page_size-1);
        
        u64 pages_to_allocate = amount_to_allocate / info.page_size;
        
        void *allocate_result = sys_map_pages(SYS_MEMORY_ALLOCATE, allocated_tail, pages_to_allocate);
        assert(allocate_result == allocated_tail, "Failed allocating pages in arena");
        
        arena->allocated_size += amount_to_allocate;
    }

    void *p = arena->position;
    arena->position = (u8*)arena->position + size;
    
    return p;
}

void arena_pop(Arena *arena, u64 size) {
    arena->position = (u8*)arena->position - size;
    if ((u64)arena->position < (u64)arena->start)  arena->position = arena->start;
}

#endif // OSTD_IMPL