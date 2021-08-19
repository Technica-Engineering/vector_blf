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
#include <vector>

#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief UNKNOWN_115
 *
 * These objects store a contiguous block of data containing the Restore
 * Points, similar to what a LogContainer does for Log data.
 *
 * The default dataLength is 2000, which results in an objectSize of 2048.
 *
 * @note
 *   This class is based on observations, as there is no
 *   public documentation available. There are undocumented API functions for
 *   RestorePoint handling. And this seems like it.
 */
struct VECTOR_BLF_EXPORT RestorePointContainer final : public ObjectHeader {
    RestorePointContainer();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /** reserved */
    std::array<uint8_t, 14> reservedRestorePointContainer {};

    /** restore point data size */
    uint16_t dataLength {};

    /** restore point data */
    std::vector<uint8_t> data {};
};

}
}
