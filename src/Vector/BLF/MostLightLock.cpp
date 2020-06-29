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

#include <Vector/BLF/MostLightLock.h>

namespace Vector {
namespace BLF {

MostLightLock::MostLightLock() :
    ObjectHeader(ObjectType::MOST_LIGHTLOCK) {
}

std::vector<uint8_t>::iterator MostLightLock::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    state =
            (static_cast<SHORT>(*it++) <<  0) |
            (static_cast<SHORT>(*it++) <<  8);
    reservedMostLightLock =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);

    return it;
}

void MostLightLock::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((state >>  0) & 0xff);
    data.push_back((state >>  8) & 0xff);
    data.push_back((reservedMostLightLock >>  0) & 0xff);
    data.push_back((reservedMostLightLock >>  8) & 0xff);
    data.push_back((reservedMostLightLock >> 16) & 0xff);
    data.push_back((reservedMostLightLock >> 24) & 0xff);
}

DWORD MostLightLock::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(state) +
        sizeof(reservedMostLightLock);
}

}
}
