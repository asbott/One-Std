
#ifndef _WINDOWS_LOADER_H
#define _WINDOWS_LOADER_H

#ifndef _BASE_H
#include "base.h"
#endif // _BASE_H

#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00


#define DECLSPEC_ALIGN(x) __declspec(align(x))
#define DECLSPEC_NOINITALL

typedef void *HANDLE;
typedef void* HWND;
typedef unsigned long* PDWORD;
typedef void* HMONITOR;
typedef u32 HRESULT;
typedef void* HDC;
typedef HANDLE HINSTANCE;
typedef HANDLE HICON;
typedef HANDLE HBRUSH;
typedef HANDLE HCURSOR;
typedef HANDLE HMODULE;
typedef HANDLE HMENU;
typedef HANDLE HBITMAP;
typedef HANDLE HGDIOBJ;
typedef HANDLE HFONT;
typedef HANDLE HPEN;
typedef HANDLE HGLOBAL;
typedef HANDLE HRGN;

typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL                *PBOOL;
typedef BOOL                *LPBOOL;
typedef BYTE                *PBYTE;
typedef BYTE                *LPBYTE;
typedef int                 *PINT;
typedef int                 *LPINT;
typedef WORD                *PWORD;
typedef WORD                *LPWORD;
typedef long                *LPLONG;
typedef DWORD               *PDWORD;
typedef DWORD               *LPDWORD;
typedef void                *LPVOID;
typedef const void          *LPCVOID;
typedef void                *PVOID;

typedef u64 DWORDLONG;


#if !defined(_M_IX86)
 typedef s64 LONGLONG; 
#else
 typedef double LONGLONG;
#endif

#if !defined(_M_IX86)
 typedef u64 ULONGLONG;
#else
 typedef double ULONGLONG;
#endif
typedef LONGLONG USN;

typedef WORD ATOM;

typedef s64 INT_PTR, *PINT_PTR;
typedef u64 UINT_PTR, *PUINT_PTR;

typedef s64 LONG_PTR, *PLONG_PTR;
typedef u64 ULONG_PTR, *PULONG_PTR;


typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

typedef signed char         INT8, *PINT8;
typedef signed short        INT16, *PINT16;
typedef signed int          INT32, *PINT32;
typedef s64      INT64, *PINT64;
typedef unsigned char       UINT8, *PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;
typedef s64    UINT64, *PUINT64;

typedef signed int LONG32, *PLONG32;

typedef unsigned int ULONG32, *PULONG32;
typedef unsigned int DWORD32, *PDWORD32;

typedef LONG32 LONG;

typedef s64 ULONG64, *PULONG64;
typedef s64 DWORD64, *PDWORD64;

typedef u64 LONG64;

typedef char CHAR;
typedef CHAR *PCHAR, *LPCH, *PCH;
typedef const CHAR *LPCCH, *PCCH;

typedef DWORD *DWORD_PTR;

typedef CHAR *NPSTR, *LPSTR, *PSTR;
typedef PSTR *PZPSTR;
typedef const PSTR *PCZPSTR;
typedef const CHAR *LPCSTR, *PCSTR;
typedef PCSTR *PZPCSTR;
typedef const PCSTR *PCZPCSTR;

typedef CHAR *PZZSTR;
typedef const CHAR *PCZZSTR;

typedef  CHAR *PNZCH;
typedef  const CHAR *PCNZCH;

typedef unsigned short WCHAR;

typedef WCHAR *NWPSTR, *LPWSTR, *PWSTR;
typedef PWSTR *PZPWSTR;
typedef const PWSTR *PCZPWSTR;
typedef WCHAR *LPUWSTR, *PUWSTR;
typedef const WCHAR *LPCWSTR, *PCWSTR;
typedef PCWSTR *PZPCWSTR;
typedef const PCWSTR *PCZPCWSTR;
typedef const WCHAR *LPCUWSTR, *PCUWSTR;

// what the fuck

// who thought this was a good idea

typedef WCHAR *PZZWSTR;
typedef const WCHAR *PCZZWSTR;
typedef WCHAR *PUZZWSTR;
typedef const WCHAR *PCUZZWSTR;

typedef  WCHAR *PNZWCH;
typedef  const WCHAR *PCNZWCH;
typedef  WCHAR *PUNZWCH;
typedef  const WCHAR *PCUNZWCH;

typedef const WCHAR *LPCWCH;

typedef long long LONGLONG;

typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } DUMMYSTRUCTNAME;
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef LARGE_INTEGER LARGE_INTEGER;

typedef LRESULT (*WNDPROC)( HWND unnamedParam1, UINT unnamedParam2, WPARAM unnamedParam3, LPARAM unnamedParam4);


// #Portability x64
#define CONTEXT_AMD64   0x00100000L

#define CONTEXT_CONTROL         (CONTEXT_AMD64 | 0x00000001L)
#define CONTEXT_INTEGER         (CONTEXT_AMD64 | 0x00000002L)
#define CONTEXT_SEGMENTS        (CONTEXT_AMD64 | 0x00000004L)
#define CONTEXT_FLOATING_POINT  (CONTEXT_AMD64 | 0x00000008L)
#define CONTEXT_DEBUG_REGISTERS (CONTEXT_AMD64 | 0x00000010L)

#define CONTEXT_FULL            (CONTEXT_CONTROL | CONTEXT_INTEGER | \
    CONTEXT_FLOATING_POINT)

#define CONTEXT_ALL             (CONTEXT_CONTROL | CONTEXT_INTEGER | \
    CONTEXT_SEGMENTS | CONTEXT_FLOATING_POINT | \
    CONTEXT_DEBUG_REGISTERS)

#define CONTEXT_XSTATE          (CONTEXT_AMD64 | 0x00000040L)




#define WINAPI __stdcall

#if COMPILER_FLAGS & COMPILER_FLAG_GNU
#define WINDOWS_IMPORT extern __attribute__((dllimport))
#elif COMPILER_FLAGS & COMPILER_FLAG_MSC

#define WINDOWS_IMPORT __declspec(dllimport)
#else
#define WINDOWS_IMPORT
#endif

typedef struct tagRECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT, *PRECT, *NPRECT, *LPRECT;
typedef const RECT* LPCRECT;

// ?!?!?!?!?!?!??!?!?!?!?!??!?!?!?!?!?!?!?!??!?!!??!?!?!?!?
typedef struct _POINTL {
  LONG x;
  LONG y;
} POINTL, *PPOINTL;
typedef struct tagPOINT {
  LONG x;
  LONG y;
} POINT, *PPOINT, *NPPOINT, *LPPOINT;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmicrosoft-anon-tag"
#endif // __clang__
typedef struct _SYSTEM_INFO {
    union _SYSTEM_INFO_DUMMYUNION {
        DWORD dwOemId;
        struct _SYSTEM_INFO_DUMMYSTRUCT {
            WORD wProcessorArchitecture;
            WORD wReserved;
        } ;
    } ;
    DWORD dwPageSize;
    LPVOID lpMinimumApplicationAddress;
    LPVOID lpMaximumApplicationAddress;
    DWORD_PTR dwActiveProcessorMask;
    DWORD dwNumberOfProcessors;
    DWORD dwProcessorType;
    DWORD dwAllocationGranularity;
    WORD wProcessorLevel;
    WORD wProcessorRevision;
} SYSTEM_INFO, *LPSYSTEM_INFO;
#ifdef __clang__
#pragma clang diagnostic pop
#endif //__clang__

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

typedef struct DECLSPEC_ALIGN(16) _M128A {
    unsigned long long Low;
    long long High;
} M128A, *PM128A;

typedef struct DECLSPEC_ALIGN(16) _XMM_SAVE_AREA32
{
    WORD   ControlWord;
    WORD   StatusWord;
    BYTE  TagWord;
    BYTE  Reserved1;
    WORD   ErrorOpcode;
    DWORD ErrorOffset;
    WORD   ErrorSelector;
    WORD   Reserved2;
    DWORD DataOffset;
    WORD   DataSelector;
    WORD   Reserved3;
    DWORD MxCsr;
    DWORD MxCsr_Mask;
    M128A FloatRegisters[8];

    #if defined(_WIN64)

    M128A XmmRegisters[16];
    BYTE  Reserved4[96];

    #else

    M128A XmmRegisters[8];
    BYTE  Reserved4[224];

    #endif

} XMM_SAVE_AREA32;
typedef struct DECLSPEC_ALIGN(16) _CONTEXT {

    //
    // Register parameter home addresses.
    //
    // N.B. These fields are for convience - they could be used to extend the
    //      context record in the future.
    //

    DWORD64 P1Home;
    DWORD64 P2Home;
    DWORD64 P3Home;
    DWORD64 P4Home;
    DWORD64 P5Home;
    DWORD64 P6Home;

    //
    // Control flags.
    //

    DWORD ContextFlags;
    DWORD MxCsr;

    //
    // Segment Registers and processor flags.
    //

    WORD   SegCs;
    WORD   SegDs;
    WORD   SegEs;
    WORD   SegFs;
    WORD   SegGs;
    WORD   SegSs;
    DWORD EFlags;

    //
    // Debug registers
    //

    DWORD64 Dr0;
    DWORD64 Dr1;
    DWORD64 Dr2;
    DWORD64 Dr3;
    DWORD64 Dr6;
    DWORD64 Dr7;

    //
    // Integer registers.
    //

    DWORD64 Rax;
    DWORD64 Rcx;
    DWORD64 Rdx;
    DWORD64 Rbx;
    DWORD64 Rsp;
    DWORD64 Rbp;
    DWORD64 Rsi;
    DWORD64 Rdi;
    DWORD64 R8;
    DWORD64 R9;
    DWORD64 R10;
    DWORD64 R11;
    DWORD64 R12;
    DWORD64 R13;
    DWORD64 R14;
    DWORD64 R15;

    //
    // Program counter.
    //

    DWORD64 Rip;

    //
    // Floating point state.
    //

    union {
        XMM_SAVE_AREA32 FltSave;
        struct {
            M128A Header[2];
            M128A Legacy[8];
            M128A Xmm0;
            M128A Xmm1;
            M128A Xmm2;
            M128A Xmm3;
            M128A Xmm4;
            M128A Xmm5;
            M128A Xmm6;
            M128A Xmm7;
            M128A Xmm8;
            M128A Xmm9;
            M128A Xmm10;
            M128A Xmm11;
            M128A Xmm12;
            M128A Xmm13;
            M128A Xmm14;
            M128A Xmm15;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    //
    // Vector registers.
    //

    M128A VectorRegister[26];
    DWORD64 VectorControl;

    //
    // Special debug control registers.
    //

    DWORD64 DebugControl;
    DWORD64 LastBranchToRip;
    DWORD64 LastBranchFromRip;
    DWORD64 LastExceptionToRip;
    DWORD64 LastExceptionFromRip;
} CONTEXT, *PCONTEXT;

typedef enum {
    AddrMode1616,
    AddrMode1632,
    AddrModeReal,
    AddrModeFlat
} ADDRESS_MODE;
typedef struct _tagADDRESS64 {
    DWORD64       Offset;
    WORD          Segment;
    ADDRESS_MODE  Mode;
} ADDRESS64, *LPADDRESS64;

typedef struct _KDHELP64 {

    DWORD64   Thread;
    DWORD   ThCallbackStack;
    DWORD   ThCallbackBStore;
    DWORD   NextCallback;
    DWORD   FramePointer;
    DWORD64   KiCallUserMode;
    DWORD64   KeUserCallbackDispatcher;
    DWORD64   SystemRangeStart;
    DWORD64   KiUserExceptionDispatcher;
    DWORD64   StackBase;
    DWORD64   StackLimit;
    DWORD     BuildVersion;
    DWORD     RetpolineStubFunctionTableSize;
    DWORD64   RetpolineStubFunctionTable;
    DWORD     RetpolineStubOffset;
    DWORD     RetpolineStubSize;
    DWORD64   Reserved0[2];

} KDHELP64, *PKDHELP64;

typedef struct _tagSTACKFRAME64 {
    ADDRESS64   AddrPC;               // program counter
    ADDRESS64   AddrReturn;           // return address
    ADDRESS64   AddrFrame;            // frame pointer
    ADDRESS64   AddrStack;            // stack pointer
    ADDRESS64   AddrBStore;           // backing store pointer
    PVOID       FuncTableEntry;       // pointer to pdata/fpo or NULL
    DWORD64     Params[4];            // possible arguments to the function
    BOOL        Far;                  // WOW far call
    BOOL        Virtual;              // is this a virtual frame?
    DWORD64     Reserved[3];
    KDHELP64    KdHelp;
} STACKFRAME64, *LPSTACKFRAME64;

typedef struct _SYMBOL_INFO {
    ULONG       SizeOfStruct;
    ULONG       TypeIndex;        // Type Index of symbol
    ULONG64     Reserved[2];
    ULONG       Index;
    ULONG       Size;
    ULONG64     ModBase;          // Base Address of module comtaining this symbol
    ULONG       Flags;
    ULONG64     Value;            // Value of symbol, ValuePresent should be 1
    ULONG64     Address;          // Address of symbol including base address of module
    ULONG       Register;         // register holding value or pointer to value
    ULONG       Scope;            // scope of the symbol
    ULONG       Tag;              // pdb classification
    ULONG       NameLen;          // Actual length of name
    ULONG       MaxNameLen;
    CHAR        Name[1];          // Name of symbol
} SYMBOL_INFO, *PSYMBOL_INFO;

typedef struct _IMAGEHLP_LINE64 {
    DWORD    SizeOfStruct;           // set to sizeof(IMAGEHLP_LINE64)
    PVOID    Key;                    // internal
    DWORD    LineNumber;             // line number in file
    PCHAR    FileName;               // full filename
    DWORD64  Address;                // first instruction of line
} IMAGEHLP_LINE64, *PIMAGEHLP_LINE64;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmicrosoft-anon-tag"
#endif // __clang__
typedef struct _OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    union _OVERLAPPED_DUMMYUNION {
        struct _OVERLAPPED_DUMMYSTRUCT {
            DWORD Offset;
            DWORD OffsetHigh;
        } ;
        PVOID Pointer;
    } ;

    HANDLE hEvent;
} OVERLAPPED, *LPOVERLAPPED;
#ifdef __clang__
#pragma clang diagnostic pop
#endif //__clang__

typedef struct tagMSG {
  HWND   hwnd;
  UINT   message;
  WPARAM wParam;
  LPARAM lParam;
  DWORD  time;
  POINT  pt;
  DWORD  lPrivate;
} MSG, *PMSG, *NPMSG, *LPMSG;

#define CCHDEVICENAME 32
#define CCHFORMNAME 32

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmicrosoft-anon-tag"
#endif // __clang__
typedef struct _devicemodeW {
  WCHAR dmDeviceName[CCHDEVICENAME];
  WORD  dmSpecVersion;
  WORD  dmDriverVersion;
  WORD  dmSize;
  WORD  dmDriverExtra;
  DWORD dmFields;
  union {
    struct {
      short dmOrientation;
      short dmPaperSize;
      short dmPaperLength;
      short dmPaperWidth;
      short dmScale;
      short dmCopies;
      short dmDefaultSource;
      short dmPrintQuality;
    } DUMMYSTRUCTNAME;
    POINTL dmPosition;
    struct {
      POINTL dmPosition;
      DWORD  dmDisplayOrientation;
      DWORD  dmDisplayFixedOutput;
    } DUMMYSTRUCTNAME2;
  } DUMMYUNIONNAME;
  short dmColor;
  short dmDuplex;
  short dmYResolution;
  short dmTTOption;
  short dmCollate;
  WCHAR dmFormName[CCHFORMNAME];
  WORD  dmLogPixels;
  DWORD dmBitsPerPel;
  DWORD dmPelsWidth;
  DWORD dmPelsHeight;
  union {
    DWORD dmDisplayFlags;
    DWORD dmNup;
  } DUMMYUNIONNAME2;
  DWORD dmDisplayFrequency;
  DWORD dmICMMethod;
  DWORD dmICMIntent;
  DWORD dmMediaType;
  DWORD dmDitherType;
  DWORD dmReserved1;
  DWORD dmReserved2;
  DWORD dmPanningWidth;
  DWORD dmPanningHeight;
} DEVMODEW, *PDEVMODEW, *NPDEVMODEW, *LPDEVMODEW;
#ifdef __clang__
#pragma clang diagnostic pop
#endif //__clang__

typedef struct tagMONITORINFO {
    DWORD cbSize;
    RECT  rcMonitor;
    RECT  rcWork;
    DWORD dwFlags;
} MONITORINFO, *LPMONITORINFO;

typedef struct tagMONITORINFOEXW {
    DWORD cbSize;
    RECT  rcMonitor;
    RECT  rcWork;
    DWORD dwFlags;
    WCHAR szDevice[CCHDEVICENAME];
} MONITORINFOEXW, *LPMONITORINFOEXW;

typedef struct _DISPLAY_DEVICEW {
  DWORD cb;
  WCHAR DeviceName[32];
  WCHAR DeviceString[128];
  DWORD StateFlags;
  WCHAR DeviceID[128];
  WCHAR DeviceKey[128];
} DISPLAY_DEVICEW, *PDISPLAY_DEVICEW, *LPDISPLAY_DEVICEW;

typedef struct tagWNDCLASSEXW {
  UINT      cbSize;
  UINT      style;
  WNDPROC   lpfnWndProc;
  int       cbClsExtra;
  int       cbWndExtra;
  HINSTANCE hInstance;
  HICON     hIcon;
  HCURSOR   hCursor;
  HBRUSH    hbrBackground;
  LPCWSTR   lpszMenuName;
  LPCWSTR   lpszClassName;
  HICON     hIconSm;
} WNDCLASSEXW, *PWNDCLASSEXW, *NPWNDCLASSEXW, *LPWNDCLASSEXW;

typedef struct _SECURITY_ATTRIBUTES {
  DWORD  nLength;
  LPVOID lpSecurityDescriptor;
  BOOL   bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct _GUID {
  unsigned long  Data1;
  unsigned short Data2;
  unsigned short Data3;
  unsigned char  Data4[8];
} GUID;
typedef struct tagRGBQUAD {
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
} RGBQUAD;
typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;
typedef struct tagBITMAPINFO {
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD          bmiColors[1];
} BITMAPINFO, *LPBITMAPINFO, *PBITMAPINFO;

typedef struct _STARTUPINFOA {
  DWORD  cb;
  LPSTR  lpReserved;
  LPSTR  lpDesktop;
  LPSTR  lpTitle;
  DWORD  dwX;
  DWORD  dwY;
  DWORD  dwXSize;
  DWORD  dwYSize;
  DWORD  dwXCountChars;
  DWORD  dwYCountChars;
  DWORD  dwFillAttribute;
  DWORD  dwFlags;
  WORD   wShowWindow;
  WORD   cbReserved2;
  LPBYTE lpReserved2;
  HANDLE hStdInput;
  HANDLE hStdOutput;
  HANDLE hStdError;
} STARTUPINFOA, *LPSTARTUPINFOA;

typedef struct _PROCESS_INFORMATION {
  HANDLE hProcess;
  HANDLE hThread;
  DWORD  dwProcessId;
  DWORD  dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;

#define MEM_COMMIT 0x00001000
#define MEM_RESERVE 0x00002000
#define MEM_DECOMMIT 0x00004000
#define MEM_RELEASE 0x00008000

#define PAGE_NOACCESS  0x01
#define PAGE_READWRITE 0x04

#define IMAGE_FILE_MACHINE_UNKNOWN           0
#define IMAGE_FILE_MACHINE_TARGET_HOST       0x0001  // Useful for indicating we want to interact with the host and not a WoW guest.
#define IMAGE_FILE_MACHINE_I386              0x014c  // Intel 386.
#define IMAGE_FILE_MACHINE_R3000             0x0162  // MIPS little-endian, 0x160 big-endian
#define IMAGE_FILE_MACHINE_R4000             0x0166  // MIPS little-endian
#define IMAGE_FILE_MACHINE_R10000            0x0168  // MIPS little-endian
#define IMAGE_FILE_MACHINE_WCEMIPSV2         0x0169  // MIPS little-endian WCE v2
#define IMAGE_FILE_MACHINE_ALPHA             0x0184  // Alpha_AXP
#define IMAGE_FILE_MACHINE_SH3               0x01a2  // SH3 little-endian
#define IMAGE_FILE_MACHINE_SH3DSP            0x01a3
#define IMAGE_FILE_MACHINE_SH3E              0x01a4  // SH3E little-endian
#define IMAGE_FILE_MACHINE_SH4               0x01a6  // SH4 little-endian
#define IMAGE_FILE_MACHINE_SH5               0x01a8  // SH5
#define IMAGE_FILE_MACHINE_ARM               0x01c0  // ARM Little-Endian
#define IMAGE_FILE_MACHINE_THUMB             0x01c2  // ARM Thumb/Thumb-2 Little-Endian
#define IMAGE_FILE_MACHINE_ARMNT             0x01c4  // ARM Thumb-2 Little-Endian
#define IMAGE_FILE_MACHINE_AM33              0x01d3
#define IMAGE_FILE_MACHINE_POWERPC           0x01F0  // IBM PowerPC Little-Endian
#define IMAGE_FILE_MACHINE_POWERPCFP         0x01f1
#define IMAGE_FILE_MACHINE_IA64              0x0200  // Intel 64
#define IMAGE_FILE_MACHINE_MIPS16            0x0266  // MIPS
#define IMAGE_FILE_MACHINE_ALPHA64           0x0284  // ALPHA64
#define IMAGE_FILE_MACHINE_MIPSFPU           0x0366  // MIPS
#define IMAGE_FILE_MACHINE_MIPSFPU16         0x0466  // MIPS
#define IMAGE_FILE_MACHINE_AXP64             IMAGE_FILE_MACHINE_ALPHA64
#define IMAGE_FILE_MACHINE_TRICORE           0x0520  // Infineon
#define IMAGE_FILE_MACHINE_CEF               0x0CEF
#define IMAGE_FILE_MACHINE_EBC               0x0EBC  // EFI Byte Code
#define IMAGE_FILE_MACHINE_AMD64             0x8664  // AMD64 (K8)
#define IMAGE_FILE_MACHINE_M32R              0x9041  // M32R little-endian
#define IMAGE_FILE_MACHINE_ARM64             0xAA64  // ARM64 Little-Endian
#define IMAGE_FILE_MACHINE_CEE               0xC0EE

#define ENUM_CURRENT_SETTINGS       ((DWORD)-1)
#define ENUM_REGISTRY_SETTINGS      ((DWORD)-2)

#define MONITOR_DEFAULTTONULL       0x00000000
#define MONITOR_DEFAULTTOPRIMARY    0x00000001
#define MONITOR_DEFAULTTONEAREST    0x00000002

#define MONITORINFOF_PRIMARY        0x00000001

#define CP_ACP                    0           // default to ANSI code page
#define CP_OEMCP                  1           // default to OEM  code page
#define CP_MACCP                  2           // default to MAC  code page
#define CP_THREAD_ACP             3           // current thread's ANSI code page
#define CP_SYMBOL                 42          // SYMBOL translations

#define CP_UTF7                   65000       // UTF-7 translation
#define CP_UTF8                   65001       // UTF-8 translation

typedef void* DPI_AWARENESS_CONTEXT;
#define DPI_AWARENESS_CONTEXT_UNAWARE              ((DPI_AWARENESS_CONTEXT)-1)
#define DPI_AWARENESS_CONTEXT_SYSTEM_AWARE         ((DPI_AWARENESS_CONTEXT)-2)
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE    ((DPI_AWARENESS_CONTEXT)-3)
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#define DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED    ((DPI_AWARENESS_CONTEXT)-5)

/*
 * Window Styles
 */
#define WS_OVERLAPPED       0x00000000L
#define WS_POPUP            0x80000000L
#define WS_CHILD            0x40000000L
#define WS_MINIMIZE         0x20000000L
#define WS_VISIBLE          0x10000000L
#define WS_DISABLED         0x08000000L
#define WS_CLIPSIBLINGS     0x04000000L
#define WS_CLIPCHILDREN     0x02000000L
#define WS_MAXIMIZE         0x01000000L
#define WS_CAPTION          0x00C00000L     /* WS_BORDER | WS_DLGFRAME  */
#define WS_BORDER           0x00800000L
#define WS_DLGFRAME         0x00400000L
#define WS_VSCROLL          0x00200000L
#define WS_HSCROLL          0x00100000L
#define WS_SYSMENU          0x00080000L
#define WS_THICKFRAME       0x00040000L
#define WS_GROUP            0x00020000L
#define WS_TABSTOP          0x00010000L

#define WS_MINIMIZEBOX      0x00020000L
#define WS_MAXIMIZEBOX      0x00010000L


#define WS_TILED            WS_OVERLAPPED
#define WS_ICONIC           WS_MINIMIZE
#define WS_SIZEBOX          WS_THICKFRAME
#define WS_TILEDWINDOW      WS_OVERLAPPEDWINDOW

/*
 * Common Window Styles
 */
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED     | \
                             WS_CAPTION        | \
                             WS_SYSMENU        | \
                             WS_THICKFRAME     | \
                             WS_MINIMIZEBOX    | \
                             WS_MAXIMIZEBOX)

#define WS_POPUPWINDOW      (WS_POPUP          | \
                             WS_BORDER         | \
                             WS_SYSMENU)

#define WS_CHILDWINDOW      (WS_CHILD)

/*
 * Extended Window Styles
 */
#define WS_EX_DLGMODALFRAME     0x00000001L
#define WS_EX_NOPARENTNOTIFY    0x00000004L
#define WS_EX_TOPMOST           0x00000008L
#define WS_EX_ACCEPTFILES       0x00000010L
#define WS_EX_TRANSPARENT       0x00000020L
#if(WINVER >= 0x0400)
#define WS_EX_MDICHILD          0x00000040L
#define WS_EX_TOOLWINDOW        0x00000080L
#define WS_EX_WINDOWEDGE        0x00000100L
#define WS_EX_CLIENTEDGE        0x00000200L
#define WS_EX_CONTEXTHELP       0x00000400L

#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0400)

#define WS_EX_RIGHT             0x00001000L
#define WS_EX_LEFT              0x00000000L
#define WS_EX_RTLREADING        0x00002000L
#define WS_EX_LTRREADING        0x00000000L
#define WS_EX_LEFTSCROLLBAR     0x00004000L
#define WS_EX_RIGHTSCROLLBAR    0x00000000L

#define WS_EX_CONTROLPARENT     0x00010000L
#define WS_EX_STATICEDGE        0x00020000L
#define WS_EX_APPWINDOW         0x00040000L


#define WS_EX_OVERLAPPEDWINDOW  (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
#define WS_EX_PALETTEWINDOW     (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)

#endif /* WINVER >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
#define WS_EX_LAYERED           0x00080000

#endif /* _WIN32_WINNT >= 0x0500 */


#if(WINVER >= 0x0500)
#define WS_EX_NOINHERITLAYOUT   0x00100000L // Disable inheritence of mirroring by children
#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0602)
#define WS_EX_NOREDIRECTIONBITMAP 0x00200000L
#endif /* WINVER >= 0x0602 */

#if(WINVER >= 0x0500)
#define WS_EX_LAYOUTRTL         0x00400000L // Right to left mirroring
#endif /* WINVER >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
#define WS_EX_COMPOSITED        0x02000000L
#endif /* _WIN32_WINNT >= 0x0501 */
#if(_WIN32_WINNT >= 0x0500)
#define WS_EX_NOACTIVATE        0x08000000L
#endif /* _WIN32_WINNT >= 0x0500 */


/*
 * Class styles
 */
#define CS_VREDRAW          0x0001
#define CS_HREDRAW          0x0002
#define CS_DBLCLKS          0x0008
#define CS_OWNDC            0x0020
#define CS_CLASSDC          0x0040
#define CS_PARENTDC         0x0080
#define CS_NOCLOSE          0x0200
#define CS_SAVEBITS         0x0800
#define CS_BYTEALIGNCLIENT  0x1000
#define CS_BYTEALIGNWINDOW  0x2000
#define CS_GLOBALCLASS      0x4000

#define CS_IME              0x00010000
#if(_WIN32_WINNT >= 0x0501)
#define CS_DROPSHADOW       0x00020000
#endif /* _WIN32_WINNT >= 0x0501 */

#define SW_HIDE             0
#define SW_SHOWNORMAL       1
#define SW_NORMAL           1
#define SW_SHOWMINIMIZED    2
#define SW_SHOWMAXIMIZED    3
#define SW_MAXIMIZE         3
#define SW_SHOWNOACTIVATE   4
#define SW_SHOW             5
#define SW_MINIMIZE         6
#define SW_SHOWMINNOACTIVE  7
#define SW_SHOWNA           8
#define SW_RESTORE          9
#define SW_SHOWDEFAULT      10
#define SW_FORCEMINIMIZE    11
#define SW_MAX              11

#define CW_USEDEFAULT       ((int)0x80000000)

/*
 * Window Messages
 */

#define WM_NULL                         0x0000
#define WM_CREATE                       0x0001
#define WM_DESTROY                      0x0002
#define WM_MOVE                         0x0003
#define WM_SIZE                         0x0005

#define WM_ACTIVATE                     0x0006
/*
 * WM_ACTIVATE state values
 */
#define     WA_INACTIVE     0
#define     WA_ACTIVE       1
#define     WA_CLICKACTIVE  2

#define WM_SETFOCUS                     0x0007
#define WM_KILLFOCUS                    0x0008
#define WM_ENABLE                       0x000A
#define WM_SETREDRAW                    0x000B
#define WM_SETTEXT                      0x000C
#define WM_GETTEXT                      0x000D
#define WM_GETTEXTLENGTH                0x000E
#define WM_PAINT                        0x000F
#define WM_CLOSE                        0x0010
#ifndef _WIN32_WCE
#define WM_QUERYENDSESSION              0x0011
#define WM_QUERYOPEN                    0x0013
#define WM_ENDSESSION                   0x0016
#endif
#define WM_QUIT                         0x0012
#define WM_ERASEBKGND                   0x0014
#define WM_SYSCOLORCHANGE               0x0015
#define WM_SHOWWINDOW                   0x0018
#define WM_WININICHANGE                 0x001A
#if(WINVER >= 0x0400)
#define WM_SETTINGCHANGE                WM_WININICHANGE
#endif /* WINVER >= 0x0400 */


#define WM_DEVMODECHANGE                0x001B
#define WM_ACTIVATEAPP                  0x001C
#define WM_FONTCHANGE                   0x001D
#define WM_TIMECHANGE                   0x001E
#define WM_CANCELMODE                   0x001F
#define WM_SETCURSOR                    0x0020
#define WM_MOUSEACTIVATE                0x0021
#define WM_CHILDACTIVATE                0x0022
#define WM_QUEUESYNC                    0x0023

#define WM_GETMINMAXINFO                0x0024

/*
 * Struct pointed to by WM_GETMINMAXINFO lParam
 */
typedef struct tagMINMAXINFO {
    POINT ptReserved;
    POINT ptMaxSize;
    POINT ptMaxPosition;
    POINT ptMinTrackSize;
    POINT ptMaxTrackSize;
} MINMAXINFO, *PMINMAXINFO, *LPMINMAXINFO;


#define WM_PAINTICON                    0x0026
#define WM_ICONERASEBKGND               0x0027
#define WM_NEXTDLGCTL                   0x0028
#define WM_SPOOLERSTATUS                0x002A
#define WM_DRAWITEM                     0x002B
#define WM_MEASUREITEM                  0x002C
#define WM_DELETEITEM                   0x002D
#define WM_VKEYTOITEM                   0x002E
#define WM_CHARTOITEM                   0x002F
#define WM_SETFONT                      0x0030
#define WM_GETFONT                      0x0031
#define WM_SETHOTKEY                    0x0032
#define WM_GETHOTKEY                    0x0033
#define WM_QUERYDRAGICON                0x0037
#define WM_COMPAREITEM                  0x0039
#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
#define WM_GETOBJECT                    0x003D
#endif
#endif /* WINVER >= 0x0500 */
#define WM_COMPACTING                   0x0041
#define WM_COMMNOTIFY                   0x0044  /* no longer suported */
#define WM_WINDOWPOSCHANGING            0x0046
#define WM_WINDOWPOSCHANGED             0x0047

#define WM_POWER                        0x0048
/*
 * wParam for WM_POWER window message and DRV_POWER driver notification
 */
#define PWR_OK              1
#define PWR_FAIL            (-1)
#define PWR_SUSPENDREQUEST  1
#define PWR_SUSPENDRESUME   2
#define PWR_CRITICALRESUME  3

#define WM_COPYDATA                     0x004A
#define WM_CANCELJOURNAL                0x004B



/*
 * lParam of WM_COPYDATA message points to...
 */
typedef struct tagCOPYDATASTRUCT {
    ULONG_PTR dwData;
    DWORD cbData;
    PVOID lpData;
} COPYDATASTRUCT, *PCOPYDATASTRUCT;

#if(WINVER >= 0x0400)
typedef struct tagMDINEXTMENU
{
    HMENU   hmenuIn;
    HMENU   hmenuNext;
    HWND    hwndNext;
} MDINEXTMENU, * PMDINEXTMENU, * LPMDINEXTMENU;
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)
#define WM_NOTIFY                       0x004E
#define WM_INPUTLANGCHANGEREQUEST       0x0050
#define WM_INPUTLANGCHANGE              0x0051
#define WM_TCARD                        0x0052
#define WM_HELP                         0x0053
#define WM_USERCHANGED                  0x0054
#define WM_NOTIFYFORMAT                 0x0055

