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

#include <Vector/BLF/Unknown115.h>

namespace Vector {
namespace BLF {

Unknown115::Unknown115() :
    ObjectHeaderBase(),
    objectFlags(),
    clientIndex(),
    objectVersion(),
    objectTimeStamp(),
    reservedUnknownObject1(),
    reservedUnknownObject2(),
    reservedUnknownObject3(),
    reservedUnknownObject4(),
    reservedUnknownObject5(),
    reservedUnknownObject6(),
    reservedUnknownObject7(),
    reservedUnknownObject8(),
    reservedUnknownObject9()
{
    headerVersion = 1;
    objectType = ObjectType::Unknown115;
}

void Unknown115::read(AbstractFile & is)
{
    ObjectHeaderBase::read(is);
    is.read(reinterpret_cast<char *>(&objectFlags), sizeof(objectFlags));
    is.read(reinterpret_cast<char *>(&clientIndex), sizeof(clientIndex));
    is.read(reinterpret_cast<char *>(&objectVersion), sizeof(objectVersion));
    is.read(reinterpret_cast<char *>(&objectTimeStamp), sizeof(objectTimeStamp));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject1), sizeof(reservedUnknownObject1));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject2), sizeof(reservedUnknownObject2));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject3), sizeof(reservedUnknownObject3));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject4), sizeof(reservedUnknownObject4));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject5), sizeof(reservedUnknownObject5));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject6), sizeof(reservedUnknownObject6));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject7), sizeof(reservedUnknownObject7));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject8), sizeof(reservedUnknownObject8));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject9), sizeof(reservedUnknownObject9));
}

void Unknown115::write(AbstractFile & os)
{
    ObjectHeaderBase::write(os);
    os.write(reinterpret_cast<char *>(&objectFlags), sizeof(objectFlags));
    os.write(reinterpret_cast<char *>(&clientIndex), sizeof(clientIndex));
    os.write(reinterpret_cast<char *>(&objectVersion), sizeof(objectVersion));
    os.write(reinterpret_cast<char *>(&objectTimeStamp), sizeof(objectTimeStamp));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject1), sizeof(reservedUnknownObject1));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject2), sizeof(reservedUnknownObject2));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject3), sizeof(reservedUnknownObject3));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject4), sizeof(reservedUnknownObject4));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject5), sizeof(reservedUnknownObject5));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject6), sizeof(reservedUnknownObject6));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject7), sizeof(reservedUnknownObject7));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject8), sizeof(reservedUnknownObject8));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject9), sizeof(reservedUnknownObject9));
}

WORD Unknown115::calculateHeaderSize() const
{
    return
        ObjectHeaderBase::calculateHeaderSize() +
        sizeof(objectFlags) +
        sizeof(clientIndex) +
        sizeof(objectVersion) +
        sizeof(objectTimeStamp);
}

DWORD Unknown115::calculateObjectSize() const
{
    return
        ObjectHeaderBase::calculateObjectSize() +
        sizeof(reservedUnknownObject1) +
        sizeof(reservedUnknownObject2) +
        sizeof(reservedUnknownObject3) +
        sizeof(reservedUnknownObject4) +
        sizeof(reservedUnknownObject5) +
        sizeof(reservedUnknownObject6) +
        sizeof(reservedUnknownObject7) +
        sizeof(reservedUnknownObject8) +
        sizeof(reservedUnknownObject9);
}

}
}
