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

#include <array>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief LIN_CRC_ERROR
 *
 * @deprecated
 *
 * Checksum error event occurring when Slave sends an incorrect checksum value for a
 * frame response that is otherwise correct.
 */
struct VECTOR_BLF_EXPORT LinCrcError final : ObjectHeader {
    LinCrcError();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief application channel
     *
     * Channel number where the event notified
     */
    uint16_t channel {};

    /**
     * @brief LIN ID
     *
     * Frame identifier
     */
    uint8_t id {};

    /**
     * @brief LIN DLC
     *
     * Frame length
     */
    uint8_t dlc {};

    /**
     * Databyte values
     */
    std::array<uint8_t, 8> data {};

    /**
     * Slave Identifier in the Final State Machine
     * (obsolete)
     */
    uint8_t fsmId {};

    /**
     * State Identifier of a Slave in the Final State
     * Machine (obsolete)
     */
    uint8_t fsmState {};

    /**
     * Duration of the frame header [in bit times]
     */
    uint8_t headerTime {};

    /**
     * Duration of the entire frame [in bit times]
     */
    uint8_t fullTime {};

    /**
     * Checksum byte value
     */
    uint16_t crc {};

    /**
     * @brief direction
     *
     * Direction of bus events
     *   - 0: Rx (received)
     *   - 1: Tx (transmit receipt)
     *   - 2: Tx Request (transmit request)
     */
    uint8_t dir {};

    /** reserved */
    uint8_t reservedLinCrcError1 {};

    /** reserved */
    uint32_t reservedLinCrcError2 {};
};

}
}
