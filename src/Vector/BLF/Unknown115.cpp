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
    ObjectHeader()
{
    objectType = ObjectType::Unknown115;
}

void Unknown115::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&reservedUnknown1), sizeof(reservedUnknown1));
    is.read(reinterpret_cast<char *>(&reservedUnknown2), sizeof(reservedUnknown2));
    is.read(reinterpret_cast<char *>(&reservedUnknown3), sizeof(reservedUnknown3));
    is.read(reinterpret_cast<char *>(&reservedUnknown4), sizeof(reservedUnknown4));
    is.read(reinterpret_cast<char *>(&reservedUnknown5), sizeof(reservedUnknown5));
    is.read(reinterpret_cast<char *>(&reservedUnknown6), sizeof(reservedUnknown6));
}

void Unknown115::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&reservedUnknown1), sizeof(reservedUnknown1));
    os.write(reinterpret_cast<char *>(&reservedUnknown2), sizeof(reservedUnknown2));
    os.write(reinterpret_cast<char *>(&reservedUnknown3), sizeof(reservedUnknown3));
    os.write(reinterpret_cast<char *>(&reservedUnknown4), sizeof(reservedUnknown4));
    os.write(reinterpret_cast<char *>(&reservedUnknown5), sizeof(reservedUnknown5));
    os.write(reinterpret_cast<char *>(&reservedUnknown6), sizeof(reservedUnknown6));
}

DWORD Unknown115::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(reservedUnknown1) +
        sizeof(reservedUnknown2) +
        sizeof(reservedUnknown3) +
        sizeof(reservedUnknown4) +
        sizeof(reservedUnknown5) +
        sizeof(reservedUnknown6);
}

}
}
