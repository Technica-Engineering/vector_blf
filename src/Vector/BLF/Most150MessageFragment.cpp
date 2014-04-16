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

#include "Most150MessageFragment.h"

namespace Vector {
namespace BLF {

Most150MessageFragment::Most150MessageFragment() :
    ObjectHeader2(),
    channel(),
    dummy1(),
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

Most150MessageFragment::~Most150MessageFragment()
{
    delete[] firstData;
    firstData = nullptr;
}

char * Most150MessageFragment::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader2::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // dummy1
    size = sizeof(dummy1);
    memcpy((char *) &dummy1, buffer, size);
    buffer += size;

    // ackNack
    size = sizeof(ackNack);
    memcpy((char *) &ackNack, buffer, size);
    buffer += size;

    // validMask
    size = sizeof(validMask);
    memcpy((char *) &validMask, buffer, size);
    buffer += size;

    // sourceAdr
    size = sizeof(sourceAdr);
    memcpy((char *) &sourceAdr, buffer, size);
    buffer += size;

    // destAdr
    size = sizeof(destAdr);
    memcpy((char *) &destAdr, buffer, size);
    buffer += size;

    // pAck
    size = sizeof(pAck);
    memcpy((char *) &pAck, buffer, size);
    buffer += size;

    // cAck
    size = sizeof(cAck);
    memcpy((char *) &cAck, buffer, size);
    buffer += size;

    // priority
    size = sizeof(priority);
    memcpy((char *) &priority, buffer, size);
    buffer += size;

    // pIndex
    size = sizeof(pIndex);
    memcpy((char *) &pIndex, buffer, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy((char *) &crc, buffer, size);
    buffer += size;

    // dataLen
    size = sizeof(dataLen);
    memcpy((char *) &dataLen, buffer, size);
    buffer += size;

    // dataLenAnnounced
    size = sizeof(dataLenAnnounced);
    memcpy((char *) &dataLenAnnounced, buffer, size);
    buffer += size;

    // firstDataLen
    size = sizeof(firstDataLen);
    memcpy((char *) &firstDataLen, buffer, size);
    buffer += size;

    // firstData
    size = sizeof(firstDataLen);
    firstData = new char[firstDataLen];
    memcpy(firstData, buffer, size);
    buffer += size;

    return buffer;
}

size_t Most150MessageFragment::calculateObjectSize()
{
    size_t size =
            ObjectHeader2::calculateObjectSize() +
            sizeof(channel) +
            sizeof(dummy1) +
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
