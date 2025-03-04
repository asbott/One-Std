#if 0
#include "ostd.h" // For syntax highlighting.
#endif

/////
// Allocator
/////

typedef enum Allocator_Message {
    ALLOCATOR_ALLOCATE,
    ALLOCATOR_REALLOCATE,
    ALLOCATOR_FREE
} Allocator_Message;
typedef void*(*Allocator_Proc)(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags);

typedef struct Allocator {
    void *data;
    Allocator_Proc proc;
} Allocator;

inline void *allocate(Allocator a, u64 n);
inline void *reallocate(Allocator a, void *p, u64 old_n, u64 n);
inline void deallocate(Allocator a, void *p);

inline void *allocatef(Allocator a, u64 n, u64 flags);
inline void *reallocatef(Allocator a, void *p, u64 old_n, u64 n, u64 flags);
inline void deallocatef(Allocator a, void *p, u64 flags);

#define New(a, T) ((T*)allocate(a, sizeof(T)))
#define NewBuffer(a, T, n) ((T*)allocate(a, sizeof(T)*n))

#define PushTemp(T) New(get_temp(), T)
#define PushTempBuffer(T, n) NewBuffer(get_temp(), T, n)

inline string string_allocate(Allocator a, u64 n);
inline void string_deallocate(Allocator a, string s);

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
void *arena_push_copy(Arena *arena, void *src, u64 size);
void arena_pop(Arena *arena, u64 size);
void arena_reset(Arena *arena);
void free_arena(Arena arena);

void* arena_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags);
unit_local inline Allocator arena_allocator(Arena *a) { return (Allocator) { a, arena_allocator_proc }; }

/////
// Temporary storage
/////

// todo(charlie) temporary storage might get bloated with large temporary allocations,
// so we should provide a way to shrink temporary storage.

Allocator get_temp(void);
void reset_temporary_storage(void);
void *tallocate(size_t n);




inline void *allocate(Allocator a, u64 n) {
    return a.proc(ALLOCATOR_ALLOCATE, a.data, 0, 0, n, 0, 0);
}
inline void *reallocate(Allocator a, void *p, u64 old_n, u64 n) {
    return a.proc(ALLOCATOR_REALLOCATE, a.data, p, old_n, n, 0, 0);
}
inline void deallocate(Allocator a, void *p) {
    a.proc(ALLOCATOR_FREE, a.data, p, 0, 0, 0, 0);
}

inline void *allocatef(Allocator a, u64 n, u64 flags) {
    return a.proc(ALLOCATOR_ALLOCATE, a.data, 0, 0, n, flags, 0);
}
inline void *reallocatef(Allocator a, void *p, u64 old_n, u64 n, u64 flags) {
    return a.proc(ALLOCATOR_REALLOCATE, a.data, p, old_n, n, flags, 0);
}
inline void deallocatef(Allocator a, void *p, u64 flags) {
    a.proc(ALLOCATOR_FREE, a.data, p, 0, 0, flags, 0);
}

inline string string_allocate(Allocator a, u64 n) {
    return (string) {n, (u8*)allocate(a, n)};
}
inline void string_deallocate(Allocator a, string s) {
    deallocate(a, s.data);
}

inline string string_copy(Allocator a, string s) {
    string new_s = string_allocate(a, s.count);
    memcpy(new_s.data, s.data, s.count);
    return new_s;
}

#ifdef OSTD_IMPL

unit_local Arena _temp_arena;
unit_local Allocator _temp;
unit_local bool _temp_initted = false;

