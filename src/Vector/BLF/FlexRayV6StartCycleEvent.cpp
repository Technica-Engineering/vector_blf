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

#include "FlexRayV6StartCycleEvent.h"

#include <cstring>

namespace Vector {
namespace BLF {

FlexRayV6StartCycleEvent::FlexRayV6StartCycleEvent() :
    ObjectHeader(),
    channel(),
    dir(),
    lowTime(),
    fpgaTick(),
    fpgaTickOverflow(),
    clientIndex(),
    clusterTime(),
    dataBytes(),
    reserved()
{
    objectType = ObjectType::FLEXRAY_CYCLE;
}

char * FlexRayV6StartCycleEvent::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((void *) &dir, buffer, size);
    buffer += size;

    // lowTime
    size = sizeof(lowTime);
    memcpy((void *) &lowTime, buffer, size);
    buffer += size;

    // fpgaTick
    size = sizeof(fpgaTick);
    memcpy((void *) &fpgaTick, buffer, size);
    buffer += size;

    // fpgaTickOverflow
    size = sizeof(fpgaTickOverflow);
    memcpy((void *) &fpgaTickOverflow, buffer, size);
    buffer += size;

    // clientIndex
    size = sizeof(clientIndex);
    memcpy((void *) &clientIndex, buffer, size);
    buffer += size;

    // clusterTime
    size = sizeof(clusterTime);
    memcpy((void *) &clusterTime, buffer, size);
    buffer += size;

    // dataBytes
    size = dataBytes.size();
    memcpy(dataBytes.data(), buffer, size);
    buffer += size;

    // reserved
    size = reserved.size();
    memcpy(reserved.data(), buffer, size);
    buffer += size;

    return buffer;
}

char * FlexRayV6StartCycleEvent::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy(buffer, (void *) &dir, size);
    buffer += size;

    // lowTime
    size = sizeof(lowTime);
    memcpy(buffer, (void *) &lowTime, size);
    buffer += size;

    // fpgaTick
    size = sizeof(fpgaTick);
    memcpy(buffer, (void *) &fpgaTick, size);
    buffer += size;

    // fpgaTickOverflow
    size = sizeof(fpgaTickOverflow);
    memcpy(buffer, (void *) &fpgaTickOverflow, size);
    buffer += size;

    // clientIndex
    size = sizeof(clientIndex);
    memcpy(buffer, (void *) &clientIndex, size);
    buffer += size;

    // clusterTime
    size = sizeof(clusterTime);
    memcpy(buffer, (void *) &clusterTime, size);
    buffer += size;

    // dataBytes
    size = dataBytes.size();
    memcpy(buffer, dataBytes.data(), size);
    buffer += size;

    // reserved
    size = reserved.size();
    memcpy(buffer, reserved.data(), size);
    buffer += size;

    return buffer;
}

size_t FlexRayV6StartCycleEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(lowTime) +
        sizeof(fpgaTick) +
        sizeof(fpgaTickOverflow) +
        sizeof(clientIndex) +
        sizeof(clusterTime) +
        dataBytes.size() +
        reserved.size();

    return size;
}

}
}
