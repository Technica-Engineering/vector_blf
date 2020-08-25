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
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief CAN_FD_MESSAGE
 */
struct VECTOR_BLF_EXPORT CanFdMessage final : ObjectHeader {
    CanFdMessage();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief application channel
     */
    uint16_t channel {};

    /**
     * enumeration for flags
     */
    enum Flags : uint8_t {
        /** transmit direction */
        TX = (1 << 0),

        /** single wire operation */
        NERR = (1 << 5),

        /** wake up message (high voltage) */
        WU = (1 << 6),

        /** remote transmission request */
        RTR = (1 << 7)
    };

    /**
     * @brief CAN dir & rtr
     *
     * CAN Message Flags
     *
     * CAN dir, rtr, wu & nerr encoded into flags
     */
    uint8_t flags {};

    /**
     * @brief CAN dlc
     */
    uint8_t dlc {};

    /**
     * @brief CAN ID
     */
    uint32_t id {};

    /**
     * @brief message length in ns - without 3 inter frame space bits and by Rx-message also without 1 End-Of-Frame bit
     */
    uint32_t frameLength {};

    /**
     * @brief bit count of arbitration phase
     */
    uint8_t arbBitCount {};

    /**
     * enumeration for canFdFlags
     */
    enum CanFdFlags : uint8_t {
        /** extended data length */
        EDL = (1 << 0),

        /** bit rate switch */
        BRS = (1 << 1),

        /** error state indicator */
        ESI = (1 << 2)
    };

    /**
     * @brief CAN FD flags
     */
    uint8_t canFdFlags {};

    /**
     * @brief Valid payload length of data
     */
    uint8_t validDataBytes {};

    /** reserved */
    uint8_t reservedCanFdMessage1 {};

    /** reserved */
    uint32_t reservedCanFdMessage2 {};

    /**
     * @brief CAN FD data
     */
    std::vector<uint8_t> data {};

    /** reserved */
    uint32_t reservedCanFdMessage3 {};
};

}
}
