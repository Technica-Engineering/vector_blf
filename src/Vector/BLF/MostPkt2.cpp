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
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    is.read(reinterpret_cast<char *>(&sourceAdr), sizeof(sourceAdr));
    is.read(reinterpret_cast<char *>(&destAdr), sizeof(destAdr));
    is.read(reinterpret_cast<char *>(&arbitration), sizeof(arbitration));
    is.read(reinterpret_cast<char *>(&timeRes), sizeof(timeRes));
    is.read(reinterpret_cast<char *>(&quadsToFollow), sizeof(quadsToFollow));
    is.read(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    is.read(reinterpret_cast<char *>(&crc), sizeof(crc));
    is.read(reinterpret_cast<char *>(&priority), sizeof(priority));
    is.read(reinterpret_cast<char *>(&transferType), sizeof(transferType));
    is.read(reinterpret_cast<char *>(&state), sizeof(state));
    is.read(reinterpret_cast<char *>(reserved3.data()), static_cast<std::streamsize>(reserved3.size()));
    is.read(reinterpret_cast<char *>(&pktDataLength), sizeof(pktDataLength));
    is.read(reinterpret_cast<char *>(reserved4.data()), static_cast<std::streamsize>(reserved4.size()));
    pktData.resize(pktDataLength);
    is.read(reinterpret_cast<char *>(pktData.data()), pktDataLength);
}

void MostPkt2::write(AbstractFile & os)
{
    /* pre processing */
    pktDataLength = static_cast<DWORD>(pktData.size());

    ObjectHeader2::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    os.write(reinterpret_cast<char *>(&sourceAdr), sizeof(sourceAdr));
    os.write(reinterpret_cast<char *>(&destAdr), sizeof(destAdr));
    os.write(reinterpret_cast<char *>(&arbitration), sizeof(arbitration));
    os.write(reinterpret_cast<char *>(&timeRes), sizeof(timeRes));
    os.write(reinterpret_cast<char *>(&quadsToFollow), sizeof(quadsToFollow));
    os.write(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    os.write(reinterpret_cast<char *>(&crc), sizeof(crc));
    os.write(reinterpret_cast<char *>(&priority), sizeof(priority));
    os.write(reinterpret_cast<char *>(&transferType), sizeof(transferType));
    os.write(reinterpret_cast<char *>(&state), sizeof(state));
    os.write(reinterpret_cast<char *>(reserved3.data()), static_cast<std::streamsize>(reserved3.size()));
    os.write(reinterpret_cast<char *>(&pktDataLength), sizeof(pktDataLength));
    os.write(reinterpret_cast<char *>(reserved4.data()), static_cast<std::streamsize>(reserved4.size()));
    os.write(reinterpret_cast<char *>(pktData.data()), pktDataLength);
}

DWORD MostPkt2::calculateObjectSize() const
{
    return
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
        static_cast<DWORD>(reserved3.size()) +
        sizeof(pktDataLength) +
        static_cast<DWORD>(reserved4.size()) +
        pktDataLength;
}

}
}
