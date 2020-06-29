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

#include <Vector/BLF/MostPkt2.h>

namespace Vector {
namespace BLF {

MostPkt2::MostPkt2() :
    ObjectHeader2(ObjectType::MOST_PKT2) {
}

std::vector<uint8_t>::iterator MostPkt2::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader2::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    dir =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMostPkt1 =
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
    arbitration =
            (static_cast<BYTE>(*it++) <<  0);
    timeRes =
            (static_cast<BYTE>(*it++) <<  0);
    quadsToFollow =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMostPkt2 =
            (static_cast<BYTE>(*it++) <<  0);
    crc =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    priority =
            (static_cast<BYTE>(*it++) <<  0);
    transferType =
            (static_cast<BYTE>(*it++) <<  0);
    state =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMostPkt3 =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMostPkt4 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    pktDataLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedMostPkt5 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    pktData.resize(pktDataLength);
    std::copy(it, it + pktData.size(), std::begin(pktData));
    it += pktData.size();

    return it;
}

void MostPkt2::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    pktDataLength = static_cast<DWORD>(pktData.size());

    ObjectHeader2::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((reservedMostPkt1 >>  0) & 0xff);
    data.push_back((sourceAdr >>  0) & 0xff);
    data.push_back((sourceAdr >>  8) & 0xff);
    data.push_back((sourceAdr >> 16) & 0xff);
    data.push_back((sourceAdr >> 24) & 0xff);
    data.push_back((destAdr >>  0) & 0xff);
    data.push_back((destAdr >>  8) & 0xff);
    data.push_back((destAdr >> 16) & 0xff);
    data.push_back((destAdr >> 24) & 0xff);
    data.push_back((arbitration >>  0) & 0xff);
    data.push_back((timeRes >>  0) & 0xff);
    data.push_back((quadsToFollow >>  0) & 0xff);
    data.push_back((reservedMostPkt2 >>  0) & 0xff);
    data.push_back((crc >>  0) & 0xff);
    data.push_back((crc >>  8) & 0xff);
    data.push_back((priority >>  0) & 0xff);
    data.push_back((transferType >>  0) & 0xff);
    data.push_back((state >>  0) & 0xff);
    data.push_back((reservedMostPkt3 >>  0) & 0xff);
    data.push_back((reservedMostPkt4 >>  0) & 0xff);
    data.push_back((reservedMostPkt4 >>  8) & 0xff);
    data.push_back((pktDataLength >>  0) & 0xff);
    data.push_back((pktDataLength >>  8) & 0xff);
    data.push_back((pktDataLength >> 16) & 0xff);
    data.push_back((pktDataLength >> 24) & 0xff);
    data.push_back((reservedMostPkt5 >>  0) & 0xff);
    data.push_back((reservedMostPkt5 >>  8) & 0xff);
    data.push_back((reservedMostPkt5 >> 16) & 0xff);
    data.push_back((reservedMostPkt5 >> 24) & 0xff);
    data.insert(std::end(data), std::begin(pktData), std::end(pktData));
}

DWORD MostPkt2::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedMostPkt1) +
        sizeof(sourceAdr) +
        sizeof(destAdr) +
        sizeof(arbitration) +
        sizeof(timeRes) +
        sizeof(quadsToFollow) +
        sizeof(reservedMostPkt2) +
        sizeof(crc) +
        sizeof(priority) +
        sizeof(transferType) +
        sizeof(state) +
        sizeof(reservedMostPkt3) +
        sizeof(reservedMostPkt4) +
        sizeof(pktDataLength) +
        sizeof(reservedMostPkt5) +
        pktDataLength;
}

}
}
