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

#include <Vector/BLF/LinReceiveError2.h>

namespace Vector {
namespace BLF {

LinReceiveError2::LinReceiveError2() :
    ObjectHeader(ObjectType::LIN_RCV_ERROR2, 1) {
}

std::vector<uint8_t>::iterator LinReceiveError2::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);
    it = LinDatabyteTimestampEvent::fromData(it);

    std::copy(it, it + this->data.size(), std::begin(data));
    it += this->data.size();
    fsmId =
        (static_cast<BYTE>(*it++) <<  0);
    fsmState =
        (static_cast<BYTE>(*it++) <<  0);
    stateReason =
        (static_cast<BYTE>(*it++) <<  0);
    offendingByte =
        (static_cast<BYTE>(*it++) <<  0);
    shortError =
        (static_cast<BYTE>(*it++) <<  0);
    timeoutDuringDlcDetection =
        (static_cast<BYTE>(*it++) <<  0);
    isEtf =
        (static_cast<BYTE>(*it++) <<  0);
    hasDatabytes =
        (static_cast<BYTE>(*it++) <<  0);
    respBaudrate =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    reservedLinReceiveError =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    uint64_t * ptr = reinterpret_cast<uint64_t *>(&exactHeaderBaudrate);
    *ptr =
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

void LinReceiveError2::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);
    LinDatabyteTimestampEvent::toData(data);

    data.insert(std::end(data), std::begin(this->data), std::end(this->data));
    data.push_back((fsmId >>  0) & 0xff);
    data.push_back((fsmState >>  0) & 0xff);
    data.push_back((stateReason >>  0) & 0xff);
    data.push_back((offendingByte >>  0) & 0xff);
    data.push_back((shortError >>  0) & 0xff);
    data.push_back((timeoutDuringDlcDetection >>  0) & 0xff);
    data.push_back((isEtf >>  0) & 0xff);
    data.push_back((hasDatabytes >>  0) & 0xff);
    data.push_back((respBaudrate >>  0) & 0xff);
    data.push_back((respBaudrate >>  8) & 0xff);
    data.push_back((respBaudrate >> 16) & 0xff);
    data.push_back((respBaudrate >> 24) & 0xff);
    data.push_back((reservedLinReceiveError >>  0) & 0xff);
    data.push_back((reservedLinReceiveError >>  8) & 0xff);
    data.push_back((reservedLinReceiveError >> 16) & 0xff);
    data.push_back((reservedLinReceiveError >> 24) & 0xff);
    uint64_t * ptr = reinterpret_cast<uint64_t *>(&exactHeaderBaudrate);
    data.push_back((*ptr >>  0) & 0xff);
    data.push_back((*ptr >>  8) & 0xff);
    data.push_back((*ptr >> 16) & 0xff);
    data.push_back((*ptr >> 24) & 0xff);
    data.push_back((*ptr >> 32) & 0xff);
    data.push_back((*ptr >> 40) & 0xff);
    data.push_back((*ptr >> 48) & 0xff);
    data.push_back((*ptr >> 56) & 0xff);
    data.push_back((earlyStopbitOffset >>  0) & 0xff);
    data.push_back((earlyStopbitOffset >>  8) & 0xff);
    data.push_back((earlyStopbitOffset >> 16) & 0xff);
    data.push_back((earlyStopbitOffset >> 24) & 0xff);
    data.push_back((earlyStopbitOffsetResponse >>  0) & 0xff);
    data.push_back((earlyStopbitOffsetResponse >>  8) & 0xff);
    data.push_back((earlyStopbitOffsetResponse >> 16) & 0xff);
    data.push_back((earlyStopbitOffsetResponse >> 24) & 0xff);
}

DWORD LinReceiveError2::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        static_cast<DWORD>(data.size()) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(stateReason) +
        sizeof(offendingByte) +
        sizeof(shortError) +
        sizeof(timeoutDuringDlcDetection) +
        sizeof(isEtf) +
        sizeof(hasDatabytes) +
        sizeof(respBaudrate) +
        sizeof(reservedLinReceiveError) +
        sizeof(exactHeaderBaudrate) +
        sizeof(earlyStopbitOffset) +
        sizeof(earlyStopbitOffsetResponse);
}

}
}
