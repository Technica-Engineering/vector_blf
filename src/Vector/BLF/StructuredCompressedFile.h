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

#include <memory>
#include <mutex>
#include <vector>

#include <Vector/BLF/LogContainer.h>
#include <Vector/BLF/RawCompressedFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * Structured Compressed File
 *
 * The StructuredCompressedFile is the 2. layer in the file architecture.
 *
 * It's structured as it provides structure-wise access to the data.
 *
 * The structures on this level are LogContainers.
 *
 * This class is thread-safe.
 */
class VECTOR_BLF_EXPORT StructuredCompressedFile {
public:
    virtual ~StructuredCompressedFile();

    /** stream offset */
    using streamoff = int32_t;

    /** stream size */
    using streamsize = uint32_t;

    /** stream position */
    using streampos = uint32_t;

    /** @copydoc RawFile::open() */
    virtual void open(const char * filename, std::ios_base::openmode mode = std::ios_base::in);

    /** @copydoc RawFile::is_open() */
    virtual bool is_open() const;

    /** @copydoc RawFile::close() */
    virtual void close();

    /**
     * Read log container.
     *
     * This operation blocks until the log container is available.
     *
     * @param[out] logContainer log container
     * @return Number of log containers read (0 or 1)
     */
    virtual streamsize read(LogContainer ** logContainer);

    /** @copydoc RawFile::tellg() */
    virtual streampos tellg() const;

    /** @copydoc RawFile::seekg(std::streampos) */
    virtual void seekg(const streampos pos);

    /** @copydoc RawFile::seekg(std::streamoff, std::ios_base::seekdir) */
    virtual void seekg(const streamoff off, const std::ios_base::seekdir way);

    /**
     * Write log container.
     *
     * @param[in] logContainer log container
     * @return Number of log containers written (0 or 1)
     */
    virtual streamsize write(LogContainer * logContainer);

    /** @copydoc RawFile::tellp() */
    virtual streampos tellp() const;

    /** @copydoc RawFile::size() */
    virtual streamsize size() const;

    /* RawCompressedFile pass-thru methods */

    /** @copydoc RawCompressedFile::size() */
    virtual RawCompressedFile::streamsize rawCompressedFileSize() const;

    /** @copydoc RawCompressedFile::statistics() */
    virtual FileStatistics statistics() const;

    /** @copydoc RawCompressedFile::setApplication() */
    virtual void setApplication(const BYTE id, const BYTE major = 0, const BYTE minor = 0, const BYTE build = 0);

    /** @copydoc RawCompressedFile::setApi() */
    virtual void setApi(const BYTE major, const BYTE minor, const BYTE build, const BYTE patch);

    /** @copydoc RawCompressedFile::setUncompressedFileSize() */
    virtual void setUncompressedFileSize(const ULONGLONG uncompressedFileSize);

    /** @copydoc RawCompressedFile::setObjectCount() */
    virtual void setObjectCount(const DWORD objectCount);

    /** @copydoc RawCompressedFile::setObjectsRead() */
    virtual void setObjectsRead(const DWORD objectsRead);

    /** @copydoc RawCompressedFile::setMeasurementStartTime() */
    virtual void setMeasurementStartTime(const SYSTEMTIME measurementStartTime);

    /** @copydoc RawCompressedFile::setLastObjectTime() */
    virtual void setLastObjectTime(const SYSTEMTIME lastObjectTime);

private:
    /** log container reference */
    struct LogContainerRef {
        /** file position */
        RawCompressedFile::streampos filePosition {0};

        // @todo cache logContainer here
    };

    /** mutex */
    mutable std::mutex m_mutex {};

    /** raw compressed file */
    RawCompressedFile m_rawCompressedFile {};

    /** open mode */
    std::ios_base::openmode m_openMode {};

    /** get position */
    streampos m_posg{0};

    /** log container references (index is streampos) */
    std::vector<LogContainerRef> m_logContainerRefs {};

    /* threads */

    /**
     * index thread
     *
     * When opening file for reading, the thread scans the file to find all
     * LogContainers.
     */
    void indexThread();

    /**
     * read thread
     *
     * This reads ahead the next LogContainers.
     */
    void readThread();

    /**
     * write thread
     *
     * This writes LogContainers.
     */
    void writeThread();
};

}
}
