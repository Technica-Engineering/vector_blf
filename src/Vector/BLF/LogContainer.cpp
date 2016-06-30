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

#include "LogContainer.h"
#include "ObjectHeader.h"

namespace Vector {
namespace BLF {

LogContainer::LogContainer() :
    ObjectHeaderBase(),
    objectFlags(ObjectHeader::ObjectFlags::TimeOneNans),
    reserved(),
    objectVersion(),
    uncompressedFileSize(),
    compressedFile(),
    compressedFileSize()
{
    headerVersion = 1;
    objectType = ObjectType::LOG_CONTAINER;
}

void LogContainer::read(AbstractFile & is)
{
    ObjectHeaderBase::read(is);
    is.read(reinterpret_cast<char *>(&objectFlags), sizeof(objectFlags));
    is.read(reinterpret_cast<char *>(&reserved), sizeof(reserved));
    is.read(reinterpret_cast<char *>(&objectVersion), sizeof(objectVersion));
    is.read(reinterpret_cast<char *>(&uncompressedFileSize), sizeof(uncompressedFileSize));
    compressedFileSize = objectSize - internalHeaderSize();
    compressedFile.resize(compressedFileSize);
    is.read(reinterpret_cast<char *>(compressedFile.data()), compressedFileSize);
}

void LogContainer::write(AbstractFile & os)
{
    /* pre processing */
    compressedFileSize = compressedFile.size();

    ObjectHeaderBase::write(os);
    os.write(reinterpret_cast<char *>(&objectFlags), sizeof(objectFlags));
    os.write(reinterpret_cast<char *>(&reserved), sizeof(reserved));
    os.write(reinterpret_cast<char *>(&objectVersion), sizeof(objectVersion));
    os.write(reinterpret_cast<char *>(&uncompressedFileSize), sizeof(uncompressedFileSize));
    os.write(reinterpret_cast<char *>(compressedFile.data()), compressedFileSize);
}

DWORD LogContainer::calculateObjectSize() const
{
    return
        internalHeaderSize() +
        static_cast<DWORD>(compressedFileSize);
}

WORD LogContainer::internalHeaderSize() const
{
    return
        ObjectHeaderBase::calculateHeaderSize() +
        sizeof(objectFlags) +
        sizeof(reserved) +
        sizeof(objectVersion) +
        sizeof(uncompressedFileSize);
}

}
}
