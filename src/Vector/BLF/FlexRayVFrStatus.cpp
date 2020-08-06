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

#include <Vector/BLF/FlexRayVFrStatus.h>

#include <algorithm>

namespace Vector {
namespace BLF {

FlexRayVFrStatus::FlexRayVFrStatus() :
    ObjectHeader(ObjectType::FR_STATUS) {
}

std::vector<uint8_t>::iterator FlexRayVFrStatus::fromData(std::vector<uint8_t>::iterator it) {
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
    cycle =
        (static_cast<BYTE>(*it++) <<  0);
    reservedFlexRayVFrStatus1 =
        (static_cast<BYTE>(*it++) <<  0);
    clientIndexFlexRayVFrStatus =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    clusterNo =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    wus =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    ccSyncState =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
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
    std::generate(reservedFlexRayVFrStatus2.begin(), reservedFlexRayVFrStatus2.end(), [&it]() {
        return
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    });

    return it;
}

void FlexRayVFrStatus::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((version >>  0) & 0xff);
    data.push_back((version >>  8) & 0xff);
    data.push_back((channelMask >>  0) & 0xff);
    data.push_back((channelMask >>  8) & 0xff);
    data.push_back((cycle >>  0) & 0xff);
    data.push_back((reservedFlexRayVFrStatus1 >>  0) & 0xff);
    data.push_back((clientIndexFlexRayVFrStatus >>  0) & 0xff);
    data.push_back((clientIndexFlexRayVFrStatus >>  8) & 0xff);
    data.push_back((clientIndexFlexRayVFrStatus >> 16) & 0xff);
    data.push_back((clientIndexFlexRayVFrStatus >> 24) & 0xff);
    data.push_back((clusterNo >>  0) & 0xff);
    data.push_back((clusterNo >>  8) & 0xff);
    data.push_back((clusterNo >> 16) & 0xff);
    data.push_back((clusterNo >> 24) & 0xff);
    data.push_back((wus >>  0) & 0xff);
    data.push_back((wus >>  8) & 0xff);
    data.push_back((wus >> 16) & 0xff);
    data.push_back((wus >> 24) & 0xff);
    data.push_back((ccSyncState >>  0) & 0xff);
    data.push_back((ccSyncState >>  8) & 0xff);
    data.push_back((ccSyncState >> 16) & 0xff);
    data.push_back((ccSyncState >> 24) & 0xff);
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
    std::for_each(reservedFlexRayVFrStatus2.begin(), reservedFlexRayVFrStatus2.end(), [&data](const WORD & d) {
        data.push_back((d >>  0) & 0xff);
        data.push_back((d >>  8) & 0xff);
    });
}

DWORD FlexRayVFrStatus::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(channelMask) +
        sizeof(cycle) +
        sizeof(reservedFlexRayVFrStatus1) +
        sizeof(clientIndexFlexRayVFrStatus) +
        sizeof(clusterNo) +
        sizeof(wus) +
        sizeof(ccSyncState) +
        sizeof(tag) +
        static_cast<DWORD>(data.size() * sizeof(DWORD)) +
        static_cast<DWORD>(reservedFlexRayVFrStatus2.size() * sizeof(WORD));
}

}
}
