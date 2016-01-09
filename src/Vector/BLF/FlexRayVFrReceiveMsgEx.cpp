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

#include "FlexRayVFrReceiveMsgEx.h"

#include <cstring>

namespace Vector {
namespace BLF {

FlexRayVFrReceiveMsgEx::FlexRayVFrReceiveMsgEx() :
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
    frameCrc(),
    frameLengthNs(),
    frameId1(),
    pduOffset(),
    blfLogMask(),
    reserved(),
    dataBytes()
{
    objectType = ObjectType::FR_RCVMESSAGE_EX;
}

char * FlexRayVFrReceiveMsgEx::read(char * buffer)
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

    // frameCrc
    size = sizeof(frameCrc);
    memcpy((void *) &frameCrc, buffer, size);
    buffer += size;

    // frameLengthNs
    size = sizeof(frameLengthNs);
    memcpy((void *) &frameLengthNs, buffer, size);
    buffer += size;

    // frameId1
    size = sizeof(frameId1);
    memcpy((void *) &frameId1, buffer, size);
    buffer += size;

    // pduOffset
    size = sizeof(pduOffset);
    memcpy((void *) &pduOffset, buffer, size);
    buffer += size;

    // blfLogMask
    size = sizeof(blfLogMask);
    memcpy((void *) &blfLogMask, buffer, size);
    buffer += size;

    // reserved
    size = reserved.size();
    memcpy(reserved.data(), buffer, size);
    buffer += size;

    // dataBytes
    size = dataCount;
    dataBytes.reserve(size);
    memcpy(dataBytes.data(), buffer, size);
    buffer += size;

    return buffer;
}

char * FlexRayVFrReceiveMsgEx::write(char * buffer)
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

    // frameCrc
    size = sizeof(frameCrc);
    memcpy(buffer, (void *) &frameCrc, size);
    buffer += size;

    // frameLengthNs
    size = sizeof(frameLengthNs);
    memcpy(buffer, (void *) &frameLengthNs, size);
    buffer += size;

    // frameId1
    size = sizeof(frameId1);
    memcpy(buffer, (void *) &frameId1, size);
    buffer += size;

    // pduOffset
    size = sizeof(pduOffset);
    memcpy(buffer, (void *) &pduOffset, size);
    buffer += size;

    // blfLogMask
    size = sizeof(blfLogMask);
    memcpy(buffer, (void *) &blfLogMask, size);
    buffer += size;

    // reserved
    size = reserved.size();
    memcpy(buffer, reserved.data(), size);
    buffer += size;

    // dataBytes
    size = dataCount;
    memcpy(buffer, dataBytes.data(), size);
    buffer += size;

    return buffer;
}

size_t FlexRayVFrReceiveMsgEx::calculateObjectSize()
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
        sizeof(frameCrc) +
        sizeof(frameLengthNs) +
        sizeof(frameId1) +
        sizeof(pduOffset) +
        sizeof(blfLogMask) +
        reserved.size() +
        dataCount;

    return size;
}

}
}
