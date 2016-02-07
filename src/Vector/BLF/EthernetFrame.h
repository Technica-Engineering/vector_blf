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
#include <vector>

#include "AbstractFile.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief ETHERNET_FRAME
 *
 * Ethernet frame.
 */
class VECTOR_BLF_EXPORT EthernetFrame : public ObjectHeader
{
public:
    EthernetFrame();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * Ethernet (MAC) address of source computer
     * (network byte order).
     */
    std::array<BYTE, 6> sourceAddress;

    /**
     * The channel of the frame.
     */
    WORD channel;

    /**
     * Ethernet (MAC) address of target computer
     * (network byte order).
     */
    std::array<BYTE, 6> destinationAddress;

    /** enumeration for dir */
    enum class Dir : WORD {
        Rx = 0,
        Tx = 1,
        TxRq = 2
    };

    /**
     * @brief Direction flag
     *
     * Direction flag
     */
    WORD dir;

    /**
     * EtherType which indicates protocol for
     * Ethernet payload data
     *
     * See Ethernet standard specification for valid
     * values.
     */
    WORD type;

    /**
     * TPID when VLAN tag valid, zero when no
     * VLAN. See Ethernet standard specification.
     */
    WORD tpid;

    /**
     * TCI when VLAND tag valid, zero when no
     * VLAN. See Ethernet standard specification.
     */
    WORD tci;

    /**
     * @brief Number of valid payLoad bytes
     *
     * Length of Ethernet payload data in bytes. Max.
     * 1500 Bytes (without Ethernet header)
     */
    WORD payLoadLength;

    /** reserved */
    std::array<BYTE, 8> reserved;

    /**
     * @brief Max 1500 data bytes per frame
     *
     * Ethernet payload data (without Ethernet
     * header)
     */
    std::vector<uint8_t> payLoad;
};

}
}
