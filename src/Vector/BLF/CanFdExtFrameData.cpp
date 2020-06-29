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

#include <Vector/BLF/CanFdExtFrameData.h>

namespace Vector {
namespace BLF {

std::vector<uint8_t>::iterator CanFdExtFrameData::fromData(std::vector<uint8_t>::iterator it) {
    btrExtArb =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    btrExtData =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    // @note reservedCanFdExtFrameData is read by CanFdMessage64/CanFdErrorFrame64 due to objectSize known there.

    return it;
}

void CanFdExtFrameData::toData(std::vector<uint8_t> & data) {
    data.push_back((btrExtArb >>  0) & 0xff);
    data.push_back((btrExtArb >>  8) & 0xff);
    data.push_back((btrExtArb >> 16) & 0xff);
    data.push_back((btrExtArb >> 24) & 0xff);
    data.push_back((btrExtData >>  0) & 0xff);
    data.push_back((btrExtData >>  8) & 0xff);
    data.push_back((btrExtData >> 16) & 0xff);
    data.push_back((btrExtData >> 24) & 0xff);
    data.insert(std::end(data), std::begin(reservedCanFdExtFrameData), std::end(reservedCanFdExtFrameData));
}

DWORD CanFdExtFrameData::calculateObjectSize() const {
    return
        sizeof(btrExtArb) +
        sizeof(btrExtData) +
        static_cast<DWORD>(reservedCanFdExtFrameData.size());
}

}
}
