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

#include "LinCrcError2.h"

namespace Vector {
namespace BLF {

LinCrcError2::LinCrcError2() :
    ObjectHeader(),
    LinDatabyteTimestampEvent(),
    data(),
    crc(),
    dir(),
    fsmId(),
    fsmState(),
    simulated(),
    reserved(),
    respBaudrate(),
    reserved2(),
    exactHeaderBaudrate(),
    earlyStopbitOffset(),
    earlyStopbitOffsetResponse()
{
}

char * LinCrcError2::parse(char * buffer)
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

size_t LinCrcError2::calculateObjectSize()
{
    size_t size =
            ObjectHeader::calculateObjectSize() +
            LinDatabyteTimestampEvent::calculateObjectSize() +
            sizeof(data) +
            sizeof(crc) +
            sizeof(dir) +
            sizeof(fsmId) +
            sizeof(fsmState) +
            sizeof(simulated) +
            sizeof(reserved) +
            sizeof(respBaudrate) +
            sizeof(reserved2) +
            sizeof(exactHeaderBaudrate) +
            sizeof(earlyStopbitOffset) +
            sizeof(earlyStopbitOffsetResponse);

    return size;
}

}
}
