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

#include "VectorTypes.h"
#include "ObjectHeader2.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief MOST_150_ALLOCTAB
 */
class VECTOR_BLF_EXPORT Most150AllocTab : public ObjectHeader2 /* applied for MOST50 and MOST150 */
{
public:
    Most150AllocTab();

    WORD channel; /**< application channel */
    WORD eventModeFlags; /**< determines the data layout */
    WORD freeBytes; /**< number of free bytes after the operation */
    WORD length; /**< number of bytes in tableData*/
    LPBYTE tableData;
/*
    Data layout:
    if((mEventModeFlags & 0x0001) == 0)
      layout A: SLLLWWWWSLLLWWWWSLLLWWWW...
    if((mEventModeFlags & 0x0001) == 0x0001)
      layout B: SLLLWWWW<channels>SLLLWWWW<channels>SLLLWWWW<channels>...
    S:    status flags
          0x4: 1: new label (alloc)
          0x8: 1: this label has been removed (dealloc)
    LLL:  label number
    WWWW: label width
    <channels>: list of 16-bit channel numbers (size = label width)
    */
};

}
}
