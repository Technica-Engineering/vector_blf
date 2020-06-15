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

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * Raw Compressed File
 *
 * This class is thread-safe.
 */
class VECTOR_BLF_EXPORT RawCompressedFile :
    public RawFile
{
public:
    RawCompressedFile();
    virtual ~RawCompressedFile();

    using streamoff = std::streamoff;
    using streamsize = std::streamsize;
    using streampos = std::streampos;

    void open(const char * filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out) override;
    bool is_open() const override;
    void close() override;
    std::streamsize read(char * s, streamsize n) override;
    streampos tellg() override;
    void seekg(const streampos pos) override;
    void seekg(const streamoff off, const std::ios_base::seekdir way) override;
    std::streamsize write(const char * s, streamsize n) override;
    streampos tellp() override;
    void seekp(const streampos pos) override;
    void seekp(const streamoff off, const std::ios_base::seekdir way) override;

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
     * @todo rename to statistics, omit file?
     * @return file statistics
     */
    virtual FileStatistics fileStatistics() const;

    /**
     * set file statistics
     *
     * @todo rename to setStatistics, omit file?
     * @param[in] fileStatistics file statistics
     */
    virtual void setFileStatistics(const FileStatistics fileStatistics);

private:
    /** mutex */
    mutable std::mutex m_mutex {};

    /** actual file on disk */
    std::fstream m_file;

    /** open mode */
    std::ios_base::openmode m_openMode {};

    /** file statistics */
    FileStatistics m_fileStatistics {};
};

}
}
