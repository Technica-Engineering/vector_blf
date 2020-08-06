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

#include <Vector/BLF/CanDriverErrorExt.h>

#include <algorithm>

namespace Vector {
namespace BLF {

CanDriverErrorExt::CanDriverErrorExt() :
    ObjectHeader(ObjectType::CAN_DRIVER_ERROR_EXT) {
}

std::vector<uint8_t>::iterator CanDriverErrorExt::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    txErrors =
        (static_cast<BYTE>(*it++) <<  0);
    rxErrors =
        (static_cast<BYTE>(*it++) <<  0);
    errorCode =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    flags =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    state =
        (static_cast<BYTE>(*it++) <<  0);
    reservedCanDriverErrorExt1 =
        (static_cast<BYTE>(*it++) <<  0);
    reservedCanDriverErrorExt2 =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    std::generate(reservedCanDriverErrorExt3.begin(), reservedCanDriverErrorExt3.end(), [&it]() {
        return
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    });

    return it;
}

void CanDriverErrorExt::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((txErrors >>  0) & 0xff);
    data.push_back((rxErrors >>  0) & 0xff);
    data.push_back((errorCode >>  0) & 0xff);
    data.push_back((errorCode >>  8) & 0xff);
    data.push_back((errorCode >> 16) & 0xff);
    data.push_back((errorCode >> 24) & 0xff);
    data.push_back((flags >>  0) & 0xff);
    data.push_back((flags >>  8) & 0xff);
    data.push_back((flags >> 16) & 0xff);
    data.push_back((flags >> 24) & 0xff);
    data.push_back((state >>  0) & 0xff);
    data.push_back((reservedCanDriverErrorExt1 >>  0) & 0xff);
    data.push_back((reservedCanDriverErrorExt2 >>  0) & 0xff);
    data.push_back((reservedCanDriverErrorExt2 >>  8) & 0xff);
    std::for_each(reservedCanDriverErrorExt3.begin(), reservedCanDriverErrorExt3.end(), [&data](const DWORD & d) {
        data.push_back((d >>  0) & 0xff);
        data.push_back((d >>  8) & 0xff);
        data.push_back((d >> 16) & 0xff);
        data.push_back((d >> 24) & 0xff);
    });
}

DWORD CanDriverErrorExt::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(txErrors) +
        sizeof(rxErrors) +
        sizeof(errorCode) +
        sizeof(flags) +
        sizeof(state) +
        sizeof(reservedCanDriverErrorExt1) +
        sizeof(reservedCanDriverErrorExt2) +
        static_cast<DWORD>(reservedCanDriverErrorExt3.size() * sizeof(DWORD));
}

}
}
