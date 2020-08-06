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

#include <Vector/BLF/AfdxBusStatistic.h>

namespace Vector {
namespace BLF {

AfdxBusStatistic::AfdxBusStatistic() :
    ObjectHeader(ObjectType::A429_BUS_STATISTIC) {
}

std::vector<uint8_t>::iterator AfdxBusStatistic::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    flags =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    statDuration =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statRxPacketCountHW =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statTxPacketCountHW =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statRxErrorCountHW =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statTxErrorCountHW =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statRxBytesHW =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statTxBytesHW =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statRxPacketCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statTxPacketCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statDroppedPacketCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statInvalidPacketCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statLostPacketCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    line =
        (static_cast<BYTE>(*it++) <<  0);
    linkStatus =
        (static_cast<BYTE>(*it++) <<  0);
    linkSpeed =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    linkLost =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedAfdxBusStatistic1 =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedAfdxBusStatistic2 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);

    return it;
}

void AfdxBusStatistic::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((flags >>  0) & 0xff);
    data.push_back((flags >>  8) & 0xff);
    data.push_back((statDuration >>  0) & 0xff);
    data.push_back((statDuration >>  8) & 0xff);
    data.push_back((statDuration >> 16) & 0xff);
    data.push_back((statDuration >> 24) & 0xff);
    data.push_back((statRxPacketCountHW >>  0) & 0xff);
    data.push_back((statRxPacketCountHW >>  8) & 0xff);
    data.push_back((statRxPacketCountHW >> 16) & 0xff);
    data.push_back((statRxPacketCountHW >> 24) & 0xff);
    data.push_back((statTxPacketCountHW >>  0) & 0xff);
    data.push_back((statTxPacketCountHW >>  8) & 0xff);
    data.push_back((statTxPacketCountHW >> 16) & 0xff);
    data.push_back((statTxPacketCountHW >> 24) & 0xff);
    data.push_back((statRxErrorCountHW >>  0) & 0xff);
    data.push_back((statRxErrorCountHW >>  8) & 0xff);
    data.push_back((statRxErrorCountHW >> 16) & 0xff);
    data.push_back((statRxErrorCountHW >> 24) & 0xff);
    data.push_back((statTxErrorCountHW >>  0) & 0xff);
    data.push_back((statTxErrorCountHW >>  8) & 0xff);
    data.push_back((statTxErrorCountHW >> 16) & 0xff);
    data.push_back((statTxErrorCountHW >> 24) & 0xff);
    data.push_back((statRxBytesHW >>  0) & 0xff);
    data.push_back((statRxBytesHW >>  8) & 0xff);
    data.push_back((statRxBytesHW >> 16) & 0xff);
    data.push_back((statRxBytesHW >> 24) & 0xff);
    data.push_back((statTxBytesHW >>  0) & 0xff);
    data.push_back((statTxBytesHW >>  8) & 0xff);
    data.push_back((statTxBytesHW >> 16) & 0xff);
    data.push_back((statTxBytesHW >> 24) & 0xff);
    data.push_back((statRxPacketCount >>  0) & 0xff);
    data.push_back((statRxPacketCount >>  8) & 0xff);
    data.push_back((statRxPacketCount >> 16) & 0xff);
    data.push_back((statRxPacketCount >> 24) & 0xff);
    data.push_back((statTxPacketCount >>  0) & 0xff);
    data.push_back((statTxPacketCount >>  8) & 0xff);
    data.push_back((statTxPacketCount >> 16) & 0xff);
    data.push_back((statTxPacketCount >> 24) & 0xff);
    data.push_back((statDroppedPacketCount >>  0) & 0xff);
    data.push_back((statDroppedPacketCount >>  8) & 0xff);
    data.push_back((statDroppedPacketCount >> 16) & 0xff);
    data.push_back((statDroppedPacketCount >> 24) & 0xff);
    data.push_back((statInvalidPacketCount >>  0) & 0xff);
    data.push_back((statInvalidPacketCount >>  8) & 0xff);
    data.push_back((statInvalidPacketCount >> 16) & 0xff);
    data.push_back((statInvalidPacketCount >> 24) & 0xff);
    data.push_back((statLostPacketCount >>  0) & 0xff);
    data.push_back((statLostPacketCount >>  8) & 0xff);
    data.push_back((statLostPacketCount >> 16) & 0xff);
    data.push_back((statLostPacketCount >> 24) & 0xff);
    data.push_back((line >>  0) & 0xff);
    data.push_back((linkStatus >>  0) & 0xff);
    data.push_back((linkSpeed >>  0) & 0xff);
    data.push_back((linkSpeed >>  8) & 0xff);
    data.push_back((linkLost >>  0) & 0xff);
    data.push_back((linkLost >>  8) & 0xff);
    data.push_back((reservedAfdxBusStatistic1 >>  0) & 0xff);
    data.push_back((reservedAfdxBusStatistic1 >>  8) & 0xff);
    data.push_back((reservedAfdxBusStatistic2 >>  0) & 0xff);
    data.push_back((reservedAfdxBusStatistic2 >>  8) & 0xff);
    data.push_back((reservedAfdxBusStatistic2 >> 16) & 0xff);
    data.push_back((reservedAfdxBusStatistic2 >> 24) & 0xff);
}

DWORD AfdxBusStatistic::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(statDuration) +
        sizeof(statRxPacketCountHW) +
        sizeof(statTxPacketCountHW) +
        sizeof(statRxErrorCountHW) +
        sizeof(statTxErrorCountHW) +
        sizeof(statRxBytesHW) +
        sizeof(statTxBytesHW) +
        sizeof(statRxPacketCount) +
        sizeof(statTxPacketCount) +
        sizeof(statDroppedPacketCount) +
        sizeof(statInvalidPacketCount) +
        sizeof(statLostPacketCount) +
        sizeof(line) +
        sizeof(linkStatus) +
        sizeof(linkSpeed) +
        sizeof(linkLost) +
        sizeof(reservedAfdxBusStatistic1) +
        sizeof(reservedAfdxBusStatistic2);
}

}
}
