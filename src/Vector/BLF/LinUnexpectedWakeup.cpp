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

#include <Vector/BLF/LinUnexpectedWakeup.h>

namespace Vector {
namespace BLF {

LinUnexpectedWakeup::LinUnexpectedWakeup() :
    ObjectHeader(ObjectType::LIN_UNEXPECTED_WAKEUP) {
}

std::vector<uint8_t>::iterator LinUnexpectedWakeup::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);
    it = LinBusEvent::fromData(it);

    width =
        (static_cast<ULONGLONG>(*it++) <<  0) |
        (static_cast<ULONGLONG>(*it++) <<  8) |
        (static_cast<ULONGLONG>(*it++) << 16) |
        (static_cast<ULONGLONG>(*it++) << 24) |
        (static_cast<ULONGLONG>(*it++) << 32) |
        (static_cast<ULONGLONG>(*it++) << 40) |
        (static_cast<ULONGLONG>(*it++) << 48) |
        (static_cast<ULONGLONG>(*it++) << 56);
    signal =
        (static_cast<BYTE>(*it++) <<  0);
    reservedLinUnexpectedWakeup1 =
        (static_cast<BYTE>(*it++) <<  0);
    reservedLinUnexpectedWakeup2 =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedLinUnexpectedWakeup3 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);

    return it;
}

void LinUnexpectedWakeup::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);
    LinBusEvent::toData(data);

    data.push_back((width >>  0) & 0xff);
    data.push_back((width >>  8) & 0xff);
    data.push_back((width >> 16) & 0xff);
    data.push_back((width >> 24) & 0xff);
    data.push_back((width >> 32) & 0xff);
    data.push_back((width >> 40) & 0xff);
    data.push_back((width >> 48) & 0xff);
    data.push_back((width >> 56) & 0xff);
    data.push_back((signal >>  0) & 0xff);
    data.push_back((reservedLinUnexpectedWakeup1 >>  0) & 0xff);
    data.push_back((reservedLinUnexpectedWakeup2 >>  0) & 0xff);
    data.push_back((reservedLinUnexpectedWakeup2 >>  8) & 0xff);
    data.push_back((reservedLinUnexpectedWakeup3 >>  0) & 0xff);
    data.push_back((reservedLinUnexpectedWakeup3 >>  8) & 0xff);
    data.push_back((reservedLinUnexpectedWakeup3 >> 16) & 0xff);
    data.push_back((reservedLinUnexpectedWakeup3 >> 24) & 0xff);
}

DWORD LinUnexpectedWakeup::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinBusEvent::calculateObjectSize() +
        sizeof(width) +
        sizeof(signal) +
        sizeof(reservedLinUnexpectedWakeup1) +
        sizeof(reservedLinUnexpectedWakeup2) +
        sizeof(reservedLinUnexpectedWakeup3);
}

}
}
