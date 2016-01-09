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

#include "CanMessage2.h"

#include <cstring>

namespace Vector {
namespace BLF {

CanMessage2::CanMessage2() :
    ObjectHeader(),
    channel(),
    flags(),
    dlc(),
    id(),
    data(),
    frameLength(),
    bitCount(),
    reserved1(),
    reserved2()
{
    objectType = ObjectType::CAN_MESSAGE2;
}

char * CanMessage2::read(char * buffer)
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

    // data
    size = data.size();
    memcpy(data.data(), buffer, size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy((void *) &frameLength, buffer, size);
    buffer += size;

    // bitCount
    size = sizeof(bitCount);
    memcpy((void *) &bitCount, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((void *) &reserved2, buffer, size);
    buffer += size;

    return buffer;
}

char * CanMessage2::write(char * buffer)
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

    // data
    size = data.size();
    memcpy(buffer, data.data(), size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy(buffer, (void *) &frameLength, size);
    buffer += size;

    // bitCount
    size = sizeof(bitCount);
    memcpy(buffer, (void *) &bitCount, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy(buffer, (void *) &reserved1, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy(buffer, (void *) &reserved2, size);
    buffer += size;

    return buffer;
}

size_t CanMessage2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(dlc) +
        sizeof(id) +
        data.size() +
        sizeof(frameLength) +
        sizeof(bitCount) +
        sizeof(reserved1) +
        sizeof(reserved2);

    return size;
}

}
}
