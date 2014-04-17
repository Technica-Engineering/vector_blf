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

#include "LinSchedulerModeChange.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinSchedulerModeChange::LinSchedulerModeChange() :
    ObjectHeader(),
    channel(),
    oldMode(),
    newMode(),
    reserved()
{
}

char * LinSchedulerModeChange::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // oldMode
    size = sizeof(oldMode);
    memcpy((char *) &oldMode, buffer, size);
    buffer += size;

    // newMode
    size = sizeof(newMode);
    memcpy((char *) &newMode, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((char *) &reserved, buffer, size);
    buffer += size;

    return buffer;
}

size_t LinSchedulerModeChange::calculateObjectSize()
{
    size_t size =
            ObjectHeader::calculateObjectSize() +
            sizeof(channel) +
            sizeof(oldMode) +
            sizeof(newMode) +
            sizeof(reserved);

    return size;
}

}
}