#define NFR_ANSI                             1
#define NFR_UNICODE                          2
#define NF_QUERY                             3
#define NF_REQUERY                           4

#define WM_CONTEXTMENU                  0x007B
#define WM_STYLECHANGING                0x007C
#define WM_STYLECHANGED                 0x007D
#define WM_DISPLAYCHANGE                0x007E
#define WM_GETICON                      0x007F
#define WM_SETICON                      0x0080
#endif /* WINVER >= 0x0400 */

#define WM_NCCREATE                     0x0081
#define WM_NCDESTROY                    0x0082
#define WM_NCCALCSIZE                   0x0083
#define WM_NCHITTEST                    0x0084
#define WM_NCPAINT                      0x0085
#define WM_NCACTIVATE                   0x0086
#define WM_GETDLGCODE                   0x0087
#ifndef _WIN32_WCE
#define WM_SYNCPAINT                    0x0088
#endif
#define WM_NCMOUSEMOVE                  0x00A0
#define WM_NCLBUTTONDOWN                0x00A1
#define WM_NCLBUTTONUP                  0x00A2
#define WM_NCLBUTTONDBLCLK              0x00A3
#define WM_NCRBUTTONDOWN                0x00A4
#define WM_NCRBUTTONUP                  0x00A5
#define WM_NCRBUTTONDBLCLK              0x00A6
#define WM_NCMBUTTONDOWN                0x00A7
#define WM_NCMBUTTONUP                  0x00A8
#define WM_NCMBUTTONDBLCLK              0x00A9



#if(_WIN32_WINNT >= 0x0500)
#define WM_NCXBUTTONDOWN                0x00AB
#define WM_NCXBUTTONUP                  0x00AC
#define WM_NCXBUTTONDBLCLK              0x00AD
#endif /* _WIN32_WINNT >= 0x0500 */


#if(_WIN32_WINNT >= 0x0501)
#define WM_INPUT_DEVICE_CHANGE          0x00FE
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0501)
#define WM_INPUT                        0x00FF
#endif /* _WIN32_WINNT >= 0x0501 */

#define WM_KEYFIRST                     0x0100
#define WM_KEYDOWN                      0x0100
#define WM_KEYUP                        0x0101
#define WM_CHAR                         0x0102
#define WM_DEADCHAR                     0x0103
#define WM_SYSKEYDOWN                   0x0104
#define WM_SYSKEYUP                     0x0105
#define WM_SYSCHAR                      0x0106
#define WM_SYSDEADCHAR                  0x0107
#if(_WIN32_WINNT >= 0x0501)
#define WM_UNICHAR                      0x0109
#define WM_KEYLAST                      0x0109
#define UNICODE_NOCHAR                  0xFFFF
#else
#define WM_KEYLAST                      0x0108
#endif /* _WIN32_WINNT >= 0x0501 */

#if(WINVER >= 0x0400)
#define WM_IME_STARTCOMPOSITION         0x010D
#define WM_IME_ENDCOMPOSITION           0x010E
#define WM_IME_COMPOSITION              0x010F
#define WM_IME_KEYLAST                  0x010F
#endif /* WINVER >= 0x0400 */

#define WM_INITDIALOG                   0x0110
#define WM_COMMAND                      0x0111
#define WM_SYSCOMMAND                   0x0112
#define WM_TIMER                        0x0113
#define WM_HSCROLL                      0x0114
#define WM_VSCROLL                      0x0115
#define WM_INITMENU                     0x0116
#define WM_INITMENUPOPUP                0x0117
#if(WINVER >= 0x0601)
#define WM_GESTURE                      0x0119
#define WM_GESTURENOTIFY                0x011A
#endif /* WINVER >= 0x0601 */
#define WM_MENUSELECT                   0x011F
#define WM_MENUCHAR                     0x0120
#define WM_ENTERIDLE                    0x0121
#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
#define WM_MENURBUTTONUP                0x0122
#define WM_MENUDRAG                     0x0123
#define WM_MENUGETOBJECT                0x0124
#define WM_UNINITMENUPOPUP              0x0125
#define WM_MENUCOMMAND                  0x0126

#ifndef _WIN32_WCE
#if(_WIN32_WINNT >= 0x0500)
#define WM_CHANGEUISTATE                0x0127
#define WM_UPDATEUISTATE                0x0128
#define WM_QUERYUISTATE                 0x0129

/*
 * LOWORD(wParam) values in WM_*UISTATE*
 */
#define UIS_SET                         1
#define UIS_CLEAR                       2
#define UIS_INITIALIZE                  3

/*
 * HIWORD(wParam) values in WM_*UISTATE*
 */
#define UISF_HIDEFOCUS                  0x1
#define UISF_HIDEACCEL                  0x2
#if(_WIN32_WINNT >= 0x0501)
#define UISF_ACTIVE                     0x4
#endif /* _WIN32_WINNT >= 0x0501 */
#endif /* _WIN32_WINNT >= 0x0500 */
#endif

#endif
#endif /* WINVER >= 0x0500 */

#define WM_CTLCOLORMSGBOX               0x0132
#define WM_CTLCOLOREDIT                 0x0133
#define WM_CTLCOLORLISTBOX              0x0134
#define WM_CTLCOLORBTN                  0x0135
#define WM_CTLCOLORDLG                  0x0136
#define WM_CTLCOLORSCROLLBAR            0x0137
#define WM_CTLCOLORSTATIC               0x0138
#define MN_GETHMENU                     0x01E1

#define WM_MOUSEFIRST                   0x0200
#define WM_MOUSEMOVE                    0x0200
#define WM_LBUTTONDOWN                  0x0201
#define WM_LBUTTONUP                    0x0202
#define WM_LBUTTONDBLCLK                0x0203
#define WM_RBUTTONDOWN                  0x0204
#define WM_RBUTTONUP                    0x0205
#define WM_RBUTTONDBLCLK                0x0206
#define WM_MBUTTONDOWN                  0x0207
#define WM_MBUTTONUP                    0x0208
#define WM_MBUTTONDBLCLK                0x0209
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#define WM_MOUSEWHEEL                   0x020A
#endif
#if (_WIN32_WINNT >= 0x0500)
#define WM_XBUTTONDOWN                  0x020B
#define WM_XBUTTONUP                    0x020C
#define WM_XBUTTONDBLCLK                0x020D
#endif
#if (_WIN32_WINNT >= 0x0600)
#define WM_MOUSEHWHEEL                  0x020E
#endif

#if (_WIN32_WINNT >= 0x0600)
#define WM_MOUSELAST                    0x020E
#elif (_WIN32_WINNT >= 0x0500)
#define WM_MOUSELAST                    0x020D
#elif (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#define WM_MOUSELAST                    0x020A
#else
#define WM_MOUSELAST                    0x0209
#endif /* (_WIN32_WINNT >= 0x0600) */


#if(_WIN32_WINNT >= 0x0400)
/* Value for rolling one detent */
#define WHEEL_DELTA                     120
#define GET_WHEEL_DELTA_WPARAM(wParam)  ((short)HIWORD(wParam))

/* Setting to scroll one page for SPI_GET/SETWHEELSCROLLLINES */
#define WHEEL_PAGESCROLL                (UINT_MAX)
#endif /* _WIN32_WINNT >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
#define GET_KEYSTATE_WPARAM(wParam)     (LOWORD(wParam))
#define GET_NCHITTEST_WPARAM(wParam)    ((short)LOWORD(wParam))
#define GET_XBUTTON_WPARAM(wParam)      (HIWORD(wParam))

/* XButton values are WORD flags */
#define XBUTTON1      0x0001
#define XBUTTON2      0x0002
/* Were there to be an XBUTTON3, its value would be 0x0004 */
#endif /* _WIN32_WINNT >= 0x0500 */

#define WM_PARENTNOTIFY                 0x0210
#define WM_ENTERMENULOOP                0x0211
#define WM_EXITMENULOOP                 0x0212

#if(WINVER >= 0x0400)
#define WM_NEXTMENU                     0x0213
#define WM_SIZING                       0x0214
#define WM_CAPTURECHANGED               0x0215
#define WM_MOVING                       0x0216
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)


#define WM_POWERBROADCAST               0x0218

#ifndef _WIN32_WCE
#define PBT_APMQUERYSUSPEND             0x0000
#define PBT_APMQUERYSTANDBY             0x0001

#define PBT_APMQUERYSUSPENDFAILED       0x0002
#define PBT_APMQUERYSTANDBYFAILED       0x0003

#define PBT_APMSUSPEND                  0x0004
#define PBT_APMSTANDBY                  0x0005

#define PBT_APMRESUMECRITICAL           0x0006
#define PBT_APMRESUMESUSPEND            0x0007
#define PBT_APMRESUMESTANDBY            0x0008

#define PBTF_APMRESUMEFROMFAILURE       0x00000001

#define PBT_APMBATTERYLOW               0x0009
#define PBT_APMPOWERSTATUSCHANGE        0x000A

#define PBT_APMOEMEVENT                 0x000B


#define PBT_APMRESUMEAUTOMATIC          0x0012
#if (_WIN32_WINNT >= 0x0502)
#ifndef PBT_POWERSETTINGCHANGE
#define PBT_POWERSETTINGCHANGE          0x8013

typedef struct {
    GUID PowerSetting;
    DWORD DataLength;
    UCHAR Data[1];
} POWERBROADCAST_SETTING, *PPOWERBROADCAST_SETTING;


#endif // PBT_POWERSETTINGCHANGE

#endif // (_WIN32_WINNT >= 0x0502)
#endif

#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)
#define WM_DEVICECHANGE                 0x0219
#endif /* WINVER >= 0x0400 */

#define WM_MDICREATE                    0x0220
#define WM_MDIDESTROY                   0x0221
#define WM_MDIACTIVATE                  0x0222
#define WM_MDIRESTORE                   0x0223
#define WM_MDINEXT                      0x0224
#define WM_MDIMAXIMIZE                  0x0225
#define WM_MDITILE                      0x0226
#define WM_MDICASCADE                   0x0227
#define WM_MDIICONARRANGE               0x0228
#define WM_MDIGETACTIVE                 0x0229


#define WM_MDISETMENU                   0x0230
#define WM_ENTERSIZEMOVE                0x0231
#define WM_EXITSIZEMOVE                 0x0232
#define WM_DROPFILES                    0x0233
#define WM_MDIREFRESHMENU               0x0234

#if(WINVER >= 0x0602)
#define WM_POINTERDEVICECHANGE          0x238
#define WM_POINTERDEVICEINRANGE         0x239
#define WM_POINTERDEVICEOUTOFRANGE      0x23A
#endif /* WINVER >= 0x0602 */


#if(WINVER >= 0x0601)
#define WM_TOUCH                        0x0240
#endif /* WINVER >= 0x0601 */

#if(WINVER >= 0x0602)
#define WM_NCPOINTERUPDATE              0x0241
#define WM_NCPOINTERDOWN                0x0242
#define WM_NCPOINTERUP                  0x0243
#define WM_POINTERUPDATE                0x0245
#define WM_POINTERDOWN                  0x0246
#define WM_POINTERUP                    0x0247
#define WM_POINTERENTER                 0x0249
#define WM_POINTERLEAVE                 0x024A
#define WM_POINTERACTIVATE              0x024B
#define WM_POINTERCAPTURECHANGED        0x024C
#define WM_TOUCHHITTESTING              0x024D
#define WM_POINTERWHEEL                 0x024E
#define WM_POINTERHWHEEL                0x024F
#define DM_POINTERHITTEST               0x0250
#define WM_POINTERROUTEDTO              0x0251
#define WM_POINTERROUTEDAWAY            0x0252
#define WM_POINTERROUTEDRELEASED        0x0253
#endif /* WINVER >= 0x0602 */


#if(WINVER >= 0x0400)
#define WM_IME_SETCONTEXT               0x0281
#define WM_IME_NOTIFY                   0x0282
#define WM_IME_CONTROL                  0x0283
#define WM_IME_COMPOSITIONFULL          0x0284
#define WM_IME_SELECT                   0x0285
#define WM_IME_CHAR                     0x0286
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0500)
#define WM_IME_REQUEST                  0x0288
#endif /* WINVER >= 0x0500 */
#if(WINVER >= 0x0400)
#define WM_IME_KEYDOWN                  0x0290
#define WM_IME_KEYUP                    0x0291
#endif /* WINVER >= 0x0400 */

#if((_WIN32_WINNT >= 0x0400) || (WINVER >= 0x0500))
#define WM_MOUSEHOVER                   0x02A1
#define WM_MOUSELEAVE                   0x02A3
#endif
#if(WINVER >= 0x0500)
#define WM_NCMOUSEHOVER                 0x02A0
#define WM_NCMOUSELEAVE                 0x02A2
#endif /* WINVER >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
#define WM_WTSSESSION_CHANGE            0x02B1

#define WM_TABLET_FIRST                 0x02c0
#define WM_TABLET_LAST                  0x02df
#endif /* _WIN32_WINNT >= 0x0501 */

#if(WINVER >= 0x0601)
#define WM_DPICHANGED                   0x02E0
#endif /* WINVER >= 0x0601 */
#if(WINVER >= 0x0605)
#define WM_DPICHANGED_BEFOREPARENT      0x02E2
#define WM_DPICHANGED_AFTERPARENT       0x02E3
#define WM_GETDPISCALEDSIZE             0x02E4
#endif /* WINVER >= 0x0605 */

#define WM_CUT                          0x0300
#define WM_COPY                         0x0301
#define WM_PASTE                        0x0302
#define WM_CLEAR                        0x0303
#define WM_UNDO                         0x0304
#define WM_RENDERFORMAT                 0x0305
#define WM_RENDERALLFORMATS             0x0306
#define WM_DESTROYCLIPBOARD             0x0307
#define WM_DRAWCLIPBOARD                0x0308
#define WM_PAINTCLIPBOARD               0x0309
#define WM_VSCROLLCLIPBOARD             0x030A
#define WM_SIZECLIPBOARD                0x030B
#define WM_ASKCBFORMATNAME              0x030C
#define WM_CHANGECBCHAIN                0x030D
#define WM_HSCROLLCLIPBOARD             0x030E
#define WM_QUERYNEWPALETTE              0x030F
#define WM_PALETTEISCHANGING            0x0310
#define WM_PALETTECHANGED               0x0311
#define WM_HOTKEY                       0x0312

#if(WINVER >= 0x0400)
#define WM_PRINT                        0x0317
#define WM_PRINTCLIENT                  0x0318
#endif /* WINVER >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
#define WM_APPCOMMAND                   0x0319
#endif /* _WIN32_WINNT >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
#define WM_THEMECHANGED                 0x031A
#endif /* _WIN32_WINNT >= 0x0501 */


#if(_WIN32_WINNT >= 0x0501)
#define WM_CLIPBOARDUPDATE              0x031D
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0600)
#define WM_DWMCOMPOSITIONCHANGED        0x031E
#define WM_DWMNCRENDERINGCHANGED        0x031F
#define WM_DWMCOLORIZATIONCOLORCHANGED  0x0320
#define WM_DWMWINDOWMAXIMIZEDCHANGE     0x0321
#endif /* _WIN32_WINNT >= 0x0600 */

#if(_WIN32_WINNT >= 0x0601)
#define WM_DWMSENDICONICTHUMBNAIL           0x0323
#define WM_DWMSENDICONICLIVEPREVIEWBITMAP   0x0326
#endif /* _WIN32_WINNT >= 0x0601 */


#if(WINVER >= 0x0600)
#define WM_GETTITLEBARINFOEX            0x033F
#endif /* WINVER >= 0x0600 */

#if(WINVER >= 0x0400)
#endif /* WINVER >= 0x0400 */


#if(WINVER >= 0x0400)
#define WM_HANDHELDFIRST                0x0358
#define WM_HANDHELDLAST                 0x035F

#define WM_AFXFIRST                     0x0360
#define WM_AFXLAST                      0x037F
#endif /* WINVER >= 0x0400 */

#define WM_PENWINFIRST                  0x0380
#define WM_PENWINLAST                   0x038F


#if(WINVER >= 0x0400)
#define WM_APP                          0x8000
#endif /* WINVER >= 0x0400 */


/*
 * NOTE: All Message Numbers below 0x0400 are RESERVED.
 *
 * Private Window Messages Start Here:
 */
#define WM_USER                         0x0400

#if(WINVER >= 0x0400)

/*  wParam for WM_SIZING message  */
#define WMSZ_LEFT           1
#define WMSZ_RIGHT          2
#define WMSZ_TOP            3
#define WMSZ_TOPLEFT        4
#define WMSZ_TOPRIGHT       5
#define WMSZ_BOTTOM         6
#define WMSZ_BOTTOMLEFT     7
#define WMSZ_BOTTOMRIGHT    8
#endif /* WINVER >= 0x0400 */

#ifndef NONCMESSAGES

/*
 * WM_NCHITTEST and MOUSEHOOKSTRUCT Mouse Position Codes
 */
#define HTERROR             (-2)
#define HTTRANSPARENT       (-1)
#define HTNOWHERE           0
#define HTCLIENT            1
#define HTCAPTION           2
#define HTSYSMENU           3
#define HTGROWBOX           4
#define HTSIZE              HTGROWBOX
#define HTMENU              5
#define HTHSCROLL           6
#define HTVSCROLL           7
#define HTMINBUTTON         8
#define HTMAXBUTTON         9
#define HTLEFT              10
#define HTRIGHT             11
#define HTTOP               12
#define HTTOPLEFT           13
#define HTTOPRIGHT          14
#define HTBOTTOM            15
#define HTBOTTOMLEFT        16
#define HTBOTTOMRIGHT       17
#define HTBORDER            18
#define HTREDUCE            HTMINBUTTON
#define HTZOOM              HTMAXBUTTON
#define HTSIZEFIRST         HTLEFT
#define HTSIZELAST          HTBOTTOMRIGHT
#if(WINVER >= 0x0400)
#define HTOBJECT            19
#define HTCLOSE             20
#define HTHELP              21
#endif /* WINVER >= 0x0400 */


/*
 * SendMessageTimeout values
 */
#define SMTO_NORMAL         0x0000
#define SMTO_BLOCK          0x0001
#define SMTO_ABORTIFHUNG    0x0002
#if(WINVER >= 0x0500)
#define SMTO_NOTIMEOUTIFNOTHUNG 0x0008
#endif /* WINVER >= 0x0500 */
#if(WINVER >= 0x0600)
#define SMTO_ERRORONEXIT    0x0020
#endif /* WINVER >= 0x0600 */
#if(WINVER >= 0x0602)
#endif /* WINVER >= 0x0602 */

#endif /* !NONCMESSAGES */

/*
 * WM_MOUSEACTIVATE Return Codes
 */
#define MA_ACTIVATE         1
#define MA_ACTIVATEANDEAT   2
#define MA_NOACTIVATE       3
#define MA_NOACTIVATEANDEAT 4

/*
 * WM_SETICON / WM_GETICON Type Codes
 */
#define ICON_SMALL          0
#define ICON_BIG            1
#if(_WIN32_WINNT >= 0x0501)
#define ICON_SMALL2         2
#endif /* _WIN32_WINNT >= 0x0501 */



/*
 * WM_SIZE message wParam values
 */
#define SIZE_RESTORED       0
#define SIZE_MINIMIZED      1
#define SIZE_MAXIMIZED      2
#define SIZE_MAXSHOW        3
#define SIZE_MAXHIDE        4

/*
 * Obsolete constant names
 */
#define SIZENORMAL          SIZE_RESTORED
#define SIZEICONIC          SIZE_MINIMIZED
#define SIZEFULLSCREEN      SIZE_MAXIMIZED
#define SIZEZOOMSHOW        SIZE_MAXSHOW
#define SIZEZOOMHIDE        SIZE_MAXHIDE


/*
 * WM_WINDOWPOSCHANGING/CHANGED struct pointed to by lParam
 */
typedef struct tagWINDOWPOS {
    HWND    hwnd;
    HWND    hwndInsertAfter;
    int     x;
    int     y;
    int     cx;
    int     cy;
    UINT    flags;
} WINDOWPOS, *LPWINDOWPOS, *PWINDOWPOS;

/*
 * WM_NCCALCSIZE parameter structure
 */
typedef struct tagNCCALCSIZE_PARAMS {
    RECT       rgrc[3];
    PWINDOWPOS lppos;
} NCCALCSIZE_PARAMS, *LPNCCALCSIZE_PARAMS;

/*
 * WM_NCCALCSIZE "window valid rect" return values
 */
