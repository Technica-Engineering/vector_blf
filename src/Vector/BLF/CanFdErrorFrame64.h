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
 * @brief CAN_FD_ERROR_64
 *
 * CAN-FD error frame received or transmitted on a CAN-FD channel.
 */
class VECTOR_BLF_EXPORT CanFdErrorFrame64 : public ObjectHeader
{
public:
    CanFdErrorFrame64();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Channel the frame was sent or received.
     */
    BYTE channel;

    /**
     * @brief CAN dlc
     *
     * Data length code of the corrupted message.
     */
    BYTE dlc;

    /**
     * @brief Valid payload length of data
     *
     * Number of data bytes of the corrupted message.
     */
    BYTE validDataBytes;

    /**
     * Content of Philips SJA1000 Error Code Capture
     * register, or the Vector CAN-Core error register.
     * See field ecc of CanErrorFrameExt.
     */
    BYTE ecc;

    /**
     * Defines what additional information is valid. See
     * field flags of CanErrorFrameExt.
     */
    WORD flags;

    /**
     * Extended error flags. See field flagsExt of
     * CanErrorFrameExt.
     */
    WORD errorCodeExt;

    /**
     * @brief FD specific flags
     *
     * CAN-FD specific flags.
     *
     * - Bit 0-3 Meaning:
     *   - unused
     * - Bit 0-4 Meaning:
     *   - 0: Error in Arbitration Phase
     *   - 1: Error in Data Phase
     * - Bit 5 Meaning:
     *   - 0: ESI is 0
     *   - 1: ESI is 1
     * - Bit 6 Meaning
     *   - 0: BRS is 0
     *   - 1: BRS is 1
     * - Bit 7 Meaning
     *   - 0: EDL is 0
     *   - 1: EDL is 1
     */
    WORD extFlags;

    /** reserved */
    WORD reserved1;

    /**
     * @brief CAN ID
     *
     * Message ID of the corrupted message.
     */
    DWORD id;

    /**
     * @brief message length in ns
     *
     * Length of the error frame in nanoseconds (time
     * difference between Start Of Frame and End Of
     * Frame)
     *
     * without 3 inter frame space bits and by Rx-message also without 1 End-Of-Frame bit
     */
    DWORD frameLength;

    /**
     * @brief bit rate used in arbitration phase
     *
     * CAN-FD bit timing configuration for arbiration
     * phase, may be 0, if not supported by
     * hardware/driver
     *
     * - Bit 0-7: Quartz Frequency
     * - Bit 8-15: Prescaler
     * - Bit 16-23: BTL Cycles
     * - Bit 24-31: Sampling Point
     */
    DWORD btrCfgArb;

    /**
     * @brief bit rate used in data phase
     *
     * CAN-FD bit timing configuration for arbiration
     * phase, may be 0, if not supported by
     * hardware/driver. See btrCfgArb.
     */
    DWORD btrCfgData;

    /**
     * @brief time offset of brs field
     *
     * Time offset of bit rate switch within BRS field in
     * nanoseconds
     */
    DWORD timeOffsetBrsNs;

    /**
     * @brief time offset of brs field
     *
     * Time offset of bit rate switch within CRC
     * delimiter field in nanoseconds
     */
    DWORD timeOffsetCrcDelNs;

    /**
     * CRC checksum of corrupted message.
     */
    DWORD crc;

    /**
     * Bit position of the error frame in the corrupted
     * message.
     */
    WORD errorPosition;

    /** reserved */
    WORD reserved2;

    /**
     * @brief CAN FD data
     *
     * CAN FD data bytes (the actual length may be
     * shorter than 64 bytes, according to the value of
     * dlc, e.g. when DLC is 12 data has length
     * 24)
     */
    std::array<BYTE, 64> data;
};

}
}
