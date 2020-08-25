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

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief FLEXRAY_CYCLE
 *
 * Start of cycle event transmitted by the hardware interface on a FlexRay channel.
 */
struct VECTOR_BLF_EXPORT FlexRayV6StartCycleEvent final : ObjectHeader {
    FlexRayV6StartCycleEvent();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief application channel
     *
     * Application channel
     */
    uint16_t channel {};

    /**
     * @brief dir flag (tx, rx)
     *
     * Direction Flags
     *   - 0 = Rx
     *   - 1 = Tx
     *   - 2 = Tx Request
     *   - 3 and 4 are for internal use only.
     */
    uint8_t dir {};

    /**
     * @brief additional time field in simulation
     *
     * Additional time field in simulation
     */
    uint8_t lowTime {};

    /**
     * @brief timestamp generated from xModule
     *
     * Timestamp generated from xModule
     */
    uint32_t fpgaTick {};

    /**
     * @brief overflow counter of the timestamp
     *
     * Overflow counter of the timestamp
     */
    uint32_t fpgaTickOverflow {};

    /**
     * @brief clientindex of send node
     *
     * Client index of send node. Must be set to 0 if file
     * is written from other applications
     */
    uint32_t clientIndexFlexRayV6StartCycleEvent {};

    /**
     * @brief relative clustertime, from 0 to cyclelength
     *
     * Relative cluster time, from 0 to cycle length
     */
    uint32_t clusterTime {};

    /**
     * @brief array of databytes
     *
     * Array of data bytes
     */
    std::array<uint8_t, 2> dataBytes {};

    /** reserved */
    uint16_t reservedFlexRayV6StartCycleEvent {};
};

}
}
