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

#include "LinWakeupEvent.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinWakeupEvent::LinWakeupEvent() :
    ObjectHeader(),
    channel(),
    signal(),
    external()
{
}

char * LinWakeupEvent::read(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // signal
    size = sizeof(signal);
    memcpy((void *) &signal, buffer, size);
    buffer += size;

    // external
    size = sizeof(external);
    memcpy((void *) &external, buffer, size);
    buffer += size;

    return buffer;
}

char * LinWakeupEvent::write(char * buffer)
{
    // @todo
}

size_t LinWakeupEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(signal) +
        sizeof(external);

    return size;
}

}
}
