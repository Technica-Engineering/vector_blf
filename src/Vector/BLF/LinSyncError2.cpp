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

#include <Vector/BLF/LinSyncError2.h>

#include <algorithm>

namespace Vector {
namespace BLF {

LinSyncError2::LinSyncError2() :
    ObjectHeader(ObjectType::LIN_SYN_ERROR2) {
}

std::vector<uint8_t>::iterator LinSyncError2::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);
    it = LinSynchFieldEvent::fromData(it);

    std::generate(timeDiff.begin(), timeDiff.end(), [&it]() {
        return
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    });

    return it;
}

void LinSyncError2::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);
    LinSynchFieldEvent::toData(data);

    std::for_each(timeDiff.begin(), timeDiff.end(), [&data](const WORD & d) {
        data.push_back((d >>  0) & 0xff);
        data.push_back((d >>  8) & 0xff);
    });
}

DWORD LinSyncError2::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinSynchFieldEvent::calculateObjectSize() +
        static_cast<DWORD>(timeDiff.size() * sizeof(WORD));
}

}
}
