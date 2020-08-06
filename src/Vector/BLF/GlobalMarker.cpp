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

#include <Vector/BLF/GlobalMarker.h>

namespace Vector {
namespace BLF {

GlobalMarker::GlobalMarker() :
    ObjectHeader(ObjectType::GLOBAL_MARKER) {
}

std::vector<uint8_t>::iterator GlobalMarker::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    commentedEventType =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    foregroundColor =
        (static_cast<COLORREF>(*it++) <<  0) |
        (static_cast<COLORREF>(*it++) <<  8) |
        (static_cast<COLORREF>(*it++) << 16) |
        (static_cast<COLORREF>(*it++) << 24);
    backgroundColor =
        (static_cast<COLORREF>(*it++) <<  0) |
        (static_cast<COLORREF>(*it++) <<  8) |
        (static_cast<COLORREF>(*it++) << 16) |
        (static_cast<COLORREF>(*it++) << 24);
    isRelocatable =
        (static_cast<BYTE>(*it++) <<  0);
    reservedGlobalMarker1 =
        (static_cast<BYTE>(*it++) <<  0);
    reservedGlobalMarker2 =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    groupNameLength =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    markerNameLength =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    descriptionLength =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    reservedGlobalMarker3 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    reservedGlobalMarker4 =
        (static_cast<ULONGLONG>(*it++) <<  0) |
        (static_cast<ULONGLONG>(*it++) <<  8) |
        (static_cast<ULONGLONG>(*it++) << 16) |
        (static_cast<ULONGLONG>(*it++) << 24) |
        (static_cast<ULONGLONG>(*it++) << 32) |
        (static_cast<ULONGLONG>(*it++) << 40) |
        (static_cast<ULONGLONG>(*it++) << 48) |
        (static_cast<ULONGLONG>(*it++) << 56);
    groupName.assign(it, it + groupNameLength);
    it += groupNameLength;
    markerName.assign(it, it + markerNameLength);
    it += markerNameLength;
    description.assign(it, it + descriptionLength);
    it += descriptionLength;

    return it;
}

void GlobalMarker::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    groupNameLength = static_cast<DWORD>(groupName.size());
    markerNameLength = static_cast<DWORD>(markerName.size());
    descriptionLength = static_cast<DWORD>(description.size());

    ObjectHeader::toData(data);

    data.push_back((commentedEventType >>  0) & 0xff);
    data.push_back((commentedEventType >>  8) & 0xff);
    data.push_back((commentedEventType >> 16) & 0xff);
    data.push_back((commentedEventType >> 24) & 0xff);
    data.push_back((foregroundColor >>  0) & 0xff);
    data.push_back((foregroundColor >>  8) & 0xff);
    data.push_back((foregroundColor >> 16) & 0xff);
    data.push_back((foregroundColor >> 24) & 0xff);
    data.push_back((backgroundColor >>  0) & 0xff);
    data.push_back((backgroundColor >>  8) & 0xff);
    data.push_back((backgroundColor >> 16) & 0xff);
    data.push_back((backgroundColor >> 24) & 0xff);
    data.push_back((isRelocatable >>  0) & 0xff);
    data.push_back((reservedGlobalMarker1 >>  0) & 0xff);
    data.push_back((reservedGlobalMarker2 >>  0) & 0xff);
    data.push_back((reservedGlobalMarker2 >>  8) & 0xff);
    data.push_back((groupNameLength >>  0) & 0xff);
    data.push_back((groupNameLength >>  8) & 0xff);
    data.push_back((groupNameLength >> 16) & 0xff);
    data.push_back((groupNameLength >> 24) & 0xff);
    data.push_back((markerNameLength >>  0) & 0xff);
    data.push_back((markerNameLength >>  8) & 0xff);
    data.push_back((markerNameLength >> 16) & 0xff);
    data.push_back((markerNameLength >> 24) & 0xff);
    data.push_back((descriptionLength >>  0) & 0xff);
    data.push_back((descriptionLength >>  8) & 0xff);
    data.push_back((descriptionLength >> 16) & 0xff);
    data.push_back((descriptionLength >> 24) & 0xff);
    data.push_back((reservedGlobalMarker3 >>  0) & 0xff);
    data.push_back((reservedGlobalMarker3 >>  8) & 0xff);
    data.push_back((reservedGlobalMarker3 >> 16) & 0xff);
    data.push_back((reservedGlobalMarker3 >> 24) & 0xff);
    data.push_back((reservedGlobalMarker4 >>  0) & 0xff);
    data.push_back((reservedGlobalMarker4 >>  8) & 0xff);
    data.push_back((reservedGlobalMarker4 >> 16) & 0xff);
    data.push_back((reservedGlobalMarker4 >> 24) & 0xff);
    data.push_back((reservedGlobalMarker4 >> 32) & 0xff);
    data.push_back((reservedGlobalMarker4 >> 40) & 0xff);
    data.push_back((reservedGlobalMarker4 >> 48) & 0xff);
    data.push_back((reservedGlobalMarker4 >> 56) & 0xff);
    data.insert(std::end(data), std::begin(groupName), std::end(groupName));
    data.insert(std::end(data), std::begin(markerName), std::end(markerName));
    data.insert(std::end(data), std::begin(description), std::end(description));
}

DWORD GlobalMarker::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(commentedEventType) +
        sizeof(foregroundColor) +
        sizeof(backgroundColor) +
        sizeof(isRelocatable) +
        sizeof(reservedGlobalMarker1) +
        sizeof(reservedGlobalMarker2) +
        sizeof(groupNameLength) +
        sizeof(markerNameLength) +
        sizeof(descriptionLength) +
        sizeof(reservedGlobalMarker3) +
        sizeof(reservedGlobalMarker4) +
        groupNameLength +
        markerNameLength +
        descriptionLength;
}

}
}
