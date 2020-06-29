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

#include <Vector/BLF/RealtimeClock.h>

namespace Vector {
namespace BLF {

RealtimeClock::RealtimeClock() :
    ObjectHeader(ObjectType::REALTIMECLOCK) {
}

std::vector<uint8_t>::iterator RealtimeClock::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    time =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    loggingOffset =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);

    return it;
}

void RealtimeClock::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((time >>  0) & 0xff);
    data.push_back((time >>  8) & 0xff);
    data.push_back((time >> 16) & 0xff);
    data.push_back((time >> 24) & 0xff);
    data.push_back((time >> 32) & 0xff);
    data.push_back((time >> 40) & 0xff);
    data.push_back((time >> 48) & 0xff);
    data.push_back((time >> 56) & 0xff);
    data.push_back((loggingOffset >>  0) & 0xff);
    data.push_back((loggingOffset >>  8) & 0xff);
    data.push_back((loggingOffset >> 16) & 0xff);
    data.push_back((loggingOffset >> 24) & 0xff);
    data.push_back((loggingOffset >> 32) & 0xff);
    data.push_back((loggingOffset >> 40) & 0xff);
    data.push_back((loggingOffset >> 48) & 0xff);
    data.push_back((loggingOffset >> 56) & 0xff);
}

DWORD RealtimeClock::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(time) +
        sizeof(loggingOffset);
}

}
}
