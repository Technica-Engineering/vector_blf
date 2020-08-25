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
 * @brief A429_ERROR
 *
 * A429 error object
 */
struct VECTOR_BLF_EXPORT A429Error final : ObjectHeader {
    A429Error();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /** application channel */
    uint16_t channel {};

    /** error type, 0=error, 1=warning, 2=info */
    uint16_t errorType {};

    /** source identifier */
    uint32_t sourceIdentifier {};

    /** error reason */
    uint32_t errReason {};

    /** error text */
    std::array<char, 512> errorText {};

    /** error attributes */
    std::array<char, 512> errorAttributes {};

    /** reserved */
    uint32_t reservedA429Error {};
};

}
}
