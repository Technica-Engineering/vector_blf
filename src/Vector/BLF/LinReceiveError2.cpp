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
}

char * LinReceiveError2::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

#if 0
    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;
#else
    // @todo
#endif

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
