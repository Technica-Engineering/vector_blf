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

std::vector<uint8_t>::iterator LinCrcError2::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);
    it = LinDatabyteTimestampEvent::fromData(it);

    std::copy(it, it + this->data.size(), std::begin(this->data));
    it += this->data.size();
    crc =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    dir =
            (static_cast<BYTE>(*it++) <<  0);
    fsmId =
            (static_cast<BYTE>(*it++) <<  0);
    fsmState =
            (static_cast<BYTE>(*it++) <<  0);
    simulated =
            (static_cast<BYTE>(*it++) <<  0);
    reservedLinCrcError1 =
            (static_cast<BYTE>(*it++) <<  0);
    respBaudrate =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedLinCrcError2 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    exactHeaderBaudrate =
            (static_cast<uint64_t>(*it++) <<  0) |
            (static_cast<uint64_t>(*it++) <<  8) |
            (static_cast<uint64_t>(*it++) << 16) |
            (static_cast<uint64_t>(*it++) << 24) |
            (static_cast<uint64_t>(*it++) << 32) |
            (static_cast<uint64_t>(*it++) << 40) |
            (static_cast<uint64_t>(*it++) << 48) |
            (static_cast<uint64_t>(*it++) << 56);
    earlyStopbitOffset =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    earlyStopbitOffsetResponse =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    return it;
}

void LinCrcError2::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);
    LinDatabyteTimestampEvent::toData(data);

    data.insert(std::end(data), std::begin(this->data), std::end(this->data));
    data.push_back((crc >>  0) & 0xff);
    data.push_back((crc >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((fsmId >>  0) & 0xff);
    data.push_back((fsmState >>  0) & 0xff);
    data.push_back((simulated >>  0) & 0xff);
    data.push_back((reservedLinCrcError1 >>  0) & 0xff);
    data.push_back((reservedLinCrcError1 >>  8) & 0xff);
    data.push_back((respBaudrate >>  0) & 0xff);
    data.push_back((respBaudrate >>  8) & 0xff);
    data.push_back((respBaudrate >> 16) & 0xff);
    data.push_back((respBaudrate >> 24) & 0xff);
    data.push_back((reservedLinCrcError2 >>  0) & 0xff);
    data.push_back((reservedLinCrcError2 >>  8) & 0xff);
    data.push_back((reservedLinCrcError2 >> 16) & 0xff);
    data.push_back((reservedLinCrcError2 >> 24) & 0xff);
    data.push_back((static_cast<uint64_t>(exactHeaderBaudrate) >>  0) & 0xff);
    data.push_back((static_cast<uint64_t>(exactHeaderBaudrate) >>  8) & 0xff);
    data.push_back((static_cast<uint64_t>(exactHeaderBaudrate) >> 16) & 0xff);
    data.push_back((static_cast<uint64_t>(exactHeaderBaudrate) >> 24) & 0xff);
    data.push_back((static_cast<uint64_t>(exactHeaderBaudrate) >> 32) & 0xff);
    data.push_back((static_cast<uint64_t>(exactHeaderBaudrate) >> 40) & 0xff);
    data.push_back((static_cast<uint64_t>(exactHeaderBaudrate) >> 48) & 0xff);
    data.push_back((static_cast<uint64_t>(exactHeaderBaudrate) >> 56) & 0xff);
    data.push_back((earlyStopbitOffset >>  0) & 0xff);
    data.push_back((earlyStopbitOffset >>  8) & 0xff);
    data.push_back((earlyStopbitOffset >> 16) & 0xff);
    data.push_back((earlyStopbitOffset >> 24) & 0xff);
    data.push_back((earlyStopbitOffsetResponse >>  0) & 0xff);
    data.push_back((earlyStopbitOffsetResponse >>  8) & 0xff);
    data.push_back((earlyStopbitOffsetResponse >> 16) & 0xff);
    data.push_back((earlyStopbitOffsetResponse >> 24) & 0xff);
}

DWORD LinCrcError2::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        static_cast<DWORD>(data.size()) +
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
