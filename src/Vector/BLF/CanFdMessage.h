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

#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief CAN_FD_MESSAGE
 */
struct VECTOR_BLF_EXPORT CanFdMessage final : ObjectHeader {
    CanFdMessage();

    std::vector<uint8_t>::iterator fromData(std::vector<uint8_t>::iterator it) override;
    void toData(std::vector<uint8_t> & data) override;
    DWORD calculateObjectSize() const override;

    /**
     * @brief application channel
     */
    WORD channel {};

    /**
     * enumeration for flags
     */
    enum Flags : BYTE {
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
    BYTE flags {};

    /**
     * @brief CAN dlc
     */
    BYTE dlc {};

    /**
     * @brief CAN ID
     */
    DWORD id {};

    /**
     * @brief message length in ns - without 3 inter frame space bits and by Rx-message also without 1 End-Of-Frame bit
     */
    DWORD frameLength {};

    /**
     * @brief bit count of arbitration phase
     */
    BYTE arbBitCount {};

    /**
     * enumeration for canFdFlags
     */
    enum CanFdFlags : BYTE {
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
    BYTE canFdFlags {};

    /**
     * @brief Valid payload length of data
     */
    BYTE validDataBytes {};

    /** reserved */
    BYTE reservedCanFdMessage1 {};

    /** reserved */
    DWORD reservedCanFdMessage2 {};

    /**
     * @brief CAN FD data
     */
    std::vector<BYTE> data {};

    /** reserved */
    DWORD reservedCanFdMessage3 {};

    // @note might be extended in future versions
};

}
}
