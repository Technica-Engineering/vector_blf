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

#include <Vector/BLF/FunctionBus.h>

namespace Vector {
namespace BLF {

FunctionBus::FunctionBus() :
    ObjectHeader()
{
    objectType = ObjectType::FUNCTION_BUS;
}

void FunctionBus::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&functionBusObjectType), sizeof(functionBusObjectType));
    is.read(reinterpret_cast<char *>(&veType), sizeof(veType));
    is.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
    is.read(reinterpret_cast<char *>(&dataLength), sizeof(dataLength));
    name.resize(nameLength);
    is.read(const_cast<char *>(name.data()), nameLength);
    data.resize(dataLength);
    is.read(reinterpret_cast<char *>(data.data()), dataLength);
}

void FunctionBus::write(AbstractFile & os)
{
    /* pre processing */
    nameLength = static_cast<DWORD>(name.size());
    dataLength = static_cast<DWORD>(data.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&functionBusObjectType), sizeof(functionBusObjectType));
    os.write(reinterpret_cast<char *>(&veType), sizeof(veType));
    os.write(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
    os.write(reinterpret_cast<char *>(&dataLength), sizeof(dataLength));
    os.write(const_cast<char *>(name.data()), nameLength);
    os.write(reinterpret_cast<char *>(data.data()), dataLength);
}

DWORD FunctionBus::calculateObjectSize() const
{
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
