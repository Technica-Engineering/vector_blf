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

#include <Vector/BLF/Most150PktFragment.h>

namespace Vector {
namespace BLF {

Most150PktFragment::Most150PktFragment() :
    ObjectHeader2(ObjectType::MOST_150_PKT_FRAGMENT) {
}

std::vector<uint8_t>::iterator Most150PktFragment::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader2::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedMost150PktFragment1 =
            (static_cast<BYTE>(*it++) <<  0);
    ackNack =
            (static_cast<BYTE>(*it++) <<  0);
    validMask =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    sourceAdr =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    destAdr =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    pAck =
            (static_cast<BYTE>(*it++) <<  0);
    cAck =
            (static_cast<BYTE>(*it++) <<  0);
    priority =
            (static_cast<BYTE>(*it++) <<  0);
    pIndex =
            (static_cast<BYTE>(*it++) <<  0);
    crc =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    dataLen =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    dataLenAnnounced =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    firstDataLen =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedMost150PktFragment2 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    firstData.resize(firstDataLen);
    std::copy(it, it + firstData.size(), std::begin(firstData));
    it += firstData.size();

    return it;
}

void Most150PktFragment::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    firstDataLen = static_cast<DWORD>(firstData.size());

    ObjectHeader2::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((reservedMost150PktFragment1 >>  0) & 0xff);
    data.push_back((ackNack >>  0) & 0xff);
    data.push_back((validMask >>  0) & 0xff);
    data.push_back((validMask >>  8) & 0xff);
    data.push_back((validMask >> 16) & 0xff);
    data.push_back((validMask >> 24) & 0xff);
    data.push_back((sourceAdr >>  0) & 0xff);
    data.push_back((sourceAdr >>  8) & 0xff);
    data.push_back((sourceAdr >> 16) & 0xff);
    data.push_back((sourceAdr >> 24) & 0xff);
    data.push_back((destAdr >>  0) & 0xff);
    data.push_back((destAdr >>  8) & 0xff);
    data.push_back((destAdr >> 16) & 0xff);
    data.push_back((destAdr >> 24) & 0xff);
    data.push_back((pAck >>  0) & 0xff);
    data.push_back((cAck >>  0) & 0xff);
    data.push_back((priority >>  0) & 0xff);
    data.push_back((pIndex >>  0) & 0xff);
    data.push_back((crc >>  0) & 0xff);
    data.push_back((crc >>  8) & 0xff);
    data.push_back((crc >> 16) & 0xff);
    data.push_back((crc >> 24) & 0xff);
    data.push_back((dataLen >>  0) & 0xff);
    data.push_back((dataLen >>  8) & 0xff);
    data.push_back((dataLen >> 16) & 0xff);
    data.push_back((dataLen >> 24) & 0xff);
    data.push_back((dataLenAnnounced >>  0) & 0xff);
    data.push_back((dataLenAnnounced >>  8) & 0xff);
    data.push_back((dataLenAnnounced >> 16) & 0xff);
    data.push_back((dataLenAnnounced >> 24) & 0xff);
    data.push_back((firstDataLen >>  0) & 0xff);
    data.push_back((firstDataLen >>  8) & 0xff);
    data.push_back((firstDataLen >> 16) & 0xff);
    data.push_back((firstDataLen >> 24) & 0xff);
    data.push_back((reservedMost150PktFragment2 >>  0) & 0xff);
    data.push_back((reservedMost150PktFragment2 >>  8) & 0xff);
    data.push_back((reservedMost150PktFragment2 >> 16) & 0xff);
    data.push_back((reservedMost150PktFragment2 >> 24) & 0xff);
    data.insert(std::end(data), std::begin(firstData), std::end(firstData));
}

DWORD Most150PktFragment::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reservedMost150PktFragment1) +
        sizeof(ackNack) +
        sizeof(validMask) +
        sizeof(sourceAdr) +
        sizeof(destAdr) +
        sizeof(pAck) +
        sizeof(cAck) +
        sizeof(priority) +
        sizeof(pIndex) +
        sizeof(crc) +
        sizeof(dataLen) +
        sizeof(dataLenAnnounced) +
        sizeof(firstDataLen) +
        sizeof(reservedMost150PktFragment2) +
        firstDataLen;
}

}
}
