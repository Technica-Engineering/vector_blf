/*
 * Copyright (C) 2013 Tobias Lorenz.
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

#include "platform.h"

#include <cstdint>

namespace Vector {
namespace BLF {

/** unsigned 8 bit */
typedef uint8_t BYTE;

/** unsigned 16 bit */
typedef uint16_t WORD;

/** signed 16 bit */
typedef int16_t SHORT;

/** unsigned 32 bit */
typedef uint32_t DWORD;

/** unsigned 32 bit */
typedef uint32_t ULONG;

/** signed 32 bit */
typedef int32_t LONG;

/** unsigned 64 bit */
typedef uint64_t ULONGLONG;

/** unsigned 64 bit */
typedef uint64_t UINT64;

/** signed 64 bit */
typedef int64_t LONGLONG;

/** double */
typedef double DOUBLE;

/** color reference */
typedef uint32_t COLORREF;

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
