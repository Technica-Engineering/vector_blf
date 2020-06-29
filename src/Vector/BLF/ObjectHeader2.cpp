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

#include <Vector/BLF/ObjectHeader2.h>

namespace Vector {
namespace BLF {

ObjectHeader2::ObjectHeader2(const ObjectType objectType) :
    ObjectHeaderBase(2, objectType) {
}

std::vector<uint8_t>::iterator ObjectHeader2::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeaderBase::fromData(it);

    objectFlags =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    timeStampStatus =
            (static_cast<BYTE>(*it++) <<  0);
    reservedObjectHeader =
            (static_cast<BYTE>(*it++) <<  0);
    objectVersion =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    objectTimeStamp =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    originalTimeStamp =
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

void ObjectHeader2::toData(std::vector<uint8_t> & data) {
    ObjectHeaderBase::toData(data);

    data.push_back((objectFlags >>  0) & 0xff);
    data.push_back((objectFlags >>  8) & 0xff);
    data.push_back((objectFlags >> 16) & 0xff);
    data.push_back((objectFlags >> 24) & 0xff);
    data.push_back((timeStampStatus >>  0) & 0xff);
    data.push_back((reservedObjectHeader >>  0) & 0xff);
    data.push_back((objectVersion >>  0) & 0xff);
    data.push_back((objectVersion >>  8) & 0xff);
    data.push_back((objectTimeStamp >>  0) & 0xff);
    data.push_back((objectTimeStamp >>  8) & 0xff);
    data.push_back((objectTimeStamp >> 16) & 0xff);
    data.push_back((objectTimeStamp >> 24) & 0xff);
    data.push_back((objectTimeStamp >> 32) & 0xff);
    data.push_back((objectTimeStamp >> 40) & 0xff);
    data.push_back((objectTimeStamp >> 48) & 0xff);
    data.push_back((objectTimeStamp >> 56) & 0xff);
    data.push_back((originalTimeStamp >>  0) & 0xff);
    data.push_back((originalTimeStamp >>  8) & 0xff);
    data.push_back((originalTimeStamp >> 16) & 0xff);
    data.push_back((originalTimeStamp >> 24) & 0xff);
    data.push_back((originalTimeStamp >> 32) & 0xff);
    data.push_back((originalTimeStamp >> 40) & 0xff);
    data.push_back((originalTimeStamp >> 48) & 0xff);
    data.push_back((originalTimeStamp >> 56) & 0xff);
}

WORD ObjectHeader2::calculateHeaderSize() const {
    return
        ObjectHeaderBase::calculateHeaderSize() +
        sizeof(objectFlags) +
        sizeof(timeStampStatus) +
        sizeof(reservedObjectHeader) +
        sizeof(objectVersion) +
        sizeof(objectTimeStamp) +
        sizeof(originalTimeStamp);
}

DWORD ObjectHeader2::calculateObjectSize() const {
    return calculateHeaderSize();
}

}
}
