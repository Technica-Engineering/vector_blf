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

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader2.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief MOST_DATALOST
 *
 * Indicates loss of data. (Number of lost messages and start and end time stamp of data
 * loss.)
 */
struct VECTOR_BLF_EXPORT MostDataLost final : ObjectHeader2 {
    MostDataLost();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief application channel
     *
     * Application channel
     */
    uint16_t channel {};

    /** reserved */
    uint16_t reservedMostDataLost {};

    /**
     * @brief info about data loss
     *
     * Data loss information
     *   - Bit0: 1: data loss on control channel (spy)
     *   - Bit1: 1: data loss on control channel (node)
     *   - Bit2: 1: data loss on asynchronous channel
     *     (spy)
     *   - Bit3: 1: data loss on asynchronous channel
     *     (node)
     *   - Bit4: 1: data loss on synchronous channel
     *   - Bit5: 1: data loss since driver queue full
     */
    uint32_t info {};

    /**
     * Number of lost messages on Control channel
     */
    uint32_t lostMsgsCtrl {};

    /**
     * Number of lost messages on Packet Data
     * Channel channel
     */
    uint32_t lostMsgsAsync {};

    /**
     * Absolute time in nano-seconds
     */
    uint64_t lastGoodTimeStampNs {};

    /**
     * Absolute time in nano-seconds
     */
    uint64_t nextGoodTimeStampNs {};
};

}
}
