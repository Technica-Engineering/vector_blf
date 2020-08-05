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

#include <Vector/BLF/SingleByteSerialEvent.h>

namespace Vector {
namespace BLF {

std::vector<uint8_t>::iterator SingleByteSerialEvent::fromData(std::vector<uint8_t>::iterator it) {
    byte =
            (static_cast<BYTE>(*it++) <<  0);
    std::copy(it, it + reservedSingleByteSerialEvent.size(), std::begin(reservedSingleByteSerialEvent));
    it += reservedSingleByteSerialEvent.size();

    return it;
}

void SingleByteSerialEvent::toData(std::vector<uint8_t> & data) {
    data.push_back((byte >>  0) & 0xff);
    data.insert(std::end(data), std::begin(reservedSingleByteSerialEvent), std::end(reservedSingleByteSerialEvent));
}

DWORD SingleByteSerialEvent::calculateObjectSize() const {
    return
        sizeof(byte) +
        static_cast<DWORD>(reservedSingleByteSerialEvent.size());
}

}
}
