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

#include <Vector/BLF/FlexRayVFrError.h>

#include <algorithm>

namespace Vector {
namespace BLF {

FlexRayVFrError::FlexRayVFrError() :
    ObjectHeader(ObjectType::FR_ERROR) {
}

std::vector<uint8_t>::iterator FlexRayVFrError::fromData(std::vector<uint8_t>::iterator it) {
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
    reservedFlexRayVFrError1 =
        (static_cast<BYTE>(*it++) <<  0);
    clientIndexFlexRayVFrError =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    clusterNo =
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
    reservedFlexRayVFrError2 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);

    return it;
}

void FlexRayVFrError::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((version >>  0) & 0xff);
    data.push_back((version >>  8) & 0xff);
    data.push_back((channelMask >>  0) & 0xff);
    data.push_back((channelMask >>  8) & 0xff);
    data.push_back((cycle >>  0) & 0xff);
    data.push_back((reservedFlexRayVFrError1 >>  0) & 0xff);
    data.push_back((clientIndexFlexRayVFrError >>  0) & 0xff);
    data.push_back((clientIndexFlexRayVFrError >>  8) & 0xff);
    data.push_back((clientIndexFlexRayVFrError >> 16) & 0xff);
    data.push_back((clientIndexFlexRayVFrError >> 24) & 0xff);
    data.push_back((clusterNo >>  0) & 0xff);
    data.push_back((clusterNo >>  8) & 0xff);
    data.push_back((clusterNo >> 16) & 0xff);
    data.push_back((clusterNo >> 24) & 0xff);
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
    data.push_back((reservedFlexRayVFrError2 >>  0) & 0xff);
    data.push_back((reservedFlexRayVFrError2 >>  8) & 0xff);
    data.push_back((reservedFlexRayVFrError2 >> 16) & 0xff);
    data.push_back((reservedFlexRayVFrError2 >> 24) & 0xff);
}

DWORD FlexRayVFrError::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(channelMask) +
        sizeof(cycle) +
        sizeof(reservedFlexRayVFrError1) +
        sizeof(clientIndexFlexRayVFrError) +
        sizeof(clusterNo) +
        sizeof(tag) +
        static_cast<DWORD>(data.size() * sizeof(DWORD)) +
        sizeof(reservedFlexRayVFrError2);
}

}
}
