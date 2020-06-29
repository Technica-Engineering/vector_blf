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

#include <Vector/BLF/SystemVariable.h>

namespace Vector {
namespace BLF {

SystemVariable::SystemVariable() :
    ObjectHeader(ObjectType::SYS_VARIABLE) {
}

std::vector<uint8_t>::iterator SystemVariable::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    type =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    representation =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedSystemVariable1 =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
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
    reservedSystemVariable2 =
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
    it += name.size();
    this->data.resize(dataLength);
    std::copy(it, it + this->data.size(), std::begin(this->data));
    it += this->data.size();

    return it;
}

void SystemVariable::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    nameLength = static_cast<DWORD>(name.size());
    dataLength = static_cast<DWORD>(this->data.size());

    ObjectHeader::toData(data);

    data.push_back((type >>  0) & 0xff);
    data.push_back((type >>  8) & 0xff);
    data.push_back((type >> 16) & 0xff);
    data.push_back((type >> 24) & 0xff);
    data.push_back((representation >>  0) & 0xff);
    data.push_back((representation >>  8) & 0xff);
    data.push_back((representation >> 16) & 0xff);
    data.push_back((representation >> 24) & 0xff);
    data.push_back((reservedSystemVariable1 >>  0) & 0xff);
    data.push_back((reservedSystemVariable1 >>  8) & 0xff);
    data.push_back((reservedSystemVariable1 >> 16) & 0xff);
    data.push_back((reservedSystemVariable1 >> 24) & 0xff);
    data.push_back((reservedSystemVariable1 >> 32) & 0xff);
    data.push_back((reservedSystemVariable1 >> 40) & 0xff);
    data.push_back((reservedSystemVariable1 >> 48) & 0xff);
    data.push_back((reservedSystemVariable1 >> 56) & 0xff);
    data.push_back((nameLength >>  0) & 0xff);
    data.push_back((nameLength >>  8) & 0xff);
    data.push_back((nameLength >> 16) & 0xff);
    data.push_back((nameLength >> 24) & 0xff);
    data.push_back((dataLength >>  0) & 0xff);
    data.push_back((dataLength >>  8) & 0xff);
    data.push_back((dataLength >> 16) & 0xff);
    data.push_back((dataLength >> 24) & 0xff);
    data.push_back((reservedSystemVariable2 >>  0) & 0xff);
    data.push_back((reservedSystemVariable2 >>  8) & 0xff);
    data.push_back((reservedSystemVariable2 >> 16) & 0xff);
    data.push_back((reservedSystemVariable2 >> 24) & 0xff);
    data.push_back((reservedSystemVariable2 >> 32) & 0xff);
    data.push_back((reservedSystemVariable2 >> 40) & 0xff);
    data.push_back((reservedSystemVariable2 >> 48) & 0xff);
    data.push_back((reservedSystemVariable2 >> 56) & 0xff);
    data.insert(std::end(data), std::begin(name), std::end(name));
    data.insert(std::end(data), std::begin(this->data), std::end(this->data));
}

DWORD SystemVariable::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(type) +
        sizeof(representation) +
        sizeof(reservedSystemVariable1) +
        sizeof(nameLength) +
        sizeof(dataLength) +
        sizeof(reservedSystemVariable2) +
        nameLength +
        dataLength;
}

}
}
