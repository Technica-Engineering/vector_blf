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

#include "VectorTypes.h"
#include "ObjectHeader.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief ETHERNET_STATUS
 *
 * Ethernet status.
 */
class VECTOR_BLF_EXPORT EthernetStatus : public ObjectHeader
{
public:
    EthernetStatus();

    virtual char * parse(char * buffer);
    virtual size_t calculateObjectSize();

    /**
     * The channel of the event.
     */
    WORD channel;

    enumclass Flags : WORD {
        /** Link Status */
        LinkStatus = 0x0001,

        /** Bit rate */
        Bitrate = 0x0002,

        /** Ethernet Phy */
        EthernetPhy = 0x0004,

        /** Duplex */
        Duplex = 0x0008,

        /** MDI Type */
        MDIType = 0x0010,

        /** Connector */
        Connector = 0x0020,

        /** Clock Mode */
        ClockMode = 0x0040,

        /** BroadR-Reach Pair */
        BroadRReachPair = 0x0080
    };
    WORD flags;

    /**
     * @brief Link Status
     */
    enumclass LinkStatus : BYTE {
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
    } linkStatus;

    /**
     * @brief Ethernet Phy
     */
    enumclass EthernetPhy : BYTE {
        /** Unknown */
        UnknownEthernetPhy = 0,

        /** IEEE 802.3 */
        Ieee802_3 = 1,

        /** BroadR-Reach */
        BroadR_Reach = 2
    } ethernetPhy;

    /**
     * @brief Duplex
     */
    enumclass Duplex : BYTE {
        /** Unknown */
        UnknownDuplex = 0,

        /** Half Duplex */
        HalfDuplex = 1,

        /** Full Duplex */
        FullDuplex = 2
    } duplex;

    enumclass Mdi : BYTE {
        /** Unknown */
        UnknownMdi = 0,

        /** Direct */
        Direct = 1,

        /** Crossover */
        Crossover = 2
    } mdi;

    enumclass Connector : BYTE {
        /** Unknown */
        UnknownConnector = 0,

        /** RJ45*/
        Rj45 = 1,

        /** D-Sub */
        DSub = 2
    } connector;

    enumclass ClockMode : BYTE {
        /** Unknown */
        UnknownClockMode = 0,

        /** Master */
        Master = 1,

        /** Slave */
        Slave = 2
    } clockMode;

    enumclass Pairs : BYTE {
        /** Unknown */
        UnknownPairs = 0,

        /** BR 1-pair */
        Br1Pair = 1,

        /** BR 2-pair */
        Br2Pair = 2,

        /** BR 4-pair */
        Br4Pair = 3
    } pairs;

    /** reserved */
    BYTE reserved;

    /**
     * @brief Bitrate in [kbit/sec]
     */
    DWORD bitrate;
};

}
}
