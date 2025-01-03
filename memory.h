
/////
// Allocator
/////

typedef enum Allocator_Message {
    ALLOCATOR_ALLOCATE,
    ALLOCATOR_REALLOCATE,
    ALLOCATOR_FREE
} Allocator_Message;
typedef void*(*Allocator_Proc)(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n);

typedef struct Allocator {
    void *data;
    Allocator_Proc proc;
} Allocator;

inline void *alloc(Allocator a, u64 n);
inline void *realloc(Allocator a, void *p, u64 old_n, u64 n);
inline void free(Allocator a, void *p);

#define New(a, T) ((T*)alloc(a, sizeof(T)))

inline string string_alloc(Allocator a, u64 n);
inline void string_free(Allocator a, string s);

/////
// Arena
/////

typedef struct Arena {
    void *start;
    void *position;
    u64 reserved_size;
    u64 allocated_size;
} Arena;

Arena make_arena(u64 reserved_size, u64 initial_allocated_size);
void *arena_push(Arena *arena, u64 size);
void arena_pop(Arena *arena, u64 size);
void arena_reset(Arena *arena);
void free_arena(Arena arena);

void* arena_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n);
inline Allocator arena_allocator(Arena *a) { return (Allocator) { a, arena_allocator_proc }; }

/////
// Temporary storage
/////

// todo(charlie) temporary storage might get bloated with large temporary allocations,
// so we should provide a way to shrink temporary storage.

Allocator get_temp(void);
void reset_temporary_storage(void);
void *talloc(size_t n);




inline void *alloc(Allocator a, u64 n) {
    return a.proc(ALLOCATOR_ALLOCATE, a.data, 0, 0, n);
}
inline void *realloc(Allocator a, void *p, u64 old_n, u64 n) {
    return a.proc(ALLOCATOR_REALLOCATE, a.data, p, old_n, n);
}
inline void free(Allocator a, void *p) {
    a.proc(ALLOCATOR_FREE, a.data, p, 0, 0);
}

inline string string_alloc(Allocator a, u64 n) {
    return (string) {n, (u8*)alloc(a, n)};
}
inline void string_free(Allocator a, string s) {
    free(a, s.data);
}

#ifdef OSTD_IMPL

Arena _temp_arena;
Allocator _temp;
bool _temp_initted = false;

inline void _lazy_init_temporary_storage(void) {
    if (_temp_initted) return;
    
    _temp_arena = make_arena(sys_get_info().page_size*4, 1024);
    
    _temp = (Allocator) { &_temp_arena, arena_allocator_proc };
    
    _temp_initted = true;
}
Allocator get_temp(void) {
    _lazy_init_temporary_storage();
    return _temp;
}
void reset_temporary_storage(void) {
    _lazy_init_temporary_storage();
    arena_reset(&_temp_arena);
}
void *talloc(size_t n) {
    _lazy_init_temporary_storage();
    
    return alloc(_temp, n);
}

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
void arena_reset(Arena *arena) {
    arena->position = arena->start;
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
        assertmsg(allocate_result == allocated_tail, STR("Failed allocating pages in arena"));
        
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

void* arena_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n) {
    Arena *a = (Arena*)data;
    switch (msg) {
        case ALLOCATOR_ALLOCATE:
            return arena_push(a, n);
        case ALLOCATOR_REALLOCATE:
            void *p = arena_push(a, n);
            if (old && old_n) {
                memcpy(p, old, min(old_n, n));
            }
            return p;
            
        case ALLOCATOR_FREE:
            break;
            
        default:
            break;
    }
    
    return 0;
}

#endif // OSTD_IMPL