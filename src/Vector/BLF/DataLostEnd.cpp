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

#include <Vector/BLF/DataLostEnd.h>

namespace Vector {
namespace BLF {

DataLostEnd::DataLostEnd() :
    ObjectHeader(ObjectType::DATA_LOST_END) {
}

std::vector<uint8_t>::iterator DataLostEnd::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    queueIdentifier =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    firstObjectLostTimeStamp =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    numberOfLostEvents =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);

    return it;
}

void DataLostEnd::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((queueIdentifier >>  0) & 0xff);
    data.push_back((queueIdentifier >>  8) & 0xff);
    data.push_back((queueIdentifier >> 16) & 0xff);
    data.push_back((queueIdentifier >> 24) & 0xff);
    data.push_back((firstObjectLostTimeStamp >>  0) & 0xff);
    data.push_back((firstObjectLostTimeStamp >>  8) & 0xff);
    data.push_back((firstObjectLostTimeStamp >> 16) & 0xff);
    data.push_back((firstObjectLostTimeStamp >> 24) & 0xff);
    data.push_back((firstObjectLostTimeStamp >> 32) & 0xff);
    data.push_back((firstObjectLostTimeStamp >> 40) & 0xff);
    data.push_back((firstObjectLostTimeStamp >> 48) & 0xff);
    data.push_back((firstObjectLostTimeStamp >> 56) & 0xff);
    data.push_back((numberOfLostEvents >>  0) & 0xff);
    data.push_back((numberOfLostEvents >>  8) & 0xff);
    data.push_back((numberOfLostEvents >> 16) & 0xff);
    data.push_back((numberOfLostEvents >> 24) & 0xff);
}

DWORD DataLostEnd::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(queueIdentifier) +
        sizeof(firstObjectLostTimeStamp) +
        sizeof(numberOfLostEvents);
}

}
}
