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

#include <Vector/BLF/MostEthernetPkt.h>

namespace Vector {
namespace BLF {

MostEthernetPkt::MostEthernetPkt() :
    ObjectHeader2(ObjectType::MOST_ETHERNET_PKT) {
}

std::vector<uint8_t>::iterator MostEthernetPkt::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader2::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    dir =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMostEthernetPkt1 =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMostEthernetPkt2 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    sourceMacAdr =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    destMacAdr =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    transferType =
            (static_cast<BYTE>(*it++) <<  0);
    state =
            (static_cast<BYTE>(*it++) <<  0);
    ackNack =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMostEthernetPkt3 =
            (static_cast<BYTE>(*it++) <<  0);
    crc =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    pAck =
            (static_cast<BYTE>(*it++) <<  0);
    cAck =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMostEthernetPkt4 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    pktDataLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedMostEthernetPkt5 =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    pktData.resize(pktDataLength);
    std::copy(it, it + pktData.size(), std::begin(pktData));
    it += pktData.size();

    return it;
}

void MostEthernetPkt::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    pktDataLength = static_cast<DWORD>(pktData.size());

    ObjectHeader2::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((reservedMostEthernetPkt1 >>  0) & 0xff);
    data.push_back((reservedMostEthernetPkt2 >>  0) & 0xff);
    data.push_back((reservedMostEthernetPkt2 >>  8) & 0xff);
    data.push_back((reservedMostEthernetPkt2 >> 16) & 0xff);
    data.push_back((reservedMostEthernetPkt2 >> 24) & 0xff);
    data.push_back((sourceMacAdr >>  0) & 0xff);
    data.push_back((sourceMacAdr >>  8) & 0xff);
    data.push_back((sourceMacAdr >> 16) & 0xff);
    data.push_back((sourceMacAdr >> 24) & 0xff);
    data.push_back((sourceMacAdr >> 32) & 0xff);
    data.push_back((sourceMacAdr >> 40) & 0xff);
    data.push_back((sourceMacAdr >> 48) & 0xff);
    data.push_back((sourceMacAdr >> 56) & 0xff);
    data.push_back((destMacAdr >>  0) & 0xff);
    data.push_back((destMacAdr >>  8) & 0xff);
    data.push_back((destMacAdr >> 16) & 0xff);
    data.push_back((destMacAdr >> 24) & 0xff);
    data.push_back((destMacAdr >> 32) & 0xff);
    data.push_back((destMacAdr >> 40) & 0xff);
    data.push_back((destMacAdr >> 48) & 0xff);
    data.push_back((destMacAdr >> 56) & 0xff);
    data.push_back((transferType >>  0) & 0xff);
    data.push_back((state >>  0) & 0xff);
    data.push_back((ackNack >>  0) & 0xff);
    data.push_back((reservedMostEthernetPkt3 >>  0) & 0xff);
    data.push_back((crc >>  0) & 0xff);
    data.push_back((crc >>  8) & 0xff);
    data.push_back((crc >> 16) & 0xff);
    data.push_back((crc >> 24) & 0xff);
    data.push_back((pAck >>  0) & 0xff);
    data.push_back((cAck >>  0) & 0xff);
    data.push_back((reservedMostEthernetPkt4 >>  0) & 0xff);
    data.push_back((reservedMostEthernetPkt4 >>  8) & 0xff);
    data.push_back((pktDataLength >>  0) & 0xff);
    data.push_back((pktDataLength >>  8) & 0xff);
    data.push_back((pktDataLength >> 16) & 0xff);
    data.push_back((pktDataLength >> 24) & 0xff);
    data.push_back((reservedMostEthernetPkt5 >>  0) & 0xff);
    data.push_back((reservedMostEthernetPkt5 >>  8) & 0xff);
    data.push_back((reservedMostEthernetPkt5 >> 16) & 0xff);
    data.push_back((reservedMostEthernetPkt5 >> 24) & 0xff);
    data.push_back((reservedMostEthernetPkt5 >> 32) & 0xff);
    data.push_back((reservedMostEthernetPkt5 >> 40) & 0xff);
    data.push_back((reservedMostEthernetPkt5 >> 48) & 0xff);
    data.push_back((reservedMostEthernetPkt5 >> 56) & 0xff);
    data.insert(std::end(data), std::begin(pktData), std::end(pktData));
}

DWORD MostEthernetPkt::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedMostEthernetPkt1) +
        sizeof(reservedMostEthernetPkt2) +
        sizeof(sourceMacAdr) +
        sizeof(destMacAdr) +
        sizeof(transferType) +
        sizeof(state) +
        sizeof(ackNack) +
        sizeof(reservedMostEthernetPkt3) +
        sizeof(crc) +
        sizeof(pAck) +
        sizeof(cAck) +
        sizeof(reservedMostEthernetPkt4) +
        sizeof(pktDataLength) +
        sizeof(reservedMostEthernetPkt5) +
        pktDataLength;
}

}
}
