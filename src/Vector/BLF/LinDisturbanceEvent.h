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

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief LIN_DISTURBANCE_EVENT
 *
 * This event occurs if CANoe/CANalyzer explicitly caused to disturb one bit or a
 * sequence of bits.
 */
struct VECTOR_BLF_EXPORT LinDisturbanceEvent final : ObjectHeader {
    LinDisturbanceEvent();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief application channel
     *
     * Channel number of the event
     */
    uint16_t channel {};

    /**
     * @brief LIN ID of disturbed response
     *
     * Identifier of a disturbed
     * response or 0xFF if a header
     * was disturbed.
     */
    uint8_t id {};

    /**
     * @brief LIN ID of disturbing header
     *
     * Identifier of a disturbing
     * header, if disturbing with a
     * header (disturbanceType
     * == 2), otherwise 0xFF.
     */
    uint8_t disturbingFrameId {};

    /**
     * @brief type of disturbance (dominant, recessive, header, bitstream, variable bitstream)
     *
     * The type of disturbance:
     *   - 0: dominant disturbance
     *   - 1: recessive disturbance
     *   - 2: disturbance with a header
     *   - 3: disturbance with a
     *     bitstream
     *   - 4: disturbance with a variable
     *     bitstream
     */
    uint32_t disturbanceType {};

    /**
     * @brief index of the byte that was disturbed
     *
     * The 0-indexed byte where
     * the disturbance occurred. 0 is
     * the first data byte, 9 is the
     * checksum in case of a dlc 8
     * frame.
     *
     * If a header was disturbed
     * (id == 0xFF), 0 is the sync
     * field and 1 is the PID.
     */
    uint32_t byteIndex {};

    /**
     * @brief index of the bit that was disturbed
     * disturbed. 0 is the first data
     * bit, 8 is the stop bit, 9 is the
     * first bit in interbyte space.
     *
     * The index of the bit that was
     */
    uint32_t bitIndex {};

    /**
     * @brief offset in 1/16th bits into the disturbed bit
     *
     * The offset in 1/16th bits
     * into the disturbed bit.
     */
    uint32_t bitOffsetInSixteenthBits {};

    /**
     * @brief length of the disturbance in units of 1/16th bit
     *
     * The length of a dominant or
     * recessive disturbance in units
     * of 1/16th bits.
     */
    uint32_t disturbanceLengthInSixteenthBits {};
};

}
}
