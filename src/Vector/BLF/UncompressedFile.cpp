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

#include <Vector/BLF/UncompressedFile.h>

#include <cstring>

#include <Vector/BLF/Exceptions.h>

namespace Vector {
namespace BLF {

UncompressedFile::UncompressedFile() :
    tellgChanged(),
    tellpChanged(),
    m_is_open(false),
    m_data(),
    m_tellg(0),
    m_tellp(0),
    m_gcount(0),
    m_fileSize(0x7fffffffffffffff),
    m_maxFileSize(0x7fffffffffffffff),
    m_rdstate(std::ios_base::goodbit),
    m_mutex()
{
}

UncompressedFile::~UncompressedFile()
{
    close();
}

void UncompressedFile::close()
{
    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_mutex);

        /* stop */
        m_is_open = false;
    }

    /* trigger blocked threads */
    tellgChanged.notify_all();
    tellpChanged.notify_all();
}

std::streamsize UncompressedFile::gcount() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_gcount;
}

void UncompressedFile::read(char * s, std::streamsize n)
{
    {
        /* mutex lock */
        std::unique_lock<std::mutex> lock(m_mutex);

        /* abort if stream is not good */
        if (m_rdstate != std::ios_base::goodbit) {
            m_gcount = 0;
            return;
        }

        /* wait until there is sufficient data */
        tellpChanged.wait(lock, [this, n]{
            return
                !m_is_open ||
                (m_tellg + n <= m_tellp) ||
                (m_tellg + n > m_fileSize);
        });

        /* handle read behind eof */
        if (m_tellg + n > m_fileSize) {
            n = m_fileSize - m_tellg;
            m_rdstate = std::ios_base::eofbit;
        } else {
            m_rdstate = std::ios_base::goodbit;
        }

        /* find starting log container */
        LogContainer * logContainer = logContainerContaining(m_tellg);

        /* read data */
        m_gcount = 0;
        while(n > 0) {
            /* offset to read */
            std::streampos filePosition = logContainer->filePosition;
            std::streamoff offset = m_tellg - filePosition;

            /* copy data */
            std::streamsize gcount = n;
            if (gcount > logContainer->uncompressedFileSize) {
                gcount = logContainer->uncompressedFileSize;
            }
            std::copy(logContainer->uncompressedFile.begin() + offset, logContainer->uncompressedFile.begin() + offset + gcount, s);

            /* remember get count */
            m_gcount += gcount;

            /* new get position */
            m_tellg += gcount;

            /* advance */
            s += gcount;

            /* calculate remaining data to copy */
            n -= gcount;
        }
    }

    /* notify */
    tellgChanged.notify_all();
}

std::streampos UncompressedFile::tellg()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_tellg;
}

void UncompressedFile::seekg(std::streamoff off, const std::ios_base::seekdir /*way*/)
{
    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_mutex);

        /* new get position */
        m_tellg += off;
    }

    /* notify */
    tellgChanged.notify_all();
}

void UncompressedFile::write(const char * s, std::streamsize n)
{
    {
        /* mutex lock */
        std::unique_lock<std::mutex> lock(m_mutex);

        /* abort if stream is not good */
        if (m_rdstate != std::ios_base::goodbit) {
            return;
        }

        /* wait for free space */
        tellgChanged.wait(lock, [this]{
            return
                !m_is_open ||
                ((m_tellp - m_tellg) < m_maxFileSize);
        });

        /* find starting log container */
        LogContainer * logContainer = logContainerContaining(m_tellp);

        /* write data */
        while(n > 0) {
            /* append new log container */
            if (logContainer == nullptr) {
                /* append new log container */
                logContainer = new LogContainer;
                logContainer->uncompressedFileSize = 0x20000; // @todo default log container size
                logContainer->uncompressedFile.resize(0x20000);
                if (m_data.back() != nullptr) {
                    logContainer->filePosition =
                        m_data.back()->filePosition +
                        static_cast<std::streamsize>(m_data.back()->uncompressedFileSize);
                }
                m_data.push_back(logContainer);
            }

            /* calculate max write size */
            uint32_t pcount = n;
            if (pcount > logContainer->uncompressedFileSize) {
                pcount = logContainer->uncompressedFileSize;
            }

            /* offset to write */
            std::streamoff offset = m_tellp - logContainer->filePosition;

            /* copy data */
            std::copy(s, s + pcount, logContainer->uncompressedFile.begin() + offset);

            /* advance put position */
            m_tellp += pcount;

            /* calculate remaining data to write */
            n -= pcount;
        }

        /* if new position is behind eof, shift it */
        if (m_tellp >= m_fileSize) {
            m_fileSize = m_tellp;
        }
    }

    /* notify */
    tellpChanged.notify_all();
}

std::streampos UncompressedFile::tellp()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_tellp;
}

void UncompressedFile::flush()
{
    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* wait till file is empty */
    tellgChanged.wait(lock, [this]{
        return (m_tellg >= m_tellp);
    });
}

bool UncompressedFile::eof() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return (m_rdstate & std::ios_base::eofbit);
}

void UncompressedFile::open()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* reset data buffer */
    m_is_open = true;
    m_data.clear();
    m_tellg = 0;
    m_tellp = 0;
    m_gcount = 0;
    m_fileSize = 0x7fffffffffffffff;
    m_maxFileSize = 0x7fffffffffffffff;
    m_rdstate = std::ios_base::goodbit;
}

void UncompressedFile::write(LogContainer * logContainer)
{
    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_mutex);

        /* append logContainer */
        m_data.push_back(logContainer);
        logContainer->filePosition = m_tellp;

        /* advance put pointer */
        m_tellp += logContainer->uncompressedFileSize;
    }

    /* notify */
    tellpChanged.notify_all();
}

void UncompressedFile::setFileSize(std::streamsize fileSize)
{
    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_mutex);

        /* set eof at m_dataEnd */
        m_fileSize = fileSize;
    }

    /* notify */
    tellpChanged.notify_all();
}

bool UncompressedFile::atEof() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* next is eof */
    return (m_tellp >= m_fileSize);
}

std::streamsize UncompressedFile::size() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* size between put/write and get/read positions */
    return (m_tellp - m_tellg);
}

void UncompressedFile::setMaxFileSize(std::streamsize maxFileSize)
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* set max size */
    m_maxFileSize = maxFileSize;
}

void UncompressedFile::dropOldData()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* check if drop should be done now */
    LogContainer * logContainer = m_data.front();
    if (logContainer) {
        std::streampos position = logContainer->filePosition + static_cast<std::streamsize>(logContainer->uncompressedFileSize);
        if ((position > m_tellg) || (position > m_tellp) || (position > m_fileSize)) {
            /* don't drop yet */
            return;
        }
    }

    /* drop data */
    m_data.pop_front();
}

LogContainer * UncompressedFile::logContainerContaining(std::streampos pos)
{
    /* loop over all logContainers */
    for(LogContainer * logContainer: m_data) {
        /* when file position is contained ... */
        if ((pos >= logContainer->filePosition) &&
            (pos < (logContainer->filePosition + static_cast<std::streamsize>(logContainer->uncompressedFileSize)))) {

            /* ... return log container */
            return logContainer;
        }
    }

    /* not found, so return nullptr */
    return nullptr;
}

}
}
