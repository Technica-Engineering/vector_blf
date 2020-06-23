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

#include <map>

#include <Vector/BLF/RawFile.h>
#include <Vector/BLF/StructuredCompressedFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * Raw Uncompressed File
 *
 * The RawUncompressedFile is the 3. layer in the file architecture.
 *
 * When the data in the LogContainers is uncompressed, it builds up another
 * file stream. The RawUncompressedFile provides byte-wise access to it.
 *
 * This class is thread-safe.
 */
class VECTOR_BLF_EXPORT RawUncompressedFile :
    public RawFile
{
public:
    virtual ~RawUncompressedFile();

    void open(const char * filename, std::ios_base::openmode mode = std::ios_base::in) override;
    bool is_open() const override;
    void close() override;
    streamsize read(char * s, const streamsize n) override;
    streampos tellg() override;
    void seekg(const streampos pos) override;
    void seekg(const streamoff off, const std::ios_base::seekdir way) override;
    streamsize write(const char * s, const streamsize n) override;
    streampos tellp() override;
    void seekp(const streampos pos) override;
    void seekp(const streamoff off, const std::ios_base::seekdir way) override;
    streamsize size() const override;

    /**
     * Get file size for FileStatistics::uncompressedFileSize
     *
     * This file size is similar to CompressedFile, but counts LogContainers
     * as they are all uncompressed.
     *
     * @note FileStatistics::statisticsSize is not included here.
     *
     * @return file size
     */
    virtual streamsize statisticsSize() const;

    /**
     * Get default log container size.
     *
     * @return default log container size
     */
    virtual DWORD defaultLogContainerSize() const;

    /**
     * Set default log container size.
     *
     * @param[in] defaultLogContainerSize default log container size
     */
    virtual void setDefaultLogContainerSize(DWORD defaultLogContainerSize);

    /**
     * get compression method
     *
     *   - 0: no compression
     *   - 2: zlib deflate
     *
     * @return compression method
     */
    virtual int compressionMethod() const;

    /**
     * set compression method
     *
     *   - 0: no compression
     *   - 2: zlib deflate
     *
     * @param[in] compressionMethod compression method
     */
    virtual void setCompressionMethod(const int compressionMethod = 2);

    /**
     * get compression level
     *
     * zlib compression level:
     *
     *   - -1: default compression
     *   - 0: no compression
     *   - 1: best speed
     *   - 6: Vector BLF default
     *   - 9: best compression
     *   - 10: maximum compression
     *
     * @return compression level
     */
    virtual int compressionLevel() const;

    /**
     * set compression level
     *
     * zlib compression level:
     *
     *   - -1: default compression
     *   - 0: no compression
     *   - 1: best speed
     *   - 6: Vector BLF default
     *   - 9: best compression
     *   - 10: maximum compression
     *
     * @param[in] compressionLevel compression level
     */
    virtual void setCompressionLevel(const int compressionLevel = 6);

    /**
     * Finish the current log container by shrinking it to fit content,
     * compress and write it.
     */
    virtual void finishLogContainer();

    /* StructuredCompressedFile pass-thru methods */

    /** @copydoc StructuredCompressedFile::size() */
    virtual StructuredCompressedFile::indexsize structuredCompressedFileSize() const;

    /* RawCompressedFile pass-thru methods */

    /** @copydoc RawCompressedFile::size() */
    virtual RawCompressedFile::streamsize rawCompressedFileSize() const;

    /** @copydoc RawCompressedFile::statistics() */
    virtual FileStatistics statistics() const;

    /** @copydoc RawCompressedFile::setApplication() */
    virtual void setApplication(const BYTE id, const BYTE major = 0, const BYTE minor = 0, const BYTE build = 0);

    /** @copydoc RawCompressedFile::setApi() */
    virtual void setApi(const BYTE major, const BYTE minor, const BYTE build, const BYTE patch);

    /** @copydoc RawCompressedFile::setObjectCount() */
    virtual void setObjectCount(const DWORD objectCount);

    /** @copydoc RawCompressedFile::setObjectsRead() */
    virtual void setObjectsRead(const DWORD objectsRead);

    /** @copydoc RawCompressedFile::setMeasurementStartTime() */
    virtual void setMeasurementStartTime(const SYSTEMTIME measurementStartTime);

    /** @copydoc RawCompressedFile::setLastObjectTime() */
    virtual void setLastObjectTime(const SYSTEMTIME lastObjectTime);

private:
    /** object reference */
    struct ObjectRef {
        /**
         * file size
         *
         * @see LogContainer::uncompressedfileSize
         */
        streamsize fileSize {0};

        /** uncompressed log container */
        std::vector<char> uncompressedFile {};
    };

    /** mutex */
    mutable std::mutex m_mutex {};

    /** structured compress file */
    StructuredCompressedFile m_structuredCompressedFile {};

    /** open mode */
    std::ios_base::openmode m_openMode {};

    /** get position */
    streampos m_posg {0};

    /** put position */
    streampos m_posp {0};

    /** file size */
    streamsize m_size {0};

    /**
     * file size for FileStatistics::uncompressedFileSize
     *
     * This file size is similar to CompressedFile, but counts LogContainers
     * as they are would all be uncompressed.
     */
    streamsize m_statisticsSize {0};

    /** object references (key: streampos) */
    std::map<streampos, ObjectRef> m_objectRefs {};

    /** default log container size */
    DWORD m_defaultLogContainerSize {0x20000};

    /** @copydoc LogContainer::compressionMethod() */
    int m_compressionMethod {2};

    /**
     * zlib compression level (0=no compression, 1=best speed, 9=best compression, -1=default compression
     */
    int m_compressionLevel {6};

    /**
     * Shrink current log container to fit content.
     */
    void shrinkLogContainer();

    /**
     * Compress and write current log container.
     */
    void writeLogContainer();

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
