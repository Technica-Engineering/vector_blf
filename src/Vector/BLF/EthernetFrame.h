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
#include <vector>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief ETHERNET_FRAME
 *
 * Ethernet frame
 */
struct VECTOR_BLF_EXPORT EthernetFrame final : ObjectHeader {
    EthernetFrame();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * Ethernet (MAC) address of source computer
     * (network byte order).
     */
    std::array<uint8_t, 6> sourceAddress {};

    /**
     * The channel of the frame.
     */
    uint16_t channel {};

    /**
     * Ethernet (MAC) address of target computer
     * (network byte order).
     */
    std::array<uint8_t, 6> destinationAddress {};

    /** enumeration for dir */
    enum Dir : uint16_t {
        Rx = 0,
        Tx = 1,
        TxRq = 2
    };

    /**
     * @brief Direction flag
     *
     * Direction flag
     */
    uint16_t dir {};

    /**
     * EtherType which indicates protocol for
     * Ethernet payload data
     *
     * See Ethernet standard specification for valid
     * values.
     */
    uint16_t type {};

    /**
     * TPID when VLAN tag valid, zero when no
     * VLAN. See Ethernet standard specification.
     */
    uint16_t tpid {};

    /**
     * TCI when VLAND tag valid, zero when no
     * VLAN. See Ethernet standard specification.
     */
    uint16_t tci {};

    /**
     * @brief Number of valid payLoad bytes
     *
     * Length of Ethernet payload data in bytes. Max.
     * 1500 Bytes (without Ethernet header)
     */
    uint16_t payLoadLength {};

    /** reserved */
    uint64_t reservedEthernetFrame {};

    /**
     * @brief Max 1500 data bytes per frame
     *
     * Ethernet payload data (without Ethernet
     * header)
     */
    std::vector<uint8_t> payLoad {};
};

}
}
