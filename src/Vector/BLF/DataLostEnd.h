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
 * @brief DATA_LOST_END
 */
struct VECTOR_BLF_EXPORT DataLostEnd final : ObjectHeader {
    DataLostEnd();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /** enumeration for queueIdentifier */
    enum QueueIdentifier : uint32_t {
        RtQueue = 0,
        AnlyzQueue = 1,
        RtAndAnlyzQueue = 2
    };

    /** identifier for the leaking queue */
    uint32_t queueIdentifier {};

    /** timestamp of the first object lost */
    uint64_t firstObjectLostTimeStamp {};

    /** number of lost events */
    uint32_t numberOfLostEvents {};
};

}
}
