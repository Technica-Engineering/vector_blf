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

#include "FlexRayVFrReceiveMsg.h"

#include <cstring>

namespace Vector {
namespace BLF {

FlexRayVFrReceiveMsg::FlexRayVFrReceiveMsg() :
    ObjectHeader(),
    channel(),
    version(),
    channelMask(),
    dir(),
    reserved1(),
    clientIndex(),
    clusterNo(),
    frameId(),
    headerCrc1(),
    headerCrc2(),
    byteCount(),
    dataCount(),
    cycle(),
    reserved2(),
    tag(),
    data(),
    frameFlags(),
    appParameter(),
    dataBytes()
{
}

char * FlexRayVFrReceiveMsg::read(char * buffer)
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

    // channelMask
    size = sizeof(channelMask);
    memcpy((void *) &channelMask, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((void *) &dir, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    // clientIndex
    size = sizeof(clientIndex);
    memcpy((void *) &clientIndex, buffer, size);
    buffer += size;

    // clusterNo
    size = sizeof(clusterNo);
    memcpy((void *) &clusterNo, buffer, size);
    buffer += size;

    // frameId
    size = sizeof(frameId);
    memcpy((void *) &frameId, buffer, size);
    buffer += size;

    // headerCrc1
    size = sizeof(headerCrc1);
    memcpy((void *) &headerCrc1, buffer, size);
    buffer += size;

    // headerCrc2
    size = sizeof(headerCrc2);
    memcpy((void *) &headerCrc2, buffer, size);
    buffer += size;

    // byteCount
    size = sizeof(byteCount);
    memcpy((void *) &byteCount, buffer, size);
    buffer += size;

    // dataCount
    size = sizeof(dataCount);
    memcpy((void *) &dataCount, buffer, size);
    buffer += size;

    // cycle
    size = sizeof(cycle);
    memcpy((void *) &cycle, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((void *) &reserved2, buffer, size);
    buffer += size;

    // tag
    size = sizeof(tag);
    memcpy((void *) &tag, buffer, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy((void *) &data, buffer, size);
    buffer += size;

    // frameFlags
    size = sizeof(frameFlags);
    memcpy((void *) &frameFlags, buffer, size);
    buffer += size;

    // appParameter
    size = sizeof(appParameter);
    memcpy((void *) &appParameter, buffer, size);
    buffer += size;

    // dataBytes
    size = sizeof(dataBytes);
    memcpy((void *) &dataBytes, buffer, size);
    buffer += size;

    return buffer;
}

char * FlexRayVFrReceiveMsg::write(char * buffer)
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

    // channelMask
    size = sizeof(channelMask);
    memcpy(buffer, (void *) &channelMask, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy(buffer, (void *) &dir, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy(buffer, (void *) &reserved1, size);
    buffer += size;

    // clientIndex
    size = sizeof(clientIndex);
    memcpy(buffer, (void *) &clientIndex, size);
    buffer += size;

    // clusterNo
    size = sizeof(clusterNo);
    memcpy(buffer, (void *) &clusterNo, size);
    buffer += size;

    // frameId
    size = sizeof(frameId);
    memcpy(buffer, (void *) &frameId, size);
    buffer += size;

    // headerCrc1
    size = sizeof(headerCrc1);
    memcpy(buffer, (void *) &headerCrc1, size);
    buffer += size;

    // headerCrc2
    size = sizeof(headerCrc2);
    memcpy(buffer, (void *) &headerCrc2, size);
    buffer += size;

    // byteCount
    size = sizeof(byteCount);
    memcpy(buffer, (void *) &byteCount, size);
    buffer += size;

    // dataCount
    size = sizeof(dataCount);
    memcpy(buffer, (void *) &dataCount, size);
    buffer += size;

    // cycle
    size = sizeof(cycle);
    memcpy(buffer, (void *) &cycle, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy(buffer, (void *) &reserved2, size);
    buffer += size;

    // tag
    size = sizeof(tag);
    memcpy(buffer, (void *) &tag, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy(buffer, (void *) &data, size);
    buffer += size;

    // frameFlags
    size = sizeof(frameFlags);
    memcpy(buffer, (void *) &frameFlags, size);
    buffer += size;

    // appParameter
    size = sizeof(appParameter);
    memcpy(buffer, (void *) &appParameter, size);
    buffer += size;

    // dataBytes
    size = sizeof(dataBytes);
    memcpy(buffer, (void *) &dataBytes, size);
    buffer += size;

    return buffer;
}

size_t FlexRayVFrReceiveMsg::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(channelMask) +
        sizeof(dir) +
        sizeof(reserved1) +
        sizeof(clientIndex) +
        sizeof(clusterNo) +
        sizeof(frameId) +
        sizeof(headerCrc1) +
        sizeof(headerCrc2) +
        sizeof(byteCount) +
        sizeof(dataCount) +
        sizeof(cycle) +
        sizeof(reserved2) +
        sizeof(tag) +
        sizeof(data) +
        sizeof(frameFlags) +
        sizeof(appParameter) +
        sizeof(dataBytes);

    return size;
}

}
}
