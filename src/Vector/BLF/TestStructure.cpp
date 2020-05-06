/*
 * Copyright (C) 2013 Tobias Lorenz.
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

void TestStructure::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&executionObjectIdentify), sizeof(executionObjectIdentify));
    is.read(reinterpret_cast<char *>(&type), sizeof(type));
    is.read(reinterpret_cast<char *>(&reservedTestStructure), sizeof(reservedTestStructure));
    is.read(reinterpret_cast<char *>(&uniqueNo), sizeof(uniqueNo));
    is.read(reinterpret_cast<char *>(&action), sizeof(action));
    is.read(reinterpret_cast<char *>(&result), sizeof(result));
    is.read(reinterpret_cast<char *>(&executingObjectNameLength), sizeof(executingObjectNameLength));
    is.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
    is.read(reinterpret_cast<char *>(&textLength), sizeof(textLength));
    executingObjectName.resize(executingObjectNameLength);
    is.read(const_cast<char *>(reinterpret_cast<const char *>(executingObjectName.data())), executingObjectNameLength * sizeof(char16_t));
    name.resize(nameLength);
    is.read(const_cast<char *>(reinterpret_cast<const char *>(name.data())), nameLength * sizeof(char16_t));
    text.resize(textLength);
    is.read(const_cast<char *>(reinterpret_cast<const char *>(text.data())), textLength * sizeof(char16_t));
}

void TestStructure::write(AbstractFile & os) {
    /* pre processing */
    executingObjectNameLength = static_cast<DWORD>(executingObjectName.size());
    nameLength = static_cast<DWORD>(name.size());
    textLength = static_cast<DWORD>(text.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&executionObjectIdentify), sizeof(executionObjectIdentify));
    os.write(reinterpret_cast<char *>(&type), sizeof(type));
    os.write(reinterpret_cast<char *>(&reservedTestStructure), sizeof(reservedTestStructure));
    os.write(reinterpret_cast<char *>(&uniqueNo), sizeof(uniqueNo));
    os.write(reinterpret_cast<char *>(&action), sizeof(action));
    os.write(reinterpret_cast<char *>(&result), sizeof(result));
    os.write(reinterpret_cast<char *>(&executingObjectNameLength), sizeof(executingObjectNameLength));
    os.write(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
    os.write(reinterpret_cast<char *>(&textLength), sizeof(textLength));
    os.write(const_cast<char *>(reinterpret_cast<const char *>(executingObjectName.data())), executingObjectNameLength * sizeof(char16_t));
    os.write(const_cast<char *>(reinterpret_cast<const char *>(name.data())), nameLength * sizeof(char16_t));
    os.write(const_cast<char *>(reinterpret_cast<const char *>(text.data())), textLength * sizeof(char16_t));
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
