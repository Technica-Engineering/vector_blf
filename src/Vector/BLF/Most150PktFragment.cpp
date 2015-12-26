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

#include "Most150PktFragment.h"

#include <cstring>

namespace Vector {
namespace BLF {

Most150PktFragment::Most150PktFragment() :
    ObjectHeader2(),
    channel(),
    reserved1(),
    ackNack(),
    validMask(),
    sourceAdr(),
    destAdr(),
    pAck(),
    cAck(),
    priority(),
    pIndex(),
    crc(),
    dataLen(),
    dataLenAnnounced(),
    firstDataLen(),
    firstData(nullptr)
{
}

Most150PktFragment::~Most150PktFragment()
{
    delete[] firstData;
    firstData = nullptr;
}

char * Most150PktFragment::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader2::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    // ackNack
    size = sizeof(ackNack);
    memcpy((void *) &ackNack, buffer, size);
    buffer += size;

    // validMask
    size = sizeof(validMask);
    memcpy((void *) &validMask, buffer, size);
    buffer += size;

    // sourceAdr
    size = sizeof(sourceAdr);
    memcpy((void *) &sourceAdr, buffer, size);
    buffer += size;

    // destAdr
    size = sizeof(destAdr);
    memcpy((void *) &destAdr, buffer, size);
    buffer += size;

    // pAck
    size = sizeof(pAck);
    memcpy((void *) &pAck, buffer, size);
    buffer += size;

    // cAck
    size = sizeof(cAck);
    memcpy((void *) &cAck, buffer, size);
    buffer += size;

    // priority
    size = sizeof(priority);
    memcpy((void *) &priority, buffer, size);
    buffer += size;

    // pIndex
    size = sizeof(pIndex);
    memcpy((void *) &pIndex, buffer, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy((void *) &crc, buffer, size);
    buffer += size;

    // dataLen
    size = sizeof(dataLen);
    memcpy((void *) &dataLen, buffer, size);
    buffer += size;

    // dataLenAnnounced
    size = sizeof(dataLenAnnounced);
    memcpy((void *) &dataLenAnnounced, buffer, size);
    buffer += size;

    // firstDataLen
    size = sizeof(firstDataLen);
    memcpy((void *) &firstDataLen, buffer, size);
    buffer += size;

    // firstData
    size = firstDataLen;
    firstData = new char[size];
    memcpy(firstData, buffer, size);
    buffer += size;

    return buffer;
}

char * Most150PktFragment::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader2::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy(buffer, (void *) &reserved1, size);
    buffer += size;

    // ackNack
    size = sizeof(ackNack);
    memcpy(buffer, (void *) &ackNack, size);
    buffer += size;

    // validMask
    size = sizeof(validMask);
    memcpy(buffer, (void *) &validMask, size);
    buffer += size;

    // sourceAdr
    size = sizeof(sourceAdr);
    memcpy(buffer, (void *) &sourceAdr, size);
    buffer += size;

    // destAdr
    size = sizeof(destAdr);
    memcpy(buffer, (void *) &destAdr, size);
    buffer += size;

    // pAck
    size = sizeof(pAck);
    memcpy(buffer, (void *) &pAck, size);
    buffer += size;

    // cAck
    size = sizeof(cAck);
    memcpy(buffer, (void *) &cAck, size);
    buffer += size;

    // priority
    size = sizeof(priority);
    memcpy(buffer, (void *) &priority, size);
    buffer += size;

    // pIndex
    size = sizeof(pIndex);
    memcpy(buffer, (void *) &pIndex, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy(buffer, (void *) &crc, size);
    buffer += size;

    // dataLen
    size = sizeof(dataLen);
    memcpy(buffer, (void *) &dataLen, size);
    buffer += size;

    // dataLenAnnounced
    size = sizeof(dataLenAnnounced);
    memcpy(buffer, (void *) &dataLenAnnounced, size);
    buffer += size;

    // firstDataLen
    size = sizeof(firstDataLen);
    memcpy(buffer, (void *) &firstDataLen, size);
    buffer += size;

    // firstData
    size = firstDataLen;
    memcpy(buffer, firstData, size);
    buffer += size;

    return buffer;
}

size_t Most150PktFragment::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reserved1) +
        sizeof(ackNack) +
        sizeof(validMask) +
        sizeof(sourceAdr) +
        sizeof(destAdr) +
        sizeof(pAck) +
        sizeof(cAck) +
        sizeof(priority) +
        sizeof(pIndex) +
        sizeof(crc) +
        sizeof(dataLen) +
        sizeof(dataLenAnnounced) +
        sizeof(firstDataLen) +
        firstDataLen;

    return size;
}

}
}
