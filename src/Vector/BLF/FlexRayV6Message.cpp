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

#include <Vector/BLF/FlexRayV6Message.h>

namespace Vector {
namespace BLF {

FlexRayV6Message::FlexRayV6Message() :
    ObjectHeader(ObjectType::FLEXRAY_MESSAGE) {
}

std::vector<uint8_t>::iterator FlexRayV6Message::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    dir =
        (static_cast<BYTE>(*it++) <<  0);
    lowTime =
        (static_cast<BYTE>(*it++) <<  0);
    fpgaTick =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    fpgaTickOverflow =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    clientIndexFlexRayV6Message =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    clusterTime =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    frameId =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    headerCrc =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    frameState =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    length =
        (static_cast<BYTE>(*it++) <<  0);
    cycle =
        (static_cast<BYTE>(*it++) <<  0);
    headerBitMask =
        (static_cast<BYTE>(*it++) <<  0);
    reservedFlexRayV6Message1 =
        (static_cast<BYTE>(*it++) <<  0);
    reservedFlexRayV6Message2 =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    std::copy(it, it + dataBytes.size(), std::begin(dataBytes));
    it += dataBytes.size();

    return it;
}

void FlexRayV6Message::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((lowTime >>  0) & 0xff);
    data.push_back((fpgaTick >>  0) & 0xff);
    data.push_back((fpgaTick >>  8) & 0xff);
    data.push_back((fpgaTick >> 16) & 0xff);
    data.push_back((fpgaTick >> 24) & 0xff);
    data.push_back((fpgaTickOverflow >>  0) & 0xff);
    data.push_back((fpgaTickOverflow >>  8) & 0xff);
    data.push_back((fpgaTickOverflow >> 16) & 0xff);
    data.push_back((fpgaTickOverflow >> 24) & 0xff);
    data.push_back((clientIndexFlexRayV6Message >>  0) & 0xff);
    data.push_back((clientIndexFlexRayV6Message >>  8) & 0xff);
    data.push_back((clientIndexFlexRayV6Message >> 16) & 0xff);
    data.push_back((clientIndexFlexRayV6Message >> 24) & 0xff);
    data.push_back((clusterTime >>  0) & 0xff);
    data.push_back((clusterTime >>  8) & 0xff);
    data.push_back((clusterTime >> 16) & 0xff);
    data.push_back((clusterTime >> 24) & 0xff);
    data.push_back((frameId >>  0) & 0xff);
    data.push_back((frameId >>  8) & 0xff);
    data.push_back((headerCrc >>  0) & 0xff);
    data.push_back((headerCrc >>  8) & 0xff);
    data.push_back((frameState >>  0) & 0xff);
    data.push_back((frameState >>  8) & 0xff);
    data.push_back((length >>  0) & 0xff);
    data.push_back((cycle >>  0) & 0xff);
    data.push_back((headerBitMask >>  0) & 0xff);
    data.push_back((reservedFlexRayV6Message1 >>  0) & 0xff);
    data.push_back((reservedFlexRayV6Message2 >>  0) & 0xff);
    data.push_back((reservedFlexRayV6Message2 >>  8) & 0xff);
    data.insert(std::end(data), std::begin(dataBytes), std::end(dataBytes));
}

DWORD FlexRayV6Message::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(lowTime) +
        sizeof(fpgaTick) +
        sizeof(fpgaTickOverflow) +
        sizeof(clientIndexFlexRayV6Message) +
        sizeof(clusterTime) +
        sizeof(frameId) +
        sizeof(headerCrc) +
        sizeof(frameState) +
        sizeof(length) +
        sizeof(cycle) +
        sizeof(headerBitMask) +
        sizeof(reservedFlexRayV6Message1) +
        sizeof(reservedFlexRayV6Message2) +
        static_cast<DWORD>(dataBytes.size());
}

}
}
