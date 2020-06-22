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

#include <fstream>
#include <mutex>

#include <Vector/BLF/FileStatistics.h>
#include <Vector/BLF/RawFile.h>
#include <Vector/BLF/Unknown115.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * Raw Compressed File
 *
 * The RawCompressed File is the 1. layer in the file architecture.
 * It provides nothing more than an abstracted std::fstream. And it handles
 * the FileStatistics.
 *
 * It's raw as it provides byte-wise access to the raw data.
 *
 * This class is thread-safe.
 */
class VECTOR_BLF_EXPORT RawCompressedFile :
    public RawFile
{
public:
    virtual ~RawCompressedFile();

    /** stream offset */
    using streamoff = std::streamoff;

    /** stream size */
    using streamsize = std::streamsize;

    /** stream position */
    using streampos = std::streampos;

    void open(const char * filename, std::ios_base::openmode mode = std::ios_base::in) override;
    bool is_open() const override;
    void close() override;
    streamsize read(char * s, streamsize n) override;
    streampos tellg() override;
    void seekg(const streampos pos) override;
    void seekg(const streamoff off, const std::ios_base::seekdir way) override;
    streamsize write(const char * s, streamsize n) override;
    streampos tellp() override;
    void seekp(const streampos pos) override;
    void seekp(const streamoff off, const std::ios_base::seekdir way) override;
    streamsize size() const override;

    /**
     * Check whether state of stream is good.
     *
     * @return true if no error flags are set
     */
    virtual bool good() const;

    /**
     * Check whether eofbit is set.
     *
     * @return true if eofbit is set
     */
    virtual bool eof() const;

    /**
     * Check whether either failbit or badbit is set.
     *
     * @return true if failbit or badbit is set
     */
    virtual bool fail() const;

    /**
     * Check whether badbit is set.
     *
     * @return true if badbit is set
     */
    virtual bool bad() const;

    /**
     * Get error state flags
     *
     * @return Error state flags
     */
    virtual std::ios_base::iostate rdstate() const;

    /**
     * Set error state flag
     *
     * @param[in] state state
     */
    virtual void setstate(std::ios_base::iostate state);

    /**
     * Set error state flags
     *
     * @param[in] state state
     */
    virtual void clear(std::ios_base::iostate state = std::ios_base::goodbit);

    /**
     * get file statistics
     *
     * @return file statistics
     */
    virtual FileStatistics statistics() const;

    /**
     * Set application in file statistics.
     *
     * @param[in] id application ID (usually CANoe)
     * @param[in] major application major number (usually 0)
     * @param[in] minor application minor number (usually 0)
     * @param[in] build application build number (usually 0)
     */
    virtual void setApplication(const BYTE id, const BYTE major = 0, const BYTE minor = 0, const BYTE build = 0);

    /**
     * Set BL API in file statistics.
     *
     * @param[in] major BL API major number
     * @param[in] minor BL API minor number
     * @param[in] build BL API build number
     * @param[in] patch BL API patch number
     */
    virtual void setApi(const BYTE major, const BYTE minor, const BYTE build, const BYTE patch);

    /**
     * Set (compressed) file size in file statistics.
     *
     * @param[in] fileSize (compressed) file size in bytes
     */
    virtual void setFileSize(const ULONGLONG fileSize);

    /**
     * Set uncompressed file size in file statistics.
     *
     * @param[in] uncompressedFileSize uncompressed file size in bytes
     */
    virtual void setUncompressedFileSize(const ULONGLONG uncompressedFileSize);

    /**
     * Set number of objects in file statistics.
     *
     * @param[in] objectCount number of objects
     */
    virtual void setObjectCount(const DWORD objectCount);

    /**
     * Set number of objects read in file statistics.
     *
     * @param[in] objectsRead number of objects read
     */
    virtual void setObjectsRead(const DWORD objectsRead);

    /**
     * Set measurement start time in file statistics.
     *
     * @param[in] measurementStartTime measurement start time
     */
    virtual void setMeasurementStartTime(const SYSTEMTIME measurementStartTime);

    /**
     * Set last object time in file statistics.
     *
     * @param[in] lastObjectTime last object time
     */
    virtual void setLastObjectTime(const SYSTEMTIME lastObjectTime);

private:
    /** mutex */
    mutable std::mutex m_mutex {};

    /** actual file on disk */
    std::fstream m_file {};

    /** open mode */
    std::ios_base::openmode m_openMode {};

    /** file size */
    streamsize m_size {0};

    /** file statistics */
    FileStatistics m_statistics {};
};

}
}
