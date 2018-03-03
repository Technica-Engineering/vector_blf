/*
 * Copyright (C) 2013 Tobias Lorenz.
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
#include <list>
#include <mutex>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/LogContainer.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * UncompressedFile (Input/output memory stream)
 *
 * This class is like a virtual file buffer. It only sees
 * the fragments that are contained in m_data and addresses
 * by the underlying uncompressed LogContainers.
 * Read is done at position m_tellg and write position is at m_tellp.
 * Write or seek operations exceeding the end of the file, will
 * automatically create new logContainers. An explicit dropOldData
 * drops logContainers that have already been processed.
 *
 * This class is thread-safe.
 */
class VECTOR_BLF_EXPORT UncompressedFile final : public AbstractFile
{
public:
    UncompressedFile();
    ~UncompressedFile();

    virtual void close() override;
    virtual std::streamsize gcount() const override;
    virtual void read(char * s, std::streamsize n) override;
    virtual std::streampos tellg() override;
    virtual void seekg(std::streamoff off, const std::ios_base::seekdir way  = std::ios_base::cur) override;
    virtual void write(const char * s, std::streamsize n) override;
    virtual std::streampos tellp() override;
    virtual void flush() override;
    virtual bool good() const override;
    virtual bool eof() const override;

    /**
     * open, basically resets all variables.
     */
    virtual void open();

    /**
     * write LogContainer
     *
     * @param[in] logContainer log container
     */
    virtual void write(LogContainer * logContainer);

    /**
     * Set file size resp. end-of-file position.
     *
     * @param[in] fileSize file size
     */
    virtual void setFileSize(std::streamsize fileSize);

    /**
     *
     */

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

    /** tellg was changed (after read or seekg) */
    std::condition_variable tellgChanged;

    /** tellp was changed (after write or seekp) */
    std::condition_variable tellpChanged;

private:
    /** is file open? */
    bool m_is_open;

    /** data */
    std::list<LogContainer *> m_data;

    /** get position */
    std::streampos m_tellg;

    /** put position */
    std::streampos m_tellp;

    /** last read size */
    std::streamsize m_gcount;

    /** file size */
    std::streamsize m_fileSize;

    /** buffer size */
    std::streamsize m_bufferSize;

    /** error state */
    std::ios_base::iostate m_rdstate;

    /** mutex */
    mutable std::mutex m_mutex;

    /** default log container size */
    DWORD m_defaultLogContainerSize;

    /**
     * Returns the file container, which contains pos.
     *
     * Searches through the data vector to find the logContainer, which contains the position.
     * If the position is behind the last logContainer, return nullptr to indicate a new
     * LogContainer need to be appended.
     *
     * @param[in] pos position
     * @return log container or nullptr
     */
    LogContainer * logContainerContaining(std::streampos pos);
};

}
}
