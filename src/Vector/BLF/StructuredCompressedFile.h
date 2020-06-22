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

#include <Vector/BLF/RawCompressedFile.h>
#include <Vector/BLF/StructuredFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * Structured Compressed File
 *
 * The StructuredCompressedFile is the 2. layer in the file architecture.
 *
 * It provides structure-wise access to the objects in RawCompressedFile.
 *
 * This class is thread-safe.
 */
class VECTOR_BLF_EXPORT StructuredCompressedFile :
    public StructuredFile
{
public:
    virtual ~StructuredCompressedFile();

    virtual void open(const char * filename, std::ios_base::openmode mode = std::ios_base::in);
    virtual bool is_open() const;
    virtual void close();
    virtual streamsize read(ObjectHeaderBase ** objectHeaderBase);
    virtual streampos tellg() const;
    virtual void seekg(const streampos pos);
    virtual void seekg(const streamoff off, const std::ios_base::seekdir way);
    virtual streamsize write(ObjectHeaderBase * objectHeaderBase);
    virtual streampos tellp() const;
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
    /** object reference */
    struct ObjectRef {
        /** file position */
        RawCompressedFile::streampos filePosition {0};

        /**
         * object size
         *
         * @see ObjectHeaderBase::objectSize
         */
        DWORD objectSize {0};

        /**
         * object type
         *
         * @see ObjectHeaderBase::objectType
         */
        ObjectType objectType {ObjectType::UNKNOWN};

        // @todo cache object here
    };

    /** mutex */
    mutable std::mutex m_mutex {};

    /** raw compressed file */
    RawCompressedFile m_rawCompressedFile {};

    /** open mode */
    std::ios_base::openmode m_openMode {};

    /** get position */
    streampos m_posg{0};

    /** object references (index is streampos) */
    std::vector<ObjectRef> m_objectRefs {};

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
