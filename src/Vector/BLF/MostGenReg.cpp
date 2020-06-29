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

#include <Vector/BLF/MostGenReg.h>

namespace Vector {
namespace BLF {

MostGenReg::MostGenReg() :
    ObjectHeader2(ObjectType::MOST_GENREG) {
}

std::vector<uint8_t>::iterator MostGenReg::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader2::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    subType =
            (static_cast<BYTE>(*it++) <<  0);
    reservedMostGenReg1 =
            (static_cast<BYTE>(*it++) <<  0);
    handle =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    regId =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedMostGenReg2 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedMostGenReg3 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    regValue =
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

void MostGenReg::toData(std::vector<uint8_t> & data) {
    ObjectHeader2::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((subType >>  0) & 0xff);
    data.push_back((reservedMostGenReg1 >>  0) & 0xff);
    data.push_back((handle >>  0) & 0xff);
    data.push_back((handle >>  8) & 0xff);
    data.push_back((handle >> 16) & 0xff);
    data.push_back((handle >> 24) & 0xff);
    data.push_back((regId >>  0) & 0xff);
    data.push_back((regId >>  8) & 0xff);
    data.push_back((reservedMostGenReg2 >>  0) & 0xff);
    data.push_back((reservedMostGenReg2 >>  8) & 0xff);
    data.push_back((reservedMostGenReg3 >>  0) & 0xff);
    data.push_back((reservedMostGenReg3 >>  8) & 0xff);
    data.push_back((reservedMostGenReg3 >> 16) & 0xff);
    data.push_back((reservedMostGenReg3 >> 24) & 0xff);
    data.push_back((regValue >>  0) & 0xff);
    data.push_back((regValue >>  8) & 0xff);
    data.push_back((regValue >> 16) & 0xff);
    data.push_back((regValue >> 24) & 0xff);
    data.push_back((regValue >> 32) & 0xff);
    data.push_back((regValue >> 40) & 0xff);
    data.push_back((regValue >> 48) & 0xff);
    data.push_back((regValue >> 56) & 0xff);
}

DWORD MostGenReg::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(subType) +
        sizeof(reservedMostGenReg1) +
        sizeof(handle) +
        sizeof(regId) +
        sizeof(reservedMostGenReg2) +
        sizeof(reservedMostGenReg3) +
        sizeof(regValue);
}

}
}
