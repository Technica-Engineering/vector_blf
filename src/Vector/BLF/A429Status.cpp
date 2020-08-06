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

#include <Vector/BLF/A429Status.h>

namespace Vector {
namespace BLF {

A429Status::A429Status() :
    ObjectHeader(ObjectType::A429_STATUS) {
}

std::vector<uint8_t>::iterator A429Status::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    dir =
        (static_cast<BYTE>(*it++) <<  0);
    reservedA429Status1 =
        (static_cast<BYTE>(*it++) <<  0);
    parity =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedA429Status2 =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    minGap =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    bitrate =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    minBitrate =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    maxBitrate =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);

    return it;
}

void A429Status::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((reservedA429Status1 >>  0) & 0xff);
    data.push_back((parity >>  0) & 0xff);
    data.push_back((parity >>  8) & 0xff);
    data.push_back((reservedA429Status2 >>  0) & 0xff);
    data.push_back((reservedA429Status2 >>  8) & 0xff);
    data.push_back((minGap >>  0) & 0xff);
    data.push_back((minGap >>  8) & 0xff);
    data.push_back((minGap >> 16) & 0xff);
    data.push_back((minGap >> 24) & 0xff);
    data.push_back((bitrate >>  0) & 0xff);
    data.push_back((bitrate >>  8) & 0xff);
    data.push_back((bitrate >> 16) & 0xff);
    data.push_back((bitrate >> 24) & 0xff);
    data.push_back((minBitrate >>  0) & 0xff);
    data.push_back((minBitrate >>  8) & 0xff);
    data.push_back((minBitrate >> 16) & 0xff);
    data.push_back((minBitrate >> 24) & 0xff);
    data.push_back((maxBitrate >>  0) & 0xff);
    data.push_back((maxBitrate >>  8) & 0xff);
    data.push_back((maxBitrate >> 16) & 0xff);
    data.push_back((maxBitrate >> 24) & 0xff);
}

DWORD A429Status::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedA429Status1) +
        sizeof(parity) +
        sizeof(reservedA429Status2) +
        sizeof(minGap) +
        sizeof(bitrate) +
        sizeof(minBitrate) +
        sizeof(maxBitrate);
}

}
}
