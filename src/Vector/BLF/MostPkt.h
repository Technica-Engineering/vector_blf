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
#include <vector>

#include "AbstractFile.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief MOST_PKT
 *
 * This event structure was never and should never be used. Use MostPkt2
 * instead.
 */
class VECTOR_BLF_EXPORT MostPkt : public ObjectHeader
{
public:
    MostPkt();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Application channel
     */
    WORD channel;

    /**
     * Direction of message events:
     *   - 0: Rx (received)
     *   - 1: Tx (transmit receipt)
     *   - 2: Tx Request (transmit request)
     */
    BYTE dir;

    /** reserved */
    BYTE reserved1;

    /**
     * Source address
     */
    DWORD sourceAdr;

    /**
     * Target address
     */
    DWORD destAdr;

    /**
     * Arbitration byte
     */
    BYTE arbitration;

    /**
     * Obsolete member; read/write 0
     */
    BYTE timeRes;

    /**
     * Number of quadlets
     */
    BYTE quadsToFollow;

    /** reserved */
    BYTE reserved2;

    /**
     * Cyclic Redundancy Check
     */
    WORD crc;

    /**
     * Priority
     */
    BYTE priority;

    /**
     * @brief Tranfer type
     *
     * Message-like events can either be recorded through the MOST transceiver chip or through a
     * separate network spy.
     *   - 1: Node
     *     MOST transceiver reported the message (either due to a successful reception or
     *     as acknowledgment for a transmit request).
     *   - 2: Spy
     *     Message was reported by the network spy. The Spy sees all messages
     *     independently of the desti-nation address.
     */
    BYTE transferType;

    /**
     * Transmission state
     *   - 0 for Rx
     *   - 0x40 for TxOk (transmit request)
     */
    BYTE state;

    /** reserved */
    std::array<BYTE, 3> reserved3;

    /**
     * @brief length of variable data in bytes
     *
     * Length of variable data in bytes (1014 max)
     */
    DWORD pktDataLength;

    /** reserved */
    std::array<BYTE, 4> reserved4;

    /**
     * @brief variable data
     *
     * Variable data
     */
    std::vector<uint8_t> pktData;
};

}
}
