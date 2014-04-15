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
    afdxFlags(),
    bagUsec(),
    payLoadLength(),
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

    // afdxFlags
    size = sizeof(afdxFlags);
    memcpy((char *) &afdxFlags, buffer, size);
    buffer += size;

    // bagUsec
    size = sizeof(bagUsec);
    memcpy((char *) &bagUsec, buffer, size);
    buffer += size;

    // payLoadLength
    size = sizeof(payLoadLength);
    memcpy((char *) &payLoadLength, buffer, size);
    buffer += size;

    // payLoad
    size = objectSize - 0x3f; // @todo this value should be made more plausible (calculated using sizeof(...))
    payLoad = new char[size];
    memcpy(payLoad, buffer, size);
    buffer += size;

    return buffer;
}

}
}