#define WVR_ALIGNTOP        0x0010
#define WVR_ALIGNLEFT       0x0020
#define WVR_ALIGNBOTTOM     0x0040
#define WVR_ALIGNRIGHT      0x0080
#define WVR_HREDRAW         0x0100
#define WVR_VREDRAW         0x0200
#define WVR_REDRAW         (WVR_HREDRAW | \
                            WVR_VREDRAW)
#define WVR_VALIDRECTS      0x0400


#ifndef NOKEYSTATES

/*
 * Key State Masks for Mouse Messages
 */
#define MK_LBUTTON          0x0001
#define MK_RBUTTON          0x0002
#define MK_SHIFT            0x0004
#define MK_CONTROL          0x0008
#define MK_MBUTTON          0x0010
#if(_WIN32_WINNT >= 0x0500)
#define MK_XBUTTON1         0x0020
#define MK_XBUTTON2         0x0040
#endif /* _WIN32_WINNT >= 0x0500 */

#endif /* !NOKEYSTATES */


#if(_WIN32_WINNT >= 0x0400)
#ifndef NOTRACKMOUSEEVENT

#define TME_HOVER       0x00000001
#define TME_LEAVE       0x00000002
#if(WINVER >= 0x0500)
#define TME_NONCLIENT   0x00000010
#endif /* WINVER >= 0x0500 */
#define TME_QUERY       0x40000000
#define TME_CANCEL      0x80000000


#define HOVER_DEFAULT   0xFFFFFFFF
#endif /* _WIN32_WINNT >= 0x0400 */

#if(_WIN32_WINNT >= 0x0400)

typedef struct tagTRACKMOUSEEVENT {
    DWORD cbSize;
    DWORD dwFlags;
    HWND  hwndTrack;
    DWORD dwHoverTime;
} TRACKMOUSEEVENT, *LPTRACKMOUSEEVENT;


#endif /* _WIN32_WINNT >= 0x0400 */

#if(_WIN32_WINNT >= 0x0400)

#endif /* !NOTRACKMOUSEEVENT */
#endif /* _WIN32_WINNT >= 0x0400 */

#define PM_NOREMOVE         0x0000
#define PM_REMOVE           0x0001
#define PM_NOYIELD          0x0002

#define HWND_BOTTOM ((HWND)1)
#define HWND_NOTOPMOST ((HWND)-2)
#define HWND_TOP ((HWND)0)
#define HWND_TOPMOST ((HWND)-1)

/*
 * SetWindowPos Flags
 */
#define SWP_NOSIZE          0x0001
#define SWP_NOMOVE          0x0002
#define SWP_NOZORDER        0x0004
#define SWP_NOREDRAW        0x0008
#define SWP_NOACTIVATE      0x0010
#define SWP_FRAMECHANGED    0x0020  /* The frame changed: send WM_NCCALCSIZE */
#define SWP_SHOWWINDOW      0x0040
#define SWP_HIDEWINDOW      0x0080
#define SWP_NOCOPYBITS      0x0100
#define SWP_NOOWNERZORDER   0x0200  /* Don't do owner Z ordering */
#define SWP_NOSENDCHANGING  0x0400  /* Don't send WM_WINDOWPOSCHANGING */

#define SWP_DRAWFRAME       SWP_FRAMECHANGED
#define SWP_NOREPOSITION    SWP_NOOWNERZORDER

#if(WINVER >= 0x0400)
#define SWP_DEFERERASE      0x2000 // same as SWP_DEFERDRAWING
#define SWP_ASYNCWINDOWPOS  0x4000 // same as SWP_CREATESPB
#endif /* WINVER >= 0x0400 */

#define FILE_READ_DATA            ( 0x0001 )    // file & pipe
#define FILE_LIST_DIRECTORY       ( 0x0001 )    // directory

#define FILE_WRITE_DATA           ( 0x0002 )    // file & pipe
#define FILE_ADD_FILE             ( 0x0002 )    // directory

#define FILE_APPEND_DATA          ( 0x0004 )    // file
#define FILE_ADD_SUBDIRECTORY     ( 0x0004 )    // directory
#define FILE_CREATE_PIPE_INSTANCE ( 0x0004 )    // named pipe


#define FILE_READ_EA              ( 0x0008 )    // file & directory

#define FILE_WRITE_EA             ( 0x0010 )    // file & directory

#define FILE_EXECUTE              ( 0x0020 )    // file
#define FILE_TRAVERSE             ( 0x0020 )    // directory

#define FILE_DELETE_CHILD         ( 0x0040 )    // directory

#define FILE_READ_ATTRIBUTES      ( 0x0080 )    // all

#define FILE_WRITE_ATTRIBUTES     ( 0x0100 )    // all

#define FILE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1FF)

#define FILE_GENERIC_READ         (STANDARD_RIGHTS_READ     |\
                                   FILE_READ_DATA           |\
                                   FILE_READ_ATTRIBUTES     |\
                                   FILE_READ_EA             |\
                                   SYNCHRONIZE)


#define FILE_GENERIC_WRITE        (STANDARD_RIGHTS_WRITE    |\
                                   FILE_WRITE_DATA          |\
                                   FILE_WRITE_ATTRIBUTES    |\
                                   FILE_WRITE_EA            |\
                                   FILE_APPEND_DATA         |\
                                   SYNCHRONIZE)


#define FILE_GENERIC_EXECUTE      (STANDARD_RIGHTS_EXECUTE  |\
                                   FILE_READ_ATTRIBUTES     |\
                                   FILE_EXECUTE             |\
                                   SYNCHRONIZE)

// end_access
#define FILE_SHARE_READ                 0x00000001  
#define FILE_SHARE_WRITE                0x00000002  
#define FILE_SHARE_DELETE               0x00000004  
#define FILE_ATTRIBUTE_READONLY             0x00000001  
#define FILE_ATTRIBUTE_HIDDEN               0x00000002  
#define FILE_ATTRIBUTE_SYSTEM               0x00000004  
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020  
#define FILE_ATTRIBUTE_DEVICE               0x00000040  
#define FILE_ATTRIBUTE_NORMAL               0x00000080  
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100  
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200  
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400  
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800  
#define FILE_ATTRIBUTE_OFFLINE              0x00001000  
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000  
#define FILE_ATTRIBUTE_ENCRYPTED            0x00004000  
#define FILE_ATTRIBUTE_INTEGRITY_STREAM     0x00008000  
#define FILE_ATTRIBUTE_VIRTUAL              0x00010000  
#define FILE_ATTRIBUTE_NO_SCRUB_DATA        0x00020000  
#define FILE_ATTRIBUTE_EA                   0x00040000  
#define FILE_ATTRIBUTE_PINNED               0x00080000  
#define FILE_ATTRIBUTE_UNPINNED             0x00100000  
#define FILE_ATTRIBUTE_RECALL_ON_OPEN       0x00040000  
#define FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS 0x00400000 
#define TREE_CONNECT_ATTRIBUTE_PRIVACY      0x00004000  
#define TREE_CONNECT_ATTRIBUTE_INTEGRITY    0x00008000  
#define TREE_CONNECT_ATTRIBUTE_GLOBAL       0x00000004  
#define TREE_CONNECT_ATTRIBUTE_PINNED       0x00000002  
#define FILE_ATTRIBUTE_STRICTLY_SEQUENTIAL  0x20000000  
#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001   
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002   
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004   
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008   
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010   
#define FILE_NOTIFY_CHANGE_LAST_ACCESS  0x00000020   
#define FILE_NOTIFY_CHANGE_CREATION     0x00000040   
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100   
#define FILE_ACTION_ADDED                   0x00000001   
#define FILE_ACTION_REMOVED                 0x00000002   
#define FILE_ACTION_MODIFIED                0x00000003   
#define FILE_ACTION_RENAMED_OLD_NAME        0x00000004   
#define FILE_ACTION_RENAMED_NEW_NAME        0x00000005   
#define MAILSLOT_NO_MESSAGE             ((DWORD)-1) 
#define MAILSLOT_WAIT_FOREVER           ((DWORD)-1) 
#define FILE_CASE_SENSITIVE_SEARCH          0x00000001  
#define FILE_CASE_PRESERVED_NAMES           0x00000002  
#define FILE_UNICODE_ON_DISK                0x00000004  
#define FILE_PERSISTENT_ACLS                0x00000008  
#define FILE_FILE_COMPRESSION               0x00000010  
#define FILE_VOLUME_QUOTAS                  0x00000020  
#define FILE_SUPPORTS_SPARSE_FILES          0x00000040  
#define FILE_SUPPORTS_REPARSE_POINTS        0x00000080  
#define FILE_SUPPORTS_REMOTE_STORAGE        0x00000100  
#define FILE_RETURNS_CLEANUP_RESULT_INFO    0x00000200  
#define FILE_SUPPORTS_POSIX_UNLINK_RENAME   0x00000400  




#define FILE_VOLUME_IS_COMPRESSED           0x00008000  
#define FILE_SUPPORTS_OBJECT_IDS            0x00010000  
#define FILE_SUPPORTS_ENCRYPTION            0x00020000  
#define FILE_NAMED_STREAMS                  0x00040000  
#define FILE_READ_ONLY_VOLUME               0x00080000  
#define FILE_SEQUENTIAL_WRITE_ONCE          0x00100000  
#define FILE_SUPPORTS_TRANSACTIONS          0x00200000  
#define FILE_SUPPORTS_HARD_LINKS            0x00400000  
#define FILE_SUPPORTS_EXTENDED_ATTRIBUTES   0x00800000  
#define FILE_SUPPORTS_OPEN_BY_FILE_ID       0x01000000  
#define FILE_SUPPORTS_USN_JOURNAL           0x02000000  
#define FILE_SUPPORTS_INTEGRITY_STREAMS     0x04000000  
#define FILE_SUPPORTS_BLOCK_REFCOUNTING     0x08000000  
#define FILE_SUPPORTS_SPARSE_VDL            0x10000000  
#define FILE_DAX_VOLUME                     0x20000000  
#define FILE_SUPPORTS_GHOSTING              0x40000000  

#define FILE_INVALID_FILE_ID               ((LONGLONG)-1LL) 

#define DELETE                           (0x00010000L)
#define READ_CONTROL                     (0x00020000L)
#define WRITE_DAC                        (0x00040000L)
#define WRITE_OWNER                      (0x00080000L)
#define SYNCHRONIZE                      (0x00100000L)

#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)

#define STANDARD_RIGHTS_READ             (READ_CONTROL)
#define STANDARD_RIGHTS_WRITE            (READ_CONTROL)
#define STANDARD_RIGHTS_EXECUTE          (READ_CONTROL)

#define STANDARD_RIGHTS_ALL              (0x001F0000L)

#define SPECIFIC_RIGHTS_ALL              (0x0000FFFFL)

#define CREATE_ALWAYS 2
#define CREATE_NEW 1
#define OPEN_ALWAYS 4
#define OPEN_EXISTING 3
#define TRUNCATE_EXISTING 5

#define INVALID_HANDLE_VALUE ((HANDLE)-1)

#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L
#define BI_JPEG       4L
#define BI_PNG        5L

#define DIB_RGB_COLORS      0 /* color table in RGBs */
#define DIB_PAL_COLORS      1 /* color table in palette indices */

#define SRCCOPY             (DWORD)0x00CC0020 /* dest = source                   */
#define SRCPAINT            (DWORD)0x00EE0086 /* dest = source OR dest           */
#define SRCAND              (DWORD)0x008800C6 /* dest = source AND dest          */
#define SRCINVERT           (DWORD)0x00660046 /* dest = source XOR dest          */
#define SRCERASE            (DWORD)0x00440328 /* dest = source AND (NOT dest )   */
#define NOTSRCCOPY          (DWORD)0x00330008 /* dest = (NOT source)             */
#define NOTSRCERASE         (DWORD)0x001100A6 /* dest = (NOT src) AND (NOT dest) */
#define MERGECOPY           (DWORD)0x00C000CA /* dest = (source AND pattern)     */
#define MERGEPAINT          (DWORD)0x00BB0226 /* dest = (NOT source) OR dest     */
#define PATCOPY             (DWORD)0x00F00021 /* dest = pattern                  */
#define PATPAINT            (DWORD)0x00FB0A09 /* dest = DPSnoo                   */
#define PATINVERT           (DWORD)0x005A0049 /* dest = pattern XOR dest         */
#define DSTINVERT           (DWORD)0x00550009 /* dest = (NOT dest)               */
#define BLACKNESS           (DWORD)0x00000042 /* dest = BLACK                    */
#define WHITENESS           (DWORD)0x00FF0062 /* dest = WHITE                    */

#define MONITOR_DEFAULTTONULL       0x00000000
#define MONITOR_DEFAULTTOPRIMARY    0x00000001
#define MONITOR_DEFAULTTONEAREST    0x00000002

WINDOWS_IMPORT void WINAPI GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);

WINDOWS_IMPORT void* WINAPI VirtualAlloc(void *lpAddress, size_t dwSize, u32 flAllocationType, u32 flProtect);
WINDOWS_IMPORT s32 WINAPI VirtualFree(void *lpAddress, size_t dwSize, u32 dwFreeType);

WINDOWS_IMPORT size_t WINAPI VirtualQuery(void* lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, u32 dwLength);

WINDOWS_IMPORT void* WINAPI GetStdHandle(u32 nStdHandle);
WINDOWS_IMPORT BOOL WINAPI SetStdHandle( DWORD nStdHandle, HANDLE hHandle);

WINDOWS_IMPORT s32 WINAPI WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
WINDOWS_IMPORT BOOL WINAPI ReadFile( HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);

WINDOWS_IMPORT void* WINAPI GetCurrentProcess(void);
WINDOWS_IMPORT void* WINAPI GetCurrentThread(void);
WINDOWS_IMPORT BOOL WINAPI SymInitialize(HANDLE hProcess, PCSTR UserSearchPath, BOOL fInvadeProcess);
WINDOWS_IMPORT int WINAPI SymCleanup(HANDLE hProcess);
WINDOWS_IMPORT BOOL WINAPI SymFromAddr(HANDLE hProcess, DWORD64 Address, PDWORD64 Displacement, PSYMBOL_INFO Symbol);
WINDOWS_IMPORT int WINAPI SymGetLineFromAddr64(HANDLE hProcess, DWORD64 dwAddr, PDWORD pdwDisplacement, PIMAGEHLP_LINE64 Line);
WINDOWS_IMPORT HANDLE WINAPI SymFunctionTableAccess64(HANDLE hProcess, DWORD64 AddrBase);
WINDOWS_IMPORT DWORD64 WINAPI SymGetModuleBase64(HANDLE hProcess, DWORD64 Address);
typedef BOOL (__stdcall *PREAD_PROCESS_MEMORY_ROUTINE64)( HANDLE hProcess, DWORD64 qwBaseAddress,  PVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead);
typedef PVOID (__stdcall *PFUNCTION_TABLE_ACCESS_ROUTINE64)( HANDLE ahProcess, DWORD64 AddrBase);
typedef DWORD64 (__stdcall *PGET_MODULE_BASE_ROUTINE64)( HANDLE hProcess, DWORD64 Address);
typedef DWORD64 (__stdcall *PTRANSLATE_ADDRESS_ROUTINE64)( HANDLE hProcess, HANDLE hThread, LPADDRESS64 lpaddr);
WINDOWS_IMPORT BOOL WINAPI StackWalk64( DWORD MachineType, HANDLE hProcess, HANDLE hThread, LPSTACKFRAME64 StackFrame, PVOID ContextRecord, PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine, PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine, PGET_MODULE_BASE_ROUTINE64 GetModuleBaseRoutine, PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress);
WINDOWS_IMPORT void WINAPI RtlCaptureContext(PCONTEXT ContextRecord);

WINDOWS_IMPORT BOOL WINAPI GetMonitorInfoW( HMONITOR hMonitor, LPMONITORINFO lpmi);
WINDOWS_IMPORT BOOL WINAPI EnumDisplaySettingsW( LPCWSTR lpszDeviceName, DWORD iModeNum, DEVMODEW *lpDevMode);

WINDOWS_IMPORT BOOL WINAPI EnumDisplayDevicesW( LPCWSTR lpDevice, DWORD iDevNum, PDISPLAY_DEVICEW lpDisplayDevice, DWORD dwFlags);



WINDOWS_IMPORT HMONITOR WINAPI MonitorFromWindow( HWND hwnd, DWORD dwFlags);

WINDOWS_IMPORT int WINAPI WideCharToMultiByte( UINT CodePage, DWORD dwFlags, LPCWCH lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar);

typedef BOOL (*MONITORENUMPROC)( HMONITOR unnamedParam1, HDC unnamedParam2, LPRECT unnamedParam3, LPARAM unnamedParam4);
WINDOWS_IMPORT BOOL WINAPI EnumDisplayMonitors( HDC hdc, LPCRECT lprcClip, MONITORENUMPROC lpfnEnum, LPARAM dwData);

WINDOWS_IMPORT HMODULE WINAPI GetModuleHandleA(LPCSTR lpModuleName);
WINDOWS_IMPORT HMODULE WINAPI GetModuleHandleW(LPCWSTR lpModuleName);

WINDOWS_IMPORT ATOM WINAPI RegisterClassExW(const WNDCLASSEXW *unnamedParam1);

WINDOWS_IMPORT BOOL WINAPI AdjustWindowRectEx( LPRECT lpRect, DWORD  dwStyle, BOOL   bMenu, DWORD  dwExStyle);

WINDOWS_IMPORT DWORD WINAPI GetLastError(void);
WINDOWS_IMPORT void WINAPI SetLastError(DWORD);

WINDOWS_IMPORT HWND WINAPI CreateWindowExW(
    DWORD     dwExStyle,
    LPCWSTR   lpClassName,
    LPCWSTR   lpWindowName,
    DWORD     dwStyle,
    int       X,
    int       Y,
    int       nWidth,
    int       nHeight,
    HWND      hWndParent,
    HMENU     hMenu,
    HINSTANCE hInstance,
    LPVOID    lpParam
);
WINDOWS_IMPORT BOOL WINAPI UpdateWindow(HWND hWnd);
WINDOWS_IMPORT BOOL WINAPI ShowWindow( HWND hWnd, int  nCmdShow);

WINDOWS_IMPORT int WINAPI MultiByteToWideChar( UINT CodePage, DWORD dwFlags, LPCCH lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);

WINDOWS_IMPORT BOOL WINAPI PeekMessageW( LPMSG lpMsg, HWND  hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax, UINT  wRemoveMsg);

WINDOWS_IMPORT BOOL WINAPI TranslateMessage(const MSG *lpMsg);

WINDOWS_IMPORT LRESULT WINAPI DispatchMessageW(const MSG *lpMsg);

WINDOWS_IMPORT LRESULT WINAPI DefWindowProcW(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);

WINDOWS_IMPORT BOOL WINAPI DestroyWindow(HWND hWnd);

WINDOWS_IMPORT LONG WINAPI GetWindowLongW( HWND hWnd, int nIndex);
WINDOWS_IMPORT LONG WINAPI SetWindowLongW(HWND hWnd, int nIndex, LONG dwNewLong);
WINDOWS_IMPORT BOOL WINAPI SetWindowPos( HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);

WINDOWS_IMPORT BOOL WINAPI CreatePipe( HANDLE* hReadPipe, HANDLE* hWritePipe, LPSECURITY_ATTRIBUTES lpPipeAttributes, DWORD nSize);

WINDOWS_IMPORT BOOL WINAPI CloseHandle(HANDLE hObject);

WINDOWS_IMPORT HANDLE WINAPI CreateFileW( LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

WINDOWS_IMPORT BOOL WINAPI GetFileSizeEx( HANDLE hFile, PLARGE_INTEGER lpFileSize);

WINDOWS_IMPORT BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
WINDOWS_IMPORT BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);

WINDOWS_IMPORT DWORD_PTR WINAPI SetThreadAffinityMask( HANDLE hThread, DWORD_PTR dwThreadAffinityMask);

WINDOWS_IMPORT BOOL WINAPI GetClientRect( HWND hWnd, LPRECT lpRect);

WINDOWS_IMPORT HBITMAP WINAPI CreateDIBSection( HDC hdc, BITMAPINFO  *pbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset);

WINDOWS_IMPORT HDC WINAPI GetDC(HWND hWnd);

WINDOWS_IMPORT int WINAPI StretchDIBits( HDC hdc, int xDest, int yDest, int DestWidth, int DestHeight, int xSrc, int ySrc, int SrcWidth, int SrcHeight, PVOID lpBits, PBITMAPINFO lpbmi, UINT iUsage, DWORD rop);

WINDOWS_IMPORT BOOL WINAPI DeleteObject(HGDIOBJ ho);

WINDOWS_IMPORT HMONITOR WINAPI MonitorFromWindow(HWND hwnd,DWORD dwFlags);

WINDOWS_IMPORT HMODULE WINAPI LoadLibraryA(LPCSTR lpLibFileName);
WINDOWS_IMPORT void* WINAPI GetProcAddress(HMODULE hModule,LPCSTR  lpProcName);

WINDOWS_IMPORT u32 WINAPI timeBeginPeriod(UINT uPeriod);

WINDOWS_IMPORT BOOL WINAPI SetPriorityClass(HANDLE hProcess,DWORD  dwPriorityClass);

WINDOWS_IMPORT BOOL WINAPI SetThreadPriority(HANDLE hThread,int    nPriority);

WINDOWS_IMPORT HMODULE WINAPI LoadLibraryA(LPCSTR lpLibFileName);

WINDOWS_IMPORT BOOL WINAPI CreateProcessA( LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);

WINDOWS_IMPORT DWORD WINAPI WaitForSingleObject(HANDLE hHandle,DWORD  dwMilliseconds);

WINDOWS_IMPORT BOOL WINAPI GetExitCodeProcess(HANDLE  hProcess,LPDWORD lpExitCode);

typedef enum DXGI_FORMAT {
  DXGI_FORMAT_UNKNOWN = 0,
  DXGI_FORMAT_R32G32B32A32_TYPELESS = 1,
  DXGI_FORMAT_R32G32B32A32_FLOAT = 2,
  DXGI_FORMAT_R32G32B32A32_UINT = 3,
  DXGI_FORMAT_R32G32B32A32_SINT = 4,
  DXGI_FORMAT_R32G32B32_TYPELESS = 5,
  DXGI_FORMAT_R32G32B32_FLOAT = 6,
  DXGI_FORMAT_R32G32B32_UINT = 7,
  DXGI_FORMAT_R32G32B32_SINT = 8,
  DXGI_FORMAT_R16G16B16A16_TYPELESS = 9,
  DXGI_FORMAT_R16G16B16A16_FLOAT = 10,
  DXGI_FORMAT_R16G16B16A16_UNORM = 11,
  DXGI_FORMAT_R16G16B16A16_UINT = 12,
  DXGI_FORMAT_R16G16B16A16_SNORM = 13,
  DXGI_FORMAT_R16G16B16A16_SINT = 14,
  DXGI_FORMAT_R32G32_TYPELESS = 15,
  DXGI_FORMAT_R32G32_FLOAT = 16,
  DXGI_FORMAT_R32G32_UINT = 17,
  DXGI_FORMAT_R32G32_SINT = 18,
  DXGI_FORMAT_R32G8X24_TYPELESS = 19,
  DXGI_FORMAT_D32_FLOAT_S8X24_UINT = 20,
  DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
  DXGI_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
  DXGI_FORMAT_R10G10B10A2_TYPELESS = 23,
  DXGI_FORMAT_R10G10B10A2_UNORM = 24,
  DXGI_FORMAT_R10G10B10A2_UINT = 25,
  DXGI_FORMAT_R11G11B10_FLOAT = 26,
  DXGI_FORMAT_R8G8B8A8_TYPELESS = 27,
  DXGI_FORMAT_R8G8B8A8_UNORM = 28,
  DXGI_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
  DXGI_FORMAT_R8G8B8A8_UINT = 30,
  DXGI_FORMAT_R8G8B8A8_SNORM = 31,
  DXGI_FORMAT_R8G8B8A8_SINT = 32,
  DXGI_FORMAT_R16G16_TYPELESS = 33,
  DXGI_FORMAT_R16G16_FLOAT = 34,
  DXGI_FORMAT_R16G16_UNORM = 35,
  DXGI_FORMAT_R16G16_UINT = 36,
  DXGI_FORMAT_R16G16_SNORM = 37,
  DXGI_FORMAT_R16G16_SINT = 38,
  DXGI_FORMAT_R32_TYPELESS = 39,
  DXGI_FORMAT_D32_FLOAT = 40,
  DXGI_FORMAT_R32_FLOAT = 41,
  DXGI_FORMAT_R32_UINT = 42,
  DXGI_FORMAT_R32_SINT = 43,
  DXGI_FORMAT_R24G8_TYPELESS = 44,
  DXGI_FORMAT_D24_UNORM_S8_UINT = 45,
  DXGI_FORMAT_R24_UNORM_X8_TYPELESS = 46,
  DXGI_FORMAT_X24_TYPELESS_G8_UINT = 47,
  DXGI_FORMAT_R8G8_TYPELESS = 48,
  DXGI_FORMAT_R8G8_UNORM = 49,
  DXGI_FORMAT_R8G8_UINT = 50,
  DXGI_FORMAT_R8G8_SNORM = 51,
  DXGI_FORMAT_R8G8_SINT = 52,
  DXGI_FORMAT_R16_TYPELESS = 53,
  DXGI_FORMAT_R16_FLOAT = 54,
  DXGI_FORMAT_D16_UNORM = 55,
  DXGI_FORMAT_R16_UNORM = 56,
  DXGI_FORMAT_R16_UINT = 57,
  DXGI_FORMAT_R16_SNORM = 58,
  DXGI_FORMAT_R16_SINT = 59,
  DXGI_FORMAT_R8_TYPELESS = 60,
  DXGI_FORMAT_R8_UNORM = 61,
  DXGI_FORMAT_R8_UINT = 62,
  DXGI_FORMAT_R8_SNORM = 63,
  DXGI_FORMAT_R8_SINT = 64,
  DXGI_FORMAT_A8_UNORM = 65,
  DXGI_FORMAT_R1_UNORM = 66,
  DXGI_FORMAT_R9G9B9E5_SHAREDEXP = 67,
  DXGI_FORMAT_R8G8_B8G8_UNORM = 68,
  DXGI_FORMAT_G8R8_G8B8_UNORM = 69,
  DXGI_FORMAT_BC1_TYPELESS = 70,
  DXGI_FORMAT_BC1_UNORM = 71,
  DXGI_FORMAT_BC1_UNORM_SRGB = 72,
  DXGI_FORMAT_BC2_TYPELESS = 73,
  DXGI_FORMAT_BC2_UNORM = 74,
  DXGI_FORMAT_BC2_UNORM_SRGB = 75,
  DXGI_FORMAT_BC3_TYPELESS = 76,
  DXGI_FORMAT_BC3_UNORM = 77,
  DXGI_FORMAT_BC3_UNORM_SRGB = 78,
  DXGI_FORMAT_BC4_TYPELESS = 79,
  DXGI_FORMAT_BC4_UNORM = 80,
  DXGI_FORMAT_BC4_SNORM = 81,
  DXGI_FORMAT_BC5_TYPELESS = 82,
  DXGI_FORMAT_BC5_UNORM = 83,
  DXGI_FORMAT_BC5_SNORM = 84,
  DXGI_FORMAT_B5G6R5_UNORM = 85,
  DXGI_FORMAT_B5G5R5A1_UNORM = 86,
  DXGI_FORMAT_B8G8R8A8_UNORM = 87,
  DXGI_FORMAT_B8G8R8X8_UNORM = 88,
  DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
  DXGI_FORMAT_B8G8R8A8_TYPELESS = 90,
  DXGI_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
  DXGI_FORMAT_B8G8R8X8_TYPELESS = 92,
  DXGI_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
  DXGI_FORMAT_BC6H_TYPELESS = 94,
  DXGI_FORMAT_BC6H_UF16 = 95,
  DXGI_FORMAT_BC6H_SF16 = 96,
  DXGI_FORMAT_BC7_TYPELESS = 97,
  DXGI_FORMAT_BC7_UNORM = 98,
  DXGI_FORMAT_BC7_UNORM_SRGB = 99,
  DXGI_FORMAT_AYUV = 100,
  DXGI_FORMAT_Y410 = 101,
  DXGI_FORMAT_Y416 = 102,
  DXGI_FORMAT_NV12 = 103,
  DXGI_FORMAT_P010 = 104,
  DXGI_FORMAT_P016 = 105,
  DXGI_FORMAT_420_OPAQUE = 106,
  DXGI_FORMAT_YUY2 = 107,
  DXGI_FORMAT_Y210 = 108,
  DXGI_FORMAT_Y216 = 109,
  DXGI_FORMAT_NV11 = 110,
  DXGI_FORMAT_AI44 = 111,
  DXGI_FORMAT_IA44 = 112,
  DXGI_FORMAT_P8 = 113,
  DXGI_FORMAT_A8P8 = 114,
  DXGI_FORMAT_B4G4R4A4_UNORM = 115,
  DXGI_FORMAT_P208 = 130,
  DXGI_FORMAT_V208 = 131,
  DXGI_FORMAT_V408 = 132,
  DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE,
  DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE,
 
} DXGI_FORMAT ;
#define  DXGI_FORMAT_FORCE_UINT 0xffffffff

