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

char * FlexRayV6Message::read(char * buffer)
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

    // frameId
    size = sizeof(frameId);
    memcpy((void *) &frameId, buffer, size);
    buffer += size;

    // headerCrc
    size = sizeof(headerCrc);
    memcpy((void *) &headerCrc, buffer, size);
    buffer += size;

    // frameState
    size = sizeof(frameState);
    memcpy((void *) &frameState, buffer, size);
    buffer += size;

    // length
    size = sizeof(length);
    memcpy((void *) &length, buffer, size);
    buffer += size;

    // cycle
    size = sizeof(cycle);
    memcpy((void *) &cycle, buffer, size);
    buffer += size;

    // headerBitMask
    size = sizeof(headerBitMask);
    memcpy((void *) &headerBitMask, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // dataBytes
    size = sizeof(dataBytes);
    memcpy((void *) &dataBytes, buffer, size);
    buffer += size;

    return buffer;
}

char * FlexRayV6Message::write(char * buffer)
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

    // frameId
    size = sizeof(frameId);
    memcpy(buffer, (void *) &frameId, size);
    buffer += size;

    // headerCrc
    size = sizeof(headerCrc);
    memcpy(buffer, (void *) &headerCrc, size);
    buffer += size;

    // frameState
    size = sizeof(frameState);
    memcpy(buffer, (void *) &frameState, size);
    buffer += size;

    // length
    size = sizeof(length);
    memcpy(buffer, (void *) &length, size);
    buffer += size;

    // cycle
    size = sizeof(cycle);
    memcpy(buffer, (void *) &cycle, size);
    buffer += size;

    // headerBitMask
    size = sizeof(headerBitMask);
    memcpy(buffer, (void *) &headerBitMask, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    // dataBytes
    size = sizeof(dataBytes);
    memcpy(buffer, (void *) &dataBytes, size);
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
