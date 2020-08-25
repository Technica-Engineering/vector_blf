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
 * @brief A429_MESSAGE
 *
 * A429 message object
 */
struct VECTOR_BLF_EXPORT A429Message final : ObjectHeader {
    A429Message();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /** data */
    std::array<uint8_t, 4> a429Data {};

    /** application channel */
    uint16_t channel {};

    /** direction flag: 0=Rx, 1=Tx */
    uint8_t dir {};

    /** reserved */
    uint8_t reservedA429Message1 {};

    /** bitrate */
    uint32_t bitrate {};

    /** error reason */
    int32_t errReason {};

    /** error position */
    uint16_t errPosition {};

    /** reserved */
    uint16_t reservedA429Message2 {};

    /** reserved */
    uint32_t reservedA429Message3 {};

    /** frame gap */
    uint64_t frameGap {};

    /** frame length */
    uint32_t frameLength {};

    /** message control */
    uint16_t msgCtrl {};

    /** reserved */
    uint16_t reservedA429Message4 {};

    /** cycle time */
    uint32_t cycleTime {};

    /** error */
    uint32_t error {};

    /** bit length of last bit */
    uint32_t bitLenOfLastBit {};

    /** reserved */
    uint32_t reservedA429Message5 {};
};

}
}
