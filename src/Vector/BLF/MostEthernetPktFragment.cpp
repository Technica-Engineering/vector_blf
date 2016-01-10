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
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &ackNack, sizeof(ackNack));
    is.read((char *) &validMask, sizeof(validMask));
    is.read((char *) &sourceMacAdr, sizeof(sourceMacAdr));
    is.read((char *) &destMacAdr, sizeof(destMacAdr));
    is.read((char *) &pAck, sizeof(pAck));
    is.read((char *) &cAck, sizeof(cAck));
    is.read((char *) &reserved2, sizeof(reserved2));
    is.read((char *) &crc, sizeof(crc));
    is.read((char *) &dataLen, sizeof(dataLen));
    is.read((char *) &dataLenAnnounced, sizeof(dataLenAnnounced));
    is.read((char *) &firstDataLen, sizeof(firstDataLen));
    is.read((char *) reserved3.data(), reserved3.size());
    firstData.resize(firstDataLen);
    is.read((char *) firstData.data(), firstDataLen);
}

void MostEthernetPktFragment::write(AbstractFile & os)
{
    /* pre processing */
    firstDataLen = firstData.size();

    ObjectHeader2::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &ackNack, sizeof(ackNack));
    os.write((char *) &validMask, sizeof(validMask));
    os.write((char *) &sourceMacAdr, sizeof(sourceMacAdr));
    os.write((char *) &destMacAdr, sizeof(destMacAdr));
    os.write((char *) &pAck, sizeof(pAck));
    os.write((char *) &cAck, sizeof(cAck));
    os.write((char *) &reserved2, sizeof(reserved2));
    os.write((char *) &crc, sizeof(crc));
    os.write((char *) &dataLen, sizeof(dataLen));
    os.write((char *) &dataLenAnnounced, sizeof(dataLenAnnounced));
    os.write((char *) &firstDataLen, sizeof(firstDataLen));
    os.write((char *) reserved3.data(), reserved3.size());
    os.write((char *) firstData.data(), firstDataLen);
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
        reserved3.size() +
        firstDataLen;

    return size;
}

}
}
