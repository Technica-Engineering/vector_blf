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

#include "ObjectHeaderBase.h"

#include <iostream>

namespace Vector {
namespace BLF {

ObjectHeaderBase::ObjectHeaderBase() :
    signature(),
    headerSize(),
    headerVersion(),
    objectSize(),
    objectType(),
    remainingSize(),
    alreadyRead(false)
{
}

ObjectHeaderBase::~ObjectHeaderBase()
{
}

void ObjectHeaderBase::read(std::istream & is)
{
    if (alreadyRead)
        return;

    /* read data */
    const std::streamsize size =
            sizeof(signature) +
            sizeof(headerSize) +
            sizeof(headerVersion) +
            sizeof(objectSize) +
            sizeof(objectType);
    is.read((char *) &signature, sizeof(signature));
    is.read((char *) &headerSize, sizeof(headerSize));
    is.read((char *) &headerVersion, sizeof(headerVersion));
    is.read((char *) &objectSize, sizeof(objectSize));
    is.read((char *) &objectType, sizeof(objectType));
    remainingSize = objectSize - size;

    alreadyRead = true;

    /* checks */
    if (signature != ObjectSignature) {
        std::cerr << "Unexpected object signature at pos 0x" << std::hex << (unsigned long) is.tellg() - 0x10 << std::endl;
        return;
    }
}

void ObjectHeaderBase::skip(std::istream & is)
{
    /* read the header at least */
    if (!alreadyRead)
        read(is);

    /* skip object */
    is.seekg(remainingSize, std::ifstream::cur);
    remainingSize = 0;
}

void ObjectHeaderBase::copyObjectHeaderBase(ObjectHeaderBase & ohb)
{
    signature = ohb.signature;
    headerSize = ohb.headerSize;
    headerVersion = ohb.headerVersion;
    objectSize = ohb.objectSize;
    objectType = ohb.objectType;
    remainingSize = ohb.remainingSize;
    alreadyRead = ohb.alreadyRead;
}

void ObjectHeaderBase::setObjectSize()
{
    /* do nothing here */
}

}
}
