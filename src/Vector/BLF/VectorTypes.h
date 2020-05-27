/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
 * Contact: tobias.lorenz@gmx.net
 *
 * This file is part of Tobias Lorenz's Toolkit.
 *
 * Commercial License Usage
 * Licensees holding valid commercial licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and Tobias Lorenz.
 *
 * GNU General Public License 3.0 Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 */

#pragma once

#include <Vector/BLF/platform.h>

#include <cstdint>

namespace Vector {
namespace BLF {

/** unsigned 8 bit */
using BYTE = uint8_t;

/** unsigned 16 bit */
using WORD = uint16_t;
using USHORT = uint16_t;

/** signed 16 bit */
using SHORT = int16_t;

/** unsigned 32 bit */
using DWORD = uint32_t;

/** unsigned 32 bit */
using ULONG = uint32_t;

/** signed 32 bit */
using LONG = int32_t;

/** unsigned 64 bit */
using ULONGLONG = uint64_t;

/** unsigned 64 bit */
using UINT64 = uint64_t;

/** signed 64 bit */
using LONGLONG = int64_t;

/** double */
using DOUBLE = double;

/** color reference */
using COLORREF = uint32_t;

/** system time */
struct SYSTEMTIME {
    /** year */
    WORD year;

    /** month */
    WORD month;

    /** day of week */
    WORD dayOfWeek;

    /** day */
    WORD day;

    /** hour */
    WORD hour;

    /** minute */
    WORD minute;

    /** second */
    WORD second;

    /** milliseconds */
    WORD milliseconds;
};

}
}
