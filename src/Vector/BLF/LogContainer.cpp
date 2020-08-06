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

std::vector<uint8_t>::iterator LogContainer::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeaderBase::fromData(it);

    compressionMethod =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedLogContainer1 =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedLogContainer2 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    uncompressedFileSize =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    reservedLogContainer3 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    compressedFile.resize(objectSize - internalHeaderSize());
    std::copy(it, it + compressedFile.size(), std::begin(compressedFile));
    it += objectSize - internalHeaderSize();

    return it;
}

void LogContainer::toData(std::vector<uint8_t> & data) {
    ObjectHeaderBase::toData(data);

    data.push_back((compressionMethod >>  0) & 0xff);
    data.push_back((compressionMethod >>  8) & 0xff);
    data.push_back((reservedLogContainer1 >>  0) & 0xff);
    data.push_back((reservedLogContainer1 >>  8) & 0xff);
    data.push_back((reservedLogContainer2 >>  0) & 0xff);
    data.push_back((reservedLogContainer2 >>  8) & 0xff);
    data.push_back((reservedLogContainer2 >> 16) & 0xff);
    data.push_back((reservedLogContainer2 >> 24) & 0xff);
    data.push_back((uncompressedFileSize >>  0) & 0xff);
    data.push_back((uncompressedFileSize >>  8) & 0xff);
    data.push_back((uncompressedFileSize >> 16) & 0xff);
    data.push_back((uncompressedFileSize >> 24) & 0xff);
    data.push_back((reservedLogContainer3 >>  0) & 0xff);
    data.push_back((reservedLogContainer3 >>  8) & 0xff);
    data.push_back((reservedLogContainer3 >> 16) & 0xff);
    data.push_back((reservedLogContainer3 >> 24) & 0xff);
    data.insert(std::end(data), std::begin(compressedFile), std::end(compressedFile));
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

void LogContainer::uncompress(std::vector<uint8_t> & uncompressedFile) const {
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
                         reinterpret_cast<const Byte *>(compressedFile.data()),
                         static_cast<uLong>(compressedFile.size()));
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

void LogContainer::compress(const std::vector<uint8_t> & uncompressedFile, const WORD compressionMethod, const int compressionLevel) {
    this->compressionMethod = compressionMethod;
    this->uncompressedFileSize = uncompressedFile.size();

    switch (compressionMethod) {
    case 0: /* no compression */
        compressedFile = uncompressedFile;
        break;

    case 2: { /* zlib compress */
        /* deflate/compress data */
        uLong compressedBufferSize = compressBound(uncompressedFileSize);
        compressedFile.resize(compressedBufferSize); // extend
        int retVal = ::compress2(
                         reinterpret_cast<Byte *>(compressedFile.data()),
                         &compressedBufferSize,
                         reinterpret_cast<const Byte *>(uncompressedFile.data()),
                         uncompressedFileSize,
                         compressionLevel);
        if (retVal != Z_OK)
            throw Exception("LogContainer::compress(): compress2 error");
        compressedFile.resize(compressedBufferSize); // shrink_to_fit
    }
    break;

    default:
        throw Exception("LogContainer::compress(): unknown compression method");
    }
}

}
}
