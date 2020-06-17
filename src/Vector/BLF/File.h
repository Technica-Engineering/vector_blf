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

#include <atomic>
#include <thread>

#include <Vector/BLF/FileStatistics.h>
#include <Vector/BLF/ObjectHeaderBase.h>
#include <Vector/BLF/RawCompressedFile.h>
#include <Vector/BLF/RawUncompressedFile.h>
#include <Vector/BLF/StructuredCompressedFile.h>
#include <Vector/BLF/StructuredUncompressedFile.h>
#include <Vector/BLF/VectorTypes.h>


#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * File
 */
class VECTOR_BLF_EXPORT File final {
public:
    File();
    virtual ~File();

    using streamoff = int32_t;
    using streamsize = uint32_t;
    using streampos = uint32_t;

    /**
     * zlib compression level (0=no compression, 1=best speed, 9=best compression, -1=default compression
     *
     * @todo shift to where compression happens and just provide a proxy function here
     */
    int compressionLevel {6};

    /**
     * Write Unknown115 message at file close
     *
     * @todo always write
     */
    bool writeUnknown115 {true};

    /* StructuredUncompressedFile methods */

    /** @copydoc StructuredUncompressedFile::open */
    virtual void open(const char * filename, const std::ios_base::openmode mode = std::ios_base::in);

    /**
     * open file
     *
     * @param[in] filename file name
     * @param[in] mode open mode, either in (read) or out (write)
     */
    virtual void open(const std::string & filename, const std::ios_base::openmode mode = std::ios_base::in);

    /** @copydoc StructuredUncompressedFile::is_open */
    virtual bool is_open() const;

    /** @copydoc StructuredUncompressedfile::close */
    virtual void close();

    /** @copydoc StructuredUncompressedfile::read */
    virtual streamsize read(ObjectHeaderBase ** objectHeaderBase);

    /**
     * Read object from file.
     *
     * Ownership is taken over from the library to the user.
     * The user has to take care to delete the object.
     *
     * @return read object or nullptr
     *
     * @deprecated Use new read method instead.
     */
    virtual ObjectHeaderBase * read();

    /** @copydoc StructuredUncompressedFile::tellg */
    virtual streampos tellg();

    /** @copydoc StructuredUncompressedFile::seekg */
    virtual void seekg(const streampos pos);

    /** @copydoc StructuredUncompressedFile::seekg */
    virtual void seekg(const streamoff off, const std::ios_base::seekdir way);

    /** @copydoc StructuredUncompressedFile::write */
    virtual bool write(ObjectHeaderBase * objectHeaderBase);

    /** @copydoc StructuredUncompressedFile::tellp */
    virtual streampos tellp();

    /* RawUncompressedFile methods */

    /** @copydoc RawUncompressedFile::defaultLogContainerSize */
    virtual DWORD defaultLogContainerSize() const;

    /** @copydoc RawUncompressedFile::setDefaultLogContainerSize */
    virtual void setDefaultLogContainerSize(DWORD defaultLogContainerSize);

    /* StructuredCompressedFile methods */

    /* RawCompressedFile methods */

    /** @copydoc RawCompressedFile::statistics */
    virtual FileStatistics statistics() const;

// @todo private:
    /** raw compressed file */
    RawCompressedFile m_rawCompressedFile;

    /** structured compressed file */
    StructuredCompressedFile m_structuredCompressedFile;

    /** raw uncompressed file */
    RawUncompressedFile m_rawUncompressedFile;

    /** structured uncompressed file */
    StructuredUncompressedFile m_structuredUncompressedFile;
};

}
}
