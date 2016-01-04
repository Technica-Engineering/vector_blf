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

#include "EthernetFrame.h"

#include <cstring>

namespace Vector {
namespace BLF {

EthernetFrame::EthernetFrame() :
    ObjectHeader(),
    sourceAddress(),
    channel(),
    destinationAddress(),
    dir(),
    type(),
    tpid(),
    tci(),
    payLoadLength(),
    payLoad()
{
    objectType = ObjectType::ETHERNET_FRAME;
}

EthernetFrame::~EthernetFrame()
{
}

char * EthernetFrame::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // sourceAddress
    size = sizeof(sourceAddress);
    memcpy((void *) &sourceAddress, buffer, size);
    buffer += size;

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // destinationAddress
    size = sizeof(destinationAddress);
    memcpy((void *) &destinationAddress, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((void *) &dir, buffer, size);
    buffer += size;

    // type
    size = sizeof(type);
    memcpy((void *) &type, buffer, size);
    buffer += size;

    // tpid
    size = sizeof(tpid);
    memcpy((void *) &tpid, buffer, size);
    buffer += size;

    // tci
    size = sizeof(tci);
    memcpy((void *) &tci, buffer, size);
    buffer += size;

    // payLoadLength
    size = sizeof(payLoadLength);
    memcpy((void *) &payLoadLength, buffer, size);
    buffer += size;

    // payLoad
    size = payLoadLength;
    payLoad.reserve(size);
    memcpy(payLoad.data(), buffer, size);
    buffer += size;

    return buffer;
}

char * EthernetFrame::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // sourceAddress
    size = sizeof(sourceAddress);
    memcpy(buffer, (void *) &sourceAddress, size);
    buffer += size;

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // destinationAddress
    size = sizeof(destinationAddress);
    memcpy(buffer, (void *) &destinationAddress, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy(buffer, (void *) &dir, size);
    buffer += size;

    // type
    size = sizeof(type);
    memcpy(buffer, (void *) &type, size);
    buffer += size;

    // tpid
    size = sizeof(tpid);
    memcpy(buffer, (void *) &tpid, size);
    buffer += size;

    // tci
    size = sizeof(tci);
    memcpy(buffer, (void *) &tci, size);
    buffer += size;

    // payLoadLength
    size = sizeof(payLoadLength);
    memcpy(buffer, (void *) &payLoadLength, size);
    buffer += size;

    // payLoad
    size = payLoadLength;
    memcpy(buffer, payLoad.data(), size);
    buffer += size;

    return buffer;
}

size_t EthernetFrame::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(sourceAddress) +
        sizeof(channel) +
        sizeof(destinationAddress) +
        sizeof(dir) +
        sizeof(type) +
        sizeof(tpid) +
        sizeof(tci) +
        sizeof(payLoadLength) +
        payLoadLength;

    return size;
}

}
}
