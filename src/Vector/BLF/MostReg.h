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
#include <Vector/BLF/ObjectHeader2.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief MOST_REG
 *
 * This event transports a register read or write result (e.g. reading the routing engine of
 * the OS8104). Unlike the special register event (MostGenReg) this event does not occur
 * spontaneous.
 */
struct VECTOR_BLF_EXPORT MostReg final : ObjectHeader2 {
    MostReg();

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
     * @brief read/write request/result
     *
     * Operation type of a register event.
     *   - Unspecified = 0: unspecified (or HW does not support sub types)
     *   - Notify = 1: notification on register change (spontaneous)
     *   - ReadRequest = 2: request of a register read operation
     *   - WriteRequest = 3: request of a register write operation
     *   - ReadResult = 4: result of a register read operation
     *   - WriteResult = 5: result of a register write operation
     *   - ReadFailed = 6: register read operation failed
     *   - WriteFailed = 7: register write operation failed
     */
    uint8_t subType {};

    /** reserved */
    uint8_t reservedMostReg {};

    /**
     * @brief operation handle
     *
     * Operation handle (obsolete; write 0)
     */
    uint32_t handle {};

    /**
     * @brief start address
     *
     * Register address offset
     */
    uint32_t offset {};

    /**
     * @brief chip id
     *
     * ID of chip
     *   - 1 – OS8104
     */
    uint16_t chip {};

    /**
     * @brief number of bytes
     *
     * Number of valid bytes in regData
     */
    uint16_t regDataLen {};

    /**
     * @brief data bytes
     *
     * Register data
     */
    std::array<uint8_t, 16> regData {};
};

}
}
