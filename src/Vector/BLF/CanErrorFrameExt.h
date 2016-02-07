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
 * @brief CAN_ERROR_EXT
 *
 * Extended CAN error frame received or transmitted on a CAN channel.
 */
class VECTOR_BLF_EXPORT CanErrorFrameExt : public ObjectHeader
{
public:
    CanErrorFrameExt();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Channel the frame was sent or received.
     */
    WORD channel;

    /**
     * @brief CAN error frame length
     *
     * Length of error frame, unused, may be 0.
     */
    WORD length;

    /**
     * @brief extended CAN error frame flags
     *
     * Defines what additional information is valid.
     * Following values are possible:
     *
     * - 1: SJA 1000 ECC is valid (member ecc)
     * - 2: Vector CAN Core Error Code is valid.
     * - 4: Vector CAN Core Error Position
     * - 8: Vector CAN Core Frame Length in ns
     */
    DWORD flags;

    /**
     * @brief error control code
     *
     * Content of Philips SJA1000 Error Code Capture
     * (ECC) register, or the Vector CAN-Core error
     * register (see also flags).
     *
     * SJA1000-ECC
     *
     * See documentation of Philips SJA1000 CAN
     * Controller.
     *
     * Vector CAN-Core
     *
     * - Bit 0-5 Meaning:
     *   - 0: Bit Error
     *   - 1: Form Error
     *   - 2: Stuff Error
     *   - 3: Other Error
     *   - 4: CRC Error
     *   - 5: Ack-Del-Error
     * - Bit 6-7 Meaning:
     *   - 0: RX-NAK-Error
     *   - 1: TK-NAK-Error
     *   - 2: RX-Error
     *   - 3: TX-Error
     */
    BYTE ecc;

    /**
     * @brief error position
     *
     * Bit position of the error frame in the corrupted
     * message.
     */
    BYTE position;

    /**
     * @brief lower 4 bits: DLC from CAN-Core. Upper 4 bits: reserved
     *
     * Data length code of the corrupted message.
     */
    BYTE dlc;

    /** reserved */
    BYTE reserved1;

    /**
     * @brief frame length in ns
     *
     * Length of the error frame in nanoseconds (time
     * difference between Start Of Frame and End Of
     * Frame)
     */
    DWORD frameLengthInNs;

    /**
     * @brief frame ID from CAN-Core
     *
     * Message ID of the corrupted message.
     */
    DWORD id;

    /**
     * @brief extended error flags
     *
     * Extended error flags.
     *
     * - Bit 0-4: Segment (only SJA1000)
     * - Bit 5: Direction, 1=RX
     * - Bit 6-11: Error Code
     *   - 0: Bit Error
     *   - 1: Form Error
     *   - 2: Stuff Error
     *   - 3: Other Error
     *   - 4: CRC Error
     *   - 5: ACK-DEL Error
     * - Bit 12-13: Extended Direction
     *   - 0: RX NAK
     *   - 1: TX NAK
     *   - 2: RX
     *   - 3: TX
     * - Bit 14: 1=The error frame was send from the application
     */
    WORD flagsExt;

    /** reserved */
    WORD reserved2;

    /**
     * @brief Payload, only for CAN-Core
     *
     * Message data.
     */
    std::array<BYTE, 8> data;
};

}
}
