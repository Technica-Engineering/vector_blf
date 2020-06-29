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

#include <Vector/BLF/MostReg.h>

namespace Vector {
namespace BLF {

MostReg::MostReg() :
    ObjectHeader2(ObjectType::MOST_REG) {
}

std::vector<uint8_t>::iterator MostReg::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader2::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    subType =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMostReg =
            (static_cast<BYTE>(*it++) <<  0);
    handle =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    offset =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    chip =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    regDataLen =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    std::copy(it, it + regData.size(), std::begin(regData));
    it += regData.size();

    return it;
}

void MostReg::toData(std::vector<uint8_t> & data) {
    ObjectHeader2::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((subType >>  0) & 0xff);
    data.push_back((reservedMostReg >>  0) & 0xff);
    data.push_back((handle >>  0) & 0xff);
    data.push_back((handle >>  8) & 0xff);
    data.push_back((handle >> 16) & 0xff);
    data.push_back((handle >> 24) & 0xff);
    data.push_back((offset >>  0) & 0xff);
    data.push_back((offset >>  8) & 0xff);
    data.push_back((offset >> 16) & 0xff);
    data.push_back((offset >> 24) & 0xff);
    data.push_back((chip >>  0) & 0xff);
    data.push_back((chip >>  8) & 0xff);
    data.push_back((regDataLen >>  0) & 0xff);
    data.push_back((regDataLen >>  8) & 0xff);
    data.insert(std::end(data), std::begin(regData), std::end(regData));
}

DWORD MostReg::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(subType) +
        sizeof(reservedMostReg) +
        sizeof(handle) +
        sizeof(offset) +
        sizeof(chip) +
        sizeof(regDataLen) +
        static_cast<DWORD>(regData.size());
}

}
}
