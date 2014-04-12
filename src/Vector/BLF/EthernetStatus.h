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
class EthernetStatus : public ObjectHeader
{
public:
    EthernetStatus();

    /**
     * The channel of the event.
     */
    WORD channel;

    enumclass Flags : WORD {
        LinkStatus = 0x0001, /**< Link Status */
        Bitrate = 0x0002, /**< Bit rate */
        EthernetPhy = 0x0004, /**< Ethernet Phy */
        Duplex = 0x0008, /**< Duplex */
        MDIType = 0x0010, /**< MDI Type */
        Connector = 0x0020, /**< Connector */
        ClockMode = 0x0040, /**< Clock Mode */
        BroadRReachPair = 0x0080 /**< BroadR-Reach Pair */
    };
    WORD flags;

    /**
     * @brief Link Status
     */
    enumclass LinkStatus : BYTE {
        UnknownLinkStatus = 0, /**< Unknown */
        LinkDown = 1, /**< Link down */
        LinkUp = 2, /**< Link up */
        Negotiate = 3, /**< Negotiate */
        LinkError = 4 /**< Link error */
    } linkStatus;

    /**
     * @brief Ethernet Phy
     */
    enumclass EthernetPhy : BYTE {
        UnknownEthernetPhy = 0, /**< Unknown */
        Ieee802_3 = 1, /**< IEEE 802.3 */
        BroadR_Reach = 2 /**< BroadR-Reach */
    } ethernetPhy;


    /**
     * @brief Duplex
     */
    enumclass Duplex : BYTE {
        UnknownDuplex = 0, /**< Unknown */
        HalfDuplex = 1, /**< Half Duplex */
        FullDuplex = 2 /**< Full Duplex */
    } duplex;

    enumclass Mdi : BYTE {
        UnknownMdi = 0, /**< Unknown */
        Direct = 1, /**< Direct */
        Crossover = 2 /**< Crossover */
    } mdi;

    enumclass Connector : BYTE {
        UnknownConnector = 0, /**< Unknown */
        Rj45 = 1, /**< RJ45*/
        DSub = 2 /**< D-Sub */
    } connector;

    enumclass ClockMode : BYTE {
        UnknownClockMode = 0, /**< Unknown */
        Master = 1, /**< Master */
        Slave = 2 /**< Slave */
    } clockMode;

    enumclass Pairs : BYTE {
        UnknownPairs = 0, /**< Unknown */
        Br1Pair = 1, /**< BR 1-pair*/
        Br2Pair = 2, /**< BR 2-pair */
        Br4Pair = 3 /**< BR 4-pair */
    } pairs;

    BYTE reserved;

    /**
     * @brief Bitrate in [kbit/sec]
     */
    DWORD bitrate;
};

}
}
