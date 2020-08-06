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

#include <Vector/BLF/FlexRaySync.h>

namespace Vector {
namespace BLF {

FlexRaySync::FlexRaySync() :
    ObjectHeader(ObjectType::FLEXRAY_SYNC) {
}

std::vector<uint8_t>::iterator FlexRaySync::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    mux =
        (static_cast<BYTE>(*it++) <<  0);
    len =
        (static_cast<BYTE>(*it++) <<  0);
    messageId =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    crc =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    dir =
        (static_cast<BYTE>(*it++) <<  0);
    reservedFlexRaySync1 =
        (static_cast<BYTE>(*it++) <<  0);
    reservedFlexRaySync2 =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    std::copy(it, it + dataBytes.size(), std::begin(dataBytes));
    it += dataBytes.size();
    cycle =
        (static_cast<BYTE>(*it++) <<  0);

    return it;
}

void FlexRaySync::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((mux >>  0) & 0xff);
    data.push_back((len >>  0) & 0xff);
    data.push_back((messageId >>  0) & 0xff);
    data.push_back((messageId >>  8) & 0xff);
    data.push_back((crc >>  0) & 0xff);
    data.push_back((crc >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((reservedFlexRaySync1 >>  0) & 0xff);
    data.push_back((reservedFlexRaySync2 >>  0) & 0xff);
    data.push_back((reservedFlexRaySync2 >>  8) & 0xff);
    data.insert(std::end(data), std::begin(dataBytes), std::end(dataBytes));
    data.push_back((cycle >>  0) & 0xff);
}

DWORD FlexRaySync::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(mux) +
        sizeof(len) +
        sizeof(messageId) +
        sizeof(crc) +
        sizeof(dir) +
        sizeof(reservedFlexRaySync1) +
        sizeof(reservedFlexRaySync2) +
        static_cast<DWORD>(dataBytes.size()) +
        sizeof(cycle);
}

}
}
