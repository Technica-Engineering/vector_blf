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

void SerialEvent::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    is.read(reinterpret_cast<char *>(&port), sizeof(port));
    is.read(reinterpret_cast<char *>(&baudrate), sizeof(baudrate));
    is.read(reinterpret_cast<char *>(&reservedSerialEvent), sizeof(reservedSerialEvent));

    if (flags & Flags::SingleByte)
        singleByte.read(is);
    else {
        if (flags & Flags::CompactByte)
            compact.read(is);
        else
            general.read(is);
    }

    /* skip padding */
    is.seekg(objectSize % 4, std::ios_base::cur);
    // @note might be extended in future versions
}

void SerialEvent::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&flags), sizeof(flags));
    os.write(reinterpret_cast<char *>(&port), sizeof(port));
    os.write(reinterpret_cast<char *>(&baudrate), sizeof(baudrate));
    os.write(reinterpret_cast<char *>(&reservedSerialEvent), sizeof(reservedSerialEvent));

    if (flags & Flags::SingleByte)
        singleByte.write(os);
    else {
        if (flags & Flags::CompactByte)
            compact.write(os);
        else
            general.write(os);
    }

    /* skip padding */
    os.skipp(objectSize % 4);
}

uint32_t SerialEvent::calculateObjectSize() const {
    uint32_t size =
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
