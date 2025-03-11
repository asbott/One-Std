//
// This file was auto-generated using the following command:
//
// jai generate.jai
//



COMPILER_FLAG_CLANG :: 1 << 0;
COMPILER_FLAG_GNU :: 1 << 1;
COMPILER_FLAG_MSC :: 1 << 2;
COMPILER_FLAG_INTEL :: 1 << 3;
COMPILER_FLAG_TCC :: 1 << 4;
COMPILER_FLAG_EMSCRIPTEN :: 1 << 5;
COMPILER_FLAG_PGI :: 1 << 6;
COMPILER_FLAG_SUNPRO :: 1 << 7;
COMPILER_FLAG_CLANG_GNU :: 1 << 8;

CLANG :: 1;

GNU :: 0;

MSC :: 1;

INTEL :: 0;

TCC :: 0;

EMSCRIPTEN :: 0;

PGI :: 0;

SUNPRO :: 0;

ARCH_X64 :: 1;

CSTD_C90 :: 1;

CSTD_C99 :: 0;

CSTD_C11 :: 0;

CSTD_C17 :: 1;

CSTD_C23 :: 0;

CSTD :: "C17";

OS_FLAG_WINDOWS :: 1 << 0;
OS_FLAG_UNIX :: 1 << 1;
OS_FLAG_LINUX :: 1 << 2;
OS_FLAG_APPLE :: 1 << 3;
OS_FLAG_MACOS :: 1 << 4;
OS_FLAG_IOS :: 1 << 5;
OS_FLAG_ANDROID :: 1 << 6;
OS_FLAG_STEAMOS :: 1 << 7;
OS_FLAG_LINUX_BASED :: 1 << 8;
OS_FLAG_HAS_WINDOW_SYSTEM :: 1 << 9;
OS_FLAG_EMSCRIPTEN :: 1 << 10;

OS_FLAG_WEB :: OS_FLAG_EMSCRIPTEN;

OS_FLAGS :: OS_FLAG_WINDOWS | OS_FLAG_HAS_WINDOW_SYSTEM;

HAS_FLOAT128 :: 0;

U8_MIN :: 0;
U8_MAX :: 255;
S8_MIN :: -128;
S8_MAX :: 127;
U16_MIN :: 0;
U16_MAX :: 65535;
S16_MIN :: -32768;
S16_MAX :: 32767;
U32_MIN :: 0;
U32_MAX :: 4294967295;
S32_MIN :: -2147483648;
S32_MAX :: 2147483647;
U64_MIN :: 0;
U64_MAX :: 18446744073709551615;
S64_MIN :: -9223372036854775807 - 1;
S64_MAX :: 9223372036854775807;

UINT8_MIN :: 0;
UINT8_MAX :: 255;
INT8_MIN :: -128;
INT8_MAX :: 127;
UINT16_MIN :: 0;
UINT16_MAX :: 65535;
INT16_MIN :: -32768;
INT16_MAX :: 32767;
UINT32_MIN :: 0;
UINT32_MAX :: 4294967295;
INT32_MIN :: -2147483648;
INT32_MAX :: 2147483647;
UINT64_MIN :: 0;
UINT64_MAX :: 18446744073709551615;
INT64_MIN :: -9223372036854775807 - 1;
INT64_MAX :: 9223372036854775807;

_true :: 1;
_false :: 0;

PI :: 3.141592653589793;
TAU :: PI*2;

SYS_MEMORY_RESERVE :: 1 << 0;
SYS_MEMORY_ALLOCATE :: 1 << 1;

FILE_OPEN_WRITE :: 1 << 0;
FILE_OPEN_READ :: 1 << 1;
FILE_OPEN_RESET :: 1 << 2;
FILE_OPEN_CREATE :: 1 << 3;

SURFACE_FLAG_HIDDEN :: 1 << 0;
SURFACE_FLAG_TOPMOST :: 1 << 1;

MAX_SURFACES :: 64;
MAX_PATH_LENGTH :: 260;

UTF16_SURROGATE_HIGH_START :: 0xD800;
UTF16_SURROGATE_HIGH_END :: 0xDBFF;
UTF16_SURROGATE_LOW_START :: 0xDC00;
UTF16_SURROGATE_LOW_END :: 0xDFFF;
UTF16_SURROGATE_OFFSET :: 0x10000;
UTF16_SURROGATE_MASK :: 0x3FF;

UNI_REPLACEMENT_CHAR :: 0x0000FFFD;
UNI_MAX_UTF32 :: 0x7FFFFFFF;
UNI_MAX_UTF16 :: 0x0010FFFF;
SURROGATES_START :: 0xD800;
SURROGATES_END :: 0xDFFF;

MAX_VAR_ARGS :: 70;

OGA_LOG_VERBOSE :: 1 << 16;

OGA_DEVICE_FEATURE_GRAPHICS_TIMESTAMP :: 1 << 0;
OGA_DEVICE_FEATURE_COMPUTE_TIMESTAMP :: 1 << 1;
OGA_DEVICE_FEATURE_PRESENT_MAILBOX :: 1 << 2;
OGA_DEVICE_FEATURE_DEPTH_CLAMP :: 1 << 3;

OGA_MAX_DEVICE_LOGICAL_ENGINE_FAMILIES :: 32;
OGA_MAX_DEVICE_LOGICAL_ENGINES_PER_FAMILY :: 32;
OGA_MAX_MEMORY_HEAPS_PER_DEVICE :: 32;

MAX_SWAPCHAIN_IMAGES :: 16;

OGA_MAX_VERTEX_BINDING_COUNT :: 32;
OGA_MAX_VERTEX_ATTRIBUTE_COUNT :: 32;
MAX_VERTEX_ATTRIBUTE_OFFSET :: 2047;
MAX_VERTEX_BINDING_OFFSET :: 2048;

OGA_COMMAND_POOL_NONE :: 0;
OGA_COMMAND_POOL_SHORT_LIVED_ALLOCATIONS :: 1 << 0;

OGA_COMMAND_LIST_USAGE_ONE_TIME_SUBMIT :: 1 << 0;

OGA_MSAA_RESOLVE_MODE_NONE :: 0;
OGA_MSAA_RESOLVE_MODE_ZERO :: 1 << 0;
OGA_MSAA_RESOLVE_MODE_AVERAGE :: 1 << 1;
OGA_MSAA_RESOLVE_MODE_MIN :: 1 << 2;
OGA_MSAA_RESOLVE_MODE_MAX :: 1 << 3;

uintptr :: u64;

_float32 :: float;

uint8 :: u8;
int8 :: s8;
uint16 :: u16;
int16 :: s16;
uint32 :: u32;
int32 :: s32;
uint64 :: u64;
int64 :: s64;

f32 :: _float32;
f64 :: float64;

sys_int :: s64;
sys_uint :: u64;

int32x2 :: struct {
    x: int32;
    y: int32;
}

int32x4 :: struct {
    x: int32;
    y: int32;
    z: int32;
    w: int32;
}

int2 :: int32x2;

float2x32 :: struct {
    x: float;
    y: float;
}

float3x32 :: struct {
    x: float;
    y: float;
    z: float;
}

float4x32 :: struct {
    x: float;
    y: float;
    z: float;
    w: float;
}

float2 :: float2x32;
float3 :: float3x32;
float4 :: float4x32;

// Column major
Matrix4 :: struct {
    data: [4] [4] _float32;
}

Mapped_Memory_Info :: struct {
    base:       *void;
    page_count: u64;
}

//////
// System info
//////
System_Info :: struct {
    page_size:         u64;
    granularity:       u64;
    logical_cpu_count: u64;
}

Physical_Monitor :: struct {
    //  Do (string) {monitor.name_count, monitor.name}
    name:         [256] u8;
    name_count:   u64;
    refresh_rate: int64;
    resolution_x: int64;
    resolution_y: int64;
    scale:        float64;
    pos_x:        int64;
    pos_y:        int64;

    handle:       *void;
}

//////
// IO
//////
File_Handle :: *void;
File_Open_Flags :: u64;

sys_get_stdout :: () -> File_Handle #foreign ostd_windows;
sys_get_stderr :: () -> File_Handle #foreign ostd_windows;

sys_write :: (h: File_Handle, data: *void, size: u64) -> s64 #foreign ostd_windows;
sys_write_string :: (h: File_Handle, s: string) -> s64 #foreign ostd_windows;

sys_read :: (h: File_Handle, buffer: *void, buffer_size: u64) -> s64 #foreign ostd_windows;

sys_make_pipe :: (read: *File_Handle, write: *File_Handle) -> bool #foreign ostd_windows;

sys_close :: (h: File_Handle) -> void #foreign ostd_windows;

// Returns 0 on failure
sys_open_file :: (path: string, flags: File_Open_Flags) -> File_Handle #foreign ostd_windows;
sys_get_file_size :: (f: File_Handle) -> u64 #foreign ostd_windows;

sys_make_directory :: (path: string, recursive: bool) -> bool #foreign ostd_windows;
sys_remove_directory :: (path: string, recursive: bool) -> bool #foreign ostd_windows;
sys_is_file :: (path: string) -> bool #foreign ostd_windows;
sys_is_directory :: (path: string) -> bool #foreign ostd_windows;

Walk_Proc :: #type (unknown0: string) -> bool #c_call;
sys_walk_directory :: (path: string, recursive: bool, walk_directories: bool, walk_proc: Walk_Proc) -> void #foreign ostd_windows;

Easy_Command_Result :: struct {
    exit_code:             s64;
    process_start_success: bool;
}

sys_run_command_easy :: (command_line: string, stdout: File_Handle, stderr: File_Handle, workspace_dir: string) -> Easy_Command_Result #foreign ostd_windows;

//////
// Sockets
//////
Socket :: u64;

Socket_Result :: enum s32 {
    OK                  :: 0;

    DISCONNECTED        :: 1;
    NOT_INITIALIZED     :: 2;
    NOACCESS            :: 3;
    IN_PROGRESS         :: 4;
    NOT_A_SOCKET        :: 5;

    INVALID_ADDRESS     :: 6;
    TIMED_OUT           :: 7;
    CONNECTION_REFUSED  :: 8;
    CONNECTION_RESET    :: 9;
    ALREADY_CONNECTED   :: 10;
    ADDRESS_IN_USE      :: 11;
    NETWORK_UNREACHABLE :: 12;
    HOST_UNREACHABLE    :: 13;
    PROTOCOL_ERROR      :: 14;

    SOCKET_OK                  :: OK;

    SOCKET_DISCONNECTED        :: DISCONNECTED;
    SOCKET_NOT_INITIALIZED     :: NOT_INITIALIZED;
    SOCKET_NOACCESS            :: NOACCESS;
    SOCKET_IN_PROGRESS         :: IN_PROGRESS;
    SOCKET_NOT_A_SOCKET        :: NOT_A_SOCKET;

    SOCKET_INVALID_ADDRESS     :: INVALID_ADDRESS;
    SOCKET_TIMED_OUT           :: TIMED_OUT;
    SOCKET_CONNECTION_REFUSED  :: CONNECTION_REFUSED;
    SOCKET_CONNECTION_RESET    :: CONNECTION_RESET;
    SOCKET_ALREADY_CONNECTED   :: ALREADY_CONNECTED;
    SOCKET_ADDRESS_IN_USE      :: ADDRESS_IN_USE;
    SOCKET_NETWORK_UNREACHABLE :: NETWORK_UNREACHABLE;
    SOCKET_HOST_UNREACHABLE    :: HOST_UNREACHABLE;
    SOCKET_PROTOCOL_ERROR      :: PROTOCOL_ERROR;
}

Socket_Domain :: enum s32 {
    IPV4      :: 0;
    BLUETOOTH :: 1;
    APPLETALK :: 2;

    SOCKET_DOMAIN_IPV4      :: IPV4;
    SOCKET_DOMAIN_BLUETOOTH :: BLUETOOTH;
    SOCKET_DOMAIN_APPLETALK :: APPLETALK;
}

Socket_Type :: enum s32 {
    STREAM    :: 0;
    DGRAM     :: 1;
    RAW       :: 2;
    RDM       :: 3;
    SEQPACKET :: 4;

    SOCKET_TYPE_STREAM    :: STREAM;
    SOCKET_TYPE_DGRAM     :: DGRAM;
    SOCKET_TYPE_RAW       :: RAW;
    SOCKET_TYPE_RDM       :: RDM;
    SOCKET_TYPE_SEQPACKET :: SEQPACKET;
}

Socket_Protocol :: enum s32 {
    TCP :: 0;
    UDP :: 1;

    SOCKET_PROTOCOL_TCP :: TCP;
    SOCKET_PROTOCOL_UDP :: UDP;
}

sys_convert_address_string :: (address: string) -> u32 #foreign ostd_windows;

sys_socket_init :: (socket: *Socket, domain: Socket_Domain, type: Socket_Type, protocol: Socket_Protocol) -> Socket_Result #foreign ostd_windows;
sys_socket_bind :: (socket: Socket, address: u32, port: u16) -> Socket_Result #foreign ostd_windows;
sys_socket_listen :: (socket: Socket, backlog: s64) -> Socket_Result #foreign ostd_windows;
sys_socket_accept :: (socket: Socket, accepted: *Socket, timeout_ms: u64) -> Socket_Result #foreign ostd_windows;

sys_socket_send :: (socket: Socket, data: *void, length: u64, sent: *u64) -> Socket_Result #foreign ostd_windows;
sys_socket_recv :: (socket: Socket, buffer: *void, length: u64, sent: *u64) -> Socket_Result #foreign ostd_windows;
sys_socket_close :: (socket: Socket) -> Socket_Result #foreign ostd_windows;
sys_socket_set_blocking :: (socket: *Socket, blocking: bool) -> Socket_Result #foreign ostd_windows;
sys_set_socket_blocking_timeout :: (socket: Socket, ms: u64) -> Socket_Result #foreign ostd_windows;

//////
// Thread Primitives
//////
Thread_Key :: *void;

sys_get_current_thread_id :: () -> u64 #foreign ostd_windows;

sys_thread_key_init :: (key: *Thread_Key) -> bool #foreign ostd_windows;
sys_thread_key_write :: (key: Thread_Key, value: *void) -> bool #foreign ostd_windows;
sys_thread_key_read :: (key: Thread_Key) -> *void #foreign ostd_windows;

Thread_Proc :: #type (unknown0: *Thread) -> s64 #c_call;
Thread :: struct {
    handle:       *void;
    id:           u64;
    userdata:     *void;
    proc:         Thread_Proc;
    is_suspended: bool;
}

sys_thread_init :: (thread: *Thread, proc: Thread_Proc, userdata: *void) -> bool #foreign ostd_windows;
sys_thread_start :: (thread: *Thread) -> void #foreign ostd_windows;
sys_thread_join :: (thread: *Thread) -> void #foreign ostd_windows;
sys_thread_close :: (thread: *Thread) -> void #foreign ostd_windows;

Mutex :: struct {
    handle:         *void;
    handle_backing: [40] u8; // This is for windows critical section;
}

sys_mutex_init :: (mutex: *Mutex) -> bool #foreign ostd_windows;
sys_mutex_uninit :: (mutex: *Mutex) -> bool #foreign ostd_windows;
sys_mutex_acquire :: (mutex: Mutex) -> void #foreign ostd_windows;
sys_mutex_release :: (mutex: Mutex) -> void #foreign ostd_windows;

Surface_Handle :: *void;

// todo(charlie) more flags
Surface_Flags :: u64;

Surface_Desc :: struct {
    // These don't do anything for main surface on phone/console systems
    width:      u32;
    height:     u32;
    x_pos:      u32;
    y_pos:      u32;
    title:      string;
    fullscreen: bool;
    flags:      Surface_Flags;
}

sys_make_surface :: (desc: Surface_Desc) -> Surface_Handle #foreign ostd_windows;
surface_close :: (s: Surface_Handle) -> void #foreign ostd_windows;

surface_poll_events :: (surface: Surface_Handle) -> void #foreign ostd_windows;
surface_should_close :: (s: Surface_Handle) -> bool #foreign ostd_windows;

// Will return false on systems where the flag isn't implemented
surface_set_flags :: (h: Surface_Handle, flags: Surface_Flags) -> bool #foreign ostd_windows;
surface_unset_flags :: (h: Surface_Handle, flags: Surface_Flags) -> bool #foreign ostd_windows;

surface_get_framebuffer_size :: (h: Surface_Handle, width: *s64, height: *s64) -> bool #foreign ostd_windows;

surface_map_pixels :: (h: Surface_Handle) -> *void #foreign ostd_windows;
surface_blit_pixels :: (h: Surface_Handle) -> void #foreign ostd_windows;

surface_get_monitor :: (h: Surface_Handle, monitor: *Physical_Monitor) -> bool #foreign ostd_windows;

//////
// Time
//////
sys_get_seconds_monotonic :: () -> float64 #foreign ostd_windows;

//////
// Process & Thread
//////
Thread_Handle :: *void;

sys_get_current_thread :: () -> Thread_Handle #foreign ostd_windows;
sys_set_thread_affinity_mask :: (thread: Thread_Handle, bits: u64) -> void #foreign ostd_windows;

Priority_Level :: enum s32 {
    LOW    :: 0;
    MEDIUM :: 1;
    HIGH   :: 2;

    SYS_PRIORITY_LOW    :: LOW;
    SYS_PRIORITY_MEDIUM :: MEDIUM;
    SYS_PRIORITY_HIGH   :: HIGH;
}

sys_set_local_process_priority_level :: (level: Priority_Level) -> void #foreign ostd_windows;
sys_set_thread_priority_level :: (thread: Thread_Handle, level: Priority_Level) -> void #foreign ostd_windows;

sys_load_library :: (s: string) -> *void #foreign ostd_windows;
sys_close_library :: (lib: *void) -> void #foreign ostd_windows;
sys_get_library_symbol :: (lib: *void, symbol: string) -> *void #foreign ostd_windows;

//////
// Debug
//////
sys_print_stack_trace :: (handle: File_Handle) -> void #foreign ostd_windows;

//////
// Implementations
//////
Per_Thread_Temporary_Storage :: struct {}
Ostd_Thread_Storage :: struct {
    thread_id:                        u64;
    temporary_storage_struct_backing: [128] u8;
    temp:                             *Per_Thread_Temporary_Storage;
    taken:                            bool;
}

_Ostd_Thread_Storage :: Ostd_Thread_Storage;

Utf8_To_Utf32_Result :: struct {
    utf32:              u32;
    continuation_bytes: s64;
    reached_end:        bool;
    error:              bool;
}

Utf8_To_Utf16_Result :: struct {
    utf32:              u32;
    continuation_bytes: s64;
    reached_end:        bool;
    error:              bool;
}

/////
// Allocator
/////
Allocator_Message :: enum s32 {
    ALLOCATE   :: 0;
    REALLOCATE :: 1;
    FREE       :: 2;

    ALLOCATOR_ALLOCATE   :: ALLOCATE;
    ALLOCATOR_REALLOCATE :: REALLOCATE;
    ALLOCATOR_FREE       :: FREE;
}

Allocator_Proc :: #type (msg: Allocator_Message, data: *void, old: *void, old_n: u64, n: u64, alignment: u64, flags: u64) -> *void #c_call;

Allocator :: struct {
    data: *void;
    proc: Allocator_Proc;
}

/////
// Arena
/////
Arena :: struct {
    start:          *void;
    position:       *void;
    reserved_size:  u64;
    allocated_size: u64;
}

make_arena :: (reserved_size: u64, initial_allocated_size: u64) -> Arena #foreign ostd_windows;
arena_push :: (arena: *Arena, size: u64) -> *void #foreign ostd_windows;
arena_push_copy :: (arena: *Arena, src: *void, size: u64) -> *void #foreign ostd_windows;
arena_pop :: (arena: *Arena, size: u64) -> void #foreign ostd_windows;
arena_reset :: (arena: *Arena) -> void #foreign ostd_windows;
free_arena :: (arena: Arena) -> void #foreign ostd_windows;

// todo(charlie) temporary storage might get bloated with large temporary allocations,
// so we should provide a way to shrink temporary storage.
get_temp :: () -> Allocator #foreign ostd_windows;
reset_temporary_storage :: () -> void #foreign ostd_windows;
tallocate :: (n: u64) -> *void #foreign ostd_windows;

Var_Arg :: struct {
    int_val: u64;
    flt_val: float64;
    str_val: string;

    size:    u64;
}

//////
// Printing
//////
Source_Location :: struct {
    line:     u64;
    file:     string;
    function: string;
}

Logger_Proc :: #type (message: string, flags: u64, location: Source_Location) -> void #c_call;

Format_String_Desc :: struct {
    buffer:      *void;
    buffer_size: u64;
    fmt:         string;
}

_Format_String_Desc :: Format_String_Desc;

Print_Desc :: struct {
    a:    Allocator;
    fmt:  string;
    file: File_Handle;
}

_Print_Desc :: Print_Desc;

Log_Desc :: struct {
    a:        Allocator;
    fmt:      string;
    flags:    u64;
    location: Source_Location;
}

_Log_Desc :: Log_Desc;

sys_read_entire_file :: (a: Allocator, path: string, result: *string) -> bool #foreign ostd_windows;
sys_write_entire_file :: (path: string, data: string) -> bool #foreign ostd_windows;

path_get_filename :: (path: string) -> string #foreign ostd_windows;
path_strip_one_extension :: (path: string) -> string #foreign ostd_windows;
path_strip_all_extensions :: (path: string) -> string #foreign ostd_windows;

// todo(charlie) make a stack of non-OK results which can be popped
Oga_Result :: enum s32 {
    OK                                                             :: 0;

    SUBOPTIMAL                                                     :: 1;
    NOT_READY                                                      :: 2;
    TIMEOUT                                                        :: 3;

    CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES                     :: 4;

    CONTEXT_INIT_ERROR_BAD_STATE_ALLOCATOR                         :: 5;

    CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE          :: 6;

    CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW           :: 7;

    INIT_SWAPCHAIN_ERROR_SURFACE_REJECTED                          :: 8;
    INIT_SWAPCHAIN_ERROR_UNSUPPORTED_PRESENT_MODE                  :: 9;

    INIT_PROGRAM_ERROR_BAD_CODE                                    :: 10;

    ERROR_STATE_ALLOCATION_FAILED                                  :: 11;
    ERROR_OUT_OF_DEVICE_MEMORY                                     :: 12;
    ERROR_OUTDATED                                                 :: 13;
    ERROR_SURFACE_LOST                                             :: 14;

    ALLOCATE_MEMORY_ERROR_INVALID_PROPERTIES_AND_USAGE_COMBINATION :: 15;
    ERROR_INVALID_INPUT_RATE_ENUM                                  :: 16;

    MEMORY_OFFSET_ERROR_UNDERFLOW                                  :: 17;
    MEMORY_OFFSET_ERROR_OVERFLOW                                   :: 18;

    CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM                          :: 19;
    CMD_DRAW_ERROR_VERTEX_LIST_BINDING_COUNT_ZERO                  :: 20;
    CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING                     :: 21;
    CMD_DRAW_ERROR_VERTEX_LIST_OFFSET_OUT_OF_RANGE                 :: 22;
    CMD_DRAW_ERROR_MISSING_INDEX_LIST                              :: 23;
    CMD_DRAW_ERROR_INVALID_INDEX_TYPE_ENUM                         :: 24;

    INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT               :: 25;
    INIT_INDEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT                :: 26;

    INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM                  :: 27;
    INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED                     :: 28;
    INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT               :: 29;
    INIT_OPTIMAL_COPY_VIEW_ERROR_INVALID_FLAGS                     :: 30;

    INIT_RENDER_PASS_ERROR_INVALID_PROGRAM_BINDING_KIND_ENUM       :: 31;
    INIT_BINDING_LIST_LAYOUT_ERROR_MISSING_STAGE_FLAGS             :: 32;

    PUSH_BINDING_LIST_ERROR_LAYOUT_COUNT_MISMATCH                  :: 33;

    OGA_OK                                                             :: OK;

    OGA_SUBOPTIMAL                                                     :: SUBOPTIMAL;
    OGA_NOT_READY                                                      :: NOT_READY;
    OGA_TIMEOUT                                                        :: TIMEOUT;

    OGA_CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES                     :: CONTEXT_INIT_ERROR_MISSING_DEVICE_FEATURES;

    OGA_CONTEXT_INIT_ERROR_BAD_STATE_ALLOCATOR                         :: CONTEXT_INIT_ERROR_BAD_STATE_ALLOCATOR;

    OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE          :: CREATE_LOGICAL_ENGINE_ERROR_FAMILY_INDEX_OUT_OF_RANGE;

    OGA_CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW           :: CREATE_LOGICAL_ENGINE_ERROR_FAMILY_CAPACITY_OVERFLOW;

    OGA_INIT_SWAPCHAIN_ERROR_SURFACE_REJECTED                          :: INIT_SWAPCHAIN_ERROR_SURFACE_REJECTED;
    OGA_INIT_SWAPCHAIN_ERROR_UNSUPPORTED_PRESENT_MODE                  :: INIT_SWAPCHAIN_ERROR_UNSUPPORTED_PRESENT_MODE;

    OGA_INIT_PROGRAM_ERROR_BAD_CODE                                    :: INIT_PROGRAM_ERROR_BAD_CODE;

    OGA_ERROR_STATE_ALLOCATION_FAILED                                  :: ERROR_STATE_ALLOCATION_FAILED;
    OGA_ERROR_OUT_OF_DEVICE_MEMORY                                     :: ERROR_OUT_OF_DEVICE_MEMORY;
    OGA_ERROR_OUTDATED                                                 :: ERROR_OUTDATED;
    OGA_ERROR_SURFACE_LOST                                             :: ERROR_SURFACE_LOST;

    OGA_ALLOCATE_MEMORY_ERROR_INVALID_PROPERTIES_AND_USAGE_COMBINATION :: ALLOCATE_MEMORY_ERROR_INVALID_PROPERTIES_AND_USAGE_COMBINATION;
    OGA_ERROR_INVALID_INPUT_RATE_ENUM                                  :: ERROR_INVALID_INPUT_RATE_ENUM;

    OGA_MEMORY_OFFSET_ERROR_UNDERFLOW                                  :: MEMORY_OFFSET_ERROR_UNDERFLOW;
    OGA_MEMORY_OFFSET_ERROR_OVERFLOW                                   :: MEMORY_OFFSET_ERROR_OVERFLOW;

    OGA_CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM                          :: CMD_DRAW_ERROR_INVALID_DRAW_TYPE_ENUM;
    OGA_CMD_DRAW_ERROR_VERTEX_LIST_BINDING_COUNT_ZERO                  :: CMD_DRAW_ERROR_VERTEX_LIST_BINDING_COUNT_ZERO;
    OGA_CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING                     :: CMD_DRAW_ERROR_MISSING_VERTEX_LIST_BINDING;
    OGA_CMD_DRAW_ERROR_VERTEX_LIST_OFFSET_OUT_OF_RANGE                 :: CMD_DRAW_ERROR_VERTEX_LIST_OFFSET_OUT_OF_RANGE;
    OGA_CMD_DRAW_ERROR_MISSING_INDEX_LIST                              :: CMD_DRAW_ERROR_MISSING_INDEX_LIST;
    OGA_CMD_DRAW_ERROR_INVALID_INDEX_TYPE_ENUM                         :: CMD_DRAW_ERROR_INVALID_INDEX_TYPE_ENUM;

    OGA_INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT               :: INIT_VERTEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT;
    OGA_INIT_INDEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT                :: INIT_INDEX_LIST_VIEW_ERROR_MEMORY_LACKS_SUPPORT;

    OGA_INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM                  :: INIT_IMAGE_VIEW_ERROR_INVALID_DIMENSIONS_ENUM;
    OGA_INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED                     :: INIT_IMAGE_VIEW_ERR_IMAGE_MEMORY_UNALIGNED;
    OGA_INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT               :: INIT_IMAGE_VIEW_ERR_UNMATCHED_MEMORY_REQUIREMENT;
    OGA_INIT_OPTIMAL_COPY_VIEW_ERROR_INVALID_FLAGS                     :: INIT_OPTIMAL_COPY_VIEW_ERROR_INVALID_FLAGS;

    OGA_INIT_RENDER_PASS_ERROR_INVALID_PROGRAM_BINDING_KIND_ENUM       :: INIT_RENDER_PASS_ERROR_INVALID_PROGRAM_BINDING_KIND_ENUM;
    OGA_INIT_BINDING_LIST_LAYOUT_ERROR_MISSING_STAGE_FLAGS             :: INIT_BINDING_LIST_LAYOUT_ERROR_MISSING_STAGE_FLAGS;

    OGA_PUSH_BINDING_LIST_ERROR_LAYOUT_COUNT_MISMATCH                  :: PUSH_BINDING_LIST_ERROR_LAYOUT_COUNT_MISMATCH;
}

