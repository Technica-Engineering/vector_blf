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

#include "Most50Pkt.h"

#include <cstring>

namespace Vector {
namespace BLF {

Most50Pkt::Most50Pkt() :
    ObjectHeader2(),
    channel(),
    dir(),
    reserved1(),
    sourceAdr(),
    destAdr(),
    transferType(),
    state(),
    ackNack(),
    reserved2(),
    crc(),
    reserved3(),
    reserved4(),
    priority(),
    reserved5(),
    pktDataLength(),
    reserved6(),
    pktData()
{
    objectType = ObjectType::MOST_50_PKT;
}

Most50Pkt::~Most50Pkt()
{
}

char * Most50Pkt::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader2::read(buffer);

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

    // transferType
    size = sizeof(transferType);
    memcpy((void *) &transferType, buffer, size);
    buffer += size;

    // state
    size = sizeof(state);
    memcpy((void *) &state, buffer, size);
    buffer += size;

    // ackNack
    size = sizeof(ackNack);
    memcpy((void *) &ackNack, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((void *) &reserved2, buffer, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy((void *) &crc, buffer, size);
    buffer += size;

    // reserved3
    size = sizeof(reserved3);
    memcpy((void *) &reserved3, buffer, size);
    buffer += size;

    // reserved4
    size = sizeof(reserved4);
    memcpy((void *) &reserved4, buffer, size);
    buffer += size;

    // priority
    size = sizeof(priority);
    memcpy((void *) &priority, buffer, size);
    buffer += size;

    // reserved5
    size = sizeof(reserved5);
    memcpy((void *) &reserved5, buffer, size);
    buffer += size;

    // pktDataLength
    size = sizeof(pktDataLength);
    memcpy((void *) &pktDataLength, buffer, size);
    buffer += size;

    // reserved6
    size = reserved6.size();
    memcpy(reserved6.data(), buffer, size);
    buffer += size;

    // pktData
    size = pktDataLength;
    pktData.reserve(size);
    memcpy(pktData.data(), buffer, size);
    buffer += size;

    return buffer;
}

char * Most50Pkt::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader2::write(buffer);

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

    // transferType
    size = sizeof(transferType);
    memcpy(buffer, (void *) &transferType, size);
    buffer += size;

    // state
    size = sizeof(state);
    memcpy(buffer, (void *) &state, size);
    buffer += size;

    // ackNack
    size = sizeof(ackNack);
    memcpy(buffer, (void *) &ackNack, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy(buffer, (void *) &reserved2, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy(buffer, (void *) &crc, size);
    buffer += size;

    // reserved3
    size = sizeof(reserved3);
    memcpy(buffer, (void *) &reserved3, size);
    buffer += size;

    // reserved4
    size = sizeof(reserved4);
    memcpy(buffer, (void *) &reserved4, size);
    buffer += size;

    // priority
    size = sizeof(priority);
    memcpy(buffer, (void *) &priority, size);
    buffer += size;

    // reserved5
    size = sizeof(reserved5);
    memcpy(buffer, (void *) &reserved5, size);
    buffer += size;

    // pktDataLength
    size = sizeof(pktDataLength);
    memcpy(buffer, (void *) &pktDataLength, size);
    buffer += size;

    // reserved6
    size = reserved6.size();
    memcpy(buffer, reserved6.data(), size);
    buffer += size;

    // pktData
    size = pktDataLength;
    memcpy(buffer, pktData.data(), size);
    buffer += size;

    return buffer;
}

size_t Most50Pkt::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reserved1) +
        sizeof(sourceAdr) +
        sizeof(destAdr) +
        sizeof(transferType) +
        sizeof(state) +
        sizeof(ackNack) +
        sizeof(reserved2) +
        sizeof(crc) +
        sizeof(reserved3) +
        sizeof(reserved4) +
        sizeof(priority) +
        sizeof(reserved5) +
        sizeof(pktDataLength) +
        reserved6.size() +
        pktDataLength;

    return size;
}

}
}
