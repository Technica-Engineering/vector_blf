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
 * @brief LIN_MESSAGE
 *
 * @deprecated
 *
 * LIN frame received or transmitted on a LIN channel.
 */
class VECTOR_BLF_EXPORT LinMessage : public ObjectHeader
{
public:
    LinMessage();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Channel number where the frame sent/received.
     */
    WORD channel;

    /**
     * @brief LIN ID
     *
     * Frame identifier
     */
    BYTE id;

    /**
     * @brief LIN DLC
     *
     * Frame length
     */
    BYTE dlc;

    /**
     * Databyte values
     */
    std::array<BYTE, 8> data;

    /**
     * Slave Identifier in the Final State Machine
     * (obsolete)
     */
    BYTE fsmId;

    /**
     * State Identifier of a Slave in the Final State
     * Machine (obsolete)
     */
    BYTE fsmState;

    /**
     * Duration of the frame header [in bit times]
     */
    BYTE headerTime;

    /**
     * Duration of the entire frame [in bit times]
     */
    BYTE fullTime;

    /**
     * Checksum byte value
     */
    WORD crc;

    /**
     * @brief direction
     *
     * Direction of bus events
     *   - 0: Rx (received)
     *   - 1: Tx (transmit receipt)
     *   - 2: Tx Request (transmit request)
     */
    BYTE dir;

    /** reserved */
    BYTE reserved;
};

}
}
