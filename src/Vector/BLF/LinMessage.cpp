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

#include <Vector/BLF/LinMessage.h>

namespace Vector {
namespace BLF {

LinMessage::LinMessage() :
    ObjectHeader(ObjectType::LIN_MESSAGE) {
}

std::vector<uint8_t>::iterator LinMessage::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    id =
        (static_cast<BYTE>(*it++) <<  0);
    dlc =
        (static_cast<BYTE>(*it++) <<  0);
    std::copy(it, it + this->data.size(), std::begin(data));
    it += this->data.size();
    fsmId =
        (static_cast<BYTE>(*it++) <<  0);
    fsmState =
        (static_cast<BYTE>(*it++) <<  0);
    headerTime =
        (static_cast<BYTE>(*it++) <<  0);
    fullTime =
        (static_cast<BYTE>(*it++) <<  0);
    crc =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    dir =
        (static_cast<BYTE>(*it++) <<  0);
    reservedLinMessage1 =
        (static_cast<BYTE>(*it++) <<  0);
    reservedLinMessage2 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);

    return it;
}

void LinMessage::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((id >>  0) & 0xff);
    data.push_back((dlc >>  0) & 0xff);
    data.insert(std::end(data), std::begin(this->data), std::end(this->data));
    data.push_back((fsmId >>  0) & 0xff);
    data.push_back((fsmState >>  0) & 0xff);
    data.push_back((headerTime >>  0) & 0xff);
    data.push_back((fullTime >>  0) & 0xff);
    data.push_back((crc >>  0) & 0xff);
    data.push_back((crc >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((reservedLinMessage1 >>  0) & 0xff);
    data.push_back((reservedLinMessage2 >>  0) & 0xff);
    data.push_back((reservedLinMessage2 >>  8) & 0xff);
    data.push_back((reservedLinMessage2 >> 16) & 0xff);
    data.push_back((reservedLinMessage2 >> 24) & 0xff);
}

DWORD LinMessage::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(id) +
        sizeof(dlc) +
        static_cast<DWORD>(data.size()) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(headerTime) +
        sizeof(fullTime) +
        sizeof(crc) +
        sizeof(dir) +
        sizeof(reservedLinMessage1) +
        sizeof(reservedLinMessage2);
}

}
}
