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

    /**
     * Current uncompressed file size
     *
     * This includes the LogContainer headers, and the uncompressed content.
     *
     * @todo this need to be a function that returns the fileSize.
     */
    ULONGLONG currentUncompressedFileSize {};

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

    /**
     * open file
     *
     * @param[in] filename file name
     * @param[in] mode open mode, either in (read) or out (write)
     */
    virtual void open(const char * filename, const std::ios_base::openmode mode = std::ios_base::in);

    /**
     * open file
     *
     * @param[in] filename file name
     * @param[in] mode open mode, either in (read) or out (write)
     */
    virtual void open(const std::string & filename, const std::ios_base::openmode mode = std::ios_base::in);

    /**
     * is file open?
     *
     * @return true if file is open
     */
    virtual bool is_open() const;

    /**
     * Read object from file.
     *
     * Ownership is taken over from the library to the user.
     * The user has to take care to delete the object.
     *
     * @todo Use std::unique_ptr in future versions.
     *
     * @return read object or nullptr
     */
    virtual ObjectHeaderBase * read();

    /**
     * Write object to file.
     *
     * Ownership is taken over from the user to the library.
     * The object should not be further accessed any more.
     *
     * @todo Use std::unique_ptr in future versions.
     *
     * @param[in] ohb write object
     * @return true, if write was successful
     */
    virtual bool write(ObjectHeaderBase * ohb);

    /** @copydoc StructuredCompressedfile::close */
    virtual void close();

    /** @copydoc RawCompressedFile::statistics */
    virtual FileStatistics statistics() const;

    /** @copydoc RawCompressedFile::setStatistics */
    virtual void setStatistics(const FileStatistics & statistics);

    /** @copydoc RawUncompressedFile::defaultLogContainerSize */
    virtual DWORD defaultLogContainerSize() const;

    /** @copydoc RawUncompressedFile::setDefaultLogContainerSize */
    virtual void setDefaultLogContainerSize(DWORD defaultLogContainerSize);

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
