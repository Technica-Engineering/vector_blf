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
     * File statistics from file header. contains total counts/sizes
     */
    FileStatistics fileStatistics {};

    /**
     * Current uncompressed file size
     *
     * This includes the LogContainer headers, and the uncompressed content.
     */
    ULONGLONG currentUncompressedFileSize {};

    /**
     * zlib compression level (0=no compression, 1=best speed, 9=best compression, -1=default compression
     */
    int compressionLevel {6};

    /**
     * Write Unknown115 message at file close
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
     * Check whether state of stream is good.
     *
     * @return true if no error flags set
     */
    virtual bool good() const;

    /**
     * Check whether eofbit is set.
     *
     * @return true if end-of-file reached
     */
    virtual bool eof() const;

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
     */
    virtual void write(ObjectHeaderBase * ohb);

    /**
     * close file
     */
    virtual void close();

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

  private:
    /** raw compressed file */
    RawCompressedFile m_rawCompressedFile;

    /** structured compressed file */
    StructuredCompressedFile m_structuredCompressedFile;

    /** raw uncompressed file */
    RawUncompressedFile m_rawUncompressedFile;

    /** structured uncompressed file */
    StructuredUncompressedFile m_structuredUncompressedFile;

    /**
     * Open mode
     */
    std::ios_base::openmode m_openMode {};

    /* compressed file */

    /**
     * thread between uncompressedFile and compressedFile
     */
    std::thread m_compressedFileThread {};

    /**
     * thread still running
     */
    std::atomic<bool> m_compressedFileThreadRunning {};

    /* uncompressed file */

    /**
     * thread between readWriteQueue and uncompressedFile
     */
    std::thread m_uncompressedFileThread {};

    /**
     * thread still running
     */
    std::atomic<bool> m_uncompressedFileThreadRunning {};

    /* internal functions */

    /**
     * Read/inflate/uncompress data from compressedFile into uncompressedFile.
     */
    void compressedFile2UncompressedFile();

    /**
     * Write/deflate/compress data from uncompressedFile into compressedFile.
     */
    void uncompressedFile2CompressedFile();

    /**
     * transfer data from uncompressedFile to readWriteQueue
     */
    static void uncompressedFileReadThread(File * file);

    /**
     * transfer data from readWriteQueue to uncompressedfile
     */
    static void uncompressedFileWriteThread(File * file);

    /**
     * transfer data from compressedFile to uncompressedFile
     */
    static void compressedFileReadThread(File * file);

    /**
     * transfer data from uncompressedfile to compressedFile
     */
    static void compressedFileWriteThread(File * file);
};

}
}
