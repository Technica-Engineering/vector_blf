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

#include "AbstractFile.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief AFDX_STATISTIC
 *
 * AFDX statistic event per virtual link.
 */
class VECTOR_BLF_EXPORT AfdxStatistic : public ObjectHeader
{
public:
    AfdxStatistic();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * The channel of the frame.
     */
    WORD channel;

    /** enumeration for flags */
    enum class Flags : WORD {
        /** Valid Rx/Tx counter */
        ValidRxTxCounter = 0x01,

        /** Valid error counter */
        ValidErrorCounter = 0x02,

        /** Valid VirtualLink ID */
        ValidVlid = 0x04
    };

    /** flags */
    WORD flags;

    /**
     * Number of Rx packets since last
     * statistic event.
     */
    ULONG rxPacketCount;

    /**
     * Number of Rx bytes since last
     * statistic event.
     */
    ULONG rxByteCount;

    /**
     * Number of Tx packets since last
     * statistic event.
     */
    ULONG txPacketCount;

    /**
     * Number of Tx bytes since last
     * statistic event.
     */
    ULONG txByteCount;

    /**
     * Number of collisions since last
     * statistic event.
     */
    ULONG collisionCount;

    /**
     * Number of errors since last statistic
     * event.
     */
    ULONG errorCount;

    /**
     * Number of dropped packet due to
     * redundancy check since last
     * statistic event.
     */
    ULONG statDroppedRedundantPacketCount;

    /**
     * Number of errors found at
     * redundancy check since last
     * statistic event.
     */
    ULONG statRedundantErrorPacketCount;

    /**
     * Number of errors found at integrity
     * check since last statistic event.
     */
    ULONG statIntegrityErrorPacketCount;

    /**
     * Average period of frames on this
     * VL in [msec].
     */
    ULONG statAvrgPeriodMsec;

    /**
     * Average jitter of the time period of
     * frames on this VL in [mysec].
     */
    ULONG statAvrgJitterMysec;

    /**
     * Unique ID assigned to this VL.
     */
    ULONG vlid;

    /**
     * Time period covered by this event
     * in [msec].
     */
    ULONG statDuration;
};

}
}
