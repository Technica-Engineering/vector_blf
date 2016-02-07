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
#include "LinDatabyteTimestampEvent.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_CRC_ERROR2
 *
 * Checksum error event occurring when Slave sends an incorrect checksum value for a
 * frame response that is otherwise correct.
 */
class VECTOR_BLF_EXPORT LinCrcError2 : public ObjectHeader, public LinDatabyteTimestampEvent
{
public:
    LinCrcError2();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief data bytes.
     *
     * Data byte values
     */
    std::array<BYTE, 8> data;

    /**
     * @brief checksum byte
     *
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

    /**
     * Slave Identifier in the Final State
     * Machine (obsolete)
     */
    BYTE fsmId;

    /**
     * State Identifier of a Slave in the
     * Final State Machine (obsolete)
     */
    BYTE fsmState;

    /**
     * @brief simulated frame
     *
     * Flag indicating whether this frame a
     * simulated one:
     *   - 0: real frame
     *   - 1: simulated frame
     */
    BYTE simulated;

    /** reserved */
    std::array<BYTE, 2> reserved1;

    /* the following variables are only available in Version 2 and above */

    /**
     * @brief Response baudrate of the event in bit/sec
     *
     * Event’s baudrate measured in
     * response [in bits/sec]
     */
    DWORD respBaudrate;

    /** reserved */
    std::array<BYTE, 4> reserved2;

    /* the following variables are only available in Version 3 and above */

    /**
     * @brief Exact baudrate of the header in bit/sec
     *
     * Event's baudrate
     * measured in header [in
     * bits/sec]
     */
    DOUBLE exactHeaderBaudrate;

    /**
     * @brief Early stop bit offset for UART timestamps in ns
     *
     * Early stop bit offset in
     * frame header for UART
     * timestamps [in ns]
     */
    DWORD earlyStopbitOffset;

    /**
     * @brief Early stop bit offset in frame response for UART timestamps in ns
     *
     * Early stop bit offset in
     * frame response for
     * UART timestamps [in ns]
     */
    DWORD earlyStopbitOffsetResponse;
};

}
}
