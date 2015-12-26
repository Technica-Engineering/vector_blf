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

#include "FlexRayStatusEvent.h"

#include <cstring>

namespace Vector {
namespace BLF {

FlexRayStatusEvent::FlexRayStatusEvent() :
    ObjectHeader(),
    channel(),
    version(),
    statusType(),
    infoMask1(),
    infoMask2(),
    infoMask3(),
    reserved()
{
}

char * FlexRayStatusEvent::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // version
    size = sizeof(version);
    memcpy((void *) &version, buffer, size);
    buffer += size;

    // statusType
    size = sizeof(statusType);
    memcpy((void *) &statusType, buffer, size);
    buffer += size;

    // infoMask1
    size = sizeof(infoMask1);
    memcpy((void *) &infoMask1, buffer, size);
    buffer += size;

    // infoMask2
    size = sizeof(infoMask2);
    memcpy((void *) &infoMask2, buffer, size);
    buffer += size;

    // infoMask3
    size = sizeof(infoMask3);
    memcpy((void *) &infoMask3, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    return buffer;
}

char * FlexRayStatusEvent::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // version
    size = sizeof(version);
    memcpy(buffer, (void *) &version, size);
    buffer += size;

    // statusType
    size = sizeof(statusType);
    memcpy(buffer, (void *) &statusType, size);
    buffer += size;

    // infoMask1
    size = sizeof(infoMask1);
    memcpy(buffer, (void *) &infoMask1, size);
    buffer += size;

    // infoMask2
    size = sizeof(infoMask2);
    memcpy(buffer, (void *) &infoMask2, size);
    buffer += size;

    // infoMask3
    size = sizeof(infoMask3);
    memcpy(buffer, (void *) &infoMask3, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    return buffer;
}

size_t FlexRayStatusEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(statusType) +
        sizeof(infoMask1) +
        sizeof(infoMask2) +
        sizeof(infoMask3) +
        sizeof(reserved);

    return size;
}

}
}
