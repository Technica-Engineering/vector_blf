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

#include "VectorTypes.h"
#include "ObjectHeader.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief FR_RCVMESSAGE
 *
 * FlexRay message received or transmitted on FlexRay bus.
 */
class FlexRayVFrReceiveMsg : public ObjectHeader
{
public:
    FlexRayVFrReceiveMsg();

    /**
     * @brief application channel
     *
     * Application channel
     */
    WORD channel;

    /**
     * @brief version of data struct
     *
     * Object version, for internal use
     */
    WORD version;

    /**
     * @brief channel mask
     * @see 3.3.2
     */
    WORD channelMask;

    /**
     * @brief dir flag (tx, rx)
     * @see 3.3.1
     */
    BYTE dir;

    /**
     * @brief clientindex of send node
     *
     * Client index of send node. Must be set to 0 if file
     * is written from other applications.
     */
    DWORD clientIndex;

    /**
     * @brief number of cluster
     *
     * Number of cluster: channel number - 1
     */
    DWORD clusterNo;

    /**
     * @brief slot identifier, word
     *
     * Slot identifier
     */
    WORD frameId;

    /**
     * @brief header crc channel 1
     *
     * Header CRC FlexRay channel 1 (A)
     */
    WORD headerCRC1;

    /**
     * @brief header crc channel 2
     *
     * Header CRC FlexRay channel 2 (B)
     */
    WORD headerCRC2;

    /**
     * @brief byte count (not payload) of frame from CC receive buffer
     *
     * Payload length in bytes
     */
    WORD byteCount;

    /**
     * @brief length of the data array (stretchy struct)
     *
     * Number of bytes of the payload stored in
     * dataBytes. If the CC-frame buffer was too
     * small to receive the complete payload, then
     * dataCount is smaller than byteCount.
     */
    WORD dataCount;

    /**
     * @brief current cycle, byte
     *
     * Cycle number
     */
    BYTE cycle;

    /**
     * @brief type of cc
     *
     * Type of communication controller
     * @see 3.3.3
     */
    DWORD tag;

    /**
     * @brief register flags
     *
     * Controller specific frame state information
     * @see 3.3.4
     */
    DWORD data;

    /**
     * @brief frame flags
     *
     * See description of flags
     * @see 3.3.5
     */
    DWORD frameFlags;

    /**
     * @brief TxRq, TxAck flags
     *
     * Not used, reserved
     */
    DWORD appParameter;

    /**
     * @brief array of databytes
     *
     * Payload
     */
    BYTE dataBytes[254];
};

}
}
