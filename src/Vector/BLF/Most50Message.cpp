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

#include "Most50Message.h"

namespace Vector {
namespace BLF {

Most50Message::Most50Message() :
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
    msgLen(),
    reserved6(),
    msg()
{
    objectType = ObjectType::MOST_50_MESSAGE;
}

void Most50Message::read(AbstractFile & is)
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
    is.read((char *) &reserved3, sizeof(reserved3));
    is.read((char *) &reserved4, sizeof(reserved4));
    is.read((char *) &priority, sizeof(priority));
    is.read((char *) &reserved5, sizeof(reserved5));
    is.read((char *) &msgLen, sizeof(msgLen));
    is.read((char *) reserved6.data(), reserved6.size());
    msg.resize(msgLen);
    is.read((char *) msg.data(), msgLen);
}

void Most50Message::write(AbstractFile & os)
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
    os.write((char *) &reserved3, sizeof(reserved3));
    os.write((char *) &reserved4, sizeof(reserved4));
    os.write((char *) &priority, sizeof(priority));
    os.write((char *) &reserved5, sizeof(reserved5));
    os.write((char *) &msgLen, sizeof(msgLen));
    os.write((char *) reserved6.data(), reserved6.size());
    os.write((char *) msg.data(), msgLen);
}

size_t Most50Message::calculateObjectSize()
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
        sizeof(msgLen) +
        reserved6.size() +
        msgLen;

    return size;
}

}
}
