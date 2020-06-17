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

#include <Vector/BLF/ObjectHeaderBase.h>
#include <Vector/BLF/RawUncompressedFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * Structured Uncompressed File
 *
 * This class is thread-safe.
 */
class VECTOR_BLF_EXPORT StructuredUncompressedFile {
public:
    StructuredUncompressedFile(RawUncompressedFile & rawUncompressedFile);
    ~StructuredUncompressedFile();

    using streamoff = int32_t;
    using streamsize = uint32_t;
    using streampos = uint32_t;

    virtual void open(const char * filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out);
    virtual bool is_open() const;
    virtual void close();
    virtual ObjectHeaderBase * read();
    virtual streampos tellg();
    virtual void seekg(const streampos pos);
    virtual void seekg(const streamoff off, const std::ios_base::seekdir way);
    virtual bool write(ObjectHeaderBase * objectHeaderBase);
    virtual streampos tellp();

    /**
     * Get file size
     *
     * @return file size
     */
    virtual streamsize size() const;

    /**
     * Current number of objects read
     *
     * Unknown115 is not counted.
     *
     * @todo isn't this the file size?
     *
     * @secreflist
     * @refitem FileStatistics::objectCount
     * @endsecreflist
     */
    //std::atomic<DWORD> currentObjectCount {};

private:
    /** object reference */
    struct ObjectRef {
        /** file position */
        RawUncompressedFile::streampos filePosition {0};

        /**
         * object size
         *
         * @secreflist
         * @refitem ObjectHeaderBase::objectSize
         * @endsecreflist
         */
        DWORD objectSize {0};

        /**
         * object type
         *
         * @secreflist
         * @refitem ObjectHeaderBase::objectType
         * @endsecreflist
         */
        ObjectType objectType {ObjectType::UNKNOWN};

        /** object */
        std::shared_ptr<ObjectHeaderBase> object {nullptr};
    };

    /** mutex */
    mutable std::mutex m_mutex {};

    /** raw uncompressed file */
    RawUncompressedFile & m_rawUncompressedFile;

    /** open mode */
    std::ios_base::openmode m_openMode {};

    /** get position */
    streampos m_posg{0};

    /** object references (index is streampos) */
    std::vector<ObjectRef> m_objectRefs {};

    /**
     * index thread
     *
     * When opening file for reading, the thread scans the file to find all
     * objects.
     */
    void indexThread();

    /**
     * read thread
     *
     * This reads ahead the next objects.
     */
    void readThread();

    /**
     * write thread
     *
     * This writes objects.
     */
    void writeThread();
};

}
}
