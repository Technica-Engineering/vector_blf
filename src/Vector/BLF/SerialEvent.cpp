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

#include <Vector/BLF/SerialEvent.h>

namespace Vector {
namespace BLF {

SerialEvent::SerialEvent() :
    ObjectHeader(ObjectType::SERIAL_EVENT) {
}

std::vector<uint8_t>::iterator SerialEvent::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    flags =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    port =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    baudrate =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedSerialEvent =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    if (flags & Flags::SingleByte)
        it = singleByte.fromData(it);
    else {
        if (flags & Flags::CompactByte)
            it = compact.fromData(it);
        else
            it = general.fromData(it);
    }

    return it;
}

void SerialEvent::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((flags >>  0) & 0xff);
    data.push_back((flags >>  8) & 0xff);
    data.push_back((flags >> 16) & 0xff);
    data.push_back((flags >> 24) & 0xff);
    data.push_back((port >>  0) & 0xff);
    data.push_back((port >>  8) & 0xff);
    data.push_back((port >> 16) & 0xff);
    data.push_back((port >> 24) & 0xff);
    data.push_back((baudrate >>  0) & 0xff);
    data.push_back((baudrate >>  8) & 0xff);
    data.push_back((baudrate >> 16) & 0xff);
    data.push_back((baudrate >> 24) & 0xff);
    data.push_back((reservedSerialEvent >>  0) & 0xff);
    data.push_back((reservedSerialEvent >>  8) & 0xff);
    data.push_back((reservedSerialEvent >> 16) & 0xff);
    data.push_back((reservedSerialEvent >> 24) & 0xff);
    if (flags & Flags::SingleByte)
        singleByte.toData(data);
    else {
        if (flags & Flags::CompactByte)
            compact.toData(data);
        else
            general.toData(data);
    }
}

DWORD SerialEvent::calculateObjectSize() const {
    DWORD size =
        ObjectHeader::calculateObjectSize() +
        sizeof(flags) +
        sizeof(port) +
        sizeof(baudrate) +
        sizeof(reservedSerialEvent) +
        16; // size of union of singleByte/compact/general

    if (flags & ~(Flags::SingleByte | Flags::CompactByte))
        size += general.dataLength + general.timeStampsLength;

    return size;
}

}
}
