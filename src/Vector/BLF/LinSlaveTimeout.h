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
 * @brief LIN_SLV_TIMEOUT
 *
 * This event occurs on a timeout in Final State Machine defined on LIN Hardware via
 * CAPL. The technology of Final State Machine on LIN Hardware is still supported, but it is
 * obsolete.
 */
struct VECTOR_BLF_EXPORT LinSlaveTimeout final : ObjectHeader {
    LinSlaveTimeout();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief application channel
     *
     * Channel number where the event notified
     */
    uint16_t channel {};

    /**
     * Slave Identifier in the Final State Machine
     */
    uint8_t slaveId {};

    /**
     * Source state identifier of a Slave in the Final
     * State Machine
     */
    uint8_t stateId {};

    /**
     * Target state identifier of a Slave in the Final
     * State Machine
     */
    uint32_t followStateId {};
};

}
}
