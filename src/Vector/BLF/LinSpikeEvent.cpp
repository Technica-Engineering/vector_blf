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

#include <Vector/BLF/LinSpikeEvent.h>

namespace Vector {
namespace BLF {

LinSpikeEvent::LinSpikeEvent() :
    ObjectHeader(ObjectType::LIN_SPIKE_EVENT) {
}

std::vector<uint8_t>::iterator LinSpikeEvent::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedLinSpikeEvent =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    width =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);

    return it;
}

void LinSpikeEvent::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((reservedLinSpikeEvent >>  0) & 0xff);
    data.push_back((reservedLinSpikeEvent >>  8) & 0xff);
    data.push_back((width >>  0) & 0xff);
    data.push_back((width >>  8) & 0xff);
    data.push_back((width >> 16) & 0xff);
    data.push_back((width >> 24) & 0xff);
}

DWORD LinSpikeEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reservedLinSpikeEvent) +
        sizeof(width);
}

}
}
