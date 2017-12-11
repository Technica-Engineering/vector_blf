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

#include <Vector/BLF/platform.h>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief ETHERNET_STATUS
 *
 * Ethernet status.
 */
class VECTOR_BLF_EXPORT EthernetStatus final : public ObjectHeader
{
public:
    EthernetStatus();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /**
     * The channel of the event.
     */
    WORD channel;

    /** enumeration for flags */
    enum class Flags : WORD
    {
        /** Link Status */
        LinkStatus = 0x0001,

        /** Bit rate */
        Bitrate = 0x0002,

        /** Ethernet Phy */
        EthernetPhy = 0x0004,

        /** Duplex */
        Duplex = 0x0008,

        /** Hardware Channel */
        HardwareChannel = 0x0010,
    };

    /** flags */
    WORD flags;

    /** enumeration for linkStatus */
    enum class LinkStatus : BYTE
    {
        /** Unknown */
        UnknownLinkStatus = 0,

        /** Link down */
        LinkDown = 1,

        /** Link up */
        LinkUp = 2,

        /** Negotiate */
        Negotiate = 3,

        /** Link error */
        LinkError = 4
    };

    /**
     * @brief Link Status
     */
    LinkStatus linkStatus;

    /** enumeration for ethernetPhy */
    enum class EthernetPhy : BYTE
    {
        /** Unknown */
        UnknownEthernetPhy = 0,

        /** IEEE 802.3 */
        Ieee802_3 = 1,

        /** BroadR-Reach */
        BroadR_Reach = 2
    };

    /**
     * @brief Ethernet Phy
     */
    EthernetPhy ethernetPhy;

    /** enumeration for duplex */
    enum class Duplex : BYTE
    {
        /** Unknown */
        UnknownDuplex = 0,

        /** Half Duplex */
        HalfDuplex = 1,

        /** Full Duplex */
        FullDuplex = 2
    };

    /**
     * @brief Duplex
     */
    Duplex duplex;

    /** enumeration for mdi */
    enum class Mdi : BYTE
    {
        /** Unknown */
        UnknownMdi = 0,

        /** Direct */
        Direct = 1,

        /** Crossover */
        Crossover = 2
    };

    /** MDI */
    Mdi mdi;

    /** enumeration for connector */
    enum class Connector : BYTE
    {
        /** Unknown */
        UnknownConnector = 0,

        /** RJ45*/
        Rj45 = 1,

        /** D-Sub */
        DSub = 2
    };

    /** connector */
    Connector connector;

    /** enumeration for clockMode */
    enum class ClockMode : BYTE
    {
        /** Unknown */
        UnknownClockMode = 0,

        /** Master */
        Master = 1,

        /** Slave */
        Slave = 2
    };

    /** clock mode */
    ClockMode clockMode;

    /** enumeration for pairs */
    enum class Pairs : BYTE
    {
        /** Unknown */
        UnknownPairs = 0,

        /** BR 1-pair */
        Br1Pair = 1,

        /** BR 2-pair */
        Br2Pair = 2,

        /** BR 4-pair */
        Br4Pair = 3
    };

    /** pairs */
    Pairs pairs;

    /** hardware channel */
    BYTE hardwareChannel;

    /**
     * @brief Bitrate in [kbit/sec]
     */
    DWORD bitrate;
};

}
}
