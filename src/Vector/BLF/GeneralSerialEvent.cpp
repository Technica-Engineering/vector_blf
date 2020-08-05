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

#include <Vector/BLF/GeneralSerialEvent.h>

#include <algorithm>

namespace Vector {
namespace BLF {

std::vector<uint8_t>::iterator GeneralSerialEvent::fromData(std::vector<uint8_t>::iterator it) {
    dataLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    timeStampsLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedGeneralSerialEvent =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    this->data.resize(dataLength);
    std::copy(it, it + this->data.size(), std::begin(this->data));
    it += dataLength;
    timeStamps.resize(timeStampsLength / sizeof(LONGLONG));
    std::generate(timeStamps.begin(), timeStamps.end(), [&it]() {
        return
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    });

    return it;
}

void GeneralSerialEvent::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    dataLength = static_cast<DWORD>(this->data.size());
    timeStampsLength = static_cast<DWORD>(timeStamps.size() * sizeof(LONGLONG));

    data.push_back((dataLength >>  0) & 0xff);
    data.push_back((dataLength >>  8) & 0xff);
    data.push_back((dataLength >> 16) & 0xff);
    data.push_back((dataLength >> 24) & 0xff);
    data.push_back((timeStampsLength >>  0) & 0xff);
    data.push_back((timeStampsLength >>  8) & 0xff);
    data.push_back((timeStampsLength >> 16) & 0xff);
    data.push_back((timeStampsLength >> 24) & 0xff);
    data.push_back((reservedGeneralSerialEvent >>  0) & 0xff);
    data.push_back((reservedGeneralSerialEvent >>  8) & 0xff);
    data.push_back((reservedGeneralSerialEvent >> 16) & 0xff);
    data.push_back((reservedGeneralSerialEvent >> 24) & 0xff);
    data.push_back((reservedGeneralSerialEvent >> 32) & 0xff);
    data.push_back((reservedGeneralSerialEvent >> 40) & 0xff);
    data.push_back((reservedGeneralSerialEvent >> 48) & 0xff);
    data.push_back((reservedGeneralSerialEvent >> 56) & 0xff);
    data.insert(std::end(data), std::begin(this->data), std::end(this->data));
    std::for_each(timeStamps.begin(), timeStamps.end(), [&data](const ULONGLONG & d) {
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

DWORD GeneralSerialEvent::calculateObjectSize() const {
    return
        sizeof(dataLength) +
        sizeof(timeStampsLength) +
        sizeof(reservedGeneralSerialEvent) +
        dataLength +
        timeStampsLength;
}

}
}
