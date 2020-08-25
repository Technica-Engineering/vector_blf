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
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief AFDX_STATISTIC
 *
 * AFDX statistic event per virtual link.
 * AFDX combined bus- and VL- statistic event; used before 8.2
 */
struct VECTOR_BLF_EXPORT AfdxStatistic final : ObjectHeader {
    AfdxStatistic();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    DWORD calculateObjectSize() const override;

    /**
     * @brief application channel
     *
     * The channel of the frame.
     */
    WORD channel {};

    /** enumeration for flags */
    enum Flags : WORD {
        /** channel is configured */
        ChannelIsConfigured = 0x0001,

        /** HW related counters valid */
        HwRelatedCountersValid = 0x0002,

        /** CANwin related counters are valid */
        CanWinRelatedCountersAreValid = 0x0004,

        /** link-related info is valid */
        LinkRelatedInfoIsValud = 0x0008,

        /** invalid packet counter is valid */
        InvalidPacketCounterIsValid = 0x0010,

        /** lost packet counter is valid */
        LostPacketCounterIsValud = 0x0020,

        /** dropped packet counter is valid */
        DroppedPacketCounterIsValid = 0x0040,

        /** byte counters are based on CANwin packets, not HW */
        ByteCountersAreBasedOnCanWinPackets = 0x0080
    };

    /** flags */
    WORD flags {};

    /**
     * Number of Rx packets since last
     * statistic event.
     */
    ULONG rxPacketCount {};

    /**
     * Number of Rx bytes since last
     * statistic event.
     */
    ULONG rxByteCount {};

    /**
     * Number of Tx packets since last
     * statistic event.
     */
    ULONG txPacketCount {};

    /**
     * Number of Tx bytes since last
     * statistic event.
     */
    ULONG txByteCount {};

    /**
     * Number of collisions since last
     * statistic event.
     */
    ULONG collisionCount {};

    /**
     * Number of errors since last statistic
     * event.
     */
    ULONG errorCount {};

    /**
     * Number of dropped packet due to
     * redundancy check since last
     * statistic event.
     */
    ULONG statDroppedRedundantPacketCount {};

    /**
     * Number of errors found at
     * redundancy check since last
     * statistic event.
     */
    ULONG statRedundantErrorPacketCount {};

    /**
     * Number of errors found at integrity
     * check since last statistic event.
     */
    ULONG statIntegrityErrorPacketCount {};

    /**
     * Average period of frames on this
     * VL in [msec].
     */
    ULONG statAvrgPeriodMsec {};

    /**
     * Average jitter of the time period of
     * frames on this VL in [mysec].
     */
    ULONG statAvrgJitterMysec {};

    /**
     * Unique ID assigned to this VL.
     */
    ULONG vlid {};

    /**
     * Time period covered by this event
     * in [msec].
     */
    ULONG statDuration {};
};

}
}
