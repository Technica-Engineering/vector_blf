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

#include "SerialEvent.h"

#include <cstring>

namespace Vector {
namespace BLF {

SerialEvent::SerialEvent() :
    ObjectHeader(),
    flags(),
    port(),
    baudrate(),
    reserved()
{
    objectType = ObjectType::SERIAL_EVENT;
}

char * SerialEvent::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // flags
    size = sizeof(flags);
    memcpy((void *) &flags, buffer, size);
    buffer += size;

    // port
    size = sizeof(port);
    memcpy((void *) &port, buffer, size);
    buffer += size;

    // baudrate
    size = sizeof(baudrate);
    memcpy((void *) &baudrate, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    /* union */
    if ((flags & ((DWORD) Flags::SingleByte)) != 0) {
        // data.singleByte.byte
        size = sizeof(data.singleByte.byte);
        memcpy((void *) &data.singleByte.byte, buffer, size);
        buffer += size;
    } else {
        if ((flags & ((DWORD) Flags::CompactByte)) != 0) {
            // data.compact.compactLength
            size = sizeof(data.compact.compactLength);
            memcpy((void *) &data.compact.compactLength, buffer, size);
            buffer += size;

            // data.compact.compactData
            size = sizeof(data.compact.compactData);
            memcpy((void *) &data.compact.compactData, buffer, size);
            buffer += size;
        } else {
            // data.general.dataLength
            size = sizeof(data.general.dataLength);
            memcpy((void *) &data.general.dataLength, buffer, size);
            buffer += size;

            // data.general.timeStampsLength
            size = sizeof(data.general.timeStampsLength);
            memcpy((void *) &data.general.timeStampsLength, buffer, size);
            buffer += size;

            // data.general.data
            size = data.general.dataLength;
            data.general.data = new char[size];
            memcpy(data.general.data, buffer, size);
            buffer += size;

            // data.general.timeStamps
            size = data.general.timeStampsLength;
            data.general.timeStamps = (LONGLONG *) new char[size];
            memcpy(data.general.timeStamps, buffer, size);
            buffer += size;
        }
    }

    return buffer;
}

char * SerialEvent::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // flags
    size = sizeof(flags);
    memcpy(buffer, (void *) &flags, size);
    buffer += size;

    // port
    size = sizeof(port);
    memcpy(buffer, (void *) &port, size);
    buffer += size;

    // baudrate
    size = sizeof(baudrate);
    memcpy(buffer, (void *) &baudrate, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    /* union */
    if ((flags & ((DWORD) Flags::SingleByte)) != 0) {
        // data.singleByte.byte
        size = sizeof(data.singleByte.byte);
        memcpy(buffer, (void *) &data.singleByte.byte, size);
        buffer += size;
    } else {
        if ((flags & ((DWORD) Flags::CompactByte)) != 0) {
            // data.compact.compactLength
            size = sizeof(data.compact.compactLength);
            memcpy(buffer, (void *) &data.compact.compactLength, size);
            buffer += size;

            // data.compact.compactData
            size = sizeof(data.compact.compactData);
            memcpy(buffer, (void *) &data.compact.compactData, size);
            buffer += size;
        } else {
            // data.general.dataLength
            size = sizeof(data.general.dataLength);
            memcpy(buffer, (void *) &data.general.dataLength, size);
            buffer += size;

            // data.general.timeStampsLength
            size = sizeof(data.general.timeStampsLength);
            memcpy(buffer, (void *) &data.general.timeStampsLength, size);
            buffer += size;

            // data.general.data
            size = data.general.dataLength;
            memcpy(buffer, data.general.data, size);
            buffer += size;

            // data.general.timeStamps
            size = data.general.timeStampsLength;
            memcpy(buffer, data.general.timeStamps, size);
            buffer += size;
        }
    }

    return buffer;
}

size_t SerialEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(flags) +
        sizeof(port) +
        sizeof(baudrate) +
        sizeof(reserved);

    if ((flags & ((DWORD) Flags::SingleByte)) != 0)
        size += sizeof(data.singleByte);
    else if ((flags & ((DWORD) Flags::CompactByte)) != 0)
        size += sizeof(data.compact);
    else
        size += sizeof(data.general.dataLength) +
                sizeof(data.general.timeStampsLength) +
                data.general.dataLength +
                data.general.timeStampsLength;

    return size;
}

}
}
