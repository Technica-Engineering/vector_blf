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
#include <Vector/BLF/LinSynchFieldEvent.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief LIN_SYN_ERROR2
 *
 * Synchronization errors occur if the LIN hardware cannot synchronize with an external
 * Master. This might happen if the baud rate actually used by the Master deviates by more than 15 %
 * from the baud rate specified by the LIN hardware. In this case the baud rate value should be
 * modified. This error event may also occur if the Master transmits an invalid or corrupted Sync
 * field.
 */
struct VECTOR_BLF_EXPORT LinSyncError2 final : ObjectHeader, LinSynchFieldEvent {
    LinSyncError2();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * Time intervals [in us] detected between the
     * falling signal edges of the Sync field
     */
    std::array<uint16_t, 4> timeDiff {};
};

}
}
