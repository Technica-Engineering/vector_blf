/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
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

#include <Vector/BLF/Most50Message.h>

namespace Vector {
namespace BLF {

Most50Message::Most50Message() :
    ObjectHeader2(ObjectType::MOST_50_MESSAGE) {
}

void Most50Message::read(AbstractFile & is) {
    ObjectHeader2::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&reservedMost50Message1), sizeof(reservedMost50Message1));
    is.read(reinterpret_cast<char *>(&sourceAdr), sizeof(sourceAdr));
    is.read(reinterpret_cast<char *>(&destAdr), sizeof(destAdr));
    is.read(reinterpret_cast<char *>(&transferType), sizeof(transferType));
    is.read(reinterpret_cast<char *>(&state), sizeof(state));
    is.read(reinterpret_cast<char *>(&ackNack), sizeof(ackNack));
    is.read(reinterpret_cast<char *>(&reservedMost50Message2), sizeof(reservedMost50Message2));
    is.read(reinterpret_cast<char *>(&crc), sizeof(crc));
    is.read(reinterpret_cast<char *>(&reservedMost50Message3), sizeof(reservedMost50Message3));
    is.read(reinterpret_cast<char *>(&priority), sizeof(priority));
    is.read(reinterpret_cast<char *>(&reservedMost50Message4), sizeof(reservedMost50Message4));
    is.read(reinterpret_cast<char *>(&msgLen), sizeof(msgLen));
    is.read(reinterpret_cast<char *>(&reservedMost50Message5), sizeof(reservedMost50Message5));
    msg.resize(msgLen);
    is.read(reinterpret_cast<char *>(msg.data()), msgLen);

    /* skip padding */
    is.seekg(objectSize % 4, std::ios_base::cur);
}

void Most50Message::write(AbstractFile & os) {
    /* pre processing */
    msgLen = static_cast<DWORD>(msg.size());

    ObjectHeader2::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&reservedMost50Message1), sizeof(reservedMost50Message1));
    os.write(reinterpret_cast<char *>(&sourceAdr), sizeof(sourceAdr));
    os.write(reinterpret_cast<char *>(&destAdr), sizeof(destAdr));
    os.write(reinterpret_cast<char *>(&transferType), sizeof(transferType));
    os.write(reinterpret_cast<char *>(&state), sizeof(state));
    os.write(reinterpret_cast<char *>(&ackNack), sizeof(ackNack));
    os.write(reinterpret_cast<char *>(&reservedMost50Message2), sizeof(reservedMost50Message2));
    os.write(reinterpret_cast<char *>(&crc), sizeof(crc));
    os.write(reinterpret_cast<char *>(&reservedMost50Message3), sizeof(reservedMost50Message3));
    os.write(reinterpret_cast<char *>(&priority), sizeof(priority));
    os.write(reinterpret_cast<char *>(&reservedMost50Message4), sizeof(reservedMost50Message4));
    os.write(reinterpret_cast<char *>(&msgLen), sizeof(msgLen));
    os.write(reinterpret_cast<char *>(&reservedMost50Message5), sizeof(reservedMost50Message5));
    os.write(reinterpret_cast<char *>(msg.data()), msgLen);

    /* skip padding */
    os.seekp(objectSize % 4, std::ios_base::cur);
}

DWORD Most50Message::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedMost50Message1) +
        sizeof(sourceAdr) +
        sizeof(destAdr) +
        sizeof(transferType) +
        sizeof(state) +
        sizeof(ackNack) +
        sizeof(reservedMost50Message2) +
        sizeof(crc) +
        sizeof(reservedMost50Message3) +
        sizeof(priority) +
        sizeof(reservedMost50Message4) +
        sizeof(msgLen) +
        sizeof(reservedMost50Message5) +
        msgLen;
}

}
}
