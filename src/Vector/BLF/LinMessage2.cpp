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
    reserved(),
    reserved_ver1_only(),
    respBaudrate(),
    exactHeaderBaudrate(),
    earlyStopbitOffset(),
    earlyStopbitOffsetResponse()
{
}

char * LinMessage2::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);
    buffer = LinDatabyteTimestampEvent::parse(buffer);

    // data
    size = sizeof(data);
    memcpy((char *) &data, buffer, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy((char *) &crc, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((char *) &dir, buffer, size);
    buffer += size;

    // simulated
    size = sizeof(simulated);
    memcpy((char *) &simulated, buffer, size);
    buffer += size;

    // isEtf
    size = sizeof(isEtf);
    memcpy((char *) &isEtf, buffer, size);
    buffer += size;

    // etfAssocIndex
    size = sizeof(etfAssocIndex);
    memcpy((char *) &etfAssocIndex, buffer, size);
    buffer += size;

    // etfAssocEtfId
    size = sizeof(etfAssocEtfId);
    memcpy((char *) &etfAssocEtfId, buffer, size);
    buffer += size;

    // fsmId
    size = sizeof(fsmId);
    memcpy((char *) &fsmId, buffer, size);
    buffer += size;

    // fsmState
    size = sizeof(fsmState);
    memcpy((char *) &fsmState, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((char *) &reserved, buffer, size);
    buffer += size;

    /* the following variables are only available in Version 2 and above */
    if (objectVersion < 2) {
        // reserved_ver1_only
        size = sizeof(reserved_ver1_only);
        memcpy((char *) &reserved_ver1_only, buffer, size);
        buffer += size;

        return buffer;
    }

    // respBaudrate
    size = sizeof(respBaudrate);
    memcpy((char *) &respBaudrate, buffer, size);
    buffer += size;

    /* the following variables are only available in Version 3 and above */
    if (objectVersion < 3)
        return buffer;

    // exactHeaderBaudrate
    size = sizeof(exactHeaderBaudrate);
    memcpy((char *) &exactHeaderBaudrate, buffer, size);
    buffer += size;

    // earlyStopbitOffset
    size = sizeof(earlyStopbitOffset);
    memcpy((char *) &earlyStopbitOffset, buffer, size);
    buffer += size;

    // earlyStopbitOffsetResponse
    size = sizeof(earlyStopbitOffsetResponse);
    memcpy((char *) &earlyStopbitOffsetResponse, buffer, size);
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
            sizeof(reserved);

    if (objectVersion < 2) {
        size += sizeof(reserved_ver1_only);
        return size;
    }

    size += sizeof(respBaudrate);

    if (objectVersion < 3) {
        return size;
    }

    size += sizeof(exactHeaderBaudrate) +
            sizeof(earlyStopbitOffset) +
            sizeof(earlyStopbitOffsetResponse);

    return size;
}

}
}
