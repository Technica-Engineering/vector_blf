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

#include <Vector/BLF/LinCrcError2.h>

namespace Vector {
namespace BLF {

LinCrcError2::LinCrcError2() :
    ObjectHeader(ObjectType::LIN_CRC_ERROR2) {
}

void LinCrcError2::read(AbstractFile & is) {
    ObjectHeader::read(is);
    LinDatabyteTimestampEvent::read(is);
    is.read(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size()));
    is.read(reinterpret_cast<char *>(&crc), sizeof(crc));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&fsmId), sizeof(fsmId));
    is.read(reinterpret_cast<char *>(&fsmState), sizeof(fsmState));
    is.read(reinterpret_cast<char *>(&simulated), sizeof(simulated));
    is.read(reinterpret_cast<char *>(&reservedLinCrcError1), sizeof(reservedLinCrcError1));
    is.read(reinterpret_cast<char *>(&respBaudrate), sizeof(respBaudrate));
    is.read(reinterpret_cast<char *>(&reservedLinCrcError2), sizeof(reservedLinCrcError2));
    is.read(reinterpret_cast<char *>(&exactHeaderBaudrate), sizeof(exactHeaderBaudrate));
    is.read(reinterpret_cast<char *>(&earlyStopbitOffset), sizeof(earlyStopbitOffset));
    is.read(reinterpret_cast<char *>(&earlyStopbitOffsetResponse), sizeof(earlyStopbitOffsetResponse));
    // @note might be extended in future versions
}

void LinCrcError2::write(AbstractFile & os) {
    ObjectHeader::write(os);
    LinDatabyteTimestampEvent::write(os);
    os.write(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size()));
    os.write(reinterpret_cast<char *>(&crc), sizeof(crc));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&fsmId), sizeof(fsmId));
    os.write(reinterpret_cast<char *>(&fsmState), sizeof(fsmState));
    os.write(reinterpret_cast<char *>(&simulated), sizeof(simulated));
    os.write(reinterpret_cast<char *>(&reservedLinCrcError1), sizeof(reservedLinCrcError1));
    os.write(reinterpret_cast<char *>(&respBaudrate), sizeof(respBaudrate));
    os.write(reinterpret_cast<char *>(&reservedLinCrcError2), sizeof(reservedLinCrcError2));
    os.write(reinterpret_cast<char *>(&exactHeaderBaudrate), sizeof(exactHeaderBaudrate));
    os.write(reinterpret_cast<char *>(&earlyStopbitOffset), sizeof(earlyStopbitOffset));
    os.write(reinterpret_cast<char *>(&earlyStopbitOffsetResponse), sizeof(earlyStopbitOffsetResponse));
}

uint32_t LinCrcError2::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        static_cast<uint32_t>(data.size()) +
        sizeof(crc) +
        sizeof(dir) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(simulated) +
        sizeof(reservedLinCrcError1) +
        sizeof(respBaudrate) +
        sizeof(reservedLinCrcError2) +
        sizeof(exactHeaderBaudrate) +
        sizeof(earlyStopbitOffset) +
        sizeof(earlyStopbitOffsetResponse);
}

}
}
