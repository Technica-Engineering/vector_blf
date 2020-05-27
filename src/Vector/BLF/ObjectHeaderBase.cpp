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

#include <Vector/BLF/ObjectHeaderBase.h>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/Exceptions.h>

namespace Vector {
namespace BLF {

ObjectHeaderBase::ObjectHeaderBase(const WORD headerVersion, const ObjectType objectType) :
    headerVersion(headerVersion),
    objectType(objectType) {
}

void ObjectHeaderBase::read(AbstractFile & is) {
    is.read(reinterpret_cast<char *>(&signature), sizeof(signature));
    if (signature != ObjectSignature)
        throw Exception("ObjectHeaderBase::read(): Object signature doesn't match at this position.");
    is.read(reinterpret_cast<char *>(&headerSize), sizeof(headerSize));
    is.read(reinterpret_cast<char *>(&headerVersion), sizeof(headerVersion));
    is.read(reinterpret_cast<char *>(&objectSize), sizeof(objectSize));
    is.read(reinterpret_cast<char *>(&objectType), sizeof(objectType));
}

void ObjectHeaderBase::write(AbstractFile & os) {
    /* pre processing */
    headerSize = calculateHeaderSize();
    objectSize = calculateObjectSize();

    os.write(reinterpret_cast<char *>(&signature), sizeof(signature));
    os.write(reinterpret_cast<char *>(&headerSize), sizeof(headerSize));
    os.write(reinterpret_cast<char *>(&headerVersion), sizeof(headerVersion));
    os.write(reinterpret_cast<char *>(&objectSize), sizeof(objectSize));
    os.write(reinterpret_cast<char *>(&objectType), sizeof(objectType));
}

WORD ObjectHeaderBase::calculateHeaderSize() const {
    return
        sizeof(signature) +
        sizeof(headerSize) +
        sizeof(headerVersion) +
        sizeof(objectSize) +
        sizeof(objectType);
}

DWORD ObjectHeaderBase::calculateObjectSize() const {
    return calculateHeaderSize();
}

}
}
