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

#include "LinStatisticEvent.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinStatisticEvent::LinStatisticEvent() :
    ObjectHeader(),
    channel(),
    reserved(),
    busLoad(),
    burstsTotal(),
    burstsOverrun(),
    framesSent(),
    framesReceived(),
    framesUnanswered()
{
}

char * LinStatisticEvent::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((char *) &reserved, buffer, size);
    buffer += size;

    // busLoad
    size = sizeof(busLoad);
    memcpy((char *) &busLoad, buffer, size);
    buffer += size;

    // burstsTotal
    size = sizeof(burstsTotal);
    memcpy((char *) &burstsTotal, buffer, size);
    buffer += size;

    // burstsOverrun
    size = sizeof(burstsOverrun);
    memcpy((char *) &burstsOverrun, buffer, size);
    buffer += size;

    // framesSent
    size = sizeof(framesSent);
    memcpy((char *) &framesSent, buffer, size);
    buffer += size;

    // framesReceived
    size = sizeof(framesReceived);
    memcpy((char *) &framesReceived, buffer, size);
    buffer += size;

    // framesUnanswered
    size = sizeof(framesUnanswered);
    memcpy((char *) &framesUnanswered, buffer, size);
    buffer += size;

    return buffer;
}

size_t LinStatisticEvent::calculateObjectSize()
{
    size_t size =
            ObjectHeader::calculateObjectSize() +
            sizeof(channel) +
            sizeof(reserved) +
            sizeof(busLoad) +
            sizeof(burstsTotal) +
            sizeof(burstsOverrun) +
            sizeof(framesSent) +
            sizeof(framesReceived) +
            sizeof(framesUnanswered);

    return size;
}

}
}
