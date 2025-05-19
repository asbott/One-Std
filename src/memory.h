#ifndef _MEMORY_H
#define _MEMORY_H

#ifndef _BASE_H
#include "base.h"
#endif // _BASE_H

#ifndef _STRING_H
#include "string.h"
#endif //_STRING_H

#ifndef _SYSTEM_1_H
#include "system1.h"
#endif //_SYSTEM_1_H

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
inline string string_copy(Allocator a, string s);

/////
// Arena
/////

typedef struct Arena {
    void *start;
    void *position;
    u64 reserved_size;
    u64 allocated_size;
} Arena;

OSTD_LIB Arena make_arena(u64 reserved_size, u64 initial_allocated_size);
OSTD_LIB void *arena_push(Arena *arena, u64 size);
OSTD_LIB void *arena_push_copy(Arena *arena, void *src, u64 size);
OSTD_LIB void arena_pop(Arena *arena, u64 size);
OSTD_LIB void arena_reset(Arena *arena);
OSTD_LIB void free_arena(Arena arena);

unit_local void* arena_allocator_proc(Allocator_Message msg, void *data, void *old, u64 old_n, u64 n, u64 alignment, u64 flags);
unit_local inline Allocator arena_allocator(Arena *a) { return (Allocator) { a, arena_allocator_proc }; }

/////
// Temporary storage
/////

// todo(charlie) temporary storage might get bloated with large temporary allocations,
// so we should provide a way to shrink temporary storage.

OSTD_LIB Allocator get_temp(void);
OSTD_LIB void reset_temporary_storage(void);
OSTD_LIB void *tallocate(size_t n);


/////
// Allocation interface
/////

OSTD_LIB void *allocate(Allocator a, u64 n);
OSTD_LIB void *reallocate(Allocator a, void *p, u64 old_n, u64 n);
OSTD_LIB void deallocate(Allocator a, void *p);

OSTD_LIB void *allocatef(Allocator a, u64 n, u64 flags);
OSTD_LIB void *reallocatef(Allocator a, void *p, u64 old_n, u64 n, u64 flags);
OSTD_LIB void deallocatef(Allocator a, void *p, u64 flags);

OSTD_LIB string string_allocate(Allocator a, u64 n);
OSTD_LIB void string_deallocate(Allocator a, string s);

OSTD_LIB string string_copy(Allocator a, string s);


/////
// Arena-backed Persistent Growing Array
/////

/*
    Usage:
    
        Data *my_array;
        persistent_array_init(allocator, (void**)&my_array, sizeof(Data));
        
        persistent_array_reserve(my_array, 7); // Optional, reserve memory for fewer grows
        
        Data elem = ...;
        persistent_array_push_copy(my_array, &elem);
        
        Data *elem = persistent_array_push_empty(my_array);
        
        persistent_array_uninit(my_array);
*/

OSTD_LIB void persistent_array_init(void **pparray, u64 element_size);
OSTD_LIB void persistent_array_uninit(void *parray);
OSTD_LIB void *persistent_array_push_copy(void *parray, void *item);
OSTD_LIB void *persistent_array_push_empty(void *parray);
OSTD_LIB void persistent_array_reserve(void *parray, u64 reserve_count);
OSTD_LIB void persistent_array_shift_left(void *parray, u64 start_index, u64 shift_amount);
OSTD_LIB void *persistent_array_shift_right(void *parray, u64 start_index, u64 shift_amount);
OSTD_LIB void persistent_array_pop(void *parray);
OSTD_LIB void persistent_array_swap_and_pop(void *parray, u64 index);
OSTD_LIB s64 persistent_array_find_from_left(void *parray, void *pcompare_mem);
OSTD_LIB s64 persistent_array_find_from_right(void *parray, void *pcompare_mem);
OSTD_LIB void persistent_array_set_count(void *parray, u64 count);
OSTD_LIB u64 persistent_array_count(void *parray);

typedef struct Arena_Backed_Array_Header {
    Arena arena;
    u64 capacity;
    u64 count;
    u64 elem_size;
    u64 signature;
} Arena_Backed_Array_Header;

#ifdef OSTD_IMPL

typedef struct _Per_Thread_Temporary_Storage {
    Arena arena;
    Allocator a;
    bool initted;
} _Per_Thread_Temporary_Storage;

unit_local inline _Per_Thread_Temporary_Storage* _lazy_init_temporary_storage(void) {
    _Ostd_Thread_Storage *s = _ostd_get_thread_storage();
    assert(s->temp);
    assertmsg(sizeof(_Per_Thread_Temporary_Storage) < sizeof(s->temporary_storage_struct_backing), "refactor time");
    if (s->temp->initted) {
        return s->temp;
    }

#if OS_FLAGS & OS_FLAG_EMSCRIPTEN
    s->temp->arena = make_arena(1024*1024, 1024*1024);
#else
    s->temp->arena = make_arena(sys_get_info().page_size*6900, 1024);
#endif
    s->temp->a = (Allocator) { &s->temp->arena, arena_allocator_proc };
    
    s->temp->initted = true;
    
    return s->temp;
}
Allocator get_temp(void) {
    return _lazy_init_temporary_storage()->a;
}
void reset_temporary_storage(void) {
    arena_reset(&_lazy_init_temporary_storage()->arena);
}
void *tallocate(size_t n) {
    return allocate(_lazy_init_temporary_storage()->a, n);
}

