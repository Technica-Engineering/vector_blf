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

#include "MostPkt2.h"

namespace Vector {
namespace BLF {

MostPkt2::MostPkt2() :
    ObjectHeader2(),
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
    objectType = ObjectType::MOST_PKT2;
}

void MostPkt2::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &sourceAdr, sizeof(sourceAdr));
    is.read((char *) &destAdr, sizeof(destAdr));
    is.read((char *) &arbitration, sizeof(arbitration));
    is.read((char *) &timeRes, sizeof(timeRes));
    is.read((char *) &quadsToFollow, sizeof(quadsToFollow));
    is.read((char *) &reserved2, sizeof(reserved2));
    is.read((char *) &crc, sizeof(crc));
    is.read((char *) &priority, sizeof(priority));
    is.read((char *) &transferType, sizeof(transferType));
    is.read((char *) &state, sizeof(state));
    is.read((char *) reserved3.data(), reserved3.size());
    is.read((char *) &pktDataLength, sizeof(pktDataLength));
    is.read((char *) reserved4.data(), reserved4.size());
    pktData.resize(pktDataLength);
    is.read((char *) pktData.data(), pktDataLength);
}

void MostPkt2::write(AbstractFile & os)
{
    /* pre processing */
    pktDataLength = pktData.size();

    ObjectHeader2::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &sourceAdr, sizeof(sourceAdr));
    os.write((char *) &destAdr, sizeof(destAdr));
    os.write((char *) &arbitration, sizeof(arbitration));
    os.write((char *) &timeRes, sizeof(timeRes));
    os.write((char *) &quadsToFollow, sizeof(quadsToFollow));
    os.write((char *) &reserved2, sizeof(reserved2));
    os.write((char *) &crc, sizeof(crc));
    os.write((char *) &priority, sizeof(priority));
    os.write((char *) &transferType, sizeof(transferType));
    os.write((char *) &state, sizeof(state));
    os.write((char *) reserved3.data(), reserved3.size());
    os.write((char *) &pktDataLength, sizeof(pktDataLength));
    os.write((char *) reserved4.data(), reserved4.size());
    os.write((char *) pktData.data(), pktDataLength);
}

size_t MostPkt2::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
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
