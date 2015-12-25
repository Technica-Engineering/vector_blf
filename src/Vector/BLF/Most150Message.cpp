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

#include "Most150Message.h"

#include <cstring>

namespace Vector {
namespace BLF {

Most150Message::Most150Message() :
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
    pAck(),
    cAck(),
    priority(),
    pIndex(),
    msgLen(),
    reserved3(),
    msg(nullptr)
{
}

Most150Message::~Most150Message()
{
    delete[] msg;
    msg = nullptr;
}

char * Most150Message::read(char * buffer)
{
    size_t size;

    // previous data
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

    // msgLen
    size = sizeof(msgLen);
    memcpy((void *) &msgLen, buffer, size);
    buffer += size;

    // reserved3
    size = sizeof(reserved3);
    memcpy((void *) &reserved3, buffer, size);
    buffer += size;

    // msg
    size = msgLen;
    msg = new char[size];
    memcpy((void *) msg, buffer, size);
    buffer += size;

    return buffer;
}

char * Most150Message::write(char * buffer)
{
    // @todo
}

size_t Most150Message::calculateObjectSize()
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
        sizeof(pAck) +
        sizeof(cAck) +
        sizeof(priority) +
        sizeof(pIndex) +
        sizeof(msgLen) +
        sizeof(reserved3) +
        msgLen;

    return size;
}

}
}
