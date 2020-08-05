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

#include <cstdint>
#include <fstream>
#include <map>
#include <mutex>
#include <vector>

#include <Vector/BLF/FileStatistics.h>
#include <Vector/BLF/ObjectHeaderBase.h>
#include <Vector/BLF/ObjectType.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * File
 *
 * This class is thread-safe.
 */
class VECTOR_BLF_EXPORT File final
{
public:
    virtual ~File();

    /* general methods */

    /**
     * open file
     *
     * @param[in] filename file name
     * @param[in] mode open in read or write mode
     */
    virtual void open(const char * filename, std::ios_base::openmode mode = std::ios_base::in);

    /**
     * is file open?
     *
     * @return true if file is open
     */
    virtual bool is_open() const;

    /** Close file. */
    virtual void close();

    /**
     * Get compressed file size.
     *
     * @return compressed file size
     */
    virtual std::streamsize compressedSize();

    /**
     * Get uncompressed file size.
     *
     * @return uncompressed file size
     */
    virtual std::streamsize uncompressedSize() const;

    /**
     * Get default log container size.
     *
     * @return Default log container size
     */
    virtual DWORD defaultLogContainerSize() const;

    /**
     * Set default log container size.
     *
     * @param[in] size default log container size
     */
    virtual void setDefaultLogContainerSize(DWORD size = 0x20000);

    /**
     * Get compression method.
     *
     * @return compression method
     */
    virtual WORD compressionMethod() const;

    /**
     * Set compression method.
     *
     * @param[in] compressionMethod compression method
     */
    virtual void setCompressionMethod(const WORD compressionMethod);

    /**
     * Get compression level.
     *
     * @return compression level
     */
    virtual int compressionLevel() const;

    /**
     * Set compression level.
     *
     * @param[in] compressionLevel compression level
     */
    virtual void setCompressionLevel(const int compressionLevel);

    /* input methods */

    /**
     * Read block of data.
     *
     * This operation blocks until the data is available.
     *
     * @param[out] s Pointer to data
     * @param[in] n Requested size of data
     * @return Size of data read
     */
    virtual std::streamsize read(uint8_t * s, const std::streamsize n);

    /**
     * Get position in input sequence.
     *
     * @return Read position
     */
    virtual std::streampos tellg();

    /**
     * Set position in input sequence.
     *
     * @param[in] pos Position
     */
    virtual void seekg(const std::streampos pos);

    /**
     * Set position in input sequence.
     *
     * @param[in] off Offset
     * @param[in] way Direction
     */
    virtual void seekg(const std::streamoff off, const std::ios_base::seekdir way);

    /**
     * Convenience function to read one object.
     *
     * @return Object
     *
     * @note Data ownership is passed on from File class to client.
     */
    virtual ObjectHeaderBase * read();

    /* output methods */

    /**
     * Write block of data.
     *
     * @param[in] s Pointer to data
     * @param[in] n Size of data
     * @return Size of data written
     */
    virtual std::streamsize write(uint8_t * s, const std::streamsize n);

    /**
     * Get position in output sequence.
     *
     * @return Write position
     */
    virtual std::streampos tellp();

    /**
     * Convenience function to write one object.
     *
     * @param[in] ohb Object (ownership is passed)
     *
     * @note Data ownership is passed on from client to File class.
     */
    virtual void write(ObjectHeaderBase * ohb);

private:
    /** mutex */
    mutable std::mutex m_mutex {};

    /** actual compressed file on disk */
    std::fstream m_file {};

    /** open mode */
    std::ios_base::openmode m_openMode {};

    /** file statistics */
    FileStatistics m_fileStatistics {};

    /* compressed file */

    /** size of compressed file */
    std::streamsize m_compressedFileSize {0}; // @todo use m_fileStatistics instead

    /** get position of compressed file */
    std::streampos m_compressedFileGetPosition {0};

    /** put position of compressed file */
    std::streampos m_compressedFilePutPosition {0};

    /** index entry */
    struct IndexEntry {
        /** uncompressed file position */
        std::streampos uncompressedFilePosition {0};

        /**
         * compressed object size
         *
         * @see ObjectHeaderBase::objectSize
         */
        DWORD compressedObjectSize {0};

        /**
         * object type
         *
         * for FileStatistics this is set to UNKNOWN
         *
         * @see ObjectHeaderBase::objectType
         */
        ObjectType objectType {};

        /**
         * uncompressed object size
         *
         * This is used to correctly size the data in cache.
         *
         * @see LogContainers::uncompressedFileSize
         */
        DWORD uncompressedObjectSize {0};
    };

    /** maps compressedFilePos to uncompressedFilePos */
    std::map<std::streampos, IndexEntry> m_index {};

    /* uncompressed file */

    /** size of uncompressed file */
    std::streamsize m_uncompressedFileSize {0}; // @todo use m_fileStatistics instead

    /** get position within uncompressed file */
    std::streampos m_uncompressedFileGetPosition {0};

    /** put position within uncompressed file */
    std::streampos m_uncompressedFilePutPosition {0};

    /**
     * uncompressed file data (cache)
     *
     * maps uncompressedFilePos to cached data
     *
     * On read this usually contains the current and following uncompressed
     * LogContainer data, until it's dropped.
     *
     * On write this usually contains the previous and current uncompressed
     * LogContainer data, unitl it's written/flashed.
     *
     * FileStatistics are usually not cached, as only during open/close, access
     * is needed.
     */
    std::map<std::streampos, std::vector<uint8_t>> m_uncompressedFileData {};

    /** default log container size */
    DWORD m_defaultLogContainerSize {0x20000};

    /** compression method */
    WORD m_compressionMethod {2};

    /** compression level */
    int m_compressionLevel {6};

    /**
     * index
     *
     * Scans the file to find FileStatistic, LogContainers and other Objects.
     */
    void indexCompressed();

    /**
     * Calculates padding for a given objectType and objectSize.
     *
     * @param[in] objectType object type
     * @param[in] objectSize object size
     * @return padding
     */
    DWORD padding(const ObjectType objectType, const DWORD objectSize) const;

    /**
     * get compressedFilePosition that contains uncompressedFilePosition
     *
     * @param[in] uncompressedFilePos uncompressed file position
     * @return compressed file position
     */
    std::streampos compressedFilePositionContaining(std::streampos uncompressedFilePos) const;

    /**
     * Set position in output sequence.
     *
     * @note seekp writes zeros if it goes beyond eof.
     *
     * @param[in] off Offset
     * @param[in] way Direction
     */
    void seekpCompressed(const std::streamoff off, const std::ios_base::seekdir way);

    /**
     * drop data that was already read and is not needed any more.
     */
    void dropOldData();

    /**
     * write old data
     */
    void writeOldData();

    /**
     * flush data
     */
    void flushOldData();
};

}
}
