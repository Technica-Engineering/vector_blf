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

#include <array>
#include <vector>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief AFDX_FRAME
 *
 * AFDX frame.
 */
class VECTOR_BLF_EXPORT AfdxFrame final : public ObjectHeader
{
public:
    AfdxFrame();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /**
     * Ethernet (MAC) address of source computer
     * (network byte order).
     */
    std::array<BYTE, 6> sourceAddress;

    /**
     * The channel of the frame.
     */
    WORD channel;

    /**
     * Ethernet (MAC) address of target computer
     * (network byte order).
     */
    std::array<BYTE, 6> destinationAddress;

    /** enumeration for dir */
    enum Dir : WORD
    {
        /** Receive */
        Rx = 0,

        /** Transmit */
        Tx = 1,

        /** Transmit Request */
        TxRq = 2
    };

    /**
     * @brief Direction flag
     */
    WORD dir;

    /**
     * EtherType which indicates protocol for
     * Ethernet payload data
     *
     * See Ethernet standard specification for valid
     * values.
     */
    WORD type;

    /**
     * TPID when VLAN tag valid, zweo when no
     * VLAN. See Ethernet stnadard specification.
     */
    WORD tpid;

    /**
     * TCI when VLAND tag valid, zero when no
     * VLAN. See Ethernet standard specification.
     */
    WORD tci;

    /**
     * Channel number of the underlying Ethernet
     * interface, where the frame originated from.
     */
    BYTE ethChannel;

    /** reserved */
    BYTE reservedAfdxFrame1;

    /**
     * Status- and error flags as:
     *
     * - Bit 0: Frame from line-B
     * - Bit 1: Packet is redundant
     * - Bit 2: Frame is a fragment only
     * - Bit 3: Frame is already reassembled
     * - Bit 4: Packet is not a valid AFDX frame
     * - Bit 5: AFDX-SequenceNo is invalud
     * - Bit 6: Redundancy timeout violated
     * - Bit 7: Redundancy error encountered
     * - Bit 8: A / B interface mismatch
     * - Bit 11: Fragmentation error
     */
    WORD afdxFlags;

    /** reserved */
    WORD reservedAfdxFrame2;

    /**
     * Time period since last received frame on this
     * virtual link in micro-seconds
     */
    ULONG bagUsec;

    /**
     * @brief Number of valid payLoad bytes
     *
     * Length of Ethernet payload data in bytes. Max.
     * 1500 Bytes (without Ethernet header)
     */
    WORD payLoadLength;

    /** reserved */
    WORD reservedAfdxFrame3;

    /** reserved */
    DWORD reservedAfdxFrame4;

    /**
     * @brief Ethernet payload data
     *
     * Ethernet payload data (without Ethernet
     * header).
     *
     * Max 1582 (1600 packet length - 18 header) data bytes per frame
     */
    std::vector<uint8_t> payLoad;
};

}
}
