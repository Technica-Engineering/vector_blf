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

namespace Vector {
namespace BLF {

SystemVariable::SystemVariable() :
    ObjectHeader(),
    type(),
    reserved(),
    nameLength(),
    dataLength(),
    unknown(),
    name(nullptr),
    data(nullptr)
{
}

SystemVariable::~SystemVariable()
{
    delete name;
    name = nullptr;

    delete data;
    data = nullptr;
}

void SystemVariable::read(std::istream & is)
{
    if (alreadyRead)
        return;

    ObjectHeader::read(is);

    const std::streamsize size =
            sizeof(type) +
            sizeof(reserved) +
            sizeof(nameLength) +
            sizeof(dataLength) +
            sizeof(unknown);
    is.read((char *) &nameLength, size);
    remainingSize -= size;

    name = new char[nameLength+1];
    is.read(name, nameLength);
    name[nameLength] = 0;
    remainingSize -= nameLength;

    data = new char[dataLength];
    is.read(data, dataLength);
    remainingSize -= dataLength;

    alreadyRead = true;
}

void SystemVariable::setObjectSize()
{
    // @todo objectSize = sizeof(SystemVariable) + nameLength + dataLength;
}

}
}
