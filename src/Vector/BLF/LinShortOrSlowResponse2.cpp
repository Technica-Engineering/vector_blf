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

#include <Vector/BLF/LinShortOrSlowResponse2.h>

namespace Vector {
namespace BLF {

LinShortOrSlowResponse2::LinShortOrSlowResponse2() :
    ObjectHeader(ObjectType::LIN_SHORT_OR_SLOW_RESPONSE2) {
}

std::vector<uint8_t>::iterator LinShortOrSlowResponse2::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);
    it = LinDatabyteTimestampEvent::fromData(it);

    numberOfRespBytes =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    std::copy(it, it + respBytes.size(), std::begin(respBytes));
    it += respBytes.size();
    slowResponse =
        (static_cast<BYTE>(*it++) <<  0);
    interruptedByBreak =
        (static_cast<BYTE>(*it++) <<  0);
    reservedLinShortOrSlowResponse1 =
        (static_cast<BYTE>(*it++) <<  0);
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
    reservedLinShortOrSlowResponse2 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);

    return it;
}

void LinShortOrSlowResponse2::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);
    LinDatabyteTimestampEvent::toData(data);

    data.push_back((numberOfRespBytes >>  0) & 0xff);
    data.push_back((numberOfRespBytes >>  8) & 0xff);
    data.push_back((numberOfRespBytes >> 16) & 0xff);
    data.push_back((numberOfRespBytes >> 24) & 0xff);
    data.insert(std::end(data), std::begin(respBytes), std::end(respBytes));
    data.push_back((slowResponse >>  0) & 0xff);
    data.push_back((interruptedByBreak >>  0) & 0xff);
    data.push_back((reservedLinShortOrSlowResponse1 >>  0) & 0xff);
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
    data.push_back((reservedLinShortOrSlowResponse2 >>  0) & 0xff);
    data.push_back((reservedLinShortOrSlowResponse2 >>  8) & 0xff);
    data.push_back((reservedLinShortOrSlowResponse2 >> 16) & 0xff);
    data.push_back((reservedLinShortOrSlowResponse2 >> 24) & 0xff);

}

DWORD LinShortOrSlowResponse2::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        sizeof(numberOfRespBytes) +
        static_cast<DWORD>(respBytes.size()) +
        sizeof(slowResponse) +
        sizeof(interruptedByBreak) +
        sizeof(reservedLinShortOrSlowResponse1) +
        sizeof(exactHeaderBaudrate) +
        sizeof(earlyStopbitOffset) +
        sizeof(reservedLinShortOrSlowResponse2);
}

}
}
