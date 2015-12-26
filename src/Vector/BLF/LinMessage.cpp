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

#include "LinMessage.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinMessage::LinMessage() :
    ObjectHeader(),
    channel(),
    id(),
    dlc(),
    data(),
    fsmId(),
    fsmState(),
    headerTime(),
    fullTime(),
    crc(),
    dir(),
    reserved()
{
}

char * LinMessage::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy((void *) &id, buffer, size);
    buffer += size;

    // dlc
    size = sizeof(dlc);
    memcpy((void *) &dlc, buffer, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy((void *) &data, buffer, size);
    buffer += size;

    // fsmId
    size = sizeof(fsmId);
    memcpy((void *) &fsmId, buffer, size);
    buffer += size;

    // fsmState
    size = sizeof(fsmState);
    memcpy((void *) &fsmState, buffer, size);
    buffer += size;

    // headerTime
    size = sizeof(headerTime);
    memcpy((void *) &headerTime, buffer, size);
    buffer += size;

    // fullTime
    size = sizeof(fullTime);
    memcpy((void *) &fullTime, buffer, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy((void *) &crc, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((void *) &dir, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    return buffer;
}

char * LinMessage::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy(buffer, (void *) &id, size);
    buffer += size;

    // dlc
    size = sizeof(dlc);
    memcpy(buffer, (void *) &dlc, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy(buffer, (void *) &data, size);
    buffer += size;

    // fsmId
    size = sizeof(fsmId);
    memcpy(buffer, (void *) &fsmId, size);
    buffer += size;

    // fsmState
    size = sizeof(fsmState);
    memcpy(buffer, (void *) &fsmState, size);
    buffer += size;

    // headerTime
    size = sizeof(headerTime);
    memcpy(buffer, (void *) &headerTime, size);
    buffer += size;

    // fullTime
    size = sizeof(fullTime);
    memcpy(buffer, (void *) &fullTime, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy(buffer, (void *) &crc, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy(buffer, (void *) &dir, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    return buffer;
}

size_t LinMessage::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(id) +
        sizeof(dlc) +
        sizeof(data) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(headerTime) +
        sizeof(fullTime) +
        sizeof(crc) +
        sizeof(dir) +
        sizeof(reserved);

    return size;
}

}
}
