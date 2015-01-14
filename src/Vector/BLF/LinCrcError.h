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

#include "VectorTypes.h"
#include "ObjectHeader.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_CRC_ERROR
 *
 * @deprecated
 *
 * Checksum error event occurring when Slave sends an incorrect checksum value for a
 * frame response that is otherwise correct.
 */
class VECTOR_BLF_EXPORT LinCrcError : public ObjectHeader
{
public:
    LinCrcError();

    virtual char * parse(char * buffer);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Channel number where the event notified
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
    BYTE data[8];

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
