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
        // singleByte.byte
        size = sizeof(singleByte.byte);
        memcpy((void *) &singleByte.byte, buffer, size);
        buffer += size;
    } else {
        if ((flags & ((DWORD) Flags::CompactByte)) != 0) {
            // compact.compactLength
            size = sizeof(compact.compactLength);
            memcpy((void *) &compact.compactLength, buffer, size);
            buffer += size;

            // compact.compactData
            size = compact.compactLength;
            memcpy((void *) &compact.compactData, buffer, size);
            buffer += size;
        } else {
            // general.dataLength
            size = sizeof(GeneralSerialEvent::dataLength);
            memcpy((void *) &general.dataLength, buffer, size);
            buffer += size;

            // general.timeStampsLength
            size = sizeof(GeneralSerialEvent::timeStampsLength);
            memcpy((void *) &general.timeStampsLength, buffer, size);
            buffer += size;

            // general.data
            size = general.dataLength;
            general.data = new char[size];
            memcpy(general.data, buffer, size);
            buffer += size;

            // general.timeStamps
            size = general.timeStampsLength;
            general.timeStamps = (LONGLONG *) new char[size];
            memcpy(general.timeStamps, buffer, size);
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
        // singleByte.byte
        size = sizeof(singleByte.byte);
        memcpy(buffer, (void *) &singleByte.byte, size);
        buffer += size;
    } else {
        if ((flags & ((DWORD) Flags::CompactByte)) != 0) {
            // compact.compactLength
            size = sizeof(compact.compactLength);
            memcpy(buffer, (void *) &compact.compactLength, size);
            buffer += size;

            // compact.compactData
            size = compact.compactLength;
            memcpy(buffer, (void *) &compact.compactData, size);
            buffer += size;
        } else {
            // general.dataLength
            size = sizeof(GeneralSerialEvent::dataLength);
            memcpy(buffer, (void *) &general.dataLength, size);
            buffer += size;

            // general.timeStampsLength
            size = sizeof(GeneralSerialEvent::timeStampsLength);
            memcpy(buffer, (void *) &general.timeStampsLength, size);
            buffer += size;

            // general.data
            size = general.dataLength;
            memcpy(buffer, general.data, size);
            buffer += size;

            // general.timeStamps
            size = general.timeStampsLength;
            memcpy(buffer, general.timeStamps, size);
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
        size += sizeof(SingleByteSerialEvent);
    else if ((flags & ((DWORD) Flags::CompactByte)) != 0)
        size += sizeof(CompactSerialEvent);
    else
        size += sizeof(GeneralSerialEvent::dataLength) +
                sizeof(GeneralSerialEvent::timeStampsLength) +
                general.dataLength +
                general.timeStampsLength;

    return size;
}

}
}
