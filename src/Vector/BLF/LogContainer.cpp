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

#include <Vector/BLF/LogContainer.h>

#include <zlib.h>

#include <Vector/BLF/Exceptions.h>

namespace Vector {
namespace BLF {

LogContainer::LogContainer() :
    ObjectHeaderBase(1, ObjectType::LOG_CONTAINER) {
}

void LogContainer::read(AbstractFile & is) {
    ObjectHeaderBase::read(is);
    is.read(reinterpret_cast<char *>(&compressionMethod), sizeof(compressionMethod));
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

void LogContainer::write(AbstractFile & os) {
    /* pre processing */
    compressedFileSize = static_cast<DWORD>(compressedFile.size());

    ObjectHeaderBase::write(os);
    os.write(reinterpret_cast<char *>(&compressionMethod), sizeof(compressionMethod));
    os.write(reinterpret_cast<char *>(&reservedLogContainer1), sizeof(reservedLogContainer1));
    os.write(reinterpret_cast<char *>(&reservedLogContainer2), sizeof(reservedLogContainer2));
    os.write(reinterpret_cast<char *>(&uncompressedFileSize), sizeof(uncompressedFileSize));
    os.write(reinterpret_cast<char *>(&reservedLogContainer3), sizeof(reservedLogContainer3));
    os.write(reinterpret_cast<char *>(compressedFile.data()), compressedFileSize);

    /* skip padding */
    os.skipp(objectSize % 4);
}

DWORD LogContainer::calculateObjectSize() const {
    return
        internalHeaderSize() +
        static_cast<DWORD>(compressedFile.size());
}

WORD LogContainer::internalHeaderSize() const {
    return
        ObjectHeaderBase::calculateHeaderSize() +
        sizeof(compressionMethod) +
        sizeof(reservedLogContainer1) +
        sizeof(reservedLogContainer2) +
        sizeof(uncompressedFileSize) +
        sizeof(reservedLogContainer3);
}

void LogContainer::uncompress() {
    switch (compressionMethod) {
    case 0: /* no compression */
        uncompressedFile = compressedFile;
        break;

    case 2: { /* zlib compress */
        /* create buffer */
        uLong size = static_cast<uLong>(uncompressedFileSize);
        uncompressedFile.resize(size);

        /* inflate */
        int retVal = ::uncompress(
                         reinterpret_cast<Byte *>(uncompressedFile.data()),
                         &size,
                         reinterpret_cast<Byte *>(compressedFile.data()),
                         static_cast<uLong>(compressedFileSize));
        if (size != uncompressedFileSize)
            throw Exception("LogContainer::uncompress(): unexpected uncompressedSize");
        if (retVal != Z_OK)
            throw Exception("LogContainer::uncompress(): uncompress error");
    }
    break;

    default:
        throw Exception("LogContainer::uncompress(): unknown compression method");
    }
}

void LogContainer::compress(const WORD compressionMethod, const int compressionLevel) {
    this->compressionMethod = compressionMethod;

    switch (compressionMethod) {
    case 0: /* no compression */
        compressedFile = uncompressedFile;
        compressedFileSize = uncompressedFileSize;
        break;

    case 2: { /* zlib compress */
        /* deflate/compress data */
        uLong compressedBufferSize = compressBound(uncompressedFileSize);
        compressedFile.resize(compressedBufferSize); // extend
        int retVal = ::compress2(
                         reinterpret_cast<Byte *>(compressedFile.data()),
                         &compressedBufferSize,
                         reinterpret_cast<Byte *>(uncompressedFile.data()),
                         uncompressedFileSize,
                         compressionLevel);
        if (retVal != Z_OK)
            throw Exception("File::uncompressedFile2CompressedFile(): compress2 error");
        compressedFileSize = static_cast<DWORD>(compressedBufferSize);
        compressedFile.resize(compressedFileSize); // shrink
    }
    break;

    default:
        throw Exception("LogContainer::compress(): unknown compression method");
    }
}

}
}
