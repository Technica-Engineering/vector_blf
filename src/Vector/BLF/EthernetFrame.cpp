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

#include <Vector/BLF/EthernetFrame.h>

namespace Vector {
namespace BLF {

EthernetFrame::EthernetFrame() :
    ObjectHeader(ObjectType::ETHERNET_FRAME) {
}

std::vector<uint8_t>::iterator EthernetFrame::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    std::copy(it, it + sourceAddress.size(), std::begin(sourceAddress));
    it += sourceAddress.size();
    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    std::copy(it, it + destinationAddress.size(), std::begin(destinationAddress));
    it += destinationAddress.size();
    dir =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    type =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    tpid =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    tci =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    payLoadLength =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedEthernetFrame =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    payLoad.resize(payLoadLength);
    std::copy(it, it + payLoad.size(), std::begin(payLoad));
    it += payLoadLength;

    return it;
}

void EthernetFrame::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    payLoadLength = static_cast<WORD>(payLoad.size());

    ObjectHeader::toData(data);

    data.insert(std::end(data), std::begin(sourceAddress), std::end(sourceAddress));
    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.insert(std::end(data), std::begin(destinationAddress), std::end(destinationAddress));
    data.push_back((dir >>  0) & 0xff);
    data.push_back((dir >>  8) & 0xff);
    data.push_back((type >>  0) & 0xff);
    data.push_back((type >>  8) & 0xff);
    data.push_back((tpid >>  0) & 0xff);
    data.push_back((tpid >>  8) & 0xff);
    data.push_back((tci >>  0) & 0xff);
    data.push_back((tci >>  8) & 0xff);
    data.push_back((payLoadLength >>  0) & 0xff);
    data.push_back((payLoadLength >>  8) & 0xff);
    data.push_back((reservedEthernetFrame >>  0) & 0xff);
    data.push_back((reservedEthernetFrame >>  8) & 0xff);
    data.push_back((reservedEthernetFrame >> 16) & 0xff);
    data.push_back((reservedEthernetFrame >> 24) & 0xff);
    data.push_back((reservedEthernetFrame >> 32) & 0xff);
    data.push_back((reservedEthernetFrame >> 40) & 0xff);
    data.push_back((reservedEthernetFrame >> 48) & 0xff);
    data.push_back((reservedEthernetFrame >> 56) & 0xff);
    data.insert(std::end(data), std::begin(payLoad), std::end(payLoad));
}

DWORD EthernetFrame::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        static_cast<DWORD>(sourceAddress.size()) +
        sizeof(channel) +
        static_cast<DWORD>(destinationAddress.size()) +
        sizeof(dir) +
        sizeof(type) +
        sizeof(tpid) +
        sizeof(tci) +
        sizeof(payLoadLength) +
        sizeof(reservedEthernetFrame) +
        payLoadLength;
}

}
}
