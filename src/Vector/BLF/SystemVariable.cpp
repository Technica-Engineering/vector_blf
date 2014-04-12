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
    data(nullptr),
    alreadyRead(false)
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

    /* read object header */
    ObjectHeader::read(is);

    /* read remaining data */
    is.read((char *) &type, sizeof(type));
    remainingSize -= is.gcount();
    is.read((char *) &reserved, sizeof(reserved));
    remainingSize -= is.gcount();
    is.read((char *) &nameLength, sizeof(nameLength));
    remainingSize -= is.gcount();
    is.read((char *) &dataLength, sizeof(dataLength));
    remainingSize -= is.gcount();
    is.read((char *) &unknown, sizeof(unknown));
    remainingSize -= is.gcount();

    /* read name */
    name = new char[nameLength+1];
    is.read(name, nameLength);
    remainingSize -= is.gcount();
    name[nameLength] = 0;

    /* read data */
    data = new char[dataLength];
    is.read(data, dataLength);
    remainingSize -= is.gcount();

    alreadyRead = true;
}

void SystemVariable::setObjectSize()
{
    // @todo objectSize = sizeof(SystemVariable) + nameLength + dataLength;
}

}
}
