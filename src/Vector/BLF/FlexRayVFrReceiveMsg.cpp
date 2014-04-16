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
    clientIndex(),
    clusterNo(),
    frameId(),
    headerCrc1(),
    headerCrc2(),
    byteCount(),
    dataCount(),
    cycle(),
    tag(),
    data(),
    frameFlags(),
    appParameter(),
    dataBytes()
{
}

char * FlexRayVFrReceiveMsg::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // version
    size = sizeof(version);
    memcpy((char *) &version, buffer, size);
    buffer += size;

    // channelMask
    size = sizeof(channelMask);
    memcpy((char *) &channelMask, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((char *) &dir, buffer, size);
    buffer += size;

    // clientIndex
    size = sizeof(clientIndex);
    memcpy((char *) &clientIndex, buffer, size);
    buffer += size;

    // clusterNo
    size = sizeof(clusterNo);
    memcpy((char *) &clusterNo, buffer, size);
    buffer += size;

    // frameId
    size = sizeof(frameId);
    memcpy((char *) &frameId, buffer, size);
    buffer += size;

    // headerCrc1
    size = sizeof(headerCrc1);
    memcpy((char *) &headerCrc1, buffer, size);
    buffer += size;

    // headerCrc2
    size = sizeof(headerCrc2);
    memcpy((char *) &headerCrc2, buffer, size);
    buffer += size;

    // byteCount
    size = sizeof(byteCount);
    memcpy((char *) &byteCount, buffer, size);
    buffer += size;

    // dataCount
    size = sizeof(dataCount);
    memcpy((char *) &dataCount, buffer, size);
    buffer += size;

    // cycle
    size = sizeof(cycle);
    memcpy((char *) &cycle, buffer, size);
    buffer += size;

    // tag
    size = sizeof(tag);
    memcpy((char *) &tag, buffer, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy((char *) &data, buffer, size);
    buffer += size;

    // frameFlags
    size = sizeof(frameFlags);
    memcpy((char *) &frameFlags, buffer, size);
    buffer += size;

    // appParameter
    size = sizeof(appParameter);
    memcpy((char *) &appParameter, buffer, size);
    buffer += size;

    // dataBytes
    size = sizeof(dataBytes);
    memcpy((char *) &dataBytes, buffer, size);
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
            sizeof(clientIndex) +
            sizeof(clusterNo) +
            sizeof(frameId) +
            sizeof(headerCrc1) +
            sizeof(headerCrc2) +
            sizeof(byteCount) +
            sizeof(dataCount) +
            sizeof(cycle) +
            sizeof(tag) +
            sizeof(data) +
            sizeof(frameFlags) +
            sizeof(appParameter) +
            sizeof(dataBytes);

    return size;
}

}
}
