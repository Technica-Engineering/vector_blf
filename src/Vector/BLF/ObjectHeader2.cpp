/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
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

#include <Vector/BLF/ObjectHeader2.h>

namespace Vector {
namespace BLF {

ObjectHeader2::ObjectHeader2(const ObjectType objectType) :
    ObjectHeaderBase(2, objectType) {
}

void ObjectHeader2::read(AbstractFile & is) {
    ObjectHeaderBase::read(is);
    is.read(reinterpret_cast<char *>(&objectFlags), sizeof(objectFlags));
    is.read(reinterpret_cast<char *>(&timeStampStatus), sizeof(timeStampStatus));
    is.read(reinterpret_cast<char *>(&reservedObjectHeader), sizeof(reservedObjectHeader));
    is.read(reinterpret_cast<char *>(&objectVersion), sizeof(objectVersion));
    is.read(reinterpret_cast<char *>(&objectTimeStamp), sizeof(objectTimeStamp));
    is.read(reinterpret_cast<char *>(&originalTimeStamp), sizeof(originalTimeStamp));
}

void ObjectHeader2::write(AbstractFile & os) {
    ObjectHeaderBase::write(os);
    os.write(reinterpret_cast<char *>(&objectFlags), sizeof(objectFlags));
    os.write(reinterpret_cast<char *>(&timeStampStatus), sizeof(timeStampStatus));
    os.write(reinterpret_cast<char *>(&reservedObjectHeader), sizeof(reservedObjectHeader));
    os.write(reinterpret_cast<char *>(&objectVersion), sizeof(objectVersion));
    os.write(reinterpret_cast<char *>(&objectTimeStamp), sizeof(objectTimeStamp));
    os.write(reinterpret_cast<char *>(&originalTimeStamp), sizeof(originalTimeStamp));
}

WORD ObjectHeader2::calculateHeaderSize() const {
    return
        ObjectHeaderBase::calculateHeaderSize() +
        sizeof(objectFlags) +
        sizeof(timeStampStatus) +
        sizeof(reservedObjectHeader) +
        sizeof(objectVersion) +
        sizeof(objectTimeStamp) +
        sizeof(originalTimeStamp);
}

DWORD ObjectHeader2::calculateObjectSize() const {
    return calculateHeaderSize();
}

}
}