typedef enum DXGI_MODE_ROTATION { 
  DXGI_MODE_ROTATION_UNSPECIFIED  = 0,
  DXGI_MODE_ROTATION_IDENTITY     = 1,
  DXGI_MODE_ROTATION_ROTATE90     = 2,
  DXGI_MODE_ROTATION_ROTATE180    = 3,
  DXGI_MODE_ROTATION_ROTATE270    = 4
} DXGI_MODE_ROTATION;

typedef struct DXGI_OUTPUT_DESC
    {
    WCHAR DeviceName[ 32 ];
    RECT DesktopCoordinates;
    BOOL AttachedToDesktop;
    DXGI_MODE_ROTATION Rotation;
    HMONITOR Monitor;
    } 	DXGI_OUTPUT_DESC;

typedef struct DXGI_RATIONAL
{
    UINT Numerator;
    UINT Denominator;
} DXGI_RATIONAL;

typedef enum DXGI_MODE_SCANLINE_ORDER { 
  DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED        = 0,
  DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE        = 1,
  DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST  = 2,
  DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST  = 3
} DXGI_MODE_SCANLINE_ORDER;

typedef enum DXGI_MODE_SCALING { 
  DXGI_MODE_SCALING_UNSPECIFIED  = 0,
  DXGI_MODE_SCALING_CENTERED     = 1,
  DXGI_MODE_SCALING_STRETCHED    = 2
} DXGI_MODE_SCALING;
typedef struct DXGI_MODE_DESC
{
    UINT Width;
    UINT Height;
    DXGI_RATIONAL RefreshRate;
    DXGI_FORMAT Format;
    DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
    DXGI_MODE_SCALING Scaling;
} DXGI_MODE_DESC;


typedef struct DXGI_GAMMA_CONTROL_CAPABILITIES
{
    BOOL ScaleAndOffsetSupported;
    float MaxConvertedValue;
    float MinConvertedValue;
    UINT NumGammaControlPoints;
    float ControlPointPositions[1025];
} DXGI_GAMMA_CONTROL_CAPABILITIES;


typedef struct DXGI_RGB {
    float Red;
    float Green;
    float Blue;
} DXGI_RGB;
typedef struct DXGI_GAMMA_CONTROL
{
    DXGI_RGB Scale;
    DXGI_RGB Offset;
    DXGI_RGB GammaCurve[ 1025 ];
} DXGI_GAMMA_CONTROL;

typedef struct DXGI_FRAME_STATISTICS
    {
    UINT PresentCount;
    UINT PresentRefreshCount;
    UINT SyncRefreshCount;
    LARGE_INTEGER SyncQPCTime;
    LARGE_INTEGER SyncGPUTime;
    } 	DXGI_FRAME_STATISTICS;

typedef struct LUID {
    DWORD LowPart;
    LONG HighPart;
} LUID;
typedef struct DXGI_ADAPTER_DESC
    {
    WCHAR Description[ 128 ];
    UINT VendorId;
    UINT DeviceId;
    UINT SubSysId;
    UINT Revision;
    size_t DedicatedVideoMemory;
    size_t DedicatedSystemMemory;
    size_t SharedSystemMemory;
    LUID AdapterLuid;
    } 	DXGI_ADAPTER_DESC;

typedef struct DXGI_SAMPLE_DESC {
  UINT Count;
  UINT Quality;
} DXGI_SAMPLE_DESC;
typedef enum DXGI_SWAP_EFFECT {
  DXGI_SWAP_EFFECT_DISCARD = 0,
  DXGI_SWAP_EFFECT_SEQUENTIAL = 1,
  DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL = 3,
  DXGI_SWAP_EFFECT_FLIP_DISCARD = 4
} DXGI_SWAP_EFFECT;
#define DXGI_CPU_ACCESS_NONE    ( 0 )
#define DXGI_CPU_ACCESS_DYNAMIC    ( 1 )
#define DXGI_CPU_ACCESS_READ_WRITE    ( 2 )
#define DXGI_CPU_ACCESS_SCRATCH    ( 3 )
#define DXGI_CPU_ACCESS_FIELD        15
#define DXGI_USAGE_SHADER_INPUT             ( 1L << (0 + 4) )
#define DXGI_USAGE_RENDER_TARGET_OUTPUT     ( 1L << (1 + 4) )
#define DXGI_USAGE_BACK_BUFFER              ( 1L << (2 + 4) )
#define DXGI_USAGE_SHARED                   ( 1L << (3 + 4) )
#define DXGI_USAGE_READ_ONLY                ( 1L << (4 + 4) )
#define DXGI_USAGE_DISCARD_ON_PRESENT       ( 1L << (5 + 4) )
#define DXGI_USAGE_UNORDERED_ACCESS         ( 1L << (6 + 4) )
typedef UINT DXGI_USAGE;
typedef struct DXGI_SWAP_CHAIN_DESC {
  DXGI_MODE_DESC   BufferDesc;
  DXGI_SAMPLE_DESC SampleDesc;
  DXGI_USAGE       BufferUsage;
  UINT             BufferCount;
  HWND             OutputWindow;
  BOOL             Windowed;
  DXGI_SWAP_EFFECT SwapEffect;
  UINT             Flags;
} DXGI_SWAP_CHAIN_DESC;

typedef struct IUnknownVtbl {
    HRESULT (*QueryInterface)(void *This, const GUID *riid, void **ppvObject);
    ULONG (*AddRef)(void *This);
    ULONG (*Release)(void *This);
} IUnknownVtbl;
typedef struct IDXGIObjectVtbl {
    IUnknownVtbl parent; // Inherits from IUnknown

    HRESULT (*SetPrivateData)(void *This, const GUID *Name, UINT DataSize, const void *pData);
    HRESULT (*SetPrivateDataInterface)(void *This, const GUID *Name, const void *pUnknown);
    HRESULT (*GetPrivateData)(void *This, const GUID *Name, UINT *pDataSize, void *pData);
    HRESULT (*GetParent)(void *This, const GUID *riid, void **ppParent);
} IDXGIObjectVtbl;

typedef struct IDXGIObject {
    const IDXGIObjectVtbl *lpVtbl;
} IDXGIObject;


typedef struct IDXGIOutputVtbl {
    IUnknownVtbl parent; // Inherits from IUnknown

    HRESULT (*SetPrivateData)(void *This, const GUID *Name, UINT DataSize, const void *pData);
    HRESULT (*SetPrivateDataInterface)(void *This, const GUID *Name, const void *pUnknown);
    HRESULT (*GetPrivateData)(void *This, const GUID *Name, UINT *pDataSize, void *pData);
    HRESULT (*GetParent)(void *This, const GUID *riid, void **ppParent);

    HRESULT (*GetDesc)(void *This, DXGI_OUTPUT_DESC *pDesc);
    HRESULT (*GetDisplayModeList)(void *This, DXGI_FORMAT EnumFormat, UINT Flags, UINT *pNumModes, DXGI_MODE_DESC *pDesc);
    HRESULT (*FindClosestMatchingMode)(void *This, const DXGI_MODE_DESC *pModeToMatch, DXGI_MODE_DESC *pClosestMatch, void *pConcernedDevice);
    HRESULT (*WaitForVBlank)(void *This);
    HRESULT (*TakeOwnership)(void *This, void *pDevice, BOOL Exclusive);
    void (*ReleaseOwnership)(void *This);
    HRESULT (*GetGammaControlCapabilities)(void *This, DXGI_GAMMA_CONTROL_CAPABILITIES *pGammaCaps);
    HRESULT (*SetGammaControl)(void *This, const DXGI_GAMMA_CONTROL *pArray);
    HRESULT (*GetGammaControl)(void *This, DXGI_GAMMA_CONTROL *pArray);
    HRESULT (*SetDisplaySurface)(void *This, void *pScanoutSurface);
    HRESULT (*GetDisplaySurfaceData)(void *This, void *pDestination);
    HRESULT (*GetFrameStatistics)(void *This, DXGI_FRAME_STATISTICS *pStats);
} IDXGIOutputVtbl;

typedef struct IDXGIOutput {
    const IDXGIOutputVtbl *lpVtbl;
} IDXGIOutput;

typedef struct IDXGIAdapterVtbl {
    IUnknownVtbl parent; // Inherits from IUnknown

    HRESULT (*SetPrivateData)(void *This, const GUID *Name, UINT DataSize, const void *pData);
    HRESULT (*SetPrivateDataInterface)(void *This, const GUID *Name, const void *pUnknown);
    HRESULT (*GetPrivateData)(void *This, const GUID *Name, UINT *pDataSize, void *pData);
    HRESULT (*GetParent)(void *This, const GUID *riid, void **ppParent);

    HRESULT (*EnumOutputs)(void *This, UINT Output, IDXGIOutput **ppOutput);
    HRESULT (*GetDesc)(void *This, DXGI_ADAPTER_DESC *pDesc);
    HRESULT (*CheckInterfaceSupport)(void *This, const GUID *InterfaceName, LARGE_INTEGER *pUMDVersion);
} IDXGIAdapterVtbl;

typedef struct IDXGIAdapter {
    const IDXGIAdapterVtbl *lpVtbl;
} IDXGIAdapter;

struct IDXGISwapChain;
typedef struct IDXGIFactoryVtbl {
    IUnknownVtbl parent; // Inherits from IUnknown

    HRESULT (*SetPrivateData)(void *This, const GUID *Name, UINT DataSize, const void *pData);
    HRESULT (*SetPrivateDataInterface)(void *This, const GUID *Name, const void *pUnknown);
    HRESULT (*GetPrivateData)(void *This, const GUID *Name, UINT *pDataSize, void *pData);
    HRESULT (*GetParent)(void *This, const GUID *riid, void **ppParent);

    HRESULT (*EnumAdapters)(void *This, UINT Adapter, IDXGIAdapter **ppAdapter);
    HRESULT (*MakeWindowAssociation)(void *This, HWND WindowHandle, UINT Flags);
    HRESULT (*GetWindowAssociation)(void *This, HWND *pWindowHandle);
    HRESULT (*CreateSwapChain)(void *This, void *pDevice, const DXGI_SWAP_CHAIN_DESC *pDesc, struct IDXGISwapChain **ppSwapChain);
    HRESULT (*CreateSoftwareAdapter)(void *This, HMODULE Module, IDXGIAdapter **ppAdapter);
} IDXGIFactoryVtbl;

typedef struct IDXGIFactory {
    const IDXGIFactoryVtbl *lpVtbl;
} IDXGIFactory;

typedef GUID IID;
extern const IID IID_IDXGIFactory;
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    const GUID name = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }
DEFINE_GUID(IID_IDXGIFactory,0x7b7166ec,0x21c7,0x44ae,0xb2,0x1a,0xc9,0xae,0x32,0x1a,0xe3,0x69);
unit_local const HRESULT DXGI_ERROR_NOT_FOUND = 0x887A0002;


WINDOWS_IMPORT HRESULT WINAPI CreateDXGIFactory(const GUID *riid, void **ppFactory);







#define WSABASEERR 10000
#define WSAEINTR                         10004L
#define WSAEBADF                         10009L
#define WSAEACCES                        10013L
#define WSAEFAULT                        10014L
#define WSAEINVAL                        10022L
#define WSAEMFILE                        10024L
#define WSAEWOULDBLOCK                   10035L
#define WSAEINPROGRESS                   10036L
#define WSAEALREADY                      10037L
#define WSAENOTSOCK                      10038L
#define WSAEDESTADDRREQ                  10039L
#define WSAEMSGSIZE                      10040L
#define WSAEPROTOTYPE                    10041L
#define WSAENOPROTOOPT                   10042L
#define WSAEPROTONOSUPPORT               10043L
#define WSAESOCKTNOSUPPORT               10044L
#define WSAEOPNOTSUPP                    10045L
#define WSAEPFNOSUPPORT                  10046L
#define WSAEAFNOSUPPORT                  10047L
#define WSAEADDRINUSE                    10048L
#define WSAEADDRNOTAVAIL                 10049L
#define WSAENETDOWN                      10050L
#define WSAENETUNREACH                   10051L
#define WSAENETRESET                     10052L
#define WSAECONNABORTED                  10053L
#define WSAECONNRESET                    10054L
#define WSAENOBUFS                       10055L
#define WSAEISCONN                       10056L
#define WSAENOTCONN                      10057L
#define WSAESHUTDOWN                     10058L
#define WSAETOOMANYREFS                  10059L
#define WSAETIMEDOUT                     10060L
#define WSAECONNREFUSED                  10061L
#define WSAELOOP                         10062L
#define WSAENAMETOOLONG                  10063L
#define WSAEHOSTDOWN                     10064L
#define WSAEHOSTUNREACH                  10065L
#define WSAENOTEMPTY                     10066L
#define WSAEPROCLIM                      10067L
#define WSAEUSERS                        10068L
#define WSAEDQUOT                        10069L
#define WSAESTALE                        10070L
#define WSAEREMOTE                       10071L
#define WSASYSNOTREADY                   10091L
#define WSAVERNOTSUPPORTED               10092L
#define WSANOTINITIALISED                10093L
#define WSAEDISCON                       10101L
#define WSAENOMORE                       10102L
#define WSAECANCELLED                    10103L
#define WSAEINVALIDPROCTABLE             10104L
#define WSAEINVALIDPROVIDER              10105L
#define WSAEPROVIDERFAILEDINIT           10106L
#define WSASYSCALLFAILURE                10107L
#define WSASERVICE_NOT_FOUND             10108L
#define WSATYPE_NOT_FOUND                10109L
#define WSA_E_NO_MORE                    10110L
#define WSA_E_CANCELLED                  10111L
#define WSAEREFUSED                      10112L
#define WSAHOST_NOT_FOUND                11001L
#define WSATRY_AGAIN                     11002L
#define WSANO_RECOVERY                   11003L
#define WSANO_DATA                       11004L
#define WSA_QOS_RECEIVERS                11005L
#define WSA_QOS_SENDERS                  11006L
#define WSA_QOS_NO_SENDERS               11007L
#define WSA_QOS_NO_RECEIVERS             11008L
#define WSA_QOS_REQUEST_CONFIRMED        11009L
#define WSA_QOS_ADMISSION_FAILURE        11010L
#define WSA_QOS_POLICY_FAILURE           11011L
#define WSA_QOS_BAD_STYLE                11012L
#define WSA_QOS_BAD_OBJECT               11013L
#define WSA_QOS_TRAFFIC_CTRL_ERROR       11014L
#define WSA_QOS_GENERIC_ERROR            11015L
#define WSA_QOS_ESERVICETYPE             11016L
#define WSA_QOS_EFLOWSPEC                11017L
#define WSA_QOS_EPROVSPECBUF             11018L
#define WSA_QOS_EFILTERSTYLE             11019L
#define WSA_QOS_EFILTERTYPE              11020L
#define WSA_QOS_EFILTERCOUNT             11021L
#define WSA_QOS_EOBJLENGTH               11022L
#define WSA_QOS_EFLOWCOUNT               11023L
#define WSA_QOS_EUNKOWNPSOBJ             11024L
#define WSA_QOS_EPOLICYOBJ               11025L
#define WSA_QOS_EFLOWDESC                11026L
#define WSA_QOS_EPSFLOWSPEC              11027L
#define WSA_QOS_EPSFILTERSPEC            11028L
#define WSA_QOS_ESDMODEOBJ               11029L
#define WSA_QOS_ESHAPERATEOBJ            11030L
#define WSA_QOS_RESERVED_PETYPE          11031L
#define WSA_SECURE_HOST_NOT_FOUND        11032L
#define WSA_IPSEC_NAME_POLICY_ERROR      11033L

#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128

typedef UINT_PTR        SOCKET;

typedef struct WSAData {
        WORD                    wVersion;
        WORD                    wHighVersion;
#ifdef _WIN64
        unsigned short          iMaxSockets;
        unsigned short          iMaxUdpDg;
        char *              lpVendorInfo;
        char                    szDescription[WSADESCRIPTION_LEN+1];
        char                    szSystemStatus[WSASYS_STATUS_LEN+1];
#else
        char                    szDescription[WSADESCRIPTION_LEN+1];
        char                    szSystemStatus[WSASYS_STATUS_LEN+1];
        unsigned short          iMaxSockets;
        unsigned short          iMaxUdpDg;
        char *              lpVendorInfo;
#endif
} WSADATA;

typedef WSADATA *LPWSADATA;

WINDOWS_IMPORT int WINAPI WSAStartup( WORD      wVersionRequired, LPWSADATA lpWSAData);

/*
 * Address families.
 */
#define AF_UNSPEC       0               /* unspecified */
#define AF_UNIX         1               /* local to host (pipes, portals) */
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#define AF_IMPLINK      3               /* arpanet imp addresses */
#define AF_PUP          4               /* pup protocols: e.g. BSP */
#define AF_CHAOS        5               /* mit CHAOS protocols */
#define AF_IPX          6               /* IPX and SPX */
#define AF_NS           6               /* XEROX NS protocols */
#define AF_ISO          7               /* ISO protocols */
#define AF_OSI          AF_ISO          /* OSI is ISO */
#define AF_ECMA         8               /* european computer manufacturers */
#define AF_DATAKIT      9               /* datakit protocols */
#define AF_CCITT        10              /* CCITT protocols, X.25 etc */
#define AF_SNA          11              /* IBM SNA */
#define AF_DECnet       12              /* DECnet */
#define AF_DLI          13              /* Direct data link interface */
#define AF_LAT          14              /* LAT */
#define AF_HYLINK       15              /* NSC Hyperchannel */
#define AF_APPLETALK    16              /* AppleTalk */
#define AF_NETBIOS      17              /* NetBios-style addresses */
#define AF_VOICEVIEW    18              /* VoiceView */
#define AF_FIREFOX      19              /* FireFox */
#define AF_UNKNOWN1     20              /* Somebody is using this! */
#define AF_BAN          21              /* Banyan */

#define AF_MAX          22

/*
 * Types
 */
#define SOCK_STREAM     1               /* stream socket */
#define SOCK_DGRAM      2               /* datagram socket */
#define SOCK_RAW        3               /* raw-protocol interface */
#define SOCK_RDM        4               /* reliably-delivered message */
#define SOCK_SEQPACKET  5               /* sequenced packet stream */


#define IPPROTO_IP              0               /* dummy for IP */
#define IPPROTO_ICMP            1               /* control message protocol */
#define IPPROTO_IGMP            2               /* group management protocol */
#define IPPROTO_GGP             3               /* gateway^2 (deprecated) */
#define IPPROTO_TCP             6               /* tcp */
#define IPPROTO_PUP             12              /* pup */
#define IPPROTO_UDP             17              /* user datagram protocol */
#define IPPROTO_IDP             22              /* xns idp */
#define IPPROTO_ND              77              /* UNOFFICIAL net disk proto */

#define IPPROTO_RAW             255             /* raw IP packet */
#define IPPROTO_MAX             256





           
typedef struct in_addr {
        union {
                struct { UCHAR s_b1,s_b2,s_b3,s_b4; } S_un_b;
                struct { USHORT s_w1,s_w2; } S_un_w;
                ULONG S_addr;
        } S_un;
#define s_addr  S_un.S_addr /* can be used for most tcp & ip code */
#define s_host  S_un.S_un_b.s_b2    // host on imp
#define s_net   S_un.S_un_b.s_b1    // network
#define s_imp   S_un.S_un_w.s_w2    // imp
#define s_impno S_un.S_un_b.s_b4    // imp #
#define s_lh    S_un.S_un_b.s_b3    // logical host
} IN_ADDR, *PIN_ADDR,  *LPIN_ADDR;

    
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)
    
  typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in *PSOCKADDR_IN;
typedef struct sockaddr_in *LPSOCKADDR_IN;

typedef USHORT ADDRESS_FAMILY;

typedef struct sockaddr_in {

#if(_WIN32_WINNT < 0x0600)
    short   sin_family;
#else //(_WIN32_WINNT < 0x0600)
    ADDRESS_FAMILY sin_family;
#endif //(_WIN32_WINNT < 0x0600)

    USHORT sin_port;
    IN_ADDR sin_addr;
    CHAR sin_zero[8];
} SOCKADDR_IN, *PSOCKADDR_IN;

struct sockaddr {
        USHORT sa_family;              /* address family */
        char    sa_data[14];            /* up to 14 bytes of direct address */
};


WINDOWS_IMPORT
SOCKET
WINAPI
socket(
    int af,
    int type,
    int protocol
    );
    
WINDOWS_IMPORT
USHORT
WINAPI
htons(
    USHORT hostshort
    );
WINDOWS_IMPORT
USHORT
WINAPI
htonl(
   USHORT hostlong
    );
        
WINDOWS_IMPORT
int
WINAPI
bind(
     SOCKET s,
    const struct sockaddr * name,
     int namelen
    );
    
WINDOWS_IMPORT
int
WINAPI
WSAGetLastError(
    void
    );    

WINDOWS_IMPORT
int
WINAPI
listen(
     SOCKET s,
     int backlog
    );

WINDOWS_IMPORT
SOCKET
WINAPI
accept(
    SOCKET s,
    struct sockaddr * addr,
    int * addrlen
    );
    

WINDOWS_IMPORT
unsigned long
WINAPI
inet_addr(
     const char * cp
    );
    
#define INADDR_NONE             0xffffffff


WINDOWS_IMPORT
int
WINAPI
connect(
    SOCKET s,
    const struct sockaddr * name,
    int namelen
    );


WINDOWS_IMPORT
int
WINAPI
send(
    SOCKET s,
    const char * buf,
    int len,
    int flags
    );
    
WINDOWS_IMPORT
int
WINAPI
recv(
    SOCKET s,
    char * buf,
    int len,
    int flags
    );



WINDOWS_IMPORT
int
WINAPI
closesocket(
    SOCKET s
    );

WINDOWS_IMPORT
int
WINAPI
ioctlsocket(
     SOCKET s,
     long cmd,
    unsigned long * argp
    );
    

#define IOCPARM_MASK    0x7f            /* parameters must be < 128 bytes */
#define IOC_VOID        0x20000000      /* no parameters */
#define IOC_OUT         0x40000000      /* copy out parameters */
#define IOC_IN          0x80000000      /* copy in parameters */
#define IOC_INOUT       (IOC_IN|IOC_OUT)
#define _IO(x,y)        (IOC_VOID|((x)<<8)|(y))

#define _IOR(x,y,t)     (IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define _IOW(x,y,t)     (IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))
#define FIONREAD    _IOR('f', 127, unsigned long) /* get # bytes to read */
#define FIONBIO     _IOW('f', 126, unsigned long) /* set/clear non-blocking i/o */
#define FIOASYNC    _IOW('f', 125, unsigned long) /* set/clear async i/o */

#define NO_ERROR 0L                                                 // dderror

int setsockopt (
                           SOCKET s,
                           int level,
                           int optname,
                           const char * optval,
                           int optlen);
                           
#define SOL_SOCKET      0xffff          /* options for socket level */

#define SO_SNDBUF       0x1001          /* send buffer size */
#define SO_RCVBUF       0x1002          /* receive buffer size */
#define SO_SNDLOWAT     0x1003          /* send low-water mark */
#define SO_RCVLOWAT     0x1004          /* receive low-water mark */
#define SO_SNDTIMEO     0x1005          /* send timeout */
#define SO_RCVTIMEO     0x1006          /* receive timeout */
#define SO_ERROR        0x1007          /* get error status and clear */
#define SO_TYPE         0x1008          /* get socket type */

#define FD_SETSIZE      64

#define FD_CLR(fd, set) do { \
    u_int __i; \
    for (__i = 0; __i < ((fd_set *)(set))->fd_count ; __i++) { \
        if (((fd_set *)(set))->fd_array[__i] == fd) { \
            while (__i < ((fd_set *)(set))->fd_count-1) { \
                ((fd_set *)(set))->fd_array[__i] = \
                    ((fd_set *)(set))->fd_array[__i+1]; \
                __i++; \
            } \
            ((fd_set *)(set))->fd_count--; \
            break; \
        } \
    } \
} while(0)

#define FD_SET(fd, set) do { \
    if (((fd_set *)(set))->fd_count < FD_SETSIZE) \
        ((fd_set *)(set))->fd_array[((fd_set *)(set))->fd_count++]=(fd);\
} while(0)

#define FD_ZERO(set) (((fd_set *)(set))->fd_count=0)

#define FD_ISSET(fd, set) __WSAFDIsSet((SOCKET)(fd), (fd_set *)(set))

/*
 * Structure used in select() call, taken from the BSD file sys/time.h.
 */
struct timeval {
        long    tv_sec;         /* seconds */
        long    tv_usec;        /* and microseconds */
};