Arena make_arena(u64 reserved_size, u64 initial_allocated_size) {
    assert(reserved_size >= initial_allocated_size);

#if OS_FLAGS & OS_FLAG_EMSCRIPTEN
    assertmsg(reserved_size == initial_allocated_size, "Emscripten does not support reserved-only memory allocations. Arena initial allocation size must match reserved_size");
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
        if (initial_allocated_size) {
            void *allocate_result = sys_map_pages(SYS_MEMORY_ALLOCATE, arena.start, initial_allocated_size/info.page_size, true);
            assert(allocate_result == arena.start);
        }
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
    memcpy(dst, src, (sys_uint)size);
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

void *allocate(Allocator a, u64 n) {
    return a.proc(ALLOCATOR_ALLOCATE, a.data, 0, 0, n, 0, 0);
}
void *reallocate(Allocator a, void *p, u64 old_n, u64 n) {
    return a.proc(ALLOCATOR_REALLOCATE, a.data, p, old_n, n, 0, 0);
}
void deallocate(Allocator a, void *p) {
    a.proc(ALLOCATOR_FREE, a.data, p, 0, 0, 0, 0);
}

void *allocatef(Allocator a, u64 n, u64 flags) {
    return a.proc(ALLOCATOR_ALLOCATE, a.data, 0, 0, n, flags, 0);
}
void *reallocatef(Allocator a, void *p, u64 old_n, u64 n, u64 flags) {
    return a.proc(ALLOCATOR_REALLOCATE, a.data, p, old_n, n, flags, 0);
}
void deallocatef(Allocator a, void *p, u64 flags) {
    a.proc(ALLOCATOR_FREE, a.data, p, 0, 0, flags, 0);
}

string string_allocate(Allocator a, u64 n) {
    return (string) {n, (u8*)allocate(a, n)};
}
void string_deallocate(Allocator a, string s) {
    deallocate(a, s.data);
}

string string_copy(Allocator a, string s) {
    string new_s = string_allocate(a, s.count);
    memcpy(new_s.data, s.data, (sys_uint)s.count);
    return new_s;
}

unit_local Arena_Backed_Array_Header *_persistent_header(void *parray) {
    Arena_Backed_Array_Header *h = (Arena_Backed_Array_Header*)parray - 1;
    assertmsg(h->signature == 0xfeedfacedeadbeef, "Pointer used as persistent array but it was not initialized with persistent_array_init()");
    return h;
}

void persistent_array_init(void **pparray, u64 element_size) {
    // todo(charlie) configurable
    Arena arena = make_arena(1024ULL*1024ULL*1024ULL*4ULL, 0);
    
    Arena_Backed_Array_Header *header = (Arena_Backed_Array_Header*)arena_push(&arena, sizeof(Arena_Backed_Array_Header));
    *header = (Arena_Backed_Array_Header){0};
    header->arena = arena;
    header->signature = 0xfeedfacedeadbeef;
    header->elem_size = element_size;
    
    *pparray = header->arena.position;
}
void persistent_array_uninit(void *parray) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    free_arena(h->arena);
}
void *persistent_array_push_copy(void *parray, void *src) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    void *p = persistent_array_push_empty(parray);
    memcpy(p, src, h->elem_size);
    return p;
}
void *persistent_array_push_empty(void *parray) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    
    void *p;
    if (h->count == h->capacity) {
        p = arena_push(&h->arena, h->elem_size);
        h->capacity += 1;
    } else {
        assert(h->count < h->capacity);
        p = (u8*)parray + h->count*h->elem_size;
    }
    
    h->count += 1;
    
    return p;
}
void persistent_array_reserve(void *parray, u64 reserve_count) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    if (reserve_count <= h->capacity) return;
    
    u64 diff = reserve_count - h->capacity;
    
    arena_push(&h->arena, diff*h->elem_size);
    h->capacity += diff;
}
void persistent_array_shift_left(void *parray, u64 start_index, u64 shift_amount) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    assertmsg(start_index < h->count, "Index out of range");
    u64 left_count = h->count-start_index-1;
    assert(shift_amount <= left_count);
    
    memcpy(
        (u8*)parray+(start_index-shift_amount)*h->elem_size, 
        (u8*)parray+(h->count-start_index)*h->elem_size, 
        shift_amount*h->elem_size
    );
}
void *persistent_array_shift_right(void *parray, u64 start_index, u64 shift_amount) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    assertmsg(start_index < h->count, "Index out of range");
    
    persistent_array_reserve(parray, h->count+shift_amount);
    
    memcpy(
        (u8*)parray+(start_index+shift_amount)*h->elem_size, 
        (u8*)parray+start_index*h->elem_size, 
        shift_amount*h->elem_size
    );
    
    return (u8*)parray+start_index*h->elem_size;
}
void persistent_array_pop(void *parray) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    assert(h->count > 0);
    h->count -= 1;
}
void persistent_array_swap_and_pop(void *parray, u64 index) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    persistent_array_pop(parray);
    memcpy((u8*)parray+index*h->elem_size, (u8*)parray+h->count*h->elem_size, h->elem_size);
}
s64 persistent_array_find_from_left(void *parray, void *pcompare_mem) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    for (u64 i = 0; i < h->count; i += 1) {
        if (memcmp(pcompare_mem, (u8*)parray + i*h->elem_size, h->elem_size) == 0)
            return (s64)i;
    }
    return -1;
}
s64 persistent_array_find_from_right(void *parray, void *pcompare_mem) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    for (s64 i = (s64)h->count-1; i >= 0; i -= 1) {
        if (memcmp(pcompare_mem, (u8*)parray + (u64)i*h->elem_size, h->elem_size) == 0)
            return i;
    }
    return -1;
}

void persistent_array_set_count(void *parray, u64 count) {
    Arena_Backed_Array_Header *h = _persistent_header(parray);
    persistent_array_reserve(parray, count);
    h->count = count;
}

u64 persistent_array_count(void *parray) {
    return _persistent_header(parray)->count;
}

#endif // OSTD_IMPL

#endif // _MEMORY_H
