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

#include <Vector/BLF/EnvironmentVariable.h>

namespace Vector {
namespace BLF {

EnvironmentVariable::EnvironmentVariable(const ObjectType objectType) :
    ObjectHeader(objectType) {
    /* can be one of:
     *   - objectType = ObjectType::ENV_INTEGER;
     *   - objectType = ObjectType::ENV_DOUBLE;
     *   - objectType = ObjectType::ENV_STRING;
     *   - objectType = ObjectType::ENV_DATA;
     */
}

std::vector<uint8_t>::iterator EnvironmentVariable::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    nameLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    dataLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedEnvironmentVariable =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    name.resize(nameLength);
    std::copy(it, it + name.size(), std::begin(name));
    it += this->data.size();
    this->data.resize(dataLength);
    std::copy(it, it + this->data.size(), std::begin(this->data));
    it += this->data.size();

    return it;
}

void EnvironmentVariable::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    nameLength = static_cast<DWORD>(name.size());
    dataLength = static_cast<DWORD>(data.size());

    ObjectHeader::toData(data);

    data.push_back((nameLength >>  0) & 0xff);
    data.push_back((nameLength >>  8) & 0xff);
    data.push_back((nameLength >> 16) & 0xff);
    data.push_back((nameLength >> 24) & 0xff);
    data.push_back((dataLength >>  0) & 0xff);
    data.push_back((dataLength >>  8) & 0xff);
    data.push_back((dataLength >> 16) & 0xff);
    data.push_back((dataLength >> 24) & 0xff);
    data.push_back((reservedEnvironmentVariable >>  0) & 0xff);
    data.push_back((reservedEnvironmentVariable >>  8) & 0xff);
    data.push_back((reservedEnvironmentVariable >> 16) & 0xff);
    data.push_back((reservedEnvironmentVariable >> 24) & 0xff);
    data.push_back((reservedEnvironmentVariable >> 32) & 0xff);
    data.push_back((reservedEnvironmentVariable >> 40) & 0xff);
    data.push_back((reservedEnvironmentVariable >> 48) & 0xff);
    data.push_back((reservedEnvironmentVariable >> 56) & 0xff);
    data.insert(std::end(data), std::begin(name), std::end(name));
    data.insert(std::end(data), std::begin(this->data), std::end(this->data));
}

DWORD EnvironmentVariable::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(nameLength) +
        sizeof(dataLength) +
        sizeof(reservedEnvironmentVariable) +
        nameLength +
        dataLength;
}

}
}
