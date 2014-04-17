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

#include "MostEthernetPktFragment.h"

#include <cstring>

namespace Vector {
namespace BLF {

MostEthernetPktFragment::MostEthernetPktFragment() :
    ObjectHeader2(),
    channel(),
    reserved1(),
    ackNack(),
    validMask(),
    sourceMacAdr(),
    destMacAdr(),
    pAck(),
    cAck(),
    reserved2(),
    crc(),
    dataLen(),
    dataLenAnnounced(),
    firstDataLen(),
    reserved3(),
    firstData(nullptr)
{
}

MostEthernetPktFragment::~MostEthernetPktFragment()
{
    delete[] firstData;
    firstData = nullptr;
}

char * MostEthernetPktFragment::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader2::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((char *) &reserved1, buffer, size);
    buffer += size;

    // ackNack
    size = sizeof(ackNack);
    memcpy((char *) &ackNack, buffer, size);
    buffer += size;

    // validMask
    size = sizeof(validMask);
    memcpy((char *) &validMask, buffer, size);
    buffer += size;

    // sourceMacAdr
    size = sizeof(sourceMacAdr);
    memcpy((char *) &sourceMacAdr, buffer, size);
    buffer += size;

    // destMacAdr
    size = sizeof(destMacAdr);
    memcpy((char *) &destMacAdr, buffer, size);
    buffer += size;

    // pAck
    size = sizeof(pAck);
    memcpy((char *) &pAck, buffer, size);
    buffer += size;

    // cAck
    size = sizeof(cAck);
    memcpy((char *) &cAck, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((char *) &reserved2, buffer, size);
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

    // reserved3
    size = sizeof(reserved3);
    memcpy((char *) &reserved3, buffer, size);
    buffer += size;

    // firstData
    size = firstDataLen;
    firstData = new char[firstDataLen];
    memcpy(firstData, buffer, size);
    buffer += size;

    return buffer;
}

size_t MostEthernetPktFragment::calculateObjectSize()
{
    size_t size =
            ObjectHeader2::calculateObjectSize() +
            sizeof(channel) +
            sizeof(reserved1) +
            sizeof(ackNack) +
            sizeof(validMask) +
            sizeof(sourceMacAdr) +
            sizeof(destMacAdr) +
            sizeof(pAck) +
            sizeof(cAck) +
            sizeof(reserved2) +
            sizeof(crc) +
            sizeof(dataLen) +
            sizeof(dataLenAnnounced) +
            sizeof(firstDataLen) +
            sizeof(reserved3) +
            firstDataLen;

    return size;
}

}
}
