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
 * @brief FLEXRAY_MESSAGE
 *
 * FlexRay Message received or transmitted on a FlexRay channel.
 */
class VECTOR_BLF_EXPORT FlexRayV6Message : public ObjectHeader
{
public:
    FlexRayV6Message();

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
     * @brief dir flag (tx, rx)
     *
     * Direction Flags
     *   - 0 = Rx
     *   - 1 = Tx
     *   - 2 = Tx Request
     *   - 3 and 4 are for internal use only.
     */
    BYTE dir;

    /**
     * @brief additional time field in simulation
     *
     * Additional time field in simulation
     */
    BYTE lowTime;

    /**
     * @brief timestamp generated from xModule
     *
     * Timestamp generated from xModule
     */
    DWORD fpgaTick;

    /**
     * @brief overflow counter of the timestamp
     *
     * Overflow counter of the timestamp
     */
    DWORD fpgaTickOverflow;

    /**
     * @brief clientindex of send node
     *
     * Client index of send node
     */
    DWORD clientIndex;

    /**
     * @brief relatvie clustertime, from 0 to cyclelength
     *
     * Relatvie clustertime, from 0 to cyclelength
     */
    DWORD clusterTime;

    /**
     * @brief slot identifier
     *
     * slot identifier
     */
    WORD frameId;

    /**
     * CRC of the frame header
     */
    WORD headerCrc;

    /**
     * @brief V6 framestate
     *
     * V6 framestate:
     *   - 0 Payload preample indicator bit
     *   - 1 Sync. frame indicator
     *   - 2 Reserved bit
     *   - 3 Null frame indicator
     *   - 4 Startup frame indicator
     *   - 5-7 Frame state format mask (see below)
     *
     * Bit 5-7 meaning:
     *   - 0 (0x00) Motorola V.6
     *   - 1 (0x20) reserved
     *   - 2 (0x40) BusDoctor
     *   - 3 (0x60) reserved
     *   - 4 (0x80) FlexCard Cyclone
     *   - 5 (0xA0) reserved
     *   - 6 (0xC0) reserved
     *   - 7 (0xE0) reserved
     */
    WORD frameState;

    /**
     * @brief dlc of message
     *
     * Payload length
     */
    BYTE length;

    /**
     * @brief current cycle
     *
     * Current cycle number
     */
    BYTE cycle;

    /**
     * @brief Bit0 = NMBit, Bit1 = SyncBit, Bit2 = Reserved
     *
     * - Bit 0 = NMBit
     * - Bit 1 = SyncBit
     * - Bit 2 = Reserved
     */
    BYTE headerBitMask;

    /** reserved */
    BYTE reserved1;

    /** reserved */
    WORD reserved2;

    /**
     * @brief array of databytes
     *
     * Payload
     */
    std::array<BYTE, 64> dataBytes;
};

}
}
