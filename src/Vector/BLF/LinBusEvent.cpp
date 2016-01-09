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

#include "LinBusEvent.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinBusEvent::LinBusEvent() :
    sof(),
    eventBaudrate(),
    channel(),
    reserved()
{
}

char * LinBusEvent::read(char * buffer)
{
    size_t size;

    // sof
    size = sizeof(sof);
    memcpy((void *) &sof, buffer, size);
    buffer += size;

    // eventBaudrate
    size = sizeof(eventBaudrate);
    memcpy((void *) &eventBaudrate, buffer, size);
    buffer += size;

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // reserved
    size = reserved.size();
    memcpy(reserved.data(), buffer, size);
    buffer += size;

    return buffer;
}

char * LinBusEvent::write(char * buffer)
{
    size_t size;

    // sof
    size = sizeof(sof);
    memcpy(buffer, (void *) &sof, size);
    buffer += size;

    // eventBaudrate
    size = sizeof(eventBaudrate);
    memcpy(buffer, (void *) &eventBaudrate, size);
    buffer += size;

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // reserved
    size = reserved.size();
    memcpy(buffer, reserved.data(), size);
    buffer += size;

    return buffer;
}

size_t LinBusEvent::calculateObjectSize()
{
    size_t size =
        sizeof(sof) +
        sizeof(eventBaudrate) +
        sizeof(channel) +
        reserved.size();

    return size;
}

}
}
