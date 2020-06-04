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

#include <condition_variable>
#include <limits>

#include <Vector/BLF/RawFile.h>
#include <Vector/BLF/StructuredCompressedFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * This class allows byte-wise access to the uncompressed file.
 */
class VECTOR_BLF_EXPORT RawUncompressedFile :
    public RawFile
{
public:
    RawUncompressedFile(StructuredCompressedFile & structuredCompressedFile);

    void open(const char * filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out) override;
    bool is_open() const override;
    void close() override;
    bool good() const override;
    bool eof() const override;
    std::streamsize gcount() const override;
    void read(char * s, std::streamsize n) override;
    std::streampos tellg() override;
    void seekg(const std::streampos pos) override;
    void seekg(const std::streamoff off, const std::ios_base::seekdir way) override;
    void write(const char * s, std::streamsize n) override;
    std::streampos tellp() override;
    void seekp(const std::streampos pos) override;
    void seekp(const std::streamoff off, const std::ios_base::seekdir way) override;

    /**
     * Stop further operations. Return from waiting reads.
     */
    virtual void abort();

    /**
     * write LogContainer
     *
     * @param[in] logContainer log container
     */
    virtual void write(const std::shared_ptr<LogContainer> & logContainer);

    /**
     * Close the current logContainer.
     */
    virtual void nextLogContainer();

    /**
     * Return current file size resp. end-of-file position.
     *
     * @return file size
     */
    virtual std::streamsize fileSize() const;

    /**
     * Set file size resp. end-of-file position.
     *
     * @param[in] fileSize file size
     */
    virtual void setFileSize(std::streamsize fileSize);

    /**
     * Sets the maximum file size.
     * Write operations block, if the size is reached.
     *
     * @param[in] bufferSize maximum file size
     */
    virtual void setBufferSize(std::streamsize bufferSize);

    /**
     * drop old log container, if tellg/tellp are beyond it
     */
    virtual void dropOldData();

    /** file size */
    std::streamsize m_fileSize {std::numeric_limits<std::streamsize>::max()};

    /** buffer size */
    std::streamsize m_bufferSize {std::numeric_limits<std::streamsize>::max()};

    /** error state */
    std::ios_base::iostate m_rdstate {std::ios_base::goodbit};

    /** last read size */
    std::streamsize m_gcount {};

    /** get position */
    std::streampos m_tellg {}; // @todo rename to m_gpos

    /** tellg was changed (after read or seekg) */
    std::condition_variable tellgChanged;

    /** put position */
    std::streampos m_tellp {}; // @todo rename to m_ppos

    /** tellp was changed (after write or seekp) */
    std::condition_variable tellpChanged;

    /** abort further operations */
    bool m_abort {};

private:
    /** structured compress file */
    StructuredCompressedFile & m_structuredCompressedFile;

    /** mutex */
    std::mutex & m_mutex;
};

}
}
