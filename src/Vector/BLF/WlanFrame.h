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
 * @brief WLAN_FRAME
 *
 * WLAN frame.
 */
class WlanFrame : public ObjectHeader
{
public:
    WlanFrame();

    virtual void setObjectSize();

    /**
     * @brief application channel 1..n
     *
     * The channel of the frame.
     */
    WORD channel;

    enumclass Flags : WORD {
        GenuineMacHeader = 0x0001 /**< Genuine MAC Header */
    };
    WORD flags;

    /**
     * @brief Direction flag
     *
     * Direction flag
     */
    enumclass Dir : BYTE {
        Rx = 0,
        Tx = 1,
        TxRq = 2
    } dir;

    /**
     * @brief channel number of the radio frequency
     *
     * Channel number of the radio frequency, i.e 180
     * or 176
     */
    BYTE radioChannel;

    /**
     * @brief signal strength in [dbm]
     *
     * Signal strength in [dBm]
     */
    SHORT signalStrength;

    /**
     * @brief signal quality in [dbm]
     *
     * Signal quality
     */
    WORD signalQuality;

    /**
     * @brief Number of bytes (header + payload)
     *
     * Length of WLAN data in bytes. Max. 2342
     * Bytes.
     */
    WORD frameLength;

    /**
     * @brief WLAN frame data
     *
     * WLAN frame data. Data starts with WLAN
     * header.
     * Max. 2342 data bytes per frame
     */
    BYTE* frameData;
};

}
}
