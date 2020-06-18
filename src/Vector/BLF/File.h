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
    virtual StructuredUncompressedFile::streamsize read(ObjectHeaderBase ** objectHeaderBase);

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
    virtual StructuredUncompressedFile::streampos tellg();

    /** @copydoc StructuredUncompressedFile::seekg */
    virtual void seekg(const StructuredUncompressedFile::streampos pos);

    /** @copydoc StructuredUncompressedFile::seekg */
    virtual void seekg(const StructuredUncompressedFile::streamoff off, const std::ios_base::seekdir way);

    /** @copydoc StructuredUncompressedFile::write */
    virtual bool write(ObjectHeaderBase * objectHeaderBase);

    /** @copydoc StructuredUncompressedFile::tellp */
    virtual StructuredUncompressedFile::streampos tellp();

    /** @copydoc StructuredUncompressedFile::size */
    virtual StructuredUncompressedFile::streamsize size() const;

    /* RawUncompressedFile methods */

    /** @copydoc RawUncompressedFile::size */
    virtual RawUncompressedFile::streamsize rawUncompressedFileSize() const;

    /** @copydoc RawUncompressedFile::statisticsSize */
    virtual RawUncompressedFile::streamsize rawUncompressedFileStatisticsSize() const;

    /** @copydoc RawUncompressedFile::defaultLogContainerSize */
    virtual DWORD defaultLogContainerSize() const;

    /** @copydoc RawUncompressedFile::setDefaultLogContainerSize */
    virtual void setDefaultLogContainerSize(DWORD defaultLogContainerSize);

    /** @copydoc RawUncompresedFile::compressionMethod */
    virtual int compressionMethod() const;

    /** @copydoc RawUncompresedFile::setCompressionMethod */
    virtual void setCompressionMethod(const int compressionMethod = 2);

    /** @copydoc RawUncompresedFile::compressionLevel */
    virtual int compressionLevel() const;

    /** @copydoc RawUncompresedFile::setCompressionLevel */
    virtual void setCompressionLevel(const int compressionLevel = 6);

    /* StructuredCompressedFile methods */

    /** @copydoc StructuredCompressedFile::size */
    virtual StructuredCompressedFile::streamsize structuredCompressedFileSize() const;

    /* RawCompressedFile methods */

    /** @copydoc RawCompressedFile::size */
    virtual RawCompressedFile::streamsize rawCompressedFileSize() const;

    /** @copydoc RawCompressedFile::statistics */
    virtual FileStatistics statistics() const;

private:
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
