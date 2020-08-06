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

#include <Vector/BLF/FlexRayVFrStartCycle.h>

#include <algorithm>

namespace Vector {
namespace BLF {

FlexRayVFrStartCycle::FlexRayVFrStartCycle() :
    ObjectHeader(ObjectType::FR_STARTCYCLE) {
}

std::vector<uint8_t>::iterator FlexRayVFrStartCycle::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    version =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    channelMask =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    dir =
        (static_cast<BYTE>(*it++) <<  0);
    cycle =
        (static_cast<BYTE>(*it++) <<  0);
    clientIndexFlexRayVFrStartCycle =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    clusterNo =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    nmSize =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    std::copy(it, it + dataBytes.size(), std::begin(dataBytes));
    it += dataBytes.size();
    reservedFlexRayVFrStartCycle1 =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    tag =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    std::generate(this->data.begin(), this->data.end(), [&it]() {
        return
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    });
    reservedFlexRayVFrStartCycle2 =
        (static_cast<ULONGLONG>(*it++) <<  0) |
        (static_cast<ULONGLONG>(*it++) <<  8) |
        (static_cast<ULONGLONG>(*it++) << 16) |
        (static_cast<ULONGLONG>(*it++) << 24) |
        (static_cast<ULONGLONG>(*it++) << 32) |
        (static_cast<ULONGLONG>(*it++) << 40) |
        (static_cast<ULONGLONG>(*it++) << 48) |
        (static_cast<ULONGLONG>(*it++) << 56);

    return it;
}

void FlexRayVFrStartCycle::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((version >>  0) & 0xff);
    data.push_back((version >>  8) & 0xff);
    data.push_back((channelMask >>  0) & 0xff);
    data.push_back((channelMask >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((cycle >>  0) & 0xff);
    data.push_back((clientIndexFlexRayVFrStartCycle >>  0) & 0xff);
    data.push_back((clientIndexFlexRayVFrStartCycle >>  8) & 0xff);
    data.push_back((clientIndexFlexRayVFrStartCycle >> 16) & 0xff);
    data.push_back((clientIndexFlexRayVFrStartCycle >> 24) & 0xff);
    data.push_back((clusterNo >>  0) & 0xff);
    data.push_back((clusterNo >>  8) & 0xff);
    data.push_back((clusterNo >> 16) & 0xff);
    data.push_back((clusterNo >> 24) & 0xff);
    data.push_back((nmSize >>  0) & 0xff);
    data.push_back((nmSize >>  8) & 0xff);
    data.insert(std::end(data), std::begin(dataBytes), std::end(dataBytes));
    data.push_back((reservedFlexRayVFrStartCycle1 >>  0) & 0xff);
    data.push_back((reservedFlexRayVFrStartCycle1 >>  8) & 0xff);
    data.push_back((tag >>  0) & 0xff);
    data.push_back((tag >>  8) & 0xff);
    data.push_back((tag >> 16) & 0xff);
    data.push_back((tag >> 24) & 0xff);
    std::for_each(this->data.begin(), this->data.end(), [&data](const DWORD & d) {
        data.push_back((d >>  0) & 0xff);
        data.push_back((d >>  8) & 0xff);
        data.push_back((d >> 16) & 0xff);
        data.push_back((d >> 24) & 0xff);
    });
    data.push_back((reservedFlexRayVFrStartCycle2 >>  0) & 0xff);
    data.push_back((reservedFlexRayVFrStartCycle2 >>  8) & 0xff);
    data.push_back((reservedFlexRayVFrStartCycle2 >> 16) & 0xff);
    data.push_back((reservedFlexRayVFrStartCycle2 >> 24) & 0xff);
    data.push_back((reservedFlexRayVFrStartCycle2 >> 32) & 0xff);
    data.push_back((reservedFlexRayVFrStartCycle2 >> 40) & 0xff);
    data.push_back((reservedFlexRayVFrStartCycle2 >> 48) & 0xff);
    data.push_back((reservedFlexRayVFrStartCycle2 >> 56) & 0xff);
}

DWORD FlexRayVFrStartCycle::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(channelMask) +
        sizeof(dir) +
        sizeof(cycle) +
        sizeof(clientIndexFlexRayVFrStartCycle) +
        sizeof(clusterNo) +
        sizeof(nmSize) +
        static_cast<DWORD>(dataBytes.size()) +
        sizeof(reservedFlexRayVFrStartCycle1) +
        sizeof(tag) +
        static_cast<DWORD>(data.size() * sizeof(DWORD)) +
        sizeof(reservedFlexRayVFrStartCycle2);
}

}
}
