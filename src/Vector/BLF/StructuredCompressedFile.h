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
 * This class is thread-safe.
 */
class VECTOR_BLF_EXPORT StructuredCompressedFile {
public:
    StructuredCompressedFile(RawCompressedFile & rawCompressedFile);
    virtual ~StructuredCompressedFile();

    using streamoff = int32_t;
    using streamsize = uint32_t;
    using streampos = uint32_t;

    virtual void open(const char * filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out);
    virtual bool is_open() const;
    virtual void close();
    virtual streamsize read(LogContainer ** logContainer);
    virtual streampos tellg();
    virtual void seekg(const streampos pos);
    virtual void seekg(const streamoff off, const std::ios_base::seekdir way);
    virtual bool write(LogContainer * logContainer);
    virtual streampos tellp();

    /**
     * Get file size
     *
     * @return file size
     */
    virtual streamsize size() const;

    /** @copydoc RawCompressedFile::statistics */
    virtual FileStatistics statistics() const;

    /** @copydoc RawCompressedFile::setStatistics */
    virtual void setStatistics(const FileStatistics & statistics);

private:
    /** log container reference */
    struct LogContainerRef {
        /** file position */
        RawCompressedFile::streampos filePosition {0};

        /** log container */
        std::shared_ptr<LogContainer> logContainer {nullptr};
    };

    /** mutex */
    mutable std::mutex m_mutex {};

    /** raw compressed file */
    RawCompressedFile & m_rawCompressedFile;

    /** open mode */
    std::ios_base::openmode m_openMode {};

    /** get position */
    streampos m_posg{0};

    /** log container references (index is streampos) */
    std::vector<LogContainerRef> m_logContainerRefs {};

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
