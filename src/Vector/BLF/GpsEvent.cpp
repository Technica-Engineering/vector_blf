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
    latitude =
            (static_cast<uint64_t>(*it++) <<  0) |
            (static_cast<uint64_t>(*it++) <<  8) |
            (static_cast<uint64_t>(*it++) << 16) |
            (static_cast<uint64_t>(*it++) << 24) |
            (static_cast<uint64_t>(*it++) << 32) |
            (static_cast<uint64_t>(*it++) << 40) |
            (static_cast<uint64_t>(*it++) << 48) |
            (static_cast<uint64_t>(*it++) << 56);
    longitude =
            (static_cast<uint64_t>(*it++) <<  0) |
            (static_cast<uint64_t>(*it++) <<  8) |
            (static_cast<uint64_t>(*it++) << 16) |
            (static_cast<uint64_t>(*it++) << 24) |
            (static_cast<uint64_t>(*it++) << 32) |
            (static_cast<uint64_t>(*it++) << 40) |
            (static_cast<uint64_t>(*it++) << 48) |
            (static_cast<uint64_t>(*it++) << 56);
    altitude =
            (static_cast<uint64_t>(*it++) <<  0) |
            (static_cast<uint64_t>(*it++) <<  8) |
            (static_cast<uint64_t>(*it++) << 16) |
            (static_cast<uint64_t>(*it++) << 24) |
            (static_cast<uint64_t>(*it++) << 32) |
            (static_cast<uint64_t>(*it++) << 40) |
            (static_cast<uint64_t>(*it++) << 48) |
            (static_cast<uint64_t>(*it++) << 56);
    speed =
            (static_cast<uint64_t>(*it++) <<  0) |
            (static_cast<uint64_t>(*it++) <<  8) |
            (static_cast<uint64_t>(*it++) << 16) |
            (static_cast<uint64_t>(*it++) << 24) |
            (static_cast<uint64_t>(*it++) << 32) |
            (static_cast<uint64_t>(*it++) << 40) |
            (static_cast<uint64_t>(*it++) << 48) |
            (static_cast<uint64_t>(*it++) << 56);
    course =
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
    data.push_back((static_cast<uint64_t>(latitude) >>  0) & 0xff);
    data.push_back((static_cast<uint64_t>(latitude) >>  8) & 0xff);
    data.push_back((static_cast<uint64_t>(latitude) >> 16) & 0xff);
    data.push_back((static_cast<uint64_t>(latitude) >> 24) & 0xff);
    data.push_back((static_cast<uint64_t>(latitude) >> 32) & 0xff);
    data.push_back((static_cast<uint64_t>(latitude) >> 40) & 0xff);
    data.push_back((static_cast<uint64_t>(latitude) >> 48) & 0xff);
    data.push_back((static_cast<uint64_t>(latitude) >> 56) & 0xff);
    data.push_back((static_cast<uint64_t>(longitude) >>  0) & 0xff);
    data.push_back((static_cast<uint64_t>(longitude) >>  8) & 0xff);
    data.push_back((static_cast<uint64_t>(longitude) >> 16) & 0xff);
    data.push_back((static_cast<uint64_t>(longitude) >> 24) & 0xff);
    data.push_back((static_cast<uint64_t>(longitude) >> 32) & 0xff);
    data.push_back((static_cast<uint64_t>(longitude) >> 40) & 0xff);
    data.push_back((static_cast<uint64_t>(longitude) >> 48) & 0xff);
    data.push_back((static_cast<uint64_t>(longitude) >> 56) & 0xff);
    data.push_back((static_cast<uint64_t>(altitude) >>  0) & 0xff);
    data.push_back((static_cast<uint64_t>(altitude) >>  8) & 0xff);
    data.push_back((static_cast<uint64_t>(altitude) >> 16) & 0xff);
    data.push_back((static_cast<uint64_t>(altitude) >> 24) & 0xff);
    data.push_back((static_cast<uint64_t>(altitude) >> 32) & 0xff);
    data.push_back((static_cast<uint64_t>(altitude) >> 40) & 0xff);
    data.push_back((static_cast<uint64_t>(altitude) >> 48) & 0xff);
    data.push_back((static_cast<uint64_t>(altitude) >> 56) & 0xff);
    data.push_back((static_cast<uint64_t>(speed) >>  0) & 0xff);
    data.push_back((static_cast<uint64_t>(speed) >>  8) & 0xff);
    data.push_back((static_cast<uint64_t>(speed) >> 16) & 0xff);
    data.push_back((static_cast<uint64_t>(speed) >> 24) & 0xff);
    data.push_back((static_cast<uint64_t>(speed) >> 32) & 0xff);
    data.push_back((static_cast<uint64_t>(speed) >> 40) & 0xff);
    data.push_back((static_cast<uint64_t>(speed) >> 48) & 0xff);
    data.push_back((static_cast<uint64_t>(speed) >> 56) & 0xff);
    data.push_back((static_cast<uint64_t>(course) >>  0) & 0xff);
    data.push_back((static_cast<uint64_t>(course) >>  8) & 0xff);
    data.push_back((static_cast<uint64_t>(course) >> 16) & 0xff);
    data.push_back((static_cast<uint64_t>(course) >> 24) & 0xff);
    data.push_back((static_cast<uint64_t>(course) >> 32) & 0xff);
    data.push_back((static_cast<uint64_t>(course) >> 40) & 0xff);
    data.push_back((static_cast<uint64_t>(course) >> 48) & 0xff);
    data.push_back((static_cast<uint64_t>(course) >> 56) & 0xff);
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
