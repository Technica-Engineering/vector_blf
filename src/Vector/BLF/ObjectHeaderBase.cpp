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

#include <cstring>
#include <iostream>

namespace Vector {
namespace BLF {

ObjectHeaderBase::ObjectHeaderBase() :
    signature(),
    headerSize(),
    headerVersion(),
    objectSize(),
    objectType()
{
}

ObjectHeaderBase::~ObjectHeaderBase()
{
}

char * ObjectHeaderBase::parse(char * buffer)
{
    size_t size;

    // signature
    size = sizeof(signature);
    memcpy((void *) &signature, buffer, size);
    buffer += size;

    // headerSize
    size = sizeof(headerSize);
    memcpy((void *) &headerSize, buffer, size);
    buffer += size;

    // headerVersion
    size = sizeof(headerVersion);
    memcpy((void *) &headerVersion, buffer, size);
    buffer += size;

    // objectSize
    size = sizeof(objectSize);
    memcpy((void *) &objectSize, buffer, size);
    buffer += size;

    // objectType
    size = sizeof(objectType);
    memcpy((void *) &objectType, buffer, size);
    buffer += size;

    /* checks */
    if (signature != ObjectSignature) {
        std::cerr << "Unexpected object signature" << std::endl;
    }

    return buffer;
}

size_t ObjectHeaderBase::calculateHeaderSize()
{
    size_t size =
        sizeof(signature) +
        sizeof(headerSize) +
        sizeof(headerVersion) +
        sizeof(objectSize) +
        sizeof(objectType);

    return size;
}

size_t ObjectHeaderBase::calculateObjectSize()
{
    return calculateHeaderSize();
}

}
}
