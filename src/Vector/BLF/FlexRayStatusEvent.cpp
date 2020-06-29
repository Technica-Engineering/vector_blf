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

#include <Vector/BLF/FlexRayStatusEvent.h>

#include <algorithm>

namespace Vector {
namespace BLF {

FlexRayStatusEvent::FlexRayStatusEvent() :
    ObjectHeader(ObjectType::FLEXRAY_STATUS) {
}

std::vector<uint8_t>::iterator FlexRayStatusEvent::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    version =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    statusType =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    infoMask1 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    infoMask2 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    infoMask3 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    std::generate(reservedFlexRayStatusEvent.begin(), reservedFlexRayStatusEvent.end(), [&it]() {
        return
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    });

    return it;
}

void FlexRayStatusEvent::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((version >>  0) & 0xff);
    data.push_back((version >>  8) & 0xff);
    data.push_back((statusType >>  0) & 0xff);
    data.push_back((statusType >>  8) & 0xff);
    data.push_back((infoMask1 >>  0) & 0xff);
    data.push_back((infoMask1 >>  8) & 0xff);
    data.push_back((infoMask2 >>  0) & 0xff);
    data.push_back((infoMask2 >>  8) & 0xff);
    data.push_back((infoMask3 >>  0) & 0xff);
    data.push_back((infoMask3 >>  8) & 0xff);
    std::for_each(reservedFlexRayStatusEvent.begin(), reservedFlexRayStatusEvent.end(), [&data](const WORD & d) {
        data.push_back((d >>  0) & 0xff);
        data.push_back((d >>  8) & 0xff);
    });
}

DWORD FlexRayStatusEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(statusType) +
        sizeof(infoMask1) +
        sizeof(infoMask2) +
        sizeof(infoMask3) +
        static_cast<DWORD>(reservedFlexRayStatusEvent.size() * sizeof(WORD));
}

}
}
