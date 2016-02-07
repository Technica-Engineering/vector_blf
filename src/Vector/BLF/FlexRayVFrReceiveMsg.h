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
 * @brief FR_RCVMESSAGE
 *
 * FlexRay message received or transmitted on FlexRay bus.
 */
class VECTOR_BLF_EXPORT FlexRayVFrReceiveMsg : public ObjectHeader
{
public:
    FlexRayVFrReceiveMsg();

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
     * @brief version of data struct
     *
     * Object version, for internal use
     */
    WORD version;

    /**
     * @brief channel mask
     *
     * Channel Mask
     *   - 0 = Reserved or invalid
     *   - 1 = FlexRay Channel A
     *   - 2 = FlexRay Channel B
     *   - 3 = FlexRay Channels A and B
     */
    WORD channelMask;

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

    /** reserved */
    BYTE reserved1;

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
    WORD headerCrc1;

    /**
     * @brief header crc channel 2
     *
     * Header CRC FlexRay channel 2 (B)
     */
    WORD headerCrc2;

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
     * @brief current cycle
     *
     * Cycle number
     */
    BYTE cycle;

    /** reserved */
    BYTE reserved2;

    /**
     * @brief type of cc
     *
     * Type of communication controller
     *   - 0 = Architecture independent
     *   - 1 = Invalid CC type (for internal use only)
     *   - 2 = Cyclone I
     *   - 3 = BUSDOCTOR
     *   - 4 = Cyclone II
     *   - 5 = Vector VN interface
     *   - 6 = VN-Sync-Pulse (only in Status Event, for debugging purposes only)
     */
    DWORD tag;

    /**
     * @brief frame flags
     *
     * Description of frame flags:
     * - Bit 0: 1 = Null frame.
     * - Bit 1: 1 = Data segment contains valid data
     * - Bit 2: 1 = Sync bit
     * - Bit 3: 1 = Startup flag
     * - Bit 4: 1 = Payload preamble bit
     * - Bit 5: 1 = Reserved bit
     * - Bit 6: 1 = Error flag (error frame or invalid frame)
     * - Bit 7: Reserved
     * - Bit 8: Internally used in CANoe/CANalyzer
     * - Bit 9: Internally used in CANoe/CANalyzer
     * - Bit 10: Internally used in CANoe/CANalyzer
     * - Bit 11: Internally used in CANoe/CANalyzer
     * - Bit 12: Internally used in CANoe/CANalyzer
     * - Bit 13: Internally used in CANoe/CANalyzer
     * - Bit 14: Internally used in CANoe/CANalyzer
     * - Bit 15: 1 = Async. monitoring has generated this event
     * - Bit 16: 1 = Event is a PDU
     * - Bit 17: Valid for PDUs only. The bit is set if the PDU is valid (either if the PDU has no update
     *   bit, or the update bit for the PDU was set in the received frame).
     * - Bit 18: Reserved
     * - Bit 19: 1 = Raw frame (only valid if PDUs are used in the configuration). A raw frame may
     *   contain PDUs in its payload
     * - Bit 20: 1 = Dynamic segment
     *   0 = Static segment
     * - Bit 21 This flag is only valid for frames and not for PDUs.
     *   1 = The PDUs in the payload of this frame are logged in separate logging entries.
     *   0 = The PDUs in the payload of this frame must be extracted out of this frame. The
     *   logging file does not contain separate PDU-entries.
     * - Bit 22 Valid for PDUs only. The bit is set if the PDU has an update bit
     *
     * The reserved bits and the bits which are for internally CANoe/CANalyzer usage must be ignored
     * from other applications. Other applications must set these bits to 0 when writing logging files.
     */
    DWORD data;

    /**
     * @brief frame flags
     *
     * Description of frame flags:
     * - Bit 0: 1 = Null frame.
     * - Bit 1: 1 = Data segment contains valid data
     * - Bit 2: 1 = Sync bit
     * - Bit 3: 1 = Startup flag
     * - Bit 4: 1 = Payload preamble bit
     * - Bit 5: 1 = Reserved bit
     * - Bit 6: 1 = Error flag (error frame or invalid frame)
     * - Bit 7: Reserved
     * - Bit 8: Internally used in CANoe/CANalyzer
     * - Bit 9: Internally used in CANoe/CANalyzer
     * - Bit 10: Internally used in CANoe/CANalyzer
     * - Bit 11: Internally used in CANoe/CANalyzer
     * - Bit 12: Internally used in CANoe/CANalyzer
     * - Bit 13: Internally used in CANoe/CANalyzer
     * - Bit 14: Internally used in CANoe/CANalyzer
     * - Bit 15: 1 = Async. monitoring has generated this event
     * - Bit 16: 1 = Event is a PDU
     * - Bit 17: Valid for PDUs only. The bit is set if the PDU is valid (either if the PDU has no update
     *   bit, or the update bit for the PDU was set in the received frame).
     * - Bit 18: Reserved
     * - Bit 19: 1 = Raw frame (only valid if PDUs are used in the configuration). A raw frame may
     *   contain PDUs in its payload
     * - Bit 20: 1 = Dynamic segment
     *   0 = Static segment
     * - Bit 21 This flag is only valid for frames and not for PDUs.
     *   1 = The PDUs in the payload of this frame are logged in separate logging entries.
     *   0 = The PDUs in the payload of this frame must be extracted out of this frame. The
     *   logging file does not contain separate PDU-entries.
     * - Bit 22 Valid for PDUs only. The bit is set if the PDU has an update bit
     *
     * The reserved bits and the bits which are for internally CANoe/CANalyzer usage must be ignored
     * from other applications. Other applications must set these bits to 0 when writing logging files.
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
    std::array<BYTE, 254> dataBytes;
};

}
}