/*
 * Operations on timevals.
 *
 * NB: timercmp does not work for >= or <=.
 */
#define timerisset(tvp)         ((tvp)->tv_sec || (tvp)->tv_usec)
#define timercmp(tvp, uvp, cmp) \
        ((tvp)->tv_sec cmp (uvp)->tv_sec || \
         (tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp (uvp)->tv_usec)
#define timerclear(tvp)         (tvp)->tv_sec = (tvp)->tv_usec = 0

typedef struct fd_set {
        unsigned int   fd_count;               /* how many are SET? */
        SOCKET  fd_array[FD_SETSIZE];   /* an array of SOCKETs */
} fd_set;

WINDOWS_IMPORT
int
WINAPI
select(
    int nfds,
    fd_set * readfds,
    fd_set * writefds,
    fd_set * exceptfds,
    const struct timeval * timeout
    );
    
#endif // _WINDOWS_LOADER_H

typedef struct _FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

WINDOWS_IMPORT BOOL WINAPI FindClose(
  HANDLE hFindFile
);

typedef struct _WIN32_FIND_DATAW {
  DWORD    dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD    nFileSizeHigh;
  DWORD    nFileSizeLow;
  DWORD    dwReserved0;
  DWORD    dwReserved1;
  WCHAR    cFileName[260];
  WCHAR    cAlternateFileName[14];
  DWORD    dwFileType; // Obsolete. Do not use.
  DWORD    dwCreatorType; // Obsolete. Do not use
  WORD     wFinderFlags; // Obsolete. Do not use
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;

WINDOWS_IMPORT HANDLE WINAPI FindFirstFileW(
  LPCWSTR            lpFileName,
  LPWIN32_FIND_DATAW lpFindFileData
);

WINDOWS_IMPORT BOOL WINAPI FindNextFileW(
  HANDLE             hFindFile,
  LPWIN32_FIND_DATAW lpFindFileData
);

WINDOWS_IMPORT DWORD WINAPI GetFileAttributesW(
  LPCWSTR lpFileName
);

WINDOWS_IMPORT BOOL WINAPI RemoveDirectoryW(
  LPCWSTR lpPathName
);

WINDOWS_IMPORT BOOL WINAPI DeleteFileW(
  LPCWSTR lpFileName
);

// end_access
#define FILE_SHARE_READ                 0x00000001  
#define FILE_SHARE_WRITE                0x00000002  
#define FILE_SHARE_DELETE               0x00000004  
#define FILE_ATTRIBUTE_READONLY             0x00000001  
#define FILE_ATTRIBUTE_HIDDEN               0x00000002  
#define FILE_ATTRIBUTE_SYSTEM               0x00000004  
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020  
#define FILE_ATTRIBUTE_DEVICE               0x00000040  
#define FILE_ATTRIBUTE_NORMAL               0x00000080  
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100  
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200  
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400  
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800  
#define FILE_ATTRIBUTE_OFFLINE              0x00001000  
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000  
#define FILE_ATTRIBUTE_ENCRYPTED            0x00004000  
#define FILE_ATTRIBUTE_INTEGRITY_STREAM     0x00008000  
#define FILE_ATTRIBUTE_VIRTUAL              0x00010000  
#define FILE_ATTRIBUTE_NO_SCRUB_DATA        0x00020000  
#define FILE_ATTRIBUTE_EA                   0x00040000  
#define FILE_ATTRIBUTE_PINNED               0x00080000  
#define FILE_ATTRIBUTE_UNPINNED             0x00100000  
#define FILE_ATTRIBUTE_RECALL_ON_OPEN       0x00040000  
#define FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS 0x00400000 
#define TREE_CONNECT_ATTRIBUTE_PRIVACY      0x00004000  
#define TREE_CONNECT_ATTRIBUTE_INTEGRITY    0x00008000  
#define TREE_CONNECT_ATTRIBUTE_GLOBAL       0x00000004  
#define TREE_CONNECT_ATTRIBUTE_PINNED       0x00000002  
#define FILE_ATTRIBUTE_STRICTLY_SEQUENTIAL  0x20000000  
#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001   
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002   
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004   
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008   
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010   
#define FILE_NOTIFY_CHANGE_LAST_ACCESS  0x00000020   
#define FILE_NOTIFY_CHANGE_CREATION     0x00000040   
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100   
#define FILE_ACTION_ADDED                   0x00000001   
#define FILE_ACTION_REMOVED                 0x00000002   
#define FILE_ACTION_MODIFIED                0x00000003   
#define FILE_ACTION_RENAMED_OLD_NAME        0x00000004   
#define FILE_ACTION_RENAMED_NEW_NAME        0x00000005   
#define MAILSLOT_NO_MESSAGE             ((DWORD)-1) 
#define MAILSLOT_WAIT_FOREVER           ((DWORD)-1) 
#define FILE_CASE_SENSITIVE_SEARCH          0x00000001  
#define FILE_CASE_PRESERVED_NAMES           0x00000002  
#define FILE_UNICODE_ON_DISK                0x00000004  
#define FILE_PERSISTENT_ACLS                0x00000008  
#define FILE_FILE_COMPRESSION               0x00000010  
#define FILE_VOLUME_QUOTAS                  0x00000020  
#define FILE_SUPPORTS_SPARSE_FILES          0x00000040  
#define FILE_SUPPORTS_REPARSE_POINTS        0x00000080  
#define FILE_SUPPORTS_REMOTE_STORAGE        0x00000100  
#define FILE_RETURNS_CLEANUP_RESULT_INFO    0x00000200  
#define FILE_SUPPORTS_POSIX_UNLINK_RENAME   0x00000400  




#define FILE_VOLUME_IS_COMPRESSED           0x00008000  
#define FILE_SUPPORTS_OBJECT_IDS            0x00010000  
#define FILE_SUPPORTS_ENCRYPTION            0x00020000  
#define FILE_NAMED_STREAMS                  0x00040000  
#define FILE_READ_ONLY_VOLUME               0x00080000  
#define FILE_SEQUENTIAL_WRITE_ONCE          0x00100000  
#define FILE_SUPPORTS_TRANSACTIONS          0x00200000  
#define FILE_SUPPORTS_HARD_LINKS            0x00400000  
#define FILE_SUPPORTS_EXTENDED_ATTRIBUTES   0x00800000  
#define FILE_SUPPORTS_OPEN_BY_FILE_ID       0x01000000  
#define FILE_SUPPORTS_USN_JOURNAL           0x02000000  
#define FILE_SUPPORTS_INTEGRITY_STREAMS     0x04000000  
#define FILE_SUPPORTS_BLOCK_REFCOUNTING     0x08000000  
#define FILE_SUPPORTS_SPARSE_VDL            0x10000000  
#define FILE_DAX_VOLUME                     0x20000000  
#define FILE_SUPPORTS_GHOSTING              0x40000000  


WINDOWS_IMPORT DWORD WINAPI TlsAlloc(void);
WINDOWS_IMPORT LPVOID WINAPI TlsGetValue(
  DWORD dwTlsIndex
);
WINDOWS_IMPORT BOOL WINAPI TlsSetValue(
  DWORD  dwTlsIndex,
  LPVOID lpTlsValue
);

WINDOWS_IMPORT DWORD WINAPI GetCurrentThreadId(void);

typedef DWORD (__stdcall *LPTHREAD_START_ROUTINE) (LPVOID lpThreadParameter);  

WINDOWS_IMPORT HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, size_t dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);

WINDOWS_IMPORT DWORD WINAPI ResumeThread(HANDLE hThread);

typedef struct CRITICAL_SECTION {
  u8 _[40]; // todo(charlie) #portability 32-bit
} CRITICAL_SECTION, *LPCRITICAL_SECTION, *PCRITICAL_SECTION;

WINDOWS_IMPORT void WINAPI InitializeCriticalSection(
  LPCRITICAL_SECTION lpCriticalSection
);

WINDOWS_IMPORT void WINAPI EnterCriticalSection(
  LPCRITICAL_SECTION lpCriticalSection
);

WINDOWS_IMPORT void WINAPI LeaveCriticalSection(
  LPCRITICAL_SECTION lpCriticalSection
);

WINDOWS_IMPORT void WINAPI DeleteCriticalSection(
  LPCRITICAL_SECTION lpCriticalSection
);

WINDOWS_IMPORT BOOL WINAPI CreateDirectoryW(
  LPCWSTR               lpPathName,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes
);


#define SO_DEBUG        0x0001          /* turn on debugging info recording */
#define SO_ACCEPTCONN   0x0002          /* socket has had listen() */
#define SO_REUSEADDR    0x0004          /* allow local address reuse */
#define SO_KEEPALIVE    0x0008          /* keep connections alive */
#define SO_DONTROUTE    0x0010          /* just use interface addresses */
#define SO_BROADCAST    0x0020          /* permit sending of broadcast msgs */
#define SO_USELOOPBACK  0x0040          /* bypass hardware when possible */
#define SO_LINGER       0x0080          /* linger on close if data present */
#define SO_OOBINLINE    0x0100          /* leave received OOB data in line */

WINDOWS_IMPORT void WINAPI ExitProcess(UINT uExitCode);

WINDOWS_IMPORT void WINAPI ExitThread(DWORD dwExitCode);

WINDOWS_IMPORT BOOL WINAPI GetExitCodeThread(HANDLE hThread, LPDWORD lpExitCode);

WINDOWS_IMPORT DWORD WINAPI GetFullPathNameA( LPCSTR lpFileName, DWORD  nBufferLength, LPSTR  lpBuffer, LPSTR  *lpFilePart);

WINDOWS_IMPORT LPWSTR  WINAPI GetCommandLineW(void);
WINDOWS_IMPORT LPCSTR  WINAPI GetCommandLineA(void);
WINDOWS_IMPORT LPWSTR* WINAPI CommandLineToArgvW(LPCWSTR, int*);

WINDOWS_IMPORT HANDLE WINAPI CreateSemaphoreA( LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCSTR lpName);

WINDOWS_IMPORT BOOL WINAPI ReleaseSemaphore( HANDLE hSemaphore, LONG   lReleaseCount, LPLONG lpPreviousCount);

typedef struct {
  LARGE_INTEGER VolumeSerialNumber;
  LARGE_INTEGER NumberSectors;
  LARGE_INTEGER TotalClusters;
  LARGE_INTEGER FreeClusters;
  LARGE_INTEGER TotalReserved;
  ULONG         BytesPerSector;
  ULONG         BytesPerCluster;
  ULONG         BytesPerFileRecordSegment;
  ULONG         ClustersPerFileRecordSegment;
  LARGE_INTEGER MftValidDataLength;
  LARGE_INTEGER MftStartLcn;
  LARGE_INTEGER Mft2StartLcn;
  LARGE_INTEGER MftZoneStart;
  LARGE_INTEGER MftZoneEnd;
} NTFS_VOLUME_DATA_BUFFER, *PNTFS_VOLUME_DATA_BUFFER;

WINDOWS_IMPORT BOOL WINAPI DeviceIoControl( HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);

typedef struct {
  DWORDLONG StartFileReferenceNumber;
  USN       LowUsn;
  USN       HighUsn;
} MFT_ENUM_DATA_V0, *PMFT_ENUM_DATA_V0;

#define DEVICE_TYPE DWORD

#define FILE_DEVICE_BEEP                0x00000001
#define FILE_DEVICE_CD_ROM              0x00000002
#define FILE_DEVICE_CD_ROM_FILE_SYSTEM  0x00000003
#define FILE_DEVICE_CONTROLLER          0x00000004
#define FILE_DEVICE_DATALINK            0x00000005
#define FILE_DEVICE_DFS                 0x00000006
#define FILE_DEVICE_DISK                0x00000007
#define FILE_DEVICE_DISK_FILE_SYSTEM    0x00000008
#define FILE_DEVICE_FILE_SYSTEM         0x00000009
#define FILE_DEVICE_INPORT_PORT         0x0000000a
#define FILE_DEVICE_KEYBOARD            0x0000000b
#define FILE_DEVICE_MAILSLOT            0x0000000c
#define FILE_DEVICE_MIDI_IN             0x0000000d
#define FILE_DEVICE_MIDI_OUT            0x0000000e
#define FILE_DEVICE_MOUSE               0x0000000f
#define FILE_DEVICE_MULTI_UNC_PROVIDER  0x00000010
#define FILE_DEVICE_NAMED_PIPE          0x00000011
#define FILE_DEVICE_NETWORK             0x00000012
#define FILE_DEVICE_NETWORK_BROWSER     0x00000013
#define FILE_DEVICE_NETWORK_FILE_SYSTEM 0x00000014
#define FILE_DEVICE_NULL                0x00000015
#define FILE_DEVICE_PARALLEL_PORT       0x00000016
#define FILE_DEVICE_PHYSICAL_NETCARD    0x00000017
#define FILE_DEVICE_PRINTER             0x00000018
#define FILE_DEVICE_SCANNER             0x00000019
#define FILE_DEVICE_SERIAL_MOUSE_PORT   0x0000001a
#define FILE_DEVICE_SERIAL_PORT         0x0000001b
#define FILE_DEVICE_SCREEN              0x0000001c
#define FILE_DEVICE_SOUND               0x0000001d
#define FILE_DEVICE_STREAMS             0x0000001e
#define FILE_DEVICE_TAPE                0x0000001f
#define FILE_DEVICE_TAPE_FILE_SYSTEM    0x00000020
#define FILE_DEVICE_TRANSPORT           0x00000021
#define FILE_DEVICE_UNKNOWN             0x00000022
#define FILE_DEVICE_VIDEO               0x00000023
#define FILE_DEVICE_VIRTUAL_DISK        0x00000024
#define FILE_DEVICE_WAVE_IN             0x00000025
#define FILE_DEVICE_WAVE_OUT            0x00000026
#define FILE_DEVICE_8042_PORT           0x00000027
#define FILE_DEVICE_NETWORK_REDIRECTOR  0x00000028
#define FILE_DEVICE_BATTERY             0x00000029
#define FILE_DEVICE_BUS_EXTENDER        0x0000002a
#define FILE_DEVICE_MODEM               0x0000002b
#define FILE_DEVICE_VDM                 0x0000002c
#define FILE_DEVICE_MASS_STORAGE        0x0000002d
#define FILE_DEVICE_SMB                 0x0000002e
#define FILE_DEVICE_KS                  0x0000002f
#define FILE_DEVICE_CHANGER             0x00000030
#define FILE_DEVICE_SMARTCARD           0x00000031
#define FILE_DEVICE_ACPI                0x00000032
#define FILE_DEVICE_DVD                 0x00000033
#define FILE_DEVICE_FULLSCREEN_VIDEO    0x00000034
#define FILE_DEVICE_DFS_FILE_SYSTEM     0x00000035
#define FILE_DEVICE_DFS_VOLUME          0x00000036
#define FILE_DEVICE_SERENUM             0x00000037
#define FILE_DEVICE_TERMSRV             0x00000038
#define FILE_DEVICE_KSEC                0x00000039
#define FILE_DEVICE_FIPS                0x0000003A
#define FILE_DEVICE_INFINIBAND          0x0000003B
#define FILE_DEVICE_VMBUS               0x0000003E
#define FILE_DEVICE_CRYPT_PROVIDER      0x0000003F
#define FILE_DEVICE_WPD                 0x00000040
#define FILE_DEVICE_BLUETOOTH           0x00000041
#define FILE_DEVICE_MT_COMPOSITE        0x00000042
#define FILE_DEVICE_MT_TRANSPORT        0x00000043
#define FILE_DEVICE_BIOMETRIC           0x00000044
#define FILE_DEVICE_PMI                 0x00000045
#define FILE_DEVICE_EHSTOR              0x00000046
#define FILE_DEVICE_DEVAPI              0x00000047
#define FILE_DEVICE_GPIO                0x00000048
#define FILE_DEVICE_USBEX               0x00000049
#define FILE_DEVICE_CONSOLE             0x00000050
#define FILE_DEVICE_NFP                 0x00000051
#define FILE_DEVICE_SYSENV              0x00000052
#define FILE_DEVICE_VIRTUAL_BLOCK       0x00000053
#define FILE_DEVICE_POINT_OF_SERVICE    0x00000054
#define FILE_DEVICE_STORAGE_REPLICATION 0x00000055
#define FILE_DEVICE_TRUST_ENV           0x00000056
#define FILE_DEVICE_UCM                 0x00000057
#define FILE_DEVICE_UCMTCPCI            0x00000058
#define FILE_DEVICE_PERSISTENT_MEMORY   0x00000059
#define FILE_DEVICE_NVDIMM              0x0000005a
#define FILE_DEVICE_HOLOGRAPHIC         0x0000005b
#define FILE_DEVICE_SDFXHCI             0x0000005c
#define FILE_DEVICE_UCMUCSI             0x0000005d

#define DEVICE_TYPE_FROM_CTL_CODE(ctrlCode)     (((DWORD)(ctrlCode & 0xffff0000)) >> 16)

//
// Macro to extract buffering method out of the device io control code
//
#define METHOD_FROM_CTL_CODE(ctrlCode)          ((DWORD)(ctrlCode & 3))

//
// Define the method codes for how buffers are passed for I/O and FS controls
//

#define METHOD_BUFFERED                 0
#define METHOD_IN_DIRECT                1
#define METHOD_OUT_DIRECT               2
#define METHOD_NEITHER                  3

//
// Define some easier to comprehend aliases:
//   METHOD_DIRECT_TO_HARDWARE (writes, aka METHOD_IN_DIRECT)
//   METHOD_DIRECT_FROM_HARDWARE (reads, aka METHOD_OUT_DIRECT)
//

#define METHOD_DIRECT_TO_HARDWARE       METHOD_IN_DIRECT
#define METHOD_DIRECT_FROM_HARDWARE     METHOD_OUT_DIRECT

#define FILE_ANY_ACCESS                 0
#define FILE_SPECIAL_ACCESS    (FILE_ANY_ACCESS)
#define FILE_READ_ACCESS          ( 0x0001 )    // file & pipe
#define FILE_WRITE_ACCESS         ( 0x0002 )    // file & pipe

//
// _WIN32_WINNT version constants
//
#define _WIN32_WINNT_NT4                    0x0400
#define _WIN32_WINNT_WIN2K                  0x0500
#define _WIN32_WINNT_WINXP                  0x0501
#define _WIN32_WINNT_WS03                   0x0502
#define _WIN32_WINNT_WIN6                   0x0600
#define _WIN32_WINNT_VISTA                  0x0600
#define _WIN32_WINNT_WS08                   0x0600
#define _WIN32_WINNT_LONGHORN               0x0600
#define _WIN32_WINNT_WIN7                   0x0601
#define _WIN32_WINNT_WIN8                   0x0602
#define _WIN32_WINNT_WINBLUE                0x0603
#define _WIN32_WINNT_WINTHRESHOLD           0x0A00 /* ABRACADABRA_THRESHOLD*/
#define _WIN32_WINNT_WIN10                  0x0A00 /* ABRACADABRA_THRESHOLD*/

//
// _WIN32_IE_ version constants
//
#define _WIN32_IE_IE20                      0x0200
#define _WIN32_IE_IE30                      0x0300
#define _WIN32_IE_IE302                     0x0302
#define _WIN32_IE_IE40                      0x0400
#define _WIN32_IE_IE401                     0x0401
#define _WIN32_IE_IE50                      0x0500
#define _WIN32_IE_IE501                     0x0501
#define _WIN32_IE_IE55                      0x0550
#define _WIN32_IE_IE60                      0x0600
#define _WIN32_IE_IE60SP1                   0x0601
#define _WIN32_IE_IE60SP2                   0x0603
#define _WIN32_IE_IE70                      0x0700
#define _WIN32_IE_IE80                      0x0800
#define _WIN32_IE_IE90                      0x0900
#define _WIN32_IE_IE100                     0x0A00
#define _WIN32_IE_IE110                     0x0A00  /* ABRACADABRA_THRESHOLD */

//
// IE <-> OS version mapping
//
// NT4 supports IE versions 2.0 -> 6.0 SP1
#define _WIN32_IE_NT4                       _WIN32_IE_IE20
#define _WIN32_IE_NT4SP1                    _WIN32_IE_IE20
#define _WIN32_IE_NT4SP2                    _WIN32_IE_IE20
#define _WIN32_IE_NT4SP3                    _WIN32_IE_IE302
#define _WIN32_IE_NT4SP4                    _WIN32_IE_IE401
#define _WIN32_IE_NT4SP5                    _WIN32_IE_IE401
#define _WIN32_IE_NT4SP6                    _WIN32_IE_IE50
// Win98 supports IE versions 4.01 -> 6.0 SP1
#define _WIN32_IE_WIN98                     _WIN32_IE_IE401
// Win98SE supports IE versions 5.0 -> 6.0 SP1
#define _WIN32_IE_WIN98SE                   _WIN32_IE_IE50
// WinME supports IE versions 5.5 -> 6.0 SP1
#define _WIN32_IE_WINME                     _WIN32_IE_IE55
// Win2k supports IE versions 5.01 -> 6.0 SP1
#define _WIN32_IE_WIN2K                     _WIN32_IE_IE501
#define _WIN32_IE_WIN2KSP1                  _WIN32_IE_IE501
#define _WIN32_IE_WIN2KSP2                  _WIN32_IE_IE501
#define _WIN32_IE_WIN2KSP3                  _WIN32_IE_IE501
#define _WIN32_IE_WIN2KSP4                  _WIN32_IE_IE501
#define _WIN32_IE_XP                        _WIN32_IE_IE60
#define _WIN32_IE_XPSP1                     _WIN32_IE_IE60SP1
#define _WIN32_IE_XPSP2                     _WIN32_IE_IE60SP2
#define _WIN32_IE_WS03                      0x0602
#define _WIN32_IE_WS03SP1                   _WIN32_IE_IE60SP2
#define _WIN32_IE_WIN6                      _WIN32_IE_IE70
#define _WIN32_IE_LONGHORN                  _WIN32_IE_IE70
#define _WIN32_IE_WIN7                      _WIN32_IE_IE80
#define _WIN32_IE_WIN8                      _WIN32_IE_IE100
#define _WIN32_IE_WINBLUE                   _WIN32_IE_IE100
#define _WIN32_IE_WINTHRESHOLD              _WIN32_IE_IE110  /* ABRACADABRA_THRESHOLD */
#define _WIN32_IE_WIN10                     _WIN32_IE_IE110  /* ABRACADABRA_THRESHOLD */


//
// NTDDI version constants
//
#define NTDDI_WIN2K                         0x05000000
#define NTDDI_WIN2KSP1                      0x05000100
#define NTDDI_WIN2KSP2                      0x05000200
#define NTDDI_WIN2KSP3                      0x05000300
#define NTDDI_WIN2KSP4                      0x05000400

#define NTDDI_WINXP                         0x05010000
#define NTDDI_WINXPSP1                      0x05010100
#define NTDDI_WINXPSP2                      0x05010200
#define NTDDI_WINXPSP3                      0x05010300
#define NTDDI_WINXPSP4                      0x05010400

#define NTDDI_WS03                          0x05020000
#define NTDDI_WS03SP1                       0x05020100
#define NTDDI_WS03SP2                       0x05020200
#define NTDDI_WS03SP3                       0x05020300
#define NTDDI_WS03SP4                       0x05020400

#define NTDDI_WIN6                          0x06000000
#define NTDDI_WIN6SP1                       0x06000100
#define NTDDI_WIN6SP2                       0x06000200
#define NTDDI_WIN6SP3                       0x06000300
#define NTDDI_WIN6SP4                       0x06000400

#define NTDDI_VISTA                         NTDDI_WIN6
#define NTDDI_VISTASP1                      NTDDI_WIN6SP1
#define NTDDI_VISTASP2                      NTDDI_WIN6SP2
#define NTDDI_VISTASP3                      NTDDI_WIN6SP3
#define NTDDI_VISTASP4                      NTDDI_WIN6SP4

#define NTDDI_LONGHORN  NTDDI_VISTA

#define NTDDI_WS08                          NTDDI_WIN6SP1
#define NTDDI_WS08SP2                       NTDDI_WIN6SP2
#define NTDDI_WS08SP3                       NTDDI_WIN6SP3
#define NTDDI_WS08SP4                       NTDDI_WIN6SP4

#define NTDDI_WIN7                          0x06010000
#define NTDDI_WIN8                          0x06020000
#define NTDDI_WINBLUE                       0x06030000
#define NTDDI_WINTHRESHOLD                  0x0A000000  /* ABRACADABRA_THRESHOLD */
#define NTDDI_WIN10                         0x0A000000  /* ABRACADABRA_THRESHOLD */
#define NTDDI_WIN10_TH2                     0x0A000001  /* ABRACADABRA_WIN10_TH2 */
#define NTDDI_WIN10_RS1                     0x0A000002  /* ABRACADABRA_WIN10_RS1 */
#define NTDDI_WIN10_RS2                     0x0A000003  /* ABRACADABRA_WIN10_RS2 */
#define NTDDI_WIN10_RS3                     0x0A000004  /* ABRACADABRA_WIN10_RS3 */
#define NTDDI_WIN10_RS4                     0x0A000005  /* ABRACADABRA_WIN10_RS4 */
#define NTDDI_WIN10_RS5                     0x0A000006  /* ABRACADABRA_WIN10_RS5 */
#define NTDDI_WIN10_19H1                    0x0A000007  /* ABRACADABRA_WIN10_19H1*/
#define NTDDI_WIN10_VB                      0x0A000008  /* ABRACADABRA_WIN10_VB */

#define WDK_NTDDI_VERSION                   NTDDI_WIN10_VB /* ABRACADABRA_WIN10_VB */


//
// masks for version macros
//
#define OSVERSION_MASK      0xFFFF0000
#define SPVERSION_MASK      0x0000FF00
#define SUBVERSION_MASK     0x000000FF


//
// macros to extract various version fields from the NTDDI version
//
#define OSVER(Version)  ((Version) & OSVERSION_MASK)
#define SPVER(Version)  (((Version) & SPVERSION_MASK) >> 8)
#define SUBVER(Version) (((Version) & SUBVERSION_MASK) )

#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
)
#define FSCTL_REQUEST_OPLOCK_LEVEL_1    CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  0, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_REQUEST_OPLOCK_LEVEL_2    CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_REQUEST_BATCH_OPLOCK      CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  2, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_OPLOCK_BREAK_ACKNOWLEDGE  CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  3, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_OPBATCH_ACK_CLOSE_PENDING CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  4, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_OPLOCK_BREAK_NOTIFY       CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  5, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_LOCK_VOLUME               CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  6, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_UNLOCK_VOLUME             CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  7, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_DISMOUNT_VOLUME           CTL_CODE(FILE_DEVICE_FILE_SYSTEM,  8, METHOD_BUFFERED, FILE_ANY_ACCESS)
// decommissioned fsctl value                                              9
#define FSCTL_IS_VOLUME_MOUNTED         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 10, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_IS_PATHNAME_VALID         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 11, METHOD_BUFFERED, FILE_ANY_ACCESS) // PATHNAME_BUFFER,
#define FSCTL_MARK_VOLUME_DIRTY         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 12, METHOD_BUFFERED, FILE_ANY_ACCESS)
// decommissioned fsctl value                                             13
#define FSCTL_QUERY_RETRIEVAL_POINTERS  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 14,  METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_GET_COMPRESSION           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 15, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SET_COMPRESSION           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 16, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA)
// decommissioned fsctl value                                             17
// decommissioned fsctl value                                             18
#define FSCTL_SET_BOOTLOADER_ACCESSED   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 19,  METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_MARK_AS_SYSTEM_HIVE       FSCTL_SET_BOOTLOADER_ACCESSED
#define FSCTL_OPLOCK_BREAK_ACK_NO_2     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 20, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_INVALIDATE_VOLUMES        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 21, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_QUERY_FAT_BPB             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 22, METHOD_BUFFERED, FILE_ANY_ACCESS) // FSCTL_QUERY_FAT_BPB_BUFFER
#define FSCTL_REQUEST_FILTER_OPLOCK     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 23, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_FILESYSTEM_GET_STATISTICS CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 24, METHOD_BUFFERED, FILE_ANY_ACCESS) // FILESYSTEM_STATISTICS

