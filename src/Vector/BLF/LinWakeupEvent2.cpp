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

#include <Vector/BLF/LinWakeupEvent2.h>

namespace Vector {
namespace BLF {

LinWakeupEvent2::LinWakeupEvent2() :
    ObjectHeader(ObjectType::LIN_WAKEUP2) {
}

std::vector<uint8_t>::iterator LinWakeupEvent2::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);
    it = LinBusEvent::fromData(it);

    lengthInfo =
        (static_cast<BYTE>(*it++) <<  0);
    signal =
        (static_cast<BYTE>(*it++) <<  0);
    external =
        (static_cast<BYTE>(*it++) <<  0);
    reservedLinWakeupEvent1 =
        (static_cast<BYTE>(*it++) <<  0);
    reservedLinWakeupEvent2 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);

    return it;
}

void LinWakeupEvent2::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);
    LinBusEvent::toData(data);

    data.push_back((lengthInfo >>  0) & 0xff);
    data.push_back((signal >>  0) & 0xff);
    data.push_back((external >>  0) & 0xff);
    data.push_back((reservedLinWakeupEvent1 >>  0) & 0xff);
    data.push_back((reservedLinWakeupEvent2 >>  0) & 0xff);
    data.push_back((reservedLinWakeupEvent2 >>  8) & 0xff);
    data.push_back((reservedLinWakeupEvent2 >> 16) & 0xff);
    data.push_back((reservedLinWakeupEvent2 >> 24) & 0xff);
}

DWORD LinWakeupEvent2::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinBusEvent::calculateObjectSize() +
        sizeof(lengthInfo) +
        sizeof(signal) +
        sizeof(external) +
        sizeof(reservedLinWakeupEvent1) +
        sizeof(reservedLinWakeupEvent2);
}

}
}
