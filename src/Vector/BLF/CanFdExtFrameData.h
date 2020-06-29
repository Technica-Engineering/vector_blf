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

#include <vector>

#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/** optional information in CanFdMessage64 and CanFdErrorFrame64 classes */
struct VECTOR_BLF_EXPORT CanFdExtFrameData {
    virtual ~CanFdExtFrameData() noexcept = default;

    /** @copydoc ObjectHeaderBase::fromData() */
    virtual std::vector<uint8_t>::iterator fromData(std::vector<uint8_t>::iterator it);

    /** @copydoc ObjectHeaderBase::toData() */
    virtual void toData(std::vector<uint8_t> & data);

    /** @copydoc ObjectHeaderBase::calculateObjectSize() */
    virtual DWORD calculateObjectSize() const;

    /**
     * bit rate in arbitration phase
     *
     * - Bit 0-7: TSEG1-1
     * - Bit 8-15: TSEG2-1
     * - Bit 16-27: Prescaler
     * - Bit 28-31: Quartz Frequency (enumeration). Supported values:
     *   - 0: 16 MHz
     *   - 1: 32 MHz
     *   - 2: 80 MHz
     */
    DWORD btrExtArb {};

    /**
     * bit rate in data phase
     *
     * - Bit 0-7: TSEG1-1
     * - Bit 8-15: TSEG2-1
     * - Bit 16-27: Prescaler
     * - Bit 28-31: Quartz Frequency (enumeration). Supported values:
     *   - 0: 16 MHz
     *   - 1: 32 MHz
     *   - 2: 80 MHz
     */
    DWORD btrExtData {};

    /** reserved */
    std::vector<uint8_t> reservedCanFdExtFrameData {};

    // @note might be extended in future versions
};

}
}
