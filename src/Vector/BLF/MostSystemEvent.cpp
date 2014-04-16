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

#include "MostSystemEvent.h"

namespace Vector {
namespace BLF {

MostSystemEvent::MostSystemEvent() :
    ObjectHeader2(),
    channel(),
    id(),
    value(),
    valueOld()
{
}

char * MostSystemEvent::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader2::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy((char *) &id, buffer, size);
    buffer += size;

    // value
    size = sizeof(value);
    memcpy((char *) &value, buffer, size);
    buffer += size;

    // valueOld
    size = sizeof(valueOld);
    memcpy((char *) &valueOld, buffer, size);
    buffer += size;

    return buffer;
}

size_t MostSystemEvent::calculateObjectSize()
{
    size_t size =
            ObjectHeader2::calculateObjectSize() +
            sizeof(channel) +
            sizeof(id) +
            sizeof(value) +
            sizeof(valueOld);

    return size;
}

}
}
