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

#include "LinMessage2.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinMessage2::LinMessage2() :
    ObjectHeader(),
    LinDatabyteTimestampEvent(),
    data(),
    crc(),
    dir(),
    simulated(),
    isEtf(),
    etfAssocIndex(),
    etfAssocEtfId(),
    fsmId(),
    fsmState(),
    reserved1(),
    respBaudrate(),
    exactHeaderBaudrate(),
    earlyStopbitOffset(),
    earlyStopbitOffsetResponse()
{
}

char * LinMessage2::read(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::read(buffer);
    buffer = LinDatabyteTimestampEvent::read(buffer);

    // data
    size = sizeof(data);
    memcpy((void *) &data, buffer, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy((void *) &crc, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((void *) &dir, buffer, size);
    buffer += size;

    // simulated
    size = sizeof(simulated);
    memcpy((void *) &simulated, buffer, size);
    buffer += size;

    // isEtf
    size = sizeof(isEtf);
    memcpy((void *) &isEtf, buffer, size);
    buffer += size;

    // etfAssocIndex
    size = sizeof(etfAssocIndex);
    memcpy((void *) &etfAssocIndex, buffer, size);
    buffer += size;

    // etfAssocEtfId
    size = sizeof(etfAssocEtfId);
    memcpy((void *) &etfAssocEtfId, buffer, size);
    buffer += size;

    // fsmId
    size = sizeof(fsmId);
    memcpy((void *) &fsmId, buffer, size);
    buffer += size;

    // fsmState
    size = sizeof(fsmState);
    memcpy((void *) &fsmState, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    /* the following variables are only available in Version 2 and above */
    if (objectVersion < 0) // this is probably a bug in Vector's original implementation
        return buffer;

    // respBaudrate
    size = sizeof(respBaudrate);
    memcpy((void *) &respBaudrate, buffer, size);
    buffer += size;

    /* the following variables are only available in Version 3 and above */
    if (objectVersion < 1) // this is probably a bug in Vector's original implementation
        return buffer;

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

size_t LinMessage2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        sizeof(data) +
        sizeof(crc) +
        sizeof(dir) +
        sizeof(simulated) +
        sizeof(isEtf) +
        sizeof(etfAssocIndex) +
        sizeof(etfAssocEtfId) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(reserved1);

    if (objectVersion >= 0) // this is probably a bug in Vector's original implementation
        size += sizeof(respBaudrate);

    if (objectVersion >= 1) // this is probably a bug in Vector's original implementation
        size += sizeof(exactHeaderBaudrate) +
                sizeof(earlyStopbitOffset) +
                sizeof(earlyStopbitOffsetResponse);

    return size;
}

}
}
