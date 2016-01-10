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

#include "MostEthernetPkt.h"

namespace Vector {
namespace BLF {

MostEthernetPkt::MostEthernetPkt() :
    ObjectHeader2(),
    channel(),
    dir(),
    reserved1(),
    sourceMacAdr(),
    destMacAdr(),
    transferType(),
    state(),
    ackNack(),
    reserved2(),
    crc(),
    pAck(),
    cAck(),
    reserved3(),
    pktDataLength(),
    reserved4(),
    pktData()
{
    objectType = ObjectType::MOST_ETHERNET_PKT;
}

void MostEthernetPkt::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) reserved1.data(), reserved1.size());
    is.read((char *) &sourceMacAdr, sizeof(sourceMacAdr));
    is.read((char *) &destMacAdr, sizeof(destMacAdr));
    is.read((char *) &transferType, sizeof(transferType));
    is.read((char *) &state, sizeof(state));
    is.read((char *) &ackNack, sizeof(ackNack));
    is.read((char *) &reserved2, sizeof(reserved2));
    is.read((char *) &crc, sizeof(crc));
    is.read((char *) &pAck, sizeof(pAck));
    is.read((char *) &cAck, sizeof(cAck));
    is.read((char *) &reserved3, sizeof(reserved3));
    is.read((char *) &pktDataLength, sizeof(pktDataLength));
    is.read((char *) reserved4.data(), reserved4.size());
    pktData.resize(pktDataLength);
    is.read((char *) pktData.data(), pktDataLength);
}

void MostEthernetPkt::write(AbstractFile & os)
{
    /* pre processing */
    pktDataLength = pktData.size();

    ObjectHeader2::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) reserved1.data(), reserved1.size());
    os.write((char *) &sourceMacAdr, sizeof(sourceMacAdr));
    os.write((char *) &destMacAdr, sizeof(destMacAdr));
    os.write((char *) &transferType, sizeof(transferType));
    os.write((char *) &state, sizeof(state));
    os.write((char *) &ackNack, sizeof(ackNack));
    os.write((char *) &reserved2, sizeof(reserved2));
    os.write((char *) &crc, sizeof(crc));
    os.write((char *) &pAck, sizeof(pAck));
    os.write((char *) &cAck, sizeof(cAck));
    os.write((char *) &reserved3, sizeof(reserved3));
    os.write((char *) &pktDataLength, sizeof(pktDataLength));
    os.write((char *) reserved4.data(), reserved4.size());
    os.write((char *) pktData.data(), pktDataLength);
}

size_t MostEthernetPkt::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        reserved1.size() +
        sizeof(sourceMacAdr) +
        sizeof(destMacAdr) +
        sizeof(transferType) +
        sizeof(state) +
        sizeof(ackNack) +
        sizeof(reserved2) +
        sizeof(crc) +
        sizeof(pAck) +
        sizeof(cAck) +
        sizeof(reserved3) +
        sizeof(pktDataLength) +
        reserved4.size() +
        pktDataLength;

    return size;
}

}
}
