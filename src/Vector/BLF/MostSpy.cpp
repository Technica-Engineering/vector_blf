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

#include <Vector/BLF/MostSpy.h>

namespace Vector {
namespace BLF {

MostSpy::MostSpy() :
    ObjectHeader(ObjectType::MOST_SPY) {
}

std::vector<uint8_t>::iterator MostSpy::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    dir =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMostSpy1 =
            (static_cast<BYTE>(*it++) <<  0);
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
    std::copy(it, it + msg.size(), std::begin(msg));
    it += msg.size();
    reservedMostSpy2 =
            (static_cast<BYTE>(*it++) <<  0);
    rTyp =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    rTypAdr =
            (static_cast<BYTE>(*it++) <<  0);
    state =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMostSpy3 =
            (static_cast<BYTE>(*it++) <<  0);
    ackNack =
            (static_cast<BYTE>(*it++) <<  0);
    crc =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);

    return it;
}

void MostSpy::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((reservedMostSpy1 >>  0) & 0xff);
    data.push_back((sourceAdr >>  0) & 0xff);
    data.push_back((sourceAdr >>  8) & 0xff);
    data.push_back((sourceAdr >> 16) & 0xff);
    data.push_back((sourceAdr >> 24) & 0xff);
    data.push_back((destAdr >>  0) & 0xff);
    data.push_back((destAdr >>  8) & 0xff);
    data.push_back((destAdr >> 16) & 0xff);
    data.push_back((destAdr >> 24) & 0xff);
    data.insert(std::end(data), std::begin(msg), std::end(msg));
    data.push_back((reservedMostSpy2 >>  0) & 0xff);
    data.push_back((rTyp >>  0) & 0xff);
    data.push_back((rTyp >>  8) & 0xff);
    data.push_back((rTypAdr >>  0) & 0xff);
    data.push_back((state >>  0) & 0xff);
    data.push_back((reservedMostSpy3 >>  0) & 0xff);
    data.push_back((ackNack >>  0) & 0xff);
    data.push_back((crc >>  0) & 0xff);
    data.push_back((crc >>  8) & 0xff);
    data.push_back((crc >> 16) & 0xff);
    data.push_back((crc >> 24) & 0xff);
}

DWORD MostSpy::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedMostSpy1) +
        sizeof(sourceAdr) +
        sizeof(destAdr) +
        static_cast<DWORD>(msg.size()) +
        sizeof(reservedMostSpy2) +
        sizeof(rTyp) +
        sizeof(rTypAdr) +
        sizeof(state) +
        sizeof(reservedMostSpy3) +
        sizeof(ackNack) +
        sizeof(crc);
}

}
}
