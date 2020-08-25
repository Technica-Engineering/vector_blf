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
 * @brief FLEXRAY_SYNC
 *
 * @deprecated
 */
struct VECTOR_BLF_EXPORT FlexRaySync final : ObjectHeader {
    FlexRaySync();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief application channel
     */
    uint16_t channel {};

    /** multiplexer */
    uint8_t mux {};

    /** length */
    uint8_t len {};

    /** message id */
    uint16_t messageId {};

    /** CRC */
    uint16_t crc {};

    /** direction */
    uint8_t dir {};

    /** reserved */
    uint8_t reservedFlexRaySync1 {};

    /** reserved */
    uint16_t reservedFlexRaySync2 {};

    /** data bytes */
    std::array<uint8_t, 11> dataBytes {};

    /** cycle */
    uint8_t cycle {};
};

}
}
