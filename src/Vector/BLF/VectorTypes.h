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

namespace Vector {
namespace BLF {

/* unsigned 8 bit */
typedef unsigned char BYTE;

/* unsigned 16 bit */
typedef unsigned short WORD;

/* signed 16 bit */
typedef short SHORT;

/* unsigned 32 bit */
typedef unsigned long DWORD;
typedef unsigned long ULONG;

/* signed 32 bit */
typedef long LONG;

/* unsigned 64 bit */
typedef unsigned long long ULONGLONG;
typedef unsigned long long UINT64;

/* signed 64 bit */
typedef long long LONGLONG;

/* double */
typedef double DOUBLE;

/* color reference */
typedef unsigned long COLORREF;

/* system time */
struct SYSTEMTIME {
  WORD year;
  WORD month;
  WORD dayOfWeek;
  WORD day;
  WORD hour;
  WORD minute;
  WORD second;
  WORD milliseconds;
};

}
}
