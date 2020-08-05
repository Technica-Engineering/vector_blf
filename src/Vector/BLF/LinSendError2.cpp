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

#include <Vector/BLF/LinSendError2.h>

namespace Vector {
namespace BLF {

LinSendError2::LinSendError2() :
    ObjectHeader(ObjectType::LIN_SND_ERROR2, 1) {
}

std::vector<uint8_t>::iterator LinSendError2::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);
    it = LinMessageDescriptor::fromData(it);

    eoh =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    isEtf =
            (static_cast<BYTE>(*it++) <<  0);
    fsmId =
            (static_cast<BYTE>(*it++) <<  0);
    fsmState =
            (static_cast<BYTE>(*it++) <<  0);
    reservedLinSendError1 =
            (static_cast<BYTE>(*it++) <<  0);
    reservedLinSendError2 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    uint64_t * ptr = reinterpret_cast<uint64_t *>(&exactHeaderBaudrate);
    *ptr =
            (static_cast<uint64_t>(*it++) <<  0) |
            (static_cast<uint64_t>(*it++) <<  8) |
            (static_cast<uint64_t>(*it++) << 16) |
            (static_cast<uint64_t>(*it++) << 24) |
            (static_cast<uint64_t>(*it++) << 32) |
            (static_cast<uint64_t>(*it++) << 40) |
            (static_cast<uint64_t>(*it++) << 48) |
            (static_cast<uint64_t>(*it++) << 56);
    earlyStopbitOffset =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedLinSendError3 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);

    return it;
}

void LinSendError2::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);
    LinMessageDescriptor::toData(data);

    data.push_back((eoh >>  0) & 0xff);
    data.push_back((eoh >>  8) & 0xff);
    data.push_back((eoh >> 16) & 0xff);
    data.push_back((eoh >> 24) & 0xff);
    data.push_back((eoh >> 32) & 0xff);
    data.push_back((eoh >> 40) & 0xff);
    data.push_back((eoh >> 48) & 0xff);
    data.push_back((eoh >> 56) & 0xff);
    data.push_back((isEtf >>  0) & 0xff);
    data.push_back((fsmId >>  0) & 0xff);
    data.push_back((fsmState >>  0) & 0xff);
    data.push_back((reservedLinSendError1 >>  0) & 0xff);
    data.push_back((reservedLinSendError2 >>  0) & 0xff);
    data.push_back((reservedLinSendError2 >>  8) & 0xff);
    data.push_back((reservedLinSendError2 >> 16) & 0xff);
    data.push_back((reservedLinSendError2 >> 24) & 0xff);
    uint64_t * ptr = reinterpret_cast<uint64_t *>(&exactHeaderBaudrate);
    data.push_back((*ptr >>  0) & 0xff);
    data.push_back((*ptr >>  8) & 0xff);
    data.push_back((*ptr >> 16) & 0xff);
    data.push_back((*ptr >> 24) & 0xff);
    data.push_back((*ptr >> 32) & 0xff);
    data.push_back((*ptr >> 40) & 0xff);
    data.push_back((*ptr >> 48) & 0xff);
    data.push_back((*ptr >> 56) & 0xff);
    data.push_back((earlyStopbitOffset >>  0) & 0xff);
    data.push_back((earlyStopbitOffset >>  8) & 0xff);
    data.push_back((earlyStopbitOffset >> 16) & 0xff);
    data.push_back((earlyStopbitOffset >> 24) & 0xff);
    data.push_back((reservedLinSendError3 >>  0) & 0xff);
    data.push_back((reservedLinSendError3 >>  8) & 0xff);
    data.push_back((reservedLinSendError3 >> 16) & 0xff);
    data.push_back((reservedLinSendError3 >> 24) & 0xff);
}

DWORD LinSendError2::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinMessageDescriptor::calculateObjectSize() +
        sizeof(eoh) +
        sizeof(isEtf) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(reservedLinSendError1) +
        sizeof(reservedLinSendError2) +
        sizeof(exactHeaderBaudrate) +
        sizeof(earlyStopbitOffset) +
        sizeof(reservedLinSendError3);
}

}
}
