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

#include <Vector/BLF/GpsEvent.h>

namespace Vector {
namespace BLF {

GpsEvent::GpsEvent() :
    ObjectHeader(ObjectType::GPS_EVENT) {
}

std::vector<uint8_t>::iterator GpsEvent::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    flags =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedGpsEvent =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    uint64_t * ptr = reinterpret_cast<uint64_t *>(&latitude);
    *ptr =
        (static_cast<uint64_t>(*it++) <<  0) |
        (static_cast<uint64_t>(*it++) <<  8) |
        (static_cast<uint64_t>(*it++) << 16) |
        (static_cast<uint64_t>(*it++) << 24) |
        (static_cast<uint64_t>(*it++) << 32) |
        (static_cast<uint64_t>(*it++) << 40) |
        (static_cast<uint64_t>(*it++) << 48) |
        (static_cast<uint64_t>(*it++) << 56);
    ptr = reinterpret_cast<uint64_t *>(&longitude);
    *ptr =
        (static_cast<uint64_t>(*it++) <<  0) |
        (static_cast<uint64_t>(*it++) <<  8) |
        (static_cast<uint64_t>(*it++) << 16) |
        (static_cast<uint64_t>(*it++) << 24) |
        (static_cast<uint64_t>(*it++) << 32) |
        (static_cast<uint64_t>(*it++) << 40) |
        (static_cast<uint64_t>(*it++) << 48) |
        (static_cast<uint64_t>(*it++) << 56);
    ptr = reinterpret_cast<uint64_t *>(&altitude);
    *ptr =
        (static_cast<uint64_t>(*it++) <<  0) |
        (static_cast<uint64_t>(*it++) <<  8) |
        (static_cast<uint64_t>(*it++) << 16) |
        (static_cast<uint64_t>(*it++) << 24) |
        (static_cast<uint64_t>(*it++) << 32) |
        (static_cast<uint64_t>(*it++) << 40) |
        (static_cast<uint64_t>(*it++) << 48) |
        (static_cast<uint64_t>(*it++) << 56);
    ptr = reinterpret_cast<uint64_t *>(&speed);
    *ptr =
        (static_cast<uint64_t>(*it++) <<  0) |
        (static_cast<uint64_t>(*it++) <<  8) |
        (static_cast<uint64_t>(*it++) << 16) |
        (static_cast<uint64_t>(*it++) << 24) |
        (static_cast<uint64_t>(*it++) << 32) |
        (static_cast<uint64_t>(*it++) << 40) |
        (static_cast<uint64_t>(*it++) << 48) |
        (static_cast<uint64_t>(*it++) << 56);
    ptr = reinterpret_cast<uint64_t *>(&course);
    *ptr =
        (static_cast<uint64_t>(*it++) <<  0) |
        (static_cast<uint64_t>(*it++) <<  8) |
        (static_cast<uint64_t>(*it++) << 16) |
        (static_cast<uint64_t>(*it++) << 24) |
        (static_cast<uint64_t>(*it++) << 32) |
        (static_cast<uint64_t>(*it++) << 40) |
        (static_cast<uint64_t>(*it++) << 48) |
        (static_cast<uint64_t>(*it++) << 56);

    return it;
}

void GpsEvent::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((flags >>  0) & 0xff);
    data.push_back((flags >>  8) & 0xff);
    data.push_back((flags >> 16) & 0xff);
    data.push_back((flags >> 24) & 0xff);
    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((reservedGpsEvent >>  0) & 0xff);
    data.push_back((reservedGpsEvent >>  8) & 0xff);
    uint64_t * ptr = reinterpret_cast<uint64_t *>(&latitude);
    data.push_back((*ptr >>  0) & 0xff);
    data.push_back((*ptr >>  8) & 0xff);
    data.push_back((*ptr >> 16) & 0xff);
    data.push_back((*ptr >> 24) & 0xff);
    data.push_back((*ptr >> 32) & 0xff);
    data.push_back((*ptr >> 40) & 0xff);
    data.push_back((*ptr >> 48) & 0xff);
    data.push_back((*ptr >> 56) & 0xff);
    ptr = reinterpret_cast<uint64_t *>(&longitude);
    data.push_back((*ptr >>  0) & 0xff);
    data.push_back((*ptr >>  8) & 0xff);
    data.push_back((*ptr >> 16) & 0xff);
    data.push_back((*ptr >> 24) & 0xff);
    data.push_back((*ptr >> 32) & 0xff);
    data.push_back((*ptr >> 40) & 0xff);
    data.push_back((*ptr >> 48) & 0xff);
    data.push_back((*ptr >> 56) & 0xff);
    ptr = reinterpret_cast<uint64_t *>(&altitude);
    data.push_back((*ptr >>  0) & 0xff);
    data.push_back((*ptr >>  8) & 0xff);
    data.push_back((*ptr >> 16) & 0xff);
    data.push_back((*ptr >> 24) & 0xff);
    data.push_back((*ptr >> 32) & 0xff);
    data.push_back((*ptr >> 40) & 0xff);
    data.push_back((*ptr >> 48) & 0xff);
    data.push_back((*ptr >> 56) & 0xff);
    ptr = reinterpret_cast<uint64_t *>(&speed);
    data.push_back((*ptr >>  0) & 0xff);
    data.push_back((*ptr >>  8) & 0xff);
    data.push_back((*ptr >> 16) & 0xff);
    data.push_back((*ptr >> 24) & 0xff);
    data.push_back((*ptr >> 32) & 0xff);
    data.push_back((*ptr >> 40) & 0xff);
    data.push_back((*ptr >> 48) & 0xff);
    data.push_back((*ptr >> 56) & 0xff);
    ptr = reinterpret_cast<uint64_t *>(&course);
    data.push_back((*ptr >>  0) & 0xff);
    data.push_back((*ptr >>  8) & 0xff);
    data.push_back((*ptr >> 16) & 0xff);
    data.push_back((*ptr >> 24) & 0xff);
    data.push_back((*ptr >> 32) & 0xff);
    data.push_back((*ptr >> 40) & 0xff);
    data.push_back((*ptr >> 48) & 0xff);
    data.push_back((*ptr >> 56) & 0xff);
}

DWORD GpsEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(flags) +
        sizeof(channel) +
        sizeof(reservedGpsEvent) +
        sizeof(latitude) +
        sizeof(longitude) +
        sizeof(altitude) +
        sizeof(speed) +
        sizeof(course);
}

}
}
