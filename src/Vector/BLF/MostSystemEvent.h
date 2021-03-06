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
 * @brief MOST_SYSTEM_EVENT
 *
 * Event for various system states.
 */
struct VECTOR_BLF_EXPORT MostSystemEvent final : ObjectHeader2 {
    MostSystemEvent();

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
     * @brief identifier of transported data
     *
     * Identification of transported data
     * (enumeration):
     *   - 1 - System Lock (MOST150)
     *   - 2 - Shutdown Flag (MOST150)
     *   - 3 - Shutdown Reason (MOST150)
     */
    uint16_t id {};

    /**
     * @brief current value
     *
     * Current value
     */
    uint32_t value {};

    /**
     * @brief previous value
     *
     * Previous value
     */
    uint32_t valueOld {};

    /** reserved */
    uint32_t reservedMostSystemEvent {};
};

}
}
