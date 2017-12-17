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

#include <Vector/BLF/platform.h>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief AFDX_BUS_STATISTIC
 *
 * AFDX line-specific bus-statistic event used since 8.2
 */
class VECTOR_BLF_EXPORT AfdxBusStatistic final : public ObjectHeader
{
public:
    AfdxBusStatistic();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /**
     * @brief application channel
     */
    WORD channel;

    /**
     * @brief Bit0=Valid Rx/Tx Counter, Bit1=Valid Error Counter; Bit2=Valid VLId
     */
    WORD flags;

    /**
     * @brief real time period in mysec of statistic datacollection
     */
    ULONG statDuration;

    /* bus-specific info */

    /**
     * @brief read frames taken from hardware, i.e. on bus
     */
    ULONG statRxPacketCountHW;

    /**
     * @brief send frames as taken from hardware, i.e. on bus
     */
    ULONG statTxPacketCountHW;

    /**
     * @brief number of erronous Rx-frames detected by HW
     */
    ULONG statRxErrorCountHW;

    /**
     * @brief number of erronous Tx-frames detected by HW
     */
    ULONG statTxErrorCountHW;

    /**
     * @brief bytes received by HW during this time period
     */
    ULONG statRxBytesHW;

    /**
     * @brief bytes sent by HW during this time period
     */
    ULONG statTxBytesHW;

    /* CANwin specific info */

    /**
     * @brief received frames within CANwin
     */
    ULONG statRxPacketCount;

    /**
     * @brief send packets from within CANwin
     */
    ULONG statTxPacketCount;

    /**
     * @brief number of packets aktively dropped by CANwin
     */
    ULONG statDroppedPacketCount;

    /**
     * @brief number of packets with incompatible eth-header regarding AFDX-spec
     */
    ULONG statInvalidPacketCount;

    /**
     * @brief number of packets lost by CABwin due to queue overflow etc
     */
    ULONG statLostPacketCount;

    /* connection related info */

    /**
     * @brief lineA (0) or lineB (1)
     */
    BYTE line;

    /**
     * @brief status of adapter as per EthernetStatus
     */
    BYTE linkStatus;

    /**
     * @brief link speed: 0:=10mbps 1:=100mbps 2:=1000mbps
     */
    WORD linkSpeed;

    /**
     * @brief counter of link-losses during this period
     */
    WORD linkLost;

    /** reserved */
    WORD reservedAfdxBusStatistic1;

    /** reserved */
    DWORD reservedAfdxBusStatistic2;
};

}
}
