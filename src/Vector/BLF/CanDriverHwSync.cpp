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

#include <Vector/BLF/CanDriverHwSync.h>

namespace Vector {
namespace BLF {

CanDriverHwSync::CanDriverHwSync() :
    ObjectHeader(ObjectType::CAN_DRIVER_SYNC) {
}

std::vector<uint8_t>::iterator CanDriverHwSync::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    flags =
        (static_cast<BYTE>(*it++) <<  0);
    reservedCanDriverHwSync1 =
        (static_cast<BYTE>(*it++) <<  0);
    reservedCanDriverHwSync2 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);

    return it;
}

void CanDriverHwSync::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((flags >>  0) & 0xff);
    data.push_back((reservedCanDriverHwSync1 >>  0) & 0xff);
    data.push_back((reservedCanDriverHwSync2 >>  0) & 0xff);
    data.push_back((reservedCanDriverHwSync2 >>  8) & 0xff);
    data.push_back((reservedCanDriverHwSync2 >> 16) & 0xff);
    data.push_back((reservedCanDriverHwSync2 >> 24) & 0xff);
}

DWORD CanDriverHwSync::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(reservedCanDriverHwSync1) +
        sizeof(reservedCanDriverHwSync2);
}

}
}
