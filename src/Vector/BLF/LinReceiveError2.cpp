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

#include "LinReceiveError2.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinReceiveError2::LinReceiveError2() :
    ObjectHeader(),
    LinDatabyteTimestampEvent(),
    data(),
    fsmId(),
    fsmState(),
    stateReason(),
    offendingByte(),
    shortError(),
    timeoutDuringDlcDetection(),
    isEtf(),
    hasDatabytes(),
    respBaudrate(),
    reserved(),
    exactHeaderBaudrate(),
    earlyStopbitOffset(),
    earlyStopbitOffsetResponse()
{
    objectType = ObjectType::LIN_RCV_ERROR2;
}

char * LinReceiveError2::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);
    buffer = LinDatabyteTimestampEvent::read(buffer);

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

    // isEtf
    size = sizeof(isEtf);
    memcpy((void *) &isEtf, buffer, size);
    buffer += size;

    // hasDatabytes
    size = sizeof(hasDatabytes);
    memcpy((void *) &hasDatabytes, buffer, size);
    buffer += size;

    // respBaudrate
    size = sizeof(respBaudrate);
    memcpy((void *) &respBaudrate, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // exactHeaderBaudrate
    size = sizeof(exactHeaderBaudrate);
    memcpy((void *) &exactHeaderBaudrate, buffer, size);
    buffer += size;

    // earlyStopbitOffset
    size = sizeof(earlyStopbitOffset);
    memcpy((void *) &earlyStopbitOffset, buffer, size);
    buffer += size;

    // earlyStopbitOffsetResponse
    size = sizeof(earlyStopbitOffsetResponse);
    memcpy((void *) &earlyStopbitOffsetResponse, buffer, size);
    buffer += size;

    return buffer;
}

char * LinReceiveError2::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);
    buffer = LinDatabyteTimestampEvent::write(buffer);

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

    // stateReason
    size = sizeof(stateReason);
    memcpy(buffer, (void *) &stateReason, size);
    buffer += size;

    // offendingByte
    size = sizeof(offendingByte);
    memcpy(buffer, (void *) &offendingByte, size);
    buffer += size;

    // shortError
    size = sizeof(shortError);
    memcpy(buffer, (void *) &shortError, size);
    buffer += size;

    // timeoutDuringDlcDetection
    size = sizeof(timeoutDuringDlcDetection);
    memcpy(buffer, (void *) &timeoutDuringDlcDetection, size);
    buffer += size;

    // isEtf
    size = sizeof(isEtf);
    memcpy(buffer, (void *) &isEtf, size);
    buffer += size;

    // hasDatabytes
    size = sizeof(hasDatabytes);
    memcpy(buffer, (void *) &hasDatabytes, size);
    buffer += size;

    // respBaudrate
    size = sizeof(respBaudrate);
    memcpy(buffer, (void *) &respBaudrate, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    // exactHeaderBaudrate
    size = sizeof(exactHeaderBaudrate);
    memcpy(buffer, (void *) &exactHeaderBaudrate, size);
    buffer += size;

    // earlyStopbitOffset
    size = sizeof(earlyStopbitOffset);
    memcpy(buffer, (void *) &earlyStopbitOffset, size);
    buffer += size;

    // earlyStopbitOffsetResponse
    size = sizeof(earlyStopbitOffsetResponse);
    memcpy(buffer, (void *) &earlyStopbitOffsetResponse, size);
    buffer += size;

    return buffer;
}

size_t LinReceiveError2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        sizeof(data) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(stateReason) +
        sizeof(offendingByte) +
        sizeof(shortError) +
        sizeof(timeoutDuringDlcDetection) +
        sizeof(isEtf) +
        sizeof(hasDatabytes) +
        sizeof(respBaudrate) +
        sizeof(reserved) +
        sizeof(exactHeaderBaudrate) +
        sizeof(earlyStopbitOffset) +
        sizeof(earlyStopbitOffsetResponse);

    return size;
}

}
}
