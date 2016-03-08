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

#include "AbstractFile.h"
#include "ObjectHeaderBase.h"

namespace Vector {
namespace BLF {

ObjectHeaderBase::ObjectHeaderBase() :
    signature(ObjectSignature),
    headerSize(calculateHeaderSize()),
    headerVersion(), // is set in ObjectHeader/ObjectHeader2
    objectSize(),
    objectType() // is set in each event class constructor
{
}

ObjectHeaderBase::~ObjectHeaderBase()
{
}

void ObjectHeaderBase::read(AbstractFile & is)
{
    is.read((char *) &signature, sizeof(signature));
    if (signature != ObjectSignature)
        return;
    is.read((char *) &headerSize, sizeof(headerSize));
    is.read((char *) &headerVersion, sizeof(headerVersion));
    is.read((char *) &objectSize, sizeof(objectSize));
    is.read((char *) &objectType, sizeof(objectType));
}

void ObjectHeaderBase::write(AbstractFile & os)
{
    /* pre processing */
    objectSize = calculateObjectSize();

    os.write((char *) &signature, sizeof(signature));
    if (signature != ObjectSignature)
        return;
    os.write((char *) &headerSize, sizeof(headerSize));
    os.write((char *) &headerVersion, sizeof(headerVersion));
    os.write((char *) &objectSize, sizeof(objectSize));
    os.write((char *) &objectType, sizeof(objectType));
}

size_t ObjectHeaderBase::calculateHeaderSize()
{
    return
        sizeof(signature) +
        sizeof(headerSize) +
        sizeof(headerVersion) +
        sizeof(objectSize) +
        sizeof(objectType);
}

size_t ObjectHeaderBase::calculateObjectSize()
{
    return calculateHeaderSize();
}

}
}
