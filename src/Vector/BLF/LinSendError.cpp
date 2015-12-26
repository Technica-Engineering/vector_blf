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

#include "LinSendError.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinSendError::LinSendError() :
    ObjectHeader(),
    channel(),
    id(),
    dlc(),
    fsmId(),
    fsmState(),
    headerTime(),
    fullTime()
{
}

char * LinSendError::read(char * buffer)
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

    return buffer;
}

char * LinSendError::write(char * buffer)
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

    return buffer;
}

size_t LinSendError::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(id) +
        sizeof(dlc) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(headerTime) +
        sizeof(fullTime);

    return size;
}

}
}
