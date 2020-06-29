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

#include <Vector/BLF/LinLongDomSignalEvent.h>

namespace Vector {
namespace BLF {

LinLongDomSignalEvent::LinLongDomSignalEvent() :
    ObjectHeader(ObjectType::LIN_LONG_DOM_SIG) {
}

std::vector<uint8_t>::iterator LinLongDomSignalEvent::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);
    it = LinBusEvent::fromData(it);

    type =
            (static_cast<BYTE>(*it++) <<  0);
    reservedLinLongDomSignalEvent1 =
            (static_cast<BYTE>(*it++) <<  0);
    reservedLinLongDomSignalEvent2 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedLinLongDomSignalEvent3 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);

    return it;
}

void LinLongDomSignalEvent::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);
    LinBusEvent::toData(data);

    data.push_back((type >>  0) & 0xff);
    data.push_back((reservedLinLongDomSignalEvent1 >>  0) & 0xff);
    data.push_back((reservedLinLongDomSignalEvent2 >>  0) & 0xff);
    data.push_back((reservedLinLongDomSignalEvent2 >>  8) & 0xff);
    data.push_back((reservedLinLongDomSignalEvent3 >>  0) & 0xff);
    data.push_back((reservedLinLongDomSignalEvent3 >>  8) & 0xff);
    data.push_back((reservedLinLongDomSignalEvent3 >> 16) & 0xff);
    data.push_back((reservedLinLongDomSignalEvent3 >> 24) & 0xff);
}

DWORD LinLongDomSignalEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinBusEvent::calculateObjectSize() +
        sizeof(type) +
        sizeof(reservedLinLongDomSignalEvent1) +
        sizeof(reservedLinLongDomSignalEvent2) +
        sizeof(reservedLinLongDomSignalEvent3);
}

}
}
