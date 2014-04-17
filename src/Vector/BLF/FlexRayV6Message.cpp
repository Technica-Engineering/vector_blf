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

#include "FlexRayV6Message.h"

#include <cstring>

namespace Vector {
namespace BLF {

FlexRayV6Message::FlexRayV6Message() :
    ObjectHeader(),
    channel(),
    dir(),
    lowTime(),
    fpgaTick(),
    fpgaTickOverflow(),
    clientIndex(),
    clusterTime(),
    frameId(),
    headerCrc(),
    frameState(),
    length(),
    cycle(),
    headerBitMask(),
    reserved(),
    dataBytes()
{
}

char * FlexRayV6Message::parse(char * buffer)
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

    // frameId
    size = sizeof(frameId);
    memcpy((char *) &frameId, buffer, size);
    buffer += size;

    // headerCrc
    size = sizeof(headerCrc);
    memcpy((char *) &headerCrc, buffer, size);
    buffer += size;

    // frameState
    size = sizeof(frameState);
    memcpy((char *) &frameState, buffer, size);
    buffer += size;

    // length
    size = sizeof(length);
    memcpy((char *) &length, buffer, size);
    buffer += size;

    // cycle
    size = sizeof(cycle);
    memcpy((char *) &cycle, buffer, size);
    buffer += size;

    // headerBitMask
    size = sizeof(headerBitMask);
    memcpy((char *) &headerBitMask, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved);
    memcpy((char *) &reserved, buffer, size);
    buffer += size;

    // dataBytes
    size = sizeof(dataBytes);
    memcpy((char *) &dataBytes, buffer, size);
    buffer += size;

    return buffer;
}

size_t FlexRayV6Message::calculateObjectSize()
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
            sizeof(frameId) +
            sizeof(headerCrc) +
            sizeof(frameState) +
            sizeof(length) +
            sizeof(cycle) +
            sizeof(headerBitMask) +
            sizeof(reserved) +
            sizeof(dataBytes);

    return size;
}

}
}
