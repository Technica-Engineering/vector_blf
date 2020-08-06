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

#include <Vector/BLF/LinBusEvent.h>

namespace Vector {
namespace BLF {

std::vector<uint8_t>::iterator LinBusEvent::fromData(std::vector<uint8_t>::iterator it) {
    sof =
        (static_cast<ULONGLONG>(*it++) <<  0) |
        (static_cast<ULONGLONG>(*it++) <<  8) |
        (static_cast<ULONGLONG>(*it++) << 16) |
        (static_cast<ULONGLONG>(*it++) << 24) |
        (static_cast<ULONGLONG>(*it++) << 32) |
        (static_cast<ULONGLONG>(*it++) << 40) |
        (static_cast<ULONGLONG>(*it++) << 48) |
        (static_cast<ULONGLONG>(*it++) << 56);
    eventBaudrate =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedLinBusEvent =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);

    return it;
}

void LinBusEvent::toData(std::vector<uint8_t> & data) {
    data.push_back((sof >>  0) & 0xff);
    data.push_back((sof >>  8) & 0xff);
    data.push_back((sof >> 16) & 0xff);
    data.push_back((sof >> 24) & 0xff);
    data.push_back((sof >> 32) & 0xff);
    data.push_back((sof >> 40) & 0xff);
    data.push_back((sof >> 48) & 0xff);
    data.push_back((sof >> 56) & 0xff);
    data.push_back((eventBaudrate >>  0) & 0xff);
    data.push_back((eventBaudrate >>  8) & 0xff);
    data.push_back((eventBaudrate >> 16) & 0xff);
    data.push_back((eventBaudrate >> 24) & 0xff);
    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((reservedLinBusEvent >>  0) & 0xff);
    data.push_back((reservedLinBusEvent >>  8) & 0xff);
}

DWORD LinBusEvent::calculateObjectSize() const {
    return
        sizeof(sof) +
        sizeof(eventBaudrate) +
        sizeof(channel) +
        sizeof(reservedLinBusEvent);
}

}
}
