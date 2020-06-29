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

#include <Vector/BLF/LinSyncError.h>

#include <algorithm>

namespace Vector {
namespace BLF {

LinSyncError::LinSyncError() :
    ObjectHeader(ObjectType::LIN_SYN_ERROR) {
}

std::vector<uint8_t>::iterator LinSyncError::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedLinSyncError1 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    std::generate(timeDiff.begin(), timeDiff.end(), [&it]() {
        return
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    });
    reservedLinSyncError2 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);

    return it;
}

void LinSyncError::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((reservedLinSyncError1 >>  0) & 0xff);
    data.push_back((reservedLinSyncError1 >>  8) & 0xff);
    std::for_each(timeDiff.begin(), timeDiff.end(), [&data](const WORD & d) {
        data.push_back((d >>  0) & 0xff);
        data.push_back((d >>  8) & 0xff);
    });
    data.push_back((reservedLinSyncError2 >>  0) & 0xff);
    data.push_back((reservedLinSyncError2 >>  8) & 0xff);
    data.push_back((reservedLinSyncError2 >> 16) & 0xff);
    data.push_back((reservedLinSyncError2 >> 24) & 0xff);
}

DWORD LinSyncError::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reservedLinSyncError1) +
        static_cast<DWORD>(timeDiff.size() * sizeof(WORD)) +
        sizeof(reservedLinSyncError2);
}

}
}
