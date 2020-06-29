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

#include <Vector/BLF/LinShortOrSlowResponse.h>

namespace Vector {
namespace BLF {

LinShortOrSlowResponse::LinShortOrSlowResponse() :
    ObjectHeader(ObjectType::LIN_SHORT_OR_SLOW_RESPONSE) {
}

std::vector<uint8_t>::iterator LinShortOrSlowResponse::fromData(std::vector<uint8_t>::iterator it) {
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
    reservedLinShortOrSlowResponse =
            (static_cast<BYTE>(*it++) <<  0);

    return it;
}

void LinShortOrSlowResponse::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);
    LinDatabyteTimestampEvent::toData(data);

    data.push_back((numberOfRespBytes >>  0) & 0xff);
    data.push_back((numberOfRespBytes >>  8) & 0xff);
    data.push_back((numberOfRespBytes >> 16) & 0xff);
    data.push_back((numberOfRespBytes >> 24) & 0xff);
    data.insert(std::end(data), std::begin(respBytes), std::end(respBytes));
    data.push_back((slowResponse >>  0) & 0xff);
    data.push_back((interruptedByBreak >>  0) & 0xff);
    data.push_back((reservedLinShortOrSlowResponse >>  0) & 0xff);
}

DWORD LinShortOrSlowResponse::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        sizeof(numberOfRespBytes) +
        static_cast<DWORD>(respBytes.size()) +
        sizeof(slowResponse) +
        sizeof(interruptedByBreak) +
        sizeof(reservedLinShortOrSlowResponse);
}

}
}
