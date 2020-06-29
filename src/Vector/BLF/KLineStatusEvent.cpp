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

#include <Vector/BLF/KLineStatusEvent.h>

#include <algorithm>

namespace Vector {
namespace BLF {

KLineStatusEvent::KLineStatusEvent() :
    ObjectHeader(ObjectType::KLINE_STATUSEVENT) {
}

std::vector<uint8_t>::iterator KLineStatusEvent::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    type =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    dataLen =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    port =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedKLineStatusEvent =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    std::generate(this->data.begin(), this->data.end(), [&it]() {
        return
            (static_cast<UINT64>(*it++) <<  0) |
            (static_cast<UINT64>(*it++) <<  8) |
            (static_cast<UINT64>(*it++) << 16) |
            (static_cast<UINT64>(*it++) << 24) |
            (static_cast<UINT64>(*it++) << 32) |
            (static_cast<UINT64>(*it++) << 40) |
            (static_cast<UINT64>(*it++) << 48) |
            (static_cast<UINT64>(*it++) << 56);
    });

    return it;
}

void KLineStatusEvent::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((type >>  0) & 0xff);
    data.push_back((type >>  8) & 0xff);
    data.push_back((dataLen >>  0) & 0xff);
    data.push_back((dataLen >>  8) & 0xff);
    data.push_back((port >>  0) & 0xff);
    data.push_back((port >>  8) & 0xff);
    data.push_back((port >> 16) & 0xff);
    data.push_back((port >> 24) & 0xff);
    data.push_back((reservedKLineStatusEvent >>  0) & 0xff);
    data.push_back((reservedKLineStatusEvent >>  8) & 0xff);
    data.push_back((reservedKLineStatusEvent >> 16) & 0xff);
    data.push_back((reservedKLineStatusEvent >> 24) & 0xff);
    data.push_back((reservedKLineStatusEvent >> 32) & 0xff);
    data.push_back((reservedKLineStatusEvent >> 40) & 0xff);
    data.push_back((reservedKLineStatusEvent >> 48) & 0xff);
    data.push_back((reservedKLineStatusEvent >> 56) & 0xff);
    std::for_each(this->data.begin(), this->data.end(), [&data](const UINT64 & d) {
        data.push_back((d >>  0) & 0xff);
        data.push_back((d >>  8) & 0xff);
        data.push_back((d >> 16) & 0xff);
        data.push_back((d >> 24) & 0xff);
        data.push_back((d >> 32) & 0xff);
        data.push_back((d >> 40) & 0xff);
        data.push_back((d >> 48) & 0xff);
        data.push_back((d >> 56) & 0xff);
    });
}

DWORD KLineStatusEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(type) +
        sizeof(dataLen) +
        sizeof(port) +
        sizeof(reservedKLineStatusEvent) +
        static_cast<DWORD>(data.size() * sizeof(UINT64));
}

}
}
