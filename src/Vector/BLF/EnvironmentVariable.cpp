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

#include "EnvironmentVariable.h"
#include <cstring>

namespace Vector {
namespace BLF {

EnvironmentVariable::EnvironmentVariable() :
    ObjectHeader(),
    nameLength(),
    dataLength(),
    unknown(),
    name(nullptr),
    data(nullptr)
{
}

EnvironmentVariable::~EnvironmentVariable()
{
    delete[] name;
    name = nullptr;

    delete[] data;
    data = nullptr;
}

char * EnvironmentVariable::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // nameLength
    size = sizeof(nameLength);
    memcpy((char *) &nameLength, buffer, size);
    buffer += size;

    // dataLength
    size = sizeof(dataLength);
    memcpy((char *) &dataLength, buffer, size);
    buffer += size;

    // unknown
    size = sizeof(unknown);
    memcpy((char *) &unknown, buffer, size);
    buffer += size;

    /* name */
    size = nameLength;
    name = new char[nameLength+1];
    memcpy(name, buffer, size);
    buffer += size;
    name[nameLength] = 0;

    /* data */
    size = dataLength;
    data = new char[dataLength];
    memcpy(data, buffer, size);
    buffer += size;

    return buffer;
}

}
}
