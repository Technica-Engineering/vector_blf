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
    firstData()
{
    objectType = ObjectType::MOST_ETHERNET_PKT_FRAGMENT;
}

void MostEthernetPktFragment::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    is.read(reinterpret_cast<char *>(&ackNack), sizeof(ackNack));
    is.read(reinterpret_cast<char *>(&validMask), sizeof(validMask));
    is.read(reinterpret_cast<char *>(&sourceMacAdr), sizeof(sourceMacAdr));
    is.read(reinterpret_cast<char *>(&destMacAdr), sizeof(destMacAdr));
    is.read(reinterpret_cast<char *>(&pAck), sizeof(pAck));
    is.read(reinterpret_cast<char *>(&cAck), sizeof(cAck));
    is.read(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    is.read(reinterpret_cast<char *>(&crc), sizeof(crc));
    is.read(reinterpret_cast<char *>(&dataLen), sizeof(dataLen));
    is.read(reinterpret_cast<char *>(&dataLenAnnounced), sizeof(dataLenAnnounced));
    is.read(reinterpret_cast<char *>(&firstDataLen), sizeof(firstDataLen));
    is.read(reinterpret_cast<char *>(reserved3.data()), reserved3.size());
    firstData.resize(firstDataLen);
    is.read(reinterpret_cast<char *>(firstData.data()), firstDataLen);
}

void MostEthernetPktFragment::write(AbstractFile & os)
{
    /* pre processing */
    firstDataLen = firstData.size();

    ObjectHeader2::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    os.write(reinterpret_cast<char *>(&ackNack), sizeof(ackNack));
    os.write(reinterpret_cast<char *>(&validMask), sizeof(validMask));
    os.write(reinterpret_cast<char *>(&sourceMacAdr), sizeof(sourceMacAdr));
    os.write(reinterpret_cast<char *>(&destMacAdr), sizeof(destMacAdr));
    os.write(reinterpret_cast<char *>(&pAck), sizeof(pAck));
    os.write(reinterpret_cast<char *>(&cAck), sizeof(cAck));
    os.write(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    os.write(reinterpret_cast<char *>(&crc), sizeof(crc));
    os.write(reinterpret_cast<char *>(&dataLen), sizeof(dataLen));
    os.write(reinterpret_cast<char *>(&dataLenAnnounced), sizeof(dataLenAnnounced));
    os.write(reinterpret_cast<char *>(&firstDataLen), sizeof(firstDataLen));
    os.write(reinterpret_cast<char *>(reserved3.data()), reserved3.size());
    os.write(reinterpret_cast<char *>(firstData.data()), firstDataLen);
}

DWORD MostEthernetPktFragment::calculateObjectSize() const
{
    return
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
        reserved3.size() +
        firstDataLen;
}

}
}
