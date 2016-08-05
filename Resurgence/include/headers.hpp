#pragma once

#pragma warning(disable: 4005) // macro redefinition
#pragma warning(disable: 4152) // nonstandard extension, function/data pointer conversion in expression
#pragma warning(disable: 4201) // nonstandard extension used : nameless struct/union
#pragma warning(disable: 6102) // Using %s from failed function call at line %u
#pragma warning(disable: 6320) // exception-filter expression is the constant EXCEPTION_EXECUTE_HANDLER

typedef long ntstatus_code;

#include <Windows.h>
#include <winioctl.h>
#include <ntstatus.h>
#include <strsafe.h>
#include <NtApi.hpp>
#include <cstdint>
#include <misc/Logging.hpp>

#if !defined PAGE_SIZE
#define PAGE_SIZE       0x1000
#endif

__forceinline ntstatus_code get_last_ntstatus()
{
    return NtCurrentTeb()->LastStatusValue;
}
__forceinline ntstatus_code set_last_ntstatus(ntstatus_code status)
{
    return NtCurrentTeb()->LastStatusValue = status;
}