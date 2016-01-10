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
    msg()
{
    objectType = ObjectType::MOST_150_MESSAGE;
}

void Most150Message::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &sourceAdr, sizeof(sourceAdr));
    is.read((char *) &destAdr, sizeof(destAdr));
    is.read((char *) &transferType, sizeof(transferType));
    is.read((char *) &state, sizeof(state));
    is.read((char *) &ackNack, sizeof(ackNack));
    is.read((char *) &reserved2, sizeof(reserved2));
    is.read((char *) &crc, sizeof(crc));
    is.read((char *) &pAck, sizeof(pAck));
    is.read((char *) &cAck, sizeof(cAck));
    is.read((char *) &priority, sizeof(priority));
    is.read((char *) &pIndex, sizeof(pIndex));
    is.read((char *) &msgLen, sizeof(msgLen));
    is.read((char *) reserved3.data(), reserved3.size());
    msg.resize(msgLen);
    is.read((char *) msg.data(), msgLen);
}

void Most150Message::write(AbstractFile & os)
{
    /* pre processing */
    msgLen = msg.size();

    ObjectHeader2::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &sourceAdr, sizeof(sourceAdr));
    os.write((char *) &destAdr, sizeof(destAdr));
    os.write((char *) &transferType, sizeof(transferType));
    os.write((char *) &state, sizeof(state));
    os.write((char *) &ackNack, sizeof(ackNack));
    os.write((char *) &reserved2, sizeof(reserved2));
    os.write((char *) &crc, sizeof(crc));
    os.write((char *) &pAck, sizeof(pAck));
    os.write((char *) &cAck, sizeof(cAck));
    os.write((char *) &priority, sizeof(priority));
    os.write((char *) &pIndex, sizeof(pIndex));
    os.write((char *) &msgLen, sizeof(msgLen));
    os.write((char *) reserved3.data(), reserved3.size());
    os.write((char *) msg.data(), msgLen);
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
        reserved3.size() +
        msgLen;

    return size;
}

}
}
