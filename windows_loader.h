
#ifdef _WIN64
    #define WINAPI
#else
    #define WINAPI __stdcall
#endif

#if COMPILER_GNU
    #define WINDOWS_IMPORT __attribute__((dllimport))
#elif COMPILER_MSVC
    #define WINDOWS_IMPORT __declspec(dllimport)
#else
    #error compiler not supported for windows
#endif

typedef struct _SYSTEM_INFO {
  union {
    u32 dwOemId;
    struct {
      u16 wProcessorArchitecture;
      u16 wReserved;
    } DUMMYSTRUCTNAME;
  } DUMMYUNIONNAME;
  u32     dwPageSize;
  void*    lpMinimumApplicationAddress;
  void*    lpMaximumApplicationAddress;
  u32 *   dwActiveProcessorMask;
  u32     dwNumberOfProcessors;
  u32     dwProcessorType;
  u32     dwAllocationGranularity;
  u16      wProcessorLevel;
  u16      wProcessorRevision;
} SYSTEM_INFO, *LPSYSTEM_INFO;

typedef struct _MEMORY_BASIC_INFORMATION {
  void*  BaseAddress;
  void*  AllocationBase;
  u32  AllocationProtect;
  u16   PartitionId;
  size_t RegionSize;
  u32  State;
  u32  Protect;
  u32  Type;
} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;


#define MEM_COMMIT 0x00001000
#define MEM_RESERVE 0x00002000
#define MEM_DECOMMIT 0x00004000  
#define MEM_RELEASE 0x00008000

#define PAGE_NOACCESS  0x01
#define PAGE_READWRITE 0x04

WINDOWS_IMPORT void WINAPI GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);

WINDOWS_IMPORT void* WINAPI VirtualAlloc(void *lpAddress, size_t dwSize, u32 flAllocationType, u32 flProtect);
WINDOWS_IMPORT s32 WINAPI VirtualFree(void *lpAddress, size_t dwSize, u32 dwFreeType);

WINDOWS_IMPORT size_t WINAPI VirtualQuery(void* lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, u32 dwLength);

WINDOWS_IMPORT void* WINAPI GetStdHandle(u32 nStdHandle);

WINDOWS_IMPORT s32 WINAPI WriteFile(void* hFile, void* lpBuffer, u32 nNumberOfBytesToWrite, unsigned long* lpNumberOfBytesWritten, void* lpOverlapped);