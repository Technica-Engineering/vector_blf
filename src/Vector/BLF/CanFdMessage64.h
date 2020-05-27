/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
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

#include <vector>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/CanFdExtFrameData.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief CAN_FD_MESSAGE_64
 *
 * CAN FD data frame, or CAN data- or remote frame on a CAN FD channel.
 */
struct VECTOR_BLF_EXPORT CanFdMessage64 final : ObjectHeader, CanFdExtFrameData {
    CanFdMessage64();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    DWORD calculateObjectSize() const override;

    virtual bool hasExtData() const;

    /**
     * @brief application channel
     *
     * Channel the frame was sent or received.
     */
    BYTE channel {};

    /**
     * @brief CAN dlc
     *
     * Data length code of frame.
     *
     * - DLC=0-8: CAN=0-8, CAN FD=0-8
     * - DLC=9: CAN=8, CAN FD=12
     * - DLC=10: CAN=8, CAN FD=16
     * - DLC=11: CAN=8, CAN FD=20
     * - DLC=12: CAN=8, CAN FD=24
     * - DLC=13: CAN=8, CAN FD=32
     * - DLC=14: CAN=8, CAN FD=48
     * - DLC=15: CAN=8, CAN FD=64
     */
    BYTE dlc {};

    /**
     * @brief Valid payload length of data
     *
     * Valid payload length of data, can differ from
     * DLC value.
     */
    BYTE validDataBytes {};

    /**
     * @brief txRequiredCount (4 bits), txReqCount (4 Bits)
     *
     * (Bits 0-3) Number of required tranmission
     * attempts, (Bits 4-7) Max Number of
     * transmission attempts.
     */
    BYTE txCount {};

    /**
     * @brief CAN ID
     *
     * Frame identifier.
     */
    DWORD id {};

    /**
     * @brief message length in ns
     *
     * Message duration [in ns]. Not including 3
     * interframe-space bit times and by Rx-messages
     * also not including 1 end-of-frame bit time
     */
    DWORD frameLength {};

    /**
     * @brief flags
     *
     * - Bit#=0 (0x0001): Must be 0
     * - Bit#=1 (0x0002): Reserved, for internal use
     * - Bit#=2 (0x0004): 1=NERR (1=single wire on low speed CAN)
     * - Bit#=3 (0x0008): 1=High voltage wake up
     * - Bit#=4 (0x0010): 1=Remote frame (only CAN)
     * - Bit#=5 (0x0020): Reserved, must be 0
     * - Bit#=6 (0x0040): 1=Tx Acknowledge
     * - Bit#=7 (0x0080): 1=Tx Request
     * - Bit#=8 (0x0100): Reserved, must be 0
     * - Bit#=9 (0x0200): SRR (CAN FD)
     * - Bit#=10 (0x0400): R0
     * - Bit#=11 (0x0800): R1
     * - Bit#=12 (0x1000): EDL, 0: CAN frame, 1: CAN FD frame
     * - Bit#=13 (0x2000): BRS (CAN FD)
     * - Bit#=14 (0x4000): ESI
     * - Bit#=15 (0x8000): Reserved, must be 0
     * - Bit#=16 (0x10000): Reserved, must be 0
     * - Bit#=17 (0x20000): 1=Frame is part of a burst
     * - Bit#=18-31: Reserved, must be 0
     */
    DWORD flags {};

    /**
     * @brief bit rate used in arbitration phase
     *
     * CAN- or CAN-FD bit timing configuration for
     * arbitration phase, may be 0, if not supported by
     * hardware/driver
     *
     * - Bit 0-7: Quartz Frequency
     * - Bit 8-15: Prescaler
     * - Bit 16-23: BTL Cycles
     * - Bit 24-31: Sampling Point
     */
    DWORD btrCfgArb {};

    /**
     * @brief bit rate used in data phase
     *
     * CAN-FD bit timing configuration for data
     * phase, may be 0, if not supported by
     * hardware/driver. See btrCfgArb.
     */
    DWORD btrCfgData {};

    /**
     * @brief time offset of brs field
     *
     * Time offset of bit rate switch within BRS field
     * in nanoseconds
     */
    DWORD timeOffsetBrsNs {};

    /**
     * @brief time offset of crc delimiter field
     *
     * Time offset of bit rate switch within CRC
     * delimiter field in nanoseconds
     */
    DWORD timeOffsetCrcDelNs {};

    /**
     * @brief complete message length in bits
     *
     * Bit count of the message
     */
    WORD bitCount {};

    /**
     * Direction of the message
     */
    BYTE dir {};

    /** offset if extDataOffset is used */
    BYTE extDataOffset {};

    /**
     * @brief CRC for CAN
     */
    DWORD crc {};

    /**
     * @brief CAN FD data
     *
     * Data bytes (the actual length may be shorter
     * than 64 bytes, according to the value of
     * dlc).
     */
    std::vector<BYTE> data {};
};

}
}
