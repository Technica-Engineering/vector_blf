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

#include "EthernetStatus.h"

#include <cstring>

namespace Vector {
namespace BLF {

EthernetStatus::EthernetStatus() :
    ObjectHeader(),
    channel(),
    flags(),
    linkStatus(),
    ethernetPhy(),
    duplex(),
    mdi(),
    connector(),
    clockMode(),
    pairs(),
    reserved(),
    bitrate()
{
}

char * EthernetStatus::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((void *) &flags, buffer, size);
    buffer += size;

    // linkStatus
    size = sizeof(linkStatus);
    memcpy((void *) &linkStatus, buffer, size);
    buffer += size;

    // ethernetPhy
    size = sizeof(ethernetPhy);
    memcpy((void *) &ethernetPhy, buffer, size);
    buffer += size;

    // duplex
    size = sizeof(duplex);
    memcpy((void *) &duplex, buffer, size);
    buffer += size;

    // mdi
    size = sizeof(mdi);
    memcpy((void *) &mdi, buffer, size);
    buffer += size;

    // connector
    size = sizeof(connector);
    memcpy((void *) &connector, buffer, size);
    buffer += size;

    // clockMode
    size = sizeof(clockMode);
    memcpy((void *) &clockMode, buffer, size);
    buffer += size;

    // pairs
    size = sizeof(pairs);
    memcpy((void *) &pairs, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // bitrate
    size = sizeof(bitrate);
    memcpy((void *) &bitrate, buffer, size);
    buffer += size;

    return buffer;
}

size_t EthernetStatus::calculateObjectSize()
{
    size_t size =
            ObjectHeader::calculateObjectSize() +
            sizeof(channel) +
            sizeof(flags) +
            sizeof(linkStatus) +
            sizeof(ethernetPhy) +
            sizeof(duplex) +
            sizeof(mdi) +
            sizeof(connector) +
            sizeof(clockMode) +
            sizeof(pairs) +
            sizeof(reserved) +
            sizeof(bitrate);

    return size;
}

}
}
