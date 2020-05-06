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

#include <Vector/BLF/MostSpy.h>

namespace Vector {
namespace BLF {

MostSpy::MostSpy() :
    ObjectHeader(ObjectType::MOST_SPY) {
}

void MostSpy::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&reservedMostSpy1), sizeof(reservedMostSpy1));
    is.read(reinterpret_cast<char *>(&sourceAdr), sizeof(sourceAdr));
    is.read(reinterpret_cast<char *>(&destAdr), sizeof(destAdr));
    is.read(reinterpret_cast<char *>(msg.data()), static_cast<std::streamsize>(msg.size()));
    is.read(reinterpret_cast<char *>(&reservedMostSpy2), sizeof(reservedMostSpy2));
    is.read(reinterpret_cast<char *>(&rTyp), sizeof(rTyp));
    is.read(reinterpret_cast<char *>(&rTypAdr), sizeof(rTypAdr));
    is.read(reinterpret_cast<char *>(&state), sizeof(state));
    is.read(reinterpret_cast<char *>(&reservedMostSpy3), sizeof(reservedMostSpy3));
    is.read(reinterpret_cast<char *>(&ackNack), sizeof(ackNack));
    is.read(reinterpret_cast<char *>(&crc), sizeof(crc));
}

void MostSpy::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&reservedMostSpy1), sizeof(reservedMostSpy1));
    os.write(reinterpret_cast<char *>(&sourceAdr), sizeof(sourceAdr));
    os.write(reinterpret_cast<char *>(&destAdr), sizeof(destAdr));
    os.write(reinterpret_cast<char *>(msg.data()), static_cast<std::streamsize>(msg.size()));
    os.write(reinterpret_cast<char *>(&reservedMostSpy2), sizeof(reservedMostSpy2));
    os.write(reinterpret_cast<char *>(&rTyp), sizeof(rTyp));
    os.write(reinterpret_cast<char *>(&rTypAdr), sizeof(rTypAdr));
    os.write(reinterpret_cast<char *>(&state), sizeof(state));
    os.write(reinterpret_cast<char *>(&reservedMostSpy3), sizeof(reservedMostSpy3));
    os.write(reinterpret_cast<char *>(&ackNack), sizeof(ackNack));
    os.write(reinterpret_cast<char *>(&crc), sizeof(crc));
}

DWORD MostSpy::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedMostSpy1) +
        sizeof(sourceAdr) +
        sizeof(destAdr) +
        static_cast<DWORD>(msg.size()) +
        sizeof(reservedMostSpy2) +
        sizeof(rTyp) +
        sizeof(rTypAdr) +
        sizeof(state) +
        sizeof(reservedMostSpy3) +
        sizeof(ackNack) +
        sizeof(crc);
}

}
}
