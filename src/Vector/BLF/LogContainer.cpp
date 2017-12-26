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

#include <Vector/BLF/LogContainer.h>

namespace Vector {
namespace BLF {

LogContainer::LogContainer() :
    ObjectHeaderBase(),
    unknownCompression(),
    reservedLogContainer1(0),
    reservedLogContainer2(0),
    uncompressedFileSize(0),
    reservedLogContainer3(0),
    compressedFile(),
    compressedFileSize(0)
{
    headerVersion = 1;
    objectType = ObjectType::LOG_CONTAINER;
}

void LogContainer::read(AbstractFile & is)
{
    ObjectHeaderBase::read(is);
    is.read(reinterpret_cast<char *>(&unknownCompression), sizeof(unknownCompression));
    is.read(reinterpret_cast<char *>(&reservedLogContainer1), sizeof(reservedLogContainer1));
    is.read(reinterpret_cast<char *>(&reservedLogContainer2), sizeof(reservedLogContainer2));
    is.read(reinterpret_cast<char *>(&uncompressedFileSize), sizeof(uncompressedFileSize));
    is.read(reinterpret_cast<char *>(&reservedLogContainer3), sizeof(reservedLogContainer3));
    compressedFileSize = objectSize - internalHeaderSize();
    compressedFile.resize(compressedFileSize);
    is.read(reinterpret_cast<char *>(compressedFile.data()), compressedFileSize);

    /* skip padding */
    is.seekg(objectSize % 4, std::ios_base::cur);
}

void LogContainer::write(AbstractFile & os)
{
    /* pre processing */
    compressedFileSize = static_cast<DWORD>(compressedFile.size());

    ObjectHeaderBase::write(os);
    os.write(reinterpret_cast<char *>(&unknownCompression), sizeof(unknownCompression));
    os.write(reinterpret_cast<char *>(&reservedLogContainer1), sizeof(reservedLogContainer1));
    os.write(reinterpret_cast<char *>(&reservedLogContainer2), sizeof(reservedLogContainer2));
    os.write(reinterpret_cast<char *>(&uncompressedFileSize), sizeof(uncompressedFileSize));
    os.write(reinterpret_cast<char *>(&reservedLogContainer3), sizeof(reservedLogContainer3));
    os.write(reinterpret_cast<char *>(compressedFile.data()), compressedFileSize);

    /* skip padding */
    os.seekp(objectSize % 4, std::ios_base::cur);
}

DWORD LogContainer::calculateObjectSize() const
{
    return
        internalHeaderSize() +
        static_cast<DWORD>(compressedFile.size());
}

WORD LogContainer::internalHeaderSize() const
{
    return
        ObjectHeaderBase::calculateHeaderSize() +
        sizeof(unknownCompression) +
        sizeof(reservedLogContainer1) +
        sizeof(reservedLogContainer2) +
        sizeof(uncompressedFileSize) +
        sizeof(reservedLogContainer3);
}

}
}
