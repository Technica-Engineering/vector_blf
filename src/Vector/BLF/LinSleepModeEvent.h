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
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_SLEEP
 *
 * This info event occurs at the start of a measurement in order to report the initial state
 * of the LIN hardware and every time the mode (awake/asleep) of LIN hardware changes.
 */
class VECTOR_BLF_EXPORT LinSleepModeEvent : public ObjectHeader
{
public:
    LinSleepModeEvent();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Channel number where the event notified
     */
    WORD channel;

    /**
     * This value indicates the reason for an event.
     * Following values are possible:
     *   - 0: Start state
     *
     * Transition to Sleep mode
     *   - 1: Go-to-Sleep frame
     *   - 2: Bus Idle Timeout
     *   - 3: Silent SleepMode command (for shortening
     *     the BusIdle Timeout)
     *
     * Leaving Sleep mode:
     *   - 9: External Wakeup signal
     *   - 10: Internal Wakeup signal
     *   - 11: Bus traffic (can only occur if the LIN
     *     hardware does not have a Master function)
     *
     * LIN hardware does not go into Sleep mode in
     * spite of request to do so:
     *   - 18: Bus traffic (can only occur if the LIN
     *     hardware does not have a Master function)
     */
    BYTE reason;

    /** Bit values for flags */
    enum class Flags : BYTE {
        /** @brief LIN "was awake" */
        WasAwake = 0x01,

        /** @brief LIN "is awake" */
        IsAwake = 0x02,

        /** @brief LIN "external" */
        External = 0x04
    };

    /**
     * Bit mask with bit values as following:
     *
     * Bit 0 (LSB): Indicates the state of the LIN
     * hardware before this event occurred:
     *   - 1: Awake
     *   - 0: Asleep
     *
     * Bit 1: Indicates the current state of the LIN
     * hardware:
     *   - 1: Awake
     *   - 0: Asleep
     *
     * Bit 2: Indicates whether this event caused by
     * external or internal event:
     *   - 1: External event
     *   - 0: Internal event
     */
    BYTE flags;

    /** reserved */
    std::array<BYTE, 4> reserved;
};

}
}