Oga_Format :: enum s32 {
    R4G4_UNORM_PACK8       :: 0;
    R4G4B4A4_UNORM_PACK16  :: 1;
    B4G4R4A4_UNORM_PACK16  :: 2;
    R5G6B5_UNORM_PACK16    :: 3;
    B5G6R5_UNORM_PACK16    :: 4;
    R5G5B5A1_UNORM_PACK16  :: 5;
    A1R5G5B5_UNORM_PACK16  :: 6;

    R8_UNORM               :: 7;
    R8_SNORM               :: 8;
    R8_UINT                :: 9;
    R8_SINT                :: 10;
    R8_SRGB                :: 11;

    R8G8_UNORM             :: 12;
    R8G8_SNORM             :: 13;
    R8G8_UINT              :: 14;
    R8G8_SINT              :: 15;
    R8G8_SRGB              :: 16;

    R8G8B8_UNORM           :: 17;
    R8G8B8_SNORM           :: 18;
    R8G8B8_UINT            :: 19;
    R8G8B8_SINT            :: 20;
    R8G8B8_SRGB            :: 21;

    R8G8B8A8_UNORM         :: 22;
    R8G8B8A8_SNORM         :: 23;
    R8G8B8A8_UINT          :: 24;
    R8G8B8A8_SINT          :: 25;
    R8G8B8A8_SRGB          :: 26;

    B8G8R8A8_UNORM         :: 27;
    B8G8R8A8_SNORM         :: 28;
    B8G8R8A8_UINT          :: 29;
    B8G8R8A8_SINT          :: 30;
    B8G8R8A8_SRGB          :: 31;

    R16_UNORM              :: 32;
    R16_SNORM              :: 33;
    R16_UINT               :: 34;
    R16_SINT               :: 35;
    R16_SFLOAT             :: 36;

    R16G16_UNORM           :: 37;
    R16G16_SNORM           :: 38;
    R16G16_UINT            :: 39;
    R16G16_SINT            :: 40;
    R16G16_SFLOAT          :: 41;

    R16G16B16A16_UNORM     :: 42;
    R16G16B16A16_SNORM     :: 43;
    R16G16B16A16_UINT      :: 44;
    R16G16B16A16_SINT      :: 45;
    R16G16B16A16_SFLOAT    :: 46;

    R32_SFLOAT             :: 47;
    R32_UINT               :: 48;
    R32_SINT               :: 49;

    R32G32_SFLOAT          :: 50;
    R32G32_UINT            :: 51;
    R32G32_SINT            :: 52;

    R32G32B32_SFLOAT       :: 53;
    R32G32B32_UINT         :: 54;
    R32G32B32_SINT         :: 55;

    R32G32B32A32_SFLOAT    :: 56;
    R32G32B32A32_UINT      :: 57;
    R32G32B32A32_SINT      :: 58;

    DEPTH16_UNORM          :: 59;
    DEPTH24_UNORM_S8_UINT  :: 60;
    DEPTH32_SFLOAT         :: 61;
    DEPTH32_SFLOAT_S8_UINT :: 62;

    BC1_RGB_UNORM_BLOCK    :: 63;
    BC1_RGB_SRGB_BLOCK     :: 64;
    BC1_RGBA_UNORM_BLOCK   :: 65;
    BC1_RGBA_SRGB_BLOCK    :: 66;
    BC2_UNORM_BLOCK        :: 67;
    BC2_SRGB_BLOCK         :: 68;
    BC3_UNORM_BLOCK        :: 69;
    BC3_SRGB_BLOCK         :: 70;
    BC4_UNORM_BLOCK        :: 71;
    BC4_SNORM_BLOCK        :: 72;
    BC5_UNORM_BLOCK        :: 73;
    BC5_SNORM_BLOCK        :: 74;
    BC6H_UFLOAT_BLOCK      :: 75;
    BC6H_SFLOAT_BLOCK      :: 76;
    BC7_UNORM_BLOCK        :: 77;
    BC7_SRGB_BLOCK         :: 78;

    ENUM_MAX               :: 79;

    OGA_FORMAT_R4G4_UNORM_PACK8       :: R4G4_UNORM_PACK8;
    OGA_FORMAT_R4G4B4A4_UNORM_PACK16  :: R4G4B4A4_UNORM_PACK16;
    OGA_FORMAT_B4G4R4A4_UNORM_PACK16  :: B4G4R4A4_UNORM_PACK16;
    OGA_FORMAT_R5G6B5_UNORM_PACK16    :: R5G6B5_UNORM_PACK16;
    OGA_FORMAT_B5G6R5_UNORM_PACK16    :: B5G6R5_UNORM_PACK16;
    OGA_FORMAT_R5G5B5A1_UNORM_PACK16  :: R5G5B5A1_UNORM_PACK16;
    OGA_FORMAT_A1R5G5B5_UNORM_PACK16  :: A1R5G5B5_UNORM_PACK16;

    OGA_FORMAT_R8_UNORM               :: R8_UNORM;
    OGA_FORMAT_R8_SNORM               :: R8_SNORM;
    OGA_FORMAT_R8_UINT                :: R8_UINT;
    OGA_FORMAT_R8_SINT                :: R8_SINT;
    OGA_FORMAT_R8_SRGB                :: R8_SRGB;

    OGA_FORMAT_R8G8_UNORM             :: R8G8_UNORM;
    OGA_FORMAT_R8G8_SNORM             :: R8G8_SNORM;
    OGA_FORMAT_R8G8_UINT              :: R8G8_UINT;
    OGA_FORMAT_R8G8_SINT              :: R8G8_SINT;
    OGA_FORMAT_R8G8_SRGB              :: R8G8_SRGB;

    OGA_FORMAT_R8G8B8_UNORM           :: R8G8B8_UNORM;
    OGA_FORMAT_R8G8B8_SNORM           :: R8G8B8_SNORM;
    OGA_FORMAT_R8G8B8_UINT            :: R8G8B8_UINT;
    OGA_FORMAT_R8G8B8_SINT            :: R8G8B8_SINT;
    OGA_FORMAT_R8G8B8_SRGB            :: R8G8B8_SRGB;

    OGA_FORMAT_R8G8B8A8_UNORM         :: R8G8B8A8_UNORM;
    OGA_FORMAT_R8G8B8A8_SNORM         :: R8G8B8A8_SNORM;
    OGA_FORMAT_R8G8B8A8_UINT          :: R8G8B8A8_UINT;
    OGA_FORMAT_R8G8B8A8_SINT          :: R8G8B8A8_SINT;
    OGA_FORMAT_R8G8B8A8_SRGB          :: R8G8B8A8_SRGB;

    OGA_FORMAT_B8G8R8A8_UNORM         :: B8G8R8A8_UNORM;
    OGA_FORMAT_B8G8R8A8_SNORM         :: B8G8R8A8_SNORM;
    OGA_FORMAT_B8G8R8A8_UINT          :: B8G8R8A8_UINT;
    OGA_FORMAT_B8G8R8A8_SINT          :: B8G8R8A8_SINT;
    OGA_FORMAT_B8G8R8A8_SRGB          :: B8G8R8A8_SRGB;

    OGA_FORMAT_R16_UNORM              :: R16_UNORM;
    OGA_FORMAT_R16_SNORM              :: R16_SNORM;
    OGA_FORMAT_R16_UINT               :: R16_UINT;
    OGA_FORMAT_R16_SINT               :: R16_SINT;
    OGA_FORMAT_R16_SFLOAT             :: R16_SFLOAT;

    OGA_FORMAT_R16G16_UNORM           :: R16G16_UNORM;
    OGA_FORMAT_R16G16_SNORM           :: R16G16_SNORM;
    OGA_FORMAT_R16G16_UINT            :: R16G16_UINT;
    OGA_FORMAT_R16G16_SINT            :: R16G16_SINT;
    OGA_FORMAT_R16G16_SFLOAT          :: R16G16_SFLOAT;

    OGA_FORMAT_R16G16B16A16_UNORM     :: R16G16B16A16_UNORM;
    OGA_FORMAT_R16G16B16A16_SNORM     :: R16G16B16A16_SNORM;
    OGA_FORMAT_R16G16B16A16_UINT      :: R16G16B16A16_UINT;
    OGA_FORMAT_R16G16B16A16_SINT      :: R16G16B16A16_SINT;
    OGA_FORMAT_R16G16B16A16_SFLOAT    :: R16G16B16A16_SFLOAT;

    OGA_FORMAT_R32_SFLOAT             :: R32_SFLOAT;
    OGA_FORMAT_R32_UINT               :: R32_UINT;
    OGA_FORMAT_R32_SINT               :: R32_SINT;

    OGA_FORMAT_R32G32_SFLOAT          :: R32G32_SFLOAT;
    OGA_FORMAT_R32G32_UINT            :: R32G32_UINT;
    OGA_FORMAT_R32G32_SINT            :: R32G32_SINT;

    OGA_FORMAT_R32G32B32_SFLOAT       :: R32G32B32_SFLOAT;
    OGA_FORMAT_R32G32B32_UINT         :: R32G32B32_UINT;
    OGA_FORMAT_R32G32B32_SINT         :: R32G32B32_SINT;

    OGA_FORMAT_R32G32B32A32_SFLOAT    :: R32G32B32A32_SFLOAT;
    OGA_FORMAT_R32G32B32A32_UINT      :: R32G32B32A32_UINT;
    OGA_FORMAT_R32G32B32A32_SINT      :: R32G32B32A32_SINT;

    OGA_FORMAT_DEPTH16_UNORM          :: DEPTH16_UNORM;
    OGA_FORMAT_DEPTH24_UNORM_S8_UINT  :: DEPTH24_UNORM_S8_UINT;
    OGA_FORMAT_DEPTH32_SFLOAT         :: DEPTH32_SFLOAT;
    OGA_FORMAT_DEPTH32_SFLOAT_S8_UINT :: DEPTH32_SFLOAT_S8_UINT;

    OGA_FORMAT_BC1_RGB_UNORM_BLOCK    :: BC1_RGB_UNORM_BLOCK;
    OGA_FORMAT_BC1_RGB_SRGB_BLOCK     :: BC1_RGB_SRGB_BLOCK;
    OGA_FORMAT_BC1_RGBA_UNORM_BLOCK   :: BC1_RGBA_UNORM_BLOCK;
    OGA_FORMAT_BC1_RGBA_SRGB_BLOCK    :: BC1_RGBA_SRGB_BLOCK;
    OGA_FORMAT_BC2_UNORM_BLOCK        :: BC2_UNORM_BLOCK;
    OGA_FORMAT_BC2_SRGB_BLOCK         :: BC2_SRGB_BLOCK;
    OGA_FORMAT_BC3_UNORM_BLOCK        :: BC3_UNORM_BLOCK;
    OGA_FORMAT_BC3_SRGB_BLOCK         :: BC3_SRGB_BLOCK;
    OGA_FORMAT_BC4_UNORM_BLOCK        :: BC4_UNORM_BLOCK;
    OGA_FORMAT_BC4_SNORM_BLOCK        :: BC4_SNORM_BLOCK;
    OGA_FORMAT_BC5_UNORM_BLOCK        :: BC5_UNORM_BLOCK;
    OGA_FORMAT_BC5_SNORM_BLOCK        :: BC5_SNORM_BLOCK;
    OGA_FORMAT_BC6H_UFLOAT_BLOCK      :: BC6H_UFLOAT_BLOCK;
    OGA_FORMAT_BC6H_SFLOAT_BLOCK      :: BC6H_SFLOAT_BLOCK;
    OGA_FORMAT_BC7_UNORM_BLOCK        :: BC7_UNORM_BLOCK;
    OGA_FORMAT_BC7_SRGB_BLOCK         :: BC7_SRGB_BLOCK;

    OGA_FORMAT_ENUM_MAX               :: ENUM_MAX;
}

Oga_Memory_Property_Flag_ :: enum s32 {
    LOCAL            :: 1;

    TO_CPU_MAPPABLE  :: 2;

    TO_CPU_REFLECTED :: 4;

    TO_CPU_CACHED    :: 8;

    OGA_MEMORY_PROPERTY_GPU_LOCAL            :: LOCAL;

    OGA_MEMORY_PROPERTY_GPU_TO_CPU_MAPPABLE  :: TO_CPU_MAPPABLE;

    OGA_MEMORY_PROPERTY_GPU_TO_CPU_REFLECTED :: TO_CPU_REFLECTED;

    OGA_MEMORY_PROPERTY_GPU_TO_CPU_CACHED    :: TO_CPU_CACHED;
}

Oga_Memory_Property_Flag :: u64;

Oga_Memory_Usage_ :: enum s32 {
    NONE                       :: 0;
    VERTEX_LIST                :: 4;
    INDEX_LIST                 :: 8;

    FAST_READONLY_DATA_BLOCK   :: 16;
    LARGE_READWRITE_DATA_BLOCK :: 32;
    COPY_DST                   :: 64;
    COPY_SRC                   :: 128;
    IMAGE_1D                   :: 256;
    IMAGE_2D                   :: 512;
    IMAGE_3D                   :: 1024;
    FBUFFER_1D                 :: 256;
    FBUFFER_2D                 :: 512;
    FBUFFER_3D                 :: 1024;

    OGA_MEMORY_USAGE_NONE                       :: NONE;
    OGA_MEMORY_USAGE_VERTEX_LIST                :: VERTEX_LIST;
    OGA_MEMORY_USAGE_INDEX_LIST                 :: INDEX_LIST;

    OGA_MEMORY_USAGE_FAST_READONLY_DATA_BLOCK   :: FAST_READONLY_DATA_BLOCK;
    OGA_MEMORY_USAGE_LARGE_READWRITE_DATA_BLOCK :: LARGE_READWRITE_DATA_BLOCK;
    OGA_MEMORY_USAGE_COPY_DST                   :: COPY_DST;
    OGA_MEMORY_USAGE_COPY_SRC                   :: COPY_SRC;
    OGA_MEMORY_USAGE_IMAGE_1D                   :: IMAGE_1D;
    OGA_MEMORY_USAGE_IMAGE_2D                   :: IMAGE_2D;
    OGA_MEMORY_USAGE_IMAGE_3D                   :: IMAGE_3D;
    OGA_MEMORY_USAGE_FBUFFER_1D                 :: FBUFFER_1D;
    OGA_MEMORY_USAGE_FBUFFER_2D                 :: FBUFFER_2D;
    OGA_MEMORY_USAGE_FBUFFER_3D                 :: FBUFFER_3D;
}

Oga_Memory_Usage :: u64;

// Unique identifer/handle for an instance of something.
// For example, if we need to know if two Oga_Device's are the same, we compare
// test them with a,id == b.id.
Oga_Id :: *void;

Oga_Sample_Count_Flag :: enum s32 {
    _1   :: 1;
    _2   :: 2;
    _4   :: 4;
    _8   :: 8;
    _16  :: 16;
    _32  :: 32;
    _64  :: 64;
    _128 :: 128;

    OGA_SAMPLE_COUNT_1   :: _1;
    OGA_SAMPLE_COUNT_2   :: _2;
    OGA_SAMPLE_COUNT_4   :: _4;
    OGA_SAMPLE_COUNT_8   :: _8;
    OGA_SAMPLE_COUNT_16  :: _16;
    OGA_SAMPLE_COUNT_32  :: _32;
    OGA_SAMPLE_COUNT_64  :: _64;
    OGA_SAMPLE_COUNT_128 :: _128;
}

//////
// Device
Oga_Logical_Engine_Family_Flags :: enum s32 {
    GRAPHICS :: 1;
    COMPUTE  :: 2;
    TRANSFER :: 4;
    PRESENT  :: 8;

    OGA_LOGICAL_ENGINE_GRAPHICS :: GRAPHICS;
    OGA_LOGICAL_ENGINE_COMPUTE  :: COMPUTE;
    OGA_LOGICAL_ENGINE_TRANSFER :: TRANSFER;
    OGA_LOGICAL_ENGINE_PRESENT  :: PRESENT;
}

Oga_Logical_Engine_Family_Info :: struct {
    flags:           Oga_Logical_Engine_Family_Flags;
    engine_capacity: u32;
}

Oga_Memory_Heap :: struct {
    properties:            Oga_Memory_Property_Flag;
    size:                  u64;
    supported_usage_flags: Oga_Memory_Usage;
}

Oga_Device_Kind :: enum s32 {
    DISCRETE   :: 0;
    INTEGRATED :: 1;
    CPU        :: 2;
    OTHER      :: 3;

    OGA_DEVICE_DISCRETE   :: DISCRETE;
    OGA_DEVICE_INTEGRATED :: INTEGRATED;
    OGA_DEVICE_CPU        :: CPU;
    OGA_DEVICE_OTHER      :: OTHER;
}

// todo(charlie) populate this with an exhaustive list.
Oga_Device_Limits :: struct {
    max_program_view_sets_per_stage:       u64;

    max_fast_data_blocks_per_stage:        u64;
    max_large_data_blocks_per_stage:       u64;
    max_images_per_stage:                  u64;
    max_fbuffers_per_stage:                u64;
    max_samplers_per_stage:                u64;

    max_fast_data_blocks_per_layout:       u64;
    max_large_data_blocks_per_layout:      u64;
    max_images_per_layout:                 u64;
    max_fbuffers_per_layout:               u64;
    max_samplers_per_layout:               u64;

    max_memory_allocations:                u64;
    max_sampler_allocations:               u64;

    max_image_dimension_1d:                u64;
    max_image_dimension_2d:                u64;
    max_image_dimension_3d:                u64;

    max_fast_access_data_block_size:       u64;

    max_vertex_layout_attributes:          u64;
    max_vertex_layout_bindings:            u64;
    max_vertex_layout_attribute_offset:    u64;
    max_vertex_layout_binding_stride:      u64;

    max_fragment_stage_output_attachments: u64;

    max_sampler_anisotropy:                _float32;

    max_viewports:                         u64;
    max_viewport_width:                    u64;
    max_viewport_height:                   u64;

    max_framebuffer_width:                 u64;
    max_framebuffer_height:                u64;

    max_render_attachments:                u64;

    min_memory_map_alignment:              u64;

    supported_sample_counts_render_pass:   Oga_Sample_Count_Flag;

    supported_sample_counts_image_float:   Oga_Sample_Count_Flag;
    supported_sample_counts_fbuffer_float: Oga_Sample_Count_Flag;
    supported_sample_counts_image_int:     Oga_Sample_Count_Flag;
    supported_sample_counts_fbuffer_int:   Oga_Sample_Count_Flag;

    memory_granularity:                    u64;
    image_memory_granularity:              u64;
    fbuffer_memory_granularity:            u64;
}

Oga_Device_Feature_Flag :: u64;

Oga_Device :: struct {
    id:                             *void;

    kind:                           Oga_Device_Kind;

    // string
    device_name_data:               [256] u8;
    device_name_length:             u64;

    vendor_id:                      u64;
    vendor_name:                    string;
    driver_version_raw:             u32;

    // string
    driver_version_data:            [128] u8;
    driver_version_length:          u64;

    api_version_raw:                u32;

    // string
    api_version_data:               [128] u8;
    api_version_length:             u64;

    limits:                         Oga_Device_Limits;

    engine_family_infos:            [32] Oga_Logical_Engine_Family_Info;
    engine_family_count:            u32;

    depth_format:                   Oga_Format;

    memory_heaps:                   [32] Oga_Memory_Heap;
    memory_heap_count:              u64;
    total_gpu_local_memory:         u64;

    features:                       Oga_Device_Feature_Flag;

    supported_surface_formats:      [79] Oga_Format;
    supported_surface_format_count: u64;
}

Oga_Device_Pick_Flag :: enum s32 {
    NONE               :: 0;
    PREFER_DISCRETE    :: 1;
    PREFER_INTEGRATED  :: 2;
    PREFER_CPU         :: 4;
    REQUIRE_DISCRETE   :: 8;
    REQUIRE_INTEGRATED :: 16;
    REQUIRE_CPU        :: 32;

    OGA_DEVICE_PICK_NONE               :: NONE;
    OGA_DEVICE_PICK_PREFER_DISCRETE    :: PREFER_DISCRETE;
    OGA_DEVICE_PICK_PREFER_INTEGRATED  :: PREFER_INTEGRATED;
    OGA_DEVICE_PICK_PREFER_CPU         :: PREFER_CPU;
    OGA_DEVICE_PICK_REQUIRE_DISCRETE   :: REQUIRE_DISCRETE;
    OGA_DEVICE_PICK_REQUIRE_INTEGRATED :: REQUIRE_INTEGRATED;
    OGA_DEVICE_PICK_REQUIRE_CPU        :: REQUIRE_CPU;
}

oga_query_devices :: (buffer: *Oga_Device, buffer_count: u64) -> u64 #foreign ostd_windows;
oga_get_devices :: (a: Allocator, count: *u64) -> *Oga_Device #foreign ostd_windows;

Oga_Pick_Device_Result :: struct {
    passed:                    bool;
    device:                    Oga_Device;
    failed_pick_flags:         Oga_Device_Pick_Flag;
    failed_required_features:  Oga_Device_Feature_Flag;
    failed_preferred_features: Oga_Device_Feature_Flag;
}

// todo(charlie) add consideration for heap properties and usage flags
oga_pick_device :: (pick_flags: Oga_Device_Pick_Flag, required_features: Oga_Device_Feature_Flag, preferred_features: Oga_Device_Feature_Flag) -> Oga_Pick_Device_Result #foreign ostd_windows;

//////////
/// Oga Context
Oga_Logical_Engines_Create_Desc :: struct {
    count:      u32;
    priorities: [32] _float32; // normalized 0.0-1.0.
}

// Default allocator of non is specified in Oga_Context_Desc::state_allocator
oga_state_allocator_proc :: (msg: Allocator_Message, data: *void, old: *void, old_n: u64, n: u64, alignment: u64, flags: u64) -> *void #foreign ostd_windows;

Oga_Allocator_Row :: struct {
    start:                   *void;
    end:                     *void;
    first_free_index:        u64;
    highest_allocated_index: u64;
}

Oga_State_Allocator_Data :: struct {
    // 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8196, 16384
    rows: [11] Oga_Allocator_Row;
}

Oga_Context_Desc :: struct {
    // Indices match to that of Oga_Device::engine_family_infos.
    // So the create engines of family 0, you set the desc in engine_create_descs[0].
    // Leave descs uninitialized to make no engines in that family.
    engine_create_descs: [32] Oga_Logical_Engines_Create_Desc;
    enabled_features:    Oga_Device_Feature_Flag;
    state_allocator:     Allocator; // The allocator used to allocate state & handles in this context. Will only be used when creating/destroying things.
}

// Some hardware expose their engines, some don't.
// So we deal with Logical Engines, which may or may not map directly to
// hardware engines.
// Equivalent to a vulkan Queue
Oga_Logical_Engine :: struct {
    id:    *void;
    index: u32;
}

Oga_Logical_Engine_Group :: struct {
    engines:      [32] Oga_Logical_Engine;
    engine_count: u64;
}

Oga_Context :: struct {
    id:                     *void;
    internal:               *void;
    device:                 Oga_Device;
    engines_by_family:      [32] Oga_Logical_Engine_Group;
    state_allocator:        Allocator;

    default_allocator_data: Oga_State_Allocator_Data; // Backing for Allocator::data
}

oga_init_context :: (target_device: Oga_Device, desc: Oga_Context_Desc, _context: **Oga_Context) -> Oga_Result #foreign ostd_windows;
oga_uninit_context :: (_context: *Oga_Context) -> void #foreign ostd_windows;

oga_wait_engine_idle :: (engine: Oga_Logical_Engine) -> void #foreign ostd_windows;
oga_wait_context_idle :: (_context: *Oga_Context) -> void #foreign ostd_windows;

//////////
/// Swap chain
Oga_Present_Mode :: enum s32 {
    VSYNC         :: 0;

    IMMEDIATE     :: 1;

    VSYNC_MAILBOX :: 2;

    OGA_PRESENT_MODE_VSYNC         :: VSYNC;

    OGA_PRESENT_MODE_IMMEDIATE     :: IMMEDIATE;

    OGA_PRESENT_MODE_VSYNC_MAILBOX :: VSYNC_MAILBOX;
}

Oga_Swapchain_Desc :: struct {
    surface:                      Surface_Handle;
    requested_image_count:        u64;
    image_format:                 Oga_Format;
    width:                        u64;
    height:                       u64;
    present_mode:                 Oga_Present_Mode;
    graphics_engine_family_index: u64; // Swapchain needs a graphics engine
}

Oga_Swapchain :: struct {
    id:                  *void;
    _context:            *Oga_Context;
    images:              [16] *Oga_Render_Image_View;
    current_image_index: u64;
    image_count:         u64;
    image_format:        Oga_Format;
}

get_preferred_swapchain_format :: (_context: *Oga_Context, wanted_formats: *Oga_Format, count: u64, format: *Oga_Format) -> bool #foreign ostd_windows;

oga_init_swapchain :: (_context: *Oga_Context, desc: Oga_Swapchain_Desc, swapchain: **Oga_Swapchain) -> Oga_Result #foreign ostd_windows;
oga_uninit_swapchain :: (swapchain: *Oga_Swapchain) -> void #foreign ostd_windows;

oga_get_next_swapchain_image :: (swapchain: *Oga_Swapchain, timeout: u64, signal_gpu_latch: *Oga_Gpu_Latch, signal_cpu_latch: *Oga_Cpu_Latch, image_index: *u64) -> Oga_Result #foreign ostd_windows;

Oga_Present_Desc :: struct {
    engine:               Oga_Logical_Engine;
    wait_gpu_latch_count: u64;
    wait_gpu_latches:     **Oga_Gpu_Latch;
    image_index:          u64;
}

oga_submit_present :: (swapchain: *Oga_Swapchain, desc: Oga_Present_Desc) -> Oga_Result #foreign ostd_windows;

//////////
/// GPU Programs
Oga_Program_Kind :: enum s32 {
    VERTEX   :: 0;
    FRAGMENT :: 1;
    COMPUTE  :: 2;

    OGA_PROGRAM_VERTEX   :: VERTEX;
    OGA_PROGRAM_FRAGMENT :: FRAGMENT;
    OGA_PROGRAM_COMPUTE  :: COMPUTE;
}

Oga_Program_Desc :: struct {
    code:      *void; // Compiled code ready to send to drivers
    code_size: u64;
    kind:      Oga_Program_Kind;
}

Oga_Program :: struct {
    id:       *void;
    _context: *Oga_Context;
    kind:     Oga_Program_Kind;
}

// Goes through OSL to compile osl lang to target drivers
// Oga_Result oga_compile_program_for_target
oga_init_program :: (_context: *Oga_Context, desc: Oga_Program_Desc, program: **Oga_Program) -> Oga_Result #foreign ostd_windows;
oga_uninit_program :: (program: *Oga_Program) -> void #foreign ostd_windows;

//////////
/// Render Passes
Oga_Program_Stage_Flag_ :: enum s32 {
    VERTEX   :: 2;
    FRAGMENT :: 4;
    COMPUTE  :: 8;

    OGA_PROGRAM_STAGE_VERTEX   :: VERTEX;
    OGA_PROGRAM_STAGE_FRAGMENT :: FRAGMENT;
    OGA_PROGRAM_STAGE_COMPUTE  :: COMPUTE;
}

Oga_Program_Stage_Flag :: u64;

Oga_Sampling_Filter :: enum s32 {
    LINEAR  :: 0;
    NEAREST :: 1;

    OGA_SAMPLE_FILTER_LINEAR  :: LINEAR;
    OGA_SAMPLE_FILTER_NEAREST :: NEAREST;
}

Oga_Sampling_Address_Mode :: enum s32 {
    REPEAT          :: 0;
    MIRRORED_REPEAT :: 1;
    CLAMP_TO_EDGE   :: 2;
    CLAMP_TO_BORDER :: 3;

    OGA_SAMPLE_ADDRESS_MODE_REPEAT          :: REPEAT;
    OGA_SAMPLE_ADDRESS_MODE_MIRRORED_REPEAT :: MIRRORED_REPEAT;
    OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_EDGE   :: CLAMP_TO_EDGE;
    OGA_SAMPLE_ADDRESS_MODE_CLAMP_TO_BORDER :: CLAMP_TO_BORDER;
}

Oga_Sample_Mode_Desc :: struct {
    magnification_filter: Oga_Sampling_Filter;
    minification_filter:  Oga_Sampling_Filter;
    address_mode_u:       Oga_Sampling_Address_Mode;
    address_mode_v:       Oga_Sampling_Address_Mode;
    address_mode_w:       Oga_Sampling_Address_Mode;
    max_anisotropy:       float;
}

Oga_Binding_Kind :: enum s32 {
    IMAGE       :: 0;
    SAMPLE_MODE :: 1;
    BLOCK       :: 2;
    FBUFFER     :: 3;

    ENUM_MAX    :: 4;

    OGA_BINDING_IMAGE       :: IMAGE;
    OGA_BINDING_SAMPLE_MODE :: SAMPLE_MODE;
    OGA_BINDING_BLOCK       :: BLOCK;
    OGA_BINDING_FBUFFER     :: FBUFFER;

    OGA_BINDING_ENUM_MAX    :: ENUM_MAX;
}

Oga_Binding_Layout_Entry_Desc :: struct {
    kind:          Oga_Binding_Kind;
    binding_slot:  u64;
    binding_count: u64; // Number of elements in this binding. If > 1, the program declaration should be an array
    stage_flags:   Oga_Program_Stage_Flag;
}

Oga_Binding_List_Layout_Desc :: struct {
    bindings:           *Oga_Binding_Layout_Entry_Desc;
    binding_count:      u64;
    binding_list_count: u64;
}

Oga_Binding_List_Layout :: struct {
    id:                    *void;
    _context:              *Oga_Context;
    bindings:              *Oga_Binding_Layout_Entry_Desc;
    binding_count:         u64;
    binding_list_count:    u64;
    allocated_lists_count: u64;
}

oga_init_binding_list_layout :: (_context: *Oga_Context, desc: Oga_Binding_List_Layout_Desc, layout: **Oga_Binding_List_Layout) -> Oga_Result #foreign ostd_windows;
oga_uninit_binding_list_layout :: (layout: *Oga_Binding_List_Layout) -> void #foreign ostd_windows;

Oga_Binding_Desc :: struct {
    kind:         Oga_Binding_Kind;
    binding_slot: u64;
    array_index:  u64;
    count:        u64;

    // OGA_BINDING_IMAGE
    images:       **Oga_Image_View;

    // OGA_BINDING_SAMPLE_MODE
    sample_modes: *Oga_Sample_Mode_Desc;

    // OGA_BINDING_BLOCK
    blocks:       **Oga_Block_View;

    // OGA_BINDING_FBUFFER
    fbuffers:     **Oga_FBuffer_View;
}

Oga_Binding_List_Desc :: struct {
    bindings:      *Oga_Binding_Desc;
    binding_count: u64;
}

Oga_Binding_List :: struct {
    id:       *void;
    _context: *Oga_Context;
    layout:   *Oga_Binding_List_Layout;
}

oga_push_binding_list :: (layout: *Oga_Binding_List_Layout, desc: Oga_Binding_List_Desc, list: **Oga_Binding_List) -> Oga_Result #foreign ostd_windows;

Oga_Vertex_List_Input_Rate :: enum s32 {
    VERTEX   :: 0;
    INSTANCE :: 1;

    OGA_VERTEX_INPUT_RATE_VERTEX   :: VERTEX;
    OGA_VERTEX_INPUT_RATE_INSTANCE :: INSTANCE;
}

Oga_Vertex_Attribute_Type :: enum s32 {
    F32             :: 0;
    F32V2           :: 1;
    F32V3           :: 2;
    F32V4           :: 3;
    S32             :: 4;
    S32V2           :: 5;
    S32V3           :: 6;
    S32V4           :: 7;
    S16             :: 8;
    S16V2           :: 9;
    S16V3           :: 10;
    S16V4           :: 11;
    S8              :: 12;
    S8V2            :: 13;
    S8V3            :: 14;
    S8V4            :: 15;
    U32             :: 16;
    U32V2           :: 17;
    U32V3           :: 18;
    U32V4           :: 19;
    U16             :: 20;
    U16V2           :: 21;
    U16V3           :: 22;
    U16V4           :: 23;
    U8              :: 24;
    U8V2            :: 25;
    U8V3            :: 26;
    U8V4            :: 27;
    U8_NORMALIZED   :: 28;
    U8V2_NORMALIZED :: 29;
    U8V3_NORMALIZED :: 30;
    U8V4_NORMALIZED :: 31;

    OGA_VERTEX_ATTRIBUTE_TYPE_F32             :: F32;
    OGA_VERTEX_ATTRIBUTE_TYPE_F32V2           :: F32V2;
    OGA_VERTEX_ATTRIBUTE_TYPE_F32V3           :: F32V3;
    OGA_VERTEX_ATTRIBUTE_TYPE_F32V4           :: F32V4;
    OGA_VERTEX_ATTRIBUTE_TYPE_S32             :: S32;
    OGA_VERTEX_ATTRIBUTE_TYPE_S32V2           :: S32V2;
    OGA_VERTEX_ATTRIBUTE_TYPE_S32V3           :: S32V3;
    OGA_VERTEX_ATTRIBUTE_TYPE_S32V4           :: S32V4;
    OGA_VERTEX_ATTRIBUTE_TYPE_S16             :: S16;
    OGA_VERTEX_ATTRIBUTE_TYPE_S16V2           :: S16V2;
    OGA_VERTEX_ATTRIBUTE_TYPE_S16V3           :: S16V3;
    OGA_VERTEX_ATTRIBUTE_TYPE_S16V4           :: S16V4;
    OGA_VERTEX_ATTRIBUTE_TYPE_S8              :: S8;
    OGA_VERTEX_ATTRIBUTE_TYPE_S8V2            :: S8V2;
    OGA_VERTEX_ATTRIBUTE_TYPE_S8V3            :: S8V3;
    OGA_VERTEX_ATTRIBUTE_TYPE_S8V4            :: S8V4;
    OGA_VERTEX_ATTRIBUTE_TYPE_U32             :: U32;
    OGA_VERTEX_ATTRIBUTE_TYPE_U32V2           :: U32V2;
    OGA_VERTEX_ATTRIBUTE_TYPE_U32V3           :: U32V3;
    OGA_VERTEX_ATTRIBUTE_TYPE_U32V4           :: U32V4;
    OGA_VERTEX_ATTRIBUTE_TYPE_U16             :: U16;
    OGA_VERTEX_ATTRIBUTE_TYPE_U16V2           :: U16V2;
    OGA_VERTEX_ATTRIBUTE_TYPE_U16V3           :: U16V3;
    OGA_VERTEX_ATTRIBUTE_TYPE_U16V4           :: U16V4;
    OGA_VERTEX_ATTRIBUTE_TYPE_U8              :: U8;
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V2            :: U8V2;
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V3            :: U8V3;
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V4            :: U8V4;
    OGA_VERTEX_ATTRIBUTE_TYPE_U8_NORMALIZED   :: U8_NORMALIZED;
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V2_NORMALIZED :: U8V2_NORMALIZED;
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V3_NORMALIZED :: U8V3_NORMALIZED;
    OGA_VERTEX_ATTRIBUTE_TYPE_U8V4_NORMALIZED :: U8V4_NORMALIZED;
}

