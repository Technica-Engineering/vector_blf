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

#include <Vector/BLF/MostEthernetPktFragment.h>

namespace Vector {
namespace BLF {

MostEthernetPktFragment::MostEthernetPktFragment() :
    ObjectHeader2(ObjectType::MOST_ETHERNET_PKT_FRAGMENT) {
}

std::vector<uint8_t>::iterator MostEthernetPktFragment::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader2::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedMostEthernetPktFragment1 =
            (static_cast<BYTE>(*it++) <<  0);
    ackNack =
            (static_cast<BYTE>(*it++) <<  0);
    validMask =
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
    pAck =
            (static_cast<BYTE>(*it++) <<  0);
    cAck =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMostEthernetPktFragment2 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
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
    reservedMostEthernetPktFragment3 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    firstData.resize(firstDataLen);
    std::copy(it, it + firstData.size(), std::begin(firstData));
    it += firstData.size();

    return it;
}

void MostEthernetPktFragment::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    firstDataLen = static_cast<DWORD>(firstData.size());

    ObjectHeader2::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((reservedMostEthernetPktFragment1 >>  0) & 0xff);
    data.push_back((ackNack >>  0) & 0xff);
    data.push_back((validMask >>  0) & 0xff);
    data.push_back((validMask >>  8) & 0xff);
    data.push_back((validMask >> 16) & 0xff);
    data.push_back((validMask >> 24) & 0xff);
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
    data.push_back((pAck >>  0) & 0xff);
    data.push_back((cAck >>  0) & 0xff);
    data.push_back((reservedMostEthernetPktFragment2 >>  0) & 0xff);
    data.push_back((reservedMostEthernetPktFragment2 >>  8) & 0xff);
    data.push_back((crc >>  0) & 0xff);
    data.push_back((crc >>  8) & 0xff);
    data.push_back((crc >> 16) & 0xff);
    data.push_back((crc >> 24) & 0xff);
    data.push_back((dataLen >>  0) & 0xff);
    data.push_back((dataLen >>  8) & 0xff);
    data.push_back((dataLen >> 16) & 0xff);
    data.push_back((dataLen >> 24) & 0xff);
    data.push_back((firstDataLen >>  0) & 0xff);
    data.push_back((firstDataLen >>  8) & 0xff);
    data.push_back((firstDataLen >> 16) & 0xff);
    data.push_back((firstDataLen >> 24) & 0xff);
    data.push_back((reservedMostEthernetPktFragment3 >>  0) & 0xff);
    data.push_back((reservedMostEthernetPktFragment3 >>  8) & 0xff);
    data.push_back((reservedMostEthernetPktFragment3 >> 16) & 0xff);
    data.push_back((reservedMostEthernetPktFragment3 >> 24) & 0xff);
    data.insert(std::end(data), std::begin(firstData), std::end(firstData));
}

DWORD MostEthernetPktFragment::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reservedMostEthernetPktFragment1) +
        sizeof(ackNack) +
        sizeof(validMask) +
        sizeof(sourceMacAdr) +
        sizeof(destMacAdr) +
        sizeof(pAck) +
        sizeof(cAck) +
        sizeof(reservedMostEthernetPktFragment2) +
        sizeof(crc) +
        sizeof(dataLen) +
        sizeof(dataLenAnnounced) +
        sizeof(firstDataLen) +
        sizeof(reservedMostEthernetPktFragment3) +
        firstDataLen;
}

}
}
