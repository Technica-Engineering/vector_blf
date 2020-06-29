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

#include <Vector/BLF/J1708Message.h>

namespace Vector {
namespace BLF {

J1708Message::J1708Message() :
    ObjectHeader(ObjectType::J1708_MESSAGE) { // or J1708_VIRTUAL_MSG
}

std::vector<uint8_t>::iterator J1708Message::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    dir =
            (static_cast<BYTE>(*it++) <<  0);
    reservedJ1708Message1 =
            (static_cast<BYTE>(*it++) <<  0);
    error =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    size =
            (static_cast<BYTE>(*it++) <<  0);
    std::copy(it, it + this->data.size(), std::begin(this->data));
    it += this->data.size();
    reservedJ1708Message2 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);

    return it;
}

void J1708Message::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((reservedJ1708Message1 >>  0) & 0xff);
    data.push_back((error >>  0) & 0xff);
    data.push_back((error >>  8) & 0xff);
    data.push_back((size >>  0) & 0xff);
    data.insert(std::end(data), std::begin(this->data), std::end(this->data));
    data.push_back((reservedJ1708Message2 >>  0) & 0xff);
    data.push_back((reservedJ1708Message2 >>  8) & 0xff);
}

DWORD J1708Message::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedJ1708Message1) +
        sizeof(error) +
        sizeof(size) +
        static_cast<DWORD>(data.size()) +
        sizeof(reservedJ1708Message2);
}

}
}
