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

#include <Vector/BLF/FunctionBus.h>

namespace Vector {
namespace BLF {

FunctionBus::FunctionBus() :
    ObjectHeader(ObjectType::FUNCTION_BUS) {
}

std::vector<uint8_t>::iterator FunctionBus::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    functionBusObjectType =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    veType =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
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
    name.assign(it, it + nameLength);
    it += nameLength;
    this->data.resize(dataLength);
    std::copy(it, it + this->data.size(), std::begin(this->data));
    it += dataLength;

    return it;
}

void FunctionBus::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    nameLength = static_cast<DWORD>(name.size());
    dataLength = static_cast<DWORD>(this->data.size());

    ObjectHeader::toData(data);

    data.push_back((functionBusObjectType >>  0) & 0xff);
    data.push_back((functionBusObjectType >>  8) & 0xff);
    data.push_back((functionBusObjectType >> 16) & 0xff);
    data.push_back((functionBusObjectType >> 24) & 0xff);
    data.push_back((veType >>  0) & 0xff);
    data.push_back((veType >>  8) & 0xff);
    data.push_back((veType >> 16) & 0xff);
    data.push_back((veType >> 24) & 0xff);
    data.push_back((nameLength >>  0) & 0xff);
    data.push_back((nameLength >>  8) & 0xff);
    data.push_back((nameLength >> 16) & 0xff);
    data.push_back((nameLength >> 24) & 0xff);
    data.push_back((dataLength >>  0) & 0xff);
    data.push_back((dataLength >>  8) & 0xff);
    data.push_back((dataLength >> 16) & 0xff);
    data.push_back((dataLength >> 24) & 0xff);
    data.insert(std::end(data), std::begin(name), std::end(name));
    data.insert(std::end(data), std::begin(this->data), std::end(this->data));
}

DWORD FunctionBus::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(functionBusObjectType) +
        sizeof(veType) +
        sizeof(nameLength) +
        sizeof(dataLength) +
        nameLength +
        dataLength;
}

}
}
