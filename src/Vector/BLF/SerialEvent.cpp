/*
 * Copyright (C) 2013 Tobias Lorenz.
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
    ObjectHeader(),
    flags(),
    port(),
    baudrate(),
    reservedSerialEvent(),
    general(),
    singleByte(),
    compact()
{
    objectType = ObjectType::SERIAL_EVENT;
}

SerialEvent::~SerialEvent()
{
}

void SerialEvent::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    is.read(reinterpret_cast<char *>(&port), sizeof(port));
    is.read(reinterpret_cast<char *>(&baudrate), sizeof(baudrate));
    is.read(reinterpret_cast<char *>(&reservedSerialEvent), sizeof(reservedSerialEvent));

    if ((flags & Flags::SingleByte) != 0) {
        singleByte.read(is);
    } else {
        if ((flags & Flags::CompactByte) != 0) {
            compact.read(is);
        } else {
            general.read(is);
        }
    }
}

void SerialEvent::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&flags), sizeof(flags));
    os.write(reinterpret_cast<char *>(&port), sizeof(port));
    os.write(reinterpret_cast<char *>(&baudrate), sizeof(baudrate));
    os.write(reinterpret_cast<char *>(&reservedSerialEvent), sizeof(reservedSerialEvent));

    if ((flags & Flags::SingleByte) != 0) {
        singleByte.write(os);
    } else {
        if ((flags & Flags::CompactByte) != 0) {
            compact.write(os);
        } else {
            general.write(os);
        }
    }
}

DWORD SerialEvent::calculateObjectSize() const
{
    DWORD size =
        ObjectHeader::calculateObjectSize() +
        sizeof(flags) +
        sizeof(port) +
        sizeof(baudrate) +
        sizeof(reservedSerialEvent);

    if ((flags & Flags::SingleByte) != 0) {
        size += singleByte.calculateObjectSize();
    } else {
        if ((flags & Flags::CompactByte) != 0) {
            size += compact.calculateObjectSize();
        } else {
            size += general.calculateObjectSize();
        }
    }

    return size;
}

}
}
