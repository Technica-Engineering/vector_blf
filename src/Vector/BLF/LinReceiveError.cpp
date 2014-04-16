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

char * LinReceiveError::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy((char *) &id, buffer, size);
    buffer += size;

    // dlc
    size = sizeof(dlc);
    memcpy((char *) &dlc, buffer, size);
    buffer += size;

    // fsmId
    size = sizeof(fsmId);
    memcpy((char *) &fsmId, buffer, size);
    buffer += size;

    // fsmState
    size = sizeof(fsmState);
    memcpy((char *) &fsmState, buffer, size);
    buffer += size;

    // headerTime
    size = sizeof(headerTime);
    memcpy((char *) &headerTime, buffer, size);
    buffer += size;

    // fullTime
    size = sizeof(fullTime);
    memcpy((char *) &fullTime, buffer, size);
    buffer += size;

    // stateReason
    size = sizeof(stateReason);
    memcpy((char *) &stateReason, buffer, size);
    buffer += size;

    // offendingByte
    size = sizeof(offendingByte);
    memcpy((char *) &offendingByte, buffer, size);
    buffer += size;

    // shortError
    size = sizeof(shortError);
    memcpy((char *) &shortError, buffer, size);
    buffer += size;

    // timeoutDuringDlcDetection
    size = sizeof(timeoutDuringDlcDetection);
    memcpy((char *) &timeoutDuringDlcDetection, buffer, size);
    buffer += size;

    return buffer;
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
