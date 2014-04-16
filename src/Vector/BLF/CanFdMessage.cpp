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
}

char * CanFdMessage::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((char *) &flags, buffer, size);
    buffer += size;

    // dlc
    size = sizeof(dlc);
    memcpy((char *) &dlc, buffer, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy((char *) &id, buffer, size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy((char *) &frameLength, buffer, size);
    buffer += size;

    // arbBitCount
    size = sizeof(arbBitCount);
    memcpy((char *) &arbBitCount, buffer, size);
    buffer += size;

    // canFdFlags
    size = sizeof(canFdFlags);
    memcpy((char *) &canFdFlags, buffer, size);
    buffer += size;

    // validDataBytes
    size = sizeof(validDataBytes);
    memcpy((char *) &validDataBytes, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((char *) &reserved1, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((char *) &reserved2, buffer, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy((char *) &data, buffer, size);
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
            sizeof(data);

    return size;
}

}
}
