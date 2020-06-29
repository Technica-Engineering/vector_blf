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

#include <cstring>

#include <Vector/BLF/EventComment.h>

namespace Vector {
namespace BLF {

EventComment::EventComment() :
    ObjectHeader(ObjectType::EVENT_COMMENT) {
}

std::vector<uint8_t>::iterator EventComment::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    commentedEventType =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    textLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedEventComment =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    text.resize(textLength);
    std::copy(it, it + text.size(), std::begin(text));
    it += text.size();

    return it;
}

void EventComment::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    textLength = static_cast<DWORD>(text.size());

    ObjectHeader::toData(data);

    data.push_back((commentedEventType >>  0) & 0xff);
    data.push_back((commentedEventType >>  8) & 0xff);
    data.push_back((commentedEventType >> 16) & 0xff);
    data.push_back((commentedEventType >> 24) & 0xff);
    data.push_back((textLength >>  0) & 0xff);
    data.push_back((textLength >>  8) & 0xff);
    data.push_back((textLength >> 16) & 0xff);
    data.push_back((textLength >> 24) & 0xff);
    data.push_back((reservedEventComment >>  0) & 0xff);
    data.push_back((reservedEventComment >>  8) & 0xff);
    data.push_back((reservedEventComment >> 16) & 0xff);
    data.push_back((reservedEventComment >> 24) & 0xff);
    data.push_back((reservedEventComment >> 32) & 0xff);
    data.push_back((reservedEventComment >> 40) & 0xff);
    data.push_back((reservedEventComment >> 48) & 0xff);
    data.push_back((reservedEventComment >> 56) & 0xff);
    data.insert(std::end(data), std::begin(text), std::end(text));
}

DWORD EventComment::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(commentedEventType) +
        sizeof(textLength) +
        sizeof(reservedEventComment) +
        textLength;
}

}
}
