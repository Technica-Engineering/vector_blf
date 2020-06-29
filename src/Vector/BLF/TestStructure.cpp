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

#include <Vector/BLF/TestStructure.h>

namespace Vector {
namespace BLF {

TestStructure::TestStructure() :
    ObjectHeader(ObjectType::TEST_STRUCTURE) {
}

std::vector<uint8_t>::iterator TestStructure::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    executionObjectIdentify =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    type =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedTestStructure =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    uniqueNo =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    action =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    result =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    executingObjectNameLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    nameLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    textLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    executingObjectName.resize(executingObjectNameLength);
    std::copy(it, it + executingObjectName.size(), std::begin(executingObjectName));
    it += executingObjectName.size();
    name.resize(nameLength);
    std::copy(it, it + name.size(), std::begin(name));
    it += name.size();
    text.resize(textLength);
    std::copy(it, it + text.size(), std::begin(text));
    it += text.size();

    return it;
}

void TestStructure::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    executingObjectNameLength = static_cast<DWORD>(executingObjectName.size());
    nameLength = static_cast<DWORD>(name.size());
    textLength = static_cast<DWORD>(text.size());

    ObjectHeader::toData(data);

    data.push_back((executionObjectIdentify >>  0) & 0xff);
    data.push_back((executionObjectIdentify >>  8) & 0xff);
    data.push_back((executionObjectIdentify >> 16) & 0xff);
    data.push_back((executionObjectIdentify >> 24) & 0xff);
    data.push_back((type >>  0) & 0xff);
    data.push_back((type >>  8) & 0xff);
    data.push_back((reservedTestStructure >>  0) & 0xff);
    data.push_back((reservedTestStructure >>  8) & 0xff);
    data.push_back((uniqueNo >>  0) & 0xff);
    data.push_back((uniqueNo >>  8) & 0xff);
    data.push_back((uniqueNo >> 16) & 0xff);
    data.push_back((uniqueNo >> 24) & 0xff);
    data.push_back((action >>  0) & 0xff);
    data.push_back((action >>  8) & 0xff);
    data.push_back((result >>  0) & 0xff);
    data.push_back((result >>  8) & 0xff);
    data.push_back((executingObjectNameLength >>  0) & 0xff);
    data.push_back((executingObjectNameLength >>  8) & 0xff);
    data.push_back((executingObjectNameLength >> 16) & 0xff);
    data.push_back((executingObjectNameLength >> 24) & 0xff);
    data.push_back((nameLength >>  0) & 0xff);
    data.push_back((nameLength >>  8) & 0xff);
    data.push_back((nameLength >> 16) & 0xff);
    data.push_back((nameLength >> 24) & 0xff);
    data.push_back((textLength >>  0) & 0xff);
    data.push_back((textLength >>  8) & 0xff);
    data.push_back((textLength >> 16) & 0xff);
    data.push_back((textLength >> 24) & 0xff);
    data.insert(std::end(data), std::begin(executingObjectName), std::end(executingObjectName));
    data.insert(std::end(data), std::begin(name), std::end(name));
    data.insert(std::end(data), std::begin(text), std::end(text));
}

DWORD TestStructure::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(executionObjectIdentify) +
        sizeof(type) +
        sizeof(reservedTestStructure) +
        sizeof(uniqueNo) +
        sizeof(action) +
        sizeof(result) +
        sizeof(executingObjectNameLength) +
        sizeof(nameLength) +
        sizeof(textLength) +
        (executingObjectNameLength + nameLength + textLength) * sizeof(char16_t);
}

}
}
