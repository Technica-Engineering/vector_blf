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
#include "ObjectHeader2.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief MOST_50_PKT
 *
 * Message on MOST50 Packet Data Channel.
 */
class VECTOR_BLF_EXPORT Most50Pkt : public ObjectHeader2
{
public:
    Most50Pkt();

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
     * @brief direction: 0: Rx; 1: Tx; 2: TxRequest
     *
     * Direction of message events:
     *   - 0: Rx (received)
     *   - 1: Tx (transmit receipt)
     *   - 2: Tx Request (transmit request)
     */
    BYTE dir;

    /** reserved */
    BYTE reserved1;

    /**
     * @brief source address
     *
     * Source address
     */
    DWORD sourceAdr;

    /**
     * @brief target address
     *
     * Target address
     */
    DWORD destAdr;

    /**
     * @brief Tranfer Type
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
     * @brief transmission status
     *
     * Transmission states of MOST50/150 messages and packets.
     *   - Bit 0:
     *     Meaning:
     *       - 0: bus inactive
     *       - 1: bus active
     *     Restriction:
     *       - only for Dir = Rx or mTransferType = Spy
     *   - Bit 4:
     *     Meaning:
     *       - 1: acknowledged (Ack)
     *     Restriction
     *       - only for mTransferType = Node and Dir =
     *         Tx (always set to 1 for Rx messages in node
     *         mode)
     *   - Bit 5:
     *     Meaning:
     *       - 1: not acknowledged (NAck)
     *     Restriction:
     *       - only for Dir = Tx
     *   - Bit 6:
     *     Meaning: Send result:
     *       - 0: Transmission error (TxF)
     *       - 1: OK
     *     Restriction:
     *       - only for Dir = Tx
     *       - only for mTransferType = Node
     */
    BYTE state;

    /**
     * @brief acknowledge code
     *
     * AckNack holds the transmit status of a control message (see Transmit Status Register of OS8104
     * for MOST25).
     *   - Bit 0:
     *     Meaning:
     *       - 1: no response (NoResp)
     *     Restriction:
     *       - only for Dir = Tx or spy messages
     *   - Bit 1:
     *     Meaning:
     *       - 1: valid receipt (Valid)
     *     Restriction:
     *       - only for Dir = Tx or spy messages
     *   - Bit 2:
     *     Meaning:
     *       - 1: CRC Error (CRCError)
     *     Restriction:
     *       - only for Dir = Tx or spy messages
     *   - Bit 3:
     *     Meaning:
     *       - 1: receive buffer full (RxBufFull)
     *     Restriction:
     *       - only for Dir = Tx or spy messages
     *   - Bit 4:
     *     Meaning:
     *       - 1: acknowledged (Ack)
     *     Restriction:
     *       - only for Dir = Tx or spy messages (always
     *         set to 1 for Rx messages in node mode)
     *   - Bit 5:
     *     Meaning:
     *       - 1: negative acknowledge (NAck)
     *     Restriction:
     *       - only for Dir = Tx or spy messages
     */
    BYTE ackNack;

    /** reserved */
    BYTE reserved2;

    /**
     * @brief Cyclic Redundancy Check
     *
     * Cyclic Redundancy Check
     */
    DWORD crc;

    /** reserved */
    BYTE reserved3;

    /** reserved */
    BYTE reserved4;

    /**
     * @brief priority of the message
     *
     * Priority
     */
    BYTE priority;

    /** reserved */
    BYTE reserved5;

    /**
     * @brief length of variable data in bytes (1014 max)
     *
     * Length of variable data in bytes (1014 max)
     */
    DWORD pktDataLength;

    /** reserved */
    std::array<BYTE, 4> reserved6;

    /**
     * @brief variable data
     *
     * Variable data
     */
    std::vector<uint8_t> pktData;
};

}
}
