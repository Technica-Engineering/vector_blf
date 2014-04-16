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
}

char * FlexRayV6StartCycleEvent::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((char *) &dir, buffer, size);
    buffer += size;

    // lowTime
    size = sizeof(lowTime);
    memcpy((char *) &lowTime, buffer, size);
    buffer += size;

    // fpgaTick
    size = sizeof(fpgaTick);
    memcpy((char *) &fpgaTick, buffer, size);
    buffer += size;

    // fpgaTickOverflow
    size = sizeof(fpgaTickOverflow);
    memcpy((char *) &fpgaTickOverflow, buffer, size);
    buffer += size;

    // clientIndex
    size = sizeof(clientIndex);
    memcpy((char *) &clientIndex, buffer, size);
    buffer += size;

    // clusterTime
    size = sizeof(clusterTime);
    memcpy((char *) &clusterTime, buffer, size);
    buffer += size;

    // dataBytes
    size = sizeof(dataBytes);
    memcpy((char *) &dataBytes, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((char *) &reserved, buffer, size);
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
            sizeof(dataBytes) +
            sizeof(reserved);

    return size;
}

}
}
