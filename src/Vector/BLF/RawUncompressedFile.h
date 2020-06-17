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

#include <Vector/BLF/RawFile.h>
#include <Vector/BLF/StructuredCompressedFile.h>
#include <Vector/BLF/Unknown115.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * Raw Uncompressed File
 *
 * This class is thread-safe.
 */
class VECTOR_BLF_EXPORT RawUncompressedFile :
    public RawFile
{
public:
    RawUncompressedFile(StructuredCompressedFile & structuredCompressedFile);
    virtual ~RawUncompressedFile();

    using streamoff = std::streamoff;
    using streamsize = std::streamsize;
    using streampos = std::streampos;

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
    virtual streamsize size() const;

    /**
     * Get file size for FileStatistics::uncompressedFileSize
     *
     * This file size is similar to CompressedFile, but counts LogContainers
     * as they are all uncompressed.
     *
     * @return file size
     */
    virtual streamsize statisticsSize() const;

    /** @copydoc RawCompressedFile::statistics */
    virtual FileStatistics statistics() const;

    /** @copydoc RawCompressedFile::setStatistics */
    virtual void setStatistics(const FileStatistics & statistics);

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
     * get end-of-file object
     *
     * @return end-of-file object
     *
     * @todo see if this is handled right
     */
    virtual Unknown115 unknown115() const;

    /**
     * set end-of-file object
     *
     * @param[in] unknown115 end-of-file object
     *
     * @todo see if this is handled right
     */
    virtual void setUnknown115(const Unknown115 & unknown115);

private:
    /** log container reference */
    struct LogContainerRef {
        /** file position */
        streampos filePosition {0};

        /**
         * file size
         *
         * @secreflist
         * @refitem LogContainer::uncompressedfileSize
         * @endsecreflist
         */
        streamsize fileSize {0};

        /** uncompressed log container */
        std::vector<char> uncompressedFile {};
    };

    /** mutex */
    mutable std::mutex m_mutex {};

    /** structured compress file */
    StructuredCompressedFile & m_structuredCompressedFile;

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
     * as they are all uncompressed.
     */
    streamsize m_statisticsSize {0};

    /** log container references (index is StructuredCompressedFile::streampos) */
    std::vector<LogContainerRef> m_logContainerRefs {};

    /** default log container size */
    DWORD m_defaultLogContainerSize {0x20000};

    /** end-of-file object */
    Unknown115 m_unknown115 {};

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
