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

#include <array>

#include "AbstractFile.h"
#include "LinBusEvent.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_LONG_DOM_SIG2
 *
 * This event occurs when a LIN channel remains in the dominant state for a time, which
 * is longer than a valid wakeup frame and it is not a valid sync break.
 */
class VECTOR_BLF_EXPORT LinLongDomSignalEvent2 : public ObjectHeader, public LinBusEvent
{
public:
    LinLongDomSignalEvent2();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * One dominant signal reported with multiple
     * events (at least 2). This field indicate the order
     * of this event in a sequence:
     *   - 0: Signal just detected
     *   - 1: Signal continuation
     *   - 2: Signal finished
     */
    BYTE type;

    /** reserved */
    std::array<BYTE, 7> reserved;

    /**
     * Current total signal length [in nanoseconds]
     */
    ULONGLONG length;
};

}
}
