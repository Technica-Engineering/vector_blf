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
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief MOST_LIGHTLOCK
 *
 * This event refers to the optical or electrical modulated signal at the transceiver's Rx.
 *
 * "Signal On" means that a modulated signal has been detected.
 *
 * "Lock" means that the receiver PLL (Phase Locked Loop) was able to establish synchronization
 * with the phase of the modulated signal (to "lock").
 *
 * "Stable Lock" means that for a certain period of time no unlock occurred (see MOST
 * specification).
 *
 * In case of a series of unlocks, the time of the different unlocks are accumulated. If this accumulated
 * time is greater than a certain threshold, it is called "Critical Unlock" (details see MOST
 * specification).
 */
struct VECTOR_BLF_EXPORT MostLightLock final : ObjectHeader {
    MostLightLock();

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
     * Signal state:
     *   - 0x01 – Signal On + Lock
     *   - 0x02 – Signal Off (implies No Lock)
     *   - 0x03 – Signal On + No Lock
     *   - 0x10 – Stable Lock
     *   - 0x20 – Critical Unlock
     */
    int16_t state {};

    /** reserved */
    uint32_t reservedMostLightLock {};
};

}
}
