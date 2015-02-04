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

#include "AfdxFrame.h"

#include <cstring>
#include <iostream>

namespace Vector {
namespace BLF {

AfdxFrame::AfdxFrame() :
    ObjectHeader(),
    sourceAddress(),
    channel(),
    destinationAddress(),
    dir(),
    type(),
    tpid(),
    tci(),
    ethChannel(),
    reserved1(),
    afdxFlags(),
    reserved2(),
    bagUsec(),
    payLoadLength(),
    reserved3(),
    payLoad(nullptr)
{
}

AfdxFrame::~AfdxFrame()
{
    delete[] payLoad;
    payLoad = nullptr;
}

char * AfdxFrame::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // sourceAddress
    size = sizeof(sourceAddress);
    memcpy((char *) &sourceAddress, buffer, size);
    buffer += size;

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // destinationAddress
    size = sizeof(destinationAddress);
    memcpy((char *) &destinationAddress, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((char *) &dir, buffer, size);
    buffer += size;

    // type
    size = sizeof(type);
    memcpy((char *) &type, buffer, size);
    buffer += size;

    // tpid
    size = sizeof(tpid);
    memcpy((char *) &tpid, buffer, size);
    buffer += size;

    // tci
    size = sizeof(tci);
    memcpy((char *) &tci, buffer, size);
    buffer += size;

    // ethChannel
    size = sizeof(ethChannel);
    memcpy((char *) &ethChannel, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((char *) &reserved1, buffer, size);
    buffer += size;

    // afdxFlags
    size = sizeof(afdxFlags);
    memcpy((char *) &afdxFlags, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((char *) &reserved2, buffer, size);
    buffer += size;

    // bagUsec
    size = sizeof(bagUsec);
    memcpy((char *) &bagUsec, buffer, size);
    buffer += size;

    // payLoadLength
    size = sizeof(payLoadLength);
    memcpy((char *) &payLoadLength, buffer, size);
    buffer += size;

    // reserved3
    size = sizeof(reserved3);
    memcpy((char *) &reserved3, buffer, size);
    buffer += size;

    // payLoad
    size = payLoadLength;
    payLoad = new uint8_t[size];
    memcpy(payLoad, buffer, size);
    buffer += size;

    return buffer;
}

size_t AfdxFrame::calculateObjectSize()
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
            sizeof(ethChannel) +
            sizeof(reserved1) +
            sizeof(afdxFlags) +
            sizeof(reserved2) +
            sizeof(bagUsec) +
            sizeof(payLoadLength) +
            sizeof(reserved3) +
            payLoadLength;

    return size;
}

}
}
