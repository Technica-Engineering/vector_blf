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

#include "MostTrigger.h"

#include <cstring>

namespace Vector {
namespace BLF {

MostTrigger::MostTrigger() :
    ObjectHeader2(),
    channel(),
    reserved(),
    mode(),
    hw(),
    previousTriggerValue(),
    currentTriggerValue()
{
}

char * MostTrigger::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader2::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // mode
    size = sizeof(mode);
    memcpy((void *) &mode, buffer, size);
    buffer += size;

    // hw
    size = sizeof(hw);
    memcpy((void *) &hw, buffer, size);
    buffer += size;

    // previousTriggerValue
    size = sizeof(previousTriggerValue);
    memcpy((void *) &previousTriggerValue, buffer, size);
    buffer += size;

    // currentTriggerValue
    size = sizeof(currentTriggerValue);
    memcpy((void *) &currentTriggerValue, buffer, size);
    buffer += size;

    return buffer;
}

char * MostTrigger::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader2::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    // mode
    size = sizeof(mode);
    memcpy(buffer, (void *) &mode, size);
    buffer += size;

    // hw
    size = sizeof(hw);
    memcpy(buffer, (void *) &hw, size);
    buffer += size;

    // previousTriggerValue
    size = sizeof(previousTriggerValue);
    memcpy(buffer, (void *) &previousTriggerValue, size);
    buffer += size;

    // currentTriggerValue
    size = sizeof(currentTriggerValue);
    memcpy(buffer, (void *) &currentTriggerValue, size);
    buffer += size;

    return buffer;
}

size_t MostTrigger::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reserved) +
        sizeof(mode) +
        sizeof(hw) +
        sizeof(previousTriggerValue) +
        sizeof(currentTriggerValue);

    return size;
}

}
}
