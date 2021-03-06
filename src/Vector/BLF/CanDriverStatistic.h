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
 * @brief CAN_STATISTIC
 *
 * CAN driver statistic data for a CAN channel.
 */
struct VECTOR_BLF_EXPORT CanDriverStatistic final : ObjectHeader {
    CanDriverStatistic();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief application channel
     *
     * CAN channel the statistic data belongs to.
     */
    uint16_t channel {};

    /**
     * @brief CAN bus load
     *
     * Busload in 1/100 percent (e.g. 100 means
     * 1%)
     */
    uint16_t busLoad {};

    /**
     * @brief standard CAN id data frames
     *
     * Number of standard data frames sent on
     * that channel.
     */
    uint32_t standardDataFrames {};

    /**
     * @brief extended CAN id data frames
     *
     * Number of extended data frames sent on
     * that channel.
     */
    uint32_t extendedDataFrames {};

    /**
     * @brief standard CAN id remote frames
     *
     * Number of remote data frames sent on that
     * channel.
     */
    uint32_t standardRemoteFrames {};

    /**
     * @brief extented CAN id remote frames
     *
     * Number of extended remote data frames
     * sent on that channel.
     */
    uint32_t extendedRemoteFrames {};

    /**
     * @brief CAN error frames
     *
     * Number of error frams sent on that channel
     */
    uint32_t errorFrames {};

    /**
     * @brief CAN overload frames
     *
     * Number of overload frams sent on that
     * channel.
     */
    uint32_t overloadFrames {};

    /** reserved */
    uint32_t reservedCanDriverStatistic {};
};

}
}
