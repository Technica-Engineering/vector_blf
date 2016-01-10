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

#include <cstring>

#include "EnvironmentVariable.h"

namespace Vector {
namespace BLF {

EnvironmentVariable::EnvironmentVariable() :
    ObjectHeader(),
    nameLength(),
    dataLength(),
    reserved(),
    name(),
    data()
{
    /* can be one of:
     *   - objectType = ObjectType::ENV_INTEGER;
     *   - objectType = ObjectType::ENV_DOUBLE;
     *   - objectType = ObjectType::ENV_STRING;
     *   - objectType = ObjectType::ENV_DATA;
     */
}

void EnvironmentVariable::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &nameLength, sizeof(nameLength));
    is.read((char *) &dataLength, sizeof(dataLength));
    is.read((char *) &reserved, sizeof(reserved));
    name.resize(nameLength);
    is.read((char *) name.data(), nameLength);
    data.resize(dataLength);
    is.read((char *) data.data(), dataLength);

    /* post processing */
    name.resize(strnlen(name.c_str(), nameLength)); // Vector bug: the actual string can be shorter than size!
    objectSize = calculateObjectSize();
}

void EnvironmentVariable::write(AbstractFile & os)
{
    /* pre processing */
    nameLength = name.size();
    dataLength = data.size();

    ObjectHeader::write(os);
    os.write((char *) &nameLength, sizeof(nameLength));
    os.write((char *) &dataLength, sizeof(dataLength));
    os.write((char *) &reserved, sizeof(reserved));
    os.write((char *) name.data(), nameLength);
    os.write((char *) data.data(), dataLength);
}

size_t EnvironmentVariable::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(nameLength) +
        sizeof(dataLength) +
        reserved.size() +
        nameLength +
        dataLength;

    return size;
}

}
}
