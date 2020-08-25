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
 * @brief A429_BUS_STATISTIC
 *
 * A429 bus statistic object
 */
struct VECTOR_BLF_EXPORT A429BusStatistic final : ObjectHeader {
    A429BusStatistic();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /** application channel */
    uint16_t channel {};

    /** direction flag: 0=Rx, 1=Tx */
    uint8_t dir {};

    /** reserved */
    uint8_t reservedA429BusStatistic {};

    /** busload */
    uint32_t busload {};

    /** data total */
    uint32_t dataTotal {};

    /** error total */
    uint32_t errorTotal {};

    /** bitrate */
    uint32_t bitrate {};

    /** parity errors */
    uint16_t parityErrors {};

    /** bitrate errors */
    uint16_t bitrateErrors {};

    /** gap errors */
    uint16_t gapErrors {};

    /** line errors */
    uint16_t lineErrors {};

    /** format errors */
    uint16_t formatErrors {};

    /** duty factor errors */
    uint16_t dutyFactorErrors {};

    /** word length errors */
    uint16_t wordLenErrors {};

    /** coding errors */
    uint16_t codingErrors {};

    /** idle errors */
    uint16_t idleErrors {};

    /** level errors */
    uint16_t levelErrors {};

    /** label count */
    std::array<uint16_t, 256> labelCount {};
};

}
}
