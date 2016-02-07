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

#include "AbstractFile.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_DISTURBANCE_EVENT
 *
 * This event occurs if CANoe/CANalyzer explicitly caused to disturb one bit or a
 * sequence of bits.
 */
class VECTOR_BLF_EXPORT LinDisturbanceEvent : public ObjectHeader
{
public:
    LinDisturbanceEvent();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Channel number of the event
     */
    WORD channel;

    /**
     * @brief LIN ID of disturbed response
     *
     * Identifier of a disturbed
     * response or 0xFF if a header
     * was disturbed.
     */
    BYTE id;

    /**
     * @brief LIN ID of disturbing header
     *
     * Identifier of a disturbing
     * header, if disturbing with a
     * header (disturbanceType
     * == 2), otherwise 0xFF.
     */
    BYTE disturbingFrameId;

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
    ULONG disturbanceType;

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
    ULONG byteIndex;

    /**
     * @brief index of the bit that was disturbed
     * disturbed. 0 is the first data
     * bit, 8 is the stop bit, 9 is the
     * first bit in interbyte space.
     *
     * The index of the bit that was
     */
    ULONG bitIndex;

    /**
     * @brief offset in 1/16th bits into the disturbed bit
     *
     * The offset in 1/16th bits
     * into the disturbed bit.
     */
    ULONG bitOffsetInSixteenthBits;

    /**
     * @brief length of the disturbance in units of 1/16th bit
     *
     * The length of a dominant or
     * recessive disturbance in units
     * of 1/16th bits.
     */
    ULONG disturbanceLengthInSixteenthBits;
};

}
}
