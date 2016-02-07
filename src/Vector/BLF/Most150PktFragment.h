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
 * @brief MOST_150_PKT_FRAGMENT
 *
 * Partial transmitted message on MOST50 and MOST150 Packet Data Channel.
 */
class VECTOR_BLF_EXPORT Most150PktFragment : public ObjectHeader2 /* applied for MOST50 and MOST150 */
{
public:
    Most150PktFragment();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Application channel
     */
    WORD channel;

    /** reserved */
    BYTE reserved1;

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

    /**
     * @brief bitfield indicating which members have valid data
     *
     * If a bit in the mask is set, the corresponding data field has been seen on the bus.
     *   - Bit 0: 0x00000001: dataLenAnnounced
     *   - Bit 1: 0x00000002: sourceAdr
     *   - Bit 2: 0x00000004: destAdr
     *   - Bit 3: 0x00000008: ackNack
     *   - Bit 4: 0x00000010: pAck
     *   - Bit 5: 0x00000020: pIndex
     *   - Bit 6: 0x00000040: piority
     *   - Bit 7: 0x00000080: crc
     *   - Bit 8: 0x00000100: cAck
     *   - Bit 9: 0x00000200: sourceMacAdr
     *   - Bit 10: 0x00000400: destMacAdr
     *   - Bit 31: 0x80000000: 0: MOST150 fragment; 1: MOST50 fragment
     */
    DWORD validMask;

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
     * @brief a preemptive acknowledge code
     *
     * Pre-emptive acknowledge code
     *   - 0x00: No Response
     *   - 0x01: Buffer full
     *   - 0x04: OK
     */
    BYTE pAck;

    /**
     * @brief CRC acknowledge from the packet receiver(s) to the packet transmitter
     *
     * CRC acknowledge from the packet receiver(s) to
     * the packet transmitter
     *   - 0x00: No Response
     *   - 0x01: CRC error
     *   - 0x04: OK
     */
    BYTE cAck;

    /**
     * @brief priority of the message
     *
     * Priority (not used; write 0x00)
     */
    BYTE priority;

    /**
     * @brief packet index, increments per message on MOST
     *
     * Packet index, increments per message on MOST
     */
    BYTE pIndex;

    /**
     * @brief Cyclic Redundancy Check
     *
     * Cyclic Redundancy Check
     */
    DWORD crc;

    /**
     * @brief number of transmitted user data bytes
     *
     * Number of transmitted user data bytes. These
     * bytes were counted on bus.
     *
     * Note: The number of bytes saved in this event is
     * stored in mFirstDataLen.
     */
    DWORD dataLen;

    /**
     * @brief announced user data length at the start of the transmission
     *
     * Announced user data length at start of
     * transmission. In some cases (e.g. sending to an
     * invalid target address, receive buffer full of
     * target device) the transmission is terminated
     * before all data bytes have been sent. Then the
     * counted number of bytes on bus is less than the
     * announced data length (dataLen <
     * dataLenAnnonced). Due to rare and very
     * specific bit errors (degrade of end termination
     * byte) dataLen can also be greater than
     * dataLenAnnonced.
     */
    DWORD dataLenAnnounced;

    /**
     * @brief number of bytes in firstData
     *
     * Number of bytes stored in firstData (1524
     * max).
     *
     * Note: In order to limit the size of this event not
     * all counted bytes on bus will be stored in the
     * payload of the logging event.
     */
    DWORD firstDataLen;

    /** reserved */
    std::array<BYTE, 4> reserved2;

    /**
     * @brief variable data
     *
     * Variable data
     */
    std::vector<uint8_t> firstData;
};

}
}
