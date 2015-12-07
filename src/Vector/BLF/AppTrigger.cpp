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

#include "AppTrigger.h"

#include <cstring>

namespace Vector {
namespace BLF {

AppTrigger::AppTrigger() :
    ObjectHeader(),
    preTriggerTime(),
    postTriggerTime(),
    channel(),
    flags(),
    appSpecific2()
{
}

char * AppTrigger::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // preTriggerTime
    size = sizeof(preTriggerTime);
    memcpy((void *) &preTriggerTime, buffer, size);
    buffer += size;

    // postTriggerTime
    size = sizeof(postTriggerTime);
    memcpy((void *) &postTriggerTime, buffer, size);
    buffer += size;

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((void *) &flags, buffer, size);
    buffer += size;

    // appSpecific2
    size = sizeof(appSpecific2);
    memcpy((void *) &appSpecific2, buffer, size);
    buffer += size;

    return buffer;
}

size_t AppTrigger::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(preTriggerTime) +
        sizeof(postTriggerTime) +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(appSpecific2);

    return size;
}

}
}
