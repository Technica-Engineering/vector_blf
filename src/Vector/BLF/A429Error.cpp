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

#include <Vector/BLF/A429Error.h>

namespace Vector {
namespace BLF {

A429Error::A429Error() :
    ObjectHeader(ObjectType::A429_ERROR) {
}

std::vector<uint8_t>::iterator A429Error::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    errorType =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    sourceIdentifier =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);
    errReason =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);
    std::copy(it, it + errorText.size(), std::begin(errorText));
    it += errorText.size();
    std::copy(it, it + errorAttributes.size(), std::begin(errorAttributes));
    it += errorAttributes.size();
    reservedA429Error =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);

    return it;
}

void A429Error::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((errorType >>  0) & 0xff);
    data.push_back((errorType >>  8) & 0xff);
    data.push_back((sourceIdentifier >>  0) & 0xff);
    data.push_back((sourceIdentifier >>  8) & 0xff);
    data.push_back((sourceIdentifier >> 16) & 0xff);
    data.push_back((sourceIdentifier >> 24) & 0xff);
    data.push_back((errReason >>  0) & 0xff);
    data.push_back((errReason >>  8) & 0xff);
    data.push_back((errReason >> 16) & 0xff);
    data.push_back((errReason >> 24) & 0xff);
    data.insert(std::end(data), std::begin(errorText), std::end(errorText));
    data.insert(std::end(data), std::begin(errorAttributes), std::end(errorAttributes));
    data.push_back((reservedA429Error >>  0) & 0xff);
    data.push_back((reservedA429Error >>  8) & 0xff);
    data.push_back((reservedA429Error >> 16) & 0xff);
    data.push_back((reservedA429Error >> 24) & 0xff);
}

DWORD A429Error::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(errorType) +
        sizeof(sourceIdentifier) +
        sizeof(errReason) +
        static_cast<DWORD>(errorText.size()) +
        static_cast<DWORD>(errorAttributes.size()) +
        sizeof(reservedA429Error);
}

}
}
