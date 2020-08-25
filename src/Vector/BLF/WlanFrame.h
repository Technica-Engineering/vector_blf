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
 * @brief WLAN_FRAME
 *
 * WLAN frame.
 */
struct VECTOR_BLF_EXPORT WlanFrame final : ObjectHeader {
    WlanFrame();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief application channel 1..n
     *
     * The channel of the frame.
     */
    uint16_t channel {};

    /** enumeration for flags */
    enum Flags : uint16_t {
        /** Genuine MAC Header */
        GenuineMacHeader = 0x0001,

        /** Correct Frame Control Format */
        CorrectFrameControlFormat = 0x0002,
    };

    /** flags */
    uint16_t flags {};

    /** enumeration for dir */
    enum Dir : uint8_t {
        /** receive */
        Rx = 0,

        /** transmit */
        Tx = 1,

        /** transmit request */
        TxRq = 2
    };

    /**
     * @brief Direction flag
     *
     * Direction flag
     */
    uint8_t dir {};

    /**
     * @brief channel number of the radio frequency
     *
     * Channel number of the radio frequency, i.e 180
     * or 176
     */
    uint8_t radioChannel {};

    /**
     * @brief signal strength in [dbm]
     *
     * Signal strength in [dBm]
     */
    int16_t signalStrength {};

    /**
     * @brief signal quality in [dbm]
     *
     * Signal quality
     */
    uint16_t signalQuality {};

    /**
     * @brief Number of bytes (header + payload)
     *
     * Length of WLAN data in bytes. Max. 2342
     * Bytes.
     */
    uint16_t frameLength {};

    /** reserved */
    uint32_t reservedWlanFrame {};

    /**
     * @brief WLAN frame data
     *
     * WLAN frame data. Data starts with WLAN
     * header.
     * Max. 2342 data bytes per frame
     */
    std::vector<uint8_t> frameData {};
};

}
}
