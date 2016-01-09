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

#include "MostPkt.h"

#include <cstring>

namespace Vector {
namespace BLF {

MostPkt::MostPkt() :
    ObjectHeader(),
    channel(),
    dir(),
    reserved1(),
    sourceAdr(),
    destAdr(),
    arbitration(),
    timeRes(),
    quadsToFollow(),
    reserved2(),
    crc(),
    priority(),
    transferType(),
    state(),
    reserved3(),
    pktDataLength(),
    reserved4(),
    pktData()
{
    objectType = ObjectType::MOST_PKT;
}

MostPkt::~MostPkt()
{
}

char * MostPkt::read(char * buffer)
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

    // reserved1
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    // sourceAdr
    size = sizeof(sourceAdr);
    memcpy((void *) &sourceAdr, buffer, size);
    buffer += size;

    // destAdr
    size = sizeof(destAdr);
    memcpy((void *) &destAdr, buffer, size);
    buffer += size;

    // arbitration
    size = sizeof(arbitration);
    memcpy((void *) &arbitration, buffer, size);
    buffer += size;

    // timeRes
    size = sizeof(timeRes);
    memcpy((void *) &timeRes, buffer, size);
    buffer += size;

    // quadsToFollow
    size = sizeof(quadsToFollow);
    memcpy((void *) &quadsToFollow, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((void *) &reserved2, buffer, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy((void *) &crc, buffer, size);
    buffer += size;

    // priority
    size = sizeof(priority);
    memcpy((void *) &priority, buffer, size);
    buffer += size;

    // transferType
    size = sizeof(transferType);
    memcpy((void *) &transferType, buffer, size);
    buffer += size;

    // state
    size = sizeof(state);
    memcpy((void *) &state, buffer, size);
    buffer += size;

    // reserved3
    size = reserved3.size();
    memcpy(reserved3.data(), buffer, size);
    buffer += size;

    // pktDataLength
    size = sizeof(pktDataLength);
    memcpy((void *) &pktDataLength, buffer, size);
    buffer += size;

    // reserved4
    size = reserved4.size();
    memcpy(reserved4.data(), buffer, size);
    buffer += size;

    // pktData
    size = pktDataLength;
    pktData.reserve(size);
    memcpy(pktData.data(), buffer, size);
    buffer += size;

    return buffer;
}

char * MostPkt::write(char * buffer)
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

    // reserved1
    size = sizeof(reserved1);
    memcpy(buffer, (void *) &reserved1, size);
    buffer += size;

    // sourceAdr
    size = sizeof(sourceAdr);
    memcpy(buffer, (void *) &sourceAdr, size);
    buffer += size;

    // destAdr
    size = sizeof(destAdr);
    memcpy(buffer, (void *) &destAdr, size);
    buffer += size;

    // arbitration
    size = sizeof(arbitration);
    memcpy(buffer, (void *) &arbitration, size);
    buffer += size;

    // timeRes
    size = sizeof(timeRes);
    memcpy(buffer, (void *) &timeRes, size);
    buffer += size;

    // quadsToFollow
    size = sizeof(quadsToFollow);
    memcpy(buffer, (void *) &quadsToFollow, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy(buffer, (void *) &reserved2, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy(buffer, (void *) &crc, size);
    buffer += size;

    // priority
    size = sizeof(priority);
    memcpy(buffer, (void *) &priority, size);
    buffer += size;

    // transferType
    size = sizeof(transferType);
    memcpy(buffer, (void *) &transferType, size);
    buffer += size;

    // state
    size = sizeof(state);
    memcpy(buffer, (void *) &state, size);
    buffer += size;

    // reserved3
    size = reserved3.size();
    memcpy(buffer, reserved3.data(), size);
    buffer += size;

    // pktDataLength
    size = sizeof(pktDataLength);
    memcpy(buffer, (void *) &pktDataLength, size);
    buffer += size;

    // reserved4
    size = reserved4.size();
    memcpy(buffer, reserved4.data(), size);
    buffer += size;

    // pktData
    size = pktDataLength;
    memcpy(buffer, pktData.data(), size);
    buffer += size;

    return buffer;
}

size_t MostPkt::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reserved1) +
        sizeof(sourceAdr) +
        sizeof(destAdr) +
        sizeof(arbitration) +
        sizeof(timeRes) +
        sizeof(quadsToFollow) +
        sizeof(reserved2) +
        sizeof(crc) +
        sizeof(priority) +
        sizeof(transferType) +
        sizeof(state) +
        reserved3.size() +
        sizeof(pktDataLength) +
        reserved4.size() +
        pktDataLength;

    return size;
}

}
}
