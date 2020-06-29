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

#include <Vector/BLF/CanMessage2.h>

namespace Vector {
namespace BLF {

CanMessage2::CanMessage2() :
    ObjectHeader(ObjectType::CAN_MESSAGE2) {
}

std::vector<uint8_t>::iterator CanMessage2::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    flags =
            (static_cast<BYTE>(*it++) <<  0);
    dlc =
            (static_cast<BYTE>(*it++) <<  0);
    id =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    std::copy(it, it + this->data.size(), std::begin(this->data));
    it += this->data.size();
    frameLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    bitCount =
            (static_cast<BYTE>(*it++) <<  0);
    reservedCanMessage1 =
            (static_cast<BYTE>(*it++) <<  0);
    reservedCanMessage2 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);

    return it;
}

void CanMessage2::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((flags >>  0) & 0xff);
    data.push_back((dlc >>  0) & 0xff);
    data.push_back((id >>  0) & 0xff);
    data.push_back((id >>  8) & 0xff);
    data.push_back((id >> 16) & 0xff);
    data.push_back((id >> 24) & 0xff);
    data.insert(std::end(data), std::begin(this->data), std::end(this->data));
    data.push_back((frameLength >>  0) & 0xff);
    data.push_back((frameLength >>  8) & 0xff);
    data.push_back((frameLength >> 16) & 0xff);
    data.push_back((frameLength >> 24) & 0xff);
    data.push_back((bitCount >>  0) & 0xff);
    data.push_back((reservedCanMessage1 >>  0) & 0xff);
    data.push_back((reservedCanMessage2 >>  0) & 0xff);
    data.push_back((reservedCanMessage2 >>  8) & 0xff);
}

DWORD CanMessage2::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(dlc) +
        sizeof(id) +
        static_cast<DWORD>(data.size()) +
        sizeof(frameLength) +
        sizeof(bitCount) +
        sizeof(reservedCanMessage1) +
        sizeof(reservedCanMessage2);
}

}
}
