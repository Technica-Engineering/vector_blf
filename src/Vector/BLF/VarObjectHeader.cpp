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

#include <Vector/BLF/VarObjectHeader.h>

namespace Vector {
namespace BLF {

VarObjectHeader::VarObjectHeader(const ObjectType objectType) :
    ObjectHeaderBase(1, objectType) {
}

std::vector<uint8_t>::iterator VarObjectHeader::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeaderBase::fromData(it);

    objectFlags =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    objectStaticSize =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
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

    return it;
}

void VarObjectHeader::toData(std::vector<uint8_t> & data) {
    ObjectHeaderBase::toData(data);

    data.push_back((objectFlags >>  0) & 0xff);
    data.push_back((objectFlags >>  8) & 0xff);
    data.push_back((objectFlags >> 16) & 0xff);
    data.push_back((objectFlags >> 24) & 0xff);
    data.push_back((objectStaticSize >>  0) & 0xff);
    data.push_back((objectStaticSize >>  8) & 0xff);
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
}

WORD VarObjectHeader::calculateHeaderSize() const {
    return
        ObjectHeaderBase::calculateHeaderSize() +
        sizeof(objectFlags) +
        sizeof(objectStaticSize) +
        sizeof(objectVersion) +
        sizeof(objectTimeStamp);
}

DWORD VarObjectHeader::calculateObjectSize() const {
    return calculateHeaderSize();
}

}
}
