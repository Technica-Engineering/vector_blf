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

#include "CanFdMessage.h"

#include <cstring>

namespace Vector {
namespace BLF {

CanFdMessage::CanFdMessage() :
    ObjectHeader(),
    channel(),
    flags(),
    dlc(),
    id(),
    frameLength(),
    arbBitCount(),
    canFdFlags(),
    validDataBytes(),
    reserved1(),
    reserved2(),
    data()
{
    objectType = ObjectType::CAN_FD_MESSAGE;
}

char * CanFdMessage::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((void *) &flags, buffer, size);
    buffer += size;

    // dlc
    size = sizeof(dlc);
    memcpy((void *) &dlc, buffer, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy((void *) &id, buffer, size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy((void *) &frameLength, buffer, size);
    buffer += size;

    // arbBitCount
    size = sizeof(arbBitCount);
    memcpy((void *) &arbBitCount, buffer, size);
    buffer += size;

    // canFdFlags
    size = sizeof(canFdFlags);
    memcpy((void *) &canFdFlags, buffer, size);
    buffer += size;

    // validDataBytes
    size = sizeof(validDataBytes);
    memcpy((void *) &validDataBytes, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((void *) &reserved2, buffer, size);
    buffer += size;

    // data
    size = data.size();
    memcpy(data.data(), buffer, size);
    buffer += size;

    return buffer;
}

char * CanFdMessage::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy(buffer, (void *) &flags, size);
    buffer += size;

    // dlc
    size = sizeof(dlc);
    memcpy(buffer, (void *) &dlc, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy(buffer, (void *) &id, size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy(buffer, (void *) &frameLength, size);
    buffer += size;

    // arbBitCount
    size = sizeof(arbBitCount);
    memcpy(buffer, (void *) &arbBitCount, size);
    buffer += size;

    // canFdFlags
    size = sizeof(canFdFlags);
    memcpy(buffer, (void *) &canFdFlags, size);
    buffer += size;

    // validDataBytes
    size = sizeof(validDataBytes);
    memcpy(buffer, (void *) &validDataBytes, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy(buffer, (void *) &reserved1, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy(buffer, (void *) &reserved2, size);
    buffer += size;

    // data
    size = data.size();
    memcpy(buffer, data.data(), size);
    buffer += size;

    return buffer;
}

size_t CanFdMessage::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(dlc) +
        sizeof(id) +
        sizeof(frameLength) +
        sizeof(arbBitCount) +
        sizeof(canFdFlags) +
        sizeof(validDataBytes) +
        sizeof(reserved1) +
        sizeof(reserved2) +
        data.size();

    return size;
}

}
}
