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
 * @brief ETHERNET_RX_ERROR
 *
 * Ethernet RX error frame.
 */
struct VECTOR_BLF_EXPORT EthernetRxError final : ObjectHeader {
    EthernetRxError();

    std::vector<uint8_t>::iterator fromData(std::vector<uint8_t>::iterator it) override;
    void toData(std::vector<uint8_t> & data) override;
    DWORD calculateObjectSize() const override;

    /**
     * Calculates structLength.
     *
     * @return struct length
     */
    virtual WORD calculateStructLength() const;

    /**
     * @brief Length of this structure
     *
     * Length of this structure, without
     * sizeof(ObjectHeader) and without raw data
     * length
     */
    WORD structLength {};

    /**
     * The channel of the frame.
     */
    WORD channel {};

    /** enumeration for dir */
    enum Dir : WORD {
        /** receive */
        Rx = 0,

        /** transmit */
        Tx = 1,

        /** transmit request */
        TxRq = 2
    };

    /**
     * @brief Direction flag
     */
    WORD dir {};

    /**
     * @brief HW channel. 0 = invalid.
     */
    WORD hardwareChannel {};

    /**
     * @brief Frame Check Sum
     *
     * Ethernet frame checksum.
     */
    DWORD fcs {};

    /**
     * @brief Number of valid raw ethernet data bytes
     *
     * Number of valid raw ethernet data bytes, starting
     * with Target MAC ID.
     */
    WORD frameDataLength {};

    /** reserved */
    WORD reservedEthernetRxError {};

    /**
     * Error code
     *
     * - 1: Data Length Error
     * - 2: Invalid CRC
     * - 3: Invalid Data received
     * - 4: Collision detected
     */
    DWORD error {};

    /**
     * @brief Max 1600 data bytes per frame
     *
     * Raw Ethernet frame data.
     * Max 1522 data bytes per frame.
     */
    std::vector<uint8_t> frameData {};
};

}
}
