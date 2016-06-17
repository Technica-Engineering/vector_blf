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

#include "Most50Pkt.h"

namespace Vector {
namespace BLF {

Most50Pkt::Most50Pkt() :
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
    pktDataLength(),
    reserved6(),
    pktData()
{
    objectType = ObjectType::MOST_50_PKT;
}

void Most50Pkt::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    is.read(reinterpret_cast<char *>(&sourceAdr), sizeof(sourceAdr));
    is.read(reinterpret_cast<char *>(&destAdr), sizeof(destAdr));
    is.read(reinterpret_cast<char *>(&transferType), sizeof(transferType));
    is.read(reinterpret_cast<char *>(&state), sizeof(state));
    is.read(reinterpret_cast<char *>(&ackNack), sizeof(ackNack));
    is.read(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    is.read(reinterpret_cast<char *>(&crc), sizeof(crc));
    is.read(reinterpret_cast<char *>(&reserved3), sizeof(reserved3));
    is.read(reinterpret_cast<char *>(&reserved4), sizeof(reserved4));
    is.read(reinterpret_cast<char *>(&priority), sizeof(priority));
    is.read(reinterpret_cast<char *>(&reserved5), sizeof(reserved5));
    is.read(reinterpret_cast<char *>(&pktDataLength), sizeof(pktDataLength));
    is.read(reinterpret_cast<char *>(reserved6.data()), reserved6.size());
    pktData.resize(pktDataLength);
    is.read(reinterpret_cast<char *>(pktData.data()), pktDataLength);
}

void Most50Pkt::write(AbstractFile & os)
{
    /* pre processing */
    pktDataLength = pktData.size();

    ObjectHeader2::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    os.write(reinterpret_cast<char *>(&sourceAdr), sizeof(sourceAdr));
    os.write(reinterpret_cast<char *>(&destAdr), sizeof(destAdr));
    os.write(reinterpret_cast<char *>(&transferType), sizeof(transferType));
    os.write(reinterpret_cast<char *>(&state), sizeof(state));
    os.write(reinterpret_cast<char *>(&ackNack), sizeof(ackNack));
    os.write(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    os.write(reinterpret_cast<char *>(&crc), sizeof(crc));
    os.write(reinterpret_cast<char *>(&reserved3), sizeof(reserved3));
    os.write(reinterpret_cast<char *>(&reserved4), sizeof(reserved4));
    os.write(reinterpret_cast<char *>(&priority), sizeof(priority));
    os.write(reinterpret_cast<char *>(&reserved5), sizeof(reserved5));
    os.write(reinterpret_cast<char *>(&pktDataLength), sizeof(pktDataLength));
    os.write(reinterpret_cast<char *>(reserved6.data()), reserved6.size());
    os.write(reinterpret_cast<char *>(pktData.data()), pktDataLength);
}

size_t Most50Pkt::calculateObjectSize()
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
        sizeof(pktDataLength) +
        reserved6.size() +
        pktDataLength;

    return size;
}

}
}
