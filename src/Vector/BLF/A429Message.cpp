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

#include <Vector/BLF/A429Message.h>

namespace Vector {
namespace BLF {

A429Message::A429Message() :
    ObjectHeader(ObjectType::A429_MESSAGE) {
}

std::vector<uint8_t>::iterator A429Message::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    std::copy(it, it + a429Data.size(), std::begin(a429Data));
    it += a429Data.size();
    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    dir =
            (static_cast<BYTE>(*it++) <<  0);
    reservedA429Message1 =
            (static_cast<BYTE>(*it++) <<  0);
    bitrate =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);
    errReason =
            (static_cast<LONG>(*it++) <<  0) |
            (static_cast<LONG>(*it++) <<  8) |
            (static_cast<LONG>(*it++) << 16) |
            (static_cast<LONG>(*it++) << 24);
    errPosition =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedA429Message2 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedA429Message3 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    frameGap =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    frameLength =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);
    msgCtrl =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedA429Message4 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    cycleTime =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);
    error =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);
    bitLenOfLastBit =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);
    reservedA429Message5 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);

    return it;
}

void A429Message::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.insert(std::end(data), std::begin(a429Data), std::end(a429Data));
    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((reservedA429Message1 >>  0) & 0xff);
    data.push_back((bitrate >>  0) & 0xff);
    data.push_back((bitrate >>  8) & 0xff);
    data.push_back((bitrate >> 16) & 0xff);
    data.push_back((bitrate >> 24) & 0xff);
    data.push_back((errReason >>  0) & 0xff);
    data.push_back((errReason >>  8) & 0xff);
    data.push_back((errReason >> 16) & 0xff);
    data.push_back((errReason >> 24) & 0xff);
    data.push_back((errPosition >>  0) & 0xff);
    data.push_back((errPosition >>  8) & 0xff);
    data.push_back((reservedA429Message2 >>  0) & 0xff);
    data.push_back((reservedA429Message2 >>  8) & 0xff);
    data.push_back((reservedA429Message3 >>  0) & 0xff);
    data.push_back((reservedA429Message3 >>  8) & 0xff);
    data.push_back((reservedA429Message3 >> 16) & 0xff);
    data.push_back((reservedA429Message3 >> 24) & 0xff);
    data.push_back((frameGap >>  0) & 0xff);
    data.push_back((frameGap >>  8) & 0xff);
    data.push_back((frameGap >> 16) & 0xff);
    data.push_back((frameGap >> 24) & 0xff);
    data.push_back((frameGap >> 32) & 0xff);
    data.push_back((frameGap >> 40) & 0xff);
    data.push_back((frameGap >> 48) & 0xff);
    data.push_back((frameGap >> 56) & 0xff);
    data.push_back((frameLength >>  0) & 0xff);
    data.push_back((frameLength >>  8) & 0xff);
    data.push_back((frameLength >> 16) & 0xff);
    data.push_back((frameLength >> 24) & 0xff);
    data.push_back((msgCtrl >>  0) & 0xff);
    data.push_back((msgCtrl >>  8) & 0xff);
    data.push_back((reservedA429Message4 >>  0) & 0xff);
    data.push_back((reservedA429Message4 >>  8) & 0xff);
    data.push_back((cycleTime >>  0) & 0xff);
    data.push_back((cycleTime >>  8) & 0xff);
    data.push_back((cycleTime >> 16) & 0xff);
    data.push_back((cycleTime >> 24) & 0xff);
    data.push_back((error >>  0) & 0xff);
    data.push_back((error >>  8) & 0xff);
    data.push_back((error >> 16) & 0xff);
    data.push_back((error >> 24) & 0xff);
    data.push_back((bitLenOfLastBit >>  0) & 0xff);
    data.push_back((bitLenOfLastBit >>  8) & 0xff);
    data.push_back((bitLenOfLastBit >> 16) & 0xff);
    data.push_back((bitLenOfLastBit >> 24) & 0xff);
    data.push_back((reservedA429Message5 >>  0) & 0xff);
    data.push_back((reservedA429Message5 >>  8) & 0xff);
    data.push_back((reservedA429Message5 >> 16) & 0xff);
    data.push_back((reservedA429Message5 >> 24) & 0xff);
}

DWORD A429Message::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        static_cast<DWORD>(a429Data.size()) +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedA429Message1) +
        sizeof(bitrate) +
        sizeof(errReason) +
        sizeof(errPosition) +
        sizeof(reservedA429Message2) +
        sizeof(reservedA429Message3) +
        sizeof(frameGap) +
        sizeof(frameLength) +
        sizeof(msgCtrl) +
        sizeof(reservedA429Message4) +
        sizeof(cycleTime) +
        sizeof(error) +
        sizeof(bitLenOfLastBit) +
        sizeof(reservedA429Message5);
}

}
}