#if (_WIN32_WINNT >= _WIN32_WINNT_NT4)
#define FSCTL_GET_NTFS_VOLUME_DATA      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 25, METHOD_BUFFERED, FILE_ANY_ACCESS) // NTFS_VOLUME_DATA_BUFFER
#define FSCTL_GET_NTFS_FILE_RECORD      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 26, METHOD_BUFFERED, FILE_ANY_ACCESS) // NTFS_FILE_RECORD_INPUT_BUFFER, NTFS_FILE_RECORD_OUTPUT_BUFFER
#define FSCTL_GET_VOLUME_BITMAP         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 27,  METHOD_NEITHER, FILE_ANY_ACCESS) // STARTING_LCN_INPUT_BUFFER, VOLUME_BITMAP_BUFFER
#define FSCTL_GET_RETRIEVAL_POINTERS    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 28,  METHOD_NEITHER, FILE_ANY_ACCESS) // STARTING_VCN_INPUT_BUFFER, RETRIEVAL_POINTERS_BUFFER
#define FSCTL_MOVE_FILE                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 29, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // MOVE_FILE_DATA,
#define FSCTL_IS_VOLUME_DIRTY           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 30, METHOD_BUFFERED, FILE_ANY_ACCESS)
// decommissioned fsctl value                                             31
#define FSCTL_ALLOW_EXTENDED_DASD_IO    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 32, METHOD_NEITHER,  FILE_ANY_ACCESS)
#endif /* _WIN32_WINNT >= _WIN32_WINNT_NT4 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
// decommissioned fsctl value                                             33
// decommissioned fsctl value                                             34
#define FSCTL_FIND_FILES_BY_SID         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 35, METHOD_NEITHER, FILE_ANY_ACCESS)
// decommissioned fsctl value                                             36
// decommissioned fsctl value                                             37
#define FSCTL_SET_OBJECT_ID             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 38, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // FILE_OBJECTID_BUFFER
#define FSCTL_GET_OBJECT_ID             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 39, METHOD_BUFFERED, FILE_ANY_ACCESS) // FILE_OBJECTID_BUFFER
#define FSCTL_DELETE_OBJECT_ID          CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 40, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_SET_REPARSE_POINT         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 41, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // REPARSE_DATA_BUFFER,
#define FSCTL_GET_REPARSE_POINT         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 42, METHOD_BUFFERED, FILE_ANY_ACCESS) // REPARSE_DATA_BUFFER
#define FSCTL_DELETE_REPARSE_POINT      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 43, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // REPARSE_DATA_BUFFER,
#define FSCTL_ENUM_USN_DATA             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 44,  METHOD_NEITHER, FILE_ANY_ACCESS) // MFT_ENUM_DATA,
#define FSCTL_SECURITY_ID_CHECK         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 45,  METHOD_NEITHER, FILE_READ_DATA)  // BULK_SECURITY_TEST_DATA,
#define FSCTL_READ_USN_JOURNAL          CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 46,  METHOD_NEITHER, FILE_ANY_ACCESS) // READ_USN_JOURNAL_DATA, USN
#define FSCTL_SET_OBJECT_ID_EXTENDED    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 47, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_CREATE_OR_GET_OBJECT_ID   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 48, METHOD_BUFFERED, FILE_ANY_ACCESS) // FILE_OBJECTID_BUFFER
#define FSCTL_SET_SPARSE                CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 49, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_SET_ZERO_DATA             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 50, METHOD_BUFFERED, FILE_WRITE_DATA) // FILE_ZERO_DATA_INFORMATION,
#define FSCTL_QUERY_ALLOCATED_RANGES    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 51,  METHOD_NEITHER, FILE_READ_DATA)  // FILE_ALLOCATED_RANGE_BUFFER, FILE_ALLOCATED_RANGE_BUFFER
#define FSCTL_ENABLE_UPGRADE            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 52, METHOD_BUFFERED, FILE_WRITE_DATA)
#define FSCTL_SET_ENCRYPTION            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 53,  METHOD_NEITHER, FILE_ANY_ACCESS) // ENCRYPTION_BUFFER, DECRYPTION_STATUS_BUFFER
#define FSCTL_ENCRYPTION_FSCTL_IO       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 54,  METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_WRITE_RAW_ENCRYPTED       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 55,  METHOD_NEITHER, FILE_SPECIAL_ACCESS) // ENCRYPTED_DATA_INFO, EXTENDED_ENCRYPTED_DATA_INFO
#define FSCTL_READ_RAW_ENCRYPTED        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 56,  METHOD_NEITHER, FILE_SPECIAL_ACCESS) // REQUEST_RAW_ENCRYPTED_DATA, ENCRYPTED_DATA_INFO, EXTENDED_ENCRYPTED_DATA_INFO
#define FSCTL_CREATE_USN_JOURNAL        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 57,  METHOD_NEITHER, FILE_ANY_ACCESS) // CREATE_USN_JOURNAL_DATA,
#define FSCTL_READ_FILE_USN_DATA        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 58,  METHOD_NEITHER, FILE_ANY_ACCESS) // Read the Usn Record for a file
#define FSCTL_WRITE_USN_CLOSE_RECORD    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 59,  METHOD_NEITHER, FILE_ANY_ACCESS) // Generate Close Usn Record
#define FSCTL_EXTEND_VOLUME             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 60, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_QUERY_USN_JOURNAL         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 61, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_DELETE_USN_JOURNAL        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 62, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_MARK_HANDLE               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 63, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SIS_COPYFILE              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 64, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SIS_LINK_FILES            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 65, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA)
// decommissional fsctl value                                             66
// decommissioned fsctl value                                             67
// decommissioned fsctl value                                             68
#define FSCTL_RECALL_FILE               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 69, METHOD_NEITHER, FILE_ANY_ACCESS)
// decommissioned fsctl value                                             70
#define FSCTL_READ_FROM_PLEX            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 71, METHOD_OUT_DIRECT, FILE_READ_DATA)
#define FSCTL_FILE_PREFETCH             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 72, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // FILE_PREFETCH
#endif /* _WIN32_WINNT >= _WIN32_WINNT_WIN2K */

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
#define FSCTL_MAKE_MEDIA_COMPATIBLE         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 76, METHOD_BUFFERED, FILE_WRITE_DATA) // UDFS R/W
#define FSCTL_SET_DEFECT_MANAGEMENT         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 77, METHOD_BUFFERED, FILE_WRITE_DATA) // UDFS R/W
#define FSCTL_QUERY_SPARING_INFO            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 78, METHOD_BUFFERED, FILE_ANY_ACCESS) // UDFS R/W
#define FSCTL_QUERY_ON_DISK_VOLUME_INFO     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 79, METHOD_BUFFERED, FILE_ANY_ACCESS) // C/UDFS
#define FSCTL_SET_VOLUME_COMPRESSION_STATE  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 80, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // VOLUME_COMPRESSION_STATE
// decommissioned fsctl value                                                 80
#define FSCTL_TXFS_MODIFY_RM                CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 81, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_QUERY_RM_INFORMATION     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 82, METHOD_BUFFERED, FILE_READ_DATA)  // TxF
// decommissioned fsctl value                                                 83
#define FSCTL_TXFS_ROLLFORWARD_REDO         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 84, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_ROLLFORWARD_UNDO         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 85, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_START_RM                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 86, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_SHUTDOWN_RM              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 87, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_READ_BACKUP_INFORMATION  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 88, METHOD_BUFFERED, FILE_READ_DATA)  // TxF
#define FSCTL_TXFS_WRITE_BACKUP_INFORMATION CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 89, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_CREATE_SECONDARY_RM      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 90, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_GET_METADATA_INFO        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 91, METHOD_BUFFERED, FILE_READ_DATA)  // TxF
#define FSCTL_TXFS_GET_TRANSACTED_VERSION   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 92, METHOD_BUFFERED, FILE_READ_DATA)  // TxF
// decommissioned fsctl value                                                 93
#define FSCTL_TXFS_SAVEPOINT_INFORMATION    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 94, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
#define FSCTL_TXFS_CREATE_MINIVERSION       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 95, METHOD_BUFFERED, FILE_WRITE_DATA) // TxF
// decommissioned fsctl value                                                 96
// decommissioned fsctl value                                                 97
// decommissioned fsctl value                                                 98
#define FSCTL_TXFS_TRANSACTION_ACTIVE       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 99, METHOD_BUFFERED, FILE_READ_DATA)  // TxF
#define FSCTL_SET_ZERO_ON_DEALLOCATION      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 101, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_SET_REPAIR                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 102, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_GET_REPAIR                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 103, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_WAIT_FOR_REPAIR               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 104, METHOD_BUFFERED, FILE_ANY_ACCESS)
// decommissioned fsctl value                                                 105
#define FSCTL_INITIATE_REPAIR               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 106, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSC_INTERNAL                  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 107, METHOD_NEITHER, FILE_ANY_ACCESS) // CSC internal implementation
#define FSCTL_SHRINK_VOLUME                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 108, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // SHRINK_VOLUME_INFORMATION
#define FSCTL_SET_SHORT_NAME_BEHAVIOR       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 109, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_DFSR_SET_GHOST_HANDLE_STATE   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 110, METHOD_BUFFERED, FILE_ANY_ACCESS)

//
//  Values 111 - 119 are reserved for FSRM.
//

#define FSCTL_TXFS_LIST_TRANSACTION_LOCKED_FILES \
                                            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 120, METHOD_BUFFERED, FILE_READ_DATA) // TxF
#define FSCTL_TXFS_LIST_TRANSACTIONS        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 121, METHOD_BUFFERED, FILE_READ_DATA) // TxF
#define FSCTL_QUERY_PAGEFILE_ENCRYPTION     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 122, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* _WIN32_WINNT >= _WIN32_WINNT_VISTA */

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
#define FSCTL_RESET_VOLUME_ALLOCATION_HINTS CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 123, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* _WIN32_WINNT >= _WIN32_WINNT_VISTA */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_QUERY_DEPENDENT_VOLUME        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 124, METHOD_BUFFERED, FILE_ANY_ACCESS)    // Dependency File System Filter
#define FSCTL_SD_GLOBAL_CHANGE              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 125, METHOD_BUFFERED, FILE_ANY_ACCESS) // Query/Change NTFS Security Descriptors
#endif /* _WIN32_WINNT >= _WIN32_WINNT_WIN7 */

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
#define FSCTL_TXFS_READ_BACKUP_INFORMATION2 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 126, METHOD_BUFFERED, FILE_ANY_ACCESS) // TxF
#endif /* _WIN32_WINNT >= _WIN32_WINNT_VISTA */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_LOOKUP_STREAM_FROM_CLUSTER    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 127, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_TXFS_WRITE_BACKUP_INFORMATION2 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 128, METHOD_BUFFERED, FILE_ANY_ACCESS) // TxF
#define FSCTL_FILE_TYPE_NOTIFICATION        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 129, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
#define FSCTL_FILE_LEVEL_TRIM               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 130, METHOD_BUFFERED, FILE_WRITE_DATA)
#endif /*_WIN32_WINNT >= _WIN32_WINNT_WIN8 */

//
//  Values 131 - 139 are reserved for FSRM.
//

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_GET_BOOT_AREA_INFO            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 140, METHOD_BUFFERED, FILE_ANY_ACCESS) // BOOT_AREA_INFO
#define FSCTL_GET_RETRIEVAL_POINTER_BASE    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 141, METHOD_BUFFERED, FILE_ANY_ACCESS) // RETRIEVAL_POINTER_BASE
#define FSCTL_SET_PERSISTENT_VOLUME_STATE   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 142, METHOD_BUFFERED, FILE_ANY_ACCESS)  // FILE_FS_PERSISTENT_VOLUME_INFORMATION
#define FSCTL_QUERY_PERSISTENT_VOLUME_STATE CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 143, METHOD_BUFFERED, FILE_ANY_ACCESS)  // FILE_FS_PERSISTENT_VOLUME_INFORMATION

#define FSCTL_REQUEST_OPLOCK                CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 144, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define FSCTL_CSV_TUNNEL_REQUEST            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 145, METHOD_BUFFERED, FILE_ANY_ACCESS) // CSV_TUNNEL_REQUEST
#define FSCTL_IS_CSV_FILE                   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 146, METHOD_BUFFERED, FILE_ANY_ACCESS) // IS_CSV_FILE

#define FSCTL_QUERY_FILE_SYSTEM_RECOGNITION CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 147, METHOD_BUFFERED, FILE_ANY_ACCESS) //
#define FSCTL_CSV_GET_VOLUME_PATH_NAME      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 148, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_GET_VOLUME_NAME_FOR_VOLUME_MOUNT_POINT CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 149, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_GET_VOLUME_PATH_NAMES_FOR_VOLUME_NAME CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 150,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_IS_FILE_ON_CSV_VOLUME         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 151,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* _WIN32_WINNT >= _WIN32_WINNT_WIN7 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
#define FSCTL_CORRUPTION_HANDLING           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 152, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_OFFLOAD_READ                  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 153, METHOD_BUFFERED, FILE_READ_ACCESS)
#define FSCTL_OFFLOAD_WRITE                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 154, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#endif /*_WIN32_WINNT >= _WIN32_WINNT_WIN8 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_CSV_INTERNAL                  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 155,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* _WIN32_WINNT >= _WIN32_WINNT_WIN7 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
#define FSCTL_SET_PURGE_FAILURE_MODE        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 156, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_QUERY_FILE_LAYOUT             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 157, METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_IS_VOLUME_OWNED_BYCSVFS       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 158,  METHOD_BUFFERED, FILE_ANY_ACCESS)

#define FSCTL_GET_INTEGRITY_INFORMATION     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 159, METHOD_BUFFERED, FILE_ANY_ACCESS)                  // FSCTL_GET_INTEGRITY_INFORMATION_BUFFER
#define FSCTL_SET_INTEGRITY_INFORMATION     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 160, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA) // FSCTL_SET_INTEGRITY_INFORMATION_BUFFER

#define FSCTL_QUERY_FILE_REGIONS            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 161, METHOD_BUFFERED, FILE_ANY_ACCESS)

#endif /*_WIN32_WINNT >= _WIN32_WINNT_WIN8 */


#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
#define FSCTL_RKF_INTERNAL                  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 171, METHOD_NEITHER, FILE_ANY_ACCESS) // Resume Key Filter

#define FSCTL_SCRUB_DATA                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 172, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_REPAIR_COPIES                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 173, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA)
#define FSCTL_DISABLE_LOCAL_BUFFERING       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 174, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_MGMT_LOCK                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 175, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_QUERY_DOWN_LEVEL_FILE_SYSTEM_CHARACTERISTICS CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 176, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_ADVANCE_FILE_ID               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 177, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_SYNC_TUNNEL_REQUEST       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 178, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_QUERY_VETO_FILE_DIRECT_IO CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 179, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_WRITE_USN_REASON              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 180, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_CONTROL                   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 181, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_GET_REFS_VOLUME_DATA          CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 182, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_CSV_H_BREAKING_SYNC_TUNNEL_REQUEST CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 185, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /*_WIN32_WINNT >= _WIN32_WINNT_WIN8 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
#define FSCTL_QUERY_STORAGE_CLASSES         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 187, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_QUERY_REGION_INFO             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 188, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_USN_TRACK_MODIFIED_RANGES     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 189, METHOD_BUFFERED, FILE_ANY_ACCESS) // USN_TRACK_MODIFIED_RANGES
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
#define FSCTL_QUERY_SHARED_VIRTUAL_DISK_SUPPORT CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 192, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SVHDX_SYNC_TUNNEL_REQUEST         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 193, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SVHDX_SET_INITIATOR_INFORMATION   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 194, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_SET_EXTERNAL_BACKING              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 195, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_GET_EXTERNAL_BACKING              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 196, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_DELETE_EXTERNAL_BACKING           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 197, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_ENUM_EXTERNAL_BACKING             CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 198, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_ENUM_OVERLAY                      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 199, METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_ADD_OVERLAY                       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 204, METHOD_BUFFERED, FILE_WRITE_DATA)
#define FSCTL_REMOVE_OVERLAY                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 205, METHOD_BUFFERED, FILE_WRITE_DATA)
#define FSCTL_UPDATE_OVERLAY                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 206, METHOD_BUFFERED, FILE_WRITE_DATA)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN7) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
#define FSCTL_SHUFFLE_FILE                      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 208, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS) // SHUFFLE_FILE_DATA
#endif /*_WIN32_WINNT >= _WIN32_WINNT_WIN8 */
#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
#define FSCTL_DUPLICATE_EXTENTS_TO_FILE         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 209, METHOD_BUFFERED, FILE_WRITE_DATA )
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
#define FSCTL_SPARSE_OVERALLOCATE               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 211, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_STORAGE_QOS_CONTROL               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 212, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WINTHRESHOLD)
#define FSCTL_INITIATE_FILE_METADATA_OPTIMIZATION       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 215, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_QUERY_FILE_METADATA_OPTIMIZATION          CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 216, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINTHRESHOLD) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
#define FSCTL_SVHDX_ASYNC_TUNNEL_REQUEST         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 217, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_GET_WOF_VERSION                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 218, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WINTHRESHOLD)
#define FSCTL_HCS_SYNC_TUNNEL_REQUEST            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 219, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_HCS_ASYNC_TUNNEL_REQUEST           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 220, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_QUERY_EXTENT_READ_CACHE_INFO       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 221, METHOD_NEITHER, FILE_ANY_ACCESS)  // VCN_RANGE_INPUT_BUFFER, EXTENT_READ_CACHE_INFO_BUFFER
#define FSCTL_QUERY_REFS_VOLUME_COUNTER_INFO     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 222, METHOD_NEITHER, FILE_ANY_ACCESS)  // REFS_VOLUME_COUNTER_INFO_INPUT_BUFFER, VOLUME_REFS_INFO_BUFFER
#define FSCTL_CLEAN_VOLUME_METADATA              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 223, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SET_INTEGRITY_INFORMATION_EX       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 224, METHOD_BUFFERED, FILE_ANY_ACCESS) // FSCTL_SET_INTEGRITY_INFORMATION_BUFFER_EX
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINTHRESHOLD) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define FSCTL_SUSPEND_OVERLAY                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 225, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif
#if (_WIN32_WINNT >= _WIN32_WINNT_WINTHRESHOLD)
#define FSCTL_VIRTUAL_STORAGE_QUERY_PROPERTY     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 226, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_FILESYSTEM_GET_STATISTICS_EX       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 227, METHOD_BUFFERED, FILE_ANY_ACCESS) // FILESYSTEM_STATISTICS_EX
#define FSCTL_QUERY_VOLUME_CONTAINER_STATE       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 228, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SET_LAYER_ROOT                     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 229, METHOD_BUFFERED, FILE_ANY_ACCESS) // CONTAINER_ROOT_INFO_INPUT CONTAINER_ROOT_INFO_OUTPUT
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundef"
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_TH2)
#define FSCTL_QUERY_DIRECT_ACCESS_EXTENTS        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 230, METHOD_NEITHER, FILE_ANY_ACCESS)
#define FSCTL_NOTIFY_STORAGE_SPACE_ALLOCATION    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 231, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SSDI_STORAGE_REQUEST               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 232, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS1)
#define FSCTL_QUERY_DIRECT_IMAGE_ORIGINAL_BASE   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 233, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_READ_UNPRIVILEGED_USN_JOURNAL      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 234,  METHOD_NEITHER, FILE_ANY_ACCESS) // READ_USN_JOURNAL_DATA, USN
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_TH2)
#define FSCTL_GHOST_FILE_EXTENTS                 CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 235, METHOD_BUFFERED, FILE_WRITE_ACCESS) // FSCTL_GHOST_FILE_EXTENTS_INPUT_BUFFER
#define FSCTL_QUERY_GHOSTED_FILE_EXTENTS         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 236, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_TH2)
#define FSCTL_UNMAP_SPACE                        CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 237, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif
#if (_WIN32_WINNT >= _WIN32_WINNT_WINTHRESHOLD)
#define FSCTL_HCS_SYNC_NO_WRITE_TUNNEL_REQUEST   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 238, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS2)
#define FSCTL_STREAMS_QUERY_PARAMETERS          CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 241, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_STREAMS_ASSOCIATE_ID              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 242, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_STREAMS_QUERY_ID                  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 243, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define FSCTL_GET_RETRIEVAL_POINTERS_AND_REFCOUNT CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 244, METHOD_NEITHER,  FILE_ANY_ACCESS) // STARTING_VCN_INPUT_BUFFER, RETRIEVAL_POINTERS_AND_REFCOUNT_BUFFER

#define FSCTL_QUERY_VOLUME_NUMA_INFO            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 245, METHOD_BUFFERED, FILE_ANY_ACCESS)

#endif
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS2)

#define FSCTL_REFS_DEALLOCATE_RANGES            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 246, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_TH2)
#define FSCTL_QUERY_REFS_SMR_VOLUME_INFO         CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 247, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SET_REFS_SMR_VOLUME_GC_PARAMETERS  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 248, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SET_REFS_FILE_STRICTLY_SEQUENTIAL  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 249, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS3)
#define FSCTL_DUPLICATE_EXTENTS_TO_FILE_EX      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 250, METHOD_BUFFERED, FILE_WRITE_DATA)
#define FSCTL_QUERY_BAD_RANGES                  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 251, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SET_DAX_ALLOC_ALIGNMENT_HINT      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 252, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_DELETE_CORRUPTED_REFS_CONTAINER   CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 253, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_SCRUB_UNDISCOVERABLE_ID           CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 254, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS3) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS4)
#define FSCTL_NOTIFY_DATA_CHANGE                CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 255, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS4) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS1)
#define FSCTL_START_VIRTUALIZATION_INSTANCE_EX  CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 256, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS1) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS4)
#define FSCTL_ENCRYPTION_KEY_CONTROL            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 257, METHOD_BUFFERED, FILE_ANY_ACCESS)  // protect/unprotect under DPL
#define FSCTL_VIRTUAL_STORAGE_SET_BEHAVIOR      CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 258, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS4) */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS1)
#define FSCTL_SET_REPARSE_POINT_EX              CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 259, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) // REPARSE_DATA_BUFFER_EX
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS1) */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS5)
#define FSCTL_REARRANGE_FILE                    CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 264, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS) // REARRANGE_FILE_DATA
#define FSCTL_VIRTUAL_STORAGE_PASSTHROUGH       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 265, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_GET_RETRIEVAL_POINTER_COUNT       CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 266, METHOD_NEITHER,  FILE_ANY_ACCESS) // STARTING_VCN_INPUT_BUFFER, RETRIEVAL_POINTER_COUNT
#if defined(_WIN64)
#define FSCTL_ENABLE_PER_IO_FLAGS               CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 267, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif /* _WIN64 */
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS5) */
//
// AVIO IOCTLS.
//

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#define IOCTL_AVIO_ALLOCATE_STREAM      CTL_CODE(FILE_DEVICE_AVIO, 1, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_AVIO_FREE_STREAM          CTL_CODE(FILE_DEVICE_AVIO, 2, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_AVIO_MODIFY_STREAM        CTL_CODE(FILE_DEVICE_AVIO, 3, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef struct {

    DWORD RecordLength;
    WORD   MajorVersion;
    WORD   MinorVersion;
    DWORDLONG FileReferenceNumber;
    DWORDLONG ParentFileReferenceNumber;
    USN Usn;
    LARGE_INTEGER TimeStamp;
    DWORD Reason;
    DWORD SourceInfo;
    DWORD SecurityId;
    DWORD FileAttributes;
    WORD   FileNameLength;
    WORD   FileNameOffset;
    WCHAR FileName[1];

} USN_RECORD_V2, *PUSN_RECORD_V2;


//
//  These are the generic rights.
//

#define GENERIC_READ                     (0x80000000L)
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL                      (0x10000000L)
typedef HANDLE HKEY;

typedef struct _SHELLEXECUTEINFOA {
  DWORD     cbSize;
  ULONG     fMask;
  HWND      hwnd;
  LPCSTR    lpVerb;
  LPCSTR    lpFile;
  LPCSTR    lpParameters;
  LPCSTR    lpDirectory;
  int       nShow;
  HINSTANCE hInstApp;
  void      *lpIDList;
  LPCSTR    lpClass;
  HKEY      hkeyClass;
  DWORD     dwHotKey;
  union {
    HANDLE hIcon;
    HANDLE hMonitor;
  } DUMMYUNIONNAME;
  HANDLE    hProcess;
} SHELLEXECUTEINFOA, *LPSHELLEXECUTEINFOA;

WINDOWS_IMPORT BOOL WINAPI ShellExecuteExA(SHELLEXECUTEINFOA *pExecInfo);

WINDOWS_IMPORT BOOL WINAPI OpenProcessToken( HANDLE ProcessHandle, DWORD DesiredAccess, HANDLE* TokenHandle);

typedef enum _TOKEN_INFORMATION_CLASS {
  TokenUser = 1,
  TokenGroups,
  TokenPrivileges,
  TokenOwner,
  TokenPrimaryGroup,
  TokenDefaultDacl,
  TokenSource,
  TokenType,
  TokenImpersonationLevel,
  TokenStatistics,
  TokenRestrictedSids,
  TokenSessionId,
  TokenGroupsAndPrivileges,
  TokenSessionReference,
  TokenSandBoxInert,
  TokenAuditPolicy,
  TokenOrigin,
  TokenElevationType,
  TokenLinkedToken,
  TokenElevation,
  TokenHasRestrictions,
  TokenAccessInformation,
  TokenVirtualizationAllowed,
  TokenVirtualizationEnabled,
  TokenIntegrityLevel,
  TokenUIAccess,
  TokenMandatoryPolicy,
  TokenLogonSid,
  TokenIsAppContainer,
  TokenCapabilities,
  TokenAppContainerSid,
  TokenAppContainerNumber,
  TokenUserClaimAttributes,
  TokenDeviceClaimAttributes,
  TokenRestrictedUserClaimAttributes,
  TokenRestrictedDeviceClaimAttributes,
  TokenDeviceGroups,
  TokenRestrictedDeviceGroups,
  TokenSecurityAttributes,
  TokenIsRestricted,
  TokenProcessTrustLevel,
  TokenPrivateNameSpace,
  TokenSingletonAttributes,
  TokenBnoIsolation,
  TokenChildProcessFlags,
  TokenIsLessPrivilegedAppContainer,
  TokenIsSandboxed,
  TokenIsAppSilo,
  TokenLoggingInformation,
  TokenLearningMode,
  MaxTokenInfoClass
} TOKEN_INFORMATION_CLASS, *PTOKEN_INFORMATION_CLASS;

