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

#include "LinReceiveError.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinReceiveError::LinReceiveError() :
    ObjectHeader(),
    channel(),
    id(),
    dlc(),
    fsmId(),
    fsmState(),
    headerTime(),
    fullTime(),
    stateReason(),
    offendingByte(),
    shortError(),
    timeoutDuringDlcDetection()
{
}

char * LinReceiveError::read(char * buffer)
{
    size_t size;

    // previous data
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

    // stateReason
    size = sizeof(stateReason);
    memcpy((void *) &stateReason, buffer, size);
    buffer += size;

    // offendingByte
    size = sizeof(offendingByte);
    memcpy((void *) &offendingByte, buffer, size);
    buffer += size;

    // shortError
    size = sizeof(shortError);
    memcpy((void *) &shortError, buffer, size);
    buffer += size;

    // timeoutDuringDlcDetection
    size = sizeof(timeoutDuringDlcDetection);
    memcpy((void *) &timeoutDuringDlcDetection, buffer, size);
    buffer += size;

    return buffer;
}

char * LinReceiveError::write(char * buffer)
{
    // @todo
}

size_t LinReceiveError::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(id) +
        sizeof(dlc) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(headerTime) +
        sizeof(fullTime) +
        sizeof(stateReason) +
        sizeof(offendingByte) +
        sizeof(shortError) +
        sizeof(timeoutDuringDlcDetection);

    return size;
}

}
}
