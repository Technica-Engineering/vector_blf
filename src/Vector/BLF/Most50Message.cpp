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

#include <Vector/BLF/Most50Message.h>

namespace Vector {
namespace BLF {

Most50Message::Most50Message() :
    ObjectHeader2(ObjectType::MOST_50_MESSAGE) {
}

std::vector<uint8_t>::iterator Most50Message::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader2::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    dir =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMost50Message1 =
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
    transferType =
            (static_cast<BYTE>(*it++) <<  0);
    state =
            (static_cast<BYTE>(*it++) <<  0);
    ackNack =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMost50Message2 =
            (static_cast<BYTE>(*it++) <<  0);
    crc =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedMost50Message3 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    priority =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMost50Message4 =
            (static_cast<BYTE>(*it++) <<  0);
    msgLen =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedMost50Message5 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    msg.resize(msgLen);
    std::copy(it, it + msg.size(), std::begin(msg));
    it += msg.size();

    return it;
}

void Most50Message::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    msgLen = static_cast<DWORD>(msg.size());

    ObjectHeader2::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((reservedMost50Message1 >>  0) & 0xff);
    data.push_back((sourceAdr >>  0) & 0xff);
    data.push_back((sourceAdr >>  8) & 0xff);
    data.push_back((sourceAdr >> 16) & 0xff);
    data.push_back((sourceAdr >> 24) & 0xff);
    data.push_back((destAdr >>  0) & 0xff);
    data.push_back((destAdr >>  8) & 0xff);
    data.push_back((destAdr >> 16) & 0xff);
    data.push_back((destAdr >> 24) & 0xff);
    data.push_back((transferType >>  0) & 0xff);
    data.push_back((state >>  0) & 0xff);
    data.push_back((ackNack >>  0) & 0xff);
    data.push_back((reservedMost50Message2 >>  0) & 0xff);
    data.push_back((crc >>  0) & 0xff);
    data.push_back((crc >>  8) & 0xff);
    data.push_back((crc >> 16) & 0xff);
    data.push_back((crc >> 24) & 0xff);
    data.push_back((reservedMost50Message3 >>  0) & 0xff);
    data.push_back((reservedMost50Message3 >>  8) & 0xff);
    data.push_back((priority >>  0) & 0xff);
    data.push_back((reservedMost50Message4 >>  0) & 0xff);
    data.push_back((msgLen >>  0) & 0xff);
    data.push_back((msgLen >>  8) & 0xff);
    data.push_back((msgLen >> 16) & 0xff);
    data.push_back((msgLen >> 24) & 0xff);
    data.push_back((reservedMost50Message5 >>  0) & 0xff);
    data.push_back((reservedMost50Message5 >>  8) & 0xff);
    data.push_back((reservedMost50Message5 >> 16) & 0xff);
    data.push_back((reservedMost50Message5 >> 24) & 0xff);
    data.insert(std::end(data), std::begin(msg), std::end(msg));
}

DWORD Most50Message::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedMost50Message1) +
        sizeof(sourceAdr) +
        sizeof(destAdr) +
        sizeof(transferType) +
        sizeof(state) +
        sizeof(ackNack) +
        sizeof(reservedMost50Message2) +
        sizeof(crc) +
        sizeof(reservedMost50Message3) +
        sizeof(priority) +
        sizeof(reservedMost50Message4) +
        sizeof(msgLen) +
        sizeof(reservedMost50Message5) +
        msgLen;
}

}
}
