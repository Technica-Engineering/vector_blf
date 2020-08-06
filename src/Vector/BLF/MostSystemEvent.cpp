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

#include <Vector/BLF/MostSystemEvent.h>

namespace Vector {
namespace BLF {

MostSystemEvent::MostSystemEvent() :
    ObjectHeader2(ObjectType::MOST_SYSTEM_EVENT) {
}

std::vector<uint8_t>::iterator MostSystemEvent::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader2::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    id =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    value =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    valueOld =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    reservedMostSystemEvent =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);

    return it;
}

void MostSystemEvent::toData(std::vector<uint8_t> & data) {
    ObjectHeader2::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((id >>  0) & 0xff);
    data.push_back((id >>  8) & 0xff);
    data.push_back((value >>  0) & 0xff);
    data.push_back((value >>  8) & 0xff);
    data.push_back((value >> 16) & 0xff);
    data.push_back((value >> 24) & 0xff);
    data.push_back((valueOld >>  0) & 0xff);
    data.push_back((valueOld >>  8) & 0xff);
    data.push_back((valueOld >> 16) & 0xff);
    data.push_back((valueOld >> 24) & 0xff);
    data.push_back((reservedMostSystemEvent >>  0) & 0xff);
    data.push_back((reservedMostSystemEvent >>  8) & 0xff);
    data.push_back((reservedMostSystemEvent >> 16) & 0xff);
    data.push_back((reservedMostSystemEvent >> 24) & 0xff);
}


DWORD MostSystemEvent::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(id) +
        sizeof(value) +
        sizeof(valueOld) +
        sizeof(reservedMostSystemEvent);
}

}
}
