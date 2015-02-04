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
    pktData(nullptr)
{
}

MostPkt::~MostPkt()
{
    delete[] pktData;
    pktData = nullptr;
}

char * MostPkt::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((char *) &dir, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((char *) &reserved1, buffer, size);
    buffer += size;

    // sourceAdr
    size = sizeof(sourceAdr);
    memcpy((char *) &sourceAdr, buffer, size);
    buffer += size;

    // destAdr
    size = sizeof(destAdr);
    memcpy((char *) &destAdr, buffer, size);
    buffer += size;

    // arbitration
    size = sizeof(arbitration);
    memcpy((char *) &arbitration, buffer, size);
    buffer += size;

    // timeRes
    size = sizeof(timeRes);
    memcpy((char *) &timeRes, buffer, size);
    buffer += size;

    // quadsToFollow
    size = sizeof(quadsToFollow);
    memcpy((char *) &quadsToFollow, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((char *) &reserved2, buffer, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy((char *) &crc, buffer, size);
    buffer += size;

    // priority
    size = sizeof(priority);
    memcpy((char *) &priority, buffer, size);
    buffer += size;

    // transferType
    size = sizeof(transferType);
    memcpy((char *) &transferType, buffer, size);
    buffer += size;

    // state
    size = sizeof(state);
    memcpy((char *) &state, buffer, size);
    buffer += size;

    // reserved3
    size = sizeof(reserved3);
    memcpy((char *) &reserved3, buffer, size);
    buffer += size;

    // pktDataLength
    size = sizeof(pktDataLength);
    memcpy((char *) &pktDataLength, buffer, size);
    buffer += size;

    // reserved4
    size = sizeof(reserved4);
    memcpy((char *) &reserved4, buffer, size);
    buffer += size;

    // pktData
    size = pktDataLength;
    pktData = new uint8_t[pktDataLength];
    memcpy(pktData, buffer, size);
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
            sizeof(reserved3) +
            sizeof(pktDataLength) +
            sizeof(reserved4) +
            pktDataLength;

    return size;
}

}
}
