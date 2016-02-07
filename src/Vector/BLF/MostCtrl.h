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
 * @brief MOST_CTRL
 *
 * Message on MOST 25 Control Channel; received or transmitted in node mode.
 */
class VECTOR_BLF_EXPORT MostCtrl : public ObjectHeader
{
public:
    MostCtrl();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Channel the message was sent or received.
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
     * 17 data bytes
     */
    std::array<BYTE, 17> msg;

    /** reserved */
    BYTE reserved2;

    /**
     * @brief Control message sub type
     *
     * Sub type of a MOST 25 Control message (see data sheet of OS8104 also).
     *   - 0: Normal
     *   - 1: RemoteRead
     *   - 2: RemoteWrite
     *   - 3: Alloc
     *   - 4: Dealloc
     *   - 5: GetSource
     *   - >5: not used so far
     */
    WORD rTyp;

    /**
     * @brief Addressing mode
     *
     * Addressing mode of MOST25 Control messages.
     *   - 0x00: Device (logical node address)
     *   - 0x10: Node position
     *   - 0x20: Broadcast
     *   - 0x30: Groupcast
     *   - 0xFF: Unknown
     */
    BYTE rTypAdr;

    /**
     * @brief Transmission state MOST25
     *
     * Transmission state of a MOST25 Control message.
     *   - Bit 0:
     *     Meaning:
     *     - 0: bus inactive
     *     - 1: bus active
     *     Restriction:
     *     - only for Dir = Rx (MOSTCtrl) or MOSTSpy
     *   - Bit 1:
     *     Meaning:
     *     - 1: unlock event during transmission (Unl)
     *     Restriction:
     *     - only for Dir = Rx (MOSTCtrl) or MOSTSpy
     *   - Bit 4:
     *     Meaning:
     *     - 1: acknowledged (Ack)
     *     Restriction:
     *     - only for Dir = Tx (always set to 1 for Rx messages in node mode)
     *   - Bit 5:
     *     Meaning:
     *     - 1: not acknowledged (NAck)
     *     Restriction:
     *     - only for Dir = Tx
     *   - Bit 6:
     *     Meaning:
     *     - Send result:
     *       - 0: Transmission error (TxF)
     *       - 1: OK
     *     Restriction:
     *     - only for Dir = Tx (MOSTCtrl)
     */
    BYTE state;

    /** reserved */
    BYTE reserved3;

    /**
     * @brief acknowledge bits
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
    std::array<BYTE, 4> reserved4;
};

}
}
