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
    payLoad()
{
    objectType = ObjectType::AFDX_FRAME;
}

AfdxFrame::~AfdxFrame()
{
}

char * AfdxFrame::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // sourceAddress
    size = sourceAddress.size();
    memcpy(sourceAddress.data(), buffer, size);
    buffer += size;

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // destinationAddress
    size = destinationAddress.size();
    memcpy(destinationAddress.data(), buffer, size);
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

    // ethChannel
    size = sizeof(ethChannel);
    memcpy((void *) &ethChannel, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    // afdxFlags
    size = sizeof(afdxFlags);
    memcpy((void *) &afdxFlags, buffer, size);
    buffer += size;

    // reserved2
    size = reserved2.size();
    memcpy(reserved2.data(), buffer, size);
    buffer += size;

    // bagUsec
    size = sizeof(bagUsec);
    memcpy((void *) &bagUsec, buffer, size);
    buffer += size;

    // payLoadLength
    size = sizeof(payLoadLength);
    memcpy((void *) &payLoadLength, buffer, size);
    buffer += size;

    // reserved3
    size = reserved3.size();
    memcpy(reserved3.data(), buffer, size);
    buffer += size;

    // payLoad
    size = payLoadLength;
    payLoad.reserve(size);
    memcpy(payLoad.data(), buffer, size);
    buffer += size;

    return buffer;
}

char * AfdxFrame::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // sourceAddress
    size = sourceAddress.size();
    memcpy(buffer, sourceAddress.data(), size);
    buffer += size;

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // destinationAddress
    size = destinationAddress.size();
    memcpy(buffer, destinationAddress.data(), size);
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

    // ethChannel
    size = sizeof(ethChannel);
    memcpy(buffer, (void *) &ethChannel, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy(buffer, (void *) &reserved1, size);
    buffer += size;

    // afdxFlags
    size = sizeof(afdxFlags);
    memcpy(buffer, (void *) &afdxFlags, size);
    buffer += size;

    // reserved2
    size = reserved2.size();
    memcpy(buffer, reserved2.data(), size);
    buffer += size;

    // bagUsec
    size = sizeof(bagUsec);
    memcpy(buffer, (void *) &bagUsec, size);
    buffer += size;

    // payLoadLength
    size = sizeof(payLoadLength);
    memcpy(buffer, (void *) &payLoadLength, size);
    buffer += size;

    // reserved3
    size = reserved3.size();
    memcpy(buffer, reserved3.data(), size);
    buffer += size;

    // payLoad
    size = payLoadLength;
    memcpy(buffer, payLoad.data(), size);
    buffer += size;

    return buffer;
}

size_t AfdxFrame::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sourceAddress.size() +
        sizeof(channel) +
        destinationAddress.size() +
        sizeof(dir) +
        sizeof(type) +
        sizeof(tpid) +
        sizeof(tci) +
        sizeof(ethChannel) +
        sizeof(reserved1) +
        sizeof(afdxFlags) +
        reserved2.size() +
        sizeof(bagUsec) +
        sizeof(payLoadLength) +
        reserved3.size() +
        payLoadLength;

    return size;
}

}
}
