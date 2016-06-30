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
    reserved2(),
    firstData()
{
    objectType = ObjectType::MOST_150_PKT_FRAGMENT;
}

void Most150PktFragment::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    is.read(reinterpret_cast<char *>(&ackNack), sizeof(ackNack));
    is.read(reinterpret_cast<char *>(&validMask), sizeof(validMask));
    is.read(reinterpret_cast<char *>(&sourceAdr), sizeof(sourceAdr));
    is.read(reinterpret_cast<char *>(&destAdr), sizeof(destAdr));
    is.read(reinterpret_cast<char *>(&pAck), sizeof(pAck));
    is.read(reinterpret_cast<char *>(&cAck), sizeof(cAck));
    is.read(reinterpret_cast<char *>(&priority), sizeof(priority));
    is.read(reinterpret_cast<char *>(&pIndex), sizeof(pIndex));
    is.read(reinterpret_cast<char *>(&crc), sizeof(crc));
    is.read(reinterpret_cast<char *>(&dataLen), sizeof(dataLen));
    is.read(reinterpret_cast<char *>(&dataLenAnnounced), sizeof(dataLenAnnounced));
    is.read(reinterpret_cast<char *>(&firstDataLen), sizeof(firstDataLen));
    is.read(reinterpret_cast<char *>(reserved2.data()), static_cast<std::streamsize>(reserved2.size()));
    firstData.resize(firstDataLen);
    is.read(reinterpret_cast<char *>(firstData.data()), firstDataLen);
}

void Most150PktFragment::write(AbstractFile & os)
{
    /* pre processing */
    firstDataLen = static_cast<DWORD>(firstData.size());

    ObjectHeader2::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    os.write(reinterpret_cast<char *>(&ackNack), sizeof(ackNack));
    os.write(reinterpret_cast<char *>(&validMask), sizeof(validMask));
    os.write(reinterpret_cast<char *>(&sourceAdr), sizeof(sourceAdr));
    os.write(reinterpret_cast<char *>(&destAdr), sizeof(destAdr));
    os.write(reinterpret_cast<char *>(&pAck), sizeof(pAck));
    os.write(reinterpret_cast<char *>(&cAck), sizeof(cAck));
    os.write(reinterpret_cast<char *>(&priority), sizeof(priority));
    os.write(reinterpret_cast<char *>(&pIndex), sizeof(pIndex));
    os.write(reinterpret_cast<char *>(&crc), sizeof(crc));
    os.write(reinterpret_cast<char *>(&dataLen), sizeof(dataLen));
    os.write(reinterpret_cast<char *>(&dataLenAnnounced), sizeof(dataLenAnnounced));
    os.write(reinterpret_cast<char *>(&firstDataLen), sizeof(firstDataLen));
    os.write(reinterpret_cast<char *>(reserved2.data()), static_cast<std::streamsize>(reserved2.size()));
    os.write(reinterpret_cast<char *>(firstData.data()), firstDataLen);
}

DWORD Most150PktFragment::calculateObjectSize() const
{
    return
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
        static_cast<DWORD>(reserved2.size()) +
        firstDataLen;
}

}
}
