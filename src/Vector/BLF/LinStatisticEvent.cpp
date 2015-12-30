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
    reserved1(),
    busLoad(),
    burstsTotal(),
    burstsOverrun(),
    framesSent(),
    framesReceived(),
    framesUnanswered(),
    reserved2()
{
    objectType = ObjectType::LIN_STATISTIC;
}

char * LinStatisticEvent::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    // busLoad
    size = sizeof(busLoad);
    memcpy((void *) &busLoad, buffer, size);
    buffer += size;

    // burstsTotal
    size = sizeof(burstsTotal);
    memcpy((void *) &burstsTotal, buffer, size);
    buffer += size;

    // burstsOverrun
    size = sizeof(burstsOverrun);
    memcpy((void *) &burstsOverrun, buffer, size);
    buffer += size;

    // framesSent
    size = sizeof(framesSent);
    memcpy((void *) &framesSent, buffer, size);
    buffer += size;

    // framesReceived
    size = sizeof(framesReceived);
    memcpy((void *) &framesReceived, buffer, size);
    buffer += size;

    // framesUnanswered
    size = sizeof(framesUnanswered);
    memcpy((void *) &framesUnanswered, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((void *) &reserved2, buffer, size);
    buffer += size;

    return buffer;
}

char * LinStatisticEvent::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy(buffer, (void *) &reserved1, size);
    buffer += size;

    // busLoad
    size = sizeof(busLoad);
    memcpy(buffer, (void *) &busLoad, size);
    buffer += size;

    // burstsTotal
    size = sizeof(burstsTotal);
    memcpy(buffer, (void *) &burstsTotal, size);
    buffer += size;

    // burstsOverrun
    size = sizeof(burstsOverrun);
    memcpy(buffer, (void *) &burstsOverrun, size);
    buffer += size;

    // framesSent
    size = sizeof(framesSent);
    memcpy(buffer, (void *) &framesSent, size);
    buffer += size;

    // framesReceived
    size = sizeof(framesReceived);
    memcpy(buffer, (void *) &framesReceived, size);
    buffer += size;

    // framesUnanswered
    size = sizeof(framesUnanswered);
    memcpy(buffer, (void *) &framesUnanswered, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy(buffer, (void *) &reserved2, size);
    buffer += size;

    return buffer;
}

size_t LinStatisticEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reserved1) +
        sizeof(busLoad) +
        sizeof(burstsTotal) +
        sizeof(burstsOverrun) +
        sizeof(framesSent) +
        sizeof(framesReceived) +
        sizeof(framesUnanswered) +
        sizeof(reserved2);

    return size;
}

}
}