/*
We often only need one vertex list in one binding slot:

Oga_Vertex_List_Layout_Desc desc = (Oga_Vertex_List_Layout_Desc) {0};
desc.bindings[0].stride = sizeof(float4)+sizeof(float3);
desc.bindings[0].input_rate = OGA_VERTEX_INPUT_RATE_VERTEX;
desc.binding_count = 1;

desc.attributes[desc.attribute_count].binding = 0;
desc.attributes[desc.attribute_count].location = 0;
desc.attributes[desc.attribute_count].offset = 0;
desc.attributes[desc.attribute_count].type = OGA_VERTEX_ATTRIBUTE_TYPE_F32V4;
desc.attribute_count += 1;

desc.attributes[desc.attribute_count].binding = 0;
desc.attributes[desc.attribute_count].location = 1;
desc.attributes[desc.attribute_count].offset = sizeof(float4);
desc.attributes[desc.attribute_count].type = OGA_VERTEX_ATTRIBUTE_TYPE_F32V3;
desc.attribute_count += 1;
*/
Oga_Vertex_List_Binding_Desc :: struct {
    stride:     u64; // The stride between the start of each vertex in the vertex list in this binding slot
    input_rate: Oga_Vertex_List_Input_Rate; // Input is per vertex or per instance
}

Oga_Vertex_List_Attribute_Desc :: struct {
    binding:  u64; // The attribute points to the vertex list in this binding slot
    location: u64; // The attribute is bound to this location in the program input
    offset:   u64;
    type:     Oga_Vertex_Attribute_Type;
}

Oga_Vertex_List_Layout_Desc :: struct {
    bindings:        [32] Oga_Vertex_List_Binding_Desc; // Vertex list binding slots
    binding_count:   u64;
    attributes:      [32] Oga_Vertex_List_Attribute_Desc;
    attribute_count: u64;
}

Oga_Render_Pass_Flag :: u64;
OGA_RENDER_PASS_INHERITANCE_PARENT: Oga_Render_Pass_Flag : 1 << 0;
OGA_RENDER_PASS_INHERITANCE_CHILD: Oga_Render_Pass_Flag : 1 << 1;
OGA_RENDER_PASS_DISABLE_DEPTH_CLAMP: Oga_Render_Pass_Flag : 1 << 2;

// #Volatile values must map to same as vulkan equivalents
Oga_Primitive_Topology :: enum s32 {
    POINT_LIST     :: 0;
    LINE_LIST      :: 1;
    LINE_STRIP     :: 2;
    TRIANGLE_LIST  :: 3;
    TRIANGLE_STRIP :: 4;

    OGA_PRIMITIVE_TOPOLOGY_POINT_LIST     :: POINT_LIST;
    OGA_PRIMITIVE_TOPOLOGY_LINE_LIST      :: LINE_LIST;
    OGA_PRIMITIVE_TOPOLOGY_LINE_STRIP     :: LINE_STRIP;
    OGA_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST  :: TRIANGLE_LIST;
    OGA_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP :: TRIANGLE_STRIP;
}

Oga_Cull_Mode :: enum s32 {
    NONE              :: 0;
    CLOCKWISE         :: 1;
    COUNTER_CLOCKWISE :: 2;

    OGA_CULL_NONE              :: NONE;
    OGA_CULL_CLOCKWISE         :: CLOCKWISE;
    OGA_CULL_COUNTER_CLOCKWISE :: COUNTER_CLOCKWISE;
}

Oga_Render_Pass_Desc :: struct {
    flags:                        Oga_Render_Pass_Flag;
    base:                         *Oga_Render_Pass;
    base_index:                   u64; // Index into buffer of descs passed. Only used if base is null.

    vertex_program:               *Oga_Program;
    vertex_program_entry_point:   string;
    fragment_program:             *Oga_Program;
    fragment_program_entry_point: string;

    attachment_formats:           *Oga_Format;
    attachment_count:             u64;

    topology:                     Oga_Primitive_Topology;

    cull_mode:                    Oga_Cull_Mode;

    line_width:                   _float32;

    // See Oga_Device::limits.supported_sample_counts_render_pass
    rasterization_samples:        Oga_Sample_Count_Flag;

    vertex_input_layout:          Oga_Vertex_List_Layout_Desc;

    binding_list_layout:          *Oga_Binding_List_Layout;
}

Oga_Render_Pass :: struct {
    id:                  *void;
    _context:            *Oga_Context;
    vertex_input_layout: Oga_Vertex_List_Layout_Desc;
}

oga_init_render_passes :: (_context: *Oga_Context, descs: *Oga_Render_Pass_Desc, render_passes: **Oga_Render_Pass, render_pass_count: u64) -> Oga_Result #foreign ostd_windows;

oga_init_render_pass :: (_context: *Oga_Context, desc: Oga_Render_Pass_Desc, render_pass: **Oga_Render_Pass) -> Oga_Result #foreign ostd_windows;
oga_uninit_render_pass :: (render_pass: *Oga_Render_Pass) -> void #foreign ostd_windows;

// Gpu latch; for synchronizing on gpu. Signalled on gpu, waited on gpu.
Oga_Gpu_Latch :: struct {
    id:       *void;
    _context: *Oga_Context;
}

oga_init_gpu_latch :: (_context: *Oga_Context, gpu_latch: **Oga_Gpu_Latch) -> Oga_Result #foreign ostd_windows;
oga_uninit_gpu_latch :: (gpu_latch: *Oga_Gpu_Latch) -> void #foreign ostd_windows;

// Cpu latch; for synchronizing cpu with gpu. Signalled on gpu, waited on cpu.
Oga_Cpu_Latch :: struct {
    id:       *void;
    _context: *Oga_Context;
}

oga_init_cpu_latch :: (_context: *Oga_Context, cpu_latch: **Oga_Cpu_Latch, start_signaled: bool) -> Oga_Result #foreign ostd_windows;
oga_uninit_cpu_latch :: (cpu_latch: *Oga_Cpu_Latch) -> void #foreign ostd_windows;
oga_wait_latch :: (cpu_latch: *Oga_Cpu_Latch) -> Oga_Result #foreign ostd_windows;
oga_reset_latch :: (cpu_latch: *Oga_Cpu_Latch) -> Oga_Result #foreign ostd_windows;

Oga_Memory_Pointer :: struct {
    id:         *void;
    _context:   *Oga_Context;
    offset:     u64;
    size:       u64;
    heap_index: u64;
    properties: Oga_Memory_Property_Flag;
    usage:      Oga_Memory_Usage;
}

oga_allocate_memory :: (_context: *Oga_Context, size: u64, properties: Oga_Memory_Property_Flag, usage: Oga_Memory_Usage, ptr: *Oga_Memory_Pointer) -> Oga_Result #foreign ostd_windows;
oga_deallocate_memory :: (ptr: Oga_Memory_Pointer) -> void #foreign ostd_windows;
oga_map_memory :: (ptr: Oga_Memory_Pointer, size: u64, mapped_mem: **void) -> Oga_Result #foreign ostd_windows;
oga_unmap_memory :: (ptr: Oga_Memory_Pointer) -> void #foreign ostd_windows;
oga_memory_offset :: (ptr: Oga_Memory_Pointer, offset: s64, result_ptr: *Oga_Memory_Pointer) -> Oga_Result #foreign ostd_windows;

Oga_Memory_View_Desc :: struct {
    memory_pointer: Oga_Memory_Pointer;
    size:           u64;
}

// These are the same (as of now) but we have a compiler and a statically typechecked programming language,
// which we should use.
Oga_Vertex_List_View :: struct {
    id:             *void;
    _context:       *Oga_Context;
    memory_pointer: Oga_Memory_Pointer;
    size:           u64;
}

Oga_Index_List_View :: struct {
    id:             *void;
    _context:       *Oga_Context;
    memory_pointer: Oga_Memory_Pointer;
    size:           u64;
}

oga_init_vertex_list_view :: (_context: *Oga_Context, desc: Oga_Memory_View_Desc, vlist: **Oga_Vertex_List_View) -> Oga_Result #foreign ostd_windows;
oga_uninit_vertex_list_view :: (vlist: *Oga_Vertex_List_View) -> void #foreign ostd_windows;

oga_init_index_list_view :: (_context: *Oga_Context, desc: Oga_Memory_View_Desc, ilist: **Oga_Index_List_View) -> Oga_Result #foreign ostd_windows;
oga_uninit_index_list_view :: (ilist: *Oga_Index_List_View) -> void #foreign ostd_windows;

/// Image view
Oga_Dimensions :: enum s32 {
    _1D :: 0;
    _2D :: 1;
    _3D :: 2;

    OGA_1D :: _1D;
    OGA_2D :: _2D;
    OGA_3D :: _3D;
}

Oga_Image_View_Desc :: struct {
    memory_pointer:               Oga_Memory_Pointer;
    format:                       Oga_Format;
    dimensions:                   Oga_Dimensions;
    width:                        u64;
    height:                       u64;
    depth:                        u64;
    linear_tiling:                bool;
    graphics_engine_family_index: u64;
}

Oga_Image_View :: struct {
    id:             *void;
    _context:       *Oga_Context;
    memory_pointer: Oga_Memory_Pointer;
    width:          u64;
    height:         u64;
    depth:          u64;
    dimensions:     Oga_Dimensions;
    linear_tiling:  bool;
}

oga_init_image_view :: (_context: *Oga_Context, desc: Oga_Image_View_Desc, image: **Oga_Image_View) -> Oga_Result #foreign ostd_windows;
oga_uninit_image_view :: (image: *Oga_Image_View) -> void #foreign ostd_windows;

oga_get_image_memory_requirement :: (_context: *Oga_Context, desc: Oga_Image_View_Desc) -> u64 #foreign ostd_windows;

Oga_FBuffer_View :: struct {
    id:             *void;
    _context:       *Oga_Context;
    memory_pointer: Oga_Memory_Pointer;
    width:          u64;
    height:         u64;
    depth:          u64;
    dimensions:     Oga_Dimensions;
    linear_tiling:  bool;
}

oga_init_fbuffer_view :: (_context: *Oga_Context, desc: Oga_Image_View_Desc, fbuffer: **Oga_FBuffer_View) -> Oga_Result #foreign ostd_windows;
oga_uninit_fbuffer_view :: (fbuffer: *Oga_FBuffer_View) -> void #foreign ostd_windows;

/// Image copy target view
Oga_Optimal_Copy_Flag_ :: enum s32 {
    DST :: 2;
    SRC :: 4;

    OGA_OPTIMAL_COPY_DST :: DST;
    OGA_OPTIMAL_COPY_SRC :: SRC;
}

Oga_Optimal_Copy_Flag :: u64;

Oga_Optimal_Copy_View_Desc :: struct {
    memory_pointer:               Oga_Memory_Pointer;
    format:                       Oga_Format;
    dimensions:                   Oga_Dimensions;
    width:                        u64;
    height:                       u64;
    depth:                        u64;
    linear_tiling:                bool;
    graphics_engine_family_index: u64;
    flags:                        Oga_Optimal_Copy_Flag;
}

Oga_Optimal_Copy_View :: struct {
    id:             *void;
    _context:       *Oga_Context;
    memory_pointer: Oga_Memory_Pointer;
    width:          u64;
    height:         u64;
    depth:          u64;
    dimensions:     Oga_Dimensions;
    linear_tiling:  bool;
    flags:          Oga_Optimal_Copy_Flag;
}

oga_init_optimal_copy_view :: (_context: *Oga_Context, desc: Oga_Optimal_Copy_View_Desc, image: **Oga_Optimal_Copy_View) -> Oga_Result #foreign ostd_windows;
oga_uninit_optimal_copy_view :: (image: *Oga_Optimal_Copy_View) -> void #foreign ostd_windows;

Oga_Render_Image_View_Desc :: struct {
    memory_pointer: Oga_Memory_Pointer;
    format:         Oga_Format;
    width:          u64;
    height:         u64;
}

Oga_Render_Image_View :: struct {
    id:             *void;
    _context:       *Oga_Context;
    memory_pointer: Oga_Memory_Pointer;
    width:          u64;
    height:         u64;
}

/// Read buffer view
Oga_Block_View :: struct {
    id:             *void;
    _context:       *Oga_Context;
    memory_pointer: Oga_Memory_Pointer;
    size:           u64;
}

oga_init_block_view :: (_context: *Oga_Context, desc: Oga_Memory_View_Desc, buffer: **Oga_Block_View) -> Oga_Result #foreign ostd_windows;
oga_uninit_block_view :: (buffer: *Oga_Block_View) -> void #foreign ostd_windows;

// todo(charlie) #validation
// Keep track of all init()'s and report them here if they were not uninitted
// This is really only here to get validation/debug layer messages for leaked resources
oga_reset :: () -> void #foreign ostd_windows;

//////////
/// Commands
Oga_Command_Pool_Flag :: u64;

Oga_Command_Pool_Desc :: struct {
    flags:               Oga_Command_Pool_Flag;
    engine_family_index: u64; // Pinky promise which queue family this will be submitted to
}

Oga_Command_Pool :: struct {
    id:       *void;
    _context: *Oga_Context;
}

Oga_Command_List :: struct {
    id:   *void;
    pool: *Oga_Command_Pool;
}

oga_init_command_pool :: (_context: *Oga_Context, desc: Oga_Command_Pool_Desc, pool: **Oga_Command_Pool) -> Oga_Result #foreign ostd_windows;

// This will free all command lists, so you do not need to explicitly free each command list.
oga_uninit_command_pool :: (pool: *Oga_Command_Pool) -> void #foreign ostd_windows;
oga_reset_command_pool :: (pool: *Oga_Command_Pool) -> void #foreign ostd_windows;

oga_get_command_lists :: (pool: *Oga_Command_Pool, lists: *Oga_Command_List, list_count: u64) -> Oga_Result #foreign ostd_windows;
oga_release_command_lists :: (lists: *Oga_Command_List, list_count: u64) -> void #foreign ostd_windows;

Oga_Command_List_Usage_Flag :: u64;

oga_cmd_begin :: (cmd: Oga_Command_List, flags: Oga_Command_List_Usage_Flag) -> Oga_Result #foreign ostd_windows;
oga_cmd_end :: (cmd: Oga_Command_List) -> Oga_Result #foreign ostd_windows;

Oga_Submit_Command_List_Desc :: struct {
    engine:                 Oga_Logical_Engine;
    wait_gpu_latches:       **Oga_Gpu_Latch;
    wait_gpu_latch_count:   u64;
    signal_gpu_latches:     **Oga_Gpu_Latch;
    signal_gpu_latch_count: u64;
    signal_cpu_latch:       *Oga_Cpu_Latch;
}

oga_submit_command_list :: (cmd: Oga_Command_List, desc: Oga_Submit_Command_List_Desc) -> Oga_Result #foreign ostd_windows;

Oga_Gpu_Timestamp_Pool :: struct {
    id:                      *void;
    _context:                *Oga_Context;
    timestamp_count:         u64;
    written_timestamp_count: u64;
}

oga_init_gpu_timestamp_pool :: (_context: *Oga_Context, timestamp_count: u64, pool: **Oga_Gpu_Timestamp_Pool) -> Oga_Result #foreign ostd_windows;
oga_uninit_gpu_timestamp_pool :: (pool: *Oga_Gpu_Timestamp_Pool) -> void #foreign ostd_windows;

oga_cmd_reset_timestamp_pool :: (cmd: Oga_Command_List, pool: *Oga_Gpu_Timestamp_Pool) -> void #foreign ostd_windows;
oga_cmd_write_timestamp :: (cmd: Oga_Command_List, pool: *Oga_Gpu_Timestamp_Pool) -> void #foreign ostd_windows;

oga_read_timestamps :: (pool: *Oga_Gpu_Timestamp_Pool, nanosecond_timestamps: *f64, wait: bool) -> Oga_Result #foreign ostd_windows;

Oga_Msaa_Resolve_Mode_Flag :: u64;

Oga_Attachment_Load_Op :: enum s32 {
    LOAD    :: 0;
    CLEAR   :: 1;
    NOTHING :: 2;

    OGA_ATTACHMENT_LOAD_OP_LOAD    :: LOAD;
    OGA_ATTACHMENT_LOAD_OP_CLEAR   :: CLEAR;
    OGA_ATTACHMENT_LOAD_OP_NOTHING :: NOTHING;
}

Oga_Attachment_Store_Op :: enum s32 {
    STORE   :: 0;
    NOTHING :: 1;

    OGA_ATTACHMENT_STORE_OP_STORE   :: STORE;
    OGA_ATTACHMENT_STORE_OP_NOTHING :: NOTHING;
}

Oga_Render_Attachment_Desc :: struct {
    image:         *Oga_Render_Image_View;

    // If rendering with multisampling, we can resolve the multiple samples into single samples
    // on another image.
    resolve_mode:  Oga_Msaa_Resolve_Mode_Flag;
    resolve_image: *Oga_Image_View;

    load_op:       Oga_Attachment_Load_Op;
    store_op:      Oga_Attachment_Store_Op;

    clear_color:   [4] _float32; // In case of load_op CLEAR
}

Oga_Begin_Render_Pass_Desc :: struct {
    render_area_offset_x: s64;
    render_area_offset_y: s64;
    render_area_width:    u64;
    render_area_height:   u64;
    attachment_count:     u64;
    attachments:          *Oga_Render_Attachment_Desc;
}

oga_cmd_begin_render_pass :: (cmd: Oga_Command_List, render_pass: *Oga_Render_Pass, desc: Oga_Begin_Render_Pass_Desc) -> void #foreign ostd_windows;
oga_cmd_end_render_pass :: (cmd: Oga_Command_List, render_pass: *Oga_Render_Pass) -> void #foreign ostd_windows;

oga_cmd_bind_render_pass_binding_list :: (cmd: Oga_Command_List, pass: *Oga_Render_Pass, list: *Oga_Binding_List) -> void #foreign ostd_windows;

Oga_Draw_Type :: enum s32 {
    INSTANCED                              :: 0;
    VERTEX_LIST                            :: 1;
    VERTEX_LIST_INSTANCED                  :: 2;
    VERTEX_LIST_INDEXED                    :: 3;
    VERTEX_LIST_INSTANCED_INDEXED          :: 4;

    INSTANCED_INDIRECT                     :: 5;
    VERTEX_LIST_INDIRECT                   :: 6;
    VERTEX_LIST_INSTANCED_INDIRECT         :: 7;
    VERTEX_LIST_INDEXED_INDIRECT           :: 8;
    VERTEX_LIST_INSTANCED_INDEXED_INDIRECT :: 9;

    OGA_DRAW_INSTANCED                              :: INSTANCED;
    OGA_DRAW_VERTEX_LIST                            :: VERTEX_LIST;
    OGA_DRAW_VERTEX_LIST_INSTANCED                  :: VERTEX_LIST_INSTANCED;
    OGA_DRAW_VERTEX_LIST_INDEXED                    :: VERTEX_LIST_INDEXED;
    OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED          :: VERTEX_LIST_INSTANCED_INDEXED;

    OGA_DRAW_INSTANCED_INDIRECT                     :: INSTANCED_INDIRECT;
    OGA_DRAW_VERTEX_LIST_INDIRECT                   :: VERTEX_LIST_INDIRECT;
    OGA_DRAW_VERTEX_LIST_INSTANCED_INDIRECT         :: VERTEX_LIST_INSTANCED_INDIRECT;
    OGA_DRAW_VERTEX_LIST_INDEXED_INDIRECT           :: VERTEX_LIST_INDEXED_INDIRECT;
    OGA_DRAW_VERTEX_LIST_INSTANCED_INDEXED_INDIRECT :: VERTEX_LIST_INSTANCED_INDEXED_INDIRECT;
}

Oga_Index_Type :: enum s32 {
    U32 :: 0;
    U16 :: 1;

    OGA_INDEX_U32 :: U32;
    OGA_INDEX_U16 :: U16;
}

Oga_Draw_Desc :: struct {
    draw_type:                 Oga_Draw_Type;

    vertex_start:              u64; // The first vertex to draw. For vertex lists, this is an offset from the BASE vertex at the binding point
    vertex_count:              u64;

    // Vertex list
    vertex_list_bindings:      [32] *Oga_Vertex_List_View;
    vertex_list_offsets:       [32] u64; // Offset to the BASE vertex to be bound
    vertex_list_binding_count: u64;

    // Instanced
    instance_start:            u64;
    instance_count:            u64;

    // Indexed
    index_start:               u64;
    index_count:               u64;
    index_list:                *Oga_Index_List_View;
    index_list_offset:         u64;
    index_type:                Oga_Index_Type;
}

oga_cmd_draw :: (cmd: Oga_Command_List, desc: Oga_Draw_Desc) -> Oga_Result #foreign ostd_windows;

oga_cmd_copy_linear :: (cmd: Oga_Command_List, dst: Oga_Memory_Pointer, src: Oga_Memory_Pointer, size: u64) -> void #foreign ostd_windows;

Oga_Optimal_Copy_Desc :: struct {
    offset_x: s64;
    offset_y: s64;
    offset_z: s64;
    width:    u64;
    height:   u64;
    depth:    u64;
}

oga_cmd_copy_linear_to_image :: (cmd: Oga_Command_List, dst_view: *Oga_Optimal_Copy_View, dst_desc: Oga_Optimal_Copy_Desc, src: Oga_Memory_Pointer) -> void #foreign ostd_windows;
oga_cmd_copy_image_to_linear :: (cmd: Oga_Command_List, dst: Oga_Memory_Pointer, src_view: *Oga_Optimal_Copy_View, src_desc: Oga_Optimal_Copy_Desc) -> void #foreign ostd_windows;
oga_cmd_copy_image :: (cmd: Oga_Command_List, dst_view: *Oga_Optimal_Copy_View, dst_desc: Oga_Optimal_Copy_Desc, src_view: *Oga_Optimal_Copy_View, src_desc: Oga_Optimal_Copy_Desc) -> void #foreign ostd_windows;

oga_cmd_fill_image :: (cmd: Oga_Command_List, dst_view: *Oga_Optimal_Copy_View, color: float4) -> void #foreign ostd_windows;

Osl_Result :: enum s32 {
    OK                                           :: 0;
    UNRESOLVED_TYPE                              :: 1;
    UNEXPECTED_TOKEN                             :: 2;
    BAD_OPERATOR                                 :: 3;
    ASSIGN_NON_STORAGE_VALUE                     :: 4;
    UNDEFINED_VALUE                              :: 5;
    BAD_VECTOR_INSTANTIATE                       :: 6;
    BAD_INSTANTIATION_ARGUMENT                   :: 7;
    BAD_DEREF                                    :: 8;
    BAD_DECORATION_ARGUMENTS                     :: 9;
    BAD_DECL_CLASS                               :: 10;
    EXCEED_MAX_TYPE_INDIRECTIONS                 :: 11;
    NOT_AN_EXPR                                  :: 12;
    NON_INT_INDEX                                :: 13;
    CANNOT_CONVERT_TYPES                         :: 14;
    INVALID_SUBSCRIPT                            :: 15;
    INVALID_SWIZZLE                              :: 16;
    SWIZZLE_USED_AS_STORAGE                      :: 17;
    INVALID_CAST                                 :: 18;
    VALUE_NAME_REDIFINITION                      :: 19;
    UNRESOLVED_FUNCTION_OR_INTRINSIC             :: 20;
    BAD_CALL_ARGUMENTS                           :: 21;
    NOT_A_LOGICAL_TYPE                           :: 22;
    PROCEDURAL_STATEMENT_IN_NON_PROCEDURAL_BLOCK :: 23;
    TYPE_REDEFINITION                            :: 24;
    NO_SUCH_MEMBER                               :: 25;
    VIEW_INSTANTIATION                           :: 26;
    VIEW_CAST                                    :: 27;
    BLOCK_TYPE_IS_NOT_STRUCT                     :: 28;
    FEATURE_NOT_ENABLED                          :: 29;
    UNSIZED_ARRAY_NOT_AT_END_OF_STRUCT           :: 30;
    INVALID_FBUFFER_VIEW                         :: 31;
    UNIMPLEMENTED                                :: 32;

    OSL_OK                                           :: OK;
    OSL_UNRESOLVED_TYPE                              :: UNRESOLVED_TYPE;
    OSL_UNEXPECTED_TOKEN                             :: UNEXPECTED_TOKEN;
    OSL_BAD_OPERATOR                                 :: BAD_OPERATOR;
    OSL_ASSIGN_NON_STORAGE_VALUE                     :: ASSIGN_NON_STORAGE_VALUE;
    OSL_UNDEFINED_VALUE                              :: UNDEFINED_VALUE;
    OSL_BAD_VECTOR_INSTANTIATE                       :: BAD_VECTOR_INSTANTIATE;
    OSL_BAD_INSTANTIATION_ARGUMENT                   :: BAD_INSTANTIATION_ARGUMENT;
    OSL_BAD_DEREF                                    :: BAD_DEREF;
    OSL_BAD_DECORATION_ARGUMENTS                     :: BAD_DECORATION_ARGUMENTS;
    OSL_BAD_DECL_CLASS                               :: BAD_DECL_CLASS;
    OSL_EXCEED_MAX_TYPE_INDIRECTIONS                 :: EXCEED_MAX_TYPE_INDIRECTIONS;
    OSL_NOT_AN_EXPR                                  :: NOT_AN_EXPR;
    OSL_NON_INT_INDEX                                :: NON_INT_INDEX;
    OSL_CANNOT_CONVERT_TYPES                         :: CANNOT_CONVERT_TYPES;
    OSL_INVALID_SUBSCRIPT                            :: INVALID_SUBSCRIPT;
    OSL_INVALID_SWIZZLE                              :: INVALID_SWIZZLE;
    OSL_SWIZZLE_USED_AS_STORAGE                      :: SWIZZLE_USED_AS_STORAGE;
    OSL_INVALID_CAST                                 :: INVALID_CAST;
    OSL_VALUE_NAME_REDIFINITION                      :: VALUE_NAME_REDIFINITION;
    OSL_UNRESOLVED_FUNCTION_OR_INTRINSIC             :: UNRESOLVED_FUNCTION_OR_INTRINSIC;
    OSL_BAD_CALL_ARGUMENTS                           :: BAD_CALL_ARGUMENTS;
    OSL_NOT_A_LOGICAL_TYPE                           :: NOT_A_LOGICAL_TYPE;
    OSL_PROCEDURAL_STATEMENT_IN_NON_PROCEDURAL_BLOCK :: PROCEDURAL_STATEMENT_IN_NON_PROCEDURAL_BLOCK;
    OSL_TYPE_REDEFINITION                            :: TYPE_REDEFINITION;
    OSL_NO_SUCH_MEMBER                               :: NO_SUCH_MEMBER;
    OSL_VIEW_INSTANTIATION                           :: VIEW_INSTANTIATION;
    OSL_VIEW_CAST                                    :: VIEW_CAST;
    OSL_BLOCK_TYPE_IS_NOT_STRUCT                     :: BLOCK_TYPE_IS_NOT_STRUCT;
    OSL_FEATURE_NOT_ENABLED                          :: FEATURE_NOT_ENABLED;
    OSL_UNSIZED_ARRAY_NOT_AT_END_OF_STRUCT           :: UNSIZED_ARRAY_NOT_AT_END_OF_STRUCT;
    OSL_INVALID_FBUFFER_VIEW                         :: INVALID_FBUFFER_VIEW;
    OSL_UNIMPLEMENTED                                :: UNIMPLEMENTED;
}

Osl_Target :: enum s32 {
    OSL_TARGET_SPIRV_VULKAN :: 0;
}

Osl_Program_Kind :: enum s32 {
    FRAGMENT :: 0;
    VERTEX   :: 1;
    COMPUTE  :: 2;

    OSL_PROGRAM_GPU_FRAGMENT :: FRAGMENT;
    OSL_PROGRAM_GPU_VERTEX   :: VERTEX;
    OSL_PROGRAM_GPU_COMPUTE  :: COMPUTE;
}

Osl_Feature_Flag_ :: enum s32 {
    OSL_FEATURE_INVOCATION_PIXEL_INTERLOCK :: 2;
}

Osl_Feature_Flag :: u64;

Osl_Compile_Desc :: struct {
    target:           Osl_Target;
    program_kind:     Osl_Program_Kind;
    code_text:        string;
    enabled_features: Osl_Feature_Flag;
}

osl_compile :: (a: Allocator, desc: Osl_Compile_Desc, pcode: **void, pcode_size: *u64, err_log: *string) -> Osl_Result #foreign ostd_windows;

#scope_file

#import "Basic"; // For assert

ostd_windows :: #library "./ostd_windows";

