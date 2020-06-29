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

#include <Vector/BLF/WlanStatistic.h>

namespace Vector {
namespace BLF {

WlanStatistic::WlanStatistic() :
    ObjectHeader(ObjectType::WLAN_STATISTIC) {
}

std::vector<uint8_t>::iterator WlanStatistic::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    flags =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    rxPacketCount =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8);
    rxByteCount =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8);
    txPacketCount =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8);
    txByteCount =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8);
    collisionCount =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8);
    errorCount =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8);
    reservedWlanStatistic =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);

    return it;
}

void WlanStatistic::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((flags >>  0) & 0xff);
    data.push_back((flags >>  8) & 0xff);
    data.push_back((rxPacketCount >>  0) & 0xff);
    data.push_back((rxPacketCount >>  8) & 0xff);
    data.push_back((rxByteCount >>  0) & 0xff);
    data.push_back((rxByteCount >>  8) & 0xff);
    data.push_back((txPacketCount >>  0) & 0xff);
    data.push_back((txPacketCount >>  8) & 0xff);
    data.push_back((txByteCount >>  0) & 0xff);
    data.push_back((txByteCount >>  8) & 0xff);
    data.push_back((collisionCount >>  0) & 0xff);
    data.push_back((collisionCount >>  8) & 0xff);
    data.push_back((errorCount >>  0) & 0xff);
    data.push_back((errorCount >>  8) & 0xff);
    data.push_back((reservedWlanStatistic >>  0) & 0xff);
    data.push_back((reservedWlanStatistic >>  8) & 0xff);
    data.push_back((reservedWlanStatistic >> 16) & 0xff);
    data.push_back((reservedWlanStatistic >> 24) & 0xff);
}

DWORD WlanStatistic::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(rxPacketCount) +
        sizeof(rxByteCount) +
        sizeof(txPacketCount) +
        sizeof(txByteCount) +
        sizeof(collisionCount) +
        sizeof(errorCount) +
        sizeof(reservedWlanStatistic);
}

}
}
