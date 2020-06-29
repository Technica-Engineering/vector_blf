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

#include <Vector/BLF/LinBusEvent.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief LIN_UNEXPECTED_WAKEUP
 *
 * This event occurs if an unexpected byte received in bus idle phase of wake mode
 * could be a wakeup frame
 */
struct VECTOR_BLF_EXPORT LinUnexpectedWakeup final : ObjectHeader, LinBusEvent {
    LinUnexpectedWakeup();

    std::vector<uint8_t>::iterator fromData(std::vector<uint8_t>::iterator it) override;
    void toData(std::vector<uint8_t> & data) override;
    DWORD calculateObjectSize() const override;

    /**
     * @brief width of the unexpected wakeup in nanoseconds (valid for LIN 2.x)
     *
     * Width of the unexpected wakeup in nanoseconds.
     * Valid for LIN 2.x
     */
    ULONGLONG width {};

    /**
     * @brief byte signal of the unexpected wakeup (valid for LIN 1.x)
     *
     * Byte signal of the unexpected wakeup. Valid for
     * LIN 1.x
     */
    BYTE signal {};

    /** reserved */
    BYTE reservedLinUnexpectedWakeup1 {};

    /** reserved */
    WORD reservedLinUnexpectedWakeup2 {};

    /** reserved */
    DWORD reservedLinUnexpectedWakeup3 {};

    // @note might be extended in future versions
};

}
}
