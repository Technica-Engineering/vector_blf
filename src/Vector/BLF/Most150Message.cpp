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

#include <Vector/BLF/Most150Message.h>

namespace Vector {
namespace BLF {

Most150Message::Most150Message() :
    ObjectHeader2(ObjectType::MOST_150_MESSAGE) {
}

std::vector<uint8_t>::iterator Most150Message::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader2::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    dir =
        (static_cast<BYTE>(*it++) <<  0);
    reservedMost150Message1 =
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
    reservedMost150Message2 =
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
    priority =
        (static_cast<BYTE>(*it++) <<  0);
    pIndex =
        (static_cast<BYTE>(*it++) <<  0);
    msgLen =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    reservedMost150Message3 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    msg.resize(msgLen);
    std::copy(it, it + msg.size(), std::begin(msg));
    it += msgLen;

    return it;
}

void Most150Message::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    msgLen = static_cast<DWORD>(msg.size());

    ObjectHeader2::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((reservedMost150Message1 >>  0) & 0xff);
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
    data.push_back((reservedMost150Message2 >>  0) & 0xff);
    data.push_back((crc >>  0) & 0xff);
    data.push_back((crc >>  8) & 0xff);
    data.push_back((crc >> 16) & 0xff);
    data.push_back((crc >> 24) & 0xff);
    data.push_back((pAck >>  0) & 0xff);
    data.push_back((cAck >>  0) & 0xff);
    data.push_back((priority >>  0) & 0xff);
    data.push_back((pIndex >>  0) & 0xff);
    data.push_back((msgLen >>  0) & 0xff);
    data.push_back((msgLen >>  8) & 0xff);
    data.push_back((msgLen >> 16) & 0xff);
    data.push_back((msgLen >> 24) & 0xff);
    data.push_back((reservedMost150Message3 >>  0) & 0xff);
    data.push_back((reservedMost150Message3 >>  8) & 0xff);
    data.push_back((reservedMost150Message3 >> 16) & 0xff);
    data.push_back((reservedMost150Message3 >> 24) & 0xff);
    data.insert(std::end(data), std::begin(msg), std::end(msg));
}

DWORD Most150Message::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedMost150Message1) +
        sizeof(sourceAdr) +
        sizeof(destAdr) +
        sizeof(transferType) +
        sizeof(state) +
        sizeof(ackNack) +
        sizeof(reservedMost150Message2) +
        sizeof(crc) +
        sizeof(pAck) +
        sizeof(cAck) +
        sizeof(priority) +
        sizeof(pIndex) +
        sizeof(msgLen) +
        sizeof(reservedMost150Message3) +
        msgLen;
}

}
}
