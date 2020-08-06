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

#include <Vector/BLF/LinDisturbanceEvent.h>

namespace Vector {
namespace BLF {

LinDisturbanceEvent::LinDisturbanceEvent() :
    ObjectHeader(ObjectType::LIN_DISTURBANCE_EVENT) {
}

std::vector<uint8_t>::iterator LinDisturbanceEvent::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    id =
        (static_cast<BYTE>(*it++) <<  0);
    disturbingFrameId =
        (static_cast<BYTE>(*it++) <<  0);
    disturbanceType =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    byteIndex =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    bitIndex =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    bitOffsetInSixteenthBits =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    disturbanceLengthInSixteenthBits =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);

    return it;
}

void LinDisturbanceEvent::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((id >>  0) & 0xff);
    data.push_back((disturbingFrameId >>  0) & 0xff);
    data.push_back((disturbanceType >>  0) & 0xff);
    data.push_back((disturbanceType >>  8) & 0xff);
    data.push_back((disturbanceType >> 16) & 0xff);
    data.push_back((disturbanceType >> 24) & 0xff);
    data.push_back((byteIndex >>  0) & 0xff);
    data.push_back((byteIndex >>  8) & 0xff);
    data.push_back((byteIndex >> 16) & 0xff);
    data.push_back((byteIndex >> 24) & 0xff);
    data.push_back((bitIndex >>  0) & 0xff);
    data.push_back((bitIndex >>  8) & 0xff);
    data.push_back((bitIndex >> 16) & 0xff);
    data.push_back((bitIndex >> 24) & 0xff);
    data.push_back((bitOffsetInSixteenthBits >>  0) & 0xff);
    data.push_back((bitOffsetInSixteenthBits >>  8) & 0xff);
    data.push_back((bitOffsetInSixteenthBits >> 16) & 0xff);
    data.push_back((bitOffsetInSixteenthBits >> 24) & 0xff);
    data.push_back((disturbanceLengthInSixteenthBits >>  0) & 0xff);
    data.push_back((disturbanceLengthInSixteenthBits >>  8) & 0xff);
    data.push_back((disturbanceLengthInSixteenthBits >> 16) & 0xff);
    data.push_back((disturbanceLengthInSixteenthBits >> 24) & 0xff);
}

DWORD LinDisturbanceEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(id) +
        sizeof(disturbingFrameId) +
        sizeof(disturbanceType) +
        sizeof(byteIndex) +
        sizeof(bitIndex) +
        sizeof(bitOffsetInSixteenthBits) +
        sizeof(disturbanceLengthInSixteenthBits);
}

}
}