typedef struct _TOKEN_ELEVATION {
    DWORD TokenIsElevated;
} TOKEN_ELEVATION, *PTOKEN_ELEVATION;

#define TOKEN_ASSIGN_PRIMARY    (0x0001)
#define TOKEN_DUPLICATE         (0x0002)
#define TOKEN_IMPERSONATE       (0x0004)
#define TOKEN_QUERY             (0x0008)
#define TOKEN_QUERY_SOURCE      (0x0010)
#define TOKEN_ADJUST_PRIVILEGES (0x0020)
#define TOKEN_ADJUST_GROUPS     (0x0040)
#define TOKEN_ADJUST_DEFAULT    (0x0080)
#define TOKEN_ADJUST_SESSIONID  (0x0100)

#define TOKEN_ALL_ACCESS_P (STANDARD_RIGHTS_REQUIRED  |\
                          TOKEN_ASSIGN_PRIMARY      |\
                          TOKEN_DUPLICATE           |\
                          TOKEN_IMPERSONATE         |\
                          TOKEN_QUERY               |\
                          TOKEN_QUERY_SOURCE        |\
                          TOKEN_ADJUST_PRIVILEGES   |\
                          TOKEN_ADJUST_GROUPS       |\
                          TOKEN_ADJUST_DEFAULT )

#if ((defined(_WIN32_WINNT) && (_WIN32_WINNT > 0x0400)) || (!defined(_WIN32_WINNT)))
#define TOKEN_ALL_ACCESS  (TOKEN_ALL_ACCESS_P |\
                          TOKEN_ADJUST_SESSIONID )
#else
#define TOKEN_ALL_ACCESS  (TOKEN_ALL_ACCESS_P)
#endif

#define TOKEN_READ       (STANDARD_RIGHTS_READ      |\
                          TOKEN_QUERY)


#define TOKEN_WRITE      (STANDARD_RIGHTS_WRITE     |\
                          TOKEN_ADJUST_PRIVILEGES   |\
                          TOKEN_ADJUST_GROUPS       |\
                          TOKEN_ADJUST_DEFAULT)

#define TOKEN_EXECUTE    (STANDARD_RIGHTS_EXECUTE)

#define TOKEN_TRUST_CONSTRAINT_MASK    (STANDARD_RIGHTS_READ  | \
                                       TOKEN_QUERY  |\
                                       TOKEN_QUERY_SOURCE )

WINDOWS_IMPORT BOOL WINAPI GetTokenInformation( HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, LPVOID TokenInformation, DWORD TokenInformationLength, PDWORD ReturnLength);

#define SEE_MASK_DEFAULT           0x00000000
#define SEE_MASK_CLASSNAME         0x00000001   // SHELLEXECUTEINFO.lpClass is valid
#define SEE_MASK_CLASSKEY          0x00000003   // SHELLEXECUTEINFO.hkeyClass is valid
// Note SEE_MASK_INVOKEIDLIST(0xC) implies SEE_MASK_IDLIST(0x04)
#define SEE_MASK_IDLIST            0x00000004   // SHELLEXECUTEINFO.lpIDList is valid
#define SEE_MASK_INVOKEIDLIST      0x0000000c   // enable IContextMenu based verbs
#define SEE_MASK_HOTKEY            0x00000020   // SHELLEXECUTEINFO.dwHotKey is valid
#define SEE_MASK_NOCLOSEPROCESS    0x00000040   // SHELLEXECUTEINFO.hProcess
#define SEE_MASK_CONNECTNETDRV     0x00000080   // enables re-connecting disconnected network drives
#define SEE_MASK_NOASYNC           0x00000100   // block on the call until the invoke has completed, use for callers that exit after calling ShellExecuteEx()
#define SEE_MASK_FLAG_DDEWAIT      SEE_MASK_NOASYNC // Use SEE_MASK_NOASYNC instead of SEE_MASK_FLAG_DDEWAIT as it more accuratly describes the behavior
#define SEE_MASK_DOENVSUBST        0x00000200   // indicates that SHELLEXECUTEINFO.lpFile contains env vars that should be expanded
#define SEE_MASK_FLAG_NO_UI        0x00000400   // disable UI including error messages
#define SEE_MASK_UNICODE           0x00004000
#define SEE_MASK_NO_CONSOLE        0x00008000
#define SEE_MASK_ASYNCOK           0x00100000

#define FILE_FLAG_WRITE_THROUGH         0x80000000
#define FILE_FLAG_OVERLAPPED            0x40000000
#define FILE_FLAG_NO_BUFFERING          0x20000000
#define FILE_FLAG_RANDOM_ACCESS         0x10000000
#define FILE_FLAG_SEQUENTIAL_SCAN       0x08000000
#define FILE_FLAG_DELETE_ON_CLOSE       0x04000000
#define FILE_FLAG_BACKUP_SEMANTICS      0x02000000
#define FILE_FLAG_POSIX_SEMANTICS       0x01000000
#define FILE_FLAG_SESSION_AWARE         0x00800000
#define FILE_FLAG_OPEN_REPARSE_POINT    0x00200000
#define FILE_FLAG_OPEN_NO_RECALL        0x00100000
#define FILE_FLAG_FIRST_PIPE_INSTANCE   0x00080000

#define PAGE_NOACCESS           0x01    
#define PAGE_READONLY           0x02    
#define PAGE_READWRITE          0x04    
#define PAGE_WRITECOPY          0x08    
#define PAGE_EXECUTE            0x10    
#define PAGE_EXECUTE_READ       0x20    
#define PAGE_EXECUTE_READWRITE  0x40    
#define PAGE_EXECUTE_WRITECOPY  0x80    
#define PAGE_GUARD             0x100    
#define PAGE_NOCACHE           0x200    
#define PAGE_WRITECOMBINE      0x400    
#define PAGE_ENCLAVE_THREAD_CONTROL 0x80000000  
#define PAGE_REVERT_TO_FILE_MAP     0x80000000  
#define PAGE_TARGETS_NO_UPDATE      0x40000000  
#define PAGE_TARGETS_INVALID        0x40000000  
#define PAGE_ENCLAVE_UNVALIDATED    0x20000000  
#define PAGE_ENCLAVE_DECOMMIT       0x10000000  
#define MEM_COMMIT                      0x00001000  
#define MEM_RESERVE                     0x00002000  
#define MEM_REPLACE_PLACEHOLDER         0x00004000  
#define MEM_RESERVE_PLACEHOLDER         0x00040000  
#define MEM_RESET                       0x00080000  
#define MEM_TOP_DOWN                    0x00100000  
#define MEM_WRITE_WATCH                 0x00200000  
#define MEM_PHYSICAL                    0x00400000  
#define MEM_ROTATE                      0x00800000  
#define MEM_DIFFERENT_IMAGE_BASE_OK     0x00800000  
#define MEM_RESET_UNDO                  0x01000000  
#define MEM_LARGE_PAGES                 0x20000000  
#define MEM_4MB_PAGES                   0x80000000  
#define MEM_64K_PAGES                   (MEM_LARGE_PAGES | MEM_PHYSICAL)  
#define MEM_UNMAP_WITH_TRANSIENT_BOOST  0x00000001  
#define MEM_COALESCE_PLACEHOLDERS       0x00000001  
#define MEM_PRESERVE_PLACEHOLDER        0x00000002  
#define MEM_DECOMMIT                    0x00004000  
#define MEM_RELEASE                     0x00008000  
#define MEM_FREE                        0x00010000  

#define SECTION_QUERY                0x0001
#define SECTION_MAP_WRITE            0x0002
#define SECTION_MAP_READ             0x0004
#define SECTION_MAP_EXECUTE          0x0008
#define SECTION_EXTEND_SIZE          0x0010
#define SECTION_MAP_EXECUTE_EXPLICIT 0x0020 // not included in SECTION_ALL_ACCESS

#define SECTION_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SECTION_QUERY|\
                            SECTION_MAP_WRITE |      \
                            SECTION_MAP_READ |       \
                            SECTION_MAP_EXECUTE |    \
                            SECTION_EXTEND_SIZE)

#define FILE_MAP_WRITE            SECTION_MAP_WRITE
#define FILE_MAP_READ             SECTION_MAP_READ
#define FILE_MAP_ALL_ACCESS       SECTION_ALL_ACCESS
#define FILE_MAP_EXECUTE          SECTION_MAP_EXECUTE_EXPLICIT  // not included in FILE_MAP_ALL_ACCESS
#define FILE_MAP_COPY             0x00000001
#define FILE_MAP_RESERVE          0x80000000
#define FILE_MAP_TARGETS_INVALID  0x40000000
#define FILE_MAP_LARGE_PAGES      0x20000000

#define SE_CREATE_TOKEN_NAME                         (L"SeCreateTokenPrivilege")
#define SE_ASSIGNPRIMARYTOKEN_NAME                   (L"SeAssignPrimaryTokenPrivilege")
#define SE_LOCK_MEMORY_NAME                          (L"SeLockMemoryPrivilege")
#define SE_INCREASE_QUOTA_NAME                       (L"SeIncreaseQuotaPrivilege")
#define SE_UNSOLICITED_INPUT_NAME                    (L"SeUnsolicitedInputPrivilege")
#define SE_MACHINE_ACCOUNT_NAME                      (L"SeMachineAccountPrivilege")
#define SE_TCB_NAME                                  (L"SeTcbPrivilege")
#define SE_SECURITY_NAME                             (L"SeSecurityPrivilege")
#define SE_TAKE_OWNERSHIP_NAME                       (L"SeTakeOwnershipPrivilege")
#define SE_LOAD_DRIVER_NAME                          (L"SeLoadDriverPrivilege")
#define SE_SYSTEM_PROFILE_NAME                       (L"SeSystemProfilePrivilege")
#define SE_SYSTEMTIME_NAME                           (L"SeSystemtimePrivilege")
#define SE_PROF_SINGLE_PROCESS_NAME                  (L"SeProfileSingleProcessPrivilege")
#define SE_INC_BASE_PRIORITY_NAME                    (L"SeIncreaseBasePriorityPrivilege")
#define SE_CREATE_PAGEFILE_NAME                      (L"SeCreatePagefilePrivilege")
#define SE_CREATE_PERMANENT_NAME                     (L"SeCreatePermanentPrivilege")
#define SE_BACKUP_NAME                               (L"SeBackupPrivilege")
#define SE_RESTORE_NAME                              (L"SeRestorePrivilege")
#define SE_SHUTDOWN_NAME                             (L"SeShutdownPrivilege")
#define SE_DEBUG_NAME                                (L"SeDebugPrivilege")
#define SE_AUDIT_NAME                                (L"SeAuditPrivilege")
#define SE_SYSTEM_ENVIRONMENT_NAME                   (L"SeSystemEnvironmentPrivilege")
#define SE_CHANGE_NOTIFY_NAME                        (L"SeChangeNotifyPrivilege")
#define SE_REMOTE_SHUTDOWN_NAME                      (L"SeRemoteShutdownPrivilege")
#define SE_UNDOCK_NAME                               (L"SeUndockPrivilege")
#define SE_SYNC_AGENT_NAME                           (L"SeSyncAgentPrivilege")
#define SE_ENABLE_DELEGATION_NAME                    (L"SeEnableDelegationPrivilege")
#define SE_MANAGE_VOLUME_NAME                        (L"SeManageVolumePrivilege")
#define SE_IMPERSONATE_NAME                          (L"SeImpersonatePrivilege")
#define SE_CREATE_GLOBAL_NAME                        (L"SeCreateGlobalPrivilege")
#define SE_TRUSTED_CREDMAN_ACCESS_NAME               (L"SeTrustedCredManAccessPrivilege")
#define SE_RELABEL_NAME                              (L"SeRelabelPrivilege")
#define SE_INC_WORKING_SET_NAME                      (L"SeIncreaseWorkingSetPrivilege")
#define SE_TIME_ZONE_NAME                            (L"SeTimeZonePrivilege")
#define SE_CREATE_SYMBOLIC_LINK_NAME                 (L"SeCreateSymbolicLinkPrivilege")
#define SE_DELEGATE_SESSION_USER_IMPERSONATE_NAME    (L"SeDelegateSessionUserImpersonatePrivilege")

#define SE_PRIVILEGE_ENABLED_BY_DEFAULT (0x00000001L)
#define SE_PRIVILEGE_ENABLED            (0x00000002L)
#define SE_PRIVILEGE_REMOVED            (0X00000004L)
#define SE_PRIVILEGE_USED_FOR_ACCESS    (0x80000000L)

#define SE_PRIVILEGE_VALID_ATTRIBUTES   (SE_PRIVILEGE_ENABLED_BY_DEFAULT | \
                                         SE_PRIVILEGE_ENABLED            | \
                                         SE_PRIVILEGE_REMOVED            | \
                                         SE_PRIVILEGE_USED_FOR_ACCESS)


#define ANYSIZE_ARRAY 1 

typedef struct {
    LUID Luid;
    DWORD Attributes;
    } LUID_AND_ATTRIBUTES, * PLUID_AND_ATTRIBUTES;
typedef LUID_AND_ATTRIBUTES LUID_AND_ATTRIBUTES_ARRAY[ANYSIZE_ARRAY];
typedef LUID_AND_ATTRIBUTES_ARRAY *PLUID_AND_ATTRIBUTES_ARRAY;

typedef struct  {
    DWORD PrivilegeCount;
    LUID_AND_ATTRIBUTES Privileges[ANYSIZE_ARRAY];
} TOKEN_PRIVILEGES, *PTOKEN_PRIVILEGES;

WINDOWS_IMPORT BOOL WINAPI SetFilePointerEx( HANDLE hFile, LARGE_INTEGER liDistanceToMove, LARGE_INTEGER* lpNewFilePointer, DWORD dwMoveMethod);

WINDOWS_IMPORT HANDLE WINAPI CreateFileMappingW(HANDLE hFile,LPSECURITY_ATTRIBUTES lpFileMappingAttributes,DWORD flProtect,DWORD dwMaximumSizeHigh,DWORD dwMaximumSizeLow,LPCWSTR lpName);

WINDOWS_IMPORT PVOID WINAPI MapViewOfFile(HANDLE hFileMappingObject,DWORD dwDesiredAccess,DWORD dwFileOffsetHigh,DWORD dwFileOffsetLow,size_t dwNumberOfBytesToMap);

WINDOWS_IMPORT BOOL WINAPI LookupPrivilegeValueW(LPCWSTR lpSystemName,LPCWSTR lpName,LUID *lpLuid);

WINDOWS_IMPORT BOOL WINAPI AdjustTokenPrivileges(HANDLE TokenHandle,BOOL DisableAllPrivileges,TOKEN_PRIVILEGES *NewState,DWORD BufferLength,PTOKEN_PRIVILEGES PreviousState,PDWORD ReturnLength);

WINDOWS_IMPORT BOOL WINAPI GetVolumePathNameW( LPCWSTR lpszFileName, LPWSTR lpszVolumePathName, DWORD cchBufferLength);

WINDOWS_IMPORT BOOL WINAPI GetVolumeNameForVolumeMountPointW( LPCWSTR lpszVolumeMountPoint, LPWSTR  lpszVolumeName, DWORD   cchBufferLength
);

typedef struct _DISK_PERFORMANCE {
  LARGE_INTEGER BytesRead;
  LARGE_INTEGER BytesWritten;
  LARGE_INTEGER ReadTime;
  LARGE_INTEGER WriteTime;
  LARGE_INTEGER IdleTime;
  DWORD         ReadCount;
  DWORD         WriteCount;
  DWORD         QueueDepth;
  DWORD         SplitCount;
  LARGE_INTEGER QueryTime;
  DWORD         StorageDeviceNumber;
  WCHAR         StorageManagerName[8];
} DISK_PERFORMANCE, *PDISK_PERFORMANCE;


#define IOCTL_DISK_BASE                 FILE_DEVICE_DISK
#define IOCTL_DISK_GET_DRIVE_GEOMETRY   CTL_CODE(IOCTL_DISK_BASE, 0x0000, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_GET_PARTITION_INFO   CTL_CODE(IOCTL_DISK_BASE, 0x0001, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_DISK_SET_PARTITION_INFO   CTL_CODE(IOCTL_DISK_BASE, 0x0002, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_DISK_GET_DRIVE_LAYOUT     CTL_CODE(IOCTL_DISK_BASE, 0x0003, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_DISK_SET_DRIVE_LAYOUT     CTL_CODE(IOCTL_DISK_BASE, 0x0004, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_DISK_VERIFY               CTL_CODE(IOCTL_DISK_BASE, 0x0005, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_FORMAT_TRACKS        CTL_CODE(IOCTL_DISK_BASE, 0x0006, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_DISK_REASSIGN_BLOCKS      CTL_CODE(IOCTL_DISK_BASE, 0x0007, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_DISK_PERFORMANCE          CTL_CODE(IOCTL_DISK_BASE, 0x0008, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_IS_WRITABLE          CTL_CODE(IOCTL_DISK_BASE, 0x0009, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_LOGGING              CTL_CODE(IOCTL_DISK_BASE, 0x000a, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_FORMAT_TRACKS_EX     CTL_CODE(IOCTL_DISK_BASE, 0x000b, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_DISK_HISTOGRAM_STRUCTURE  CTL_CODE(IOCTL_DISK_BASE, 0x000c, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_HISTOGRAM_DATA       CTL_CODE(IOCTL_DISK_BASE, 0x000d, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_HISTOGRAM_RESET      CTL_CODE(IOCTL_DISK_BASE, 0x000e, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_REQUEST_STRUCTURE    CTL_CODE(IOCTL_DISK_BASE, 0x000f, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_REQUEST_DATA         CTL_CODE(IOCTL_DISK_BASE, 0x0010, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_PERFORMANCE_OFF      CTL_CODE(IOCTL_DISK_BASE, 0x0018, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct _GLYPHMETRICS {
    UINT    gmBlackBoxX;
    UINT    gmBlackBoxY;
    POINT   gmptGlyphOrigin;
    short   gmCellIncX;
    short   gmCellIncY;
} GLYPHMETRICS, *LPGLYPHMETRICS;

typedef struct _FIXED {
#ifndef _MAC
    WORD    fract;
    short   value;
#else
    short   value;
    WORD    fract;
#endif
} FIXED;

typedef struct _MAT2 {
  FIXED eM11;
  FIXED eM12;
  FIXED eM21;
  FIXED eM22;
} MAT2, *LPMAT2;

#define FW_DONTCARE         0
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900

#define FW_ULTRALIGHT       FW_EXTRALIGHT
#define FW_REGULAR          FW_NORMAL
#define FW_DEMIBOLD         FW_SEMIBOLD
#define FW_ULTRABOLD        FW_EXTRABOLD
#define FW_BLACK            FW_HEAVY

#define ANSI_CHARSET            0
#define DEFAULT_CHARSET         1
#define SYMBOL_CHARSET          2
#define SHIFTJIS_CHARSET        128
#define HANGEUL_CHARSET         129
#define HANGUL_CHARSET          129
#define GB2312_CHARSET          134
#define CHINESEBIG5_CHARSET     136
#define OEM_CHARSET             255

#define JOHAB_CHARSET           130
#define HEBREW_CHARSET          177
#define ARABIC_CHARSET          178
#define GREEK_CHARSET           161
#define TURKISH_CHARSET         162
#define VIETNAMESE_CHARSET      163
#define THAI_CHARSET            222
#define EASTEUROPE_CHARSET      238
#define RUSSIAN_CHARSET         204

#define OUT_DEFAULT_PRECIS          0
#define OUT_STRING_PRECIS           1
#define OUT_CHARACTER_PRECIS        2
#define OUT_STROKE_PRECIS           3
#define OUT_TT_PRECIS               4
#define OUT_DEVICE_PRECIS           5
#define OUT_RASTER_PRECIS           6
#define OUT_TT_ONLY_PRECIS          7
#define OUT_OUTLINE_PRECIS          8
#define OUT_SCREEN_OUTLINE_PRECIS   9
#define OUT_PS_ONLY_PRECIS          10

#define CLIP_DEFAULT_PRECIS     0
#define CLIP_CHARACTER_PRECIS   1
#define CLIP_STROKE_PRECIS      2
#define CLIP_MASK               0xf
#define CLIP_LH_ANGLES          (1<<4)
#define CLIP_TT_ALWAYS          (2<<4)
#if (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
#define CLIP_DFA_DISABLE        (4<<4)
#endif // (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
#define CLIP_EMBEDDED           (8<<4)

#define DEFAULT_QUALITY         0
#define DRAFT_QUALITY           1
#define PROOF_QUALITY           2
#if(WINVER >= 0x0400)
#define NONANTIALIASED_QUALITY  3
#define ANTIALIASED_QUALITY     4
#endif /* WINVER >= 0x0400 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WINXP)
#define CLEARTYPE_QUALITY       5
#define CLEARTYPE_NATURAL_QUALITY       6
#endif

#define DEFAULT_PITCH           0
#define FIXED_PITCH             1
#define VARIABLE_PITCH          2
#if(WINVER >= 0x0400)
#define MONO_FONT               8
#endif /* WINVER >= 0x0400 */

#define ANSI_CHARSET            0
#define DEFAULT_CHARSET         1
#define SYMBOL_CHARSET          2
#define SHIFTJIS_CHARSET        128
#define HANGEUL_CHARSET         129
#define HANGUL_CHARSET          129
#define GB2312_CHARSET          134
#define CHINESEBIG5_CHARSET     136
#define OEM_CHARSET             255
#if(WINVER >= 0x0400)
#define JOHAB_CHARSET           130
#define HEBREW_CHARSET          177
#define ARABIC_CHARSET          178
#define GREEK_CHARSET           161
#define TURKISH_CHARSET         162
#define VIETNAMESE_CHARSET      163
#define THAI_CHARSET            222
#define EASTEUROPE_CHARSET      238
#define RUSSIAN_CHARSET         204

#define MAC_CHARSET             77
#define BALTIC_CHARSET          186

#define FS_LATIN1               0x00000001L
#define FS_LATIN2               0x00000002L
#define FS_CYRILLIC             0x00000004L
#define FS_GREEK                0x00000008L
#define FS_TURKISH              0x00000010L
#define FS_HEBREW               0x00000020L
#define FS_ARABIC               0x00000040L
#define FS_BALTIC               0x00000080L
#define FS_VIETNAMESE           0x00000100L
#define FS_THAI                 0x00010000L
#define FS_JISJAPAN             0x00020000L
#define FS_CHINESESIMP          0x00040000L
#define FS_WANSUNG              0x00080000L
#define FS_CHINESETRAD          0x00100000L
#define FS_JOHAB                0x00200000L
#define FS_SYMBOL               0x80000000L
#endif /* WINVER >= 0x0400 */

/* Font Families */
#define FF_DONTCARE         (0<<4)  /* Don't care or don't know. */
#define FF_ROMAN            (1<<4)  /* Variable stroke width, serifed. */
                                    /* Times Roman, Century Schoolbook, etc. */
#define FF_SWISS            (2<<4)  /* Variable stroke width, sans-serifed. */
                                    /* Helvetica, Swiss, etc. */
#define FF_MODERN           (3<<4)  /* Constant stroke width, serifed or sans-serifed. */
                                    /* Pica, Elite, Courier, etc. */
#define FF_SCRIPT           (4<<4)  /* Cursive, etc. */
#define FF_DECORATIVE       (5<<4)  /* Old English, etc. */

#define GGO_METRICS        0
#define GGO_BITMAP         1
#define GGO_NATIVE         2
#define GGO_BEZIER         3

#if(WINVER >= 0x0400)
#define  GGO_GRAY2_BITMAP   4
#define  GGO_GRAY4_BITMAP   5
#define  GGO_GRAY8_BITMAP   6
#define  GGO_GLYPH_INDEX    0x0080
#endif /* WINVER >= 0x0400 */

typedef struct tagBITMAP {
  LONG   bmType;
  LONG   bmWidth;
  LONG   bmHeight;
  LONG   bmWidthBytes;
  WORD   bmPlanes;
  WORD   bmBitsPixel;
  LPVOID bmBits;
} BITMAP, *PBITMAP, *NPBITMAP, *LPBITMAP;

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
#define  GGO_UNHINTED       0x0100
#endif // (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)

#define TT_POLYGON_TYPE   24

#define TT_PRIM_LINE       1
#define TT_PRIM_QSPLINE    2
#define TT_PRIM_CSPLINE    3

WINDOWS_IMPORT HFONT WINAPI CreateFontA( int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet, DWORD iOutPrecision, DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily, LPCSTR pszFaceName);

WINDOWS_IMPORT DWORD WINAPI GetGlyphOutlineA( HDC hdc, UINT uChar, UINT fuFormat, LPGLYPHMETRICS lpgm, DWORD cjBuffer, LPVOID pvBuffer, const MAT2 *lpmat2);

WINDOWS_IMPORT HGDIOBJ WINAPI SelectObject(HDC hdc,HGDIOBJ h);

WINDOWS_IMPORT void WINAPI Sleep(DWORD dwMilliseconds);
typedef DWORD COLORREF;
typedef DWORD* LPCOLORREF;
typedef struct tagLOGFONTA {
  LONG lfHeight;
  LONG lfWidth;
  LONG lfEscapement;
  LONG lfOrientation;
  LONG lfWeight;
  BYTE lfItalic;
  BYTE lfUnderline;
  BYTE lfStrikeOut;
  BYTE lfCharSet;
  BYTE lfOutPrecision;
  BYTE lfClipPrecision;
  BYTE lfQuality;
  BYTE lfPitchAndFamily;
  CHAR lfFaceName[32];
} LOGFONTA, *PLOGFONTA, *NPLOGFONTA, *LPLOGFONTA;

WINDOWS_IMPORT int WINAPI GetObjectA( HANDLE h, int c, LPVOID pv);

WINDOWS_IMPORT COLORREF WINAPI SetTextColor( HDC hdc, COLORREF color);

WINDOWS_IMPORT int WINAPI SetBkMode( HDC hdc, int mode);
WINDOWS_IMPORT UINT WINAPI SetTextAlign( HDC hdc, UINT align);



/* EnumFonts Masks */
#define RASTER_FONTTYPE     0x0001
#define DEVICE_FONTTYPE     0x0002
#define TRUETYPE_FONTTYPE   0x0004

