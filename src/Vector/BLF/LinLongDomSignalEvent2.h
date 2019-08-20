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

#include <Vector/BLF/platform.h>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/LinBusEvent.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief LIN_LONG_DOM_SIG2
 *
 * This event occurs when a LIN channel remains in the dominant state for a time, which
 * is longer than a valid wakeup frame and it is not a valid sync break.
 */
class VECTOR_BLF_EXPORT LinLongDomSignalEvent2 final : public ObjectHeader, public LinBusEvent
{
public:
    LinLongDomSignalEvent2();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /**
     * One dominant signal reported with multiple
     * events (at least 2). This field indicate the order
     * of this event in a sequence:
     *   - 0: Signal just detected
     *   - 1: Signal continuation
     *   - 2: Signal finished
     */
    BYTE type {};

    /** reserved */
    BYTE reservedLinLongDomSignalEvent1 {};

    /** reserved */
    WORD reservedLinLongDomSignalEvent2 {};

    /** reserved */
    DWORD reservedLinLongDomSignalEvent3 {};

    /**
     * Current total signal length [in nanoseconds]
     */
    ULONGLONG length {};
};

}
}
