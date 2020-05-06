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
    ObjectHeader(ObjectType::Unknown115) {
}

void Unknown115::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&reservedUnknownObject1), sizeof(reservedUnknownObject1));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject2), sizeof(reservedUnknownObject2));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject3), sizeof(reservedUnknownObject3));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject4), sizeof(reservedUnknownObject4));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject5), sizeof(reservedUnknownObject5));
    is.read(reinterpret_cast<char *>(&reservedUnknownObject6), sizeof(reservedUnknownObject6));
}

void Unknown115::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&reservedUnknownObject1), sizeof(reservedUnknownObject1));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject2), sizeof(reservedUnknownObject2));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject3), sizeof(reservedUnknownObject3));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject4), sizeof(reservedUnknownObject4));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject5), sizeof(reservedUnknownObject5));
    os.write(reinterpret_cast<char *>(&reservedUnknownObject6), sizeof(reservedUnknownObject6));
}

DWORD Unknown115::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(reservedUnknownObject1) +
        sizeof(reservedUnknownObject2) +
        sizeof(reservedUnknownObject3) +
        sizeof(reservedUnknownObject4) +
        sizeof(reservedUnknownObject5) +
        sizeof(reservedUnknownObject6);
}

}
}
