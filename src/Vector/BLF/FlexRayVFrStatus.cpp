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

#include "FlexRayVFrStatus.h"

namespace Vector {
namespace BLF {

FlexRayVFrStatus::FlexRayVFrStatus() :
    ObjectHeader(),
    channel(),
    version(),
    channelMask(),
    cycle(),
    clientIndex(),
    clusterNo(),
    wus(),
    ccSyncState(),
    tag(),
    data(),
    reserved()
{
}

char * FlexRayVFrStatus::parse(char * buffer)
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

    // cycle
    size = sizeof(cycle);
    memcpy((char *) &cycle, buffer, size);
    buffer += size;

    // clientIndex
    size = sizeof(clientIndex);
    memcpy((char *) &clientIndex, buffer, size);
    buffer += size;

    // clusterNo
    size = sizeof(clusterNo);
    memcpy((char *) &clusterNo, buffer, size);
    buffer += size;

    // wus
    size = sizeof(wus);
    memcpy((char *) &wus, buffer, size);
    buffer += size;

    // ccSyncState
    size = sizeof(ccSyncState);
    memcpy((char *) &ccSyncState, buffer, size);
    buffer += size;

    // tag
    size = sizeof(tag);
    memcpy((char *) &tag, buffer, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy((char *) &data, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((char *) &reserved, buffer, size);
    buffer += size;

    return buffer;
}

size_t FlexRayVFrStatus::calculateObjectSize()
{
    size_t size =
            ObjectHeader::calculateObjectSize() +
            sizeof(channel) +
            sizeof(version) +
            sizeof(channelMask) +
            sizeof(cycle) +
            sizeof(clientIndex) +
            sizeof(clusterNo) +
            sizeof(wus) +
            sizeof(ccSyncState) +
            sizeof(tag) +
            sizeof(data) +
            sizeof(reserved);

    return size;
}

}
}
