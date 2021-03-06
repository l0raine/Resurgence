#pragma once

#include "pe_structs.h"

#define MAKEINTRESOURCEW(i) ((PWCH)((ULONG_PTR)((USHORT)(i))))
#define ROUND_UP(N, S) ((( (N) + (S)  - 1) / (S) ) * (S) )

typedef USHORT RTL_ATOM, *PRTL_ATOM;

#pragma warning(disable : 4214 4201)

typedef struct _SYSTEM_SERVICE_DESCRIPTOR_TABLE
{
    PULONG_PTR ServiceTableBase;
    PULONG ServiceCounterTableBase;
    ULONG_PTR NumberOfServices;
    PUCHAR ParamTableBase;
} SYSTEM_SERVICE_DESCRIPTOR_TABLE, *PSYSTEM_SERVICE_DESCRIPTOR_TABLE;

typedef union _PS_PROTECTION
{
    UCHAR Level;
    struct
    {
        UCHAR Type : 3;
        UCHAR Audit : 1;
        UCHAR Signer : 4;
    } Flags;
} PS_PROTECTION, *PPS_PROTECTION;

typedef union _KEXECUTE_OPTIONS
{
    struct
    {
        UCHAR ExecuteDisable : 1;
        UCHAR ExecuteEnable : 1;
        UCHAR DisableThunkEmulation : 1;
        UCHAR Permanent : 1;
        UCHAR ExecuteDispatchEnable : 1;
        UCHAR ImageDispatchEnable : 1;
        UCHAR DisableExceptionChainValidation : 1;
        UCHAR Spare : 1;
    } Flags;

    UCHAR ExecuteOptions;
    UCHAR ExecuteOptionsNV;
} KEXECUTE_OPTIONS, *PKEXECUTE_OPTIONS;

typedef union _EXHANDLE
{
    struct
    {
        int TagBits : 2;
        int Index : 30;
    } u;
    void * GenericHandleOverlay;
    ULONG_PTR Value;
} EXHANDLE, *PEXHANDLE;

typedef struct _HANDLE_TABLE_ENTRY // Size=16
{
    union
    {
        ULONG_PTR VolatileLowValue; // Size=8 Offset=0
        ULONG_PTR LowValue; // Size=8 Offset=0
        struct _HANDLE_TABLE_ENTRY_INFO * InfoTable; // Size=8 Offset=0
        struct
        {
            ULONG_PTR Unlocked : 1; // Size=8 Offset=0 BitOffset=0 BitCount=1
            ULONG_PTR RefCnt : 16; // Size=8 Offset=0 BitOffset=1 BitCount=16
            ULONG_PTR Attributes : 3; // Size=8 Offset=0 BitOffset=17 BitCount=3
            ULONG_PTR ObjectPointerBits : 44; // Size=8 Offset=0 BitOffset=20 BitCount=44
        };
    };
    union
    {
        ULONG_PTR HighValue; // Size=8 Offset=8
        struct _HANDLE_TABLE_ENTRY * NextFreeHandleEntry; // Size=8 Offset=8
        union _EXHANDLE LeafHandleValue; // Size=8 Offset=8
        struct
        {
            ULONG GrantedAccessBits : 25; // Size=4 Offset=8 BitOffset=0 BitCount=25
            ULONG NoRightsUpgrade : 1; // Size=4 Offset=8 BitOffset=25 BitCount=1
            ULONG Spare : 6; // Size=4 Offset=8 BitOffset=26 BitCount=6
        };
    };
    ULONG TypeInfo; // Size=4 Offset=12
} HANDLE_TABLE_ENTRY, *PHANDLE_TABLE_ENTRY;



