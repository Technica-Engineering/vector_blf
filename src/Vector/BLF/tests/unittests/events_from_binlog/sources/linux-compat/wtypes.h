// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <cstdint>
#include <cstdlib>

/* boolean */
using BOOL = bool;

/* unsigned 8 bit */
using BYTE = uint8_t;

/* unsigned 16 bit */
using WORD = uint16_t;
using USHORT = uint16_t;

/* signed 16 bit */
using SHORT = int16_t;

/* unsigned 32 bit */
using DWORD = uint32_t;

/* unsigned 32 bit */
using ULONG = uint32_t;

/* signed 32 bit */
using LONG = int32_t;

/* unsigned 64 bit */
using ULONGLONG = uint64_t;

/* unsigned 64 bit */
using UINT64 = uint64_t;

/* signed 64 bit */
using LONGLONG = int64_t;

/* float */
using FLOAT = float;

/* double */
using DOUBLE = double;

/* color reference */
using COLORREF = uint32_t;

/* pointers */
using LPBYTE = BYTE *;
using LPSTR = char *;
using LPWSTR = wchar_t *;
using PLONGLONG = ULONGLONG *;
using LPCSTR = const char *;

/* handle */
using HANDLE = void *;
const HANDLE INVALID_HANDLE_VALUE = (HANDLE) - 1;

/** system time */
struct SYSTEMTIME {
    /** year */
    WORD wYear;

    /** month */
    WORD wMonth;

    /** day of week */
    WORD wDayOfWeek;

    /** day */
    WORD wDay;

    /** hour */
    WORD wHour;

    /** minute */
    WORD wMinute;

    /** second */
    WORD wSecond;

    /** milliseconds */
    WORD wMilliseconds;
};

using LPSYSTEMTIME = SYSTEMTIME *;

#define __stdcall
