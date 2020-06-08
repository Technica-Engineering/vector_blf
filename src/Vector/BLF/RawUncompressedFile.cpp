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

#include <Vector/BLF/RawUncompressedFile.h>

#undef NDEBUG
#include <cassert>

namespace Vector {
namespace BLF {

RawUncompressedFile::RawUncompressedFile(StructuredCompressedFile & structuredCompressedFile) :
    m_structuredCompressedFile(structuredCompressedFile)
{
}

void RawUncompressedFile::open(const char * /*filename*/, std::ios_base::openmode /*mode*/) {
    assert(false);
}

bool RawUncompressedFile::is_open() const {
    assert(false);
}

void RawUncompressedFile::close() {
    assert(false);
}

bool RawUncompressedFile::good() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_rdstate == std::ios_base::goodbit;
}

bool RawUncompressedFile::eof() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_rdstate & std::ios_base::eofbit;
}

std::streamsize RawUncompressedFile::gcount() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_gcount;
}

void RawUncompressedFile::read(char * s, std::streamsize n) {
    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* wait until there is sufficient data */
    tellpChanged.wait(lock, [&] {
        return
        m_abort ||
        (n + m_gpos <= m_ppos) ||
        (n + m_gpos > m_fileSize);
    });

    /* handle read behind eof */
    if (n + m_gpos > m_fileSize) {
        n = m_fileSize - m_gpos;
        m_rdstate = std::ios_base::eofbit | std::ios_base::failbit;
    } else
        m_rdstate = std::ios_base::goodbit;

    /* read data */
    m_gcount = 0;
    while (n > 0) {
        /* find starting log container */
        std::shared_ptr<LogContainer> logContainer = m_structuredCompressedFile.logContainerContaining(m_gpos);
        if (!logContainer)
            break;

        /* offset to read */
        std::streamoff offset = m_gpos - logContainer->filePosition;

        /* copy data */
        std::streamsize gcount = std::min(n, static_cast<std::streamsize>(logContainer->uncompressedFileSize - offset));
        std::copy(logContainer->uncompressedFile.cbegin() + offset, logContainer->uncompressedFile.cbegin() + offset + gcount, s);

        /* remember get count */
        m_gcount += gcount;

        /* new get position */
        m_gpos += gcount;

        /* advance */
        s += gcount;

        /* calculate remaining data to copy */
        n -= gcount;
    }

    /* notify */
    tellgChanged.notify_all();
}

std::streampos RawUncompressedFile::tellg() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* in case of failure return -1 */
    if (m_rdstate & (std::ios_base::failbit | std::ios_base::badbit))
        return -1;
    return m_gpos;
}

void RawUncompressedFile::seekg(const std::streampos pos) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* new get position */
    m_gpos = pos;

    /* notify */
    tellgChanged.notify_all();
}

void RawUncompressedFile::seekg(const std::streamoff off, const std::ios_base::seekdir way) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* new get position */
    switch(way) {
    case std::ios_base::beg:
        m_gpos = off;
        break;
    case std::ios_base::cur:
        m_gpos = m_gpos + off;
        break;
    case std::ios_base::end:
        m_gpos = m_fileSize + off;
        break;
    default:
        assert(false);
    }

    /* notify */
    tellgChanged.notify_all();
}

void RawUncompressedFile::write(const char * s, std::streamsize n) {
    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* wait for free space */
    tellgChanged.wait(lock, [&] {
        return
        m_abort ||
        ((m_ppos - m_gpos) < m_bufferSize);
    });

    /* write data */
    while (n > 0) {
        /* find starting log container */
        std::shared_ptr<LogContainer> logContainer = m_structuredCompressedFile.logContainerContaining(m_ppos);

        /* append new log container */
        if (!logContainer) {
            /* append new log container */
            logContainer = std::make_shared<LogContainer>();
            logContainer->uncompressedFile.resize(m_structuredCompressedFile.defaultLogContainerSize());
            logContainer->uncompressedFileSize = logContainer->uncompressedFile.size();
            if (!m_structuredCompressedFile.empty()) {
                logContainer->filePosition =
                    m_structuredCompressedFile.back()->uncompressedFileSize +
                    m_structuredCompressedFile.back()->filePosition;
            }
            m_structuredCompressedFile.push_back(logContainer);
        }

        /* offset to write */
        std::streamoff offset = m_ppos - logContainer->filePosition;

        /* copy data */
        std::streamsize pcount = std::min(n, static_cast<std::streamsize>(logContainer->uncompressedFileSize - offset));
        if (pcount > 0) {
            std::copy(s, s + pcount, logContainer->uncompressedFile.begin() + offset);

            /* new put position */
            m_ppos += pcount;

            /* advance */
            s += pcount;

            /* calculate remaining data to copy */
            n -= pcount;
        }
    }

    /* if new position is behind eof, shift it */
    if (m_ppos >= m_fileSize)
        m_fileSize = m_ppos;

    /* notify */
    tellpChanged.notify_all();
}

std::streampos RawUncompressedFile::tellp() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* in case of failure return -1 */
    if (m_rdstate & (std::ios_base::failbit | std::ios_base::badbit))
        return -1;
    return m_ppos;
}

void RawUncompressedFile::seekp(const std::streampos /*pos*/) {
    /* should not be used */
    assert(false);
}

void RawUncompressedFile::seekp(const std::streamoff off, const std::ios_base::seekdir way) {
    /* only to be used to skip padding bytes */
    assert(off >= 0);
    assert(way == std::ios_base::cur);

    std::vector<char> zero(off);
    write(zero.data(), zero.size()); // write does the lock
}

void RawUncompressedFile::abort() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* stop */
    m_abort = true;

    /* trigger blocked threads */
    tellgChanged.notify_all();
    tellpChanged.notify_all();
}

void RawUncompressedFile::write(const std::shared_ptr<LogContainer> & logContainer) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* append logContainer */
    m_structuredCompressedFile.push_back(logContainer);
    logContainer->filePosition = m_ppos;

    /* advance put pointer */
    m_ppos += logContainer->uncompressedFileSize;

    /* notify */
    tellpChanged.notify_all();
}

void RawUncompressedFile::nextLogContainer() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* find starting log container */
    std::shared_ptr<LogContainer> logContainer = m_structuredCompressedFile.logContainerContaining(m_ppos);
    if (logContainer) {
        /* offset to write */
        std::streamoff offset = m_ppos - logContainer->filePosition;

        /* resize logContainer, if it's not already a newly created one */
        if (offset > 0) {
            logContainer->uncompressedFile.resize(offset);
            logContainer->uncompressedFileSize = offset;
        }
    }
}

std::streamsize RawUncompressedFile::fileSize() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* return file size */
    return m_fileSize;
}

void RawUncompressedFile::setFileSize(std::streamsize fileSize) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* set eof at m_dataEnd */
    m_fileSize = fileSize;

    /* notify */
    tellpChanged.notify_all();
}

void RawUncompressedFile::setBufferSize(std::streamsize bufferSize) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* set max size */
    m_bufferSize = bufferSize;
}

void RawUncompressedFile::dropOldData() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* check if drop should be done now */
    if (m_structuredCompressedFile.empty()) {
        return;
    }
    std::shared_ptr<LogContainer> logContainer = m_structuredCompressedFile.front();
    if (logContainer) {
        std::streampos position = logContainer->uncompressedFileSize + logContainer->filePosition;
        if ((position > m_gpos) || (position > m_ppos) || (position > m_fileSize)) {
            /* don't drop yet */
            return;
        }
    }

    /* drop data */
    // @todo m_structuredCompressedFile.pop_front();
}

}
}