unit_local inline void _lazy_init_temporary_storage(void) {
    if (_temp_initted) return;

#if OS_FLAGS & OS_FLAG_EMSCRIPTEN
    _temp_arena = make_arena(1024*1024, 1024*1024);
#else
    _temp_arena = make_arena(sys_get_info().page_size*6900, 1024);
#endif
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
void *tallocate(size_t n) {
    _lazy_init_temporary_storage();

    return allocate(_temp, n);
}

Arena make_arena(u64 reserved_size, u64 initial_allocated_size) {
    assert(reserved_size >= initial_allocated_size);

#if OS_FLAGS & OS_FLAG_EMSCRIPTEN
    assertmsg(reserved_size == initial_allocated_size, STR("Emscripten does not support reserved-only memory allocations. Arena initial allocation size must match reserved_size"));
#endif // OS_FLAGS & OS_FLAG_EMSCRIPTEN

    System_Info info = sys_get_info();

    // Align to page size
    reserved_size = (reserved_size + info.page_size - 1) & ~(info.page_size - 1);
    initial_allocated_size = (initial_allocated_size + info.page_size - 1) & ~(info.page_size - 1);

    assert(initial_allocated_size <= reserved_size);

    Arena arena;

    if (reserved_size > initial_allocated_size) {
        arena.start = sys_map_pages(SYS_MEMORY_RESERVE, 0, reserved_size/info.page_size, false);
        assert(arena.start);
        void *allocate_result = sys_map_pages(SYS_MEMORY_ALLOCATE, arena.start, initial_allocated_size/info.page_size, true);
        assert(allocate_result == arena.start);
    } else {
        arena.start = sys_map_pages(SYS_MEMORY_RESERVE | SYS_MEMORY_ALLOCATE, 0, reserved_size/info.page_size, false);
    }

    arena.position = arena.start;


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

    u64 pointer_count = sys_query_mapped_regions(start, end, 0, 0);

    Mapped_Memory_Info *pointers = (Mapped_Memory_Info *)arena.start;
    sys_query_mapped_regions(start, end, pointers, pointer_count);

    u32 i;
    for (i = 0; i < pointer_count; i += 1) {
        sys_unmap_pages(pointers[i].base);
    }
}

void *arena_push(Arena *arena, u64 size) {

    System_Info info = sys_get_info();

    void *allocated_tail = (u8*)arena->start + arena->allocated_size;
    void *reserved_tail = (u8*)arena->start + arena->reserved_size;

    if ((u64)arena->position + size > (u64)reserved_tail) {
        return 0;
    }

    if ((u64)arena->position + size > (u64)allocated_tail) {

        u64 amount_to_allocate = ((u64)arena->position + size) - (u64)allocated_tail;

        amount_to_allocate = (amount_to_allocate + info.page_size-1) & ~(info.page_size-1);

        u64 pages_to_allocate = amount_to_allocate / info.page_size;

        void *allocate_result = sys_map_pages(SYS_MEMORY_ALLOCATE, allocated_tail, pages_to_allocate, true);
        assertmsg(allocate_result == allocated_tail, "Failed allocating pages in arena");

        arena->allocated_size += amount_to_allocate;
    }

    void *p = arena->position;
    arena->position = (u8*)arena->position + size;

    return p;
}

void *arena_push_copy(Arena *arena, void *src, u64 size) {
    void *dst = arena_push(arena, size);
    memcpy(dst, src, size);
    return dst;
}

void arena_pop(Arena *arena, u64 size) {
    arena->position = (u8*)arena->position - size;
    if ((u64)arena->position < (u64)arena->start)  arena->position = arena->start;
}

void* arena_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags) {
    (void)flags;
    Arena *a = (Arena*)data;
    switch (msg) {
        case ALLOCATOR_ALLOCATE:
        {
            return arena_push(a, n);
        }
        case ALLOCATOR_REALLOCATE:
        {
            u64 pad = (u64)a->start - ((u64)a->start+alignment-1) & ~(alignment-1);
            void* p = (u8*)arena_push(a, n+pad) + pad;
            assert((u64)p % alignment == 0);
            if (old && old_n) {
                memcpy(p, old, (sys_uint)min(old_n, n));
            }
            return p;

        }
        case ALLOCATOR_FREE:
        {
            break;
        }

        default:
        {
            break;
        }
    }

    return 0;
}

#endif // OSTD_IMPL

