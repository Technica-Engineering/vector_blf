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

#include "SystemVariable.h"

#include <cstring>

namespace Vector {
namespace BLF {

SystemVariable::SystemVariable() :
    ObjectHeader(),
    type(),
    reserved1(),
    nameLength(),
    dataLength(),
    reserved2(),
    name(),
    data()
{
    objectType = ObjectType::SYS_VARIABLE;
}

SystemVariable::~SystemVariable()
{
}

char * SystemVariable::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // type
    size = sizeof(type);
    memcpy((void *) &type, buffer, size);
    buffer += size;

    // reserved1
    size = reserved1.size() * sizeof(DWORD);
    memcpy(reserved1.data(), buffer, size);
    buffer += size;

    // nameLength
    size = sizeof(nameLength);
    memcpy((void *) &nameLength, buffer, size);
    buffer += size;

    // dataLength
    size = sizeof(dataLength);
    memcpy((void *) &dataLength, buffer, size);
    buffer += size;

    // reserved2
    size = reserved2.size() * sizeof(BYTE);
    memcpy(reserved2.data(), buffer, size);
    buffer += size;

    // name
    size = nameLength;
    name.assign(buffer, size);
    buffer += size;

    // data
    size = dataLength;
    data.reserve(size);
    memcpy(data.data(), buffer, size);
    buffer += size;

    return buffer;
}

char * SystemVariable::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // type
    size = sizeof(type);
    memcpy(buffer, (void *) &type, size);
    buffer += size;

    // reserved1
    size = reserved1.size() * sizeof(DWORD);
    memcpy(buffer, reserved1.data(), size);
    buffer += size;

    // nameLength
    size = sizeof(nameLength);
    memcpy(buffer, (void *) &nameLength, size);
    buffer += size;

    // dataLength
    size = sizeof(dataLength);
    memcpy(buffer, (void *) &dataLength, size);
    buffer += size;

    // reserved2
    size = reserved2.size() * sizeof(BYTE);
    memcpy(buffer, reserved2.data(), size);
    buffer += size;

    // name
    size = nameLength;
    memcpy(buffer, name.data(), size);
    buffer += size;

    // data
    size = dataLength;
    memcpy(buffer, data.data(), size);
    buffer += size;

    return buffer;
}

size_t SystemVariable::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(type) +
        reserved1.size() * sizeof(DWORD) +
        sizeof(nameLength) +
        sizeof(dataLength) +
        reserved2.size() * sizeof(BYTE) +
        nameLength +
        dataLength;

    return size;
}

}
}