#run {
    {
        instance: int32x2;
        assert(((cast(*void)(*instance.x)) - cast(*void)(*instance)) == 0, "int32x2.x has unexpected offset % instead of 0", ((cast(*void)(*instance.x)) - cast(*void)(*instance)));
        assert(size_of(type_of(int32x2.x)) == 4, "int32x2.x has unexpected size % instead of 4", size_of(type_of(int32x2.x)));
        assert(((cast(*void)(*instance.y)) - cast(*void)(*instance)) == 4, "int32x2.y has unexpected offset % instead of 4", ((cast(*void)(*instance.y)) - cast(*void)(*instance)));
        assert(size_of(type_of(int32x2.y)) == 4, "int32x2.y has unexpected size % instead of 4", size_of(type_of(int32x2.y)));
        assert(size_of(int32x2) == 8, "int32x2 has size % instead of 8", size_of(int32x2));
    }

    {
        instance: int32x4;
        assert(((cast(*void)(*instance.x)) - cast(*void)(*instance)) == 0, "int32x4.x has unexpected offset % instead of 0", ((cast(*void)(*instance.x)) - cast(*void)(*instance)));
        assert(size_of(type_of(int32x4.x)) == 4, "int32x4.x has unexpected size % instead of 4", size_of(type_of(int32x4.x)));
        assert(((cast(*void)(*instance.y)) - cast(*void)(*instance)) == 4, "int32x4.y has unexpected offset % instead of 4", ((cast(*void)(*instance.y)) - cast(*void)(*instance)));
        assert(size_of(type_of(int32x4.y)) == 4, "int32x4.y has unexpected size % instead of 4", size_of(type_of(int32x4.y)));
        assert(((cast(*void)(*instance.z)) - cast(*void)(*instance)) == 8, "int32x4.z has unexpected offset % instead of 8", ((cast(*void)(*instance.z)) - cast(*void)(*instance)));
        assert(size_of(type_of(int32x4.z)) == 4, "int32x4.z has unexpected size % instead of 4", size_of(type_of(int32x4.z)));
        assert(((cast(*void)(*instance.w)) - cast(*void)(*instance)) == 12, "int32x4.w has unexpected offset % instead of 12", ((cast(*void)(*instance.w)) - cast(*void)(*instance)));
        assert(size_of(type_of(int32x4.w)) == 4, "int32x4.w has unexpected size % instead of 4", size_of(type_of(int32x4.w)));
        assert(size_of(int32x4) == 16, "int32x4 has size % instead of 16", size_of(int32x4));
    }

    {
        instance: float2x32;
        assert(((cast(*void)(*instance.x)) - cast(*void)(*instance)) == 0, "float2x32.x has unexpected offset % instead of 0", ((cast(*void)(*instance.x)) - cast(*void)(*instance)));
        assert(size_of(type_of(float2x32.x)) == 4, "float2x32.x has unexpected size % instead of 4", size_of(type_of(float2x32.x)));
        assert(((cast(*void)(*instance.y)) - cast(*void)(*instance)) == 4, "float2x32.y has unexpected offset % instead of 4", ((cast(*void)(*instance.y)) - cast(*void)(*instance)));
        assert(size_of(type_of(float2x32.y)) == 4, "float2x32.y has unexpected size % instead of 4", size_of(type_of(float2x32.y)));
        assert(size_of(float2x32) == 8, "float2x32 has size % instead of 8", size_of(float2x32));
    }

    {
        instance: float3x32;
        assert(((cast(*void)(*instance.x)) - cast(*void)(*instance)) == 0, "float3x32.x has unexpected offset % instead of 0", ((cast(*void)(*instance.x)) - cast(*void)(*instance)));
        assert(size_of(type_of(float3x32.x)) == 4, "float3x32.x has unexpected size % instead of 4", size_of(type_of(float3x32.x)));
        assert(((cast(*void)(*instance.y)) - cast(*void)(*instance)) == 4, "float3x32.y has unexpected offset % instead of 4", ((cast(*void)(*instance.y)) - cast(*void)(*instance)));
        assert(size_of(type_of(float3x32.y)) == 4, "float3x32.y has unexpected size % instead of 4", size_of(type_of(float3x32.y)));
        assert(((cast(*void)(*instance.z)) - cast(*void)(*instance)) == 8, "float3x32.z has unexpected offset % instead of 8", ((cast(*void)(*instance.z)) - cast(*void)(*instance)));
        assert(size_of(type_of(float3x32.z)) == 4, "float3x32.z has unexpected size % instead of 4", size_of(type_of(float3x32.z)));
        assert(size_of(float3x32) == 12, "float3x32 has size % instead of 12", size_of(float3x32));
    }

    {
        instance: float4x32;
        assert(((cast(*void)(*instance.x)) - cast(*void)(*instance)) == 0, "float4x32.x has unexpected offset % instead of 0", ((cast(*void)(*instance.x)) - cast(*void)(*instance)));
        assert(size_of(type_of(float4x32.x)) == 4, "float4x32.x has unexpected size % instead of 4", size_of(type_of(float4x32.x)));
        assert(((cast(*void)(*instance.y)) - cast(*void)(*instance)) == 4, "float4x32.y has unexpected offset % instead of 4", ((cast(*void)(*instance.y)) - cast(*void)(*instance)));
        assert(size_of(type_of(float4x32.y)) == 4, "float4x32.y has unexpected size % instead of 4", size_of(type_of(float4x32.y)));
        assert(((cast(*void)(*instance.z)) - cast(*void)(*instance)) == 8, "float4x32.z has unexpected offset % instead of 8", ((cast(*void)(*instance.z)) - cast(*void)(*instance)));
        assert(size_of(type_of(float4x32.z)) == 4, "float4x32.z has unexpected size % instead of 4", size_of(type_of(float4x32.z)));
        assert(((cast(*void)(*instance.w)) - cast(*void)(*instance)) == 12, "float4x32.w has unexpected offset % instead of 12", ((cast(*void)(*instance.w)) - cast(*void)(*instance)));
        assert(size_of(type_of(float4x32.w)) == 4, "float4x32.w has unexpected size % instead of 4", size_of(type_of(float4x32.w)));
        assert(size_of(float4x32) == 16, "float4x32 has size % instead of 16", size_of(float4x32));
    }

    {
        instance: Matrix4;
        assert(((cast(*void)(*instance.data)) - cast(*void)(*instance)) == 0, "Matrix4.data has unexpected offset % instead of 0", ((cast(*void)(*instance.data)) - cast(*void)(*instance)));
        assert(size_of(type_of(Matrix4.data)) == 64, "Matrix4.data has unexpected size % instead of 64", size_of(type_of(Matrix4.data)));
        assert(size_of(Matrix4) == 64, "Matrix4 has size % instead of 64", size_of(Matrix4));
    }

    {
        instance: Mapped_Memory_Info;
        assert(((cast(*void)(*instance.base)) - cast(*void)(*instance)) == 0, "Mapped_Memory_Info.base has unexpected offset % instead of 0", ((cast(*void)(*instance.base)) - cast(*void)(*instance)));
        assert(size_of(type_of(Mapped_Memory_Info.base)) == 8, "Mapped_Memory_Info.base has unexpected size % instead of 8", size_of(type_of(Mapped_Memory_Info.base)));
        assert(((cast(*void)(*instance.page_count)) - cast(*void)(*instance)) == 8, "Mapped_Memory_Info.page_count has unexpected offset % instead of 8", ((cast(*void)(*instance.page_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Mapped_Memory_Info.page_count)) == 8, "Mapped_Memory_Info.page_count has unexpected size % instead of 8", size_of(type_of(Mapped_Memory_Info.page_count)));
        assert(size_of(Mapped_Memory_Info) == 16, "Mapped_Memory_Info has size % instead of 16", size_of(Mapped_Memory_Info));
    }

    {
        instance: System_Info;
        assert(((cast(*void)(*instance.page_size)) - cast(*void)(*instance)) == 0, "System_Info.page_size has unexpected offset % instead of 0", ((cast(*void)(*instance.page_size)) - cast(*void)(*instance)));
        assert(size_of(type_of(System_Info.page_size)) == 8, "System_Info.page_size has unexpected size % instead of 8", size_of(type_of(System_Info.page_size)));
        assert(((cast(*void)(*instance.granularity)) - cast(*void)(*instance)) == 8, "System_Info.granularity has unexpected offset % instead of 8", ((cast(*void)(*instance.granularity)) - cast(*void)(*instance)));
        assert(size_of(type_of(System_Info.granularity)) == 8, "System_Info.granularity has unexpected size % instead of 8", size_of(type_of(System_Info.granularity)));
        assert(((cast(*void)(*instance.logical_cpu_count)) - cast(*void)(*instance)) == 16, "System_Info.logical_cpu_count has unexpected offset % instead of 16", ((cast(*void)(*instance.logical_cpu_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(System_Info.logical_cpu_count)) == 8, "System_Info.logical_cpu_count has unexpected size % instead of 8", size_of(type_of(System_Info.logical_cpu_count)));
        assert(size_of(System_Info) == 24, "System_Info has size % instead of 24", size_of(System_Info));
    }

    {
        instance: Physical_Monitor;
        assert(((cast(*void)(*instance.name)) - cast(*void)(*instance)) == 0, "Physical_Monitor.name has unexpected offset % instead of 0", ((cast(*void)(*instance.name)) - cast(*void)(*instance)));
        assert(size_of(type_of(Physical_Monitor.name)) == 256, "Physical_Monitor.name has unexpected size % instead of 256", size_of(type_of(Physical_Monitor.name)));
        assert(((cast(*void)(*instance.name_count)) - cast(*void)(*instance)) == 256, "Physical_Monitor.name_count has unexpected offset % instead of 256", ((cast(*void)(*instance.name_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Physical_Monitor.name_count)) == 8, "Physical_Monitor.name_count has unexpected size % instead of 8", size_of(type_of(Physical_Monitor.name_count)));
        assert(((cast(*void)(*instance.refresh_rate)) - cast(*void)(*instance)) == 264, "Physical_Monitor.refresh_rate has unexpected offset % instead of 264", ((cast(*void)(*instance.refresh_rate)) - cast(*void)(*instance)));
        assert(size_of(type_of(Physical_Monitor.refresh_rate)) == 8, "Physical_Monitor.refresh_rate has unexpected size % instead of 8", size_of(type_of(Physical_Monitor.refresh_rate)));
        assert(((cast(*void)(*instance.resolution_x)) - cast(*void)(*instance)) == 272, "Physical_Monitor.resolution_x has unexpected offset % instead of 272", ((cast(*void)(*instance.resolution_x)) - cast(*void)(*instance)));
        assert(size_of(type_of(Physical_Monitor.resolution_x)) == 8, "Physical_Monitor.resolution_x has unexpected size % instead of 8", size_of(type_of(Physical_Monitor.resolution_x)));
        assert(((cast(*void)(*instance.resolution_y)) - cast(*void)(*instance)) == 280, "Physical_Monitor.resolution_y has unexpected offset % instead of 280", ((cast(*void)(*instance.resolution_y)) - cast(*void)(*instance)));
        assert(size_of(type_of(Physical_Monitor.resolution_y)) == 8, "Physical_Monitor.resolution_y has unexpected size % instead of 8", size_of(type_of(Physical_Monitor.resolution_y)));
        assert(((cast(*void)(*instance.scale)) - cast(*void)(*instance)) == 288, "Physical_Monitor.scale has unexpected offset % instead of 288", ((cast(*void)(*instance.scale)) - cast(*void)(*instance)));
        assert(size_of(type_of(Physical_Monitor.scale)) == 8, "Physical_Monitor.scale has unexpected size % instead of 8", size_of(type_of(Physical_Monitor.scale)));
        assert(((cast(*void)(*instance.pos_x)) - cast(*void)(*instance)) == 296, "Physical_Monitor.pos_x has unexpected offset % instead of 296", ((cast(*void)(*instance.pos_x)) - cast(*void)(*instance)));
        assert(size_of(type_of(Physical_Monitor.pos_x)) == 8, "Physical_Monitor.pos_x has unexpected size % instead of 8", size_of(type_of(Physical_Monitor.pos_x)));
        assert(((cast(*void)(*instance.pos_y)) - cast(*void)(*instance)) == 304, "Physical_Monitor.pos_y has unexpected offset % instead of 304", ((cast(*void)(*instance.pos_y)) - cast(*void)(*instance)));
        assert(size_of(type_of(Physical_Monitor.pos_y)) == 8, "Physical_Monitor.pos_y has unexpected size % instead of 8", size_of(type_of(Physical_Monitor.pos_y)));
        assert(((cast(*void)(*instance.handle)) - cast(*void)(*instance)) == 312, "Physical_Monitor.handle has unexpected offset % instead of 312", ((cast(*void)(*instance.handle)) - cast(*void)(*instance)));
        assert(size_of(type_of(Physical_Monitor.handle)) == 8, "Physical_Monitor.handle has unexpected size % instead of 8", size_of(type_of(Physical_Monitor.handle)));
        assert(size_of(Physical_Monitor) == 320, "Physical_Monitor has size % instead of 320", size_of(Physical_Monitor));
    }

    {
        instance: Easy_Command_Result;
        assert(((cast(*void)(*instance.exit_code)) - cast(*void)(*instance)) == 0, "Easy_Command_Result.exit_code has unexpected offset % instead of 0", ((cast(*void)(*instance.exit_code)) - cast(*void)(*instance)));
        assert(size_of(type_of(Easy_Command_Result.exit_code)) == 8, "Easy_Command_Result.exit_code has unexpected size % instead of 8", size_of(type_of(Easy_Command_Result.exit_code)));
        assert(((cast(*void)(*instance.process_start_success)) - cast(*void)(*instance)) == 8, "Easy_Command_Result.process_start_success has unexpected offset % instead of 8", ((cast(*void)(*instance.process_start_success)) - cast(*void)(*instance)));
        assert(size_of(type_of(Easy_Command_Result.process_start_success)) == 1, "Easy_Command_Result.process_start_success has unexpected size % instead of 1", size_of(type_of(Easy_Command_Result.process_start_success)));
        assert(size_of(Easy_Command_Result) == 16, "Easy_Command_Result has size % instead of 16", size_of(Easy_Command_Result));
    }

    {
        instance: Thread;
        assert(((cast(*void)(*instance.handle)) - cast(*void)(*instance)) == 0, "Thread.handle has unexpected offset % instead of 0", ((cast(*void)(*instance.handle)) - cast(*void)(*instance)));
        assert(size_of(type_of(Thread.handle)) == 8, "Thread.handle has unexpected size % instead of 8", size_of(type_of(Thread.handle)));
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 8, "Thread.id has unexpected offset % instead of 8", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Thread.id)) == 8, "Thread.id has unexpected size % instead of 8", size_of(type_of(Thread.id)));
        assert(((cast(*void)(*instance.userdata)) - cast(*void)(*instance)) == 16, "Thread.userdata has unexpected offset % instead of 16", ((cast(*void)(*instance.userdata)) - cast(*void)(*instance)));
        assert(size_of(type_of(Thread.userdata)) == 8, "Thread.userdata has unexpected size % instead of 8", size_of(type_of(Thread.userdata)));
        assert(((cast(*void)(*instance.proc)) - cast(*void)(*instance)) == 24, "Thread.proc has unexpected offset % instead of 24", ((cast(*void)(*instance.proc)) - cast(*void)(*instance)));
        assert(size_of(type_of(Thread.proc)) == 8, "Thread.proc has unexpected size % instead of 8", size_of(type_of(Thread.proc)));
        assert(((cast(*void)(*instance.is_suspended)) - cast(*void)(*instance)) == 32, "Thread.is_suspended has unexpected offset % instead of 32", ((cast(*void)(*instance.is_suspended)) - cast(*void)(*instance)));
        assert(size_of(type_of(Thread.is_suspended)) == 1, "Thread.is_suspended has unexpected size % instead of 1", size_of(type_of(Thread.is_suspended)));
        assert(size_of(Thread) == 40, "Thread has size % instead of 40", size_of(Thread));
    }

    {
        instance: Mutex;
        assert(((cast(*void)(*instance.handle)) - cast(*void)(*instance)) == 0, "Mutex.handle has unexpected offset % instead of 0", ((cast(*void)(*instance.handle)) - cast(*void)(*instance)));
        assert(size_of(type_of(Mutex.handle)) == 8, "Mutex.handle has unexpected size % instead of 8", size_of(type_of(Mutex.handle)));
        assert(((cast(*void)(*instance.handle_backing)) - cast(*void)(*instance)) == 8, "Mutex.handle_backing has unexpected offset % instead of 8", ((cast(*void)(*instance.handle_backing)) - cast(*void)(*instance)));
        assert(size_of(type_of(Mutex.handle_backing)) == 40, "Mutex.handle_backing has unexpected size % instead of 40", size_of(type_of(Mutex.handle_backing)));
        assert(size_of(Mutex) == 48, "Mutex has size % instead of 48", size_of(Mutex));
    }

    {
        instance: Surface_Desc;
        assert(((cast(*void)(*instance.width)) - cast(*void)(*instance)) == 0, "Surface_Desc.width has unexpected offset % instead of 0", ((cast(*void)(*instance.width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Surface_Desc.width)) == 4, "Surface_Desc.width has unexpected size % instead of 4", size_of(type_of(Surface_Desc.width)));
        assert(((cast(*void)(*instance.height)) - cast(*void)(*instance)) == 4, "Surface_Desc.height has unexpected offset % instead of 4", ((cast(*void)(*instance.height)) - cast(*void)(*instance)));
        assert(size_of(type_of(Surface_Desc.height)) == 4, "Surface_Desc.height has unexpected size % instead of 4", size_of(type_of(Surface_Desc.height)));
        assert(((cast(*void)(*instance.x_pos)) - cast(*void)(*instance)) == 8, "Surface_Desc.x_pos has unexpected offset % instead of 8", ((cast(*void)(*instance.x_pos)) - cast(*void)(*instance)));
        assert(size_of(type_of(Surface_Desc.x_pos)) == 4, "Surface_Desc.x_pos has unexpected size % instead of 4", size_of(type_of(Surface_Desc.x_pos)));
        assert(((cast(*void)(*instance.y_pos)) - cast(*void)(*instance)) == 12, "Surface_Desc.y_pos has unexpected offset % instead of 12", ((cast(*void)(*instance.y_pos)) - cast(*void)(*instance)));
        assert(size_of(type_of(Surface_Desc.y_pos)) == 4, "Surface_Desc.y_pos has unexpected size % instead of 4", size_of(type_of(Surface_Desc.y_pos)));
        assert(((cast(*void)(*instance.title)) - cast(*void)(*instance)) == 16, "Surface_Desc.title has unexpected offset % instead of 16", ((cast(*void)(*instance.title)) - cast(*void)(*instance)));
        assert(size_of(type_of(Surface_Desc.title)) == 16, "Surface_Desc.title has unexpected size % instead of 16", size_of(type_of(Surface_Desc.title)));
        assert(((cast(*void)(*instance.fullscreen)) - cast(*void)(*instance)) == 32, "Surface_Desc.fullscreen has unexpected offset % instead of 32", ((cast(*void)(*instance.fullscreen)) - cast(*void)(*instance)));
        assert(size_of(type_of(Surface_Desc.fullscreen)) == 1, "Surface_Desc.fullscreen has unexpected size % instead of 1", size_of(type_of(Surface_Desc.fullscreen)));
        assert(((cast(*void)(*instance.flags)) - cast(*void)(*instance)) == 40, "Surface_Desc.flags has unexpected offset % instead of 40", ((cast(*void)(*instance.flags)) - cast(*void)(*instance)));
        assert(size_of(type_of(Surface_Desc.flags)) == 8, "Surface_Desc.flags has unexpected size % instead of 8", size_of(type_of(Surface_Desc.flags)));
        assert(size_of(Surface_Desc) == 48, "Surface_Desc has size % instead of 48", size_of(Surface_Desc));
    }

    {
        instance: Ostd_Thread_Storage;
        assert(((cast(*void)(*instance.thread_id)) - cast(*void)(*instance)) == 0, "Ostd_Thread_Storage.thread_id has unexpected offset % instead of 0", ((cast(*void)(*instance.thread_id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Ostd_Thread_Storage.thread_id)) == 8, "Ostd_Thread_Storage.thread_id has unexpected size % instead of 8", size_of(type_of(Ostd_Thread_Storage.thread_id)));
        assert(((cast(*void)(*instance.temporary_storage_struct_backing)) - cast(*void)(*instance)) == 8, "Ostd_Thread_Storage.temporary_storage_struct_backing has unexpected offset % instead of 8", ((cast(*void)(*instance.temporary_storage_struct_backing)) - cast(*void)(*instance)));
        assert(size_of(type_of(Ostd_Thread_Storage.temporary_storage_struct_backing)) == 128, "Ostd_Thread_Storage.temporary_storage_struct_backing has unexpected size % instead of 128", size_of(type_of(Ostd_Thread_Storage.temporary_storage_struct_backing)));
        assert(((cast(*void)(*instance.temp)) - cast(*void)(*instance)) == 136, "Ostd_Thread_Storage.temp has unexpected offset % instead of 136", ((cast(*void)(*instance.temp)) - cast(*void)(*instance)));
        assert(size_of(type_of(Ostd_Thread_Storage.temp)) == 8, "Ostd_Thread_Storage.temp has unexpected size % instead of 8", size_of(type_of(Ostd_Thread_Storage.temp)));
        assert(((cast(*void)(*instance.taken)) - cast(*void)(*instance)) == 144, "Ostd_Thread_Storage.taken has unexpected offset % instead of 144", ((cast(*void)(*instance.taken)) - cast(*void)(*instance)));
        assert(size_of(type_of(Ostd_Thread_Storage.taken)) == 1, "Ostd_Thread_Storage.taken has unexpected size % instead of 1", size_of(type_of(Ostd_Thread_Storage.taken)));
        assert(size_of(Ostd_Thread_Storage) == 152, "Ostd_Thread_Storage has size % instead of 152", size_of(Ostd_Thread_Storage));
    }

    {
        instance: Utf8_To_Utf32_Result;
        assert(((cast(*void)(*instance.utf32)) - cast(*void)(*instance)) == 0, "Utf8_To_Utf32_Result.utf32 has unexpected offset % instead of 0", ((cast(*void)(*instance.utf32)) - cast(*void)(*instance)));
        assert(size_of(type_of(Utf8_To_Utf32_Result.utf32)) == 4, "Utf8_To_Utf32_Result.utf32 has unexpected size % instead of 4", size_of(type_of(Utf8_To_Utf32_Result.utf32)));
        assert(((cast(*void)(*instance.continuation_bytes)) - cast(*void)(*instance)) == 8, "Utf8_To_Utf32_Result.continuation_bytes has unexpected offset % instead of 8", ((cast(*void)(*instance.continuation_bytes)) - cast(*void)(*instance)));
        assert(size_of(type_of(Utf8_To_Utf32_Result.continuation_bytes)) == 8, "Utf8_To_Utf32_Result.continuation_bytes has unexpected size % instead of 8", size_of(type_of(Utf8_To_Utf32_Result.continuation_bytes)));
        assert(((cast(*void)(*instance.reached_end)) - cast(*void)(*instance)) == 16, "Utf8_To_Utf32_Result.reached_end has unexpected offset % instead of 16", ((cast(*void)(*instance.reached_end)) - cast(*void)(*instance)));
        assert(size_of(type_of(Utf8_To_Utf32_Result.reached_end)) == 1, "Utf8_To_Utf32_Result.reached_end has unexpected size % instead of 1", size_of(type_of(Utf8_To_Utf32_Result.reached_end)));
        assert(((cast(*void)(*instance.error)) - cast(*void)(*instance)) == 17, "Utf8_To_Utf32_Result.error has unexpected offset % instead of 17", ((cast(*void)(*instance.error)) - cast(*void)(*instance)));
        assert(size_of(type_of(Utf8_To_Utf32_Result.error)) == 1, "Utf8_To_Utf32_Result.error has unexpected size % instead of 1", size_of(type_of(Utf8_To_Utf32_Result.error)));
        assert(size_of(Utf8_To_Utf32_Result) == 24, "Utf8_To_Utf32_Result has size % instead of 24", size_of(Utf8_To_Utf32_Result));
    }

    {
        instance: Utf8_To_Utf16_Result;
        assert(((cast(*void)(*instance.utf32)) - cast(*void)(*instance)) == 0, "Utf8_To_Utf16_Result.utf32 has unexpected offset % instead of 0", ((cast(*void)(*instance.utf32)) - cast(*void)(*instance)));
        assert(size_of(type_of(Utf8_To_Utf16_Result.utf32)) == 4, "Utf8_To_Utf16_Result.utf32 has unexpected size % instead of 4", size_of(type_of(Utf8_To_Utf16_Result.utf32)));
        assert(((cast(*void)(*instance.continuation_bytes)) - cast(*void)(*instance)) == 8, "Utf8_To_Utf16_Result.continuation_bytes has unexpected offset % instead of 8", ((cast(*void)(*instance.continuation_bytes)) - cast(*void)(*instance)));
        assert(size_of(type_of(Utf8_To_Utf16_Result.continuation_bytes)) == 8, "Utf8_To_Utf16_Result.continuation_bytes has unexpected size % instead of 8", size_of(type_of(Utf8_To_Utf16_Result.continuation_bytes)));
        assert(((cast(*void)(*instance.reached_end)) - cast(*void)(*instance)) == 16, "Utf8_To_Utf16_Result.reached_end has unexpected offset % instead of 16", ((cast(*void)(*instance.reached_end)) - cast(*void)(*instance)));
        assert(size_of(type_of(Utf8_To_Utf16_Result.reached_end)) == 1, "Utf8_To_Utf16_Result.reached_end has unexpected size % instead of 1", size_of(type_of(Utf8_To_Utf16_Result.reached_end)));
        assert(((cast(*void)(*instance.error)) - cast(*void)(*instance)) == 17, "Utf8_To_Utf16_Result.error has unexpected offset % instead of 17", ((cast(*void)(*instance.error)) - cast(*void)(*instance)));
        assert(size_of(type_of(Utf8_To_Utf16_Result.error)) == 1, "Utf8_To_Utf16_Result.error has unexpected size % instead of 1", size_of(type_of(Utf8_To_Utf16_Result.error)));
        assert(size_of(Utf8_To_Utf16_Result) == 24, "Utf8_To_Utf16_Result has size % instead of 24", size_of(Utf8_To_Utf16_Result));
    }

    {
        instance: Allocator;
        assert(((cast(*void)(*instance.data)) - cast(*void)(*instance)) == 0, "Allocator.data has unexpected offset % instead of 0", ((cast(*void)(*instance.data)) - cast(*void)(*instance)));
        assert(size_of(type_of(Allocator.data)) == 8, "Allocator.data has unexpected size % instead of 8", size_of(type_of(Allocator.data)));
        assert(((cast(*void)(*instance.proc)) - cast(*void)(*instance)) == 8, "Allocator.proc has unexpected offset % instead of 8", ((cast(*void)(*instance.proc)) - cast(*void)(*instance)));
        assert(size_of(type_of(Allocator.proc)) == 8, "Allocator.proc has unexpected size % instead of 8", size_of(type_of(Allocator.proc)));
        assert(size_of(Allocator) == 16, "Allocator has size % instead of 16", size_of(Allocator));
    }

    {
        instance: Arena;
        assert(((cast(*void)(*instance.start)) - cast(*void)(*instance)) == 0, "Arena.start has unexpected offset % instead of 0", ((cast(*void)(*instance.start)) - cast(*void)(*instance)));
        assert(size_of(type_of(Arena.start)) == 8, "Arena.start has unexpected size % instead of 8", size_of(type_of(Arena.start)));
        assert(((cast(*void)(*instance.position)) - cast(*void)(*instance)) == 8, "Arena.position has unexpected offset % instead of 8", ((cast(*void)(*instance.position)) - cast(*void)(*instance)));
        assert(size_of(type_of(Arena.position)) == 8, "Arena.position has unexpected size % instead of 8", size_of(type_of(Arena.position)));
        assert(((cast(*void)(*instance.reserved_size)) - cast(*void)(*instance)) == 16, "Arena.reserved_size has unexpected offset % instead of 16", ((cast(*void)(*instance.reserved_size)) - cast(*void)(*instance)));
        assert(size_of(type_of(Arena.reserved_size)) == 8, "Arena.reserved_size has unexpected size % instead of 8", size_of(type_of(Arena.reserved_size)));
        assert(((cast(*void)(*instance.allocated_size)) - cast(*void)(*instance)) == 24, "Arena.allocated_size has unexpected offset % instead of 24", ((cast(*void)(*instance.allocated_size)) - cast(*void)(*instance)));
        assert(size_of(type_of(Arena.allocated_size)) == 8, "Arena.allocated_size has unexpected size % instead of 8", size_of(type_of(Arena.allocated_size)));
        assert(size_of(Arena) == 32, "Arena has size % instead of 32", size_of(Arena));
    }

    {
        instance: Var_Arg;
        assert(((cast(*void)(*instance.int_val)) - cast(*void)(*instance)) == 0, "Var_Arg.int_val has unexpected offset % instead of 0", ((cast(*void)(*instance.int_val)) - cast(*void)(*instance)));
        assert(size_of(type_of(Var_Arg.int_val)) == 8, "Var_Arg.int_val has unexpected size % instead of 8", size_of(type_of(Var_Arg.int_val)));
        assert(((cast(*void)(*instance.flt_val)) - cast(*void)(*instance)) == 8, "Var_Arg.flt_val has unexpected offset % instead of 8", ((cast(*void)(*instance.flt_val)) - cast(*void)(*instance)));
        assert(size_of(type_of(Var_Arg.flt_val)) == 8, "Var_Arg.flt_val has unexpected size % instead of 8", size_of(type_of(Var_Arg.flt_val)));
        assert(((cast(*void)(*instance.str_val)) - cast(*void)(*instance)) == 16, "Var_Arg.str_val has unexpected offset % instead of 16", ((cast(*void)(*instance.str_val)) - cast(*void)(*instance)));
        assert(size_of(type_of(Var_Arg.str_val)) == 16, "Var_Arg.str_val has unexpected size % instead of 16", size_of(type_of(Var_Arg.str_val)));
        assert(((cast(*void)(*instance.size)) - cast(*void)(*instance)) == 32, "Var_Arg.size has unexpected offset % instead of 32", ((cast(*void)(*instance.size)) - cast(*void)(*instance)));
        assert(size_of(type_of(Var_Arg.size)) == 8, "Var_Arg.size has unexpected size % instead of 8", size_of(type_of(Var_Arg.size)));
        assert(size_of(Var_Arg) == 40, "Var_Arg has size % instead of 40", size_of(Var_Arg));
    }

    {
        instance: Source_Location;
        assert(((cast(*void)(*instance.line)) - cast(*void)(*instance)) == 0, "Source_Location.line has unexpected offset % instead of 0", ((cast(*void)(*instance.line)) - cast(*void)(*instance)));
        assert(size_of(type_of(Source_Location.line)) == 8, "Source_Location.line has unexpected size % instead of 8", size_of(type_of(Source_Location.line)));
        assert(((cast(*void)(*instance.file)) - cast(*void)(*instance)) == 8, "Source_Location.file has unexpected offset % instead of 8", ((cast(*void)(*instance.file)) - cast(*void)(*instance)));
        assert(size_of(type_of(Source_Location.file)) == 16, "Source_Location.file has unexpected size % instead of 16", size_of(type_of(Source_Location.file)));
        assert(((cast(*void)(*instance.function)) - cast(*void)(*instance)) == 24, "Source_Location.function has unexpected offset % instead of 24", ((cast(*void)(*instance.function)) - cast(*void)(*instance)));
        assert(size_of(type_of(Source_Location.function)) == 16, "Source_Location.function has unexpected size % instead of 16", size_of(type_of(Source_Location.function)));
        assert(size_of(Source_Location) == 40, "Source_Location has size % instead of 40", size_of(Source_Location));
    }

    {
        instance: Format_String_Desc;
        assert(((cast(*void)(*instance.buffer)) - cast(*void)(*instance)) == 0, "Format_String_Desc.buffer has unexpected offset % instead of 0", ((cast(*void)(*instance.buffer)) - cast(*void)(*instance)));
        assert(size_of(type_of(Format_String_Desc.buffer)) == 8, "Format_String_Desc.buffer has unexpected size % instead of 8", size_of(type_of(Format_String_Desc.buffer)));
        assert(((cast(*void)(*instance.buffer_size)) - cast(*void)(*instance)) == 8, "Format_String_Desc.buffer_size has unexpected offset % instead of 8", ((cast(*void)(*instance.buffer_size)) - cast(*void)(*instance)));
        assert(size_of(type_of(Format_String_Desc.buffer_size)) == 8, "Format_String_Desc.buffer_size has unexpected size % instead of 8", size_of(type_of(Format_String_Desc.buffer_size)));
        assert(((cast(*void)(*instance.fmt)) - cast(*void)(*instance)) == 16, "Format_String_Desc.fmt has unexpected offset % instead of 16", ((cast(*void)(*instance.fmt)) - cast(*void)(*instance)));
        assert(size_of(type_of(Format_String_Desc.fmt)) == 16, "Format_String_Desc.fmt has unexpected size % instead of 16", size_of(type_of(Format_String_Desc.fmt)));
        assert(size_of(Format_String_Desc) == 32, "Format_String_Desc has size % instead of 32", size_of(Format_String_Desc));
    }

    {
        instance: Print_Desc;
        assert(((cast(*void)(*instance.a)) - cast(*void)(*instance)) == 0, "Print_Desc.a has unexpected offset % instead of 0", ((cast(*void)(*instance.a)) - cast(*void)(*instance)));
        assert(size_of(type_of(Print_Desc.a)) == 16, "Print_Desc.a has unexpected size % instead of 16", size_of(type_of(Print_Desc.a)));
        assert(((cast(*void)(*instance.fmt)) - cast(*void)(*instance)) == 16, "Print_Desc.fmt has unexpected offset % instead of 16", ((cast(*void)(*instance.fmt)) - cast(*void)(*instance)));
        assert(size_of(type_of(Print_Desc.fmt)) == 16, "Print_Desc.fmt has unexpected size % instead of 16", size_of(type_of(Print_Desc.fmt)));
        assert(((cast(*void)(*instance.file)) - cast(*void)(*instance)) == 32, "Print_Desc.file has unexpected offset % instead of 32", ((cast(*void)(*instance.file)) - cast(*void)(*instance)));
        assert(size_of(type_of(Print_Desc.file)) == 8, "Print_Desc.file has unexpected size % instead of 8", size_of(type_of(Print_Desc.file)));
        assert(size_of(Print_Desc) == 40, "Print_Desc has size % instead of 40", size_of(Print_Desc));
    }

    {
        instance: Log_Desc;
        assert(((cast(*void)(*instance.a)) - cast(*void)(*instance)) == 0, "Log_Desc.a has unexpected offset % instead of 0", ((cast(*void)(*instance.a)) - cast(*void)(*instance)));
        assert(size_of(type_of(Log_Desc.a)) == 16, "Log_Desc.a has unexpected size % instead of 16", size_of(type_of(Log_Desc.a)));
        assert(((cast(*void)(*instance.fmt)) - cast(*void)(*instance)) == 16, "Log_Desc.fmt has unexpected offset % instead of 16", ((cast(*void)(*instance.fmt)) - cast(*void)(*instance)));
        assert(size_of(type_of(Log_Desc.fmt)) == 16, "Log_Desc.fmt has unexpected size % instead of 16", size_of(type_of(Log_Desc.fmt)));
        assert(((cast(*void)(*instance.flags)) - cast(*void)(*instance)) == 32, "Log_Desc.flags has unexpected offset % instead of 32", ((cast(*void)(*instance.flags)) - cast(*void)(*instance)));
        assert(size_of(type_of(Log_Desc.flags)) == 8, "Log_Desc.flags has unexpected size % instead of 8", size_of(type_of(Log_Desc.flags)));
        assert(((cast(*void)(*instance.location)) - cast(*void)(*instance)) == 40, "Log_Desc.location has unexpected offset % instead of 40", ((cast(*void)(*instance.location)) - cast(*void)(*instance)));
        assert(size_of(type_of(Log_Desc.location)) == 40, "Log_Desc.location has unexpected size % instead of 40", size_of(type_of(Log_Desc.location)));
        assert(size_of(Log_Desc) == 80, "Log_Desc has size % instead of 80", size_of(Log_Desc));
    }

    {
        instance: Oga_Logical_Engine_Family_Info;
        assert(((cast(*void)(*instance.flags)) - cast(*void)(*instance)) == 0, "Oga_Logical_Engine_Family_Info.flags has unexpected offset % instead of 0", ((cast(*void)(*instance.flags)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Logical_Engine_Family_Info.flags)) == 4, "Oga_Logical_Engine_Family_Info.flags has unexpected size % instead of 4", size_of(type_of(Oga_Logical_Engine_Family_Info.flags)));
        assert(((cast(*void)(*instance.engine_capacity)) - cast(*void)(*instance)) == 4, "Oga_Logical_Engine_Family_Info.engine_capacity has unexpected offset % instead of 4", ((cast(*void)(*instance.engine_capacity)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Logical_Engine_Family_Info.engine_capacity)) == 4, "Oga_Logical_Engine_Family_Info.engine_capacity has unexpected size % instead of 4", size_of(type_of(Oga_Logical_Engine_Family_Info.engine_capacity)));
        assert(size_of(Oga_Logical_Engine_Family_Info) == 8, "Oga_Logical_Engine_Family_Info has size % instead of 8", size_of(Oga_Logical_Engine_Family_Info));
    }

    {
        instance: Oga_Memory_Heap;
        assert(((cast(*void)(*instance.properties)) - cast(*void)(*instance)) == 0, "Oga_Memory_Heap.properties has unexpected offset % instead of 0", ((cast(*void)(*instance.properties)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Memory_Heap.properties)) == 8, "Oga_Memory_Heap.properties has unexpected size % instead of 8", size_of(type_of(Oga_Memory_Heap.properties)));
        assert(((cast(*void)(*instance.size)) - cast(*void)(*instance)) == 8, "Oga_Memory_Heap.size has unexpected offset % instead of 8", ((cast(*void)(*instance.size)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Memory_Heap.size)) == 8, "Oga_Memory_Heap.size has unexpected size % instead of 8", size_of(type_of(Oga_Memory_Heap.size)));
        assert(((cast(*void)(*instance.supported_usage_flags)) - cast(*void)(*instance)) == 16, "Oga_Memory_Heap.supported_usage_flags has unexpected offset % instead of 16", ((cast(*void)(*instance.supported_usage_flags)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Memory_Heap.supported_usage_flags)) == 8, "Oga_Memory_Heap.supported_usage_flags has unexpected size % instead of 8", size_of(type_of(Oga_Memory_Heap.supported_usage_flags)));
        assert(size_of(Oga_Memory_Heap) == 24, "Oga_Memory_Heap has size % instead of 24", size_of(Oga_Memory_Heap));
    }

    {
        instance: Oga_Device_Limits;
        assert(((cast(*void)(*instance.max_program_view_sets_per_stage)) - cast(*void)(*instance)) == 0, "Oga_Device_Limits.max_program_view_sets_per_stage has unexpected offset % instead of 0", ((cast(*void)(*instance.max_program_view_sets_per_stage)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_program_view_sets_per_stage)) == 8, "Oga_Device_Limits.max_program_view_sets_per_stage has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_program_view_sets_per_stage)));
        assert(((cast(*void)(*instance.max_fast_data_blocks_per_stage)) - cast(*void)(*instance)) == 8, "Oga_Device_Limits.max_fast_data_blocks_per_stage has unexpected offset % instead of 8", ((cast(*void)(*instance.max_fast_data_blocks_per_stage)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_fast_data_blocks_per_stage)) == 8, "Oga_Device_Limits.max_fast_data_blocks_per_stage has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_fast_data_blocks_per_stage)));
        assert(((cast(*void)(*instance.max_large_data_blocks_per_stage)) - cast(*void)(*instance)) == 16, "Oga_Device_Limits.max_large_data_blocks_per_stage has unexpected offset % instead of 16", ((cast(*void)(*instance.max_large_data_blocks_per_stage)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_large_data_blocks_per_stage)) == 8, "Oga_Device_Limits.max_large_data_blocks_per_stage has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_large_data_blocks_per_stage)));
        assert(((cast(*void)(*instance.max_images_per_stage)) - cast(*void)(*instance)) == 24, "Oga_Device_Limits.max_images_per_stage has unexpected offset % instead of 24", ((cast(*void)(*instance.max_images_per_stage)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_images_per_stage)) == 8, "Oga_Device_Limits.max_images_per_stage has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_images_per_stage)));
        assert(((cast(*void)(*instance.max_fbuffers_per_stage)) - cast(*void)(*instance)) == 32, "Oga_Device_Limits.max_fbuffers_per_stage has unexpected offset % instead of 32", ((cast(*void)(*instance.max_fbuffers_per_stage)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_fbuffers_per_stage)) == 8, "Oga_Device_Limits.max_fbuffers_per_stage has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_fbuffers_per_stage)));
        assert(((cast(*void)(*instance.max_samplers_per_stage)) - cast(*void)(*instance)) == 40, "Oga_Device_Limits.max_samplers_per_stage has unexpected offset % instead of 40", ((cast(*void)(*instance.max_samplers_per_stage)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_samplers_per_stage)) == 8, "Oga_Device_Limits.max_samplers_per_stage has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_samplers_per_stage)));
        assert(((cast(*void)(*instance.max_fast_data_blocks_per_layout)) - cast(*void)(*instance)) == 48, "Oga_Device_Limits.max_fast_data_blocks_per_layout has unexpected offset % instead of 48", ((cast(*void)(*instance.max_fast_data_blocks_per_layout)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_fast_data_blocks_per_layout)) == 8, "Oga_Device_Limits.max_fast_data_blocks_per_layout has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_fast_data_blocks_per_layout)));
        assert(((cast(*void)(*instance.max_large_data_blocks_per_layout)) - cast(*void)(*instance)) == 56, "Oga_Device_Limits.max_large_data_blocks_per_layout has unexpected offset % instead of 56", ((cast(*void)(*instance.max_large_data_blocks_per_layout)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_large_data_blocks_per_layout)) == 8, "Oga_Device_Limits.max_large_data_blocks_per_layout has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_large_data_blocks_per_layout)));
        assert(((cast(*void)(*instance.max_images_per_layout)) - cast(*void)(*instance)) == 64, "Oga_Device_Limits.max_images_per_layout has unexpected offset % instead of 64", ((cast(*void)(*instance.max_images_per_layout)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_images_per_layout)) == 8, "Oga_Device_Limits.max_images_per_layout has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_images_per_layout)));
        assert(((cast(*void)(*instance.max_fbuffers_per_layout)) - cast(*void)(*instance)) == 72, "Oga_Device_Limits.max_fbuffers_per_layout has unexpected offset % instead of 72", ((cast(*void)(*instance.max_fbuffers_per_layout)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_fbuffers_per_layout)) == 8, "Oga_Device_Limits.max_fbuffers_per_layout has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_fbuffers_per_layout)));
        assert(((cast(*void)(*instance.max_samplers_per_layout)) - cast(*void)(*instance)) == 80, "Oga_Device_Limits.max_samplers_per_layout has unexpected offset % instead of 80", ((cast(*void)(*instance.max_samplers_per_layout)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_samplers_per_layout)) == 8, "Oga_Device_Limits.max_samplers_per_layout has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_samplers_per_layout)));
        assert(((cast(*void)(*instance.max_memory_allocations)) - cast(*void)(*instance)) == 88, "Oga_Device_Limits.max_memory_allocations has unexpected offset % instead of 88", ((cast(*void)(*instance.max_memory_allocations)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_memory_allocations)) == 8, "Oga_Device_Limits.max_memory_allocations has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_memory_allocations)));
        assert(((cast(*void)(*instance.max_sampler_allocations)) - cast(*void)(*instance)) == 96, "Oga_Device_Limits.max_sampler_allocations has unexpected offset % instead of 96", ((cast(*void)(*instance.max_sampler_allocations)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_sampler_allocations)) == 8, "Oga_Device_Limits.max_sampler_allocations has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_sampler_allocations)));
        assert(((cast(*void)(*instance.max_image_dimension_1d)) - cast(*void)(*instance)) == 104, "Oga_Device_Limits.max_image_dimension_1d has unexpected offset % instead of 104", ((cast(*void)(*instance.max_image_dimension_1d)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_image_dimension_1d)) == 8, "Oga_Device_Limits.max_image_dimension_1d has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_image_dimension_1d)));
        assert(((cast(*void)(*instance.max_image_dimension_2d)) - cast(*void)(*instance)) == 112, "Oga_Device_Limits.max_image_dimension_2d has unexpected offset % instead of 112", ((cast(*void)(*instance.max_image_dimension_2d)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_image_dimension_2d)) == 8, "Oga_Device_Limits.max_image_dimension_2d has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_image_dimension_2d)));
        assert(((cast(*void)(*instance.max_image_dimension_3d)) - cast(*void)(*instance)) == 120, "Oga_Device_Limits.max_image_dimension_3d has unexpected offset % instead of 120", ((cast(*void)(*instance.max_image_dimension_3d)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_image_dimension_3d)) == 8, "Oga_Device_Limits.max_image_dimension_3d has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_image_dimension_3d)));
        assert(((cast(*void)(*instance.max_fast_access_data_block_size)) - cast(*void)(*instance)) == 128, "Oga_Device_Limits.max_fast_access_data_block_size has unexpected offset % instead of 128", ((cast(*void)(*instance.max_fast_access_data_block_size)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_fast_access_data_block_size)) == 8, "Oga_Device_Limits.max_fast_access_data_block_size has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_fast_access_data_block_size)));
        assert(((cast(*void)(*instance.max_vertex_layout_attributes)) - cast(*void)(*instance)) == 136, "Oga_Device_Limits.max_vertex_layout_attributes has unexpected offset % instead of 136", ((cast(*void)(*instance.max_vertex_layout_attributes)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_vertex_layout_attributes)) == 8, "Oga_Device_Limits.max_vertex_layout_attributes has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_vertex_layout_attributes)));
        assert(((cast(*void)(*instance.max_vertex_layout_bindings)) - cast(*void)(*instance)) == 144, "Oga_Device_Limits.max_vertex_layout_bindings has unexpected offset % instead of 144", ((cast(*void)(*instance.max_vertex_layout_bindings)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_vertex_layout_bindings)) == 8, "Oga_Device_Limits.max_vertex_layout_bindings has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_vertex_layout_bindings)));
        assert(((cast(*void)(*instance.max_vertex_layout_attribute_offset)) - cast(*void)(*instance)) == 152, "Oga_Device_Limits.max_vertex_layout_attribute_offset has unexpected offset % instead of 152", ((cast(*void)(*instance.max_vertex_layout_attribute_offset)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_vertex_layout_attribute_offset)) == 8, "Oga_Device_Limits.max_vertex_layout_attribute_offset has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_vertex_layout_attribute_offset)));
        assert(((cast(*void)(*instance.max_vertex_layout_binding_stride)) - cast(*void)(*instance)) == 160, "Oga_Device_Limits.max_vertex_layout_binding_stride has unexpected offset % instead of 160", ((cast(*void)(*instance.max_vertex_layout_binding_stride)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_vertex_layout_binding_stride)) == 8, "Oga_Device_Limits.max_vertex_layout_binding_stride has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_vertex_layout_binding_stride)));
        assert(((cast(*void)(*instance.max_fragment_stage_output_attachments)) - cast(*void)(*instance)) == 168, "Oga_Device_Limits.max_fragment_stage_output_attachments has unexpected offset % instead of 168", ((cast(*void)(*instance.max_fragment_stage_output_attachments)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_fragment_stage_output_attachments)) == 8, "Oga_Device_Limits.max_fragment_stage_output_attachments has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_fragment_stage_output_attachments)));
        assert(((cast(*void)(*instance.max_sampler_anisotropy)) - cast(*void)(*instance)) == 176, "Oga_Device_Limits.max_sampler_anisotropy has unexpected offset % instead of 176", ((cast(*void)(*instance.max_sampler_anisotropy)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_sampler_anisotropy)) == 4, "Oga_Device_Limits.max_sampler_anisotropy has unexpected size % instead of 4", size_of(type_of(Oga_Device_Limits.max_sampler_anisotropy)));
        assert(((cast(*void)(*instance.max_viewports)) - cast(*void)(*instance)) == 184, "Oga_Device_Limits.max_viewports has unexpected offset % instead of 184", ((cast(*void)(*instance.max_viewports)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_viewports)) == 8, "Oga_Device_Limits.max_viewports has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_viewports)));
        assert(((cast(*void)(*instance.max_viewport_width)) - cast(*void)(*instance)) == 192, "Oga_Device_Limits.max_viewport_width has unexpected offset % instead of 192", ((cast(*void)(*instance.max_viewport_width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_viewport_width)) == 8, "Oga_Device_Limits.max_viewport_width has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_viewport_width)));
        assert(((cast(*void)(*instance.max_viewport_height)) - cast(*void)(*instance)) == 200, "Oga_Device_Limits.max_viewport_height has unexpected offset % instead of 200", ((cast(*void)(*instance.max_viewport_height)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_viewport_height)) == 8, "Oga_Device_Limits.max_viewport_height has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_viewport_height)));
        assert(((cast(*void)(*instance.max_framebuffer_width)) - cast(*void)(*instance)) == 208, "Oga_Device_Limits.max_framebuffer_width has unexpected offset % instead of 208", ((cast(*void)(*instance.max_framebuffer_width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_framebuffer_width)) == 8, "Oga_Device_Limits.max_framebuffer_width has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_framebuffer_width)));
        assert(((cast(*void)(*instance.max_framebuffer_height)) - cast(*void)(*instance)) == 216, "Oga_Device_Limits.max_framebuffer_height has unexpected offset % instead of 216", ((cast(*void)(*instance.max_framebuffer_height)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_framebuffer_height)) == 8, "Oga_Device_Limits.max_framebuffer_height has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_framebuffer_height)));
        assert(((cast(*void)(*instance.max_render_attachments)) - cast(*void)(*instance)) == 224, "Oga_Device_Limits.max_render_attachments has unexpected offset % instead of 224", ((cast(*void)(*instance.max_render_attachments)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.max_render_attachments)) == 8, "Oga_Device_Limits.max_render_attachments has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.max_render_attachments)));
        assert(((cast(*void)(*instance.min_memory_map_alignment)) - cast(*void)(*instance)) == 232, "Oga_Device_Limits.min_memory_map_alignment has unexpected offset % instead of 232", ((cast(*void)(*instance.min_memory_map_alignment)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.min_memory_map_alignment)) == 8, "Oga_Device_Limits.min_memory_map_alignment has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.min_memory_map_alignment)));
        assert(((cast(*void)(*instance.supported_sample_counts_render_pass)) - cast(*void)(*instance)) == 240, "Oga_Device_Limits.supported_sample_counts_render_pass has unexpected offset % instead of 240", ((cast(*void)(*instance.supported_sample_counts_render_pass)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.supported_sample_counts_render_pass)) == 4, "Oga_Device_Limits.supported_sample_counts_render_pass has unexpected size % instead of 4", size_of(type_of(Oga_Device_Limits.supported_sample_counts_render_pass)));
        assert(((cast(*void)(*instance.supported_sample_counts_image_float)) - cast(*void)(*instance)) == 244, "Oga_Device_Limits.supported_sample_counts_image_float has unexpected offset % instead of 244", ((cast(*void)(*instance.supported_sample_counts_image_float)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.supported_sample_counts_image_float)) == 4, "Oga_Device_Limits.supported_sample_counts_image_float has unexpected size % instead of 4", size_of(type_of(Oga_Device_Limits.supported_sample_counts_image_float)));
        assert(((cast(*void)(*instance.supported_sample_counts_fbuffer_float)) - cast(*void)(*instance)) == 248, "Oga_Device_Limits.supported_sample_counts_fbuffer_float has unexpected offset % instead of 248", ((cast(*void)(*instance.supported_sample_counts_fbuffer_float)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.supported_sample_counts_fbuffer_float)) == 4, "Oga_Device_Limits.supported_sample_counts_fbuffer_float has unexpected size % instead of 4", size_of(type_of(Oga_Device_Limits.supported_sample_counts_fbuffer_float)));
        assert(((cast(*void)(*instance.supported_sample_counts_image_int)) - cast(*void)(*instance)) == 252, "Oga_Device_Limits.supported_sample_counts_image_int has unexpected offset % instead of 252", ((cast(*void)(*instance.supported_sample_counts_image_int)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.supported_sample_counts_image_int)) == 4, "Oga_Device_Limits.supported_sample_counts_image_int has unexpected size % instead of 4", size_of(type_of(Oga_Device_Limits.supported_sample_counts_image_int)));
        assert(((cast(*void)(*instance.supported_sample_counts_fbuffer_int)) - cast(*void)(*instance)) == 256, "Oga_Device_Limits.supported_sample_counts_fbuffer_int has unexpected offset % instead of 256", ((cast(*void)(*instance.supported_sample_counts_fbuffer_int)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.supported_sample_counts_fbuffer_int)) == 4, "Oga_Device_Limits.supported_sample_counts_fbuffer_int has unexpected size % instead of 4", size_of(type_of(Oga_Device_Limits.supported_sample_counts_fbuffer_int)));
        assert(((cast(*void)(*instance.memory_granularity)) - cast(*void)(*instance)) == 264, "Oga_Device_Limits.memory_granularity has unexpected offset % instead of 264", ((cast(*void)(*instance.memory_granularity)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.memory_granularity)) == 8, "Oga_Device_Limits.memory_granularity has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.memory_granularity)));
        assert(((cast(*void)(*instance.image_memory_granularity)) - cast(*void)(*instance)) == 272, "Oga_Device_Limits.image_memory_granularity has unexpected offset % instead of 272", ((cast(*void)(*instance.image_memory_granularity)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.image_memory_granularity)) == 8, "Oga_Device_Limits.image_memory_granularity has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.image_memory_granularity)));
        assert(((cast(*void)(*instance.fbuffer_memory_granularity)) - cast(*void)(*instance)) == 280, "Oga_Device_Limits.fbuffer_memory_granularity has unexpected offset % instead of 280", ((cast(*void)(*instance.fbuffer_memory_granularity)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device_Limits.fbuffer_memory_granularity)) == 8, "Oga_Device_Limits.fbuffer_memory_granularity has unexpected size % instead of 8", size_of(type_of(Oga_Device_Limits.fbuffer_memory_granularity)));
        assert(size_of(Oga_Device_Limits) == 288, "Oga_Device_Limits has size % instead of 288", size_of(Oga_Device_Limits));
    }

    {
        instance: Oga_Device;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Device.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.id)) == 8, "Oga_Device.id has unexpected size % instead of 8", size_of(type_of(Oga_Device.id)));
        assert(((cast(*void)(*instance.kind)) - cast(*void)(*instance)) == 8, "Oga_Device.kind has unexpected offset % instead of 8", ((cast(*void)(*instance.kind)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.kind)) == 4, "Oga_Device.kind has unexpected size % instead of 4", size_of(type_of(Oga_Device.kind)));
        assert(((cast(*void)(*instance.device_name_data)) - cast(*void)(*instance)) == 12, "Oga_Device.device_name_data has unexpected offset % instead of 12", ((cast(*void)(*instance.device_name_data)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.device_name_data)) == 256, "Oga_Device.device_name_data has unexpected size % instead of 256", size_of(type_of(Oga_Device.device_name_data)));
        assert(((cast(*void)(*instance.device_name_length)) - cast(*void)(*instance)) == 272, "Oga_Device.device_name_length has unexpected offset % instead of 272", ((cast(*void)(*instance.device_name_length)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.device_name_length)) == 8, "Oga_Device.device_name_length has unexpected size % instead of 8", size_of(type_of(Oga_Device.device_name_length)));
        assert(((cast(*void)(*instance.vendor_id)) - cast(*void)(*instance)) == 280, "Oga_Device.vendor_id has unexpected offset % instead of 280", ((cast(*void)(*instance.vendor_id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.vendor_id)) == 8, "Oga_Device.vendor_id has unexpected size % instead of 8", size_of(type_of(Oga_Device.vendor_id)));
        assert(((cast(*void)(*instance.vendor_name)) - cast(*void)(*instance)) == 288, "Oga_Device.vendor_name has unexpected offset % instead of 288", ((cast(*void)(*instance.vendor_name)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.vendor_name)) == 16, "Oga_Device.vendor_name has unexpected size % instead of 16", size_of(type_of(Oga_Device.vendor_name)));
        assert(((cast(*void)(*instance.driver_version_raw)) - cast(*void)(*instance)) == 304, "Oga_Device.driver_version_raw has unexpected offset % instead of 304", ((cast(*void)(*instance.driver_version_raw)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.driver_version_raw)) == 4, "Oga_Device.driver_version_raw has unexpected size % instead of 4", size_of(type_of(Oga_Device.driver_version_raw)));
        assert(((cast(*void)(*instance.driver_version_data)) - cast(*void)(*instance)) == 308, "Oga_Device.driver_version_data has unexpected offset % instead of 308", ((cast(*void)(*instance.driver_version_data)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.driver_version_data)) == 128, "Oga_Device.driver_version_data has unexpected size % instead of 128", size_of(type_of(Oga_Device.driver_version_data)));
        assert(((cast(*void)(*instance.driver_version_length)) - cast(*void)(*instance)) == 440, "Oga_Device.driver_version_length has unexpected offset % instead of 440", ((cast(*void)(*instance.driver_version_length)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.driver_version_length)) == 8, "Oga_Device.driver_version_length has unexpected size % instead of 8", size_of(type_of(Oga_Device.driver_version_length)));
        assert(((cast(*void)(*instance.api_version_raw)) - cast(*void)(*instance)) == 448, "Oga_Device.api_version_raw has unexpected offset % instead of 448", ((cast(*void)(*instance.api_version_raw)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.api_version_raw)) == 4, "Oga_Device.api_version_raw has unexpected size % instead of 4", size_of(type_of(Oga_Device.api_version_raw)));
        assert(((cast(*void)(*instance.api_version_data)) - cast(*void)(*instance)) == 452, "Oga_Device.api_version_data has unexpected offset % instead of 452", ((cast(*void)(*instance.api_version_data)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.api_version_data)) == 128, "Oga_Device.api_version_data has unexpected size % instead of 128", size_of(type_of(Oga_Device.api_version_data)));
        assert(((cast(*void)(*instance.api_version_length)) - cast(*void)(*instance)) == 584, "Oga_Device.api_version_length has unexpected offset % instead of 584", ((cast(*void)(*instance.api_version_length)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.api_version_length)) == 8, "Oga_Device.api_version_length has unexpected size % instead of 8", size_of(type_of(Oga_Device.api_version_length)));
        assert(((cast(*void)(*instance.limits)) - cast(*void)(*instance)) == 592, "Oga_Device.limits has unexpected offset % instead of 592", ((cast(*void)(*instance.limits)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.limits)) == 288, "Oga_Device.limits has unexpected size % instead of 288", size_of(type_of(Oga_Device.limits)));
        assert(((cast(*void)(*instance.engine_family_infos)) - cast(*void)(*instance)) == 880, "Oga_Device.engine_family_infos has unexpected offset % instead of 880", ((cast(*void)(*instance.engine_family_infos)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.engine_family_infos)) == 256, "Oga_Device.engine_family_infos has unexpected size % instead of 256", size_of(type_of(Oga_Device.engine_family_infos)));
        assert(((cast(*void)(*instance.engine_family_count)) - cast(*void)(*instance)) == 1136, "Oga_Device.engine_family_count has unexpected offset % instead of 1136", ((cast(*void)(*instance.engine_family_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.engine_family_count)) == 4, "Oga_Device.engine_family_count has unexpected size % instead of 4", size_of(type_of(Oga_Device.engine_family_count)));
        assert(((cast(*void)(*instance.depth_format)) - cast(*void)(*instance)) == 1140, "Oga_Device.depth_format has unexpected offset % instead of 1140", ((cast(*void)(*instance.depth_format)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.depth_format)) == 4, "Oga_Device.depth_format has unexpected size % instead of 4", size_of(type_of(Oga_Device.depth_format)));
        assert(((cast(*void)(*instance.memory_heaps)) - cast(*void)(*instance)) == 1144, "Oga_Device.memory_heaps has unexpected offset % instead of 1144", ((cast(*void)(*instance.memory_heaps)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.memory_heaps)) == 768, "Oga_Device.memory_heaps has unexpected size % instead of 768", size_of(type_of(Oga_Device.memory_heaps)));
        assert(((cast(*void)(*instance.memory_heap_count)) - cast(*void)(*instance)) == 1912, "Oga_Device.memory_heap_count has unexpected offset % instead of 1912", ((cast(*void)(*instance.memory_heap_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.memory_heap_count)) == 8, "Oga_Device.memory_heap_count has unexpected size % instead of 8", size_of(type_of(Oga_Device.memory_heap_count)));
        assert(((cast(*void)(*instance.total_gpu_local_memory)) - cast(*void)(*instance)) == 1920, "Oga_Device.total_gpu_local_memory has unexpected offset % instead of 1920", ((cast(*void)(*instance.total_gpu_local_memory)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.total_gpu_local_memory)) == 8, "Oga_Device.total_gpu_local_memory has unexpected size % instead of 8", size_of(type_of(Oga_Device.total_gpu_local_memory)));
        assert(((cast(*void)(*instance.features)) - cast(*void)(*instance)) == 1928, "Oga_Device.features has unexpected offset % instead of 1928", ((cast(*void)(*instance.features)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.features)) == 8, "Oga_Device.features has unexpected size % instead of 8", size_of(type_of(Oga_Device.features)));
        assert(((cast(*void)(*instance.supported_surface_formats)) - cast(*void)(*instance)) == 1936, "Oga_Device.supported_surface_formats has unexpected offset % instead of 1936", ((cast(*void)(*instance.supported_surface_formats)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.supported_surface_formats)) == 316, "Oga_Device.supported_surface_formats has unexpected size % instead of 316", size_of(type_of(Oga_Device.supported_surface_formats)));
        assert(((cast(*void)(*instance.supported_surface_format_count)) - cast(*void)(*instance)) == 2256, "Oga_Device.supported_surface_format_count has unexpected offset % instead of 2256", ((cast(*void)(*instance.supported_surface_format_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Device.supported_surface_format_count)) == 8, "Oga_Device.supported_surface_format_count has unexpected size % instead of 8", size_of(type_of(Oga_Device.supported_surface_format_count)));
        assert(size_of(Oga_Device) == 2264, "Oga_Device has size % instead of 2264", size_of(Oga_Device));
    }

    {
        instance: Oga_Pick_Device_Result;
        assert(((cast(*void)(*instance.passed)) - cast(*void)(*instance)) == 0, "Oga_Pick_Device_Result.passed has unexpected offset % instead of 0", ((cast(*void)(*instance.passed)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Pick_Device_Result.passed)) == 1, "Oga_Pick_Device_Result.passed has unexpected size % instead of 1", size_of(type_of(Oga_Pick_Device_Result.passed)));
        assert(((cast(*void)(*instance.device)) - cast(*void)(*instance)) == 8, "Oga_Pick_Device_Result.device has unexpected offset % instead of 8", ((cast(*void)(*instance.device)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Pick_Device_Result.device)) == 2264, "Oga_Pick_Device_Result.device has unexpected size % instead of 2264", size_of(type_of(Oga_Pick_Device_Result.device)));
        assert(((cast(*void)(*instance.failed_pick_flags)) - cast(*void)(*instance)) == 2272, "Oga_Pick_Device_Result.failed_pick_flags has unexpected offset % instead of 2272", ((cast(*void)(*instance.failed_pick_flags)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Pick_Device_Result.failed_pick_flags)) == 4, "Oga_Pick_Device_Result.failed_pick_flags has unexpected size % instead of 4", size_of(type_of(Oga_Pick_Device_Result.failed_pick_flags)));
        assert(((cast(*void)(*instance.failed_required_features)) - cast(*void)(*instance)) == 2280, "Oga_Pick_Device_Result.failed_required_features has unexpected offset % instead of 2280", ((cast(*void)(*instance.failed_required_features)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Pick_Device_Result.failed_required_features)) == 8, "Oga_Pick_Device_Result.failed_required_features has unexpected size % instead of 8", size_of(type_of(Oga_Pick_Device_Result.failed_required_features)));
        assert(((cast(*void)(*instance.failed_preferred_features)) - cast(*void)(*instance)) == 2288, "Oga_Pick_Device_Result.failed_preferred_features has unexpected offset % instead of 2288", ((cast(*void)(*instance.failed_preferred_features)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Pick_Device_Result.failed_preferred_features)) == 8, "Oga_Pick_Device_Result.failed_preferred_features has unexpected size % instead of 8", size_of(type_of(Oga_Pick_Device_Result.failed_preferred_features)));
        assert(size_of(Oga_Pick_Device_Result) == 2296, "Oga_Pick_Device_Result has size % instead of 2296", size_of(Oga_Pick_Device_Result));
    }

    {
        instance: Oga_Logical_Engines_Create_Desc;
        assert(((cast(*void)(*instance.count)) - cast(*void)(*instance)) == 0, "Oga_Logical_Engines_Create_Desc.count has unexpected offset % instead of 0", ((cast(*void)(*instance.count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Logical_Engines_Create_Desc.count)) == 4, "Oga_Logical_Engines_Create_Desc.count has unexpected size % instead of 4", size_of(type_of(Oga_Logical_Engines_Create_Desc.count)));
        assert(((cast(*void)(*instance.priorities)) - cast(*void)(*instance)) == 4, "Oga_Logical_Engines_Create_Desc.priorities has unexpected offset % instead of 4", ((cast(*void)(*instance.priorities)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Logical_Engines_Create_Desc.priorities)) == 128, "Oga_Logical_Engines_Create_Desc.priorities has unexpected size % instead of 128", size_of(type_of(Oga_Logical_Engines_Create_Desc.priorities)));
        assert(size_of(Oga_Logical_Engines_Create_Desc) == 132, "Oga_Logical_Engines_Create_Desc has size % instead of 132", size_of(Oga_Logical_Engines_Create_Desc));
    }

    {
        instance: Oga_Allocator_Row;
        assert(((cast(*void)(*instance.start)) - cast(*void)(*instance)) == 0, "Oga_Allocator_Row.start has unexpected offset % instead of 0", ((cast(*void)(*instance.start)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Allocator_Row.start)) == 8, "Oga_Allocator_Row.start has unexpected size % instead of 8", size_of(type_of(Oga_Allocator_Row.start)));
        assert(((cast(*void)(*instance.end)) - cast(*void)(*instance)) == 8, "Oga_Allocator_Row.end has unexpected offset % instead of 8", ((cast(*void)(*instance.end)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Allocator_Row.end)) == 8, "Oga_Allocator_Row.end has unexpected size % instead of 8", size_of(type_of(Oga_Allocator_Row.end)));
        assert(((cast(*void)(*instance.first_free_index)) - cast(*void)(*instance)) == 16, "Oga_Allocator_Row.first_free_index has unexpected offset % instead of 16", ((cast(*void)(*instance.first_free_index)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Allocator_Row.first_free_index)) == 8, "Oga_Allocator_Row.first_free_index has unexpected size % instead of 8", size_of(type_of(Oga_Allocator_Row.first_free_index)));
        assert(((cast(*void)(*instance.highest_allocated_index)) - cast(*void)(*instance)) == 24, "Oga_Allocator_Row.highest_allocated_index has unexpected offset % instead of 24", ((cast(*void)(*instance.highest_allocated_index)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Allocator_Row.highest_allocated_index)) == 8, "Oga_Allocator_Row.highest_allocated_index has unexpected size % instead of 8", size_of(type_of(Oga_Allocator_Row.highest_allocated_index)));
        assert(size_of(Oga_Allocator_Row) == 32, "Oga_Allocator_Row has size % instead of 32", size_of(Oga_Allocator_Row));
    }

    {
        instance: Oga_State_Allocator_Data;
        assert(((cast(*void)(*instance.rows)) - cast(*void)(*instance)) == 0, "Oga_State_Allocator_Data.rows has unexpected offset % instead of 0", ((cast(*void)(*instance.rows)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_State_Allocator_Data.rows)) == 352, "Oga_State_Allocator_Data.rows has unexpected size % instead of 352", size_of(type_of(Oga_State_Allocator_Data.rows)));
        assert(size_of(Oga_State_Allocator_Data) == 352, "Oga_State_Allocator_Data has size % instead of 352", size_of(Oga_State_Allocator_Data));
    }

    {
        instance: Oga_Context_Desc;
        assert(((cast(*void)(*instance.engine_create_descs)) - cast(*void)(*instance)) == 0, "Oga_Context_Desc.engine_create_descs has unexpected offset % instead of 0", ((cast(*void)(*instance.engine_create_descs)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Context_Desc.engine_create_descs)) == 4224, "Oga_Context_Desc.engine_create_descs has unexpected size % instead of 4224", size_of(type_of(Oga_Context_Desc.engine_create_descs)));
        assert(((cast(*void)(*instance.enabled_features)) - cast(*void)(*instance)) == 4224, "Oga_Context_Desc.enabled_features has unexpected offset % instead of 4224", ((cast(*void)(*instance.enabled_features)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Context_Desc.enabled_features)) == 8, "Oga_Context_Desc.enabled_features has unexpected size % instead of 8", size_of(type_of(Oga_Context_Desc.enabled_features)));
        assert(((cast(*void)(*instance.state_allocator)) - cast(*void)(*instance)) == 4232, "Oga_Context_Desc.state_allocator has unexpected offset % instead of 4232", ((cast(*void)(*instance.state_allocator)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Context_Desc.state_allocator)) == 16, "Oga_Context_Desc.state_allocator has unexpected size % instead of 16", size_of(type_of(Oga_Context_Desc.state_allocator)));
        assert(size_of(Oga_Context_Desc) == 4248, "Oga_Context_Desc has size % instead of 4248", size_of(Oga_Context_Desc));
    }

    {
        instance: Oga_Logical_Engine;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Logical_Engine.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Logical_Engine.id)) == 8, "Oga_Logical_Engine.id has unexpected size % instead of 8", size_of(type_of(Oga_Logical_Engine.id)));
        assert(((cast(*void)(*instance.index)) - cast(*void)(*instance)) == 8, "Oga_Logical_Engine.index has unexpected offset % instead of 8", ((cast(*void)(*instance.index)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Logical_Engine.index)) == 4, "Oga_Logical_Engine.index has unexpected size % instead of 4", size_of(type_of(Oga_Logical_Engine.index)));
        assert(size_of(Oga_Logical_Engine) == 16, "Oga_Logical_Engine has size % instead of 16", size_of(Oga_Logical_Engine));
    }

    {
        instance: Oga_Logical_Engine_Group;
        assert(((cast(*void)(*instance.engines)) - cast(*void)(*instance)) == 0, "Oga_Logical_Engine_Group.engines has unexpected offset % instead of 0", ((cast(*void)(*instance.engines)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Logical_Engine_Group.engines)) == 512, "Oga_Logical_Engine_Group.engines has unexpected size % instead of 512", size_of(type_of(Oga_Logical_Engine_Group.engines)));
        assert(((cast(*void)(*instance.engine_count)) - cast(*void)(*instance)) == 512, "Oga_Logical_Engine_Group.engine_count has unexpected offset % instead of 512", ((cast(*void)(*instance.engine_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Logical_Engine_Group.engine_count)) == 8, "Oga_Logical_Engine_Group.engine_count has unexpected size % instead of 8", size_of(type_of(Oga_Logical_Engine_Group.engine_count)));
        assert(size_of(Oga_Logical_Engine_Group) == 520, "Oga_Logical_Engine_Group has size % instead of 520", size_of(Oga_Logical_Engine_Group));
    }

    {
        instance: Oga_Context;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Context.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Context.id)) == 8, "Oga_Context.id has unexpected size % instead of 8", size_of(type_of(Oga_Context.id)));
        assert(((cast(*void)(*instance.internal)) - cast(*void)(*instance)) == 8, "Oga_Context.internal has unexpected offset % instead of 8", ((cast(*void)(*instance.internal)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Context.internal)) == 8, "Oga_Context.internal has unexpected size % instead of 8", size_of(type_of(Oga_Context.internal)));
        assert(((cast(*void)(*instance.device)) - cast(*void)(*instance)) == 16, "Oga_Context.device has unexpected offset % instead of 16", ((cast(*void)(*instance.device)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Context.device)) == 2264, "Oga_Context.device has unexpected size % instead of 2264", size_of(type_of(Oga_Context.device)));
        assert(((cast(*void)(*instance.engines_by_family)) - cast(*void)(*instance)) == 2280, "Oga_Context.engines_by_family has unexpected offset % instead of 2280", ((cast(*void)(*instance.engines_by_family)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Context.engines_by_family)) == 16640, "Oga_Context.engines_by_family has unexpected size % instead of 16640", size_of(type_of(Oga_Context.engines_by_family)));
        assert(((cast(*void)(*instance.state_allocator)) - cast(*void)(*instance)) == 18920, "Oga_Context.state_allocator has unexpected offset % instead of 18920", ((cast(*void)(*instance.state_allocator)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Context.state_allocator)) == 16, "Oga_Context.state_allocator has unexpected size % instead of 16", size_of(type_of(Oga_Context.state_allocator)));
        assert(((cast(*void)(*instance.default_allocator_data)) - cast(*void)(*instance)) == 18936, "Oga_Context.default_allocator_data has unexpected offset % instead of 18936", ((cast(*void)(*instance.default_allocator_data)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Context.default_allocator_data)) == 352, "Oga_Context.default_allocator_data has unexpected size % instead of 352", size_of(type_of(Oga_Context.default_allocator_data)));
        assert(size_of(Oga_Context) == 19288, "Oga_Context has size % instead of 19288", size_of(Oga_Context));
    }

    {
        instance: Oga_Swapchain_Desc;
        assert(((cast(*void)(*instance.surface)) - cast(*void)(*instance)) == 0, "Oga_Swapchain_Desc.surface has unexpected offset % instead of 0", ((cast(*void)(*instance.surface)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Swapchain_Desc.surface)) == 8, "Oga_Swapchain_Desc.surface has unexpected size % instead of 8", size_of(type_of(Oga_Swapchain_Desc.surface)));
        assert(((cast(*void)(*instance.requested_image_count)) - cast(*void)(*instance)) == 8, "Oga_Swapchain_Desc.requested_image_count has unexpected offset % instead of 8", ((cast(*void)(*instance.requested_image_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Swapchain_Desc.requested_image_count)) == 8, "Oga_Swapchain_Desc.requested_image_count has unexpected size % instead of 8", size_of(type_of(Oga_Swapchain_Desc.requested_image_count)));
        assert(((cast(*void)(*instance.image_format)) - cast(*void)(*instance)) == 16, "Oga_Swapchain_Desc.image_format has unexpected offset % instead of 16", ((cast(*void)(*instance.image_format)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Swapchain_Desc.image_format)) == 4, "Oga_Swapchain_Desc.image_format has unexpected size % instead of 4", size_of(type_of(Oga_Swapchain_Desc.image_format)));
        assert(((cast(*void)(*instance.width)) - cast(*void)(*instance)) == 24, "Oga_Swapchain_Desc.width has unexpected offset % instead of 24", ((cast(*void)(*instance.width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Swapchain_Desc.width)) == 8, "Oga_Swapchain_Desc.width has unexpected size % instead of 8", size_of(type_of(Oga_Swapchain_Desc.width)));
        assert(((cast(*void)(*instance.height)) - cast(*void)(*instance)) == 32, "Oga_Swapchain_Desc.height has unexpected offset % instead of 32", ((cast(*void)(*instance.height)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Swapchain_Desc.height)) == 8, "Oga_Swapchain_Desc.height has unexpected size % instead of 8", size_of(type_of(Oga_Swapchain_Desc.height)));
        assert(((cast(*void)(*instance.present_mode)) - cast(*void)(*instance)) == 40, "Oga_Swapchain_Desc.present_mode has unexpected offset % instead of 40", ((cast(*void)(*instance.present_mode)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Swapchain_Desc.present_mode)) == 4, "Oga_Swapchain_Desc.present_mode has unexpected size % instead of 4", size_of(type_of(Oga_Swapchain_Desc.present_mode)));
        assert(((cast(*void)(*instance.graphics_engine_family_index)) - cast(*void)(*instance)) == 48, "Oga_Swapchain_Desc.graphics_engine_family_index has unexpected offset % instead of 48", ((cast(*void)(*instance.graphics_engine_family_index)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Swapchain_Desc.graphics_engine_family_index)) == 8, "Oga_Swapchain_Desc.graphics_engine_family_index has unexpected size % instead of 8", size_of(type_of(Oga_Swapchain_Desc.graphics_engine_family_index)));
        assert(size_of(Oga_Swapchain_Desc) == 56, "Oga_Swapchain_Desc has size % instead of 56", size_of(Oga_Swapchain_Desc));
    }

    {
        instance: Oga_Swapchain;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Swapchain.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Swapchain.id)) == 8, "Oga_Swapchain.id has unexpected size % instead of 8", size_of(type_of(Oga_Swapchain.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Swapchain._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Swapchain._context)) == 8, "Oga_Swapchain._context has unexpected size % instead of 8", size_of(type_of(Oga_Swapchain._context)));
        assert(((cast(*void)(*instance.images)) - cast(*void)(*instance)) == 16, "Oga_Swapchain.images has unexpected offset % instead of 16", ((cast(*void)(*instance.images)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Swapchain.images)) == 128, "Oga_Swapchain.images has unexpected size % instead of 128", size_of(type_of(Oga_Swapchain.images)));
        assert(((cast(*void)(*instance.current_image_index)) - cast(*void)(*instance)) == 144, "Oga_Swapchain.current_image_index has unexpected offset % instead of 144", ((cast(*void)(*instance.current_image_index)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Swapchain.current_image_index)) == 8, "Oga_Swapchain.current_image_index has unexpected size % instead of 8", size_of(type_of(Oga_Swapchain.current_image_index)));
        assert(((cast(*void)(*instance.image_count)) - cast(*void)(*instance)) == 152, "Oga_Swapchain.image_count has unexpected offset % instead of 152", ((cast(*void)(*instance.image_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Swapchain.image_count)) == 8, "Oga_Swapchain.image_count has unexpected size % instead of 8", size_of(type_of(Oga_Swapchain.image_count)));
        assert(((cast(*void)(*instance.image_format)) - cast(*void)(*instance)) == 160, "Oga_Swapchain.image_format has unexpected offset % instead of 160", ((cast(*void)(*instance.image_format)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Swapchain.image_format)) == 4, "Oga_Swapchain.image_format has unexpected size % instead of 4", size_of(type_of(Oga_Swapchain.image_format)));
        assert(size_of(Oga_Swapchain) == 168, "Oga_Swapchain has size % instead of 168", size_of(Oga_Swapchain));
    }

    {
        instance: Oga_Present_Desc;
        assert(((cast(*void)(*instance.engine)) - cast(*void)(*instance)) == 0, "Oga_Present_Desc.engine has unexpected offset % instead of 0", ((cast(*void)(*instance.engine)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Present_Desc.engine)) == 16, "Oga_Present_Desc.engine has unexpected size % instead of 16", size_of(type_of(Oga_Present_Desc.engine)));
        assert(((cast(*void)(*instance.wait_gpu_latch_count)) - cast(*void)(*instance)) == 16, "Oga_Present_Desc.wait_gpu_latch_count has unexpected offset % instead of 16", ((cast(*void)(*instance.wait_gpu_latch_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Present_Desc.wait_gpu_latch_count)) == 8, "Oga_Present_Desc.wait_gpu_latch_count has unexpected size % instead of 8", size_of(type_of(Oga_Present_Desc.wait_gpu_latch_count)));
        assert(((cast(*void)(*instance.wait_gpu_latches)) - cast(*void)(*instance)) == 24, "Oga_Present_Desc.wait_gpu_latches has unexpected offset % instead of 24", ((cast(*void)(*instance.wait_gpu_latches)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Present_Desc.wait_gpu_latches)) == 8, "Oga_Present_Desc.wait_gpu_latches has unexpected size % instead of 8", size_of(type_of(Oga_Present_Desc.wait_gpu_latches)));
        assert(((cast(*void)(*instance.image_index)) - cast(*void)(*instance)) == 32, "Oga_Present_Desc.image_index has unexpected offset % instead of 32", ((cast(*void)(*instance.image_index)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Present_Desc.image_index)) == 8, "Oga_Present_Desc.image_index has unexpected size % instead of 8", size_of(type_of(Oga_Present_Desc.image_index)));
        assert(size_of(Oga_Present_Desc) == 40, "Oga_Present_Desc has size % instead of 40", size_of(Oga_Present_Desc));
    }

    {
        instance: Oga_Program_Desc;
        assert(((cast(*void)(*instance.code)) - cast(*void)(*instance)) == 0, "Oga_Program_Desc.code has unexpected offset % instead of 0", ((cast(*void)(*instance.code)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Program_Desc.code)) == 8, "Oga_Program_Desc.code has unexpected size % instead of 8", size_of(type_of(Oga_Program_Desc.code)));
        assert(((cast(*void)(*instance.code_size)) - cast(*void)(*instance)) == 8, "Oga_Program_Desc.code_size has unexpected offset % instead of 8", ((cast(*void)(*instance.code_size)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Program_Desc.code_size)) == 8, "Oga_Program_Desc.code_size has unexpected size % instead of 8", size_of(type_of(Oga_Program_Desc.code_size)));
        assert(((cast(*void)(*instance.kind)) - cast(*void)(*instance)) == 16, "Oga_Program_Desc.kind has unexpected offset % instead of 16", ((cast(*void)(*instance.kind)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Program_Desc.kind)) == 4, "Oga_Program_Desc.kind has unexpected size % instead of 4", size_of(type_of(Oga_Program_Desc.kind)));
        assert(size_of(Oga_Program_Desc) == 24, "Oga_Program_Desc has size % instead of 24", size_of(Oga_Program_Desc));
    }

    {
        instance: Oga_Program;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Program.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Program.id)) == 8, "Oga_Program.id has unexpected size % instead of 8", size_of(type_of(Oga_Program.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Program._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Program._context)) == 8, "Oga_Program._context has unexpected size % instead of 8", size_of(type_of(Oga_Program._context)));
        assert(((cast(*void)(*instance.kind)) - cast(*void)(*instance)) == 16, "Oga_Program.kind has unexpected offset % instead of 16", ((cast(*void)(*instance.kind)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Program.kind)) == 4, "Oga_Program.kind has unexpected size % instead of 4", size_of(type_of(Oga_Program.kind)));
        assert(size_of(Oga_Program) == 24, "Oga_Program has size % instead of 24", size_of(Oga_Program));
    }

    {
        instance: Oga_Sample_Mode_Desc;
        assert(((cast(*void)(*instance.magnification_filter)) - cast(*void)(*instance)) == 0, "Oga_Sample_Mode_Desc.magnification_filter has unexpected offset % instead of 0", ((cast(*void)(*instance.magnification_filter)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Sample_Mode_Desc.magnification_filter)) == 4, "Oga_Sample_Mode_Desc.magnification_filter has unexpected size % instead of 4", size_of(type_of(Oga_Sample_Mode_Desc.magnification_filter)));
        assert(((cast(*void)(*instance.minification_filter)) - cast(*void)(*instance)) == 4, "Oga_Sample_Mode_Desc.minification_filter has unexpected offset % instead of 4", ((cast(*void)(*instance.minification_filter)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Sample_Mode_Desc.minification_filter)) == 4, "Oga_Sample_Mode_Desc.minification_filter has unexpected size % instead of 4", size_of(type_of(Oga_Sample_Mode_Desc.minification_filter)));
        assert(((cast(*void)(*instance.address_mode_u)) - cast(*void)(*instance)) == 8, "Oga_Sample_Mode_Desc.address_mode_u has unexpected offset % instead of 8", ((cast(*void)(*instance.address_mode_u)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Sample_Mode_Desc.address_mode_u)) == 4, "Oga_Sample_Mode_Desc.address_mode_u has unexpected size % instead of 4", size_of(type_of(Oga_Sample_Mode_Desc.address_mode_u)));
        assert(((cast(*void)(*instance.address_mode_v)) - cast(*void)(*instance)) == 12, "Oga_Sample_Mode_Desc.address_mode_v has unexpected offset % instead of 12", ((cast(*void)(*instance.address_mode_v)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Sample_Mode_Desc.address_mode_v)) == 4, "Oga_Sample_Mode_Desc.address_mode_v has unexpected size % instead of 4", size_of(type_of(Oga_Sample_Mode_Desc.address_mode_v)));
        assert(((cast(*void)(*instance.address_mode_w)) - cast(*void)(*instance)) == 16, "Oga_Sample_Mode_Desc.address_mode_w has unexpected offset % instead of 16", ((cast(*void)(*instance.address_mode_w)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Sample_Mode_Desc.address_mode_w)) == 4, "Oga_Sample_Mode_Desc.address_mode_w has unexpected size % instead of 4", size_of(type_of(Oga_Sample_Mode_Desc.address_mode_w)));
        assert(((cast(*void)(*instance.max_anisotropy)) - cast(*void)(*instance)) == 20, "Oga_Sample_Mode_Desc.max_anisotropy has unexpected offset % instead of 20", ((cast(*void)(*instance.max_anisotropy)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Sample_Mode_Desc.max_anisotropy)) == 4, "Oga_Sample_Mode_Desc.max_anisotropy has unexpected size % instead of 4", size_of(type_of(Oga_Sample_Mode_Desc.max_anisotropy)));
        assert(size_of(Oga_Sample_Mode_Desc) == 24, "Oga_Sample_Mode_Desc has size % instead of 24", size_of(Oga_Sample_Mode_Desc));
    }

    {
        instance: Oga_Binding_Layout_Entry_Desc;
        assert(((cast(*void)(*instance.kind)) - cast(*void)(*instance)) == 0, "Oga_Binding_Layout_Entry_Desc.kind has unexpected offset % instead of 0", ((cast(*void)(*instance.kind)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_Layout_Entry_Desc.kind)) == 4, "Oga_Binding_Layout_Entry_Desc.kind has unexpected size % instead of 4", size_of(type_of(Oga_Binding_Layout_Entry_Desc.kind)));
        assert(((cast(*void)(*instance.binding_slot)) - cast(*void)(*instance)) == 8, "Oga_Binding_Layout_Entry_Desc.binding_slot has unexpected offset % instead of 8", ((cast(*void)(*instance.binding_slot)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_Layout_Entry_Desc.binding_slot)) == 8, "Oga_Binding_Layout_Entry_Desc.binding_slot has unexpected size % instead of 8", size_of(type_of(Oga_Binding_Layout_Entry_Desc.binding_slot)));
        assert(((cast(*void)(*instance.binding_count)) - cast(*void)(*instance)) == 16, "Oga_Binding_Layout_Entry_Desc.binding_count has unexpected offset % instead of 16", ((cast(*void)(*instance.binding_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_Layout_Entry_Desc.binding_count)) == 8, "Oga_Binding_Layout_Entry_Desc.binding_count has unexpected size % instead of 8", size_of(type_of(Oga_Binding_Layout_Entry_Desc.binding_count)));
        assert(((cast(*void)(*instance.stage_flags)) - cast(*void)(*instance)) == 24, "Oga_Binding_Layout_Entry_Desc.stage_flags has unexpected offset % instead of 24", ((cast(*void)(*instance.stage_flags)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_Layout_Entry_Desc.stage_flags)) == 8, "Oga_Binding_Layout_Entry_Desc.stage_flags has unexpected size % instead of 8", size_of(type_of(Oga_Binding_Layout_Entry_Desc.stage_flags)));
        assert(size_of(Oga_Binding_Layout_Entry_Desc) == 32, "Oga_Binding_Layout_Entry_Desc has size % instead of 32", size_of(Oga_Binding_Layout_Entry_Desc));
    }

    {
        instance: Oga_Binding_List_Layout_Desc;
        assert(((cast(*void)(*instance.bindings)) - cast(*void)(*instance)) == 0, "Oga_Binding_List_Layout_Desc.bindings has unexpected offset % instead of 0", ((cast(*void)(*instance.bindings)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List_Layout_Desc.bindings)) == 8, "Oga_Binding_List_Layout_Desc.bindings has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List_Layout_Desc.bindings)));
        assert(((cast(*void)(*instance.binding_count)) - cast(*void)(*instance)) == 8, "Oga_Binding_List_Layout_Desc.binding_count has unexpected offset % instead of 8", ((cast(*void)(*instance.binding_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List_Layout_Desc.binding_count)) == 8, "Oga_Binding_List_Layout_Desc.binding_count has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List_Layout_Desc.binding_count)));
        assert(((cast(*void)(*instance.binding_list_count)) - cast(*void)(*instance)) == 16, "Oga_Binding_List_Layout_Desc.binding_list_count has unexpected offset % instead of 16", ((cast(*void)(*instance.binding_list_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List_Layout_Desc.binding_list_count)) == 8, "Oga_Binding_List_Layout_Desc.binding_list_count has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List_Layout_Desc.binding_list_count)));
        assert(size_of(Oga_Binding_List_Layout_Desc) == 24, "Oga_Binding_List_Layout_Desc has size % instead of 24", size_of(Oga_Binding_List_Layout_Desc));
    }

    {
        instance: Oga_Binding_List_Layout;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Binding_List_Layout.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List_Layout.id)) == 8, "Oga_Binding_List_Layout.id has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List_Layout.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Binding_List_Layout._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List_Layout._context)) == 8, "Oga_Binding_List_Layout._context has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List_Layout._context)));
        assert(((cast(*void)(*instance.bindings)) - cast(*void)(*instance)) == 16, "Oga_Binding_List_Layout.bindings has unexpected offset % instead of 16", ((cast(*void)(*instance.bindings)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List_Layout.bindings)) == 8, "Oga_Binding_List_Layout.bindings has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List_Layout.bindings)));
        assert(((cast(*void)(*instance.binding_count)) - cast(*void)(*instance)) == 24, "Oga_Binding_List_Layout.binding_count has unexpected offset % instead of 24", ((cast(*void)(*instance.binding_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List_Layout.binding_count)) == 8, "Oga_Binding_List_Layout.binding_count has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List_Layout.binding_count)));
        assert(((cast(*void)(*instance.binding_list_count)) - cast(*void)(*instance)) == 32, "Oga_Binding_List_Layout.binding_list_count has unexpected offset % instead of 32", ((cast(*void)(*instance.binding_list_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List_Layout.binding_list_count)) == 8, "Oga_Binding_List_Layout.binding_list_count has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List_Layout.binding_list_count)));
        assert(((cast(*void)(*instance.allocated_lists_count)) - cast(*void)(*instance)) == 40, "Oga_Binding_List_Layout.allocated_lists_count has unexpected offset % instead of 40", ((cast(*void)(*instance.allocated_lists_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List_Layout.allocated_lists_count)) == 8, "Oga_Binding_List_Layout.allocated_lists_count has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List_Layout.allocated_lists_count)));
        assert(size_of(Oga_Binding_List_Layout) == 48, "Oga_Binding_List_Layout has size % instead of 48", size_of(Oga_Binding_List_Layout));
    }

    {
        instance: Oga_Binding_Desc;
        assert(((cast(*void)(*instance.kind)) - cast(*void)(*instance)) == 0, "Oga_Binding_Desc.kind has unexpected offset % instead of 0", ((cast(*void)(*instance.kind)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_Desc.kind)) == 4, "Oga_Binding_Desc.kind has unexpected size % instead of 4", size_of(type_of(Oga_Binding_Desc.kind)));
        assert(((cast(*void)(*instance.binding_slot)) - cast(*void)(*instance)) == 8, "Oga_Binding_Desc.binding_slot has unexpected offset % instead of 8", ((cast(*void)(*instance.binding_slot)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_Desc.binding_slot)) == 8, "Oga_Binding_Desc.binding_slot has unexpected size % instead of 8", size_of(type_of(Oga_Binding_Desc.binding_slot)));
        assert(((cast(*void)(*instance.array_index)) - cast(*void)(*instance)) == 16, "Oga_Binding_Desc.array_index has unexpected offset % instead of 16", ((cast(*void)(*instance.array_index)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_Desc.array_index)) == 8, "Oga_Binding_Desc.array_index has unexpected size % instead of 8", size_of(type_of(Oga_Binding_Desc.array_index)));
        assert(((cast(*void)(*instance.count)) - cast(*void)(*instance)) == 24, "Oga_Binding_Desc.count has unexpected offset % instead of 24", ((cast(*void)(*instance.count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_Desc.count)) == 8, "Oga_Binding_Desc.count has unexpected size % instead of 8", size_of(type_of(Oga_Binding_Desc.count)));
        assert(((cast(*void)(*instance.images)) - cast(*void)(*instance)) == 32, "Oga_Binding_Desc.images has unexpected offset % instead of 32", ((cast(*void)(*instance.images)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_Desc.images)) == 8, "Oga_Binding_Desc.images has unexpected size % instead of 8", size_of(type_of(Oga_Binding_Desc.images)));
        assert(((cast(*void)(*instance.sample_modes)) - cast(*void)(*instance)) == 40, "Oga_Binding_Desc.sample_modes has unexpected offset % instead of 40", ((cast(*void)(*instance.sample_modes)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_Desc.sample_modes)) == 8, "Oga_Binding_Desc.sample_modes has unexpected size % instead of 8", size_of(type_of(Oga_Binding_Desc.sample_modes)));
        assert(((cast(*void)(*instance.blocks)) - cast(*void)(*instance)) == 48, "Oga_Binding_Desc.blocks has unexpected offset % instead of 48", ((cast(*void)(*instance.blocks)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_Desc.blocks)) == 8, "Oga_Binding_Desc.blocks has unexpected size % instead of 8", size_of(type_of(Oga_Binding_Desc.blocks)));
        assert(((cast(*void)(*instance.fbuffers)) - cast(*void)(*instance)) == 56, "Oga_Binding_Desc.fbuffers has unexpected offset % instead of 56", ((cast(*void)(*instance.fbuffers)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_Desc.fbuffers)) == 8, "Oga_Binding_Desc.fbuffers has unexpected size % instead of 8", size_of(type_of(Oga_Binding_Desc.fbuffers)));
        assert(size_of(Oga_Binding_Desc) == 64, "Oga_Binding_Desc has size % instead of 64", size_of(Oga_Binding_Desc));
    }

    {
        instance: Oga_Binding_List_Desc;
        assert(((cast(*void)(*instance.bindings)) - cast(*void)(*instance)) == 0, "Oga_Binding_List_Desc.bindings has unexpected offset % instead of 0", ((cast(*void)(*instance.bindings)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List_Desc.bindings)) == 8, "Oga_Binding_List_Desc.bindings has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List_Desc.bindings)));
        assert(((cast(*void)(*instance.binding_count)) - cast(*void)(*instance)) == 8, "Oga_Binding_List_Desc.binding_count has unexpected offset % instead of 8", ((cast(*void)(*instance.binding_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List_Desc.binding_count)) == 8, "Oga_Binding_List_Desc.binding_count has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List_Desc.binding_count)));
        assert(size_of(Oga_Binding_List_Desc) == 16, "Oga_Binding_List_Desc has size % instead of 16", size_of(Oga_Binding_List_Desc));
    }

    {
        instance: Oga_Binding_List;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Binding_List.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List.id)) == 8, "Oga_Binding_List.id has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Binding_List._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List._context)) == 8, "Oga_Binding_List._context has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List._context)));
        assert(((cast(*void)(*instance.layout)) - cast(*void)(*instance)) == 16, "Oga_Binding_List.layout has unexpected offset % instead of 16", ((cast(*void)(*instance.layout)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Binding_List.layout)) == 8, "Oga_Binding_List.layout has unexpected size % instead of 8", size_of(type_of(Oga_Binding_List.layout)));
        assert(size_of(Oga_Binding_List) == 24, "Oga_Binding_List has size % instead of 24", size_of(Oga_Binding_List));
    }

    {
        instance: Oga_Vertex_List_Binding_Desc;
        assert(((cast(*void)(*instance.stride)) - cast(*void)(*instance)) == 0, "Oga_Vertex_List_Binding_Desc.stride has unexpected offset % instead of 0", ((cast(*void)(*instance.stride)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_Binding_Desc.stride)) == 8, "Oga_Vertex_List_Binding_Desc.stride has unexpected size % instead of 8", size_of(type_of(Oga_Vertex_List_Binding_Desc.stride)));
        assert(((cast(*void)(*instance.input_rate)) - cast(*void)(*instance)) == 8, "Oga_Vertex_List_Binding_Desc.input_rate has unexpected offset % instead of 8", ((cast(*void)(*instance.input_rate)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_Binding_Desc.input_rate)) == 4, "Oga_Vertex_List_Binding_Desc.input_rate has unexpected size % instead of 4", size_of(type_of(Oga_Vertex_List_Binding_Desc.input_rate)));
        assert(size_of(Oga_Vertex_List_Binding_Desc) == 16, "Oga_Vertex_List_Binding_Desc has size % instead of 16", size_of(Oga_Vertex_List_Binding_Desc));
    }

    {
        instance: Oga_Vertex_List_Attribute_Desc;
        assert(((cast(*void)(*instance.binding)) - cast(*void)(*instance)) == 0, "Oga_Vertex_List_Attribute_Desc.binding has unexpected offset % instead of 0", ((cast(*void)(*instance.binding)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_Attribute_Desc.binding)) == 8, "Oga_Vertex_List_Attribute_Desc.binding has unexpected size % instead of 8", size_of(type_of(Oga_Vertex_List_Attribute_Desc.binding)));
        assert(((cast(*void)(*instance.location)) - cast(*void)(*instance)) == 8, "Oga_Vertex_List_Attribute_Desc.location has unexpected offset % instead of 8", ((cast(*void)(*instance.location)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_Attribute_Desc.location)) == 8, "Oga_Vertex_List_Attribute_Desc.location has unexpected size % instead of 8", size_of(type_of(Oga_Vertex_List_Attribute_Desc.location)));
        assert(((cast(*void)(*instance.offset)) - cast(*void)(*instance)) == 16, "Oga_Vertex_List_Attribute_Desc.offset has unexpected offset % instead of 16", ((cast(*void)(*instance.offset)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_Attribute_Desc.offset)) == 8, "Oga_Vertex_List_Attribute_Desc.offset has unexpected size % instead of 8", size_of(type_of(Oga_Vertex_List_Attribute_Desc.offset)));
        assert(((cast(*void)(*instance.type)) - cast(*void)(*instance)) == 24, "Oga_Vertex_List_Attribute_Desc.type has unexpected offset % instead of 24", ((cast(*void)(*instance.type)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_Attribute_Desc.type)) == 4, "Oga_Vertex_List_Attribute_Desc.type has unexpected size % instead of 4", size_of(type_of(Oga_Vertex_List_Attribute_Desc.type)));
        assert(size_of(Oga_Vertex_List_Attribute_Desc) == 32, "Oga_Vertex_List_Attribute_Desc has size % instead of 32", size_of(Oga_Vertex_List_Attribute_Desc));
    }

    {
        instance: Oga_Vertex_List_Layout_Desc;
        assert(((cast(*void)(*instance.bindings)) - cast(*void)(*instance)) == 0, "Oga_Vertex_List_Layout_Desc.bindings has unexpected offset % instead of 0", ((cast(*void)(*instance.bindings)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_Layout_Desc.bindings)) == 512, "Oga_Vertex_List_Layout_Desc.bindings has unexpected size % instead of 512", size_of(type_of(Oga_Vertex_List_Layout_Desc.bindings)));
        assert(((cast(*void)(*instance.binding_count)) - cast(*void)(*instance)) == 512, "Oga_Vertex_List_Layout_Desc.binding_count has unexpected offset % instead of 512", ((cast(*void)(*instance.binding_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_Layout_Desc.binding_count)) == 8, "Oga_Vertex_List_Layout_Desc.binding_count has unexpected size % instead of 8", size_of(type_of(Oga_Vertex_List_Layout_Desc.binding_count)));
        assert(((cast(*void)(*instance.attributes)) - cast(*void)(*instance)) == 520, "Oga_Vertex_List_Layout_Desc.attributes has unexpected offset % instead of 520", ((cast(*void)(*instance.attributes)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_Layout_Desc.attributes)) == 1024, "Oga_Vertex_List_Layout_Desc.attributes has unexpected size % instead of 1024", size_of(type_of(Oga_Vertex_List_Layout_Desc.attributes)));
        assert(((cast(*void)(*instance.attribute_count)) - cast(*void)(*instance)) == 1544, "Oga_Vertex_List_Layout_Desc.attribute_count has unexpected offset % instead of 1544", ((cast(*void)(*instance.attribute_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_Layout_Desc.attribute_count)) == 8, "Oga_Vertex_List_Layout_Desc.attribute_count has unexpected size % instead of 8", size_of(type_of(Oga_Vertex_List_Layout_Desc.attribute_count)));
        assert(size_of(Oga_Vertex_List_Layout_Desc) == 1552, "Oga_Vertex_List_Layout_Desc has size % instead of 1552", size_of(Oga_Vertex_List_Layout_Desc));
    }

    {
        instance: Oga_Render_Pass_Desc;
        assert(((cast(*void)(*instance.flags)) - cast(*void)(*instance)) == 0, "Oga_Render_Pass_Desc.flags has unexpected offset % instead of 0", ((cast(*void)(*instance.flags)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.flags)) == 8, "Oga_Render_Pass_Desc.flags has unexpected size % instead of 8", size_of(type_of(Oga_Render_Pass_Desc.flags)));
        assert(((cast(*void)(*instance.base)) - cast(*void)(*instance)) == 8, "Oga_Render_Pass_Desc.base has unexpected offset % instead of 8", ((cast(*void)(*instance.base)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.base)) == 8, "Oga_Render_Pass_Desc.base has unexpected size % instead of 8", size_of(type_of(Oga_Render_Pass_Desc.base)));
        assert(((cast(*void)(*instance.base_index)) - cast(*void)(*instance)) == 16, "Oga_Render_Pass_Desc.base_index has unexpected offset % instead of 16", ((cast(*void)(*instance.base_index)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.base_index)) == 8, "Oga_Render_Pass_Desc.base_index has unexpected size % instead of 8", size_of(type_of(Oga_Render_Pass_Desc.base_index)));
        assert(((cast(*void)(*instance.vertex_program)) - cast(*void)(*instance)) == 24, "Oga_Render_Pass_Desc.vertex_program has unexpected offset % instead of 24", ((cast(*void)(*instance.vertex_program)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.vertex_program)) == 8, "Oga_Render_Pass_Desc.vertex_program has unexpected size % instead of 8", size_of(type_of(Oga_Render_Pass_Desc.vertex_program)));
        assert(((cast(*void)(*instance.vertex_program_entry_point)) - cast(*void)(*instance)) == 32, "Oga_Render_Pass_Desc.vertex_program_entry_point has unexpected offset % instead of 32", ((cast(*void)(*instance.vertex_program_entry_point)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.vertex_program_entry_point)) == 16, "Oga_Render_Pass_Desc.vertex_program_entry_point has unexpected size % instead of 16", size_of(type_of(Oga_Render_Pass_Desc.vertex_program_entry_point)));
        assert(((cast(*void)(*instance.fragment_program)) - cast(*void)(*instance)) == 48, "Oga_Render_Pass_Desc.fragment_program has unexpected offset % instead of 48", ((cast(*void)(*instance.fragment_program)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.fragment_program)) == 8, "Oga_Render_Pass_Desc.fragment_program has unexpected size % instead of 8", size_of(type_of(Oga_Render_Pass_Desc.fragment_program)));
        assert(((cast(*void)(*instance.fragment_program_entry_point)) - cast(*void)(*instance)) == 56, "Oga_Render_Pass_Desc.fragment_program_entry_point has unexpected offset % instead of 56", ((cast(*void)(*instance.fragment_program_entry_point)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.fragment_program_entry_point)) == 16, "Oga_Render_Pass_Desc.fragment_program_entry_point has unexpected size % instead of 16", size_of(type_of(Oga_Render_Pass_Desc.fragment_program_entry_point)));
        assert(((cast(*void)(*instance.attachment_formats)) - cast(*void)(*instance)) == 72, "Oga_Render_Pass_Desc.attachment_formats has unexpected offset % instead of 72", ((cast(*void)(*instance.attachment_formats)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.attachment_formats)) == 8, "Oga_Render_Pass_Desc.attachment_formats has unexpected size % instead of 8", size_of(type_of(Oga_Render_Pass_Desc.attachment_formats)));
        assert(((cast(*void)(*instance.attachment_count)) - cast(*void)(*instance)) == 80, "Oga_Render_Pass_Desc.attachment_count has unexpected offset % instead of 80", ((cast(*void)(*instance.attachment_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.attachment_count)) == 8, "Oga_Render_Pass_Desc.attachment_count has unexpected size % instead of 8", size_of(type_of(Oga_Render_Pass_Desc.attachment_count)));
        assert(((cast(*void)(*instance.topology)) - cast(*void)(*instance)) == 88, "Oga_Render_Pass_Desc.topology has unexpected offset % instead of 88", ((cast(*void)(*instance.topology)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.topology)) == 4, "Oga_Render_Pass_Desc.topology has unexpected size % instead of 4", size_of(type_of(Oga_Render_Pass_Desc.topology)));
        assert(((cast(*void)(*instance.cull_mode)) - cast(*void)(*instance)) == 92, "Oga_Render_Pass_Desc.cull_mode has unexpected offset % instead of 92", ((cast(*void)(*instance.cull_mode)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.cull_mode)) == 4, "Oga_Render_Pass_Desc.cull_mode has unexpected size % instead of 4", size_of(type_of(Oga_Render_Pass_Desc.cull_mode)));
        assert(((cast(*void)(*instance.line_width)) - cast(*void)(*instance)) == 96, "Oga_Render_Pass_Desc.line_width has unexpected offset % instead of 96", ((cast(*void)(*instance.line_width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.line_width)) == 4, "Oga_Render_Pass_Desc.line_width has unexpected size % instead of 4", size_of(type_of(Oga_Render_Pass_Desc.line_width)));
        assert(((cast(*void)(*instance.rasterization_samples)) - cast(*void)(*instance)) == 100, "Oga_Render_Pass_Desc.rasterization_samples has unexpected offset % instead of 100", ((cast(*void)(*instance.rasterization_samples)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.rasterization_samples)) == 4, "Oga_Render_Pass_Desc.rasterization_samples has unexpected size % instead of 4", size_of(type_of(Oga_Render_Pass_Desc.rasterization_samples)));
        assert(((cast(*void)(*instance.vertex_input_layout)) - cast(*void)(*instance)) == 104, "Oga_Render_Pass_Desc.vertex_input_layout has unexpected offset % instead of 104", ((cast(*void)(*instance.vertex_input_layout)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.vertex_input_layout)) == 1552, "Oga_Render_Pass_Desc.vertex_input_layout has unexpected size % instead of 1552", size_of(type_of(Oga_Render_Pass_Desc.vertex_input_layout)));
        assert(((cast(*void)(*instance.binding_list_layout)) - cast(*void)(*instance)) == 1656, "Oga_Render_Pass_Desc.binding_list_layout has unexpected offset % instead of 1656", ((cast(*void)(*instance.binding_list_layout)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass_Desc.binding_list_layout)) == 8, "Oga_Render_Pass_Desc.binding_list_layout has unexpected size % instead of 8", size_of(type_of(Oga_Render_Pass_Desc.binding_list_layout)));
        assert(size_of(Oga_Render_Pass_Desc) == 1664, "Oga_Render_Pass_Desc has size % instead of 1664", size_of(Oga_Render_Pass_Desc));
    }

    {
        instance: Oga_Render_Pass;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Render_Pass.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass.id)) == 8, "Oga_Render_Pass.id has unexpected size % instead of 8", size_of(type_of(Oga_Render_Pass.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Render_Pass._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass._context)) == 8, "Oga_Render_Pass._context has unexpected size % instead of 8", size_of(type_of(Oga_Render_Pass._context)));
        assert(((cast(*void)(*instance.vertex_input_layout)) - cast(*void)(*instance)) == 16, "Oga_Render_Pass.vertex_input_layout has unexpected offset % instead of 16", ((cast(*void)(*instance.vertex_input_layout)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Pass.vertex_input_layout)) == 1552, "Oga_Render_Pass.vertex_input_layout has unexpected size % instead of 1552", size_of(type_of(Oga_Render_Pass.vertex_input_layout)));
        assert(size_of(Oga_Render_Pass) == 1568, "Oga_Render_Pass has size % instead of 1568", size_of(Oga_Render_Pass));
    }

    {
        instance: Oga_Gpu_Latch;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Gpu_Latch.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Gpu_Latch.id)) == 8, "Oga_Gpu_Latch.id has unexpected size % instead of 8", size_of(type_of(Oga_Gpu_Latch.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Gpu_Latch._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Gpu_Latch._context)) == 8, "Oga_Gpu_Latch._context has unexpected size % instead of 8", size_of(type_of(Oga_Gpu_Latch._context)));
        assert(size_of(Oga_Gpu_Latch) == 16, "Oga_Gpu_Latch has size % instead of 16", size_of(Oga_Gpu_Latch));
    }

    {
        instance: Oga_Cpu_Latch;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Cpu_Latch.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Cpu_Latch.id)) == 8, "Oga_Cpu_Latch.id has unexpected size % instead of 8", size_of(type_of(Oga_Cpu_Latch.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Cpu_Latch._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Cpu_Latch._context)) == 8, "Oga_Cpu_Latch._context has unexpected size % instead of 8", size_of(type_of(Oga_Cpu_Latch._context)));
        assert(size_of(Oga_Cpu_Latch) == 16, "Oga_Cpu_Latch has size % instead of 16", size_of(Oga_Cpu_Latch));
    }

    {
        instance: Oga_Memory_Pointer;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Memory_Pointer.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Memory_Pointer.id)) == 8, "Oga_Memory_Pointer.id has unexpected size % instead of 8", size_of(type_of(Oga_Memory_Pointer.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Memory_Pointer._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Memory_Pointer._context)) == 8, "Oga_Memory_Pointer._context has unexpected size % instead of 8", size_of(type_of(Oga_Memory_Pointer._context)));
        assert(((cast(*void)(*instance.offset)) - cast(*void)(*instance)) == 16, "Oga_Memory_Pointer.offset has unexpected offset % instead of 16", ((cast(*void)(*instance.offset)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Memory_Pointer.offset)) == 8, "Oga_Memory_Pointer.offset has unexpected size % instead of 8", size_of(type_of(Oga_Memory_Pointer.offset)));
        assert(((cast(*void)(*instance.size)) - cast(*void)(*instance)) == 24, "Oga_Memory_Pointer.size has unexpected offset % instead of 24", ((cast(*void)(*instance.size)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Memory_Pointer.size)) == 8, "Oga_Memory_Pointer.size has unexpected size % instead of 8", size_of(type_of(Oga_Memory_Pointer.size)));
        assert(((cast(*void)(*instance.heap_index)) - cast(*void)(*instance)) == 32, "Oga_Memory_Pointer.heap_index has unexpected offset % instead of 32", ((cast(*void)(*instance.heap_index)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Memory_Pointer.heap_index)) == 8, "Oga_Memory_Pointer.heap_index has unexpected size % instead of 8", size_of(type_of(Oga_Memory_Pointer.heap_index)));
        assert(((cast(*void)(*instance.properties)) - cast(*void)(*instance)) == 40, "Oga_Memory_Pointer.properties has unexpected offset % instead of 40", ((cast(*void)(*instance.properties)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Memory_Pointer.properties)) == 8, "Oga_Memory_Pointer.properties has unexpected size % instead of 8", size_of(type_of(Oga_Memory_Pointer.properties)));
        assert(((cast(*void)(*instance.usage)) - cast(*void)(*instance)) == 48, "Oga_Memory_Pointer.usage has unexpected offset % instead of 48", ((cast(*void)(*instance.usage)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Memory_Pointer.usage)) == 8, "Oga_Memory_Pointer.usage has unexpected size % instead of 8", size_of(type_of(Oga_Memory_Pointer.usage)));
        assert(size_of(Oga_Memory_Pointer) == 56, "Oga_Memory_Pointer has size % instead of 56", size_of(Oga_Memory_Pointer));
    }

    {
        instance: Oga_Memory_View_Desc;
        assert(((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)) == 0, "Oga_Memory_View_Desc.memory_pointer has unexpected offset % instead of 0", ((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Memory_View_Desc.memory_pointer)) == 56, "Oga_Memory_View_Desc.memory_pointer has unexpected size % instead of 56", size_of(type_of(Oga_Memory_View_Desc.memory_pointer)));
        assert(((cast(*void)(*instance.size)) - cast(*void)(*instance)) == 56, "Oga_Memory_View_Desc.size has unexpected offset % instead of 56", ((cast(*void)(*instance.size)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Memory_View_Desc.size)) == 8, "Oga_Memory_View_Desc.size has unexpected size % instead of 8", size_of(type_of(Oga_Memory_View_Desc.size)));
        assert(size_of(Oga_Memory_View_Desc) == 64, "Oga_Memory_View_Desc has size % instead of 64", size_of(Oga_Memory_View_Desc));
    }

    {
        instance: Oga_Vertex_List_View;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Vertex_List_View.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_View.id)) == 8, "Oga_Vertex_List_View.id has unexpected size % instead of 8", size_of(type_of(Oga_Vertex_List_View.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Vertex_List_View._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_View._context)) == 8, "Oga_Vertex_List_View._context has unexpected size % instead of 8", size_of(type_of(Oga_Vertex_List_View._context)));
        assert(((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)) == 16, "Oga_Vertex_List_View.memory_pointer has unexpected offset % instead of 16", ((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_View.memory_pointer)) == 56, "Oga_Vertex_List_View.memory_pointer has unexpected size % instead of 56", size_of(type_of(Oga_Vertex_List_View.memory_pointer)));
        assert(((cast(*void)(*instance.size)) - cast(*void)(*instance)) == 72, "Oga_Vertex_List_View.size has unexpected offset % instead of 72", ((cast(*void)(*instance.size)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Vertex_List_View.size)) == 8, "Oga_Vertex_List_View.size has unexpected size % instead of 8", size_of(type_of(Oga_Vertex_List_View.size)));
        assert(size_of(Oga_Vertex_List_View) == 80, "Oga_Vertex_List_View has size % instead of 80", size_of(Oga_Vertex_List_View));
    }

    {
        instance: Oga_Index_List_View;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Index_List_View.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Index_List_View.id)) == 8, "Oga_Index_List_View.id has unexpected size % instead of 8", size_of(type_of(Oga_Index_List_View.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Index_List_View._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Index_List_View._context)) == 8, "Oga_Index_List_View._context has unexpected size % instead of 8", size_of(type_of(Oga_Index_List_View._context)));
        assert(((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)) == 16, "Oga_Index_List_View.memory_pointer has unexpected offset % instead of 16", ((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Index_List_View.memory_pointer)) == 56, "Oga_Index_List_View.memory_pointer has unexpected size % instead of 56", size_of(type_of(Oga_Index_List_View.memory_pointer)));
        assert(((cast(*void)(*instance.size)) - cast(*void)(*instance)) == 72, "Oga_Index_List_View.size has unexpected offset % instead of 72", ((cast(*void)(*instance.size)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Index_List_View.size)) == 8, "Oga_Index_List_View.size has unexpected size % instead of 8", size_of(type_of(Oga_Index_List_View.size)));
        assert(size_of(Oga_Index_List_View) == 80, "Oga_Index_List_View has size % instead of 80", size_of(Oga_Index_List_View));
    }

    {
        instance: Oga_Image_View_Desc;
        assert(((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)) == 0, "Oga_Image_View_Desc.memory_pointer has unexpected offset % instead of 0", ((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View_Desc.memory_pointer)) == 56, "Oga_Image_View_Desc.memory_pointer has unexpected size % instead of 56", size_of(type_of(Oga_Image_View_Desc.memory_pointer)));
        assert(((cast(*void)(*instance.format)) - cast(*void)(*instance)) == 56, "Oga_Image_View_Desc.format has unexpected offset % instead of 56", ((cast(*void)(*instance.format)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View_Desc.format)) == 4, "Oga_Image_View_Desc.format has unexpected size % instead of 4", size_of(type_of(Oga_Image_View_Desc.format)));
        assert(((cast(*void)(*instance.dimensions)) - cast(*void)(*instance)) == 60, "Oga_Image_View_Desc.dimensions has unexpected offset % instead of 60", ((cast(*void)(*instance.dimensions)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View_Desc.dimensions)) == 4, "Oga_Image_View_Desc.dimensions has unexpected size % instead of 4", size_of(type_of(Oga_Image_View_Desc.dimensions)));
        assert(((cast(*void)(*instance.width)) - cast(*void)(*instance)) == 64, "Oga_Image_View_Desc.width has unexpected offset % instead of 64", ((cast(*void)(*instance.width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View_Desc.width)) == 8, "Oga_Image_View_Desc.width has unexpected size % instead of 8", size_of(type_of(Oga_Image_View_Desc.width)));
        assert(((cast(*void)(*instance.height)) - cast(*void)(*instance)) == 72, "Oga_Image_View_Desc.height has unexpected offset % instead of 72", ((cast(*void)(*instance.height)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View_Desc.height)) == 8, "Oga_Image_View_Desc.height has unexpected size % instead of 8", size_of(type_of(Oga_Image_View_Desc.height)));
        assert(((cast(*void)(*instance.depth)) - cast(*void)(*instance)) == 80, "Oga_Image_View_Desc.depth has unexpected offset % instead of 80", ((cast(*void)(*instance.depth)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View_Desc.depth)) == 8, "Oga_Image_View_Desc.depth has unexpected size % instead of 8", size_of(type_of(Oga_Image_View_Desc.depth)));
        assert(((cast(*void)(*instance.linear_tiling)) - cast(*void)(*instance)) == 88, "Oga_Image_View_Desc.linear_tiling has unexpected offset % instead of 88", ((cast(*void)(*instance.linear_tiling)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View_Desc.linear_tiling)) == 1, "Oga_Image_View_Desc.linear_tiling has unexpected size % instead of 1", size_of(type_of(Oga_Image_View_Desc.linear_tiling)));
        assert(((cast(*void)(*instance.graphics_engine_family_index)) - cast(*void)(*instance)) == 96, "Oga_Image_View_Desc.graphics_engine_family_index has unexpected offset % instead of 96", ((cast(*void)(*instance.graphics_engine_family_index)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View_Desc.graphics_engine_family_index)) == 8, "Oga_Image_View_Desc.graphics_engine_family_index has unexpected size % instead of 8", size_of(type_of(Oga_Image_View_Desc.graphics_engine_family_index)));
        assert(size_of(Oga_Image_View_Desc) == 104, "Oga_Image_View_Desc has size % instead of 104", size_of(Oga_Image_View_Desc));
    }

    {
        instance: Oga_Image_View;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Image_View.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View.id)) == 8, "Oga_Image_View.id has unexpected size % instead of 8", size_of(type_of(Oga_Image_View.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Image_View._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View._context)) == 8, "Oga_Image_View._context has unexpected size % instead of 8", size_of(type_of(Oga_Image_View._context)));
        assert(((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)) == 16, "Oga_Image_View.memory_pointer has unexpected offset % instead of 16", ((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View.memory_pointer)) == 56, "Oga_Image_View.memory_pointer has unexpected size % instead of 56", size_of(type_of(Oga_Image_View.memory_pointer)));
        assert(((cast(*void)(*instance.width)) - cast(*void)(*instance)) == 72, "Oga_Image_View.width has unexpected offset % instead of 72", ((cast(*void)(*instance.width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View.width)) == 8, "Oga_Image_View.width has unexpected size % instead of 8", size_of(type_of(Oga_Image_View.width)));
        assert(((cast(*void)(*instance.height)) - cast(*void)(*instance)) == 80, "Oga_Image_View.height has unexpected offset % instead of 80", ((cast(*void)(*instance.height)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View.height)) == 8, "Oga_Image_View.height has unexpected size % instead of 8", size_of(type_of(Oga_Image_View.height)));
        assert(((cast(*void)(*instance.depth)) - cast(*void)(*instance)) == 88, "Oga_Image_View.depth has unexpected offset % instead of 88", ((cast(*void)(*instance.depth)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View.depth)) == 8, "Oga_Image_View.depth has unexpected size % instead of 8", size_of(type_of(Oga_Image_View.depth)));
        assert(((cast(*void)(*instance.dimensions)) - cast(*void)(*instance)) == 96, "Oga_Image_View.dimensions has unexpected offset % instead of 96", ((cast(*void)(*instance.dimensions)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View.dimensions)) == 4, "Oga_Image_View.dimensions has unexpected size % instead of 4", size_of(type_of(Oga_Image_View.dimensions)));
        assert(((cast(*void)(*instance.linear_tiling)) - cast(*void)(*instance)) == 100, "Oga_Image_View.linear_tiling has unexpected offset % instead of 100", ((cast(*void)(*instance.linear_tiling)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Image_View.linear_tiling)) == 1, "Oga_Image_View.linear_tiling has unexpected size % instead of 1", size_of(type_of(Oga_Image_View.linear_tiling)));
        assert(size_of(Oga_Image_View) == 104, "Oga_Image_View has size % instead of 104", size_of(Oga_Image_View));
    }

    {
        instance: Oga_FBuffer_View;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_FBuffer_View.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_FBuffer_View.id)) == 8, "Oga_FBuffer_View.id has unexpected size % instead of 8", size_of(type_of(Oga_FBuffer_View.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_FBuffer_View._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_FBuffer_View._context)) == 8, "Oga_FBuffer_View._context has unexpected size % instead of 8", size_of(type_of(Oga_FBuffer_View._context)));
        assert(((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)) == 16, "Oga_FBuffer_View.memory_pointer has unexpected offset % instead of 16", ((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_FBuffer_View.memory_pointer)) == 56, "Oga_FBuffer_View.memory_pointer has unexpected size % instead of 56", size_of(type_of(Oga_FBuffer_View.memory_pointer)));
        assert(((cast(*void)(*instance.width)) - cast(*void)(*instance)) == 72, "Oga_FBuffer_View.width has unexpected offset % instead of 72", ((cast(*void)(*instance.width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_FBuffer_View.width)) == 8, "Oga_FBuffer_View.width has unexpected size % instead of 8", size_of(type_of(Oga_FBuffer_View.width)));
        assert(((cast(*void)(*instance.height)) - cast(*void)(*instance)) == 80, "Oga_FBuffer_View.height has unexpected offset % instead of 80", ((cast(*void)(*instance.height)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_FBuffer_View.height)) == 8, "Oga_FBuffer_View.height has unexpected size % instead of 8", size_of(type_of(Oga_FBuffer_View.height)));
        assert(((cast(*void)(*instance.depth)) - cast(*void)(*instance)) == 88, "Oga_FBuffer_View.depth has unexpected offset % instead of 88", ((cast(*void)(*instance.depth)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_FBuffer_View.depth)) == 8, "Oga_FBuffer_View.depth has unexpected size % instead of 8", size_of(type_of(Oga_FBuffer_View.depth)));
        assert(((cast(*void)(*instance.dimensions)) - cast(*void)(*instance)) == 96, "Oga_FBuffer_View.dimensions has unexpected offset % instead of 96", ((cast(*void)(*instance.dimensions)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_FBuffer_View.dimensions)) == 4, "Oga_FBuffer_View.dimensions has unexpected size % instead of 4", size_of(type_of(Oga_FBuffer_View.dimensions)));
        assert(((cast(*void)(*instance.linear_tiling)) - cast(*void)(*instance)) == 100, "Oga_FBuffer_View.linear_tiling has unexpected offset % instead of 100", ((cast(*void)(*instance.linear_tiling)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_FBuffer_View.linear_tiling)) == 1, "Oga_FBuffer_View.linear_tiling has unexpected size % instead of 1", size_of(type_of(Oga_FBuffer_View.linear_tiling)));
        assert(size_of(Oga_FBuffer_View) == 104, "Oga_FBuffer_View has size % instead of 104", size_of(Oga_FBuffer_View));
    }

    {
        instance: Oga_Optimal_Copy_View_Desc;
        assert(((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)) == 0, "Oga_Optimal_Copy_View_Desc.memory_pointer has unexpected offset % instead of 0", ((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View_Desc.memory_pointer)) == 56, "Oga_Optimal_Copy_View_Desc.memory_pointer has unexpected size % instead of 56", size_of(type_of(Oga_Optimal_Copy_View_Desc.memory_pointer)));
        assert(((cast(*void)(*instance.format)) - cast(*void)(*instance)) == 56, "Oga_Optimal_Copy_View_Desc.format has unexpected offset % instead of 56", ((cast(*void)(*instance.format)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View_Desc.format)) == 4, "Oga_Optimal_Copy_View_Desc.format has unexpected size % instead of 4", size_of(type_of(Oga_Optimal_Copy_View_Desc.format)));
        assert(((cast(*void)(*instance.dimensions)) - cast(*void)(*instance)) == 60, "Oga_Optimal_Copy_View_Desc.dimensions has unexpected offset % instead of 60", ((cast(*void)(*instance.dimensions)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View_Desc.dimensions)) == 4, "Oga_Optimal_Copy_View_Desc.dimensions has unexpected size % instead of 4", size_of(type_of(Oga_Optimal_Copy_View_Desc.dimensions)));
        assert(((cast(*void)(*instance.width)) - cast(*void)(*instance)) == 64, "Oga_Optimal_Copy_View_Desc.width has unexpected offset % instead of 64", ((cast(*void)(*instance.width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View_Desc.width)) == 8, "Oga_Optimal_Copy_View_Desc.width has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_View_Desc.width)));
        assert(((cast(*void)(*instance.height)) - cast(*void)(*instance)) == 72, "Oga_Optimal_Copy_View_Desc.height has unexpected offset % instead of 72", ((cast(*void)(*instance.height)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View_Desc.height)) == 8, "Oga_Optimal_Copy_View_Desc.height has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_View_Desc.height)));
        assert(((cast(*void)(*instance.depth)) - cast(*void)(*instance)) == 80, "Oga_Optimal_Copy_View_Desc.depth has unexpected offset % instead of 80", ((cast(*void)(*instance.depth)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View_Desc.depth)) == 8, "Oga_Optimal_Copy_View_Desc.depth has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_View_Desc.depth)));
        assert(((cast(*void)(*instance.linear_tiling)) - cast(*void)(*instance)) == 88, "Oga_Optimal_Copy_View_Desc.linear_tiling has unexpected offset % instead of 88", ((cast(*void)(*instance.linear_tiling)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View_Desc.linear_tiling)) == 1, "Oga_Optimal_Copy_View_Desc.linear_tiling has unexpected size % instead of 1", size_of(type_of(Oga_Optimal_Copy_View_Desc.linear_tiling)));
        assert(((cast(*void)(*instance.graphics_engine_family_index)) - cast(*void)(*instance)) == 96, "Oga_Optimal_Copy_View_Desc.graphics_engine_family_index has unexpected offset % instead of 96", ((cast(*void)(*instance.graphics_engine_family_index)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View_Desc.graphics_engine_family_index)) == 8, "Oga_Optimal_Copy_View_Desc.graphics_engine_family_index has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_View_Desc.graphics_engine_family_index)));
        assert(((cast(*void)(*instance.flags)) - cast(*void)(*instance)) == 104, "Oga_Optimal_Copy_View_Desc.flags has unexpected offset % instead of 104", ((cast(*void)(*instance.flags)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View_Desc.flags)) == 8, "Oga_Optimal_Copy_View_Desc.flags has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_View_Desc.flags)));
        assert(size_of(Oga_Optimal_Copy_View_Desc) == 112, "Oga_Optimal_Copy_View_Desc has size % instead of 112", size_of(Oga_Optimal_Copy_View_Desc));
    }

    {
        instance: Oga_Optimal_Copy_View;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Optimal_Copy_View.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View.id)) == 8, "Oga_Optimal_Copy_View.id has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_View.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Optimal_Copy_View._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View._context)) == 8, "Oga_Optimal_Copy_View._context has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_View._context)));
        assert(((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)) == 16, "Oga_Optimal_Copy_View.memory_pointer has unexpected offset % instead of 16", ((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View.memory_pointer)) == 56, "Oga_Optimal_Copy_View.memory_pointer has unexpected size % instead of 56", size_of(type_of(Oga_Optimal_Copy_View.memory_pointer)));
        assert(((cast(*void)(*instance.width)) - cast(*void)(*instance)) == 72, "Oga_Optimal_Copy_View.width has unexpected offset % instead of 72", ((cast(*void)(*instance.width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View.width)) == 8, "Oga_Optimal_Copy_View.width has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_View.width)));
        assert(((cast(*void)(*instance.height)) - cast(*void)(*instance)) == 80, "Oga_Optimal_Copy_View.height has unexpected offset % instead of 80", ((cast(*void)(*instance.height)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View.height)) == 8, "Oga_Optimal_Copy_View.height has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_View.height)));
        assert(((cast(*void)(*instance.depth)) - cast(*void)(*instance)) == 88, "Oga_Optimal_Copy_View.depth has unexpected offset % instead of 88", ((cast(*void)(*instance.depth)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View.depth)) == 8, "Oga_Optimal_Copy_View.depth has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_View.depth)));
        assert(((cast(*void)(*instance.dimensions)) - cast(*void)(*instance)) == 96, "Oga_Optimal_Copy_View.dimensions has unexpected offset % instead of 96", ((cast(*void)(*instance.dimensions)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View.dimensions)) == 4, "Oga_Optimal_Copy_View.dimensions has unexpected size % instead of 4", size_of(type_of(Oga_Optimal_Copy_View.dimensions)));
        assert(((cast(*void)(*instance.linear_tiling)) - cast(*void)(*instance)) == 100, "Oga_Optimal_Copy_View.linear_tiling has unexpected offset % instead of 100", ((cast(*void)(*instance.linear_tiling)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View.linear_tiling)) == 1, "Oga_Optimal_Copy_View.linear_tiling has unexpected size % instead of 1", size_of(type_of(Oga_Optimal_Copy_View.linear_tiling)));
        assert(((cast(*void)(*instance.flags)) - cast(*void)(*instance)) == 104, "Oga_Optimal_Copy_View.flags has unexpected offset % instead of 104", ((cast(*void)(*instance.flags)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_View.flags)) == 8, "Oga_Optimal_Copy_View.flags has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_View.flags)));
        assert(size_of(Oga_Optimal_Copy_View) == 112, "Oga_Optimal_Copy_View has size % instead of 112", size_of(Oga_Optimal_Copy_View));
    }

    {
        instance: Oga_Render_Image_View_Desc;
        assert(((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)) == 0, "Oga_Render_Image_View_Desc.memory_pointer has unexpected offset % instead of 0", ((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Image_View_Desc.memory_pointer)) == 56, "Oga_Render_Image_View_Desc.memory_pointer has unexpected size % instead of 56", size_of(type_of(Oga_Render_Image_View_Desc.memory_pointer)));
        assert(((cast(*void)(*instance.format)) - cast(*void)(*instance)) == 56, "Oga_Render_Image_View_Desc.format has unexpected offset % instead of 56", ((cast(*void)(*instance.format)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Image_View_Desc.format)) == 4, "Oga_Render_Image_View_Desc.format has unexpected size % instead of 4", size_of(type_of(Oga_Render_Image_View_Desc.format)));
        assert(((cast(*void)(*instance.width)) - cast(*void)(*instance)) == 64, "Oga_Render_Image_View_Desc.width has unexpected offset % instead of 64", ((cast(*void)(*instance.width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Image_View_Desc.width)) == 8, "Oga_Render_Image_View_Desc.width has unexpected size % instead of 8", size_of(type_of(Oga_Render_Image_View_Desc.width)));
        assert(((cast(*void)(*instance.height)) - cast(*void)(*instance)) == 72, "Oga_Render_Image_View_Desc.height has unexpected offset % instead of 72", ((cast(*void)(*instance.height)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Image_View_Desc.height)) == 8, "Oga_Render_Image_View_Desc.height has unexpected size % instead of 8", size_of(type_of(Oga_Render_Image_View_Desc.height)));
        assert(size_of(Oga_Render_Image_View_Desc) == 80, "Oga_Render_Image_View_Desc has size % instead of 80", size_of(Oga_Render_Image_View_Desc));
    }

    {
        instance: Oga_Render_Image_View;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Render_Image_View.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Image_View.id)) == 8, "Oga_Render_Image_View.id has unexpected size % instead of 8", size_of(type_of(Oga_Render_Image_View.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Render_Image_View._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Image_View._context)) == 8, "Oga_Render_Image_View._context has unexpected size % instead of 8", size_of(type_of(Oga_Render_Image_View._context)));
        assert(((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)) == 16, "Oga_Render_Image_View.memory_pointer has unexpected offset % instead of 16", ((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Image_View.memory_pointer)) == 56, "Oga_Render_Image_View.memory_pointer has unexpected size % instead of 56", size_of(type_of(Oga_Render_Image_View.memory_pointer)));
        assert(((cast(*void)(*instance.width)) - cast(*void)(*instance)) == 72, "Oga_Render_Image_View.width has unexpected offset % instead of 72", ((cast(*void)(*instance.width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Image_View.width)) == 8, "Oga_Render_Image_View.width has unexpected size % instead of 8", size_of(type_of(Oga_Render_Image_View.width)));
        assert(((cast(*void)(*instance.height)) - cast(*void)(*instance)) == 80, "Oga_Render_Image_View.height has unexpected offset % instead of 80", ((cast(*void)(*instance.height)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Image_View.height)) == 8, "Oga_Render_Image_View.height has unexpected size % instead of 8", size_of(type_of(Oga_Render_Image_View.height)));
        assert(size_of(Oga_Render_Image_View) == 88, "Oga_Render_Image_View has size % instead of 88", size_of(Oga_Render_Image_View));
    }

    {
        instance: Oga_Block_View;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Block_View.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Block_View.id)) == 8, "Oga_Block_View.id has unexpected size % instead of 8", size_of(type_of(Oga_Block_View.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Block_View._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Block_View._context)) == 8, "Oga_Block_View._context has unexpected size % instead of 8", size_of(type_of(Oga_Block_View._context)));
        assert(((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)) == 16, "Oga_Block_View.memory_pointer has unexpected offset % instead of 16", ((cast(*void)(*instance.memory_pointer)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Block_View.memory_pointer)) == 56, "Oga_Block_View.memory_pointer has unexpected size % instead of 56", size_of(type_of(Oga_Block_View.memory_pointer)));
        assert(((cast(*void)(*instance.size)) - cast(*void)(*instance)) == 72, "Oga_Block_View.size has unexpected offset % instead of 72", ((cast(*void)(*instance.size)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Block_View.size)) == 8, "Oga_Block_View.size has unexpected size % instead of 8", size_of(type_of(Oga_Block_View.size)));
        assert(size_of(Oga_Block_View) == 80, "Oga_Block_View has size % instead of 80", size_of(Oga_Block_View));
    }

    {
        instance: Oga_Command_Pool_Desc;
        assert(((cast(*void)(*instance.flags)) - cast(*void)(*instance)) == 0, "Oga_Command_Pool_Desc.flags has unexpected offset % instead of 0", ((cast(*void)(*instance.flags)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Command_Pool_Desc.flags)) == 8, "Oga_Command_Pool_Desc.flags has unexpected size % instead of 8", size_of(type_of(Oga_Command_Pool_Desc.flags)));
        assert(((cast(*void)(*instance.engine_family_index)) - cast(*void)(*instance)) == 8, "Oga_Command_Pool_Desc.engine_family_index has unexpected offset % instead of 8", ((cast(*void)(*instance.engine_family_index)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Command_Pool_Desc.engine_family_index)) == 8, "Oga_Command_Pool_Desc.engine_family_index has unexpected size % instead of 8", size_of(type_of(Oga_Command_Pool_Desc.engine_family_index)));
        assert(size_of(Oga_Command_Pool_Desc) == 16, "Oga_Command_Pool_Desc has size % instead of 16", size_of(Oga_Command_Pool_Desc));
    }

    {
        instance: Oga_Command_Pool;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Command_Pool.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Command_Pool.id)) == 8, "Oga_Command_Pool.id has unexpected size % instead of 8", size_of(type_of(Oga_Command_Pool.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Command_Pool._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Command_Pool._context)) == 8, "Oga_Command_Pool._context has unexpected size % instead of 8", size_of(type_of(Oga_Command_Pool._context)));
        assert(size_of(Oga_Command_Pool) == 16, "Oga_Command_Pool has size % instead of 16", size_of(Oga_Command_Pool));
    }

    {
        instance: Oga_Command_List;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Command_List.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Command_List.id)) == 8, "Oga_Command_List.id has unexpected size % instead of 8", size_of(type_of(Oga_Command_List.id)));
        assert(((cast(*void)(*instance.pool)) - cast(*void)(*instance)) == 8, "Oga_Command_List.pool has unexpected offset % instead of 8", ((cast(*void)(*instance.pool)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Command_List.pool)) == 8, "Oga_Command_List.pool has unexpected size % instead of 8", size_of(type_of(Oga_Command_List.pool)));
        assert(size_of(Oga_Command_List) == 16, "Oga_Command_List has size % instead of 16", size_of(Oga_Command_List));
    }

    {
        instance: Oga_Submit_Command_List_Desc;
        assert(((cast(*void)(*instance.engine)) - cast(*void)(*instance)) == 0, "Oga_Submit_Command_List_Desc.engine has unexpected offset % instead of 0", ((cast(*void)(*instance.engine)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Submit_Command_List_Desc.engine)) == 16, "Oga_Submit_Command_List_Desc.engine has unexpected size % instead of 16", size_of(type_of(Oga_Submit_Command_List_Desc.engine)));
        assert(((cast(*void)(*instance.wait_gpu_latches)) - cast(*void)(*instance)) == 16, "Oga_Submit_Command_List_Desc.wait_gpu_latches has unexpected offset % instead of 16", ((cast(*void)(*instance.wait_gpu_latches)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Submit_Command_List_Desc.wait_gpu_latches)) == 8, "Oga_Submit_Command_List_Desc.wait_gpu_latches has unexpected size % instead of 8", size_of(type_of(Oga_Submit_Command_List_Desc.wait_gpu_latches)));
        assert(((cast(*void)(*instance.wait_gpu_latch_count)) - cast(*void)(*instance)) == 24, "Oga_Submit_Command_List_Desc.wait_gpu_latch_count has unexpected offset % instead of 24", ((cast(*void)(*instance.wait_gpu_latch_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Submit_Command_List_Desc.wait_gpu_latch_count)) == 8, "Oga_Submit_Command_List_Desc.wait_gpu_latch_count has unexpected size % instead of 8", size_of(type_of(Oga_Submit_Command_List_Desc.wait_gpu_latch_count)));
        assert(((cast(*void)(*instance.signal_gpu_latches)) - cast(*void)(*instance)) == 32, "Oga_Submit_Command_List_Desc.signal_gpu_latches has unexpected offset % instead of 32", ((cast(*void)(*instance.signal_gpu_latches)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Submit_Command_List_Desc.signal_gpu_latches)) == 8, "Oga_Submit_Command_List_Desc.signal_gpu_latches has unexpected size % instead of 8", size_of(type_of(Oga_Submit_Command_List_Desc.signal_gpu_latches)));
        assert(((cast(*void)(*instance.signal_gpu_latch_count)) - cast(*void)(*instance)) == 40, "Oga_Submit_Command_List_Desc.signal_gpu_latch_count has unexpected offset % instead of 40", ((cast(*void)(*instance.signal_gpu_latch_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Submit_Command_List_Desc.signal_gpu_latch_count)) == 8, "Oga_Submit_Command_List_Desc.signal_gpu_latch_count has unexpected size % instead of 8", size_of(type_of(Oga_Submit_Command_List_Desc.signal_gpu_latch_count)));
        assert(((cast(*void)(*instance.signal_cpu_latch)) - cast(*void)(*instance)) == 48, "Oga_Submit_Command_List_Desc.signal_cpu_latch has unexpected offset % instead of 48", ((cast(*void)(*instance.signal_cpu_latch)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Submit_Command_List_Desc.signal_cpu_latch)) == 8, "Oga_Submit_Command_List_Desc.signal_cpu_latch has unexpected size % instead of 8", size_of(type_of(Oga_Submit_Command_List_Desc.signal_cpu_latch)));
        assert(size_of(Oga_Submit_Command_List_Desc) == 56, "Oga_Submit_Command_List_Desc has size % instead of 56", size_of(Oga_Submit_Command_List_Desc));
    }

    {
        instance: Oga_Gpu_Timestamp_Pool;
        assert(((cast(*void)(*instance.id)) - cast(*void)(*instance)) == 0, "Oga_Gpu_Timestamp_Pool.id has unexpected offset % instead of 0", ((cast(*void)(*instance.id)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Gpu_Timestamp_Pool.id)) == 8, "Oga_Gpu_Timestamp_Pool.id has unexpected size % instead of 8", size_of(type_of(Oga_Gpu_Timestamp_Pool.id)));
        assert(((cast(*void)(*instance._context)) - cast(*void)(*instance)) == 8, "Oga_Gpu_Timestamp_Pool._context has unexpected offset % instead of 8", ((cast(*void)(*instance._context)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Gpu_Timestamp_Pool._context)) == 8, "Oga_Gpu_Timestamp_Pool._context has unexpected size % instead of 8", size_of(type_of(Oga_Gpu_Timestamp_Pool._context)));
        assert(((cast(*void)(*instance.timestamp_count)) - cast(*void)(*instance)) == 16, "Oga_Gpu_Timestamp_Pool.timestamp_count has unexpected offset % instead of 16", ((cast(*void)(*instance.timestamp_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Gpu_Timestamp_Pool.timestamp_count)) == 8, "Oga_Gpu_Timestamp_Pool.timestamp_count has unexpected size % instead of 8", size_of(type_of(Oga_Gpu_Timestamp_Pool.timestamp_count)));
        assert(((cast(*void)(*instance.written_timestamp_count)) - cast(*void)(*instance)) == 24, "Oga_Gpu_Timestamp_Pool.written_timestamp_count has unexpected offset % instead of 24", ((cast(*void)(*instance.written_timestamp_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Gpu_Timestamp_Pool.written_timestamp_count)) == 8, "Oga_Gpu_Timestamp_Pool.written_timestamp_count has unexpected size % instead of 8", size_of(type_of(Oga_Gpu_Timestamp_Pool.written_timestamp_count)));
        assert(size_of(Oga_Gpu_Timestamp_Pool) == 32, "Oga_Gpu_Timestamp_Pool has size % instead of 32", size_of(Oga_Gpu_Timestamp_Pool));
    }

    {
        instance: Oga_Render_Attachment_Desc;
        assert(((cast(*void)(*instance.image)) - cast(*void)(*instance)) == 0, "Oga_Render_Attachment_Desc.image has unexpected offset % instead of 0", ((cast(*void)(*instance.image)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Attachment_Desc.image)) == 8, "Oga_Render_Attachment_Desc.image has unexpected size % instead of 8", size_of(type_of(Oga_Render_Attachment_Desc.image)));
        assert(((cast(*void)(*instance.resolve_mode)) - cast(*void)(*instance)) == 8, "Oga_Render_Attachment_Desc.resolve_mode has unexpected offset % instead of 8", ((cast(*void)(*instance.resolve_mode)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Attachment_Desc.resolve_mode)) == 8, "Oga_Render_Attachment_Desc.resolve_mode has unexpected size % instead of 8", size_of(type_of(Oga_Render_Attachment_Desc.resolve_mode)));
        assert(((cast(*void)(*instance.resolve_image)) - cast(*void)(*instance)) == 16, "Oga_Render_Attachment_Desc.resolve_image has unexpected offset % instead of 16", ((cast(*void)(*instance.resolve_image)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Attachment_Desc.resolve_image)) == 8, "Oga_Render_Attachment_Desc.resolve_image has unexpected size % instead of 8", size_of(type_of(Oga_Render_Attachment_Desc.resolve_image)));
        assert(((cast(*void)(*instance.load_op)) - cast(*void)(*instance)) == 24, "Oga_Render_Attachment_Desc.load_op has unexpected offset % instead of 24", ((cast(*void)(*instance.load_op)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Attachment_Desc.load_op)) == 4, "Oga_Render_Attachment_Desc.load_op has unexpected size % instead of 4", size_of(type_of(Oga_Render_Attachment_Desc.load_op)));
        assert(((cast(*void)(*instance.store_op)) - cast(*void)(*instance)) == 28, "Oga_Render_Attachment_Desc.store_op has unexpected offset % instead of 28", ((cast(*void)(*instance.store_op)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Attachment_Desc.store_op)) == 4, "Oga_Render_Attachment_Desc.store_op has unexpected size % instead of 4", size_of(type_of(Oga_Render_Attachment_Desc.store_op)));
        assert(((cast(*void)(*instance.clear_color)) - cast(*void)(*instance)) == 32, "Oga_Render_Attachment_Desc.clear_color has unexpected offset % instead of 32", ((cast(*void)(*instance.clear_color)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Render_Attachment_Desc.clear_color)) == 16, "Oga_Render_Attachment_Desc.clear_color has unexpected size % instead of 16", size_of(type_of(Oga_Render_Attachment_Desc.clear_color)));
        assert(size_of(Oga_Render_Attachment_Desc) == 48, "Oga_Render_Attachment_Desc has size % instead of 48", size_of(Oga_Render_Attachment_Desc));
    }

    {
        instance: Oga_Begin_Render_Pass_Desc;
        assert(((cast(*void)(*instance.render_area_offset_x)) - cast(*void)(*instance)) == 0, "Oga_Begin_Render_Pass_Desc.render_area_offset_x has unexpected offset % instead of 0", ((cast(*void)(*instance.render_area_offset_x)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Begin_Render_Pass_Desc.render_area_offset_x)) == 8, "Oga_Begin_Render_Pass_Desc.render_area_offset_x has unexpected size % instead of 8", size_of(type_of(Oga_Begin_Render_Pass_Desc.render_area_offset_x)));
        assert(((cast(*void)(*instance.render_area_offset_y)) - cast(*void)(*instance)) == 8, "Oga_Begin_Render_Pass_Desc.render_area_offset_y has unexpected offset % instead of 8", ((cast(*void)(*instance.render_area_offset_y)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Begin_Render_Pass_Desc.render_area_offset_y)) == 8, "Oga_Begin_Render_Pass_Desc.render_area_offset_y has unexpected size % instead of 8", size_of(type_of(Oga_Begin_Render_Pass_Desc.render_area_offset_y)));
        assert(((cast(*void)(*instance.render_area_width)) - cast(*void)(*instance)) == 16, "Oga_Begin_Render_Pass_Desc.render_area_width has unexpected offset % instead of 16", ((cast(*void)(*instance.render_area_width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Begin_Render_Pass_Desc.render_area_width)) == 8, "Oga_Begin_Render_Pass_Desc.render_area_width has unexpected size % instead of 8", size_of(type_of(Oga_Begin_Render_Pass_Desc.render_area_width)));
        assert(((cast(*void)(*instance.render_area_height)) - cast(*void)(*instance)) == 24, "Oga_Begin_Render_Pass_Desc.render_area_height has unexpected offset % instead of 24", ((cast(*void)(*instance.render_area_height)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Begin_Render_Pass_Desc.render_area_height)) == 8, "Oga_Begin_Render_Pass_Desc.render_area_height has unexpected size % instead of 8", size_of(type_of(Oga_Begin_Render_Pass_Desc.render_area_height)));
        assert(((cast(*void)(*instance.attachment_count)) - cast(*void)(*instance)) == 32, "Oga_Begin_Render_Pass_Desc.attachment_count has unexpected offset % instead of 32", ((cast(*void)(*instance.attachment_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Begin_Render_Pass_Desc.attachment_count)) == 8, "Oga_Begin_Render_Pass_Desc.attachment_count has unexpected size % instead of 8", size_of(type_of(Oga_Begin_Render_Pass_Desc.attachment_count)));
        assert(((cast(*void)(*instance.attachments)) - cast(*void)(*instance)) == 40, "Oga_Begin_Render_Pass_Desc.attachments has unexpected offset % instead of 40", ((cast(*void)(*instance.attachments)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Begin_Render_Pass_Desc.attachments)) == 8, "Oga_Begin_Render_Pass_Desc.attachments has unexpected size % instead of 8", size_of(type_of(Oga_Begin_Render_Pass_Desc.attachments)));
        assert(size_of(Oga_Begin_Render_Pass_Desc) == 48, "Oga_Begin_Render_Pass_Desc has size % instead of 48", size_of(Oga_Begin_Render_Pass_Desc));
    }

    {
        instance: Oga_Draw_Desc;
        assert(((cast(*void)(*instance.draw_type)) - cast(*void)(*instance)) == 0, "Oga_Draw_Desc.draw_type has unexpected offset % instead of 0", ((cast(*void)(*instance.draw_type)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Draw_Desc.draw_type)) == 4, "Oga_Draw_Desc.draw_type has unexpected size % instead of 4", size_of(type_of(Oga_Draw_Desc.draw_type)));
        assert(((cast(*void)(*instance.vertex_start)) - cast(*void)(*instance)) == 8, "Oga_Draw_Desc.vertex_start has unexpected offset % instead of 8", ((cast(*void)(*instance.vertex_start)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Draw_Desc.vertex_start)) == 8, "Oga_Draw_Desc.vertex_start has unexpected size % instead of 8", size_of(type_of(Oga_Draw_Desc.vertex_start)));
        assert(((cast(*void)(*instance.vertex_count)) - cast(*void)(*instance)) == 16, "Oga_Draw_Desc.vertex_count has unexpected offset % instead of 16", ((cast(*void)(*instance.vertex_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Draw_Desc.vertex_count)) == 8, "Oga_Draw_Desc.vertex_count has unexpected size % instead of 8", size_of(type_of(Oga_Draw_Desc.vertex_count)));
        assert(((cast(*void)(*instance.vertex_list_bindings)) - cast(*void)(*instance)) == 24, "Oga_Draw_Desc.vertex_list_bindings has unexpected offset % instead of 24", ((cast(*void)(*instance.vertex_list_bindings)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Draw_Desc.vertex_list_bindings)) == 256, "Oga_Draw_Desc.vertex_list_bindings has unexpected size % instead of 256", size_of(type_of(Oga_Draw_Desc.vertex_list_bindings)));
        assert(((cast(*void)(*instance.vertex_list_offsets)) - cast(*void)(*instance)) == 280, "Oga_Draw_Desc.vertex_list_offsets has unexpected offset % instead of 280", ((cast(*void)(*instance.vertex_list_offsets)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Draw_Desc.vertex_list_offsets)) == 256, "Oga_Draw_Desc.vertex_list_offsets has unexpected size % instead of 256", size_of(type_of(Oga_Draw_Desc.vertex_list_offsets)));
        assert(((cast(*void)(*instance.vertex_list_binding_count)) - cast(*void)(*instance)) == 536, "Oga_Draw_Desc.vertex_list_binding_count has unexpected offset % instead of 536", ((cast(*void)(*instance.vertex_list_binding_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Draw_Desc.vertex_list_binding_count)) == 8, "Oga_Draw_Desc.vertex_list_binding_count has unexpected size % instead of 8", size_of(type_of(Oga_Draw_Desc.vertex_list_binding_count)));
        assert(((cast(*void)(*instance.instance_start)) - cast(*void)(*instance)) == 544, "Oga_Draw_Desc.instance_start has unexpected offset % instead of 544", ((cast(*void)(*instance.instance_start)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Draw_Desc.instance_start)) == 8, "Oga_Draw_Desc.instance_start has unexpected size % instead of 8", size_of(type_of(Oga_Draw_Desc.instance_start)));
        assert(((cast(*void)(*instance.instance_count)) - cast(*void)(*instance)) == 552, "Oga_Draw_Desc.instance_count has unexpected offset % instead of 552", ((cast(*void)(*instance.instance_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Draw_Desc.instance_count)) == 8, "Oga_Draw_Desc.instance_count has unexpected size % instead of 8", size_of(type_of(Oga_Draw_Desc.instance_count)));
        assert(((cast(*void)(*instance.index_start)) - cast(*void)(*instance)) == 560, "Oga_Draw_Desc.index_start has unexpected offset % instead of 560", ((cast(*void)(*instance.index_start)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Draw_Desc.index_start)) == 8, "Oga_Draw_Desc.index_start has unexpected size % instead of 8", size_of(type_of(Oga_Draw_Desc.index_start)));
        assert(((cast(*void)(*instance.index_count)) - cast(*void)(*instance)) == 568, "Oga_Draw_Desc.index_count has unexpected offset % instead of 568", ((cast(*void)(*instance.index_count)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Draw_Desc.index_count)) == 8, "Oga_Draw_Desc.index_count has unexpected size % instead of 8", size_of(type_of(Oga_Draw_Desc.index_count)));
        assert(((cast(*void)(*instance.index_list)) - cast(*void)(*instance)) == 576, "Oga_Draw_Desc.index_list has unexpected offset % instead of 576", ((cast(*void)(*instance.index_list)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Draw_Desc.index_list)) == 8, "Oga_Draw_Desc.index_list has unexpected size % instead of 8", size_of(type_of(Oga_Draw_Desc.index_list)));
        assert(((cast(*void)(*instance.index_list_offset)) - cast(*void)(*instance)) == 584, "Oga_Draw_Desc.index_list_offset has unexpected offset % instead of 584", ((cast(*void)(*instance.index_list_offset)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Draw_Desc.index_list_offset)) == 8, "Oga_Draw_Desc.index_list_offset has unexpected size % instead of 8", size_of(type_of(Oga_Draw_Desc.index_list_offset)));
        assert(((cast(*void)(*instance.index_type)) - cast(*void)(*instance)) == 592, "Oga_Draw_Desc.index_type has unexpected offset % instead of 592", ((cast(*void)(*instance.index_type)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Draw_Desc.index_type)) == 4, "Oga_Draw_Desc.index_type has unexpected size % instead of 4", size_of(type_of(Oga_Draw_Desc.index_type)));
        assert(size_of(Oga_Draw_Desc) == 600, "Oga_Draw_Desc has size % instead of 600", size_of(Oga_Draw_Desc));
    }

    {
        instance: Oga_Optimal_Copy_Desc;
        assert(((cast(*void)(*instance.offset_x)) - cast(*void)(*instance)) == 0, "Oga_Optimal_Copy_Desc.offset_x has unexpected offset % instead of 0", ((cast(*void)(*instance.offset_x)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_Desc.offset_x)) == 8, "Oga_Optimal_Copy_Desc.offset_x has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_Desc.offset_x)));
        assert(((cast(*void)(*instance.offset_y)) - cast(*void)(*instance)) == 8, "Oga_Optimal_Copy_Desc.offset_y has unexpected offset % instead of 8", ((cast(*void)(*instance.offset_y)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_Desc.offset_y)) == 8, "Oga_Optimal_Copy_Desc.offset_y has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_Desc.offset_y)));
        assert(((cast(*void)(*instance.offset_z)) - cast(*void)(*instance)) == 16, "Oga_Optimal_Copy_Desc.offset_z has unexpected offset % instead of 16", ((cast(*void)(*instance.offset_z)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_Desc.offset_z)) == 8, "Oga_Optimal_Copy_Desc.offset_z has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_Desc.offset_z)));
        assert(((cast(*void)(*instance.width)) - cast(*void)(*instance)) == 24, "Oga_Optimal_Copy_Desc.width has unexpected offset % instead of 24", ((cast(*void)(*instance.width)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_Desc.width)) == 8, "Oga_Optimal_Copy_Desc.width has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_Desc.width)));
        assert(((cast(*void)(*instance.height)) - cast(*void)(*instance)) == 32, "Oga_Optimal_Copy_Desc.height has unexpected offset % instead of 32", ((cast(*void)(*instance.height)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_Desc.height)) == 8, "Oga_Optimal_Copy_Desc.height has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_Desc.height)));
        assert(((cast(*void)(*instance.depth)) - cast(*void)(*instance)) == 40, "Oga_Optimal_Copy_Desc.depth has unexpected offset % instead of 40", ((cast(*void)(*instance.depth)) - cast(*void)(*instance)));
        assert(size_of(type_of(Oga_Optimal_Copy_Desc.depth)) == 8, "Oga_Optimal_Copy_Desc.depth has unexpected size % instead of 8", size_of(type_of(Oga_Optimal_Copy_Desc.depth)));
        assert(size_of(Oga_Optimal_Copy_Desc) == 48, "Oga_Optimal_Copy_Desc has size % instead of 48", size_of(Oga_Optimal_Copy_Desc));
    }

    {
        instance: Osl_Compile_Desc;
        assert(((cast(*void)(*instance.target)) - cast(*void)(*instance)) == 0, "Osl_Compile_Desc.target has unexpected offset % instead of 0", ((cast(*void)(*instance.target)) - cast(*void)(*instance)));
        assert(size_of(type_of(Osl_Compile_Desc.target)) == 4, "Osl_Compile_Desc.target has unexpected size % instead of 4", size_of(type_of(Osl_Compile_Desc.target)));
        assert(((cast(*void)(*instance.program_kind)) - cast(*void)(*instance)) == 4, "Osl_Compile_Desc.program_kind has unexpected offset % instead of 4", ((cast(*void)(*instance.program_kind)) - cast(*void)(*instance)));
        assert(size_of(type_of(Osl_Compile_Desc.program_kind)) == 4, "Osl_Compile_Desc.program_kind has unexpected size % instead of 4", size_of(type_of(Osl_Compile_Desc.program_kind)));
        assert(((cast(*void)(*instance.code_text)) - cast(*void)(*instance)) == 8, "Osl_Compile_Desc.code_text has unexpected offset % instead of 8", ((cast(*void)(*instance.code_text)) - cast(*void)(*instance)));
        assert(size_of(type_of(Osl_Compile_Desc.code_text)) == 16, "Osl_Compile_Desc.code_text has unexpected size % instead of 16", size_of(type_of(Osl_Compile_Desc.code_text)));
        assert(((cast(*void)(*instance.enabled_features)) - cast(*void)(*instance)) == 24, "Osl_Compile_Desc.enabled_features has unexpected offset % instead of 24", ((cast(*void)(*instance.enabled_features)) - cast(*void)(*instance)));
        assert(size_of(type_of(Osl_Compile_Desc.enabled_features)) == 8, "Osl_Compile_Desc.enabled_features has unexpected size % instead of 8", size_of(type_of(Osl_Compile_Desc.enabled_features)));
        assert(size_of(Osl_Compile_Desc) == 32, "Osl_Compile_Desc has size % instead of 32", size_of(Osl_Compile_Desc));
    }
}