typedef struct _OBJECT_HEADER // Size=56
{
    ULONG_PTR PointerCount; // Size=8 Offset=0
    union
    {
        ULONG_PTR HandleCount; // Size=8 Offset=8
        void * NextToFree; // Size=8 Offset=8
    };
    void* Lock; // Size=8 Offset=16
    UCHAR TypeIndex; // Size=1 Offset=24
    union
    {
        UCHAR TraceFlags; // Size=1 Offset=25
        struct
        {
            UCHAR DbgRefTrace : 1; // Size=1 Offset=25 BitOffset=0 BitCount=1
            UCHAR DbgTracePermanent : 1; // Size=1 Offset=25 BitOffset=1 BitCount=1
        };
    };
    UCHAR InfoMask; // Size=1 Offset=26
    union
    {
        UCHAR Flags; // Size=1 Offset=27
        struct
        {
            UCHAR NewObject : 1; // Size=1 Offset=27 BitOffset=0 BitCount=1
            UCHAR KernelObject : 1; // Size=1 Offset=27 BitOffset=1 BitCount=1
            UCHAR KernelOnlyAccess : 1; // Size=1 Offset=27 BitOffset=2 BitCount=1
            UCHAR ExclusiveObject : 1; // Size=1 Offset=27 BitOffset=3 BitCount=1
            UCHAR PermanentObject : 1; // Size=1 Offset=27 BitOffset=4 BitCount=1
            UCHAR DefaultSecurityQuota : 1; // Size=1 Offset=27 BitOffset=5 BitCount=1
            UCHAR SingleHandleEntry : 1; // Size=1 Offset=27 BitOffset=6 BitCount=1
            UCHAR DeletedInline : 1; // Size=1 Offset=27 BitOffset=7 BitCount=1
        };
    };
    ULONG Spare; // Size=4 Offset=28
    union
    {
        struct _OBJECT_CREATE_INFORMATION * ObjectCreateInfo; // Size=8 Offset=32
        void * QuotaBlockCharged; // Size=8 Offset=32
    };
    void * SecurityDescriptor; // Size=8 Offset=40
    struct _QUAD Body; // Size=8 Offset=48
} OBJECT_HEADER, *POBJECT_HEADER;

typedef struct _MEMORY_BASIC_INFORMATION_EX
{
    PVOID BaseAddress;
    PVOID AllocationBase;
    ULONG AllocationProtect;
    SIZE_T RegionSize;
    ULONG State;
    ULONG Protect;
    ULONG Type;
} MEMORY_BASIC_INFORMATION_EX, *PMEMORY_BASIC_INFORMATION_EX;

typedef struct _SYSTEM_CALL_COUNT_INFORMATION
{
    ULONG Length;
    ULONG NumberOfTables;
    ULONG limits[2];
} SYSTEM_CALL_COUNT_INFORMATION, *PSYSTEM_CALL_COUNT_INFORMATION;

typedef struct _SYSTEM_THREAD_INFORMATION
{
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER CreateTime;
    ULONG WaitTime;
    PVOID StartAddress;
    CLIENT_ID ClientId;
    KPRIORITY Priority;
    LONG BasePriority;
    ULONG ContextSwitches;
    ULONG ThreadState;
    KWAIT_REASON WaitReason;
}SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;

