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
 * @brief ETHERNET_ERROR_FORWARDED
 *
 * Ethernet error forwarded
 */
struct VECTOR_BLF_EXPORT EthernetErrorForwarded final : ObjectHeader {
    EthernetErrorForwarded();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * Calculates structLength.
     *
     * @return struct length
     */
    virtual uint16_t calculateStructLength() const;

    /**
     * @brief Length of this structure
     *
     * Length of this structure, without
     * sizeof(ObjectHeader) and without raw data
     * length
     */
    uint16_t structLength {};

    /**
     * @brief flags, which indicates the valid fields:
     *   - Bit 0 - reserved
     *   - Bit 1 - hardwareChannel valid
     *   - Bit 2 - frameDuration valid
     *   - Bit 3 - frameChecksum valid
     *   - Bit 4 - frameHandle valid
     */
    uint16_t flags {};

    /**
     * @brief application channel, i.e. Eth 1
     */
    uint16_t channel {};

    /**
     * @brief HW channel
     */
    uint16_t hardwareChannel {};

    /**
     * @brief Transmission duration in [ns]
     */
    uint64_t frameDuration {};

    /**
     * @brief Ethernet checksum
     */
    uint32_t frameChecksum {};

    /**
     * @brief Direction flag: 0=Rx, 1=Tx, 2=TxRq
     */
    uint16_t dir {};

    /**
     * @brief Number of valid frameData bytes
     */
    uint16_t frameLength {};

    /**
     * @brief Handle which refer the corresponding EthernetFrameForwarded event
     */
    uint32_t frameHandle {};

    /**
     * Error code
     *
     * - 1: Data Length Error
     * - 2: Invalid CRC
     * - 3: Invalid Data received
     * - 4: Collision detected
     */
    uint32_t error {};

    /**
     * @brief Max 1612 data bytes per frame. Contains Ethernet header + Ethernet payload
     */
    std::vector<uint8_t> frameData {};
};

}
}