#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define PALETTERGB(r,g,b)   (0x02000000 | RGB(r,g,b))
#define PALETTEINDEX(i)     ((COLORREF)(0x01000000 | (DWORD)(WORD)(i)))

/* palette entry flags */

#define PC_RESERVED     0x01    /* palette index used for animation */
#define PC_EXPLICIT     0x02    /* palette index is explicit to device */
#define PC_NOCOLLAPSE   0x04    /* do not match color to system palette */

#define GetRValue(rgb)      (LOBYTE(rgb))
#define GetGValue(rgb)      (LOBYTE(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)      (LOBYTE((rgb)>>16))

/* Background Modes */
#define TRANSPARENT         1
#define OPAQUE              2
#define BKMODE_LAST         2

/* Text Alignment Options */
#define TA_NOUPDATECP                0
#define TA_UPDATECP                  1

#define TA_LEFT                      0
#define TA_RIGHT                     2
#define TA_CENTER                    6

#define TA_TOP                       0
#define TA_BOTTOM                    8
#define TA_BASELINE                  24
#if (WINVER >= 0x0400)
#define TA_RTLREADING                256
#define TA_MASK       (TA_BASELINE+TA_CENTER+TA_UPDATECP+TA_RTLREADING)
#else
#define TA_MASK       (TA_BASELINE+TA_CENTER+TA_UPDATECP)
#endif

#define VTA_BASELINE TA_BASELINE
#define VTA_LEFT     TA_BOTTOM
#define VTA_RIGHT    TA_TOP
#define VTA_CENTER   TA_CENTER
#define VTA_BOTTOM   TA_RIGHT
#define VTA_TOP      TA_LEFT

WINDOWS_IMPORT BOOL WINAPI ExtTextOutW( HDC hdc, int x, int y, UINT options , RECT *lprect, LPCWSTR lpString, UINT c, INT  *lpDx);
WINDOWS_IMPORT BOOL WINAPI TextOutW( HDC hdc, int x, int y, LPCWSTR lpString, int c);

#define GCP_DBCS           0x0001
#define GCP_REORDER        0x0002
#define GCP_USEKERNING     0x0008
#define GCP_GLYPHSHAPE     0x0010
#define GCP_LIGATE         0x0020
////#define GCP_GLYPHINDEXING  0x0080
#define GCP_DIACRITIC      0x0100
#define GCP_KASHIDA        0x0400
#define GCP_ERROR          0x8000
#define FLI_MASK           0x103B

#define GCP_JUSTIFY        0x00010000L
////#define GCP_NODIACRITICS   0x00020000L
#define FLI_GLYPHS         0x00040000L
#define GCP_CLASSIN        0x00080000L
#define GCP_MAXEXTENT      0x00100000L
#define GCP_JUSTIFYIN      0x00200000L
#define GCP_DISPLAYZWG      0x00400000L
#define GCP_SYMSWAPOFF      0x00800000L
#define GCP_NUMERICOVERRIDE 0x01000000L
#define GCP_NEUTRALOVERRIDE 0x02000000L
#define GCP_NUMERICSLATIN   0x04000000L
#define GCP_NUMERICSLOCAL   0x08000000L

#define GCPCLASS_LATIN                  1
#define GCPCLASS_HEBREW                 2
#define GCPCLASS_ARABIC                 2
#define GCPCLASS_NEUTRAL                3
#define GCPCLASS_LOCALNUMBER            4
#define GCPCLASS_LATINNUMBER            5
#define GCPCLASS_LATINNUMERICTERMINATOR 6
#define GCPCLASS_LATINNUMERICSEPARATOR  7
#define GCPCLASS_NUMERICSEPARATOR       8
#define GCPCLASS_PREBOUNDLTR         0x80
#define GCPCLASS_PREBOUNDRTL         0x40
#define GCPCLASS_POSTBOUNDLTR        0x20
#define GCPCLASS_POSTBOUNDRTL        0x10

#define GCPGLYPH_LINKBEFORE          0x8000
#define GCPGLYPH_LINKAFTER           0x4000

typedef struct tagGCP_RESULTSA
{
    DWORD   lStructSize;
    LPSTR     lpOutString;
    UINT *lpOrder;
    int  *lpDx;
    int  *lpCaretPos;
    LPSTR   lpClass;
    LPWSTR  lpGlyphs;
    UINT    nGlyphs;
    int     nMaxFit;
} GCP_RESULTSA, *LPGCP_RESULTSA;
typedef struct tagGCP_RESULTSW
{
    DWORD   lStructSize;
    LPWSTR    lpOutString;
    UINT *lpOrder;
    int  *lpDx;
    int  *lpCaretPos;
    LPSTR   lpClass;
    LPWSTR  lpGlyphs;
    UINT    nGlyphs;
    int     nMaxFit;
} GCP_RESULTSW, *LPGCP_RESULTSW;

WINDOWS_IMPORT DWORD WINAPI GetCharacterPlacementW( HDC hdc, LPCWSTR lpString, int nCount, int nMexExtent, LPGCP_RESULTSW lpResults, DWORD dwFlags);

WINDOWS_IMPORT DWORD WINAPI GetGlyphIndicesW( HDC hdc, LPCWSTR lpstr, int c, LPWORD pgi, DWORD fl);

typedef struct tagKERNINGPAIR {
  WORD wFirst;
  WORD wSecond;
  int  iKernAmount;
} KERNINGPAIR, *LPKERNINGPAIR;

WINDOWS_IMPORT DWORD WINAPI GetKerningPairsW( HDC hdc, DWORD nPairs, LPKERNINGPAIR lpKernPair);

/* flAccel flags for the GLYPHSET structure above */

#define GS_8BIT_INDICES     0x00000001

/* flags for GetGlyphIndices */

#define GGI_MARK_NONEXISTING_GLYPHS  0X0001

WINDOWS_IMPORT BOOL WINAPI GetOverlappedResult( HANDLE hFile, LPOVERLAPPED lpOverlapped, LPDWORD lpNumberOfBytesTransferred, BOOL bWait);

WINDOWS_IMPORT HANDLE WINAPI CreateEventA( LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCSTR lpName
);

WINDOWS_IMPORT BOOL WINAPI ResetEvent(HANDLE hEvent);


WINDOWS_IMPORT LPVOID WINAPI HeapAlloc(HANDLE hHeap,DWORD  dwFlags,u64 dwBytes);

WINDOWS_IMPORT HANDLE WINAPI GetProcessHeap(void);


WINDOWS_IMPORT BOOL WINAPI HeapFree(HANDLE hHeap,DWORD dwFlags,LPVOID lpMem);

WINDOWS_IMPORT HPEN WINAPI CreatePen( int iStyle, int cWidth, COLORREF color);

/* Pen Styles */
#define PS_SOLID            0
#define PS_DASH             1       /* -------  */
#define PS_DOT              2       /* .......  */
#define PS_DASHDOT          3       /* _._._._  */
#define PS_DASHDOTDOT       4       /* _.._.._  */
#define PS_NULL             5
#define PS_INSIDEFRAME      6
#define PS_USERSTYLE        7
#define PS_ALTERNATE        8
#define PS_STYLE_MASK       0x0000000F

#define DC_BRUSH            18
#define DC_PEN              19

#define NULL_BRUSH          5
#define ETO_OPAQUE                   0x0002
#define ETO_CLIPPED                  0x0004
#if(WINVER >= 0x0400)
#define ETO_GLYPH_INDEX              0x0010
#define ETO_RTLREADING               0x0080
#define ETO_NUMERICSLOCAL            0x0400
#define ETO_NUMERICSLATIN            0x0800
#define ETO_IGNORELANGUAGE           0x1000
#endif /* WINVER >= 0x0400 */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
#define ETO_PDY                      0x2000
#endif // (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
#if (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
#define ETO_REVERSE_INDEX_MAP        0x10000
#endif

typedef USHORT COLOR16;

typedef struct _TRIVERTEX
{
    LONG    x;
    LONG    y;
    COLOR16 Red;
    COLOR16 Green;
    COLOR16 Blue;
    COLOR16 Alpha;
}TRIVERTEX,*PTRIVERTEX,*LPTRIVERTEX;

typedef struct _BLENDFUNCTION
{
    BYTE   BlendOp;
    BYTE   BlendFlags;
    BYTE   SourceConstantAlpha;
    BYTE   AlphaFormat;
}BLENDFUNCTION,*PBLENDFUNCTION;

typedef struct _GRADIENT_TRIANGLE
{
    ULONG Vertex1;
    ULONG Vertex2;
    ULONG Vertex3;
} GRADIENT_TRIANGLE,*PGRADIENT_TRIANGLE,*LPGRADIENT_TRIANGLE;


#define AC_SRC_OVER                 0x00

//
// alpha format flags
//

#define AC_SRC_ALPHA                0x01

#define GRADIENT_FILL_RECT_H    0x00000000
#define GRADIENT_FILL_RECT_V    0x00000001
#define GRADIENT_FILL_TRIANGLE  0x00000002
#define GRADIENT_FILL_OP_FLAG   0x000000ff

#define TRUE 1
#define FALSE 0

typedef struct tagTEXTMETRICW
{
    LONG        tmHeight;
    LONG        tmAscent;
    LONG        tmDescent;
    LONG        tmInternalLeading;
    LONG        tmExternalLeading;
    LONG        tmAveCharWidth;
    LONG        tmMaxCharWidth;
    LONG        tmWeight;
    LONG        tmOverhang;
    LONG        tmDigitizedAspectX;
    LONG        tmDigitizedAspectY;
    WCHAR       tmFirstChar;
    WCHAR       tmLastChar;
    WCHAR       tmDefaultChar;
    WCHAR       tmBreakChar;
    BYTE        tmItalic;
    BYTE        tmUnderlined;
    BYTE        tmStruckOut;
    BYTE        tmPitchAndFamily;
    BYTE        tmCharSet;
} TEXTMETRICW, *PTEXTMETRICW, *NPTEXTMETRICW, *LPTEXTMETRICW;

#define CF_TEXT               1
#define CF_BITMAP             2
#define CF_METAFILEPICT       3
#define CF_SYLK               4
#define CF_DIF                5
#define CF_TIFF               6
#define CF_OEMTEXT            7
#define CF_DIB                8
#define CF_PALETTE            9
#define CF_PENDATA            10
#define CF_RIFF               11
#define CF_WAVE               12
#define CF_UNICODETEXT        13
#define CF_ENHMETAFILE        14
#define CF_HDROP              15
#define CF_LOCALE             16
#define CF_DIBV5              17

#define CF_OWNERDISPLAY       0x0080
#define CF_DSPTEXT            0x0081
#define CF_DSPBITMAP          0x0082
#define CF_DSPMETAFILEPICT    0x0083
#define CF_DSPENHMETAFILE     0x008E

#define CF_PRIVATEFIRST       0x0200
#define CF_PRIVATELAST        0x02FF

#define CF_GDIOBJFIRST        0x0300
#define CF_GDIOBJLAST         0x03FF

#define VK_LBUTTON             0x01
#define VK_RBUTTON             0x02
#define VK_CANCEL              0x03
#define VK_MBUTTON             0x04
#define VK_XBUTTON1            0x05
#define VK_XBUTTON2            0x06
#define VK_BACK                0x08
#define VK_TAB                 0x09
#define VK_CLEAR               0x0C
#define VK_RETURN              0x0D
#define VK_SHIFT               0x10
#define VK_CONTROL             0x11
#define VK_MENU                0x12
#define VK_PAUSE               0x13
#define VK_CAPITAL             0x14
#define VK_KANA                0x15
#define VK_HANGUL              0x15
#define VK_IME_ON              0x16
#define VK_JUNJA               0x17
#define VK_FINAL               0x18
#define VK_HANJA               0x19
#define VK_KANJI               0x19
#define VK_IME_OFF             0x1A
#define VK_ESCAPE              0x1B
#define VK_CONVERT             0x1C
#define VK_NONCONVERT          0x1D
#define VK_ACCEPT              0x1E
#define VK_MODECHANGE          0x1F
#define VK_SPACE               0x20
#define VK_PRIOR               0x21
#define VK_NEXT                0x22
#define VK_END                 0x23
#define VK_HOME                0x24
#define VK_LEFT                0x25
#define VK_UP                  0x26
#define VK_RIGHT               0x27
#define VK_DOWN                0x28
#define VK_SELECT              0x29
#define VK_PRINT               0x2A
#define VK_EXECUTE             0x2B
#define VK_SNAPSHOT            0x2C
#define VK_INSERT              0x2D
#define VK_DELETE              0x2E
#define VK_HELP                0x2F

#define VK_0                   0x30
#define VK_1                   0x31
#define VK_2                   0x32
#define VK_3                   0x33
#define VK_4                   0x34
#define VK_5                   0x35
#define VK_6                   0x36
#define VK_7                   0x37
#define VK_8                   0x38
#define VK_9                   0x39

#define VK_A                   0x41
#define VK_B                   0x42
#define VK_C                   0x43
#define VK_D                   0x44
#define VK_E                   0x45
#define VK_F                   0x46
#define VK_G                   0x47
#define VK_H                   0x48
#define VK_I                   0x49
#define VK_J                   0x4A
#define VK_K                   0x4B
#define VK_L                   0x4C
#define VK_M                   0x4D
#define VK_N                   0x4E
#define VK_O                   0x4F
#define VK_P                   0x50
#define VK_Q                   0x51
#define VK_R                   0x52
#define VK_S                   0x53
#define VK_T                   0x54
#define VK_U                   0x55
#define VK_V                   0x56
#define VK_W                   0x57
#define VK_X                   0x58
#define VK_Y                   0x59
#define VK_Z                   0x5A

#define VK_LWIN                0x5B
#define VK_RWIN                0x5C
#define VK_APPS                0x5D
#define VK_SLEEP               0x5F

#define VK_NUMPAD0             0x60
#define VK_NUMPAD1             0x61
#define VK_NUMPAD2             0x62
#define VK_NUMPAD3             0x63
#define VK_NUMPAD4             0x64
#define VK_NUMPAD5             0x65
#define VK_NUMPAD6             0x66
#define VK_NUMPAD7             0x67
#define VK_NUMPAD8             0x68
#define VK_NUMPAD9             0x69
#define VK_MULTIPLY            0x6A
#define VK_ADD                 0x6B
#define VK_SEPARATOR           0x6C
#define VK_SUBTRACT            0x6D
#define VK_DECIMAL             0x6E
#define VK_DIVIDE              0x6F

#define VK_F1                  0x70
#define VK_F2                  0x71
#define VK_F3                  0x72
#define VK_F4                  0x73
#define VK_F5                  0x74
#define VK_F6                  0x75
#define VK_F7                  0x76
#define VK_F8                  0x77
#define VK_F9                  0x78
#define VK_F10                 0x79
#define VK_F11                 0x7A
#define VK_F12                 0x7B
#define VK_F13                 0x7C
#define VK_F14                 0x7D
#define VK_F15                 0x7E
#define VK_F16                 0x7F
#define VK_F17                 0x80
#define VK_F18                 0x81
#define VK_F19                 0x82
#define VK_F20                 0x83
#define VK_F21                 0x84
#define VK_F22                 0x85
#define VK_F23                 0x86
#define VK_F24                 0x87

#define VK_NUMLOCK             0x90
#define VK_SCROLL              0x91

#define VK_LSHIFT              0xA0
#define VK_RSHIFT              0xA1
#define VK_LCONTROL            0xA2
#define VK_RCONTROL            0xA3
#define VK_LMENU               0xA4
#define VK_RMENU               0xA5

#define VK_BROWSER_BACK        0xA6
#define VK_BROWSER_FORWARD     0xA7
#define VK_BROWSER_REFRESH     0xA8
#define VK_BROWSER_STOP        0xA9
#define VK_BROWSER_SEARCH      0xAA
#define VK_BROWSER_FAVORITES   0xAB
#define VK_BROWSER_HOME        0xAC

#define VK_VOLUME_MUTE         0xAD
#define VK_VOLUME_DOWN         0xAE
#define VK_VOLUME_UP           0xAF

#define VK_MEDIA_NEXT_TRACK    0xB0
#define VK_MEDIA_PREV_TRACK    0xB1
#define VK_MEDIA_STOP          0xB2
#define VK_MEDIA_PLAY_PAUSE    0xB3

#define VK_LAUNCH_MAIL         0xB4
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define VK_LAUNCH_APP1         0xB6
#define VK_LAUNCH_APP2         0xB7

#define VK_OEM_1               0xBA
#define VK_OEM_PLUS            0xBB
#define VK_OEM_COMMA           0xBC
#define VK_OEM_MINUS           0xBD
#define VK_OEM_PERIOD          0xBE
#define VK_OEM_2               0xBF
#define VK_OEM_3               0xC0
#define VK_OEM_4               0xDB
#define VK_OEM_5               0xDC
#define VK_OEM_6               0xDD
#define VK_OEM_7               0xDE
#define VK_OEM_8               0xDF
#define VK_OEM_102             0xE2

#define VK_PROCESSKEY          0xE5
#define VK_PACKET              0xE7

#define VK_ATTN                0xF6
#define VK_CRSEL               0xF7
#define VK_EXSEL               0xF8
#define VK_EREOF               0xF9
#define VK_PLAY                0xFA
#define VK_ZOOM                0xFB
#define VK_NONAME              0xFC
#define VK_PA1                 0xFD
#define VK_OEM_CLEAR           0xFE

typedef struct tagSIZE {
  LONG cx;
  LONG cy;
} SIZE, *PSIZE, *LPSIZE;

typedef struct tagPAINTSTRUCT {
  HDC  hdc;
  BOOL fErase;
  RECT rcPaint;
  BOOL fRestore;
  BOOL fIncUpdate;
  BYTE rgbReserved[32];
} PAINTSTRUCT, *PPAINTSTRUCT, *NPPAINTSTRUCT, *LPPAINTSTRUCT;

#define GMEM_FIXED          0x0000
#define GMEM_MOVEABLE       0x0002
#define GMEM_NOCOMPACT      0x0010
#define GMEM_NODISCARD      0x0020
#define GMEM_ZEROINIT       0x0040
#define GMEM_MODIFY         0x0080
#define GMEM_DISCARDABLE    0x0100
#define GMEM_NOT_BANKED     0x1000
#define GMEM_SHARE          0x2000
#define GMEM_DDESHARE       0x2000
#define GMEM_NOTIFY         0x4000
#define GMEM_LOWER          GMEM_NOT_BANKED
#define GMEM_VALID_FLAGS    0x7F72
#define GMEM_INVALID_HANDLE 0x8000

WINDOWS_IMPORT int WINAPI GetDIBits(HDC hdc, HBITMAP hbm, UINT start, UINT cLines, LPVOID lpvBits, LPBITMAPINFO lpbmi, UINT usage);

WINDOWS_IMPORT int WINAPI SetDIBits(HDC hdc, HBITMAP hbm, UINT start, UINT cLines, const LPVOID lpBits, const BITMAPINFO *lpbmi, UINT ColorUse);

WINDOWS_IMPORT HDC WINAPI CreateCompatibleDC(HDC hdc);

#define GetObject GetObjectA

#ifndef LOWORD
#define LOWORD(l) ((WORD)((l) & 0xFFFF))
#endif

#ifndef HIWORD
#define HIWORD(l) ((WORD)(((l) >> 16) & 0xFFFF))
#endif


WINDOWS_IMPORT BOOL WINAPI StretchBlt(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop);

WINDOWS_IMPORT BOOL WINAPI DeleteDC(HDC hdc);

WINDOWS_IMPORT int WINAPI SelectClipRgn(HDC hdc, HRGN hrgn);

WINDOWS_IMPORT int WINAPI IntersectClipRect(HDC hdc, int left, int top, int right, int bottom);

WINDOWS_IMPORT COLORREF WINAPI SetDCPenColor(HDC hdc, COLORREF color);

WINDOWS_IMPORT BOOL WINAPI MoveToEx(HDC hdc, int x, int y, LPPOINT lppt);

WINDOWS_IMPORT BOOL WINAPI LineTo(HDC hdc, int x, int y);

WINDOWS_IMPORT HGDIOBJ WINAPI GetStockObject(int i);

WINDOWS_IMPORT BOOL WINAPI Rectangle(HDC hdc, int left, int top, int right, int bottom);

WINDOWS_IMPORT BOOL WINAPI RoundRect(HDC hdc, int left, int top, int right, int bottom, int width, int height);

WINDOWS_IMPORT BOOL WINAPI SetRect(LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom);

WINDOWS_IMPORT COLORREF WINAPI SetBkColor(HDC hdc, COLORREF color);

WINDOWS_IMPORT COLORREF WINAPI SetDCBrushColor(HDC hdc, COLORREF color);

WINDOWS_IMPORT BOOL WINAPI GdiGradientFill(HDC hdc, PTRIVERTEX pVertex, ULONG nVertex, PVOID pMesh, ULONG nMesh, ULONG dwMode);

WINDOWS_IMPORT BOOL WINAPI AlphaBlend(HDC hdcDest, int xDest, int yDest, int wDest, int hDest,
                                      HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, BLENDFUNCTION blend);

WINDOWS_IMPORT BOOL WINAPI Polygon(HDC hdc, const POINT *apt, int cpt);

WINDOWS_IMPORT BOOL WINAPI Polyline(HDC hdc, const POINT *apt, int cpt);

WINDOWS_IMPORT BOOL WINAPI Ellipse(HDC hdc, int left, int top, int right, int bottom);

WINDOWS_IMPORT BOOL WINAPI PolyBezier(HDC hdc, const POINT *apt, DWORD cpt);

WINDOWS_IMPORT BOOL WINAPI BitBlt(HDC hdcDest, int xDest, int yDest, int w, int h,
                                   HDC hdcSrc, int xSrc, int ySrc, DWORD rop);

WINDOWS_IMPORT BOOL WINAPI GetTextMetricsW(HDC hdc, LPTEXTMETRICW lptm);

WINDOWS_IMPORT BOOL WINAPI GetTextExtentPoint32W(HDC hdc, LPCWSTR lpStr, int c, LPSIZE lpSize);

WINDOWS_IMPORT BOOL WINAPI IsClipboardFormatAvailable(UINT format);

WINDOWS_IMPORT BOOL WINAPI OpenClipboard(HWND hWndNewOwner);

WINDOWS_IMPORT HANDLE WINAPI GetClipboardData(UINT uFormat);

WINDOWS_IMPORT u64 WINAPI GlobalSize(HGLOBAL hMem);

WINDOWS_IMPORT LPVOID WINAPI GlobalLock(HGLOBAL hMem);

WINDOWS_IMPORT BOOL WINAPI GlobalUnlock(HGLOBAL hMem);

WINDOWS_IMPORT BOOL WINAPI CloseClipboard(void);

WINDOWS_IMPORT HGLOBAL WINAPI GlobalAlloc(UINT uFlags, u64 dwBytes);

WINDOWS_IMPORT HANDLE WINAPI SetClipboardData(UINT uFormat, HANDLE hMem);

WINDOWS_IMPORT HBITMAP WINAPI CreateCompatibleBitmap(HDC hdc, int cx, int cy);

WINDOWS_IMPORT HDC WINAPI BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint);

WINDOWS_IMPORT BOOL WINAPI EndPaint(HWND hWnd, const PAINTSTRUCT *lpPaint);

WINDOWS_IMPORT short WINAPI GetKeyState(int nVirtKey);

WINDOWS_IMPORT HWND WINAPI SetCapture(HWND hWnd);

WINDOWS_IMPORT BOOL WINAPI ReleaseCapture(void);

WINDOWS_IMPORT HMODULE WINAPI GetModuleHandleA(LPCSTR lpModuleName);
#define GetModuleHandle GetModuleHandleA

WINDOWS_IMPORT HICON WINAPI LoadIconA(HINSTANCE hInstance, LPCSTR lpIconName);

#define IDI_APPLICATION 32512

#define LoadIcon LoadIconW

WINDOWS_IMPORT HCURSOR WINAPI LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName);

#define IDC_ARROW 32512

#define LoadCursor LoadCursorW

WINDOWS_IMPORT BOOL WINAPI UnregisterClassW(LPCWSTR lpClassName, HINSTANCE hInstance);

WINDOWS_IMPORT BOOL WINAPI SetWindowTextA(HWND hWnd, LPCSTR lpString);

WINDOWS_IMPORT HDC WINAPI GetWindowDC(HWND hWnd);

WINDOWS_IMPORT int WINAPI ReleaseDC(HWND hWnd, HDC hDC);

WINDOWS_IMPORT BOOL WINAPI CloseWindow(HWND hWnd);

WINDOWS_IMPORT BOOL WINAPI PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
#define PeekMessage PeekMessageW

WINDOWS_IMPORT int WINAPI GetWindowTextA(HWND hWnd, LPSTR lpString, int nMaxCount);

WINDOWS_IMPORT LONG_PTR WINAPI SetWindowLongPtrA(HWND hWnd,int nIndex,LONG_PTR dwNewLong);

WINDOWS_IMPORT LONG_PTR WINAPI SetWindowLongPtrW(HWND hWnd, int nIndex, LONG_PTR dwNewLong);

#define SetWindowLongPtr SetWindowLongPtrW

typedef struct tagCREATESTRUCTA {
  LPVOID    lpCreateParams;
  HINSTANCE hInstance;
  HMENU     hMenu;
  HWND      hwndParent;
  int       cy;
  int       cx;
  int       y;
  int       x;
  LONG      style;
  LPCSTR    lpszName;
  LPCSTR    lpszClass;
  DWORD     dwExStyle;
} CREATESTRUCTA, *LPCREATESTRUCTA;
#define CREATESTRUCT CREATESTRUCTA

#define GWL_WNDPROC         (-4)
#define GWL_HINSTANCE       (-6)
#define GWL_HWNDPARENT      (-8)
#define GWL_STYLE           (-16)
#define GWL_EXSTYLE         (-20)
#define GWL_USERDATA        (-21)
#define GWL_ID              (-12)


#define DefWindowProc DefWindowProcW

WINDOWS_IMPORT HICON WINAPI LoadIconW(HINSTANCE hInstance, LPCWSTR lpIconName);

WINDOWS_IMPORT HCURSOR WINAPI LoadCursorW(HINSTANCE hInstance, LPCWSTR lpCursorName);

WINDOWS_IMPORT BOOL WINAPI PeekMessageW(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

WINDOWS_IMPORT LONG_PTR WINAPI SetWindowLongPtrW(HWND hWnd, int nIndex, LONG_PTR dwNewLong);

WINDOWS_IMPORT LONG_PTR WINAPI GetWindowLongPtrW(HWND hWnd, int nIndex);

WINDOWS_IMPORT BOOL WINAPI GetCursorPos(LPPOINT lpPoint);


#define GWLP_WNDPROC        (-4)
#define GWLP_HINSTANCE      (-6)
#define GWLP_HWNDPARENT     (-8)
#define GWLP_USERDATA       (-21)
#define GWLP_ID             (-12)

WINDOWS_IMPORT DWORD WINAPI GetLogicalDriveStringsA(DWORD nBufferLength,LPSTR lpBuffer);
