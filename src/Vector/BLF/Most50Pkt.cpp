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

#include <Vector/BLF/Most50Pkt.h>

namespace Vector {
namespace BLF {

Most50Pkt::Most50Pkt() :
    ObjectHeader2(),
    channel(),
    dir(),
    reservedMost50Pkt1(),
    sourceAdr(),
    destAdr(),
    transferType(),
    state(),
    ackNack(),
    reservedMost50Pkt2(),
    crc(),
    reservedMost50Pkt3(),
    priority(),
    reservedMost50Pkt4(),
    pktDataLength(),
    reservedMost50Pkt5(),
    pktData()
{
    objectType = ObjectType::MOST_50_PKT;
}

void Most50Pkt::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&reservedMost50Pkt1), sizeof(reservedMost50Pkt1));
    is.read(reinterpret_cast<char *>(&sourceAdr), sizeof(sourceAdr));
    is.read(reinterpret_cast<char *>(&destAdr), sizeof(destAdr));
    is.read(reinterpret_cast<char *>(&transferType), sizeof(transferType));
    is.read(reinterpret_cast<char *>(&state), sizeof(state));
    is.read(reinterpret_cast<char *>(&ackNack), sizeof(ackNack));
    is.read(reinterpret_cast<char *>(&reservedMost50Pkt2), sizeof(reservedMost50Pkt2));
    is.read(reinterpret_cast<char *>(&crc), sizeof(crc));
    is.read(reinterpret_cast<char *>(&reservedMost50Pkt3), sizeof(reservedMost50Pkt3));
    is.read(reinterpret_cast<char *>(&priority), sizeof(priority));
    is.read(reinterpret_cast<char *>(&reservedMost50Pkt4), sizeof(reservedMost50Pkt4));
    is.read(reinterpret_cast<char *>(&pktDataLength), sizeof(pktDataLength));
    is.read(reinterpret_cast<char *>(&reservedMost50Pkt5), sizeof(reservedMost50Pkt5));
    pktData.resize(pktDataLength);
    is.read(reinterpret_cast<char *>(pktData.data()), pktDataLength);

    /* skip padding */
    is.seekg(objectSize % 4, std::ios_base::cur);
}

void Most50Pkt::write(AbstractFile & os)
{
    /* pre processing */
    pktDataLength = static_cast<DWORD>(pktData.size());

    ObjectHeader2::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&reservedMost50Pkt1), sizeof(reservedMost50Pkt1));
    os.write(reinterpret_cast<char *>(&sourceAdr), sizeof(sourceAdr));
    os.write(reinterpret_cast<char *>(&destAdr), sizeof(destAdr));
    os.write(reinterpret_cast<char *>(&transferType), sizeof(transferType));
    os.write(reinterpret_cast<char *>(&state), sizeof(state));
    os.write(reinterpret_cast<char *>(&ackNack), sizeof(ackNack));
    os.write(reinterpret_cast<char *>(&reservedMost50Pkt2), sizeof(reservedMost50Pkt2));
    os.write(reinterpret_cast<char *>(&crc), sizeof(crc));
    os.write(reinterpret_cast<char *>(&reservedMost50Pkt3), sizeof(reservedMost50Pkt3));
    os.write(reinterpret_cast<char *>(&priority), sizeof(priority));
    os.write(reinterpret_cast<char *>(&reservedMost50Pkt4), sizeof(reservedMost50Pkt4));
    os.write(reinterpret_cast<char *>(&pktDataLength), sizeof(pktDataLength));
    os.write(reinterpret_cast<char *>(&reservedMost50Pkt5), sizeof(reservedMost50Pkt5));
    os.write(reinterpret_cast<char *>(pktData.data()), pktDataLength);

    /* skip padding */
    os.skipp(objectSize % 4);
}

DWORD Most50Pkt::calculateObjectSize() const
{
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedMost50Pkt1) +
        sizeof(sourceAdr) +
        sizeof(destAdr) +
        sizeof(transferType) +
        sizeof(state) +
        sizeof(ackNack) +
        sizeof(reservedMost50Pkt2) +
        sizeof(crc) +
        sizeof(reservedMost50Pkt3) +
        sizeof(priority) +
        sizeof(reservedMost50Pkt4) +
        sizeof(pktDataLength) +
        sizeof(reservedMost50Pkt5) +
        pktDataLength;
}

}
}
