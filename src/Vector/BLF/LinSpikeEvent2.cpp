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

#include <Vector/BLF/LinSpikeEvent2.h>

namespace Vector {
namespace BLF {

LinSpikeEvent2::LinSpikeEvent2() :
    ObjectHeader(ObjectType::LIN_SPIKE_EVENT2) {
}

std::vector<uint8_t>::iterator LinSpikeEvent2::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);
    it = LinBusEvent::fromData(it);

    width =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);
    internal =
            (static_cast<BYTE>(*it++) <<  0);
    reservedLinSpikeEvent1 =
            (static_cast<BYTE>(*it++) <<  0);
    reservedLinSpikeEvent2 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);

    return it;
}

void LinSpikeEvent2::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);
    LinBusEvent::toData(data);

    data.push_back((width >>  0) & 0xff);
    data.push_back((width >>  8) & 0xff);
    data.push_back((width >> 16) & 0xff);
    data.push_back((width >> 24) & 0xff);
    data.push_back((internal >>  0) & 0xff);
    data.push_back((reservedLinSpikeEvent1 >>  0) & 0xff);
    data.push_back((reservedLinSpikeEvent2 >>  0) & 0xff);
    data.push_back((reservedLinSpikeEvent2 >>  8) & 0xff);
}

DWORD LinSpikeEvent2::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinBusEvent::calculateObjectSize() +
        sizeof(width) +
        sizeof(internal) +
        sizeof(reservedLinSpikeEvent1) +
        sizeof(reservedLinSpikeEvent2);
}

}
}
