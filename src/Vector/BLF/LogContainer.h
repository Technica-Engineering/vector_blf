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

#pragma once

#include <Vector/BLF/platform.h>

#include <vector>

#include <Vector/BLF/ObjectHeaderBase.h>
#include <Vector/BLF/RawFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief LOG_CONTAINER
 */
struct VECTOR_BLF_EXPORT LogContainer final : ObjectHeaderBase {
    LogContainer();

    std::vector<uint8_t>::iterator fromData(std::vector<uint8_t>::iterator it) override;
    void toData(std::vector<uint8_t> & data) override;
    DWORD calculateObjectSize() const override;

    /**
     * compression method
     *
     *   - 0: no compression
     *   - 2: zlib deflate
     */
    WORD compressionMethod {};

    /**
     * reserved
     */
    WORD reservedLogContainer1 {};

    /**
     * reserved
     */
    DWORD reservedLogContainer2 {};

    /**
     * uncompressed file size in bytes
     */
    DWORD uncompressedFileSize {};

    /** reserved */
    DWORD reservedLogContainer3 {}; // @todo what is this? 0x0215, 0x9a, 0, 0x0c...

    /** compressed file content */
    std::vector<char> compressedFile {};

    /* following data is calculated */

    /** compressed file size in bytes */
    DWORD compressedFileSize {};

    /**
     * internalHeaderSize returns the size of all headers.
     *
     * @note Not to be mixed with headerSize, which only takes ObjectHeaderBase headers into account.
     *
     * @return Size of all headers.
     */
    WORD internalHeaderSize() const;

    /**
     * read LogContainer without File
     *
     * @param[in] is raw file
     */
    virtual void readWithoutFile(RawFile & is);

    /**
     * uncompress data
     *
     * @param[out] uncompressedFile uncompressed data
     */
    virtual void uncompress(std::vector<char> & uncompressedFile) const;

    /**
     * compress data
     *
     * @param[in] uncompressedFile compressed data
     * @param[in] compressionMethod compression method
     * @param[in] compressionLevel compression level (different for each method)
     */
    virtual void compress(const std::vector<char> & uncompressedFile, const WORD compressionMethod = 2, const int compressionLevel = 6);
};

}
}
