/*
 * Copyright (C) 2013 Tobias Lorenz.
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

#include "platform.h"

#include <array>

#include "AbstractFile.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief CAN_STATISTIC
 *
 * CAN driver statistic data for a CAN channel.
 */
class VECTOR_BLF_EXPORT CanDriverStatistic : public ObjectHeader
{
public:
    CanDriverStatistic();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * CAN channel the statistic data belongs to.
     */
    WORD channel;

    /**
     * @brief CAN bus load
     *
     * Busload in 1/100 percent (e.g. 100 means
     * 1%)
     */
    WORD busLoad;

    /**
     * @brief standard CAN id data frames
     *
     * Number of standard data frames sent on
     * that channel.
     */
    DWORD standardDataFrames;

    /**
     * @brief extended CAN id data frames
     *
     * Number of extended data frames sent on
     * that channel.
     */
    DWORD extendedDataFrames;

    /**
     * @brief standard CAN id remote frames
     *
     * Number of remote data frames sent on that
     * channel.
     */
    DWORD standardRemoteFrames;

    /**
     * @brief extented CAN id remote frames
     *
     * Number of extended remote data frames
     * sent on that channel.
     */
    DWORD extendedRemoteFrames;

    /**
     * @brief CAN error frames
     *
     * Number of error frams sent on that channel
     */
    DWORD errorFrames;

    /**
     * @brief CAN overload frames
     *
     * Number of overload frams sent on that
     * channel.
     */
    DWORD overloadFrames;

    /** reserved */
    std::array<BYTE, 4> reserved;
};

}
}
