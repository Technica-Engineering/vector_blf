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

#include <Vector/BLF/WaterMarkEvent.h>

namespace Vector {
namespace BLF {

WaterMarkEvent::WaterMarkEvent() :
    ObjectHeader(ObjectType::WATER_MARK_EVENT) {
}

std::vector<uint8_t>::iterator WaterMarkEvent::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    queueState =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedWaterMarkEvent =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);

    return it;
}

void WaterMarkEvent::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((queueState >>  0) & 0xff);
    data.push_back((queueState >>  8) & 0xff);
    data.push_back((queueState >> 16) & 0xff);
    data.push_back((queueState >> 24) & 0xff);
    data.push_back((reservedWaterMarkEvent >>  0) & 0xff);
    data.push_back((reservedWaterMarkEvent >>  8) & 0xff);
    data.push_back((reservedWaterMarkEvent >> 16) & 0xff);
    data.push_back((reservedWaterMarkEvent >> 24) & 0xff);
}

DWORD WaterMarkEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(queueState) +
        sizeof(reservedWaterMarkEvent);
}

}
}
