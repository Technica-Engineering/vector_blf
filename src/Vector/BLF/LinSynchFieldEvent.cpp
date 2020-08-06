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

#include <Vector/BLF/LinSynchFieldEvent.h>

namespace Vector {
namespace BLF {

std::vector<uint8_t>::iterator LinSynchFieldEvent::fromData(std::vector<uint8_t>::iterator it) {
    it = LinBusEvent::fromData(it);

    synchBreakLength =
        (static_cast<ULONGLONG>(*it++) <<  0) |
        (static_cast<ULONGLONG>(*it++) <<  8) |
        (static_cast<ULONGLONG>(*it++) << 16) |
        (static_cast<ULONGLONG>(*it++) << 24) |
        (static_cast<ULONGLONG>(*it++) << 32) |
        (static_cast<ULONGLONG>(*it++) << 40) |
        (static_cast<ULONGLONG>(*it++) << 48) |
        (static_cast<ULONGLONG>(*it++) << 56);
    synchDelLength =
        (static_cast<ULONGLONG>(*it++) <<  0) |
        (static_cast<ULONGLONG>(*it++) <<  8) |
        (static_cast<ULONGLONG>(*it++) << 16) |
        (static_cast<ULONGLONG>(*it++) << 24) |
        (static_cast<ULONGLONG>(*it++) << 32) |
        (static_cast<ULONGLONG>(*it++) << 40) |
        (static_cast<ULONGLONG>(*it++) << 48) |
        (static_cast<ULONGLONG>(*it++) << 56);

    return it;
}

void LinSynchFieldEvent::toData(std::vector<uint8_t> & data) {
    LinBusEvent::toData(data);

    data.push_back((synchBreakLength >>  0) & 0xff);
    data.push_back((synchBreakLength >>  8) & 0xff);
    data.push_back((synchBreakLength >> 16) & 0xff);
    data.push_back((synchBreakLength >> 24) & 0xff);
    data.push_back((synchBreakLength >> 32) & 0xff);
    data.push_back((synchBreakLength >> 40) & 0xff);
    data.push_back((synchBreakLength >> 48) & 0xff);
    data.push_back((synchBreakLength >> 56) & 0xff);
    data.push_back((synchDelLength >>  0) & 0xff);
    data.push_back((synchDelLength >>  8) & 0xff);
    data.push_back((synchDelLength >> 16) & 0xff);
    data.push_back((synchDelLength >> 24) & 0xff);
    data.push_back((synchDelLength >> 32) & 0xff);
    data.push_back((synchDelLength >> 40) & 0xff);
    data.push_back((synchDelLength >> 48) & 0xff);
    data.push_back((synchDelLength >> 56) & 0xff);
}

DWORD LinSynchFieldEvent::calculateObjectSize() const {
    return
        LinBusEvent::calculateObjectSize() +
        sizeof(synchBreakLength) +
        sizeof(synchDelLength);
}

}
}