typedef struct _THREAD_BASIC_INFORMATION
{
    NTSTATUS ExitStatus;
    PVOID TebBaseAddress;
    CLIENT_ID ClientId;
    ULONG_PTR AffinityMask;
    LONG Priority;
    LONG BasePriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

typedef struct _SYSTEM_PROCESS_INFO
{
    ULONG NextEntryOffset;
    ULONG NumberOfThreads;
    LARGE_INTEGER WorkingSetPrivateSize;
    ULONG HardFaultCount;
    ULONG NumberOfThreadsHighWatermark;
    ULONGLONG CycleTime;
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER KernelTime;
    UNICODE_STRING ImageName;
    KPRIORITY BasePriority;
    HANDLE UniqueProcessId;
    HANDLE InheritedFromUniqueProcessId;
    ULONG HandleCount;
    ULONG SessionId;
    ULONG_PTR UniqueProcessKey;
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivatePageCount;
    LARGE_INTEGER ReadOperationCount;
    LARGE_INTEGER WriteOperationCount;
    LARGE_INTEGER OtherOperationCount;
    LARGE_INTEGER ReadTransferCount;
    LARGE_INTEGER WriteTransferCount;
    LARGE_INTEGER OtherTransferCount;
    SYSTEM_THREAD_INFORMATION Threads[1];
}SYSTEM_PROCESS_INFO, *PSYSTEM_PROCESS_INFO;

#pragma warning(disable : 4214)
typedef struct _MMPTE_HARDWARE64
{
    ULONGLONG Valid : 1;
    ULONGLONG Dirty1 : 1;
    ULONGLONG Owner : 1;
    ULONGLONG WriteThrough : 1;
    ULONGLONG CacheDisable : 1;
    ULONGLONG Accessed : 1;
    ULONGLONG Dirty : 1;
    ULONGLONG LargePage : 1;
    ULONGLONG Global : 1;
    ULONGLONG CopyOnWrite : 1;
    ULONGLONG Unused : 1;
    ULONGLONG Write : 1;
    ULONGLONG PageFrameNumber : 36;
    ULONGLONG reserved1 : 4;
    ULONGLONG SoftwareWsIndex : 11;
    ULONGLONG NoExecute : 1;
} MMPTE_HARDWARE64, *PMMPTE_HARDWARE64;

typedef struct _MMPTE
{
    union
    {
        ULONG_PTR Long;
        MMPTE_HARDWARE64 Hard;
    } u;
} MMPTE;
typedef MMPTE *PMMPTE;

#pragma warning(default : 4214)

typedef struct _NT_PROC_THREAD_ATTRIBUTE_ENTRY
{
    ULONG Attribute;    // PROC_THREAD_ATTRIBUTE_XXX
    SIZE_T Size;
    ULONG_PTR Value;
    ULONG Unknown;
} NT_PROC_THREAD_ATTRIBUTE_ENTRY, *NT_PPROC_THREAD_ATTRIBUTE_ENTRY;

typedef struct _NT_PROC_THREAD_ATTRIBUTE_LIST
{
    ULONG Length;
    NT_PROC_THREAD_ATTRIBUTE_ENTRY Entry[1];
} NT_PROC_THREAD_ATTRIBUTE_LIST, *PNT_PROC_THREAD_ATTRIBUTE_LIST;


typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
    HANDLE Section;         // Not filled in
    PVOID MappedBase;
    PVOID ImageBase;
    ULONG ImageSize;
    ULONG Flags;
    USHORT LoadOrderIndex;
    USHORT InitOrderIndex;
    USHORT LoadCount;
    USHORT OffsetToFileName;
    UCHAR  FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, *PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES
{
    ULONG NumberOfModules;
    RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, *PRTL_PROCESS_MODULES;

#pragma warning(disable : 4214)
typedef union _MEMORY_WORKING_SET_EX_BLOCK
{
    ULONG_PTR Flags;
    struct
    {
        ULONG_PTR Valid : 1;
        ULONG_PTR ShareCount : 3;
        ULONG_PTR Win32Protection : 11;
        ULONG_PTR Shared : 1;
        ULONG_PTR Node : 6;
        ULONG_PTR Locked : 1;
        ULONG_PTR LargePage : 1;
        ULONG_PTR Reserved : 7;
        ULONG_PTR Bad : 1;

    #if defined(_WIN64)
        ULONG_PTR ReservedUlong : 32;
    #endif
    };
} MEMORY_WORKING_SET_EX_BLOCK, *PMEMORY_WORKING_SET_EX_BLOCK;

typedef struct _MEMORY_WORKING_SET_EX_INFORMATION
{
    PVOID VirtualAddress;
    MEMORY_WORKING_SET_EX_BLOCK VirtualAttributes;
} MEMORY_WORKING_SET_EX_INFORMATION, *PMEMORY_WORKING_SET_EX_INFORMATION;

typedef struct _PEB_LDR_DATA
{
    ULONG Length;
    UCHAR Initialized;
    PVOID SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _LDR_DATA_TABLE_ENTRY
{
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderLinks;
    LIST_ENTRY InInitializationOrderLinks;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    ULONG Flags;
    USHORT LoadCount;
    USHORT TlsIndex;
    LIST_ENTRY HashLinks;
    ULONG TimeDateStamp;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _CURDIR
{
    UNICODE_STRING DosPath;
    HANDLE Handle;
} CURDIR, *PCURDIR;

typedef struct _CURDIR32
{
    UNICODE_STRING32 DosPath;
    ULONG Handle;
} CURDIR32, *PCURDIR32;

typedef struct _RTL_DRIVE_LETTER_CURDIR
{
    USHORT  Flags;
    USHORT  Length;
    ULONG   TimeStamp;
    STRING  DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS
{
    ULONG MaximumLength;
    ULONG Length;
    ULONG Flags;
    ULONG DebugFlags;
    HANDLE ConsoleHandle;
    ULONG ConsoleFlags;
    HANDLE StandardInput;
    HANDLE StandardOutput;
    HANDLE StandardError;
    CURDIR CurrentDirectory;
    UNICODE_STRING DllPath;
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
    PVOID Environment;
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING WindowTitle;
    UNICODE_STRING DesktopInfo;
    UNICODE_STRING ShellInfo;
    UNICODE_STRING RuntimeData;
    RTL_DRIVE_LETTER_CURDIR CurrentDirectories[RTL_MAX_DRIVE_LETTERS];
    ULONG EnvironmentSize;
    ULONG EnvironmentVersion;
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef struct _RTL_USER_PROCESS_PARAMETERS32
{
    ULONG MaximumLength;
    ULONG Length;
    ULONG Flags;
    ULONG DebugFlags;
    ULONG ConsoleHandle;
    ULONG ConsoleFlags;
    ULONG StandardInput;
    ULONG StandardOutput;
    ULONG StandardError;
    CURDIR32 CurrentDirectory;
    UNICODE_STRING32 DllPath;
    UNICODE_STRING32 ImagePathName;
    UNICODE_STRING32 CommandLine;
    ULONG Environment;
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING32 WindowTitle;
    UNICODE_STRING32 DesktopInfo;
    UNICODE_STRING32 ShellInfo;
    UNICODE_STRING32 RuntimeData;
    RTL_DRIVE_LETTER_CURDIR CurrentDirectories[RTL_MAX_DRIVE_LETTERS];
    ULONG EnvironmentSize;
    ULONG EnvironmentVersion;
} RTL_USER_PROCESS_PARAMETERS32, *PRTL_USER_PROCESS_PARAMETERS32;

typedef struct _PEB
{
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;
    union
    {
        BOOLEAN BitField;
        struct
        {
            BOOLEAN ImageUsesLargePages : 1;
            BOOLEAN IsProtectedProcess : 1;
            BOOLEAN IsLegacyProcess : 1;
            BOOLEAN IsImageDynamicallyRelocated : 1;
            BOOLEAN SkipPatchingUser32Forwarders : 1;
            BOOLEAN IsPackagedProcess : 1;
            BOOLEAN IsAppContainer : 1;
            BOOLEAN IsProtectedProcessLight : 1;
            BOOLEAN SpareBits : 1;
        };
    };
    HANDLE Mutant;
    PVOID ImageBaseAddress;
    PPEB_LDR_DATA Ldr;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
    PVOID SubSystemData;
    PVOID ProcessHeap;
    PVOID FastPebLock;
    PVOID AtlThunkSListPtr;
    PVOID IFEOKey;
    PVOID CrossProcessFlags;
    PVOID UserSharedInfoPtr;
    ULONG SystemReserved;
    ULONG AtlThunkSListPtr32;
    PVOID ApiSetMap;
    ULONG TlsExpansionCounter;
    ULONG Padding2;
    PVOID TlsBitmap;
    ULONG TlsBitmapBits[2];
    PVOID ReadOnlySharedMemoryBase;
    PVOID SparePvoid0;
    PVOID* ReadOnlyStaticServerData;
    PVOID AnsiCodePageData;
    PVOID OemCodePageData;
    PVOID UnicodeCaseTableData;
    ULONG NumberOfProcessors;
    ULONG NtGlobalFlag;
} PEB, *PPEB;

typedef struct _PEB_LDR_DATA32
{
    ULONG Length;
    UCHAR Initialized;
    ULONG SsHandle;
    LIST_ENTRY32 InLoadOrderModuleList;
    LIST_ENTRY32 InMemoryOrderModuleList;
    LIST_ENTRY32 InInitializationOrderModuleList;
} PEB_LDR_DATA32, *PPEB_LDR_DATA32;

typedef struct _LDR_DATA_TABLE_ENTRY32
{
    LIST_ENTRY32 InLoadOrderLinks;
    LIST_ENTRY32 InMemoryOrderLinks;
    LIST_ENTRY32 InInitializationOrderLinks;
    ULONG DllBase;
    ULONG EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING32 FullDllName;
    UNICODE_STRING32 BaseDllName;
    ULONG Flags;
    USHORT LoadCount;
    USHORT TlsIndex;
    LIST_ENTRY32 HashLinks;
    ULONG TimeDateStamp;
} LDR_DATA_TABLE_ENTRY32, *PLDR_DATA_TABLE_ENTRY32;

typedef struct _PEB32
{
    UCHAR InheritedAddressSpace;
    UCHAR ReadImageFileExecOptions;
    UCHAR BeingDebugged;
    UCHAR BitField;
    ULONG Mutant;
    ULONG ImageBaseAddress;
    ULONG Ldr;
    ULONG ProcessParameters;
    ULONG SubSystemData;
    ULONG ProcessHeap;
    ULONG FastPebLock;
    ULONG AtlThunkSListPtr;
    ULONG IFEOKey;
    ULONG CrossProcessFlags;
    ULONG UserSharedInfoPtr;
    ULONG SystemReserved;
    ULONG AtlThunkSListPtr32;
    ULONG ApiSetMap;
} PEB32, *PPEB32;

typedef struct _WOW64_PROCESS
{
    PPEB32 Wow64;
} WOW64_PROCESS, *PWOW64_PROCESS;

typedef union _WOW64_APC_CONTEXT
{
    struct
    {
        ULONG Apc32BitContext;
        ULONG Apc32BitRoutine;
    };

    PVOID Apc64BitContext;

} WOW64_APC_CONTEXT, *PWOW64_APC_CONTEXT;


typedef struct _NON_PAGED_DEBUG_INFO
{
    USHORT      Signature;
    USHORT      Flags;
    ULONG       Size;
    USHORT      Machine;
    USHORT      Characteristics;
    ULONG       TimeDateStamp;
    ULONG       CheckSum;
    ULONG       SizeOfImage;
    ULONGLONG   ImageBase;
} NON_PAGED_DEBUG_INFO, *PNON_PAGED_DEBUG_INFO;

typedef struct _KLDR_DATA_TABLE_ENTRY
{
    LIST_ENTRY InLoadOrderLinks;
    PVOID ExceptionTable;
    ULONG ExceptionTableSize;
    // ULONG padding on IA64
    PVOID GpValue;
    PNON_PAGED_DEBUG_INFO NonPagedDebugInfo;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    ULONG Flags;
    USHORT LoadCount;
    USHORT __Unused5;
    PVOID SectionPointer;
    ULONG CheckSum;
    // ULONG padding on IA64
    PVOID LoadedImports;
    PVOID PatchInformation;
} KLDR_DATA_TABLE_ENTRY, *PKLDR_DATA_TABLE_ENTRY;


#define ACTCTX_FLAG_PROCESSOR_ARCHITECTURE_VALID    (0x00000001)
#define ACTCTX_FLAG_LANGID_VALID                    (0x00000002)
#define ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID        (0x00000004)
#define ACTCTX_FLAG_RESOURCE_NAME_VALID             (0x00000008)
#define ACTCTX_FLAG_SET_PROCESS_DEFAULT             (0x00000010)
#define ACTCTX_FLAG_APPLICATION_NAME_VALID          (0x00000020)
#define ACTCTX_FLAG_SOURCE_IS_ASSEMBLYREF           (0x00000040)
#define ACTCTX_FLAG_HMODULE_VALID                   (0x00000080)

typedef struct tagACTCTXW
{
    ULONG  cbSize;
    ULONG  dwFlags;
    PWCH   lpSource;
    USHORT wProcessorArchitecture;
    USHORT wLangId;
    PWCH   lpAssemblyDirectory;
    PWCH   lpResourceName;
    PWCH   lpApplicationName;
    PVOID  hModule;
} ACTCTXW, *PACTCTXW;

typedef struct tagACTCTXW32
{
    ULONG  cbSize;
    ULONG  dwFlags;
    ULONG  lpSource;
    USHORT wProcessorArchitecture;
    USHORT wLangId;
    ULONG  lpAssemblyDirectory;
    ULONG  lpResourceName;
    ULONG  lpApplicationName;
    ULONG  hModule;
} ACTCTXW32, *PACTCTXW32;

//
// Firmware Boot Entry
//
typedef struct _BOOT_ENTRY
{
    ULONG Version;
    ULONG Length;
    ULONG Id;
    ULONG Attributes;
    ULONG FriendlyNameOffset;
    ULONG BootFilePathOffset;
    ULONG OsOptionsLength;
    CHAR OsOptions[1];
} BOOT_ENTRY, *PBOOT_ENTRY;

//
// Firmware Boot File Path
//
typedef struct _FILE_PATH
{
    ULONG Version;
    ULONG Length;
    ULONG Type;
    CHAR FilePath[1];
} FILE_PATH, *PFILE_PATH;

//
// Firmware Boot Options
//
typedef struct _BOOT_OPTIONS
{
    ULONG Version;
    ULONG Length;
    ULONG Timeout;
    ULONG CurrentBootEntryId;
    ULONG NextBootEntryId;
    WCHAR HeadlessRedirection[1];
} BOOT_OPTIONS, *PBOOT_OPTIONS;

//
// Firmware Driver Entry
//
typedef struct _EFI_DRIVER_ENTRY
{
    ULONG Version;
    ULONG Length;
    ULONG Id;
    ULONG Attributes;
    ULONG FriendlyNameOffset;
    ULONG DriverFilePathOffset;
} EFI_DRIVER_ENTRY, *PEFI_DRIVER_ENTRY;

//
// System Debugger Types
//
typedef struct _SYSDBG_PHYSICAL
{
    PHYSICAL_ADDRESS Address;
    PVOID Buffer;
    ULONG Request;
} SYSDBG_PHYSICAL, *PSYSDBG_PHYSICAL;

typedef struct _SYSDBG_VIRTUAL
{
    PVOID Address;
    PVOID Buffer;
    ULONG Request;
} SYSDBG_VIRTUAL, *PSYSDBG_VIRTUAL;

typedef struct _SYSDBG_CONTROL_SPACE
{
    ULONGLONG Address;
    PVOID Buffer;
    ULONG Request;
    ULONG Processor;
} SYSDBG_CONTROL_SPACE, *PSYSDBG_CONTROL_SPACE;

typedef struct _SYSDBG_IO_SPACE
{
    ULONGLONG Address;
    PVOID Buffer;
    ULONG Request;
    INTERFACE_TYPE InterfaceType;
    ULONG BusNumber;
    ULONG AddressSpace;
} SYSDBG_IO_SPACE, *PSYSDBG_IO_SPACE;

typedef struct _SYSDBG_BUS_DATA
{
    ULONG Address;
    PVOID Buffer;
    ULONG Request;
    BUS_DATA_TYPE BusDataType;
    ULONG BusNumber;
    ULONG SlotNumber;
} SYSDBG_BUS_DATA, *PSYSDBG_BUS_DATA;

typedef struct _SYSDBG_MSR
{
    ULONG Address;
    ULONGLONG Data;
} SYSDBG_MSR, *PSYSDBG_MSR;

typedef struct _SYSDBG_TRIAGE_DUMP
{
    ULONG Flags;
    ULONG BugCheckCode;
    ULONG_PTR BugCheckParam1;
    ULONG_PTR BugCheckParam2;
    ULONG_PTR BugCheckParam3;
    ULONG_PTR BugCheckParam4;
    ULONG ProcessHandles;
    ULONG ThreadHandles;
    PHANDLE Handles;
} SYSDBG_TRIAGE_DUMP, *PSYSDBG_TRIAGE_DUMP;

//
// KD Structures
//
typedef struct _KD_SYMBOLS_INFO
{
    PVOID BaseOfDll;
    ULONG_PTR ProcessId;
    ULONG CheckSum;
    ULONG SizeOfImage;
} KD_SYMBOLS_INFO, *PKD_SYMBOLS_INFO;

//
// Initial TEB
//
typedef struct _INITIAL_TEB
{
    PVOID PreviousStackBase;
    PVOID PreviousStackLimit;
    PVOID StackBase;
    PVOID StackLimit;
    PVOID AllocatedStackBase;
} INITIAL_TEB, *PINITIAL_TEB;

typedef struct _JOB_SET_ARRAY
{
    HANDLE JobHandle;
    DWORD MemberLevel;
    DWORD Flags;
} JOB_SET_ARRAY, *PJOB_SET_ARRAY;

typedef struct _SYSTEM_BASIC_INFORMATION
{
    ULONG Reserved;
    ULONG TimerResolution;
    ULONG PageSize;
    ULONG NumberOfPhysicalPages;
    ULONG LowestPhysicalPageNumber;
    ULONG HighestPhysicalPageNumber;
    ULONG AllocationGranularity;
    ULONG MinimumUserModeAddress;
    ULONG MaximumUserModeAddress;
    KAFFINITY ActiveProcessorsAffinityMask;
    CCHAR NumberOfProcessors;
} SYSTEM_BASIC_INFORMATION, *PSYSTEM_BASIC_INFORMATION;

typedef struct _HANDLE_TABLE
{
    ULONG       NextHandleNeedingPool;
    LONG        ExtraInfoPages;
    ULONG_PTR   TableCode;
    PEPROCESS   QuotaProcess;
    LIST_ENTRY  HandleTableList;
    ULONG       UniqueProcessId;
    //
    // ...
    //
} HANDLE_TABLE, *PHANDLE_TABLE;

typedef struct _OBJECT_TYPE
{
    LIST_ENTRY      TypeList;
    UNICODE_STRING  Name;
    PVOID           DefaultObject;
    UCHAR           Index;
    ULONG           TotalNumberOfObjects;
    ULONG           TotalNumberOfHandles;
    //
    // More stuff here
    //
} OBJECT_TYPE, *POBJECT_TYPE;

#pragma warning(default : 4214 4201)