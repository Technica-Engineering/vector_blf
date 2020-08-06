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

#include <Vector/BLF/AfdxErrorEvent.h>

namespace Vector {
namespace BLF {

AfdxErrorEvent::AfdxErrorEvent() :
    ObjectHeader(ObjectType::AFDX_ERROR_EVENT) {
}

std::vector<uint8_t>::iterator AfdxErrorEvent::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    errorLevel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    sourceIdentifier =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    std::copy(it, it + errorText.size(), std::begin(errorText));
    it += errorText.size();
    std::copy(it, it + errorAttributes.size(), std::begin(errorAttributes));
    it += errorAttributes.size();

    return it;
}

void AfdxErrorEvent::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((errorLevel >>  0) & 0xff);
    data.push_back((errorLevel >>  8) & 0xff);
    data.push_back((sourceIdentifier >>  0) & 0xff);
    data.push_back((sourceIdentifier >>  8) & 0xff);
    data.push_back((sourceIdentifier >> 16) & 0xff);
    data.push_back((sourceIdentifier >> 24) & 0xff);
    data.insert(std::end(data), std::begin(errorText), std::end(errorText));
    data.insert(std::end(data), std::begin(errorAttributes), std::end(errorAttributes));
}

DWORD AfdxErrorEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(errorLevel) +
        sizeof(sourceIdentifier) +
        errorText.size() +
        errorAttributes.size();
}

}
}
